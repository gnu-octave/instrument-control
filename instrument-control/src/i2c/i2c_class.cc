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
#include <string>

#ifndef __WIN32__
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#endif

using std::string;

#include "i2c_class.h"

DEFINE_OCTAVE_ALLOCATOR (octave_i2c);
DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_i2c, "octave_i2c", "octave_i2c");

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

int octave_i2c::write(unsigned char *buf, int len)
{
    if (this->get_fd() < 0)
    {
        error("i2c: Interface must be open first...");
        return -1;
    }
    
    int retval = ::write(this->get_fd(), buf, len);
    
    if (retval < 0)
        error("i2c: Failed to write to the i2c bus: %s\n", strerror(errno));
    
    return retval;
}

int octave_i2c::close()
{
    /*
    if (this->get_fd() < 0)
    {
        error("i2c: Interface must be open first...");
        return -1;
    }
    */
    
    int retval = ::close(this->get_fd());
    this->fd = -1;
    
    return retval;
}
