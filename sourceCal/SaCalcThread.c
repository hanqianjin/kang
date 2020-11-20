//==============================================================================
//
// Title:		SaCalcThread.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/3/21 at 16:02:00 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <windows.h>
#include <toolbox.h>
#include <ansi_c.h>
#include <userint.h>
#include <utility.h>
#include <visa.h>
#include "RfVirtualDriver.h"
#include "SaCalcThread.h"
#include "CalcPointAlog.h"
#include "DiIoCtrl.h"
#include "MainBoardVirtualDriver.h"
#include "TestinWin.h"


extern int panelHandle;

//==============================================================================
// Constants
static int Y = 1;
//==============================================================================
// Types
typedef struct
{
	int index;
	double freqHz;
	double ampdB;
} FREQAMPLIST, *PFREQAMPLIST;

PFREQAMPLIST maplist = NULL;
//==============================================================================
// Static global variables
static const double PREC = 0.03;
static const int CIRCLENUM = 20;
#ifdef BIT_F238
static const char* path = "saclacconfig\\freqlist.txt";
#endif

#ifdef BIT_F239
static const char* path = "saclacconfig\\freqlist_239.txt";   
#endif

#ifdef BIT_F238_SMART
static const char* path = "saclacconfig\\freqlist_238_smart.txt";   
#endif
//==============================================================================
// Static functions
static int CVICALLBACK CalcFunc(void *functionData);
static int SetSourOutputPower(double outpower);
static int SetSourceOutFreq(double ofreq);
static int SetPowerMeterFreq(double freq);
static int SetHoldMode(int hold);
static int GetPower(double* power);
static int PowerMeterSelfCalc(void);
static int  SetBufferClear();
//==============================================================================
// Global variables
FREQLIST bitFreqList;
const double PER = 0.0000001;
//==============================================================================
// Global functions
int GoCalc(void* param);
int GoSaCalc(void* param);
int GetSourceCalcResultParam();

double powerlistpoints[] = {10,5,0.0,-5.0,-10.0,-15.0,-20.0,-25.0,-30.0,-35.0};		//for source
///double powerlistpoints[] = {10.0,5.0,0.0,-5.0,-10.0,-15.0,-20.0,-25.0,-30.0,-35.0};		//for source
//-20 used in the off mode,from -20 to -50 ,20 as if ref
//-30 used also in the on mode,from -30 to -60,-30 as if ref
double powerlistpoint[] = {-20.0,-30.0,-40.0,-50.0,-60.0}; //for source
double freqpoint = 100.0e6;//if gain calc

//double powerlistpointsampoff[] = {10,10,10,10,10.0,5.0,0.0,-5.0,-10.0,-15.0,-20.0}; //for sa	source value
double powerlistpointsampoff[] = {3.0,5.0,0.0,-5.0,-10.0,-15.0,-20.0}; //for sa	source value
double powerlistpointsampon[] = {-5.0,-10.0,-15.0,-20.0,-25.0,-30.0,-35.0}; //for sa

typedef struct
{
	double refLevel;
	double atten;
	double ifGain;
} CHANNELGAIN,*PCHANNELGAIN;

CHANNELGAIN ifGainOff[] =
{
	//{20,50,30},
	//{20,45,30},
//	{20,40,30},
//	{20,35,30},//the first four items only used in handle mode,1030

	{20,30,30},
	{15,25,30},
	{10,20,30},
	{5,15,30},
	{0,10,30},
	{-5,5,30},
	{-10,0,30},
};

CHANNELGAIN ifGainOn[] =
{
	{0,30,30},
	{-5,25,30},
	{-10,20,30},
	{-15,15,30},
	{-20,10,30},
	{-25,5,30},
	{-30,0,30}
};

int manaHandle = 0;
int sourHandle = 0;
int powermeterHandle = 0;
int saHandle = 0;
static const int BUFFERSIZE = 256;
char commandBuffer[BUFFERSIZE];
static CmtThreadFunctionID threadID = 0; //线程句柄

static int CVICALLBACK CalcSaFunc(void *functionData);
static CmtThreadFunctionID threadSaID = 0; //线程句柄

static int OpenManager();
static int OpenMeter();
static int OpenSource();
static int OpenSa();

static void GetLog(double* buffer,int isize);

extern DiReal64 freqChannelList[];

DiInt32 GetCalcDataWhenPreAmpOffZeroSpan(double freq,int datanum,int autoflag,double manatten,double* calcresult);

DiInt32 GetCalcDataWhenPreAmpOnZeroSpan(double ferq,int datanum,int autoflag,double manatten,double* calcresult);
//==============================================================================
#define SOURCESIMU 1
int GoCalc(void* param)
{
	int istatus = 0;
	//ini source and power meter
#if SOURCESIMU
	if(OpenManager() < 0)
	{
		MessagePopup("error","manager failed");
	}  
	if(OpenMeter() < 0)
	{
		 MessagePopup("error","meter failed");
	}
	if(OpenSource() < 0)
	{
		 MessagePopup("error","source failed");  
	}
#endif 
	
	//PowerMeterSelfCalc();
	//MessagePopup("Attention","Change the sensor line");

	//get freq list
	GetParamFromFile(path,&bitFreqList);

	//start thread
	return istatus = CmtScheduleThreadPoolFunctionAdv (
						 DEFAULT_THREAD_POOL_HANDLE, CalcFunc, NULL,
						 THREAD_PRIORITY_NORMAL, NULL, EVENT_TP_THREAD_FUNCTION_END, NULL, CmtGetCurrentThreadID(),
						 &threadID);

}

static int OpenManager()
{
	return viOpenDefaultRM (&manaHandle);
}

static int OpenSource()
{
	int iNum = 0,istatus = 0;
	istatus = viOpen(manaHandle,"TCPIP::192.168.26.252::5025::SOCKET",VI_NULL, VI_NULL, &sourHandle);
	if(istatus < 0)
	{
	MessagePopup("error","Lan connect failed");
	}
	viSetAttribute (sourHandle, VI_ATTR_TERMCHAR_EN, VI_TRUE);
	viSetAttribute (sourHandle, VI_ATTR_TERMCHAR, 0xa);

	memset(commandBuffer,0,BUFFERSIZE);
	sprintf(commandBuffer,":OUTPUT 1\n");
	viWrite(sourHandle,commandBuffer,strlen(commandBuffer),&iNum);
	Sleep(50);
	
	return istatus;
}

static int OpenSa()
{
	int iNum = 0,istatus = 0;
	istatus = viOpen(manaHandle,"TCPIP::192.168.254.132::5555::SOCKET",VI_NULL, VI_NULL, &saHandle);
	viSetAttribute (saHandle, VI_ATTR_TERMCHAR_EN, VI_TRUE);
	viSetAttribute (saHandle, VI_ATTR_TERMCHAR, 0xa);
	Sleep(50);
	return istatus;
}

static int OpenMeter()
{
	int istatus = 0;
	istatus = viOpen(manaHandle,"GPIB0::13::INSTR",VI_NULL, VI_NULL, &powermeterHandle);
	viSetAttribute (powermeterHandle, VI_ATTR_TERMCHAR_EN, VI_TRUE);
	viSetAttribute (powermeterHandle, VI_ATTR_TERMCHAR, 0xa);
	SetBufferClear();
	return istatus;
}

//this part is for analog source calc
static int CVICALLBACK CalcFunc(void *functionData)
{
#ifdef BIT_F238
	FILE *resultfp = fopen("saclacconfig\\soureccalcresult.txt","w");
#endif
#ifdef BIT_F239
	FILE *resultfp = fopen("saclacconfig\\soureccalcresult_239.txt","w");   
#endif
#ifdef BIT_F238_SMART
	FILE *resultfp = fopen("saclacconfig\\soureccalcresult_238_smart.txt","w");   
#endif
	fprintf(resultfp,"No. freqHz  powerdB\n");
	
	double metervalue = 0.0;
	double inioutput = 0.0;
	double detavalue = 0.0;

	int i = 0,j = 0;
	int powerlistpointsnum = sizeof(powerlistpoints) / sizeof(double);

	int iTimes = 0;
	int iIndex = 0;
	int w = 0;
	char d[128];
	
	int icir = 1;
	for(j = 0; j < powerlistpointsnum; j++)
	{
		
		inioutput = powerlistpoints[j];
		for(i = 0; i < bitFreqList.count; i++)
		{
#if SOURCESIMU
			SetSourceOutFreq(*(bitFreqList.param+i));
			SetPowerMeterFreq(*(bitFreqList.param+i));
#endif
			//inioutput = powerlistpoints[j];
			detavalue = 0.0;
			iTimes = 0;
			icir = 1;
#if SOURCESIMU	
			do
			{
				inioutput += detavalue;
				//set source output

				if(iTimes == CIRCLENUM && icir)
				{
					inioutput = powerlistpoints[j];
					detavalue = 0.0;
					iTimes = 0;  
					icir = 0;
				}
		
				SetSourOutputPower(inioutput);  
				//read meter value
				//SetHoldMode(0);

				
			
				GetPower(&metervalue); 
				sprintf(d,"freq %lf,source:%lf,meter:%lf",*(bitFreqList.param+i),inioutput,metervalue);
				
				
				w++;
				if(w > 30)
				{
					w = 0;
					DeleteTextBoxLines (panelHandle,PANEL_TEXTBOX_2,0,-1);  
				}
				else
				{
				InsertTextBoxLine(panelHandle,PANEL_TEXTBOX_2,-1,d); 
				}
				
				//get detavalue
				detavalue = (powerlistpoints[j] - metervalue);
				
				
				//if(fabs(detavalue) > 5.0)				 g
				//{
				//	MessagePopup("attention","there is a hole");
				//}
				
			}
			while(fabs(detavalue) > PREC && iTimes++ <= CIRCLENUM);
#endif  		
			fprintf(resultfp,"%d    %.01lf    %.2lf\n",iIndex++,*(bitFreqList.param+i),inioutput);
		}
	}

	fclose(resultfp);
#if  SOURCESIMU
	viClose(powermeterHandle);
	viClose(sourHandle);
	viClose(manaHandle); 
#endif 
	return 0;
}
//over 2018/04/13

//===============================================================================================
static int SetSourOutputPower(double outpower)
{
	int iBack = 0;
	memset(commandBuffer,0,BUFFERSIZE);
	sprintf(commandBuffer,":POWER %lf\n",outpower);
	iBack = viPrintf(sourHandle,commandBuffer);
	Sleep(100);
	return iBack;
}

//set lo outfreq
static int SetSourceOutFreq(double ofreq)
{
	int iBack = 0;
	memset(commandBuffer,0,BUFFERSIZE);
	sprintf(commandBuffer,":FREQ %f\n",ofreq);
	iBack = viPrintf(sourHandle,commandBuffer);
	Sleep(100);
	return iBack;
}
static int SetBufferClear()
{
	memset(commandBuffer,0,BUFFERSIZE);

	sprintf(commandBuffer,"BUFF OFF\n");

	int itrueNum = 0;
	int iBack = viWrite(powermeterHandle,commandBuffer,strlen(commandBuffer),&itrueNum);
	Sleep(100);
	return iBack;
}
//Set the frequency.
static int SetPowerMeterFreq(double freq)
{
	memset(commandBuffer,0,BUFFERSIZE);

	sprintf(commandBuffer,"CFFRQ A,%lf\n",freq);

	int itrueNum = 0;
	int iBack = viWrite(powermeterHandle,commandBuffer,strlen(commandBuffer),&itrueNum);
	Sleep(100);
	return iBack;
}

// Set the maintance mode.
//in param:hold, 0:automatic mode,
static int SetHoldMode(int hold)
{
	memset(commandBuffer,0,BUFFERSIZE);

	sprintf(commandBuffer,"RGH A,%d\n",hold);

	int itrueNum = 0;
	int iBack = viWrite(powermeterHandle,commandBuffer,strlen(commandBuffer),&itrueNum);
	Sleep(500);
	return iBack;
}

//Get current power.
static int GetPower(double* power)
{
	memset(commandBuffer,0,BUFFERSIZE);

	sprintf(commandBuffer,"O 1\n");

	int itrueNum = 0;
	int iBack = viWrite(powermeterHandle,commandBuffer,strlen(commandBuffer),&itrueNum);
	Sleep(200);
	if(iBack < 0)
		return iBack;

	memset(commandBuffer,0,BUFFERSIZE);
	iBack = viRead(powermeterHandle,commandBuffer,BUFFERSIZE,&itrueNum);	   
	if(iBack >= 0)
		sscanf(commandBuffer,"%lf",power);
	return iBack;
}

static int PowerMeterSelfCalc(void)
{
	memset(commandBuffer,0,BUFFERSIZE);
	sprintf(commandBuffer,"CAL A\n");

	int itrueNum = 0;
	int iBack = viWrite(powermeterHandle,commandBuffer,strlen(commandBuffer),&itrueNum);
	Sleep(100);
	return iBack;
}

//==================================================================================================
//ctrl_api
CALCRESULTLIST preOffCalcResult; //the buffer size is freqNum * ampNum + extraNum
CALCRESULTLIST preOnCalcResult;  //the same


int ProBufferForpreoff(PCALCRESULTLIST pbuffer,int iNum);
int ProBufferForpreon(PCALCRESULTLIST pbuffer,int iNum);

int ProBufferForpreoff(PCALCRESULTLIST pbuffer,int iNum)
{
	return ResizeArray(pbuffer, iNum);
}

int ProBufferForpreon(PCALCRESULTLIST pbuffer,int iNum)
{
	return ResizeArray(pbuffer, iNum);
}

int GetAllCalcData(void);
int GetAllCalcData(void)
{
	int iBack = GetParamFromFile(path,&bitFreqList);
	if(iBack < 0)
		return iBack;

	FILE *fp;
	fp = fopen("saclacconfig\\sacalcresult.txt", "r");
	if (NULL == fp)
	{
		return -1;
	}
	char titlestr[64];
	fscanf(fp,"%s %s %s",titlestr,titlestr,titlestr);

	int iampNum = sizeof(powerlistpointsampoff) / sizeof(double);
	int iBsize = iampNum * bitFreqList.count;
	iBack = ProBufferForpreoff(&preOffCalcResult,iBsize);
	if(iBack < 0)
		return iBack;

	int i = 0;
	int ii = 0;
	double ff = 0.0;
	for(i = 0; i < iBsize; i++)
	{
		fscanf(fp,"%d  %lf %lf",&ii,&ff,preOffCalcResult.param + i);
	}

	iampNum = sizeof(powerlistpointsampon) / sizeof(double);
	iBsize = bitFreqList.count * iampNum;
	iBack = ProBufferForpreon(&preOnCalcResult,iBsize);
	if(iBack < 0)
		return iBack;

	for(i = 0; i < iBsize; i++)
	{
		fscanf(fp,"%d  %lf %lf",&ii,&ff,preOnCalcResult.param + i);
	}

	fclose(fp);
	return 0;
}

double calcdata[801];

double preAtten = 0.0;//pre atten ctrl
double ifAmp = 0.0;//if ampifier
int SetIfgainByReflevel(double refLevel,double* ifamp)
{
	if(refLevel > -50.0)
		*ifamp = 30;
	else if(refLevel > -60.0)
		*ifamp = 40;
	else if(refLevel > -70.0)
		*ifamp = 50;
	else
		*ifamp = 60;
	return 0;
}

int GetCalcDataWhenPreAmpOff(double startfreq,double stopfreq,int datanum,int autoflag,double manatten,double* calcresult);
int GetCalcDataWhenPreAmpOn(double startfreq,double stopfreq,int datanum,int autoflag,double manatten,double* calcresult);
static int GetpreOffAttenIndex(double refLevel);
static void GetStartAndStopIndex(double freqHz,int serStart,int* startIndex,int* stopIndex,int islastpoint);//islastpoint 0 means last point
static int GetAttenIndexOff(double attendB);
static int GetpreOnAttenIndex(double refLevel);
static int GetAttenIndexOn(double attendB);

double lastifgain = 30.0;//save last ifgain value for man mode

double tempREF = 0.0;
double attendB = 0.0;
int atuoflag = 0;//1 auto


static const double ATTENZERODOORWHENOFF = -5.0;
static const double ATTENZEROWHENOFF = -10.0;
static const double IFGAINMINWHENOFF = -180.0;

static const double IFGAINMIN = 30.0; 
//when set refLevel or atten,the mid msg object will do hardware ctrl,
//and trig the action to get the calc data again;

char tempmsg[128];
int GetCalcDataWhenPreAmpOff(double startfreq,double stopfreq,int datanum,int autoflag,double manatten,double* calcresult)
{
	autoflag = !!autoflag;
	double mstep = (stopfreq - startfreq) / (datanum - 1);
	double mfreq = 0.0;
	double mfdeta = 0.0;
	int i = 0,istart = 0,istop = 0;
	int iBack = 0;


	int ioverflow = 0;//when un 0 means freq is over the largest freq;
	if(autoflag)
	{
		int index0,index1 = 0;
		int setchannelIndex = 0;
		double deta = 0.0;

		//means will used -10dB datas
		if(tempREF < ATTENZERODOORWHENOFF)
		{
			index0 = GetpreOffAttenIndex(ATTENZEROWHENOFF);
			setchannelIndex = index0;
			int icalcIndex0 = bitFreqList.count * index0;

			//< -5.0 ~ -180.0,means using -10.0dB calc datas
			//means deta value is 0,direct use calc datas
			//Linear interpolation for filling datas
			for(i = 0; i < datanum; i++)
			{
				//get freq location,start index and stop index
				mfreq = startfreq + i * mstep;
				GetStartAndStopIndex(mfreq,istart,&istart,&istop,(i + 1) % datanum);
				mfdeta = mfreq - *(bitFreqList.param + istart);
				if(0 == ioverflow)
				{
					if(mfreq >= 43000000000.)
					{
						ioverflow = istart - 1;
					}
				}
				if(mfdeta < 0.0)
				{
					calcresult[i] = *(preOffCalcResult.param + icalcIndex0 + istart);
				}
				else if(mfreq >= 43000000000.)
				{
					calcresult[i] = *(preOffCalcResult.param + icalcIndex0 + ioverflow);
				}
				else
				{
					calcresult[i] = mfdeta * (*(preOffCalcResult.param + icalcIndex0 + istop)  - *(preOffCalcResult.param + icalcIndex0 + istart))
									/ (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOffCalcResult.param + icalcIndex0 + istart);
				}
			}
		}
		else
		{
			index0 = GetpreOffAttenIndex(tempREF);
			sprintf(tempmsg,"%d",index0);
			MessagePopup("zidong",tempmsg);
			//1030
			index0 = index0 == 0 ? 4 : index0;

			int icalcIndex0 = bitFreqList.count * index0;
			setchannelIndex = index0;
			for(i = 0; i < datanum; i++)
			{
				//1119 steve
				//get freq location,start index and stop index
				mfreq = startfreq + i * mstep;

				GetStartAndStopIndex(mfreq,istart,&istart,&istop,(i + 1) % datanum);
				mfdeta = mfreq - *(bitFreqList.param + istart);
				if(0 == ioverflow)
				{
					if(mfreq >= 43000000000.)
					{
						ioverflow = istart - 1;
					}
				}
				if(mfdeta < 0.0)
				{
					calcresult[i] = *(preOffCalcResult.param + icalcIndex0 + istart);
				}
				else if(mfreq >= 43000000000.)
				{
					calcresult[i] = *(preOffCalcResult.param + icalcIndex0 + ioverflow);
				}
				else
				{
					calcresult[i] = mfdeta * (*(preOffCalcResult.param + icalcIndex0 + istop)  - *(preOffCalcResult.param + icalcIndex0 + istart))
									/ (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOffCalcResult.param + icalcIndex0 + istart);
				}
			}
		}

#if Y
		//set IFgain,pre amp off and atten
		iBack = PreAmpliChannelCtrl(0,0);
		iBack = PreAttenCtrl(0,ifGainOff[setchannelIndex].atten);
#endif
	}
	//in the man mode,means only set atten,and ref\ifgain not change
	else
	{
		//calc needed calc datas
		int inowindex = GetAttenIndexOff(manatten);
		
			sprintf(tempmsg,"%d",inowindex);
			MessagePopup("shoudong",tempmsg);
		int icalcIndex0 = bitFreqList.count * inowindex;
		for(i = 0; i < datanum; i++)
		{
			mfreq = startfreq + i * mstep;
			GetStartAndStopIndex(mfreq,istart,&istart,&istop,(i + 1) % datanum);
			mfdeta = mfreq - *(bitFreqList.param + istart);

			//calcdata
			if(0 == ioverflow)
			{
				if(mfreq >= 43000000000.)
				{
					ioverflow = istart - 1;
				}
			}
			if(mfdeta < 0.0)
			{
				calcresult[i] = *(preOffCalcResult.param + icalcIndex0 + istart);
			}
			else if(mfreq >= 43000000000.)
			{
				calcresult[i] = *(preOffCalcResult.param + icalcIndex0 + ioverflow);
			}
			else
			{
				calcresult[i] = mfdeta * (*(preOffCalcResult.param + icalcIndex0 + istop)  - *(preOffCalcResult.param + icalcIndex0 + istart))
								/ (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOffCalcResult.param + icalcIndex0 + istart);
			}
		}
#if Y
		iBack = PreAttenCtrl(0,manatten);
		//only set sa pre atten and pre amp off
		iBack = PreAmpliChannelCtrl(0,0);
#endif
	}
	return 0;
}

static const double ATTENZERODOORWHENON = -25.0;
static const double ATTENZEROWHENON = -30.0;
static const double IFGAINMINWHENON = -40.0;
static const double REFWITHOUTHARDWHENON = -70.0;

//20180420
int GetCalcDataWhenPreAmpOn(double startfreq,double stopfreq,int datanum,int autoflag,double manatten,double* calcresult)
{
	char tete[128];
	autoflag = !!autoflag;
	double mstep = (stopfreq - startfreq) / (datanum - 1);
	double mfreq = 0.0;
	double mfdeta = 0.0;
	int i = 0,istart = 0,istop = 0;
	int iBack = 0;
	//means set atten auto
	int ioverflow = 0;//when un 0 means freq is over the largest freq;
	if(autoflag)
	{
		int index0,index1 = 0;
		int setchannelIndex = 0;
		double deta = 0.0;

		//means will used -10dB datas
		if(tempREF < ATTENZERODOORWHENON)
		{
			index0 = GetpreOnAttenIndex(ATTENZEROWHENON);
			setchannelIndex = index0;
			int icalcIndex0 = bitFreqList.count * index0;

			//means deta value is 0,direct use calc datas
			//Linear interpolation for filling datas
			for(i = 0; i < datanum; i++)
			{
				//get freq location,start index and stop index
				mfreq = startfreq + i * mstep;
				GetStartAndStopIndex(mfreq,istart,&istart,&istop,(i + 1) % datanum);
				mfdeta = mfreq - *(bitFreqList.param + istart);
				if(0 == ioverflow)
				{
					if(mfreq >= 43000000000.)
					{
						ioverflow = istart - 1;
					}
				}
				if(mfdeta < 0.0)
				{
					calcresult[i] = *(preOnCalcResult.param + icalcIndex0 + istart);
				}
				else if(mfreq >= 43000000000.)
				{
					calcresult[i] = *(preOnCalcResult.param + icalcIndex0 + ioverflow);
				}
				else
				{
					calcresult[i] = mfdeta * (*(preOnCalcResult.param + icalcIndex0 + istop)  - *(preOnCalcResult.param + icalcIndex0 + istart))
									/ (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOnCalcResult.param + icalcIndex0 + istart);
				}
			}
		}
		else
		{
			index0 = GetpreOnAttenIndex(tempREF);
			int icalcIndex0 = bitFreqList.count * index0;
			setchannelIndex = index0;
			for(i = 0; i < datanum; i++)
			{
				//get freq location,start index and stop index
				mfreq = startfreq + i * mstep;
				GetStartAndStopIndex(mfreq,istart,&istart,&istop,(i + 1) % datanum);
				mfdeta = mfreq - *(bitFreqList.param + istart);
				if(0 == ioverflow)
				{
					if(mfreq >= 43000000000.)
					{
						ioverflow = istart - 1;
					}
				}
				if(mfdeta < 0.0)
				{
					calcresult[i] = *(preOnCalcResult.param + icalcIndex0 + istart);	  
				}
				else if(mfreq >= 43000000000.)
				{
					calcresult[i] = *(preOnCalcResult.param + icalcIndex0 + ioverflow);
				}
				else
				{
					calcresult[i] = mfdeta * (*(preOnCalcResult.param + icalcIndex0 + istop)  - *(preOnCalcResult.param + icalcIndex0 + istart))
									/ (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOnCalcResult.param + icalcIndex0 + istart);
				}
			}
		}

#if Y
		//set pre amp off and atten
		iBack = PreAmpliChannelCtrl(0,1);
		iBack = PreAttenCtrl(0,ifGainOn[setchannelIndex].atten);	 
#endif
	}
	//in the man mode,means only set atten,and ref not change
	else
	{
		//calc needed calc datas
		//use lastatten and now atten to get the deta datas
		int inowindex = GetAttenIndexOn(manatten);
		int icalcIndex0 = bitFreqList.count * inowindex;
		for(i = 0; i < datanum; i++)
		{
			mfreq = startfreq + i * mstep;
			GetStartAndStopIndex(mfreq,istart,&istart,&istop,(i + 1) % datanum);
			mfdeta = mfreq - *(bitFreqList.param + istart);
			//calcdata
			if(0 == ioverflow)
			{
				if(mfreq >= 43000000000.)
				{
					ioverflow = istart - 1;
				}
			}
			if(mfdeta < 0.0)
			{
				calcresult[i] = *(preOnCalcResult.param + icalcIndex0 + istart);
			}
			else if(mfreq >= 43000000000.)
			{
				calcresult[i] = *(preOnCalcResult.param + icalcIndex0 + ioverflow);
			}
			else
			{
				calcresult[i] = mfdeta * (*(preOnCalcResult.param + icalcIndex0 + istop)  - *(preOnCalcResult.param + icalcIndex0 + istart))
								/ (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOnCalcResult.param + icalcIndex0 + istart);
			}
		}
#if Y
		iBack = PreAttenCtrl(0,manatten);
		//only set sa pre atten and pre amp off
		iBack = PreAmpliChannelCtrl(0,1);
#endif
	}
	//trig resweep,UNDO
	return 0;
}


//0503
DiInt32 GetCalcDataWhenPreAmpOffZeroSpan(double freq,int datanum,int autoflag,double manatten,double* calcresult)
{
	autoflag = !!autoflag;
	double mfreq = freq;
	double mfdeta = 0.0;
	int istart = 0,istop = 0;
	int iBack = 0;
	//means set atten and IF gain auto
	int ioverflow = 0;//when un 0 means freq is over the largest freq;
	if(autoflag)
	{
		int index0,index1 = 0;
		int setchannelIndex = 0;
		double deta = 0.0;

		//means will used -10dB datas
		if(tempREF < ATTENZERODOORWHENOFF)
		{
			index0 = GetpreOffAttenIndex(ATTENZEROWHENOFF);
			setchannelIndex = index0;
			int icalcIndex0 = bitFreqList.count * index0;

			//means deta value is 0,direct use calc datas
			//Linear interpolation for filling datas
			GetStartAndStopIndex(mfreq,istart,&istart,&istop,0);
			mfdeta = mfreq - *(bitFreqList.param + istart);
			if(0 == ioverflow)
			{
				if(mfreq >= 43000000000.)
				{
					ioverflow = istart - 1;
				}
			}
			if(mfdeta < 0.0)
			{
				calcresult[0] = *(preOffCalcResult.param + icalcIndex0 + istart);
			}
			else if(mfreq >= 43000000000.)
			{
				calcresult[0] = *(preOffCalcResult.param + icalcIndex0 + ioverflow);
			}
			else
			{
				calcresult[0] = mfdeta * (*(preOffCalcResult.param + icalcIndex0 + istop)  - *(preOffCalcResult.param + icalcIndex0 + istart))
								/ (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOffCalcResult.param + icalcIndex0 + istart);
			}
		}
		else
		{
			index0 = GetpreOffAttenIndex(tempREF);
			//1030
			index0 = index0 == 0 ? 4 : index0;
			int icalcIndex0 = bitFreqList.count * index0;
			setchannelIndex = index0;

			//get freq location,start index and stop index
			GetStartAndStopIndex(mfreq,istart,&istart,&istop,0);
			mfdeta = mfreq - *(bitFreqList.param + istart);
			if(0 == ioverflow)
			{
				if(mfreq >= 43000000000.)
				{
					ioverflow = istart - 1;
				}
			}
			if(mfdeta < 0.0)
			{
				calcresult[0] = *(preOffCalcResult.param + icalcIndex0 + istart);
			}
			else if(mfreq >= 43000000000.)
			{
				calcresult[0] = *(preOffCalcResult.param + icalcIndex0 + ioverflow);
			}
			else
			{
				calcresult[0] = mfdeta * (*(preOffCalcResult.param + icalcIndex0 + istop)  - *(preOffCalcResult.param + icalcIndex0 + istart))
								/ (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOffCalcResult.param + icalcIndex0 + istart);
			}
		}

#if Y
		//set IFgain,pre amp off and atten
		iBack = PreAmpliChannelCtrl(0,0);
		iBack = PreAttenCtrl(0,ifGainOff[setchannelIndex].atten);
#endif
	}
	//in the man mode,means only set atten,and ref\ifgain not change
	else
	{
		//calc needed calc datas
		//use lastatten and now atten to get the deta datas
		int inowindex = GetAttenIndexOff(manatten);

		int icalcIndex0 = bitFreqList.count * inowindex;

		GetStartAndStopIndex(mfreq,istart,&istart,&istop,0);
		mfdeta = mfreq - *(bitFreqList.param + istart);
		if(0 == ioverflow)
		{
			if(mfreq >= 43000000000.)
			{
				ioverflow = istart - 1;
			}
		}
		if(mfdeta < 0.0)
		{
			calcresult[0] = *(preOffCalcResult.param + icalcIndex0 + istart);
		}
		else if(mfreq >= 43000000000.)
		{
			calcresult[0] = *(preOffCalcResult.param + icalcIndex0 + ioverflow);
		}
		else
		{
			//calcdata
			calcresult[0] = mfdeta * (*(preOffCalcResult.param + icalcIndex0 + istop)  - *(preOffCalcResult.param + icalcIndex0 + istart))
							/ (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOffCalcResult.param + icalcIndex0 + istart);
		}
#if Y
		iBack = PreAttenCtrl(0,manatten);
		//only set sa pre atten and pre amp off
		iBack = PreAmpliChannelCtrl(0,0);
#endif
	}
	int i = 1;
	for(i = 1; i < datanum; i++ )
	{
		calcresult[i] = calcresult[0];
	}
	return 0;
}


DiInt32 GetCalcDataWhenPreAmpOnZeroSpan(double ferq,int datanum,int autoflag,double manatten,double* calcresult)
{
	autoflag = !!autoflag;
	double mfreq = ferq;
	double mfdeta = 0.0;
	int iBack = 0;
	int istart = 0,istop = 0;
	//means set atten and IF gain auto
	int ioverflow = 0;//when un 0 means freq is over the largest freq;
	if(autoflag)
	{
		int index0,index1 = 0;
		int setchannelIndex = 0;
		double deta = 0.0;

		//means will used -10dB datas
		if(tempREF < ATTENZERODOORWHENON)
		{
			index0 = GetpreOnAttenIndex(ATTENZEROWHENON);
			setchannelIndex = index0;
			int icalcIndex0 = bitFreqList.count * index0;

			//means deta value is 0,direct use calc datas
			//Linear interpolation for filling datas

			//get freq location,start index and stop index
			GetStartAndStopIndex(mfreq,istart,&istart,&istop,0);
			mfdeta = mfreq - *(bitFreqList.param + istart);
			if(0 == ioverflow)
			{
				if(mfreq >= 43000000000.)
				{
					ioverflow = istart - 1;
				}
			}
			if(mfdeta < 0.0)
			{
				calcresult[0] = *(preOnCalcResult.param + icalcIndex0 + istart);
			}
			else if(mfreq >= 43000000000.)
			{
				calcresult[0] = *(preOnCalcResult.param + icalcIndex0 + ioverflow);
			}
			else
			{
				calcresult[0] = mfdeta * (*(preOnCalcResult.param + icalcIndex0 + istop)  - *(preOnCalcResult.param + icalcIndex0 + istart))
								/ (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOnCalcResult.param + icalcIndex0 + istart);
			}

		}
		else
		{
			index0 = GetpreOnAttenIndex(tempREF);
			int icalcIndex0 = bitFreqList.count * index0;
			setchannelIndex = index0;
			GetStartAndStopIndex(mfreq,istart,&istart,&istop,0);
			mfdeta = mfreq - *(bitFreqList.param + istart);
			if(0 == ioverflow)
			{
				if(mfreq >= 43000000000.)
				{
					ioverflow = istart - 1;
				}
			}
			if(mfdeta < 0.0)
			{
				calcresult[0] = *(preOnCalcResult.param + icalcIndex0 + istart);
			}
			else if(mfreq >= 43000000000.)
			{
				calcresult[0] = *(preOnCalcResult.param + icalcIndex0 + ioverflow);
			}
			else
			{
				calcresult[0] = mfdeta * (*(preOnCalcResult.param + icalcIndex0 + istop)  - *(preOnCalcResult.param + icalcIndex0 + istart))
								/ (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOnCalcResult.param + icalcIndex0 + istart);
			}
		}

#if Y
		//set pre amp on and atten
		iBack = PreAmpliChannelCtrl(0,1);
		iBack = PreAttenCtrl(0,ifGainOn[setchannelIndex].atten);
#endif
	}
	//in the man mode,means only set atten,and ref\ifgain not change
	else
	{
		//calc needed calc datas
		//use lastatten and now atten to get the deta datas
		int inowindex = GetAttenIndexOn(manatten);
		int icalcIndex0 = bitFreqList.count * inowindex;

		GetStartAndStopIndex(mfreq,istart,&istart,&istop,0);
		mfdeta = mfreq - *(bitFreqList.param + istart);
		//calcdata
		if(0 == ioverflow)
		{
			if(mfreq >= 43000000000.)
			{
				ioverflow = istart - 1;
			}
		}
		if(mfdeta < 0.0)
		{
			calcresult[0] = *(preOnCalcResult.param + icalcIndex0 + istart);
		}
		else if(mfreq >= 43000000000.)
		{
			calcresult[0] = *(preOnCalcResult.param + icalcIndex0 + ioverflow);
		}
		else
		{
			calcresult[0] = mfdeta * (*(preOnCalcResult.param + icalcIndex0 + istop)  - *(preOnCalcResult.param + icalcIndex0 + istart))
							/ (*(bitFreqList.param + istop) - *(bitFreqList.param + istart)) + *(preOnCalcResult.param + icalcIndex0 + istart);
		}

#if Y
		iBack = PreAttenCtrl(0,manatten);
		//only set sa pre atten and pre amp on
		iBack = PreAmpliChannelCtrl(0,1);
#endif
	}
	int i = 1;
	for(i = 1; i < datanum; i++ )
	{
		calcresult[i] = calcresult[0];
	}
	//trig resweep,UNDO
	return 0;
}

static void GetStartAndStopIndex(double freqHz,int serStart,int* startIndex,int* stopIndex,int islastpoint)
{
	int i = 0,j = 0;
#ifdef BIT_F239
	int ilen = 15; //0503 UNDO,get the num from ini
#endif
#ifdef BIT_F238_SMART
	int ilen = 8;
#endif
#ifdef BIT_F238
	int ilen = 20;
#endif
	if(freqHz >= *(bitFreqList.param + bitFreqList.count - 1))
	{
		//20190102
		*startIndex = bitFreqList.count;
		return;
	}

	for(i = serStart; i < bitFreqList.count; i++)
	{
		if(freqHz <= *(bitFreqList.param + i))
		{
			if(0 == i)
			{
				*startIndex = 0;
				*stopIndex = 1;
				return;
			}
			else
			{
				*startIndex = i -1;
				if(islastpoint)
				{
					for(j = 0; j < ilen; j++)
					{
						if(freqHz == freqChannelList[j])
						{
							*startIndex = i + 1;
							break;
						}
					}
				}
				*stopIndex = *startIndex + 1;
				return;
			}
		}
	}
	return;
}

static int GetpreOffAttenIndex(double refLevel)
{
	int iSum = sizeof(ifGainOff) / sizeof(CHANNELGAIN);
	int i = 0;

	for(i = 0; i < iSum; i++)
	{
		if(refLevel >= ifGainOff[i].refLevel)
			return i;
	}
	//means the ref is very small,the if gain should set 60dB and atten set 0dB
	return -1;
}

static int GetpreOnAttenIndex(double refLevel)
{
	int iSum = sizeof(ifGainOn) / sizeof(CHANNELGAIN);
	int i = 0;
	for(i = 0; i < iSum; i++)
	{
		if(refLevel >= ifGainOn[i].refLevel)
			return i;
	}
	//means the ref is very small,the if gain should set 60dB and atten set 0dB
	return -1;
}

static int GetAttenIndexOff(double attendB)
{
	int iSum = sizeof(ifGainOff) / sizeof(CHANNELGAIN);
	int i = 0;
	for(i = 0; i < iSum; i++)
	{
		if(attendB >= ifGainOff[i].atten)
			return i;
	}
	return -1;
}

static int GetAttenIndexOn(double attendB)
{
	int iSum = sizeof(ifGainOn) / sizeof(CHANNELGAIN);
	int i = 0;
	for(i = 0; i < iSum; i++)
	{
		if(attendB >= ifGainOn[i].atten)
			return i;
	}
	return -1;
}

//============================================================================================
//SA_calc 2018/03/27
//============================================================================================
int itemsSum = 0;
int GetSourceCalcResultParam()
{
	FILE *fp;
	//open file
	fp = fopen("saclacconfig\\soureccalcresult.txt", "r");
	if (NULL == fp)
	{
		return -1;
	}

	// get file nums
	char flag;
	int filelen = 0;

	while (!feof(fp))
	{
		flag = fgetc(fp);
		if (flag == '\n')
			filelen++;
	}
	itemsSum = filelen;
	//back pointer
	rewind(fp);

	maplist = (PFREQAMPLIST)malloc(sizeof(FREQAMPLIST) * filelen);
	if (NULL == maplist)
		return -1;

	char str1[64];
	fscanf(fp, "%s  %s  %s", str1, str1, str1);
	int i = 0;
	for (i = 0; i < filelen; i++)
	{
		fscanf(fp, "%d%lf%lf", &((maplist + i)->index), &((maplist + i)->freqHz), &((maplist + i)->ampdB));
	}

	if (fp != NULL)
		fclose(fp);
	return 0;
}

static int CVICALLBACK CalcSaFuncEx(void *functionData);
int GoSaCalc(void* param)
{
	int istatus = 0;

#if Y
	OpenManager();
	OpenSource();
	OpenSa();
#endif

	//get freq points
	GetParamFromFile(path,&bitFreqList);

	//get param
	istatus = GetSourceCalcResultParam();
	if(istatus < 0)
		return istatus;

	return istatus = CmtScheduleThreadPoolFunctionAdv (
						 DEFAULT_THREAD_POOL_HANDLE, CalcSaFuncEx, NULL,
						 THREAD_PRIORITY_NORMAL, NULL, EVENT_TP_THREAD_FUNCTION_END, NULL, CmtGetCurrentThreadID(),
						 &threadSaID);
}

#define LOWDOOR 7.5e9
#define HIGHDOOR 23.63375e9
static void SyncCtrlWithCalc(double param);
//whole calc with if gain ctrl
static int CVICALLBACK CalcSaFunc(void *functionData)
{
	int iBack = 0;
	//all freq points from 50MHz to end
	int iNum = sizeof(powerlistpointsampoff) / sizeof(double);

	int iIndex = 0;

	BOOL lowcutroad = FALSE;
	BOOL highcutroad = FALSE;
	BOOL mircocutroad = FALSE;

	int i = 0,j = 0;
	double saveData = 0.0;
	//for(i = 0;i < iNum;i++)
	for(i = 0; i < 1; i++)
	{
		lowcutroad = FALSE;
		highcutroad = FALSE;
		mircocutroad = FALSE;

		//for(j = 0;j < bitFreqList.count;j++)
		for(j = 0; j < 10; j++)
		{
			SetSourceOutFreq(*(bitFreqList.param + j));
			SetSourOutputPower((maplist + i * bitFreqList.count + j)->ampdB);
			SyncCtrlWithCalc(*(bitFreqList.param + j));
		}
	}

	SetSourceOutFreq(freqpoint);
	SyncCtrlWithCalc(freqpoint);

	//IF ampilier set 40dB
	SetSourOutputPower((maplist + itemsSum - 4)->ampdB);
	SyncCtrlWithCalc(freqpoint);

	//IF ampilier set 50dB
	SetSourOutputPower((maplist + itemsSum - 3)->ampdB);
	SyncCtrlWithCalc(freqpoint);

	//IF ampilier set 60dB
	SetSourOutputPower((maplist + itemsSum - 2)->ampdB);
	SyncCtrlWithCalc(freqpoint);

	//=================================================ON
	//need changed,0411,UNDO
	iNum = sizeof(powerlistpoints) / sizeof(double);
	for(i = 0; i < iNum; i++)
	{
		lowcutroad = FALSE;
		highcutroad = FALSE;
		mircocutroad = FALSE;

		for(j = 0; j < bitFreqList.count; j++)
		{
			SetSourceOutFreq(*(bitFreqList.param + j));
			SetSourOutputPower((maplist + i * bitFreqList.count + j)->ampdB);
			SyncCtrlWithCalc(*(bitFreqList.param + j));
		}
	}

	//100MHz  calc IF ampliter
	SetSourceOutFreq(freqpoint);
	SyncCtrlWithCalc(freqpoint);

	//IF ampilier set 40dB
	SetSourOutputPower((maplist + itemsSum - 3)->ampdB);
	SyncCtrlWithCalc(freqpoint);

	//IF ampilier set 50dB
	SetSourOutputPower((maplist + itemsSum - 2)->ampdB);
	SyncCtrlWithCalc(freqpoint);

	//IF ampilier set 60dB
	SetSourOutputPower((maplist + itemsSum - 1)->ampdB);
	SyncCtrlWithCalc(freqpoint);

	viClose(saHandle);
	viClose(sourHandle);
	viClose(manaHandle);
	return 0;
}

static void SyncCtrlWithCalc(double param)
{
	int itrueNum = 0;
	int iBack = 0;
	memset(commandBuffer,0,BUFFERSIZE);
	sprintf(commandBuffer,"%lf\n",param);
	iBack = viWrite(saHandle,commandBuffer,strlen(commandBuffer),&itrueNum);
	if(VI_SUCCESS != iBack)
		MessagePopup("error","write commu failed");
	memset(commandBuffer,0,BUFFERSIZE);
	iBack = viRead(saHandle,commandBuffer,BUFFERSIZE,&itrueNum);
	if(VI_SUCCESS < 0)
		MessagePopup("error","read commu failed");
	return;
}

static int CVICALLBACK CalcSaFuncEx(void *functionData)
{
	//open the file
	FILE *fp;
	//open file
	fp = fopen("saclacconfig\\sacalcresult.txt", "w");
	if (NULL == fp)
	{
		return -1;
	}
	fprintf(fp,"No.       freqHz          detadB\n");

	//all freq points from 50MHz to end
	int iNum = sizeof(powerlistpointsampoff) / sizeof(double);

	int iIndex = 0;
	int i = 0,j = 0;
	double saveData = 0.0;

	PreAmpliChannelCtrl(0,0);

	//1030
	double tempAtten = 0.0;
	for(i = 0; i < iNum; i++)
	{
		//1030
		if(i == 0)
		{
			//20190102
			tempAtten = powerlistpointsampoff[i] + 24;
			//tempAtten = powerlistpointsampoff[i];
		}
		else
		{
			tempAtten = powerlistpointsampoff[i] + 20;
		}
#if Y
		PreAttenCtrl(0,tempAtten);
#endif
		for(j = 0; j < bitFreqList.count; j++)
		{
#if Y
			RfChannelChoose(0,*(bitFreqList.param + j));
			SetSourceOutFreq(*(bitFreqList.param + j));
			SetSourOutputPower((maplist + i * bitFreqList.count + j)->ampdB);
#endif
			//set acq states and call acq func

			//log convert

			//get maxvalue

			//save deta calc datas
			saveData = Random(123.0,321.0);
			saveData -= powerlistpointsampoff[i];
			fprintf(fp,"%d         %.1lf         %.2lf\n",iIndex++,*(bitFreqList.param + j),saveData);
		}
	}

	iNum = sizeof(powerlistpointsampon) / sizeof(double);

	//when preamp is on,the source out power start from -5dBm
	int nstartIndex = 3 * bitFreqList.count;

	for(i = 0; i < iNum; i++)
	{
#if Y
		PreAmpliChannelCtrl(0,1);
		PreAttenCtrl(0,powerlistpointsampon[i] + 35);
#endif
		for(j = 0; j < bitFreqList.count; j++)
		{
#if Y
			RfChannelChoose(0,*(bitFreqList.param + j));
			SetSourceOutFreq(*(bitFreqList.param + j));
			SetSourOutputPower((maplist + nstartIndex + i * bitFreqList.count + j)->ampdB);
#endif
			//set acq states and call acq func

			//log convert

			//get maxvalue

			//save deta calc datas
			saveData = Random(333.0,353.0);
			saveData -= powerlistpointsampon[i];
			fprintf(fp,"%d         %.1lf         %.2lf\n",iIndex++,*(bitFreqList.param + j),saveData);
		}
	}

	fclose(fp);
	return 0;
}

//this part is for sa whole machine calc who do 50~35dB atten
static int CVICALLBACK CalcSaFuncEx0(void *functionData)
{
	//open the file
	FILE *fp;
	//open file
	fp = fopen("saclacconfig\\sacalcresult.txt", "w");
	if (NULL == fp)
	{
		return -1;
	}
	fprintf(fp,"No.       freqHz          detadB\n");

	//all freq points from 50MHz to end
	int iNum = sizeof(powerlistpointsampoff) / sizeof(double);

	int iIndex = 0;
	int i = 0,j = 0;
	double saveData = 0.0;

	PreAmpliChannelCtrl(0,0);

	//1030
	double tempAtten = 0.0;
	for(i = 0; i < iNum; i++)
	{
		//1030
		if(i <= 3)
		{
			//20190102
			tempAtten = powerlistpointsampoff[i] + 40 - i * 5;
			//tempAtten = powerlistpointsampoff[i];
		}
		else
		{
			tempAtten = powerlistpointsampoff[i] + 20;
		}
#if Y
		PreAttenCtrl(0,tempAtten);
#endif
		for(j = 0; j < bitFreqList.count; j++)
		{
#if Y
			RfChannelChoose(0,*(bitFreqList.param + j));
			SetSourceOutFreq(*(bitFreqList.param + j));
			SetSourOutputPower((maplist + i * bitFreqList.count + j)->ampdB);
#endif
			//set acq states and call acq func

			//log convert

			//get maxvalue

			//save deta calc datas
			saveData = Random(123.0,321.0);
			saveData -= powerlistpointsampoff[i];
			fprintf(fp,"%d         %.1lf         %.2lf\n",iIndex++,*(bitFreqList.param + j),saveData);
		}
	}

	iNum = sizeof(powerlistpointsampon) / sizeof(double);

	//when preamp is on,the source out power start from -5dBm
	int nstartIndex = 3 * bitFreqList.count;

	for(i = 0; i < iNum; i++)
	{
#if Y
		PreAmpliChannelCtrl(0,1);
		PreAttenCtrl(0,powerlistpointsampon[i] + 35);
#endif
		for(j = 0; j < bitFreqList.count; j++)
		{
#if Y
			RfChannelChoose(0,*(bitFreqList.param + j));
			SetSourceOutFreq(*(bitFreqList.param + j));
			SetSourOutputPower((maplist + nstartIndex + i * bitFreqList.count + j)->ampdB);
#endif
			//set acq states and call acq func

			//log convert

			//get maxvalue

			//save deta calc datas
			saveData = Random(333.0,353.0);
			saveData -= powerlistpointsampon[i];
			fprintf(fp,"%d         %.1lf         %.2lf\n",iIndex++,*(bitFreqList.param + j),saveData);
		}
	}

	fclose(fp);
	return 0;
}
//over 2018/04/16

static void GetLog(double* buffer,int isize)
{
	int i = 0;
	for(i = 0; i < isize; i++)
	{
		*(buffer + i) = 20 * log10(*(buffer + i) + PER);
	}
	return;
}

double GetMaxValue(double* buffer,int isize)
{
	int i = 0;
	double temp = buffer[0];
	for(i = 0; i < isize; i++)
	{
		if(*(buffer + i) > temp)
			temp = *(buffer + i);
	}
	return temp;
}




