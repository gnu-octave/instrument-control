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
## @deftypefn {Function File} {@var{data} =} read (@var{obj})
## @deftypefnx {Function File} {@var{data} =} read (@var{obj}, @var{size})
## Reads @var{data} from SPI instrument
##
## @subsubheading Inputs
## @var{obj} is a SPI object.@*
## @var{size} Number of values to read. (Default: 10).@*
##
## @subsubheading Outputs
## @var{data} data values.@*
##
## @end deftypefn

function data = read (obj, size)

  if (nargin < 2)
    error("read: Size expected");
  endif

  data = spi_read (obj, size);

endfunction
