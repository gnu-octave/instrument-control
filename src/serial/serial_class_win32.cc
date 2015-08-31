// Copyright (C) 2014   John Donoghue   <john.donoghue@ieee.org>
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

#include "serial_class.h"

volatile bool read_interrupt = false;

char * winerror(int err)
{
  static char errstring[100];

  if(err != 0) return strerror(err);
  else
  {
    DWORD e;

    e = GetLastError();

    if(FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, 0, e,
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), errstring,
      sizeof(errstring)-1, 0) < 0)
      errstring[0] = '\0';
  }
  return errstring;
}

DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_serial, "octave_serial", "octave_serial");

octave_serial::octave_serial()
{
    this->fd = INVALID_HANDLE_VALUE;
}

void octave_serial::open(string path)
{
   this->fd = CreateFile(path.c_str(), GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
   this->portPath = path;

   if (!this->fd_is_valid())
   {
       error("serial: Error opening the interface: %s\n", winerror(errno));
       return;
   }

   // clear any errors that may be on the port
   COMSTAT stats;
   DWORD err;
   ClearCommError(this->fd, &err, &stats);

   // Clean the configuration struct (DCB)
   memset (&this->config, 0, sizeof (this->config));
   // set up device settings
   this->config.DCBlength = sizeof(this->config);
   if(GetCommState(this->fd,&this->config) == FALSE)
   {
       error("serial: Failed to get terminal attributes: %s\n", winerror(errno));
       this->close();
       return;
   }

   this->timeouts.ReadIntervalTimeout = MAXDWORD;
   this->timeouts.ReadTotalTimeoutMultiplier = 0;
   this->timeouts.ReadTotalTimeoutConstant = 0;
   this->timeouts.WriteTotalTimeoutMultiplier = 0;
   this->timeouts.WriteTotalTimeoutConstant = 0;

   if(SetCommTimeouts(this->fd, &this->timeouts) == FALSE)
   {
       error("serial: Failed to disable timeouts: %s\n", winerror(errno));
       this->close();
       return;
   }

   return;
}

octave_serial::~octave_serial()
{
    this->close();
}

int octave_serial::read(uint8_t *buf, unsigned int len)
{
    if (!this->fd_is_valid())
    {
        error("srl_read: Interface must be opened first...");
        return 0;
    }

    size_t bytes_read = 0;
    ssize_t read_retval = -1;

    // While not interrupted in blocking mode
    while (!read_interrupt)
    {
        DWORD readsz;
        read_retval = -1;
        if(ReadFile(this->fd, buf, len, &readsz, NULL) == TRUE)
        {
           read_retval = readsz;
        }

        if(read_retval < 0)
        {
            error("srl_read: Error while reading: %s\n", winerror(errno));
            break;
        }

        bytes_read += read_retval;

        // Required number of bytes read
        if (bytes_read >= len)
            break;

        // Timeout while in non-blocking mode
        if (read_retval == 0 && !this->blocking_read)
            break;
    }

    return bytes_read;
}

int octave_serial::write(string str)
{
    if (!this->fd_is_valid())
    {
        error("serial: Interface must be opened first...");
        return -1;
    }
    int wrote_ret = -1;
    DWORD wrote;
    if(WriteFile(this->fd, str.c_str(), str.length(), &wrote, NULL) == TRUE)
    {
      wrote_ret = wrote;
    }
    return wrote_ret;
}

int octave_serial::write(uint8_t *buf, unsigned int len)
{
    if (!this->fd_is_valid())
    {
        error("serial: Interface must be opened first...");
        return -1;
    }
    int wrote_ret = -1;
    DWORD wrote;
    if(WriteFile(this->fd, buf, len, &wrote, NULL) == TRUE)
    {
      wrote_ret = wrote;
    }
    return wrote_ret;
}

int octave_serial::set_timeout(short timeout)
{
    if (!this->fd_is_valid())
    {
        error("serial: Interface must be opened first...");
        return -1;
    }

    if (timeout < -1 || timeout > 255)
    {
        error("srl_timeout: timeout value must be between [-1..255]...");
        return -1;
    }

    // Disable custom timeout, enable blocking read
    if (timeout < 0)
    {
        this->blocking_read = true;
        timeout = 5;
    }
    // Enable custom timeout, disable blocking read
    else
    {
        this->blocking_read = false;
    }

    this->timeouts.ReadIntervalTimeout = MAXDWORD;
    this->timeouts.ReadTotalTimeoutMultiplier = 0;
    this->timeouts.ReadTotalTimeoutConstant = timeout*100;
    this->timeouts.WriteTotalTimeoutMultiplier = 0;
    this->timeouts.WriteTotalTimeoutConstant = 0;

    if(SetCommTimeouts(this->fd, &this->timeouts) == FALSE)
    {
        error("srl_timeout: error setting timeout...");
        return -1;
    }

    return 1;
}

int octave_serial::get_timeout() const
{
    if (blocking_read)
        return -1;
    else
        return this->timeouts.ReadTotalTimeoutConstant/100;
}

int octave_serial::set_stopbits(unsigned short stopbits)
{
    if (!this->fd_is_valid())
    {
        error("serial: Interface must be opened first...");
        return -1;
    }

    if (stopbits == 1)
    {
        // Set to one stop bit
        this->config.StopBits = ONESTOPBIT;
    }
    else if (stopbits == 2)
    {
        // Set to two stop bits
        this->config.StopBits = TWOSTOPBITS;
    }
    else
    {
        error("srl_stopbits: Only 1 or 2 stop bits are supported...");
        return false;
    }

    if(SetCommState(this->fd,&this->config) == FALSE)
    {
        error("srl_stopbits: error setting stop bits: %s\n", winerror(errno));
        return false;
    }

    return true;
}

int octave_serial::get_stopbits() const
{
    if (!this->fd_is_valid())
    {
        error("serial: Interface must be opened first...");
        return -1;
    }
    if(this->config.StopBits == TWOSTOPBITS)
        return 2;
    else
        return 1;
}

int octave_serial::set_bytesize(unsigned short bytesize)
{
    if (!this->fd_is_valid())
    {
        error("serial: Interface must be opened first...");
        return -1;
    }

    if(bytesize < 5 || bytesize > 8)
    {
        error("srl_bytesize: expecting value between [5..8]...");
        return false;
    }
    this->config.ByteSize = bytesize;

    if(SetCommState(this->fd,&this->config) == FALSE)
    {
        error ("serial: error setting byte size: %s\n", winerror(errno));
        return false;
    }

    return true;
}

int octave_serial::get_bytesize() const
{
    if (!this->fd_is_valid())
    {
        error("serial: Interface must be opened first...");
        return -1;
    }

    return this->config.ByteSize;
}

int octave_serial::set_baudrate(unsigned int baud)
{
    if (!this->fd_is_valid())
    {
        error("serial: Interface must be opened first...");
        return -1;
    }

    DWORD baud_rate;
    // Set a valid baudrate as default
    baud_rate = this->config.BaudRate;
    // List of valid baudrates from 
    // https://msdn.microsoft.com/en-us/library/windows/desktop/aa363214%28v=vs.85%29.aspx
    switch (baud)
    {
      case 110:
        baud_rate = CBR_110; break;
      case 300:
        baud_rate = CBR_300; break;
      case 600:
        baud_rate = CBR_600; break;
      case 1200:
        baud_rate = CBR_1200; break;
      case 2400:
        baud_rate = CBR_2400; break;
      case 4800:
        baud_rate = CBR_4800; break;
      case 9600:
        baud_rate = CBR_9600; break;
      case 14400:
        baud_rate = CBR_14400; break;
      case 19200:
        baud_rate = CBR_19200; break;
      case 38400:
        baud_rate = CBR_38400; break;
      case 57600:
        baud_rate = CBR_57600; break;
      case 115200:
        baud_rate = CBR_115200; break;
      case 128000:
        baud_rate = CBR_128000; break;
      case 256000:
        baud_rate = CBR_256000; break;
      default:
        error ("serial: currently only \
                110, 300, 600, 1200, 2400, 4800, \
                9600, 19200, 38400, 57600, 115200, 128000 \
                and 256000 baud rates are supported...");
        return false;
    }

    this->config.BaudRate = baud_rate;

    if(SetCommState(this->fd,&this->config) == FALSE)
    {
        error ("serial: error setting baud rate: %s\n", winerror(errno));
        return false;
    }

    return true;
}

int octave_serial::get_baudrate() const
{
    if (!this->fd_is_valid())
    {
        error("serial: Interface must be opened first...");
        return -1;
    }

    return this->config.BaudRate;
}

int octave_serial::flush(unsigned short queue_selector)
{
    if (!this->fd_is_valid())
    {
        error("serial: Interface must be opened first...");
        return -1;
    }

    int flag;

    switch (queue_selector)
    {
    case 0: flag = PURGE_TXCLEAR; break;
    case 1: flag = PURGE_RXCLEAR; break;
    case 2: flag = PURGE_RXCLEAR|PURGE_TXCLEAR; break;
    default:
        error("srl_flush: only [0..2] values are accepted...");
        return false;
    }

   if(PurgeComm(this->fd,flag) == FALSE)
     return -1;
   else
     return true;
}


int octave_serial::set_parity(string parity)
{
    if (!this->fd_is_valid())
    {
        error("serial: Interface must be opened first...");
        return -1;
    }

    // Convert string to lowercase
    std::transform(parity.begin(), parity.end(), parity.begin(), ::tolower);

    /*
     * PARENB Enable parity generation on output and parity checking for input.
     * PARODD If set, then parity for input and output is odd; otherwise even parity is used.
     */

    if (parity == "n" || parity == "none")
    {
        // Disable parity generation/checking
        this->config.Parity = NOPARITY;
    }
    else if (parity == "e" || parity == "even")
    {
        // Enable parity generation/checking
        this->config.Parity = EVENPARITY;
    }
    else if (parity == "o" || parity == "odd")
    {
         this->config.Parity = ODDPARITY;
    }
    else
    {
        error("srl_parity: Only [N]one, [E]ven or [O]dd parities are supported...");
        return false;
    }

    if(SetCommState(this->fd,&this->config) == FALSE)
    {
        error("srl_parity: error setting parity: %s\n", winerror(errno));
        return false;
    }

    return true;
}

string octave_serial::get_parity() const
{
    if(this->config.Parity == NOPARITY)
        return "None";
    else if(this->config.Parity == ODDPARITY)
        return "Odd";
    else
        return "Even";
}

void octave_serial::get_control_line_status(void)
{
    if (!this->fd_is_valid())
    {
      error("serial: Interface must be opened first...");
      return;
    }

    GetCommState (this->fd, &this->config);
    GetCommModemStatus (this->fd, &this->status);
}

bool octave_serial::get_control_line(string control_signal)
{
    get_control_line_status ();

    if (control_signal == "DTR")
        return (this->config.fDtrControl == DTR_CONTROL_ENABLE);
    else if (control_signal == "RTS")
        return (this->config.fRtsControl == RTS_CONTROL_ENABLE);
    else if (control_signal == "CTS")
        return (this->status & MS_CTS_ON);
    else if (control_signal == "DSR")
        return (this->status & MS_DSR_ON);
    else if (control_signal == "CD")
        return (this->status & MS_RLSD_ON);
    else if (control_signal == "RI")
        return (this->status & MS_RING_ON);
    else
        error("serial: Unknown control signal...");
    return false;

}

void octave_serial::set_control_line(string control_signal, bool set)
{

    get_control_line_status ();

    int signal;

    if (control_signal == "DTR")
    {
        if(set)
          this->config.fDtrControl = DTR_CONTROL_ENABLE;
        else
          this->config.fDtrControl = DTR_CONTROL_DISABLE;
    }
    else if (control_signal == "RTS")
    {
        if(set)
          this->config.fRtsControl = RTS_CONTROL_ENABLE;
        else
          this->config.fRtsControl = RTS_CONTROL_DISABLE;
    }
    else
    {
        error("serial: Unknown control signal...");
        return;
    }

    SetCommState(this->fd,&this->config);
}

bool octave_serial::fd_is_valid() const
{
  return (this->fd != INVALID_HANDLE_VALUE);
}

void octave_serial::close()
{
  if (this->fd_is_valid())
    {
      CloseHandle(this->fd);
      this->fd = INVALID_HANDLE_VALUE;
    }
}
#endif
