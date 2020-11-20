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
#include "msgNoticeCode.h"
//==============================================================================
// Constants

//==============================================================================
//0927
typedef struct
{
DiUInt32 startedflag;//37 means not first start
}_START_FLAG,*PSTART_FLAG; 

typedef struct
{
 DiInt8 IPAddress[16];
  DiInt8 NetMask[16];
  DiInt8 GateWayAddress[16];
  DiUInt32 Local_Remote;				// [0]Local, [1]Remote
  DiUInt32 LcdpadLight;				// [0]Off, [1]On
  DiUInt32 LCDBrightness;		        // [0 ~ 100] %
  DiUInt32 SleepMode;			        // [0]Off, [1 ~ 60] Minute
  DiUInt32 Volume;				// [0 ~ 5]
  DiUInt32 KeyBeep;				// [0]Off, [1]On
  DiUInt32 LimitBeep;				// [0]Off, [1]On
  DiUInt32 FWupdateRequest;			// [0]Off, [1]Request
  DiUInt32 TouchScreen;
  DiUInt32 AnaMode;                              //in RUNMODE order to tell sys app whitch bitstream to burn
  DiUInt32 PicSwitch;
  DiUInt32 mainfpgaver;         //ControlApp Major Version
  DiUInt32 spafpgaver;        //ControlApp Minor Version
  DiUInt32 cpldver;      //DSP Revision Number
  DiUInt32 adcover;
  DiUInt32 selftest;
  DiChar InvenSerialNo[16];      //System Serial Number
  DiChar PSModel[16];            //Power Sensor Model Name
  DiUInt32 PSType;                //Power Sensor Type
  DiUInt32 PSFreqCalc;              //Power Sensor Method
  DiChar PSSerialNo[16];         //Power Sensor Serial Number
  DiUInt32 PSInvenMajor;          //Power Sensor Major Version
  DiUInt32 PSInvenMinor;          //Power Sensor Minor Version
  DiReal64 PSTemp;                  //Power Sensor Temperature
  DiUInt32 Gpswitch;              //[0]disable, [1]enable
  DiChar WavFileName[100];       //WavFileName 
DiInt32 wifiswitch;  //when 0 means burn over
  DiInt32 bluetwitch;  //PON open
  DiUInt32 refset;
DiInt32 Convertflag;
DiInt32 secifatten;
}_CONFIG_SYSTEM,*PCONFIG_SYSTEM;

typedef struct
{
	 DiReal64 BoardTemp;               //Carrier Baord Temperature
  DiReal64 RfTemp;               //Carrier Baord Temperature
  DiUInt32  BatteryOnLine;        //[0] no battery, [1] have battery
  DiReal32 BatteryTemp;             //Battery Temperature
  DiUInt32 BatteryRemaind;        //[0 ~ 100] %
  DiUInt32 BatterChargeStatus;    //[0]Unknown,[1]Charging, [2]Discharging, [3]Full
  DiUInt32 ACStatus;              //[0]AC Power, [1]Battery Power
  DiReal32 batvoltage;
  DiReal32 batcurrent;
  DiUInt32 LanPortStatus;         //[0]Link Down, [1]Link Up
  DiUInt32 USBMemoryStatus;       //[0]None, [1]Insert
  DiChar DeviceMsg[50];          //Device Info / Error Message
  DiUInt32 BoardTempAlarm;        //[0]Normal,
  DiUInt32 BatteryTempAlarm;      //[0]Normal,

  DiChar GPSLatitude[100];       //GPS Info - Latitude (N 3722.04194)
  DiChar GPSLongitude[100];      //GPS Info - Longitude (E 12638.92059)
  DiChar GPSDate[11];            //GPS Info - Date (190117)
  DiChar GPSTime[12];            //GPS Info - Time (130934.00)
  DiReal64 GPSElevation;            //GPS elevation
  DiUInt32 GPSStatus;             //GPS status [0] Invalid [1] fixed [2] Differential [3] Sensitive
  DiUInt32 GPSSatelliteNum;       //GPS Satellite in use 
  DiUInt32 GPSInView;
  DiReal64 GpsSpeedKmh;
  DiReal64 GpsDirection;
  DiUInt32 GpsOperMode;
  DiUInt32 GpsPrnNumber;	

  DiReal64 FpgaTemp;
  DiUInt32 datetype;
  DiInt32 dismode;
} _SYSTEM_INFO,*PSYSTEM_INFO;

typedef struct
{
  DiUInt32 top_flag_conf;  //once mode
  DiUInt32 top_flag_sys;//polling mode
  DiUInt32 system_flag_conf;
  DiUInt32 sys_flag_info;	
}_CONFIG_UPDATE,*PCONFIG_UPDATE;

typedef struct all_notice
{
  DiUInt32 noticode;//!< none zero means notice happened
}ALL_NOTIC_CODE,*PALL_NOTIC_CODE;

#define SM_Key_ConfigSystem						5602
#define SM_Key_SystemInfo						5605
#define SM_Key_ConfigUpdate					    	5688
#define SM_Key_TemperCalc                                               5509
#define SM_Key_ExcepNotic 5551 //!<in all mod for notice

#define PLT_EXCE_SOURCE 16

/*-----------------------------------------------------*/
#define IXT_ConfigSystem (0x00000004)
#define IXS_IPAddress             0x00000001
#define IXS_NetMask               0x00000002
#define IXS_GateWayAddress        0x00000004
#define IXS_Local_Remote	  0x00000008
#define IXS_LcdpadLight		  0x00000010
#define IXS_LCDBrightness         0x00000020
#define IXS_SleepMode		  0x00000040
#define IXS_Volume		  0x00000080
#define IXS_KeyBeep		  0x00000100
#define IXS_LimitBeep		  0x00000200
#define IXS_FWupdateRequest       0x00000400
#define IXS_TouchScreen           0x00000800
#define IXS_BurnAction            0x00001000
#define IXS_SwitchPic     0x00002000
#define IXS_InvenAppMajor         0x00004000
#define IXS_InvenAppMiinor        0x00008000
#define IXS_ADCOver      0x00010000
#define IXS_SELFTest 	  0x00020000
#define IXS_InvenSerialNo 	  0x00040000
//this part about sys info use one command is OK
#define IXS_PSModel  		  0x00080000
#define IXS_FreqCalc		  0x00100000
#define IXS_SecIfAtten 		  0x00200000
//#define IXS_PSSerialNo 		  0x00400000
//#define IXS_PSInvenMajor 	  0x00800000
//#define IXS_PSInvenMinor 	  0x01000000
//#define IXS_PSTemp 		  0x00100000
#define IXS_GPSSwitch 		  0x00200000
#define IXS_WIFI    0x00400000
#define IXS_BLUETOOTH  0x00800000
#define IXS_Ref			  0x01000000
#define IXS_Calc			  0x02000000
#define IXS_PLAYMUSICON		0x04000000
#define IXS_PLAYMUSICOFF		0x08000000


//Albert 1024
#define IXT_System_Info (0x00000008)
#define IXT_System_Info          (0x00000008)
#define IXS_BoardTemp 		  0x00000020
#define IXS_BatteryInfoAll        0x00000040
#define IXS_BatteryRemaind 	  0x00000080
#define IXS_BatterChargeStatus 	  0x00000100
#define IXS_ACStatus		  0x00000200
#define IXS_LanPortStatus 	  0x00000400
#define IXS_USBMemoryStatus 	  0x00000800
#define IXS_DeviceMsg  		  0x00001000
#define IXS_BoardTempAlarm 	  0x00002000
#define IXS_BatteryTempAlarm 	  0x00004000
#define IXS_GPSInfoAll		  0x00800000
#define IXS_GPSLongitude	  0x01000000
#define IXS_GPSDate		  0x02000000
#define IXS_GPSTime		  0x04000000
#define IXS_BatteryOnline	  0x08000000

#define IXT_Tempercalc (0x00010000)


#define IXT_MUSIC_PLAY (0x00000010)
#define IXS_PLAYMUSICON1		0x00000001
#define IXS_PLAYMUSICOFF1		0x00000002

#define IXS_PLAYMUSICVOL		0x40000000
/*----------------------------------------------------*/

typedef struct
{
DiInt32 mainthreadExit ;
DiInt32 midmsgthreadExit;
DiInt32 listenthreadExit;
DiInt32 acqthreadExit;
}RSA_EXIT;

typedef struct temper_calc
{
DiUInt32 calctop;
DiReal64 detatemp;
}TEMP_CALC,*PTEMP_CALC;
//==============================================================================
// External variables

//==============================================================================
// Global functions
typedef struct DevMsg
{
	DiInt32 osiword;
  DiInt32 secifatten;
  char swver[64];
  char hwver[64];
  char update[64];

}DEVMSG,*PDEVMSG;

#ifdef __cplusplus
}
#endif

#endif  /* ndef __SaDataStruct_H__ */
