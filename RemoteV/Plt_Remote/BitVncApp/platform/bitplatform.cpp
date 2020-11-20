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
//#include "shmengine.h"
#include <QDateTime>
#include <QDebug>
#include <qapplication.h>
#include <QTextStream>
#include "remoteinterface.h"
#include "scpidef/scpidef.h"
#include <unistd.h>
#include "hotplug/hotplughandler.h"

quint32 BitPlatForm::modesumnum = NONEMODE;
QFile BitPlatForm::logfile("gui.log");
QChar BitPlatForm::regchar = '<';
const char* BitPlatForm::syncpath = "/bin/sync";
extern ScpiPort_usb        *g_pPortUsb;
BitPlatForm::BitPlatForm(QWidget *parent) :  
  QMainWindow(parent),
  lcf (PUZERO),
  ncf (POFF),
  lncf (PUZERO),
  nncf(POFF),
  BURN_STATE(PON),
  timerstate(POFF),
  batnum(BATTARYINI),
  modbtnindex(INDEXBASE),
  loreflag(POFF),
  touchstate(PTY0),
  //  bitCursor(QPixmap(":/bit/image/bitmouse.png"),-1,-1),
  ui(new Ui::BitPlatForm)
{  
  ui->setupUi(this);
  QApplication::setOverrideCursor(Qt::ArrowCursor/*BlankCursor*/);

  //this->setCursor(Qt::BlankCursor);
#ifdef _Linux_F238_Log
  qInstallMessageHandler(BitPlatForm::bitRedirectHandler);
  if(!BitPlatForm::logfile.open(QIODevice::Append))
    {
      qCritical("open log file failed");
    }
#endif
  setWindowFlags(Qt::FramelessWindowHint);
  this->setGeometry(mapToGlobal(QPoint(0,0)).x(),mapToGlobal(QPoint(0,0)).y(),this->width(),this->height());

#ifndef PLT_STATE_COND
  pltlastallstates.nowshowmodsum = 3;
  pltlastallstates.orimode = 0;
  pltlastallstates.oribtnIndex = 0;
  pltlastallstates.pltpres.powerstate = 1;

  pltlastallstates.iallmesa[0] = 0;
  pltlastallstates.iallmesa[1] = 2;
  pltlastallstates.iallmesa[2] = 0;
  pltlastallstates.iallmesa[3] = 0;
  pltlastallstates.iallmesa[4] = 0;
  pltlastallstates.iallmesa[5] = 0;
  pltlastallstates.iallmesa[6] = 0;

  pltlastallstates.ilastallmesa[0] = 0;
  pltlastallstates.ilastallmesa[1] = 2;
  pltlastallstates.ilastallmesa[2] = 0;
  pltlastallstates.ilastallmesa[3] = 0;
  pltlastallstates.ilastallmesa[4] = 0;
  pltlastallstates.ilastallmesa[5] = 0;
  pltlastallstates.ilastallmesa[6] = 0;

  pltlastallstates.iuimode[0] = 0;
  pltlastallstates.iuimode[1] = 1;
  pltlastallstates.iuimode[2] = 4;
  pltlastallstates.iuimode[3] = 3;

  pltsystate.powerstate = 1;
  pltlastallstates.lantype = 1;
  pltlastallstates.freqref = 0;
  pltlastallstates.sleept = 0;
  pltlastallstates.dismod = 0;
  pltlastallstates.lcdbright = 2;
  pltlastallstates.soundnum = 40;
  pltlastallstates.soundswitch = 1;
  pltlastallstates.datetype = 2;
  pltlastallstates.syssetindex = 0;
  pltlastallstates.gpswitch = 0;
  pltlastallstates.gkeybeepswitch = 0;

  pltlastallstates.lanport = 5026;
  sprintf(pltlastallstates.ipstr,"%s","192.168.26.238");
  sprintf(pltlastallstates.maskstr,"%s","255.255.255.0");
  sprintf(pltlastallstates.gatewaystr,"%s","192.168.26.1");

  pltlastallstates.remoteintertype = 0;
  pltlastallstates.wifiswitch = 0;
  pltlastallstates.blumode = 0;
  pltlastallstates.bluetswitch = 0;
  sprintf(pltlastallstates.wifimib,"%s","123456");

  PltSavePreStates();
  PltSaveStates(0);
  PltSaveStates(1);
  PltSaveStates(2 + 3);
#endif

  PltLoadDevelopMsg();
  PltLoadPreStates();
  PltLoadStates(pltsystate.powerstate);
  SCPI_SetSCPI_Port(&pltlastallstates.lanport);
  SCPI_Communicate_Init();
  qDebug()<<"@"<<"3";
  IniOther();
  qDebug()<<"@"<<"4";
  IniCtrlVec();
  qDebug()<<"@"<<"5";
  //StartCtrlApp(pltlastallstates.orimode);
  SetIniQss();
  qDebug()<<"@"<<"6";
  IniBtnVecText();
  qDebug()<<"@"<<"7";
  Uphomeapp();
  qDebug()<<"@"<<"8";
  InitP();
  qDebug()<<"@"<<"9";
  if(LoadAllTimer() < 0)
    {
      //dealing expec
      qFatal("platform timer ini failed");
    }
  qDebug()<<"@"<<"10";
  ConnectAllSigSlot();
  qDebug("=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=.=");
}

BitPlatForm::~BitPlatForm()
{  
  ReleaseAllTimer();
  CloseCtrlApp(pltlastallstates.orimode);
  Downhomeapp();
  PltToMainEXit();
//  shmengine::getsingleshm()->pshm_calnotic->notic = pltlastallstates.oribtnIndex + 1;
  DeleteW();
#ifdef _Linux_F238_Log
  BitPlatForm::logfile.close();
  qInstallMessageHandler(0);
#endif
  //  shmengine::getsingleshm()->pshm_calnotic->notic = pltlastallstates.oribtnIndex + 1;
}

/**
 * @brief to exit all app
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-04-29}
*/
void BitPlatForm::PltToMainEXit()
{  
//  shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_Calc);
  return;
}

/**
 * @brief recover home app and sys time states
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-05-20;c09-27}
*/
void BitPlatForm::IniOther()
{
//  shmengine::getsingleshm()->pshm_home->modetype = pltlastallstates.orimode;
//  shmengine::getsingleshm()->pshm_sysinfo->datetype = pltlastallstates.datetype;
//  shmengine::getsingleshm()->pshm_sysconf->AnaMode = pltlastallstates.orimode;
//  shmengine::getsingleshm()->pshm_sysinfo->dismode = pltlastallstates.dismod;
  return;
}

/**
 * @brief load process for all modes by RUNMODE order
 * @note [will extend by mode]
 * @since {2018-12-21;c04-10;c05-20}
*/
void BitPlatForm::IniCtrlVec()
{
  nowmodebtn.append(ui->mode1btn);
  nowmodebtn.append(ui->mode2btn);
  nowmodebtn.append(ui->mode3btn);
  nowmodebtn.append(ui->mode4btn);

  modelabel.append(ui->label_5);
  modelabel.append(ui->label_6);
  modelabel.append(ui->label_7);
  modelabel.append(ui->label_8);

  clobtnvec.append(ui->chafir);
  clobtnvec.append(ui->chasec);
  clobtnvec.append(ui->chathird);
  clobtnvec.append(ui->chafourth);

  pPlusDia = NULL;
  pSetWid = NULL;
  //for ctrl app standard output
#ifdef _Linux_F238_Log
  ctrlstr << "sactrl.log" << "rtsactrl.log"<<"inter.log"<<"pm.log"<<"ltefdd.log"<<"ltetdd.log"<<"fgnr.log";
  processvec.append(&sactrlprocess);
  processvec.at(SA_MODE)->setStandardOutputFile(ctrlstr.at(SA_MODE),QIODevice::Append);

  processvec.append(&rtsactrlprocess);
  processvec.at(RTSA_MODE)->setStandardOutputFile(ctrlstr.at(RTSA_MODE),QIODevice::Append);

  processvec.append(&rtsactrlprocess);
  processvec.append(&rtsactrlprocess);

  processvec.append(&ltefddctrlprocess);
  processvec.at(LTE_FDD_MODE)->setStandardOutputFile(ctrlstr.at(LTE_FDD_MODE),QIODevice::Append);

  processvec.append(&ltetddctrlprocess);
  processvec.at(LTE_TDD_MODE)->setStandardOutputFile(ctrlstr.at(LTE_TDD_MODE),QIODevice::Append);

  processvec.append(&fgnrctrlprocess);
  processvec.at(FIVE_G_NR)->setStandardOutputFile(ctrlstr.at(FIVE_G_NR),QIODevice::Append);

#endif
  battpicvec.append(NOBATPIC);
  battpicvec.append(CHARGEPIC);
  battpicvec.append(DISCHARGEPIC);
  battpicvec.append(FULLPIC);

  toppicvec.append(TOPMENU_1);
  toppicvec.append(TOPMENU_2);
  toppicvec.append(TOPMENU_3);
  toppicvec.append(TOPMENU_4);
  return;
}


/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-05-20}
*/
void BitPlatForm::IniBtnVecText()
{
  qint32 inum = modelabel.size();
  qint32 i = 0;
  for(i = 0;i < inum;i++)
    {
      nowmodetext.append(modelabel.at(i)->text());
    }
  return;
}


/**
 * @brief start home app by platform not itself
 * @param[in]
 * @param[in]
 * @return
 * @note
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
 * @since {2019-01-09}
*/
void BitPlatForm::Downhomeapp()
{
  homeprocess.close();
  homeprocess.waitForStarted(CTRLUPOVERTIME);
  return;
}

/**
 * @brief accor with now four text
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-01-08}
*/
void BitPlatForm::FillConstText()
{
  qint32 inum = nowmodetext.size();
  qint32 i = 0;
  for(i = 0;i < inum;i++)
    {
      nowmodetext[i] = (modelabel.at(i)->text());
    }
  return;
}

/**
 * @brief set mode ui by home and plus
 * @param[in]
 * @param[in]
 * @return when search from now mode btn return index,else -1
 * @note
 * @since {2019-01-08:c01-17:c01-24:c01-25}
*/
qint32 BitPlatForm::NowModExitor(QString& modstr)
{  
  QString tempstr = modstr.mid(INDEXBASE,modstr.indexOf(BitPlatForm::regchar));
  qint32 i = 0;
  qint32 iIndex = 0;
  qint32 iflag = 1;
  for(i = 0;i < pltlastallstates.nowshowmodsum;i++)
  {
      QString istr = nowmodetext.at(i);
      if(istr.mid(INDEXBASE,istr.indexOf(BitPlatForm::regchar)) == tempstr)
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
 * @param[in]before plus event and sum already 4,means replace ori active btn
 * @return
 * @note
 * @since {2019-01-25;c02-26}
*/
qint32 BitPlatForm::SetModBtntext(qint32 iIndex, QString &modstr ,qint32 iflag)
{  
  if(iIndex < 0)
  {
      if(iflag)
      {
          modelabel.at(modbtnindex)->setText(modstr);
      }
      else
      {
          modelabel.at(pltlastallstates.nowshowmodsum - 1)->setText(modstr);
      }
  }
  else
  {
      modelabel[iIndex]->setText(modstr);
  }
  return iIndex;
}

/**
 * @brief for out call
 * @param[in]
 * @param[in]
 * @return
 * @note home to switch mode just replace or switch but not add
 * @since {2019-02-13;c02-25;c02-27;c:03-12;c:03-21;c:04-17;c:05-20;c:08-22;c:09-09}
*/
void BitPlatForm::InnerTimeCtrl(qint32 tid)
{
  if(sysmsgtimerhandle == tid)
    {
      if(PTY0 == pltlastallstates.datetype)
      {
          timerstr = QDateTime::currentDateTime().toString("dd-MM-yyyy   APhh:mm:ss");
//          shmengine::getsingleshm()->pshm_sysinfo->datetype = PTY0;
      }
      else if(PTY1 == pltlastallstates.datetype)
      {
          timerstr = QDateTime::currentDateTime().toString("MM-dd-yyyy   APhh:mm:ss");
//          shmengine::getsingleshm()->pshm_sysinfo->datetype = PTY1;
      }
      else
      {
          timerstr = QDateTime::currentDateTime().toString("yyyy-MM-dd   APhh:mm:ss");
//          shmengine::getsingleshm()->pshm_sysinfo->datetype = PTY2;
      }
      ui->timelabel->setText(timerstr);
//      if(pSetWid && pSetWid->pdedtsetwid)
//        {
//          pSetWid->pdedtsetwid->refreshTime();
//        }
      if(pltlastallstates.gpswitch)
        {
          if("-- -- -- --" != ui->gpslabel->text())
            {
              if(ui->gpslabel->isHidden())
                {
                  this->ui->gpslabel->show();
                }
              else
                {
                  this->ui->gpslabel->hide();
                }
            }
        }
    }
  if(modeswitchtimerhandle == tid)
    {
//      if(shmengine::getsingleshm()->pshm_home->modesource)
//        {
//          if(PON == shmengine::getsingleshm()->pshm_home->systype)
//            {
//              SysPanelCtrl();
//              shmengine::getsingleshm()->pshm_home->systype = POFF;
//            }
//          else if(PON + 1 == shmengine::getsingleshm()->pshm_home->systype)
//            {
//              SaveAllModeWhenShutOff(pltsystate.powerstate);
//              system(BitPlatForm::syncpath);
//              shmengine::getsingleshm()->pshm_home->systype = POFF;
//            }
//          //!<preset default states
//          else if(PON + 2 == shmengine::getsingleshm()->pshm_home->systype)
//            {
//              //for notice dialog
//              emit PltFactorySig();
//              shmengine::getsingleshm()->pshm_home->systype = POFF;
//            }
//          else
//            {
//              if(pltlastallstates.orimode != shmengine::getsingleshm()->pshm_home->modetype)
//                {
//                  qint32 iresult = HomeModeExistornot(shmengine::getsingleshm()->pshm_home->modetype);
//                  //has nothing to do with measurements
//                  emit ModeSwitchSig(pltlastallstates.orimode);
//                  if(iresult < 0)
//                    {
//                      //change btn text
//                      SetBtnTextByHomeSwitch(pltlastallstates.orimode);
//                      pltlastallstates.iuimode[modbtnindex] = shmengine::getsingleshm()->pshm_home->modetype;
//                    }
//                  else
//                    {
//                      modbtnindex = iresult;
//                      pltlastallstates.oribtnIndex = modbtnindex;
//                      ChangeModPic(pltlastallstates.nowshowmodsum,iresult);
//                      pltlastallstates.iuimode[modbtnindex] = shmengine::getsingleshm()->pshm_home->modetype;
//                    }
//                  FillConstText();
//                }
//            }
//          shmengine::getsingleshm()->pshm_home->modesource = POFF;
//        }
    }

  if(tempertimerhandle == tid)
    {
      if(BURN_STATE)
        {
          timerstate = PON;
          static qint32 nflf = -1;
          static qint32 nfnf = -2;
          quint32 groupflg = PLT_IXS_BatteryInfoAll | PLT_IXS_BoardTempAlarm;
          static qint32 gpsflag = POFF;
          if(pltlastallstates.gpswitch)
            {
              groupflg |= PLT_IXS_GPSInfoAll;
//              shmengine::PassTrigToSysExt(PLT_IXT_System_Info,groupflg);
              if(POFF == gpsflag)
                {
                  gpsflag = PON;
                  //setting qss
                  GpsPltdisMod(pltlastallstates.dismod,gpsflag);
                }
              //reflesh statebar states
              pSetWid->pnetsetwid->ReflesGpsLabelStatus(gpsflag);
//              ui->gpslabel->setText(QString(QLatin1String(shmengine::getsingleshm()->pshm_sysinfo->GPSLatitude)) + " " +
//                                    QString(QLatin1String(shmengine::getsingleshm()->pshm_sysinfo->GPSLongitude)));
            }
          else
            {
//              shmengine::PassTrigToSysExt(PLT_IXT_System_Info,groupflg);
              if(gpsflag)
                {
                  gpsflag = POFF;
                  //setting qss
                  GpsPltdisMod(pltlastallstates.dismod,gpsflag);
                  pSetWid->pnetsetwid->ReflesGpsLabelStatus(gpsflag);
                  ui->gpslabel->setText("-- -- -- --");
                  this->ui->gpslabel->show();
                }
            }

//          QString strtemper = "TR:" + QString::number(shmengine::getsingleshm()->pshm_sysinfo->RfTemp) + "deg\n"
//              + "TM:" + QString::number(shmengine::getsingleshm()->pshm_sysinfo->BoardTemp) + "deg\n"
//              + "TD:" + QString::number(shmengine::getsingleshm()->pshm_sysinfo->FpgaTemp) + "deg";
//          ui->label_9->setText(strtemper);

//          switch (shmengine::getsingleshm()->pshm_sysinfo->BatterChargeStatus)
//            {
//            case UN_BATT:
//              nflf = UN_BATT;
//              if(nflf != nfnf)
//                {
//                  NoBatteryCtrl();
//                  nfnf = nflf;
//                }
//              break;
//            case BATT_CHARGE:
//              nfnf = BATT_CHARGE;
//              ChargeStateCtrl();
//              break;
//            case BATT_DISCHARGE:
//              nfnf = BATT_DISCHARGE;
//              DisChargeStateCtrl();
//              break;
//            case BATT_FULL:
//              nflf = BATT_FULL;
//              if(nflf != nfnf)
//                {
//                  FullBatteryCtrl();
//                  nfnf = nflf;
//                }
//              break;
//            default:
//              break;
//            }
        }
      timerstate = POFF;
    }
  return;
}

/**
 * @brief will increase with mode...
 * @param[in]
 * @return
 * @note just used by home switch and now mode doesn't exit
 * @since {2019-02-27}
*/
void BitPlatForm::SetBtnTextByHomeSwitch(qint32 imod)
{
  const QString* pmeastr = NULL;
  switch (imod)
    {
    case SA_MODE:
      pmeastr = sameasbtntext;
      break;
    case RTSA_MODE:
      pmeastr = rtsameasbtntext;
      break;
    case INTERF_MODE:
      pmeastr = intermeasbtntext;
      break;
    case PM_MODE:
      pmeastr = pmmeasbtntext;
      break;
    case LTE_FDD_MODE:
      pmeastr = ltefddmeasbtntext;
      break;
    case LTE_TDD_MODE:
      pmeastr = ltetddmeasbtntext;
      break;
    case FIVE_G_NR:
      pmeastr = fgnrmeasbtntext;
    default:
      break;
    }
  modelabel.at(modbtnindex)->setText(modbtntext[imod] + QObject::tr("<BR/><span style=\"font-weight:normal;\">%1</span>").arg(*(pmeastr + pltlastallstates.iallmesa[imod])));
  return;
}

/**
 * @brief for without battery ctrl
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-02-13}
*/
void BitPlatForm::NoBatteryCtrl()
{
  lncf = -1;
  nncf = 0;
  lcf = -1;
  ncf = 0;
  ui->batpiclabel->setPixmap(QPixmap(QString::fromUtf8(battpicvec.at(PTY0)[INDEXBASE])/*(NOBATPIC[INDEXBASE])*/));
  ui->batterylabel->setText(tr("NBat"));
  return;
}

/**
 * @brief for charge state to cut picture
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-02-13:c02-14;c03-12}
*/
void BitPlatForm::ChargeStateCtrl()
{
  lncf = -1;
  nncf = 0;
//  batnum = shmengine::getsingleshm()->pshm_sysinfo->BatteryRemaind;
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
      ui->batpiclabel->setPixmap(QPixmap(QString::fromUtf8(battpicvec.at(PTY1)[iunit]/*CHARGEPIC[iunit]*/)));
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
 * @since {2019-02-13:c02-14;c03-12}
*/
void BitPlatForm::DisChargeStateCtrl()
{  
  lcf = -1;
  ncf = 0;
//  batnum = shmengine::getsingleshm()->pshm_sysinfo->BatteryRemaind;
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
      ui->batpiclabel->setPixmap(QPixmap(QString::fromUtf8(battpicvec.at(PTY2)[iunit]/*DISCHARGEPIC[iunit]*/)));
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
 * @since {2019-02-13}
*/
void BitPlatForm::FullBatteryCtrl()
{
  lncf = -1;
  nncf = 0;
  lcf = -1;
  ncf = 0;
  ui->batterylabel->setText("100%");
  return ui->batpiclabel->setPixmap(QPixmap(QString::fromUtf8(battpicvec.at(PTY3)[INDEXBASE]/*FULLPIC[INDEXBASE]*/)));
}

void BitPlatForm::timerEvent(QTimerEvent *event)
{  
  return InnerTimeCtrl(event->timerId());
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-10-08}
*/
//void BitPlatForm::changeEvent(QEvent *event)
//{
//  if(event->type() == QEvent::LanguageChange)
//    {
//      pSetWid->pcomsetwid->trsetText();
//    }
//  else
//    return QWidget::changeEvent(event);
//}

/**
 * @brief setting platform ini qss
 * @note
 * @since {2019-01-04:c01-25;c02-26;c03-01;c-05-20;}
*/
void BitPlatForm::SetIniQss()
{
  QString mqss = "QPushButton{text-align:left;\
      padding-left:10px;\
  background-color:transparent;\
  border-style: flat;}\
QPushButton:flat {border: none;}";
QString mqss1 = "QPushButton { border-style: flat;}\
    QPushButton:flat {border: none;}";
    ui->chafir->setStyleSheet(mqss1);
ui->chasec->setStyleSheet(mqss1);
ui->chathird->setStyleSheet(mqss1);
ui->chafourth->setStyleSheet(mqss1);
ui->mode1btn->setStyleSheet(mqss);
ui->mode2btn->setStyleSheet(mqss);
ui->mode3btn->setStyleSheet(mqss);
ui->mode4btn->setStyleSheet(mqss);

qint32 i = 0;
for(i = 0;i < pltlastallstates.nowshowmodsum;i++)
{
  //mode btn text
  modbtnindex = i;
  SetBtnTextByHomeSwitch(pltlastallstates.iuimode[i]);
}
//recover active btn
modbtnindex = pltlastallstates.oribtnIndex;
ChangeModPic(pltlastallstates.nowshowmodsum,modbtnindex);
//cha and label and btn show/hide
for(i = pltlastallstates.nowshowmodsum;i < UIMODMAXNUM;i++)
{
  clobtnvec.at(i)->hide();
  nowmodebtn.at(i)->hide();
  modelabel.at(i)->hide();
}
if(1 == pltlastallstates.nowshowmodsum)
{
  ui->plusbtn->move(SPX + 1,SPY);
}
else
{
ui->plusbtn->move(SPX + (pltlastallstates.nowshowmodsum - 1) * STEPP,SPY);
}
return;
}

/**
 * @brief load all timer for different communication
 * @return under zero means error
 * @note only called once in constructor
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
 * @brief init connect sig and slot used inner
 * @note
 * @since {2018-12-14;c8-22}
*/
void BitPlatForm::ConnectAllSigSlot()
{
  QObject::connect(this, SIGNAL(PltFactorySig()), this, SLOT(PltFactorySet()));
  QObject::connect(this, SIGNAL(ModeSwitchSig(quint32)), this, SLOT(DoSwitchAction(quint32)));
  QObject::connect(HotplugManager::instance(),SIGNAL(sigTmcUsbPlugOut()),g_pPortUsb,SLOT(closeConn()));
  return;
}

/**
 * @brief init all resources when platform construct
 * @note
 * @since {2018-12-17:c01-18:c02-11;c02-27;c03-22;c05-23}
*/
void BitPlatForm::InitP()
{   
  remoteinterface::SetAnaModeHandle(&pltlastallstates.orimode);
  remoteinterface::SetPlatFormHandle(this);
  //ini ana mode
#ifdef _Linux_PLT_FDD
  pLtefddAna = new BitLteFdd(this);
  remoteinterface::SetRemoteFddHandle(pLtefddAna);
  pLtefddAna->setGeometry(QRect(PSTARTX,PSTARTY,PWIDTH,PHEIGHT));
  QObject::connect(pLtefddAna,SIGNAL(ZoomIn(bool)),this,SLOT(PlatZoomCtrl(bool)));
  QObject::connect(pLtefddAna,SIGNAL(SysSetSig()),this,SLOT(SysPanelCtrl()));
  QObject::connect(pLtefddAna,SIGNAL(MesPlatTitleSig(qint32)),this,SLOT(ChangeMeaTitle(qint32)));
  QObject::connect(pLtefddAna,SIGNAL(KeyEventSig(qint32)),this,SLOT(SetLocalUi(qint32)));
  QObject::connect(pLtefddAna,SIGNAL(PltAllPresetSig()),this,SLOT(PltFactorySet()));
  if(PTY4 != pltlastallstates.orimode)
    {
      pLtefddAna->hide();
    }
#else
  pLtefddAna = new QLabel(this);
  if(PTY4 != pltlastallstates.orimode)
    {
      pLtefddAna->hide();
    }
#endif

#ifdef _Linux_PLT_TDD
  pLtetddAna = new BitLteTdd(this);
  remoteinterface::SetRemoteTddHandle(pLtetddAna);
  pLtetddAna->setGeometry(QRect(PSTARTX,PSTARTY,PWIDTH,PHEIGHT));
  QObject::connect(pLtetddAna,SIGNAL(ZoomIn(bool)),this,SLOT(PlatZoomCtrl(bool)));
  QObject::connect(pLtetddAna,SIGNAL(SysSetSig()),this,SLOT(SysPanelCtrl()));
  QObject::connect(pLtetddAna,SIGNAL(MesPlatTitleSig(qint32)),this,SLOT(ChangeMeaTitle(qint32)));
  QObject::connect(pLtetddAna,SIGNAL(KeyEventSig(qint32)),this,SLOT(SetLocalUi(qint32)));
  QObject::connect(pLtetddAna,SIGNAL(PltAllPresetSig()),this,SLOT(PltFactorySet()));
  if(PTY5 != pltlastallstates.orimode)
    {
      pLtetddAna->hide();
    }
#else
  pLtetddAna = new QLabel(this);
  if(PTY5 != pltlastallstates.orimode)
    {
      pLtetddAna->hide();
    }
#endif

#ifdef _Linux_PLT_SA  
  pSaAna = new BitSA(this);
  remoteinterface::SetRemoteSaHandle(pSaAna);
  pSaAna->setGeometry(QRect(PSTARTX,PSTARTY,PWIDTH,PHEIGHT));
  QObject::connect(pSaAna,SIGNAL(ZoomIn(bool)),this,SLOT(PlatZoomCtrl(bool)));
  QObject::connect(pSaAna,SIGNAL(SysSetSig()),this,SLOT(SysPanelCtrl()));
  QObject::connect(pSaAna,SIGNAL(MesPlatTitleSig(qint32)),this,SLOT(ChangeMeaTitle(qint32)));
  QObject::connect(pSaAna,SIGNAL(KeyEventSig(qint32)),this,SLOT(SetLocalUi(qint32)));
  QObject::connect(pSaAna->pcontrolInterface,SIGNAL(signalZeroCalComplete(bool)),this,SLOT(QuitZeroCalc(bool)));
  QObject::connect(pSaAna,SIGNAL(PltAllPresetSig()),this,SLOT(PltFactorySet()));
  QObject::connect(pSaAna->pcontrolInterface,SIGNAL(sendSCPIcmd(QString)),this,SLOT(on_sendSCPIcmd(QString)));
  if(PTY0 != pltlastallstates.orimode)
    {
      pSaAna->hide();
    }
#else
  pSaAna = new QLabel(this);
  if(PTY0 != pltlastallstates.orimode)
    {
      pSaAna->hide();
    }
#endif

#ifdef _Linux_PLT_RTSA
  pRtsaAna = new RtSaRemote(this);
  remoteinterface::SetRemoteRtsaHandle(pRtsaAna);
  pRtsaAna->setGeometry(QRect(PSTARTX,PSTARTY,PWIDTH,PHEIGHT));
  QObject::connect(pRtsaAna,SIGNAL(ZoomIn(bool)),this,SLOT(PlatZoomCtrl(bool)));
  QObject::connect(pRtsaAna,SIGNAL(SysSetSig()),this,SLOT(SysPanelCtrl()));
  QObject::connect(pRtsaAna,SIGNAL(MesPlatTitleSig(qint32)),this,SLOT(ChangeMeaTitle(qint32)));
  QObject::connect(pRtsaAna,SIGNAL(KeyEventSig(qint32)),this,SLOT(SetLocalUi(qint32)));
  QObject::connect(pRtsaAna,SIGNAL(PltAllPresetSig()),this,SLOT(PltFactorySet()));
  if(PTY1 != pltlastallstates.orimode)
    {
      pRtsaAna->hide();
    }
#else
  pRtsaAna = new QLabel(this);
  if(PTY1 != pltlastallstates.orimode)
    {
      pRtsaAna->hide();
    }
#endif

  pInterAna = pSaAna;
  pPowerAna = pSaAna;

#ifdef _Linux_PLT_FGNR
  pFgnrAna = new BitNr(this);
  remoteinterface::SetRemoteFgnrHandle(pFgnrAna);
  pFgnrAna->setGeometry(QRect(PSTARTX,PSTARTY,PWIDTH,PHEIGHT));
  QObject::connect(pFgnrAna,SIGNAL(ZoomIn(bool)),this,SLOT(PlatZoomCtrl(bool)));
  QObject::connect(pFgnrAna,SIGNAL(SysSetSig()),this,SLOT(SysPanelCtrl()));
  QObject::connect(pFgnrAna,SIGNAL(MesPlatTitleSig(qint32)),this,SLOT(ChangeMeaTitle(qint32)));
  QObject::connect(pFgnrAna,SIGNAL(KeyEventSig(qint32)),this,SLOT(SetLocalUi(qint32)));
  QObject::connect(pFgnrAna,SIGNAL(PltAllPresetSig()),this,SLOT(PltFactorySet()));
  if(PTY6 != pltlastallstates.orimode)
    {
      pFgnrAna->hide();
    }
#else
  pFgnrAna = new QLabel(this);
  if(PTY5 != pltlastallstates.orimode)
    {
      pFgnrAna->hide();
    }
#endif

  //add widget handle by RUNMODE order
  modewidvec.append(pSaAna);
  modewidvec.append(pRtsaAna);
  modewidvec.append(pInterAna);
  modewidvec.append(pPowerAna);
  modewidvec.append(pLtefddAna);//fdd
  modewidvec.append(pLtetddAna);//tdd
  modewidvec.append(pFgnrAna);//fgnr

#ifdef _Linux_PLT_ALL
  modeintervec.append(pSaAna);
  modeintervec.append(pRtsaAna);
  modeintervec.append(pInterAna);
  modeintervec.append(pPowerAna);
  modeintervec.append(pLtefddAna);
  modeintervec.append(pLtetddAna);
  modeintervec.append(pFgnrAna);
#else
  modeintervec.append(pSaAna);
  modeintervec.append(pSaAna );
  modeintervec.append(pSaAna);
  modeintervec.append(pSaAna);
  modeintervec.append(pSaAna);
  modeintervec.append(pSaAna);
  modeintervec.append(pSaAna);
#endif

  //when do switch action show
  pswitchwid = new switmod(this);
  pswitchwid->hide();
  //for setting phy after up such as gps\lcdbrightness
  pSetWid = new setwid(&pltsystate,&pltlastallstates,0);
  modewidvec.at(pltlastallstates.orimode)->setFocus();
  wavmap.insert(PTY0,"beep_1.wav");
  wavmap.insert(PTY1,"beep_2.wav");
  wavlen = wavmap.count();
  return;
}

/**
 * @brief release new widgets obj
 * @note [should let mode thread stop first]
 * @since {2018-12-18;c02-25;c02-27}
*/
void BitPlatForm::DeleteW()
{
    if(pSetWid)
    {
        delete pSetWid;
        pSetWid = 0;
    }
    if(pswitchwid)
    {
        delete pswitchwid;
        pswitchwid = 0;
    }
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
 * @since {2019-01-04:c01-18;c:03-21}
*/
qint32 BitPlatForm::GetModeNum(QString &str)
{
  QString tempstr = str.mid(INDEXBASE,str.indexOf(BitPlatForm::regchar));
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
 * @since {2019-01-24}
*/
qint32 BitPlatForm::HomeModeExistornot(quint32 ihmode)
{
  qint32 i = 0;
  quint32 j = 0;
  qint32 iIndex = -1;
  qint32 iSum = NONEMODE;
  for(i = 0;i < pltlastallstates.nowshowmodsum;i++)
    {
      QString tempstr = nowmodetext.at(i).mid(INDEXBASE,nowmodetext.at(i).indexOf(BitPlatForm::regchar));
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
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-09-06}
*/
void BitPlatForm::GpsPltdisMod(qint32 imode, qint32 enflag)
{
  if(enflag)
    {
      if(PTY0 == imode)
        {
          ui->label_3->setPixmap(QPixmap(QString::fromUtf8(":/bit/image/icn_gps.png")));
          ui->gpslabel->setStyleSheet("color:rgb(255,255,255)");
        }
      else if(PTY1 == imode)
        {
          ui->label_3->setPixmap(QPixmap(QString::fromUtf8(":/bit/image/icn_gps.png")));
          ui->gpslabel->setStyleSheet("color:rgb(255,255,255)");
        }
      else if(PTY2 == imode)
        {
          ui->label_3->setPixmap(QPixmap(QString::fromUtf8(":/bit/image/icn_gps_night.png")));
          ui->gpslabel->setStyleSheet("color:rgb(251,219,167)");
        }
    }
  else
    {
      if(PTY0 == imode)
        {
          ui->label_3->setPixmap(QPixmap(QString::fromUtf8(":/bit/image/icn_gps_disable.png")));
          ui->gpslabel->setStyleSheet("color:rgb(136,136,136)");
        }
      else if(PTY1 == imode)
        {
          ui->label_3->setPixmap(QPixmap(QString::fromUtf8(":/bit/image/icn_gps_disable.png")));
          ui->gpslabel->setStyleSheet("color:rgb(136,136,136)");
        }
      else if(PTY2 == imode)
        {
          ui->label_3->setPixmap(QPixmap(QString::fromUtf8(":/bit/image/icn_gps_disable_night.png")));
          ui->gpslabel->setStyleSheet("color:rgb(251,219,167)");
        }
    }
}

void BitPlatForm::CtrlModePltdis(qint32 imode, qint32 ictrl)
{
  //remote
  if(ictrl)
    {
      if(PTY0 == imode)
        {
          ui->label_4->setPixmap(QPixmap(QString::fromUtf8(":/bit/image/icn_remote.png")));
        }
      else if(PTY1 == imode)
        {
          ui->label_4->setPixmap(QPixmap(QString::fromUtf8(":/bit/image/icn_remote.png")));
        }
      else if(PTY2 == imode)
        {
          ui->label_4->setPixmap(QPixmap(QString::fromUtf8(":/bit/image/icn_night_mode.png")));
        }
    }
  else
    {
      if(PTY0 == imode)
        {
          ui->label_4->setPixmap(QPixmap(QString::fromUtf8(":/bit/image/icn_local.png")));
        }
      else if(PTY1 == imode)
        {
          ui->label_4->setPixmap(QPixmap(QString::fromUtf8(":/bit/image/icn_local.png")));
        }
      else if(PTY2 == imode)
        {
          ui->label_4->setPixmap(QPixmap(QString::fromUtf8(":/bit/image/ICN-LOCAL_night.png")));
        }
    }
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-09-06}
*/
void BitPlatForm::BatPicPltdis(qint32 imode)
{
  if(PTY0 == imode)
    {
      battpicvec.replace(PTY0,NOBATPIC);
      battpicvec.replace(PTY1,CHARGEPIC);
      battpicvec.replace(PTY2,DISCHARGEPIC);
      battpicvec.replace(PTY3,FULLPIC);
    }
  else if(PTY1 == imode)
    {
      battpicvec.replace(PTY0,NOBATPIC);
      battpicvec.replace(PTY1,CHARGEPIC);
      battpicvec.replace(PTY2,DISCHARGEPIC);
      battpicvec.replace(PTY3,FULLPIC);
    }
  else if(PTY2 == imode)
    {
      battpicvec.replace(PTY0,NOBATPICNIGHT);
      battpicvec.replace(PTY1,CHARGEPICNIGHT);
      battpicvec.replace(PTY2,DISCHARGEPICNIGHT);
      battpicvec.replace(PTY3,FULLPICNIGHT);
    }
  qint32 ilen = 0;
  qint32 i = 0;
  qint32 iunit = 0;
//  switch (shmengine::getsingleshm()->pshm_sysinfo->BatterChargeStatus)
//    {
//    case UN_BATT:
//      ui->batpiclabel->setPixmap(QPixmap(QString::fromUtf8(battpicvec.at(PTY0)[INDEXBASE])/*(NOBATPIC[INDEXBASE])*/));
//      ui->batterylabel->setText(tr("NBat"));
//      break;
//    case BATT_CHARGE:
//      batnum = shmengine::getsingleshm()->pshm_sysinfo->BatteryRemaind;
//      batnum = batnum > 100 ? 100 : batnum;
//      ilen = sizeof(CHARGEREMAIN) / sizeof(quint32);
//      iunit = ilen - 1;
//      i = 0;
//      for(i = 0;i < ilen;i++)
//        {
//          if(batnum < CHARGEREMAIN[i])
//            {
//              iunit = i;
//              break;
//            }
//        }
//      ui->batpiclabel->setPixmap(QPixmap(QString::fromUtf8(battpicvec.at(PTY1)[iunit]/*CHARGEPIC[iunit]*/)));
//      batterystr = QString::number(batnum) + "%";
//      ui->batterylabel->setText(batterystr);
//      break;
//    case BATT_DISCHARGE:
//      batnum = shmengine::getsingleshm()->pshm_sysinfo->BatteryRemaind;
//      batnum = batnum > 100 ? 100 : batnum;
//      ilen = sizeof(DISCHARGEREMIAN) / sizeof(quint32);
//      i = 0;
//      for(i = ilen - 1;i >= 0;i--)
//        {
//          if(batnum > DISCHARGEREMIAN[i])
//            {
//              iunit = i;
//              break;
//            }
//        }
//      ui->batpiclabel->setPixmap(QPixmap(QString::fromUtf8(battpicvec.at(PTY2)[iunit]/*DISCHARGEPIC[iunit]*/)));
//      batterystr = QString::number(batnum) + "%";
//      ui->batterylabel->setText(batterystr);
//      break;
//    case BATT_FULL:
//      ui->batterylabel->setText("100%");
//      ui->batpiclabel->setPixmap(QPixmap(QString::fromUtf8(battpicvec.at(PTY3)[INDEXBASE]/*FULLPIC[INDEXBASE]*/)));
//      break;
//    default:
//      break;
//    }
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-09-10}
*/
void BitPlatForm::TopTabPicdis(qint32 imode)
{
  if(PTY0 == imode)
    {
      toppicvec.replace(PTY0,TOPMENU_1);
      toppicvec.replace(PTY1,TOPMENU_2);
      toppicvec.replace(PTY2,TOPMENU_3);
      toppicvec.replace(PTY3,TOPMENU_4);
    }
  else if(PTY1 == imode)
    {
      toppicvec.replace(PTY0,TOPMENU_1);
      toppicvec.replace(PTY1,TOPMENU_2);
      toppicvec.replace(PTY2,TOPMENU_3);
      toppicvec.replace(PTY3,TOPMENU_4);
    }
  else if(PTY2 == imode)
    {
      toppicvec.replace(PTY0,TOPMENU_night_1);
      toppicvec.replace(PTY1,TOPMENU_night_2);
      toppicvec.replace(PTY2,TOPMENU_night_3);
      toppicvec.replace(PTY3,TOPMENU_night_4);
    }
  ChangeModPic(pltlastallstates.nowshowmodsum,pltlastallstates.oribtnIndex);
}

/**
 * @brief close ctrl app
 * @param[in] modetype one of ana mode,same with RUNMODE
 * @return under zero means error
 * @note
 * @since {2018-12-14:c02-12:c04-10}
*/
bool BitPlatForm::CloseCtrlApp(quint32 modetype)
{
  //setting shm
  if(modetype >= BitPlatForm::modesumnum)
    return false;
  if(modetype <= RTSA_MODE)
    {
//      *shmengine::getsingleshm()->pctrlexitvec.at(modetype) = BEXIT;
      QString mstr = gloadctrlparam.pctrlpathvec.at(modetype);
      //for auto exit
      QThread::msleep(MAINBACKT);
      //for clear resource
      processvec.at(modetype)->close();
      return processvec.at(modetype)->waitForFinished(CTRLUPOVERTIME);
    }
  else
    {
      if(modetype == LTE_FDD_MODE || modetype == LTE_TDD_MODE || modetype == FIVE_G_NR)
        {
          processvec.at(modetype)->close();
          return processvec.at(modetype)->waitForFinished(CTRLUPOVERTIME);
        }
    }
  return true;
}

/**
 * @brief when switch mode to show pic and finish to close
 * @param[in] action 0 means close pic,1 means open pic
 * @return under zero means error
 * @note
 * @since {2018-12-14;c06-04}
*/
qint32 BitPlatForm::CutSwitchPic(quint32 action)
{
  while(timerstate){};
//  shmengine::getsingleshm()->pshm_sysconf->PicSwitch = action;
  //lcd lock
  if(PTY1 == touchstate)
    {
//      shmengine::getsingleshm()->pshm_sysconf->TouchScreen = PTY0;
//      shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_TouchScreen | PLT_IXS_SwitchPic);
      return 0;
    }
//  shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_SwitchPic);
  return 0;
}

/**
 * @brief hide before mode gui
 * @param[in] modetype one of ana mode
 * @note
 * @since {2018-12-14}
*/
void BitPlatForm::HideModeGui(quint32 modetype)
{  
  if(modetype >= BitPlatForm::modesumnum)
    return;
  modewidvec.at(modetype)->hide();
  return;
}

/**
 * @brief burn .bit file
 * @param[in] modetype one of ana mode
 * @return under zero means error
 * @note [this part put in sysctrlapp better]
 * @since {2018-12-14:c02-13}
*/
qint32 BitPlatForm::FlashBitStream(quint32 modetype)
{  
  if(modetype >= BitPlatForm::modesumnum)
    return -1;
  while(timerstate){};
  BURN_STATE = POFF;
  usleep(BURNTIME);
//  shmengine::getsingleshm()->pshm_sysconf->Convertflag = PON;
//  shmengine::getsingleshm()->pshm_sysconf->AnaMode = modetype;
//  shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_BurnAction);
  qint32 itime = 0;
//  while(shmengine::getsingleshm()->pshm_sysconf->Convertflag)
//  {
//      itime++;
//      if(itime > BURNTIMEOUT)
//      {
//          qCritical()<<"shm:"<<shmengine::getsingleshm()->pshm_sysaction->system_flag_conf<<";"<<"state:"<<shmengine::getsingleshm()->pshm_sysconf->Convertflag;
//          break;
//      }
//      usleep(SYSINTER);
//  }
  BURN_STATE = PON;
  return 0;
}

/**
 * @brief show now mode gui
 * @param[in] modetype one of ana mode
 * @note
 * @since {2018-12-14}
*/
void BitPlatForm::ShowModeGui(quint32 modetype)
{
  if(modetype >= BitPlatForm::modesumnum)
    return;
  modewidvec.at(modetype)->show();
  this->repaint();
  return;
}

/**
 * @brief start now mode ctrl app
 * @param[in] modetype one of ana mode
 * @return  under zero means error
 * @note
 * @since {2018-12-14}
*/
bool BitPlatForm::StartCtrlApp(quint32 modetype)
{
  if(modetype >= BitPlatForm::modesumnum)
    return false;
  QString mstr = gloadctrlparam.pctrlpathvec.at(modetype);
  if(mstr != "bit")
    {
      processvec.at(modetype)->start(mstr,QStringList(mstr));
      processvec.at(modetype)->waitForStarted(CTRLUPOVERTIME);
    }
  return true;
}

/**
 * @brief for release debug redirect log
 * @param[in]
 * @param[in]
 * @param[in]
 * @note
 * @since {2018-12-19}
*/
void BitPlatForm::bitRedirectHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
  QTextStream logstream(&BitPlatForm::logfile);
  QString logtime = QDateTime::currentDateTime().toString("yyyy-MM-dd APhh:mm:ss");
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
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-03-05}
*/
void BitPlatForm::CloseAnaWigInherit(qint32 imod)
{  
  modeintervec.at(imod)->MenuClose();
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-03-07}
*/
void BitPlatForm::ChangeModeMeasure(qint32 imod,qint32 imea)
{  
  modeintervec.at(imod)->SetMeasureItems(imea);
  return;
}

/**
 * @brief for remote to tell any ana mode
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-05-14;c:08-30}
*/
void BitPlatForm::ChangeModeLR(qint32 imod,qint32 ilr)
{  
  qint32 i = 0;
  for(i = 0;i < NONEMODE;i++)
    {
      modeintervec.at(imod)->SetLocalRemoteMode(ilr);
    }
  return;
}

/**
 * @brief when timer receive home switch or platform itself then to send sig
 * @param[in] switchtype running mode type old
 * @note called by multi different switch mode
 * @since {2018-12-14:c02-12;c03-05;c08-27}
*/
void BitPlatForm::DoSwitchAction(quint32 switchtype)
{  
  QObject::disconnect(HotplugManager::instance(),SIGNAL(sigTmcUsbPlugOut()),g_pPortUsb,SLOT(closeConn()));
  g_pPortUsb->ReleaseMiniUsb();
  delete g_pPortUsb;
  g_pPortUsb = NULL;

  pSetWid->pnetsetwid->SetWifiOn(false);

  CloseAnaWigInherit(switchtype);
  //  pswitchwid->show();
  //  pswitchwid->repaint();
  //close before mode ctrl app
  CloseCtrlApp(switchtype);
  HideModeGui(switchtype);
  //tell sec FPGA to cut picture,this func put in sysctrlapp
  if(CutSwitchPic(PON) < 0)
    {
      return;
    }
//  switchtype = shmengine::getsingleshm()->pshm_home->modetype;
  //flash bitstream
  if(FlashBitStream(switchtype) < 0)
    {
      return;
    }

  //tell sec FPGA to cut picture
  if(CutSwitchPic(POFF) < 0)
    {
      return;
    }
  //  pswitchwid->hide();
  //show now ui mode
//  ShowModeGui(shmengine::getsingleshm()->pshm_home->modetype);
  //start now ctrl app
  StartCtrlApp(switchtype);

  g_pPortUsb = new ScpiPort_usb();
  QObject::connect(HotplugManager::instance(),SIGNAL(sigTmcUsbPlugOut()),g_pPortUsb,SLOT(closeConn()));
  //reflesh platform tab msg,do this outside
  //should last reflesh
//  pltlastallstates.orimode = shmengine::getsingleshm()->pshm_home->modetype;
  return;
}

/**
 * @brief
 * @param[in]flag when true zoom out else zoom in
 * @param[in]
 * @return
 * @note
 * @since {2019-01-09}
*/
void BitPlatForm::PlatZoomCtrl(bool flag)
{
  if(flag)
    {
      modewidvec.at(pltlastallstates.orimode)->setGeometry((QRect(INDEXBASE,INDEXBASE,PWIDTH,PHEIGHT + MAXDETA)));
    }
  else
    {
      modewidvec.at(pltlastallstates.orimode)->setGeometry((QRect(PSTARTX,PSTARTY,PWIDTH,PHEIGHT)));
    }
  return;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {c:2019-02-26}
*/
void BitPlatForm::on_mode1btn_clicked()
{  
  //remote mode not respond
  if(loreflag)
    {
      return;
    }
  modbtnindex = INDEXBASE;
  pltlastallstates.oribtnIndex = modbtnindex;
  QString mstr = ui->label_5->text();
//  shmengine::getsingleshm()->pshm_home->modetype = GetModeNum(mstr);
//  if(pltlastallstates.orimode != shmengine::getsingleshm()->pshm_home->modetype)
//    {
//      DoSwitchAction(pltlastallstates.orimode);
//      pltlastallstates.iuimode[0] = pltlastallstates.orimode;
//      ChangeModPic(pltlastallstates.nowshowmodsum,INDEXBASE);
//    }
  return;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {c:2019-02-26}
*/
void BitPlatForm::on_mode2btn_clicked()
{
  //remote mode not respond
  if(loreflag)
    {
      return;
    }
  modbtnindex = INDEXBASE + 1;
  pltlastallstates.oribtnIndex = modbtnindex;
  QString mstr = ui->label_6->text();
//  shmengine::getsingleshm()->pshm_home->modetype = GetModeNum(mstr);
//  if(pltlastallstates.orimode != shmengine::getsingleshm()->pshm_home->modetype)
//    {
//      DoSwitchAction(pltlastallstates.orimode);
//      pltlastallstates.iuimode[1] = pltlastallstates.orimode;
//      ChangeModPic(pltlastallstates.nowshowmodsum,INDEXBASE + 1);
//    }
  return;
}

void BitPlatForm::on_mode3btn_clicked()
{
  //remote mode not respond
  if(loreflag)
    {
      return;
    }
  modbtnindex = INDEXBASE + 2;
  pltlastallstates.oribtnIndex = modbtnindex;
  QString mstr = ui->label_7->text();
//  shmengine::getsingleshm()->pshm_home->modetype = GetModeNum(mstr);
//  if(pltlastallstates.orimode != shmengine::getsingleshm()->pshm_home->modetype)
//    {
//      DoSwitchAction(pltlastallstates.orimode);
//      pltlastallstates.iuimode[2] = pltlastallstates.orimode;
//      ChangeModPic(pltlastallstates.nowshowmodsum,INDEXBASE + 2);
//    }
  return;
}

void BitPlatForm::on_mode4btn_clicked()
{
  //remote mode not respond
  if(loreflag)
    {
      return;
    }
  modbtnindex = INDEXBASE + 3;
  pltlastallstates.oribtnIndex = modbtnindex;
  QString mstr = ui->label_8->text();
//  shmengine::getsingleshm()->pshm_home->modetype = GetModeNum(mstr);
//  if(pltlastallstates.orimode != shmengine::getsingleshm()->pshm_home->modetype)
//    {
//      DoSwitchAction(pltlastallstates.orimode);
//      pltlastallstates.iuimode[3] = pltlastallstates.orimode;
//      ChangeModPic(pltlastallstates.nowshowmodsum,INDEXBASE + 3);
//    }
  return;
}

void BitPlatForm::on_plusbtn_clicked()
{  
  //remote mode not respond
  if(loreflag)
    {
      return;
    }
  return  PlusBtnCtrl();
}

/**
 * @brief when switch or add or delete one mode,change pic
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-02-26}
*/
void BitPlatForm::ChangeModPic(qint32 isum, qint32 imod)
{
  ui->toplabel->setPixmap(QPixmap(QString::fromUtf8(toppicvec.at(isum - 1)[imod])));
  //  if(UIMODMAXNUM == isum)
  //    {
  //      ui->toplabel->setPixmap(QPixmap(QString::fromUtf8(TOPMENU_4[imod])));
  //    }
  //  else if(UIMODMAXNUM - 1 == isum)
  //    {
  //      ui->toplabel->setPixmap(QPixmap(QString::fromUtf8(TOPMENU_3[imod])));
  //    }
  //  else if(UIMODMAXNUM - 2 == isum)
  //    {
  //      ui->toplabel->setPixmap(QPixmap(QString::fromUtf8(TOPMENU_2[imod])));
  //    }
  //  else
  //    {
  //      ui->toplabel->setPixmap(QPixmap(QString::fromUtf8(TOPMENU_1[imod])));
  //    }
  return;
}

/**
 * @brief maybe close valid mode or not
 * @param[in]
 * @param[in]
 * @return
 * @note left side as to switch mode when close valid mode
 * @since {c:2019-02-26}
*/
void BitPlatForm::on_chafir_clicked()
{
  //remote mode not respond
  if(loreflag)
    {
      return;
    }
  return CloseAnaMode(INDEXBASE);
}

void BitPlatForm::on_chasec_clicked()
{  
  //remote mode not respond
  if(loreflag)
    {
      return;
    }
  return CloseAnaMode(INDEXBASE + 1);
}

void BitPlatForm::on_chathird_clicked()
{
  //remote mode not respond
  if(loreflag)
    {
      return;
    }
  return CloseAnaMode(INDEXBASE + 2);
}

void BitPlatForm::on_chafourth_clicked()
{  
  //remote mode not respond
  if(loreflag)
    {
      return;
    }
  return CloseAnaMode(INDEXBASE + 3);
}

/**
 * @brief called by cha and scpi inner
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-02-26;c:05-21}
*/
void BitPlatForm::CloseAnaMode(qint32 imod)
{
  CloseBtnCtrl(imod);
  //do switch action
  if(imod == modbtnindex)
    {
      //switch to left switch
      modbtnindex--;
      modbtnindex = modbtnindex < 0 ? INDEXBASE : modbtnindex;
      pltlastallstates.oribtnIndex = modbtnindex;
      ChangeModPic(pltlastallstates.nowshowmodsum,modbtnindex);
      QString tempstr = modelabel.at(modbtnindex)->text();
//      shmengine::getsingleshm()->pshm_home->modetype = GetModeNum(tempstr);
      DoSwitchAction(pltlastallstates.orimode);
    }
  //not switch
  else
    {
      if(modbtnindex > imod)
        {
          modbtnindex--;
          pltlastallstates.oribtnIndex = modbtnindex;
        }
      ChangeModPic(pltlastallstates.nowshowmodsum,modbtnindex);
    }
  return;
}

/**
 * @brief for remote to local ctrl
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-05-15;c05-29;c06-04;c08-16}
*/
void BitPlatForm::keyPressEvent(QKeyEvent *event)
{
  if(Qt::Key_PowerOff == event->key())
    {
      if(!event->isAutoRepeat())
        {
          SaveAllModeWhenShutOff(pltsystate.powerstate);
          system(BitPlatForm::syncpath);
          ui->timelabel->setText(tr("Ready to shut off..."));
        }
      return;
    }
  if(loreflag)
    {
      if(Qt::Key_Escape == event->key())
        {
          SetLocalUi(Qt::Key_Escape);
        }
    }
  else
    {
      if(Qt::Key_PowerOff != event->key())
        {
          //when focus in platform to send key event to now running ana mode
          QApplication::sendEvent(modewidvec.at(pltlastallstates.orimode),event);
        }
      if(Qt::Key_Escape == event->key() && !pSetWid->isHidden())
        {
          pSetWid->hide();
        }
    }
  return;
}

/**
 * @brief when receive short power off event to save all states
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-05-29;c06-01}
*/
void BitPlatForm::SaveAllModeWhenShutOff(qint32 ireset)
{  
  QFile pltprefile("/mnt/bitup");
  if (pltprefile.open(QIODevice::ReadWrite))
    {
      QTextStream stream(&pltprefile);
      //default states
      if(PTY0 == ireset)
        {
          stream << QString::number(PTY0) << endl;
        }
      else
        {
          stream << QString::number(pltlastallstates.orimode) << endl;
        }
    }
  if(!pltprefile.flush())
    {

    }

  pltprefile.close();
  PltSaveDevelopMsg();
  PltSavePreStates();
  PltSaveStates(ireset);
  return;
}

/**
 * @brief through remote to close ana mode
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-03-01;c05-22}
*/
void BitPlatForm::CloseAnaModeR(qint32 imode)
{
  if(imode < 0 || imode >= NONEMODE)
    {
      return;
    }
  QString mstr = modbtntext[imode];
  if(pltlastallstates.nowshowmodsum > 1)
    {
      qint32 iIndex = NowModExitor(mstr);
      if(iIndex < UIMODMAXNUM && iIndex >= 0)
        {
          CloseAnaMode(iIndex);
        }
    }
  return;
}

/**
 * @brief for every mode and home to call system setting panel
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-02-25;c08-15}
*/
void BitPlatForm::SysPanelCtrl()
{
  if(NULL == pSetWid)
    {
      pSetWid = new setwid(&pltsystate,&pltlastallstates,0);
    }
  pSetWid->setGeometry(mapToGlobal(QPoint(0,0)).x(),mapToGlobal(QPoint(0,0)).y(),this->width(),this->height() - MMD);
  pSetWid->show();
  pSetWid->activateWindow();
  return;
}

/**
 * @brief when select measurement from mode itself should send sig
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-03-22}
*/
void BitPlatForm::ChangeMeaTitle(qint32 iIndex)
{
  pltlastallstates.iallmesa[pltlastallstates.orimode] = iIndex;
  SetBtnTextByHomeSwitch(pltlastallstates.orimode);
  FillConstText();
  return;
}

/**
 * @brief for scpi and inner to call for cha btn hide or show
 * @param[in]inum index from left to right start from 0
 * @param[in]
 * @return
 * @note
 * @since {2019-01-17;c02-26;c03-21;c05-22}
*/
void BitPlatForm::CloseBtnCtrl(qint32 iIndex)
{  
  pltlastallstates.nowshowmodsum--;
  clobtnvec.at(pltlastallstates.nowshowmodsum)->hide();
  nowmodebtn.at(pltlastallstates.nowshowmodsum)->hide();
  modelabel.at(pltlastallstates.nowshowmodsum)->hide();
  if(1 == pltlastallstates.nowshowmodsum)
    {
      clobtnvec.at(INDEXBASE)->hide();
    }

  //forward to move mode text one by one
  qint32 i = 0;
  for(i = iIndex;i < pltlastallstates.nowshowmodsum;i++)
  {
      modelabel.at(i)->setText(modelabel.at(i + 1)->text());
      pltlastallstates.iuimode[i] = pltlastallstates.iuimode[i + 1];
  }
  modelabel.at(pltlastallstates.nowshowmodsum)->setText("--");

  if(1 == pltlastallstates.nowshowmodsum)
  {
      ui->plusbtn->move(SPX + 1,SPY);
  }
  else
  {
      ui->plusbtn->move(SPX + (pltlastallstates.nowshowmodsum - 1) * STEPP,SPY);
  }
  FillConstText();
  return;
}

/**
 * @brief for plus mode
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-01-17:c01-24:c01-25;c02-26;c02-27;c03-01;c09-10}
*/
void BitPlatForm::PlusBtnCtrl()
{
  //  if(pltlastallstates.nowshowmodsum >= UIMODMAXNUM)
  //    {
  //      return;
  //    }
  if(NULL == pPlusDia)
    {
      //all modes measure items index will reflesh when setting moment
      //so here doesn't collect but uses directly
      memcpy(pltlastallstates.ilastallmesa,pltlastallstates.iallmesa,sizeof(pltlastallstates.ilastallmesa));
//      pPlusDia = new plusmode(this,&shmengine::getsingleshm()->pshm_home->modetype,pltlastallstates.iallmesa,NONEMODE);
//      pPlusDia->SetPlusDisMode(pltlastallstates.dismod);
//      pPlusDia->exec();
//      if(loreflag)
//        {
//          delete pPlusDia;
//          this->repaint();
//          pPlusDia = NULL;
//          return;
//        }
//      QString smod = pPlusDia->getmodstr();
//      qint32 iaction = pPlusDia->getdostate();
//      delete pPlusDia;
//      this->repaint();
//      pPlusDia = NULL;
//      if(iaction)
//        {
//          PartWtichMode(smod);
//        }
    }
  return;
}

/**
 * @brief for scpi to switch mode
 * @param[in]
 * @param[in]
 * @return
 * @note remote use
 * @since {2019-03-01}
*/
void BitPlatForm::SwitchAnaMode(qint32 imode, qint32 imeas)
{
  if(imode < 0 || imode >= NONEMODE)
  {
      return;
  }
  //pltlastallstates.iallmesa
  memcpy(pltlastallstates.ilastallmesa,pltlastallstates.iallmesa,sizeof(pltlastallstates.ilastallmesa));
  //shmengine::getsingleshm()->pshm_home->modetype = imode;
  QString mstr = modbtntext[imode] + QObject::tr("<BR/><span style=\"font-weight:normal;\">%1</span>").arg(GetMeasIteamsNum(imode,imeas));
  PartWtichMode(mstr);
  return;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-03-01;c:03-05,c:05-14}
*/
void BitPlatForm::SetRemoteUi()
{
  loreflag = PON;
//  shmengine::getsingleshm()->pshm_home->remotecloseflag = PON;
  CtrlModePltdis(pltlastallstates.dismod,loreflag);
  CloseAnaWigInherit(pltlastallstates.orimode);
  ChangeModeLR(pltlastallstates.orimode,PON);
  //close widgets
  if(pSetWid)
    {
      if(!pSetWid->isHidden())
        {
          pSetWid->hide();
        }
    }
  if(pPlusDia)
    {
      pPlusDia->close();
    }
  ui->plusbtn->setEnabled(false);
  return;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-03-01;c04-19;c05-29;c06-04}
*/
void BitPlatForm::SetLocalUi(qint32 ival)
{  
  qint32 ilock = PTY0;
  if(Qt::Key_PowerOff == ival)
    {
      //save all states
      SaveAllModeWhenShutOff(pltsystate.powerstate);
      system(BitPlatForm::syncpath);
      ui->timelabel->setText(tr("ana mode to shut off"));
      return;
    }
  //local
  else if(Qt::Key_Escape == ival)
    {
      loreflag = POFF;
//      shmengine::getsingleshm()->pshm_home->remotecloseflag = POFF;
      CtrlModePltdis(pltlastallstates.dismod,loreflag);
      ui->plusbtn->setEnabled(true);
      ChangeModeLR(pltlastallstates.orimode,POFF);
      touchstate = PTY0;
      ilock = PTY0;
    }
  //lock touch screen
  else if(Qt::Key_Escape + 1 == ival)
    {
//    shmengine::getsingleshm()->pshm_sysconf->TouchScreen = PTY0;
//    shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_TouchScreen);
      touchstate = PTY1;
      ilock = PTY1;
    }
  //unlock touch screen
  else if(Qt::Key_Escape + 2 == ival)
    {
//    shmengine::getsingleshm()->pshm_sysconf->TouchScreen = PTY1;
//    shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_TouchScreen);
      touchstate = PTY2;
      ilock = PTY1;
    }
  //local and unlock
  else if(Qt::Key_Escape + 3 == ival)
    {
      loreflag = POFF;
//    shmengine::getsingleshm()->pshm_home->remotecloseflag = POFF;
      ui->label_4->setPixmap(QPixmap(QString::fromUtf8(":/bit/image/icn_local.png")));
      ui->plusbtn->setEnabled(true);
      ChangeModeLR(pltlastallstates.orimode,POFF);

//    shmengine::getsingleshm()->pshm_sysconf->TouchScreen = PTY1;
//    shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_TouchScreen);
      touchstate = PTY3;
      ilock = PTY1;
    }

  //to change other mode ui and inner states
  if(ilock)
  {
      SetLockUiStates(pltlastallstates.orimode,touchstate);
  }
  return;
}


/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-06-10}
*/
void BitPlatForm::QuitZeroCalc(bool bl)
{
  if(NULL != pSetWid && NULL != pSetWid->pfilemanaowid->pnoticwid)
    {
      pSetWid->pfilemanaowid->pnoticwid->StopZeroCalc(bl);
    }
}

/**
 * @brief for preset recovery
 * @param[in]
 * @param[in]
 * @return
 * @note this function should provide two selections for now only or all mode,
 * @since {2019-08-22}
*/
void BitPlatForm::PltFactorySet()
{
  //close valid setting wid first
  CloseAnaWigInherit(pltlastallstates.orimode);
  qint32 isall = 0;//1 means all to recovery,for append use
  //first preset valid ana mode

  modeintervec.at(pltlastallstates.orimode)->PresetDefaultStates();
  if(isall)
    {
      qint32 i = 0;
      for(i = 0;i < NONEMODE;i++)
        {
          if(i != pltlastallstates.orimode)
            {

            }
        }
    }
  //plt recovery
  PltSysPlugFactory();
  return;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-08-22}
*/
void BitPlatForm::PltSysPlugFactory()
{
  PLTSTATEPARAM mpltlastallstates;
  QFile mpltdefaultfile("plt_default.cond");
  mpltdefaultfile.open(QIODevice::ReadOnly);
  qint32 iwnum = mpltdefaultfile.read((char*)&mpltlastallstates,sizeof(PLTSTATEPARAM));
  mpltdefaultfile.close();

  SetSysVolume(mpltlastallstates.soundnum);
  usleep(CLOTIME);
  SetSysVolSwitch(mpltlastallstates.soundswitch);
  usleep(CLOTIME);
  SetSysLcdBri(mpltlastallstates.lcdbright);
  usleep(CLOTIME);
  SetSysDateType(mpltlastallstates.datetype);
  SetSysSleepT(mpltlastallstates.sleept);
  SetGpsEnable(mpltlastallstates.gpswitch);
  usleep(CLOTIME);
  SetSysRef(mpltlastallstates.freqref);
  usleep(CLOTIME);
  SetSysKeyBeep(mpltlastallstates.gkeybeepswitch);
  usleep(CLOTIME);
  SetSysIpAddr(mpltlastallstates.ipstr);
  SetSysMaskAddr(mpltlastallstates.maskstr);
  SetSysGateAddr(mpltlastallstates.gatewaystr);
  SetSysNetPort(mpltlastallstates.lanport);
  pSetWid->LabCli(mpltlastallstates.syssetindex);
  SetSysDisMod(mpltlastallstates.dismod);
  SetSysPowerState(mpltlastallstates.pltpres.powerstate);
  SetSysLanType(mpltlastallstates.lantype);

  SetLocalUi(Qt::Key_Escape);
  ui->gpslabel->setText(tr("N 00 00 00 00 00 00"));
  return;
}


/**
 * @brief to change other mode states for switch mod fo lock lcd
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-06-04}
*/
void BitPlatForm::SetLockUiStates(qint32 imode,qint32 ilock)
{   
  qint32 itype = 0;
  if(PTY1 == ilock)
    {
      itype = 1;
    }

  qint32 i = 0;
  for(i = 0;i < NONEMODE;i++)
  {
      modeintervec.at(i)->ChangeLcdStateWithNoSig(itype);
  }
  return;
}


/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-04-29}
*/
void BitPlatForm::StartDevCalc()
{
  if(!pSetWid->isHidden())
    pSetWid->hide();
  this->close();
  return;
}

/**
 * @brief to call child interface
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-05-21}
*/
void BitPlatForm::SetSysVolume(qint32 ivol)
{
  //for when remote run but sys has not ini yet
  if(NULL == pSetWid)
  {
      pSetWid = new setwid(&pltsystate,&pltlastallstates,0);
  }
  if(NULL != pSetWid)
  {
      pSetWid->pdedtsetwid->SetVolume(ivol);
  }
}

void BitPlatForm::SetSysVolSwitch(qint32 iswitch)
{
    if(NULL == pSetWid)
    {
        pSetWid = new setwid(&pltsystate,&pltlastallstates,0);
    }
    if(NULL != pSetWid)
    {
        pSetWid->pdedtsetwid->SetVolSwitch(iswitch);
    }
}

void BitPlatForm::SetSysLcdBri(qint32 ibri)
{
    if(NULL == pSetWid)
    {
        pSetWid = new setwid(&pltsystate,&pltlastallstates,0);
    }
    if(NULL != pSetWid)
    {
        pSetWid->pdedtsetwid->SetLcdLight(ibri);
    }
}

void BitPlatForm::SetSysDateType(qint32 itype)
{
  if(NULL == pSetWid)
    {
      pSetWid = new setwid(&pltsystate,&pltlastallstates,0);
    }
  if(NULL != pSetWid)
    {
      pSetWid->pdedtsetwid->SetDateType(itype);
    }
}

void BitPlatForm::SetSysDisMod(qint32 imod)
{
  if(NULL == pSetWid)
    {
      pSetWid = new setwid(&pltsystate,&pltlastallstates,0);
    }
  if(NULL != pSetWid)
    {
      pSetWid->pdedtsetwid->SetDisMod(imod);
    }
}

void BitPlatForm::SetSysSleepT(qint32 itype)
{
  if(NULL == pSetWid)
    {
      pSetWid = new setwid(&pltsystate,&pltlastallstates,0);
    }
  if(NULL != pSetWid)
    {
      pSetWid->pdedtsetwid->SetSleepT(itype);
    }
}

void BitPlatForm::SetSysKeyBeep(qint32 iswitch)
{
  if(NULL == pSetWid)
    {
      pSetWid = new setwid(&pltsystate,&pltlastallstates,0);
    }
  if(NULL != pSetWid)
    {
      pSetWid->pdedtsetwid->SetKeyBeepSwi(iswitch);
    }
}

void BitPlatForm::SetGpsEnable(qint32 iswitch)
{
  if(NULL == pSetWid)
    {
      pSetWid = new setwid(&pltsystate,&pltlastallstates,0);
    }
  if(NULL != pSetWid)
    {
      pSetWid->pnetsetwid->SetGpsSwitch(iswitch);
    }
}

void BitPlatForm::SetSysIpAddr(QString ipstr)
{
  if(NULL == pSetWid)
    {
      pSetWid = new setwid(&pltsystate,&pltlastallstates,0);
    }
  if(NULL != pSetWid)
    {
      pSetWid->pnetsetwid->SetIPAddressEx(ipstr);
    }
}

void BitPlatForm::SetSysMaskAddr(QString maskstr)
{
  if(NULL == pSetWid)
    {
      pSetWid = new setwid(&pltsystate,&pltlastallstates,0);
    }
  if(NULL != pSetWid)
    {
      pSetWid->pnetsetwid->SetMaskAddressEx(maskstr);
    }
}

void BitPlatForm::SetSysGateAddr(QString gatestr)
{
  if(NULL == pSetWid)
    {
      pSetWid = new setwid(&pltsystate,&pltlastallstates,0);
    }
  if(NULL != pSetWid)
    {
      pSetWid->pnetsetwid->SetGateWayAddressEx(gatestr);
    }
}

void BitPlatForm::SetSysNetPort(qint32 port)
{
  if(NULL == pSetWid)
    {
      pSetWid = new setwid(&pltsystate,&pltlastallstates,0);
    }
  if(NULL != pSetWid)
    {
      pSetWid->pnetsetwid->SetLanPort(port);
    }
}

void BitPlatForm::SetSysWifiSwitch(qint32 iswitch)
{
  if(NULL == pSetWid)
    {
      pSetWid = new setwid(&pltsystate,&pltlastallstates,0);
    }
  if(NULL != pSetWid)
    {
      pSetWid->pnetsetwid->SetWifiSwitch(iswitch);
    }
}

void BitPlatForm::SetSysWifMib(QString mibstr)
{
  if(NULL == pSetWid)
    {
      pSetWid = new setwid(&pltsystate,&pltlastallstates,0);
    }
  if(NULL != pSetWid)
    {
      pSetWid->pnetsetwid->SetWifiMib(mibstr);
    }
}

void BitPlatForm::SetSysBlueSwitch(qint32 iswitch)
{
  if(NULL == pSetWid)
    {
      pSetWid = new setwid(&pltsystate,&pltlastallstates,0);
    }
  if(NULL != pSetWid)
    {
      pSetWid->pnetsetwid->SetBltSwitch(iswitch);
    }
}

void BitPlatForm::SetSysRef(quint32 iref)
{
  if(NULL == pSetWid)
    {
      pSetWid = new setwid(&pltsystate,&pltlastallstates,0);
    }
  if(NULL != pSetWid)
    {
      pSetWid->pcomsetwid->SetFreqRef(iref);
    }
}

void BitPlatForm::SetSysPowerState(qint32 itype)
{
  if(NULL == pSetWid)
    {
      pSetWid = new setwid(&pltsystate,&pltlastallstates,0);
    }
  if(NULL != pSetWid)
    {
      pSetWid->pcomsetwid->SetPowerType(itype);
    }
}

void BitPlatForm::SetSysLanType(qint32 itype)
{
  if(NULL == pSetWid)
    {
      pSetWid = new setwid(&pltsystate,&pltlastallstates,0);
    }
  if(NULL != pSetWid)
    {
      pSetWid->pcomsetwid->SetLanType(itype);
    }
}

void BitPlatForm::SetSysRefleshUserState()
{
  if(NULL == pSetWid)
    {
      pSetWid = new setwid(&pltsystate,&pltlastallstates,0);
    }
  if(NULL != pSetWid)
    {
      pSetWid->pcomsetwid->SetNowTouser();
    }
}

/**
 * @brief when set ref in sys panel will change all ana mode ui states
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-05-23}
*/
void BitPlatForm::SetRefUiStates(qint32 iref)
{
  qint32 i = 0;
  for(i = 0;i < NONEMODE;i++)
    {
      modeintervec.at(i)->SetSysRefuiStates(iref);
    }
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-03-01}
*/
QString BitPlatForm::GetMeasIteamsNum(qint32 imod,qint32 inum)
{
  switch (imod)
    {
    case SA_MODE:
      if(inum < 0 || inum >= SANONE)
        {
          return  sameasbtntext[pltlastallstates.iallmesa[imod]];
        }
      else
        {
          pltlastallstates.iallmesa[imod] = inum;
          return sameasbtntext[inum];
        }
    case RTSA_MODE:
      if(inum < 0 || inum >= RTSANONE)
        {
          return  rtsameasbtntext[pltlastallstates.iallmesa[imod]];
        }
      else
        {
          pltlastallstates.iallmesa[imod] = inum;
          return rtsameasbtntext[inum];
        }
    case INTERF_MODE:
      if(inum < 0 || inum >= INTERNONE)
        {
          return  intermeasbtntext[pltlastallstates.iallmesa[imod]];
        }
      else
        {
          pltlastallstates.iallmesa[imod] = inum;
          return intermeasbtntext[inum];
        }
    case PM_MODE:
      if(inum < 0 || inum >= PMNONE)
        {
          return  pmmeasbtntext[pltlastallstates.iallmesa[imod]];
        }
      else
        {
          pltlastallstates.iallmesa[imod] = inum;
          return pmmeasbtntext[inum];
        }
    case LTE_FDD_MODE:
      if(inum < 0 || inum >= LTEFDDNONE)
        {
          return  ltefddmeasbtntext[pltlastallstates.iallmesa[imod]];
        }
      else
        {
          pltlastallstates.iallmesa[imod] = inum;
          return ltefddmeasbtntext[inum];
        }
    case LTE_TDD_MODE:
      if(inum < 0 || inum >= LTETDDNONE)
        {
          return  ltetddmeasbtntext[pltlastallstates.iallmesa[imod]];
        }
      else
        {
          pltlastallstates.iallmesa[imod] = inum;
          return ltetddmeasbtntext[inum];
        }
    case FIVE_G_NR:
      if(inum < 0 || inum >= FGNRNONE)
        {
          return  fgnrmeasbtntext[pltlastallstates.iallmesa[imod]];
        }
      else
        {
          pltlastallstates.iallmesa[imod] = inum;
          return fgnrmeasbtntext[inum];
        }
    default:
      return NULL;
    }
}

/**
 * @brief called by local plus and remote when to switch mode
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-03-01;c:03-07;c03-21;c05-20}
*/
void BitPlatForm::PartWtichMode(QString mstr)
{
  //must switch ana mode
//  if(pltlastallstates.orimode != shmengine::getsingleshm()->pshm_home->modetype)
    {
      //change title text and move
      qint32 ist = NowModExitor(mstr);
      qint32 ifull = 0;
      if(ist < 0)
        {
          //if mode exit and just meas different,means just
          if(pltlastallstates.nowshowmodsum <= UIMODMAXNUM)
            {
              if(UIMODMAXNUM == pltlastallstates.nowshowmodsum)
                {
                  pltlastallstates.nowshowmodsum--;
                  ifull = 1;
                }
              //show before hide btn
              clobtnvec.at(INDEXBASE)->show();
              clobtnvec.at(pltlastallstates.nowshowmodsum)->show();
              modelabel.at(pltlastallstates.nowshowmodsum)->show();
              nowmodebtn.at(pltlastallstates.nowshowmodsum)->show();
              pltlastallstates.nowshowmodsum++;

              if(!ifull)
                {
                  modbtnindex = pltlastallstates.nowshowmodsum - 1;
                }
              ChangeModPic(pltlastallstates.nowshowmodsum,modbtnindex);
              if(UIMODMAXNUM == pltlastallstates.nowshowmodsum)
                {
                  ui->plusbtn->move(SPX +(UIMODMAXNUM - 1) * STEPP,SPY);
                }
              else
                {
                  ui->plusbtn->move(SPX + modbtnindex * STEPP,SPY);
                }
            }
        }
      else
        {
          //this only happened in remote mode
          modbtnindex = ist;
          ChangeModPic(pltlastallstates.nowshowmodsum,ist);
        }
      SetModBtntext(ist,mstr,ifull);
      FillConstText();
      //do mode switch action
      DoSwitchAction(pltlastallstates.orimode);

      //save btn mode state for recover when start up
      pltlastallstates.oribtnIndex = modbtnindex;
      pltlastallstates.iuimode[modbtnindex] = pltlastallstates.orimode;
      //when measure differ also to call interface
      if(pltlastallstates.ilastallmesa[pltlastallstates.orimode] != pltlastallstates.iallmesa[pltlastallstates.orimode])
        {
          ChangeModeMeasure(pltlastallstates.orimode,pltlastallstates.iallmesa[pltlastallstates.orimode]);
        }
    }
//  else
//    {
//      //just change title text but not move
//      if(pltlastallstates.ilastallmesa[pltlastallstates.orimode] != pltlastallstates.iallmesa[pltlastallstates.orimode])
//        {
//          modelabel[NowModExitor(mstr)]->setText(mstr);
//          FillConstText();
//          //just call mode interface to convert measure
//          ChangeModeMeasure(pltlastallstates.orimode,pltlastallstates.iallmesa[pltlastallstates.orimode]);
//        }
//    }
  return;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-07-09}
*/
qint32 BitPlatForm::PltSaveDevelopMsg()
{
  QFile pltdevmsg("develop.msg");
  pltdevmsg.open(QIODevice::WriteOnly);
  qint32 iwnum = pltdevmsg.write((char*)&pltdevelopmsg,sizeof(DEVEMSG));
  pltdevmsg.flush();
  pltdevmsg.close();
  return iwnum;
}

qint32 BitPlatForm::PltLoadDevelopMsg()
{
  QFile pltdevfile("develop.msg");
  pltdevfile.open(QIODevice::ReadOnly);
  qint32 iwnum = pltdevfile.read((char*)&pltdevelopmsg,sizeof(DEVEMSG));
  pltdevfile.close();
  return iwnum;
}

/**
 * @brief
 * @param[in]0>default,1>last,2>user
 * @param[in]
 * @return
 * @note
 * @since {2019-05-20}
*/
qint32 BitPlatForm::PltSaveStates(qint32 itype)
{  
  if(PTY0 == itype)
    {
#ifdef PLT_STATE_COND
      PltSaveAnayStates(itype);
      return 0;
#endif
      QFile pltdefaultfile("plt_default.cond");
      pltdefaultfile.open(QIODevice::WriteOnly);
      qint32 iwnum = pltdefaultfile.write((char*)&pltlastallstates,sizeof(PLTSTATEPARAM));
      pltdefaultfile.flush();
      pltdefaultfile.close();
      return iwnum;
    }
  //only happen when shut down
  else if(PTY1 == itype)
    {
      QFile pltlastfile("plt_last.cond");
      pltlastfile.open(QIODevice::WriteOnly);
      qint32 iwnum = pltlastfile.write((char*)&pltlastallstates,sizeof(PLTSTATEPARAM));
      if(!pltlastfile.flush())
        {

        }
      pltlastfile.close();
#ifdef PLT_STATE_COND
      PltSaveAnayStates(itype);
#endif
      return iwnum;
    }
  //only happen when user to set
  else if(PTY2 + 3 == itype)
    {
      QFile pltuserfile("plt_user.cond");
      pltuserfile.open(QIODevice::WriteOnly);
      pltlastallstates.pltpres.powerstate = pltsystate.powerstate;
      qint32 iwnum = pltuserfile.write((char*)&pltlastallstates,sizeof(PLTSTATEPARAM));
      if(!pltuserfile.flush())
        {

        }
      pltuserfile.close();
#ifdef PLT_STATE_COND
      PltSaveAnayStates(itype);
#endif
      return iwnum;
    }
  return 0;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-07-02;c:09-04}
*/
qint32 BitPlatForm::PltSetDisMod(qint32 imod)
{  
  //change method because cost long time
  PltDismodForstart(imod);
  //other ana mode part
  qint32 i = 0;
  for(i = 0;i < NONEMODE;i++)
    {
      modeintervec.at(i)->SetDisplayMode(imod);
    }
  return 0;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-10-10}
*/
void BitPlatForm::PltPlayWav(qint32 itype, qint32 iswitch)
{
  if(itype >= wavlen)
    {
      return;
    }
  //play wav
  if(iswitch)
    {
//      strcpy(shmengine::getsingleshm()->pshm_sysconf->WavFileName,wavmap.values().at(itype).toLatin1().data());
//      shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_PLAYMUSICON);
    }
  //close
  else
    {
//      shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_PLAYMUSICOFF);
    }
  return;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-09-06}
*/
qint32 BitPlatForm::PltDismodForstart(qint32 imod)
{
  QString pltmsl[] = {":/bit/stylesheet/pltindoor.qss",":/bit/stylesheet/pltoutdoor.qss",":/bit/stylesheet/pltnight.qss"};
  QFile pltf(pltmsl[imod]);
  pltf.open(QIODevice::ReadOnly);
  QString distr = pltf.readAll();
  ui->label->setStyleSheet(distr);
  ui->label_2->setStyleSheet(distr);
  ui->timelabel->setStyleSheet(distr);
  ui->plusbtn->setStyleSheet(distr);
  ui->batterylabel->setStyleSheet(distr);
  ui->statebarlabel->setStyleSheet(distr);
  pltf.close();
  TopTabPicdis(imod);
  CtrlModePltdis(pltlastallstates.dismod,loreflag);
  GpsPltdisMod(imod,pltlastallstates.gpswitch);
  BatPicPltdis(imod);
  return 0;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-06-04}
*/
void BitPlatForm::PltSaveAnayStates(qint32 itype)
{
  qint32 i = 0;
  for(i = 0;i < NONEMODE;i++)
    {
      modeintervec.at(i)->PltCurAnaMode(pltlastallstates.orimode);
      modeintervec.at(i)->PltSaveConditions(itype);
    }
  return;
}

qint32 BitPlatForm::PltSavePreStates()
{
  QFile pltprefile("plt.pres");
  pltprefile.open(QIODevice::WriteOnly);
  qint32 iwnum = pltprefile.write((char*)&pltsystate,sizeof(PLTPRESTATE));
  pltprefile.flush();
  pltprefile.close();
  qint32 i = 0;
#ifdef PLT_STATE_COND
  for(i = 0;i < NONEMODE;i++)
    {
      modeintervec.at(i)->PltSavePres(pltsystate.powerstate);
    }
#endif
  return iwnum;
}

qint32 BitPlatForm::PltLoadPreStates()
{
  QFile pltprefile("plt.pres");
  pltprefile.open(QIODevice::ReadOnly);
  qint32 iwnum = pltprefile.read((char*)&pltsystate,sizeof(PLTPRESTATE));
  pltprefile.close();
  return iwnum;
}

PDEVEMSG BitPlatForm::GetDMsgHandle()
{
  return &pltdevelopmsg;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-05-20}
*/
qint32 BitPlatForm::PltLoadStates(qint32 itype)
{
  if(PTY0 == itype)
    {
      QFile pltdefaultfile("plt_default.cond");
      pltdefaultfile.open(QIODevice::ReadOnly);
      qint32 iwnum = pltdefaultfile.read((char*)&pltlastallstates,sizeof(PLTSTATEPARAM));
      pltdefaultfile.close();
      return iwnum;
    }
  else if(PTY1 == itype)
    {
      QFile pltlastfile("plt_last.cond");
      pltlastfile.open(QIODevice::ReadOnly);
      qint32 iwnum = pltlastfile.read((char*)&pltlastallstates,sizeof(PLTSTATEPARAM));
      pltlastfile.close();
      return iwnum;
    }
  else if(PTY2 == itype)
    {
      QFile pltuserfile("plt_user.cond");
      pltuserfile.open(QIODevice::ReadOnly);
      qint32 iwnum = pltuserfile.read((char*)&pltlastallstates,sizeof(PLTSTATEPARAM));
      pltuserfile.close();
      return iwnum;
    }
  return 0;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-08-15}
*/
void BitPlatForm::on_timelabel_clicked()
{
  SysPanelCtrl();
  pSetWid->LabCli(PTY1);
}

void BitPlatForm::on_gpslabel_clicked()
{  
  SysPanelCtrl();
  pSetWid->LabCli(PTY2);
}

void BitPlatForm::on_batpiclabel_clicked()
{  
  SysPanelCtrl();
  pSetWid->LabCli(PTY5);
}

void BitPlatForm::on_batterylabel_clicked()
{
  SysPanelCtrl();
  pSetWid->LabCli(PTY5);
}

void BitPlatForm::on_label_3_clicked()
{ 
  SysPanelCtrl();
  pSetWid->LabCli(PTY2);
}

extern ScpiPort_internet   *g_pPortInterNet;
#include "bitvnchandle.h"

void BitPlatForm::on_sendSCPIcmd(QString cmd)
{
    cmd += "\n";
    BitVncHandle::GetVncInternetHandle()->GetTcpSocket()->write(cmd.toLatin1(),cmd.size());
    /*
    if(g_pPortInterNet->getUserContext())
    {
        ((QTcpSocket *)g_pPortInterNet->getUserContext())->write();
    }
    */
}

