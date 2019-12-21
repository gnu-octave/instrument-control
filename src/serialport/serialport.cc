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

#include "serialport_class.h"

#endif

// PKG_ADD: autoload ("serialport", "serialport.oct");
DEFUN_DLD (serialport, args, nargout, 
        "-*- texinfo -*-\n \
@deftypefn {Loadable Function} {@var{serial} = } serialport ([@var{path}], [@var{baudrate}])\n \
@deftypefnx {Loadable Function} {@var{serial} = } serialport ([@var{path}], [@var{propname}, @var{propvalue}])\n \
\n\
Open serial port interface.\n \
\n\
@subsubheading Inputs\n \
@var{path} - the interface path of type String. @*\n \
@var{baudrate} - the baudrate of interface.@*\n \
@var{propname},@var{propvalue} - property name/value pairs.\n \
\n \
Known input properties:\n \
@table @asis\n \
@item baudrate\n \
Numeric baudrate value\n \
@item timeout\n \
Numeric timeout value or -1 to wait forever\n \
@end table\n \
\n\
@subsubheading Outputs\n \
The serialport() shall return an instance of @var{octave_serialport} class as the result @var{serial}.\n \
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
@item databits\n \
Number of bits to a byte (5 to 8)\n \
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
  double timeout = -1;
  unsigned short databits = 8;
  std::string parity("N");
  std::string flow("none");
  unsigned short stopbits = 1;
  // Parse the function arguments
  if ((args.length () == 0) || !args(0 ).is_string ())
    {
      print_usage ();
      return octave_value ();
    }

  path = args (0).string_value ();

  baud_rate = 115200;

  // baudrate
  if (args.length() == 2)
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
  else if (args.length() > 2 && (args.length() & 1)  == 0)
    {
      error ("Expected property name/value pairs");
          return octave_value ();
    }
  else if (args.length() > 2)
  {
    // go through the properties
    for(int i=1;i<args.length();i+=2)
    {
      std::string name = args(i).string_value();
      octave_value val = args(i+1);

      std::transform (name.begin (), name.end (), name.begin (), ::tolower);

      if (name == "baudrate")
        {
          if (val.OV_ISINTEGER () || val.OV_ISFLOAT ())
            baud_rate = val.int_value ();
          else
            {
              error ("baudrate must be a integer");
              return octave_value();
            }
	}
      else if (name == "timeout")
        {
          if (val.OV_ISINTEGER () || val.OV_ISFLOAT ())
            timeout = val.double_value ();
          else
            {
              error ("timeout must be a integer or double");
              return octave_value();
            }
	}
      else if (name == "databits")
        {
          if (val.OV_ISINTEGER () || val.OV_ISFLOAT ())
            databits = val.int_value ();
          else
            {
              error ("databits must be a integer");
              return octave_value();
            }
	}
      else if (name == "stopbits")
        {
          if (val.OV_ISINTEGER () || val.OV_ISFLOAT ())
            stopbits = val.int_value ();
          else
            {
              error ("databits must be a integer");
              return octave_value();
            }
	}
      else if (name == "parity")
        {
          if (val.is_string ())
            parity = val.string_value ();
          else
            {
              error ("parity must be a string");
              return octave_value();
            }
	}
      else if (name == "flowcontrol")
        {
          if (val.is_string ())
            flow = val.string_value ();
          else
            {
              error ("flowcontrol must be a string");
              return octave_value();
            }
	}
      else
        {
          error ("unknown property '%s'", name.c_str());
          return octave_value();
        }
    }
  }

  octave_serialport* retval = new octave_serialport ();

  // Open the interface
  retval->open (path);

  retval->set_baudrate (baud_rate);
  retval->set_timeout (timeout);
  retval->set_parity (parity);
  retval->set_flowcontrol (flow);
  retval->set_databits (databits);
  retval->set_stopbits (stopbits);

  //retval->flush (2);

  return octave_value (retval);
#endif
}

#if 0
%!test
%! if any(strcmp(instrhwinfo().SupportedInterfaces, "serial"))
%!   fail ("serialport ()", "Invalid call to serial");
%! else
%!   fail ("serialport ()", "serial: Your system doesn't support the serial interface");
%! endif
#endif
