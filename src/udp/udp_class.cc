// Copyright (C) 2016   John Donoghue   <john.donoghue@ieee.org>
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
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#else
#include <winsock2.h>
#endif

#ifndef __WIN32__
#define SOCKETERR errno
#define STRSOCKETERR strerror(errno)
#else
#define SOCKETERR WSAGetLastError()
#define STRSOCKETERR ""
#define socklen_t int
#endif

using std::string;

static std::string to_ip_str (const sockaddr_in *in)
{
  std::stringstream n;
  u_long addr = ntohl (in->sin_addr.s_addr);
  int b[4];
  b[0] = (addr>>24)&0xff;
  b[1] = (addr>>16)&0xff;
  b[2] = (addr>>8)&0xff;
  b[3] = (addr>>0)&0xff;
  n << b[0] << "." << b[1] << "." << b[2] << "." << b[3];
  return n.str ();
}

static bool lookup_addr(const std::string &ip, sockaddr_in *in)
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

#include "udp_class.h"

volatile bool read_interrupt = false;

DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_udp, "octave_udp", "octave_udp");

octave_udp::octave_udp()
{
    this->fd = -1;
}

int octave_udp::open(string address, int port, int localport)
{
    int sockerr;

    this->name = "UDP-" + address;
#ifdef __WIN32__
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD( 2, 2 );
    err = WSAStartup( wVersionRequested, &wsaData );
    if ( err != 0 )
    {
      error( "could not initialize winsock library" );
      return -1;
    }
#endif
    memset(&remote_addr,0,sizeof(remote_addr));

    if( !lookup_addr(address, &remote_addr))
    {
        error("udp: error looking up remote host : %d - %s\n", SOCKETERR, STRSOCKETERR);
        octave_udp::close();
        return -1;
    }
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(port);


    this->fd = socket(AF_INET, SOCK_DGRAM,0);
    if (this->fd < 0)
    {
        error("udp: error opening socket : %d - %s\n", SOCKETERR, STRSOCKETERR);
        octave_udp::close();
        return -1;
    }

    memset(&local_addr,0,sizeof(local_addr));
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(localport);

    sockerr = bind(this->fd, (struct sockaddr*)&local_addr, sizeof(local_addr));
    if (sockerr < 0)
    {
        error("udp: error on bind : %d - %s\n", SOCKETERR, STRSOCKETERR);
        octave_udp::close();
        return -1;
    }
    else if (localport == 0)
    {
      // if said port, 0, lookup actual port it used
      socklen_t sz = sizeof(local_addr);
      getsockname(this->fd, (struct sockaddr*)&local_addr, &sz);
    }

    return this->get_fd();
}

octave_udp::~octave_udp()
{
    this->close();
}

void octave_udp::print (std::ostream& os, bool pr_as_read_syntax)
{
    print_raw(os, pr_as_read_syntax);
    newline(os);
}

void octave_udp::print (std::ostream& os, bool pr_as_read_syntax ) const
{
    print_raw(os, pr_as_read_syntax);
    newline(os);
}

void octave_udp::print_raw (std::ostream& os, bool pr_as_read_syntax) const
{
    os << "  UDP Object " << this->get_name();
    newline(os);
    os << "          type: " << this->get_type(); 
    newline(os);
    os << "        status: " << this->get_status();
    newline(os);
    os << "    remoteport: " << this->get_remote_port ();
    newline(os);
    os << "    remotehost: " << this->get_remote_addr ();
    newline(os);
    os << "     localport: " << this->get_local_port();
    newline(os);
}

int octave_udp::read(uint8_t *buf, unsigned int len, int timeout)
{
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    struct timeval tv;
    struct timeval *ptv;

    fd_set readfds;

    if (this->get_fd() < 0)
    {
        error("udp_read: Interface must be opened first...");
        return 0;
    }

    size_t bytes_read = 0;
    ssize_t read_retval = -1;

    // While not interrupted in blocking mode
    while (!read_interrupt)
    {
        ptv = &tv;
        tv.tv_sec = 0;
        tv.tv_usec = timeout * 1000;

        // blocking read
        if (timeout < 0)
        {
            ptv = NULL;
        }

        FD_ZERO(&readfds);
        FD_SET(this->get_fd(),&readfds);
        if (::select(this->get_fd()+1,&readfds,NULL,NULL,ptv) < 0)
        {
            error("udp_read: Error while reading/select: %d - %s\n", SOCKETERR, STRSOCKETERR);
            break;
        }

        if (FD_ISSET(this->get_fd(),&readfds))
        {
            addrlen = sizeof(addr);
            read_retval = ::recvfrom(get_fd(),reinterpret_cast<char *>((buf + bytes_read)),len - bytes_read,0, (struct sockaddr*)&addr, &addrlen);
            if (read_retval < 0)
            {
                error("udp_read: Error while reading: %d - %s\n", SOCKETERR, STRSOCKETERR);
                break;
            } else if (read_retval == 0)
            {
                error("udp_read: Connection lost: %d - %s\n", SOCKETERR, STRSOCKETERR);
                break;
            }
        } else {
            // Timeout
            break;
        }

        bytes_read += read_retval;

        // Required number of bytes read
        if (bytes_read >= len)
            break;

    }

    return bytes_read;

}

int octave_udp::write(string str)
{
    return ::sendto(get_fd(), str.c_str(), str.length(), 0, (struct sockaddr *)&remote_addr, sizeof(remote_addr));
}

int octave_udp::write(uint8_t *buf, unsigned int len)
{
    if (this->get_fd() < 0)
    {
        error("udp: Interface must be opened first...");
        return -1;
    }

    return ::sendto(get_fd(), reinterpret_cast<const char *>(buf), 
        len, 0, (struct sockaddr *)&remote_addr, sizeof(remote_addr));
}

int octave_udp::set_timeout(int timeout)
{
    if (this->get_fd() < 0)
    {
        error("udp: Interface must be opened first...");
        return -1;
    }

    if (timeout < -1 )
    {
        error("udp_timeout: timeout value must be -1 or positive");
        return -1;
    }

    this->timeout = timeout;

    return 1;
}

int octave_udp::get_timeout()
{
    return this->timeout;
}

int octave_udp::get_fd()
{
    return this->fd;
}

int octave_udp::get_remote_port () const
{
    return ntohs (remote_addr.sin_port);
}

int octave_udp::set_remote_port (int port)
{
    if (port < 0 )
    {
        error("udp_remote_port: value must be positive");
        return -1;
    }
    remote_addr.sin_port = htons(port);

    return get_remote_port();
}

std::string octave_udp::get_remote_addr () const
{
    return to_ip_str (&remote_addr);
}

std::string octave_udp::set_remote_addr (const std::string &addr)
{
    if (addr.length() == 0 )
    {
        error("udp_remote_addr: value must be non empty");
    }
    else if( !lookup_addr(addr, &remote_addr))
    {
        error("udp: error looking up remote host : %d - %s\n", SOCKETERR, STRSOCKETERR);
    }
    return to_ip_str (&remote_addr);
}

int octave_udp::get_local_port () const
{
    return ntohs (local_addr.sin_port);
}
std::string octave_udp::get_name () const
{
    return this->name;
}
std::string octave_udp::set_name (const std::string &n)
{
    if (n.length() == 0 )
    {
        error("udp_name: value must be non empty");
    }
    else
    {
      this->name = n;
    }
 
    return this->name;
}

bool octave_udp::is_open () const
{
    return this->fd >= 0;
}
std::string octave_udp::get_status () const
{
    if (!this->is_open ()) return "closed";
    return "open";
}
int octave_udp::close()
{
    int retval = -1;

    if (this->get_fd() > 0)
    {
#ifndef __WIN32__
        retval = ::close(this->get_fd());
#else
        retval = ::closesocket(this->get_fd());
#endif
        this->fd = -1;
    }

    return retval;
}
#endif
