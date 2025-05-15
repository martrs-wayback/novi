# Process this file with autoconf to produce a configure script.
AC_INIT( [novi], [2.1.2], [novi-questions -at- ExMachinaTech -dot- net])

## AC_CONFIG_SRCDIR([src/support_classes.h])
## AC_CONFIG_HEADER([config.h])

## package release date
AC_SUBST(PACKAGE_RELEASE_DATE, [20120729])

## default install directory
ac_default_prefix="/opt/AC_PACKAGE_NAME-AC_PACKAGE_VERSION"

## AC_PACKAGE_NAME,
## AC_PACKAGE_VERSION,
## prefix


# Checks for programs.

AC_PROG_LIBTOOL
AC_SUBST([LIBTOOL_DEPS])



AC_PROG_CXX
## AC_PROG_CC

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lpopt':
AC_CHECK_LIB([popt], [main])
# FIXME: Replace `main' with a function in `-lrpm':
AC_CHECK_LIB([rpm], [main])

# Checks for header files.
AC_CHECK_HEADERS([unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_SIZE_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_STAT
AC_CHECK_FUNCS([mkdir strerror])

AC_CONFIG_FILES([
	Makefile
	novi.spec-autogen
	include.generated/NoviInfo.h
])
AC_OUTPUT

## make sure the generated spec file is always ready
## to be checked in
cp -f novi.spec-autogen novi.spec
