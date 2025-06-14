## Copyright (C) 2021 John Donoghue <john.donoghue@ieee.org>
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

function testudpport

  sock = udpport();
  sock.Timeout = 0.5

  flush(sock);

  # should be nothing to read
  data = read(sock, 10);

  write(sock, "hello", "127.0.0.1", sock.LocalPort);
  data = read(sock, 10);

  flush(sock);
  wdata = read(sock, 10) 
  write(sock, "hello")
  wdata = read(sock, 10) 

  # write 2 packets and read both
  flush(sock);
  write(sock, "hello")
  write(sock, "hello")
  # should read back hellohello
  wdata = read(sock, 10) 

  # increase buffer
  d = ones([1 1030]);
  flush(sock);
  x = write(sock, d)
  xdata = read(sock);
  length(xdata)
 
  clear sock

endfunction
