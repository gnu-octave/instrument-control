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
#include <octave/oct-map.h>

#ifdef HAVE_CONFIG_H
#  include "../config.h"
#endif

#ifdef BUILD_VISA
#include <octave/uint8NDArray.h>

#include <errno.h>

#include "visadev_class.h"

#endif

// PKG_ADD: autoload ("__visadev_dispatch__", "visadev.oct");
DEFUN_DLD (__visadev_dispatch__, args, nargout,
        "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{data} = } __visadev_dispatch__ (@var{visadev}, @var{functionname}, @dots{})\n \
\n\
Private function to dispatch a function to the visadev interface.\n \
\n\
@subsubheading Inputs\n \
@var{visadev} - instance of @var{octave_visadev} class.@* \
@var{functionname} - function@* \n \
\n\
@end deftypefn")
{
#ifndef BUILD_VISA
  error("visadev: Your system doesn't support the VISADEV interface");
  return octave_value();
#else

  if (args.length() < 2 || args(0).type_id() != octave_visadev::static_type_id())
    {
      print_usage();
      return octave_value(-1);
    }

  std::string function = args(1).string_value();

  octave_visadev* visadev = NULL;

  const octave_base_value& rep = args(0).get_rep();
  visadev = &((octave_visadev &)rep);

  octave_value_list ret_value;
  
  if (function == "read")
    {
      if (args.length() < 3)
        {
          error("__visadev_dispatch__(read): expects 3 arguments");
          return octave_value();
        }	
  
      unsigned int buffer_len = 0;

      if ( !(args (2).OV_ISINTEGER () || args (2).OV_ISFLOAT ()) || args(2).int_value() < 0)
        {
          error ("Expected length to be a number value");
          return octave_value (-1);
        }

      buffer_len = args (2).int_value ();

      OCTAVE_LOCAL_BUFFER (uint8_t, buffer, (buffer_len + 1));

      if (buffer == NULL)
        {
          error ("cannot allocate requested memory");
          return octave_value (-1);  
        }
      int bytes_read = visadev->read (buffer, buffer_len);

      octave_value_list return_list;
      uint8NDArray data (dim_vector (1, bytes_read));

      for (int i = 0; i < bytes_read; i++)
        data (i) = buffer[i];

      return_list (0) = data;
      return_list (1) = bytes_read;
      ret_value = return_list;

    }
  else if (function == "write")
    {
      if (args.length() < 3)
        {
          error("__visadev_dispatch__(write): expects 3 arguments");
          return octave_value();
        }
      NDArray data = args (2).array_value ();
      OCTAVE_LOCAL_BUFFER (uint8_t, buf, (data.numel ()));

      if (buf == NULL)
        {
          error ("cannot allocate requested memory");
          return octave_value (-1);  
        }

      for (int i = 0; i < data.numel (); i++)
        buf[i] =  static_cast<uint8_t>(data(i));

     int bytes_wrote = visadev->write (buf, data.numel ());
     ret_value = octave_value(bytes_wrote);
    }
  else if (function == "properties")
    {
      string_vector a = visadev->map_keys();
      Cell fieldnames (dim_vector (1, a.numel ()));
      for (int i=0;i<a.numel();i++)
        {
          fieldnames(i) = a(i);
        }
      ret_value(0) = fieldnames;
    }
  else if (function == "flush")
    {
      if (args.length() < 3)
        {
          error("__visadev_dispatch__(flush): expects 3 arguments");
          return octave_value();
        }	
  
      unsigned int mode= 0;

      if ( !(args (2).OV_ISINTEGER () || args (2).OV_ISFLOAT ()) || args(2).int_value() < 0)
        {
          error ("Expected mode to be a number value");
          return octave_value (-1);
        }

     mode = args (2).int_value ();

     int ok = visadev->flush (mode);
     ret_value = octave_value(ok);
    }
  else if (function == "trigger")
    {
     int ok = visadev->trigger ();
     ret_value = octave_value(ok);
    }
 
  else if (function == "setRTS")
    {
      if (args.length() < 3)
        {
          error("__visadev_dispatch__(setRTS): expects 3 arguments");
          return octave_value();
        }

      if (! (args (2).OV_ISINTEGER () || args (2).OV_ISFLOAT () || args(2).OV_ISLOGICAL ()) )
        {
          error("argument must be boolean or a number");
	  return octave_value();
        }

      if (visadev->get_type() != "serial")
        {
          error("setRTS only works on ASRL devices");
          return octave_value();
        }
 
      int onoff = args (2).int_value ();
 
      int ok = visadev->set_control_line("RTS", onoff ? true : false);

      ret_value = octave_value(ok);
    }
  else if (function == "setDTR")
    {
      if (args.length() < 3)
        {
          error("__visadev_dispatch__(setDTR): expects 3 arguments");
          return octave_value();
        }

      if (! (args (2).OV_ISINTEGER () || args (2).OV_ISFLOAT () || args(2).OV_ISLOGICAL ()) )
        {
          error("argument must be boolean or a number");
	  return octave_value();
        }

      if (visadev->get_type() != "serial")
        {
          error("setDTR only works on ASRL devices");
          return octave_value();
        }
 
      int onoff = args (2).int_value ();
 
      int ok = visadev->set_control_line("DTR", onoff ? true : false);

      ret_value = octave_value(ok);
    }
  else if (function == "pinstatus")
    {
      if (args.length() < 2)
        {
          error("__visadev_dispatch__(pinstatus): expects 2 arguments");
          return octave_value();
	}
      if (visadev->get_type() != "serial")
        {
          error("pinstatus only works on ASRL devices");
          return octave_value();
        }
      octave_scalar_map res;
      res.assign ("CarrierDetect", visadev->get_control_line ("CD") ?
                               octave_value (1) :
                               octave_value (0));

      res.assign ("ClearToSend", visadev->get_control_line ("CTS") ?
                               octave_value (1) :
                               octave_value (0));

      res.assign ("DataSetReady", visadev->get_control_line ("DSR") ?
                               octave_value (1) :
                               octave_value (0));

      res.assign ("RingIndicator", visadev->get_control_line ("RI") ?
                               octave_value (0) :
                               octave_value (1));
 
      ret_value = octave_value(res);
    }
  else if (function == "status")
    {
      int stat = visadev->get_visa_status();

      ret_value = octave_value(stat);
    }
  else if (function == "terminator")
    {
      // get
      if (args.length() < 3)
        {
  // may have a single terminator or a start and stop
  octave_value in = visadev->get_input_terminator ();
  octave_value out = visadev->get_output_terminator ();

  if(in.is_string() && out.is_string() && in.string_value() == out.string_value())
    return in;
  else if(in.is_scalar_type() && out.is_scalar_type() && in.int_value() == out.int_value())
    return in;
  else
    {
      Cell ret = Cell(dim_vector(1, 2));
      ret(0) = in;
      ret(1) = out;
      return octave_value (ret);
    }

	}
      else
        {
      ret_value = octave_value((int)0);
          if (args.length() == 3)
            {
               // one terminator only
               octave_value term = args(2);
	       if ( !(term.is_string ()) && !(term.is_scalar_type()))
                 error("argument must be a string or number");
	       else
	         {
                   visadev->set_input_terminator (term);
                   visadev->set_output_terminator (term);
	         }
            }
	  else if (args.length() == 4)
            {
               octave_value interm = args(2);
	       if ( !(interm.is_string ()) && !(interm.is_scalar_type()))
                 error("argument must be a string or number");
               octave_value outterm = args(3);
	       if ( !(outterm.is_string ()) && !(outterm.is_scalar_type()))
                 error("argument must be a string or number");
            }
	  else
            {
                 error("expected as most 2 terminators");
            }

        }
      
    }

  else
    {
      error("Unknown function '%s'", function.c_str());
      return octave_value();
    }

  return ret_value;
#endif
}

#if 0
%!error __visadev_dispatch__(1)
#endif
