// Copyright (C) 2019 John Donoghue   <john.donoghue@ieee.org>
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

using std::string;

#include "serialport_class.h"

char *
winerror (int err)
{
  static char errstring[100];

  if (err != 0) 
    return strerror (err);
  else
   {
     DWORD e;

     e = GetLastError ();

     if (FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, 0, e,
                        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), errstring,
                        sizeof(errstring)-1, 0) < 0)
       {
         errstring[0] = '\0';
       }
    }
  return errstring;
}

DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_serialport, "octave_serialport", "octave_serialport");

octave_serialport::octave_serialport(void)
{
  static bool type_registered = false;

  if (! type_registered)
    {
      type_registered = true;
      register_type ();
    }

  fd = INVALID_HANDLE_VALUE;
}

void 
octave_serialport::open (const std::string &path)
{
  portPath = path;
  name = "Serial-" + path;

  // use full extended port names if not already specified
  std::string fullPath = path;
  if (fullPath.length() > 0 && fullPath[0] != '\\')
    fullPath = "\\\\.\\" + path;

  fd = CreateFile(fullPath.c_str (), GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    
  if (! fd_is_valid())
    {
      error("serialport: Error opening the interface: %s\n", winerror (errno));
      return;
    }

  // clear any errors that may be on the port
  COMSTAT stats;
  DWORD err;
  ClearCommError (fd, &err, &stats);

  // Clean the configuration struct (DCB)
  memset (&config, 0, sizeof (config));
  // set up device settings
  config.DCBlength = sizeof (config);
  
  if(GetCommState (fd, &config) == FALSE)
    {
      error ("serialport: Failed to get terminal attributes: %s\n", winerror (errno));
      octave_serialport::close ();
      return;
    }

  timeouts.ReadIntervalTimeout = MAXDWORD;
  timeouts.ReadTotalTimeoutMultiplier = 0;
  timeouts.ReadTotalTimeoutConstant = 0;
  timeouts.WriteTotalTimeoutMultiplier = 0;
  timeouts.WriteTotalTimeoutConstant = 0;

  timeout = -1;

  if (SetCommTimeouts(fd, &timeouts) == FALSE)
    {
      error ("serialport: Failed to disable timeouts: %s\n", winerror (errno));
      octave_serialport::close ();
      return;
    }

  return;
}

octave_serialport::~octave_serialport(void)
{
  octave_serialport::close();
}

int
octave_serialport::read(uint8_t *buf, unsigned int len)
{
  if (! fd_is_valid ())
    {
      error ("serialport: Interface must be opened first...");
      return 0;
    }

  size_t bytes_read = 0;
  ssize_t read_retval = -1;

  double maxwait = timeout;
  // While not interrupted in blocking mode
  while (bytes_read < len)
    {
      OCTAVE_QUIT;

      DWORD readsz;
      read_retval = -1;
      if (ReadFile (fd, (buf + bytes_read), len - bytes_read, &readsz, NULL) == TRUE)
        {
          read_retval = readsz;
        }

      if(read_retval < 0)
        {
          error ("serialport.read: Error while reading: %s\n", winerror (errno));
          break;
        }

      bytes_read += read_retval;

      if (read_retval == 0 && !blocking_read)
        {
          maxwait -= (double)timeouts.ReadTotalTimeoutConstant/1000.0;

	  // actual timeout
	  if (maxwait <= 0)
            break;
	}
    }

  return bytes_read;
}

int
octave_serialport::write (const std::string & str)
{
  if (! fd_is_valid ())
    {
      error("serialport: Interface must be opened first...");
      return -1;
    }
  int wrote_ret = -1;
  DWORD wrote;
  if (WriteFile (fd, str.c_str (), str.length (), &wrote, NULL) == TRUE)
    {
      wrote_ret = wrote;
      byteswritten += wrote;
    }
  return wrote_ret;
}

int
octave_serialport::write (uint8_t *buf, unsigned int len)
{
  if (! fd_is_valid ())
    {
      error("serialport: Interface must be opened first...");
      return -1;
    }
  int wrote_ret = -1;
  DWORD wrote;
  if (WriteFile (fd, buf, len, &wrote, NULL) == TRUE)
    {
      wrote_ret = wrote;
      byteswritten += wrote;
    }
  return wrote_ret;
}

int
octave_serialport::set_timeout (double newtimeout)
{
  if (! fd_is_valid())
    {
      error ("serialport: Interface must be opened first...");
      return -1;
    }

  if (newtimeout < -1 || newtimeout > 255)
    {
      error ("serialport: timeout value must be between [-1..255]...");
      return -1;
    }

  timeout = newtimeout;

  newtimeout *= 1000;

  // Disable custom timeout, enable blocking read
  if (newtimeout < 0)
    {
      blocking_read = true;
      newtimeout = 50;
    }
  // Enable custom timeout, disable blocking read
  else
    {
      blocking_read = false;
      if (newtimeout > 50)
        newtimeout = 50;
    }

  timeouts.ReadIntervalTimeout = MAXDWORD;
  timeouts.ReadTotalTimeoutMultiplier = 0;
  timeouts.ReadTotalTimeoutConstant = newtimeout;
  timeouts.WriteTotalTimeoutMultiplier = 0;
  timeouts.WriteTotalTimeoutConstant = 0;

  if (SetCommTimeouts (fd, &timeouts) == FALSE)
    {
      error ("serialport.timeout: error setting timeout...");
      return -1;
    }

  return 1;
}

double
octave_serialport::get_timeout (void) const
{
  if (blocking_read)
    return -1;
  else
    return timeout;
}

int
octave_serialport::set_stopbits (unsigned short stopbits)
{
  if (! fd_is_valid ())
    {
      error ("serialport: Interface must be opened first...");
      return -1;
    }

  if (stopbits == 1)
    {
      // Set to one stop bit
      config.StopBits = ONESTOPBIT;
    }
  else if (stopbits == 2)
    {
      // Set to two stop bits
      config.StopBits = TWOSTOPBITS;
    }
  else
    {
      error ("serialport: Only 1 or 2 stop bits are supported...");
      return false;
    }

  if (SetCommState (fd,&config) == FALSE)
    {
      error ("serialport: error setting stop bits: %s\n", winerror (errno));
      return false;
    }

  return true;
}

int
octave_serialport::get_stopbits (void) const
{
  if (! fd_is_valid ())
    {
      error ("serialport: Interface must be opened first...");
      return -1;
    }
  if (config.StopBits == TWOSTOPBITS)
    return 2;
  else
    return 1;
}

int
octave_serialport::set_databits (unsigned short bytesize)
{
  if (! fd_is_valid ())
    {
      error ("serialport: Interface must be opened first...");
      return -1;
    }

  if(bytesize < 5 || bytesize > 8)
    {
      error ("serialport.databits: expecting value between [5..8]...");
      return false;
    }

  config.ByteSize = bytesize;

  if (SetCommState (fd, &config) == FALSE)
    {
      error ("serialport: error setting data size: %s\n", winerror (errno));
      return false;
    }

  return true;
}

int
octave_serialport::get_databits (void) const
{
  if (! fd_is_valid ())
    {
      error("serialport: Interface must be opened first...");
      return -1;
    }

  return config.ByteSize;
}

int
octave_serialport::set_baudrate (unsigned int baud)
{
  if (! fd_is_valid ())
    {
      error ("serialport: Interface must be opened first...");
      return -1;
    }
 
  DWORD old_baud = config.BaudRate;

  config.BaudRate = baud;

  if (SetCommState (fd, &config) == FALSE)
    {
      error ("serialport: error setting baud rate: %s\n", winerror (errno));
      config.BaudRate = old_baud;
      return false;
    }

  return true;
}

int
octave_serialport::get_baudrate (void) const
{
  if (! fd_is_valid ())
    {
      error("serialport: Interface must be opened first...");
      return -1;
    }

  return config.BaudRate;
}

int
octave_serialport::flush (unsigned short queue_selector)
{
  if (! fd_is_valid ())
    {
      error ("serialport: Interface must be opened first...");
      return -1;
    }

  int flag;

  switch (queue_selector)
    {
    case 0: flag = PURGE_TXCLEAR; break;
    case 1: flag = PURGE_RXCLEAR; break;
    case 2: flag = PURGE_RXCLEAR|PURGE_TXCLEAR; break;
    default:
      error ("serialport: only [0..2] values are accepted...");
      return false;
    }

  if (PurgeComm (fd,flag) == FALSE)
    return -1;
  else
    return true;
}

int
octave_serialport::sendbreak (unsigned short ms)
{
  if (! fd_is_valid ())
    {
      error ("serialport: Interface must be opened first...");
      return -1;
    }

  if (ms > 5000)
    ms = 5000;

  if(SetCommBreak(fd) == TRUE)
  {
    Sleep(ms);

    ClearCommBreak(fd);

    return true;
  }

  return false;
}

int
octave_serialport::set_parity (const std::string &newparity)
{
  if (! fd_is_valid ())
    {
        error ("serialport: Interface must be opened first...");
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
      config.Parity = NOPARITY;
  }
  else if (parity == "e" || parity == "even")
    {
      // Enable parity generation/checking
      config.Parity = EVENPARITY;
    }
  else if (parity == "o" || parity == "odd")
    {
       config.Parity = ODDPARITY;
    }
  else
    {
      error ("serialport: Only [N]one, [E]ven or [O]dd parities are supported...");
      return false;
    }

  if (SetCommState (fd, &config) == FALSE)
    {
      error ("serialport: error setting parity: %s\n", winerror (errno));
      return false;
    }

  return true;
}

std::string
octave_serialport::get_parity (void) const
{
  if(config.Parity == NOPARITY)
    return "None";
  else if(config.Parity == ODDPARITY)
    return "Odd";
  else
    return "Even";
}

int
octave_serialport::set_flowcontrol (const std::string &newctrl)
{
  if (! fd_is_valid ())
    {
      error ("serialport: Interface must be opened first...");
      return -1;
    }

  // Convert string to lowercase
  std::string ctrl = newctrl;
  std::transform (ctrl.begin (), ctrl.end (), ctrl.begin (), ::tolower);

  if (ctrl == "n" || ctrl == "none")
    {
      config.fDtrControl = DTR_CONTROL_ENABLE;
      config.fRtsControl = RTS_CONTROL_ENABLE;
      config.fOutxCtsFlow = 0;
      config.fOutxDsrFlow = 0;
      config.fOutX = 0;
      config.fInX = 0;
    }
  else if (ctrl == "h" || ctrl == "hardware")
    {
      config.fDtrControl = DTR_CONTROL_ENABLE;
      config.fRtsControl = RTS_CONTROL_HANDSHAKE;
      config.fOutxCtsFlow = 1;
      config.fOutxDsrFlow = 0;
      config.fOutX = 0;
      config.fInX = 0;
    }
  else if (ctrl == "s" || ctrl == "software")
    {
      config.fDtrControl = DTR_CONTROL_ENABLE;
      config.fRtsControl = RTS_CONTROL_ENABLE;
      config.fOutxCtsFlow = 0;
      config.fOutxDsrFlow = 0;
      config.fOutX = 1;
      config.fInX = 1;
    }
  else
    {
      error ("serialport.flowcontrol: Only [N]one, [s]software or [h]hardware flow contols are supported...");
      return false;
    }

  return true;
}

std::string
octave_serialport::get_flowcontrol (void) const
{
  if (config.fOutxCtsFlow == 1)
    return "hardware";
  else if (config.fOutX == 1)
    return "software";
  else
    return "none";
}



void
octave_serialport::get_control_line_status (void)
{
  if (! fd_is_valid())
    {
      error ("serialport: Interface must be opened first...");
      return;
    }

  GetCommState (fd, &config);
  GetCommModemStatus (fd, &status);
}

bool
octave_serialport::get_control_line (const std::string &control_signal)
{
  get_control_line_status ();

  if (control_signal == "DTR")
    return (config.fDtrControl == DTR_CONTROL_ENABLE);
  else if (control_signal == "RTS")
    return (config.fRtsControl == RTS_CONTROL_ENABLE);
  else if (control_signal == "CTS")
    return (status & MS_CTS_ON);
  else if (control_signal == "DSR")
    return (status & MS_DSR_ON);
  else if (control_signal == "CD")
    return (status & MS_RLSD_ON);
  else if (control_signal == "RI")
    return (status & MS_RING_ON);
  else
    error("serialport: Unknown control signal...");
  return false;
}

void
octave_serialport::set_control_line (const std::string &control_signal, bool set)
{
  get_control_line_status ();

  int signal;

  if (control_signal == "DTR")
    {
      if(set)
        config.fDtrControl = DTR_CONTROL_ENABLE;
      else
        config.fDtrControl = DTR_CONTROL_DISABLE;
    }
  else if (control_signal == "RTS")
    {
      if(set)
        config.fRtsControl = RTS_CONTROL_ENABLE;
      else
        config.fRtsControl = RTS_CONTROL_DISABLE;
    }
  else
    {
      error("serialport: Unknown control signal...");
      return;
    }

  SetCommState (fd, &config);
}

bool
octave_serialport::fd_is_valid (void) const
{
  return (fd != INVALID_HANDLE_VALUE);
}

void
octave_serialport::close (void)
{
  if (fd_is_valid ())
    {
      CloseHandle(fd);
      fd = INVALID_HANDLE_VALUE;
    }
}

int
octave_serialport::get_numbytesavailable (void) const
{
  int available = 0;
  if (fd_is_valid ())
    {
      COMSTAT stats;
      DWORD err;
      if (ClearCommError (fd, &err, &stats))
        available = stats.cbInQue;
    }
  return available;
}
#endif
