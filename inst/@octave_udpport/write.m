## Copyright (C) 2021 John Donoghue <john.donoghue@ieee.org>
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
## @deftypefn {Function File} {@var{numbytes} = } write (@var{obj}, @var{data})
## @deftypefnx {Function File} {@var{numbytes} = } write (@var{obj}, @var{data}, @var{destinationAddress}, @var{destinationPort}))
## @deftypefnx {Function File} {@var{numbytes} =} write (@var{obj}, @var{data}, @var{datatype})
## @deftypefnx {Function File} {@var{numbytes} =} write (@var{obj}, @var{data}, @var{datatype}, @var{destinationAddress}, @var{destinationPort})
## Writes @var{data} to UDP instrument
##
## @subsubheading Inputs
## @var{obj} is a UDPPort object.@*
## @var{data} data to write.@*
## @var{datatype} datatype of data. If not specified defaults to uint8.@*
## @var{destinationAddress} ipaddress to send to. If not specified, use the previously used remote address.@*
## @var{destinationPort} port to send to. If not specified, use the remote port.@*
##
## @subsubheading Outputs
## returns number of bytes written.
## @end deftypefn

function numbytes = write(obj, data, varargin)

  if (nargin < 2)
    print_usage ();
  endif

  datatype = "uint8";
  destinationAddress = "";
  destinationPort = 0;

  if (nargin == 3)
    datatype = varargin{1};
  elseif (nargin == 4)
    destinationAddress = varargin{1};
    destinationPort = varargin{2};
  elseif (nargin == 5)
    datatype = varargin{1};
    destinationAddress = varargin{2};
    destinationPort = varargin{3};
  elseif nargin > 5
    print_usage ();
  endif

  switch (datatype)
    case {"char" "schar" "int8", "string"}
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
    otherwise
      error ("datatype not supported");
  endswitch

  if !isempty(destinationAddress)
    if !ischar(destinationAddress)
      error ("Expected address as a string");
    endif
    numbytes = __udpport_write__ (obj, typecast(data,'uint8'), destinationAddress, destinationPort);
  else
    numbytes = __udpport_write__ (obj, typecast(data,'uint8'));
  endif
endfunction
