---
layout: "default"
permalink: "/functions/7_udpport/"
pkg_name: "instrument-control"
pkg_version: "0.10.0"
pkg_description: "Low level I/O functions for serial, i2c, spi, parallel, tcp, gpib, modbus, visa, vxi11, udp and usbtmc interfaces."
title: "Instrument-control Toolkit - udpport"
category: "VXI11"
func_name: "udpport"
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
<dt class="deftypefn def-line" id="index-udpport"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">udp</var> =</code> <strong class="def-name">udpport</strong> <code class="def-code-arguments">()</code><a class="copiable-link" href="#index-udpport"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn def-line" id="index-udpport-1"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">udp</var> =</code> <strong class="def-name">udpport</strong> <code class="def-code-arguments">(<var class="var">propertyname</var>, <var class="var">propertyvalue</var> ...)</code><a class="copiable-link" href="#index-udpport-1"></a></span></dt>
<dd> 
<p>Open udpport interface.
</p> 
<h4 class="subsubheading" id="Inputs"><span>Inputs<a class="copiable-link" href="#Inputs"></a></span></h4>
<p><var class="var">propertyname</var>, <var class="var">propertyvalue</var> - property name/value pair
</p> 
<p>Known input properties:
 </p><dl class="table">
<dt>Name</dt>
<dd><p>name assigned to the udp object
 </p></dd>
<dt>LocalPort</dt>
<dd><p>local port number
 </p></dd>
<dt>LocalHost</dt>
<dd><p>local host address
 </p></dd>
<dt>Timeout</dt>
<dd><p>timeout value in seconds used for waiting for data
 </p></dd>
<dt>EnablePortSharing</dt>
<dd><p>Boolean if the socket has port sharing enabled (readonly)
 </p></dd>
</dl>
 
<h4 class="subsubheading" id="Outputs"><span>Outputs<a class="copiable-link" href="#Outputs"></a></span></h4>
<p>The udpport() shall return instance of <var class="var">octave_udp</var> class as the result <var class="var">udp</var>.
</p> 
<h4 class="subsubheading" id="Properties"><span>Properties<a class="copiable-link" href="#Properties"></a></span></h4>
<p>The udp object has the following public properties:
 </p><dl class="table">
<dt>Name</dt>
<dd><p>name assigned to the udp object
 </p></dd>
<dt>Tag</dt>
<dd><p>user tag assigned to the udp object
 </p></dd>
<dt>Type</dt>
<dd><p>instrument type &rsquo;udpport&rsquo; (readonly)
 </p></dd>
<dt>LocalPort</dt>
<dd><p>local port number (readonly)
 </p></dd>
<dt>LocalHost</dt>
<dd><p>local host address (readonly)
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
<dt>MulticastGroup</dt>
<dd><p>multicast group socket  is subscribed to (readonly)
 </p></dd>
<dt>EnableMultcast</dt>
<dd><p>Boolean if the socket has any multicast group it is subscribed to (readonly)
 </p></dd>
<dt>EnablePortSharing</dt>
<dd><p>Boolean if the socket has port sharing enabled (readonly)
 </p></dd>
<dt>Terminator</dt>
<dd><p>Terminator value used for string data (currently not used)
 </p></dd>
</dl>
</dd></dl>