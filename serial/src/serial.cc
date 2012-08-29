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

// TODO: Include more detailed error messages (perror?)
// TODO: Implement Flow Control
// TODO: Implement H/W handshaking
// TODO: Implement read timeout
// TODO: Check if interface is opened first

#include <octave/oct.h>
#include <octave/ov-int32.h>
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

DEFINE_OCTAVE_ALLOCATOR (octave_serial);
DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_serial, "octave_serial", "octave_serial");

static bool type_loaded = false;

octave_serial::octave_serial()
{
    this->fd = -1;
}

octave_serial::octave_serial(string path, int flags)
{
    this->fd = open(path.c_str(), flags, 0);
    
    if (this->fd > 0)
    {
        tcgetattr(this->fd, &this->config);
        this->blocking_read = true;
    }
}

octave_serial::~octave_serial()
{
    this->srl_close();
}

int octave_serial::srl_get_fd()
{
    return this->fd;
}

void octave_serial::print (std::ostream& os, bool pr_as_read_syntax ) const
{
    print_raw(os, pr_as_read_syntax);
    newline(os);
}

void octave_serial::print_raw (std::ostream& os, bool pr_as_read_syntax) const
{
    os << this->fd;
}

// PKG_ADD: autoload ("serial", "serial.oct");
DEFUN_DLD (serial, args, nargout, "Hello World Help String")
{
#ifdef __WIN32__
    error("serial: Windows platform support is not yet implemented, go away...");
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
    string path("/dev/ttyUSB0");
    unsigned int baud_rate = 115200;
    short timeout = -1;
    
    unsigned short bytesize = 8;
    string parity("N");
    unsigned short stopbits = 1;
    int oflags = O_RDWR | O_NOCTTY | O_SYNC; 
    // O_SYNC - All writes immediately effective, no buffering

    if (!type_loaded)
    {
        octave_serial::register_type();
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
            baud_rate = args(1).int_value();
        }
        else
        {
            print_usage();
            return octave_value();
        }
    }

    if (args.length() > 2)
    {
        if (args(2).is_integer_type() || args(2).is_float_type())
        {
            timeout = args(2).int_value();
        }
        else
        {
            print_usage();
            return octave_value();
        }
    }

    // Open the interface
    octave_serial* retval = new octave_serial(path, oflags);

    if (retval->srl_get_fd() < 0)
    {
        error("serial: Error opening the interface: %s\n", strerror(errno));
        return octave_value();
    }
    
    retval->srl_baudrate(baud_rate);
    
    if (timeout >= 0) {
        retval->srl_timeout(timeout);
    }
    
    retval->srl_parity(parity);
    retval->srl_bytesize(bytesize);
    retval->srl_stopbits(stopbits);
    
    retval->srl_flush();
    
    return octave_value(retval);
}
