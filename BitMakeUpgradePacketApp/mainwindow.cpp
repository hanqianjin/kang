/****************************************Copyright (c)****************************************************
**
**                     DaHao Info Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:
** Latest Version: V0.0.1
** Latest modified Date:  2019-12-31
** Modified by:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by: BitYang
** Created date: 2019-12-31
** Descriptions:
**
*********************************************************************************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QCoreApplication>
#include <QDir>

#define test_dir 0

//Johnson 20200324
#define upgrade_F238_pro
//#define upgrade_F238_smart

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);  
  upproperty.isum = 0;
  upitempro = NULL;
//  this->setAttribute(Qt::WA_InputMethodEnabled,true);
#if test_dir
  //Johnson 20200330
  //Get all the dirs and files in the current dir
  QStringList dir_list = QDir("/home/bqs/sbq/SA_RTSA/Update_sf/BitMakeUpgradePacketApp/output").entryList(QDir::Dirs | QDir::NoDotAndDotDot);   //去掉"."和".."
  QStringList file_list = QDir("/home/bqs/sbq/SA_RTSA/Update_sf/BitMakeUpgradePacketApp/output").entryList(QDir::Files | QDir::NoDotAndDotDot);

  QFileInfoList info_list = QDir("/home/bqs/sbq/SA_RTSA/Update_sf/BitMakeUpgradePacketApp/output").entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
  QListIterator<QFileInfo> i(info_list);
  while (i.hasNext())
  {
      QFileInfo info = i.next();
      if (info.isDir())
      {
          dir_list << QDir(info.absoluteFilePath()).dirName();
      }
      if (info.isFile())
      {

          file_list << info.fileName();
      }
  }

  QDir dir("/home/bqs/sbq/SA_RTSA/Update_sf/BitMakeUpgradePacketApp/output");
  QStringList filters;
  filters<<QString("bitupgradepacket_pro*");
  dir.setFilter(QDir::Files | QDir::NoSymLinks); //设置类型过滤器，只为文件格式
  dir.setNameFilters(filters);  //设置文件名称过滤器，只为filters格式

  //统计cfg格式的文件个数
  int dir_count = dir.count();
  if(dir_count <= 0)
      return;
  QStringList string_list;
  for(int i=0; i<dir_count; i++)
  {
      QString file_name = dir[i];  //文件名称
      //ts<<file_name<<"\r\n"<<"\r\n";
      string_list.append(file_name);
  }
#endif
}

MainWindow::~MainWindow()
{
  if(upitempro)
    {
      delete upitempro;
    }
  delete ui;
}

void MainWindow::on_pushButton_clicked()
{
  ui->pushButton->setText("packing ...");
  ui->pushButton->repaint();
  ui->pushButton->setEnabled(false);  
  GetSum();
  GenConfig();
  QString tmps = "cp bitupdate.conf " + QCoreApplication::applicationDirPath() + "/Armoutput";
  system(tmps.toStdString().c_str());
  system("sync");
  //Johnson 20200324
  //system("tar -zcf - Armoutput |openssl des3 -salt -k zzsdbz | dd of=bitupgradepacket.rc");
#ifdef upgrade_F238_pro
  //system("tar -zcf - Armoutput |openssl des3 -salt -k zzsdbz | dd of=bitupgradepacket_pro.rc");
  QString command = "tar -zcf - Armoutput |openssl des3 -salt -k zzsdbz | dd of=bitupgradepacket_pro_" + QString(upproperty.swver) + ".rc";
  system(command.toStdString().c_str());
#endif
#ifdef upgrade_F238_smart
  //system("tar -zcf - Armoutput |openssl des3 -salt -k zzsdbz | dd of=bitupgradepacket_smart.rc");
  QString command = "tar -zcf - Armoutput |openssl des3 -salt -k zzsdbz | dd of=bitupgradepacket_smart_" + QString(upproperty.swver) + ".rc";
  system(command.toStdString().c_str());
#endif
  system("sync");

  ui->pushButton->setEnabled(true);
  ui->pushButton->setText("Make Pakcet");
  QMessageBox::about(this,"Attention","finish packet");
}

void MainWindow::GetSum()
{
  qint32 rowsum = ui->tableWidget->rowCount();
  if(rowsum <=0 )
    return;
  if(upitempro)
    {
      delete upitempro;
      upproperty.isum = 0;
    }
  upitempro = new UPDATEPRO[rowsum];
  qint32 i = 0;
  qint32 ival = 0;
  for(i = 0; i < rowsum;i++)
    {
      ival = ui->tableWidget->item(i,2)->text().toInt();
      if(1 == ival)
        {
          upitempro[upproperty.isum].itype = ui->tableWidget->item(i,1)->text().toInt();
          strcpy(upitempro[upproperty.isum].name,ui->tableWidget->item(i,0)->text().toLatin1().data());
          upproperty.isum++;
        }
    }

  strcpy(upproperty.hwver,ui->lineEdit_3->text().toLatin1().data());
  strcpy(upproperty.swver,ui->lineEdit_2->text().toLatin1().data());
  strcpy(upproperty.update,ui->lineEdit->text().toLatin1().data());
}

void MainWindow::GenConfig()
{
    QFile upconf("bitupdate.conf");
    upconf.open(QIODevice::WriteOnly);
    upconf.write((char*)&upproperty,sizeof(UPPRO));
    qint32 i = 0;
    for(i = 0;i < upproperty.isum;i++)
      {
        upconf.write((char*)(upitempro + i),sizeof(UPDATEPRO));
      }
    upconf.flush();
    upconf.close();
}


void MainWindow::on_pushButton_2_clicked()
{
  QFile upconf1("bitupdate.conf");
  upconf1.open(QIODevice::ReadOnly);
  upconf1.read((char*)&readpro,sizeof(UPPRO));
  qint32 i = 0;
  ui->textEdit->clear();
  ui->textEdit->insertPlainText("VERSION AND DATE:\n");
  ui->textEdit->insertPlainText("Hversion:" + QString(readpro.hwver) + "\n");
  ui->textEdit->insertPlainText("Sversion:" + QString(readpro.swver) + "\n");
  ui->textEdit->insertPlainText("Date:" + QString(readpro.update) + "\n");
  ui->textEdit->insertPlainText("Sum:" + QString::number(readpro.isum) + "\n");
  ui->textEdit->insertPlainText("ITEMS:\n");
  for(i = 0;i < readpro.isum;i++)
    {
      upconf1.read((char*)(&readitempro),sizeof(UPDATEPRO));
      ui->textEdit->insertPlainText("Property:" + QString::number(readitempro.itype) + ";" + "Item:" + QString(readitempro.name) + "\n");
    }  
  upconf1.flush();
  upconf1.close();
}

//void MainWindow::keyPressEvent(QKeyEvent *event)
//{

//}
