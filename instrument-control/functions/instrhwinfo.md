---
layout: "default"
permalink: "/functions/11_instrhwinfo/"
pkg_name: "instrument-control"
pkg_version: "0.9.5"
pkg_description: "Low level I/O functions for serial, i2c, spi, parallel, tcp, gpib, modbus, vxi11, udp and usbtmc interfaces."
title: "Instrument-control Toolkit - instrhwinfo"
category: "General"
func_name: "instrhwinfo"
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
<dt class="deftypefn" id="index-instrhwinfo"><span class="category-def">Function File: </span><span><code class="def-type">[<var class="var">list</var>] =</code> <strong class="def-name">instrhwinfo</strong> <code class="def-code-arguments">()</code><a class="copiable-link" href="#index-instrhwinfo"></a></span></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-instrhwinfo-1"><span class="category-def">Function File: </span><span><code class="def-type"><var class="var">list</var> =</code> <strong class="def-name">instrhwinfo</strong> <code class="def-code-arguments">(<var class="var">interface</var>)</code><a class="copiable-link" href="#index-instrhwinfo-1"></a></span></dt>
<dd><p>Query available hardware for instrument-control
</p>
<p>When run without any input parameters, instrhwinfo will provide the toolbox
 information and a list of supported interfaces.
</p>
<h4 class="subsubheading" id="Inputs"><span>Inputs<a class="copiable-link" href="#Inputs"></a></span></h4>
<p><var class="var">interface</var> is the instrument interface to query. When provided, instrhwinfo
 will provide information on the specified interface.
</p>
<p>Currently only interface &quot;serialport&quot;,&quot;i2c&quot; and &quot;spi&quot; and is supported, which will provide a list of
 available serial ports or i2c ports.
</p>
<h4 class="subsubheading" id="Outputs"><span>Outputs<a class="copiable-link" href="#Outputs"></a></span></h4>
<p>If an output variable is provided, the function will store the information
 to the variable, otherwise it will be displayed to the screen.
</p>
<h4 class="subsubheading" id="Example"><span>Example<a class="copiable-link" href="#Example"></a></span></h4>
<div class="example">
<pre class="example-preformatted"> instrhwinfo
 scalar structure containing the fields:

    ToolboxVersion = 0.4.0
    ToolboxName = octave instrument control package
    SupportedInterfaces =
    {
      [1,1] = i2c
      [1,2] = parallel
      [1,3] = serialport
      [1,4] = tcp
      [1,5] = udp
      [1,6] = usbtmc
      [1,7] = vxi11
    }

 </pre></div>

</dd></dl>