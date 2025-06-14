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

#ifndef VXI11_CLASS_H
#define VXI11_CLASS_H

#include <octave/oct.h>

#include <rpc/rpc.h>
#include "vxi11.h"

#include <string>

using std::string;

#ifdef HAVE_CONFIG_H
#  include "../config.h"
#endif

class octave_vxi11 : public OCTAVE_BASE_CLASS
{
public:
  octave_vxi11 (void);
  ~octave_vxi11 (void);

    int open (string, string);
    int close (void);

    // Simple vxi11 commands
    int write (const char*, int);
    int read (char*, unsigned int);

    // Overloaded base functions
    string vxi11_value () const
    {
        return (string)this->ip;
    }

    virtual double scalar_value (bool frc_str_conv = false) const
    {
        return (double)0;
    }

    void print (std::ostream& os, bool pr_as_read_syntax = false);
    void print (std::ostream& os, bool pr_as_read_syntax = false) const;
    void print_raw (std::ostream& os, bool pr_as_read_syntax) const;

    // Properties
    bool is_constant (void) const { return true;}
    bool is_defined (void) const { return true;}
    bool print_as_scalar (void) const { return true;}

private:
    CLIENT *client;
    Create_LinkResp *link;
    std::string ip;
    std::string inst;
    std::string device;

    int openvxi (const char *, CLIENT **, Create_LinkResp **, const char *);
    int closevxi (const char *, CLIENT *, Create_LinkResp *);

    DECLARE_OV_TYPEID_FUNCTIONS_AND_DATA
};


#endif
