## Copyright (C) 2020 John Donoghue <john.donoghue#ieee.org>
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
## Set the properties of spi object.
##
## @subsubheading Inputs
## @var{obj} - instance of @var{octave_spi} class.@*
## @var{property} - name of property.@*
##
## If @var{property} is a cell so must be @var{value}, it sets the values of
## all matching properties.
##
## The function also accepts property-value pairs.
##
## @subsubheading Properties
## @table @var
## @item 'name'
## Set the name for the spi socket.
##
## @item 'bitrate'
## Set the bitrate for the spi object.
##
## @item 'clockpolarity'
## Set the clock polarity for the spi object of 'idlehigh' or 'idlelow'.
##
## @item 'clockphase'
## Set the clock phase for the spi object of 'firstedge' or 'secondedge'.
##
## @end table
##
## @subsubheading Outputs
## None
##
## @seealso{@@octave_spi/get}
## @end deftypefn

function set (spi, varargin)

  properties = {'bitrate', 'name', 'clockpolarity', 'clockphase' };

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
    error ('spi:set:InvalidArgument', ...
           'PROPERIES and VALUES must have the same number of elements.');
  endif

  property = tolower(property);
  valid     = ismember (property, properties);
  not_found = {property{!valid}};

  if !isempty (not_found)
    msg = @(x) error ("spi:set:InvalidArgument", ...
                      "Property '%s' not found in spi object.\n",x);
    cellfun (msg, not_found);
  endif

  property = {property{valid}};
  value = {value{valid}};

  for i=1:length(property)
    __spi_properties__ (spi, property{i}, value{i});
  endfor

endfunction
