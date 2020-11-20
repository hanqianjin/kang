#if 0

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>
#include "sa_shared_memory.h"
#include "sa_status_code.h"
#include "sa_user_variable.h"

#include <sys/sem.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <QDebug>


#if 0
#include "sweep_control.h"
#endif

bool bParaLoad = false;//1 mode change and param load,0 common mode

pthread_mutex_t SA_lockobj;
typedef struct
{
  int sm_configsweep_id;
  int sm_configmeasure_id;
  int sm_configsystem_id;
  int sm_sweepdata_id;
#if USABLE
  int sm_measuredata_id;
#endif
  int sm_systeminfo_id;
  int sm_sync_id;
  int sm_configupdate_id;
  int sm_channel_param_id;
  int sm_fft_fir_commonnum_id;
  int sm_sweep_num_id;
  int sm_bsa_visi_id;
  int sm_started_id;
  int sm_tempercalc_id;

  void *sm_configsweep_addr;
  void *sm_configmeasure_addr;
  void *sm_configsystem_addr;
  void *sm_sweepdata_addr;
#if USABLE
  void *sm_measuredata_addr;
#endif
  void *sm_systeminfo_addr;
  void *sm_sync_addr;
  void *sm_configupdate_addr;
  void *sm_channel_param_addr;
  void *sm_fft_fir_commonnum_addr;
  void *sm_sweep_num_addr;
  void *sm_bsa_visi_addr;
  void *sm_started_addr;
  void *sm_tempercalc_addr;
}SA_SM_INFO;

SA_SM_INFO SA_sm_info;
SA_CONFIG_SWEEP *SA_sm_config_sweep = NULL;
SA_CONFIG_MEASURE *SA_sm_config_measure = NULL;
//SA_CONFIG_SYSTEM *sm_config_system = NULL;
SA_SWEEP_DATA *SA_sm_sweep_data = NULL;
#if USABLE
SA_MEASURE_DATA *SA_sm_measure_data = NULL;
#endif
//SA_SYSTEM_INFO *sm_system_info = NULL;
SA_SM_SYNC *SA_sm_sync = NULL;
SA_CONFIG_UPDATE *SA_sm_config_update = NULL;

SA_PCHANNEL_PARAM sm_channel_param = NULL;
SA_PFFT_FIR_COMMON_NUM sm_fft_fir_common_num = NULL;
SA_PSWEEP_NUM SA_sm_sweep_num = NULL;

SA_PBIT_BSA_VISI SA_sm_bsa_visi = NULL;
SA_PSTART_FLAG sm_startflag = NULL;//Johnson 190524

SA_PTEMP_CALC sm_temper_calc = NULL;

int SA_syncHandle = 0;//212
int SA_guiHandle = 0;

//0921
int SA_homeuiHandle = 0;


qint32 SA_init_shared_memory(user_variable *globalUserVariable)
{
  pthread_mutex_init(&SA_lockobj,NULL);
  SA_sm_info.sm_configsweep_id = 0;
  SA_sm_info.sm_configsweep_addr = NULL;
  SA_sm_info.sm_configmeasure_id = 0;
  SA_sm_info.sm_configmeasure_addr = NULL;
  SA_sm_info.sm_configsystem_id = 0;
  SA_sm_info.sm_configsystem_addr = NULL;
  SA_sm_info.sm_sweepdata_id = 0;
  SA_sm_info.sm_sweepdata_addr = NULL;
#if USABLE
  SA_sm_info.sm_measuredata_id = 0;
  SA_sm_info.sm_measuredata_addr = NULL;
#endif
  SA_sm_info.sm_systeminfo_id = 0;
  SA_sm_info.sm_systeminfo_addr = NULL;
  SA_sm_info.sm_sync_id = 0;
  SA_sm_info.sm_sync_addr = NULL;
  SA_sm_info.sm_configupdate_id = 0;
  SA_sm_info.sm_configupdate_addr = NULL;

  SA_sm_info.sm_bsa_visi_id = 0;

  SA_sm_info.sm_channel_param_id = 0;
  SA_sm_info.sm_channel_param_addr = NULL;
  SA_sm_info.sm_fft_fir_commonnum_id = 0;
  SA_sm_info.sm_fft_fir_commonnum_addr = NULL;
  SA_sm_info.sm_sweepdata_id = 0;
  SA_sm_info.sm_sweepdata_addr = NULL;

  SA_sm_info.sm_bsa_visi_addr = NULL;

  SA_sm_info.sm_started_id = 0;
  SA_sm_info.sm_started_addr = NULL;

  //190524 Johnson
  SA_sm_info.sm_started_id = shmget((key_t)SM_CTRL7_KEY_START, sizeof(SA_START_FLAG), IPC_CREAT | 0777);
  if(-1 == SA_sm_info.sm_started_id)
  {
      return 0;
  }
  else
  {
      SA_sm_info.sm_started_addr= shmat( SA_sm_info.sm_started_id, (void*)0, 0);
      if (SA_sm_info.sm_started_addr == (void*)-1)
          {
              return 0;
          }
      sm_startflag = (SA_PSTART_FLAG)SA_sm_info.sm_started_addr;
  }

  // config sweep
  SA_sm_info.sm_bsa_visi_id = shmget((key_t)SA_BSA_VISI_KEY, sizeof(SA_BIT_BSA_VISI), IPC_CREAT|0777);
  if  (SA_sm_info.sm_bsa_visi_id == -1)
    {
      printf("sm_bsa_hwnd_id - error shmget()\n\r");
      //code_log_directwrite(__FUNCTION__, R_ErrorInit_ShmGetID_Config, NULL);
      return R_ErrorInit_ShmGetID_Config;
    }
  else
    {
      SA_sm_info.sm_bsa_visi_addr = shmat(SA_sm_info.sm_bsa_visi_id, (void*)0, 0);
      if (SA_sm_info.sm_bsa_visi_addr == (void*)-1)
        {
          printf("config sweep addr - error shmat()\n\r");
          //code_log_directwrite(__FUNCTION__, R_ErrorInit_ShmGetAddr_Config, NULL);
          return R_ErrorInit_ShmGetAddr_Config;
        }

      // zero fill
      //memset(SA_sm_info.sm_configsweep_addr, 0, sizeof(SA_CONFIG_SWEEP));

      SA_sm_bsa_visi = (SA_PBIT_BSA_VISI) SA_sm_info.sm_bsa_visi_addr;
      SA_sm_bsa_visi->visiableflag = 2;
    }


  // config sweep
  SA_sm_info.sm_configsweep_id = shmget((key_t)SM_SA_Key_ConfigSweep, sizeof(SA_CONFIG_SWEEP), IPC_CREAT|0777);
  if  (SA_sm_info.sm_configsweep_id == -1)
    {
      printf("config sweep id - error shmget()\n\r");
      //code_log_directwrite(__FUNCTION__, R_ErrorInit_ShmGetID_Config, NULL);
      return R_ErrorInit_ShmGetID_Config;
    }
  else
    {
      SA_sm_info.sm_configsweep_addr = shmat(SA_sm_info.sm_configsweep_id, (void*)0, 0);
      if (SA_sm_info.sm_configsweep_addr == (void*)-1)
        {
          printf("config sweep addr - error shmat()\n\r");
          //code_log_directwrite(__FUNCTION__, R_ErrorInit_ShmGetAddr_Config, NULL);
          return R_ErrorInit_ShmGetAddr_Config;
        }

      // zero fill
      //memset(SA_sm_info.sm_configsweep_addr, 0, sizeof(SA_CONFIG_SWEEP));

      SA_sm_config_sweep = (SA_CONFIG_SWEEP*) SA_sm_info.sm_configsweep_addr;
    }


  // config measure
  SA_sm_info.sm_configmeasure_id = shmget((key_t)SM_SA_Key_ConfigMeasure, sizeof(SA_CONFIG_MEASURE), IPC_CREAT|0777);
  if  (SA_sm_info.sm_configmeasure_id == -1)
    {
      printf("config measure id - error shmget()\n\r");
      //code_log_directwrite(__FUNCTION__, R_ErrorInit_ShmGetID_Status, NULL);
      return R_ErrorInit_ShmGetID_Status;
    }
  else
    {
      SA_sm_info.sm_configmeasure_addr = shmat(SA_sm_info.sm_configmeasure_id, (void*)0, 0);
      if (SA_sm_info.sm_configmeasure_addr == (void*)-1)
        {
          printf("config measure addr - error shmat()\n\r");
          //code_log_directwrite(__FUNCTION__, R_ErrorInit_ShmGetAddr_Status, NULL);
          return R_ErrorInit_ShmGetAddr_Status;
        }

      // zero fill
      //memset(SA_sm_info.sm_configmeasure_addr, 0, sizeof(SA_CONFIG_MEASURE));


      SA_sm_config_measure = (SA_CONFIG_MEASURE *)SA_sm_info.sm_configmeasure_addr;
    }

  // config system
  /*SA_sm_info.sm_configsystem_id = shmget((key_t)SM_SA_Key_ConfigSystem, sizeof(SA_CONFIG_SYSTEM), IPC_CREAT|0777);
  if  (SA_sm_info.sm_configsystem_id == -1)
    {
      printf("config system id - error shmget()\n\r");
      //code_log(__FUNCTION__, R_ErrorInit_ShmGetID_Sync, NULL);
      return R_ErrorInit_ShmGetID_Sync;
    }
  else
    {
      SA_sm_info.sm_configsystem_addr = shmat(SA_sm_info.sm_configsystem_id, (void*)0, 0);
      if (SA_sm_info.sm_configsystem_addr == (void*)-1)
        {
          printf("config system addr - error shmat()\n\r");
          //code_log_directwrite(__FUNCTION__, R_ErrorInit_ShmGetAddr_Sync, NULL);
          return R_ErrorInit_ShmGetAddr_Sync;
        }

      // zero fill
      //memset(SA_sm_info.sm_configsystem_addr, 0, sizeof(SA_CONFIG_SYSTEM));

      // output
      sm_config_system = (SA_CONFIG_SYSTEM *) SA_sm_info.sm_configsystem_addr;
      qDebug() << "init sharedmemory -------------------c ";
    }*/

  // sweep data
  SA_sm_info.sm_sweepdata_id = shmget((key_t)SM_SA_Key_SweepData, sizeof(SA_SWEEP_DATA), IPC_CREAT|0660);
  if  (SA_sm_info.sm_sweepdata_id == -1)
    {
      perror("sweep shm is failed");
      printf("sweepdata id - error shmget()\n\r");
      //code_log_directwrite(__FUNCTION__, R_ErrorInit_ShmGetID_SweepData, NULL);
      return R_ErrorInit_ShmGetID_SweepData;
    }
  else
    {
      SA_sm_info.sm_sweepdata_addr = shmat(SA_sm_info.sm_sweepdata_id, (void*)0, 0);
      if (SA_sm_info.sm_sweepdata_addr == (void*)-1)
        {
          printf("sweepdata addr - error shmat()\n\r");
          //code_log_directwrite(__FUNCTION__, R_ErrorInit_ShmGetAddr_SweepData, NULL);
          return R_ErrorInit_ShmGetAddr_SweepData;
        }

      // zero fill
      //Steve
      //memset(SA_sm_info.sm_sweepdata_addr, 0, sizeof(SA_SWEEP_DATA));
      SA_sm_sweep_data = (SA_SWEEP_DATA *)SA_sm_info.sm_sweepdata_addr;
    }

#if USABLE
  // measure data
  SA_sm_info.sm_measuredata_id = shmget((key_t)SM_SA_Key_MeasureData, sizeof(SA_MEASURE_DATA), IPC_CREAT|0660);
  if  (SA_sm_info.sm_measuredata_id == -1)
    {
      printf("measure data id - error shmget()\n\r");
      //code_log_directwrite(__FUNCTION__, R_ErrorInit_ShmGetID_SweepData, NULL);
      return R_ErrorInit_ShmGetID_SweepData;
    }
  else
    {
      SA_sm_info.sm_measuredata_addr = shmat(SA_sm_info.sm_measuredata_id, (void*)0, 0);
      if (SA_sm_info.sm_measuredata_addr == (void*)-1)
        {
          printf("measure data addr - error shmat()\n\r");
          //code_log_directwrite(__FUNCTION__, R_ErrorInit_ShmGetAddr_SweepData, NULL);
          return R_ErrorInit_ShmGetAddr_SweepData;
        }

      // zero fill
      //Steve
      //memset(SA_sm_info.sm_measuredata_addr, 0, sizeof(SA_MEASURE_DATA));
      SA_sm_measure_data = (SA_MEASURE_DATA *) SA_sm_info.sm_measuredata_addr;
    }
#endif
  // system info
  /*SA_sm_info.sm_systeminfo_id = shmget((key_t)SM_SA_Key_SystemInfo, sizeof(SA_SYSTEM_INFO), IPC_CREAT|0660);
  if  (SA_sm_info.sm_systeminfo_id == -1)
    {
      printf("system info id - error shmget()\n\r");
      //code_log_directwrite(__FUNCTION__, R_ErrorInit_ShmGetID_SweepData, NULL);
      return R_ErrorInit_ShmGetID_SweepData;
    }
  else
    {
      SA_sm_info.sm_systeminfo_addr = shmat(SA_sm_info.sm_systeminfo_id, (void*)0, 0);
      if (SA_sm_info.sm_systeminfo_addr == (void*)-1)
        {
          printf("system info addr - error shmat()\n\r");
          //code_log_directwrite(__FUNCTION__, R_ErrorInit_ShmGetAddr_SweepData, NULL);
          return R_ErrorInit_ShmGetAddr_SweepData;
        }
      // zero fill
      memset(SA_sm_info.sm_systeminfo_addr, 0, sizeof(SA_SYSTEM_INFO));

      sm_system_info = (SA_SYSTEM_INFO *) SA_sm_info.sm_systeminfo_addr;
    }*/

  // sync
  SA_sm_info.sm_sync_id = shmget((key_t)SM_SA_Key_Sync, sizeof(SA_SM_SYNC), IPC_CREAT|0660);
  if  (SA_sm_info.sm_sync_id == -1)
    {
      printf("sync id - error shmget()\n\r");
      //code_log_directwrite(__FUNCTION__, R_ErrorInit_ShmGetID_SweepData, NULL);
      return R_ErrorInit_ShmGetID_SweepData;
    }
  else
    {
      SA_sm_info.sm_sync_addr = shmat(SA_sm_info.sm_sync_id, (void*)0, 0);
      if (SA_sm_info.sm_sync_addr == (void*)-1)
        {
          printf("sync addr - error shmat()\n\r");
          //code_log_directwrite(__FUNCTION__, R_ErrorInit_ShmGetAddr_SweepData, NULL);
          return R_ErrorInit_ShmGetAddr_SweepData;
        }

      // zero fill
      memset(SA_sm_info.sm_sync_addr, 0, sizeof(SA_SM_SYNC));

      SA_sm_sync = (SA_SM_SYNC *)SA_sm_info.sm_sync_addr;
    }

  // config update
  SA_sm_info.sm_configupdate_id = shmget((key_t)SM_SA_Key_ConfigUpdate, sizeof(SA_CONFIG_UPDATE), IPC_CREAT|0777);
  //SA_sm_info.sm_configupdate_id = shmget((key_t)SM_SA_Key_ConfigUpdate, 0, 0);
  if  (SA_sm_info.sm_configupdate_id == -1)
    {
      printf("config update id - error shmget()\n\r");
      //code_log_directwrite(__FUNCTION__, R_ErrorInit_ShmGetID_SweepData, NULL);
      return R_ErrorInit_ShmGetID_SweepData;
    }
  else
    {
      SA_sm_info.sm_configupdate_addr = shmat(SA_sm_info.sm_configupdate_id, (void*)0, 0);
      if (SA_sm_info.sm_configupdate_addr == (void*)-1)
        {
          printf("config update addr - error shmat()\n\r");
          //code_log_directwrite(__FUNCTION__, R_ErrorInit_ShmGetAddr_SweepData, NULL);
          return R_ErrorInit_ShmGetAddr_SweepData;
        }

      // zero fill
      //Steve
      memset(SA_sm_info.sm_configupdate_addr, 0, sizeof(SA_CONFIG_UPDATE));

      SA_sm_config_update = (SA_CONFIG_UPDATE *) SA_sm_info.sm_configupdate_addr;
    }

  //channel param
  SA_sm_info.sm_channel_param_id = shmget((key_t)SM_SA_Key_Channelparam, sizeof(SA_CHANNEL_PARAM), IPC_CREAT|0666);
  if(-1 == SA_sm_info.sm_channel_param_id)
    {
      perror("config_channel_param_shm_failed");
      return -1;
    }
  else
    {
      SA_sm_info.sm_channel_param_addr = shmat(SA_sm_info.sm_channel_param_id, (void*)0, 0);
      if (SA_sm_info.sm_channel_param_addr == (void*)-1)
        {
          perror("attach_channel_param_shm_failed");
          return -1;
        }
      sm_channel_param = (SA_CHANNEL_PARAM*)SA_sm_info.sm_channel_param_addr;
    }

  //fft_fir commom num
  SA_sm_info.sm_fft_fir_commonnum_id = shmget((key_t)SM_SA_Key_FftFirCommonnum, sizeof(SA_FFT_FIR_COMMON_NUM), IPC_CREAT|0666);
  if(-1 == SA_sm_info.sm_fft_fir_commonnum_id)
    {
      perror("config_fft_fir_commonnum_shm_failed");
      return -1;
    }
  else
    {
      SA_sm_info.sm_fft_fir_commonnum_addr = shmat(SA_sm_info.sm_fft_fir_commonnum_id, (void*)0, 0);
      if (SA_sm_info.sm_fft_fir_commonnum_addr == (void*)-1)
        {
          perror("attach_fft_fir_commonnum_shm_failed");
          return -1;
        }
      sm_fft_fir_common_num  = (SA_FFT_FIR_COMMON_NUM*)SA_sm_info.sm_fft_fir_commonnum_addr;
    }

  //sweep num
  SA_sm_info.sm_sweep_num_id = shmget((key_t)SM_SA_Key_SweepNum  , sizeof(SA_SWEEP_NUM), IPC_CREAT|0666);
  if(-1 == SA_sm_info.sm_sweep_num_id)
    {
      perror("config_sweep_num_shm_failed");
      return -1;
    }
  else
    {
      SA_sm_info.sm_sweep_num_addr = shmat(SA_sm_info.sm_sweep_num_id, (void*)0, 0);
      if (SA_sm_info.sm_sweep_num_addr == (void*)-1)
        {
          perror("attach_sweep_num_shm_failed");
          return -1;
        }
      SA_sm_sweep_num  = (SA_SWEEP_NUM*)SA_sm_info.sm_sweep_num_addr;
    }  

  // config temper calc
      SA_sm_info.sm_tempercalc_id = shmget((key_t)SM_Key_TemperCalc, sizeof(SA_TEMP_CALC), IPC_CREAT|0666);
      if  (-1 == SA_sm_info.sm_tempercalc_id)
      {
          perror("temp_calc_shm_failed");
              return -1;
      }
      else
      {
          SA_sm_info.sm_tempercalc_addr = shmat(SA_sm_info.sm_tempercalc_id, (void*)0, 0);
          if (SA_sm_info.sm_tempercalc_addr == (void*)-1)
          {
              perror("attach_temp_calc_shm_failed");
                  return -1;
          }
          sm_temper_calc = (SA_TEMP_CALC *) SA_sm_info.sm_tempercalc_addr;
      }


  /*
    // log message
    shm_logmsg_id = shmget((key_t)SM_Key_LogMsg, sizeof(_SM_LogMsg), IPC_CREAT|0777);
    if  (shm_logmsg_id == -1)
    {
        printf("logmsg id - error shmget()\n\r");
        code_log_directwrite(__FUNCTION__, R_ErrorInit_ShmGetID_Log, NULL);
        return R_ErrorInit_ShmGetID_Log;
    }
    else
    {
        shm_logmsg_addr = shmat(shm_logmsg_id, (void*)0, 0);
        if (shm_logmsg_addr == (void*)-1)
        {
            printf("logmsg addr - error shmat()\n\r");
            code_log_directwrite(__FUNCTION__, R_ErrorInit_ShmGetAddr_Log, NULL);
            return R_ErrorInit_ShmGetAddr_Log;
        }

        // zero fill
        memset(shm_logmsg_addr, 0, sizeof(_SM_LogMsg));

        // output
        SA_sm_info.sm_logmsg_id = shm_logmsg_id;
        SA_sm_info.sm_logmsg_addr = shm_logmsg_addr;

        _SM_LogMsg *temp_logmsg = (_SM_LogMsg*)SA_sm_info.sm_logmsg_addr;
        temp_logmsg->push_pt = 0;
        temp_logmsg->read_pt = 0;
    }
*/

  qDebug() << "init sharedmemory Complete -------------------";

  //repair bug by Steve,0309
  SA_sm_sweep_num->validRatio = 0.75;
  //by steve,0418
  SA_sm_sweep_num->loStepHz = 1000000;

  //by steve,0503
 // SA_sm_config_sweep->sweepMode = 0;
  //added by Steve
  if((SA_syncHandle = semget(SYNC_SA_KEY,1,IPC_CREAT | 0660))<0)
  {
      //printf("semget errno,%d:%s",errno,strerror(errno));
  }
  if((SA_guiHandle = semget(SYNC_SA_KEY_GUI,1,IPC_CREAT | 0660))<0)
  {
      //printf("semget errno,%d:%s",errno,strerror(errno));
  }
  if((SA_homeuiHandle = semget(SA_HOME_UI_SHOW_KEY,1,IPC_CREAT | 0660))<0)
  {
      //printf("semget errno,%d:%s",errno,strerror(errno));
  }
  // For Thread verification
  //globalUserVariable->gSharedMemoryInit = 1;
  globalUserVariable->sharedMemoryVariableAssignFunc();

  return R_StatusNormal;
}

// for shared memory config flag
qint32 SA_Set_config_flag(quint32 modelist, quint32 changelist)
{
    //Johnson 190416
    if(bParaLoad) return 0;

  //changed by Steve
  if(1 == modelist)
  {
      SA_sm_config_update->sweep_flag = changelist;
  }
  else if(2 == modelist)
  {

      SA_sm_config_update->measure_flag = changelist;
  }
  else if(4 == modelist)
  {
      SA_sm_config_update->trigger_flag = changelist;
  }
  else if(8 == modelist)
  {
      SA_sm_config_update->doorControl_flag = changelist;
  }
#if USABLE
  else
  {
      SA_sm_config_update->system_flag = changelist;
  }
#endif
  SA_sm_config_update->top_flag = modelist;
  /*
    SA_sm_config_update->top_flag = SA_sm_config_update->top_flag|modelist;

    if (modelist&IXT_SA_ConfigSweep) SA_sm_config_update->sweep_flag = SA_sm_config_update->sweep_flag|changelist;
    else if (modelist&IXT_SA_ConfigMeasure) SA_sm_config_update->measure_flag = SA_sm_config_update->measure_flag|changelist;
    else if (modelist&IXT_SA_ConfigSystem) SA_sm_config_update->system_flag = SA_sm_config_update->system_flag|changelist;
  */
  return 0;
}


qint32 SA_Check_InitializeSharedMemory_fromGUI(void)
{
  int sm_test_id = shmget((key_t)SM_SA_Key_ConfigSweep, sizeof(SA_CONFIG_SWEEP), IPC_EXCL);
  if (sm_test_id == -1)
    {
      printf("Already created::test id - error shmget()\n\r");
      return sm_test_id;
    }

  return 0;
}

#endif
