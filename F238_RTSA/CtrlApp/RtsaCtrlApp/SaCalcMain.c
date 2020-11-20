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
#define PORT 5025
#define SYNC_SERVER   6000
#define SYNC_CLIENT   6001

#define SOURIP "192.168.1.10"
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
static int GetMaxValue(double* buffer,int isize); 
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
int main(int argc, char *argv[])
{
    int iBack = 0;
    char pPath[256] = {0};
    memset(pPath,0,256);
    getcwd(pPath, 256);
    strcat(pPath,"/freqlist.txt");
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

    //ini sa states for calc
    iBack = BitOpen("/dev/mem",&bitdevHandle);
    if(iBack < 0)
        {
            printf("mem map ini failed\n");
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
    //fir stable time and before check trig time
    iBack = SetFirRbwvbwDelayTime(bitdevHandle,600.0);
    if(iBack < 0)
        {
            printf("fir stable time  failed\n");
            return iBack;
        }
    iBack = SetBucketTrigTime(bitdevHandle,100.0);
    if(iBack < 0)
        {
            printf("before check trig time  failed\n");
            return iBack;
        }
    //sum sweep time
    SetTotalSwtTimeUs(bitdevHandle,501*20-40);
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
    iBack = SetDisplayNum(bitdevHandle,501);
    if(iBack < 0)
        {
            printf("SetDisplayNum failed\n");
            return iBack;
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

    int ialive = 1;
    char ch = ' ';
    while(ialive && (ch = getchar()))
        {
            switch(ch)
                {
                case 'q':
                    if(close(sourceId) < 0)
                        printf("source close falied\n");
                    ialive = 0;
                    break;
                }
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
    return 0;
}

int GetSourceCalcResultParam()
{
    FILE *fp1;
    //open file
    fp1 = fopen("soureccalcresult.txt", "r");
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
#define WAITINGTIME 200000  //200ms
unsigned int midBuffer[BUFFERSIZE];
static int SetSourOutputPower(double outpower);
static int SetSourceOutFreq(double ofreq);
#define NETBUFFERSIZE 256
char commandBuffer[NETBUFFERSIZE];

static void* CalcFlatCtrl(void *functionData)  
{	
    //open file
    char pPath[256] = {0};
    getcwd(pPath, 256);
    strcat(pPath,"/saflatcalcresult.txt");
    flagfp = fopen(pPath,"w");
    if (NULL == flagfp)
        {
            return NULL;
        }
    fprintf(flagfp,"No.       freqHz          detadB\n");
    //all freq points from 50MHz to end
    int iNum = sizeof(powerlistpointsampoff) / sizeof(double);

    //IF ampilier set 30dB

    IFGainCtrl(bitdevHandle,30.0);

    int iIndex = 0;

    int i = 0,j = 0;
    double saveData = 0.0;
    double acqBuffer[BUFFERSIZE];
    PreAmpliChannelCtrl(bitdevHandle,0);
    for(i = 0;i < iNum;i++)
        {

            PreAttenCtrl(bitdevHandle,powerlistpointsampoff[i] + 20);

            for(j = 0;j < bitFreqList.count;j++)
                {

                    RfChannelChoose(bitdevHandle,*(bitFreqList.param + j));
                    SetSourceOutFreq(*(bitFreqList.param + j));
                    SetSourOutputPower((maplist + i * bitFreqList.count + j)->ampdB);

                    //get maxvalue
                    saveData = GetCalcMaxValue(acqBuffer,BUFFERSIZE,*(bitFreqList.param + j));
                    //save deta calc datas
                    saveData -= powerlistpointsampoff[i];
                    fprintf(flagfp,"%d         %.1lf         %.2lf\n",iIndex++,*(bitFreqList.param + j),saveData);
                    printf("preamp is %d,atten is %lf,freq is %lf,result is %lf\n",0,powerlistpointsampoff[i] + 20,*(bitFreqList.param + j),saveData);
                }
        }

    //100MHz  calc IF ampliter
    PreAmpliChannelCtrl(0,0);
    PreAttenCtrl(0,0);

    RfChannelChoose(0,freqpoint);
    SetSourceOutFreq(freqpoint);

    //-20dB single point,0416
    SetSourOutputPower((maplist + itemsSum - 5)->ampdB);
    saveData = GetCalcMaxValue(acqBuffer,BUFFERSIZE,freqpoint);
    saveData -= -20;
    fprintf(flagfp,"%d         %.1lf         %.2lf\n",iIndex++,freqpoint,saveData);
    printf("preamp is %d,atten is %lf,freq is %lf,result is %lf\n",0,0.0,freqpoint,saveData);


    //IF ampilier set 40dB
    IFGainCtrl(0,40.0);
    SetSourOutputPower((maplist + itemsSum - 4)->ampdB);
    saveData = GetCalcMaxValue(acqBuffer,BUFFERSIZE,freqpoint);
    saveData -= -30;
    fprintf(flagfp,"%d         %.1lf         %.2lf\n",iIndex++,freqpoint,saveData);
    printf("preamp is %d,if gain is %lf,freq is %lf,result is %lf\n",1,40.0,freqpoint,saveData);

    //IF ampilier set 50dB
    IFGainCtrl(0,50.0);
    SetSourOutputPower((maplist + itemsSum - 3)->ampdB);
    saveData = GetCalcMaxValue(acqBuffer,BUFFERSIZE,freqpoint);
    saveData -= -40;
    fprintf(flagfp,"%d         %.1lf         %.2lf\n",iIndex++,freqpoint,saveData);
    printf("preamp is %d,if gain is %lf,freq is %lf,result is %lf\n",1,50.0,freqpoint,saveData);

    //IF ampilier set 60dB
    IFGainCtrl(0,60.0);
    SetSourOutputPower((maplist + itemsSum - 2)->ampdB);
    saveData = GetCalcMaxValue(acqBuffer,BUFFERSIZE,freqpoint);
    saveData -= -50;
    fprintf(flagfp,"%d         %.1lf         %.2lf\n",iIndex++,freqpoint,saveData);
    printf("preamp is %d,if gain is %lf,freq is %lf,result is %lf\n",1,60.0,freqpoint,saveData);
    //=================================================ON

    IFGainCtrl(0,30.0);

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
                    SetSourceOutFreq(*(bitFreqList.param + j));
                    SetSourOutputPower((maplist + nstartIndex + i * bitFreqList.count + j)->ampdB);

                    saveData = GetCalcMaxValue(acqBuffer,BUFFERSIZE,*(bitFreqList.param + j));
                    saveData -= powerlistpointsampon[i];
                    fprintf(flagfp,"%d         %.1lf         %.2lf\n",iIndex++,*(bitFreqList.param + j),saveData);
                    printf("preamp is %d,atten is %lf,freq is %lf,result is %lf\n",1,powerlistpointsampon[i] + 35,*(bitFreqList.param + j),saveData);
                }
        }


    //100MHz  calc IF ampliter
    PreAmpliChannelCtrl(0,1);
    PreAttenCtrl(0,0);

    RfChannelChoose(0,freqpoint);
    SetSourceOutFreq(freqpoint);

    //add -30 single 100MHz point,0416
    SetSourOutputPower((maplist + itemsSum - 4)->ampdB);

    saveData = GetCalcMaxValue(acqBuffer,BUFFERSIZE,freqpoint);
    saveData -= -30;
    fprintf(flagfp,"%d         %.1lf         %.2lf\n",iIndex++,freqpoint,saveData);
    printf("preamp is %d,atten is %lf,freq is %lf,result is %lf\n",1,0.0,freqpoint,saveData);

    //IF ampilier set 40dB
    IFGainCtrl(0,40.0);
    SetSourOutputPower((maplist + itemsSum - 3)->ampdB);

    saveData = GetCalcMaxValue(acqBuffer,BUFFERSIZE,freqpoint);
    saveData -= -40;
    fprintf(flagfp,"%d         %.1lf         %.2lf\n",iIndex++,freqpoint,saveData);
    printf("preamp is %d,if gain is %lf,freq is %lf,result is %lf\n",1,40.0,freqpoint,saveData);

    //IF ampilier set 50dB
    IFGainCtrl(0,50.0);
    SetSourOutputPower((maplist + itemsSum - 2)->ampdB);

    saveData = GetCalcMaxValue(acqBuffer,BUFFERSIZE,freqpoint);
    saveData -= -50;
    fprintf(flagfp,"%d         %.1lf         %.2lf\n",iIndex++,freqpoint,saveData);
    printf("preamp is %d,if gain is %lf,freq is %lf,result is %lf\n",1,50.0,freqpoint,saveData);

    //IF ampilier set 60dB
    IFGainCtrl(0,60.0);
    SetSourOutputPower((maplist + itemsSum - 1)->ampdB);

    saveData = GetCalcMaxValue(acqBuffer,BUFFERSIZE,freqpoint);
    saveData -= -60;
    fprintf(flagfp,"%d         %.1lf         %.2lf\n",iIndex++,freqpoint,saveData);
    printf("preamp is %d,if gain is %lf,freq is %lf,result is %lf\n",1,60.0,freqpoint,saveData);

    fclose(flagfp);
    return NULL;
}

static double GetCalcMaxValue(double* buffer,int num,double freqHz)
{
    FirstLoFreqCtrl(bitdevHandle,freqHz);
    SetSwpRun(bitdevHandle);
    usleep(WAITINGTIME);
    //set acq states and call acq func
    GetResultData(bitdevHandle,midBuffer,num);
    SetSwpStop(bitdevHandle);
    //log convert
    int i = 0;
    for(i = 0;i < num;i++)
        {
            buffer[i] = 20 * log10(*(midBuffer + i) + 0.000001);
        }
    //get maxvalue
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
