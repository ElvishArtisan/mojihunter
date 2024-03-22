// timezonehunter4.cpp
//
// A utility for testing timezone mapping.
//
//   (C) Copyright 2019-2024 Fred Gleason <fredg@paravelsystems.com>
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

#include <stdio.h>
#include <stdlib.h>

#include <QApplication>
#include <QDir>
#include <QFontInfo>
#include <QLabel>
#include <QResizeEvent>
#include <QStringList>

#include "cmdswitch.h"
#include "timezonehunter4.h"

MainWidget::MainWidget(QWidget *parent)
  : QWidget(parent)
{
  d_tzmap=NULL;

  //
  // Process Switches
  //
  CmdSwitch *cmd=
    new CmdSwitch(TIMEZONEHUNTER_MODNAME,TIMEZONEHUNTER_USAGE);
  for(unsigned i=0;i<cmd->keys();i++) {
    if(cmd->key(i)=="--tzid") {
      d_initial_tzid=cmd->value(i);
      cmd->setProcessed(i,true);
    }
    if(!cmd->processed(i)) {
      fprintf(stderr,"unrecognized switch \"%s\"\n",
	      cmd->key(i).toUtf8().constData());
      exit(1);
    }
  }

  //
  // Create Fonts
  //
  QFont label_font(font().family(),font().pointSize(),QFont::Bold);

  //
  // Set Window Title
  //
  setWindowTitle(tr("Timezonehunter - Qt4"));
  setMinimumSize(sizeHint());

  //
  // Zone Directory
  //
  d_zonedir_label=new QLabel(tr("Zone Directory")+":",this);
  d_zonedir_label->setFont(label_font);
  d_zonedir_label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
  d_zonedir_edit=new QLineEdit(this);
  connect(d_zonedir_edit,SIGNAL(textChanged(const QString &)),
	  this,SLOT(zonedirChangedData(const QString &)));

  //
  // TZ Identifier
  //
  d_tzid_label=new QLabel(tr("TZ Identifier")+":",this);
  d_tzid_label->setFont(label_font);
  d_tzid_label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
  d_tzid_box=new QComboBox(this);
  connect(d_tzid_box,SIGNAL(activated(const QString &)),
	  this,SLOT(tzidActivatedData(const QString &)));

  //
  // UTC Date/Time
  //
  d_utc_time_label=new QLabel(tr("UTC Date-Time")+":",this);
  d_utc_time_label->setFont(label_font);
  d_utc_time_label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
  d_utc_time_edit=new QDateTimeEdit(this);
  d_utc_time_edit->setDisplayFormat("yyyy-MM-ddThh:mm:ss");
  d_utc_time_edit->setDateTime(QDateTime::currentDateTimeUtc());

  //
  // Local Date/Time
  //
  d_local_time_label=new QLabel(tr("Local Date-Time")+":",this);
  d_local_time_label->setFont(label_font);
  d_local_time_label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
  d_local_time_edit=new QLineEdit(this);
  d_local_time_edit->setReadOnly(true);

  //
  // Apply Button
  //
  d_apply_button=new QPushButton(tr("Apply"),this);
  d_apply_button->setFont(label_font);
  connect(d_apply_button,SIGNAL(clicked()),this,SLOT(applyData()));

  d_zonedir_edit->setText("/usr/share/zoneinfo");
  tzidActivatedData(d_tzid_box->currentText());
}


QSize MainWidget::sizeHint() const
{
  return QSize(400,150);
}


void MainWidget::zonedirChangedData(const QString &dirname)
{
  QStringList files;
  ReadDir(dirname,&files);
  d_tzid_box->clear();
  for(int i=0;i<files.size();i++) {
    d_tzid_box->insertItem(d_tzid_box->count(),files.at(i));
  }
  if(!d_initial_tzid.isEmpty()) {
    for(int i=0;i<d_tzid_box->count();i++) {
      if(d_tzid_box->itemText(i)==d_initial_tzid) {
	d_tzid_box->setCurrentIndex(i);
	d_initial_tzid="";
	return;
      }
    }
    fprintf(stderr,"timezonehunter4: no such TZ identifier\n");
    exit(1);
  }
}


void MainWidget::tzidActivatedData(const QString &tzid)
{
  if(d_tzmap!=NULL) {
    delete d_tzmap;
  }
  d_tzmap=new TzMap();
  d_tzmap->load(d_zonedir_edit->text()+"/"+tzid);
}


void MainWidget::applyData()
{
  d_local_time_edit->setText(d_tzmap->
	     convert(d_utc_time_edit->dateTime()).toString(Qt::ISODate));
}


void MainWidget::resizeEvent(QResizeEvent *e)
{
  int w=width();
  int h=height();
  int ypos=2;

  d_zonedir_label->setGeometry(10,ypos,130,20);
  d_zonedir_edit->setGeometry(145,ypos,w-155,20);
  ypos+=25;

  d_tzid_label->setGeometry(10,ypos,130,20);
  d_tzid_box->setGeometry(145,ypos,w-155,20);
  ypos+=25;

  d_utc_time_label->setGeometry(10,ypos,130,20);
  d_utc_time_edit->setGeometry(145,ypos,w-155,20);
  ypos+=25;

  d_local_time_label->setGeometry(10,ypos,130,20);
  d_local_time_edit->setGeometry(145,ypos,w-155,20);
  ypos+=25;

  d_apply_button->setGeometry(10,h-45,w-20,30);
}


void MainWidget::ReadDir(const QString &dir_name,QStringList *files) const
{
  QDir dir(dir_name);
  QStringList dir_names;
  QStringList file_names;

  //
  // Directories
  //
  dir_names=dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot);
  for(int i=0;i<dir_names.size();i++) {
    ReadDir(dir_name+"/"+dir_names.at(i),files);
  }

  //
  // Files
  //
  QString path=dir_name;
  path.replace(d_zonedir_edit->text(),"");
  file_names=dir.entryList(QDir::Files);
  for(int i=0;i<file_names.size();i++) {
    files->push_back(path+"/"+file_names.at(i));
    files->back()=files->back().right(files->back().length()-1);
  }
}


int main(int argc,char *argv[])
{
  QApplication a(argc,argv);

  MainWidget *w=new MainWidget();
  w->show();
  return a.exec();
}
