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
## @deftypefn {} {@var{data} =} readbinblock (@var{dev})
## @deftypefnx {} {@var{data} =} readbinblock (@var{dev}, @var{datatype})
## read a binblock of data from a instrument device
##
## @subsubheading Inputs
## @var{dev} - connected device
##
## @var{datatype} - optional data type to read data as (default 'uint8')
##
## @subsubheading Outputs
## @var{data} - data read
##
## @seealso{flushoutput}
## @end deftypefn

function data = readbinblock (dev, varargin)

  if nargin < 1
    error ('expected instrument control device');
  endif

  type = typeinfo(dev);
  if !strncmp(type, "octave_", 7)
    error ('expected instrument control device');
  endif

  if nargin > 1
    switch (varargin{1})
    case {"string"}
      toclass = "char";
    case {"char" "schar" "int8"}
      toclass = "int8";
    case {"uchar" "uint8"}
      toclass = "uint8";
    case {"int16" "short"}
      toclass = "int16";
    case {"uint16" "ushort"}
      toclass = "uint16";
    case {"int32" "int"}
      toclass = "int32";
    case {"uint32" "uint"}
      toclass = "uint32";
    case {"long" "int64"}
      toclass = "int64";
    case {"ulong" "uint64"}
      toclass = "uint64";
    case {"single" "float" "float32"}
      toclass = "single";
    case {"double" "float64"}
      toclass = "double";
    otherwise
      error ("datatype not supported");
    endswitch
  else
    toclass = "uint8";
  endif

  # read and numbytesavailable
  types_with_read = { "octave_udpport", "octave_serialport", ...
                      "octave_tcpclient", "octave_tcpserver", "octave_udpport" };

  if sum(strcmp(type, types_with_read)) > 0
    has_read = 1;
  else
    has_read = 0;
  endif

  data = uint8([]);
  sz = -1;

  # need read ?????? # D <dsizenumn> <data...> \n
   
  if has_read
    len = dev.NumBytesAvailable;
    if(len == 0)
      len = 100;
    endif

    tdata = read (dev, len);
  else
    tdata = fread(dev, 100);
  endif

  while !isempty (tdata)
    # getting hdr part
    if sz < 0
      data = [data tdata];
      idx = index (char(data), "#");
      if (idx > 1)
        data = data(1:idx-1);
      elseif (idx == 0)
        data = "";
      # if == 0, keep all data
      endif

      if numel(data) > 2
        len = str2num(char(data(2)));
        if (numel(data) > 2+len)
          sz = str2num(char(data(3:3+len-1)));
          data = uint8(data(3+len:end));
        endif
      endif
    endif
    # reading body
    if sz >= 0
      if numel(data) >= sz
        data = data(1:sz);
        break;
      endif
    endif

    if has_read
      tdata = read (dev);
    else
      tdata = fread(dev, 100);
    endif

  endwhile

  if !strcmp(toclass, 'uint8')
     data = typecast(data,toclass);
  endif
endfunction

%!error readbinblock
%!error readbinblock (1)

%!test
%! a = udp ();
%! a.remoteport = a.localport;
%! a.remotehost = '127.0.0.1';
%! a.timeout = 1;
%!
%! writebinblock(a, "hello", "char");
%! x = read(a);
%! assert(char(x), "#15hello\n");
%!
%! writebinblock(a, "hello", "char");
%! assert(readbinblock(a), uint8("hello"));
%!
%! x = [1 2 3 4];
%! writebinblock(a, x, "double");
%! assert(readbinblock(a, "double"), x);
%! clear a
