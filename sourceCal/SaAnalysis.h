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

int ConfigureRefLevel(double refLevel,int preAmpState,int attenAuto,double attenvalue,double* produceCalcdata,int traceNum);
/*
purpose:set first lo freq
func:SetFirstLoFreq
param:<in>devHandle:dev's ctrl handle from ini
      <out>loFreq:the freq of first lo Hz
return:>=0 is ok
 */
DiInt32 SetFirstLoFreq(DiSession devHandle,DiReal64 loFreq);

//
//inner driver 
DiInt32 SetFirLoStepFreq(DiSession devHandle,DiUInt32 lowbit,DiUInt32 highbit);
DiInt32 SetFirLoStaytime(DiSession devHandle,DiUInt32 fsnum);
DiInt32 SetSegPoint(DiSession devHandle,DiUInt32 pointsnum);

DiInt32 SetRbw(DiSession devHandle,DiReal64 rbwValue);
DiInt32 SetVbw(DiSession devHandle,DiReal64 vbwValue);
DiInt32 SetDetectormode(DiSession devHandle,DiUInt32 checkMode);
DiInt32 SetdataprocMode(DiSession devHandle,DiUInt32 dataproMode);
DiInt32 SetzeroSpan(DiSession devHandle,DiUInt32 zeroSpan);
DiInt32 SetdotswpTime(DiSession devHandle,DiUInt32 dotswpTime);
DiInt32 SettotalswpTimeLow(DiSession devHandle,DiUInt32 totalswptimeLow);
DiInt32 SettotalswpTimeHight(DiSession devHandle,DiUInt32 totalswptimeHight);
DiInt32 SetdisplayNum(DiSession devHandle,DiUInt32 displayNum);
DiInt32 SetdataaddrClr(DiSession devHandle,DiUInt32 dataaddrClr);
DiInt32 SetfftbucketNum(DiSession devHandle,DiUInt32 fftbucketNum);
DiInt32 SetdetectorFlag(DiSession devHandle,DiUInt32 detectorFlag);
DiInt32 SetaudioTime(DiSession devHandle,DiUInt32 audiotime);
DiInt32 SetaudioVolume(DiSession devHandle,DiUInt32 audioVolume);
DiInt32 SetaudioType(DiSession devHandle,DiUInt32 audioType);
DiInt32 SetaudioEn(DiSession devHandle,DiUInt32 audioEn);
DiInt32 SetfftcalNum(DiSession devHandle,DiUInt32 fftcalNum);
DiInt32 SetfftDirection(DiSession devHandle,DiUInt32 fftDirection);
DiInt32 SetfftvalidstartNum(DiSession devHandle,DiUInt32 fftvalidstartNum);
DiInt32 SetfftvalidendNum(DiSession devHandle,DiUInt32 fftvalidendNum);
DiInt32 SetfftdotswpTime(DiSession devHandle,DiUInt32 fftdotswpTime);
DiInt32 SetbuckettrigTime(DiSession devHandle,DiUInt32 buckettrigTime);
DiInt32 SetrbwvbwdelayTime(DiSession devHandle,DiUInt32 rbwvbwdelayTime);
DiInt32 SettrigType(DiSession devHandle,DiUInt32 trigType);
DiInt32 SettrigDirect(DiSession devHandle,DiUInt32 trigDirect);
DiInt32 SettrigTime(DiSession devHandle,DiUInt32 trigTime);
DiInt32 SettrigAmp(DiSession devHandle,DiUInt32 trigAmp);
DiInt32 SetswpStop(DiSession devHandle);
DiInt32 SetswpRun(DiSession devHandle);
DiInt32 SetCheckSegNum(DiSession devHandle,DiUInt32 segNum);
#ifdef __cplusplus
}
#endif

#endif  /* ndef __SaAnalysis_H__ */
