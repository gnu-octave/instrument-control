---
layout: "default"
permalink: "/functions/@octave_serial/27_octaveserialsrlbytesize/"
pkg_name: "instrument-control"
pkg_version: "0.10.0"
pkg_description: "Low level I/O functions for serial, i2c, spi, parallel, tcp, gpib, modbus, visa, vxi11, udp and usbtmc interfaces."
title: "Instrument-control Toolkit - @octave_serial/srl_bytesize"
category: "VXI11"
func_name: "@octave_serial/srl_bytesize"
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
<dt class="deftypefn def-line" id="index-srl_005fbytesize"><span class="category-def">Loadable Function: </span><span><strong class="def-name">srl_bytesize</strong> <code class="def-code-arguments">(<var class="var">serial</var>, <var class="var">bsize</var>)</code><a class="copiable-link" href="#index-srl_005fbytesize"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn def-line" id="index-srl_005fbytesize-1"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">bs</var> =</code> <strong class="def-name">srl_bytesize</strong> <code class="def-code-arguments">(<var class="var">serial</var>)</code><a class="copiable-link" href="#index-srl_005fbytesize-1"></a></span></dt>
<dd>
<p>Set new or get existing serial interface byte size parameter.
</p>
<h4 class="subsubheading" id="Inputs"><span>Inputs<a class="copiable-link" href="#Inputs"></a></span></h4>
<p><var class="var">serial</var> - instance of <var class="var">octave_serial</var> class.<br>
 <var class="var">bsize</var> - byte size of type Integer. Supported values: 5/6/7/8.<br>
</p>
<p>If <var class="var">bsize</var> parameter is omitted, the srl_bytesize() shall return current byte size value
 or in case of unsupported setting -1, as the result <var class="var">bs</var>.
</p>
<p>This function is obsolete. Use get and set method instead.
</p>
<h4 class="subsubheading" id="Outputs"><span>Outputs<a class="copiable-link" href="#Outputs"></a></span></h4>
<p><var class="var">bs</var> -the currently set  byte size.
</p>
</dd></dl>