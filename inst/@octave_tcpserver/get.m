## Copyright (C) 2022 John Donoghue <john.donoghue@ieee.org>
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
## @deftypefn {Function File} {@var{struct} = } get (@var{tcpserver})
## @deftypefnx {Function File} {@var{field} = } get (@var{tcpserver}, @var{property})
## Get the properties of tcpserver object.
##
## @subsubheading Inputs
## @var{tcpserver} - instance of @var{octave_tcpserver} class.@*
## @var{property} - name of property.@*
##
## @subsubheading Outputs
## When @var{property} was specified, return the value of that property.@*
## otherwise return the values of all properties as a structure.@*
##
## @seealso{@@octave_tcpserver/set}
## @end deftypefn

function retval = get (tcpserver, property)

  properties = {'Name', 'ServerAddress', 'ServerPort', ...
                'ClientAddress', 'ClientPort', ...
                'Type', 'Status', 'Timeout', 'UserData', ...
		'NumBytesAvailable', 'NumBytesWritten', ...
		'Terminator', 'Connected' };

  if (nargin == 1)
    property = properties;
  elseif (nargin > 2)
    error ("Too many arguments.\n");
  endif

  if !iscell (property)
    property = {property};
  endif

  valid     = ismember (property, properties);
  not_found = {property{!valid}};

  if !isempty (not_found)
    msg = @(x) error("tcpserver:get:InvalidArgument", ...
                     "Unknown property '%s'.\n",x);
    cellfun (msg, not_found);
  endif

  property = {property{valid}};
  retval = {};
  for i=1:length(property)
    retval{end+1} = __tcpserver_properties__ (tcpserver, property{i});
  endfor

  if numel(property) == 1
    retval = retval{1};
  elseif (nargin == 1)
    retval = cell2struct (retval',properties);
  endif

endfunction
