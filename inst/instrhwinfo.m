## Copyright (C) 2018-2020 John Donoghue <john.donoghue@ieee.org>
## Copyright (C) 2016 Andreas Weber <andy.weber.aw@gmail.com>
##
## This program is free software; you can redistribute it and/or modify it under
## the terms of the GNU General Public License as published by the Free Software
## Foundation; either version 3 of the License, or (at your option) any later
## version.
##
## This program is distributed in the hope that it will be useful, but WITHOUT
## ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
## FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
## details.
##
## You should have received a copy of the GNU General Public License along with
## this program; if not, see <http://www.gnu.org/licenses/>.

## -*- texinfo -*-
## @deftypefn {Function File} {[@var{list}] =} instrhwinfo ()
## @deftypefnx {Function File} {@var{list} =} instrhwinfo (@var{interface})
## Query available hardware for instrument-control
##
## When run without any input parameters, instrhwinfo will provide the toolbox
## information and a list of supported interfaces.
##
## @subsubheading Inputs
## @var{interface} is the instrument interface to query. When provided, instrhwinfo
## will provide information on the specified interface.
##
## Currently only interface "serialport","i2c" and "spi" and is supported, which will provide a list of
## available serial ports or i2c ports.
##
## @subsubheading Outputs
## If an output variable is provided, the function will store the information
## to the variable, otherwise it will be displayed to the screen.
##
## @subsubheading Example
## @example
## instrhwinfo
## scalar structure containing the fields:
##
##    ToolboxVersion = 0.4.0
##    ToolboxName = octave instrument control package
##    SupportedInterfaces =
##    @{
##      [1,1] = i2c
##      [1,2] = parallel
##      [1,3] = serialport
##      [1,4] = tcp
##      [1,5] = udp
##      [1,6] = usbtmc
##      [1,7] = vxi11
##    @}
##
## @end example
##
## @end deftypefn

function out = instrhwinfo (interface)

  if (nargin == 0)
    a = __instr_hwinfo__();
    if (nargout == 0)
      disp(a);
    else
      out = a;
    endif
  elseif (nargin != 1)
    print_usage ();
  elseif (strcmpi (interface, "serial"))

    if (ispc ()) # windoze

      Skey = 'HKEY_LOCAL_MACHINE\HARDWARE\DEVICEMAP\SERIALCOMM';
      ## Find connected serial devices and clean up the output
      [~, list] = dos(['REG QUERY ' Skey]);
      [~, ~, ~, out]=regexp (list, "COM[0-9]+");

    elseif (ismac ())

      tmp = glob ("/dev/tty.*");
      out = strrep (tmp, "/dev/", "");

    elseif (isunix ()) # GNU/Linux, BSD...

      ## only devices with device/driver
      tmp = glob ("/sys/class/tty/*/device/driver");
      tmp = strrep (tmp, "/sys/class/tty/", "");
      out = strrep (tmp, "/device/driver", "");

    endif
  elseif (strcmpi (interface, "serialport"))
    if (ispc ()) # windoze

      Skey = 'HKEY_LOCAL_MACHINE\HARDWARE\DEVICEMAP\SERIALCOMM';
      ## Find connected serial devices and clean up the output
      [~, list] = dos(['REG QUERY ' Skey]);
      [~, ~, ~, out]=regexp (list, "COM[0-9]+");

    elseif (ismac ())

      out = glob ("/dev/tty.*");

    elseif (isunix ()) # GNU/Linux, BSD...

      ## only devices with device/driver
      #/sys/class/tty/ttyS0/device/driver
      tmp = glob ("/sys/class/tty/*/device/driver");
      tmp = strrep (tmp, "/sys/class/tty", "/dev");
      out = strrep (tmp, "/device/driver", "");
    endif

  elseif (strcmpi (interface, "i2c"))
    if (isunix ()) # GNU/Linux, BSD...

      ## only devices with device/driver
      tmp = glob ("/sys/class/i2c-adapter/*/device/driver");
      tmp = strrep (tmp, "/sys/class/i2c-adapter/", "");
      out = strrep (tmp, "/device/driver", "");
    else
      out = [];
    endif

  elseif (strcmpi (interface, "spi"))
    if (isunix ()) # GNU/Linux, BSD...

      ## only devices with device/driver
      tmp = glob ("/sys/class/spidev/*/device/driver");
      tmp = strrep (tmp, "/sys/class/spidev/", "");
      out = strrep (tmp, "/device/driver", "");
    else
      out = [];
    endif

   else
    error ("Interface '%s' not yet implemented...", interface);
  endif

endfunction

%!test
%! a = instrhwinfo();
%! assert(! isempty (a))

%!xtest
%! # could fail if no serial ports?
%! assert(!isempty(instrhwinfo("serial")))

%!error instrhwinfo("serial", "2ndarg")

%!xtest
%! # could fail if no i2c ports or not configured
%! assert(!isempty(instrhwinfo("i2c")))

%!test
%! p = pkg('describe', 'instrument-control');
%! hw = instrhwinfo ();
%! assert (hw.ToolboxVersion, p{1}.version)
