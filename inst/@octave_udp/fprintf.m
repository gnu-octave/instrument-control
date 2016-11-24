## Copyright (C) 2016 John Donoghue <john.donoghue@ieee.org>
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
## @deftypefn {Function File} {@var{numbytes} =} fprintf (@var{obj}, @var{template} ...)
## Writes formatted string @var{template} using optional paramters to 
## UDP instrument
##
## @var{obj} is a UDP object
## @var{template} Format template string 
##
## @end deftypefn

function numbytes = fprintf (varargin)

defaultformat = '%s\n';

if (nargin < 2)
  print_usage ();
elseif (nargin < 3)
  formargs = varargin(2);
  format = defaultformat;
else(nargin < 4)
  formargs = varargin(3:nargin);
  format = varargin{2};
end

if (! ( ischar (format)))
  print_usage ();
end

numbytes = udp_write (varargin{1}, sprintf (format, formargs{:}))

end
