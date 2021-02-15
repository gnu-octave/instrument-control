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

#ifdef BUILD_UDP
#  include "udpport_class.h"
#endif

static octave_value_list get_terminator (octave_udpport* udp)
{
  // may have a single terminator or a start and stop
  std::string in = udp->get_input_terminator ();
  std::string out = udp->get_output_terminator ();

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

static octave_value set_terminator(octave_udpport* udp, const octave_value_list& args)
{
  if (args.length () == 1)
    {
      if ( !(args (0).is_string ()) )
        (*current_liboctave_error_handler) ("argument must be a string");

      udp->set_input_terminator (args (0).string_value());
      udp->set_output_terminator (args (0).string_value());

      return octave_value (); // Should it return by default?
    }
  else if (args.length () == 2)
    {
      if ( !(args (0).is_string ()) )
        (*current_liboctave_error_handler) ("argument must be a string");
      if ( !(args (1).is_string ()) )
        (*current_liboctave_error_handler) ("argument must be a string");

      udp->set_input_terminator (args (0).string_value());
      udp->set_output_terminator (args (1).string_value());

      return octave_value (); // Should it return by default?
    }
  else if (args.length () > 2)
    (*current_liboctave_error_handler) ("wrong number of arguments");

  return octave_value();
}

// PKG_ADD: autoload ("__udpport_properties__", "udpport.oct");
DEFUN_DLD (__udpport_properties__, args, nargout,
"-*- texinfo -*-\n\
@deftypefn {Loadable Function} {varargout =} __udpport_properties__ (@var{octave_udpport}, @var{property}, @var{varargin})\n\
Undocumented internal function.\n\
@end deftypefn")
{
#ifdef BUILD_UDP
  if (args.length () < 2 || args.length () > 3 ||
    args(0).type_id () != octave_udpport::static_type_id () || 
    !args(1).is_string ())
      (*current_liboctave_error_handler) ("wrong number of arguments");
    
  const octave_base_value& rep = args(0).get_rep ();
  octave_udpport* udpport = &((octave_udpport &)rep);
    
  std::string property = args(1).string_value ();
  std::transform (property.begin (), property.end (), property.begin (), ::tolower);

  if (args.length () == 2) // get
    {
      if (property == "name")
        return octave_value (udpport->get_name ());
      else if (property == "type")
        return octave_value (udpport->get_type ());
      else if (property == "remoteport")
        return octave_value (udpport->get_remote_port ());
      else if (property == "remotehost")
        return octave_value (udpport->get_remote_addr ());
      else if (property == "localport")
        return octave_value (udpport->get_local_port ());
      else if (property == "localhost")
        return octave_value (udpport->get_local_addr ());
      else if (property == "status")
        return octave_value (udpport->get_status ());
      else if (property == "timeout")
        return octave_value (udpport->get_timeout ());
      else if (property == "numbytesavailable")
        return octave_value (udpport->get_bytesavailable ());
      else if (property == "numbyteswritten")
        return octave_value (udpport->get_byteswritten ());
      else if (property == "userdata")
        return octave_value (udpport->get_userdata ());
      else if (property == "terminator")
        return get_terminator (udpport);
      else if (property == "multicastgroup")
        return octave_value (udpport->get_multicastgroup ());
      else if (property == "enablemulticast")
        return octave_value (udpport->get_multicastgroup ().length () > 0 ? 1 : 0);
      else if (property == "enablemulticastloopback")
        return octave_value (udpport->get_multicastloopback ()); 
      else if (property == "enableportsharing")
        return octave_value (udpport->get_enableportsharing ()); 
      else if (property == "enablebroadcast")
        return octave_value (udpport->get_enablebroadcast ()); 
      else if (property == "ipaddressversion")
        return octave_value (udpport->get_ipaddressversion ()); 
      else if (property == "byteorder")
        return octave_value (udpport->get_byteorder ()); 
      else
        (*current_liboctave_error_handler) ("invalid property name");
    }
  else // set
    {
      if (property == "name")
        return octave_value (udpport->set_name (args(2).string_value ()));
      else if (property == "type")
        (*current_liboctave_error_handler) ("can not set this property");
      else if (property == "localport")
        (*current_liboctave_error_handler) ("can not set this property");
      else if (property == "localhost")
        (*current_liboctave_error_handler) ("can not set this property");
      else if (property == "status")
        (*current_liboctave_error_handler) ("can not set this property");
      else if (property == "timeout")
        return octave_value (udpport->set_timeout (args(2).double_value ()));
      else if (property == "flush")
        return octave_value (udpport->flush (args(2).int_value ()));
      else if (property == "terminator")
        return set_terminator (udpport, args.slice (2, args.length ()-2));
      else if (property == "userdata")
        { udpport->set_userdata (args(2)); return octave_value(); } 
      else if (property == "multicastgroup")
        return octave_value (udpport->set_multicastgroup (args(2).string_value ()));
      else if (property == "byteorder")
        return octave_value (udpport->set_byteorder (args(2).string_value ())); 
      else if (property == "enablemulticastloopback")
        return octave_value (udpport->set_multicastloopback (args(2).int_value ()));
      else if (property == "enablebroadcast")
        return octave_value (udpport->set_enablebroadcast (args(2).int_value ()));
      else
        (*current_liboctave_error_handler) ("invalid property name");
    }

#endif
    /* never reached in normal operation */
  (*current_liboctave_error_handler) ("Your system doesn't support the UDP interface");
}
#if 0
%!test
%! # test get
%! a = udpport ();
%! assert (__udpport_properties__ (a,"type"), "udpport");
%! assert (__udpport_properties__ (a,"timeout"), -1);
%! assert (__udpport_properties__ (a,"status"), "open");
%! assert (__udpport_properties__ (a,"name"), "UDP-0.0.0.0");
%! fail ("__udpport_properties__ (a,'invalid')", "invalid property name");
%! clear a;

%!test
%! # test set
%! a = udpport();
%! __udpport_properties__ (a, 'name', "mytest");
%! assert (__udpport_properties__ (a,"name"), "mytest");
%! fail ("__udpport_properties__ (a,'invalid', 1)", "invalid property name");
%! clear a;

%!test
%! # test flush
%! a = udpport();
%! __udpport_properties__ (a, 'flush', 0);
%! __udpport_properties__ (a, 'flush', 1);
%! __udpport_properties__ (a, 'flush', 2);
%! fail ("__udpport_properties__ (a,'flush')", "invalid property name");
%! clear a;

%!test
%! # test subsref and get/set
%! a = udpport ();
%! a.Name = "test1";
%! assert (isa(a, "octave_udpport"));
%! assert (a.Name, "test1");
%! assert (get(a, 'Name'), "test1");
%!
%! set (a, "Name", "test2");
%! assert (a.Name, "test2");
%! assert (get(a, 'Name'), "test2");
%! assert (__udpport_properties__ (a,"Name"), "test2");
%! clear a

%!error <wrong number of arguments> __udpport_properties__ ()

%!error <wrong number of arguments> __udpport_properties__ (1)

%!test
%! a = udpport ();
%! fail ("__udpport_properties__ (a, 'Name', 'test', 0)", "wrong number of arguments");
%! clear a;

#endif
