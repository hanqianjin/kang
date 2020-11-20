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
#include "string.h"
//==============================================================================
// Constants   

//==============================================================================
// Types 

/*-----------------shm------------------------*/
typedef struct
{
    DiInt32 sm_configrsactrl_id;
    DiInt32 sm_sweepdata_id; 
    DiInt32 sm_sync_id;
    DiInt32 sm_configupdate_id;   
    DiInt32 sm_rsactrl_id;
    DiInt32 sm_started_id;
	DiInt32 sm_tempercalc_id;
	DiInt32 sm_notice_id;

    void *sm_configrsactrl_addr;
    void *sm_sweepdata_addr;
    void *sm_sync_addr;
    void *sm_configupdate_addr;
    void *sm_rsactrl_addr;
    void *sm_started_addr;
	void *sm_tempercalc_addr;
	void *sm_notice_addr;
}_SM_INFO;

_SM_INFO sm_info; 
PCONFIG_RSA_CTRL sm_config_rsa_ctrl = NULL;
PSWEEP_DATA sm_sweep_data = NULL;
PSM_SYNC sm_sync = NULL;
PCONFIG_UPDATE sm_config_update = NULL;
SWEEPCTRL CTRL_SWEEP_MODE = SWEEP_IDLE;//0 continue 1 single 2 idle
PRSA_RUN_SYNC sm_rasctrl = NULL;
PSTART_FLAG sm_startflag = NULL;
PTEMP_CALC sm_temper_calc = NULL;
PALL_NOTIC_CODE sm_notice_calc = NULL;
/*-----------------over-------------------------*/
DiInt32 IniShmCtrl(void* param)
{	
	sm_info.sm_configrsactrl_id = 0;
    	sm_info.sm_configrsactrl_addr = NULL;
    	sm_info.sm_sweepdata_id = 0;
    	sm_info.sm_sweepdata_addr = NULL;
	sm_info.sm_sync_id = 0;
	sm_info.sm_sync_addr = NULL;
	sm_info.sm_configupdate_id = 0;
	sm_info.sm_configupdate_addr = NULL;
	sm_info.sm_rsactrl_id = 0;
	sm_info.sm_rsactrl_addr = NULL;
	sm_info.sm_started_id = 0;
	sm_info.sm_started_addr = NULL;
	sm_info.sm_tempercalc_id = 0;
	sm_info.sm_tempercalc_addr = NULL;
	sm_info.sm_notice_id = 0;
	sm_info.sm_notice_addr = NULL;
	

	
    sm_info.sm_started_id = shmget((key_t)SM_CTRL_KEY_START, sizeof(_START_FLAG), IPC_CREAT | 0777);
    if  (-1 == sm_info.sm_started_id)
        {
	    printf("sm_started_id errno,%d:%s",errno,strerror(errno));
            return errno;
        }
    else
        {
            sm_info.sm_started_addr= shmat( sm_info.sm_started_id, (void*)0, 0);
            if (sm_info.sm_started_addr == (void*)-1)
                {
		    printf("sm_started_addr errno,%d:%s",errno,strerror(errno));
                    return errno;
                }
            sm_startflag = (PSTART_FLAG)sm_info.sm_started_addr;
        }
    
    sm_info.sm_rsactrl_id = shmget((key_t)RSA_MANA_SHM_KEY, sizeof(RSA_RUN_SYNC), IPC_CREAT | 0777);
    if  (-1 == sm_info.sm_rsactrl_id)
        {
	    printf("sm_rsactrl_id errno,%d:%s",errno,strerror(errno));
            return errno;
        }
    else
        {
            sm_info.sm_rsactrl_addr= shmat( sm_info.sm_rsactrl_id, (void*)0, 0);
            if (sm_info.sm_rsactrl_addr == (void*)-1)
                {
	    printf("sm_rsactrl_addr errno,%d:%s",errno,strerror(errno));
                    return errno;
                }
            sm_rasctrl = (PRSA_RUN_SYNC)sm_info.sm_rsactrl_addr;
        }
    sm_rasctrl->appexit = 1;

	
	sm_info.sm_configrsactrl_id = shmget((key_t)SM_Key_ConfigRsaCtrl, sizeof(_CONFIG_RSA_CTRL), IPC_CREAT|0777);	
	if(-1 == sm_info.sm_configrsactrl_id)	
	{
		printf("sm_configrsactrl_id errno,%d:%s",errno,strerror(errno));            
			return errno;
	}
	else
	{		
		sm_info.sm_configrsactrl_addr = shmat(sm_info.sm_configrsactrl_id, NULL, 0);
		if(sm_info.sm_configrsactrl_addr == (void*)-1)
		{
			printf("sm_configrsactrl_addr errno,%d:%s",errno,strerror(errno));            
			return errno;
		}
		sm_config_rsa_ctrl = (_CONFIG_RSA_CTRL*) sm_info.sm_configrsactrl_addr;
	}
	

	// sweep data
	sm_info.sm_sweepdata_id = shmget((key_t)SM_Key_SweepData, sizeof(_SWEEP_DATA), IPC_CREAT|0666);
	if(-1 == sm_info.sm_sweepdata_id)
	{
		printf("sm_sweepdata_id errno,%d:%s",errno,strerror(errno));            
			return errno;
	}
	else
	{
		sm_info.sm_sweepdata_addr = shmat(sm_info.sm_sweepdata_id, (void*)0, 0);
		if (sm_info.sm_sweepdata_addr == (void*)-1)
		{
			printf("sm_sweepdata_addr errno,%d:%s",errno,strerror(errno));            
			return errno;
		}
		sm_sweep_data = (_SWEEP_DATA *)sm_info.sm_sweepdata_addr;
	}
	
	// sync
	sm_info.sm_sync_id = shmget((key_t)SM_Key_Sync, sizeof(_SM_SYNC), IPC_CREAT|0666);
	if  (-1 == sm_info.sm_sync_id)
	{
		printf("sm_sync_id errno,%d:%s",errno,strerror(errno));            
			return errno;
	}
	else
	{
		sm_info.sm_sync_addr = shmat(sm_info.sm_sync_id, (void*)0, 0);
		if (sm_info.sm_sync_addr == (void*)-1)
		{
			printf("sm_sync_addr errno,%d:%s",errno,strerror(errno));            
			return errno;
		}
		sm_sync = (_SM_SYNC *)sm_info.sm_sync_addr;							
	}

	// config update
	sm_info.sm_configupdate_id = shmget((key_t)SM_Key_ConfigUpdate, sizeof(_CONFIG_UPDATE), IPC_CREAT|0777);	
	if  (-1 == sm_info.sm_configupdate_id)
	{
		printf("sm_configupdate_id errno,%d:%s",errno,strerror(errno));            
			return errno;
	}
	else
	{
		sm_info.sm_configupdate_addr = shmat(sm_info.sm_configupdate_id, (void*)0, 0);		
		if (sm_info.sm_configupdate_addr == (void*)-1)
		{
			printf("sm_configupdate_addr errno,%d:%s",errno,strerror(errno));            
			return errno;
		}
		sm_config_update = (_CONFIG_UPDATE *) sm_info.sm_configupdate_addr;			
	}
	// config temper calc
	sm_info.sm_tempercalc_id = shmget((key_t)SM_Key_TemperCalc, sizeof(TEMP_CALC), IPC_CREAT|0666);	
	if  (-1 == sm_info.sm_tempercalc_id)
	{
		perror("temp_calc_shm_failed");
			return -1;
	}
	else
	{
		sm_info.sm_tempercalc_addr = shmat(sm_info.sm_tempercalc_id, (void*)0, 0);		
		if (sm_info.sm_tempercalc_addr == (void*)-1)
		{
			perror("attach_temp_calc_shm_failed");
				return -1;
		}
		sm_temper_calc = (TEMP_CALC *) sm_info.sm_tempercalc_addr;			
	}
	// config notice 
	sm_info.sm_notice_id = shmget((key_t)RSA_NOTICE_CODE_KEY, sizeof(ALL_NOTIC_CODE), IPC_CREAT|0666);	
	if  (-1 == sm_info.sm_notice_id)
	{
		perror("temp_calc_shm_failed");
			return -1;
	}
	else
	{
		sm_info.sm_notice_addr = shmat(sm_info.sm_notice_id, (void*)0, 0);		
		if (sm_info.sm_notice_addr == (void*)-1)
		{
			perror("attach_temp_calc_shm_failed");
				return -1;
		}
		sm_notice_calc = (ALL_NOTIC_CODE *) sm_info.sm_notice_addr;			
	}


	return 0;
}

//unused
DiInt32 CloseShmCtrl(void* param)
{
	DiInt32 iBack = 0;
	iBack = shmctl(sm_info.sm_configrsactrl_id,IPC_RMID,NULL);
		if(iBack < 0)return iBack;
	iBack = shmctl(sm_info.sm_sweepdata_id,IPC_RMID,NULL);
		if(iBack < 0)return iBack;
	iBack = shmctl(sm_info.sm_sync_id,IPC_RMID,NULL);
		if(iBack < 0)return iBack;
	iBack = shmctl(sm_info.sm_configupdate_id,IPC_RMID,NULL);
		if(iBack < 0)return iBack;	
	return iBack;
}
