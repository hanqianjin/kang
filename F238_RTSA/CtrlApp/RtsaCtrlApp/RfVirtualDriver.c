#include "RfVirtualDriver.h"
#include <math.h>
#include "msgNoticeCode.h"
#include "BitSehInfo.h"
//---------------------------------//
//global values	   
/*DiReal64 freqChannelList[] = {9000.0,1366250000.0,2600000000.0,7500000000.0,9500000000.0,
			12300000000.0,15700000000.0,16300000000.0,19500000000.0,
			23430000000.0,26800000000.0,27833750000.0,29500000000.0,32000000000.0};
DiReal64 freqChannelList[] = {9000.0,1366250000.0,2600000000.0,4133750000.0,7500000000.0,9500000000.0,11500000000.0,
			13500000000.0,15500000000.0,16300000000.0,17500000000.0,20000000000.0,23000000000.0,25200000000.0,26000000000.0,
			29000000000.0,30500000000.0,32000000000.0,35000000000.0,37800000000.0,38000000000.0,41000000000.0,43000000000.0};*/
/*DiReal64 freqChannelList[] = {9000.0,1366250000.0,2600000000.0,4133750000.0,7500000000.0,9500000000.0,11500000000.0,
			13500000000.0,15500000000.0,16300000000.0,17500000000.0,20000000000.0,23000000000.0,26000000000.0,
			29000000000.0,32000000000.0,35000000000.0,38000000000.0,41000000000.0,43000000000.0};*/
/*DiReal64 freqChannelList[] = {9000.0,1366250000.0,2600000000.0,4133750000.0,7500000000.0,9500000000.0,11500000000.0,
			13500000000.0,15500000000.0,16300000000.0,17500000000.0,20000000000.0,22700000000.0,26000000000.0,
			29000000000.0,32000000000.0,35000000000.0,37800000000.0,41000000000.0,43000000000.0};*/
#ifdef BIT_F238
/*190704*/
DiReal64 freqChannelList[] = {9000.0,1366250000.0,2600000000.0,4133750000.0,
                           7500000000.0,9500000000.0, 11500000000.0,13500000000.0,
                           15500000000.0,16300000000.0,17500000000.0,20000000000.0,
                           22420000000.0,25550000000.0,28700000000.0,31450000000.0,
                           34500000000.0,37250000000.0,39700000000.0,43000000000.0};
#endif
#ifdef BIT_F239
//Johnson 190919
DiReal64 freqChannelList[] = {9000.0,1366250000.0,2800000000.0,7200000000.0,9500000000.0,
                            12000000000.0,15000000000.0,18000000000.0,21000000000.0,24500000000.0,
                           28000000000.0,31500000000.0,35000000000.0,39000000000.0,43000000000.0};
#endif
#ifdef BIT_F238_SMART
//Johnson 190919
DiReal64 freqChannelList[] = {9000.0,1366250000.0,2600000000.0,7200000000.0,9500000000.0,
                            11500000000.0,13500000000.0,15000000000.0};
#endif

//---------------------------------//
//macro defines
#define FREQCHADDR 0x80001010
#ifdef BIT_F239
	#define ZERORESTRAINADDR 0x800010A0
#endif
#ifdef BIT_F238
	#define ZERORESTRAINADDR 0x80001020
#endif
#define SECIFATTENADDR 0x80001030
#define MICROFREQADDR 0x800010b0
#define HIGHPREADDR 0x80001040
#define LOWPREADDR 0x80001050
#define SECLOADDR 0x80001060
#define INIADDR 0x80001070
#define REFADDR 0x80001090
#define INTERMDFREQMODEADDR 0x800010B0


#define FIRLOSTARTFREQFRACADDR 0x800010C0  /*frac part*/
#define FIRLOSTARTFREQADDR 0x800010D0 /*low 16 bit is frac part,high 16 bit is int part*/
#define FIRLOSTEPLOWADDR  0x800010E0 /*low 32 bits*/
#define FIRLOSTEPHIGHADDR  0x800010F0 /*high 16 bits*/
#define FIRLOKEEPADDR 0x80001100/*last part freq keep time*/

//#define FIRLOSTARTFREQFRACADDR 0x800001E0  /*frac part*/
//#define FIRLOSTARTFREQADDR 0x800001F0 /*low 16 bit is frac part,high 16 bit is int part*/
//#define FIRLOSTEPLOWADDR  0x80000200 /*low 32 bits*/
//#define FIRLOSTEPHIGHADDR  0x80000210 /*high 16 bits*/
//#define FIRLOKEEPADDR 0x80000220/*last part freq keep time*/

#define BRIGHTNESSLEVEL 0x80001110


#define PHASEMIN 0.0
#define PHASEMAX 354.375
#define PHASESTEP 5.625

#define ATTENMIN0  0.0
#define ATTENMAX0 50.0
#define ATTENSTEP0 1.0 

#define ATTENMICROMAX 30.0
#define ATTENMICROSTEP 5.0
//---------------------------------//
//static functions  
DiInt32 GetFreqChannelIndex(DiReal64 freqHz);
DiInt32 GetFreqChannelIndexSec(DiReal64 freqHz,DiInt32 istart);
static DiInt32 GetPhaseIndex(DiReal64 phase,DiReal64 step);
static DiInt32 AttenToIndex(DiReal64 attendB,DiReal64 step);  

typedef struct
{
	DiReal64 r;
	DiReal64 d;
	DiReal64 feedback;
	DiReal64 iffreq;
} LO_FREQ_DIV; /*calc differ seg freq div values*/

/*LO_FREQ_DIV lodivList[] =
{
	{2.0,4.0,4.0,3633750000.0},
	{2.0,2.0,4.0,3633750000.0},
	{2.0,1.0,4.0,9866250000.0},
	{2.0,1.0,4.0,3633750000.0},
	{2.0,1.0,4.0,3633750000.0},
	{2.0,1.0,4.0,3633750000.0},
	{2.0,1.0,4.0,3633750000.0},
	{2.0,1.0,4.0,-3633750000.0},
	{2.0,1.0,4.0,-3633750000.0},
	{2.0,0.5,4.0,-3633750000.0},
	{2.0,0.5,4.0,-3633750000.0},
	{2.0,0.5,4.0,-3633750000.0},
	{2.0,0.5,4.0,-3633750000.0}
};
LO_FREQ_DIV lodivList[] =
{
    {1.0,4.0,4.0,3633750000.0},//9k~1.36625G
    {1.0,2.0,4.0,3633750000.0},//1.36625-2.6GHz
    {1.0,1.0,4.0,9866250000.0},//2.6~4.13375G
    {1.0,1.0,4.0,9866250000.0},//4.13375~7.5G
    {1.0,1.0,4.0,3633750000.0},//7.5~9.5G
    {1.0,1.0,4.0,3633750000.0},//9.5~11.5G
    {1.0,1.0,4.0,3633750000.0},//11.5~13.5G
    {1.0,1.0,4.0,3633750000.0},//13.5~15.5G
    {1.0,1.0,4.0,3633750000.0},//15.5~16.3G
    {1.0,1.0,4.0,-3633750000.0},//16.3~17.5G
    {1.0,1.0,4.0,-3633750000.0},//17.5~20G
    {1.0,0.5,4.0,3633750000.0},//20~23G
    {1.0,0.5,4.0,3633750000.0},//23~25.2G
    {1.0,0.5,4.0,3633750000.0},//25.2~26G
    {1.0,0.5,4.0,3633750000.0},//26~29G
    {1.0,0.5,4.0,3633750000.0},//29~30.5G
    {1.0,0.5,4.0,3633750000.0},//30.5~32G
    {1.0,0.5,4.0,3633750000.0},//32~35G
    {1.0,0.5,4.0,-3633750000.0},//35~37.8G
    {1.0,0.5,4.0,-3633750000.0},//37.8~38G
    {1.0,0.5,4.0,-3633750000.0},//38~41G
    {1.0,0.5,4.0,-3633750000.0}//41~43G
};*/
#ifdef BIT_F238
LO_FREQ_DIV lodivList[] =
{
     {1.0,4.0,4.0,3633750000.0},//9k~1.36625G
     {1.0,2.0,4.0,3633750000.0},//1.36625-2.6GHz
     {1.0,1.0,4.0,9866250000.0},//2.6~4.13375G
     {1.0,1.0,4.0,9866250000.0},//4.13375~7.5G
     {1.0,1.0,4.0,3633750000.0},//7.5~9.5G
     {1.0,1.0,4.0,3633750000.0},//9.5~11.5G
     {1.0,1.0,4.0,3633750000.0},//11.5~13.5G
     {1.0,1.0,4.0,3633750000.0},//13.5~15.5G
     {1.0,1.0,4.0,3633750000.0},//15.5~16.3G
     {1.0,1.0,4.0,-3633750000.0},//16.3~17.5G
     {1.0,1.0,4.0,-3633750000.0},//17.5~20G
     {1.0,0.5,4.0,3633750000.0},//20~23G
     {1.0,0.5,4.0,3633750000.0},//23~26G
     {1.0,0.5,4.0,3633750000.0},//26~29G
     {1.0,0.5,4.0,3633750000.0},//29~32G
     {1.0,0.5,4.0,3633750000.0},//32~35G
     {1.0,0.5,4.0,-3633750000.0},//35~38G
     {1.0,0.5,4.0,-3633750000.0},//38~41G
     {1.0,0.5,4.0,-3633750000.0}//41~43G
};
#endif
#ifdef BIT_F239
//Johnson 190919
LO_FREQ_DIV lodivList[] =
{
     {1.0,4.0,4.0,3633750000.0},//9k~1.36625G
     {1.0,2.0,4.0,3633750000.0},//1.36625-2.6GHz
     {1.0,1.0,4.0,9866250000.0},//2.6~7.2G
     {1.0,1.0,4.0,3633750000.0},//7.2~9.5G
     {1.0,1.0,4.0,3633750000.0},//9.5~12G
     {1.0,1.0,4.0,3633750000.0},//12~15G
     {1.0,1.0,4.0,-3633750000.0},//15~18G
     {1.0,0.5,4.0,3633750000.0},//18~21G
     {1.0,0.5,4.0,3633750000.0},//21~24.5G
     {1.0,0.5,4.0,-3633750000.0},//24.5~28G
     {1.0,0.5,4.0,-3633750000.0},//28~31.5G
     {1.0,0.5,4.0,-3633750000.0},//31.5~35G
     {1.0,0.5,4.0,-3633750000.0},//35~39G
     {1.0,0.5,4.0,-3633750000.0}//39~43G
};
#endif
#ifdef BIT_F238_SMART
//Johnson 190919
LO_FREQ_DIV lodivList[] =
{
     {1.0,4.0,4.0,3633750000.0},//9k~1.36625G
     {1.0,2.0,4.0,3633750000.0},//1.36625-2.6GHz
     {1.0,1.0,4.0,9866250000.0},//2.6~7.2G
     {1.0,1.0,4.0,3633750000.0},//7.2~9.5G
     {1.0,1.0,4.0,3633750000.0},//9.5~11.5G
     {1.0,1.0,4.0,3633750000.0},//11.5~13.5G
     {1.0,1.0,4.0,3633750000.0}//13.5~15G
};
#endif

#define IFATTENADDR 0x80001080
/*
purpose:IF BW select
func:SetIfAtten
param:<in>devHandle:dev's ctrl handle from ini
return:>=0 is ok
 */
DiInt32 SetIfAtten(DiSession devHandle)
{
  DiUInt32 iData = 0;
  DiInt32 iBack = BitRead32(devHandle,IFATTENADDR,&iData);    
   
  iBack =  BitWrite32(devHandle,IFATTENADDR,0);
  if(iBack < 0)
    iBack = RTSA_RESEVER_NOTICE;
  return iBack;
}


static const DiInt32 REF_CLOCK = 50000000;//ref clock
DiInt32 GetFreqlistNum()
{
 	return sizeof(freqChannelList) / sizeof(DiReal64);	
}

/*
purpose:ini the ctrl of the board
func:RfIni
param:<in>devHandle:dev's ctrl handle from ini 
return:>=0 is ok
*/
DiInt32 RfIni(DiSession devHandle)
{
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,INIADDR,&iData);		
	iData &= 0xfffffff0;
	iData |= 0xf;  
	iBack =	BitWrite32(devHandle,INIADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_RESEVER_NOTICE;
	return iBack;
}

/*
purpose: select sa intermidate frequency mode 
func:
param:<in>devHandle:dev's ctrl handle from ini
param:<in>uIFMode:IF mode which is setted by user
return:>=0 is ok
*/
DiInt32 InterMDFreqModeCtrl(DiSession devHandle,DiUInt32 uIFMode)
{
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,INTERMDFREQMODEADDR,&iData);		
	iData &= 0xfffffffc;  
	iData |= uIFMode;
	iBack =	BitWrite32(devHandle,INTERMDFREQMODEADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_RESEVER_NOTICE;
	return iBack;
}

/*
purpose: channel choose by freq
func:RfChannelChoose
param:<in>devHandle:dev's ctrl handle from ini
      <in>freqHz:set the freqHz's channel
	  value range:9kHz~32GHz
return:>=0 is ok
 */
DiInt32 RfChannelChoose(DiSession devHandle,DiReal64 freqHz)
{
	/*DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,FREQCHADDR,&iData);
	iData &= 0xfffffff0;
	iData |= GetFreqChannelIndex(freqHz);
	iBack =	BitWrite32(devHandle,FREQCHADDR,iData);
	if(iBack < 0)
	  iBack = SA_RF_Path;
	return iBack;*/

	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,FREQCHADDR,&iData);
#ifdef BIT_F239
	iData &= 0xfffffff0;
#else
	iData &= 0xffffffe0;
#endif
//	iData &= 0xffffffe0;
	iData |= GetFreqChannelIndex(freqHz);
	iBack =	BitWrite32(devHandle,FREQCHADDR,iData);

	if(iBack < 0)
	  iBack = RTSA_CTL_RF_CHANNEL;
	return iBack;
}

DiInt32 GetFreqChannelIndex(DiReal64 freqHz)
{
	if(freqHz < freqChannelList[0] + ESP)
	  return 1;
	DiInt32 iLen = sizeof(freqChannelList) / sizeof(DiReal64);
	DiInt32 i = 0;
	for(i = 1;i < iLen;i++)
	{
		if(freqHz < freqChannelList[i] + ESP)
		  return i;
	}
	return iLen - 1;
}

DiInt32 GetFreqChannelIndexSec(DiReal64 freqHz,DiInt32 istart)
{
	if(freqHz < freqChannelList[0] + ESP)
	  return 1;
	DiInt32 iLen = sizeof(freqChannelList) / sizeof(DiReal64);
	DiInt32 i = 0;
	for(i = istart;i < iLen;i++)
	{
		if(freqHz < freqChannelList[i] + ESP)
		  return i;
	}
	return iLen - 1;
}

DiInt32 RfChannelChoosebyIndex(DiSession devHandle,DiInt32 waveindex)
{
	/*DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,FREQCHADDR,&iData);	
	iData &= 0xfffffff0;
	iData |= waveindex;	
	iBack =	BitWrite32(devHandle,FREQCHADDR,iData);
	if(iBack < 0)
	  iBack = SA_RF_Path;
	return iBack;*/
	
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,FREQCHADDR,&iData);	
#ifdef BIT_F239
	iData &= 0xfffffff0;
#else
	iData &= 0xffffffe0;
#endif
//	iData &= 0xffffffe0;
	iData |= waveindex;	
	iBack =	BitWrite32(devHandle,FREQCHADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_RESEVER_NOTICE;
	return iBack;
}

#ifdef BIT_F239
/*
purpose: restrain the zero freq by phase
func:ZeroRestrainPhaseCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>phase:set the phase
	  value range:low 14bits
return:>=0 is ok
 */
DiInt32 ZeroRestrainPhaseCtrl(DiSession devHandle,DiInt32 dcvalue)
{
	DiUInt32 iData = 0;

	dcvalue = dcvalue < 0 ? 0 : dcvalue; 
	dcvalue = dcvalue > 0x3fff ? 0x3fff : dcvalue;  
	dcvalue &= 0x3fff;
	DiInt32 iBack = BitRead32(devHandle,ZERORESTRAINADDR,&iData);
	iData &= 0xffff0000;
	iData |= dcvalue;
	iData |= 0x4000;

	iBack = BitWrite32(devHandle,ZERORESTRAINADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_RESEVER_NOTICE;
	return iBack;
}
#endif
#ifdef BIT_F238
/*
purpose: restrain the zero freq by phase
func:ZeroRestrainPhaseCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>phase:set the phase
	  value range:0~354.375,per bit is 5.625
return:>=0 is ok
 */
DiInt32 ZeroRestrainPhaseCtrl(DiSession devHandle,DiReal64 phase)
{
	phase = phase < PHASEMIN ? PHASEMIN : phase;
	phase = phase > PHASEMAX ? PHASEMAX : phase;
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,ZERORESTRAINADDR,&iData);
	iData &= 0xffc0ffff;
	iData |= (GetPhaseIndex(phase,PHASESTEP) << 16);

	iBack = BitWrite32(devHandle,ZERORESTRAINADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_RESEVER_NOTICE;
	return iBack;
}
#endif

static DiInt32 GetPhaseIndex(DiReal64 phase,DiReal64 step)
{ 
	return (DiInt32)(ceil(phase / step));
}

#ifdef BIT_F239
/*
purpose: set the zero freq restain atten
func:ZeroRestrainAttenCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>dcvalue:set the atten dc
	  value range:low 14bits
return:>=0 is ok
 */
DiInt32 ZeroRestrainAttenCtrl(DiSession devHandle,DiInt32 dcvalue)
{
	DiUInt32 iData = 0;

	dcvalue = dcvalue < 0 ? 0 : dcvalue; 
	dcvalue = dcvalue > 0x3fff ? 0x3fff : dcvalue;  
	dcvalue &= 0x3fff;
	DiInt32 iBack = BitRead32(devHandle,ZERORESTRAINADDR,&iData);
	iData &= 0xffff0000;
	iData |= dcvalue;

	iBack = BitWrite32(devHandle,ZERORESTRAINADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_RESEVER_NOTICE;
	return iBack;
}
#endif
#ifdef BIT_F238
/*
purpose: set the zero freq restain atten
func:ZeroRestrainAttenCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>dcvalue:set the atten dc
	  value range:low 16bits
return:>=0 is ok
 */
DiInt32 ZeroRestrainAttenCtrl(DiSession devHandle,DiInt32 dcvalue)
{
	DiUInt32 iData = 0;

	dcvalue = dcvalue < 0 ? 0 : dcvalue; 
	dcvalue = dcvalue > 0xffff ? 0xffff : dcvalue;  
	dcvalue &= 0xffff;
	DiInt32 iBack = BitRead32(devHandle,ZERORESTRAINADDR,&iData);
	iData &= 0xffff0000;
	iData |= dcvalue;

	iBack = BitWrite32(devHandle,ZERORESTRAINADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_RESEVER_NOTICE;
	return iBack;
}
#endif


/*
purpose: set the sec IF attention
func:SecIfAttenCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>attendB:set the attenvalue
	  value range:0~31,0~31dB
return:>=0 is ok
 */
DiInt32 SecIfAttenCtrl(DiSession devHandle,DiReal64 attendB)
{
	attendB = attendB < ATTENMIN0 ? ATTENMIN0 : attendB;
	attendB = attendB > ATTENMAX0 ? ATTENMAX0 : attendB;
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,SECIFATTENADDR,&iData);
	iData &= 0xffffffe0;
	iData |= AttenToIndex(attendB,ATTENSTEP0); 
	
	iBack = BitWrite32(devHandle,SECIFATTENADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_RESEVER_NOTICE;
	return iBack;
}

static DiInt32 AttenToIndex(DiReal64 attendB,DiReal64 step)
{ 
	return (DiInt32)(ceil(attendB / step));
}


/*
purpose: set the high freq pre atten
func:HighFreqPreAttenCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>attendB:set the attenvalue
	  value range:7.5~23.63375GHz,0~31dB
return:>=0 is ok
 */
DiInt32 PreAttenCtrl(DiSession devHandle,DiReal64 attendB)
{
	/*attendB = attendB < ATTENMIN0 ? ATTENMIN0 : attendB;
	attendB = attendB > ATTENMAX0 ? ATTENMAX0 : attendB;
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,HIGHPREADDR,&iData);
	iData &= 0xffffffe0;
	iData |= (~AttenToIndex(attendB,ATTENSTEP0) & 0x0000001f);
		
	iBack = BitWrite32(devHandle,HIGHPREADDR,iData);
	if(iBack < 0)
	  iBack = SA_HIGH_PREAtten;
	return iBack;*/


	/*attendB = attendB < ATTENMIN0 ? ATTENMIN0 : attendB;
	attendB = attendB > ATTENMAX0 ? ATTENMAX0 : attendB;
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,HIGHPREADDR,&iData);
	iData &= 0xffffffc0;
	//iData |= (~AttenToIndex(attendB,ATTENSTEP0) & 0x0000001f);
	iData |= ((DiInt32)attendB & 0x0000003f);
		
	iBack = BitWrite32(devHandle,HIGHPREADDR,iData);
	if(iBack < 0)
	  iBack = SA_HIGH_PREAtten;*/

	attendB = attendB < ATTENMIN0 ? ATTENMIN0 : attendB;
	attendB = attendB > ATTENMAX0 ? ATTENMAX0 : attendB;
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,LOWPREADDR,&iData);
	iData &= 0xffffffc0;
	//iData |= (~AttenToIndex(attendB,ATTENSTEP0) & 0x0000001f);
	iData |= ((DiInt32)attendB & 0x0000003f);
		
	iBack = BitWrite32(devHandle,LOWPREADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_CTL_ATTEN;

	return iBack;
}

/*
purpose: set the high freq pre amplifier channel
func:HighFreqPreAmpliChannelCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>ctrlswitch:channel switch
	  value range:7.5~23.63375GHz,0:direct,1:amplier
return:>=0 is ok
 */
DiInt32 PreAmpliChannelCtrl(DiSession devHandle,DiUInt32 ctrlswitch)
{
	/*DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,HIGHPREADDR,&iData);
	//keep the ctrl same
	ctrlswitch = !ctrlswitch; 
	ctrlswitch <<= 5;
	iData &= 0xffffffdf;
	iData |= ctrlswitch;
		
	iBack = BitWrite32(devHandle,HIGHPREADDR,iData);
	if(iBack < 0)
	  iBack = SA_HIGH_FRONTGate;
	return iBack;*/

	/*DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,HIGHPREADDR,&iData);
	//keep the ctrl same
	//ctrlswitch = !ctrlswitch; 
	//ctrlswitch <<= 5;
	//iData &= 0xffffffdf;
	ctrlswitch <<= 6;
	iData &= 0xffffffbf;
	iData |= ctrlswitch;
		
	iBack = BitWrite32(devHandle,HIGHPREADDR,iData);
	if(iBack < 0)
	  iBack = SA_HIGH_FRONTGate;*/

	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,HIGHPREADDR,&iData);
	iData &= 0xfffffffe;
	iData |= ctrlswitch;
		
	iBack = BitWrite32(devHandle,HIGHPREADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_CTL_PREAMP;

	return iBack;
}

/*
purpose: set the low freq pre atten
func:LowFreqPreAttenCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>attendB:set the attenvalue
	  value range:9kHz~7.5GHz,0~31dB
return:>=0 is ok
 */
DiInt32 LowFreqPreAttenCtrl(DiSession devHandle,DiReal64 attendB)
{
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,LOWPREADDR,&iData);
	iData &= 0xffffffe0;
	iData |= AttenToIndex(attendB,ATTENSTEP0);
		
	iBack = BitWrite32(devHandle,LOWPREADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_RESEVER_NOTICE;
	return iBack;
}

/*
purpose: set the low freq pre amplifier channel
func:LowFreqPreAmpliChannelCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>ctrlswitch:channel switch
	  value range:9kHz~7.5GHz,0:direct,1:amplier
return:>=0 is ok
 */
DiInt32 LowFreqPreAmpliChannelCtrl(DiSession devHandle,DiUInt32 ctrlswitch)
{
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,LOWPREADDR,&iData);
	ctrlswitch = !!ctrlswitch;
	ctrlswitch <<= 5;
	iData &= 0xffffffdf;
	iData |= ctrlswitch;
	
	iBack = BitWrite32(devHandle,LOWPREADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_RESEVER_NOTICE;
	return iBack;
}

/*
purpose: get temp from Rf
func:GetRfTemperature
param:<in>devHandle:dev's ctrl handle from ini
      <out>tempValue:get temp of RfBoard 
return:>=0 is ok
 */
DiInt32 GetRfTemperature(DiSession devHandle,DiPReal64 tempValue)
{		 
	return 0;
}

/*
purpose:set first lo freq
func:FirstLoFreqCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <out>loFreq:the freq of first lo Hz
return:>=0 is ok
 */
DiInt32 FirstLoFreqCtrl(DiSession devHandle,DiReal64 loFreq)
{
	DiInt32 iIndex = GetFreqChannelIndex(loFreq);
	iIndex = iIndex == 0 ? iIndex : iIndex - 1;
	DiReal64 temp = (loFreq + lodivList[iIndex].iffreq) / REF_CLOCK * lodivList[iIndex].d * lodivList[iIndex].r / lodivList[iIndex].feedback;
	DiUInt32 intpart = (DiUInt32)temp;
	DiUInt32 fracpart = 0;
	DiUInt64 tempfrac = (DiUInt64)ceil((temp - intpart) * 4 * (1 << 16) * (1 << 30)); 
	fracpart = (tempfrac & 0xffffffff);
	intpart <<= 16;
	intpart |= (tempfrac >> 32 & 0xffff);
	DiInt32 iBack = SetFirLoFreq(devHandle,intpart,fracpart);
	if(iBack < 0)
		iBack = RTSA_CTL_FIR_LO_FREQ;

	return iBack;
}

/*
purpose:set first lo freq by ctrlword
func:SetFirLoFreq
param:<in>devHandle:dev's ctrl handle from ini
      <in>intseg:int seg
      <in>fracseg:frac seg
return:>=0 is ok
 */
DiInt32 SetFirLoFreq(DiSession devHandle,DiUInt32 intseg,DiUInt32 fracseg)
{
	DiInt32 iBack = BitWrite32(devHandle,FIRLOSTARTFREQFRACADDR,fracseg);
	iBack = BitWrite32(devHandle,FIRLOSTARTFREQADDR,intseg);
	if(iBack < 0)
		iBack = RTSA_RESEVER_NOTICE;
	return iBack;
}

/*
purpose:set first lo step freq by ctrlword
func:SetFirLoStepFreq
param:<in>devHandle:dev's ctrl handle from ini
      <in>lowbit:low bits
      <in>highbit:high bits
return:>=0 is ok
 */
DiInt32 SetFirLoStepFreq(DiSession devHandle,DiUInt32 lowbit,DiUInt32 highbit)
{
	DiInt32 iBack = BitWrite32(devHandle,FIRLOSTEPLOWADDR,lowbit);
	iBack = BitWrite32(devHandle,FIRLOSTEPHIGHADDR,highbit);	
	if(iBack < 0)
	      iBack = RTSA_CTL_LO_STEP;
	return iBack;
}

/*
purpose:seg last part to stay time for calc
func:SetFirLoStaytime
param:<in>devHandle:dev's ctrl handle from ini
      <in>fsnum:us     
return:>=0 is ok
 */
//DiInt32 SetFirLoStaytime(DiSession devHandle,DiReal64 staytime)
//{
//	DiUInt32 fsnum = (DiUInt32)(staytime * 10);
//	DiInt32 iBack = BitWrite32(devHandle,FIRLOKEEPADDR,fsnum);
//	if(iBack < 0)
//	  iBack = SA_LOLastBandKeeptime;
//	return iBack;
//}

/*
purpose:set frequency segment flag
func:setFreqSegFlag
param:<in>devHandle:dev's ctrl handle from ini
      <in>Fpga control word
return:>=0 is ok
*/
DiInt32 SetFreqSegFlag(DiSession devHandle,DiUInt32 segFlag)
{
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,FREQCHADDR,&iData);
#ifdef BIT_F238_SMART
	iData &= 0xffffff1f;
	iData |= segFlag<<5;
#endif
#ifdef BIT_F239
	iData &= 0xffffff8f;
	iData |= segFlag<<4;
#endif
#ifdef BIT_F238
	iData &= 0xffffff9f;
	iData |= segFlag<<5;
#endif
	iBack = BitWrite32(devHandle,FREQCHADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_CTL_FREQ_SEG_FLAG;
	return iBack;
}
/*
purpose:set frequency segment flag
func:SetSegmentFlag
param:<in>devHandle:dev's ctrl handle from ini
      <in>Fpga control word
return:>=0 is ok
*/
DiInt32 SetSegmentFlag(DiSession devHandle, DiReal64 freq)
{
 	DiInt32 iBack = 0;
	DiUInt32 iData = 0;
	iData = GetFreqChannelIndex(freq);
#ifdef BIT_F238_SMART
if(iData < 3)
{
    iBack = SetFreqSegFlag(devHandle,0x1);
}
else if(iData > 3)
{
    iBack = SetFreqSegFlag(devHandle,0x4);
}
else
{
    iBack = SetFreqSegFlag(devHandle,0x2);
}
#endif
#ifdef BIT_F238
	if(iData > 11)
		{
			iBack = SetFreqSegFlag(devHandle,0x0);
		}
	else if(iData > 4)
		{
			iBack = SetFreqSegFlag(devHandle,0x2);
		}
	else
		{
			iBack = SetFreqSegFlag(devHandle,0x1);
		}
#endif
#ifdef BIT_F239
	iBack = SetFreqSegFlag(devHandle,0x0);
//	if(iData > 7)
//		{
//			iBack = SetFreqSegFlag(devHandle,0x6);
//		}
//	else if(iData > 3)
//		{
//			iBack = SetFreqSegFlag(devHandle,0x4);
//		}
//	else
//		{
//			iBack = SetFreqSegFlag(devHandle,0x1);
//		}
#endif
	return iBack;
}
