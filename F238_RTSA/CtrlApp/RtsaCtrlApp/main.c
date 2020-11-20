#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include "ShmEngine.h"
#include "DiIoCtrl.h"
#include "MainBoardVirtualDriver.h"
#include "RfVirtualDriver.h"
#include "SaAnalysis.h"
#include "SaDataStruct.h"
#include "MidMsg.h"
#include "DigSigDealVirtualDriver.h"
#include "sweepinterupt.h"
#include "BitSehInfo.h"
#include "sweepinterupt.h"
#include "time.h"
#include "dpxMem.h"
#include "DpxContrl.h"
#include "msgNoticeCode.h"
//---------------------------------------------
typedef struct
{
    sem_t thread_syn_sem;
    pthread_t threadId;
    void* (*func)(void* param);
}THREAD_INFO,*PTHREAD_INFO;

THREAD_INFO mid_msg_thread;
PTHREAD_INFO pmid_msg_thread = NULL;

THREAD_INFO resweep_interrupt_thread;
PTHREAD_INFO presweep_interrupt_thread = NULL;

THREAD_INFO acquire_data_thread;
PTHREAD_INFO pacquire_data_thread = NULL;
//-----------------------------------------------
#define THREAD_BY_TIME 10000 //for thread start one by one
extern _SM_SYNC syncMana;
extern PCONFIG_UPDATE sm_config_update;
extern PCONFIG_RSA_CTRL sm_config_rsa_ctrl;

#define UPFLAG  (37)
//-----------------------------------------------
//global static obj
static struct timespec wtime;//test time
//-----------------------------------------------
//global obj
DiInt32 syncHandle = 0;
DiInt32 guiHandle = 0;
DiInt32 sweepHandle = 0;
//-----------------------------------------------
//static func
static DiInt32 WhileFunc(void);
static DiInt32 StartMultiWork(void);
static DiInt32 ObjIni(void);
static DiInt32 ProRelease(void* param);

//Albert 19/04/19
static DiInt32 UpdateMsg();
//static DiInt32 InitTriggerParam();

//Albert for DPX
void *pAddr  = NULL;
DiSession DpxHandler = 0;
extern PSWEEP_DATA sm_sweep_data;
extern void ReleaseCtrlInHand(DiInt32 handle);
//void DpxReadfunc (void *pAddr)
//{
//	ReleaseCtrlInHand(sweepHandle);
//	printf("ctrl app sweep interrupt!!!!\n");
//	return;	
//}
//-----------------------------------------------
//global func
//DiSession rfHandle;
extern DiSession bitdevHandle;
extern _CONFIG_RSA_CTRL localConfigRsaCtrl;
extern PALL_NOTIC_CODE sm_notice_calc;
DiInt32 LangType = 0;
#define Len 128
static DiChar errBuffer[Len];	
void ErrOutPut(DiInt32 errCode,DiInt32 itype);

void ErrOutPutEx(DiInt32 ToLogFlag,DiInt32 ToShmFlag);
RSA_EXIT gappexit;
//0927 steve,for back recover
extern PSTART_FLAG sm_startflag;
extern PSM_SYNC sm_sync;

int main(int argc, char *argv[])
{	
    DiInt32 iBack = 0;

    //20190121 steve 
    setvbuf(stdout, (char *)NULL, _IONBF, 0);   
    time_t timep;
    time (&timep); 
//#if ERR_PRINT_DEBUG
    printf("RTSA CTRL APP START UP:%s",asctime(gmtime(&timep)));
//#endif
	// Init Notice Msg
	initNoticeCode(RTSA_MODU, CONTROL_PROGRAM);

    //shm done
    iBack = IniShmCtrl(NULL);
	if(iBack < 0)
		{
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,RTSA_CTL_SHM_INIT);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_ENABLE);
#if ERR_PRINT_DEBUG
		printf("IniShmCtrl error\n");
#endif
		}
//	sm_sync->CtrlAppRunOk = 1;
    //open and ini dev
    iBack = ObjIni();

    //load the calibrate data
    iBack = LoadCalibrateDatas();
    //if(iBack >= 0)
       // printf("load calc datas successed\n");

    iBack = StartMultiWork();
    printf("start multi thread state is %d\n",iBack);

    //tell the GUI that the ctrl app run well
    if(iBack >= 0)
        {
            syncMana.CtrlAppRunOk = 1;
        }
    else
        {
            syncMana.CtrlAppRunOk = -1;
        }
    WhileFunc();
   //Albert 19/05/09 when ctrl app exit, should stop rtsa fpga and wait dpx current data transimit done.
	SetRtSaFpgaStop(bitdevHandle);
	 usleep(10000);
	 
    ProRelease(NULL);
    FreeMemBuffer();   
#if ERR_PRINT_DEBUG
 	 printf("start multi thread stop\n");
#endif
   return 0;
}

static DiInt32 WhileFunc(void)
{
    while(gappexit.mainthreadExit)
        {
            usleep(10000);
        }
#if ERR_PRINT_DEBUG
    printf("gappexit.mainthreadExit is %d\n",gappexit.mainthreadExit);
#endif
    return 0;
}

static DiInt32 ProRelease(void* param)
{	
    ClosePlInterrupt();
    return BitClose(bitdevHandle);
}
static DiInt32 ObjIni(void)
{    
    gappexit.acqthreadExit = 1;
    gappexit.listenthreadExit = 1;
    gappexit.mainthreadExit = 1;
    gappexit.midmsgthreadExit = 1;    
    
    localConfigRsaCtrl.TracePoint = 801;
    localConfigRsaCtrl.attenAuto = 1;  

//	sm_startflag->startedflag = UPFLAG;



//#if BIT_DEBUG	 DPX data remove to GUI 
	//DpxEn(DpxHandler,0x1);
	//openDPXMem(&DpxHandler);	
	//registerDPXHandler(DpxHandler, DpxReadfunc);
	//pAddr = (void *)getDPXAddr(DpxHandler);


	
//#endif
    DiInt32 iBack  = 0;
    iBack = BitOpen("/dev/pl-mem",&bitdevHandle);
    if(iBack < 0)
        {
            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,RTSA_CTL_MEM_MAP);
			 ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_ENABLE);
#if ERR_PRINT_DEBUG
            printf("mem map ini failed\n");
#endif
          return iBack;
    	}
		// here must wait fpga get ready
	iBack =  WaitFpgaReady(bitdevHandle);
    if(iBack < 0)
        {
            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,RTSA_CTL_FPGA_LOAD);
			 ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_ENABLE);
#if ERR_PRINT_DEBUG
            printf("fpga load error\n");
#endif
            return iBack;
        }

	iBack = OpenPlInterrupt();
    if(iBack < 0)
        {
            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,RTSA_CTL_INT_OPEN);
			 ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_ENABLE);
#if ERR_PRINT_DEBUG
            printf("interrupt ini failed\n");
#endif
            return iBack;
        }   		
    iBack = SetRtSaIFBandWidth(bitdevHandle);
    if(iBack < 0)
        {
            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,RTSA_CTL_IFBW);
			 ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_ENABLE);
#if ERR_PRINT_DEBUG
            printf("rtsa if bw set error\n");
#endif
            return iBack;
        }
		
    if((syncHandle = semget(SYNC_KEY,1,IPC_CREAT | 0660))<0)
        {
        		strerror(errno);
//            printf("semget errno,%d:%s",errno,strerror(errno));
        }

    if(semctl(syncHandle,0,SETVAL,1) < 0)
        {
        		strerror(errno);
//            printf("init error,%d:%s",errno,strerror(errno));
        }

    if((guiHandle = semget(SYNC_KEY_GUI,1,IPC_CREAT | 0660))<0)
        {
        		strerror(errno);
//            printf("semget errno,%d:%s",errno,strerror(errno));
        }

    if(semctl(guiHandle,0,SETVAL,1) < 0)
        {
        		strerror(errno);
//            printf("init error,%d:%s",errno,strerror(errno));
        }

    if((sweepHandle = semget(SYNC_SWEEP,1,IPC_CREAT | 0660))<0)
        {
        		strerror(errno);
//            printf("semget errno,%d:%s",errno,strerror(errno));
        }

    if(semctl(sweepHandle,0,SETVAL,0) < 0)
        {
       		strerror(errno);
//            printf("init error,%d:%s",errno,strerror(errno));
        }
    pmid_msg_thread	 = &mid_msg_thread;
    pmid_msg_thread->func = MidMsgFunc;

    presweep_interrupt_thread = &resweep_interrupt_thread;
    presweep_interrupt_thread->func = ListenAndDownSweepParamFunc;

    pacquire_data_thread = &acquire_data_thread;
    pacquire_data_thread->func = AcqDataFunc;

		   UpdateMsg();
    return 0;
}

static DiInt32 StartMultiWork(void)
{
    //mid msg listen thread

    DiInt32 iBack = pthread_create(&pmid_msg_thread->threadId,NULL,pmid_msg_thread->func,NULL);
    if(iBack < 0)
        {
#if ERR_PRINT_DEBUG
            printf("mid msg thread create fail");
#endif
       }
    /*
    iBack = pthread_create(&presweep_interrupt_thread->threadId,NULL,presweep_interrupt_thread->func,NULL);
    if(iBack < 0)
        {
            perror("listen interrupt thread create fail");
        }
    */

    usleep(THREAD_BY_TIME);
    iBack = pthread_create(&pacquire_data_thread->threadId,NULL,pacquire_data_thread->func,NULL);
    if(iBack < 0)
        {
 #if ERR_PRINT_DEBUG
           printf("data acq thread create fail");
 #endif
       }
    return iBack;
}

void ErrOutPut(DiInt32 errCode,DiInt32 itype)
{
    time_t timep;
    time (&timep);
    memset(errBuffer,0,Len);
    BitGetErrorInfo(errCode,LangType,errBuffer);		
    printf("type:%d,err:%d, %s;time:%s\n",itype,errCode,errBuffer,asctime(gmtime(&timep)));
    return;
}
void ErrOutPutEx(DiInt32 ToLogFlag,DiInt32 ToShmFlag)
{
    DiUInt32 errCode = GetNoticeCode();
	if(LOG_FLAG_ENABLE == ToLogFlag)
		{
			printf("error index:    %0x\n",errCode);
		}
	if(SHM_FLAG_ENABLE == ToShmFlag)
		{
			sm_notice_calc->noticode = errCode;
		}
    return;
}
DiInt32 UpdateMsg()
{
#if BIT_DEBUG
return 0;
#endif
	DiInt32 iBack = 0;
	iBack = SetRtSaFpgaStop(bitdevHandle);
	if(iBack < 0)
    {
   	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_ENABLE);
       return iBack;
    }
//	DpxEn(bitdevHandle, 0);

//	iBack = EliminateDC(bitdevHandle,0);
//	usleep(1000);
//	iBack = EliminateDC(bitdevHandle,1);
//	printf("sm_startflag->startedflag %d\n",sm_startflag->startedflag);
//sm_startflag->startedflag = UPFLAG;	
    if(sm_startflag->startedflag != UPFLAG)
    {
//		RtSaTestParam(bitdevHandle);
		DpxTest(bitdevHandle);
	iBack = SetRtSaRBW(bitdevHandle,5);
   	if(iBack < 0)
   	{	
   	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_ENABLE);
//    	ErrOutPut(iBack,1);
    	return iBack;
   	}
	iBack = SetRtSaFFTWindow(bitdevHandle,4);
   	if(iBack < 0)
   	{	
   	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_ENABLE);
		return iBack;
   	}
	iBack = SetRtSaDetector(bitdevHandle, 0);
    if(iBack < 0)
    {
   	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_ENABLE);
       return iBack;
    }
    iBack = SetRtSaSpan(bitdevHandle,0);
    if(iBack < 0)
    {
   	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_ENABLE);
        return iBack;
    }		
	iBack = SetRtSaAcqTime(bitdevHandle,0.07);
   if(iBack < 0)
   {
   	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_ENABLE);
       return iBack;
   }  
//	iBack = DpxAmptAxisMin(bitdevHandle, sm_config_rsa_ctrl->dpxApmtMin);
//	printf("sm_config_rsa_ctrl->dpxApmtMin %0x\n",sm_config_rsa_ctrl->dpxApmtMin);
//    if(iBack < 0)
//    {
//       ErrOutPut(iBack,1);
//       return iBack;
//    }  
//	iBack = DpxAmptAxisZoom(bitdevHandle, sm_config_rsa_ctrl->dpxApmtZoom);
//	printf("sm_config_rsa_ctrl->dpxApmtZoom %0x\n",sm_config_rsa_ctrl->dpxApmtZoom);
//    if(iBack < 0)
//    {
//       ErrOutPut(iBack,1);
//       return iBack;
//    }  
            sm_config_rsa_ctrl->attenValue = 0;
            localConfigRsaCtrl.attenAuto = 1;
            iBack = PreAttenCtrl(bitdevHandle,0);

	iBack = DpxPersistenceTime(bitdevHandle,0);
   	if(iBack < 0)
   	{
   	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_ENABLE);
      	return iBack;
   	}  

	iBack = SetRtSaTrigger(bitdevHandle,1);
	   	if(iBack < 0)
   	{
   	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_ENABLE);
      	return iBack;
   	}  
	sm_config_rsa_ctrl->CenterFreq = 5050000000.0;
	sm_config_rsa_ctrl->TracePoint = 801;
	sm_config_rsa_ctrl->RefLevel = -10;
	sm_config_rsa_ctrl->attenAuto = 1;
	sm_config_rsa_ctrl->attenValue = 0;
	sm_config_rsa_ctrl->ischangeRbwitself = 0;
	sm_config_update->sweep_flag = IXS_CenterFreq;
	sm_config_update->top_flag = IXT_ConfigSweep;
		
		sm_startflag->startedflag = UPFLAG;	


		iBack = SetRtSaFpgaStart(bitdevHandle);
		if(iBack < 0)
	    {
//	    	printf("SetRtSaFpgaStart error!!!!\n");
	   	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
			ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_ENABLE);
	       return iBack;
	    }
    }
	else
	{
	iBack = SetRtSaRBW(bitdevHandle,sm_config_rsa_ctrl->RBW);
   	if(iBack < 0)
   	{	
   	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_ENABLE);
    	return iBack;
   	}
	iBack = SetRtSaFFTWindow(bitdevHandle,sm_config_rsa_ctrl->flitertype);
   	if(iBack < 0)
   	{	
   	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_ENABLE);
    	return iBack;
   	}
	iBack = SetRtSaDetector(bitdevHandle, sm_config_rsa_ctrl->DetectorMode);
    if(iBack < 0)
    {
   	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_ENABLE);
       return iBack;
    }
    iBack = SetRtSaSpan(bitdevHandle,sm_config_rsa_ctrl->SpanFreq);
    if(iBack < 0)
    {
   	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_ENABLE);
        return iBack;
    }		
	iBack = SetRtSaAcqTime(bitdevHandle,sm_config_rsa_ctrl->acqtimems);
   if(iBack < 0)
   {
   	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_ENABLE);
       return iBack;
   }  
	 
	iBack = DpxAmptAxisMin(bitdevHandle, sm_config_rsa_ctrl->dpxApmtMin);
//	printf("sm_config_rsa_ctrl->dpxApmtMin %0x\n",sm_config_rsa_ctrl->dpxApmtMin);
    if(iBack < 0)
    {
   	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_ENABLE);
       return iBack;
    }  
	iBack = DpxAmptAxisZoom(bitdevHandle, sm_config_rsa_ctrl->dpxApmtZoom);
//	printf("sm_config_rsa_ctrl->dpxApmtZoom %0x\n",sm_config_rsa_ctrl->dpxApmtZoom);
    if(iBack < 0)
    {
   	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_ENABLE);
       return iBack;
    }  
	iBack = DpxPersistenceTime(bitdevHandle,sm_config_rsa_ctrl->persistimeword);
   	if(iBack < 0)
   	{
   	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_ENABLE);
      	return iBack;
   	}  
	sm_config_rsa_ctrl->TracePoint = 801;
	iBack = SetDisplayNum(bitdevHandle,sm_config_rsa_ctrl->TracePoint);
	 if(iBack < 0)
   	{
   	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_ENABLE);
      	return iBack;
   	}  
	InitTriggerParam();
//	iBack = PreAmpliChannelCtrl(bitdevHandle,sm_config_rsa_ctrl->Preamp);
//	 if(iBack < 0)
//   	{
//    	ErrOutPut(iBack,1);
//      	return iBack;
//   	}  

//	iBack = PreAttenCtrl(bitdevHandle,sm_config_rsa_ctrl->attenValue);
//   if(iBack < 0)
//   {
//         ErrOutPut(iBack,1);
//         return iBack;
//   }  

//	sm_config_rsa_ctrl->RefLevel = -10;
//	sm_config_rsa_ctrl->attenAuto = 1;
//	sm_config_rsa_ctrl->attenValue = 0;
	
	sm_config_rsa_ctrl->ischangeRbwitself = 0;
   if(sm_config_rsa_ctrl->TriggerMode == 0x20)
   	{
		sm_config_update->sweep_flag = IXS_CenterFreq | IXS_RefLevel | IXS_Preamp | IXS_PersisTime | IXS_AcqTime | IXS_DPXAmptZoom | IXS_DPXAmptMin | IXS_Highest_Density|IXS_Curve|IXS_Fmt_Data;
   	}
	else
	{
		sm_config_update->sweep_flag = IXS_CenterFreq | IXS_RefLevel | IXS_Preamp | IXS_PersisTime | IXS_AcqTime | IXS_DPXAmptZoom | IXS_DPXAmptMin | IXS_Highest_Density|IXS_Curve;
	}
	sm_config_update->top_flag = IXT_ConfigSweep;
		
		}
  
	sm_sync->CtrlAppRunOk = 1;
//	iBack = SetRtSaIFBandWidth(bitdevHandle);
	return iBack;
}
