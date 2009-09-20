AC_INIT([befunge], [0.1.0], [sudharsh@gmail.com], [befunge])
AC_CONFIG_SRCDIR([Makefile.am])
AC_CONFIG_HEADERS(config.h)
AM_INIT_AUTOMAKE([dist-bzip2])
AM_MAINTAINER_MODE

AC_PROG_CC
AM_PROG_CC_C_O
AC_DISABLE_STATIC
AC_PROG_LIBTOOL


dnl define TRUE and FALSE
FALSE=(0)
AC_DEFINE_UNQUOTED(FALSE, $FALSE, [Boolean False])
AC_DEFINE_UNQUOTED(TRUE, (!FALSE), [Boolean True]) 

AC_OUTPUT([
Makefile
src/Makefile
])
