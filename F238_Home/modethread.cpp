/****************************************Copyright (c)****************************************************
**
**                     DaHao Info Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name: modethread.cpp
** Latest Version: V0.0.1
** Latest modified Date:  2018-12-17
** Modified by:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by: BitYang
** Created date: 2018-12-17
** Descriptions: this class for all modes to show homeui ctrl
**
*********************************************************************************************************/
#include "modethread.h"

/**
* @class modethread
* @brief other mode to show home ui
*/
modethread::modethread(QObject *parent)
  :QThread(parent),
    overflg(0),
    runflg(1)
{

}

void modethread::run()
{
  while(runflg)
    {
      //get home key msg from one of mode
      RunStateShm::GetSemp(RunStateShm::getsingleshm()->homeuihandle);
      if(overflg)
        return;
      //send sig to home gui to show
      emit ShowSig();
    };
  return;
}

/**
 * @brief when home app close to exit run thread
 * @note
 * @author steve
 * @since {2018-12-17}
*/
void modethread::ExitThread()
{
  overflg = 1;
  return;
}
