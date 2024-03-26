// timezonehunter4.h
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

#ifndef TIMEZONEHUNTER4_H
#define TIMEZONEHUNTER4_H

#include <QComboBox>
#include <QDateTimeEdit>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QResizeEvent>
#include <QSize>

#include "tzmap.h"

#define TIMEZONEHUNTER_MODNAME "timezonehunter"
#define TIMEZONEHUNTER_USAGE "[--tzid=<tz-id>]\n"

class MainWidget : public QWidget
{
  Q_OBJECT
 public:
  MainWidget(QWidget *parent=0);
  QSize sizeHint() const;

 private slots:
  void zonedirChangedData(const QString &dirname);
  void tzidActivatedData(const QString &tzid);
  void utcChangedData(const QDateTime &dt);
  void applyData();

 protected:
  void resizeEvent(QResizeEvent *e);

 private:
  void ReadDir(const QString &dir_name,QStringList *files) const;

  QLabel *d_zonedir_label;
  QLineEdit *d_zonedir_edit;

  QLabel *d_tzid_label;
  QComboBox *d_tzid_box;

  QLabel *d_utc_time_label;
  QDateTimeEdit *d_utc_time_edit;

  QLabel *d_local_time_label;
  QLineEdit *d_local_time_edit;

  QLabel *d_offset_label;
  QLineEdit *d_offset_edit;

  QLabel *d_isdup_label;
  QLineEdit *d_isdup_edit;

  QPushButton *d_apply_button;

  TzMap *d_tzmap;
  QString d_initial_tzid;
};


#endif  // TIMEZONEHUNTER4_H
