// Copyright (C) 2020 John Donoghue   <john.donoghue@ieee.org>
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

#ifdef BUILD_UDP
#  include "udpport_class.h"
#endif

// PKG_ADD: autoload ("udpport", "udpport.oct");
DEFUN_DLD (udpport, args, nargout,
        "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{udp} = } udpport ()\n \
@deftypefnx {Loadable Function} {@var{udp} = } udpport (@var{propertyname}, @var{propertyvalue} ...)\n \
\n\
Open udpport interface.\n \
\n\
@subsubheading Inputs\n \
@var{propertyname}, @var{propertyvalue} - property name/value pair\n \
\n\
Known input properties:\n \
@table @asis\n \
@item Name\n \
name assigned to the udp object\n \
@item LocalPort\n \
local port number\n \
@item LocalHost\n \
local host address\n \
@item Timeout\n \
timeout value in seconds used for waiting for data\n \
@item EnablePortSharing\n \
Boolean if the socket has port sharing enabled (readonly)\n \
@end table \n \
\n\
@subsubheading Outputs\n \
The udpport() shall return instance of @var{octave_udp} class as the result @var{udp}.\n \
\n \
@subsubheading Properties\n \
The udp object has the following public properties:\n \
@table @asis\n \
@item Name\n \
name assigned to the udp object\n \
@item Type\n \
instrument type 'udpport' (readonly)\n \
@item LocalPort\n \
local port number (readonly)\n \
@item LocalHost\n \
local host address (readonly)\n \
@item Status\n \
status of the object 'open' or 'closed' (readonly)\n \
@item Timeout\n \
timeout value in seconds used for waiting for data\n \
@item NumBytesAvailable\n \
number of bytes currently available to read (readonly)\n \
@item MulticastGroup\n \
multicast group socket  is subscribed to (readonly)\n \
@item EnableMultcast\n \
Boolean if the socket has any multicast group it is subscribed to (readonly)\n \
@item EnablePortSharing\n \
Boolean if the socket has port sharing enabled (readonly)\n \
@item Terminator\n \
Terminator value used for string data (currently not used)\n \
@end table \n \
@end deftypefn")
{
#ifndef BUILD_UDP
  error("udpport: Your system doesn't support the UDPPORT interface");
  return octave_value();
#else
  // Do not open interface if return value is not assigned
  if (nargout != 1)
    {
      print_usage();
      return octave_value();
    }

  // Default values
  std::string name = "";
  std::string localhost("0.0.0.0");
  int localport = 0;
  double timeout = -1;
  int portshare = 0;

  if (args.length() > 0 && ((args.length() & 1)  == 1))
    {
      error ("Expected property name/value pairs");
      return octave_value ();
    }

  if (args.length() > 0)
    {
      // go through the properties
      for(int i=0;i<args.length();i+=2)
        {
          if (!args(i).is_string())
	    {
              error ("Expected property name as a string");
	      return octave_value ();
	    }
          std::string pname = args(i).string_value();
          octave_value pval = args(i+1);

          std::transform (pname.begin (), pname.end (), pname.begin (), ::tolower);

          if (pname == "localport")
            {
              if (pval.OV_ISINTEGER () || pval.OV_ISFLOAT ())
                localport = pval.int_value ();
              else
                {
                  error ("localport must be a integer");
                  return octave_value();
                }
	    }
	  else if (pname == "localhost")
            {
              if (pval.is_string ())
                localhost = pval.string_value ();
              else
                {
                  error ("localhost must be a string");
                  return octave_value();
                }
	    }

          else if (pname == "timeout")
            {
              if (pval.OV_ISINTEGER () || pval.OV_ISFLOAT ())
                timeout = pval.double_value ();
              else
                {
                  error ("timeout must be a integer or double");
                  return octave_value();
                }
	    }
          else if (pname == "enableportsharing")
            {
              if (pval.OV_ISINTEGER () || pval.OV_ISFLOAT () || pval.OV_ISLOGICAL ())
                portshare = pval.int_value ();
              else
                {
                  error ("enableportsharing must be a integer or logical type");
                  return octave_value();
                }
	    }
          else if (pname == "name")
            {
              if (pval.is_string ())
                name = pval.string_value ();
              else
                {
                  error ("name must be a string");
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
  octave_udpport* retval = new octave_udpport();

  if (retval->open(localhost, localport, portshare) < 0)
    {
      return octave_value();
    }

  retval->set_timeout(timeout);

  if(name.length() > 0)
    retval->set_name(name);

  return octave_value(retval);
#endif
}

#if 0
%!test
%! # can create default udp object
%! a = udpport ();
%! assert (! isnull (a));
%! assert (isa (a, 'octave_udpport'));
%! clear a;

%!error <Expected property name/value pairs> a = udpport (1)

%!test
%! a = udpport ("Name", "test", "Timeout", 2.5);
%! assert (! isnull (a));
%! assert (a.Name, "test");
%! assert (a.Timeout, 2.5);
%! clear a;

#endif
