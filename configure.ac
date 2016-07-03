#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([bdgui], [0.1], [allu_yuan@163.com])

CFLAGS="$CFLAGS -std=gnu99"

AC_CONFIG_SRCDIR([src/event/events.c])

AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE(bdgui, 0.1)

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_PROG_RANLIB

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h stddef.h stdint.h stdlib.h string.h sys/ioctl.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
# AC_FUNC_MALLOC
AC_FUNC_MMAP
AC_CHECK_FUNCS([memset munmap])

AC_DEFINE(WITH_GDSL, 1, with gdsl library)
AC_DEFINE(WITH_LINUX, 1, with linux)

AC_OUTPUT([Makefile
          src/Makefile])
