#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
#
### Copyright (C) 2020-2023 John Donoghue <john.donoghue@ieee.org>
###
### This program is free software; you can redistribute it and/or
### modify it under the terms of the GNU General Public License as
### published by the Free Software Foundation; either version 3 of the
### License, or (at your option) any later version.
###
### This program is distributed in the hope that it will be useful,
### but WITHOUT ANY WARRANTY; without even the implied warranty of
### MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
### General Public License for more details.
###
### You should have received a copy of the GNU General Public License
### along with this program; if not, see
### <http://www.gnu.org/licenses/>.

AC_PREREQ([2.69])
AC_INIT([octave instrument control package],[0.9.2])
AC_CONFIG_HEADERS([config.h])

# Avoid warnings for redefining AH-generated preprocessor symbols of
# Octave.
AH_TOP([#include "undef-ah-octave.h"])

AC_CONFIG_MACRO_DIRS([m4])

AC_CANONICAL_HOST
AC_CANONICAL_TARGET

# Checks for programs.
AC_PROG_CXX
AC_PROG_GREP
AC_PROG_SED

AC_LANG(C++)

# Define macros needed
#AC_DEFINE(__STDC_CONSTANT_MACROS, [], [workaround for C++ programs to use C99 macros])

AC_CHECK_PROG([MKOCTFILE], [mkoctfile], [mkoctfile], [none])
if [test "$MKOCTFILE" = "none"]; then
  AC_MSG_ERROR([mkoctfile required to install $PACKAGE_NAME])
fi

AC_CHECK_PROG(OCTAVE_CONFIG,octave-config,octave-config)
test -z "$OCTAVE_CONFIG" && OCTAVE_CONFIG=$MKOCTFILE

# try get around possible spaces in the path
if test "X${IGNORE_MINGW_PATH_MODIFICATION}" == "X"; then
case $host_os in
  mingw*)
    # try demangle spaces in escaped input strings
    MKOCTFILE=`echo $MKOCTFILE | $SED "s,\\\\\ ,?,g"`
    OCTAVE_CONFIG=`echo $OCTAVE_CONFIG | $SED "s,\\\\\ ,?,g"`
    ;;
  *)
    ;;
esac
fi

## Simple symbol alternatives of different Octave versions.
save_altsyms_CXX="$CXX"
save_altsyms_CXXFLAGS="$CXXFLAGS"
save_altsyms_LDFLAGS="$LDFLAGS"
save_altsyms_LIBS="$LIBS"
OCTINCLUDEDIR="${OCTINCLUDEDIR:-`$MKOCTFILE -p OCTINCLUDEDIR`}/.."
OCTLIBDIR=${OCTLIBDIR:-`$MKOCTFILE -p OCTLIBDIR`}

if test "X${IGNORE_MINGW_PATH_MODIFICATION}" == "X"; then
  MSYSTEM="${MSYSTEM}"
else
  MSYSTEM="none"
fi

case X$MSYSTEM in
  XMINGW64*)
    OCTAVE_HOME=`${MKOCTFILE} -p OCTAVE_HOME | $SED 's,\\\\,/,g'`
    # change \ to / and replace octave home part with mingw part
    OCTINCLUDEDIR=`echo $OCTINCLUDEDIR | $SED -e 's,\\\\,/,g' -e "s,${OCTAVE_HOME},/mingw64,g"`
    OCTLIBDIR=`echo $OCTLIBDIR | $SED -e 's,\\\\,/,g' -e "s,${OCTAVE_HOME},/mingw64,g"`
    ;;
  XMINGW32*)
    OCTAVE_HOME=`${MKOCTFILE} -p OCTAVE_HOME | $SED 's,\\\\,/,g'`
    # change \ to / and replace octave home part with mingw part
    OCTINCLUDEDIR=`echo $OCTINCLUDEDIR | $SED -e 's,\\\\,/,g' -e "s,${OCTAVE_HOME},/mingw32,g"`
    OCTLIBDIR=`echo $OCTLIBDIR | $SED -e 's,\\\\,/,g -e "s,${OCTAVE_HOME},/mingw32,g"'`
    ;;
  *)
    ;;
esac

CXX=`${MKOCTFILE} -p CXX`
CXXFLAGS="-I$OCTINCLUDEDIR $CXXFLAGS"
LDFLAGS="-L$OCTLIBDIR $LDFLAGS"
LIBS="-loctinterp $LIBS"

# includes
AC_CHECK_HEADERS([octave/interpreter.h],
  [],
  [],
  [#include <octave/oct.h>]
)

AC_CHECK_HEADERS([octave/lo-sysdep.h],
  [],
  [],
  [#include <octave/oct.h>]
)

OF_OCTAVE_LIST_ALT_SYMS([
[dnl
  [feval],
  [octave::feval],
  [[octave::feval ("date");]],
  [OCTAVE__FEVAL],
  [[#include <octave/parse.h>]],
  [[#include <octave/parse.h>]]
],

[dnl
  [is_float_type],
  [isfloat],
  [[octave_value ().isfloat ();]],
  [OV_ISFLOAT],
  [],
  []
],

[dnl
  [is_integer_type],
  [isinteger],
  [[octave_value ().isinteger ();]],
  [OV_ISINTEGER],
  [],
  []
],

[dnl
  [is_bool_type],
  [islogical],
  [[octave_value ().islogical ();]],
  [OV_ISLOGICAL],
  [],
  []
],

[dnl
  [unwind_protect],
  [octave::unwind_protect],
  [[octave::unwind_protect frame;]],
  [OCTAVE__UNWIND_PROTECT],
  [[#include <octave/unwind-prot.h>]
   [#include <octave/octave.h>]
  ],
  [[#include <octave/unwind-prot.h>]
   [#include <octave/octave.h>]
  ]
],

[dnl
  [octave_value_typeinfo::register_binary_op],
  [octave::type_info::register_binary_op],
  [
   [octave::type_info& ti = octave::interpreter::the_interpreter ()->get_type_info ();]
   [ti.register_binary_op(octave_value::op_eq, 1,1,0);]
  ],
  [OCTAVE__REGISTER_BINARY_OP],
  [[#include <octave/octave.h>]],
  [
   [#include <octave/octave.h>]
   [#include <octave/interpreter.h>]
  ]
],

[dnl
  [octave_base_value],
  [octave_base_dld_value],
  [[octave_base_dld_value tmp;]],
  [OCTAVE_BASE_CLASS],
  [],
  []
]

],[oct-alt-includes.h])

if test $ac_cv_octsym_OCTAVE__REGISTER_BINARY_OP = "octave::type_info::register_binary_op"; then
  AC_DEFINE([OCTAVE__NEW_REGISTER_OP], [], [Use new register_binary_op]) 
fi

OF_OCTAVE_CHECK_SYM(
  [for octave::sys::u8_to_wstring],
  [
    std::wstring s = octave::sys::u8_to_wstring("test");
  ],
  [HAVE_OCTAVE_U8_TO_WSTRING],
  [
    #include <octave/lo-sysdep.h>
  ]
)

AC_MSG_CHECKING([for octave_base_value count field])
octave_count_field=count
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
   #include <octave/oct.h>
   #ifdef HAVE_CONFIG_H
   #  include "config.h"
   #endif
   class test_base_class : public octave_base_value
   {
   public:
     test_base_class() {}
     ~test_base_class() {}
     void test() { m_count ++; }
     bool is_object (void) const { return true; }
   };
  ]], [
    test_base_class t;  t.is_object();
  ])],
 [octave_count_field=m_count],
 [octave_count_field=count]
)
AC_MSG_RESULT([$octave_count_field])
AC_DEFINE_UNQUOTED([OV_COUNT],$octave_count_field,[octave_base_value ref count field])

CXX=$save_altsyms_CXX
CXXFLAGS=$save_altsyms_CXXFLAGS
LDFLAGS=$save_altsyms_LDFLAGS
LIBS=$save_altsyms_LIBS

build_parallel=no
build_serial=no
build_i2c=no
build_spi=no
build_usbtmc=no
build_tcp=no
build_udp=no
build_gpib=no
build_vxi11=no
build_visa=no
build_resolvehost=no
build_modbus=no

# Check for Windows
AC_MSG_CHECKING([for windows])
have_windows=no
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
   #include <windows.h>
   #ifndef __WIN32__
     #error "Not windows!"
   #endif
  ]], [])],
 [AC_MSG_RESULT([yes])
  have_windows=yes],
 [AC_MSG_RESULT([no])])

# if windows, we can build some of the packages just by having
# windows.h
if test $have_windows = yes; then
  build_serial=yes
  AC_SUBST([BUILD_FOR_WINDOWS], [1], [build using native windows functions])
  # prevent some warnings by defining this ...
  AC_DEFINE([_NO_SYS_GUID_OPERATOR_EQ_], [1], [Dont define guid == ops])
fi

# check for i2c
# if linux/i2c-dev.h exists we are probably under linux, so build usbtmc as well
AC_CHECK_HEADERS([linux/i2c-dev.h],[build_i2c=yes build_usbtmc=yes])
AC_CHECK_HEADERS([dev/iicbus/iic.h],[build_i2c=yes])

# check for spi
AC_CHECK_HEADERS([linux/spi/spidev.h],[build_spi=yes])

# check for serial
AC_CHECK_HEADERS([termios.h],[build_serial=yes])

# check for parallel
AC_CHECK_HEADERS([linux/parport.h linux/ppdev.h],[build_parallel=yes])
AC_CHECK_HEADERS([dev/ppbus/ppi.h dev/ppbus/ppbconf.h],[build_parallel=yes])

# build tcp, available for most platforms
AC_CHECK_HEADERS([sys/socket.h],[build_tcp=yes])

# Check for winsock2 and ws2_32
have_winsock2=no
AC_CHECK_HEADERS([winsock2.h],
  [AC_SEARCH_LIBS([_head_libws2_32_a], [ws2_32],
                  [have_winsock2=yes] , [] )
   AC_SEARCH_LIBS([_head_lib32_libws2_32_a], [ws2_32],
                  [have_winsock2=yes] , [] )
   AC_SEARCH_LIBS([_head_lib64_libws2_32_a], [ws2_32],
                  [have_winsock2=yes] , [] )
  ], [])

if test $have_winsock2 = yes; then
  AC_SUBST(TCPLIBS, ["-lws2_32"])
  build_tcp=yes
  build_resolvehost=yes
fi

# if can build tcp, can build udp
if test $build_tcp = yes; then
  build_udp=yes
fi

# checks for resolve host
if test $build_tcp = yes; then
  if test $build_resolvehost = no; then
    AC_SEARCH_LIBS(getnameinfo, [inet6 socket], [build_resolvehost=yes])
    if test "x$ac_cv_search_getnameinfo" != "xno"; then
      test "x$ac_cv_search_getnameinfo" = "xnone required" || AC_SUBST(TCPLIBS, [$ac_cv_search_getnameinfo])
    fi
  fi
fi

# Checks for GPIB
AC_CHECK_HEADERS([gpib/ib.h],
  [AC_SEARCH_LIBS([ibrd], [gpib], [build_gpib=yes], [])] , [] )

if test "x$ac_cv_search_ibrd" != "xno"; then
  test "x$ac_cv_search_ibrd" = "xnone required" || AC_SUBST(GPIBLIBS, [$ac_cv_search_ibrd])
fi


# Checks for RPC/VXI11
AC_ARG_WITH([librpc],
  [AS_HELP_STRING([--with-librpc=tirpc|sunrpc|auto|none],[Choose use/selection of librpc used])],
  [with_libtirpc="$with_librpc"], [with_librpc="auto"])

if test "x${with_librpc}" = "xyes"; then
  with_librpc="auto"
fi
if test "x${with_librpc}" = "xno"; then
  with_librpc="none"
fi

if test "x${with_librpc}" = "xauto" || test "x${with_librpc}" = "xtirpc"; then
  PKG_CHECK_MODULES([TIRPC], [libtirpc],
    [with_librpc="yes"; build_vxi11=yes; RPCINCLUDE="$RPCINCLUDE $TIRPC_CFLAGS"; RPCLIBS="$RPCLIBS $TIRPC_LIBS";],
    [RPCINCLUDE="$RPCINCLUDE"])
fi

if test "x${with_librpc}" = "xauto" || test "x${with_librpc}" = "xsunrpc"; then
  AC_SEARCH_LIBS([clnt_create], [tirpc],
    [with_librpc="yes"],
    [])
  if test "x$ac_cv_search_clnt_create" != "xnone required"; then
    RPCLIBS="$RPCLIBS $ac_cv_search_clnt_create"
  fi
  AC_CHECK_HEADERS([rpc/rpc.h],[RPCINCLUDE="$RPC_CFLAGS"],[with_librpc="no"; build_vxi11=no])
fi
if test "x${with_librpc}" = "xauto"; then
  with_librpc="none"
fi

AC_SUBST(RPCINCLUDE)
AC_SUBST(RPCLIBS)

# with_librpc should now be yes, if found
# none if was never wanted or not auto detected

if test "x${with_librpc}" != "xyes" && test "x${with_librpc}" != "xnone"; then
  AC_MSG_NOTICE([Did not find valid rpc libraries - disabling vxi11 interface])
fi

if test "x${with_librpc}" = "xyes"; then
  build_vxi11=yes
  
  # we support const input into clnt_create ?
  AC_MSG_CHECKING([const input allowed into clnt_perror])
  const_clnt_perror=no
  AC_LANG_PUSH([C++])
  save_LIBS=$LIBS
  save_CPPFLAGS=$CPPFLAGS
  LIBS=$RPCLIBS
  CPPFLAGS=$RPCINCLUDE
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
    #include <rpc/rpc.h>
   ]], [[
    const char * msg = "const message";
    CLIENT *clnt = 0;
    clnt_perror(clnt, msg);
   ]])],
   [AC_MSG_RESULT([yes])
    const_clnt_perror=yes],
   [AC_MSG_RESULT([no])]
  )
  LIBS=$save_LIBS=
  CPPFLAGS=$save_CPPFLAGS
  AC_LANG_POP([C++])

  if test $const_clnt_perror = yes; then
    AC_DEFINE([CONST_CLNT_SUPPORT], [1], [clnt allows const inputs])
  fi
fi

# we have rpcgen ?
AC_CHECK_PROGS([RPCGEN], [rpcgen rpcgen-mt], [none])

if test "xRPCGEN" = "xnone"; then
  AC_MSG_WARN([No rpcgen found - if rpc sources are modified, the build will fail])
else
  AC_MSG_CHECKING([whether ${RPCGEN} accepts -M option])
  rm -f rpcgen_test.*
cat > rpcgen_test.x <<END
program STRLEN {
  version STRLENVERS {
    int strlen(string) = 1;
  } = 1;
} = 11;
END
  RPCGENOPTS=""
  ${RPCGEN} -M rpcgen_test.x > /dev/null 2>&1
  if test -f rpcgen_test.h; then
    _rpcgen_result=yes
    RPCGENOPTS="-M"
  else
    _rpcgen_result=no
  fi
  AC_MSG_RESULT([$_rpcgen_result])
  AC_SUBST([RPCGENOPTS], [$RPCGENOPTS])
  rm -f rpcgen_test.*
  rm -f rpcgen_test_*
fi

# Checks for openvisa
AC_CHECK_HEADERS([visa/visa.h],
  [AC_SEARCH_LIBS([viOpenDefaultRM], [openvisa], [build_visa=yes], [])] , [] )

if test "x$ac_cv_search_viOpenDefaultRM" != "xno"; then
  test "x$ac_cv_search_viOpenDefaultRM" = "xnone required" || AC_SUBST(VISALIBS, [$ac_cv_search_viOpenDefaultRM])
fi

# Checks for libmodbus
build_modbus=no
PKG_CHECK_MODULES([LIBMODBUS], [libmodbus],
    [AC_CHECK_HEADERS([modbus/modbus.h],[build_modbus=yes], [])],
    [build_modbus=no])

if test $build_modbus = yes; then
  AC_SUBST(MODBUSLIBS, [$LIBMODBUS_LIBS])
  AC_SUBST(MODBUSINCLUDES, [$LIBMODBUS_CFLAGS])

AC_MSG_CHECKING([modbus_set_response_timeout(modbus_t*,uint32,uint32)])
AC_COMPILE_IFELSE(
  [AC_LANG_PROGRAM([[#include <modbus/modbus.h>]],
   [[
     modbus_t *m=0;
     modbus_set_response_timeout(m,0,0);
   ]])],
 [AC_MSG_RESULT([yes])
  AC_DEFINE([HAVE_MODBUS_SET_RESPONSE_TIMEOUT2], [], [Defined if have modbus_set_response_timeout(modbus_t*,uint32,uint32)])],
 [AC_MSG_RESULT([no])])
fi

if test $build_parallel = yes; then
  AC_DEFINE([BUILD_PARALLEL], [], [build PARALLEL interface functions])
fi

if test $build_serial = yes; then
  AC_DEFINE([BUILD_SERIAL], [], [build SERIAL interface functions])
fi

if test $build_i2c = yes; then
  AC_DEFINE([BUILD_I2C], [], [build I2C interface functions])
fi

if test $build_spi = yes; then
  AC_DEFINE([BUILD_SPI], [], [build SPI interface functions])
fi

if test $build_usbtmc = yes; then
  AC_DEFINE([BUILD_USBTMC], [], [build USBTMC interface functions])
fi

if test $build_tcp = yes; then
  AC_DEFINE([BUILD_TCP], [], [build TCP interface functions])
fi

if test $build_udp = yes; then
  AC_DEFINE([BUILD_UDP], [], [build UDP interface functions])
fi

if test $build_gpib = yes; then
  AC_DEFINE([BUILD_GPIB], [], [build GPIB interface functions]) 
fi

if test $build_vxi11 = yes; then
  AC_DEFINE([BUILD_VXI11], [], [build VXI11 interface functions])
  AC_SUBST([BUILD_VXI11], [1])
fi

if test $build_visa = yes; then
  AC_DEFINE([BUILD_VISA], [], [build VISA interface functions])
fi

if test $build_resolvehost = yes; then
  AC_DEFINE([BUILD_RESOLVEHOST], [], [build resolvehost function])
fi

if test $build_modbus = yes; then
  AC_DEFINE([BUILD_MODBUS], [], [build MODBUS interface functions]) 
fi

# all done

AC_CONFIG_FILES([common.mk Makefile gpib/Makefile
		 tcp/Makefile tcpclient/Makefile
		 tcpserver/Makefile
		 udp/Makefile udpport/Makefile
		 vxi11/Makefile usbtmc/Makefile spi/Makefile
		 serial/Makefile parallel/Makefile i2c/Makefile
		 resolvehost/Makefile hwinfo/Makefile
		 serialport/Makefile modbus/Makefile])
AC_OUTPUT

AC_MSG_NOTICE([

$PACKAGE_NAME is now configured with

   BUILD SERIAL:      $build_serial
   BUILD PARALLEL:    $build_parallel
   BUILD I2C:         $build_i2c
   BUILD SPI:         $build_spi
   BUILD TCP:         $build_tcp
   BUILD UDP:         $build_udp
   BUILD USBTMC:      $build_usbtmc
   BUILD GPIB:        $build_gpib
   BUILD VXI11:       $build_vxi11
   BUILD RESOLVEHOST: $build_resolvehost
   BUILD MODBUS:      $build_modbus

   GPIB LIBS:         $GPIBLIBS
   VXI11 LIBS:        $RPCLIBS
   VXI11 INCLUDE:     $RPCINCLUDE
   VISA LIBS:         $VISALIBS
   TCP LIBS:          $TCPLIBS
   MODBUS LIBS:       $MODBUSLIBS
   MODBUS INCLUDE:    $MODBUSINCLUDE
])
