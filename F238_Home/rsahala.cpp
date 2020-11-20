#include "rsahala.h"
#include "ui_rsahala.h"
#include <unistd.h>
#include <QMessageBox>
#include <QTime>
#include "homesoftbus.h"
#include "qdebug.h"
#include <QKeyEvent>
#include <errno.h>

const char* homedistrc::pltdismod[] =
{
  QT_TR_NOOP("indoor"),
  QT_TR_NOOP("outdoor"),
  QT_TR_NOOP("night")
};
QFile RsaHala::logfile("home.log");
NOTICMSG homexcep;
RsaHala::RsaHala(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::RsaHala),
  lcf (PUZERO),
  ncf (POFF),
  lncf (PUZERO),
  nncf (POFF),
  timerHandle(0),
  batteryHandle(0),
  batnum(BATTARYINI),
  showflag(POFF),
  presetflag(POFF),
  homedismode(PTY0)
{
  ui->setupUi(this);
  this->setCursor(Qt::BlankCursor);
  qInstallMessageHandler(RsaHala::bithomeRedirectHandler);
  homexcep.source = 17;
  homexcep.logicmode = 1;
  if(!RsaHala::logfile.open(QIODevice::Append))
    {
      qCritical("7");
      homexcep.npflag = 1;
      homexcep.ntype = 2;
      homexcep.index = 7;
      RunStateShm::getsingleshm()->pshm_homenotic->noticode = GetNoticeCode(&homexcep);
    }
  //top hint
  this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
  battpicvec.append(NOBATPIC);
  battpicvec.append(CHARGEPIC);
  battpicvec.append(DISCHARGEPIC);
  battpicvec.append(FULLPIC);
  pmthread = new modethread(this);
  QObject::connect(pmthread, SIGNAL(ShowSig()), this, SLOT(homeuishow()));
  pmthread->start();
  if(LoadTimerHandle() < 0)
    {
      qCritical("4");
      homexcep.npflag = 1;
      homexcep.ntype = 2;
      homexcep.index = 4;
      RunStateShm::getsingleshm()->pshm_homenotic->noticode = GetNoticeCode(&homexcep);
    }  
  ui->pushButton->hide();
  ui->timelb->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd\n   APhh:mm:ss"));
}

RsaHala::~RsaHala()
{
  ReleaseTimerHandle();
  pmthread->ExitThread();
  RunStateShm::getsingleshm()->ReleaseSemp(RunStateShm::getsingleshm()->homeuihandle);
  RsaHala::logfile.close();
  qInstallMessageHandler(0);
  delete ui;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-02-25}
*/
void RsaHala::HomeTimeCtrl(qint32 id)
{
  if(timerHandle == id)
    {
      if(showflag)
        {
          if(PTY0 == RunStateShm::getsingleshm()->pshm_sysinfo->datetype)
            {
              ui->timelb->setText(QDateTime::currentDateTime().toString("dd-MM-yyyy\n   APhh:mm:ss"));
            }
          else if(PTY1 == RunStateShm::getsingleshm()->pshm_sysinfo->datetype)
            {
              ui->timelb->setText(QDateTime::currentDateTime().toString("MM-dd-yyyy\n   APhh:mm:ss"));
            }
          else
            {
              ui->timelb->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd\n   APhh:mm:ss"));
            }

          if(PON == RunStateShm::getsingleshm()->pshm_home->remotecloseflag)
            {
              showflag = POFF;
              this->hide();
              RunStateShm::getsingleshm()->pshm_home->remotecloseflag = POFF;
            }
        }
    }
  if(batteryHandle == id)
    {
      if(showflag)
        {
          static qint32 nflf = -1;
          static qint32 nfnf = -2;
          RunStateShm::PassTrigToSys(PLT_IXT_System_Info,PLT_IXS_BatteryInfoAll);
          switch (RunStateShm::getsingleshm()->pshm_sysinfo->BatterChargeStatus)
            {
            case UN_BATT:
              nflf = UN_BATT;
              //if(nflf != nfnf)
                {
                  NoBatteryCtrl();
                  nfnf = nflf;
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
              nflf = BATT_FULL;
              //if(nflf != nfnf)
                {
                  FullBatteryCtrl();
                  nfnf = nflf;
                }
              break;
            default:
              break;
            }
        }
    }
  return;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-09-27}
*/
void RsaHala::BatPicPltdis(qint32 imode)
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
  switch (RunStateShm::getsingleshm()->pshm_sysinfo->BatterChargeStatus)
    {
    case UN_BATT:
      ui->label_3->setPixmap(QPixmap(QString::fromUtf8(battpicvec.at(PTY0)[INDEXBASE])/*(NOBATPIC[INDEXBASE])*/));
      ui->label_4->setText(tr("NBat"));
      break;
    case BATT_CHARGE:
      batnum = RunStateShm::getsingleshm()->pshm_sysinfo->BatteryRemaind;
      batnum = batnum > 100 ? 100 : batnum;
      ilen = sizeof(CHARGEREMAIN) / sizeof(quint32);
      iunit = ilen - 1;
      i = 0;
      for(i = 0;i < ilen;i++)
        {
          if(batnum < CHARGEREMAIN[i])
            {
              iunit = i;
              break;
            }
        }
      ui->label_3->setPixmap(QPixmap(QString::fromUtf8(battpicvec.at(PTY1)[iunit]/*CHARGEPIC[iunit]*/)));
      batterystr = QString::number(batnum) + "%";
      ui->label_4->setText(batterystr);
      break;
    case BATT_DISCHARGE:
      batnum = RunStateShm::getsingleshm()->pshm_sysinfo->BatteryRemaind;
      batnum = batnum > 100 ? 100 : batnum;
      ilen = sizeof(DISCHARGEREMIAN) / sizeof(quint32);
      i = 0;
      for(i = ilen - 1;i >= 0;i--)
        {
          if(batnum > DISCHARGEREMIAN[i])
            {
              iunit = i;
              break;
            }
        }
      ui->label_3->setPixmap(QPixmap(QString::fromUtf8(battpicvec.at(PTY2)[iunit]/*DISCHARGEPIC[iunit]*/)));
      batterystr = QString::number(batnum) + "%";
      ui->label_4->setText(batterystr);
      break;
    case BATT_FULL:
      ui->label_4->setText("100%");
      ui->label_3->setPixmap(QPixmap(QString::fromUtf8(battpicvec.at(PTY3)[INDEXBASE]/*FULLPIC[INDEXBASE]*/)));
      break;
    default:
      break;
    }
}

/**
 * @brief load time and sys timer handle
 * @return under zero means error
 * @note only called once in constructor
 * @author steve
 * @since {2018-12-18}
*/
qint32 RsaHala::LoadTimerHandle()
{
  qint32 iBack = -1;
  if(0 == (timerHandle = startTimer(SYSINTER)))
    {
      return iBack;
    }
  if(0 == (batteryHandle = startTimer(BATTINTER)))
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
 * @since {2018-12-18}
*/
void RsaHala::ReleaseTimerHandle()
{
  if(timerHandle)
    {
      killTimer(timerHandle);
      timerHandle = 0;
    }
  if(batteryHandle)
    {
      killTimer(batteryHandle);
      batteryHandle = 0;
    }
  return;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-02-25}
*/
void RsaHala::NoBatteryCtrl()
{
  lncf = -1;
  nncf = 0;
  lcf = -1;
  ncf = 0;
  ui->label_4->setText(tr("NBat"));
  ui->label_3->setPixmap(QPixmap(QString::fromUtf8(battpicvec.at(PTY0)[INDEXBASE])));
  return;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-02-25}
*/
void RsaHala::ChargeStateCtrl()
{
  lncf = -1;
  nncf = 0;
  batnum = RunStateShm::getsingleshm()->pshm_sysinfo->BatteryRemaind;
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
  //if(lcf != ncf)
    {
      ui->label_3->setPixmap(QPixmap(QString::fromUtf8(battpicvec.at(PTY1)[iunit])));
      lcf = ncf;
    }
  batterystr = QString::number(batnum) + "%";
  ui->label_4->setText(batterystr);
  return;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-02-25}
*/
void RsaHala::DisChargeStateCtrl()
{
  lcf = -1;
  ncf = 0;
  batnum = RunStateShm::getsingleshm()->pshm_sysinfo->BatteryRemaind;
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
  //if(lncf != nncf)
    {
      ui->label_3->setPixmap(QPixmap(QString::fromUtf8(battpicvec.at(PTY2)[iunit])));
      lncf = nncf;
    }
  batterystr = QString::number(batnum) + "%";
  ui->label_4->setText(batterystr);
  return;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-02-25}
*/
void RsaHala::FullBatteryCtrl()
{
  lncf = -1;
  nncf = 0;
  lcf = -1;
  ncf = 0;
  ui->label_4->setText("100%");
  ui->label_3->setPixmap(QPixmap(QString::fromUtf8(battpicvec.at(PTY3)[INDEXBASE])));
  return;
}

void RsaHala::bithomeRedirectHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
  QTextStream logstream(&RsaHala::logfile);
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
  RsaHala::logfile.flush();
  return;
}

quint32 GetNoticeCode(PNOTICMSG notichandle)
{
  quint32 icode = 0;
  icode |= ((quint32)notichandle->npflag) << 31;
  icode |= ((quint32)notichandle->ntype) << 29;
  icode |= ((quint32)notichandle->source) << 20;
  icode |= ((quint32)notichandle->logicmode) << 19;
  icode |= notichandle->index;
  return icode;
}

void RsaHala::on_bsabutton_clicked()
{  
  return DoSwitchCtrl(SA_MODE);
}

void RsaHala::on_rsabutton_clicked()
{ 
  return DoSwitchCtrl(RTSA_MODE);
}

void RsaHala::on_ltetddbutton_clicked()
{
  return DoSwitchCtrl(LTE_TDD_MODE);
}

void RsaHala::on_ltefddbutton_clicked()
{
  return DoSwitchCtrl(LTE_FDD_MODE);
}

void RsaHala::on_pmbutton_clicked()
{
  //return DoSwitchCtrl(PM_MODE);
  //QMessageBox::about(this,"Hi,Dear","This mode will meet you soon...\n\n");
}

void RsaHala::on_interbutton_clicked()
{
  //return DoSwitchCtrl(INTERF_MODE);
  //QMessageBox::about(this,"Hi,Dear","This mode will meet you soon...\n\n");
}

void RsaHala::on_fivegbutton_clicked()
{
  return DoSwitchCtrl(FIVE_G_NR);
  //QMessageBox::about(this,"Hi,Dear","This mode will meet you soon...\n\n");
}

void RsaHala::on_sysbutton_clicked()
{
  //tell timer that not get battery msg
  showflag = POFF;
  RunStateShm::getsingleshm()->pshm_home->systype = PON;
  //to tell platapp that switch action is through home,every mode should add this ctrl
  RunStateShm::getsingleshm()->pshm_home->modesource = PON;
  //UNDO sleep how long to hide
  if(-1 == usleep(HIDEWAIT))
    {
      qCritical(strerror(errno));
      homexcep.npflag = 1;
      homexcep.ntype = 2;
      homexcep.index = 6;
      RunStateShm::getsingleshm()->pshm_homenotic->noticode = GetNoticeCode(&homexcep);
    }
  presetflag = POFF;
  this->hide();
  return;
}

void RsaHala::homeuishow()
{
  showflag = PON;
  ui->label_5->setText(" ");
  this->show();
  this->activateWindow();
  this->setFocus();
  /**
* @brief setting dismode
* @since {2019-09-27}
*/
  if(homedismode != RunStateShm::getsingleshm()->pshm_sysinfo->dismode)
    {
      homedismode = RunStateShm::getsingleshm()->pshm_sysinfo->dismode;
      if(PTY1 == homedismode)
        {
          homedismode = PTY0;
        }
      if(true != this->setProperty("homedismode",homedistrc::pltdismod[homedismode]))
        {

        }
      setStyle(QApplication::style());      
    }
  BatPicPltdis(RunStateShm::getsingleshm()->pshm_sysinfo->dismode);
  return;
}

/**
 * @brief for all mode switch to call
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-02-25}
*/
void RsaHala::DoSwitchCtrl(quint32 imode)
{
  this->hide();
  if(-1 == usleep(HIDEWAIT))
    {
      qCritical(strerror(errno));
      homexcep.npflag = 1;
      homexcep.ntype = 2;
      homexcep.index = 6;
      RunStateShm::getsingleshm()->pshm_homenotic->noticode = GetNoticeCode(&homexcep);
    }
  //tell timer that not get battery msg
  showflag = POFF;
  presetflag = POFF;
  //QMessageBox::about(this,"Hi,Dear","This mode will meet you soon...\n\n");
  RunStateShm::getsingleshm()->pshm_home->modetype = imode;
  //to tell platapp that switch action is through home,every mode should add this ctrl
  RunStateShm::getsingleshm()->pshm_home->modesource = PON;
  return;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-03-05;c08-22}
*/
void RsaHala::keyPressEvent(QKeyEvent *event)
{  
  if(Qt::Key_Escape == event->key())
    {
      showflag = POFF;
      presetflag = POFF;
      this->hide();
    }
  if(Qt::Key_PowerOff == event->key())
    {
      RunStateShm::getsingleshm()->pshm_home->systype = PON + 1;
      //to tell platapp that switch action is through home,every mode should add this ctrl
      RunStateShm::getsingleshm()->pshm_home->modesource = PON;
    }
  if(Qt::Key_Shift == event->key())
    {
      presetflag = !presetflag;
      if(presetflag)
        {
          ui->label_5->setText("Functional Composition");
        }
      else
        {
          ui->label_5->setText(" ");
        }
    }
  if(presetflag)
    {
      if(Qt::Key_F2 == event->key())
        {
          showflag = POFF;
          presetflag = POFF;
          this->hide();
          this->repaint();
          RunStateShm::getsingleshm()->pshm_home->systype = PON + 2;
          RunStateShm::getsingleshm()->pshm_home->modesource = PON;
        }
      else if(Qt::Key_1 == event->key())
        {
          on_bsabutton_clicked();
        }
      else if(Qt::Key_2 == event->key())
        {
          on_rsabutton_clicked();
        }
      else if(Qt::Key_3 == event->key())
        {
          on_ltetddbutton_clicked();
        }
      else if(Qt::Key_4 == event->key())
        {
          on_ltefddbutton_clicked();
        }
      else if(Qt::Key_5 == event->key())
        {
          on_pmbutton_clicked();
        }
      else if(Qt::Key_6 == event->key())
        {
          on_interbutton_clicked();
        }
      else if(Qt::Key_7 == event->key())
        {
          on_fivegbutton_clicked();
        }
      else if(Qt::Key_8 == event->key())
        {
          on_sysbutton_clicked();
        }
    }
  return;
}

//c0225
void RsaHala::timerEvent(QTimerEvent *event)
{
  return HomeTimeCtrl(event->timerId());
}

void RsaHala::changeEvent(QEvent *event)
{
  if(event->type() == QEvent::LanguageChange)
    {
      ui->bsabutton->setText(tr("Spectrum Analyzer"));
      ui->rsabutton->setText(tr("Realtime Spectrum\n""Analyzer"));
      ui->ltetddbutton->setText(tr("LTE-A TDD"));
      ui->ltefddbutton->setText(tr("LTE-A FDD"));
      ui->pmbutton->setText(tr("Power Meter"));
      ui->interbutton->setText(tr("Interference\n""Analyzer"));
      ui->fivegbutton->setText(tr("5G Analyzer"));
      ui->sysbutton->setText(tr("System Setting"));
      ui->label_4->setText(tr("NBat"));
      ui->pushButton->setText(tr(homedistrc::pltdismod[0]));
    }
  else
    return QWidget::changeEvent(event);
}

bool BitHomeForLang(qint32 ilantype);
qint32 itype = PTY0;
void RsaHala::on_pushButton_clicked()
{  
//  homexcep.npflag = 1;
//  homexcep.ntype = 2;
//  homexcep.index = 7;
//  RunStateShm::getsingleshm()->pshm_homenotic->noticode = GetNoticeCode(&homexcep);
    if(PTY0 == itype)
      itype = PTY1;
    else
      itype = PTY0;
    BitHomeForLang(itype);
}
