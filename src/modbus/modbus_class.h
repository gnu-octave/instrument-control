// Copyright (C) 2022 John Donoghue   <john.donoghue@ieee.org>
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

#ifndef MODBUS_CLASS_H
#define MODBUS_CLASS_H

#include <octave/oct.h>
//#include <octave/ov-int32.h>
#include <modbus/modbus.h>

#include <string>

#ifdef HAVE_CONFIG_H
#  include "../config.h"
#endif

class octave_modbus : public OCTAVE_BASE_CLASS
{
public:
  octave_modbus (void);
  ~octave_modbus (void);

  int open_tcp (const std::string &address, int port);
  int open_serial (const std::string &comport, unsigned long baud=9600, int dbits=8, const std::string &parity="none", int sbits=1);
  int close (void);

  std::string get_error() const;

  int set_slave (int id);
  int get_slave () const { return slaveid; }

  int read_bits (int address, uint8_t *buf, unsigned int len);
  int read_input_bits (int address, uint8_t *buf, unsigned int len);
  int read_registers (int address, uint16_t *buf, unsigned int len);
  int read_input_registers (int address, uint16_t *buf, unsigned int len);

  int write_bits (int address, const uint8_t *buf, unsigned int len);
  int write_registers (int address, const uint16_t *buf, unsigned int len);

  int write_read_registers (int wraddress, const uint16_t *wrbuf, unsigned int wrlen, int rdaddress, uint16_t *rdbuf, unsigned int rdlen);

  void print (std::ostream& os, bool pr_as_read_syntax = false);
  void print (std::ostream& os, bool pr_as_read_syntax = false) const;
  void print_raw (std::ostream& os, bool pr_as_read_syntax) const;

  int flush (int mode);

  // Properties
  bool is_constant (void) const { return true; }
  bool is_defined (void) const { return true; }
  // < 4.4
  bool is_object (void) const { return true; }
  // 4.4 +
  bool isobject (void) const { return true; }

  octave_base_value * unique_clone (void) { count++; return this;}

  // required to use subsasn
  string_vector map_keys (void) const;
  dim_vector dims (void) const { static dim_vector dv(1, 1); return dv; }

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

  bool is_open(void) const;

  std::string get_type (void) const { return "modbus"; }

  std::string get_status (void) const;

  int set_timeout (double);
  double get_timeout (void) const { return timeout; }

  double get_numretries (void) const { return retries; }
  int set_numretries (int retries);

  std::string get_deviceaddress (void) const { return ipaddress; }

  int get_tcpport (void) const { return ipport; }

  int set_byteorder(const std::string& /* order */);

  std::string get_byteorder() const
  {
    return byteorder;
  }

  int set_wordorder(const std::string& /* order */);

  std::string get_wordorder() const
  {
    return wordorder;
  }

  std::string get_transport (void) const { return transport; }

  std::string get_parity (void) const { return parity; }

  std::string get_rtuport (void) const { return sport; }

  unsigned long get_baudrate (void) const { return baud; }

  int get_databits (void) const { return databits; }

  int get_stopbits (void) const { return stopbits; }

  octave_value get_userdata () const
  {
    return userData;
  }

  void set_userdata (const octave_value &newv)
  {
    userData = newv;
  }

private:
  bool has_property(const std::string &name) const;

  modbus_t *modbus;

  // common properties
  std::string name;
  std::string transport;
  double timeout;
  int retries;
  std::string byteorder;
  std::string wordorder;
  octave_value userData;
  int slaveid;

  // tcpip
  std::string ipaddress;
  int ipport;

  // serial
  unsigned long baud;
  std::string parity;
  int databits;
  int stopbits;
  std::string sport;

  string_vector fieldnames;

  DECLARE_OV_TYPEID_FUNCTIONS_AND_DATA
};

#endif
