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
#include <octave/uint8NDArray.h>
#include <octave/sighandlers.h>

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

volatile bool read_interrupt = false;

void read_sighandler(int sig)
{
    printf("srl_read: Interrupting...\n\r");
    read_interrupt = true;
}

DEFUN_DLD (srl_read, args, nargout, 
        "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {[@var{data}, @var{count}] = } srl_read (@var{serial}, @var{n})\n \
\n\
Read from serial interface.\n \
\n\
@var{serial} - instance of @var{octave_serial} class.@*\
@var{n} - number of bytes to attempt to read of type Integer.\n \
\n\
The srl_read() shall return number of bytes successfully read in @var{count} as Integer and the bytes themselves in @var{data} as uint8 array.\n \
@end deftypefn")
{
    if (args.length() != 2 || args(0).type_id() != octave_serial::static_type_id())
    {
        print_usage();
        return octave_value(-1);
    }

    unsigned int buffer_len = 0;

    if ( !(args(1).is_integer_type() || args(1).is_float_type()) )
    {
        print_usage();
        return octave_value(-1);
    }

    buffer_len = args(1).int_value();

    char *buffer = NULL;
    buffer = new char[buffer_len + 1];

    if (buffer == NULL)
    {
        error("srl_read: cannot allocate requested memory: %s\n", strerror(errno));
        return octave_value(-1);  
    }

    octave_serial* serial = NULL;

    const octave_base_value& rep = args(0).get_rep();
    serial = &((octave_serial &)rep);

    // Register custom interrupt signal handler
    octave_set_signal_handler(SIGINT, read_sighandler);
    read_interrupt = false;
    
    // Read data
    int bytes_read = serial->read(buffer, buffer_len);

    // Restore default signal handling
    // TODO: a better way? 
    install_signal_handlers();
    
    // Convert data to octave type variables
    octave_value_list return_list(2);
    uint8NDArray data( dim_vector(1, bytes_read) );

    for (int i = 0; i < bytes_read; i++)
        data(i) = buffer[i];

    return_list(0) = data;
    return_list(1) = bytes_read;

    delete[] buffer;

    return return_list;
}

int octave_serial::read(char *buf, unsigned int len)
{
    if (this->get_fd() < 0)
    {
        error("srl_read: Interface must be opened first...");
        return 0;
    }

    int bytes_read = 0, read_retval = -1;

    // While not interrupted in blocking mode
    while (!read_interrupt) 
    {
        read_retval = ::read(this->get_fd(), (void *)(buf + bytes_read), len - bytes_read);
        //printf("read_retval: %d\n\r", read_retval);

        if (read_retval < 0)
        {
            error("srl_read: Error while reading: %s\n", strerror(errno));
            break;
        }

        bytes_read += read_retval;

        // Required number of bytes read
        if (bytes_read >= len)
            break;

        // Timeout while in non-blocking mode
        if (read_retval == 0 && !this->blocking_read)
            break;
    }

    return bytes_read;
}

/*int octave_serial::readline(char *buf, unsigned int len)
{
}*/
