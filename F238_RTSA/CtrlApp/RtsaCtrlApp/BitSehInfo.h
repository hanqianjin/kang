//==============================================================================
//
// Title:		BitSehInfo
// Purpose:		A short description of the interface.
//
// Created on:	2017/10/10 at 10:35:45 by yangxiaotao.
// Copyright:	cetc41. All Rights Reserved.
//
//==============================================================================

#ifndef __BitSehInfo_H__
#define __BitSehInfo_H__

#ifdef  BITSEHINFO
#else
#define BITSEHINFO  __declspec(dllimport)
#endif

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "BitVisaType.h" 

//==============================================================================
// Constants

//==============================================================================
// Types
#ifndef BITDICTIONLISE
#define BITDICTIONLISE

#define ERR_MASK            	(0<<12|0x80000000)   
//#define ERR_RF_Path		    (ERR_MASK|0x1)		//设置射频通路失败
//#define ERR_LO_Path		    (ERR_MASK|0x2)		//设置本振通路失败
//#define ERR_PreSelector		(ERR_MASK|0x3)		//设置预选开关失败
//#define ERR_Atten		    (ERR_MASK|0x4)		//手动设置衰减器失败

//---------------------F235_SA----------------------------------------	
//#define RTSA_PRESelect			(ERR_MASK|0x1A)		//前置放大器选择失败

//#define RTSA_VBW					(ERR_MASK|0x1C)		//设置视频带宽失败
//#define RTSA_DETECTORMode			(ERR_MASK|0x1D)		//设置检波方式/类型失败 
//#define RTSA_DATAPROMode			(ERR_MASK|0x1E)		//设置数据处理模式失败 
#define RTSA_SWPStart				(ERR_MASK|0x1F)		//设置开始扫描信号失败
#define RTSA_ZEROSPANFlag			(ERR_MASK|0x20)		//设置零扫宽模式标志失败   
#define RTSA_DOTSWPTime			(ERR_MASK|0x21)		//设置每点扫描时间间隔失败 
#define RTSA_TOTALSWPTime			(ERR_MASK|0x22)		//设置波段总扫描时间失败    
#define RTSA_DISPLAYNum			(ERR_MASK|0x23)		//设置仪器屏幕显示点数失败  
#define RTSA_DETECTORFlag			(ERR_MASK|0x24)		//设置检波标志失败   
#define RTSA_DATAADDRClr			(ERR_MASK|0x25)		//设置数据存储RAM地址清零信号失败    
#define RTSA_FFTBUCKETNum			(ERR_MASK|0x26)		//设置FFT检波点数失败  
#define RTSA_FFTCALNum			(ERR_MASK|0x2b)		//设置FFT计算点数失败     
#define RTSA_FFTDirection			(ERR_MASK|0x2c)		//设置FFT扫描方向失败   
#define RTSA_FFTVALIDSTANum		(ERR_MASK|0x2d)		//设置数据FFT有效点数起始失败
#define RTSA_FFTVALIDENDNum   	(ERR_MASK|0x2e)		//设置数据FFT有效点数终止失败    
#define RTSA_FFTDOTSWPTime		(ERR_MASK|0x2f)		//设置FFT每点扫描时间失败  
#define RTSA_BUCKETTRIGTime   	(ERR_MASK|0x30)		//设置锁相步进触发提前检波触发时间失败 
#define RTSA_RBWVBWFIL_DELAYTime      (ERR_MASK|0x31)		//设置RBW VBW滤波器延迟时间失败  
//#define RTSA_TRIGType					(ERR_MASK|0x32)		//软件触发类型设置失败  
//#define RTSA_TRIGDirect			 	(ERR_MASK|0x33)		//设置触发极性方向失败
//#define RTSA_TRIGTIME					(ERR_MASK|0x34)		//设置触发延迟时间失败 
//#define RTSA_TRIGAmp					(ERR_MASK|0x35)		//设置触发电平幅值失败  

//08/10 steve
//#define RTSA_LASTBand    (ERR_MASK|0x36)   //setting to tell this is last band
//#define RTSA_LOStep     (ERR_MASK|0x37)
//#define RTSA_LOLastBandKeeptime   (ERR_MASK|0x38)
#define RTSA_SEGPoint     (ERR_MASK|0x39)
#define RTSA_SWPStop			(ERR_MASK|0x3a)
//#define RTSA_CHECKSegNum			(ERR_MASK|0x3b)
#define RTSA_FIRBUcketTime			(ERR_MASK|0x3c)
#define RTSA_GETSPECData   (ERR_MASK|0x3d)
//--------------------------------------------------------------------
		 
#define ERR_NoErr				    0

// rtsa ctrl warning dictions.
#define RTSA_RESEVER_NOTICE -1
enum
{
	RTSA_CTL_SHM_INIT = 0,
	RTSA_CTL_MEM_MAP,
	RTSA_CTL_FPGA_LOAD,
	RTSA_CTL_INT_OPEN,
	RTSA_CTL_CAL_FILE,
	RTSA_CTL_TEMP_CAL_FILE,
	RTSA_CTL_FPGA_STOP,
	RTSA_CTL_FPGA_START,
	RTSA_CTL_IFBW,
	RTSA_CTL_RBW,
	RTSA_CTL_DECTECTOR,
	RTSA_CTL_SPAN,
	RTSA_CTL_BUCKET_NUM,
	RTSA_CTL_VALID_START,
	RTSA_CTL_VALID_STOP,
	RTSA_CTL_FFT_WINDOW,
	RTSA_CTL_ACQ_TIME,
	RTSA_CTL_TRIG_MODE,
	RTSA_CTL_TRIG_PERIOD,
	RTSA_CTL_TRIG_DELAY,
	RTSA_CTL_TRIG_HOLDOFF,
	RTSA_CTL_TRIG_VIDEO_LEVEL,
	RTSA_CTL_TRIG_RF_LEVEL,
	RTSA_CTL_TRIG_SLOPE,
	RTSA_CTL_CAL_FACTOR,
	RTSA_CTL_DPX_ENABLE,
	RTSA_CTL_DPX_DISABLE,
	RTSA_CTL_PERSIS_TIME,
	RTSA_CTL_DPX_AXIS_MIN,
	RTSA_CTL_DPX_AXIS_ZOOM,
	RTSA_CTL_DPX_CURVE,
	RTSA_CTL_DPX_DENSITY_HIGHEST,
	RTSA_CTL_DPX_DENSITY_LOWEST,
	RTSA_CTL_FMT_REG,
	RTSA_CTL_FMT_DATA,
	RTSA_CTL_FMT_CRITERION,
	RTSA_CTL_IF_GAIN,
	RTSA_CTL_RF_CHANNEL,
	RTSA_CTL_LO_STEP,
	RTSA_CTL_FIR_LO_FREQ,
	RTSA_CTL_FREQ_SEG_FLAG,
	RTSA_CTL_PREAMP,
	RTSA_CTL_ATTEN,
};

// error wirte to log file or shm flags
enum{
 	LOG_FLAG_DISABLE = 0,
   LOG_FLAG_ENABLE = 1,
   SHM_FLAG_DISABLE = 0,
   SHM_FLAG_ENABLE = 1,
};

#endif 
//==============================================================================
// External variables

//==============================================================================
// Global functions

//by steve,0809
DiInt32 BitGetErrorInfo(DiInt32 errorCode,DiInt32 LangType,DiPChar errBuffer);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __BitSehInfo_H__ */
