// Copyright (C) 2022   John Donoghue   <john.donoghue@ieee.org>
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

#ifdef BUILD_MODBUS
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

#include "modbus_class.h"

static struct timeval
to_timeval(long ms)
{
  struct timeval tv;
  if(ms <= 0)
    {
      tv.tv_usec = 0;
      tv.tv_sec = 0;
    }
  else
    {
      tv.tv_usec = (ms % 1000) * 1000;
      tv.tv_sec = ms/1000;;
    }
  return tv;
}


DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_modbus, "octave_modbus", "octave_modbus");

octave_modbus::octave_modbus (void)
: fieldnames(15)
{
  static bool type_registered = false;

  if (! type_registered)
    {
      type_registered = true;
      register_type ();
    }
  userData = Matrix ();
  modbus = 0;
  ipport = 0;
  name = "";
  timeout = -1;
  retries = 0;
  slaveid = -1;

  wordorder = "big-endian";
  byteorder = "big-endian";

  // common
  fieldnames[0] = "Transport";
  fieldnames[1] = "Type";
  fieldnames[2] = "Name";
  fieldnames[3] = "Status";
  fieldnames[4] = "UserData";

  fieldnames[5] = "Port";
  fieldnames[6] = "NumRetries";
  fieldnames[7] = "Timeout";
  fieldnames[8] = "ByteOrder";
  fieldnames[9] = "WordOrder";
 
  // tcp
  fieldnames[10] = "DeviceAddress";

  // serial
  fieldnames[11] = "BaudRate";
  fieldnames[12] = "DataBits";
  fieldnames[13] = "Parity";
  fieldnames[14] = "StopBits";
}

bool octave_modbus::has_property(const std::string &name) const
{
  for (octave_idx_type i=0; i<fieldnames.numel(); i++)
    {
      if (fieldnames[i] == name)
        {
          // properties available depend on type we are
          if (name == "DeviceAddress")
            {
              if(transport != "tcpip") return false;
            }
          if (name == "BaudRate")
            {
              if(transport != "serialrtu") return false;
            }
          if (name == "DataBits")
            {
              if(transport != "serialrtu") return false;
            }
          if (name == "StopBits")
            {
              if(transport != "serialrtu") return false;
            }
          if (name == "Parity")
            {
              if(transport != "serialrtu") return false;
            }

	  // if here must be a valid property
          return true;
        }
    }
  return false;
}

string_vector 
octave_modbus::map_keys (void) const 
{
  string_vector actual_fields;
  // get list of fields that are valid
  for (octave_idx_type idx = 0; idx < fieldnames.numel(); idx++)
    {
      std::string name = fieldnames[idx];
      if(has_property(name))
        actual_fields.append(name);
    }
  return actual_fields;
}

octave_value_list
octave_modbus::subsref (const std::string& type, const std::list<octave_value_list>& idx, int nargout)
{
  octave_value_list retval;
  int skip = 1;

  switch (type[0])
    {
    default:
      error ("octave_modbus object cannot be indexed with %c", type[0]);
      break;
    case '.':
      {
	std::string property = (idx.front ()) (0).string_value ();
        if (!has_property(property))
	  {
            error ("Unknown property '%s'", property.c_str());
            return retval;
          }
        else
	  {
            octave_value_list ovl;
            // inc ref count as assign this to octave_value
            OV_COUNT++; 
            ovl (0) = octave_value (this);
            ovl (1) = (idx.front ()) (0);
            retval = OCTAVE__FEVAL (std::string ("__modbus_properties__"), ovl, 1);
          }
      }
      break;
    }

  if (idx.size () > 1 && type.length () > 1)
    retval = retval (0).next_subsref (nargout, type, idx, skip);

  return retval;
}

octave_value
octave_modbus::subsasgn (const std::string& type, const std::list<octave_value_list>& idx, const octave_value& rhs)
{
  octave_value retval;

  switch (type[0])
    {
    default:
      error ("octave_modbus object cannot be indexed with %c", type[0]);
      break;
    case '.':
      if (type.length () == 1)
        {
          std::string property = (idx.front ()) (0).string_value ();
          if (! has_property(property))
	    {
              error ("Unknown property '%s'", property.c_str());
              return retval;
            }
          else
            {
              octave_value_list ovl;
              // inc ref count as assign this to octave_value
              OV_COUNT++; 
              ovl (0) = octave_value (this);
              ovl (1) = (idx.front ()) (0);
              ovl (2) = rhs;
              OCTAVE__FEVAL (std::string ("__modbus_properties__"), ovl, 1);
              OV_COUNT++;
              retval = octave_value (this);
            }
        }
      else if (type.length () > 1 && type[1] == '.')
        {
          // pass along any further assignments
          octave_value_list u = subsref (type.substr (0, 1), idx, 1);
          if (u.length () > 0)
            {
              std::list<octave_value_list> next_idx (idx);
              next_idx.erase (next_idx.begin ());
              u (0).subsasgn(type.substr (1), next_idx, rhs);
              OV_COUNT++;
              retval = octave_value (this);
            } 
        }
      else
        {
          error ("octave_modbus invalid index");
        }

    }
  return retval;
}

int
octave_modbus::open_tcp (const std::string &address, int port)
{
  modbus_t *bus = modbus_new_tcp (address.c_str(), port);

  if(!bus)
    {
      error( "could not create new modbus context" );
      return -1;
    }

  if (modbus_connect(bus) == -1) 
    {
      error( "could not connect - '%s'", modbus_strerror(errno));
      modbus_free(bus);
      return -1;
    }

  this->modbus = bus;
  this->transport = "tcpip";
  this->name = "MODBUS-" + address;
  this->ipport = port;
  this->ipaddress = address;
  return 1;
}

std::string
octave_modbus::get_error() const
{
  std::string ret;
  const char * err = modbus_strerror(errno);
  if (err)
    ret = err;
  return ret;
}

int
octave_modbus::open_serial (const std::string &device, unsigned long baud, int dbits, const std::string &parity, int sbits)
{
  char parityval =  'N';
  if(parity == "odd")
    parityval = 'O';
  if(parity == "event")
    parityval = 'E';
  //modbus_t *bus = modbus_new_rtu (device.c_str(), 115200, 'N', 8, 1);
  modbus_t *bus = modbus_new_rtu (device.c_str(), baud, parityval, dbits, sbits);

  if(!bus)
    {
      error( "could not create new modbus context" );
      return -1;
    }

  // do we need this ?
  if (modbus_connect(bus) == -1) 
    {
      error( "could not connect - '%s'", modbus_strerror(errno));
      modbus_free(bus);
      return -1;
    }

  this->modbus = bus;
  this->transport = "serialrtu";
  this->name = "MODBUS-" + device;
  this->baud = baud;
  this->parity = parity;
  this->databits = dbits;
  this->stopbits = sbits;
  this->sport = device;
  return 1;
}
 
octave_modbus::~octave_modbus (void)
{
  close();
}

void
octave_modbus::print (std::ostream& os, bool pr_as_read_syntax)
{
  print_raw (os, pr_as_read_syntax);
  newline (os);
}

void
octave_modbus::print (std::ostream& os, bool pr_as_read_syntax) const
{
  print_raw (os, pr_as_read_syntax);
  newline (os);
}

void
octave_modbus::print_raw (std::ostream& os, bool pr_as_read_syntax) const
{
  std::string ttype = "Serial RTU";
  if(this->transport == "tcpip")
    ttype = "TCPIP";

  os << "  MODBUS " << ttype << " Object " << get_name ();
  newline(os);
  if (this->transport == "tcpip")
    {
      os << " DeviceAddress: " << get_deviceaddress ();
      newline(os);
      //os << "          Port: " << get_port ();
      os << "          Port: " << this->get_tcpport();
      newline(os);
    }
  else if(this->transport == "serialrtu")
    {
      os << "          Port: " << this->get_rtuport();
      newline(os);
      os << "      BaudRate: " << this->get_baudrate();
      newline(os);
      os << "      DataBits: " << this->get_databits();
      newline(os);
      os << "        Parity: " << this->get_parity();
      newline(os);
      os << "      StopBits: " << this->get_stopbits();
      newline(os);
    }
  os << "        Status: " << get_status ();
  newline(os);
  os << "    NumRetries: " << get_numretries (); 
  newline(os);
  os << "       Timeout: " << get_timeout (); 
  newline(os);
  os << "     ByteOrder: " << get_byteorder (); 
  newline(os);
  os << "     WordOrder: " << get_wordorder (); 
  newline(os);
}

int
octave_modbus::set_slave (int id)
{
  if (! is_open ())
    {
      error ("modbus_read: Interface must be opened first...");
      return 0;
    }

  int err = modbus_set_slave(this->modbus, id);

  if(err >= 0)
    this->slaveid = id;

  return err;
}


int
octave_modbus::read_bits (int address, uint8_t *buf, unsigned int len)
{
  if (! is_open ())
    {
      error ("modbus_read: Interface must be opened first...");
      return 0;
    }

  // TODO: handle retries as needed depending errno etc

  ssize_t bytes_read = -1;

  bytes_read = modbus_read_bits(this->modbus, address, len, buf);

  return bytes_read;
}

int
octave_modbus::read_input_bits (int address, uint8_t *buf, unsigned int len)
{
  if (! is_open ())
    {
      error ("modbus_read: Interface must be opened first...");
      return 0;
    }

  ssize_t bytes_read = -1;

  bytes_read = modbus_read_input_bits(this->modbus, address, len, buf);

  return bytes_read;
}

int
octave_modbus::read_registers (int address, uint16_t *buf, unsigned int len)
{
  if (! is_open ())
    {
      error ("modbus_read: Interface must be opened first...");
      return 0;
    }

  ssize_t bytes_read = -1;

  bytes_read = modbus_read_registers(this->modbus, address, len, buf);

  return bytes_read;
}

int
octave_modbus::read_input_registers (int address, uint16_t *buf, unsigned int len)
{
  if (! is_open ())
    {
      error ("modbus_read: Interface must be opened first...");
      return 0;
    }

  ssize_t bytes_read = -1;

  bytes_read = modbus_read_input_registers(this->modbus, address, len, buf);

  return bytes_read;
}

int
octave_modbus::write_bits (int address, const uint8_t *buf, unsigned int len)
{
  if (! is_open ())
    {
      error ("modbus_write: Interface must be opened first...");
      return 0;
    }

  ssize_t regs_wrote = -1;

  regs_wrote = modbus_write_bits(this->modbus, address, len, buf);

  return regs_wrote;
}

int
octave_modbus::write_registers (int address, const uint16_t *buf, unsigned int len)
{
  if (! is_open ())
    {
      error ("modbus_write: Interface must be opened first...");
      return 0;
    }

  ssize_t regs_wrote = -1;

  regs_wrote = modbus_write_registers(this->modbus, address, len, buf);

  return regs_wrote;
}

int
octave_modbus::write_read_registers(int wraddress, const uint16_t *wrbuf, unsigned int wrlen, int rdaddress, uint16_t *rdbuf, unsigned int rdlen)
{
  if (! is_open ())
    {
      error ("modbus_write_read: Interface must be opened first...");
      return 0;
    }

  ssize_t regs_read = -1;

  regs_read = modbus_write_and_read_registers(this->modbus, wraddress, wrlen, wrbuf, rdaddress, rdlen, rdbuf);

  return regs_read;
}

int
octave_modbus::set_timeout (double newtimeout)
{
  if (! is_open ())
    {
      error ("modbus: Interface must be opened first...");
      return -1;
    }

  if (newtimeout < -1 )
    {
      error ("modbus_timeout: timeout value must be -1 or positive");
      return -1;
    }

  struct timeval tv = to_timeval((long)(newtimeout*1000L));
#ifdef HAVE_MODBUS_SET_RESPONSE_TIMEOUT2
  modbus_set_response_timeout(this->modbus, tv.tv_sec, tv.tv_usec);
#else
  modbus_set_response_timeout(this->modbus, &tv);
#endif

  timeout = newtimeout;

  return 1;
}

int
octave_modbus::set_numretries (int newretries)
{
  if (! is_open ())
    {
      error ("modbus: Interface must be opened first...");
      return -1;
    }

  if (newretries < 0 )
    {
      error ("modbus_numretries: must be 0 or positive");
      return -1;
    }

  // we use the num retries to handle errors
  retries = newretries;

  return 1;
}

std::string
octave_modbus::set_name (const std::string &n)
{
  if (n.length() == 0 )
    {
      error ("modbus_name: value must be non empty");
    }
  else
    {
      name = n;
    }
 
  return name;
}

bool
octave_modbus::is_open (void) const
{
  return modbus != 0;
}

std::string
octave_modbus::get_status (void) const
{
  if (! is_open ()) 
    {
      return "closed";
    }
  else
    {
      return "open";
    }
}

int
octave_modbus::close (void)
{
  int retval = -1;

  if (is_open ())
    {
      modbus_close(modbus);
      modbus_free(modbus);
      modbus = 0;
      retval = 0;
    }

  return retval;
}

int
octave_modbus::flush (int mode)
{
  int retval = -1;

  if (is_open())
    {
      if (mode == 0 || mode == 2)
        {
	  // we are sending data as we get it, so no outout
	  // buffers to flush
        }
      if (mode == 1 || mode == 2)
        {
          retval = modbus_flush(this->modbus);
        }
    }

  return retval;
}

int
octave_modbus::set_byteorder(const std::string& neworder)
{
  std::string order = neworder;
  std::transform (order.begin (), order.end (), order.begin (), ::tolower);
  if (order == "big" || order == "big-endian")
    byteorder = "big-endian";
  else if (order == "little" || order == "little-endian")
    byteorder = "little-endian";
 else
    error ("octave_modbus invalid byteorder");

 return 1;
}

int
octave_modbus::set_wordorder(const std::string& neworder)
{
  std::string order = neworder;
  std::transform (order.begin (), order.end (), order.begin (), ::tolower);
  if (order == "big" || order == "big-endian")
    wordorder = "big-endian";
  else if (order == "little" || order == "little-endian")
    wordorder = "little-endian";
 else
    error ("octave_modbus invalid wordorder");

 return 1;
}

#endif
