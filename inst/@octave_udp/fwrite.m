## Copyright (C) 2016 John Donoghue <john.donoghue@ieee.org>
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
## @deftypefn {Function File} {@var{numbytes} = } fwrite (@var{obj}, @var{data})
## @deftypefnx {Function File} {@var{numbytes} =} fwrite (@var{obj}, @var{data}, @var{precision})
## Writes @var{data} to UDP instrument
##
## @var{obj} is a UDP object
##
## @var{data} data to write
## @var{precision} precision of data
##
## returns number of bytes written.
## @end deftypefn

function numbytes = fwrite(obj, data, precision)

if (nargin < 2)
  print_usage ();
elseif (nargin < 3)
  precision = [];
end

switch (precision)
  case {"char" "schar" "int8"}
    data = int8 (data);
  case {"uchar" "uint8"}
    data = uint8 (data);
  case {"int16" "short"}
    data = int16 (data);
  case {"uint16" "ushort"}
    data = uint16 (data);
  case {"int32" "int"}
    data = int32 (data);
  case {"uint32" "uint"}
    data = uint32 (data);
  case {"long" "int64"}
    data = int64 (data);
  case {"ulong" "uint64"}
    data = uint64 (data);
  case {"single" "float" "float32"}
    data = single (data);
  case {"double" "float64"}
    data = double (data);
  case []
    %% use data as it is
  otherwise
    error ("precision not supported");
end

%% should we handle endianess ?
numbytes = udp_write (obj, typecast(data,'uint8'));

end
