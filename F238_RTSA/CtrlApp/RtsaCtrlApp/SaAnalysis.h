//==============================================================================
//
// Title:		SaAnalysis.h
// Purpose:		A short description of the interface.
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
void* AcqDataFuncSimu(void *param);
void* AcqDataFuncPhy(void *param);

DiInt32 GetCalcDataWhenPreAmpOff(double startfreq,double stopfreq,int datanum,int autoflag,double manatten,double* calcresult);
DiInt32 GetCalcDataWhenPreAmpOn(double startfreq,double stopfreq,int datanum,int autoflag,double manatten,double* calcresult);
DiInt32 GetSpanCalcDatasPreOff(DiReal64 freqHz,DiReal64 fspan,DiInt32 datanum,DiInt32 atflag,DiReal64 atten,DiPReal32 calcresult);
DiInt32 GetSpanCalcDatasPreOn(DiReal64 freqHz,DiReal64 fspan,DiInt32 datanum,DiInt32 atflag,DiReal64 atten,DiPReal32 calcresult);
//DiInt32 GetCalcDataWhenPreAmpOffZeroSpan(double freq,int datanum,int autoflag,double manatten,double* calcresult);
//DiInt32 GetCalcDataWhenPreAmpOnZeroSpan(double freq,int datanum,int autoflag,double manatten,double* calcresult);
DiInt32 GetCalcDataWhenPreAmpOffZeroSpan(DiReal64 freq,DiInt32 datanum,DiReal64 refl,DiInt32 autoflag,DiReal64 manatten,DiReal64* calcresult);
DiInt32 GetCalcDataWhenPreAmpOnZeroSpan(DiReal64 freq,DiInt32 datanum,DiReal64 refl,DiInt32 autoflag,DiReal64 manatten,DiReal64* calcresult);
DiInt32 GetTemperCalcDatas(DiReal64 centerfreq,DiInt32 datanum,DiReal64 tempercoef,DiPReal64 calcresult,DiInt32 zeroflag);


DiInt32 LoadCalibrateDatas();
DiInt32 FreeMemBuffer();
#ifdef __cplusplus
}
#endif

#endif  /* ndef __SaAnalysis_H__ */
