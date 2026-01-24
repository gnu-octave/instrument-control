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
## @deftypefn {} set (@var{obj}, @var{property},@var{value})
## @deftypefnx {} set (@var{obj}, @var{property},@var{value},@dots{})
## Set the properties of modbus object.
##
## @subsubheading Inputs
## @var{obj} - instance of @var{octave_modbus} class.@*
## @var{property} - name of property.@*
##
## If @var{property} is a cell so must be @var{value}, it sets the values of
## all matching properties.
##
## The function also accepts property-value pairs.
##
## @subsubheading Properties
## @table @var
## @item 'Name'
## Set the stored string name of the object.
##
## @item 'Timeout'
## Set the timeout value.
##
## @item 'Numretries'
## Set the numretries value.
##
## @item 'ByteOrder'
## Set the byteorder value
##
## @item 'WordOrder'
## Set the wordorder value
##
## @item 'UserData'
## Set the userdata value
##
## @end table
##
## @subsubheading Outputs
## None
##
## @seealso{@@octave_modbus/get}
## @end deftypefn

function set (dev, varargin)

  properties = {'Name', 'Timeout', 'ByteOrder', 'WordOrder', ...
                'UserData', 'NumRetries'};

  if numel (varargin) == 1 && isstruct (varargin{1})
    property = fieldnames (varargin{1});
    func  = @(x) getfield (varargin{1}, x);
    value = cellfun (func, property, 'UniformOutput', false);
  elseif numel (varargin) == 2 && iscell (varargin{1}) && iscell (varargin{2})
  %% The arguments are two cells, expecting fields and values.
    property = varargin{1};
    value = varargin{2};
  else
    property = {varargin{1:2:end}};
    value = {varargin{2:2:end}};
  endif

  if numel (property) != numel (value)
    error ('modbus:set:InvalidArgument', ...
           'PROPERIES and VALUES must have the same number of elements.');
  endif

  property = tolower(property);
  valid     = ismember (property, properties);
  not_found = {property{!valid}};

  if !isempty (not_found)
    msg = @(x) error ("modbus:set:InvalidArgument", ...
                      "Property '%s' not found in serial object.\n",x);
    cellfun (msg, not_found);
  endif

  property = {property{valid}};
  value = {value{valid}};

  for i=1:length(property)
    __modbus_properties__ (dev, property{i}, value{i});
  endfor

endfunction
