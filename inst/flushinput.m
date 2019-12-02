## Copyright (C) 2019 John Donoghue <john.donoghue@ieee.org>
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
## @deftypefn {} {} flushinput (@var{dev})
## Flush the instruments input buffers
##
## @subsubheading Inputs
## @var{dev} - connected device or array of devices
##
## @subsubheading Outputs
## None
##
## @seealso{flushoutput}
## @end deftypefn

function flushinput (dev)

  if nargin < 1
    error ('expected instrument control device');
  endif

  if iscell(dev)
    for i=1:length(dev)
      flushinput(dev{i});
    endfor
  else
    if !strncmp(typeinfo(dev), "octave_", 7)
      error ('expected instrument control device');
    endif

    # handle instruments we have a valid way of flushing input 
    if (isa (dev,'octave_serialport'))
      flush(dev, "input");
    elseif (isa (dev,'octave_serial'))
      __srl_properties__ (dev, 'flush', 1);
    elseif (isa (dev,'octave_udp'))
      __udp_properties__ (dev, 'flush', 1);
    elseif (isa (dev,'octave_tcp'))
      __tcp_properties__ (dev, 'flush', 1);
    elseif (isa (dev,'octave_gpib'))
      __gpib_clrdevice__ (obj);
    else
      # anything not handled specifically
      data = [1];
      while (~isempty(data))
        data = fread(obj,100);
      endwhile
    endif
  endif
endfunction

%!error flushinput
%!error flushinput (1)

%!test
%! a = udp ();
%! flushinput(a);
%! clear a

%!test
%! a = udp ();
%! b = udp ();
%! flushinput({a b});
%! clear a b
