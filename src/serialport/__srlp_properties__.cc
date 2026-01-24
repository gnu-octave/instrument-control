// Copyright (C) 2019-2022 John Donoghue <john.donoghue@ieee.org>
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
#include "serialport_class.h"
#endif

#ifdef BUILD_SERIAL

octave_value_list srlp_flush (octave_serialport* serialport, const octave_value_list& args, int nargout)
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

    serialport->flush (queue_selector);

    return octave_value ();
}

octave_value_list srlp_break (octave_serialport* serialport, const octave_value_list& args, int nargout)
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

    serialport->sendbreak (ms);

    return octave_value ();
}

octave_value_list srlp_timeout (octave_serialport* serialport, const octave_value_list& args, int nargout)
{
  if (args.length () > 1)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  // Setting new timeout
  if (args.length () > 0)
    {
      if ( !(args (0).OV_ISINTEGER () || args (0).OV_ISFLOAT ()) )
        (*current_liboctave_error_handler) ("argument must be integer or float");

      serialport->set_timeout (args (0).double_value ());

      return octave_value (); // Should it return by default?
    }

  // Returning current timeout
  return octave_value (serialport->get_timeout ());
}

octave_value_list srlp_userdata (octave_serialport* serialport, const octave_value_list& args, int nargout)
{
  if (args.length () > 1)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  // Setting new timeout
  if (args.length () > 0)
    {
      if ( !(args (0).OV_ISINTEGER () || args (0).OV_ISFLOAT ()) )
        (*current_liboctave_error_handler) ("argument must be integer or float");

      serialport->set_userdata (args (0));

      return octave_value (); // Should it return by default?
    }

  // Returning current timeout
  return octave_value (serialport->get_userdata ());
}

octave_value_list srlp_tag (octave_serialport* serialport, const octave_value_list& args, int nargout)
{
  if (args.length () > 1)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  // Setting new timeout
  if (args.length () > 0)
    {
      if ( !args (0).is_string() )
        (*current_liboctave_error_handler) ("argument must be a string");

      serialport->set_tag (args (0).string_value());

      return octave_value (); // Should it return by default?
    }

  // Returning current timeout
  return octave_value (serialport->get_tag ());
}

octave_value_list srlp_flowcontrol (octave_serialport* serialport, const octave_value_list& args, int nargout)
{
  if (args.length () > 1)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  // Setting new timeout
  if (args.length () > 0)
    {
      if ( !(args (0).is_string() ))
        (*current_liboctave_error_handler) ("argument must be a string");

      serialport->set_flowcontrol (args (0).string_value());

      return octave_value (); // Should it return by default?
    }

  return octave_value (serialport->get_flowcontrol ());
}

octave_value_list srlp_terminator (octave_serialport* serialport, const octave_value_list& args, int nargout)
{
  // Setting new timeout
  if (args.length () == 1)
    {
      if ( !(args (0).is_string ()) && !(args (0).is_scalar_type()))
        (*current_liboctave_error_handler) ("argument must be a string or number");

      serialport->set_input_terminator (args (0));
      serialport->set_output_terminator (args (0));

      return octave_value (); // Should it return by default?
    }
  else if (args.length () == 2)
    {
      if ( !(args (0).is_string ()) && !(args (0).is_scalar_type()))
        (*current_liboctave_error_handler) ("argument must be a string or number");
      if ( !(args (1).is_string ()) && !(args (0).is_scalar_type()))
        (*current_liboctave_error_handler) ("argument must be a string or number");

      // could be 1 or 2 args here

      serialport->set_input_terminator (args (0));
      serialport->set_output_terminator (args (1));

      return octave_value (); // Should it return by default?
    }
  else if (args.length () > 2)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  // may have a single terminator or a start and stop
  octave_value in = serialport->get_input_terminator ();
  octave_value out = serialport->get_output_terminator ();

  if(in.is_string() && out.is_string() && in.string_value() == out.string_value())
    return in;
  else if(in.is_scalar_type() && out.is_scalar_type() && in.int_value() == out.int_value())
    return in;
  else
    {
      Cell ret = Cell(dim_vector(1, 2));
      ret(0) = in;
      ret(1) = out;
      return octave_value (ret);
    }
  return octave_value_list();
}

octave_value_list srlp_byteorder (octave_serialport* serialport, const octave_value_list& args, int nargout)
{
  if (args.length () > 1)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  // Setting new timeout
  if (args.length () > 0)
    {
      if ( !(args (0).is_string ()) )
        (*current_liboctave_error_handler) ("argument must be a string");

      serialport->set_byteorder (args (0).string_value());

      return octave_value (); // Should it return by default?
    }

  return octave_value (serialport->get_byteorder ());
}


octave_value_list srlp_numbytesavailable (octave_serialport* serialport, const octave_value_list& args, int nargout)
{
  if (args.length () > 0)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  // Returning bytes available
  return octave_value (serialport->get_numbytesavailable ());
}

octave_value_list srlp_numbyteswritten (octave_serialport* serialport, const octave_value_list& args, int nargout)
{
  if (args.length () > 0)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  // Returning bytes available
  return octave_value (serialport->get_numbyteswritten ());
}

octave_value_list srlp_port (octave_serialport* serialport, const octave_value_list& args, int nargout)
{
  if (args.length () > 0)
    (*current_liboctave_error_handler) ("read only value");

  // Returning bytes available
  return octave_value (serialport->get_port ());
}

octave_value_list srlp_baudrate (octave_serialport* serialport, const octave_value_list& args, int nargout)
{
  if (args.length() > 1)
    (*current_liboctave_error_handler) ("wrong number of arguments");
    
  // Setting new baudrate
  if (args.length () > 0)
    {
      if (! (args (0).OV_ISINTEGER () || args (0).OV_ISFLOAT ()))
        (*current_liboctave_error_handler) ("argument must be integer or float");

      serialport->set_baudrate (args (0).int_value ());

      return octave_value ();
    }

  // Returning current baud rate
  return octave_value (serialport->get_baudrate ());
}

octave_value_list srlp_databits (octave_serialport* serialport, const octave_value_list& args, int nargout)
{
  if (args.length () > 1)
    (*current_liboctave_error_handler) ("wrong number of arguments");
    
  // Setting new byte size
  if (args.length () > 0)
    {
      if (! (args (0).OV_ISINTEGER () || args (0).OV_ISFLOAT ()) )
        (*current_liboctave_error_handler) ("argument must be integer or float");

      serialport->set_databits (args (0).int_value ());

      return octave_value ();
    }

  // Returning current byte size 
  return octave_value (serialport->get_databits ());
}

octave_value_list srlp_stopbits (octave_serialport* serialport, const octave_value_list& args, int nargout)
{
  if (args.length() > 1)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  // Setting new stop bits
  if (args.length () > 0)
    {
      if (! (args (0).OV_ISINTEGER () || args (0).OV_ISFLOAT ()) )
        (*current_liboctave_error_handler) ("argument must be integer or float");

      serialport->set_stopbits(args (0).int_value ());

      return octave_value ();
    }

  // Returning current stop bits
  return octave_value (serialport->get_stopbits ());
}

octave_value_list srlp_parity (octave_serialport* serialport, const octave_value_list& args, int nargout)
{
  if (args.length () > 1)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  // Setting new parity
  if (args.length () > 0)
    {
      if ( !(args (0).is_string ()) )
        (*current_liboctave_error_handler) ("argument must be string");

      serialport->set_parity (args (0).string_value());

      return octave_value ();
    }

  // Returning current parity
  return octave_value (serialport->get_parity ());
}

octave_value_list srlp_requesttosend (octave_serialport* serialport, const octave_value_list& args, int nargout)
{
  if (args.length () > 1)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  // Setting RTS
  if (args.length () > 0)
    {
      if (! (args (0).OV_ISINTEGER () || args (0).OV_ISFLOAT () || args(0).OV_ISLOGICAL ()) )
        (*current_liboctave_error_handler) ("argument must be boolean or a number");

      int onoff = args (0).int_value ();
      if (onoff)
        serialport->set_control_line ("RTS", true);
      else
        serialport->set_control_line ("RTS", false);
    }

  // Returning RTS
  if (serialport->get_control_line ("RTS"))
    return octave_value (1);

  return octave_value (0);
}

octave_value_list srlp_dataterminalready (octave_serialport* serialport, const octave_value_list& args, int nargout)
{
  if (args.length () > 1)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  std::string onoff = "";

  // Setting DTR
  if (args.length () > 0)
    {
      if (! (args (0).OV_ISINTEGER () || args (0).OV_ISFLOAT () || args(0).OV_ISLOGICAL ()) )
        (*current_liboctave_error_handler) ("argument must be boolean or a number");

      int onoff = args (0).int_value ();
      if (onoff)
        serialport->set_control_line ("DTR", true);
      else
        serialport->set_control_line ("DTR", false);
    }

  // Returning DTR
  if (serialport->get_control_line ("DTR"))
    return octave_value (1);

  return octave_value (0);
}

octave_value_list srlp_pinstatus (octave_serialport* serialport, const octave_value_list& args, int nargout)
{
  if (args.length () > 0)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  octave_scalar_map res;

  res.assign ("CarrierDetect", serialport->get_control_line ("CD") ?
                               octave_value (1) :
                               octave_value (0));

  res.assign ("ClearToSend", serialport->get_control_line ("CTS") ?
                               octave_value (1) :
                               octave_value (0));

  res.assign ("DataSetReady", serialport->get_control_line ("DSR") ?
                               octave_value (1) :
                               octave_value (0));

  res.assign ("RingIndicator", serialport->get_control_line ("RI") ?
                               octave_value (0) :
                               octave_value (1));

  return octave_value (res);
}
#endif

// PKG_ADD: autoload ("__srlp_properties__", "serialport.oct");
DEFUN_DLD (__srlp_properties__, args, nargout,
"-*- texinfo -*-\n\
@deftypefn {} {varargout =} __srlp_properties__ (@var{octave_serialport}, @var{property}, @var{varargin})\n\
Undocumented internal function.\n\
@end deftypefn")
{
#ifdef BUILD_SERIAL

  if (args.length () < 2 || args (0).type_id () != octave_serialport::static_type_id () || !args (1).is_string ())
    (*current_liboctave_error_handler) ("wrong number of arguments");
    
  const octave_base_value& rep = args (0).get_rep ();
  octave_serialport* serialport = &((octave_serialport &)rep);
    
  std::string property = args (1).string_value ();
  std::transform (property.begin (), property.end (), property.begin (), ::tolower);

  octave_value_list args2 = args.slice (2, args.length ()-2);
    
  if (property == "port")
    return srlp_port (serialport, args2, nargout);
  else if (property == "baudrate")
    return srlp_baudrate (serialport, args2, nargout);
  else if (property == "numbytesavailable")
    return srlp_numbytesavailable (serialport, args2, nargout);
  else if (property == "numbyteswritten")
    return srlp_numbyteswritten (serialport, args2, nargout);
  else if (property == "byteorder")
    return srlp_byteorder (serialport, args2, nargout);
  else if (property == "databits")
    return srlp_databits (serialport, args2, nargout);
  else if (property == "stopbits")
    return srlp_stopbits (serialport, args2, nargout);
  else if (property == "parity")
    return srlp_parity (serialport, args2, nargout);
  else if (property == "flowcontrol")
    return srlp_flowcontrol (serialport, args2, nargout);
  else if (property == "timeout")
    return srlp_timeout (serialport, args2, nargout);
  else if (property == "userdata")
    return srlp_userdata (serialport, args2, nargout);
  else if (property == "terminator")
    return srlp_terminator (serialport, args2, nargout);
  else if (property == "tag")
    return srlp_tag (serialport, args2, nargout);
  // internals
  else if (property == "__flush__")
    return srlp_flush (serialport, args2, nargout);
  else if (property == "__break__")
    return srlp_break (serialport, args2, nargout);
  else if (property == "__pinstatus__")
    return srlp_pinstatus (serialport, args2, nargout);
  else if (property == "__requesttosend__")
    return srlp_requesttosend (serialport, args2, nargout);
  else if (property == "__dataterminalready__")
    return srlp_dataterminalready (serialport, args2, nargout);
  else
    (*current_liboctave_error_handler) ("wrong keyword");
#endif
    /* never reached in normal operation */
  (*current_liboctave_error_handler) ("Your system doesn't support the SERIAL interface");
}
