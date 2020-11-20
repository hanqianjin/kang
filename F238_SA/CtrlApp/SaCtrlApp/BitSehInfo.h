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
#define ERR_RF_Path		    (ERR_MASK|0x1)		//设置射频通路失败
#define ERR_LO_Path		    (ERR_MASK|0x2)		//设置本振通路失败
#define ERR_PreSelector		    (ERR_MASK|0x3)		//设置预选开关失败
#define ERR_Atten		    (ERR_MASK|0x4)		//手动设置衰减器失败
#define ERR_YTFFreq		    (ERR_MASK|0x5)		//设置YTF频率失败
#define ERR_Config		    (ERR_MASK|0x6)		//配置模块参数失败
#define ERR_Setup		    (ERR_MASK|0x7)		//自动配置模块失败
#define ERR_GetCorrections	    (ERR_MASK|0x8)		//获取插损值失败
#define ERR_YTFDegauss		    (ERR_MASK|0x9)		//获取消磁时间失败
#define ERR_REFloss		    (ERR_MASK|0xa)		//本振10M内外参考设置失败
#define ERR_Trigloss		    (ERR_MASK|0xb)		//触发设置失败 

//---------------------F235_SA----------------------------------------	
#define SA_FREQ_BANDSwitch  		(ERR_MASK|0xc) 		//设置频段控制失败
#define SA_ZEROFRE_SUPAMPAtten  	(ERR_MASK|0xd)		//零频抑制幅度衰减器控制失败
#define SA_SECMEDFRE_Atten 		(ERR_MASK|0xe)		//设置二中频衰减器控制失败
#define SA_ZEROFRE_SUPPhase  		(ERR_MASK|0xf)		//设置零频抑制相位控制失败  
#define SA_LOW_PREAtten 		(ERR_MASK|0x10)		// 设置7.5-23.63375GHz前置衰减器控制失败
#define SA_LOW_FRONTGate		(ERR_MASK|0x11)		// 设置7.5-23.63375G前放选通失败
#define SA_HIGH_PREAtten 		(ERR_MASK|0x12)		//设置9k-7.5GHz前置衰减器控制失败      
#define SA_HIGH_FRONTGate  		(ERR_MASK|0x13)		//设置9k-7.5GHz前放选通失败 
#define SA_LO_Control			(ERR_MASK|0x14)		//设置Hmc703本振控制失败  
#define SA_SYSRES_Signal		(ERR_MASK|0x15)		//设置系统复位信号失败 
#define SA_MEDFRE_Gain 	   		(ERR_MASK|0x16)		//设置AD8009中频增益控制失败 
#define SA_INEXT_Reference		(ERR_MASK|0x17)		//设置内外参考控制失败   
#define SA_CRYVOLT_Control  		(ERR_MASK|0x18)		//设置晶振电压控制失败 
#define SA_ULTRAHIGH_PREAtten		(ERR_MASK|0x19)		//设置23.63375-32GHz前置衰减器控制失败  
#define SA_PRESelect			(ERR_MASK|0x1A)		//前置放大器选择失败

#define SA_RBW 				(ERR_MASK|0x1B)		//设置分辨率带宽失败   
#define SA_VBW				(ERR_MASK|0x1C)		//设置视频带宽失败
#define SA_DETECTORMode			(ERR_MASK|0x1D)		//设置检波方式/类型失败 
#define SA_DATAPROMode			(ERR_MASK|0x1E)		//设置数据处理模式失败 
#define SA_SWPStart			(ERR_MASK|0x1F)		//设置开始扫描信号失败
#define SA_ZEROSPANFlag			(ERR_MASK|0x20)		//设置零扫宽模式标志失败   
#define SA_DOTSWPTime			(ERR_MASK|0x21)		//设置每点扫描时间间隔失败 
#define SA_TOTALSWPTime			(ERR_MASK|0x22)		//设置波段总扫描时间失败    
#define SA_DISPLAYNum			(ERR_MASK|0x23)		//设置仪器屏幕显示点数失败  
#define SA_DETECTORFlag			(ERR_MASK|0x24)		//设置检波标志失败   
#define SA_DATAADDRClr			(ERR_MASK|0x25)		//设置数据存储RAM地址清零信号失败    
#define SA_FFTBUCKETNum			(ERR_MASK|0x26)		//设置FFT检波点数失败  
#define SA_AUDIOTime			(ERR_MASK|0x27)		//设置解调时间失败   
#define SA_AUDIOVolume			(ERR_MASK|0x28)		//设置解调音量失败 
#define SA_AUDIOType			(ERR_MASK|0x29)		//设置解调类型失败  
#define SA_AUDIOEn			(ERR_MASK|0x2a)		//设置解调开关失败
#define SA_FFTCALNum			(ERR_MASK|0x2b)		//设置FFT计算点数失败     
#define SA_FFTDirection			(ERR_MASK|0x2c)		//设置FFT扫描方向失败   
#define SA_FFTVALIDSTANum		(ERR_MASK|0x2d)		//设置数据FFT有效点数起始失败
#define SA_FFTVALIDENDNum   		(ERR_MASK|0x2e)		//设置数据FFT有效点数终止失败    
#define SA_FFTDOTSWPTime		(ERR_MASK|0x2f)		//设置FFT每点扫描时间失败  
#define SA_BUCKETTRIGTime   		(ERR_MASK|0x30)		//设置锁相步进触发提前检波触发时间失败 
#define SA_RBWVBWFIL_DELAYTime      	(ERR_MASK|0x31)		//设置RBW VBW滤波器延迟时间失败  
#define SA_TRIGType			(ERR_MASK|0x32)		//软件触发类型设置失败  
#define SA_TRIGDirect			(ERR_MASK|0x33)		//设置触发极性方向失败
#define SA_TRIGTIME			(ERR_MASK|0x34)		//设置触发延迟时间失败 
#define SA_TRIGAmp			(ERR_MASK|0x35)		//设置触发电平幅值失败  
#define SA_VEDIOTRIGAmp                 (ERR_MASK|0x75)
#define SA_TRIGPERTIME                  (ERR_MASK|0x76)
#define SA_RFBURSTTRIGAmp               (ERR_MASK|0x77)

//08/10 steve
#define SA_LASTBand    			(ERR_MASK|0x36)   //setting to tell this is last band
#define SA_LOStep     			(ERR_MASK|0x37)
#define SA_LOLastBandKeeptime   	(ERR_MASK|0x38)
#define SA_SEGPoint     		(ERR_MASK|0x39)
#define SA_SWPStop			(ERR_MASK|0x3a)
#define SA_CHECKSegNum			(ERR_MASK|0x3b)
#define SA_FIRBUcketTime		(ERR_MASK|0x3c)
#define SA_GETSPECData   		(ERR_MASK|0x3d)
///14/08 brook

#define SA_DEV_RESISTED		 (ERR_MASK|0x3e)//设备功能已经注册
#define SA_DEV_RESISTE_FAILD	 (ERR_MASK|0x3f)//设备功能注册失败
#define SA_DEV_UNRESISTE_FAILD	 (ERR_MASK|0x40)//设备功能撤销失败
#define SA_DEV_NOTRESISTE    	 (ERR_MASK|0x41)//设备功能没有注册
#define SA_DEV_NOT          	 (ERR_MASK|0x42)//没有此设备功能
#define SA_DEV_OPEN          	 (ERR_MASK|0x43)//设备功能打开失败
#define SA_DEV_CLOSE          	 (ERR_MASK|0x44)//设备功能关闭失败
#define SA_DEV_READ          	 (ERR_MASK|0x45)//设备功能读失败
#define SA_DEV_WRITE          	 (ERR_MASK|0x46)//设备功能写失败
#define SA_BUS_NOT          	 (ERR_MASK|0x47)//没有此种总线
#define SA_MEM_ALLOC        	 (ERR_MASK|0x48)//内存分配失败
#define SA_EPOLL_WAITE      	 (ERR_MASK|0x49)//epoll_wait函数失败
#define SA_THREAD_CREATE     	 (ERR_MASK|0x4a)//pthread_create函数失败
#define SA_THREAD_CANCEL     	 (ERR_MASK|0x4b)//pthread_cancel函数失败
#define SA_NO_CALLBACK     	 (ERR_MASK|0x4c)//注册回调函数失败
#define SA_SHAREMEM_OVER         (ERR_MASK|0X4d)//共享内存越界
#define SA_SHAREMEM_ALIGNED      (ERR_MASK|0X4e)//共享内存不4字节对齐
#define SA_DPX_OPEN              (ERR_MASK|0X4f)//DPX打开失败
#define SA_DPX_REGISTE           (ERR_MASK|0X50)//DPX注册失败
#define SA_DPX_UNREGISTE         (ERR_MASK|0X51)//DPX撤销失败
#define SA_DPX_OVER              (ERR_MASK|0X52)//DPX内存越界
#define SA_DPX_CLOSE             (ERR_MASK|0X53)//DPX关闭失败
#define SA_TEMP_OPEN             (ERR_MASK|0X54)//温度打开失败
#define SA_TEMP_READ             (ERR_MASK|0X55)//温度读取失败
#define SA_TEMP_CLOSE            (ERR_MASK|0X56)//温度关闭失败
#define SA_UDISK_OPEN            (ERR_MASK|0X57)//U盘打开失败
#define SA_UDISK_READ            (ERR_MASK|0X58)//U盘读取失败
#define SA_UDISK_CLOSE           (ERR_MASK|0X59)//U盘关闭失败
#define SA_SWEEP_OPEN            (ERR_MASK|0X5a)//SWEEP打开失败
#define SA_SWEEP_REGISTE         (ERR_MASK|0X5b)//SWEEP注册失败
#define SA_SWEEP_UNREGISTE       (ERR_MASK|0X5c)//SWEEP撤销失败
#define SA_SWEEP_CLOSE           (ERR_MASK|0X5d)//SWEEP关闭失败




//end brook 
//--------------------------------------------------------------------

///14/08 gaven

#define SA_MISC_OPEN           (ERR_MASK|0X60)//杂项设备打开失败
#define SA_MISC_IOCTL          (ERR_MASK|0X61)//杂项设备控制失败
#define SA_MISC_CLOSE          (ERR_MASK|0X61)//杂项设备关闭失败


#define SA_KEYLIGHT_OPEN       (ERR_MASK|0X62)//键盘灯打开失败
#define SA_KEYLIGHT_CLOSE      (ERR_MASK|0X63)//键盘灯关闭失败
#define SA_FANALARM_RESISTED		(ERR_MASK|0x64)//风扇报警已经注册
#define SA_FANALARM_RESISTE_FAILD	(ERR_MASK|0x65)//风扇报警注册失败
#define SA_FANALARM_UNRESISTE_FAILD	(ERR_MASK|0x66)//风扇报警撤销失败
#define SA_FAN_OPEN            (ERR_MASK|0X67)//风扇打开失败
#define SA_FAN_CLOSE           (ERR_MASK|0X68)//风扇关闭失败
#define SA_USBHUB_OPEN         (ERR_MASK|0X69)//USBHUB打开失败
#define SA_USBHUB_CLOSE        (ERR_MASK|0X6A)//USBHUB关闭失败
#define SA_GPS_ENABLE          (ERR_MASK|0X6B)//GPS使能失败
#define SA_GPS_DISABLE         (ERR_MASK|0X6C)//GPS不使能失败
#define SA_GPS_OPEN            (ERR_MASK|0X6D)//GPS打开失败
#define SA_GPS_READ            (ERR_MASK|0X6E)//GPS数据读取失败
#define SA_GPS_CLOSE           (ERR_MASK|0X6F)//GPS关闭失败
#define SA_GPSPULSE_OPEN       (ERR_MASK|0X70)//GPS打开脉冲输出失败
#define SA_GPSPULSE_CLOSE      (ERR_MASK|0X71)//GPS关闭脉冲输出失败

#define SA_DEV_MUTEX_INIT      (ERR_MASK|0X72)//驱动线程锁初始化失败
#define SA_DEV_MUTEX_LOCK      (ERR_MASK|0X73)//驱动线程锁上锁失败
#define SA_DEV_MUTEX_UNLOCK    (ERR_MASK|0X74)//驱动线程锁解锁失败


//end gaven 
//--------------------------------------------------------------------





		
//错误信息
		
#define ERR_NoErr			0
#define ERR_COMMON_INVALIDPARAM1	0x1		//第1个输入参数无效
#define ERR_COMMON_INVALIDPARAM2	0x2		//第2个输入参数无效
#define ERR_COMMON_INVALIDPARAM3	0x3		//第3个输入参数无效
#define ERR_COMMON_INVALIDPARAM4	0x4		//第4个输入参数无效
#define ERR_COMMON_INVALIDPARAM5	0x5		//第5个输入参数无效
#define ERR_COMMON_INVALIDPARAM6	0x6		//第6个输入参数无效
#define ERR_COMMON_INVALIDPARAM7	0x7		//第7个输入参数无效
#define ERR_COMMON_NOHANDLE		0x8		//无句柄，初始化失败或已经关闭     
#define ERR_COMMON_INIT			0x9		//初始化失败
#define ERR_COMMON_OPENED		0xA		//模块已经打开 
#define ERR_COMMON_RESCNAME		0xB	    //资源名错误
#define ERR_COMMON_CANNT_OPEN		0xC		//获得模块句柄错误 
#define ERR_COMMON_GET_SERIALID		0xD		//获得串号失败 
#define ERR_COMMON_SET_SERIALID		0xE		//获得串号失败 
#define ERR_COMMON_GET_POS_INFO     	0xF		//获取位置信息失败
#define ERR_COMMON_GET_DEV_INFO     	0x10	//获取模块信息失败
#define ERR_COMMON_GET_RMTDEV_INFO  	0x11	//获取远程模块信息失败
#define ERR_COMMON_RESET		0x12	//复位失败
#define ERR_COMMON_SELF_TEST		0x13	//自测试失败 
#define ERR_COMMON_GETTEMPERATURE	0x14	//获取温度信息失败
#define ERR_COMMON_ALLOC_CALDATA	0x15	//分配校准数据空间失败
#define ERR_COMMON_READCALDATA		0x16	//获取校准数据失败
#define ERR_COMMON_WRITECALDATA	    	0x17	//写入校准数据失败
#define ERR_COMMON_READ_CAL_FILE	0x18	//读取校准数据文件失败
#define ERR_COMMON_REWRITE_CAL_FILE 	0x19	//重写校准数据文件失败
#define ERR_COMMON_CHECK_CAL_FILE   	0x1A	//校验校准文件失败
#define ERR_COMMON_REGEDITL_FILE    	0x1B	//注册路径文件失败 

#define ERR_COMMON_MASK    	(0<<12|0x80000800) 
#define ERR_InvalidParam1	(ERR_COMMON_MASK | ERR_COMMON_INVALIDPARAM1)	//第1个输入参数无效
#define ERR_InvalidParam2	(ERR_COMMON_MASK | ERR_COMMON_INVALIDPARAM2)	//第2个输入参数无效
#define ERR_InvalidParam3	(ERR_COMMON_MASK | ERR_COMMON_INVALIDPARAM3)	//第3个输入参数无效
#define ERR_InvalidParam4	(ERR_COMMON_MASK | ERR_COMMON_INVALIDPARAM4)	//第4个输入参数无效
#define ERR_InvalidParam5	(ERR_COMMON_MASK | ERR_COMMON_INVALIDPARAM5)	//第5个输入参数无效
#define ERR_InvalidParam6	(ERR_COMMON_MASK | ERR_COMMON_INVALIDPARAM6)	//第6个输入参数无效
#define ERR_InvalidParam7	(ERR_COMMON_MASK | ERR_COMMON_INVALIDPARAM7)	//第7个输入参数无效
#define ERR_NoHandle		(ERR_COMMON_MASK | ERR_COMMON_NOHANDLE)			//无句柄，初始化失败或已经关闭     
#define ERR_Init		(ERR_COMMON_MASK | ERR_COMMON_INIT)				//初始化失败
#define ERR_InitOpened  	(ERR_COMMON_MASK | ERR_COMMON_OPENED)			//模块已经打开
#define ERR_InitRescName	(ERR_COMMON_MASK | ERR_COMMON_RESCNAME)			//资源名错误
#define ERR_InitCanntOpen	(ERR_COMMON_MASK | ERR_COMMON_CANNT_OPEN)		//获得模块句柄错误
#define ERR_GetSerialID 	(ERR_COMMON_MASK | ERR_COMMON_GET_SERIALID)		//获得串号失败    
#define ERR_SetSerialID 	(ERR_COMMON_MASK | ERR_COMMON_SET_SERIALID)		//获得串号失败    
#define ERR_Get_Pos_Info 	(ERR_COMMON_MASK | ERR_COMMON_GET_POS_INFO)		//获取位置信息失败     
#define ERR_Get_Dev_Info 	(ERR_COMMON_MASK | ERR_COMMON_GET_DEV_INFO)		//获取模块信息失败     
#define ERR_Get_RDev_Info 	(ERR_COMMON_MASK | ERR_COMMON_GET_RMTDEV_INFO)	//获取远程模块信息失败     
#define ERR_Reset		(ERR_COMMON_MASK | ERR_COMMON_RESET)			//复位失败
#define ERR_SelfTest		(ERR_COMMON_MASK | ERR_COMMON_SELF_TEST)		//自测试失败 
#define ERR_GetTemperature	(ERR_COMMON_MASK | ERR_COMMON_GETTEMPERATURE)	//获取温度信息失败
#define ERR_AllocCalData    	(ERR_COMMON_MASK | ERR_COMMON_ALLOC_CALDATA)    //分配校准数据空间失败 
#define ERR_ReadCalData		(ERR_COMMON_MASK | ERR_COMMON_READCALDATA)		//获取校准数据失败
#define ERR_WriteCalData	(ERR_COMMON_MASK | ERR_COMMON_WRITECALDATA)		//写入校准数据失败
#define ERR_ReadCALFile 	(ERR_COMMON_MASK | ERR_COMMON_READ_CAL_FILE)	//读取校准数据文件失败
#define ERR_ReWriteCALFile  	(ERR_COMMON_MASK | ERR_COMMON_REWRITE_CAL_FILE) //重写校准数据文件失败
#define ERR_CheckCalData    	(ERR_COMMON_MASK | ERR_COMMON_CHECK_CAL_FILE)   //校验校准文件失败
#define ERR_CheckregeditPath 	(ERR_COMMON_MASK | ERR_COMMON_REGEDITL_FILE)

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
