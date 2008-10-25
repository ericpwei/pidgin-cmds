AC_PREREQ(2.59)
AC_INIT(pidgin-cmds, 0.1.0, ericwei.dev@gmail.com)
AM_INIT_AUTOMAKE
AM_MAINTAINER_MODE

AC_PROG_CC
AC_PROG_INSTALL
AC_DISABLE_STATIC

AM_PROG_LIBTOOL
LIBTOOL="$LIBTOOL --silent"
AC_DEFINE(PURPLE_PLUGINS, 1, ["pidgin_plugin"])

PKG_CHECK_MODULES(pidgin, [pidgin >= 2.0.0])
AC_SUBST(pidgin_CFLAGS)
AC_SUBST(pidgin_LIBS)

PKG_CHECK_MODULES(glib, [glib-2.0])
AC_SUBST(glib_CFLAGS)
AC_SUBST(glib_LIBS)

PIDGIN_INSTALL="`$PKG_CONFIG pidgin --variable=libdir`/pidgin"
AC_SUBST(PIDGIN_INSTALL)

AC_OUTPUT([
	Makefile
	src/Makefile
])
