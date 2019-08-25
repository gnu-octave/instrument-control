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

#ifndef I2C_CLASS_H
#define I2C_CLASS_H

#include <octave/oct.h>

#include <string>

class octave_i2c : public octave_base_value
{
public:
  octave_i2c (void);
  ~octave_i2c (void);

  int open (const std::string& /* path */, int /* open flags */);
  int close (void);
  int get_fd (void) const;

  int set_addr (int /* slave ddress */);
  int get_addr (void) const;

  std::string get_name () const;
  std::string set_name (const std::string &newname);

  std::string get_status () const;

  std::string get_port () const;

  // Simple i2c commands
  int write (uint8_t* /* buffer */, unsigned int /* buffer size */);
  int read (uint8_t* /* buffer */, unsigned int /* buffer size */);


  // Overloaded base functions
  double i2c_value () const
  {
    return (double)fd;
  }

  virtual double scalar_value (bool frc_str_conv = false) const
  {
    return (double)fd;
  }

  void print (std::ostream& os, bool pr_as_read_syntax = false);
  void print (std::ostream& os, bool pr_as_read_syntax = false) const;
  void print_raw (std::ostream& os, bool pr_as_read_syntax) const;

  // required to use subsasn
  string_vector map_keys (void) const { return fieldnames; }
  dim_vector dims (void) const { static dim_vector dv(1, 1); return dv; }

  // Properties
  bool is_constant (void) const { return true;}
  bool is_defined (void) const { return true;}
  bool is_object (void) const { return true;}
  // 4.4+
  bool isobject (void) const { return true;}

  octave_base_value * unique_clone (void) { return this;}

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
private:
  int fd;
  int addr;
  std::string name;
  std::string port;
  string_vector fieldnames;

  DECLARE_OV_TYPEID_FUNCTIONS_AND_DATA
};


#endif
