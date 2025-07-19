// Copyright (C) 2025 John Donoghue   <john.donoghue@ieee.org>
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

#ifndef VISADEV_CLASS_H
#define VISADEV_CLASS_H

#include <octave/oct.h>
#include <octave/ov-int32.h>

#include <string>
#include <vector>

#ifdef HAVE_CONFIG_H
#  include "../config.h"
#endif

#ifdef HAVE_VISA_H
# include <visa.h>
#else
# ifdef HAVE_VISA_VISA_H
#  include <visa/visa.h>
# endif
#endif

struct PropertyMap;

class visa_devinfo
{
public:
  visa_devinfo() {};
  virtual ~visa_devinfo() {};

  std::string name;
  std::string alias;
  std::string vendor;
  std::string model;
  std::string serial_number;
  std::string type;
};

class visa_library;

class octave_visadev : public OCTAVE_BASE_CLASS
{
public:
  octave_visadev (void);
  ~octave_visadev (void);

  static std::vector <visa_devinfo> list_devices();

  int write (const std::string &str);
  int write (const uint8_t *buf, unsigned int len);

  int read (uint8_t *buf, unsigned int len);

  //int getsockopt (int level, int opt, void *buf, socklen_t *len);
  //int setsockopt (int level, int opt, const void *buf, socklen_t len);

  int open (const std::string &resource);

  int close (void);

  //int get_fd (void) const { return fd; }

  int get_bytesavailable (void) const;
  unsigned int get_byteswritten (void) const { return byteswritten; }

  // Overloaded base functions
  //double udpport_value (void) const { return (double)fd; }

  virtual double scalar_value (bool frc_str_conv = false) const
    {
      return (double)instrument;
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
  //string_vector map_keys (void) const { return fieldnames; }
  string_vector map_keys (void) const;
  dim_vector dims (void) const { static dim_vector dv(1, 1); return dv; }

  // use single copy of each device
  octave_base_value * unique_clone (void) { OV_COUNT++; return this; }

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
  //std::string set_name (const std::string &);

  bool is_open(void) const;

  std::string get_type (void) const { return type_str; }

  std::string get_status (void) const;

  int set_timeout (double);
  double get_timeout (void) const { return timeout; }

  int flush(int mode);
  int trigger();

  int get_control_line(const std::string &line);
  int set_control_line(const std::string &line, bool on_off);

  int get_visa_status();

  octave_value get_userdata () const
  {
    return userData;
  }

  void set_userdata (const octave_value &newv)
  {
    userData = newv;
  }

  std::string get_eoimode () const
  {
    return (eoimode ? "on" : "off");
  }

  std::string get_tag () const
  {
    return tag;
  }

  void set_tag (const std::string &newv)
  {
    tag = newv;
  }

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
  class visa_library * lib;
  const PropertyMap* get_property(const std::string &name) const;
  octave_value get_attribute(const PropertyMap *p);
  bool set_attribute(const PropertyMap *p, const octave_value &value);
  
  uint8_t *input_buffer;
  int buffer_len;
  int buffer_pos;
  //sockaddr_in read_addr;
  //
  struct PropertyMap * properties;

  //int fd;
  ViSession instrument;
  double timeout;
  std::string name;
  std::string tag;
  std::string type_str;
  string_vector fieldnames;
  octave_value userData;
  std::string byteOrder;
  unsigned int byteswritten;
  octave_value interminator;
  octave_value outterminator;
  bool eoimode;

  DECLARE_OV_TYPEID_FUNCTIONS_AND_DATA
};

#endif
