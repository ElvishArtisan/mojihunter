## automake.am
##
## Automake.am for mojihunter/src/mojihunter
##
##   (C) Copyright 2015-2019 Fred Gleason <fredg@paravelsystems.com>
##
##   This program is free software; you can redistribute it and/or modify
##   it under the terms of the GNU General Public License as
##   published by the Free Software Foundation; either version 2 of
##   the License, or (at your option) any later version.
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

if MOJI_QT3
  MOJI_MOJIHUNTER_QT3_OPT = qt3
endif
if MOJI_QT4
  MOJI_MOJIHUNTER_QT4_OPT = qt4
endif
if MOJI_QT5
  MOJI_MOJIHUNTER_QT5_OPT = qt5
endif
SUBDIRS = $(MOJI_MOJIHUNTER_QT3_OPT) $(MOJI_MOJIHUNTER_QT4_OPT) $(MOJI_MOJIHUNTER_QT5_OPT)
