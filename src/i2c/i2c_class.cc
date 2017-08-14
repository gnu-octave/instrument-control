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

#ifdef HAVE_CONFIG_H
#include "../config.h"
#endif

#ifdef BUILD_I2C
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>


#if defined (__linux__)
#include <linux/i2c-dev.h>
#endif

// Platform specific header files
#if defined (__FreeBSD__)
#include <dev/iicbus/iic.h>
#endif

#include "i2c_class.h"

DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_i2c, "octave_i2c", "octave_i2c");

octave_i2c::octave_i2c (void)
{
  static bool type_registered = false;

  if (! type_registered)
    {
      type_registered = true;
      register_type ();
    }
 
  fd = -1;
}

octave_i2c::~octave_i2c (void)
{
  octave_i2c::close ();
}

int
octave_i2c::get_fd (void) const
{
  return fd;
}

void
octave_i2c::print (std::ostream& os, bool pr_as_read_syntax)
{
  print_raw (os, pr_as_read_syntax);
  newline (os);
}

void
octave_i2c::print (std::ostream& os, bool pr_as_read_syntax ) const
{
  print_raw (os, pr_as_read_syntax);
  newline (os);
}

void
octave_i2c::print_raw (std::ostream& os, bool pr_as_read_syntax) const
{
  os << fd;
}

int
octave_i2c::open (const std::string &path, int flags)
{
  fd = ::open (path.c_str (), flags, 0);

  if (get_fd () < 0)
    {
      error ("i2c: Error opening the interface: %s\n", strerror (errno));
      return -1;
    }

  return get_fd ();
}


int
octave_i2c::set_addr (int addr)
{
  if (get_fd () < 0)
    {
      error ("i2c: Interface must be open first...");
      return -1;
    }

#if defined (__linux__)
  if (::ioctl (get_fd (), I2C_SLAVE, addr) < 0)
    {
        error ("i2c: Error setting slave address: %s\n", strerror (errno));
        return -1;
    }
#endif

    return 1;
}

int
octave_i2c::get_addr (void) const
{
    if (get_fd() < 0)
    {
        error ("i2c: Interface must be open first...");
        return -1;
    }

    return addr;
}

int
octave_i2c::read (uint8_t *buf, unsigned int len)
{   
  if (get_fd () < 0)
    {
      error ("i2c: Interface must be open first...");
      return -1;
    }

  int retval = -1;

#if defined (__linux__)
  retval = ::read (get_fd (), buf, len);
#endif

#if defined (__FreeBSD__)
  // Populate FreeBSD-specific structure
  struct iiccmd i2c_slave;

  i2c_slave.slave = static_cast<uint8_t>(get_addr ());
  i2c_slave.count = len;
  i2c_slave.last = 0; // No additional reads will follow for this transaction
  i2c_slave.buf = buf;

  ::ioctl (get_fd (), I2CSTART, &i2c_slave);
  retval = ::ioctl (get_fd(), I2CREAD, &i2c_slave);
  ::ioctl (get_fd(), I2CSTOP);
#endif

  if (retval < 0)
    error ("i2c: Failed to read from the i2c bus: %s\n", strerror (errno));

  return retval;
}

int
octave_i2c::write (uint8_t *buf, unsigned int len)
{
  if (get_fd () < 0)
    {
      error ("i2c: Interface must be open first...");
      return -1;
    }

  int retval = -1;

#if defined (__linux__)
  retval = ::write (get_fd (), buf, len);
#endif

#if defined (__FreeBSD__)
  // Populate FreeBSD-specific structure
  struct iiccmd i2c_slave;

  i2c_slave.slave = static_cast<uint16_t>(get_addri ());
  i2c_slave.count = len;
  i2c_slave.last = 0; // No additional writes will follow for this transaction
  i2c_slave.buf = buf;

  ::ioctl (get_fd (), I2CSTART, &i2c_slave);
  retval = ::ioctl (get_fd (), I2CWRITE, &i2c_slave);
  ::ioctl(get_fd (), I2CSTOP);
#endif

  if (retval < 0)
    error ("i2c: Failed to write to the i2c bus: %s\n", strerror (errno));

  return retval;
}

int
octave_i2c::close (void)
{
  int retval = -1;

  if (get_fd () > 0)
    {
      retval = ::close(get_fd ());
      fd = -1;
    }

  return retval;
}
#endif
