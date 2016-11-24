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
#include "udp_class.h"

static bool type_loaded = false;
#endif

DEFUN_DLD (udp_close, args, nargout,
"-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} udp_close (@var{udp})\n \
\n\
Close the interface and release a file descriptor.\n \
\n\
@var{udp} - instance of @var{octave_udp} class.\n \
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

    if (args.length() != 1 || args(0).type_id() != octave_udp::static_type_id())
    {
        print_usage();
        return octave_value(-1);
    }

    octave_udp* udp = NULL;

    const octave_base_value& rep = args(0).get_rep();
    udp = &((octave_udp &)rep);

    udp->close();

    return octave_value();
#endif
}
