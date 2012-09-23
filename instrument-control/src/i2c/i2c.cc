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
//#include <octave/ov-int32.h>

#include <stdio.h>
#include <stdlib.h>
#include <string>

#ifndef __WIN32__
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#endif

using std::string;

#include "i2c.h"

DEFINE_OCTAVE_ALLOCATOR (octave_i2c);
DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_i2c, "octave_i2c", "octave_i2c");

static bool type_loaded = false;

octave_i2c::octave_i2c()
{
    this->fd = -1;
}

octave_i2c::octave_i2c(string path, int flags)
{
    this->fd = open(path.c_str(), flags, 0);
}

octave_i2c::~octave_i2c()
{
    this->close();
}

int octave_i2c::get_fd()
{
    return this->fd;
}

void octave_i2c::print (std::ostream& os, bool pr_as_read_syntax ) const
{
    print_raw(os, pr_as_read_syntax);
    newline(os);
}

void octave_i2c::print_raw (std::ostream& os, bool pr_as_read_syntax) const
{
    os << this->fd;
}

DEFUN_DLD (i2c, args, nargout, 
"-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{i2c} = } i2c ([@var{path}], [@var{address}])\n \
\n\
Open i2c interface.\n \
\n\
@var{path} - the interface path of type String. If omitted defaults to '/dev/i2c-0'. @*\
@var{address} - the slave device address. If omitted must be set using i2c_addr() call.\n \
\n\
The i2c() shall return instance of @var{octave_i2c} class as the result @var{i2c}.\n \
@end deftypefn")
{
#ifdef __WIN32__
    error("i2c: Windows platform support is not yet implemented, go away...");
    return octave_value();
#endif

    int nargin = args.length();
    
    // Default values
    int oflags = O_RDWR;
    string path("/dev/i2c-0");

    // Do not open interface if return value is not assigned
    if (nargout != 1)
    {
        print_usage();
        return octave_value();
    }

    // Open the interface
    octave_i2c* retval = new octave_i2c(path, oflags);

    if (retval->get_fd() < 0)
    {
        error("i2c: Error opening the interface: %s\n", strerror(errno));
        return octave_value();
    }

    return octave_value(retval);
}
