## Copyright (C) 2019 John Donoghue
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
## @deftypefn {Function File} {} serialbreak (@var{serial})
## @deftypefnx {Function File} {} serialbreak (@var{serial}, @var{time})
## Send a break to the serial port
##
## @subsubheading Inputs
## @var{serial} - serial object@*
## @var{time} - number of milliseconds to break for. If not specified a value of 10 will be used.
##
## @subsubheading Outputs
## None
##
## @seealso{serial}
## @end deftypefn

function serialbreak (serial, mstime)

  if (nargin == 1)
    mstime = 10;
  elseif (nargin > 2)
    error ("Too many arguments.\n");
  end

  __srl_properties__ (serial, 'break', mstime);

end
