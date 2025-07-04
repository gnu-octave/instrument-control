// Copyright (C) 2017   John Donoghue   <john.donoghue@ieee.org>
// Copyright (C) 2013   Stefan Mahr     <dac922@gmx.de>
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
#  include "../config.h"
#endif

#ifdef BUILD_TCP
#  include "tcp_class.h"
#endif

// PKG_ADD: autoload ("tcp", "tcp.oct");
DEFUN_DLD (tcp, args, nargout,
        "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{tcp} = } tcp ()\n \
@deftypefnx {Loadable Function} {@var{tcp} = } tcp (@var{ipaddress})\n \
@deftypefnx {Loadable Function} {@var{tcp} = } tcp (@var{ipaddress}, @var{port})\n \
@deftypefnx {Loadable Function} {@var{tcp} = } tcp (@var{ipaddress}, @var{port}, @var{timeout})\n \
@deftypefnx {Loadable Function} {@var{tcp} = } tcp (@var{ipaddress}, [@var{propertyname}, @var{propertyvalue}])\n \
@deftypefnx {Loadable Function} {@var{tcp} = } tcp (@var{ipaddress}, @var{port}, [@var{propertyname}, @var{propertyvalue}])\n \
\n\
Open tcp interface.\n \
\n\
@subsubheading Inputs\n \
@var{ipaddress} - the ip address of type String. If omitted defaults to '127.0.0.1'.@* \
@var{port} - the port number to connect. If omitted defaults to 23.@* \
@var{timeout} - the interface timeout value. If omitted defaults to blocking call.@*\n \
@var{propname},@var{propvalue} - property name/value pairs.\n \
\n \
Known input properties:\n \
@table @asis\n \
@item name\n \
name value\n \
@item timeout\n \
Numeric timeout value or -1 to wait forever\n \
@end table\n \
\n\
@subsubheading Outputs\n \
The tcp() shall return instance of @var{octave_tcp} class as the result @var{tcp}.\n \
@subsubheading Properties\n \
The tcp object has the following public properties:\n \
@table @asis\n \
@item name\n \
name assigned to the tcp object\n \
@item type\n \
instrument type 'tcp' (readonly)\n \
@item localport\n \
local port number (readonly)\n \
@item remoteport\n \
remote port number\n \
@item remotehost\n \
remote host\n \
@item status\n \
status of the object 'open' or 'closed' (readonly)\n \
@item timeout\n \
timeout value in seconds used for waiting for data\n \
@item bytesavailable\n \
number of bytes currently available to read (readonly)\n \
@end table \n \
@end deftypefn")
{
#ifndef BUILD_TCP
  error("tcp: Your system doesn't support the TCP interface");
  return octave_value ();
#else
  // Do not open interface if return value is not assigned
  if (nargout != 1)
    {
      print_usage ();
      return octave_value ();
    }

  // Default values
  std::string address ("127.0.0.1");
  std::string name = "";
  int port = 23;
  double timeout = -1;


  // Parse the function arguments
  if (args.length () > 0)
    {
      if (args (0).is_string ())
        {
          address = args (0).string_value ();
        }
      else
        {
          print_usage ();
          return octave_value ();
        }
    }

  // is_float_type() is or'ed to allow expression like ("", 123), without user
  // having to use ("", int32(123)), as we still only take "int_value"
  int property_start = -1;
  if (args.length () > 1)
    {
      if (args (1).OV_ISINTEGER () || args (1).OV_ISFLOAT ())
        {
          port = args (1).int_value ();
        }
      else
        {
          property_start = 1;
        }
    }

  if (args.length () > 2 && property_start == -1)
    {
      if (args (2).OV_ISINTEGER () || args (2).OV_ISFLOAT ())
        {
          timeout = args (2).int_value ();
        }
      else
        {
          property_start = 2;
        }
    }

  if (args.length () > 3 && property_start == -1)
    {
       property_start = 2;
    }

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
          else
            {
              error ("unknown property '%s'", propname.c_str ());
              return octave_value ();
            }
        }

    }

  // Open the interface and connect
  octave_tcp* retval = new octave_tcp ();

  if (retval->open (address, port) < 0)
    {
      return octave_value ();
    }

  retval->set_timeout (timeout);

  //retval->flush (2);
  if (name.length() > 0)
    retval->set_name (name);

  return octave_value (retval);
#endif
}

#if 0
%!test
%! addr = resolvehost ('gnu.org', 'address');
%! a = tcp (addr, 80);
%! assert (! isnull (a));
%! assert (isa (a, 'octave_tcp'));
%! tcp_close (a);

%!test
%! addr = resolvehost ('gnu.org', 'address');
%! a = tcp (addr, 80, 'name', 'test', 'timeout', 2.5);
%! assert (! isnull (a));
%! assert (isa (a, 'octave_tcp'));
%! assert (get(a, 'name'), 'test');
%! assert (get(a, 'timeout'), 2.5);
%! tcp_close (a);

%!error <Invalid call to tcp> tcp (1)

%!error <Invalid call to tcp> tcp (1, 1)

%!error <Invalid call to tcp> tcp ('127.0.0.1', '80', 'prop1')

#endif
