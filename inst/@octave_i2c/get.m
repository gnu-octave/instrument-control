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
## @deftypefn {Function File} {@var{struct} = } get (@var{i2c})
## @deftypefnx {Function File} {@var{field} = } get (@var{i2c}, @var{property})
## Get the properties of i2c object.
##
## @subsubheading Inputs
## @var{i2c} - instance of @var{octave_i2c} class.@*
##
## @var{property} - name of property.@*
##
## @subsubheading Outputs
## When @var{property} was specified, return the value of that property.@*
## otherwise return the values of all properties as a structure.@*
##
## @seealso{@@octave_i2c/set}
## @end deftypefn

function retval = get (i2c, property)

  properties = {'name', 'remoteaddress', 'status', ...
                'port'};

  if (nargin == 1)
    property = properties;
  elseif (nargin > 2)
    error ("Too many arguments.\n");
  end

  if !iscell (property)
    property = {property};
  end
  property = tolower(property);

  valid     = ismember (property, properties);
  not_found = {property{!valid}};

  if !isempty (not_found)
    msg = @(x) error("i2c:get:InvalidArgument", ...
                     "Unknown property '%s'.\n",x);
    cellfun (msg, not_found);
  end

  property = {property{valid}};
  func     = @(x) __i2c_properties__ (i2c, x);
  retval   = cellfun (func, property, 'UniformOutput', false);

  if numel(property) == 1
    retval = retval{1};
  elseif (nargin == 1)
    retval = cell2struct (retval',properties);
  end

end
