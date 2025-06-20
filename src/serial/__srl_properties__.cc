// Copyright (C) 2017   John Donoghue   <john.donoghue@ieee.org>
// Copyright (C) 2012   Andrius Sutas   <andrius.sutas@gmail.com>
// Copyright (C) 2014   Stefan Mahr     <dac922@gmx.de>
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

#ifdef BUILD_SERIAL
#include "serial_class.h"
#endif

#ifdef BUILD_SERIAL
octave_value_list srl_close (octave_serial* serial, const octave_value_list& args, int nargout)
{
  serial->close ();
  return octave_value ();
}

octave_value_list srl_flush (octave_serial* serial, const octave_value_list& args, int nargout)
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

    serial->flush (queue_selector);

    return octave_value ();
}

octave_value_list srl_break (octave_serial* serial, const octave_value_list& args, int nargout)
{
  if (args.length() > 1) 
    (*current_liboctave_error_handler) ("wrong number of arguments");
    
  // Default arguments
  int ms = 2; // Input and Output
    
  if (args.length () > 0)
    {
      if (!(args (0).OV_ISINTEGER () || args (0).OV_ISFLOAT ()))
        (*current_liboctave_error_handler) ("argument must be integer");

      ms = args (0).int_value ();
    }

    serial->sendbreak (ms);

    return octave_value ();
}


octave_value_list srl_timeout (octave_serial* serial, const octave_value_list& args, int nargout)
{
  if (args.length () > 1)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  // Setting new timeout
  if (args.length () > 0)
    {
      if ( !(args (0).OV_ISINTEGER () || args (0).OV_ISFLOAT ()) )
        (*current_liboctave_error_handler) ("argument must be integer or float");

      serial->set_timeout (args (0).int_value ());

      return octave_value (); // Should it return by default?
    }

  // Returning current timeout
  return octave_value (serial->get_timeout ());
}

octave_value_list srl_bytesavailable (octave_serial* serial, const octave_value_list& args, int nargout)
{
  if (args.length () > 0)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  // Returning bytes available
  return octave_value (serial->get_bytesavailable ());
}

octave_value_list srl_status (octave_serial* serial, const octave_value_list& args, int nargout)
{
  if (args.length () > 0)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  // Returning bytes available
  return octave_value (serial->get_status ());
}

octave_value_list srl_type (octave_serial* serial, const octave_value_list& args, int nargout)
{
  if (args.length () > 0)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  // Returning bytes available
  return octave_value (serial->get_type ());
}

octave_value_list srl_port (octave_serial* serial, const octave_value_list& args, int nargout)
{
  if (args.length () > 0)
    (*current_liboctave_error_handler) ("read only value");

  // Returning bytes available
  return octave_value (serial->get_port ());
}

octave_value_list srl_name (octave_serial* serial, const octave_value_list& args, int nargout)
{
  if (args.length() > 1)
    (*current_liboctave_error_handler) ("wrong number of arguments");
    
  // Setting new name
  if (args.length () > 0)
    {
      if (! (args (0).is_string ()))
        (*current_liboctave_error_handler) ("argument must be string");

      serial->set_name (args (0).string_value ());

      return octave_value ();
    }

  // Returning current baud rate
  return octave_value (serial->get_name ());
}

octave_value_list srl_baudrate (octave_serial* serial, const octave_value_list& args, int nargout)
{
  if (args.length() > 1)
    (*current_liboctave_error_handler) ("wrong number of arguments");
    
  // Setting new baudrate
  if (args.length () > 0)
    {
      if (! (args (0).OV_ISINTEGER () || args (0).OV_ISFLOAT ()))
        (*current_liboctave_error_handler) ("argument must be integer or float");

      serial->set_baudrate (args (0).int_value ());

      return octave_value ();
    }

  // Returning current baud rate
  return octave_value (serial->get_baudrate ());
}

octave_value_list srl_bytesize (octave_serial* serial, const octave_value_list& args, int nargout)
{
  if (args.length () > 1)
    (*current_liboctave_error_handler) ("wrong number of arguments");
    
  // Setting new byte size
  if (args.length () > 0)
    {
      if (! (args (0).OV_ISINTEGER () || args (0).OV_ISFLOAT ()) )
        (*current_liboctave_error_handler) ("argument must be integer or float");

      serial->set_bytesize (args (0).int_value ());

      return octave_value ();
    }

  // Returning current byte size 
  return octave_value (serial->get_bytesize ());
}

octave_value_list srl_stopbits (octave_serial* serial, const octave_value_list& args, int nargout)
{
  if (args.length() > 1)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  // Setting new stop bits
  if (args.length () > 0)
    {
      if (! (args (0).OV_ISINTEGER () || args (0).OV_ISFLOAT ()) )
        (*current_liboctave_error_handler) ("argument must be integer or float");

      serial->set_stopbits(args (0).int_value ());

      return octave_value ();
    }

  // Returning current stop bits
  return octave_value (serial->get_stopbits ());
}

octave_value_list srl_parity (octave_serial* serial, const octave_value_list& args, int nargout)
{
  if (args.length () > 1)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  // Setting new parity
  if (args.length () > 0)
    {
      if ( !(args (0).is_string ()) )
        (*current_liboctave_error_handler) ("argument must be string");

      serial->set_parity (args (0).string_value());

      return octave_value ();
    }

  // Returning current parity
  return octave_value (serial->get_parity ());
}

octave_value_list srl_requesttosend (octave_serial* serial, const octave_value_list& args, int nargout)
{
  if (args.length () > 1)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  std::string onoff = "";

  // Setting RTS
  if (args.length () > 0)
    {
      if ( !(args (0).is_string ()) )
        (*current_liboctave_error_handler) ("argument must be string");

      onoff = args (0).string_value ();
      std::transform (onoff.begin (), onoff.end (), onoff.begin (), ::tolower);
      if (onoff == "on")
        serial->set_control_line ("RTS", true);
      else if (onoff == "off")
        serial->set_control_line ("RTS", false);
      else
        (*current_liboctave_error_handler) ("wrong argument");
    }

  // Returning RTS
  if (serial->get_control_line ("RTS"))
    return octave_value ("on");

  return octave_value ("off");
}

octave_value_list srl_dataterminalready (octave_serial* serial, const octave_value_list& args, int nargout)
{
  if (args.length () > 1)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  std::string onoff = "";

  // Setting DTR
  if (args.length () > 0)
    {
      if ( !(args (0).is_string ()) )
        (*current_liboctave_error_handler) ("argument must be string");

      onoff = args (0).string_value ();
      std::transform (onoff.begin (), onoff.end (), onoff.begin (), ::tolower);
      if (onoff == "on")
        serial->set_control_line ("DTR", true);
      else if (onoff == "off")
        serial->set_control_line ("DTR", false);
      else
        (*current_liboctave_error_handler) ("wrong argument");
    }

  // Returning DTR
  if (serial->get_control_line ("DTR"))
    return octave_value ("on");

  return octave_value ("off");
}

octave_value_list srl_pinstatus (octave_serial* serial, const octave_value_list& args, int nargout)
{
  if (args.length () > 0)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  octave_scalar_map res;

  res.assign ("CarrierDetect", serial->get_control_line ("CD") ?
                               octave_value ("on") :
                               octave_value ("off"));

  res.assign ("ClearToSend", serial->get_control_line ("CTS") ?
                               octave_value ("on") :
                               octave_value ("off"));

  res.assign ("DataSetReady", serial->get_control_line ("DSR") ?
                               octave_value ("on") :
                               octave_value ("off"));

  res.assign ("RingIndicator", serial->get_control_line ("RI") ?
                               octave_value ("on") :
                               octave_value ("off"));

  return octave_value (res);
}
#endif

// PKG_ADD: autoload ("__srl_properties__", "serial.oct");
DEFUN_DLD (__srl_properties__, args, nargout,
"-*- texinfo -*-\n\
@deftypefn {Loadable Function} {varargout =} __srl_properties__ (@var{octave_serial}, @var{property}, @var{varargin})\n\
Undocumented internal function.\n\
@end deftypefn")
{
#ifdef BUILD_SERIAL

  if (args.length () < 2 || args (0).type_id () != octave_serial::static_type_id () || !args (1).is_string ())
    (*current_liboctave_error_handler) ("wrong number of arguments");
    
  const octave_base_value& rep = args (0).get_rep ();
  octave_serial* serial = &((octave_serial &)rep);
    
  std::string property = args (1).string_value ();
  octave_value_list args2 = args.slice (2, args.length ()-2);
    
  if (property == "baudrate")
    return srl_baudrate (serial, args2, nargout);
  else if (property == "bytesize")
    return srl_bytesize (serial, args2, nargout);
  else if (property == "dataterminalready")
    return srl_dataterminalready (serial, args2, nargout);
  else if (property == "close")
    return srl_close (serial, args2, nargout);
  else if (property == "flush")
    return srl_flush (serial, args2, nargout);
  else if (property == "break")
    return srl_break (serial, args2, nargout);
  else if (property == "parity")
    return srl_parity (serial, args2, nargout);
  else if (property == "pinstatus")
    return srl_pinstatus (serial, args2, nargout);
  else if (property == "requesttosend")
    return srl_requesttosend (serial, args2, nargout);
  else if (property == "stopbits")
    return srl_stopbits (serial, args2, nargout);
  else if (property == "timeout")
    return srl_timeout (serial, args2, nargout);
  else if (property == "bytesavailable")
    return srl_bytesavailable (serial, args2, nargout);
  else if (property == "status")
    return srl_status (serial, args2, nargout);
  else if (property == "name")
    return srl_name (serial, args2, nargout);
  else if (property == "type")
    return srl_type (serial, args2, nargout);
  else if (property == "port")
    return srl_port (serial, args2, nargout);
  else
    (*current_liboctave_error_handler) ("wrong keyword");
#endif
    /* never reached in normal operation */
  (*current_liboctave_error_handler) ("Your system doesn't support the SERIAL interface");
}
