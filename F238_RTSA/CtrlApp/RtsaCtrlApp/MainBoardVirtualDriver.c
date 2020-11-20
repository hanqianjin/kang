//==============================================================================
//
// Title:		MainBoardVirtualDriver.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/1/11 at 8:39:55 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include "BitSehInfo.h"
#include "MainBoardVirtualDriver.h"
//==============================================================================
// Constants
#define IFGAINADDR 0x80001080
#define MBOARDINIADDR 0x800010a0

//#define MINIFGAIN 30.0
//#define MAXIFGAIN 60.0
#define MINIFGAIN 0.0
#define MAXIFGAIN 45.0

#define MINOSCIVOLT 0.0
#define MAXOSCIVOLT 3.3
#define REFOSCIVOLT 3.3
//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

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
DiInt32 SetOsciVolt(DiSession devHandle,DiReal64 osciVolt)
{	
	osciVolt = osciVolt < MINOSCIVOLT + ESP ? MINOSCIVOLT : osciVolt;
	osciVolt = osciVolt > MAXOSCIVOLT + ESP ? MAXOSCIVOLT : osciVolt;
	DiInt32 voltWord = (DiInt32)((1 << 13) * osciVolt / REFOSCIVOLT); 
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,MBOARDINIADDR,&iData);
	iData &= 0xffff0000;
	iData |= (voltWord << 2);
	
	iBack = BitWrite32(devHandle,MBOARDINIADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_RESEVER_NOTICE;
	return iBack;
}

/*
purpose: IF gain ctrl
func:IFGainCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>gaindB:set the IF gain
      value range:30~60dB,10dB step 
return:>=0 is ok
 */
DiInt32 IFGainCtrl(DiSession devHandle,DiReal64 gaindB)
{
	/*gaindB = gaindB < MINIFGAIN + ESP ? MINIFGAIN : gaindB;
	gaindB = gaindB > MAXIFGAIN + ESP ? MAXIFGAIN : gaindB;
	DiInt32 ival = ((DiInt32)gaindB - 30) / 10; 
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,IFGAINADDR,&iData);
	iData &= 0xfffffffc;
	iData |= ival;
		
	iBack = BitWrite32(devHandle,IFGAINADDR,iData);
	if(iBack < 0)
	  iBack = SA_MEDFRE_Gain;
	return iBack;*/

	gaindB = gaindB < MINIFGAIN + ESP ? MINIFGAIN : gaindB;
	gaindB = gaindB > MAXIFGAIN + ESP ? MAXIFGAIN : gaindB;
	DiInt32 ival = ((DiInt32)gaindB) / 3; 
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,IFGAINADDR,&iData);
	iData &= 0xfffffff0;
	iData |= (~ival&0xf);
		
	iBack = BitWrite32(devHandle,IFGAINADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_CTL_IF_GAIN;
	return iBack;
}

/*
purpose: get temp from mainboard digital part
func:GetDigBoardTemperature
param:<in>devHandle:dev's ctrl handle from ini
      <out>tempValue:get temp of RfBoard 
return:>=0 is ok
 */
DiInt32 GetDigBoardTemperature(DiSession devHandle,DiPReal64 tempValue)
{
	return 0;
}
/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
