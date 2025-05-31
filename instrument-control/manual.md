---
layout: "default"
permalink: "/manual/"
title: "Instrument-control Toolkit - Manual"
pkg_name: "instrument-control"
version: "0.9.5"
description: "Low level I/O functions for serial, i2c, spi, parallel, tcp, gpib, modbus, vxi11, udp and usbtmc interfaces."
navigation:
- id: "overview"
  name: "Overview"
  url: "/index"
- id: "Functions"
  name: "Function Reference"
  url: "/functions"
- id: "news"
  name: "News"
  url: "/news"
- id: "manual"
  name: "Manual"
- id: "Installing-and-loading-1"
  name: "&nbsp;&nbsp; Installing and loading"
  url: "/manual/#Installing-and-loading-1"
- id: "Basic-Usage-Overview-1"
  name: "&nbsp;&nbsp; Basic Usage Overview"
  url: "/manual/#Basic-Usage-Overview-1"
- id: "Function-Reference-1"
  name: "&nbsp;&nbsp; Function Reference"
  url: "/manual/#Function-Reference-1"
---
<div class="top-level-extent" id="Top">
<h1 class="top" id="Introduction">Introduction</h1>
<p>The Instrument Control toolkit is a set of low level I/O functions for serial, i2c, spi, modbus, parallel, tcp, gpib, vxi11, udp and usbtmc interfaces
</p>
<div class="element-contents" id="SEC_Contents">
<h2 class="contents-heading">Table of Contents</h2>
<div class="contents">
<ul class="toc-numbered-mark">
  <li><a id="toc-Installing-and-loading-1" href="#Installing-and-loading">1 Installing and loading</a>
  <ul class="toc-numbered-mark">
    <li><a id="toc-Requirements" href="#Requirements">1.1 Requirements</a></li>
    <li><a id="toc-Windows-install" href="#Windows-install">1.2 Windows install</a></li>
    <li><a id="toc-Online-Direct-install" href="#Online-Direct-install">1.3 Online Direct install</a></li>
    <li><a id="toc-Off_002dline-install" href="#Off_002dline-install">1.4 Off-line install</a></li>
    <li><a id="toc-Loading" href="#Loading">1.5 Loading</a></li>
  </ul></li>
  <li><a id="toc-Basic-Usage-Overview-1" href="#Basic-Usage-Overview">2 Basic Usage Overview</a>
  <ul class="toc-numbered-mark">
    <li><a id="toc-Authors-1" href="#Authors">2.1 Authors</a></li>
    <li><a id="toc-Available-Interfaces" href="#Available-Interface">2.2 Available Interfaces</a></li>
    <li><a id="toc-Basic-Serial-1" href="#Basic-Serial">2.3 Basic Serial</a>
    <ul class="toc-numbered-mark">
      <li><a id="toc-Serial" href="#Serial">2.3.1 Serial</a></li>
      <li><a id="toc-SerialPort" href="#SerialPort">2.3.2 SerialPort</a></li>
    </ul></li>
    <li><a id="toc-Basic-TCP-1" href="#Basic-TCP">2.4 Basic TCP</a>
    <ul class="toc-numbered-mark">
      <li><a id="toc-TCP" href="#TCP">2.4.1 TCP</a></li>
      <li><a id="toc-TCP-Client-1" href="#TCP-Client-1">2.4.2 TCP Client</a></li>
    </ul></li>
    <li><a id="toc-Basic-UDP-1" href="#Basic-UDP">2.5 Basic UDP</a>
    <ul class="toc-numbered-mark">
      <li><a id="toc-UDP" href="#UDP">2.5.1 UDP</a></li>
      <li><a id="toc-UDP-Port-1" href="#UDP-Port-1">2.5.2 UDP Port</a></li>
    </ul></li>
  </ul></li>
  <li><a id="toc-Function-Reference-1" href="#Function-Reference">3 Function Reference</a>
  <ul class="toc-numbered-mark">
    <li><a id="toc-Common-Functions-1" href="#Common-Functions">3.1 Common Functions</a>
    <ul class="toc-numbered-mark">
      <li><a id="toc-flushinput" href="#flushinput">3.1.1 flushinput</a></li>
      <li><a id="toc-flushoutput" href="#flushoutput">3.1.2 flushoutput</a></li>
      <li><a id="toc-readbinblock" href="#readbinblock">3.1.3 readbinblock</a></li>
      <li><a id="toc-readline" href="#readline">3.1.4 readline</a></li>
      <li><a id="toc-writebinblock" href="#writebinblock">3.1.5 writebinblock</a></li>
      <li><a id="toc-writeline" href="#writeline">3.1.6 writeline</a></li>
      <li><a id="toc-writeread" href="#writeread">3.1.7 writeread</a></li>
    </ul></li>
    <li><a id="toc-General-1" href="#General">3.2 General</a>
    <ul class="toc-numbered-mark">
      <li><a id="toc-instrhelp" href="#instrhelp">3.2.1 instrhelp</a></li>
      <li><a id="toc-instrhwinfo" href="#instrhwinfo">3.2.2 instrhwinfo</a></li>
      <li><a id="toc-resolvehost" href="#resolvehost">3.2.3 resolvehost</a></li>
    </ul></li>
    <li><a id="toc-GPIB-1" href="#GPIB">3.3 GPIB</a>
    <ul class="toc-numbered-mark">
      <li><a id="toc-_0040octave_005fgpib_002ffclose" href="#g_t_0040octave_005fgpib_002ffclose">3.3.1 @octave_gpib/fclose</a></li>
      <li><a id="toc-_0040octave_005fgpib_002ffopen" href="#g_t_0040octave_005fgpib_002ffopen">3.3.2 @octave_gpib/fopen</a></li>
      <li><a id="toc-_0040octave_005fgpib_002ffprintf" href="#g_t_0040octave_005fgpib_002ffprintf">3.3.3 @octave_gpib/fprintf</a></li>
      <li><a id="toc-_0040octave_005fgpib_002ffread" href="#g_t_0040octave_005fgpib_002ffread">3.3.4 @octave_gpib/fread</a></li>
      <li><a id="toc-_0040octave_005fgpib_002ffscanf" href="#g_t_0040octave_005fgpib_002ffscanf">3.3.5 @octave_gpib/fscanf</a></li>
      <li><a id="toc-_0040octave_005fgpib_002ffwrite" href="#g_t_0040octave_005fgpib_002ffwrite">3.3.6 @octave_gpib/fwrite</a></li>
      <li><a id="toc-clrdevice" href="#clrdevice">3.3.7 clrdevice</a></li>
      <li><a id="toc-gpib" href="#gpib">3.3.8 gpib</a></li>
      <li><a id="toc-gpib_005fclose" href="#gpib_005fclose">3.3.9 gpib_close</a></li>
      <li><a id="toc-gpib_005fread" href="#gpib_005fread">3.3.10 gpib_read</a></li>
      <li><a id="toc-gpib_005ftimeout" href="#gpib_005ftimeout">3.3.11 gpib_timeout</a></li>
      <li><a id="toc-gpib_005fwrite" href="#gpib_005fwrite">3.3.12 gpib_write</a></li>
      <li><a id="toc-spoll" href="#spoll">3.3.13 spoll</a></li>
      <li><a id="toc-trigger" href="#trigger">3.3.14 trigger</a></li>
    </ul></li>
    <li><a id="toc-I2C-1" href="#I2C">3.4 I2C</a>
    <ul class="toc-numbered-mark">
      <li><a id="toc-_0040octave_005fi2c_002ffclose" href="#g_t_0040octave_005fi2c_002ffclose">3.4.1 @octave_i2c/fclose</a></li>
      <li><a id="toc-_0040octave_005fi2c_002ffopen" href="#g_t_0040octave_005fi2c_002ffopen">3.4.2 @octave_i2c/fopen</a></li>
      <li><a id="toc-_0040octave_005fi2c_002ffread" href="#g_t_0040octave_005fi2c_002ffread">3.4.3 @octave_i2c/fread</a></li>
      <li><a id="toc-_0040octave_005fi2c_002ffwrite" href="#g_t_0040octave_005fi2c_002ffwrite">3.4.4 @octave_i2c/fwrite</a></li>
      <li><a id="toc-_0040octave_005fi2c_002fget" href="#g_t_0040octave_005fi2c_002fget">3.4.5 @octave_i2c/get</a></li>
      <li><a id="toc-_0040octave_005fi2c_002fset" href="#g_t_0040octave_005fi2c_002fset">3.4.6 @octave_i2c/set</a></li>
      <li><a id="toc-i2c" href="#i2c">3.4.7 i2c</a></li>
      <li><a id="toc-i2c_005faddr" href="#i2c_005faddr">3.4.8 i2c_addr</a></li>
      <li><a id="toc-i2c_005fclose" href="#i2c_005fclose">3.4.9 i2c_close</a></li>
      <li><a id="toc-i2c_005fread" href="#i2c_005fread">3.4.10 i2c_read</a></li>
      <li><a id="toc-i2c_005fwrite" href="#i2c_005fwrite">3.4.11 i2c_write</a></li>
    </ul></li>
    <li><a id="toc-Modbus-1" href="#Modbus">3.5 Modbus</a>
    <ul class="toc-numbered-mark">
      <li><a id="toc-_0040octave_005fmodbus_002fget" href="#g_t_0040octave_005fmodbus_002fget">3.5.1 @octave_modbus/get</a></li>
      <li><a id="toc-_0040octave_005fmodbus_002fmaskWrite" href="#g_t_0040octave_005fmodbus_002fmaskWrite">3.5.2 @octave_modbus/maskWrite</a></li>
      <li><a id="toc-_0040octave_005fmodbus_002fread" href="#g_t_0040octave_005fmodbus_002fread">3.5.3 @octave_modbus/read</a></li>
      <li><a id="toc-_0040octave_005fmodbus_002fset" href="#g_t_0040octave_005fmodbus_002fset">3.5.4 @octave_modbus/set</a></li>
      <li><a id="toc-_0040octave_005fmodbus_002fwrite" href="#g_t_0040octave_005fmodbus_002fwrite">3.5.5 @octave_modbus/write</a></li>
      <li><a id="toc-_0040octave_005fmodbus_002fwriteRead" href="#g_t_0040octave_005fmodbus_002fwriteRead">3.5.6 @octave_modbus/writeRead</a></li>
      <li><a id="toc-modbus" href="#modbus">3.5.7 modbus</a></li>
    </ul></li>
    <li><a id="toc-Parallel-1" href="#Parallel">3.6 Parallel</a>
    <ul class="toc-numbered-mark">
      <li><a id="toc-_0040octave_005fparallel_002ffclose" href="#g_t_0040octave_005fparallel_002ffclose">3.6.1 @octave_parallel/fclose</a></li>
      <li><a id="toc-_0040octave_005fparallel_002ffopen" href="#g_t_0040octave_005fparallel_002ffopen">3.6.2 @octave_parallel/fopen</a></li>
      <li><a id="toc-_0040octave_005fparallel_002ffread" href="#g_t_0040octave_005fparallel_002ffread">3.6.3 @octave_parallel/fread</a></li>
      <li><a id="toc-_0040octave_005fparallel_002ffwrite" href="#g_t_0040octave_005fparallel_002ffwrite">3.6.4 @octave_parallel/fwrite</a></li>
      <li><a id="toc-parallel" href="#parallel">3.6.5 parallel</a></li>
      <li><a id="toc-pp_005fclose" href="#pp_005fclose">3.6.6 pp_close</a></li>
      <li><a id="toc-pp_005fctrl" href="#pp_005fctrl">3.6.7 pp_ctrl</a></li>
      <li><a id="toc-pp_005fdata" href="#pp_005fdata">3.6.8 pp_data</a></li>
      <li><a id="toc-pp_005fdatadir" href="#pp_005fdatadir">3.6.9 pp_datadir</a></li>
      <li><a id="toc-pp_005fstat" href="#pp_005fstat">3.6.10 pp_stat</a></li>
    </ul></li>
    <li><a id="toc-Serial-_0028Deprecated_0029-1" href="#Serial-_0028Deprecated_0029">3.7 Serial (Deprecated)</a>
    <ul class="toc-numbered-mark">
      <li><a id="toc-_0040octave_005fserial_002ffclose" href="#g_t_0040octave_005fserial_002ffclose">3.7.1 @octave_serial/fclose</a></li>
      <li><a id="toc-_0040octave_005fserial_002fflushinput" href="#g_t_0040octave_005fserial_002fflushinput">3.7.2 @octave_serial/flushinput</a></li>
      <li><a id="toc-_0040octave_005fserial_002fflushoutput" href="#g_t_0040octave_005fserial_002fflushoutput">3.7.3 @octave_serial/flushoutput</a></li>
      <li><a id="toc-_0040octave_005fserial_002ffopen" href="#g_t_0040octave_005fserial_002ffopen">3.7.4 @octave_serial/fopen</a></li>
      <li><a id="toc-_0040octave_005fserial_002ffprintf" href="#g_t_0040octave_005fserial_002ffprintf">3.7.5 @octave_serial/fprintf</a></li>
      <li><a id="toc-_0040octave_005fserial_002ffread" href="#g_t_0040octave_005fserial_002ffread">3.7.6 @octave_serial/fread</a></li>
      <li><a id="toc-_0040octave_005fserial_002ffwrite" href="#g_t_0040octave_005fserial_002ffwrite">3.7.7 @octave_serial/fwrite</a></li>
      <li><a id="toc-_0040octave_005fserial_002fget" href="#g_t_0040octave_005fserial_002fget">3.7.8 @octave_serial/get</a></li>
      <li><a id="toc-_0040octave_005fserial_002fserialbreak" href="#g_t_0040octave_005fserial_002fserialbreak">3.7.9 @octave_serial/serialbreak</a></li>
      <li><a id="toc-_0040octave_005fserial_002fset" href="#g_t_0040octave_005fserial_002fset">3.7.10 @octave_serial/set</a></li>
      <li><a id="toc-_0040octave_005fserial_002fsrl_005fbaudrate" href="#g_t_0040octave_005fserial_002fsrl_005fbaudrate">3.7.11 @octave_serial/srl_baudrate</a></li>
      <li><a id="toc-_0040octave_005fserial_002fsrl_005fbytesize" href="#g_t_0040octave_005fserial_002fsrl_005fbytesize">3.7.12 @octave_serial/srl_bytesize</a></li>
      <li><a id="toc-_0040octave_005fserial_002fsrl_005fclose" href="#g_t_0040octave_005fserial_002fsrl_005fclose">3.7.13 @octave_serial/srl_close</a></li>
      <li><a id="toc-_0040octave_005fserial_002fsrl_005fflush" href="#g_t_0040octave_005fserial_002fsrl_005fflush">3.7.14 @octave_serial/srl_flush</a></li>
      <li><a id="toc-_0040octave_005fserial_002fsrl_005fparity" href="#g_t_0040octave_005fserial_002fsrl_005fparity">3.7.15 @octave_serial/srl_parity</a></li>
      <li><a id="toc-_0040octave_005fserial_002fsrl_005fstopbits" href="#g_t_0040octave_005fserial_002fsrl_005fstopbits">3.7.16 @octave_serial/srl_stopbits</a></li>
      <li><a id="toc-_0040octave_005fserial_002fsrl_005ftimeout" href="#g_t_0040octave_005fserial_002fsrl_005ftimeout">3.7.17 @octave_serial/srl_timeout</a></li>
      <li><a id="toc-serial" href="#serial">3.7.18 serial</a></li>
      <li><a id="toc-seriallist" href="#seriallist">3.7.19 seriallist</a></li>
      <li><a id="toc-srl_005fread" href="#srl_005fread">3.7.20 srl_read</a></li>
      <li><a id="toc-srl_005fwrite" href="#srl_005fwrite">3.7.21 srl_write</a></li>
    </ul></li>
    <li><a id="toc-Serial-Port-1" href="#Serial-Port">3.8 Serial Port</a>
    <ul class="toc-numbered-mark">
      <li><a id="toc-_0040octave_005fserialport_002fconfigureTerminator" href="#g_t_0040octave_005fserialport_002fconfigureTerminator">3.8.1 @octave_serialport/configureTerminator</a></li>
      <li><a id="toc-_0040octave_005fserialport_002fflush" href="#g_t_0040octave_005fserialport_002fflush">3.8.2 @octave_serialport/flush</a></li>
      <li><a id="toc-_0040octave_005fserialport_002ffprintf" href="#g_t_0040octave_005fserialport_002ffprintf">3.8.3 @octave_serialport/fprintf</a></li>
      <li><a id="toc-_0040octave_005fserialport_002ffread" href="#g_t_0040octave_005fserialport_002ffread">3.8.4 @octave_serialport/fread</a></li>
      <li><a id="toc-_0040octave_005fserialport_002ffwrite" href="#g_t_0040octave_005fserialport_002ffwrite">3.8.5 @octave_serialport/fwrite</a></li>
      <li><a id="toc-_0040octave_005fserialport_002fget" href="#g_t_0040octave_005fserialport_002fget">3.8.6 @octave_serialport/get</a></li>
      <li><a id="toc-_0040octave_005fserialport_002fgetpinstatus" href="#g_t_0040octave_005fserialport_002fgetpinstatus">3.8.7 @octave_serialport/getpinstatus</a></li>
      <li><a id="toc-_0040octave_005fserialport_002fread" href="#g_t_0040octave_005fserialport_002fread">3.8.8 @octave_serialport/read</a></li>
      <li><a id="toc-_0040octave_005fserialport_002fserialbreak" href="#g_t_0040octave_005fserialport_002fserialbreak">3.8.9 @octave_serialport/serialbreak</a></li>
      <li><a id="toc-_0040octave_005fserialport_002fset" href="#g_t_0040octave_005fserialport_002fset">3.8.10 @octave_serialport/set</a></li>
      <li><a id="toc-_0040octave_005fserialport_002fsetDTR" href="#g_t_0040octave_005fserialport_002fsetDTR">3.8.11 @octave_serialport/setDTR</a></li>
      <li><a id="toc-_0040octave_005fserialport_002fsetRTS" href="#g_t_0040octave_005fserialport_002fsetRTS">3.8.12 @octave_serialport/setRTS</a></li>
      <li><a id="toc-_0040octave_005fserialport_002fwrite" href="#g_t_0040octave_005fserialport_002fwrite">3.8.13 @octave_serialport/write</a></li>
      <li><a id="toc-serialport" href="#serialport">3.8.14 serialport</a></li>
      <li><a id="toc-serialportlist" href="#serialportlist">3.8.15 serialportlist</a></li>
    </ul></li>
    <li><a id="toc-SPI-1" href="#SPI">3.9 SPI</a>
    <ul class="toc-numbered-mark">
      <li><a id="toc-_0040octave_005fspi_002ffclose" href="#g_t_0040octave_005fspi_002ffclose">3.9.1 @octave_spi/fclose</a></li>
      <li><a id="toc-_0040octave_005fspi_002ffopen" href="#g_t_0040octave_005fspi_002ffopen">3.9.2 @octave_spi/fopen</a></li>
      <li><a id="toc-_0040octave_005fspi_002ffread" href="#g_t_0040octave_005fspi_002ffread">3.9.3 @octave_spi/fread</a></li>
      <li><a id="toc-_0040octave_005fspi_002ffwrite" href="#g_t_0040octave_005fspi_002ffwrite">3.9.4 @octave_spi/fwrite</a></li>
      <li><a id="toc-_0040octave_005fspi_002fget" href="#g_t_0040octave_005fspi_002fget">3.9.5 @octave_spi/get</a></li>
      <li><a id="toc-_0040octave_005fspi_002fread" href="#g_t_0040octave_005fspi_002fread">3.9.6 @octave_spi/read</a></li>
      <li><a id="toc-_0040octave_005fspi_002fset" href="#g_t_0040octave_005fspi_002fset">3.9.7 @octave_spi/set</a></li>
      <li><a id="toc-_0040octave_005fspi_002fwrite" href="#g_t_0040octave_005fspi_002fwrite">3.9.8 @octave_spi/write</a></li>
      <li><a id="toc-_0040octave_005fspi_002fwriteAndRead" href="#g_t_0040octave_005fspi_002fwriteAndRead">3.9.9 @octave_spi/writeAndRead</a></li>
      <li><a id="toc-spi" href="#spi">3.9.10 spi</a></li>
      <li><a id="toc-spi_005fclose" href="#spi_005fclose">3.9.11 spi_close</a></li>
      <li><a id="toc-spi_005fread" href="#spi_005fread">3.9.12 spi_read</a></li>
      <li><a id="toc-spi_005fwrite" href="#spi_005fwrite">3.9.13 spi_write</a></li>
      <li><a id="toc-spi_005fwriteAndRead" href="#spi_005fwriteAndRead">3.9.14 spi_writeAndRead</a></li>
    </ul></li>
    <li><a id="toc-TCP-_0028Deprecated_0029-1" href="#TCP-_0028Deprecated_0029">3.10 TCP (Deprecated)</a>
    <ul class="toc-numbered-mark">
      <li><a id="toc-_0040octave_005ftcp_002ffclose" href="#g_t_0040octave_005ftcp_002ffclose">3.10.1 @octave_tcp/fclose</a></li>
      <li><a id="toc-_0040octave_005ftcp_002fflush" href="#g_t_0040octave_005ftcp_002fflush">3.10.2 @octave_tcp/flush</a></li>
      <li><a id="toc-_0040octave_005ftcp_002fflushinput" href="#g_t_0040octave_005ftcp_002fflushinput">3.10.3 @octave_tcp/flushinput</a></li>
      <li><a id="toc-_0040octave_005ftcp_002fflushoutput" href="#g_t_0040octave_005ftcp_002fflushoutput">3.10.4 @octave_tcp/flushoutput</a></li>
      <li><a id="toc-_0040octave_005ftcp_002ffopen" href="#g_t_0040octave_005ftcp_002ffopen">3.10.5 @octave_tcp/fopen</a></li>
      <li><a id="toc-_0040octave_005ftcp_002ffprintf" href="#g_t_0040octave_005ftcp_002ffprintf">3.10.6 @octave_tcp/fprintf</a></li>
      <li><a id="toc-_0040octave_005ftcp_002ffread" href="#g_t_0040octave_005ftcp_002ffread">3.10.7 @octave_tcp/fread</a></li>
      <li><a id="toc-_0040octave_005ftcp_002ffwrite" href="#g_t_0040octave_005ftcp_002ffwrite">3.10.8 @octave_tcp/fwrite</a></li>
      <li><a id="toc-_0040octave_005ftcp_002fget" href="#g_t_0040octave_005ftcp_002fget">3.10.9 @octave_tcp/get</a></li>
      <li><a id="toc-_0040octave_005ftcp_002fread" href="#g_t_0040octave_005ftcp_002fread">3.10.10 @octave_tcp/read</a></li>
      <li><a id="toc-_0040octave_005ftcp_002fset" href="#g_t_0040octave_005ftcp_002fset">3.10.11 @octave_tcp/set</a></li>
      <li><a id="toc-_0040octave_005ftcp_002fwrite" href="#g_t_0040octave_005ftcp_002fwrite">3.10.12 @octave_tcp/write</a></li>
      <li><a id="toc-tcp" href="#tcp">3.10.13 tcp</a></li>
      <li><a id="toc-tcp_005fclose" href="#tcp_005fclose">3.10.14 tcp_close</a></li>
      <li><a id="toc-tcp_005fread" href="#tcp_005fread">3.10.15 tcp_read</a></li>
      <li><a id="toc-tcp_005ftimeout" href="#tcp_005ftimeout">3.10.16 tcp_timeout</a></li>
      <li><a id="toc-tcp_005fwrite" href="#tcp_005fwrite">3.10.17 tcp_write</a></li>
      <li><a id="toc-tcpip" href="#tcpip">3.10.18 tcpip</a></li>
    </ul></li>
    <li><a id="toc-TCP-Client-2" href="#TCP-Client">3.11 TCP Client</a>
    <ul class="toc-numbered-mark">
      <li><a id="toc-_0040octave_005ftcpclient_002fconfigureTerminator" href="#g_t_0040octave_005ftcpclient_002fconfigureTerminator">3.11.1 @octave_tcpclient/configureTerminator</a></li>
      <li><a id="toc-_0040octave_005ftcpclient_002fflush" href="#g_t_0040octave_005ftcpclient_002fflush">3.11.2 @octave_tcpclient/flush</a></li>
      <li><a id="toc-_0040octave_005ftcpclient_002fget" href="#g_t_0040octave_005ftcpclient_002fget">3.11.3 @octave_tcpclient/get</a></li>
      <li><a id="toc-_0040octave_005ftcpclient_002fread" href="#g_t_0040octave_005ftcpclient_002fread">3.11.4 @octave_tcpclient/read</a></li>
      <li><a id="toc-_0040octave_005ftcpclient_002fset" href="#g_t_0040octave_005ftcpclient_002fset">3.11.5 @octave_tcpclient/set</a></li>
      <li><a id="toc-_0040octave_005ftcpclient_002fwrite" href="#g_t_0040octave_005ftcpclient_002fwrite">3.11.6 @octave_tcpclient/write</a></li>
      <li><a id="toc-tcpclient" href="#tcpclient">3.11.7 tcpclient</a></li>
    </ul></li>
    <li><a id="toc-TCP-Server-1" href="#TCP-Server">3.12 TCP Server</a>
    <ul class="toc-numbered-mark">
      <li><a id="toc-_0040octave_005ftcpserver_002fconfigureTerminator" href="#g_t_0040octave_005ftcpserver_002fconfigureTerminator">3.12.1 @octave_tcpserver/configureTerminator</a></li>
      <li><a id="toc-_0040octave_005ftcpserver_002fflush" href="#g_t_0040octave_005ftcpserver_002fflush">3.12.2 @octave_tcpserver/flush</a></li>
      <li><a id="toc-_0040octave_005ftcpserver_002fget" href="#g_t_0040octave_005ftcpserver_002fget">3.12.3 @octave_tcpserver/get</a></li>
      <li><a id="toc-_0040octave_005ftcpserver_002fread" href="#g_t_0040octave_005ftcpserver_002fread">3.12.4 @octave_tcpserver/read</a></li>
      <li><a id="toc-_0040octave_005ftcpserver_002fset" href="#g_t_0040octave_005ftcpserver_002fset">3.12.5 @octave_tcpserver/set</a></li>
      <li><a id="toc-_0040octave_005ftcpserver_002fwrite" href="#g_t_0040octave_005ftcpserver_002fwrite">3.12.6 @octave_tcpserver/write</a></li>
      <li><a id="toc-tcpserver" href="#tcpserver">3.12.7 tcpserver</a></li>
    </ul></li>
    <li><a id="toc-UDP-_0028Deprecated_0029-1" href="#UDP-_0028Deprecated_0029">3.13 UDP (Deprecated)</a>
    <ul class="toc-numbered-mark">
      <li><a id="toc-_0040octave_005fudp_002ffclose" href="#g_t_0040octave_005fudp_002ffclose">3.13.1 @octave_udp/fclose</a></li>
      <li><a id="toc-_0040octave_005fudp_002fflush" href="#g_t_0040octave_005fudp_002fflush">3.13.2 @octave_udp/flush</a></li>
      <li><a id="toc-_0040octave_005fudp_002fflushinput" href="#g_t_0040octave_005fudp_002fflushinput">3.13.3 @octave_udp/flushinput</a></li>
      <li><a id="toc-_0040octave_005fudp_002fflushoutput" href="#g_t_0040octave_005fudp_002fflushoutput">3.13.4 @octave_udp/flushoutput</a></li>
      <li><a id="toc-_0040octave_005fudp_002ffopen" href="#g_t_0040octave_005fudp_002ffopen">3.13.5 @octave_udp/fopen</a></li>
      <li><a id="toc-_0040octave_005fudp_002ffprintf" href="#g_t_0040octave_005fudp_002ffprintf">3.13.6 @octave_udp/fprintf</a></li>
      <li><a id="toc-_0040octave_005fudp_002ffread" href="#g_t_0040octave_005fudp_002ffread">3.13.7 @octave_udp/fread</a></li>
      <li><a id="toc-_0040octave_005fudp_002ffwrite" href="#g_t_0040octave_005fudp_002ffwrite">3.13.8 @octave_udp/fwrite</a></li>
      <li><a id="toc-_0040octave_005fudp_002fget" href="#g_t_0040octave_005fudp_002fget">3.13.9 @octave_udp/get</a></li>
      <li><a id="toc-_0040octave_005fudp_002fread" href="#g_t_0040octave_005fudp_002fread">3.13.10 @octave_udp/read</a></li>
      <li><a id="toc-_0040octave_005fudp_002fset" href="#g_t_0040octave_005fudp_002fset">3.13.11 @octave_udp/set</a></li>
      <li><a id="toc-_0040octave_005fudp_002fwrite" href="#g_t_0040octave_005fudp_002fwrite">3.13.12 @octave_udp/write</a></li>
      <li><a id="toc-udp" href="#udp">3.13.13 udp</a></li>
      <li><a id="toc-udp_005fclose" href="#udp_005fclose">3.13.14 udp_close</a></li>
      <li><a id="toc-udp_005fdemo" href="#udp_005fdemo">3.13.15 udp_demo</a></li>
      <li><a id="toc-udp_005fread" href="#udp_005fread">3.13.16 udp_read</a></li>
      <li><a id="toc-udp_005ftimeout" href="#udp_005ftimeout">3.13.17 udp_timeout</a></li>
      <li><a id="toc-udp_005fwrite" href="#udp_005fwrite">3.13.18 udp_write</a></li>
    </ul></li>
    <li><a id="toc-UDP-Port-2" href="#UDP-Port">3.14 UDP Port</a>
    <ul class="toc-numbered-mark">
      <li><a id="toc-_0040octave_005fudpport_002fconfigureMulticast" href="#g_t_0040octave_005fudpport_002fconfigureMulticast">3.14.1 @octave_udpport/configureMulticast</a></li>
      <li><a id="toc-_0040octave_005fudpport_002fconfigureTerminator" href="#g_t_0040octave_005fudpport_002fconfigureTerminator">3.14.2 @octave_udpport/configureTerminator</a></li>
      <li><a id="toc-_0040octave_005fudpport_002fflush" href="#g_t_0040octave_005fudpport_002fflush">3.14.3 @octave_udpport/flush</a></li>
      <li><a id="toc-_0040octave_005fudpport_002ffprintf" href="#g_t_0040octave_005fudpport_002ffprintf">3.14.4 @octave_udpport/fprintf</a></li>
      <li><a id="toc-_0040octave_005fudpport_002ffread" href="#g_t_0040octave_005fudpport_002ffread">3.14.5 @octave_udpport/fread</a></li>
      <li><a id="toc-_0040octave_005fudpport_002ffwrite" href="#g_t_0040octave_005fudpport_002ffwrite">3.14.6 @octave_udpport/fwrite</a></li>
      <li><a id="toc-_0040octave_005fudpport_002fget" href="#g_t_0040octave_005fudpport_002fget">3.14.7 @octave_udpport/get</a></li>
      <li><a id="toc-_0040octave_005fudpport_002fread" href="#g_t_0040octave_005fudpport_002fread">3.14.8 @octave_udpport/read</a></li>
      <li><a id="toc-_0040octave_005fudpport_002fset" href="#g_t_0040octave_005fudpport_002fset">3.14.9 @octave_udpport/set</a></li>
      <li><a id="toc-_0040octave_005fudpport_002fwrite" href="#g_t_0040octave_005fudpport_002fwrite">3.14.10 @octave_udpport/write</a></li>
      <li><a id="toc-_0040octave_005fudpport_002fwriteline" href="#g_t_0040octave_005fudpport_002fwriteline">3.14.11 @octave_udpport/writeline</a></li>
      <li><a id="toc-udpport" href="#udpport">3.14.12 udpport</a></li>
    </ul></li>
    <li><a id="toc-USBTMC-1" href="#USBTMC">3.15 USBTMC</a>
    <ul class="toc-numbered-mark">
      <li><a id="toc-_0040octave_005fusbtmc_002ffclose" href="#g_t_0040octave_005fusbtmc_002ffclose">3.15.1 @octave_usbtmc/fclose</a></li>
      <li><a id="toc-_0040octave_005fusbtmc_002ffopen" href="#g_t_0040octave_005fusbtmc_002ffopen">3.15.2 @octave_usbtmc/fopen</a></li>
      <li><a id="toc-_0040octave_005fusbtmc_002ffread" href="#g_t_0040octave_005fusbtmc_002ffread">3.15.3 @octave_usbtmc/fread</a></li>
      <li><a id="toc-_0040octave_005fusbtmc_002ffwrite" href="#g_t_0040octave_005fusbtmc_002ffwrite">3.15.4 @octave_usbtmc/fwrite</a></li>
      <li><a id="toc-usbtmc" href="#usbtmc">3.15.5 usbtmc</a></li>
      <li><a id="toc-usbtmc_005fclose" href="#usbtmc_005fclose">3.15.6 usbtmc_close</a></li>
      <li><a id="toc-usbtmc_005fread" href="#usbtmc_005fread">3.15.7 usbtmc_read</a></li>
      <li><a id="toc-usbtmc_005fwrite" href="#usbtmc_005fwrite">3.15.8 usbtmc_write</a></li>
    </ul></li>
    <li><a id="toc-VXI11-1" href="#VXI11">3.16 VXI11</a>
    <ul class="toc-numbered-mark">
      <li><a id="toc-_0040octave_005fvxi11_002ffclose" href="#g_t_0040octave_005fvxi11_002ffclose">3.16.1 @octave_vxi11/fclose</a></li>
      <li><a id="toc-_0040octave_005fvxi11_002ffopen" href="#g_t_0040octave_005fvxi11_002ffopen">3.16.2 @octave_vxi11/fopen</a></li>
      <li><a id="toc-_0040octave_005fvxi11_002ffread" href="#g_t_0040octave_005fvxi11_002ffread">3.16.3 @octave_vxi11/fread</a></li>
      <li><a id="toc-_0040octave_005fvxi11_002ffwrite" href="#g_t_0040octave_005fvxi11_002ffwrite">3.16.4 @octave_vxi11/fwrite</a></li>
      <li><a id="toc-vxi11" href="#vxi11">3.16.5 vxi11</a></li>
      <li><a id="toc-vxi11_005fclose" href="#vxi11_005fclose">3.16.6 vxi11_close</a></li>
      <li><a id="toc-vxi11_005fread" href="#vxi11_005fread">3.16.7 vxi11_read</a></li>
      <li><a id="toc-vxi11_005fwrite" href="#vxi11_005fwrite">3.16.8 vxi11_write</a></li>
    </ul></li>
  </ul></li>
  <li><a id="toc-GNU-General-Public-License" href="#Copying">Appendix A GNU General Public License</a></li>
  <li><a id="toc-Index-1" href="#Index" rel="index">Index</a></li>
</ul>
</div>
</div>
<hr>
<div class="chapter-level-extent" id="Installing-and-loading">
<h2 class="chapter" id="Installing-and-loading-1">1 Installing and loading</h2>
<a class="index-entry-id" id="index-Installing-and-loading"></a>
<p>The Instrument Control toolkit must be installed and then loaded to be used.
</p>
<p>It can be installed in <abbr class="acronym">GNU</abbr> Octave directly from octave-forge,
or can be installed in an off-line mode via a downloaded tarball.
</p>
<p>The toolkit must be then be loaded once per each <abbr class="acronym">GNU</abbr> Octave session in order to use its functionality.
</p>
<div class="section-level-extent" id="Requirements">
<h3 class="section">1.1 Requirements</h3>
<a class="index-entry-id" id="index-Requirements"></a>
<p>For GPIB support (Linux only), linux-gpib must be installed before installing instrument-control. 
GPIB support is also available for windows by following the information from the wiki:
https://wiki.octave.org/Instrument_control_package#Requirements
</p>
<p>For VXI11 support, rpcgen, and libtirpc-devel must be installed before installing instrument-control. 
</p>
<p>For MODBUS support, the libmodbus-devel must be installed before installing instrument-control.
</p>
</div>
<div class="section-level-extent" id="Windows-install">
<h3 class="section">1.2 Windows install</h3>
<a class="index-entry-id" id="index-Windows-install"></a>
<p>If using the <abbr class="acronym">GNU</abbr> Octave installer in Windows, the toolkit will have already been installed, and does not need to be re-installed
unless a newer version is available.
</p>
<p>Run the following command to verify if the toolkit is available:
</p>
<div class="example">
<pre class="example-preformatted">pkg list instrument-control
</pre></div>
</div>
<div class="section-level-extent" id="Online-Direct-install">
<h3 class="section">1.3 Online Direct install</h3>
<a class="index-entry-id" id="index-Online-install"></a>
<p>With an internet connection available, toolkit can be installed from
octave-forge using the following command within <abbr class="acronym">GNU</abbr> Octave:
</p>
<div class="example">
<pre class="example-preformatted">pkg install -forge instrument-control
</pre></div>
<p>The latest released version of the toolkit will be downloaded, compiled and installed.
</p>
</div>
<div class="section-level-extent" id="Off_002dline-install">
<h3 class="section">1.4 Off-line install</h3>
<a class="index-entry-id" id="index-Off_002dline-install"></a>
<p>With the toolkit package already downloaded, and in the current directory when running
<abbr class="acronym">GNU</abbr> Octave, the package can be installed using the following command within <abbr class="acronym">GNU</abbr> Octave:
</p>
<div class="example">
<pre class="example-preformatted">pkg install instrument-control-0.9.5.tar.gz
</pre></div>
</div>
<div class="section-level-extent" id="Loading">
<h3 class="section">1.5 Loading</h3>
<a class="index-entry-id" id="index-Loading"></a>
<p>Regardless of the method of installing the toolkit, in order to use its functions,
the toolkit must be loaded using the pkg load command:
</p>
<div class="example">
<pre class="example-preformatted">pkg load instrument-control
</pre></div>
<p>The toolkit must be loaded on each <abbr class="acronym">GNU</abbr> Octave session.
</p>
<hr>
</div>
</div>
<div class="chapter-level-extent" id="Basic-Usage-Overview">
<h2 class="chapter" id="Basic-Usage-Overview-1">2 Basic Usage Overview</h2>
<a class="index-entry-id" id="index-Basic-Usage-Overview"></a>
<hr>
<div class="section-level-extent" id="Authors">
<h3 class="section" id="Authors-1">2.1 Authors</h3>
<p>The Instrument control package provides low level I/O functions for serial, i2c, spi, parallel, tcp, gpib, vxi11, udp and usbtmc interfaces.
</p>
<p>It was written  mainly by the following developers:
</p>
<ul class="itemize mark-bullet">
<li>Andrius Sutas &lt;andrius.sutasg at mail.com&gt;
</li><li>Stefan Mahr &lt;dac922 at gmx.de&gt;
</li><li>John Donoghue &lt;john.donoghue at ieee.org&gt;
</li></ul>
<hr>
</div>
<div class="section-level-extent" id="Available-Interface">
<h3 class="section" id="Available-Interfaces">2.2 Available Interfaces</h3>
<p>The ability to use each interface is dependent on OS and what libraries were available during the toolkit install.
</p>
<p>To verify the available interfaces, run the following command in octave:
</p>
<div class="example">
<pre class="example-preformatted">instrhwinfo
</pre></div>
<p>The function will return information on the supported interfaces that are available, similar to below:
</p>
<div class="example">
<pre class="example-preformatted">    ToolboxVersion = 0.7.0
    ToolboxName = octave instrument control package
    SupportedInterfaces =
    {
      [1,1] = gpib
      [1,2] = i2c
      [1,3] = parallel
      [1,4] = serial
      [1,5] = serialport
      [1,6] = tcp
      [1,7] = tcpclient
      [1,8] = udp
      [1,9] = udpport
      [1,10] = usbtmc
      [1,11] = vxi11
    }
</pre></div>
<p>Most interfaces have two types of functions:
</p>
<ul class="itemize mark-bullet">
<li>somewhat compatible matlab functions such as fread, fwrite
</li><li>interface specific lower level functions such as udp_read, udp_write
</li></ul>
<hr>
</div>
<div class="section-level-extent" id="Basic-Serial">
<h3 class="section" id="Basic-Serial-1">2.3 Basic Serial</h3>
<div class="subsection-level-extent" id="Serial">
<h4 class="subsection">2.3.1 Serial</h4>
<table class="cartouche" border="1"><tr><td>
<p><strong class="strong">NOTE</strong>: The serial object has been deprecated and may not appear in newer versions of the instrument-control toolbox. Instead new code should use the serialport object.
</p></td></tr></table>
<p>The serial port can be opened using the serial function:
</p>
<div class="example">
<pre class="example-preformatted">s = serial(&quot;/dev/ttyUSB1&quot;, 115200) 
</pre></div>
<p>The first parameter is the device name and is OS specific. The second parameter is the baudrate. 
</p>
<p>A list of available serial ports can be retrieved using the function:
</p>
<div class="example">
<pre class="example-preformatted">seriallist
</pre></div>
<p>After creating the interface object, properties of the device can be set or retrieved using get or set functions or as property access.
</p>
<div class="example">
<pre class="example-preformatted">s = serial(&quot;/dev/ttyUSB1&quot;, 115200) 
br = get(s, &quot;baudrate&quot;) # gets the baudrate
br = s.baudrate  # also gets the baudrate
set(s, &quot;baudrate&quot;, 9600) # set the baudrate
s.baudrate = 9600 # also sets the baudrate
</pre></div>
<p>The device can be written and read from using fread, fwrite and srl_read and slr_write functions.
</p>
<div class="example">
<pre class="example-preformatted">srl_write(s, &quot;hello world&quot;) # write hello world
fprintf(s, &quot;hello again&quot;)
val = srl_read(s, 10) # attempt to read
val = fread(s, 10)
</pre></div>
<p>The device can be closed using fclose or srl_close.
</p>
<div class="example">
<pre class="example-preformatted">fclose(s)
</pre></div>
</div>
<div class="subsection-level-extent" id="SerialPort">
<h4 class="subsection">2.3.2 SerialPort</h4>
<p>The recommended method of accessing serial ports is through the serialport object.
</p>
<p>The serial port can be opened using the serialport function:
</p>
<div class="example">
<pre class="example-preformatted">s = serialport(&quot;/dev/ttyUSB1&quot;, 115200) 
</pre></div>
<p>The first parameter is the device name and is OS specific. The second parameter is the baudrate. 
</p>
<p>A list of available serial ports can be retrieved using the function:
</p>
<div class="example">
<pre class="example-preformatted">serialportlist
</pre></div>
<p>After creating the interface object, properties of the device can be set or retrieved using get or set functions or as property access.
</p>
<div class="example">
<pre class="example-preformatted">s = serialport(&quot;/dev/ttyUSB1&quot;, 115200) 
br = get(s, &quot;BaudRate&quot;) # gets the baudrate
br = s.BaudRate  # also gets the baudrate
set(s, &quot;BaudRate&quot;, 9600) # set the baudrate
s.BaudRate = 9600 # also sets the baudrate
</pre></div>
<p>The device can be written and read from using read and write functions.
</p>
<div class="example">
<pre class="example-preformatted">write(s, &quot;hello world&quot;) # write hello world
val = read(s, 10)
</pre></div>
<p>The device can be closed by clearing the serialport object.
</p>
<div class="example">
<pre class="example-preformatted">clear s
</pre></div>
<hr>
</div>
</div>
<div class="section-level-extent" id="Basic-TCP">
<h3 class="section" id="Basic-TCP-1">2.4 Basic TCP</h3>
<div class="subsection-level-extent" id="TCP">
<h4 class="subsection">2.4.1 TCP</h4>
<table class="cartouche" border="1"><tr><td>
<p><strong class="strong">NOTE</strong>: The TCP object has been deprecated and may not appear in newer versions of the instrument-control toolbox. Instead new code should use the tcpclient object.
</p></td></tr></table>
<p>A TCP connection can be opened using the tcp or tcpip function:
</p>
<div class="example">
<pre class="example-preformatted">s = tcp(&quot;127.0.0.1&quot;, 80) 
</pre></div>
<p>The first parameter is the IP address to connect to. The second parameter is the port number. And optional timeout value can be also be provided.
</p>
<p>A more matlab compatible function is available as tcpip to also open a tcp port:
</p>
<div class="example">
<pre class="example-preformatted">s = tcpip(&quot;gnu.org&quot;, 80) 
</pre></div>
<p>The first  parameter is a hostname or ip address, the second the port number. Additional parameter/value pairs can be provided after the port.
</p>
<p>After creating the interface object, properties of the device can be set or retrieved using get or set functions or as property access.
</p>
<div class="example">
<pre class="example-preformatted">s = tcp(&quot;127.0.0.1&quot;, 80)
oldtimeout = get(s, &quot;timeout&quot;) # get timeout
set(s, &quot;timeout&quot;, 10) # set the timeout
s.timeout = oldtimeout # also sets the timeout
</pre></div>
<p>The device can be written and read from using fread, fwrite and tcp_read and tcp_write functions.
</p>
<div class="example">
<pre class="example-preformatted">tcp_write(s, &quot;HEAD / HTTP/1.1\r\n\r\n&quot;)
val = tcp_read(s, 100, 500) # attempt to read 100 bytes
</pre></div>
<p>The device can be closed using fclose or tcp_close.
</p>
<div class="example">
<pre class="example-preformatted">fclose(s)
</pre></div>
</div>
<div class="subsection-level-extent" id="TCP-Client-1">
<h4 class="subsection">2.4.2 TCP Client</h4>
<p>The recommended method of creating a tcp connection is through the tcpclient object.
</p>
<p>A TCP connection can be opened using the tcpclient function:
</p>
<div class="example">
<pre class="example-preformatted">s = tcpclient(&quot;127.0.0.1&quot;, 80) 
</pre></div>
<p>The first parameter is the IP address or hostname to connect to. The second parameter is the port number.
</p>
<p>Additional parameter/value pairs can be provided after the port.
</p>
<p>After creating the interface object, properties of the device can be set or retrieved using get or set functions or as property access.
</p>
<div class="example">
<pre class="example-preformatted">s = tcpclient(&quot;127.0.0.1&quot;, 80)
oldtimeout = get(s, &quot;Timeout&quot;) # get timeout
set(s, &quot;Timeout&quot;, 10) # set the timeout
s.Timeout = oldtimeout # also sets the timeout
</pre></div>
<p>The device can be written and read from using read and write functions.
</p>
<div class="example">
<pre class="example-preformatted">write(s, &quot;HEAD / HTTP/1.1\r\n\r\n&quot;)
val = read(s, 100) # attempt to read 100 bytes
</pre></div>
<p>The device can be closed by clearing the object variable.
</p>
<div class="example">
<pre class="example-preformatted">clear s
</pre></div>
<hr>
</div>
</div>
<div class="section-level-extent" id="Basic-UDP">
<h3 class="section" id="Basic-UDP-1">2.5 Basic UDP</h3>
<div class="subsection-level-extent" id="UDP">
<h4 class="subsection">2.5.1 UDP</h4>
<table class="cartouche" border="1"><tr><td>
<p><strong class="strong">NOTE</strong>: The UDP object has been deprecated and may not appear in newer versions of the instrument-control toolbox. Instead new code should use the udpport object.
</p></td></tr></table>
<p>A UDP connection can be opened using the udp function:
</p>
<div class="example">
<pre class="example-preformatted">s = udp(&quot;127.0.0.1&quot;, 80) 
</pre></div>
<p>The first parameter is the IP address data will be to. The second parameter is the port number. 
</p>
<p>If and ip address and port is not provides, it will default to &quot;127.0.0.1&quot; and 23.
</p>
<p>The address and port can be changed after creation using the remotehost and remoteport properties.
</p>
<div class="example">
<pre class="example-preformatted">s = udp() 
s.remotehost = &quot;127.0.0.1&quot;;
s.remoteport = 100;
</pre></div>
<p>After creating the interface object, other properties of the device can be set or retrieved using get or set functions or as property access.
</p>
<div class="example">
<pre class="example-preformatted">s = udp(&quot;127.0.0.1&quot;, 80)
oldtimeout = get(s, &quot;timeout&quot;) # get timeout
set(s, &quot;timeout&quot;, 10) # set the timeout
s.timeout = oldtimeout # also sets the timeout
</pre></div>
<p>The device can be written and read from using fread, fwrite and udp_read and udp_write functions.
</p>
<div class="example">
<pre class="example-preformatted">udp_write(s, &quot;test&quot;)
val = udp_read(s, 5)
</pre></div>
<p>The device can be closed using fclose or udp_close.
</p>
<div class="example">
<pre class="example-preformatted">fclose(s)
</pre></div>
</div>
<div class="subsection-level-extent" id="UDP-Port-1">
<h4 class="subsection">2.5.2 UDP Port</h4>
<p>The recommended method of creating a udp socket is through the udpport object.
</p>
<p>A udpport object can be created using the udpport function:
</p>
<div class="example">
<pre class="example-preformatted">s = udpport()
</pre></div>
<p>Additional parameter/value pairs can be provided during creation of the object.
</p>
<p>After creating the interface object, properties of the device can be set or retrieved using get or set functions or as property access.
</p>
<div class="example">
<pre class="example-preformatted">s = udpport()
oldtimeout = get(s, &quot;Timeout&quot;) # get timeout
set(s, &quot;Timeout&quot;, 10) # set the timeout
s.Timeout = oldtimeout # also sets the timeout
</pre></div>
<p>The device can be written and read from using read and write functions.
</p>
<p>The destination address and port to send data to must be specified at least on the first time write is used.
</p>
<div class="example">
<pre class="example-preformatted">write(s, &quot;test&quot;, &quot;127.0.0.1&quot;, s.LocalPort)
val = read(s)
</pre></div>
<p>The device can be closed by clearing the object variable.
</p>
<div class="example">
<pre class="example-preformatted">clear s
</pre></div>
<hr>
</div>
</div>
</div>
<div class="chapter-level-extent" id="Function-Reference">
<h2 class="chapter" id="Function-Reference-1">3 Function Reference</h2>
<a class="index-entry-id" id="index-Function-Reference"></a>
<p>The functions currently available in the toolkit are described below.
</p>
<hr>
<div class="section-level-extent" id="Common-Functions">
<h3 class="section" id="Common-Functions-1">3.1 Common Functions</h3>
<a class="index-entry-id" id="index-Common-Functions"></a>
<div class="subsection-level-extent" id="flushinput">
<h4 class="subsection">3.1.1 flushinput</h4>
<a class="index-entry-id" id="index-flushinput"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-flushinput-4"><span class="category-def">: </span><strong class="def-name">flushinput</strong> <code class="def-code-arguments">(<var class="var">dev</var>)</code></dt>
<dd><p>Flush the instruments input buffers
</p>
<h4 class="subsubheading" id="Inputs">Inputs</h4>
<p><var class="var">dev</var> - connected device or array of devices
</p>
<h4 class="subsubheading" id="Outputs">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> flushoutput.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="flushoutput">
<h4 class="subsection">3.1.2 flushoutput</h4>
<a class="index-entry-id" id="index-flushoutput"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-flushoutput-4"><span class="category-def">: </span><strong class="def-name">flushoutput</strong> <code class="def-code-arguments">(<var class="var">dev</var>)</code></dt>
<dd><p>Flush the instruments output buffers
</p>
<h4 class="subsubheading" id="Inputs-1">Inputs</h4>
<p><var class="var">dev</var> - connected device or array of devices
</p>
<h4 class="subsubheading" id="Outputs-1">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> flushinput.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="readbinblock">
<h4 class="subsection">3.1.3 readbinblock</h4>
<a class="index-entry-id" id="index-readbinblock"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-readbinblock-1"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">readbinblock</strong> <code class="def-code-arguments">(<var class="var">dev</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-readbinblock-2"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">readbinblock</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">datatype</var>)</code></dt>
<dd><p>read a binblock of data from a instrument device
</p>
<h4 class="subsubheading" id="Inputs-2">Inputs</h4>
<p><var class="var">dev</var> - connected device
</p>
<p><var class="var">datatype</var> - optional data type to read data as (default &rsquo;uint8&rsquo;)
</p>
<h4 class="subsubheading" id="Outputs-2">Outputs</h4>
<p><var class="var">data</var> - data read
</p>
<p><strong class="strong">See also:</strong> flushoutput.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="readline">
<h4 class="subsection">3.1.4 readline</h4>
<a class="index-entry-id" id="index-readline"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-readline-1"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">readline</strong> <code class="def-code-arguments">(<var class="var">dev</var>)</code></dt>
<dd><p>read data from a instrument device excluding terminator value
</p>
<h4 class="subsubheading" id="Inputs-3">Inputs</h4>
<p><var class="var">dev</var> - connected device
</p>
<h4 class="subsubheading" id="Outputs-3">Outputs</h4>
<p><var class="var">data</var> - ASCII data read
</p>
<p><strong class="strong">See also:</strong> flushoutput.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="writebinblock">
<h4 class="subsection">3.1.5 writebinblock</h4>
<a class="index-entry-id" id="index-writebinblock"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-writebinblock-1"><span class="category-def">: </span><strong class="def-name">writebinblock</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">data</var>, <var class="var">datatype</var>)</code></dt>
<dd><p>Write a IEEE 488.2 binblock of data to a instrument device
</p>
<p>binblock formatted data is defined as:
</p>
<p>#&lt;A&gt;&lt;B&gt;&lt;C&gt;
</p>
<p>where:
     &lt;A&gt; ASCII number containing the length of part &lt;B&gt;
</p>
<p>&lt;B&gt; ASCII number containing the number of bytes of &lt;C&gt;
</p>
<p>&lt;C&gt; Binary data block
</p>
<h4 class="subsubheading" id="Inputs-4">Inputs</h4>
<p><var class="var">dev</var> - connected device
</p>
<p><var class="var">data</var> - binary data to send
</p>
<p><var class="var">datatype</var> - datatype to send data as
</p>
<h4 class="subsubheading" id="Outputs-4">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> flushoutput.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="writeline">
<h4 class="subsection">3.1.6 writeline</h4>
<a class="index-entry-id" id="index-writeline"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-writeline-2"><span class="category-def">: </span><strong class="def-name">writeline</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">data</var>)</code></dt>
<dd><p>Write data to a instrument device including terminator value
</p>
<h4 class="subsubheading" id="Inputs-5">Inputs</h4>
<p><var class="var">dev</var> - connected device
</p>
<p><var class="var">data</var> - ASCII data to write
</p>
<h4 class="subsubheading" id="Outputs-5">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> flushoutput.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="writeread">
<h4 class="subsection">3.1.7 writeread</h4>
<a class="index-entry-id" id="index-writeread"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-writeread-1"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">writeread</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">command</var>)</code></dt>
<dd><p>write a ASCII command and read data from a instrument device.
</p>
<h4 class="subsubheading" id="Inputs-6">Inputs</h4>
<p><var class="var">dev</var> - connected device
</p>
<p><var class="var">command</var> - ASCII command
</p>
<h4 class="subsubheading" id="Outputs-6">Outputs</h4>
<p><var class="var">data</var> - ASCII data read
</p>
<p><strong class="strong">See also:</strong> readline, writeline.
</p></dd></dl>
<hr>
</div>
</div>
<div class="section-level-extent" id="General">
<h3 class="section" id="General-1">3.2 General</h3>
<a class="index-entry-id" id="index-General"></a>
<div class="subsection-level-extent" id="instrhelp">
<h4 class="subsection">3.2.1 instrhelp</h4>
<a class="index-entry-id" id="index-instrhelp"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-instrhelp-1"><span class="category-def">: </span><strong class="def-name">instrhelp</strong> <code class="def-code-arguments">()</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-instrhelp-2"><span class="category-def">: </span><strong class="def-name">instrhelp</strong> <code class="def-code-arguments">(<var class="var">funcname</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-instrhelp-3"><span class="category-def">: </span><strong class="def-name">instrhelp</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dd><p>Display instrument help
</p>
<h4 class="subsubheading" id="Inputs-7">Inputs</h4>
<p><var class="var">funcname</var> - function to display help about.<br>
<var class="var">obj</var> - object to display help about.<br>
</p>
<p>If no input is provided, the function will display and overview
 of the package functionality.
</p>
<h4 class="subsubheading" id="Outputs-7">Outputs</h4>
<p>None
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="instrhwinfo">
<h4 class="subsection">3.2.2 instrhwinfo</h4>
<a class="index-entry-id" id="index-instrhwinfo"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-instrhwinfo-1"><span class="category-def">Function File: </span><code class="def-type">[<var class="var">list</var>] =</code> <strong class="def-name">instrhwinfo</strong> <code class="def-code-arguments">()</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-instrhwinfo-2"><span class="category-def">Function File: </span><code class="def-type"><var class="var">list</var> =</code> <strong class="def-name">instrhwinfo</strong> <code class="def-code-arguments">(<var class="var">interface</var>)</code></dt>
<dd><p>Query available hardware for instrument-control
</p>
<p>When run without any input parameters, instrhwinfo will provide the toolbox
 information and a list of supported interfaces.
</p>
<h4 class="subsubheading" id="Inputs-8">Inputs</h4>
<p><var class="var">interface</var> is the instrument interface to query. When provided, instrhwinfo
 will provide information on the specified interface.
</p>
<p>Currently only interface &quot;serialport&quot;,&quot;i2c&quot; and &quot;spi&quot; and is supported, which will provide a list of
 available serial ports or i2c ports.
</p>
<h4 class="subsubheading" id="Outputs-8">Outputs</h4>
<p>If an output variable is provided, the function will store the information
 to the variable, otherwise it will be displayed to the screen.
</p>
<h4 class="subsubheading" id="Example">Example</h4>
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
</div>
<div class="subsection-level-extent" id="resolvehost">
<h4 class="subsection">3.2.3 resolvehost</h4>
<a class="index-entry-id" id="index-resolvehost"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-resolvehost-1"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">name</var> =</code> <strong class="def-name">resolvehost</strong> <code class="def-code-arguments">(<var class="var">host</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-resolvehost-2"><span class="category-def">Loadable Function: </span><code class="def-type">[<var class="var">name</var>, <var class="var">address</var>] =</code> <strong class="def-name">resolvehost</strong> <code class="def-code-arguments">(<var class="var">host</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-resolvehost-3"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">out</var> =</code> <strong class="def-name">resolvehost</strong> <code class="def-code-arguments">(<var class="var">host</var>, <var class="var">returntype</var>)</code></dt>
<dd>
<p>Resolve a network host name or address to network name and address
</p>
<h4 class="subsubheading" id="Inputs-9">Inputs</h4>
<p><var class="var">host</var> - Host name or IP address string to resolve.<br>
<var class="var">name</var> - Resolved IP host name.<br>
<var class="var">returntype</var> - &rsquo;name&rsquo; to get host name, &rsquo;address&rsquo; to get IP address.
</p>
<h4 class="subsubheading" id="Outputs-9">Outputs</h4>
<p><var class="var">name</var> - Resolved IP host name.<br>
<var class="var">address</var> - Resolved IP host address.<br>
<var class="var">out</var> - host name if <var class="var">returntype</var> is &rsquo;name&rsquo;, ipaddress if <var class="var">returntype</var> is &rsquo;address&rsquo;<br>
</p>
<h4 class="subsubheading" id="Example-1">Example</h4>
<div class="example">
<pre class="example-preformatted">%% get resolved ip name and address of www.gnu.org
[name, address] = resolvehost ('www.gnu.org');
%% get ip address of www.gnu.org
ipaddress = resolvehost ('www.gnu.org', 'address');
</pre></div>
<p><strong class="strong">See also:</strong> tcp, udp.
</p>
</dd></dl>
<hr>
</div>
</div>
<div class="section-level-extent" id="GPIB">
<h3 class="section" id="GPIB-1">3.3 GPIB</h3>
<a class="index-entry-id" id="index-GPIB"></a>
<div class="subsection-level-extent" id="g_t_0040octave_005fgpib_002ffclose">
<h4 class="subsection">3.3.1 @octave_gpib/fclose</h4>
<a class="index-entry-id" id="index-fclose"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fclose-9"><span class="category-def">Function File: </span><code class="def-type"><var class="var">res</var> =</code> <strong class="def-name">fclose</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dd><p>Closes connection to GPIB device <var class="var">obj</var>
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fgpib_002ffopen">
<h4 class="subsection">3.3.2 @octave_gpib/fopen</h4>
<a class="index-entry-id" id="index-fopen"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fopen-9"><span class="category-def">Function File: </span><code class="def-type"><var class="var">res</var> =</code> <strong class="def-name">fopen</strong> <code class="def-code-arguments">(<var class="var">obj</var>) (dummy)</code></dt>
<dd><p>Opens connection to GPIB device <var class="var">obj</var>
 This currently is a dummy function to improve compatibility to MATLAB
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fgpib_002ffprintf">
<h4 class="subsection">3.3.3 @octave_gpib/fprintf</h4>
<a class="index-entry-id" id="index-fprintf"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fprintf-6"><span class="category-def">Function File: </span><strong class="def-name">fprintf</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">cmd</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fprintf-7"><span class="category-def">Function File: </span><strong class="def-name">fprintf</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">format</var>, <var class="var">cmd</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fprintf-8"><span class="category-def">Function File: </span><strong class="def-name">fprintf</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">cmd</var>, <var class="var">mode</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fprintf-9"><span class="category-def">Function File: </span><strong class="def-name">fprintf</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">format</var>, <var class="var">cmd</var>, <var class="var">mode</var>)</code></dt>
<dd><p>Writes string <var class="var">cmd</var> to GPIB instrument
</p>
<p><var class="var">obj</var> is a GPIB object
</p>
<p><var class="var">cmd</var> String
<var class="var">format</var> Format specifier
<var class="var">mode</var> sync
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fgpib_002ffread">
<h4 class="subsection">3.3.4 @octave_gpib/fread</h4>
<a class="index-entry-id" id="index-fread"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fread-11"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-12"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-13"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>, <var class="var">precision</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-14"><span class="category-def">Function File: </span><code class="def-type">[<var class="var">data</var>,<var class="var">count</var>] =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, ...)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-15"><span class="category-def">Function File: </span><code class="def-type">[<var class="var">data</var>,<var class="var">count</var>,<var class="var">errmsg</var>] =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, ...)</code></dt>
<dd><p>Reads <var class="var">data</var> from GPIB instrument
</p>
<p><var class="var">obj</var> is a GPIB object
</p>
<p><var class="var">size</var> Number of values to read. (Default: 100)
<var class="var">precision</var> precision of data
</p>
<p><var class="var">count</var> values read
<var class="var">errmsg</var> read operation error message
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fgpib_002ffscanf">
<h4 class="subsection">3.3.5 @octave_gpib/fscanf</h4>
<a class="index-entry-id" id="index-fscanf"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fscanf-1"><span class="category-def">Function File: </span><code class="def-type"><var class="var">res</var> =</code> <strong class="def-name">fscanf</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fscanf-2"><span class="category-def">Function File: </span><code class="def-type"><var class="var">res</var> =</code> <strong class="def-name">fscanf</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">format</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fscanf-3"><span class="category-def">Function File: </span><code class="def-type"><var class="var">res</var> =</code> <strong class="def-name">fscanf</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">format</var>, <var class="var">size</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fscanf-4"><span class="category-def">Function File: </span><code class="def-type">[<var class="var">res</var>,<var class="var">count</var>] =</code> <strong class="def-name">fscanf</strong> <code class="def-code-arguments">(<var class="var">obj</var>, ...)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fscanf-5"><span class="category-def">Function File: </span><code class="def-type">[<var class="var">res</var>,<var class="var">count</var>,<var class="var">errmsg</var>] =</code> <strong class="def-name">fscanf</strong> <code class="def-code-arguments">(<var class="var">obj</var>, ...)</code></dt>
<dd><p>Reads data <var class="var">res</var> from GPIB instrument
</p>
<p><var class="var">obj</var> is a GPIB object
</p>
<p><var class="var">format</var> Format specifier
<var class="var">size</var> number of values
</p>
<p><var class="var">count</var> values read
<var class="var">errmsg</var> read operation error message
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fgpib_002ffwrite">
<h4 class="subsection">3.3.6 @octave_gpib/fwrite</h4>
<a class="index-entry-id" id="index-fwrite"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fwrite-11"><span class="category-def">Function File: </span><strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fwrite-12"><span class="category-def">Function File: </span><strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>, <var class="var">precision</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fwrite-13"><span class="category-def">Function File: </span><strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>, <var class="var">mode</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fwrite-14"><span class="category-def">Function File: </span><strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>, <var class="var">precision</var>, <var class="var">mode</var>)</code></dt>
<dd><p>Writes <var class="var">data</var> to GPIB instrument
</p>
<p><var class="var">obj</var> is a GPIB object
</p>
<p><var class="var">data</var> data to write
<var class="var">precision</var> precision of data
<var class="var">mode</var> sync
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="clrdevice">
<h4 class="subsection">3.3.7 clrdevice</h4>
<a class="index-entry-id" id="index-clrdevice"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-clrdevice-1"><span class="category-def">Function File: </span><strong class="def-name">clrdevice</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dd><p>Send clear command to Clear GPIB instrument.
</p>
<p><var class="var">obj</var> is a GPIB object
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="gpib">
<h4 class="subsection">3.3.8 gpib</h4>
<a class="index-entry-id" id="index-gpib"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-gpib-1"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">gpib</var> =</code> <strong class="def-name">gpib</strong> <code class="def-code-arguments">([<var class="var">gpibid</var>], [<var class="var">timeout</var>])</code></dt>
<dd>
<p>Open gpib interface.
</p>
<p><var class="var">gpibid</var> - the interface number.<br>
<var class="var">timeout</var> - the interface timeout value. If omitted defaults to blocking call.
</p>
<p>The gpib() shall return instance of <var class="var">octave_gpib</var> class as the result <var class="var">gpib</var>.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="gpib_005fclose">
<h4 class="subsection">3.3.9 gpib_close</h4>
<a class="index-entry-id" id="index-gpib_005fclose"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-gpib_005fclose-1"><span class="category-def">Loadable Function: </span><strong class="def-name">gpib_close</strong> <code class="def-code-arguments">(<var class="var">gpib</var>)</code></dt>
<dd>
<p>Close the interface and release a file descriptor.
</p>
<p><var class="var">gpib</var> - instance of <var class="var">octave_gpib</var> class.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="gpib_005fread">
<h4 class="subsection">3.3.10 gpib_read</h4>
<a class="index-entry-id" id="index-gpib_005fread"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-gpib_005fread-1"><span class="category-def">Loadable Function: </span><code class="def-type">[<var class="var">data</var>, <var class="var">count</var>, <var class="var">eoi</var>] =</code> <strong class="def-name">gpib_read</strong> <code class="def-code-arguments">(<var class="var">gpib</var>, <var class="var">n</var>)</code></dt>
<dd>
<p>Read from gpib interface.
</p>
<p><var class="var">gpib</var> - instance of <var class="var">octave_gpib</var> class.<br>
<var class="var">n</var> - number of bytes to attempt to read of type Integer.
</p>
<p>The gpib_read() shall return number of bytes successfully read in <var class="var">count</var> as Integer and the bytes themselves in <var class="var">data</var> as uint8 array.
<var class="var">eoi</var> indicates read operation complete 
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="gpib_005ftimeout">
<h4 class="subsection">3.3.11 gpib_timeout</h4>
<a class="index-entry-id" id="index-gpib_005ftimeout"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-gpib_005ftimeout-1"><span class="category-def">Loadable Function: </span><strong class="def-name">gpib_timeout</strong> <code class="def-code-arguments">(<var class="var">gpib</var>, <var class="var">timeout</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-gpib_005ftimeout-2"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">t</var> =</code> <strong class="def-name">gpib_timeout</strong> <code class="def-code-arguments">(<var class="var">gpib</var>)</code></dt>
<dd>
<p>Set new or get existing gpib interface timeout parameter. The timeout value is valid from 0 to 17.
</p>
<p><var class="var">gpib</var> - instance of <var class="var">octave_gpib</var> class.<br>
<var class="var">timeout</var> - Value of 0 means never timeout, 11 means one second and 17 means 1000 seconds (see GPIB documentation (ibtmo) for further details)
</p>
<p>If <var class="var">timeout</var> parameter is omitted, the gpib_timeout() shall return current timeout value as the result <var class="var">t</var>.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="gpib_005fwrite">
<h4 class="subsection">3.3.12 gpib_write</h4>
<a class="index-entry-id" id="index-gpib_005fwrite"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-gpib_005fwrite-1"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">n</var> =</code> <strong class="def-name">gpib_write</strong> <code class="def-code-arguments">(<var class="var">gpib</var>, <var class="var">data</var>)</code></dt>
<dd>
<p>Write data to a gpib interface.
</p>
<p><var class="var">gpib</var> - instance of <var class="var">octave_gpib</var> class.<br>
<var class="var">data</var> - data to be written to the gpib interface. Can be either of String or uint8 type.
</p>
<p>Upon successful completion, gpib_write() shall return the number of bytes written as the result <var class="var">n</var>.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="spoll">
<h4 class="subsection">3.3.13 spoll</h4>
<a class="index-entry-id" id="index-spoll"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-spoll-1"><span class="category-def">Function File: </span><code class="def-type"><var class="var">out</var> =</code> <strong class="def-name">spoll</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-spoll-2"><span class="category-def">Function File: </span><code class="def-type">[<var class="var">out</var>,<var class="var">statusByte</var>] =</code> <strong class="def-name">spoll</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dd><p>Serial polls GPIB instruments.
</p>
<p><var class="var">obj</var> is a GPIB object or a cell array of GPIB objects
</p>
<p><var class="var">out</var> GPIB objects ready for service
<var class="var">statusByte</var> status Byte
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="trigger">
<h4 class="subsection">3.3.14 trigger</h4>
<a class="index-entry-id" id="index-trigger"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-trigger-1"><span class="category-def">Function File: </span><strong class="def-name">trigger</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dd><p>Triggers GPIB instrument.
</p>
<p><var class="var">obj</var> is a GPIB object
</p>
</dd></dl>
<hr>
</div>
</div>
<div class="section-level-extent" id="I2C">
<h3 class="section" id="I2C-1">3.4 I2C</h3>
<a class="index-entry-id" id="index-I2C"></a>
<div class="subsection-level-extent" id="g_t_0040octave_005fi2c_002ffclose">
<h4 class="subsection">3.4.1 @octave_i2c/fclose</h4>
<a class="index-entry-id" id="index-fclose-1"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fclose-10"><span class="category-def">Function File: </span><code class="def-type"><var class="var">res</var> =</code> <strong class="def-name">fclose</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dd><p>Closes I2C connection <var class="var">obj</var>
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fi2c_002ffopen">
<h4 class="subsection">3.4.2 @octave_i2c/fopen</h4>
<a class="index-entry-id" id="index-fopen-1"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fopen-10"><span class="category-def">Function File: </span><code class="def-type"><var class="var">res</var> =</code> <strong class="def-name">fopen</strong> <code class="def-code-arguments">(<var class="var">obj</var>) (dummy)</code></dt>
<dd><p>Opens I2C connection <var class="var">obj</var>
</p>
<p>This currently is a dummy function to improve compatibility to MATLAB
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fi2c_002ffread">
<h4 class="subsection">3.4.3 @octave_i2c/fread</h4>
<a class="index-entry-id" id="index-fread-1"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fread-16"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-17"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-18"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>, <var class="var">precision</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-19"><span class="category-def">Function File: </span><code class="def-type">[<var class="var">data</var>,<var class="var">count</var>] =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, ...)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-20"><span class="category-def">Function File: </span><code class="def-type">[<var class="var">data</var>,<var class="var">count</var>,<var class="var">errmsg</var>] =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, ...)</code></dt>
<dd><p>Reads <var class="var">data</var> from I2C instrument
</p>
<h4 class="subsubheading" id="Inputs-10">Inputs</h4>
<p><var class="var">obj</var> is a I2C object.<br>
<var class="var">size</var> Number of values to read. (Default: 100).<br>
<var class="var">precision</var> precision of data.<br>
</p>
<h4 class="subsubheading" id="Outputs-10">Outputs</h4>
<p><var class="var">data</var> data values.<br>
<var class="var">count</var> number of values read.<br>
<var class="var">errmsg</var> read operation error message.<br>
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fi2c_002ffwrite">
<h4 class="subsection">3.4.4 @octave_i2c/fwrite</h4>
<a class="index-entry-id" id="index-fwrite-1"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fwrite-15"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fwrite-16"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>, <var class="var">precision</var>)</code></dt>
<dd><p>Writes <var class="var">data</var> to I2C instrument
</p>
<h4 class="subsubheading" id="Inputs-11">Inputs</h4>
<p><var class="var">obj</var> is a I2C object.<br>
<var class="var">data</var> data to write.<br>
<var class="var">precision</var> precision of data.<br>
</p>
<h4 class="subsubheading" id="Outputs-11">Outputs</h4>
<p>returns number of bytes written.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fi2c_002fget">
<h4 class="subsection">3.4.5 @octave_i2c/get</h4>
<a class="index-entry-id" id="index-get"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-get-10"><span class="category-def">Function File: </span><code class="def-type"><var class="var">struct</var> =</code> <strong class="def-name">get</strong> <code class="def-code-arguments">(<var class="var">i2c</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-get-11"><span class="category-def">Function File: </span><code class="def-type"><var class="var">field</var> =</code> <strong class="def-name">get</strong> <code class="def-code-arguments">(<var class="var">i2c</var>, <var class="var">property</var>)</code></dt>
<dd><p>Get the properties of i2c object.
</p>
<h4 class="subsubheading" id="Inputs-12">Inputs</h4>
<p><var class="var">i2c</var> - instance of <var class="var">octave_i2c</var> class.<br>
</p>
<p><var class="var">property</var> - name of property.<br>
</p>
<h4 class="subsubheading" id="Outputs-12">Outputs</h4>
<p>When <var class="var">property</var> was specified, return the value of that property.<br>
 otherwise return the values of all properties as a structure.<br>
</p>
<p><strong class="strong">See also:</strong> @octave_i2c/set.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fi2c_002fset">
<h4 class="subsection">3.4.6 @octave_i2c/set</h4>
<a class="index-entry-id" id="index-set"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-_0028obj_002c"><span class="category-def">Function File: </span><code class="def-type">set</code> <strong class="def-name">(<var class="var">obj</var>,</strong> <code class="def-code-arguments"><var class="var">property</var>,<var class="var">value</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-_0028obj_002c-1"><span class="category-def">Function File: </span><code class="def-type">set</code> <strong class="def-name">(<var class="var">obj</var>,</strong> <code class="def-code-arguments"><var class="var">property</var>,<var class="var">value</var>,&hellip;)</code></dt>
<dd><p>Set the properties of i2c object.
</p>
<h4 class="subsubheading" id="Inputs-13">Inputs</h4>
<p><var class="var">obj</var> - instance of <var class="var">octave_i2c</var> class.<br>
<var class="var">property</var> - name of property.<br>
</p>
<p>If <var class="var">property</var> is a cell so must be <var class="var">value</var>, it sets the values of
 all matching properties.
</p>
<p>The function also accepts property-value pairs.
</p>
<h4 class="subsubheading" id="Properties">Properties</h4>
<dl class="table">
<dt><var class="var">&rsquo;name&rsquo;</var></dt>
<dd><p>Set the name for the i2c socket.
</p>
</dd>
<dt><var class="var">&rsquo;remoteaddress&rsquo;</var></dt>
<dd><p>Set the remote address for the i2c socket.
</p>
</dd>
</dl>
<h4 class="subsubheading" id="Outputs-13">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> @octave_i2c/get.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="i2c">
<h4 class="subsection">3.4.7 i2c</h4>
<a class="index-entry-id" id="index-i2c"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-i2c-1"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">i2c</var> =</code> <strong class="def-name">i2c</strong> <code class="def-code-arguments">([<var class="var">port_path</var>], [<var class="var">address</var>])</code></dt>
<dd>
<p>Open i2c interface.
</p>
<h4 class="subsubheading" id="Inputs-14">Inputs</h4>
<p><var class="var">port_path</var> - the interface device port/path of type String. If omitted defaults to 
&rsquo;/dev/i2c-0&rsquo;. <br>
<var class="var">address</var> - the slave device address. If omitted must be set using i2c_addr() call.
</p>
<h4 class="subsubheading" id="Outputs-14">Outputs</h4>
<p><var class="var">i2c</var> - An instance of <var class="var">octave_i2c</var> class.
</p>
<h4 class="subsubheading" id="Properties-1">Properties</h4>
<p>The i2c object has the following properties:
</p><dl class="table">
<dt>name</dt>
<dd><p>Name of the object
</p></dd>
<dt>remoteaddress</dt>
<dd><p>the slave device address
</p></dd>
<dt>port</dt>
<dd><p>The interface driver port (readonly)
</p></dd>
</dl>
</dd></dl>
</div>
<div class="subsection-level-extent" id="i2c_005faddr">
<h4 class="subsection">3.4.8 i2c_addr</h4>
<a class="index-entry-id" id="index-i2c_005faddr"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-i2c_005faddr-1"><span class="category-def">Loadable Function: </span><strong class="def-name">i2c_addr</strong> <code class="def-code-arguments">(<var class="var">i2c</var>, <var class="var">address</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-i2c_005faddr-2"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">addr</var> =</code> <strong class="def-name">i2c_addr</strong> <code class="def-code-arguments">(<var class="var">i2c</var>)</code></dt>
<dd>
<p>Set new or get existing i2c slave device address.
</p>
<h4 class="subsubheading" id="Inputs-15">Inputs</h4>
<p><var class="var">i2c</var> - instance of <var class="var">octave_i2c</var> class.<br>
<var class="var">address</var> - i2c slave device address of type Integer.
The address is passed in the 7 or 10 lower bits of the argument.
</p>
<h4 class="subsubheading" id="Outputs-15">Outputs</h4>
<p><var class="var">addr</var> - If <var class="var">address</var> parameter is omitted, the i2c_addr() shall return
current i2c slave device address.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="i2c_005fclose">
<h4 class="subsection">3.4.9 i2c_close</h4>
<a class="index-entry-id" id="index-i2c_005fclose"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-i2c_005fclose-1"><span class="category-def">Loadable Function: </span><strong class="def-name">i2c_close</strong> <code class="def-code-arguments">(<var class="var">i2c</var>)</code></dt>
<dd>
<p>Close the interface and release a file descriptor.
</p>
<h4 class="subsubheading" id="Inputs-16">Inputs</h4>
<p><var class="var">i2c</var> - instance of <var class="var">octave_i2c</var> class.<br>
</p>
<h4 class="subsubheading" id="Outputs-16">Outputs</h4>
<p>None
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="i2c_005fread">
<h4 class="subsection">3.4.10 i2c_read</h4>
<a class="index-entry-id" id="index-i2c_005fread"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-i2c_005fread-1"><span class="category-def">Loadable Function: </span><code class="def-type">[<var class="var">data</var>, <var class="var">count</var>] =</code> <strong class="def-name">i2c_read</strong> <code class="def-code-arguments">(<var class="var">i2c</var>, <var class="var">n</var>)</code></dt>
<dd>
<p>Read from i2c slave device.
</p>
<h4 class="subsubheading" id="Inputs-17">Inputs</h4>
<p><var class="var">i2c</var> - instance of <var class="var">octave_i2c</var> class.<br>
<var class="var">n</var> - number of bytes to attempt to read of type Integer.
</p>
<h4 class="subsubheading" id="Outputs-17">Outputs</h4>
<p>The i2c_read() shall return number of bytes successfully read in <var class="var">count</var> as Integer and the bytes themselves in <var class="var">data</var> as uint8 array.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="i2c_005fwrite">
<h4 class="subsection">3.4.11 i2c_write</h4>
<a class="index-entry-id" id="index-i2c_005fwrite"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-i2c_005fwrite-1"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">n</var> =</code> <strong class="def-name">i2c_write</strong> <code class="def-code-arguments">(<var class="var">i2c</var>, <var class="var">data</var>)</code></dt>
<dd>
<p>Write data to a i2c slave device.
</p>
<h4 class="subsubheading" id="Inputs-18">Inputs</h4>
<p><var class="var">i2c</var> - instance of <var class="var">octave_i2c</var> class.<br>
<var class="var">data</var> - data, of type uint8, to be written to the slave device.
</p>
<h4 class="subsubheading" id="Outputs-18">Outputs</h4>
<p>Upon successful completion, i2c_write() shall return the number of bytes written as the result <var class="var">n</var>.
</p></dd></dl>
<hr>
</div>
</div>
<div class="section-level-extent" id="Modbus">
<h3 class="section" id="Modbus-1">3.5 Modbus</h3>
<a class="index-entry-id" id="index-Modbus"></a>
<div class="subsection-level-extent" id="g_t_0040octave_005fmodbus_002fget">
<h4 class="subsection">3.5.1 @octave_modbus/get</h4>
<a class="index-entry-id" id="index-get-1"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-get-12"><span class="category-def">Function File: </span><code class="def-type"><var class="var">struct</var> =</code> <strong class="def-name">get</strong> <code class="def-code-arguments">(<var class="var">dev</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-get-13"><span class="category-def">Function File: </span><code class="def-type"><var class="var">field</var> =</code> <strong class="def-name">get</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">property</var>)</code></dt>
<dd><p>Get the properties of modbus object.
</p>
<h4 class="subsubheading" id="Inputs-19">Inputs</h4>
<p><var class="var">dev</var> - instance of <var class="var">octave_modbus</var> class.<br>
<var class="var">property</var> - name of property.<br>
</p>
<h4 class="subsubheading" id="Outputs-19">Outputs</h4>
<p>When <var class="var">property</var> was specified, return the value of that property.<br>
 otherwise return the values of all properties as a structure.<br>
</p>
<p><strong class="strong">See also:</strong> @octave_modbus/set.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fmodbus_002fmaskWrite">
<h4 class="subsection">3.5.2 @octave_modbus/maskWrite</h4>
<a class="index-entry-id" id="index-maskWrite"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-maskWrite-1"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">maskWrite</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">address</var>, <var class="var">andmask</var>, <var class="var">ormask</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-maskWrite-2"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">maskWrite</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">address</var>, <var class="var">andmask</var>, <var class="var">ormask</var>, <var class="var">serverid</var>)</code></dt>
<dd><p>Read holding register at <var class="var">address</var> from modbus device <var class="var">dev</var> apply masking and write the change data.
</p>
<p>writeregister value = (readregister value AND andMask) OR (orMask AND (NOT andMask))
</p>
<h4 class="subsubheading" id="Inputs-20">Inputs</h4>
<p><var class="var">dev</var> - connected modbus device
</p>
<p><var class="var">address</var> - address to read from.
</p>
<p><var class="var">andmask</var> - AND mask to apply to the register
</p>
<p><var class="var">ormask</var> - OR mask to apply to the register
</p>
<p><var class="var">serverId</var> - address to send to (0-247). Default of 1 is used if not specified.
</p>
<h4 class="subsubheading" id="Outputs-20">Outputs</h4>
<p><var class="var">data</var> - data read from the device
</p>
<p><strong class="strong">See also:</strong> modbus.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fmodbus_002fread">
<h4 class="subsection">3.5.3 @octave_modbus/read</h4>
<a class="index-entry-id" id="index-read"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-read-8"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">read</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">target</var>, <var class="var">address</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-read-9"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">read</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">target</var>, <var class="var">address</var>, <var class="var">count</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-read-10"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">read</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">target</var>, <var class="var">address</var>, <var class="var">count</var>, <var class="var">serverId</var>, <var class="var">precision</var>)</code></dt>
<dd><p>Read data from modbus device <var class="var">dev</var> target <var class="var">target</var> starting at address <var class="var">address</var>.
</p>
<h4 class="subsubheading" id="Inputs-21">Inputs</h4>
<p><var class="var">dev</var> - connected modbus device
</p>
<p><var class="var">target</var> - target type to read. One of &rsquo;coils&rsquo;, &rsquo;inputs&rsquo;, &rsquo;inputregs&rsquo; or &rsquo;holdingregs&rsquo;
</p>
<p><var class="var">address</var> - address to start reading from.
</p>
<p><var class="var">count</var> - number of elements to read. If not provided, count is 1.
</p>
<p><var class="var">serverId</var> - address to send to (0-247). Default of 1 is used if not specified.
</p>
<p><var class="var">precision</var> - Optional precision for how to interpret the read data.
 Currently known precision values are uint16 (default), int16, uint32, int32, uint64, uint64, single, double.
</p>
<h4 class="subsubheading" id="Outputs-21">Outputs</h4>
<p><var class="var">data</var> - data read from the device
</p>
<p><strong class="strong">See also:</strong> modbus.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fmodbus_002fset">
<h4 class="subsection">3.5.4 @octave_modbus/set</h4>
<a class="index-entry-id" id="index-set-1"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-_0028obj_002c-2"><span class="category-def">Function File: </span><code class="def-type">set</code> <strong class="def-name">(<var class="var">obj</var>,</strong> <code class="def-code-arguments"><var class="var">property</var>,<var class="var">value</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-_0028obj_002c-3"><span class="category-def">Function File: </span><code class="def-type">set</code> <strong class="def-name">(<var class="var">obj</var>,</strong> <code class="def-code-arguments"><var class="var">property</var>,<var class="var">value</var>,&hellip;)</code></dt>
<dd><p>Set the properties of modbus object.
</p>
<h4 class="subsubheading" id="Inputs-22">Inputs</h4>
<p><var class="var">obj</var> - instance of <var class="var">octave_modbus</var> class.<br>
<var class="var">property</var> - name of property.<br>
</p>
<p>If <var class="var">property</var> is a cell so must be <var class="var">value</var>, it sets the values of
 all matching properties.
</p>
<p>The function also accepts property-value pairs.
</p>
<h4 class="subsubheading" id="Properties-2">Properties</h4>
<dl class="table">
<dt><var class="var">&rsquo;Name&rsquo;</var></dt>
<dd><p>Set the stored string name of the object.
</p>
</dd>
<dt><var class="var">&rsquo;Timeout&rsquo;</var></dt>
<dd><p>Set the timeout value.
</p>
</dd>
<dt><var class="var">&rsquo;Numretries&rsquo;</var></dt>
<dd><p>Set the numretries value.
</p>
</dd>
<dt><var class="var">&rsquo;ByteOrder&rsquo;</var></dt>
<dd><p>Set the byteorder value
</p>
</dd>
<dt><var class="var">&rsquo;WordOrder&rsquo;</var></dt>
<dd><p>Set the wordorder value
</p>
</dd>
<dt><var class="var">&rsquo;UserData&rsquo;</var></dt>
<dd><p>Set the userdata value
</p>
</dd>
</dl>
<h4 class="subsubheading" id="Outputs-22">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> @octave_modbus/get.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fmodbus_002fwrite">
<h4 class="subsection">3.5.5 @octave_modbus/write</h4>
<a class="index-entry-id" id="index-write"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-write-8"><span class="category-def">: </span><strong class="def-name">write</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">target</var>, <var class="var">address</var>, <var class="var">values</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-read-11"><span class="category-def">: </span><strong class="def-name">read</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">target</var>, <var class="var">address</var>, <var class="var">values</var>, <var class="var">serverId</var>, <var class="var">precision</var>)</code></dt>
<dd><p>Write data <var class="var">data</var> to modbus device <var class="var">dev</var> target <var class="var">target</var> starting at address <var class="var">address</var>.
</p>
<h4 class="subsubheading" id="Inputs-23">Inputs</h4>
<p><var class="var">dev</var> - connected modbus device
</p>
<p><var class="var">target</var> - target type to read. One of &rsquo;coils&rsquo; or &rsquo;holdingregs&rsquo;
</p>
<p><var class="var">address</var> - address to start reading from.
</p>
<p><var class="var">data</var> - data to write.
</p>
<p><var class="var">serverId</var> - address to send to (0-247). Default of 1 is used if not specified.
</p>
<p><var class="var">precision</var> - Optional precision for how to interpret the write data.
 Currently known precision values are uint16 (default), int16, uint32, int32, uint64, uint64, single, double.
</p>
<h4 class="subsubheading" id="Outputs-23">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> modbus.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fmodbus_002fwriteRead">
<h4 class="subsection">3.5.6 @octave_modbus/writeRead</h4>
<a class="index-entry-id" id="index-writeRead"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-writeRead-1"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">writeRead</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">writeAddress</var>, <var class="var">values</var>, <var class="var">readAddress</var>, <var class="var">readcount</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-writeRead-2"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">writeRead</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">writeAddress</var>, <var class="var">values</var>, <var class="var">readAddress</var>, <var class="var">readcount</var>, <var class="var">serverId</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-writeRead-3"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">writeRead</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">writeAddress</var>, <var class="var">values</var>, <var class="var">writePrecision</var>, <var class="var">readAddress</var>, <var class="var">readCount</var>, <var class="var">readPrecision</var>)</code></dt>
<dd><p>Write data <var class="var">values</var> to the modbus device <var class="var">dev</var> holding registers starting at address <var class="var">writeAddress</var>
 and then read <var class="var">readCount</var> register values starting at address <var class="var">readAddress</var>.
</p>
<h4 class="subsubheading" id="Inputs-24">Inputs</h4>
<p><var class="var">dev</var> - connected modbus device
</p>
<p><var class="var">writeAddress</var> - address to start writing to.
</p>
<p><var class="var">values</var> - data to write to the device.
</p>
<p><var class="var">readAddress</var> - address to start reading from.
</p>
<p><var class="var">readCount</var> - number of elements to read.
</p>
<p><var class="var">serverId</var> - address to send to (0-247). Default of 1 is used if not specified.
</p>
<p><var class="var">precision</var> - Optional precision for how to interpret the read data.
 Currently known precision values are uint16 (default), int16, uint32, int32, uint64, uint64, single, double.
</p>
<h4 class="subsubheading" id="Outputs-24">Outputs</h4>
<p><var class="var">data</var> - data read from the device
</p>
<p><strong class="strong">See also:</strong> modbus.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="modbus">
<h4 class="subsection">3.5.7 modbus</h4>
<a class="index-entry-id" id="index-modbus"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-modbus-1"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">dev</var> =</code> <strong class="def-name">modbus</strong> <code class="def-code-arguments">('tcpip', <var class="var">deviceaddress</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-modbus-2"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">dev</var> =</code> <strong class="def-name">modbus</strong> <code class="def-code-arguments">('tcpip', <var class="var">deviceaddress</var>, <var class="var">remoteport</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-modbus-3"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">dev</var> =</code> <strong class="def-name">modbus</strong> <code class="def-code-arguments">('tcpip', <var class="var">deviceaddress</var>, <var class="var">name</var>, <var class="var">value</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-modbus-4"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">dev</var> =</code> <strong class="def-name">modbus</strong> <code class="def-code-arguments">('serialrtu', <var class="var">serialport</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-modbus-5"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">dev</var> =</code> <strong class="def-name">modbus</strong> <code class="def-code-arguments">('serialrtu', <var class="var">serialport</var>, <var class="var">name</var>, <var class="var">value</var>)</code></dt>
<dd>
<p>Open modbus interface using a specified transport of &rsquo;tcpip&rsquo; or &rsquo;serialrtu&rsquo;.
</p>
<h4 class="subsubheading" id="Inputs-25">Inputs</h4>
<p><var class="var">deviceaddress</var> - the device ip address of type String.<br>
<var class="var">remoteport</var> - the device remote port number. If not specified, a default of 502 will be used.<br>
<var class="var">name</var>, <var class="var">value</var> - Optional name value pairs for setting properties of the object.<br>
<var class="var">serialport</var> - the name of the serial port to connect to. It must be specified when transport is &rsquo;serialrtu&rsquo;.<br>
</p>
<h4 class="subsubheading" id="Common-Input-Name_002c-Value-pairs">Common Input Name, Value pairs</h4>
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
<h4 class="subsubheading" id="Serial-RTU-Input-Name_002c-Value-pairs">Serial RTU Input Name, Value pairs</h4>
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
<h4 class="subsubheading" id="Outputs-25">Outputs</h4>
<p>The modbus() shall return instance of <var class="var">octave_modbus</var> class as the result <var class="var">modbus</var>.
</p>
<h4 class="subsubheading" id="Properties-3">Properties</h4>
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
<hr>
</div>
</div>
<div class="section-level-extent" id="Parallel">
<h3 class="section" id="Parallel-1">3.6 Parallel</h3>
<a class="index-entry-id" id="index-Parallel"></a>
<div class="subsection-level-extent" id="g_t_0040octave_005fparallel_002ffclose">
<h4 class="subsection">3.6.1 @octave_parallel/fclose</h4>
<a class="index-entry-id" id="index-fclose-2"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fclose-11"><span class="category-def">Function File: </span><code class="def-type"><var class="var">res</var> =</code> <strong class="def-name">fclose</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dd><p>Closes parallel connection <var class="var">obj</var>
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fparallel_002ffopen">
<h4 class="subsection">3.6.2 @octave_parallel/fopen</h4>
<a class="index-entry-id" id="index-fopen-2"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fopen-11"><span class="category-def">Function File: </span><code class="def-type"><var class="var">res</var> =</code> <strong class="def-name">fopen</strong> <code class="def-code-arguments">(<var class="var">obj</var>) (dummy)</code></dt>
<dd><p>Opens parallel interface <var class="var">obj</var>
</p>
<p>This currently is a dummy function to improve compatibility to MATLAB
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fparallel_002ffread">
<h4 class="subsection">3.6.3 @octave_parallel/fread</h4>
<a class="index-entry-id" id="index-fread-2"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fread-21"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-22"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-23"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>, <var class="var">precision</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-24"><span class="category-def">Function File: </span><code class="def-type">[<var class="var">data</var>,<var class="var">count</var>] =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, ...)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-25"><span class="category-def">Function File: </span><code class="def-type">[<var class="var">data</var>,<var class="var">count</var>,<var class="var">errmsg</var>] =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, ...)</code></dt>
<dd><p>Reads <var class="var">data</var> from parallel instrument
</p>
<h4 class="subsubheading" id="Inputs-26">Inputs</h4>
<p><var class="var">obj</var> is a parallel object.<br>
<var class="var">size</var> Number of values to read. (Default: 1).<br>
<var class="var">precision</var> precision of data.<br>
</p>
<h4 class="subsubheading" id="Outputs-26">Outputs</h4>
<p><var class="var">data</var> The read data.<br>
<var class="var">count</var> values read.<br>
<var class="var">errmsg</var> read operation error message.<br>
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fparallel_002ffwrite">
<h4 class="subsection">3.6.4 @octave_parallel/fwrite</h4>
<a class="index-entry-id" id="index-fwrite-2"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fwrite-17"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fwrite-18"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>, <var class="var">precision</var>)</code></dt>
<dd><p>Writes <var class="var">data</var> to parallel instrument
</p>
<h4 class="subsubheading" id="Inputs-27">Inputs</h4>
<p><var class="var">obj</var> is a parallel object.<br>
<var class="var">data</var> data to write.<br>
<var class="var">precision</var> precision of data.<br>
</p>
<h4 class="subsubheading" id="Outputs-27">Outputs</h4>
<p>returns number of bytes written.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="parallel">
<h4 class="subsection">3.6.5 parallel</h4>
<a class="index-entry-id" id="index-parallel"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-parallel-1"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">parallel</var> =</code> <strong class="def-name">parallel</strong> <code class="def-code-arguments">([<var class="var">path</var>], [<var class="var">direction</var>])</code></dt>
<dd>
<p>Open Parallel interface.
</p>
<h4 class="subsubheading" id="Inputs-28">Inputs</h4>
<p><var class="var">path</var> - the interface path of type String. If omitted defaults to &rsquo;/dev/parport0&rsquo;.<br>
<var class="var">direction</var> - the direction of interface drivers of type Integer, see: PP_DATADIR for more info.
If omitted defaults to 1 (Input).
</p>
<h4 class="subsubheading" id="Outputs-28">Outputs</h4>
<p>The parallel() shall return instance of <var class="var">octave_parallel</var> class as the result <var class="var">parallel</var>.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="pp_005fclose">
<h4 class="subsection">3.6.6 pp_close</h4>
<a class="index-entry-id" id="index-pp_005fclose"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-pp_005fclose-1"><span class="category-def">Loadable Function: </span><strong class="def-name">pp_close</strong> <code class="def-code-arguments">(<var class="var">parallel</var>)</code></dt>
<dd>
<p>Close the interface and release a file descriptor.
</p>
<h4 class="subsubheading" id="Inputs-29">Inputs</h4>
<p><var class="var">parallel</var> - instance of <var class="var">octave_serial</var> class.<br>
</p><h4 class="subsubheading" id="Outputs-29">Outputs</h4>
<p>None
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="pp_005fctrl">
<h4 class="subsection">3.6.7 pp_ctrl</h4>
<a class="index-entry-id" id="index-pp_005fctrl"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-pp_005fctrl-1"><span class="category-def">Loadable Function: </span><strong class="def-name">pp_ctrl</strong> <code class="def-code-arguments">(<var class="var">parallel</var>, <var class="var">ctrl</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-pp_005fctrl-2"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">c</var> =</code> <strong class="def-name">pp_ctrl</strong> <code class="def-code-arguments">(<var class="var">parallel</var>)</code></dt>
<dd>
<p>Sets or Read the Control lines.
</p>
<h4 class="subsubheading" id="Inputs-30">Inputs</h4>
<p><var class="var">parallel</var> - instance of <var class="var">octave_parallel</var> class.<br>
<var class="var">ctrl</var> - control parameter to be set of type Byte.
</p>
<h4 class="subsubheading" id="Outputs-30">Outputs</h4>
<p>If <var class="var">ctrl</var> parameter is omitted, the pp_ctrl() shall return current Control lines state as the result <var class="var">c</var>.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="pp_005fdata">
<h4 class="subsection">3.6.8 pp_data</h4>
<a class="index-entry-id" id="index-pp_005fdata"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-pp_005fdata-1"><span class="category-def">Loadable Function: </span><strong class="def-name">pp_data</strong> <code class="def-code-arguments">(<var class="var">parallel</var>, <var class="var">data</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-pp_005fdata-2"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">d</var> =</code> <strong class="def-name">pp_data</strong> <code class="def-code-arguments">(<var class="var">parallel</var>)</code></dt>
<dd>
<p>Sets or Read the Data lines.
</p>
<h4 class="subsubheading" id="Inputs-31">Inputs</h4>
<p><var class="var">parallel</var> - instance of <var class="var">octave_parallel</var> class.<br>
<var class="var">data</var> - data parameter to be set of type Byte.
</p>
<h4 class="subsubheading" id="Outputs-31">Outputs</h4>
<p>If <var class="var">data</var> parameter is omitted, the pp_data() shall return current Data lines state as the result <var class="var">d</var>.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="pp_005fdatadir">
<h4 class="subsection">3.6.9 pp_datadir</h4>
<a class="index-entry-id" id="index-pp_005fdatadir"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-pp_005fdatadir-1"><span class="category-def">Loadable Function: </span><strong class="def-name">pp_datadir</strong> <code class="def-code-arguments">(<var class="var">parallel</var>, <var class="var">direction</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-pp_005fdatadir-2"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">dir</var> =</code> <strong class="def-name">pp_datadir</strong> <code class="def-code-arguments">(<var class="var">parallel</var>)</code></dt>
<dd>
<p>Controls the Data line drivers.
</p>
<p>Normally the computer&rsquo;s parallel port will drive the data lines,
but for byte-wide transfers from the peripheral to the host it is useful to turn off those drivers
and let the peripheral drive the signals. (If the drivers on the computer&rsquo;s parallel port are left
on when this happens, the port might be damaged.)
</p>
<h4 class="subsubheading" id="Inputs-32">Inputs</h4>
<p><var class="var">parallel</var> - instance of <var class="var">octave_parallel</var> class.<br>
<var class="var">direction</var> - direction parameter of type Integer. Supported values: 0 - the drivers are turned on
(Output/Forward direction); 1 - the drivers are turned off (Input/Reverse direction).
</p>
<h4 class="subsubheading" id="Outputs-32">Outputs</h4>
<p>If <var class="var">direction</var> parameter is omitted, the pp_datadir() shall return current Data direction as the result <var class="var">dir</var>.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="pp_005fstat">
<h4 class="subsection">3.6.10 pp_stat</h4>
<a class="index-entry-id" id="index-pp_005fstat"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-pp_005fstat-1"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">stat</var> =</code> <strong class="def-name">pp_stat</strong> <code class="def-code-arguments">(<var class="var">parallel</var>)</code></dt>
<dd>
<p>Reads the Status lines.
</p>
<h4 class="subsubheading" id="Inputs-33">Inputs</h4>
<p><var class="var">parallel</var> - instance of <var class="var">octave_parallel</var> class.<br>
</p>
<h4 class="subsubheading" id="Outputs-33">Outputs</h4>
<p>The pp_stat() shall return current Status lines state as the result <var class="var">stat</var>.
</p></dd></dl>
<hr>
</div>
</div>
<div class="section-level-extent" id="Serial-_0028Deprecated_0029">
<h3 class="section" id="Serial-_0028Deprecated_0029-1">3.7 Serial (Deprecated)</h3>
<a class="index-entry-id" id="index-Serial-_0028Deprecated_0029"></a>
<div class="subsection-level-extent" id="g_t_0040octave_005fserial_002ffclose">
<h4 class="subsection">3.7.1 @octave_serial/fclose</h4>
<a class="index-entry-id" id="index-fclose-3"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fclose-12"><span class="category-def">Function File: </span><code class="def-type"><var class="var">res</var> =</code> <strong class="def-name">fclose</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dd><p>Closes SERIAL connection <var class="var">obj</var>
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserial_002fflushinput">
<h4 class="subsection">3.7.2 @octave_serial/flushinput</h4>
<a class="index-entry-id" id="index-flushinput-1"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-flushinput-5"><span class="category-def">Loadable Function: </span><strong class="def-name">flushinput</strong> <code class="def-code-arguments">(<var class="var">serial</var>)</code></dt>
<dd>
<p>Flush the pending input, which will also make the BytesAvailable property be 0.
</p>
<h4 class="subsubheading" id="Inputs-34">Inputs</h4>
<p><var class="var">serial</var> - instance of <var class="var">octave_serial</var> class.
</p>
<h4 class="subsubheading" id="Outputs-34">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> srl_flush, flushoutput.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserial_002fflushoutput">
<h4 class="subsection">3.7.3 @octave_serial/flushoutput</h4>
<a class="index-entry-id" id="index-flushoutput-1"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-flushoutput-5"><span class="category-def">Loadable Function: </span><strong class="def-name">flushoutput</strong> <code class="def-code-arguments">(<var class="var">serial</var>)</code></dt>
<dd>
<p>Flush the output buffer.
</p>
<h4 class="subsubheading" id="Inputs-35">Inputs</h4>
<p><var class="var">serial</var> - instance of <var class="var">octave_serial</var> class.
</p>
<h4 class="subsubheading" id="Outputs-35">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> srl_flush, flushinput.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserial_002ffopen">
<h4 class="subsection">3.7.4 @octave_serial/fopen</h4>
<a class="index-entry-id" id="index-fopen-3"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fopen-12"><span class="category-def">Function File: </span><code class="def-type"><var class="var">res</var> =</code> <strong class="def-name">fopen</strong> <code class="def-code-arguments">(<var class="var">obj</var>) (dummy)</code></dt>
<dd><p>Opens SERIAL interface <var class="var">obj</var>
</p>
<p>This currently is a dummy function to improve compatibility to MATLAB
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserial_002ffprintf">
<h4 class="subsection">3.7.5 @octave_serial/fprintf</h4>
<a class="index-entry-id" id="index-fprintf-1"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fprintf-10"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fprintf</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">template</var> ...)</code></dt>
<dd><p>Writes formatted string <var class="var">template</var> using optional parameters to
 serial instrument
</p>
<h4 class="subsubheading" id="Inputs-36">Inputs</h4>
<p><var class="var">obj</var> is a serial object.<br>
<var class="var">template</var> Format template string
</p>
<h4 class="subsubheading" id="Outputs-36">Outputs</h4>
<p><var class="var">numbytes</var> - number of bytes written to the serial device.
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserial_002ffread">
<h4 class="subsection">3.7.6 @octave_serial/fread</h4>
<a class="index-entry-id" id="index-fread-3"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fread-26"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-27"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-28"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>, <var class="var">precision</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-29"><span class="category-def">Function File: </span><code class="def-type">[<var class="var">data</var>,<var class="var">count</var>] =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, ...)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-30"><span class="category-def">Function File: </span><code class="def-type">[<var class="var">data</var>,<var class="var">count</var>,<var class="var">errmsg</var>] =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, ...)</code></dt>
<dd><p>Reads <var class="var">data</var> from serial instrument
</p>
<h4 class="subsubheading" id="Inputs-37">Inputs</h4>
<p><var class="var">obj</var> is a serial object.<br>
<var class="var">size</var> Number of values to read. (Default: 100).<br>
<var class="var">precision</var> precision of data.<br>
</p>
<h4 class="subsubheading" id="Outputs-37">Outputs</h4>
<p><var class="var">data</var> The read data.<br>
<var class="var">count</var> values read.<br>
<var class="var">errmsg</var> read operation error message.<br>
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserial_002ffwrite">
<h4 class="subsection">3.7.7 @octave_serial/fwrite</h4>
<a class="index-entry-id" id="index-fwrite-3"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fwrite-19"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fwrite-20"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>, <var class="var">precision</var>)</code></dt>
<dd><p>Writes <var class="var">data</var> to serial instrument
</p>
<h4 class="subsubheading" id="Inputs-38">Inputs</h4>
<p><var class="var">obj</var> is a serial object.<br>
<var class="var">data</var> data to write.<br>
<var class="var">precision</var> precision of data.<br>
</p>
<h4 class="subsubheading" id="Outputs-38">Outputs</h4>
<p>returns number of bytes written.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserial_002fget">
<h4 class="subsection">3.7.8 @octave_serial/get</h4>
<a class="index-entry-id" id="index-get-2"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-get-14"><span class="category-def">Function File: </span><code class="def-type"><var class="var">struct</var> =</code> <strong class="def-name">get</strong> <code class="def-code-arguments">(<var class="var">serial</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-get-15"><span class="category-def">Function File: </span><code class="def-type"><var class="var">field</var> =</code> <strong class="def-name">get</strong> <code class="def-code-arguments">(<var class="var">serial</var>, <var class="var">property</var>)</code></dt>
<dd><p>Get the properties of serial object.
</p>
<h4 class="subsubheading" id="Inputs-39">Inputs</h4>
<p><var class="var">serial</var> - instance of <var class="var">octave_serial</var> class.<br>
<var class="var">property</var> - name of property.<br>
</p>
<h4 class="subsubheading" id="Outputs-39">Outputs</h4>
<p>When <var class="var">property</var> was specified, return the value of that property.<br>
 otherwise return the values of all properties as a structure.<br>
</p>
<p><strong class="strong">See also:</strong> @octave_serial/set.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserial_002fserialbreak">
<h4 class="subsection">3.7.9 @octave_serial/serialbreak</h4>
<a class="index-entry-id" id="index-serialbreak"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-serialbreak-2"><span class="category-def">Function File: </span><strong class="def-name">serialbreak</strong> <code class="def-code-arguments">(<var class="var">serial</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-serialbreak-3"><span class="category-def">Function File: </span><strong class="def-name">serialbreak</strong> <code class="def-code-arguments">(<var class="var">serial</var>, <var class="var">time</var>)</code></dt>
<dd><p>Send a break to the serial port
</p>
<h4 class="subsubheading" id="Inputs-40">Inputs</h4>
<p><var class="var">serial</var> - serial object<br>
<var class="var">time</var> - number of milliseconds to break for. If not specified a value of 10 will be used.
</p>
<h4 class="subsubheading" id="Outputs-40">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> serial.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserial_002fset">
<h4 class="subsection">3.7.10 @octave_serial/set</h4>
<a class="index-entry-id" id="index-set-2"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-_0028obj_002c-4"><span class="category-def">Function File: </span><code class="def-type">set</code> <strong class="def-name">(<var class="var">obj</var>,</strong> <code class="def-code-arguments"><var class="var">property</var>,<var class="var">value</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-_0028obj_002c-5"><span class="category-def">Function File: </span><code class="def-type">set</code> <strong class="def-name">(<var class="var">obj</var>,</strong> <code class="def-code-arguments"><var class="var">property</var>,<var class="var">value</var>,&hellip;)</code></dt>
<dd><p>Set the properties of serial object.
</p>
<h4 class="subsubheading" id="Inputs-41">Inputs</h4>
<p><var class="var">serial</var> - instance of <var class="var">octave_serial</var> class.<br>
<var class="var">property</var> - name of property.<br>
</p>
<p>If <var class="var">property</var> is a cell so must be <var class="var">value</var>, it sets the values of
 all matching properties.
</p>
<p>The function also accepts property-value pairs.
</p>
<h4 class="subsubheading" id="Properties-4">Properties</h4>
<dl class="table">
<dt><var class="var">&rsquo;baudrate&rsquo;</var></dt>
<dd><p>Set the baudrate of serial port. Supported values by instrument-control:
 0, 50, 75, 110, 134, 150, 200, 300, 600, 1200, 1800, 2400, 4800, 9600,
 19200, 38400, 57600, 115200 and 230400. The supported baudrate of your
 serial port may be different.
</p>
</dd>
<dt><var class="var">&rsquo;bytesize&rsquo;</var></dt>
<dd><p>Set the bytesize. Supported values: 5, 6, 7 and 8.
</p>
</dd>
<dt><var class="var">&rsquo;name&rsquo;</var></dt>
<dd><p>Set the stored string name of the serial object.
</p>
</dd>
<dt><var class="var">&rsquo;parity&rsquo;</var></dt>
<dd><p>Set the parity value. Supported values: Even/Odd/None. This Parameter
 must be of type string. It is case insensitive and can be abbreviated
 to the first letter only
</p>
</dd>
<dt><var class="var">&rsquo;stopbits&rsquo;</var></dt>
<dd><p>Set the number of stopbits. Supported values: 1, 2.
</p>
</dd>
<dt><var class="var">&rsquo;timeout&rsquo;</var></dt>
<dd><p>Set the timeout value in tenths of a second. Value of -1 means a
 blocking call. Maximum value of 255 (i.e. 25.5 seconds).
</p>
</dd>
<dt><var class="var">&rsquo;requesttosend&rsquo;</var></dt>
<dd><p>Set the requesttosend (RTS) line.
</p>
</dd>
<dt><var class="var">&rsquo;dataterminalready&rsquo;</var></dt>
<dd><p>Set the dataterminalready (DTR) line.
</p>
</dd>
</dl>
<h4 class="subsubheading" id="Outputs-41">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> @octave_serial/get.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserial_002fsrl_005fbaudrate">
<h4 class="subsection">3.7.11 @octave_serial/srl_baudrate</h4>
<a class="index-entry-id" id="index-srl_005fbaudrate"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-srl_005fbaudrate-1"><span class="category-def">Loadable Function: </span><strong class="def-name">srl_baudrate</strong> <code class="def-code-arguments">(<var class="var">serial</var>, <var class="var">baudrate</var>)\</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-srl_005fbaudrate-2"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">br</var> =</code> <strong class="def-name">srl_baudrate</strong> <code class="def-code-arguments">(<var class="var">serial</var>)</code></dt>
<dd>
<p>Set new or get existing serial interface baudrate parameter. Only standard values are supported.
</p>
<h4 class="subsubheading" id="Inputs-42">Inputs</h4>
<p><var class="var">serial</var> - instance of <var class="var">octave_serial</var> class.<br>
<var class="var">baudrate</var> - the baudrate value used. Supported values: 0, 50, 75, 110, 134, 150, 200, 300, 600, 1200, 1800, 2400, 4800, 9600 19200, 38400, 57600, 115200 and 230400.<br>
</p>
<p>If <var class="var">baudrate</var> parameter is omitted, the srl_baudrate() shall return current baudrate value as the result <var class="var">br</var>.
</p>
<h4 class="subsubheading" id="Outputs-42">Outputs</h4>
<p><var class="var">br</var> - The currently set baudrate
</p>
<p>This function is obsolete. Use get and set method instead.
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserial_002fsrl_005fbytesize">
<h4 class="subsection">3.7.12 @octave_serial/srl_bytesize</h4>
<a class="index-entry-id" id="index-srl_005fbytesize"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-srl_005fbytesize-1"><span class="category-def">Loadable Function: </span><strong class="def-name">srl_bytesize</strong> <code class="def-code-arguments">(<var class="var">serial</var>, <var class="var">bsize</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-srl_005fbytesize-2"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">bs</var> =</code> <strong class="def-name">srl_bytesize</strong> <code class="def-code-arguments">(<var class="var">serial</var>)</code></dt>
<dd>
<p>Set new or get existing serial interface byte size parameter.
</p>
<h4 class="subsubheading" id="Inputs-43">Inputs</h4>
<p><var class="var">serial</var> - instance of <var class="var">octave_serial</var> class.<br>
<var class="var">bsize</var> - byte size of type Integer. Supported values: 5/6/7/8.<br>
</p>
<p>If <var class="var">bsize</var> parameter is omitted, the srl_bytesize() shall return current byte size value
 or in case of unsupported setting -1, as the result <var class="var">bs</var>.
</p>
<p>This function is obsolete. Use get and set method instead.
</p>
<h4 class="subsubheading" id="Outputs-43">Outputs</h4>
<p><var class="var">bs</var> -the currently set  byte size.
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserial_002fsrl_005fclose">
<h4 class="subsection">3.7.13 @octave_serial/srl_close</h4>
<a class="index-entry-id" id="index-srl_005fclose"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-srl_005fclose-1"><span class="category-def">Loadable Function: </span><strong class="def-name">srl_close</strong> <code class="def-code-arguments">(<var class="var">serial</var>)</code></dt>
<dd>
<p>Close the interface and release a file descriptor.
</p>
<h4 class="subsubheading" id="Inputs-44">Inputs</h4>
<p><var class="var">serial</var> - instance of <var class="var">octave_serial</var> class.
</p>
<p>This function is obsolete. Use fclose() method instead.
</p>
<h4 class="subsubheading" id="Outputs-44">Outputs</h4>
<p>None
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserial_002fsrl_005fflush">
<h4 class="subsection">3.7.14 @octave_serial/srl_flush</h4>
<a class="index-entry-id" id="index-srl_005fflush"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-srl_005fflush-1"><span class="category-def">Loadable Function: </span><strong class="def-name">srl_flush</strong> <code class="def-code-arguments">(<var class="var">serial</var>, [<var class="var">q</var>])</code></dt>
<dd>
<p>Flush the pending input/output.
</p>
<h4 class="subsubheading" id="Inputs-45">Inputs</h4>
<p><var class="var">serial</var> - instance of <var class="var">octave_serial</var> class.<br>
<var class="var">q</var> - queue selector of type Integer. Supported values:<br>
</p><dl class="table">
<dt>0</dt>
<dd><p>flush untransmitted output
</p></dd>
<dt>1</dt>
<dd><p>flush pending input
</p></dd>
<dt>2</dt>
<dd><p>flush both pending input and untransmitted output.
</p></dd>
</dl>
<p>If <var class="var">q</var> parameter is omitted, the srl_flush() shall flush both, input and output buffers.
</p>
<h4 class="subsubheading" id="Outputs-45">Outputs</h4>
<p>None
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserial_002fsrl_005fparity">
<h4 class="subsection">3.7.15 @octave_serial/srl_parity</h4>
<a class="index-entry-id" id="index-srl_005fparity"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-srl_005fparity-1"><span class="category-def">Loadable Function: </span><strong class="def-name">srl_parity</strong> <code class="def-code-arguments">(<var class="var">serial</var>, <var class="var">parity</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-srl_005fparity-2"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">p</var> =</code> <strong class="def-name">srl_parity</strong> <code class="def-code-arguments">(<var class="var">serial</var>)</code></dt>
<dd>
<p>Set new or get existing serial interface parity parameter. Even/Odd/None values are supported.
</p>
<h4 class="subsubheading" id="Inputs-46">Inputs</h4>
<p><var class="var">serial</var> - instance of <var class="var">octave_serial</var> class.<br>
<var class="var">parity</var> - parity value of type String. Supported values:
 Even/Odd/None (case insensitive, can be abbreviated to the first letter only)<br>
</p>
<p>If <var class="var">parity</var> parameter is omitted, the srl_parity() shall return current parity value as the result <var class="var">p</var>.
</p>
<p>This function is obsolete. Use get and set method instead.
</p>
<h4 class="subsubheading" id="Outputs-46">Outputs</h4>
<p><var class="var">p</var> - The currently set parity
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserial_002fsrl_005fstopbits">
<h4 class="subsection">3.7.16 @octave_serial/srl_stopbits</h4>
<a class="index-entry-id" id="index-srl_005fstopbits"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-srl_005fstopbits-1"><span class="category-def">Loadable Function: </span><strong class="def-name">srl_stopbits</strong> <code class="def-code-arguments">(<var class="var">serial</var>, <var class="var">stopb</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-srl_005fstopbits-2"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">sb</var> =</code> <strong class="def-name">srl_stopbits</strong> <code class="def-code-arguments">(<var class="var">serial</var>)</code></dt>
<dd>
<p>Set new or get existing serial interface stop bits parameter. Only 1 or 2 stop bits are supported.
</p>
<h4 class="subsubheading" id="Inputs-47">Inputs</h4>
<p><var class="var">serial</var> - instance of <var class="var">octave_serial</var> class.<br>
<var class="var">stopb</var> - number of stop bits used. Supported values: 1, 2.<br>
</p>
<h4 class="subsubheading" id="Outputs-47">Outputs</h4>
<p>If <var class="var">stopb</var> parameter is omitted, the srl_stopbits() shall return current stop bits value as the result <var class="var">sb</var>.
</p>
<p>This function is obsolete. Use get and set method instead.
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserial_002fsrl_005ftimeout">
<h4 class="subsection">3.7.17 @octave_serial/srl_timeout</h4>
<a class="index-entry-id" id="index-srl_005ftimeout"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-srl_005ftimeout-1"><span class="category-def">Loadable Function: </span><strong class="def-name">srl_timeout</strong> <code class="def-code-arguments">(<var class="var">serial</var>, <var class="var">timeout</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-srl_005ftimeout-2"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">t</var> =</code> <strong class="def-name">srl_timeout</strong> <code class="def-code-arguments">(<var class="var">serial</var>)</code></dt>
<dd>
<p>Set new or get existing serial interface timeout parameter used for srl_read() requests. The timeout value is specified in tenths of a second.
</p>
<h4 class="subsubheading" id="Inputs-48">Inputs</h4>
<p><var class="var">serial</var> - instance of <var class="var">octave_serial</var> class.<br>
<var class="var">timeout</var> - srl_read() timeout value in tenths of a second.
 A value of -1 means a blocking call. Maximum value of 255 (i.e. 25.5 seconds).<br>
</p>
<h4 class="subsubheading" id="Outputs-48">Outputs</h4>
<p>If <var class="var">timeout</var> parameter is omitted, the srl_timeout() shall return current timeout value as the result <var class="var">t</var>.
</p>
<p>This function is obsolete. Use get and set method instead.
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="serial">
<h4 class="subsection">3.7.18 serial</h4>
<a class="index-entry-id" id="index-serial"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-serial-1"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">serial</var> =</code> <strong class="def-name">serial</strong> <code class="def-code-arguments">([<var class="var">path</var>], [<var class="var">baudrate</var>], [<var class="var">timeout</var>])</code></dt>
<dd>
<p>Open serial interface.
</p>
<h4 class="subsubheading" id="Inputs-49">Inputs</h4>
<p><var class="var">path</var> - the interface path of type String. <br>
<var class="var">baudrate</var> - the baudrate of interface. If omitted defaults to 115200. <br>
<var class="var">timeout</var> - the interface timeout value. If omitted defaults to blocking call.
</p>
<h4 class="subsubheading" id="Outputs-49">Outputs</h4>
<p>The serial() shall return an instance of <var class="var">octave_serial</var> class as the result <var class="var">serial</var>.
</p><h4 class="subsubheading" id="Properties-5">Properties</h4>
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
</div>
<div class="subsection-level-extent" id="seriallist">
<h4 class="subsection">3.7.19 seriallist</h4>
<a class="index-entry-id" id="index-seriallist"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-seriallist-1"><span class="category-def">Function File: </span><code class="def-type"><var class="var">list</var> =</code> <strong class="def-name">seriallist</strong> <code class="def-code-arguments">()</code></dt>
<dd><p>Returns a list of all serial ports detected in the system.
</p>
<h4 class="subsubheading" id="Inputs-50">Inputs</h4>
<p>None
</p>
<h4 class="subsubheading" id="Outputs-50">Outputs</h4>
<p><var class="var">list</var> is a string cell array of serial ports names detected
 in the system.
</p>
<p><strong class="strong">See also:</strong> instrhwinfo(&quot;serial&quot;).
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="srl_005fread">
<h4 class="subsection">3.7.20 srl_read</h4>
<a class="index-entry-id" id="index-srl_005fread"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-srl_005fread-1"><span class="category-def">Loadable Function: </span><code class="def-type">[<var class="var">data</var>, <var class="var">count</var>] =</code> <strong class="def-name">srl_read</strong> <code class="def-code-arguments">(<var class="var">serial</var>, <var class="var">n</var>)</code></dt>
<dd>
<p>Read from serial interface.
</p>
<h4 class="subsubheading" id="Inputs-51">Inputs</h4>
<p><var class="var">serial</var> - instance of <var class="var">octave_serial</var> class.<br>
<var class="var">n</var> - number of bytes to attempt to read of type Integer.
</p>
<h4 class="subsubheading" id="Outputs-51">Outputs</h4>
<p>The srl_read() shall return number of bytes successfully read in <var class="var">count</var> as Integer and the bytes themselves in <var class="var">data</var> as uint8 array.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="srl_005fwrite">
<h4 class="subsection">3.7.21 srl_write</h4>
<a class="index-entry-id" id="index-srl_005fwrite"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-srl_005fwrite-1"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">n</var> =</code> <strong class="def-name">srl_write</strong> <code class="def-code-arguments">(<var class="var">serial</var>, <var class="var">data</var>)</code></dt>
<dd>
<p>Write data to a serial interface.
</p>
<h4 class="subsubheading" id="Inputs-52">Inputs</h4>
<p><var class="var">serial</var> - instance of <var class="var">octave_serial</var> class.<br>
<var class="var">data</var> - data to be written to the serial interface. Can be either of String or uint8 type.
</p>
<h4 class="subsubheading" id="Outputs-52">Outputs</h4>
<p>Upon successful completion, srl_write() shall return the number of bytes written as the result <var class="var">n</var>.
</p></dd></dl>
<hr>
</div>
</div>
<div class="section-level-extent" id="Serial-Port">
<h3 class="section" id="Serial-Port-1">3.8 Serial Port</h3>
<a class="index-entry-id" id="index-Serial-Port"></a>
<div class="subsection-level-extent" id="g_t_0040octave_005fserialport_002fconfigureTerminator">
<h4 class="subsection">3.8.1 @octave_serialport/configureTerminator</h4>
<a class="index-entry-id" id="index-configureTerminator"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-configureTerminator-4"><span class="category-def">Function File: </span><strong class="def-name">configureTerminator</strong> <code class="def-code-arguments">(<var class="var">serial</var>, <var class="var">term</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-configureTerminator-5"><span class="category-def">Function File: </span><strong class="def-name">configureTerminator</strong> <code class="def-code-arguments">(<var class="var">serial</var>, <var class="var">readterm</var>, <var class="var">writeterm</var>)</code></dt>
<dd><p>Set terminator for ASCII string manipulation
</p>
<h4 class="subsubheading" id="Inputs-53">Inputs</h4>
<p><var class="var">serial</var> - serialport object<br>
<var class="var">term</var> - terminal value for both read and write<br>
<var class="var">readterm</var> = terminal value type for read data<br>
<var class="var">writeterm</var> = terminal value for written data<br>
</p>
<p>The terminal can be either strings &quot;cr&quot;, &quot;lf&quot; (default), &quot;lf/cr&quot; or an integer between 0 to 255.
</p>
<h4 class="subsubheading" id="Outputs-53">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> serialport.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserialport_002fflush">
<h4 class="subsection">3.8.2 @octave_serialport/flush</h4>
<a class="index-entry-id" id="index-flush"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-flush-6"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">flush</strong> <code class="def-code-arguments">(<var class="var">dev</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-flush-7"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">flush</strong> <code class="def-code-arguments">(<var class="var">dev</var>, &quot;input&quot;)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-flush-8"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">flush</strong> <code class="def-code-arguments">(<var class="var">dev</var>, &quot;output&quot;)</code></dt>
<dd><p>Flush the serial port buffers
</p>
<h4 class="subsubheading" id="Inputs-54">Inputs</h4>
<p><var class="var">dev</var> - connected serialport device
</p>
<p>If an additional parameter is provided of &quot;input&quot; or &quot;output&quot;,
 then only the input or output buffer will be flushed
</p>
<h4 class="subsubheading" id="Outputs-54">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> serialport.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserialport_002ffprintf">
<h4 class="subsection">3.8.3 @octave_serialport/fprintf</h4>
<a class="index-entry-id" id="index-fprintf-2"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fprintf-11"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fprintf</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">template</var> ...)</code></dt>
<dd><p>Writes formatted string <var class="var">template</var> using optional parameters to
 serialport instrument
</p>
<h4 class="subsubheading" id="Inputs-55">Inputs</h4>
<p><var class="var">obj</var> is a serialport object.<br>
<var class="var">template</var> Format template string
</p>
<h4 class="subsubheading" id="Outputs-55">Outputs</h4>
<p><var class="var">numbytes</var> - number of bytes written to the serial device.
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserialport_002ffread">
<h4 class="subsection">3.8.4 @octave_serialport/fread</h4>
<a class="index-entry-id" id="index-fread-4"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fread-31"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-32"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-33"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>, <var class="var">precision</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-34"><span class="category-def">Function File: </span><code class="def-type">[<var class="var">data</var>,<var class="var">count</var>] =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, ...)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-35"><span class="category-def">Function File: </span><code class="def-type">[<var class="var">data</var>,<var class="var">count</var>,<var class="var">errmsg</var>] =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, ...)</code></dt>
<dd><p>Reads <var class="var">data</var> from serial port instrument
</p>
<h4 class="subsubheading" id="Inputs-56">Inputs</h4>
<p><var class="var">obj</var> is a serialport object.<br>
<var class="var">size</var> Number of values to read.<br>
<var class="var">precision</var> precision of data.<br>
</p>
<h4 class="subsubheading" id="Outputs-56">Outputs</h4>
<p><var class="var">data</var> The read data.<br>
<var class="var">count</var> number of values read.<br>
<var class="var">errmsg</var> read operation error message.<br>
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserialport_002ffwrite">
<h4 class="subsection">3.8.5 @octave_serialport/fwrite</h4>
<a class="index-entry-id" id="index-fwrite-4"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fwrite-21"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fwrite-22"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>, <var class="var">precision</var>)</code></dt>
<dd><p>Writes <var class="var">data</var> to serial port instrument
</p>
<h4 class="subsubheading" id="Inputs-57">Inputs</h4>
<p><var class="var">obj</var> is a serial port object.<br>
<var class="var">data</var> data to write.<br>
<var class="var">precision</var> precision of data.<br>
</p>
<h4 class="subsubheading" id="Outputs-57">Outputs</h4>
<p>returns number of bytes written.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserialport_002fget">
<h4 class="subsection">3.8.6 @octave_serialport/get</h4>
<a class="index-entry-id" id="index-get-3"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-get-16"><span class="category-def">Function File: </span><code class="def-type"><var class="var">struct</var> =</code> <strong class="def-name">get</strong> <code class="def-code-arguments">(<var class="var">serial</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-get-17"><span class="category-def">Function File: </span><code class="def-type"><var class="var">field</var> =</code> <strong class="def-name">get</strong> <code class="def-code-arguments">(<var class="var">serial</var>, <var class="var">property</var>)</code></dt>
<dd><p>Get the properties of serialport object.
</p>
<h4 class="subsubheading" id="Inputs-58">Inputs</h4>
<p><var class="var">serial</var> - instance of <var class="var">octave_serialport</var> class.<br>
<var class="var">property</var> - name of property.<br>
</p>
<h4 class="subsubheading" id="Outputs-58">Outputs</h4>
<p>When <var class="var">property</var> was specified, return the value of that property.<br>
 otherwise return the values of all properties as a structure.<br>
</p>
<p><strong class="strong">See also:</strong> @octave_serial/set.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserialport_002fgetpinstatus">
<h4 class="subsection">3.8.7 @octave_serialport/getpinstatus</h4>
<a class="index-entry-id" id="index-getpinstatus"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-getpinstatus-1"><span class="category-def">Function File: </span><code class="def-type"><var class="var">status</var></code> <strong class="def-name">getpinstatus</strong> <code class="def-code-arguments">(<var class="var">serial</var>)</code></dt>
<dd><p>Get status of serial pins
</p>
<h4 class="subsubheading" id="Inputs-59">Inputs</h4>
<p><var class="var">serial</var> - serial object<br>
</p>
<h4 class="subsubheading" id="Outputs-59">Outputs</h4>
<p><var class="var">status</var> - a structure with the logic names of ClearToSend, DataSetReady, CarrierDetect, and RingIndicator
</p>
<p><strong class="strong">See also:</strong> serialport.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserialport_002fread">
<h4 class="subsection">3.8.8 @octave_serialport/read</h4>
<a class="index-entry-id" id="index-read-1"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-read-12"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">read</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">count</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-read-13"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">read</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">count</var>, <var class="var">precision</var>)</code></dt>
<dd><p>Read a specified number of values from a serialport
 using optional precision for valuesize.
</p>
<h4 class="subsubheading" id="Inputs-60">Inputs</h4>
<p><var class="var">dev</var> - connected serialport device
</p>
<p><var class="var">count</var> - number of elements to read
</p>
<p><var class="var">precision</var> - Optional precision for the output data read data.
 Currently known precision values are uint8 (default), int8, uint16, int16, uint32, int32, uint64, uint64
</p>
<h4 class="subsubheading" id="Outputs-60">Outputs</h4>
<p><var class="var">data</var> - data read from the device
</p>
<p><strong class="strong">See also:</strong> serialport.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserialport_002fserialbreak">
<h4 class="subsection">3.8.9 @octave_serialport/serialbreak</h4>
<a class="index-entry-id" id="index-serialbreak-1"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-serialbreak-4"><span class="category-def">Function File: </span><strong class="def-name">serialbreak</strong> <code class="def-code-arguments">(<var class="var">serial</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-serialbreak-5"><span class="category-def">Function File: </span><strong class="def-name">serialbreak</strong> <code class="def-code-arguments">(<var class="var">serial</var>, <var class="var">time</var>)</code></dt>
<dd><p>Send a break to the serial port
</p>
<h4 class="subsubheading" id="Inputs-61">Inputs</h4>
<p><var class="var">serial</var> - serialport object<br>
<var class="var">time</var> - number of milliseconds to break for. If not specified a value of 10 will be used.
</p>
<h4 class="subsubheading" id="Outputs-61">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> serial.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserialport_002fset">
<h4 class="subsection">3.8.10 @octave_serialport/set</h4>
<a class="index-entry-id" id="index-set-3"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-_0028obj_002c-6"><span class="category-def">Function File: </span><code class="def-type">set</code> <strong class="def-name">(<var class="var">obj</var>,</strong> <code class="def-code-arguments"><var class="var">property</var>,<var class="var">value</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-_0028obj_002c-7"><span class="category-def">Function File: </span><code class="def-type">set</code> <strong class="def-name">(<var class="var">obj</var>,</strong> <code class="def-code-arguments"><var class="var">property</var>,<var class="var">value</var>,&hellip;)</code></dt>
<dd><p>Set the properties of serialport object.
</p>
<h4 class="subsubheading" id="Inputs-62">Inputs</h4>
<p><var class="var">serial</var> - instance of <var class="var">octave_serialport</var> class.<br>
<var class="var">property</var> - name of property.<br>
</p>
<p>If <var class="var">property</var> is a cell so must be <var class="var">value</var>, it sets the values of
 all matching properties.
</p>
<p>The function also accepts property-value pairs.
</p>
<h4 class="subsubheading" id="Properties-6">Properties</h4>
<dl class="table">
<dt><var class="var">&rsquo;baudrate&rsquo;</var></dt>
<dd><p>Set the baudrate of serial port. Supported values by instrument-control:
 0, 50, 75, 110, 134, 150, 200, 300, 600, 1200, 1800, 2400, 4800, 9600,
 19200, 38400, 57600, 115200 and 230400. The supported baudrate of your
 serial port may be different.
</p>
</dd>
<dt><var class="var">&rsquo;bytesize&rsquo;</var></dt>
<dd><p>Set the bytesize. Supported values: 5, 6, 7 and 8.
</p>
</dd>
<dt><var class="var">&rsquo;name&rsquo;</var></dt>
<dd><p>Set the stored string name of the serial object.
</p>
</dd>
<dt><var class="var">&rsquo;parity&rsquo;</var></dt>
<dd><p>Set the parity value. Supported values: Even/Odd/None. This Parameter
 must be of type string. It is case insensitive and can be abbreviated
 to the first letter only
</p>
</dd>
<dt><var class="var">&rsquo;stopbits&rsquo;</var></dt>
<dd><p>Set the number of stopbits. Supported values: 1, 2.
</p>
</dd>
<dt><var class="var">&rsquo;timeout&rsquo;</var></dt>
<dd><p>Set the timeout value in tenths of a second. Value of -1 means a
 blocking call. Maximum value of 255 (i.e. 25.5 seconds).
</p>
</dd>
<dt><var class="var">&rsquo;requesttosend&rsquo;</var></dt>
<dd><p>Set the requesttosend (RTS) line.
</p>
</dd>
<dt><var class="var">&rsquo;dataterminalready&rsquo;</var></dt>
<dd><p>Set the dataterminalready (DTR) line.
</p>
</dd>
</dl>
<h4 class="subsubheading" id="Outputs-62">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> @octave_serialport/-get.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserialport_002fsetDTR">
<h4 class="subsection">3.8.11 @octave_serialport/setDTR</h4>
<a class="index-entry-id" id="index-setDTR"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-setDTR-1"><span class="category-def">: </span><strong class="def-name">setDTR</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">true_false</var>)</code></dt>
<dd><p>Set the state of the DTR line
</p>
<h4 class="subsubheading" id="Inputs-63">Inputs</h4>
<p><var class="var">dev</var> - connected serial device.<br>
<var class="var">true_false</var> - state to set the line.<br>
</p>
<h4 class="subsubheading" id="Outputs-63">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> serialport, getpinstatus, setRTS.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserialport_002fsetRTS">
<h4 class="subsection">3.8.12 @octave_serialport/setRTS</h4>
<a class="index-entry-id" id="index-setRTS"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-setRTS-1"><span class="category-def">: </span><strong class="def-name">setRTS</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">true_false</var>)</code></dt>
<dd><p>Set the state of the RTS line
</p>
<h4 class="subsubheading" id="Inputs-64">Inputs</h4>
<p><var class="var">dev</var> - connected serial device.<br>
<var class="var">true_false</var> - state to set the line.<br>
</p>
<h4 class="subsubheading" id="Outputs-64">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> serialport, getpinstatus.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fserialport_002fwrite">
<h4 class="subsection">3.8.13 @octave_serialport/write</h4>
<a class="index-entry-id" id="index-write-1"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-write-9"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">write</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-write-10"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">write</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>, <var class="var">precision</var>)</code></dt>
<dd><p>Writes <var class="var">data</var> to serialport instrument
</p>
<h4 class="subsubheading" id="Inputs-65">Inputs</h4>
<p><var class="var">obj</var> is a serialport object.<br>
<var class="var">data</var> data to write.<br>
<var class="var">precision</var> precision of data.<br>
</p>
<h4 class="subsubheading" id="Outputs-65">Outputs</h4>
<p>returns number of bytes written.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="serialport">
<h4 class="subsection">3.8.14 serialport</h4>
<a class="index-entry-id" id="index-serialport"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-serialport-1"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">serial</var> =</code> <strong class="def-name">serialport</strong> <code class="def-code-arguments">([<var class="var">path</var>], [<var class="var">baudrate</var>])</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-serialport-2"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">serial</var> =</code> <strong class="def-name">serialport</strong> <code class="def-code-arguments">([<var class="var">path</var>], [<var class="var">propname</var>, <var class="var">propvalue</var>])</code></dt>
<dd>
<p>Open serial port interface.
</p>
<h4 class="subsubheading" id="Inputs-66">Inputs</h4>
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
<h4 class="subsubheading" id="Outputs-66">Outputs</h4>
<p>The serialport() shall return an instance of <var class="var">octave_serialport</var> class as the result <var class="var">serial</var>.
</p>
<h4 class="subsubheading" id="Properties-7">Properties</h4>
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
</div>
<div class="subsection-level-extent" id="serialportlist">
<h4 class="subsection">3.8.15 serialportlist</h4>
<a class="index-entry-id" id="index-serialportlist"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-serialportlist-1"><span class="category-def">Function File: </span><code class="def-type"><var class="var">list</var> =</code> <strong class="def-name">serialportlist</strong> <code class="def-code-arguments">()</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-serialportlist-2"><span class="category-def">Function File: </span><code class="def-type"><var class="var">list</var> =</code> <strong class="def-name">serialportlist</strong> <code class="def-code-arguments">(&quot;all&quot;)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-serialportlist-3"><span class="category-def">Function File: </span><code class="def-type"><var class="var">list</var> =</code> <strong class="def-name">serialportlist</strong> <code class="def-code-arguments">(&quot;available&quot;)</code></dt>
<dd><p>Returns a list of all serial ports detected in the system.
</p>
<h4 class="subsubheading" id="Inputs-67">Inputs</h4>
<p>&rsquo;all&rsquo; - show all serial ports (same as providing no arguments)
 &rsquo;available&rsquo; - show only serial ports that are available for use
</p>
<h4 class="subsubheading" id="Outputs-67">Outputs</h4>
<p><var class="var">list</var> is a string cell array of serial ports names detected
 in the system.
</p>
<p><strong class="strong">See also:</strong> instrhwinfo(&quot;serialport&quot;).
</p></dd></dl>
<hr>
</div>
</div>
<div class="section-level-extent" id="SPI">
<h3 class="section" id="SPI-1">3.9 SPI</h3>
<a class="index-entry-id" id="index-SPI"></a>
<div class="subsection-level-extent" id="g_t_0040octave_005fspi_002ffclose">
<h4 class="subsection">3.9.1 @octave_spi/fclose</h4>
<a class="index-entry-id" id="index-fclose-4"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fclose-13"><span class="category-def">Function File: </span><code class="def-type"><var class="var">res</var> =</code> <strong class="def-name">fclose</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dd><p>Closes SPI connection <var class="var">obj</var>
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fspi_002ffopen">
<h4 class="subsection">3.9.2 @octave_spi/fopen</h4>
<a class="index-entry-id" id="index-fopen-4"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fopen-13"><span class="category-def">Function File: </span><code class="def-type"><var class="var">res</var> =</code> <strong class="def-name">fopen</strong> <code class="def-code-arguments">(<var class="var">obj</var>) (dummy)</code></dt>
<dd><p>Opens SPI connection <var class="var">obj</var>
</p>
<p>This currently is a dummy function to improve compatibility to MATLAB
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fspi_002ffread">
<h4 class="subsection">3.9.3 @octave_spi/fread</h4>
<a class="index-entry-id" id="index-fread-5"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fread-36"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-37"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-38"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>, <var class="var">precision</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-39"><span class="category-def">Function File: </span><code class="def-type">[<var class="var">data</var>,<var class="var">count</var>] =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, ...)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-40"><span class="category-def">Function File: </span><code class="def-type">[<var class="var">data</var>,<var class="var">count</var>,<var class="var">errmsg</var>] =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, ...)</code></dt>
<dd><p>Reads <var class="var">data</var> from a SPI instrument
</p>
<h4 class="subsubheading" id="Inputs-68">Inputs</h4>
<p><var class="var">obj</var> is a SPI object.<br>
<var class="var">size</var> Number of values to read. (Default: 10).<br>
<var class="var">precision</var> precision of data.<br>
</p>
<h4 class="subsubheading" id="Outputs-68">Outputs</h4>
<p><var class="var">data</var> data values.<br>
<var class="var">count</var> number of values read.<br>
<var class="var">errmsg</var> read operation error message.<br>
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fspi_002ffwrite">
<h4 class="subsection">3.9.4 @octave_spi/fwrite</h4>
<a class="index-entry-id" id="index-fwrite-5"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fwrite-23"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fwrite-24"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>, <var class="var">precision</var>)</code></dt>
<dd><p>Writes <var class="var">data</var> to SPI instrument
</p>
<h4 class="subsubheading" id="Inputs-69">Inputs</h4>
<p><var class="var">obj</var> is a SPI object.<br>
<var class="var">data</var> data to write.<br>
<var class="var">precision</var> precision of data.<br>
</p>
<h4 class="subsubheading" id="Outputs-69">Outputs</h4>
<p>returns number of bytes written.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fspi_002fget">
<h4 class="subsection">3.9.5 @octave_spi/get</h4>
<a class="index-entry-id" id="index-get-4"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-get-18"><span class="category-def">Function File: </span><code class="def-type"><var class="var">struct</var> =</code> <strong class="def-name">get</strong> <code class="def-code-arguments">(<var class="var">spi</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-get-19"><span class="category-def">Function File: </span><code class="def-type"><var class="var">field</var> =</code> <strong class="def-name">get</strong> <code class="def-code-arguments">(<var class="var">spi</var>, <var class="var">property</var>)</code></dt>
<dd><p>Get the properties of spi object.
</p>
<h4 class="subsubheading" id="Inputs-70">Inputs</h4>
<p><var class="var">spi</var> - instance of <var class="var">octave_spi</var> class.<br>
</p>
<p><var class="var">property</var> - name of property.<br>
</p>
<h4 class="subsubheading" id="Properties-8">Properties</h4>
<dl class="table">
<dt><var class="var">&rsquo;name&rsquo;</var></dt>
<dd><p>Name for the spi socket.
</p>
</dd>
<dt><var class="var">&rsquo;bitrate&rsquo;</var></dt>
<dd><p>The bitrate for the spi object.
</p>
</dd>
<dt><var class="var">&rsquo;clockpolarity&rsquo;</var></dt>
<dd><p>The clock polarity for the spi object of &rsquo;idlehigh&rsquo; or &rsquo;idlelow&rsquo;.
</p>
</dd>
<dt><var class="var">&rsquo;clockphase&rsquo;</var></dt>
<dd><p>The clock phase for the spi object of &rsquo;firstedge&rsquo; or &rsquo;secondedge&rsquo;.
</p>
</dd>
<dt><var class="var">&rsquo;port&rsquo;</var></dt>
<dd><p>The device port name.
</p>
</dd>
<dt><var class="var">&rsquo;status&rsquo;</var></dt>
<dd><p>The device status of &rsquo;open&rsquo; or &rsquo;closed&rsquo;
</p></dd>
</dl>
<h4 class="subsubheading" id="Outputs-70">Outputs</h4>
<p>When <var class="var">property</var> was specified, return the value of that property.<br>
 otherwise return the values of all properties as a structure.<br>
</p>
<p><strong class="strong">See also:</strong> @octave_spi/set.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fspi_002fread">
<h4 class="subsection">3.9.6 @octave_spi/read</h4>
<a class="index-entry-id" id="index-read-2"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-read-14"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">read</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-read-15"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">read</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>)</code></dt>
<dd><p>Reads <var class="var">data</var> from SPI instrument
</p>
<h4 class="subsubheading" id="Inputs-71">Inputs</h4>
<p><var class="var">obj</var> is a SPI object.<br>
<var class="var">size</var> Number of values to read. (Default: 10).<br>
</p>
<h4 class="subsubheading" id="Outputs-71">Outputs</h4>
<p><var class="var">data</var> data values.<br>
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fspi_002fset">
<h4 class="subsection">3.9.7 @octave_spi/set</h4>
<a class="index-entry-id" id="index-set-4"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-_0028obj_002c-8"><span class="category-def">Function File: </span><code class="def-type">set</code> <strong class="def-name">(<var class="var">obj</var>,</strong> <code class="def-code-arguments"><var class="var">property</var>,<var class="var">value</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-_0028obj_002c-9"><span class="category-def">Function File: </span><code class="def-type">set</code> <strong class="def-name">(<var class="var">obj</var>,</strong> <code class="def-code-arguments"><var class="var">property</var>,<var class="var">value</var>,&hellip;)</code></dt>
<dd><p>Set the properties of spi object.
</p>
<h4 class="subsubheading" id="Inputs-72">Inputs</h4>
<p><var class="var">obj</var> - instance of <var class="var">octave_spi</var> class.<br>
<var class="var">property</var> - name of property.<br>
</p>
<p>If <var class="var">property</var> is a cell so must be <var class="var">value</var>, it sets the values of
 all matching properties.
</p>
<p>The function also accepts property-value pairs.
</p>
<h4 class="subsubheading" id="Properties-9">Properties</h4>
<dl class="table">
<dt><var class="var">&rsquo;name&rsquo;</var></dt>
<dd><p>Set the name for the spi socket.
</p>
</dd>
<dt><var class="var">&rsquo;bitrate&rsquo;</var></dt>
<dd><p>Set the bitrate for the spi object.
</p>
</dd>
<dt><var class="var">&rsquo;clockpolarity&rsquo;</var></dt>
<dd><p>Set the clock polarity for the spi object of &rsquo;idlehigh&rsquo; or &rsquo;idlelow&rsquo;.
</p>
</dd>
<dt><var class="var">&rsquo;clockphase&rsquo;</var></dt>
<dd><p>Set the clock phase for the spi object of &rsquo;firstedge&rsquo; or &rsquo;secondedge&rsquo;.
</p>
</dd>
</dl>
<h4 class="subsubheading" id="Outputs-72">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> @octave_spi/get.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fspi_002fwrite">
<h4 class="subsection">3.9.8 @octave_spi/write</h4>
<a class="index-entry-id" id="index-write-2"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fwrite-25"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>)</code></dt>
<dd><p>Writes <var class="var">data</var> to SPI instrument
</p>
<h4 class="subsubheading" id="Inputs-73">Inputs</h4>
<p><var class="var">obj</var> is a SPI object.<br>
<var class="var">data</var> data to write.<br>
</p>
<h4 class="subsubheading" id="Outputs-73">Outputs</h4>
<p>returns number of bytes written.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fspi_002fwriteAndRead">
<h4 class="subsection">3.9.9 @octave_spi/writeAndRead</h4>
<a class="index-entry-id" id="index-writeAndRead"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-writeAndRead-1"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">writeAndRead</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">wrdata</var>)</code></dt>
<dd><p>Writes and reads <var class="var">data</var> from SPI instrument
</p>
<h4 class="subsubheading" id="Inputs-74">Inputs</h4>
<p><var class="var">obj</var> is a SPI object.<br>
<var class="var">wrdata</var> Data to write.<br>
</p>
<h4 class="subsubheading" id="Outputs-74">Outputs</h4>
<p><var class="var">data</var> data values read.<br>
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="spi">
<h4 class="subsection">3.9.10 spi</h4>
<a class="index-entry-id" id="index-spi"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-spi-1"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">spi</var> =</code> <strong class="def-name">spi</strong> <code class="def-code-arguments">([<var class="var">port_path</var>])</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-spi-2"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">spi</var> =</code> <strong class="def-name">spi</strong> <code class="def-code-arguments">([<var class="var">port_path</var>], [<var class="var">propname</var>, <var class="var">propvalue</var>])</code></dt>
<dd>
<p>Open a spi interface.
</p>
<h4 class="subsubheading" id="Inputs-75">Inputs</h4>
<p><var class="var">port_path</var> - the interface device port/path of type String. If omitted defaults to 
&rsquo;/dev/spi-0&rsquo;. <br>
<var class="var">propname</var>,<var class="var">propvalue</var> - property name/value pairs.
</p>
<p>Known input properties:
</p><dl class="table">
<dt>name</dt>
<dd><p>Name of the object
</p></dd>
<dt>bitrate</dt>
<dd><p>Numeric bitrate value
</p></dd>
<dt>clockpolarity</dt>
<dd><p>Clock polarity: idlehigh or idlelow.
</p></dd>
<dt>clockphase</dt>
<dd><p>Clock phase value: firstedge or secondedge
</p></dd>
</dl>
<h4 class="subsubheading" id="Outputs-75">Outputs</h4>
<p><var class="var">spi</var> - An instance of <var class="var">octave_spi</var> class.
</p>
<h4 class="subsubheading" id="Properties-10">Properties</h4>
<p>The spi object has the following properties:
</p><dl class="table">
<dt>name</dt>
<dd><p>Name of the object
</p></dd>
<dt>status</dt>
<dd><p>Open or closed status of object (readonly).
</p></dd>
<dt>bitrate</dt>
<dd><p>Numeric bitrate value
</p></dd>
<dt>clockpolarity</dt>
<dd><p>Clock polarity: idlehigh or idlelow.
</p></dd>
<dt>clockphase</dt>
<dd><p>Clock phase value: firstedge or secondedge
</p></dd>
<dt>port</dt>
<dd><p>The interface driver port (readonly)
</p></dd>
</dl>
</dd></dl>
</div>
<div class="subsection-level-extent" id="spi_005fclose">
<h4 class="subsection">3.9.11 spi_close</h4>
<a class="index-entry-id" id="index-spi_005fclose"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-spi_005fclose-1"><span class="category-def">Loadable Function: </span><strong class="def-name">spi_close</strong> <code class="def-code-arguments">(<var class="var">spi</var>)</code></dt>
<dd>
<p>Close the interface and release a file descriptor.
</p>
<h4 class="subsubheading" id="Inputs-76">Inputs</h4>
<p><var class="var">spi</var> - instance of <var class="var">octave_spi</var> class.<br>
</p>
<h4 class="subsubheading" id="Outputs-76">Outputs</h4>
<p>None
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="spi_005fread">
<h4 class="subsection">3.9.12 spi_read</h4>
<a class="index-entry-id" id="index-spi_005fread"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-spi_005fread-1"><span class="category-def">Loadable Function: </span><code class="def-type">[<var class="var">data</var>, <var class="var">count</var>] =</code> <strong class="def-name">spi_read</strong> <code class="def-code-arguments">(<var class="var">spi</var>, <var class="var">n</var>)</code></dt>
<dd>
<p>Read from spi slave device.
</p>
<h4 class="subsubheading" id="Inputs-77">Inputs</h4>
<p><var class="var">spi</var> - instance of <var class="var">octave_spi</var> class.<br>
<var class="var">n</var> - number of bytes to attempt to read of type Integer.
</p>
<h4 class="subsubheading" id="Outputs-77">Outputs</h4>
<p>The spi_read() shall return number of bytes successfully read in <var class="var">count</var> as Integer and the bytes themselves in <var class="var">data</var> as uint8 array.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="spi_005fwrite">
<h4 class="subsection">3.9.13 spi_write</h4>
<a class="index-entry-id" id="index-spi_005fwrite"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-spi_005fwrite-1"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">n</var> =</code> <strong class="def-name">spi_write</strong> <code class="def-code-arguments">(<var class="var">spi</var>, <var class="var">data</var>)</code></dt>
<dd>
<p>Write data to a spi slave device.
</p>
<h4 class="subsubheading" id="Inputs-78">Inputs</h4>
<p><var class="var">spi</var> - instance of <var class="var">octave_spi</var> class.<br>
<var class="var">data</var> - data, of type uint8, to be written to the slave device.
</p>
<h4 class="subsubheading" id="Outputs-78">Outputs</h4>
<p>Upon successful completion, spi_write() shall return the number of bytes written as the result <var class="var">n</var>.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="spi_005fwriteAndRead">
<h4 class="subsection">3.9.14 spi_writeAndRead</h4>
<a class="index-entry-id" id="index-spi_005fwriteAndRead"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-spi_005fwriteAndRead-1"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">rddata</var> =</code> <strong class="def-name">spi_writeAndRead</strong> <code class="def-code-arguments">(<var class="var">spi</var>, <var class="var">wrdata</var>)</code></dt>
<dd>
<p>Write data to a spi slave device and then read same number of values.
</p>
<h4 class="subsubheading" id="Inputs-79">Inputs</h4>
<p><var class="var">spi</var> - instance of <var class="var">octave_spi</var> class.<br>
<var class="var">wrdata</var> - data, of type uint8, to be written to the slave device.<br>
</p>
<h4 class="subsubheading" id="Outputs-79">Outputs</h4>
<p>Upon successful completion, spi_writeAndRead() shall return the bytes read.
</p></dd></dl>
<hr>
</div>
</div>
<div class="section-level-extent" id="TCP-_0028Deprecated_0029">
<h3 class="section" id="TCP-_0028Deprecated_0029-1">3.10 TCP (Deprecated)</h3>
<a class="index-entry-id" id="index-TCP-_0028Deprecated_0029"></a>
<div class="subsection-level-extent" id="g_t_0040octave_005ftcp_002ffclose">
<h4 class="subsection">3.10.1 @octave_tcp/fclose</h4>
<a class="index-entry-id" id="index-fclose-5"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fclose-14"><span class="category-def">Function File: </span><code class="def-type"><var class="var">res</var> =</code> <strong class="def-name">fclose</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dd><p>Closes TCP connection <var class="var">obj</var>
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005ftcp_002fflush">
<h4 class="subsection">3.10.2 @octave_tcp/flush</h4>
<a class="index-entry-id" id="index-flush-1"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-flush-9"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">flush</strong> <code class="def-code-arguments">(<var class="var">dev</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-flush-10"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">flush</strong> <code class="def-code-arguments">(<var class="var">dev</var>, &quot;input&quot;)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-flush-11"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">flush</strong> <code class="def-code-arguments">(<var class="var">dev</var>, &quot;output&quot;)</code></dt>
<dd><p>Flush the tcp socket buffers
</p>
<h4 class="subsubheading" id="Inputs-80">Inputs</h4>
<p><var class="var">dev</var> - connected tcp device
</p>
<p>If an additional parameter is provided of &quot;input&quot; or &quot;output&quot;,
 then only the input or output buffer will be flushed
</p>
<h4 class="subsubheading" id="Outputs-80">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> serialport.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005ftcp_002fflushinput">
<h4 class="subsection">3.10.3 @octave_tcp/flushinput</h4>
<a class="index-entry-id" id="index-flushinput-2"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-flushinput-6"><span class="category-def">Loadable Function: </span><strong class="def-name">flushinput</strong> <code class="def-code-arguments">(<var class="var">tcp</var>)</code></dt>
<dd>
<p>Flush the pending input, which will also make the BytesAvailable property be 0.
</p>
<h4 class="subsubheading" id="Inputs-81">Inputs</h4>
<p><var class="var">tcp</var> - instance of <var class="var">octave_tcp</var> class.
</p>
<h4 class="subsubheading" id="Outputs-81">Outputs</h4>
<p>None.
</p>
<p><strong class="strong">See also:</strong> flushoutput.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005ftcp_002fflushoutput">
<h4 class="subsection">3.10.4 @octave_tcp/flushoutput</h4>
<a class="index-entry-id" id="index-flushoutput-2"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-flushoutput-6"><span class="category-def">Loadable Function: </span><strong class="def-name">flushoutput</strong> <code class="def-code-arguments">(<var class="var">tcp</var>)</code></dt>
<dd>
<p>Flush the output buffer.
</p>
<h4 class="subsubheading" id="Inputs-82">Inputs</h4>
<p><var class="var">tcp</var> - instance of <var class="var">octave_tcp</var> class.
</p>
<h4 class="subsubheading" id="Outputs-82">Outputs</h4>
<p>None.
</p>
<p><strong class="strong">See also:</strong> flushinput.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005ftcp_002ffopen">
<h4 class="subsection">3.10.5 @octave_tcp/fopen</h4>
<a class="index-entry-id" id="index-fopen-5"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fopen-14"><span class="category-def">Function File: </span><code class="def-type"><var class="var">res</var> =</code> <strong class="def-name">fopen</strong> <code class="def-code-arguments">(<var class="var">obj</var>) (dummy)</code></dt>
<dd><p>Opens TCP connection <var class="var">obj</var>
</p>
<p>This currently is a dummy function to improve compatibility to MATLAB
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005ftcp_002ffprintf">
<h4 class="subsection">3.10.6 @octave_tcp/fprintf</h4>
<a class="index-entry-id" id="index-fprintf-3"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fprintf-12"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fprintf</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">template</var> ...)</code></dt>
<dd><p>Writes formatted string <var class="var">template</var> using optional parameters to
 TCP instrument
</p>
<h4 class="subsubheading" id="Inputs-83">Inputs</h4>
<p><var class="var">obj</var> is a TCP object.<br>
<var class="var">template</var> Format template string
</p>
<h4 class="subsubheading" id="Outputs-83">Outputs</h4>
<p>Number of characters written
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005ftcp_002ffread">
<h4 class="subsection">3.10.7 @octave_tcp/fread</h4>
<a class="index-entry-id" id="index-fread-6"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fread-41"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-42"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-43"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>, <var class="var">precision</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-44"><span class="category-def">Function File: </span><code class="def-type">[<var class="var">data</var>,<var class="var">count</var>] =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, ...)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-45"><span class="category-def">Function File: </span><code class="def-type">[<var class="var">data</var>,<var class="var">count</var>,<var class="var">errmsg</var>] =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, ...)</code></dt>
<dd><p>Reads <var class="var">data</var> from TCP instrument
</p>
<h4 class="subsubheading" id="Inputs-84">Inputs</h4>
<p><var class="var">obj</var> is a TCP object.<br>
<var class="var">size</var> Number of values to read. (Default: 100).<br>
<var class="var">precision</var> precision of data.<br>
</p>
<h4 class="subsubheading" id="Outputs-84">Outputs</h4>
<p><var class="var">data</var> data read.<br>
<var class="var">count</var> values read.<br>
<var class="var">errmsg</var> read operation error message.<br>
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005ftcp_002ffwrite">
<h4 class="subsection">3.10.8 @octave_tcp/fwrite</h4>
<a class="index-entry-id" id="index-fwrite-6"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fwrite-26"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fwrite-27"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>, <var class="var">precision</var>)</code></dt>
<dd><p>Writes <var class="var">data</var> to TCP instrument
</p>
<h4 class="subsubheading" id="Inputs-85">Inputs</h4>
<p><var class="var">obj</var> is a TCP object.<br>
<var class="var">data</var> data to write.<br>
<var class="var">precision</var> precision of data.<br>
</p>
<h4 class="subsubheading" id="Outputs-85">Outputs</h4>
<p>returns number of bytes written.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005ftcp_002fget">
<h4 class="subsection">3.10.9 @octave_tcp/get</h4>
<a class="index-entry-id" id="index-get-5"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-get-20"><span class="category-def">Function File: </span><code class="def-type"><var class="var">struct</var> =</code> <strong class="def-name">get</strong> <code class="def-code-arguments">(<var class="var">tcp</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-get-21"><span class="category-def">Function File: </span><code class="def-type"><var class="var">field</var> =</code> <strong class="def-name">get</strong> <code class="def-code-arguments">(<var class="var">tcp</var>, <var class="var">property</var>)</code></dt>
<dd><p>Get the properties of tcp object.
</p>
<h4 class="subsubheading" id="Inputs-86">Inputs</h4>
<p><var class="var">tcp</var> - instance of <var class="var">octave_tcp</var> class.<br>
<var class="var">property</var> - name of property.<br>
</p>
<h4 class="subsubheading" id="Outputs-86">Outputs</h4>
<p>When <var class="var">property</var> was specified, return the value of that property.<br>
 otherwise return the values of all properties as a structure.<br>
</p>
<p><strong class="strong">See also:</strong> @octave_tcp/set.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005ftcp_002fread">
<h4 class="subsection">3.10.10 @octave_tcp/read</h4>
<a class="index-entry-id" id="index-read-3"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-read-16"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">read</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-read-17"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">read</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-read-18"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">read</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>, <var class="var">datatype</var>)</code></dt>
<dd><p>Reads <var class="var">data</var> from TCP instrument
</p>
<h4 class="subsubheading" id="Inputs-87">Inputs</h4>
<p><var class="var">obj</var> is a TCP object.<br>
<var class="var">size</var> Number of values to read. (Default: 100).<br>
<var class="var">datatype</var> datatype of data.<br>
</p>
<h4 class="subsubheading" id="Outputs-87">Outputs</h4>
<p><var class="var">data</var> data read.<br>
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005ftcp_002fset">
<h4 class="subsection">3.10.11 @octave_tcp/set</h4>
<a class="index-entry-id" id="index-set-5"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-_0028obj_002c-10"><span class="category-def">Function File: </span><code class="def-type">set</code> <strong class="def-name">(<var class="var">obj</var>,</strong> <code class="def-code-arguments"><var class="var">property</var>,<var class="var">value</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-_0028obj_002c-11"><span class="category-def">Function File: </span><code class="def-type">set</code> <strong class="def-name">(<var class="var">obj</var>,</strong> <code class="def-code-arguments"><var class="var">property</var>,<var class="var">value</var>,&hellip;)</code></dt>
<dd><p>Set the properties of tcp object.
</p>
<h4 class="subsubheading" id="Inputs-88">Inputs</h4>
<p>If <var class="var">property</var> is a cell so must be <var class="var">value</var>, it sets the values of
 all matching properties.
</p>
<p>The function also accepts property-value pairs.
</p>
<h4 class="subsubheading" id="Properties-11">Properties</h4>
<dl class="table">
<dt><var class="var">&rsquo;name&rsquo;</var></dt>
<dd><p>Set the name for the tcp socket.
</p>
</dd>
<dt><var class="var">&rsquo;remotehost&rsquo;</var></dt>
<dd><p>Set the remote host name for the tcp socket.
</p>
</dd>
<dt><var class="var">&rsquo;remoteport&rsquo;</var></dt>
<dd><p>Set the remote port for the tcp socket.
</p>
</dd>
<dt><var class="var">&rsquo;timeout&rsquo;</var></dt>
<dd><p>Set the timeout value in seconds. Value of -1 means a
 blocking call.
</p>
</dd>
</dl>
<h4 class="subsubheading" id="Outputs-88">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> @octave_tcp/get.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005ftcp_002fwrite">
<h4 class="subsection">3.10.12 @octave_tcp/write</h4>
<a class="index-entry-id" id="index-write-3"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-write-11"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">write</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-write-12"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">write</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>, <var class="var">datatype</var>)</code></dt>
<dd><p>Writes <var class="var">data</var> to TCP instrument
</p>
<h4 class="subsubheading" id="Inputs-89">Inputs</h4>
<p><var class="var">obj</var> is a TCP object.<br>
<var class="var">data</var> data to write.<br>
<var class="var">datatype</var> datatype of data. If not specified, it defaults to &quot;uint8&quot;.<br>
</p>
<h4 class="subsubheading" id="Outputs-89">Outputs</h4>
<p>returns number of bytes written.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="tcp">
<h4 class="subsection">3.10.13 tcp</h4>
<a class="index-entry-id" id="index-tcp"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-tcp-1"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">tcp</var> =</code> <strong class="def-name">tcp</strong> <code class="def-code-arguments">()</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-tcp-2"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">tcp</var> =</code> <strong class="def-name">tcp</strong> <code class="def-code-arguments">(<var class="var">ipaddress</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-tcp-3"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">tcp</var> =</code> <strong class="def-name">tcp</strong> <code class="def-code-arguments">(<var class="var">ipaddress</var>, <var class="var">port</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-tcp-4"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">tcp</var> =</code> <strong class="def-name">tcp</strong> <code class="def-code-arguments">(<var class="var">ipaddress</var>, <var class="var">port</var>, <var class="var">timeout</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-tcp-5"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">tcp</var> =</code> <strong class="def-name">tcp</strong> <code class="def-code-arguments">(<var class="var">ipaddress</var>, [<var class="var">propertyname</var>, <var class="var">propertyvalue</var>])</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-tcp-6"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">tcp</var> =</code> <strong class="def-name">tcp</strong> <code class="def-code-arguments">(<var class="var">ipaddress</var>, <var class="var">port</var>, [<var class="var">propertyname</var>, <var class="var">propertyvalue</var>])</code></dt>
<dd>
<p>Open tcp interface.
</p>
<h4 class="subsubheading" id="Inputs-90">Inputs</h4>
<p><var class="var">ipaddress</var> - the ip address of type String. If omitted defaults to &rsquo;127.0.0.1&rsquo;.<br>
<var class="var">port</var> - the port number to connect. If omitted defaults to 23.<br>
<var class="var">timeout</var> - the interface timeout value. If omitted defaults to blocking call.<br>
<var class="var">propname</var>,<var class="var">propvalue</var> - property name/value pairs.
</p>
<p>Known input properties:
</p><dl class="table">
<dt>name</dt>
<dd><p>name value
</p></dd>
<dt>timeout</dt>
<dd><p>Numeric timeout value or -1 to wait forever
</p></dd>
</dl>
<h4 class="subsubheading" id="Outputs-90">Outputs</h4>
<p>The tcp() shall return instance of <var class="var">octave_tcp</var> class as the result <var class="var">tcp</var>.
</p><h4 class="subsubheading" id="Properties-12">Properties</h4>
<p>The tcp object has the following public properties:
</p><dl class="table">
<dt>name</dt>
<dd><p>name assigned to the tcp object
</p></dd>
<dt>type</dt>
<dd><p>instrument type &rsquo;tcp&rsquo; (readonly)
</p></dd>
<dt>localport</dt>
<dd><p>local port number (readonly)
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
</div>
<div class="subsection-level-extent" id="tcp_005fclose">
<h4 class="subsection">3.10.14 tcp_close</h4>
<a class="index-entry-id" id="index-tcp_005fclose"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-tcp_005fclose-1"><span class="category-def">Loadable Function: </span><strong class="def-name">tcp_close</strong> <code class="def-code-arguments">(<var class="var">tcp</var>)</code></dt>
<dd>
<p>Close the interface and release a file descriptor.
</p>
<h4 class="subsubheading" id="Inputs-91">Inputs</h4>
<p><var class="var">tcp</var> - instance of <var class="var">octave_tcp</var> class.
</p>
<h4 class="subsubheading" id="Outputs-91">Outputs</h4>
<p>None
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="tcp_005fread">
<h4 class="subsection">3.10.15 tcp_read</h4>
<a class="index-entry-id" id="index-tcp_005fread"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-tcp_005fread-1"><span class="category-def">Loadable Function: </span><code class="def-type">[<var class="var">data</var>, <var class="var">count</var>] =</code> <strong class="def-name">tcp_read</strong> <code class="def-code-arguments">(<var class="var">tcp</var>, <var class="var">n</var>, <var class="var">timeout</var>)</code></dt>
<dd>
<p>Read from tcp interface.
</p>
<h4 class="subsubheading" id="Inputs-92">Inputs</h4>
<p><var class="var">tcp</var> - instance of <var class="var">octave_tcp</var> class.<br>
<var class="var">n</var> - number of bytes to attempt to read of type Integer<br>
<var class="var">timeout</var> - timeout in ms if different from default of type Integer
</p>
<h4 class="subsubheading" id="Outputs-92">Outputs</h4>
<p><var class="var">count</var> - number of bytes successfully read as an Integer<br>
<var class="var">data</var> - data bytes themselves as uint8 array.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="tcp_005ftimeout">
<h4 class="subsection">3.10.16 tcp_timeout</h4>
<a class="index-entry-id" id="index-tcp_005ftimeout"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-tcp_005ftimeout-1"><span class="category-def">Loadable Function: </span><strong class="def-name">tcp_timeout</strong> <code class="def-code-arguments">(<var class="var">tcp</var>, <var class="var">timeout</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-tcp_005ftimeout-2"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">t</var> =</code> <strong class="def-name">tcp_timeout</strong> <code class="def-code-arguments">(<var class="var">tcp</var>)</code></dt>
<dd>
<p>Set new or get existing tcp interface timeout parameter used for tcp_read() requests. The timeout value is specified in milliseconds.
</p>
<h4 class="subsubheading" id="Inputs-93">Inputs</h4>
<p><var class="var">tcp</var> - instance of <var class="var">octave_tcp</var> class.<br>
<var class="var">timeout</var> - tcp_read() timeout value in milliseconds. Value of -1 means a blocking call.
</p>
<h4 class="subsubheading" id="Outputs-93">Outputs</h4>
<p>If <var class="var">timeout</var> parameter is omitted, the tcp_timeout() shall return current timeout value as the result <var class="var">t</var>.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="tcp_005fwrite">
<h4 class="subsection">3.10.17 tcp_write</h4>
<a class="index-entry-id" id="index-tcp_005fwrite"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-tcp_005fwrite-1"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">n</var> =</code> <strong class="def-name">tcp_write</strong> <code class="def-code-arguments">(<var class="var">tcp</var>, <var class="var">data</var>)</code></dt>
<dd>
<p>Write data to a tcp interface.
</p>
<h4 class="subsubheading" id="Inputs-94">Inputs</h4>
<p><var class="var">tcp</var> - instance of <var class="var">octave_tcp</var> class.<br>
<var class="var">data</var> - data to be written to the tcp interface. Can be either of String or uint8 type.
</p>
<h4 class="subsubheading" id="Outputs-94">Outputs</h4>
<p>Upon successful completion, tcp_write() shall return the number of bytes written as the result <var class="var">n</var>.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="tcpip">
<h4 class="subsection">3.10.18 tcpip</h4>
<a class="index-entry-id" id="index-tcpip"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-tcpip-1"><span class="category-def">Function File: </span><code class="def-type"><var class="var">tcp</var> =</code> <strong class="def-name">tcpip</strong> <code class="def-code-arguments">(<var class="var">host</var>, [<var class="var">port</var>], [<var class="var">PropertyName</var>, <var class="var">PropertyValue</var>...])</code></dt>
<dd><p>Matlab compatible wrapper to the tcp interface.
</p>
<p>NOTE: tcpip has been deprecated. Use tcpclient instead
</p>
<h4 class="subsubheading" id="Inputs-95">Inputs</h4>
<p><var class="var">host</var> - the host name or ip.<br>
<var class="var">port</var> - the port number to connect. If omitted defaults to 80.<br>
<var class="var">PropertyName</var>, <var class="var">PropertyValue</var> - Optional property name, value pairs to set on the tcp object.<br>
</p>
<h4 class="subsubheading" id="Properties-13">Properties</h4>
<p>Currently the only known properties are &quot;timeout&quot; and &quot;name&quot;.
</p>
<h4 class="subsubheading" id="Outputs-95">Outputs</h4>
<p>tcpip will return an instance of <var class="var">octave_tcp</var> class as the result.
</p></dd></dl>
<hr>
</div>
</div>
<div class="section-level-extent" id="TCP-Client">
<h3 class="section" id="TCP-Client-2">3.11 TCP Client</h3>
<a class="index-entry-id" id="index-TCP-Client"></a>
<div class="subsection-level-extent" id="g_t_0040octave_005ftcpclient_002fconfigureTerminator">
<h4 class="subsection">3.11.1 @octave_tcpclient/configureTerminator</h4>
<a class="index-entry-id" id="index-configureTerminator-1"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-configureTerminator-6"><span class="category-def">Function File: </span><strong class="def-name">configureTerminator</strong> <code class="def-code-arguments">(<var class="var">tcp</var>, <var class="var">term</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-configureTerminator-7"><span class="category-def">Function File: </span><strong class="def-name">configureTerminator</strong> <code class="def-code-arguments">(<var class="var">tcp</var>, <var class="var">readterm</var>, <var class="var">writeterm</var>)</code></dt>
<dd><p>Set terminator on a tcpclient object for ASCII string manipulation
</p>
<h4 class="subsubheading" id="Inputs-96">Inputs</h4>
<p><var class="var">tcp</var> - tcpclient object<br>
<var class="var">term</var> - terminal value for both read and write<br>
<var class="var">readterm</var> = terminal value type for read data<br>
<var class="var">writeterm</var> = terminal value for written data<br>
</p>
<p>The terminal can be either strings &quot;cr&quot;, &quot;lf&quot; (default), &quot;lf/cr&quot; or an integer between 0 to 255.
</p>
<h4 class="subsubheading" id="Outputs-96">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> tcpport.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005ftcpclient_002fflush">
<h4 class="subsection">3.11.2 @octave_tcpclient/flush</h4>
<a class="index-entry-id" id="index-flush-2"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-flush-12"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">flush</strong> <code class="def-code-arguments">(<var class="var">dev</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-flush-13"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">flush</strong> <code class="def-code-arguments">(<var class="var">dev</var>, &quot;input&quot;)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-flush-14"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">flush</strong> <code class="def-code-arguments">(<var class="var">dev</var>, &quot;output&quot;)</code></dt>
<dd><p>Flush the tcpclient socket buffers
</p>
<h4 class="subsubheading" id="Inputs-97">Inputs</h4>
<p><var class="var">dev</var> - connected tcpclient device
</p>
<p>If an additional parameter is provided of &quot;input&quot; or &quot;output&quot;,
 then only the input or output buffer will be flushed
</p>
<h4 class="subsubheading" id="Outputs-97">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> serialport.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005ftcpclient_002fget">
<h4 class="subsection">3.11.3 @octave_tcpclient/get</h4>
<a class="index-entry-id" id="index-get-6"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-get-22"><span class="category-def">Function File: </span><code class="def-type"><var class="var">struct</var> =</code> <strong class="def-name">get</strong> <code class="def-code-arguments">(<var class="var">tcpclient</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-get-23"><span class="category-def">Function File: </span><code class="def-type"><var class="var">field</var> =</code> <strong class="def-name">get</strong> <code class="def-code-arguments">(<var class="var">tcpclient</var>, <var class="var">property</var>)</code></dt>
<dd><p>Get the properties of tcpclient object.
</p>
<h4 class="subsubheading" id="Inputs-98">Inputs</h4>
<p><var class="var">tcpclient</var> - instance of <var class="var">octave_tcpclient</var> class.<br>
<var class="var">property</var> - name of property.<br>
</p>
<h4 class="subsubheading" id="Outputs-98">Outputs</h4>
<p>When <var class="var">property</var> was specified, return the value of that property.<br>
 otherwise return the values of all properties as a structure.<br>
</p>
<p><strong class="strong">See also:</strong> @octave_tcpclient/set.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005ftcpclient_002fread">
<h4 class="subsection">3.11.4 @octave_tcpclient/read</h4>
<a class="index-entry-id" id="index-read-4"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-read-19"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">read</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-read-20"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">read</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-read-21"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">read</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>, <var class="var">datatype</var>)</code></dt>
<dd><p>Reads <var class="var">data</var> from TCP instrument
</p>
<h4 class="subsubheading" id="Inputs-99">Inputs</h4>
<p><var class="var">obj</var> is a TCP object.<br>
<var class="var">size</var> Number of values to read. (Default: NumBytesAvailable).<br>
<var class="var">datatype</var> datatype of data.<br>
</p>
<h4 class="subsubheading" id="Outputs-99">Outputs</h4>
<p><var class="var">data</var> data read.<br>
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005ftcpclient_002fset">
<h4 class="subsection">3.11.5 @octave_tcpclient/set</h4>
<a class="index-entry-id" id="index-set-6"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-_0028obj_002c-12"><span class="category-def">Function File: </span><code class="def-type">set</code> <strong class="def-name">(<var class="var">obj</var>,</strong> <code class="def-code-arguments"><var class="var">property</var>,<var class="var">value</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-_0028obj_002c-13"><span class="category-def">Function File: </span><code class="def-type">set</code> <strong class="def-name">(<var class="var">obj</var>,</strong> <code class="def-code-arguments"><var class="var">property</var>,<var class="var">value</var>,&hellip;)</code></dt>
<dd><p>Set the properties of tcpclient object.
</p>
<h4 class="subsubheading" id="Inputs-100">Inputs</h4>
<p>If <var class="var">property</var> is a cell so must be <var class="var">value</var>, it sets the values of
 all matching properties.
</p>
<p>The function also accepts property-value pairs.
</p>
<h4 class="subsubheading" id="Properties-14">Properties</h4>
<dl class="table">
<dt><var class="var">&rsquo;Name&rsquo;</var></dt>
<dd><p>Set the name for the tcpclient socket.
</p>
</dd>
<dt><var class="var">&rsquo;UserData&rsquo;</var></dt>
<dd><p>Set user data for the tcpclient socket.
</p>
</dd>
<dt><var class="var">&rsquo;Timeout&rsquo;</var></dt>
<dd><p>Set the timeout value in seconds. Value of -1 means a
 blocking call.
</p>
</dd>
<dt><var class="var">&rsquo;Tag&rsquo;</var></dt>
<dd><p>Set user tag to identify the port
</p>
</dd>
</dl>
<h4 class="subsubheading" id="Outputs-100">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> @octave_tcpclient/get.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005ftcpclient_002fwrite">
<h4 class="subsection">3.11.6 @octave_tcpclient/write</h4>
<a class="index-entry-id" id="index-write-4"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-write-13"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">write</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-write-14"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">write</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>, <var class="var">datatype</var>)</code></dt>
<dd><p>Writes <var class="var">data</var> to TCP instrument
</p>
<h4 class="subsubheading" id="Inputs-101">Inputs</h4>
<p><var class="var">obj</var> is a TCPclient  object.<br>
<var class="var">data</var> data to write.<br>
<var class="var">datatype</var> datatype of data. If not specified, it defaults to &quot;uint8&quot;.<br>
</p>
<h4 class="subsubheading" id="Outputs-101">Outputs</h4>
<p>returns number of bytes written.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="tcpclient">
<h4 class="subsection">3.11.7 tcpclient</h4>
<a class="index-entry-id" id="index-tcpclient"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-tcpclient-1"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">tcpclient</var> =</code> <strong class="def-name">tcpclient</strong> <code class="def-code-arguments">(<var class="var">ipaddress</var>, <var class="var">port</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-tcpclient-2"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">tcpclient</var> =</code> <strong class="def-name">tcpclient</strong> <code class="def-code-arguments">(<var class="var">ipaddress</var>, <var class="var">port</var>, [<var class="var">propertyname</var>, <var class="var">propertyvalue</var>])</code></dt>
<dd>
<p>Open tcpclient interface.
</p>
<h4 class="subsubheading" id="Inputs-102">Inputs</h4>
<p><var class="var">ipaddress</var> - the ip address of type String.<br>
<var class="var">port</var> - the port number to connect.<br>
<var class="var">propname</var>,<var class="var">propvalue</var> - property name/value pairs.
</p>
<p>Known input properties:
</p><dl class="table">
<dt>Name</dt>
<dd><p>name value
</p></dd>
<dt>Tag</dt>
<dd><p>tag value
</p></dd>
<dt>Timeout</dt>
<dd><p>Numeric timeout value or -1 to wait forever
</p></dd>
<dt>EnableTransferDelay</dt>
<dd><p>Boolean to enable or disable the nagle algorithm for delay transfer.
</p></dd>
<dt>UserData</dt>
<dd><p>User data value.
</p></dd>
</dl>
<h4 class="subsubheading" id="Outputs-102">Outputs</h4>
<p>The tcpclient() shall return instance of <var class="var">octave_tcpclient</var> class as the result <var class="var">tcpclient</var>.
</p>
<h4 class="subsubheading" id="Properties-15">Properties</h4>
<p>The tcpclient object has the following public properties:
</p><dl class="table">
<dt>Name</dt>
<dd><p>name assigned to the tcpclient object
</p></dd>
<dt>Tag</dt>
<dd><p>user tag assigned to the tcpclient object
</p></dd>
<dt>Type</dt>
<dd><p>instrument type &rsquo;tcpclient&rsquo; (readonly)
</p></dd>
<dt>Port</dt>
<dd><p>remote port number (Readonly)
</p></dd>
<dt>Address</dt>
<dd><p>remote host address (Readonly)
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
<dt>EnableTransferDelay</dt>
<dd><p>Bool for whether transfer delay is enabled. (Read only)
</p></dd>
</dl>
</dd></dl>
<hr>
</div>
</div>
<div class="section-level-extent" id="TCP-Server">
<h3 class="section" id="TCP-Server-1">3.12 TCP Server</h3>
<a class="index-entry-id" id="index-TCP-Server"></a>
<div class="subsection-level-extent" id="g_t_0040octave_005ftcpserver_002fconfigureTerminator">
<h4 class="subsection">3.12.1 @octave_tcpserver/configureTerminator</h4>
<a class="index-entry-id" id="index-configureTerminator-2"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-configureTerminator-8"><span class="category-def">Function File: </span><strong class="def-name">configureTerminator</strong> <code class="def-code-arguments">(<var class="var">tcp</var>, <var class="var">term</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-configureTerminator-9"><span class="category-def">Function File: </span><strong class="def-name">configureTerminator</strong> <code class="def-code-arguments">(<var class="var">tcp</var>, <var class="var">readterm</var>, <var class="var">writeterm</var>)</code></dt>
<dd><p>Set terminator on a tcpserver object for ASCII string manipulation
</p>
<h4 class="subsubheading" id="Inputs-103">Inputs</h4>
<p><var class="var">tcp</var> - tcpserver object<br>
<var class="var">term</var> - terminal value for both read and write<br>
<var class="var">readterm</var> = terminal value type for read data<br>
<var class="var">writeterm</var> = terminal value for written data<br>
</p>
<p>The terminal can be either strings &quot;cr&quot;, &quot;lf&quot; (default), &quot;lf/cr&quot; or an integer between 0 to 255.
</p>
<h4 class="subsubheading" id="Outputs-103">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> tcpport.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005ftcpserver_002fflush">
<h4 class="subsection">3.12.2 @octave_tcpserver/flush</h4>
<a class="index-entry-id" id="index-flush-3"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-flush-15"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">flush</strong> <code class="def-code-arguments">(<var class="var">dev</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-flush-16"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">flush</strong> <code class="def-code-arguments">(<var class="var">dev</var>, &quot;input&quot;)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-flush-17"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">flush</strong> <code class="def-code-arguments">(<var class="var">dev</var>, &quot;output&quot;)</code></dt>
<dd><p>Flush the tcpserver socket buffers
</p>
<h4 class="subsubheading" id="Inputs-104">Inputs</h4>
<p><var class="var">dev</var> - connected tcpserver device
</p>
<p>If an additional parameter is provided of &quot;input&quot; or &quot;output&quot;,
 then only the input or output buffer will be flushed
</p>
<h4 class="subsubheading" id="Outputs-104">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> serialport.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005ftcpserver_002fget">
<h4 class="subsection">3.12.3 @octave_tcpserver/get</h4>
<a class="index-entry-id" id="index-get-7"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-get-24"><span class="category-def">Function File: </span><code class="def-type"><var class="var">struct</var> =</code> <strong class="def-name">get</strong> <code class="def-code-arguments">(<var class="var">tcpserver</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-get-25"><span class="category-def">Function File: </span><code class="def-type"><var class="var">field</var> =</code> <strong class="def-name">get</strong> <code class="def-code-arguments">(<var class="var">tcpserver</var>, <var class="var">property</var>)</code></dt>
<dd><p>Get the properties of tcpserver object.
</p>
<h4 class="subsubheading" id="Inputs-105">Inputs</h4>
<p><var class="var">tcpserver</var> - instance of <var class="var">octave_tcpserver</var> class.<br>
<var class="var">property</var> - name of property.<br>
</p>
<h4 class="subsubheading" id="Outputs-105">Outputs</h4>
<p>When <var class="var">property</var> was specified, return the value of that property.<br>
 otherwise return the values of all properties as a structure.<br>
</p>
<p><strong class="strong">See also:</strong> @octave_tcpserver/set.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005ftcpserver_002fread">
<h4 class="subsection">3.12.4 @octave_tcpserver/read</h4>
<a class="index-entry-id" id="index-read-5"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-read-22"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">read</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-read-23"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">read</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-read-24"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">read</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>, <var class="var">datatype</var>)</code></dt>
<dd><p>Reads <var class="var">data</var> from TCP instrument
</p>
<h4 class="subsubheading" id="Inputs-106">Inputs</h4>
<p><var class="var">obj</var> is a TCP Server object.<br>
<var class="var">size</var> Number of values to read. (Default: NumBytesAvailable).<br>
<var class="var">datatype</var> datatype of data.<br>
</p>
<h4 class="subsubheading" id="Outputs-106">Outputs</h4>
<p><var class="var">data</var> data read.<br>
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005ftcpserver_002fset">
<h4 class="subsection">3.12.5 @octave_tcpserver/set</h4>
<a class="index-entry-id" id="index-set-7"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-_0028obj_002c-14"><span class="category-def">Function File: </span><code class="def-type">set</code> <strong class="def-name">(<var class="var">obj</var>,</strong> <code class="def-code-arguments"><var class="var">property</var>,<var class="var">value</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-_0028obj_002c-15"><span class="category-def">Function File: </span><code class="def-type">set</code> <strong class="def-name">(<var class="var">obj</var>,</strong> <code class="def-code-arguments"><var class="var">property</var>,<var class="var">value</var>,&hellip;)</code></dt>
<dd><p>Set the properties of tcpserver object.
</p>
<h4 class="subsubheading" id="Inputs-107">Inputs</h4>
<p>If <var class="var">property</var> is a cell so must be <var class="var">value</var>, it sets the values of
 all matching properties.
</p>
<p>The function also accepts property-value pairs.
</p>
<h4 class="subsubheading" id="Properties-16">Properties</h4>
<dl class="table">
<dt><var class="var">&rsquo;Name&rsquo;</var></dt>
<dd><p>Set the name for the tcpserver socket.
</p>
</dd>
<dt><var class="var">&rsquo;UserData&rsquo;</var></dt>
<dd><p>Set user data for the tcpserver socket.
</p>
</dd>
<dt><var class="var">&rsquo;Timeout&rsquo;</var></dt>
<dd><p>Set the timeout value in seconds. Value of -1 means a
 blocking call.
</p>
</dd>
</dl>
<h4 class="subsubheading" id="Outputs-107">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> @octave_tcpserver/get.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005ftcpserver_002fwrite">
<h4 class="subsection">3.12.6 @octave_tcpserver/write</h4>
<a class="index-entry-id" id="index-write-5"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-write-15"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">write</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-write-16"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">write</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>, <var class="var">datatype</var>)</code></dt>
<dd><p>Writes <var class="var">data</var> to TCP instrument
</p>
<h4 class="subsubheading" id="Inputs-108">Inputs</h4>
<p><var class="var">obj</var> is a TCPServer object.<br>
<var class="var">data</var> data to write.<br>
<var class="var">datatype</var> datatype of data. If not specified, it defaults to &quot;uint8&quot;.<br>
</p>
<h4 class="subsubheading" id="Outputs-108">Outputs</h4>
<p>returns number of bytes written.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="tcpserver">
<h4 class="subsection">3.12.7 tcpserver</h4>
<a class="index-entry-id" id="index-tcpserver"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-tcpserver-1"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">tcpserver</var> =</code> <strong class="def-name">tcpserver</strong> <code class="def-code-arguments">(<var class="var">ipaddress</var>, <var class="var">port</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-tcpserver-2"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">tcpserver</var> =</code> <strong class="def-name">tcpserver</strong> <code class="def-code-arguments">(<var class="var">port</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-tcpserver-3"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">tcpserver</var> =</code> <strong class="def-name">tcpserver</strong> <code class="def-code-arguments">(&hellip;, [<var class="var">propertyname</var>, <var class="var">propertyvalue</var>])</code></dt>
<dd>
<p>Open tcpserver interface.
</p>
<h4 class="subsubheading" id="Inputs-109">Inputs</h4>
<p><var class="var">ipaddress</var> - the ip address of type String.<br>
<var class="var">port</var> - the port number to bind.<br>
<var class="var">propname</var>,<var class="var">propvalue</var> - property name/value pairs.
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
<h4 class="subsubheading" id="Outputs-109">Outputs</h4>
<p>The tcpserver() shall return instance of <var class="var">octave_tcpserver</var> class as the result <var class="var">tcpserver</var>.
</p>
<h4 class="subsubheading" id="Properties-17">Properties</h4>
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
<hr>
</div>
</div>
<div class="section-level-extent" id="UDP-_0028Deprecated_0029">
<h3 class="section" id="UDP-_0028Deprecated_0029-1">3.13 UDP (Deprecated)</h3>
<a class="index-entry-id" id="index-UDP-_0028Deprecated_0029"></a>
<div class="subsection-level-extent" id="g_t_0040octave_005fudp_002ffclose">
<h4 class="subsection">3.13.1 @octave_udp/fclose</h4>
<a class="index-entry-id" id="index-fclose-6"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fclose-15"><span class="category-def">Function File: </span><code class="def-type"><var class="var">res</var> =</code> <strong class="def-name">fclose</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dd><p>Closes UDP connection <var class="var">obj</var>
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fudp_002fflush">
<h4 class="subsection">3.13.2 @octave_udp/flush</h4>
<a class="index-entry-id" id="index-flush-4"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-flush-18"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">flush</strong> <code class="def-code-arguments">(<var class="var">dev</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-flush-19"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">flush</strong> <code class="def-code-arguments">(<var class="var">dev</var>, &quot;input&quot;)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-flush-20"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">flush</strong> <code class="def-code-arguments">(<var class="var">dev</var>, &quot;output&quot;)</code></dt>
<dd><p>Flush the udp socket buffers
</p>
<h4 class="subsubheading" id="Inputs-110">Inputs</h4>
<p><var class="var">dev</var> - open udp device
</p>
<p>If an additional parameter is provided of &quot;input&quot; or &quot;output&quot;,
 then only the input or output buffer will be flushed
</p>
<h4 class="subsubheading" id="Outputs-110">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> udp.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fudp_002fflushinput">
<h4 class="subsection">3.13.3 @octave_udp/flushinput</h4>
<a class="index-entry-id" id="index-flushinput-3"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-flushinput-7"><span class="category-def">Loadable Function: </span><strong class="def-name">flushinput</strong> <code class="def-code-arguments">(<var class="var">udp</var>)</code></dt>
<dd>
<p>Flush the pending input, which will also make the BytesAvailable property be 0.
</p>
<h4 class="subsubheading" id="Inputs-111">Inputs</h4>
<p><var class="var">udp</var> - instance of <var class="var">octave_udp</var> class.
</p>
<h4 class="subsubheading" id="Outputs-111">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> flushoutput.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fudp_002fflushoutput">
<h4 class="subsection">3.13.4 @octave_udp/flushoutput</h4>
<a class="index-entry-id" id="index-flushoutput-3"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-flushoutput-7"><span class="category-def">Loadable Function: </span><strong class="def-name">flushoutput</strong> <code class="def-code-arguments">(<var class="var">udp</var>)</code></dt>
<dd>
<p>Flush the output buffer.
</p>
<h4 class="subsubheading" id="Inputs-112">Inputs</h4>
<p><var class="var">udp</var> - instance of <var class="var">octave_udp</var> class.
</p>
<h4 class="subsubheading" id="Outputs-112">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> flushinput.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fudp_002ffopen">
<h4 class="subsection">3.13.5 @octave_udp/fopen</h4>
<a class="index-entry-id" id="index-fopen-6"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fopen-15"><span class="category-def">Function File: </span><code class="def-type"><var class="var">res</var> =</code> <strong class="def-name">fopen</strong> <code class="def-code-arguments">(<var class="var">obj</var>) (dummy)</code></dt>
<dd><p>Opens UDP connection <var class="var">obj</var>
 This currently is a dummy function to improve compatibility to MATLAB
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fudp_002ffprintf">
<h4 class="subsection">3.13.6 @octave_udp/fprintf</h4>
<a class="index-entry-id" id="index-fprintf-4"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fprintf-13"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fprintf</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">template</var> ...)</code></dt>
<dd><p>Writes formatted string <var class="var">template</var> using optional parameters to
 UDP instrument
</p>
<h4 class="subsubheading" id="Inputs-113">Inputs</h4>
<p><var class="var">obj</var> is a UDP object.<br>
<var class="var">template</var> Format template string.<br>
</p>
<h4 class="subsubheading" id="Outputs-113">Outputs</h4>
<p><var class="var">numbytes</var> is the number of bytes written to the device
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fudp_002ffread">
<h4 class="subsection">3.13.7 @octave_udp/fread</h4>
<a class="index-entry-id" id="index-fread-7"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fread-46"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-47"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-48"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>, <var class="var">precision</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-49"><span class="category-def">Function File: </span><code class="def-type">[<var class="var">data</var>,<var class="var">count</var>] =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, ...)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-50"><span class="category-def">Function File: </span><code class="def-type">[<var class="var">data</var>,<var class="var">count</var>,<var class="var">errmsg</var>] =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, ...)</code></dt>
<dd><p>Reads <var class="var">data</var> from UDP instrument
</p>
<h4 class="subsubheading" id="Inputs-114">Inputs</h4>
<p><var class="var">obj</var> is a UDP object.<br>
<var class="var">size</var> Number of values to read. (Default: 100).<br>
<var class="var">precision</var> precision of data.<br>
</p>
<h4 class="subsubheading" id="Outputs-114">Outputs</h4>
<p><var class="var">data</var> data values.<br>
<var class="var">count</var> number of values read.<br>
<var class="var">errmsg</var> read operation error message.<br>
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fudp_002ffwrite">
<h4 class="subsection">3.13.8 @octave_udp/fwrite</h4>
<a class="index-entry-id" id="index-fwrite-7"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fwrite-28"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fwrite-29"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>, <var class="var">precision</var>)</code></dt>
<dd><p>Writes <var class="var">data</var> to UDP instrument
</p>
<h4 class="subsubheading" id="Inputs-115">Inputs</h4>
<p><var class="var">obj</var> is a UDP object.<br>
<var class="var">data</var> data to write.<br>
<var class="var">precision</var> precision of data.<br>
</p>
<h4 class="subsubheading" id="Outputs-115">Outputs</h4>
<p>returns number of bytes written.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fudp_002fget">
<h4 class="subsection">3.13.9 @octave_udp/get</h4>
<a class="index-entry-id" id="index-get-8"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-get-26"><span class="category-def">Function File: </span><code class="def-type"><var class="var">struct</var> =</code> <strong class="def-name">get</strong> <code class="def-code-arguments">(<var class="var">udp</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-get-27"><span class="category-def">Function File: </span><code class="def-type"><var class="var">field</var> =</code> <strong class="def-name">get</strong> <code class="def-code-arguments">(<var class="var">udp</var>, <var class="var">property</var>)</code></dt>
<dd><p>Get the properties of udp object.
</p>
<h4 class="subsubheading" id="Inputs-116">Inputs</h4>
<p><var class="var">udp</var> - instance of <var class="var">octave_udp</var> class.<br>
</p>
<p><var class="var">property</var> - name of property.<br>
</p>
<h4 class="subsubheading" id="Outputs-116">Outputs</h4>
<p>When <var class="var">property</var> was specified, return the value of that property.<br>
 otherwise return the values of all properties as a structure.<br>
</p>
<p><strong class="strong">See also:</strong> @octave_udp/set.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fudp_002fread">
<h4 class="subsection">3.13.10 @octave_udp/read</h4>
<a class="index-entry-id" id="index-read-6"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-read-25"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">read</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-read-26"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">read</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-read-27"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">read</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>, <var class="var">datatype</var>)</code></dt>
<dd><p>Reads <var class="var">data</var> from UDP instrument
</p>
<h4 class="subsubheading" id="Inputs-117">Inputs</h4>
<p><var class="var">obj</var> is a UDP object.<br>
<var class="var">size</var> Number of values to read. (Default: BytesAvailable).<br>
<var class="var">datatype</var> datatype of data.<br>
</p>
<h4 class="subsubheading" id="Outputs-117">Outputs</h4>
<p><var class="var">data</var> data read.<br>
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fudp_002fset">
<h4 class="subsection">3.13.11 @octave_udp/set</h4>
<a class="index-entry-id" id="index-set-8"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-_0028obj_002c-16"><span class="category-def">Function File: </span><code class="def-type">set</code> <strong class="def-name">(<var class="var">obj</var>,</strong> <code class="def-code-arguments"><var class="var">property</var>,<var class="var">value</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-_0028obj_002c-17"><span class="category-def">Function File: </span><code class="def-type">set</code> <strong class="def-name">(<var class="var">obj</var>,</strong> <code class="def-code-arguments"><var class="var">property</var>,<var class="var">value</var>,&hellip;)</code></dt>
<dd><p>Set the properties of udp object.
</p>
<h4 class="subsubheading" id="Inputs-118">Inputs</h4>
<p><var class="var">obj</var> - instance of <var class="var">octave_udp</var> class.<br>
<var class="var">property</var> - name of property.<br>
</p>
<p>If <var class="var">property</var> is a cell so must be <var class="var">value</var>, it sets the values of
 all matching properties.
</p>
<p>The function also accepts property-value pairs.
</p>
<h4 class="subsubheading" id="Properties-18">Properties</h4>
<dl class="table">
<dt><var class="var">&rsquo;name&rsquo;</var></dt>
<dd><p>Set the name for the udp socket.
</p>
</dd>
<dt><var class="var">&rsquo;remotehost&rsquo;</var></dt>
<dd><p>Set the remote host name for the udp socket.
</p>
</dd>
<dt><var class="var">&rsquo;remoteport&rsquo;</var></dt>
<dd><p>Set the remote port for the udp socket.
</p>
</dd>
<dt><var class="var">&rsquo;timeout&rsquo;</var></dt>
<dd><p>Set the timeout value in seconds. Value of -1 means a
 blocking call.
</p>
</dd>
</dl>
<h4 class="subsubheading" id="Outputs-118">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> @octave_udp/get.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fudp_002fwrite">
<h4 class="subsection">3.13.12 @octave_udp/write</h4>
<a class="index-entry-id" id="index-write-6"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-write-17"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">write</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-write-18"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">write</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>, <var class="var">destinationAddress</var>, <var class="var">destinationPort</var>))</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-write-19"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">write</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>, <var class="var">datatype</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-write-20"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">write</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>, <var class="var">datatype</var>, <var class="var">destinationAddress</var>, <var class="var">destinationPort</var>)</code></dt>
<dd><p>Writes <var class="var">data</var> to UDP instrument
</p>
<h4 class="subsubheading" id="Inputs-119">Inputs</h4>
<p><var class="var">obj</var> is a UDP object.<br>
<var class="var">data</var> data to write.<br>
<var class="var">datatype</var> datatype of data. If not specified defaults to uint8.<br>
<var class="var">destinationAddress</var> ipaddress to send to. If not specified, use the remote address.<br>
<var class="var">destinationPort</var> port to send to. If not specified, use the remote port.<br>
</p>
<h4 class="subsubheading" id="Outputs-119">Outputs</h4>
<p>returns number of bytes written.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="udp">
<h4 class="subsection">3.13.13 udp</h4>
<a class="index-entry-id" id="index-udp"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-udp-1"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">udp</var> =</code> <strong class="def-name">udp</strong> <code class="def-code-arguments">()</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-udp-2"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">udp</var> =</code> <strong class="def-name">udp</strong> <code class="def-code-arguments">(<var class="var">remoteipaddress</var>, <var class="var">remoteport</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-udp-3"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">udp</var> =</code> <strong class="def-name">udp</strong> <code class="def-code-arguments">(<var class="var">remoteipaddress</var>, <var class="var">remoteport</var>, [<var class="var">propertyname</var>, <var class="var">propertyvalue</var> ...])</code></dt>
<dd>
<p>Open udp interface.
</p>
<h4 class="subsubheading" id="Inputs-120">Inputs</h4>
<p><var class="var">remoteipaddress</var> - the ip address of type String. If omitted defaults to &rsquo;127.0.0.1&rsquo;.<br> 
<var class="var">remoteport</var> - the port number to connect. If omitted defaults to 23.<br> 
<var class="var">localport</var> - the local port number to bind. If omitted defaults to 0<br> 
<var class="var">propertyname</var>, <var class="var">propertyvalue</var> - property name/value pair
</p>
<h4 class="subsubheading" id="Outputs-120">Outputs</h4>
<p>The udp() shall return instance of <var class="var">octave_udp</var> class as the result <var class="var">udp</var>.
</p>
<h4 class="subsubheading" id="Properties-19">Properties</h4>
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
</div>
<div class="subsection-level-extent" id="udp_005fclose">
<h4 class="subsection">3.13.14 udp_close</h4>
<a class="index-entry-id" id="index-udp_005fclose"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-udp_005fclose-1"><span class="category-def">Loadable Function: </span><strong class="def-name">udp_close</strong> <code class="def-code-arguments">(<var class="var">udp</var>)</code></dt>
<dd>
<p>Close the interface and release a file descriptor.
</p>
<h4 class="subsubheading" id="Inputs-121">Inputs</h4>
<p><var class="var">udp</var> - instance of <var class="var">octave_udp</var> class.
</p>
<h4 class="subsubheading" id="Inputs-122">Inputs</h4>
<p>None
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="udp_005fdemo">
<h4 class="subsection">3.13.15 udp_demo</h4>
<a class="index-entry-id" id="index-udp_005fdemo"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-udp_005fdemo-1"><span class="category-def">Function File: </span><code class="def-type"><var class="var">result</var> =</code> <strong class="def-name">udp_demo</strong> <code class="def-code-arguments">()</code></dt>
<dd><p>Run test SNTP demonstration for udp class
</p>
<p><strong class="strong">See also:</strong> udp.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="udp_005fread">
<h4 class="subsection">3.13.16 udp_read</h4>
<a class="index-entry-id" id="index-udp_005fread"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-udp_005fread-1"><span class="category-def">Loadable Function: </span><code class="def-type">[<var class="var">data</var>, <var class="var">count</var>] =</code> <strong class="def-name">udp_read</strong> <code class="def-code-arguments">(<var class="var">udp</var>, <var class="var">n</var>, <var class="var">timeout</var>)</code></dt>
<dd>
<p>Read from udp interface.
</p>
<h4 class="subsubheading" id="Inputs-123">Inputs</h4>
<p><var class="var">udp</var> - instance of <var class="var">octave_udp</var> class.<br>
<var class="var">n</var> - number of bytes to attempt to read of type Integer<br>
<var class="var">timeout</var> - timeout in ms if different from default of type Integer
</p>
<h4 class="subsubheading" id="Outputs-121">Outputs</h4>
<p>The udp_read() shall return number of bytes successfully read in <var class="var">count</var> as Integer and the bytes themselves in <var class="var">data</var> as uint8 array.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="udp_005ftimeout">
<h4 class="subsection">3.13.17 udp_timeout</h4>
<a class="index-entry-id" id="index-udp_005ftimeout"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-udp_005ftimeout-1"><span class="category-def">Loadable Function: </span><strong class="def-name">udp_timeout</strong> <code class="def-code-arguments">(<var class="var">udp</var>, <var class="var">timeout</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-udp_005ftimeout-2"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">t</var> =</code> <strong class="def-name">udp_timeout</strong> <code class="def-code-arguments">(<var class="var">udp</var>)</code></dt>
<dd>
<p>Set new or get existing udp interface timeout parameter used for udp_read() requests. The timeout value is specified in milliseconds.
</p>
<h4 class="subsubheading" id="Inputs-124">Inputs</h4>
<p><var class="var">udp</var> - instance of <var class="var">octave_udp</var> class.<br>
<var class="var">timeout</var> - udp_read() timeout value in milliseconds. Value of -1 means a blocking call.
</p>
<h4 class="subsubheading" id="Outputs-122">Outputs</h4>
<p>If <var class="var">timeout</var> parameter is omitted, the udp_timeout() shall return current timeout value as the result <var class="var">t</var>.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="udp_005fwrite">
<h4 class="subsection">3.13.18 udp_write</h4>
<a class="index-entry-id" id="index-udp_005fwrite"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-udp_005fwrite-1"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">n</var> =</code> <strong class="def-name">udp_write</strong> <code class="def-code-arguments">(<var class="var">udp</var>, <var class="var">data</var>)</code></dt>
<dd>
<p>Write data to a udp interface.
</p>
<h4 class="subsubheading" id="Inputs-125">Inputs</h4>
<p><var class="var">udp</var> - instance of <var class="var">octave_udp</var> class.<br>
<var class="var">data</var> - data to be written to the udp interface. Can be either of String or uint8 type.
</p>
<h4 class="subsubheading" id="Outputs-123">Outputs</h4>
<p>Upon successful completion, udp_write() shall return the number of bytes written as the result <var class="var">n</var>.
</p></dd></dl>
<hr>
</div>
</div>
<div class="section-level-extent" id="UDP-Port">
<h3 class="section" id="UDP-Port-2">3.14 UDP Port</h3>
<a class="index-entry-id" id="index-UDP-Port"></a>
<div class="subsection-level-extent" id="g_t_0040octave_005fudpport_002fconfigureMulticast">
<h4 class="subsection">3.14.1 @octave_udpport/configureMulticast</h4>
<a class="index-entry-id" id="index-configureMulticast"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-configureMulticast_0028_0028dev_002c"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">configureMulticast((<var class="var">dev</var>,</strong> <code class="def-code-arguments"><var class="var">address</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-configureMulticast_0028_0028dev_002c-1"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">configureMulticast((<var class="var">dev</var>,</strong> <code class="def-code-arguments"><var class="var">&quot;off&quot;</var>)</code></dt>
<dd><p>Configure udpport device to receive multicast data
</p>
<h4 class="subsubheading" id="Inputs-126">Inputs</h4>
<p><var class="var">dev</var> - open udpport device
</p>
<p>If <var class="var">address</var>  is &rsquo;off&rsquo; disable udp multicast. Otherwise it is the multicast address to use.
</p>
<h4 class="subsubheading" id="Outputs-124">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> udpport.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fudpport_002fconfigureTerminator">
<h4 class="subsection">3.14.2 @octave_udpport/configureTerminator</h4>
<a class="index-entry-id" id="index-configureTerminator-3"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-configureTerminator-10"><span class="category-def">Function File: </span><strong class="def-name">configureTerminator</strong> <code class="def-code-arguments">(<var class="var">udp</var>, <var class="var">term</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-configureTerminator-11"><span class="category-def">Function File: </span><strong class="def-name">configureTerminator</strong> <code class="def-code-arguments">(<var class="var">udp</var>, <var class="var">readterm</var>, <var class="var">writeterm</var>)</code></dt>
<dd><p>Set terminator for ASCII string manipulation
</p>
<h4 class="subsubheading" id="Inputs-127">Inputs</h4>
<p><var class="var">udp</var> - udpport object<br>
<var class="var">term</var> - terminal value for both read and write<br>
<var class="var">readterm</var> = terminal value type for read data<br>
<var class="var">writeterm</var> = terminal value for written data<br>
</p>
<p>The terminal can be either strings &quot;cr&quot;, &quot;lf&quot; (default), &quot;lf/cr&quot; or an integer between 0 to 255.
</p>
<h4 class="subsubheading" id="Outputs-125">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> udpport.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fudpport_002fflush">
<h4 class="subsection">3.14.3 @octave_udpport/flush</h4>
<a class="index-entry-id" id="index-flush-5"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-flush-21"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">flush</strong> <code class="def-code-arguments">(<var class="var">dev</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-flush-22"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">flush</strong> <code class="def-code-arguments">(<var class="var">dev</var>, &quot;input&quot;)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-flush-23"><span class="category-def">: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">flush</strong> <code class="def-code-arguments">(<var class="var">dev</var>, &quot;output&quot;)</code></dt>
<dd><p>Flush the udpport socket buffers
</p>
<h4 class="subsubheading" id="Inputs-128">Inputs</h4>
<p><var class="var">dev</var> - open udpport device
</p>
<p>If an additional parameter is provided of &quot;input&quot; or &quot;output&quot;,
 then only the input or output buffer will be flushed
</p>
<h4 class="subsubheading" id="Outputs-126">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> udpport.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fudpport_002ffprintf">
<h4 class="subsection">3.14.4 @octave_udpport/fprintf</h4>
<a class="index-entry-id" id="index-fprintf-5"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fprintf-14"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fprintf</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">template</var> ...)</code></dt>
<dd><p>Writes formatted string <var class="var">template</var> using optional parameters to
 UDP instrument
</p>
<h4 class="subsubheading" id="Inputs-129">Inputs</h4>
<p><var class="var">obj</var> is a UDPPort object.<br>
<var class="var">template</var> Format template string.<br>
</p>
<h4 class="subsubheading" id="Outputs-127">Outputs</h4>
<p><var class="var">numbytes</var> is the number of bytes written to the device
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fudpport_002ffread">
<h4 class="subsection">3.14.5 @octave_udpport/fread</h4>
<a class="index-entry-id" id="index-fread-8"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fread-51"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-52"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-53"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>, <var class="var">precision</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-54"><span class="category-def">Function File: </span><code class="def-type">[<var class="var">data</var>,<var class="var">count</var>] =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, ...)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-55"><span class="category-def">Function File: </span><code class="def-type">[<var class="var">data</var>,<var class="var">count</var>,<var class="var">errmsg</var>] =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, ...)</code></dt>
<dd><p>Reads <var class="var">data</var> from UDP instrument
</p>
<h4 class="subsubheading" id="Inputs-130">Inputs</h4>
<p><var class="var">obj</var> is a UDP port object.<br>
<var class="var">size</var> Number of values to read. (Default: 100).<br>
<var class="var">precision</var> precision of data.<br>
</p>
<h4 class="subsubheading" id="Outputs-128">Outputs</h4>
<p><var class="var">data</var> data values.<br>
<var class="var">count</var> number of values read.<br>
<var class="var">errmsg</var> read operation error message.<br>
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fudpport_002ffwrite">
<h4 class="subsection">3.14.6 @octave_udpport/fwrite</h4>
<a class="index-entry-id" id="index-fwrite-8"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fwrite-30"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fwrite-31"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>, <var class="var">precision</var>)</code></dt>
<dd><p>Writes <var class="var">data</var> to UDP instrument
</p>
<h4 class="subsubheading" id="Inputs-131">Inputs</h4>
<p><var class="var">obj</var> is a UDP port object.<br>
<var class="var">data</var> data to write.<br>
<var class="var">precision</var> precision of data.<br>
</p>
<h4 class="subsubheading" id="Outputs-129">Outputs</h4>
<p>returns number of bytes written.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fudpport_002fget">
<h4 class="subsection">3.14.7 @octave_udpport/get</h4>
<a class="index-entry-id" id="index-get-9"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-get-28"><span class="category-def">Function File: </span><code class="def-type"><var class="var">struct</var> =</code> <strong class="def-name">get</strong> <code class="def-code-arguments">(<var class="var">udpport</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-get-29"><span class="category-def">Function File: </span><code class="def-type"><var class="var">field</var> =</code> <strong class="def-name">get</strong> <code class="def-code-arguments">(<var class="var">udpport</var>, <var class="var">property</var>)</code></dt>
<dd><p>Get the properties of udpport object.
</p>
<h4 class="subsubheading" id="Inputs-132">Inputs</h4>
<p><var class="var">udpport</var> - instance of <var class="var">octave_udpport</var> class.<br>
</p>
<p><var class="var">property</var> - name of property.<br>
</p>
<h4 class="subsubheading" id="Outputs-130">Outputs</h4>
<p>When <var class="var">property</var> was specified, return the value of that property.<br>
 otherwise return the values of all properties as a structure.<br>
</p>
<p><strong class="strong">See also:</strong> @octave_udpport/set.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fudpport_002fread">
<h4 class="subsection">3.14.8 @octave_udpport/read</h4>
<a class="index-entry-id" id="index-read-7"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-read-28"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">read</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-read-29"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">read</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-read-30"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">read</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>, <var class="var">datatype</var>)</code></dt>
<dd><p>Reads <var class="var">data</var> from UDP instrument
</p>
<h4 class="subsubheading" id="Inputs-133">Inputs</h4>
<p><var class="var">obj</var> is a UDP object.<br>
<var class="var">size</var> Number of values to read. (Default: BytesAvailable).<br>
<var class="var">datatype</var> datatype of data.<br>
</p>
<h4 class="subsubheading" id="Outputs-131">Outputs</h4>
<p><var class="var">data</var> data read.<br>
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fudpport_002fset">
<h4 class="subsection">3.14.9 @octave_udpport/set</h4>
<a class="index-entry-id" id="index-set-9"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-_0028obj_002c-18"><span class="category-def">Function File: </span><code class="def-type">set</code> <strong class="def-name">(<var class="var">obj</var>,</strong> <code class="def-code-arguments"><var class="var">property</var>,<var class="var">value</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-_0028obj_002c-19"><span class="category-def">Function File: </span><code class="def-type">set</code> <strong class="def-name">(<var class="var">obj</var>,</strong> <code class="def-code-arguments"><var class="var">property</var>,<var class="var">value</var>,&hellip;)</code></dt>
<dd><p>Set the properties of udpport object.
</p>
<h4 class="subsubheading" id="Inputs-134">Inputs</h4>
<p><var class="var">obj</var> - instance of <var class="var">octave_udpport</var> class.<br>
<var class="var">property</var> - name of property.<br>
</p>
<p>If <var class="var">property</var> is a cell so must be <var class="var">value</var>, it sets the values of
 all matching properties.
</p>
<p>The function also accepts property-value pairs.
</p>
<h4 class="subsubheading" id="Properties-20">Properties</h4>
<dl class="table">
<dt><var class="var">&rsquo;Name&rsquo;</var></dt>
<dd><p>Set the name for the udpport socket.
</p>
</dd>
<dt><var class="var">&rsquo;UserData&rsquo;</var></dt>
<dd><p>Set the user data of the object.
</p>
</dd>
<dt><var class="var">&rsquo;Tag&rsquo;</var></dt>
<dd><p>Set the user tag to identify the port.
</p>
</dd>
<dt><var class="var">&rsquo;Timeout&rsquo;</var></dt>
<dd><p>Set the timeout value in seconds. Value of -1 means a
 blocking call.
</p>
</dd>
</dl>
<h4 class="subsubheading" id="Outputs-132">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> @octave_udpport/get.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fudpport_002fwrite">
<h4 class="subsection">3.14.10 @octave_udpport/write</h4>
<a class="index-entry-id" id="index-write-7"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-write-21"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">write</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-write-22"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">write</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>, <var class="var">destinationAddress</var>, <var class="var">destinationPort</var>))</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-write-23"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">write</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>, <var class="var">datatype</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-write-24"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">write</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>, <var class="var">datatype</var>, <var class="var">destinationAddress</var>, <var class="var">destinationPort</var>)</code></dt>
<dd><p>Writes <var class="var">data</var> to UDP instrument
</p>
<h4 class="subsubheading" id="Inputs-135">Inputs</h4>
<p><var class="var">obj</var> is a UDPPort object.<br>
<var class="var">data</var> data to write.<br>
<var class="var">datatype</var> datatype of data. If not specified defaults to uint8.<br>
<var class="var">destinationAddress</var> ipaddress to send to. If not specified, use the previously used remote address.<br>
<var class="var">destinationPort</var> port to send to. If not specified, use the remote port.<br>
</p>
<h4 class="subsubheading" id="Outputs-133">Outputs</h4>
<p>returns number of bytes written.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fudpport_002fwriteline">
<h4 class="subsection">3.14.11 @octave_udpport/writeline</h4>
<a class="index-entry-id" id="index-writeline-1"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-writeline-3"><span class="category-def">: </span><strong class="def-name">writeline</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">data</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-writeline-4"><span class="category-def">: </span><strong class="def-name">writeline</strong> <code class="def-code-arguments">(<var class="var">dev</var>, <var class="var">data</var>, <var class="var">destaddr</var>, <var class="var">destport</var>)</code></dt>
<dd><p>Write data to a udpport including terminator value
</p>
<h4 class="subsubheading" id="Inputs-136">Inputs</h4>
<p><var class="var">dev</var> - connected device
</p>
<p><var class="var">data</var> - ASCII data to write
</p>
<p><var class="var">destaddr</var> - Destination address
</p>
<p><var class="var">destport</var> - Destination port
</p>
<p>Where the address and port is not specified, the previously used address and port is used.
</p>
<h4 class="subsubheading" id="Outputs-134">Outputs</h4>
<p>None
</p>
<p><strong class="strong">See also:</strong> flushoutput.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="udpport">
<h4 class="subsection">3.14.12 udpport</h4>
<a class="index-entry-id" id="index-udpport"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-udpport-1"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">udp</var> =</code> <strong class="def-name">udpport</strong> <code class="def-code-arguments">()</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-udpport-2"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">udp</var> =</code> <strong class="def-name">udpport</strong> <code class="def-code-arguments">(<var class="var">propertyname</var>, <var class="var">propertyvalue</var> ...)</code></dt>
<dd>
<p>Open udpport interface.
</p>
<h4 class="subsubheading" id="Inputs-137">Inputs</h4>
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
<h4 class="subsubheading" id="Outputs-135">Outputs</h4>
<p>The udpport() shall return instance of <var class="var">octave_udp</var> class as the result <var class="var">udp</var>.
</p>
<h4 class="subsubheading" id="Properties-21">Properties</h4>
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
<hr>
</div>
</div>
<div class="section-level-extent" id="USBTMC">
<h3 class="section" id="USBTMC-1">3.15 USBTMC</h3>
<a class="index-entry-id" id="index-USBTMC"></a>
<div class="subsection-level-extent" id="g_t_0040octave_005fusbtmc_002ffclose">
<h4 class="subsection">3.15.1 @octave_usbtmc/fclose</h4>
<a class="index-entry-id" id="index-fclose-7"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fclose-16"><span class="category-def">Function File: </span><code class="def-type"><var class="var">res</var> =</code> <strong class="def-name">fclose</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dd><p>Closes USBTMC connection <var class="var">obj</var>
</p>
<h4 class="subsubheading" id="Inputs-138">Inputs</h4>
<p><var class="var">obj</var> is a usbtmc object.<br>
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fusbtmc_002ffopen">
<h4 class="subsection">3.15.2 @octave_usbtmc/fopen</h4>
<a class="index-entry-id" id="index-fopen-7"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fopen-16"><span class="category-def">Function File: </span><code class="def-type"><var class="var">res</var> =</code> <strong class="def-name">fopen</strong> <code class="def-code-arguments">(<var class="var">obj</var>) (dummy)</code></dt>
<dd><p>Opens USBTMC connection <var class="var">obj</var>
 This currently is a dummy function to improve compatibility to MATLAB
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fusbtmc_002ffread">
<h4 class="subsection">3.15.3 @octave_usbtmc/fread</h4>
<a class="index-entry-id" id="index-fread-9"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fread-56"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-57"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-58"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>, <var class="var">precision</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-59"><span class="category-def">Function File: </span><code class="def-type">[<var class="var">data</var>,<var class="var">count</var>] =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, ...)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-60"><span class="category-def">Function File: </span><code class="def-type">[<var class="var">data</var>,<var class="var">count</var>,<var class="var">errmsg</var>] =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, ...)</code></dt>
<dd><p>Reads <var class="var">data</var> from usbtmc instrument
</p>
<h4 class="subsubheading" id="Inputs-139">Inputs</h4>
<p><var class="var">obj</var> is a usbtmc object.<br>
<var class="var">size</var> Number of values to read. (Default: 100).<br>
<var class="var">precision</var> precision of data.<br>
</p>
<h4 class="subsubheading" id="Outputs-136">Outputs</h4>
<p><var class="var">data</var> The read data.<br>
<var class="var">count</var> values read.<br>
<var class="var">errmsg</var> read operation error message.<br>
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fusbtmc_002ffwrite">
<h4 class="subsection">3.15.4 @octave_usbtmc/fwrite</h4>
<a class="index-entry-id" id="index-fwrite-9"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fwrite-32"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fwrite-33"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>, <var class="var">precision</var>)</code></dt>
<dd><p>Writes <var class="var">data</var> to an usbtmc instrument
</p>
<h4 class="subsubheading" id="Inputs-140">Inputs</h4>
<p><var class="var">obj</var> is a usbtmc object.<br>
<var class="var">data</var> data to write.<br>
<var class="var">precision</var> precision of data.<br>
</p>
<h4 class="subsubheading" id="Outputs-137">Outputs</h4>
<p>returns number of bytes written.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="usbtmc">
<h4 class="subsection">3.15.5 usbtmc</h4>
<a class="index-entry-id" id="index-usbtmc"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-usbtmc-1"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">usbtmc</var> =</code> <strong class="def-name">usbtmc</strong> <code class="def-code-arguments">(<var class="var">path</var>)</code></dt>
<dd>
<p>Open usbtmc interface.
</p>
<h4 class="subsubheading" id="Inputs-141">Inputs</h4>
<p><var class="var">path</var> - the interface path of type String. If omitted defaults to &rsquo;/dev/usbtmc0&rsquo;.
</p>
<h4 class="subsubheading" id="Outputs-138">Outputs</h4>
<p>The usbtmc() shall return instance of <var class="var">octave_usbtmc</var> class as the result <var class="var">usbtmc</var>.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="usbtmc_005fclose">
<h4 class="subsection">3.15.6 usbtmc_close</h4>
<a class="index-entry-id" id="index-usbtmc_005fclose"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-usbtmc_005fclose-1"><span class="category-def">Loadable Function: </span><strong class="def-name">usbtmc_close</strong> <code class="def-code-arguments">(<var class="var">usbtmc</var>)</code></dt>
<dd>
<p>Close the interface and release a file descriptor.
</p>
<h4 class="subsubheading" id="Inputs-142">Inputs</h4>
<p><var class="var">usbtmc</var> - instance of <var class="var">octave_usbtmc</var> class.
</p><h4 class="subsubheading" id="Outputs-139">Outputs</h4>
<p>None
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="usbtmc_005fread">
<h4 class="subsection">3.15.7 usbtmc_read</h4>
<a class="index-entry-id" id="index-usbtmc_005fread"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-usbtmc_005fread-1"><span class="category-def">Loadable Function: </span><code class="def-type">[<var class="var">data</var>, <var class="var">count</var>] =</code> <strong class="def-name">usbtmc_read</strong> <code class="def-code-arguments">(<var class="var">usbtmc</var>, <var class="var">n</var>)</code></dt>
<dd>
<p>Read from usbtmc slave device.
</p>
<h4 class="subsubheading" id="Inputs-143">Inputs</h4>
<p><var class="var">usbtmc</var> - instance of <var class="var">octave_usbtmc</var> class.<br>
<var class="var">n</var> - number of bytes to attempt to read of type Integer.
</p>
<h4 class="subsubheading" id="Outputs-140">Outputs</h4>
<p><var class="var">count</var> - the number of bytes successfully read as an Integer.<br>
<var class="var">data</var> - the read bytes as a uint8 array.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="usbtmc_005fwrite">
<h4 class="subsection">3.15.8 usbtmc_write</h4>
<a class="index-entry-id" id="index-usbtmc_005fwrite"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-usbtmc_005fwrite-1"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">n</var> =</code> <strong class="def-name">usbtmc_write</strong> <code class="def-code-arguments">(<var class="var">usbtmc</var>, <var class="var">data</var>)</code></dt>
<dd>
<p>Write data to a usbtmc slave device.
</p>
<h4 class="subsubheading" id="Inputs-144">Inputs</h4>
<p><var class="var">usbtmc</var> - instance of <var class="var">octave_usbtmc</var> class.<br>
<var class="var">data</var> - data, of type uint8, to be written to the slave device.
</p>
<h4 class="subsubheading" id="Outputs-141">Outputs</h4>
<p>Upon successful completion, usbtmc_write() shall return the number of bytes written as the result <var class="var">n</var>.
</p></dd></dl>
<hr>
</div>
</div>
<div class="section-level-extent" id="VXI11">
<h3 class="section" id="VXI11-1">3.16 VXI11</h3>
<a class="index-entry-id" id="index-VXI11"></a>
<div class="subsection-level-extent" id="g_t_0040octave_005fvxi11_002ffclose">
<h4 class="subsection">3.16.1 @octave_vxi11/fclose</h4>
<a class="index-entry-id" id="index-fclose-8"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fclose-17"><span class="category-def">Function File: </span><code class="def-type"><var class="var">res</var> =</code> <strong class="def-name">fclose</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dd><p>Closes VXI11 connection <var class="var">obj</var>
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fvxi11_002ffopen">
<h4 class="subsection">3.16.2 @octave_vxi11/fopen</h4>
<a class="index-entry-id" id="index-fopen-8"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fopen-17"><span class="category-def">Function File: </span><code class="def-type"><var class="var">res</var> =</code> <strong class="def-name">fopen</strong> <code class="def-code-arguments">(<var class="var">obj</var>) (dummy)</code></dt>
<dd><p>Opens VXI11 connection <var class="var">obj</var>
 This currently is a dummy function to improve compatibility to MATLAB
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fvxi11_002ffread">
<h4 class="subsection">3.16.3 @octave_vxi11/fread</h4>
<a class="index-entry-id" id="index-fread-10"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fread-61"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-62"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-63"><span class="category-def">Function File: </span><code class="def-type"><var class="var">data</var> =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">size</var>, <var class="var">precision</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-64"><span class="category-def">Function File: </span><code class="def-type">[<var class="var">data</var>,<var class="var">count</var>] =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, ...)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fread-65"><span class="category-def">Function File: </span><code class="def-type">[<var class="var">data</var>,<var class="var">count</var>,<var class="var">errmsg</var>] =</code> <strong class="def-name">fread</strong> <code class="def-code-arguments">(<var class="var">obj</var>, ...)</code></dt>
<dd><p>Reads <var class="var">data</var> from vxi11 instrument
</p>
<h4 class="subsubheading" id="Inputs-145">Inputs</h4>
<p><var class="var">obj</var> is a vxi11 object.<br>
<var class="var">size</var> Number of values to read. (Default: 100).<br>
<var class="var">precision</var> precision of data.<br>
</p>
<h4 class="subsubheading" id="Outputs-142">Outputs</h4>
<p><var class="var">data</var> The read data.<br>
<var class="var">count</var> values read.<br>
<var class="var">errmsg</var> read operation error message.<br>
</p>
</dd></dl>
</div>
<div class="subsection-level-extent" id="g_t_0040octave_005fvxi11_002ffwrite">
<h4 class="subsection">3.16.4 @octave_vxi11/fwrite</h4>
<a class="index-entry-id" id="index-fwrite-10"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-fwrite-34"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>)</code></dt>
<dt class="deftypefnx def-cmd-deftypefn" id="index-fwrite-35"><span class="category-def">Function File: </span><code class="def-type"><var class="var">numbytes</var> =</code> <strong class="def-name">fwrite</strong> <code class="def-code-arguments">(<var class="var">obj</var>, <var class="var">data</var>, <var class="var">precision</var>)</code></dt>
<dd><p>Writes <var class="var">data</var> to vxi11 instrument
</p>
<h4 class="subsubheading" id="Inputs-146">Inputs</h4>
<p><var class="var">obj</var> is a vxi11 object.<br>
<var class="var">data</var> data to write.<br>
<var class="var">precision</var> precision of data.<br>
</p>
<h4 class="subsubheading" id="Outputs-143">Outputs</h4>
<p>returns number of bytes written.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="vxi11">
<h4 class="subsection">3.16.5 vxi11</h4>
<a class="index-entry-id" id="index-vxi11"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-vxi11-1"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">vxi11</var> =</code> <strong class="def-name">vxi11</strong> <code class="def-code-arguments">(<var class="var">ip</var>,<var class="var">instr</var>)</code></dt>
<dd>
<p>Open vxi11 interface.
</p>
<p><var class="var">ip</var> - the ip address of type String. If omitted defaults to &rsquo;127.0.0.1&rsquo;.
<var class="var">instr</var> - the instrument name of type String. If omitted defaults to &rsquo;inst0&rsquo;.
</p>
<p>The vxi11() shall return instance of <var class="var">octave_vxi11</var> class as the result <var class="var">vxi11</var>.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="vxi11_005fclose">
<h4 class="subsection">3.16.6 vxi11_close</h4>
<a class="index-entry-id" id="index-vxi11_005fclose"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-vxi11_005fclose-1"><span class="category-def">Loadable Function: </span><strong class="def-name">vxi11_close</strong> <code class="def-code-arguments">(<var class="var">vxi11</var>)</code></dt>
<dd>
<p>Close the interface and release a file descriptor.
</p>
<p><var class="var">vxi11</var> - instance of <var class="var">octave_vxi11</var> class.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="vxi11_005fread">
<h4 class="subsection">3.16.7 vxi11_read</h4>
<a class="index-entry-id" id="index-vxi11_005fread"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-vxi11_005fread-1"><span class="category-def">Loadable Function: </span><code class="def-type">[<var class="var">data</var>, <var class="var">count</var>] =</code> <strong class="def-name">vxi11_read</strong> <code class="def-code-arguments">(<var class="var">vxi11</var>, <var class="var">n</var>)</code></dt>
<dd>
<p>Read from vxi11 slave device.
</p>
<p><var class="var">vxi11</var> - instance of <var class="var">octave_vxi11</var> class.<br>
<var class="var">n</var> - number of bytes to attempt to read of type Integer.
</p>
<p>The vxi11_read() shall return number of bytes successfully read in <var class="var">count</var> as Integer and the bytes themselves in <var class="var">data</var> as uint8 array.
</p></dd></dl>
</div>
<div class="subsection-level-extent" id="vxi11_005fwrite">
<h4 class="subsection">3.16.8 vxi11_write</h4>
<a class="index-entry-id" id="index-vxi11_005fwrite"></a>
<dl class="first-deftypefn">
<dt class="deftypefn" id="index-vxi11_005fwrite-1"><span class="category-def">Loadable Function: </span><code class="def-type"><var class="var">n</var> =</code> <strong class="def-name">vxi11_write</strong> <code class="def-code-arguments">(<var class="var">vxi11</var>, <var class="var">data</var>)</code></dt>
<dd>
<p>Write data to a vxi11 slave device.
</p>
<p><var class="var">vxi11</var> - instance of <var class="var">octave_vxi11</var> class.<br>
<var class="var">data</var> - data to be written to the slave device. Can be either of String or uint8 type.
</p>
<p>Upon successful completion, vxi11_write() shall return the number of bytes written as the result <var class="var">n</var>.
</p></dd></dl>
<hr>
</div>
</div>
</div>
<div class="appendix-level-extent" id="Copying">
<h2 class="appendix" id="GNU-General-Public-License">Appendix A GNU General Public License</h2>
<a class="index-entry-id" id="index-warranty"></a>
<a class="index-entry-id" id="index-copyright"></a>
<div class="center">Version 3, 29 June 2007
</div>
<div class="display">
<pre class="display-preformatted">Copyright &copy; 2007 Free Software Foundation, Inc. <a class="url" href="http://fsf.org/">http://fsf.org/</a>
Everyone is permitted to copy and distribute verbatim copies of this
license document, but changing it is not allowed.
</pre></div>
<h3 class="heading" id="Preamble">Preamble</h3>
<p>The GNU General Public License is a free, copyleft license for
software and other kinds of works.
</p>
<p>The licenses for most software and other practical works are designed
to take away your freedom to share and change the works.  By contrast,
the GNU General Public License is intended to guarantee your freedom
to share and change all versions of a program&mdash;to make sure it remains
free software for all its users.  We, the Free Software Foundation,
use the GNU General Public License for most of our software; it
applies also to any other work released this way by its authors.  You
can apply it to your programs, too.
</p>
<p>When we speak of free software, we are referring to freedom, not
price.  Our General Public Licenses are designed to make sure that you
have the freedom to distribute copies of free software (and charge for
them if you wish), that you receive source code or can get it if you
want it, that you can change the software or use pieces of it in new
free programs, and that you know you can do these things.
</p>
<p>To protect your rights, we need to prevent others from denying you
these rights or asking you to surrender the rights.  Therefore, you
have certain responsibilities if you distribute copies of the
software, or if you modify it: responsibilities to respect the freedom
of others.
</p>
<p>For example, if you distribute copies of such a program, whether
gratis or for a fee, you must pass on to the recipients the same
freedoms that you received.  You must make sure that they, too,
receive or can get the source code.  And you must show them these
terms so they know their rights.
</p>
<p>Developers that use the GNU GPL protect your rights with two steps:
(1) assert copyright on the software, and (2) offer you this License
giving you legal permission to copy, distribute and/or modify it.
</p>
<p>For the developers&rsquo; and authors&rsquo; protection, the GPL clearly explains
that there is no warranty for this free software.  For both users&rsquo; and
authors&rsquo; sake, the GPL requires that modified versions be marked as
changed, so that their problems will not be attributed erroneously to
authors of previous versions.
</p>
<p>Some devices are designed to deny users access to install or run
modified versions of the software inside them, although the
manufacturer can do so.  This is fundamentally incompatible with the
aim of protecting users&rsquo; freedom to change the software.  The
systematic pattern of such abuse occurs in the area of products for
individuals to use, which is precisely where it is most unacceptable.
Therefore, we have designed this version of the GPL to prohibit the
practice for those products.  If such problems arise substantially in
other domains, we stand ready to extend this provision to those
domains in future versions of the GPL, as needed to protect the
freedom of users.
</p>
<p>Finally, every program is threatened constantly by software patents.
States should not allow patents to restrict development and use of
software on general-purpose computers, but in those that do, we wish
to avoid the special danger that patents applied to a free program
could make it effectively proprietary.  To prevent this, the GPL
assures that patents cannot be used to render the program non-free.
</p>
<p>The precise terms and conditions for copying, distribution and
modification follow.
</p>
<h3 class="heading" id="TERMS-AND-CONDITIONS">TERMS AND CONDITIONS</h3>
<ol class="enumerate" start="0">
<li> Definitions.
<p>&ldquo;This License&rdquo; refers to version 3 of the GNU General Public License.
</p>
<p>&ldquo;Copyright&rdquo; also means copyright-like laws that apply to other kinds
of works, such as semiconductor masks.
</p>
<p>&ldquo;The Program&rdquo; refers to any copyrightable work licensed under this
License.  Each licensee is addressed as &ldquo;you&rdquo;.  &ldquo;Licensees&rdquo; and
&ldquo;recipients&rdquo; may be individuals or organizations.
</p>
<p>To &ldquo;modify&rdquo; a work means to copy from or adapt all or part of the work
in a fashion requiring copyright permission, other than the making of
an exact copy.  The resulting work is called a &ldquo;modified version&rdquo; of
the earlier work or a work &ldquo;based on&rdquo; the earlier work.
</p>
<p>A &ldquo;covered work&rdquo; means either the unmodified Program or a work based
on the Program.
</p>
<p>To &ldquo;propagate&rdquo; a work means to do anything with it that, without
permission, would make you directly or secondarily liable for
infringement under applicable copyright law, except executing it on a
computer or modifying a private copy.  Propagation includes copying,
distribution (with or without modification), making available to the
public, and in some countries other activities as well.
</p>
<p>To &ldquo;convey&rdquo; a work means any kind of propagation that enables other
parties to make or receive copies.  Mere interaction with a user
through a computer network, with no transfer of a copy, is not
conveying.
</p>
<p>An interactive user interface displays &ldquo;Appropriate Legal Notices&rdquo; to
the extent that it includes a convenient and prominently visible
feature that (1) displays an appropriate copyright notice, and (2)
tells the user that there is no warranty for the work (except to the
extent that warranties are provided), that licensees may convey the
work under this License, and how to view a copy of this License.  If
the interface presents a list of user commands or options, such as a
menu, a prominent item in the list meets this criterion.
</p>
</li><li> Source Code.
<p>The &ldquo;source code&rdquo; for a work means the preferred form of the work for
making modifications to it.  &ldquo;Object code&rdquo; means any non-source form
of a work.
</p>
<p>A &ldquo;Standard Interface&rdquo; means an interface that either is an official
standard defined by a recognized standards body, or, in the case of
interfaces specified for a particular programming language, one that
is widely used among developers working in that language.
</p>
<p>The &ldquo;System Libraries&rdquo; of an executable work include anything, other
than the work as a whole, that (a) is included in the normal form of
packaging a Major Component, but which is not part of that Major
Component, and (b) serves only to enable use of the work with that
Major Component, or to implement a Standard Interface for which an
implementation is available to the public in source code form.  A
&ldquo;Major Component&rdquo;, in this context, means a major essential component
(kernel, window system, and so on) of the specific operating system
(if any) on which the executable work runs, or a compiler used to
produce the work, or an object code interpreter used to run it.
</p>
<p>The &ldquo;Corresponding Source&rdquo; for a work in object code form means all
the source code needed to generate, install, and (for an executable
work) run the object code and to modify the work, including scripts to
control those activities.  However, it does not include the work&rsquo;s
System Libraries, or general-purpose tools or generally available free
programs which are used unmodified in performing those activities but
which are not part of the work.  For example, Corresponding Source
includes interface definition files associated with source files for
the work, and the source code for shared libraries and dynamically
linked subprograms that the work is specifically designed to require,
such as by intimate data communication or control flow between those
subprograms and other parts of the work.
</p>
<p>The Corresponding Source need not include anything that users can
regenerate automatically from other parts of the Corresponding Source.
</p>
<p>The Corresponding Source for a work in source code form is that same
work.
</p>
</li><li> Basic Permissions.
<p>All rights granted under this License are granted for the term of
copyright on the Program, and are irrevocable provided the stated
conditions are met.  This License explicitly affirms your unlimited
permission to run the unmodified Program.  The output from running a
covered work is covered by this License only if the output, given its
content, constitutes a covered work.  This License acknowledges your
rights of fair use or other equivalent, as provided by copyright law.
</p>
<p>You may make, run and propagate covered works that you do not convey,
without conditions so long as your license otherwise remains in force.
You may convey covered works to others for the sole purpose of having
them make modifications exclusively for you, or provide you with
facilities for running those works, provided that you comply with the
terms of this License in conveying all material for which you do not
control copyright.  Those thus making or running the covered works for
you must do so exclusively on your behalf, under your direction and
control, on terms that prohibit them from making any copies of your
copyrighted material outside their relationship with you.
</p>
<p>Conveying under any other circumstances is permitted solely under the
conditions stated below.  Sublicensing is not allowed; section 10
makes it unnecessary.
</p>
</li><li> Protecting Users&rsquo; Legal Rights From Anti-Circumvention Law.
<p>No covered work shall be deemed part of an effective technological
measure under any applicable law fulfilling obligations under article
11 of the WIPO copyright treaty adopted on 20 December 1996, or
similar laws prohibiting or restricting circumvention of such
measures.
</p>
<p>When you convey a covered work, you waive any legal power to forbid
circumvention of technological measures to the extent such
circumvention is effected by exercising rights under this License with
respect to the covered work, and you disclaim any intention to limit
operation or modification of the work as a means of enforcing, against
the work&rsquo;s users, your or third parties&rsquo; legal rights to forbid
circumvention of technological measures.
</p>
</li><li> Conveying Verbatim Copies.
<p>You may convey verbatim copies of the Program&rsquo;s source code as you
receive it, in any medium, provided that you conspicuously and
appropriately publish on each copy an appropriate copyright notice;
keep intact all notices stating that this License and any
non-permissive terms added in accord with section 7 apply to the code;
keep intact all notices of the absence of any warranty; and give all
recipients a copy of this License along with the Program.
</p>
<p>You may charge any price or no price for each copy that you convey,
and you may offer support or warranty protection for a fee.
</p>
</li><li> Conveying Modified Source Versions.
<p>You may convey a work based on the Program, or the modifications to
produce it from the Program, in the form of source code under the
terms of section 4, provided that you also meet all of these
conditions:
</p>
<ol class="enumerate" type="a" start="1">
<li> The work must carry prominent notices stating that you modified it,
and giving a relevant date.
</li><li> The work must carry prominent notices stating that it is released
under this License and any conditions added under section 7.  This
requirement modifies the requirement in section 4 to &ldquo;keep intact all
notices&rdquo;.
</li><li> You must license the entire work, as a whole, under this License to
anyone who comes into possession of a copy.  This License will
therefore apply, along with any applicable section 7 additional terms,
to the whole of the work, and all its parts, regardless of how they
are packaged.  This License gives no permission to license the work in
any other way, but it does not invalidate such permission if you have
separately received it.
</li><li> If the work has interactive user interfaces, each must display
Appropriate Legal Notices; however, if the Program has interactive
interfaces that do not display Appropriate Legal Notices, your work
need not make them do so.
</li></ol>
<p>A compilation of a covered work with other separate and independent
works, which are not by their nature extensions of the covered work,
and which are not combined with it such as to form a larger program,
in or on a volume of a storage or distribution medium, is called an
&ldquo;aggregate&rdquo; if the compilation and its resulting copyright are not
used to limit the access or legal rights of the compilation&rsquo;s users
beyond what the individual works permit.  Inclusion of a covered work
in an aggregate does not cause this License to apply to the other
parts of the aggregate.
</p>
</li><li> Conveying Non-Source Forms.
<p>You may convey a covered work in object code form under the terms of
sections 4 and 5, provided that you also convey the machine-readable
Corresponding Source under the terms of this License, in one of these
ways:
</p>
<ol class="enumerate" type="a" start="1">
<li> Convey the object code in, or embodied in, a physical product
(including a physical distribution medium), accompanied by the
Corresponding Source fixed on a durable physical medium customarily
used for software interchange.
</li><li> Convey the object code in, or embodied in, a physical product
(including a physical distribution medium), accompanied by a written
offer, valid for at least three years and valid for as long as you
offer spare parts or customer support for that product model, to give
anyone who possesses the object code either (1) a copy of the
Corresponding Source for all the software in the product that is
covered by this License, on a durable physical medium customarily used
for software interchange, for a price no more than your reasonable
cost of physically performing this conveying of source, or (2) access
to copy the Corresponding Source from a network server at no charge.
</li><li> Convey individual copies of the object code with a copy of the written
offer to provide the Corresponding Source.  This alternative is
allowed only occasionally and noncommercially, and only if you
received the object code with such an offer, in accord with subsection
6b.
</li><li> Convey the object code by offering access from a designated place
(gratis or for a charge), and offer equivalent access to the
Corresponding Source in the same way through the same place at no
further charge.  You need not require recipients to copy the
Corresponding Source along with the object code.  If the place to copy
the object code is a network server, the Corresponding Source may be
on a different server (operated by you or a third party) that supports
equivalent copying facilities, provided you maintain clear directions
next to the object code saying where to find the Corresponding Source.
Regardless of what server hosts the Corresponding Source, you remain
obligated to ensure that it is available for as long as needed to
satisfy these requirements.
</li><li> Convey the object code using peer-to-peer transmission, provided you
inform other peers where the object code and Corresponding Source of
the work are being offered to the general public at no charge under
subsection 6d.
</li></ol>
<p>A separable portion of the object code, whose source code is excluded
from the Corresponding Source as a System Library, need not be
included in conveying the object code work.
</p>
<p>A &ldquo;User Product&rdquo; is either (1) a &ldquo;consumer product&rdquo;, which means any
tangible personal property which is normally used for personal,
family, or household purposes, or (2) anything designed or sold for
incorporation into a dwelling.  In determining whether a product is a
consumer product, doubtful cases shall be resolved in favor of
coverage.  For a particular product received by a particular user,
&ldquo;normally used&rdquo; refers to a typical or common use of that class of
product, regardless of the status of the particular user or of the way
in which the particular user actually uses, or expects or is expected
to use, the product.  A product is a consumer product regardless of
whether the product has substantial commercial, industrial or
non-consumer uses, unless such uses represent the only significant
mode of use of the product.
</p>
<p>&ldquo;Installation Information&rdquo; for a User Product means any methods,
procedures, authorization keys, or other information required to
install and execute modified versions of a covered work in that User
Product from a modified version of its Corresponding Source.  The
information must suffice to ensure that the continued functioning of
the modified object code is in no case prevented or interfered with
solely because modification has been made.
</p>
<p>If you convey an object code work under this section in, or with, or
specifically for use in, a User Product, and the conveying occurs as
part of a transaction in which the right of possession and use of the
User Product is transferred to the recipient in perpetuity or for a
fixed term (regardless of how the transaction is characterized), the
Corresponding Source conveyed under this section must be accompanied
by the Installation Information.  But this requirement does not apply
if neither you nor any third party retains the ability to install
modified object code on the User Product (for example, the work has
been installed in ROM).
</p>
<p>The requirement to provide Installation Information does not include a
requirement to continue to provide support service, warranty, or
updates for a work that has been modified or installed by the
recipient, or for the User Product in which it has been modified or
installed.  Access to a network may be denied when the modification
itself materially and adversely affects the operation of the network
or violates the rules and protocols for communication across the
network.
</p>
<p>Corresponding Source conveyed, and Installation Information provided,
in accord with this section must be in a format that is publicly
documented (and with an implementation available to the public in
source code form), and must require no special password or key for
unpacking, reading or copying.
</p>
</li><li> Additional Terms.
<p>&ldquo;Additional permissions&rdquo; are terms that supplement the terms of this
License by making exceptions from one or more of its conditions.
Additional permissions that are applicable to the entire Program shall
be treated as though they were included in this License, to the extent
that they are valid under applicable law.  If additional permissions
apply only to part of the Program, that part may be used separately
under those permissions, but the entire Program remains governed by
this License without regard to the additional permissions.
</p>
<p>When you convey a copy of a covered work, you may at your option
remove any additional permissions from that copy, or from any part of
it.  (Additional permissions may be written to require their own
removal in certain cases when you modify the work.)  You may place
additional permissions on material, added by you to a covered work,
for which you have or can give appropriate copyright permission.
</p>
<p>Notwithstanding any other provision of this License, for material you
add to a covered work, you may (if authorized by the copyright holders
of that material) supplement the terms of this License with terms:
</p>
<ol class="enumerate" type="a" start="1">
<li> Disclaiming warranty or limiting liability differently from the terms
of sections 15 and 16 of this License; or
</li><li> Requiring preservation of specified reasonable legal notices or author
attributions in that material or in the Appropriate Legal Notices
displayed by works containing it; or
</li><li> Prohibiting misrepresentation of the origin of that material, or
requiring that modified versions of such material be marked in
reasonable ways as different from the original version; or
</li><li> Limiting the use for publicity purposes of names of licensors or
authors of the material; or
</li><li> Declining to grant rights under trademark law for use of some trade
names, trademarks, or service marks; or
</li><li> Requiring indemnification of licensors and authors of that material by
anyone who conveys the material (or modified versions of it) with
contractual assumptions of liability to the recipient, for any
liability that these contractual assumptions directly impose on those
licensors and authors.
</li></ol>
<p>All other non-permissive additional terms are considered &ldquo;further
restrictions&rdquo; within the meaning of section 10.  If the Program as you
received it, or any part of it, contains a notice stating that it is
governed by this License along with a term that is a further
restriction, you may remove that term.  If a license document contains
a further restriction but permits relicensing or conveying under this
License, you may add to a covered work material governed by the terms
of that license document, provided that the further restriction does
not survive such relicensing or conveying.
</p>
<p>If you add terms to a covered work in accord with this section, you
must place, in the relevant source files, a statement of the
additional terms that apply to those files, or a notice indicating
where to find the applicable terms.
</p>
<p>Additional terms, permissive or non-permissive, may be stated in the
form of a separately written license, or stated as exceptions; the
above requirements apply either way.
</p>
</li><li> Termination.
<p>You may not propagate or modify a covered work except as expressly
provided under this License.  Any attempt otherwise to propagate or
modify it is void, and will automatically terminate your rights under
this License (including any patent licenses granted under the third
paragraph of section 11).
</p>
<p>However, if you cease all violation of this License, then your license
from a particular copyright holder is reinstated (a) provisionally,
unless and until the copyright holder explicitly and finally
terminates your license, and (b) permanently, if the copyright holder
fails to notify you of the violation by some reasonable means prior to
60 days after the cessation.
</p>
<p>Moreover, your license from a particular copyright holder is
reinstated permanently if the copyright holder notifies you of the
violation by some reasonable means, this is the first time you have
received notice of violation of this License (for any work) from that
copyright holder, and you cure the violation prior to 30 days after
your receipt of the notice.
</p>
<p>Termination of your rights under this section does not terminate the
licenses of parties who have received copies or rights from you under
this License.  If your rights have been terminated and not permanently
reinstated, you do not qualify to receive new licenses for the same
material under section 10.
</p>
</li><li> Acceptance Not Required for Having Copies.
<p>You are not required to accept this License in order to receive or run
a copy of the Program.  Ancillary propagation of a covered work
occurring solely as a consequence of using peer-to-peer transmission
to receive a copy likewise does not require acceptance.  However,
nothing other than this License grants you permission to propagate or
modify any covered work.  These actions infringe copyright if you do
not accept this License.  Therefore, by modifying or propagating a
covered work, you indicate your acceptance of this License to do so.
</p>
</li><li> Automatic Licensing of Downstream Recipients.
<p>Each time you convey a covered work, the recipient automatically
receives a license from the original licensors, to run, modify and
propagate that work, subject to this License.  You are not responsible
for enforcing compliance by third parties with this License.
</p>
<p>An &ldquo;entity transaction&rdquo; is a transaction transferring control of an
organization, or substantially all assets of one, or subdividing an
organization, or merging organizations.  If propagation of a covered
work results from an entity transaction, each party to that
transaction who receives a copy of the work also receives whatever
licenses to the work the party&rsquo;s predecessor in interest had or could
give under the previous paragraph, plus a right to possession of the
Corresponding Source of the work from the predecessor in interest, if
the predecessor has it or can get it with reasonable efforts.
</p>
<p>You may not impose any further restrictions on the exercise of the
rights granted or affirmed under this License.  For example, you may
not impose a license fee, royalty, or other charge for exercise of
rights granted under this License, and you may not initiate litigation
(including a cross-claim or counterclaim in a lawsuit) alleging that
any patent claim is infringed by making, using, selling, offering for
sale, or importing the Program or any portion of it.
</p>
</li><li> Patents.
<p>A &ldquo;contributor&rdquo; is a copyright holder who authorizes use under this
License of the Program or a work on which the Program is based.  The
work thus licensed is called the contributor&rsquo;s &ldquo;contributor version&rdquo;.
</p>
<p>A contributor&rsquo;s &ldquo;essential patent claims&rdquo; are all patent claims owned
or controlled by the contributor, whether already acquired or
hereafter acquired, that would be infringed by some manner, permitted
by this License, of making, using, or selling its contributor version,
but do not include claims that would be infringed only as a
consequence of further modification of the contributor version.  For
purposes of this definition, &ldquo;control&rdquo; includes the right to grant
patent sublicenses in a manner consistent with the requirements of
this License.
</p>
<p>Each contributor grants you a non-exclusive, worldwide, royalty-free
patent license under the contributor&rsquo;s essential patent claims, to
make, use, sell, offer for sale, import and otherwise run, modify and
propagate the contents of its contributor version.
</p>
<p>In the following three paragraphs, a &ldquo;patent license&rdquo; is any express
agreement or commitment, however denominated, not to enforce a patent
(such as an express permission to practice a patent or covenant not to
sue for patent infringement).  To &ldquo;grant&rdquo; such a patent license to a
party means to make such an agreement or commitment not to enforce a
patent against the party.
</p>
<p>If you convey a covered work, knowingly relying on a patent license,
and the Corresponding Source of the work is not available for anyone
to copy, free of charge and under the terms of this License, through a
publicly available network server or other readily accessible means,
then you must either (1) cause the Corresponding Source to be so
available, or (2) arrange to deprive yourself of the benefit of the
patent license for this particular work, or (3) arrange, in a manner
consistent with the requirements of this License, to extend the patent
license to downstream recipients.  &ldquo;Knowingly relying&rdquo; means you have
actual knowledge that, but for the patent license, your conveying the
covered work in a country, or your recipient&rsquo;s use of the covered work
in a country, would infringe one or more identifiable patents in that
country that you have reason to believe are valid.
</p>
<p>If, pursuant to or in connection with a single transaction or
arrangement, you convey, or propagate by procuring conveyance of, a
covered work, and grant a patent license to some of the parties
receiving the covered work authorizing them to use, propagate, modify
or convey a specific copy of the covered work, then the patent license
you grant is automatically extended to all recipients of the covered
work and works based on it.
</p>
<p>A patent license is &ldquo;discriminatory&rdquo; if it does not include within the
scope of its coverage, prohibits the exercise of, or is conditioned on
the non-exercise of one or more of the rights that are specifically
granted under this License.  You may not convey a covered work if you
are a party to an arrangement with a third party that is in the
business of distributing software, under which you make payment to the
third party based on the extent of your activity of conveying the
work, and under which the third party grants, to any of the parties
who would receive the covered work from you, a discriminatory patent
license (a) in connection with copies of the covered work conveyed by
you (or copies made from those copies), or (b) primarily for and in
connection with specific products or compilations that contain the
covered work, unless you entered into that arrangement, or that patent
license was granted, prior to 28 March 2007.
</p>
<p>Nothing in this License shall be construed as excluding or limiting
any implied license or other defenses to infringement that may
otherwise be available to you under applicable patent law.
</p>
</li><li> No Surrender of Others&rsquo; Freedom.
<p>If conditions are imposed on you (whether by court order, agreement or
otherwise) that contradict the conditions of this License, they do not
excuse you from the conditions of this License.  If you cannot convey
a covered work so as to satisfy simultaneously your obligations under
this License and any other pertinent obligations, then as a
consequence you may not convey it at all.  For example, if you agree
to terms that obligate you to collect a royalty for further conveying
from those to whom you convey the Program, the only way you could
satisfy both those terms and this License would be to refrain entirely
from conveying the Program.
</p>
</li><li> Use with the GNU Affero General Public License.
<p>Notwithstanding any other provision of this License, you have
permission to link or combine any covered work with a work licensed
under version 3 of the GNU Affero General Public License into a single
combined work, and to convey the resulting work.  The terms of this
License will continue to apply to the part which is the covered work,
but the special requirements of the GNU Affero General Public License,
section 13, concerning interaction through a network will apply to the
combination as such.
</p>
</li><li> Revised Versions of this License.
<p>The Free Software Foundation may publish revised and/or new versions
of the GNU General Public License from time to time.  Such new
versions will be similar in spirit to the present version, but may
differ in detail to address new problems or concerns.
</p>
<p>Each version is given a distinguishing version number.  If the Program
specifies that a certain numbered version of the GNU General Public
License &ldquo;or any later version&rdquo; applies to it, you have the option of
following the terms and conditions either of that numbered version or
of any later version published by the Free Software Foundation.  If
the Program does not specify a version number of the GNU General
Public License, you may choose any version ever published by the Free
Software Foundation.
</p>
<p>If the Program specifies that a proxy can decide which future versions
of the GNU General Public License can be used, that proxy&rsquo;s public
statement of acceptance of a version permanently authorizes you to
choose that version for the Program.
</p>
<p>Later license versions may give you additional or different
permissions.  However, no additional obligations are imposed on any
author or copyright holder as a result of your choosing to follow a
later version.
</p>
</li><li> Disclaimer of Warranty.
<p>THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY
APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT
HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM &ldquo;AS IS&rdquo; WITHOUT
WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND
PERFORMANCE OF THE PROGRAM IS WITH YOU.  SHOULD THE PROGRAM PROVE
DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR
CORRECTION.
</p>
</li><li> Limitation of Liability.
<p>IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR
CONVEYS THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES,
INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES
ARISING OUT OF THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT
NOT LIMITED TO LOSS OF DATA OR DATA BEING RENDERED INACCURATE OR
LOSSES SUSTAINED BY YOU OR THIRD PARTIES OR A FAILURE OF THE PROGRAM
TO OPERATE WITH ANY OTHER PROGRAMS), EVEN IF SUCH HOLDER OR OTHER
PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
</p>
</li><li> Interpretation of Sections 15 and 16.
<p>If the disclaimer of warranty and limitation of liability provided
above cannot be given local legal effect according to their terms,
reviewing courts shall apply local law that most closely approximates
an absolute waiver of all civil liability in connection with the
Program, unless a warranty or assumption of liability accompanies a
copy of the Program in return for a fee.
</p>
</li></ol>
<h3 class="heading" id="END-OF-TERMS-AND-CONDITIONS">END OF TERMS AND CONDITIONS</h3>
<h3 class="heading" id="How-to-Apply-These-Terms-to-Your-New-Programs">How to Apply These Terms to Your New Programs</h3>
<p>If you develop a new program, and you want it to be of the greatest
possible use to the public, the best way to achieve this is to make it
free software which everyone can redistribute and change under these
terms.
</p>
<p>To do so, attach the following notices to the program.  It is safest
to attach them to the start of each source file to most effectively
state the exclusion of warranty; and each file should have at least
the &ldquo;copyright&rdquo; line and a pointer to where the full notice is found.
</p>
<div class="example smallexample">
<pre class="example-preformatted"><var class="var">one line to give the program's name and a brief idea of what it does.</var>  
Copyright (C) <var class="var">year</var> <var class="var">name of author</var>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.
This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <a class="url" href="http://www.gnu.org/licenses/">http://www.gnu.org/licenses/</a>.
</pre></div>
<p>Also add information on how to contact you by electronic and paper mail.
</p>
<p>If the program does terminal interaction, make it output a short
notice like this when it starts in an interactive mode:
</p>
<div class="example smallexample">
<pre class="example-preformatted"><var class="var">program</var> Copyright (C) <var class="var">year</var> <var class="var">name of author</var> 
This program comes with ABSOLUTELY NO WARRANTY; for details type &lsquo;<samp class="samp">show w</samp>&rsquo;.
This is free software, and you are welcome to redistribute it
under certain conditions; type &lsquo;<samp class="samp">show c</samp>&rsquo; for details.
</pre></div>
<p>The hypothetical commands &lsquo;<samp class="samp">show w</samp>&rsquo; and &lsquo;<samp class="samp">show c</samp>&rsquo; should show
the appropriate parts of the General Public License.  Of course, your
program&rsquo;s commands might be different; for a GUI interface, you would
use an &ldquo;about box&rdquo;.
</p>
<p>You should also get your employer (if you work as a programmer) or school,
if any, to sign a &ldquo;copyright disclaimer&rdquo; for the program, if necessary.
For more information on this, and how to apply and follow the GNU GPL, see
<a class="url" href="http://www.gnu.org/licenses/">http://www.gnu.org/licenses/</a>.
</p>
<p>The GNU General Public License does not permit incorporating your
program into proprietary programs.  If your program is a subroutine
library, you may consider it more useful to permit linking proprietary
applications with the library.  If this is what you want to do, use
the GNU Lesser General Public License instead of this License.  But
first, please read <a class="url" href="http://www.gnu.org/philosophy/why-not-lgpl.html">http://www.gnu.org/philosophy/why-not-lgpl.html</a>.
</p>
<hr>
</div>
<div class="unnumbered-level-extent" id="Index">
<h2 class="unnumbered" id="Index-1">Index</h2>
 
<div class="printindex cp-printindex">
<table class="cp-letters-header-printindex"><tr><th>Jump to: &nbsp; </th><td><a class="summary-letter-printindex" href="#Index_cp_letter-B"><b>B</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-C"><b>C</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-F"><b>F</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-G"><b>G</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-I"><b>I</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-L"><b>L</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-M"><b>M</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-O"><b>O</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-P"><b>P</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-R"><b>R</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-S"><b>S</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-T"><b>T</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-U"><b>U</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-V"><b>V</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-W"><b>W</b></a>
 &nbsp; 
</td></tr></table>
<table class="cp-entries-printindex" border="0">
<tr><td></td><th class="entries-header-printindex">Index Entry</th><th class="sections-header-printindex">Section</th></tr>
<tr><td colspan="3"><hr></td></tr>
<tr><th id="Index_cp_letter-B">B</th></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-Basic-Usage-Overview">Basic Usage Overview</a></td><td class="printindex-index-section"><a href="#Basic-Usage-Overview">Basic Usage Overview</a></td></tr>
<tr><td colspan="3"><hr></td></tr>
<tr><th id="Index_cp_letter-C">C</th></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-clrdevice">clrdevice</a></td><td class="printindex-index-section"><a href="#GPIB">GPIB</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-Common-Functions">Common Functions</a></td><td class="printindex-index-section"><a href="#Common-Functions">Common Functions</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-configureMulticast">configureMulticast</a></td><td class="printindex-index-section"><a href="#UDP-Port">UDP Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-configureTerminator">configureTerminator</a></td><td class="printindex-index-section"><a href="#Serial-Port">Serial Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-configureTerminator-1">configureTerminator</a></td><td class="printindex-index-section"><a href="#TCP-Client">TCP Client</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-configureTerminator-2">configureTerminator</a></td><td class="printindex-index-section"><a href="#TCP-Server">TCP Server</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-configureTerminator-3">configureTerminator</a></td><td class="printindex-index-section"><a href="#UDP-Port">UDP Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-copyright">copyright</a></td><td class="printindex-index-section"><a href="#Copying">Copying</a></td></tr>
<tr><td colspan="3"><hr></td></tr>
<tr><th id="Index_cp_letter-F">F</th></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fclose">fclose</a></td><td class="printindex-index-section"><a href="#GPIB">GPIB</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fclose-1">fclose</a></td><td class="printindex-index-section"><a href="#I2C">I2C</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fclose-2">fclose</a></td><td class="printindex-index-section"><a href="#Parallel">Parallel</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fclose-3">fclose</a></td><td class="printindex-index-section"><a href="#Serial-_0028Deprecated_0029">Serial (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fclose-4">fclose</a></td><td class="printindex-index-section"><a href="#SPI">SPI</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fclose-5">fclose</a></td><td class="printindex-index-section"><a href="#TCP-_0028Deprecated_0029">TCP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fclose-6">fclose</a></td><td class="printindex-index-section"><a href="#UDP-_0028Deprecated_0029">UDP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fclose-7">fclose</a></td><td class="printindex-index-section"><a href="#USBTMC">USBTMC</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fclose-8">fclose</a></td><td class="printindex-index-section"><a href="#VXI11">VXI11</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-flush">flush</a></td><td class="printindex-index-section"><a href="#Serial-Port">Serial Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-flush-1">flush</a></td><td class="printindex-index-section"><a href="#TCP-_0028Deprecated_0029">TCP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-flush-2">flush</a></td><td class="printindex-index-section"><a href="#TCP-Client">TCP Client</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-flush-3">flush</a></td><td class="printindex-index-section"><a href="#TCP-Server">TCP Server</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-flush-4">flush</a></td><td class="printindex-index-section"><a href="#UDP-_0028Deprecated_0029">UDP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-flush-5">flush</a></td><td class="printindex-index-section"><a href="#UDP-Port">UDP Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-flushinput">flushinput</a></td><td class="printindex-index-section"><a href="#Common-Functions">Common Functions</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-flushinput-1">flushinput</a></td><td class="printindex-index-section"><a href="#Serial-_0028Deprecated_0029">Serial (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-flushinput-2">flushinput</a></td><td class="printindex-index-section"><a href="#TCP-_0028Deprecated_0029">TCP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-flushinput-3">flushinput</a></td><td class="printindex-index-section"><a href="#UDP-_0028Deprecated_0029">UDP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-flushoutput">flushoutput</a></td><td class="printindex-index-section"><a href="#Common-Functions">Common Functions</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-flushoutput-1">flushoutput</a></td><td class="printindex-index-section"><a href="#Serial-_0028Deprecated_0029">Serial (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-flushoutput-2">flushoutput</a></td><td class="printindex-index-section"><a href="#TCP-_0028Deprecated_0029">TCP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-flushoutput-3">flushoutput</a></td><td class="printindex-index-section"><a href="#UDP-_0028Deprecated_0029">UDP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fopen">fopen</a></td><td class="printindex-index-section"><a href="#GPIB">GPIB</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fopen-1">fopen</a></td><td class="printindex-index-section"><a href="#I2C">I2C</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fopen-2">fopen</a></td><td class="printindex-index-section"><a href="#Parallel">Parallel</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fopen-3">fopen</a></td><td class="printindex-index-section"><a href="#Serial-_0028Deprecated_0029">Serial (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fopen-4">fopen</a></td><td class="printindex-index-section"><a href="#SPI">SPI</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fopen-5">fopen</a></td><td class="printindex-index-section"><a href="#TCP-_0028Deprecated_0029">TCP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fopen-6">fopen</a></td><td class="printindex-index-section"><a href="#UDP-_0028Deprecated_0029">UDP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fopen-7">fopen</a></td><td class="printindex-index-section"><a href="#USBTMC">USBTMC</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fopen-8">fopen</a></td><td class="printindex-index-section"><a href="#VXI11">VXI11</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fprintf">fprintf</a></td><td class="printindex-index-section"><a href="#GPIB">GPIB</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fprintf-1">fprintf</a></td><td class="printindex-index-section"><a href="#Serial-_0028Deprecated_0029">Serial (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fprintf-2">fprintf</a></td><td class="printindex-index-section"><a href="#Serial-Port">Serial Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fprintf-3">fprintf</a></td><td class="printindex-index-section"><a href="#TCP-_0028Deprecated_0029">TCP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fprintf-4">fprintf</a></td><td class="printindex-index-section"><a href="#UDP-_0028Deprecated_0029">UDP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fprintf-5">fprintf</a></td><td class="printindex-index-section"><a href="#UDP-Port">UDP Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fread">fread</a></td><td class="printindex-index-section"><a href="#GPIB">GPIB</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fread-1">fread</a></td><td class="printindex-index-section"><a href="#I2C">I2C</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fread-2">fread</a></td><td class="printindex-index-section"><a href="#Parallel">Parallel</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fread-3">fread</a></td><td class="printindex-index-section"><a href="#Serial-_0028Deprecated_0029">Serial (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fread-4">fread</a></td><td class="printindex-index-section"><a href="#Serial-Port">Serial Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fread-5">fread</a></td><td class="printindex-index-section"><a href="#SPI">SPI</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fread-6">fread</a></td><td class="printindex-index-section"><a href="#TCP-_0028Deprecated_0029">TCP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fread-7">fread</a></td><td class="printindex-index-section"><a href="#UDP-_0028Deprecated_0029">UDP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fread-8">fread</a></td><td class="printindex-index-section"><a href="#UDP-Port">UDP Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fread-9">fread</a></td><td class="printindex-index-section"><a href="#USBTMC">USBTMC</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fread-10">fread</a></td><td class="printindex-index-section"><a href="#VXI11">VXI11</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fscanf">fscanf</a></td><td class="printindex-index-section"><a href="#GPIB">GPIB</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-Function-Reference">Function Reference</a></td><td class="printindex-index-section"><a href="#Function-Reference">Function Reference</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fwrite">fwrite</a></td><td class="printindex-index-section"><a href="#GPIB">GPIB</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fwrite-1">fwrite</a></td><td class="printindex-index-section"><a href="#I2C">I2C</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fwrite-2">fwrite</a></td><td class="printindex-index-section"><a href="#Parallel">Parallel</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fwrite-3">fwrite</a></td><td class="printindex-index-section"><a href="#Serial-_0028Deprecated_0029">Serial (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fwrite-4">fwrite</a></td><td class="printindex-index-section"><a href="#Serial-Port">Serial Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fwrite-5">fwrite</a></td><td class="printindex-index-section"><a href="#SPI">SPI</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fwrite-6">fwrite</a></td><td class="printindex-index-section"><a href="#TCP-_0028Deprecated_0029">TCP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fwrite-7">fwrite</a></td><td class="printindex-index-section"><a href="#UDP-_0028Deprecated_0029">UDP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fwrite-8">fwrite</a></td><td class="printindex-index-section"><a href="#UDP-Port">UDP Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fwrite-9">fwrite</a></td><td class="printindex-index-section"><a href="#USBTMC">USBTMC</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-fwrite-10">fwrite</a></td><td class="printindex-index-section"><a href="#VXI11">VXI11</a></td></tr>
<tr><td colspan="3"><hr></td></tr>
<tr><th id="Index_cp_letter-G">G</th></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-General">General</a></td><td class="printindex-index-section"><a href="#General">General</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-get">get</a></td><td class="printindex-index-section"><a href="#I2C">I2C</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-get-1">get</a></td><td class="printindex-index-section"><a href="#Modbus">Modbus</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-get-2">get</a></td><td class="printindex-index-section"><a href="#Serial-_0028Deprecated_0029">Serial (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-get-3">get</a></td><td class="printindex-index-section"><a href="#Serial-Port">Serial Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-get-4">get</a></td><td class="printindex-index-section"><a href="#SPI">SPI</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-get-5">get</a></td><td class="printindex-index-section"><a href="#TCP-_0028Deprecated_0029">TCP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-get-6">get</a></td><td class="printindex-index-section"><a href="#TCP-Client">TCP Client</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-get-7">get</a></td><td class="printindex-index-section"><a href="#TCP-Server">TCP Server</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-get-8">get</a></td><td class="printindex-index-section"><a href="#UDP-_0028Deprecated_0029">UDP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-get-9">get</a></td><td class="printindex-index-section"><a href="#UDP-Port">UDP Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-getpinstatus">getpinstatus</a></td><td class="printindex-index-section"><a href="#Serial-Port">Serial Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-GPIB">GPIB</a></td><td class="printindex-index-section"><a href="#GPIB">GPIB</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-gpib">gpib</a></td><td class="printindex-index-section"><a href="#GPIB">GPIB</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-gpib_005fclose">gpib_close</a></td><td class="printindex-index-section"><a href="#GPIB">GPIB</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-gpib_005fread">gpib_read</a></td><td class="printindex-index-section"><a href="#GPIB">GPIB</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-gpib_005ftimeout">gpib_timeout</a></td><td class="printindex-index-section"><a href="#GPIB">GPIB</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-gpib_005fwrite">gpib_write</a></td><td class="printindex-index-section"><a href="#GPIB">GPIB</a></td></tr>
<tr><td colspan="3"><hr></td></tr>
<tr><th id="Index_cp_letter-I">I</th></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-I2C">I2C</a></td><td class="printindex-index-section"><a href="#I2C">I2C</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-i2c">i2c</a></td><td class="printindex-index-section"><a href="#I2C">I2C</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-i2c_005faddr">i2c_addr</a></td><td class="printindex-index-section"><a href="#I2C">I2C</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-i2c_005fclose">i2c_close</a></td><td class="printindex-index-section"><a href="#I2C">I2C</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-i2c_005fread">i2c_read</a></td><td class="printindex-index-section"><a href="#I2C">I2C</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-i2c_005fwrite">i2c_write</a></td><td class="printindex-index-section"><a href="#I2C">I2C</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-Installing-and-loading">Installing and loading</a></td><td class="printindex-index-section"><a href="#Installing-and-loading">Installing and loading</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-instrhelp">instrhelp</a></td><td class="printindex-index-section"><a href="#General">General</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-instrhwinfo">instrhwinfo</a></td><td class="printindex-index-section"><a href="#General">General</a></td></tr>
<tr><td colspan="3"><hr></td></tr>
<tr><th id="Index_cp_letter-L">L</th></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-Loading">Loading</a></td><td class="printindex-index-section"><a href="#Installing-and-loading">Installing and loading</a></td></tr>
<tr><td colspan="3"><hr></td></tr>
<tr><th id="Index_cp_letter-M">M</th></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-maskWrite">maskWrite</a></td><td class="printindex-index-section"><a href="#Modbus">Modbus</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-Modbus">Modbus</a></td><td class="printindex-index-section"><a href="#Modbus">Modbus</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-modbus">modbus</a></td><td class="printindex-index-section"><a href="#Modbus">Modbus</a></td></tr>
<tr><td colspan="3"><hr></td></tr>
<tr><th id="Index_cp_letter-O">O</th></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-Off_002dline-install">Off-line install</a></td><td class="printindex-index-section"><a href="#Installing-and-loading">Installing and loading</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-Online-install">Online install</a></td><td class="printindex-index-section"><a href="#Installing-and-loading">Installing and loading</a></td></tr>
<tr><td colspan="3"><hr></td></tr>
<tr><th id="Index_cp_letter-P">P</th></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-Parallel">Parallel</a></td><td class="printindex-index-section"><a href="#Parallel">Parallel</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-parallel">parallel</a></td><td class="printindex-index-section"><a href="#Parallel">Parallel</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-pp_005fclose">pp_close</a></td><td class="printindex-index-section"><a href="#Parallel">Parallel</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-pp_005fctrl">pp_ctrl</a></td><td class="printindex-index-section"><a href="#Parallel">Parallel</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-pp_005fdata">pp_data</a></td><td class="printindex-index-section"><a href="#Parallel">Parallel</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-pp_005fdatadir">pp_datadir</a></td><td class="printindex-index-section"><a href="#Parallel">Parallel</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-pp_005fstat">pp_stat</a></td><td class="printindex-index-section"><a href="#Parallel">Parallel</a></td></tr>
<tr><td colspan="3"><hr></td></tr>
<tr><th id="Index_cp_letter-R">R</th></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-read">read</a></td><td class="printindex-index-section"><a href="#Modbus">Modbus</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-read-1">read</a></td><td class="printindex-index-section"><a href="#Serial-Port">Serial Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-read-2">read</a></td><td class="printindex-index-section"><a href="#SPI">SPI</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-read-3">read</a></td><td class="printindex-index-section"><a href="#TCP-_0028Deprecated_0029">TCP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-read-4">read</a></td><td class="printindex-index-section"><a href="#TCP-Client">TCP Client</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-read-5">read</a></td><td class="printindex-index-section"><a href="#TCP-Server">TCP Server</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-read-6">read</a></td><td class="printindex-index-section"><a href="#UDP-_0028Deprecated_0029">UDP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-read-7">read</a></td><td class="printindex-index-section"><a href="#UDP-Port">UDP Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-readbinblock">readbinblock</a></td><td class="printindex-index-section"><a href="#Common-Functions">Common Functions</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-readline">readline</a></td><td class="printindex-index-section"><a href="#Common-Functions">Common Functions</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-Requirements">Requirements</a></td><td class="printindex-index-section"><a href="#Installing-and-loading">Installing and loading</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-resolvehost">resolvehost</a></td><td class="printindex-index-section"><a href="#General">General</a></td></tr>
<tr><td colspan="3"><hr></td></tr>
<tr><th id="Index_cp_letter-S">S</th></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-serial">serial</a></td><td class="printindex-index-section"><a href="#Serial-_0028Deprecated_0029">Serial (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-Serial-_0028Deprecated_0029">Serial (Deprecated)</a></td><td class="printindex-index-section"><a href="#Serial-_0028Deprecated_0029">Serial (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-Serial-Port">Serial Port</a></td><td class="printindex-index-section"><a href="#Serial-Port">Serial Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-serialbreak">serialbreak</a></td><td class="printindex-index-section"><a href="#Serial-_0028Deprecated_0029">Serial (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-serialbreak-1">serialbreak</a></td><td class="printindex-index-section"><a href="#Serial-Port">Serial Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-seriallist">seriallist</a></td><td class="printindex-index-section"><a href="#Serial-_0028Deprecated_0029">Serial (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-serialport">serialport</a></td><td class="printindex-index-section"><a href="#Serial-Port">Serial Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-serialportlist">serialportlist</a></td><td class="printindex-index-section"><a href="#Serial-Port">Serial Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-set">set</a></td><td class="printindex-index-section"><a href="#I2C">I2C</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-set-1">set</a></td><td class="printindex-index-section"><a href="#Modbus">Modbus</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-set-2">set</a></td><td class="printindex-index-section"><a href="#Serial-_0028Deprecated_0029">Serial (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-set-3">set</a></td><td class="printindex-index-section"><a href="#Serial-Port">Serial Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-set-4">set</a></td><td class="printindex-index-section"><a href="#SPI">SPI</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-set-5">set</a></td><td class="printindex-index-section"><a href="#TCP-_0028Deprecated_0029">TCP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-set-6">set</a></td><td class="printindex-index-section"><a href="#TCP-Client">TCP Client</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-set-7">set</a></td><td class="printindex-index-section"><a href="#TCP-Server">TCP Server</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-set-8">set</a></td><td class="printindex-index-section"><a href="#UDP-_0028Deprecated_0029">UDP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-set-9">set</a></td><td class="printindex-index-section"><a href="#UDP-Port">UDP Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-setDTR">setDTR</a></td><td class="printindex-index-section"><a href="#Serial-Port">Serial Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-setRTS">setRTS</a></td><td class="printindex-index-section"><a href="#Serial-Port">Serial Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-SPI">SPI</a></td><td class="printindex-index-section"><a href="#SPI">SPI</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-spi">spi</a></td><td class="printindex-index-section"><a href="#SPI">SPI</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-spi_005fclose">spi_close</a></td><td class="printindex-index-section"><a href="#SPI">SPI</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-spi_005fread">spi_read</a></td><td class="printindex-index-section"><a href="#SPI">SPI</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-spi_005fwrite">spi_write</a></td><td class="printindex-index-section"><a href="#SPI">SPI</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-spi_005fwriteAndRead">spi_writeAndRead</a></td><td class="printindex-index-section"><a href="#SPI">SPI</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-spoll">spoll</a></td><td class="printindex-index-section"><a href="#GPIB">GPIB</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-srl_005fbaudrate">srl_baudrate</a></td><td class="printindex-index-section"><a href="#Serial-_0028Deprecated_0029">Serial (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-srl_005fbytesize">srl_bytesize</a></td><td class="printindex-index-section"><a href="#Serial-_0028Deprecated_0029">Serial (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-srl_005fclose">srl_close</a></td><td class="printindex-index-section"><a href="#Serial-_0028Deprecated_0029">Serial (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-srl_005fflush">srl_flush</a></td><td class="printindex-index-section"><a href="#Serial-_0028Deprecated_0029">Serial (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-srl_005fparity">srl_parity</a></td><td class="printindex-index-section"><a href="#Serial-_0028Deprecated_0029">Serial (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-srl_005fread">srl_read</a></td><td class="printindex-index-section"><a href="#Serial-_0028Deprecated_0029">Serial (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-srl_005fstopbits">srl_stopbits</a></td><td class="printindex-index-section"><a href="#Serial-_0028Deprecated_0029">Serial (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-srl_005ftimeout">srl_timeout</a></td><td class="printindex-index-section"><a href="#Serial-_0028Deprecated_0029">Serial (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-srl_005fwrite">srl_write</a></td><td class="printindex-index-section"><a href="#Serial-_0028Deprecated_0029">Serial (Deprecated)</a></td></tr>
<tr><td colspan="3"><hr></td></tr>
<tr><th id="Index_cp_letter-T">T</th></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-tcp">tcp</a></td><td class="printindex-index-section"><a href="#TCP-_0028Deprecated_0029">TCP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-TCP-_0028Deprecated_0029">TCP (Deprecated)</a></td><td class="printindex-index-section"><a href="#TCP-_0028Deprecated_0029">TCP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-TCP-Client">TCP Client</a></td><td class="printindex-index-section"><a href="#TCP-Client">TCP Client</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-TCP-Server">TCP Server</a></td><td class="printindex-index-section"><a href="#TCP-Server">TCP Server</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-tcp_005fclose">tcp_close</a></td><td class="printindex-index-section"><a href="#TCP-_0028Deprecated_0029">TCP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-tcp_005fread">tcp_read</a></td><td class="printindex-index-section"><a href="#TCP-_0028Deprecated_0029">TCP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-tcp_005ftimeout">tcp_timeout</a></td><td class="printindex-index-section"><a href="#TCP-_0028Deprecated_0029">TCP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-tcp_005fwrite">tcp_write</a></td><td class="printindex-index-section"><a href="#TCP-_0028Deprecated_0029">TCP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-tcpclient">tcpclient</a></td><td class="printindex-index-section"><a href="#TCP-Client">TCP Client</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-tcpip">tcpip</a></td><td class="printindex-index-section"><a href="#TCP-_0028Deprecated_0029">TCP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-tcpserver">tcpserver</a></td><td class="printindex-index-section"><a href="#TCP-Server">TCP Server</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-trigger">trigger</a></td><td class="printindex-index-section"><a href="#GPIB">GPIB</a></td></tr>
<tr><td colspan="3"><hr></td></tr>
<tr><th id="Index_cp_letter-U">U</th></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-udp">udp</a></td><td class="printindex-index-section"><a href="#UDP-_0028Deprecated_0029">UDP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-UDP-_0028Deprecated_0029">UDP (Deprecated)</a></td><td class="printindex-index-section"><a href="#UDP-_0028Deprecated_0029">UDP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-UDP-Port">UDP Port</a></td><td class="printindex-index-section"><a href="#UDP-Port">UDP Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-udp_005fclose">udp_close</a></td><td class="printindex-index-section"><a href="#UDP-_0028Deprecated_0029">UDP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-udp_005fdemo">udp_demo</a></td><td class="printindex-index-section"><a href="#UDP-_0028Deprecated_0029">UDP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-udp_005fread">udp_read</a></td><td class="printindex-index-section"><a href="#UDP-_0028Deprecated_0029">UDP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-udp_005ftimeout">udp_timeout</a></td><td class="printindex-index-section"><a href="#UDP-_0028Deprecated_0029">UDP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-udp_005fwrite">udp_write</a></td><td class="printindex-index-section"><a href="#UDP-_0028Deprecated_0029">UDP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-udpport">udpport</a></td><td class="printindex-index-section"><a href="#UDP-Port">UDP Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-USBTMC">USBTMC</a></td><td class="printindex-index-section"><a href="#USBTMC">USBTMC</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-usbtmc">usbtmc</a></td><td class="printindex-index-section"><a href="#USBTMC">USBTMC</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-usbtmc_005fclose">usbtmc_close</a></td><td class="printindex-index-section"><a href="#USBTMC">USBTMC</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-usbtmc_005fread">usbtmc_read</a></td><td class="printindex-index-section"><a href="#USBTMC">USBTMC</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-usbtmc_005fwrite">usbtmc_write</a></td><td class="printindex-index-section"><a href="#USBTMC">USBTMC</a></td></tr>
<tr><td colspan="3"><hr></td></tr>
<tr><th id="Index_cp_letter-V">V</th></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-VXI11">VXI11</a></td><td class="printindex-index-section"><a href="#VXI11">VXI11</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-vxi11">vxi11</a></td><td class="printindex-index-section"><a href="#VXI11">VXI11</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-vxi11_005fclose">vxi11_close</a></td><td class="printindex-index-section"><a href="#VXI11">VXI11</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-vxi11_005fread">vxi11_read</a></td><td class="printindex-index-section"><a href="#VXI11">VXI11</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-vxi11_005fwrite">vxi11_write</a></td><td class="printindex-index-section"><a href="#VXI11">VXI11</a></td></tr>
<tr><td colspan="3"><hr></td></tr>
<tr><th id="Index_cp_letter-W">W</th></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-warranty">warranty</a></td><td class="printindex-index-section"><a href="#Copying">Copying</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-Windows-install">Windows install</a></td><td class="printindex-index-section"><a href="#Installing-and-loading">Installing and loading</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-write">write</a></td><td class="printindex-index-section"><a href="#Modbus">Modbus</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-write-1">write</a></td><td class="printindex-index-section"><a href="#Serial-Port">Serial Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-write-2">write</a></td><td class="printindex-index-section"><a href="#SPI">SPI</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-write-3">write</a></td><td class="printindex-index-section"><a href="#TCP-_0028Deprecated_0029">TCP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-write-4">write</a></td><td class="printindex-index-section"><a href="#TCP-Client">TCP Client</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-write-5">write</a></td><td class="printindex-index-section"><a href="#TCP-Server">TCP Server</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-write-6">write</a></td><td class="printindex-index-section"><a href="#UDP-_0028Deprecated_0029">UDP (Deprecated)</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-write-7">write</a></td><td class="printindex-index-section"><a href="#UDP-Port">UDP Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-writeAndRead">writeAndRead</a></td><td class="printindex-index-section"><a href="#SPI">SPI</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-writebinblock">writebinblock</a></td><td class="printindex-index-section"><a href="#Common-Functions">Common Functions</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-writeline">writeline</a></td><td class="printindex-index-section"><a href="#Common-Functions">Common Functions</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-writeline-1">writeline</a></td><td class="printindex-index-section"><a href="#UDP-Port">UDP Port</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-writeread">writeread</a></td><td class="printindex-index-section"><a href="#Common-Functions">Common Functions</a></td></tr>
<tr><td></td><td class="printindex-index-entry"><a href="#index-writeRead">writeRead</a></td><td class="printindex-index-section"><a href="#Modbus">Modbus</a></td></tr>
<tr><td colspan="3"><hr></td></tr>
</table>
<table class="cp-letters-footer-printindex"><tr><th>Jump to: &nbsp; </th><td><a class="summary-letter-printindex" href="#Index_cp_letter-B"><b>B</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-C"><b>C</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-F"><b>F</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-G"><b>G</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-I"><b>I</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-L"><b>L</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-M"><b>M</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-O"><b>O</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-P"><b>P</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-R"><b>R</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-S"><b>S</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-T"><b>T</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-U"><b>U</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-V"><b>V</b></a>
 &nbsp; 
<a class="summary-letter-printindex" href="#Index_cp_letter-W"><b>W</b></a>
 &nbsp; 
</td></tr></table>
</div>
 
</div>
</div>
