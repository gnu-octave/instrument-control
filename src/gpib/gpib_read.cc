// Copyright (C) 2018   John Donoghue   <john.donoghue@ieee.org>
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
#include <octave/uint8NDArray.h>

#include <errno.h>

#include "gpib_class.h"

#endif

// PKG_ADD: autoload ("gpib_read", "gpib.oct");
DEFUN_DLD (gpib_read, args, nargout,
        "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {[@var{data}, @var{count}, @var{eoi}] = } gpib_read (@var{gpib}, @var{n})\n \
\n\
Read from gpib interface.\n \
\n\
@var{gpib} - instance of @var{octave_gpib} class.@* \
@var{n} - number of bytes to attempt to read of type Integer.\n \
\n\
The gpib_read() shall return number of bytes successfully read in @var{count} as Integer and the bytes themselves in @var{data} as uint8 array.\n \
@var{eoi} indicates read operation complete \n \
@end deftypefn")
{
#ifndef BUILD_GPIB
  error ("gpib: Your system doesn't support the GPIB interface");
  return octave_value ();
#else
  if (args.length () < 2 || args.length () > 3 || args (0).type_id () != octave_gpib::static_type_id ())
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

  buffer_len = args (1).int_value ();

  OCTAVE_LOCAL_BUFFER (uint8_t, buffer, (buffer_len + 1));

  if (buffer == NULL)
    {
      error ("gpib_read: cannot allocate requested memory: %s\n", strerror (errno));
      return octave_value (-1);
    }

  octave_gpib* gpib = NULL;

  const octave_base_value& rep = args (0).get_rep ();
  gpib = &((octave_gpib &)rep);

  // Read data
  bool eoi;
  int bytes_read = gpib->read (buffer, buffer_len, &eoi);

  // Convert data to octave type variables
  octave_value_list return_list;
  uint8NDArray data(dim_vector (1, bytes_read));

  for (int i = 0; i < bytes_read; i++)
    data (i) = buffer[i];

  return_list (0) = data;
  return_list (1) = bytes_read;
  return_list (2) = eoi;

  return return_list;
#endif
}
