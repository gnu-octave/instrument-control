// Copyright (C) 2019   John Donoghue   <john.donoghue@ieee.org>
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

#ifdef HAVE_CONFIG_H
#include "../config.h"
#endif

#ifdef BUILD_SERIAL
#include "serialport_class.h"
#include <octave/Matrix.h>
#include <string>
#include <algorithm>

octave_serialport_common::octave_serialport_common ()
 : fieldnames(12)
{
  byteswritten = 0;
  userData = Matrix ();

  interminator = "lf";
  outterminator = "lf";
  byteOrder = "little-endian";

  fieldnames[0] = "baudrate";
  fieldnames[1] = "databits";
  fieldnames[3] = "parity";
  fieldnames[4] = "stopbits";
  fieldnames[5] = "timeout";
  fieldnames[6] = "numbytesavailable";
  fieldnames[7] = "numbyteswritten";
  fieldnames[8] = "port";
  fieldnames[9] = "flowcontrol";
  fieldnames[10] = "userdata";
  fieldnames[11] = "byteorder";
}

octave_value_list
octave_serialport_common::subsref (const std::string& type, const std::list<octave_value_list>& idx, int nargout)
{
  octave_value_list retval;
  int skip = 1;

  switch (type[0])
    {
    default:
      error ("octave_serialport object cannot be indexed with %c", type[0]);
      break;
    case '.':
      {
        octave_value_list ovl;
        // inc ref count as assign this to octave_value
        count++; 
        ovl (0) = octave_value (this);
        ovl (1) = (idx.front ()) (0);
        retval = OCTAVE__FEVAL (std::string ("__srlp_properties__"), ovl, 1);
      }
      break;
    }

  if (idx.size () > 1 && type.length () > 1)
    retval = retval (0).next_subsref (nargout, type, idx, skip);

  return retval;
}

octave_value
octave_serialport_common::subsasgn (const std::string& type, const std::list<octave_value_list>& idx, const octave_value& rhs)
{
  octave_value retval;

  switch (type[0])
    {
    default:
      error ("octave_serialport object cannot be indexed with %c", type[0]);
      break;
    case '.':
      if (type.length () == 1)
        {
          octave_value_list ovl;
          // inc ref count as assign this to octave_value
          count++; 
          ovl (0) = octave_value (this);
          ovl (1) = (idx.front ()) (0);
          ovl (2) = rhs;
          OCTAVE__FEVAL (std::string ("__srlp_properties__"), ovl, 1);
 
          // property assignment
          if (! error_state)
            {
              count++;
              retval = octave_value (this);
            }
        }
      else if (type.length () > 1 && type[1] == '.')
        {
          // pass along any further assignments
          octave_value_list u = subsref (type.substr (0, 1), idx, 1);
          if (! error_state)
            {
              std::list<octave_value_list> next_idx (idx);
              next_idx.erase (next_idx.begin ());
              u (0).subsasgn(type.substr (1), next_idx, rhs);
              if (!error_state)
                {
                  count++;
                  retval = octave_value (this);
                }
            } 
        }
      else
        {
          error ("octave_serialport invalid index");
        }

    }
  return retval;
}

int
octave_serialport_common::set_byteorder(const std::string& neworder)
{
  std::string order = neworder;
  std::transform (order.begin (), order.end (), order.begin (), ::tolower);
  if (order == "big" || order == "big-endian")
    byteOrder = "big-endian";
  else if (order == "little" || order == "little-endian")
    byteOrder = "little-endian";
 else
    error ("octave_serialport invalid byteorder");

 return 1;
}

int
octave_serialport_common::set_input_terminator(const std::string& t)
{
  std::string term = t;
  std::transform (term.begin (), term.end (), term.begin (), ::tolower);
  if (term != "lf" && term != "cr" && term != "cr/lf")
    error ("octave_serialport invalid input terminator");
  else
    interminator = term;

 return 1;
}

int
octave_serialport_common::set_output_terminator(const std::string& t)
{
  std::string term = t;
  std::transform (term.begin (), term.end (), term.begin (), ::tolower);
  if (term != "lf" && term != "cr" && term != "cr/lf")
    error ("octave_serialport invalid output terminator");
  else
    outterminator = term;

 return 1;
}


#endif
