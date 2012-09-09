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

#include <stdio.h>
#include <stdlib.h>

#ifndef __WIN32__
#include <errno.h>
#include <unistd.h>
#endif

#include "i2c.h"

DEFUN_DLD (i2c_read, args, nargout, "")
{
    if (args.length() < 1 || args.length() > 2 || args(0).type_id() != octave_i2c::static_type_id())
    {
        print_usage();
        return octave_value(-1);
    }

    char *buffer = NULL;
    unsigned int buffer_len = 1;

    if (args.length() > 1)
    {
        if ( !(args(1).is_integer_type() || args(1).is_float_type()) )
        {
            print_usage();
            return octave_value(-1);
        }

        buffer_len = args(1).int_value();
    }

    buffer = new char [buffer_len + 1];

    if (buffer == NULL)
    {
        error("i2c_read: cannot allocate requested memory...");
        return octave_value(-1);  
    }

    octave_i2c* i2c = NULL;

    const octave_base_value& rep = args(0).get_rep();
    i2c = &((octave_i2c &)rep);

    int retval;
    
    retval = i2c->read(buffer, buffer_len);
    
    octave_value_list return_list;
    uint8NDArray data(retval);
    
    for (int i = 0; i < retval; i++)
        data(i) = buffer[i];

    return_list(1) = retval; 
    return_list(0) = data;

    delete[] buffer;

    return return_list;
}

int octave_i2c::read(char *buf, unsigned int len)
{   
    if (this->get_fd() < 0)
    {
        error("i2c: Interface must be open first...");
        return -1;
    }
    
    int retval = ::read(this->get_fd(), buf, len);
    
    if (retval != len)
        error("i2c: Failed to read from the i2c bus: %s\n", strerror(errno));
                    
    return retval;
}