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
#include "BitSehInfo.h"
#include <math.h>
#include <unistd.h>
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
#define FFTDOTSWPTIMEADDR 0x80000180/*bit:0~31*/
#define BUCKETTRIGTIMEADDR 0x80000190/*bit:0~31*/
#define RBWVBWDELAYTIMEADDR 0x800001A0/*bit:0~31*/
#define TRIGTYPEANDDIRECTADDR   0x800001B0/*TRIGTYPE: 00 free trig;01 level trig;10 video trig*/
#define TRIGTIMEADDR 0x800001C0 /*bit:0~31*/
#define TRIGAMPADDR 0x800001D0 /*bit:0~31*/

#define TRIGSWEEPINTERPADDR 0x800001E0 /*set 1 ,then set 0*/

#define SEGSWEEPNUMADDR 0x80000230/*zero span set 0*/


#define PLLOCALMEMBASEADDR 0x80010000

//Albert 09/04/04   for real-time FPGA
#define RTSA_FPGA_CMD_START_ADDR    			0x80000010 	/* bit: 0~7  */
#define RTSA_FPGA_CMD_STOP_ADDR					0x80000020	/* bit: 0~7  */
#define RTSA_INTERRUPT_CMD_ADDR					0x80000030	/* bit: 0~7  */

#define RTSA_FFT_LEGTH											0x80000200		
#define RTSA_RBW_ARRD											0x80000210 	/*bit:0~3 0000:32pts 0001:64pts 0010:128pts 0011:256pts 0100:512pts 0101:1024pts 0110: 2048pts*/
#define RTSA_DETECTOR_ADDR								0x80000220 	/*bit:0~3 0000:Pos 0001:Neg Pos 0010:Sample 0011:Aerage 0100:RMS*/
#define RTSA_SPAN_ADDR											0x80000230	/*bit:0~7 0:100M 1:50M 2:20M 3:10M 4:5M 5:2M 6:1M 7:500K 8:200K 9:100K 10:50K 11:20K 12:10K 13:5K 14:2K*/
#define RTSA_FFT_WINDOW_ADDR							0x80000240	/*bit:0~7 0:hanning 1:flattop 2:gausian 3:rectangular 4:kaiser 5 blackman-harris*/
#define RTSA_ACQTIME_ADDR									0x80000250	/*bit:0~31*/
#define RTSA_MEAN_FACTOR_ADDR						0x80000260	/*bit:0~31 8 exponential bits, 23 decimal places, 1 symbol bit */
#define RTSA_FFT_BUCKET_NUM_ADDR					0x80000270	/*bit:0~31 High 16-bit corresponding integer part, lower 16-bit decimal part */
#define RTSA_FFT_VALID_NUM_START_STOP_ADDR		0x80000280 /*bit:0~31 0~15:start_addr  16~31:stop_addr*/
#define RTSA_MEAN_FACTOR1									0x80000290
#define RTSA_MEAN_FACTOR2									0x800002A0
#define RTSA_TRIGGER_MODE 									0x800002B0
#define RTSA_TRIGGER_PERIOD								0x800002C0
#define RTSA_TRIGGER_DELAY									0x800002D0
#define RTSA_TRIGGER_HIDE_TIME						0x800002E0
#define RTSA_TRIGGER_RF_BURST_HIGH				0x80000300
#define RTSA_TRIGGER_RF_BURST_LOW				0x800002F0


#define RTSA_TRIGGER_VIEDO_LEVEL					0x80000310

#define RTSA_TRIGGER_SLOPE								    0x80000330

#define RTSA_DC_ELIMIT											0x80000150

#define RTSA_GAIN_COMP_ADDR								0x86001000	/*bit:0~31  4001 float*/
//////////Albert 19/04/04


//Albert add rtsa IF 
#define RTSA_IF_BANDWIDTH								0x80001080		

#define RTSA_DSP_STATUS									0x8400001C

 



#define RTSA_AD_RATIO										(0.73 /8192.0);

#define RTSA_I_Q_RATIO										(0.78 /8192.0);


const Rtsa_fft_Param RTSA_FFT_Param[] = 
{
		{184320000.0,	1.112e0-5,   1111, 0x00016333,   469,  1579,		1.0,	0.5},
		{92160000.0,		2.223e-5,    1111, 0x00016333,   469,  1579,		1.0,	0.5},
		{46080000.0,		4.445e-5,    889,  0x00011c28,    580,  1468,		1.0,	0.5},
		{18432000.0,    	1.112e-4,	1111, 0x00016333,   469,  1579,		1.0,	0.5},
		{9216000.0,		2.223e-5,   	1111, 0x00016333,   469,  1579,		1.0,	0.5},
		{3686400.0,		5.556e-4,   1111, 0x00016333,   469,  1579,		1.0,	0.5},
		{1843200.0,		1.112e-3,   1111, 0x00016333,   469,  1579,		1.0,	0.5},
		{921600.0,			2.223e-3,   1111, 0x00016333,   469,  1579,		1.0,	0.5},
		{368640.0,  		5.556e-3,   1111, 0x00016333,   469,  1579,		1.0,	0.5},
		{184320.0,  		1.112e-2,   1111, 0x00016333,   469,  1579,		1.0,	0.5},
		{92160.0,  			2.223e-2,   1111, 0x00016333,   469,  1579,		1.0,	0.5},
		{36864.0,   			5.556e-2,   1111, 0x00016333,   469,  1579,		1.0,	0.5},
		{18432.0,   			0.112,		   1111, 0x00016333,   469,  1579,		1.0,	0.5},
		{9216.0,    			0.223,		   1111, 0x00016333,   469,  1579,		1.0,	0.5},
		{3686.4,        		0.556,			1111, 0x00016333,   469,  1579,		1.0,	0.5},
		{1843.2,        		1.112,			1111, 0x00016333,   469,  1579,		1.0,	0.5},
		{921.6,         		2.223,			1111, 0x00016333,   469,  1579,		1.0,	0.5}
};
const DiReal32 spanList[] = 
{
	100000000.0, 
	50000000.0, 
	20000000.0, 
	10000000.0, 
	5000000.0, 
	2000000.0,
   	1000000.0, 
   	500000.0, 
   	200000.0, 
   	100000.0, 
   	50000.0, 
   	20000.0, 
   	10000.0, 
   	5000.0,
   	2000.0, 
   	1000.0, 
   	500.0
   	/*, 200.0, 100.0*/
	};
;
const DiReal64 SampleSpeed[] = 
{
	184320000.0, 
	92160000.0, 
	46080000.0, 
	18432000.0, 
	9216000.0, 
	3686400.0, 
	1843200.0, 
	921600.0, 
	368640.0, 
	184320.0, 
	92160.0, 
	36864.0 ,
	18432.0, 
	9216.0, 
	3686.4, 
	1843.2, 
	921.6	
};

#define FFT_OVERLAP_NUM    							3

////////////////////////////////////////////////////////////////////////////////////////////////
const DiReal64 rbwList[] = {5.0e6,3.0e6,1.0e6,3.0e5,1.0e5,3.0e4,1.0e4,3000,1000,300,100,30, 10, 3, 1};

extern const DiReal64 freqChannelList[];
extern DiInt32 GetFreqChannelIndex(DiReal64 freqHz);

static const DiInt32  CHECKMODEMAX = 5;//dector max nums

const int checkclockcircle = 100;//ns
DiInt32 GetrbwIndex(DiReal64 rbwHz);

//Albert 19/04/28
static DiInt32 SpanIndex = 0;

extern int firstInterrupt;
////////////////////////////////////////////////////////////////////////////////////////////////
/*
purpose:set last sweep band
func:SetLastBandCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <int>flag:0 not last,1 last
return:>=0 is ok
 */
//steve 0504
//DiInt32 SetLastBandCtrl(DiSession devHandle,DiUInt32 flag)
//{
//	flag = !!flag;
//	DiInt32 iBack = BitWrite32(devHandle,ENDBANDFLAG,flag);	
//	if(iBack < 0)
//	  iBack = RTSA_LASTBand;
//	return iBack;
//}

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
	  iBack = RTSA_SEGPoint;

	//printf("The number of sweep point is %d******************************\n",pointsnum);//Johnson 190322

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
//	  if(iBack < 0)
//	    iBack = RTSA_RBW;
	return iBack;
}

/*
purpose:set vbw
func:SetVbw
param:<in>devHandle:dev's ctrl handle from ini
      <in>vbwValue:the rbw value    
return:>=0 is ok
 */
//DiInt32 SetVbw(DiSession devHandle,DiReal64 vbwValue)
//{
//	//get the ori data
//	DiUInt32 iData = 0;
//	DiInt32 iBack = BitRead32(devHandle,RBWVBWADDR,&iData);
//	DiInt32 iIndex = GetrbwIndex(vbwValue);  
//	// 4-7 bit set 0
//	iData &= 0xffffff0f;
//	iData |= ((iIndex & 0xf) << 4);
//	//insert
//	iBack = BitWrite32(devHandle,RBWVBWADDR,iData);
//	if(iBack < 0)
//	  iBack = RTSA_VBW;
//	return iBack;

//}

/*
purpose:set detector mode
func:SetDetectormode
param:<in>devHandle:dev's ctrl handle from ini
      <in>checkMode:check mode   
return:>=0 is ok
 */
//DiInt32 SetDetectormode(DiSession devHandle,DiUInt32 checkMode)
//{
//	checkMode &= 0x0000000f;
//	checkMode = checkMode > CHECKMODEMAX ? CHECKMODEMAX : checkMode;
//	//get the ori data
//	DiUInt32 iData = 0;
//	DiInt32 iBack = BitRead32(devHandle,DETECTORMODEADDR,&iData);

//	// 0~3 bit set 0
//	iData &=  0xfffffff0;
//	iData |= checkMode;

//	//insert
//	iBack = BitWrite32(devHandle,DETECTORMODEADDR,iData);
//	if(iBack < 0)
//	  iBack = RTSA_DETECTORMode;
//	return iBack;
//}

/*
purpose:set data proc mode
func:SetDataprocMode
param:<in>devHandle:dev's ctrl handle from ini
      <in>dataproMode:data proc mode   
return:>=0 is ok
 */
//DiInt32 SetDataProcMode(DiSession devHandle,DiUInt32 dataproMode)
//{
//	dataproMode &= 0x00000003;

//get the ori data
//	DiUInt32 iData = 0;
//	DiInt32 iBack = BitRead32(devHandle,DATAPROCMODEADDR,&iData);

//	// 0~1 bit set 0
//	iData &=  0xfffffffc;
//	iData |= dataproMode;

//	//insert
//	iBack = BitWrite32(devHandle,DATAPROCMODEADDR,iData);
//	if(iBack < 0)
//	  iBack = RTSA_DATAPROMode;
//	return iBack;  
//}

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
	  iBack = RTSA_SWPStart;
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
	  iBack = RTSA_SWPStop;
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
	//if(iBack < 0)
	//  iBack = SA_SWPStop;

	iData &=  0xfffffffe;
	iData |= 0;   
	iBack = BitWrite32(devHandle,TRIGSWEEPINTERPADDR,iData);
	//if(iBack < 0)
	//  iBack = SA_SWPStop;

	return iBack;
}

/*
purpose:used in wave check,get seg num
func:SetCheckSegNum
param:<in>devHandle:dev's ctrl handle from ini
      <in>segNum:seg num
return:>=0 is ok
 */
//DiInt32 SetCheckSegNum(DiSession devHandle,DiUInt32 segNum)
//{
//	segNum &= 0x1f;
//	DiUInt32 iData = 0;
//	DiInt32 iBack = BitRead32(devHandle,CHECKSEGNUMADDR,&iData);
//	
//	iData &= 0xffffffe0;
//	//bit0~4
//	iBack = BitWrite32(devHandle,CHECKSEGNUMADDR,iData);
//	if(iBack < 0)
//	  iBack = RTSA_CHECKSegNum;
//	return iBack;
//}

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
	  iBack = RTSA_ZEROSPANFlag;
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
	iData |= (DiUInt32)(dotswpTime * 10); 
	//insert
	iBack = BitWrite32(devHandle,DOTSWPTIMEADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_DOTSWPTime;

	return iBack;
}

//0505
//steve
DiInt32 SetTotalSwtTimeUs(DiSession devHandle,DiReal64 sumTime)
{
	DiInt32 iBack = 0;
	DiUInt64 isum = (DiUInt64)ceil(sumTime * 10);
	//set low bits
	iBack = BitWrite32(devHandle,TOTALSWPTIMELOWADDR,isum & 0xffffffff);
	//set high bits
	iBack = BitWrite32(devHandle,TOTALSWPTIMEHIGHADDR,isum >> 32 & 0xffffffff);
	if(iBack < 0)
	  iBack = RTSA_TOTALSWPTime;

	//printf("The total sweep time is %f,the send data is %ld***************************\n",sumTime,isum);

	return iBack;
}

/*
purpose:set one seg sweep time
func:SetTotalSwpTimeLow
param:<in>devHandle:dev's ctrl handle from ini
      <in>totalswptimeLow:time   
return:>=0 is ok
 */
DiInt32 SetTotalSwpTimeLow(DiSession devHandle,DiUInt32 totalswptimeLow)
{ 
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,TOTALSWPTIMELOWADDR,&iData);
	// 0~31 bit set 0
	iData &=  0x0;
	iData |= totalswptimeLow; 
	//insert
	iBack = BitWrite32(devHandle,TOTALSWPTIMELOWADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_TOTALSWPTime;
	return iBack;
}

/*
purpose:set one seg sweep time
func:SetTotalSwpTimeHigh
param:<in>devHandle:dev's ctrl handle from ini
      <in>totalswptimeHigh:time   
return:>=0 is ok
 */
DiInt32 SetTotalSwpTimeHigh(DiSession devHandle,DiUInt32 totalswptimeHigh)
{
	//high 16 bits set 0
	totalswptimeHigh &= 0xffff;
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,TOTALSWPTIMEHIGHADDR,&iData);

	// 0~15 bit set 0
	iData &= 0xffff0000;
	iData |= totalswptimeHigh;

	//insert
	iBack = BitWrite32(devHandle,TOTALSWPTIMEHIGHADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_TOTALSWPTime;
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
	  iBack = RTSA_DISPLAYNum;
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
	  iBack = RTSA_DATAADDRClr;
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
	  iBack = RTSA_FFTBUCKETNum;
//printf("fft bucket num 0x%0x\n",iData);
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
	  iBack = RTSA_DETECTORFlag;
	return iBack;
}

/*
purpose:set audio time
func:SetAudioTime
param:<in>devHandle:dev's ctrl handle from ini
      <in>audiotime:audio time
return:>=0 is ok
 */
//DiInt32 SetAudioTime(DiSession devHandle,DiUInt32 audiotime)
//{
//	audiotime &= 0x0000000f ;
//	//get the ori data
//	DiUInt32 iData = 0;
//	DiInt32 iBack = BitRead32(devHandle,ANALOGDEMOD,&iData);

//	// 0`3 bit set 0
//	iData &=  0xfffffff0;
//	iData |= audiotime;

//	//insert
//	iBack = BitWrite32(devHandle,ANALOGDEMOD,iData);
//	if(iBack < 0)
//	  iBack = RTSA_AUDIOTime;
//	return iBack;
//}

/*
purpose:set audio volume
func:SetAudioVolume
param:<in>devHandle:dev's ctrl handle from ini
      <in>audioVolume:volume
return:>=0 is ok
 */
//DiInt32 SetAudioVolume(DiSession devHandle,DiUInt32 audioVolume)
//{
//	audioVolume &= 0x0000ffff ;
//	//get the ori data
//	DiUInt32 iData = 0;
//	DiInt32 iBack = BitRead32(devHandle,ANALOGDEMOD,&iData);

//	// 4`19 bit set 0
//	iData &=  0xfff0000f;
//	iData |= (audioVolume<<4);
//	 
//	//insert
//	iBack = BitWrite32(devHandle,ANALOGDEMOD,iData);
//	if(iBack < 0)
//	  iBack = RTSA_AUDIOVolume;
//	return iBack;
//}

/*
purpose:set demod type
func:SetAudioType
param:<in>devHandle:dev's ctrl handle from ini
      <in>audioType:type
return:>=0 is ok
 */
//DiInt32 SetAudioType(DiSession devHandle,DiUInt32 audioType)
//{
//	audioType &= 0x0000001f;
//	//get the ori data
//	DiUInt32 iData = 0;
//	DiInt32 iBack = BitRead32(devHandle,ANALOGDEMOD,&iData);

//	// 20`24 bit set 0
//	iData &=  0xfe0fffff;
//	iData |= (audioType << 20);
//	
//	//insert
//	iBack = BitWrite32(devHandle,ANALOGDEMOD,iData);
//	if(iBack < 0)
//	  iBack = RTSA_AUDIOType;
//	return iBack;
//}

/*
purpose:set demod enable
func:SetAudioEn
param:<in>devHandle:dev's ctrl handle from ini
      <in>audioEn:type
return:>=0 is ok
 */
//DiInt32 SetAudioEn(DiSession devHandle,DiUInt32 audioEn)
//{
//	audioEn =!!audioEn;
//	//get the ori data
//	DiUInt32 iData = 0;
//	DiInt32 iBack = BitRead32(devHandle,AUDIOENADDR,&iData);

//	//0 bit set 0
//	iData &=  0xfffffffe;
//	iData |= audioEn;
// 
//	//insert
//	iBack = BitWrite32(devHandle,AUDIOENADDR,iData);
//	if(iBack < 0)
//	  iBack = RTSA_AUDIOEn;
//	return iBack;
//}

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
	  iBack = RTSA_FFTCALNum;
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
	  iBack = RTSA_FFTDirection;
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
	  iBack = RTSA_FFTVALIDSTANum;
//printf("fft start index 0x%0x\n",iData);
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
	  iBack = RTSA_FFTVALIDENDNum;
//printf("fft stop index 0x%0x\n",iData);
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
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,FFTDOTSWPTIMEADDR,&iData);

	//0~31 bit set 0
	iData &=  0;
	iData = (DiUInt32)(fftdotswpTime * 45000.0);
	DiUInt32 frac = (DiUInt32)((fftdotswpTime * 45000.0 - iData) * 0xff);
	iData <<= 8;
	iData &= 0xffffff00;
	iData |= frac;

	//insert
	iBack = BitWrite32(devHandle,FFTDOTSWPTIMEADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_FFTDOTSWPTime;
//printf("fft dot time ms 0x%0x\n",iData);
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
	iData |= (DiUInt32)(buckettrigTime * 10);

	//insert
	iBack = BitWrite32(devHandle,BUCKETTRIGTIMEADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_BUCKETTRIGTime;
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
	iData |= (DiUInt32)(rbwvbwdelayTime * 10);
	
	//insert
	iBack = BitWrite32(devHandle,RBWVBWDELAYTIMEADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_RBWVBWFIL_DELAYTime;
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
	  iBack = RTSA_RBWVBWFIL_DELAYTime;
	return iBack;
}


/*
purpose:set trig type
func:SetTrigType
param:<in>devHandle:dev's ctrl handle from ini
      <in>trigType:trig type
return:>=0 is ok
 */
//DiInt32 SetTrigType(DiSession devHandle,DiUInt32 trigType)
//{
//	trigType &= 0x00000002;
//	//get the ori data
//	DiUInt32 iData = 0;
//	DiInt32 iBack = BitRead32(devHandle,TRIGTYPEANDDIRECTADDR,&iData);

//	//0~1 bit set 0
//	iData &=  0xfffffffc;
//	iData |= trigType;

//	//insert
//	iBack = BitWrite32(devHandle,TRIGTYPEANDDIRECTADDR,iData);
//	if(iBack < 0)
//	  iBack = RTSA_TRIGType;
//	return iBack;
//}

/*
purpose:set trig direction
func:SetTrigDirect
param:<in>devHandle:dev's ctrl handle from ini
      <in>trigDirect:direction
return:>=0 is ok
 */
//DiInt32 SetTrigDirect(DiSession devHandle,DiUInt32 trigDirect)
//{
//	trigDirect &=0x00000001;
//	trigDirect = !!trigDirect;
//	//get the ori data
//	DiUInt32 iData = 0;
//	DiInt32 iBack = BitRead32(devHandle,TRIGTYPEANDDIRECTADDR,&iData);

//	//2 bit set 0
//	iData &=  0xfffffffb;
//	iData |= (trigDirect << 2);
//	
//	//insert
//	iBack = BitWrite32(devHandle,TRIGTYPEANDDIRECTADDR,iData);
//	if(iBack < 0)
//	  iBack = RTSA_TRIGDirect;
//	return iBack;
//}

/*
purpose:set trig delay time
func:SetTrigDelayTime
param:<in>devHandle:dev's ctrl handle from ini
      <in>trigTime:delay time
return:>=0 is ok
 */
//DiInt32 SetTrigDelayTime(DiSession devHandle,DiUInt32 trigTime)
//{
//	//get the ori data
//	DiUInt32 iData = 0;
//	DiInt32 iBack = BitRead32(devHandle,TRIGTIMEADDR,&iData);

//	//0~31 bit set 0
//	iData &=  0;
//	iData |= trigTime;
//		
//	//insert
//	iBack = BitWrite32(devHandle,TRIGTIMEADDR,iData);
//	if(iBack < 0)
//	  iBack = RTSA_TRIGTIME;
//	return iBack;
//}

/*
purpose:set trig level
func:SetTrigLevel
param:<in>devHandle:dev's ctrl handle from ini
      <in>trigAmp:trig level
return:>=0 is ok
 */
//DiInt32 SetTrigLevel(DiSession devHandle,DiUInt32 trigAmp)
//{
//	//get the ori data
//	DiUInt32 iData = 0;
//	DiInt32 iBack = BitRead32(devHandle,TRIGAMPADDR,&iData);
//	//0~31 bit set 0
//	iData &=  0;
//	iData |= trigAmp;
//	//insert
//	iBack = BitWrite32(devHandle,TRIGAMPADDR,iData);
//	if(iBack < 0)
//	  iBack = RTSA_TRIGAmp;
//	return iBack;
//}

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
	iBack = BitWrite32(devHandle,FIRBUCKETHIGH,isum >> 32 & 0xffffffff);
	if(iBack < 0)
	  iBack = RTSA_FIRBUcketTime;

	//printf("The detector time is %f,the send data is %ud ******************************\n",bucketime,ifrac);//Johnson 190322
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
	  iBack = RTSA_GETSPECData;
	return iBack;
}
/*
purpose:set real time fpga start
func:SetRtSaFpgaStart
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 SetRtSaFpgaStart(DiSession devHandle)
{
	#if BIT_DEBUG
	return 0;
	#endif	
	DiInt32 iBack = 0;
	iBack = BitWrite32(devHandle,RTSA_FPGA_CMD_START_ADDR,0);
	if(iBack < 0)
	  iBack = RTSA_CTL_FPGA_START;
//	printf("fpga started!!!!\n");
    firstInterrupt = 0;
	return iBack;
}
/*
purpose:set real time fpga stop
func:SetRtSaFpgaStop
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 SetRtSaFpgaStop(DiSession devHandle)
{
	#if BIT_DEBUG
	return 0;
	#endif	
	DiInt32 iBack = 0;	
	DiInt32 DspStatus = 0;
	firstInterrupt = 0;
	DiInt32 retDspCheckCnt = 0;
//DSP Status 0- reset, 1- stop, 2- start, 4- ready
	iBack = BitWrite32(devHandle,RTSA_FPGA_CMD_STOP_ADDR,0);
//	printf("fpga stoped!!!!\n");
	while(1)
		{
			iBack = GetRtSaDspStatus(devHandle, &DspStatus);
			DspStatus &= 0x3;
			if(DspStatus == 1)
				{
				  	return iBack;
				}
		usleep(1000);
		iBack = BitWrite32(devHandle,RTSA_FPGA_CMD_STOP_ADDR,0);
		retDspCheckCnt ++;
		if(retDspCheckCnt > 200)
		    {
		    	iBack = RTSA_CTL_FPGA_STOP;
				return iBack;
		    }
		}
//	if(iBack < 0)
//	  iBack = RTSA_FPGA_STOP;
	return iBack;
}
/*
purpose:set real time fpga rbw
func:SetRtSaRBW
param:<in>devHandle:dev's ctrl handle from ini
			<in>rbwIndex:rbw set to FPGA
return:>=0 is ok
 */
DiInt32 SetRtSaRBW(DiSession devHandle,DiUInt32 rbwIndex)
{
	#if BIT_DEBUG
	printf("set rbw index   ++++++ %d\n",rbwIndex);
	return 0;
	#endif	
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,RTSA_RBW_ARRD,&iData);

	//convert the data to bit value
//	DiInt32 iIndex = GetrbwIndex(rbwValue);

	//low 4 bit set 0
	iData &= 0xfffffff0;
	iData |= (rbwIndex & 0xf);

	//insert
	iBack = BitWrite32(devHandle,RTSA_RBW_ARRD,iData);
	  if(iBack < 0)
	    iBack = RTSA_CTL_RBW;

	return iBack;
}
/*
purpose:set real time fpga dectector
func:SetRtSaDetector
param:<in>devHandle:dev's ctrl handle from ini
			<in>detectorIndex:detector set to FPGA
return:>=0 is ok
 */
DiInt32 SetRtSaDetector(DiSession devHandle,DiUInt32 detectorIndex)
{
	detectorIndex &= 0x0000000f;
	detectorIndex = detectorIndex > CHECKMODEMAX ? CHECKMODEMAX : detectorIndex;
	//get the ori data
	#if BIT_DEBUG
	printf("set detector index   ++++++ %d\n",detectorIndex);
	return 0;
	#endif	
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,RTSA_DETECTOR_ADDR,&iData);

	// 0~3 bit set 0
	iData &=  0xfffffff0;
	iData |= detectorIndex;

	//insert
	iBack = BitWrite32(devHandle,RTSA_DETECTOR_ADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_CTL_DECTECTOR;
	return iBack;
}
/*
purpose:set real time span
func:SetRtSaDetector
param:<in>devHandle:dev's ctrl handle from ini
			<in>span:real time span
return:>=0 is ok
 */
DiInt32 SetRtSaSpan(DiSession devHandle,DiReal64 Span)
{
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iListLeng = sizeof(spanList) / sizeof(DiReal32);
	DiInt32 i = 0;
	DiReal32 MeanFactor = 0.0;
	for(i = 0;i <iListLeng; i++ )
	{
		if((Span - spanList[i]) <= 0.00001 && ((Span - spanList[i]) >= -0.00001))
			{
				SpanIndex = i;
			}
	}
	#if BIT_DEBUG
	printf("Span------------    %f \n",Span);
	printf("set span index------------    %d \n",SpanIndex);

	iData = RTSA_FFT_Param[SpanIndex].fft_bucket_num;
	printf("set fft_bucket_num------------    %d \n",iData);

	// set valid start and stop index
	iData &=  0x0000ffff;
	iData = RTSA_FFT_Param[SpanIndex].fft_valid_stop;
	printf("set fft_valid_stop------------    %0x \n",iData);
	iData = iData << 16;
	iData |= RTSA_FFT_Param[SpanIndex].fft_valid_start;
	printf("set fft_valid_start------------    %0x \n",iData);

	MeanFactor = RTSA_FFT_Param[SpanIndex].fft_mean_factor1;
	printf("set fft_mean_factor1------------    %.2f \n",MeanFactor);

	MeanFactor = RTSA_FFT_Param[SpanIndex].fft_mean_factor2;
	printf("set fft_mean_factor2------------    %.2f \n",MeanFactor);
	
	return 0;
	#endif	
	DiInt32 iBack = BitRead32(devHandle,RTSA_SPAN_ADDR,&iData);

	// 0~3 bit set 0
	iData &=  0xffffff00;
	iData |= SpanIndex;
//	printf("set span index------------    %d \n",iData);

	//insert
	iBack = BitWrite32(devHandle,RTSA_SPAN_ADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_CTL_SPAN;

	// set bucket number
	iData = RTSA_FFT_Param[SpanIndex].fft_bucket_num;
	iBack = BitWrite32(devHandle,RTSA_FFT_BUCKET_NUM_ADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_CTL_BUCKET_NUM;

	// set valid start and stop index
	iData &=  0x0000ffff;
	iData = RTSA_FFT_Param[SpanIndex].fft_valid_stop;
	iData = iData << 16;
	iData |= RTSA_FFT_Param[SpanIndex].fft_valid_start;
	iBack = BitWrite32(devHandle,RTSA_FFT_VALID_NUM_START_STOP_ADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_CTL_VALID_STOP;

	//set mean factor 1 and 2
	MeanFactor = RTSA_FFT_Param[SpanIndex].fft_mean_factor1;
	iBack = BitWriteFloat32(devHandle,RTSA_MEAN_FACTOR1,MeanFactor);
	if(iBack < 0)
	  iBack = RTSA_CTL_VALID_STOP;

	MeanFactor = RTSA_FFT_Param[SpanIndex].fft_mean_factor2;
	iBack = BitWriteFloat32(devHandle,RTSA_MEAN_FACTOR2,MeanFactor);
	if(iBack < 0)
	  iBack = RTSA_CTL_VALID_STOP;

	return iBack;
}
/*
purpose:set real time fft window
func:SetRtSaFFTWindow
param:<in>devHandle:dev's ctrl handle from ini
			<in>fftWindowIndex:real time fft window index
return:>=0 is ok
 */
DiInt32 SetRtSaFFTWindow(DiSession devHandle,DiUInt32 fftWindowIndex)
{
	#if BIT_DEBUG
	printf("set fftWindowIndex index   ++++++ %d\n",fftWindowIndex);
	return 0;
	#endif	
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,RTSA_FFT_WINDOW_ADDR,&iData);

	// 0~3 bit set 0
	iData &=  0xfffffff0;
	iData |= fftWindowIndex;

	//insert
	iBack = BitWrite32(devHandle,RTSA_FFT_WINDOW_ADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_CTL_FFT_WINDOW;
	return iBack;
}
/*
purpose:set real time acq time 
func:SetRtSaAcqTime
param:<in>devHandle:dev's ctrl handle from ini
			<in>acqtime:real time acq time
return:>=0 is ok
 */
DiInt32 SetRtSaAcqTime(DiSession devHandle,DiReal32 acqtime)
{

	DiInt32 iBack = 0;
	DiUInt32 iTotalftFrame = 0;
	DiReal32 acqtime_s = 0.0;
	DiInt32 FftPointFromRbw = 32;
	DiReal32 MeanFactor = 0.0;
	//First set Acq time
	//change ms to s
	acqtime_s = (acqtime);
	
	//cal FFT time per frame
	acqtime_s = acqtime_s *  RTSA_FFT_Param[SpanIndex].SampleRate;
//	acqtime_s = acqtime_s *  RTSA_FFT_Param[0].SampleRate;
	// get fft points(32 ~ 2048)
	iTotalftFrame = (DiUInt32)(acqtime_s / 2048);
	iTotalftFrame &= 0xffffffff;

	#if BIT_DEBUG
	printf("acqtime  %f,     %f\n",acqtime,acqtime_s);
	
	printf("SetRtSaAcqTime  %0x\n",iTotalftFrame);
	//Second set mean factor should use 
	MeanFactor = 1.0 / (FFT_OVERLAP_NUM * iTotalftFrame);
	printf("mean factor   %0.9f\n",MeanFactor);
	return 0;
	#endif	
//	printf("SetRtSaAcqTime  %0x\n",iTotalftFrame);
#if BIT_NEW_ACQTIME
	acqtime_s = (acqtime);
	iTotalftFrame = (DiUInt32)(acqtime_s * 184320000);
	iTotalftFrame &= 0xffffffff;
#endif
	iBack = BitWrite32(devHandle,RTSA_ACQTIME_ADDR,iTotalftFrame);
	if(iBack < 0)
	  iBack = RTSA_CTL_ACQ_TIME;

	//Second set mean factor should use 
	MeanFactor = 1.0 /  (FFT_OVERLAP_NUM * iTotalftFrame);
//	printf("mean factor   %0.9f\n",MeanFactor);
	BitWriteFloat32(devHandle,RTSA_MEAN_FACTOR_ADDR,MeanFactor);
	if(iBack < 0)
	  iBack = RTSA_CTL_ACQ_TIME;	
	return iBack;
}
/*
purpose:set real time fft bucket num 
func:SetRtSaFFTBucketNum
param:<in>devHandle:dev's ctrl handle from ini
			<in>fftBucketNum:real time fft bucket number
return:>=0 is ok
 */
DiInt32 SetRtSaFFTBucketNum(DiSession devHandle,DiInt32 fftBucketNum)
{
	DiInt32 iBack = 0;
	
	return iBack;
}
/*
purpose:set rtsa fft length
func:SetRtSaFFTLength
param:<in>devHandle:dev's ctrl handle from ini
			<in>length:real time fft length
return:>=0 is ok
 */
DiInt32 SetRtSaFFTLength(DiSession devHandle, DiUInt32 length)
{
	DiInt32 iBack = 0;
		iBack = BitWrite32(devHandle,RTSA_FFT_LEGTH,2048);
//	if(iBack < 0)
//	  iBack = RTSA_FPGA_START;
	return iBack;	
}
/*
purpose:set real time if bandwidth
func:SetRtSaIFBandWidth
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 SetRtSaIFBandWidth(DiSession devHandle)
{
#if BIT_DEBUG
    return 0;
#endif
	DiInt32 iBack = 0;

	iBack = BitWrite32(devHandle,RTSA_IF_BANDWIDTH,0x1);
	if(iBack < 0)
	  iBack = RTSA_CTL_IFBW;	
	return iBack;
}
/*
purpose:set real time trigger type
func:SetRtSaTrigger
param:<in>devHandle:dev's ctrl handle from ini\
return:>=0 is ok
 */
DiInt32 SetRtSaTrigger(DiSession devHandle,DiUInt32 trigger)
{
#if BIT_DEBUG
    return 0;
#endif
	DiInt32 iBack = 0;
	DiUInt32 iData = trigger;
	iData = iData & 0xffff;
	
	iBack = BitWrite32(devHandle,RTSA_TRIGGER_MODE,iData);
	if(iBack < 0)
	  iBack = RTSA_CTL_TRIG_MODE;	
	
	return iBack;
}
/*
purpose:set real time trigger period
func:SetRtSaTriggerPeriod
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 SetRtSaTriggerPeriod(DiSession devHandle,DiUInt32 Period)
{
#if BIT_DEBUG
    return 0;
#endif
	DiInt32 iBack = 0;
	DiUInt32 iData = Period;
	iBack = BitWrite32(devHandle,RTSA_TRIGGER_PERIOD,iData);
	if(iBack < 0)
		iBack = RTSA_CTL_TRIG_PERIOD;	
	
	return iBack;
}
/*
purpose:set real time trigger delay
func:SetRtSaTriggerDelay
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 SetRtSaTriggerDelay(DiSession devHandle,DiUInt32 Delay)
{
#if BIT_DEBUG
    return 0;
#endif
	DiInt32 iBack = 0;
	DiUInt32 iData = Delay;
	iBack = BitWrite32(devHandle,RTSA_TRIGGER_DELAY,iData);
	if(iBack < 0)
		iBack = RTSA_CTL_TRIG_DELAY;	

	return iBack;
}
/*
purpose:set real time trigger hide time
func:SetRtSaTriggerPeriod
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 SetRtSaTriggerHideTime(DiSession devHandle,DiUInt32 time)
{
#if BIT_DEBUG
    return 0;
#endif
	DiInt32 iBack = 0;
	DiUInt32 iData = time;
	iBack = BitWrite32(devHandle,RTSA_TRIGGER_HIDE_TIME,iData);
	if(iBack < 0)
		iBack = RTSA_CTL_TRIG_HOLDOFF;	

	return iBack;
}
/*
purpose:set real time trigger level
func:SetRtSaTriggerPeriod
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 SetRtSaTriggerVideoLevel(DiSession devHandle,DiReal32 time)
{
#if BIT_DEBUG
    return 0;
#endif
	DiInt32 iBack = 0;
//	DiInt32 iData = time;
	iBack = BitWriteFloat32(devHandle,RTSA_TRIGGER_VIEDO_LEVEL,time);
	if(iBack < 0)
		iBack = RTSA_CTL_TRIG_VIDEO_LEVEL;	
	return iBack;
}
/*
purpose:set real time trigger level
func:SetRtSaTriggerRFLevel
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 SetRtSaTriggerRFLevel(DiSession devHandle,DiReal64 time)
{
#if BIT_DEBUG
    return 0;
#endif
DiInt32 iBack = 0;
#if 0
// 13bits inter and 51 bits frac
	printf("time before %f\n",time);

	time = time / RTSA_AD_RATIO;
	
	printf("time after %.12f\n",time);

	DiInt32 IntPart = (DiInt32)time;

	printf("time IntPart %d\n",IntPart);

	IntPart = (IntPart & 0x1fff);
	
	DiReal64 FracPart = time - IntPart;
	printf("time FracPart %.12f\n",FracPart);

//	DiReal64 FracPart1 = FracPart * pow(2,51);
//	printf("time FracPart1 %.12f\n",FracPart1);

	DiReal64 FracPart_High = (FracPart * pow(2,19));
	printf("time Frac_Int %.12f\n",FracPart_High);
	
	DiInt32 FracPartHigh = (DiInt32)(FracPart_High);
	printf("time FracPartHigh %0x\n",FracPartHigh);

	FracPart = FracPart_High - (DiInt64)(FracPart_High);
	printf("time FracPart1xxxxx %.12f\n",FracPart);


//	DiReal64 FracPart_Temp = (FracPart * pow(2,32));
//	printf("time FracPart_Temp %.12f\n",FracPart_Temp);
	
	DiInt64 FracPartLow = (DiInt64)(FracPart * pow(2,32));
//	printf("time FracPartLow %0x\n",FracPartLow);

	
	DiInt32 RfLevel_High = (IntPart << 13) + (FracPartHigh & 0x7ffff);
	printf("time RfLevel_High %0x\n",RfLevel_High);
	
	DiInt32 RfLevel_Low = (FracPartLow)  & 0xffffffff;
	printf("time RfLevel_Low %0x\n",RfLevel_Low);

	iBack = BitWrite32(devHandle,RTSA_TRIGGER_RF_BURST_HIGH,RfLevel_High);
	if(iBack < 0)
		iBack = RTSA_RBW;	
	iBack = BitWrite32(devHandle,RTSA_TRIGGER_RF_BURST_LOW,RfLevel_Low);
	if(iBack < 0)
		iBack = RTSA_RBW;	
	
		return iBack;
#endif
// 48 bits int and 16 bits frac
    time = time / RTSA_I_Q_RATIO;
    DiInt64 IntPart = (DiInt64)time;
		//printf("IntPart~~~~~~~~~~ %lld \n",IntPart);
    DiReal64 FracPart = time - IntPart;
		//printf("FracPartLow~~~~~~~~~~ %.12f\n",FracPart);
    DiInt64 FracPartLow = (DiInt64)(FracPart * pow(2,19));
	//printf("FracPartLow~~~~~~~~~~ %lld \n",FracPartLow);
//    DiInt32 RfLevel_High = (IntPart >> 16) & 0xffffffff;
//DiInt32 aaa = (IntPart & 0x1fff);
//printf("aaa ------------ %0x\n",aaa);
//DiInt32 bbb = aaa << 19;
//printf("bbb ------------ %0x\n",bbb);

//DiInt32 ccc = (FracPartLow)  & 0x7ffff;
//printf("ccc------------ %0x\n",ccc);
//    DiInt32 RfLevel_Low = bbb + ccc;
//printf("RfLevel_Low ------------ %0x\n",RfLevel_Low);

		DiInt32 RfLevel_Low = ((IntPart & 0x1fff) << 19) + ((FracPartLow)  & 0x7ffff);
//		printf("RfLevel_Low ------------ %0x\n",RfLevel_Low);


//    iBack = BitWrite32(devHandle,RTSA_TRIGGER_RF_BURST_HIGH,RfLevel_High);
//    if(iBack < 0)
//	iBack = RTSA_RBW;	
    iBack = BitWrite32(devHandle,RTSA_TRIGGER_RF_BURST_LOW,RfLevel_Low);
    if(iBack < 0)
		iBack = RTSA_CTL_TRIG_RF_LEVEL;	
    return iBack;

}
/*
purpose:set real time trigger slope
func:setRtSaTriggerSlope
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 setRtSaTriggerSlope(DiSession devHandle, DiUInt32 slope)
{
	#if BIT_DEBUG
    return 0;
	#endif
	DiInt32 iBack = 0;
	DiInt32 iData = slope & 0xff;
	iBack = BitWrite32(devHandle,RTSA_TRIGGER_SLOPE,iData);
	if(iBack < 0)
		iBack = RTSA_CTL_TRIG_SLOPE;	
		return iBack;
}
/*
purpose:set real time balance factor
func:setRtSaBalanceFactor
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 GetRtSaDspStatus(DiSession devHandle, DiPUInt32 status)
{
	#if BIT_DEBUG
    return 0;
	#endif
	DiInt32 iBack = 0;
	
	iBack = BitRead32(devHandle,RTSA_DSP_STATUS,status);
//	if(iBack < 0)
//		iBack = RTSA_RBW;	
		return iBack;
}
/*
purpose:set real time balance factor
func:setRtSaBalanceFactor
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 setRtSaBalanceFactor(DiSession devHandle,DiPReal32 factor)
{
	#if BIT_DEBUG
	    return 0;
	#endif
	DiInt32 iBack = 0;
	DiInt32 i = 0;
	DiUInt32 tempaddr = RTSA_GAIN_COMP_ADDR;
	DiInt32 iaddrstep = sizeof(DiPReal32);
	
	for(i = 0; i < 801; i++)
		{
			iBack = BitWriteFloat32(devHandle, tempaddr, factor[i]);
			if(iBack < 0)
          {
          iBack = RTSA_CTL_CAL_FACTOR;
//              printf("get dpx fmt data error at  %d \n",i);
              return iBack;
          }
			tempaddr += iaddrstep;
		}

	return iBack;	
}
/*
purpose:eliminate dc  
func:SetRtSaTriggerPeriod
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 EliminateDC(DiSession devHandle, DiUInt32 flag)
{
#if BIT_DEBUG
    return 0;
#endif
	DiInt32 iBack = 0;
	DiUInt32 iData = flag;
	iData &= 0x1;
	iBack = BitWrite32(devHandle,RTSA_DC_ELIMIT,iData);
//	if(iBack < 0)
//	  iBack = RTSA_RBW;	
	return iBack;	
}

/*
purpose:get result data from local part
func:GetResultFloatData
param:<in>devHandle:dev's ctrl handle from ini
      <in/out>pbuffer:data buffer
      <in>num: data nums
return:>=0 is ok
 */
DiInt32 GetResultFloatData(DiSession devHandle,DiPReal32 pbuffer,DiUInt32 num)
{
#if BIT_DEBUG
    return 0;
#endif
	DiInt32 iBack = 0;
	iBack = BitMoveOutFloat32(devHandle,PLLOCALMEMBASEADDR,num,pbuffer);
	if(iBack < 0)
	  iBack = RTSA_GETSPECData;
	return iBack;
}
//test

DiInt32 RtSaTestParam(DiSession devHandle)
{
#if BIT_DEBUG
    return 0;
#endif
	DiInt32 iBack = 0;

	//	iBack = BitWrite32(devHandle,RTSA_FFT_LEGTH,2048);
	iBack = BitWrite32(devHandle,0x80000020,0);
		
	iBack = BitWrite32(devHandle,RTSA_SPAN_ADDR,0);
	
	iBack = BitWrite32(devHandle,0x80000210,6);
	
	iBack = BitWrite32(devHandle,RTSA_MEAN_FACTOR_ADDR,0x385debbd);

	iBack = BitWrite32(devHandle,RTSA_FFT_WINDOW_ADDR,5);

	iBack = BitWrite32(devHandle,RTSA_FFT_BUCKET_NUM_ADDR,0x00016333);


	iBack = BitWrite32(devHandle,RTSA_FFT_VALID_NUM_START_STOP_ADDR,0x062a01d4);

	iBack = BitWrite32(devHandle,RTSA_ACQTIME_ADDR,0x0000159f);

	iBack = BitWrite32(devHandle,0x80000220,0);

	iBack = BitWrite32(devHandle,0x80000290,0x3f700000);

	iBack = BitWrite32(devHandle,0x800002a0,0x40000000);

	iBack = BitWrite32(devHandle,RTSA_TRIGGER_MODE,1);
	
	
//	iBack = BitWrite32(devHandle,RTSA_ACQTIME_ADDR,0x0000114C);
	
	
	return iBack;
}

DiInt32 WaitFpgaReady(DiSession devHandle)
{
	DiInt32 iBack = 0;
	DiInt32 DspStatus = -1;
	DiInt32 retDspCheckCnt = 0;
	while(1)
		{
			iBack = GetRtSaDspStatus(devHandle, &DspStatus);
			if(DspStatus == 4)
				{
					return 0;
				}
			usleep(2000);
			retDspCheckCnt ++;
			if(retDspCheckCnt > 200)
				{
//				 printf("RTSA FPGA error, can not ready!\n");
				 return iBack;
				}
		}
	return iBack;
}

