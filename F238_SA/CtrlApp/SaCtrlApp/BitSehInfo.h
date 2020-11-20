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
#define ERR_RF_Path		    (ERR_MASK|0x1)		//������Ƶͨ·ʧ��
#define ERR_LO_Path		    (ERR_MASK|0x2)		//���ñ���ͨ·ʧ��
#define ERR_PreSelector		    (ERR_MASK|0x3)		//����Ԥѡ����ʧ��
#define ERR_Atten		    (ERR_MASK|0x4)		//�ֶ�����˥����ʧ��
#define ERR_YTFFreq		    (ERR_MASK|0x5)		//����YTFƵ��ʧ��
#define ERR_Config		    (ERR_MASK|0x6)		//����ģ�����ʧ��
#define ERR_Setup		    (ERR_MASK|0x7)		//�Զ�����ģ��ʧ��
#define ERR_GetCorrections	    (ERR_MASK|0x8)		//��ȡ����ֵʧ��
#define ERR_YTFDegauss		    (ERR_MASK|0x9)		//��ȡ����ʱ��ʧ��
#define ERR_REFloss		    (ERR_MASK|0xa)		//����10M����ο�����ʧ��
#define ERR_Trigloss		    (ERR_MASK|0xb)		//��������ʧ�� 

//---------------------F235_SA----------------------------------------	
#define SA_FREQ_BANDSwitch  		(ERR_MASK|0xc) 		//����Ƶ�ο���ʧ��
#define SA_ZEROFRE_SUPAMPAtten  	(ERR_MASK|0xd)		//��Ƶ���Ʒ���˥��������ʧ��
#define SA_SECMEDFRE_Atten 		(ERR_MASK|0xe)		//���ö���Ƶ˥��������ʧ��
#define SA_ZEROFRE_SUPPhase  		(ERR_MASK|0xf)		//������Ƶ������λ����ʧ��  
#define SA_LOW_PREAtten 		(ERR_MASK|0x10)		// ����7.5-23.63375GHzǰ��˥��������ʧ��
#define SA_LOW_FRONTGate		(ERR_MASK|0x11)		// ����7.5-23.63375Gǰ��ѡͨʧ��
#define SA_HIGH_PREAtten 		(ERR_MASK|0x12)		//����9k-7.5GHzǰ��˥��������ʧ��      
#define SA_HIGH_FRONTGate  		(ERR_MASK|0x13)		//����9k-7.5GHzǰ��ѡͨʧ�� 
#define SA_LO_Control			(ERR_MASK|0x14)		//����Hmc703�������ʧ��  
#define SA_SYSRES_Signal		(ERR_MASK|0x15)		//����ϵͳ��λ�ź�ʧ�� 
#define SA_MEDFRE_Gain 	   		(ERR_MASK|0x16)		//����AD8009��Ƶ�������ʧ�� 
#define SA_INEXT_Reference		(ERR_MASK|0x17)		//��������ο�����ʧ��   
#define SA_CRYVOLT_Control  		(ERR_MASK|0x18)		//���þ����ѹ����ʧ�� 
#define SA_ULTRAHIGH_PREAtten		(ERR_MASK|0x19)		//����23.63375-32GHzǰ��˥��������ʧ��  
#define SA_PRESelect			(ERR_MASK|0x1A)		//ǰ�÷Ŵ���ѡ��ʧ��

#define SA_RBW 				(ERR_MASK|0x1B)		//���÷ֱ��ʴ���ʧ��   
#define SA_VBW				(ERR_MASK|0x1C)		//������Ƶ����ʧ��
#define SA_DETECTORMode			(ERR_MASK|0x1D)		//���ü첨��ʽ/����ʧ�� 
#define SA_DATAPROMode			(ERR_MASK|0x1E)		//�������ݴ���ģʽʧ�� 
#define SA_SWPStart			(ERR_MASK|0x1F)		//���ÿ�ʼɨ���ź�ʧ��
#define SA_ZEROSPANFlag			(ERR_MASK|0x20)		//������ɨ��ģʽ��־ʧ��   
#define SA_DOTSWPTime			(ERR_MASK|0x21)		//����ÿ��ɨ��ʱ����ʧ�� 
#define SA_TOTALSWPTime			(ERR_MASK|0x22)		//���ò�����ɨ��ʱ��ʧ��    
#define SA_DISPLAYNum			(ERR_MASK|0x23)		//����������Ļ��ʾ����ʧ��  
#define SA_DETECTORFlag			(ERR_MASK|0x24)		//���ü첨��־ʧ��   
#define SA_DATAADDRClr			(ERR_MASK|0x25)		//�������ݴ洢RAM��ַ�����ź�ʧ��    
#define SA_FFTBUCKETNum			(ERR_MASK|0x26)		//����FFT�첨����ʧ��  
#define SA_AUDIOTime			(ERR_MASK|0x27)		//���ý��ʱ��ʧ��   
#define SA_AUDIOVolume			(ERR_MASK|0x28)		//���ý������ʧ�� 
#define SA_AUDIOType			(ERR_MASK|0x29)		//���ý������ʧ��  
#define SA_AUDIOEn			(ERR_MASK|0x2a)		//���ý������ʧ��
#define SA_FFTCALNum			(ERR_MASK|0x2b)		//����FFT�������ʧ��     
#define SA_FFTDirection			(ERR_MASK|0x2c)		//����FFTɨ�跽��ʧ��   
#define SA_FFTVALIDSTANum		(ERR_MASK|0x2d)		//��������FFT��Ч������ʼʧ��
#define SA_FFTVALIDENDNum   		(ERR_MASK|0x2e)		//��������FFT��Ч������ֹʧ��    
#define SA_FFTDOTSWPTime		(ERR_MASK|0x2f)		//����FFTÿ��ɨ��ʱ��ʧ��  
#define SA_BUCKETTRIGTime   		(ERR_MASK|0x30)		//�������ಽ��������ǰ�첨����ʱ��ʧ�� 
#define SA_RBWVBWFIL_DELAYTime      	(ERR_MASK|0x31)		//����RBW VBW�˲����ӳ�ʱ��ʧ��  
#define SA_TRIGType			(ERR_MASK|0x32)		//���������������ʧ��  
#define SA_TRIGDirect			(ERR_MASK|0x33)		//���ô������Է���ʧ��
#define SA_TRIGTIME			(ERR_MASK|0x34)		//���ô����ӳ�ʱ��ʧ�� 
#define SA_TRIGAmp			(ERR_MASK|0x35)		//���ô�����ƽ��ֵʧ��  
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

#define SA_DEV_RESISTED		 (ERR_MASK|0x3e)//�豸�����Ѿ�ע��
#define SA_DEV_RESISTE_FAILD	 (ERR_MASK|0x3f)//�豸����ע��ʧ��
#define SA_DEV_UNRESISTE_FAILD	 (ERR_MASK|0x40)//�豸���ܳ���ʧ��
#define SA_DEV_NOTRESISTE    	 (ERR_MASK|0x41)//�豸����û��ע��
#define SA_DEV_NOT          	 (ERR_MASK|0x42)//û�д��豸����
#define SA_DEV_OPEN          	 (ERR_MASK|0x43)//�豸���ܴ�ʧ��
#define SA_DEV_CLOSE          	 (ERR_MASK|0x44)//�豸���ܹر�ʧ��
#define SA_DEV_READ          	 (ERR_MASK|0x45)//�豸���ܶ�ʧ��
#define SA_DEV_WRITE          	 (ERR_MASK|0x46)//�豸����дʧ��
#define SA_BUS_NOT          	 (ERR_MASK|0x47)//û�д�������
#define SA_MEM_ALLOC        	 (ERR_MASK|0x48)//�ڴ����ʧ��
#define SA_EPOLL_WAITE      	 (ERR_MASK|0x49)//epoll_wait����ʧ��
#define SA_THREAD_CREATE     	 (ERR_MASK|0x4a)//pthread_create����ʧ��
#define SA_THREAD_CANCEL     	 (ERR_MASK|0x4b)//pthread_cancel����ʧ��
#define SA_NO_CALLBACK     	 (ERR_MASK|0x4c)//ע��ص�����ʧ��
#define SA_SHAREMEM_OVER         (ERR_MASK|0X4d)//�����ڴ�Խ��
#define SA_SHAREMEM_ALIGNED      (ERR_MASK|0X4e)//�����ڴ治4�ֽڶ���
#define SA_DPX_OPEN              (ERR_MASK|0X4f)//DPX��ʧ��
#define SA_DPX_REGISTE           (ERR_MASK|0X50)//DPXע��ʧ��
#define SA_DPX_UNREGISTE         (ERR_MASK|0X51)//DPX����ʧ��
#define SA_DPX_OVER              (ERR_MASK|0X52)//DPX�ڴ�Խ��
#define SA_DPX_CLOSE             (ERR_MASK|0X53)//DPX�ر�ʧ��
#define SA_TEMP_OPEN             (ERR_MASK|0X54)//�¶ȴ�ʧ��
#define SA_TEMP_READ             (ERR_MASK|0X55)//�¶ȶ�ȡʧ��
#define SA_TEMP_CLOSE            (ERR_MASK|0X56)//�¶ȹر�ʧ��
#define SA_UDISK_OPEN            (ERR_MASK|0X57)//U�̴�ʧ��
#define SA_UDISK_READ            (ERR_MASK|0X58)//U�̶�ȡʧ��
#define SA_UDISK_CLOSE           (ERR_MASK|0X59)//U�̹ر�ʧ��
#define SA_SWEEP_OPEN            (ERR_MASK|0X5a)//SWEEP��ʧ��
#define SA_SWEEP_REGISTE         (ERR_MASK|0X5b)//SWEEPע��ʧ��
#define SA_SWEEP_UNREGISTE       (ERR_MASK|0X5c)//SWEEP����ʧ��
#define SA_SWEEP_CLOSE           (ERR_MASK|0X5d)//SWEEP�ر�ʧ��




//end brook 
//--------------------------------------------------------------------

///14/08 gaven

#define SA_MISC_OPEN           (ERR_MASK|0X60)//�����豸��ʧ��
#define SA_MISC_IOCTL          (ERR_MASK|0X61)//�����豸����ʧ��
#define SA_MISC_CLOSE          (ERR_MASK|0X61)//�����豸�ر�ʧ��


#define SA_KEYLIGHT_OPEN       (ERR_MASK|0X62)//���̵ƴ�ʧ��
#define SA_KEYLIGHT_CLOSE      (ERR_MASK|0X63)//���̵ƹر�ʧ��
#define SA_FANALARM_RESISTED		(ERR_MASK|0x64)//���ȱ����Ѿ�ע��
#define SA_FANALARM_RESISTE_FAILD	(ERR_MASK|0x65)//���ȱ���ע��ʧ��
#define SA_FANALARM_UNRESISTE_FAILD	(ERR_MASK|0x66)//���ȱ�������ʧ��
#define SA_FAN_OPEN            (ERR_MASK|0X67)//���ȴ�ʧ��
#define SA_FAN_CLOSE           (ERR_MASK|0X68)//���ȹر�ʧ��
#define SA_USBHUB_OPEN         (ERR_MASK|0X69)//USBHUB��ʧ��
#define SA_USBHUB_CLOSE        (ERR_MASK|0X6A)//USBHUB�ر�ʧ��
#define SA_GPS_ENABLE          (ERR_MASK|0X6B)//GPSʹ��ʧ��
#define SA_GPS_DISABLE         (ERR_MASK|0X6C)//GPS��ʹ��ʧ��
#define SA_GPS_OPEN            (ERR_MASK|0X6D)//GPS��ʧ��
#define SA_GPS_READ            (ERR_MASK|0X6E)//GPS���ݶ�ȡʧ��
#define SA_GPS_CLOSE           (ERR_MASK|0X6F)//GPS�ر�ʧ��
#define SA_GPSPULSE_OPEN       (ERR_MASK|0X70)//GPS���������ʧ��
#define SA_GPSPULSE_CLOSE      (ERR_MASK|0X71)//GPS�ر��������ʧ��

#define SA_DEV_MUTEX_INIT      (ERR_MASK|0X72)//�����߳�����ʼ��ʧ��
#define SA_DEV_MUTEX_LOCK      (ERR_MASK|0X73)//�����߳�������ʧ��
#define SA_DEV_MUTEX_UNLOCK    (ERR_MASK|0X74)//�����߳�������ʧ��


//end gaven 
//--------------------------------------------------------------------





		
//������Ϣ
		
#define ERR_NoErr			0
#define ERR_COMMON_INVALIDPARAM1	0x1		//��1�����������Ч
#define ERR_COMMON_INVALIDPARAM2	0x2		//��2�����������Ч
#define ERR_COMMON_INVALIDPARAM3	0x3		//��3�����������Ч
#define ERR_COMMON_INVALIDPARAM4	0x4		//��4�����������Ч
#define ERR_COMMON_INVALIDPARAM5	0x5		//��5�����������Ч
#define ERR_COMMON_INVALIDPARAM6	0x6		//��6�����������Ч
#define ERR_COMMON_INVALIDPARAM7	0x7		//��7�����������Ч
#define ERR_COMMON_NOHANDLE		0x8		//�޾������ʼ��ʧ�ܻ��Ѿ��ر�     
#define ERR_COMMON_INIT			0x9		//��ʼ��ʧ��
#define ERR_COMMON_OPENED		0xA		//ģ���Ѿ��� 
#define ERR_COMMON_RESCNAME		0xB	    //��Դ������
#define ERR_COMMON_CANNT_OPEN		0xC		//���ģ�������� 
#define ERR_COMMON_GET_SERIALID		0xD		//��ô���ʧ�� 
#define ERR_COMMON_SET_SERIALID		0xE		//��ô���ʧ�� 
#define ERR_COMMON_GET_POS_INFO     	0xF		//��ȡλ����Ϣʧ��
#define ERR_COMMON_GET_DEV_INFO     	0x10	//��ȡģ����Ϣʧ��
#define ERR_COMMON_GET_RMTDEV_INFO  	0x11	//��ȡԶ��ģ����Ϣʧ��
#define ERR_COMMON_RESET		0x12	//��λʧ��
#define ERR_COMMON_SELF_TEST		0x13	//�Բ���ʧ�� 
#define ERR_COMMON_GETTEMPERATURE	0x14	//��ȡ�¶���Ϣʧ��
#define ERR_COMMON_ALLOC_CALDATA	0x15	//����У׼���ݿռ�ʧ��
#define ERR_COMMON_READCALDATA		0x16	//��ȡУ׼����ʧ��
#define ERR_COMMON_WRITECALDATA	    	0x17	//д��У׼����ʧ��
#define ERR_COMMON_READ_CAL_FILE	0x18	//��ȡУ׼�����ļ�ʧ��
#define ERR_COMMON_REWRITE_CAL_FILE 	0x19	//��дУ׼�����ļ�ʧ��
#define ERR_COMMON_CHECK_CAL_FILE   	0x1A	//У��У׼�ļ�ʧ��
#define ERR_COMMON_REGEDITL_FILE    	0x1B	//ע��·���ļ�ʧ�� 

#define ERR_COMMON_MASK    	(0<<12|0x80000800) 
#define ERR_InvalidParam1	(ERR_COMMON_MASK | ERR_COMMON_INVALIDPARAM1)	//��1�����������Ч
#define ERR_InvalidParam2	(ERR_COMMON_MASK | ERR_COMMON_INVALIDPARAM2)	//��2�����������Ч
#define ERR_InvalidParam3	(ERR_COMMON_MASK | ERR_COMMON_INVALIDPARAM3)	//��3�����������Ч
#define ERR_InvalidParam4	(ERR_COMMON_MASK | ERR_COMMON_INVALIDPARAM4)	//��4�����������Ч
#define ERR_InvalidParam5	(ERR_COMMON_MASK | ERR_COMMON_INVALIDPARAM5)	//��5�����������Ч
#define ERR_InvalidParam6	(ERR_COMMON_MASK | ERR_COMMON_INVALIDPARAM6)	//��6�����������Ч
#define ERR_InvalidParam7	(ERR_COMMON_MASK | ERR_COMMON_INVALIDPARAM7)	//��7�����������Ч
#define ERR_NoHandle		(ERR_COMMON_MASK | ERR_COMMON_NOHANDLE)			//�޾������ʼ��ʧ�ܻ��Ѿ��ر�     
#define ERR_Init		(ERR_COMMON_MASK | ERR_COMMON_INIT)				//��ʼ��ʧ��
#define ERR_InitOpened  	(ERR_COMMON_MASK | ERR_COMMON_OPENED)			//ģ���Ѿ���
#define ERR_InitRescName	(ERR_COMMON_MASK | ERR_COMMON_RESCNAME)			//��Դ������
#define ERR_InitCanntOpen	(ERR_COMMON_MASK | ERR_COMMON_CANNT_OPEN)		//���ģ��������
#define ERR_GetSerialID 	(ERR_COMMON_MASK | ERR_COMMON_GET_SERIALID)		//��ô���ʧ��    
#define ERR_SetSerialID 	(ERR_COMMON_MASK | ERR_COMMON_SET_SERIALID)		//��ô���ʧ��    
#define ERR_Get_Pos_Info 	(ERR_COMMON_MASK | ERR_COMMON_GET_POS_INFO)		//��ȡλ����Ϣʧ��     
#define ERR_Get_Dev_Info 	(ERR_COMMON_MASK | ERR_COMMON_GET_DEV_INFO)		//��ȡģ����Ϣʧ��     
#define ERR_Get_RDev_Info 	(ERR_COMMON_MASK | ERR_COMMON_GET_RMTDEV_INFO)	//��ȡԶ��ģ����Ϣʧ��     
#define ERR_Reset		(ERR_COMMON_MASK | ERR_COMMON_RESET)			//��λʧ��
#define ERR_SelfTest		(ERR_COMMON_MASK | ERR_COMMON_SELF_TEST)		//�Բ���ʧ�� 
#define ERR_GetTemperature	(ERR_COMMON_MASK | ERR_COMMON_GETTEMPERATURE)	//��ȡ�¶���Ϣʧ��
#define ERR_AllocCalData    	(ERR_COMMON_MASK | ERR_COMMON_ALLOC_CALDATA)    //����У׼���ݿռ�ʧ�� 
#define ERR_ReadCalData		(ERR_COMMON_MASK | ERR_COMMON_READCALDATA)		//��ȡУ׼����ʧ��
#define ERR_WriteCalData	(ERR_COMMON_MASK | ERR_COMMON_WRITECALDATA)		//д��У׼����ʧ��
#define ERR_ReadCALFile 	(ERR_COMMON_MASK | ERR_COMMON_READ_CAL_FILE)	//��ȡУ׼�����ļ�ʧ��
#define ERR_ReWriteCALFile  	(ERR_COMMON_MASK | ERR_COMMON_REWRITE_CAL_FILE) //��дУ׼�����ļ�ʧ��
#define ERR_CheckCalData    	(ERR_COMMON_MASK | ERR_COMMON_CHECK_CAL_FILE)   //У��У׼�ļ�ʧ��
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
