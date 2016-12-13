#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(test_takao_mincho, 0.0.1, mihara@netlab.jp)
AC_CONFIG_SRCDIR([test_takao_mincho.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([no-define])

# Checks for programs.
AC_PROG_CC
AC_PROG_CPP

AM_PROG_CC_C_O

AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

AC_HEADER_STDC

# Checks for libraries.

PKG_CHECK_MODULES(PANGOVERSION, pango >= 1.8.0, , 
                  AC_MSG_ERROR([Need Pango version 1.8.0 or higher]))

PKG_CHECK_MODULES(CAIRO, cairo,have_cairo=yes,have_cairo=no)
AC_SUBST(CAIRO_LIBS)
AC_SUBST(CAIRO_CFLAGS)

PKG_CHECK_MODULES(PANGOCAIRO,pangocairo, pangocairo_ok=yes, pangocairo_ok=no)

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h stdlib.h sys/socket.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
