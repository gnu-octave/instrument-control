// Copyright (C) 2021   John Donoghue   <john.donoghue@ieee.org>
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

#ifdef BUILD_TCP
#include <octave/uint8NDArray.h>

#include <errno.h>

#include "tcpclient_class.h"

#endif

// PKG_ADD: autoload ("__tcpclient_read__", "tcpclient.oct");
DEFUN_DLD (__tcpclient_read__, args, nargout,
        "-*- texinfo -*-\n\
@deftypefn {} {[@var{data}, @var{count}] = } __tcpclient_read__ (@var{tcpclient}, @var{n}, @var{timeout})\n \
\n\
Private function t read from tcpclient interface.\n \
\n\
@subsubheading Inputs\n \
@var{tcpclient} - instance of @var{octave_tcpclient} class.@* \
@var{n} - number of bytes to attempt to read of type Integer@* \
@var{timeout} - timeout in ms if different from default of type Integer\n \
\n\
@subsubheading Outputs\n \
@var{count} - number of bytes successfully read as an Integer@*\n \
@var{data} - data bytes themselves as uint8 array.\n \
@end deftypefn")
{
#ifndef BUILD_TCP
  error ("tcpclient: Your system doesn't support the TCP interface");
  return octave_value ();
#else

  if (args.length() < 2 || args.length () > 3 || args (0).type_id () != octave_tcpclient::static_type_id ())
    {
      print_usage ();
      return octave_value (-1);
    }

  unsigned int buffer_len = 0;

  if ( !(args (1).OV_ISINTEGER () || args (1).OV_ISFLOAT ()))
    {
      print_usage ();
      return octave_value (-1);
    }

  if ( args.length () > 2 )
    {
      if ( !(args (2).OV_ISINTEGER () || args (2).OV_ISFLOAT ()))
        {
          print_usage ();
          return octave_value (-1);
        }
    }

  buffer_len = args (1).int_value ();

  OCTAVE_LOCAL_BUFFER (uint8_t, buffer, (buffer_len + 1));

  if (buffer == NULL)
    {
      error ("tcpclient_read: cannot allocate requested memory: %s\n", strerror(errno));
      return octave_value (-1);
    }

  octave_tcpclient* tcpclient = NULL;

  const octave_base_value& rep = args (0).get_rep ();
  tcpclient = &((octave_tcpclient &)rep);

  double timeout = tcpclient->get_timeout () * 1000;
  if (args.length () == 3)
    {
      timeout = args (2).double_value ();
    }

  // Read data
  int bytes_read = tcpclient->read (buffer, buffer_len, timeout);

  // Convert data to octave type variables
  octave_value_list return_list;
  uint8NDArray data (dim_vector (1, bytes_read) );

  for (int i = 0; i < bytes_read; i++)
    data(i) = buffer[i];

  return_list(0) = data;
  return_list(1) = bytes_read;

  return return_list;
#endif
}

#if 0
%!test
%! addr = resolvehost ('gnu.org', 'address');
%! a = tcpclient (addr, 80);
%! assert (! isnull (a));
%! # server should be waiting for us to send request
%! fail ("__tcpclient_read__ (a, 10, 0, 0)", "Invalid call to __tcpclient_read__");
%!
%! [d,c] = __tcpclient_read__ (a, 1, 0);
%! assert (0, c);
%! assert (isempty (d));
%!
%! tic;
%! [d,c] = __tcpclient_read__ (a, 1, 1000);
%! t = toc;
%! assert (c, 0);
%! assert (isempty (d));
%! assert (t >= 1.0)
%!
%! clear a

%!error <Invalid call to __tcpclient_read__> __tcpclient_read__ (1)

%!error <Invalid call to __tcpclient_read__> __tcpclient_read__ (1, 10, 0)

#endif
