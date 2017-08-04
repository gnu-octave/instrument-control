// Copyright (C) 2013   Stefan Mahr     <dac922@gmx.de>
// Copyright (C) 2012   Andrius Sutas   <andrius.sutas@gmail.com>
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
#include "../config.h"
#endif

#ifdef BUILD_UDP
#include "udp_class.h"

static bool type_loaded = false;
#endif

DEFUN_DLD (udp_write, args, nargout,
        "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{n} = } udp_write (@var{udp}, @var{data})\n \
\n\
Write data to a udp interface.\n \
\n\
@var{udp} - instance of @var{octave_udp} class.@* \
@var{data} - data to be written to the udp interface. Can be either of String or uint8 type.\n \
\n\
Upon successful completion, udp_write() shall return the number of bytes written as the result @var{n}.\n \
@end deftypefn")
{
#ifndef BUILD_UDP
    error("udp: Your system doesn't support the UDP interface");
    return octave_value();
#else
    if (!type_loaded)
    {
        octave_udp::register_type();
        type_loaded = true;
    }

    if (args.length() != 2 || args(0).type_id() != octave_udp::static_type_id())
    {
        print_usage();
        return octave_value(-1);
    }

    octave_udp *udp = NULL;
    int retval;

    const octave_base_value& rep = args(0).get_rep();
    udp = &((octave_udp &)rep);

    if (args(1).is_string()) // String
    {
        retval = udp->write(args(1).string_value());
    }
    else if (args(1).is_uint8_type ())
    {
        NDArray data = args(1).array_value();
        uint8_t *buf = NULL;
        buf = new uint8_t[data.numel()];

        // memcpy?
        if (buf == NULL)
        {
            error("udp_write: cannot allocate requested memory");
            return octave_value(-1);
        }

        for (int i = 0; i < data.numel(); i++)
            buf[i] = static_cast<uint8_t>(data(i));

        retval = udp->write(buf, data.numel());

        delete[] buf;
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
%! a = udp();
%! b = udp();
%! p = get(a, 'localport');
%! set(b, 'remoteport', p);
%! p = get(b, 'localport');
%! set(a, 'remoteport', p);
%! assert(5, udp_write(a, uint8([104  101  108  108  111])));
%! [d, c] = udp_read(b, 5, 1000);
%! assert(c, 5);
%! assert(d, uint8([104  101  108  108  111]));
%! udp_close(a);
%! udp_close(b);

%!error <Invalid call to udp_write> udp_write(1, uint8([104  101  108  108  111]))

%!error <Invalid call to udp_write> udp_write()

%!test
%! a = udp();
%! fail ("udp_write(a, uint8([104  101  108  108  111]), 0)", "Invalid call to udp_write")
%! udp_close(a);

%!test
%! a = udp();
%! fail ("udp_write(a)", "Invalid call to udp_write")
%! udp_close(a);
#endif

