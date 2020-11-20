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

//==============================================================================
//0927
typedef struct
{
DiUInt32 startedflag;//1 means not first start
}_START_FLAG,*PSTART_FLAG; 

// Types	
typedef struct
{
	DiReal64 	CenterFreq;		//Set Center Frequency (Hz)
	DiReal64 SPANFreq;	//Set SPAN Frequency (Hz)
	DiReal64 StartFreq;//	Set Start Frequency (Hz)
	DiReal64 StopFreq;	//Set Stop Frequency (Hz)
	DiUInt32 SPANMode;	//0 no zero;1 zero span//[0]Normal, [1]Full SPAN, [2]Zero SPAN
	DiUInt32 TracePoint;	//[0]501, [1]1001, [2]2001, [3]3001 (point) (后面还会变更)
	DiUInt32 RBW;	//Set RBW (10 ~ 3000000 Hz)
	DiUInt32 RBWAuto;//	[0]Manual, [1]Auto
	DiUInt32 VBW;	//Set VBW (10 ~ 3000000 Hz)
	DiUInt32 VBWAuto;//	[0]Manual, [1]Auto
	DiUInt32 DetectorMode;	//[0]Max, [1]Min, [2]Sample, [3]Avg-Power, [4]Avg-Voltage
	DiReal64 RefLevel;	//Set Reference Level (dBm)
	DiUInt32 AttenSelect;	//[0]0, [1]5, [2]10, [3]15, [4]20, [5]25, [6]30 (dB)
	DiUInt32 SweepType;	//[0]Continuous, [1]Single, [2]Sweep Off
	DiUInt32 ExtTrigger;//	[0]Off, [1]On
	DiUInt32 TriggerMode;//	[0]Free Run, [1]Rise, [2]Fall, [3]Delay
	DiReal64 ZeroSPANTime;	//Set Zero SPAN Measure Time (millisecond)
	DiUInt32 ZeroSPANMode;	//[0]Amplitude, [1]Frequency, [2]Phase
	DiUInt32 Preamp;	//[0]Off, [1]On
	DiUInt32 ImageRejection;	//[0]Off, [1]On (后面还会变更)
	//added by bityang
	DiReal64 attenValue;
	DiUInt32 attenAuto;//0 man,1 aut0
	DiUInt32 sweepMode;       //sweep mode 00 FIR,11 FFT
	DiReal64 VBWTORBW;	//the default  = 1.0
	DiUInt32 VBWTORBWAuto;//	[0]Manual, [1]Auto
	DiUInt32 ListenState;//0323

	//by steve,0423
    	DiUInt32 ischangeRbwitself;//when change rbw by freq,its value is 0,when change rbw by itself,its value is 1
	//Johnson 0503
    	DiUInt32 uisPreampChangedItself;

    //Johnson 0718
    DiUInt32 AutoSweepTime;
    DiReal64 SweeepTime;

 //0829 steve
    DiUInt32 checkswitch;//0 check ,1 direct
//0904 steve
    DiInt32 checkinsert;//this used for software ctrl only,-1 check and not insert,0 check and insert,1 direct and insert
    DiReal64 firstper;//only when two channel will use secper
    DiReal64 secper;
//0905
    DiReal64 spanperstep;
}_CONFIG_SWEEP,*PCONFIG_SWEEP;  

typedef struct
{
	DiUInt32 MeasureMode;	//[0]Off, [1]Channel Power, [2]ACP, [3]Demoduleation, [4] Power Sensor
	DiReal64 ChannelBW;	//Set Channel Power Bandwidth (Hz)
	DiReal64 ChannelSpacing;//	Set Channel Power Spacing (Hz)
	DiReal64 DemodFreq;	//Set Demodulation Frequency (Hz)
	DiReal64 DemodIFBW;//	Set Demodulation Bandwidth (Hz)
	DiUInt32 DemodMode;		//[0]AM, [1]FM, [2]NFM
	DiReal64	PSFreq;		//Set Power Sensor Frequency (Hz)
}_CONFIG_MEASURE,*PCONFIG_MEASURE;  

typedef struct
{	
	DiUInt32 _TotalNumber;//	Total Sweep Point Number
	DiReal64 _PwrLevel[10000];//	Measure Data Max 10000 points (_PwrLevel[10000])
	DiReal64 _Freq[10000];//	Frequency for each point (_Freq[10000])
	DiUInt32 SweepTime;//millisecond
  	DiUInt32 DpxData[1000000];//Johnson 0726
}_SWEEP_DATA,*PSWEEP_DATA;

typedef struct 
{	
	DiReal64 ChannelPwr;//	Channel Power Level
	DiReal64 ACPR;//	ACPR
	DiReal64 ACPL;//	ACPL
	DiReal64 PSLevel;//	Power Sensor Measure Data (dBm)
}_MEASURE_DATA,*PMEASURE_DATA;


typedef struct 
{	
	DiUInt32 SweepUpdate;//	[0]Wait, [1]Update Ok, [2]ChangeParameter
	DiUInt32 BWUpdate;	//BW Changed from ControlApp (Only BW Auto Mode)
	DiUInt32 CtrlAppRunOk;//	ControlApp Alive Message (First RUN)
	DiUInt32 CtrlAppAlive;//	ControlApp Alive Signal, [0]->[1]->[0]-> …. (±1 second)
	DiUInt32 DeviceMsgUpdate;//	Device Message Update
	
	//added by bityang
	DiUInt32 AppExit;//the ctrlapp is over		
	DiUInt32 SysparamReflesh;//1 reflesh over
	DiUInt32 BufferSync;//when 0 means the gui has finished copy the shm to gui local,and ctrl will copy ctrl local to shm then set 1 
				//when 1 means the ctrl has finished copy the ctrl local to shm,and gui will copy the shm to gui local then set 0	
}_SM_SYNC,*PSM_SYNC;

typedef struct
{
	 DiUInt32 top_flag;  //Indicates a mode update. (sweep or measure or system)
	 DiUInt32 sweep_flag;//Indicate the update status of subitems. (sweep)
	 DiUInt32 measure_flag;//Indicate the update status of subitems. (measure)
	 DiUInt32 system_flag; //Indicate the update status of subitems. (system)
}_CONFIG_UPDATE,*PCONFIG_UPDATE;

#define SM_Key_ConfigSweep						5600
#define SM_Key_ConfigMeasure						5601
#define SM_Key_SweepData						5603
#define SM_Key_MeasureData						5604
#define SM_Key_Sync							5606
#define SM_Key_ConfigUpdate					    	5607
//added by bityang
#define SM_Key_Channelparam						5608
#define SM_Key_FftFirCommonnum	5609
#define SM_Key_SweepNum   5610

#define SYNC_KEY       5611
#define SYNC_KEY_GUI   5612
//0428
#define SYNC_SWEEP    5613
#define SM_CTRL7_KEY_START    5614


#define SYNC_KEY_CAL       5532 //!<in calc app also
#define SYNC_KEY_GUI_CAL   5533 //!<in calc app also
#define SYNC_KEY_CALC_CAL  5534 //!<in calc app also


typedef struct shmnotic
{
  int notic; //!<1 means to start calc
}SHM_NOTIC,*PSHM_NOTIC;


typedef struct calc_buf
{
  double calcb[801];
}CALC_DATA,*PCALC_DATA;
/*--------------------------mid_msg_deal------------------*/
#define IXT_ConfigSweep (0x00000001) //IXT_ConfigSweep
#define IXS_CenterFreq 0x00000001
#define IXS_SpanFreq   0x00000002
#define IXS_StartFreq  0x00000004
#define IXS_StopFreq	0x00000008
#define IXS_SpanMode   0x00000010
#define IXS_TracePoint  0x00000020
#define IXS_RBW		   0x00000040
#define IXS_RBWAuto	   0x00000080
#define IXS_VBW		   0x00000100
#define IXS_VBWAuto	   0x00000200
#define IXS_DetectorMode 0x00000400
#define IXS_RefLevel   0x00000800
#define IXS_AttenSelect 0x00001000
#define IXS_SweepType   0x00002000
#define IXS_ExtTrigger   0x00004000
#define IXS_TriggerMode  0x00008000
#define IXS_ZeroSpanTime  0x00010000
#define IXS_ZeroSpanMode   0x00020000
#define IXS_Preamp		  0x00040000
#define IXS_ImageRejection 0x00080000
#define IXS_SweepTimeAuto                       0x00100000//Johnson 0718
#define IXS_SweepTime                           0x00200000//Johnson 0718
//0829 steve
#define IXS_CheckAciton   0x00400000
#define IXS_Refoffset 0x00800000
/*----------------------------------------------------*/
#define IXT_ConfigMeasure (0x00000002)
#define IXS_MeasureMode  0x00000001
#define IXS_ChannelBW   0x00000002
#define IXS_ChannelSpacing  0x00000004
#define IXS_DemodFreq	 0x00000008
#define IXS_DemodIFBW	  0x00000010
#define IXS_DemodMode	   0x00000020
#define IXS_PSFreq		  0x00000040
/*-----------------------------------------------------*/
#define IXT_ConfigSystem (0x00000004)
#define IXS_IPAddress  0x00000001
#define IXS_NetMask	   0x00000002
#define IXS_GateWayAddress  0x00000004
#define IXS_Local_Remote	0x00000008
#define IXS_KeypadLight		0x00000010
#define IXS_LCDBrightness   0x00000020
#define IXS_SleepMode		0x00000040
#define IXS_Volume			0x00000080
#define IXS_KeyBeep			0x00000100
#define IXS_LimitBeep		0x00000200
#define IXS_FWupdateRequest 0x00000400
/*----------------------------------------------------*/

//added by bityang
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
//0719
       DiReal64 tsms;
       DiUInt32 orderNum;
} CHANNEL_PARAM,*PCHANNEL_PARAM;		 

typedef struct 
{
   	DiUInt32 segmentIndex;	 //segment index
	DiUInt32 segmentDataNum;  //segment data num  
	DiUInt32 seglostartfreqinter;/*high 32bit*/
	DiUInt32 seglostartfreqfrac;/*low 32bit*/ 
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
//0726			 //fft calc num
	DiReal64 fftBucketnum;//fft bucket num
	DiReal64 singlefftTime;   //single fft num acq time
	DiReal64 loStepHz;		 //lo step
	DiReal64 validRatio;     //efficient 
	DiUInt32 segmentNum;//decided by start and stop freq  
	//DiUInt32 lostepdivfreqlow;/*0~31bit*/
	//DiUInt32 lostepdivfreqhigh;/*32~47bit*/
	DiUInt32 seglokeeptime;//seg last part lo keep time 
	DiReal64 sumSweeptime;//span sweep time
	
	//steve 0719
        DiReal64 firdottimems;

	//Steve 0424
	DiReal64 firBucketimeus;//means us
	DiUInt32 segmentsDataSumNum;//from start to end all points num
	FFT_FIR_COMMON_NUM comNum[22];
}SWEEP_NUM,*PSWEEP_NUM;

typedef enum {SWEEP_CONTI = 0,SWEEP_SINGLE,SWEEP_IDLE} SWEEPCTRL;
typedef enum {ON = 0,OFF} SWITCHCTRL;

#define BSA_MANA_SHM_KEY 5500
//steve,0925
typedef struct
{
    DiUInt32 appexit;

}BSA_RUN_SYNC,*PBSA_RUN_SYNC;

//0925
typedef struct
{
DiInt32 mainthreadExit ;
DiInt32 midmsgthreadExit;
DiInt32 listenthreadExit;
DiInt32 acqthreadExit;
}BSA_EXIT;
//==============================================================================
// External variables

//==============================================================================
// Global functions


#ifdef __cplusplus
}
#endif

#endif  /* ndef __SaDataStruct_H__ */
