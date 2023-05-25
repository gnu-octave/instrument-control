## Copyright (C) 2023 John Donoghue <john.donoghue@ieee.org>
## 
## This program is free software: you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.

## -*- texinfo -*- 
## @deftypefn {} {} writeline (@var{dev}, @var{data})
## @deftypefnx {} {} writeline (@var{dev}, @var{data}, @var{destaddr}, @var{destport})
## Write data to a udpport including terminator value
##
## @subsubheading Inputs
## @var{dev} - connected device
##
## @var{data} - ASCII data to write
##
## @var{destaddr} - Destination address
##
## @var{destport} - Destination port
##
## Where the address and port is not specified, the previously used address and port is used.
##
## @subsubheading Outputs
## None
##
## @seealso{flushoutput}
## @end deftypefn

function writeline (dev, data, varargin)

  if nargin != 2 && nargin != 4
    error ('expected instrument control device and data');
  endif

  type = typeinfo(dev);
  if !strncmp(type, "octave_", 7)
    error ('expected instrument control device');
  endif

  if !ischar(data)
    error ("Expected data to be characters");
  endif

  terminator = dev.Terminator;
  if iscell(terminator) && length(terminator) > 1
    terminator = terminator{2};
  endif

  if ! ischar (terminator)
    terminator = char(terminator);
  else
    if strcmpi (terminator, "lf")
      terminator = "\n";
    elseif strcmpi (terminator, "cr")
      terminator = "\r";
    elseif strcmpi (terminator, "cr/lf")
      terminator = "\r\n";
    endif
  endif

  if nargin == 4
    write (dev, [data terminator], varargin{1}, varargin{2});
  else
    write (dev, [data terminator]);
  endif

endfunction

%!error writeline
%!error writeline (1)

%!test
%! a = udpport ();
%! writeline(a, "hello", '127.0.0.1', a.LocalPort);
%! writeline(a, "hello2");
%! clear a
