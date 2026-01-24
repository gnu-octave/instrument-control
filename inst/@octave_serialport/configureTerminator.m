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
## @deftypefn {} {} configureTerminator (@var{serial}, @var{term})
## @deftypefnx {} {} configureTerminator (@var{serial}, @var{readterm}, @var{writeterm})
## Set terminator for ASCII string manipulation
##
## @subsubheading Inputs
## @var{serial} - serialport object@*
## @var{term} - terminal value for both read and write@*
## @var{readterm} = terminal value type for read data@*
## @var{writeterm} = terminal value for written data@*
##
## The terminal can be either strings "cr", "lf" (default), "lf/cr" or an integer between 0 to 255.
##
## @subsubheading Outputs
## None
##
## @seealso{serialport}
## @end deftypefn

function configureTerminator (serial, readterm, writeterm)

  if nargin < 2
    error ("Expected terminal");
  elseif nargin == 2
    __srlp_properties__ (serial, 'terminator', readterm);
  elseif nargin == 3
    __srlp_properties__ (serial, 'terminator', readterm, writeterm);
  else
    error ("Expected read and write terminal only");
  endif

endfunction
