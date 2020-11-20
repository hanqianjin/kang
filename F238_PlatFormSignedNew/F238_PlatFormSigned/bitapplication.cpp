#include "bitapplication.h"
#include "dsdtset.h"
#include "QEvent"
#include "softbus.h"
#include "shmengine.h"

bitapplication::bitapplication(int &argc, char **argv):
  QApplication(argc,argv)
{
  gplt = NULL;
}

bitapplication::~bitapplication()
{

}

bool bitapplication::notify(QObject *receiver, QEvent *e)
{    
  //key beep
  if(shmengine::getsingleshm()->pshm_sysconf->KeyBeep)
    {
      if(e->type() == QEvent::MouseButtonDblClick || e->type() == QEvent::MouseButtonPress)
        {
          shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_KeyBeep);
        }
      else if(e->type() == QEvent::KeyPress  &&  !static_cast<QKeyEvent*>(e)->isAutoRepeat())
        {
          shmengine::PassTrigToSys(PLT_IXT_ConfigSystem,PLT_IXS_KeyBeep);
        }
    }
  if(e->type() == QEvent::KeyPress)
    {
      if(static_cast<QKeyEvent*>(e)->key() == Qt::Key_PowerOff)
        {
          if(this->gplt)
            {
              return QApplication::notify(this->gplt,e);
            }
        }
    }
  if(dsdtset::timerswitch)
    {
      if(e->type() == QEvent::MouseButtonDblClick || e->type() == QEvent::MouseButtonPress
         || e->type() == QEvent::MouseButtonRelease || e->type() == QEvent::MouseMove
         || e->type() == QEvent::KeyPress || e->type() == QEvent::KeyRelease)
        {
          if(this->gplt)
            {
              this->gplt->pSetWid->pdedtsetwid->ReStartSysSleep();
            }
        }
    }
  return QApplication::notify(receiver,e);
}
