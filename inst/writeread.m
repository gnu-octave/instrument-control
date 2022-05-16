## Copyright (C) 2022 John Donoghue <john.donoghue@ieee.org>
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
## @deftypefn {} {@var{data} =} writeread (@var{dev}, @var{command})
## write a ASCII command and read data from a instrument device.
##
## @subsubheading Inputs
## @var{dev} - connected device
##
## @var{command} - ASCII command
##
## @subsubheading Outputs
## @var{data} - ASCII data read
##
## @seealso{readline, writeline}
## @end deftypefn

function data = writeread (dev, cmd)
  writeline(dev, cmd);
  data = readline(dev);
endfunction

%!error writeread
%!error writeread (1)

%!test
%! a = udp ();
%! a.remoteport = a.localport;
%! a.remotehost = '127.0.0.1';
%! a.timeout = 1
%!
%! data = writeread(a, "hello");
%! assert(data, "hello");
%! clear a
