#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include "ShmEngine.h"
#include "SaDataStruct.h"
#include "MidMsg.h"
#include "BitSehInfo.h"
#include "DiIoCtrl.h"
#include "time.h"
#include "whoref.h"
//---------------------------------------------
typedef struct
{
    sem_t thread_syn_sem;
    pthread_t threadId;
    void* (*func)(void* param);
}THREAD_INFO,*PTHREAD_INFO;
//Albert 1022, extract sys ctrl only.
THREAD_INFO mid_msg_thread;
PTHREAD_INFO pmid_msg_thread = NULL;
//-----------------------------------------------
//#define THREAD_BY_TIME 10000 //for thread start one by one
//extern _SM_SYNC syncMana;
//extern PCONFIG_UPDATE sm_config_update;
//extern PCONFIG_RSA_CTRL sm_config_rsa_ctrl;
//-----------------------------------------------
//-----------------------------------------------
//static func
static DiInt32 WhileFunc(void);
static DiInt32 StartMultiWork(void);
static DiInt32 ObjIni(void);
static DiInt32 ProRelease(void* param);
//-----------------------------------------------
//global func
//DiSession rfHandle;
DiSession bitdevHandle = 0;

//0810 steve
DiInt32 LangType = 0;
#define Len 128
static DiChar errBuffer[Len];	
void ErrOutPut(DiInt32 errCode,DiInt32 itype);
extern void FirstReadInfo();
extern PCONFIG_UPDATE sm_config_update;
extern PALL_NOTIC_CODE sm_notic_excep;
RSA_EXIT gappexit;
extern PCONFIG_SYSTEM sm_config_system;
//0927 steve,for back recover
//extern PSTART_FLAG sm_startflag;

DEVMSG devmsg;

int main(int argc, char *argv[])
{	
    DiInt32 iBack = 0;
    system("/sbin/ifconfig eth0 192.168.26.238");

    freopen("sysctrl.log", "a", stdout);
    setvbuf(stdout, (char *)NULL, _IONBF, 0);
    freopen("sysctrlerr.log", "a", stderr);
    setvbuf(stderr, (char *)NULL, _IONBF, 0);

    time_t timep;
    time (&timep);
    //printf("SYS CTRL APP START UP:\n%s",asctime(gmtime(&timep)));
    initNoticeCode(0);

    if((iBack = IniShmCtrl(NULL)) >= 0)
        {
            printf("sys shm init success\n");
        }
    else
        {
            printf("sys shm init failed\n");
        }

    iBack = BitOpen("/dev/pl-mem",&bitdevHandle);
    if(iBack < 0)
        {
            setNoticePara(1,2,2,PLT_EXCE_SOURCE);
            sm_notic_excep->noticode = GetNoticeCode();
            printf("pl remap failed\n");
            return iBack;
        }

    
    char pPath[256] = {0};
    getcwd(pPath, 256);
    strcat(pPath,"/develop.msg");
    FILE *fp;
    fp = fopen(pPath, "rb");
    if (NULL == fp)
        {
            setNoticePara(1,2,3,PLT_EXCE_SOURCE);
            sm_notic_excep->noticode = GetNoticeCode();
            printf("load develop file excep\n");
            return -1;
        }
    fread(&devmsg,sizeof(DEVMSG),1,fp);
    fclose(fp);

    if(SetOsciFreq(bitdevHandle,devmsg.osiword) < 0)
        {
            setNoticePara(1,2,4,PLT_EXCE_SOURCE);
            sm_notic_excep->noticode = GetNoticeCode();
            printf("freq osci calc failed\n");
        }
 
    //Initial Api Driver
    iBack = InitSysApiDev();
    if(iBack < 0)
        {
            setNoticePara(1,2,5,PLT_EXCE_SOURCE);
            sm_notic_excep->noticode = GetNoticeCode();
            printf("devices handle init failed\n");
        }
    //playWav("button.wav");
    //shm done

    // initial Udisk and Mouse recall funtion  Albert 19/03/15
    //RegisterUDisk();
    // read system info at first Albert 19/02/22
    //FirstReadInfo();
    sm_config_system->PSFreqCalc = devmsg.osiword;

 if(GetCpldVer(bitdevHandle,&sm_config_system->cpldver ) < 0)
{
setNoticePara(1,2,27,PLT_EXCE_SOURCE);
            sm_notic_excep->noticode = GetNoticeCode();
            printf("get cpld version failed\n");
}

 if(GetZynqVer(bitdevHandle,&sm_config_system->mainfpgaver ) < 0)
{
setNoticePara(1,2,25,PLT_EXCE_SOURCE);
            sm_notic_excep->noticode = GetNoticeCode();
            printf("get main fpga version failed\n");
}


    //open and ini dev
    iBack = ObjIni();
    if(iBack < 0)
        {
            setNoticePara(1,2,6,PLT_EXCE_SOURCE);
            sm_notic_excep->noticode = GetNoticeCode();
            printf("object init failed\n");
        }

 if(GetSpaVer(bitdevHandle,&sm_config_system->spafpgaver ) < 0)
{
setNoticePara(1,2,26,PLT_EXCE_SOURCE);
            sm_notic_excep->noticode = GetNoticeCode();
            printf("get spa fpga version failed\n");
}
    sm_config_update->sys_flag_info = IXS_BatteryInfoAll | IXS_BoardTempAlarm;
    sm_config_update->top_flag_sys = IXT_System_Info;
    iBack = StartMultiWork();
    if(iBack < 0)
        {
            setNoticePara(1,2,7,PLT_EXCE_SOURCE);
            sm_notic_excep->noticode = GetNoticeCode();
            printf("engine up failed\n");
        }

    WhileFunc();
    ProRelease(NULL);
    //   FreeMemBuffer();
    //Albert 19-03-07 when ctrl exit, close all device.
    CloseApiDev();
    printf("system app has exit \n");
    return 0;
}

static DiInt32 WhileFunc(void)
{
    DiInt32 inum = 0;
    printf("system circle\n");
    while(gappexit.mainthreadExit)
        {
            usleep(500000);
            if(inum < 10)
                {
                    sm_config_update->sys_flag_info = IXS_BatteryInfoAll;
                    sm_config_update->top_flag_sys = IXT_System_Info;
                }
            else
                {
                    inum = 10;
                }
            inum++;
        }
    printf("gappexit.mainthreadExit is %d\n",gappexit.mainthreadExit);
    return 0;
}

static DiInt32 ProRelease(void* param)
{	
    //    ClosePlInterrupt();
    return BitClose(bitdevHandle);
}

static DiInt32 ObjIni(void)
{	
    //0925
    gappexit.acqthreadExit = 1;
    gappexit.listenthreadExit = 1;
    gappexit.mainthreadExit = 1;
    gappexit.midmsgthreadExit = 1;
    

    pmid_msg_thread	 = &mid_msg_thread;
    pmid_msg_thread->func = MidMsgFunc;

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
    return iBack;
}

//0810 steve
void ErrOutPut(DiInt32 errCode,DiInt32 itype)
{
    //   memset(errBuffer,0,Len);
    //    BitGetErrorInfo(errCode,LangType,errBuffer);
    //   printf("type:%d,err:%d, %s\n",itype,errCode,errBuffer);
    return;
}
