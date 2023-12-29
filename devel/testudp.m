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

function testudp

  sock = udp();
  sock.remoteport = sock.localport;
  sock.remotehost = '127.0.0.1';
  sock.timeout = 0.5

  flushinput(sock);
  flushoutput(sock);

  # should be nothing to read
  data = udp_read(sock, 10) 

  udp_write(sock, "hello")
  data = udp_read(sock, 10) 

  fdata = fread(sock, 10) 
  fwrite(sock, "hello")
  fdata = fread(sock, 10) 

  flush(sock);
  wdata = read(sock, 10) 
  write(sock, "hello")
  wdata = read(sock, 10) 

  # fprintf
  fprintf(sock, "%d %d", 1, 2)
  xdata = read(sock) 

  flush(sock);
  write(sock, "hello")
  write(sock, "hello")
  # should read back hellohello
  wdata = read(sock, 10) 

  # read parts
  write(sock, "hello")
  wdata = read(sock, 4) 
  wdata = read(sock, 1) 

  # test increase buff size
  d = ones([1 1030]);
  flush(sock);
  x = write(sock, d)
  xdata = read(sock) ;
  length(xdata)
  sum(xdata)

  clear sock

endfunction
