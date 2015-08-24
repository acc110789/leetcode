AC_INIT([rpm-testcase], [1.0], [xiang.zhai@i-soft.com.cn])
AM_INIT_AUTOMAKE([1.11 subdir-objects foreign])
AC_PROG_CC
AM_MAINTAINER_MODE
AC_CONFIG_MACRO_DIR([m4])
LT_INIT

CFLAGS='-Wall -std=gnu11'

RPM_REQUIRED=4.12.90

PKG_CHECK_MODULES(RPM, rpm >= RPM_REQUIRED)
AC_SUBST(RPM_CFLAGS)
AC_SUBST(RPM_LIBS)

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
