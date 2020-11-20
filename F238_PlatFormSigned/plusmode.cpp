/****************************************Copyright (c)****************************************************
**
**                     DaHao Info Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:plusmode.cpp
** Latest Version: V0.0.1
** Latest modified Date:  2019-01-07
** Modified by:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by: BitYang
** Created date: 2019-01-07
** Descriptions:for plus to add ana mode
**
*********************************************************************************************************/
#include "plusmode.h"
#include "ui_plusmode.h"

plusmode::plusmode(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::plusmode)
{
  ui->setupUi(this);
}

/**
 * @brief
 * @param[in/out]pmode
 * @param[in/out]pmeaitem
 * @param[in]pallmeas for inner to know all mode's measure items
 * @param[in]inum the num of ana mode
 * @return
 * @note
 * @author steve
 * @since {2019-01-15}
*/
plusmode::plusmode(QWidget *parent, quint32 *pmode, quint32 *pmeaitem, qint32 *pallmeas, qint32 inum, QVector<QString> *meastrvec):
  QDialog(parent), 
  unokmode(*pmode),
  okaction(POFF),
  pmeastrvec(meastrvec),
  ui(new Ui::plusmode)
{
  ui->setupUi(this);
  GetAllModeMeaIndex(pallmeas,inum);
  AddBtnGroups(pmode,pmeaitem);


  //this will lead distortion
  //setAttribute(Qt::WA_TranslucentBackground, true);
  this->setWindowOpacity(0.85);

  //means when receive close event will delete all resources about;
  //because outside need to use mem,so delete happened in outside;
  //setAttribute(Qt::WA_DeleteOnClose);
  this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
  //this->setGeometry(mapToParent(parent->pos()).x() + PLUSMODX,mapToParent(parent->pos()).y() + PLUSMODY,this->width(),this->height());
  this->setGeometry(mapToParent(parent->pos()).x(),mapToParent(parent->pos()).y(),this->width(),this->height());
}

plusmode::~plusmode()
{
  ReleaseRes();
}

/**
 * @brief loading button for some control
 * @param[in]tmode anamode
 * @param[in]tmeas mode's measure
 * @return
 * @note
 * @author steve
 * @since {2019-01-15}
*/
void plusmode::AddBtnGroups(quint32 *tmode, quint32 *tmea)
{
  //by mode order
  pstrvec.append(sameasbtntext);
  pstrvec.append(rtsameasbtntext);
  pstrvec.append(intermeasbtntext);
  pstrvec.append(pmmeasbtntext);
  pstrvec.append(letddmeasbtntext);

  //mode
  bitbtngroup = new QButtonGroup(this);
  bitbtngroup->addButton(ui->pushButton,SA_MODE);
  bitbtngroup->addButton(ui->pushButton_2,RTSA_MODE);
  bitbtngroup->addButton(ui->pushButton_3,INTERF_MODE);
  bitbtngroup->addButton(ui->pushButton_4,PM_MODE);
  bitbtngroup->addButton(ui->pushButton_5,LTE_TDD_MODE);
  anamode = tmode;
  connect(bitbtngroup,SIGNAL(buttonClicked(qint32)),this,SLOT(on_buttonGroup_clicked(qint32)));
  bitbtngroup->button(*tmode)->setChecked(true);

  btnwidvec.append(ui->sameawid);
  btnwidvec.append(ui->rtsameawid);
  btnwidvec.append(ui->intermeawid);
  btnwidvec.append(ui->pmmeawid);
  btnwidvec.append(ui->ltetddmeawid);

  //measure--sa
  measitem = tmea;
  meabtngroup = new QButtonGroup(this);
  meabtngroup->addButton(ui->pushButton_6,SPEC_MEAS);  
  meabtngroup->addButton(ui->pushButton_7,CHPOWER_MEAS);
  meabtngroup->addButton(ui->pushButton_8,OCCBW_MEAS);
  meabtngroup->addButton(ui->pushButton_9,SPEEMIMASK_MEAS);
  meabtngroup->addButton(ui->pushButton_10,ACP_MEAS);
  meabtngroup->addButton(ui->pushButton_11,MACP_MEAS);
  meabtngroup->addButton(ui->pushButton_12,SPUEMIMASK_MEAS);
  meabtngroup->addButton(ui->pushButton_13,FIELD_MEAS);
  meabtngroup->addButton(ui->pushButton_14,ANADEMO_MEAS);
  connect(meabtngroup,SIGNAL(buttonClicked(qint32)),this,SLOT(on_meaGroup_clicked(qint32)));
  ui->sameawid->setGeometry(QRect(MX, MY, MW, MH));
  ui->sameawid->hide();
  meabtngroup->button(unokmeas[0])->setChecked(true);
  //measure--rtsa
  rtsabtngroup = new QButtonGroup(this);
  rtsabtngroup->addButton(ui->pushButton_30,PERSIS_SPEC_MEAS);
  rtsabtngroup->addButton(ui->pushButton_37,PERSIS_SPECGRAM_MEAS);
  connect(rtsabtngroup,SIGNAL(buttonClicked(qint32)),this,SLOT(on_rtsameaGroup_clicked(qint32)));
  ui->rtsameawid->setGeometry(QRect(MX, MY, MW, MH));
  ui->rtsameawid->hide();
  rtsabtngroup->button(unokmeas[1])->setChecked(true);
  //measure--inter
  intertnmgroup = new QButtonGroup(this);
  intertnmgroup->addButton(ui->pushButton_43,ISPEC_MEAS);
  intertnmgroup->addButton(ui->pushButton_48,ISPECGRAM_MEAS);
  intertnmgroup->addButton(ui->pushButton_45,IRSSI_MEAS);
  intertnmgroup->addButton(ui->pushButton_46,ICM_MEAS);
  intertnmgroup->addButton(ui->pushButton_47,IPERSIS_SPEC_MEAS);
  intertnmgroup->addButton(ui->pushButton_51,IPERSIS_SPECGRAM_MEAS);
  connect(intertnmgroup,SIGNAL(buttonClicked(qint32)),this,SLOT(on_intermeaGroup_clicked(qint32)));
  ui->intermeawid->setGeometry(QRect(MX, MY, MW, MH));
  ui->intermeawid->hide();
  intertnmgroup->button(unokmeas[2])->setChecked(true);
  //measure--powermeter
  pmbtngroup = new QButtonGroup(this);
  pmbtngroup->addButton(ui->pushButton_49,INTER_PM_MEAS);
  pmbtngroup->addButton(ui->pushButton_53,EXTERN_PM_MEAS);
  connect(pmbtngroup,SIGNAL(buttonClicked(qint32)),this,SLOT(on_pmmeaGroup_clicked(qint32)));
  ui->pmmeawid->setGeometry(QRect(MX, MY, MW, MH));
  ui->pmmeawid->hide();
  pmbtngroup->button(unokmeas[3])->setChecked(true);
  //measure--ltetdd
  ltetddbtngroup = new QButtonGroup(this);
  ltetddbtngroup->addButton(ui->pushButton_56,TDD_CP_MEAS);
  ltetddbtngroup->addButton(ui->pushButton_63,TDD_OBW_MEAS);
  ltetddbtngroup->addButton(ui->pushButton_59,TDD_SEM_MEAS);
  ltetddbtngroup->addButton(ui->pushButton_60,TDD_ACP_MEAS);
  ltetddbtngroup->addButton(ui->pushButton_61,TDD_MACP_MEAS);
  ltetddbtngroup->addButton(ui->pushButton_54,TDD_SPUEM_MEAS);
  ltetddbtngroup->addButton(ui->pushButton_58,TDD_PTF_MEAS);
  ltetddbtngroup->addButton(ui->pushButton_55,TDD_PTS_MEAS);
  ltetddbtngroup->addButton(ui->pushButton_57,TDD_DC_MEAS);
  connect(ltetddbtngroup,SIGNAL(buttonClicked(qint32)),this,SLOT(on_ltetddmeaGroup_clicked(qint32)));
  ui->ltetddmeawid->setGeometry(QRect(MX, MY, MW, MH));
  ui->ltetddmeawid->hide();
  ltetddbtngroup->button(unokmeas[4])->setChecked(true);

  btnwidvec.at(*tmode)->show();
  return;
}

/**
 * @brief release self resources
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-01-15}
*/
void plusmode::ReleaseRes()
{
  disconnect(bitbtngroup,SIGNAL(buttonClicked(qint32)),this,SLOT(on_buttonGroup_clicked(qint32)));
  disconnect(meabtngroup,SIGNAL(buttonClicked(qint32)),this,SLOT(on_meaGroup_clicked(qint32)));
  disconnect(rtsabtngroup,SIGNAL(buttonClicked(qint32)),this,SLOT(on_rtsameaGroup_clicked(qint32)));
  disconnect(intertnmgroup,SIGNAL(buttonClicked(qint32)),this,SLOT(on_intermeaGroup_clicked(qint32)));
  disconnect(pmbtngroup,SIGNAL(buttonClicked(qint32)),this,SLOT(on_pmmeaGroup_clicked(qint32)));
  disconnect(ltetddbtngroup,SIGNAL(buttonClicked(qint32)),this,SLOT(on_ltetddmeaGroup_clicked(qint32)));
  delete ui;
  delete bitbtngroup;
  delete meabtngroup;
  delete rtsabtngroup;
  delete intertnmgroup;
  delete pmbtngroup;
  delete ltetddbtngroup;
}

/**
 * @brief get mode name str
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-01-08}
*/
QString plusmode::getmodstr() const
{
  return modstr;
}

/**
 * @brief when setting ok outside will konw
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-01-15}
*/
qint32 plusmode::getdostate() const
{
  return okaction;
}

/**
 * @brief get all measures
 * @param[in]pmeas
 * @param[in] inum
 * @return
 * @note
 * @author steve
 * @since {2019-01-15}
*/
void plusmode::GetAllModeMeaIndex(qint32 *pmeas, qint32 inum)
{
  qint32 i = 0;
  for(i = 0;i < inum;i++)
    {
      *(unokmeas + i) = *(pmeas +i);
    }
  return;
}

//mode
void plusmode::on_buttonGroup_clicked(qint32 idIndex)
{
  btnwidvec.at(unokmode)->hide();
  unokmode = idIndex;
  btnwidvec.at(unokmode)->show();
  return;
}

//measure
void plusmode::on_meaGroup_clicked(qint32 idIndex)
{
  unokmeas[INDEXBASE] = idIndex;
  return;
}

void plusmode::on_rtsameaGroup_clicked(qint32 idIndex)
{
  unokmeas[INDEXBASE + 1] = idIndex;
  return;
}

void plusmode::on_intermeaGroup_clicked(qint32 idIndex)
{
  unokmeas[INDEXBASE + 2] = idIndex;
  return;
}

void plusmode::on_pmmeaGroup_clicked(qint32 idIndex)
{
  unokmeas[INDEXBASE + 3] = idIndex;
  return;
}

void plusmode::on_ltetddmeaGroup_clicked(qint32 idIndex)
{
  unokmeas[INDEXBASE + 4] = idIndex;
  return;
}

//ok
//[c:20190124]
void plusmode::on_pushButton_16_clicked()
{
  okaction = PON;
  *anamode = unokmode;
  *measitem = unokmeas[*anamode];
  modstr = modbtntext[*anamode] + *(pstrvec.at(*anamode) + *measitem);
  (*pmeastrvec)[*anamode]= *(pstrvec.at(*anamode) + *measitem);
  this->close();
  return;
}

//cancel
void plusmode::on_pushButton_17_clicked()
{
  okaction = POFF;
  this ->close();
  return;
}

