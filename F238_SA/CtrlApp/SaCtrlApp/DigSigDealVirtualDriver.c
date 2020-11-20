//==============================================================================
//
// Title:		DigSigDealVirtualDriver.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/1/20 at 11:34:57 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include "DigSigDealVirtualDriver.h"
#include <math.h>
#include "msgNoticeCode.h"
//==============================================================================
// Constants
#define RBWVBWADDR 0x80000010 /*RBW:bit0~3
VBW:bit4~7
*/
#define DETECTORMODEADDR 0x80000020 /*bit0~3* +p -p samp comm ava rms*/
#define DATAPROCMODEADDR 0x80000030 /*00 sweep;11 fft*/
#define SWPSTARTADDR 0x80000040 /*0 stop;1 run*/
#define ZEROSPANADDR 0x80000050 /*0 no zero;1 zero span */
#define DOTSWPTIMEADDR 0x80000060 /*fir single point time/45MHz*/

#define TOTALSWPTIMEHIGHADDR 0x80000090 /*single segment sweep time,90 high 16bits,80 low 32bits*/
#define TOTALSWPTIMELOWADDR 0x80000080

#define CHECKSEGNUMADDR 0x80000070 /*bit0~4,used in dector*/

#define DISPLAYNUMADDR 0x800000f0 /*bit0~11,screen show points*/
#define DETECTORFLAGADDR 0x80000100 /*0 not direct;1 direct */

//0412,Steve
#define FIRBUCKETLOW  0x800000D0
#define FIRBUCKETHIGH 0x800000E0
//0504,steve
#define ENDBANDFLAG 0x800000C0

//
#define DATAADDRCLRADDR 0x80000110 /*0 not clr 1clr;check register clr*/
#define FFTBUCKETNUMADDR 0x80000120 /*bit0~31,fft bucketnum points*/
#define ANALOGDEMOD 0x80000130/*audio time:bit 0~3  audio volume:bit 4~19 
audio type:bit 20~24
*/
#define AUDIOENADDR 0x80000140/*0 OFF;1 ON*/
#define FFTCALNUMADDR 0x80000150/*bit 0~15 ,fft calnum*/
#define FFTDIRECTIONADDR 0x80000160/* */
#define FFTVALIDNUMPROADDR 0x80000170/*FFTVALIDSTARTNUM:bit0~15 
FFTVALIDENDNUM:bit16~31
*/
#define TRIGSWEEPINTERPADDR 0x80000180 /*set 1 ,then set 0*/
#define BUCKETTRIGTIMEADDR 0x80000190/*bit:0~31*/
#define RBWVBWDELAYTIMEADDR 0x800001A0/*bit:0~31*/
#define TRIGTYPEANDDIRECTADDR   0x800001B0/*TRIGTYPE: 000 free trig;001 external trig;010 video trig;011 Periodic trig;100 RF Burst trig*/
#define TRIGTIMEADDR 0x800001C0 /*bit:0~31*/
#define VEDIOTRIGAMPADDR 0x80000210 /*bit:0~31*/
#define FFTDOTSWPTIMEADDRFRAC 0x800001E0/*bit:0~7 frac part*/
#define FFTDOTSWPTIMEADDRINT  0x800001F0/*bit:0~31 int part*/

#define TRIGPERTIMEADDR 0x80000200/*bit:0~31*/
//#define RFBURSTTRIGAMPLOWADDR 0x80000210
#define RFBURSTTRIGAMPHIGHADDR 0x80000220

#define SEGSWEEPNUMADDR 0x80000230/*zero span set 0*/

#define DETECTORTIMEADDR 0x80000240

#define FSRSTARTADDR   0x80000138
#define FSRSTOPADDR    0x80000148
#define FSRGETADDR     0x84000008

#define PLLOCALMEMBASEADDR 0x80010000

//Door Control Sweep Addr
#define DOORCTL_SWEEPADDR          0x8000000c
#define DOORCTL_EDG_TRIGDLYADDR    0x8000001c
#define DOORCTL_EDG_DOORWDTHADDR   0x8000002c
#define DOORCTL_EDG_PREVENTTMADDR  0x8000003c
#define DOORCTL_PRD_PERIODADDR     0x8000004c
#define DOORCTL_PRD_SRCDLYADDR     0x8000005c
#define DOORCTL_PRD_PREVENTTMADDR  0x8000006c
#define DOORCTL_RFBURST_TRIGLEVEL  0x8000007c

//ADC OverRange Test
#define ADC_OVERRANGE_TESTADDR     0x84000040
#define ADC_OVERRANG_CLEARADDR     0x80000178

////////////////////////////////////////////////////////////////////////////////////////////////
const DiReal64 rbwList[] = {5.0e6,3.0e6,1.0e6,3.0e5,1.0e5,3.0e4,1.0e4,3000,1000,300,100,30, 10, 3, 1};

extern const DiReal64 freqChannelList[];
extern DiInt32 GetFreqChannelIndex(DiReal64 freqHz);

static const DiInt32  CHECKMODEMAX = 5;//dector max nums

const int checkclockcircle = 100;//ns
DiInt32 GetrbwIndex(DiReal64 rbwHz);
////////////////////////////////////////////////////////////////////////////////////////////////
/*
purpose:set last sweep band
func:SetLastBandCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <int>flag:0 not last,1 last
return:>=0 is ok
 */
//steve 0504
DiInt32 SetLastBandCtrl(DiSession devHandle,DiUInt32 flag)
{
	flag = !!flag;
	DiInt32 iBack = BitWrite32(devHandle,ENDBANDFLAG,flag);	
	if(iBack < 0)
	  iBack = SA_LASTBand;
	return iBack;
}

/*
purpose:per seg sum nums
func:SetSegPoint
param:<in>devHandle:dev's ctrl handle from ini
      <in>pointsnum:the nums of per seg      
return:>=0 is ok
 */
DiInt32 SetSegPoint(DiSession devHandle,DiUInt32 pointsnum)
{
	DiInt32 iBack = BitWrite32(devHandle,SEGSWEEPNUMADDR,pointsnum);
	if(iBack < 0)
	  iBack = SA_SEGPoint;

	return iBack;
}

/*
purpose:set rbw
func:SetRbw
param:<in>devHandle:dev's ctrl handle from ini
      <in>rbwValue:the rbw value    
return:>=0 is ok
 */
DiInt32 SetRbw(DiSession devHandle,DiReal64 rbwValue)
{
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,RBWVBWADDR,&iData);

	//convert the data to bit value
	DiInt32 iIndex = GetrbwIndex(rbwValue);

	//low 4 bit set 0
	iData &= 0xfffffff0;
	iData |= (iIndex & 0xf);

	//insert
	iBack = BitWrite32(devHandle,RBWVBWADDR,iData);
	if(iBack < 0)
	    iBack = SA_RBW;
	return iBack;
}

/*
purpose:set vbw
func:SetVbw
param:<in>devHandle:dev's ctrl handle from ini
      <in>vbwValue:the rbw value    
return:>=0 is ok
 */
DiInt32 SetVbw(DiSession devHandle,DiReal64 vbwValue)
{
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,RBWVBWADDR,&iData);
	DiInt32 iIndex = GetrbwIndex(vbwValue);  
	// 4-7 bit set 0
	iData &= 0xffffff0f;
	iData |= ((iIndex & 0xf) << 4);
	//insert
	iBack = BitWrite32(devHandle,RBWVBWADDR,iData);
	if(iBack < 0)
	  iBack = SA_VBW;
	return iBack;

}

/*
purpose:set detector mode
func:SetDetectormode
param:<in>devHandle:dev's ctrl handle from ini
      <in>checkMode:check mode   
return:>=0 is ok
 */
DiInt32 SetDetectormode(DiSession devHandle,DiUInt32 checkMode)
{
	checkMode &= 0x0000000f;
	checkMode = checkMode > CHECKMODEMAX ? CHECKMODEMAX : checkMode;
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,DETECTORMODEADDR,&iData);

	// 0~3 bit set 0
	iData &=  0xfffffff0;
	iData |= checkMode;

	//insert
	iBack = BitWrite32(devHandle,DETECTORMODEADDR,iData);
	if(iBack < 0)
	  iBack = SA_DETECTORMode;
	return iBack;
}

/*
purpose:set data proc mode
func:SetDataprocMode
param:<in>devHandle:dev's ctrl handle from ini
      <in>dataproMode:data proc mode   
return:>=0 is ok
 */
DiInt32 SetDataProcMode(DiSession devHandle,DiUInt32 dataproMode)
{
	dataproMode &= 0x00000003;

//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,DATAPROCMODEADDR,&iData);

	// 0~1 bit set 0
	iData &=  0xfffffffc;
	iData |= dataproMode;

	//insert
	iBack = BitWrite32(devHandle,DATAPROCMODEADDR,iData);
	if(iBack < 0)
	  iBack = SA_DATAPROMode;
	return iBack;  
}

/*
purpose:run sweep
func:SetSwpRun
param:<in>devHandle:dev's ctrl handle from ini      
return:>=0 is ok
 */
DiInt32 SetSwpRun(DiSession devHandle)
{
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,SWPSTARTADDR,&iData);

	// 0 bit set 0
	iData &=  0xfffffffe;
	iData |= 1;

	//insert
	iBack = BitWrite32(devHandle,SWPSTARTADDR,iData);
	if(iBack < 0)
	  iBack = SA_SWPStart;
	return iBack;
}

/*
purpose:stop sweep
func:SetSwpStop
param:<in>devHandle:dev's ctrl handle from ini      
return:>=0 is ok
 */
DiInt32 SetSwpStop(DiSession devHandle)
{
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,SWPSTARTADDR,&iData);

	// 0 bit set 0
	iData &=  0xfffffffe;
	iData |= 0;   
	
	//insert
	iBack = BitWrite32(devHandle,SWPSTARTADDR,iData);
	if(iBack < 0)
	  iBack = SA_SWPStop;
	return iBack;
}

/*
purpose:trigger resweep interrupt
func:SetSwpInterrupt
param:<in>devHandle:dev's ctrl handle from ini      
return:>=0 is ok
 */
DiInt32 SetSwpInterrupt(DiSession devHandle)
{
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,TRIGSWEEPINTERPADDR,&iData);

	iData &=  0xfffffffe;
	iData |= 1;   
	iBack = BitWrite32(devHandle,TRIGSWEEPINTERPADDR,iData);

	/*iData &=  0xfffffffe;
	iData |= 0;   
	iBack = BitWrite32(devHandle,TRIGSWEEPINTERPADDR,iData);*/

 	if(iBack<0) iBack = SA_SweepInterrupt_Start;

	return iBack;
}

/*
purpose:resweep interrupt stop
func:SetSwpInterruptStop
param:<in>devHandle:dev's ctrl handle from ini      
return:>=0 is ok
 */
DiInt32 SetSwpInterruptStop(DiSession devHandle)
{
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,TRIGSWEEPINTERPADDR,&iData);

	iData &=  0xfffffffe;   
	iBack = BitWrite32(devHandle,TRIGSWEEPINTERPADDR,iData);

	if(iBack<0) iBack = SA_SweepInterrupt_Stop;

	return iBack;
}

/*
purpose:used in wave check,get seg num
func:SetCheckSegNum
param:<in>devHandle:dev's ctrl handle from ini
      <in>segNum:seg num
return:>=0 is ok
 */
DiInt32 SetCheckSegNum(DiSession devHandle,DiUInt32 segNum)
{
	segNum &= 0x1f;
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,CHECKSEGNUMADDR,&iData);
	
	iData &= 0xffffffe0;
	//bit0~4
	iBack = BitWrite32(devHandle,CHECKSEGNUMADDR,iData);
	if(iBack < 0)
	  iBack = SA_CHECKSegNum;
	return iBack;
}

/*
purpose:set zero span
func:SetZeroSpan
param:<in>devHandle:dev's ctrl handle from ini
      <in>zeroSpan:zero span mode   
return:>=0 is ok
 */
DiInt32 SetZeroSpan(DiSession devHandle,DiUInt32 zeroSpan)
{
	zeroSpan=!!zeroSpan;
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,ZEROSPANADDR,&iData); 
	// 0 bit set 0
	iData &=  0xfffffffe;
	iData |= zeroSpan;
	//insert
	iBack = BitWrite32(devHandle,ZEROSPANADDR,iData);
	if(iBack < 0)
	  iBack = SA_ZEROSPANFlag;
	return iBack;
}

/*
purpose:set fft one part sweep time
func:SetDotswpTime
param:<in>devHandle:dev's ctrl handle from ini
      <in>dotswpTime:time,us   
return:>=0 is ok
 */
DiInt32 SetDotSwpTime(DiSession devHandle,DiReal64 dotswpTime)
{ 
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,DOTSWPTIMEADDR,&iData);  
	// 0~31 bit set 0
	iData &=  0;
	
	//back to 10MHz
	iData |= (DiUInt32)(dotswpTime * 46.08); 
	//insert
	iBack = BitWrite32(devHandle,DOTSWPTIMEADDR,iData);
	if(iBack < 0)
	  iBack = SA_DOTSWPTime;

	return iBack;
}

//0505
//steve
DiInt32 SetTotalSwtTimeUs(DiSession devHandle,DiReal64 sumTime)
{
	DiInt32 iBack = 0;
	DiUInt64 isum = (DiUInt64)ceil(sumTime * 46.08);
	//set low bits
	iBack = BitWrite32(devHandle,TOTALSWPTIMELOWADDR,isum & 0xffffffff);
	//set high bits
	iBack = BitWrite32(devHandle,TOTALSWPTIMEHIGHADDR,isum >> 32 & 0xffffffff);
	if(iBack < 0)
	  iBack = SA_TOTALSWPTime;

	return iBack;
}

/*
purpose:set trace num
func:SetDisplayNum
param:<in>devHandle:dev's ctrl handle from ini
      <in>displayNum:trace line num   
return:>=0 is ok
 */
DiInt32 SetDisplayNum(DiSession devHandle,DiUInt32 displayNum)
{ 
	displayNum &= 0x00000fff;
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,DISPLAYNUMADDR,&iData);

	// 0~11 bit set 0
	iData &=  0xfffff000;
	iData |= displayNum;
	 
	//insert
	iBack = BitWrite32(devHandle,DISPLAYNUMADDR,iData);
	if(iBack < 0)
	  iBack = SA_DISPLAYNum;
	return iBack;
}

/*
purpose:clear local ram
func:DataBufferClear
param:<in>devHandle:dev's ctrl handle from ini
      <in>dataaddrClr:clear flag,1 clear;0 unclear 
return:>=0 is ok
 */
DiInt32 DataBufferClear(DiSession devHandle,DiUInt32 dataaddrClr)
{
	dataaddrClr = !! dataaddrClr;
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,DATAADDRCLRADDR,&iData);

	// 0 bit set 0
	iData &=  0xfffffffe;
	iData |= dataaddrClr;
	
	//insert
	iBack = BitWrite32(devHandle,DATAADDRCLRADDR,iData);
	if(iBack < 0)
	  iBack = SA_DATAADDRClr;
	return iBack;
}

/*
purpose:set fft bucket for dector
func:SetFftbucketNum
param:<in>devHandle:dev's ctrl handle from ini
      <in>fftbucketNum:bucket num 
return:>=0 is ok  //0726
 */
DiInt32 SetFftBucketNum(DiSession devHandle,DiReal64 fftbucketNum)
{
	//get the ori data
	DiUInt32 iData = (DiUInt32)fftbucketNum;
        DiUInt32 frac = (DiUInt32)((fftbucketNum - iData) * 0xff);
	//DiInt32 iBack = BitRead32(devHandle,FFTBUCKETNUMADDR,&iData);

	DiInt32 iBack = 0;
	iData <<= 8;
	iData &= 0xffffff00;
	iData |= frac;

	//insert
	iBack = BitWrite32(devHandle,FFTBUCKETNUMADDR,iData);

	if(iBack < 0)
	  iBack = SA_FFTBUCKETNum;
	return iBack;
}

/*
purpose:set dector direct ctrl
func:SetDetectorDirectFlag
param:<in>devHandle:dev's ctrl handle from ini
      <in>detectorFlag:bucket num 0 undirect;1 direct
return:>=0 is ok
 */
DiInt32 SetDetectorDirectFlag(DiSession devHandle,DiUInt32 detectorFlag)
{
	detectorFlag =!!detectorFlag;
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,DETECTORFLAGADDR,&iData);

	// 0 bit set 0
	iData &=  0xfffffffe;
	iData |= detectorFlag;
	
	//insert
	iBack = BitWrite32(devHandle,DETECTORFLAGADDR,iData);
	if(iBack < 0)
	  iBack = SA_DETECTORFlag;
	return iBack;
}

/*
purpose:fft calc num
func:SetFftCalcNum
param:<in>devHandle:dev's ctrl handle from ini
      <in>fftcalNum:num
return:>=0 is ok
 */
DiInt32 SetFftCalcNum(DiSession devHandle,DiUInt32 fftcalNum)
{
	fftcalNum &= 0x0000ffff;
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,FFTCALNUMADDR,&iData);

	//0~15 bit set 0
	iData &=  0xffff0000;
	iData |= fftcalNum;
	
	//insert
	iBack = BitWrite32(devHandle,FFTCALNUMADDR,iData);
	if(iBack < 0)
	  iBack = SA_FFTCALNum;
	return iBack;
}

/*
purpose:fft calc direction
func:SetFftCalcDirection
param:<in>devHandle:dev's ctrl handle from ini
      <in>fftDirection:direction
return:>=0 is ok
 */
DiInt32 SetFftCalcDirection(DiSession devHandle,DiUInt32 fftDirection)
{
	fftDirection=!!fftDirection;
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,FFTDIRECTIONADDR,&iData);

	//0 bit set 0
	iData &=  0xfffffffe;
	iData |= fftDirection;
	
	//insert
	iBack = BitWrite32(devHandle,FFTDIRECTIONADDR,iData);
	if(iBack < 0)
	  iBack = SA_FFTDirection;
	return iBack;
}

/*
purpose:fft start index
func:SetFftValidStartNum
param:<in>devHandle:dev's ctrl handle from ini
      <in>fftvalidstartNum:start index
return:>=0 is ok
 */
DiInt32 SetFftValidStartNum(DiSession devHandle,DiUInt32 fftvalidstartNum)
{
	fftvalidstartNum &= 0x0000ffff;
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,FFTVALIDNUMPROADDR,&iData);

	//0~15 bit set 0
	iData &=  0xffff0000;
	iData |= fftvalidstartNum;

	//insert
	iBack = BitWrite32(devHandle,FFTVALIDNUMPROADDR,iData);
	if(iBack < 0)
	  iBack = SA_FFTVALIDSTANum;
	return iBack;
}

/*
purpose:fft end index
func:SetFftValidEndNum
param:<in>devHandle:dev's ctrl handle from ini
      <in>fftvalidendNum:end index
return:>=0 is ok
 */
DiInt32 SetFftValidEndNum(DiSession devHandle,DiUInt32 fftvalidendNum)
{
	fftvalidendNum &= 0x0000ffff;
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,FFTVALIDNUMPROADDR,&iData);

	//16~31 bit set 0
	iData &=  0x0000ffff;
	iData |= (fftvalidendNum << 16);

	//insert
	iBack = BitWrite32(devHandle,FFTVALIDNUMPROADDR,iData);
	if(iBack < 0)
	  iBack = SA_FFTVALIDENDNum;
	return iBack;
}

/*
purpose:fft dot sweep time
func:SetFftDotSwpTime
param:<in>devHandle:dev's ctrl handle from ini
      <in>fftdotswpTime:time
return:>=0 is ok//0801 
 */

DiInt32 SetFftDotSwpTime(DiSession devHandle,DiReal64 fftdotswpTime)
{
	//get the ori data
	DiUInt32 iDataFrac = 0;
	DiUInt32 iDataInt  = 0;
	DiInt32 iBack = BitRead32(devHandle,FFTDOTSWPTIMEADDRFRAC,&iDataFrac);
	iBack = BitRead32(devHandle,FFTDOTSWPTIMEADDRINT,&iDataInt);

	iDataInt = (DiUInt32)(fftdotswpTime * 46080.0);
	iBack = BitWrite32(devHandle,FFTDOTSWPTIMEADDRINT,iDataInt);

	DiUInt32 frac = (DiUInt32)((fftdotswpTime * 46080.0 - iDataInt) * 0xff);
	iDataFrac &= 0xffffff00;
	iDataFrac |= frac;

	iBack = BitWrite32(devHandle,FFTDOTSWPTIMEADDRFRAC,iDataFrac);

	if(iBack < 0)
	  iBack = SA_FFTDOTSWPTime;
	return iBack;
}

/*
purpose:before dector trig time
func:SetBucketTrigDelayTime
param:<in>devHandle:dev's ctrl handle from ini
      <in>buckettrigTime:time,us
return:>=0 is ok
 */
DiInt32 SetBucketTrigDelayTime(DiSession devHandle,DiReal64 buckettrigTime)
{
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,BUCKETTRIGTIMEADDR,&iData);

	//0~31 bit set 0
	iData &=  0;
	//back to 10MHz
	iData |= (DiUInt32)(buckettrigTime * 46.08);

	//insert
	iBack = BitWrite32(devHandle,BUCKETTRIGTIMEADDR,iData);
	if(iBack < 0)
	  iBack = SA_BUCKETTRIGTime;
	return iBack;
}

/*
purpose:rbw/vbw delay time
func:SetFirRbwvbwDelayTime
param:<in>devHandle:dev's ctrl handle from ini
      <in>rbwvbwdelayTime:time,us
return:>=0 is ok
 */
DiInt32 SetFirRbwvbwDelayTime(DiSession devHandle,DiReal64 rbwvbwdelayTime)
{
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,RBWVBWDELAYTIMEADDR,&iData);

	//0~31 bit set 0
	iData &=  0;
	//back to 10MHz
	iData |= (DiUInt32)(rbwvbwdelayTime * 46.08);
	
	//insert
	iBack = BitWrite32(devHandle,RBWVBWDELAYTIMEADDR,iData);

	if(iBack < 0)
	  iBack = SA_RBWVBWFIL_DELAYTime;
	return iBack;
}

/*
purpose:rbw/vbw delay time
func:SetFftRbwvbwDelayTime
param:<in>devHandle:dev's ctrl handle from ini
      <in>rbwvbwdelayTime:time,us
return:>=0 is ok
 */
DiInt32 SetFftRbwvbwDelayTime(DiSession devHandle,DiUInt32 rbwvbwdelayTime)
{
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,RBWVBWDELAYTIMEADDR,&iData);

	//0~31 bit set 0
	iData &=  0;
	//back to 45MHz
	iData |= (rbwvbwdelayTime * 45);
	
	//insert
	iBack = BitWrite32(devHandle,RBWVBWDELAYTIMEADDR,iData);
	if(iBack < 0)
	  iBack = SA_RBWVBWFIL_DELAYTime;
	return iBack;
}

DiInt32 GetrbwIndex(DiReal64 rbwHz)
{
	//check param
	DiInt32 iListLeng = sizeof(rbwList) / sizeof(DiReal64);
	iListLeng = iListLeng < 1 ? 1 : iListLeng;
	rbwHz = rbwHz > rbwList[0] ? rbwList[0] : rbwHz;
	rbwHz = rbwHz < rbwList[iListLeng - 1] ? rbwList[iListLeng - 1] : rbwHz;

	DiInt32 iIndex = 0;
	for(iIndex = 0; iIndex < iListLeng; iIndex++)
	{
		if(*(rbwList + iIndex) <= rbwHz)
			return iIndex;
	}
	return iIndex - 1;
}

/*
purpose:set fir bucket time
func:SetFirBucketTime
param:<in>devHandle:dev's ctrl handle from ini
      <in>bucketime:us
return:>=0 is ok
 */
//0507
DiInt32 SetFirBucketTime(DiSession devHandle,DiReal64 bucketime)
{
	DiInt32 iBack = 0;
	DiUInt64 isum = (DiUInt64)(bucketime * 46.08);
	DiUInt32 ifrac = (DiUInt32)((bucketime * 46.08 - isum) * 0xff);//Johnson 190131
	ifrac |= (isum << 8 & 0xffffff00);
	//set low eight bits	
	iBack = BitWrite32(devHandle,FIRBUCKETLOW,ifrac);
	//set else bits
	iBack = BitWrite32(devHandle,FIRBUCKETHIGH,isum >> 24 & 0xffffffff);
	if(iBack < 0)
	  iBack = SA_FIRBUcketTime;

	return iBack;
}

/*
purpose:get result data from local part
func:GetResultData
param:<in>devHandle:dev's ctrl handle from ini
      <in/out>pbuffer:data buffer
      <in>num: data nums
return:>=0 is ok
 */
DiInt32 GetResultData(DiSession devHandle,DiPUInt32 pbuffer,DiUInt32 num)
{	
	DiInt32 iBack = 0;
	iBack = BitMoveOut32(devHandle,PLLOCALMEMBASEADDR,num,pbuffer);
	if(iBack < 0)
	  iBack = SA_GETSPECData;
	return iBack;
}

/*
purpose:get detector time
func:GetDetectorTime
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 GetDetectorTime(DiSession devHandle)
{
	DiUInt32 num = 0;
	DiInt32 iBack = 0;
	iBack = BitRead32(devHandle,DETECTORTIMEADDR,&num);

	return num;
}

/*
purpose:get fsr
func:GetFsr
param:<in>devHandle:dev's ctrl handle from ini
return:fsr value
 */
DiInt32 GetFsr(DiSession devHandle)
{
	DiInt32 Fsr = 0;
	DiInt32 iBack = 0;
	iBack = BitRead32(devHandle,FSRGETADDR,&Fsr);
	
	return Fsr;
}

/*
purpose:set fsrGet start
func:SetFsrGetStart
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 SetFsrGetStart(DiSession devHandle)
{
	DiInt32 iBack = 0;
	iBack = BitWrite32(devHandle,FSRSTARTADDR,1);
	if(iBack<0) iBack = SA_FSRGet_Start;
	return iBack;
}

/*
purpose:set fsrGet stop
func:SetFsrGetStop
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 SetFsrGetStop(DiSession devHandle)
{
	DiInt32 iBack = 0;
	iBack = BitWrite32(devHandle,FSRSTOPADDR,1);
	if(iBack<0) iBack = SA_FSRGet_Stop;
	return iBack;
}

/*
perpose:set trigger mode
func:SetTriggerMode
param:<in>devHandle:dev's ctrl handle from ini
param:<in>triggermode:trigger mode
return:>=0 is ok
*/
DiInt32 SetTriggerMode(DiSession devHandle,DiUInt32 triggermode)
{
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,TRIGTYPEANDDIRECTADDR,&iData);

	//0~1 bit set 0
	iData &=  0xfffffff8;
	iData |= triggermode;

	//insert
	iBack = BitWrite32(devHandle,TRIGTYPEANDDIRECTADDR,iData);
	if(iBack < 0)
	  iBack = SA_TRIGType;
	return iBack;
}

/*
perpose:set trigger direct
func:SetTriggerDirect
param:<in>devHandle:dev's ctrl handle from ini
param:<in>SetTriggerDirect:trigger direct
return:>=0 is ok
*/
DiInt32 SetTriggerDirect(DiSession devHandle,DiUInt32 triggerdirect)
{
	triggerdirect &=0x00000001;
	triggerdirect = !!triggerdirect;
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,TRIGTYPEANDDIRECTADDR,&iData);

	//2 bit set 0
	iData &=  0xfffffff7;
	iData |= (triggerdirect<<3);
	
	//insert
	iBack = BitWrite32(devHandle,TRIGTYPEANDDIRECTADDR,iData);
	if(iBack < 0)
	  iBack = SA_TRIGDirect;
	return iBack;
}

/*
perpose:set trigger delay time
func:SetTriggerDelayTime
param:<in>devHandle:dev's ctrl handle from ini
param:<in>triggerdelaytime:trigger delay time
return:>=0 is ok
*/
DiInt32 SetTriggerDelayTime(DiSession devHandle,DiReal64 triggerdelaytime)
{
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,TRIGTIMEADDR,&iData);

	//0~31 bit set 0
	iData &=  0;
	iData |= (DiUInt32)(triggerdelaytime*46080.0);
		
	//insert
	iBack = BitWrite32(devHandle,TRIGTIMEADDR,iData);
	if(iBack < 0)
	  iBack = SA_TRIGTIME;
	return iBack;
}

/*
perpose:set vedio trigger amplitude
func:SetVedioTriggerAmp
param:<in>devHandle:dev's ctrl handle from ini
param:<in>vediotriggeramp:vedio trigger amplitude
return:>=0 is ok
*/
DiInt32 SetVedioTriggerAmp(DiSession devHandle,DiInt32 vediotriggeramp)
{
	DiInt32 iBack = 0;
	iBack = BitWrite32(devHandle,VEDIOTRIGAMPADDR,vediotriggeramp);
	if(iBack < 0)
		iBack = SA_VEDIOTRIGAmp;	
	return iBack;
}

/*
perpose:set trigger per time
func:SetTriggerPerTime
param:<in>devHandle:dev's ctrl handle from ini
param:<in>triggerpertime:trigger per time
return:>=0 is ok
*/
DiInt32 SetTriggerPerTime(DiSession devHandle,DiReal64 triggerpertime)
{
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,TRIGPERTIMEADDR,&iData);

	//0~31 bit set 0
	iData &=  0;
	iData |= (DiUInt32)(triggerpertime*46080.0);
		
	//insert
	iBack = BitWrite32(devHandle,TRIGPERTIMEADDR,iData);
	if(iBack < 0)
	  iBack = SA_TRIGPERTIME;
	return iBack;
}

/*
perpose:set RF Burst Trigger Amplitude
func:SetRFBurstTriggerAmp
param:<in>devHandle:dev's ctrl handle from ini
param:<in>triggerpertime:rf burst trigger amplitude
return:>=0 is ok
*/
DiInt32 SetRFBurstTriggerAmp(DiSession devHandle,DiInt32 refbursttriggeramp)
{
	DiInt32 iBack = 0;
	iBack = BitWrite32(devHandle,DOORCTL_RFBURST_TRIGLEVEL,refbursttriggeramp);
	if(iBack < 0)
		iBack = SA_RFBURSTTRIGAmp;	
	return iBack;
}

//*************Door Control Sweep
/*
perpose:set Door Control Source
func:SetDoorControlSourceSelect
param:<in>devHandle:dev's ctrl handle from ini
param:<in>triggerMode:[2:0]0 extern_trigger 1 RF_trigger 2 period_trigger
return:>=0 is ok
*/
DiInt32 SetDoorControlSourceSelect(DiSession devHandle,DiUInt32 triggerMode)
{
	DiInt32 iData = 0;
	DiUInt32 iBack = BitRead32(devHandle,DOORCTL_SWEEPADDR,&iData);

	iData &= 0xfffffff8;
	iData |= triggerMode;

	iBack = BitWrite32(devHandle,DOORCTL_SWEEPADDR,iData);
	if(iBack < 0)
		iBack = SA_GateSweep_Source;
	return iBack;
}

/*
perpose:Level or Edge Select
func:SetLevelEdgeSelect
param:<in>devHandle:dev's ctrl handle from ini
param:<in>selectControlWord:[5]0 edge 1 level
return:>=0 is ok
*/
DiInt32 SetLevelEdgeSelect(DiSession devHandle,DiUInt32 selectControlWord)
{
	DiInt32 iData = 0;
	DiUInt32 iBack = BitRead32(devHandle,DOORCTL_SWEEPADDR,&iData);

	iData &= 0xffffffdf;
	iData |= (DiUInt32)(selectControlWord<<5);

	iBack = BitWrite32(devHandle,DOORCTL_SWEEPADDR,iData);
	if(iBack < 0)
		iBack = SA_GateSweep_Control;
	return iBack;
}

/*
perpose:Level and Edge mode set
func:SetLevelEdgeMode
param:<in>devHandle:dev's ctrl handle from ini
param:<in>mode:[4] 0 low 1 high
return:>=0 is ok
*/
DiInt32 SetLevelEdgeMode(DiSession devHandle,DiUInt32 mode)
{
	DiInt32 iData = 0;
	DiUInt32 iBack = BitRead32(devHandle,DOORCTL_SWEEPADDR,&iData);

	iData &= 0xffffffef;
	iData |= (DiUInt32)(mode<<4);

	iBack = BitWrite32(devHandle,DOORCTL_SWEEPADDR,iData);
	if(iBack < 0)
		iBack = SA_GateSweep_ControlValue;
	return iBack;
}

/*
perpose:Door Control Sweep Mode Select
func:SetDoorControlSweepModeSelect
param:<in>devHandle:dev's ctrl handle from ini
param:<in>sweepMode:[9:8]0 lo 1 vedio 2 fft
return:>=0 is ok
*/
DiInt32 SetDoorControlSweepModeSelect(DiSession devHandle,DiUInt32 sweepMode)
{
	DiInt32 iData = 0;
	DiUInt32 iBack = BitRead32(devHandle,DOORCTL_SWEEPADDR,&iData);

	iData &= 0xfffffcff;
	iData |= (DiUInt32)(sweepMode<<8);

	iBack = BitWrite32(devHandle,DOORCTL_SWEEPADDR,iData);
	if(iBack < 0)
		iBack = SA_GateSweep_GateMethod;
	return iBack;
}

/*
perpose:Period Trigger Door Control Synchro Source Select
func:SetPrdTrgSynchroSrcSelect
param:<in>devHandle:dev's ctrl handle from ini
param:<in>sourceMode:[14:12]0 noSouce 1 externTrigger 2 RFBurst
return:>=0 is ok
*/
DiInt32 SetPrdTrgSynchroSrcSelect(DiSession devHandle,DiUInt32 sourceMode)
{
	DiInt32 iData = 0;
	DiUInt32 iBack = BitRead32(devHandle,DOORCTL_SWEEPADDR,&iData);

	iData &= 0xffff8fff;
	iData |= (DiUInt32)(sourceMode<<12);

	iBack = BitWrite32(devHandle,DOORCTL_SWEEPADDR,iData);
	if(iBack < 0)
		iBack = SA_GateSweep_SynSrc;
	return iBack;
}

/*
perpose:Door Control Sweep Switch
func:SetDoorControlSwitch
param:<in>devHandle:dev's ctrl handle from ini
param:<in>switchMode:[31]0 close 1 open
return:>=0 is ok
*/
DiInt32 SetDoorControlSwitch(DiSession devHandle,DiUInt32 switchMode)
{
	DiInt32 iData = 0;
	DiUInt32 iBack = BitRead32(devHandle,DOORCTL_SWEEPADDR,&iData);

	iData &= 0x7fffffff;
	iData |= (DiUInt32)(switchMode<<31);

	iBack = BitWrite32(devHandle,DOORCTL_SWEEPADDR,iData);
	if(iBack < 0)
		iBack = SA_GateSweep_Gate;
	return iBack;
}

/*
perpose:Edge Trigger Trigger_Delay
func:SetEdgTrigDely
param:<in>devHandle:dev's ctrl handle from ini
param:<DiReal64>triggerDelay:[31:0]ms
return:>=0 is ok
*/
DiInt32 SetEdgTrigDely(DiSession devHandle,DiReal64 triggerDelay)
{
	DiInt32 iData = 0;
	DiUInt32 iBack = BitRead32(devHandle,DOORCTL_EDG_TRIGDLYADDR,&iData);

	iData &= 0;
	iData |= (DiUInt32)(triggerDelay*46080);

	iBack = BitWrite32(devHandle,DOORCTL_EDG_TRIGDLYADDR,iData);
	if(iBack < 0)
		iBack = SA_GateSweep_GateDelay;
	return iBack;
}

/*
perpose:Edge Trigger Door_Width
func:SetEdgTrigDoorWdth
param:<in>devHandle:dev's ctrl handle from ini
param:<DiReal64>doorWidth:[31:0]ms
return:>=0 is ok
*/
DiInt32 SetEdgTrigDoorWdth(DiSession devHandle,DiReal64 doorWidth)
{
	DiInt32 iData = 0;
	DiUInt32 iBack = BitRead32(devHandle,DOORCTL_EDG_DOORWDTHADDR,&iData);

	iData &= 0;
	iData |= (DiUInt32)(doorWidth*46080);

	iBack = BitWrite32(devHandle,DOORCTL_EDG_DOORWDTHADDR,iData);
	if(iBack < 0)
		iBack = SA_GateSweep_GateLength;
	return iBack;
}

/*
perpose:Edge Trigger Trigger_Prevent_Status
func:SetEdgTrigPrvntStatus
param:<in>devHandle:dev's ctrl handle from ini
param:<DiUInt32>preventStatus:[31] 0 close 1 open
return:>=0 is ok
*/
DiInt32 SetEdgTrigPrvntStatus(DiSession devHandle,DiUInt32 preventStatus)
{
	DiInt32 iData = 0;
	DiUInt32 iBack = BitRead32(devHandle,DOORCTL_EDG_PREVENTTMADDR,&iData);

	iData &= 0x7fffffff;
	iData |= (DiUInt32)(preventStatus<<31);

	iBack = BitWrite32(devHandle,DOORCTL_EDG_PREVENTTMADDR,iData);
	if(iBack < 0)
		iBack = SA_GateSweep_PreventStatus;
	return iBack;
}

/*
perpose:Edge Trigger Trigger_Prevent_Times
func:SetEdgTrigPrvntTimes
param:<in>devHandle:dev's ctrl handle from ini
param:<DiReal64>preventTimes:[29:0]ms
return:>=0 is ok
*/
DiInt32 SetEdgTrigPrvntTimes(DiSession devHandle,DiReal64 preventTimes)
{
	DiInt32 iData = 0;
	DiUInt32 iBack = BitRead32(devHandle,DOORCTL_EDG_PREVENTTMADDR,&iData);

	iData &= 0xc0000000;
	iData |= (DiUInt32)(preventTimes*46080);

	iBack = BitWrite32(devHandle,DOORCTL_EDG_PREVENTTMADDR,iData);
	if(iBack < 0)
		iBack = SA_GateSweep_PreventTime;
	return iBack;
}

/*
perpose:Period Trigger Trigger_Period
func:SetPrdTrgPeriod
param:<in>devHandle:dev's ctrl handle from ini
param:<DiReal64>triggerPeriod:[31:0]ms
return:>=0 is ok
*/
DiInt32 SetPrdTrgPeriod(DiSession devHandle,DiReal64 triggerPeriod)
{
	DiInt32 iData = 0;
	DiUInt32 iBack = BitRead32(devHandle,TRIGPERTIMEADDR,&iData);

	iData &= 0;
	iData |= (DiUInt32)(triggerPeriod*46080);

	iBack = BitWrite32(devHandle,TRIGPERTIMEADDR,iData);
	if(iBack < 0)
		iBack = SA_GateSweep_Period;
	return iBack;
}

/*
perpose:Period Trigger Source_Delay
func:SetPrdTrgSrcDelay
param:<in>devHandle:dev's ctrl handle from ini
param:<DiReal64>sourceDelay:[31:0]ms
return:>=0 is ok
*/
DiInt32 SetPrdTrgSrcDelay(DiSession devHandle,DiReal64 sourceDelay)
{
	DiInt32 iData = 0;
	DiUInt32 iBack = BitRead32(devHandle,DOORCTL_PRD_SRCDLYADDR,&iData);

	iData &= 0;
	iData |= (DiUInt32)(sourceDelay*46080);

	iBack = BitWrite32(devHandle,DOORCTL_PRD_SRCDLYADDR,iData);
	if(iBack < 0)
		iBack = SA_GateSweep_PerTrig_SrcDelay;
	return iBack;
}

/*
perpose:Period Trigger Trigger_Prevent_Status
func:SetPrdTrigPrvntStatus
param:<in>devHandle:dev's ctrl handle from ini
param:<DiUInt32>preventStatus:[31] 0 close 1 open
return:>=0 is ok
*/
DiInt32 SetPrdTrigPrvntStatus(DiSession devHandle,DiUInt32 preventStatus)
{
	DiInt32 iData = 0;
	DiUInt32 iBack = BitRead32(devHandle,DOORCTL_PRD_PREVENTTMADDR,&iData);

	iData &= 0x7fffffff;
	iData |= (DiUInt32)(preventStatus<<31);

	iBack = BitWrite32(devHandle,DOORCTL_PRD_PREVENTTMADDR,iData);
	if(iBack < 0)
		iBack = SA_GateSweep_PerTrig_PrvStatus;
	return iBack;
}

/*
perpose:Period Trigger Trigger_Prevent_Times
func:SetPrdTrigPrvntTimes
param:<in>devHandle:dev's ctrl handle from ini
param:<DiReal64>preventTimes:[29:0]ms
return:>=0 is ok
*/
DiInt32 SetPrdTrigPrvntTimes(DiSession devHandle,DiReal64 preventTimes)
{
	DiInt32 iData = 0;
	DiUInt32 iBack = BitRead32(devHandle,DOORCTL_PRD_PREVENTTMADDR,&iData);

	iData &= 0xc0000000;
	iData |= (DiUInt32)(preventTimes*46080);

	iBack = BitWrite32(devHandle,DOORCTL_PRD_PREVENTTMADDR,iData);
	if(iBack < 0)
		iBack = SA_GateSweep_PerTrig_PrvTime;
	return iBack;
}

/*
perpose:RFBurst Trigger Level
func:SetRFBurstTrigLevel
param:<in>devHandle:dev's ctrl handle from ini
param:<DiInt32>trigLevel:32bit dBm
return:>=0 is ok
*/
DiInt32 SetRFBurstTrigLevel(DiSession devHandle,DiInt32 trigLevel)
{
	DiInt32 iData = 0;
	DiUInt32 iBack = BitRead32(devHandle,DOORCTL_RFBURST_TRIGLEVEL,&iData);

	iData &= 0;
	iData |= trigLevel;

	iBack = BitWrite32(devHandle,DOORCTL_RFBURST_TRIGLEVEL,iData);
	if(iBack < 0)
		iBack = SA_GateSweep_RFBurst_TrigLevl;
	return iBack;
}

/*
perpose:Test DAC OverRange
func:SetDACOverRangeTest
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
*/
DiInt32 SetDACOverRangeTest(DiSession devHandle)
{
	DiInt32 iData = 0;
	DiUInt32 iBack = BitRead32(devHandle,ADC_OVERRANGE_TESTADDR,&iData);

	if(iData == 1)
	{
		iBack = BitWrite32(devHandle,ADC_OVERRANG_CLEARADDR,1);
		//if(iBack < 0)
			//iBack = SA_GateSweep_PerTrig_PrvStatus;
	}
	
	return iBack;
}
