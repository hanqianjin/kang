//==============================================================================
//
// Title:		BitSehInfo
// Purpose:		A short description of the library.
//
// Created on:	2017/10/10 at 10:35:45 by yangxiaotao.
// Copyright:	cetc41. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <stdio.h>
#include "BitSehInfo.h"

//==============================================================================
// Constants	
//==============================================================================
// Types
#pragma pack(push,1)  
typedef struct 
{
  unsigned int  nCode;        	//error info num
  char strInfo[64];  //error info msg
} BITDICTION;
#pragma pack(pop)

//0809 do not change data structure by steve
//==============================================================================
// Static global variables
static const BITDICTION errInfoList[] =
{
  {ERR_NoErr,    "state ok"},
  {ERR_InvalidParam1, "param1 error"},
  {ERR_InvalidParam2, "param2 error"},
  {ERR_InvalidParam3, "param3 error"},
  {ERR_InvalidParam4, "param4 error"},
  {ERR_InvalidParam5, "param5 error"},
  {ERR_InvalidParam6, "param6 error"},
  {ERR_InvalidParam7, "param7 error"},
  {ERR_NoHandle, 		"no ctrl handle"},
  {ERR_Init, 			"init failed"},
  {ERR_InitOpened,    "init open failed"},
  {ERR_InitRescName,  "res name error"},
  {ERR_InitCanntOpen, "ini cannt open"},
  {ERR_GetSerialID,   "get serial ID failed"},
  {ERR_SetSerialID,   "set serial ID failed"},
  {ERR_Get_Pos_Info,  "get pos info failed"},
  {ERR_Get_Dev_Info,  "get dev info failed"},
  {ERR_Get_RDev_Info, "get rdev info failed"},
  {ERR_Reset, 		"reset error"},
  {ERR_SelfTest, 		"self test error"},
  {ERR_GetTemperature,"get temperature failed"},
  {ERR_AllocCalData, 	"allco cal data failed"},
  {ERR_ReadCalData, 	"read cal data failed"},
  {ERR_WriteCalData,  "write cal data failed"},
  {ERR_ReadCALFile,   "read cal file failed"},
  {ERR_ReWriteCALFile,"rewrite cal file failed"},
  {ERR_CheckCalData,  "check cal data failed"},
};

static const BITDICTION errInfoListEx[] =
{
  {ERR_RF_Path,		"setting Rf path failed"},
  {ERR_LO_Path,  	    "setting Lo path failed" },
  {ERR_PreSelector,	"setting preselector failed" },
  {ERR_Atten, 		"man mode setting atten failed"},
  {ERR_YTFFreq,		"YTF freq failed" },
  {ERR_Config	,		"config dev param failed"},
  {ERR_Setup,		    "auto config dev param failed"},
  {ERR_GetCorrections,"Failed to get the interpolation value" },
  {ERR_YTFDegauss,	"Failed to acquire degaussing time"},
  {ERR_REFloss,       "10M Inner or external ref setting failed"},
  {ERR_Trigloss,      "Trigger setting failed"},
  //SA_f235
  {SA_FREQ_BANDSwitch,			"Failed to switch frequency band"},
  {SA_ZEROFRE_SUPAMPAtten,		"zero freq restrain failed"},
  {SA_SECMEDFRE_Atten,			"sec IF atten failed"},
  {SA_ZEROFRE_SUPPhase,			"zero freq restrain phase failed"},
  {SA_LOW_PREAtten,				"low freq band pre atten failed"},
  {SA_LOW_FRONTGate,				"low freq pre ampli channel failed"},
  {SA_HIGH_PREAtten,				"9k-7.5GHz pre atten failed "},
  {SA_HIGH_FRONTGate,				"9k-7.5GHz pre amp open failed"},
  {SA_LO_Control,					"lo freq set failed "},
  {SA_SYSRES_Signal,				"sys reset signal failed"},
  {SA_MEDFRE_Gain,				"IF gain ctrl failed"},
  {SA_INEXT_Reference,			"inext ref failed"},
  {SA_CRYVOLT_Control,			"failed to set cryvolt failed"},
  {SA_ULTRAHIGH_PREAtten,			"23.63375-32GHz pre atten failed"},
  {SA_PRESelect,					"pre amp select failed"},
  {SA_RBW,						"rbw failed"},
  {SA_VBW,						"vbw failed"},
  {SA_DETECTORMode,				"failed to set detector mode"},
  {SA_DATAPROMode,				"failed to set data process mode"},
  {SA_SWPStart,					"start sweep failed"},
  {SA_ZEROSPANFlag,				"zero span flag failed "},
  {SA_DOTSWPTime,					"dot sweep time failed "},
  {SA_TOTALSWPTime,				"total swp time failed"},
  {SA_DISPLAYNum,					"trace num failed"},
  {SA_DETECTORFlag,				"detector or not flag failed "},
  {SA_DATAADDRClr,				"data clear failed "},
  {SA_FFTBUCKETNum,				"fft bucket num failed "},
  {SA_AUDIOTime,					"audio time failed"},
  {SA_AUDIOVolume,				"audio volume failed"},
  {SA_AUDIOType,					"audio type failed "},
  {SA_AUDIOEn,					"audio enable failed "},
  {SA_FFTCALNum,					"fft calc num failed"},
  {SA_FFTDirection,				"fft direction failed  "},
  {SA_FFTVALIDSTANum,				"fft valid start index failed  "},
  {SA_FFTVALIDENDNum,				"fft valid stop index failed "},
  {SA_FFTDOTSWPTime,				"fft dot swp time failed  "},
  {SA_BUCKETTRIGTime,				"suo xiang check time failed"},
  {SA_RBWVBWFIL_DELAYTime,		"RBW VBW filte delay time failed   "},
  {SA_TRIGType,					"trig type failed "},
  {SA_TRIGDirect,					"trig polar direct failed  "},
  {SA_TRIGTIME,					"trig delay time failed  "},
  {SA_VEDIOTRIGAmp,					"vedio trig level failed  "},
  {SA_TRIGPERTIME,                               "trig per time failed "},
  {SA_RFBURSTTRIGAmp,                             "rf burst trig level failed  "},
  {SA_LASTBand,    "setting last band failed"},
  {SA_LOStep,     "setting lo step freq failed"},
  {SA_LOLastBandKeeptime,   "failed to set last band keep time"},
  {SA_SEGPoint,     "failed to set seg points"},
  {SA_SWPStop,			"failed to set sweep stop"},
  {SA_CHECKSegNum,			"failed to set seg check num"},
  {SA_FIRBUcketTime,			"failed to set fir bucket time"},
	{SA_GETSPECData,"failed to get freq datas"},

//add brook
	{SA_DEV_RESISTED,          "device function has been registered"},    //璁惧鍔熻兘宸茬粡娉ㄥ唽
	{SA_DEV_RESISTE_FAILD,     "device function registered failed"},      //璁惧鍔熻兘娉ㄥ唽澶辫触
	{SA_DEV_UNRESISTE_FAILD,   "device function unregistered failed"},    //璁惧鍔熻兘鎾ら攢澶辫触
	{SA_DEV_NOTRESISTE,        "device function has not been registered"},//璁惧鍔熻兘娌℃湁娉ㄥ唽
	{SA_DEV_NOT,               "not have this device function"},          //娌℃湁姝よ澶囧姛鑳?
	{SA_DEV_OPEN,              "device function open error"},             //璁惧鍔熻兘鎵撳紑澶辫触
	{SA_DEV_CLOSE,             "device function close error"},            //璁惧鍔熻兘鍏抽棴澶辫触
	{SA_DEV_READ,              "device function read error"},             //璁惧鍔熻兘璇诲け璐?
	{SA_DEV_WRITE,             "device function write error"},            //璁惧鍔熻兘鍐欏け璐?
	{SA_BUS_NOT,               "not have this bus type"},                 //娌℃湁姝ょ鎬荤嚎
	{SA_MEM_ALLOC,             "memery alloc failed"},                    //鍐呭瓨鍒嗛厤澶辫触
	{SA_EPOLL_WAITE,           "epoll_wait failed"},                      //epoll_wait鍑芥暟澶辫触
	{SA_THREAD_CREATE,         "pthread_create failed"},                  //pthread_create鍑芥暟澶辫触
	{SA_THREAD_CANCEL,         "pthread cancel failed"},                  //pthread_cancel鍑芥暟澶辫触
	{SA_NO_CALLBACK,           "callback registered failed"},             //娉ㄥ唽鍥炶皟鍑芥暟澶辫触
	{SA_SHAREMEM_OVER,         "share memery overflow"},                  //鍏变韩鍐呭瓨瓒婄晫
	{SA_SHAREMEM_ALIGNED,      "share memery aligned error"},             //鍏变韩鍐呭瓨涓?瀛楄妭瀵归綈
	{SA_DPX_OPEN,              "DPX open error"},                         //DPX鎵撳紑澶辫触
	{SA_DPX_REGISTE,           "DPX register error"},                     //DPX娉ㄥ唽澶辫触
	{SA_DPX_UNREGISTE,         "DPX unregister error"},                   //DPX鎾ら攢澶辫触
	{SA_DPX_OVER,			   "DPX memery overflow"},                    //DPX memery overflow
	{SA_DPX_CLOSE,             "DPX close error"},                        //DPX鍏抽棴澶辫触
	{SA_TEMP_OPEN,             "temperature open error"},                 //娓╁害鎵撳紑澶辫触
	{SA_TEMP_READ,             "temperature read error"},                 //娓╁害璇诲彇澶辫触
	{SA_TEMP_CLOSE,            "temperature close error"},                //娓╁害鍏抽棴澶辫触
	{SA_UDISK_OPEN,            "UDISK open error"},                       //U鐩樻墦寮€澶辫触
	{SA_UDISK_READ,            "UDISK read error"},                       //U鐩樿鍙栧け璐?
	{SA_UDISK_CLOSE,           "UDISK close error"},                      //U鐩樺叧闂け璐?
	{SA_SWEEP_OPEN,            "sweep open error"},                       //SWEEP靠靠
	{SA_SWEEP_REGISTE,         "sweep register error"},                   //SWEEP靠靠
	{SA_SWEEP_UNREGISTE,       "sweep unregister error"},                 //SWEEP靠靠
	{SA_SWEEP_CLOSE,           "sweep close error"},                      //SWEEP靠靠
//end brook



//add gaven     
  {SA_MISC_OPEN, 		       "pl misc open error"},	//杂项设备打开失败
  {SA_MISC_CLOSE,	           "pl misc close error"},  //杂项设备关闭失败
  {SA_KEYLIGHT_OPEN,	       "keyBacklight open error"},	//键盘灯打开错误
  {SA_KEYLIGHT_CLOSE,		   "keyBacklight close error"}, //键盘灯关闭错误
  {SA_FANALARM_RESISTED,	   "fan alarm has been registered"},//风扇报警已经注册
  {SA_FANALARM_RESISTE_FAILD,  "fan alarm  registered failed"}, //风扇报警注册失败
  {SA_FANALARM_UNRESISTE_FAILD,"fan alarm  unregistered failed"},//风扇报警卸载失败
  {SA_FAN_OPEN, 			   "fan open error"}, 			//风扇打开错误
  {SA_FAN_CLOSE,			   "fan close error"},			//风扇关闭错误
  {SA_USBHUB_OPEN,			   "usbhub open error"}, 	    //usb hub 打开错误
  {SA_USBHUB_CLOSE,			   "usbhub close error"},		//usb hub 关闭错误
  {SA_GPS_ENABLE,			   "gps dev enable error"}, 	 //gps dev 使能错误
  {SA_GPS_DISABLE,			   "gps dev disable error"},	 //gps dev 不使能错误
  {SA_GPS_OPEN,			       "gps open error"}, 	         //gps 打开错误
  {SA_GPS_READ,                "gps read error"},            //gps 读取数据错误
  {SA_GPS_CLOSE,			   "gps close error"},		     //gps 关闭错误
  {SA_GPSPULSE_OPEN,		   "gps out pulse open error"},  //gps 脉冲输出打开错误
  {SA_GPSPULSE_CLOSE,		   "gps out pulse close error"}, //gps 脉冲输出关闭错误
  

//end gaven

};
//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions   
/*
In the process of function execution, if there is no exception, the return value is 0, and the return value of any exception is negative
Different error return codes represent different meanings, and the meaning of representation is obtained through error code query.
The error code is from the thirtieth to the right of the hexadecimal to indicate the setting ID number of the module, and the eleventh represents the error class.
When is 1, the parameter level error is represented, and the lower eight bits represent the index number of the error information;A value of 0 indicates a hardware path control failure
*/
DiInt32 BitGetErrorInfo(DiInt32 errorCode,DiInt32 LangType,DiPChar errBuffer)
{  
  if(errorCode>=0)
    {
      sprintf(errBuffer,"state ok");
      return -1;
    }
  if(errorCode>>11&1)
    {
      int temp = sizeof(errInfoList)/sizeof(BITDICTION);
      if((errorCode & 0x000000ff) <= temp -1)
        {
          sprintf(errBuffer,"%s",errInfoList[errorCode & 0x000000ff].strInfo);
          return 0;
        }
      else
        {
          sprintf(errBuffer,"No such exception code");
          return -1;
        }
    }
  else
    {
      int temp = sizeof(errInfoListEx)/sizeof(BITDICTION);
      if((errorCode & 0x000000ff) <= temp)
        {
          sprintf(errBuffer,"%s",errInfoListEx[(errorCode & 0x000000ff ) - 1].strInfo);
          return 0;
        }
      else
        {
          sprintf(errBuffer,"No such exception code");
          return -1;
        }
    }
}


