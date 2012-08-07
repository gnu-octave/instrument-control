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

// PKG_ADD: autoload ("srl_parity", "serial.oct");
DEFUN_DLD (srl_parity, args, nargout, "Hello World Help String")
{
    if (args.length() < 1 || args.length() > 2)
    {
        error("srl_parity: expecting one or two arguments...");
        return octave_value(-1);
    }

    if (args(0).type_id() != octave_serial::static_type_id())
    {
        error("srl_parity: expecting first argument of type octave_serial...");
        return octave_value(-1);
    }

    // Setting new parity
    if (args.length() > 1)
    {
        if ( !(args(1).is_string()) )
        {
            error("srl_parity: expecting second argument of type string...");
            return octave_value(-1);
        }

        octave_serial* serial = NULL;

        const octave_base_value& rep = args(0).get_rep();
        serial = &((octave_serial &)rep);

        serial->srl_parity(args(1).string_value());

        return octave_value();
    }

    // Returning current parity
    // TODO: return current parity

    return octave_value("-N");
}

int octave_serial::srl_parity(string parity)
{
    // Convert string to lowercase
    std::transform(parity.begin(), parity.end(), parity.begin(), ::tolower);

    /*
     * PARENB Enable parity generation on output and parity checking for input.
     * PARODD If set, then parity for input and output is odd; otherwise even parity is used.
     */

    if (parity == "n" || parity == "none")
    {
        // Disable parity generation/checking
        BITMASK_CLEAR(this->config.c_cflag, PARENB);
    }
    else if (parity == "e" || parity == "even")
    {
        // Enable parity generation/checking
        BITMASK_SET(this->config.c_cflag, PARENB);

        // Set to Even
        BITMASK_CLEAR(this->config.c_cflag, PARODD);

    }
    else if (parity == "o" || parity == "odd")
    {
        // Enable parity generation/checking
        BITMASK_SET(this->config.c_cflag, PARENB);

        // Set to Odd
        BITMASK_SET(this->config.c_cflag, PARODD);

    }
    else
    {
        error("srl_parity: Only [N]one, [E]ven or [O]dd parities are supported...");
        return false;
    }

    if (tcsetattr(this->srl_get_fd(), TCSANOW, &this->config) < 0) {
        error("srl_parity: error setting parity...");
        return false;
    }

    return true;
}