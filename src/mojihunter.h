// mojihunter.h
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
#include <qtextedit.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qlabel.h>

#include "textviewer.h"

class MainWidget : public QMainWindow
{
  Q_OBJECT
 public:
  MainWidget(QWidget *parent=0);
  QSize sizeHint() const;
  QSizePolicy sizePolicy() const;

 private slots:
  void processClickedData();
  void sqlClickedData();
  void inputChangedData();

 protected:
  void resizeEvent(QResizeEvent *e);

 private:
  void Process();
  QString InsertionSql() const;
  QString SqlEscape(const QString &str) const;
  QLabel *moji_db_type_label;
  QComboBox *moji_db_type_box;
  QLabel *moji_db_hostname_label;
  QLineEdit *moji_db_hostname_edit;
  QLabel *moji_db_dbname_label;
  QLineEdit *moji_db_dbname_edit;
  QLabel *moji_db_username_label;
  QLineEdit *moji_db_username_edit;
  QLabel *moji_db_password_label;
  QLineEdit *moji_db_password_edit;
  QLabel *moji_input_label;
  QTextEdit *moji_input_text;
  QLabel *moji_result_label;
  QTextEdit *moji_result_text;
  QPushButton *moji_process_button;
  QPushButton *moji_sql_button;
  QPushButton *moji_exit_button;
  TextViewer *moji_text_viewer;
};


#endif  // mojihunter_H
