//==============================================================================
//
// Title:		SaDataStruct.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/1/16 at 14:18:22 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __SaDataStruct_H__
#define __SaDataStruct_H__

#ifdef __cplusplus
extern "C" {
#endif

//==============================================================================
// Include files
#include "BitVisaType.h" 
#include <pthread.h>
#include <errno.h>

//==============================================================================
// Constants
typedef enum {SWEEP_CONTI = 0,SWEEP_SINGLE,SWEEP_IDLE} SWEEPCTRL;
typedef enum {ON = 0,OFF} SWITCHCTRL;

#define RSA_MANA_SHM_KEY 5501
#define SM_Key_ConfigRsaCtrl	5700
#define SM_Key_SweepData	5701
#define SM_Key_Sync	5702
#define SM_Key_ConfigUpdate	5703
#define SM_CTRL_KEY_START    5704

#define SYNC_KEY       5711
#define SYNC_KEY_GUI   5712
#define SYNC_SWEEP     5713

#define SM_Key_TemperCalc 5509

#define RSA_NOTICE_CODE_KEY 5551

//==============================================================================
/*--------------------------mid_msg_deal------------------*/
#define IXT_ConfigSweep (0x00000001) //IXT_ConfigSweep
#define IXS_CenterFreq							0x00000001
#define IXS_SpanFreq							0x00000002
#define IXS_StartFreq							0x00000004
#define IXS_StopFreq							0x00000008
#define IXS_SpanMode							0x00000010
#define IXS_TracePoint							0x00000020
#define IXS_RBW			    					0x00000040
#define IXS_RBWAuto							0x00000080
#define IXS_AcqTime				    			0x00000100
#define IXS_PersisTime							0x00000200
#define IXS_DetectorMode						0x00000400
#define IXS_RefLevel							0x00000800
#define IXS_AttenSelect							0x00001000
#define IXS_SweepType							0x00002000
#define IXS_ExtTrigger							0x00004000
#define IXS_TriggerMode							0x00008000
#define IXS_Preamp							0x00010000
#define IXS_FilterType							0x00020000
#define IXS_Refoffset                           			0x00040000
#define IXS_DPXAmptMin							0x00080000
#define IXS_DPXAmptZoom							0x00100000
#define IXS_FFT_Bucket_Num							0x00200000
#define IXS_Highest_Density                        0x00400000
#define IXS_Lowest_Density                         0x00800000
#define IXS_Fmt_Data                          		 0x01000000
#define IXS_Curve                              0x02000000
#define IXS_Fmt_Trigger_Criterion   0x04000000
#define IXS_DPX_Probability				0x08000000
//#define IXS_Trigger_Delay                      0x02000000
//#define IXS_Trigger_Period                     0x04000000
//#define IXS_Trigger_Video_Level                0x08000000
//#define IXS_Trigger_RF_Level                   0x10000000


/*----------------------------------------------------*/
#define IXT_ConfigMeasure (0x00000002)
#define IXS_Density  0x00000001
#define IXS_Spectrum   0x00000002
#define IXS_Spectrogram  0x00000004
#define IXS_Density_Spectrogram	 0x00000008
//#define IXS_DemodIFBW	  0x00000010
//#define IXS_DemodMode	   0x00000020
//#define IXS_PSFreq		  0x00000040
/*----------------------------------------------------*/
#define IXT_Trigger (0x00000004)
#define IXS_Trigger_Slope						0x00000001
#define IXS_Trigger_Delay						0x00000002
#define IXS_Trigger_Period						0x00000004
#define IXS_Trigger_Video_Level			0x00000008
#define IXS_Trigger_RF_Level					0x00000010
#define IXS_Trigger_HoldOff_Time			0x00000020
/*----------------------------------------------------*/
#define IXT_TEMPER_CALC 						0x00010000

/*----------------------------------------------------*/

//used in ctrl and mana for ctrl app to exit auto
typedef struct
{
    DiUInt32 appexit;
}RSA_RUN_SYNC,*PRSA_RUN_SYNC;

typedef struct
{
  DiReal64 CenterFreq; 	            // Hz
  DiReal64 SpanFreq; 	            // Hz
  DiReal64 StartFreq; 	            // Hz
  DiReal64 StopFreq; 	            // Hz
  DiUInt32 SpanMode;		    // multi fix ana span
  DiUInt32 TracePoint;        // [0]501, [1]1001, [2]2001, [3]3001 (point)
  DiUInt32 RBW; 			    // Hz
  DiUInt32 RBWAuto;		    // [0]Manual, [1]Auto 
  DiUInt32 DetectorMode;	    // [0]Max, [1]Min, [2]Sample, [3]Avg-Power, [4]Avg-Voltage
  DiReal64 RefLevel;				// +10 ~ -150 dBm  
  DiUInt32 SweepType;		    // [0]Continuous, [1]Single, [2]Sweep Offk
  DiUInt32 ExtTrigger;		// [0]Off, [1]On
  DiUInt32 TriggerMode;		// [0]Free Run, [1]Rise, [2]Fall, [3]Delay  
  DiUInt32 Preamp;
  DiReal64 attenValue;			// [0]Off, [1]On
  DiUInt32 attenAuto;//0 man,1 aut0
  DiUInt32 ListenState;//  
  DiReal64 acqtimems;
  DiUInt32 acqtimeword;
  DiReal64 persistimems;
  DiUInt32 persistimeword;
  DiUInt32 flitertype;
  DiUInt32 ischangeRbwitself;//when change rbw by freq,its value is 0,when change rbw by itself,its value is 1	
  DiUInt32 uisPreampChangedItself;
  DiUInt32 AttenSelect;	//[0]0, [1]5, [2]10, [3]15, [4]20, [5]25, [6]30 (dB)
  DiUInt32 channelnum;
  DiInt32   dpxApmtMin;	//DPX bottom value Albert 19/04/12
  DiInt32   dpxApmtZoom;	//DPX ampt zoom Albert 19/04/12
  DiInt32   dpxHighestDensity;
  DiInt32   dpxLowestDensity;
  DiInt32   fmtData[801];	
  DiUInt32 triggerDelay;
  DiUInt32 triggerPeriod;
  DiReal32 triggervideoLevel;
  DiReal64 triggerRFBurstLevel;
  DiUInt32 triggerSlope;
  DiUInt32 triggerHoldOffTime;
  DiReal32 dpxCurve;
  DiInt32   FmtTriggerCriterion;
}_CONFIG_RSA_CTRL,*PCONFIG_RSA_CTRL; // GUI -> Ctrlapp

typedef struct
{	
	//20190122 this part should change after fpga over
	DiUInt32 _TotalNumber;//	Total Sweep Point Number
	DiReal64 _PwrLevel[10000];//	Measure Data Max 10000 points (_PwrLevel[10000])
	DiReal64 _Freq[10000];//	Frequency for each point (_Freq[10000])
	DiUInt32 SweepTime;//millisecond
  	DiUInt32 *DpxData;//Johnson 0726
}_SWEEP_DATA,*PSWEEP_DATA;


typedef struct 
{	
	DiUInt32 SweepUpdate;//	[0]Wait, [1]Update Ok, [2]ChangeParameter
	DiUInt32 BWUpdate;	//BW Changed from ControlApp (Only BW Auto Mode)
	DiUInt32 CtrlAppRunOk;//	ControlApp Alive Message (First RUN)
	DiUInt32 CtrlAppAlive;//	ControlApp Alive Signal, [0]->[1]->[0]-> бн. (б└1 second)
	DiUInt32 DeviceMsgUpdate;//	Device Message Update
	
	DiUInt32 SysparamReflesh;//1 reflesh over	
}_SM_SYNC,*PSM_SYNC;

typedef struct
{
	 DiUInt32 top_flag;  //Indicates a mode update. (sweep or measure)
	 DiUInt32 sweep_flag;//Indicate the update status of subitems. (sweep)	 
	 DiUInt32 measure_flag;//Indicate the update status of subitems. (measure)
	 DiUInt32 trigger_flag;
	 DiUInt32 stopFlag;	//Indicate fpga should stop 
}_CONFIG_UPDATE,*PCONFIG_UPDATE;

typedef struct
{
  DiUInt32 startedflag;//1 means not first start
			//inner use
}_START_FLAG,*PSTART_FLAG; 

typedef struct temper_calc
{
	DiUInt32 calctop;
	DiReal64 detatemp;
}TEMP_CALC,*PTEMP_CALC;

typedef struct all_notice
{
    DiUInt32 noticode;
}ALL_NOTIC_CODE,*PALL_NOTIC_CODE;

#if 0
//Steve 20190122 these reverse for rsa sweet 
#define SM_Key_Channelparam	5720
#define SM_Key_FftFirCommonnum	5721
#define SM_Key_SweepNum         5722
typedef struct
{
	DiUInt32 rbwkHz;         //rbw
	DiReal64 sampRateHz;	 //the fds
	DiReal64 stepFreqHz;	 //lo step
	DiUInt32 fftNum;		     //FFT num 
	DiReal64 winAlpha;		 //win coef
	DiReal64 respondTimeus;	 //respond time(switch channel and IF fliter time)
	DiReal64 validRatio;     //efficient  
	DiUInt32 singleacqTime;		 //the num of fs
       DiReal64 tsms;
       DiUInt32 orderNum;
} CHANNEL_PARAM,*PCHANNEL_PARAM;		 

typedef struct 
{
   	DiUInt32 segmentIndex;	 //segment index
	DiUInt32 segmentDataNum;  //segment data num  
	DiUInt32 seglostartfreqinter;//high 32bit
	DiUInt32 seglostartfreqfrac;//low 32bit
	DiReal64 persegfftsegNum;//per segment fft step nums     
	DiReal64 persegsweeptimes;//per segment sweep times
	DiUInt32 seglosteplow;//per segment lo step low 32 bits,fir/fft mode
	DiUInt32 seglostephigh;//per segment lo step high 16 bits,fir/fft mode
} FFT_FIR_COMMON_NUM,*PFFT_FIR_COMMON_NUM; 

typedef struct
{  
	DiUInt32 startIndex;		 //valid start index
	DiUInt32 stopIndex;		 //valid stop index
	DiUInt32 fftNum;
	DiReal64 fftBucketnum;//fft bucket num
	DiReal64 singlefftTime;   //single fft num acq time
	DiReal64 loStepHz;		 //lo step
	DiReal64 validRatio;     //efficient 
	DiUInt32 segmentNum;//decided by start and stop freq  
	DiUInt32 seglokeeptime;//seg last part lo keep time 
	DiReal64 sumSweeptime;//span sweep time	
    DiReal64 firdottimems;
	DiReal64 firBucketimeus;//means us
	DiUInt32 segmentsDataSumNum;//from start to end all points num
	FFT_FIR_COMMON_NUM comNum[19];
}SWEEP_NUM,*PSWEEP_NUM;
#endif
//===============================================================================
//as common struct only used inner
typedef struct
{
	DiInt32 mainthreadExit ;
	DiInt32 midmsgthreadExit;
	DiInt32 listenthreadExit;
	DiInt32 acqthreadExit;
}RSA_EXIT;

typedef struct FLATEMP
{
    double freq;
    double atten;
    int preswitch;
    int index;
    float ampbuf[801];
    struct FLATEMP* pndata; 
}CHANNELTEMPLATE,*PCHANNELTEMPLATE;
#ifdef __cplusplus
}
#endif

#endif  /* ndef __SaDataStruct_H__ */
