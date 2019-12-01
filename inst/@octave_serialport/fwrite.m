## Copyright (C) 2019 John Donoghue <john.donoghue@ieee.org>
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
## Writes @var{data} to serial port instrument
##
## @subsubheading Inputs
## @var{obj} is a serial port object.@*
## @var{data} data to write.@*
## @var{precision} precision of data.@*
##
## @subsubheading Outputs
## returns number of bytes written.
## @end deftypefn

function numbytes = fwrite(obj, data, precision)

  if (nargin < 2)
    print_usage ();
  elseif (nargin < 3)
    precision = [];
  endif

  numbytes = write (obj, data, precision);

endfunction
