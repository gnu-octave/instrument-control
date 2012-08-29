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

// PKG_ADD: autoload ("srl_flush", "serial.oct");
DEFUN_DLD (srl_flush, args, nargout, "Hello World Help String")
{
    int queue_selector = 2; // Input and Output

    if (args.length() < 1 || args.length() > 2 || args(0).type_id() != octave_serial::static_type_id()) 
    {
        print_usage();
        return octave_value(-1);
    }

    if (args.length() > 1)
    {
        if (!(args(1).is_integer_type() || args(1).is_float_type()))
        {
            print_usage();
            return octave_value(-1);
        }

        queue_selector = args(1).int_value();
    }

    octave_serial* serial = NULL;

    const octave_base_value& rep = args(0).get_rep();
    serial = &((octave_serial &)rep);

    serial->srl_flush(queue_selector);

    return octave_value();
}

int octave_serial::srl_flush(unsigned short queue_selector)
{
    /*
     * TCIOFLUSH Flush both pending input and untransmitted output.
     * TCOFLUSH Flush untransmitted output.
     * TCIFLUSH Flush pending input.
     */

    int flag;

    switch (queue_selector)
    {
    case 0: flag = TCOFLUSH; break;
    case 1: flag = TCIFLUSH; break;
    case 2: flag = TCIOFLUSH; break;
    default:
        error("srl_flush: only [0..2] values are accepted...");
        return false;
    }

    return ::tcflush(this->srl_get_fd(), flag);
}