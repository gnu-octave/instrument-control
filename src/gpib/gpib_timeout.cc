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
#include "../config.h"
#endif

#ifdef BUILD_GPIB

#include "gpib_class.h"

#endif

// PKG_ADD: autoload ("gpib_timeout", "gpib.oct");
DEFUN_DLD (gpib_timeout, args, nargout,
        "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} gpib_timeout (@var{gpib}, @var{timeout})\n \
@deftypefnx {Loadable Function} {@var{t} = } gpib_timeout (@var{gpib})\n \
\n\
Set new or get existing gpib interface timeout parameter. The timeout value is valid from 0 to 17.\n \
\n\
@var{gpib} - instance of @var{octave_gpib} class.@* \
@var{timeout} - Value of 0 means never timeout, 11 means one second and 17 means 1000 seconds (see GPIB documentation (ibtmo) for further details)\n \
\n\
If @var{timeout} parameter is omitted, the gpib_timeout() shall return current timeout value as the result @var{t}.\n \
@end deftypefn")
{
#ifndef BUILD_GPIB
  error ("gpib: Your system doesn't support the GPIB interface");
  return octave_value();
#else
  if (args.length () < 1 || args.length () > 2 || args (0).type_id () != octave_gpib::static_type_id ())
    {
      print_usage ();
      return octave_value (-1);
    }

  octave_gpib* gpib = NULL;

  const octave_base_value& rep = args (0).get_rep ();
  gpib = &((octave_gpib &)rep);

  // Setting new timeout
  if (args.length () > 1)
    {
      if ( !(args (1).OV_ISINTEGER () || args (1).OV_ISFLOAT ()) )
        {
          print_usage ();
          return octave_value (-1);
        }

      gpib->set_timeout (args (1).int_value ());

      return octave_value (); // Should it return by default?
    }

  // Returning current timeout
  return octave_value (gpib->get_timeout ());
#endif
}
