//==============================================================================
//
// Title:		ShmEngine
// Purpose:		A short description of the command-line tool.
//
// Created on:	2018/2/5 at 9:35:16 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include "ShmEngine.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include "msgNoticeCode.h"
//==============================================================================
// Constants   

extern void ErrOutPut(DiInt32 errCode,DiInt32 itype);

//==============================================================================
// Types 

/*-----------------shm------------------------*/
typedef struct
{
    DiInt32 sm_configsweep_id;
    DiInt32 sm_configmeasure_id;
    DiInt32 sm_sweepdata_id;
#if USABLE
    DiInt32 sm_measuredata_id;  
#endif
    DiInt32 sm_sync_id;
    DiInt32 sm_configupdate_id;
    DiInt32 sm_channel_param_id;
    DiInt32 sm_fft_fir_commonnum_id;
    DiInt32 sm_sweep_num_id;

    //0925
    DiInt32 sm_bsactrl_id;

    DiInt32 sm_started_id;
    DiInt32 sm_tempercalc_id;

    DiInt32 sm_noticecode_id;
	

    void *sm_configsweep_addr;
    void *sm_configmeasure_addr;
    void *sm_sweepdata_addr;
#if USABLE
    void *sm_measuredata_addr;
#endif
    void *sm_sync_addr;
    void *sm_configupdate_addr;
    void *sm_channel_param_addr;
    void *sm_fft_fir_commonnum_addr;
    void *sm_sweep_num_addr;
    void *sm_bsactrl_addr;
    void *sm_started_addr;
    void *sm_tempercalc_addr;

    void *sm_noticecode_addr;
}_SM_INFO;
_SM_INFO sm_info; 

PCONFIG_SWEEP sm_config_sweep = NULL;
PCONFIG_MEASURE sm_config_measure = NULL;
PSWEEP_DATA sm_sweep_data = NULL;
#if _MEASURE_DATA
PMEASURE_DATA sm_measure_data = NULL;
#endif
PSM_SYNC sm_sync = NULL;
PCONFIG_UPDATE sm_config_update = NULL;

PCHANNEL_PARAM sm_channel_param = NULL;
PFFT_FIR_COMMON_NUM sm_fft_fir_common_num = NULL;
PSWEEP_NUM sm_sweep_num = NULL;
PTEMP_CALC sm_temper_calc = NULL;

SWEEPCTRL CTRL_SWEEP_MODE = SWEEP_IDLE;//0 continue 1 single 2 idle

PBSA_RUN_SYNC sm_basctrl = NULL;

PSTART_FLAG sm_startflag = NULL;

PALL_NOTIC_CODE sm_notic_code = NULL;
/*-----------------over-------------------------*/
DiInt32 IniShmCtrl(void* param)
{	
	sm_info.sm_configsweep_id = 0;
    	sm_info.sm_configsweep_addr = NULL;
    	sm_info.sm_configmeasure_id = 0;
    	sm_info.sm_configmeasure_addr = NULL;
    	sm_info.sm_sweepdata_id = 0;
    	sm_info.sm_sweepdata_addr = NULL;
#if USABLE
    	sm_info.sm_measuredata_id = 0;
    	sm_info.sm_measuredata_addr = NULL;    
#endif
	sm_info.sm_sync_id = 0;
	sm_info.sm_sync_addr = NULL;
	sm_info.sm_configupdate_id = 0;
	sm_info.sm_configupdate_addr = NULL;

	sm_info.sm_channel_param_id = 0;
	sm_info.sm_channel_param_addr = NULL;
	sm_info.sm_fft_fir_commonnum_id = 0;
	sm_info.sm_fft_fir_commonnum_addr = NULL;
	sm_info.sm_sweepdata_id = 0;
	sm_info.sm_sweepdata_addr = NULL;

	sm_info.sm_bsactrl_id = 0;
	sm_info.sm_bsactrl_addr = NULL;
	sm_info.sm_started_id = 0;
	sm_info.sm_started_addr = NULL;

	//0927 
    sm_info.sm_started_id = shmget((key_t)SM_CTRL7_KEY_START, sizeof(_START_FLAG), IPC_CREAT | 0777);
    if  (-1 == sm_info.sm_started_id)
        {
#if DEBUG_OUTPUT
	    perror("config_started_shm_failed");
#endif
	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_ShmGetID_startflag);
	    ErrOutPut(REDIRECT_YES,WRSHM_NO);
            return -1;
        }
    else
        {
            sm_info.sm_started_addr= shmat( sm_info.sm_started_id, (void*)0, 0);
            if (sm_info.sm_started_addr == (void*)-1)
                {
#if DEBUG_OUTPUT
		    perror("attach_started_shm_failed");
#endif
		    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_ShmGetAddr_startflag);
	    	    ErrOutPut(REDIRECT_YES,WRSHM_NO);
                    return -1;
                }
            sm_startflag = (PSTART_FLAG)sm_info.sm_started_addr;
        }
   

    //0925
    sm_info.sm_bsactrl_id = shmget((key_t)BSA_MANA_SHM_KEY, sizeof(BSA_RUN_SYNC), IPC_CREAT | 0777);
    if  (-1 == sm_info.sm_bsactrl_id)
        {
#if DEBUG_OUTPUT
	    perror("config_bsactrl_shm_failed");
#endif
	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_ShmGetID_basctrl);
	    ErrOutPut(REDIRECT_YES,WRSHM_NO);
            return -1;
        }
    else
        {
            sm_info.sm_bsactrl_addr= shmat( sm_info.sm_bsactrl_id, (void*)0, 0);
            if (sm_info.sm_bsactrl_addr == (void*)-1)
                {
#if DEBUG_OUTPUT
		    perror("attach_bsactrl_shm_failed");
#endif
		    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_ShmGetAddr_basctrl);
	    	    ErrOutPut(REDIRECT_YES,WRSHM_NO);
                    return -1;
                }
            sm_basctrl = (PBSA_RUN_SYNC)sm_info.sm_bsactrl_addr;
        }
 //0928 temp used,should 0
    sm_basctrl->appexit = 1;

	// config sweep
	sm_info.sm_configsweep_id = shmget((key_t)SM_Key_ConfigSweep, sizeof(_CONFIG_SWEEP), IPC_CREAT|0777);	
	if(-1 == sm_info.sm_configsweep_id)	
	{
#if DEBUG_OUTPUT
		perror("config_sweep_shm_failed");
#endif
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_ShmGetID_configsweep);
	    	ErrOutPut(REDIRECT_YES,WRSHM_NO);
		return -1;
	}
	else
	{
		//attach the shm addr to the thread
		sm_info.sm_configsweep_addr = shmat(sm_info.sm_configsweep_id, NULL, 0);
		if(sm_info.sm_configsweep_addr == (void*)-1)
		{
#if DEBUG_OUTPUT
			perror("attach_sweep_shm_failed");
#endif
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_ShmGetAddr_configsweep);
	    		ErrOutPut(REDIRECT_YES,WRSHM_NO);
			return -1;
		}
		sm_config_sweep = (_CONFIG_SWEEP*) sm_info.sm_configsweep_addr;
	}	

	// config measure
	sm_info.sm_configmeasure_id = shmget((key_t)SM_Key_ConfigMeasure, sizeof(_CONFIG_MEASURE), IPC_CREAT|0777);
	if(-1 == sm_info.sm_configmeasure_id)
	{
#if DEBUG_OUTPUT
		perror("config_measure_shm_failed");
#endif
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_ShmGetID_configmeasure);
	    	ErrOutPut(REDIRECT_YES,WRSHM_NO);
		return -1;
	}
	else
	{
		sm_info.sm_configmeasure_addr = shmat(sm_info.sm_configmeasure_id, (void*)0, 0);
		if (sm_info.sm_configmeasure_addr == (void*)-1)
		{
#if DEBUG_OUTPUT
			perror("attach_measure_shm_failed");
#endif
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_ShmGetAddr_configmeasure);
	    		ErrOutPut(REDIRECT_YES,WRSHM_NO);
			return -1;
		}
		sm_config_measure = (_CONFIG_MEASURE *)sm_info.sm_configmeasure_addr;
	}	

	// sweep data
	sm_info.sm_sweepdata_id = shmget((key_t)SM_Key_SweepData, sizeof(_SWEEP_DATA), IPC_CREAT|0666);
	if(-1 == sm_info.sm_sweepdata_id)
	{
#if DEBUG_OUTPUT
		perror("config_sweepdata_shm_failed");
#endif
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_ShmGetID_sweepdata);
	    	ErrOutPut(REDIRECT_YES,WRSHM_NO);

		return -1;
	}
	else
	{
		sm_info.sm_sweepdata_addr = shmat(sm_info.sm_sweepdata_id, (void*)0, 0);
		if (sm_info.sm_sweepdata_addr == (void*)-1)
		{
#if DEBUG_OUTPUT
			perror("attach_sweepdata_shm_failed");
#endif
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_ShmGetAddr_sweepdata);
	    		ErrOutPut(REDIRECT_YES,WRSHM_NO);
			return -1;
		}
		sm_sweep_data = (_SWEEP_DATA *)sm_info.sm_sweepdata_addr;
	}
#if USABLE
	// measure data
	sm_info.sm_measuredata_id = shmget((key_t)SM_Key_MeasureData, sizeof(_MEASURE_DATA), IPC_CREAT|0666);
	if(-1 == sm_info.sm_measuredata_id)
	{
#if DEBUG_OUTPUT
		perror("config_measuredata_shm_failed");
#endif
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_ShmGetID_measuredata);
	    	ErrOutPut(REDIRECT_YES,WRSHM_NO);
		return -1;
	}
	else
	{
		sm_info.sm_measuredata_addr = shmat(sm_info.sm_measuredata_id, (void*)0, 0);
		if (sm_info.sm_measuredata_addr == (void*)-1)
		{
#if DEBUG_OUTPUT
			perror("attach_measuredata_shm_failed");
#endif
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_ShmGetAddr_measuredata);
	    		ErrOutPut(REDIRECT_YES,WRSHM_NO);
			return -1;
		}
		sm_measure_data = (_MEASURE_DATA *) sm_info.sm_measuredata_addr;
	}	
#endif

	// sync
	sm_info.sm_sync_id = shmget((key_t)SM_Key_Sync, sizeof(_SM_SYNC), IPC_CREAT|0666);
	if  (-1 == sm_info.sm_sync_id)
	{
#if DEBUG_OUTPUT
		perror("config_sync_shm_failed");
#endif
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_ShmGetID_sync);
	    	ErrOutPut(REDIRECT_YES,WRSHM_NO);
		return -1;
	}
	else
	{
		sm_info.sm_sync_addr = shmat(sm_info.sm_sync_id, (void*)0, 0);
		if (sm_info.sm_sync_addr == (void*)-1)
		{
#if DEBUG_OUTPUT
			perror("attach_sync_shm_failed");
#endif
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_ShmGetAddr_sync);
	    		ErrOutPut(REDIRECT_YES,WRSHM_NO);
			return -1;
		}
		sm_sync = (_SM_SYNC *)sm_info.sm_sync_addr;
		sm_sync-> BufferSync = 0;
		//pthread_mutex_init(&sm_sync->lockobj,NULL);				
	}

	// config update
	sm_info.sm_configupdate_id = shmget((key_t)SM_Key_ConfigUpdate, sizeof(_CONFIG_UPDATE), IPC_CREAT|0777);	
	if  (-1 == sm_info.sm_configupdate_id)
	{
#if DEBUG_OUTPUT
		perror("config_update_shm_failed");
#endif
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_ShmGetID_configupdate);
	    	ErrOutPut(REDIRECT_YES,WRSHM_NO);

		return -1;
	}
	else
	{
		sm_info.sm_configupdate_addr = shmat(sm_info.sm_configupdate_id, (void*)0, 0);		
		if (sm_info.sm_configupdate_addr == (void*)-1)
		{
#if DEBUG_OUTPUT
			perror("attach_update_shm_failed");
#endif
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_ShmGetAddr_configupdate);
    			ErrOutPut(REDIRECT_YES,WRSHM_NO);

			return -1;
		}
		sm_config_update = (_CONFIG_UPDATE *) sm_info.sm_configupdate_addr;			
	}
	
	//channel param 
	sm_info.sm_channel_param_id = shmget((key_t)SM_Key_Channelparam, sizeof(CHANNEL_PARAM), IPC_CREAT|0666);
	if(-1 == sm_info.sm_channel_param_id)
	{
#if DEBUG_OUTPUT
		perror("config_channel_param_shm_failed");
#endif
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_ShmGetID_channelparam);
	    	ErrOutPut(REDIRECT_YES,WRSHM_NO);

		return -1;
	}
	else
	{
		sm_info.sm_channel_param_addr = shmat(sm_info.sm_channel_param_id, (void*)0, 0);
		if (sm_info.sm_channel_param_addr == (void*)-1)
		{
#if DEBUG_OUTPUT
			perror("attach_channel_param_shm_failed");
#endif
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_ShmGetAddr_channelparam);
    			ErrOutPut(REDIRECT_YES,WRSHM_NO);

			return -1;
		}
		sm_channel_param = (CHANNEL_PARAM*)sm_info.sm_channel_param_addr;
	}
	
	//fft_fir commom num
	sm_info.sm_fft_fir_commonnum_id = shmget((key_t)SM_Key_FftFirCommonnum, sizeof(FFT_FIR_COMMON_NUM), IPC_CREAT|0666);
	if(-1 == sm_info.sm_fft_fir_commonnum_id)
	{
#if DEBUG_OUTPUT
		perror("config_fft_fir_commonnum_shm_failed");
#endif
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_ShmGetID_fftfircommonnum);
	    	ErrOutPut(REDIRECT_YES,WRSHM_NO);

		return -1;
	}
	else
	{
		sm_info.sm_fft_fir_commonnum_addr = shmat(sm_info.sm_fft_fir_commonnum_id, (void*)0, 0);
		if (sm_info.sm_fft_fir_commonnum_addr == (void*)-1)
		{
#if DEBUG_OUTPUT
			perror("attach_fft_fir_commonnum_shm_failed");
#endif
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_ShmGetAddr_fftfircommonnum);
	    		ErrOutPut(REDIRECT_YES,WRSHM_NO);

			return -1;
		}
		sm_fft_fir_common_num  = (FFT_FIR_COMMON_NUM*)sm_info.sm_fft_fir_commonnum_addr;
	}
 
	
	//sweep num 
	sm_info.sm_sweep_num_id = shmget((key_t)SM_Key_SweepNum  , sizeof(SWEEP_NUM), IPC_CREAT|0666);
	if(-1 == sm_info.sm_sweep_num_id)
	{
#if DEBUG_OUTPUT
		perror("config_sweep_num_shm_failed");
#endif
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_ShmGetID_sweepnum);
	    	ErrOutPut(REDIRECT_YES,WRSHM_NO);

		return -1;
	}
	else
	{
		sm_info.sm_sweep_num_addr = shmat(sm_info.sm_sweep_num_id, (void*)0, 0);
		if (sm_info.sm_sweep_num_addr == (void*)-1)
		{
#if DEBUG_OUTPUT
			perror("attach_sweep_num_shm_failed");
#endif
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_ShmGetAddr_sweepnum);
    			ErrOutPut(REDIRECT_YES,WRSHM_NO);

			return -1;
		}
		sm_sweep_num  = (SWEEP_NUM*)sm_info.sm_sweep_num_addr;
	}

// config temper calc
	sm_info.sm_tempercalc_id = shmget((key_t)SM_Key_TemperCalc, sizeof(TEMP_CALC), IPC_CREAT|0666);	
	if  (-1 == sm_info.sm_tempercalc_id)
	{
#if DEBUG_OUTPUT
		perror("temp_calc_shm_failed");
#endif
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_ShmGetID_tempercalc);
	    	ErrOutPut(REDIRECT_YES,WRSHM_NO);

		return -1;
	}
	else
	{
		sm_info.sm_tempercalc_addr = shmat(sm_info.sm_tempercalc_id, (void*)0, 0);		
		if (sm_info.sm_tempercalc_addr == (void*)-1)
		{
#if DEBUG_OUTPUT
			perror("attach_temp_calc_shm_failed");
#endif
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_ShmGetAddr_tempercalc);
	    		ErrOutPut(REDIRECT_YES,WRSHM_NO);

			return -1;
		}
		sm_temper_calc = (TEMP_CALC *) sm_info.sm_tempercalc_addr;			
	}

	//Johnson 091107 create noticcode shm
	sm_info.sm_noticecode_id = shmget((key_t)SM_KEY_NOTICE,sizeof(ALL_NOTIC_CODE),IPC_CREAT|0666);
	if  (-1 == sm_info.sm_noticecode_id)
	{
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_ShmGetID_noticecode);
		ErrOutPut(REDIRECT_YES,WRSHM_NO);
		return -1;
	}
	else
	{
		sm_info.sm_noticecode_addr = shmat(sm_info.sm_noticecode_id, (void*)0, 0);
		if (sm_info.sm_noticecode_addr == (void*)-1)
		{
		    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_ShmGetAddr_noticecode);
		    ErrOutPut(REDIRECT_YES,WRSHM_NO);
		    return -1;
		}
		sm_notic_code = (ALL_NOTIC_CODE *) sm_info.sm_noticecode_addr;
	}

	return 0;
}


DiInt32 CloseShmCtrl(void* param)
{
	DiInt32 iBack = 0;
	iBack = shmctl(sm_info.sm_configsweep_id,IPC_RMID,NULL);
		if(iBack < 0)return iBack;
	iBack = shmctl(sm_info.sm_configmeasure_id,IPC_RMID,NULL);
		if(iBack < 0)return iBack;
	iBack = shmctl(sm_info.sm_sweepdata_id,IPC_RMID,NULL);
		if(iBack < 0)return iBack;
#if USABLE
	iBack = shmctl(sm_info.sm_measuredata_id,IPC_RMID,NULL);
		if(iBack < 0)return iBack;
#endif
	iBack = shmctl(sm_info.sm_sync_id,IPC_RMID,NULL);
		if(iBack < 0)return iBack;
	iBack = shmctl(sm_info.sm_configupdate_id,IPC_RMID,NULL);
		if(iBack < 0)return iBack;	

	iBack = shmctl(sm_info.sm_channel_param_id,IPC_RMID,NULL);
		if(iBack < 0)return iBack;
	iBack = shmctl(sm_info.sm_fft_fir_commonnum_id,IPC_RMID,NULL);
		if(iBack < 0)return iBack;
	iBack = shmctl(sm_info.sm_sweep_num_id,IPC_RMID,NULL);
		if(iBack < 0)return iBack;
	iBack = shmctl(sm_info.sm_tempercalc_id,IPC_RMID,NULL);
		if(iBack < 0)return iBack;
	return iBack;
}
