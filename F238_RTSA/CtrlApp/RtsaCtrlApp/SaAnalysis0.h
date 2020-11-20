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
/*
purpose: config start and stop freq
func:DiInst_ConfigureFrequencyStartStop
param:<in>devHandle:dev's ctrl handle from ini
      <in>startFrequency:start freq in Hz
      <in>stopFrequency:stop freq in Hz
	  value range:9kHz~32GHz
return:>=0 is ok
*/
DiInt32 DiInst_ConfigureFrequencyStartStop (DiSession devHandle,DiReal64 startFrequency,DiReal64 stopFrequency);

/*
purpose: config center and span freq
func:DiInst_ConfigureFrequencyCenterSpan
param:<in>devHandle:dev's ctrl handle from ini
	  <in>centerFrequency:center freq in Hz
      <in>span:span freq in Hz
	  value range:9kHz~32GHz
return:>=0 is ok
*/
DiInt32 DiInst_ConfigureFrequencyCenterSpan (DiSession devHandle,DiReal64 centerFrequency,DiReal64 span);
  
/*
purpose: config sweep ctrl
func:DiInst_ConfigureSweepCoupling
param:<in>devHandle:dev's ctrl handle from ini
	  <in>resolutionBandwidthAuto: 1 auto;0 man
	  <in>resolutionBandwidth:5MHz~1Hz
	  <in>videoBandwidthAuto:1 auto;0 man
	  <in>videoBandwidth:3MHz~1Hz
	  <in>vbwtorbwAuto:1 auto;0 man
	  <in>vbwtorbwValue:>zero
return:>=0 is ok
*/
DiInt32 DiInst_ConfigureSweepCoupling (DiSession devHandle,DiUInt32 resolutionBandwidthAuto,DiReal64 resolutionBandwidth,DiUInt32 videoBandwidthAuto,DiReal64 videoBandwidth,DiUInt32 vbwtorbwAuto,DiReal64 vbwtorbwValue);

/*
purpose: config acq ctrl
func:DiInst_ConfigureAcquisition
param:<in>devHandle:dev's ctrl handle from ini
	  <in>sweepMode:continue or single or times
	  <in>numberOfTraces:show points
	  <in>detectorType:check mode
return:>=0 is ok
*/
DiInt32 DiInst_ConfigureAcquisition (DiSession devHandle,DiInt32 sweepMode,DiInt32 numberOfTraces,DiInt32 detectorType);

/*
purpose: config level and atten ctrl
func:DiInst_ConfigureLevel
param:<in>devHandle:dev's ctrl handle from ini  
	  <in>amplitudeUnits:
      <in>inputImpedance:
      <in>referenceLevel:
      <in>referenceLevelOffset:
      <in>attenuationAuto:
      <in>attenuation: 
return:>=0 is ok
*/
DiInt32 DiInst_ConfigureLevel (DiSession devHandle,DiInt32 amplitudeUnits,DiReal64 inputImpedance,DiReal64 referenceLevel,DiReal64 referenceLevelOffset,DiBoolean attenuationAuto,DiReal64 attenuation);
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
#ifdef __cplusplus
}
#endif

#endif  /* ndef __SaAnalysis_H__ */
