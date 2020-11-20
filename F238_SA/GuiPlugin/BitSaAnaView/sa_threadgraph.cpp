#include "sa_threadgraph.h"
#include <QDebug>
#include "sa_user_variable.h"
#include "define.h"
#include "sa_stdafx.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/time.h>

void SA_P_sem(int handle);
void SA_V_sem(int handle);


ThreadGraph::ThreadGraph(controlInterface &control,user_variable &m_user_variable, QObject *parent) :
    QThread(parent),sa_listenState(1)
{
    globalUserVariable = &m_user_variable;
    mControl = &control;
}

ThreadGraph::~ThreadGraph()
{

}

void ThreadGraph::run()
{
    while(sa_listenState)
    {
        if(globalUserVariable->currentMode != SA_SPAN_MODE)
        {
            usleep(70000);
        }
        else
        {
            usleep(50000);
        }
//        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE||\
//            globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE)
//        {
//            usleep(70000);
//        }else
//        {
//            usleep(50000);
//        }
#if 0
        if(globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE)
        {
            usleep(80000);
        }else if(globalUserVariable->currentMode == SA_SPAN_MODE)
        {
            usleep(50000);
        }else
        {
            usleep(100000);
        }
        if(globalUserVariable->gDetectorMode == SA_AUTO_DETECTOR || globalUserVariable->gDetectorMode == SA_COMMON)
        {
            usleep(20000);
        }
#endif

        {
            SA_P_sem(SA_guiHandle);
            pthread_mutex_lock(&SA_lockobj);
            //SA_sm_config_sweep->uSweepCompleteFlag = 1;
            //****************Johnson 0724********************
#if 1
            if(SA_sm_config_sweep->uSweepCompleteFlag)
            {
                globalUserVariable->gMsComplete = 1;
            }
            else
            {
                globalUserVariable->gMsComplete = 0;
            }
            if((globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE))
            {
                if(SA_sm_config_sweep->uSweepCompleteFlag)
                    memcpy(globalUserVariable->gOriginalMeasureVal,SA_sm_sweep_data->_PwrLevel,NUM_SWEEP_POINT * 8);
            }
            else if(globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE)
            {
//                if(SA_sm_config_sweep->uSweepCompleteFlag)
                    memcpy(globalUserVariable->gOriginalMeasureVal,SA_sm_sweep_data->_PwrLevel,NUM_SWEEP_POINT * 8);
            }else
            {
                    memcpy(globalUserVariable->gOriginalMeasureVal,SA_sm_sweep_data->_PwrLevel,NUM_SWEEP_POINT * 8);
            } 
            //Johnson 190621
            if(globalUserVariable->gMarkerFreqCount)
            {
                globalUserVariable->gFsr = SA_sm_sweep_data->fsr;
                globalUserVariable->gSignalFreq = SA_sm_config_sweep->signalFreq;
            }
            //Johnson 190705
            globalUserVariable->calData = SA_sm_sweep_data->CalData;
#else
            memcpy(globalUserVariable->gDpxData,SA_sm_sweep_data->DpxData,sizeof(SA_sm_sweep_data->DpxData));
#endif
            //************************************************
            pthread_mutex_unlock(&SA_lockobj);
            SA_V_sem(SA_syncHandle);
            emit FinishCount(1);

//            if((globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE))
//            {
//                if(SA_sm_config_sweep->uSweepCompleteFlag)
//                    emit FinishCount(1);
//            }
//            else if(globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE)
//            {
//                if(SA_sm_config_sweep->uSweepCompleteFlag)
//                    emit FinishCount(1);
//            }else
//            {
//                 emit FinishCount(1);
//            }
      }
    }
}

void SA_P_sem(int handle)
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

 void SA_V_sem(int handle)
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
