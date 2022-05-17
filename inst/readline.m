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
## @deftypefn {} {@var{data} =} readline (@var{dev}, @var{data})
## read data from a instrument device excluding terminator value
##
## @subsubheading Inputs
## @var{dev} - connected device
##
## @subsubheading Outputs
## @var{data} - ASCII data read
##
## @seealso{flushoutput}
## @end deftypefn

function data = readline (dev)

  if nargin < 1
    error ('expected instrument control device');
  endif

  type = typeinfo(dev);
  if !strncmp(type, "octave_", 7)
    error ('expected instrument control device');
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
      if strcmpi(terminator, "lf")
        terminator = "\n";
      elseif strcmpi(terminator, "cr")
        terminator = "\r";
      elseif strcmpi(terminator, "cr/lf")
        terminator = "\r\n";
      endif
    endif

    data = "";
    idx = 0;

    len = dev.NumBytesAvailable;
    if(len == 0)
      len = 100;
    endif

    tdata = read (dev, len);
    while !isempty (tdata) && idx == 0
      data = [data char(tdata)];
      idx = index (data, terminator);
      if (idx > 0)
        if (idx > 1)
          data = data(1:idx-1);
        else
          data = "";
        endif
      else
        tdata = read (dev);
      endif
    endwhile
  else
    terminator = "\n";

    data = "";
    idx = 0;
    tdata = fread(dev, 100);
    while !isempty(tdata) && idx == 0
      data = [data  char(tdata)];
      idx = index(data, terminator);
      if (idx > 0)
        if (idx > 1)
          data = data(1:idx-1);
        else
          data = "";
        endif
      else
        tdata = fread(dev, 100);
      endif
    endwhile
 
  endif

endfunction

%!error readline
%!error readline (1)

%!test
%! a = udp ();
%! a.remoteport = a.localport;
%! a.remotehost = '127.0.0.1';
%! a.timeout = 1;
%!
%! writeline(a, "hello");
%! assert(readline(a), "hello");
%! clear a
