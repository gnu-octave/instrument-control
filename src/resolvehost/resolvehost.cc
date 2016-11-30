// Copyright (C) 2016   John Donoghue   <john.donoghue@ieee.org>
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

#ifndef __WIN32__
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#else
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

#ifndef __WIN32__
#define SOCKETERR errno
#define STRSOCKETERR strerror(errno)
#else
#define SOCKETERR WSAGetLastError()
#define STRSOCKETERR ""
#endif

static bool type_loaded = false;

#endif

DEFUN_DLD (resolvehost, args, nargout,
        "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{name} = } resolvehost (@var{host})\n \
@deftypefnx {Loadable Function} {[@var{name}, @var{address}] = } resolvehost (@var{host})\n \
@deftypefnx {Loadable Function} {@var{out} = } resolvehost (@var{host}, @var{returntype})\n \
\n\
Resolve a network host name or address to network name and address\n \
\n\
@var{host} - Host name or IP address string to resolve.@* \
@var{name} - Resolved IP host name.@* \
@var{address} - Resolved IP host address.@* \
@var{returntype} - 'name' to get host name, 'address' to get IP address.\n \
\n \
Examples:\n \
\n \
@example\n \
%% get resolved ip name and address pf www.gnu.org\n \
[name, address] = resolvehost ('www.gnu.org');\n \
\n \
%% get ip address of www.gnu.org\n \
ipaddress = resolvehost ('www.gnu.org', 'address');\n \
\n \
@end example\n \
\n \
@seealso{tcp, udp}\n \
\n\
@end deftypefn")
{
#ifndef BUILD_TCP
    error("resolvehost: Your system doesn't support the TCP/UDP interface");
    return octave_value();
#else
    octave_value_list return_value;

    if (!type_loaded)
    {
#ifdef __WIN32__
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD( 2, 2 );
    err = WSAStartup ( wVersionRequested, &wsaData );
    if ( err != 0 )
    {
      error( "resolvehost: could not initialize winsock library" );
      return return_value;
    }
#endif
 
        type_loaded = true;
    }

    // Nothing to do
    if (args.length () != 1 && args.length () != 2)
    {
        print_usage ();
        return return_value;
    }

    // expects host string
    if (! args(0).is_string ())
    {
        print_usage ();
        return return_value;
    }

    std::string host = args(0).string_value ();

    // optional return type
    std::string return_type = "both";

    if (args.length () == 2)
    {
        if(! args(1).is_string ())
        {
            print_usage ();
            return return_value;
        }
        return_type = args(1).string_value ();
        std::transform (return_type.begin(), return_type.end(), 
            return_type.begin(), ::tolower);

        if (return_type != "name" && return_type != "address")
        {
            print_usage ();
            return return_value;
        }
    }

    // create addr from ip/looked up ip of value
    sockaddr_in in;
    memset (&in,0,sizeof(in));
    in.sin_family = AF_INET;

    in.sin_addr.s_addr = inet_addr (host.c_str ());

    if (in.sin_addr.s_addr == INADDR_NONE)
    {
      struct hostent * hostinfo = gethostbyname (host.c_str());
      if (hostinfo)
        memcpy (&in.sin_addr, hostinfo->h_addr_list[0], hostinfo->h_length);
    }
 
    if (in.sin_addr.s_addr == INADDR_NONE)
    {
      error( "resolvehost: could not lookup IP address" );
      return return_value;
    }

    // we want to look up the name (ie: not only address)
    if (return_type != "address")
    {
        char name[1025];
        if( getnameinfo ((struct sockaddr *)&in, sizeof(in),
            name, sizeof(name), NULL, 0, 0) != 0)
        {
            error("resolvehost: error looking up host name : %d - %s\n", 
                SOCKETERR, STRSOCKETERR);
        
            return return_value;
        }
        return_value(0) = name;
    }

    // we want the ip address (both or address)
    if (return_type != "name")
    {
        std::stringstream n;
        u_long addr = ntohl (in.sin_addr.s_addr);
        int b[4];
        b[0] = (addr>>24)&0xff;
        b[1] = (addr>>16)&0xff;
        b[2] = (addr>>8)&0xff;
        b[3] = (addr>>0)&0xff;
        n << b[0] << "." << b[1] << "." << b[2] << "." << b[3];
  
        if (return_type == "both")
            return_value(1) = n.str ();
        else
            return_value(0) = n.str ();
    }

    return return_value;
#endif
}

