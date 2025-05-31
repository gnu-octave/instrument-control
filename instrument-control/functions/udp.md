---
layout: "default"
permalink: "/functions/3_udp/"
pkg_name: "instrument-control"
pkg_version: "0.9.5"
pkg_description: "Low level I/O functions for serial, i2c, spi, parallel, tcp, gpib, modbus, vxi11, udp and usbtmc interfaces."
title: "Instrument-control Toolkit - udp"
category: "UDP (Deprecated)"
func_name: "udp"
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
<dt class="deftypefn" id="index-udp"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">udp</var> =</code> <strong class="def-name">udp</strong> <code class="def-code-arguments">()</code><a class="copiable-link" href="#index-udp"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-udp-1"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">udp</var> =</code> <strong class="def-name">udp</strong> <code class="def-code-arguments">(<var class="var">remoteipaddress</var>, <var class="var">remoteport</var>)</code><a class="copiable-link" href="#index-udp-1"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-udp-2"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">udp</var> =</code> <strong class="def-name">udp</strong> <code class="def-code-arguments">(<var class="var">remoteipaddress</var>, <var class="var">remoteport</var>, [<var class="var">propertyname</var>, <var class="var">propertyvalue</var> ...])</code><a class="copiable-link" href="#index-udp-2"></a></span></dt>
<dd> 
<p>Open udp interface.
</p> 
<h4 class="subsubheading" id="Inputs"><span>Inputs<a class="copiable-link" href="#Inputs"></a></span></h4>
<p><var class="var">remoteipaddress</var> - the ip address of type String. If omitted defaults to &rsquo;127.0.0.1&rsquo;.<br> 
 <var class="var">remoteport</var> - the port number to connect. If omitted defaults to 23.<br> 
 <var class="var">localport</var> - the local port number to bind. If omitted defaults to 0<br> 
 <var class="var">propertyname</var>, <var class="var">propertyvalue</var> - property name/value pair
</p> 
<h4 class="subsubheading" id="Outputs"><span>Outputs<a class="copiable-link" href="#Outputs"></a></span></h4>
<p>The udp() shall return instance of <var class="var">octave_udp</var> class as the result <var class="var">udp</var>.
</p> 
<h4 class="subsubheading" id="Properties"><span>Properties<a class="copiable-link" href="#Properties"></a></span></h4>
<p>The udp object has the following public properties:
 </p><dl class="table">
<dt>name</dt>
<dd><p>name assigned to the udp object
 </p></dd>
<dt>type</dt>
<dd><p>instrument type &rsquo;udp&rsquo; (readonly)
 </p></dd>
<dt>localport</dt>
<dd><p>local port number (readonly)
 </p></dd>
<dt>localhost</dt>
<dd><p>local host address (readonly)
 </p></dd>
<dt>remoteport</dt>
<dd><p>remote port number
 </p></dd>
<dt>remotehost</dt>
<dd><p>remote host
 </p></dd>
<dt>status</dt>
<dd><p>status of the object &rsquo;open&rsquo; or &rsquo;closed&rsquo; (readonly)
 </p></dd>
<dt>timeout</dt>
<dd><p>timeout value in seconds used for waiting for data
 </p></dd>
<dt>bytesavailable</dt>
<dd><p>number of bytes currently available to read (readonly)
 </p></dd>
</dl>
</dd></dl>