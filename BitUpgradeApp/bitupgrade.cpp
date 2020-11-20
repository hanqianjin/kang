/****************************************Copyright (c)****************************************************
**
**                     DaHao Info Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:
** Latest Version: V0.0.1
** Latest modified Date:  2019-11-26
** Modified by:
** Descriptions:for update
**
**--------------------------------------------------------------------------------------------------------
** Created by: BitYang
** Created date: 2019-11-26
** Descriptions:
**
*********************************************************************************************************/
#include "bitupgrade.h"
#include "ui_bitupgrade.h"
#include "sys/sem.h"
#include "sys/shm.h"
#include <QFile>

#define CALC_SHM_KEY 5531

bitupgrade::bitupgrade(QWidget *parent) :
  QMainWindow(parent),
  circle(1),
  finper(0),
  ui(new Ui::bitupgrade)
{
  ui->setupUi(this);
  ui->pushButton->hide();
  midper = 0;
  void* temptr = 0;  
  shm_calnot_id = shmget((key_t)CALC_SHM_KEY,sizeof(SHM_NOTIC),IPC_CREAT | 0777);
  if  (-1 == shm_calnot_id)    {

    }
  else
    {
      temptr= shmat(shm_calnot_id, (void*)0, 0);
      if (temptr == (void*)-1)
        {

        }
      pshm_calnotic = static_cast<PSHM_NOTIC>(temptr);
    } 
  connect(this, SIGNAL(dosig()), this, SLOT(doslots()));

//  pSaAna = new BitSA(this);
//  pSaAna->setGeometry(QRect(0,0,30,20));

  tid = startTimer(1000);
  setWindowFlags(Qt::FramelessWindowHint);
  QApplication::setOverrideCursor(Qt::/*ArrowCursor*/BlankCursor);
}

bitupgrade::~bitupgrade()
{ 
  disconnect(bitupaction, SIGNAL(Upgradesig()), this, SLOT(DoEnginer()));
  delete bitupaction;
  delete ui;
}

void bitupgrade::UpEngine()
{
  bitupaction = new upaction();
  connect(bitupaction, SIGNAL(UpGradeStage(qint32)), this, SLOT(ShowUpStage(qint32)));
  connect(bitupaction, SIGNAL(Upgradesig()), this, SLOT(DoEnginer()));
  bitupaction->sendflag = 1;
  bitupaction->start();
}

void bitupgrade::timerEvent(QTimerEvent *event)
{
  Q_UNUSED(event)
  if(-1 == pshm_calnotic->notic)
    {
      //system("rm /app/*.log");
      pshm_calnotic->notic = -2;
      emit dosig();
    }
  if(circle > 6)
    circle = 1;
  if(1 == circle)
    {
      ui->label_3->setText(".");
    }
  else if(2 == circle)
    {
      ui->label_3->setText(". .");
    }
  else if(3 == circle)
    {
      ui->label_3->setText(". . .");
    }
  else if(4 == circle)
    {
      ui->label_3->setText(". . . .");
    }
  else if(5 == circle)
    {
      ui->label_3->setText(". . . . .");
    }
  else if(6 == circle)
    {
      ui->label_3->setText(". . . . . .");
    }
  circle++;
}

#define Bit_Whole_Refresh 1
void bitupgrade::DoEnginer()
{
  finper++;
  qint32 tmper = 100 * finper / bitupaction->sumitem;
  //do action
#if Bit_Whole_Refresh
  bitupaction->Ganba(bitupaction->puplist + finper - 1);
#endif
  while(midper != tmper)
    {
      ui->label->setText(QString::number(midper) + " %");
      this->repaint();
      midper++;
      if(midper > 100)
        {
          break;
        }
    }

  if(finper == bitupaction->sumitem)
    {      
      ui->label->setText("100 %");      
      bitupaction->mflag = 0;
      killTimer(tid);
#if Bit_Whole_Refresh
      bitupaction->SaveDevelopMsg();
#endif

      system("/bin/sync");
      ui->label_3->setText("Firmware update is ready! Restart to complete the update");
    }
  bitupaction->sendflag = 1;
}

void bitupgrade::ShowUpStage(qint32 istage)
{
  if(0 == istage)
    {
//      ui->label->setText("load packages");
      ui->label->setText("Preparing to install updates");
    }
  else if(1 == istage)
    {
//      ui->label->setText("decompress packages");
      ui->label->setText("Preparing to install updates");
    }
  else if(2 == istage)
    {
      ui->label->setText("Preparing to install updates");
    }
  else if(-1 == istage)
    {
      killTimer(tid);
      ui->label->setText("not found update configure file,update failed");
    }
  else if(-3 == istage)
    {
      killTimer(tid);
      ui->label->setText("decompress packets failed,update failed");
    }
  else if(-2 == istage)
    {
      killTimer(tid);
      ui->label->setText("100 %");
      ui->label_3->setText("Firmware update is ready! Restart to complete the update");
    }
}

void bitupgrade::doslots()
{
  pshm_calnotic->notic = -2;
  this->show();
  while(this->isHidden()){}
  UpEngine();
}

void bitupgrade::on_pushButton_clicked()
{
  pshm_calnotic->notic = -1;
}
