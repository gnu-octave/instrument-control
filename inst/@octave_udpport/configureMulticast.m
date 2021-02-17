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

## -*- texinfo -*- 
## @deftypefn {} {@var{data} =} configureMulticast((@var{dev}, @var{address})
## @deftypefnx {} {@var{data} =} configureMulticast((@var{dev}, @var{"off"})
## Configure udpport device to receive multicast data
##
## @subsubheading Inputs
## @var{dev} - open udpport device
##
## If @var{address}  is 'off' disable udp multicast. Otherwise it is the multicast address to use.
##
## @subsubheading Outputs
## None
##
## @seealso{udpport}
## @end deftypefn

function configureMulticast(dev, address, loopback)

  if nargin < 2
    error("configureMulticast: expected udp object and address");
  endif

  if nargin < 3
    loopback = 1;
  endif

  if  !ischar (address)
    error("configureMulticast: expected address to be a string");
  endif

  if !islogical(loopback) && !isscalar(loopback)
    error("configureMulticast: expected loopback to be a boolean");
  endif

  __udpport_properties__ (dev, 'multicastgroup', address);
  __udpport_properties__ (dev, 'enablemulticastloopback', loopback);
endfunction
