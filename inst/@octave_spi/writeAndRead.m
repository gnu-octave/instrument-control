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
## @deftypefn {Function File} {@var{data} =} writeAndRead (@var{obj}, @var{wrdata})
## Writes and reads @var{data} from SPI instrument
##
## @subsubheading Inputs
## @var{obj} is a SPI object.@*
## @var{wrdata} Data to write.@*
##
## @subsubheading Outputs
## @var{data} data values read.@*
##
## @end deftypefn

function data = writeAndRead (obj, wrdata)

if (nargin < 2)
  error("expected data to write");
endif

data = spi_writeAndRead(obj, uint8(wrdata));

endfunction
