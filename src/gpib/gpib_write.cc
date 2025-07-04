// Copyright (C) 2018   John Donoghue   <john.donoghue@ieee.org>
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


// PKG_ADD: autoload ("gpib_write", "gpib.oct");
DEFUN_DLD (gpib_write, args, nargout,
        "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{n} = } gpib_write (@var{gpib}, @var{data})\n \
\n\
Write data to a gpib interface.\n \
\n\
@var{gpib} - instance of @var{octave_gpib} class.@* \
@var{data} - data to be written to the gpib interface. Can be either of String or uint8 type.\n \
\n\
Upon successful completion, gpib_write() shall return the number of bytes written as the result @var{n}.\n \
@end deftypefn")
{
#ifndef BUILD_GPIB
  error ("gpib: Your system doesn't support the GPIB interface");
  return octave_value ();
#else
  if (args.length () != 2 || args (0).type_id () != octave_gpib::static_type_id ())
    {
      print_usage();
      return octave_value(-1);
    }

  octave_gpib* gpib = NULL;
  int retval;

  const octave_base_value& rep = args (0).get_rep ();
  gpib = &((octave_gpib &)rep);

  if (args (1).is_string ()) // String
    {
      retval = gpib->write (args (1).string_value ());
    }
  else if (args (1).is_uint8_type ()) // uint8_t
    {
      NDArray data = args (1).array_value ();
      OCTAVE_LOCAL_BUFFER (uint8_t, buf, (data.numel ()));

      if (buf == NULL)
        {
          error ("gpib_write: cannot allocate requested memory: %s\n", strerror (errno));
          return octave_value(-1);
        }

      for (int i = 0; i < data.numel (); i++)
        buf[i] = static_cast<uint8_t>(data (i));

      retval = gpib->write (buf, data.numel ());
    }
  else
    {
      print_usage ();
      return octave_value (-1);
    }

  return octave_value (retval);
#endif
}
