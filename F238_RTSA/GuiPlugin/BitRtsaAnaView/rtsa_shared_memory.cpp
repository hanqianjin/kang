#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>
#include "rtsa_shared_memory.h"
#include "rtsa_status_code.h"

#include <sys/sem.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <QDebug>
#include "msgNoticeCode.h"


#if 0
#include "sweep_control.h"
#endif

pthread_mutex_t RTSA_lockobj;
typedef struct
{
    qint32 sm_configrsactrl_id;
    qint32 sm_sweepdata_id;
    qint32 sm_sync_id;
    qint32 sm_configupdate_id;
    qint32 sm_rsactrl_id;
    qint32 sm_started_id;
    //Albert 19/01/13 delete system memory control
//    int sm_configsystem_id;
    int sm_rsa_visi_id;
//    int sm_systeminfo_id;

//    void *sm_configsystem_addr;
//    void *sm_systeminfo_addr;
    void *sm_configrsactrl_addr;
    void *sm_sweepdata_addr;
    void *sm_sync_addr;
    void *sm_configupdate_addr;
    void *sm_rsactrl_addr;
    void *sm_started_addr;
    void *sm_rsa_visi_addr;

}_RTSA_SM_INFO;

_RTSA_SM_INFO sm_rtsa_info;
_CONFIG_RSA_CTRL *sm_rtsa_config_rsa_ctrl = NULL;
_RTSA_SWEEP_DATA *sm_rtsa_sweep_data = NULL;
_RTSA_SM_SYNC *sm_rtsa_sync = NULL;
_RTSA_CONFIG_UPDATE *sm_rtsa_config_update = NULL;
//SWEEPCTRL CTRL_SWEEP_MODE = SWEEP_IDLE;//0 continue 1 single 2 idle
RSA_RUN_SYNC *sm_rasctrl = NULL;
_RTSA_START_FLAG *sm_startflag = NULL;
PBIT_RTSA_VISI sm_rtsa_rsa_visi = NULL;
//Albert 19/01/13 delete system memory control
//_RTSA_CONFIG_SYSTEM *sm_rtsa_config_system = NULL;
//_RTSA_SYSTEM_INFO *sm_rtsa_system_info = NULL;

int RTSA_syncHandle = 0;//212
int RTSA_guiHandle = 0;

//Albert 19/04/24 for dpx data mutex
bool RTSA_DpxRefreshFlag = true;

//0921
int rtsa_homeuiHandle = 0;

qint32 RtSa_init_shared_memory(void)
{
  sm_rtsa_info.sm_configrsactrl_id = 0;
  sm_rtsa_info.sm_configrsactrl_addr = NULL;
  sm_rtsa_info.sm_sweepdata_id = 0;
  sm_rtsa_info.sm_sweepdata_addr = NULL;
  sm_rtsa_info.sm_sync_id = 0;
  sm_rtsa_info.sm_sync_addr = NULL;
  sm_rtsa_info.sm_configupdate_id = 0;
  sm_rtsa_info.sm_configupdate_addr = NULL;

  sm_rtsa_info.sm_rsa_visi_id = 0;

  sm_rtsa_info.sm_sweepdata_id = 0;
  sm_rtsa_info.sm_sweepdata_addr = NULL;

  sm_rtsa_info.sm_rsa_visi_addr = NULL;

  //190524 Johnson
  sm_rtsa_info.sm_started_id = shmget((key_t)SM_CTRL_KEY_START, sizeof(_RTSA_START_FLAG), IPC_CREAT | 0777);
  if(-1 == sm_rtsa_info.sm_started_id)
  {
      setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,RTSA_SHM_START_ID_INIT);
      errorOutput();
      return 0;
  }
  else
  {
      sm_rtsa_info.sm_started_addr= shmat(sm_rtsa_info.sm_started_id, (void*)0, 0);
      if (sm_rtsa_info.sm_started_addr == (void*)-1)
          {
          setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,RTSA_SHM_START_ADDR_INIT);
          errorOutput();
              return 0;
          }
      sm_startflag = (_RTSA_START_FLAG*)sm_rtsa_info.sm_started_addr;
  }

  // config sweep
  sm_rtsa_info.sm_rsa_visi_id = shmget((key_t)RSA_VISI_KEY, sizeof(BIT_RTSA_VISI), IPC_CREAT|0777);
  if  (sm_rtsa_info.sm_rsa_visi_id == -1)
    {
      setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,RTSA_SHM_CTRL_ID_INIT);
      errorOutput();
//      printf("sm_bsa_hwnd_id - error shmget()\n\r");
//      qFatal("sm_bsa_hwnd_id - error shmget()\n\r");
      //code_log_directwrite(__FUNCTION__, R_ErrorInit_ShmGetID_Config, NULL);
      return 0;
    }
  else
    {
      sm_rtsa_info.sm_rsa_visi_addr = shmat(sm_rtsa_info.sm_rsa_visi_id, (void*)0, 0);
      if (sm_rtsa_info.sm_rsa_visi_addr == (void*)-1)
        {
          setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,RTSA_SHM_SWEEP_ADDR_INIT);
          errorOutput();
//          printf("config sweep addr - error shmat()\n\r");
//          qFatal("config sweep addr - error shmat()\n\r");
          //code_log_directwrite(__FUNCTION__, R_ErrorInit_ShmGetAddr_Config, NULL);
          return 0;
        }

      // zero fill
      //memset(sm_rtsa_info.sm_configrsactrl_addr, 0, sizeof(_RTSA_CONFIG_RSA_CTRL));
      sm_rtsa_rsa_visi = (PBIT_RTSA_VISI) sm_rtsa_info.sm_rsa_visi_addr;
      sm_rtsa_rsa_visi->visiableflag = 2;
    }


  // config rsa ctrl
  sm_rtsa_info.sm_configrsactrl_id = shmget((key_t)SM_Key_ConfigRsaCtrl, sizeof(_CONFIG_RSA_CTRL), IPC_CREAT|0777);
  if  (sm_rtsa_info.sm_configrsactrl_id == -1)
    {
      setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,RTSA_SHM_CTRL_ID_INIT);
      errorOutput();
//      printf("config sweep id - error shmget()\n\r");
//      qFatal("config sweep id - error shmget()\n\r");
      //code_log_directwrite(__FUNCTION__, R_ErrorInit_ShmGetID_Config, NULL);
      return 0;
    }
  else
    {
      sm_rtsa_info.sm_configrsactrl_addr = shmat(sm_rtsa_info.sm_configrsactrl_id, (void*)0, 0);
      if (sm_rtsa_info.sm_configrsactrl_addr == (void*)-1)
        {
          setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,RTSA_SHM_CTRL_ADDR_INIT);
          errorOutput();
//          printf("config sweep addr - error shmat()\n\r");
//          qFatal("config sweep addr - error shmat()\n\r");
          //code_log_directwrite(__FUNCTION__, R_ErrorInit_ShmGetAddr_Config, NULL);
          return 0;
        }

      // zero fill
      //memset(sm_rtsa_info.sm_configrsactrl_addr, 0, sizeof(_RTSA_CONFIG_RSA_CTRL));

      sm_rtsa_config_rsa_ctrl = (_CONFIG_RSA_CTRL*) sm_rtsa_info.sm_configrsactrl_addr;
    }
  // sweep data
  sm_rtsa_info.sm_sweepdata_id = shmget((key_t)RTSA_SM_Key_SweepData, sizeof(_RTSA_SWEEP_DATA), IPC_CREAT|0660);
  if  (sm_rtsa_info.sm_sweepdata_id == -1)
    {
      setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,RTSA_SHM_SWEEPDATA_ID_INIT);
      errorOutput();
      //code_log_directwrite(__FUNCTION__, R_ErrorInit_ShmGetID_SweepData, NULL);
      return 0;
    }
  else
    {
      sm_rtsa_info.sm_sweepdata_addr = shmat(sm_rtsa_info.sm_sweepdata_id, (void*)0, 0);
      if (sm_rtsa_info.sm_sweepdata_addr == (void*)-1)
        {
          setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,RTSA_SHM_SWEEPDATA_ADDR_INIT);
          errorOutput();
          return 0;
        }

      // zero fill
      //Steve
      //memset(sm_rtsa_info.sm_sweepdata_addr, 0, sizeof(_RTSA_SWEEP_DATA));
      sm_rtsa_sweep_data = (_RTSA_SWEEP_DATA *)sm_rtsa_info.sm_sweepdata_addr;
    }
  // sync
  sm_rtsa_info.sm_sync_id = shmget((key_t)RTSA_SM_Key_Sync, sizeof(_RTSA_SM_SYNC), IPC_CREAT|0660);
  if  (sm_rtsa_info.sm_sync_id == -1)
    {
      setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,RTSA_SHM_SYNC_ID_INIT);
      errorOutput();
      return 0;
    }
  else
    {
      sm_rtsa_info.sm_sync_addr = shmat(sm_rtsa_info.sm_sync_id, (void*)0, 0);
      if (sm_rtsa_info.sm_sync_addr == (void*)-1)
        {
          setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,RTSA_SHM_SYNC_ADDR_INIT);
          errorOutput();
          return 0;
        }

      // zero fill
      memset(sm_rtsa_info.sm_sync_addr, 0, sizeof(_RTSA_SM_SYNC));

      sm_rtsa_sync = (_RTSA_SM_SYNC *)sm_rtsa_info.sm_sync_addr;
    }

  // config update
  sm_rtsa_info.sm_configupdate_id = shmget((key_t)RTSA_SM_Key_ConfigUpdate, sizeof(_RTSA_CONFIG_UPDATE), IPC_CREAT|0777);
  //sm_rtsa_info.sm_configupdate_id = shmget((key_t)SM_Key_ConfigUpdate, 0, 0);
  if  (sm_rtsa_info.sm_configupdate_id == -1)
    {
      setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,RTSA_SHM_UPDATE_ID_INIT);
      errorOutput();
      return 0;
    }
  else
    {
      sm_rtsa_info.sm_configupdate_addr = shmat(sm_rtsa_info.sm_configupdate_id, (void*)0, 0);
      if (sm_rtsa_info.sm_configupdate_addr == (void*)-1)
        {
          setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,RTSA_SHM_UPDATE_ADDR_INIT);
          errorOutput();
          return 0;
        }

      // zero fill
      //Steve
      memset(sm_rtsa_info.sm_configupdate_addr, 0, sizeof(_RTSA_CONFIG_UPDATE));

      sm_rtsa_config_update = (_RTSA_CONFIG_UPDATE *) sm_rtsa_info.sm_configupdate_addr;
    }

  qDebug() << "init sharedmemory Complete -------------------";

  //by steve,0503
 // sm_rtsa_config_rsa_ctrl->sweepMode = 0;
  //added by Steve
  if((RTSA_syncHandle = semget(RTSA_SYNC_KEY,1,IPC_CREAT | 0660))<0)
    {
      //printf("semget errno,%d:%s",errno,strerror(errno));
      qFatal("RTSA_syncHandle RTSA_SYNC_KEY error\n\r");
    }

  if((RTSA_guiHandle = semget(RTSA_SYNC_KEY_GUI,1,IPC_CREAT | 0660))<0)
    {
      //printf("semget errno,%d:%s",errno,strerror(errno));
      qFatal("RTSA_guiHandle RTSA_SYNC_KEY_GUI error\n\r");
    }

  if((rtsa_homeuiHandle = semget(RTSA_HOME_UI_SHOW_KEY,1,IPC_CREAT | 0660))<0)
    {
      //printf("semget errno,%d:%s",errno,strerror(errno));
      qFatal("rtsa_homeuiHandle RTSA_HOME_UI_SHOW_KEY error\n\r");
    }
  // For Thread verification
//  globalUserVariable->gSharedMemoryInit = 1;
//  globalUserVariable->sharedMemoryVariableAssignFunc();

  return RTSA_R_StatusNormal;
}

// for shared memory config flag
qint32 RtSa_Set_config_flag(quint32 modelist, quint32 changelist)
{
  //changed by Steve
  if(1 == modelist)
    {
      sm_rtsa_config_update->sweep_flag = changelist;
    }
  else if(2 == modelist)
    {
      sm_rtsa_config_update->measure_flag = changelist;
    }
  else if(4 == modelist)
    {
        sm_rtsa_config_update->trigger_flag = changelist;
    }
//  else
//    {
//      sm_rtsa_config_update->system_flag = changelist;
//    }
  sm_rtsa_config_update->top_flag = modelist;
//  sm_rtsa_config_rsa_ctrl->stopGuiThread = 0;
  /*
    sm_rtsa_config_update->top_flag = sm_rtsa_config_update->top_flag|modelist;

    if (modelist&IXT_ConfigSweep) sm_rtsa_config_update->sweep_flag = sm_rtsa_config_update->sweep_flag|changelist;
    else if (modelist&IXT_ConfigMeasure) sm_rtsa_config_update->measure_flag = sm_rtsa_config_update->measure_flag|changelist;
    else if (modelist&IXT_RTSA_ConfigSystem) sm_rtsa_config_update->system_flag = sm_rtsa_config_update->system_flag|changelist;
  */
  return 0;
}


qint32 RtSa_Check_InitializeSharedMemory_fromGUI(void)
{
  int sm_test_id = shmget((key_t)SM_Key_ConfigRsaCtrl, sizeof(_CONFIG_RSA_CTRL), IPC_EXCL);
  if (sm_test_id == -1)
    {
//      printf("Already created::test id - error shmget()\n\r");
      qFatal("Already created::test id - error shmget()\n\r");
      return sm_test_id;
    }

  return 0;
}







