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

// PKG_ADD: autoload ("__modbus_write_read__", "modbus.oct");
DEFUN_DLD (__modbus_write_read__, args, nargout,
        "-*- texinfo -*-\n\
@deftypefn {} {[@var{data} = } __modbus_write_read__ (@var{modbus}, @var{writeaddress}, @var{writedata}, @var{readaddress}, @var{readCount}, @var{serverId})\n \
\n\
Private function to read from modbus interface.\n \
\n\
@subsubheading Inputs\n \
@var{modbus} - instance of @var{octave_modbus} class.@* \
@var{writeaddress} - address of type Integer@* \n \
@var{writedata} - uint16 data to write.@* \n \
@var{readaddress} - address of type Integer@* \n \
@var{readcount} - number of bytes to attempt to read of type Integer@* \n \
@var{serverId} - serverId as an integer\n \
\n\
@subsubheading Outputs\n \
The __modbus_read__() function shall return the read data in @var{data} as uint16 array.\n \
@end deftypefn")
{
#ifndef BUILD_MODBUS
  error("modbus: Your system doesn't support the MODBUS interface");
  return octave_value();
#else

  if (args.length() != 6 || args(0).type_id() != octave_modbus::static_type_id())
    {
      print_usage();
      return octave_value(-1);
    }

  int writeAddress = args(1).int_value();
  // writedata = 2
  int readAddress = args(3).int_value();
  int readCount = args(4).int_value();
  int serverId = args(5).int_value();

  octave_modbus* modbus = NULL;

  const octave_base_value& rep = args(0).get_rep();
  modbus = &((octave_modbus &)rep);

  if (serverId != modbus->get_slave())
    {
      if (modbus->set_slave(serverId) < 0)
        {
          error("modbus_write_read: %s\n", modbus->get_error().c_str());
	  return octave_value();
        }
    }

  octave_value ret_value;

  NDArray writeData = args (2).array_value ();
  OCTAVE_LOCAL_BUFFER (uint16_t, writeBuffer, (writeData.numel ()));

  OCTAVE_LOCAL_BUFFER (uint16_t, readBuffer, readCount);

  if (readBuffer == NULL || writeBuffer == NULL)
    {
      error("modbus_write_read: cannot allocate requested memory: %s\n", strerror(errno));
      return octave_value();
    }

  for (int i = 0; i < writeData.numel (); i++)
    writeBuffer[i] =  static_cast<uint16_t>(writeData(i));
 
  int regs_read = 0;
      
  regs_read = modbus->write_read_registers(writeAddress, writeBuffer, writeData.numel(), readAddress, readBuffer, readCount);

  if (regs_read < 0)
    {
      error("modbus_write_read: %s\n", modbus->get_error().c_str());
      return octave_value();
    }

  // have data here which should be 0s or 1s
  uint16NDArray data( dim_vector(1, regs_read) );

  for (int i = 0; i < regs_read; i++)
     data(i) = readBuffer[i];

  ret_value = data;
 
  return ret_value;
#endif
}

#if 0
%!error __modbus_write_read__(1, 10, 0)
#endif
