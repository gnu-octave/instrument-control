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
## read a binblock of data from an instrument device
##
## readbinblock will discard any data before a recognised binblock.
## If no binblock is found or read, an empty @var{data} will be returned.
##
## @subsubheading Inputs
## @var{dev} - connected device
##
## @var{datatype} - optional data type to read data as (default 'uint8')
## Valid values are:
## @table @asis
## @item "string"
## maps to a char array
## @item "char", "schar", "int8"
## maps to int8
## @item "uchar", "uint8"
## maps to uint8
## @item "int16", "short"
## maps to int16
## @item "uint16", "ushort"
## maps to uint16
## @item "int32", "int"
## maps to int32
## @item "uint32", "uint"
## maps to uint32
## @item "int64", "long"
## maps to int64
## @item "uint64", "ulong"
## maps to uint64
## @item "single", "float", "float32"
## maps to single
## @item "double", "float64"
## maps to double
## @end table
##
## @subsubheading Outputs
## @var{data} - data read
##
## @seealso{writebinblock}
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

  # Dataformat: # D <dsizenumn> <data...> \n
  # hdr: '#'
  #      D= ascii number of chars the datasize value uses
  #      datasizenum (acsii number for datasize) length=D
  # data: of datasize
  # terminator \n
  
  # scan for start of header
  tmp = 1;
  while !isempty(tmp) && tmp != '#'
    if has_read
      tmp = read (dev, 1);
    else
      tmp = fread (dev, 1);
    endif
  endwhile

  if isempty(tmp)
    data = [];
    return;
  endif

  # get data size size byte
  if has_read
    tmp = read (dev, 1);
  else
    tmp = fread (dev, 1);
  endif

  if isempty(tmp)
    data = [];
    return
  endif

  # read data sz
  len = str2num(char(tmp));
  pos = 0;
  dsize = [];
  while (pos < len)
    
    if has_read
      tmp = read (dev, len-pos);
    else
      tmp = fread (dev, len-pos);
    endif

    if isempty(tmp)
      data = [];
      return;
    endif
  
    dsize = [dsize tmp];
    pos = numel(dsize);
  endwhile

  len = str2num(char(dsize));
 
  if has_read
    tdata = read (dev, len);
  else
    tdata = fread(dev, len);
  endif

  while !isempty (tdata)
    data = [data tdata];
    pos = numel(data);

    if pos >= len
      break;
    endif

    if has_read
      tdata = read (dev, len-pos);
    else
      tdata = fread(dev, len-pos);
    endif

  endwhile

  # end byte
  if has_read
    eol = read (dev, 1);
  else
    eol = fread(dev, 1);
  endif

  assert(eol, uint8(10))

  if !strcmp(toclass, 'uint8')
     data = typecast(data,toclass);
  endif
endfunction

%!error readbinblock
%!error readbinblock (1)

%!test
%! # old class
%! a = udp ();
%! a.remoteport = a.localport;
%! a.remotehost = '127.0.0.1';
%! a.timeout = 1;
%!
%! writebinblock(a, "hello", "char");
%! assert(readbinblock(a), uint8("hello"));
%!
%! x = [1 2 3 4];
%! writebinblock(a, x, "double");
%! assert(readbinblock(a, "double"), x);
%!
%! # bigger blocks (prev was failing > 96)
%! x = uint8(255*rand(1,4096));
%! writebinblock(a, x, "uint8");
%! y = readbinblock(a, "uint8");
%! assert (y, x);
%!
%! # insert some noise before the data
%! write(a, "invalidstuff");
%!
%! writebinblock(a, "hello", "char");
%! assert(readbinblock(a), uint8("hello"));
%!
%! clear a

%!test
%! # new style class
%! a = udpport ();
%! #a.remoteport = a.localport;
%! #a.remotehost = '127.0.0.1';
%! a.Timeout = 1;
%! # set dest to us
%! write(a, "test", "127.0.0.1", a.LocalPort);
%! flush(a);
%!
%! writebinblock(a, "hello", "char");
%! assert(readbinblock(a), uint8("hello"));
%!
%! x = [1 2 3 4];
%! writebinblock(a, x, "double");
%! assert(readbinblock(a, "double"), x);
%!
%! # bigger blocks (prev was failing > 96)
%! x = uint8(255*rand(1,4096));
%! writebinblock(a, x, "uint8");
%! y = readbinblock(a, "uint8");
%! assert (y, x);
%!
%! # insert some noise before the data
%! write(a, "invalidstuff");
%!
%! writebinblock(a, "hello", "char");
%! assert(readbinblock(a), uint8("hello"));
%!
%! clear a

