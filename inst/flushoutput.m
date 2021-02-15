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
## @deftypefn {} {} flushoutput (@var{dev})
## Flush the instruments output buffers
##
## @subsubheading Inputs
## @var{dev} - connected device or array of devices
##
## @subsubheading Outputs
## None
##
## @seealso{flushinput}
## @end deftypefn

function flushoutput (dev)

  if nargin < 1
    error ('expected instrument control device');
  endif

  if iscell(dev)
    for i=1:length(dev)
      flushoutput(dev{i});
    endfor
  else
    if !strncmp(typeinfo(dev), "octave_", 7)
      error ('expected instrument control device');
    endif

    # handle instruments we have a valid way of flushing input 
    if (isa (dev,'octave_serialport'))
      flush(dev, "output");
    elseif (isa (dev,'octave_serial'))
      __srl_properties__ (dev, 'flush', 0);
    elseif (isa (dev,'octave_udp'))
      __udp_properties__ (dev, 'flush', 0);
    elseif (isa (dev,'octave_udpport'))
      __udpport_properties__ (dev, 'flush', 0);
    elseif (isa (dev,'octave_tcp'))
      __tcp_properties__ (dev, 'flush', 0);
    elseif (isa (dev,'octave_tcpclient'))
      __tcpclient_properties__ (dev, 'flush', 0);
    elseif (isa (dev,'octave_gpib'))
      __gpib_clrdevice__ (obj);
    endif
  endif
endfunction

%!error flushoutput
%!error flushoutput (1)

%!test
%! a = udp ();
%! flushoutput(a);
%! clear a

%!test
%! a = udp ();
%! b = udp ();
%! flushoutput({a b});
%! clear a b
