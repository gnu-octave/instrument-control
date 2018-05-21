// Copyright (C) 2018   John Donoghue   <john.donoghue@ieee.org>
// Copyright (C) 2012   Andrius Sutas   <andrius.sutas@gmail.com>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.

#include <octave/oct.h>

#ifdef HAVE_CONFIG_H
#include "../config.h"
#endif

#ifdef BUILD_SERIAL
#include <iostream>
#include <string>
#include <algorithm>

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "serial_class.h"

DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_serial, "octave_serial", "octave_serial");

octave_serial::octave_serial (void)
: fd (-1)
{
  static bool type_registered = false;

  if (! type_registered)
    {
      type_registered = true;
      register_type ();
      INSTALL_BINOP (op_eq, octave_serial, octave_serial, eq_serial_serial);
      INSTALL_BINOP (op_ne, octave_serial, octave_serial, ne_serial_serial);
    }
}

void
octave_serial::open (const std::string &path)
{
  int flags = O_RDWR | O_NOCTTY | O_SYNC | O_NDELAY;
  // O_SYNC - All writes immediately effective, no buffering
  // O_NOCTTY - Do not make serial terminal the controlling terminal for the process
  // O_NDELAY - Do not care what state the DCD signal line is in. Used for open only, later disabled.

  fd = ::open (path.c_str (), flags);
  portPath = path;

  if (fd_is_valid ())
    {
      // Check whether fd is an open file descriptor referring to a terminal
      if(! isatty (fd))
        {
          error("serial: Interface does not refer to a terminal: %s\n", strerror (errno));
          octave_serial::close ();
          return;
        }

      if (tcgetattr (fd, &config) < 0)
        {
          error ("serial: Failed to get terminal attributes: %s\n", strerror (errno));
          octave_serial::close ();
          return;
        }

      // Clear all settings
      config.c_iflag = 0; // Input modes
      config.c_oflag = 0; // Output modes
      config.c_cflag = CS8 | CREAD | CLOCAL; // Control modes, 8n1
      config.c_lflag = 0; // Local modes
      config.c_cc[VMIN] = 1;

      if (tcsetattr (fd, TCSANOW, &config) < 0)
        {
            error ("serial: Failed to set default terminal attributes: %s\n", strerror (errno));
            octave_serial::close ();
            return;
        }

        // Disable NDELAY
      if (fcntl (fd, F_SETFL, 0) < 0)
        {
          error ("serial: Failed to disable NDELAY flag: %s\n", strerror (errno));
          octave_serial::close ();
          return;
        }

      timeout = -1;
      blocking_read = true;
    }
  else
    {
      error ("serial: Error opening the interface: %s\n", strerror (errno));
      return;
    }
}

octave_serial::~octave_serial (void)
{
  octave_serial::close();
}

int
octave_serial::read (uint8_t *buf, unsigned int len)
{
  if (! fd_is_valid ())
    {
      error ("srl_read: Interface must be opened first...");
      return 0;
    }

  size_t bytes_read = 0;
  ssize_t read_retval = -1;

  int maxwait = timeout;
  // While not interrupted in blocking mode
  while (bytes_read < len)
    {
      OCTAVE_QUIT;

      read_retval = ::read (fd, (void *)(buf + bytes_read), len - bytes_read);
      //printf("read_retval: %d\n\r", read_retval);

      if (read_retval < 0)
        {
          error ("srl_read: Error while reading: %s\n", strerror (errno));
          break;
        }

      bytes_read += read_retval;

      // Timeout while in non-blocking mode
      if (read_retval == 0 && !blocking_read)
        {
          maxwait -= config.c_cc[VTIME];

	  // actual timeout
	  if (maxwait <= 0)
            break;
	}
    }

  return bytes_read;
}

int
octave_serial::write (const std::string &str)
{
  if (! fd_is_valid ())
    {
      error ("serial: Interface must be opened first...");
      return -1;
    }

  return ::write (fd, str.c_str (), str.length ());
}

int
octave_serial::write(uint8_t *buf, unsigned int len)
{
  if (!fd_is_valid ())
    {
      error ("serial: Interface must be opened first...");
      return -1;
    }

  return ::write (fd, buf, len);
}

int
octave_serial::set_timeout (short newtimeout)
{
  if (! fd_is_valid ())
    {
      error("serial: Interface must be opened first...");
      return -1;
    }

  if (timeout < -1 || timeout > 255)
    {
      error("srl_timeout: timeout value must be between [-1..255]...");
      return -1;
    }

  timeout = newtimeout;

  // Disable custom timeout, enable blocking read
  if (newtimeout < 0)
    {
      blocking_read = true;
      newtimeout = 5;
    }
  // Enable custom timeout, disable blocking read
  else
    {
      blocking_read = false;
      if(newtimeout > 10) newtimeout = 5;
    }


  BITMASK_CLEAR (config.c_lflag, ICANON); // Set non-canonical mode
  config.c_cc[VMIN] = 0;
  config.c_cc[VTIME] = (unsigned) newtimeout; // Set timeout of 'timeout * 10' seconds

  if (tcsetattr (fd, TCSANOW, &config) < 0)
    {
      error ("srl_timeout: error setting timeout...");
      return -1;
    }

  return 1;
}

int
octave_serial::get_timeout (void) const
{
  if (blocking_read)
    return -1;
  else
    return timeout;
}

int
octave_serial::set_stopbits (unsigned short stopbits)
{
  if (!fd_is_valid ())
    {
      error ("serial: Interface must be opened first...");
      return -1;
    }

  /*
   * CSTOPB Send two stop bits, else one.
   */

  if (stopbits == 1)
    {
      // Set to one stop bit
      BITMASK_CLEAR (config.c_cflag, CSTOPB);
    }
  else if (stopbits == 2)
    {
      // Set to two stop bits
      BITMASK_SET (config.c_cflag, CSTOPB);
    }
  else
    {
      error ("srl_stopbits: Only 1 or 2 stop bits are supported...");
      return false;
    }

  if (tcsetattr (fd, TCSANOW, &config) < 0)
    {
      error ("srl_stopbits: error setting stop bits: %s\n", strerror (errno));
      return false;
    }

  return true;
}

int
octave_serial::get_stopbits (void) const
{
  if (! fd_is_valid ())
    {
        error ("serial: Interface must be opened first...");
        return -1;
    }

  if (BITMASK_CHECK (config.c_cflag, CSTOPB))
    return 2;
  else
    return 1;
}

int
octave_serial::set_bytesize (unsigned short bytesize)
{
  if (! fd_is_valid ())
    {
      error ("serial: Interface must be opened first...");
      return -1;
    }

  tcflag_t c_bytesize = 0;

  switch (bytesize)
    {
    case 5: c_bytesize = CS5; break;
    case 6: c_bytesize = CS6; break;
    case 7: c_bytesize = CS7; break;
    case 8: c_bytesize = CS8; break;

    default:
        error ("srl_bytesize: expecting value between [5..8]...");
        return false;
    }

  // Clear bitmask CSIZE
  BITMASK_CLEAR (config.c_cflag, CSIZE);

  // Apply new
  BITMASK_SET (config.c_cflag, c_bytesize);

  if (tcsetattr (fd, TCSANOW, &config) < 0)
    {
      error ("srl_bytesize: error setting byte size: %s\n", strerror (errno));
      return false;
    }

  return true;
}

int
octave_serial::get_bytesize (void) const
{
  if (! fd_is_valid ())
    {
      error ("serial: Interface must be opened first...");
      return -1;
    }

  int retval = -1;

  if (BITMASK_CHECK_VALUE (config.c_cflag, CSIZE, CS5))
    retval = 5;
  else if (BITMASK_CHECK_VALUE (config.c_cflag, CSIZE, CS6))
    retval = 6;
  else if (BITMASK_CHECK_VALUE (config.c_cflag, CSIZE, CS7))
    retval = 7;
  else if (BITMASK_CHECK_VALUE (config.c_cflag, CSIZE, CS8))
    retval = 8;

  return retval;
}

int
octave_serial::set_baudrate (unsigned int baud)
{
  if (! fd_is_valid ())
    {
      error ("serial: Interface must be opened first...");
      return -1;
    }

  speed_t baud_rate = 0;

  switch (baud)
    {
    case 0:
      baud_rate = B0; break;
    case 50:
      baud_rate = B50; break;
    case 75:
      baud_rate = B75; break;
    case 110:
      baud_rate = B110; break;
    case 134:
      baud_rate = B134; break;
    case 150:
      baud_rate = B150; break;
    case 200:
      baud_rate = B200; break;
    case 300:
      baud_rate = B300; break;
    case 600:
      baud_rate = B600; break;
    case 1200:
      baud_rate = B1200; break;
    case 1800:
      baud_rate = B1800; break;
    case 2400:
      baud_rate = B2400; break;
    case 4800:
      baud_rate = B4800; break;
    case 9600:
      baud_rate = B9600; break;
    case 19200:
      baud_rate = B19200; break;
    case 38400:
      baud_rate = B38400; break;
#ifdef B57600
    case 57600:
      baud_rate = B57600; break;
#endif
#ifdef B115200
    case 115200:
      baud_rate = B115200; break;
#endif
#ifdef B230400
    case 230400:
      baud_rate = B230400; break;
#endif
#ifdef B460800
    case 460800:
      baud_rate = B460800; break;
#endif
#ifdef B500000
    case 500000:
      baud_rate = B500000; break;
#endif
#ifdef B576000
    case 576000:
      baud_rate = B576000; break;
#endif
#ifdef B921600
    case 921600:
      baud_rate = B921600; break;
#endif
#ifdef B1000000
    case 1000000:
      baud_rate = B1000000; break;
#endif
#ifdef B1152000
    case 1152000:
      baud_rate = B1152000; break;
#endif
#ifdef B2000000
    case 2000000:
      baud_rate = B2000000; break;
#endif
#ifdef B3000000
    case 3000000:
      baud_rate = B3000000; break;
#endif
#ifdef B3500000
    case 3500000:
      baud_rate = B3500000; break;
#endif
#ifdef B4000000
    case 4000000:
      baud_rate = B4000000; break;
#endif
    default:
      error ("serial: baud rate not supported...");
      return false;
    }

  cfsetispeed (&config, baud_rate);
  cfsetospeed (&config, baud_rate);

  if (tcsetattr (fd, TCSANOW, &config) < 0) 
    {
      error ("srl_baudrate: error setting baud rate: %s\n", strerror (errno));
      return false;
    }

  return true;
}

int
octave_serial::get_baudrate (void) const
{
  if (! fd_is_valid ())
    {
      error ("serial: Interface must be opened first...");
      return -1;
    }

  int retval = -1;

  speed_t baudrate = cfgetispeed (&config);

  if (baudrate == B0)
    retval = 0;
  else if (baudrate == B50)
    retval = 50;
  else if (baudrate == B75)
    retval = 75;
  else if (baudrate == B110)
    retval = 110;
  else if (baudrate == B134)
    retval = 134;
  else if (baudrate == B150)
    retval = 150;
  else if (baudrate == B200)
    retval = 200;
  else if (baudrate == B300)
    retval = 300;
  else if (baudrate == B600)
    retval = 600;
  else if (baudrate == B1200)
    retval = 1200;
  else if (baudrate == B1800)
    retval = 1800;
  else if (baudrate == B2400)
    retval = 2400;
  else if (baudrate == B4800)
    retval = 4800;
  else if (baudrate == B9600)
    retval = 9600;
  else if (baudrate == B19200)
    retval = 19200;
  else if (baudrate == B38400)
    retval = 38400;
  else if (baudrate == B57600)
    retval = 57600;
  else if (baudrate == B115200)
    retval = 115200;
  else if (baudrate == B230400)
    retval = 230400;

  return retval;
}

int
octave_serial::flush (unsigned short queue_selector)
{
  if (! fd_is_valid ())
    {
      error ("serial: Interface must be opened first...");
      return -1;
    }

  /*
   * TCIOFLUSH Flush both pending input and untransmitted output.
   * TCOFLUSH Flush untransmitted output.
   * TCIFLUSH Flush pending input.
   */

  int flag;

  switch (queue_selector)
    {
    case 0: flag = TCOFLUSH; break;
    case 1: flag = TCIFLUSH; break;
    case 2: flag = TCIOFLUSH; break;
    default:
      error("srl_flush: only [0..2] values are accepted...");
      return false;
    }

  return ::tcflush (fd, flag);
}


int
octave_serial::set_parity (const std::string &newparity)
{
  if (! fd_is_valid ())
    {
      error ("serial: Interface must be opened first...");
      return -1;
    }

  // Convert string to lowercase
  std::string parity = newparity;
  std::transform (parity.begin (), parity.end (), parity.begin (), ::tolower);

  /*
   * PARENB Enable parity generation on output and parity checking for input.
   * PARODD If set, then parity for input and output is odd; otherwise even parity is used.
   */

  if (parity == "n" || parity == "none")
    {
      // Disable parity generation/checking
      BITMASK_CLEAR (config.c_cflag, PARENB);
    }
  else if (parity == "e" || parity == "even")
    {
      // Enable parity generation/checking
      BITMASK_SET (config.c_cflag, PARENB);

      // Set to Even
      BITMASK_CLEAR (config.c_cflag, PARODD);

    }
  else if (parity == "o" || parity == "odd")
    {
      // Enable parity generation/checking
      BITMASK_SET (config.c_cflag, PARENB);

      // Set to Odd
      BITMASK_SET (config.c_cflag, PARODD);

    }
  else
    {
      error ("srl_parity: Only [N]one, [E]ven or [O]dd parities are supported...");
      return false;
    }

  if (tcsetattr (fd, TCSANOW, &config) < 0) 
    {
      error ("srl_parity: error setting parity: %s\n", strerror (errno));
      return false;
    }

  return true;
}

std::string
octave_serial::get_parity (void) const
{
  if (!BITMASK_CHECK (config.c_cflag, PARENB))
    return "None";
  else if (BITMASK_CHECK (config.c_cflag, PARODD))
    return "Odd";
  else
    return "Even";
}

void
octave_serial::get_control_line_status (void)
{
  if (! fd_is_valid ())
    {
      error ("serial: Interface must be opened first...");
      return;
    }
  ioctl (fd, TIOCMGET, &status);
}

bool
octave_serial::get_control_line (const std::string &control_signal)
{
  get_control_line_status ();

  if (control_signal == "DTR")
    return (status & TIOCM_DTR);
  else if (control_signal == "RTS")
    return (status & TIOCM_RTS);
  else if (control_signal == "CTS")
    return (status & TIOCM_CTS);
  else if (control_signal == "DSR")
    return (status & TIOCM_DSR);
  else if (control_signal == "CD")
    return (status & TIOCM_CD);
  else if (control_signal == "RI")
    return (status & TIOCM_RI);

  error ("serial: Unknown control signal...");
  return false;

}

void
octave_serial::set_control_line (const std::string &control_signal, bool set)
{

  get_control_line_status ();

  int signal;

  if (control_signal == "DTR")
    signal = TIOCM_DTR;
  else if (control_signal == "RTS")
    signal = TIOCM_RTS;
  else
    {
      error ("serial: Unknown control signal...");
      return;
    }

  if (set)
    status |= signal;
  else
    status &= ~signal;

  ioctl (fd, TIOCMSET, &status);

}

bool
octave_serial::fd_is_valid (void) const
{
  return (fd >= 0);
}

void
octave_serial::close (void)
{
  if (fd_is_valid ())
    {
      ::close (fd);
      fd = -1;
    }
}

int
octave_serial::get_bytesavailable (void) const
{
  int available = 0;
  if (fd_is_valid ())
    {
      ioctl (fd, FIONREAD, &available);
    }
  return available;
}

#endif
