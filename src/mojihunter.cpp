// mojihunter.cpp
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
#include <qmessagebox.h>
#include <qsqldatabase.h>

#include "mojihunter.h"

MainWidget::MainWidget(QWidget *parent)
  :QMainWindow(parent)
{
  //
  // Create Fonts
  //
  QFont font("Helvetica",12,QFont::Normal);
  font.setPixelSize(12);
  setFont(font);
  QFont label_font("Helvetica",12,QFont::Bold);
  label_font.setPixelSize(12);

  //
  // Set Window Title
  //
  setCaption(tr("MojiHunter")+" v"+VERSION);

  //
  // Dialogs
  //
  moji_text_viewer=new TextViewer(this);

  //
  // DB Type
  //
  moji_db_type_box=new QComboBox(this);
  moji_db_type_label=
    new QLabel(moji_db_type_box,tr("DB Type")+":",this);
  moji_db_type_label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
  moji_db_type_label->setFont(label_font);
  moji_db_type_box->insertItem("QODBC3");
  moji_db_type_box->insertItem("QOCI8");
  moji_db_type_box->insertItem("QQSQL7");
  moji_db_type_box->insertItem("QTDS7");
  moji_db_type_box->insertItem("QMYSQL3");
  moji_db_type_box->insertItem("QDB2");
  moji_db_type_box->insertItem("QSQLITE");
  moji_db_type_box->insertItem("QIBASE");

  //
  // DB Hostname
  //
  moji_db_hostname_edit=new QLineEdit(this);
  moji_db_hostname_label=
    new QLabel(moji_db_hostname_edit,tr("DB Host")+":",this);
  moji_db_hostname_label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
  moji_db_hostname_label->setFont(label_font);

  //
  // DB Database Name
  //
  moji_db_dbname_edit=new QLineEdit(this);
  moji_db_dbname_label=
    new QLabel(moji_db_dbname_edit,tr("DB Database Name")+":",this);
  moji_db_dbname_label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
  moji_db_dbname_label->setFont(label_font);

  //
  // DB Username
  //
  moji_db_username_edit=new QLineEdit(this);
  moji_db_username_label=
    new QLabel(moji_db_username_edit,tr("DB User")+":",this);
  moji_db_username_label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
  moji_db_username_label->setFont(label_font);

  //
  // DB Password
  //
  moji_db_password_edit=new QLineEdit(this);
  moji_db_password_edit->setEchoMode(QLineEdit::Password);
  moji_db_password_label=
    new QLabel(moji_db_password_edit,tr("DB Password")+":",this);
  moji_db_password_label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
  moji_db_password_label->setFont(label_font);

  //
  // Process Button
  //
  moji_process_button=new QPushButton(tr("Process"),this);
  moji_process_button->setFont(label_font);
  moji_process_button->setDisabled(true);
  connect(moji_process_button,SIGNAL(clicked()),
	  this,SLOT(processClickedData()));

  //
  // View SQL Button
  //
  moji_sql_button=new QPushButton(tr("View SQL"),this);
  moji_sql_button->setFont(label_font);
  moji_sql_button->setDisabled(true);
  connect(moji_sql_button,SIGNAL(clicked()),
	  this,SLOT(sqlClickedData()));

  //
  // Input Text
  //
  moji_input_text=new QTextEdit(this);
  moji_input_text->setFont(font);
  connect(moji_input_text,SIGNAL(textChanged()),this,SLOT(inputChangedData()));
  moji_input_label=new QLabel(moji_input_text,tr("Input Text"),this);
  moji_input_label->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
  moji_input_label->setFont(label_font);

  //
  // Result
  //
  moji_result_text=new QTextEdit(this);
  moji_result_text->setFont(font);
  moji_result_text->setReadOnly(true);
  moji_result_label=new QLabel(moji_result_text,tr("Result"),this);
  moji_result_label->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
  moji_result_label->setFont(label_font);

  setMinimumSize(sizeHint());
}


QSize MainWidget::sizeHint() const
{
  return QSize(400,600);
}


QSizePolicy MainWidget::sizePolicy() const
{
  return QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
}


void MainWidget::processClickedData()
{
  Process();
}


void MainWidget::sqlClickedData()
{
  moji_text_viewer->exec(InsertionSql(),tr("Insertion SQL"));
}


void MainWidget::inputChangedData()
{
  moji_process_button->setDisabled(moji_input_text->text().isEmpty());
  moji_sql_button->setDisabled(moji_input_text->text().isEmpty());
}


void MainWidget::resizeEvent(QResizeEvent *e)
{
  moji_db_type_label->setGeometry(10,10,120,20);
  moji_db_type_box->setGeometry(135,10,size().width()-145,20);

  moji_db_hostname_label->setGeometry(10,32,120,20);
  moji_db_hostname_edit->setGeometry(135,32,size().width()-145,20);

  moji_db_dbname_label->setGeometry(10,54,120,20);
  moji_db_dbname_edit->setGeometry(135,54,size().width()-145,20);

  moji_db_username_label->setGeometry(10,76,120,20);
  moji_db_username_edit->setGeometry(135,76,size().width()-145,20);

  moji_db_password_label->setGeometry(10,98,120,20);
  moji_db_password_edit->setGeometry(135,98,size().width()-145,20);

  moji_process_button->setGeometry(145,125,100,33);

  moji_sql_button->setGeometry(size().width()-120,125,100,33);

  moji_input_label->setGeometry(15,155,100,20);
  moji_input_text->
    setGeometry(10,175,size().width()-20,(size().height()-152)/2-32);

  moji_result_label->setGeometry(15,170+(size().height()-152)/2-22,100,20);
  moji_result_text->
    setGeometry(10,190+(size().height()-152)/2-22,
		size().width()-20,(size().height()-152)/2-22);
}


void MainWidget::Process()
{
  QSqlDatabase *db=NULL;
  QString sql;
  QSqlQuery *q;

  db=QSqlDatabase::addDatabase(moji_db_type_box->currentText());
  if(!db) {
    QMessageBox::critical(this,tr("MojiHunter")+" - "+tr("Database Error"),
			  tr("Unable to open DB connection."));
    return;
  }
  db->setDatabaseName(moji_db_dbname_edit->text());
  db->setHostName(moji_db_hostname_edit->text());
  db->setUserName(moji_db_username_edit->text());
  db->setPassword(moji_db_password_edit->text());
  if(!db->open()) {
    QMessageBox::critical(this,tr("MojiHunter")+" - "+tr("Database Error"),
			  tr("Unable to connect to database")+"\n"+
			  db->lastError().text()+".");
    QSqlDatabase::removeDatabase(db);
    return;
  }
  q=new QSqlQuery(InsertionSql());
  if(!q->isActive()) {
    QMessageBox::warning(this,tr("Mojihunter")+" - "+tr("Insertion SQL Error"),
			 tr("SQL Error")+":\n"+db->lastError().text());
    delete q;
    QSqlDatabase::removeDatabase(db);
    return;
  }
  delete q;

  sql=QString("select MOJIFIELD from MOJITABLE ")+
    "where ID=LAST_INSERT_ID()";
  q=new QSqlQuery(sql);
  if(!q->isActive()) {
    QMessageBox::warning(this,tr("Mojihunter")+" - "+tr("Select SQL Error"),
			 tr("SQL Error")+":\n"+db->lastError().text());
    delete q;
    QSqlDatabase::removeDatabase(db);
    return;
  }
  if(q->first()) {
    moji_result_text->setText(q->value(0).toString());
  }
  delete q;

  QSqlDatabase::removeDatabase(db);
}


QString MainWidget::InsertionSql() const
{
  return QString("insert into MOJITABLE set ")+
    "MOJIFIELD=\""+SqlEscape(moji_input_text->text())+"\"";
}


QString MainWidget::SqlEscape(const QString &str) const
{
  return str;
}


int main(int argc,char *argv[])
{
  QApplication a(argc,argv);

  MainWidget *w=new MainWidget();
  a.setMainWidget(w);
  w->show();
  return a.exec();
}
