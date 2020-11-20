#include "rtsa_threadgraph.h"
#include <QDebug>
//#include "define.h"
#include "rtsa_define.h"
#include "rtsa_shared_memory.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/time.h>
#include "rtsa_interface.h"

extern _RTSA_SWEEP_DATA *sm_rtsa_sweep_data;
extern _CONFIG_RSA_CTRL *sm_rtsa_config_rsa_ctrl;
extern _RTSA_START_FLAG *sm_startflag;
extern _RTSA_CONFIG_UPDATE *sm_rtsa_config_update;
extern bool RTSA_DpxRefreshFlag;
void P_RTSA_sem(int handle);
void V_RTSA_sem(int handle);
RtSa_ThreadGraph::RtSa_ThreadGraph(QObject *parent)
    :QThread(parent)
    , rtsa_thread_state(1)
{

}
RtSa_ThreadGraph::~RtSa_ThreadGraph()
{
}
extern int RTSA_syncHandle;//212
extern int RTSA_guiHandle;
extern pthread_mutex_t RTSA_lockobj;

int gfirst = 1;
void RtSa_ThreadGraph::run()
{
  while(rtsa_thread_state)
    {
//      if(0 == sm_rtsa_config_rsa_ctrl->ListenState)
//        {
          usleep(globalUserVariable->gSleepTime);

          P_RTSA_sem(RTSA_guiHandle);
          pthread_mutex_lock(&RTSA_lockobj);
          //****************Johnson 0724********************
#if 1
//          memcpy(MainUserVariable.gOriginalMeasureVal,sm_rtsa_sweep_data->_PwrLevel,RTSA_NUM_SWEEP_POINT * 8);
            InterfaceObj->updateTraceData(sm_rtsa_sweep_data->_PwrLevel,RTSA_NUM_SWEEP_POINT);
            if(globalUserVariable->gDpxOpenFlag)
                InterfaceObj->updateDpxData(sm_rtsa_sweep_data->DpxData,DPX_WIDTH_SIZE * DPX_HEIGHT_SIZE);
//          memcpy(TraceObj.gOriginalTrace,sm_rtsa_sweep_data->_PwrLevel,RTSA_NUM_SWEEP_POINT * 8);
//          Tony 1207 data size need to modify when FPGA give size
//        memcpy(globalUserVariable->gOriginalDPXdata,sm_rtsa_sweep_data->DpxData,BIT_DPXSIZE * 4);
#else
          memcpy(globalUserVariable->gDpxData,sm_rtsa_sweep_data->DpxData,sizeof(sm_rtsa_sweep_data->DpxData));
#endif
          //************************************************

          pthread_mutex_unlock(&RTSA_lockobj);
          RTSA_DpxRefreshFlag = true;
          V_RTSA_sem(RTSA_syncHandle);
          if(0 == sm_rtsa_config_update->stopFlag)
          {
              emit FinishCount(1);
          }
          if(gfirst)
            {
              usleep(200000);
              gfirst = 0;
            }
        }
//      else
//        {
//          msleep(100);
//        }
//    }
}


void P_RTSA_sem(int handle)
{
  struct sembuf s;
  s.sem_num=0;
  s.sem_op=-1;
  s.sem_flg=0;
  if(semop(handle,&s,1)<0)
    {
      //printf("op error,%d:%s",errno,strerror(errno));
    }
}

void V_RTSA_sem(int handle)
{
  struct sembuf s;
  s.sem_num=0;
  s.sem_op=1;
  s.sem_flg=0;
  if(semop(handle,&s,1)<0)
    {
      //printf("op error,%d:%s",errno,strerror(errno));
    }
}

void RtSa_ThreadGraph::setGobalVariable(RtSa_User_Variable *userVariable)
{
    globalUserVariable = userVariable;
    return;
}
void RtSa_ThreadGraph::setInterface(RtSa_Interface *interface)
{
    InterfaceObj = interface;
    return;
}
