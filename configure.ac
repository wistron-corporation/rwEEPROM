AC_PREREQ([2.69])
AC_INIT([dbus], [1.0], [bug-automake@gnu.org])
#AC_LANG([C++])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([fcntl.h])
AC_CHECK_HEADERS([libxml/parser.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([wEE.cpp])
AC_CONFIG_MACRO_DIRS([m4])
AC_CHECK_FUNCS([strerror])

# Checks for programs.
AC_PROG_CXX
AM_PROG_AR
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_RANLIB

# Checks for typedefs, structures, and compiler characteristics.
AX_CXX_COMPILE_STDCXX_11(noext)
AX_APPEND_COMPILE_FLAGS([-Wall -Werror], [CXXFLAGS])

# Checks for libraries.
LT_INIT
AC_ENABLE_SHARED
AC_DISABLE_STATIC
AC_PROG_LIBTOOL(libtool)

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

# Output Makefile file.
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
