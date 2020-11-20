#include "sysinfo.h"
#include "ui_sysinfo.h"
#include "shmengine.h"

sysinfo::sysinfo(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::sysinfo)
{
  ui->setupUi(this);
  Flszsb();
}

sysinfo::~sysinfo()
{
  delete ui;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-12-02}
*/
void sysinfo::RefleshVerDate(PDEVEMSG pmsg)
{
  //14 date Johnson 20200317
  ui->label_14->setText(QString(pmsg->update).insert(4,"/").insert(7,"/"));
  //16 sw
  ui->label_16->setText(QString(pmsg->swver));
  //17hw
  ui->label_17->setText(QString(pmsg->hwver));
}



/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-12-19}
*/
void sysinfo::SetTemperSysinfo(QStringList &slist)
{
  ui->label_23->setText(slist.at(PTY0));
  ui->label_24->setText(slist.at(PTY1));
  ui->label_27->setText(slist.at(PTY2));
  ui->label_29->setText(slist.at(PTY3));
  return;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-12-19}
*/
void sysinfo::RefreshVerMsg0()
{
  QString tmpstr = QString::number(shmengine::getsingleshm()->pshm_sysconf->mainfpgaver && 0xff0000)
      + "." + QString::number(shmengine::getsingleshm()->pshm_sysconf->mainfpgaver && 0xff00)
      + "." + QString::number(shmengine::getsingleshm()->pshm_sysconf->mainfpgaver && 0xff);
  ui->label_15->setText(tmpstr);
  //  tmpstr = QString::number(shmengine::getsingleshm()->pshm_sysconf->spafpgaver && 0xff0000)
  //      + "." + QString::number(shmengine::getsingleshm()->pshm_sysconf->spafpgaver && 0xff00)
  //      + "." + QString::number(shmengine::getsingleshm()->pshm_sysconf->spafpgaver && 0xff);
  //  ui->label_18->setText(tmpstr);
  //  tmpstr = QString::number(shmengine::getsingleshm()->pshm_sysconf->cpldver && 0xff0000)
  //      + "." + QString::number(shmengine::getsingleshm()->pshm_sysconf->cpldver && 0xff00)
  //      + "." + QString::number(shmengine::getsingleshm()->pshm_sysconf->cpldver && 0xff);
  //  ui->label_20->setText(tmpstr);
  return;
}

void sysinfo::RefreshVerMsg1()
{
  QString tmpstr = QString::number(shmengine::getsingleshm()->pshm_sysconf->spafpgaver && 0xff0000)
      + "." + QString::number(shmengine::getsingleshm()->pshm_sysconf->spafpgaver && 0xff00)
      + "." + QString::number(shmengine::getsingleshm()->pshm_sysconf->spafpgaver && 0xff);
  ui->label_18->setText(tmpstr);
  return;
}

void sysinfo::RefreshVerMsg2()
{
  QString tmpstr = QString::number(shmengine::getsingleshm()->pshm_sysconf->cpldver && 0xff0000)
      + "." + QString::number(shmengine::getsingleshm()->pshm_sysconf->cpldver && 0xff00)
      + "." + QString::number(shmengine::getsingleshm()->pshm_sysconf->cpldver && 0xff);
  ui->label_20->setText(tmpstr);
  return;
}

void sysinfo::Flszsb()
{
#ifdef plt_bit_238_smart
  ui->label_12->setText("1500");
  ui->label->setText("5G SMART 15");
#endif

#ifdef plt_bit_239
  ui->label_12->setText("4300");
  ui->label->setText("5G PRO 43");
#endif

#ifdef plt_bit_238
  ui->label_12->setText("4300");
  ui->label->setText("5G PRO 43");
#endif
}




