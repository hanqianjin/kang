#include "RfVirtualDriver.h"
#include <math.h>

#include "TestinWin.h"  
extern int panelHandle;

//---------------------------------//
//global values	   
/*
const DiReal64 freqChannelList[] = {9000.0,1366250000.0,2600000000.0,7500000000.0,9500000000.0,
											12300000000.0,15700000000.0,16300000000.0,19500000000.0,
											23430000000.0,26800000000.0,27833750000.0,29500000000.0,32000000000.0};
*/
/*
double freqChannelList[] = {9000.0,1366250000.0,2600000000.0,4133750000.0,
							7500000000.0,9500000000.0, 11500000000.0,13500000000.0,
							15500000000.0,16300000000.0,17500000000.0,
			    20000000000.0,23000000000.0,26000000000.0,29000000000.0,
			    32000000000.0,35000000000.0,38000000000.0,41000000000.0,43000000000.0};
*/
#ifdef BIT_F238
DiReal64 freqChannelList[] = {9000.0,1366250000.0,2600000000.0,4133750000.0,
                           7500000000.0,9500000000.0, 11500000000.0,13500000000.0,
                           15500000000.0,16300000000.0,17500000000.0,20000000000.0,
                           22420000000.0,25550000000.0,28700000000.0,31450000000.0,
                           34500000000.0,37250000000.0,39700000000.0,43000000000.0};
#endif

#ifdef BIT_F239
	 DiReal64 freqChannelList[] = {9000.0,1366250000.0,2800000000.0,7200000000.0,9500000000.0,
                            12000000000.0,15000000000.0,18000000000.0,21000000000.0,24500000000.0,
                           28000000000.0,31500000000.0,35000000000.0,39000000000.0,43000000000.0};
#endif

#ifdef BIT_F238_SMART
 DiReal64 freqChannelList[] = {9000.0,1366250000.0,2600000000.0,7200000000.0,9500000000.0,
                            11500000000.0,13500000000.0,15000000000.0};
#endif
//---------------------------------//
//macro defines
#define FREQCHADDR 0x80000010
#ifdef BIT_F239
	#define ZERORESTRAINADDR 0x800010A0
#endif
#ifdef BIT_F238_SMART
	#define ZERORESTRAINADDR 0x800010A0
#endif

#ifdef BIT_F238
	#define ZERORESTRAINADDR 0x80001020
#endif  

#define SECIFATTENADDR 0x80000030
#define MICROFREQADDR 0x800000b0
#define HIGHPREADDR 0x80000040
#define LOWPREADDR 0x80000050
#define SECLOADDR 0x80000060
#define INIADDR 0x80000070
#define REFADDR 0x80000090

#define PHASEMIN 0.0
#define PHASEMAX 354.375
#define PHASESTEP 5.625

#define ATTENMIN0  0.0
#define ATTENMAX0 31.0
#define ATTENSTEP0 1.0 

#define ATTENMICROMAX 30.0
#define ATTENMICROSTEP 5.0
//---------------------------------//
//static functions  
DiInt32 GetFreqChannelIndex(DiReal64 freqHz);
static DiInt32 GetPhaseIndex(DiReal64 phase,DiReal64 step);
static DiInt32 AttenToIndex(DiReal64 attendB,DiReal64 step);  

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
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,FREQCHADDR,&iData);
	iData &= 0xfffffff0;
	iData |= GetFreqChannelIndex(freqHz);
	
#if TESTUNIT
	int i = GetFreqChannelIndex(freqHz);
	char tempchar[128];
	sprintf(tempchar,"通道频段:%.3lf,索引号:%d",freqHz,i);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,tempchar);
#endif
	
	iBack =	BitWrite32(devHandle,FREQCHADDR,iData);
	return iBack;
}

DiInt32 GetFreqChannelIndex(DiReal64 freqHz)
{
	if(freqHz < freqChannelList[0] + ESP)
	  return 1;
	DiInt32 iLen = sizeof(freqChannelList) / sizeof(DiReal64);
	for(DiInt32 i = 1;i < iLen;i++)
	{
		if(freqHz < freqChannelList[i] + ESP)
		  return i;
	}
	return iLen - 1;
}

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
	
#if TESTUNIT
	int i = GetPhaseIndex(phase,PHASESTEP);
	char tempchar[128];
	sprintf(tempchar,"相位设置:%.3lf,索引号:%d",phase,i);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,tempchar);
#endif
	
	iBack = BitWrite32(devHandle,ZERORESTRAINADDR,iData);
	return iBack;
}

static DiInt32 GetPhaseIndex(DiReal64 phase,DiReal64 step)
{ 
	return (DiInt32)(ceil(phase / step));
}

/*
purpose: set the zero freq restain atten
func:ZeroRestrainPhaseCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>dcvalue:set the atten dc
	  value range:low 16bits
return:>=0 is ok
 */
DiInt32 ZeroRestrainAttenCtrl(DiSession devHandle,DiInt32 dcvalue)
{
	DiUInt32 iData = 0;
	
#if TESTUNIT
	DiInt32 oridata = dcvalue ; 
#endif
	
	dcvalue = dcvalue < 0 ? 0 : dcvalue; 
	dcvalue = dcvalue > 0xffff ? 0xffff : dcvalue;  
	dcvalue &= 0xffff;
	DiInt32 iBack = BitRead32(devHandle,ZERORESTRAINADDR,&iData);
	iData &= 0xffff0000;
	iData |= dcvalue;
	
#if TESTUNIT
	char tempchar[128];
	sprintf(tempchar,"输入DA值:%d,实际设置的DA值:%d",oridata,iData);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,tempchar);
#endif
	
	iBack = BitWrite32(devHandle,ZERORESTRAINADDR,iData);
	return iBack;
}

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
	
#if TESTUNIT
	int i = AttenToIndex(attendB,ATTENSTEP0);
	char tempchar[128];
	sprintf(tempchar,"二中频衰减值设置:%.2lf,索引号:%d",attendB,i);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,tempchar);
#endif
	
	iBack = BitWrite32(devHandle,SECIFATTENADDR,iData);
	return iBack;
}

static DiInt32 AttenToIndex(DiReal64 attendB,DiReal64 step)
{ 
	return (DiInt32)(ceil(attendB / step));
}

/*
purpose: set the high freq pre atten
func:PreAttenCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>attendB:set the attenvalue
	  value range:7.5~23.63375GHz,0~31dB
return:>=0 is ok
 */
DiInt32 PreAttenCtrl(DiSession devHandle,DiReal64 attendB)
{
	attendB = attendB < ATTENMIN0 ? ATTENMIN0 : attendB;
	attendB = attendB > ATTENMAX0 ? ATTENMAX0 : attendB;
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,HIGHPREADDR,&iData);
	iData &= 0xffffffe0;
	iData |= (~AttenToIndex(attendB,ATTENSTEP0) & 0x0000001f);
	
	#if TESTUNIT
	int i = (~AttenToIndex(attendB,ATTENSTEP0) & 0x0000001f);
	char tempchar[128];
	sprintf(tempchar,"高波段衰减值设置:%.2lf,索引号:%d",attendB,i);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,tempchar);
	#endif
	
	iBack = BitWrite32(devHandle,HIGHPREADDR,iData);
	return iBack;
}

/*
purpose: set the high freq pre amplifier channel
func:PreAmpliChannelCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>ctrlswitch:channel switch
	  value range:7.5~23.63375GHz,0:direct,1:amplier
return:>=0 is ok
 */
DiInt32 PreAmpliChannelCtrl(DiSession devHandle,DiUInt32 ctrlswitch)
{
	#if TESTUNIT
	DiInt32 itemp = ctrlswitch;
	#endif
	
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,HIGHPREADDR,&iData);
	//keep the ctrl same
	ctrlswitch = !ctrlswitch; 
	ctrlswitch <<= 5;
	iData &= 0xffffffdf;
	iData |= ctrlswitch;
	
	#if TESTUNIT  
	char tempchar[128];
	sprintf(tempchar,"高波前置放大设置:%d,索引号:0x%x",itemp,iData);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,tempchar);
	#endif
	
	iBack = BitWrite32(devHandle,HIGHPREADDR,iData);
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
	
	#if TESTUNIT
	int i = AttenToIndex(attendB,ATTENSTEP0);
	char tempchar[128];
	sprintf(tempchar,"低波段衰减值设置:%.2lf,索引号:%d",attendB,i);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,tempchar);
	#endif
	
	iBack = BitWrite32(devHandle,LOWPREADDR,iData);
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
	#if TESTUNIT
	DiInt32 itemp = ctrlswitch;
	#endif
	
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,LOWPREADDR,&iData);
	ctrlswitch = !!ctrlswitch;
	ctrlswitch <<= 5;
	iData &= 0xffffffdf;
	iData |= ctrlswitch;
	
	#if TESTUNIT  
	char tempchar[128];
	sprintf(tempchar,"低波前置放大设置:%d,索引号:0x%x",itemp,iData);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,tempchar);
	#endif
	
	iBack = BitWrite32(devHandle,LOWPREADDR,iData);
	return iBack;
}

/*
purpose: set the sec lo out freq in Hz
func:SecLoOutfreqCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>freqHz:set the sec lo freq
	  value range:
return:>=0 is ok
 */
DiInt32 SecLoOutfreqCtrl(DiSession devHandle,DiReal64 freqHz)
{
	freqHz = freqHz < 90000000.0 + ESP ? 90000000.0 : freqHz;
	DiReal64 frac = freqHz / 90000000.0 / 2.0;	  
	frac *= 1.0e6;
	
	#if TESTUNIT  
	char tempchar[128];
	sprintf(tempchar,"二本振分频比%lf",frac);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,tempchar);
	#endif
	
	DiInt32 iBack = BitWrite32(devHandle,SECLOADDR,(DiInt32)frac);
	return iBack;
}

/*
purpose: set the ref of the board
func:InOutRefCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>refValue:set the ref in or out
	  value range:0 out ref,1 in ref
return:>=0 is ok
 */
DiInt32 InOutRefCtrl(DiSession devHandle,DiUInt32 refValue)
{
	#if TESTUNIT 
	DiUInt32 temp = refValue;
    #endif
	
	refValue = !!refValue;
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,REFADDR,&iData);
	iData &= 0xfffffffe;
	iData |= refValue;
	
	#if TESTUNIT  
	char tempchar[128];
	sprintf(tempchar,"内外参考设置形参：%d,实设%d",temp,iData);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,tempchar);
	#endif
	
	iBack = BitWrite32(devHandle,REFADDR,iData); 
	return iBack;
}

/*
purpose: set the micro freq pre atten
func:MicroFreqPreAttenCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>attendB:set the attenvalue
	  value range:23.63375~32GHz,0~30dB,step 5dB
return:>=0 is ok
 */
DiInt32 MicroFreqPreAttenCtrl(DiSession devHandle,DiReal64 attendB)
{
	attendB = attendB < ATTENMIN0 ? ATTENMIN0 : attendB;
	attendB = attendB > ATTENMICROMAX ? ATTENMICROMAX : attendB;
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,MICROFREQADDR,&iData);
	iData &= 0xffffffe0;
	iData |= ((DiInt32)ATTENMICROSTEP * AttenToIndex(attendB,ATTENMICROSTEP) & 0x0000001f); 
	
	#if TESTUNIT
	int i = (DiInt32)ATTENMICROSTEP * AttenToIndex(attendB,ATTENMICROSTEP);
	char tempchar[128];
	sprintf(tempchar,"微波段衰减值设置:%.2lf,索引号:%d",attendB,i);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,tempchar);
	#endif
	
	iBack = BitWrite32(devHandle,HIGHPREADDR,iData);
	return iBack;
}
	  
/*
purpose: set the micro freq pre amplifier channel
func:MicroFreqPreAmpliChannelCtrl
param:<in>devHandle:dev's ctrl handle from ini
      <in>ctrlswitch:channel switch
	  value range:23.63375~32GHz,0:direct,1:amplier
return:>=0 is ok		
 */
DiInt32 MicroFreqPreAmpliChannelCtrl(DiSession devHandle,DiUInt32 ctrlswitch)
{
	#if TESTUNIT
	DiInt32 itemp = ctrlswitch;
	#endif
	
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,MICROFREQADDR,&iData);
	ctrlswitch = !!ctrlswitch;
	ctrlswitch <<= 5;
	iData &= 0xffffffdf;
	iData |= ctrlswitch;  
	
	#if TESTUNIT  
	char tempchar[128];
	sprintf(tempchar,"微波前置放大设置:%d,索引号:0x%x",itemp,iData);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,tempchar);
	#endif
	
	iBack = BitWrite32(devHandle,MICROFREQADDR,iData);
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


