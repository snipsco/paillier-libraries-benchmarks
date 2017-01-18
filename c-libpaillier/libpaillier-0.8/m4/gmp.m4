dnl Check for GNU MP and set GMP_CFLAGS and GMP_LIBS appropriately.

AC_DEFUN([PRIVSS_GMP_CHECK],
[

AC_ARG_WITH(gmp-include,
 AC_HELP_STRING([--with-gmp-include=<path>],
   [look for the header gmp.h in <path> rather than the default search path]),
  [
   GMP_INPUT_HEADER=$withval
   GMP_HEADER_PATH="${GMP_INPUT_HEADER} /usr/include /usr/local/include"
  ],
  [
    GMP_HEADER_PATH="/usr/include /usr/local/include"
  ])

AC_ARG_WITH(gmp-lib,
 AC_HELP_STRING([--with-gmp-lib=<path>],
   [look for libgmp in <path> rather than the default search path]),
  [
    GMP_INPUT_LIB=$withval
    GMP_LIBRARY_PATH="${GMP_INPUT_LIB} /lib /usr/lib /usr/local/lib /var/lib"
  ],
  [
    GMP_LIBRARY_PATH="/lib /usr/lib /usr/local/lib /var/lib"
  ])

dnl input data check
if test  "x${GMP_INPUT_HEADER}" != x; then
  if test -z "${GMP_INPUT_LIB}"; then
    echo 'error: since you have specified the GMP header path, you must specify the'
    echo 'GMP library path using --with-gmp-lib.'
    exit 1
  fi
fi

if test "x${GMP_INPUT_LIB}" != x; then
  if test -z "${GMP_INPUT_HEADER}"; then
    echo 'error: since you have specified the GMP library path, you must specify the'
    echo 'GMP header path using --with-gmp-include.'
    exit 1
  fi
fi

min_gmp_version=ifelse([$1], ,3.1.1,$1)

dnl check for existence
BACKUP_CFLAGS=${CFLAGS}
BACKUP_LIBS=${LIBS}

AC_MSG_CHECKING(for GMP >= $min_gmp_version)

gmp_found="no"

for GMP_HEADER in ${GMP_HEADER_PATH}
do
  if test -r "${GMP_HEADER}/gmp.h"; then
    if test "x${GMP_HEADER}" != "x/usr/include" -a "x${GMP_HEADER}" != "x/usr/local/include"; then
      for GMP_LIBRARY in ${GMP_LIBRARY_PATH}
      do
        if test "x${GMP_LIBRARY}" != "x/usr/lib" -a "x${GMP_LIBRARY}" != "x/usr/local/lib"; then
          GMP_CFLAGS="-I${GMP_HEADER}"
          GMP_LIBS="${GMP_LIBS} -L${GMP_LIBRARY} -lgmp"
        fi
      done
    else
      GMP_CFLAGS=
      GMP_LIBS="-lgmp"
    fi

    CFLAGS="${CFLAGS} ${GMP_CFLAGS}"
    LIBS="${LIBS} ${GMP_LIBS}"

    AC_TRY_LINK(
    [#include <gmp.h>],
    [mpz_t a; mpz_init (a);],
    [
      AC_TRY_RUN(
       [#include <gmp.h>
       int main() { if (__GNU_MP_VERSION < 3) return -1;
               else return 0; }
        ],[
        AC_MSG_RESULT(found)
        gmp_found="yes"
        AC_SUBST(GMP_CFLAGS)
          AC_SUBST(GMP_LIBS)
        AC_DEFINE(HAVE_GMP,1,[Define if GMP is installed])
        # see if we are running gmp 4.0
           AC_MSG_CHECKING(whether GMP is 4.0 or greater)
           AC_TRY_RUN(
           [#include <gmp.h>
            int main () { if (__GNU_MP_VERSION < 4) return -1; else return 0; }
           ],[
          AC_MSG_RESULT(yes)
        ],[
          AC_MSG_RESULT(no)
          AC_DEFINE(GMP_VERSION_3,1,[Define if GMP is version 3.xxx])
          GMP_VERSION="-DGMP_VERSION_3"
          AC_SUBST(GMP_VERSION)
        ],[
          dnl this should never happen
          AC_MSG_RESULT(no)
        ])
        break
      ],[
        gmp_problem="$gmp_problem $GMP_HEADER"
        unset GMP_CFLAGS
        unset GMP_LIBS
      ],[
        AC_MSG_RESULT(unknown)
        gmp_found="yes"
        echo 'You appear to be cross compiling, so there is'
        echo 'no way to determine whether your GMP version is new enough.'
        echo 'I am assuming it is'
        AC_SUBST(GMP_CFLAGS)
        AC_SUBST(GMP_LIBS)
        AC_DEFINE(HAVE_GMP,1,[Define if GMP is installed])
        break
      ])
    ],[
    unset GMP_CFLAGS
    unset GMP_LIBS
    ])
  fi
done

if test "x$gmp_found" = "xno"; then
  if test -n "$gmp_problem"; then
    AC_MSG_RESULT(old version)
    AC_MSG_ERROR([

Your version of the GNU Multiple Precision library (libgmp) is too
old! Please install a more recent version from http://swox.com/gmp and
try again. If more than one version is installed, try specifying a
particular version with

  ./configure --with-gmp-include=<path> --with-gmp-lib=<path>

See ./configure --help for more information.
])
  else
    AC_MSG_RESULT(not found)
    AC_MSG_ERROR([

The GNU Multiple Precision library (libgmp) was not found on your
system! Please obtain it from http://swox.com/gmp and install it
before trying again. If libgmp is already installed in a non-standard
location, try again with

  ./configure --with-gmp-include=<path> --with-gmp-lib=<path>

See ./configure --help for more information.
])
  fi
fi

CFLAGS=${BACKUP_CFLAGS}
LIBS=${BACKUP_LIBS}

])
