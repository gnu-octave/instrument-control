// Copyright (C) 2022   John Donoghue   <john.donoghue@ieee.org>
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
#include <octave/Matrix.h>

#ifdef HAVE_CONFIG_H
#  include "../config.h"
#endif

#ifdef BUILD_TCP
#  include "tcpserver_class.h"
#endif

// PKG_ADD: autoload ("tcpserver", "tcpserver.oct");
DEFUN_DLD (tcpserver, args, nargout,
        "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{tcpserver} = } tcpserver (@var{ipaddress}, @var{port})\n \
@deftypefnx {Loadable Function} {@var{tcpserver} = } tcpserver (@var{port})\n \
@deftypefnx {Loadable Function} {@var{tcpserver} = } tcpserver (@dots{}, [@var{propertyname}, @var{propertyvalue}])\n \
\n\
Open tcpserver interface.\n \
\n\
@subsubheading Inputs\n \
@var{ipaddress} - the ip address of type String.@* \
@var{port} - the port number to bind.@* \
@var{propname},@var{propvalue} - property name/value pairs.\n \
\n \
Known input properties:\n \
@table @asis\n \
@item Name\n \
name value\n \
@item Timeout\n \
Numeric timeout value or -1 to wait forever\n \
@item UserData\n \
User data value.\n \
@end table\n \
\n\
@subsubheading Outputs\n \
The tcpserver() shall return instance of @var{octave_tcpserver} class as the result @var{tcpserver}.\n \
\n \
@subsubheading Properties\n \
The tcpserver object has the following public properties:\n \
@table @asis\n \
@item Connected\n \
boolean flag for when connected to a client (Readonly)\n \
@item ClientPort\n \
connected client port number (Readonly)\n \
@item ClientAddress\n \
connected client address (Readonly)\n \
@item Name\n \
name assigned to the tcpserver object\n \
@item Type\n \
instrument type 'tcpserver' (readonly)\n \
@item ServerPort\n \
server port number (Readonly)\n \
@item ServerAddress\n \
server address (Readonly)\n \
@item Status\n \
status of the object 'open' or 'closed' (readonly)\n \
@item Timeout\n \
timeout value in seconds used for waiting for data\n \
@item NumBytesAvailable\n \
number of bytes currently available to read (readonly)\n \
@item NumBytesWritten\n \
number of bytes currently available to read (readonly)\n \
@item ByteOrder\n \
Byte order  for data (currently not used)\n \
@item Terminator\n \
Terminator value used for string data (currently not used)\n \
@item UserData\n \
User data\n \
@end table \n \
@end deftypefn")
{
#ifndef BUILD_TCP
  error("tcpserver: Your system doesn't support the TCP interface");
  return octave_value ();
#else
  // Do not open interface if return value is not assigned
  if (nargout != 1)
    {
      print_usage ();
      return octave_value ();
    }

  // Default values
  std::string address ("");
  std::string name = "";
  int port = 23;
  double timeout = -1;
  octave_value userdata = Matrix();

  int property_start = -1;

  // Parse the function arguments - needs at least 1 arg
  if (args.length () < 1)
    {
      print_usage ();
      return octave_value ();
    }

  // either first arg is an address, or a port to user
  if (args (0).is_string ())
    {
      address = args (0).string_value ();

      if (args.length() < 2)
        {
          error ("Expected port after address");
          return octave_value ();
        }
      else if (args (1).OV_ISINTEGER () || args (1).OV_ISFLOAT ())
        {
          port = args (1).int_value ();
        }
      else
        {
          error ("Expected port as a number");
          return octave_value ();
        }
      property_start = 2;
    }
  else if (args (0).OV_ISINTEGER () || args (0).OV_ISFLOAT ())
    {
      port = args (0).int_value ();
      property_start = 1;
    }
  else
    {
      error ("Expected address as a string or port number");
      return octave_value ();
    }

  // properties
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

  // Open the interface and connect
  octave_tcpserver* retval = new octave_tcpserver ();

  if (retval->open (address, port) < 0)
    {
      return octave_value ();
    }

  retval->set_timeout (timeout);

  //retval->flush (2);
  if (name.length() > 0)
    retval->set_name (name);

  retval->set_userdata (userdata);

  return octave_value (retval);
#endif
}

#if 0
%!test
%! a = tcpserver ("", 0);
%! assert (! isnull (a));
%! assert (isa (a, 'octave_tcpserver'));
%! clear a

%!test
%! a = tcpserver (0);
%! assert (! isnull (a));
%! assert (isa (a, 'octave_tcpserver'));
%! clear a

%!test
%! a = tcpserver (0, 'Name', 'test', 'Timeout', 2.5);
%! assert (! isnull (a));
%! assert (isa (a, 'octave_tcpserver'));
%! assert (get(a, 'Name'), 'test');
%! assert (get(a, 'Timeout'), 2.5);
%! clear a

%!error <Invalid call to tcpserver> tcpserver (1, 1)

%!error <Invalid call to tcpserver> tcpserver ('127.0.0.1', '80')

%!error <Invalid call to tcpserver> tcpserver ('127.0.0.1', 80, 'prop1')

#endif
