---
layout: "default"
permalink: "/functions/6_modbus/"
pkg_name: "instrument-control"
pkg_version: "0.10.0"
pkg_description: "Low level I/O functions for serial, i2c, spi, parallel, tcp, gpib, modbus, visa, vxi11, udp and usbtmc interfaces."
title: "Instrument-control Toolkit - modbus"
category: "VXI11"
func_name: "modbus"
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
<dt class="deftypefn def-line" id="index-modbus"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">dev</var> =</code> <strong class="def-name">modbus</strong> <code class="def-code-arguments">('tcpip', <var class="var">deviceaddress</var>)</code><a class="copiable-link" href="#index-modbus"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn def-line" id="index-modbus-1"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">dev</var> =</code> <strong class="def-name">modbus</strong> <code class="def-code-arguments">('tcpip', <var class="var">deviceaddress</var>, <var class="var">remoteport</var>)</code><a class="copiable-link" href="#index-modbus-1"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn def-line" id="index-modbus-2"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">dev</var> =</code> <strong class="def-name">modbus</strong> <code class="def-code-arguments">('tcpip', <var class="var">deviceaddress</var>, <var class="var">name</var>, <var class="var">value</var>)</code><a class="copiable-link" href="#index-modbus-2"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn def-line" id="index-modbus-3"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">dev</var> =</code> <strong class="def-name">modbus</strong> <code class="def-code-arguments">('serialrtu', <var class="var">serialport</var>)</code><a class="copiable-link" href="#index-modbus-3"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn def-line" id="index-modbus-4"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">dev</var> =</code> <strong class="def-name">modbus</strong> <code class="def-code-arguments">('serialrtu', <var class="var">serialport</var>, <var class="var">name</var>, <var class="var">value</var>)</code><a class="copiable-link" href="#index-modbus-4"></a></span></dt>
<dd> 
<p>Open modbus interface using a specified transport of &rsquo;tcpip&rsquo; or &rsquo;serialrtu&rsquo;.
</p> 
<h4 class="subsubheading" id="Inputs"><span>Inputs<a class="copiable-link" href="#Inputs"></a></span></h4>
<p><var class="var">deviceaddress</var> - the device ip address of type String.<br>
 <var class="var">remoteport</var> - the device remote port number. If not specified, a default of 502 will be used.<br>
 <var class="var">name</var>, <var class="var">value</var> - Optional name value pairs for setting properties of the object.<br>
 <var class="var">serialport</var> - the name of the serial port to connect to. It must be specified when transport is &rsquo;serialrtu&rsquo;.<br>
</p> 
<h4 class="subsubheading" id="Common-Input-Name_002c-Value-pairs"><span>Common Input Name, Value pairs<a class="copiable-link" href="#Common-Input-Name_002c-Value-pairs"></a></span></h4>
<dl class="table">
<dt>Timeout</dt>
<dd><p>timeout value used for waiting for data
 </p></dd>
<dt>NumRetries</dt>
<dd><p>number of retries after a timeout
 </p></dd>
<dt>UserData</dt>
<dd><p>Additional data to attach to the object
 </p></dd>
</dl>
 
<h4 class="subsubheading" id="Serial-RTU-Input-Name_002c-Value-pairs"><span>Serial RTU Input Name, Value pairs<a class="copiable-link" href="#Serial-RTU-Input-Name_002c-Value-pairs"></a></span></h4>
<dl class="table">
<dt>BaudRate</dt>
<dd><p>Baudrate for the serial port
 </p></dd>
<dt>DataBits</dt>
<dd><p>number of databits for serial port
 </p></dd>
<dt>Parity</dt>
<dd><p>Parity for serial port (&rsquo;odd&rsquo;, &rsquo;even&rsquo; or &rsquo;none&rsquo;)
 </p></dd>
<dt>StopBits</dt>
<dd><p>number of stopbits for serial port
 </p></dd>
</dl>
 
<h4 class="subsubheading" id="Outputs"><span>Outputs<a class="copiable-link" href="#Outputs"></a></span></h4>
<p>The modbus() shall return instance of <var class="var">octave_modbus</var> class as the result <var class="var">modbus</var>.
</p> 
<h4 class="subsubheading" id="Properties"><span>Properties<a class="copiable-link" href="#Properties"></a></span></h4>
<p>The modbus object has the following public properties:
 </p><dl class="table">
<dt>Name</dt>
<dd><p>name assigned to the modbus object
 </p></dd>
<dt>Type</dt>
<dd><p>instrument type &rsquo;modbus&rsquo; (readonly)
 </p></dd>
<dt>Port</dt>
<dd><p>Remote port number or serial port name (readonly)
 </p></dd>
<dt>DeviceAddress</dt>
<dd><p>Device address if transport was &rsquo;tcpip&rsquo; (readonly)
 </p></dd>
<dt>Status</dt>
<dd><p>status of the object &rsquo;open&rsquo; or &rsquo;closed&rsquo; (readonly)
 </p></dd>
<dt>Timeout</dt>
<dd><p>timeout value used for waiting for data
 </p></dd>
<dt>NumRetries</dt>
<dd><p>number of retries after a timeout
 </p></dd>
<dt>UserData</dt>
<dd><p>Additional data to attach to the object
 </p></dd>
</dl>
</dd></dl>