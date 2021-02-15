## Copyright (C) 2019 John Donoghue <john.donoghue@ieee.org>
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
## @deftypefn {} {@var{data} =} read (@var{dev}, @var{count})
## @deftypefnx {} {@var{data} =} read (@var{dev}, @var{count}, @var{precision})
## Read a specified number of values from a serialport
## using optional precision for valuesize.
##
## @subsubheading Inputs
## @var{dev} - connected serialport device
##
## @var{count} - number of elements to read
##
## @var{precision} - Optional precision for the output data read data.
## Currently known precision values are uint8 (default), int8, uint16, int16, uint32, int32, uint64, uint64 
##
## @subsubheading Outputs
## @var{data} - data read from the device
##
## @seealso{serialport}
## @end deftypefn

function data = read (dev, count, precision)
  if nargin < 2
    print_usage();
  endif
  if nargin < 3
    precision = "uint8";
  endif

  if !ischar(precision)
    error ("Expected precision to be a character type");
  endif

  toread = count;

  switch (precision)
  case {"string"}
    toclass = "char";
    tosize = 1;
  case {"char" "schar" "int8"}
    toclass = "int8";
    tosize = 1;
  case {"uchar" "uint8"}
    toclass = "uint8";
    tosize = 1;
  case {"int16" "short"}
    toclass = "int16";
    tosize = 2;
    toread = toread * 2;
  case {"uint16" "ushort"}
    toclass = "uint16";
    tosize = 2;
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

  eoi=0; tmp=[]; count=0;
  while ((!eoi) && (toread > 0))
    tmp1 = __srlp_read__ (dev, toread);
    if !isempty(tmp1)
      wasread = numel(tmp1);
      count = count + wasread;
      toread = toread - wasread;
    else
      break;
    end
    tmp = [tmp tmp1];
  end

  data = typecast(tmp,toclass);

endfunction
