#ifndef DSDTSET_H
#define DSDTSET_H

#include <QWidget>
#include "pltdisthread.h"

#include "plugin/timesetup.h"
#include "plugin/pltcalendar.h"
namespace Ui {
  class dsdtset;
}


typedef struct
{
  qint32* slemod;
  qint32* dismod;
  qint32* lcdbri;
  qint32* datetype;
  qint32* soundswitch;
  qint32* soundnum;
  qint32* keybeepswitch;
}PLT_DSDT,*PPLT_DSDT;

class dsdtset : public QWidget
{
  Q_OBJECT

public:
  explicit dsdtset(QWidget *parent = 0);
  ~dsdtset();
private:
  Ui::dsdtset *ui;

private slots:
  void on_soundswithbtn_clicked();
  void on_horizontalSlider_valueChanged(int value);

  void on_date1btn_clicked();
  void on_date2btn_clicked();
  void on_date3btn_clicked();
  void on_horizontalSlider_2_valueChanged(int value);
  void on_pushButton_7_clicked();
  void on_pushButton_8_clicked();
  void on_pushButton_9_clicked();
  void on_pushButton_10_clicked();
  void on_pushButton_12_clicked();
  void on_pushButton_13_clicked();
  void on_pushButton_14_clicked();
  void on_keybeepbtn_clicked();

  void on_DateEdit_clicked();

  void on_TimeEdit_clicked();

  void on_pushButton_clicked();

  void on_pushButton_2_clicked();


private:
  PLT_DSDT dsdtobj;
  pltdisthread *pltdisT;
  void initDSDTObj(PLT_DSDT &obj);

protected:
  void timerEvent(QTimerEvent *event);
  void showEvent(QShowEvent *event);
public:
  //!<for scpi use
  void SetLcdLight(qint32 inum);
  void SetVolume(qint32 ivol);
  void SetVolSwitch(qint32 iswitch);
  void SetDateType(qint32 itype);
  void SetDisMod(qint32 imod);
  void SetSleepT(qint32 itype);
  void SetKeyBeepSwi(qint32 iswitch);

  static qint32 timerswitch;//PTY0 off;
  void ReStartSysSleep();
  qint32 sleeptimerid;
public:
  //!<for recovery use
  void SetSleepBtnCheck(qint32* iIndex);
  void SetDisBtnCheck(qint32* iIndex);
  void SetLcdBtn(qint32* iIndex);
  void SetDateBtnCheck(qint32* iIndex);
  void SetSoundSwitchBtn(qint32* iIndex);
  void SetSoundBtn(qint32* iIndex);
  void SetKeybeepBtn(qint32* iswitch);

  void SetPluginProperty(const char *name, QString value);
private:
  void KeyBeepStyleOn();
  void KeyBeepStyleOff();
  void SoundSwitchStyleOn();
  void SoundSwitchStyleOff();
  void initCalendar();
  void refreshDate();
public:
  void refreshTime();
private:
  pltCalendar* pCalendar;
  timeSetup*   pTime;
};

#endif // DSDTSET_H
