## Copyright (C) 2025 John Donoghue
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
## @deftypefn {Function File} {@var{status}} getpinstatus (@var{dev})
## Get status of visadev serial pins
##
## @subsubheading Inputs
## @var{dev} - visadev serial object@*
##
## @subsubheading Outputs
## @var{status} - a structure with the logic names of ClearToSend, DataSetReady, CarrierDetect, and RingIndicator
##
## @seealso{serialport}
## @end deftypefn

function status = getpinstatus (serial)

  status = __visadev_dispatch__ (serial, 'pinstatus');

endfunction
