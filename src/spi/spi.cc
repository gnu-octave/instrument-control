// Copyright (C) 2020   John Donoghue   <john.donoghue@ieee.org>
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
#include "../config.h"
#endif

#ifdef BUILD_SPI
#include <fcntl.h>

#include "spi_class.h"
#endif

// PKG_ADD: autoload ("spi", "spi.oct");
DEFUN_DLD (spi, args, nargout, 
        "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{spi} = } spi ([@var{port_path}])\n \
@deftypefnx {Loadable Function} {@var{spi} = } spi ([@var{port_path}], [@var{propname}, @var{provalue}])\n \
\n\
Open spi interface.\n \
\n\
@subsubheading Inputs\n \
@var{port_path} - the interface device port/path of type String. If omitted defaults to \n \
'/dev/spi-0'. @*\n \
@var{address} - the slave device address. If omitted must be set using spi_addr() call.@*\n \
@var{propname},@var{propvalue} - property name/value pairs.\n \
\n\
Known input properties:\n \
@table @asis\n \
@item name\n \
Name of the object\n \
@item bitrate\n \
Numeric bitrate value\n \
@item clockpolarity\n \
Clock polarity: idlehigh or idlelow.\n \
@item clockphase\n \
Clock phase value: firstededge or secondedge\n \
@end table\n \
\n\
@subsubheading Outputs\n \
@var{spi} - An instance of @var{octave_spi} class.\n \
\n\
@subsubheading Properties\n \
The spi object has the following properties:\n \
@table @asis\n \
@item name\n \
Name of the object\n \
@item bitrate\n \
Numeric bitrate value\n \
@item clockpolarity\n \
Clock polarity: idlehigh or idlelow.\n \
@item clockphase\n \
Clock phase value: firstededge or secondedge\n \
@item port\n \
The interface driver port (readonly)\n \
@end table\n \
@end deftypefn")
{
#ifndef BUILD_SPI
  error ("spi: Your system doesn't support the SPI interface");
  return octave_value ();
#else
    
  // Do not open interface if return value is not assigned
  if (nargout != 1)
    {
      print_usage ();
      return octave_value ();
    }

  // Default values
  int oflags = O_RDWR;
  std::string path ("/dev/spi-0");
  unsigned int bitrate = 0;
  std::string polarity = "";
  std::string phase = "";
  std::string objname = "";
 
  // Parse the function arguments
  if (args.length () > 0)
    {
      if (args (0).is_string ())
        {
          path = args (0).string_value ();
        }
      else
        {
          print_usage ();
          return octave_value ();
        }

    }

  if (args.length() > 1 && (args.length() & 1)  == 0)
    {
      error ("Expected property name/value pairs");
          return octave_value ();
    }
   
  for(int i=1;i<args.length();i+=2)
    {
      // first pair should be a property name
      if (! args (i).is_string ())
        {
          error ("Expected property name string");
          return octave_value ();
        }

      std::string name = args (i).string_value ();
      octave_value val = args (i+1);

      std::transform (name.begin (), name.end (), name.begin (), ::tolower);

      if (name == "bitrate")
        {
          if ((val.OV_ISINTEGER () || val.OV_ISFLOAT ()) && (val.int_value () > 0))
            bitrate = val.int_value ();
          else
            {
              error ("bitrate must be a positive integer");
              return octave_value();
            }
	}
      else if (name == "clockpolarity")
        {
          if (val.is_string ())
            polarity = val.string_value ();
          else
            {
              error ("polarity must be a string");
              return octave_value();
            }
	}
      else if (name == "clockphase")
        {
          if (val.is_string ())
            phase = val.string_value ();
          else
            {
              error ("phase must be a string");
              return octave_value();
            }
	}
      else if (name == "name")
        {
          if (val.is_string ())
            objname = val.string_value ();
          else
            {
              error ("name must be a string");
              return octave_value();
            }
	}
      else
        {
          error ("unknown property '%s'", name.c_str());
          return octave_value();
        }
    }

  octave_spi* retval = new octave_spi ();

  // Open the interface
  if (retval->open (path, oflags) < 0)
    return octave_value ();

  if (bitrate > 0)
    retval->set_bitrate (bitrate);

  if (objname.length() > 0)
    retval->set_name (objname);

  if (polarity.length() > 0)
    retval->set_clockpolarity (polarity);

  if (phase.length() > 0)
    retval->set_clockphase (phase);

  return octave_value (retval);
#endif
}

#if 0

%!test
%! if any(strcmp(instrhwinfo().SupportedInterfaces, "spi"))
%!   fail ("spi ()", "Invalid call to spi");
%! else
%!   fail ("spi ()", "spi: Your system doesn't support the SPI interface");
%! endif

#endif
