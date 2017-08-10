#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])
AC_INIT([octave instrument control package], [0.0.0+])
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_MACRO_DIRS([m4])

# Checks for programs.
AC_PROG_CXX
AC_LANG(C++)

# Define macros needed
#AC_DEFINE(__STDC_CONSTANT_MACROS, [], [workaround for C++ programs to use C99 macros])

AC_CHECK_PROG([MKOCTFILE], [mkoctfile], [mkoctfile], [none])
if [test "$MKOCTFILE" = "none"]; then
  AC_MSG_ERROR([mkoctfile required to install $PACKAGE_NAME])
fi

AC_PROG_GREP

## Simple symbol alternatives of different Octave versions.
save_altsyms_CXX="$CXX"
save_altsyms_CXXFLAGS="$CXXFLAGS"
save_altsyms_LDFLAGS="$LDFLAGS"
save_altsyms_LIBS="$LIBS"
OCTINCLUDEDIR=${OCTINCLUDEDIR:-`$MKOCTFILE -p INCFLAGS`}
OCTLIBDIR=${OCTLIBDIR:-`$MKOCTFILE -p OCTLIBDIR`}
CXX=`${MKOCTFILE} -p CXX`
CXXFLAGS="$OCTINCLUDEDIR $CXXFLAGS"
LDFLAGS="-L$OCTLIBDIR $LDFLAGS"
LIBS="-loctinterp $LIBS"

OF_OCTAVE_LIST_ALT_SYMS([
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
  [octave_install_signal_handlers],
  [octave::install_signal_handlers],
  [[octave::install_signal_handlers();]],
  [OCTAVE__INSTALL_SIGNAL_HANDLERS],
  [[#include <sighandlers.h>],
   [#include <octave.h>]
  ],
  [[#include <sighandlers.h>]
   [#include <octave.h>]
  ]
],

[dnl
  [octave_set_signal_handler],
  [octave::set_signal_handler],
  [[octave::set_signal_handler(SIGINT, 0);]],
  [OCTAVE__SET_SIGNAL_HANDLER],
  [[#include <sighandlers.h>]],
  [[#include <sighandlers.h>]]
]

],[oct-alt-includes.h])

CC=$save_alsyms_CXX
CXXFLAGS=$save_altsyms_CXXFLAGS
LDFLAGS=$save_altsyms_LDFLAGS
LIBS=$save_altsyms_LIBS

build_parallel=no
build_serial=no
build_i2c=no
build_usbtmc=no
build_tcp=no
build_udp=no
build_gpib=no
build_vxi11=no
build_visa=no
build_resolvehost=no

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
fi

# check for i2c
# if linux/i2c-dev.h exists we are probably under linux, so build usbtmc as well
AC_CHECK_HEADERS([linux/i2c-dev.h],[build_i2c=yes build_usbtmc=yes])
AC_CHECK_HEADERS([dev/iicbus/iic.h],[build_i2c=yes])

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
fi

# if can build tcp, can build udp
if test $build_tcp = yes; then
  build_udp=yes
fi

# checks for resolve host
if test $build_tcp = yes; then
  AC_SEARCH_LIBS(getnameinfo, [ws2_32 inet6 socket], [build_resolvehost=yes])
  if test "x$ac_cv_search_getnameinfo" != "xno"; then
    test "x$ac_cv_search_getnameinfo" = "xnone required" || AC_SUBST(TCPLIBS, [$ac_cv_search_getnameinfo])
  fi
fi

# Checks for GPIB
AC_CHECK_HEADERS([gpib/ib.h],
  [AC_SEARCH_LIBS([ibrd], [gpib], [build_gpib=yes], [])] , [] )

if test "x$ac_cv_search_ibrd" != "xno"; then
  test "x$ac_cv_search_ibrd" = "xnone required" || AC_SUBST(GPIBLIBS, [$ac_cv_search_ibrd])
fi


# Checks for RPC/VXI11
AC_ARG_WITH([tirpcinclude],
  [AC_HELP_STRING([--with-tirpcinclude=DIR],
    [use TI-RPC headers in DIR])],
    [tirpc_header_dir=$withval],
    [tirpc_header_dir=/usr/include/tirpc])

AC_CHECK_PROG([HAVE_RPCGEN], [rpcgen], [yes], [no])
if test "x$HAVE_RPCGEN" = "xyes"; then
  AC_SEARCH_LIBS([clnt_create], [tirpc], [build_vxi11=yes])
  AC_CHECK_HEADERS([rpc/rpc.h],[],
    [AC_CHECK_HEADERS([${tirpc_header_dir}/netconfig.h],
      [AC_SUBST([RPCINCLUDE], ["-I${tirpc_header_dir}"])],[build_vxi11=no])])

  if test "x$ac_cv_search_clnt_create" != "xno"; then
    test "x$ac_cv_search_clnt_create" = "xnone required" || AC_SUBST(RPCLIBS, [$ac_cv_search_clnt_create])
  fi

fi


# Checks for openvisa
AC_CHECK_HEADERS([visa/visa.h],
  [AC_SEARCH_LIBS([viOpenDefaultRM], [openvisa], [build_vxi11=yes], [])] , [] )

if test "x$ac_cv_search_viOpenDefaultRM" != "xno"; then
  test "x$ac_cv_search_viOpenDefaultRM" = "xnone required" || AC_SUBST(VISALIBS, [$ac_cv_search_viOpenDefaultRM])
fi


#

if test $build_parallel = yes; then
  AC_DEFINE([BUILD_PARALLEL], [], [build PARALLEL interface functions])
fi

if test $build_serial = yes; then
  AC_DEFINE([BUILD_SERIAL], [], [build SERIAL interface functions])
fi

if test $build_i2c = yes; then
  AC_DEFINE([BUILD_I2C], [], [build I2C interface functions])
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
  AC_SUBST([BUILD_VXI11], [1], [build VXI11 interface functions])
fi

if test $build_visa = yes; then
  AC_DEFINE([BUILD_VISA], [], [build VISA interface functions])
fi

if test $build_resolvehost = yes; then
  AC_DEFINE([BUILD_RESOLVEHOST], [], [build resolvehost function])
fi


# all done

AC_CONFIG_FILES([Makefile gpib/Makefile tcp/Makefile udp/Makefile vxi11/Makefile usbtmc/Makefile serial/Makefile parallel/Makefile i2c/Makefile resolvehost/Makefile])
AC_OUTPUT

AC_MSG_NOTICE([

$PACKAGE_NAME is now configured with

   BUILD SERIAL:      $build_serial
   BUILD PARALLEL:    $build_parallel
   BUILD I2C:         $build_i2c
   BUILD TCP:         $build_tcp
   BUILD UDP:         $build_udp
   BUILD USBTMC:      $build_usbtmc
   BUILD GPIB:        $build_gpib
   BUILD VXI11:       $build_vxi11
   BUILD RESOLVEHOST: $build_resolvehost

   GPIB LIBS:         $GPIBLIBS
   VXI11 LIBS:        $RPCLIBS
   VXI11 INCLUDE:     $RPCINCLUDE
   VISA LIBS:         $VISALIBS
   TCP LIBS:          $TCPLIBS

])
