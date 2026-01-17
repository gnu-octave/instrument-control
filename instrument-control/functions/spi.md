---
layout: "default"
permalink: "/functions/3_spi/"
pkg_name: "instrument-control"
pkg_version: "0.10.0"
pkg_description: "Low level I/O functions for serial, i2c, spi, parallel, tcp, gpib, modbus, visa, vxi11, udp and usbtmc interfaces."
title: "Instrument-control Toolkit - spi"
category: "VXI11"
func_name: "spi"
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
<dt class="deftypefn def-line" id="index-spi"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">spi</var> =</code> <strong class="def-name">spi</strong> <code class="def-code-arguments">([<var class="var">port_path</var>])</code><a class="copiable-link" href="#index-spi"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn def-line" id="index-spi-1"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">spi</var> =</code> <strong class="def-name">spi</strong> <code class="def-code-arguments">([<var class="var">port_path</var>], [<var class="var">propname</var>, <var class="var">propvalue</var>])</code><a class="copiable-link" href="#index-spi-1"></a></span></dt>
<dd> 
<p>Open a spi interface.
</p> 
<h4 class="subsubheading" id="Inputs"><span>Inputs<a class="copiable-link" href="#Inputs"></a></span></h4>
<p><var class="var">port_path</var> - the interface device port/path of type String. If omitted defaults to 
 &rsquo;/dev/spi-0&rsquo;. <br>
 <var class="var">propname</var>,<var class="var">propvalue</var> - property name/value pairs.
</p> 
<p>Known input properties:
 </p><dl class="table">
<dt>name</dt>
<dd><p>Name of the object
 </p></dd>
<dt>bitrate</dt>
<dd><p>Numeric bitrate value
 </p></dd>
<dt>clockpolarity</dt>
<dd><p>Clock polarity: idlehigh or idlelow.
 </p></dd>
<dt>clockphase</dt>
<dd><p>Clock phase value: firstedge or secondedge
 </p></dd>
</dl>
 
<h4 class="subsubheading" id="Outputs"><span>Outputs<a class="copiable-link" href="#Outputs"></a></span></h4>
<p><var class="var">spi</var> - An instance of <var class="var">octave_spi</var> class.
</p> 
<h4 class="subsubheading" id="Properties"><span>Properties<a class="copiable-link" href="#Properties"></a></span></h4>
<p>The spi object has the following properties:
 </p><dl class="table">
<dt>name</dt>
<dd><p>Name of the object
 </p></dd>
<dt>status</dt>
<dd><p>Open or closed status of object (readonly).
 </p></dd>
<dt>bitrate</dt>
<dd><p>Numeric bitrate value
 </p></dd>
<dt>clockpolarity</dt>
<dd><p>Clock polarity: idlehigh or idlelow.
 </p></dd>
<dt>clockphase</dt>
<dd><p>Clock phase value: firstedge or secondedge
 </p></dd>
<dt>port</dt>
<dd><p>The interface driver port (readonly)
 </p></dd>
</dl>
</dd></dl>