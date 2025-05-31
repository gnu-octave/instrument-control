---
layout: "default"
permalink: "/functions/@octave_modbus/24_octavemodbuswriteRead/"
pkg_name: "instrument-control"
pkg_version: "0.9.5"
pkg_description: "Low level I/O functions for serial, i2c, spi, parallel, tcp, gpib, modbus, vxi11, udp and usbtmc interfaces."
title: "Instrument-control Toolkit - @octave_modbus/writeRead"
category: "Modbus"
func_name: "@octave_modbus/writeRead"
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
- id: "7_General"
  name: "&nbsp;&nbsp;General"
  url: "/functions/#7_General"
- id: "4_GPIB"
  name: "&nbsp;&nbsp;GPIB"
  url: "/functions/#4_GPIB"
- id: "3_I2C"
  name: "&nbsp;&nbsp;I2C"
  url: "/functions/#3_I2C"
- id: "6_Modbus"
  name: "&nbsp;&nbsp;Modbus"
  url: "/functions/#6_Modbus"
- id: "8_Parallel"
  name: "&nbsp;&nbsp;Parallel"
  url: "/functions/#8_Parallel"
- id: "19_Serial(Deprecated)"
  name: "&nbsp;&nbsp;Serial (Deprecated)"
  url: "/functions/#19_Serial(Deprecated)"
- id: "11_SerialPort"
  name: "&nbsp;&nbsp;Serial Port"
  url: "/functions/#11_SerialPort"
- id: "3_SPI"
  name: "&nbsp;&nbsp;SPI"
  url: "/functions/#3_SPI"
- id: "16_TCP(Deprecated)"
  name: "&nbsp;&nbsp;TCP (Deprecated)"
  url: "/functions/#16_TCP(Deprecated)"
- id: "10_TCPClient"
  name: "&nbsp;&nbsp;TCP Client"
  url: "/functions/#10_TCPClient"
- id: "10_TCPServer"
  name: "&nbsp;&nbsp;TCP Server"
  url: "/functions/#10_TCPServer"
- id: "16_UDP(Deprecated)"
  name: "&nbsp;&nbsp;UDP (Deprecated)"
  url: "/functions/#16_UDP(Deprecated)"
- id: "8_UDPPort"
  name: "&nbsp;&nbsp;UDP Port"
  url: "/functions/#8_UDPPort"
- id: "6_USBTMC"
  name: "&nbsp;&nbsp;USBTMC"
  url: "/functions/#6_USBTMC"
- id: "5_VXI11"
  name: "&nbsp;&nbsp;VXI11"
  url: "/functions/#5_VXI11"
- id: "news"
  name: "News"
  url: "/news"
- id: "manual"
  name: "Manual"
  url: "/manual"
---
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-writeRead"><span class="category-def">: </span><span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">writeRead</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">writeAddress</var>, <var class="var">values</var>, <var class="var">readAddress</var>, <var class="var">readcount</var>)</code><a class="copiable-link" href="#index-writeRead"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-writeRead-1"><span class="category-def">: </span><span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">writeRead</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">writeAddress</var>, <var class="var">values</var>, <var class="var">readAddress</var>, <var class="var">readcount</var>, <var class="var">serverId</var>)</code><a class="copiable-link" href="#index-writeRead-1"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-writeRead-2"><span class="category-def">: </span><span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">writeRead</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">writeAddress</var>, <var class="var">values</var>, <var class="var">writePrecision</var>, <var class="var">readAddress</var>, <var class="var">readCount</var>, <var class="var">readPrecision</var>)</code><a class="copiable-link" href="#index-writeRead-2"></a></span></dt>
<dd><p>Write data <var class="var">values</var> to the modbus device <var class="var">dev</var> holding registers starting at address <var class="var">writeAddress</var>
 and then read <var class="var">readCount</var> register values starting at address <var class="var">readAddress</var>.
</p>
<h4 class="subsubheading" id="Inputs"><span>Inputs<a class="copiable-link" href="#Inputs"></a></span></h4>
<p><var class="var">dev</var> - connected modbus device
</p>
<p><var class="var">writeAddress</var> - address to start writing to.
</p>
<p><var class="var">values</var> - data to write to the device.
</p>
<p><var class="var">readAddress</var> - address to start reading from.
</p>
<p><var class="var">readCount</var> - number of elements to read.
</p>
<p><var class="var">serverId</var> - address to send to (0-247). Default of 1 is used if not specified.
</p>
<p><var class="var">precision</var> - Optional precision for how to interpret the read data.
 Currently known precision values are uint16 (default), int16, uint32, int32, uint64, uint64, single, double.
</p>
<h4 class="subsubheading" id="Outputs"><span>Outputs<a class="copiable-link" href="#Outputs"></a></span></h4>
<p><var class="var">data</var> - data read from the device
</p>

<p><strong class="strong">See also:</strong> modbus.
 </p></dd></dl>