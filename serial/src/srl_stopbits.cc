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
//#include <octave/ops.h>
//#include <octave/ov-typeinfo.h>

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

// PKG_ADD: autoload ("srl_stopbits", "serial.oct");
DEFUN_DLD (srl_stopbits, args, nargout, "Hello World Help String")
{
    if (args.length() < 1 || args.length() > 2)
    {
        error("srl_stopbits: expecting one or two arguments...");
        return octave_value(-1);
    }

    if (args(0).type_id() != octave_serial::static_type_id())
    {
        error("srl_stopbits: expecting first argument of type octave_serial...");
        return octave_value(-1);
    }

    // Setting new stop bits
    if (args.length() > 1)
    {
        if ( !(args(1).is_integer_type() || args(1).is_float_type()) )
        {
            error("srl_stopbits: expecting second argument of type integer...");
            return octave_value(-1);
        }

        octave_serial* serial = NULL;

        const octave_base_value& rep = args(0).get_rep();
        serial = &((octave_serial &)rep);

        serial->srl_stopbits(args(1).int_value());

        return octave_value();
    }

    // Returning current stop bits

    // TODO: return current stop bits

    return octave_value(-1);
}

int octave_serial::srl_stopbits(unsigned short stopbits)
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

    if (tcsetattr(this->srl_get_fd(), TCSANOW, &this->config) < 0) {
        error("srl_stopbits: error setting stop bits...");
        return false;
    }

    return true;
}