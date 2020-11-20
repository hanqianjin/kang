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
//==============================================================================

//==============================================================================

static const DiReal64 minFreqHz = 9000.0;
static const DiReal64 maxFreqHz = 3.2e10;
static const DiInt32 checkTypenum = 6;//check wave nums

static const DiReal64 firStep = 0.2;//FIR lo step
static const DiReal64 rbwtospan = 0.01;//span to rbw,when small down 1
static const DiReal64 vbwtorbw = 1.0;//vbw to rbw
static const DiInt32  CHECKMODEMAX = 5;//dector max nums
static const DiInt32 REF_CLOCK = 90000000;//ref clock
static const DiReal64 fstimens = 1000. / 45;//acq time
//==============================================================================
// Types
static CHANNEL_PARAM chparamlist[] =
{
	//rbwHz fsHz  stepHz						 Nfs
	{3000, 45000, 33750, 32,   2.133, 0.0, 0.75, 32000},
	{1000, 45000, 33750, 128,  2.844, 0.0, 0.75, 128000},
	{300,  45000, 33750, 256,  1.707, 0.0, 0.75, 256000},
	{100,  45000, 33750, 1024, 2.275, 0.0, 0.75, 1024000},
	{30,   4500,  3375,  256,  1.707, 0.0, 0.75, 2560000},
	{10,   4500,  3375,  1024, 2.275, 0.0, 0.75, 10240000},
	{3,    4500,  3375,  4096, 2.731, 0.0, 0.75, 40960000},
	{1,    2250,  1800,  8192, 3.641, 0.0, 0.8,  1638400000}
};/*FFT mode*/

//static SWEEP_NUM sweepnumList = {0};/*calc the nums of the fft and fir mode*/
/*undo
	  need inial datas when finished the app*/


//==============================================================================
// Static global variables
//this part defined by south korea
static _CONFIG_SWEEP bit_config_sweep;
static _CONFIG_MEASURE bit_config_measure;
static _CONFIG_SYSTEM bit_config_system;
static _SWEEP_DATA bit_sweep_data;
static _MEASURE_DATA bit_measure_data;
static _SYSTEM_INFO bit_system_info;
static _SM_SYNC bit_sm_sync;

//==============================================================================
// Static functions
static void GetSegmentWaveIndex(void* param);
static void RefCalSweepParams(DiInt32 sweepMode);
extern DiInt32 GetrbwIndex(DiReal64 rbwHz);
static void GetFreqDivValue(DiReal64 freqHz,DiPUInt32 intdiv,DiPUInt32 fracdiv);
static void GetLastPartTime(DiInt32 iIndex);
static void TrigResweep(void* param);
static DiInt32 GetFftRbwIndex();
static void ParamConvertByRbw(DiInt32 iIndex);
static void ListenEngine();

//==============================================================================
// Global variables												//6
extern const DiReal64 rbwList[];
const DiReal64 dealTimeList[] = {1000.0  ,1000.0  ,1000.0  ,1000.0  ,1000.0  ,1000.0  ,1000.0  ,1000.0 ,1000.0 ,1000.0,1000.0,1000.0,1000.0,1000.0,1000.0};/*last part spend time*/
//============================================================================== 
DiSession bitdevHandle = 0;  
static SWEEP_NUM sweepListinthread = {0};/*just used in the listen and down param thread*/
static void GetSweepInterruptState(DiPUInt32 state);//provided by xujiwen driver
extern const DiReal64 freqChannelList[];
extern LO_FREQ_DIV lodivList[];
extern _SM_SYNC syncMana;
extern DiInt32 GetFreqChannelIndex(DiReal64 freqHz);

//share shm
extern PSWEEP_DATA sm_sweep_data;
extern PMEASURE_DATA sm_measure_data;
extern PSM_SYNC sm_sync;
extern PSWEEP_NUM sm_sweep_num;
extern PCONFIG_SWEEP sm_config_sweep;
//===============================================================================
//change bityang,0323
static DiInt32 listState = 0;//1 means single sweep mode,and sweep is over
extern SWEEPCTRL CTRL_SWEEP_MODE;

void* ListenAndDownSweepParamFunc(void *param)
{	
	do
	{
		if(SWEEP_CONTI == CTRL_SWEEP_MODE)
		{
			ListenEngine();					
		}
		else if(SWEEP_SINGLE == CTRL_SWEEP_MODE)
		{
			ListenEngine();
			sm_config_sweep->ListenState = OFF;
			CTRL_SWEEP_MODE = SWEEP_IDLE;			
		}
		else
		{			
			usleep(100000);
		}
	}
	while(syncMana.AppExit);
	printf("listen seg sweep interrupt thread stop\n");
	return NULL;
}

static void ListenEngine()
{	
		DiInt32 iBack = 0; 
		sm_config_sweep->ListenState = ON;
		DiInt32 i = 0;
		DiInt32 interState = 0;
		if(syncMana.DeviceMsgUpdate)
		{
			//updataparam
			//memcpy(&sweepListinthread,&sweepnumList,sizeof(SWEEP_NUM));
			//get the sweep param from the gui shm
			memcpy(&sweepListinthread,sm_sweep_num,sizeof(SWEEP_NUM));
			printf("the segment num is %u\n",sweepListinthread.segmentNum);
#if 1
			for(i = 0;i < sweepListinthread.segmentNum;i++)
			{
				printf("segment index is %u,segment data num is %u\n",sweepListinthread.comNum[i].segmentIndex,sweepListinthread.comNum[i].segmentDataNum);
				printf("lo int part is 0x%x,frac part is 0x%x\n",sweepListinthread.comNum[i].seglostartfreqinter,sweepListinthread.comNum[i].seglostartfreqfrac);
				printf("lo step low is 0x%x,high part is 0x%x\n",sweepListinthread.comNum[i].seglosteplow,sweepListinthread.comNum[i].seglostephigh);

				}
#endif 
			syncMana.DeviceMsgUpdate = !syncMana.DeviceMsgUpdate;
			printf("the param has update\n");						
		}
		
		//0424
		//addr clear
		DataBufferClear(bitdevHandle,0);

		for(i = 0; i < sweepListinthread.segmentNum; i++)
		{ 
			//when receive the soft interrupt,break   
			if(syncMana.AppExit && syncMana.DeviceMsgUpdate)
				break;
			
			RfChannelChoosebyIndex(bitdevHandle,sweepListinthread.comNum[i].segmentIndex);
			printf("the segment index num is %d\n",sweepListinthread.comNum[i].segmentIndex);
			//
			SetSwpStop(bitdevHandle);
			//down the param
			//the start freq div frq
			SetFirLoFreq(bitdevHandle,(sweepListinthread.comNum + i) -> seglostartfreqinter,(sweepListinthread.comNum + i) -> seglostartfreqfrac);
			
			//the lo step
			SetFirLoStepFreq(bitdevHandle,(sweepListinthread.comNum + i) -> seglosteplow, (sweepListinthread.comNum + i) -> seglostephigh);
			//SetFirLoStepFreq(bitdevHandle,0x16c16c16, 0x16c);  
			
			//the seg last part stay time
			// SetFirLoStaytime(bitdevHandle,sweepListinthread.seglokeeptime);
			SetFirLoStaytime(bitdevHandle,0.1);  
			
			//segment sum time 
			SetTotalSwpTimeLow(bitdevHandle,sweepListinthread.comNum[i].persegsweeptimes & 0xffffffff);
			SetTotalSwpTimeHigh(bitdevHandle,sweepListinthread.comNum[i].persegsweeptimes >> 32 & 0xffffffff);
			//if fft single acq time
			if(3 == bit_config_sweep.sweepMode)
			{
				SetFftDotSwpTime(bitdevHandle,sweepListinthread.singlefftTime);
				//SetSegPoint(bitdevHandle,0);
				SetSegPoint(bitdevHandle,(sweepListinthread.comNum + i) -> segmentDataNum); 
			}
			else
			{
				//segment points num,means lo step times
				SetSegPoint(bitdevHandle,(sweepListinthread.comNum + i) -> segmentDataNum);
				//SetSegPoint(bitdevHandle,201);				
			}		

			//resweet			
			SetSwpRun(bitdevHandle);

			//query the interrupt
			//when receive the soft interrupt,break				
			while(syncMana.AppExit && !syncMana.DeviceMsgUpdate && !interState)
			{
				GetSweepInterruptState(&interState); 
			}			
			//clear the state
			interState = 0; 
		}
		return;		
}

static void GetSweepInterruptState(DiPUInt32 state)
{
	usleep(1000);	
	return;
}
// Global functions
/*
purpose: config start and stop freq
func:DiInst_ConfigureFrequencyStartStop
param:<in>devHandle:dev's ctrl handle from ini
	  <in>startFrequency:start freq in Hz
	  <in>stopFrequency:stop freq in Hz
	  value range:9kHz~32GHz
return:>=0 is ok
*/
static DiInt32 rbwTrigDoor = 0;/*set rbw when 0 ifself,1 function call */
DiInt32 DiInst_ConfigureFrequencyStartStop (DiSession devHandle,DiReal64 startFrequency,DiReal64 stopFrequency)
{
	//check param
	startFrequency = startFrequency < minFreqHz + ESP ? minFreqHz : startFrequency;
	stopFrequency = stopFrequency > maxFreqHz + ESP ? maxFreqHz : stopFrequency;
	startFrequency = startFrequency > stopFrequency ? minFreqHz : startFrequency;

	//reflesh params
	bit_config_sweep.StartFreq = startFrequency;
	bit_config_sweep.StopFreq = stopFrequency;
	bit_config_sweep.CenterFreq = 0.5 * (stopFrequency + startFrequency);
	bit_config_sweep.SPANFreq = stopFrequency - startFrequency;  

	//get segment index   bit_config_sweep.sweepMode
	GetSegmentWaveIndex(NULL);
	//associate with rbw
	if(bit_config_sweep.RBWAuto)
	{
		//calc rbw through the span,0.01
		DiInt32 tempIndexcalc = GetrbwIndex(bit_config_sweep.SPANFreq * rbwtospan);
		DiInt32 tempIndexnow = GetrbwIndex((DiReal64)bit_config_sweep.RBW);  
		if(tempIndexnow != tempIndexcalc)
		{
			rbwTrigDoor = 1;
			DiInst_ConfigureSweepCoupling(devHandle,bit_config_sweep.RBWAuto,rbwList[tempIndexcalc],bit_config_sweep.VBWAuto,bit_config_sweep.VBW,bit_config_sweep.VBWTORBWAuto,bit_config_sweep.VBWTORBW);
			rbwTrigDoor = !rbwTrigDoor;
		}
	}
	//calculate params by sweet mode
	RefCalSweepParams(bit_config_sweep.sweepMode);

	//trig the resweep sig
	/*in the listen thread will down the ctrl param*/
	TrigResweep(NULL);
	return 0;
}

extern DiInt32 guiHandle;
extern DiInt32 syncHandle;
void GetCtrlInHand(DiInt32 handle);
void ReleaseCtrlInHand(DiInt32 handle);
DiReal64 acqLocBuffer[10000];
DiUInt32 acqb[10000];
void* AcqDataFunc(void *param)
{
	DiInt32 i = 0;
	DiReal64 iacp = 0.0;
	
	DiInt32 ic = 0;
	do
	{
		int iMaxIndex = 0;
		if(0 == sm_config_sweep->ListenState)
		{
			//iacp = 0.0;
			//simu acq				
			//for(i = 0;i<1001;i++)
			//acqLocBuffer[i] = rand();				
			//pthread_mutex_lock(&sm_sync->lockobj);	
			//*(sm_sweep_data->_PwrLevel+i) = rand();
			//if(0 == sm_sync-> BufferSync)
			//{				
	
#if 1
			GetResultData(bitdevHandle,acqb,501);
			for(i = 0;i < 501;i++)
			{
				//printf("the ori data at num %d is:0x%x\n",i,acqb[i]);
				acqLocBuffer[i] = 20 * log10(*(acqb + i) + 0.000001) - 200;
			}	

#endif
			//printf("more......\n\n");	
			GetCtrlInHand(syncHandle);			
			
			memcpy(sm_sweep_data->_PwrLevel,acqLocBuffer,501*8);
			
			/*
			for(i = 0;i<501;i++)
			{
				sm_sweep_data->_PwrLevel[i] = -4 * log(sm_sweep_data->_PwrLevel[i]);
			}
		
			for(i = 249;i<252;i++)
			{
				sm_sweep_data->_PwrLevel[i] += 57.356;
			}
*/
			
			//simulation acq time by bityang,0223
			//usleep(10000);
			ReleaseCtrlInHand(guiHandle);
			//sm_sync-> BufferSync = 1;
			//pthread_mutex_unlock(&sm_sync->lockobj);
			//}
			//sm_measure_data->ACPL = iacp;
			//printf("get the data with lock, the ACPL value is %lf\n",iacp);//sm_measure_data->ACPL);			
#if 0			
if(ic)
			{
				printf("the acq is running...\n");
				ic = !ic;
			}
			else
			{
				printf("the acq is still running...\n");
				ic = !ic;
			}
#endif
			//usleep(10000);//will adjust across rbw
		}
		else
		{
#if 0
			if(ic)
			{
				printf("the acq is pausing...\n");
				ic = !ic;
			}
			else
			{
				ic = !ic;
				printf("the acq is still pausing...\n");
			}
#endif
			usleep(100000);					
		}
	}while(syncMana.AppExit);
	printf("acq data thread stop\n");
	return NULL;
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
}

static void TrigResweep(void* param)
{
//	INNERSOFTINTER = 1;
	return;
}

static void GetSegmentWaveIndex(void* param)
{
	//get the freq segment num
	DiInt32 istartIndex = GetFreqChannelIndex(bit_config_sweep.StartFreq);
	//back
	if(freqChannelList[istartIndex] <= bit_config_sweep.StartFreq + ESP)
	{
	   istartIndex++;
	}
	DiInt32 istopIndex = GetFreqChannelIndex(bit_config_sweep.StopFreq);
	sm_sweep_num->segmentNum = istopIndex - istartIndex + 1;
	DiInt32 i = 0;
	for(i = 0; i < sm_sweep_num->segmentNum; i++)
	{
		//start from zero index,cor with wave index and data nums
		sm_sweep_num->comNum[i].segmentIndex = istartIndex + i;
	}
	return;
}

/*
calc segment nums and per segment's data nums
*/
static void RefCalSweepParams(DiInt32 sweepMode)
{
	DiReal64 dStep = 0.0;
	DiUInt64 dSteptime = 0;
	DiInt32 ifftRbwIndex = 0;
	
	//clear sum time
	sm_sweep_num->sumSweeptime = 0;
	//FIR lo step freq
	if(0 == sweepMode)
	{
		dStep = sm_sweep_num->loStepHz; 
		dSteptime = 1;//normal to fs
	}
	else if(3 == sweepMode)
	{
		//lo step cor points
		dStep = sm_sweep_num->loStepHz / (sm_sweep_num->fftNum * sm_sweep_num->validRatio);
		ifftRbwIndex = GetFftRbwIndex();
		dSteptime = chparamlist[ifftRbwIndex].singleacqTime;
		//set single fft time
		sm_sweep_num->singlefftTime = chparamlist[ifftRbwIndex].singleacqTime;
	}
	//other mode for future

	/*calc the lo step freq div value*/
	//sm_sweep_num->lostepdivfreqlow = (DiUInt32)sm_sweep_num->loStepHz;
	/*temp use 0*/
	//sm_sweep_num->lostepdivfreqhigh = 0;
	
	//calc every seg sweep time and sum sweep time and segment points num
	if(sm_sweep_num->segmentNum > 1)
	{
		DiInt32 iSize = sm_sweep_num->segmentNum - 1;
		DiReal64 dfreqspan = freqChannelList[sm_sweep_num->comNum[0].segmentIndex] - bit_config_sweep.StartFreq;
		//first seg time
		sm_sweep_num->comNum[0].persegsweeptimes = (DiUInt64)ceil(dfreqspan / sm_sweep_num->loStepHz) * dSteptime;
		sm_sweep_num->sumSweeptime += sm_sweep_num->comNum[0].persegsweeptimes;
		
		//first seg points num 
		sm_sweep_num->comNum[0].segmentDataNum = (DiUInt32)(dfreqspan / dStep);
		/*calc the freq div value of every segment start freq*/ 
		GetFreqDivValue(bit_config_sweep.StartFreq,&sm_sweep_num->comNum[0].seglostartfreqinter,&sm_sweep_num->comNum[0].seglostartfreqfrac);
		
		DiInt32 i = 0;
		for(i = 1; i < sm_sweep_num->segmentNum - 1; i++)
		{
			dfreqspan = freqChannelList[sm_sweep_num->comNum[i].segmentIndex] - freqChannelList[sm_sweep_num->comNum[i - 1].segmentIndex];
			sm_sweep_num->comNum[i].persegsweeptimes = (DiUInt64)ceil(dfreqspan / sm_sweep_num->loStepHz) * dSteptime; 
			sm_sweep_num->sumSweeptime += sm_sweep_num->comNum[i].persegsweeptimes;
			
			sm_sweep_num->comNum[i].segmentDataNum = (DiUInt32)(dfreqspan / dStep);
			GetFreqDivValue(freqChannelList[sm_sweep_num->comNum[i].segmentIndex],&sm_sweep_num->comNum[i].seglostartfreqinter,&sm_sweep_num->comNum[i].seglostartfreqfrac);
		}
		
		dfreqspan = bit_config_sweep.StopFreq - freqChannelList[sm_sweep_num->comNum[iSize].segmentIndex - 1];
		sm_sweep_num->comNum[iSize].persegsweeptimes = (DiUInt64)ceil(dfreqspan / sm_sweep_num->loStepHz) * dSteptime; 
		sm_sweep_num->sumSweeptime += sm_sweep_num->comNum[iSize].persegsweeptimes;
		
		//last segments nums
		sm_sweep_num->comNum[iSize].segmentDataNum = (DiUInt32)(dfreqspan / dStep);
		GetFreqDivValue(freqChannelList[sm_sweep_num->comNum[iSize].segmentIndex - 1],&sm_sweep_num->comNum[iSize].seglostartfreqinter,&sm_sweep_num->comNum[iSize].seglostartfreqfrac);
	} 
	//only one segment
	else
	{
		/*calc every segment points*/
		sm_sweep_num->comNum[0].segmentDataNum = (DiUInt32)(bit_config_sweep.SPANFreq / dStep);
		/*calc the freq div value of every segment start freq*/
		GetFreqDivValue(bit_config_sweep.StartFreq,&sm_sweep_num->comNum[0].seglostartfreqinter,&sm_sweep_num->comNum[0].seglostartfreqfrac);
		//calc sweep time
		//if fft mode
		if(3 == sweepMode)
		{
			sm_sweep_num->comNum[0].persegfftsegNum = bit_config_sweep.SPANFreq / sm_sweep_num->loStepHz;
			sm_sweep_num->sumSweeptime = sm_sweep_num->comNum[0].persegfftsegNum * dSteptime;
			sm_sweep_num->comNum[0].persegsweeptimes = sm_sweep_num->sumSweeptime;
		}
		//FIR
		else
		{
			sm_sweep_num->sumSweeptime = sm_sweep_num->comNum[0].segmentDataNum * dSteptime;
			sm_sweep_num->comNum[0].persegsweeptimes = sm_sweep_num->sumSweeptime; 
		}
	}  
	return;
}

static DiInt32 GetFftRbwIndex()
{
	DiInt32 iNum = sizeof(chparamlist) / sizeof(CHANNEL_PARAM);
	DiInt32 i = 0;	
	for(i = 0; i < iNum; i++)
	{
		if(bit_config_sweep.RBW >= (chparamlist+i)->rbwkHz)
			return i;
	}
	return iNum - 1;
}

static void GetFreqDivValue(DiReal64 freqHz,DiPUInt32 intdiv,DiPUInt32 fracdiv)
{
	DiInt32 iIndex = GetFreqChannelIndex(freqHz);
	iIndex = iIndex == 0 ? iIndex : iIndex - 1;
	DiReal64 temp = (freqHz + lodivList[iIndex].iffreq) / REF_CLOCK * lodivList[iIndex].d * lodivList[iIndex].r / lodivList[iIndex].feedback;
	
	*intdiv = (DiUInt32)temp;
	DiUInt64 tempfrac = (DiUInt64)ceil((temp - *intdiv) * 4 * (1 << 16) * (1 << 30)); 
	*fracdiv = (tempfrac & 0xffffffff);
	*intdiv <<= 16;
	*intdiv |= (tempfrac >> 32 & 0xffff);
	return;
}

/*
purpose: config center and span freq
func:DiInst_ConfigureFrequencyCenterSpan
param:<in>devHandle:dev's ctrl handle from ini
	  <in>centerFrequency:center freq in Hz
	  <in>span:span freq in Hz
	  value range:9kHz~32GHz
return:>=0 is ok
*/
DiInt32 DiInst_ConfigureFrequencyCenterSpan (DiSession devHandle,DiReal64 centerFrequency,DiReal64 span)
{
	//check params
	centerFrequency = centerFrequency < minFreqHz ? minFreqHz : centerFrequency;
	centerFrequency = centerFrequency > maxFreqHz ? maxFreqHz : centerFrequency;
	span = span < 0.0 ? 0.0 : span;

	DiInt32 iBack = 0;
	//adjust the span
	if(centerFrequency - 0.5 * span < minFreqHz)
	{
		iBack = DiInst_ConfigureFrequencyStartStop(devHandle,minFreqHz,2 * centerFrequency - minFreqHz);
	}
	else if(centerFrequency + 0.5 * span > maxFreqHz)
	{
		iBack = DiInst_ConfigureFrequencyStartStop(devHandle,centerFrequency * 2 - maxFreqHz,maxFreqHz);
	}
	else
	{
		iBack = DiInst_ConfigureFrequencyStartStop(devHandle,centerFrequency - span * 0.5,centerFrequency + span * 0.5);
	}
	return iBack;
}

/*
purpose: config sweep ctrl
func:DiInst_ConfigureSweepCoupling
param:<in>devHandle:dev's ctrl handle from ini
	  <in>resolutionBandwidthAuto: 1 auto;0 man
	  <in>resolutionBandwidth:5MHz~1Hz
	  <in>videoBandwidthAuto:1 auto;0 man
	  <in>videoBandwidth:3MHz~1Hz
	  <in>vbwtorbwAuto:1 auto;0 man
	  <in>vbwtorbwValue:>zero
return:>=0 is ok
*/
static DiInt32 rbwFlag = 0;//1 state changed
DiInt32 DiInst_ConfigureSweepCoupling (DiSession devHandle,DiUInt32 resolutionBandwidthAuto,DiReal64 resolutionBandwidth,DiUInt32 videoBandwidthAuto,DiReal64 videoBandwidth,DiUInt32 vbwtorbwAuto,DiReal64 vbwtorbwValue)
{
	//check and reflesh param
	resolutionBandwidthAuto = !!resolutionBandwidthAuto;
	bit_config_sweep.RBWAuto = resolutionBandwidthAuto;
	videoBandwidthAuto = !!videoBandwidthAuto;
	bit_config_sweep.VBWAuto = videoBandwidthAuto;
	vbwtorbwAuto = !!vbwtorbwAuto;
	bit_config_sweep.VBWTORBWAuto = vbwtorbwAuto; 
	
	rbwFlag = 0; 
	//adjust the couple param,when rbw is auto
	if(bit_config_sweep.RBWAuto)
	{
		//get the rbw through the span
		DiInt32 spanrbwIndex = GetrbwIndex(bit_config_sweep.SPANFreq * rbwtospan);
		DiInt32 nowIndex = GetrbwIndex((DiReal64)bit_config_sweep.RBW);   
		if(nowIndex != spanrbwIndex)
		{
			rbwFlag = 1;
			bit_config_sweep.RBW = (DiUInt32)rbwList[spanrbwIndex];
			GetLastPartTime(spanrbwIndex);
			if(bit_config_sweep.VBWAuto)
			{
				if(bit_config_sweep.VBWTORBWAuto)
				{
					bit_config_sweep.VBWTORBW = vbwtorbw;
				}
				else
				{
					bit_config_sweep.VBWTORBW = vbwtorbwValue;
				}
				DiInt32 iIndex = GetrbwIndex(bit_config_sweep.RBW * bit_config_sweep.VBWTORBW);
				iIndex = iIndex == 0 ? 1 : iIndex;
				bit_config_sweep.VBW = (DiUInt32)rbwList[iIndex];
			}
			else
			{
				DiInt32 vbwIndex = GetrbwIndex(videoBandwidth);
				bit_config_sweep.VBW = (DiUInt32)rbwList[vbwIndex];
			} 
			
			ParamConvertByRbw(spanrbwIndex); 
			//down rbw and vbw in the ctrlapp   
		}
	}
	//the rbw is man
	else
	{
		rbwFlag = 1;
		DiInt32 rbwIndex = GetrbwIndex(resolutionBandwidth);
		bit_config_sweep.RBW = (DiUInt32)rbwList[rbwIndex];
		GetLastPartTime(rbwIndex);
		//vbw is not 5MHz
		rbwIndex = rbwIndex == 0 ? 1 : rbwIndex;
		//more used
		if(bit_config_sweep.VBWAuto)
		{
			if(bit_config_sweep.VBWTORBWAuto)
			{
				bit_config_sweep.VBWTORBW = vbwtorbw;
			}
			else
			{
				bit_config_sweep.VBWTORBW = vbwtorbwValue;
			}
			bit_config_sweep.VBW = (DiUInt32)((DiInt32)rbwList[rbwIndex] * bit_config_sweep.VBWTORBW);
		}
		else
		{
			DiInt32 vbwIndex = GetrbwIndex(videoBandwidth);
			bit_config_sweep.VBW = (DiUInt32)rbwList[vbwIndex];
		}  
	
		ParamConvertByRbw(rbwIndex);
	} 
	
	if(!rbwTrigDoor && rbwFlag)
	{
		//recalc time
		RefCalSweepParams(bit_config_sweep.sweepMode); 
		//trig the resweep sig
		TrigResweep(NULL);
	}
	return 0;
}

static void ParamConvertByRbw(DiInt32 iIndex)
{
	//get the sweep mode of FIR
	if(iIndex <= 6)
	{
		bit_config_sweep.sweepMode = 0x00;
		//calc lo step
		sm_sweep_num->loStepHz = bit_config_sweep.RBW * firStep;
	}
	else//FFT mode
	{
		bit_config_sweep.sweepMode = 0x03;
		//calc lo step
		sm_sweep_num->loStepHz = chparamlist[GetFftRbwIndex()].stepFreqHz;
		//set fft num
		sm_sweep_num->fftNum = chparamlist[GetFftRbwIndex()].fftNum; 
	}
	return;
}

static void GetLastPartTime(DiInt32 iIndex)
{
	/*the seg last part keep time is decided by rbw,ns*/
	sm_sweep_num->seglokeeptime = (DiUInt32)(dealTimeList[iIndex] / fstimens);
	return;
}

/*
purpose: config acq ctrl
func:DiInst_ConfigureAcquisition
param:<in>devHandle:dev's ctrl handle from ini
	  <in>sweepMode:continue or single or times
	  <in>numberOfTraces:show points
	  <in>detectorType:check mode
return:>=0 is ok
*/
DiInt32 DiInst_ConfigureAcquisition (DiSession devHandle,DiInt32 sweepMode,DiInt32 numberOfTraces,DiInt32 detectorType)
{
	//check param
	sweepMode &= 0x3;
	bit_config_sweep.SweepType = sweepMode;
	detectorType = detectorType > checkTypenum - 1 ? checkTypenum - 1 : detectorType;
	bit_config_sweep.DetectorMode = detectorType;
	bit_config_sweep.TracePoint = numberOfTraces;

	//down commands
	return 0;
}

/*
purpose: config level and atten ctrl
func:DiInst_ConfigureLevel
param:<in>devHandle:dev's ctrl handle from ini
	  <in>amplitudeUnits:
	  <in>inputImpedance:
	  <in>referenceLevel:
	  <in>referenceLevelOffset:
	  <in>attenuationAuto:
	  <in>attenuation:
return:>=0 is ok
*/
DiInt32 DiInst_ConfigureLevel (DiSession devHandle,DiInt32 amplitudeUnits,DiReal64 inputImpedance,DiReal64 referenceLevel,DiReal64 referenceLevelOffset,DiBoolean attenuationAuto,DiReal64 attenuation)
{

}



