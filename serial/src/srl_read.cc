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
#include <octave/ov-uint8.h>
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

// PKG_ADD: autoload ("srl_read", "serial.oct");
DEFUN_DLD (srl_read, args, nargout, "Hello World Help String")
{
    if (args.length() < 1 || args.length() > 2)
    {
        error("srl_read: expecting one or two arguments...");
        return octave_value(-1);
    }

    if (args(0).type_id() != octave_serial::static_type_id())
    {
        error("srl_read: expecting first argument of type octave_serial...");
        return octave_value(-1);
    }

    char *buffer = NULL;
    unsigned int buffer_len = 1;

    if (args.length() > 1)
    {
        if ( !(args(1).is_integer_type() || args(1).is_float_type()) )
        {
            error("srl_read: expecting second argument of type integer...");
            return octave_value(-1);
        }

        buffer_len = args(1).int_value();
    }

    buffer = new char[buffer_len+1];

    if (buffer == NULL)
    {
        error("srl_read: cannot allocate requested memory...");
        return octave_value(-1);  
    }

    octave_serial* serial = NULL;

    const octave_base_value& rep = args(0).get_rep();
    serial = &((octave_serial &)rep);

    int retval = 0;

    while (retval < buffer_len)
    {
        retval += serial->srl_read(buffer + retval, buffer_len - retval);
    }

    //buffer[retval] = '\0';

    octave_value_list return_list;
    uint8NDArray data;
    data.resize(retval);

    // TODO: clean this up
    for (int i = 0; i < retval; i++)
    {
        data(i) = buffer[i];
    }

    return_list(1) = retval; 
    return_list(0) = data;

    delete[] buffer;

    return return_list;
}

int octave_serial::srl_read(char *buf, unsigned int len)
{
    return ::read(srl_get_fd(), buf, len);
}