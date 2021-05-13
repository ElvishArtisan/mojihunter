## Makefile.am
##
##   (C) Copyright 2015-2021 Fred Gleason <fredg@paravelsystems.com>
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

AM_CPPFLAGS = -Wall -DPREFIX=\"$(prefix)\" -pthread -fPIC -std=c++11 @QT5_CFLAGS@
MOC = @QT5_MOC@

# The dependency for qt's Meta Object Compiler (moc)
moc_%.cpp:	%.h
	$(MOC) $< -o $@

bin_PROGRAMS = mojihunter5

dist_mojihunter5_SOURCES = mojihunter5.cpp mojihunter5.h\
                           profile.cpp profile.h\
                           textviewer.cpp textviewer.h

nodist_mojihunter5_SOURCES = moc_mojihunter5.cpp\
                             moc_textviewer.cpp

mojihunter5_LDADD = -lm -lpthread @QT5_LIBS@

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
