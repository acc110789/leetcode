AC_INIT([dpkg-testcase], [1.0], [xiang.zhai@i-soft.com.cn])
AM_INIT_AUTOMAKE([1.11 subdir-objects foreign])
AC_PROG_CC
AM_MAINTAINER_MODE
AC_CONFIG_MACRO_DIR([m4])
LT_INIT

CFLAGS='-Wall -std=gnu11'

LIBDPKG_REQUIRED=1.18.1
ZLIB_REQUIRED=1.2.8
LIBLZMA_REQUIRED=5.2.1

PKG_CHECK_MODULES(LIBDPKG, libdpkg >= LIBDPKG_REQUIRED)
AC_SUBST(LIBDPKG_CFLAGS)
AC_SUBST(LIBDPKG_LIBS)

PKG_CHECK_MODULES(ZLIB, zlib >= ZLIB_REQUIRED)
AC_SUBST(ZLIB_CFLAGS)
AC_SUBST(ZLIB_LIBS)

PKG_CHECK_MODULES(LIBLZMA, liblzma >= LIBLZMA_REQUIRED)
AC_SUBST(LIBLZMA_CFLAGS)
AC_SUBST(LIBLZMA_LIBS)

AC_ARG_ENABLE(debug,                                                                
              [AS_HELP_STRING([--enable-debug=@<:@no/yes@:>@],              
                              [turn on debugging [default=no]])],,
              [enable_debug=yes])

if test "x$enable_debug" = "xyes"; then                                             
  test "$cflags_set" = set || CFLAGS="$CFLAGS -g -DDEBUG" 
fi

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
])
AC_OUTPUT
