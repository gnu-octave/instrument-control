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

#ifndef TCP_CLASS_H
#define TCP_CLASS_H

#include <octave/oct.h>
#include <octave/ov-int32.h>

#include <string>

class octave_tcp : public octave_base_value
{
public:
  octave_tcp (void);
  ~octave_tcp (void);

  int write (const std::string &);
  int write (uint8_t *, unsigned int);

  int read (uint8_t *, unsigned int, int);

  int open (const std::string &, int);
  int close (void);
  int get_fd (void) const { return fd; }

  int set_timeout (int);
  int get_timeout (void) const { return timeout; }

  // Overloaded base functions
  double tcp_value (void) const { return (double)fd; }

  virtual double scalar_value (bool frc_str_conv = false) const
    {
        return (double)fd;
    }

  void print (std::ostream& os, bool pr_as_read_syntax = false);
  void print (std::ostream& os, bool pr_as_read_syntax = false) const;
  void print_raw (std::ostream& os, bool pr_as_read_syntax) const;

  // Properties
  bool is_constant (void) const { return true;}
  bool is_defined (void) const { return true;}
  bool print_as_scalar (void) const { return true;}

private:
  int fd;
  int timeout;

  DECLARE_OV_TYPEID_FUNCTIONS_AND_DATA
};

#endif
