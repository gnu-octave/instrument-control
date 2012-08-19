#include <octave/oct.h>
#include <octave/ov-int32.h>
//#include <octave/ops.h>
//#include <octave/ov-typeinfo.h>

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

// PKG_ADD: autoload ("srl_baudrate", "serial.oct");
DEFUN_DLD (srl_baudrate, args, nargout, "Hello World Help String")
{
    if (args.length() < 1 || args.length() > 2 ||
        args(0).type_id() != octave_serial::static_type_id())
    {
        print_usage();
        return octave_value(-1);
    }

    // Setting new baudrate
    if (args.length() > 1)
    {
        if ( !(args(1).is_integer_type() || args(1).is_float_type()) )
        {
            error("srl_baudrate: expecting second argument of type integer...");
            return octave_value(-1);
        }

        octave_serial* serial = NULL;

        const octave_base_value& rep = args(0).get_rep();
        serial = &((octave_serial &)rep);

        serial->srl_baudrate(args(1).int_value());

        return octave_value();
    }

    // Returning current baud rate
    // TODO: return current baudrate

    return octave_value(-115200);
}

int octave_serial::srl_baudrate(unsigned int baud) 
{
    speed_t baud_rate = 0;

    switch (baud) 
    {
    case 0: 
        baud_rate = B0; break;
    case 50:
        baud_rate = B50; break;
    case 75:
        baud_rate = B75; break;
    case 110:
        baud_rate = B110; break;
    case 134:
        baud_rate = B134; break;
    case 150:
        baud_rate = B150; break;
    case 200:
        baud_rate = B200; break;
    case 300:
        baud_rate = B300; break;
    case 600:
        baud_rate = B600; break;
    case 1200:
        baud_rate = B1200; break;
    case 1800:
        baud_rate = B1800; break;
    case 2400:
        baud_rate = B2400; break;
    case 4800:
        baud_rate = B4800; break;
    case 9600:
        baud_rate = B9600; break;
    case 19200:
        baud_rate = B19200; break;
    case 38400:
        baud_rate = B38400; break;
    case 57600:
        baud_rate = B57600; break;
    case 115200:
        baud_rate = B115200; break;
    case 230400:
        baud_rate = B230400; break;
    default:
        error("srl_baudrate: currently only standard baud rates are supported...");
        return false;
    }

    cfsetispeed(&this->config, baud_rate);
    cfsetospeed(&this->config, baud_rate);

    if (tcsetattr(this->srl_get_fd(), TCSANOW, &this->config) < 0) {
        error("srl_baudrate: error setting baud rate...");
        return false;
    }

    return true;
}