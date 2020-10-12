## Copyright (C) 2018-2020 John Donoghue <john.donoghue@ieee.org>
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
## @deftypefn {Function File} {@var{tcp} = } tcpclient (@var{host}, @var{port})
## @deftypefnx {Function File} {@var{tcp} = } tcpclient (@var{host}, @var{port}, [@var{PropertyName}, @var{PropertyValue}...])
## Matlab compatible wrapper to the tcp interface.
##
## @subsubheading Inputs
## @var{host} - the host name or ip.@*
## @var{port} - the port number to connect.@*
## @var{PropertyName}, @var{PropertyValue} - Optional property name, value pairs to set on the tcp object.@*
##
## @subsubheading Properties
## Currently the only known properties are "timeout" and "name".
##
## @subsubheading Outputs
## tcpclient will return an instance of @var{octave_tcp} class as the result.
## @end deftypefn

function out = tcpclient (varargin)

  if nargin < 2
    print_usage ();
  endif

  host = varargin{1};

  if !isnumeric(varargin{2})
    error ("tcpclient: expected port number");
  else
    port = varargin{2};
  endif

  if nargin > 2
    if mod(nargin, 2) != 0
      error ("tcpclient: expected property name, value pairs");
    endif
    if !iscellstr (varargin(3:2:nargin))
      error ("tcpclient: expected property names to be strings");
    endif
  endif

  out = tcp (resolvehost(host, "address"), port);

  for i = 3:2:nargin
    propname = tolower(varargin{i});
    propvalue = varargin{i+1};

    __tcp_properties__ (out, propname, propvalue);
  endfor

endfunction

%!test
%! a = tcpclient ("octave.org", 80);
%! assert(isa(a, "octave_tcp"));
%! fclose(a);
