## Makefile.am
##
##   (C) Copyright 2015-2019 Fred Gleason <fredg@paravelsystems.com>
##
##   This program is free software; you can redistribute it and/or modify
##   it under the terms of the GNU General Public License version 2 as
##   published by the Free Software Foundation.
##
##   This program is distributed in the hope that it will be useful,
##   but WITHOUT ANY WARRANTY; without even the implied warranty of
##   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##   GNU General Public License for more details.
##
##   You should have received a copy of the GNU General Public
##   License along with this program; if not, write to the Free Software
##   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
##
## Use automake to process this into a Makefile.in

AM_CPPFLAGS = -Wall -DPREFIX=\"$(prefix)\" -DQTDIR=\"@QT_DIR@\" @QT_CXXFLAGS@ -I$(top_srcdir)/lib
LIBS = @QT_LIBS@ -L$(top_srcdir)/lib
MOC = @QT_MOC@

# The dependency for qt's Meta Object Compiler (moc)
moc_%.cpp:	%.h
	$(MOC) $< -o $@

bin_PROGRAMS = mojihunter3

dist_mojihunter3_SOURCES = mojihunter3.cpp mojihunter3.h\
                           profile.cpp profile.h\
                           textviewer.cpp textviewer.h

nodist_mojihunter3_SOURCES = moc_mojihunter3.cpp\
                             moc_textviewer.cpp

mojihunter3_LDADD = -lm -lpthread -lqui

CLEANFILES = *~\
             *.exe\
             *.idb\
             *ilk\
             *.qm\
             *.obj\
             *.pdb\
             moc_*

MAINTAINERCLEANFILES = *~\
                       Makefile.in\
                       moc_*
