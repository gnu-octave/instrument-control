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
#  include <ws2tcpip.h>
#  define IOCTL_TYPE u_long
#  define ioctl ioctlsocket
#endif

#include "udpport_class.h"
#include <octave/Matrix.h>

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

int to_ip_port (const sockaddr_in *in, std::string &ip, int &port)
{
  port = ntohs (in->sin_port);
  ip = to_ip_str(in);
  return 1;
}

DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_udpport, "octave_udpport", "octave_udpport");

octave_udpport::octave_udpport (void)
: buffer_len(0), fd(-1), timeout(-1), name(""), fieldnames(17)
{
  static bool type_registered = false;

  if (! type_registered)
    {
      type_registered = true;
      register_type ();
    }
  userData = Matrix ();
  byteswritten = 0;
  byteOrder = "little-endian";
  enableportsharing = 0;
  enablemulticastloopback = 0;
  enablebroadcast = 0;
  interminator = octave_value("lf");
  outterminator = octave_value("lf");

  fieldnames[0] = "Type";
  fieldnames[1] = "Name";
  fieldnames[2] = "LocalPort";
  fieldnames[3] = "LocalHost";
  fieldnames[4] = "Status";
  fieldnames[5] = "Timeout";
  fieldnames[6] = "NumBytesAvailable";
  fieldnames[7] = "NumBytesWritten";
  fieldnames[8] = "ByteOrder";
  fieldnames[9] = "UserData";
  fieldnames[10] = "MulticastGroup";
  fieldnames[11] = "EnableMulticast";
  fieldnames[12] = "EnableMulticastLoopback";
  fieldnames[13] = "EnableBroadcast";
  fieldnames[14] = "EnablePortSharing";
  fieldnames[15] = "IPAddressVersion";
  fieldnames[16] = "Terminator";
}

bool octave_udpport::has_property(const std::string &name) const
{
  for (octave_idx_type i=0; i<fieldnames.numel(); i++)
    {
      if (fieldnames[i] == name) return true;
    }
  return false;
}

octave_value_list
octave_udpport::subsref (const std::string& type, const std::list<octave_value_list>& idx, int nargout)
{
  octave_value_list retval;
  int skip = 1;

  switch (type[0])
    {
    default:
      error ("octave_udpport object cannot be indexed with %c", type[0]);
      return retval;
    case '.':
      {
	std::string property = (idx.front ()) (0).string_value ();
        if (!has_property(property))
	  {
            error ("Unknown property '%s'", property.c_str());
            return retval;
          }
        else
	  {
            octave_value_list ovl;
            // inc ref count as assign this to octave_value
            OV_COUNT++; 
            ovl (0) = octave_value (this);
            ovl (1) = (idx.front ()) (0);
            retval = OCTAVE__FEVAL (std::string ("__udpport_properties__"), ovl, 1);
	  }
      }
      break;
    }

  if (idx.size () > 1 && type.length () > 1)
    retval = retval (0).next_subsref (nargout, type, idx, skip);

  return retval;
}

octave_value
octave_udpport::subsasgn (const std::string& type, const std::list<octave_value_list>& idx, const octave_value& rhs)
{
  octave_value retval;

  switch (type[0])
    {
    default:
      error ("octave_udpport object cannot be indexed with %c", type[0]);
      break;
    case '.':
      if (type.length () == 1)
        {
          std::string property = (idx.front ()) (0).string_value ();
          if (! has_property(property))
	    {
              error ("Unknown property '%s'", property.c_str());
              return retval;
            }

          octave_value_list ovl;
          // inc ref count as assign this to octave_value
          OV_COUNT++; 
          ovl (0) = octave_value (this);
          ovl (1) = (idx.front ()) (0);
          ovl (2) = rhs;
          OCTAVE__FEVAL (std::string ("__udpport_properties__"), ovl, 0);
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
          error ("octave_udpport invalid index");
        }

    }
  return retval;
}

int
octave_udpport::open (const std::string &address, int port, int portshare)
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
  // default size for now
  input_buffer = new uint8_t[1024];
  buffer_len = 1024;
  buffer_pos = 0;
  memset (&read_addr, 0, sizeof (read_addr));

  memset (&remote_addr, 0, sizeof (remote_addr));
  remote_addr.sin_family = AF_INET;
  remote_addr.sin_port = 0;
  remote_addr.sin_addr.s_addr = htonl (INADDR_ANY);

  fd = socket (AF_INET, SOCK_DGRAM, 0);

  if (fd < 0)
    {
      error ("udpport: error opening socket : %d - %s\n", SOCKETERR, STRSOCKETERR);
      octave_udpport::close ();
      return -1;
    }

  // port sharing
  enableportsharing = portshare;
  if(portshare)
    {
#ifdef SO_REUSEPORT
      setsockopt(SOL_SOCKET, SO_REUSEPORT, (void*)&portshare, sizeof(portshare));
#else
      setsockopt(SOL_SOCKET, SO_REUSEADDR, (void*)&portshare, sizeof(portshare));
#endif
    }

  memset (&local_addr, 0, sizeof (local_addr));
  if (address == "0.0.0.0")
    local_addr.sin_addr.s_addr = htonl (INADDR_ANY);
  else
    {
      lookup_addr(address, &local_addr);
    }
  local_addr.sin_family = AF_INET;
  local_addr.sin_port = htons (port);

  sockerr = bind (fd, (struct sockaddr*)&local_addr, sizeof (local_addr));
  if (sockerr < 0)
    {
      error ("udpport: error on bind : %d - %s\n", SOCKETERR, STRSOCKETERR);
      octave_udpport::close ();
      return -1;
    }  
  else if (port == 0)
    {
      // if said port, 0, lookup actual port it used
      socklen_t sz = sizeof (local_addr);
      getsockname (fd, (struct sockaddr*)&local_addr, &sz);
    }

  return get_fd();
}

octave_udpport::~octave_udpport (void)
{
  close();
}

void
octave_udpport::print (std::ostream& os, bool pr_as_read_syntax)
{
  print_raw (os, pr_as_read_syntax);
  newline (os);
}

void
octave_udpport::print (std::ostream& os, bool pr_as_read_syntax) const
{
  print_raw (os, pr_as_read_syntax);
  newline (os);
}

void
octave_udpport::print_raw (std::ostream& os, bool pr_as_read_syntax) const
{
  os << "  UDPPort Object " << get_name ();
  newline(os);
  os << "          Type: " << get_type (); 
  newline(os);
  os << "        Status: " << get_status ();
  newline(os);
  os << "    LocalHost: " << get_local_addr ();
  newline(os);
  os << "     LocalPort: " << get_local_port ();
  newline (os);
}

int
octave_udpport::get_bytesavailable () const
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
octave_udpport::getsockopt (int level, int opt, void *buf, socklen_t *len)
{
#ifndef __WIN32__
  return ::getsockopt(get_fd(), level, opt, buf, len);
#else
  return ::getsockopt(get_fd(), level, opt, (char *)buf, len);
#endif
}

int
octave_udpport::setsockopt (int level, int opt, const void *buf, socklen_t len)
{
#ifndef __WIN32__
  return ::setsockopt(get_fd(), level, opt, buf, len);
#else
  return ::setsockopt(get_fd(), level, opt, (const char *)buf, len);
#endif
}

int
octave_udpport::read (uint8_t *buf, unsigned int len, double readtimeout, sockaddr_in *rdinfo)
{
  //struct sockaddr_in addr;
  socklen_t addrlen = sizeof (read_addr);
  struct timeval tv;

  fd_set readfds;

  if (get_fd () < 0)
    {
      error ("udpport_read: Interface must be opened first...");
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
                error("udpport_read: Error while reading/select: %d - %s\n", SOCKETERR, STRSOCKETERR);
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

              addrlen = sizeof (read_addr);
              read_retval = ::recvfrom (get_fd (), reinterpret_cast<char *>(input_buffer), buffer_len,
                                        0, (struct sockaddr*)&read_addr, &addrlen);
            
              if (read_retval < 0)
                {
                    error ("udpport_read: Error while reading: %d - %s\n", SOCKETERR, STRSOCKETERR);
                    break;
                } 
              else if (read_retval == 0)
                {
                    error ("udpport_read: Connection lost: %d - %s\n", SOCKETERR, STRSOCKETERR);
                    break;
                }
              else
                {
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

      if (buffer_pos > 0)
        {
          if (len - bytes_read < buffer_pos)
	    {
              read_retval = len - bytes_read;
              memcpy(&buf[bytes_read], input_buffer, read_retval);
              memcpy(&input_buffer[0], &input_buffer[read_retval], buffer_pos-read_retval);
              buffer_pos -= read_retval;

            }
          else
            {
              read_retval = buffer_pos;
              memcpy(&buf[bytes_read], input_buffer, buffer_pos);
              buffer_pos = 0;
            }

          if (rdinfo)
            *rdinfo = read_addr;
          bytes_read += read_retval;
        }

    }

  return bytes_read;
}

int
octave_udpport::write (const std::string &str, const std::string &destip, int destport)
{
  if (get_fd () < 0)
    {
      error("udpport: Interface must be opened first...");
      return -1;
    }

  if (destip.length() > 0)
    {
      sockaddr_in in;

      memset (&in, 0, sizeof (in));

      in.sin_family = AF_INET;

      lookup_addr (destip, &in);

      in.sin_port = htons(destport);

      remote_addr = in;
    }
  else
    {
      if (remote_addr.sin_port == 0)
        {
          error("udpport: No destination address/port previously set");
          return -1;
        }
    }
  int wrote = ::sendto (get_fd (), str.c_str(), str.length(), 0, 
                  (struct sockaddr *)&remote_addr, sizeof(remote_addr));
  if(wrote > 0)
    byteswritten += wrote;

  return wrote;
}

int
octave_udpport::write (uint8_t *buf, unsigned int len, const std::string &destip, int destport)
{
  if (get_fd () < 0)
    {
      error("udpport: Interface must be opened first...");
      return -1;
    }

  if (destip.length() > 0)
    {
      sockaddr_in in;

      memset (&in, 0, sizeof (in));

      in.sin_family = AF_INET;

      lookup_addr (destip, &in);

      in.sin_port = htons(destport);

      remote_addr = in;
    }
  else
    {
      if (remote_addr.sin_port == 0)
        {
          error("udpport: No destination address/port previously set");
          return -1;
        }
    }

  int wrote = ::sendto (get_fd(), reinterpret_cast<const char *>(buf), 
                   len, 0, (struct sockaddr *)&remote_addr, sizeof (remote_addr));
  if(wrote > 0)
    byteswritten += wrote;

  return wrote;
}

int
octave_udpport::set_timeout (double newtimeout)
{
  if (get_fd () < 0)
    {
      error ("udpport: Interface must be opened first...");
      return -1;
    }

  if (newtimeout < -1 )
    {
      error ("udpport_timeout: timeout value must be -1 or positive");
      return -1;
    }

  timeout = newtimeout;

  return 1;
}

int
octave_udpport::get_remote_port (void) const
{
  return ntohs (remote_addr.sin_port);
}

int
octave_udpport::set_remote_port (int port)
{
  if (port < 0 )
    {
        error ("udpport_remote_port: value must be positive");
        return -1;
    }

  remote_addr.sin_port = htons(port);

  return get_remote_port();
}

std::string
octave_udpport::get_remote_addr (void) const
{
  return to_ip_str (&remote_addr);
}

std::string
octave_udpport::set_remote_addr (const std::string &addr)
{
  if (addr.length() == 0 )
    {
      error ("udpport_remote_addr: value must be non empty");
    }
  else if ( !lookup_addr(addr, &remote_addr))
    {
      error ("udpport: error looking up remote host : %d - %s\n", SOCKETERR, STRSOCKETERR);
    }

  return to_ip_str (&remote_addr);
}

int
octave_udpport::get_local_port (void) const
{
  return ntohs (local_addr.sin_port);
}

std::string
octave_udpport::get_local_addr (void) const
{
  return  to_ip_str (&local_addr);
}


std::string
octave_udpport::set_name (const std::string &n)
{
  if (n.length() == 0 )
    {
      error ("udpport_name: value must be non empty");
    }
  else
    {
      name = n;
    }
 
  return name;
}

bool
octave_udpport::is_open (void) const
{
  return fd >= 0;
}

std::string
octave_udpport::get_status (void) const
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
octave_udpport::close (void)
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
octave_udpport::flush (int mode)
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

int
octave_udpport::set_enablebroadcast (int enable)
{

  if (get_fd () < 0)
    {
      error ("udpport: Interface must be opened first...");
      return -1;
    }

  enablebroadcast = enable;

  return setsockopt(SOL_SOCKET, SO_BROADCAST, (void*)&enable, sizeof(enable));
}

int
octave_udpport::set_multicastloopback (int enable)
{

  if (get_fd () < 0)
    {
      error ("udpport: Interface must be opened first...");
      return -1;
    }

  enablemulticastloopback = enable;

  return setsockopt(IPPROTO_IP, IP_MULTICAST_LOOP, (void*)&enable, sizeof(enable));
}

std::string
octave_udpport::get_multicastgroup () const
{
  if (multicastaddr.size() > 0)
    {
      sockaddr_in in = multicastaddr[0];
      return  to_ip_str (&in);
    }
  else
    return "";
}

int
octave_udpport::set_multicastgroup (const std::string &addr)
{
  int retval = -1;

  if (get_fd() > 0)
    {
      if (addr == "off")
        {
          sockaddr_in in;

          for (int i=0; i<(int)multicastaddr.size (); i++)
            {
              struct ip_mreq multicastRequest;  /* Multicast address join structure */

              in = multicastaddr[i];
              memcpy(&multicastRequest.imr_multiaddr,
                &in.sin_addr,
                sizeof(multicastRequest.imr_multiaddr));

              multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY);

              setsockopt(IPPROTO_IP, IP_DROP_MEMBERSHIP, (void*) &multicastRequest, sizeof(multicastRequest));
       
            }

          multicastaddr.erase(multicastaddr.begin(), multicastaddr.end());
        }
      else
        {
          sockaddr_in in;
          if (! lookup_addr (addr, &in))
           {
              error ("Could not resolve address %s", addr.c_str());
           }
         else
           {
              struct ip_mreq multicastRequest;  /* Multicast address join structure */

             memcpy(&multicastRequest.imr_multiaddr,
               &in.sin_addr,
               sizeof(multicastRequest.imr_multiaddr));

             multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY);

             /* Join the multicast address */
             if ( setsockopt(IPPROTO_IP, IP_ADD_MEMBERSHIP, (void*) &multicastRequest, sizeof(multicastRequest)) != 0 )
               {
                 error ("Failed to add address");
               }
             else
               {
                 // store address
                 multicastaddr.push_back(in);

                 retval = 1;
               }
           }
        }
    }

  return retval;
}

int
octave_udpport::set_byteorder(const std::string& neworder)
{
  std::string order = neworder;
  std::transform (order.begin (), order.end (), order.begin (), ::tolower);
  if (order == "big" || order == "big-endian")
    byteOrder = "big-endian";
  else if (order == "little" || order == "little-endian")
    byteOrder = "little-endian";
 else
    error ("octave_udpport invalid byteorder");

 return 1;
}

int
octave_udpport::set_input_terminator(const octave_value& t)
{
  if(t.is_string())
  {
    std::string term = t.string_value();
    std::transform (term.begin (), term.end (), term.begin (), ::tolower);
    if (term != "lf" && term != "cr" && term != "cr/lf")
      error ("octave_udpport invalid input terminator");
    else
      interminator = term;
    }
  else if(t.is_scalar_type())
    {
      int x = t.int_value();
      if(x < 0 || x > 255)
        {
          error ("octave_udpport invalid input terminator");
        }
      else
        {
          interminator = octave_value(x);
        }
    }
  else
    error ("octave_udpport invalid input terminator");

  return 1;
}

int
octave_udpport::set_output_terminator(const octave_value& t)
{
  if(t.is_string())
  {
    std::string term = t.string_value();
    std::transform (term.begin (), term.end (), term.begin (), ::tolower);
    if (term != "lf" && term != "cr" && term != "cr/lf")
      error ("octave_udpport invalid output terminator");
    else
      outterminator = term;
    }
  else if(t.is_scalar_type())
    {
      int x = t.int_value();
      if(x < 0 || x > 255)
        {
          error ("octave_udpport invalid output terminator");
        }
      else
        {
          outterminator = octave_value(x);
        }
    }
  else
    error ("octave_udpport invalid output terminator");

 return 1;
}

#endif
