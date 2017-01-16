dnl Process this file with autoconf to produce a configure script.
AC_PREREQ(2.59)
AC_INIT([libpaillier], [0.8], [bethenco@cs.berkeley.edu])
AC_CONFIG_SRCDIR([paillier.h])

dnl First, standard system stuff.

dnl  language and compiler support
if test "x${CFLAGS}" == x; then
  CFLAGS="-O3 -Wall"
fi
if test "x${LDFLAGS}" == x; then
  LDFLAGS="-O3 -Wall"
fi
AC_PROG_CC
AC_LANG(C)

dnl  standard headers
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h],,
  [AC_MSG_ERROR([could not find standard headers stdlib.h, string.h])])

dnl  specific library functions and types
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_TYPE_SIZE_T
AC_CHECK_FUNCS([memset],,
  [AC_MSG_ERROR([could not link to required function memset])])

dnl Now, we check for specific packages we need.
PRIVSS_GMP_CHECK

dnl Specify the output.
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
