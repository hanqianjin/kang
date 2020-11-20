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
//==============================================================================
// Constants   

//==============================================================================
// Types 

/*-----------------shm------------------------*/
typedef struct
{ 
    DiInt32 sm_configsystem_id;
    DiInt32 sm_systeminfo_id;
    DiInt32 sm_configupdate_id;
    DiInt32 sm_tempercalc_id;
    DiInt32 shm_pltnoti_id;

    void *sm_configsystem_addr;
    void *sm_systeminfo_addr;
    void *sm_configupdate_addr;
    void *sm_tempercalc_addr;
    void *pshm_pltnotic;

}_SM_INFO;
_SM_INFO sm_info; 


PCONFIG_SYSTEM sm_config_system = NULL;
PSYSTEM_INFO sm_system_info = NULL;
PCONFIG_UPDATE sm_config_update = NULL;
PTEMP_CALC sm_temper_calc = NULL;
PALL_NOTIC_CODE sm_notic_excep = NULL;
/*-----------------over-------------------------*/
DiInt32 IniShmCtrl(void* param)
{

    sm_info.sm_configsystem_id = 0;
    sm_info.sm_configsystem_addr = NULL;
    sm_info.sm_systeminfo_id = 0;
    sm_info.sm_systeminfo_addr = NULL;
    sm_info.sm_configupdate_id = 0;
    sm_info.sm_configupdate_addr = NULL;

    sm_info.shm_pltnoti_id = 0;
    sm_info.pshm_pltnotic = NULL;

    sm_info.shm_pltnoti_id = shmget((key_t)SM_Key_ExcepNotic,sizeof(ALL_NOTIC_CODE),IPC_CREAT | 0666);
    if  (-1 == sm_info.shm_pltnoti_id)
        {
            return errno;
        }
    else
        {
            sm_info.pshm_pltnotic= shmat(sm_info.shm_pltnoti_id, (void*)0, 0);
            if (sm_info.pshm_pltnotic == (void*)-1)
                {
                    return errno;
                }
            sm_notic_excep = (PALL_NOTIC_CODE)(sm_info.pshm_pltnotic);
        }
    // config system
    sm_info.sm_configsystem_id = shmget((key_t)SM_Key_ConfigSystem, sizeof(_CONFIG_SYSTEM), IPC_CREAT|0666);
    if  (-1 == sm_info.sm_configsystem_id)
        {
            printf(strerror(errno));
            setNoticePara(1,2,0,PLT_EXCE_SOURCE);
            sm_notic_excep->noticode = GetNoticeCode();
            return errno;
        }
    else
        {
            sm_info.sm_configsystem_addr = shmat(sm_info.sm_configsystem_id, (void*)0, 0);
            if (sm_info.sm_configsystem_addr == (void*)-1)
                {
                    //perror("attach_system_shm_failed");
                    printf(strerror(errno));
                    setNoticePara(1,2,1,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    return errno;
                }
            sm_config_system = (_CONFIG_SYSTEM *) sm_info.sm_configsystem_addr;
        }

    // system info
    sm_info.sm_systeminfo_id = shmget((key_t)SM_Key_SystemInfo, sizeof(_SYSTEM_INFO), IPC_CREAT|0666);
    if  (-1 == sm_info.sm_systeminfo_id)
        {
            printf(strerror(errno));
            setNoticePara(1,2,0,PLT_EXCE_SOURCE);
            sm_notic_excep->noticode = GetNoticeCode();
            return errno;
        }
    else
        {
            sm_info.sm_systeminfo_addr = shmat(sm_info.sm_systeminfo_id, (void*)0, 0);
            if (sm_info.sm_systeminfo_addr == (void*)-1)
                {
                    printf(strerror(errno));
                    setNoticePara(1,2,1,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    return errno;
                }
            sm_system_info = (_SYSTEM_INFO *) sm_info.sm_systeminfo_addr;
        }

    // config update
    sm_info.sm_configupdate_id = shmget((key_t)SM_Key_ConfigUpdate, sizeof(_CONFIG_UPDATE), IPC_CREAT|0666);
    if  (-1 == sm_info.sm_configupdate_id)
        {
            printf(strerror(errno));
            setNoticePara(1,2,0,PLT_EXCE_SOURCE);
            sm_notic_excep->noticode = GetNoticeCode();
            return errno;
        }
    else
        {
            sm_info.sm_configupdate_addr = shmat(sm_info.sm_configupdate_id, (void*)0, 0);
            if (sm_info.sm_configupdate_addr == (void*)-1)
                {
                    printf(strerror(errno));
                    setNoticePara(1,2,1,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    return errno;
                }
            sm_config_update = (_CONFIG_UPDATE *) sm_info.sm_configupdate_addr;
        }

    // config temper calc
    sm_info.sm_tempercalc_id = shmget((key_t)SM_Key_TemperCalc, sizeof(TEMP_CALC), IPC_CREAT|0666);
    if  (-1 == sm_info.sm_tempercalc_id)
        {
            printf(strerror(errno));
            setNoticePara(1,2,0,PLT_EXCE_SOURCE);
            sm_notic_excep->noticode = GetNoticeCode();
            return errno;
        }
    else
        {
            sm_info.sm_tempercalc_addr = shmat(sm_info.sm_tempercalc_id, (void*)0, 0);
            if (sm_info.sm_tempercalc_addr == (void*)-1)
                {
                    printf(strerror(errno));
                    setNoticePara(1,2,1,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    return errno;
                }
            sm_temper_calc = (TEMP_CALC *) sm_info.sm_tempercalc_addr;
        }
    return 0;
}


DiInt32 CloseShmCtrl(void* param)
{
    DiInt32 iBack = 0;
    iBack = shmctl(sm_info.sm_configsystem_id,IPC_RMID,NULL);
    if(iBack < 0)return iBack;
    iBack = shmctl(sm_info.sm_systeminfo_id,IPC_RMID,NULL);
    if(iBack < 0)return iBack;
    iBack = shmctl(sm_info.sm_configupdate_id,IPC_RMID,NULL);
    if(iBack < 0)return iBack;
    iBack = shmctl(sm_info.sm_tempercalc_id,IPC_RMID,NULL);
    if(iBack < 0)return iBack;
    return iBack;
}
