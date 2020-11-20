//==============================================================================
//
// Title:		TestinWin
// Purpose:		A short description of the application.
//
// Created on:	2017/12/15 at 17:25:14 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <ansi_c.h>
#include <cvirte.h>
#include <userint.h>
#include "TestinWin.h"
#include "toolbox.h"
#include "RfVirtualDriver.h"
#include "MainBoardVirtualDriver.h"
//#include "bitplattype.h"
#include "BitVisaType.h"
#include "SaDataStruct.h"
#include "SaAnalysis.h"
#include <visa.h>
#include "CalcPointAlog.h"

#include "SaCalcThread.h"
//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

int panelHandle = 0;
static void UnitTest(void* param);
//==============================================================================
// Static functions
//extern DiInt32 GetrbwIndex(DiReal64 rbwHz);
//==============================================================================
// Global variables

//==============================================================================
// Global functions
static _CONFIG_SWEEP bit_config_sweep1[2];
void TestFunc(int* param);
extern DiInt32 StartListenThread();
extern DiInt32 StartAcqThread();
extern DiInt32 interflag;
extern DiInt32 INNERSOFTINTER;
void IniParam();

extern void GetSegmentWaveIndex(void* param);

char* ipath = "saclacconfig\\freqlist.txt";
FREQLIST parainfo;
/// HIFN The main entry-point function.

ViSession bitSession = 0;
ViSession devHandle = 0;

extern void GetSourceParam();
extern int GoSaCalc(void* param);
extern int GoCalc(void* param);  

extern int GetAllCalcData(void);
#define IXS_CenterFreq							0x00000001
#define IXS_SpanFreq							0x00000002
#define IXS_StartFreq							0x00000004
#define IXS_StartFreq1							0x00000008


DiInt32 SetTotalSwtTimeUs(DiSession devHandle,DiReal64 sumTime)
{
	DiInt32 iBack = 0;
	DiUInt64 isum = (DiUInt64)(sumTime * 10);
	DiUInt32 ifrac = (DiUInt32)((sumTime * 10 - isum) * 0xff);
	ifrac |= (isum << 8 & 0xffffff00);
	return iBack;
}


char fu[64];
/////////////
#define INFLUENCENUM 8
#define OVERNUM 1000
static void ResampleInsert(DiPReal64 poribuffer,DiInt32 orinum,DiInt32 dataindex,DiPReal64 poutbuffer,DiInt32 outnum,DiPReal64 refunc,DiInt32 refnum);
static void ResampleInsert(DiPReal64 poribuffer,DiInt32 orinum,DiInt32 dataindex,DiPReal64 poutbuffer,DiInt32 outnum,DiPReal64 refunc,DiInt32 refnum)
{
	//to decide which oridata to use for inserting,and the max num is influence << 1 - 1
	DiInt32 istart = 0;
	DiInt32 istop = 0;

	//the model is 8 1 8,total is 17
	//left part ori data num <= 8,include dataindex
	if(dataindex <= INFLUENCENUM)//index not num
	{
		istart = 0;
	}
	else
	{
		istart = dataindex - INFLUENCENUM;
	}

	//right part ori data num <= 8
	if(dataindex + INFLUENCENUM >= orinum)//index not num
	{
		istop = orinum - 1;
	}
	else
	{
		istop = dataindex + INFLUENCENUM;
	}

	//action use ori data num
	DiInt32 actnum = istop - istart + 1;
	DiInt32 leftnum = dataindex - istart + 1;
	DiInt32 rightnum = istop - dataindex;

	DiReal64 dstepindex = 0.1 * 10 * (OVERNUM - 2)  / outnum;
	//Do insert action
	DiInt32 i = 0;
	DiInt32 j = 0;

	for(i = 0; i < outnum; i++)
	{
		*(poutbuffer + i) = 0.0;
		//
		for(j = 0; j < leftnum; j++)
		{
			*(poutbuffer + i) += *(poribuffer + istart + j) * *(refunc + (leftnum - j - 1) * OVERNUM + (DiInt32)((j + 1) * dstepindex));
		}
		//
		for(j = 0; j < rightnum; j++)
		{
			*(poutbuffer + i) += *(poribuffer + dataindex + j + 1) * *(refunc +  j * OVERNUM + OVERNUM - (DiInt32)((j + 1) * dstepindex));
		}
	}
	return;
}


double insert[8001];
double A = 0.0;
double B = 0.0;

extern void GetStepFrqDivValue(double startfreq,double stepHz,unsigned int* lowbits,unsigned int* highbits); 
int main (int argc, char *argv[])
{

    /*
	insert[0]  = 1;
	A = 1000 / PI;
	B = PI / 1000;
	  int i = 0;
	for(i = 1; i < 8001; i++)
	{
		insert[i] = 1 *  A * sin(B * i) / i;
	}
	*/
	int error = 0;

	//SetTotalSwtTimeUs(0,17.799);
	//GetSegmentWaveIndex(NULL);
	//GetAllCalcData();
	//unsigned int wh = 454313445;
	//printf("0x%x",wh);
	//double calcBuffer[501];
	errChk(GoCalc(NULL));     
	//CalcWhenPreAmpOff(11000000000.0,12500000000.0,501,calcBuffer);
	//errChk(GoSaCalc(NULL));
	//MessagePopup("Attention","Change the source to SA");
	//errChk(GoSaCalc(NULL));

	//GetParamFromFile(ipath,&parainfo);
	/*
	int istatus = viOpenDefaultRM (&bitSession);
	istatus = viOpen(bitSession,"GPIB0::13::INSTR",VI_NULL, VI_NULL, &devHandle);

	int iNum = 0;
	viSetAttribute (devHandle, VI_ATTR_TERMCHAR_EN, VI_TRUE);
	viSetAttribute (devHandle, VI_ATTR_TERMCHAR, 0xa);

	viWrite(devHandle,"*IDN?\n",strlen("*IDN?\n"),&iNum);

	char bitbuffer[256];
	viRead(devHandle,bitbuffer,256,&iNum);

	viClose(devHandle);
	viClose(bitSession);
	  */
	/*
	DiUInt64 X = 910222950400000;
	DiUInt64 L = 3416260608;
	DiUInt64 H = 15319;
	int a = sizeof(DiUInt64);
	unsigned long long num1 = 1024 * 1024 ;
	unsigned long long num2 = 1024 * 1024;
	unsigned long long num = num1 * num2 + 12154;
	unsigned int low = num & 0xffffffff;
	unsigned int high = num >> 32 & 0xffffffff;
	//a = sizeof(w);
	TestFunc(&a);



	memcpy(bit_config_sweep1+1,bit_config_sweep1,sizeof(_CONFIG_SWEEP));
	int k = 0;
	k = sizeof(long long);
	k = 0x80000000;
	k = 1<< 14;
	k = (1<<13) | (0<<12) | (1<<9) | (0<<8) | (0<<1) | (0<<0);

	double t = 0.0;
	t = 45.625 / 5.625;
	int i = (int)(ceil(t));
	IniParam();
	  */

	/* initialize and load resources */
	nullChk (InitCVIRTE (0, argv, 0));
	errChk (panelHandle = LoadPanel (0, "TestinWin.uir", PANEL));
	//ZeroRestrainPhaseCtrl(0,45.625);
	/* display the panel and run the user interface */
	errChk (DisplayPanel (panelHandle));
	//GoCalc(NULL);
	//GoSaCalc(NULL);
	//SetFirstLoFreq(0,1.3665e9);
	//SetFirstLoFreq(0,2.36635e9);
	//SetFirstLoFreq(0,2.3664e9);
	//SetFirstLoFreq(0,2.36645e9);
	//SetFirstLoFreq(0,2.3665e9); 

#if 0
	unsigned int low = 0;
	unsigned int high = 0;
	GetStepFrqDivValue(15.5e9,100e3,&low,&high);
	
	char tempchar[128];
	sprintf(tempchar,"本振步进低位:0x%x,高位:0x%x",low,high);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX_2,-1,tempchar);
	
#endif
	/*
	int tempBuffer[] = {0xfff555 ,
	0xfff556 ,
	0xfff557 ,
	0xfff558 ,

	0xfff570 ,
	0xfff571 ,
	0xfff572 ,
	0xfff573 ,

	0xfff603 ,
	0xfff604 ,
	0xfff605 ,

	0xfff1054,
	0xfff1055};

	int iNum = sizeof(tempBuffer) / sizeof(int);
	double* mk  = (double*)malloc(sizeof(double) * iNum);
	for(int i = 0;i<iNum;i++)
	{
	   *(mk + i)  = 20 * log((double)tempBuffer[i]);
	}

	PlotY(panelHandle,PANEL_GRAPH,mk,iNum,VAL_DOUBLE,VAL_THIN_LINE,VAL_SOLID_SQUARE,VAL_SOLID,VAL_CONNECTED_POINTS,VAL_RED);
	*/
	//SetFirstLoFreq(0,8e9);
	//SetFirstLoFreq(0,9e9);
	//SetFirstLoFreq(0,23.6e9);

	//SetFirstLoFreq(0,10.0e9);
	/*
		SetFirstLoFreq(0,19.99e9);

			SetFirstLoFreq(0,24.63375e9);
		SetFirstLoFreq(0,25.63375e9);

			SetFirstLoFreq(0,26.63375e9);
		SetFirstLoFreq(0,27.63375e9);

			SetFirstLoFreq(0,28.63375e9);
		SetFirstLoFreq(0,29.63375e9);

			SetFirstLoFreq(0,30.63375e9);
		SetFirstLoFreq(0,31.63375e9);

			SetFirstLoFreq(0,32e9);
		 */

//	SetFirstLoFreq(0,23.01e9);

	//	SetFirstLoFreq(0,1366250000);
//	SetFirstLoFreq(0,2600000000);
	//	SetFirstLoFreq(0,29500000000);
	//SetFirstLoFreq(0,1356250000);
	//	SetFirstLoFreq(0,1376250000);

//	SetFirstLoFreq(0,100000000.0);
	/*
		SetFirstLoFreq(0,2000000000.0);
		SetFirstLoFreq(0,3000000000.0);
		SetFirstLoFreq(0,5000000000.0);
			SetFirstLoFreq(0,8000000000.0);
				SetFirstLoFreq(0,10000000000.0);
		SetFirstLoFreq(0,12000000000.0);
		SetFirstLoFreq(0,14000000000.0);
		SetFirstLoFreq(0,16000000000.0);
			SetFirstLoFreq(0,17000000000.0);
		SetFirstLoFreq(0,18000000000.0);
		SetFirstLoFreq(0,20000000000.0);
			 */
	//SetFirstLoFreq(0,10000000000.0);
	///SetFreq(0,0,EVENT_COMMIT,NULL,0,0);
	///SetBW(0,0,EVENT_COMMIT,NULL,0,0);

	///StartListenThread();
	///StartAcqThread();

	/*
	int    g_canvasWidth;
	int    g_canvasHeight;

	GetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_HEIGHT, &g_canvasHeight);
	GetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_WIDTH, &g_canvasWidth);
	SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_ENABLE_ANTI_ALIASING, 1);
	CanvasStartBatchDraw (panelHandle, PANEL_CANVAS);
	//CanvasDrawLine (panelHandle, PANEL_CANVAS,MakePoint (10, 10),MakePoint (g_canvasWidth-10, g_canvasHeight-10));
	for(int i = 0; i <= 10; i++)
	{
		CanvasDrawLine (panelHandle, PANEL_CANVAS,MakePoint (10,10+ i * (g_canvasHeight - 20) / 10 ),MakePoint (g_canvasWidth-10, 10 + i * (g_canvasHeight - 20) / 10 ));
		CanvasDrawLine (panelHandle, PANEL_CANVAS,MakePoint (10 + i * (g_canvasWidth - 20) / 10,10),MakePoint (10 + i * (g_canvasWidth - 20) / 10, g_canvasHeight-10));
	}
	CanvasEndBatchDraw (panelHandle, PANEL_CANVAS);
	*/
	errChk (RunUserInterface ());

Error:
	/* clean up */
	if (panelHandle > 0)
		DiscardPanel (panelHandle);
	return 0;
}

int GetCalcDataWhenPreAmpOn(double startfreq,double stopfreq,int datanum,int autoflag,double manatten,double* calcresult);
int GetCalcDataWhenPreAmpOff(double startfreq,double stopfreq,int datanum,int autoflag,double manatten,double* calcresult);
DiInt32 GetCalcDataWhenPreAmpOffZeroSpan(double freq,int datanum,int autoflag,double manatten,double* calcresult) ;
DiInt32 GetCalcDataWhenPreAmpOnZeroSpan(double freq,int datanum,int autoflag,double manatten,double* calcresult) ;
extern double tempREF;
double showdata[801];
int NUM = 801;

double *ptest;
extern double GetMaxValue(double* buffer,int isize);
int CVICALLBACK TestRefAndAtten (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	double stafreq,stopfreq,ref,atten = 0.0;
	int autoflag = 0;
	static int plotHandle = 0;
	double t0,t1 = 0.0;
	double dmax = 0.;
	int i = 0;
	
	int tempsum = 78;
	int k = 0;
	int m = 0;
	int gperinsertintpart = 0;
	double gperinsertfracpart = 0.0;
	 DiReal64 tempfrac = 0.;
	 double gperinsertnum = 0.0;
	 int trueinsertnum = 0;
	 
	 double midCalcBuffer[801] = {0.0};
	 double acqLocBuffer[801] = {0.0};
	switch (event)
	{
		case EVENT_COMMIT:
			//MessagePopup("daf","fdaf");		 
			 ptest = (double*)malloc(1024 * 1024);
			
			return 0;
			GetCtrlVal(panelHandle,PANEL_NUMERIC_10,&stafreq);
			GetCtrlVal(panelHandle,PANEL_NUMERIC_9,&stopfreq);
			GetCtrlVal(panelHandle,PANEL_NUMERIC_12,&ref);
			GetCtrlVal(panelHandle,PANEL_NUMERIC_11,&atten);
			GetCtrlVal(panelHandle,PANEL_BINARYSWITCH_4,&autoflag);
			tempREF = ref;
			t0 = Timer();
			//GetCalcDataWhenPreAmpOnZeroSpan(stafreq,NUM,autoflag,atten,showdata);
			GetCalcDataWhenPreAmpOn(stafreq,stopfreq,NUM,autoflag,atten,showdata);
			//GetCalcDataWhenPreAmpOnZeroSpan(stafreq,NUM,autoflag,atten,showdata);
			//GetCalcDataWhenPreAmpOn(stafreq,stopfreq,NUM,autoflag,atten,showdata);
			t1 = Timer();
			SetCtrlVal(panelHandle,PANEL_NUMERIC_13,(t1-t0));
			if(plotHandle)
			{
				DeleteGraphPlot(panelHandle,PANEL_GRAPH,plotHandle,VAL_IMMEDIATE_DRAW);
			}
			plotHandle = PlotY(panelHandle,PANEL_GRAPH,showdata,NUM,VAL_DOUBLE,VAL_THIN_LINE,VAL_SOLID_SQUARE,VAL_SOLID,VAL_CONNECTED_POINTS,VAL_GREEN);
#if 0
			for(i = 0; i < 501; i++)
			{
				showdata[i] = 5 * sin(2 * PI * i / 501);
			}

			plotHandle = PlotY(panelHandle,PANEL_GRAPH,showdata,NUM,VAL_DOUBLE,VAL_THIN_LINE,VAL_SOLID_SQUARE,VAL_SOLID,VAL_CONNECTED_POINTS,VAL_GREEN);
#endif

#if 0
			/*
			   for(i = 0;i < 301;i++)
				{
					insert[i] = 100 * cos(2 * PI * i / 300) - 80;
				}
			*/


				 for(m = 0;m < 801;m++)
				 {					  
				 	 acqLocBuffer[m] = midCalcBuffer[m] = Random(2.5,13.56);
				 }
			
				gperinsertnum = (0.1 * 10 * 801 - tempsum) / (tempsum - 1);
				gperinsertintpart = (DiInt32)gperinsertnum;
				gperinsertfracpart = gperinsertnum - gperinsertintpart;
		
		
			for(m = 0; m < tempsum - 1; m++)
			{
				tempfrac += gperinsertfracpart;
				if(tempfrac - 1.0 > -1.0e-6)
				{
					tempfrac -= 1.0;
					trueinsertnum = gperinsertintpart + 1;
				}
				else
				{
					trueinsertnum = gperinsertintpart;
				}


				acqLocBuffer[k++] = midCalcBuffer[m];
				ResampleInsert(midCalcBuffer,tempsum,m,acqLocBuffer + k,trueinsertnum,insert,8001);
				k += trueinsertnum;
			}
			acqLocBuffer[++k] = midCalcBuffer[tempsum - 1];


			plotHandle = PlotY(panelHandle,PANEL_GRAPH,acqLocBuffer,801,VAL_DOUBLE,VAL_THIN_LINE,VAL_SOLID_SQUARE,VAL_SOLID,VAL_CONNECTED_POINTS,VAL_GREEN);
#endif


			dmax = GetMaxValue(showdata,501);

			t0 = Timer();
			for(int i = 0; i < NUM; i++)
			{
				showdata[i] += 3.1541;
			}
			t1 = Timer();

			SetCtrlVal(panelHandle,PANEL_NUMERIC_14,(t1-t0));
			break;
	}
	return 0;
}

int CVICALLBACK ReceiveInterrupt (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{

	int a,b,c,d,e;
	int i = 0;
	switch (event)
	{
		case EVENT_COMMIT:
			for(i = 0; i < 100; i++)
			{
				interflag = 1;
				a = rand() % 10;
				b = rand() % 10;
				while(b == a)
				{
					b = rand() % 10;
				}
				c = rand() % 10;
				while(c == a || c == b)
				{
					c = rand() % 10;
				}
				d = rand() % 10;
				while(d == a || d == b ||  d ==c)
				{
					d = rand() % 10;
				}
				e = rand() % 10;
				while(e == d || e == c || e == b || e == a)
				{
					e = rand() % 10;
				}
				sprintf(fu,"%d,%d,%d,%d,%d",a,b,c,d,e);
				InsertTextBoxLine(panelHandle,PANEL_TEXTBOX_2,-1,fu);
			}
			break;
	}
	return 0;
}

int CVICALLBACK SetFreq (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	double dcenter = 0.0;
	double dspan = 0.0;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panelHandle,PANEL_NUMERIC_4,&dcenter);
			GetCtrlVal(panelHandle,PANEL_NUMERIC_5,&dspan);
			DiInst_ConfigureFrequencyCenterSpan(0,dcenter,dspan);
			break;
	}
	return 0;
}

int CVICALLBACK SetBW (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	int rbwauto = 0;
	int vbwauto = 0;
	int vbwtorbwauto = 0;
	double rbw = 0.0;
	double vbw = 0.0;
	double vbwtorbw = 0.0;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panelHandle,PANEL_NUMERIC_6,&rbw);
			GetCtrlVal(panelHandle,PANEL_NUMERIC_7,&vbw);
			GetCtrlVal(panelHandle,PANEL_NUMERIC_8,&vbwtorbw);

			GetCtrlVal(panelHandle,PANEL_BINARYSWITCH,&rbwauto);
			GetCtrlVal(panelHandle,PANEL_BINARYSWITCH_2,&vbwauto);
			GetCtrlVal(panelHandle,PANEL_BINARYSWITCH_3,&vbwtorbwauto);
			DiInst_ConfigureSweepCoupling(0,rbwauto,rbw,vbwauto,vbw,vbwtorbwauto,vbwtorbw);
			break;
	}
	return 0;
}

void TestFunc(int* param)
{
	int b = 0;
	param = &b;
	return;
}

//==============================================================================
// UI callback function prototypes

/// HIFN Exit when the user dismisses the panel.
int CVICALLBACK panelCB (int panel, int event, void *callbackData,
						 int eventData1, int eventData2)
{
	if (event == EVENT_CLOSE)
		QuitUserInterface (0);
	return 0;
}

int CVICALLBACK StartTest (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			free(ptest);
			return 0;
			UnitTest(NULL);
			break;
	}
	return 0;
}

extern _CONFIG_SWEEP bit_config_sweep;
static const DiReal64 freqList[] = {100,9000.0,100004.0,1366250000.0,1366250140,2600000000.0,2600005000,7500000000.0,7500040000,9500000000.0,
									9500000070,12300000000.0,12330000000,15700000000.0,15700700000,16300000000.0,16300007000,19500000000.0,
									19500009000,23633750000.0,23633750400,26500000000.0,26510000000,27833750000.0,27833750700,29500000000.0,29500500000,32000000000.0,33000000000
								   };

static void UnitTest(void* param)
{

	int iBack = 0;
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"频段划分测试用例执行");
	int ilen = sizeof(freqList) /sizeof(DiReal64);
	for(int i = 0; i<ilen; i++)
	{
		RfChannelChoose(0,freqList[i]);
	}

	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"频段划分测试用例执行完成");
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"------------------------");
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"相位设置测试用例执行");

	DiReal64 dphase = 0.0;
	iBack = ZeroRestrainPhaseCtrl(0,-1.25);
	while(dphase <= 354.375)
	{
		iBack = ZeroRestrainPhaseCtrl(0,dphase);
		dphase+=5.625/2.0;
	};
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"相位设置测试用例执行完成");
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"------------------------");

	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"设置DA值测试用例执行");
	iBack = ZeroRestrainAttenCtrl(0,-10);
	iBack = ZeroRestrainAttenCtrl(0,0);
	iBack = ZeroRestrainAttenCtrl(0,56841);
	iBack = ZeroRestrainAttenCtrl(0,0xffff);
	iBack = ZeroRestrainAttenCtrl(0,0xffff+10);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"设置DA值测试用例执行完成");
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"------------------------");

	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"设置二中频衰减器测试用例执行");
	dphase = -1.0;
	while(dphase <= 31.0)
	{
		iBack = SecIfAttenCtrl(0,dphase);
		dphase+= 0.5;
	};
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"设置二中频衰减器测试用例执行完成");
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"------------------------");


	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"高波段频衰减器测试用例执行");
	dphase = -1.0;
	while(dphase <= 31.0)
	{
		iBack = PreAttenCtrl(0,dphase);
		dphase+= 0.5;
	};
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"高波段衰减器测试用例执行完成");
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"------------------------");

	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"高波段前置放大通路测试用例执行");
	iBack = PreAmpliChannelCtrl(0,0);
	iBack = PreAmpliChannelCtrl(0,1);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"高波段前置放大通路测试用例执行完成");
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"------------------------");


	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"低波段频衰减器测试用例执行");
	dphase = -1.0;
	while(dphase <= 31.0)
	{
		iBack = LowFreqPreAttenCtrl(0,dphase);
		dphase+= 0.5;
	};
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"低波段衰减器测试用例执行完成");
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"------------------------");


	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"低波段前置放大通路测试用例执行");
	iBack = LowFreqPreAmpliChannelCtrl(0,0);
	iBack = LowFreqPreAmpliChannelCtrl(0,1);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"低波段前置放大通路测试用例执行完成");
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"------------------------");

	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"二本振分频比测试用例执行");
	SecLoOutfreqCtrl(0,9000000000);
	SecLoOutfreqCtrl(0,8900000000);
	SecLoOutfreqCtrl(0,9026000000);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"二本振分频比测试用例执行完成");
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"------------------------");

	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"内外参考测试用例执行");
	InOutRefCtrl(0,0);
	InOutRefCtrl(0,1);
	InOutRefCtrl(0,-10);
	InOutRefCtrl(0,10);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"内外参考测试用例执行完成");
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"------------------------");

	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"微波段衰减器测试用例执行");
	dphase = -2.5;
	while(dphase <= 31.0)
	{
		iBack = MicroFreqPreAttenCtrl(0,dphase);
		dphase+= 2.5;
	};
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"微波段衰减器测试用例执行完成");
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"------------------------");

	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"微波段低噪放通路设置测试用例执行");
	MicroFreqPreAmpliChannelCtrl(0,0);
	MicroFreqPreAmpliChannelCtrl(0,1);
	MicroFreqPreAmpliChannelCtrl(0,-5);
	MicroFreqPreAmpliChannelCtrl(0,6);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"微波段低噪放通路设置测试用例执行完成");
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"------------------------");

	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"晶振电压设置测试用例执行");
	SetOsciVolt(0,1.5);
	SetOsciVolt(0,3);
	SetOsciVolt(0,2.5);
	SetOsciVolt(0,3.3);
//	SetOsciVolt(0,4.2);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"晶振电压设置测试用例执行完成");
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"------------------------");

	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"中频增益设置测试用例执行");
	IFGainCtrl(0,10.56);
	IFGainCtrl(0,20);
	IFGainCtrl(0,30);
	IFGainCtrl(0,40);
	IFGainCtrl(0,50);
	IFGainCtrl(0,60);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"中频增益设置测试用例执行完成");
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"------------------------");

	/*
	int ii = GetrbwIndex(6.0e6);
	char cc[64];
	sprintf(cc,"rbw的索引是%d",ii);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,cc);
	ii = GetrbwIndex(3.5e6);
	sprintf(cc,"rbw的索引是%d",ii);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,cc);
	ii = GetrbwIndex(5.0e6);
	sprintf(cc,"rbw的索引是%d",ii);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,cc);
	ii = GetrbwIndex(1.3);
	sprintf(cc,"rbw的索引是%d",ii);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,cc);
	*/
	bit_config_sweep.RBW = 1000000;
	bit_config_sweep.VBWAuto = 1;
	bit_config_sweep.VBWTORBWAuto = 0;
	bit_config_sweep.VBWTORBW = 10;
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"------------------------");
	//DiInst_ConfigureFrequencyStartStop(0,9500.0,20.0e9);
	DiInst_ConfigureFrequencyCenterSpan(0,1000000000.0,600000000.0);
	DiInst_ConfigureFrequencyCenterSpan(0,1000000000.0,60000.0);
	DiInst_ConfigureFrequencyCenterSpan(0,1000000000.0,30.0);
	DiInst_ConfigureFrequencyCenterSpan(0,1000000000.0,2900000.0);
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"------------------------");

	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"------------------------");
	bit_config_sweep.SPANFreq = 2000000000;
	DiInst_ConfigureSweepCoupling(0,1,1000000,0,300000,1,1.0);
	/*
	bit_config_sweep.SPANFreq = 100000000;
	DiInst_ConfigureSweepCoupling(0,1,300,1,300000,1,1.0);
	bit_config_sweep.SPANFreq = 333000;
	DiInst_ConfigureSweepCoupling(0,0,1000000,1,300000,1,1.0);
	bit_config_sweep.SPANFreq = 10000;
	DiInst_ConfigureSweepCoupling(0,0,100000,0,300000,1,1.0);
	*/
	InsertTextBoxLine(panelHandle,PANEL_TEXTBOX,-1,"------------------------");
	return;
}





