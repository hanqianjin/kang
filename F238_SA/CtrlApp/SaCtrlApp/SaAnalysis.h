//==============================================================================
//
// Title:		SaAnalysis.h
// Purpose:		A short description of the DiInt32erface.
//
// Created on:	2018/1/20 at 11:34:57 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __SaAnalysis_H__
#define __SaAnalysis_H__

#ifdef __cplusplus
extern "C" {
#endif

//==============================================================================
// Include files
#include <sys/ipc.h>
#include <sys/sem.h>
#include "DiIoCtrl.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions
//----------------upon part will locate in the gui app---------------------------------------
/*
purpose:listen the sweep segment state,used in the thread
func:ListenAndDownSweepParamFunc
param:<in>param:the thread param pointer      
return:NULL
 */
void* ListenAndDownSweepParamFunc(void *param);

/*
purpose:acq the data from hardware,used in the thread
func:AcqDataFunc
param:<in>param:the thread param pointer      
return:NULL
 */
void* AcqDataFunc(void *param);

DiInt32 GetCalcDataWhenPreAmpOff(DiReal64 startfreq,DiReal64 stopfreq,DiInt32 datanum,DiReal64 refl,DiInt32 autoflag,DiReal64 manatten,DiReal64* calcresult);
DiInt32 GetCalcDataWhenPreAmpOn(DiReal64 startfreq,DiReal64 stopfreq,DiInt32 datanum,DiReal64 refl,DiInt32 autoflag,DiReal64 manatten,DiReal64* calcresult);

DiInt32 GetCalcDataWhenPreAmpOffZeroSpan(DiReal64 freq,DiInt32 datanum,DiReal64 refl,DiInt32 autoflag,DiReal64 manatten,DiReal64* calcresult);
DiInt32 GetCalcDataWhenPreAmpOnZeroSpan(DiReal64 freq,DiInt32 datanum,DiReal64 refl,DiInt32 autoflag,DiReal64 manatten,DiReal64* calcresult);
DiInt32 GetTemperCalcDatas(DiReal64 startfreq,DiReal64 stopfreq,DiInt32 datanum,DiReal64 tempercoef,DiPReal64 calcresult,DiInt32 zeroflag);

DiInt32 LoadCalibrateDatas();
DiInt32 FreeMemBuffer();

void GetCtrlInHand(DiInt32 handle);
void ReleaseCtrlInHand(DiInt32 handle);

void SetSegFlagByFreq(DiUInt32 iSweepSegIndex);

#ifdef __cplusplus
}
#endif

#endif  /* ndef __SaAnalysis_H__ */
