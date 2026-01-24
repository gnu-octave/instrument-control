## Copyright (C) 2022 John Donoghue <john.donoghue#ieee.org>
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
## Set the properties of tcpserver object.
##
## @subsubheading Inputs
## If @var{property} is a cell so must be @var{value}, it sets the values of
## all matching properties.
##
## The function also accepts property-value pairs.
##
## @subsubheading Properties
## @table @var
## @item 'Name'
## Set the name for the tcpserver socket.
##
## @item 'UserData'
## Set user data for the tcpserver socket.
##
## @item 'Timeout'
## Set the timeout value in seconds. Value of -1 means a
## blocking call.
##
## @end table
##
## @subsubheading Outputs
## None
##
## @seealso{@@octave_tcpserver/get}
## @end deftypefn

function set (tcpserver, varargin)

  properties = {'Timeout', 'Name', 'UserData', ...
                'ByteOrder'};

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
    error ('tcpserver:set:InvalidArgument', ...
           'PROPERIES and VALUES must have the same number of elements.');
  endif

  valid     = ismember (property, properties);
  not_found = {property{!valid}};

  if !isempty (not_found)
    msg = @(x) error ("tcpserver:set:InvalidArgument", ...
                      "Property '%s' not found in tcpserver object.\n",x);
    cellfun (msg, not_found);
  endif

  property = {property{valid}};
  value = {value{valid}};

  for i=1:length(property)
    __tcpserver_properties__ (tcpserver, property{i}, value{i});
  endfor

endfunction
