#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
//#include "DiIoCtrl.h"
#include "MainBoardVirtualDriver.h"
#include "RfVirtualDriver.h"
#include "SaAnalysis.h"
#include "SaDataStruct.h"
#include "MidMsg.h"
#include "DigSigDealVirtualDriver.h"

//---------------------------------------------
//self data types
typedef struct bit_mechanism
{
	sem_t prosem;
	sem_t showsem;
	pthread_mutex_t lockobj;
	DiInt32 acqflag;
	DiInt32 showflag;
	pthread_t acqTId;
	pthread_t showTId;
	DiReal64 dataBuffer[202];
}MECH_OBJ,*PMECH_OBJ;

//-----------------------------------------------
//global static obj
static MECH_OBJ gmech;
static struct timespec wtime;
//-----------------------------------------------
//global obj
//global obj
DiInt32 syncHandle = 0;//212
DiInt32 guiHandle = 0;
//-----------------------------------------------
//static func
static DiInt32 StartWork(void);
static DiInt32 ObjIni(void);
static DiInt32 ProRelease(void* param);
//-----------------------------------------------
//global func
void* AcqFunc(void* param);
void* ShowFunc(void* param);
static DiInt32 runflag = 0;
DiSession rfHandle;
int main(void)
{ 
	DiInt32 iBack = 0;
	iBack = BitOpen("/dev/mem",&rfHandle);
	if(iBack < 0)
	{
		printf("get the devhandle failed");		
		return iBack;
	}
	printf("get the devhandle success\n");
	ObjIni(); 
	char ch = ' ';
	DiReal64 dparam[10];
	DiUInt32 uiparam[10];
	while(runflag && (ch = getchar()))
	{
		switch(ch)
		{
			case 'A':
				RfIni(rfHandle);
				printf("the RF has ini\n");
				printf("wait input...\n"); 
				break;
			case 'a':
				scanf("%lf",&dparam[0]);
				RfChannelChoose(rfHandle,dparam[0]);
				printf("RfChannelChoose\n");
				printf("wait input...\n"); 
				break;
			case 'b':
				scanf("%lf",&dparam[0]);
				ZeroRestrainPhaseCtrl(rfHandle,dparam[0]);  
				printf("ZeroRestrainPhaseCtrl\n");
				printf("wait input...\n");
				break;
			case 'c':
				scanf("%u",&uiparam[0]);       
				ZeroRestrainAttenCtrl(rfHandle,uiparam[0]);
				printf("ZeroRestrainAttenCtrl\n");
				printf("wait input...\n");
				break;
			case 'd':
				scanf("%lf",&dparam[0]);
				SecIfAttenCtrl(rfHandle,dparam[0]);  
				printf("SecIfAttenCtrl\n");
				printf("wait input...\n");
				break;
			case 'e':
				scanf("%lf",&dparam[0]);
				MicroFreqPreAttenCtrl(rfHandle,dparam[0]);  
				printf("MicroFreqPreAttenCtrl\n"); 
				printf("wait input...\n");
				break;
			case 'f':
				scanf("%u",&uiparam[0]);       
				MicroFreqPreAmpliChannelCtrl(rfHandle,uiparam[0]);
				printf("MicroFreqPreAmpliChannelCtrl\n");
				printf("wait input...\n");
				break;
			case 'g':
				scanf("%lf",&dparam[0]);
				HighFreqPreAttenCtrl(rfHandle,dparam[0]);  
				printf("HighFreqPreAttenCtrl\n"); 
				printf("wait input...\n");
				break;
			case 'h':
				scanf("%u",&uiparam[0]);       
				HighFreqPreAmpliChannelCtrl(rfHandle,uiparam[0]);
				printf("HighFreqPreAmpliChannelCtrl\n");
				printf("wait input...\n");
				break;
			case 'i':
				scanf("%lf",&dparam[0]);
				LowFreqPreAttenCtrl(rfHandle,dparam[0]);  
				printf("LowFreqPreAttenCtrl\n"); 
				printf("wait input...\n");
				break;
			case 'j':
				scanf("%u",&uiparam[0]);       
				LowFreqPreAmpliChannelCtrl(rfHandle,uiparam[0]);
				printf("LowFreqPreAmpliChannelCtrl\n");
				printf("wait input...\n");
				break;
			case 'k':
				scanf("%lf",&dparam[0]);
				SecLoOutfreqCtrl(rfHandle,dparam[0]);  
				printf("SecLoOutfreqCtrl\n");
				printf("wait input...\n");
				break;
			case 'l':
				scanf("%u",&uiparam[0]);       
				InOutRefCtrl(rfHandle,uiparam[0]);
				printf("InOutRefCtrl\n");
				printf("wait input...\n");
				break;
			case 'm':
				printf("wait input...\n");
				break;
			case 'n':
				scanf("%lf",&dparam[0]);
				SetOsciVolt(rfHandle,dparam[0]);  
				printf("SetOsciVolt\n"); 
				printf("wait input...\n");
				break;
			case 'o':  
				scanf("%lf",&dparam[0]);
				IFGainCtrl(rfHandle,dparam[0]);  
				printf("IFGainCtrl\n"); 
				printf("wait input...\n");
				break;
			case 'p':
				printf("wait input...\n");
				break;
			case 'r':
				scanf("%lf",&dparam[0]);
				SetRbw(rfHandle,dparam[0]);  
				printf("SetRbw\n");
				printf("wait input...\n");
				break;
			case 's':
				scanf("%lf",&dparam[0]);
				SetVbw(rfHandle,dparam[0]);  
				printf("SetVbw\n");
				printf("wait input...\n");
				break;
			case 't': 
				scanf("%u",&uiparam[0]);       
				SetDetectormode(rfHandle,uiparam[0]);
				printf("SetDetectormode\n");
				printf("wait input...\n");
				break;
			case 'u': 
				scanf("%u",&uiparam[0]);       
				SetDataProcMode(rfHandle,uiparam[0]);
				printf("SetDataProcMode\n");
				printf("wait input...\n");
				break;
			case 'v': 
				scanf("%u",&uiparam[0]);       
				SetZeroSpan(rfHandle,uiparam[0]);
				printf("SetZeroSpan\n");
				printf("wait input...\n");
				break;
			case 'w':   
				scanf("%u",&uiparam[0]);       
				SetDotSwpTime(rfHandle,uiparam[0]);
				printf("SetDotSwpTime\n");
				printf("wait input...\n");
				break;
			case 'x':
				scanf("%u",&uiparam[0]); 
				scanf("%u",&uiparam[1]);
				SetTotalSwpTimeLow(rfHandle,uiparam[0]);
				printf("SetTotalSwpTimeLow\n");
				SetTotalSwpTimeHigh(rfHandle,uiparam[0]);
				printf("SetTotalSwpTimeHigh\n");
				printf("wait input...\n");
				break;
			case 'y':
				scanf("%u",&uiparam[0]);
				SetCheckSegNum(rfHandle,uiparam[0]);  
				printf("SetCheckSegNum\n"); 
				printf("wait input...\n");
				break;
			case 'z':
				scanf("%u",&uiparam[0]);       
				SetDisplayNum(rfHandle,uiparam[0]);
				printf("SetDisplayNum\n");
				printf("wait input...\n");
				break;
			case 'B':  
				scanf("%u",&uiparam[0]);       
				DataBufferClear(rfHandle,uiparam[0]);
				printf("DataBufferClear\n");
				printf("wait input...\n");
				break;
			case 'C':	 
				scanf("%u",&uiparam[0]);       
				SetFftBucketNum(rfHandle,uiparam[0]);
				printf("SetFftBucketNum\n");
				printf("wait input...\n");
				break;
			case 'D': 
				scanf("%u",&uiparam[0]);       
				SetAudioTime(rfHandle,uiparam[0]);
				printf("SetAudioTime\n");
				printf("wait input...\n");
				break;
			case 'E':
				scanf("%u",&uiparam[0]);       
				SetAudioVolume(rfHandle,uiparam[0]);
				printf("SetAudioVolume\n");
				printf("wait input...\n");
				break;
			case 'F':	   
				scanf("%u",&uiparam[0]);       
				SetAudioType(rfHandle,uiparam[0]);
				printf("SetAudioType\n");
				printf("wait input...\n");
				break;
			case 'G': 
				scanf("%u",&uiparam[0]);       
				SetAudioEn(rfHandle,uiparam[0]);
				printf("SetAudioEn\n");
				printf("wait input...\n");
				break;
			case 'H': 
				scanf("%u",&uiparam[0]);       
				SetFftCalcNum(rfHandle,uiparam[0]);
				printf("SetFftCalcNum\n");
				printf("wait input...\n");
				break;
			case 'I':
				scanf("%u",&uiparam[0]);       
				SetFftCalcDirection(rfHandle,uiparam[0]);
				printf("SetFftCalcDirection\n");
				printf("wait input...\n");
				break;
			case 'J':  
				scanf("%u",&uiparam[0]);       
				SetFftValidStartNum(rfHandle,uiparam[0]);
				printf("SetFftValidStartNum\n");
				printf("wait input...\n");
				break;
			case 'K': 
				scanf("%u",&uiparam[0]);       
				SetFftValidEndNum(rfHandle,uiparam[0]);
				printf("SetFftValidEndNum\n");
				printf("wait input...\n");
				break;
			case 'L': 
				scanf("%u",&uiparam[0]);       
				SetFftDotSwpTime(rfHandle,uiparam[0]);
				printf("SetFftDotSwpTime\n");
				printf("wait input...\n");  
				break;
			case 'M':  
				scanf("%u",&uiparam[0]);       
				SetBucketTrigTime(rfHandle,uiparam[0]);
				printf("SetBucketTrigTime\n");
				printf("wait input...\n"); 
				break;
			case 'N':
				scanf("%u",&uiparam[0]);       
				SetRbwvbwDelayTime(rfHandle,uiparam[0]);
				printf("SetRbwvbwDelayTime\n");
				printf("wait input...\n"); 
				break;
			case 'O': 
				scanf("%u",&uiparam[0]);       
				SetTrigType(rfHandle,uiparam[0]);
				printf("SetTrigType\n");
				printf("wait input...\n");
				break;
			case 'P':
				scanf("%u",&uiparam[0]);       
				SetTrigDirect(rfHandle,uiparam[0]);
				printf("SetTrigDirect\n");
				printf("wait input...\n");
				break;
			case 'R': 
				scanf("%u",&uiparam[0]);       
				SetTrigDelayTime(rfHandle,uiparam[0]);
				printf("SetTrigDelayTime\n");
				printf("wait input...\n");
				break;
			case 'S':
				scanf("%u",&uiparam[0]);       
				SetTrigLevel(rfHandle,uiparam[0]);
				printf("SetTrigLevel\n");
				printf("wait input...\n");
				break;
			case 'T': 
				scanf("%lf",&dparam[0]);       
				FirstLoFreqCtrl(rfHandle,dparam[0]);
				printf("FirstLoFreqCtrl\n");
				printf("wait input...\n");
				break;
			case 'U':
				scanf("%u",&uiparam[0]); 
				scanf("%u",&uiparam[1]); 
				SetFirLoStepFreq(rfHandle,uiparam[0],uiparam[1]);
				printf("SetFirLoStepFreq\n");
				printf("wait input...\n");
				break;
			case 'V':
				scanf("%u",&uiparam[0]); 
				SetFirLoStaytime(rfHandle,uiparam[0]);
				printf("SetFirLoStaytime\n");
				printf("wait input...\n"); 
				break;
			case 'W':
				scanf("%u",&uiparam[0]); 
				SetSegPoint(rfHandle,uiparam[0]);
				printf("SetSegPoint\n");
				printf("wait input...\n");
				break;
			case 'X':
				SetSwpStop(rfHandle);
				printf("SetswpStop\n");
				printf("wait input...\n");
				break;
			case 'Y':
				SetSwpRun(rfHandle);
				printf("SetswpRun\n");
				printf("wait input...\n");
				break;
			case 'Z':
				printf("\n");
				break;
			case '1':
				printf("\n");
				break;
			case '2':
				printf("\n");
				break;
			case '3':
				printf("\n");
				break;
			case '4':
				printf("\n");
				break;
			case '5':
				printf("\n");
				break;
			case '6':
				printf("\n");
				break;
			case '7':
				printf("\n");
				break;
			case '8':
				printf("\n");
				break;
			case '9':
				printf("\n");
				break;
			case '0':
				printf("\n");
				break;
			case 'q':
				ProRelease(NULL);
				break; 
		}
	};
	BitClose(rfHandle);
	printf("the test is over!\n");

	return 0;
}

static DiInt32 ProRelease(void* param)
{
	runflag = 0;
	return 0;
}

static DiInt32 ObjIni(void)
{	
	runflag = 1;
	return 0;
}

static DiInt32 StartWork(void)
{
	pthread_create(&gmech.acqTId,NULL,AcqFunc,NULL);
	pthread_create(&gmech.showTId,NULL,ShowFunc,NULL);
	return 0;
}

static DiInt32 acqTimes = 0;
static DiInt32 showTimes = 0;
void* AcqFunc(void* param)
{
	printf("the acq thread has run\n");
	int i = 0;
	while(gmech.acqflag)
	{
		pthread_mutex_lock(&gmech.lockobj);
	//	printf("A:the %d times show has over,to acq...\n",showTimes);
		
		for(i = 0;i < 202;i++)			
		{
			gmech.dataBuffer[i] = cos(2*3.1415926*0.1);
		}
		acqTimes++;
		pthread_mutex_unlock(&gmech.lockobj);	
		usleep(10000);
	};
	printf("the acq thread is over\n");
	sem_post(&gmech.prosem);
	return NULL;
}

void* ShowFunc(void* param)
{
	printf("the show thread has run\n");
	while(gmech.showflag)
	{
		pthread_mutex_lock(&gmech.lockobj);
	//	printf("B:the %d times acq has over,to show\n",acqTimes);
		memset(gmech.dataBuffer,37.0,sizeof(double) * 202);
		showTimes++;
		pthread_mutex_unlock(&gmech.lockobj);	
		usleep(10000);
	};
	printf("the show thread is over\n");
	sem_post(&gmech.showsem);
	return NULL;
}
