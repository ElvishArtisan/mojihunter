// fonthunter5.h
//
// A utility for testing fonts.
//
//   (C) Copyright 2019 Fred Gleason <fredg@paravelsystems.com>
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

#ifndef FONTHUNTER5_H
#define FONTHUNTER5_H

#include <vector>

#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QResizeEvent>
#include <QSize>
#include <QSpinBox>
#include <QTextEdit>
#include <QWidget>

class MainWidget : public QWidget
{
  Q_OBJECT
 public:
  MainWidget(QWidget *parent=0);
  QSize sizeHint() const;

 private slots:
  void applyData();

 protected:
  void resizeEvent(QResizeEvent *e);

 private:
  QLabel *font_family_label;
  QLineEdit *font_family_edit;
  QLabel *font_size_label;
  QSpinBox *font_size_spin;
  QLabel *font_weight_label;
  QComboBox *font_weight_box;
  std::vector<QFont::Weight> font_weights;
  QStringList font_weight_names;
  QLabel *font_italic_label;
  QComboBox *font_italic_box;


  QPushButton *font_apply_button;

  QLabel *font_metric_exact_match_label;
  QLabel *font_metric_exact_match_value;

  QLabel *font_metric_family_label;
  QLabel *font_metric_family_value;

  QLabel *font_metric_size_label;
  QLabel *font_metric_size_value;

  QLabel *font_metric_weight_label;
  QLabel *font_metric_weight_value;

  QLabel *font_metric_bold_label;
  QLabel *font_metric_bold_value;

  QLabel *font_metric_italic_label;
  QLabel *font_metric_italic_value;


  QLabel *font_sample_label_label;
  QLabel *font_sample_label;
  QLabel *font_sample_edit_label;
  QLineEdit *font_sample_edit;
  QLabel *font_sample_textedit_label;
  QTextEdit *font_sample_textedit;
};


#endif  // FONTHUNTER5_H
