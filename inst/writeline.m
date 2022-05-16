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
## @deftypefn {} {} writeline (@var{dev}, @var{data})
## Write data to a instrument device inclding terminator value
##
## @subsubheading Inputs
## @var{dev} - connected device
##
## @var{data} - ASCII data to write
##
## @subsubheading Outputs
## None
##
## @seealso{flushoutput}
## @end deftypefn

function writeline (dev, data)

  if nargin < 2
    error ('expected instrument control device and data');
  endif

  type = typeinfo(dev);
  if !strncmp(type, "octave_", 7)
    error ('expected instrument control device');
  endif

  if !ischar(data)
    error ("Expected data to be characters");
  endif

  types_with_confterminator = { "octave_udpport", "octave_serialport", ...
                                "octave_tcpclient", "octave_tcpserver", "octave_udpport" };

  if sum(strcmp(type, types_with_confterminator)) > 0
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

    write (dev, [data terminator]);
  else
    terminator = "\n";

    fwrite (dev, [data terminator]);
  endif

endfunction

%!error writeline
%!error writeline (1)

%!test
%! a = udp ();
%! a.remoteport = a.localport;
%! a.remotehost = '127.0.0.1';
%! a.timeout = 1;
%!
%! writeline(a, "hello");
%! clear a
