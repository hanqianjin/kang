#include "bitplatform.h"
#include <QDebug>
#include "bitapplication.h"
#include <QTranslator>

void CutStartPic();
int main(int argc, char *argv[])
{
  bitapplication a(argc, argv);
  QFile f("/sys/devices/soc0/43000000.ps7-lcdc/pl_bg/bg_flag");
  if(!f.open(QIODevice::WriteOnly)){
      qCritical()<<"Open file fail!";
    }
  BitPlatForm w;
  a.gplt = &w;
  w.show(); 
  w.repaint();
  f.write("1");
  f.close();
  //CutStartPic();
  return a.exec();
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-03-12}
*/
void CutStartPic()
{
  //********write control code to drive program
  QFile f("/sys/devices/soc0/43000000.ps7-lcdc/pl_bg/bg_flag");
  if(!f.open(QIODevice::WriteOnly)){
      qCritical()<<"Open file fail!";
    }
  else{
      f.write("1");
      f.close();
    }
}
