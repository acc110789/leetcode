AC_INIT([gtk-testcase], [1.0], [xiang.zhai@i-soft.com.cn])
AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror foreign])
AC_PROG_CC
AM_MAINTAINER_MODE
AC_CONFIG_MACRO_DIR([m4])
LT_INIT

CFLAGS='-Wall -std=gnu99'

GTK2_REQUIRED=2.24
GTK3_REQUIRED=3.8.2
GDK3_REQUIRED=3.8.2
GLIB2_REQUIRED=2.36.3
CLUTTER_REQUIRED=1.20
CLUTTER_GTK_REQUIRED=1.2

PKG_CHECK_MODULES(GTK2, gtk+-2.0 >= $GTK2_REQUIRED)
AC_SUBST(GTK2_CFLAGS)
AC_SUBST(GTK2_LIBS)

PKG_CHECK_MODULES(GTK3, gtk+-3.0 >= $GTK3_REQUIRED 
                  gdk-3.0 >= $GDK3_REQUIRED glib-2.0 >= $GLIB2_REQUIRED)
AC_SUBST(GTK3_CFLAGS)
AC_SUBST(GTK3_LIBS)

PKG_CHECK_MODULES(CLUTTER, clutter-1.0 >= CLUTTER_REQUIRED 
                  clutter-gtk-1.0 >= CLUTTER_GTK_REQUIRED)
AC_SUBST(CLUTTER_CFLAGS)
AC_SUBST(CLUTTER_LIBS)

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
