// Copyright (C) 2020  John Donoghue <john.donoghue@ieee.org>
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
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>


#include "spi_class.h"

DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_spi, "octave_spi", "octave_spi");

octave_spi::octave_spi (void)
  : fieldnames(6)
{
  static bool type_registered = false;

  if (! type_registered)
    {
      type_registered = true;
      register_type ();
    }
 
  fd = -1;
  mode = 0;
  bitrate = 250000;

  fieldnames[0] = "status";
  fieldnames[1] = "name";
  fieldnames[2] = "port";
  fieldnames[3] = "bitrate";
  fieldnames[4] = "clockpolarity";
  fieldnames[5] = "clockphase";
}

octave_spi::~octave_spi (void)
{
  octave_spi::close ();
}

int
octave_spi::get_fd (void) const
{
  return fd;
}

void
octave_spi::print (std::ostream& os, bool pr_as_read_syntax)
{
  print_raw (os, pr_as_read_syntax);
  newline (os);
}

void
octave_spi::print (std::ostream& os, bool pr_as_read_syntax ) const
{
  print_raw (os, pr_as_read_syntax);
  newline (os);
}

void
octave_spi::print_raw (std::ostream& os, bool pr_as_read_syntax) const
{
  os << "  SPI Object " << this->get_name(); newline(os);
  os << "    status:   " << this->get_status(); newline(os);
  if (get_fd() > -1)
    {
      os << "    bitrate:   " << this->get_bitrate();
      newline(os);
    }
}

int
octave_spi::open (const std::string &path, int flags)
{
  port = path;
  name = "SPI-" + path;

  fd = ::open (path.c_str (), flags, 0);

  if (get_fd () < 0)
    {
      error ("spi: Error opening the interface: %s\n", strerror (errno));
      return -1;
    }

  __u8 dmode, dlsb, dbits;
  __u32 dspeed;

  mode = 0;
  if (ioctl(get_fd (), SPI_IOC_RD_MODE, &dmode) < 0)
    {
      warning ("spi: failed to read RD mode: %s\n", strerror (errno));
    }
  else
    {
      mode = dmode;
    }

  if (ioctl(get_fd (), SPI_IOC_RD_LSB_FIRST, &dlsb) < 0)
    {
      warning ("spi: failed to read LSB mode: %s\n", strerror (errno));
    }
  if (ioctl(get_fd (), SPI_IOC_RD_BITS_PER_WORD, &dbits) < 0)
    {
      warning ("spi: failed to read bits per word: %s\n", strerror (errno));
    }

  bitrate = 250000;
  if (ioctl(get_fd (), SPI_IOC_RD_MAX_SPEED_HZ, &dspeed) < 0)
    {
      warning ("spi: failed to read speed: %s\n", strerror (errno));
    }
  else
    {
       if (bitrate > dspeed)
         bitrate = dspeed;
    }

  return get_fd ();
}

int
octave_spi::read (uint8_t *buf, unsigned int len)
{   
  if (get_fd () < 0)
    {
      error ("spi: Interface must be open first...");
      return -1;
    }

  int retval = -1;

//  retval = ::read (get_fd (), buf, len);
  struct spi_ioc_transfer tr;
  memset(&tr, 0, sizeof(tr));

  tr.rx_buf = (__u64)buf;
  //tr.tx_buf = (__u64)tbuf;
  tr.len = len; /* Length of  command to write*/
  tr.cs_change = 0; /* Keep CS activated */
  tr.delay_usecs = 0; //delay in us
  tr.speed_hz = bitrate; //speed
  tr.bits_per_word = 8; // bits per word 8
 
  retval = ioctl(get_fd (), SPI_IOC_MESSAGE(1), &tr);

  if (retval < 0)
    error ("spi: Failed to read from the spi bus: %s\n", strerror (errno));

  return retval;
}

int
octave_spi::write (uint8_t *buf, unsigned int len)
{
  if (get_fd () < 0)
    {
      error ("spi: Interface must be open first...");
      return -1;
    }

  int retval = -1;

//  retval = ::write (get_fd (), buf, len);
  struct spi_ioc_transfer tr;
  memset(&tr, 0, sizeof(tr));

  tr.tx_buf = (__u64)buf;
  //tr.rx_buf = (__u64)rbuf;
  tr.len = len; /* Length of  command to write*/
  tr.cs_change = 0; /* Keep CS activated */
  tr.delay_usecs = 0; //delay in us
  tr.speed_hz = bitrate; //speed
  tr.bits_per_word = 8; // bits per word 8
 
  retval = ioctl(get_fd (), SPI_IOC_MESSAGE(1), &tr);


  if (retval < 0)
    error ("spi: Failed to write to the spi bus: %s\n", strerror (errno));

  return retval;
}

int
octave_spi::writeRead (uint8_t *wbuf, unsigned int wlen, uint8_t *rbuf)
{
  if (get_fd () < 0)
    {
      error ("spi: Interface must be open first...");
      return -1;
    }

  int retval = -1;

  struct spi_ioc_transfer tr;
  memset(&tr, 0, sizeof(tr));

  tr.tx_buf = (__u64)wbuf;
  tr.rx_buf = (__u64)rbuf;
  tr.len = wlen; /* Length of  command to write*/
  tr.cs_change = 0; /* Keep CS activated */
  tr.delay_usecs = 0; //delay in us
  tr.speed_hz = bitrate; //speed
  tr.bits_per_word = 8; // bits per word 8
 
  retval = ioctl(get_fd (), SPI_IOC_MESSAGE(1), &tr);

  if (retval < 0)
    error ("spi: Failed to writeRead to the spi bus: %s\n", strerror (errno));

  return retval;
}


int
octave_spi::close (void)
{
  int retval = -1;

  if (get_fd () > 0)
    {
      retval = ::close(get_fd ());
      fd = -1;
    }

  return retval;
}

std::string
octave_spi::get_port () const
{
  return port;
}

std::string
octave_spi::get_name () const
{
  return name;
}

std::string
octave_spi::get_clockpolarity () const
{
  if(mode & SPI_CPOL) return "idlehigh";
  else return "idlelow";
}

std::string
octave_spi::set_clockpolarity (const std::string &newpolarity)
{
  std::string polarity = newpolarity;
  std::transform (polarity.begin (), polarity.end (), polarity.begin (), ::tolower);

  int newmode = mode;
  if(polarity == "idlelow")
    newmode = mode & ~SPI_CPOL;
  else if(polarity == "idlehigh")
    newmode = mode | SPI_CPOL;

  __u8 dmode = newmode;

  if(ioctl(fd, SPI_IOC_WR_MODE, &dmode) < 0)
    {
      error ("spi: failed to mode: %s\n", strerror (errno));
    }
  else
    {
      mode = newmode;
    }

  return get_clockpolarity();
}

std::string
octave_spi::get_clockphase () const
{
  if(mode & SPI_CPHA) return "secondedge";
  else return "firstedge";
}

std::string
octave_spi::set_clockphase (const std::string &newphase)
{
  std::string phase = newphase;
  std::transform (phase.begin (), phase.end (), phase.begin (), ::tolower);

  int newmode = mode;
  if(phase == "firstedge")
    newmode = mode & ~SPI_CPHA;
  else if(phase == "secondedge")
    newmode = mode | SPI_CPHA;

  __u8 dmode = newmode;

  if(ioctl(fd, SPI_IOC_WR_MODE, &dmode) < 0)
    {
      error ("spi: failed to mode: %s\n", strerror (errno));
    }
  else
    {
      mode = newmode;
    }
  return get_clockphase();
}

std::string
octave_spi::set_name (const std::string &newname)
{
  name = newname;
  return name;
}

unsigned long
octave_spi::get_bitrate () const
{
  return bitrate;
}

unsigned long
octave_spi::set_bitrate (unsigned long newbitrate)
{
  __u32 speed = newbitrate;
  if (ioctl(get_fd (), SPI_IOC_WR_MAX_SPEED_HZ, &speed) < 0)
    {
      error ("spi: failed to set speed: %s\n", strerror (errno));
    }
  else
    {
      bitrate = newbitrate;
    }
  return bitrate;
}

std::string
octave_spi::get_status () const
{
  if (get_fd () > -1)
    return "open";
  else
    return "closed";
}

octave_value_list
octave_spi::subsref (const std::string& type, const std::list<octave_value_list>& idx, int nargout)
{
  octave_value_list retval;
  int skip = 1;

  switch (type[0])
    {
    default:
      error ("octave_spi object cannot be indexed with %c", type[0]);
      break;
    case '.':
      {
        octave_value_list ovl;
        // inc ref count as assign this to octave_value
        count++; 
        ovl (0) = octave_value (this);
        ovl (1) = (idx.front ()) (0);
        retval = OCTAVE__FEVAL (std::string ("__spi_properties__"), ovl, 1);
      }
      break;
    }

  if (idx.size () > 1 && type.length () > 1)
    retval = retval (0).next_subsref (nargout, type, idx, skip);

  return retval;
}

octave_value
octave_spi::subsasgn (const std::string& type, const std::list<octave_value_list>& idx, const octave_value& rhs)
{
  octave_value retval;

  switch (type[0])
    {
    default:
      error ("octave_spi object cannot be indexed with %c", type[0]);
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
          OCTAVE__FEVAL (std::string ("__spi_properties__"), ovl, 0);
 
          count++;
          retval = octave_value (this);
        }
      else if (type.length () > 1 && type[1] == '.')
        {
          // pass along any further assignments
          octave_value_list u = subsref (type.substr (0, 1), idx, 1);
          if (u.length() > 0)
            {
              std::list<octave_value_list> next_idx (idx);
              next_idx.erase (next_idx.begin ());
              u (0).subsasgn(type.substr (1), next_idx, rhs);
              count++;
              retval = octave_value (this);
            } 
        }
      else
        {
          error ("octave_spi invalid index");
        }

    }
  return retval;
}

#endif
