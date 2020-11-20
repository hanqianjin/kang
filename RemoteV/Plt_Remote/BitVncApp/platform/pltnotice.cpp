/****************************************Copyright (c)****************************************************
**
**                     DaHao Info Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:
** Latest Version: V0.0.1
** Latest modified Date:  2019-05-22
** Modified by:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by: BitYang
** Created date: 2019-05-22
** Descriptions:
**
*********************************************************************************************************/
#include "pltnotice.h"
#include "ui_pltnotice.h"
#include "softbus.h"
#include "remoteinterface.h"

pltnotice::pltnotice(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::pltnotice)
{
  ui->setupUi(this);    
  this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
}

/**
 * @brief
 * @param[in]istyle PTY0 reflesh USER;PTY1 zero calc;PTY2 freqcalc debug ui need code;
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-06-10}
*/
pltnotice::pltnotice(qint32 itype,qint32 istyle,QWidget *parent):
  QDialog(parent),
  eyestate(PTY0),
  ui(new Ui::pltnotice)
{
  ui->setupUi(this);
  btnstate = 0;
  pltnot.itype = itype;
  pltnot.istyle = istyle; 
  this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);  
  ui->lineEdit->hide();
  ui->label_2->hide(); 
  ui->pushButton->hide();
  //zero calc
  if(PTY1 == pltnot.istyle)
    {
      if(PTY0 == pltnot.itype)
        {
          ui->Warning->setText("Press \"Cancel\" to quit zero calc");
          ui->pushButtonok->hide();
          ui->pushButtoncancel->move(440,118);
          //call sa interfaced avoid hung
          QTimer::singleShot(PLTQUERY,remoteinterface::getsaremotehandle()->pcontrolInterface,SLOT(setBeginZeroRestrainCal()));
        }
      else
        {
          ui->Warning->setText("Please convert to Spectrum Analyse mode first");
          ui->pushButtoncancel->hide();
        }
    }
  //freq calc mib input
  else if(PTY2 == pltnot.istyle)
    {
      ui->Warning->setText("password");
      ui->lineEdit->show();
      ui->Title->setText("Please Enter Password");
      ui->lineEdit->setFocus();
      ui->pushButton->show();
    }  
}

pltnotice::~pltnotice()
{
  delete ui;
}

/**
 * @brief get ok or cancel state
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-05-22}
*/
qint32 pltnotice::GetSelectState()
{
  return btnstate;
}

/**
 * @brief when finish or stop zero calc
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-06-10}
*/
void pltnotice::StopZeroCalc(bool bl)
{
  btnstate = 0;  
  this->close();
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-09-12}
*/
void pltnotice::SetNoticDisMode(qint32 imod)
{
  dismode = imod;
  imod = imod == PTY1 ? PTY0 : imod;
  this->setProperty("pltdismode",pltdismod[imod]);
  setStyle(QApplication::style());
  if(eyestate)
    {
      ui->lineEdit->setEchoMode(QLineEdit::Normal);
      SetEyeOpenDisM();
    }
  else
    {
      ui->lineEdit->setEchoMode(QLineEdit::Password);
      SetEyeCloseDisM();
    }
}

void pltnotice::on_pushButtoncancel_clicked()
{
  btnstate = 0;
  if(PTY1 == pltnot.istyle)
    {
      if(PTY0 == pltnot.itype)
        {
          //call sa interface to cancel zero calc
          remoteinterface::getsaremotehandle()->pcontrolInterface->setZeroRestrainCalStop();         
        }
    }
  this->close();
}

void pltnotice::on_pushButtonok_clicked()
{
  btnstate = 1;
  if(PTY2 == pltnot.istyle)
    {
      if(110201 == ui->lineEdit->text().toInt()){}
      else
        {
          ui->label_2->show();
          ui->lineEdit->selectAll();
          ui->lineEdit->setFocus();
          return;
        }
    }
  this->close();
}

void pltnotice::keyPressEvent(QKeyEvent *event)
{  
  if(Qt::Key_PowerOff == event->key())
    {
      QApplication::sendEvent(remoteinterface::getplatformremotehandle(),event);
    }
  else if(Qt::Key_Escape == event->key())
    {
      on_pushButtoncancel_clicked();
    }
  else if(Qt::Key_Shift == event->key())
    {
      QApplication::sendEvent(remoteinterface::getplatformremotehandle(),event);
      on_pushButtoncancel_clicked();
    }
}

void pltnotice::on_lineEdit_returnPressed()
{
    on_pushButtonok_clicked();
}

void pltnotice::on_pushButton_clicked()
{
  if(!eyestate)
    {
      ui->lineEdit->setEchoMode(QLineEdit::Normal);
      eyestate = PTY1;
      SetEyeOpenDisM();
    }
  else
    {
      ui->lineEdit->setEchoMode(QLineEdit::Password);
      eyestate = PTY0;
      SetEyeCloseDisM();
    }
}

void pltnotice::SetEyeOpenDisM()
{
  QString mstr = "#pltnotice[pltdismode=\"indoor\"] ";
  QString qstr = QString("QPushButton{border-image: url(:/bit/image/eyeopen.png);border-style: flat;\
                         background-color: transparent;}\n");
QString mstr1 = "#pltnotice[pltdismode=\"night\"] ";
QString qstr1 = QString("QPushButton{border-image: url(:/bit/image/eyeopen_night.png);border-style: flat;\
                        background-color: transparent;}\n");
ui->pushButton->setStyleSheet(mstr + qstr + mstr1 + qstr1);
return;
}

void pltnotice::SetEyeCloseDisM()
{
  QString mstr = "#pltnotice[pltdismode=\"indoor\"] ";
  QString qstr = QString("QPushButton{border-image: url(:/bit/image/eyeclose.png);border-style: flat;\
                         background-color: transparent;}\n");
QString mstr1 = "#pltnotice[pltdismode=\"night\"] ";
QString qstr1 = QString("QPushButton{border-image: url(:/bit/image/eyeclose_night.png);border-style: flat;\
                        background-color: transparent;}\n");
ui->pushButton->setStyleSheet(mstr + qstr + mstr1 + qstr1);
return;
}
