/****************************************Copyright (c)****************************************************
**
**                     DaHao Info Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:
** Latest Version: V0.0.1
** Latest modified Date:  2019-06-10
** Modified by:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by: BitYang
** Created date: 2019-06-10
** Descriptions:for debug need mib
**
*********************************************************************************************************/
#include "debugdia.h"
#include "ui_debugdia.h"
#include "remoteinterface.h"
//#include "shmengine.h"

debugdia::debugdia(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::debugdia)
{
  ui->setupUi(this);  
  this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
  ui->spinBox->setFocus();
  calcloseflag = 0;
}

debugdia::~debugdia()
{
  delete ui;
}

void debugdia::on_pushButton_clicked()
{
  debugmsgH->qsoci = ui->spinBox->value();
//  shmengine::getsingleshm()->pshm_sysconf->PSFreqVol = ui->spinBox->value();
//  shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_FreqCalc);
}

void debugdia::on_pushButton_15_clicked()
{
  this->close();
}

void debugdia::keyPressEvent(QKeyEvent *event)
{  
  if(Qt::Key_PowerOff == event->key())
    {
      QApplication::sendEvent(remoteinterface::getplatformremotehandle(),event);
    }
  else if(Qt::Key_Escape == event->key())
    {
      on_pushButton_15_clicked();
    }
}

qint32 debugdia::GetCalcCloseFlag()
{
  return calcloseflag;
}

void debugdia::RefleshStates(PDEVEMSG pHandle)
{
  debugmsgH = pHandle;
  this->ui->spinBox->setValue(debugmsgH->qsoci);
}

void debugdia::on_pushButton_2_clicked()
{
  calcloseflag = 1;
  this->close();
}
