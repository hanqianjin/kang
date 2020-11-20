//==============================================================================
//
// Title:		MainBoardVirtualDriver.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/1/11 at 8:39:55 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __MainBoardVirtualDriver_H__
#define __MainBoardVirtualDriver_H__

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
purpose:ini the ctrl of the mainboard,for osci
func:SetOsciVolt
param:<in>devHandle:dev's ctrl handle from ini
      <in>osciVolt:set osci volt for ref clock
      value range:0~3.3v
return:>=0 is ok
*/
DiInt32 SetOsciVolt(DiSession devHandle,DiReal64 osciVolt);

/*
purpose: IF gain ctrl
func:IFGainCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>gaindB:set the IF gain
      value range:30~60dB,10dB step 
return:>=0 is ok
 */
DiInt32 IFGainCtrl(DiSession devHandle,DiReal64 gaindB);

/*
purpose: get temp from mainboard digital part
func:GetDigBoardTemperature
param:<in>devHandle:dev's ctrl handle from ini
      <out>tempValue:get temp of RfBoard 
return:>=0 is ok
 */
DiInt32 GetDigBoardTemperature(DiSession devHandle,DiPReal64 tempValue);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __MainBoardVirtualDriver_H__ */
