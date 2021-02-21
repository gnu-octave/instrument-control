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

function testi2c
  # test app that reads from a Si7021 temp sensor on the i2c bus

  instrhwinfo("i2c")

  i2c_device = "/dev/i2c-1";
  i2c_address = 0x40;

  i2cdev = i2c(i2c_device, i2c_address)

  SENSOR_ID_1 = uint8([ hex2dec("FA") hex2dec("F0") ]);
  SENSOR_ID_2 = uint8([ hex2dec("FC") hex2dec("C9") ]);

  fwrite (i2cdev, SENSOR_ID_1);
  id1 = fread(i2cdev, 1)
  i2c_write (i2cdev, SENSOR_ID_1);
  id1 = i2c_read(i2cdev, 1)
  fwrite (i2cdev, SENSOR_ID_2);
  id2 = fread(i2cdev, 1)

  printf ("Sensor ID: %02X%02X\n", id1, id2)
  printf ("Sensor Type: ");
  if id2 == hex2dec("15")
    printf ("Si7021\n");
  elseif id2 == hex2dec("14")
    printf ("Si7020\n");
  elseif id2 == hex2dec("0D")
    printf ("Si7013\n");
  elseif id2 == hex2dec("32")
    printf ("HTU21D\n");
  else
    error ("unknown sensor type of %d found", id2);
  endif

  SENSOR_VERSION = uint8([ hex2dec("84") hex2dec("B8") ]);
  fwrite (i2cdev, SENSOR_VERSION);
  ver = fread(i2cdev, 1);
  printf ("F/W Version: ");
  if ver == hex2dec("FF")
    printf ("Version: 1.0\n");
  elseif ver == hex2dec("20")
    printf ("Version: 2.0\n");
  else
    printf ("Version: %f\n", double(ver)/10.0);
  endif

  TEMP_MEASURE_NOHOLD = hex2dec("F3");
  HUMIDITY_MEASURE_NOHOLD = hex2dec("F5");

  fwrite (i2cdev, uint8([TEMP_MEASURE_NOHOLD]));
  pause (0.02);
  data = fread (i2cdev, 3);

  value = uint16(data(1))*256 + uint16(data(2));
  value = bitand (value, hex2dec("FFFC"));
  temp_Code = double(value);

  C = (175.72*temp_Code/65536)-46.85;
  printf ("temperature read %f C\n", C);

  % write command to get rel humidity
  fwrite (i2cdev, uint8([HUMIDITY_MEASURE_NOHOLD]));
  pause (0.02);
  data = fread (i2cdev, 3);
  value = uint16(data(1))*256 + uint16(data(2));
  value = bitand (value, hex2dec("FFFC"));
  humidity_Code = double(value);

  humidity = (125.0*humidity_Code/65536)-6;

  printf ("relative humidity read %f %%\n", humidity);

  clear i2cdev

endfunction
