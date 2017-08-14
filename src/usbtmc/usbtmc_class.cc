// Copyright (C) 2013   Stefan Mahr     <dac922@gmx.de>
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

#ifdef BUILD_USBTMC
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include <string>

#include "usbtmc_class.h"

DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_usbtmc, "octave_usbtmc", "octave_usbtmc");

octave_usbtmc::octave_usbtmc (void)
: fd (-1)
{
  static bool type_registered = false;

  if (! type_registered)
    {
      type_registered = true;
      register_type ();
    }
}

octave_usbtmc::~octave_usbtmc (void)
{
  octave_usbtmc::close();
}

int
octave_usbtmc::get_fd() const
{
  return fd;
}

void
octave_usbtmc::print (std::ostream& os, bool pr_as_read_syntax)
{
  print_raw(os, pr_as_read_syntax);
  newline(os);
}

void
octave_usbtmc::print (std::ostream& os, bool pr_as_read_syntax ) const
{
  print_raw(os, pr_as_read_syntax);
  newline(os);
}

void
octave_usbtmc::print_raw (std::ostream& os, bool pr_as_read_syntax) const
{
  os << fd;
}

int
octave_usbtmc::open (const std::string &path, int flags)
{
  fd = ::open (path.c_str (), flags, 0);

  if (get_fd () < 0)
    {
      error ("usbtmc: Error opening the interface: %s\n", strerror (errno));
      return -1;
    }

  return get_fd ();
}

int
octave_usbtmc::read (uint8_t *buf, unsigned int len)
{
  if (get_fd () < 0)
    {
      error ("usbtmc: Interface must be open first...");
      return -1;
    }

  int retval = ::read (get_fd (), buf, len);

  if (retval < 0)
    error ("usbtmc: Failed to read from the usbtmc bus: %s\n", strerror (errno));

  return retval;
}

int
octave_usbtmc::write (uint8_t *buf, unsigned int len)
{
  if (get_fd () < 0)
    {
      error ("usbtmc: Interface must be open first...");
      return -1;
    }

  int retval = ::write (get_fd (), buf, len);

  if (retval < 0)
    error("usbtmc: Failed to write to the usbtmc bus: %s\n", strerror(errno));

  return retval;
}

int
octave_usbtmc::close (void)
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
