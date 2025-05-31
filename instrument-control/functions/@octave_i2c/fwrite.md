---
layout: "default"
permalink: "/functions/@octave_i2c/18_octavei2cfwrite/"
pkg_name: "instrument-control"
pkg_version: "0.9.5"
pkg_description: "Low level I/O functions for serial, i2c, spi, parallel, tcp, gpib, modbus, vxi11, udp and usbtmc interfaces."
title: "Instrument-control Toolkit - @octave_i2c/fwrite"
category: "I2C"
func_name: "@octave_i2c/fwrite"
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
<dt class="deftypefn" id="index-fwrite"><span class="category-def">Function File: </span><span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>)</code><a class="copiable-link" href="#index-fwrite"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fwrite-1"><span class="category-def">Function File: </span><span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>, <var class="var">precision</var>)</code><a class="copiable-link" href="#index-fwrite-1"></a></span></dt>
<dd><p>Writes <var class="var">data</var> to I2C instrument
</p>
<h4 class="subsubheading" id="Inputs"><span>Inputs<a class="copiable-link" href="#Inputs"></a></span></h4>
<p><var class="var">obj</var> is a I2C object.<br>
 <var class="var">data</var> data to write.<br>
 <var class="var">precision</var> precision of data.<br>
</p>
<h4 class="subsubheading" id="Outputs"><span>Outputs<a class="copiable-link" href="#Outputs"></a></span></h4>
<p>returns number of bytes written.
 </p></dd></dl>