## Copyright (C) 2021 John Donoghue <john.donoghue@ieee.org>
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
## @deftypefn {Function File} {@var{struct} = } get (@var{tcpclient})
## @deftypefnx {Function File} {@var{field} = } get (@var{tcpclient}, @var{property})
## Get the properties of tcpclient object.
##
## @subsubheading Inputs
## @var{tcpclient} - instance of @var{octave_tcpclient} class.@*
## @var{property} - name of property.@*
##
## @subsubheading Outputs
## When @var{property} was specified, return the value of that property.@*
## otherwise return the values of all properties as a structure.@*
##
## @seealso{@@octave_tcpclient/set}
## @end deftypefn

function retval = get (tcpclient, property)

  properties = {'Name', 'Address', 'Port', ...
                'Type', 'Status', 'Timeout', 'UserData', ...
		'NumBytesAvailable', 'NumBytesWritten', ...
		'Terminator' };

  if (nargin == 1)
    property = properties;
  elseif (nargin > 2)
    error ("Too many arguments.\n");
  end

  if !iscell (property)
    property = {property};
  end

  valid     = ismember (property, properties);
  not_found = {property{!valid}};

  if !isempty (not_found)
    msg = @(x) error("tcpclient:get:InvalidArgument", ...
                     "Unknown property '%s'.\n",x);
    cellfun (msg, not_found);
  end

  property = {property{valid}};
  retval = {};
  for i=1:length(property)
    retval{end+1} = __tcpclient_properties__ (tcpclient, property{i});
  endfor

  if numel(property) == 1
    retval = retval{1};
  elseif (nargin == 1)
    retval = cell2struct (retval',properties);
  end

end
