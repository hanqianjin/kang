#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include "ShmEngine.h"
#include "DiIoCtrl.h"
#include "RfVirtualDriver.h"
#include "SaAnalysis.h"
#include "SaDataStruct.h"
#include "MidMsg.h"
#include "DigSigDealVirtualDriver.h"
#include "sweepinterupt.h"
#include "sweepinterupt.h"
#include "time.h"
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
//by Johnson 1130
#define BIT_DOTNUM  801

#define THREAD_BY_TIME 10000 //for thread start one by one
extern _SM_SYNC syncMana;
extern PCONFIG_UPDATE sm_config_update;
extern PCONFIG_SWEEP sm_config_sweep;
extern PALL_NOTIC_CODE sm_notic_code;
//-----------------------------------------------
//global static obj
static struct timespec wtime;//test time
//-----------------------------------------------
//global obj
DiInt32 syncHandle = 0;//212
DiInt32 guiHandle = 0;

//0428
DiInt32 sweepHandle = 0;
//-----------------------------------------------
//static func
static DiInt32 WhileFunc(void);
static DiInt32 StartMultiWork(void);
static DiInt32 ObjIni(void);
static DiInt32 ProRelease(void* param);
static void ProduceResampleList();
//-----------------------------------------------
//global func
//DiSession rfHandle;
extern DiSession bitdevHandle;
//0426
extern _CONFIG_SWEEP localSweepConfig;
extern SWEEP_NUM sweepListinthread;

extern PCONFIG_MEASURE sm_config_measure;

//0810 steve
DiInt32 LangType = 0;
#define Len 128
static DiChar errBuffer[Len];	
void ErrOutPut(DiInt32 redirectFlag,DiInt32 writeShmFlag);

BSA_EXIT gappexit;
//0927 steve,for back recover
extern PSTART_FLAG sm_startflag;
#define UPFLAG  (37)
extern PSWEEP_DATA sm_sweep_data;


//1120 for insert
DiReal64 insertFuncDatas[8001];
DiReal64 inPI =  3.1415926535897932384626433832795028841971;


//*************Johnson 190718***********
//*********Freq count********
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <error.h>
#include <errno.h>

extern PSWEEP_DATA sm_sweep_data;
extern DiInt32 bMarkerFreqCountInterrupt;

static DiInt32 epfd,nfds;
static pthread_t g_thread;
static DiInt32 fd;

static DiInt32 freqCountHandle = -1;

static void* epoll_func(void *arg)
{
	DiInt32 i;
	struct epoll_event events[5];                   
	
	for(;;)
	{
		nfds = epoll_wait(epfd, events, 5, -1);
		for(i = 0; i < nfds; i++)
		{
			if(events[i].data.fd==fd)
			{
				if (events[i].events == EPOLLIN) {
					
					bMarkerFreqCountInterrupt = 1;
				}
			}            
		}
	}
}

DiInt32 init_freq(DiInt32 *handle)
{
	struct epoll_event ev,events[5];                   
	DiInt32 ret;

	fd = open("/dev/pl_freq", O_RDWR);
	if (fd < 0) {
		printf("freq cnt interrupt init fail\n");
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_FreqCntInterrupt_Init);
		ErrOutPut(REDIRECT_YES,WRSHM_YES);
		return -1;
	}

	epfd = epoll_create(1);                           
	ev.data.fd = fd;
	ev.events = EPOLLIN|EPOLLET;                     
	epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);

	ret = pthread_create(&g_thread, NULL, epoll_func, NULL);
	if (ret != 0)
	{
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_FreqCount_Thread_Init);
		ErrOutPut(REDIRECT_YES,WRSHM_YES);

		return -1; 
	}

	*handle = fd;
	return 0;
}

DiInt32 exit_freq(DiInt32 handle)
{
	DiInt32 ret;

	close(epfd);
	close(handle);
	ret = pthread_cancel(g_thread);
	if (ret != 0){
		return -1;
	}
	pthread_join(g_thread, NULL);
	return 0;

}

//=============================================


extern DiInt32 reCalcflag;
int main(int argc, char *argv[])
{	
    DiInt32 iBack = 0;
    //20190121 steve 
    setvbuf(stdout, (char *)NULL, _IONBF, 0);  //0713
	
#if DEBUG_OUTPUT
    time_t timep;
    time (&timep); 
    printf("SA CTRL APP START UP:%s",asctime(gmtime(&timep)));
#endif

    initNoticeCode(SA_MODU,CONTROL_PROGRAM);
    //shm done
    iBack = IniShmCtrl(NULL);
    if(iBack<0)
    {
	setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_Shm_Init);
	ErrOutPut(REDIRECT_YES,WRSHM_YES);
#if DEBUG_OUTPUT
	printf("shm init failed\n");
#endif
    }
    
    //open and ini dev
    iBack = ObjIni();
sm_config_sweep->uSweepCompleteFlag = 0;
    //ProduceResampleList();

    //load the calibrate data
    iBack = LoadCalibrateDatas();
    if(iBack < 0)
    {
	setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_CALCData_Load);
	ErrOutPut(REDIRECT_YES,WRSHM_YES);
#if DEBUG_OUTPUT
	printf("load calc datas failed\n");
#endif
    }
        

    //load multi threads(acq\listen seg sweep\get sys param)
    iBack = StartMultiWork();   

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
    iBack = SetSwpStop(bitdevHandle);
    if(iBack < 0)
    {
    	setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	ErrOutPut(REDIRECT_YES,WRSHM_YES);        
        return iBack;            
    } 
    ProRelease(NULL);
    FreeMemBuffer();

    //-----------delete freq_count interrupt-----
    if(freqCountHandle != -1) exit_freq(freqCountHandle);
    //-------------------------------------------
    return 0;
}

static DiInt32 WhileFunc(void)
{
    //while(syncMana.AppExit)
    while(gappexit.mainthreadExit)
	{
	    usleep(10000);
	}    
    return 0;
}

static DiInt32 ProRelease(void* param)
{	
    ClosePlInterrupt();
    return BitClose(bitdevHandle);
}
static void ProduceResampleList()
{
    //1123 steve  
    DiInt32 i = 0;
    DiInt32 oversamp = 1000;  
    DiInt32 influ = 8;  
    DiReal64 A = oversamp / inPI;
    DiReal64 B = inPI / oversamp;
    influ = influ * oversamp + 1;
    insertFuncDatas[0] = 1.0;
    for(i = 1;i < influ;i++)
    {
	insertFuncDatas[i] = A * sin(B * i) / i;
    }
    return;
}

DiSession handler = 0;
void *pAddr  = NULL;
extern DiInt32 intersource;//1 means zhudong occur interrupt,0 means finish sweeping then interrupt;
extern DiInt32 gwhole;
static DiInt32 ObjIni(void)
{	
    reCalcflag = 1;
    //0925
    gappexit.acqthreadExit = 1;
    gappexit.listenthreadExit = 1;
    gappexit.mainthreadExit = 1;
    gappexit.midmsgthreadExit = 1;

    
    //0426,ini value to local obj
    localSweepConfig.TracePoint = BIT_DOTNUM;

    localSweepConfig.checkinsert = sm_config_sweep->checkinsert;

 sm_config_sweep->FirstStart = 1;
    DiInt32 iBack  = 0;

    iBack = BitOpen("/dev/pl-mem",&bitdevHandle);
    if(iBack < 0)
        {
	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_MemMap_Init);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);

#if DEBUG_OUTPUT
            printf("mem map ini failed\n");
#endif
            return iBack;
        }

    iBack = OpenPlInterrupt();
    if(iBack < 0)
        {
            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_Sweepinterrupt_Init);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
#if DEBUG_OUTPUT
            printf("interrupt ini failed\n");
#endif
            return iBack;
        }  
    //this part for ini ctrl 0412
    iBack = SetDotSwpTime(bitdevHandle,2);
    if(iBack < 0)
        {
            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
            return iBack;
        }   

    iBack = SetFirRbwvbwDelayTime(bitdevHandle,2000);
    if(iBack < 0)
        {
            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
            return iBack;
        }

    iBack = SetDisplayNum(bitdevHandle,BIT_DOTNUM);
    if(iBack < 0)
        {
            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
            return iBack;
        }

//    //the seg last part stay time
    iBack = SetFirLoStaytime(bitdevHandle,2);
    if(iBack < 0)
        {
            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
            return iBack;
        }

    iBack = SetBucketTrigDelayTime(bitdevHandle,0.5);
    if(iBack < 0)
        {
            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
            return iBack;
        }    
//     
//    //Johnson 0425
    iBack = SetIfAtten(bitdevHandle);   
    if(iBack < 0)
        {
            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
            return iBack;
        }  
    iBack = InterMDFreqModeCtrl(bitdevHandle,0);
    if(iBack < 0)
        {
            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
            return iBack;
        } 

   //means 0
    if(sm_startflag->startedflag != UPFLAG)
    {
	sm_startflag->startedflag = UPFLAG;	
    }
    else
	{
		/*iBack =PreAttenCtrl(bitdevHandle,sm_config_sweep->attenValue);
		if(iBack < 0)
		{
		    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
		    return iBack;
		}  

		iBack = PreAmpliChannelCtrl(bitdevHandle,sm_config_sweep->Preamp);
		if(iBack < 0)
		{
		    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
		    return iBack;
		}    
		  
		iBack =SetDetectorDirectFlag(bitdevHandle,sm_config_sweep->checkswitch);
		if(iBack < 0)
		{
		    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
		    return iBack;
		} 
		iBack = SetDetectormode(bitdevHandle,sm_config_sweep->DetectorMode);
		if(iBack < 0)
		{
		    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
		    return iBack;
		} 
		iBack = InterMDFreqModeCtrl(bitdevHandle,sm_config_sweep->uIFMode);
		if(iBack < 0)
		{
		    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
		    return iBack;
		}*/
		localSweepConfig.RefLevel = sm_config_sweep->RefLevel;
		localSweepConfig.attenValue = sm_config_sweep->attenValue;
	    	iBack =PreAttenCtrl(bitdevHandle,sm_config_sweep->attenValue);
		if(iBack < 0)
		{
		    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
		    return iBack;
		}  

		localSweepConfig.Preamp = sm_config_sweep->Preamp;
		iBack = PreAmpliChannelCtrl(bitdevHandle,sm_config_sweep->Preamp);
		if(iBack < 0)
		{
		    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
		    return iBack;
		}    
//		  
		localSweepConfig.checkswitch = sm_config_sweep->checkswitch;
		iBack =SetDetectorDirectFlag(bitdevHandle,sm_config_sweep->checkswitch);
		if(iBack < 0)
		{
		    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
		    return iBack;
		} 

		localSweepConfig.DetectorMode = sm_config_sweep->DetectorMode;
		iBack = SetDetectormode(bitdevHandle,localSweepConfig.DetectorMode);
		if(iBack < 0)
		{
		    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
		    return iBack;
		}

		iBack = InterMDFreqModeCtrl(bitdevHandle,sm_config_sweep->uIFMode);
		if(iBack < 0)
		{
		    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
		    return iBack;
		}


//		//Johnson 190709
		iBack = SetTriggerMode(bitdevHandle,sm_config_sweep->TriggerMode);
		if(iBack < 0)
		{
		    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
		    return iBack;
		}
		switch(sm_config_sweep->TriggerMode)
		{
			case 0://Free Run
			case 5://GPS
			break;
			case 1://External
				iBack = SetTriggerDirect(bitdevHandle,sm_config_sweep->TriggerDirect);
				if(iBack < 0)
				{
				    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    			    ErrOutPut(REDIRECT_YES,WRSHM_YES);
				    return iBack;
				}

				iBack = SetTriggerDelayTime(bitdevHandle,sm_config_sweep->TriggerDelayTime);
				if(iBack < 0)
				{
				    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
				    return iBack;
				}
			break;
			case 2://Vedio
				iBack = SetTriggerDirect(bitdevHandle,sm_config_sweep->TriggerDirect);
				if(iBack < 0)
				{
				    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
				    return iBack;
				}

				iBack = SetTriggerDelayTime(bitdevHandle,sm_config_sweep->TriggerDelayTime);
				if(iBack < 0)
				{
				    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
				    return iBack;
				}

				iBack = SetVedioTriggerAmp(bitdevHandle,sm_config_sweep->VedioTriggerAmp);
				if(iBack < 0)
				{
				    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
				    return iBack;
				}
			break;
			case 3://Periodic time
				iBack = SetTriggerPerTime(bitdevHandle,sm_config_sweep->TriggerPerTime);
				printf("sm_config_sweep->TriggerPerTime.......%lf\n",sm_config_sweep->TriggerPerTime);
				if(iBack < 0)
				{
				    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
				    return iBack;
				}

				iBack = SetTriggerDelayTime(bitdevHandle,sm_config_sweep->TriggerDelayTime);
				if(iBack < 0)
				{
				    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
				    return iBack;
				}
			break;
			case 4://RF Burst
				iBack = SetTriggerDirect(bitdevHandle,sm_config_sweep->TriggerDirect);
				if(iBack < 0)
				{
				    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
				    return iBack;
				}

				iBack = SetTriggerDelayTime(bitdevHandle,sm_config_sweep->TriggerDelayTime);
				if(iBack < 0)
				{
				    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
				    return iBack;
				}

				iBack = SetRFBurstTriggerAmp(bitdevHandle,sm_config_sweep->RFBurstTriggerAmp);
				if(iBack < 0)
				{
				    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
				    return iBack;
				}
			break;
			default: break;
		}

		if(sm_config_measure->MeasureMode != 0)
		{
			iBack = SetDoorControlSwitch(bitdevHandle,0);
			if(iBack < 0)
			{
			    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
			    return iBack;
			}
		}

		if(sm_config_sweep->DrCtrlSource != -1)
		{
			iBack = SetDoorControlSourceSelect(bitdevHandle,sm_config_sweep->DrCtrlSource);
			if(iBack < 0)
			{
			    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
			    return iBack;
			}

			iBack = SetLevelEdgeSelect(bitdevHandle,sm_config_sweep->LvlEdgSelect);
			if(iBack < 0)
			{
			    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
			    return iBack;
			}

			iBack = SetLevelEdgeMode(bitdevHandle,sm_config_sweep->LvlEdgMode);
			if(iBack < 0)
			{
			    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
			    return iBack;
			}

			iBack = SetDoorControlSweepModeSelect(bitdevHandle,sm_config_sweep->DrCtrlSweepMode);
			if(iBack < 0)
			{
			    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
			    return iBack;
			}

			iBack = SetDoorControlSwitch(bitdevHandle,sm_config_sweep->DrCtrlSwitch);
			if(iBack < 0)
			{
			    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
			    return iBack;
			}

			if(sm_config_sweep->DrCtrlSource == 2)
			{
				iBack = SetPrdTrgSynchroSrcSelect(bitdevHandle,sm_config_sweep->PrdTrgSynchroSrc);
				if(iBack < 0)
				{
				    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
				    return iBack;
				}

				iBack = SetPrdTrgPeriod(bitdevHandle,sm_config_sweep->PrdTrgPeriod);
				if(iBack < 0)
				{
				    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
				    return iBack;
				}

				iBack = SetPrdTrgSrcDelay(bitdevHandle,sm_config_sweep->PrdTrgSrcDelay);
				if(iBack < 0)
				{
				    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
				    return iBack;
				}

				iBack = SetPrdTrigPrvntStatus(bitdevHandle,sm_config_sweep->PrdTrigPrvntStatus);
				if(iBack < 0)
				{
				    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
				    return iBack;
				}

				iBack = SetPrdTrigPrvntTimes(bitdevHandle,sm_config_sweep->PrdTrigPrvntTimes);
				if(iBack < 0)
				{
				    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
				    return iBack;
				}
			}
			else if(sm_config_sweep->DrCtrlSource == 1)
			{
				iBack = SetRFBurstTrigLevel(bitdevHandle,sm_config_sweep->RFBurstTrigLevel);
				if(iBack < 0)
				{
				    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
				    return iBack;
				}
			}
			if(sm_config_sweep->LvlEdgSelect == 0)
			{
				iBack = SetEdgTrigDely(bitdevHandle,sm_config_sweep->EdgTrigDely);
				if(iBack < 0)
				{
				    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
				    return iBack;
				}

				iBack = SetEdgTrigDoorWdth(bitdevHandle,sm_config_sweep->EdgTrigDoorWdth);
				if(iBack < 0)
				{
				    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
				    return iBack;
				}

				iBack = SetEdgTrigPrvntStatus(bitdevHandle,sm_config_sweep->EdgTrigPrvntStatus);
				if(iBack < 0)
				{
				    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
				    return iBack;
				}

				iBack = SetEdgTrigPrvntTimes(bitdevHandle,sm_config_sweep->EdgTrigPrvntTimes);
				if(iBack < 0)
				{
				    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
				    return iBack;
				}
			}
		}
//	
		iBack = ZeroRestrainPhaseCtrl(bitdevHandle,sm_config_sweep->dZeroRestrainPhase);
		if(iBack < 0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
			ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return iBack;
		}

		iBack = ZeroRestrainAttenCtrl(bitdevHandle,sm_config_sweep->dZeroRestrainAtten);
		if(iBack < 0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
			ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return iBack;
		}

		sm_config_sweep->ischangeRbwitself = 0;
		sm_config_update->sweep_flag = IXS_RBW | IXS_VBW | IXS_SpanMode;
		sm_config_update->top_flag = IXT_ConfigSweep;
	}    

    //212
    if((syncHandle = semget(SYNC_KEY,1,IPC_CREAT | 0660))<0)
        {
	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_Sm_syncHandle_Create);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
        }

    if(semctl(syncHandle,0,SETVAL,1) < 0)
        {
	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_Sm_syncHandle_Init);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
        }

    if((guiHandle = semget(SYNC_KEY_GUI,1,IPC_CREAT | 0660))<0)
        {
	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_Sm_guiHandle_Create);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
        }

    if(semctl(guiHandle,0,SETVAL,1) < 0)
        {
	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_Sm_guiHandle_Init);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
        }

    if((sweepHandle = semget(SYNC_SWEEP,1,IPC_CREAT | 0660))<0)
        {
	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_Sm_sweepHandle_Create);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);

        }

    if(semctl(sweepHandle,0,SETVAL,0) < 0)
        {
	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_Sm_sweepHandle_Init);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
        }


    pmid_msg_thread	 = &mid_msg_thread;
    pmid_msg_thread->func = MidMsgFunc;

    presweep_interrupt_thread = &resweep_interrupt_thread;
    presweep_interrupt_thread->func = ListenAndDownSweepParamFunc;

    pacquire_data_thread = &acquire_data_thread;
    pacquire_data_thread->func = AcqDataFunc;

    //------------init fre_count interrupt------
    init_freq(&freqCountHandle);
    //------------------------------------------
    return 0;
}

static DiInt32 StartMultiWork(void)
{
    //mid msg listen thread
    DiInt32 iBack = pthread_create(&pmid_msg_thread->threadId,NULL,pmid_msg_thread->func,NULL);
    if(iBack < 0)
        {
	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_MidMsg_Thread_Init);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);

#if DEBUG_OUTPUT
            perror("mid msg thread create fail");
#endif
        }

    usleep(THREAD_BY_TIME);

    iBack = pthread_create(&presweep_interrupt_thread->threadId,NULL,presweep_interrupt_thread->func,NULL);
    if(iBack < 0)
        {
	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_Sweep_Thread_Init);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);

#if DEBUG_OUTPUT
            perror("listen interrupt thread create fail");
#endif
        }

    usleep(THREAD_BY_TIME);
    iBack = pthread_create(&pacquire_data_thread->threadId,NULL,pacquire_data_thread->func,NULL);
    if(iBack < 0)
        {
	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_DataAcq_Thread_Init);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);

#if DEBUG_OUTPUT
            perror("data acq thread create fail");
#endif
        }
    return iBack;
}

//Johnson 191025
void ErrOutPut(DiInt32 redirectFlag,DiInt32 writeShmFlag)
{
    static DiUInt32 redirectCounter = 1;

    DiUInt32 noticeCode = GetNoticeCode();

    if(!!redirectFlag)
    {
	//printf("The %uth notice message code is 0x%x\n ",redirectCounter++,noticeCode);
    }

    if(!!writeShmFlag)
    {
	sm_notic_code->noticode = noticeCode;
    }
    return;
}
