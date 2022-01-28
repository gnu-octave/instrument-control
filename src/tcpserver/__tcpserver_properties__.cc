// Copyright (C) 2022   John Donoghue   <john.donoghue@ieee.org>
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
#  include "tcpserver_class.h"
#endif

static octave_value_list get_terminator (octave_tcpserver* tcp)
{
  // may have a single terminator or a start and stop
  std::string in = tcp->get_input_terminator ();
  std::string out = tcp->get_output_terminator ();

  if (in == out)
    return octave_value (in);
  else
    {
      octave_value_list ret;
      ret(0) = octave_value(in);
      ret(1) = octave_value(out);
      return octave_value (ret);
    }
}

static octave_value set_terminator(octave_tcpserver* tcp, const octave_value_list& args)
{
  if (args.length () == 1)
    {
      if ( !(args (0).is_string ()) )
        (*current_liboctave_error_handler) ("argument must be a string");

      tcp->set_input_terminator (args (0).string_value());
      tcp->set_output_terminator (args (0).string_value());

      return octave_value (); // Should it return by default?
    }
  else if (args.length () == 2)
    {
      if ( !(args (0).is_string ()) )
        (*current_liboctave_error_handler) ("argument must be a string");
      if ( !(args (1).is_string ()) )
        (*current_liboctave_error_handler) ("argument must be a string");

      tcp->set_input_terminator (args (0).string_value());
      tcp->set_output_terminator (args (1).string_value());

      return octave_value (); // Should it return by default?
    }
  else if (args.length () > 2)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  return octave_value();
}

// PKG_ADD: autoload ("__tcpserver_properties__", "tcpserver.oct");
DEFUN_DLD (__tcpserver_properties__, args, nargout,
"-*- texinfo -*-\n\
@deftypefn {Loadable Function} {varargout =} __tcpserver_properties__ (@var{octave_tcpserver}, @var{property}, @var{varargin})\n\
Undocumented internal function.\n\
@end deftypefn")
{
#ifdef BUILD_TCP
  if (args.length () < 2 || args.length () > 3 ||
    args(0).type_id () != octave_tcpserver::static_type_id () || 
    !args(1).is_string ())
      (*current_liboctave_error_handler) ("wrong number of arguments");
    
  const octave_base_value& rep = args(0).get_rep ();
  octave_tcpserver* tcpserver = &((octave_tcpserver &)rep);
    
  std::string property = args(1).string_value ();
  std::transform (property.begin (), property.end (), property.begin (), ::tolower);

  if (args.length () == 2) // get
    {
      if (property == "name")
        return octave_value (tcpserver->get_name ());
      else if (property == "type")
        return octave_value (tcpserver->get_type ());
      else if (property == "serverport")
        return octave_value (tcpserver->get_port ());
      else if (property == "serveraddress")
        return octave_value (tcpserver->get_address ());
      else if (property == "clientport")
        return octave_value (tcpserver->get_client_port ());
      else if (property == "clientaddress")
        return octave_value (tcpserver->get_client_address ());
      else if (property == "status")
        return octave_value (tcpserver->get_status ());
      else if (property == "connected")
        return octave_value (tcpserver->get_connected ());
      else if (property == "timeout")
        return octave_value (tcpserver->get_timeout ());
      else if (property == "numbytesavailable")
        return octave_value (tcpserver->get_numbytesavailable ());
      else if (property == "numbyteswritten")
        return octave_value (tcpserver->get_numbyteswritten ());
      else if (property == "byteorder")
        return octave_value (tcpserver->get_byteorder ());
      else if (property == "userdata")
        return octave_value (tcpserver->get_userdata ());
      else if (property == "terminator")
        return get_terminator (tcpserver);
      else
        (*current_liboctave_error_handler) ("invalid property name");
    }
  else // set
    {
      if (property == "name")
        return octave_value (tcpserver->set_name (args(2).string_value ()));
      else if (property == "type")
        (*current_liboctave_error_handler) ("can not set this property");
      else if (property == "serverport")
        (*current_liboctave_error_handler) ("can not set this property");
      else if (property == "serveraddress")
        (*current_liboctave_error_handler) ("can not set this property");
      else if (property == "clientport")
        (*current_liboctave_error_handler) ("can not set this property");
      else if (property == "clientaddress")
        (*current_liboctave_error_handler) ("can not set this property");
      else if (property == "connected")
        (*current_liboctave_error_handler) ("can not set this property");
      else if (property == "status")
        (*current_liboctave_error_handler) ("can not set this property");
      else if (property == "timeout")
        return octave_value (tcpserver->set_timeout (args(2).double_value ()));
      else if (property == "userdata")
        { tcpserver->set_userdata (args(2)); return octave_value (); }
      else if (property == "byteorder")
        return octave_value (tcpserver->set_byteorder (args(2).string_value ()));
      else if (property == "flush")
        return octave_value (tcpserver->flush (args(2).int_value ()));
      else if (property == "terminator")
        return set_terminator (tcpserver, args.slice (2, args.length ()-2));
      else
        (*current_liboctave_error_handler) ("invalid property name");
    }

#endif
    /* never reached in normal operation */
  (*current_liboctave_error_handler) ("Your system doesn't support the TCP interface");
}
#if 0
%!test
%! # test get
%! a = tcpserver (0);
%! assert (__tcpserver_properties__ (a,"Type"), "tcpserver");
%! assert (__tcpserver_properties__ (a,"ServerPort") > 0);
%! assert (! isempty(__tcpserver_properties__ (a,"ServerAddress")));
%! assert (__tcpserver_properties__ (a,"Timeout"), -1);
%! assert (__tcpserver_properties__ (a,"Status"), "open");
%! assert (! isempty(__tcpserver_properties__ (a,"Name")));
%! assert (__tcpserver_properties__ (a,"Connected"), false);
%! fail ("__tcpserver_properties__ (a,'invalid')", "invalid property name");
%! clear a

%!test
%! # test set
%! a = tcpserver(0);
%! __tcpserver_properties__ (a, 'Name', "mytest");
%! assert (__tcpserver_properties__ (a,"Name"), "mytest");
%! assert (a.Name, "mytest");
%! fail ("__tcpserver_properties__ (a,'invalid', 1)", "invalid property name");
%! clear a

%!test
%! # test flush
%! a = tcpserver(0);
%! __tcpserver_properties__ (a, 'flush', 0);
%! __tcpserver_properties__ (a, 'flush', 1);
%! __tcpserver_properties__ (a, 'flush', 2);
%! fail ("__tcpserver_properties__ (a,'flush')", "invalid property name");
%! clear a

%!error <wrong number of arguments> __tcpserver_properties__ ()

%!error <wrong number of arguments> __tcpserver_properties__ (1)

%!test
%! a = tcpserver (0);
%! fail ("__tcpserver_properties__ (a, 'Name', 'test', 0)", "wrong number of arguments");
%! clear a

#endif
