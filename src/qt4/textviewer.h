// textviewer.h
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

#ifndef TEXTVIEWER_H
#define TEXTVIEWER_H

#include <QtGui/QDialog>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>

class TextViewer : public QDialog
{
  Q_OBJECT
 public:
  TextViewer(QWidget *parent=0);
  ~TextViewer();
  QSize sizeHint() const;
  QSizePolicy sizePolicy() const;

 public slots:
   int exec(const QString &text,const QString &title);

 private slots:
  void closeData();

 protected:
  void resizeEvent(QResizeEvent *e);

 private:
  QTextEdit *text_view;
  QPushButton *text_close_button;
};


#endif  // TEXTVIEWER_H
