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
#include "errno.h"

#define BITMSGBUFFER 1024
#define PORT 5025//5001
#define SYNC_SERVER   6000
#define SYNC_CLIENT   6001

#define SOURIP "192.168.26.252"
static const double PER = 0.0000001; 

FILE *fp = NULL;

pthread_t threadId;
pthread_t connectId;
pthread_t syncthreadId;
static void* CalcFlatCtrlEx(void *functionData);
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
static double GetMaxValue(double* buffer,int isize); 
static double GetAvgValue(double* buffer,int size);

//0427
typedef struct
{
	int index;
	double freqHz;
	double ampdB;
}FREQAMPLIST, *PFREQAMPLIST;
static int sourceId = 0;
struct sockaddr_in sourceaddr = {0};
pthread_t calcId;
static void* CalcFlatCtrl(void *functionData);
FILE *flagfp;
DiSession bitdevHandle;
int itemsSum = 0;
PFREQAMPLIST maplist = NULL; 
int GetSourceCalcResultParam();

//03-25
typedef struct
{
    DiReal64 isa;
    DiInt32 iIndex;
    DiReal64 dfreq;
    DiReal64 damp;
}SINGLE_POI;
static SINGLE_POI sinpoi;

static int ialive = 1;
char ch = ' ';
int syncHandle = 0;//212
int guiHandle = 0;
  PCALC_DATA pshm_calbuf;
  int shm_calbuf_id;
int main(int argc, char *argv[])
{
	int iBack = 0;
	char pPath[256] = {0}; 
	memset(pPath,0,256);
	getcwd(pPath, 256);
#ifdef BIT_F238
	strcat(pPath,"/freqlist.txt");
#endif

#ifdef BIT_F239
	strcat(pPath,"/freqlist_239.txt");
#endif

#ifdef BIT_F238_SMART
	strcat(pPath,"/freqlist_238_smart.txt");
#endif
	iBack = GetParamFromFile(pPath,&bitFreqList);
	
	/*
	printf("iBack is %d\n",iBack);
        FILE* fp1 = fopen("freqlistb.fla","wb+");	
        for(int i = 0;i < 10;i++)
	{
sinpoi.isa = 3.33;
		sinpoi.iIndex = i; 
			sinpoi.dfreq = *(bitFreqList.param + i);
			sinpoi.damp = 0.25+i;
			fwrite(&sinpoi,sizeof(SINGLE_POI),1,fp1);
	}   

 
        //fclose(fp1);
	FILE *fp1 = fopen("saflatcalcresult.fla","rb");

	rewind(fp1);
	double val = 0.0;	
 	SINGLE_POI tempsin;
	
	FILE *tempf = fp1;
	FILE *flagfp1 = fopen("sacal.txt","w");
 
        while(!feof(tempf))  
	{

		iBack = fread(&tempsin,sizeof(SINGLE_POI),1,fp1);

		val =  tempsin.damp;

                fprintf(flagfp1,"%lf,num is %d,index is %lf,the freq val is %lf\n",sinpoi.isa,tempsin.iIndex,tempsin.dfreq,val);

               
	};
 	fclose(fp1);
	fclose(flagfp1);
	return 0;       
	 */ 
        
	if(iBack < 0)
	{
		printf("load freqlist error\n");
		return iBack;
	}
	iBack = GetSourceCalcResultParam();
	if(iBack < 0)
	{
		printf("load source calc datas error\n");
		return iBack;
	}	
	
	//ini sa states for calc
	iBack = BitOpen("/dev/pl-mem",&bitdevHandle);
	if(iBack < 0)
	{
		printf("mem map ini failed\n");
		return iBack;
	}
#ifdef BIT_F238
	iBack = SetFreqSegFlag(bitdevHandle,3);
#endif

#ifdef BIT_F239
	iBack = SetFreqSegFlag(bitdevHandle,3);
#endif

#ifdef BIT_F238_SMART
	iBack = SetFreqSegFlag(bitdevHandle,7);
#endif

	if(iBack < 0)
	{
		printf("power source failed\n");
		return iBack;
	}

	iBack = SetDataProcMode(bitdevHandle,0);
		if(iBack < 0)
		{
			
			return iBack;
		}
	//set zerospan mode
	iBack =	SetZeroSpan(bitdevHandle,1);
	if(iBack < 0)
	{
		printf("settiing zerospan failed\n");
		return iBack;
	}
	//points num and step set 0
	iBack = SetFirLoStepFreq(bitdevHandle,0,0);	
	if(iBack < 0)
	{
		printf("settiing lo step to 0 failed\n");
		return iBack;
	}
	iBack = SetSegPoint(bitdevHandle,0);
	if(iBack < 0)
	{
		printf("settiing points num to 0 failed\n");
		return iBack;
	}
	//rbw/vbw
	iBack = SetRbw(bitdevHandle,1000000);
	if(iBack < 0)
	{
		printf("SetRbw failed\n");
		return iBack;
	}

	iBack = SetVbw(bitdevHandle,1000000);
	if(iBack < 0)
	{
		printf("SetVbw failed\n");
		return iBack;
	}
	//fir stable time and before check trig time
	iBack = SetFirRbwvbwDelayTime(bitdevHandle,2000.0);
	if(iBack < 0)
	{
		printf("fir stable time  failed\n");
		return iBack;
	}
	iBack = SetBucketTrigDelayTime(bitdevHandle,100.0);
	if(iBack < 0)
	{
		printf("before check trig time  failed\n");
		return iBack;
	}
	//sum sweep time
	SetTotalSwtTimeUs(bitdevHandle,801*20+40);
	if(iBack < 0)
	{
		printf("total sweep time failed\n");
		return iBack;
	}

	//bucket time
	iBack = SetFirBucketTime(bitdevHandle,20);
	if(iBack < 0)
	{
		printf("SetFirBucketTime  failed\n");
		return iBack;
	}
	//show num
	iBack = SetDisplayNum(bitdevHandle,801);
	if(iBack < 0)
	{
		printf("SetDisplayNum failed\n");
		return iBack;
	}
	iBack = SetDetectormode(bitdevHandle,1);
	if(iBack < 0)
	{
		printf("check mode failed\n");
		return iBack;
	}
void* temptr = 0;
	  shm_calbuf_id = shmget((key_t)SYNC_KEY_CALC_CAL, sizeof(CALC_DATA), IPC_CREAT|0660);
  if  (shm_calbuf_id == -1)
    {
	printf("calc buffer error\n");
    }
  else
    {
      temptr = shmat(shm_calbuf_id, (void*)0, 0);
      if (temptr == (void*)-1)
        {
printf("calc buffer addr error\n");
        }
      pshm_calbuf = (PCALC_DATA)temptr;
    }


  if((syncHandle = semget(SYNC_KEY_CAL,1,IPC_CREAT | 0660))<0)
    {

    }
    if(semctl(syncHandle,0,SETVAL,1) < 0)
        {
            printf("init error,%d:%s",errno,strerror(errno));
        }

  if((guiHandle = semget(SYNC_KEY_GUI_CAL,1,IPC_CREAT | 0660))<0)
    {

    }
	
  if(semctl(guiHandle,0,SETVAL,1) < 0)
        {
            printf("init error,%d:%s",errno,strerror(errno));
        }

	sourceId = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sourceId < 0)
	printf("create socket failed,code is%d\n",errno);
	printf("have created socket\n");

	sourceaddr.sin_family = AF_INET;
	sourceaddr.sin_port = htons(PORT);
	sourceaddr.sin_addr.s_addr = inet_addr(SOURIP);
	int iRetVal = connect(sourceId,(struct sockaddr*)&sourceaddr,sizeof(sourceaddr));
	if(iRetVal < 0)
	{
		printf("Server connection failed,code is%d\n",errno);
		close(sourceId);
		return 0;
	}

	usleep(1000000);
	//start calc thread and calc
	iBack = pthread_create(&calcId,NULL,CalcFlatCtrl,NULL);
	if(iBack < 0)
	{
		perror("calc thread create fail\n");
		return iBack;
	}	

	
	//while(ialive && (ch = getchar()))
	while(ialive)
	{
		switch(ch)
		{
			case 'q':
			if(close(sourceId) < 0)
				printf("source close falied\n");		
			ialive = 0;
			break;
		}
		usleep(500000);	
	}

	if(maplist !=  NULL)
	{
		free(maplist);
		maplist = NULL;
	}
	if (bitFreqList.param != NULL)
	{
		free(bitFreqList.param);
		bitFreqList.param = NULL;
	}

	
#ifdef BIT_F238
system("rm saflatcalcresult.fla");
	system("mv saflatcalcresulttmp.fla saflatcalcresult.fla");
#endif
#ifdef BIT_F239
system("rm saflatcalcresult_239.fla");
	system("mv saflatcalcresulttmp.fla saflatcalcresult_239.fla");
#endif

#ifdef BIT_F238_SMART
system("rm saflatcalcresult_238_smart.fla");
	system("mv saflatcalcresulttmp.fla saflatcalcresult_238_smart.fla");
#endif
	system("/bin/sync");
	system("/sbin/reboot");
	return 0;
}

int GetSourceCalcResultParam()
{
	FILE *fp1; 
	//open file
#ifdef BIT_F238
	fp1 = fopen("soureccalcresult.txt", "r");
#endif

#ifdef BIT_F239
	fp1 = fopen("soureccalcresult_239.txt", "r");
#endif

#ifdef BIT_F238_SMART
	fp1 = fopen("soureccalcresult_238_smart.txt", "r");
#endif
	if (NULL == fp1)
	{
		return -1;
	}

	
	// get file nums
	char flag;
	int filelen = 0;

	while (!feof(fp1))
	{
		flag = fgetc(fp1);
		if (flag == '\n')
			filelen++;
	}
	itemsSum = filelen;
	//back pointer 
    	rewind(fp1);

	maplist = (PFREQAMPLIST)malloc(sizeof(FREQAMPLIST) * filelen);
	if (NULL == maplist)
		return -1;

	char str1[64];
	fscanf(fp1, "%s  %s  %s", str1, str1, str1); 
	int i = 0;
	for (i = 0; i < filelen; i++)
	{
		fscanf(fp1, "%d%lf%lf", &((maplist + i)->index), &((maplist + i)->freqHz), &((maplist + i)->ampdB));
	}
	
	if (fp1 != NULL)
		fclose(fp1); 	
	return 0;	
}

int fmainold(int argc, char *argv[])
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
		iBack = pthread_create(&threadId,NULL,CalcFlatCtrlEx,NULL);
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
//double powerlistpointsampoff[] = {10.0,10.0,10.0,10.0,10.0,5.0,0.0,-5.0,-10.0,-15.0,-20.0};
double powerlistpointsampoff[] = {10.0,5.0,0.0,-5.0,-10.0,-15.0,-20.0};  

static void* CalcFlatCtrlEx(void *functionData)
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

static double GetMaxValue(double* buffer,int isize) 
{
    	int i = 0;
	double temp = buffer[0];
	int imaxindex = 0;
	double sum = 0.0;
	for(i = 0;i < isize;i++)
	{
		if(*(buffer + i) > temp)
		{
			temp = *(buffer + i);
			imaxindex = i;
		}
	sum+=*(buffer + i);
	}
	//printf("index 1 data is %lf,max value is %lf,max index is %d,check value is %lf\n",*(buffer + 1),temp,imaxindex,sum);
	return temp;
}

static double GetAvgValue(double* buffer,int size)
{
	int i = 0;
	double tempAvg = 0.0;
	for(i = 0;i < size;i++)
	{
		tempAvg += buffer[i];
	}	
	return tempAvg / size;
}

//added by Steve,0427
//=================================================
//calc when zero span mode
//this part is for sa whole machine calc
//double powerlistpointsampoff[] = {10.0,5.0,0.0,-5.0,-10.0,-15.0,-20.0}; //for sa	source value 
double powerlistpointsampon[] = {-5.0,-10.0,-15.0,-20.0,-25.0,-30.0,-35.0}; //for sa
static int Y = 1;   
static double GetCalcMaxValue(double* buffer,int num,double freqHz);
#define BUFFERSIZE 801
#define WAITINGTIME 100000  
unsigned int midBuffer[BUFFERSIZE];
static int SetSourOutputPower(double outpower);
static int SetSourceOutFreq(double ofreq);
#define NETBUFFERSIZE 256
char commandBuffer[NETBUFFERSIZE];
#define TEST_CALC_DATA
static void* CalcFlatCtrl(void *functionData)  
{
	
	//open file
	char pPath[256] = {0};
    	getcwd(pPath, 256);
	char pPath_new[256] = {0};
    	getcwd(pPath_new, 256);
	strcat(pPath,"/saflatcalcresulttmp.fla");
	flagfp = fopen(pPath,"wb");		
	if (NULL == flagfp)
	{
	printf("tmp error\n");
		return NULL;
	}
        

	memset(pPath,0,sizeof(pPath));
	getcwd(pPath, 256);

#ifdef TEST_CALC_DATA
#ifdef BIT_F238
	strcat(pPath_new,"/sacal.txt");
#endif
#ifdef BIT_F239
strcat(pPath_new,"/sacal_239.txt");
#endif
#ifdef BIT_F238_SMART
strcat(pPath_new,"/sacal_238_smart.txt");
#endif
	FILE *flagfp1 = fopen(pPath_new,"w");
	if (NULL == flagfp1)
	{
		return NULL;
	}
#endif
	//all freq points from 50MHz to end
	int iNum = sizeof(powerlistpointsampoff) / sizeof(double);	

	int iIndex = 0;  
	
	int i = 0,j = 0;
	double saveData = 0.0;
	double acqBuffer[BUFFERSIZE];
	PreAmpliChannelCtrl(bitdevHandle,0);
	double tempAtten = 0.0; 
	int n = 0;
	for(i = 0;i < iNum;i++)
	{
	  	//1030
		//if(i <= 3)
/*
		if(0 == i)
		{
			//20190102
			//tempAtten = powerlistpointsampoff[i] + 40 - i * 5;
			//tempAtten = powerlistpointsampoff[i];


			tempAtten = powerlistpointsampoff[i] + 27.5;
//tempAtten = powerlistpointsampoff[i] + 20;
		}
else if(1 == i)
{
tempAtten = powerlistpointsampoff[i] + 22.5;
}
		else
*/
		{
			tempAtten = powerlistpointsampoff[i] + 20;
		}			
	   
		PreAttenCtrl(bitdevHandle,tempAtten);
/*
		if(i < 5)
		{
			n = 0;
		}
		else
		{
			n = i - 4;
		}
*/
		n = i;	
		for(j = 0;j < bitFreqList.count;j++)
		{

			RfChannelChoose(bitdevHandle,*(bitFreqList.param + j));

			FirstLoFreqCtrl(bitdevHandle,*(bitFreqList.param + j));
			SetSourceOutFreq(*(bitFreqList.param + j));

			SetSourOutputPower((maplist + n * bitFreqList.count + j)->ampdB);
			if(j == 0)
			{
				usleep(100000);
			}			
			//get maxvalue
			saveData = GetCalcMaxValue(acqBuffer,BUFFERSIZE,*(bitFreqList.param + j));
			//save deta calc datas			
			saveData -= powerlistpointsampoff[i]; 
			sinpoi.iIndex = iIndex; 
			sinpoi.dfreq = *(bitFreqList.param + j);
			sinpoi.damp = saveData;
                        fwrite(&sinpoi,sizeof(SINGLE_POI),1,flagfp);
#ifdef TEST_CALC_DATA
			fprintf(flagfp1,"%d         %.1lf         %.2lf\n",iIndex,*(bitFreqList.param + j),saveData);
#endif
			iIndex++;
			//printf("preamp is %d,atten is %lf,freq is %lf,result is %lf\n",0,tempAtten,*(bitFreqList.param + j),saveData);
		}
	}
	
	iNum = sizeof(powerlistpointsampon) / sizeof(double);	
	//when preamp is on,the source out power start from -5dBm
	int nstartIndex = 3 * bitFreqList.count;

	PreAmpliChannelCtrl(0,1);
	for(i = 0;i < iNum;i++)
	{
		
		PreAttenCtrl(0,powerlistpointsampon[i] + 35);

		for(j = 0;j < bitFreqList.count;j++)
		{

			RfChannelChoose(0,*(bitFreqList.param + j));

			FirstLoFreqCtrl(bitdevHandle,*(bitFreqList.param + j));
			SetSourceOutFreq(*(bitFreqList.param + j));
			SetSourOutputPower((maplist + nstartIndex + i * bitFreqList.count + j)->ampdB); 
		 	if(j == 0)
			{
				usleep(100000);
			}
			saveData = GetCalcMaxValue(acqBuffer,BUFFERSIZE,*(bitFreqList.param + j));
			saveData -= powerlistpointsampon[i]; 
			sinpoi.iIndex = iIndex; 
			sinpoi.dfreq = *(bitFreqList.param + j);
			sinpoi.damp = saveData;
			fwrite(&sinpoi,sizeof(SINGLE_POI),1,flagfp);
#ifdef TEST_CALC_DATA
			fprintf(flagfp1,"%d         %.1lf         %.2lf\n",iIndex,*(bitFreqList.param + j),saveData);
#endif
			iIndex++;
			//printf("preamp is %d,atten is %lf,freq is %lf,result is %lf\n",1,powerlistpointsampon[i] + 35,*(bitFreqList.param + j),saveData);
		}
	} 
	
	fclose(flagfp);
#ifdef TEST_CALC_DATA
	fclose(flagfp1);
#endif
	ch = 'q';
	return NULL;
}

void GetCtrlInHand(DiInt32 handle);
void ReleaseCtrlInHand(DiInt32 handle);
static double GetCalcMaxValue(double* buffer,int num,double freqHz)
{
	

 DiInt32 iBack = DataBufferClear(bitdevHandle,1);
    if(iBack < 0)
        {
            printf("lo setting failed\n");
        }
    iBack = DataBufferClear(bitdevHandle,0);
    if(iBack < 0)
        {
           printf("lo setting failed\n");
        }
if(FirstLoFreqCtrl(bitdevHandle,freqHz) < 0)
	{
		printf("lo setting failed\n");
	}
	
	usleep(50000);	
SetSwpRun(bitdevHandle);
	usleep(50000);
	//set acq states and call acq func
GetCtrlInHand(syncHandle); 
	GetResultData(bitdevHandle,midBuffer,num);
	SetSwpStop(bitdevHandle);
	//log convert
	int i = 0;

	for(i = 0;i < num;i++)
	{				
		buffer[i] = 20 * log10(*(midBuffer + i) + 0.000001);
//printf("%lf\n",buffer[i]);
		
	}

for(i = 0;i < num;i++)
{
pshm_calbuf->calcb[i] = buffer[i];
}
	//get maxvalue
ReleaseCtrlInHand(guiHandle);
	return GetMaxValue(buffer,num);
}

static int SetSourOutputPower(double outpower)
{   
	int iBack = 0;
	memset(commandBuffer,0,NETBUFFERSIZE);
	sprintf(commandBuffer,":POWER %lf\n",outpower);   
	iBack = send(sourceId, commandBuffer, strlen(commandBuffer), 0);
	if(iBack < 0)
	printf("send source power failed\n");
	usleep(100000);
	return iBack;
}

//set lo outfreq
static int SetSourceOutFreq(double ofreq)
{
	int iBack = 0;
	memset(commandBuffer,0,NETBUFFERSIZE);
	sprintf(commandBuffer,":FREQ %f\n",ofreq);
	iBack = send(sourceId, commandBuffer, strlen(commandBuffer), 0);
	if(iBack < 0)
	printf("send source freq failed\n");
	usleep(100000);
	return iBack;
}

void GetCtrlInHand(DiInt32 handle)
{
    struct sembuf s;
    s.sem_num=0;
    s.sem_op=-1;
    s.sem_flg=0;
    if(semop(handle,&s,1)<0)
        {
            printf("op errro,%d:%s",errno,strerror(errno));
        }
    return;
}

void ReleaseCtrlInHand(DiInt32 handle)
{
    struct sembuf s;
    s.sem_num=0;
    s.sem_op=1;
    s.sem_flg=0;
    if(semop(handle,&s,1)<0)
        {
            printf("op error,%d:%s",errno,strerror(errno));
        }
    return;
}

