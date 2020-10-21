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

function testserial
  # test app looks for arduino devices on serial port that have been setup
  # from the octave-arduino package
 
  printf("scanning for possible arduinos\n"); 
  ports = seriallist()

  for i = 1:numel (ports)
    try
      s = {};
      unwind_protect
        portname = ports{i};
	if isunix()
	  portname = [ "/dev/" portname ];
	endif
        printf("* trying comport %s\n", portname);
        s = serial (portname, 9600, 1);
        pause(2);

	flushinput(s);
	flushoutput(s);

        hdr = uint8 ([ hex2dec("A5") 0 1 0]);
        len = fwrite(s, hdr)
        tmpdataOut = fread (s, 4)
        tmpdataSize = length(tmpdataOut)
      
        if tmpdataSize == 4 && tmpdataOut(1) == hex2dec("A5") && tmpdataOut(3) == 1 
        
           expectlen =  tmpdataOut(4);

           dataout = fread (s, expectlen)
           datalen = length(dataout)

           if datalen == expectlen && datalen >= 4
             board = dataout(4);
             printf(" ** found board %d\n", board);
           endif
        endif
      unwind_protect_cleanup
        if !isempty (s)
          clear s
        endif
      end_unwind_protect
    catch err
      # do nothing
      # printf(" ** caught err: %s\n", err.message)
    end_try_catch
  endfor

endfunction

