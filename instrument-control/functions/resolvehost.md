---
layout: "default"
permalink: "/functions/11_resolvehost/"
pkg_name: "instrument-control"
pkg_version: "0.9.5"
pkg_description: "Low level I/O functions for serial, i2c, spi, parallel, tcp, gpib, modbus, vxi11, udp and usbtmc interfaces."
title: "Instrument-control Toolkit - resolvehost"
category: "General"
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
<dt class="deftypefn" id="index-resolvehost"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">name</var> =</code> <strong class="def-name">resolvehost</strong> <code class="def-code-arguments">(<var class="var">host</var>)</code><a class="copiable-link" href="#index-resolvehost"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-resolvehost-1"><span class="category-def">Loadable Function: </span><span><code class="def-type">[<var class="var">name</var>, <var class="var">address</var>] =</code> <strong class="def-name">resolvehost</strong> <code class="def-code-arguments">(<var class="var">host</var>)</code><a class="copiable-link" href="#index-resolvehost-1"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-resolvehost-2"><span class="category-def">Loadable Function: </span><span><code class="def-type"><var class="var">out</var> =</code> <strong class="def-name">resolvehost</strong> <code class="def-code-arguments">(<var class="var">host</var>, <var class="var">returntype</var>)</code><a class="copiable-link" href="#index-resolvehost-2"></a></span></dt>
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