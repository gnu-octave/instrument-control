## Copyright (C) 2014 Stefan Mahr <dac922@gmx.de>
## Copyright (C) 2019 John Donoghue <john.donoghue@ieee.org>
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
## @deftypefn {Loadable Function} {} srl_close (@var{serial})
##
## Close the interface and release a file descriptor.
##
## @subsubheading Inputs
## @var{serial} - instance of @var{octave_serial} class.
##
## This function is obsolete. Use fclose() method instead.
##
## @subsubheading Outputs
## None
##
## @end deftypefn
function srl_close (serial)

  try
    __srl_properties__ (serial, 'close');
  catch
    print_usage();
  end
end
