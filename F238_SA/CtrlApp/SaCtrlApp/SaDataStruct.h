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
#include "DiIoCtrl.h"

//==============================================================================
// Constants

//===========================Johnson 091009=====================================
#define USABLE 0

//==============================================================================
//0927
typedef struct
{
DiUInt32 startedflag;//1 means not first start
}_START_FLAG,*PSTART_FLAG; 

// Types	
typedef struct
{
	DiReal64 CenterFreq;		//Set Center Frequency (Hz)
#if USABLE
	DiReal64 SPANFreq;	//Set SPAN Frequency (Hz)
#endif
	DiReal64 StartFreq;//	Set Start Frequency (Hz)
	DiReal64 StopFreq;	//Set Stop Frequency (Hz)
	DiUInt32 SPANMode;	//0 no zero;1 zero span//[0]Normal, [1]Full SPAN, [2]Zero SPAN
	DiUInt32 TracePoint;	//[0]501, [1]1001, [2]2001, [3]3001 (point) (后面还会变更)
	DiUInt32 RBW;	//Set RBW (10 ~ 3000000 Hz)
#if USABLE
	DiUInt32 RBWAuto;//	[0]Manual, [1]Auto
#endif
	DiUInt32 VBW;	//Set VBW (10 ~ 3000000 Hz)
#if USABLE
	DiUInt32 VBWAuto;//	[0]Manual, [1]Auto
#endif
	DiUInt32 DetectorMode;	//[0]Max, [1]Min, [2]Sample, [3]Avg-Power, [4]Avg-Voltage
	DiReal64 RefLevel;	//Set Reference Level (dBm)
#if USABLE
	DiUInt32 AttenSelect;	//[0]0, [1]5, [2]10, [3]15, [4]20, [5]25, [6]30 (dB)
#endif
	DiUInt32 SweepType;	//[0]Continuous, [1]Single, [2]Sweep Off
#if USABLE
	DiReal64 ZeroSPANTime;	//Set Zero SPAN Measure Time (millisecond)
	DiUInt32 ZeroSPANMode;	//[0]Amplitude, [1]Frequency, [2]Phase
#endif
	DiUInt32 Preamp;	//[0]Off, [1]On
#if USABLE
	DiUInt32 ImageRejection;	//[0]Off, [1]On (后面还会变更)
#endif
	//added by bityang
	DiReal64 attenValue;
	DiUInt32 attenAuto;//0 man,1 aut0
	DiUInt32 sweepMode;       //sweep mode 00 FIR,11 FFT
#if USABLE
	DiReal64 VBWTORBW;	//the default  = 1.0
	DiUInt32 VBWTORBWAuto;//	[0]Manual, [1]Auto
#endif
	DiUInt32 ListenState;//0323

	//by steve,0423
    	DiUInt32 ischangeRbwitself;//when change rbw by freq,its value is 0,when change rbw by itself,its value is 1
#if USABLE
	//Johnson 0503
    	DiUInt32 uisPreampChangedItself;
	//Johnson 0718
	DiUInt32 AutoSweepTime;
	DiReal64 SweeepTime;
#endif
	//0829 steve
	DiUInt32 checkswitch;//0 check ,1 direct
	//0904 steve
	DiInt32 checkinsert;//this used for software ctrl only,-1 check and not insert,0 check and insert,1 direct and insert
	DiReal64 firstper;//only when two channel will use secper
	DiReal64 secper;
	//0905
	DiReal64 spanperstep;
	//Johnson 190410
	DiInt32 dZeroRestrainAtten;
	DiReal64 dZeroRestrainPhase;
	//Johnson 190412
	DiUInt32 uSweepCompleteFlag;//1 means that current sweep complete,0 means that current sweep is running
	DiUInt32 uAllSweepCompleteFlag;//GUI->CtrlApp    1 means that all sweep complete or average is not open,0 means that sweep is running
	//Johnson 190425
	DiUInt32 uIFMode; //0 means SA_OFF    1 means Narrow 10MHz  2 means Wide 100MHz
#if USABLE
	DiUInt32 uMsCompleteFlag; //used to when mode is spurious or spectrum,1 means that measure complete,0 means that measure is running	
#endif 

	DiUInt32 TriggerMode;
	DiUInt32 TriggerDirect;
	DiReal64 TriggerDelayTime;
	DiReal64 TriggerPerTime;
	DiInt32 VedioTriggerAmp;
	DiInt32 RFBurstTriggerAmp;

	DiUInt32 markerFreqCount;
	DiUInt32 bSendFreqCountStopCmd;

	DiUInt32 uMinMaxHoldComplete;

	DiReal64 signalFreq;

	DiInt32 DrCtrlSource;
	DiInt32 LvlEdgSelect;
	DiInt32 LvlEdgMode;
	DiInt32 DrCtrlSweepMode;
	DiInt32 PrdTrgSynchroSrc;
	DiInt32 DrCtrlSwitch;
	DiReal64 EdgTrigDely;
	DiReal64 EdgTrigDoorWdth;
	DiInt32 EdgTrigPrvntStatus;
	DiReal64 EdgTrigPrvntTimes;
	DiReal64 RFBurstTrigLevel;
	DiReal64 PrdTrgPeriod;
	DiReal64 PrdTrgSrcDelay;
	DiInt32 PrdTrigPrvntStatus;
	DiReal64 PrdTrigPrvntTimes;
	DiInt32  GateView;
	DiInt32  FirstStart;
}_CONFIG_SWEEP,*PCONFIG_SWEEP;  

typedef struct
{
	DiUInt32 MeasureMode;	//[0]Off, [1]Channel Power, [2]ACP, [3]Demoduleation, [4] Power Sensor
#if USABLE
	DiReal64 ChannelBW;	//Set Channel Power Bandwidth (Hz)
	DiReal64 ChannelSpacing;//	Set Channel Power Spacing (Hz)
	DiReal64 DemodFreq;	//Set Demodulation Frequency (Hz)
	DiReal64 DemodIFBW;//	Set Demodulation Bandwidth (Hz)
	DiUInt32 DemodMode;		//[0]AM, [1]FM, [2]NFM
	DiReal64 PSFreq;		//Set Power Sensor Frequency (Hz)
#endif
}_CONFIG_MEASURE,*PCONFIG_MEASURE;  

typedef struct
{	
#if USABLE
	DiUInt32 _TotalNumber;//	Total Sweep Point Number
#endif
	DiReal64 _PwrLevel[1000];//	Measure Data Max 10000 points (_PwrLevel[10000])
#if USABLE
	DiUInt32 SweepTime;//millisecond
#endif
	DiInt32  fsr;
	DiReal64 CalData;
}_SWEEP_DATA,*PSWEEP_DATA;

#if USABLE
typedef struct 
{	
	DiReal64 ChannelPwr;//	Channel Power Level
	DiReal64 ACPR;//	ACPR
	DiReal64 ACPL;//	ACPL
	DiReal64 PSLevel;//	Power Sensor Measure Data (dBm)
}_MEASURE_DATA,*PMEASURE_DATA;
#endif


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
#if USABLE
	 DiUInt32 system_flag; //Indicate the update status of subitems. (system)
#endif
	 DiUInt32 trigger_flag;
	 DiUInt32 doorControl_flag;
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
#define IXS_ZeroSpanTime  0x00010000
#define IXS_ZeroSpanMode   0x00020000
#define IXS_Preamp		  0x00040000
#define IXS_ImageRejection 0x00080000
#define IXS_SweepTimeAuto                       0x00100000//Johnson 0718
#define IXS_SweepTime                           0x00200000//Johnson 0718
//0829 steve
#define IXS_CheckAciton   0x00400000
#define IXS_Refoffset 0x00800000

//Johnson 190412
#define IXS_PARALOAD                            0x04000000
//Johnson 190422
#define IXS_SA_ZeroRestrain                     0x08000000
//Johnson 0425
#define IXS_SA_IFmode                           0x10000000
//Johnson 0710
#define IXS_MARKERFRECOUNT                      0x20000000
//Johnson 0729
#define IXS_DOTSWEEPTIME                        0x40000000

#define IXS_GATEVIEW                       	0x80000000

#define IXS_TriggerMode			   0x80000001
#define IXS_TriggerDirect                  0x80000002
#define IXS_TriggerDelayTime               0x80000004
#define IXS_TriggerPerTime                 0x80000008
#define IXS_VedioTriggerAmp                0x80000010
#define IXS_RFBurstTriggerAmp              0x80000020

#define IXS_DrCtrlSource 	           0x80000040
#define IXS_LvlEdgModeSelect               0x80000080
#define IXS_LvlEdgValueSelect              0x80000100
#define IXS_DrCtrlSweepMode                0x80000200
#define IXS_PrdTrigSycSrcSelect            0x80000400
#define IXS_DrCtrlSweepSwitch              0x80000800

#define IXS_EdgTrigDelay                   0x80001000
#define IXS_EdgTrigDrWidth                 0x80002000
#define IXS_EdgTrigPrvtSwitch	           0x80004000
#define IXS_EdgTrigPrvtValue               0x80008000
#define IXS_RFBurst_TrigLevel              0x80010000

#define IXS_PrdTrigPeriod                  0x80020000
#define IXS_PrdTrigSycSrcDelay             0x80040000
#define IXS_PrdTrigPrvtSwitch	           0x80080000
#define IXS_PrdTrigPrvtValue               0x80100000
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
/*#define IXT_ConfigSystem (0x00000004)
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
#define IXS_FWupdateRequest 0x00000400*/
/*----------------------------------------------------*/		
/*-----------------------------------------------------*/
#define IXT_ConfigTrigger 		   0x00000004
/*#define IXS_TriggerMode			   0x00000001
#define IXS_TriggerDirect                  0x00000002
#define IXS_TriggerDelayTime               0x00000004
#define IXS_TriggerPerTime                 0x00000008
#define IXS_VedioTriggerAmp                0x00000010
#define IXS_RFBurstTriggerAmp              0x00000020*/
/*-----------------------------------------------------*/

/*-----------------------------------------------------*/
#define IXT_ConfigDrCtrlSweep              0x00000008
/*#define IXS_DrCtrlSource 	           0x00000001
#define IXS_LvlEdgModeSelect               0x00000002
#define IXS_LvlEdgValueSelect              0x00000004
#define IXS_DrCtrlSweepMode                0x00000008
#define IXS_PrdTrigSycSrcSelect            0x00000010
#define IXS_DrCtrlSweepSwitch              0x00000020

#define IXS_EdgTrigDelay                   0x00000040
#define IXS_EdgTrigDrWidth                 0x00000080
#define IXS_EdgTrigPrvtSwitch	           0x00000100
#define IXS_EdgTrigPrvtValue               0x00000200
#define IXS_RFBurst_TrigLevel              0x00000400

#define IXS_PrdTrigPeriod                  0x00000800
#define IXS_PrdTrigSycSrcDelay             0x00001000
#define IXS_PrdTrigPrvtSwitch	           0x00002000
#define IXS_PrdTrigPrvtValue               0x00004000*/
//#define IXS_GATEVIEW                       0x00008000
/*-----------------------------------------------------*/

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
	DiUInt64 segmentsDataSumNum;//from start to end all points num
#ifdef BIT_F238
	FFT_FIR_COMMON_NUM comNum[19];
#endif
#ifdef BIT_F239
        FFT_FIR_COMMON_NUM comNum[14];//Johnson 190919
#endif
#ifdef BIT_F238_SMART
        FFT_FIR_COMMON_NUM comNum[7];//Johnson 190919
#endif
}SWEEP_NUM,*PSWEEP_NUM;

typedef struct
{  
	DiUInt32 RBW;	//Set RBW (10 ~ 3000000 Hz)
	DiUInt32 VBW;

	DiUInt32 startIndex;		 //valid start index
	DiUInt32 stopIndex;		 //valid stop index
	DiReal64 fftBucketnum;//fft bucket num
	DiReal64 singlefftTime;   //single fft num acq time
	DiReal64 firBucketimeus;//means us	
	
}FREQ_COUNT_LOCAL,*PFREQ_COUNT_LOCAL;

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

#define IXT_Tempercalc (0x00010000)
#define SM_Key_TemperCalc                                               5509
typedef struct temper_calc
{
	DiUInt32 calctop;
	DiReal64 detatemp;
}TEMP_CALC,*PTEMP_CALC;


#define SM_KEY_NOTICE 5551
//Johnson 191107
typedef struct
{
	DiUInt32 noticode;
}ALL_NOTIC_CODE,*PALL_NOTIC_CODE;
//==============================================================================
// External variables

//==============================================================================
// Global functions


#ifdef __cplusplus
}
#endif

#endif  /* ndef __SaDataStruct_H__ */
