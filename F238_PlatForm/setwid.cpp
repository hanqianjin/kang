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

setwid::setwid(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::setwid)
{
  ui->setupUi(this);
  LoadAllSetwid(INDEXBASE);
  setAttribute(Qt::WA_DeleteOnClose);
  this->setWindowModality(Qt::ApplicationModal);
  this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
  this->setGeometry(mapToGlobal(QPoint(0,0)).x(), +  mapToGlobal(QPoint(0,0)).y() + PLUSMODY + SETDETAY,this->width(),this->height());
}

setwid::~setwid()
{
  disconnect(bitsetbtngroup,SIGNAL(buttonClicked(qint32)),this,SLOT(on_buttonGroup_clicked(qint32)));
  delete pcomsetwid;
  delete pdedtsetwid;
  delete pnetsetwid;
  delete plicmanwid;
  delete phswinfowid;
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
 * @since {2019-01-23}
*/
void setwid::LoadAllSetwid(qint32 iIndex)
{
    lastsetindex = iIndex;
    pcomsetwid = new comset(this);
    pcomsetwid->setGeometry(SMX,SMY,pcomsetwid->width(),pcomsetwid->height());
    pcomsetwid->hide();
    setwidvec.append(pcomsetwid);
    pdedtsetwid = new dsdtset(this);
    pdedtsetwid->setGeometry(SMX,SMY,pdedtsetwid->width(),pdedtsetwid->height());
    pdedtsetwid->hide();
    setwidvec.append(pdedtsetwid);
    pnetsetwid = new networkset(this);
    pnetsetwid->setGeometry(SMX,SMY,pnetsetwid->width(),pnetsetwid->height());
    pnetsetwid->hide();
    setwidvec.append(pnetsetwid);
    plicmanwid = new licemana(this);
    plicmanwid->setGeometry(SMX,SMY,plicmanwid->width(),plicmanwid->height());
    plicmanwid->hide();
    setwidvec.append(plicmanwid);
    phswinfowid = new hswinfo(this);
    phswinfowid->setGeometry(SMX,SMY,phswinfowid->width(),phswinfowid->height());
    phswinfowid->hide();
    setwidvec.append(phswinfowid);
    psyswid = new sysinfo(this);
    psyswid->setGeometry(SMX,SMY,psyswid->width(),psyswid->height());
    psyswid->hide();
    setwidvec.append(psyswid);

    setwidvec.at(iIndex)->show();
    bitsetbtngroup = new QButtonGroup(this);
    bitsetbtngroup->addButton(ui->pushButton,COM_SET);
    bitsetbtngroup->addButton(ui->pushButton_2,DSDT_SET);
    bitsetbtngroup->addButton(ui->pushButton_3,NETWORK_SET);
    bitsetbtngroup->addButton(ui->pushButton_4,LICE_SET);
    bitsetbtngroup->addButton(ui->pushButton_5,HSW_SET);
    bitsetbtngroup->addButton(ui->pushButton_6,SYS_SET);
    connect(bitsetbtngroup,SIGNAL(buttonClicked(qint32)),this,SLOT(on_buttonGroup_clicked(qint32)));
    bitsetbtngroup->button(iIndex)->setChecked(true);
    return;
}


void setwid::on_clobtn_clicked()
{
  this->hide();
  return;
}

void setwid::on_buttonGroup_clicked(qint32 idIndex)
{
  setwidvec.at(lastsetindex)->hide();
  lastsetindex = idIndex;
  setwidvec.at(lastsetindex)->show();
  return;
}


