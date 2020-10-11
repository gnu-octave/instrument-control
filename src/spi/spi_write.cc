// Copyright (C) 2020   John Donoghue   <john.donoghue@ieee.org>
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

#ifdef BUILD_SPI
#include <errno.h>

#include "spi_class.h"
#endif

// PKG_ADD: autoload ("spi_write", "spi.oct");
DEFUN_DLD (spi_write, args, nargout, 
        "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{n} = } spi_write (@var{spi}, @var{data})\n \
\n\
Write data to a spi slave device.\n \
\n\
@subsubheading Inputs\n \
@var{spi} - instance of @var{octave_spi} class.@*\
@var{data} - data, of type uint8, to be written to the slave device.\n \
\n\
@subsubheading Outputs\n \
Upon successful completion, spi_write() shall return the number of bytes written as the result @var{n}.\n \
@end deftypefn")
{
#ifndef BUILD_SPI
  error ("spi: Your system doesn't support the SPI interface");
  return octave_value ();
#else
  if (args.length () != 2 || args (0).type_id () != octave_spi::static_type_id ()) 
    {
      print_usage ();
      return octave_value (-1);
    }

  octave_spi* spi = NULL;
  int retval;

  const octave_base_value& rep = args (0).get_rep ();
  spi = &((octave_spi &)rep);

  if (args (1).is_uint8_type ()) // uint8_t
    {
      NDArray data = args (1).array_value ();
      OCTAVE_LOCAL_BUFFER (uint8_t, buf, (data.numel ()));

      if (buf == NULL)
        {
          error ("spi_write: cannot allocate requested memory: %s", strerror (errno));
          return octave_value (-1);  
        }

      for (int i = 0; i < data.numel (); i++)
        buf[i] =  static_cast<uint8_t>(data (i));

      retval = spi->write (buf, data.numel());
    }
  else
    {
      error ("spi_write: expected uint8 data");
      return octave_value (-1);
    }

  return octave_value (retval);
#endif
}
