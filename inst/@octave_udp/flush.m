## Copyright (C) 2020 John Donoghue <john.donoghue@ieee.org>
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
## @deftypefn {} {@var{data} =} flush (@var{dev})
## @deftypefnx {} {@var{data} =} flush (@var{dev}, "input")
## @deftypefnx {} {@var{data} =} flush (@var{dev}, "output")
## Flush the udp socket buffers
##
## @subsubheading Inputs
## @var{dev} - open udp device
##
## If an additional parameter is provided of "input" or "output",
## then only the input or output buffer will be flushed
##
## @subsubheading Outputs
## None
##
## @seealso{udp}
## @end deftypefn

function flush (dev, flushdir)

  if nargin < 2
    __udp_properties__ (dev, 'flush', 0);
    __udp_properties__ (dev, 'flush', 1);
  else
    if  !ischar (flushdir)
      error("flush: expected flushdir to be a string");
    endif

    if strcmp(flushdir, "output")
      __udp_properties__ (dev, 'flush', 0);
    elseif strcmp(flushdir, "input")
      __udp_properties__ (dev, 'flush', 1);
    else
      error("flush: invalid flushdir '%s'", flushdir);
    endif
  endif
endfunction
