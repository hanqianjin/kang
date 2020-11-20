#include "upaction.h"
#include <QFile>
#include <QDir>

//Johnson 20200324
#define upgrade_F238_pro
//#define upgrade_F238_smart

upaction::upaction()
{
  mflag = 1;
  sendflag = 0;
  puplist  = NULL;
}

upaction::~upaction()
{
  if(puplist)
    delete puplist;
}

void upaction::run()
{
    emit UpGradeStage(0);

    //Johnson 20200325
    //system("/bin/cp /tmp/USB/bitupgradepacket.rc /tmp");
#ifdef upgrade_F238_pro
    QDir dir("/tmp/USB");
    QStringList filters;
    filters<<QString("bitupgradepacket_pro*");
    dir.setFilter(QDir::Files | QDir::NoSymLinks); //设置类型过滤器，只为文件格式
    dir.setNameFilters(filters);  //设置文件名称过滤器，只为filters格式

    QString command = "/bin/cp /tmp/USB/" + dir[0] +" /tmp";
    system(command.toStdString().c_str());
#endif
#ifdef upgrade_F238_smart
    QDir dir("/tmp/USB");
    QStringList filters;
    filters<<QString("bitupgradepacket_smart*");
    dir.setFilter(QDir::Files | QDir::NoSymLinks); //设置类型过滤器，只为文件格式
    dir.setNameFilters(filters);  //设置文件名称过滤器，只为filters格式

    QString command = "/bin/cp /tmp/USB/" + dir[0] +" /tmp";
    system(command.toStdString().c_str());
#endif
  system("/bin/sync");

  emit UpGradeStage(1);

#ifdef upgrade_F238_pro
  command = "/bin/dd if=/tmp/" + dir[0] +" |openssl des3 -d -k zzsdbz | tar zxfm - -C /tmp";
  if(system(command.toStdString().c_str())< 0)
    //if(system("/bin/dd if=/tmp/bitupgradepacket_pro.rc |openssl des3 -d -k zzsdbz | tar zxf - -C /tmp") < 0)
#endif
#ifdef upgrade_F238_smart
  command = "/bin/dd if=/tmp/" + dir[0] +" |openssl des3 -d -k zzsdbz | tar zxfm - -C /tmp";
  if(system(command.toStdString().c_str())< 0)
    //if(system("/bin/dd if=/tmp/bitupgradepacket_smart.rc |openssl des3 -d -k zzsdbz | tar zxf - -C /tmp") < 0)
#endif
      //if(system("/bin/dd if=/tmp/bitupgradepacket.rc |openssl des3 -d -k zzsdbz | tar zxf - -C /tmp") < 0)
    {
      emit UpGradeStage(-3);
    }

  system("/bin/sync");

  emit UpGradeStage(2);
  qint32 iback = loaddata();
  if(iback < 0)
    {
      emit UpGradeStage(iback);
      return;
    }

  system("/usr/bin/killall SysCtrl");
  system("/usr/bin/killall CalcNotic");
  while(mflag)
    {
      if(sendflag)
        {
          sendflag = 0;
          emit Upgradesig();
        }
      usleep(1000);
    };
}

qint32 upaction::loaddata()
{
  QFile upconf("/tmp/Armoutput/bitupdate.conf");
  if(!upconf.open(QIODevice::ReadOnly))
    {
      return -1;
    }
  upconf.read((char*)&upproperty,sizeof(UPPRO));
  sumitem = upproperty.isum;
  if(sumitem <=0)
    {
      return -2;
    }
  puplist = new UPDATEPRO[sumitem];
  qint32 i = 0;
  for(i = 0;i < upproperty.isum;i++)
    {
      upconf.read((char*)(puplist + i),sizeof(UPDATEPRO));
    }
  upconf.flush();
  upconf.close();
  return 0;
}

void upaction::Ganba(PUPDATEPRO pmsg)
{  
  //folder
  if(0 == pmsg->itype)
    {
      system((QString("/bin/rm -r /app/")+QString(pmsg->name)).toStdString().data());
      system((QString("/bin/cp -r /tmp/Armoutput/") + QString(pmsg->name) + QString(" /app")).toStdString().data());
    }
  //file
  else if(1 == pmsg->itype)
    {
      if(QString(pmsg->name).contains("BOOT"))
        {
          system("/bin/cp /tmp/Armoutput/BOOT.bin /mnt");
          system("flashcp /mnt/BOOT.bin /dev/mtd0");
        }
      else if(QString(pmsg->name).contains("dtb"))
        {
          system("/bin/cp /tmp/Armoutput/*.dtb /mnt");
        }
      else if("bitup" == QString(pmsg->name))
        {
          system("/bin/cp /tmp/Armoutput/bitup /mnt");
        }
      else if("info" == QString(pmsg->name))
        {
          system("/bin/cp /tmp/Armoutput/info /mnt");
        }
      else if("uImage" == QString(pmsg->name))
        {
          system("/bin/cp /tmp/Armoutput/uImage /mnt");
        }
      else if("BitGradeApp" == QString(pmsg->name))
        {
          system("/bin/rm /app/BitGradeApp");
          system("/bin/cp /tmp/Armoutput/BitGradeApp /app");
        }
      else if(QString(pmsg->name).contains("rtl8188eufw"))
      {
          if(!QDir("/lib/firmware/rtlwifi/").exists())
          {
              system("/bin/mkdir /lib/firmware/rtlwifi");
          }
          system("/bin/cp /tmp/Armoutput/rtl8188eufw.bin /lib/firmware/rtlwifi");
      }
      else
        {
            system((QString("/bin/cp /tmp/Armoutput/") + QString(pmsg->name) + QString(" /app")).toStdString().data());
        }
    }
  //extension
  else if(2 == pmsg->itype)
    {
      if("bit" == QString(pmsg->name))
        {
          system("/bin/cp /tmp/Armoutput/*.bit /app");
          system("/bin/cp /tmp/Armoutput/*.bit /mnt");
        }
      else if("so" == QString(pmsg->name))
        {
          system("/bin/cp /tmp/Armoutput/*.so /usr/qt/lib");
        }
      else if("bmp" == QString(pmsg->name))
        {
          system("/bin/cp /tmp/Armoutput/*.bmp /mnt");
        }
      else if("dtb" == QString(pmsg->name))
        {
          system("/bin/cp /tmp/Armoutput/*.dtb /mnt");
        }
      else
        {
          QString cmdstr = QString("/bin/cp ") + QString("/tmp/Armoutput/*.") + QString(pmsg->name) + QString(" /app");
          system(cmdstr.toStdString().data());
        }
    }
}

qint32 upaction::SaveDevelopMsg()
{
  QFile pltdevmsg("develop.msg");
  if(!pltdevmsg.open(QIODevice::ReadOnly))
    {
      return -1;
    }
  pltdevmsg.read((char*)&pltdevelopmsg,sizeof(DEVEMSG));
  strcpy(pltdevelopmsg.update,upproperty.update);
  strcpy(pltdevelopmsg.swver,upproperty.swver);
  strcpy(pltdevelopmsg.hwver,upproperty.hwver);
  pltdevmsg.close();


  QFile pltdevmsg1("develop.msg");
  if(!pltdevmsg1.open(QIODevice::WriteOnly))
    {
      return -1;
    }
  qint32 iwnum = pltdevmsg1.write((char*)&pltdevelopmsg,sizeof(DEVEMSG));
  pltdevmsg1.close();

  return iwnum;
}


