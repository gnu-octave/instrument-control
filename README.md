Introduction
============

The Instrument control package provides low level I/O functions for serial, i2c, spi, parallel, tcp,
gpib, vxi11, modbus, udp and usbtmc interfaces.

It attempts to provide the same function calls as the Matlab toolkit, as well as additional functionality.

Requirements
============

* Octave >= 4.0.0

* linux-gpib (Linux only)

* libmodbus for MOSBUS support

* rpcgen and libtirpc for VXI11 support


Installing
==========

To install, run the octave package manager:

1. If running Windows, the package may already be installed:
   type pkg list, to view the installed packages.

2. To install from source forge:
   pkg install -forge instrument-control

3. To install from a local tarball.
   pkg install instrument-control-XXXXXXX.tar.gz
   Where XXXXXXX is the version of the the downloaded tarball.

Usage:
======

1. Load the package.
   pkg load instrument-control
   (Required each time Octave is started)

2. Use the function calls to control the instrument hardware.

Documentation
==============

See the function list for instrument-control on [octave forge](https://octave.sourceforge.io/instrument-control/overview.html) for function documentation.

Read the Octave [instrument-control wiki](https://wiki.octave.org/Instrument_control_package) for install tips and examples.

Known limitations and bugs
==========================

None provided
