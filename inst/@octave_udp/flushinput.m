## Copyright (C) 2018 John Donoghue
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
## @deftypefn {Loadable Function} {} flushinput (@var{udp})
##
## Flush the pending input, which will also make the BytesAvailable property be 0.
##
## @var{udp} - instance of @var{octave_udp} class.
##
## @seealso{flushoutput}
## @end deftypefn
function flushinput (udp, q)
  __udp_properties__ (udp, 'flush', 1);
end
