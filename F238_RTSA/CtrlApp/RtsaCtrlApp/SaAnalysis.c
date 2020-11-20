//==============================================================================
//
// Title:		SaAnalysis.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/1/20 at 11:34:57 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include "SaAnalysis.h"
#include "SaDataStruct.h"
#include "DigSigDealVirtualDriver.h"
#include "RfVirtualDriver.h"
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "CalcPointAlog.h"
#include "sweepinterupt.h"
#include "msgNoticeCode.h"
#include "BitSehInfo.h"

//==============================================================================
//==============================================================================
// Static functions
static void ListenEngine();
//==============================================================================
// Global variables	
DiSession bitdevHandle = 0;  
_CONFIG_RSA_CTRL localConfigRsaCtrl = {0};//just used in ctrl app

extern const DiReal64 freqChannelList[];
extern _SM_SYNC syncMana;
//share shm
extern PSWEEP_DATA sm_sweep_data;
extern PSM_SYNC sm_sync;
extern PCONFIG_RSA_CTRL sm_config_rsa_ctrl;
extern PCONFIG_UPDATE sm_config_update;
//===============================================================================
//change bityang,0323
static DiInt32 listState = 0;//1 means single sweep mode,and sweep is over
extern SWEEPCTRL CTRL_SWEEP_MODE;

FREQLIST bitFreqList;  
CALCRESULTLIST preOffCalcResult; //the buffer size is freqNum * ampNum + extraNum
CALCRESULTLIST preOnCalcResult;

//add amp ctrl,0424,by steve
double powerlistpoints[] = {10.0,5.0,0.0,-5.0,-10.0,-15.0,-20.0,-25.0,-30.0,-35.0};		//for source 
//-20 used in the off mode,from -20 to -50 ,20 as if ref
//-30 used also in the on mode,from -30 to -60,-30 as if ref
double powerlistpoint[] = {-20.0,-30,-40.0,-50.0,-60.0}; //for source 
double freqpoint = 100.0e6;//if gain calc

double powerlistpointsampoff[] = {10.0,5.0,0.0,-5.0,-10.0,-15.0,-20.0}; //for sa	source value 
double powerlistpointsampon[] = {-5.0,-10.0,-15.0,-20.0,-25.0,-30.0,-35.0}; //for sa

#ifdef BIT_F238
static DiReal64 FREQMAX = 43000000000.;
#endif
#ifdef BIT_F239
static DiReal64 FREQMAX = 43000000000.;
#endif
#ifdef BIT_F238_SMART
static DiReal64 FREQMAX = 15000000000.;
#endif


static int ProBufferForpreoff(PCALCRESULTLIST pbuffer,int iNum);
static int ProBufferForpreon(PCALCRESULTLIST pbuffer,int iNum);

static int GetpreOffAttenIndex(double refLevel);
static void GetStartAndStopIndex(double freqHz,int serStart,int* startIndex,int* stopIndex,int islastpoint);//islastpoint 0 means last point
static int GetAttenIndexOff(double attendB);
static int GetpreOnAttenIndex(double refLevel);
static int GetAttenIndexOn(double attendB);

//0426
extern DiInt32 reCtrlSweep;

static DiInt32 TimeStart;
static DiInt32 TimeStop;
int fileSave = 0;
typedef struct 
{
    double refLevel;
    double atten;
    double ifGain;
}CHANNELGAIN,*PCHANNELGAIN;

CHANNELGAIN ifGainOff[] = {{20,30,30},
                           {15,25,30},
                           {10,20,30},
                           {5,15,30},
                           {0,10,30},
                           {-5,5,30},
                           {-10,0,30}, //-10~-40 use the same data
                          };

CHANNELGAIN ifGainOn[] = {{0,30,30},
                          {-5,25,30},
                          {-10,20,30},
                          {-15,15,30},
                          {-20,10,30},
                          {-25,5,30},
                          {-30,0,30},
                         };
static void PassSweepParmFromShmToLocal();
//0428
extern int sweepHandle; 
void GetCtrlInHand(DiInt32 handle);
void ReleaseCtrlInHand(DiInt32 handle);
//0504
enum SWEEPSTAGE {NOLAST = 0,YESLAST = 1};
typedef enum {ADDRNOTCLEAR = 0,ADDRCLEAR = 1} CLEARFPGAADDR;

//0810 steve
extern void ErrOutPut(DiInt32 errCode,DiInt32 itype);
extern void ErrOutPutEx(DiInt32 ToLogFlag,DiInt32 ToShmFlag);

double gperinsertnum = 0.0;
double gperinsertfracpart = 0.0;
int gperinsertintpart = 0;

//0925
extern RSA_EXIT gappexit;

int SweepDoneFlag = 0;
extern int firstInterrupt;

DiInt32 lisIdleflag = 0;//0 means in idle state

//DiInt32 SweepType = 0;

PCHANNELTEMPLATE refpreofftemp = NULL;
PCHANNELTEMPLATE refpreontemp = NULL;
PCHANNELTEMPLATE refpreofferrtemp = NULL;
PCHANNELTEMPLATE refpreonerrtemp = NULL;
extern DiInt32 GetFreqChannelIndex(DiReal64 freqHz);
static PCHANNELTEMPLATE DecideErr(DiReal64 freqHz,PCHANNELTEMPLATE plist);

void* ListenAndDownSweepParamFunc(void *param)
{	
    do
        {
            if(SWEEP_CONTI == CTRL_SWEEP_MODE)
                {
               	   lisIdleflag = 1;
                    ListenEngine();
                }
            else if(SWEEP_SINGLE == CTRL_SWEEP_MODE)
                {
                   lisIdleflag = 1;
                    ListenEngine();
                    sm_config_rsa_ctrl->ListenState = OFF;
                    CTRL_SWEEP_MODE = SWEEP_IDLE;
                }
            else
                {
                    lisIdleflag = 0;
                    usleep(2000);
                }
        }
    //while(syncMana.AppExit);
    while(gappexit.listenthreadExit);
    gappexit.midmsgthreadExit = 0;
    return NULL;
}

static void ListenEngine()
{	
    DiInt32 iBack = 0;
    sm_config_rsa_ctrl->ListenState = ON;
    DiInt32 i = 0;
    DiInt32 interState = 0;
    if(syncMana.DeviceMsgUpdate)
        {           
            PassSweepParmFromShmToLocal(); 
            syncMana.DeviceMsgUpdate = !syncMana.DeviceMsgUpdate;           
        }   
      
    return;
}

static void PassSweepParmFromShmToLocal()
{   
    return;
}

extern DiInt32 guiHandle;
extern DiInt32 syncHandle;
//0426
#define MAXBUFFERSIZE 4001
DiReal64 acqLocBuffer[MAXBUFFERSIZE];
DiUInt32 acqb[MAXBUFFERSIZE];
DiPReal32 acqbNew;
DiReal32 acqbNewData[MAXBUFFERSIZE];
DiReal64 midCalcBuffer[MAXBUFFERSIZE];
extern DiInt32 reCalcflag; 
extern DiInt32 reCalcflag;
static void PassAcqParamFromShmToLocal();

static DiInt32 dCompare2(DiReal64 data1,DiReal64 data2);

extern DiReal64 localtempcalc;
extern DiInt32 temptrigflag;//1 means retrig
DiReal64 tempercalcbuffer[MAXBUFFERSIZE];
DiPReal64 pcalcdata;
#define ESP0 (1.0e-6)
DiInt32 dCompare2(DiReal64 data1,DiReal64 data2)
{
    DiReal64 diff=data1-data2;
    if(diff<=-ESP0)
        return -1;
    if((diff>-ESP0)&&(diff<ESP0))
        return 0;
    if(diff>=ESP0)
        return 1;
    return 0;
}

static void PassAcqParamFromShmToLocal();


void* AcqDataFunc(void *param)
{
do
{
			if(0 == sm_config_rsa_ctrl->SweepType)
                { 	
#if BIT_DEBUG      
lisIdleflag = 0;
                     AcqDataFuncSimu(NULL);
#else
lisIdleflag = 1;
AcqDataFuncPhy(NULL);
#endif
                }
            //single
            else if(1 == sm_config_rsa_ctrl->SweepType)
                { 	
#if BIT_DEBUG
	lisIdleflag = 0;
	AcqDataFuncSimu(NULL);   
#else    
	lisIdleflag = 1;
	AcqDataFuncPhy(NULL);
#endif                           
            		sm_config_rsa_ctrl->SweepType = 2;
                }
		else
		{
		lisIdleflag = 0;
		usleep(2000);
		}

         }while(gappexit.acqthreadExit);    
//    printf("acq data thread stop\n");
    gappexit.listenthreadExit = 0;
	gappexit.midmsgthreadExit = 0;
return NULL;
}

static DiReal64 tempsumcal = 0.0;
void* AcqDataFuncSimu(void *param)
{ 
	tempsumcal = 0.0;
    DiInt32 i = 0;
    DiReal64 iacp = 0.0;

    DiReal64 iphase = 0.0;
    DiInt32 ic = 0;
  
    DiInt32 ireflesh = 0;   
static int testi = 0;
                            if(1 == reCalcflag)
                                {
                                    PassAcqParamFromShmToLocal();
                                    ireflesh = 0;
                                }
                            memset(acqLocBuffer,0,localConfigRsaCtrl.TracePoint * 8);

                            iphase += 2.56/180*3.1415926;
                            if(iphase > 3.1415926)
                                iphase = 0;

                            for(i = 0;i<localConfigRsaCtrl.TracePoint ;i++)
                                {
                                    midCalcBuffer[i] = rand();
                                    midCalcBuffer[i] =-4 * log(midCalcBuffer[i]);//sin(2* 3.1415926535/80*i + iphase);// + sin(2*3.1415926535/10*i -iphase);
//midCalcBuffer[i] = sin(2* 3.1415926535/80*i + iphase) + sin(2*3.1415926535/10*i -iphase);
                                    acqLocBuffer[i] = midCalcBuffer[i];// * 10 - 70;
                                }
				testi = !testi;
				if(testi)
				{
				acqLocBuffer[300] += 60;
				}
				else
				{
				acqLocBuffer[300] += 10;
				}


				for(i = 267;i<277;i++ )
				{
				 acqLocBuffer[i] += 50;
				}


				for(i = 67;i<77;i++ )
				{
				 acqLocBuffer[i] += 42;
				}

				acqLocBuffer[489] += 72;          
				acqLocBuffer[799] += 72; 
				acqLocBuffer[1] += 72;  
                            GetCtrlInHand(syncHandle);
                            for(i = 0;i<localConfigRsaCtrl.TracePoint ;i++)
				{
                                sm_sweep_data->_PwrLevel[i] =  acqLocBuffer[i]; 
				}
                            ReleaseCtrlInHand(guiHandle); 
      
    return NULL;
}

void* AcqDataFuncPhy(void *param)
{
    DiInt32 i = 0;
    DiInt32 iBack = 0;
    DiUInt32 n1 = 0;
    DiUInt32 n2 = 0;
    DiUInt32 n3 = 0;
    DiUInt32 n4 = 0;
    DiUInt32 n5 = 0;
    DiInt32 ireflesh = 0;

    DiInt32 dataout = 0;
    DiUInt32 tempsum = 0;  
//                    if(1 == reCalcflag)
//                        {
//                            PassAcqParamFromShmToLocal();
//                            //means zero span mode,0503
//                            ireflesh = 0;
//                            //if(localConfigRsaCtrl.SPANMode)
//                           if(1)
//                                {
//                                    if(localConfigRsaCtrl.Preamp)
//                                        {
//                                        		if(reCtrlSweep)
//														return NULL;
//                                            GetCalcDataWhenPreAmpOnZeroSpan(localConfigRsaCtrl.CenterFreq,localConfigRsaCtrl.TracePoint,localConfigRsaCtrl.RefLevel,localConfigRsaCtrl.attenAuto,localConfigRsaCtrl.attenValue,midCalcBuffer);
//                                        }
//                                    else
//                                        {
//                                               if(reCtrlSweep)
//														return NULL;
//                                            GetCalcDataWhenPreAmpOffZeroSpan(localConfigRsaCtrl.CenterFreq,localConfigRsaCtrl.TracePoint,localConfigRsaCtrl.RefLevel,localConfigRsaCtrl.attenAuto,localConfigRsaCtrl.attenValue,midCalcBuffer);
//                                        }
//                                }
//                            else
//                                {
//                                    if(localConfigRsaCtrl.Preamp)
//                                        {
//                                              if(reCtrlSweep)
//														return NULL;
//                                            GetCalcDataWhenPreAmpOn(localConfigRsaCtrl.StartFreq,localConfigRsaCtrl.StopFreq,localConfigRsaCtrl.TracePoint,localConfigRsaCtrl.attenAuto,localConfigRsaCtrl.attenValue,midCalcBuffer);
//                                        }
//                                    //preamp is off
//                                    else
//                                        {
//                                            if(reCtrlSweep)
//														return NULL;
//                                            GetCalcDataWhenPreAmpOff(localConfigRsaCtrl.StartFreq,localConfigRsaCtrl.StopFreq,localConfigRsaCtrl.TracePoint,localConfigRsaCtrl.attenAuto,localConfigRsaCtrl.attenValue,midCalcBuffer);
//                                        }
//                                }
//                            reCalcflag = 0;
//                        }
	                   if(reCtrlSweep)
							return NULL;
//                    iBack =  GetResultData(bitdevHandle,acqb,localConfigRsaCtrl.TracePoint);
					//acqbNew = (DiReal32*)&acqb;		
					GetCtrlInHand(sweepHandle);
						iBack = GetResultFloatData(bitdevHandle, acqbNewData, localConfigRsaCtrl.TracePoint);
						for(i = 0;i < localConfigRsaCtrl.TracePoint;i++)
                        {
//								midCalcBuffer[i] = 20 * log10(*(acqbNewData + i) + 0.000001) - 200;
								midCalcBuffer[i] = 20 * log10(*(acqbNewData + i)+ 0.00000000000000000001);
                            acqLocBuffer[i] = midCalcBuffer[i] ;
                        }
                    GetCtrlInHand(syncHandle);
						//Albert 19/04/26
						//here must wait DPX interrupt, or data refresh unsync
                    memcpy(sm_sweep_data->_PwrLevel,acqLocBuffer,localConfigRsaCtrl.TracePoint << 3);
                    ReleaseCtrlInHand(guiHandle);
					  firstInterrupt = 0;
    return NULL;
}

 static void PassAcqParamFromShmToLocal()
{
    localConfigRsaCtrl.Preamp = sm_config_rsa_ctrl->Preamp;
    localConfigRsaCtrl.StartFreq = sm_config_rsa_ctrl->StartFreq;
    localConfigRsaCtrl.StopFreq = sm_config_rsa_ctrl->StopFreq;
    localConfigRsaCtrl.attenAuto = sm_config_rsa_ctrl->attenAuto;
    localConfigRsaCtrl.attenValue = sm_config_rsa_ctrl->attenValue;
    //0503
    localConfigRsaCtrl.CenterFreq = sm_config_rsa_ctrl->CenterFreq; 
	localConfigRsaCtrl.SpanFreq = sm_config_rsa_ctrl->SpanFreq;
	localConfigRsaCtrl.RBW = sm_config_rsa_ctrl->RBW;
	localConfigRsaCtrl.flitertype = sm_config_rsa_ctrl->flitertype;
    return;
}
typedef struct
{
    DiReal64 isa;
    DiInt32 iIndex;
    DiReal64 dfreq;
    DiReal64 damp;
}SINGLE_POI;
extern DiInt32 GetFreqlistNum();
DiInt32 twicenum = 0;
DiInt32 LoadCalibrateDatas()
{
    SINGLE_POI sinpoi;
    char pPath[256] = {0};
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

    int iBack = GetParamFromFile(pPath,&bitFreqList);
    if(iBack < 0)
        return iBack;

    memset(pPath,0,256);
    getcwd(pPath, 256);
#ifdef BIT_F238
    strcat(pPath,"/saflatcalcresult.fla");
#endif

#ifdef BIT_F239
   strcat(pPath,"/saflatcalcresult_239.fla");
#endif

#ifdef BIT_F238_SMART
   strcat(pPath,"/saflatcalcresult_238_smart.fla");
#endif
    FILE *fp;
    fp = fopen(pPath, "rb");
    if (NULL == fp)
        {
            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,RTSA_CTL_CAL_FILE);
			 ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_ENABLE);
#if ERR_PRINT_DEBUG
        	printf("calibrate file open failed!!\n");
#endif
            return -1;
        }

    int iampNum = sizeof(powerlistpointsampoff) / sizeof(DiReal64);
    int iBsize = iampNum * bitFreqList.count;
    iBack = ProBufferForpreoff(&preOffCalcResult,iBsize);
    if(iBack < 0)
        return iBack;

    DiInt32 i = 0;
    for(i = 0;i < iBsize;i++)
        {
            fread(&sinpoi,sizeof(SINGLE_POI),1,fp);
            *(preOffCalcResult.param + i) = sinpoi.damp;
        }

    iampNum = sizeof(powerlistpointsampon) / sizeof(DiReal64);
    iBsize = bitFreqList.count * iampNum;
    iBack = ProBufferForpreon(&preOnCalcResult,iBsize);
    if(iBack < 0)
        return iBack;

    for(i = 0;i < iBsize;i++)
        {
            fread(&sinpoi,sizeof(SINGLE_POI),1,fp);
            *(preOnCalcResult.param + i) = sinpoi.damp;
        }

    fclose(fp);
    //get temper calc datas
    memset(pPath,0,256);
    getcwd(pPath, 256);
#ifdef BIT_F238
strcat(pPath,"/tempercalc.fla");
#endif
#ifdef BIT_F239
strcat(pPath,"/tempercalc_239.fla");
#endif
#ifdef BIT_F238_SMART
strcat(pPath,"/tempercalc_238_smart.fla");
#endif
//    strcat(pPath,"/tempercalc.fla");

    fp = fopen(pPath, "r");
    if (NULL == fp)
        {
            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,RTSA_CTL_TEMP_CAL_FILE);
			 ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_ENABLE);
#if ERR_PRINT_DEBUG
        printf("temper file open failed!!\n");
#endif
            return -1;
        }
    iampNum = 0;
    DiReal64 wh;
    while(!feof(fp))
        {
            fscanf(fp,"%lf",&wh);
            iampNum++;
        };
    rewind(fp);
    iampNum--;
    twicenum = (iampNum >> 1);
    pcalcdata = (DiPReal64)malloc(sizeof(DiReal64) * iampNum);
    if(pcalcdata)
        {
            for(i = 0;i < iampNum;i++)
                {
                    fscanf(fp,"%lf",pcalcdata + i);
                }
        }
    fclose(fp);

    refpreofftemp = (PCHANNELTEMPLATE)malloc(sizeof(CHANNELTEMPLATE) * twicenum);
#ifdef BIT_F238
    fp = fopen("rtsareftemplate.fla","rb");
#endif

#ifdef BIT_F239
    fp = fopen("rtsareftemplate_239.fla","rb");
#endif

#ifdef BIT_F238_SMART
    fp = fopen("rtsareftemplate_238_smart.fla","rb");
#endif

    for(i = 0;i < twicenum;i++)
        {
            fread(refpreofftemp + i,sizeof(CHANNELTEMPLATE),1,fp);
        }

    refpreontemp = (PCHANNELTEMPLATE)malloc(sizeof(CHANNELTEMPLATE) * twicenum);
    for(i = 0;i < twicenum;i++)
        {
            fread(refpreontemp  + i,sizeof(CHANNELTEMPLATE),1,fp);
        }
    fclose(fp);
#ifdef BIT_F238
    fp = fopen("rtsaerrtemplate.fla","rb");
#endif

#ifdef BIT_F239
    fp = fopen("rtsaerrtemplate_239.fla","rb");
#endif

#ifdef BIT_F238_SMART
    fp = fopen("rtsaerrtemplate_238_smart.fla","rb");
#endif
    refpreofferrtemp = (PCHANNELTEMPLATE)malloc(sizeof(CHANNELTEMPLATE));
    size_t ibytenum = fread(refpreofferrtemp,sizeof(CHANNELTEMPLATE),1,fp);
    PCHANNELTEMPLATE tmpNow;
    PCHANNELTEMPLATE lastp;
    if(ibytenum)
        {
            DiInt32 n = 0;
            tmpNow = refpreofferrtemp;
            i = 0;
            while(!feof(fp) && !tmpNow->preswitch)
                {
                    tmpNow->pndata = (PCHANNELTEMPLATE)malloc(sizeof(CHANNELTEMPLATE));
                    tmpNow = tmpNow->pndata;
                    if(0 == fread(tmpNow,sizeof(CHANNELTEMPLATE),1,fp))
                        {
                            lastp = tmpNow;
                            lastp->pndata = NULL;
                            free(tmpNow);
                            tmpNow = lastp;
                        }
                    else
                        {
                            lastp = tmpNow;
                            tmpNow->pndata = NULL;
                            i++;
                        }
                }

            if(i > 0)
                {
                    refpreonerrtemp = tmpNow;
                    tmpNow = refpreofferrtemp;
                    for(n = 0;n < i - 1;n++)
                        {
                            tmpNow = tmpNow->pndata;
                        }
                    tmpNow->pndata = NULL;
                    tmpNow = refpreonerrtemp;
                    tmpNow->pndata = NULL;

                    while(!feof(fp) && tmpNow->preswitch)
                        {
                            tmpNow->pndata = (PCHANNELTEMPLATE)malloc(sizeof(CHANNELTEMPLATE));
                            tmpNow = tmpNow->pndata;
                            if(0 == fread(tmpNow,sizeof(CHANNELTEMPLATE),1,fp))
                                {
                                    free(tmpNow);
                                    tmpNow = lastp;
                                    tmpNow->pndata = NULL;
                                }
                            else
                                {
                                    lastp = tmpNow;
                                    tmpNow->pndata = NULL;
                                }
                        }
                }
        }
		else
			{
			  free(refpreofferrtemp);
				refpreofferrtemp = NULL;
			}

    rewind(fp);
    fclose(fp);

    return 0;
}

DiInt32 GetSpanCalcDatasPreOff(DiReal64 freqHz,DiReal64 fspan,DiInt32 datanum,DiInt32 atflag,DiReal64 atten,DiPReal32 calcresult)
{
    PCHANNELTEMPLATE ph;
    DiInt32 i = 0;
    if(fspan > 60000000)
        {
            ph = DecideErr(freqHz,refpreofferrtemp);
            if(ph)
                {
                   for(i = 0;i < datanum;i++)
                        {
                            *(calcresult + i) = ph->ampbuf[i];
                        }
                }
            else
                {
                   DiInt32 iIndex = GetFreqChannelIndex(freqHz);
                    for(i = 0;i < datanum;i++)
                        {
                            *(calcresult + i) = (refpreofftemp + iIndex - 1)->ampbuf[i];
                        }
                }
        }
    else
        {
          DiInt32 iIndex = GetFreqChannelIndex(freqHz);
            DiInt32 imulti = ((DiInt32)(fspan / 100000000 * 801) >> 1);
            if(imulti <= 1)
                {
                    for(i = 0;i < datanum;i++)
                        {
                            *(calcresult + i) = (refpreofftemp + iIndex - 1)->ampbuf[400];
                        }
                    return 0;
                }
            else
                {
                    DiReal64 itom = 400. / imulti;
                    DiInt32 iuint = (DiInt32)itom;
                    DiReal64 fracpart = itom - iuint;
                    DiInt32 j = 0;
                    DiInt32 intpart = 0;
                    DiReal64 ifrac = 0.0;
                    DiInt32 itsum = 0;
                    for(i = 0;i < imulti;i++)
                        {
                            ifrac += fracpart;
                            if(ifrac - 1.0 > -1.0e-6)
                                {
                                    ifrac -= 1.0;
                                    intpart = iuint + 1;
                                }
                            else
                                {
                                    intpart = iuint;
                                }
                            for(j = 0;j < intpart;j++)
                                {
                                    *(calcresult + j + itsum) = (refpreofftemp + iIndex - 1)->ampbuf[400 - imulti + i];
                                    *(calcresult + j + itsum + 401) = (refpreofftemp + iIndex - 1)->ampbuf[401 + i];
                                }
                                itsum += intpart;
                        }
                }
            *(calcresult + 400) = (refpreofftemp + iIndex - 1)->ampbuf[400];
        }
    return 0;
}

DiInt32 GetSpanCalcDatasPreOn(DiReal64 freqHz,DiReal64 fspan,DiInt32 datanum,DiInt32 atflag,DiReal64 atten,DiPReal32 calcresult)
{
    PCHANNELTEMPLATE ph;
    DiInt32 i = 0;
    if(fspan > 60000000)
        {
            ph = DecideErr(freqHz,refpreonerrtemp);
            if(ph)
                {
                    for(i = 0;i < datanum;i++)
                        {
                            *(calcresult + i) = ph->ampbuf[i];
                        }
                }
            else
                {
                    DiInt32 iIndex = GetFreqChannelIndex(freqHz);
                    for(i = 0;i < datanum;i++)
                        {
                            *(calcresult + i) = (refpreontemp + iIndex - 1)->ampbuf[i];
                        }
                }
        }
    else
        {
            DiInt32 iIndex = GetFreqChannelIndex(freqHz);
            DiInt32 imulti = ((DiInt32)(fspan / 100000000 * 801) >> 1);
            if(imulti <= 1)
                {
                    for(i = 0;i < datanum;i++)
                        {
                            *(calcresult + i) = (refpreontemp + iIndex - 1)->ampbuf[400];
                        }
                    return 0;
                }
            else
                {
                    DiReal64 itom = 400. / imulti;
                    DiInt32 iuint = (DiInt32)itom;
                    DiReal64 fracpart = itom - iuint;
                    DiInt32 j = 0;
                    DiInt32 intpart = 0;
                    DiReal64 ifrac = 0.0;
                    DiInt32 itsum = 0;
                    for(i = 0;i < imulti;i++)
                        {
                            ifrac += fracpart;
                            if(ifrac - 1.0 > -1.0e-6)
                                {
                                    ifrac -= 1.0;
                                    intpart = iuint + 1;
                                }
                            else
                                {
                                    intpart = iuint;
                                }
                            for(j = 0;j < itom;j++)
                                {
                                    *(calcresult + j + itsum) = (refpreontemp + iIndex - 1)->ampbuf[400 - imulti + i];
                                    *(calcresult + j + itsum + 401) = (refpreontemp + iIndex - 1)->ampbuf[401 + i];
                                }
                            itsum += intpart;
                        }
                }
            *(calcresult + 400) = (refpreontemp + iIndex - 1)->ampbuf[400];
        }
    return 0;
}

static PCHANNELTEMPLATE DecideErr(DiReal64 freqHz,PCHANNELTEMPLATE plist)
{
    PCHANNELTEMPLATE ph = plist;
	if(NULL == plist)
		{
		   return NULL;
		}
    while(ph->pndata)
        {
            if(freqHz < ph->freq + 10000000 && freqHz > ph->freq - 10000000)
                {
                    return ph;
                }
            ph = ph->pndata;
        }
    return NULL;
}


static int ProBufferForpreoff(PCALCRESULTLIST pbuffer,int iNum)
{
    return ResizeArray((ArrayHandle)pbuffer, iNum);
}

static int ProBufferForpreon(PCALCRESULTLIST pbuffer,int iNum)
{
    return ResizeArray((ArrayHandle)pbuffer, iNum);
}

DiInt32 FreeMemBuffer()
{	
    if(bitFreqList.param != NULL)
        {
            free(preOnCalcResult.param);
            preOnCalcResult.param = NULL;
        }
    if(preOffCalcResult.param != NULL)
        {
            free(preOnCalcResult.param);
            preOnCalcResult.param = NULL;
        }
    if(preOnCalcResult.param != NULL)
        {
            free(preOnCalcResult.param);
            preOnCalcResult.param = NULL;
        }
	if(pcalcdata != NULL)
        {
            free(pcalcdata);
            pcalcdata = NULL;
        }
    return 0;
}

static double lastifgain = 30.0;//save last ifgain value for man mode

double tempREF = 0.0;

static const double ATTENZERODOORWHENOFF = -10.0;
//static const double ATTENZERODOORWHENOFF = -5.0;
static const double ATTENZEROWHENOFF = -10.0;
static const double IFGAINMINWHENOFF = -40.0;
static const double REFWITHOUTHARDWHENOFF = -70.0;

static const double IFGAINMIN = 30.0;
static const int ZEROATTENUM = 4;
//when set refLevel or atten,the mid msg object will do hardware ctrl,
//and trig the action to get the calc data again;	

DiInt32 GetCalcDataWhenPreAmpOff(double startfreq,double stopfreq,int datanum,int autoflag,double manatten,double* calcresult)
{
    autoflag = !!autoflag;
    double mstep = (stopfreq - startfreq) / (datanum - 1);
    double mfreq = 0.0;
    double mfdeta = 0.0;
    int i = 0,istart = 0,istop = 0;
    int iBack = 0;
    tempREF = localConfigRsaCtrl.RefLevel;
    //means set atten and IF gain auto
    if(autoflag)
        {
            int index0,index1 = 0;
            int setchannelIndex = 0;
            double deta = 0.0;

            //means will used -10dB datas
            if(tempREF <= ATTENZERODOORWHENOFF)
                {
                    index0 = GetpreOffAttenIndex(ATTENZEROWHENOFF);
                    setchannelIndex = index0;
                    int icalcIndex0 = bitFreqList.count * index0;
                    if(tempREF >= IFGAINMINWHENOFF)
                        {
                            //means deta value is 0,direct use calc datas
                            //Linear interpolation for filling datas
                            for(i = 0; i < datanum; i++)
                                {
                                    //get freq location,start index and stop index
                                    mfreq = startfreq + i * mstep;
                                    GetStartAndStopIndex(mfreq,istart,&istart,&istop,(i + 1) % datanum);
                                    mfdeta = mfreq - *(bitFreqList.param + istart);
                                    calcresult[i] = mfdeta * (*(preOffCalcResult.param + icalcIndex0 + istop)  - *(preOffCalcResult.param + icalcIndex0 + istart))
                                            / (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOffCalcResult.param + icalcIndex0 + istart);
                                }
                        }
                    else
                        {
                            tempREF = tempREF <= REFWITHOUTHARDWHENOFF ? REFWITHOUTHARDWHENOFF : tempREF;
                            index1 = GetpreOffAttenIndex(tempREF);
                            setchannelIndex = index1;
                            //ref at -10dB,and freq at 100MHz,get IFgain deta value
                            deta = *(preOffCalcResult.param + preOffCalcResult.count - 1 - ZEROATTENUM + index1 - index0)
                                    - *(preOffCalcResult.param + preOffCalcResult.count - 1 - ZEROATTENUM);
                            for(i = 0; i < datanum; i++)
                                {
                                    mfreq = startfreq + i * mstep;
                                    GetStartAndStopIndex(mfreq,istart,&istart,&istop,(i + 1) % datanum);
                                    mfdeta = mfreq - *(bitFreqList.param + istart);
                                    calcresult[i] = deta + mfdeta * (*(preOffCalcResult.param + icalcIndex0 + istop)  - *(preOffCalcResult.param + icalcIndex0 + istart))
                                            / (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOffCalcResult.param + icalcIndex0 + istart);
                                }
                        }
                }
            else
                {
                    index0 = GetpreOffAttenIndex(tempREF);
                    int icalcIndex0 = bitFreqList.count * index0;
                    setchannelIndex = index0;
                    for(i = 0; i < datanum; i++)
                        {
                            //get freq location,start index and stop index
                            mfreq = startfreq + i * mstep;
                            GetStartAndStopIndex(mfreq,istart,&istart,&istop,(i + 1) % datanum);
                            mfdeta = mfreq - *(bitFreqList.param + istart);
                            calcresult[i] = mfdeta * (*(preOffCalcResult.param + icalcIndex0 + istop)  - *(preOffCalcResult.param + icalcIndex0 + istart))
                                    / (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOffCalcResult.param + icalcIndex0 + istart);
                        }
                }

#if Y
            //set IFgain,pre amp off and atten
            iBack = IFGainCtrl(bitdevHandle,ifGainOff[setchannelIndex].ifGain);
            if(iBack < 0)
                {
						setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
						ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
                    return iBack;
                }
            iBack = PreAmpliChannelCtrl(bitdevHandle,0);
            if(iBack < 0)
                {
						setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
						ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
                    return iBack;
                }
            iBack = PreAttenCtrl(bitdevHandle,ifGainOff[setchannelIndex].atten);
            if(iBack < 0)
                {
						setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
						ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
                    return iBack;
                }
#endif	
            lastifgain = ifGainOff[setchannelIndex].ifGain;
        }
    //in the man mode,means only set atten,and ref\ifgain not change
    else
        {
            //calc needed calc datas
            //use lastatten and now atten to get the deta datas
            int inowindex = GetAttenIndexOff(manatten);
            int detaindex = (int)((lastifgain - IFGAINMIN) / 10.0 + 0.5);
            double mgain = 0.0;
            if(detaindex != 0)
                {
                    mgain = *(preOffCalcResult.param + preOffCalcResult.count - 1 - ZEROATTENUM + detaindex)
                            - *(preOffCalcResult.param + preOffCalcResult.count - 1 - ZEROATTENUM);
                }

            int icalcIndex0 = bitFreqList.count * inowindex;
            for(i = 0; i < datanum; i++)
                {
                    mfreq = startfreq + i * mstep;
                    GetStartAndStopIndex(mfreq,istart,&istart,&istop,(i + 1) % datanum);
                    mfdeta = mfreq - *(bitFreqList.param + istart);
                    //calcdata
                    calcresult[i] = mgain + mfdeta * (*(preOffCalcResult.param + icalcIndex0 + istop)  - *(preOffCalcResult.param + icalcIndex0 + istart))
                            / (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOffCalcResult.param + icalcIndex0 + istart);
                }

#if Y
            iBack = PreAttenCtrl(bitdevHandle,manatten);
            if(iBack < 0)
                {
						setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
						ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
                    return iBack;
                }
            //only set sa pre atten and pre amp off
            iBack = PreAmpliChannelCtrl(bitdevHandle,0);
            if(iBack < 0)
                {
						setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
						ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
                    return iBack;
                }
#endif
        }
    return 0;
} 

static const double ATTENZERODOORWHENON = -30.0;
//static const double ATTENZERODOORWHENON = -25.0;
static const double ATTENZEROWHENON = -30.0;
static const double IFGAINMINWHENON = -40.0;
static const double REFWITHOUTHARDWHENON = -70.0;

//20180420
DiInt32 GetCalcDataWhenPreAmpOn(double startfreq,double stopfreq,int datanum,int autoflag,double manatten,double* calcresult)
{
    autoflag = !!autoflag;
    double mstep = (stopfreq - startfreq) / (datanum - 1);
    double mfreq = 0.0;
    double mfdeta = 0.0;
    int i = 0,istart = 0,istop = 0;
    int iBack = 0;
    tempREF = localConfigRsaCtrl.RefLevel;
    //means set atten and IF gain auto
    if(autoflag)
        {
            int index0,index1 = 0;
            int setchannelIndex = 0;
            double deta = 0.0;

            //means will used -10dB datas
            if(tempREF <= ATTENZERODOORWHENON)
                {
                    index0 = GetpreOnAttenIndex(ATTENZEROWHENON);
                    setchannelIndex = index0;
                    int icalcIndex0 = bitFreqList.count * index0;
                    if(tempREF >= IFGAINMINWHENON)
                        {
                            //means deta value is 0,direct use calc datas
                            //Linear interpolation for filling datas
                            for(i = 0; i < datanum; i++)
                                {
                                    //get freq location,start index and stop index
                                    mfreq = startfreq + i * mstep;
                                    GetStartAndStopIndex(mfreq,istart,&istart,&istop,(i + 1) % datanum);
                                    mfdeta = mfreq - *(bitFreqList.param + istart);
                                    calcresult[i] = mfdeta * (*(preOnCalcResult.param + icalcIndex0 + istop)  - *(preOnCalcResult.param + icalcIndex0 + istart))
                                            / (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOnCalcResult.param + icalcIndex0 + istart);
                                }
                        }
                    else
                        {
                            tempREF = tempREF <= REFWITHOUTHARDWHENON ? REFWITHOUTHARDWHENON : tempREF;
                            index1 = GetpreOnAttenIndex(tempREF);
                            setchannelIndex = index1;
                            //ref at -10dB,and freq at 100MHz,get IFgain deta value
                            deta = *(preOnCalcResult.param + preOnCalcResult.count - 1 - ZEROATTENUM + index1 - index0)
                                    - *(preOnCalcResult.param + preOnCalcResult.count - 1 - ZEROATTENUM);
                            for(i = 0; i < datanum; i++)
                                {
                                    mfreq = startfreq + i * mstep;
                                    GetStartAndStopIndex(mfreq,istart,&istart,&istop,(i + 1) % datanum);
                                    mfdeta = mfreq - *(bitFreqList.param + istart);
                                    calcresult[i] = deta + mfdeta * (*(preOnCalcResult.param + icalcIndex0 + istop)  - *(preOnCalcResult.param + icalcIndex0 + istart))
                                            / (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOnCalcResult.param + icalcIndex0 + istart);
                                }
                        }
                }
            else
                {
                    index0 = GetpreOnAttenIndex(tempREF);
                    int icalcIndex0 = bitFreqList.count * index0;
                    setchannelIndex = index0;
                    for(i = 0; i < datanum; i++)
                        {
                            //get freq location,start index and stop index
                            mfreq = startfreq + i * mstep;
                            GetStartAndStopIndex(mfreq,istart,&istart,&istop,(i + 1) % datanum);
                            mfdeta = mfreq - *(bitFreqList.param + istart);
                            calcresult[i] = mfdeta * (*(preOnCalcResult.param + icalcIndex0 + istop)  - *(preOnCalcResult.param + icalcIndex0 + istart))
                                    / (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOnCalcResult.param + icalcIndex0 + istart);
                        }
                }

#if Y
            //set IFgain,pre amp on and atten
            iBack = IFGainCtrl(bitdevHandle,ifGainOn[setchannelIndex].ifGain);
            if(iBack < 0)
                {
						setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
						ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
                    return iBack;
                }
            iBack = PreAmpliChannelCtrl(bitdevHandle,1);
            if(iBack < 0)
                {
						setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
						ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
                    return iBack;
                }
            iBack = PreAttenCtrl(bitdevHandle,ifGainOn[setchannelIndex].atten);
            if(iBack < 0)
                {
						setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
						ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
                    return iBack;
                }
#endif	
            lastifgain = ifGainOn[setchannelIndex].ifGain;
        }
    //in the man mode,means only set atten,and ref\ifgain not change
    else
        {
            //calc needed calc datas
            //use lastatten and now atten to get the deta datas
            int inowindex = GetAttenIndexOn(manatten);
            int detaindex = (int)((lastifgain - IFGAINMIN) / 10.0 + 0.5);
            double mgain = 0.0;
            if(detaindex != 0)
                {
                    mgain = *(preOnCalcResult.param + preOnCalcResult.count - 1 - ZEROATTENUM + detaindex)
                            - *(preOnCalcResult.param + preOnCalcResult.count - 1 - ZEROATTENUM);
                }

            int icalcIndex0 = bitFreqList.count * inowindex;
            for(i = 0; i < datanum; i++)
                {
                    mfreq = startfreq + i * mstep;
                    GetStartAndStopIndex(mfreq,istart,&istart,&istop,(i + 1) % datanum);
                    mfdeta = mfreq - *(bitFreqList.param + istart);
                    //calcdata
                    calcresult[i] = mgain + mfdeta * (*(preOnCalcResult.param + icalcIndex0 + istop)  - *(preOnCalcResult.param + icalcIndex0 + istart))
                            / (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOnCalcResult.param + icalcIndex0 + istart);
                }

#if Y
            iBack = PreAttenCtrl(bitdevHandle,manatten);
            if(iBack < 0)
                {
						setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
						ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
                    return iBack;
                }
            //only set sa pre atten and pre amp on
            iBack = PreAmpliChannelCtrl(bitdevHandle,1);
            if(iBack < 0)
                {
						setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
						ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
                    return iBack;
                }
#endif
        }
    return 0;
}

static void GetStartAndStopIndex(double freqHz,int serStart,int* startIndex,int* stopIndex,int islastpoint)
{   
    int i = 0,j = 0;
    int ilen = 14;
    for(i = serStart;i < bitFreqList.count;i++)
        {
            if(freqHz <= *(bitFreqList.param + i))
                {
                    if(0 == i)
                        {
                            *startIndex = 0;
                            *stopIndex = 1;
                            return;
                        }
                    else
                        {
                            *startIndex = i -1;
                            if(islastpoint)
                                {
                                    for(j = 0; j < ilen; j++)
                                        {
                                            if(freqHz == freqChannelList[j])
                                                {
                                                    *startIndex = i + 1;
                                                    break;
                                                }
                                        }
                                }
                            *stopIndex = *startIndex + 1;
                            return;
                        }
                }
        }
    return;
}

static int GetpreOffAttenIndex(double refLevel)
{
    int iSum = sizeof(ifGainOff) / sizeof(CHANNELGAIN);
    int i = 0;
    for(i = 0;i < iSum;i++)
        {
            if(refLevel > ifGainOff[i].refLevel)
	   {
		i -= 1;
		if(i < 0)
			i = 0;
             return i;
	    }
        }
    //means the ref is very small,the if gain should set 60dB and atten set 0dB
    return iSum - 1;
}

static int GetpreOnAttenIndex(double refLevel)
{
    int iSum = sizeof(ifGainOn) / sizeof(CHANNELGAIN);
    int i = 0;
    for(i = 0;i < iSum;i++)
        {
            if(refLevel >= ifGainOn[i].refLevel)
		{
			i -= 1;
		if(i < 0)
		i = 0;
                return i;
		}               
        }
    //means the ref is very small,the if gain should set 60dB and atten set 0dB
    return iSum - 1;
}

static int GetAttenIndexOff(double attendB)
{  
    int iSum = sizeof(ifGainOff) / sizeof(CHANNELGAIN);
    int i = 0;
    for(i = 0;i < iSum;i++)
        {
            if(attendB >= ifGainOff[i].atten)
                return i;
        }
    return -1;
}

static int GetAttenIndexOn(double attendB)
{  
    int iSum = sizeof(ifGainOn) / sizeof(CHANNELGAIN);
    int i = 0;
    for(i = 0;i < iSum;i++)
        {
            if(attendB >= ifGainOn[i].atten)
                return i;
        }
    return -1;
}

void GetCtrlInHand(DiInt32 handle)
{
    struct sembuf s;
    s.sem_num=0;
    s.sem_op=-1;
    s.sem_flg=0;
    if(semop(handle,&s,1)<0)
        {
//            printf("op errro,%d:%s",errno,strerror(errno));
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
//            printf("op error,%d:%s",errno,strerror(errno));
        }
    return;
}

//0503
//0504
DiInt32 GetCalcDataWhenPreAmpOffZeroSpan(DiReal64 freq,DiInt32 datanum,DiReal64 refl,DiInt32 autoflag,DiReal64 manatten,DiReal64* calcresult)
{
    autoflag = !!autoflag;
    DiReal64 mfreq = freq;
    DiReal64 mfdeta = 0.0;
    int istart = 0,istop = 0;    
    //means set atten and IF gain auto
    int ioverflow = 0;//when un 0 means freq is over the largest freq;

    DiReal64 ideta = 0.0;
    if(autoflag)
        {
            int index0;
            int setchannelIndex = 0;

            //means will used -10dB datas
            if(refl <= ATTENZERODOORWHENOFF)
                {
                    index0 = GetpreOffAttenIndex(ATTENZEROWHENOFF);
                    setchannelIndex = index0;
#if ERR_PRINT_DEBUG										
						printf("setchannelIndex     %d\n",setchannelIndex);
#endif
                    int icalcIndex0 = bitFreqList.count * index0;

                    //means deta value is 0,direct use calc datas
                    //Linear interpolation for filling datas
                    GetStartAndStopIndex(mfreq,istart,&istart,&istop,0);
                    mfdeta = mfreq - *(bitFreqList.param + istart);
#if ERR_PRINT_DEBUG										
						printf("mfdeta     %f\n",mfdeta);
#endif
                    if(0 == ioverflow)
                        {
                            if(mfreq >= FREQMAX)
                                {
                                    ioverflow = istart - 1;
                                }
                        }
                    if(mfdeta < 0.0)
                        {
                            calcresult[0] = *(preOffCalcResult.param + icalcIndex0 + istart);
                        }
                    else if(mfreq >= FREQMAX)
                        {
                            calcresult[0] = *(preOffCalcResult.param + icalcIndex0 + ioverflow);
                        }
                    else
                        {
                            calcresult[0] = mfdeta * (*(preOffCalcResult.param + icalcIndex0 + istop)  - *(preOffCalcResult.param + icalcIndex0 + istart))
                                    / (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOffCalcResult.param + icalcIndex0 + istart);
                        }
                }
            else
                {
                    index0 = GetpreOffAttenIndex(refl);                    
                    int icalcIndex0 = bitFreqList.count * index0;
                    setchannelIndex = index0;
#if ERR_PRINT_DEBUG										
						printf("setchannelIndex     %d\n",setchannelIndex);
#endif
                    //get freq location,start index and stop index
                    GetStartAndStopIndex(mfreq,istart,&istart,&istop,0);
                    mfdeta = mfreq - *(bitFreqList.param + istart);
#if ERR_PRINT_DEBUG										
										printf("mfdeta     %f\n",mfdeta);
#endif
                    if(0 == ioverflow)
                        {
                            if(mfreq >= FREQMAX)
                                {
                                    ioverflow = istart - 1;
                                }
                        }
                    if(mfdeta < 0.0)
                        {
                            calcresult[0] = *(preOffCalcResult.param + icalcIndex0 + istart);
                        }
                    else if(mfreq >= FREQMAX)
                        {
                            calcresult[0] = *(preOffCalcResult.param + icalcIndex0 + ioverflow);
                        }
                    else
                        {
                            calcresult[0] = mfdeta * (*(preOffCalcResult.param + icalcIndex0 + istop)  - *(preOffCalcResult.param + icalcIndex0 + istart))
                                    / (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOffCalcResult.param + icalcIndex0 + istart);
                        }
                }

        }
    //in the man mode,means only set atten,and ref\ifgain not change
    else
        {
            //calc needed calc datas
            //use lastatten and now atten to get the deta datas
            int inowindex = GetAttenIndexOff(manatten);
            ideta = manatten - 30.0;
            if(ideta <= 0.0)
                {
                    ideta = 0.0;
                }
            int icalcIndex0 = bitFreqList.count * inowindex;

            GetStartAndStopIndex(mfreq,istart,&istart,&istop,0);
            mfdeta = mfreq - *(bitFreqList.param + istart);
            if(0 == ioverflow)
                {
                    if(mfreq >= FREQMAX)
                        {
                            ioverflow = istart - 1;
                        }
                }
            if(mfdeta < 0.0)
                {
                    calcresult[0] = *(preOffCalcResult.param + icalcIndex0 + istart);
                }
            else if(mfreq >= FREQMAX)
                {
                    calcresult[0] = *(preOffCalcResult.param + icalcIndex0 + ioverflow);
                }
            else
                {
                    //calcdata
                    calcresult[0] = mfdeta * (*(preOffCalcResult.param + icalcIndex0 + istop)  - *(preOffCalcResult.param + icalcIndex0 + istart))
                            / (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOffCalcResult.param + icalcIndex0 + istart);
                }

        }
    int i = 1;
    calcresult[0] -= ideta;
    for(i = 1; i < datanum; i++ )
        {
            calcresult[i] = calcresult[0];
        }
    return 0;
}


DiInt32 GetCalcDataWhenPreAmpOnZeroSpan(DiReal64 freq,DiInt32 datanum,DiReal64 refl,DiInt32 autoflag,DiReal64 manatten,DiReal64* calcresult)
{
    autoflag = !!autoflag;
    DiReal64 mfreq = freq;
    DiReal64 mfdeta = 0.0;
    int iBack = 0;
    int istart = 0,istop = 0;
    //means set atten and IF gain auto
    int ioverflow = 0;//when un 0 means freq is over the largest freq;

    if(autoflag)
        {
            int index0,index1 = 0;
            int setchannelIndex = 0;
            DiReal64 deta = 0.0;

            //means will used -10dB datas
            if(refl <= ATTENZERODOORWHENON)
                {
                    index0 = GetpreOnAttenIndex(ATTENZEROWHENON);
                    setchannelIndex = index0;
                    int icalcIndex0 = bitFreqList.count * index0;

                    //means deta value is 0,direct use calc datas
                    //Linear interpolation for filling datas

                    //get freq location,start index and stop index
                    GetStartAndStopIndex(mfreq,istart,&istart,&istop,0);
                    mfdeta = mfreq - *(bitFreqList.param + istart);
                    if(0 == ioverflow)
                        {
                            if(mfreq >= FREQMAX)
                                {
                                    ioverflow = istart - 1;
                                }
                        }
                    if(mfdeta < 0.0)
                        {
                            calcresult[0] = *(preOnCalcResult.param + icalcIndex0 + istart);
                        }
                    else if(mfreq >= FREQMAX)
                        {
                            calcresult[0] = *(preOnCalcResult.param + icalcIndex0 + ioverflow);
                        }
                    else
                        {
                            calcresult[0] = mfdeta * (*(preOnCalcResult.param + icalcIndex0 + istop)  - *(preOnCalcResult.param + icalcIndex0 + istart))
                                    / (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOnCalcResult.param + icalcIndex0 + istart);
                        }

                }
            else
                {
                    index0 = GetpreOnAttenIndex(refl);
                    int icalcIndex0 = bitFreqList.count * index0;
                    setchannelIndex = index0;
                    GetStartAndStopIndex(mfreq,istart,&istart,&istop,0);
                    mfdeta = mfreq - *(bitFreqList.param + istart);
                    if(0 == ioverflow)
                        {
                            if(mfreq >= FREQMAX)
                                {
                                    ioverflow = istart - 1;
                                }
                        }
                    if(mfdeta < 0.0)
                        {
                            calcresult[0] = *(preOnCalcResult.param + icalcIndex0 + istart);
                        }
                    else if(mfreq >= FREQMAX)
                        {
                            calcresult[0] = *(preOnCalcResult.param + icalcIndex0 + ioverflow);
                        }
                    else
                        {
                            calcresult[0] = mfdeta * (*(preOnCalcResult.param + icalcIndex0 + istop)  - *(preOnCalcResult.param + icalcIndex0 + istart))
                                    / (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOnCalcResult.param + icalcIndex0 + istart);
                        }
                }

        }
    //in the man mode,means only set atten,and ref\ifgain not change
    else
        {
            //calc needed calc datas
            //use lastatten and now atten to get the deta datas
            int inowindex = GetAttenIndexOn(manatten);
            int icalcIndex0 = bitFreqList.count * inowindex;

            GetStartAndStopIndex(mfreq,istart,&istart,&istop,0);
            mfdeta = mfreq - *(bitFreqList.param + istart);
            //calcdata
            if(0 == ioverflow)
                {
                    if(mfreq >= FREQMAX)
                        {
                            ioverflow = istart - 1;
                        }
                }
            if(mfdeta < 0.0)
                {
                    calcresult[0] = *(preOnCalcResult.param + icalcIndex0 + istart);
                }
            else if(mfreq >= FREQMAX)
                {
                    calcresult[0] = *(preOnCalcResult.param + icalcIndex0 + ioverflow);
                }
            else
                {
                    calcresult[0] = mfdeta * (*(preOnCalcResult.param + icalcIndex0 + istop)  - *(preOnCalcResult.param + icalcIndex0 + istart))
                            / (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOnCalcResult.param + icalcIndex0 + istart);
                }

        }
    int i = 1;
    for(i = 1; i < datanum; i++ )
        {
            calcresult[i] = calcresult[0];
        }
    return 0;
}
/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-06-19}
*/
DiInt32 GetTemperCalcDatas(DiReal64 centerfreq,DiInt32 datanum,DiReal64 tempercoef,DiPReal64 calcresult,DiInt32 zeroflag)
{
    DiInt32 im = twicenum;
    if(dCompare2(tempercoef,0.0))
    {
        im = 0;
    }
    DiInt32 i = 0;
    DiInt32 isindex = 0;
    if(zeroflag)
        {
            calcresult[0] = *(pcalcdata + im + GetFreqChannelIndex(centerfreq) - 1) * tempercoef;
            for(i = 1;i < datanum;i++)
                {
                    *(calcresult + i) = *calcresult;
                }
        }
    else
        {
//            DiReal64 mstep = (stopfreq - startfreq) / (datanum - 1);
//            DiReal64 mfreq = startfreq;
//            for(i = 0;i < datanum;i++)
//                {
//                    isindex = GetFreqChannelIndexSec(mfreq,isindex);
//                    calcresult[i] = *(pcalcdata + im + isindex - 1) * tempercoef;
//                    mfreq += mstep;
//                }
        }
    return 0;
		}

