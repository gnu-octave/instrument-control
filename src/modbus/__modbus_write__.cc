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

#include <octave/oct.h>

#ifdef HAVE_CONFIG_H
#  include "../config.h"
#endif

#ifdef BUILD_MODBUS
#include <octave/uint8NDArray.h>

#include <errno.h>

#include "modbus_class.h"

#endif

// PKG_ADD: autoload ("__modbus_write__", "modbus.oct");
DEFUN_DLD (__modbus_write__, args, nargout,
        "-*- texinfo -*-\n\
@deftypefn {} {@var{count} = } __modbus_write__ (@var{modbus}, @var{target}, @var{address}, @var{data}, @var{serverId})\n \
\n\
Private function to write to modbus interface.\n \
\n\
@subsubheading Inputs\n \
@var{modbus} - instance of @var{octave_modbus} class.@* \
@var{target} - target for read type@* \n \
@var{address} - address of type Integer@* \n \
@var{data} - data to write to modbus@* \n \
@var{serverId} - serverId as an integer\n \
\n\
@subsubheading Outputs\n \
The __modbus_write__() function shall return number of bytes successfully written.\n \
@end deftypefn")
{
#ifndef BUILD_MODBUS
  error("modbus: Your system doesn't support the MODBUS interface");
  return octave_value();
#else

  if (args.length() != 5 || args(0).type_id() != octave_modbus::static_type_id())
    {
      print_usage();
      return octave_value(-1);
    }

  std::string target = args(1).string_value();
  int address = args(2).int_value();
  //data = args(3).int_value();
  int serverId = args(4).int_value();

  octave_modbus* modbus = NULL;

  const octave_base_value& rep = args(0).get_rep();
  modbus = &((octave_modbus &)rep);

  if (serverId != modbus->get_slave())
    {
      if (modbus->set_slave(serverId) < 0)
        {
          error("modbus_write: %s\n", modbus->get_error().c_str());
	  return octave_value();
        }
    }

  int retval = -1;
  // uint8 for coils and inputs
  // uint16 for inputregs and holdingregs
  if (target == "coils")
    { 
      NDArray data = args (3).array_value ();
      OCTAVE_LOCAL_BUFFER (uint8_t, buf, (data.numel ()));

      if (buf == NULL)
        {
          error ("__modbus_write__: cannot allocate requested memory");
          return octave_value (-1);  
        }

      for (int i = 0; i < data.numel (); i++)
        buf[i] =  static_cast<uint8_t>(data(i));


      retval = modbus->write_bits(address, buf, data.numel());

      if (retval < 0)
        {
          error("modbus_write: %s\n", modbus->get_error().c_str());
	  return octave_value(-1);
        }
    }
  else if (target == "holdingregs")
    {
      NDArray data = args (3).array_value ();
      OCTAVE_LOCAL_BUFFER (uint16_t, buf, (data.numel ()));

      if (buf == NULL)
        {
          error ("__modbus_write__: cannot allocate requested memory");
          return octave_value (-1);  
        }

      for (int i = 0; i < data.numel (); i++)
        buf[i] =  static_cast<uint16_t>(data(i));

      retval = modbus->write_registers(address, buf, data.numel());

      if (retval < 0)
        {
          error("modbus_write: %s\n", modbus->get_error().c_str());
	  return octave_value(-1);
        }
    }
  else
    {
      error ("__modbus_write__: invalid target");
      return octave_value (-1);  
    }

  return octave_value(retval);
#endif
}

#if 0
%!error __modbus_write__(1, 10, 0)
#endif
