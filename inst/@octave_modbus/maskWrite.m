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
## @deftypefn {} {@var{data} =} maskWrite (@var{dev}, @var{address}, @var{andmask}, @var{ormask})
## @deftypefnx {} {@var{data} =} maskWrite (@var{dev}, @var{address}, @var{andmask}, @var{ormask}, @var{serverid})
## Read holding register at @var{address} from modbus device @var{dev} apply masking and write the change data.
##
## writeregister value = (readregister value AND andMask) OR (orMask AND (NOT andMask))
##
## @subsubheading Inputs
## @var{dev} - connected modbus device
##
## @var{address} - address to read from.
##
## @var{andmask} - AND mask to apply to the register
##
## @var{ormask} - OR mask to apply to the register
##
## @var{serverId} - address to send to (0-247). Default of 1 is used if not specified.
##
## @subsubheading Outputs
## @var{data} - data read from the device
##
## @seealso{modbus}
## @end deftypefn

function data = maskWrite (dev, address, andmask, ormask, serverid)
  if nargin < 4
    print_usage();
  endif

  if nargin < 5
    serverid = 1;
  endif

  if ! isnumeric(address) || address < 0
    error ("Expected address to be a number.");
  endif

  if ! isnumeric(ormask)
    error ("Expected ormask to be a number.");
  endif

  if ! isnumeric(andmask)
    error ("Expected andmask to be a number.");
  endif

  if ! isnumeric(serverid) || serverid < 0 || serverid > 247
    error ("Expected serverId to be a number between 0 .. 247");
  endif

  data = read(dev, "holdingregs", address, 1, serverid);

  # manipulate for
  if !isempty(data)
    value = data(1);
    value = bitand(value, andmask);
    value = bitor(value, ormask);
    data(1) = value;
  endif

  write(dev, "holdingregs", address, data, serverid);

endfunction
