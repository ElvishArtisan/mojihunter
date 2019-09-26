// textviewer.cpp
//
// Display text so it can be copy/pasted
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

#include "textviewer.h"

TextViewer::TextViewer(QWidget *parent)
  : QDialog(parent)
{
  QFont button_font("helvetica",12,QFont::Bold);
  button_font.setPixelSize(12);

  text_view=new QTextEdit(this);
  text_view->setReadOnly(true);

  text_close_button=new QPushButton(tr("Close"),this);
  text_close_button->setFont(button_font);
  connect(text_close_button,SIGNAL(clicked()),this,SLOT(closeData()));

  setMinimumSize(sizeHint());
}


TextViewer::~TextViewer()
{
  delete text_close_button;
  delete text_view;
}


QSize TextViewer::sizeHint() const
{
  return QSize(400,300);
}


QSizePolicy TextViewer::sizePolicy() const
{
  return QSizePolicy(QSizePolicy::MinimumExpanding,
		     QSizePolicy::MinimumExpanding);
}


int TextViewer::exec(const QString &text,const QString &title)
{
  setWindowTitle(tr("MojiHunter")+" - "+title);
  text_view->setText(text);
  return QDialog::exec();
}


void TextViewer::closeData()
{
  done(0);
}


void TextViewer::resizeEvent(QResizeEvent *e)
{
  text_view->setGeometry(10,10,size().width()-20,size().height()-50);
  text_close_button->setGeometry(size().width()-70,size().height()-35,60,30);
}
