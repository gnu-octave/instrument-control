// Copyright (C) 2014-2020 John Donoghue   <john.donoghue@ieee.org>
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
#if HAVE_OCTAVE_LO_SYSDEP_H
  #include <octave/lo-sysdep.h>
#endif

#include <iostream>
#include <string>
#include <algorithm>

using std::string;

#include "serial_class.h"

std::string
winerror ()
{
  DWORD e;

  e = GetLastError ();

#if HAVE_OCTAVE_U8_TO_WSTRING
  wchar_t errstring[100+1];
  if (FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, 0, e,
                     MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), errstring,
                     100, 0) == 0)
    {
      errstring[0] = '\0';
    }
  return octave::sys::u8_from_wstring (errstring);
#else
  char errstring[100+1];
  if (FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, 0, e,
                     MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), errstring,
                     100, 0) == 0)
    {
      errstring[0] = '\0';
    }
  return errstring;
#endif
}


DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_serial, "octave_serial", "octave_serial");

DEFBINOP_CLASS_OP (eq_serial_serial, serial, serial, ==)
DEFBINOP_CLASS_OP (ne_serial_serial, serial, serial, !=)

octave_serial::octave_serial(void)
{
  static bool type_registered = false;

  if (! type_registered)
    {
      type_registered = true;
      register_type ();
      INSTALL_BINOP (op_eq, octave_serial, octave_serial, eq_serial_serial);
      INSTALL_BINOP (op_ne, octave_serial, octave_serial, ne_serial_serial);
    }

  fd = INVALID_HANDLE_VALUE;
}

void 
octave_serial::open (const std::string &path)
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
      std::string err = winerror ();
      error("serial: Error opening the interface: %s\n", err.c_str ());
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
      std::string err = winerror ();
      octave_serial::close ();
      error ("serial: Failed to get terminal attributes: %s\n", err.c_str ());
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
      std::string err = winerror ();
      octave_serial::close ();
      error ("serial: Failed to disable timeouts: %s\n", err.c_str ());
      return;
    }

  return;
}

octave_serial::~octave_serial(void)
{
  octave_serial::close();
}

int
octave_serial::read(uint8_t *buf, unsigned int len)
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

      DWORD readsz;
      read_retval = -1;
      if (ReadFile (fd, (buf + bytes_read), len - bytes_read, &readsz, NULL) == TRUE)
        {
          read_retval = readsz;
        }

      if(read_retval < 0)
        {
          error ("srl_read: Error while reading: %s\n", winerror ().c_str ());
          break;
        }

      bytes_read += read_retval;

      if (read_retval == 0 && !blocking_read)
        {
          maxwait -= timeouts.ReadTotalTimeoutConstant/100;

	  // actual timeout
	  if (maxwait <= 0)
            break;
	}
    }

  return bytes_read;
}

int
octave_serial::write (const std::string & str)
{
  if (! fd_is_valid ())
    {
      error("serial: Interface must be opened first...");
      return -1;
    }
  int wrote_ret = -1;
  DWORD wrote;
  if (WriteFile (fd, str.c_str (), str.length (), &wrote, NULL) == TRUE)
    {
      wrote_ret = wrote;
    }
  return wrote_ret;
}

int
octave_serial::write (uint8_t *buf, unsigned int len)
{
  if (! fd_is_valid ())
    {
      error("serial: Interface must be opened first...");
      return -1;
    }
  int wrote_ret = -1;
  DWORD wrote;
  if (WriteFile (fd, buf, len, &wrote, NULL) == TRUE)
    {
      wrote_ret = wrote;
    }
  return wrote_ret;
}

int
octave_serial::set_timeout (short newtimeout)
{
  if (! fd_is_valid())
    {
      error ("serial: Interface must be opened first...");
      return -1;
    }

  if (newtimeout < -1 || newtimeout > 255)
    {
      error ("srl_timeout: timeout value must be between [-1..255]...");
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
      if (newtimeout > 10)
        newtimeout = 5;
    }

  timeouts.ReadIntervalTimeout = MAXDWORD;
  timeouts.ReadTotalTimeoutMultiplier = 0;
  timeouts.ReadTotalTimeoutConstant = newtimeout*100;
  timeouts.WriteTotalTimeoutMultiplier = 0;
  timeouts.WriteTotalTimeoutConstant = 0;

  if (SetCommTimeouts (fd, &timeouts) == FALSE)
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
  if (! fd_is_valid ())
    {
      error ("serial: Interface must be opened first...");
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
      error ("srl_stopbits: Only 1 or 2 stop bits are supported...");
      return false;
    }

  if (SetCommState (fd,&config) == FALSE)
    {
      error ("srl_stopbits: error setting stop bits: %s\n", winerror ().c_str ());
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
  if (config.StopBits == TWOSTOPBITS)
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

  if(bytesize < 5 || bytesize > 8)
    {
      error ("srl_bytesize: expecting value between [5..8]...");
      return false;
    }

  config.ByteSize = bytesize;

  if (SetCommState (fd, &config) == FALSE)
    {
      error ("serial: error setting byte size: %s\n", winerror ().c_str ());
      return false;
    }

  return true;
}

int
octave_serial::get_bytesize (void) const
{
  if (! fd_is_valid ())
    {
      error("serial: Interface must be opened first...");
      return -1;
    }

  return config.ByteSize;
}

int
octave_serial::set_baudrate (unsigned int baud)
{
  if (! fd_is_valid ())
    {
      error ("serial: Interface must be opened first...");
      return -1;
    }
 
  DWORD old_baud = config.BaudRate;

  config.BaudRate = baud;

  if (SetCommState (fd, &config) == FALSE)
    {
      error ("serial: error setting baud rate: %s\n", winerror ().c_str ());
      config.BaudRate = old_baud;
      return false;
    }

  return true;
}

int
octave_serial::get_baudrate (void) const
{
  if (! fd_is_valid ())
    {
      error("serial: Interface must be opened first...");
      return -1;
    }

  return config.BaudRate;
}

int
octave_serial::flush (unsigned short queue_selector)
{
  if (! fd_is_valid ())
    {
      error ("serial: Interface must be opened first...");
      return -1;
    }

  int flag;

  switch (queue_selector)
    {
    case 0: flag = PURGE_TXCLEAR; break;
    case 1: flag = PURGE_RXCLEAR; break;
    case 2: flag = PURGE_RXCLEAR|PURGE_TXCLEAR; break;
    default:
      error ("srl_flush: only [0..2] values are accepted...");
      return false;
    }

  if (PurgeComm (fd,flag) == FALSE)
    return -1;
  else
    return true;
}

int
octave_serial::sendbreak (unsigned short ms)
{
  if (! fd_is_valid ())
    {
      error ("serial: Interface must be opened first...");
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
      error ("srl_parity: Only [N]one, [E]ven or [O]dd parities are supported...");
      return false;
    }

  if (SetCommState (fd, &config) == FALSE)
    {
      error ("srl_parity: error setting parity: %s\n", winerror ().c_str ());
      return false;
    }

  return true;
}

std::string
octave_serial::get_parity (void) const
{
  if(config.Parity == NOPARITY)
    return "None";
  else if(config.Parity == ODDPARITY)
    return "Odd";
  else
    return "Even";
}

void
octave_serial::get_control_line_status (void)
{
  if (! fd_is_valid())
    {
      error ("serial: Interface must be opened first...");
      return;
    }

  GetCommState (fd, &config);
  GetCommModemStatus (fd, &status);
}

bool
octave_serial::get_control_line (const std::string &control_signal)
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
    error("serial: Unknown control signal...");
  return false;
}

void
octave_serial::set_control_line (const std::string &control_signal, bool set)
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
      error("serial: Unknown control signal...");
      return;
    }

  SetCommState (fd, &config);
}

bool
octave_serial::fd_is_valid (void) const
{
  return (fd != INVALID_HANDLE_VALUE);
}

void
octave_serial::close (void)
{
  if (fd_is_valid ())
    {
      CloseHandle(fd);
      fd = INVALID_HANDLE_VALUE;
    }
}

int
octave_serial::get_bytesavailable (void) const
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
