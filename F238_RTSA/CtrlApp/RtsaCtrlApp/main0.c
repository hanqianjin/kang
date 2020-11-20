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
extern PCONFIG_SWEEP sm_config_sweep;
//-----------------------------------------------
//global static obj
static struct timespec wtime;//test time
//-----------------------------------------------
//global obj
DiInt32 syncHandle = 0;//212
DiInt32 guiHandle = 0;
//-----------------------------------------------
//static func
static DiInt32 WhileFunc(void);
static DiInt32 StartMultiWork(void);
static DiInt32 ObjIni(void);
static DiInt32 ProRelease(void* param);
//-----------------------------------------------
//global func
//DiSession rfHandle;
extern DiSession bitdevHandle;
int main(int argc, char *argv[])
{	
	DiInt32 iBack = 0;
	//open and ini dev
	iBack = ObjIni();
	//printf("obj ini is %d\n",iBack);

	//shm done	
	iBack = IniShmCtrl(NULL);
	printf("share mem state is %d\n",iBack);	
	//load the calibrate data
	sm_config_sweep->TracePoint = 1001;
	//load multi threads(acq\listen seg sweep\get sys param)
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
	//do while for forbidding the app exit
	WhileFunc();	
	char ch = ' ';
	DiInt32 msgnum = 0;
	while(syncMana.AppExit && (ch = getchar()))
	{
		switch(ch)
		{
			case 'a':
				scanf("%d",&msgnum);
				sm_config_update->sweep_flag = msgnum;
				sm_config_update->top_flag = 1;
				break;
			case 'b':
				scanf("%d",&msgnum);
				sm_config_update->measure_flag = msgnum;
				sm_config_update->top_flag = 2;
				break;
			case 'c':
				scanf("%d",&msgnum);
				sm_config_update->system_flag = msgnum;
				sm_config_update->top_flag = 4;
				break;
			case 'q':	
				syncMana.AppExit = 0;
				break;							
		}		
	};
	
	sleep(1);
	printf("over over!\n");
	ProRelease(NULL);	
	return 0;
}

DiInt32 WhileFunc(void)
{
	while(syncMana.AppExit)
	{
		sleep(1);
	}
	return 0;
}

static DiInt32 ProRelease(void* param)
{	
	return BitClose(bitdevHandle);
}

static DiInt32 ObjIni(void)
{	
	

	//0412
	DiInt32 iBack = BitOpen("/dev/mem",&bitdevHandle);
	if(iBack < 0)
	{
		printf("mem map ini failed\n");
		return iBack;
	}

#if 0
	iBack = SetSwpStop(bitdevHandle);
	{
		if(iBack < 0)
		{
			printf("SetSwpStop failed\n");
			return iBack;
		}
	}
#endif

	//this part for ini ctrl 0412
	iBack = SetDotSwpTime(bitdevHandle,2);
	if(iBack < 0)
	{
		printf("SetDotSwpTime failed\n");
		return iBack;
	}

	iBack = SetFirBucketTime(bitdevHandle,2);
	if(iBack < 0)
	{
		printf("SetFirBucketTime failed\n");
		return iBack;
	}

	iBack = SetDetectormode(bitdevHandle,3);
	if(iBack < 0)
	{
		printf("SetDetectormode failed\n");
		return iBack;
	}

	iBack = SetDataProcMode(bitdevHandle,0);	
	if(iBack < 0)
	{
		printf("SetDataProcMode failed\n");
		return iBack;
	}

	iBack = SetFirRbwvbwDelayTime(bitdevHandle,10);
	if(iBack < 0)
	{
		printf("SetFirRbwvbwDelayTime failed\n");
		return iBack;
	}

	iBack = SetDisplayNum(bitdevHandle,501);
	if(iBack < 0)
	{
		printf("SetDisplayNum failed\n");
		return iBack;
	}

	iBack = SetBucketTrigTime(bitdevHandle,1);
	if(iBack < 0)
	{
		printf("SetBucketTrigTime failed\n");
		return iBack;
	}

	iBack = SetTrigType(bitdevHandle,0);
	if(iBack < 0)
	{
		printf("SetTrigType failed\n");
		return iBack;
	}

	iBack = SetZeroSpan(bitdevHandle,0);
	if(iBack < 0)
	{
		printf("SetZeroSpan failed\n");
		return iBack;
	}

	iBack = SetRbw(bitdevHandle,5000000);
	if(iBack < 0)
	{
		printf("SetRbw failed\n");
		return iBack;
	}

	iBack = SetVbw(bitdevHandle,3000000);
	if(iBack < 0)
	{
		printf("SetVbw failed\n");
		return iBack;
	}

	////////
#if 0
	iBack = SetFirLoFreq(bitdevHandle,0x47c1c7,0x1c71c71c);
	if(iBack < 0)
	{
		printf("SetFirLoFreq failed\n");
		return iBack;
	}
			//the lo step
	iBack = SetFirLoStepFreq(bitdevHandle,0x16c16c16, 0x16c); 
	if(iBack < 0)
	{
		printf("SetFirLoStepFreq failed\n");
		return iBack;
	}
			//the seg last part stay time
	iBack = SetFirLoStaytime(bitdevHandle,0x0000061A); 
	if(iBack < 0)
	{
		printf("SetFirLoStaytime failed\n");
		return iBack;
	}
	iBack = SetSegPoint(bitdevHandle,4000);
	if(iBack < 0)
	{
		printf("SetSegPoint failed\n");
		return iBack;
	}
	iBack = SetSwpRun(bitdevHandle); 
	if(iBack < 0)
	{
		printf("SetSwpRun failed\n");
		return iBack;
	}

#endif

	//212
	if((syncHandle = semget(SYNC_KEY,1,IPC_CREAT | 0660))<0)
   	{
     		printf("semget errno,%d:%s",errno,strerror(errno));
	}	
   
   	if(semctl(syncHandle,0,SETVAL,1) < 0)
   	{
     		printf("init error,%d:%s",errno,strerror(errno));
   	}

	if((guiHandle = semget(SYNC_KEY_GUI,1,IPC_CREAT | 0660))<0)
   	{
     		printf("semget errno,%d:%s",errno,strerror(errno));
	}	
   
   	if(semctl(guiHandle,0,SETVAL,1) < 0)
   	{
     		printf("init error,%d:%s",errno,strerror(errno));
   	}
	

	pmid_msg_thread	 = &mid_msg_thread;
	pmid_msg_thread->func = MidMsgFunc;

	presweep_interrupt_thread = &resweep_interrupt_thread;
	presweep_interrupt_thread->func = ListenAndDownSweepParamFunc;

	pacquire_data_thread = &acquire_data_thread;
	pacquire_data_thread->func = AcqDataFunc;
	return 0;
}

static DiInt32 StartMultiWork(void)
{
	//mid msg listen thread
	DiInt32 iBack = pthread_create(&pmid_msg_thread->threadId,NULL,pmid_msg_thread->func,NULL);
	if(iBack < 0)
	{
		perror("mid msg thread create fail");
	}	
	
	usleep(THREAD_BY_TIME);	
	
	iBack = pthread_create(&presweep_interrupt_thread->threadId,NULL,presweep_interrupt_thread->func,NULL);
	if(iBack < 0)
	{
		perror("listen interrupt thread create fail");
	}

	usleep(THREAD_BY_TIME);	
	iBack = pthread_create(&pacquire_data_thread->threadId,NULL,pacquire_data_thread->func,NULL);
	if(iBack < 0)
	{
		perror("data acq thread create fail");
	}
	return iBack;	
}

