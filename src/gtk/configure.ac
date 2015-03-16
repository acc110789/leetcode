AC_INIT([gtk-testcase], [1.0], [xiang.zhai@i-soft.com.cn])
AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror foreign])
AC_PROG_CC
AM_MAINTAINER_MODE
AC_CONFIG_MACRO_DIR([m4])
LT_INIT

CFLAGS='-Wall -std=gnu99'

GTK3_REQUIRED=3.8.2                                                             
GDK3_REQUIRED=3.8.2                                                             
GLIB2_REQUIRED=2.36.3                                                           
                                                                                
PKG_CHECK_MODULES(GTK_TESTCASE, gtk+-3.0 >= $GTK3_REQUIRED gdk-3.0 >= $GDK3_REQUIRED glib-2.0 >= $GLIB2_REQUIRED)
AC_SUBST(GTK_TESTCASE_CFLAGS)                                                 
AC_SUBST(GTK_TESTCASE_LIBS)

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
