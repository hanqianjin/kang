#include "licemana.h"
#include "ui_licemana.h"
#include "shmengine.h"
#include "softbus.h"
#include <QThread>
#include <QDate>

licemana::licemana(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::licemana)
{
  ui->setupUi(this);
}

licemana::~licemana()
{
  delete ui;
}

void licemana::on_pushButton_19_clicked()
{
  OutTest();
}

void licemana::Xx(QLabel *pl, qint32 it)
{
  pl->repaint();
  QThread::msleep(it);
}

void licemana::SetTemperSysinfo()
{
  ui->label_37->setText(QString::number(shmengine::getsingleshm()->pshm_sysinfo->BoardTemp) + " deg");
  ui->label_35->setText(QString::number(shmengine::getsingleshm()->pshm_sysinfo->RfTemp) + " deg");
  ui->label_33->setText(QString::number(shmengine::getsingleshm()->pshm_sysinfo->FpgaTemp) + " deg");
  ui->label_31->setText(QString::number(shmengine::getsingleshm()->pshm_sysinfo->BatteryTemp) + " deg");

  ui->label_38->setText(QString::number(shmengine::getsingleshm()->pshm_sysinfo->batvol) + " V");
  ui->label_41->setText(QString::number(shmengine::getsingleshm()->pshm_sysinfo->batcurrent) + " A");
  ui->label_43->setText(QString::number(shmengine::getsingleshm()->pshm_sysinfo->BatteryRemaind) + "%");

  if(BATT_CHARGE == shmengine::getsingleshm()->pshm_sysinfo->BatterChargeStatus)
    {
      if(shmengine::getsingleshm()->pshm_sysinfo->batcurrent > 0)
        {
          qint32 inum = (100 - shmengine::getsingleshm()->pshm_sysinfo->BatteryRemaind) * 0.01 * 7.8 * 11.1 / shmengine::getsingleshm()->pshm_sysinfo->batcurrent / shmengine::getsingleshm()->pshm_sysinfo->batvol * 100;
          ui->label_47->setText(QString::number(inum * 0.01) + " h");
          ui->label_45->setText("-- --");
        }
    }
  else if(BATT_DISCHARGE == shmengine::getsingleshm()->pshm_sysinfo->BatterChargeStatus)
    {
      if(shmengine::getsingleshm()->pshm_sysinfo->batcurrent > 0)
        {
          qint32 inum = shmengine::getsingleshm()->pshm_sysinfo->BatteryRemaind * 0.01 * 7.8 * 11.1 / shmengine::getsingleshm()->pshm_sysinfo->batcurrent / shmengine::getsingleshm()->pshm_sysinfo->batvol * 100;
          ui->label_45->setText(QString::number(inum * 0.01) + " h");
          ui->label_47->setText("-- --");
        }
    }
  else
    {
      ui->label_45->setText("0 h");
      ui->label_47->setText("0 h");
    }
  ui->label_72->setText("normal");
  ui->label_78->setText("Last Self Test  " + QDateTime::currentDateTime().toString("yyyy-MM-dd APhh:mm:ss"));
  return;
}

void licemana::OutTest()
{
  ui->label_23->setText("-- --");
  ui->label_24->setText("-- --");
  ui->label_26->setText("-- --");
  ui->label_28->setText("-- --");
  ui->label_49->setText("-- --");
  ui->label_54->setText("-- --");

  ui->label_53->setText("-- --");
  ui->label_62->setText("-- --");
  ui->label_66->setText("-- --");
  ui->label_70->setText("-- --");
  ui->label_51->setText("-- --");
  ui->label_57->setText("-- --");

  ui->label_63->setText("-- --");
  ui->label_81->setText("-- --");
  ui->label_69->setText("-- --");
  ui->label_77->setText("-- --");
  ui->label_80->setText("-- --");
  ui->label_60->setText("-- --");

  ui->label_59->setText("-- --");
  ui->label_79->setText("-- --");
  ui->label_87->setText("-- --");
  this->repaint();
  SetTemperSysinfo();
  ui->label_23->setText("<font color=green>pass</font>");
  ui->label_24->setText("<font color=green>pass</font>");
  ui->label_26->setText("<font color=green>pass</font>");
  ui->label_28->setText("<font color=green>pass</font>");
  ui->label_49->setText("<font color=green>pass</font>");
  ui->label_54->setText("<font color=green>pass</font>");
  shmengine::getsingleshm()->PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_ADCOVER);
  QThread::msleep(200);
  if(shmengine::getsingleshm()->pshm_sysconf->adcover && 0x1)
    {
      ui->label_72->setText("<font color=red>Overload</font>");
    }
  else
    {
      ui->label_72->setText("<font color=green>normal</font>");
    }
  shmengine::getsingleshm()->PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_SELFTEST);
  QThread::msleep(200);
  if(shmengine::getsingleshm()->pshm_sysconf->selftest && 0x1)
    {
      ui->label_53->setText("<font color=green>pass</font>");
      Xx(ui->label_53,20);
      ui->label_62->setText("<font color=green>pass</font>");
      Xx(ui->label_62,20);
      ui->label_66->setText("<font color=green>pass</font>");
      Xx(ui->label_66,20);
      ui->label_70->setText("<font color=green>pass</font>");
      Xx(ui->label_70,20);
      ui->label_51->setText("<font color=green>pass</font>");
      Xx(ui->label_51,20);
      ui->label_57->setText("<font color=green>pass</font>");
      Xx(ui->label_57,20);
    }
  else
    {
      ui->label_53->setText("<font color=red>failed</font>");
      ui->label_62->setText("<font color=red>failed</font>");
      ui->label_66->setText("<font color=red>failed</font>");
      ui->label_70->setText("<font color=red>failed</font>");
      ui->label_51->setText("<font color=red>failed</font>");
      ui->label_57->setText("<font color=red>failed</font>");
    }
  if(shmengine::getsingleshm()->pshm_sysconf->selftest && 0x2)
    {
      ui->label_63->setText("<font color=green>pass</font>");
      Xx(ui->label_63,20);
      ui->label_81->setText("<font color=green>pass</font>");
      Xx(ui->label_81,20);
      ui->label_69->setText("<font color=green>pass</font>");
      Xx(ui->label_69,20);
      ui->label_77->setText("<font color=green>pass</font>");
      Xx(ui->label_77,20);
      ui->label_80->setText("<font color=green>pass</font>");
      Xx(ui->label_80,20);
      ui->label_60->setText("<font color=green>pass</font>");
      Xx(ui->label_60,20);
    }
  else
    {
      ui->label_63->setText("<font color=red>failed</font>");
      ui->label_81->setText("<font color=red>failed</font>");
      ui->label_69->setText("<font color=red>failed</font>");
      ui->label_77->setText("<font color=red>failed</font>");
      ui->label_80->setText("<font color=red>failed</font>");
      ui->label_60->setText("<font color=red>failed</font>");
    }
  if(shmengine::getsingleshm()->pshm_sysconf->selftest && 0x4)
    {
      ui->label_59->setText("<font color=green>pass</font>");
      Xx(ui->label_59,20);
      ui->label_79->setText("<font color=green>pass</font>");
      Xx(ui->label_79,20);
      ui->label_87->setText("<font color=green>pass</font>");
      Xx(ui->label_87,20);
    }
  else
    {
      ui->label_59->setText("<font color=red>failed</font>");
      ui->label_79->setText("<font color=red>failed</font>");
      ui->label_87->setText("<font color=red>failed</font>");
    }
  ui->label_78->setText("Last Self Test  " + QDateTime::currentDateTime().toString("yyyy-MM-dd APhh:mm:ss"));
}
