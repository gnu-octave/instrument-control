---
layout: "default"
permalink: "/functions/12_gpibtimeout/"
pkg_name: "instrument-control"
pkg_version: "0.10.0"
pkg_description: "Low level I/O functions for serial, i2c, spi, parallel, tcp, gpib, modbus, visa, vxi11, udp and usbtmc interfaces."
title: "Instrument-control Toolkit - gpib_timeout"
category: "VXI11"
func_name: "gpib_timeout"
navigation:
- id: "overview"
  name: "Overview"
  url: "/index"
- id: "Functions"
  name: "Function Reference"
  url: "/functions"
- id: "16_CommonFunctions"
  name: "&nbsp;&nbsp;Common Functions"
  url: "/functions/#16_CommonFunctions"
  subitems:
- id: "7_General"
  name: "&nbsp;&nbsp;General"
  url: "/functions/#7_General"
  subitems:
- id: "4_GPIB"
  name: "&nbsp;&nbsp;GPIB"
  url: "/functions/#4_GPIB"
  subitems:
- id: "3_I2C"
  name: "&nbsp;&nbsp;I2C"
  url: "/functions/#3_I2C"
  subitems:
- id: "6_Modbus"
  name: "&nbsp;&nbsp;Modbus"
  url: "/functions/#6_Modbus"
  subitems:
- id: "8_Parallel"
  name: "&nbsp;&nbsp;Parallel"
  url: "/functions/#8_Parallel"
  subitems:
- id: "19_Serial(Deprecated)"
  name: "&nbsp;&nbsp;Serial (Deprecated)"
  url: "/functions/#19_Serial(Deprecated)"
  subitems:
- id: "11_SerialPort"
  name: "&nbsp;&nbsp;Serial Port"
  url: "/functions/#11_SerialPort"
  subitems:
- id: "3_SPI"
  name: "&nbsp;&nbsp;SPI"
  url: "/functions/#3_SPI"
  subitems:
- id: "16_TCP(Deprecated)"
  name: "&nbsp;&nbsp;TCP (Deprecated)"
  url: "/functions/#16_TCP(Deprecated)"
  subitems:
- id: "10_TCPClient"
  name: "&nbsp;&nbsp;TCP Client"
  url: "/functions/#10_TCPClient"
  subitems:
- id: "10_TCPServer"
  name: "&nbsp;&nbsp;TCP Server"
  url: "/functions/#10_TCPServer"
  subitems:
- id: "16_UDP(Deprecated)"
  name: "&nbsp;&nbsp;UDP (Deprecated)"
  url: "/functions/#16_UDP(Deprecated)"
  subitems:
- id: "8_UDPPort"
  name: "&nbsp;&nbsp;UDP Port"
  url: "/functions/#8_UDPPort"
  subitems:
- id: "6_USBTMC"
  name: "&nbsp;&nbsp;USBTMC"
  url: "/functions/#6_USBTMC"
  subitems:
- id: "4_Visa"
  name: "&nbsp;&nbsp;Visa"
  url: "/functions/#4_Visa"
  subitems:
- id: "5_VXI11"
  name: "&nbsp;&nbsp;VXI11"
  url: "/functions/#5_VXI11"
  subitems:
- id: "news"
  name: "News"
  url: "/news"
- id: "manual"
  name: "Manual"
  url: "/manual"
---
<dl class="first-deftypefn def-block">
<dt class="deftypefn def-line" id="index-gpib_005ftimeout"><span class="category-def">Loadable Function: </span><span><strong class="def-name">gpib_timeout</strong> <code class="def-code-arguments">(<var class="var">gpib</var>, <var class="var">timeout</var>)</code><a class="copiable-link" href="#index-gpib_005ftimeout"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn def-line" id="index-gpib_005ftimeout-1"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">t</var> =</code> <strong class="def-name">gpib_timeout</strong> <code class="def-code-arguments">(<var class="var">gpib</var>)</code><a class="copiable-link" href="#index-gpib_005ftimeout-1"></a></span></dt>
<dd> 
<p>Set new or get existing gpib interface timeout parameter. The timeout value is valid from 0 to 17.
</p> 
<p><var class="var">gpib</var> - instance of <var class="var">octave_gpib</var> class.<br> <var class="var">timeout</var> - Value of 0 means never timeout, 11 means one second and 17 means 1000 seconds (see GPIB documentation (ibtmo) for further details)
</p> 
<p>If <var class="var">timeout</var> parameter is omitted, the gpib_timeout() shall return current timeout value as the result <var class="var">t</var>.
 </p></dd></dl>