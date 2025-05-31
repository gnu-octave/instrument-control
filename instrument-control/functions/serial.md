---
layout: "default"
permalink: "/functions/6_serial/"
pkg_name: "instrument-control"
pkg_version: "0.9.5"
pkg_description: "Low level I/O functions for serial, i2c, spi, parallel, tcp, gpib, modbus, vxi11, udp and usbtmc interfaces."
title: "Instrument-control Toolkit - serial"
category: "Serial (Deprecated)"
func_name: "serial"
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
<dt class="deftypefn" id="index-serial"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">serial</var> =</code> <strong class="def-name">serial</strong> <code class="def-code-arguments">([<var class="var">path</var>], [<var class="var">baudrate</var>], [<var class="var">timeout</var>])</code><a class="copiable-link" href="#index-serial"></a></span></dt>
<dd> 
<p>Open serial interface.
</p> 
<h4 class="subsubheading" id="Inputs"><span>Inputs<a class="copiable-link" href="#Inputs"></a></span></h4>
<p><var class="var">path</var> - the interface path of type String. <br><var class="var">baudrate</var> - the baudrate of interface. If omitted defaults to 115200. <br><var class="var">timeout</var> - the interface timeout value. If omitted defaults to blocking call.
</p> 
<h4 class="subsubheading" id="Outputs"><span>Outputs<a class="copiable-link" href="#Outputs"></a></span></h4>
<p>The serial() shall return an instance of <var class="var">octave_serial</var> class as the result <var class="var">serial</var>.
 </p><h4 class="subsubheading" id="Properties"><span>Properties<a class="copiable-link" href="#Properties"></a></span></h4>
<p>The serial object has the following public properties:
 </p><dl class="table">
<dt>name</dt>
<dd><p>name assigned to the object
 </p></dd>
<dt>type</dt>
<dd><p>instrument type &rsquo;serial&rsquo; (readonly)
 </p></dd>
<dt>port</dt>
<dd><p>OS specific port name (readonly)
 </p></dd>
<dt>status</dt>
<dd><p>status of the object &rsquo;open&rsquo; or &rsquo;closed&rsquo; (readonly)
 </p></dd>
<dt>timeout</dt>
<dd><p>timeout value used for waiting for data
 </p></dd>
<dt>bytesavailable</dt>
<dd><p>number of bytes currently available to read (readonly)
 </p></dd>
<dt>stopbits</dt>
<dd><p>number of stopbits to use
 </p></dd>
<dt>requesttosend</dt>
<dd><p>request to send state - &rsquo;on&rsquo; or &rsquo;off&rsquo;
 </p></dd>
<dt>parity</dt>
<dd><p>Parity setting &rsquo;none&rsquo;, &rsquo;even&rsquo;, &rsquo;odd&rsquo;
 </p></dd>
<dt>bytesize</dt>
<dd><p>Number of bits to a byte (7 or 8)
 </p></dd>
<dt>baudrate</dt>
<dd><p>Baudrate setting
 </p></dd>
<dt>dataterminalready</dt>
<dd><p>state of dataterminal ready - &rsquo;on&rsquo; or &rsquo;off&rsquo;
 </p></dd>
<dt>pinstatus</dt>
<dd><p>current state of pins (readonly)
 </p></dd>
</dl>
</dd></dl>