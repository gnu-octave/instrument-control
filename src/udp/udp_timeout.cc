// Copyright (C) 2017-2019   John Donoghue   <john.donoghue@ieee.org>
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

// PKG_ADD: autoload ("udp_timeout", "udp.oct");
DEFUN_DLD (udp_timeout, args, nargout,
        "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} udp_timeout (@var{udp}, @var{timeout})\n \
@deftypefnx {Loadable Function} {@var{t} = } udp_timeout (@var{udp})\n \
\n\
Set new or get existing udp interface timeout parameter used for udp_read() requests. The timeout value is specified in milliseconds.\n \
\n\
@subsubheading Inputs\n \
@var{udp} - instance of @var{octave_udp} class.@* \
@var{timeout} - udp_read() timeout value in milliseconds. Value of -1 means a blocking call.\n \
\n\
@subsubheading Outputs\n \
If @var{timeout} parameter is omitted, the udp_timeout() shall return current timeout value as the result @var{t}.\n \
@end deftypefn")
{
#ifndef BUILD_UDP
  error("udp: Your system doesn't support the UDP interface");
  return octave_value();
#else
  if (args.length() < 1 || args.length() > 2 || args(0).type_id() != octave_udp::static_type_id())
    {
      print_usage();
      return octave_value(-1);
    }

  octave_udp* udp = NULL;

  const octave_base_value& rep = args(0).get_rep();
  udp = &((octave_udp &)rep);

  // Setting new timeout
  if (args.length() > 1)
    {
      if ( !(args(1).OV_ISINTEGER() || args(1).OV_ISFLOAT()) )
        {
          print_usage();
          return octave_value(-1);
        }

      if(args(1).double_value() >= 0)
        udp->set_timeout(args(1).double_value()/1000.0);
      else
        udp->set_timeout(-1);

      return octave_value(); // Should it return by default?
    }

  // Returning current timeout in ms
  double timeout = udp->get_timeout();
  if(timeout < 0)
    return octave_value(-1);
  else
    return octave_value(timeout*1000.0);
#endif
}

#if 0
%!test
%! a = udp();
%! assert(udp_timeout(a), -1);
%! udp_timeout(a, 103);
%! assert(udp_timeout(a), 103);
%! udp_close(a);

%!test
%! a = udp();
%! assert(udp_timeout(a), -1);
%! a.timeout = 2;
%! assert(udp_timeout(a), 2000);
%! a.timeout = 0;
%! assert(udp_timeout(a), 0);
%! a.timeout = -1;
%! assert(udp_timeout(a), -1);

%!error <Invalid call to udp_timeout> udp_timeout()

%!error <Invalid call to udp_timeout> udp_timeout(1)
#endif
