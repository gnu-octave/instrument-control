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

#ifndef SERIALPORT_CLASS_WIN32_H
#define SERIALPORT_CLASS_WIN32_H

#ifndef  WIN32_LEAN_AND_MEAN
# define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <string>

class octave_serialport : public octave_serialport_common
{
public:
  octave_serialport(void);
  ~octave_serialport(void);

  int write(const std::string& /* buffer */);
  int write(uint8_t* /* buffer */, unsigned int /* buffer size */);

  int read(uint8_t* /* buffer */, unsigned int /* buffer size */);

  void open(const std::string& /* path */);
  void close(void);

  int flush(unsigned short /* stream select */);

  int sendbreak(unsigned short /* breaktime */);

  int set_timeout(double /* timeout */);
  double get_timeout(void) const;

  int set_baudrate(unsigned int /* baudrate */);
  int get_baudrate() const;

  int set_databits(unsigned short /* bytesize */);
  int get_databits(void) const;

  int set_parity(const std::string& /* parity */);
  std::string get_parity(void) const;

  int set_flowcontrol(const std::string& /* flow */);
  std::string get_flowcontrol() const;

  int set_stopbits(unsigned short /* stop bits */);
  int get_stopbits(void) const;

  bool get_control_line(const std::string &);
  void set_control_line(const std::string&, bool);

  int get_numbytesavailable(void) const;
private:
  HANDLE fd;
  DWORD status;
  DCB config;
  COMMTIMEOUTS timeouts;

  volatile bool blocking_read;
  double timeout;

  void get_control_line_status(void);

  bool fd_is_valid(void) const;

  DECLARE_OV_TYPEID_FUNCTIONS_AND_DATA
};

#endif
