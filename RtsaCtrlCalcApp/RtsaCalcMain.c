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
#include "dpxMem.h"
#include "DpxContrl.h"
#include "errno.h"
#include "sweepinterupt.h"

#define BITMSGBUFFER 1024
#define PORT 5025//5001
#define SYNC_SERVER   6000
#define SYNC_CLIENT   6001

#define SOURIP "192.168.26.252"
static const double PER = 0.000000001; 

FILE *fp = NULL;
#define NETBUFFERSIZE 256
char commandBuffer[NETBUFFERSIZE];
pthread_t threadId;
pthread_t connectId;
pthread_t syncthreadId;
static void* CalcFlatCtrlEx(void *functionData);
static void* MultiConncet(void* param);
static void* SyncFunc(void* param);
void GetCtrlInHand(DiInt32 handle);
void ReleaseCtrlInHand(DiInt32 handle);
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
static double GetMaxValue(float *buffer, int isize);
static double GetAvgValue(double* buffer,int size);
int sweepHandle;

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

#define BUFFERSIZE 801
typedef struct FLATEMP
{
    double freq;
    double atten;
    int preswitch;
    int index;
    float ampbuf[BUFFERSIZE];
    struct FLATEMP* pndata; 
}CHANNELTEMPLATE,*PCHANNELTEMPLATE;

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
double *preflsit;
CHANNELTEMPLATE glotemp;
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


    FILE *fp1;
    //open file
#ifdef BIT_F238
    fp1 = fopen("refereq.txt", "r");
#endif
#ifdef BIT_F239
    fp1 = fopen("refereq_239.txt", "r");
#endif
#ifdef BIT_F238_SMART
    fp1 = fopen("refereq_238_smart.txt", "r");
#endif
    if (NULL == fp1)
        {
            return -1;
        }

    int freqlen = 0;
    int i = 0;
    fscanf(fp1,"%d",&freqlen);

    preflsit = (double*)malloc(sizeof(double) * freqlen);

    for (i = 0; i < freqlen; i++)
        {
            fscanf(fp1, "%lf", preflsit + i);
        }

    fclose(fp1);

    //ini sa states for calc
    iBack = BitOpen("/dev/pl-mem",&bitdevHandle);
    if(iBack < 0)
        {
            printf("mem map ini failed\n");
            return iBack;
        }

    iBack = OpenPlInterrupt();
    if(iBack < 0)
        {
            printf("interrupt ini failed\n");
            return iBack;
        }
    iBack =  RfIni(bitdevHandle);
    usleep(1000);
    if(iBack < 0)
        {
            printf("rtsa if bw set error\n");
            return iBack;
        }

    iBack = SetRtSaIFBandWidth(bitdevHandle);
    if(iBack < 0)
        {
            printf("rtsa if bw set error\n");
            return iBack;
        }

    iBack = DpxDisable(bitdevHandle);
    if(iBack < 0)
        {
            printf("DpxDisable error\n");
            return iBack;
        }

    iBack = SetRtSaFpgaStop(bitdevHandle);
    if(iBack < 0)
        {
            printf("SetRtSaFpgaStop error!!!!\n");
            //ErrOutPut(iBack,1);
            return iBack;
        }

	
    for(i = 0;i < 801;i++)
	{
*(glotemp.ampbuf + i) = 1;
	}
    if(setRtSaBalanceFactor(bitdevHandle,glotemp.ampbuf) < 0)
{
	printf("factor to 1 errot\n");
}

    iBack = SetRtSaRBW(bitdevHandle,5);
    if(iBack < 0)
        {
            //ErrOutPut(iBack,1);
            return iBack;
        }
    iBack = SetRtSaFFTWindow(bitdevHandle,4);
    if(iBack < 0)
        {
            //ErrOutPut(iBack,1);
            return iBack;
        }
    iBack = SetRtSaDetector(bitdevHandle, 0);
    if(iBack < 0)
        {
            //ErrOutPut(iBack,1);
            return iBack;
        }
    iBack = SetRtSaSpan(bitdevHandle,0);
    if(iBack < 0)
        {
            //ErrOutPut(iBack,1);
            return iBack;
        }
    iBack = SetRtSaAcqTime(bitdevHandle,0.1);
    if(iBack < 0)
        {
            //ErrOutPut(iBack,1);
            return iBack;
        }

    iBack = SetRtSaTrigger(bitdevHandle,1);
    if(iBack < 0)
        {
            //ErrOutPut(iBack,1);
            return iBack;
        }

    iBack = SetFirLoStepFreq(bitdevHandle,0,0);
    if(iBack < 0)
        {
            //ErrOutPut(iBack,1);
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


    if((sweepHandle = semget(SYNC_SWEEP,1,IPC_CREAT | 0660))<0)
        {
            printf("semget errno,%d:%s",errno,strerror(errno));
        }

    if(semctl(sweepHandle,0,SETVAL,0) < 0)
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

    memset(commandBuffer,0,NETBUFFERSIZE);
    sprintf(commandBuffer,":FREQ:MODE SWE\n");
    iBack = send(sourceId, commandBuffer, strlen(commandBuffer), 0);
    if(iBack < 0)
        printf("send source sweep failed\n");
    usleep(100000);
    memset(commandBuffer,0,NETBUFFERSIZE);
    sprintf(commandBuffer,":FREQ:SPAN 100MHz\n");
    iBack = send(sourceId, commandBuffer, strlen(commandBuffer), 0);
    if(iBack < 0)
        printf("send source sweep span failed\n");
    usleep(100000);

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

    if(preflsit != NULL)
        {
            free(preflsit);
            preflsit = NULL;
        }
#ifdef BIT_F238
        system("rm rtsareftemplate.fla");
        system("mv rtsareftmp.fla rtsareftemplate.fla");
        system("rm rtsaerrtemplate.fla");
        system("mv rtsaerrtmp.fla rtsaerrtemplate.fla");
#endif
#ifdef BIT_F239
        system("rm rtsareftemplate_239.fla");
        system("mv rtsareftmp.fla rtsareftemplate_239.fla");
        system("rm rtsaerrtemplate.fla");
        system("mv rtsaerrtmp.fla rtsaerrtemplate_239.fla");
#endif
#ifdef BIT_F238_SMART
        system("rm rtsareftemplate_238_smart.fla");
        system("mv rtsareftmp.fla rtsareftemplate_238_smart.fla");
        system("rm rtsaerrtemplate.fla");
        system("mv rtsaerrtmp.fla rtsaerrtemplate_238_smart.fla");
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

static double GetMaxValue(float* buffer,int isize)
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
static double GetCalcMaxValue(float *buffer, int num, double freqHz);

#define WAITINGTIME 100000  
unsigned int midBuffer[BUFFERSIZE];
static int SetSourOutputPower(double outpower);
static int SetSourceOutFreq(double ofreq);


double PRCEISE = 1.35;
int MIDPOS = 400;

#define UISHOW 1
#define TESTCALC 0
static void* CalcFlatCtrl(void *functionData)  
{
    //open file
    char pPath[256] = {0};
    getcwd(pPath, 256);
    strcat(pPath,"/rtsareftmp.fla");
    flagfp = fopen(pPath,"wb");
    if (NULL == flagfp)
        {
            printf("tmp error\n");
            return NULL;
        }
    memset(pPath,0,sizeof(pPath));
    getcwd(pPath, 256);
#if TESTCALC
#ifdef BIT_F238
    strcat(pPath,"/rtsacal.txt");
#endif
#ifdef BIT_F239
    strcat(pPath,"/rtsacal_239.txt");
#endif
#ifdef BIT_F238_SMART
    strcat(pPath,"/rtsacal_238_smart.txt");
#endif

    FILE *flagfp1 = fopen(pPath,"w");
    if (NULL == flagfp1)
        {
            return NULL;
        }
#endif
    FILE *fperr;
    //open file
    fperr = fopen("rtsaerrtmp.fla", "wb");
    if (NULL == fperr)
        {
            return NULL;
        }

    //all freq points from 50MHz to end
    int iNum = sizeof(powerlistpointsampoff) / sizeof(double);

    int iIndex = 0;

    int i = 0,j = 0;
    double saveData = 0.0;
    float acqBuffer[BUFFERSIZE];
    PreAmpliChannelCtrl(bitdevHandle,0);
    double tempAtten = 0.0;
    int n = 0;
    int ig = 0;
    int iflag = 0;
    double ddeta = 0.0;
    double refdeta = 0.0;
    int m = 0;
    int isum = 0;
    float what = 0.0;
    int in = 0;
    float fu = 0.0;
    for(i = 1;i < 2;i++)
        {
            tempAtten = powerlistpointsampoff[i] + 20;
            PreAttenCtrl(bitdevHandle,tempAtten);
            n = i;
            isum = 0;
            iflag = 0;
            ig = 0;
            //delete first zero freq points
            for(j = 1;j < bitFreqList.count;j++)
                {
                    what = 0.0;
                    ddeta = *(bitFreqList.param + j) - (DiInt64)(*(bitFreqList.param + j));
                    if(ddeta > 0.0)
                        {
                            iflag = 0;
                        }
                    if(!iflag)
                        {
                            for(m = 0;m < bitFreqList.count;m++)
                                {
                                    if(*(bitFreqList.param + m) >= *(preflsit + ig))
                                        {
                                            break;
                                        }
                                }                           
                            printf("preamp:0,ref freq %lf,posi is %d\n",*(preflsit + ig),m);
#if TESTCALC
                            fprintf(flagfp1,"preamp:0,ref freq %lf,posi is %d\n",*(preflsit + ig),m);
#endif
                            SetSourOutputPower((maplist + n * bitFreqList.count + m)->ampdB);
                            SetSourceOutFreq(*(preflsit + ig));
                            SetRtSaFpgaStop(bitdevHandle);
                            RfChannelChoose(bitdevHandle,*(preflsit + ig));
                            FirstLoFreqCtrl(bitdevHandle,*(preflsit + ig));                            
                            SetRtSaFpgaStart(bitdevHandle);
			usleep(1000000);

                            GetCtrlInHand(sweepHandle);
                            //usleep(100000);
                            GetResultFloatData(bitdevHandle, acqBuffer, BUFFERSIZE);
                            for(m = 0;m < BUFFERSIZE;m++)
                                {
                                    acqBuffer[m] = 20 * log10(*(acqBuffer + m) + 0.000001);
                                }			    
#if UISHOW
			    GetCtrlInHand(syncHandle); 
			    for(m = 0;m < BUFFERSIZE;m++)
				{
				    pshm_calbuf->calcb[m] = acqBuffer[m];
				}	
			    ReleaseCtrlInHand(guiHandle);
#endif
                            glotemp.freq = *(preflsit + ig);
                            glotemp.atten = tempAtten;
                            glotemp.preswitch = 0;
                            glotemp.index = ig;
                            //fprintf(flagfp1,"freq:%f,atten:%lf,preswitch:%d\n",glotemp.freq,glotemp.atten,glotemp.preswitch);
                            fu = acqBuffer[MIDPOS];
                            for(m = 0;m < BUFFERSIZE;m++)
                                {
				    //printf("freq is %lf,ori data is%f,mid data is %f\n",*(preflsit + ig),*(acqBuffer + m),fu);
                                    *(glotemp.ampbuf + m) = *(acqBuffer + m) - fu;
                                    //fprintf(flagfp1,"%f\n",*(glotemp.ampbuf + m));					
                                }                            
                            fwrite(&glotemp,sizeof(CHANNELTEMPLATE),1,flagfp);
                            ig++;
                            iflag = !iflag;
                        }

                    SetSourOutputPower((maplist + n * bitFreqList.count + j)->ampdB);
                    SetSourceOutFreq(*(bitFreqList.param + j));    
		    SetRtSaFpgaStop(bitdevHandle);                
                    RfChannelChoose(bitdevHandle,*(bitFreqList.param + j));
                    FirstLoFreqCtrl(bitdevHandle,*(bitFreqList.param + j));
                   
                    SetRtSaFpgaStart(bitdevHandle);
 	 	    usleep(1000000);
                    GetCtrlInHand(sweepHandle);
                    //usleep(100000);
                    GetResultFloatData(bitdevHandle, glotemp.ampbuf, BUFFERSIZE);
                    for(m = 0;m < BUFFERSIZE;m++)
                        {
                            glotemp.ampbuf[m] = 20 * log10(*(glotemp.ampbuf + m) + 0.000001);

                        }
		   
#if UISHOW
   		    GetCtrlInHand(syncHandle); 
			    for(m = 0;m < BUFFERSIZE;m++)
				{
				    pshm_calbuf->calcb[m] = glotemp.ampbuf[m];
				}	
		    ReleaseCtrlInHand(guiHandle);
#endif
                    refdeta = acqBuffer[MIDPOS] - glotemp.ampbuf[MIDPOS];
                    for(m = 0;m < BUFFERSIZE;m++)
                        {
                            if(what < fabs ((fabs(acqBuffer[m] - glotemp.ampbuf[m])) - fabs(refdeta)))
                                {
                                    what = fabs ((fabs(acqBuffer[m] - glotemp.ampbuf[m])) - fabs(refdeta));
                                    in = m;
                                }
                        }
		printf("all preamp:0,error at atten:%lf,freq:%lf,index:%d,deta:%f\n",tempAtten,*(bitFreqList.param + j),in,what);
#if TESTCALC
fprintf(flagfp1,"all preamp:0,error at atten:%lf,freq:%lf,index:%d,deta:%f\n",tempAtten,*(bitFreqList.param + j),in,what);
#endif
                    if(what >= PRCEISE)
                        {
                            glotemp.freq = *(bitFreqList.param + j);
                            glotemp.atten = tempAtten;
                            glotemp.preswitch = 0;
                            glotemp.index = in;
                            glotemp.pndata = NULL;
                            //fprintf(flagfp1,"freq:%f,atten:%lf,preswitch:%d\n",glotemp.freq,glotemp.atten,glotemp.preswitch);
                            fu = glotemp.ampbuf[MIDPOS];
                            for(m = 0;m < BUFFERSIZE;m++)
                                {
                                    *(glotemp.ampbuf + m) = *(glotemp.ampbuf + m) - fu;
                                    //fprintf(flagfp1,"%f\n",*(glotemp.ampbuf + m));
                                }
                            //fprintf(flagfp1,"=======================\n");
                            fwrite(&glotemp,sizeof(CHANNELTEMPLATE),1,fperr);
                            printf("preamp:0,error at atten:%lf,freq:%lf,sum:%d,index:%d,deta:%f\n",tempAtten,*(bitFreqList.param + j),++isum,in,what);
#if TESTCALC
fprintf(flagfp1,"preamp:0,error at atten:%lf,freq:%lf,sum:%d,index:%d,deta:%f\n",tempAtten,*(bitFreqList.param + j),isum,in,what);
#endif
                        }
                }
        }

    iNum = sizeof(powerlistpointsampon) / sizeof(double);
    //when preamp is on,the source out power start from -5dBm
    int nstartIndex = 3 * bitFreqList.count;
    PreAmpliChannelCtrl(0,1);

    for(i = 1;i < 2;i++)
        {
            ig = 0;
            iflag = 0;
            isum = 0;
            PreAttenCtrl(0,powerlistpointsampon[i] + 35);
            tempAtten = powerlistpointsampon[i] + 35;
            for(j = 1;j < bitFreqList.count;j++)
                {
                    what = 0.0;
                    ddeta = *(bitFreqList.param + j) - (DiInt64)(*(bitFreqList.param + j));
                    if(ddeta > 0.0)
                        {
                            iflag = 0;
                        }
                    if(!iflag)
                        {
                            for(m = 0;m < bitFreqList.count;m++)
                                {
                                    if(*(bitFreqList.param + m) >= *(preflsit + ig))
                                        {
                                            break;
                                        }
                                }                           
                            printf("preamp:1,ref freq %lf,posi is %d\n",*(preflsit + ig),m);
#if TESTCALC
fprintf(flagfp1,"preamp:1,ref freq %lf,posi is %d\n",*(preflsit + ig),m);
#endif
                            SetSourOutputPower((maplist + nstartIndex + i * bitFreqList.count + m)->ampdB);
                            SetSourceOutFreq(*(preflsit + ig));
                            SetRtSaFpgaStop(bitdevHandle);
                            RfChannelChoose(bitdevHandle,*(preflsit + ig));
                            FirstLoFreqCtrl(bitdevHandle,*(preflsit + ig));                            
                            SetRtSaFpgaStart(bitdevHandle);  
usleep(1000000);                          
                            GetCtrlInHand(sweepHandle);
                            //usleep(100000);
                            GetResultFloatData(bitdevHandle, acqBuffer, BUFFERSIZE);
                            for(m = 0;m < BUFFERSIZE;m++)
                                {
                                    acqBuffer[m] = 20 * log10(*(acqBuffer + m) + 0.0000001);
                                }
			    

#if UISHOW
			    GetCtrlInHand(syncHandle); 
			    for(m = 0;m < BUFFERSIZE;m++)
				{
				    pshm_calbuf->calcb[m] = acqBuffer[m];
				}	
			    ReleaseCtrlInHand(guiHandle);
#endif
                            glotemp.freq = *(preflsit + ig);
                            glotemp.atten = tempAtten;
                            glotemp.preswitch = 1;
                            glotemp.index = ig;
                            //fprintf(flagfp1,"freq:%f,atten:%lf,preswitch:%d\n",glotemp.freq,glotemp.atten,glotemp.preswitch);
                            fu = acqBuffer[MIDPOS];
                            for(m = 0;m < BUFFERSIZE;m++)
                                {
                                    *(glotemp.ampbuf + m) = *(acqBuffer + m) - fu;
                                    //fprintf(flagfp1,"%f\n",*(glotemp.ampbuf + m));
                                }
                            //fprintf(flagfp1,"=======================\n");
                            fwrite(&glotemp,sizeof(CHANNELTEMPLATE),1,flagfp);

                            ig++;
                            iflag = !iflag;
                        }
                    SetSourOutputPower((maplist + nstartIndex + i * bitFreqList.count + j)->ampdB);
                    SetSourceOutFreq(*(bitFreqList.param + j)); 
SetRtSaFpgaStop(bitdevHandle);                   
                    RfChannelChoose(bitdevHandle,*(bitFreqList.param + j));
                    FirstLoFreqCtrl(bitdevHandle,*(bitFreqList.param + j));                    
                    SetRtSaFpgaStart(bitdevHandle);
		 usleep(1000000);
                    GetCtrlInHand(sweepHandle);
                    //usleep(100000);
                    GetResultFloatData(bitdevHandle, glotemp.ampbuf, BUFFERSIZE);
                    for(m = 0;m < BUFFERSIZE;m++)
                        {
                            glotemp.ampbuf[m] = 20 * log10(*(glotemp.ampbuf + m) + 0.000001);
                        }
		    

#if UISHOW
		       GetCtrlInHand(syncHandle); 
   			    for(m = 0;m < BUFFERSIZE;m++)
				{
				    pshm_calbuf->calcb[m] = glotemp.ampbuf[m];
				}	
			ReleaseCtrlInHand(guiHandle);
#endif

                    refdeta = acqBuffer[MIDPOS] - glotemp.ampbuf[MIDPOS];
                    for(m = 0;m < BUFFERSIZE;m++)
                        {
                            if(what < fabs ((fabs(acqBuffer[m] - glotemp.ampbuf[m])) - fabs(refdeta)))
                                {
                                    what = fabs ((fabs(acqBuffer[m] - glotemp.ampbuf[m])) - fabs(refdeta));
                                    in = m;
                                }
                        }
printf("all preamp:1,error at atten:%lf,freq:%lf,index:%d,deta:%f\n",tempAtten,*(bitFreqList.param + j),in,what);
#if TESTCALC
fprintf(flagfp1,"all preamp:1,error at atten:%lf,freq:%lf,index:%d,deta:%f\n",tempAtten,*(bitFreqList.param + j),in,what);
#endif
                    if(what >= PRCEISE)
                        {
                            glotemp.freq = *(bitFreqList.param + j);
                            glotemp.atten = tempAtten;
                            glotemp.preswitch = 1;
                            glotemp.index = ig;
                            glotemp.pndata = NULL;
                            //fprintf(flagfp1,"freq:%f,atten:%lf,preswitch:%d\n",glotemp.freq,glotemp.atten,glotemp.preswitch);
                            fu = glotemp.ampbuf[MIDPOS];
                            for(m = 0;m < BUFFERSIZE;m++)
                                {
                                    *(glotemp.ampbuf + m) = *(glotemp.ampbuf + m) - fu;
                                    //fprintf(flagfp1,"%f\n",*(glotemp.ampbuf + m));
                                }
                            //fprintf(flagfp1,"=======================\n");
                            fwrite(&glotemp,sizeof(CHANNELTEMPLATE),1,fperr);
                            printf("preamp:1,error at atten:%lf,freq:%lf,sum:%d,index:%d,deta:%f\n",tempAtten,*(bitFreqList.param + j),++isum,in,what);
#if TESTCALC
fprintf(flagfp1,"preamp:1,error at atten:%lf,freq:%lf,sum:%d,index:%d,deta:%f\n",tempAtten,*(bitFreqList.param + j),isum,in,what);
#endif
                        }

                }
        }

    fclose(flagfp);
#if TESTCALC
    fclose(flagfp1);
#endif
    fclose(fperr);
    ch = 'q';
    return NULL;
}


static double GetCalcMaxValue(float* buffer,int num,double freqHz)
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
    sprintf(commandBuffer,":AMPL %lf\n",outpower);
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
    sprintf(commandBuffer,":FREQ:CENT %f\n",ofreq);
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

