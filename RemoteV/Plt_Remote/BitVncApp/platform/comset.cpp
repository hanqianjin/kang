#include "comset.h"
#include "ui_comset.h"
#include "softbus.h"
#include "remoteinterface.h"

comset::comset(QWidget *parent) :
  QWidget(parent),
  refsource(INNER10M),
  ui(new Ui::comset)
{
  ui->setupUi(this);
  pnwid = NULL;
}

comset::~comset()
{
  delete ui;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-04-25;c05-23;08-22}
*/
void comset::PltSetRef(quint32 iref)
{
//  shmengine::getsingleshm()->pshm_sysconf->refset = iref;
//  shmengine::getsingleshm()->PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_Ref);
  //call all ana mode to change ui states
  remoteinterface::getplatformremotehandle()->SetRefUiStates(*comvar.pref);
}

/**
 * @brief for first time to recover state
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-05-20}
*/
void comset::SetRefBtnCheck(qint32* iIndex)
{
  comvar.pref = iIndex;
  quint32 iref = INNER10M;
  if(PTY0 == *iIndex)
    {
      ui->interrefbtn->setChecked(true);
      iref = INNER10M;
    }
  else if(PTY1 == *iIndex)
    {
      ui->ext10btn->setChecked(true);
      iref = EXT10M;
    }
  else if(PTY2 == *iIndex)
    {
      ui->ext13btn->setChecked(true);
      iref = EXT13M;
    }
  else if(PTY3 == *iIndex)
    {
      ui->ext15btn->setChecked(true);
      iref = EXT15M;
    }
  else if(PTY4 == *iIndex)
    {
      ui->gpsrefbtn->setChecked(true);
      iref = GPSREF;
    }
  PltSetRef(iref);
}

void comset::SetPowerBtnCheck(qint32 *iIndex)
{
  comvar.ppower = iIndex;
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

void comset::SetLangBtnCheck(qint32 *iIndex)
{
  comvar.plang = iIndex;
  if(PTY0 == *iIndex)
    {
      ui->pushButton_15->setChecked(true);
    }
  else if(PTY1 == *iIndex)
    {
      ui->pushButton_16->setChecked(true);
    }
  else if(PTY2 == *iIndex)
    {
      ui->pushButton_17->setChecked(true);
    }
  else if(PTY3 == *iIndex)
    {
      ui->pushButton_18->setChecked(true);
    }
}

void comset::GetNowAnaMode(quint32 *inowmode)
{
  comvar.panamode = inowmode;
  return;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-09-12}
*/
void comset::GetDisModeExt(qint32 *idismode)
{
  comvar.pdismode = idismode;
}

void comset::on_interrefbtn_clicked()
{
  refsource = INNER10M;
  *comvar.pref = PTY0;
  PltSetRef(refsource);
}

void comset::on_ext10btn_clicked()
{
  refsource = EXT10M;
  *comvar.pref = PTY1;
  PltSetRef(refsource);
}

void comset::on_ext13btn_clicked()
{
  refsource = EXT13M;
  *comvar.pref = PTY2;
  PltSetRef(refsource);
}

void comset::on_ext15btn_clicked()
{
  refsource = EXT15M;
  *comvar.pref = PTY3;
  PltSetRef(refsource);
}

void comset::on_gpsrefbtn_clicked()
{
  refsource = GPSREF;
  *comvar.pref = PTY4;
  PltSetRef(refsource);
}

/**
 * @brief 12~14 for power reset ctrl
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-05-21}
*/
void comset::on_pushButton_12_clicked()
{
  *comvar.ppower = PTY0;
}

void comset::on_pushButton_13_clicked()
{
  *comvar.ppower = PTY1;
}

void comset::on_pushButton_14_clicked()
{
  *comvar.ppower = PTY2;
}

/**
 * @brief 15~17 for language ctrl
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-05-21}
*/
void comset::on_pushButton_15_clicked()
{
  *comvar.plang = PTY0;
}

void comset::on_pushButton_16_clicked()
{
  *comvar.plang = PTY1;
}

void comset::on_pushButton_17_clicked()
{
  *comvar.plang = PTY2;
}

void comset::on_pushButton_18_clicked()
{
  *comvar.plang = PTY3;
}

/**
 * @brief save now sys states and running mode states to user
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-05-22}
*/
void comset::on_pushButton_20_clicked()
{
  if(NULL == pnwid)
    {
      pnwid = new pltnotice(*comvar.panamode,PTY0,this);
      pnwid->move(PLTX,PLTY);
      pnwid->SetNoticDisMode(*comvar.pdismode);
      pnwid->exec();
      qint32 isel = pnwid->GetSelectState();
      delete pnwid;
      pnwid = NULL;
      if(isel)
        {
          //save now state to user.cond
          remoteinterface::getplatformremotehandle()->PltSaveStates(PTY2 + 3);
        }
    }
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-08-22}
*/
void comset::SetFreqRef(quint32 iref)
{
  if(iref >= NONEREF)
    return;
  *comvar.pref = iref;
  quint32 iset = INNER10M;
  if(PTY0 == iref)
    {
      ui->interrefbtn->setChecked(true);
      iset = INNER10M;
    }
  else if(PTY1 == iref)
    {
      ui->ext10btn->setChecked(true);
      iset = EXT10M;
    }
  else if(PTY2 == iref)
    {
      ui->ext13btn->setChecked(true);
      iset = EXT13M;
    }
  else if(PTY3 == iref)
    {
      ui->ext15btn->setChecked(true);
      iset = EXT15M;
    }
  else if(PTY4 == iref)
    {
      ui->gpsrefbtn->setChecked(true);
      iset = GPSREF;
    }
  PltSetRef(iset);
}

void comset::SetLanType(qint32 itype)
{
  if(itype >= NONELAN)
    return;
  *comvar.plang = itype;
  if(PTY0 == itype)
    {
      ui->pushButton_15->setChecked(true);
    }
  else if(PTY1 == itype)
    {
      ui->pushButton_16->setChecked(true);
    }
  else if(PTY2 == itype)
    {
      ui->pushButton_17->setChecked(true);
    }
  else if(PTY3 == itype)
    {
      ui->pushButton_18->setChecked(true);
    }
}

void comset::SetPowerType(qint32 itype)
{
  if(itype > PTY2)
    return;
  *comvar.ppower = itype;
  if(PTY0 == itype)
    {
      ui->pushButton_12->setChecked(true);
    }
  else if(PTY1 == itype)
    {
      ui->pushButton_13->setChecked(true);
    }
  else if(PTY2 == itype)
    {
      ui->pushButton_14->setChecked(true);
    }
}

void comset::SetNowTouser()
{
  remoteinterface::getplatformremotehandle()->PltSaveStates(PTY2 + 3);
}
