---
layout: "default"
permalink: "/functions/@octave_serialport/22_octaveserialportset/"
pkg_name: "instrument-control"
pkg_version: "0.9.5"
pkg_description: "Low level I/O functions for serial, i2c, spi, parallel, tcp, gpib, modbus, vxi11, udp and usbtmc interfaces."
title: "Instrument-control Toolkit - @octave_serialport/set"
category: "Serial Port"
func_name: "@octave_serialport/set"
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
<dt class="deftypefn" id="index-_0028obj_002c"><span class="category-def">Function File: </span><span><code class="def-type">set</code> <strong class="def-name">(<var class="var">obj</var>,</strong> <code class="def-code-arguments"><var class="var">property</var>,<var class="var">value</var>)</code><a class="copiable-link" href="#index-_0028obj_002c"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-_0028obj_002c-1"><span class="category-def">Function File: </span><span><code class="def-type">set</code> <strong class="def-name">(<var class="var">obj</var>,</strong> <code class="def-code-arguments"><var class="var">property</var>,<var class="var">value</var>,&hellip;)</code><a class="copiable-link" href="#index-_0028obj_002c-1"></a></span></dt>
<dd><p>Set the properties of serialport object.
</p>
<h4 class="subsubheading" id="Inputs"><span>Inputs<a class="copiable-link" href="#Inputs"></a></span></h4>
<p><var class="var">serial</var> - instance of <var class="var">octave_serialport</var> class.<br>
 <var class="var">property</var> - name of property.<br>
</p>
<p>If <var class="var">property</var> is a cell so must be <var class="var">value</var>, it sets the values of
 all matching properties.
</p>
<p>The function also accepts property-value pairs.
</p>
<h4 class="subsubheading" id="Properties"><span>Properties<a class="copiable-link" href="#Properties"></a></span></h4>
<dl class="table">
<dt><var class="var">&rsquo;baudrate&rsquo;</var></dt>
<dd><p>Set the baudrate of serial port. Supported values by instrument-control:
 0, 50, 75, 110, 134, 150, 200, 300, 600, 1200, 1800, 2400, 4800, 9600,
 19200, 38400, 57600, 115200 and 230400. The supported baudrate of your
 serial port may be different.
</p>
</dd>
<dt><var class="var">&rsquo;bytesize&rsquo;</var></dt>
<dd><p>Set the bytesize. Supported values: 5, 6, 7 and 8.
</p>
</dd>
<dt><var class="var">&rsquo;name&rsquo;</var></dt>
<dd><p>Set the stored string name of the serial object.
</p>
</dd>
<dt><var class="var">&rsquo;parity&rsquo;</var></dt>
<dd><p>Set the parity value. Supported values: Even/Odd/None. This Parameter
 must be of type string. It is case insensitive and can be abbreviated
 to the first letter only
</p>
</dd>
<dt><var class="var">&rsquo;stopbits&rsquo;</var></dt>
<dd><p>Set the number of stopbits. Supported values: 1, 2.
</p>
</dd>
<dt><var class="var">&rsquo;timeout&rsquo;</var></dt>
<dd><p>Set the timeout value in tenths of a second. Value of -1 means a
 blocking call. Maximum value of 255 (i.e. 25.5 seconds).
</p>
</dd>
<dt><var class="var">&rsquo;requesttosend&rsquo;</var></dt>
<dd><p>Set the requesttosend (RTS) line.
</p>
</dd>
<dt><var class="var">&rsquo;dataterminalready&rsquo;</var></dt>
<dd><p>Set the dataterminalready (DTR) line.
</p>
</dd>
</dl>

<h4 class="subsubheading" id="Outputs"><span>Outputs<a class="copiable-link" href="#Outputs"></a></span></h4>
<p>None
</p>

<p><strong class="strong">See also:</strong> @@octave_serialport/-get.
 </p></dd></dl>