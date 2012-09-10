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

// PKG_ADD: autoload ("pp_close", "instrument-control.oct");
DEFUN_DLD (pp_close, args, nargout, 
"-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} pp_close (@var{parallel})\n \
\n\
Close the interface and release a file descriptor.\n \
\n\
@var{parallel} - instance of @var{octave_serial} class.@*\
@end deftypefn")
{
    if (args.length() != 1 || args(0).type_id() != octave_parallel::static_type_id())
    {
        print_usage();
        return octave_value(-1);
    }

    octave_parallel* parallel = NULL;

    const octave_base_value& rep = args(0).get_rep();
    parallel = &((octave_parallel &)rep);

    parallel->close();

    return octave_value();
}

int octave_parallel::close()
{
    if (this->get_fd() < 0)
    {
        error("parallel: port must be open first...");
        return -1;
    }

    // Release parallel port
    if (ioctl(this->get_fd(), PPRELEASE) < 0)
        error("parallel: error releasing parallel port: %s\n", strerror(errno));

    int retval = ::close(this->get_fd());

    this->fd = -1;

    return retval;
}
