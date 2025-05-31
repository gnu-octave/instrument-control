---
layout: "default"
permalink: "/functions/@octave_serial/20_octaveserialfread/"
pkg_name: "instrument-control"
pkg_version: "0.9.5"
pkg_description: "Low level I/O functions for serial, i2c, spi, parallel, tcp, gpib, modbus, vxi11, udp and usbtmc interfaces."
title: "Instrument-control Toolkit - @octave_serial/fread"
category: "Serial (Deprecated)"
func_name: "@octave_serial/fread"
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
<dt class="deftypefn" id="index-fread"><span class="category-def">Function File: </span><span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code><a class="copiable-link" href="#index-fread"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-1"><span class="category-def">Function File: </span><span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>)</code><a class="copiable-link" href="#index-fread-1"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-2"><span class="category-def">Function File: </span><span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>, <var class="var">precision</var>)</code><a class="copiable-link" href="#index-fread-2"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-3"><span class="category-def">Function File: </span><span><code class="def-type">[<var class="var">data</var>,<var class="var">count</var>] =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, ...)</code><a class="copiable-link" href="#index-fread-3"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-4"><span class="category-def">Function File: </span><span><code class="def-type">[<var class="var">data</var>,<var class="var">count</var>,<var class="var">errmsg</var>] =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, ...)</code><a class="copiable-link" href="#index-fread-4"></a></span></dt>
<dd><p>Reads <var class="var">data</var> from serial instrument
</p>
<h4 class="subsubheading" id="Inputs"><span>Inputs<a class="copiable-link" href="#Inputs"></a></span></h4>
<p><var class="var">obj</var> is a serial object.<br>
 <var class="var">size</var> Number of values to read. (Default: 100).<br>
 <var class="var">precision</var> precision of data.<br>
</p>
<h4 class="subsubheading" id="Outputs"><span>Outputs<a class="copiable-link" href="#Outputs"></a></span></h4>
<p><var class="var">data</var> The read data.<br>
 <var class="var">count</var> values read.<br>
 <var class="var">errmsg</var> read operation error message.<br>
</p>
</dd></dl>