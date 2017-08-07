// Copyright (C) 2016   John Donoghue   <john.donoghue@ieee.org>
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
#include <octave/uint8NDArray.h>
#include <octave/sighandlers.h>

#include <errno.h>

#include "udp_class.h"

#include "../octave-wrappers.h"

extern bool read_interrupt;
static bool type_loaded = false;

void read_sighandler(int sig)
{
    printf("udp_read: Interrupting...\n\r");
    read_interrupt = true;
}
#endif

DEFUN_DLD (udp_read, args, nargout,
        "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {[@var{data}, @var{count}] = } udp_read (@var{udp}, @var{n}, @var{timeout})\n \
\n\
Read from udp interface.\n \
\n\
@var{udp} - instance of @var{octave_udp} class.@* \
@var{n} - number of bytes to attempt to read of type Integer@* \
@var{timeout} - timeout in ms if different from default of type Integer\n \
\n\
The udp_read() shall return number of bytes successfully read in @var{count} as Integer and the bytes themselves in @var{data} as uint8 array.\n \
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

    if (args.length() < 2 || args.length() > 3 || args(0).type_id() != octave_udp::static_type_id())
    {
        print_usage();
        return octave_value(-1);
    }

    unsigned int buffer_len = 0;

    if ( !(args(1).is_integer_type() || args(1).is_float_type()))
    {
        print_usage();
        return octave_value(-1);
    }

    if ( args.length() > 2 )
    {
        if ( !(args(2).is_integer_type() || args(2).is_float_type()))
        {
            print_usage();
            return octave_value(-1);
        }
    }

    buffer_len = args(1).int_value();

    uint8_t *buffer = NULL;
    buffer = new uint8_t[buffer_len + 1];

    if (buffer == NULL)
    {
        error("udp_read: cannot allocate requested memory: %s\n", strerror(errno));
        return octave_value(-1);
    }

    octave_udp* udp = NULL;

    const octave_base_value& rep = args(0).get_rep();
    udp = &((octave_udp &)rep);

    int timeout = udp->get_timeout();
    if (args.length() == 3)
    {
        timeout = args(2).int_value();
    }

    // Register custom interrupt signal handler
    instrument_control::set_signal_handler(SIGINT, read_sighandler);
    read_interrupt = false;

    // Read data
    int bytes_read = udp->read(buffer, buffer_len, timeout);

    // Restore default signal handling
    // TODO: a better way?
    instrument_control::install_signal_handlers();

    // Convert data to octave type variables
    octave_value_list return_list;
    uint8NDArray data( dim_vector(1, bytes_read) );

    for (int i = 0; i < bytes_read; i++)
        data(i) = buffer[i];

    return_list(0) = data;
    return_list(1) = bytes_read;

    delete[] buffer;

    return return_list;
#endif
}

#if 0
%!test
%! a = udp();
%! assert(!isnull(a));
%! [d,c] = udp_read(a, 1, 0);
%! assert(c == 0);
%! assert(isempty(d));
%! udp_close(a);

%!error <Invalid call to udp_read> udp_read(1, 10, 0)

%!test
%! a = udp();
%! fail ("udp_read(a, 10, 0, 0)", "Invalid call to udp_read");
%! udp_close(a);

%!test
%! # does read wait
%! a = udp();
%! assert(!isnull(a));
%! tic;
%! [d,c] = udp_read(a, 1, 1000);
%! t = toc;
%! assert(c, 0);
%! assert(isempty(d));
%! assert(t, 1.0, 0.01)
%! udp_close(a);

#endif
