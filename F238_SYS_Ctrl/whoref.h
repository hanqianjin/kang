//==============================================================================
//
// Title:		MainBoardVirtualDriver.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/1/11 at 8:39:55 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __Whoref_H__
#define __Whoref_H__

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
purpose: set the ref of the board
func:InOutRefCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>refValue:set the ref in or out
	  value range:0 GPS ref,1 out_10MHz ref,2 out_13MHz ref,3 out_15MHz ref,4 in_10MHz ref   
return:>=0 is ok
 */
DiInt32 InOutRefCtrl(DiSession devHandle,DiUInt32 refValue);

/*
purpose:Brightness level select
func:SetBrightnessLevel
param:<in>devHandle:dev's ctrl handle from ini
param:<in>brtLevel:brightness level setted by user
          value range:1 lev1,2 lev2,3 lev3,4 lev4,5 lev5
return:>=0 is ok
 */
DiInt32 SetBrightnessLevel(DiSession devHandle,DiUInt32 brtLevel);

/*
purpose:ini the ctrl of the mainboard,for osci
func:SetOsciVolt
param:<in>devHandle:dev's ctrl handle from ini
      <in>osciVolt:set osci volt for ref clock
      value range:0~1024*16
return:>=0 is ok
*/
DiInt32 SetOsciFreq(DiSession devHandle,DiInt32 osci);

DiInt32 FpgaCpldIniHigh(DiSession devHandle);
DiInt32 FpgaCpldIniLow(DiSession devHandle);

/*
for debug
*/
DiInt32 SetSecIfAttendB(DiSession devHandle,DiInt32 attenval);


DiInt32 GetAdcoverFlag(DiSession devHandle,DiPUInt32 adcover);

DiInt32 ClearAdcoverFlag(DiSession devHandle,DiUInt32 adcover);

DiInt32 GetZynqVer(DiSession devHandle,DiPUInt32 ver);

DiInt32 GetSpaVer(DiSession devHandle,DiPUInt32 ver);

DiInt32 GetCpldVer(DiSession devHandle,DiPUInt32 ver);

DiInt32 GetFpgaState(DiSession devHandle,DiPUInt32 ver);
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Whoref_H__ */
