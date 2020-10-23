## Copyright (C) 2019-202 John Donoghue <john.donoghue@ieee.org>
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
## @subsubheading Overview
## The Instrument control package provides low level I/O functions for serial, i2c, parallel, spi, tcp, gpib, 
## vxi11, udp and usbtmc interfaces.
##
## It attempts to provide the same function calls as the Matlab toolkit, as well as additional functionality.
##
## @subsubheading Interfaces
## The following interfaces have been implemented:
## @table @asis
## @item serial (depreciated)
## serial port functionality. It has been depreciated in favor of the serialport interface.
## @item serialport
## serial port functionality. 
## @item spi
## spi device functionality. 
## @item tcp / tcpip
## tcp socket functionality
## @item udp
## udp socket functionality
## @item i2c
## i2c device functionality
## @item usbtmc
## usbtmc device functionality
## @item vxi11
## vxi11 device functionality
## @item parallel
## parallel port functionality
## @item gpip
## gpip device functionality
## @end table
##
## Use of the actual devices depend on whether teh functionality was enabled during package installation.
##
## To verify the available interfaces, run the following command in octave:
##
## @example
## instrhwinfo
## @end example
## 
## The function will return information on the supported interfaces that are available, similar to below:
## 
## @example
##     ToolboxVersion = 0.4.0
##     ToolboxName = octave instrument control package
##     SupportedInterfaces =
##     @{
##       [1,1] = gpib
##       [1,2] = i2c
##       [1,3] = parallel
##       [1,4] = serial
##       [1,5] = tcp
##       [1,6] = udp
##       [1,7] = usbtmc
##       [1,8] = vxi11
##     @}
## @end example
## 
## Information on each device type can be obtained using:
##
## @example
## instrhelp <theclassname>.
## @end example
function __instrument_control__ ()
  # do nothing
endfunction
