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
## @deftypefn {} {} write (@var{dev}, @var{target}, @var{address}, @var{values})
## @deftypefnx {} {} read (@var{dev}, @var{target}, @var{address}, @var{values}, @var{serverId}, @var{precision})
## Write data @var{data} to modbus device @var{dev} target @var{target} starting at address @var{address}.
##
## @subsubheading Inputs
## @var{dev} - connected modbus device
##
## @var{target} - target type to read. One of 'coils' or 'holdingregs'
##
## @var{address} - address to start reading from.
##
## @var{data} - data to write.
##
## @var{serverId} - address to send to (0-247). Default of 1 is used if not specified.
##
## @var{precision} - Optional precision for how to interpret the write data.
## Currently known precision values are uint16 (default), int16, uint32, int32, uint64, uint64, single, double.
##
## @subsubheading Outputs
## None
##
## @seealso{modbus}
## @end deftypefn

function write (dev, target, address, data, serverid, precision)
  if nargin < 4
    print_usage();
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

  if ! isnumeric(serverid) || serverid < 0 || serverid > 247
    error ("Expected serverId to be a number between 0 .. 247");
  endif

  if !ischar(precision)
    error ("Expected precision to be a character type");
  endif

  # precision only used for holdingregs
  switch (precision)
  case {"int16" "short"}
    toclass = "int16";
    tosize = 2;
  case {"uint16" "ushort"}
    toclass = "uint16";
    tosize = 2;
  case {"int32" "int"}
    toclass = "int32";
    tosize = 4;
  case {"uint32" "uint"}
    toclass = "uint32";
    tosize = 4;
  case {"long" "int64"}
    toclass = "int64";
    toread = toread * 8;
  case {"ulong" "uint64"}
    toclass = "uint64";
    toread = toread * 8;
  case {"single" "float" "float32"}
    toclass = "single";
    tosize = 4;
  case {"double" "float64"}
    toclass = "double";
    tosize = 8;
  otherwise
    error ("precision not supported");
  endswitch

  switch (target)
  case "coils"
    # single bit output bits (count = 1 .. 2000)
    data = uint8(data);
  case "holdingregs"
    # 16 bit read/write reg
    data = uint16(data);
  otherwise
    error ("Invalid target type");
  endswitch

  #data = typecast(tmp,toclass);

  numbytes = __modbus_write__(dev, target, address, data, serverid);

endfunction
