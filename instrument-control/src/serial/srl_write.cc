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

DEFUN_DLD (srl_write, args, nargout, 
"-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{n} = } srl_write (@var{serial}, @var{data})\n \
\n\
Write data to a serial interface.\n \
\n\
@var{serial} - instance of @var{octave_serial} class.@*\
@var{data} - data to be written to the serial interface. Can be either of String or uint8 type.\n \
\n\
Upon successful completion, srl_write() shall return the number of bytes written as the result @var{n}.\n \
@end deftypefn")
{
    if (args.length() != 2 || args(0).type_id() != octave_serial::static_type_id())
    {
        print_usage();
        return octave_value(-1);
    }

    octave_serial* serial = NULL;
    int retval;

    const octave_base_value& rep = args(0).get_rep();
    serial = &((octave_serial &)rep);

    if (args(1).is_string()) // String
    {
        retval = serial->write(args(1).string_value());
    }
    else if (args(1).byte_size() == args(1).numel()) // uint8_t
    {
        NDArray data = args(1).array_value();
        unsigned char* buf = new unsigned char[data.length()];
        
        // memcpy?
        for (int i = 0; i < data.length(); i++)
            buf[i] = (unsigned char)data(i);
        
        retval = serial->write(buf, data.length());
        
        delete[] buf;
    }
    else
    {
        print_usage();
        return octave_value(-1);
    }

    return octave_value(retval);
}

int octave_serial::write(string str)
{
    if (this->get_fd() < 0)
    {
        error("serial: Interface must be opened first...");
        return -1;
    }
    
    return ::write(get_fd(), str.c_str(), str.length());
}

int octave_serial::write(unsigned char *buf, int len)
{
    if (this->get_fd() < 0)
    {
        error("serial: Interface must be opened first...");
        return -1;
    }
    
    return ::write(get_fd(), buf, len);
}