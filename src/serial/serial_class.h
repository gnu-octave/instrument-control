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

#ifndef SERIAL_CLASS_H
#define SERIAL_CLASS_H

#include <octave/oct.h>
//#include <octave/ops.h>

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

#define INSTALL_BINOP(op, t1, t2, f) \
  octave_value_typeinfo::register_binary_op \
    (octave_value::op, t1::static_type_id (), t2::static_type_id (), \
     CONCAT2(oct_binop_, f));


class octave_serial_common : public octave_base_value
{
public:

  // os dependent functions
  virtual bool fd_is_valid() const = 0;
  virtual int get_timeout() const = 0;
  virtual int get_baudrate() const = 0;
  virtual int get_bytesize() const = 0;
  virtual std::string get_parity() const = 0;
  virtual int get_stopbits() const = 0;

  // Properties
  bool is_constant (void) const { return true;}
  bool is_defined (void) const { return true;}
  bool is_object (void) const { return true;}

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
    os << "  Serial Port Object"; newline(os);
    os << "    open:     " << this->fd_is_valid(); newline(os);
    if (this->fd_is_valid())
      {
        os << "    port:     " << this->portPath; newline(os);
        os << "    baudrate: " << this->get_baudrate(); newline(os);
        os << "    parity:   " << this->get_parity(); newline(os);
        os << "    bytesize: " << this->get_bytesize(); newline(os);
        os << "    stopbits: " << this->get_stopbits(); newline(os);
        os << "    timeout:  " << this->get_timeout(); newline(os);
        //os << "Mode:     " << blockmode; newline(os);
      }
  }

  bool operator==(octave_serial_common& other) const
  {
    return (this == &other);
  }

  bool operator!=(octave_serial_common& other) const
  {
    return ! (this == &other);
  }

protected:
  std::string portPath;

};


#ifdef __WIN32__
 #include "serial_class_win32.h"
#else
 #include "serial_class_lin.h"
#endif

DEFBINOP_CLASS_OP (eq_serial_serial, serial, serial, ==)
DEFBINOP_CLASS_OP (ne_serial_serial, serial, serial, !=)

#endif
