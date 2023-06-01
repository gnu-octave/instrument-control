// Copyright (C) 2022 John Donoghue   <john.donoghue@ieee.org>
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
#  include "../config.h"
#endif

#ifdef BUILD_MODBUS
#  include "modbus_class.h"
#endif

// PKG_ADD: autoload ("modbus", "modbus.oct");
DEFUN_DLD (modbus, args, nargout,
        "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{dev} = } modbus ('tcpip', @var{deviceaddress})\n \
@deftypefnx {Loadable Function} {@var{dev} = } modbus ('tcpip', @var{deviceaddress}, @var{remoteport})\n \
@deftypefnx {Loadable Function} {@var{dev} = } modbus ('tcpip', @var{deviceaddress}, @var{name}, @var{value})\n \
@deftypefnx {Loadable Function} {@var{dev} = } modbus ('serialrtu', @var{serialport})\n \
@deftypefnx {Loadable Function} {@var{dev} = } modbus ('serialrtu', @var{serialport}, @var{name}, @var{value})\n \
\n\
Open modbus interface using a specified transport of 'tcpip' or 'serialrtu'.\n \
\n\
@subsubheading Inputs\n \
@var{deviceaddress} - the device ip address of type String.@*\n \
@var{remoteport} - the device remote port number. If not specified, a default of 502 will be used.@*\n \
@var{name}, @var{value} - Optional name value pairs for setting properties of the object.@*\n \
@var{serialport} - the name of the serial port to connect to. It must be specified when transport is 'serialrtu'.@*\n \
\n\
@subsubheading Common Input Name, Value pairs\n \
@table @asis\n \
@item Timeout\n \
timeout value used for waiting for data\n \
@item NumRetries\n \
number of retries after a timeout\n \
@item UserData\n \
Additional data to attach to the object\n \
@end table\n \
\n \
@subsubheading Serial RTU Input Name, Value pairs\n \
@table @asis\n \
@item BaudRate\n \
Baudrate for the serial port\n \
@item DataBits\n \
number of databits for serial port\n \
@item Parity\n \
Parity for serial port ('odd', 'even' or 'none')\n \
@item StopBits\n \
number of stopbits for serial port\n \
@end table\n \
\n\
@subsubheading Outputs\n \
The modbus() shall return instance of @var{octave_modbus} class as the result @var{modbus}.\n \
\n \
@subsubheading Properties\n \
The modbus object has the following public properties:\n \
@table @asis\n \
@item Name\n \
name assigned to the modbus object\n \
@item Type\n \
instrument type 'modbus' (readonly)\n \
@item Port\n \
Remote port number or serial port name (readonly)\n \
@item DeviceAddress\n \
Device address if transport was 'tcpip' (readonly)\n \
@item Status\n \
status of the object 'open' or 'closed' (readonly)\n \
@item Timeout\n \
timeout value used for waiting for data\n \
@item NumRetries\n \
number of retries after a timeout\n \
@item UserData\n \
Additional data to attach to the object\n \
@end table \n \
@end deftypefn")
{
#ifndef BUILD_MODBUS
  error("modbus: Your system doesn't support the MODBUS interface");
  return octave_value();
#else
  // Do not open interface if return value is not assigned
  if (nargout != 1)
    {
      print_usage();
      return octave_value();
    }

  // at minumum we need transport and device address or serialport (strings)
  if (args.length() < 2)
    {
      print_usage();
      return octave_value();
    }

  // Default values
  std::string transport("");

  std::string deviceaddress("127.0.0.1");
  int ipport = 502;
  double timeout = 10;
  int numretries = 1;
  std::string name = "";
  octave_value userdata = Matrix ();
  long baudrate = 9600;
  int databits = 8;
  int stopbits = 1;
  std::string parity = "none";

  int property_start = -1;

  if (args(0).is_string())
    {
      transport = args(0).string_value();
    }
  else
    {
      error ("Expected transport of 'serialrtu' or 'tcpip'");
      return octave_value();
    }

  if (transport == "tcpip")
    {
      if (! args(1).is_string())
        {
          error ("Expected deviceaddress as string");
	  return octave_value();
        }
      deviceaddress = args (1).string_value ();

      // optional remote port
      if (args.length () > 2)
        {
          if (args (2).OV_ISINTEGER () || args (2).OV_ISFLOAT ())
            {
              ipport = args (2).int_value ();
            }
          else
            {
              property_start = 2;
            }
        }
    }
  else if(transport == "serialrtu")
    {
      if (! args(1).is_string())
        {
          error ("Expected device port as string");
	  return octave_value();
        }
      deviceaddress = args (1).string_value ();

      property_start = 2;
    }
  else
    {
      error ("Expected transport of 'serialrtu' or 'tcpip'");
      return octave_value();
    }

  // property args
  if (property_start != -1)
    {
       if (((args.length () - property_start) & 1) == 1)
         {
           error ("Expected property name/value pairs");
           return octave_value ();
         }

      // go through the properties
      for(int i=property_start;i<args.length();i+=2)
        {
          std::string propname = args(i).string_value();
          octave_value propval = args(i+1);

          std::transform (propname.begin (), propname.end (), propname.begin (), ::tolower);

          if (propname == "name")
            {
              if (propval.is_string ())
                name = propval.string_value ();
              else
                {
                  error ("name must be a string");
                  return octave_value ();
                }
            }
          else if (propname == "timeout")
            {
              if (propval.OV_ISINTEGER () || propval.OV_ISFLOAT ())
                timeout = propval.double_value ();
              else
                {
                  error ("timeout must be a integer or double");
                  return octave_value ();
                }
            }
          else if (propname == "numretries")
            {
              if (propval.OV_ISINTEGER () || propval.OV_ISFLOAT ())
                {
                  numretries = propval.double_value ();
                  if (numretries < 0)
                    {
                      error ("numretries must be 0 or a positive integer");
                      return octave_value ();
                    }
                }
              else
                {
                  error ("numretries must be a integer or double");
                  return octave_value ();
                }
            }
          else if (propname == "baudrate")
            {
              if (propval.OV_ISINTEGER () || propval.OV_ISFLOAT ())
                {
                  baudrate = propval.long_value ();
                  if (baudrate <= 0)
                    {
                      error ("baudrate must be a positive integer or double");
                      return octave_value ();
                    }
		}
              else
                {
                  error ("baudrate must be a positive integer or double");
                  return octave_value ();
                }
            }
          else if (propname == "databits")
            {
              if (propval.OV_ISINTEGER () || propval.OV_ISFLOAT ())
                {
                  databits = propval.int_value ();
                  if (databits < 5 || databits > 8)
                    {
                      error ("databits must be a between 5-8");
                      return octave_value ();
                    }
		}
              else
                {
                  error ("databits must be a positive integer or double");
                  return octave_value ();
                }
            }
          else if (propname == "stopbits")
            {
              if (propval.OV_ISINTEGER () || propval.OV_ISFLOAT ())
                {
                  stopbits = propval.int_value ();
                  if (stopbits < 1 || stopbits > 2)
                    {
                      error ("stopbits must be 1 or 2");
                      return octave_value ();
                    }
		}
              else
                {
                  error ("stopbits must be 1 or 2");
                  return octave_value ();
                }
            }
	  else if (propname == "parity")
            {
              if (propval.is_string ())
                {
                  parity = propval.string_value ();
                  if (parity != "none" && parity != "odd" && parity != "even")
                    {
                      error ("parity must be 'odd', 'even' or 'none'");
                      return octave_value ();
                    }
                }
              else
                {
                  error ("parity must be a string");
                  return octave_value ();
                }
            }
 
          else if (propname == "userdata")
            {
              userdata = propval;
            }
          else
            {
              error ("unknown property '%s'", propname.c_str ());
              return octave_value ();
            }
        }
    }

  // Open the interface and connect
  octave_modbus* retval = new octave_modbus();

  if (transport == "tcpip")
    {
      if (retval->open_tcp(deviceaddress, ipport) < 0)
        {
          return octave_value();
        }
    }
  else
    {
      if (retval->open_serial(deviceaddress, baudrate, databits, parity, stopbits) < 0)
        {
          return octave_value();
        }
    }

  // set w/r properties we may have
  retval->set_timeout(timeout);
  retval->set_numretries(numretries);
  retval->set_userdata(userdata);
  if (name.length() > 0)
    retval->set_name(name);

  return octave_value(retval);
#endif
}
#if 0
%!error modbus (1)

%!error modbus ('noatransport', '127.0.0.1')
#endif
