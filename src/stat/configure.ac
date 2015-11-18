AC_INIT([stat-testcase], [1.0], [xiang.zhai@i-soft.com.cn])
AM_INIT_AUTOMAKE([1.11 subdir-objects foreign])
AC_PROG_CC
AM_MAINTAINER_MODE
AC_CONFIG_MACRO_DIR([m4])
LT_INIT

# for gcc 5.x
CFLAGS='-Wall -std=gnu11'

GLIB2_REQUIRED=2.36.3
GIO2_REQUIRED=2.36.3

PKG_CHECK_MODULES(GLIB2, glib-2.0 >= $GLIB2_REQUIRED)
AC_SUBST(GLIB2_CFLAGS)
AC_SUBST(GLIB2_LIBS)

PKG_CHECK_MODULES(GIO2, gio-2.0 >= $GIO2_REQUIRED)
AC_SUBST(GIO2_CFLAGS)
AC_SUBST(GIO2_LIBS)

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
