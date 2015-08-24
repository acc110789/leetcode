AC_INIT([rpm-testcase], [1.0], [xiang.zhai@i-soft.com.cn])
AM_INIT_AUTOMAKE([1.11 subdir-objects foreign])
AC_PROG_CC
AM_MAINTAINER_MODE
AC_CONFIG_MACRO_DIR([m4])
LT_INIT

CFLAGS='-Wall -std=gnu11'

RPM_REQUIRED=4.12.90
GLIB2_REQUIRED=2.45.4
POPT_REQUIRED=1.16

PKG_CHECK_MODULES(RPM, rpm >= RPM_REQUIRED)
AC_SUBST(RPM_CFLAGS)
AC_SUBST(RPM_LIBS)

PKG_CHECK_MODULES(GLIB2, glib-2.0 >= GLIB2_REQUIRED)
AC_SUBST(GLIB2_CFLAGS)
AC_SUBST(GLIB2_LIBS)

PKG_CHECK_MODULES(POPT, popt >= POPT_REQUIRED)
AC_SUBST(POPT_CFLAGS)
AC_SUBST(POPT_LIBS)

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
