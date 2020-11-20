#include "rsahala.h"
#include <QApplication>
#include <QTranslator>
#include <QVector>

bool BitHomeForLang(qint32 ilantype);
QTranslator bithomechinaLG;
QTranslator bithomeenglishLG;
QApplication *phomeHandle;
QVector<QTranslator*> bithomeLgvec;
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  phomeHandle = &a;
  bithomeLgvec.append(&bithomechinaLG);
  bithomeLgvec.append(&bithomeenglishLG);
  bithomechinaLG.load("bithomechina.qm");
  bithomeenglishLG.load("bithomeenglish.qm");
  RsaHala w;
//  w.show();
  return a.exec();
}

bool BitHomeForLang(qint32 ilantype)
{
  return phomeHandle->installTranslator(bithomeLgvec.at(ilantype));
}
