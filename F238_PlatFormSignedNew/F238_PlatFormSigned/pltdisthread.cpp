#include "pltdisthread.h"
#include "softbus.h"

pltdisthread::pltdisthread():
  pltdism(PUZERO),
  grunflag(PON)
{

}

void pltdisthread::run()
{
  while(grunflag)
    {
      if(pltdism != PUZERO)
        {
          emit sigpltdis(pltdism);
          pltdism = PUZERO;
        }
      QThread::sleep(PON);
    }
  return;
}
