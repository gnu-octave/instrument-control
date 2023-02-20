// Copyright (C) 2022 John Donoghue <john.donoghue@ieee.org>
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

#ifdef BUILD_TCP
#include <iostream>
#include <string>
#include <algorithm>

#ifndef __WIN32__
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <termios.h>
#include <sys/ioctl.h>
#else
#include <winsock2.h>
#endif

#ifndef __WIN32__
#define SOCKETERR errno
#define STRSOCKETERR strerror(errno)
#define IOCTL_TYPE int
#else
#define SOCKETERR WSAGetLastError()
#define STRSOCKETERR ""
#define IOCTL_TYPE u_long
#define ioctl ioctlsocket
#define socklen_t int
#endif

#include "tcpserver_class.h"
#include <octave/Matrix.h>

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

static std::string
num2str(int num)
{
  std::stringstream n;
  n << num;
  return n.str ();
}


DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_tcpserver, "octave_tcpserver", "octave_tcpserver");

octave_tcpserver::octave_tcpserver (void)
: fieldnames(14), fd (-1), clientfd(-1), timeout(-1), name("")
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
  interminator = octave_value("lf");
  outterminator = octave_value("lf");

  fieldnames[0] = "Type";
  fieldnames[1] = "Name";
  fieldnames[2] = "ServerPort";
  fieldnames[3] = "ServerAddress";
  fieldnames[4] = "ClientPort";
  fieldnames[5] = "ClientAddress";
  fieldnames[6] = "Connected";
  fieldnames[7] = "Status";
  fieldnames[8] = "Timeout";
  fieldnames[9] = "NumBytesAvailable";
  fieldnames[10] = "NumBytesWritten";
  fieldnames[11] = "ByteOrder";
  fieldnames[12] = "UserData";
  fieldnames[13] = "Terminator";
}

bool
octave_tcpserver::has_property(const std::string &name) const
{
  for (octave_idx_type i=0; i<fieldnames.numel(); i++)
    {
      if (fieldnames[i] == name) return true;
    }
  return false;
}

octave_value_list
octave_tcpserver::subsref (const std::string& type, const std::list<octave_value_list>& idx, int nargout)
{
  octave_value_list retval;
  int skip = 1;

  switch (type[0])
    {
    default:
      error ("octave_tcpserver object cannot be indexed with %c", type[0]);
      return retval;
    case '.':
      {
        std::string property = (idx.front ()) (0).string_value ();
        if (!has_property(property))
          {
            error ("Unknown property '%s'", property.c_str());
            return retval;
          }
        // check connections
        if (property == "Connected")
          check_for_connections();

        octave_value_list ovl;
        // inc ref count as assign this to octave_value
        OV_COUNT++; 
        ovl (0) = octave_value (this);
        ovl (1) = (idx.front ()) (0);
        retval = OCTAVE__FEVAL (std::string ("__tcpserver_properties__"), ovl, 1);
      }
      break;
    }

  if (idx.size () > 1 && type.length () > 1)
    retval = retval (0).next_subsref (nargout, type, idx, skip);

  return retval;
}

octave_value
octave_tcpserver::subsasgn (const std::string& type, const std::list<octave_value_list>& idx, const octave_value& rhs)
{
  octave_value retval;

  switch (type[0])
    {
    default:
      error ("octave_tcpserver object cannot be indexed with %c", type[0]);
      break;
    case '.':
      if (type.length () == 1)
        {
          std::string property = (idx.front ()) (0).string_value ();
          if (!has_property(property))
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
          OCTAVE__FEVAL (std::string ("__tcpserver_properties__"), ovl, 0);
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
          error ("octave_tcpserver invalid index");
        }

    }
  return retval;
}

int
octave_tcpserver::open (const std::string &address, int port)
{
  int sockerr;

  name = "TCPServer-" + num2str(port);

#ifdef __WIN32__
  WORD wVersionRequested;
  WSADATA wsaData;
  int err;

  wVersionRequested = MAKEWORD( 2, 2 );
  err = WSAStartup (wVersionRequested, &wsaData);
  if ( err != 0 )
    {
      error( "could not initialize winsock library" );
      return -1;
    }
#endif

  // 1. bind to address/port
  // 2. start listending
  // 3. in read ? or somewhere else? need check for incomming connections ? 
  memset (&local_addr, 0, sizeof (local_addr));
  if (address == "0.0.0.0" || address == "::" or address == "")
    local_addr.sin_addr.s_addr = htonl (INADDR_ANY);
  else
    {
      if (! lookup_addr(address, &local_addr))
        {
          error ("tcpserver: error looking up remote host : %d - %s\n", SOCKETERR, STRSOCKETERR);
          octave_tcpserver::close ();
          return -1;
        }
    }
  local_addr.sin_family = AF_INET;
  local_addr.sin_port = htons (port);


  memset (&remote_addr, 0, sizeof (remote_addr));
  //remote_addr.sin_family = AF_INET;
  //remote_addr.sin_port = htons (port);

  fd = socket (AF_INET, SOCK_STREAM,0);
  if (fd < 0)
    {
      error ("tcpserver: error opening socket : %d - %s\n", SOCKETERR, STRSOCKETERR);
      octave_tcpserver::close ();
      return -1;
    }

  sockerr = bind (fd, (struct sockaddr*)&local_addr, sizeof (local_addr));
  if (sockerr < 0)
    {
      error ("tcpserver: error on bind : %d - %s\n", SOCKETERR, STRSOCKETERR);
      octave_tcpserver::close ();
      return -1;
    }  
 
  // get local socket info
  //memset (&local_addr, 0, sizeof (local_addr));
  socklen_t sz = sizeof (local_addr);
  getsockname (fd, (struct sockaddr*)&local_addr, &sz);

  sockerr = listen (fd, 1);
  if (sockerr < 0)
    {
      error ("tcpserver: error on listen : %d - %s\n", SOCKETERR, STRSOCKETERR);
      octave_tcpserver::close ();
      return -1;
    }
  return get_fd();
}

octave_tcpserver::~octave_tcpserver (void)
{
  octave_tcpserver::close ();
}

void
octave_tcpserver::print (std::ostream& os, bool pr_as_read_syntax)
{
  print_raw (os, pr_as_read_syntax);
  newline (os);
}

void
octave_tcpserver::print (std::ostream& os, bool pr_as_read_syntax ) const
{
  print_raw (os, pr_as_read_syntax);
  newline (os);
}

void
octave_tcpserver::print_raw (std::ostream& os, bool pr_as_read_syntax) const
{
  os << "  TCP Server Object " << get_name ();
  newline(os);
  os << "ServerAddress: " << get_address ();
  newline(os);
  os << "   ServerPort: " << get_port ();
  newline(os);
  os << "    Connected: " << get_connected ();
  newline(os);
}

int
octave_tcpserver::read (uint8_t *buf, unsigned int len, double readtimeout)
{
  struct timeval tv;

  fd_set readfds;

  if (get_fd () < 0)
    {
        error ("tcpserver_read: Interface must be opened first...");
        return 0;
    }

  if (this->clientfd < 0)
    {
        error ("tcpserver_read: Not connected");
        return 0;
    }

  size_t bytes_read = 0;
  ssize_t read_retval = -1;

  // While not interrupted in blocking mode
  while (bytes_read < len)
    {

      OCTAVE_QUIT;

      tv = to_timeval((readtimeout < 0 || readtimeout > 1000) ? 1000 : (int)readtimeout);

      FD_ZERO (&readfds);
      FD_SET (this->clientfd, &readfds);

      if (::select (this->clientfd+1, &readfds, NULL, NULL, &tv) < 0)
        {
          error ("tcpserver_read: Error while reading/select: %d - %s\n", SOCKETERR, STRSOCKETERR);
          break;
        }

      if (FD_ISSET (this->clientfd, &readfds))
        {
          read_retval = ::recv(this->clientfd, reinterpret_cast<char *>((buf + bytes_read)), len - bytes_read, 0);
          if (read_retval < 0)
            {
              error ("tcpserver_read: Error while reading: %d - %s\n", SOCKETERR, STRSOCKETERR);
              break;
            } 
          else if (read_retval == 0)
            {
              //error ("tcpserver_read: Connection lost: %d - %s\n", SOCKETERR, STRSOCKETERR);
	      this->clientfd = -1;
	      // TODO: call back for disconnected
              break;
            }
          else
            {
              bytes_read += read_retval;
            }
        } 
      else 
        {
          // time out
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

  return bytes_read;
}

int
octave_tcpserver::write (const std::string &str)
{
  if (get_fd () < 0)
    {
      error ("tcpserver: Interface must be opened first...");
      return -1;
    }

  if (this->clientfd < 0)
    {
        error ("tcpserver_read: Not connected");
        return 0;
    }

  int wrote = ::send (this->clientfd, str.c_str (), str.length (), 0);
  if(wrote > 0)
    byteswritten += wrote;
  return wrote;
}

int
octave_tcpserver::write (uint8_t *buf, unsigned int len)
{
  if (get_fd () < 0)
    {
      error ("tcpserver: Interface must be opened first...");
      return -1;
    }

  if (this->clientfd < 0)
    {
        error ("tcpserver_read: Not connected");
        return 0;
    }

  int wrote = ::send (this->clientfd, reinterpret_cast<const char *>(buf), len, 0);
  if(wrote > 0)
    byteswritten += wrote;
  return wrote;
}

int
octave_tcpserver::check_for_connections ()
{
  if (get_fd () < 0)
    {
      return -1;
    }

  fd_set ready;
  struct timeval tv;

  FD_ZERO (&ready);
  FD_SET (get_fd (), &ready);
  tv.tv_sec = 0;
  tv.tv_usec = 0;

  if (::select (get_fd ()+1, &ready, NULL, NULL, &tv) < 0)
    {
      error ("tcpserver_read: Error while reading/select: %d - %s\n", SOCKETERR, STRSOCKETERR);
      return -1;
    }

  if (FD_ISSET (get_fd (), &ready))
    {
      socklen_t sz = sizeof (remote_addr);
      int client = accept(get_fd(), (sockaddr*)&remote_addr, &sz);

      if(client < 0)
        {
          // shouldnt happen ?
        }
      else if(this->clientfd >= 0)
        {
          // already have a connection so just close this one
#ifndef __WIN32__
          ::close (client);
#else
          ::closesocket (client);
#endif
	  return 0;
        }
      else
        {
          this->clientfd = client;

          //warning ("Connected new socket %d", client);
	  //TODO: connected call back ?
	  
          return 1;
        }
    }

  return 0;
}

int
octave_tcpserver::set_timeout (double newtimeout)
{
  if (get_fd () < 0)
    {
      error ("tcpserver: Interface must be opened first...");
      return -1;
    }

  if (newtimeout < -1 )
    {
      error ("tcpserver_timeout: timeout value must be -1 or positive");
      return -1;
    }

  timeout = newtimeout;

  return 1;
}

int
octave_tcpserver::close (void)
{
  int retval = -1;

  if(this->clientfd)
    {
#ifndef __WIN32__
      retval = ::close (this->clientfd);
#else
      retval = ::closesocket (this->clientfd);
#endif
      clientfd = -1;
    }

  if (get_fd() > 0)
    {
#ifndef __WIN32__
      retval = ::close (get_fd ());
#else
      retval = ::closesocket (get_fd ());
#endif
      fd = -1;
    }

  return retval;
}

int
octave_tcpserver::get_numbytesavailable () const
{
  IOCTL_TYPE available = 0;

  if (this->clientfd < 0)
    {
      return 0;
    }
  ioctl (this->clientfd, FIONREAD, &available);

  return available;
}

int
octave_tcpserver::get_port (void) const
{
  return ntohs (local_addr.sin_port);
}

std::string
octave_tcpserver::get_address (void) const
{
  return to_ip_str (&local_addr);
}

int
octave_tcpserver::get_client_port (void) const
{
  return ntohs (remote_addr.sin_port);
}

std::string
octave_tcpserver::get_client_address (void) const
{
  return to_ip_str (&remote_addr);
}

bool
octave_tcpserver::get_connected (void) const
{
  return clientfd != -1;
}

std::string
octave_tcpserver::set_name (const std::string &n)
{
  if (n.length() == 0 )
    {
      error ("tcpserver_name: value must be non empty");
    }
  else
    {
      name = n;
    }
 
  return name;
}

bool
octave_tcpserver::is_open (void) const
{
  return fd > 0;
}

std::string
octave_tcpserver::get_status (void) const
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
octave_tcpserver::flush (int mode)
{
  int retval = -1;

  if (this->clientfd > 0)
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
        }
    }

  return retval;
}


int
octave_tcpserver::set_byteorder(const std::string& neworder)
{
  std::string order = neworder;
  std::transform (order.begin (), order.end (), order.begin (), ::tolower);
  if (order == "big" || order == "big-endian")
    byteOrder = "big-endian";
  else if (order == "little" || order == "little-endian")
    byteOrder = "little-endian";
 else
    error ("octave_tcpserver invalid byteorder");

 return 1;
}

int
octave_tcpserver::set_input_terminator(const octave_value& t)
{
  if(t.is_string())
    {
      std::string term = t.string_value();
      std::transform (term.begin (), term.end (), term.begin (), ::tolower);
      if (term != "lf" && term != "cr" && term != "cr/lf")
        error ("octave_tcpserver invalid input terminator");
      else
        interminator = term;
    }
  else if(t.is_scalar_type())
    {
      int x = t.int_value();
      if(x < 0 || x > 255)
        {
          error ("octave_tcpserver invalid input terminator");
        }
      else
        {
          interminator = octave_value(x);
        }
    }
  else
    error ("octave_tcpserver invalid input terminator");

 return 1;
}

int
octave_tcpserver::set_output_terminator(const octave_value& t)
{
  if(t.is_string())
  {
    std::string term = t.string_value();
    std::transform (term.begin (), term.end (), term.begin (), ::tolower);
    if (term != "lf" && term != "cr" && term != "cr/lf")
      error ("octave_tcpserver invalid output terminator");
    else
      outterminator = term;
    }
  else if(t.is_scalar_type())
    {
      int x = t.int_value();
      if(x < 0 || x > 255)
        {
          error ("octave_tcpserver invalid output terminator");
        }
      else
        {
          outterminator = octave_value(x);
        }
    }
  else
    error ("octave_tcpserver invalid output terminator");

 return 1;
}

#endif
