#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include "DiIoCtrl.h"
#include "MainBoardVirtualDriver.h"
#include "RfVirtualDriver.h"
#include "SaAnalysis.h"
#include "SaDataStruct.h"
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

//-----------------------------------------------
//static func
static DiInt32 StartWork(void);
static DiInt32 ObjIni(void);
static DiInt32 ProRelease(void* param);
//-----------------------------------------------
//global func
void* AcqFunc(void* param);
void* ShowFunc(void* param);
int main(void)
{
	ObjIni();
	
	char ch = ' ';
	while((gmech.acqflag || gmech.showflag) && (ch = getchar()))
	{
		switch(ch)
		{
			case 'a':
				break;
			case 'r':
				StartWork();
				break;
			case 's':
				ProRelease(NULL);
				break;
			default:
				if('\n' != ch)
				  printf("this is not a command\n");
		}		
	};
	
	printf("the main circle has finished\n");
	clock_gettime(CLOCK_REALTIME,&wtime);
	wtime.tv_sec += 10;
	printf("wait the time out...\n");
	sem_timedwait(&gmech.showsem,&wtime);
	printf("have received the show sig\n");
	clock_gettime(CLOCK_REALTIME,&wtime);
	wtime.tv_sec += 10;
	printf("wait the time out...\n");
	sem_timedwait(&gmech.prosem,&wtime);
	printf("have received the acq sig\n");
	sem_destroy(&gmech.prosem);
	sem_destroy(&gmech.showsem);
	return 0;
}

static DiInt32 ProRelease(void* param)
{
	gmech.acqflag = 0;
	gmech.showflag = 0;
	return 0;
}

static DiInt32 ObjIni(void)
{
	sem_init(&gmech.prosem,0,0);
	sem_init(&gmech.showsem,0,0);
	pthread_mutex_init(&gmech.lockobj,NULL);
	gmech.showflag = 1;
	gmech.acqflag = 1;
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
