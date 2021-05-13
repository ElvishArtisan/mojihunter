// fonthunter5.cpp
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

#include <stdio.h>
#include <stdlib.h>

#include <QApplication>
#include <QFontInfo>
#include <QLabel>
#include <QResizeEvent>
#include <QStringList>

#include "fonthunter5.h"

MainWidget::MainWidget(QWidget *parent)
  : QWidget(parent)
{
  //
  // Create Fonts
  //
  QFont label_font(font().family(),font().pointSize(),QFont::Bold);

  //
  // Set Window Title
  //
  setWindowTitle(tr("FontHunter - Qt5"));
  setMinimumSize(sizeHint());

  //
  // Family
  //
  font_family_label=new QLabel(tr("Family")+":",this);
  font_family_label->setFont(label_font);
  font_family_label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
  font_family_edit=new QLineEdit(this);
  font_family_edit->setText(font().family());

  //
  // Size
  //
  font_size_label=new QLabel(tr("Size")+":",this);
  font_size_label->setFont(label_font);
  font_size_label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
  font_size_spin=new QSpinBox(this);
  font_size_spin->setRange(2,200);
  font_size_spin->setValue(font().pointSize());

  //
  // Weight
  //
  font_weight_label=new QLabel(tr("Weight")+":",this);
  font_weight_label->setFont(label_font);
  font_weight_label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
  font_weight_box=new QComboBox(this);

  font_weights.push_back(QFont::Light);
  font_weight_names.push_back(tr("Light"));
  font_weight_box->insertItem(font_weight_box->count(),tr("Light"));

  font_weights.push_back(QFont::Normal);
  font_weight_names.push_back(tr("Normal"));
  font_weight_box->insertItem(font_weight_box->count(),tr("Normal"));

  font_weights.push_back(QFont::DemiBold);
  font_weight_names.push_back(tr("DemiBold"));
  font_weight_box->insertItem(font_weight_box->count(),tr("DemiBold"));

  font_weights.push_back(QFont::Bold);
  font_weight_names.push_back(tr("Bold"));
  font_weight_box->insertItem(font_weight_box->count(),tr("Bold"));

  font_weights.push_back(QFont::Black);
  font_weight_names.push_back(tr("Black"));
  font_weight_box->insertItem(font_weight_box->count(),tr("Black"));

  for(unsigned i=0;i<font_weights.size();i++) {
    if(font_weights.at(i)>=font().weight()) {
      font_weight_box->setCurrentIndex(i);
      break;
    }
  }

  //
  // Italic
  //
  font_italic_label=new QLabel(tr("Italicize")+":",this);
  font_italic_label->setFont(label_font);
  font_italic_label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
  font_italic_box=new QComboBox(this);
  font_italic_box->insertItem(0,tr("No"));
  font_italic_box->insertItem(1,tr("Yes"));

  //
  // Apply Button
  //
  font_apply_button=new QPushButton(tr("Apply"),this);
  font_apply_button->setFont(label_font);
  connect(font_apply_button,SIGNAL(clicked()),this,SLOT(applyData()));

  //
  // Metric Value Outputs
  //
  font_metric_exact_match_label=new QLabel(tr("Exact Match")+":",this);
  font_metric_exact_match_label->setFont(label_font);
  font_metric_exact_match_label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
  font_metric_exact_match_value=new QLabel(this);
  font_metric_exact_match_value->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

  font_metric_family_label=new QLabel(tr("Family")+":",this);
  font_metric_family_label->setFont(label_font);
  font_metric_family_label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
  font_metric_family_value=new QLabel(this);
  font_metric_family_value->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

  font_metric_size_label=new QLabel(tr("Point Size")+":",this);
  font_metric_size_label->setFont(label_font);
  font_metric_size_label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
  font_metric_size_value=new QLabel(this);
  font_metric_size_value->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

  font_metric_weight_label=new QLabel(tr("Weight")+":",this);
  font_metric_weight_label->setFont(label_font);
  font_metric_weight_label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
  font_metric_weight_value=new QLabel(this);
  font_metric_weight_value->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

  font_metric_bold_label=new QLabel(tr("Is Bold")+":",this);
  font_metric_bold_label->setFont(label_font);
  font_metric_bold_label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
  font_metric_bold_value=new QLabel(this);
  font_metric_bold_value->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

  font_metric_italic_label=new QLabel(tr("Is Italicized")+":",this);
  font_metric_italic_label->setFont(label_font);
  font_metric_italic_label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
  font_metric_italic_value=new QLabel(this);
  font_metric_italic_value->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

  //
  // Samples
  //
  font_sample_label_label=new QLabel("QLabel",this);
  font_sample_label_label->setFont(label_font);
  font_sample_label_label->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
  font_sample_label=new QLabel(this);
  font_sample_label->setFrameStyle(QFrame::Box|QFrame::Plain);
  font_sample_label->setLineWidth(1);

  font_sample_edit_label=new QLabel("QLineEdit",this);
  font_sample_edit_label->setFont(label_font);
  font_sample_edit_label->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
  font_sample_edit=new QLineEdit(this);
  connect(font_sample_edit,SIGNAL(textChanged(const QString &)),
	  font_sample_label,SLOT(setText(const QString &)));

  font_sample_textedit_label=new QLabel("QTextEdit",this);
  font_sample_textedit_label->setFont(label_font);
  font_sample_textedit_label->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
  font_sample_textedit=new QTextEdit(this);
  font_sample_textedit->setAcceptRichText(true);

  applyData();
}


QSize MainWidget::sizeHint() const
{
  return QSize(400,622);
}


void MainWidget::applyData()
{
  QFont test_font(font_family_edit->text(),font_size_spin->value(),
		  font_weights.at(font_weight_box->currentIndex()),
		  font_italic_box->currentIndex());
  QFontInfo fi(test_font);

  if(fi.exactMatch()) {
    font_metric_exact_match_value->setText(tr("True"));
  }
  else {
    font_metric_exact_match_value->setText(tr("False"));
  }
  font_metric_family_value->setText(fi.family());
  font_metric_size_value->setText(QString().sprintf("%d",fi.pointSize()));
  QString name="";
  for(unsigned i=0;i<font_weights.size();i++) {
    if(fi.weight()==font_weights.at(i)) {
      name=font_weight_names[i];
    }
  }
  if(name.isEmpty()) {
    font_metric_weight_value->setText(QString().sprintf("%d",fi.weight()));
  }
  else {
    font_metric_weight_value->setText(name);
  }
  if(fi.bold()) {
    font_metric_bold_value->setText(tr("True"));
  }
  else {
    font_metric_bold_value->setText(tr("False"));
  }
  if(fi.italic()) {
    font_metric_italic_value->setText(tr("True"));
  }
  else {
    font_metric_italic_value->setText(tr("False"));
  }

  font_sample_label->setFont(test_font);
  font_sample_edit->setFont(test_font);
  font_sample_textedit->setFont(test_font);

  resizeEvent(NULL);
}


void MainWidget::resizeEvent(QResizeEvent *e)
{
  int w=width();

  font_family_label->setGeometry(10,2,100,30);
  font_family_edit->setGeometry(115,2,w-125,30);

  font_size_label->setGeometry(10,37,100,30);
  font_size_spin->setGeometry(115,37,w-125,30);

  font_weight_label->setGeometry(10,72,100,30);
  font_weight_box->setGeometry(115,72,w-125,30);

  font_italic_label->setGeometry(10,107,100,30);
  font_italic_box->setGeometry(115,107,60,30);

  font_apply_button->setGeometry(10,142,w-20,40);

  font_metric_exact_match_label->setGeometry(10,190,100,20);
  font_metric_exact_match_value->setGeometry(115,190,w-20,20);

  font_metric_family_label->setGeometry(10,215,100,20);
  font_metric_family_value->setGeometry(115,215,w-20,20);

  font_metric_size_label->setGeometry(10,240,100,20);
  font_metric_size_value->setGeometry(115,240,w-20,20);

  font_metric_weight_label->setGeometry(10,265,100,20);
  font_metric_weight_value->setGeometry(115,265,w-20,20);

  font_metric_bold_label->setGeometry(10,290,100,20);
  font_metric_bold_value->setGeometry(115,290,w-20,20);

  font_metric_italic_label->setGeometry(10,315,100,20);
  font_metric_italic_value->setGeometry(115,315,w-20,20);

  QFont test_font=font_sample_label->font();
  int ypos=350;

  font_sample_label_label->setGeometry(20,ypos,w-30,20);
  ypos+=20;
  font_sample_label->setGeometry(10,ypos,w-20,3*test_font.pointSize());
  ypos+=3*test_font.pointSize()+20;

  font_sample_edit_label->setGeometry(20,ypos,w-30,20);
  ypos+=20;
  font_sample_edit->setGeometry(10,ypos,w-20,3*test_font.pointSize());
  ypos+=3*test_font.pointSize()+20;

  font_sample_textedit_label->setGeometry(20,ypos,w-30,20);
  ypos+=20;
  font_sample_textedit->setGeometry(10,ypos,w-20,10*test_font.pointSize());
  ypos+=10*test_font.pointSize()+20;
}


int main(int argc,char *argv[])
{
  QApplication a(argc,argv);

  MainWidget *w=new MainWidget();
  w->show();
  return a.exec();
}
