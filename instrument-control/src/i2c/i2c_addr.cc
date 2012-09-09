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
#include <linux/i2c-dev.h>
#include <errno.h>
#include <sys/ioctl.h>
#endif

#include "i2c.h"

DEFUN_DLD (i2c_addr, args, nargout, "")
{
    if (args.length() > 2 || 
        args(0).type_id() != octave_i2c::static_type_id()) 
    {
        print_usage();
        return octave_value(-1);
    }
    
    octave_i2c* i2c = NULL;

    const octave_base_value& rep = args(0).get_rep();
    i2c = &((octave_i2c &)rep);


    // Setting new slave address
    if (args.length() > 1)
    {
        if ( !(args(1).is_integer_type() || args(1).is_float_type()) )
        {
            print_usage();
            return octave_value(-1);
        }

        i2c->set_addr(args(1).int_value());

        return octave_value();
    }

    // Returning current slave address
    return octave_value(i2c->get_addr());
}

int octave_i2c::set_addr(int addr)
{
    if (this->get_fd() < 0)
    {
        error("i2c: Interface must be open first...");
        return -1;
    }
    
    if (::ioctl(this->get_fd(), I2C_SLAVE, addr) < 0)
    {
        error("i2c: Error setting slave address: %s\n", strerror(errno));
        return -1;
    }
    
    return 1;
}

int octave_i2c::get_addr()
{
    if (this->get_fd() < 0)
    {
        error("i2c: Interface must be open first...");
        return -1;
    }
    
    return this->addr;
}