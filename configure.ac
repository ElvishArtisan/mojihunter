dnl configure.ac
dnl
dnl Autoconf configuration for qt3chars
dnl Use autoconf to process this into a configure script
dnl
dnl   (C) Copyright 2015 Fred Gleason <fredg@paravelsystems.com>
dnl
dnl   This program is free software; you can redistribute it and/or modify
dnl   it under the terms of the GNU General Public License version 2 as
dnl   published by the Free Software Foundation.
dnl
dnl   This program is distributed in the hope that it will be useful,
dnl   but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl   GNU General Public License for more details.
dnl
dnl   You should have received a copy of the GNU General Public
dnl   License along with this program; if not, write to the Free Software
dnl   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
dnl

AC_INIT([qt3chars],m4_esyscmd(cat PACKAGE_VERSION))
AM_INIT_AUTOMAKE
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])
AC_CONFIG_MACRO_DIR([m4])

#
# Basic Compiler Checks
#
AC_PROG_CXX
AC_LANG(C++)

#
# Check for Qt
#
BNV_HAVE_QT
if test $have_qt = "no" ; then
  AC_MSG_ERROR([*** Qt3 toolkit not found, unable to continue ***])
fi

#
# Determine the target architecture
#
AR_GCC_TARGET()
AC_SUBST(VENDOR,$ar_gcc_distro)
AC_SUBST(ARCH,$ar_gcc_arch)

#
# Determine Distro
#
AR_GET_DISTRO()
AC_SUBST(DISTRO,$ar_gcc_distro)


AC_CONFIG_FILES([ \
    src/Makefile \
    Makefile \
    ])
AC_OUTPUT()

#
# Configuration Results
#
AC_MSG_NOTICE()
AC_MSG_NOTICE(Now enter 'make' to build the software.)
AC_MSG_NOTICE()
