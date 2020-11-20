//==============================================================================
//
// Title:		SaAnalysis.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/1/20 at 11:34:57 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <windows.h>
#include <toolbox.h>
#include <analysis.h>
#include <utility.h>
#include <ansi_c.h>
#include "SaAnalysis.h"
#include "SaDataStruct.h"

#include <visa.h>  

#include "TestinWin.h"
extern int panelHandle;
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
#define DATACLRADDR 0x80000110 /*0 not clr 1clr;check register clr*/

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
//

#define FIRLOSTARTFREQFRACADDR 0x800001E0  /*frac part*/
#define FIRLOSTARTFREQADDR 0x800001F0 /*low 16 bit is frac part,high 16 bit is int part*/
#define FIRLOSTEPLOWADDR  0x80000200 /*low 32 bits*/
#define FIRLOSTEPHIGHADDR  0x80000210 /*high 16 bits*/
#define FIRLOKEEPADDR 0x80000220/*last part freq keep time*/
#define SEGSWEEPNUMADDR 0x80000230/*fft and zero span set 0*/

//inner driver
static DiInt32 SetFirLoFreq(DiSession devHandle,DiUInt32 intseg,DiUInt32 fracseg);
void GetStepFrqDivValue(double startfreq,double stepHz,unsigned int* lowbits,unsigned int* highbits);
//==============================================================================

static const DiReal64 minFreqHz = 9000.0;
static const DiReal64 maxFreqHz = 3.2e10;
static const DiInt32 checkTypenum = 6;//check wave nums

static const DiReal64 firStep = 0.2;//FIR lo step
static const DiReal64 rbwtospan = 0.01;//span to rbw,when small down 1
static const DiReal64 vbwtorbw = 1.0;//vbw to rbw
static const DiInt32  CHECKMODEMAX = 5;//dector max nums
static const DiInt32 REF_CLOCK = 100000000;//ref clock
static const DiReal64 fstimens = 1000. / 45;//acq time
//==============================================================================
// Types
static CHANNEL_PARAM chparamlist[] =
{
	//rbwHz fsHz  stepHz						 Nfs
	{3000, 45000, 33750, 32,   2.133, 0.0, 0.75, 32000},
	{1000, 45000, 33750, 128,  2.844, 0.0, 0.75, 128000},
	{300,  45000, 33750, 256,  1.707, 0.0, 0.75, 256000},
	{100,  45000, 33750, 1024, 2.275, 0.0, 0.75, 1024000},
	{30,   4500,  3375,  256,  1.707, 0.0, 0.75, 2560000},
	{10,   4500,  3375,  1024, 2.275, 0.0, 0.75, 10240000},
	{3,    4500,  3375,  4096, 2.731, 0.0, 0.75, 40960000},
	{1,    2250,  1800,  8192, 3.641, 0.0, 0.8,  1638400000}
};/*FFT mode*/

static SWEEP_NUM sweepnumList = {0};/*calc the nums of the fft and fir mode*/
/*undo
	  need inial datas when finished the app*/

typedef struct
{
	DiReal64 r;
	DiReal64 d;
	DiReal64 feedback;
	DiReal64 iffreq;
} LO_FREQ_DIV; /*calc differ seg freq div values*/

/*
static LO_FREQ_DIV lodivList[] =
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
*/

/*
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
*/
 
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
LO_FREQ_DIV lodivList[] =
{
     {1.0,4.0,4.0,3633750000.0},//9k~1.36625G
     {1.0,2.0,4.0,3633750000.0},//1.36625-2.6GHz
     {1.0,1.0,4.0,9866250000.0},//2.6~7.5G
     {1.0,1.0,4.0,3633750000.0},//7.5~9.5G
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
LO_FREQ_DIV lodivList[] =
{
     {1.0,4.0,4.0,3633750000.0},//9k~1.36625G
     {1.0,2.0,4.0,3633750000.0},//1.36625-2.6GHz
     {1.0,1.0,4.0,9866250000.0},//2.6~7.5G
     {1.0,1.0,4.0,3633750000.0},//7.5~9.5G
     {1.0,1.0,4.0,3633750000.0},//9.5~11.5G
     {1.0,1.0,4.0,3633750000.0},//11.5~13.5G 
	 {1.0,1.0,4.0,3633750000.0}//13.5~15G 
};
#endif


//==============================================================================
// Static global variables
//this part defined by south korea
_CONFIG_SWEEP bit_config_sweep;
static _CONFIG_MEASURE bit_config_measure;
static _CONFIG_SYSTEM bit_config_system;
static _SWEEP_DATA bit_sweep_data;
static _MEASURE_DATA bit_measure_data;
static _SYSTEM_INFO bit_system_info;
static _SM_SYNC bit_sm_sync;

//==============================================================================
// Static functions
void GetSegmentWaveIndex(void* param);
static void RefCalSweepParams(DiInt32 sweepMode);
static DiInt32 GetrbwIndex(DiReal64 rbwHz);
static void GetFreqDivValue(DiReal64 freqHz,DiPUInt32 intdiv,DiPUInt32 fracdiv);
static void GetLastPartTime(DiInt32 iIndex);
static void TrigResweep(void* param);
static DiInt32 GetFftRbwIndex();
static void ParamConvertByRbw(DiInt32 iIndex);

//==============================================================================
// Global variables												//6
const DiReal64 rbwList[] =      {5.0e6,3.0e6,1.0e6,3.0e5,1.0e5,3.0e4,1.0e4,3000,1000,300,100,30, 10, 3, 1};
const DiReal64 dealTimeList[] = {1000.0  ,1000.0  ,1000.0  ,1000.0  ,1000.0  ,1000.0  ,1000.0  ,1000.0 ,1000.0 ,1000.0,1000.0,1000.0,1000.0,1000.0,1000.0};/*last part spend time*/
extern const DiReal64 freqChannelList[];
extern DiInt32 GetFreqChannelIndex(DiReal64 freqHz);

//==============================================================================
//multi thread designs
DiSession bitdevHandle = 0;
/*thread:for listen and down param*/
DiInt32 INNERSOFTINTER = 1;/*1 receive the soft inter eg change rbw or freq*/
static SWEEP_NUM sweepListinthread = {0};/*just used in the listen and down param thread*/
static DiInt32 ListenAndDownSweepParamThread(void *functionData);
static void GetSweepInterruptState(DiPUInt32 state);

/*thread:for acq the datas*/
void IniParam()
{
	bit_config_sweep.CenterFreq = 10.0e9;
	bit_config_sweep.SPANFreq = 1.0e9;
	bit_config_sweep.RBWAuto = 1;
	bit_config_sweep.VBWAuto = 1;
	bit_config_sweep.VBWTORBWAuto = 1;
	bit_config_sweep.RBW = 3000000;
	bit_config_sweep.sweepMode = 0; 

	sweepnumList.validRatio = 0.75;   
	return;
}
//==============================================================================
CmtThreadFunctionID threadID;
DiInt32 interflag = 0;
DiInt32 StartListenThread()
{
	return CmtScheduleThreadPoolFunctionAdv (
			   DEFAULT_THREAD_POOL_HANDLE, ListenAndDownSweepParamThread, NULL,
			   THREAD_PRIORITY_NORMAL, NULL, EVENT_TP_THREAD_FUNCTION_END, NULL,
			   CmtGetCurrentThreadID(),&threadID);
}
CmtThreadFunctionID acqthreadID;
static DiInt32 AcqandAnaSigThread(void *functionData);
DiInt32 StartAcqThread()
{
	return CmtScheduleThreadPoolFunctionAdv (
			   DEFAULT_THREAD_POOL_HANDLE, AcqandAnaSigThread, NULL,
			   THREAD_PRIORITY_NORMAL, NULL, EVENT_TP_THREAD_FUNCTION_END, NULL,
			   CmtGetCurrentThreadID(),&acqthreadID);
}

int value = 0;
#define POINTNUM 1001
static DiInt32 AcqandAnaSigThread(void *functionData)
{

	double wfm2[POINTNUM] = {0.0};
	double useddatap[POINTNUM] = {0.0};
	int ploth1 = 0;
#if TESTUNIT
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX_2,-1,"采集分析线程启动！");
	int times = 0;
#endif
	int    g_canvasWidth;
	int    g_canvasHeight;
	GetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_HEIGHT, &g_canvasHeight);
	GetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_WIDTH, &g_canvasWidth);
	int xPres = 0;
	int yPres = 0;

	int color = MakeColor (rand () % 256, rand () % 256,rand () % 256);
	SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_COLOR,color);
	SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_ENABLE_ANTI_ALIASING, 1);

	do
	{
		for(int i = 0; i<POINTNUM; i++)
		{
			*(wfm2 + i) = Random(0.5,2.5);
			*(wfm2 + i) += value;
			*(wfm2 + i) *= 10.0;
		}
		for(int i = (POINTNUM / 2 - 5); i<(POINTNUM / 2 + 7); i++)
		{
			*(wfm2 + i) += 155.23;
		}

		for(int i = 0; i<POINTNUM; i++)
		{
			*(wfm2 + i) *= -1;
			*(wfm2 + i) += (g_canvasHeight - 10 -20);
		}


		double time0 = Timer();
		memcpy(useddatap,wfm2,sizeof(double) * POINTNUM);
		double deta = Timer() - time0;
		//if(times == 10)
		{
			SetCtrlVal(panelHandle,PANEL_NUMERIC_3,deta);
		}
		CanvasStartBatchDraw (panelHandle, PANEL_CANVAS);

		CanvasClear (panelHandle, PANEL_CANVAS, VAL_ENTIRE_OBJECT);
		for(int i = 0; i <= 10; i++)
		{
			CanvasDrawLine (panelHandle, PANEL_CANVAS,MakePoint (10,10+ i * (g_canvasHeight - 20) / 10 ),MakePoint (g_canvasWidth-10, 10 + i * (g_canvasHeight - 20) / 10 ));
			CanvasDrawLine (panelHandle, PANEL_CANVAS,MakePoint (10 + i * (g_canvasWidth - 20) / 10,10),MakePoint (10 + i * (g_canvasWidth - 20) / 10, g_canvasHeight-10));
		}

		for (int i = 0; i < POINTNUM - 1; i++)
		{
			CanvasDrawLine (panelHandle, PANEL_CANVAS,MakePoint (10 + i * (g_canvasWidth - 20) / POINTNUM,wfm2[i]),MakePoint (10 + (i + 1) * (g_canvasWidth - 20) / POINTNUM, wfm2[i + 1]));
		}
		CanvasEndBatchDraw (panelHandle, PANEL_CANVAS);

		//SetCtrlVal(panelHandle,PANEL_NUMERIC,times++);
		Sleep(1);
	}
	while(1);
	return 0;
}
/*
listening the interupt and down the sweep params
the thread is designed for supporing the segment sweep
*/
int iquery = 0;
static DiInt32 ListenAndDownSweepParamThread(void *functionData)
{
	DiUInt32 interState = 0;/*1 receive the interrupt*/
	DiInt32 iBack = 0;  
	int nowseg = 0;
	do
	{
		if(INNERSOFTINTER)
		{
			//updataparam
			memcpy(&sweepListinthread,&sweepnumList,sizeof(SWEEP_NUM));
			INNERSOFTINTER = !INNERSOFTINTER;
			
				#if TESTUNIT
				char tempchar[128];
				sprintf(tempchar,"总的频段数量:%u",sweepnumList.segmentNum);
				InsertTextBoxLine(panelHandle,PANEL_TEXTBOX_2,-1,tempchar);
				sprintf(tempchar,"总的扫描时间:%lf",sweepnumList.sumSweeptime);
				InsertTextBoxLine(panelHandle,PANEL_TEXTBOX_2,-1,tempchar);
				sprintf(tempchar,"分析模式:%d",bit_config_sweep.sweepMode);
				InsertTextBoxLine(panelHandle,PANEL_TEXTBOX_2,-1,tempchar);
				#endif 
			
		}
		SetCtrlVal(panelHandle,PANEL_NUMERIC_2,nowseg);
		for(DiInt32 i = 0; i < sweepListinthread.segmentNum; i++)
		{ 
			/*when receive the soft interrupt,break*/        
			if(INNERSOFTINTER)
				break;
			//down the param
			//the start freq div frq
			SetFirLoFreq(bitdevHandle,(sweepListinthread.comNum + i) -> seglostartfreqinter,(sweepListinthread.comNum + i) -> seglostartfreqfrac);
			//the lo step
			SetFirLoStepFreq(bitdevHandle,(sweepListinthread.comNum + i) -> seglosteplow, (sweepListinthread.comNum + i) -> seglostephigh);
			//the seg last part stay time
			SetFirLoStaytime(bitdevHandle,sweepListinthread.seglokeeptime); 
			//segment sum time 
			SettotalswpTimeLow(bitdevHandle,sweepListinthread.comNum[i].persegsweeptimes & 0xffffffff);
			SettotalswpTimeHight(bitdevHandle,sweepListinthread.comNum[i].persegsweeptimes >> 32 & 0xffffffff);
			//if fft single acq time
			if(3 == bit_config_sweep.sweepMode)
			{
				SetfftdotswpTime(bitdevHandle,sweepListinthread.singlefftTime);
				//SetSegPoint(bitdevHandle,0);
				SetSegPoint(bitdevHandle,(sweepListinthread.comNum + i) -> segmentDataNum); 
			}
			else
			{
				//segment points num,means lo step times
				SetSegPoint(bitdevHandle,(sweepListinthread.comNum + i) -> segmentDataNum);
			}
			//resweet
			SetswpStop(bitdevHandle);
			SetswpRun(bitdevHandle); 
			//query the interrupt
			/*when receive the soft interrupt,break*/  
			#if TESTUNIT
			InsertTextBoxLine(panelHandle,PANEL_TEXTBOX_2,-1,"等待中断！");
			#endif
			nowseg = i;
			while(!INNERSOFTINTER && !interState)
			{
				GetSweepInterruptState(&interState); 
			}
			value++;
			#if TESTUNIT
			InsertTextBoxLine(panelHandle,PANEL_TEXTBOX_2,-1,"收到中断！");
			#endif

			//clear the state
			interState = 0; 
		}
	}
	while(1);
	return 0;
}

static void GetSweepInterruptState(DiPUInt32 state)
{
	Sleep(1);
	*state = interflag;
	interflag = 0;
	return;
}

// Global functions
/*
purpose: config start and stop freq
func:DiInst_ConfigureFrequencyStartStop
param:<in>devHandle:dev's ctrl handle from ini
	  <in>startFrequency:start freq in Hz
	  <in>stopFrequency:stop freq in Hz
	  value range:9kHz~32GHz
return:>=0 is ok
*/
static DiInt32 rbwTrigDoor = 0;/*set rbw when 0 ifself,1 function call */
DiInt32 DiInst_ConfigureFrequencyStartStop (DiSession devHandle,DiReal64 startFrequency,DiReal64 stopFrequency)
{
	//check param
	startFrequency = startFrequency < minFreqHz + ESP ? minFreqHz : startFrequency;
	stopFrequency = stopFrequency > maxFreqHz + ESP ? maxFreqHz : stopFrequency;
	startFrequency = startFrequency > stopFrequency ? minFreqHz : startFrequency;

	//reflesh params
	bit_config_sweep.StartFreq = startFrequency;
	bit_config_sweep.StopFreq = stopFrequency;
	bit_config_sweep.CenterFreq = 0.5 * (stopFrequency + startFrequency);
	bit_config_sweep.SPANFreq = stopFrequency - startFrequency;  

	//get segment index   bit_config_sweep.sweepMode
	GetSegmentWaveIndex(NULL);
	//associate with rbw
	if(bit_config_sweep.RBWAuto)
	{
		//calc rbw through the span,0.01
		DiInt32 tempIndexcalc = GetrbwIndex(bit_config_sweep.SPANFreq * rbwtospan);
		DiInt32 tempIndexnow = GetrbwIndex((DiReal64)bit_config_sweep.RBW);  
		if(tempIndexnow != tempIndexcalc)
		{
			rbwTrigDoor = 1;
			DiInst_ConfigureSweepCoupling(devHandle,bit_config_sweep.RBWAuto,rbwList[tempIndexcalc],bit_config_sweep.VBWAuto,bit_config_sweep.VBW,bit_config_sweep.VBWTORBWAuto,bit_config_sweep.VBWTORBW);
			rbwTrigDoor = !rbwTrigDoor;
		}
	}
	//calculate params by sweet mode
	RefCalSweepParams(bit_config_sweep.sweepMode);

	//trig the resweep sig
	/*in the listen thread will down the ctrl param*/
	TrigResweep(NULL);
	return 0;
}

static void TrigResweep(void* param)
{
	INNERSOFTINTER = 1;
	return;
}

void GetSegmentWaveIndex(void* param)
{
	bit_config_sweep.StartFreq = 2600000000.;
	bit_config_sweep.StopFreq = 2700000000.;
								 
	//get the freq segment num
	DiInt32 istartIndex = GetFreqChannelIndex(bit_config_sweep.StartFreq);
	
	//back,means if the bound freq is startfreq,put it in the next part
	if(freqChannelList[istartIndex] <= bit_config_sweep.StartFreq + ESP)
	{
	   istartIndex++;
	} 
	
	DiInt32 istopIndex = GetFreqChannelIndex(bit_config_sweep.StopFreq);
	sweepnumList.segmentNum = istopIndex - istartIndex + 1;
	for(DiInt32 i = 0; i < sweepnumList.segmentNum; i++)
	{
		//start from zero index,cor with wave index and data nums
		sweepnumList.comNum[i].segmentIndex = istartIndex + i;
	}
	return;
}

/*
calc segment nums and per segment's data nums
*/
static void RefCalSweepParams(DiInt32 sweepMode)
{
	DiReal64 dStep = 0.0;
	DiUInt64 dSteptime = 0;
	DiInt32 ifftRbwIndex = 0;
	
	//clear sum time
	sweepnumList.sumSweeptime = 0;
	//FIR lo step freq
	if(0 == sweepMode)
	{
		dStep = sweepnumList.loStepHz; 
		dSteptime = 1;//normal to fs
	}
	else if(3 == sweepMode)
	{
		//lo step cor points
		dStep = sweepnumList.loStepHz / (sweepnumList.fftNum * sweepnumList.validRatio);
		ifftRbwIndex = GetFftRbwIndex();
		dSteptime = chparamlist[ifftRbwIndex].singleacqTime;
		//set single fft time
		sweepnumList.singlefftTime = chparamlist[ifftRbwIndex].singleacqTime;   
	}
	//other mode for future
	//calc every seg sweep time and sum sweep time and segment points num
	if(sweepnumList.segmentNum > 1)
	{
		DiInt32 iSize = sweepnumList.segmentNum - 1;
		DiReal64 dfreqspan = freqChannelList[sweepnumList.comNum[0].segmentIndex] - bit_config_sweep.StartFreq;
		//first seg time
		sweepnumList.comNum[0].persegsweeptimes = (DiUInt64)ceil(dfreqspan / sweepnumList.loStepHz) * dSteptime;
		sweepnumList.sumSweeptime += sweepnumList.comNum[0].persegsweeptimes;
		
		//first seg points num 
		sweepnumList.comNum[0].segmentDataNum = (DiUInt32)(dfreqspan / dStep);
		/*calc the freq div value of every segment start freq*/ 
		GetFreqDivValue(bit_config_sweep.StartFreq,&sweepnumList.comNum[0].seglostartfreqinter,&sweepnumList.comNum[0].seglostartfreqfrac);
		/*calc step div*/
		GetStepFrqDivValue(bit_config_sweep.StartFreq,dStep,&sweepnumList.comNum[0].seglosteplow,&sweepnumList.comNum[0].seglostephigh);
		
		for(DiInt32 i = 1; i < sweepnumList.segmentNum - 1; i++)
		{
			dfreqspan = freqChannelList[sweepnumList.comNum[i].segmentIndex] - freqChannelList[sweepnumList.comNum[i - 1].segmentIndex];
			sweepnumList.comNum[i].persegsweeptimes = (DiUInt64)ceil(dfreqspan / sweepnumList.loStepHz) * dSteptime; 
			sweepnumList.sumSweeptime += sweepnumList.comNum[i].persegsweeptimes;
			
			sweepnumList.comNum[i].segmentDataNum = (DiUInt32)(dfreqspan / dStep);
			GetFreqDivValue(freqChannelList[sweepnumList.comNum[i].segmentIndex],&sweepnumList.comNum[i].seglostartfreqinter,&sweepnumList.comNum[i].seglostartfreqfrac);
			GetStepFrqDivValue(freqChannelList[sweepnumList.comNum[i].segmentIndex],dStep,&sweepnumList.comNum[i].seglosteplow,&sweepnumList.comNum[i].seglostephigh); 
		}
		
		dfreqspan = bit_config_sweep.StopFreq - freqChannelList[sweepnumList.comNum[iSize].segmentIndex - 1];
		sweepnumList.comNum[iSize].persegsweeptimes = (DiUInt64)ceil(dfreqspan / sweepnumList.loStepHz) * dSteptime; 
		sweepnumList.sumSweeptime += sweepnumList.comNum[iSize].persegsweeptimes;
		
		//last segments nums
		sweepnumList.comNum[iSize].segmentDataNum = (DiUInt32)(dfreqspan / dStep);
		GetFreqDivValue(freqChannelList[sweepnumList.comNum[iSize].segmentIndex - 1],&sweepnumList.comNum[iSize].seglostartfreqinter,&sweepnumList.comNum[iSize].seglostartfreqfrac);
		GetStepFrqDivValue(freqChannelList[sweepnumList.comNum[iSize].segmentIndex - 1],dStep,&sweepnumList.comNum[iSize].seglosteplow,&sweepnumList.comNum[iSize].seglostephigh); 
	} 
	//only one segment
	else
	{
		/*calc every segment points*/
		sweepnumList.comNum[0].segmentDataNum = (DiUInt32)(bit_config_sweep.SPANFreq / dStep);
		/*calc the freq div value of every segment start freq*/
		GetFreqDivValue(bit_config_sweep.StartFreq,&sweepnumList.comNum[0].seglostartfreqinter,&sweepnumList.comNum[0].seglostartfreqfrac);
		GetStepFrqDivValue(bit_config_sweep.StartFreq,dStep,&sweepnumList.comNum[0].seglosteplow,&sweepnumList.comNum[0].seglostephigh);
		//calc sweep time
		//if fft mode
		if(3 == sweepMode)
		{
			sweepnumList.comNum[0].persegfftsegNum = bit_config_sweep.SPANFreq / sweepnumList.loStepHz;
			sweepnumList.sumSweeptime = sweepnumList.comNum[0].persegfftsegNum * dSteptime;
			sweepnumList.comNum[0].persegsweeptimes = sweepnumList.sumSweeptime;
		}
		//FIR
		else
		{
			sweepnumList.sumSweeptime = sweepnumList.comNum[0].segmentDataNum * dSteptime;
			sweepnumList.comNum[0].persegsweeptimes = sweepnumList.sumSweeptime; 
		}
	}  
	
	//UNDO
	//calc fft/fir bucket means how many points out one point
	//0411,fir 检波bucket使用时间，fft 检波bucket使用的是点数
	
	return;
}

static DiInt32 GetFftRbwIndex()
{
	DiInt32 iNum = sizeof(chparamlist) / sizeof(CHANNEL_PARAM);
	for(DiInt32 i = 0; i < iNum; i++)
	{
		if(bit_config_sweep.RBW >= (chparamlist+i)->rbwkHz)
			return i;
	}
	return iNum - 1;
}

static void GetFreqDivValue(DiReal64 freqHz,DiPUInt32 intdiv,DiPUInt32 fracdiv)
{
	DiInt32 iIndex = GetFreqChannelIndex(freqHz);
	iIndex = iIndex == 0 ? iIndex : iIndex - 1;
	DiReal64 temp = (freqHz + lodivList[iIndex].iffreq) / REF_CLOCK * lodivList[iIndex].d * lodivList[iIndex].r / lodivList[iIndex].feedback;
	
	*intdiv = (DiUInt32)temp;
	DiUInt64 tempfrac = (DiUInt64)ceil((temp - *intdiv) * 4 * (1 << 16) * (1 << 30)); 
	*fracdiv = (tempfrac & 0xffffffff);
	*intdiv <<= 16;
	*intdiv |= (tempfrac >> 32 & 0xffff);
	return;
}

void GetStepFrqDivValue(double startfreq,double stepHz,unsigned int* lowbits,unsigned int* highbits)
{
	DiInt32 iIndex = GetFreqChannelIndex(startfreq);
	iIndex = iIndex == 0 ? iIndex : iIndex - 1;
	double temp = stepHz / REF_CLOCK * lodivList[iIndex].d * lodivList[iIndex].r / lodivList[iIndex].feedback;
	DiUInt64 tempfrac = (DiUInt64)(temp * (1 << 24) * (1 << 24));
	*lowbits = tempfrac & 0xffffffff;
	*highbits = (tempfrac >> 32) & 0xffff;
	return;
}

/*
purpose:set first lo freq
func:SetFirstLoFreq
param:<in>devHandle:dev's ctrl handle from ini
      <out>loFreq:the freq of first lo Hz
return:>=0 is ok
 */
DiInt32 SetFirstLoFreq(DiSession devHandle,DiReal64 loFreq)
{
	DiInt32 iIndex = GetFreqChannelIndex(loFreq);
	iIndex = iIndex == 0 ? iIndex : iIndex - 1;
	DiReal64 temp = (loFreq + lodivList[iIndex].iffreq) / REF_CLOCK * lodivList[iIndex].d * lodivList[iIndex].r / lodivList[iIndex].feedback;
	DiUInt32 intpart = (DiUInt32)temp;
	DiUInt32 fracpart = 0;
	//DiUInt64 tempfrac = (DiUInt64)ceil((temp - intpart) * 4 * (1 << 30)); 
	DiUInt64 tempfrac = (DiUInt64)((temp - intpart) * 4 * (1 << 16) * (1 << 30));    
	fracpart = (tempfrac & 0xffffffff);
	intpart <<= 16;
	intpart |= (tempfrac >> 32 & 0xffff);
	return SetFirLoFreq(devHandle,intpart,fracpart);
}

/*
purpose: config center and span freq
func:DiInst_ConfigureFrequencyCenterSpan
param:<in>devHandle:dev's ctrl handle from ini
	  <in>centerFrequency:center freq in Hz
	  <in>span:span freq in Hz
	  value range:9kHz~32GHz
return:>=0 is ok
*/
DiInt32 DiInst_ConfigureFrequencyCenterSpan (DiSession devHandle,DiReal64 centerFrequency,DiReal64 span)
{
	//check params
	centerFrequency = centerFrequency < minFreqHz ? minFreqHz : centerFrequency;
	centerFrequency = centerFrequency > maxFreqHz ? maxFreqHz : centerFrequency;
	span = span < 0.0 ? 0.0 : span;

	DiInt32 iBack = 0;
	//adjust the span
	if(centerFrequency - 0.5 * span < minFreqHz)
	{
		iBack = DiInst_ConfigureFrequencyStartStop(devHandle,minFreqHz,2 * centerFrequency - minFreqHz);
	}
	else if(centerFrequency + 0.5 * span > maxFreqHz)
	{
		iBack = DiInst_ConfigureFrequencyStartStop(devHandle,centerFrequency * 2 - maxFreqHz,maxFreqHz);
	}
	else
	{
		iBack = DiInst_ConfigureFrequencyStartStop(devHandle,centerFrequency - span * 0.5,centerFrequency + span * 0.5);
	}
	return iBack;
}

/*
purpose: config sweep ctrl
func:DiInst_ConfigureSweepCoupling
param:<in>devHandle:dev's ctrl handle from ini
	  <in>resolutionBandwidthAuto: 1 auto;0 man
	  <in>resolutionBandwidth:5MHz~1Hz
	  <in>videoBandwidthAuto:1 auto;0 man
	  <in>videoBandwidth:3MHz~1Hz
	  <in>vbwtorbwAuto:1 auto;0 man
	  <in>vbwtorbwValue:>zero
return:>=0 is ok
*/
static DiInt32 rbwFlag = 0;//1 state changed
DiInt32 DiInst_ConfigureSweepCoupling (DiSession devHandle,DiUInt32 resolutionBandwidthAuto,DiReal64 resolutionBandwidth,DiUInt32 videoBandwidthAuto,DiReal64 videoBandwidth,DiUInt32 vbwtorbwAuto,DiReal64 vbwtorbwValue)
{
	//check and reflesh param
	resolutionBandwidthAuto = !!resolutionBandwidthAuto;
	bit_config_sweep.RBWAuto = resolutionBandwidthAuto;
	videoBandwidthAuto = !!videoBandwidthAuto;
	bit_config_sweep.VBWAuto = videoBandwidthAuto;
	vbwtorbwAuto = !!vbwtorbwAuto;
	bit_config_sweep.VBWTORBWAuto = vbwtorbwAuto; 
	
	rbwFlag = 0; 
	//adjust the couple param,when rbw is auto
	if(bit_config_sweep.RBWAuto)
	{
		//get the rbw through the span
		DiInt32 spanrbwIndex = GetrbwIndex(bit_config_sweep.SPANFreq * rbwtospan);
		DiInt32 nowIndex = GetrbwIndex((DiReal64)bit_config_sweep.RBW);   
		if(nowIndex != spanrbwIndex)
		{
			rbwFlag = 1;
			bit_config_sweep.RBW = (DiUInt32)rbwList[spanrbwIndex];
			GetLastPartTime(spanrbwIndex);
			if(bit_config_sweep.VBWAuto)
			{
				if(bit_config_sweep.VBWTORBWAuto)
				{
					bit_config_sweep.VBWTORBW = vbwtorbw;
				}
				else
				{
					bit_config_sweep.VBWTORBW = vbwtorbwValue;
				}
				DiInt32 iIndex = GetrbwIndex(bit_config_sweep.RBW * bit_config_sweep.VBWTORBW);
				iIndex = iIndex == 0 ? 1 : iIndex;
				bit_config_sweep.VBW = (DiUInt32)rbwList[iIndex];
			}
			else
			{
				DiInt32 vbwIndex = GetrbwIndex(videoBandwidth);
				bit_config_sweep.VBW = (DiUInt32)rbwList[vbwIndex];
			} 
			
			ParamConvertByRbw(spanrbwIndex); 
			//down rbw and vbw in the ctrlapp   
		}
	}
	//the rbw is man
	else
	{
		rbwFlag = 1;
		DiInt32 rbwIndex = GetrbwIndex(resolutionBandwidth);
		bit_config_sweep.RBW = (DiUInt32)rbwList[rbwIndex];
		GetLastPartTime(rbwIndex);
		//vbw is not 5MHz
		rbwIndex = rbwIndex == 0 ? 1 : rbwIndex;
		//more used
		if(bit_config_sweep.VBWAuto)
		{
			if(bit_config_sweep.VBWTORBWAuto)
			{
				bit_config_sweep.VBWTORBW = vbwtorbw;
			}
			else
			{
				bit_config_sweep.VBWTORBW = vbwtorbwValue;
			}
			bit_config_sweep.VBW = (DiUInt32)((DiInt32)rbwList[rbwIndex] * bit_config_sweep.VBWTORBW);
		}
		else
		{
			DiInt32 vbwIndex = GetrbwIndex(videoBandwidth);
			bit_config_sweep.VBW = (DiUInt32)rbwList[vbwIndex];
		}  
	
		ParamConvertByRbw(rbwIndex);
	} 
	
	#if TESTUNIT
	char tempchar[128];
	sprintf(tempchar,"扫描模式：%d,RBW:%dHz,VBW:%d，本振步进:%lf",bit_config_sweep.sweepMode,bit_config_sweep.RBW,bit_config_sweep.VBW,sweepnumList.loStepHz);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,tempchar);
	#endif
	
	if(!rbwTrigDoor && rbwFlag)
	{
		//recalc time
		RefCalSweepParams(bit_config_sweep.sweepMode); 
		//trig the resweep sig
		TrigResweep(NULL);
	}
	return 0;
}

static void ParamConvertByRbw(DiInt32 iIndex)
{
	DiInt32 tempIndex = 0;
	//get the sweep mode of FIR
	if(iIndex <= 6)
	{
		bit_config_sweep.sweepMode = 0x00;
		//calc lo step
		sweepnumList.loStepHz = bit_config_sweep.RBW * firStep;
	}
	else//FFT mode
	{
		tempIndex = GetFftRbwIndex();
		bit_config_sweep.sweepMode = 0x03;
		//calc lo step
		sweepnumList.loStepHz = chparamlist[tempIndex].stepFreqHz;
		//set fft num
		sweepnumList.fftNum = chparamlist[tempIndex].fftNum; 
		//set start and stop index
		sweepnumList.startIndex = sweepnumList.fftNum * (1 - chparamlist[tempIndex].validRatio) * 0.5;
		sweepnumList.stopIndex = sweepnumList.fftNum * (1 - chparamlist[tempIndex].validRatio * 0.5);
	}
	return;
}

static void GetLastPartTime(DiInt32 iIndex)
{
	/*the seg last part keep time is decided by rbw,ns*/
	sweepnumList.seglokeeptime = (DiUInt32)(dealTimeList[iIndex] / fstimens);
	return;
}

static DiInt32 GetrbwIndex(DiReal64 rbwHz)
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
purpose: config acq ctrl
func:DiInst_ConfigureAcquisition
param:<in>devHandle:dev's ctrl handle from ini
	  <in>sweepMode:continue or single or times
	  <in>numberOfTraces:show points
	  <in>detectorType:check mode
return:>=0 is ok
*/
DiInt32 DiInst_ConfigureAcquisition (DiSession devHandle,DiInt32 sweepMode,DiInt32 numberOfTraces,DiInt32 detectorType)
{
	//check param
	sweepMode &= 0x3;
	bit_config_sweep.SweepType = sweepMode;
	detectorType = detectorType > checkTypenum - 1 ? checkTypenum - 1 : detectorType;
	bit_config_sweep.DetectorMode = detectorType;
	bit_config_sweep.TracePoint = numberOfTraces;

	//down commands
	return 0;
}

/*
purpose: config level and atten ctrl
func:DiInst_ConfigureLevel
param:<in>devHandle:dev's ctrl handle from ini
	  <in>amplitudeUnits:
	  <in>inputImpedance:
	  <in>referenceLevel:
	  <in>referenceLevelOffset:
	  <in>attenuationAuto:
	  <in>attenuation:
return:>=0 is ok
*/
DiInt32 DiInst_ConfigureLevel (DiSession devHandle,DiInt32 amplitudeUnits,DiReal64 inputImpedance,DiReal64 referenceLevel,DiReal64 referenceLevelOffset,DiBoolean attenuationAuto,DiReal64 attenuation)
{

}

double acqOridata[3001];//acq data
double calcDataList[3001];//calc chery list,when state is sure,the list data is sure,so that providing the speed
int traceNum = 0;

double tempStartFreq = 10.0;//this will instead by shm
double tempStopFreq = 33.73;//this will instead by shm
int ConfigureRefLevel(double refLevel,int preAmpState,int attenAuto,double attenvalue,double* produceCalcdata,int tracenum)
{
	//if atten auto,means no matter with attenvalue
	double tempFreqDeta = (tempStartFreq - tempStopFreq) / (tracenum - 1);
	if(attenAuto)
	{
		//pre ampli is on
		if(preAmpState)
		{
			//
		
		}
		//pre ampli is off
		else
		{
		
		}
		
		//last setting preampli on and atten and if gain
		
	}
	//atten is man
	else
	{
		 if(preAmpState)
		 {
		 
		 }
		 else
		 {
		 
		 }
	}
	return 0;
}

///////////////////////////////////////////////////////////
//inner driver
static DiInt32 SetFirLoFreq(DiSession devHandle,DiUInt32 intseg,DiUInt32 fracseg)
{
	DiInt32 iBack = BitWrite32(devHandle,FIRLOSTARTFREQADDR,intseg);
	iBack = BitWrite32(devHandle,FIRLOSTARTFREQFRACADDR,fracseg);
    
	#if TESTUNIT
	char tempchar[128];
	sprintf(tempchar,"本振整数分频比:0x%x,小数分频比:0x%x",intseg,fracseg);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX_2,-1,tempchar);
	#endif 
	return iBack;
}

DiInt32 SetFirLoStepFreq(DiSession devHandle,DiUInt32 lowbit,DiUInt32 highbit)
{
	DiInt32 iBack = BitWrite32(devHandle,FIRLOSTEPLOWADDR,lowbit);
	iBack = BitWrite32(devHandle,FIRLOSTEPHIGHADDR,0);
	
	#if TESTUNIT
	char tempchar[128];
	sprintf(tempchar,"本振步进分频比低位:0x%x,高位:0x%x",lowbit,highbit);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX_2,-1,tempchar);
	#endif 
	return iBack;
}

DiInt32 SetFirLoStaytime(DiSession devHandle,DiUInt32 fsnum)
{
	DiInt32 iBack = BitWrite32(devHandle,FIRLOKEEPADDR,fsnum);
	
	#if TESTUNIT
	char tempchar[128];
	sprintf(tempchar,"本振最后一段保持时间fs个数:%d",fsnum);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX_2,-1,tempchar);
	#endif 
	return iBack;
}

DiInt32 SetSegPoint(DiSession devHandle,DiUInt32 pointsnum)
{
	DiInt32 iBack = BitWrite32(devHandle,SEGSWEEPNUMADDR,pointsnum);
		
	#if TESTUNIT
	char tempchar[128];
	sprintf(tempchar,"波段数据点数:%d\n",pointsnum);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX_2,-1,tempchar);
	#endif 
	return iBack;
}

/////////////////////////////////////////////////////////////////////////////////////
DiInt32 SetRbw(DiSession devHandle,DiReal64 rbwValue)
{
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,RBWVBWADDR,&iData);

	//convert the data to bit value
	DiInt32 iIndex = GetrbwIndex(rbwValue);

	//low 4 bit set 0
	iData &= 0xfffffff0;
	iData |= iIndex;

	//insert
	iBack = BitWrite32(devHandle,RBWVBWADDR,iData);
	return iBack;
}

DiInt32 SetVbw(DiSession devHandle,DiReal64 vbwValue)
{
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,RBWVBWADDR,&iData);
	DiInt32 iIndex = GetrbwIndex(vbwValue);  
	// 4-8 bit set 0
	iData &= 0xffffff0f;
	iData |= iIndex;
	//insert
	iBack = BitWrite32(devHandle,RBWVBWADDR,iData);
	return iBack;

}

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
	return iBack;
}

DiInt32 SetdataprocMode(DiSession devHandle,DiUInt32 dataproMode)
{
	dataproMode &= 0x00000002;

//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,DATAPROCMODEADDR,&iData);

	// 0~1 bit set 0
	iData &=  0xfffffffc;
	iData |= dataproMode;

	//insert
	iBack = BitWrite32(devHandle,DATAPROCMODEADDR,iData);
	return iBack;  
}

DiInt32 SetswpRun(DiSession devHandle)
{
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,SWPSTARTADDR,&iData);

	// 0 bit set 0
	iData &=  0xfffffffe;
	iData |= 1;

	//insert
	iBack = BitWrite32(devHandle,SWPSTARTADDR,iData);
	return iBack;
}

DiInt32 SetswpStop(DiSession devHandle)
{
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,SWPSTARTADDR,&iData);

	// 0 bit set 0
	iData &=  0xfffffffe;
	iData |= 0;   
	
	//insert
	iBack = BitWrite32(devHandle,SWPSTARTADDR,iData);
	return iBack;
}

DiInt32 SetCheckSegNum(DiSession devHandle,DiUInt32 segNum)
{
	segNum &= 0x1f;
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,CHECKSEGNUMADDR,&iData);
	
	iData &= 0xffffffe0;
	//bit0~4
	iBack = BitWrite32(devHandle,CHECKSEGNUMADDR,iData);
	return iBack;
}

DiInt32 SetzeroSpan(DiSession devHandle,DiUInt32 zeroSpan)
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
	return iBack;
}

DiInt32 SetdotswpTime(DiSession devHandle,DiUInt32 dotswpTime)
{ 
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,DOTSWPTIMEADDR,&iData);  
	// 0~31 bit set 0
	iData &=  0;
	iData |= dotswpTime; 
	//insert
	iBack = BitWrite32(devHandle,DOTSWPTIMEADDR,iData);
	return iBack;
}

DiInt32 SettotalswpTimeLow(DiSession devHandle,DiUInt32 totalswptimeLow)
{ 
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,TOTALSWPTIMELOWADDR,&iData);
	// 0~31 bit set 0
	iData &=  0x0;
	iData |= totalswptimeLow; 
	//insert
	iBack = BitWrite32(devHandle,TOTALSWPTIMELOWADDR,iData);
	return iBack;
}

DiInt32 SettotalswpTimeHight(DiSession devHandle,DiUInt32 totalswptimeHight)
{
	//high 16 bits set 0
	totalswptimeHight &= 0xffff;
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,TOTALSWPTIMEHIGHADDR,&iData);

	// 0~15 bit set 0
	iData &= 0xffff0000;
	iData |= totalswptimeHight;

	//insert
	iBack = BitWrite32(devHandle,TOTALSWPTIMEHIGHADDR,iData);
	return iBack;
}

DiInt32 SetdisplayNum(DiSession devHandle,DiUInt32 displayNum)
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
	return iBack;
}

DiInt32 SetdataaddrClr(DiSession devHandle,DiUInt32 dataaddrClr)
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
	return iBack;
}

DiInt32 SetfftbucketNum(DiSession devHandle,DiUInt32 fftbucketNum)
{
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,FFTBUCKETNUMADDR,&iData);

	// 0~31 bit set 0
	iData &=  0;
	iData |= fftbucketNum;

	//insert
	iBack = BitWrite32(devHandle,FFTBUCKETNUMADDR,iData);
	return iBack;
}

DiInt32 SetdetectorFlag(DiSession devHandle,DiUInt32 detectorFlag)
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
	return iBack;
}

DiInt32 SetaudioTime(DiSession devHandle,DiUInt32 audiotime)
{
	audiotime &= 0x0000000f ;
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,ANALOGDEMOD,&iData);

	// 0`3 bit set 0
	iData &=  0xfffffff0;
	iData |= audiotime;

	//insert
	iBack = BitWrite32(devHandle,ANALOGDEMOD,iData);
	return iBack;
}

DiInt32 SetaudioVolume(DiSession devHandle,DiUInt32 audioVolume)
{
	audioVolume &= 0x0000ffff ;
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,ANALOGDEMOD,&iData);

	// 4`19 bit set 0
	iData &=  0xfff0000f;
	iData |= (audioVolume<<4);
	 
	//insert
	iBack = BitWrite32(devHandle,ANALOGDEMOD,iData);
	return iBack;
}

DiInt32 SetaudioType(DiSession devHandle,DiUInt32 audioType)
{
	audioType &= 0x0000001f;
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,ANALOGDEMOD,&iData);

	// 20`24 bit set 0
	iData &=  0xfe0fffff;
	iData |= (audioType << 20);
	
	//insert
	iBack = BitWrite32(devHandle,ANALOGDEMOD,iData);
	return iBack;
}

DiInt32 SetaudioEn(DiSession devHandle,DiUInt32 audioEn)
{
	audioEn =!!audioEn;
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,AUDIOENADDR,&iData);

	//0 bit set 0
	iData &=  0xfffffffe;
	iData |= audioEn;
 
	//insert
	iBack = BitWrite32(devHandle,AUDIOENADDR,iData);
	return iBack;
}

DiInt32 SetfftcalNum(DiSession devHandle,DiUInt32 fftcalNum)
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
	return iBack;
}

DiInt32 SetfftDirection(DiSession devHandle,DiUInt32 fftDirection)
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
	return iBack;
}

DiInt32 SetfftvalidstartNum(DiSession devHandle,DiUInt32 fftvalidstartNum)
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
	return iBack;
}

DiInt32 SetfftvalidendNum(DiSession devHandle,DiUInt32 fftvalidendNum)
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
	return iBack;
}

DiInt32 SetfftdotswpTime(DiSession devHandle,DiUInt32 fftdotswpTime)
{
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,FFTDOTSWPTIMEADDR,&iData);

	//0~31 bit set 0
	iData &=  0;
	iData |= fftdotswpTime;

	//insert
	iBack = BitWrite32(devHandle,FFTDOTSWPTIMEADDR,iData);
	return iBack;
}

DiInt32 SetbuckettrigTime(DiSession devHandle,DiUInt32 buckettrigTime)
{
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,BUCKETTRIGTIMEADDR,&iData);

	//0~31 bit set 0
	iData &=  0;
	iData |= buckettrigTime;

	//insert
	iBack = BitWrite32(devHandle,BUCKETTRIGTIMEADDR,iData);
	return iBack;
}

DiInt32 SetrbwvbwdelayTime(DiSession devHandle,DiUInt32 rbwvbwdelayTime)
{
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,RBWVBWDELAYTIMEADDR,&iData);

	//0~31 bit set 0
	iData &=  0;
	iData |= rbwvbwdelayTime;
	
	//insert
	iBack = BitWrite32(devHandle,RBWVBWDELAYTIMEADDR,iData);
	return iBack;
}

DiInt32 SettrigType(DiSession devHandle,DiUInt32 trigType)
{
	trigType &= 0x00000002;
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,TRIGTYPEANDDIRECTADDR,&iData);

	//0~1 bit set 0
	iData &=  0xfffffffc;
	iData |= trigType;

	//insert
	iBack = BitWrite32(devHandle,TRIGTYPEANDDIRECTADDR,iData);
	return iBack;
}

DiInt32 SettrigDirect(DiSession devHandle,DiUInt32 trigDirect)
{
	trigDirect &=0x00000001;
	trigDirect = !!trigDirect;
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,TRIGTYPEANDDIRECTADDR,&iData);

	//2 bit set 0
	iData &=  0xfffffffd;
	iData |= (trigDirect << 2);
	
	//insert
	iBack = BitWrite32(devHandle,TRIGTYPEANDDIRECTADDR,iData);
	return iBack;
}

DiInt32 SettrigTime(DiSession devHandle,DiUInt32 trigTime)
{
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,TRIGTIMEADDR,&iData);

	//0~31 bit set 0
	iData &=  0;
	iData |= trigTime;
		
	//insert
	iBack = BitWrite32(devHandle,TRIGTIMEADDR,iData);
	return iBack;
}

DiInt32 SettrigAmp(DiSession devHandle,DiUInt32 trigAmp)
{
	//get the ori data
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,TRIGAMPADDR,&iData);
	//0~31 bit set 0
	iData &=  0;
	iData |= trigAmp;
	//insert
	iBack = BitWrite32(devHandle,TRIGAMPADDR,iData);
	return iBack;
}
