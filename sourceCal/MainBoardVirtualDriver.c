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

#include "MainBoardVirtualDriver.h"

#include "TestinWin.h"  
extern int panelHandle;
//==============================================================================
// Constants
#define IFGAINADDR 0x80000080
#define MBOARDINIADDR 0x800000a0  

#define MINIFGAIN 30.0
#define MAXIFGAIN 60.0

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
	#if TESTUNIT  
	DiReal64 temp = osciVolt;
	#endif  
	
	osciVolt = osciVolt < MINOSCIVOLT + ESP ? MINOSCIVOLT : osciVolt;
	osciVolt = osciVolt > MAXOSCIVOLT + ESP ? MAXOSCIVOLT : osciVolt;
	DiInt32 voltWord = (DiInt32)((1 << 13) * osciVolt / REFOSCIVOLT); 
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,MBOARDINIADDR,&iData);
	iData &= 0xffff0000;
	iData |= (voltWord << 2);
	
	#if TESTUNIT  
	char tempchar[128];
	sprintf(tempchar,"晶振电压设置:%.3lf,实设%.3lf,控制字:0x%x",temp,osciVolt,iData);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,tempchar);
	#endif
	
	iBack = BitWrite32(devHandle,MBOARDINIADDR,iData);
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
	#if TESTUNIT  
	DiReal64 temp = gaindB;
	#endif
	
	gaindB = gaindB < MINIFGAIN + ESP ? MINIFGAIN : gaindB;
	gaindB = gaindB > MAXIFGAIN + ESP ? MAXIFGAIN : gaindB;
	DiInt32 ival = ((DiInt32)gaindB - 30) / 10; 
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,IFGAINADDR,&iData);
	iData &= 0xfffffffc;
	iData |= ival;
	
	#if TESTUNIT  
	char tempchar[128];
	sprintf(tempchar,"晶振电压设置:%.3lf,实设0x%x",temp,iData);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,tempchar);
	#endif
	
	iBack = BitWrite32(devHandle,IFGAINADDR,iData);
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
