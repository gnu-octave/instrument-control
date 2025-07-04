// Copyright (C) 2016-2019   John Donoghue   <john.donoghue@ieee.org>
// Copyright (C) 2013   Stefan Mahr     <dac922@gmx.de>
// Copyright (C) 2012   Andrius Sutas   <andrius.sutas@gmail.com>
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

#ifdef BUILD_UDP
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

#ifndef __WIN32__
#  include <unistd.h>
#  include <errno.h>
#  include <netinet/in.h>
#  include <sys/socket.h>
#  include <netdb.h>
#  include <arpa/inet.h>
#  include <termios.h>
#  include <sys/ioctl.h>
#  define IOCTL_TYPE int
#else
#  include <winsock2.h>
#  define IOCTL_TYPE u_long
#  define ioctl ioctlsocket
#endif

#include "udp_class.h"

#ifndef __WIN32__
#  define SOCKETERR errno
#  define STRSOCKETERR strerror(errno)
#else
#  define SOCKETERR WSAGetLastError()
#  define STRSOCKETERR ""
#  define socklen_t int
#endif

static struct timeval
to_timeval(int ms)
{
  struct timeval tv;
  if(ms <= 0)
    {
      tv.tv_usec = 0;
      tv.tv_sec = 0;
    }
    else
    {
      tv.tv_usec = (ms % 1000) * 1000;
      tv.tv_sec = ms/1000;;
    }
  return tv;
}

static std::string 
to_ip_str (const sockaddr_in *in)
{
  u_long addr = ntohl (in->sin_addr.s_addr);

  int b[4];
  b[0] = (addr>>24)&0xff;
  b[1] = (addr>>16)&0xff;
  b[2] = (addr>>8)&0xff;
  b[3] = (addr>>0)&0xff;

  std::stringstream n;
  n << b[0] << "." << b[1] << "." << b[2] << "." << b[3];

  return n.str ();
}

static bool 
lookup_addr (const std::string &ip, sockaddr_in *in)
{
  in->sin_addr.s_addr = inet_addr (ip.c_str());

  if (in->sin_addr.s_addr == INADDR_NONE)
    {
      struct hostent * host = gethostbyname (ip.c_str());
      if (!host)
        return false;

      memcpy(&in->sin_addr, host->h_addr_list[0], host->h_length);
    }

  return true;
}

DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_udp, "octave_udp", "octave_udp");

octave_udp::octave_udp (void)
: buffer_len(0), fd(-1), timeout(-1), name(""), fieldnames(9)
{
  static bool type_registered = false;

  if (! type_registered)
    {
      type_registered = true;
      register_type ();
    }
  fieldnames[0] = "type";
  fieldnames[1] = "name";
  fieldnames[2] = "remoteport";
  fieldnames[3] = "remotehost";
  fieldnames[4] = "localport";
  fieldnames[5] = "status";
  fieldnames[6] = "timeout";
  fieldnames[7] = "bytesavailable";
  fieldnames[8] = "localhost";
}

octave_value_list
octave_udp::subsref (const std::string& type, const std::list<octave_value_list>& idx, int nargout)
{
  octave_value_list retval;
  int skip = 1;

  switch (type[0])
    {
    default:
      error ("octave_udp object cannot be indexed with %c", type[0]);
      break;
    case '.':
      {
        octave_value_list ovl;
        // inc ref count as assign this to octave_value
        OV_COUNT++; 
        ovl (0) = octave_value (this);
        ovl (1) = (idx.front ()) (0);
        retval = OCTAVE__FEVAL (std::string ("__udp_properties__"), ovl, 1);
      }
      break;
    }

  if (idx.size () > 1 && type.length () > 1)
    retval = retval (0).next_subsref (nargout, type, idx, skip);

  return retval;
}

octave_value
octave_udp::subsasgn (const std::string& type, const std::list<octave_value_list>& idx, const octave_value& rhs)
{
  octave_value retval;

  switch (type[0])
    {
    default:
      error ("octave_udp object cannot be indexed with %c", type[0]);
      break;
    case '.':
      if (type.length () == 1)
        {
          octave_value_list ovl;
          // inc ref count as assign this to octave_value
          OV_COUNT++; 
          ovl (0) = octave_value (this);
          ovl (1) = (idx.front ()) (0);
          ovl (2) = rhs;
          OCTAVE__FEVAL (std::string ("__udp_properties__"), ovl, 0);
          OV_COUNT++;
          retval = octave_value (this);
        }
      else if (type.length () > 1 && type[1] == '.')
        {
          // pass along any further assignments
          octave_value_list u = subsref (type.substr (0, 1), idx, 1);
          if (u.length () > 0)
            {
              std::list<octave_value_list> next_idx (idx);
              next_idx.erase (next_idx.begin ());
              u (0).subsasgn(type.substr (1), next_idx, rhs);
              OV_COUNT++;
              retval = octave_value (this);
            } 
        }
      else
        {
          error ("octave_udp invalid index");
        }

    }
  return retval;
}

int
octave_udp::open (const std::string &address, int port, int localport)
{
  int sockerr;

  name = "UDP-" + address;

#ifdef __WIN32__
  WORD wVersionRequested;
  WSADATA wsaData;
  int err;

  wVersionRequested = MAKEWORD( 2, 2 );
  err = WSAStartup (wVersionRequested, &wsaData );
  if ( err != 0 )
    {
      error( "could not initialize winsock library" );
      return -1;
    }
#endif

  memset (&remote_addr, 0, sizeof (remote_addr));

  if( !lookup_addr (address, &remote_addr))
    {
      int err = SOCKETERR;
      octave_udp::close ();
      error ("udp: error looking up remote host : %d - %s\n", err, STRSOCKETERR);
      return -1;
    }

  // default size for now
  input_buffer = new uint8_t[1024];
  buffer_len = 1024;
  buffer_pos = 0;

  remote_addr.sin_family = AF_INET;
  remote_addr.sin_port = htons(port);

  fd = socket (AF_INET, SOCK_DGRAM, 0);

  if (fd < 0)
    {
      int err = SOCKETERR;
      octave_udp::close ();
      error ("udp: error opening socket : %d - %s\n", err, STRSOCKETERR);
      return -1;
    }

  memset (&local_addr, 0, sizeof (local_addr));

  local_addr.sin_addr.s_addr = htonl (INADDR_ANY);
  local_addr.sin_family = AF_INET;
  local_addr.sin_port = htons (localport);

  sockerr = bind (fd, (struct sockaddr*)&local_addr, sizeof (local_addr));
  if (sockerr < 0)
    {
      int err = SOCKETERR;
      octave_udp::close ();
      error ("udp: error on bind : %d - %s\n", err, STRSOCKETERR);
      return -1;
    }
  else if (localport == 0)
    {
      // if said port, 0, lookup actual port it used
      socklen_t sz = sizeof (local_addr);
      getsockname (fd, (struct sockaddr*)&local_addr, &sz);
    }

  return get_fd();
}

octave_udp::~octave_udp (void)
{
  close();
}

void
octave_udp::print (std::ostream& os, bool pr_as_read_syntax)
{
  print_raw (os, pr_as_read_syntax);
  newline (os);
}

void
octave_udp::print (std::ostream& os, bool pr_as_read_syntax) const
{
  print_raw (os, pr_as_read_syntax);
  newline (os);
}

void
octave_udp::print_raw (std::ostream& os, bool pr_as_read_syntax) const
{
  os << "  UDP Object " << get_name ();
  newline(os);
  os << "          type: " << get_type (); 
  newline(os);
  os << "        status: " << get_status ();
  newline(os);
  os << "    remoteport: " << get_remote_port ();
  newline(os);
  os << "    remotehost: " << get_remote_addr ();
  newline(os);
  os << "     localport: " << get_local_port ();
  newline (os);
}

int
octave_udp::get_bytesavailable () const
{
  IOCTL_TYPE available = 0;

  if (get_fd () < 0)
    {
      return 0;
    }
  if (buffer_pos > 0)
    return buffer_pos;

  ioctl (get_fd (), FIONREAD, &available);

  return available;
}

int
octave_udp::read (uint8_t *buf, unsigned int len, double readtimeout)
{
  struct sockaddr_in addr;
  socklen_t addrlen = sizeof (addr);
  struct timeval tv;

  fd_set readfds;

  if (get_fd () < 0)
    {
      error ("udp_read: Interface must be opened first...");
      return 0;
    }

  size_t bytes_read = 0;
  ssize_t read_retval = -1;

  // While not interrupted in blocking mode
  while (bytes_read < len)
    {
      OCTAVE_QUIT;

      // need get some data in the buffer
      if (buffer_pos == 0)
        {
          // need read some data first
          tv = to_timeval((readtimeout < 0 || readtimeout > 1000) ? 1000 : readtimeout);

          FD_ZERO (&readfds);
          FD_SET (get_fd (), &readfds);

          if (::select(get_fd ()+1, &readfds, NULL, NULL, &tv) < 0)
            {
                error("udp_read: Error while reading/select: %d - %s\n", SOCKETERR, STRSOCKETERR);
                break;
            }

          if (FD_ISSET (get_fd (), &readfds))
            {
              int available = get_bytesavailable();

              // alloc new buffer
              if (available > buffer_len)
                {
                  // get nearest 1k over if can
                  if (available + 1024 > 0)
                    {
                      available = (available + 1023);
                      available &= ~0x3ff;
                    }
                  delete [] input_buffer;
                  input_buffer = 0;
                  input_buffer = new uint8_t[available];
                  buffer_len = available;
                }

              addrlen = sizeof (addr);
              read_retval = ::recvfrom (get_fd (), reinterpret_cast<char *>(input_buffer), buffer_len,
                                        0, (struct sockaddr*)&addr, &addrlen);
            
              if (read_retval < 0)
                {
                    error ("udp_read: Error while reading: %d - %s\n", SOCKETERR, STRSOCKETERR);
                    break;
                } 
              else if (read_retval == 0)
                {
                    error ("udp_read: Connection lost: %d - %s\n", SOCKETERR, STRSOCKETERR);
                    break;
                }
              else
                {
                  //bytes_read += read_retval;
	          buffer_pos = read_retval;
                }
            }
          else 
            {
              // Timeout
              if (readtimeout >= 0)
                {
                  // real timeout
                  if (readtimeout <= 1000)
                    break;
                  // timed out 1 sec of an actual timeout
                  else
                    readtimeout -= 1000;
                }
            }
        }

      // buffered data can read ?
      if (buffer_pos > 0)
        {
          if (len - bytes_read < buffer_pos)
            {
              read_retval = len - bytes_read;
              memcpy(&buf[bytes_read], input_buffer, read_retval);
              memmove(&input_buffer[0], &input_buffer[read_retval], buffer_pos-read_retval);
              buffer_pos -= read_retval;
	    }
          else
            {
              read_retval = buffer_pos;
              memcpy(&buf[bytes_read], input_buffer, buffer_pos);
	      buffer_pos = 0;
            }

          bytes_read += read_retval;
        }
    }

  return bytes_read;
}

int
octave_udp::write (const std::string &str)
{
  return ::sendto (get_fd (), str.c_str(), str.length(), 0, 
                  (struct sockaddr *)&remote_addr, sizeof(remote_addr));
}

int
octave_udp::write (uint8_t *buf, unsigned int len)
{
  if (get_fd () < 0)
    {
      error("udp: Interface must be opened first...");
      return -1;
    }

  return ::sendto (get_fd(), reinterpret_cast<const char *>(buf), 
                   len, 0, (struct sockaddr *)&remote_addr, sizeof (remote_addr));
}

int
octave_udp::set_timeout (double newtimeout)
{
  if (get_fd () < 0)
    {
      error ("udp: Interface must be opened first...");
      return -1;
    }

  if (newtimeout < -1 )
    {
      error ("udp_timeout: timeout value must be -1 or positive");
      return -1;
    }

  timeout = newtimeout;

  return 1;
}

int
octave_udp::get_remote_port (void) const
{
  return ntohs (remote_addr.sin_port);
}

int
octave_udp::set_remote_port (int port)
{
  if (port < 0 )
    {
        error ("udp_remote_port: value must be positive");
        return -1;
    }

  remote_addr.sin_port = htons(port);

  return get_remote_port();
}

std::string
octave_udp::get_remote_addr (void) const
{
  return to_ip_str (&remote_addr);
}

std::string
octave_udp::set_remote_addr (const std::string &addr)
{
  if (addr.length() == 0 )
    {
      error ("udp_remote_addr: value must be non empty");
    }
  else if ( !lookup_addr(addr, &remote_addr))
    {
      error ("udp: error looking up remote host : %d - %s\n", SOCKETERR, STRSOCKETERR);
    }

  return to_ip_str (&remote_addr);
}

int
octave_udp::get_local_port (void) const
{
  return ntohs (local_addr.sin_port);
}

std::string
octave_udp::get_local_addr (void) const
{
  return  to_ip_str (&local_addr);
}


std::string
octave_udp::set_name (const std::string &n)
{
  if (n.length() == 0 )
    {
      error ("udp_name: value must be non empty");
    }
  else
    {
      name = n;
    }
 
  return name;
}

bool
octave_udp::is_open (void) const
{
  return fd >= 0;
}

std::string
octave_udp::get_status (void) const
{
  if (! is_open ()) 
    {
      return "closed";
    }
  else
    {
      return "open";
    }
}

int
octave_udp::close (void)
{
  int retval = -1;

  if (get_fd() > 0)
    {
#ifndef __WIN32__
      retval = ::close (get_fd ());
#else
      retval = ::closesocket (get_fd ());
#endif
      fd = -1;
    }

  if (buffer_len)
    {
      delete [] input_buffer;
      buffer_len = 0;
    }

  return retval;
}

int
octave_udp::flush (int mode)
{
  int retval = -1;

  if (get_fd() > 0)
    {
      uint8_t tmpbuffer[1024];
      if (mode == 0 || mode == 2)
        {
	  // we are sending data as we get it, so no outout
	  // buffers to flush
        }
      if (mode == 1 || mode == 2)
        {
          while (read (tmpbuffer, 1024, 0) > 0) {}
	  buffer_pos = 0;
        }
    }

  return retval;
}
#endif
