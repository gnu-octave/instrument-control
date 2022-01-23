## Copyright (C) 2022 John D <john.donoghue@ieee.org>
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
## @deftypefn {Function File} {@var{struct} = } get (@var{dev})
## @deftypefnx {Function File} {@var{field} = } get (@var{dev}, @var{property})
## Get the properties of modbus object.
##
## @subsubheading Inputs
## @var{dev} - instance of @var{octave_modbus} class.@*
## @var{property} - name of property.@*
##
## @subsubheading Outputs
## When @var{property} was specified, return the value of that property.@*
## otherwise return the values of all properties as a structure.@*
##
## @seealso{@@octave_modbus/set}
## @end deftypefn

function retval = get (dev, property)

  if strcmp( __modbus_properties__ (dev, "Transport"),  "tcpip")
      properties = {'Type', 'WordOrder', 'ByteOrder', 'Name', ...
		'Timeout', 'UserData', 'Transport', 'Port', ...
                'DeviceAddress', 'NumRetries' };
  else
      properties = {'Type', 'WordOrder', 'ByteOrder', 'Name', ...
		'Timeout', 'UserData', 'Transport', 'Port', ...
                'BaudRate', 'DataBits', 'Parity', 'StopBits', ...
                'NumRetries'};
  endif

  if (nargin == 1)
    property = properties;
  elseif (nargin > 2)
    # TODO: multi properties ?
    error ("Too many arguments.\n");
  endif

  if !iscell (property)
    property = {property};
  endif

  valid     = ismember (property, properties);
  not_found = {property{!valid}};

  if !isempty (not_found)
    msg = @(x) error("modbus:get:InvalidArgument", ...
                     "Unknown property '%s'.\n",x);
    cellfun (msg, not_found);
  endif

  property = {property{valid}};
  retval = {};
  for i=1:length(property)
    retval{end+1} = __modbus_properties__ (dev, property{i});
  endfor

  if numel(property) == 1
    retval = retval{1};
  elseif (nargin == 1)
    retval = cell2struct (retval',properties);
  endif

endfunction
