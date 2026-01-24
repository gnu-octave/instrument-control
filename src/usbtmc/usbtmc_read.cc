// Copyright (C) 2019   John Donoghue   <john.donoghue@ieee.org>
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

#ifdef BUILD_USBTMC
#include <octave/uint8NDArray.h>

#include <errno.h>

#include "usbtmc_class.h"
#endif

// PKG_ADD: autoload ("usbtmc_read", "usbtmc.oct");
DEFUN_DLD (usbtmc_read, args, nargout,
        "-*- texinfo -*-\n\
@deftypefn {} {[@var{data}, @var{count}] = } usbtmc_read (@var{usbtmc}, @var{n})\n \
\n\
Read from usbtmc slave device.\n \
\n\
@subsubheading Inputs\n \
@var{usbtmc} - instance of @var{octave_usbtmc} class.@* \
@var{n} - number of bytes to attempt to read of type Integer.\n \
\n\
@subsubheading Outputs\n \
@var{count} - the number of bytes successfully read as an Integer.@*\n \
@var{data} - the read bytes as a uint8 array.\n \
@end deftypefn")
{
#ifndef BUILD_USBTMC
  error ("usbtmc: Your system doesn't support the USBTMC interface");
  return octave_value ();
#else

  if (args.length () < 1 || args.length () > 2 || args (0).type_id () != octave_usbtmc::static_type_id ())
    {
      print_usage ();
      return octave_value (-1);
    }

  unsigned int buffer_len = 1;

  if (args.length () > 1)
    {
      if (! (args (1).OV_ISINTEGER () || args (1).OV_ISFLOAT ()) )
        {
          print_usage ();
          return octave_value (-1);
        }

      buffer_len = args(1).int_value();
    }

  OCTAVE_LOCAL_BUFFER (uint8_t, buffer, (buffer_len + 1));

  if (buffer == NULL)
    {
      error ("usbtmc_read: cannot allocate requested memory: %s\n", strerror (errno));
      return octave_value (-1);
    }

  octave_usbtmc* usbtmc = NULL;

  const octave_base_value& rep = args (0).get_rep ();
  usbtmc = &((octave_usbtmc &)rep);

  int retval;

  retval = usbtmc->read (buffer, buffer_len);

  if (retval < 0)
    {
      // read has already displayed a message, so just exit
      return octave_value (-1);
    }

  octave_value_list return_list;
  uint8NDArray data (dim_vector (1, retval));

  for (int i = 0; i < retval; i++)
    data (i) = buffer[i];

  return_list (0) = data;
  return_list (1) = retval;

  return return_list;
#endif
}
