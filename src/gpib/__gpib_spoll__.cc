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

#ifdef BUILD_GPIB
#include <errno.h>

#include "gpib_class.h"

#endif


// PKG_ADD: autoload ("__gpib_spoll__", "gpib.oct");
DEFUN_DLD (__gpib_spoll__, args, nargout,
        "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{sb} = } __gpib_spoll__ (@var{gpib})\n \
\n\
serial poll gpib interface.\n \
\n\
@var{gpib} - instance of @var{octave_gpib} class.@*\
\n\
Upon successful completion, gpib_spoll() shall return the status byte @var{sb}.\n \
@end deftypefn")
{
#ifndef BUILD_GPIB
  error ("gpib: Your system doesn't support the GPIB interface");
  return octave_value ();
#else
  if (args.length () != 1 || args (0).type_id () != octave_gpib::static_type_id ())
    {
      print_usage ();
      return octave_value (-1);
    }

  octave_gpib* gpib = NULL;
  int retval;

  const octave_base_value& rep = args (0).get_rep ();
  gpib = &((octave_gpib &)rep);

  char rqs;

  retval = gpib->spoll (&rqs);
  if (retval == -1)
    return octave_value ();

  return octave_value (rqs);

#endif
}
