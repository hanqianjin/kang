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
#include "RfVirtualDriver.h"
#include "SaAnalysis.h"
#include "SaDataStruct.h"
#include "DigSigDealVirtualDriver.h"
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "CalcPointAlog.h"
#include "sweepinterupt.h"
#include "msgNoticeCode.h"



//==============================================================================
extern DiReal64 insertFuncDatas[8001];
extern DiReal64 inPI;
const DiInt32 INFLUENCENUM = 8;
const DiInt32 OVERNUM = 1000;
//==============================================================================
// Static functions
static void ListenEngine();
//==============================================================================
// Global variables
DiSession bitdevHandle = 0;
SWEEP_NUM sweepListinthread = {0};/*just used in the listen and down param thread*/
_CONFIG_SWEEP localSweepConfig = {0};//just used in ctrl app

FREQ_COUNT_LOCAL localFreqCountConfig = {0};

static void GetSweepInterruptState(DiPUInt32 state);//provided by foolish driver later
extern DiReal64 freqChannelList[];
extern _SM_SYNC syncMana;
//share shm
extern PSWEEP_DATA sm_sweep_data;
//extern PMEASURE_DATA sm_measure_data;
extern PSM_SYNC sm_sync;
extern PSWEEP_NUM sm_sweep_num;
extern PCONFIG_SWEEP sm_config_sweep;

extern PCONFIG_MEASURE sm_config_measure;
//===============================================================================
//change bityang,0323
static DiInt32 listState = 0;//1 means single sweep mode,and sweep is over
extern SWEEPCTRL CTRL_SWEEP_MODE;


FREQLIST bitFreqList;
CALCRESULTLIST preOffCalcResult; //the buffer size is freqNum * ampNum + extraNum
CALCRESULTLIST preOnCalcResult;
DiInt32 GetFreqChannelIndexSec(DiReal64 freqHz,DiInt32 istart);
//add amp ctrl,0424,by steve
//DiReal64 powerlistpoints[] = {10.0,5.0,0.0,-5.0,-10.0,-15.0,-20.0,-25.0,-30.0,-35.0};		//for source
//-20 used in the off mode,from -20 to -50 ,20 as if ref
//-30 used also in the on mode,from -30 to -60,-30 as if ref
DiReal64 powerlistpoint[] = {-20.0,-30,-40.0,-50.0,-60.0}; //for source
DiReal64 freqpoint = 100.0e6;//if gain calc

double powerlistpointsampoff[] = {10.0,5.0,0.0,-5.0,-10.0,-15.0,-20.0};
DiReal64 powerlistpointsampon[] = {-5.0,-10.0,-15.0,-20.0,-25.0,-30.0,-35.0}; //for sa

static int ProBufferForpreoff(PCALCRESULTLIST pbuffer,int iNum);
static int ProBufferForpreon(PCALCRESULTLIST pbuffer,int iNum);

static int GetpreOffAttenIndex(DiReal64 refLevel);
static void GetStartAndStopIndex(DiReal64 freqHz,int serStart,int* startIndex,int* stopIndex,int islastpoint);//islastpoint 0 means last point
static int GetAttenIndexOff(DiReal64 attendB);
static int GetpreOnAttenIndex(DiReal64 refLevel);
static int GetAttenIndexOn(DiReal64 attendB);
static void ResampleInsert(DiPReal64 poribuffer,DiInt32 orinum,DiInt32 dataindex,DiPReal64 poutbuffer,DiInt32 outnum,DiPReal64 refunc,DiInt32 refnum);

static void FreqCountZeroSpanControlSet();
static void FreqCountControlRecover();

static DiReal64 localSignalFreq = 0;

extern int SpanFlag;

extern DiInt32 reCtrlSweep;
typedef struct
{
    DiReal64 refLevel;
    DiReal64 atten;
    DiReal64 ifGain;
}CHANNELGAIN,*PCHANNELGAIN;

CHANNELGAIN ifGainOff[] = {    
    {20,30,30},
    {15,25,30},
    {10,20,30},
    {5,15,30},
    {0,10,30},
    {-5,5,30},
    {-10,0,30}//-10~-40 use the same data
};

CHANNELGAIN ifGainOn[] = {
    {0,30,30},
    {-5,25,30},
    {-10,20,30},
    {-15,15,30},
    {-20,10,30},
    {-25,5,30},
    {-30,0,30}
};
static void PassSweepParmFromShmToLocal();
extern int sweepHandle;
void GetCtrlInHand(DiInt32 handle);
void ReleaseCtrlInHand(DiInt32 handle);
enum SWEEPSTAGE {NOLAST = 0,YESLAST = 1};
typedef enum {ADDRNOTCLEAR = 0,ADDRCLEAR = 1} CLEARFPGAADDR;
extern void ErrOutPut(DiInt32 errCode,DiInt32 itype);


DiReal64 gperinsertnum = 0.0;
DiReal64 gperinsertfracpart = 0.0;
int gperinsertintpart = 0;
extern BSA_EXIT gappexit;
DiInt32 lisIdleflag = 0;//0 means in idle state
void* ListenAndDownSweepParamFunc(void *param)
{
    do
        {
            if(0 == sm_config_sweep->SweepType)
                {
                    lisIdleflag = 1;
                    //clear sig state
                    if(semctl(sweepHandle,0,SETVAL,0) < 0)
                        {
#if DEBUG_OUTPUT
                            printf("init error,%d:%s",errno,strerror(errno));
#endif
                        }
                    ListenEngine();
                    if(1 == sm_config_sweep->SweepType)
                        {
#if 1
                            //Tony 0517  6 means Spurious and 3 means SEM
                            if(6 == sm_config_measure->MeasureMode || 3 == sm_config_measure->MeasureMode)
                                {
                                            sm_config_sweep->SweepType = 2;
                                            sm_config_sweep->ListenState = OFF;
                                }else
                                {
                                    if(sm_config_sweep->uAllSweepCompleteFlag)
                                        {
                                            sm_config_sweep->SweepType = 2;
                                            sm_config_sweep->ListenState = OFF;//Johnson 190411
                                        }
                                }
#endif
                        }
                }
            else if(1 == sm_config_sweep->SweepType)
                {
                    lisIdleflag = 1;
                    if(semctl(sweepHandle,0,SETVAL,0) < 0)
                        {
#if DEBUT_OUTPUT
                            printf("init error,%d:%s",errno,strerror(errno));
#endif
                        }
		    ListenEngine();

                    //Johnson 190412
                    if(sm_config_sweep->SweepType != 0)
                        {
#if 1
                            //Tony 0517   6 means Spurious and 3 means SEM
                            if(6 == sm_config_measure->MeasureMode || 3 == sm_config_measure->MeasureMode)
                                {
                                
                                        {
                                            sm_config_sweep->SweepType = 2;
                                            sm_config_sweep->ListenState = OFF;//Johnson 190411
                                        }
                                }else
                                {
                                    if(sm_config_sweep->uAllSweepCompleteFlag)
                                        {
                                            sm_config_sweep->SweepType = 2;
                                            sm_config_sweep->ListenState = OFF;//Johnson 190411
                                        }
                                }
#endif
                        }
                }
            else
                {
                    lisIdleflag = 0;
                    usleep(1000);
                }
        }
    while(gappexit.listenthreadExit);
    gappexit.midmsgthreadExit = 0;
    return NULL;
}

extern DiInt32 intersource;
DiInt32 ifinish = 0;
extern DiInt32 gwhole;

static double iwhat = 0.;
extern PCONFIG_MEASURE sm_config_measure;

DiInt32 bMarkerFreqCountInterrupt = 0;
DiInt32 bFreqCountSpanMode = 1;//1,normal span;0,zero span
DiInt32 bFreqCountSweepComplete = 0;
DiInt32 bFreqCountDataGetComplete = 0;

static void ListenEngine()
{
    //sm_config_sweep->ListenState = ON;
    DiInt32 iBack = 0;
    DiInt32 i = 0;
    DiInt32 interState = 0;

    //means whole run from down params to sweep once
    if(reCtrlSweep) return;
    gwhole = 1;
    if(intersource) intersource = 0;


    if(syncMana.DeviceMsgUpdate)
        {
            if(0 == localSweepConfig.SPANMode)
                {
                    PassSweepParmFromShmToLocal();
                }
            syncMana.DeviceMsgUpdate = !syncMana.DeviceMsgUpdate;
        }

    iBack = DataBufferClear(bitdevHandle,ADDRCLEAR);
    if(iBack < 0)
        {
            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
            return;
        }
    iBack = DataBufferClear(bitdevHandle,ADDRNOTCLEAR);
    if(iBack < 0)
        {
            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
            return;
        }

#if BIT_DEBUG
    usleep(100000);
#endif
    
    //zero span mode
    if(1 == localSweepConfig.SPANMode)
        {
            iBack = SetSwpStop(bitdevHandle);
            if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return;
                }
            iBack = SetSwpRun(bitdevHandle);
            if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return;
                }
	sm_config_sweep->ListenState = ON;//Johnson 190712
	
	if(reCtrlSweep) return;
	
            //0606,steve
#if !BIT_DEBUG
            lisIdleflag = 0;
            GetCtrlInHand(sweepHandle);
            sm_config_sweep->uSweepCompleteFlag = 1;
	    sm_config_sweep->uMinMaxHoldComplete = 1;
	    

	#if FREQ_COUNT
	    if(sm_config_sweep->markerFreqCount && 0 == localSweepConfig.sweepMode)
	    {
		while(1)
		{
			if(bMarkerFreqCountInterrupt)
			{
    				//sm_sweep_data->fsr = GetFsr(bitdevHandle);
				usleep(100000);
				sm_sweep_data->fsr = GetFsr(bitdevHandle);
		    		sm_config_sweep->signalFreq = localSignalFreq;
		    
				break;
			}
			usleep(20000);
			if(reCtrlSweep) return;
		}

		bFreqCountSweepComplete = 0;
		bFreqCountSpanMode = 1;//normal span flag
		bFreqCountDataGetComplete = 0;

		//*******set normal span param(midmsg non_zero_span control and localSweepConfig.SPANMode = 0)
		FreqCountControlRecover();
		if(reCtrlSweep) return;
	    }
	#endif
#endif
        }
    else
        {
            for(i = 0; i < sweepListinthread.segmentNum; i++)
                {
                    //Johnson 190514
                    SetSegFlagByFreq(i);

                    //when receive the soft interrupt,break
                    if(reCtrlSweep) return;

                    iBack = RfChannelChoosebyIndex(bitdevHandle,sweepListinthread.comNum[i].segmentIndex);
                    if(iBack < 0)
                        {
                            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
    		    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                            return;
                        }

                    if(reCtrlSweep) return;

                    iBack = SetSwpStop(bitdevHandle);
                    if(iBack < 0)
                        {
                            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
    		    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                            return;
                        }
                    //down the param
                    //the lo step
                    if(reCtrlSweep) return;

                    iBack = SetFirLoStepFreq(bitdevHandle,(sweepListinthread.comNum + i) -> seglosteplow, (sweepListinthread.comNum + i) -> seglostephigh);
                    if(iBack < 0)
                        {
                            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
    		    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                            return;
                        }
                    if(reCtrlSweep) return;


                    //if fft single acq time
                    if(3 == localSweepConfig.sweepMode)
                        {
                            iBack = SetSegPoint(bitdevHandle,(sweepListinthread.comNum + i) -> segmentDataNum);
                            if(iBack < 0)
                                {
                                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
    		    	    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                                    return;
                                }

                            if(reCtrlSweep) return;
                        }
                    else
                        {
                            //setting per segment total sweep time,steve,0504
                            //0726
                            iBack = SetTotalSwtTimeUs(bitdevHandle,sweepListinthread.comNum[i].persegsweeptimes * 1000);
                            if(iBack < 0)
                                {
                                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
    		    	    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                                    return;
                                }
                            //segment points num,means lo step times
                            if(reCtrlSweep) return;
                                
                            iBack = SetSegPoint(bitdevHandle,(sweepListinthread.comNum + i) -> segmentDataNum);
                            if(iBack < 0)
                                {
                                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
    		    	    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                                    return;
                                }

                            if(reCtrlSweep) return;
                        }

                    //the start freq div frq,last down
                    iBack = SetFirLoFreq(bitdevHandle,(sweepListinthread.comNum + i) -> seglostartfreqinter,(sweepListinthread.comNum + i) -> seglostartfreqfrac);
                    if(iBack < 0)
                        {
                            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    	    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                            return;
                        }
                    if(reCtrlSweep) return;
                    //steve,0504
                    if(i == sweepListinthread.segmentNum - 1)
                        {
                            //means FPGA to clear inner control states to resweep
                            iBack = SetLastBandCtrl(bitdevHandle,YESLAST);
                            if(iBack < 0)
                                {
                                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    	    	    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                                    return;
                                }
                            if(reCtrlSweep) return;
                              
                        }
                    else
                        {
                            iBack = SetLastBandCtrl(bitdevHandle,NOLAST);
                            if(iBack < 0)
                                {
                                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    	    	    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                                    return;
                                }
                            if(reCtrlSweep) return;
                               
                        }
                    //resweet
                    iBack = SetSwpRun(bitdevHandle);
                    if(iBack < 0)
                        {
                            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
    	    	    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                            return;
                        }
		    if(reCtrlSweep) return;
                       

		    sm_config_sweep->ListenState = ON;//Johnson 190712

#if !BIT_DEBUG
                    lisIdleflag = 0;
                    GetCtrlInHand(sweepHandle);

		    if(reCtrlSweep) return;
		   
		
                    if(i == sweepListinthread.segmentNum - 1)
                    {			
	                    if(3 == sm_config_measure->MeasureMode || 6 == sm_config_measure->MeasureMode)
	                    {
			            if(!intersource && gwhole)
			            {
			                    ifinish = 1;
			                    //gwhole = 0;
			            }
	                    }
	                    else
	                    {
				   if(sm_config_sweep->FirstStart < 5)
				   	{
				  		 sm_config_sweep->FirstStart ++;
				   	}
                    		    sm_config_sweep->uSweepCompleteFlag = 1;
		    		sm_config_sweep->uMinMaxHoldComplete = 1;
	                    }
                    }

                    iBack = SetSwpStop(bitdevHandle);
                    if(iBack < 0)
                        {
                            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
    	    	    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                            return;
                        }


	#if FREQ_COUNT
		   if(i == sweepListinthread.segmentNum - 1)
		   {
			//========Johnson 190718 marker freq count=======
			    if(sm_config_sweep->markerFreqCount)
			    {
				if(0 == localSweepConfig.sweepMode)
				{
					bMarkerFreqCountInterrupt = 0;
					bFreqCountSweepComplete = 1;

					while(!bFreqCountDataGetComplete)
					{
						if(reCtrlSweep) return;
						usleep(200000);
					}

					bFreqCountSpanMode = 0;//zero span flag 190809

					//******set zerospan param(midmsg zero_span control and localSweepConfig.SPANMode = 1)
					FreqCountZeroSpanControlSet();
					if(reCtrlSweep) return;

					usleep(1000000);

					iBack = SetFsrGetStart(bitdevHandle);
					if(iBack<0)
					{
						setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    	    	    	    	ErrOutPut(REDIRECT_YES,WRSHM_YES);
						return;
					}
					if(reCtrlSweep) return;
				}
				else
				{
					bMarkerFreqCountInterrupt = 0;
					bFreqCountSweepComplete = 1;
					while(!bFreqCountDataGetComplete)
					{
						if(reCtrlSweep) return;
						usleep(200000);
					}

					usleep(10000);
					bFreqCountSweepComplete = 0;

					//*********find the max point and set
					DiInt32 iBack = 0;
					DiUInt32 acqb[1001];
					memset(acqb,0,sizeof(acqb));
					iBack =  GetResultData(bitdevHandle,acqb,localSweepConfig.TracePoint);
					if(iBack<0)
					{
						setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
						ErrOutPut(REDIRECT_YES,WRSHM_YES);
						return;
					}

					DiInt32 i = 0;
					DiReal64 tmpData = acqb[0];
					DiInt32 tmpIndex = 0;
					for(i = 1;i < localSweepConfig.TracePoint;i++)
					{
						if(tmpData < acqb[i]) 
						{
							tmpData = acqb[i];
							tmpIndex = i;
						}
					}

	
					DiReal64 tmpCenterFreq = sm_config_sweep->StartFreq + (sm_config_sweep->StopFreq - sm_config_sweep->StartFreq)/(localSweepConfig.TracePoint - 1) * tmpIndex;
					localSignalFreq = tmpCenterFreq;


					if(reCtrlSweep) return;

					usleep(1000000);

					iBack = SetFsrGetStart(bitdevHandle);
					if(iBack<0)
					{
						setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    	    	    	    	ErrOutPut(REDIRECT_YES,WRSHM_YES);
						return;
					}
					if(reCtrlSweep) return;

					while(1)
					{
						if(bMarkerFreqCountInterrupt)
						{
							//Get Fsr
			    				//sm_sweep_data->fsr = GetFsr(bitdevHandle);
							usleep(100000);
							sm_sweep_data->fsr = GetFsr(bitdevHandle);
					    		sm_config_sweep->signalFreq = localSignalFreq;
							break;
						}
						usleep(20000);
						if(reCtrlSweep) return;
					}
					bFreqCountDataGetComplete = 0;
				}
			    }
			    else if(sm_config_sweep->bSendFreqCountStopCmd)
			    {
				bFreqCountSweepComplete = 1;
			    }
			    //===============================================
		   }
	#endif
#endif

                    if(!gappexit.listenthreadExit || reCtrlSweep || syncMana.DeviceMsgUpdate) return;
                }
        }
    	return;
}


const DiReal64 firfskHzlist[] = {1.0/11250.0,1.0/11250.0,1.0/5625.0,1.0/1125.0,1.0/375.0,1.0/112.5,1.0/37.5,1/11.25,1/3.75,1/1.125,1/0.375,1/0.1125,1/0.0375,1/0.01125,1/0.00375};
static DiInt32 GetrbwIndex(DiReal64 rbwHz)
{
	  const DiReal64 rbwList[] = {5.0e6,3.0e6,1.0e6,3.0e5,1.0e5,3.0e4,1.0e4,3000,1000,300,100,30, 10, 3, 1};
	  //check param
	  DiInt32 iListLeng = sizeof(rbwList) / sizeof(DiReal64);
	  iListLeng = iListLeng < 1 ? 1 : iListLeng;
	  rbwHz = rbwHz > rbwList[0] ? rbwList[0] : rbwHz;
	  rbwHz = rbwHz < rbwList[iListLeng - 1] ? rbwList[iListLeng - 1] : rbwHz;

	  DiInt32 iIndex = 0;
	  for(iIndex = 0; iIndex < iListLeng; iIndex++)
	  {
	      if(*(rbwList + iIndex) <= rbwHz)
		return iIndex;
	  }
	  return iIndex - 1;
}
//190731 Johnson
static void FreqCountZeroSpanControlSet()
{
	//*********find the max point and set
	DiInt32 iBack = 0;
	DiUInt32 acqb[1001];
	memset(acqb,0,sizeof(acqb));
	iBack =  GetResultData(bitdevHandle,acqb,localSweepConfig.TracePoint);
	if(iBack<0)
	{
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		ErrOutPut(REDIRECT_YES,WRSHM_YES);
		return;
	}

	DiInt32 i = 0;
	DiReal64 tmpData = acqb[0];
	DiInt32 tmpIndex = 0;
	for(i = 1;i < localSweepConfig.TracePoint;i++)
	{
		if(tmpData < acqb[i]) 
		{
			tmpData = acqb[i];
			tmpIndex = i;
		}
	}

	
	DiReal64 tmpCenterFreq = sm_config_sweep->StartFreq + (sm_config_sweep->StopFreq - sm_config_sweep->StartFreq)/(localSweepConfig.TracePoint - 1) * tmpIndex;
	localSignalFreq = tmpCenterFreq;

	if(0 == localSweepConfig.sweepMode)
	{
		localSweepConfig.SPANMode = 1;
		iBack = SetZeroSpan(bitdevHandle,localSweepConfig.SPANMode);
		if(iBack<0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
			ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return;
		}
	
		iBack = DataBufferClear(bitdevHandle,1);
		if(iBack<0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
			ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return;
		}
		iBack = DataBufferClear(bitdevHandle,0);
		if(iBack<0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
			ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return;
		}
	}
	

#ifdef BIT_F238
	if(tmpCenterFreq <= 7500000000) 				    iBack = SetFreqSegFlag(bitdevHandle,1);
	else if(tmpCenterFreq > 7500000000 && tmpCenterFreq <= 20000000000) iBack = SetFreqSegFlag(bitdevHandle,2);
	else if(tmpCenterFreq > 20000000000) 				    iBack = SetFreqSegFlag(bitdevHandle,0);
	
	if(iBack<0)
	{
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		ErrOutPut(REDIRECT_YES,WRSHM_YES);
		return;
	}
#endif

#ifdef BIT_F239
	iBack = SetFreqSegFlag(bitdevHandle,0);
	if(iBack<0)
	{
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		ErrOutPut(REDIRECT_YES,WRSHM_YES);
		return;
	}
	/*if(tmpCenterFreq <= 2800000000) 	     				iBack = SetFreqSegFlag(bitdevHandle,1);
	else if(tmpCenterFreq > 2800000000 && tmpCenterFreq <= 7200000000) 	iBack = SetFreqSegFlag(bitdevHandle,3);
	else if(tmpCenterFreq > 7200000000 && tmpCenterFreq <= 18000000000) 	iBack = SetFreqSegFlag(bitdevHandle,3);
	else if(tmpCenterFreq > 18000000000) 					iBack = SetFreqSegFlag(bitdevHandle,4);

	if(iBack<0)
	{
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		ErrOutPut(REDIRECT_YES,WRSHM_YES);
		return;
	}*/
#endif

#ifdef BIT_F238_SMART
	if(tmpCenterFreq <= 2600000000LL) 				       iBack = SetFreqSegFlag(bitdevHandle,1);
	else if(tmpCenterFreq > 2600000000LL && tmpCenterFreq <= 7200000000LL) iBack = SetFreqSegFlag(bitdevHandle,2);
	else if(tmpCenterFreq > 7200000000LL) 				       iBack = SetFreqSegFlag(bitdevHandle,4);

	if(iBack<0)
	{
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		ErrOutPut(REDIRECT_YES,WRSHM_YES);
		return;
	}
#endif

	DiReal64 tmpDottime = 0;
	if(localSweepConfig.sweepMode == 3)
	{
		iBack = SetDataProcMode(bitdevHandle,0);
		if(iBack<0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
			ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return;
		}

		iBack = SetRbw(bitdevHandle,10000);
		if(iBack<0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
			ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return;
		}

		iBack = SetVbw(bitdevHandle,10000);
		if(iBack<0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
			ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return;
		}

		tmpDottime = *(firfskHzlist + GetrbwIndex(10000));
  		tmpDottime = tmpDottime < 0.0001 ? 0.0001 : tmpDottime;
	}
	else
	{
		tmpDottime = *(firfskHzlist + GetrbwIndex((DiReal64)sm_config_sweep->RBW));
  		tmpDottime = tmpDottime < 0.0001 ? 0.0001 : tmpDottime;
	}

	

	iBack = SetTotalSwtTimeUs(bitdevHandle,tmpDottime * localSweepConfig.TracePoint * 1000);
	if(iBack<0)
	{
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		ErrOutPut(REDIRECT_YES,WRSHM_YES);
		return;
	}

        iBack = SetFirBucketTime(bitdevHandle,tmpDottime * 1000);
	if(iBack<0)
	{
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		ErrOutPut(REDIRECT_YES,WRSHM_YES);
		return;
	}

        iBack = SetFirLoStepFreq(bitdevHandle,0,0);
	if(iBack<0)
	{
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		ErrOutPut(REDIRECT_YES,WRSHM_YES);
		return;
	}

        iBack = SetSegPoint(bitdevHandle,1);
	if(iBack<0)
	{
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		ErrOutPut(REDIRECT_YES,WRSHM_YES);
		return;
	}

        iBack = FirstLoFreqCtrl(bitdevHandle,/*sm_config_sweep->CenterFreq*/tmpCenterFreq);
	if(iBack<0)
	{
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		ErrOutPut(REDIRECT_YES,WRSHM_YES);
		return;
	}

        iBack = RfChannelChoose(bitdevHandle,/*sm_config_sweep->CenterFreq*/tmpCenterFreq);
	if(iBack<0)
	{
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		ErrOutPut(REDIRECT_YES,WRSHM_YES);
		return;
	}
}

//190731 Johnson
static void FreqCountControlRecover()
{
	DiInt32 iBack = 0;
	localSweepConfig.SPANMode = 0;

	iBack = SetZeroSpan(bitdevHandle,localSweepConfig.SPANMode);
	if(iBack<0)
	{
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		ErrOutPut(REDIRECT_YES,WRSHM_YES);
		return;
	}
	

	if(localSweepConfig.sweepMode == 3)
	{
		iBack = SetRbw(bitdevHandle,sm_config_sweep->RBW);
		if(iBack<0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
			ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return;
		}

		iBack = SetVbw(bitdevHandle,sm_config_sweep->VBW);
		if(iBack<0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
			ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return;
		}

		iBack = SetFftValidStartNum(bitdevHandle, sm_sweep_num->startIndex);
		if(iBack<0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
			ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return;
		}

	        iBack = SetFftValidEndNum(bitdevHandle,sm_sweep_num->stopIndex);
		if(iBack<0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
			ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return;
		}

	        iBack = SetFftDotSwpTime(bitdevHandle,sm_sweep_num->singlefftTime);
		if(iBack<0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
			ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return;
		}

	        iBack = SetFftBucketNum(bitdevHandle,sm_sweep_num->fftBucketnum);
		if(iBack<0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
			ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return;
		}

		iBack = SetDataProcMode(bitdevHandle,localSweepConfig.sweepMode);
		if(iBack<0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
			ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return;
		}
	}
	else
	{
		iBack = SetFirBucketTime(bitdevHandle,sm_sweep_num->firBucketimeus * 1000);
		if(iBack<0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
			ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return;
		}
	}

	localFreqCountConfig.RBW = sm_config_sweep->RBW;
	localFreqCountConfig.VBW = sm_config_sweep->VBW;
	localFreqCountConfig.startIndex = sm_sweep_num->startIndex;
	localFreqCountConfig.stopIndex = sm_sweep_num->stopIndex;
	localFreqCountConfig.singlefftTime = sm_sweep_num->singlefftTime;
	localFreqCountConfig.fftBucketnum = sm_sweep_num->fftBucketnum;
	localFreqCountConfig.firBucketimeus = sm_sweep_num->firBucketimeus;
}

//Johnson 190514
void SetSegFlagByFreq(DiUInt32 iSweepSegIndex)
{
	DiInt32 iBack = 0;
	DiUInt32 iStartFreqIndex = sweepListinthread.comNum[0].segmentIndex;
	DiUInt32 iStopFreqIndex  = sweepListinthread.comNum[sweepListinthread.segmentNum - 1].segmentIndex;

#ifdef BIT_F238_SMART
	if(iStopFreqIndex <= 2 && iSweepSegIndex == 0) 							   iBack = SetFreqSegFlag(bitdevHandle,1);//segment is before 2.6GHz
	else if(iStartFreqIndex > 2 && iStopFreqIndex <= 3 && iSweepSegIndex == 0) 			   iBack = SetFreqSegFlag(bitdevHandle,2);//(2.6G,7.2G]
	else if(iStartFreqIndex >= 4 && iStopFreqIndex <= 7 && iSweepSegIndex == 0) 			   iBack = SetFreqSegFlag(bitdevHandle,4);//(7.2G,15G]
	else if(iStartFreqIndex <= 2 && iStopFreqIndex == 3 && iSweepSegIndex == 0) 			   iBack = SetFreqSegFlag(bitdevHandle,3); //only across 2.6G
	else if(iStartFreqIndex == 3 && iStopFreqIndex >= 4 && iStopFreqIndex <= 7 && iSweepSegIndex == 0) iBack = SetFreqSegFlag(bitdevHandle,6);//only across 7.2G
	else if(iStartFreqIndex <= 2 && iStopFreqIndex >= 4 && iStopFreqIndex <= 7 && iSweepSegIndex == 0) iBack = SetFreqSegFlag(bitdevHandle,7);//acroos 2.8G and 7.2G

	if(iSweepSegIndex == 0 && iBack<0)
	{
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		ErrOutPut(REDIRECT_YES,WRSHM_YES);
		return;
	}
#endif
#ifdef BIT_F239
	if(iStartFreqIndex <= 2 && iStopFreqIndex == 3 && iSweepSegIndex == 0)                              iBack = SetFreqSegFlag(bitdevHandle,1);//only across 2.8G      			  
	else if(iStartFreqIndex <= 2 && iStopFreqIndex >= 4 && iStopFreqIndex <= 7 && iSweepSegIndex == 0)  iBack = SetFreqSegFlag(bitdevHandle,2);//across 2.8G and 7.2G 			  
	else if(iStartFreqIndex <= 2 && iStopFreqIndex >= 8 && iSweepSegIndex == 0) 			    iBack = SetFreqSegFlag(bitdevHandle,3);//across 2.8G and 7.2G and 18G			    
	else if(iStartFreqIndex == 3 && iStopFreqIndex <= 7 && iStopFreqIndex >= 4 && iSweepSegIndex == 0)  iBack = SetFreqSegFlag(bitdevHandle,4);//only across 7.2G 
	else if(iStartFreqIndex == 3 && iStopFreqIndex >= 8 && iSweepSegIndex == 0) 			    iBack = SetFreqSegFlag(bitdevHandle,5);//across 7.2G and 18G 			  
	else if(iStartFreqIndex >= 4 && iStartFreqIndex <= 7 && iStopFreqIndex >= 8 && iSweepSegIndex == 0) iBack = SetFreqSegFlag(bitdevHandle,6);//only across 18G			  
	else if(iSweepSegIndex == 0) iBack = SetFreqSegFlag(bitdevHandle,0);//other

	if(iSweepSegIndex == 0 && iBack<0)
	{
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		ErrOutPut(REDIRECT_YES,WRSHM_YES);
		return;
	}
#endif
#ifdef BIT_F238
	if(iStopFreqIndex <= 4 && iSweepSegIndex == 0)                                                        iBack = SetFreqSegFlag(bitdevHandle,1);//segment is before 7.5GHz
    	else if(iStartFreqIndex >= 5 && iStopFreqIndex <= 11 && iSweepSegIndex == 0)                          iBack = SetFreqSegFlag(bitdevHandle,2);//segment is between 7.5GHz and 20GHz
    	else if(iStartFreqIndex >= 12 && iSweepSegIndex == 0)                                                 iBack = SetFreqSegFlag(bitdevHandle,0);//segment is after 20GHz
    	else if(iStartFreqIndex <= 4 && iStopFreqIndex <= 11 && iStopFreqIndex >= 5 && iSweepSegIndex == 0)   iBack = SetFreqSegFlag(bitdevHandle,3);//segment is across 7.5GHz
    	else if(iStartFreqIndex <= 4 && iStopFreqIndex >= 12 && iSweepSegIndex == 0)                          iBack = SetFreqSegFlag(bitdevHandle,3);//segment is across 7.5GHz and 20GHz
     	else if(iStartFreqIndex <= 11 && iStartFreqIndex >= 5 && iStopFreqIndex >= 12 && iSweepSegIndex == 0) iBack = SetFreqSegFlag(bitdevHandle,2); //segment is across 20GHz

	if(iSweepSegIndex == 0 && iBack < 0)
	{
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    	ErrOutPut(REDIRECT_YES,WRSHM_YES);
	    	return;
	}
#endif
}

static void PassSweepParmFromShmToLocal()
{
    memcpy(sweepListinthread.comNum,sm_sweep_num->comNum,sizeof(sweepListinthread.comNum));
    sweepListinthread.segmentNum = sm_sweep_num->segmentNum;
    localSweepConfig.sweepMode = sm_config_sweep->sweepMode;
    //sweepListinthread.sumSweeptime = sm_sweep_num->sumSweeptime * 1000;
    return;
}

static void GetSweepInterruptState(DiPUInt32 state)
{
    usleep(1000);
    return;
}

extern DiInt32 guiHandle;
extern DiInt32 syncHandle;
#define MAXBUFFERSIZE 1001
DiReal64 acqLocBuffer[MAXBUFFERSIZE];
DiUInt32 acqb[MAXBUFFERSIZE];
DiReal64 midInsertBuffer[MAXBUFFERSIZE];
DiReal64 midCalcBuffer[MAXBUFFERSIZE];
DiUInt32 detectorTime = 0;
DiUInt32 lastdetectorTime = 0;
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

static DiReal64 GetMaxVal(DiReal64* pbuffer,int num);
static DiReal64 GetMinVal(DiReal64* pbuffer,int num);

#define BIT_DOTNUM 801
extern DiPUInt32 pDpxBuffer;
#if BIT_DEBUG
void* AcqDataFunc(void *param)
{
    DiInt32 i = 0;
    DiReal64 iacp = 0.0;

    DiReal64 iphase = 0.0;
    DiInt32 ic = 0;

    DiInt32 icheckorinsert = 0;
    sweepListinthread.segmentsDataSumNum = 11;
    gperinsertnum = (BIT_DOTNUM - 11) / (11 - 1);

    gperinsertintpart = (int)gperinsertnum;

    gperinsertfracpart = gperinsertnum - gperinsertintpart;

    DiUInt32 n1 = 0;
    DiUInt32 n2 = 0;
    DiUInt32 n3 = 0;
    DiUInt32 n4 = 0;
    DiUInt32 n5 = 0;
    DiInt32 ireflesh = 0;
    DiUInt32 tempsum = 0;

    //20190123
    
    DiInt32 istart = 0;
    DiInt32 istop = 0;
    do
        {

            if(0 == sm_config_sweep->ListenState)
                {

                    if(1)
                        {

                            if(1 == reCalcflag)
                                {
                                    PassAcqParamFromShmToLocal();
                                    ireflesh = 0;
                                    reCalcflag = 0;
                                }
                            memset(acqLocBuffer,0,BIT_DOTNUM * 8);

                            iphase += 2.56/180*3.1415926;
                            if(iphase > 3.1415926)
                                iphase = 0;

                            istop = istart + 20;
                            if(istop > BIT_DOTNUM)
                                {
                                    istop = BIT_DOTNUM;
                                    istart = istop - 20;
                                }
                            for(i = 0;i<801;i++)
                                {
                                    midInsertBuffer[i] = rand();

                                    midInsertBuffer[i] = -8 * log(midInsertBuffer[i]);//8*sin(2* 3.1415926535/75*i) - 60;// + sin(2*3.1415926535/10*i -iphase);

                                    //-4 * log(midInsertBuffer[i]);
                                    acqLocBuffer[i] = midInsertBuffer[i];
                                }
                            /*
                            if(istop == BIT_DOTNUM)
                                {
                                    istart = 0;
                                    istop = 0;
                                }
                            else
                                {
                                    istart+=20;
                                }


                            for(i = 0;i < 100;i++)
                                {

                                     acqLocBuffer[i] = midInsertBuffer[i] = -63.45;
                                }


                     acqLocBuffer[0] = midInsertBuffer[0] = -60.34;
                            acqLocBuffer[1] = midInsertBuffer[1] = -56.23;
                            acqLocBuffer[2] = midInsertBuffer[2] =  -70.56;
                            acqLocBuffer[3] = midInsertBuffer[3] = -66.25;
                            acqLocBuffer[4] = midInsertBuffer[4] = -50.36;
                            acqLocBuffer[5] = midInsertBuffer[5] = -60.89;
                            acqLocBuffer[6] = midInsertBuffer[6] = -63.22;
                            acqLocBuffer[7] = midInsertBuffer[7] = -63.22;
                            acqLocBuffer[8] = midInsertBuffer[8] = -57.96;
                            acqLocBuffer[9] = midInsertBuffer[9] = -56.45;
                            acqLocBuffer[10] = midInsertBuffer[10] = -55.90;
                            acqLocBuffer[11] = midInsertBuffer[11] = -70.36;
                            acqLocBuffer[12] = midInsertBuffer[12] = -58.36;
                            acqLocBuffer[13] = midInsertBuffer[13] = -66.35;
                            acqLocBuffer[14] = midInsertBuffer[14] = -65.12;
                            acqLocBuffer[15] = midInsertBuffer[15] = -60.32;
                            acqLocBuffer[16] = midInsertBuffer[16] = -57.23;
                            acqLocBuffer[17] = midInsertBuffer[17] = -55.12;
                            acqLocBuffer[18] = midInsertBuffer[18] = -56.31;
                            acqLocBuffer[19] = midInsertBuffer[19] = -62.35;
                            acqLocBuffer[20] = midInsertBuffer[20] = -55.21;
                            acqLocBuffer[21] = midInsertBuffer[21] = -60.21;
                            acqLocBuffer[22] = midInsertBuffer[22] = -68.21;
                            acqLocBuffer[23] = midInsertBuffer[23] = -54.21;
                            acqLocBuffer[24] = midInsertBuffer[24] = -40.21;
                            acqLocBuffer[25] = midInsertBuffer[25] = -56.21;
                            acqLocBuffer[26] = midInsertBuffer[26] = -64.21;
                            acqLocBuffer[27] = midInsertBuffer[27] = -63.21;
                            acqLocBuffer[28] = midInsertBuffer[28] = -59.21;
                            acqLocBuffer[29] = midInsertBuffer[29] = -67.21;
                            acqLocBuffer[30] = midInsertBuffer[30] = -64.21;
                            acqLocBuffer[31] = midInsertBuffer[31] = -60.21;

                            acqLocBuffer[30] += 25;
                            acqLocBuffer[489] +=15;

                            midInsertBuffer[1] += 25;
                            midInsertBuffer[489] +=15;
                            acqLocBuffer[146] +=15;

                            midInsertBuffer[146] += 25;

*/

                            //0829 insert
                            if(-1 != localSweepConfig.checkinsert)
                                {

                                    tempsum = sweepListinthread.segmentsDataSumNum;
                                    //0905
                                    if(localSweepConfig.spanperstep < 1.0 - 1.0e-6)
                                        {

                                            if(1 == sweepListinthread.segmentNum)
                                                {

                                                    if(0 ==  localSweepConfig.checkinsert)
                                                        {
                                                            tempsum = localSweepConfig.TracePoint * localSweepConfig.firstper;
                                                        }
                                                    else
                                                        {
                                                            tempsum *= localSweepConfig.firstper;
                                                        }
                                                }
                                            else
                                                {
                                                    if(0 == ireflesh)
                                                        {

                                                            if(0 ==  localSweepConfig.checkinsert)
                                                                {
                                                                    n3 = localSweepConfig.TracePoint >> 1;

                                                                }
                                                            else
                                                                {
                                                                    n3 = sweepListinthread.fftNum;
                                                                }
                                                            n1 =  n3 * localSweepConfig.firstper;
                                                            n2 =  n3 * localSweepConfig.secper;
                                                            tempsum = n1 + n2;
                                                        }
                                                    //extract buffer

                                                    for(i = 0;i < n2;i++)
                                                        {
                                                            midInsertBuffer[n1 + i] = midInsertBuffer[n3 + i];
                                                        }

                                                }
                                        }
                                    else
                                        {

                                            if(0 == ireflesh)
                                                {
                                                    n1 = sweepListinthread.fftNum * localSweepConfig.firstper;
                                                    n2 = sweepListinthread.fftNum * localSweepConfig.secper;
                                                    n3 = sweepListinthread.comNum[0].segmentDataNum * sweepListinthread.fftNum;
                                                    n4 = tempsum - n3;
                                                    n5 = n3 - sweepListinthread.fftNum + n1;
                                                }
                                            if(1 == sweepListinthread.segmentNum)
                                                {
                                                    //1113 steve
                                                    if(0 != n1)
                                                        {
                                                            tempsum -= (sweepListinthread.fftNum - n1);
                                                        }
                                                }
                                            else
                                                {
                                                    if(0 != n1)
                                                        {
                                                            tempsum -= (sweepListinthread.fftNum - n1);

                                                        }
                                                    if(0 != n2)
                                                        {
                                                            tempsum -= (sweepListinthread.fftNum - n2);
                                                        }
                                                    for(i = 0;i < n4;i++)
                                                        {
                                                            midInsertBuffer[n5 + i] = midInsertBuffer[n3 + i];
                                                        }
                                                }
                                        }

                                    //insert action
                                    DiInt32 trueinsertnum = 0;
                                    DiReal64 tempfrac = 0.;
                                    DiInt32 m = 0;
                                    DiInt32 n = 0;


                                    if(tempsum <= 1)
                                        {

                                            for(m = 0; m < localSweepConfig.TracePoint;m++)
                                                {
                                                    acqLocBuffer[m] = midInsertBuffer[0];
                                                }
                                        }
                                    else
                                        {
                                            //0904
                                            //0831
                                            if(0 == ireflesh)
                                                {
                                                    gperinsertnum = (0.1 * 10 * localSweepConfig.TracePoint - tempsum) / (tempsum - 1);
                                                    gperinsertintpart = (DiInt32)gperinsertnum;
                                                    gperinsertfracpart = gperinsertnum - gperinsertintpart;
                                                }
                                            DiInt32 k = 0;
                                            for(m = 0;m < tempsum - 1;m++)
                                                {
                                                    tempfrac += gperinsertfracpart;
                                                    if(tempfrac - 1.0 > -1.0e-6)
                                                        {
                                                            tempfrac -= 1.0;
                                                            trueinsertnum = gperinsertintpart + 1;
                                                        }
                                                    else
                                                        {
                                                            trueinsertnum = gperinsertintpart;
                                                        }

                                                    DiReal64 tempdeta = (midInsertBuffer[m+1] - midInsertBuffer[m]) / (trueinsertnum + 1);
                                                    acqLocBuffer[k++] = midInsertBuffer[m];
                                                    for(n = 0;n < trueinsertnum;n++)
                                                        {
                                                            acqLocBuffer[k++] = acqLocBuffer[k-2] + tempdeta;
                                                        }
                                                }
                                            acqLocBuffer[k] = midInsertBuffer[tempsum - 1];
                                        }
                                    ireflesh = 1;
                                }


                            GetCtrlInHand(syncHandle);
                            for(i = 0;i<BIT_DOTNUM;i++)
                                {
                                    sm_sweep_data->_PwrLevel[i] = (acqLocBuffer[i] + 80);
                                }
                            ReleaseCtrlInHand(guiHandle);


                            
		                /*GetResultData(bitdevHandle,acqb,localSweepConfig.TracePoint);
		                for(i = 0;i < localSweepConfig.TracePoint;i++)
		                {
		                        acqLocBuffer[i] = 20 * log10(*(acqb + i) + 0.000001) - 200;
		                }

		                GetCtrlInHand(syncHandle);
		                memcpy(sm_sweep_data->_PwrLevel,acqLocBuffer,localSweepConfig.TracePoint << 3);
		                ReleaseCtrlInHand(guiHandle);*/
                        }
                }
            else
                {
                    usleep(100000);
                    istart = 0;
                    istop = 0;
                }
        }while(gappexit.acqthreadExit);//while(syncMana.AppExit);
    gappexit.listenthreadExit = 0;
    return NULL;
}
#else
void* AcqDataFunc(void *param)
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
    DiUInt64 tempsum = 0;

    DiReal64 orimax = 0.0;
    DiReal64 orimin = 0.0;
    DiReal64 insertmax = 0.0;
    DiReal64 insertmin = 0.0;
    DiReal64 actor1 = 0.0;
    DiReal64 actor2 = 0.0;

	
    do
        {
			//Tony 19-12-19
  		if(0 == sm_config_sweep->ListenState || (3 == sm_config_sweep->sweepMode &&
		    (sm_sweep_num->segmentsDataSumNum < localSweepConfig.TracePoint - 1 && detectorTime != sm_sweep_num->segmentsDataSumNum -1) || 
		    (sm_sweep_num-> segmentsDataSumNum >= localSweepConfig.TracePoint - 1 && detectorTime != sm_config_sweep->TracePoint -1))||
		    (0 == sm_config_sweep->sweepMode && detectorTime != sm_config_sweep->TracePoint -1)
		  )
                {
		    
                    if(1 == reCalcflag)
                        {
                            PassAcqParamFromShmToLocal();
                            //means zero span mode,0503
                            //ireflesh = 0;
                            if(localSweepConfig.SPANMode)
                                {
                                    if(localSweepConfig.Preamp)
                                        {
                                            GetCalcDataWhenPreAmpOnZeroSpan(localSweepConfig.CenterFreq,localSweepConfig.TracePoint,localSweepConfig.RefLevel,localSweepConfig.attenAuto,localSweepConfig.attenValue,midCalcBuffer);
                                        }
                                    else
                                        {
                                            GetCalcDataWhenPreAmpOffZeroSpan(localSweepConfig.CenterFreq,localSweepConfig.TracePoint,localSweepConfig.RefLevel,localSweepConfig.attenAuto,localSweepConfig.attenValue,midCalcBuffer);
                                        }
                                }
                            else
                                {
                                    if(localSweepConfig.Preamp)
                                        {
                                            GetCalcDataWhenPreAmpOn(localSweepConfig.StartFreq,localSweepConfig.StopFreq,localSweepConfig.TracePoint,localSweepConfig.RefLevel,localSweepConfig.attenAuto,localSweepConfig.attenValue,midCalcBuffer);
                                        }
                                    //preamp is off
                                    else
                                        {
                                            GetCalcDataWhenPreAmpOff(localSweepConfig.StartFreq,localSweepConfig.StopFreq,localSweepConfig.TracePoint,localSweepConfig.RefLevel,localSweepConfig.attenAuto,localSweepConfig.attenValue,midCalcBuffer);
                                        }
                                }
                            reCalcflag = 0;
                        }
		    lastdetectorTime = detectorTime;
                    detectorTime = GetDetectorTime(bitdevHandle);
		    
        	    
	#if DEBUG_OUTPUT
		    //printf("sm_sweep_num->segmentsDataSumNum is %u,detectorTime is %u listenstate is %u\n",sm_sweep_num->segmentsDataSumNum,detectorTime,sm_config_sweep->ListenState);	
		    //printf("check insert %d\n",sm_config_sweep->checkinsert);
	#endif
#if FREQ_COUNT
		    //********Johnson 190718 marker freq count
		    if(sm_config_sweep->markerFreqCount)
		    {
			#if DEBUG_OUTPUT
			//printf("bFreqCountSpanMode %u,bFreqCountSweepComplete %u\n",bFreqCountSpanMode,bFreqCountSweepComplete);
			//printf("spanmode %u\n",localSweepConfig.SPANMode);
			#endif

			if(!(bFreqCountSpanMode && bFreqCountSweepComplete) && 0 == localSweepConfig.sweepMode) continue;
			if(!bFreqCountSweepComplete && 3 == localSweepConfig.sweepMode) continue;
		    }
		    else if(sm_config_sweep->bSendFreqCountStopCmd)
		    {
			#if DEBUG_OUTPUT
			//printf("bFreqCountSpanMode %u,bFreqCountSweepComplete %u\n",bFreqCountSpanMode,bFreqCountSweepComplete);
			#endif

			if(!(bFreqCountSpanMode && bFreqCountSweepComplete) && 0 == localSweepConfig.sweepMode) continue;
			if(3 == localSweepConfig.sweepMode && !bFreqCountSweepComplete) continue;
			sm_config_sweep->bSendFreqCountStopCmd = 0;
		    }
		    //****************************************
#endif


                    iBack =  GetResultData(bitdevHandle,acqb,localSweepConfig.TracePoint);
                    if(iBack < 0)
                        {
                            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
			    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                            return NULL;
                        }

		    if(SpanFlag)
		     {
			int maxpoint = 0;
			unsigned int tmpData = acqb[0];
			printf("startFreq:%f,stopFreq:%f\n",sm_config_sweep->StartFreq,sm_config_sweep->StopFreq);
			for(i = 0;i<localSweepConfig.TracePoint;i++)
			{
				//printf("number:%d,detectorData:%u\n",i+1,acqb[i]);
				if(tmpData < acqb[i])
				{
					tmpData = acqb[i];
					maxpoint = i+1;
				}
			}
			printf("***************the max point :%d***************\n",maxpoint);
			SpanFlag = 0;
		     }

#if FREQ_COUNT
		    //********Johnson 190718 marker freq count
		    if(sm_config_sweep->markerFreqCount)
		    {
			bFreqCountDataGetComplete = 1;
		    }
		    //****************************************
#endif
			
		    //if(!sm_config_sweep->uMinMaxHoldComplete && detectorTime == localSweepConfig.TracePoint -1) sm_config_sweep->uMinMaxHoldComplete = 1;

                    for(i = 0;i < localSweepConfig.TracePoint;i++)
                        {
                            //acqLocBuffer[i] = 20 * log10(*(acqb + i) + 0.000001) - 200;
                            //0830
                            //0121
                            //midInsertBuffer[i] = 20 * log10(*(acqb + i) + 0.000001) - 200;
			    //printf("%d data is %f\n",i+1,acqb[i]);
                            midInsertBuffer[i] = acqb[i];
                            midInsertBuffer[i] *= acqb[i];
                            acqLocBuffer[i] = midInsertBuffer[i];
                        }


                    //0829 insert
                    if(-1 != localSweepConfig.checkinsert)
                        {
			     ireflesh = 0;
                            //active valid point for one fft
                            tempsum = sweepListinthread.segmentsDataSumNum;
                            //0905
                            //means only one points
                            if(localSweepConfig.spanperstep < 1.0 - 1.0e-6)
                                {
                                    if(1 == sweepListinthread.segmentNum)
                                        {
                                            //check and insert
                                            if(0 ==  localSweepConfig.checkinsert)
                                                {
                                                    tempsum = localSweepConfig.TracePoint * localSweepConfig.firstper;
                                                    //mid valid start index
                                                    //                                                    n1 = localSweepConfig.TracePoint * (1 - localSweepConfig.firstper) * 0.5;
                                                }
                                            else
                                                {
                                                    //mid valid start index
                                                    //                                                    n1 = tempsum * (1 - localSweepConfig.firstper) * 0.5;
                                                    //direct and insert
                                                    tempsum *= localSweepConfig.firstper;
                                                }
                                            //extract data
                                            //                                            for(i = 0;i < tempsum;i++)
                                            //                                                {
                                            //                                                    midInsertBuffer[i] = midInsertBuffer[n1 + i];
                                            //                                                }
                                            //printf("firstper is %lf,n1 is %d\n",localSweepConfig.firstper,n1);
                                        }
                                    else
                                        {
                                            //means step two segments
                                            if(0 == ireflesh)
                                                {
                                                    //check and insert
                                                    if(0 ==  localSweepConfig.checkinsert)
                                                        {
                                                            n3 = localSweepConfig.TracePoint >> 1;
                                                            n1 =  n3 * localSweepConfig.firstper;
                                                            n2 =  n3 * localSweepConfig.secper;
                                                            //first segment valid start index
                                                            //n4 = n3 - n1;
                                                            //second segment valid start index
                                                            //n5 = 0;
                                                        }
                                                    else
                                                        {
                                                            //direct and insert
                                                            n3 = sweepListinthread.fftNum;
                                                            n1 =  n3 * localSweepConfig.firstper;
                                                            n2 =  n3 * localSweepConfig.secper;
                                                            //first segment valid start index
                                                            //n4 = n3 - n1;
                                                            //second segment valid start index
                                                            //n5 = n3 - n2;
                                                        }
                                                    tempsum = n1 + n2;
                                                }
                                            //extract data
                                            //                                            for(i = 0;i < n1;i++)
                                            //                                                {
                                            //                                                    midInsertBuffer[i] = midInsertBuffer[n4 + i];
                                            //                                                }

                                            for(i = 0;i < n2;i++)
                                                {
                                                    //                                                    midInsertBuffer[n1 + i] = midInsertBuffer[n3 + n5 + i];
                                                    midInsertBuffer[n1 + i] = midInsertBuffer[n3 + i];
                                                }
                                        }
                                }
                            else if (0 ==  localSweepConfig.checkinsert) {
                                if(1 == sweepListinthread.segmentNum){
                                    tempsum = localSweepConfig.TracePoint * localSweepConfig.firstper;
                                } else {
                                    n3 = localSweepConfig.TracePoint * sm_sweep_num->comNum[0].segmentDataNum / (sm_sweep_num->comNum[0].segmentDataNum + sm_sweep_num->comNum[1].segmentDataNum);
                                    n1 =  localSweepConfig.TracePoint * localSweepConfig.firstper * 
                                        sm_sweep_num->comNum[0].segmentDataNum / (sm_sweep_num->comNum[0].segmentDataNum + sm_sweep_num->comNum[1].segmentDataNum);
                                    n2 =  localSweepConfig.TracePoint * localSweepConfig.secper * 
                                        sm_sweep_num->comNum[1].segmentDataNum / (sm_sweep_num->comNum[0].segmentDataNum + sm_sweep_num->comNum[1].segmentDataNum);
                                    tempsum = n1 + n2;
                                    for(i = 0;i < n2;i++) {
                                        midInsertBuffer[n1 + i] = midInsertBuffer[n3 + i];
                                    }
                                }
                            }
                            else
                                {
                                    //means multi points,means direct
                                    if(0 == ireflesh)
                                        {
                                            //first fft point valid num
                                            n1 = sweepListinthread.fftNum * localSweepConfig.firstper;
                                            //last fft point valid num
                                            n2 = sweepListinthread.fftNum * localSweepConfig.secper;
                                            //first segment points num
                                            n3 = sweepListinthread.comNum[0].segmentDataNum * sweepListinthread.fftNum;
                                            //second segment valid points num
                                            n4 = tempsum - n3 - sweepListinthread.fftNum + n2;
                                            //first segment last valid point index
                                            n5 = n3 - sweepListinthread.fftNum + n1;
                                        }
                                    if(1 == sweepListinthread.segmentNum)
                                        {
                                            //1113 steve
                                            if(0 != n1)
                                                {
                                                    tempsum -= (sweepListinthread.fftNum - n1);
                                                    //extract data
                                                    //                                                    for(i = 0;i < sweepListinthread.segmentsDataSumNum - sweepListinthread.fftNum;i++)
                                                    //                                                        {
                                                    //                                                            midInsertBuffer[n1 + i] = midInsertBuffer[sweepListinthread.fftNum + i];
                                                    //                                                        }
                                                }
                                        }
                                    else
                                        {
                                            if(0 != n1)
                                                {
                                                    tempsum -= (sweepListinthread.fftNum - n1);
                                                }
                                            if(0 != n2)
                                                {
                                                    tempsum -= (sweepListinthread.fftNum - n2);
                                                }

                                            for(i = 0;i < n4;i++)
                                                {
                                                    midInsertBuffer[n5 + i] = midInsertBuffer[n3 + i];
                                                }
                                        }
                                }

                            //insert action
                            DiInt32 trueinsertnum = 0;
                            DiReal64 tempfrac = 0.;
                            DiInt32 m = 0;
                            DiInt32 n = 0;

                            if(tempsum <= 1)
                                {
                                    for(m = 0; m < localSweepConfig.TracePoint;m++)
                                        {
                                            acqLocBuffer[m] = midInsertBuffer[0];
                                        }
                                }
                            else
                                {
                                    //0904
                                    //0831
                                    if(0 == ireflesh)
                                        {
                                            gperinsertnum = (0.1 * 10 * localSweepConfig.TracePoint - tempsum) / (tempsum - 1);
                                            gperinsertintpart = (DiInt32)gperinsertnum;
                                            gperinsertfracpart = gperinsertnum - gperinsertintpart;
                                        }
                                    DiInt32 k = 0;
                                    for(m = 0;m < tempsum - 1;m++)
                                        {
                                            tempfrac += gperinsertfracpart;
                                            if(tempfrac - 1.0 > -1.0e-6)
                                                {
                                                    tempfrac -= 1.0;
                                                    trueinsertnum = gperinsertintpart + 1;
                                                }
                                            else
                                                {
                                                    trueinsertnum = gperinsertintpart;
                                                }

                                            DiReal64 tempdeta = (midInsertBuffer[m + 1] - midInsertBuffer[m]) / (trueinsertnum + 1);
                                            acqLocBuffer[k++] = midInsertBuffer[m];
                                            for(n = 0;n < trueinsertnum;n++)
                                                {
                                                    acqLocBuffer[k++] = acqLocBuffer[k - 2] + tempdeta;
                                                }
                                        }
                                    acqLocBuffer[k] = midInsertBuffer[tempsum - 1];
                                }
                            ireflesh = 1;
                        }
                    if(temptrigflag)
                        {
                            //call get temper interface
                            GetTemperCalcDatas(localSweepConfig.StartFreq,localSweepConfig.StopFreq,localSweepConfig.TracePoint,localtempcalc,tempercalcbuffer,localSweepConfig.SPANMode);
                            temptrigflag = !temptrigflag;
                        }
                    GetCtrlInHand(syncHandle);
//Tony 190628
		    //if(6 == sm_config_measure->MeasureMode)
		    //{
			//
		    //printf("intersource %d  ",intersource);
		    //printf("uSweepCompleteFlag %d  ",sm_config_sweep->uSweepCompleteFlag);
		    //printf("SweepType is %d  ",sm_config_sweep->SweepType);
		    //printf("ifinish is %d  ",ifinish);
		    //printf("detectorTime is %u\n",detectorTime);

		    //}
		    
//Tony 190705  0 means old and use ifinish
//	       1 means use detectorTime
#if 0
                    if(ifinish)
                        {
                            for(i = 0;i < BIT_DOTNUM;i++)
                                {
                                    sm_sweep_data->_PwrLevel[i] = 10 * log10(*(acqLocBuffer + i) + 0.000001) - midCalcBuffer[i] + tempercalcbuffer[i];
                                }
				//Tony 190628
				if(detectorTime == localSweepConfig.TracePoint -1)
			    {
					
                            ifinish = 0;
                            if(!intersource)
                                {
						ifinish = 0;
                                    sm_config_sweep->uSweepCompleteFlag = 1;
                                    gwhole = 1;
                                }
                        }
                        }
                    else
                        {
                                for(i = 0;i < BIT_DOTNUM;i++)
                                {
                                    sm_sweep_data->_PwrLevel[i] = 10 * log10(*(acqLocBuffer + i) + 0.000001) - midCalcBuffer[i] + tempercalcbuffer[i];
                                }
				sm_sweep_data->CalData = tempercalcbuffer[i] - midCalcBuffer[i];
                        }
#else
		    for(i = 0;i < BIT_DOTNUM;i++)
                    {
                         sm_sweep_data->_PwrLevel[i] = 10 * log10(*(acqLocBuffer + i) + 0.000001) - midCalcBuffer[i] + tempercalcbuffer[i];
			   //sm_sweep_data->_PwrLevel[i] = 10 * log10(*(acqLocBuffer + i) + 0.000001)  - 200;
                    }
		    
		    sm_sweep_data->CalData = tempercalcbuffer[0] - midCalcBuffer[0];
		    //printf("cal data is %lf\n",sm_sweep_data->CalData);

		    if(3 == sm_config_measure->MeasureMode || 6 == sm_config_measure->MeasureMode)
		    {
			if(detectorTime == localSweepConfig.TracePoint -1)
			{
				if(ifinish)
				{
					if(!intersource)
					{
						ifinish = 0;
						gwhole = 1;
						sm_config_sweep->uSweepCompleteFlag = 1;
						sm_config_sweep->uMinMaxHoldComplete = 1;
					}
				}
				
			}
			else
			{
				if(sm_config_sweep->ListenState == OFF && detectorTime == lastdetectorTime)
				{
					sm_config_sweep->uSweepCompleteFlag = 1;
					sm_config_sweep->uMinMaxHoldComplete = 1;
				}
			}
		    }
	            //printf("lastdetectorTime is %u",lastdetectorTime);
		    //printf("detectorTime is %u",detectorTime);	
		    //printf("uSweepCompleteFlag is %u\n",sm_config_sweep->uSweepCompleteFlag);
#endif  
                    //memcpy(sm_sweep_data->_PwrLevel,acqLocBuffer,localSweepConfig.TracePoint << 3);
                    ReleaseCtrlInHand(guiHandle);

                }
            else
                {
                    usleep(1000);
                }

        }while(gappexit.acqthreadExit);//while(syncMana.AppExit);
    //while(sm_bsa_run_sync->appexit);
    gappexit.listenthreadExit = 0;
    iBack = SetSwpStop(bitdevHandle);
    if(iBack < 0)
        {
            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
            return NULL;
        }
    iBack = SetSwpInterrupt(bitdevHandle);
    if(iBack < 0)
        {
            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
            return NULL;
        }
    
    SetSwpInterruptStop(bitdevHandle);

    return NULL;
}
#endif



static DiReal64 GetMaxVal(DiReal64* pbuffer,int num)
{
    DiReal64 temp = *pbuffer;
    int i = 0;
    for(i = 0;i < num;i++)
        {
            if(temp < *(pbuffer + i))
                temp = *(pbuffer + i);
        }
    return temp;
}

static DiReal64 GetMinVal(DiReal64* pbuffer,int num)
{
    DiReal64 temp = *pbuffer;
    int i = 0;
    for(i = 0;i < num;i++)
        {
            if(temp > *(pbuffer + i))
                temp = *(pbuffer + i);
        }
    return temp;
}

static void PassAcqParamFromShmToLocal()
{
    localSweepConfig.Preamp = sm_config_sweep->Preamp;
    localSweepConfig.StartFreq = sm_config_sweep->StartFreq;
    localSweepConfig.StopFreq = sm_config_sweep->StopFreq;
    localSweepConfig.attenAuto = sm_config_sweep->attenAuto;
    localSweepConfig.attenValue = sm_config_sweep->attenValue;
    //0503
    localSweepConfig.CenterFreq = sm_config_sweep->CenterFreq;

    //0904
    localSweepConfig.checkinsert = sm_config_sweep->checkinsert;
    localSweepConfig.firstper = sm_config_sweep->firstper;
    localSweepConfig.secper = sm_config_sweep->secper;
    localSweepConfig.spanperstep = sm_config_sweep->spanperstep;
    sweepListinthread.fftNum = sm_sweep_num->fftNum;
    sweepListinthread.segmentNum = sm_sweep_num->segmentNum;
    sweepListinthread.segmentsDataSumNum = sm_sweep_num->segmentsDataSumNum;
    memcpy(sweepListinthread.comNum,sm_sweep_num->comNum,sizeof(sweepListinthread.comNum));
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

    fp = fopen(pPath, "r");
    if (NULL == fp)
        {
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
    return 0;
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
            free(bitFreqList.param);
            bitFreqList.param = NULL;
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

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-06-19}
*/
DiInt32 GetTemperCalcDatas(DiReal64 startfreq,DiReal64 stopfreq,DiInt32 datanum,DiReal64 tempercoef,DiPReal64 calcresult,DiInt32 zeroflag)
{
    //zerospan only one point
    DiInt32 im = twicenum;
    if(dCompare2(tempercoef,0.0))
    {
        im = 0;
    }
    DiInt32 i = 0;
    DiInt32 isindex = 0;
    if(zeroflag)
        {
            calcresult[0] = *(pcalcdata + im + GetFreqChannelIndexSec(startfreq,isindex) - 1) * tempercoef;
          for(i = 1;i < datanum;i++)
                {
                    *(calcresult + i) = *calcresult;
                }
       }
    else
        {
            DiReal64 mstep = (stopfreq - startfreq) / (datanum - 1);
#if SEG_CHANGE_NEW	 
   if((stopfreq - startfreq) <= SEG_MINSPAN)
    	{
    	    mstep = 0;
    	}
 #endif
            DiReal64 mfreq = startfreq;
            for(i = 0;i < datanum;i++)
                {
                    isindex = GetFreqChannelIndexSec(mfreq,isindex);
                    calcresult[i] = *(pcalcdata + im + isindex - 1) * tempercoef;
                    mfreq += mstep;
                }
        }
    return 0;
}

//static const DiReal64 ATTENZERODOORWHENOFF = -5.0;
static const DiReal64 ATTENZERODOORWHENOFF = -10.0;
static const DiReal64 ATTENZEROWHENOFF = -10.0;
static const int ZEROATTENUM = 4;
//when set refLevel or atten,the mid msg object will do hardware ctrl,
//and trig the action to get the calc data again;
#ifdef BIT_F239
static DiReal64 FREQMAX = 43000000000.;
#endif
#ifdef BIT_F238
static DiReal64 FREQMAX = 43000000000.;
#endif
#ifdef BIT_F238_SMART
static DiReal64 FREQMAX = 15000000000.;
#endif
DiInt32 GetCalcDataWhenPreAmpOff(DiReal64 startfreq,DiReal64 stopfreq,DiInt32 datanum,DiReal64 refl,DiInt32 autoflag,DiReal64 manatten,DiReal64* calcresult)
{
    autoflag = !!autoflag;
     DiReal64 mstep = (stopfreq - startfreq) / (datanum - 1);
#if SEG_CHANGE_NEW	 
   if((stopfreq - startfreq) <= SEG_MINSPAN)
    	{
    	    mstep = 0;
    	}
 #endif
    DiReal64 mfreq = 0.0;
    DiReal64 mfdeta = 0.0;
    int i = 0,istart = 0,istop = 0;    

    int ioverflow = 0;//when un 0 means freq is over the largest freq;
    if(autoflag && refl <= 20.0)
        {
            int index0;
            int setchannelIndex = 0;           
            //means will used -10dB datas
            if(refl <= ATTENZERODOORWHENOFF)
                {
                    index0 = GetpreOffAttenIndex(ATTENZEROWHENOFF);
                    setchannelIndex = index0;
                    int icalcIndex0 = bitFreqList.count * index0;

                    //< -5.0 ~ -180.0,means using -10.0dB calc datas
                    //means deta value is 0,direct use calc datas
                    //Linear interpolation for filling datas
                    for(i = 0; i < datanum; i++)
                        {
                            //get freq location,start index and stop index
                            mfreq = startfreq + i * mstep;
                            GetStartAndStopIndex(mfreq,istart,&istart,&istop,(i + 1) % datanum);
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
                                    calcresult[i] = *(preOffCalcResult.param + icalcIndex0 + istart);
                                }
                            else if(mfreq >= FREQMAX)
                                {
                                    calcresult[i] = *(preOffCalcResult.param + icalcIndex0 + ioverflow);
                                }
                            else
                                {
                                    calcresult[i] = mfdeta * (*(preOffCalcResult.param + icalcIndex0 + istop)  - *(preOffCalcResult.param + icalcIndex0 + istart))
                                            / (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOffCalcResult.param + icalcIndex0 + istart);
                                }
							}
                        }
            else
                {
                    index0 = GetpreOffAttenIndex(refl);
//                    printf("anto pre off atten index is %d\n",index0);
                    int icalcIndex0 = bitFreqList.count * index0;
                    setchannelIndex = index0;
                    for(i = 0; i < datanum; i++)
                        {
                            //1119 steve
                            //get freq location,start index and stop index
                            mfreq = startfreq + i * mstep;

                            GetStartAndStopIndex(mfreq,istart,&istart,&istop,(i + 1) % datanum);
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
                                    calcresult[i] = *(preOffCalcResult.param + icalcIndex0 + istart);
                                }
                            else if(mfreq >= FREQMAX)
                                {
                                    calcresult[i] = *(preOffCalcResult.param + icalcIndex0 + ioverflow);
                                }
                            else
                                {
                                    calcresult[i] = mfdeta * (*(preOffCalcResult.param + icalcIndex0 + istop)  - *(preOffCalcResult.param + icalcIndex0 + istart))
                                            / (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOffCalcResult.param + icalcIndex0 + istart);
                                }
                        }
                }
        }
    //in the man mode,means only set atten,and ref\ifgain not change
    else
        {
            //calc needed calc datas
            int inowindex = GetAttenIndexOff(manatten);
//            printf("manu pre off atten index is %d\n",inowindex);
            DiReal64 ideta = manatten - 30.0;
            if(ideta <= 0.0)
                {
                    ideta = 0.0;
                }
            int icalcIndex0 = bitFreqList.count * inowindex;
            for(i = 0; i < datanum; i++)
                {
                    mfreq = startfreq + i * mstep;
                    GetStartAndStopIndex(mfreq,istart,&istart,&istop,(i + 1) % datanum);
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
                            calcresult[i] = *(preOffCalcResult.param + icalcIndex0 + istart) - ideta;
                        }
                    else if(mfreq >= FREQMAX)
                        {
                            calcresult[i] = *(preOffCalcResult.param + icalcIndex0 + ioverflow) - ideta;
                        }
                    else
                        {
                            calcresult[i] = mfdeta * (*(preOffCalcResult.param + icalcIndex0 + istop)  - *(preOffCalcResult.param + icalcIndex0 + istart))
                                    / (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOffCalcResult.param + icalcIndex0 + istart) - ideta;
                        }
                }
        }
    return 0;
}

static const DiReal64 ATTENZERODOORWHENON = -30.0;
//static const DiReal64 ATTENZERODOORWHENON = -25.0;
static const DiReal64 ATTENZEROWHENON = -30.0;
//20180420
DiInt32 GetCalcDataWhenPreAmpOn(DiReal64 startfreq,DiReal64 stopfreq,DiInt32 datanum,DiReal64 refl,DiInt32 autoflag,DiReal64 manatten,DiReal64* calcresult)
{        
    autoflag = !!autoflag;
    DiReal64 mstep = (stopfreq - startfreq) / (datanum - 1);
#if SEG_CHANGE_NEW	 
   if((stopfreq - startfreq) <= SEG_MINSPAN)
    	{
    	    mstep = 0;
    	}
 #endif
    DiReal64 mfreq = 0.0;
    DiReal64 mfdeta = 0.0;
    int i = 0,istart = 0,istop = 0;
    int iBack = 0;
    //means set atten auto
    int ioverflow = 0;//when un 0 means freq is over the largest freq;

    if(autoflag)
        {
            int index0,index1 = 0;
            int setchannelIndex = 0;
            DiReal64 deta = 0.0;

            //means will used -10dB datas
//            if(refl < ATTENZERODOORWHENON)
            if(refl <= ATTENZERODOORWHENON)
                {
                    index0 = GetpreOnAttenIndex(ATTENZEROWHENON);
                    setchannelIndex = index0;
                    int icalcIndex0 = bitFreqList.count * index0;

                    //means deta value is 0,direct use calc datas
                    //Linear interpolation for filling datas
                    for(i = 0; i < datanum; i++)
                        {
                            //get freq location,start index and stop index
                            mfreq = startfreq + i * mstep;
                            GetStartAndStopIndex(mfreq,istart,&istart,&istop,(i + 1) % datanum);
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
                                    calcresult[i] = *(preOnCalcResult.param + icalcIndex0 + istart);
                                }
                            else if(mfreq >= FREQMAX)
                                {
                                    calcresult[i] = *(preOnCalcResult.param + icalcIndex0 + ioverflow);
                                }
                            else
                                {
                                    calcresult[i] = mfdeta * (*(preOnCalcResult.param + icalcIndex0 + istop)  - *(preOnCalcResult.param + icalcIndex0 + istart))
                                            / (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOnCalcResult.param + icalcIndex0 + istart);
                                }
                        }
                }
            else
                {
                    index0 = GetpreOnAttenIndex(refl);
                    int icalcIndex0 = bitFreqList.count * index0;
                    setchannelIndex = index0;
                    for(i = 0; i < datanum; i++)
                        {
                            //get freq location,start index and stop index
                            mfreq = startfreq + i * mstep;
                            GetStartAndStopIndex(mfreq,istart,&istart,&istop,(i + 1) % datanum);
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
                                    calcresult[i] = *(preOnCalcResult.param + icalcIndex0 + istart);
                                }
                            else if(mfreq >= FREQMAX)
                                {
                                    calcresult[i] = *(preOnCalcResult.param + icalcIndex0 + ioverflow);
                                }
                            else
                                {
                                    calcresult[i] = mfdeta * (*(preOnCalcResult.param + icalcIndex0 + istop)  - *(preOnCalcResult.param + icalcIndex0 + istart))
                                            / (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOnCalcResult.param + icalcIndex0 + istart);
                                }
                        }
                }

        }
    //in the man mode,means only set atten,and ref not change
    else
        {
            //calc needed calc datas
            //use lastatten and now atten to get the deta datas
            int inowindex = GetAttenIndexOn(manatten);
            int icalcIndex0 = bitFreqList.count * inowindex;
            for(i = 0; i < datanum; i++)
                {
                    mfreq = startfreq + i * mstep;
                    GetStartAndStopIndex(mfreq,istart,&istart,&istop,(i + 1) % datanum);
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
                            calcresult[i] = *(preOnCalcResult.param + icalcIndex0 + istart);
                        }
                    else if(mfreq >= FREQMAX)
                        {
                            calcresult[i] = *(preOnCalcResult.param + icalcIndex0 + ioverflow);
                        }
                    else
                        {
                            calcresult[i] = mfdeta * (*(preOnCalcResult.param + icalcIndex0 + istop)  - *(preOnCalcResult.param + icalcIndex0 + istart))
                                    / (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOnCalcResult.param + icalcIndex0 + istart);

                        }
                }

        }
    return 0;
}

static void GetStartAndStopIndex(DiReal64 freqHz,int serStart,int* startIndex,int* stopIndex,int islastpoint)
{
    int i = 0,j = 0;
    int ilen = GetFreqlistNum();
    if(freqHz >= *(bitFreqList.param + bitFreqList.count - 1))
        {
            *startIndex = bitFreqList.count;
            return;
        }
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
                            *startIndex = i - 1;
#if 0
                           if(islastpoint == 1 || islastpoint == 801)
#else
			if(islastpoint)
#endif
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

static int GetpreOffAttenIndex(DiReal64 refLevel)
{
    int iSum = sizeof(ifGainOff) / sizeof(CHANNELGAIN);
    int i = 0;
    for(i = 0;i < iSum;i++)
        {
//            if(refLevel >= ifGainOff[i].refLevel)
//                return i;
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

static int GetpreOnAttenIndex(DiReal64 refLevel)
{
    int iSum = sizeof(ifGainOn) / sizeof(CHANNELGAIN);
    int i = 0;
    for(i = 0;i < iSum;i++)
        {
//            if(refLevel >= ifGainOn[i].refLevel)
//                return i;
            if(refLevel > ifGainOn[i].refLevel)
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

static int GetAttenIndexOff(DiReal64 attendB)
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

static int GetAttenIndexOn(DiReal64 attendB)
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
#if DEBUG_OUTPUT
            printf("op errro,%d:%s",errno,strerror(errno));
#endif
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
#if DEBUG_OUTPUT
            printf("op error,%d:%s",errno,strerror(errno));
#endif
        }
    return;
}

DiInt32 GetCalcDataWhenPreAmpOffZeroSpan(DiReal64 freq,DiInt32 datanum,DiReal64 refl,DiInt32 autoflag,DiReal64 manatten,DiReal64* calcresult)
{
    autoflag = !!autoflag;
    DiReal64 mfreq = freq;
    DiReal64 mfdeta = 0.0;
    int istart = 0,istop = 0;    
    //means set atten and IF gain auto
    int ioverflow = 0;//when un 0 means freq is over the largest freq;

    DiReal64 ideta = 0.0;
    if(autoflag && refl <= 20.0)
        {
            int index0;
            int setchannelIndex = 0;

            //means will used -10dB datas
            if(refl <= ATTENZERODOORWHENOFF)
                {
                    index0 = GetpreOffAttenIndex(ATTENZEROWHENOFF);
                    setchannelIndex = index0;
                    int icalcIndex0 = bitFreqList.count * index0;

                    //means deta value is 0,direct use calc datas
                    //Linear interpolation for filling datas
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
                            calcresult[0] = mfdeta * (*(preOffCalcResult.param + icalcIndex0 + istop)  - *(preOffCalcResult.param + icalcIndex0 + istart))
                                    / (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOffCalcResult.param + icalcIndex0 + istart);
                        }
                }
            else
                {
                    index0 = GetpreOffAttenIndex(refl);
                    int icalcIndex0 = bitFreqList.count * index0;
                    setchannelIndex = index0;

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

///
/// \brief ResampleInsert:when data num less than show num to use and only under fft mode;
/// \param poribuffer:ori data buffer;
/// \param orinum:actual data num, and always less than ori buffer size;
/// \param dataindex:to decided left and right data bound to use for inserting,less than orinum;
/// \param poutbuffer:put insert value;
/// \param outnum:call one time to produce insert data num;
/// \param refunc:insert func template;
/// \param refnum:refunc buffer datas num;
static void ResampleInsert(DiPReal64 poribuffer,DiInt32 orinum,DiInt32 dataindex,DiPReal64 poutbuffer,DiInt32 outnum,DiPReal64 refunc,DiInt32 refnum)
{
    //to decide which oridata to use for inserting,and the max num is influence << 1 - 1
    DiInt32 istart = 0;
    DiInt32 istop = 0;

    //the model is 8 1 8,total is 17
    //left part ori data num <= 8,include dataindex
    if(dataindex <= INFLUENCENUM)//index not num
        {
            istart = 0;
        }
    else
        {
            istart = dataindex - INFLUENCENUM;
        }
    DiInt32 leftnumincludemid = dataindex - istart + 1;

    //right part ori data num <= 8
    if(dataindex + INFLUENCENUM >= orinum -1)//index not num
        {
            istop = orinum - 1;
        }
    else
        {
            istop = dataindex + INFLUENCENUM;
        }
    DiInt32 rightnum = istop - dataindex;

    //how many point out one
    DiReal64 dstepdeta = 0.1 * 10 * OVERNUM / (outnum + 1);
    DiInt32 i = 0;
    DiInt32 j = 0;

    DiInt32 releftindex = 0;
    DiInt32 rerightindex = 0;
    //do insert actions
    DiInt32 mole = 0;
    DiReal64 tempsinc = 0.0;
    for(i = 0;i < outnum;i++)
        {
            *(poutbuffer + i) = 0.0;
            releftindex = (DiInt32)((i + 1) * dstepdeta);
            rerightindex = OVERNUM - releftindex;
            //left datas use zheng xiang index
            for(j = 0;j < leftnumincludemid;j++)
                {
                    mole = leftnumincludemid - j - 1;
                    if(INFLUENCENUM == mole)
                        {
                            tempsinc = 0.0;
                        }
                    else
                        {
                            tempsinc = *(refunc + ((leftnumincludemid - j - 1) % INFLUENCENUM) * OVERNUM + releftindex);
                        }
                    *(poutbuffer + i) += *(poribuffer + istart + j) * tempsinc;
                }
            //right datas use dui chen index
            for(j = 0;j < rightnum;j++)
                {
                    *(poutbuffer + i) += *(poribuffer + dataindex + j + 1) * *(refunc + j * OVERNUM + rerightindex);
                }
        }
    return;
}

