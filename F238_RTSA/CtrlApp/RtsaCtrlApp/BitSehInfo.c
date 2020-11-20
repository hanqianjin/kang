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
};

static const BITDICTION errInfoListEx[] =
{
//  {ERR_RF_Path,		"setting Rf path failed"},
//  {ERR_LO_Path,  	    "setting Lo path failed" },
//  {ERR_PreSelector,	"setting preselector failed" },
//  {ERR_Atten, 		"man mode setting atten failed"},
  {RTSA_SWPStart,					"start sweep failed"},
  {RTSA_ZEROSPANFlag,				"zero span flag failed "},
  {RTSA_DOTSWPTime,					"dot sweep time failed "},
  {RTSA_TOTALSWPTime,				"total swp time failed"},
  {RTSA_DISPLAYNum,					"trace num failed"},
  {RTSA_DETECTORFlag,				"detector or not flag failed "},
  {RTSA_DATAADDRClr,				"data clear failed "},
  {RTSA_FFTBUCKETNum,				"fft bucket num failed "},
  {RTSA_FFTCALNum,					"fft calc num failed"},
  {RTSA_FFTDirection,				"fft direction failed  "},
  {RTSA_FFTVALIDSTANum,				"fft valid start index failed  "},
  {RTSA_FFTVALIDENDNum,				"fft valid stop index failed "},
  {RTSA_FFTDOTSWPTime,				"fft dot swp time failed  "},
  {RTSA_BUCKETTRIGTime,				"suo xiang check time failed"},
  {RTSA_RBWVBWFIL_DELAYTime,		"RBW VBW filte delay time failed   "},
//  {RTSA_TRIGType,					"trig type failed "},
//  {RTSA_TRIGDirect,					"trig polar direct failed  "},
//  {RTSA_TRIGTIME,					"trig delay time failed  "},
//  {RTSA_TRIGAmp,					"trig level failed  "},
  
//  {RTSA_LASTBand,    "setting last band failed"},
//  {RTSA_LOStep,     "setting lo step freq failed"},
//  {RTSA_LOLastBandKeeptime,   "failed to set last band keep time"},
  {RTSA_SEGPoint,     "failed to set seg points"},
  {RTSA_SWPStop,			"failed to set sweep stop"},
//  {RTSA_CHECKSegNum,			"failed to set seg check num"},
  {RTSA_FIRBUcketTime,			"failed to set fir bucket time"},
	{RTSA_GETSPECData,"failed to get freq datas"},
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


