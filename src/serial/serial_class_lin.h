// Copyright (C) 2018   John Donoghue   <john.donoghue@ieee.org>
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

#ifndef SERIAL_CLASS_LIN_H
#define SERIAL_CLASS_LIN_H

#include <string>
#include <termios.h>

class octave_serial : public octave_serial_common
{
public:
  octave_serial(void);
  ~octave_serial(void);

  int write(const std::string& /* buffer */);
  int write(uint8_t* /* buffer */, unsigned int /* buffer size */);

  int read(uint8_t* /* buffer */, unsigned int /* buffer size */);

  void open(const std::string& /* path */);
  void close(void);

  int flush(unsigned short /* stream select */);

  int set_timeout(short /* timeout */);
  int get_timeout(void) const;

  int set_baudrate(unsigned int /* baudrate */);
  int get_baudrate(void) const;

  int set_bytesize(unsigned short /* bytesize */);
  int get_bytesize(void) const;

  int set_parity(const std::string& /* parity */);
  std::string get_parity() const;

  int set_stopbits(unsigned short /* stop bits */);
  int get_stopbits(void) const;

  bool get_control_line(const std::string &);
  void set_control_line(const std::string &, bool);

private:
  int fd;
  int status;
  struct termios config;
  short timeout;
  volatile bool blocking_read;

  void get_control_line_status(void);

  bool fd_is_valid(void) const;

  DECLARE_OV_TYPEID_FUNCTIONS_AND_DATA
};

#endif
