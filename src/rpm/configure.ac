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

#=================
# Check for libelf library. Prefer external, otherwise none.
WITH_LIBELF_LIB=
AC_CHECK_HEADER([libelf.h])
AC_CHECK_HEADERS([gelf.h], [
	AC_CHECK_LIB(elf, gelf_getvernaux, [
	    AC_DEFINE(HAVE_LIBELF, 1, [Define to 1 if you have the 'elf' library (-lelf).])
	    WITH_LIBELF_LIB="-lelf"
	    WITH_LIBELF=yes
	])
])
AC_SUBST(WITH_LIBELF_LIB)
AM_CONDITIONAL(LIBELF,[test "$WITH_LIBELF" = yes])

#=================
# Check for librpmbuild library. Prefer external, otherwise none.
WITH_LIBRPMBUILD_LIB=
AC_CHECK_HEADER([rpm/rpmbuild.h])
AC_CHECK_HEADERS([rpm/rpmspec.h], [
	AC_CHECK_LIB(rpmbuild, rpmSpecCheckDeps, [
	    AC_DEFINE(HAVE_LIBRPMBUILD, 1, [Define to 1 if you have the 'rpmbuild' library (-lrpmbuild).])
	    WITH_LIBRPMBUILD_LIB="-lrpmbuild"
	    WITH_LIBRPMBUILD=yes
	])
])
AC_SUBST(WITH_LIBRPMBUILD_LIB)
AM_CONDITIONAL(LIBRPMBUILD,[test "$WITH_LIBRPMBUILD" = yes])

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
