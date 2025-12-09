// Copyright (C) 2021 John Donoghue   <john.donoghue@ieee.org>
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
#include <octave/uint8NDArray.h>

#include <errno.h>

#include "udpport_class.h"

#endif

// PKG_ADD: autoload ("__udpport_read__", "udpport.oct");
DEFUN_DLD (__udpport_read__, args, nargout,
        "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {[@var{data}, @var{count}] = } __udpport_read__ (@var{udpport}, @var{n}, @var{timeout})\n \
@deftypefnx {Loadable Function} {[@var{data}, @var{count}. @var{srcip}, @var{srcport}] = } __udpport_read__ (@var{udpport}, @var{n}, @var{timeout})\n \
\n\
Provate function to read from udpport interface.\n \
\n\
@subsubheading Inputs\n \
@var{udpport} - instance of @var{octave_udpport} class.@* \
@var{n} - number of bytes to attempt to read of type Integer@* \n \
@var{timeout} - timeout in ms if different from default of type Integer\n \
\n\
@subsubheading Outputs\n \
The __udpport_read__() shall return number of bytes successfully read in @var{count} as Integer and the bytes themselves in @var{data} as uint8 array.\n \
Optional outputs are provided for the source ip address and port of the read data.\n \
@end deftypefn")
{
#ifndef BUILD_UDP
  error("udpport: Your system doesn't support the UDP interface");
  return octave_value();
#else

  if (args.length() < 2 || args.length() > 3 || args(0).type_id() != octave_udpport::static_type_id())
    {
      print_usage();
      return octave_value(-1);
    }

  unsigned int buffer_len = 0;
  sockaddr_in addr;

  if ( !(args(1).OV_ISINTEGER() || args(1).OV_ISFLOAT()))
    {
      print_usage();
      return octave_value(-1);
    }

  if ( args.length() > 2 )
    {
      if ( !(args(2).OV_ISINTEGER() || args(2).OV_ISFLOAT()))
        {
          print_usage();
          return octave_value(-1);
        }
    }

  buffer_len = args(1).int_value();

  OCTAVE_LOCAL_BUFFER (uint8_t, buffer, (buffer_len + 1));

  if (buffer == NULL)
    {
      error("udpport_read: cannot allocate requested memory: %s\n", strerror(errno));
      return octave_value(-1);
    }

  octave_udpport* udpport = NULL;

  const octave_base_value& rep = args(0).get_rep();
  udpport = &((octave_udpport &)rep);

  double timeout = udpport->get_timeout() * 1000;
  if (args.length() == 3)
    {
      timeout = args(2).double_value();
    }

  // Read data
  int bytes_read = udpport->read(buffer, buffer_len, timeout, &addr);

  // Convert data to octave type variables
  octave_value_list return_list;
  uint8NDArray data( dim_vector(1, bytes_read) );

  for (int i = 0; i < bytes_read; i++)
    data(i) = buffer[i];

  return_list(0) = data;
  return_list(1) = bytes_read;

  if (nargout > 2)
    {
      int port = 0;
      std::string ip = "";

      if  (bytes_read > 0)
        to_ip_port(&addr, ip, port);

      return_list(2) = ip;
      if (nargout > 3)
        return_list(3) = port;
    }

  return return_list;
#endif
}

#if 0
%!test
%! a = udpport ();
%! assert (! isnull (a));
%! [d,c] = __udpport_read__ (a, 1, 0);
%! assert (c == 0);
%! assert (isempty (d));
%! clear a;

%!error <Invalid call to __udpport_read__> __udpport_read__(1, 10, 0)

%!test
%! a = udpport ();
%! fail ("__udpport_read__ (a, 10, 0, 0)", "Invalid call to __udpport_read__");
%! clear a;

%!test
%! # does read wait
%! a = udpport ();
%! assert (! isnull (a));
%! tic;
%! [d,c] = __udpport_read__ (a, 1, 1000);
%! t = toc;
%! assert (c, 0);
%! assert (isempty (d));
%! assert (t >= 1.0)
%! clear a;

#endif
