// Copyright (C) 2016,2017 John Donoghue   <john.donoghue@ieee.org>
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
@deftypefn {Loadable Function} {@var{udp} = } udp ([@var{remoteipaddress}], [@var{remoteport}], [@var{localport}], [@var{timeout}])\n \
\n\
Open udp interface.\n \
\n\
@var{remoteipaddress} - the ip address of type String. If omitted defaults to '127.0.0.1'.@* \
@var{remoteport} - the port number to connect. If omitted defaults to 23.@* \
@var{localport} - the local port number to bind. If omitted defaults to 0@* \
@var{timeout} - the interface timeout value. If omitted defaults to blocking call.\n \
\n\
The udp() shall return instance of @var{octave_udp} class as the result @var{udp}.\n \
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
  std::string address("127.0.0.1");
  int port = 23;
  int timeout = -1;
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

  if (args.length() > 2)
    {
      if (args(2).OV_ISINTEGER() || args(2).OV_ISFLOAT())
        {
          localport = args(2).int_value();
        }
      else
        {
          print_usage();
          return octave_value();
        }
    }

  if (args.length() > 3)
    {
      if (args(3).OV_ISINTEGER() || args(3).OV_ISFLOAT())
        {
          timeout = args(3).int_value();
        }
      else
        {
          print_usage();
          return octave_value();
        }
    }

  // Open the interface and connect
  octave_udp* retval = new octave_udp();

  if (retval->open(address, port, localport) < 0)
    {
      return octave_value();
    }

  retval->set_timeout(timeout);

  //retval->flush(2);

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

%!error <Invalid call to udp> udp (1)

%!test
%! a = udp ('127.0.0.1', 23, 0, 0);
%! assert (! isnull (a));
%! udp_close (a);

%!error <Invalid call to udp> udp ('127.0.0.1', 23,0,0,0)
#endif
