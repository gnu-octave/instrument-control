// Copyright (C) 2021 John Donoghue   <john.donoghue@ieee.org>
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

#ifndef UDPPORT_CLASS_H
#define UDPPORT_CLASS_H

#include <octave/oct.h>
#include <octave/ov-int32.h>

#include <string>
#include <vector>

#ifndef __WIN32__
# include <netinet/in.h>
#else
# include <winsock2.h>
typedef int socklen_t;
#endif

int to_ip_port (const sockaddr_in *in, std::string &ip, int &port);

class octave_udpport : public octave_base_value
{
public:
  octave_udpport (void);
  ~octave_udpport (void);

  int write (const std::string &str, const std::string &destip="", int destport=0);
  int write (uint8_t *buf, unsigned int len, const std::string &destip="", int destport=0);

  int read (uint8_t *buf, unsigned int len, double readtimeout, sockaddr_in *rdinfo=0);

  int getsockopt (int level, int opt, void *buf, socklen_t *len);
  int setsockopt (int level, int opt, const void *buf, socklen_t len);

  int open (const std::string &address, int port, int portshare);

  int close (void);

  int get_fd (void) const { return fd; }

  int get_bytesavailable (void) const;
  unsigned int get_byteswritten (void) const { return byteswritten; }

  // Overloaded base functions
  double udpport_value (void) const { return (double)fd; }

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
  // < 4.4
  bool is_object (void) const { return true; }
  // 4.4 +
  bool isobject (void) const { return true; }

  // required to use subsasn
  string_vector map_keys (void) const { return fieldnames; }
  dim_vector dims (void) const { static dim_vector dv(1, 1); return dv; }

  // use single copy of each udpport socket
  octave_base_value * unique_clone (void) { count++; return this; }

 /**
  * overloaded methods to get properties
  */
  octave_value_list subsref (const std::string& type, const std::list<octave_value_list>& idx, int nargout);

  octave_value subsref (const std::string& type, const std::list<octave_value_list>& idx)
  {
    octave_value_list retval = subsref (type, idx, 1);
    return (retval.length () > 0 ? retval(0) : octave_value ());
  }

  octave_value subsasgn (const std::string& type, const std::list<octave_value_list>& idx, const octave_value& rhs);

  std::string get_name (void) const { return name; }
  std::string set_name (const std::string &);

  std::string get_remote_addr (void) const;
  std::string set_remote_addr (const std::string &);

  int get_remote_port (void) const;
  int set_remote_port (int);

  int get_local_port (void) const;

  std::string get_local_addr (void) const;

  bool is_open(void) const;

  std::string get_type (void) const { return "udpport"; }

  std::string get_status (void) const;

  int set_timeout (double);
  double get_timeout (void) const { return timeout; }

  int flush(int mode);

  int set_multicastgroup (const std::string &);
  std::string get_multicastgroup () const;

  int get_enableportsharing() const { return enableportsharing; }

  int get_enablebroadcast() const { return enablebroadcast; }
  int set_enablebroadcast (int enable);

  int get_multicastloopback() const { return enablemulticastloopback; }
  int set_multicastloopback (int enable);

  octave_value get_userdata () const
  {
    return userData;
  }

  void set_userdata (const octave_value &newv)
  {
    userData = newv;
  }

  std::string get_ipaddressversion () const { return "IPV4"; }

  int set_byteorder(const std::string& /* order */);

  std::string get_byteorder() const
  {
    return byteOrder;
  }

  int set_input_terminator(const octave_value& /* term */);
  int set_output_terminator(const octave_value& /* term */);

  octave_value get_input_terminator() const
  {
    return interminator;
  }

  octave_value get_output_terminator() const
  {
    return outterminator;
  }

private:
  bool has_property(const std::string &name) const;

  int fd;
  double timeout;
  std::string name;
  sockaddr_in remote_addr;
  sockaddr_in local_addr;
  string_vector fieldnames;
  std::vector<sockaddr_in> multicastaddr;
  octave_value userData;
  int enableportsharing;
  int enablemulticastloopback;
  int enablebroadcast;
  std::string byteOrder;
  unsigned int byteswritten;
  octave_value interminator;
  octave_value outterminator;

  DECLARE_OV_TYPEID_FUNCTIONS_AND_DATA
};

#endif
