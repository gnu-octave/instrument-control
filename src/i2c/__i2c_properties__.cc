// Copyright (C) 2019   John Donoghue   <john.donoghue@ieee.org>
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

#ifdef BUILD_I2C
#  include "i2c_class.h"
#endif


// PKG_ADD: autoload ("__i2c_properties__", "i2c.oct");
DEFUN_DLD (__i2c_properties__, args, nargout,
"-*- texinfo -*-\n\
@deftypefn {} {varargout =} __i2c_properties__ (@var{octave_i2c}, @var{property}, @var{varargin})\n\
Undocumented internal function.\n\
@end deftypefn")
{
#ifdef BUILD_I2C
  if (args.length () < 2 || args.length () > 3 ||
    args(0).type_id () != octave_i2c::static_type_id () || 
    !args(1).is_string ())
      (*current_liboctave_error_handler) ("wrong number of arguments");
    
  const octave_base_value& rep = args(0).get_rep ();
  octave_i2c* i2c = &((octave_i2c &)rep);
    
  std::string property = args(1).string_value ();

  if (args.length () == 2) // get
    {
      if (property == "name")
        return octave_value (i2c->get_name ());
      else if (property == "remoteaddress")
        return octave_value (i2c->get_addr ());
      else if (property == "status")
        return octave_value (i2c->get_status ());
      else if (property == "port")
        return octave_value (i2c->get_port ());
      else
        (*current_liboctave_error_handler) ("invalid property name");
    }
  else // set
    {
      if (property == "name")
        return octave_value (i2c->set_name (args(2).string_value ()));
      else if (property == "status")
        (*current_liboctave_error_handler) ("can not set this property");
      else if (property == "remoteaddress")
        return octave_value (i2c->set_addr (args(2).int_value ()));
      else if (property == "port")
        (*current_liboctave_error_handler) ("can not set this property");
      else
        (*current_liboctave_error_handler) ("invalid property name");
    }

#else
    /* never reached in normal operation */
  (*current_liboctave_error_handler) ("Your system doesn't support the I2C interface");
#endif
  return octave_value();
}
