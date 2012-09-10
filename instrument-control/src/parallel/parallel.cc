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
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/parport.h>
#include <linux/ppdev.h>
#endif

using std::string;

#include "parallel.h"

DEFINE_OCTAVE_ALLOCATOR (octave_parallel);
DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_parallel, "octave_parallel", "octave_parallel");

static bool type_loaded = false;

octave_parallel::octave_parallel()
{
    this->fd = -1;
}

int octave_parallel::open(string path, int flags)
{
    this->fd = ::open(path.c_str(), flags, 0);

    if (this->fd < 0)
    {
        error("parallel: Error opening the interface: %s\n", strerror(errno));
        return -1;
    }

    // Claim control of parallel port
    if (ioctl(this->get_fd(), PPCLAIM) < 0)
    {
        error("parallel: Error when claiming the interface: %s\n", strerror(errno));
        ::close(this->get_fd());
        return -1;
    }

    return 1;
}

octave_parallel::~octave_parallel()
{
    this->close();
}

int octave_parallel::get_fd()
{
    return this->fd;
}

void octave_parallel::print(std::ostream& os, bool pr_as_read_syntax ) const
{
    print_raw(os, pr_as_read_syntax);
    newline(os);
}

void octave_parallel::print_raw(std::ostream& os, bool pr_as_read_syntax) const
{
    os << this->fd;
}

// PKG_ADD: autoload ("parallel", "instrument-control.oct");
DEFUN_DLD (parallel, args, nargout, 
"-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{parallel} = } parallel ([@var{path}], [@var{direction})\n \
\n\
Open Parallel interface.\n \
\n\
@var{path} - the interface path of type String. If omitted defaults to '/dev/parport0'.@*\
@var{direction} - the direction of interface drivers of type Integer, see: @seealso{pp_datadir} for more info.\
If omitted defaults to 1 (Input).\n \
\n\
The parallel() shall return instance of @var{octave_parallel} class as the result @var{parallel}.\n \
@end deftypefn")
{
#ifdef __WIN32__
    error("parallel: Windows platform support is not yet implemented, go away...");
    return octave_value();
#endif   

    int nargin = args.length();

    // Do not open interface if return value is not assigned
    if (nargout != 1)
    {
        print_usage();
        return octave_value();
    }

    // Default values
    int oflags = O_RDWR;
    int dir = 1; // Input
    string path("/dev/parport0");


    if (!type_loaded)
    {
        octave_parallel::register_type();
        type_loaded = true;
    }

    // Parse the function arguments
    if (args.length() > 0)
    {
        if (args(0).is_string())
        {
            path = args(0).string_value();
        }
        else
        {
            print_usage();
            return octave_value();
        }

    }

    // is_float_type() is or'ed to allow expression like ("", 123), without user
    // having to use ("", int32(123)), as we still only take "int_value"
    if (args.length() > 1)
    {
        if (args(1).is_integer_type() || args(1).is_float_type())
        {
            dir = args(1).int_value();
        }
        else
        {
            print_usage();
            return octave_value();
        }
    }

    // Open the interface
    octave_parallel* retval = new octave_parallel();

    if (retval->open(path, oflags) < 0)
        return octave_value();

    // Set direction
    retval->set_datadir(dir);

    return octave_value(retval);
}
