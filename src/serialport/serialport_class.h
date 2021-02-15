// Copyright (C) 2019   John Donoghue   <john.donoghue@ieee.org>
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

#ifndef SERIALPORT_CLASS_H
#define SERIALPORT_CLASS_H

#include <octave/oct.h>

#include <string>

#define BITMASK_SET(x,y) ((x) |= (y))
#define BITMASK_CLEAR(x,y) ((x) &= (~(y)))
#define BITMASK_TOGGLE(x,y) ((x) ^= (y))
#define BITMASK_CHECK(x,y) ((x) & (y))
#define BITMASK_CHECK_VALUE(x,y,z) (((x) & (y)) == (z))

#define CONCAT2X(x,y) x ## y
#define CONCAT2(x,y) CONCAT2X(x,y)

#define BINOPDECL(name, a1, a2) \
  static octave_value \
  CONCAT2(oct_binop_, name) (const octave_base_value& a1, const octave_base_value& a2)

#define CAST_BINOP_ARGS(t1, t2) \
  t1 v1 = dynamic_cast<t1> (a1);                \
  t2 v2 = dynamic_cast<t2> (a2)


#define DEFBINOP_CLASS_OP(name, t1, t2, op) \
  BINOPDECL (name, a1, a2) \
  { \
    CAST_BINOP_ARGS (const CONCAT2(octave_, t1)&, const CONCAT2(octave_, t2)&); \
    return octave_value \
      (&v1 op &v2); \
  }

#ifdef OCTAVE__NEW_REGISTER_OP
#define INSTALL_BINOP(op, t1, t2, f) \
 {octave::type_info& ti = octave::interpreter::the_interpreter ()->get_type_info (); \
  ti.register_binary_op \
    (octave_value::op, t1::static_type_id (), t2::static_type_id (), \
     CONCAT2(oct_binop_, f));}
#else
#define INSTALL_BINOP(op, t1, t2, f) \
  octave_value_typeinfo::register_binary_op \
    (octave_value::op, t1::static_type_id (), t2::static_type_id (), \
     CONCAT2(oct_binop_, f));
#endif

class octave_serialport_common : public octave_base_value
{
protected:
  octave_serialport_common();

  bool has_property(const std::string &name) const;
public:

  // os dependent functions
  virtual bool fd_is_valid() const = 0;
  virtual double get_timeout() const = 0;
  virtual int get_baudrate() const = 0;
  virtual int get_databits() const = 0;
  virtual std::string get_parity() const = 0;
  virtual int get_stopbits() const = 0;
  virtual int get_numbytesavailable() const = 0;

  // Properties
  bool is_constant (void) const { return true;}
  bool is_defined (void) const { return true;}
  bool is_object (void) const { return true;}
  // 4.4+
  bool isobject (void) const { return true;}

  octave_base_value * unique_clone (void) { count++; return this;}

  // required to use subsasn
  string_vector map_keys (void) const { return fieldnames; }
  dim_vector dims (void) const { static dim_vector dv(1, 1); return dv; }

  void print (std::ostream& os, bool pr_as_read_syntax = false)
  {
    print_raw(os, pr_as_read_syntax);
    newline(os);
  }

  void print (std::ostream& os, bool pr_as_read_syntax = false) const
  {
    print_raw(os, pr_as_read_syntax);
    newline(os);
  }

  void print_raw (std::ostream& os, bool pr_as_read_syntax) const
  {
    os << "  Serial Port Object " << this->get_name(); newline(os);
    //os << "    status:   " << this->get_status(); newline(os);
    if (this->fd_is_valid())
      {
        os << "    port:     " << this->portPath; newline(os);
        os << "    baudrate: " << this->get_baudrate(); newline(os);
        os << "    parity:   " << this->get_parity(); newline(os);
        os << "    databits: " << this->get_databits(); newline(os);
        os << "    stopbits: " << this->get_stopbits(); newline(os);
        os << "    timeout:  " << this->get_timeout(); newline(os);
        //os << "Mode:     " << blockmode; newline(os);
      }
  }

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

  std::string get_type () const
  {
    return "serialport";
  }

  std::string get_port () const
  {
    return portPath;
  }

  std::string get_name () const
  {
    return name;
  }

  void set_name (const std::string &newname)
  {
    name = newname;
  }

  unsigned long get_numbyteswritten() const
  {
    return byteswritten;
  }

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

protected:
  string_vector fieldnames;
  unsigned long byteswritten;

  std::string name;
  std::string portPath;
  std::string byteOrder;
  std::string interminator;
  std::string outterminator;
  octave_value userData;
};


#ifdef __WIN32__
 #include "serialport_class_win32.h"
#else
 #include "serialport_class_lin.h"
#endif

#endif
