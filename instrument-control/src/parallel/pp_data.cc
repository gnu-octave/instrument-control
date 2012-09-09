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

#include <iostream>
#include <string>
#include <algorithm>

#ifndef __WIN32__
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/parport.h>
#include <linux/ppdev.h>
#endif

using std::string;

#include "parallel.h"

// PKG_ADD: autoload ("pp_data", "instrument-control.oct");
DEFUN_DLD (pp_data, args, nargout, "")
{
    if (args.length() < 1 || args.length() > 2 || args(0).type_id() != octave_parallel::static_type_id())
    {
        print_usage();
        return octave_value(-1);
    }

    octave_parallel* parallel = NULL;

    const octave_base_value& rep = args(0).get_rep();
    parallel = &((octave_parallel &)rep);

    // Set new Data register value
    if (args.length() > 1)
    {
        if ( !(args(1).is_integer_type() || args(1).is_float_type()) )
        {
            print_usage();
            return octave_value(-1);
        }

        parallel->set_datadir(args(1).int_value());

        return octave_value();
    }

    // Return current Data register value on port
    return octave_value(parallel->get_data());
}

int octave_parallel::set_data(uint8_t data)
{
    if (this->get_fd() < 0)
    {
        error("parallel: Open the interface first...");
        return -1;
    }

    /*
    if (this->get_dir() == 1)
    {
        error("parallel: Trying to output data while in Input mode, this can result in hardware damage! \
                   Use override if you know what you are doing...");
        return false;
    }  
     */

    if (ioctl(this->get_fd(), PPWDATA, &data) < 0) 
    {
        error("parallel: Error while writing to Data register: %s\n", strerror(errno));
        return -1;
    }

    return 1;
}

int octave_parallel::get_data()
{
    if (this->get_fd() < 0)
    {
        error("parallel: Open the interface first...");
        return -1;
    }

    uint8_t data;

    if (ioctl(this->get_fd(), PPRDATA, &data) < 0)    
    {
        error("parallel: Error while reading from Data register: %s\n", strerror(errno));
        return -1;
    }

    return data;
}

