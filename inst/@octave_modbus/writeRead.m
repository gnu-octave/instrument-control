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
## @deftypefn {} {@var{data} =} writeRead (@var{dev}, @var{writeAddress}, @var{values}, @var{readAddress}, @var{readcount})
## @deftypefnx {} {@var{data} =} writeRead (@var{dev}, @var{writeAddress}, @var{values}, @var{readAddress}, @var{readcount}, @var{serverId})
## @deftypefnx {} {@var{data} =} writeRead (@var{dev}, @var{writeAddress}, @var{values}, @var{writePrecision}, @var{readAddress}, @var{readCount}, @var{readPrecision})
## Write data @var{values} to the modbus device @var{dev} holding registers starting at address @var{writeAddress}
## and then read @var{readCount} register values starting at address @var{readAddress}.
##
## @subsubheading Inputs
## @var{dev} - connected modbus device
##
## @var{writeAddress} - address to start writing to.
##
## @var{values} - data to write to the device.
##
## @var{readAddress} - address to start reading from.
##
## @var{readCount} - number of elements to read.
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

function data = writeRead (varargin)
  # num args should be 5, 6 or 7
  if nargin < 5 || nargin > 7
    print_usage();
  endif

  dev = varargin{1};
  writeAddress = varargin{2};
  values = varargin{3};

  if nargin == 7
    writePrecision = varargin{4};
    readAddress = varargin{5};
    readCount = varargin{6};
    readPrecision = varargin{7};
    serverId = 1;
  else
     writePrecision = "uint16";
     readPrecision = "uint16";

     readAddress = varargin{4};
     readCount = varargin{5};

     if nargin == 6
       serverId = varargin{6}
     else
       serverId = 1;
     endif
  endif

  if ! isnumeric(writeAddress) || writeAddress < 0
    error ("Expected writeAddress to be a number.");
  endif

  if ! isnumeric(readAddress) || readAddress < 0
    error ("Expected readAddress to be a number.");
  endif

  if ! isnumeric(readCount) || readCount < 1
    error ("Expected readCount to be a positive number.");
  endif

  if ! isnumeric(serverId) || serverId < 0 || serverId > 247
    error ("Expected serverId to be a number between 0 .. 247");
  endif

  if !ischar(readPrecision)
    error ("Expected readPrecision to be a character type");
  endif

  if !ischar(writePrecision)
    error ("Expected writePrecision to be a character type");
  endif

  toread = readCount;

  # precision only used for inputregs and holdingregs
  # TODO: current doesnt use the precision
  switch (readPrecision)
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
    error ("readPrecision not supported");
  endswitch

  data = uint16(values)

  data = __modbus_write_read__(dev, writeAddress, data, readAddress, readCount, serverId);

endfunction
