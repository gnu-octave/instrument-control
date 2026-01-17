---
layout: "default"
permalink: "/functions/12_readbinblock/"
pkg_name: "instrument-control"
pkg_version: "0.10.0"
pkg_description: "Low level I/O functions for serial, i2c, spi, parallel, tcp, gpib, modbus, visa, vxi11, udp and usbtmc interfaces."
title: "Instrument-control Toolkit - readbinblock"
category: "VXI11"
func_name: "readbinblock"
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
<dt class="deftypefn def-line" id="index-readbinblock"><span class="category-def">: </span><span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">readbinblock</strong> <code class="def-code-arguments">(<var class="var">dev</var>)</code><a class="copiable-link" href="#index-readbinblock"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn def-line" id="index-readbinblock-1"><span class="category-def">: </span><span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">readbinblock</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">datatype</var>)</code><a class="copiable-link" href="#index-readbinblock-1"></a></span></dt>
<dd><p>read a binblock of data from an instrument device
</p>
<p>readbinblock will discard any data before a recognised binblock.
 If no binblock is found or read, an empty <var class="var">data</var> will be returned.
</p>
<h4 class="subsubheading" id="Inputs"><span>Inputs<a class="copiable-link" href="#Inputs"></a></span></h4>
<p><var class="var">dev</var> - connected device
</p>
<p><var class="var">datatype</var> - optional data type to read data as (default &rsquo;uint8&rsquo;)
 Valid values are:
 </p><dl class="table">
<dt>&quot;string&quot;</dt>
<dd><p>maps to a char array
 </p></dd>
<dt>&quot;char&quot;, &quot;schar&quot;, &quot;int8&quot;</dt>
<dd><p>maps to int8
 </p></dd>
<dt>&quot;uchar&quot;, &quot;uint8&quot;</dt>
<dd><p>maps to uint8
 </p></dd>
<dt>&quot;int16&quot;, &quot;short&quot;</dt>
<dd><p>maps to int16
 </p></dd>
<dt>&quot;uint16&quot;, &quot;ushort&quot;</dt>
<dd><p>maps to uint16
 </p></dd>
<dt>&quot;int32&quot;, &quot;int&quot;</dt>
<dd><p>maps to int32
 </p></dd>
<dt>&quot;uint32&quot;, &quot;uint&quot;</dt>
<dd><p>maps to uint32
 </p></dd>
<dt>&quot;int64&quot;, &quot;long&quot;</dt>
<dd><p>maps to int64
 </p></dd>
<dt>&quot;uint64&quot;, &quot;ulong&quot;</dt>
<dd><p>maps to uint64
 </p></dd>
<dt>&quot;single&quot;, &quot;float&quot;, &quot;float32&quot;</dt>
<dd><p>maps to single
 </p></dd>
<dt>&quot;double&quot;, &quot;float64&quot;</dt>
<dd><p>maps to double
 </p></dd>
</dl>

<h4 class="subsubheading" id="Outputs"><span>Outputs<a class="copiable-link" href="#Outputs"></a></span></h4>
<p><var class="var">data</var> - data read
</p>

<p><strong class="strong">See also:</strong> writebinblock.
 </p></dd></dl>