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
#include "tcpclient_class.h"
#endif

// PKG_ADD: autoload ("__tcpclient_write__", "tcpclient.oct");
DEFUN_DLD (__tcpclient_write__, args, nargout,
        "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{n} = } __tcpclient_write__ (@var{tcpclient}, @var{data})\n \
\n\
Private function to write data to a tcpclient interface.\n \
\n\
@subsubheading Inputs\n \
@var{tcpclient} - instance of @var{octave_tcpclient} class.@* \
@var{data} - data to be written to the tcpclient interface. Can be either of String or uint8 type.\n \
\n\
@subsubheading Outputs\n \
Upon successful completion, __tcpclient_write__() shall return the number of bytes written as the result @var{n}.\n \
@end deftypefn")
{
#ifndef BUILD_TCP
  error("tcpclient: Your system doesn't support the TCP interface");
  return octave_value ();
#else
  if (args.length () != 2 || args (0).type_id () != octave_tcpclient::static_type_id ())
    {
      print_usage ();
      return octave_value (-1);
    }

  octave_tcpclient *tcpclient = NULL;
  int retval;

  const octave_base_value& rep = args (0).get_rep ();
  tcpclient = &((octave_tcpclient &)rep);

  if (args (1).is_string ()) // String
    {
      retval = tcpclient->write (args (1).string_value ());
    }
  else if (args (1).is_uint8_type ())
    {
      NDArray data = args (1).array_value ();
      OCTAVE_LOCAL_BUFFER (uint8_t, buf, (data.numel ()));

      // memcpy?
      if (buf == NULL)
        {
          error ("tcpclient_write: cannot allocate requested memory");
          return octave_value (-1);
        }

      for (int i = 0; i < data.numel (); i++)
        buf[i] = static_cast<uint8_t>(data(i));

      retval = tcpclient->write (buf, data.numel ());

    }
  else
    {
      print_usage ();
      return octave_value (-1);
    }

  return octave_value (retval);
#endif
}

#if 0
%!error <Invalid call to __tcpclient_write> __tcpclient_write__(1, uint8([104  101  108  108  111]))

%!error <Invalid call to __tcpclient_write__> __tcpclient_write__()

%!test
%! addr = resolvehost ('gnu.org', 'address');
%! a = tcpclient (addr, 80);;
%! # call HTTP HEAD
%! req = "HEAD / HTTP/1.1\r\n\r\n";
%! assert (length (req), __tcpclient_write__ (a, req));
%! [d, c] = __tcpclient_read__ (a, 12, 5000);
%! clear a
%! assert (12, c);
%! assert (c, length (d));
#endif

