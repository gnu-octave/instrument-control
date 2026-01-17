---
layout: "default"
permalink: "/functions/@octave_modbus/19_octavemodbusread/"
pkg_name: "instrument-control"
pkg_version: "0.10.0"
pkg_description: "Low level I/O functions for serial, i2c, spi, parallel, tcp, gpib, modbus, visa, vxi11, udp and usbtmc interfaces."
title: "Instrument-control Toolkit - @octave_modbus/read"
category: "VXI11"
func_name: "@octave_modbus/read"
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
<dt class="deftypefn def-line" id="index-read"><span class="category-def">: </span><span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">read</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">target</var>, <var class="var">address</var>)</code><a class="copiable-link" href="#index-read"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn def-line" id="index-read-1"><span class="category-def">: </span><span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">read</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">target</var>, <var class="var">address</var>, <var class="var">count</var>)</code><a class="copiable-link" href="#index-read-1"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn def-line" id="index-read-2"><span class="category-def">: </span><span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">read</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">target</var>, <var class="var">address</var>, <var class="var">count</var>, <var class="var">serverId</var>, <var class="var">precision</var>)</code><a class="copiable-link" href="#index-read-2"></a></span></dt>
<dd><p>Read data from modbus device <var class="var">dev</var> target <var class="var">target</var> starting at address <var class="var">address</var>.
</p>
<h4 class="subsubheading" id="Inputs"><span>Inputs<a class="copiable-link" href="#Inputs"></a></span></h4>
<p><var class="var">dev</var> - connected modbus device
</p>
<p><var class="var">target</var> - target type to read. One of &rsquo;coils&rsquo;, &rsquo;inputs&rsquo;, &rsquo;inputregs&rsquo; or &rsquo;holdingregs&rsquo;
</p>
<p><var class="var">address</var> - address to start reading from.
</p>
<p><var class="var">count</var> - number of elements to read. If not provided, count is 1.
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