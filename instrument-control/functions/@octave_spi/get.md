---
layout: "default"
permalink: "/functions/@octave_spi/15_octavespiget/"
pkg_name: "instrument-control"
pkg_version: "0.10.0"
pkg_description: "Low level I/O functions for serial, i2c, spi, parallel, tcp, gpib, modbus, visa, vxi11, udp and usbtmc interfaces."
title: "Instrument-control Toolkit - @octave_spi/get"
category: "VXI11"
func_name: "@octave_spi/get"
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
<dt class="deftypefn def-line" id="index-get"><span class="category-def">Function File: </span><span><code class="def-type"><var class="var">struct</var> =</code> <strong class="def-name">get</strong> <code class="def-code-arguments">(<var class="var">spi</var>)</code><a class="copiable-link" href="#index-get"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn def-line" id="index-get-1"><span class="category-def">Function File: </span><span><code class="def-type"><var class="var">field</var> =</code> <strong class="def-name">get</strong> <code class="def-code-arguments">(<var class="var">spi</var>, <var class="var">property</var>)</code><a class="copiable-link" href="#index-get-1"></a></span></dt>
<dd><p>Get the properties of spi object.
</p>
<h4 class="subsubheading" id="Inputs"><span>Inputs<a class="copiable-link" href="#Inputs"></a></span></h4>
<p><var class="var">spi</var> - instance of <var class="var">octave_spi</var> class.<br>
</p>
<p><var class="var">property</var> - name of property.<br>
</p>
<h4 class="subsubheading" id="Properties"><span>Properties<a class="copiable-link" href="#Properties"></a></span></h4>
<dl class="table">
<dt><var class="var">&rsquo;name&rsquo;</var></dt>
<dd><p>Name for the spi socket.
</p>
</dd>
<dt><var class="var">&rsquo;bitrate&rsquo;</var></dt>
<dd><p>The bitrate for the spi object.
</p>
</dd>
<dt><var class="var">&rsquo;clockpolarity&rsquo;</var></dt>
<dd><p>The clock polarity for the spi object of &rsquo;idlehigh&rsquo; or &rsquo;idlelow&rsquo;.
</p>
</dd>
<dt><var class="var">&rsquo;clockphase&rsquo;</var></dt>
<dd><p>The clock phase for the spi object of &rsquo;firstedge&rsquo; or &rsquo;secondedge&rsquo;.
</p>
</dd>
<dt><var class="var">&rsquo;port&rsquo;</var></dt>
<dd><p>The device port name.
</p>
</dd>
<dt><var class="var">&rsquo;status&rsquo;</var></dt>
<dd><p>The device status of &rsquo;open&rsquo; or &rsquo;closed&rsquo;
 </p></dd>
</dl>

<h4 class="subsubheading" id="Outputs"><span>Outputs<a class="copiable-link" href="#Outputs"></a></span></h4>
<p>When <var class="var">property</var> was specified, return the value of that property.<br>
 otherwise return the values of all properties as a structure.<br>
</p>

<p><strong class="strong">See also:</strong> @@octave_spi/set.
 </p></dd></dl>