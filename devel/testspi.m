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

function testspi
  # test app that reads from a BME280 humidity and pressure sensor on the spi bus

  instrhwinfo("spi")

  spi_device = "/dev/spidev0.0";

  spidev = spi(spi_device, 'clockpolarity', 'idlehigh', 'clockphase', 'firstedge')

  SENSOR_ID = uint8([ hex2dec("D0"), 0 ]);

  id = writeAndRead (spidev, SENSOR_ID)(2);

  printf ("Sensor ID: %02X\n", id)
  printf ("Sensor Type: ");
  if id == hex2dec("60")
    printf ("BME 280\n");
  elseif id == hex2dec("56")
    printf ("BMP 280 (Samples)\n");
  elseif id == hex2dec("57")
    printf ("BMP 280 (Samples)\n");
  elseif id == hex2dec("58")
    printf ("BMP 280 (production)\n");
  else
    error ("unknown sensor type of %d found", id);
  endif

  # read cal regs
  SENSOR_VOLTAGE_CAL = uint8([ hex2dec("88"), 0, 0, 0, 0, 0, 0]); # 88 ..
  caldata = writeAndRead (spidev, SENSOR_VOLTAGE_CAL);

  T1 = uint16(caldata(3))*256 + uint16(caldata(2));
  T2 = typecast(uint16(caldata(5))*256 + uint16(caldata(4)), 'int16');
  T3 = typecast(uint16(caldata(7))*256 + uint16(caldata(6)), 'int16');

  # start
  SENSOR_SET_MODE = uint8([ hex2dec("74") ]); # F4&0x7f

  #mode = hex2dec("B7"); # 16x over sample
  mode = hex2dec("27"); # normal mode, sample rate = 1
  write (spidev, uint8([SENSOR_SET_MODE mode]));

  # sensor status - wait until ok
  SENSOR_STATUS = uint8([ hex2dec("F3"), 0 ]); # F3
  m = 1;
  while m == 1
    pause(.5);
    status = writeAndRead (spidev, SENSOR_STATUS)(2);
    m = bitand(bitshift(status, -3), 1);
    u = bitand(status, 1);
    printf("status = %02X meas=%d update=%d\n", status, m, u);
  endwhile

  SENSOR_READTEMP = uint8([ hex2dec("FA"), 0, 0, 0 ]); # FA
  data = writeAndRead (spidev, SENSOR_READTEMP)
  value = bitshift(uint32(data(2)), 12) + bitshift(uint32(data(3)), 4) + bitand(bitshift(uint32(data(4)), -4), 0x0f);
  var1 = (bitshift(int32(value), -3) - bitshift(int32(T1), 1)) * bitshift(int32(T2), -11);
  var2 = (int32(bitshift(value, -4)) - int32(T1)) * (int32(bitshift(value, -4)) - int32(T1));
  var2 = bitshift( (bitshift(var2, -12) * int32(T3)), -14); 

  value = bitshift(((var1 + var2) * 5 + 128), -8);
  tempC = double(value) / 100;
  tempF = (tempC * 1.8) +32.0;
  printf("temp C = %f  F = %f\n", tempC, tempF);

  clear spidev

endfunction
