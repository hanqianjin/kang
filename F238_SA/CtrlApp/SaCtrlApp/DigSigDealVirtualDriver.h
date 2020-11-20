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
DiInt32 SetLastBandCtrl(DiSession devHandle,DiUInt32 flag);


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
DiInt32 SetVbw(DiSession devHandle,DiReal64 vbwValue);

/*
purpose:set detector mode
func:SetDetectormode
param:<in>devHandle:dev's ctrl handle from ini
      <in>checkMode:check mode   
return:>=0 is ok
 */
DiInt32 SetDetectormode(DiSession devHandle,DiUInt32 checkMode);

/*
purpose:set data proc mode
func:SetDataProcMode
param:<in>devHandle:dev's ctrl handle from ini
      <in>dataproMode:data proc mode   
return:>=0 is ok
 */
DiInt32 SetDataProcMode(DiSession devHandle,DiUInt32 dataproMode);

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
purpose:trigger resweep interrupt
func:SetSwpInterrupt
param:<in>devHandle:dev's ctrl handle from ini      
return:>=0 is ok
 */
DiInt32 SetSwpInterrupt(DiSession devHandle);

/*
purpose:resweep interrupt stop
func:SetSwpInterruptStop
param:<in>devHandle:dev's ctrl handle from ini      
return:>=0 is ok
 */
DiInt32 SetSwpInterruptStop(DiSession devHandle);

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
DiInt32 SetCheckSegNum(DiSession devHandle,DiUInt32 segNum);

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

/*
purpose:get detector time
func:GetDetectorTime
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 GetDetectorTime(DiSession devHandle);

/*
purpose:get fsr
func:GetFsr
param:<in>devHandle:dev's ctrl handle from ini
return:fsr value
 */
DiInt32 GetFsr(DiSession devHandle);

/*
purpose:set fsrGet start
func:SetFsrGetStart
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 SetFsrGetStart(DiSession devHandle);

/*
purpose:set fsrGet stop
func:SetFsrGetStop
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 SetFsrGetStop(DiSession devHandle);

/*
perpose:set trigger mode
func:SetTriggerMode
param:<in>devHandle:dev's ctrl handle from ini
param:<in>triggermode:trigger mode
return:>=0 is ok
*/
DiInt32 SetTriggerMode(DiSession devHandle,DiUInt32 triggermode);

/*
perpose:set trigger direct
func:SetTriggerDirect
param:<in>devHandle:dev's ctrl handle from ini
param:<in>SetTriggerDirect:trigger direct
return:>=0 is ok
*/
DiInt32 SetTriggerDirect(DiSession devHandle,DiUInt32 triggerdirect);

/*
perpose:set trigger delay time
func:SetTriggerDelayTime
param:<in>devHandle:dev's ctrl handle from ini
param:<in>triggerdelaytime:trigger delay time
return:>=0 is ok
*/
DiInt32 SetTriggerDelayTime(DiSession devHandle,DiReal64 triggerdelaytime);

/*
perpose:set vedio trigger amplitude
func:SetVedioTriggerAmp
param:<in>devHandle:dev's ctrl handle from ini
param:<in>vediotriggeramp:vedio trigger amplitude
return:>=0 is ok
*/
DiInt32 SetVedioTriggerAmp(DiSession devHandle,DiInt32 vediotriggeramp);

/*
perpose:set trigger per time
func:SetTriggerPerTime
param:<in>devHandle:dev's ctrl handle from ini
param:<in>triggerpertime:trigger per time
return:>=0 is ok
*/
DiInt32 SetTriggerPerTime(DiSession devHandle,DiReal64 triggerpertime);

/*
perpose:set RF Burst Trigger Amplitude
func:SetRFBurstTriggerAmp
param:<in>devHandle:dev's ctrl handle from ini
param:<in>triggerpertime:rf burst trigger amplitude
return:>=0 is ok
*/
DiInt32 SetRFBurstTriggerAmp(DiSession devHandle,DiInt32 refbursttriggeramp);

//*************Door Control Sweep
/*
perpose:set Door Control Source
func:SetDoorControlSourceSelect
param:<in>devHandle:dev's ctrl handle from ini
param:<in>triggerMode:[2:0]0 extern_trigger 1 RF_trigger 2 period_trigger
return:>=0 is ok
*/
DiInt32 SetDoorControlSourceSelect(DiSession devHandle,DiUInt32 triggerMode);

/*
perpose:Level or Edge Select
func:SetLevelEdgeSelect
param:<in>devHandle:dev's ctrl handle from ini
param:<in>selectControlWord:[5]0 edge 1 level
return:>=0 is ok
*/
DiInt32 SetLevelEdgeSelect(DiSession devHandle,DiUInt32 selectControlWord);

/*
perpose:Level and Edge mode set
func:SetLevelEdgeMode
param:<in>devHandle:dev's ctrl handle from ini
param:<in>mode:[4] 0 low 1 high
return:>=0 is ok
*/
DiInt32 SetLevelEdgeMode(DiSession devHandle,DiUInt32 mode);

/*
perpose:Door Control Sweep Mode Select
func:SetDoorControlSweepModeSelect
param:<in>devHandle:dev's ctrl handle from ini
param:<in>sweepMode:[9:8]0 lo 1 vedio 2 fft
return:>=0 is ok
*/
DiInt32 SetDoorControlSweepModeSelect(DiSession devHandle,DiUInt32 sweepMode);

/*
perpose:Period Trigger Door Control Synchro Source Select
func:SetPrdTrgSynchroSrcSelect
param:<in>devHandle:dev's ctrl handle from ini
param:<in>sourceMode:[14:12]0 noSouce 1 externTrigger 2 RFBurst
return:>=0 is ok
*/
DiInt32 SetPrdTrgSynchroSrcSelect(DiSession devHandle,DiUInt32 sourceMode);

/*
perpose:Door Control Sweep Switch
func:SetDoorControlSwitch
param:<in>devHandle:dev's ctrl handle from ini
param:<in>switchMode:[31]0 close 1 open
return:>=0 is ok
*/
DiInt32 SetDoorControlSwitch(DiSession devHandle,DiUInt32 switchMode);

/*
perpose:Edge Trigger Trigger_Delay
func:SetEdgTrigDely
param:<in>devHandle:dev's ctrl handle from ini
param:<DiReal64>triggerDelay:[31:0]ms
return:>=0 is ok
*/
DiInt32 SetEdgTrigDely(DiSession devHandle,DiReal64 triggerDelay);

/*
perpose:Edge Trigger Door_Width
func:SetEdgTrigDoorWdth
param:<in>devHandle:dev's ctrl handle from ini
param:<DiReal64>doorWidth:[31:0]ms
return:>=0 is ok
*/
DiInt32 SetEdgTrigDoorWdth(DiSession devHandle,DiReal64 doorWidth);

/*
perpose:Edge Trigger Trigger_Prevent_Status
func:SetEdgTrigPrvntStatus
param:<in>devHandle:dev's ctrl handle from ini
param:<DiUInt32>preventStatus:[31] 0 close 1 open
return:>=0 is ok
*/
DiInt32 SetEdgTrigPrvntStatus(DiSession devHandle,DiUInt32 preventStatus);

/*
perpose:Edge Trigger Trigger_Prevent_Times
func:SetEdgTrigPrvntTimes
param:<in>devHandle:dev's ctrl handle from ini
param:<DiReal64>preventTimes:[29:0]ms
return:>=0 is ok
*/
DiInt32 SetEdgTrigPrvntTimes(DiSession devHandle,DiReal64 preventTimes);

/*
perpose:RFBurst Trigger Level
func:SetRFBurstTrigLevel
param:<in>devHandle:dev's ctrl handle from ini
param:<DiInt32>trigLevel:32bit dBm
return:>=0 is ok
*/
DiInt32 SetRFBurstTrigLevel(DiSession devHandle,DiInt32 trigLevel);

/*
perpose:Period Trigger Trigger_Period
func:SetPrdTrgPeriod
param:<in>devHandle:dev's ctrl handle from ini
param:<DiReal64>triggerPeriod:[31:0]ms
return:>=0 is ok
*/
DiInt32 SetPrdTrgPeriod(DiSession devHandle,DiReal64 triggerPeriod);

/*
perpose:Period Trigger Source_Delay
func:SetPrdTrgSrcDelay
param:<in>devHandle:dev's ctrl handle from ini
param:<DiReal64>sourceDelay:[31:0]ms
return:>=0 is ok
*/
DiInt32 SetPrdTrgSrcDelay(DiSession devHandle,DiReal64 sourceDelay);

/*
perpose:Period Trigger Trigger_Prevent_Status
func:SetPrdTrigPrvntStatus
param:<in>devHandle:dev's ctrl handle from ini
param:<DiUInt32>preventStatus:[31] 0 close 1 open
return:>=0 is ok
*/
DiInt32 SetPrdTrigPrvntStatus(DiSession devHandle,DiUInt32 preventStatus);

/*
perpose:Period Trigger Trigger_Prevent_Times
func:SetPrdTrigPrvntTimes
param:<in>devHandle:dev's ctrl handle from ini
param:<DiReal64>preventTimes:[29:0]ms
return:>=0 is ok
*/
DiInt32 SetPrdTrigPrvntTimes(DiSession devHandle,DiReal64 preventTimes);

/*
perpose:Test DAC OverRange
func:SetDACOverRangeTest
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
*/
DiInt32 SetDACOverRangeTest(DiSession devHandle);




#ifdef __cplusplus
    }
#endif

#endif  /* ndef __DigSigDealVirtualDriver__ */
