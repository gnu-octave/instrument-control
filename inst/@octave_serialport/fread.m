## Copyright (C) 2019 John Donoghue  <john.donoghue@ieee.org>
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
## @deftypefn {Function File} {@var{data} =} fread (@var{obj})
## @deftypefnx {Function File} {@var{data} =} fread (@var{obj}, @var{size})
## @deftypefnx {Function File} {@var{data} =} fread (@var{obj}, @var{size}, @var{precision})
## @deftypefnx {Function File} {[@var{data},@var{count}] =} fread (@var{obj}, ...)
## @deftypefnx {Function File} {[@var{data},@var{count},@var{errmsg}] =} fread (@var{obj}, ...)
## Reads @var{data} from serial port instrument
##
## @subsubheading Inputs
## @var{obj} is a serialport object.@*
## @var{size} Number of values to read.@*
## @var{precision} precision of data.@*
##
## @subsubheading Outputs
## @var{data} The read data.@*
## @var{count} number of values read.@*
## @var{errmsg} read operation error message.@*
##
## @end deftypefn

function [data, count, errmsg] = fread (obj, size, precision)

if (nargin < 2)
  size = get(obj, 'numbytesavailable');
end

if (nargin < 3)
  precision = 'uchar';
end


data = read(obj,size, precision);
errmsg = '';
count = numel(data);

endfunction
