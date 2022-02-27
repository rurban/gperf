dnl autoconf configuration for gperf

dnl Copyright (C) 1998-2022 Free Software Foundation, Inc.
dnl Written by Douglas C. Schmidt <schmidt@ics.uci.edu>
dnl and Bruno Haible <bruno@clisp.org>.
dnl Refactored by Reini Urban, 2022
dnl
dnl This file is part of GNU GPERF.
dnl
dnl This program is free software: you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 3 of the License, or
dnl (at your option) any later version.
dnl
dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with this program.  If not, see <https://www.gnu.org/licenses/>.

AC_PREREQ([2.64])
AC_INIT([gperf],[m4_esyscmd(build-aux/git-version-gen .tarball-version)],[bug-gperf@gnu.org],[],[https://savannah.gnu.org/projects/gperf/])
AC_CONFIG_SRCDIR([src/main.cc])
AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([-Wall 1.14 gnu no-define info-in-builddir std-options])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_CONFIG_HEADERS([src/config.h])
AC_MSG_CHECKING([git version])
AC_MSG_RESULT($PACKAGE_VERSION)

AC_CANONICAL_HOST

dnl
dnl           checks for programs
dnl
AC_PROG_MAKE_SET
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_CXXCPP
AC_PROG_INSTALL
AM_PROG_AR
#AC_CHECK_PROGS([AR], [gnu-ar ar])
AC_CHECK_PROGS([RANLIB], [gnu-ranlib ranlib])

AC_CHECK_PROGS([SED],[sed])
AC_CHECK_PROGS([DIFF],[diff])
AC_CHECK_PROGS([XXD],[xxd])

dnl
dnl           checks for compiler characteristics
dnl
CXXFLAGS_save="$CXXFLAGS"
AC_CACHE_CHECK([for stack-allocated variable-size arrays],
  [gp_cv_cxx_dynamic_array],
  [AC_LANG_PUSH([C++])
   CXXFLAGS="$CXXFLAGS -Werror=vla"
   AC_COMPILE_IFELSE(
     [AC_LANG_PROGRAM([[int func (int n) { int dynamic_array[n]; }]], [[]])],
     [gp_cv_cxx_dynamic_array=yes], [gp_cv_cxx_dynamic_array=no])
   AC_LANG_POP([C++])
  ])
if test $gp_cv_cxx_dynamic_array = yes; then
  AC_DEFINE([HAVE_DYNAMIC_ARRAY], [1],
    [Define if the C++ compiler supports stack-allocated variable-size arrays.])
fi
CXXFLAGS="$CXXFLAGS_save"

if test $ac_cv_c_compiler_gnu = yes && test $ac_cv_cxx_compiler_gnu = yes; then
  CHECK_LANG_SYNTAX='check-lang-syntax'
else
  CHECK_LANG_SYNTAX=''
fi
AC_SUBST([CHECK_LANG_SYNTAX])
dnl
dnl           checks for functions and declarations
dnl
AC_CHECK_HEADERS([stddef.h unistd.h])

AC_CHECK_FUNCS([strndup])
AC_DEFINE([_POSIX_C_SOURCE],[200809L],[Needed for strdup])
AC_DEFINE([__XSI_VISIBLE],[700],[Needed for cygwin strdup])

AC_CHECK_HEADER([endian.h])     dnl for mi_vector_hash
AC_CHECK_HEADER([sys/endian.h]) dnl for mi_vector_hash

AC_CHECK_HEADER([smmintrin.h])  dnl for crc
AC_CHECK_FUNCS([_mm_crc32_u32])
AC_CHECK_FUNCS([_mm_crc32_u64])

dnl
dnl           checks for libraries
dnl
AC_CHECK_LIB([m], [rand], [GPERF_LIBM="-lm"], [GPERF_LIBM=""])
AC_SUBST([GPERF_LIBM])
dnl
dnl           That's it.
dnl
dnl AC_CONFIG_SUBDIRS([lib src tests doc])
AC_CONFIG_FILES([
        Makefile
        lib/Makefile
        src/Makefile
        doc/Makefile
        tests/Makefile
        ])

AC_OUTPUT
