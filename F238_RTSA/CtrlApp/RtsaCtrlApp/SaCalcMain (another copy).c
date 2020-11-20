#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "DiIoCtrl.h"
#include "MainBoardVirtualDriver.h"
#include "RfVirtualDriver.h"
#include "SaDataStruct.h"
#include "DigSigDealVirtualDriver.h"
#include <fcntl.h> 
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "CalcPointAlog.h"

#define BITMSGBUFFER 1024
#define PORT 5555
#define SYNC_SERVER   6000
#define SYNC_CLIENT   6001

static const double PER = 0.0000001; 

FILE *fp = NULL;

pthread_t threadId;
pthread_t connectId;
pthread_t syncthreadId;
static void* CalcFlatCtrl(void *functionData);
static void* MultiConncet(void* param);
static void* SyncFunc(void* param);

static int serverId = 0;
static int clientId = 0;
static char cbuffer[BITMSGBUFFER];
struct sockaddr_in svraddr = {0};
struct sockaddr_in clientaddr = {0};

static void GetSync(DiInt32 handle);
static void ReleaseSync(DiInt32 handle);

int synclistenHandle = 0;
int synccalcHandle = 0;

static FREQLIST bitFreqList;
static void GetLog(double* buffer,int isize);
static int GetMaxValue(double* buffer,int isize); 

int main(int argc, char *argv[])
{
	DiInt32 iBack = 0;

	if((synclistenHandle = semget(SYNC_SERVER,1,IPC_CREAT | 0660))<0)
   	{
     		printf("semget errno,%d:%s",errno,strerror(errno));
	}	
   
   	if(semctl(synclistenHandle,0,SETVAL,0) < 0)
   	{
     		printf("init error,%d:%s",errno,strerror(errno));
   	}

	if((synccalcHandle = semget(SYNC_CLIENT,1,IPC_CREAT | 0660))<0)
   	{
     		printf("semget errno,%d:%s",errno,strerror(errno));
	}	
   
   	if(semctl(synccalcHandle,0,SETVAL,0) < 0)
   	{
     		printf("init error,%d:%s",errno,strerror(errno));
   	}	

	char pPath[256] = {0};
    	getcwd(pPath, 256);
	strcat(pPath,"/SaFlatCalc.txt");
	fp = fopen(pPath,"w");

	memset(pPath,0,256);
	getcwd(pPath, 256);
	strcat(pPath,"/freqlist.txt");
	GetParamFromFile(pPath,&bitFreqList);  

	serverId = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(-1 == serverId)
	{
		perror("server create socket failed\n");
		return -1;
	}	
	  
   	svraddr.sin_family = AF_INET;
   	svraddr.sin_port = htons(PORT);
	svraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	bind(serverId,(struct sockaddr *)&svraddr,sizeof(svraddr));
	listen(serverId,SOMAXCONN);//noblock	

	//start calc thread
	iBack = pthread_create(&connectId,NULL,MultiConncet,NULL);
	if(iBack < 0)
	{
		perror("multi connect thread create fail");
		return iBack;
	}	

	int ialive = 1;
	char ch = ' ';	

	while(ialive && (ch = getchar()))
	{
		switch(ch)
		{
			case 'q':
			if(close(clientId) < 0)
				printf("client close falied\n");
			else
				printf("client close OK\n");
			if(close(serverId) < 0)
				printf("server close failed\n");
			else
				printf("server close OK\n");
			ialive = 0;
			break;
		}	
	}	
	return 0;
}

static void* MultiConncet(void* param)
{
	int iBack = 0;
	while(1)
	{
		int clientaddrLen = sizeof(clientaddr);
		printf("wait for client...\n");
		clientId = accept(serverId,(struct sockaddr*)&clientaddr,&clientaddrLen);
		printf("have a client comes...\n");

		iBack = pthread_create(&syncthreadId,NULL,SyncFunc,NULL);
		if(iBack < 0)	
		{
			perror("sync thread create fail");
			return NULL;
		}

		//start calc thread
		iBack = pthread_create(&threadId,NULL,CalcFlatCtrl,NULL);
		if(iBack < 0)
		{
			perror("mid msg thread create fail");
			return NULL;
		}
	};
	return NULL;
}

#define LOWDOOR 7.5e9
#define HIGHDOOR 23.63375e9
double freqpoint = 100.0e6;//if gain calc 
double powerlistpoints[] = {10.0,5.0,0.0,-5.0,-10.0,-15.0,-20.0,-25.0,-30.0,-35.0}; 
double powerlistpointsampoff[] = {10.0,5.0,0.0,-5.0,-10.0,-15.0,-20.0}; 

static void* CalcFlatCtrl(void *functionData)
{
	//all freq points from 50MHz to end
	int iNum = sizeof(powerlistpointsampoff) / sizeof(double);
	
	//IF ampilier set 30dB
	///IFGainCtrl(0,30.0);
	int iIndex = 0;
	
	int lowcutroad = 0;
	int highcutroad = 0;
	int mircocutroad = 0;
	
	int i = 0,j = 0;
	double saveData = 0.0;
	
	for(i = 0;i < iNum;i++)
	{
		lowcutroad = 0;
	 	highcutroad = 0;
		mircocutroad = 0;
		
		for(j = 0;j < bitFreqList.count;j++)
		{
			GetSync(synccalcHandle);
			printf("calc is running pre amp off,%d\n",i * iNum + j);

			///RfChannelChoose(0,*(bitFreqList.param + j));			

			//low freq	  	 
			if(*(bitFreqList.param+j) < LOWDOOR + ESP)
			{
				if(!lowcutroad)
				{
					lowcutroad = 1;
					//direct and
					///LowFreqPreAmpliChannelCtrl(0,0);
					///LowFreqPreAttenCtrl(0,powerlistpointsampoff[i] + 20);
				} 
			}
			else if(*(bitFreqList.param+j) < HIGHDOOR + ESP)
			{
				 if(!highcutroad)
				{
					highcutroad = 1;
					//direct and
					///HighFreqPreAmpliChannelCtrl(0,0);
					///HighFreqPreAttenCtrl(0,powerlistpointsampoff[i] + 20);
				}
			}
			else
			{
				if(!mircocutroad)
				{
					mircocutroad = 1;
					//direct and
					///MicroFreqPreAttenCtrl(0,0);
					///MicroFreqPreAttenCtrl(0,powerlistpointsampoff[i] + 20);
				}
			}					 
			//set acq states and call acq func
			
			//log convert
			
			//get maxvalue
			
			//save deta calc datas
			saveData -= powerlistpointsampoff[i]; 
			fprintf(fp,"%d         %.0lf         %.2lf\n",iIndex++,*(bitFreqList.param + j),saveData);
			
			ReleaseSync(synclistenHandle);
		}
	}
	
	//100MHz  calc IF ampliter
	GetSync(synccalcHandle);

	///LowFreqPreAmpliChannelCtrl(0,0);
	///LowFreqPreAttenCtrl(0,0);
	
	///RfChannelChoose(0,freqpoint);

	printf("calc is running,%d\n",100);
	ReleaseSync(synclistenHandle);
	
	//IF ampilier set 40dB
	GetSync(synccalcHandle);
	///IFGainCtrl(0,40.0);
	
	//log convert
	//get maxvalue
	///saveData -= -30;
	///fprintf(fp,"%d         %.0lf         %.2lf\n",iIndex++,freqpoint,saveData);
	printf("calc is running,%d\n",40);
	ReleaseSync(synclistenHandle);
	
	//IF ampilier set 50dB
	GetSync(synccalcHandle);
	///IFGainCtrl(0,50.0);
	
	///saveData -= -40;
	///fprintf(fp,"%d         %.0lf         %.2lf\n",iIndex++,freqpoint,saveData);
	printf("calc is running,%d\n",50);
	ReleaseSync(synclistenHandle); 
	
	//IF ampilier set 60dB
	GetSync(synccalcHandle);
	///IFGainCtrl(0,60.0);
	
	///saveData -= -50;
	///fprintf(fp,"%d         %.0lf         %.2lf\n",iIndex++,freqpoint,saveData);
	printf("calc is running,%d\n",60); 
	ReleaseSync(synclistenHandle); 
	//=================================================ON 
	///IFGainCtrl(0,30.0);    
	iNum = sizeof(powerlistpoints) / sizeof(double);
	for(i = 0;i < iNum;i++)	
	{
		lowcutroad = 0;
	 	highcutroad = 0;
		mircocutroad = 0;
		
		for(j = 0;j < bitFreqList.count;j++)		
		{
			GetSync(synccalcHandle);
			
			printf("calc is running pre amp on,%d\n",i * iNum + j);	
			///RfChannelChoose(0,*(bitFreqList.param + j));			
			
			//low freq	  	 
			if(*(bitFreqList.param+j) < LOWDOOR + ESP)
			{
				if(!lowcutroad)
				{
					lowcutroad = 1;
					//direct and
					///LowFreqPreAmpliChannelCtrl(0,1);
					///LowFreqPreAttenCtrl(0,powerlistpoints[i] + 35);
				} 
			}
			else if(*(bitFreqList.param+j) < HIGHDOOR + ESP)
			{
				 if(!highcutroad)
				{
					highcutroad = 1;
					//direct and
					///HighFreqPreAmpliChannelCtrl(0,1);
					///HighFreqPreAttenCtrl(0,powerlistpoints[i] + 35);
				}
			}
			else
			{
				if(!mircocutroad)
				{
					mircocutroad = 1;
					//direct and
					///MicroFreqPreAttenCtrl(0,1);
					///MicroFreqPreAttenCtrl(0,powerlistpoints[i] + 35);
				}
			}					 
			//set acq states and call acq func
			
			//log convert
			
			//get maxvalue
			
			//save deta calc datas
			saveData -= powerlistpoints[i]; 
			fprintf(fp,"%d         %.0lf         %.2lf\n",iIndex++,*(bitFreqList.param + j),saveData);
			ReleaseSync(synclistenHandle); 
		}
	} 
	
	//100MHz  calc IF ampliter
	GetSync(synccalcHandle);
	///LowFreqPreAmpliChannelCtrl(0,1);
	///LowFreqPreAttenCtrl(0,0);
	
	///RfChannelChoose(0,freqpoint);
	ReleaseSync(synclistenHandle); 
	
	//IF ampilier set 40dB
	GetSync(synccalcHandle);
	///IFGainCtrl(0,40.0);	
	//log convert
	//get maxvalue
	saveData -= -40;
	fprintf(fp,"%d         %.0lf         %.2lf\n",iIndex++,freqpoint,saveData);
	ReleaseSync(synclistenHandle); 
	
	//IF ampilier set 50dB
	GetSync(synccalcHandle);
	///IFGainCtrl(0,50.0);	
	saveData -= -50;
	fprintf(fp,"%d         %.0lf         %.2lf\n",iIndex++,freqpoint,saveData);
	ReleaseSync(synclistenHandle);

	//IF ampilier set 60dB
	GetSync(synccalcHandle);
	///IFGainCtrl(0,60.0);	
	saveData -= -60;
	fprintf(fp,"%d         %.0lf         %.2lf\n",iIndex++,freqpoint,saveData);
	ReleaseSync(synclistenHandle);
		
	fclose(fp);
	printf("the calc is over\n");
	return NULL;
}

static void* SyncFunc(void* param)
{
	int ret = 0;
	while(1)
	{
		//receive the cmd from the client and release the signal means the calc do actions		
		memset(cbuffer,0,BITMSGBUFFER);
		ret = recv(clientId,cbuffer,BITMSGBUFFER,0);
		if(ret <= 0)
		{
			printf("the connect has disconnect!!\n");			
			return NULL;
		}
		else
		{
			printf("%s\n",cbuffer);
		}

		cbuffer[ret] = 'Y';
		cbuffer[ret + 1] = '\n';

		ReleaseSync(synccalcHandle);			
		GetSync(synclistenHandle);
		send(clientId, cbuffer, strlen(cbuffer), 0);		
	};	
	return NULL;
}

static void GetSync(DiInt32 handle)
 {   
struct sembuf s;
   s.sem_num=0;
   s.sem_op=-1;
   s.sem_flg=0;
   if(semop(handle,&s,1)<0)
   {
     printf("op errro,%d:%s",errno,strerror(errno));
   }
 }
 
static void ReleaseSync(DiInt32 handle)
{   
struct sembuf s;
   s.sem_num=0;
   s.sem_op=1;
   s.sem_flg=0;
   if(semop(handle,&s,1)<0)
   {
     printf("op error,%d:%s",errno,strerror(errno));
   } 
}

static void GetLog(double* buffer,int isize)
{
	int i = 0;
	for(i = 0; i < isize; i++)
	{
		*(buffer + i) = 20 * log10(*(buffer + i) + PER);
	}
	return;
}

static int GetMaxValue(double* buffer,int isize) 
{
    	int i = 0;
	double temp = buffer[0];
	for(i = 0;i < isize;i++)
	{
		if(*(buffer + i) > temp)
			temp = *(buffer + i);
	}
	return temp;
}
