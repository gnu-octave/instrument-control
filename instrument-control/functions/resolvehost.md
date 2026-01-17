---
layout: "default"
permalink: "/functions/11_resolvehost/"
pkg_name: "instrument-control"
pkg_version: "0.10.0"
pkg_description: "Low level I/O functions for serial, i2c, spi, parallel, tcp, gpib, modbus, visa, vxi11, udp and usbtmc interfaces."
title: "Instrument-control Toolkit - resolvehost"
category: "VXI11"
func_name: "resolvehost"
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
<dt class="deftypefn def-line" id="index-resolvehost"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">name</var> =</code> <strong class="def-name">resolvehost</strong> <code class="def-code-arguments">(<var class="var">host</var>)</code><a class="copiable-link" href="#index-resolvehost"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn def-line" id="index-resolvehost-1"><span class="category-def">Loadable Function: </span><span><code class="def-type">[<var class="var">name</var>, <var class="var">address</var>] =</code> <strong class="def-name">resolvehost</strong> <code class="def-code-arguments">(<var class="var">host</var>)</code><a class="copiable-link" href="#index-resolvehost-1"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn def-line" id="index-resolvehost-2"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">out</var> =</code> <strong class="def-name">resolvehost</strong> <code class="def-code-arguments">(<var class="var">host</var>, <var class="var">returntype</var>)</code><a class="copiable-link" href="#index-resolvehost-2"></a></span></dt>
<dd> 
<p>Resolve a network host name or address to network name and address
</p> 
<h4 class="subsubheading" id="Inputs"><span>Inputs<a class="copiable-link" href="#Inputs"></a></span></h4>
<p><var class="var">host</var> - Host name or IP address string to resolve.<br> <var class="var">name</var> - Resolved IP host name.<br> <var class="var">returntype</var> - &rsquo;name&rsquo; to get host name, &rsquo;address&rsquo; to get IP address.
</p> 
<h4 class="subsubheading" id="Outputs"><span>Outputs<a class="copiable-link" href="#Outputs"></a></span></h4>
<p><var class="var">name</var> - Resolved IP host name.<br> <var class="var">address</var> - Resolved IP host address.<br> <var class="var">out</var> - host name if <var class="var">returntype</var> is &rsquo;name&rsquo;, ipaddress if <var class="var">returntype</var> is &rsquo;address&rsquo;<br> 
 </p><h4 class="subsubheading" id="Example"><span>Example<a class="copiable-link" href="#Example"></a></span></h4>
<div class="example">
<pre class="example-preformatted"> %% get resolved ip name and address of www.gnu.org
 [name, address] = resolvehost ('www.gnu.org');
 
 %% get ip address of www.gnu.org
 ipaddress = resolvehost ('www.gnu.org', 'address');
 
 </pre></div>
 

<p><strong class="strong">See also:</strong> tcp, udp.
</p> 
</dd></dl>