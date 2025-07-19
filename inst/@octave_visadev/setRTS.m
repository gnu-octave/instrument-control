## Copyright (C) 2025 John Donoghue <john.donoghue@ieee.org>
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
## @deftypefn {} {} setRTS (@var{dev}, @var{true_false})
## Set the state of the RTS line
##
## @subsubheading Inputs
## @var{dev} - connected visadev serial device.@*
## @var{true_false} - state to set the line.@*
##
## @subsubheading Outputs
## None
##
## @seealso{visadev, getpinstatus}
## @end deftypefn

function setRTS (dev, tf)

  if nargin < 2
    print_usage();
  else
    if  !islogical (tf) && !isnumeric(tf)
      error("setRTS expected pin state to be true or false");
    endif

    __visadev_dispatch__ (dev, "setRTS", tf);

  endif
endfunction
