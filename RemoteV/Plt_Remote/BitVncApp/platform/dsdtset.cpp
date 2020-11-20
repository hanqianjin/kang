#include "dsdtset.h"
#include "ui_dsdtset.h"
#include "softbus.h"
//#include "shmengine.h"
#include "remoteinterface.h"

qint32 dsdtset::timerswitch = PTY0;
dsdtset::dsdtset(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::dsdtset)
{
  ui->setupUi(this);
  sleeptimerid = PTY0;  
  pltdisT = new pltdisthread();
  connect(pltdisT,SIGNAL(sigpltdis(qint32)),remoteinterface::getplatformremotehandle(),SLOT(PltSetDisMod(qint32)));
  pltdisT->start();
  initCalendar();


  refreshTime();

  ui->datesurebtn->setVisible(false);
  ui->dateTimeEdit->setVisible(false);
  ui->label_2->setVisible(false);
}

dsdtset::~dsdtset()
{
  pltdisT->grunflag = 0;
  delete ui;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-04-17}
*/
void dsdtset::on_soundswithbtn_clicked()
{
  *dsdtobj.soundswitch = !*dsdtobj.soundswitch;
  //open sound
  if(*dsdtobj.soundswitch)
    {
      SoundSwitchStyleOn();
//      shmengine::getsingleshm()->pshm_sysconf->Volume = *dsdtobj.soundnum;
//      shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_Volume);
    }
  else
    {
      SoundSwitchStyleOff();
//      shmengine::getsingleshm()->pshm_sysconf->Volume = PTY0;
//      shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_Volume);
    }
  return;
}

/**
 * @brief setting lcd brightness
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-05-05;c05-21}
*/
void dsdtset::SetLcdLight(qint32 inum)
{
  if(inum > ui->horizontalSlider->maximum() || inum < ui->horizontalSlider->minimum())
    return;
  ui->horizontalSlider->setValue(inum);
  return;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-05-05}
*/
void dsdtset::SetVolume(qint32 ivol)
{
  if(ivol < (SINGVOL - SINGVOL) || ivol > SINGVOL * 10)
    return;
  ui->horizontalSlider_2->setValue(ivol);
  return;
}

/**
 * @brief for scpi
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-05-21}
*/
void dsdtset::SetVolSwitch(qint32 iswitch)
{
  if(iswitch != PTY0 && iswitch != PTY1)
    return;
  *dsdtobj.soundswitch = iswitch;
  //open sound
  if(*dsdtobj.soundswitch)
    {
      SoundSwitchStyleOn();
//      shmengine::getsingleshm()->pshm_sysconf->Volume = *dsdtobj.soundnum;
//      shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_Volume);
    }
  else
    {
      SoundSwitchStyleOff();
//      shmengine::getsingleshm()->pshm_sysconf->Volume = PTY0;
//      shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_Volume);
    }
  return;
}

void dsdtset::SetDateType(qint32 itype)
{
  if(itype < PTY0 || itype > PTY2)
    return;
  *dsdtobj.datetype = itype;
  if(PTY0 == itype)
    {
      ui->date1btn->setChecked(true);
    }
  else if(PTY1 == itype)
    {
      ui->date2btn->setChecked(true);
    }
  else if(PTY2 == itype)
    {
      ui->date3btn->setChecked(true);
    }
  refreshDate();
}

void dsdtset::SetDisMod(qint32 imod)
{
  if(imod < PTY0 || imod > PTY2 || *dsdtobj.dismod == imod)
    return;  
  *dsdtobj.dismod = imod;
  if(PTY0 == imod)
    {
      ui->pushButton_12->setChecked(true);
    }
  else if(PTY1 == imod)
    {
      ui->pushButton_13->setChecked(true);      
    }
  else if(PTY2 == imod)
    {
      ui->pushButton_14->setChecked(true);      
    }
  static_cast<setwid*>(parent())->SetPltSysDisM(imod);
  pltdisT->pltdism = imod;
//  remoteinterface::getplatformremotehandle()->PltSetDisMod(imod);
}

void dsdtset::SetSleepT(qint32 itype)
{
  if(itype < PTY0 || itype > PTY3)
    return;
  *dsdtobj.slemod = itype;
  if(PTY0 == itype)
    {
      ui->pushButton_7->setChecked(true);
      emit ui->pushButton_7->clicked();
      ReStartSysSleep();
    }
  else if(PTY1 == itype)
    {
      ui->pushButton_8->setChecked(true);
      emit ui->pushButton_8->clicked();
    }
  else if(PTY2 == itype)
    {
      ui->pushButton_9->setChecked(true);
      emit ui->pushButton_9->clicked();
    }
  else if(PTY3 == itype)
    {
      ui->pushButton_10->setChecked(true);
      emit ui->pushButton_10->clicked();
    }
}

void dsdtset::SetKeyBeepSwi(qint32 iswitch)
{
  *dsdtobj.keybeepswitch = iswitch;
  if(*dsdtobj.keybeepswitch)
    {
      KeyBeepStyleOn();
    }
  else
    {
      KeyBeepStyleOff();
    }
//  shmengine::getsingleshm()->pshm_sysconf->KeyBeep = *dsdtobj.keybeepswitch;
//  shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_KeyBeep);
}

/**
 * @brief for ini recover
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-05-21}
*/
void dsdtset::SetSleepBtnCheck(qint32 *iIndex)
{
  dsdtobj.slemod = iIndex;
  if(PTY0 == *iIndex)
    {
      ui->pushButton_7->setChecked(true);
      emit ui->pushButton_7->clicked();
      //open lcd brightness
//      shmengine::getsingleshm()->pshm_sysconf->LcdpadLight = PTY1;
//      shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_LcdpadLight);
    }
  else if(PTY1 == *iIndex)
    {
      ui->pushButton_8->setChecked(true);
      emit ui->pushButton_8->clicked();
    }
  else if(PTY2 == *iIndex)
    {
      ui->pushButton_9->setChecked(true);
      emit ui->pushButton_9->clicked();
    }
  else if(PTY3 == *iIndex)
    {
      ui->pushButton_10->setChecked(true);
      emit ui->pushButton_10->clicked();
    }
}

void dsdtset::SetDisBtnCheck(qint32 *iIndex)
{
  dsdtobj.dismod = iIndex; 
  if(PTY0 == *iIndex)
    {
      ui->pushButton_12->setChecked(true);
    }
  else if(PTY1 == *iIndex)
    {
      ui->pushButton_13->setChecked(true);
    }
  else if(PTY2 == *iIndex)
    {
      ui->pushButton_14->setChecked(true);
    }  
}

void dsdtset::SetLcdBtn(qint32 *iIndex)
{
  dsdtobj.lcdbri = iIndex;
  ui->horizontalSlider->setValue(*iIndex);
}

void dsdtset::SetDateBtnCheck(qint32 *iIndex)
{
  dsdtobj.datetype = iIndex;
  if(PTY0 == *iIndex)
    {
      ui->date1btn->setChecked(true);
    }
  else if(PTY1 == *iIndex)
    {
      ui->date2btn->setChecked(true);
    }
  else if(PTY2 == *iIndex)
    {
      ui->date3btn->setChecked(true);
    }
  refreshDate();
}

void dsdtset::SetSoundSwitchBtn(qint32 *iIndex)
{
  dsdtobj.soundswitch = iIndex;
  if(*dsdtobj.soundswitch)
  {
      SoundSwitchStyleOn();
//      shmengine::getsingleshm()->pshm_sysconf->Volume = *dsdtobj.soundnum;
//      shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_Volume);
  }
  else
  {
      SoundSwitchStyleOff();
//      shmengine::getsingleshm()->pshm_sysconf->Volume = PTY0;
//      shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_Volume);
   }
}

void dsdtset::SetSoundBtn(qint32 *iIndex)
{
  dsdtobj.soundnum = iIndex;
  ui->horizontalSlider_2->setValue(*iIndex / SINGVOL);
}

void dsdtset::SetKeybeepBtn(qint32 *iswitch)
{
  dsdtobj.keybeepswitch = iswitch;
  if(*dsdtobj.keybeepswitch)
    {
      KeyBeepStyleOn();
    }
  else
    {
      KeyBeepStyleOff();
    }
//  shmengine::getsingleshm()->pshm_sysconf->KeyBeep = *dsdtobj.keybeepswitch;
//  shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_KeyBeep);
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-09-04}
*/
void dsdtset::KeyBeepStyleOn()
{
  QString mstr = "#dsdtset[pltdismode=\"indoor\"] ";
  QString qstr = QString("QPushButton{background-image: url(:/bit/image/btn_radio_on_w90.png);border-style: flat;\
                         background-color: transparent;}\n");
QString mstr1 = "#dsdtset[pltdismode=\"night\"] ";
QString qstr1 = QString("QPushButton{background-image: url(:/bit/image/night_On.png);border-style: flat;\
                        background-color: transparent;}\n");
this->ui->keybeepbtn->setStyleSheet(mstr + qstr + mstr1 + qstr1);
return;
}

void dsdtset::KeyBeepStyleOff()
{
  QString mstr = "#dsdtset[pltdismode=\"indoor\"] ";
  QString qstr = QString("QPushButton{background-image: url(:/bit/image/btn_radio_off_w90.png);border-style: flat;\
                         background-color: transparent;}\n");
QString mstr1 = "#dsdtset[pltdismode=\"night\"] ";
QString qstr1 = QString("QPushButton{background-image: url(:/bit/image/night_Off.png);border-style: flat;\
                        background-color: transparent;}\n");
this->ui->keybeepbtn->setStyleSheet(mstr + qstr + mstr1 + qstr1);
return;
}

void dsdtset::SoundSwitchStyleOn()
{
  QString mstr = "#dsdtset[pltdismode=\"indoor\"] ";
  QString qstr = QString("QPushButton{border-image: url(:/bit/image/icn_sound.png);border-style: flat;background-color: transparent;}\n");
  QString mstr1 = "#dsdtset[pltdismode=\"night\"] ";
  QString qstr1 = QString("QPushButton{border-image: url(:/bit/image/icn_night_sound.png);border-style: flat;background-color: transparent;}\n");
  this->ui->soundswithbtn->setStyleSheet(mstr + qstr + mstr1 + qstr1);
}

void dsdtset::SoundSwitchStyleOff()
{
  QString mstr = "#dsdtset[pltdismode=\"indoor\"] ";
  QString qstr = QString("QPushButton{border-image: url(:/bit/image/icn_mute.png);border-style: flat;background-color: transparent;}\n");
  QString mstr1 = "#dsdtset[pltdismode=\"night\"] ";
  QString qstr1 = QString("QPushButton{border-image: url(:/bit/image/icn_night_mute.png);border-style: flat;background-color: transparent;}\n");
  this->ui->soundswithbtn->setStyleSheet(mstr + qstr + mstr1 + qstr1);
}

void dsdtset::on_horizontalSlider_valueChanged(int value)
{
  *dsdtobj.lcdbri = value;
//  shmengine::getsingleshm()->pshm_sysconf->LCDBrightness = value;
//  shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_LCDBrightness);
  return;
}

void dsdtset::on_date1btn_clicked()
{  
  *dsdtobj.datetype = PTY0;
    refreshDate();
}

void dsdtset::on_date2btn_clicked()
{  
  *dsdtobj.datetype = PTY1;
    refreshDate();
}

void dsdtset::on_date3btn_clicked()
{  
  *dsdtobj.datetype = PTY2;
    refreshDate();
}

void dsdtset::on_datesurebtn_clicked()
{
  QString dstr = this->ui->dateTimeEdit->date().toString("yyyy-MM-dd");
  QString tstr = this->ui->dateTimeEdit->time().toString("hh:mm:ss");
  QString tdstr = "date -s " + QString(" \" ") +dstr + " " + tstr + QString(" \" ");
  system(tdstr.toStdString().c_str());
  system("hwclock -w");
  return;
}

void dsdtset::on_datesurebtn_pressed()
{
  ui->label_2->setPixmap(QPixmap(QString::fromUtf8(":/bit/image/input_w462_click.png")));
}

void dsdtset::on_datesurebtn_released()
{
  ui->label_2->setPixmap(QPixmap(QString::fromUtf8(":/bit/image/input_w462_nor.png")));
}

void dsdtset::on_horizontalSlider_2_valueChanged(int value)
{
  if(dsdtobj.soundswitch && *dsdtobj.soundswitch)
    {
      *dsdtobj.soundnum = value * SINGVOL;
//      shmengine::getsingleshm()->pshm_sysconf->Volume = *dsdtobj.soundnum;
//      shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_Volume);
      QString mstr = "#dsdtset[pltdismode=\"indoor\"] ";
      QString qstr = QString("QSlider{background-image: url(%1)}\n").arg(QString(VOLPIC[value]));
      QString mstr1 = "#dsdtset[pltdismode=\"night\"] ";
      QString qstr1 = QString("QSlider{background-image: url(%1)}\n").arg(QString(NIGHTVOLPIC[value]));
      ui->horizontalSlider_2->setStyleSheet(mstr + qstr + mstr1 + qstr1);
    }
  else
    {
      *dsdtobj.soundnum = value * SINGVOL;
      QString mstr = "#dsdtset[pltdismode=\"indoor\"] ";
      QString qstr = QString("QSlider{background-image: url(%1)}\n").arg(QString(VOLPIC[value]));
      QString mstr1 = "#dsdtset[pltdismode=\"night\"] ";
      QString qstr1 = QString("QSlider{background-image: url(%1)}\n").arg(QString(NIGHTVOLPIC[value]));
      ui->horizontalSlider_2->setStyleSheet(mstr + qstr + mstr1 + qstr1);
    }
  return;
}

/**
 * @brief 7~10 for sleep mode
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-05-21}
*/
void dsdtset::on_pushButton_7_clicked()
{
  *dsdtobj.slemod = PTY0;
  timerswitch = PTY0;
  if(sleeptimerid)
    {
      killTimer(sleeptimerid);
      sleeptimerid = PTY0;
    }
}

//10min
void dsdtset::on_pushButton_8_clicked()
{
  *dsdtobj.slemod = PTY1;
  timerswitch = PTY1;
  if(sleeptimerid)
    {
      killTimer(sleeptimerid);
    }
  sleeptimerid = startTimer(SYSSLEEP);
}

//20min
void dsdtset::on_pushButton_9_clicked()
{
  *dsdtobj.slemod = PTY2;
  timerswitch = PTY2;
  if(sleeptimerid)
    {
      killTimer(sleeptimerid);
    }
  sleeptimerid = startTimer(SYSSLEEP << 1);
}

//30min
void dsdtset::on_pushButton_10_clicked()
{
  *dsdtobj.slemod = PTY3;
  timerswitch = PTY3;
  if(sleeptimerid)
    {
      killTimer(sleeptimerid);
    }
  sleeptimerid = startTimer(SYSSLEEP * PTY3);
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-06-20}
*/
void dsdtset::ReStartSysSleep()
{
  //open lcd brightness
//  shmengine::getsingleshm()->pshm_sysconf->LcdpadLight = PTY1;
//  shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_LcdpadLight);
  //retimer
  if(timerswitch)
    {
      if(sleeptimerid)
        {
          killTimer(sleeptimerid);
          sleeptimerid = PTY0;
        }
      sleeptimerid = startTimer(SYSSLEEP * timerswitch);
    }
}

/**
 * @brief 12~14 for indoor/night/outdoor mode
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-05-21}
*/
void dsdtset::on_pushButton_12_clicked()
{
  if(PTY0 == *dsdtobj.dismod)
    {
      return;
    }
  *dsdtobj.dismod = PTY0;
  static_cast<setwid*>(parent())->SetPltSysDisM(PTY0);
  pltdisT->pltdism = PTY0;
//  shmengine::getsingleshm()->pshm_sysinfo->dismode = PTY0;
//  remoteinterface::getplatformremotehandle()->PltSetDisMod(PTY0);
}

void dsdtset::on_pushButton_13_clicked()
{
  if(PTY1 == *dsdtobj.dismod)
    {
      return;
    }
  *dsdtobj.dismod = PTY1;
  static_cast<setwid*>(parent())->SetPltSysDisM(PTY1);  
  pltdisT->pltdism = PTY1;
//  shmengine::getsingleshm()->pshm_sysinfo->dismode = PTY1;
//  remoteinterface::getplatformremotehandle()->PltSetDisMod(PTY1);
}

void dsdtset::on_pushButton_14_clicked()
{
  if(PTY2 == *dsdtobj.dismod)
    {
      return;
    }
  *dsdtobj.dismod = PTY2;
  static_cast<setwid*>(parent())->SetPltSysDisM(PTY2);  
  pltdisT->pltdism = PTY2;
//  shmengine::getsingleshm()->pshm_sysinfo->dismode = PTY2;
//  remoteinterface::getplatformremotehandle()->PltSetDisMod(PTY2);
}

void dsdtset::timerEvent(QTimerEvent *event)
{
  Q_UNUSED(event)
  //close lcd brightness
//  shmengine::getsingleshm()->pshm_sysconf->LcdpadLight = PTY0;
//  shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_LcdpadLight);
}

void dsdtset::showEvent(QShowEvent *event)
{
    refreshDate();
    refreshTime();
    return QWidget::showEvent(event);
}

void dsdtset::on_keybeepbtn_clicked()
{
  *dsdtobj.keybeepswitch = !*dsdtobj.keybeepswitch;
  if(*dsdtobj.keybeepswitch)
    {
      KeyBeepStyleOn();
    }
  else
    {
      KeyBeepStyleOff();
    }
//  shmengine::getsingleshm()->pshm_sysconf->KeyBeep = *dsdtobj.keybeepswitch;
//  shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_KeyBeep);
  return;
}

void dsdtset::SetPluginProperty(const char* name, QString value)
{
    pCalendar->setProperty(name,value);
    pTime->setProperty(name,value);
}

void dsdtset::initCalendar()
{
    pCalendar = new pltCalendar(this);
    pCalendar->move(mapToParent(QPoint(311,107)).x(),mapToParent(QPoint(311,107)).y());

    pTime = new timeSetup(this);
    pTime->move(mapToParent(QPoint(611,326)).x(),mapToParent(QPoint(611,326)).y());

}

void dsdtset::refreshDate()
{
    QString strDate,strDateFormat;
    if(dsdtobj.datetype == 0)
    {
        strDateFormat = "yyyy - MM - dd";
    }else
    {
        switch (*dsdtobj.datetype) {
        case PTY0:
            strDateFormat = "dd - MM - yyyy";
            break;
        case PTY1:
            strDateFormat = "MM - dd - yyyy";
            break;
        case PTY2:
            strDateFormat = "yyyy - MM - dd";
            break;
        default:
            strDateFormat = "yyyy - MM - dd";
            break;
        }
    }

    strDate = QDate::currentDate().toString(strDateFormat);
    ui->DateEdit->setText(strDate);

}
void dsdtset::refreshTime()
{
    QString strTime,strTimeFormat;
    strTimeFormat = "hh : mm : ss";
    strTime = QTime::currentTime().toString(strTimeFormat);
    ui->TimeEdit->setText(strTime);
}

void dsdtset::on_DateEdit_clicked()
{
    pCalendar->exec();
    ui->DateEdit->setSelection(0,0);
    refreshDate();
}

void dsdtset::on_TimeEdit_clicked()
{
    pTime->exec();
    ui->TimeEdit->setSelection(0,1);
    refreshTime();
}
