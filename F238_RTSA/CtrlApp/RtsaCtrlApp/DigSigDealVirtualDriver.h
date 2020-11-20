#ifndef __DigSigDealVirtualDriver_H__
#define __DigSigDealVirtualDriver_H__

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
typedef struct
{
	DiReal32 SampleRate;					//fs speed
	DiReal32 AcqTime_Min;				// min acq time for current span
	DiInt32   fft_total_num_valid;
	DiInt32   fft_bucket_num;
	DiInt32   fft_valid_start;
	DiInt32   fft_valid_stop;
	DiReal32   fft_mean_factor1;
	DiReal32   fft_mean_factor2;
} Rtsa_fft_Param;
//==============================================================================
// External variables

//==============================================================================
// Global functions
/*
purpose:set last sweep band
func:SetLastBandCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <int>flag:0 not last,1 last
return:>=0 is ok
 */
//DiInt32 SetLastBandCtrl(DiSession devHandle,DiUInt32 flag);


/*
purpose:per seg sum nums
func:SetSegPoint
param:<in>devHandle:dev's ctrl handle from ini
      <in>pointsnum:the nums of per seg      
return:>=0 is ok
 */
DiInt32 SetSegPoint(DiSession devHandle,DiUInt32 pointsnum);

/*
purpose:set rbw
func:SetRbw
param:<in>devHandle:dev's ctrl handle from ini
      <in>rbwValue:the rbw value    
return:>=0 is ok
 */
DiInt32 SetRbw(DiSession devHandle,DiReal64 rbwValue);

/*
purpose:set vbw
func:SetVbw
param:<in>devHandle:dev's ctrl handle from ini
      <in>vbwValue:the rbw value    
return:>=0 is ok
 */
//DiInt32 SetVbw(DiSession devHandle,DiReal64 vbwValue);

/*
purpose:set detector mode
func:SetDetectormode
param:<in>devHandle:dev's ctrl handle from ini
      <in>checkMode:check mode   
return:>=0 is ok
 */
//DiInt32 SetDetectormode(DiSession devHandle,DiUInt32 checkMode);

/*
purpose:set data proc mode
func:SetDataProcMode
param:<in>devHandle:dev's ctrl handle from ini
      <in>dataproMode:data proc mode   
return:>=0 is ok
 */
//DiInt32 SetDataProcMode(DiSession devHandle,DiUInt32 dataproMode);

/*
purpose:set zero span
func:SetZeroSpan
param:<in>devHandle:dev's ctrl handle from ini
      <in>zeroSpan:zero span mode   
return:>=0 is ok
 */
DiInt32 SetZeroSpan(DiSession devHandle,DiUInt32 zeroSpan);

/*
purpose:set fft one part sweep time
func:SetDotSwpTime
param:<in>devHandle:dev's ctrl handle from ini
      <in>dotswpTime:time   
return:>=0 is ok
 */
DiInt32 SetDotSwpTime(DiSession devHandle,DiReal64 dotswpTime);

DiInt32 SetTotalSwtTimeUs(DiSession devHandle,DiReal64 sumTime);
/*
purpose:set one seg sweep time
func:SetTotalSwpTimeLow
param:<in>devHandle:dev's ctrl handle from ini
      <in>totalswptimeLow:time   
return:>=0 is ok
 */
DiInt32 SetTotalSwpTimeLow(DiSession devHandle,DiUInt32 totalswptimeLow);

/*
purpose:set one seg sweep time
func:SetTotalSwpTimeHigh
param:<in>devHandle:dev's ctrl handle from ini
      <in>totalswptimeHigh:time   
return:>=0 is ok
 */
DiInt32 SetTotalSwpTimeHigh(DiSession devHandle,DiUInt32 totalswptimeHigh);

/*
purpose:set trace num
func:SetDisplayNum
param:<in>devHandle:dev's ctrl handle from ini
      <in>displayNum:trace line num   
return:>=0 is ok
 */
DiInt32 SetDisplayNum(DiSession devHandle,DiUInt32 displayNum);

/*
purpose:clear local ram
func:DataBufferClear
param:<in>devHandle:dev's ctrl handle from ini
      <in>dataaddrClr:clear flag,0 clear;1 unclear 
return:>=0 is ok
 */
DiInt32 DataBufferClear(DiSession devHandle,DiUInt32 dataaddrClr);

/*
purpose:set fft bucket for dector
func:SetFftBucketNum
param:<in>devHandle:dev's ctrl handle from ini
      <in>fftbucketNum:bucket num //0726
return:>=0 is ok
 */
DiInt32 SetFftBucketNum(DiSession devHandle,DiReal64 fftbucketNum);

/*
purpose:set dector direct ctrl
func:SetDetectorDirectFlag
param:<in>devHandle:dev's ctrl handle from ini
      <in>detectorFlag:bucket num 0 undirect;1 direct
return:>=0 is ok
 */
DiInt32 SetDetectorDirectFlag(DiSession devHandle,DiUInt32 detectorFlag);

/*
purpose:set audio time
func:SetAudioTime
param:<in>devHandle:dev's ctrl handle from ini
      <in>audiotime:audio time
return:>=0 is ok
 */
//DiInt32 SetAudioTime(DiSession devHandle,DiUInt32 audiotime);

/*
purpose:set audio volume
func:SetAudioVolume
param:<in>devHandle:dev's ctrl handle from ini
      <in>audioVolume:volume
return:>=0 is ok
 */
//DiInt32 SetAudioVolume(DiSession devHandle,DiUInt32 audioVolume);

/*
purpose:set demod type
func:SetAudioType
param:<in>devHandle:dev's ctrl handle from ini
      <in>audioType:type
return:>=0 is ok
 */
//DiInt32 SetAudioType(DiSession devHandle,DiUInt32 audioType);

/*
purpose:set demod enable
func:SetAudioEn
param:<in>devHandle:dev's ctrl handle from ini
      <in>audioEn:type
return:>=0 is ok
 */
//DiInt32 SetAudioEn(DiSession devHandle,DiUInt32 audioEn);

/*
purpose:fft calc num
func:SetFftCalcNum
param:<in>devHandle:dev's ctrl handle from ini
      <in>fftcalNum:num
return:>=0 is ok
 */
DiInt32 SetFftCalcNum(DiSession devHandle,DiUInt32 fftcalNum);

/*
purpose:fft calc direction
func:SetFftCalcDirection
param:<in>devHandle:dev's ctrl handle from ini
      <in>fftDirection:direction
return:>=0 is ok
 */
DiInt32 SetFftCalcDirection(DiSession devHandle,DiUInt32 fftDirection);

/*
purpose:fft start index
func:SetFftValidStartNum
param:<in>devHandle:dev's ctrl handle from ini
      <in>fftvalidstartNum:start index
return:>=0 is ok
 */
DiInt32 SetFftValidStartNum(DiSession devHandle,DiUInt32 fftvalidstartNum);

/*
purpose:fft end index
func:SetFftValidEndNum
param:<in>devHandle:dev's ctrl handle from ini
      <in>fftvalidendNum:end index
return:>=0 is ok
 */
DiInt32 SetFftValidEndNum(DiSession devHandle,DiUInt32 fftvalidendNum);

/*
purpose:fft dot sweep time
func:SetFftDotSwpTime
param:<in>devHandle:dev's ctrl handle from ini
      <in>fftdotswpTime:time
return:>=0 is ok
 */
DiInt32 SetFftDotSwpTime(DiSession devHandle,DiReal64 fftdotswpTime);

/*
purpose:before dector trig time
func:SetBucketTrigDelayTime
param:<in>devHandle:dev's ctrl handle from ini
      <in>buckettrigTime:time
return:>=0 is ok
 */
DiInt32 SetBucketTrigDelayTime(DiSession devHandle,DiReal64 buckettrigTime);

/*
purpose:rbw/vbw delay time
func:SetFirRbwvbwDelayTime
param:<in>devHandle:dev's ctrl handle from ini
      <in>rbwvbwdelayTime:time,us
return:>=0 is ok
 */
DiInt32 SetFirRbwvbwDelayTime(DiSession devHandle,DiReal64 rbwvbwdelayTime);

/*
purpose:rbw/vbw delay time
func:SetFftRbwvbwDelayTime
param:<in>devHandle:dev's ctrl handle from ini
      <in>rbwvbwdelayTime:time,us
return:>=0 is ok
 */
DiInt32 SetFftRbwvbwDelayTime(DiSession devHandle,DiUInt32 rbwvbwdelayTime);

/*
purpose:set trig type
func:SetTrigType
param:<in>devHandle:dev's ctrl handle from ini
      <in>trigType:trig type
return:>=0 is ok
 */
//DiInt32 SetTrigType(DiSession devHandle,DiUInt32 trigType);

/*
purpose:set trig direction
func:SetTrigDirect
param:<in>devHandle:dev's ctrl handle from ini
      <in>trigDirect:direction
return:>=0 is ok
 */
//DiInt32 SetTrigDirect(DiSession devHandle,DiUInt32 trigDirect);

/*
purpose:set trig delay time
func:SetTrigDelayTime
param:<in>devHandle:dev's ctrl handle from ini
      <in>trigTime:delay time
return:>=0 is ok
 */
//DiInt32 SetTrigDelayTime(DiSession devHandle,DiUInt32 trigTime);

/*
purpose:set trig level
func:SetTrigLevel
param:<in>devHandle:dev's ctrl handle from ini
      <in>trigAmp:trig level
return:>=0 is ok
 */
//DiInt32 SetTrigLevel(DiSession devHandle,DiUInt32 trigAmp);

/*
purpose:trigger resweep interrupt
func:SetSwpInterrupt
param:<in>devHandle:dev's ctrl handle from ini      
return:>=0 is ok
 */
DiInt32 SetSwpInterrupt(DiSession devHandle);

/*
purpose:stop sweep
func:SetSwpStop
param:<in>devHandle:dev's ctrl handle from ini      
return:>=0 is ok
 */
DiInt32 SetSwpStop(DiSession devHandle);

/*
purpose:run sweep
func:SetSwpRun
param:<in>devHandle:dev's ctrl handle from ini      
return:>=0 is ok
 */
DiInt32 SetSwpRun(DiSession devHandle);

/*
purpose:used in wave check,get seg num
func:SetCheckSegNum
param:<in>devHandle:dev's ctrl handle from ini
      <in>segNum:seg num
return:>=0 is ok
 */
//DiInt32 SetCheckSegNum(DiSession devHandle,DiUInt32 segNum);

/*
purpose:set fir bucket time
func:SetFirBucketTime
param:<in>devHandle:dev's ctrl handle from ini
      <in>bucketime:us
return:>=0 is ok
 */
DiInt32 SetFirBucketTime(DiSession devHandle,DiReal64 bucketime);

/*
purpose:get result data from local part
func:GetResultData
param:<in>devHandle:dev's ctrl handle from ini
      <in/out>pbuffer:data buffer
      <in>num: data nums
return:>=0 is ok
 */
DiInt32 GetResultData(DiSession devHandle,DiPUInt32 pbuffer,DiUInt32 num);
//Albert 19/04/04 for real-time FPGA
/*
purpose:set real time fpga start
func:SetRtSaFpgaStart
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 SetRtSaFpgaStart(DiSession devHandle);
/*
purpose:set real time fpga stop
func:SetRtSaFpgaStop
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 SetRtSaFpgaStop(DiSession devHandle);
/*
purpose:set real time fpga rbw
func:SetRtSaRBW
param:<in>devHandle:dev's ctrl handle from ini
			<in>rbwIndex:rbw set to FPGA
return:>=0 is ok
 */
DiInt32 SetRtSaRBW(DiSession devHandle,DiUInt32 rbwIndex);
/*
purpose:set real time fpga dectector
func:SetRtSaDetector
param:<in>devHandle:dev's ctrl handle from ini
			<in>detectorIndex:detector set to FPGA
return:>=0 is ok
 */
DiInt32 SetRtSaDetector(DiSession devHandle,DiUInt32 detectorIndex);
/*
purpose:set real time span
func:SetRtSaDetector
param:<in>devHandle:dev's ctrl handle from ini
			<in>Span:real time span
return:>=0 is ok
 */
DiInt32 SetRtSaSpan(DiSession devHandle,DiReal64 Span);
/*
purpose:set real time fft window
func:SetRtSaFFTWindow
param:<in>devHandle:dev's ctrl handle from ini
			<in>fftWindowIndex:real time fft window index
return:>=0 is ok
 */
DiInt32 SetRtSaFFTWindow(DiSession devHandle,DiUInt32 fftWindowIndex);
/*
purpose:set real time acq time 
func:SetRtSaAcqTime
param:<in>devHandle:dev's ctrl handle from ini
			<in>acqtime:real time acq time
return:>=0 is ok
 */
DiInt32 SetRtSaAcqTime(DiSession devHandle,DiReal32 acqtime);
/*
purpose:set real time mean factor 
func:SetRtSaMeanFactor
param:<in>devHandle:dev's ctrl handle from ini
			<in>meanFactor:real time mean factor
return:>=0 is ok
 */
DiInt32 SetRtSaMeanFactor(DiSession devHandle,DiReal32 meanFactor);
/*
purpose:set real time fft bucket num 
func:SetRtSaFFTBucketNum
param:<in>devHandle:dev's ctrl handle from ini
			<in>fftBucketNum:real time fft bucket number
return:>=0 is ok
 */
DiInt32 SetRtSaFFTBucketNum(DiSession devHandle,DiInt32 fftBucketNum);
/*
purpose:set real time fft valid start & stop num
func:SetRtSaFFTBucketNum
param:<in>devHandle:dev's ctrl handle from ini
			<in>fftBucketNum:real time fft valid num 0~15:start 16_31:stop
return:>=0 is ok
 */
DiInt32 SetRtSaFFTValidNum(DiSession devHandle,DiReal32 fftvalidNum);
/*
purpose:set rtsa fft length
func:SetRtSaFFTLength
param:<in>devHandle:dev's ctrl handle from ini
			<in>length:real time fft length
return:>=0 is ok
 */
DiInt32 SetRtSaFFTLength(DiSession devHandle, DiUInt32 length);
/*
purpose:set real time if bandwidth
func:SetRtSaIFBandWidth
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 SetRtSaIFBandWidth(DiSession devHandle);
/*
purpose:set real time trigger type
func:SetRtSaTrigger
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 SetRtSaTrigger(DiSession devHandle,DiUInt32 trigger);
/*
purpose:set real time trigger period
func:SetRtSaTriggerPeriod
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 SetRtSaTriggerPeriod(DiSession devHandle,DiUInt32 Period);
/*
purpose:set real time trigger delay
func:SetRtSaTriggerDelay
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 SetRtSaTriggerDelay(DiSession devHandle,DiUInt32 Delay);

/*
purpose:set real time trigger hide time
func:SetRtSaTriggerPeriod
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 SetRtSaTriggerHideTime(DiSession devHandle,DiUInt32 time);
/*
purpose:set real time trigger level
func:SetRtSaTriggerVideoLevel
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 SetRtSaTriggerVideoLevel(DiSession devHandle,DiReal32 time);
/*
purpose:set real time trigger level
func:SetRtSaTriggerRFLevel
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 SetRtSaTriggerRFLevel(DiSession devHandle,DiReal64 time);
/*
purpose:set real time trigger slope
func:setRtSaTriggerSlope
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 setRtSaTriggerSlope(DiSession devHandle, DiUInt32 slope);
/*
purpose:set real time dsp status
func:setRtSaDspStatus
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 GetRtSaDspStatus(DiSession devHandle, DiPUInt32 status);
/*
purpose:set real time balance factor
func:setRtSaBalanceFactor
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 setRtSaBalanceFactor(DiSession devHandle,DiPReal32 factor);
/*
purpose:eliminate dc  
func:SetRtSaTriggerPeriod
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 EliminateDC(DiSession devHandle, DiUInt32 flag);
/*
purpose:get result data from local part
func:GetResultFloatData
param:<in>devHandle:dev's ctrl handle from ini
      <in/out>pbuffer:data buffer
      <in>num: data nums
return:>=0 is ok
 */
DiInt32 GetResultFloatData(DiSession devHandle,DiPReal32 pbuffer,DiUInt32 num);

DiInt32 RtSaTestParam(DiSession devHandle);
/*
purpose:wait rtsa fpga get ready
func:WaitFpgaReady
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 WaitFpgaReady(DiSession devHandle);
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __DigSigDealVirtualDriver__ */
