#include "bitplatform.h"
#include <QDebug>
#include "bitapplication.h"
#include <QTranslator>

int main(int argc, char *argv[])
{
  bitapplication a(argc, argv);
  BitPlatForm w;
  a.gplt = &w;
  w.show();
  QThread::msleep(2500);
  QFile f("/sys/devices/soc0/43000000.ps7-lcdc/pl_bg/bg_flag");
  if(!f.open(QIODevice::WriteOnly)){
      qCritical()<<"Open file fail!";
    }
  w.StartCtrlApp(w.pltlastallstates.orimode);
  QThread::msleep(500);
  f.write("1");
  f.close();
  return a.exec();
}
