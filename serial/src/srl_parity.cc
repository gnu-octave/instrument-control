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
DEFUN_DLD (srl_parity, args, nargout,
"-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} srl_parity (@var{serial}, @var{parity})\n \
@deftypefnx {Loadable Function} {@var{p} = } srl_parity (@var{serial})\n \
\n\
Set new or get existing serial interface parity parameter. Even/Odd/None values are supported.\n \
\n\
@var{serial} - instance of @var{octave_serial} class.@*\
@var{parity} - parity value of type String. Supported values: Even/Odd/None (case insensitive, can be abbreviated to the first letter only).\n \
\n\
If @var{parity} parameter is omitted, the srl_parity() shall return current parity value as the result @var{p}.\n \
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

    // Setting new parity
    if (args.length() > 1)
    {
        if ( !(args(1).is_string()) )
        {
            print_usage();
            return octave_value(-1);
        }

        serial->set_parity(args(1).string_value());

        return octave_value();
    }

    // Returning current parity
    return octave_value(serial->get_parity());
}

int octave_serial::set_parity(string parity)
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

    if (tcsetattr(this->get_fd(), TCSANOW, &this->config) < 0) {
        error("srl_parity: error setting parity: %s\n", strerror(errno));
        return false;
    }

    return true;
}

string octave_serial::get_parity()
{
    if (!BITMASK_CHECK(this->config.c_cflag, PARENB))
        return "None";
    else if (BITMASK_CHECK(this->config.c_cflag, PARODD))
        return "Odd";
    else
        return "Even";
}