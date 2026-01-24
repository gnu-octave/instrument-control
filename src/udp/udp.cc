// Copyright (C) 2016-2019 John Donoghue   <john.donoghue@ieee.org>
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

#ifdef BUILD_UDP
#  include "udp_class.h"
#endif

// PKG_ADD: autoload ("udp", "udp.oct");
DEFUN_DLD (udp, args, nargout,
        "-*- texinfo -*-\n\
@deftypefn {} {@var{udp} = } udp ()\n \
@deftypefnx {} {@var{udp} = } udp (@var{remoteipaddress}, @var{remoteport})\n \
@deftypefnx {} {@var{udp} = } udp (@var{remoteipaddress}, @var{remoteport}, [@var{propertyname}, @var{propertyvalue} ...])\n \
\n\
Open udp interface.\n \
\n\
@subsubheading Inputs\n \
@var{remoteipaddress} - the ip address of type String. If omitted defaults to '127.0.0.1'.@* \n \
@var{remoteport} - the port number to connect. If omitted defaults to 23.@* \n \
@var{localport} - the local port number to bind. If omitted defaults to 0@* \n \
@var{propertyname}, @var{propertyvalue} - property name/value pair\n \
\n\
@subsubheading Outputs\n \
The udp() shall return instance of @var{octave_udp} class as the result @var{udp}.\n \
\n \
@subsubheading Properties\n \
The udp object has the following public properties:\n \
@table @asis\n \
@item name\n \
name assigned to the udp object\n \
@item type\n \
instrument type 'udp' (readonly)\n \
@item localport\n \
local port number (readonly)\n \
@item localhost\n \
local host address (readonly)\n \
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
#ifndef BUILD_UDP
  error("udp: Your system doesn't support the UDP interface");
  return octave_value();
#else
  // Do not open interface if return value is not assigned
  if (nargout != 1)
    {
      print_usage();
      return octave_value();
    }

  // Default values
  std::string name = "";
  std::string address("127.0.0.1");
  int port = 23;
  double timeout = -1;
  int localport = 0;

  // Parse the function arguments
  if (args.length() > 0)
    {
      if (args(0).is_string())
        {
          address = args(0).string_value();
        }
      else
        {
          print_usage();
          return octave_value();
        }

    }

  // is_float_type() is or'ed to allow expression like ("", 123), without user
  // having to use ("", int32(123)), as we still only take "int_value"
  if (args.length() > 1)
    {
      if (args(1).OV_ISINTEGER() || args(1).OV_ISFLOAT())
        {
          port = args(1).int_value();
        }
      else
        {
          print_usage();
          return octave_value();
        }
    }

  if (args.length() > 2 && ((args.length() & 1)  == 1))
    {
      error ("Expected property name/value pairs");
      return octave_value ();
    }

  if (args.length() > 2)
    {
      // go through the properties
      for(int i=2;i<args.length();i+=2)
        {
          if (!args(i).is_string())
	    {
              error ("Expected property name as a string");
	      return octave_value ();
	    }
          std::string pname = args(i).string_value();
          octave_value pval = args(i+1);

          std::transform (pname.begin (), pname.end (), pname.begin (), ::tolower);

          if (pname == "localport")
            {
              if (pval.OV_ISINTEGER () || pval.OV_ISFLOAT ())
                localport = pval.int_value ();
              else
                {
                  error ("localport must be a integer");
                  return octave_value();
                }
	    }
          else if (pname == "timeout")
            {
              if (pval.OV_ISINTEGER () || pval.OV_ISFLOAT ())
                timeout = pval.double_value ();
              else
                {
                  error ("timeout must be a integer or double");
                  return octave_value();
                }
	    }
          else if (pname == "name")
            {
              if (pval.is_string ())
                name = pval.string_value ();
              else
                {
                  error ("name must be a string");
                  return octave_value();
                }
	    }
          else
            {
              error ("unknown property '%s'", pname.c_str());
              return octave_value();
            }
        }
    }

  // Open the interface and connect
  octave_udp* retval = new octave_udp();

  if (retval->open(address, port, localport) < 0)
    {
      return octave_value();
    }

  retval->set_timeout(timeout);

  if(name.length() > 0)
    retval->set_name(name);

  return octave_value(retval);
#endif
}
#if 0
%!test
%! # can create default udp object
%! a = udp ();
%! assert (! isnull (a));
%! assert (isa (a, 'octave_udp'));
%! udp_close (a);

%!error <Invalid call to udp> a = udp (1)

%!error <Expected property name/value pairs> a = udp ("127.0.0.1", 23, 0)

%!error <Expected property name as a string> a = udp ("127.0.0.1", 23, 0, 0)

%!test
%! a = udp ('127.0.0.1', 23);
%! assert (! isnull (a));
%! udp_close (a);

%!test
%! a = udp ('127.0.0.1', 23, "name", "test", "timeout", 2.5);
%! assert (! isnull (a));
%! assert (a.name, "test");
%! assert (a.timeout, 2.5);
%! udp_close (a);

%!error <Invalid call to udp> udp ('127.0.0.1', 23,0,0,0)
#endif
