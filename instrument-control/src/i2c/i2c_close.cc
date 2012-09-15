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

DEFUN_DLD (i2c_close, args, nargout, "")
{
    if (args.length() != 1 || args(0).type_id() != octave_i2c::static_type_id())
    {
        print_usage();
        return octave_value(-1);
    }

    octave_i2c* i2c = NULL;

    const octave_base_value& rep = args(0).get_rep();
    i2c = &((octave_i2c &)rep);

    i2c->close();

    return octave_value();
}

int octave_i2c::close()
{
    if (this->get_fd() < 0)
    {
        error("i2c: Interface must be open first...");
        return -1;
    }
    
    int retval = ::close(this->get_fd());
    this->fd = -1;
    
    return retval;
}
