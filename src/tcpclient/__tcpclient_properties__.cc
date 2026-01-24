// Copyright (C) 2021   John Donoghue   <john.donoghue@ieee.org>
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

#ifdef BUILD_TCP
#  include "tcpclient_class.h"
#endif

static octave_value_list get_terminator (octave_tcpclient* tcp)
{
  // may have a single terminator or a start and stop
  octave_value in = tcp->get_input_terminator ();
  octave_value out = tcp->get_output_terminator ();

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
}

static octave_value set_terminator(octave_tcpclient* tcp, const octave_value_list& args)
{
  if (args.length () == 1)
    {
      if ( !(args (0).is_string ()) && !(args (0).is_scalar_type ()))
        (*current_liboctave_error_handler) ("argument must be a number or string");

      tcp->set_input_terminator (args (0));
      tcp->set_output_terminator (args (0));

      return octave_value (); // Should it return by default?
    }
  else if (args.length () == 2)
    {
      if ( !(args (0).is_string ()) && !(args (0).is_scalar_type ()))
        (*current_liboctave_error_handler) ("argument must be a number or string");
      if ( !(args (1).is_string ()) && !(args (1).is_scalar_type ()))
        (*current_liboctave_error_handler) ("argument must be a number or string");

      tcp->set_input_terminator (args (0));
      tcp->set_output_terminator (args (1));

      return octave_value (); // Should it return by default?
    }
  else if (args.length () > 2)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  return octave_value();
}

// PKG_ADD: autoload ("__tcpclient_properties__", "tcpclient.oct");
DEFUN_DLD (__tcpclient_properties__, args, nargout,
"-*- texinfo -*-\n\
@deftypefn {} {varargout =} __tcpclient_properties__ (@var{octave_tcpclient}, @var{property}, @var{varargin})\n\
Undocumented internal function.\n\
@end deftypefn")
{
#ifdef BUILD_TCP
  if (args.length () < 2 ||
    args(0).type_id () != octave_tcpclient::static_type_id () || 
    !args(1).is_string ())
      (*current_liboctave_error_handler) ("wrong number of arguments");
    
  const octave_base_value& rep = args(0).get_rep ();
  octave_tcpclient* tcpclient = &((octave_tcpclient &)rep);
    
  std::string property = args(1).string_value ();
  std::transform (property.begin (), property.end (), property.begin (), ::tolower);

  int maxinputs = 3;
  if (property == "terminator")
    maxinputs = 4;

  if (args.length () > maxinputs)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  if (args.length () == 2) // get
    {
      if (property == "name")
        return octave_value (tcpclient->get_name ());
      else if (property == "tag")
        return octave_value (tcpclient->get_tag ());
      else if (property == "type")
        return octave_value (tcpclient->get_type ());
      else if (property == "port")
        return octave_value (tcpclient->get_port ());
      else if (property == "address")
        return octave_value (tcpclient->get_address ());
      else if (property == "status")
        return octave_value (tcpclient->get_status ());
      else if (property == "timeout")
        return octave_value (tcpclient->get_timeout ());
      else if (property == "numbytesavailable")
        return octave_value (tcpclient->get_numbytesavailable ());
      else if (property == "numbyteswritten")
        return octave_value (tcpclient->get_numbyteswritten ());
      else if (property == "byteorder")
        return octave_value (tcpclient->get_byteorder ());
      else if (property == "userdata")
        return octave_value (tcpclient->get_userdata ());
      else if (property == "terminator")
        return get_terminator (tcpclient);
      else if (property == "enabletransferdelay")
        return octave_value(tcpclient->get_enabletransferdelay ());
      else
        (*current_liboctave_error_handler) ("invalid property name");
    }
  else // set
    {
      if (property == "name")
        return octave_value (tcpclient->set_name (args(2).string_value ()));
      else if (property == "tag")
       { tcpclient->set_tag (args(2).string_value ()); return octave_value (); }
      else if (property == "type")
        (*current_liboctave_error_handler) ("can not set this property");
      else if (property == "port")
        (*current_liboctave_error_handler) ("can not set this property");
      else if (property == "address")
        (*current_liboctave_error_handler) ("can not set this property");
      else if (property == "status")
        (*current_liboctave_error_handler) ("can not set this property");
      else if (property == "timeout")
        return octave_value (tcpclient->set_timeout (args(2).double_value ()));
      else if (property == "userdata")
        { tcpclient->set_userdata (args(2)); return octave_value (); }
      else if (property == "byteorder")
        return octave_value (tcpclient->set_byteorder (args(2).string_value ()));
      else if (property == "flush")
        return octave_value (tcpclient->flush (args(2).int_value ()));
      else if (property == "terminator")
        return set_terminator (tcpclient, args.slice (2, args.length ()-2));
      else if (property == "enabletransferdelay")
        (*current_liboctave_error_handler) ("can not set this property");
      else
        (*current_liboctave_error_handler) ("invalid property name");
    }

#endif
    /* never reached in normal operation */
  (*current_liboctave_error_handler) ("Your system doesn't support the TCP interface");
}
#if 0
%!shared ip
%! ip = resolvehost("www.octave.org", "address");

%!test
%! # test get
%! a = tcpclient (ip, 80);
%! assert (__tcpclient_properties__ (a,"type"), "tcpclient");
%! assert (__tcpclient_properties__ (a,"port"), 80);
%! assert (__tcpclient_properties__ (a,"address"), ip);
%! assert (__tcpclient_properties__ (a,"timeout"), -1);
%! assert (__tcpclient_properties__ (a,"status"), "open");
%! assert (__tcpclient_properties__ (a,"name"), ["TCP-" ip]);
%! fail ("__tcpclient_properties__ (a,'invalid')", "invalid property name");
%! clear a

%!test
%! # test set
%! a = tcpclient(ip, 80);
%! __tcpclient_properties__ (a, 'name', "mytest");
%! assert (__tcpclient_properties__ (a,"name"), "mytest");
%! fail ("__tcpclient_properties__ (a,'invalid', 1)", "invalid property name");
%! clear a

%!test
%! # test flush
%! a = tcpclient(ip, 80);
%! __tcpclient_properties__ (a, 'flush', 0);
%! __tcpclient_properties__ (a, 'flush', 1);
%! __tcpclient_properties__ (a, 'flush', 2);
%! fail ("__tcpclient_properties__ (a,'flush')", "invalid property name");
%! clear a


%!error <wrong number of arguments> __tcpclient_properties__ ()

%!error <wrong number of arguments> __tcpclient_properties__ (1)

%!test
%! a = tcpclient (ip, 80);
%! fail ("__tcpclient_properties__ (a, 'name', 'test', 0)", "wrong number of arguments");
%! clear a

#endif
