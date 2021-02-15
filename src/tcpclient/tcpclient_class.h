// Copyright (C) 2021 John Donoghue <john.donoghue@ieee.org>
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

#ifndef __WIN32__
# include <netinet/in.h>
#else
# include <winsock2.h>
#endif

class octave_tcpclient : public octave_base_value
{
public:
  octave_tcpclient (void);
  ~octave_tcpclient (void);

  int write (const std::string &);
  int write (uint8_t *, unsigned int);

  int read (uint8_t *, unsigned int, double);

  int open (const std::string &, int);
  int close (void);
  int get_fd (void) const { return fd; }

  int flush (int mode);

  // Overloaded base functions
  double tcpclient_value (void) const { return (double)fd; }

  virtual double scalar_value (bool frc_str_conv = false) const
    {
        return (double)fd;
    }

  void print (std::ostream& os, bool pr_as_read_syntax = false);
  void print (std::ostream& os, bool pr_as_read_syntax = false) const;
  void print_raw (std::ostream& os, bool pr_as_read_syntax) const;

  // Properties
  bool is_map (void) const { return true; }
  bool is_constant (void) const { return true;}
  bool is_defined (void) const { return true;}
  bool is_object (void) const { return true; }
  // 4.4+
  bool isobject (void) const { return true; }

  // required to use subsasn
  string_vector map_keys (void) const { return fieldnames; }
  dim_vector dims (void) const { static dim_vector dv(1, 1); return dv; }

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

  int get_numbytesavailable (void) const;
  unsigned int get_numbyteswritten (void) const { return byteswritten; }

  std::string get_name (void) const { return name; }
  std::string set_name (const std::string &);

  int set_timeout (double);
  double get_timeout (void) const { return timeout; }

  std::string get_address (void) const;
  int get_port (void) const;

  bool is_open(void) const;

  std::string get_type (void) const { return "tcpclient"; }

  std::string get_status (void) const;

  octave_value get_userdata () const
  {
    return userData;
  }

  void set_userdata (const octave_value &newv)
  {
    userData = newv;
  }

  int set_byteorder(const std::string& /* order */);

  std::string get_byteorder() const
  {
    return byteOrder;
  }

  int set_input_terminator(const std::string& /* term */);
  int set_output_terminator(const std::string& /* term */);

  std::string get_input_terminator() const
  {
    return interminator;
  }

  std::string get_output_terminator() const
  {
    return outterminator;
  }


private:
  string_vector fieldnames;

  int fd;
  double timeout;

  std::string name;
  sockaddr_in remote_addr;
  sockaddr_in local_addr;
  octave_value userData;
  std::string byteOrder;
  unsigned int byteswritten;
  std::string interminator;
  std::string outterminator;

  DECLARE_OV_TYPEID_FUNCTIONS_AND_DATA
};

#endif
