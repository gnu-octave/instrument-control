// Copyright (C) 2017   John Donoghue   <john.donoghue@ieee.org>
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
#  include "../config.h"
#endif

DEFUN_DLD (__instr_hwinfo__, args, nargout,
        "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{res} = }  __instr_hwinfo__()\n \
\n\
Internal private function\n \
\n\
@end deftypefn")
{
  octave_value_list return_value;
  octave_value_list interfaces;
  
  octave_map inf;

  inf.assign("ToolboxVersion", octave_value(PACKAGE_VERSION));
  inf.assign("ToolboxName", octave_value(PACKAGE_NAME));

  int int_count = 0;
#ifdef BUILD_GPIB
  interfaces (int_count++) = "gpib";
#endif
#ifdef BUILD_I2C
  interfaces (int_count++) = "i2c";
#endif
#ifdef BUILD_PARALLEL
  interfaces (int_count++) = "parallel";
#endif

#ifdef BUILD_SERIAL
  interfaces (int_count++) = "serial";
#endif

#ifdef BUILD_TCP
  interfaces (int_count++) = "tcp";
#endif

#ifdef BUILD_UDP
  interfaces (int_count++) = "udp";
#endif

#ifdef BUILD_USTMC
  interfaces (int_count++) = "usbtmc";
#endif

#ifdef BUILD_VXI11
  interfaces (int_count++) = "vxi11";
#endif

  inf.assign("SupportedInterfaces", octave_value(interfaces.cell_value()));

  return_value (0) = inf;

  return return_value;
}
#if 0
%!test
%! a = __instr_hwinfo__();
%! assert (! isempty (a));
#endif
