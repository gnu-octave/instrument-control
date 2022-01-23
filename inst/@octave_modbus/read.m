## Copyright (C) 2022 John Donoghue <john.donoghue@ieee.org>
## 
## This program is free software: you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.

## -*- texinfo -*- 
## @deftypefn {} {@var{data} =} read (@var{dev}, @var{target}, @var{address})
## @deftypefnx {} {@var{data} =} read (@var{dev}, @var{target}, @var{address}, @var{count})
## @deftypefnx {} {@var{data} =} read (@var{dev}, @var{target}, @var{address}, @var{count}, @var{serverId}, @var{precision})
## Read data from modbus device @var{dev} target @var{target} starting at address @var{address}.
##
## @subsubheading Inputs
## @var{dev} - connected modbus device
##
## @var{target} - target type to read. One of 'coils', 'inputs', 'inputregs' or 'holdingregs'
##
## @var{address} - address to start reading from.
##
## @var{count} - number of elements to read. If not provided, count is 1.
##
## @var{serverId} - address to send to (0-247). Default of 1 is used if not specified.
##
## @var{precision} - Optional precision for how to interpret the read data.
## Currently known precision values are uint16 (default), int16, uint32, int32, uint64, uint64, single, double.
##
## @subsubheading Outputs
## @var{data} - data read from the device
##
## @seealso{modbus}
## @end deftypefn

function data = read (dev, target, address, count, serverid, precision)
  if nargin < 3
    print_usage();
  endif

  if nargin < 4
    count = 1;
  endif
  if nargin < 5
    serverid = 1;
  endif
  if nargin < 6
    precision = "uint16";
  endif

  if ! isnumeric(address) || address < 0
    error ("Expected address to be a number.");
  endif

  if ! isnumeric(count) || count < 1
    error ("Expected count to be a positive number.");
  endif

  if ! isnumeric(serverid) || serverid < 0 || serverid > 247
    error ("Expected serverId to be a number between 0 .. 247");
  endif

  if !ischar(precision)
    error ("Expected precision to be a character type");
  endif

  toread = count;

  # precision only used for inputregs and holdingregs
  switch (precision)
  case {"int16" "short"}
    toclass = "int16";
    tosize = 2;
    toread = toread * 2;
  case {"uint16" "ushort"}
    toclass = "uint16";
    tosize = 2;
    toread = toread * 2;
  case {"int32" "int"}
    toclass = "int32";
    tosize = 4;
    toread = toread * 4;
  case {"uint32" "uint"}
    toclass = "uint32";
    tosize = 4;
    toread = toread * 4;
  case {"long" "int64"}
    toclass = "int64";
    toread = toread * 8;
    tosize = 8;
  case {"ulong" "uint64"}
    toclass = "uint64";
    toread = toread * 8;
    tosize = 8;
  case {"single" "float" "float32"}
    toclass = "single";
    tosize = 4;
    toread = toread * 4;
  case {"double" "float64"}
    toclass = "double";
    tosize = 8;
    toread = toread * 8;
  otherwise
    error ("precision not supported");
  endswitch

  switch (target)
  case "coils"
    # single bit output bits (count = 1 .. 2000)
  case "inputs"
    # single bit input regs
  case "inputregs"
    # 16 bit input read regs (count = 1 ... 125)
  case "holdingregs"
    # 16 bit read/write reg
  otherwise
    error ("Invalid target type");
  endswitch

  data = __modbus_read__(dev, target, address, count, serverid);

  # TODO: use precision to combine regs etc

endfunction
