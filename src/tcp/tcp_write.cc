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

#ifdef BUILD_TCP
#include "tcp_class.h"

static bool type_loaded = false;
#endif

DEFUN_DLD (tcp_write, args, nargout,
        "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{n} = } tcp_write (@var{tcp}, @var{data})\n \
\n\
Write data to a tcp interface.\n \
\n\
@var{tcp} - instance of @var{octave_tcp} class.@* \
@var{data} - data to be written to the tcp interface. Can be either of String or uint8 type.\n \
\n\
Upon successful completion, tcp_write() shall return the number of bytes written as the result @var{n}.\n \
@end deftypefn")
{
#ifndef BUILD_TCP
    error("tcp: Your system doesn't support the TCP interface");
    return octave_value();
#else
    if (!type_loaded)
    {
        octave_tcp::register_type();
        type_loaded = true;
    }

    if (args.length() != 2 || args(0).type_id() != octave_tcp::static_type_id())
    {
        print_usage();
        return octave_value(-1);
    }

    octave_tcp *tcp = NULL;
    int retval;

    const octave_base_value& rep = args(0).get_rep();
    tcp = &((octave_tcp &)rep);

    if (args(1).is_string()) // String
    {
        retval = tcp->write(args(1).string_value());
    }
    else if (args(1).is_uint8_type ())
    {
        NDArray data = args(1).array_value();
        uint8_t *buf = NULL;
        buf = new uint8_t[data.numel()];

        // memcpy?
        if (buf == NULL)
        {
            error("tcp_write: cannot allocate requested memory");
            return octave_value(-1);
        }

        for (int i = 0; i < data.numel(); i++)
            buf[i] = static_cast<uint8_t>(data(i));

        retval = tcp->write(buf, data.numel());

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
%!error <Invalid call to tcp_write> tcp_write(1, uint8([104  101  108  108  111]))

%!error <Invalid call to tcp_write> tcp_write()

%!test
%! addr = resolvehost('gnu.org', 'address');
%! a = tcp(addr, 80);;
%! # call HTTP HEAD
%! req = "HEAD / HTTP/1.1\r\n\r\n";
%! assert(length(req), tcp_write(a, req));
%! [d, c] = tcp_read(a, 12, 5000);
%! tcp_close(a);
%! assert(12, c);
%! assert(c, length(d));
#endif

