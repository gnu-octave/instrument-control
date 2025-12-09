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
  : fieldnames(4)
{
  static bool type_registered = false;

  if (! type_registered)
    {
      type_registered = true;
      register_type ();
    }
 
  fd = -1;
  addr = -1;

  fieldnames[0] = "status";
  fieldnames[1] = "name";
  fieldnames[2] = "remoteaddress";
  fieldnames[3] = "port";
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
  os << "  I2C Object " << this->get_name(); newline(os);
  os << "    status:   " << this->get_status(); newline(os);
  if (get_fd() > -1)
    {
      if (get_addr() > -1)
        os << "    remoteaddress:   " << this->get_addr();
      else 
        os << "    remoteaddress:   None set";
      newline(os);
    }
}

int
octave_i2c::open (const std::string &path, int flags)
{
  port = path;
  name = "I2C-" + path;

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

    this->addr = addr;

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
  i2c_slave.buf = reinterpret_cast<char *>(buf);

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

  i2c_slave.slave = static_cast<uint16_t>(get_addr ());
  i2c_slave.count = len;
  i2c_slave.last = 0; // No additional writes will follow for this transaction
  i2c_slave.buf = reinterpret_cast<char *>(buf);

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

std::string
octave_i2c::get_port () const
{
  return port;
}

std::string
octave_i2c::get_name () const
{
  return name;
}

std::string
octave_i2c::set_name (const std::string &newname)
{
  name = newname;
  return name;
}

std::string
octave_i2c::get_status () const
{
  if (get_fd () > -1)
    return "open";
  else
    return "closed";
}

octave_value_list
octave_i2c::subsref (const std::string& type, const std::list<octave_value_list>& idx, int nargout)
{
  octave_value_list retval;
  int skip = 1;

  switch (type[0])
    {
    default:
      error ("octave_i2c object cannot be indexed with %c", type[0]);
      break;
    case '.':
      {
        octave_value_list ovl;
        // inc ref count as assign this to octave_value
        OV_COUNT++; 
        ovl (0) = octave_value (this);
        ovl (1) = (idx.front ()) (0);
        retval = OCTAVE__FEVAL (std::string ("__i2c_properties__"), ovl, 1);
      }
      break;
    }

  if (idx.size () > 1 && type.length () > 1)
    retval = retval (0).next_subsref (nargout, type, idx, skip);

  return retval;
}

octave_value
octave_i2c::subsasgn (const std::string& type, const std::list<octave_value_list>& idx, const octave_value& rhs)
{
  octave_value retval;

  switch (type[0])
    {
    default:
      error ("octave_i2c object cannot be indexed with %c", type[0]);
      break;
    case '.':
      if (type.length () == 1)
        {
          octave_value_list ovl;
          // inc ref count as assign this to octave_value
          OV_COUNT++; 
          ovl (0) = octave_value (this);
          ovl (1) = (idx.front ()) (0);
          ovl (2) = rhs;
          OCTAVE__FEVAL (std::string ("__i2c_properties__"), ovl, 0);
 
          OV_COUNT++;
          retval = octave_value (this);
        }
      else if (type.length () > 1 && type[1] == '.')
        {
          // pass along any further assignments
          octave_value_list u = subsref (type.substr (0, 1), idx, 1);
          if (u.length() > 0)
            {
              std::list<octave_value_list> next_idx (idx);
              next_idx.erase (next_idx.begin ());
              u (0).subsasgn(type.substr (1), next_idx, rhs);
              OV_COUNT++;
              retval = octave_value (this);
            } 
        }
      else
        {
          error ("octave_i2c invalid index");
        }

    }
  return retval;
}

#endif
