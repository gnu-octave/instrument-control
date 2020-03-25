// Copyright (C) 2017-2020   John Donoghue   <john.donoghue@ieee.org>
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

#ifdef BUILD_I2C
#include <fcntl.h>

#include "i2c_class.h"
#endif

// PKG_ADD: autoload ("i2c", "i2c.oct");
DEFUN_DLD (i2c, args, nargout, 
        "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{i2c} = } i2c ([@var{port_path}], [@var{address}])\n \
\n\
Open i2c interface.\n \
\n\
@subsubheading Inputs\n \
@var{port_path} - the interface device port/path of type String. If omitted defaults to \n \
'/dev/i2c-0'. @*\n \
@var{address} - the slave device address. If omitted must be set using i2c_addr() call.\n \
\n\
@subsubheading Outputs\n \
@var{i2c} - An instance of @var{octave_i2c} class.\n \
\n\
@subsubheading Properties\n \
The i2c object has the following properties:\n \
@table @asis\n \
@item name\n \
Name of the object\n \
@item remoteaddress\n \
the slave device address\n \
@item port\n \
The interface driver port (readonly)\n \
@end table\n \
@end deftypefn")
{
#ifndef BUILD_I2C
  error ("i2c: Your system doesn't support the I2C interface");
  return octave_value ();
#else
    
  // Do not open interface if return value is not assigned
  if (nargout != 1)
    {
      print_usage ();
      return octave_value ();
    }

  // Default values
  int oflags = O_RDWR;
  std::string path ("/dev/i2c-0");
  int addr = -1;

  // Parse the function arguments
  if (args.length () > 0)
    {
      if (args (0).is_string ())
        {
          path = args (0).string_value ();
        }
      else
        {
          print_usage ();
          return octave_value ();
        }

    }

  // is_float_type() is or'ed to allow expression like ("", 123), without user
  // having to use ("", int32(123)), as we still only take "int_value"
  if (args.length () > 1)
    {
      if (args (1).OV_ISINTEGER () || args (1).OV_ISFLOAT ())
        {
          addr = args (1).int_value ();
        }
      else
        {
          print_usage ();
          return octave_value ();
        }
    }

  octave_i2c* retval = new octave_i2c ();

  // Open the interface
  if (retval->open (path, oflags) < 0)
    return octave_value ();

  if (addr > 0)
    retval->set_addr (addr);

  return octave_value (retval);
#endif
}

#if 0

%!test
%! if any(strcmp(instrhwinfo().SupportedInterfaces, "i2c"))
%!   fail ("i2c ()", "Invalid call to i2c");
%! else
%!   fail ("i2c ()", "i2c: Your system doesn't support the I2C interface");
%! endif

#endif
