//==============================================================================
//
// Title:		MidMsg.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/1/11 at 8:39:55 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "MidMsg.h"
#include "MainBoardVirtualDriver.h"
#include "RfVirtualDriver.h"
#include "DigSigDealVirtualDriver.h"
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include "DpxContrl.h"
#include <math.h>
#include "SaAnalysis.h"
#include "msgNoticeCode.h"
#include "BitSehInfo.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
static int  MID_SLEEP_TIME = 2000;
extern PCONFIG_UPDATE sm_config_update;
extern PCONFIG_RSA_CTRL sm_config_rsa_ctrl;
//extern int sweepHandle; 
extern PSM_SYNC sm_sync;
_SM_SYNC syncMana = {1,1,1,1,1,1};//system control brain
//==============================================================================
// Static functions
static void ClearMsg(void *param);
static DiInt32 DoSweepAction(DiUInt32 msg);
static DiInt32 DoMeasureAction(DiUInt32 msg);
static DiInt32 DoTriggerAction(DiUInt32 msg);
static void TrigResweepByParam();
static void RecovTrigResweepByCtrl();
static void DoTemperCalcAction(DiUInt32 msg);
static void ClearTemperCalcMsg(void *param);
//==============================================================================
// Global variables
extern SWEEPCTRL CTRL_SWEEP_MODE;
extern DiSession bitdevHandle;
extern _CONFIG_RSA_CTRL localConfigRsaCtrl;//used in ctrl_app only

static void TrigAcqByParam();
//added by steve,0423
DiInt32 reCalcflag = 0;//1 means re calc calibrating datas

//0426
static void TrigResweepByCtrl();//means do not reflesh params
DiInt32 reCtrlSweep = 0;//1 means resweep
//==============================================================================
// Global functions
//steve,0605,add ini ctrl for thread not go into listen func
DiInt32 firstguimsg = 0;


extern void ErrOutPut(DiInt32 errCode,DiInt32 itype);
extern void ErrOutPutEx(DiInt32 ToLogFlag,DiInt32 ToShmFlag);
extern PRSA_RUN_SYNC sm_rasctrl;
extern RSA_EXIT gappexit;
extern DiInt32 lisIdleflag;
PSTART_FLAG sm_startflag;
extern int firstInterrupt;
DiReal64 CalRSAData[4001];
DiReal32 CalResultata[4001];
DiReal64 localtempcalc = 0.0;
static DiInt32 cnt = 0;
static DiInt32 innstate = 2;


DiReal32 gspandata[4001];
#define SRDETA (2.0 * 2)
DiInt32 temptrigflag = 0;//1 means retrig
extern DiReal64 tempercalcbuffer[4001];
extern PTEMP_CALC sm_temper_calc;

//extern DiInt32 SweepType;

#define RTSA_SA_SUBTRACTOR	3

void* MidMsgFunc(void *functionData)
{
    while(gappexit.midmsgthreadExit)
        {
            if(!sm_rasctrl->appexit)
                {
                    gappexit.acqthreadExit = 0;
                    //sm_rasctrl->appexit = 1;
//					  sm_startflag->startedflag = 0;
					gappexit.mainthreadExit = 0;
                }
            else if(sm_config_update->top_flag & IXT_ConfigSweep)
                {
                    if(0 == firstguimsg)
                        {
                            CTRL_SWEEP_MODE = SWEEP_CONTI;
                            firstguimsg = 1;
                        }		    
                    DoSweepAction(sm_config_update->sweep_flag);
                    ClearMsg(NULL);
                }      
				else if(sm_config_update->top_flag & IXT_ConfigMeasure)
                {
                      // if(0 == firstguimsg)
                      // {
                      //     CTRL_SWEEP_MODE = SWEEP_CONTI;
                      //      firstguimsg = 1;
                      //   }	
                    DoMeasureAction(sm_config_update->measure_flag);
                    ClearMsg(NULL);
                }
				else if(sm_config_update->top_flag & IXT_Trigger)
                {
//                printf("start trigger msg! %0x\n",sm_config_update->trigger_flag);
                    DoTriggerAction(sm_config_update->trigger_flag);
                    ClearMsg(NULL);
                }
		if(sm_temper_calc->calctop & IXT_TEMPER_CALC)
		{
			DoTemperCalcAction(sm_temper_calc->calctop);
			ClearTemperCalcMsg(NULL);
		}
            usleep(MID_SLEEP_TIME);
        };
		
    gappexit.mainthreadExit = 0;
//		printf("mainthreadExit exit----------------- \n");
    return NULL;
}
static DiReal64 tempData = 0.0;
static void DoTemperCalcAction(DiUInt32 msg)
{
	localtempcalc = sm_temper_calc->detatemp;
	temptrigflag = 1;
       GetTemperCalcDatas(sm_config_rsa_ctrl->CenterFreq,sm_config_rsa_ctrl->TracePoint,localtempcalc,tempercalcbuffer,temptrigflag);
	if((localtempcalc - tempData) > 1 || (localtempcalc - tempData) < -1)
	{
	 tempData = localtempcalc;
	SetRtSaFpgaStop(bitdevHandle);
	TrigResweepByCtrl();
   	 reCtrlSweep = 0;
	sm_config_rsa_ctrl->SweepType = innstate;
	if(localConfigRsaCtrl.Preamp)
   	{
            GetSpanCalcDatasPreOn(localConfigRsaCtrl.CenterFreq,localConfigRsaCtrl.SpanFreq,localConfigRsaCtrl.TracePoint,localConfigRsaCtrl.attenAuto,localConfigRsaCtrl.attenValue,gspandata);
            GetCalcDataWhenPreAmpOnZeroSpan(sm_config_rsa_ctrl->CenterFreq,sm_config_rsa_ctrl->TracePoint,sm_config_rsa_ctrl->RefLevel,sm_config_rsa_ctrl->attenAuto,sm_config_rsa_ctrl->attenValue,CalRSAData);
	}
   	else
   	{
             GetSpanCalcDatasPreOff(localConfigRsaCtrl.CenterFreq,localConfigRsaCtrl.SpanFreq,localConfigRsaCtrl.TracePoint,localConfigRsaCtrl.attenAuto,localConfigRsaCtrl.attenValue,gspandata);
	      	GetCalcDataWhenPreAmpOffZeroSpan(sm_config_rsa_ctrl->CenterFreq,sm_config_rsa_ctrl->TracePoint,sm_config_rsa_ctrl->RefLevel,sm_config_rsa_ctrl->attenAuto,sm_config_rsa_ctrl->attenValue,CalRSAData);
	 }
	for(cnt = 0; cnt < localConfigRsaCtrl.TracePoint; cnt ++)		
		{

            CalResultata[cnt] = (DiReal32)(-tempercalcbuffer[cnt] + CalRSAData[cnt] - SRDETA + gspandata[cnt]);    
			CalResultata[cnt] = pow(10,CalResultata[cnt]/20);
			CalResultata[cnt] = 1 / CalResultata[cnt];
		}
		//printf("DoTemperCalcAction   localtempcalc.......%lf\n",localtempcalc);
		//printf("DoTemperCalcAction   CalResultata %lf,  %lf\n",tempercalcbuffer[0],tempercalcbuffer[800]);

	setRtSaBalanceFactor(bitdevHandle,CalResultata);
	usleep(10000);
	SetRtSaFpgaStart(bitdevHandle);	
	}
	
}
static void ClearTemperCalcMsg(void *param)
{
	sm_temper_calc->calctop = 0;
}
static void ClearMsg(void *param)
{	   
    sm_config_update->top_flag = 0;
    sm_config_update->sweep_flag = 0;   
    return;
}

static void TrigResweepByParam()
{
    syncMana.DeviceMsgUpdate = 1;
    return;
}

static void TrigAcqByParam()
{
    reCalcflag = 1;
    return;
}

static void TrigResweepByCtrl()
{
#if BIT_DEBUG
	return;
#endif
    sm_config_update->stopFlag= 1;
    reCtrlSweep = 1;
    syncMana.DeviceMsgUpdate = 1;
    //SweepType = 2;
   innstate = sm_config_rsa_ctrl->SweepType;
   sm_config_rsa_ctrl->SweepType = 2;
	usleep(20000);

	firstInterrupt = 0;
    return;
}

static void RecovTrigResweepByCtrl()
{
#if BIT_DEBUG
	return;
#endif
    reCtrlSweep = 0;
sm_config_rsa_ctrl->SweepType = innstate;
    //SweepType = sm_config_rsa_ctrl->SweepType;

//Albert 19/07/12 add calc data
	if(localConfigRsaCtrl.Preamp)
   {
            GetSpanCalcDatasPreOn(localConfigRsaCtrl.CenterFreq,localConfigRsaCtrl.SpanFreq,localConfigRsaCtrl.TracePoint,localConfigRsaCtrl.attenAuto,localConfigRsaCtrl.attenValue,gspandata);
        GetCalcDataWhenPreAmpOnZeroSpan(sm_config_rsa_ctrl->CenterFreq,sm_config_rsa_ctrl->TracePoint,sm_config_rsa_ctrl->RefLevel,sm_config_rsa_ctrl->attenAuto,sm_config_rsa_ctrl->attenValue,CalRSAData);
		//printf("GetCalcDataWhenPreAmpOnZeroSpan %10f,  %10f\n",CalRSAData[0],CalRSAData[800]);
	}
   else
   {
             GetSpanCalcDatasPreOff(localConfigRsaCtrl.CenterFreq,localConfigRsaCtrl.SpanFreq,localConfigRsaCtrl.TracePoint,localConfigRsaCtrl.attenAuto,localConfigRsaCtrl.attenValue,gspandata);
	      	GetCalcDataWhenPreAmpOffZeroSpan(sm_config_rsa_ctrl->CenterFreq,sm_config_rsa_ctrl->TracePoint,sm_config_rsa_ctrl->RefLevel,sm_config_rsa_ctrl->attenAuto,sm_config_rsa_ctrl->attenValue,CalRSAData);
		///printf("GetCalcDataWhenPreAmpOnZeroSpan %10f,  %10f\n",CalRSAData[0],CalRSAData[800]);
	 }
	GetTemperCalcDatas(sm_config_rsa_ctrl->CenterFreq,sm_config_rsa_ctrl->TracePoint,localtempcalc,tempercalcbuffer,1);
	for(cnt = 0; cnt < localConfigRsaCtrl.TracePoint; cnt ++)		{

            CalResultata[cnt] = (DiReal32)(-tempercalcbuffer[cnt] + CalRSAData[cnt] - SRDETA + gspandata[cnt]);    
			CalResultata[cnt] = pow(10,CalResultata[cnt]/20);
			CalResultata[cnt] = 1 / CalResultata[cnt];
		}
	
		//printf("sm_config_rsa_ctrl data %10f,  %d,  %10f\n",sm_config_rsa_ctrl->RefLevel,sm_config_rsa_ctrl->attenAuto,sm_config_rsa_ctrl->attenValue);
		//printf("localtempcalc.......%lf\n",localtempcalc);
		//printf("CalResultata %lf,  %lf\n",tempercalcbuffer[0],tempercalcbuffer[800]);
	setRtSaBalanceFactor(bitdevHandle,CalResultata);

	usleep(10000);

    return;
}
static DiInt32 DoSweepAction(DiUInt32 msg)
{
     if(msg & IXS_SweepType)
        {
           if(0 == sm_config_rsa_ctrl->SweepType)
                {                   
                     CTRL_SWEEP_MODE = SWEEP_CONTI;
                }
            //single
            else if(1 == sm_config_rsa_ctrl->SweepType)
                {                    
                     CTRL_SWEEP_MODE = SWEEP_SINGLE;
                }
#if ERR_PRINT_DEBUG
            printf("sweep type msg is %u\n",sm_config_rsa_ctrl->SweepType);
#endif
	  if(msg == IXS_SweepType)
	    {
	      return 0;
            }
        }
	
    DiInt32 iBack = 0;
	DiInt32 iDpxProData = 0;
	iBack = SetRtSaFpgaStop(bitdevHandle);
	TrigResweepByCtrl();
   if(iBack < 0)
   {	
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
      return iBack;
   }

 if(msg & IXS_FilterType)
{
	iBack = SetSwpInterrupt(bitdevHandle);
	if(iBack < 0)
   {
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
		return iBack;
    }	 
    localConfigRsaCtrl.flitertype = sm_config_rsa_ctrl->flitertype;
	iBack = SetRtSaFFTWindow(bitdevHandle,localConfigRsaCtrl.flitertype);
   if(iBack < 0)
   {	
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
      return iBack;
   }
//	printf("filter type msg\n");
}

    if(msg & IXS_Refoffset)
	{			
//	    printf("ref offset msg\n");
	}

    if(msg & IXS_SpanMode)
        {
//            printf("ref ana span msg\n");
        }
	if(msg & IXS_RBW || msg & IXS_RBWAuto)
		{
//			iBack = SetSwpInterrupt(bitdevHandle);
//	       if(iBack < 0)
//          {
//		       ErrOutPut(iBack,2);
//		       return iBack;
//          }
			localConfigRsaCtrl.RBW = sm_config_rsa_ctrl->RBW;
//			printf("RBW msg  set value  %d \n",localConfigRsaCtrl.RBW);
			iBack = SetRtSaRBW(bitdevHandle,localConfigRsaCtrl.RBW);
   			if(iBack < 0)
   			{	
				setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
				ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
      			return iBack;
   			}
//		   printf("RBW msg\n");
		}

    if(msg & IXS_CenterFreq || msg & IXS_SpanFreq || msg & IXS_StartFreq || msg & IXS_StopFreq)
        {  
        // RTSA Means zero span SA
           //local to set step and num to zero
           iBack = SetFirLoStepFreq(bitdevHandle,0,0);
           if(iBack < 0)
           {
				setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
				ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
              return iBack;
           }
			usleep(1000);
           //setting center freq,0503
           localConfigRsaCtrl.CenterFreq = sm_config_rsa_ctrl->CenterFreq;
           iBack = FirstLoFreqCtrl(bitdevHandle,localConfigRsaCtrl.CenterFreq);
			usleep(1000);
           if(iBack < 0)
           {
				setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
				ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
               return iBack;
           }
			 iBack =SetSegmentFlag(bitdevHandle,localConfigRsaCtrl.CenterFreq);
			usleep(1000);
           if(iBack < 0)
           {
				setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
				ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
              return iBack;
           }		
           //setting band,0504
           iBack = RfChannelChoose(bitdevHandle,localConfigRsaCtrl.CenterFreq);
			usleep(1000);
           if(iBack < 0)
           {
				setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
				ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
              return iBack;
           }
           localConfigRsaCtrl.SpanFreq = sm_config_rsa_ctrl->SpanFreq;
           iBack = SetRtSaSpan(bitdevHandle,localConfigRsaCtrl.SpanFreq);
			usleep(1000);
           if(iBack < 0)
           {
				setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
				ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
              return iBack;
           }		
//            printf("freq msg\n"); 
        }

      if(msg & IXS_TracePoint)
        {
            localConfigRsaCtrl.TracePoint = sm_config_rsa_ctrl->TracePoint;
			if(localConfigRsaCtrl.TracePoint < 1)
				{
				   localConfigRsaCtrl.TracePoint = 801;
				}
            iBack = SetDisplayNum(bitdevHandle,localConfigRsaCtrl.TracePoint);
            if(iBack < 0)
                {
//                    ErrOutPut(iBack,1);
                    return iBack;
                }
//            printf("the trace point num is %u\n",localConfigRsaCtrl.TracePoint);
        }

    if(msg & IXS_DetectorMode)
        {			
           localConfigRsaCtrl.DetectorMode = sm_config_rsa_ctrl->DetectorMode;
			iBack = SetRtSaDetector(bitdevHandle, localConfigRsaCtrl.DetectorMode);
           // iBack = SetDetectormode(bitdevHandle,localConfigRsaCtrl.DetectorMode);
           if(iBack < 0)
            {
				setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
				ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
                return iBack;
            }
//            printf("get detector mode msg\n");
        }

    if(msg & IXS_Preamp)
        {            		
           localConfigRsaCtrl.Preamp = sm_config_rsa_ctrl->Preamp;
           iBack = PreAmpliChannelCtrl(bitdevHandle,localConfigRsaCtrl.Preamp);
           if(iBack < 0)
           {
				setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
				ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
               return iBack;
            }
//            if(1)
//                {
//                    TrigAcqByParam();
		    //911
//                    TrigResweepByParam();
//                }
//            printf("get preamp msg\n");
        }

    if(msg & IXS_RefLevel || msg & IXS_AttenSelect)
        {       			 
            localConfigRsaCtrl.RefLevel = sm_config_rsa_ctrl->RefLevel;
            localConfigRsaCtrl.attenValue = sm_config_rsa_ctrl->attenValue;
            localConfigRsaCtrl.attenAuto = sm_config_rsa_ctrl->attenAuto;
            iBack = PreAttenCtrl(bitdevHandle,localConfigRsaCtrl.attenValue);
            if(iBack < 0)
                {
						setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
						ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
                    return iBack;
                }  
//	     printf("amp msg\n");          
        }  
  
    if(msg & IXS_ExtTrigger)
        {
//         	localConfigRsaCtrl.TriggerMode = sm_config_rsa_ctrl->TriggerMode;
//			SetRtSaTrigger(bitdevHandle,localConfigRsaCtrl.dpxApmtMin);
//            printf("get ext trigger\n");
        }
    if(msg & IXS_TriggerMode)
        {
			localConfigRsaCtrl.TriggerMode = sm_config_rsa_ctrl->TriggerMode;
			iBack = SetRtSaTrigger(bitdevHandle,localConfigRsaCtrl.TriggerMode);
			if(iBack < 0)
           {
				setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
				ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
              return iBack;
           }
//			printf("localConfigRsaCtrl.TriggerMode  %0x\n",localConfigRsaCtrl.TriggerMode);
			if(localConfigRsaCtrl.TriggerMode & 0x20)
				{
					 iBack = ConfigFmtReg(bitdevHandle,1);
					if(iBack < 0)
					     {
								setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
								ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
					     }
				}
			else
				{
					iBack = ConfigFmtReg(bitdevHandle,0);
					if(iBack < 0)
					     {
								setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
								ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
					     }
				}
			InitTriggerParam();
//           printf("get trigger mode msg\n");
        } 
		if(msg & IXS_DPXAmptMin)
			{	 
			 localConfigRsaCtrl.dpxApmtMin = sm_config_rsa_ctrl->dpxApmtMin;
			 iBack = DpxAmptAxisMin(bitdevHandle, localConfigRsaCtrl.dpxApmtMin);
            if(iBack < 0)
             {
					setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
					ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
	              return iBack;
             }  
//	            printf("get DPXAmptMin msg\n");
		
		}
			if(msg & IXS_DPXAmptZoom)
			{
			 localConfigRsaCtrl.dpxApmtZoom = sm_config_rsa_ctrl->dpxApmtZoom;
			 iBack = DpxAmptAxisZoom(bitdevHandle, localConfigRsaCtrl.dpxApmtZoom);
            if(iBack < 0)
             {
					setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
					ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
	              return iBack;
             }  
//	            printf("get DPXAmptZoom msg\n");
		
		}
	 if(msg & IXS_AcqTime)
	{		
		localConfigRsaCtrl.acqtimems = sm_config_rsa_ctrl->acqtimems;
//		localConfigRsaCtrl.RBW = sm_config_rsa_ctrl->RBW;
		iBack = SetRtSaAcqTime(bitdevHandle,localConfigRsaCtrl.acqtimems);
       if(iBack < 0)
       {
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
			ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
           return iBack;
        }  
//	    printf("acq time msg \n");
	}
 if(msg & IXS_PersisTime)
{	
	localConfigRsaCtrl.persistimeword = sm_config_rsa_ctrl->persistimeword;
	iBack = DpxPersistenceTime(bitdevHandle,localConfigRsaCtrl.persistimeword);
    if(iBack < 0)
    {
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
        return iBack;
    }  
//	printf("persis time msg   %d\n",localConfigRsaCtrl.persistimeword);
}
 if(msg & IXS_FFT_Bucket_Num)
 	{
//		printf("fft bucket time msg\n");
 	}
if(msg & IXS_Highest_Density)
{
	localConfigRsaCtrl.dpxHighestDensity = sm_config_rsa_ctrl->dpxHighestDensity;
	iBack = setHighestDpxColorTable(bitdevHandle, localConfigRsaCtrl.dpxHighestDensity);
	if(iBack < 0)
    {
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
      return iBack;
    }  
	localConfigRsaCtrl.dpxLowestDensity = sm_config_rsa_ctrl->dpxLowestDensity;
	iBack = setLowestDpxColorTable(bitdevHandle, localConfigRsaCtrl.dpxLowestDensity);
	if(iBack < 0)
    {
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
      return iBack;
    }  
	  localConfigRsaCtrl.dpxCurve = sm_config_rsa_ctrl->dpxCurve;
	iBack = setDpxCurveColor(bitdevHandle, localConfigRsaCtrl.dpxCurve,localConfigRsaCtrl.dpxLowestDensity,localConfigRsaCtrl.dpxHighestDensity);
	if(iBack < 0)
    {
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
       return iBack;
    }  

// 	printf("highest density msg\n");
}
if(msg & IXS_Lowest_Density)
{
	localConfigRsaCtrl.dpxHighestDensity = sm_config_rsa_ctrl->dpxHighestDensity;
	iBack = setHighestDpxColorTable(bitdevHandle, localConfigRsaCtrl.dpxHighestDensity);
	if(iBack < 0)
    {
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
        return iBack;
    }  
	localConfigRsaCtrl.dpxLowestDensity = sm_config_rsa_ctrl->dpxLowestDensity;
	iBack = setLowestDpxColorTable(bitdevHandle, localConfigRsaCtrl.dpxLowestDensity);
	if(iBack < 0)
    {
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
        return iBack;
    }  
	localConfigRsaCtrl.dpxCurve = sm_config_rsa_ctrl->dpxCurve;
	iBack = setDpxCurveColor(bitdevHandle, localConfigRsaCtrl.dpxCurve,localConfigRsaCtrl.dpxLowestDensity,localConfigRsaCtrl.dpxHighestDensity);
	if(iBack < 0)
    {
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
        return iBack;
    }  
// 	printf("lowest density msg\n");
} 
if(msg & IXS_Fmt_Data)
{
	if(sm_config_rsa_ctrl->TriggerMode == 0x20)
	{
		memcpy(localConfigRsaCtrl.fmtData,sm_config_rsa_ctrl->fmtData,sizeof(DiInt32) * 801);
		iBack = setFmtData(bitdevHandle, localConfigRsaCtrl.fmtData);
		if(iBack < 0)
			{
				setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
				ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
				return iBack;
			}
//	 	printf("fmt data msg\n");
	}
}
if(msg & IXS_Curve)
{
  localConfigRsaCtrl.dpxLowestDensity = sm_config_rsa_ctrl->dpxLowestDensity;
  localConfigRsaCtrl.dpxHighestDensity = sm_config_rsa_ctrl->dpxHighestDensity;
  localConfigRsaCtrl.dpxCurve = sm_config_rsa_ctrl->dpxCurve;
	iBack = setDpxCurveColor(bitdevHandle, localConfigRsaCtrl.dpxCurve,localConfigRsaCtrl.dpxLowestDensity,localConfigRsaCtrl.dpxHighestDensity);
	if(iBack < 0)
    {
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
		return iBack;
    } 
//	printf("dpx curve msg\n");
}
if(msg & IXS_Fmt_Trigger_Criterion)
{
	if(sm_config_rsa_ctrl->TriggerMode == 0x20)
		{
			  localConfigRsaCtrl.FmtTriggerCriterion = sm_config_rsa_ctrl->FmtTriggerCriterion;
				iBack = ConfigFmtTriggerCriterion(bitdevHandle,localConfigRsaCtrl.FmtTriggerCriterion);
				if(iBack < 0)
			    {
					setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
					ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
			        return iBack;
			    } 
//				printf("fmt trigger criterion msg\n");
		}
}
if(msg & IXS_DPX_Probability)
{
	getDensityProbability(bitdevHandle,&iDpxProData);
	localConfigRsaCtrl.dpxHighestDensity= (iDpxProData >> 8) & 0xff;
	localConfigRsaCtrl.dpxHighestDensity = (DiInt32)(localConfigRsaCtrl.dpxHighestDensity * 100 / 256 ) ;
	localConfigRsaCtrl.dpxLowestDensity = iDpxProData & 0xff;
	localConfigRsaCtrl.dpxLowestDensity = (DiInt32)(localConfigRsaCtrl.dpxLowestDensity * 100 / 256 ) ;
   sm_config_rsa_ctrl->dpxLowestDensity = localConfigRsaCtrl.dpxLowestDensity;
   sm_config_rsa_ctrl->dpxHighestDensity =localConfigRsaCtrl.dpxHighestDensity;
//	printf("dpxLowestDensity----dpxHighestDensity---- %d,    %d\n",sm_config_rsa_ctrl->dpxLowestDensity,sm_config_rsa_ctrl->dpxHighestDensity);
	if(iBack < 0)
    {
		return iBack;
    } 
}

	RecovTrigResweepByCtrl();

	iBack = SetRtSaFpgaStart(bitdevHandle);
   if(iBack < 0)
   {	
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
		return iBack;
   }

       return 0;
}

static DiInt32 DoMeasureAction(DiUInt32 msg)
{
	DiInt32 iBack = 0;
	TrigResweepByCtrl();
	
	iBack = SetRtSaFpgaStop(bitdevHandle);
	if(iBack < 0)
    	{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
			ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
    		return iBack;
	    }

    if(msg & IXS_Density)
        {
        		iBack = DpxEn(bitdevHandle, 0);
				if(iBack < 0)
				{
					setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
					ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
		    		return iBack;
				}
//            printf("get IXS_Density msg\n");
        }
		else
			{
			 	 DpxDisable(bitdevHandle);
				if(iBack < 0)
				{
					setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
					ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
		    		return iBack;
				}
			}
//    if(msg & IXS_Spectrum)
//        {
//            DpxDisable(bitdevHandle);
//            printf("get channel bw msg\n");
//        }
//    if(msg & IXS_Spectrogram)
//        {
//        	 DpxDisable(bitdevHandle);
//            printf("get channel space msg\n");
//        }
//    if(msg & IXS_Density_Spectrogram)
//        {
//        DpxDisable(bitdevHandle);
//            printf("get demod freq msg\n");
//        }
				RecovTrigResweepByCtrl();

		iBack = SetRtSaFpgaStart(bitdevHandle);
		if(iBack < 0)
    	{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
			ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
    		return iBack;
    	}

    return 0;
}
/*
because trigger param do not need fpga stop and start
*/
static DiInt32 DoTriggerAction(DiUInt32 msg)
{
	DiInt32 iBack = 0;
	TrigResweepByCtrl();
//	printf("DoTriggerAction  start    !!!!\n");
//	printf("msg   index   %0x\n",msg);
    if(msg & IXS_Trigger_Slope)
        {
        	localConfigRsaCtrl.triggerSlope = sm_config_rsa_ctrl->triggerSlope;
			iBack = setRtSaTriggerSlope(bitdevHandle, localConfigRsaCtrl.triggerSlope);
			if(iBack < 0)
    		{
				setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
				ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
        		return iBack;
    		}  
//            printf("get IXS_Trigger_Slope msg %0x\n",localConfigRsaCtrl.triggerSlope);
        }
    if(msg & IXS_Trigger_Delay)
        {
           localConfigRsaCtrl.triggerDelay = sm_config_rsa_ctrl->triggerDelay;
			iBack = SetRtSaTriggerDelay(bitdevHandle, localConfigRsaCtrl.triggerDelay);
			if(iBack < 0)
    		{
				setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
				ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
        		return iBack;
    		}  
//            printf("get IXS_Trigger_Delay %0x\n",localConfigRsaCtrl.triggerDelay);
        }
    if(msg & IXS_Trigger_Period)
        {
           localConfigRsaCtrl.triggerPeriod = sm_config_rsa_ctrl->triggerPeriod;
			iBack = SetRtSaTriggerPeriod(bitdevHandle, localConfigRsaCtrl.triggerPeriod);
			if(iBack < 0)
    		{
				setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
				ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
        		return iBack;
    		}  
//            printf("get IXS_Trigger_Period %0x\n",localConfigRsaCtrl.triggerPeriod);
        }
    if(msg & IXS_Trigger_Video_Level)
        {
           localConfigRsaCtrl.triggervideoLevel = sm_config_rsa_ctrl->triggervideoLevel;
			iBack = SetRtSaTriggerVideoLevel(bitdevHandle, localConfigRsaCtrl.triggervideoLevel);
			if(iBack < 0)
    		{
				setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
				ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
        		return iBack;
    		} 
//            printf("get IXS_Trigger_Video_Level %f\n",localConfigRsaCtrl.triggervideoLevel);
        }
	if(msg & IXS_Trigger_RF_Level)
        {
           localConfigRsaCtrl.triggerRFBurstLevel = sm_config_rsa_ctrl->triggerRFBurstLevel;
			iBack = SetRtSaTriggerRFLevel(bitdevHandle, localConfigRsaCtrl.triggerRFBurstLevel);
			if(iBack < 0)
    		{
				setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
				ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
        		return iBack;
    		}         
//            printf("get IXS_Trigger_Video_Level %f\n",localConfigRsaCtrl.triggerRFBurstLevel);
        }
	if(msg & IXS_Trigger_HoldOff_Time)
        {
           localConfigRsaCtrl.triggerHoldOffTime = sm_config_rsa_ctrl->triggerHoldOffTime;
			iBack = SetRtSaTriggerHideTime(bitdevHandle, localConfigRsaCtrl.triggerHoldOffTime);
			if(iBack < 0)
    		{
				setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
				ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
        		return iBack;
    		}         
//            printf("get IXS_Trigger_HoldOff_Time %d\n",localConfigRsaCtrl.triggerHoldOffTime);
        }	
RecovTrigResweepByCtrl();
	return 0;
}

DiInt32 InitTriggerParam()
{
	DiInt32 iBack = 0;
	DiUInt32 triggerMode = sm_config_rsa_ctrl->TriggerMode;
	iBack = SetRtSaTrigger(bitdevHandle,triggerMode);
	if(iBack < 0)
   	{
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
		ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
      	return iBack;
   	} 
	switch(triggerMode)
		{
			case 0x1:
				break;
			case 0x2:
				iBack = setRtSaTriggerSlope(bitdevHandle, sm_config_rsa_ctrl->triggerSlope);
				if(iBack < 0)
			   	{
					setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
					ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
			      	return iBack;
			   	} 			
				iBack = SetRtSaTriggerDelay(bitdevHandle, sm_config_rsa_ctrl->triggerDelay);
				if(iBack < 0)
			    {
					setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
					ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
			        return iBack;
			    }  
				iBack = SetRtSaTriggerHideTime(bitdevHandle, sm_config_rsa_ctrl->triggerHoldOffTime);
				if(iBack < 0)
			    {
					setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
					ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
			        return iBack;
			    }
				break;
			case 0x4:
				iBack = SetRtSaTriggerPeriod(bitdevHandle, sm_config_rsa_ctrl->triggerPeriod);
				if(iBack < 0)
			    {
					setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
					ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
			        return iBack;
			    }  
				iBack = SetRtSaTriggerDelay(bitdevHandle, sm_config_rsa_ctrl->triggerDelay);
				if(iBack < 0)
			    {
					setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
					ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
			        return iBack;
			    } 
				break;
			case 0x8:
				iBack = setRtSaTriggerSlope(bitdevHandle, sm_config_rsa_ctrl->triggerSlope);
				if(iBack < 0)
			   	{
					setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
					ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
			      	return iBack;
			   	} 			
				iBack = SetRtSaTriggerRFLevel(bitdevHandle, sm_config_rsa_ctrl->triggerRFBurstLevel);
				if(iBack < 0)
			    {
					setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
					ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
			        return iBack;
			    }         
				iBack = SetRtSaTriggerDelay(bitdevHandle, sm_config_rsa_ctrl->triggerDelay);
				if(iBack < 0)
			    {
					setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
					ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
			        return iBack;
			    }  
				iBack = SetRtSaTriggerHideTime(bitdevHandle, sm_config_rsa_ctrl->triggerHoldOffTime);
				if(iBack < 0)
			    {
					setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
					ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
			        return iBack;
			    }
				break;
			case 0x10:
				break;
			case 0x20:
				iBack = ConfigFmtReg(bitdevHandle,1);
				if(iBack < 0)
			    {
					setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_WARNING,iBack);
					ErrOutPutEx(LOG_FLAG_ENABLE,SHM_FLAG_DISABLE);
			        return iBack;
			    }
				break;
		}
	return iBack;
}

