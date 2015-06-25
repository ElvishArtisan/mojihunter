// qt3chars.cpp
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

#include <qapplication.h>

#include "qt3chars.h"

MainWidget::MainWidget(QWidget *parent)
  :QMainWindow(parent)
{

  //
  // Create Fonts
  //
  QFont font("Helvetica",10,QFont::Normal);
  font.setPixelSize(10);
  setFont(font);
  QFont main_font("Helvetica",12,QFont::Bold);
  main_font.setPixelSize(12);
  QFont label_font("Helvetica",10,QFont::Bold);
  label_font.setPixelSize(10);

}


QSize MainWidget::sizeHint() const
{
  return QSize(400,300);
}


QSizePolicy MainWidget::sizePolicy() const
{
  return QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
}


int main(int argc,char *argv[])
{
  QApplication a(argc,argv);

  MainWidget *w=new MainWidget();
  a.setMainWidget(w);
  w->show();
  return a.exec();
}
