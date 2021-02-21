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

function testmulticast

  sender = udpport();

  receiver1 = udpport("LocalPort", 3030, "EnablePortSharing", true);
  receiver2 = udpport("LocalPort", 3030, "EnablePortSharing", true);

  configureMulticast(receiver1, "226.0.0.1");
  configureMulticast(receiver2, "226.0.0.1");

  assert(receiver1.EnableMulticast, 1)
  assert(receiver2.EnableMulticast, 1)

  # write data
  printf("writing data to multcast address %s\n", receiver1.MulticastGroup);
  write(sender, "hello", "string", "226.0.0.1", 3030);

  pause(.5)

  # now should see same data on both receivers
  sz1 = receiver1.NumBytesAvailable
  sz2 = receiver1.NumBytesAvailable

  data1 = read(receiver1, sz1, "string")
  data2 = read(receiver2, sz2, "string")

  # disable multicast
  configureMulticast(receiver1, "off");
  configureMulticast(receiver2, "off");

  assert(receiver1.EnableMulticast, 0)
  assert(receiver2.EnableMulticast, 0)

  clear sender
  clear receiver1
  clear receiver2

  assert(sz1, sz2)
  assert(data1, data2)

  printf("done!\n");
endfunction
