---
layout: "default"
permalink: "/functions/9_tcpserver/"
pkg_name: "instrument-control"
pkg_version: "0.9.5"
pkg_description: "Low level I/O functions for serial, i2c, spi, parallel, tcp, gpib, modbus, vxi11, udp and usbtmc interfaces."
title: "Instrument-control Toolkit - tcpserver"
category: "TCP Server"
func_name: "tcpserver"
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
<dt class="deftypefn" id="index-tcpserver"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">tcpserver</var> =</code> <strong class="def-name">tcpserver</strong> <code class="def-code-arguments">(<var class="var">ipaddress</var>, <var class="var">port</var>)</code><a class="copiable-link" href="#index-tcpserver"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-tcpserver-1"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">tcpserver</var> =</code> <strong class="def-name">tcpserver</strong> <code class="def-code-arguments">(<var class="var">port</var>)</code><a class="copiable-link" href="#index-tcpserver-1"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-tcpserver-2"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">tcpserver</var> =</code> <strong class="def-name">tcpserver</strong> <code class="def-code-arguments">(&hellip;, [<var class="var">propertyname</var>, <var class="var">propertyvalue</var>])</code><a class="copiable-link" href="#index-tcpserver-2"></a></span></dt>
<dd> 
<p>Open tcpserver interface.
</p> 
<h4 class="subsubheading" id="Inputs"><span>Inputs<a class="copiable-link" href="#Inputs"></a></span></h4>
<p><var class="var">ipaddress</var> - the ip address of type String.<br> <var class="var">port</var> - the port number to bind.<br> <var class="var">propname</var>,<var class="var">propvalue</var> - property name/value pairs.
</p> 
<p>Known input properties:
 </p><dl class="table">
<dt>Name</dt>
<dd><p>name value
 </p></dd>
<dt>Timeout</dt>
<dd><p>Numeric timeout value or -1 to wait forever
 </p></dd>
<dt>UserData</dt>
<dd><p>User data value.
 </p></dd>
</dl>
 
<h4 class="subsubheading" id="Outputs"><span>Outputs<a class="copiable-link" href="#Outputs"></a></span></h4>
<p>The tcpserver() shall return instance of <var class="var">octave_tcpserver</var> class as the result <var class="var">tcpserver</var>.
</p> 
<h4 class="subsubheading" id="Properties"><span>Properties<a class="copiable-link" href="#Properties"></a></span></h4>
<p>The tcpserver object has the following public properties:
 </p><dl class="table">
<dt>Connected</dt>
<dd><p>boolean flag for when connected to a client (Readonly)
 </p></dd>
<dt>ClientPort</dt>
<dd><p>connected client port number (Readonly)
 </p></dd>
<dt>ClientAddress</dt>
<dd><p>connected client address (Readonly)
 </p></dd>
<dt>Name</dt>
<dd><p>name assigned to the tcpserver object
 </p></dd>
<dt>Type</dt>
<dd><p>instrument type &rsquo;tcpserver&rsquo; (readonly)
 </p></dd>
<dt>ServerPort</dt>
<dd><p>server port number (Readonly)
 </p></dd>
<dt>ServerAddress</dt>
<dd><p>server address (Readonly)
 </p></dd>
<dt>Status</dt>
<dd><p>status of the object &rsquo;open&rsquo; or &rsquo;closed&rsquo; (readonly)
 </p></dd>
<dt>Timeout</dt>
<dd><p>timeout value in seconds used for waiting for data
 </p></dd>
<dt>NumBytesAvailable</dt>
<dd><p>number of bytes currently available to read (readonly)
 </p></dd>
<dt>NumBytesWritten</dt>
<dd><p>number of bytes currently available to read (readonly)
 </p></dd>
<dt>ByteOrder</dt>
<dd><p>Byte order  for data (currently not used)
 </p></dd>
<dt>Terminator</dt>
<dd><p>Terminator value used for string data (currently not used)
 </p></dd>
<dt>UserData</dt>
<dd><p>User data
 </p></dd>
</dl>
</dd></dl>