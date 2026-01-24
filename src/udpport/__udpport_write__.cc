// Copyright (C) 2021 John Donoghue <john.donoghue@ieee.org>
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

#ifdef HAVE_CONFIG_H
#  include "../config.h"
#endif

#ifdef BUILD_UDP
#  include "udpport_class.h"
#endif

// PKG_ADD: autoload ("__udpport_write__", "udpport.oct");
DEFUN_DLD (__udpport_write__, args, nargout,
        "-*- texinfo -*-\n\
@deftypefn {} {@var{n} = } __udpport_write__ (@var{udpport}, @var{data})\n \
@deftypefnx {} {@var{n} = } __udpport_write__ (@var{udpport}, @var{data}, @var{destipaddress}, @var{destport})\n \
\n\
Provate function to write data to a udpport interface.\n \
\n\
@subsubheading Inputs\n \
@var{udpport} - instance of @var{octave_udpport} class.@* \
@var{data} - data to be written to the udpport interface. Can be either of String or uint8 type.\n \
@var{destipaddress} - ip address to write to.@* \
@var{destport} - port number to write to.\n \
\n\
If @var{destipaddress}, @var{destport} is not provided, write will go to the address configure from the udpport\n \
creation or last used for write.\n \
\n\
@subsubheading Outputs\n \
Upon successful completion, __udpport_write__() shall return the number of bytes written as the result @var{n}.\n \
@end deftypefn")
{
#ifndef BUILD_UDP
  error("udpport: Your system doesn't support the UDP interface");
  return octave_value();
#else
  if ((args.length() != 2 && args.length() != 4) || args(0).type_id() != octave_udpport::static_type_id())
    {
      print_usage();
      return octave_value(-1);
    }

  octave_udpport *udpport = NULL;
  int retval;

  const octave_base_value& rep = args(0).get_rep();
  udpport = &((octave_udpport &)rep);

  std::string destip = "";
  int destport = 0;

  if (args.length() == 4)
    {
      if (!args(2).is_string())
        {
          error("udpport_write: expected destipaddress as a string");
          return octave_value(-1);
        }
      if ( !(args(3).OV_ISINTEGER() || args(3).OV_ISFLOAT()))
        {
          error("udpport_write: expected destport as a integer");
          return octave_value(-1);
        }

      destip = args(2).string_value();
      destport = args(3).int_value();
    }

  if (args(1).is_string()) // String
    {
      retval = udpport->write(args(1).string_value(), destip, destport);
    }
  else if (args(1).is_uint8_type ())
    {
      NDArray data = args(1).array_value();
      OCTAVE_LOCAL_BUFFER (uint8_t, buf, (data.numel ()));

      // memcpy?
      if (buf == NULL)
        {
          error("udpport_write: cannot allocate requested memory");
          return octave_value(-1);
        }

      for (int i = 0; i < data.numel(); i++)
        buf[i] = static_cast<uint8_t>(data(i));

      retval = udpport->write(buf, data.numel(), destip, destport);

    }
  else
    {
      print_usage();
      return octave_value(-1);
    }

  return octave_value(retval);
#endif
}

#if 0
%!test
%! a = udpport ();
%! b = udpport ();
%! port = get (b, 'LocalPort');
%! assert (5, __udpport_write__ (a, uint8 ([104  101  108  108  111]), "127.0.0.1", port));
%! [d, c] = __udpport_read__ (b, 5, 1000);
%! assert (c, 5);
%! assert (d, uint8 ([104  101  108  108  111]));
%! clear a;
%! clear b;

%!error <Invalid call to __udpport_write__> __udpport_write__ (1, uint8([104  101  108  108  111]))

%!error <Invalid call to __udpport_write__> __udpport_write__ ()

%!test
%! a = udpport ();
%! fail ("__udpport_write__ (a, uint8([104  101  108  108  111]), 0)", "Invalid call to __udpport_write__")
%! clear a;

%!test
%! a = udpport ();
%! fail ("__udpport_write__ (a)", "Invalid call to __udpport_write__")
%! clear a;
#endif

