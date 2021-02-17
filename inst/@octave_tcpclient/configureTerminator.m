## Copyright (C) 2021 John Donoghue
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
## @deftypefn {Function File} {} configureTerminator (@var{tcp}, @var{term})
## @deftypefnx {Function File} {} configureTerminator (@var{tcp}, @var{readterm}, @var{writeterm})
## Set terminator on a tcpclient object for ASCII string manipulation
##
## @subsubheading Inputs
## @var{tcp} - tcpclient object@*
## @var{term} - terminal value for both read and write@*
## @var{readterm} = terminal value type for read data@*
## @var{writeterm} = terminal value for written data@*
##
## The terminal can be either strings "cr", "lf" (default), "lf/cr" or an integer between 0 to 255.
##
## @subsubheading Outputs
## None
##
## @seealso{tcpport}
## @end deftypefn

function configureTerminator (tcp, readterm, writeterm)

  if nargin < 2
    error ("Expected terminal");
  elseif nargin == 2
    __tcpclient_properties__ (tcp, 'terminator', readterm);
  elseif nargin == 3
    __tcpclient_properties__ (tcp, 'terminator', readterm, writeterm);
  else
    error ("Expected read and write terminal only");
  endif

endfunction
