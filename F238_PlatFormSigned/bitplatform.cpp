/****************************************Copyright (c)****************************************************
**
**                     DaHao Info Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:bitplatform.cpp
** Latest Version: V1.0.0
** Latest modified Date:  2018-12-21
** Modified by:steve
** Descriptions:achieve the first V
**
**--------------------------------------------------------------------------------------------------------
** Created by: BitYang
** Created date: 2018-12-12
** Descriptions:main widget associated class
**
*********************************************************************************************************/
#include "bitplatform.h"
#include "ui_bitplatform.h"
#include "shmengine.h"
#include <QDateTime>
#include <QDebug>
#include <qapplication.h>
#include <QTextStream>
#include "remoteinterface.h"
#include "scpidef/scpidef.h"
#include <unistd.h>

quint32 BitPlatForm::modesumnum = NONEMODE;
QFile BitPlatForm::logfile("gui.log");
//UNDO 20181227
/* the device start up to recover last running state,
 * but saving action is finished by different ana mode,
 * so the data type should be same,to avoid conflict,
 * maybe use qsql better;
 */
BitPlatForm::BitPlatForm(QWidget *parent) :  
  QMainWindow(parent),
  lcf (PON),
  ncf (POFF),
  lncf (PON),
  nncf(POFF),
  BURN_STATE(PON),
  timerstate(POFF),
  nowshowmodsum(UIMODMAXNUM),
  orimode(SA_MODE),
  batnum(BATTARYINI),
  ui(new Ui::BitPlatForm)
{
  ui->setupUi(this);
  SetIniQss();
  qInstallMessageHandler(BitPlatForm::bitRedirectHandler);

  if(!BitPlatForm::logfile.open(QIODevice::Append))
    {
      qCritical("open log file failed");
    }
  setWindowFlags(Qt::FramelessWindowHint);
  this->setGeometry(mapToGlobal(QPoint(0,0)).x(), +  mapToGlobal(QPoint(0,0)).y(),this->width(),this->height());

  Uphomeapp();
  InitP();
  if(LoadAllTimer() < 0)
    {
      //dealing expec
      qFatal("platform timer ini failed");
   }

  IniCtrlVec();
  ConnectAllSigSlot();
  StartCtrlApp(orimode);
  SCPI_Communicate_Init();
  qCritical("STARTING UP"); 
}

BitPlatForm::~BitPlatForm()
{
  ReleaseAllTimer();
  CloseCtrlApp(orimode);
  DeleteW();
  BitPlatForm::logfile.close();
  qInstallMessageHandler(0);
}

/**
 * @brief load process for all modes by RUNMODE order
 * @note [will extend by mode]
 * @author steve
 * @since {2018-12-21}
*/
void BitPlatForm::IniCtrlVec()
{
  nowmodebtn.append(ui->mode1btn);
  nowmodebtn.append(ui->mode2btn);
  nowmodebtn.append(ui->mode3btn);
  nowmodebtn.append(ui->mode4btn);

  clobtnvec.append(ui->chafir);
  clobtnvec.append(ui->chasec);
  clobtnvec.append(ui->chathird);
  clobtnvec.append(ui->chafourth);

  qint32 inum = nowmodebtn.size();
  qint32 i = 0;
  for(i = 0;i < inum;i++)
    {
      nowmodetext.append(nowmodebtn.at(i)->text());
    }

  pPlusDia = 0;
  pSetWid = 0;
  //for ctrl app standard output
  processvec.append(&sactrlprocess);
  processvec.at(SA_MODE)->setStandardOutputFile(ctrlstr.at(SA_MODE),QIODevice::Append);

  processvec.append(&rtsactrlprocess);
  processvec.at(RTSA_MODE)->setStandardOutputFile(ctrlstr.at(RTSA_MODE),QIODevice::Append);
  return;
}


/**
 * @brief start home app by platform not itself
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-01-09}
*/
void BitPlatForm::Uphomeapp()
{
  homeprocess.start("./HomeApp",QStringList("./HomeApp"));
  homeprocess.waitForStarted(CTRLUPOVERTIME);
  return;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note this part for update to close app need commu with home app
 * @author steve
 * @since {2019-01-09}
*/
void BitPlatForm::Downhomeapp()
{

}

/**
 * @brief accor with now four text
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-01-08}
*/
void BitPlatForm::FillConstText()
{
  qint32 inum = nowmodetext.size();
  qint32 i = 0;
  for(i = 0;i < inum;i++)
    {
      nowmodetext[i] = (nowmodebtn.at(i)->text());
    }
  return;
}

/**
 * @brief set mode ui by home and plus
 * @param[in]
 * @param[in]
 * @return when search from now mode btn return index,else -1
 * @note
 * @author steve
 * @since {2019-01-08:c01-17:c0124:c0125}
*/
qint32 BitPlatForm::NowModExitor(QString& modstr)
{
  QString tempstr = modstr.mid(INDEXBASE,modstr.indexOf('-') + 1);
  qint32 i = 0;
  qint32 iIndex = 0;
  qint32 iflag = 1;
  for(i = 0;i < nowshowmodsum - 1;i++)
    {
      QString istr = nowmodetext.at(i);
      if(istr.mid(INDEXBASE,istr.indexOf('-') + 1) == tempstr)
        {
          iIndex = i;
          iflag  = 0;
          break;
        }
    }
  if(iflag)
    {
      iIndex = -1;
    }
  return iIndex;
}

/**
 * @brief reflesh ui mode btn text
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-01-25}
*/
qint32 BitPlatForm::SetModBtntext(qint32 iIndex, QString &modstr)
{
  qint32 i = 0;
  if(iIndex < 0)
    {
      for(i = 0;i < nowshowmodsum - 1;i++)
        {
          nowmodebtn.at(nowshowmodsum - 1 - i) ->setText(nowmodebtn.at(nowshowmodsum - 2 - i)->text());
        }
      nowmodebtn.at(INDEXBASE)->setText(modstr);
    }
  else
    {
      for(i = 0; i < iIndex;i++)
        {
          nowmodebtn[iIndex - i]->setText(nowmodebtn[iIndex - 1 - i]->text());
        }
      nowmodebtn[INDEXBASE]->setText(modstr);
    }
  return iIndex;
}

void BitPlatForm::GetMeasitemsIndex(qint32 *iIndex)
{
  return;
}

/**
 * @brief for out call
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-02-13}
*/
void BitPlatForm::InnerTimeCtrl(qint32 tid)
{
  if(sysmsgtimerhandle == tid)
    {
      timerstr = QDateTime::currentDateTime().toString("yyyy-MM-dd   APhh:mm:ss");
      ui->timelabel->setText(timerstr);
    }
  if(modeswitchtimerhandle == tid)
    {
      if(shmengine::getsingleshm()->pshm_home->modesource)
        {
          if(orimode != shmengine::getsingleshm()->pshm_home->modetype)
            {
              qint32 iresult = HomeModeExistornot(shmengine::getsingleshm()->pshm_home->modetype);
              qint32 i = 0;
              if(iresult < 0)
                {
                  for(i = 0;i < nowshowmodsum - 1;i++)
                    {
                      nowmodebtn.at(nowshowmodsum - 1 - i) ->setText(nowmodebtn.at(nowshowmodsum - 2 - i)->text());
                    }
                  nowmodebtn.at(INDEXBASE)->setText(modbtntext[shmengine::getsingleshm()->pshm_home->modetype]
                      + modesmeasstr.at(shmengine::getsingleshm()->pshm_home->modetype));
                }
              else
                {
                  QString mstr = nowmodebtn.at(iresult)->text();
                  for(i = 0; i < iresult;i++)
                    {
                      nowmodebtn[iresult - i]->setText(nowmodebtn[iresult - 1 - i]->text());
                    }
                  nowmodebtn[INDEXBASE]->setText(mstr);
                }
              emit ModeSwitchSig(orimode);
              FillConstText();
            }
          shmengine::getsingleshm()->pshm_home->modesource = POFF;
        }
    }

  if(tempertimerhandle == tid)
    {
      if(BURN_STATE)
        {
          timerstate = PON;
          static qint32 nflf = -1;
          static qint32 nfnf = 0;
          shmengine::PassTrigToSys(PLT_IXT_System_Info,PLT_IXS_BatteryInfoAll);
          switch (shmengine::getsingleshm()->pshm_sysinfo->BatterChargeStatus)
            {
            case UN_BATT:
              nfnf = UN_BATT;
              if(nflf != nfnf)
                {
                  NoBatteryCtrl();
                  nflf = nfnf;
                }
              break;
            case BATT_CHARGE:
              nfnf = BATT_CHARGE;
              ChargeStateCtrl();
              break;
            case BATT_DISCHARGE:
              nfnf = BATT_DISCHARGE;
              DisChargeStateCtrl();
              break;
            case BATT_FULL:
              nfnf = BATT_FULL;
              if(nflf != nfnf)
                {
                  FullBatteryCtrl();
                  nflf = nfnf;
                }
              break;
            default:
              break;
            }
        }
      timerstate = POFF;
    }
  return;
}

/**
 * @brief for without battery ctrl
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-02-13}
*/
void BitPlatForm::NoBatteryCtrl()
{
  ui->batpiclabel->setPixmap(QPixmap(QString::fromUtf8(NOBATPIC[INDEXBASE])));
  return;
}

/**
 * @brief for charge state to cut picture
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-02-13:c02-14}
*/
void BitPlatForm::ChargeStateCtrl()
{
  lncf = -1;
  nncf = 0;
  batnum = shmengine::getsingleshm()->pshm_sysinfo->BatteryRemaind;
  batnum = batnum > 100 ? 100 : batnum;
  qint32 ilen = sizeof(CHARGEREMAIN) / sizeof(quint32);
  qint32 iunit = ilen - 1;
  qint32 i = 0;
  for(i = 0;i < ilen;i++)
    {
      if(batnum < CHARGEREMAIN[i])
        {
          iunit = i;
          ncf = i;
          break;
        }
    }
  if(lcf != ncf)
    {
      ui->batpiclabel->setPixmap(QPixmap(QString::fromUtf8(CHARGEPIC[iunit])));
      lcf = ncf;
    }
  batterystr = QString::number(batnum) + "%";
  ui->batterylabel->setText(batterystr);
  return;
}

/**
 * @brief for discharge state to cut picture
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-02-13:c02-14}
*/
void BitPlatForm::DisChargeStateCtrl()
{  
  lcf = -1;
  ncf = 0;
  batnum = shmengine::getsingleshm()->pshm_sysinfo->BatteryRemaind;
  batnum = batnum > 100 ? 100 : batnum;
  qint32 iunit = 0;
  qint32 ilen = sizeof(DISCHARGEREMIAN) / sizeof(quint32);
  qint32 i = 0;
  for(i = ilen - 1;i >= 0;i--)
    {
      if(batnum > DISCHARGEREMIAN[i])
        {
          iunit = i;
          nncf = i;
          break;
        }
    }
  if(lncf != nncf)
    {
      ui->batpiclabel->setPixmap(QPixmap(QString::fromUtf8(DISCHARGEPIC[iunit])));
      lncf = nncf;
    }
  batterystr = QString::number(batnum) + "%";
  ui->batterylabel->setText(batterystr);
  return;
}

/**
 * @brief for full state ctrl
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-02-13}
*/
void BitPlatForm::FullBatteryCtrl()
{
  ui->batpiclabel->setPixmap(QPixmap(QString::fromUtf8(FULLPIC[INDEXBASE])));
  return;
}

void BitPlatForm::timerEvent(QTimerEvent *event)
{  
  return InnerTimeCtrl(event->timerId());
}

/**
 * @brief setting platform ini qss
 * @note
 * @author steve
 * @since {2019-01-04:c0125}
*/
void BitPlatForm::SetIniQss()
{   
  modestr << "SA-Spectrum" << "RTSA-Persist Spectrogram" << "IA-RSSI" << "PM-Internal" << "LTE-Power vs.Time(Frame)";
  ctrlstr << "sactrl.log" << "rtsactrl.log";
  modesmeasstr << "Spectrum" << "Persist Spectrum" << "RSSI" << "Internal" << "CP";//......

  ui->chafir->setStyleSheet("QPushButton { border-style: flat;}\
                            QPushButton:flat {border: none;}");
                            ui->chasec->setStyleSheet("QPushButton { border-style: flat;}\
                                                      QPushButton:flat {border: none;}");
                                                      ui->chathird->setStyleSheet("QPushButton { border-style: flat;}\
                                                                                  QPushButton:flat {border: none;}");
                                                                                  ui->chafourth->setStyleSheet("QPushButton { border-style: flat;}\
                                                                                                               QPushButton:flat {border: none;}");

                                                                                                               ui->plusbtn->setStyleSheet("QPushButton { border-style: flat;}\
                                                                                                                                          QPushButton:flat {border: none;}");

                                                                                                                                          ui->mode1btn->setStyleSheet("QPushButton { border-style: none;}\
                                                                                                                                                                      QPushButton:flat {border: none;}");

                                                                                                                                                                      ui->mode2btn->setStyleSheet("QPushButton { border-style: none;}\
                                                                                                                                                                                                  QPushButton:flat {border: none;}");

                                                                                                                                                                                                  ui->mode3btn->setStyleSheet("QPushButton { border-style: none;}\
                                                                                                                                                                                                                              QPushButton:flat {border: none;}");

                                                                                                                                                                                                                              ui->mode4btn->setStyleSheet("QPushButton { border-style: none;}\
                                                                                                                                                                                                                                                          QPushButton:flat {border: none;}");
                                                                                                                                                                                                                                                          return;
}

/**
 * @brief load all timer for different communication
 * @return under zero means error
 * @note only called once in constructor
 * @author steve
 * @since {2018-12-12}
*/
qint32 BitPlatForm::LoadAllTimer()
{
  qint32 iBack = -1;
  if(0 == (modeswitchtimerhandle = startTimer(MODESWITCH)))
    {
      return iBack;
    }
  if(0 == (sysmsgtimerhandle = startTimer(SYSINTER)))
    {
      return iBack;
    }
  if(0 == (tempertimerhandle = startTimer(TEMPERSWITCH)))
    {
      return iBack;
    }
  iBack = 0;
  return iBack;
}

/**
 * @brief when close app to release timer
 * @note only used in destructor
 * @author steve
 * @since {2018-12-12}
*/
void BitPlatForm::ReleaseAllTimer()
{
  if(modeswitchtimerhandle)
    {
      killTimer(modeswitchtimerhandle);
      modeswitchtimerhandle = 0;
    }
  if(sysmsgtimerhandle)
    {
      killTimer(sysmsgtimerhandle);
      sysmsgtimerhandle = 0;
    }
  if(tempertimerhandle)
    {
      killTimer(tempertimerhandle);
      tempertimerhandle = 0;
    }
  return;
}

/**
 * @brief init connect sig and slot
 * @note
 * @author steve
 * @since {2018-12-14}
*/
void BitPlatForm::ConnectAllSigSlot()
{
  QObject::connect(this, SIGNAL(ModeSwitchSig(quint32)), this, SLOT(DoSwitchAction(quint32)));
  return;
}

/**
 * @brief init all resources when platform construct
 * @note
 * @author steve
 * @since {2018-12-17:c01-18:c02-11}
*/
void BitPlatForm::InitP()
{  
  //ini ana mode
  pSaAna = new BitSA(this);
  remoteinterface::SetRemoteSaHandle(pSaAna);
  pSaAna->setGeometry(QRect(PSTARTX,PSTARTY,PWIDTH,PHEIGHT));
  QObject::connect(pSaAna,SIGNAL(ZoomIn(bool)),this,SLOT(PlatZoomCtrl(bool)));

  pRtsaAna = new BitRtSa(this);
  remoteinterface::SetRemoteRtsaHandle(pRtsaAna);
  pRtsaAna->setGeometry(QRect(PSTARTX,PSTARTY,PWIDTH,PHEIGHT));
  QObject::connect(pRtsaAna,SIGNAL(ZoomIn(bool)),this,SLOT(PlatZoomCtrl(bool)));
  pRtsaAna->hide();

  //add widget handle by RUNMODE order
  modewidvec.append(pSaAna);
  modewidvec.append(pRtsaAna);

  //to show timer battery and gps immediately when up
  timerstr = QDateTime::currentDateTime().toString("yyyy-MM-dd   APhh:mm:ss");
  ui->timelabel->setText(timerstr);
  shmengine::PassTrigToSys(PLT_IXT_System_Info,PLT_IXS_BatteryInfoAll);
  usleep(CTRLUPOVERTIME);
  switch (shmengine::getsingleshm()->pshm_sysinfo->BatterChargeStatus)
    {
    case UN_BATT:
      NoBatteryCtrl();
      break;
    case BATT_CHARGE:
      ChargeStateCtrl();
      break;
    case BATT_DISCHARGE:
      DisChargeStateCtrl();
      break;
    case BATT_FULL:
      FullBatteryCtrl();
      break;
    default:
      break;
    }
  return;
}

/**
 * @brief release new widgets obj
 * @note [should let mode thread stop first]
 * @author steve
 * @since {2018-12-18}
*/
void BitPlatForm::DeleteW()
{  
  delete pSetWid;
  //every plugin has a debug for close app
  //this problem only a problem when under desktop environment
  foreach (QWidget* pw,modewidvec)
    {
      delete pw;
    }
  delete ui;
}

/**
 * @brief get ana mode by push btn text
 * @param[in]mode text
 * @return mode index same order with RUNMODE
 * @note
 * @author steve
 * @since {2019-01-04:c01-18}
*/
qint32 BitPlatForm::GetModeNum(QString &str)
{
  QString tempstr = str.mid(INDEXBASE,str.indexOf('-') + 1);
  qint32 i = 0;
  qint32 ilen = sizeof(modbtntext) / sizeof(QString);
  for(i = 0;i < ilen;i++)
    {
      if(modbtntext[i] == tempstr)
        {
          return i;
        }
    }
  return -1;
}

/**
 * @brief for detect home mode whether exit in ui by mode num
 * @param[in]
 * @param[in]
 * @return <0 not exit,means call before state
 * @note
 * @author steve
 * @since {2019-01-24}
*/
qint32 BitPlatForm::HomeModeExistornot(quint32 ihmode)
{
  qint32 i = 0;
  qint32 j = 0;
  qint32 iIndex = -1;
  qint32 iSum = sizeof(modbtntext) / sizeof(QString);
  for(i = 0;i < nowshowmodsum;i++)
    {
      QString tempstr = nowmodetext.at(i).mid(INDEXBASE,nowmodetext.at(i).indexOf('-') + 1);
      for(j = 0;j < iSum;j++)
        {
          if(modbtntext[j] == tempstr)
            {
              if(j == ihmode)
                {
                  return i;
                }
            }
        }
    }
  return iIndex;
}

/**
 * @brief close ctrl app
 * @param[in] modetype one of ana mode,same with RUNMODE
 * @return under zero means error
 * @note
 * @author steve
 * @since {2018-12-14:c02-12}
*/
qint32 BitPlatForm::CloseCtrlApp(quint32 modetype)
{
  //setting shm
  if(modetype >= BitPlatForm::modesumnum)
    return -1;
  //UNDO modetype temp
  if(modetype > RTSA_MODE)
    return 0;
  *shmengine::getsingleshm()->pctrlexitvec.at(modetype) = BEXIT;
  QString mstr = gloadctrlparam.pctrlpathvec.at(modetype);
  //for auto exit
  QThread::msleep(MODESWITCH);
  //for clear resource
  processvec.at(modetype)->close();
  return static_cast<qint32>(processvec.at(modetype)->waitForFinished(CTRLUPOVERTIME));
}

/**
 * @brief when switch mode to show pic and finish to close
 * @param[in] action 0 means close pic,1 means open pic
 * @return under zero means error
 * @note
 * @author steve
 * @since {2018-12-14}
*/
qint32 BitPlatForm::CutSwitchPic(quint32 action)
{
  return 0;
}

/**
 * @brief hide before mode gui
 * @param[in] modetype one of ana mode
 * @note
 * @author steve
 * @since {2018-12-14}
*/
void BitPlatForm::HideModeGui(quint32 modetype)
{  
  if(modetype >= BitPlatForm::modesumnum)
    return;
  if(modetype > RTSA_MODE)
    return;
  modewidvec.at(modetype)->hide();
  return;
}

/**
 * @brief burn .bit file
 * @param[in] modetype one of ana mode
 * @return under zero means error
 * @note [this part put in sysctrlapp better]
 * @author steve
 * @since {2018-12-14:c02-13}
*/
qint32 BitPlatForm::FlashBitStream(quint32 modetype)
{
  if(modetype >= BitPlatForm::modesumnum)
    return -1;
  while(timerstate){};
  BURN_STATE = POFF;
  shmengine::getsingleshm()->pshm_sysconf->AnaMode = modetype;
  shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_BurnAction);
  usleep(BURNTIME);
  BURN_STATE = PON;
  return 0;
}

/**
 * @brief show now mode gui
 * @param[in] modetype one of ana mode
 * @note
 * @author steve
 * @since {2018-12-14}
*/
void BitPlatForm::ShowModeGui(quint32 modetype)
{
  if(modetype >= BitPlatForm::modesumnum)
    return;
  if(modetype > RTSA_MODE)
    return;
  modewidvec.at(modetype)->show();
  return;
}

/**
 * @brief start now mode ctrl app
 * @param[in] modetype one of ana mode
 * @return  under zero means error
 * @note
 * @author steve
 * @since {2018-12-14}
*/
qint32 BitPlatForm::StartCtrlApp(quint32 modetype)
{
  if(modetype >= BitPlatForm::modesumnum)
    return -1;
  if(modetype > RTSA_MODE)
    return 0;
  QString mstr = gloadctrlparam.pctrlpathvec.at(modetype);
  processvec.at(modetype)->start(mstr,QStringList(mstr));
  processvec.at(modetype)->waitForStarted(CTRLUPOVERTIME);
  return 0;
}

/**
 * @brief for release debug redirect log
 * @param[in]
 * @param[in]
 * @param[in]
 * @note
 * @author steve
 * @since {2018-12-19}
*/
void BitPlatForm::bitRedirectHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
  QTextStream logstream(&BitPlatForm::logfile);
  QString logtime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
  QString logstr = NULL;
  switch (type)
    {
    case QtDebugMsg:
      logstr = "Debug:";
      break;
    case QtWarningMsg:
      logstr = "Waring:";
      break;
    case QtCriticalMsg:
      logstr = "Critical:";
      break;
    case QtFatalMsg:
      logstr = "Fatal:";
      break;
    }

  logstr += msg + context.file + ";" + QString::number(context.line) + ";" + context.function + ";" + logtime + ";";
  logstream << logstr << "\r\n";
  BitPlatForm::logfile.flush();
  return;
}

/**
 * @brief when timer receive home switch or platform itself then to send sig
 * @param[in] switchtype running mode type old
 * @note called by multi different switch mode
 * @author steve
 * @since {2018-12-14:c02-12}
*/
void BitPlatForm::DoSwitchAction(quint32 switchtype)
{
  if(SA_MODE == switchtype)
    {
      pSaAna->menuClose();
    }
  //close before mode ctrl app
  if(CloseCtrlApp(switchtype) < 0)
    {
      qCritical("ctrl app close failed");
      return;
    }

  //tell sec FPGA to cut picture,this func put in sysctrlapp
  //UNDO:2018-12-17
  //cut picture could unuse instead of platform back picture,because when switch mode
  //the ana UI will be hide,then the platform will show up all;
  if(CutSwitchPic(PON) < 0)
    {
      return;
    }

  //hide before ui mode
  HideModeGui(switchtype);

  switchtype = shmengine::getsingleshm()->pshm_home->modetype;
  //flash bitstream
  if(FlashBitStream(switchtype) < 0)
    {
      return;
    }

  //show now ui mode
  ShowModeGui(switchtype);
  //start now ctrl app
  if(StartCtrlApp(switchtype) < 0)
    {
      qCritical("ctrl app open failed");
      return;
    }

  //tell sec FPGA to cut picture
  if(CutSwitchPic(POFF) < 0)
    {
      return;
    }

  //reflesh platform tab msg,do this outside

  //should last reflesh
  orimode = shmengine::getsingleshm()->pshm_home->modetype;
  return;
}

/**
 * @brief
 * @param[in]flag when true zoom out else zoom in
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-01-09}
*/
void BitPlatForm::PlatZoomCtrl(bool flag)
{
  if(flag)
    {
      modewidvec.at(orimode)->setGeometry((QRect(0,0,PWIDTH,PHEIGHT + MAXDETA)));
    }
  else
    {
      modewidvec.at(orimode)->setGeometry((QRect(PSTARTX,PSTARTY,PWIDTH,PHEIGHT)));
    }
  return;
}

void BitPlatForm::on_mode1btn_clicked()
{  
#if 0
  shmengine::getsingleshm()->pshm_home->modetype = SA_MODE;
  if(orimode != shmengine::getsingleshm()->pshm_home->modetype)
    {
      DoSwitchAction(orimode);
    }
#endif
  return;
}

void BitPlatForm::on_mode2btn_clicked()
{
  QString mstr = ui->mode2btn->text();

  shmengine::getsingleshm()->pshm_home->modetype = GetModeNum(mstr);
  DoSwitchAction(orimode);

  SetModBtntext(NowModExitor(mstr),mstr);
  FillConstText();
  return;
}

void BitPlatForm::on_mode3btn_clicked()
{
  QString mstr = ui->mode3btn->text();

  shmengine::getsingleshm()->pshm_home->modetype = GetModeNum(mstr);
  DoSwitchAction(orimode);

  SetModBtntext(NowModExitor(mstr),mstr);
  FillConstText();
  return;
}

void BitPlatForm::on_mode4btn_clicked()
{
  QString mstr = ui->mode4btn->text();

  shmengine::getsingleshm()->pshm_home->modetype = GetModeNum(mstr);
  DoSwitchAction(orimode);

  SetModBtntext(NowModExitor(mstr),mstr);
  FillConstText();
  return;
}

void BitPlatForm::on_plusbtn_clicked()
{  
  return  PlusBtnCtrl();
}

void BitPlatForm::on_chafir_clicked()
{
  CloseBtnCtrl(INDEXBASE);
  //get mode and reflesh shm
  QString tempstr = nowmodebtn.at(INDEXBASE)->text();
  shmengine::getsingleshm()->pshm_home->modetype = GetModeNum(tempstr);
  DoSwitchAction(orimode);
  return;
}

void BitPlatForm::on_chasec_clicked()
{
  return CloseBtnCtrl(INDEXBASE + 1);
}

void BitPlatForm::on_chathird_clicked()
{
  return CloseBtnCtrl(INDEXBASE + 2);
}

void BitPlatForm::on_chafourth_clicked()
{
  return CloseBtnCtrl(INDEXBASE + 3);
}

void BitPlatForm::on_pushButton_clicked()
{
  if(0 == pSetWid)
    {
      pSetWid = new setwid(0);
    }
  pSetWid->show();
  return;
}

/**
 * @brief for scpi and inner to call for cha btn hide or show
 * @param[in]inum index from left to right start from 0
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-01-17}
*/
void BitPlatForm::CloseBtnCtrl(qint32 iIndex)
{
  nowshowmodsum--;
  clobtnvec.at(nowshowmodsum)->hide();
  nowmodebtn.at(nowshowmodsum)->hide();
  if(1 == nowshowmodsum)
    {
      clobtnvec.at(INDEXBASE)->hide();
    }
  //cut back-image


  //forward to move mode text one by one
  qint32 i = 0;
  for(i = iIndex;i < nowshowmodsum;i++)
    {
      nowmodebtn.at(i)->setText(nowmodebtn.at(i + 1)->text());
    }
  nowmodebtn.at(nowshowmodsum)->setText("--");

  ui->toplabel->setPixmap(QPixmap(QString::fromUtf8(TOPMENU[nowshowmodsum - 1])));
  ui->plusbtn->move(SPX + (nowshowmodsum - 1) * STEPP + DETAP,SPY);
  FillConstText();
  return;
}

/**
 * @brief for plus mode
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-01-17:c0124:c0125}
*/
void BitPlatForm::PlusBtnCtrl()
{
  if(0 == pPlusDia)
    {
      //call all modes to collect ana mode to sure now measure items
      qint32 ilastmea = 1;//as last measure item
      GetMeasitemsIndex(&ilastmea);
      qint32 iallmesa[NONEMODE] = {1,1,1,1,1};
      quint32 imea = ilastmea;

      pPlusDia = new plusmode(this,&shmengine::getsingleshm()->pshm_home->modetype,&imea,iallmesa,NONEMODE,&modesmeasstr);
      pPlusDia->exec();
      QString smod = pPlusDia->getmodstr();
      qint32 iaction = pPlusDia->getdostate();
      delete pPlusDia;
      pPlusDia = 0;
      if(iaction)
        {
          //must switch ana mode
          if(orimode != shmengine::getsingleshm()->pshm_home->modetype)
            {
              //change title text and move
              qint32 ist = NowModExitor(smod);
              if(ist < 0)
                {
                  //if mode exit and just meas different,means just
                  if(nowshowmodsum < UIMODMAXNUM)
                    {
                      //show before hide btn
                      clobtnvec.at(INDEXBASE)->show();
                      clobtnvec.at(nowshowmodsum)->show();
                      nowmodebtn.at(nowshowmodsum)->show();
                      nowshowmodsum++;

                      ui->toplabel->setPixmap(QPixmap(QString::fromUtf8(TOPMENU[nowshowmodsum - 1])));
                      ui->plusbtn->move(SPX + (nowshowmodsum - 1) * STEPP + DETAP,SPY);
                    }
                }
              SetModBtntext(ist,smod);
              //do mode switch action
              DoSwitchAction(orimode);
              //UNDO,when measure differ also to call interface,whether or not
              FillConstText();
            }
          else
            {
              //just change title text but not move
              if(ilastmea != imea)
                {
                  nowmodebtn.at(INDEXBASE)->setText(smod);
                  FillConstText();
                  //just call mode interface to convert measure

                }
            }
        }
    }
  return;
}

