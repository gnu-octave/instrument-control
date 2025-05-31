---
layout: "default"
permalink: "/functions/10_serialport/"
pkg_name: "instrument-control"
pkg_version: "0.9.5"
pkg_description: "Low level I/O functions for serial, i2c, spi, parallel, tcp, gpib, modbus, vxi11, udp and usbtmc interfaces."
title: "Instrument-control Toolkit - serialport"
category: "Serial Port"
func_name: "serialport"
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
<dt class="deftypefn" id="index-serialport"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">serial</var> =</code> <strong class="def-name">serialport</strong> <code class="def-code-arguments">([<var class="var">path</var>], [<var class="var">baudrate</var>])</code><a class="copiable-link" href="#index-serialport"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-serialport-1"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">serial</var> =</code> <strong class="def-name">serialport</strong> <code class="def-code-arguments">([<var class="var">path</var>], [<var class="var">propname</var>, <var class="var">propvalue</var>])</code><a class="copiable-link" href="#index-serialport-1"></a></span></dt>
<dd> 
<p>Open serial port interface.
</p> 
<h4 class="subsubheading" id="Inputs"><span>Inputs<a class="copiable-link" href="#Inputs"></a></span></h4>
<p><var class="var">path</var> - the interface path of type String. <br>
 <var class="var">baudrate</var> - the baudrate of interface.<br>
 <var class="var">propname</var>,<var class="var">propvalue</var> - property name/value pairs.
</p> 
<p>Known input properties:
 </p><dl class="table">
<dt>BaudRate</dt>
<dd><p>Numeric baudrate value
 </p></dd>
<dt>Timeout</dt>
<dd><p>Numeric timeout value in seconds or -1 to wait forever
 </p></dd>
<dt>StopBits</dt>
<dd><p>number of stopbits to use
 </p></dd>
<dt>Parity</dt>
<dd><p>Parity setting &rsquo;none&rsquo;, &rsquo;even&rsquo;, &rsquo;odd&rsquo;
 </p></dd>
<dt>DataBits</dt>
<dd><p>Number of bits to a byte (5 to 8)
 </p></dd>
<dt>FlowControl</dt>
<dd><p>Number of bits to a byte &rsquo;none&rsquo;, &rsquo;hardware&rsquo;, &rsquo;software&rsquo;
 </p></dd>
<dt>Tag</dt>
<dd><p>User settable string to identify the port.
 </p></dd>
</dl>
 
<h4 class="subsubheading" id="Outputs"><span>Outputs<a class="copiable-link" href="#Outputs"></a></span></h4>
<p>The serialport() shall return an instance of <var class="var">octave_serialport</var> class as the result <var class="var">serial</var>.
</p> 
<h4 class="subsubheading" id="Properties"><span>Properties<a class="copiable-link" href="#Properties"></a></span></h4>
<p>The serial object has the following public properties:
 </p><dl class="table">
<dt>Name</dt>
<dd><p>name assigned to the object
 </p></dd>
<dt>Type</dt>
<dd><p>instrument type &rsquo;serial&rsquo; (readonly)
 </p></dd>
<dt>Port</dt>
<dd><p>OS specific port name (readonly)
 </p></dd>
<dt>Status</dt>
<dd><p>status of the object &rsquo;open&rsquo; or &rsquo;closed&rsquo; (readonly)
 </p></dd>
<dt>Timeout</dt>
<dd><p>timeout value used for waiting for data
 </p></dd>
<dt>NumBytesAvailable</dt>
<dd><p>number of bytes currently available to read (readonly)
 </p></dd>
<dt>NumBytesWritten</dt>
<dd><p>number of bytes written (readonly)
 </p></dd>
<dt>StopBits</dt>
<dd><p>number of stopbits to use
 </p></dd>
<dt>Parity</dt>
<dd><p>Parity setting &rsquo;none&rsquo;, &rsquo;even&rsquo;, &rsquo;odd&rsquo;
 </p></dd>
<dt>DataBits</dt>
<dd><p>Number of bits to a byte (5 to 8)
 </p></dd>
<dt>BaudRate</dt>
<dd><p>Baudrate setting
 </p></dd>
<dt>FlowControl</dt>
<dd><p>Number of bits to a byte &rsquo;none&rsquo;, &rsquo;hardware&rsquo;, &rsquo;software&rsquo;
 </p></dd>
<dt>PinStatus</dt>
<dd><p>current state of pins (readonly)
 </p></dd>
<dt>UserData</dt>
<dd><p>user defined data
 </p></dd>
<dt>Tag</dt>
<dd><p>user defined tag name
 </p></dd>
</dl>
</dd></dl>