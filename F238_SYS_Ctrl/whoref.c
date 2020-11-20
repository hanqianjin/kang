//==============================================================================
//
// Title:		whoref.c
// Purpose:		A short description of the implementation.
//
// Created on:	2019/4/25 at 8:39:55 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include "BitSehInfo.h"
#include "whoref.h"
//==============================================================================
// Constants
#define REFSOURCE 0x80001090
#define LCDLIGHT 0x80001110

#ifdef BIT_F238
#define MBOARDINIADDR 0x800010a0
#endif

#ifdef BIT_F239
#define MBOARDINIADDR 0x80001020
#endif

#ifdef BIT_F238_SMART
#define MBOARDINIADDR 0x80001020
#endif

#define FPGACPLDRESET 0x80001070


#define SECIFATTEN 0x80001030
#define MINOSCIVOLT 0
#define MAXOSCIVOLT 32767

#define ADCOVER 0x84000040
#define CLEARADCOVER 0x80000178
#define ZYNQVER 0x8400007c
#define SPARTANVER 0x84000078
#define CPLDVER 0x84000074
#define FPGASTATE 0x84000070
/*
purpose: set the ref of the board
func:InOutRefCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>refValue:set the ref in or out
	  value range:0 GPS ref,1 out_10MHz ref,2 out_13MHz ref,3 out_15MHz ref,4 in_10MHz ref
return:>=0 is ok
 */
DiInt32 InOutRefCtrl(DiSession devHandle,DiUInt32 refValue)
{	
	DiUInt32 iData = 0;
	refValue &= 0x7;
	DiInt32 iBack = BitRead32(devHandle,REFSOURCE,&iData);
	iData &= 0xfffffff8;
	iData |= refValue;	
	
	iBack = BitWrite32(devHandle,REFSOURCE,iData); 

	return iBack;
}


/*
purpose:Brightness level select
func:SetBrightnessLevel
param:<in>devHandle:dev's ctrl handle from ini
param:<in>brtLevel:brightness level setted by user
	  value range:1 lev1,2 lev2,3 lev3,4 lev4,5 lev5
return:>=0 is ok
 */
DiInt32 SetBrightnessLevel(DiSession devHandle,DiUInt32 brtLevel)
{
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,LCDLIGHT,&iData);

	iData &= 0xfff00000;
	switch(brtLevel)
	{
		case 1: iData |= 20000; break;
		case 2: iData |= 40000; break;
		case 3: iData |= 60000; break;
		case 4: iData |= 80000; break;
		case 5: iData |= 90000; break;
	}
	iBack = BitWrite32(devHandle,LCDLIGHT,iData);
	//if(iBack < 0)
	  //iBack = SA_LOLastBandKeeptime;
	return iBack;
}

/*
purpose:ini the ctrl of the mainboard,for osci
func:SetOsciVolt
param:<in>devHandle:dev's ctrl handle from ini
      <in>osciVolt:set osci volt for ref clock
      value range:0~1024*16
return:>=0 is ok
*/
DiInt32 SetOsciFreq(DiSession devHandle,DiInt32 osci)
{	

	osci = osci < MINOSCIVOLT ? MINOSCIVOLT : osci;
	osci = osci > MAXOSCIVOLT ? MAXOSCIVOLT : osci;	
	DiUInt32 iData = 0;
#ifdef BIT_F238
	DiInt32 iBack = BitRead32(devHandle,MBOARDINIADDR,&iData);
	iData &= 0xffff8000;
	iData |= osci;
	
	iBack = BitWrite32(devHandle,MBOARDINIADDR,iData);

#endif 

#ifdef BIT_F239
	DiInt32 iBack = BitRead32(devHandle,MBOARDINIADDR,&iData);
	iData &= 0xffffc000;
	iData |= osci;
	
	iBack = BitWrite32(devHandle,MBOARDINIADDR,iData);
#endif

#ifdef BIT_F238_SMART
	DiInt32 iBack = BitRead32(devHandle,MBOARDINIADDR,&iData);
	iData &= 0xffffc000;
	iData |= osci;
	
	iBack = BitWrite32(devHandle,MBOARDINIADDR,iData);
#endif
	//if(iBack < 0)
	  //iBack = SA_CRYVOLT_Control;
	return iBack;
}

DiInt32 FpgaCpldIniHigh(DiSession devHandle)
{	
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,FPGACPLDRESET,&iData);		
	iData &= 0xfffffff0;
	iData |= 0xf;  
	iBack =	BitWrite32(devHandle,FPGACPLDRESET,iData);		
	return iBack;
}

DiInt32 FpgaCpldIniLow(DiSession devHandle)
{	
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,FPGACPLDRESET,&iData);				
	iData &= 0xfffffff0;	 
	iBack =	BitWrite32(devHandle,FPGACPLDRESET,iData);	
	return iBack;
}

DiInt32 SetSecIfAttendB(DiSession devHandle,DiInt32 attenval)
{
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,SECIFATTEN,&iData);				
	iData &= 0xffffffd0;	
	iData |= attenval; 
	iBack =	BitWrite32(devHandle,SECIFATTEN,iData);	
	return iBack;	
}

DiInt32 GetAdcoverFlag(DiSession devHandle,DiPUInt32 adcover)
{

DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,ADCOVER,&iData);	
*adcover = iData;
	return iBack;

}
DiInt32 ClearAdcoverFlag(DiSession devHandle,DiUInt32 adcover)
{

}
DiInt32 GetZynqVer(DiSession devHandle,DiPUInt32 ver)
{
DiUInt32 iData = 0;
DiInt32 iBack = BitRead32(devHandle,ZYNQVER,&iData);	
*ver = iData;
	return iBack;

}

DiInt32 GetSpaVer(DiSession devHandle,DiPUInt32 ver)
{
DiUInt32 iData = 0;
DiInt32 iBack = BitRead32(devHandle,SPARTANVER,&iData);
*ver = iData;	
	return iBack;

}
DiInt32 GetCpldVer(DiSession devHandle,DiPUInt32 ver)
{
DiUInt32 iData = 0;
DiInt32 iBack = BitRead32(devHandle,CPLDVER,&iData);
*ver = iData;	
	return iBack;
}
DiInt32 GetFpgaState(DiSession devHandle,DiPUInt32 ver)
{
DiUInt32 iData = 0;
DiInt32 iBack = BitRead32(devHandle,FPGASTATE,&iData);	
*ver = iData;
	return iBack;
}
/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
