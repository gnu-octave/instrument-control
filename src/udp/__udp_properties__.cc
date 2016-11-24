// Copyright (C) 2012   Andrius Sutas   <andrius.sutas@gmail.com>
// Copyright (C) 2014   Stefan Mahr     <dac922@gmx.de>
// Copyright (C) 2016   John Donoghue   <john.donoghue@ieee.org>
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

#ifdef BUILD_UDP
#include "udp_class.h"

static bool type_loaded = false;
#endif


DEFUN_DLD (__udp_properties__, args, nargout,
"-*- texinfo -*-\n\
@deftypefn {Loadable Function} {varargout =} __udp_properties__ (@var{octave_udp}, @var{property}, @var{varargin})\n\
Undocumented internal function.\n\
@end deftypefn")
{
#ifdef BUILD_UDP
  if (!type_loaded)
    {
      octave_udp::register_type();
      type_loaded = true;
    }

  if (args.length () < 2 || args.length () > 3 ||
    args(0).type_id () != octave_udp::static_type_id () || 
    !args(1).is_string ())
      (*current_liboctave_error_handler) ("wrong number of arguments");
    
  const octave_base_value& rep = args(0).get_rep ();
  octave_udp* udp = &((octave_udp &)rep);
    
  string property = args(1).string_value ();

  if (args.length () == 2) // get
    {
      if (property == "name")
        return octave_value (udp->get_name ());
      else if (property == "type")
        return octave_value (udp->get_type ());
      else if (property == "remoteport")
        return octave_value (udp->get_remote_port ());
      else if (property == "remotehost")
        return octave_value (udp->get_remote_addr ());
      else if (property == "localport")
        return octave_value (udp->get_local_port ());
      else if (property == "status")
        return octave_value (udp->get_status ());
      else if (property == "timeout")
        return octave_value (udp->get_timeout ());
      else
        (*current_liboctave_error_handler) ("invalid property name");
    }
  else // set
    {
      if (property == "name")
        return octave_value (udp->set_name (args(2).string_value ()));
      else if (property == "type")
        (*current_liboctave_error_handler) ("can not set this property");
      else if (property == "remoteport")
        return octave_value (udp->set_remote_port (args(2).int_value ()));
      else if (property == "remotehost")
        return octave_value (udp->set_remote_addr (args(2).string_value ()));
      else if (property == "localport")
        (*current_liboctave_error_handler) ("can not set this property");
      else if (property == "status")
        (*current_liboctave_error_handler) ("can not set this property");
      else if (property == "timeout")
        return octave_value (udp->set_timeout (args(2).int_value ()));
      else
        (*current_liboctave_error_handler) ("invalid property name");
    }

#endif
    /* never reached in normal operation */
  (*current_liboctave_error_handler) ("Your system doesn't support the UDP interface");
}
