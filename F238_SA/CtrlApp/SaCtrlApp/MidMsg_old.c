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
#include "RfVirtualDriver.h"
#include "DigSigDealVirtualDriver.h"
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include "time.h"
#include "msgNoticeCode.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
DiInt32 intersource = 0;//1 means zhudong occur interrupt,0 means finish sweeping then interrupt;
DiInt32 gwhole = 0;
extern DiInt32 ifinish;
static int  MID_SLEEP_TIME = 1000;
extern PCONFIG_UPDATE sm_config_update;
extern PCONFIG_SWEEP sm_config_sweep;
extern PSM_SYNC sm_sync;
_SM_SYNC syncMana = {1,1,1,1,1,1};//system control brain
//==============================================================================
// Static functions
static void ClearMsg(void *param);
static DiInt32 DoSweepAction(DiUInt32 msg);
static DiInt32 DoMeasureAction(DiUInt32 msg);
static DiInt32 DoSystemAction(DiUInt32 msg);
static DiInt32 DoTriggerAction(DiUInt32 msg);
static DiInt32 DoDoorControlAction(DiUInt32 msg);
static void RecovTrigResweepByCtrl();
static void TrigResweepByParam();
static DiInt32 DoSweepParamLoad();
static DiInt32 DoSweepParamLoadOnSemAndSpur();
static void DoTemperCalcAction(DiUInt32 msg);
static void ClearTemperCalcMsg(void *param);
static DiInt32 StopFreqCountWhenSetPara();
//==============================================================================
// Global variables
extern SWEEPCTRL CTRL_SWEEP_MODE;
extern PSWEEP_NUM sm_sweep_num;
extern DiSession bitdevHandle;
extern _CONFIG_SWEEP localSweepConfig;//used in ctrl_app only

//0426,used in freq,preamp and so on
static void TrigAcqByParam();
//added by steve,0423
DiInt32 reCalcflag = 0;//1 means re calc calibrating datas

//0426
static void TrigResweepByCtrl();//means do not reflesh params
DiInt32 reCtrlSweep = 0;//1 means resweep
extern SWEEP_NUM sweepListinthread;

extern PCONFIG_MEASURE sm_config_measure;
//==============================================================================
// Global functions
//steve,0605,add ini ctrl for thread not go into listen func
DiInt32 firstguimsg = 0;
int SpanFlag = 0;
//0810 steve
extern void ErrOutPut(DiInt32 errCode,DiInt32 itype);

void ZeroSpanSegFlagSet();
extern FREQ_COUNT_LOCAL localFreqCountConfig;

extern DiInt32 bMarkerFreqCountInterrupt;
extern DiInt32 bFreqCountSpanMode;
extern DiInt32 bFreqCountSweepComplete;
extern DiInt32 bFreqCountDataGetComplete;

//0925
extern PBSA_RUN_SYNC sm_basctrl;
extern BSA_EXIT gappexit;
extern PTEMP_CALC sm_temper_calc;
DiReal64 localtempcalc = 0.0;
DiInt32 temptrigflag = 0;//1 means retrig
void* MidMsgFunc(void *functionData)
{
    //while(syncMana.AppExit)
    while(gappexit.midmsgthreadExit)
    {
           if(!sm_basctrl->appexit)
           {
                    	gappexit.acqthreadExit = 0;
                    	sm_basctrl->appexit = 1;
           }
           else if(sm_config_update->top_flag & IXT_ConfigSweep)
           {
/*
                    	if(0 == firstguimsg)
                        {
                            CTRL_SWEEP_MODE = SWEEP_CONTI;
                            firstguimsg = 1;
                        }
*/
                    	DoSweepAction(sm_config_update->sweep_flag);
                    	ClearMsg(NULL);
           }
           else if(sm_config_update->top_flag & IXT_ConfigMeasure)
           {
                    	DoMeasureAction(sm_config_update->measure_flag);
                    	ClearMsg(NULL);
           }
	   else if(sm_config_update->top_flag & IXT_ConfigTrigger)
	   {
			DoTriggerAction(sm_config_update->trigger_flag);
			ClearMsg(NULL);
	   }
	   else if(sm_config_update->top_flag & IXT_ConfigDrCtrlSweep)
	   {
			DoDoorControlAction(sm_config_update->doorControl_flag);
		        ClearMsg(NULL);
	   }
	   if(sm_temper_calc->calctop & IXT_Tempercalc)
           {
			DoTemperCalcAction(sm_temper_calc->calctop);
			ClearTemperCalcMsg(NULL);
	   }
            usleep(MID_SLEEP_TIME);
    };
    gappexit.mainthreadExit = 0;
    return NULL;
}

static void DoTemperCalcAction(DiUInt32 msg)
{
	localtempcalc = sm_temper_calc->detatemp;
	temptrigflag = 1;
}
static void ClearTemperCalcMsg(void *param)
{
	sm_temper_calc->calctop = 0;
}

static void ClearMsg(void *param)
{	   
    sm_config_update->top_flag = 0;
    sm_config_update->sweep_flag = 0;
    sm_config_update->measure_flag = 0;
    sm_config_update->trigger_flag = 0;
    sm_config_update->doorControl_flag = 0;
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

static DiInt32 innstate = 2;
extern DiInt32 lisIdleflag;
static void TrigResweepByCtrl()
{
	reCtrlSweep = 1;
	syncMana.DeviceMsgUpdate = 1;

	innstate = sm_config_sweep->SweepType;
	sm_config_sweep->SweepType = 2;
	while(lisIdleflag)
	{
		usleep(20000);
	}

	DiInt32 iBack = SetSwpInterrupt(bitdevHandle);
	if(iBack < 0)
	{
		 setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    	 ErrOutPut(REDIRECT_YES,WRSHM_YES);

		 return;
	}
	return;
}


static void RecovTrigResweepByCtrl()
{
	reCtrlSweep = 0;
	sm_config_sweep->SweepType = innstate;

	DiInt32 iBack = SetSwpInterruptStop(bitdevHandle);
	if(iBack < 0)
	{
		 setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		 ErrOutPut(REDIRECT_YES,WRSHM_YES);

		 return;
	}

    	return;
}

DiInt32 DoSweepParamLoad()
{ 
#if DEBUG_OUTPUT
	time_t timep;
	time (&timep);
	printf("%s enter param load function**********************\n",asctime(gmtime(&timep)));
#endif

	DiInt32 iBack = 0;

	TrigResweepByCtrl();

	localSweepConfig.RefLevel = sm_config_sweep->RefLevel;
        localSweepConfig.attenValue = sm_config_sweep->attenValue;
    	iBack =PreAttenCtrl(bitdevHandle,sm_config_sweep->attenValue);
	if(iBack < 0)
	{
	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
	    return iBack;
	}  

	localSweepConfig.Preamp = sm_config_sweep->Preamp;
	iBack = PreAmpliChannelCtrl(bitdevHandle,sm_config_sweep->Preamp);
	if(iBack < 0)
	{
	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
	    return iBack;
	}    
	  
	localSweepConfig.checkswitch = sm_config_sweep->checkswitch;
	iBack =SetDetectorDirectFlag(bitdevHandle,sm_config_sweep->checkswitch);
	if(iBack < 0)
	{
	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
	    return iBack;
	} 

	localSweepConfig.DetectorMode = sm_config_sweep->DetectorMode;
        iBack = SetDetectormode(bitdevHandle,localSweepConfig.DetectorMode);
        if(iBack < 0)
        {
            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
            return iBack;
        }

	iBack = InterMDFreqModeCtrl(bitdevHandle,sm_config_sweep->uIFMode);
        if(iBack < 0)
        {
	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
	    return iBack;
        }


	//Johnson 190709
	iBack = SetTriggerMode(bitdevHandle,sm_config_sweep->TriggerMode);
	if(iBack < 0)
        {
            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
            return iBack;
        }
	switch(sm_config_sweep->TriggerMode)
	{
		case 0://Free Run
		case 5://GPS
		break;
		case 1://External
			iBack = SetTriggerDirect(bitdevHandle,sm_config_sweep->TriggerDirect);
			if(iBack < 0)
		        {
		            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
    			    ErrOutPut(REDIRECT_YES,WRSHM_YES);
		            return iBack;
		        }

			iBack = SetTriggerDelayTime(bitdevHandle,sm_config_sweep->TriggerDelayTime);
			if(iBack < 0)
		        {
		            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
		            return iBack;
		        }
		break;
		case 2://Vedio
			iBack = SetTriggerDirect(bitdevHandle,sm_config_sweep->TriggerDirect);
			if(iBack < 0)
		        {
		            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
		            return iBack;
		        }

			iBack = SetTriggerDelayTime(bitdevHandle,sm_config_sweep->TriggerDelayTime);
			if(iBack < 0)
		        {
		            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
		            return iBack;
		        }

			iBack = SetVedioTriggerAmp(bitdevHandle,sm_config_sweep->VedioTriggerAmp);
			if(iBack < 0)
		        {
		            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
		            return iBack;
		        }
		break;
		case 3://Periodic time
			iBack = SetTriggerPerTime(bitdevHandle,sm_config_sweep->TriggerPerTime);
			if(iBack < 0)
		        {
		            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
		            return iBack;
		        }

			iBack = SetTriggerDelayTime(bitdevHandle,sm_config_sweep->TriggerDelayTime);
			if(iBack < 0)
		        {
		            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
		            return iBack;
		        }
		break;
		case 4://RF Burst
			iBack = SetTriggerDirect(bitdevHandle,sm_config_sweep->TriggerDirect);
			if(iBack < 0)
		        {
		            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
		            return iBack;
		        }

			iBack = SetTriggerDelayTime(bitdevHandle,sm_config_sweep->TriggerDelayTime);
			if(iBack < 0)
		        {
		            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
		            return iBack;
		        }

			iBack = SetRFBurstTriggerAmp(bitdevHandle,sm_config_sweep->RFBurstTriggerAmp);
			if(iBack < 0)
		        {
		            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
		            return iBack;
		        }
		break;
		default: break;
	}

	if(sm_config_measure->MeasureMode != 0)
	{
		iBack = SetDoorControlSwitch(bitdevHandle,0);
		if(iBack < 0)
		{
		    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
		    return iBack;
		}
	}

	if(sm_config_sweep->DrCtrlSource != -1)
	{
		iBack = SetDoorControlSourceSelect(bitdevHandle,sm_config_sweep->DrCtrlSource);
		if(iBack < 0)
	        {
	            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
	            return iBack;
	        }

		iBack = SetLevelEdgeSelect(bitdevHandle,sm_config_sweep->LvlEdgSelect);
		if(iBack < 0)
	        {
	            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
	            return iBack;
	        }

		iBack = SetLevelEdgeMode(bitdevHandle,sm_config_sweep->LvlEdgMode);
		if(iBack < 0)
	        {
	            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
	            return iBack;
	        }

		iBack = SetDoorControlSweepModeSelect(bitdevHandle,sm_config_sweep->DrCtrlSweepMode);
		if(iBack < 0)
	        {
	            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
	            return iBack;
	        }

		iBack = SetDoorControlSwitch(bitdevHandle,sm_config_sweep->DrCtrlSwitch);
		if(iBack < 0)
	        {
	            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
	            return iBack;
	        }

		if(sm_config_sweep->DrCtrlSource == 2)
		{
			iBack = SetPrdTrgSynchroSrcSelect(bitdevHandle,sm_config_sweep->PrdTrgSynchroSrc);
			if(iBack < 0)
			{
			    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
			    return iBack;
			}

			iBack = SetPrdTrgPeriod(bitdevHandle,sm_config_sweep->PrdTrgPeriod);
			if(iBack < 0)
			{
			    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
			    return iBack;
			}

			iBack = SetPrdTrgSrcDelay(bitdevHandle,sm_config_sweep->PrdTrgSrcDelay);
			if(iBack < 0)
			{
			    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
			    return iBack;
			}

			iBack = SetPrdTrigPrvntStatus(bitdevHandle,sm_config_sweep->PrdTrigPrvntStatus);
			if(iBack < 0)
			{
			    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
			    return iBack;
			}

			iBack = SetPrdTrigPrvntTimes(bitdevHandle,sm_config_sweep->PrdTrigPrvntTimes);
			if(iBack < 0)
			{
			    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
			    return iBack;
			}
		}
		else if(sm_config_sweep->DrCtrlSource == 1)
		{
			iBack = SetRFBurstTrigLevel(bitdevHandle,sm_config_sweep->RFBurstTrigLevel);
			if(iBack < 0)
			{
			    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
			    return iBack;
			}
		}
		if(sm_config_sweep->LvlEdgSelect == 0)
		{
			iBack = SetEdgTrigDely(bitdevHandle,sm_config_sweep->EdgTrigDely);
			if(iBack < 0)
			{
			    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
			    return iBack;
			}

			iBack = SetEdgTrigDoorWdth(bitdevHandle,sm_config_sweep->EdgTrigDoorWdth);
			if(iBack < 0)
			{
			    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
			    return iBack;
			}

			iBack = SetEdgTrigPrvntStatus(bitdevHandle,sm_config_sweep->EdgTrigPrvntStatus);
			if(iBack < 0)
			{
			    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
			    return iBack;
			}

			iBack = SetEdgTrigPrvntTimes(bitdevHandle,sm_config_sweep->EdgTrigPrvntTimes);
			if(iBack < 0)
			{
			    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
			    return iBack;
			}
		}
	}

	iBack = ZeroRestrainPhaseCtrl(bitdevHandle,sm_config_sweep->dZeroRestrainPhase);
	if(iBack < 0)
	{
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		ErrOutPut(REDIRECT_YES,WRSHM_YES);
		return iBack;
	}

	iBack = ZeroRestrainAttenCtrl(bitdevHandle,sm_config_sweep->dZeroRestrainAtten);
	if(iBack < 0)
	{
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		ErrOutPut(REDIRECT_YES,WRSHM_YES);
		return iBack;
	}

	//if(!sm_config_sweep->markerFreqCount) StopFreqCountWhenSetPara();
	

	RecovTrigResweepByCtrl();
	TrigAcqByParam();

	//sm_config_update->sweep_flag = IXS_RBW | IXS_VBW | IXS_SpanMode;
	//DoSweepAction(sm_config_update->sweep_flag);

#if DEBUG_OUTPUT
	time (&timep); 
	printf("%s complete param load function**********************\n",asctime(gmtime(&timep)));
#endif
	return 0;
}
void ZeroSpanSegFlagSet()
{
	DiInt32 iBack = 0;
#ifdef BIT_F238_SMART
	//*******segment flag set Johnson 191109*********
	if(sm_config_sweep->CenterFreq <= 2600000000LL) 						   iBack = SetFreqSegFlag(bitdevHandle,1);
	else if(sm_config_sweep->CenterFreq > 2600000000LL && sm_config_sweep->CenterFreq <= 7200000000LL) iBack = SetFreqSegFlag(bitdevHandle,2);
	else if(sm_config_sweep->CenterFreq > 7200000000LL) 						   iBack = SetFreqSegFlag(bitdevHandle,4);

	if(iBack < 0)
	{
	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
	    return;
	}
	//***********************************************
#endif
#ifdef BIT_F239
	//*******segment flag set Johnson 190603*********

	/*if(sm_config_sweep->CenterFreq >= 9000 && sm_config_sweep->CenterFreq <= 7200000000) 		 iBack = SetFreqSegFlag(bitdevHandle,1);
	else if(sm_config_sweep->CenterFreq >= 9000 && sm_config_sweep->CenterFreq <= 18000000000) 	 iBack = SetFreqSegFlag(bitdevHandle,2);
	else if(sm_config_sweep->CenterFreq >= 9000 && sm_config_sweep->CenterFreq <= 43000000000) 	 iBack = SetFreqSegFlag(bitdevHandle,3);
	else if(sm_config_sweep->CenterFreq >= 2800000000 && sm_config_sweep->CenterFreq <= 18000000000) iBack = SetFreqSegFlag(bitdevHandle,4);
	else if(sm_config_sweep->CenterFreq >= 2800000000 && sm_config_sweep->CenterFreq <= 43000000000) iBack = SetFreqSegFlag(bitdevHandle,5);
	else if(sm_config_sweep->CenterFreq >= 7200000000 && sm_config_sweep->CenterFreq <= 43000000000) iBack = SetFreqSegFlag(bitdevHandle,6);


	if(iBack<0)
	{
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		ErrOutPut(REDIRECT_YES,WRSHM_YES);
		return;
	}*/
	//***********************************************
#endif
#ifdef BIT_F238
	//*******segment flag set Johnson 190603*********
	if(sm_config_sweep->CenterFreq <= 7500000000LL) 						    iBack = SetFreqSegFlag(bitdevHandle,1);
	else if(sm_config_sweep->CenterFreq > 7500000000LL && sm_config_sweep->CenterFreq <= 20000000000LL) iBack = SetFreqSegFlag(bitdevHandle,2);
	else if(sm_config_sweep->CenterFreq > 20000000000LL) 					            iBack = SetFreqSegFlag(bitdevHandle,0);
	
	if(iBack < 0)
	{
	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
	    return;
	}
	//***********************************************
#endif
}

DiInt32 DoSweepParamLoadOnSemAndSpur()
{
#if DEBUG_OUTPUT
	time_t timep;
	time (&timep); 
	printf("%s enter param load function**********************\n",asctime(gmtime(&timep)));
#endif

	DiInt32 iBack = 0;

	TrigResweepByCtrl();

	//Tony 190628
	{
		gwhole = 0;
                intersource = 1;
		ifinish = 0;
		sm_config_sweep->uSweepCompleteFlag = 0;
	}

	localSweepConfig.RefLevel = sm_config_sweep->RefLevel;
        localSweepConfig.attenValue = sm_config_sweep->attenValue;
    	iBack =PreAttenCtrl(bitdevHandle,sm_config_sweep->attenValue);
	if(iBack < 0)
	{
	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
	    return iBack;
	}  

	localSweepConfig.Preamp = sm_config_sweep->Preamp;
	iBack = PreAmpliChannelCtrl(bitdevHandle,sm_config_sweep->Preamp);
	if(iBack < 0)
	{
	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
	    return iBack;
	}    
	  
	localSweepConfig.checkswitch = sm_config_sweep->checkswitch;
	iBack =SetDetectorDirectFlag(bitdevHandle,sm_config_sweep->checkswitch);
	if(iBack < 0)
	{
	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
	    return iBack;
	} 

	localSweepConfig.DetectorMode = sm_config_sweep->DetectorMode;
        iBack = SetDetectormode(bitdevHandle,localSweepConfig.DetectorMode);
        if(iBack < 0)
        {
            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
            return iBack;
        }

	// SpanMode SweepTime

        localSweepConfig.SPANMode = sm_config_sweep->SPANMode;
        iBack = SetZeroSpan(bitdevHandle,localSweepConfig.SPANMode);
        if(iBack < 0)
        {
        	setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    	ErrOutPut(REDIRECT_YES,WRSHM_YES);
                return iBack;
        }
        if(1 == localSweepConfig.SPANMode)
        {
                //clear addr,0504
                iBack = DataBufferClear(bitdevHandle,1);
                if(iBack < 0)
                {
                       setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	   	       ErrOutPut(REDIRECT_YES,WRSHM_YES);
                       return iBack;
                }
		iBack = DataBufferClear(bitdevHandle,0);
		if(iBack < 0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	   	        ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return iBack;
		}

		ZeroSpanSegFlagSet();

		//setting total sweep time when zero span mode
		sweepListinthread.sumSweeptime = sm_sweep_num->sumSweeptime * 1000;
		iBack = SetTotalSwtTimeUs(bitdevHandle,sweepListinthread.sumSweeptime);
		if(iBack < 0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	   	        ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return iBack;
		}

		//bucket time
		sweepListinthread.firBucketimeus = sm_sweep_num->firBucketimeus * 1000;
		iBack = SetFirBucketTime(bitdevHandle,sweepListinthread.firBucketimeus);
		if(iBack < 0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	   	        ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return iBack;
		}

		//local to set step and num to zero
		iBack = SetFirLoStepFreq(bitdevHandle,0,0);
		if(iBack < 0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	   	        ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return iBack;
		}
		iBack = SetSegPoint(bitdevHandle,1);
		if(iBack < 0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	   	        ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return iBack;
		}

		//setting center freq,0503
		localSweepConfig.CenterFreq = sm_config_sweep->CenterFreq;
		iBack = FirstLoFreqCtrl(bitdevHandle,localSweepConfig.CenterFreq);
		if(iBack < 0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	   	        ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return iBack;
		}


		//setting band,0504
		iBack = RfChannelChoose(bitdevHandle,localSweepConfig.CenterFreq);
		if(iBack < 0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	   	        ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return iBack;
		}
		//0725
		iBack = SetDataProcMode(bitdevHandle,sm_config_sweep->sweepMode);
		if(iBack < 0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	   	        ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return iBack;
		}
	}
	else
	{
		//0912
		//if(msg & IXS_SweepTime)
		//{
		//	sweepListinthread.firBucketimeus = sm_sweep_num->firBucketimeus * 1000;
		//	iBack = SetFirBucketTime(bitdevHandle,sweepListinthread.firBucketimeus);
		//	if(iBack < 0)
		//	{
		//		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
   	        		ErrOutPut(REDIRECT_YES,WRSHM_YES);
		//		return iBack;
		//	}
		//}
	}
       
	//RBW
	localSweepConfig.RBW = sm_config_sweep->RBW;
	iBack = SetRbw(bitdevHandle,localSweepConfig.RBW);
	if(iBack < 0)
	{
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
   	        ErrOutPut(REDIRECT_YES,WRSHM_YES);
		return iBack;
	}
	localSweepConfig.sweepMode = sm_config_sweep->sweepMode;
	//0726 steve add fft control
	if(3 == localSweepConfig.sweepMode)
	{
		iBack = SetFftValidStartNum(bitdevHandle, sm_sweep_num->startIndex);
		if(iBack < 0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	   	        ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return iBack;
		}
		iBack = SetFftValidEndNum(bitdevHandle,sm_sweep_num->stopIndex);
		if(iBack < 0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	   	        ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return iBack;
		}
		iBack = SetFftDotSwpTime(bitdevHandle,sm_sweep_num->singlefftTime);
		if(iBack < 0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	   	        ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return iBack;
		}
		iBack = SetFftBucketNum(bitdevHandle,sm_sweep_num->fftBucketnum);
		if(iBack < 0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	   	        ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return iBack;
		}
	}
	else
	{
		sweepListinthread.firBucketimeus = sm_sweep_num->firBucketimeus * 1000;
		iBack = SetFirBucketTime(bitdevHandle,sweepListinthread.firBucketimeus);
		if(iBack < 0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	   	        ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return iBack;
		}
		//0719 fir dot time
		sweepListinthread.firdottimems = sm_sweep_num->firdottimems * 1000;
		iBack = SetDotSwpTime(bitdevHandle,sweepListinthread.firdottimems);
		if(iBack < 0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	   	        ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return iBack;
		}
	}
	//0725
	iBack = SetDataProcMode(bitdevHandle,localSweepConfig.sweepMode);
	if(iBack < 0)
	{
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
   	        ErrOutPut(REDIRECT_YES,WRSHM_YES);
		return iBack;
	}
	
	//VBW
	localSweepConfig.VBW = sm_config_sweep->VBW;
	iBack = SetVbw(bitdevHandle,sm_config_sweep->VBW);
	if(iBack < 0)
	{
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
   	        ErrOutPut(REDIRECT_YES,WRSHM_YES);
		return iBack;
	}  
	
	//Span center start stop
	if(0 == localSweepConfig.sweepMode)
	{
		//steve,0504,setting bucket time
		sweepListinthread.firBucketimeus = sm_sweep_num->firBucketimeus * 1000;
		iBack = SetFirBucketTime(bitdevHandle,sweepListinthread.firBucketimeus);
		if(iBack < 0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	   	        ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return iBack;
		}
	}
	else
	{
		iBack = SetFftBucketNum(bitdevHandle,sm_sweep_num->fftBucketnum);
		if(iBack < 0)
		{
			setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	   	        ErrOutPut(REDIRECT_YES,WRSHM_YES);
			return iBack;
		}
	}

	//if(!sm_config_sweep->markerFreqCount) StopFreqCountWhenSetPara();

	RecovTrigResweepByCtrl();
	TrigAcqByParam();

 
#if DEBUG_OUTPUT
	time (&timep);
	printf("%s complete param load function**********************\n",asctime(gmtime(&timep)));
#endif
	return 0;
}

static DiInt32 StopFreqCountWhenSetPara()
{
	DiInt32 iBack = 0;
	iBack = SetFsrGetStop(bitdevHandle);
	if(iBack < 0)
	{
	    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
	    return iBack;
	}

	if(0 == localSweepConfig.sweepMode)
	{
		//*******set normal span param(midmsg non_zero_span control and localSweepConfig.SPANMode = 0)
		localSweepConfig.SPANMode = 0;
		iBack = SetZeroSpan(bitdevHandle,localSweepConfig.SPANMode);
		if(iBack < 0)
		{
		    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
		    return iBack;
		}

		if(localSweepConfig.sweepMode == 3)
		{
			iBack = SetRbw(bitdevHandle,sm_config_sweep->RBW);
			if(iBack < 0)
			{
			    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
			    ErrOutPut(REDIRECT_YES,WRSHM_YES);
			    return iBack;
			}

			iBack = SetVbw(bitdevHandle,sm_config_sweep->VBW);
			if(iBack < 0)
			{
			    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
			    ErrOutPut(REDIRECT_YES,WRSHM_YES);
			    return iBack;
			}

			iBack = SetFftValidStartNum(bitdevHandle, sm_sweep_num->startIndex);
			if(iBack < 0)
			{
			    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
			    ErrOutPut(REDIRECT_YES,WRSHM_YES);
			    return iBack;
			}

			iBack = SetFftValidEndNum(bitdevHandle,sm_sweep_num->stopIndex);
			if(iBack < 0)
			{
			    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
			    ErrOutPut(REDIRECT_YES,WRSHM_YES);
			    return iBack;
			}

			iBack = SetFftDotSwpTime(bitdevHandle,sm_sweep_num->singlefftTime);
			if(iBack < 0)
			{
			    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
			    ErrOutPut(REDIRECT_YES,WRSHM_YES);
			    return iBack;
			}

			iBack = SetFftBucketNum(bitdevHandle,sm_sweep_num->fftBucketnum);
			if(iBack < 0)
			{
			    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
			    ErrOutPut(REDIRECT_YES,WRSHM_YES);
			    return iBack;
			}

			iBack = SetDataProcMode(bitdevHandle,localSweepConfig.sweepMode);
			if(iBack < 0)
			{
			    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
			    ErrOutPut(REDIRECT_YES,WRSHM_YES);
			    return iBack;
			}
		}
		else 
		{
			iBack = SetFirBucketTime(bitdevHandle,sm_sweep_num->firBucketimeus * 1000);
			if(iBack < 0)
			{
			    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
			    ErrOutPut(REDIRECT_YES,WRSHM_YES);
			    return iBack;
			}
		}
		//**************************************
		bFreqCountSpanMode = 1;
		//Johnson 191119
		bFreqCountDataGetComplete = 0;
		bMarkerFreqCountInterrupt = 0;
		bFreqCountSweepComplete = 0;

		usleep(200000);
	}
}

static DiInt32 DoSweepAction(DiUInt32 msg)
{	
     DiInt32 iBack = 0;

    if(msg & 0x80000000)
    {
	DoTriggerAction(msg & 0x0fffffff);
    	DoDoorControlAction(msg & 0x0fffffff);

	return 0;
    }

#if FREQ_COUNT
     DiInt32 tmpMarkerFreqCount = 0;

    if(msg & IXS_MARKERFRECOUNT)
    {
	TrigResweepByCtrl();

	if(!sm_config_sweep->markerFreqCount) StopFreqCountWhenSetPara();

	RecovTrigResweepByCtrl();
    }

   /*if(!(msg & IXS_MARKERFRECOUNT) && sm_config_sweep->markerFreqCount)
    {
	TrigResweepByCtrl();

	tmpMarkerFreqCount = 1;
	sm_config_sweep->markerFreqCount = 0;
	sm_config_sweep->bSendFreqCountStopCmd = 1;
	
	if(!sm_config_sweep->markerFreqCount) StopFreqCountWhenSetPara();

	RecovTrigResweepByCtrl();

	while(1)
	{
		if(!sm_config_sweep->bSendFreqCountStopCmd) break;
		usleep(100000);
	}
    }*/
#endif

     if(msg & IXS_SA_IFmode)//Johnson 190425
     {
	    TrigResweepByCtrl();

	    iBack = InterMDFreqModeCtrl(bitdevHandle,sm_config_sweep->uIFMode);
	    if(iBack < 0)
            {
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
   	        ErrOutPut(REDIRECT_YES,WRSHM_YES);
		return iBack;
            }

	    RecovTrigResweepByCtrl();
     }
     if(msg & IXS_PARALOAD)//Johnson 190412
     {
	    if(3 == sm_config_measure->MeasureMode || 6 == sm_config_measure->MeasureMode )
	    {
		    DoSweepParamLoadOnSemAndSpur();
	    }
	    else
	    {
		    DoSweepParamLoad();
		    msg = IXS_RBW | IXS_VBW | IXS_SpanMode | IXS_SweepTime;
     	    }      
     }      

     if(msg & IXS_SA_ZeroRestrain)//Johnson 190422
     {
	    TrigResweepByCtrl();

	    iBack = ZeroRestrainPhaseCtrl(bitdevHandle,sm_config_sweep->dZeroRestrainPhase);
	    if(iBack < 0)
            {
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
   	        ErrOutPut(REDIRECT_YES,WRSHM_YES);
		return iBack;
            }

	    iBack = ZeroRestrainAttenCtrl(bitdevHandle,sm_config_sweep->dZeroRestrainAtten);
	    if(iBack < 0)
            {
		setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
   	        ErrOutPut(REDIRECT_YES,WRSHM_YES);
		return iBack;
            }

	    RecovTrigResweepByCtrl();
     }


    if(msg & IXS_Refoffset)
        {
            //TrigResweepByParam();
	    TrigResweepByCtrl();
	    RecovTrigResweepByCtrl();
        }

    if(msg & IXS_SpanMode || msg & IXS_SweepTime)
        {

	TrigResweepByCtrl();
	time_t timep;
	time (&timep); 

            //0502
            //means to change sweep ctrl
            localSweepConfig.SPANMode = sm_config_sweep->SPANMode;
            iBack = SetZeroSpan(bitdevHandle,localSweepConfig.SPANMode);
            if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
   	            ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }
            if(1 == localSweepConfig.SPANMode)
                {
                    //clear addr,0504
                    iBack = DataBufferClear(bitdevHandle,1);
                    if(iBack < 0)
                        {
                            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
   	        	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                            return iBack;
                        }
                    iBack = DataBufferClear(bitdevHandle,0);
                    if(iBack < 0)
                        {
                            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
   	        	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                            return iBack;
                        }

		    ZeroSpanSegFlagSet();

                    //setting total sweep time when zero span mode
                    sweepListinthread.sumSweeptime = sm_sweep_num->sumSweeptime * 1000;
                    iBack = SetTotalSwtTimeUs(bitdevHandle,sweepListinthread.sumSweeptime);
                    if(iBack < 0)
                        {
                            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
   	        	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                            return iBack;
                        }

                    //bucket time
                    sweepListinthread.firBucketimeus = sm_sweep_num->firBucketimeus * 1000;
                    iBack = SetFirBucketTime(bitdevHandle,sweepListinthread.firBucketimeus);
                    if(iBack < 0)
                        {
                            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
   	        	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                            return iBack;
                        }

                    //local to set step and num to zero
                    iBack = SetFirLoStepFreq(bitdevHandle,0,0);
                    if(iBack < 0)
                        {
                            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
   	        	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                            return iBack;
                        }
                    iBack = SetSegPoint(bitdevHandle,1);
                    if(iBack < 0)
                        {
                            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
   	        	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                            return iBack;
                        }

                    //setting center freq,0503
                    localSweepConfig.CenterFreq = sm_config_sweep->CenterFreq;
                    iBack = FirstLoFreqCtrl(bitdevHandle,localSweepConfig.CenterFreq);
                    if(iBack < 0)
                        {
                            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
   	        	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                            return iBack;
                        }


                    //setting band,0504
                    iBack = RfChannelChoose(bitdevHandle,localSweepConfig.CenterFreq);
                    if(iBack < 0)
                        {
                            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
   	        	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                            return iBack;
                        }
                    //0725
                    iBack = SetDataProcMode(bitdevHandle,sm_config_sweep->sweepMode);
                    if(iBack < 0)
                        {
                            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
   	        	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                            return iBack;
                        }
                }
            else
                {
                    //0912
                    if(msg & IXS_SweepTime)
                        {
                            sweepListinthread.firBucketimeus = sm_sweep_num->firBucketimeus * 1000;
                            iBack = SetFirBucketTime(bitdevHandle,sweepListinthread.firBucketimeus);
                            if(iBack < 0)
                                {
                                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
   	        	    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                                    return iBack;
                                }
                        }
                }
 	    RecovTrigResweepByCtrl();
            //0503
            TrigAcqByParam();
        }

    if(msg & IXS_RBW || msg & IXS_RBWAuto || msg & IXS_VBW || msg & IXS_VBWAuto)
        {
	time_t timep;
	time (&timep); 

#if 0
	    if(sm_config_sweep->ischangeRbwitself)
            {
		    //if 0,means trig is done by freq ctrl
		    //TrigResweepByParam();
	            TrigResweepByCtrl();
            }
#else 

            TrigResweepByCtrl();
#endif

            if(msg & IXS_RBW || msg & IXS_RBWAuto)
                {
                    localSweepConfig.RBW = sm_config_sweep->RBW;
                    iBack = SetRbw(bitdevHandle,localSweepConfig.RBW);
                    if(iBack < 0)
                        {
                            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
   	        	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                            return iBack;
                        }

                    localSweepConfig.sweepMode = sm_config_sweep->sweepMode;
                    //0726 steve add fft control
                    if(3 == localSweepConfig.sweepMode)
                        {
                            iBack = SetFftValidStartNum(bitdevHandle, sm_sweep_num->startIndex);
                            if(iBack < 0)
                                {
                                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
   	        	    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                                    return iBack;
                                }
                            iBack = SetFftValidEndNum(bitdevHandle,sm_sweep_num->stopIndex);
                            if(iBack < 0)
                                {
                                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
   	        	    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                                    return iBack;
                                }
                            iBack = SetFftDotSwpTime(bitdevHandle,sm_sweep_num->singlefftTime);
                            if(iBack < 0)
                                {
                                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
   	        	    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                                    return iBack;
                                }
                            iBack = SetFftBucketNum(bitdevHandle,sm_sweep_num->fftBucketnum);
                            if(iBack < 0)
                                {
                                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
   	        	    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                                    return iBack;
                                }
#if DEBUG_OUTPUT
                            printf("fft start index %d\n",sm_sweep_num->startIndex);
                            printf("fft stop index %d\n",sm_sweep_num->stopIndex);
                            printf("fft dot time ms %lf\n",sm_sweep_num->singlefftTime);
                            printf("fft bucket num %lf\n",sm_sweep_num->fftBucketnum);
#endif
                        }
                    else
                        {
                            sweepListinthread.firBucketimeus = sm_sweep_num->firBucketimeus * 1000;
                            iBack = SetFirBucketTime(bitdevHandle,sweepListinthread.firBucketimeus);
                            if(iBack < 0)
                                {
                                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
   	        	    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                                    return iBack;
                                }

                            //0719 fir dot time
                            sweepListinthread.firdottimems = sm_sweep_num->firdottimems * 1000;
                            iBack = SetDotSwpTime(bitdevHandle,sweepListinthread.firdottimems);
                            if(iBack < 0)
                                {
                                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
   	        	    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                                    return iBack;
                                }
                        }
                    //0725
                    iBack = SetDataProcMode(bitdevHandle,localSweepConfig.sweepMode);
                    if(iBack < 0)
                        {
                            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
        	    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                            return iBack;
                        }
                }
            //0718
            if(msg & IXS_VBW || msg & IXS_VBWAuto)
                {
                    localSweepConfig.VBW = sm_config_sweep->VBW;
                    iBack = SetVbw(bitdevHandle,sm_config_sweep->VBW);
                    if(iBack < 0)
                        {
                            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
        	    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                            return iBack;
                        }
                }
#if 0
	   if(sm_config_sweep->ischangeRbwitself)
            {
		    //if 0,means trig is done by freq ctrl
		    RecovTrigResweepByCtrl();
            }
#else
	   	RecovTrigResweepByCtrl();
	   	TrigAcqByParam();
#endif
        }

    if(msg & IXS_CenterFreq || msg & IXS_SpanFreq || msg & IXS_StartFreq || msg & IXS_StopFreq)
        {
	    TrigResweepByCtrl();
            //0726
            if(0 == localSweepConfig.sweepMode)
                {
                    //steve,0504,setting bucket time
                    sweepListinthread.firBucketimeus = sm_sweep_num->firBucketimeus * 1000;
                    iBack = SetFirBucketTime(bitdevHandle,sweepListinthread.firBucketimeus);
                    if(iBack < 0)
                        {
                            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
        	    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                            return iBack;
                        }
                }
            //0810
            else
                {
                    iBack = SetFftBucketNum(bitdevHandle,sm_sweep_num->fftBucketnum);
                    if(iBack < 0)
                        {
                            setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
        	    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                            return iBack;
                        }
                }
            TrigAcqByParam();
	    RecovTrigResweepByCtrl();
        }

    //0829
    if(msg & IXS_CheckAciton)
        {
	    TrigResweepByCtrl();
            localSweepConfig.checkswitch = sm_config_sweep->checkswitch;
            iBack = SetDetectorDirectFlag(bitdevHandle,localSweepConfig.checkswitch);
            if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }
#if DEBUG_OUTPUT
	    printf("checkSwitch %u\n",localSweepConfig.checkswitch);
#endif
            //TrigResweepByParam();
	    RecovTrigResweepByCtrl();
        }

    if(msg & IXS_TracePoint)
        {
	    TrigResweepByCtrl();

            localSweepConfig.TracePoint = sm_config_sweep->TracePoint;
            iBack = SetDisplayNum(bitdevHandle,localSweepConfig.TracePoint);
            if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }
            TrigAcqByParam();
	    RecovTrigResweepByCtrl();
        }

    if(msg & IXS_DetectorMode)
        {
	    TrigResweepByCtrl();

            localSweepConfig.DetectorMode = sm_config_sweep->DetectorMode;
            iBack = SetDetectormode(bitdevHandle,localSweepConfig.DetectorMode);
            if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }
	    RecovTrigResweepByCtrl();
        }

    if(msg & IXS_Preamp)
        {
	    TrigResweepByCtrl();
            //0503

            localSweepConfig.Preamp = sm_config_sweep->Preamp;
            iBack = PreAmpliChannelCtrl(bitdevHandle,localSweepConfig.Preamp);
            if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }
	    RecovTrigResweepByCtrl();
            TrigAcqByParam();                    
        }

    if(msg & IXS_RefLevel || msg & IXS_AttenSelect)
        { 
            TrigResweepByCtrl();

            localSweepConfig.RefLevel = sm_config_sweep->RefLevel;
            localSweepConfig.attenValue = sm_config_sweep->attenValue;
            iBack = PreAttenCtrl(bitdevHandle,localSweepConfig.attenValue);
            if(iBack < 0)
            {
		    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
	    	    ErrOutPut(REDIRECT_YES,WRSHM_YES);
		    return iBack;
            }

	   RecovTrigResweepByCtrl();
           TrigAcqByParam();           
        }

    if(msg & IXS_DOTSWEEPTIME)
    {
	TrigResweepByCtrl();

    	if(0 == localSweepConfig.sweepMode)//fir
        {
	    sweepListinthread.firdottimems = sm_sweep_num->firdottimems * 1000;
            iBack = SetDotSwpTime(bitdevHandle,sweepListinthread.firdottimems);
            if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }

            sweepListinthread.firBucketimeus = sm_sweep_num->firBucketimeus * 1000;
            iBack = SetFirBucketTime(bitdevHandle,sweepListinthread.firBucketimeus);
            if(iBack < 0)
	    {
		    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
		    return iBack;
	    }
        }
    	else//fft
        {
	    iBack = SetFftDotSwpTime(bitdevHandle,sm_sweep_num->singlefftTime);
            if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }

            iBack = SetFftBucketNum(bitdevHandle,sm_sweep_num->fftBucketnum);
            if(iBack < 0)
            {
		    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
		    return iBack;
            }
        }

    	TrigAcqByParam();
    	RecovTrigResweepByCtrl();
    }

    if(msg & IXS_ZeroSpanTime)
        {
        }
    if(msg & IXS_ZeroSpanMode)
        {
        }
    if(msg & IXS_ImageRejection)
        {
        }

    if(!(msg & IXS_MARKERFRECOUNT) && tmpMarkerFreqCount)
    {
#if FREQ_COUNT
	sm_config_sweep->markerFreqCount = 1;
#endif
    }

    return 0;
}

static DiInt32 DoMeasureAction(DiUInt32 msg)
{
    if(msg & IXS_MeasureMode)
        {
        }
    else if(msg & IXS_ChannelBW)
        {
        }
    else if(msg & IXS_ChannelSpacing)
        {
        }
    else if(msg & IXS_DemodFreq)
        {
        }
    else if(msg & IXS_DemodIFBW)
        {
        }
    else if(msg & IXS_DemodMode)
        {
        }
    else if(msg & IXS_PSFreq)
        {
        }
    else
        {
        }
    return 0;
}
extern PSWEEP_DATA sm_sweep_data;
static DiInt32 DoTriggerAction(DiUInt32 msg)
{
	DiInt32 iBack = 0;
	if(msg & IXS_TriggerMode)
	{
		TrigResweepByCtrl();
		iBack = SetTriggerMode(bitdevHandle,sm_config_sweep->TriggerMode);
		if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }

	    	RecovTrigResweepByCtrl();
	}
	if(msg & IXS_TriggerDirect)
	{
		TrigResweepByCtrl();
		iBack = SetTriggerDirect(bitdevHandle,sm_config_sweep->TriggerDirect);
		if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }

	    	RecovTrigResweepByCtrl();
	}
	if(msg & IXS_TriggerDelayTime)
	{
		TrigResweepByCtrl();
		iBack = SetTriggerDelayTime(bitdevHandle,sm_config_sweep->TriggerDelayTime);
		if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }

	    	RecovTrigResweepByCtrl();
	}
	if(msg & IXS_TriggerPerTime)
	{
		TrigResweepByCtrl();
		iBack = SetTriggerPerTime(bitdevHandle,sm_config_sweep->TriggerPerTime);
		if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }

	    	RecovTrigResweepByCtrl();
		
	}
	if(msg & IXS_VedioTriggerAmp)
	{
		TrigResweepByCtrl();
		iBack = SetVedioTriggerAmp(bitdevHandle,sm_config_sweep->VedioTriggerAmp);
		if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }

	    	RecovTrigResweepByCtrl();
	}
	if(msg & IXS_RFBurstTriggerAmp)
	{
		TrigResweepByCtrl();
		iBack = SetRFBurstTriggerAmp(bitdevHandle,sm_config_sweep->RFBurstTriggerAmp);
		if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }

	    	RecovTrigResweepByCtrl();
	}
}
static DiInt32 DoDoorControlAction(DiUInt32 msg)
{
	DiInt32 iBack = 0;
	if(msg & IXS_DrCtrlSource)
	{
		TrigResweepByCtrl();
		
		iBack = SetDoorControlSourceSelect(bitdevHandle,sm_config_sweep->DrCtrlSource);
		if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }

	    	RecovTrigResweepByCtrl();
	}
	if(msg & IXS_LvlEdgModeSelect)
	{
		TrigResweepByCtrl();
		iBack = SetLevelEdgeSelect(bitdevHandle,sm_config_sweep->LvlEdgSelect);
		if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }

	    	RecovTrigResweepByCtrl();
	}
	if(msg & IXS_LvlEdgValueSelect)
	{
		TrigResweepByCtrl();
		iBack = SetLevelEdgeMode(bitdevHandle,sm_config_sweep->LvlEdgMode);
		if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }

	    	RecovTrigResweepByCtrl();
	}
	if(msg & IXS_DrCtrlSweepMode)
	{
		TrigResweepByCtrl();
		iBack = SetDoorControlSweepModeSelect(bitdevHandle,sm_config_sweep->DrCtrlSweepMode);
		if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }

	    	RecovTrigResweepByCtrl();
	}
	if(msg & IXS_PrdTrigSycSrcSelect)
	{
		TrigResweepByCtrl();
		iBack = SetPrdTrgSynchroSrcSelect(bitdevHandle,sm_config_sweep->PrdTrgSynchroSrc);
		if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }

	    	RecovTrigResweepByCtrl();
	}
	if(msg & IXS_DrCtrlSweepSwitch)
	{
		TrigResweepByCtrl();
		iBack = SetDoorControlSwitch(bitdevHandle,sm_config_sweep->DrCtrlSwitch);
		if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }

	    	RecovTrigResweepByCtrl();
	}
	if(msg & IXS_EdgTrigDelay)
	{
		TrigResweepByCtrl();
		iBack = SetEdgTrigDely(bitdevHandle,sm_config_sweep->EdgTrigDely);
		if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }

	    	RecovTrigResweepByCtrl();
	}
	if(msg & IXS_EdgTrigDrWidth)
	{
		TrigResweepByCtrl();
		iBack = SetEdgTrigDoorWdth(bitdevHandle,sm_config_sweep->EdgTrigDoorWdth);
		if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }

	    	RecovTrigResweepByCtrl();
	}
	if(msg & IXS_EdgTrigPrvtSwitch)
	{
		TrigResweepByCtrl();
		iBack = SetEdgTrigPrvntStatus(bitdevHandle,sm_config_sweep->EdgTrigPrvntStatus);
		if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }

	    	RecovTrigResweepByCtrl();
	}
	if(msg & IXS_EdgTrigPrvtValue)
	{
		TrigResweepByCtrl();
		iBack = SetEdgTrigPrvntTimes(bitdevHandle,sm_config_sweep->EdgTrigPrvntTimes);
		if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }

	    	RecovTrigResweepByCtrl();
	}
	if(msg & IXS_PrdTrigPeriod)
	{
		TrigResweepByCtrl();
		iBack = SetPrdTrgPeriod(bitdevHandle,sm_config_sweep->PrdTrgPeriod);
		if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }

	    	RecovTrigResweepByCtrl();
	}
	if(msg & IXS_PrdTrigSycSrcDelay)
	{
		TrigResweepByCtrl();
		iBack = SetPrdTrgSrcDelay(bitdevHandle,sm_config_sweep->PrdTrgSrcDelay);
		if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }

	    	RecovTrigResweepByCtrl();
	}
	if(msg & IXS_PrdTrigPrvtSwitch)
	{
		TrigResweepByCtrl();
		iBack = SetPrdTrigPrvntStatus(bitdevHandle,sm_config_sweep->PrdTrigPrvntStatus);
		if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }

	    	RecovTrigResweepByCtrl();
	}
	if(msg & IXS_PrdTrigPrvtValue)
	{
		TrigResweepByCtrl();
		iBack = SetPrdTrigPrvntTimes(bitdevHandle,sm_config_sweep->PrdTrigPrvntTimes);
		if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }

	    	RecovTrigResweepByCtrl();
	}

	if(msg & IXS_RFBurst_TrigLevel)
	{
		TrigResweepByCtrl();
		iBack = SetRFBurstTrigLevel(bitdevHandle,sm_config_sweep->RFBurstTrigLevel);
		if(iBack < 0)
                {
                    setNoticePara(WARNING_EXCEPTION_MESSAGE,EXECUTE_ERR_EXCEPTION,iBack);
		    ErrOutPut(REDIRECT_YES,WRSHM_YES);
                    return iBack;
                }

	    	RecovTrigResweepByCtrl();
	}
}

