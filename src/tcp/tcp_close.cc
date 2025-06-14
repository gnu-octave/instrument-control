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
#include "../config.h"
#endif

#ifdef BUILD_TCP
#include "tcp_class.h"
#endif

// PKG_ADD: autoload ("tcp_close", "tcp.oct");
DEFUN_DLD (tcp_close, args, nargout,
"-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} tcp_close (@var{tcp})\n \
\n\
Close the interface and release a file descriptor.\n \
\n\
@subsubheading Inputs\n \
@var{tcp} - instance of @var{octave_tcp} class.\n \
\n \
@subsubheading Outputs\n \
None\n \
@end deftypefn")
{
#ifndef BUILD_TCP
  error ("tcp: Your system doesn't support the TCP interface");
  return octave_value ();
#else

  if (args.length () != 1 || args (0).type_id () != octave_tcp::static_type_id ())
    {
      print_usage ();
      return octave_value (-1);
    }

  octave_tcp* tcp = NULL;

  const octave_base_value& rep = args (0).get_rep ();
  tcp = &((octave_tcp &)rep);

  tcp->close ();

  return octave_value ();
#endif
}
#if 0
%!test
%! addr = resolvehost ('gnu.org', 'address');
%! a = tcp (addr, 80);
%! tcp_close (a);

%!error <Invalid call to tcp_close> tcp_close (1)

%!error <Invalid call to tcp_close> tcp_close ()
#endif
