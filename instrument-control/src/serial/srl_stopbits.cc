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
#include <octave/ov-int32.h>

#include <iostream>
#include <string>
#include <algorithm>

#ifndef __WIN32__
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#endif

using std::string;

#include "serial.h"

// PKG_ADD: autoload ("srl_stopbits", "instrument-control.oct");
DEFUN_DLD (srl_stopbits, args, nargout, 
"-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} srl_stopbits (@var{serial}, @var{stopb})\n \
@deftypefnx {Loadable Function} {@var{sb} = } srl_stopbits (@var{serial})\n \
\n\
Set new or get existing serial interface stop bits parameter. Only 1 or 2 stop bits are supported.\n \
\n\
@var{serial} - instance of @var{octave_serial} class.@*\
@var{stopb} - number of stop bits used. Supported values: 1, 2.\n \
\n\
If @var{stopb} parameter is omitted, the srl_stopbits() shall return current stop bits value as the result @var{sb}.\n \
@end deftypefn")
{
    if (args.length() < 1 || args.length() > 2 || args(0).type_id() != octave_serial::static_type_id())
    {
        print_usage();
        return octave_value(-1);
    }

    octave_serial* serial = NULL;

    const octave_base_value& rep = args(0).get_rep();
    serial = &((octave_serial &)rep);

    // Setting new stop bits
    if (args.length() > 1)
    {
        if ( !(args(1).is_integer_type() || args(1).is_float_type()) )
        {
            print_usage();
            return octave_value(-1);
        }

        serial->set_stopbits(args(1).int_value());

        return octave_value();
    }

    // Returning current stop bits
    return octave_value(serial->get_stopbits());
}

int octave_serial::set_stopbits(unsigned short stopbits)
{
    /*
     * CSTOPB Send two stop bits, else one.
     */

    if (stopbits == 1)
    {
        // Set to one stop bit
        BITMASK_CLEAR(this->config.c_cflag, CSTOPB);
    }
    else if (stopbits == 2)
    {
        // Set to two stop bits
        BITMASK_SET(this->config.c_cflag, CSTOPB);
    }
    else
    {
        error("srl_stopbits: Only 1 or 2 stop bits are supported...");
        return false;
    }

    if (tcsetattr(this->get_fd(), TCSANOW, &this->config) < 0) {
        error("srl_stopbits: error setting stop bits: %s\n", strerror(errno));
        return false;
    }

    return true;
}

int octave_serial::get_stopbits()
{
    if (BITMASK_CHECK(this->config.c_cflag, CSTOPB))
        return 2;
    else
        return 1;
}