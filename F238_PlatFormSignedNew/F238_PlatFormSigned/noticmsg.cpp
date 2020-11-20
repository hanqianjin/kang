#include "noticmsg.h"
#include "ui_noticmsg.h"
#include "remoteinterface.h"
#include "softbus.h"

noticmsg::noticmsg(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::noticmsg)
{
  rowindex = 0;
  excenum = 0;
  noticnum = 0;
  ui->setupUi(this);
  this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
  ui->tableWidget->setColumnWidth(0,35);
  ui->tableWidget->setColumnWidth(1,60);
  ui->tableWidget->setColumnWidth(2,401);
  ui->tableWidget->verticalHeader()->setDefaultSectionSize(35);
  ui->tableWidget->clearContents();
  ui->tableWidget->setRowCount(0);
  this->move(353,205);
}

noticmsg::~noticmsg()
{
  delete ui;
}

void noticmsg::on_pushButton_clicked()
{
  this->hide();
  this->setWindowModality(Qt::NonModal);
  this->parentWidget()->setFocus();
}

void noticmsg::SetPltExceDisM(qint32 imod)
{
  if(imod < PLT_INDOOR || imod >= PLT_DNONE)
    return;
  imod = imod == PTY1 ? PTY0 : imod;
  dismode = imod;
  this->setProperty("pltdismode",pltdismod[imod]);
  setStyle(QApplication::style());
}

void noticmsg::keyPressEvent(QKeyEvent *event)
{
  if(Qt::Key_PowerOff == event->key())
    {
      QApplication::sendEvent(remoteinterface::getplatformremotehandle(),event);
    }
  else if(Qt::Key_Escape == event->key())
    {
      on_pushButton_clicked();
    }
  else if(Qt::Key_Shift == event->key())
    {
      QApplication::sendEvent(remoteinterface::getplatformremotehandle(),event);
      on_pushButton_clicked();
    }
}

/**
 * @brief
 * @param[in] itype:notice or exce png
 * @param[in]
 * @return
 * @note
 * @since {2019-10-17}
*/
void noticmsg::InsertMsg(short itype,QString typestr, const char *str)
{
  itype &= 1;
  if(itype)
    {
      excenum++;
    }
  else
    {
      noticnum++;
    }
  if(excenum > PLTMAXCIRLEN)
    {
      ui->label_2->setText(tr("Too much exception,please commu with the factory"));
      return;
    }
  if(noticnum > (PLTMAXCIRLEN << 1))
    {
      return;
    }
  if(rowindex >= 5)
    {
      ui->label->setGeometry(508,30,15,175);
    }
  qint32 tmpdismode = 0;
  if(PTY2 == dismode || PTY1 == dismode)
    {
      tmpdismode = PTY1;
    }
  else
    {
      tmpdismode = PTY0;
    }

  ui->tableWidget->insertRow(rowindex);
  QTableWidgetItem *icoitem = new QTableWidgetItem();
  icoitem->setFlags(icoitem->flags() /*& ~Qt::ItemIsEnabled*/ & ~Qt::ItemIsSelectable);
  QIcon icon1;
  icon1.addFile(remoteinterface::getplatformremotehandle()->noticexcepicvec.at(tmpdismode)[itype], QSize(), QIcon::Normal, QIcon::Off);
  icoitem->setIcon(icon1);
  ui->tableWidget->setItem(rowindex, 0, icoitem);
  QTableWidgetItem *tempitem = new QTableWidgetItem();
  tempitem->setFlags(icoitem->flags() /*& ~Qt::ItemIsEnabled*/ & ~Qt::ItemIsSelectable);
  tempitem->setText(typestr);
  ui->tableWidget->setItem(rowindex, 1, tempitem);
  QTableWidgetItem *tempitem1 = new QTableWidgetItem();
  tempitem1->setFlags(icoitem->flags() /*& ~Qt::ItemIsEnabled*/ & ~Qt::ItemIsSelectable);
  tempitem1->setText(tr(str));
  ui->tableWidget->setItem(rowindex, 2, tempitem1);  
  rowindex++;
}

void noticmsg::ChangeNodeDismode(qint32 imode, pltcirlist &pcirnode)
{
  if(PTY2 == imode)
    {
      imode = PTY1;
    }
  else
    {
      imode = PTY0;
    }
  qint32 i = 0;
  qint32 isum = pcirnode.Count();
  QTableWidgetItem *icoitem = NULL;
  dismode = imode;
  for(i = 0;i < isum;i++)
    {
      icoitem = ui->tableWidget->item(i,0);
      icoitem->setFlags(icoitem->flags() /*& ~Qt::ItemIsEnabled*/ & ~Qt::ItemIsSelectable);
      QIcon icon1;
      icon1.addFile(remoteinterface::getplatformremotehandle()->noticexcepicvec.at(imode)[pcirnode.GetNodeByQueue(i)->npflag], QSize(), QIcon::Normal, QIcon::Off);
      icoitem->setIcon(icon1);
      ui->tableWidget->setItem(rowindex, 0, icoitem);
    }
}

void noticmsg::ClearAllExceNotic()
{
  if(rowindex)
    {
      ui->label->setGeometry(518,30,21,175);
      ui->label_2->clear();
      rowindex = 0;
      noticnum = 0;
      excenum = 0;
      remoteinterface::getplatformremotehandle()->GetCirHandle()->Clear();
      remoteinterface::getplatformremotehandle()->ClearExceUi();
      ui->tableWidget->clearContents();
      ui->tableWidget->setRowCount(0);
    }
}

void noticmsg::on_pushButton_2_clicked()
{
  //clear msg list
  ClearAllExceNotic();
}
