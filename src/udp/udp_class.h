// Copyright (C) 2016   John Donoghue   <john.donoghue@ieee.org>
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

#ifndef UDP_CLASS_H
#define UDP_CLASS_H

#include <octave/oct.h>
#include <octave/ov-int32.h>

#include <string>

#ifndef __WIN32__
# include <netinet/in.h>
#else
# include <winsock2.h>
#endif

class octave_udp : public octave_base_value
{
public:
  octave_udp (void);
  ~octave_udp (void);

  int write (const std::string &str);
  int write (uint8_t *buf, unsigned int len);

  int read (uint8_t *buf, unsigned int len, int readtimeout);

  int open (const std::string &address, int port, int localport);

  int close (void);

  int get_fd (void) const { return fd; }

  // Overloaded base functions
  double udp_value (void) const { return (double)fd; }

  virtual double scalar_value (bool frc_str_conv = false) const
    {
      return (double)fd;
    }

  void print (std::ostream& os, bool pr_as_read_syntax = false);
  void print (std::ostream& os, bool pr_as_read_syntax = false) const;
  void print_raw (std::ostream& os, bool pr_as_read_syntax) const;

  // Properties
  bool is_constant (void) const { return true; }
  bool is_defined (void) const { return true; }
  bool is_object (void) const { return true; }

  std::string get_name (void) const { return name; }
  std::string set_name (const std::string &);

  std::string get_remote_addr (void) const;
  std::string set_remote_addr (const std::string &);

  int get_remote_port (void) const;
  int set_remote_port (int);

  int get_local_port (void) const;

  bool is_open(void) const;

  std::string get_type (void) const { return "udp"; }

  std::string get_status (void) const;

  int set_timeout (int);
  int get_timeout (void) const { return timeout; }

private:
  int fd;
  int timeout;
  std::string name;
  sockaddr_in remote_addr;
  sockaddr_in local_addr;

  DECLARE_OV_TYPEID_FUNCTIONS_AND_DATA
};

#endif
