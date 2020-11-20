#ifndef _BIT_RFVIRTUALDRIVER_H
#define _BIT_RFVIRTUALDRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DiIoCtrl.h" 
	
/*
purpose:ini the ctrl of the board
func:RfIni
param:<in>devHandle:dev's ctrl handle from ini 
return:>=0 is ok
*/
DiInt32 RfIni(DiSession devHandle);

/*
purpose: channel choose by freq
func:RfChannelChoose
param:<in>devHandle:dev's ctrl handle from ini
      <in>freqHz:set the freqHz's channel
	  value range:9kHz~32GHz
return:>=0 is ok
 */
DiInt32 RfChannelChoose(DiSession devHandle,DiReal64 freqHz);

/*
purpose: restrain the zero freq by phase
func:ZeroRestrainPhaseCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>phase:set the phase
	  value range:0~354.375,per bit is 5.625
return:>=0 is ok
 */
DiInt32 ZeroRestrainPhaseCtrl(DiSession devHandle,DiReal64 phase);

/*
purpose: set the zero freq restain atten
func:ZeroRestrainPhaseCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>dcvalue:set the atten dc
	  value range:low 16bits
return:>=0 is ok
 */
DiInt32 ZeroRestrainAttenCtrl(DiSession devHandle,DiInt32 dcvalue);

/*
purpose: set the sec IF attention
func:SecIfAttenCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>attendB:set the attenvalue
	  value range:0~31,0~31dB
return:>=0 is ok
 */
DiInt32 SecIfAttenCtrl(DiSession devHandle,DiReal64 attendB);

/*
purpose: set the high freq pre atten
func:PreAttenCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>attendB:set the attenvalue
	  value range:7.5~23.63375GHz,0~31dB
return:>=0 is ok
 */
DiInt32 PreAttenCtrl(DiSession devHandle,DiReal64 attendB);

/*
purpose: set the high freq pre amplifier channel
func:PreAmpliChannelCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>ctrlswitch:channel switch
	  value range:7.5~23.63375GHz,0:direct,1:amplier
return:>=0 is ok
 */
DiInt32 PreAmpliChannelCtrl(DiSession devHandle,DiUInt32 ctrlswitch);

/*
purpose: set the low freq pre atten
func:LowFreqPreAttenCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>attendB:set the attenvalue
	  value range:9kHz~7.5GHz,0~31dB
return:>=0 is ok
 */
DiInt32 LowFreqPreAttenCtrl(DiSession devHandle,DiReal64 attendB);

/*
purpose: set the low freq pre amplifier channel
func:LowFreqPreAmpliChannelCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>ctrlswitch:channel switch
	  value range:9kHz~7.5GHz,0:direct,1:amplier
return:>=0 is ok
 */
DiInt32 LowFreqPreAmpliChannelCtrl(DiSession devHandle,DiUInt32 ctrlswitch);

/*
purpose: set the sec lo out freq in Hz
func:SecLoOutfreqCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>freqHz:set the sec lo freq
	  value range:
return:>=0 is ok
 */
DiInt32 SecLoOutfreqCtrl(DiSession devHandle,DiReal64 freqHz);

/*
purpose: set the ref of the board
func:InOutRefCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>refValue:set the ref in or out
	  value range:0 out ref,1 in ref   
return:>=0 is ok
 */
DiInt32 InOutRefCtrl(DiSession devHandle,DiUInt32 refValue);

/*
purpose: set the micro freq pre atten
func:MicroFreqPreAttenCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>attendB:set the attenvalue
	  value range:23.63375~32GHz,0~30dB,step 5dB
return:>=0 is ok
 */
DiInt32 MicroFreqPreAttenCtrl(DiSession devHandle,DiReal64 attendB);

/*
purpose: set the micro freq pre amplifier channel
func:MicroFreqPreAmpliChannelCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>ctrlswitch:channel switch
	  value range:23.63375~32GHz,0:direct,1:amplier
return:>=0 is ok
 */
DiInt32 MicroFreqPreAmpliChannelCtrl(DiSession devHandle,DiUInt32 ctrlswitch);

/*
purpose: get temp from Rf
func:GetRfTemperature
param:<in>devHandle:dev's ctrl handle from ini
      <out>tempValue:get temp of RfBoard 
return:>=0 is ok
 */
DiInt32 GetRfTemperature(DiSession devHandle,DiPReal64 tempValue);

#ifdef __cplusplus
}
#endif

#endif
