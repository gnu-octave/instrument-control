// Copyright (C) 2017,2019   John Donoghue   <john.donoghue@ieee.org>
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

#ifdef BUILD_PARALLEL
#include "parallel_class.h"

#endif

// PKG_ADD: autoload ("pp_ctrl", "parallel.oct");
DEFUN_DLD (pp_ctrl, args, nargout, 
"-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} pp_ctrl (@var{parallel}, @var{ctrl})\n \
@deftypefnx {Loadable Function} {@var{c} = } pp_ctrl (@var{parallel})\n \
\n\
Sets or Read the Control lines.\
\n\
@subsubheading Inputs\n \
@var{parallel} - instance of @var{octave_parallel} class.@*\
@var{ctrl} - control parameter to be set of type Byte.\n \
\n\
@subsubheading Outputs\n \
If @var{ctrl} parameter is omitted, the pp_ctrl() shall return current Control lines state as the result @var{c}.\n \
@end deftypefn")
{
#ifndef BUILD_PARALLEL
  error ("parallel: Your system doesn't support the parallel interface");
  return octave_value();
#else
  if (args.length () < 1 || args.length () > 2 || args (0).type_id () != octave_parallel::static_type_id ())
    {
      print_usage ();
      return octave_value (-1);
    }

  octave_parallel* parallel = NULL;

  const octave_base_value& rep = args (0).get_rep ();
  parallel = &((octave_parallel &)rep);

  // Set new Control register value
  if (args.length () > 1)
    {
      if ( !(args (1).OV_ISINTEGER () || args(1).OV_ISFLOAT ()) )
        {
          print_usage ();
          return octave_value (-1);
        }

        parallel->set_ctrl (args (1).int_value ());

        return octave_value ();
    }

  // Return current Control register value on port
  return octave_value (parallel->get_ctrl ());
#endif
}
#if 0
%!xtest
%! if any (strcmp(instrhwinfo().SupportedInterfaces, "parallel"))
%!   a = parallel ();
%!   v = pp_ctrl(a);
%!   pp_close (a);
%! endif

%!test
%! if any (strcmp(instrhwinfo().SupportedInterfaces, "parallel"))
%!   fail ("pp_ctrl(1);", "Invalid call to pp_ctrl");
%! endif
#endif
