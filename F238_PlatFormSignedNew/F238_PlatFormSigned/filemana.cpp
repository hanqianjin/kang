#include "filemana.h"
#include "ui_filemana.h"
#include "softbus.h"
#include "remoteinterface.h"

filemana::filemana(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::filemana)
{
  ui->setupUi(this);
  pnoticwid = NULL;
  pdegd = NULL;

  //Johnson 20200318
#if PLT_CAL_HIDE
  ui->label_5->setVisible(false);
  ui->line_5->setVisible(false);
  ui->pushButton_21->setVisible(false);
#endif
}

filemana::~filemana()
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
 * @since {2019-06-10}
*/
void filemana::GetNowAnaMode(quint32 *imod)
{
  filemanavar.panamode = imod;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-09-12}
*/
void filemana::GetDisMode(qint32 *imod)
{
  filemanavar.pdismode = imod;
}

void filemana::on_pushButton_21_clicked()
{
  qint32 iback = -1;
  if(NULL == pnoticwid)
    {
      pnoticwid = new pltnotice(*filemanavar.panamode,PTY2,this);
      pnoticwid->move(PLTX,PLTY);
      pnoticwid->SetNoticDisMode(*filemanavar.pdismode);
      pnoticwid->exec();
      iback = pnoticwid->GetSelectState();
      delete pnoticwid;
      pnoticwid = NULL;
    }
  if(iback)
    {
      if(NULL == pdegd)
        {
          pdegd = new debugdia(this);
          pdegd->RefleshStates(remoteinterface::getplatformremotehandle()->GetDMsgHandle());
          pdegd->exec();
          qint32 ic = pdegd->GetCalcCloseFlag();
          delete pdegd;
          pdegd = NULL;
          if(ic)
            {
              remoteinterface::getplatformremotehandle()->StartDevCalc();
            }
        }
    }
}

void filemana::on_pushButton_19_clicked()
{
  if(NULL == pnoticwid)
    {
      pnoticwid = new pltnotice(*filemanavar.panamode,PTY1,this);
      pnoticwid->move(PLTX,PLTY);      
      pnoticwid->exec();      
      delete pnoticwid;
      this->repaint();
      pnoticwid = NULL;
    }
}
