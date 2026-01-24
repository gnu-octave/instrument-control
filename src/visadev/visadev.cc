// Copyright (C) 2025 John Donoghue   <john.donoghue@ieee.org>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.

#include <octave/oct.h>

#ifdef HAVE_CONFIG_H
#  include "../config.h"
#endif

#ifdef BUILD_VISA
#  include "visadev_class.h"
#endif

// PKG_ADD: autoload ("visadev", "visadev.oct");
DEFUN_DLD (visadev, args, nargout,
        "-*- texinfo -*-\n\
@deftypefn {} {@var{dev} = } visadev (@var{resourcename})\n \
@deftypefnx {} {@var{dev} = } visadev (@var{resourcename}, @var{propertyname}, @var{propertyvalue} @dots{})\n \
\n\
Open visadev interface.\n \
\n\
@subsubheading Inputs\n \
@var {resourcename} - name of visadev device to open.\n\
\n\
@var{propertyname}, @var{propertyvalue} - property name/value pair\n \
\n\
Known input properties:\n \
@table @asis\n \
@item Tag\n \
tag value assigned to the visadev object\n \
@item Timeout\n \
timeout value in seconds used for waiting for data\n \
@end table \n \
\n\
@subsubheading Outputs\n \
visadev() shall return instance of @var{octave_visadev} class as the result @var{dev}.\n \
\n \
@subsubheading Properties\n \
The visadev object has the following public properties:\n \
@table @asis\n \
@item Tag\n \
user tag assigned to the visadev object\n \
@item Type\n \
instrument type (readonly)\n \
@item Status\n \
status of the object 'open' or 'closed' (readonly)\n \
@item Timeout\n \
timeout value in seconds used for waiting for data\n \
@item NumBytesAvailable\n \
number of bytes currently available to read (readonly)\n \
@item MulticastGroup\n \
multicast group socket  is subscribed to (readonly)\n \
@item Terminator\n \
Terminator value used for string data (readonly)\n \
@end table \n \
\n \
Other properties are available depending on the visadev type and can \n \
be retrieved using te properties function.\n \
\n \
@seealso{properties, visadevlist}\n \
@end deftypefn")
{
#ifndef BUILD_VISA
  error("visadev: Your system doesn't support the VISA interface");
  return octave_value();
#else
  // Do not open interface if return value is not assigned
  if (nargout != 1)
    {
      print_usage();
      return octave_value();
    }

  if (args.length() < 1 || !args(0).is_string())
    {
      error ("Expected resource name");
      return octave_value ();
    }

  std::string resource = args(0).string_value();

  // Default values
  std::string name = "";
  std::string tag = "";
  double timeout = 10.0;

  if (args.length() > 1 && ((args.length() & 1)  == 0))
    {
      error ("Expected property name/value pairs");
      return octave_value ();
    }

  if (args.length() > 0)
    {
      // go through the properties
      for(int i=1;i<args.length();i+=2)
        {
          if (!args(i).is_string())
	    {
              error ("Expected property name as a string");
	      return octave_value ();
	    }
          std::string pname = args(i).string_value();
          octave_value pval = args(i+1);

          std::transform (pname.begin (), pname.end (), pname.begin (), ::tolower);

          if (pname == "timeout")
            {
              if (pval.OV_ISINTEGER () || pval.OV_ISFLOAT ())
                timeout = pval.double_value ();
              else
                {
                  error ("timeout must be a integer or double");
                  return octave_value();
                }
	    }
          /*else if (pname == "name")
            {
              if (pval.is_string ())
                name = pval.string_value ();
              else
                {
                  error ("name must be a string");
                  return octave_value();
                }
	    }
	    */
          else if (pname == "tag")
            {
              if (pval.is_string ())
                tag = pval.string_value ();
              else
                {
                  error ("tag must be a string");
                  return octave_value();
                }
	    }
          else
            {
              error ("unknown property '%s'", pname.c_str());
              return octave_value();
            }
        }
    }

  // Open the interface and connect
  octave_visadev* retval = new octave_visadev();

  if (retval->open(resource) < 0)
    {
      return octave_value();
    }

  retval->set_timeout(timeout);
  retval->set_tag(tag);

  return octave_value(retval);
#endif
}

#if 0
%!xtest
%! # can create a serial obj
%! a = visadev('ASRL1::INSTR');
%! assert (isa (a, 'octave_visadev'));
%! assert (a.Type, "serial");
%! clear a;

%!error a = visadev (1)

#endif
