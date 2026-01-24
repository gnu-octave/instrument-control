## Copyright (C) 2020 John Donoghue  <john.donoghue@ieee.org>
##
## This program is free software; you can redistribute it and/or modify it under
## the terms of the GNU General Public License as published by the Free Software
## Foundation; either version 3 of the License, or (at your option) any later
## version.
##
## This program is distributed in the hope that it will be useful, but WITHOUT
## ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
## FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
## details.
##
## You should have received a copy of the GNU General Public License along with
## this program; if not, see <http://www.gnu.org/licenses/>.

## -*- texinfo -*-
## @deftypefn {} {@var{data} =} read (@var{obj})
## @deftypefnx {} {@var{data} =} read (@var{obj}, @var{size})
## @deftypefnx {} {@var{data} =} read (@var{obj}, @var{size}, @var{datatype})
## Reads @var{data} from UDP instrument
##
## @subsubheading Inputs
## @var{obj} is a UDP object.@*
## @var{size} Number of values to read. (Default: BytesAvailable).@*
## @var{datatype} datatype of data.@*
##
## @subsubheading Outputs
## @var{data} data read.@*
##
## @end deftypefn

function data = read (obj, cnt, datatype)

  if (nargin < 3)
    datatype = 'uint8';
  endif

  switch (datatype)
    case {"char" "schar" "int8"}
      toclass = "int8";
      tosize=1;
    case {"uchar" "uint8"}
      toclass = "uint8";
      tosize=1;
    case {"int16" "short"}
      toclass = "int16";
      tosize=2;
    case {"uint16" "ushort"}
      toclass = "uint16";
      tosize=2;
    case {"int32" "int"}
      toclass = "int32";
      tosize=4;
    case {"uint32" "uint"}
      toclass = "uint32";
      tosize=4;
    case {"long" "int64"}
      toclass = "int64";
      tosize=8;
    case {"ulong" "uint64"}
      toclass = "uint64";
      tosize=8;
    case {"single" "float" "float32"}
      toclass = "single";
      tosize=4;
    case {"double" "float64"}
      toclass = "double";
      tosize=8;
    otherwise
      error ("precision not supported");
  endswitch

  if (nargin < 2)
    cnt = int32(obj.bytesavailable/tosize);
  else
    cnt = cnt*tosize;
  endif

  tmp = udp_read (obj, cnt, get(obj, 'timeout')*1000);

  data = typecast(tmp,toclass);

endfunction
