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
## @deftypefn {Function File} {@var{list} = } serialportlist ()
## @deftypefnx {Function File} {@var{list} = } serialportlist ("all")
## @deftypefnx {Function File} {@var{list} = } serialportlist ("available")
## Returns a list of all serial ports detected in the system.
##
## @subsubheading Inputs
## 'all' - show all serial ports (same as providing no arguments)
## 'available' - show only serial ports that are available for use
##
## @subsubheading Outputs
## @var{list} is a string cell array of serial ports names detected
## in the system.
##
## @seealso{instrhwinfo("serialport")}
## @end deftypefn

function out = serialportlist (listtype)

  if nargin > 1
    print_usage ();
  endif

  if nargin < 1
    listtype = "all";
  endif

  ports = instrhwinfo("serialport");

  if strcmpi(listtype, "available")
    tmp = {};
    for i=1:numel(ports)
      try
	portname = ports{i};
        s = serialport (portname, 9600);
	clear s;
        tmp{end+1} = portname;
      catch err
        # no nothing here
      end_try_catch
    endfor
    out = tmp;
  else
    out = ports;
  endif
endfunction

%!assert(serialportlist, instrhwinfo("serialport"))
%!assert(serialportlist("all"), instrhwinfo("serialport"))
