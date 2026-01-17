---
layout: "default"
permalink: "/functions/@octave_udpport/19_octaveudpportset/"
pkg_name: "instrument-control"
pkg_version: "0.10.0"
pkg_description: "Low level I/O functions for serial, i2c, spi, parallel, tcp, gpib, modbus, visa, vxi11, udp and usbtmc interfaces."
title: "Instrument-control Toolkit - @octave_udpport/set"
category: "VXI11"
func_name: "@octave_udpport/set"
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
<dt class="deftypefn def-line" id="index-_0028obj_002c"><span class="category-def">Function File: </span><span><code class="def-type">set</code> <strong class="def-name">(<var class="var">obj</var>,</strong> <code class="def-code-arguments"><var class="var">property</var>,<var class="var">value</var>)</code><a class="copiable-link" href="#index-_0028obj_002c"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn def-line" id="index-_0028obj_002c-1"><span class="category-def">Function File: </span><span><code class="def-type">set</code> <strong class="def-name">(<var class="var">obj</var>,</strong> <code class="def-code-arguments"><var class="var">property</var>,<var class="var">value</var>,&hellip;)</code><a class="copiable-link" href="#index-_0028obj_002c-1"></a></span></dt>
<dd><p>Set the properties of udpport object.
</p>
<h4 class="subsubheading" id="Inputs"><span>Inputs<a class="copiable-link" href="#Inputs"></a></span></h4>
<p><var class="var">obj</var> - instance of <var class="var">octave_udpport</var> class.<br>
 <var class="var">property</var> - name of property.<br>
</p>
<p>If <var class="var">property</var> is a cell so must be <var class="var">value</var>, it sets the values of
 all matching properties.
</p>
<p>The function also accepts property-value pairs.
</p>
<h4 class="subsubheading" id="Properties"><span>Properties<a class="copiable-link" href="#Properties"></a></span></h4>
<dl class="table">
<dt><var class="var">&rsquo;Name&rsquo;</var></dt>
<dd><p>Set the name for the udpport socket.
</p>
</dd>
<dt><var class="var">&rsquo;UserData&rsquo;</var></dt>
<dd><p>Set the user data of the object.
</p>
</dd>
<dt><var class="var">&rsquo;Tag&rsquo;</var></dt>
<dd><p>Set the user tag to identify the port.
</p>
</dd>
<dt><var class="var">&rsquo;Timeout&rsquo;</var></dt>
<dd><p>Set the timeout value in seconds. Value of -1 means a
 blocking call.
</p>
</dd>
</dl>

<h4 class="subsubheading" id="Outputs"><span>Outputs<a class="copiable-link" href="#Outputs"></a></span></h4>
<p>None
</p>

<p><strong class="strong">See also:</strong> @@octave_udpport/get.
 </p></dd></dl>