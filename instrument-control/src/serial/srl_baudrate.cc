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

// PKG_ADD: autoload ("srl_baudrate", "instrument-control.oct");
DEFUN_DLD (srl_baudrate, args, nargout, 
"-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} srl_baudrate (@var{serial}, @var{baudrate})\n \
@deftypefnx {Loadable Function} {@var{br} = } srl_baudrate (@var{serial})\n \
\n\
Set new or get existing serial interface baudrate parameter. Only standard values are supported.\n \
\n\
@var{serial} - instance of @var{octave_serial} class.@*\
@var{baudrate} - the baudrate value used. Supported values: 0, 50, 75, 110, \
134, 150, 200, 300, 600, 1200, 1800, 2400, 4800, 9600 19200, 38400, 57600, \
115200 and 230400.\n \
\n\
If @var{baudrate} parameter is omitted, the srl_baudrate() shall return current baudrate value as the result @var{br}.\n \
@end deftypefn")
{
    if (args.length() < 1 || args.length() > 2 ||
        args(0).type_id() != octave_serial::static_type_id())
    {
        print_usage();
        return octave_value(-1);
    }
    
    octave_serial* serial = NULL;

    const octave_base_value& rep = args(0).get_rep();
    serial = &((octave_serial &)rep);

    // Setting new baudrate
    if (args.length() > 1)
    {
        if ( !(args(1).is_integer_type() || args(1).is_float_type()) )
        {
            error("srl_baudrate: expecting second argument of type integer...");
            return octave_value(-1);
        }

        serial->set_baudrate(args(1).int_value());

        return octave_value();
    }

    // Returning current baud rate
    return octave_value(serial->get_baudrate());
}

int octave_serial::set_baudrate(unsigned int baud) 
{
    if (this->get_fd() < 0)
    {
        error("serial: Interface must be opened first...");
        return -1;
    }
    
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
        error("srl_baudrate: currently only 0, 50, 75, 110, \
                134, 150, 200, 300, 600, 1200, 1800, 2400, 4800, \
                9600 19200, 38400, 57600, 115200 and 230400 baud rates are supported...");
        return false;
    }

    cfsetispeed(&this->config, baud_rate);
    cfsetospeed(&this->config, baud_rate);

    if (tcsetattr(this->get_fd(), TCSANOW, &this->config) < 0) {
        error("srl_baudrate: error setting baud rate: %s\n", strerror(errno));
        return false;
    }

    return true;
}

int octave_serial::get_baudrate()
{
    if (this->get_fd() < 0)
    {
        error("serial: Interface must be opened first...");
        return -1;
    }
    
    int retval = -1;
    
    speed_t baudrate = cfgetispeed(&this->config);
    
    if (baudrate == B0)
        retval = 0;
    else if (baudrate == B50)
        retval = 50;
    else if (baudrate == B75)
        retval = 75;
    else if (baudrate == B110)
        retval = 110;
    else if (baudrate == B134)
        retval = 134;
    else if (baudrate == B150)
        retval = 150;
    else if (baudrate == B200)
        retval = 200;
    else if (baudrate == B300)
        retval = 300;
    else if (baudrate == B600)
        retval = 600;
    else if (baudrate == B1200)
        retval = 1200;
    else if (baudrate == B1800)
        retval = 1800;
    else if (baudrate == B2400)
        retval = 2400;
    else if (baudrate == B4800)
        retval = 4800;
    else if (baudrate == B9600)
        retval = 9600;
    else if (baudrate == B19200)
        retval = 19200;
    else if (baudrate == B38400)
        retval = 38400;
    else if (baudrate == B57600)
        retval = 57600;
    else if (baudrate == B115200)
        retval = 115200;
    else if (baudrate == B230400)
        retval = 230400;
    
    return retval;
    
}
