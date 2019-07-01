// Copyright (C) 2019   John Donoghue   <john.donoghue@ieee.org>
// Copyright (C) 2017   John Donoghue   <john.donoghue@ieee.org>
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

// TODO: Implement Flow Control
// TODO: Implement H/W handshaking

#include <octave/oct.h>

#ifdef HAVE_CONFIG_H
#include "../config.h"
#endif

#ifdef BUILD_SERIAL
#include <errno.h>
#include <fcntl.h>

#include "serial_class.h"

#endif

// PKG_ADD: autoload ("serial", "serial.oct");
DEFUN_DLD (serial, args, nargout, 
        "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{serial} = } serial ([@var{path}], [@var{baudrate}], [@var{timeout}])\n \
\n\
Open serial interface.\n \
\n\
@subsubheading Inputs\n \
@var{path} - the interface path of type String. @*\
@var{baudrate} - the baudrate of interface. If omitted defaults to 115200. @*\
@var{timeout} - the interface timeout value. If omitted defaults to blocking call.\n \
\n\
@subsubheading Outputs\n \
The serial() shall return instance of @var{octave_serial} class as the result @var{serial}.\n \
@subsubheading Properties\n \
The serial object has the following public properties:\n \
@table @asis\n \
@item name\n \
name assigned to the object\n \
@item type\n \
instrument type 'serial' (readonly)\n \
@item port\n \
OS specific port name (readonly)\n \
@item status\n \
status of the object 'open' or 'closed' (readonly)\n \
@item timeout\n \
timeout value used for waiting for data\n \
@item bytesavailable\n \
number of bytes currently available to read (readonly)\n \
@item stopbits\n \
number of stopbits to use\n \
@item requesttosend\n \
request to send state - 'on' or 'off'\n \
@item parity\n \
Parity setting 'none', 'even', 'odd'\n \
@item bytesize\n \
Number of bits to a byte (7 or 8)\n \
@item baudrate\n \
Baudrate setting\n \
@item dataterminalready\n \
state of dataterminal ready - 'on' or 'off'\n \
@item pinstatus\n \
current state of pins (readonly)\n \
@end table \n \
@end deftypefn")
{
#ifndef BUILD_SERIAL
  error ("serial: Your system doesn't support the SERIAL interface");
  return octave_value ();
#else
  // Do not open interface if return value is not assigned
  if (nargout != 1)
    {
        print_usage ();
        return octave_value ();
    }

  // Default values
  std::string path;
  unsigned int baud_rate = 115200;
  short timeout = -1;

  unsigned short bytesize = 8;
  std::string parity("N");
  unsigned short stopbits = 1;
  // Parse the function arguments
  if ((args.length () == 0) || !args(0 ).is_string ())
    {
      print_usage ();
      return octave_value ();
    }

  path = args (0).string_value ();

  // isfloat() is or'ed to allow expression like ("", 123), without user
  // having to use ("", int32(123)), as we still only take "int_value"
  if (args.length() > 1)
    {
      if (args (1).OV_ISINTEGER () || args (1).OV_ISFLOAT ())
        {
          baud_rate = args (1).int_value ();
        }
        else
        {
          print_usage ();
          return octave_value ();
        }
    }

  if (args.length () > 2)
    {
      if (args (2).OV_ISINTEGER () || args (2).OV_ISFLOAT ())
        {
          timeout = args (2).int_value ();
        }
      else
        {
          print_usage ();
          return octave_value ();
        }
    }


  octave_serial* retval = new octave_serial ();

  // Open the interface
  retval->open (path);

  retval->set_baudrate (baud_rate);
  retval->set_timeout (timeout);
  retval->set_parity (parity);
  retval->set_bytesize (bytesize);
  retval->set_stopbits (stopbits);

  //retval->flush (2);

  return octave_value (retval);
#endif
}

#if 0
%!test
%! if any(strcmp(instrhwinfo().SupportedInterfaces, "serial"))
%!   fail ("serial ()", "Invalid call to serial");
%! else
%!   fail ("serial ()", "serial: Your system doesn't support the serial interface");
%! endif

#endif
