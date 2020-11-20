/****************************************Copyright (c)****************************************************
**
**                     DaHao Info Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name: setwid.cpp
** Latest Version: V0.0.1
** Latest modified Date:  2019-01-23
** Modified by:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by: BitYang
** Created date: 2019-01-23
** Descriptions: the main setting wid
**
*********************************************************************************************************/
#include "setwid.h"
#include "ui_setwid.h"
#include "softbus.h"
#include <QKeyEvent>
#include "remoteinterface.h"

setwid::setwid(PPLTPRESTATE psys, PPSTATEPARAM pplt, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::setwid)
{
  ui->setupUi(this);
  //this->setCursor(Qt::BlankCursor);
  recoversys = psys;
  recoverplt = pplt;
  recoversys->powerstate = recoverplt->pltpres.powerstate;
  LoadAllSetwid(recoverplt->syssetindex);
  setAttribute(Qt::WA_DeleteOnClose);
  this->setWindowModality(Qt::NonModal);// ApplicationModal);
  this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

  this->setGeometry(mapToGlobal(QPoint(0,0)).x(),mapToGlobal(QPoint(0,0)).y(),this->width(),this->height() - MMD);
}

setwid::~setwid()
{  
  QObject::disconnect(bitsetbtngroup,SIGNAL(buttonClicked(int)),this,SLOT(buttonGroupClicked(qint32)));
  delete pcomsetwid;
  delete pdedtsetwid;
  delete pnetsetwid;
  delete plicmanwid;
  delete pfilemanaowid;
  delete psyswid;
  delete bitsetbtngroup;
  delete ui;
}

/**
 * @brief load all set wids
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-01-23;c02-25;c05-20}
*/
void setwid::LoadAllSetwid(qint32 iIndex)
{    
  lastsetindex = iIndex;
  pcomsetwid = new comset(this);
  pcomsetwid->GetDisModeExt(&recoverplt->dismod);
  pcomsetwid->SetRefBtnCheck(&recoverplt->freqref);
  QThread::msleep(PLTQUERY);
  pcomsetwid->SetPowerBtnCheck(&recoversys->powerstate);
  pcomsetwid->SetLangBtnCheck(&recoverplt->lantype);
  pcomsetwid->GetNowAnaMode(&recoverplt->orimode);
  pcomsetwid->setGeometry(SMX,SMY,SMW,SMH);
  pcomsetwid->hide();
  setwidvec.append(pcomsetwid);

  setwidvec.append(pdedtsetwid);
  pnetsetwid = new networkset(this);

#ifdef _linux_238_netctrl
  pnetsetwid->SetGpsBtn(&recoverplt->gpswitch);
  pnetsetwid->SetPortBtn(&recoverplt->lanport);
  pnetsetwid->SetIpBtn(recoverplt->ipstr);
  pnetsetwid->SetMaskBtn(recoverplt->maskstr);
  pnetsetwid->SetGateBtn(recoverplt->gatewaystr);
  pnetsetwid->SetRemoteBtn(&recoverplt->remoteintertype);
  //pnetsetwid->SetWifiSwitchBtn(&recoverplt->wifiswitch);
  recoverplt->wifiswitch = 0;
  pnetsetwid->SetWifiSwitchBtn(&recoverplt->wifiswitch); //default off.If it is turned on, it will take a long time and affect the startup time.
  QThread::msleep(PLTQUERY);
  pnetsetwid->SetWifiMibBtn(recoverplt->wifimib);
  QThread::msleep(PLTQUERY);
  pnetsetwid->SetBltSwitchBtn(&recoverplt->bluetswitch);
  QThread::msleep(PLTQUERY);
  pnetsetwid->setGeometry(SMX,SMY,SMW,SMH);
#endif
  pnetsetwid->hide();
  setwidvec.append(pnetsetwid);

  plicmanwid = new licemana(this);
  plicmanwid->setGeometry(SMX,SMY,SMW,SMH);
  plicmanwid->SetTemperSysinfo();
  plicmanwid->hide();
  setwidvec.append(plicmanwid);

  pfilemanaowid = new filemana(this);
  pfilemanaowid->GetNowAnaMode(&recoverplt->orimode);
  pfilemanaowid->GetDisMode(&recoverplt->dismod);
  pfilemanaowid->setGeometry(SMX,SMY,SMW,SMH);
  pfilemanaowid->hide();
  setwidvec.append(pfilemanaowid);

  psyswid = new sysinfo(this);
  psyswid->setGeometry(SMX,SMY,SMW,SMH);
  psyswid->RefleshVerDate(remoteinterface::getplatformremotehandle()->GetDMsgHandle());
  psyswid->RefreshVerMsg0();
  psyswid->hide();
  setwidvec.append(psyswid); 

  pdedtsetwid = new dsdtset(this);
  pdedtsetwid->SetSleepBtnCheck(&recoverplt->sleept);
  pdedtsetwid->SetDisBtnCheck(&recoverplt->dismod);
  pdedtsetwid->SetLcdBtn(&recoverplt->lcdbright);
  QThread::msleep(PLTQUERY);
  pdedtsetwid->SetDateBtnCheck(&recoverplt->datetype);
  pdedtsetwid->SetSoundBtn(&recoverplt->soundnum);
  pdedtsetwid->SetSoundSwitchBtn(&recoverplt->soundswitch);
  QThread::msleep(PLTQUERY);
  pdedtsetwid->SetKeybeepBtn(&recoverplt->gkeybeepswitch);
  QThread::msleep(PLTQUERY);
  pdedtsetwid->setGeometry(SMX,SMY,SMW,SMH);
  pdedtsetwid->hide();
  setwidvec.replace(PTY1,pdedtsetwid);
  psyswid->RefreshVerMsg1();

  setwidvec.at(iIndex)->show();
  bitsetbtngroup = new QButtonGroup(this);
  bitsetbtngroup->addButton(ui->pushButton,COM_SET);
  bitsetbtngroup->addButton(ui->pushButton_2,DSDT_SET);
  bitsetbtngroup->addButton(ui->pushButton_3,NETWORK_SET);
  bitsetbtngroup->addButton(ui->pushButton_4,LICE_SET);
  bitsetbtngroup->addButton(ui->pushButton_5,HSW_SET);
  bitsetbtngroup->addButton(ui->pushButton_6,SYS_SET);
  QObject::connect(bitsetbtngroup,SIGNAL(buttonClicked(int)),this,SLOT(buttonGroupClicked(qint32)));
  bitsetbtngroup->button(iIndex)->setChecked(true);
  psyswid->RefreshVerMsg2();

  if(recoverplt->dismod)
    {
      SetPltSysDisM(recoverplt->dismod);
      remoteinterface::getplatformremotehandle()->PltSetDisMod(recoverplt->dismod);
    }
  return;
}

void setwid::on_clobtn_clicked()
{
  this->hide();
  return;
}

void setwid::buttonGroupClicked(qint32 idIndex)
{
  setwidvec.at(lastsetindex)->hide();
  lastsetindex = idIndex;
  setwidvec.at(lastsetindex)->show();
  if(LICE_SET == lastsetindex)
    {
//      plicmanwid->OutTest();
    }
  else if(SYS_SET == lastsetindex)
    {
      psyswid->Flszsb();
    }
  recoverplt->syssetindex = lastsetindex;
  return;
}

/**
 * @brief this call by plt label
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-08-15}
*/
void setwid::LabCli(qint32 iIndex)
{
  bitsetbtngroup->button(iIndex)->setChecked(true);
  emit bitsetbtngroup->buttonClicked(iIndex);
  return;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note will include all sys setting chidl widget
 * @since {2019-09-03}
*/
void setwid::SetPltSysDisM(qint32 imod)
{
  if(imod < PLT_INDOOR || imod >= PLT_DNONE)
    return;
  imod = imod == PTY1 ? PTY0 : imod;
  this->setProperty("pltdismode",pltdismod[imod]);
  if(pcomsetwid)
    {
      pcomsetwid->setProperty("pltdismode",pltdismod[imod]);
    }
  if(pdedtsetwid)
    {
      pdedtsetwid->setProperty("pltdismode",pltdismod[imod]);
      pdedtsetwid->SetPluginProperty("pltdismode",pltdismod[imod]);
    }
  if(pnetsetwid)
    {
      pnetsetwid->setProperty("pltdismode",pltdismod[imod]);
      pnetsetwid->SetPluginProperty("pltdismode",pltdismod[imod]);
    }
  if(plicmanwid)
    {
      plicmanwid->setProperty("pltdismode",pltdismod[imod]);
    }
  if(pfilemanaowid)
    {
      pfilemanaowid->setProperty("pltdismode",pltdismod[imod]);
    }
  if(psyswid)
    {
      psyswid->setProperty("pltdismode",pltdismod[imod]);
    }
  setStyle(QApplication::style());
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-07-03}
*/
void setwid::DisToHide()
{
  on_clobtn_clicked();
}

void setwid::keyPressEvent(QKeyEvent *event)
{
  if(Qt::Key_Escape == event->key())
    {
      on_clobtn_clicked();
    }
  else if(Qt::Key_PowerOff == event->key())
    {
      QApplication::sendEvent(remoteinterface::getplatformremotehandle(),event);
    }
  else if(Qt::Key_Shift == event->key())
    {      
      QApplication::sendEvent(remoteinterface::getplatformremotehandle(),event);
      on_clobtn_clicked();
    }
  return;
}


