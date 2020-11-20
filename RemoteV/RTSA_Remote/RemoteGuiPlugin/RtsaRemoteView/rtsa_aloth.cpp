#include "rtsa_aloth.h"
#include "rtsa_user_variable.h"
#include "rtsa_shared_memory.h"
#include <math.h>
#include <QDebug>

//extern PRTSA_SWEEP_NUM sm_rtsa_sweep_num;
extern _CONFIG_RSA_CTRL *sm_rtsa_config_rsa_ctrl;

//added by Steve,0227
double ESP = 1.0e-3;
double freqChannelList[] = {9000.0,1366250000.0,2600000000.0,7500000000.0,9500000000.0,
                12300000000.0,15700000000.0,16300000000.0,19500000000.0,
                23633750000.0,26500000000.0,27833750000.0,29500000000.0,32000000000.0};

//RTSA_CHANNEL_PARAM  chparamlist[] = {
//  //rbwHz fsHz  stepHz						 Nfs
//  {3000, 45000, 33750, 32,   2.133, 0.0, 0.75, 32000, 1.0/45, 47},
//  {1000, 45000, 33750, 128,  2.844, 0.0, 0.75, 128000, 1.0/45, 47},
//  {300,  45000, 33750, 256,  1.707, 0.0, 0.75, 256000, 1.0/45, 47},
//  {100,  45000, 33750, 1024, 2.275, 0.0, 0.75, 1024000, 1.0/45, 47},
//  {30,   4500,  3375,  256,  1.707, 0.0, 0.75, 2560000, 1.0/4.5, 47},
//  {10,   4500,  3375,  1024, 2.275, 0.0, 0.75, 10240000, 1.0/4.5, 47},
//  {3,    4500,  3375,  4096, 2.731, 0.0, 0.75, 40960000, 1.0/4.5, 47},
//  {1,    2250,  1800,  8192, 3.641, 0.0, 0.8,  1638400000, 1.0/2.25, 47}};//FFT mode

double rbwList[] = {5.0e6,3.0e6,1.0e6,3.0e5,1.0e5,3.0e4,1.0e4,3000,1000,300,100,30, 10, 3, 1};
double dealTimeList[] = {1000.0  ,1000.0  ,1000.0  ,1000.0  ,1000.0  ,1000.0  ,1000.0  ,1000.0 ,1000.0 ,1000.0,1000.0,1000.0,1000.0,1000.0,1000.0};//last part spend time
double rbwtospan = 0.01;//span to rbw,when small down 1
int rbwTrigDoor = 0;//set rbw when 0 ifself,1 function call
int REF_CLOCK = 90000000;//ref clock
double vbwtorbw = 1.0;//vbw to rbw
double firStep = 0.2;//FIR lo step
double fstimens = 1000. / 45;//acq time

enum anaMode {FIR_MODE = 0,FFT_MODE = 3};

RTSA_LO_FREQ_DIV lodivList[] =
{
  {2.0,4.0,4.0,3633750000.0},//9k~1.36625G
  {2.0,2.0,4.0,3633750000.0},//1.36625~2.6G
  {2.0,1.0,4.0,9866250000.0},//2.6~7.5G
  {2.0,1.0,4.0,3633750000.0},//7.5~9.5G
  {2.0,1.0,4.0,3633750000.0},//9.5~12.3G
  {2.0,1.0,4.0,3633750000.0},//12.3~15.7G
  {2.0,1.0,4.0,3633750000.0},//15.7~16.3G
  {2.0,1.0,4.0,-3633750000.0},//16.3~19.5G
  {2.0,1.0,4.0,-3633750000.0},//19.5~23.63375G
  {2.0,0.5,4.0,-3633750000.0},//23.63375~26.5G
  {2.0,0.5,4.0,-3633750000.0},//26.5~27.83375G
  {2.0,0.5,4.0,-3633750000.0},//27.83375~29.5G
  {2.0,0.5,4.0,-3633750000.0}//29.5~32G
};

//0424
double firfskHzlist[] = {1.0/11250.0,1.0/11250.0,1.0/5625.0,1.0/1125.0,1.0/375.0,1.0/112.5,1.0/37.5,1/11.25,1/3.75,1/1.125,1/0.375,1/0.1125,1/0.0375,1/0.01125,1/0.00375};//rbw from 5000kHz to 1 Hz

//0711
unsigned int firfliterOrder[] = {11,11,19,19,19,35,35,35,35,35,35,35,35,35,35};//rbw from 5M to 10kHz
double interRuptCommutimems = 0.8;

const double sweepTrigCircle = 1.5;//us

//0428,lo keep time and suoxiang bujing time
//change only suoxiang bujing time from 4 to 2,0503
double loStepandStaytime = 0.0;//

//by steve start on 07/10 to achieve sweep time ctrl
RtSa_Aloth::RtSa_Aloth(QObject *parent/* = 0*/)
{

}
RtSa_Aloth::~RtSa_Aloth()
{
}
void RtSa_Aloth::setGobalVariable(RtSa_User_Variable *globalVariable)
{
    globalUserVariable = globalVariable;
}
int RtSa_Aloth::GetFreqChannelIndex(double freqHz)
{
  if(freqHz < freqChannelList[0] + ESP)
    return 1;
  int iLen = sizeof(freqChannelList) / sizeof(double);

  int i = 1;
  for(i = 1;i < iLen;i++)
    {
      if(freqHz < freqChannelList[i] + ESP)
        return i;
    }
  return iLen - 1;
}

void RtSa_Aloth::GetSegmentWaveIndex(void* param)
{
  //get the freq segment num
  int iIndex = GetFreqChannelIndex(globalUserVariable->gCenterFreq);
  //back
  if(freqChannelList[iIndex] <= globalUserVariable->gStartFreq + ESP)
    {
      iIndex++;
    }
//  int istopIndex = GetFreqChannelIndex(globalUserVariable->gStopFreq);

  sm_rtsa_config_rsa_ctrl->channelnum = iIndex;
//  sm_rtsa_sweep_num->segmentNum = istopIndex - istartIndex + 1;
//  unsigned int i = 0;
//  for(i = 0; i < sm_rtsa_sweep_num->segmentNum; i++)
//    {
//      //start from zero index,cor with wave index and data nums
//      sm_rtsa_sweep_num->comNum[i].segmentIndex = istartIndex + i;
//    }
  return;
}

int RtSa_Aloth::ConfigureFrequencyStartStop (double startFrequency,double stopFrequency)
{
  //0713 clear
  globalUserVariable->gautoMintimems = 0.0;

  //get segment index   sm_rtsa_config_rsa_ctrl->sweepMode
  GetSegmentWaveIndex(0);

  //0713
  globalUserVariable->gautoMintimems += /*sm_rtsa_sweep_num->segmentNum **/ interRuptCommutimems;

  //associate with rbw
  if(globalUserVariable->gAutoRbw)
    {
      //calc rbw through the span,0.01
      int tempIndexcalc = GetrbwIndex(globalUserVariable->gSpanFreq * rbwtospan);
      int tempIndexnow = GetrbwIndex((double)globalUserVariable->gRbw);
      //by Steve,0302
      globalUserVariable->grbwChangedbyFreq = 0;
      if(tempIndexnow != tempIndexcalc)
        {
          rbwTrigDoor = 1;
          globalUserVariable->grbwChangedbyFreq = 1;
//          ConfigureSweepCoupling(globalUserVariable->gAutoRbw,rbwList[tempIndexcalc],globalUserVariable->gAutoVbw,globalUserVariable->gVbw,globalUserVariable->gAutoVbwtoRbw,globalUserVariable->gVbwtoRbw);
          rbwTrigDoor = !rbwTrigDoor;
        }
    }
  else
    {
      //by Steve,0309
      //recover lostep by now  rbw when fir mode

    }
  //calculate params by sweet mode
  RefCalSweepParams(0);
  return 0;
}

//0716 this interface only used in fir mode,in man sweep time mode
VARIABLE_IS_NOT_USED static int gsweepflag = 0;//when 1 means not itself call
//void RtSa_Aloth::SettingSweepTimeManmode(double sweeptimems,double autotimems)
//{
////  int iflag = 0;
////  if(sweeptimems <= autotimems)
////    {
////      iflag = 1;
////      sweeptimems = autotimems;
////    }
////  //firstly calc persegment points num and sum points num
////  //if(sweeptimems > autotimems)
////    {
////      sm_rtsa_sweep_num->segmentsDataSumNum = 0;
////      int iextranum = 1;
////      unsigned int i = 0;
////      int iSize = sm_rtsa_sweep_num->segmentNum - 1;
////      //means call setting sweep time direct
////      if(!gsweepflag)
////        {
////          //recover loStepHz
////          sm_rtsa_sweep_num->loStepHz = globalUserVariable->gRbw * firStep;
////        }
////      double dStep = sm_rtsa_sweep_num->loStepHz;

////      if(sm_rtsa_sweep_num->segmentNum > 1)
////        {
////          double dfreqspan = freqChannelList[sm_rtsa_sweep_num->comNum[0].segmentIndex] - globalUserVariable->gStartFreq;
////          //first seg points num
////          sm_rtsa_sweep_num->comNum[0].segmentDataNum = (unsigned int)(dfreqspan / dStep) + iextranum;
////          sm_rtsa_sweep_num->segmentsDataSumNum += sm_rtsa_sweep_num->comNum[0].segmentDataNum;
////          for(i = 1; i < sm_rtsa_sweep_num->segmentNum - 1; i++)
////            {
////              dfreqspan = freqChannelList[sm_rtsa_sweep_num->comNum[i].segmentIndex] - freqChannelList[sm_rtsa_sweep_num->comNum[i - 1].segmentIndex];
////              sm_rtsa_sweep_num->comNum[i].segmentDataNum = (unsigned int)(dfreqspan / dStep) + iextranum;
////              sm_rtsa_sweep_num->segmentsDataSumNum += sm_rtsa_sweep_num->comNum[i].segmentDataNum;
////            }

////          dfreqspan = globalUserVariable->gStopFreq - freqChannelList[sm_rtsa_sweep_num->comNum[iSize].segmentIndex - 1];

////          sm_rtsa_sweep_num->comNum[iSize].segmentDataNum = (unsigned int)(dfreqspan / dStep) + iextranum;
////          sm_rtsa_sweep_num->segmentsDataSumNum += sm_rtsa_sweep_num->comNum[iSize].segmentDataNum;
////        }
////      //only one segment
////      else
////        {
////          //calc every segment points
////          sm_rtsa_sweep_num->comNum[0].segmentDataNum = (unsigned int)(globalUserVariable->gSpanFreq / dStep) + iextranum;
////          sm_rtsa_sweep_num->segmentsDataSumNum += sm_rtsa_sweep_num->comNum[0].segmentDataNum;
////        }

////      //sum sweep points num by sweeptimems
////      int inowsumnum = (sweeptimems - sm_rtsa_sweep_num->segmentNum * (0.002 + interRuptCommutimems)) / globalUserVariable -> gfirsingletimems;
////      if(1 == iflag)
////        {
////          sm_rtsa_sweep_num->loStepHz = globalUserVariable->gRbw * firStep;
////        }
////      else
////        {
////          sm_rtsa_sweep_num->loStepHz = (double)globalUserVariable->gSpanFreq / (inowsumnum - 1);
////        }
////      dStep = sm_rtsa_sweep_num->loStepHz;

////      if(sm_rtsa_sweep_num->segmentNum > 1)
////        {
////          sm_rtsa_sweep_num->comNum[0].segmentDataNum = (double)sm_rtsa_sweep_num->comNum[0].segmentDataNum / sm_rtsa_sweep_num->segmentsDataSumNum * inowsumnum + 0.5;
////          //calc the freq div value of every segment start freq
////          GetFreqDivValue(globalUserVariable->gStartFreq,&sm_rtsa_sweep_num->comNum[0].seglostartfreqinter,&sm_rtsa_sweep_num->comNum[0].seglostartfreqfrac);
////          GetStepFrqDivValue(globalUserVariable->gStartFreq,dStep,&sm_rtsa_sweep_num->comNum[0].seglosteplow,&sm_rtsa_sweep_num->comNum[0].seglostephigh);
////          sm_rtsa_sweep_num->comNum[0].persegsweeptimes = sm_rtsa_sweep_num->comNum[0].segmentDataNum * globalUserVariable -> gfirsingletimems + 0.002;
////          for(i = 1; i < sm_rtsa_sweep_num->segmentNum - 1; i++)
////            {
////              sm_rtsa_sweep_num->comNum[i].segmentDataNum = (double)sm_rtsa_sweep_num->comNum[i].segmentDataNum / sm_rtsa_sweep_num->segmentsDataSumNum * inowsumnum + 0.5;
////              GetFreqDivValue(freqChannelList[sm_rtsa_sweep_num->comNum[i].segmentIndex - 1],&sm_rtsa_sweep_num->comNum[i].seglostartfreqinter,&sm_rtsa_sweep_num->comNum[i].seglostartfreqfrac);
////              GetStepFrqDivValue(freqChannelList[sm_rtsa_sweep_num->comNum[i].segmentIndex - 1],dStep,&sm_rtsa_sweep_num->comNum[i].seglosteplow,&sm_rtsa_sweep_num->comNum[i].seglostephigh);
////              sm_rtsa_sweep_num->comNum[i].persegsweeptimes = sm_rtsa_sweep_num->comNum[i].segmentDataNum * globalUserVariable -> gfirsingletimems + 0.002;
////            }
////          sm_rtsa_sweep_num->comNum[iSize].segmentDataNum = (double)sm_rtsa_sweep_num->comNum[iSize].segmentDataNum / sm_rtsa_sweep_num->segmentsDataSumNum * inowsumnum + 0.5;
////          sm_rtsa_sweep_num->comNum[iSize].persegsweeptimes = sm_rtsa_sweep_num->comNum[iSize].segmentDataNum * globalUserVariable -> gfirsingletimems + 0.002;
////          GetFreqDivValue(freqChannelList[sm_rtsa_sweep_num->comNum[iSize].segmentIndex - 1],&sm_rtsa_sweep_num->comNum[iSize].seglostartfreqinter,&sm_rtsa_sweep_num->comNum[iSize].seglostartfreqfrac);
////          GetStepFrqDivValue(freqChannelList[sm_rtsa_sweep_num->comNum[iSize].segmentIndex - 1],dStep,&sm_rtsa_sweep_num->comNum[iSize].seglosteplow,&sm_rtsa_sweep_num->comNum[iSize].seglostephigh);
////        }
////      else
////        {
////          sm_rtsa_sweep_num->comNum[0].segmentDataNum = (double)sm_rtsa_sweep_num->comNum[0].segmentDataNum / sm_rtsa_sweep_num->segmentsDataSumNum * inowsumnum + 0.5;
////          GetFreqDivValue(freqChannelList[sm_rtsa_sweep_num->comNum[0].segmentIndex - 1],&sm_rtsa_sweep_num->comNum[0].seglostartfreqinter,&sm_rtsa_sweep_num->comNum[0].seglostartfreqfrac);
////          GetStepFrqDivValue(freqChannelList[sm_rtsa_sweep_num->comNum[0].segmentIndex - 1],dStep,&sm_rtsa_sweep_num->comNum[0].seglosteplow,&sm_rtsa_sweep_num->comNum[0].seglostephigh);
////        }
////      sm_rtsa_sweep_num->sumSweeptime = sweeptimems - sm_rtsa_sweep_num->segmentNum * interRuptCommutimems;

////      if(!gsweepflag)
////        {
////          sm_rtsa_sweep_num->firBucketimeus = sm_rtsa_sweep_num->sumSweeptime / globalUserVariable->gTracePoint;
////        }
////    }
//  return;
//}

//double RtSa_Aloth::GetZeroSpanRbwMinms(unsigned int tracenums)
//{
//  double temp  = *(firfskHzlist + GetrbwIndex((double)globalUserVariable->gRbw));
//  temp = temp < 0.0001 ? 0.0001 : temp;
//  return temp * tracenums;
//}

//void RtSa_Aloth::GetZeroShmTimes(double timems,unsigned int tracenum)
//{
////  sm_rtsa_sweep_num->sumSweeptime = timems;
////  sm_rtsa_sweep_num->firBucketimeus = sm_rtsa_sweep_num->sumSweeptime / tracenum;
//  return;
//}

//0713 main calc sweep time   RtSa_User_Variable->gsweepAuto = 1;
void RtSa_Aloth::RefCalSweepParams(int sweepMode)
{
//  double dStep = 0.0;
//  double dSteptime = 0.0;
//  //u_int64_t dSteptime = 0;
//  int ifftRbwIndex = 0;

//  //added by steve 0418,extra one point needed only by fir
//  double iextranum = 0;
//  //clear sum time
//  sm_rtsa_sweep_num->sumSweeptime = 0;
//  sm_rtsa_sweep_num->segmentsDataSumNum = 0;

//  //steve,0504
//  double temppersegtime = 0.;

//  //0725
//  double tempsingsweeptime = 0.0;
//  unsigned int onetomulti = 0.0;

//  //0716
//  //FIR lo step freq
//  if(FIR_MODE == sweepMode)
//    {
//      iextranum = 1.;
//      //added by Steve,0309
//      //if sum sweep num smaller than trace points,adjust the lo step
//      //repair bug by steve 0418
//      int iNum = (unsigned int)(globalUserVariable->gSpanFreq / sm_rtsa_sweep_num->loStepHz + iextranum);
//      if(iNum <  globalUserVariable->gSweepTracePoint)
//        {
//          sm_rtsa_sweep_num->loStepHz = (double)globalUserVariable->gSpanFreq  / (globalUserVariable->gSweepTracePoint - 1);
//        }
//      dStep = sm_rtsa_sweep_num->loStepHz;
//      dSteptime = 0.002;//normal to ms

//      //calc single point time 0716
//      int iFirRbwIndex = 0;
//      iFirRbwIndex = GetrbwIndex((double)globalUserVariable->gRbw);
//      globalUserVariable -> gfirsingletimems =firfskHzlist[iFirRbwIndex] * (firfliterOrder[iFirRbwIndex] + 4 + 1);
//      globalUserVariable -> gfirsingletimems = globalUserVariable -> gfirsingletimems < 0.002 ? 0.002 : globalUserVariable -> gfirsingletimems;
//      sm_rtsa_sweep_num->firdottimems = globalUserVariable -> gfirsingletimems;
//      tempsingsweeptime = sm_rtsa_sweep_num->firdottimems;
//      onetomulti = 1;
//    }
//  else if(FFT_MODE == sweepMode)
//    {
//      //0725 steve
//      iextranum = 0.5;
//      //lo stdoubleep cor points
//      dStep = sm_rtsa_sweep_num->loStepHz;
//      ifftRbwIndex = GetFftRbwIndex();
//      dSteptime = 0.002;
//      sm_rtsa_sweep_num->singlefftTime = (chparamlist[ifftRbwIndex].fftNum + chparamlist[ifftRbwIndex].orderNum + 4) * chparamlist[ifftRbwIndex].tsms;
//      //set single fft time
//      tempsingsweeptime = sm_rtsa_sweep_num->singlefftTime;
//      onetomulti = sm_rtsa_sweep_num->fftNum;
//    }

//  //calc every seg sweep time and sum sweep time and segment points num
//  int temcriflg = 0;
//  //0726
//  int msumfftsweepoints = 0;
//  if(sm_rtsa_sweep_num->segmentNum > 1)
//    {
//      int iSize = sm_rtsa_sweep_num->segmentNum - 1;
//      double dfreqspan = freqChannelList[sm_rtsa_sweep_num->comNum[0].segmentIndex] - globalUserVariable->gStartFreq;
//      //first seg points num
//      sm_rtsa_sweep_num->comNum[0].segmentDataNum = (unsigned int)(dfreqspan / dStep + iextranum);
//      msumfftsweepoints += sm_rtsa_sweep_num->comNum[0].segmentDataNum;
//      //first seg time
//      //0504
//      temppersegtime = sm_rtsa_sweep_num->comNum[0].segmentDataNum * tempsingsweeptime + dSteptime;
//      sm_rtsa_sweep_num->comNum[0].persegsweeptimes = temppersegtime;

//      //by Steve,0424
//      //0725 if fft mode differ to fir mode
//      sm_rtsa_sweep_num->segmentsDataSumNum += (sm_rtsa_sweep_num->comNum[0].segmentDataNum * onetomulti);

//      /*calc the freq div value of every segment start freq*/
//      temcriflg = 0;
//      GetFreqDivValue(globalUserVariable->gStartFreq,&sm_rtsa_sweep_num->comNum[0].seglostartfreqinter,&sm_rtsa_sweep_num->comNum[0].seglostartfreqfrac);

//      //by Steve,0328
//      GetStepFrqDivValue(globalUserVariable->gStartFreq,dStep,&sm_rtsa_sweep_num->comNum[0].seglosteplow,&sm_rtsa_sweep_num->comNum[0].seglostephigh);

//      unsigned int i = 0;
//      for(i = 1; i < sm_rtsa_sweep_num->segmentNum - 1; i++)
//        {
//          dfreqspan = freqChannelList[sm_rtsa_sweep_num->comNum[i].segmentIndex] - freqChannelList[sm_rtsa_sweep_num->comNum[i - 1].segmentIndex];
//          sm_rtsa_sweep_num->comNum[i].segmentDataNum = (unsigned int)(dfreqspan / dStep + iextranum);
//          msumfftsweepoints += sm_rtsa_sweep_num->comNum[i].segmentDataNum;
//          sm_rtsa_sweep_num->segmentsDataSumNum += (sm_rtsa_sweep_num->comNum[i].segmentDataNum * onetomulti);
//          temppersegtime = sm_rtsa_sweep_num->comNum[i].segmentDataNum * tempsingsweeptime + dSteptime;
//          sm_rtsa_sweep_num->comNum[i].persegsweeptimes = temppersegtime;
//          //by Steve,0309
//          GetFreqDivValue(freqChannelList[sm_rtsa_sweep_num->comNum[i].segmentIndex - 1],&sm_rtsa_sweep_num->comNum[i].seglostartfreqinter,&sm_rtsa_sweep_num->comNum[i].seglostartfreqfrac);
//          //by Steve,0328
//          GetStepFrqDivValue(freqChannelList[sm_rtsa_sweep_num->comNum[i].segmentIndex - 1],dStep,&sm_rtsa_sweep_num->comNum[i].seglosteplow,&sm_rtsa_sweep_num->comNum[i].seglostephigh);
//        }
//      dfreqspan = globalUserVariable->gStopFreq - freqChannelList[sm_rtsa_sweep_num->comNum[iSize].segmentIndex - 1];
//      //last segments numsdouble
//      sm_rtsa_sweep_num->comNum[iSize].segmentDataNum = (unsigned int)(dfreqspan / dStep + iextranum);
//      msumfftsweepoints += sm_rtsa_sweep_num->comNum[iSize].segmentDataNum;
//      sm_rtsa_sweep_num->segmentsDataSumNum += (sm_rtsa_sweep_num->comNum[iSize].segmentDataNum * onetomulti);
//      temppersegtime = sm_rtsa_sweep_num->comNum[iSize].segmentDataNum * tempsingsweeptime + dSteptime;
//      sm_rtsa_sweep_num->comNum[i].persegsweeptimes = temppersegtime;
//      GetFreqDivValue(freqChannelList[sm_rtsa_sweep_num->comNum[iSize].segmentIndex - 1],&sm_rtsa_sweep_num->comNum[iSize].seglostartfreqinter,&sm_rtsa_sweep_num->comNum[iSize].seglostartfreqfrac);
//      //by Steve,0328
//      GetStepFrqDivValue(freqChannelList[sm_rtsa_sweep_num->comNum[iSize].segmentIndex - 1],dStep,&sm_rtsa_sweep_num->comNum[iSize].seglosteplow,&sm_rtsa_sweep_num->comNum[iSize].seglostephigh);
//    }
//  //only one segment
//  else
//    {
//      /*calc every segment points*/
//      sm_rtsa_sweep_num->comNum[0].segmentDataNum = (unsigned int)(globalUserVariable->gSpanFreq / dStep + iextranum);
//      msumfftsweepoints += sm_rtsa_sweep_num->comNum[0].segmentDataNum;
//      sm_rtsa_sweep_num->segmentsDataSumNum += (sm_rtsa_sweep_num->comNum[0].segmentDataNum * onetomulti);
//      /*calc the freq div value of every segment start freq*/
//      GetFreqDivValue(globalUserVariable->gStartFreq,&sm_rtsa_sweep_num->comNum[0].seglostartfreqinter,&sm_rtsa_sweep_num->comNum[0].seglostartfreqfrac);
//      //by steve 0418
//      GetStepFrqDivValue(globalUserVariable->gStartFreq,dStep,&sm_rtsa_sweep_num->comNum[0].seglosteplow,&sm_rtsa_sweep_num->comNum[0].seglostephigh);
//      sm_rtsa_sweep_num->comNum[0].persegsweeptimes = sm_rtsa_sweep_num->comNum[0].segmentDataNum * tempsingsweeptime + dSteptime;
//    }

//  //0716  steve calc per and sum segments data nums
//  if(FIR_MODE == sweepMode)
//    {
//      sm_rtsa_sweep_num->sumSweeptime = sm_rtsa_sweep_num->segmentsDataSumNum  * tempsingsweeptime + sm_rtsa_sweep_num->segmentNum * 0.002;
//      globalUserVariable->gautoMintimems += sm_rtsa_sweep_num->sumSweeptime;

//      if(!globalUserVariable->gsweepAuto)
//        {
//          if(globalUserVariable -> gmanSettimems < globalUserVariable->gautoMintimems)
//            {
//              globalUserVariable -> gmanSettimems = globalUserVariable->gautoMintimems;
//              globalUserVariable->gSweepTime = globalUserVariable -> gmanSettimems;
//            }
//          else
//            {
//              globalUserVariable->gSweepTime = globalUserVariable -> gmanSettimems;
//              sm_rtsa_sweep_num->sumSweeptime = globalUserVariable -> gmanSettimems - sm_rtsa_sweep_num->segmentNum * interRuptCommutimems;
//            }
//          gsweepflag = 1;
//          SettingSweepTimeManmode(globalUserVariable -> gmanSettimems,globalUserVariable->gautoMintimems);
//          gsweepflag = 0;
//        }
//      else
//        {
//          globalUserVariable->gSweepTime = globalUserVariable->gautoMintimems;
//        }
//      sm_rtsa_sweep_num->firBucketimeus = sm_rtsa_sweep_num->sumSweeptime / globalUserVariable->gTracePoint;
//    }
//  else
//    {
//      sm_rtsa_sweep_num->sumSweeptime = msumfftsweepoints  * tempsingsweeptime + sm_rtsa_sweep_num->segmentNum * 0.002;
//      globalUserVariable->gautoMintimems += sm_rtsa_sweep_num->sumSweeptime;
//      globalUserVariable->gSweepTime = globalUserVariable->gautoMintimems;
//      sm_rtsa_sweep_num->fftBucketnum = 0.1 * 10 * sm_rtsa_sweep_num->segmentsDataSumNum / globalUserVariable->gTracePoint;
//    }
  return;
}

int RtSa_Aloth::GetrbwIndex(double rbwHz)
{
  //check param
  int iListLeng = sizeof(rbwList) / sizeof(double);
  iListLeng = iListLeng < 1 ? 1 : iListLeng;
  rbwHz = rbwHz > rbwList[0] ? rbwList[0] : rbwHz;
  rbwHz = rbwHz < rbwList[iListLeng - 1] ? rbwList[iListLeng - 1] : rbwHz;

  int iIndex = 0;
  for(iIndex = 0; iIndex < iListLeng; iIndex++)
    {
      if(*(rbwList + iIndex) <= rbwHz)
        return iIndex;
    }
  return iIndex - 1;
}

int RtSa_Aloth::GetFftRbwIndex()
{
//  int iNum = sizeof(chparamlist) / sizeof(RTSA_CHANNEL_PARAM);
//  int i = 0;
//  for(i = 0; i < iNum; i++)
//    {
//      if(globalUserVariable->gRbw >= (chparamlist+i)->rbwkHz)
//        return i;
//    }
//  return iNum - 1;
    return 0;
}

void RtSa_Aloth::GetFreqDivValue(double freqHz,unsigned int* intdiv,unsigned int* fracdiv)
{
  int iIndex = GetFreqChannelIndex(freqHz);

  //0522,steve
  if(freqChannelList[iIndex] <= freqHz + ESP  && freqChannelList[iIndex] >= freqHz - ESP)
    {
      iIndex = iIndex;
    }
  else
    {
      iIndex--;
    }

  //Steve,0309
  //iIndex = iIndex == 0 ? iIndex : iIndex - 1;
  double temp = (freqHz + lodivList[iIndex].iffreq) / REF_CLOCK * lodivList[iIndex].d * lodivList[iIndex].r / lodivList[iIndex].feedback;

  *intdiv = (unsigned int)temp;
  //Steve,0309
  u_int64_t tempfrac = (u_int64_t)ceil((temp - *intdiv) * 4 * (1 << 16) * (1 << 30));
  *fracdiv = (tempfrac & 0xffffffff);
  *intdiv <<= 16;
  *intdiv |= (tempfrac >> 32 & 0xffff);
  return;
}

/*criflg 1 means end freq and should belong to former seg
0 means start freq and should belong to later segment*/
void RtSa_Aloth::GetStepFrqDivValue(double startfreq,double stepHz,unsigned int* lowbits,unsigned int* highbits)
{
  int iIndex = GetFreqChannelIndex(startfreq);

  //0522,steve
  if(freqChannelList[iIndex] <= startfreq + ESP  && freqChannelList[iIndex] >= startfreq - ESP)
    {
      iIndex = iIndex;
    }
  else
    {
      iIndex--;
    }

  //iIndex = iIndex == 0 ? iIndex : iIndex - 1;
  double temp = stepHz / REF_CLOCK * lodivList[iIndex].d * lodivList[iIndex].r / lodivList[iIndex].feedback;
  u_int64_t tempfrac = (u_int64_t)(temp * (1 << 24) * (1 << 24));
  *lowbits = tempfrac & 0xffffffff;
  *highbits = (tempfrac >> 32) & 0xffff;
  return;
}

VARIABLE_IS_NOT_USED static int rbwFlag = 0;//1 state changed
//steve,0504
int autoChangerbwflag = 0;//1 change, 0 nochange
//steve,0703
int autoChangevbwflag = 0;//1 change, 0 nochange
int RtSa_Aloth::ConfigureSweepCoupling (unsigned int resolutionBandwidthAuto,double resolutionBandwidth,unsigned int videoBandwidthAuto,double videoBandwidth,unsigned int vbwtorbwAuto,double vbwtorbwValue)
{
//  resolutionBandwidthAuto = !!resolutionBandwidthAuto;
//  globalUserVariable->gAutoRbw = resolutionBandwidthAuto;
//  videoBandwidthAuto = !!videoBandwidthAuto;
//  globalUserVariable->gAutoVbw = videoBandwidthAuto;
//  vbwtorbwAuto = !!vbwtorbwAuto;
//  globalUserVariable->gAutoVbwtoRbw = vbwtorbwAuto;

//  rbwFlag = 0;
//  //adjust the couple param,when rbw is auto
//  if( globalUserVariable->gAutoRbw)
//    {
//      //get the rbw through the span
//      int spanrbwIndex = GetrbwIndex(globalUserVariable->gSpanFreq * rbwtospan);
//      int nowIndex = GetrbwIndex((double)globalUserVariable->gRbw);

//      //0504
//      autoChangerbwflag = 0;

//      if(nowIndex != spanrbwIndex)
//        {
//          //0504
//          autoChangerbwflag = 1;

//          rbwFlag = 1;
//          globalUserVariable->gRbw = (unsigned int)rbwList[spanrbwIndex];
//          GetLastPartTime(spanrbwIndex);
//          ParamConvertByRbw(spanrbwIndex);
//          //down rbw and vbw in the ctrlapp
//        }

//      //bug,Steve,0302
//      if(globalUserVariable->gAutoVbw)
//        {
//          if(globalUserVariable->gAutoVbwtoRbw)
//            {
//              globalUserVariable->gVbwtoRbw = vbwtorbw;
//            }
//          else
//            {
//              globalUserVariable->gVbwtoRbw = vbwtorbwValue;
//            }
//          int iIndex = GetrbwIndex(globalUserVariable->gRbw * globalUserVariable->gVbwtoRbw);
//          iIndex = iIndex == 0 ? 1 : iIndex;
//          int ilastIndex = GetrbwIndex(globalUserVariable->gVbw);
//          ilastIndex = ilastIndex == 0 ? : ilastIndex;
//          autoChangevbwflag = 0;
//          if(iIndex != ilastIndex)
//            {
//              autoChangevbwflag = 1;
//            }
//          globalUserVariable->gVbw = (unsigned int)((int)rbwList[iIndex] * globalUserVariable->gVbwtoRbw);
//        }
//      else
//        {
//          int vbwIndex = GetrbwIndex(videoBandwidth);
//          globalUserVariable->gVbw = (unsigned int)rbwList[vbwIndex];
//        }
//    }
//  //the rbw is man
//  else
//    {
//      rbwFlag = 1;
//      int rbwIndex = GetrbwIndex(resolutionBandwidth);
//      globalUserVariable->gRbw = (unsigned int)rbwList[rbwIndex];
//      GetLastPartTime(rbwIndex);
//      //vbw is not 5MHz
//      rbwIndex = rbwIndex == 0 ? 1 : rbwIndex;
//      //more used
//      if(globalUserVariable->gAutoVbw)
//        {
//          if(globalUserVariable->gVbwtoRbw)
//            {
//              globalUserVariable->gVbwtoRbw = vbwtorbw;
//            }
//          else
//            {
//              globalUserVariable->gVbwtoRbw = vbwtorbwValue;
//            }
//          int iIndex = GetrbwIndex(globalUserVariable->gRbw * globalUserVariable->gVbwtoRbw);
//          iIndex = iIndex == 0 ? 1 : iIndex;
//          int ilastIndex = GetrbwIndex(globalUserVariable->gVbw);
//          ilastIndex = ilastIndex == 0 ? : ilastIndex;
//          autoChangevbwflag = 0;
//          if(iIndex != ilastIndex)
//            {
//              autoChangevbwflag = 1;
//            }
//          globalUserVariable->gVbw = (unsigned int)((int)rbwList[rbwIndex] * globalUserVariable->gVbwtoRbw);
//        }
//      else
//        {
//          int vbwIndex = GetrbwIndex(videoBandwidth);
//          globalUserVariable->gVbw = (unsigned int)rbwList[vbwIndex];
//        }

//      ParamConvertByRbw(rbwIndex);
//    }

//  if(!rbwTrigDoor && rbwFlag)
//    {
//      //0713
//      globalUserVariable->gautoMintimems = 0.0;
//      //0713
//      globalUserVariable->gautoMintimems += sm_rtsa_sweep_num->segmentNum * interRuptCommutimems;

//      //recalc time
//      RefCalSweepParams(0);

//    }
  return 0;
}

void RtSa_Aloth::ParamConvertByRbw(int iIndex)
{
//  int tempIndex = 0;
//  //get the sweep mode of FIR
//  if(iIndex <= 6)
//    {


//      //calc lo step
//      sm_rtsa_sweep_num->loStepHz = globalUserVariable->gRbw * firStep;
//    }
//  else//FFT mode
//    {
//      tempIndex = GetFftRbwIndex();


//      //calc lo step
//      sm_rtsa_sweep_num->loStepHz = chparamlist[tempIndex].stepFreqHz;
//      //set fft valid num  //0725 steve
//      sm_rtsa_sweep_num->fftNum = chparamlist[tempIndex].fftNum * chparamlist[tempIndex].validRatio;
//      //set start and stop index
//      sm_rtsa_sweep_num->startIndex = sm_rtsa_sweep_num->fftNum * (1 - chparamlist[tempIndex].validRatio) * 0.5;
//      sm_rtsa_sweep_num->stopIndex = sm_rtsa_sweep_num->fftNum * (1 - chparamlist[tempIndex].validRatio * 0.5);
//    }
  return;
}

void RtSa_Aloth::GetLastPartTime(int iIndex)
{
//  sm_rtsa_sweep_num->seglokeeptime = (unsigned int)(dealTimeList[iIndex] / fstimens);
  return;
}
