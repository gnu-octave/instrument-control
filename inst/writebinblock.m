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
## @deftypefn {} {} writebinblock (@var{dev}, @var{data}, @var{datatype})
## Write a IEEE 488.2 binblock of data to a instrument device
##
## binblock formatted data is defined as:
##
## #<A><B><C> 
##
## where:
##     <A> ASCII number containing the length of part <B>
##
##     <B> ASCII number containing the number of bytes of <C>
##
##     <C> Binary data block
##
## @subsubheading Inputs
## @var{dev} - connected device
##
## @var{data} - binary data to send
##
## @var{datatype} - datatype to send data as
##
## @subsubheading Outputs
## None
##
## @seealso{readbinblock}
## @end deftypefn

function writebinblock (dev, data, datatype)

  if nargin < 3
    error ('expected instrument control device, data and datatype');
  endif

  type = typeinfo(dev);
  if !strncmp(type, "octave_", 7)
    error ('expected instrument control device');
  endif

  switch (datatype)
    case {"string"}
      data = char (data);
    case {"char" "schar" "int8"}
      data = int8 (data);
    case {"uchar" "uint8"}
      data = uint8 (data);
    case {"int16" "short"}
      data = int16 (data);
    case {"uint16" "ushort"}
      data = uint16 (data);
    case {"int32" "int"}
      data = int32 (data);
    case {"uint32" "uint"}
      data = uint32 (data);
    case {"long" "int64"}
      data = int64 (data);
    case {"ulong" "uint64"}
      data = uint64 (data);
    case {"single" "float" "float32"}
      data = single (data);
    case {"double" "float64"}
      data = double (data);
    otherwise
      error ("datatype not supported");
  endswitch

  # make byte stream
  data = typecast(data,'uint8');

  # hdr part
  hdr = sprintf("#X%d", numel(data));
  # fix the hdr for X = num digits for the %d size
  hdr(2) = num2str(numel(hdr)-2);

  types_with_write = { "octave_udpport", "octave_serialport", ...
                       "octave_tcpclient", "octave_tcpserver", "octave_udpport" };

  if sum(strcmp(type, types_with_write)) > 0
    write (dev, [uint8(hdr) data uint8("\n")]);
  else
    fwrite (dev, [uint8(hdr) data uint8("\n")]);
  endif

endfunction

%!error writebinblock
%!error writebinblock (1)

%!test
%! # old classes
%! a = udp ();
%! a.remoteport = a.localport;
%! a.remotehost = '127.0.0.1';
%! a.timeout = 1;
%!
%! writebinblock(a, "hello", "char");
%! x = read(a);
%! assert(char(x), "#15hello\n");
%!
%! writebinblock(a, "hello", "uint16");
%! x = read(a);
%! assert(char(x), "#210h\0e\0l\0l\0o\0\n");
%! clear a

%!test
%! # new style class
%! a = udpport ();
%! #a.remoteport = a.localport;
%! #a.remotehost = '127.0.0.1';
%! a.Timeout = 1;
%! # set dest to us
%! write(a, "a", "127.0.0.1", a.LocalPort);
%! flush(a);
%! writebinblock(a, "hello", "char");
%! x = read(a);
%! assert(char(x), "#15hello\n");
%! clear a
