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
#include <octave/ov-struct.h>

#ifdef HAVE_CONFIG_H
#  include "../config.h"
#endif

#ifdef BUILD_SPI
#  include "spi_class.h"
#endif


// PKG_ADD: autoload ("__spi_properties__", "spi.oct");
DEFUN_DLD (__spi_properties__, args, nargout,
"-*- texinfo -*-\n\
@deftypefn {Loadable Function} {varargout =} __spi_properties__ (@var{octave_spi}, @var{property}, @var{varargin})\n\
Undocumented internal function.\n\
@end deftypefn")
{
#ifdef BUILD_SPI
  if (args.length () < 2 || args.length () > 3 ||
    args(0).type_id () != octave_spi::static_type_id () || 
    !args(1).is_string ())
      (*current_liboctave_error_handler) ("wrong number of arguments");
    
  const octave_base_value& rep = args(0).get_rep ();
  octave_spi* spi = &((octave_spi &)rep);
    
  std::string property = args(1).string_value ();

  if (args.length () == 2) // get
    {
      if (property == "name")
        return octave_value (spi->get_name ());
      else if (property == "bitrate")
        return octave_value (spi->get_bitrate ());
      else if (property == "clockpolarity")
        return octave_value (spi->get_clockpolarity ());
      else if (property == "clockphase")
        return octave_value (spi->get_clockphase ());
      else if (property == "status")
        return octave_value (spi->get_status ());
      else if (property == "port")
        return octave_value (spi->get_port ());
      else
        (*current_liboctave_error_handler) ("invalid property name");
    }
  else // set
    {
      if (property == "name")
        return octave_value (spi->set_name (args(2).string_value ()));
      else if (property == "status")
        (*current_liboctave_error_handler) ("can not set this property");
      else if (property == "bitrate")
        return octave_value (spi->set_bitrate (args(2).int_value ()));
      else if (property == "clockpolarity")
        return octave_value (spi->set_clockpolarity (args(2).string_value ()));
      else if (property == "clockphase")
        return octave_value (spi->set_clockphase (args(2).string_value ()));
      else if (property == "port")
        (*current_liboctave_error_handler) ("can not set this property");
      else
        (*current_liboctave_error_handler) ("invalid property name");
    }

#else
    /* never reached in normal operation */
  (*current_liboctave_error_handler) ("Your system doesn't support the SPI interface");
#endif
  return octave_value();
}
