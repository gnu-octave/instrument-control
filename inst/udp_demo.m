## Copyright (C) 2016 John Donoghue
## 
## This program is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 3 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.

## -*- texinfo -*- 
## @deftypefn {Function File} {@var{result} =} udp_demo ()
## Run test SNTP demonstration for udp class
##
## @seealso{udp}
## @end deftypefn

## Author: john donoghue <john.donoghue@ieee.org>
## Created: 2016-11-23

function result = udp_demo ()

  result = false;
  server = 'pool.ntp.org';
  
  fprintf ('getting time from %s\n', server);
  
  # query time using SNTP
  s = udp (server, 123);

  # send request packet
  data = [uint8(0x1b) uint8(zeros (1,47))];
  res = udp_write (s, data);

  # recieve packet
  data = udp_read (s,48, 4000);

  # should have 48 bytes reply
  if length (data) == 48
    
    # convert uint8s to integer32
    dataL = typecast (data, 'uint32');
    
    # convert to little endian if we are on a little endian machine
    if typecast (uint8([1 0]), 'uint16') == 1
        dataL = swapbytes (dataL);
    endif

    # network time
    ntimeval = dataL(11) - 2208988800;
    # get system time 
    ltimeval = uint32 (time());
    
    fprintf ('network time=%lu local time=%lu\n', ...
      ntimeval, ltimeval);
    
    result = true;
  endif

  fclose (s);
endfunction

%!test
% assert(udp_demo)

%!test
% s = udp('127.0.0.1', 80);
% assert(!isempty(s));
% assert(get(s,'name'), 'UDP-127.0.0.1');
% assert(get(s,'remoteport'), 80);
% assert(get(s,'remotehost','127.0.0.1');
% assert(get(s,'localport'))
% set(s,'name', 'test');
% assert(get(s,'name'), 'test');
% udp_close(s);

%!test
% s = udp('127.0.0.1', 80);
% assert(get(s,'status'), 'open');
% fclose(s);
% assert(get(s,'status'), 'closed');

