## Copyright (C) 2014 Stefan Mahr <dac922@gmx.de>
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
## @deftypefn {Function File} set (@var{obj}, @var{property},@var{value})
## @deftypefnx {Function File} set (@var{obj}, @var{property},@var{value},@dots{})
## Set the properties of serial object.
##
## If @var{property} is a cell so must be @var{value}, it sets the values of
## all matching properties.
##
## The function also accepts property-value pairs.
##
## @table @var
## @item 'baudrate'
## Set the baudrate of serial port. Supported values by instrument-control:
## 0, 50, 75, 110, 134, 150, 200, 300, 600, 1200, 1800, 2400, 4800, 9600,
## 19200, 38400, 57600, 115200 and 230400. The supported baudrate of your
## serial port may be different.
##
## @item 'bytesize'
## Set the bytesize. Supported values: 5, 6, 7 and 8.
##
## @item 'parity'
## Set the parity value. Supported values: Even/Odd/None. This Parameter
## must be of type string. It is case insensitive and can be abbreviated
## to the first letter only
##
## @item 'stopbits'
## Set the number of stopbits. Supported values: 1, 2.
##
## @item 'timeout'
## Set the timeout value in tenths of a second. Value of -1 means a
## blocking call. Maximum value of 255 (i.e. 25.5 seconds).
##
## @item 'requesttosend'
## Set the requesttosend (RTS) line.
##
## @item 'dataterminalready'
## Set the dataterminalready (DTR) line.
##
## @end table
##
## @seealso{@@octave_serial/get}
## @end deftypefn

function set (serial, varargin)

  properties = {'baudrate','bytesize','parity','stopbits','timeout', ...
                'requesttosend','dataterminalready'};

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
  end

  if numel (property) != numel (value)
    error ('serial:set:InvalidArgument', ...
           'PROPERIES and VALUES must have the same number of elements.');
  end

  property = tolower(property);
  valid     = ismember (property, properties);
  not_found = {property{!valid}};

  if !isempty (not_found)
    msg = @(x) error ("serial:set:InvalidArgument", ...
                      "Property '%s' not found in serial object.\n",x);
    cellfun (msg, not_found);
  end

  property = {property{valid}};
  value = {value{valid}};

  for i=1:length(property)
    __srl_properties__ (serial, property{i}, value{i});
  end

end
