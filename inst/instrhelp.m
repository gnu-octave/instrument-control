## Copyright (C) 2019 John Donoghue <john.donoghue@ieee.org>
## 
## This program is free software: you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.

## -*- texinfo -*- 
## @deftypefn {} {} instrhelp ()
## @deftypefnx {} {} instrhelp (@var{funcname})
## @deftypefnx {} {} instrhelp (@var{obj})
## Display instrument help
##
## @subsubheading Inputs
## @var{funcname} - function to display help about
## @var{obj} - object to display help about
##
## @subsubheading Outputs
## None
##
## @end deftypefn

function ret = instrhelp (varargin)
   if nargin < 1
     v = "__instrument_control__";
   else
     v = varargin{1};
     if !ischar(v)
       v = typeinfo(v);
       if !strncmp(v, "octave_", 7)
         error ('expected instrument control device');
       endif

       v = strrep(v, "octave_", "");
     endif
   endif

   if nargout > 0
     out = help(v);
   else
     help(v);
   endif

endfunction

%!test
%! instrhelp ("instrhelp")

%!error instrhelp (1)
