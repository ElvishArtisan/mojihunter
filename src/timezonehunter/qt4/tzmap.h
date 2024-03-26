// tzmap.h
//
// Map a timezone definition file from the TZ database.
//
//   (C) Copyright 2018 Fred Gleason <fredg@paravelsystems.com>
//
//   All Rights Reserved.
//

#ifndef TZMAP_H
#define TZMAP_H

#include <stdint.h>

#include <QDateTime>
#include <QString>
#include <QStringList>

class TzType
{
 public:
  TzType(const QDateTime &start_datetime);
  QDateTime startDateTime() const;
  int64_t offset() const;
  void setOffset(int64_t msec);
  QString name() const;
  void setName(const QString &str);
  QString dump() const;

 private:
  QDateTime tzt_start_datetime;
  int64_t tzt_offset;
  QString tzt_name;
};




class TzMap
{
 public:
  TzMap();
  QString name() const;
  QDateTime convert(const QDateTime &utc,QString *tz_name=NULL,
		    int *offset_secs=NULL,bool *is_dup=NULL) const;
  bool load(const QString &filename,bool dump=false);
  static QString dumpDateTime(const QDateTime &dt);
  static QString timeSpecString(Qt::TimeSpec spec);
  static int utcOffset(const QDateTime &lcl,const QDateTime &utc);

 private:
  void ReadVersion0Block(int fd,bool dump);
  void ReadVersion2Block(int fd,bool dump);
  QDateTime DateTimeFromTimeT(int64_t time) const;
  uint32_t ReadUnsigned(int fd) const;
  int32_t ReadSigned(int fd) const;
  int64_t ReadLongSigned(int fd) const;
  uint8_t ReadByte(int fd) const;
  QStringList ReadStrings(int fd);
  uint64_t ntohll(uint64_t lword) const;
  QList<TzType *> tzh_types;
  QString tzh_name;
};


#endif  // TZMAP_H
