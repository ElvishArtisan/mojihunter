dnl configure.ac
dnl
dnl Autoconf configuration for mojihunter
dnl Use autoconf to process this into a configure script
dnl
dnl   (C) Copyright 2015-2021 Fred Gleason <fredg@paravelsystems.com>
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

AC_INIT([mojihunter],m4_esyscmd(cat PACKAGE_VERSION))
AM_INIT_AUTOMAKE
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])
AC_CONFIG_MACRO_DIR([m4])

#
# Basic Compiler Checks
#
AC_PROG_CXX
AC_LANG(C++)

#
# Check for Qt3
#
BNV_HAVE_QT
AM_CONDITIONAL([MOJI_QT3], [test "$have_qt" = yes])

#
# Check for Qt4
#
PKG_CHECK_MODULES(QT4,QtCore QtGui QtSql QtNetwork,[have_qt4=yes],[have_qt4=no])
AM_CONDITIONAL([MOJI_QT4], [test "$have_qt4" = yes])
if test $have_qt4="yes" ; then
  AC_CHECK_PROG(MOC_NAME,moc-qt4,[moc-qt4],[moc])
  AC_SUBST(QT4_MOC,$MOC_NAME)
else
  AC_SUBST(QT4_MOC,"")
fi

#
# Check for Qt5
#
PKG_CHECK_MODULES(QT5,Qt5Core Qt5Widgets Qt5Sql Qt5Network Qt5PrintSupport,[have_qt5=yes],[have_qt5=no])
AM_CONDITIONAL([MOJI_QT5], [test "$have_qt5" = yes])
if test $have_qt5="yes" ; then
  AC_CHECK_PROG(MOC5_NAME,moc-qt5,[moc-qt5],[moc])
  echo "MOC5: $MOC5_NAME"
  AC_SUBST(QT5_MOC,$MOC5_NAME)
else
  AC_SUBST(QT5_MOC,"")
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
    src/fonthunter/Makefile \
    src/fonthunter/qt3/Makefile \
    src/fonthunter/qt4/Makefile \
    src/fonthunter/qt5/Makefile \
    src/mojihunter/Makefile \
    src/mojihunter/qt3/Makefile \
    src/mojihunter/qt4/Makefile \
    src/mojihunter/qt5/Makefile \
    src/timezonehunter/Makefile \
    src/timezonehunter/qt4/Makefile \
    Makefile \
    ])
AC_OUTPUT()

#
# Configuration Results
#
AC_MSG_NOTICE()
AC_MSG_NOTICE("|------------------------------------------|")
AC_MSG_NOTICE("| *** MOJIHUNTER CONFIGURATION SUMMARY *** |")
AC_MSG_NOTICE("|------------------------------------------|")
AC_MSG_NOTICE("| Detected Qt Versions:                    |")
if test "$have_qt" = no ; then
AC_MSG_NOTICE("|                         Qt 3.x ... No    |")
else
AC_MSG_NOTICE("|                         Qt 3.x ... Yes   |")
fi
if test "$have_qt4" = no ; then
AC_MSG_NOTICE("|                         Qt 4.x ... No    |")
else
AC_MSG_NOTICE("|                         Qt 4.x ... Yes   |")
fi
if test "$have_qt5" = no ; then
AC_MSG_NOTICE("|                         Qt 5.x ... No    |")
else
AC_MSG_NOTICE("|                         Qt 5.x ... Yes   |")
fi
AC_MSG_NOTICE("|------------------------------------------|")
AC_MSG_NOTICE()
AC_MSG_NOTICE(Now enter 'make' to build the software.)
AC_MSG_NOTICE()
