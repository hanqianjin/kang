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
#include <QKeyEvent>

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
plusmode::plusmode(QWidget *parent, quint32 *pmode, qint32 *pallmeas, qint32 inum):
  QDialog(parent),
  unokmode(*pmode),
  okaction(POFF),
  ui(new Ui::plusmode)
{
  ui->setupUi(this);
  //this->setCursor(Qt::BlankCursor);
  GetAllModeMeaIndex(pallmeas,inum);
  AddBtnGroups(pmode);

  //this will lead distortion
  //setAttribute(Qt::WA_TranslucentBackground, true);
  //this->setWindowOpacity(0.85);

  //means when receive close event will delete all resources about;
  //because outside need to use mem,so delete happened in outside;
  //setAttribute(Qt::WA_DeleteOnClose);
  this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
  //this->setGeometry(mapToParent(parent->pos()).x() + PLUSMODX,mapToParent(parent->pos()).y() + PLUSMODY,this->width(),this->height());
  this->setGeometry(mapToParent(parent->pos()).x(),mapToParent(parent->pos()).y(),this->width(),this->height() - MMD);
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
 * @since {2019-01-15;c:02-27}
*/
void plusmode::AddBtnGroups(quint32 *tmode)
{
  //by mode order
  pstrvec.append(sameasbtntext);
  pstrvec.append(rtsameasbtntext);
  pstrvec.append(intermeasbtntext);
  pstrvec.append(pmmeasbtntext);
  pstrvec.append(ltefddmeasbtntext);
  pstrvec.append(ltetddmeasbtntext);
  pstrvec.append(fgnrmeasbtntext);

  //mode
  bitbtngroup = new QButtonGroup(this);
  bitbtngroup->addButton(ui->pushButton,SA_MODE);
  bitbtngroup->addButton(ui->pushButton_2,RTSA_MODE);
  bitbtngroup->addButton(ui->pushButton_3,INTERF_MODE);
  bitbtngroup->addButton(ui->pushButton_4,PM_MODE);
  bitbtngroup->addButton(ui->pushButton_5,LTE_FDD_MODE);
  bitbtngroup->addButton(ui->pushButton_18,LTE_TDD_MODE);
  bitbtngroup->addButton(ui->pushButton_19,FIVE_G_NR);
  QObject::connect(bitbtngroup,SIGNAL(buttonClicked(int)),this,SLOT(buttonGroupClicked(qint32)));
  anamode = tmode;
  ui->backwid->setGeometry(QRect(MMX, MMY, MMW, MMH));
  bitbtngroup->button(*tmode)->setChecked(true);

  btnwidvec.append(ui->sameawid);
  btnwidvec.append(ui->rtsameawid);
  btnwidvec.append(ui->intermeawid);
  btnwidvec.append(ui->pmmeawid);
  btnwidvec.append(ui->ltefddmeawid);
  btnwidvec.append(ui->ltetddmeawid);
  btnwidvec.append(ui->fivegnrmeawid);

  //measure--sa
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
  ui->pushButton_13->hide();
  ui->pushButton_14->hide();
  QObject::connect(meabtngroup,SIGNAL(buttonClicked(int)),this,SLOT(meaGroupClicked(qint32)));
  ui->sameawid->setGeometry(QRect(MX, MY, MW, MH));
  ui->sameawid->hide();
  meabtngroup->button(unokmeas[PTY0])->setChecked(true);

  //measure--rtsa
  rtsabtngroup = new QButtonGroup(this);
  rtsabtngroup->addButton(ui->pushButton_30,PERSIS_SPEC_MEAS);
  rtsabtngroup->addButton(ui->pushButton_37,PERSIS_SPECGRAM_MEAS);
  rtsabtngroup->addButton(ui->pushButton_38,PERSIS_DENSITY_MEAS);
 // rtsabtngroup->addButton(ui->pushButton_39,PERSIS_DENSITY_SPECGRAM_MEAS);
  ui->pushButton_39->hide();
  QObject::connect(rtsabtngroup,SIGNAL(buttonClicked(int)),this,SLOT(rtsameaGroupClicked(qint32)));
  ui->rtsameawid->setGeometry(QRect(MX, MY, MW, MH));
  ui->rtsameawid->hide();
  rtsabtngroup->button(unokmeas[PTY1])->setChecked(true);

  //measure--inter
  intertnmgroup = new QButtonGroup(this);
  intertnmgroup->addButton(ui->pushButton_43,ISPEC_MEAS);
  intertnmgroup->addButton(ui->pushButton_48,ISPECGRAM_MEAS);
  intertnmgroup->addButton(ui->pushButton_45,IRSSI_MEAS);
  intertnmgroup->addButton(ui->pushButton_46,ICM_MEAS);
  intertnmgroup->addButton(ui->pushButton_47,IPERSIS_SPEC_MEAS);
  intertnmgroup->addButton(ui->pushButton_51,IPERSIS_SPECGRAM_MEAS);
  QObject::connect(intertnmgroup,SIGNAL(buttonClicked(int)),this,SLOT(intermeaGroupClicked(qint32)));
  ui->intermeawid->setGeometry(QRect(MX, MY + 1, MW, MH));
  ui->intermeawid->hide();
  intertnmgroup->button(unokmeas[PTY2])->setChecked(true);

  //measure--powermeter
  pmbtngroup = new QButtonGroup(this);
  pmbtngroup->addButton(ui->pushButton_49,INTER_PM_MEAS);
  pmbtngroup->addButton(ui->pushButton_53,EXTERN_PM_MEAS);
  QObject::connect(pmbtngroup,SIGNAL(buttonClicked(int)),this,SLOT(pmmeaGroupClicked(qint32)));
  ui->pmmeawid->setGeometry(QRect(MX, MY + 1, MW, MH));
  ui->pmmeawid->hide();
  pmbtngroup->button(unokmeas[PTY3])->setChecked(true);

  //measure--ltefdd
  ui->pushButton_60->setVisible(false);
  ui->pushButton_61->setVisible(false);
  ltefddbtngroup = new QButtonGroup(this);
  ltefddbtngroup->addButton(ui->pushButton_56,FDD_SPECTRUM_MEAS);
  ltefddbtngroup->addButton(ui->pushButton_63,FDD_CP_MEAS);
  ltefddbtngroup->addButton(ui->pushButton_59,FDD_OBW_MEAS);
  //ltefddbtngroup->addButton(ui->pushButton_60,FDD_SEM_MEAS);
  //ltefddbtngroup->addButton(ui->pushButton_61,FDD_ACLR_MEAS);
  ltefddbtngroup->addButton(ui->pushButton_54,FDD_PTF_MEAS);  
  ltefddbtngroup->addButton(ui->pushButton_55,FDD_CONSTELL_MEAS);
  ltefddbtngroup->addButton(ui->pushButton_57,FDD_DATAC_MEAS);
  ltefddbtngroup->addButton(ui->pushButton_62,FDD_CONTROLC_MEAS);
  ltefddbtngroup->addButton(ui->pushButton_64,FDD_FRAMEANA_MEAS);  
  ltefddbtngroup->addButton(ui->pushButton_66,FDD_DAM_MEAS);
  ltefddbtngroup->addButton(ui->pushButton_67,FDD_CHASCA_MEAS);
  ltefddbtngroup->addButton(ui->pushButton_68,FDD_IDS_MEAS);
  ltefddbtngroup->addButton(ui->pushButton_69,FDD_RMAP_MEAS);
  ltefddbtngroup->addButton(ui->pushButton_70,FDD_CONCHA_MEAS);
  ltefddbtngroup->addButton(ui->pushButton_71,FDD_DATAGRAM_MEAS);
  ltefddbtngroup->addButton(ui->pushButton_72,FDD_CARAGG_MEAS);
  ui->pushButton_73->hide();
  ui->pushButton_94->hide();
  ui->pushButton_95->hide();
  ui->pushButton_96->hide();
  ui->pushButton_97->hide();
  ui->pushButton_98->hide();



  QObject::connect(ltefddbtngroup,SIGNAL(buttonClicked(int)),this,SLOT(ltefddmeaGroupClicked(qint32)));
  ui->ltefddmeawid->setGeometry(QRect(MX, MY + 1, MW << 1, MH));
  ui->ltefddmeawid->hide();
  ltefddbtngroup->button(unokmeas[PTY4])->setChecked(true);

  //measure--ltetdd
  ui->pushButton_79->setVisible(false);
  ui->pushButton_80->setVisible(false);
  ltetddbtngroup = new QButtonGroup(this);
  ltetddbtngroup->addButton(ui->pushButton_76,TDD_SPECTRUM_MEAS);
  ltetddbtngroup->addButton(ui->pushButton_81,TDD_CP_MEAS);
  ltetddbtngroup->addButton(ui->pushButton_78,TDD_OBW_MEAS);
  //ltetddbtngroup->addButton(ui->pushButton_79,TDD_SEM_MEAS);
  //ltetddbtngroup->addButton(ui->pushButton_80,TDD_ACLR_MEAS);
  ltetddbtngroup->addButton(ui->pushButton_74,TDD_PTF_MEAS);
  ltetddbtngroup->addButton(ui->pushButton_77,TDD_PTS_MEAS);
  ltetddbtngroup->addButton(ui->pushButton_75,TDD_CONSTELL_MEAS);
  ltetddbtngroup->addButton(ui->pushButton_82,TDD_DATAC_MEAS);
  ltetddbtngroup->addButton(ui->pushButton_83,TDD_CONTROLC_MEAS);
  ltetddbtngroup->addButton(ui->pushButton_84,TDD_FRAMEANA_MEAS);
  ltetddbtngroup->addButton(ui->pushButton_85,TDD_TAE_MEAS);
  ltetddbtngroup->addButton(ui->pushButton_86,TDD_DAM_MEAS);
  ltetddbtngroup->addButton(ui->pushButton_87,TDD_CHASCA_MEAS);
  ltetddbtngroup->addButton(ui->pushButton_88,TDD_IDS_MEAS);
  ltetddbtngroup->addButton(ui->pushButton_89,TDD_RMAP_MEAS);
  ltetddbtngroup->addButton(ui->pushButton_90,TDD_CONCHA_MEAS);
  ltetddbtngroup->addButton(ui->pushButton_91,TDD_DATAGRAM_MEAS);
  ltetddbtngroup->addButton(ui->pushButton_92,TDD_CARAGG_MEAS);
  ui->pushButton_93->hide();
  ui->pushButton_99->hide();
  ui->pushButton_100->hide();
  ui->pushButton_101->hide();
  ui->pushButton_102->hide();
  ui->pushButton_103->hide();


  QObject::connect(ltetddbtngroup,SIGNAL(buttonClicked(int)),this,SLOT(ltetddmeaGroupClicked(qint32)));
  ui->ltetddmeawid->setGeometry(QRect(MX, MY + 1, MW << 1, MH));
  ui->ltetddmeawid->hide();
  ltetddbtngroup->button(unokmeas[PTY5])->setChecked(true);

  //measure--5Gnr
  fgnrbtngroup = new QButtonGroup(this);

  fgnrbtngroup->addButton(ui->pushButton_52,FGNR_SPECTRUM);
  fgnrbtngroup->addButton(ui->pushButton_105,FGNR_CHANNEL_POWER);
  fgnrbtngroup->addButton(ui->pushButton_106,FGNR_OCCUPIED_BW);
  fgnrbtngroup->addButton(ui->pushButton_107,FGNR_MULTI_BEAM);
  fgnrbtngroup->addButton(ui->pushButton_108,FGNR_SINGLE_BEAM);
  fgnrbtngroup->addButton(ui->pushButton_111,FGNR_PCI_SACNER);
  fgnrbtngroup->addButton(ui->pushButton_109,FGNR_EIRP_NORMAL);
  fgnrbtngroup->addButton(ui->pushButton_110,FGNR_EIRP_QUICK);
  fgnrbtngroup->addButton(ui->pushButton_112,ROUTE_MAP);


  QObject::connect(fgnrbtngroup,SIGNAL(buttonClicked(int)),this,SLOT(fgnrmeaGroupClicked(qint32)));
  ui->fivegnrmeawid->setGeometry(QRect(MX, MY + 1, MW << 1, MH));
  ui->fivegnrmeawid->hide();
  fgnrbtngroup->button(unokmeas[PTY6])->setChecked(true);

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
  QObject::disconnect(bitbtngroup,SIGNAL(buttonClicked(int)),this,SLOT(buttonGroupClicked(qint32)));
  QObject::disconnect(meabtngroup,SIGNAL(buttonClicked(int)),this,SLOT(meaGroupClicked(qint32)));
  QObject::disconnect(rtsabtngroup,SIGNAL(buttonClicked(int)),this,SLOT(rtsameaGroupClicked(qint32)));
  QObject::disconnect(intertnmgroup,SIGNAL(buttonClicked(int)),this,SLOT(intermeaGroupClicked(qint32)));
  QObject::disconnect(pmbtngroup,SIGNAL(buttonClicked(int)),this,SLOT(pmmeaGroupClicked(qint32)));
  QObject::disconnect(ltetddbtngroup,SIGNAL(buttonClicked(int)),this,SLOT(ltetddmeaGroupClicked(qint32)));
  QObject::disconnect(fgnrbtngroup,SIGNAL(buttonClicked(int)),this,SLOT(fgnrmeaGroupClicked(qint32)));
  delete ui;
  delete bitbtngroup;
  delete meabtngroup;
  delete rtsabtngroup;
  delete intertnmgroup;
  delete pmbtngroup;
  delete ltetddbtngroup;
  delete fgnrbtngroup;
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

void plusmode::SetPlusDisMode(qint32 imod)
{
  imod = imod == PTY1 ? PTY0 : imod;
  this->setProperty("pltdismode",pltdismod[imod]);
  setStyle(QApplication::style());
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
  pmodemeasbuffer = pmeas;
  for(i = 0;i < inum;i++)
    {
      *(unokmeas + i) = *(pmeas +i);
    }
  return;
}

//mode
void plusmode::buttonGroupClicked(qint32 idIndex)
{
  btnwidvec.at(unokmode)->hide();
  unokmode = idIndex;
  btnwidvec.at(unokmode)->show();
  return;
}

//measure
void plusmode::meaGroupClicked(qint32 idIndex)
{
  unokmeas[INDEXBASE] = idIndex;
  return;
}

void plusmode::rtsameaGroupClicked(qint32 idIndex)
{
  unokmeas[INDEXBASE + PTY1] = idIndex;
  return;
}

void plusmode::intermeaGroupClicked(qint32 idIndex)
{
  unokmeas[INDEXBASE + PTY2] = idIndex;
  return;
}

void plusmode::pmmeaGroupClicked(qint32 idIndex)
{
  unokmeas[INDEXBASE + PTY3] = idIndex;
  return;
}

void plusmode::ltefddmeaGroupClicked(qint32 idIndex)
{
  unokmeas[INDEXBASE + PTY4] = idIndex;
  return;
}

void plusmode::ltetddmeaGroupClicked(qint32 idIndex)
{
  unokmeas[INDEXBASE + PTY5] = idIndex;
  return;
}

void plusmode::fgnrmeaGroupClicked(qint32 idIndex)
{
  unokmeas[INDEXBASE + PTY6] = idIndex;
  return;
}

void plusmode::on_pushButton_15_clicked()
{
  okaction = POFF;
  this ->close();
  return;
}

//ok
//[c:20190124;c:02-27;c03-21]
void plusmode::on_pushButton_16_clicked()
{
  okaction = PON;
  *anamode = unokmode;
  qint32 iIndex = unokmeas[*anamode];
  modstr = modbtntext[*anamode] + QObject::tr("<BR/><span style=\"font-weight:normal;\">%1</span>").arg(*(pstrvec.at(*anamode) + iIndex));
  //reflesh measure index buffer
  *(pmodemeasbuffer + *anamode) = iIndex;
  this->close();
  return;
}

//cancel
void plusmode::on_pushButton_17_clicked()
{
  okaction = POFF;
  this->close();
  return;
}

/**
 * @brief when esc key event close
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-03-05;c08-22}
*/
void plusmode::keyPressEvent(QKeyEvent *event)
{
  if(Qt::Key_PowerOff == event->key())
    {
      QApplication::sendEvent(parent(),event);
    }
  else if(Qt::Key_Escape == event->key())
    {
      on_pushButton_17_clicked();
    }
  else if(Qt::Key_Shift == event->key())
    {
      QApplication::sendEvent(parent(),event);
      on_pushButton_17_clicked();
    }
  return;
}



