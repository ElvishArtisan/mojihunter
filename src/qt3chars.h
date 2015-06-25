// qt3chars.h
//
// A utility for testing RDBMS for character fidelity.
//
//   (C) Copyright 2015 Fred Gleason <fredg@paravelsystems.com>
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License version 2 as
//   published by the Free Software Foundation.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public
//   License along with this program; if not, write to the Free Software
//   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//

#ifndef QT3CHARS_H
#define QT3CHARS_H

#include <qmainwindow.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qsocketdevice.h>
#include <qlabel.h>
#include <qtimer.h>

class MainWidget : public QMainWindow
{
  Q_OBJECT
 public:
  MainWidget(QWidget *parent=0);
  QSize sizeHint() const;
  QSizePolicy sizePolicy() const;
};


#endif  // QT3CHARS_H
