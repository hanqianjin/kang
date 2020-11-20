#ifndef EXCENOTI_H
#define EXCENOTI_H

#include <QObject>
#include <softbus.h>
typedef struct pltallexcenoti
{
  short npflag;
  short ntype;
  short source;
  short logicmode;
  short index;
}PLTEXCENOTI,*PPLTEXCENOTI;

//typedef struct pltcodeunit
//{
//  short index;
//  char msg[64];
//}PLTCODEUNIT,*PPLTCODEUNIT;

class excenoti
{
private:
  excenoti();
public:
  static void anaexcenoticode(quint32 code);
  PLTEXCENOTI codemsg;
  static excenoti* getexecnotihandle();
  static const char* alldictionary[][220];
  static const char* unknowdic[];
  static short execsumlist[];
//  static const PPLTCODEUNIT alldictionary[];
private:
  static excenoti* innernotic;
};

#endif // EXCENOTI_H
