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

#ifdef BUILD_VXI11
#include <errno.h>

using std::string;

#include "vxi11_class.h"
#endif

// PKG_ADD: autoload ("vxi11", "vxi11.oct");
DEFUN_DLD (vxi11, args, nargout,
        "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{vxi11} = } vxi11 (@var{ip})\n \
\n\
Open vxi11 interface.\n \
\n\
@var{path} - the ip address of type String. If omitted defaults to '127.0.0.1'.\n \
\n\
The vxi11() shall return instance of @var{octave_vxi11} class as the result @var{vxi11}.\n \
@end deftypefn")
{
#ifndef BUILD_VXI11
  error ("vxi11: Your system doesn't support the VXI11 interface");
  return octave_value ();
#else
  // Do not open interface if return value is not assigned
  if (nargout != 1)
    {
      print_usage ();
      return octave_value ();
    }

  // Default values
  string path ("127.0.0.1");

  // Parse the function arguments
  if (args.length () > 0)
    {
      if (args(0).is_string ())
        {
          path = args (0).string_value ();
        }
      else
        {
          print_usage ();
          return octave_value ();
        }
    }

  // Open the interface
  octave_vxi11* retval = new octave_vxi11;

  if (retval->open (path) < 0)
    {
      error("vxi11: Error opening the interface: %s\n", strerror (errno));
      return octave_value ();
    }

  return octave_value (retval);
#endif
}
#if 0
%!test
%! if any(strcmp(instrhwinfo().SupportedInterfaces, "vxi11"))
%!   fail ("vxi11 ()", "Invalid call to vxi11");
%! else
%!   fail ("vxi11 ()", "vxi11: Your system doesn't support the VXI11 interface");
%! endif

#endif
