// Copyright (C) 2012   Andrius Sutas   <andrius.sutas@gmail.com>
// Copyright (C) 2014   Stefan Mahr     <dac922@gmx.de>
// Copyright (C) 2016   John Donoghue   <john.donoghue@ieee.org>
// Copyright (C) 2018-2019   John Donoghue   <john.donoghue@ieee.org>
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
#  include "tcp_class.h"
#endif


// PKG_ADD: autoload ("__tcp_properties__", "tcp.oct");
DEFUN_DLD (__tcp_properties__, args, nargout,
"-*- texinfo -*-\n\
@deftypefn {Loadable Function} {varargout =} __tcp_properties__ (@var{octave_tcp}, @var{property}, @var{varargin})\n\
Undocumented internal function.\n\
@end deftypefn")
{
#ifdef BUILD_TCP
  if (args.length () < 2 || args.length () > 3 ||
    args(0).type_id () != octave_tcp::static_type_id () || 
    !args(1).is_string ())
      (*current_liboctave_error_handler) ("wrong number of arguments");
    
  const octave_base_value& rep = args(0).get_rep ();
  octave_tcp* tcp = &((octave_tcp &)rep);
    
  std::string property = args(1).string_value ();

  if (args.length () == 2) // get
    {
      if (property == "name")
        return octave_value (tcp->get_name ());
      else if (property == "type")
        return octave_value (tcp->get_type ());
      else if (property == "remoteport")
        return octave_value (tcp->get_remote_port ());
      else if (property == "remotehost")
        return octave_value (tcp->get_remote_addr ());
      else if (property == "localport")
        return octave_value (tcp->get_local_port ());
      else if (property == "status")
        return octave_value (tcp->get_status ());
      else if (property == "timeout")
        return octave_value (tcp->get_timeout ());
      else if (property == "bytesavailable")
        return octave_value (tcp->get_bytesavailable ());
      else
        (*current_liboctave_error_handler) ("invalid property name");
    }
  else // set
    {
      if (property == "name")
        return octave_value (tcp->set_name (args(2).string_value ()));
      else if (property == "type")
        (*current_liboctave_error_handler) ("can not set this property");
      else if (property == "remoteport")
        (*current_liboctave_error_handler) ("can not set this property");
      else if (property == "remotehost")
        (*current_liboctave_error_handler) ("can not set this property");
      else if (property == "localport")
        (*current_liboctave_error_handler) ("can not set this property");
      else if (property == "status")
        (*current_liboctave_error_handler) ("can not set this property");
      else if (property == "timeout")
        return octave_value (tcp->set_timeout (args(2).double_value ()));
      else if (property == "flush")
        return octave_value (tcp->flush (args(2).int_value ()));
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
%! a = tcp (ip, 80);
%! assert (__tcp_properties__ (a,"type"), "tcp");
%! assert (__tcp_properties__ (a,"remoteport"), 80);
%! assert (__tcp_properties__ (a,"remotehost"), ip);
%! assert (__tcp_properties__ (a,"timeout"), -1);
%! assert (__tcp_properties__ (a,"status"), "open");
%! assert (__tcp_properties__ (a,"name"), ["TCP-" ip]);
%! fail ("__tcp_properties__ (a,'invalid')", "invalid property name");
%! tcp_close (a);
%! assert (__tcp_properties__ (a,"status"), "closed");

%!test
%! # test set
%! a = tcp(ip, 80);
%! __tcp_properties__ (a, 'name', "mytest");
%! assert (__tcp_properties__ (a,"name"), "mytest");
%! fail ("__tcp_properties__ (a,'invalid', 1)", "invalid property name");
%! tcp_close (a);

%!test
%! # test flush
%! a = tcp(ip, 80);
%! __tcp_properties__ (a, 'flush', 0);
%! __tcp_properties__ (a, 'flush', 1);
%! __tcp_properties__ (a, 'flush', 2);
%! fail ("__tcp_properties__ (a,'flush')", "invalid property name");
%! tcp_close (a);


%!error <wrong number of arguments> __tcp_properties__ ()

%!error <wrong number of arguments> __tcp_properties__ (1)

%!test
%! a = tcp (ip, 80);
%! fail ("__tcp_properties__ (a, 'name', 'test', 0)", "wrong number of arguments");
%! tcp_close (a);

#endif
