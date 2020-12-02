## Copyright (C) 2020 John Donoghue <john.donoghue@ieee.org>
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
## @deftypefn {Function File} {@var{struct} = } get (@var{spi})
## @deftypefnx {Function File} {@var{field} = } get (@var{spi}, @var{property})
## Get the properties of spi object.
##
## @subsubheading Inputs
## @var{spi} - instance of @var{octave_spi} class.@*
##
## @var{property} - name of property.@*
##
## @subsubheading Properties
## @table @var
## @item 'name'
## Name for the spi socket.
##
## @item 'bitrate'
## The bitrate for the spi object.
##
## @item 'clockpolarity'
## The clock polarity for the spi object of 'idlehigh' or 'idlelow'.
##
## @item 'clockphase'
## The clock phase for the spi object of 'firstedge' or 'secondedge'.
##
## @item 'port'
## The device port name.
##
## @item 'status'
## The device status of 'open' or 'closed'
## @end table
##
## @subsubheading Outputs
## When @var{property} was specified, return the value of that property.@*
## otherwise return the values of all properties as a structure.@*
##
## @seealso{@@octave_spi/set}
## @end deftypefn

function retval = get (spi, property)

  properties = {'name', 'bitrate', 'status', ...
                'port', 'clockpolarity', 'clockphase'};

  if (nargin == 1)
    property = properties;
  elseif (nargin > 2)
    error ("Too many arguments.\n");
  endif

  if !iscell (property)
    property = {property};
  endif
  property = tolower(property);

  valid     = ismember (property, properties);
  not_found = {property{!valid}};

  if !isempty (not_found)
    msg = @(x) error("spi:get:InvalidArgument", ...
                     "Unknown property '%s'.\n",x);
    cellfun (msg, not_found);
  endif

  property = {property{valid}};
  retval = {};
  for i=1:length(property)
    retval{end+1} = __spi_properties__ (spi, property{i});
  endfor

  if numel(property) == 1
    retval = retval{1};
  elseif (nargin == 1)
    retval = cell2struct (retval',properties);
  endif

endfunction
