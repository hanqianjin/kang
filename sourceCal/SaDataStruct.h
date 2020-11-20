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


//==============================================================================
// Constants

//==============================================================================
// Types	
typedef struct
{
	double 	CenterFreq;		//Set Center Frequency (Hz)
	double SPANFreq;	//Set SPAN Frequency (Hz)
	double StartFreq;//	Set Start Frequency (Hz)
	double StopFreq;	//Set Stop Frequency (Hz)
	unsigned int SPANMode;	//[0]Normal, [1]Full SPAN, [2]Zero SPAN
	unsigned int TracePoint;	//[0]501, [1]1001, [2]2001, [3]3001 (point) (后面还会变更)
	unsigned int RBW;	//Set RBW (10 ~ 3000000 Hz)
	unsigned int RBWAuto;//	[0]Manual, [1]Auto
	unsigned int VBW;	//Set VBW (10 ~ 3000000 Hz)
	unsigned int VBWAuto;//	[0]Manual, [1]Auto
	unsigned int DetectorMode;	//[0]Max, [1]Min, [2]Sample, [3]Avg-Power, [4]Avg-Voltage
	double RefLevel;	//Set Reference Level (dBm)
	unsigned int AttenSelect;	//[0]0, [1]5, [2]10, [3]15, [4]20, [5]25, [6]30 (dB)
	unsigned int SweepType;	//[0]Continuous, [1]Single, [2]Sweep Off
	unsigned int ExtTrigger;//	[0]Off, [1]On
	unsigned int TriggerMode;//	[0]Free Run, [1]Rise, [2]Fall, [3]Delay
	double ZeroSPANTime;	//Set Zero SPAN Measure Time (millisecond)
	unsigned int ZeroSPANMode;	//[0]Amplitude, [1]Frequency, [2]Phase
	unsigned int Preamp;	//[0]Off, [1]On
	unsigned int ImageRejection;	//[0]Off, [1]On (后面还会变更)
	//added by bityang
	unsigned int sweepMode;       //sweep mode 00 FIR,11 FFT
	double VBWTORBW;	//the default  = 1.0
	unsigned int VBWTORBWAuto;//	[0]Manual, [1]Auto
}_CONFIG_SWEEP;  

typedef struct
{
	unsigned int MeasureMode;	//[0]Off, [1]Channel Power, [2]ACP, [3]Demoduleation, [4] Power Sensor
	double ChannelBW;	//Set Channel Power Bandwidth (Hz)
	double ChannelSpacing;//	Set Channel Power Spacing (Hz)
	double DemodFreq;	//Set Demodulation Frequency (Hz)
	double DemodIFBW;//	Set Demodulation Bandwidth (Hz)
	unsigned int DemodMode;		//[0]AM, [1]FM, [2]NFM
	double	PSFreq;		//Set Power Sensor Frequency (Hz)
}_CONFIG_MEASURE;  

typedef struct
{
	char IPAddress[16];		//255.255.255.255 (String; IPAddress[16])
	char NetMask[16];		//255.255.255.255 (String; NetMask[16])
	char GatewayAddress[16];		//255.255.255.255 (String; GatewayAddress[16])
	unsigned int LocalRemote;		//[0]Local, [1]Remote
	unsigned int 	KeypadLight;		//[0]Off, [1]On
	unsigned int 	LCDBrightness;		//[0 ~ 100] %
	unsigned int 	SleepMode;	//[0]Off, [1 ~ 60] Minute
	unsigned int 	Volume;		//[0 ~ 5]
	unsigned int 	KeyBeep;		//[0]Off, [1]On
	unsigned int 	LimitBeep;		//[0]Off, [1]On
	unsigned int 	FWUpdateRequest;	//[0]Off, [1]Request
}_CONFIG_SYSTEM;

typedef struct
{	
	unsigned int _TotalNumber;//	Total Sweep Point Number
	double _PwrLevel[10000];//	Measure Data Max 10000 points (_PwrLevel[10000])
	double _Freq[10000];//	Frequency for each point (_Freq[10000])
	unsigned int SweepTime;//millisecond
}_SWEEP_DATA;

typedef struct 
{	
	double ChannelPwr;//	Channel Power Level
	double ACPR;//	ACPR
	double ACPL;//	ACPL
	double PSLevel;//	Power Sensor Measure Data (dBm)
}_MEASURE_DATA;

typedef struct
{
	unsigned int InvenAppMajor;	//	ControlApp Major Version
	unsigned int InvenAppMiinor;//	ControlApp Minor Version
	unsigned int InvenDSPRevision;	//	DSP Revision Number
	unsigned int InvenDSPDate;	//DSP Compile Date (0828 => 8/28)
	char InvenSerialNo[16];		//System Serial Number
	float BoardTemp;		//Carrier Baord Temperature
	float BatteryTemp;		//Battery Temperature
	unsigned int BatteryRemaind;	//[0 ~ 100] %
	unsigned int BatterChargeStatus;	//[0]Charging, [1]Discharging
	unsigned int ACStatus;		//[0]AC Power, [1]Battery Power
	unsigned int LanPortStatus;	//[0]Link Down, [1]Link Up
	unsigned int USBMemoryStatus;		//[0]None, [1]Insert
	char DeviceMsg[50];		//Device Info / Error Message
	unsigned int BoardTempAlarm;	//[0]Normal, [1]85 °C Over
	unsigned int BatteryTempAlarm;		//[0]Normal, [1]80 °C Over
	char PSModel[16];		//Power Sensor Model Name
	unsigned int PSType;	//Power Sensor Type
	unsigned int PSMethod;		//Power Sensor Method
	char PSSerialNo[16];		//Power Sensor Serial Number
	unsigned int PSInvenMajor;		//Power Sensor Major Version
	unsigned int PSInvenMinor;		//Power Sensor Minor Version
	float PSTemp;		//Power Sensor Temperature
	unsigned int PSStatus;	//[0]Wait, [1]Conneted, [2]Disconnected
	char GPSLatitude[100];		//GPS Info – Latitude (N 3722.04194)
	char GPSLongitude[100];		//GPS Info – Longitude (E 12638.92059)
	char GPSDate[8];		//GPS Info – Date (190117)
	char GPSTime[11];		//GPS Info – Time (130934.00)
} _SYSTEM_INFO;

typedef struct 
{	
	unsigned int SweepUpdate;//	[0]Wait, [1]Update Ok, [2]ChangeParameter
	unsigned int BWUpdate;	//BW Changed from ControlApp (Only BW Auto Mode)
	unsigned int CtrlAppRunOk;//	ControlApp Alive Message (First RUN)
	unsigned int CtrlAppAlive;//	ControlApp Alive Signal, [0]->[1]->[0]-> …. (±1 second)
	unsigned int DeviceMsgUpdate;//	Device Message Update
}_SM_SYNC;   

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
} CHANNEL_PARAM;		 

typedef struct 
{
   	DiUInt32 segmentIndex;	 //segment index
	DiUInt32 segmentDataNum;  //segment data num  
	DiUInt32 seglostartfreqinter;/*high 32bit*/
	DiUInt32 seglostartfreqfrac;/*low 32bit*/ 
	DiReal64 persegfftsegNum;//per segment fft step nums     
	DiUInt64 persegsweeptimes;//per segment sweep times
	DiUInt32 seglosteplow;//per segment lo step low 32 bits,fir/fft mode
	DiUInt32 seglostephigh;//per segment lo step high 16 bits,fir/fft mode
} FFT_FIR_COMMON_NUM; 

typedef struct
{  
	DiUInt32 startIndex;		 //valid start index
	DiUInt32 stopIndex;		 //valid stop index
	DiUInt32 fftNum;			 //fft calc num
	DiUInt32 fftBucketnum;//fft bucket num
	DiReal64 singlefftTime;   //single fft num acq time
	DiReal64 loStepHz;		 //lo step
	DiReal64 validRatio;     //efficient 
	DiUInt32 segmentNum;//decided by start and stop freq 
	DiUInt32 seglokeeptime;//seg last part lo keep time 
	DiReal64 sumSweeptime;//span sweep time
	FFT_FIR_COMMON_NUM comNum[13];
}SWEEP_NUM;
//==============================================================================
// External variables

//==============================================================================
// Global functions


#ifdef __cplusplus
}
#endif

#endif  /* ndef __SaDataStruct_H__ */
