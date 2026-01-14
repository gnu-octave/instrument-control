// Copyright (C) 2022 John Donoghue <john.donoghue@ieee.org>
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
#include "../config.h"
#endif

#ifdef BUILD_MODBUS
#include "modbus_class.h"

octave_value_list modbus_flush (octave_modbus* dev, const octave_value_list& args, int nargout)
{
  if (args.length() > 1) 
    (*current_liboctave_error_handler) ("wrong number of arguments");
    
  // Default arguments
  int queue_selector = 2; // Input and Output
    
  if (args.length () > 0)
    {
      if (!(args (0).OV_ISINTEGER () || args (0).OV_ISFLOAT ()))
        (*current_liboctave_error_handler) ("argument must be integer or float");

      queue_selector = args (0).int_value ();
    }

    dev->flush (queue_selector);

    return octave_value ();
}

octave_value_list modbus_timeout (octave_modbus* dev, const octave_value_list& args, int nargout)
{
  if (args.length () > 1)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  // Setting new timeout
  if (args.length () > 0)
    {
      if ( !(args (0).OV_ISINTEGER () || args (0).OV_ISFLOAT ()) )
        (*current_liboctave_error_handler) ("argument must be integer or float");

      dev->set_timeout (args (0).double_value ());

      return octave_value (); // Should it return by default?
    }

  // Returning current timeout
  return octave_value (dev->get_timeout ());
}

octave_value_list modbus_numretries (octave_modbus* dev, const octave_value_list& args, int nargout)
{
  if (args.length () > 1)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  // Setting new reties
  if (args.length () > 0)
    {
      if ( !(args (0).OV_ISINTEGER () || args (0).OV_ISFLOAT ()) )
        (*current_liboctave_error_handler) ("argument must be integer or float");

      dev->set_numretries (args (0).double_value ());

      return octave_value (); // Should it return by default?
    }

  // Returning current value
  return octave_value (dev->get_numretries ());
}


octave_value_list modbus_userdata (octave_modbus* dev, const octave_value_list& args, int nargout)
{
  if (args.length () > 1)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  // set user data
  if (args.length () > 0)
    {
      dev->set_userdata (args (0));

      return octave_value (); // Should it return by default?
    }

  // Returning current timeout
  return octave_value (dev->get_userdata ());
}

octave_value_list modbus_byteorder (octave_modbus* dev, const octave_value_list& args, int nargout)
{
  if (args.length () > 1)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  // Setting new byte order
  if (args.length () > 0)
    {
      if ( !(args (0).is_string ()) )
        (*current_liboctave_error_handler) ("argument must be a string");

      dev->set_byteorder (args (0).string_value());

      return octave_value (); // Should it return by default?
    }

  return octave_value (dev->get_byteorder ());
}

octave_value_list modbus_wordorder (octave_modbus* dev, const octave_value_list& args, int nargout)
{
  if (args.length () > 1)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  // Setting new timeout
  if (args.length () > 0)
    {
      if ( !(args (0).is_string ()) )
        (*current_liboctave_error_handler) ("argument must be a string");

      dev->set_wordorder (args (0).string_value());

      return octave_value (); // Should it return by default?
    }

  return octave_value (dev->get_wordorder ());
}

octave_value_list modbus_name (octave_modbus* dev, const octave_value_list& args, int nargout)
{
  if (args.length () > 1)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  // Setting new timeout
  if (args.length () > 0)
    {
      if ( !(args (0).is_string ()) )
        (*current_liboctave_error_handler) ("argument must be a string");

      dev->set_name (args (0).string_value());

      return octave_value (); // Should it return by default?
    }

  return octave_value (dev->get_name ());
}

octave_value_list modbus_port (octave_modbus* dev, const octave_value_list& args, int nargout)
{
  if (args.length () > 0)
    (*current_liboctave_error_handler) ("read only value");

  // TODO: depending on serial or tcp of what is returned
  //return octave_value (dev->get_port ());
  if(dev->get_transport() == "tcpip")
    return octave_value(dev->get_tcpport());
  else
    return octave_value(dev->get_rtuport());
}

octave_value_list modbus_baudrate (octave_modbus* dev, const octave_value_list& args, int nargout)
{
  if (args.length () > 0)
    (*current_liboctave_error_handler) ("read only value");

  return octave_value(dev->get_baudrate());
}

octave_value_list modbus_databits (octave_modbus* dev, const octave_value_list& args, int nargout)
{
  if (args.length () > 0)
    (*current_liboctave_error_handler) ("read only value");

  return octave_value(dev->get_databits());
}

octave_value_list modbus_stopbits (octave_modbus* dev, const octave_value_list& args, int nargout)
{
  if (args.length () > 0)
    (*current_liboctave_error_handler) ("read only value");

  return octave_value(dev->get_stopbits());
}

octave_value_list modbus_parity (octave_modbus* dev, const octave_value_list& args, int nargout)
{
  if (args.length () > 0)
    (*current_liboctave_error_handler) ("read only value");

  return octave_value(dev->get_parity());
}

octave_value_list modbus_deviceaddress (octave_modbus* dev, const octave_value_list& args, int nargout)
{
  if (args.length () > 0)
    (*current_liboctave_error_handler) ("read only value");

  return octave_value(dev->get_deviceaddress());
}

octave_value_list modbus_type (octave_modbus* dev, const octave_value_list& args, int nargout)
{
  if (args.length () > 0)
    (*current_liboctave_error_handler) ("read only value");

  // TODO: depending on serial or tcp of what is returned
  //return octave_value (dev->get_port ());
  return octave_value(dev->get_type());
}


octave_value_list modbus_transport (octave_modbus* dev, const octave_value_list& args, int nargout)
{
  if (args.length () > 0)
    (*current_liboctave_error_handler) ("read only value");

  // TODO: depending on serial or tcp of what is returned
  //return octave_value (dev->get_port ());
  return octave_value(dev->get_transport());
}

#endif

// PKG_ADD: autoload ("__modbus_properties__", "modbus.oct");
DEFUN_DLD (__modbus_properties__, args, nargout,
"-*- texinfo -*-\n\
@deftypefn {Loadable Function} {varargout =} __modbus_properties__ (@var{octave_serialport}, @var{property}, @var{varargin})\n\
Undocumented internal function.\n\
@end deftypefn")
{
#ifdef BUILD_MODBUS

  if (args.length () < 2 || args (0).type_id () != octave_modbus::static_type_id () || !args (1).is_string ())
    (*current_liboctave_error_handler) ("wrong number of arguments");
    
  const octave_base_value& rep = args (0).get_rep ();
  octave_modbus* dev = &((octave_modbus &)rep);
    
  std::string property = args (1).string_value ();
  std::transform (property.begin (), property.end (), property.begin (), ::tolower);

  octave_value_list args2 = args.slice (2, args.length ()-2);
    
  if (property == "port")
    return modbus_port (dev, args2, nargout);
  else if (property == "baudrate")
    return modbus_baudrate (dev, args2, nargout);
  else if (property == "transport")
    return modbus_transport (dev, args2, nargout);
  else if (property == "type")
    return modbus_type (dev, args2, nargout);
  else if (property == "byteorder")
    return modbus_byteorder (dev, args2, nargout);
  else if (property == "wordorder")
    return modbus_wordorder (dev, args2, nargout);
  else if (property == "databits")
    return modbus_databits (dev, args2, nargout);
  else if (property == "stopbits")
    return modbus_stopbits (dev, args2, nargout);
  else if (property == "parity")
    return modbus_parity (dev, args2, nargout);
  else if (property == "timeout")
    return modbus_timeout (dev, args2, nargout);
  else if (property == "numretries")
    return modbus_numretries (dev, args2, nargout);
  else if (property == "deviceaddress")
    return modbus_deviceaddress (dev, args2, nargout);
  else if (property == "name")
    return modbus_name (dev, args2, nargout);
  else if (property == "userdata")
    return modbus_userdata (dev, args2, nargout);
  // internals
  else if (property == "__flush__")
    return modbus_flush (dev, args2, nargout);
  else
    (*current_liboctave_error_handler) ("unknown property");
#endif
    /* never reached in normal operation */
  (*current_liboctave_error_handler) ("Your system doesn't support the MODBUS interface");

  return octave_value();
}
