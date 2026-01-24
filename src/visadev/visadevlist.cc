// Copyright (C) 2025 John Donoghue   <john.donoghue@ieee.org>
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
#include <octave/oct-map.h>

#ifdef HAVE_CONFIG_H
#  include "../config.h"
#endif

#ifdef BUILD_VISA
#  include "visadev_class.h"
#endif

// PKG_ADD: autoload ("visadevlist", "visadev.oct");
DEFUN_DLD (visadevlist, args, nargout,
        "-*- texinfo -*-\n\
@deftypefn {} {@var{resourcelist} = } visadevlist ()\n \
\n\
List available visadev resources.\n \
\n\
@subsubheading Inputs\n \
@var{propertyname}, @var{propertyvalue} - property name/value pair\n \
\n\
Known input properties:\n \
@table @asis\n \
@end table \n \
\n\
@subsubheading Outputs\n \
The visdevlist function shall return struct array of available resoures.\n \
Struct properties:\n \
@table @asis\n \
@end table \n \
\n \
@end deftypefn")
{
#ifndef BUILD_VISA
  error("visadev: Your system doesn't support the VISA interface");
  return octave_value();
#else
  octave_value retval;

  std::vector <visa_devinfo> devs = octave_visadev::list_devices();

  Cell name (dim_vector (1, devs.size()));
  Cell alias (dim_vector (1, devs.size()));
  Cell type (dim_vector (1, devs.size()));

  for(size_t i=0; i<devs.size(); i++)
    {
      visa_devinfo dev = devs[i];

      name(i) = dev.name;
      alias(i) = dev.alias;
      type(i) = dev.type;
    }

  octave_map devinfo;
  devinfo.setfield("ResourceName", name);
  devinfo.setfield("Alias", alias);
  devinfo.setfield("Type", type);

  retval = devinfo;

  return retval;
#endif
}

#if 0
%!xtest
%! lst = visadevlist();
%! assert(isstruct(lst));
%! assert(isfield(lst, "Alias"));
%! assert(isfield(lst, "ResourceName"));
#endif
