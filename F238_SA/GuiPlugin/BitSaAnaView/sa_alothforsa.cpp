/****************************************Copyright (c)****************************************************
**
**                                     INNO Instrument(China) Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                sa_alothforsa.cpp
** Latest Version:           V1.0.0
** Created by:               Johnson
** Created date:             2018/12/05
** Descriptions:             the class which used to define the control algorithm
**
*********************************************************************************************************/

#include "sa_alothforsa.h"
#include "sa_shared_memory.h"
#include "sa_alothforsa_globalpara.h"

#include <math.h>
#include <QDebug>

//by steve start on 07/10 to achieve sweep time ctrl
alothforsa::alothforsa(user_variable &m_user_variable)
{
    globalUserVariable = &m_user_variable;
}
alothforsa::~alothforsa()
{
    //delete globalUserVariable;
}

/*****************inner interface***********/
qint32 alothforsa::GetFreqChannelIndex(qreal freqHz)
{
    if(freqHz < freqChannelList[0] + ESP) return 1;
    qint32 iLen = sizeof(freqChannelList) / sizeof(qreal);
    qint32 i = 1;
    for(i = 1;i < iLen;i++)
    {
        if(freqHz < freqChannelList[i] + ESP) return i;
    }
    return iLen - 1;
}

void alothforsa::GetSegmentWaveIndex(void* param)
{
  //get the freq segment num
  qint32 istartIndex = GetFreqChannelIndex(globalUserVariable->gStartFreq);
  //back
#ifdef SA_SEG_START_STOP_NEW
  qreal StartFreq = globalUserVariable->gStartFreq;
  if(StartFreq >= freqChannelList[istartIndex] - SA_SEG_START_STOP_EXTENSION)
  {
      istartIndex ++;
  }
#else
  if(freqChannelList[istartIndex] <= globalUserVariable->gStartFreq + ESP)
    {
      istartIndex++;
    }
#endif
  qint32 istopIndex = GetFreqChannelIndex(globalUserVariable->gStopFreq);
#ifdef SA_SEG_START_STOP_NEW
  qreal StopFreq = globalUserVariable->gStopFreq;
  if(StopFreq <= freqChannelList[istopIndex - 1] - SA_SEG_START_STOP_EXTENSION)
  {
      istopIndex --;
  }
#endif
  qint32 ioverflag = 0;
  if(istartIndex > istopIndex)
    {
      ioverflag = 1;
      istartIndex = istopIndex;
    }
#ifdef SA_SEG_CHANGE_NEW
  if(globalUserVariable->gSpanFreq > SA_SEG_CHANGE_MINSPAN)
  {
      SA_sm_sweep_num->segmentNum = istopIndex - istartIndex + 1;
  }
  else
  {
      SA_sm_sweep_num->segmentNum = 1;
  }
#else
  SA_sm_sweep_num->segmentNum = istopIndex - istartIndex + 1;
#endif
  if(1 == SA_sm_sweep_num->segmentNum && ioverflag)
    {
      SA_sm_sweep_num->comNum[0].segmentIndex = istartIndex;
    }
  else
    {
      quint32 i = 0;
      for(i = 0; i < SA_sm_sweep_num->segmentNum; i++)
        {
          //start from zero index,cor with wave index and data nums
          SA_sm_sweep_num->comNum[i].segmentIndex = istartIndex + i;
        }
    }
  return;
}

//0713 main calc sweep time   user_variable->gsweepAuto = 1;
void alothforsa::RefCalSweepParams(qint32 sweepMode)
{
  qreal dStep = 0.0;
  qreal dSteptime = 0.0;
  qint32 ifftRbwIndex = 0;

  //added by steve 0418,extra one point needed only by fir
  SA_sm_sweep_num->sumSweeptime = 0;
  SA_sm_sweep_num->segmentsDataSumNum = 0;
  //steve,0504
  qreal temppersegtime = 0.;
  //0725
  qreal tempsingsweeptime = 0.0;
  qint32 onetomulti = 0;
  //0716
  //FIR lo step freq

  //0903
  qreal dspantostep = 0.0;
  if(FIR_MODE == sweepMode)
  {
      //iextranum = 1.;
      //added by Steve,0309
      //if sum sweep num smaller than trace points,adjust the lo step
      //repair bug by steve 0418

      SA_sm_sweep_num->loStepHz = globalUserVariable->gRbw*firStep;//Johnson 191107

      qint32 iNum = (quint32)(ceil(globalUserVariable->gSpanFreq / SA_sm_sweep_num->loStepHz));
      if(iNum <  globalUserVariable->gSweepTracePoint)
      {
          SA_sm_sweep_num->loStepHz = (qreal)globalUserVariable->gSpanFreq  / (globalUserVariable->gSweepTracePoint - 1);
      }
      dStep = SA_sm_sweep_num->loStepHz;
      dSteptime = 0.002;//normal to ms

#if DOTTIME_200409
        qreal sweeptime = 0.0;
        quint32 totalSegmentDataNum = 0;
        if(globalUserVariable->gRbw < globalUserVariable->gVbw)
        {
          sweeptime = SWEEP_K * globalUserVariable->gSpanFreq / ((qreal)globalUserVariable->gRbw * (qreal)globalUserVariable->gRbw) * 1000;
        }
        else
        {
          sweeptime = SWEEP_K * globalUserVariable->gSpanFreq / ((qreal)globalUserVariable->gRbw * (qreal)globalUserVariable->gVbw) * 1000;
        }
        totalSegmentDataNum = globalUserVariable->gSpanFreq / dStep;
        globalUserVariable->gfirsingletimems = sweeptime / totalSegmentDataNum;
#endif

      //calc fir single point time 0716
      if(globalUserVariable->gAutoDotSweepTime == SA_AUTO)
      {
          qint32 iFirRbwIndex = 0;
          iFirRbwIndex = GetrbwIndex((qreal)globalUserVariable->gRbw);
          if(globalUserVariable->gFixDotSweepTime == SA_ON)
          {
              if(globalUserVariable->gVbw > 3000)//vbw>3kHz
                  globalUserVariable->gfirsingletimems = autoSetDotSweepTime[iFirRbwIndex];
#if !DOTTIME_200409
              else
                  globalUserVariable->gfirsingletimems = firfskHzlist[iFirRbwIndex] * (firfliterOrder[iFirRbwIndex]);
#endif
          }
#if !DOTTIME_200409
          else
          {
              globalUserVariable->gfirsingletimems = firfskHzlist[iFirRbwIndex] * (firfliterOrder[iFirRbwIndex]);//+ 4 + 1);
          }
#endif
          globalUserVariable -> gfirsingletimems = globalUserVariable -> gfirsingletimems < 0.002 ? 0.002 : globalUserVariable -> gfirsingletimems;

          SA_sm_sweep_num->firdottimems = globalUserVariable -> gfirsingletimems;
          globalUserVariable->gDotSweepTime = SA_sm_sweep_num->firdottimems;
      }
      else
      {
          SA_sm_sweep_num->firdottimems = globalUserVariable->gDotSweepTime;
          globalUserVariable -> gfirsingletimems = globalUserVariable->gDotSweepTime;
      }
      tempsingsweeptime = SA_sm_sweep_num->firdottimems;
      onetomulti = 1;
  }
  else if(FFT_MODE == sweepMode)
  {
      //0725 steve
      //iextranum = 0.5;
      //lo stdoubleep cor points
      dStep = SA_sm_sweep_num->loStepHz;
      //0903
      dspantostep = globalUserVariable->gSpanFreq / dStep;
      ifftRbwIndex = GetFftRbwIndex();
      dSteptime = 0.002;
      //SA_sm_sweep_num->singlefftTime = (chparamlist[ifftRbwIndex].fftNum + chparamlist[ifftRbwIndex].orderNum + 4) * chparamlist[ifftRbwIndex].tsms;
      if(globalUserVariable->gAutoDotSweepTime == SA_AUTO)
      {
          SA_sm_sweep_num->singlefftTime = (chparamlist[ifftRbwIndex].fftNum + chparamlist[ifftRbwIndex].orderNum) * chparamlist[ifftRbwIndex].tsms + dSteptime;//Johnson 190529
          //qint32 offset = (char *)(&SA_sm_sweep_num->singlefftTime) - (char *)SA_sm_sweep_num;//variable "singlefftTime" offset relative to starting address
          globalUserVariable->gDotSweepTime = SA_sm_sweep_num->singlefftTime;
      }
      else
      {
          SA_sm_sweep_num->singlefftTime = globalUserVariable->gDotSweepTime;
      }
      //set single fft time
      tempsingsweeptime = SA_sm_sweep_num->singlefftTime;
      onetomulti = SA_sm_sweep_num->fftNum;
  }

  //calc every seg sweep time and sum sweep time and segment points num
  //qint32 temcriflg = 0;
  //0726
  qint32 msumfftsweepoints = 0;

  //0828
  qreal daddedfreq = 0.;
  if(SA_sm_sweep_num->segmentNum > 1)
  {
      qint32 iSize = SA_sm_sweep_num->segmentNum - 1;
      qreal dfreqspan = freqChannelList[SA_sm_sweep_num->comNum[0].segmentIndex] - globalUserVariable->gStartFreq;
      //first seg points num
      SA_sm_sweep_num->comNum[0].segmentDataNum = (quint32)(ceil(dfreqspan / dStep));
      SA_sm_sweep_num->comNum[0].segmentDataNum = SA_sm_sweep_num->comNum[0].segmentDataNum == 0 ? 1 : SA_sm_sweep_num->comNum[0].segmentDataNum;

      //0828,this happen only when fft mode
      if(FIR_MODE == sweepMode) daddedfreq = 0.;
      else
      {
          daddedfreq = dStep * 0.5;
          if(SA_sm_sweep_num->comNum[0].segmentDataNum <= 1)
          {
              SA_sm_sweep_num->comNum[0].segmentDataNum = 1;
              //daddedfreq = dfreqspan * 0.5;
          }
      }

      msumfftsweepoints += SA_sm_sweep_num->comNum[0].segmentDataNum;
      //first seg time
      //0504
      temppersegtime = SA_sm_sweep_num->comNum[0].segmentDataNum * tempsingsweeptime + dSteptime;
      SA_sm_sweep_num->comNum[0].persegsweeptimes = temppersegtime;
      //by Steve,0424
      //0725 if fft mode differ to fir mode
      SA_sm_sweep_num->segmentsDataSumNum += (SA_sm_sweep_num->comNum[0].segmentDataNum * onetomulti);
      /*calc the freq div value of every segment start freq*/
      //temcriflg = 0;
      GetFreqDivValue(globalUserVariable->gStartFreq,daddedfreq,&SA_sm_sweep_num->comNum[0].seglostartfreqinter,&SA_sm_sweep_num->comNum[0].seglostartfreqfrac);
      //by Steve,0328
      GetStepFrqDivValue(globalUserVariable->gStartFreq,dStep,&SA_sm_sweep_num->comNum[0].seglosteplow,&SA_sm_sweep_num->comNum[0].seglostephigh);

      quint32 i = 0;
      for(i = 1; i < SA_sm_sweep_num->segmentNum - 1; i++)
      {
          dfreqspan = freqChannelList[SA_sm_sweep_num->comNum[i].segmentIndex] - freqChannelList[SA_sm_sweep_num->comNum[i - 1].segmentIndex];
          SA_sm_sweep_num->comNum[i].segmentDataNum = (quint32)(ceil(dfreqspan / dStep));
          SA_sm_sweep_num->comNum[i].segmentDataNum = SA_sm_sweep_num->comNum[i].segmentDataNum == 0 ? 1 : SA_sm_sweep_num->comNum[i].segmentDataNum;
          msumfftsweepoints += SA_sm_sweep_num->comNum[i].segmentDataNum;
          SA_sm_sweep_num->segmentsDataSumNum += (SA_sm_sweep_num->comNum[i].segmentDataNum * onetomulti);
          temppersegtime = SA_sm_sweep_num->comNum[i].segmentDataNum * tempsingsweeptime + dSteptime;
          SA_sm_sweep_num->comNum[i].persegsweeptimes = temppersegtime;

          if(FIR_MODE == sweepMode)
          {
              daddedfreq = 0.;
          }
          else
          {
              daddedfreq = dStep * 0.5;
          }
          //by Steve,0309
          GetFreqDivValue(freqChannelList[SA_sm_sweep_num->comNum[i].segmentIndex - 1],daddedfreq,&SA_sm_sweep_num->comNum[i].seglostartfreqinter,&SA_sm_sweep_num->comNum[i].seglostartfreqfrac);
          //by Steve,0328
          GetStepFrqDivValue(freqChannelList[SA_sm_sweep_num->comNum[i].segmentIndex - 1],dStep,&SA_sm_sweep_num->comNum[i].seglosteplow,&SA_sm_sweep_num->comNum[i].seglostephigh);
      }
      dfreqspan = globalUserVariable->gStopFreq - freqChannelList[SA_sm_sweep_num->comNum[iSize].segmentIndex - 1];
      //last segments numsdouble
      SA_sm_sweep_num->comNum[iSize].segmentDataNum = (quint32)(ceil(dfreqspan / dStep));
      SA_sm_sweep_num->comNum[iSize].segmentDataNum = SA_sm_sweep_num->comNum[iSize].segmentDataNum == 0 ? 1 : SA_sm_sweep_num->comNum[iSize].segmentDataNum;

      if(FIR_MODE == sweepMode)
      {
          daddedfreq = 0.;
      }
      else
      {
          daddedfreq = dStep * 0.5;
          if(SA_sm_sweep_num->comNum[iSize].segmentDataNum <= 1)
            {
              SA_sm_sweep_num->comNum[iSize].segmentDataNum = 1;
              //daddedfreq = dfreqspan * 0.5;
            }
      }

      msumfftsweepoints += SA_sm_sweep_num->comNum[iSize].segmentDataNum;
      SA_sm_sweep_num->segmentsDataSumNum += (SA_sm_sweep_num->comNum[iSize].segmentDataNum * onetomulti);
      temppersegtime = SA_sm_sweep_num->comNum[iSize].segmentDataNum * tempsingsweeptime + dSteptime;
      SA_sm_sweep_num->comNum[i].persegsweeptimes = temppersegtime;
      GetFreqDivValue(freqChannelList[SA_sm_sweep_num->comNum[iSize].segmentIndex - 1],daddedfreq,&SA_sm_sweep_num->comNum[iSize].seglostartfreqinter,&SA_sm_sweep_num->comNum[iSize].seglostartfreqfrac);
      //by Steve,0328
      GetStepFrqDivValue(freqChannelList[SA_sm_sweep_num->comNum[iSize].segmentIndex - 1],dStep,&SA_sm_sweep_num->comNum[iSize].seglosteplow,&SA_sm_sweep_num->comNum[iSize].seglostephigh);
  }
  else//only one segment
  {
      /*calc every segment points*/
      SA_sm_sweep_num->comNum[0].segmentDataNum = (quint32)(ceil(globalUserVariable->gSpanFreq / dStep));
      SA_sm_sweep_num->comNum[0].segmentDataNum = SA_sm_sweep_num->comNum[0].segmentDataNum == 0 ? 1 : SA_sm_sweep_num->comNum[0].segmentDataNum;

      if(FIR_MODE == sweepMode) daddedfreq = 0.;
      else
      {
          daddedfreq = dStep * 0.5;
          if(SA_sm_sweep_num->comNum[0].segmentDataNum <= 1)
          {
              SA_sm_sweep_num->comNum[0].segmentDataNum = 1;
              //daddedfreq = globalUserVariable->gSpanFreq * 0.5;
          }
      }

      msumfftsweepoints += SA_sm_sweep_num->comNum[0].segmentDataNum;
      SA_sm_sweep_num->segmentsDataSumNum += (SA_sm_sweep_num->comNum[0].segmentDataNum * onetomulti);
      /*calc the freq div value of every segment start freq*/
      GetFreqDivValue(globalUserVariable->gStartFreq,daddedfreq,&SA_sm_sweep_num->comNum[0].seglostartfreqinter,&SA_sm_sweep_num->comNum[0].seglostartfreqfrac);
      //by steve 0418
      GetStepFrqDivValue(globalUserVariable->gStartFreq,dStep,&SA_sm_sweep_num->comNum[0].seglosteplow,&SA_sm_sweep_num->comNum[0].seglostephigh);
      SA_sm_sweep_num->comNum[0].persegsweeptimes = SA_sm_sweep_num->comNum[0].segmentDataNum * tempsingsweeptime + dSteptime;
  }

  //0716  steve calc per and sum segments data nums
  if(FIR_MODE == sweepMode)
  {
      SA_sm_sweep_num->sumSweeptime = SA_sm_sweep_num->segmentsDataSumNum  * tempsingsweeptime + SA_sm_sweep_num->segmentNum * 0.002;
      globalUserVariable->gautoMintimems += SA_sm_sweep_num->sumSweeptime;

      if(!globalUserVariable->gsweepAuto)
      {
          if(globalUserVariable -> gmanSettimems < globalUserVariable->gautoMintimems)
          {
              globalUserVariable -> gmanSettimems = globalUserVariable->gautoMintimems;
              globalUserVariable->gSweepTime = globalUserVariable -> gmanSettimems;
          }
          else
          {
              globalUserVariable->gSweepTime = globalUserVariable -> gmanSettimems;
              SA_sm_sweep_num->sumSweeptime = globalUserVariable -> gmanSettimems - SA_sm_sweep_num->segmentNum * interRuptCommutimems;
          }
          gsweepflag = 1;
          SettingSweepTimeManmode(globalUserVariable -> gmanSettimems,globalUserVariable->gautoMintimems);
          gsweepflag = 0;
      }
      else
      {
          globalUserVariable->gSweepTime = globalUserVariable->gautoMintimems;
      }
      SA_sm_sweep_num->firBucketimeus = SA_sm_sweep_num->sumSweeptime / globalUserVariable->gTracePoint;
      //SA_sm_config_sweep->checkinsert = -1;

      //*************Johnson 190611
      globalUserVariable->gcheckswitch = 0;//0 check and not insert,1 direct and insert,2 check and insert
      SA_sm_config_sweep->checkswitch = 0;
      SA_sm_config_sweep->checkinsert = -1;
  }
  else
  {
      SA_sm_sweep_num->sumSweeptime = msumfftsweepoints  * tempsingsweeptime + SA_sm_sweep_num->segmentNum * 0.002;
      globalUserVariable->gautoMintimems += SA_sm_sweep_num->sumSweeptime;
      globalUserVariable->gSweepTime = globalUserVariable->gautoMintimems;
      SA_sm_sweep_num->fftBucketnum = 0.1 * 10 * SA_sm_sweep_num->segmentsDataSumNum / globalUserVariable->gTracePoint;

      //0903 by steve<1>check and extract and insert<2>uncheck and extract and insert<uncheck and not extract and insert>
      if(SA_sm_sweep_num->segmentsDataSumNum < globalUserVariable->gTracePoint ||
              ((dspantostep < 1.0 - 1.0e-6)/* || (SA_sm_sweep_num->segmentsDataSumNum * dspantostep < globalUserVariable->gTracePoint)*/))
      {
          //0905
          SA_sm_config_sweep->spanperstep = dspantostep;
          if(dspantostep < 1.0 + 1.0e-6)
          {
              //span in one channel and only one sweep point
              if(1 == SA_sm_sweep_num->segmentNum)
              {
                  //check and extract and insert
                  if(onetomulti > globalUserVariable->gTracePoint)
                  {
                      globalUserVariable->gcheckswitch = 2;
                      SA_sm_config_sweep->checkswitch = 0;
                      SA_sm_config_sweep->checkinsert = 0;
                      SA_sm_config_sweep->firstper = dspantostep;
                      SA_sm_config_sweep->secper = 0.;
                  }
                  //no check and extract and insert
                  else
                  {
                      globalUserVariable->gcheckswitch = 1;
                      SA_sm_config_sweep->checkswitch = 1;
                      SA_sm_config_sweep->checkinsert = 1;
                      SA_sm_config_sweep->firstper = dspantostep;
                      SA_sm_config_sweep->secper = 0.;
                  }
              }
              //span in more than one channel
              //and in this situation just two channel
              else
              {
                  if((onetomulti << 1) > globalUserVariable->gTracePoint)
                  {
                      globalUserVariable->gcheckswitch = 2;
                      SA_sm_config_sweep->checkswitch = 0;
                      SA_sm_config_sweep->checkinsert = 0;
                  }
                  else
                  {
                      globalUserVariable->gcheckswitch = 1;
                      SA_sm_config_sweep->checkswitch = 1;
                      SA_sm_config_sweep->checkinsert = 1;
                  }
                  SA_sm_config_sweep->firstper = (freqChannelList[SA_sm_sweep_num->comNum[0].segmentIndex] - globalUserVariable->gStartFreq) / dStep;
                  SA_sm_config_sweep->secper = (globalUserVariable->gStopFreq - freqChannelList[SA_sm_sweep_num->comNum[0].segmentIndex]) / dStep;
              }
          }
          //means datanum smaller than trace num
          else
          {
              globalUserVariable->gcheckswitch = 1;
              SA_sm_config_sweep->checkswitch = 1;
              SA_sm_config_sweep->checkinsert = 1;
              if(1 == SA_sm_sweep_num->segmentNum)
              {
                  //just calc last point percent
                  SA_sm_config_sweep->firstper = globalUserVariable->gSpanFreq / dStep - (qint32)(globalUserVariable->gSpanFreq / dStep);
                  SA_sm_config_sweep->secper = 0.;
              }
              else
              {
                  //calc separate and last percent
                  SA_sm_config_sweep->firstper = (freqChannelList[SA_sm_sweep_num->comNum[0].segmentIndex] - globalUserVariable->gStartFreq) / dStep -
                          (qint32)((freqChannelList[SA_sm_sweep_num->comNum[0].segmentIndex] - globalUserVariable->gStartFreq) / dStep);
                  SA_sm_config_sweep->secper = (globalUserVariable->gStopFreq - freqChannelList[SA_sm_sweep_num->comNum[0].segmentIndex]) / dStep -
                          (qint32)((globalUserVariable->gStopFreq - freqChannelList[SA_sm_sweep_num->comNum[0].segmentIndex]) / dStep);
              }
          }
      }
      else
      {
          if (dspantostep < (globalUserVariable->gTracePoint >> 1))
              if (1 == SA_sm_sweep_num->segmentNum){
                  globalUserVariable->gcheckswitch = 2;
                  SA_sm_config_sweep->checkswitch = 0;
                  SA_sm_config_sweep->checkinsert = 0;
                  SA_sm_config_sweep->firstper = globalUserVariable->gSpanFreq/(SA_sm_sweep_num->loStepHz*SA_sm_sweep_num->comNum[0].segmentDataNum);
                  SA_sm_config_sweep->secper = 0.;
              } else {
                  globalUserVariable->gcheckswitch = 2;
                  SA_sm_config_sweep->checkswitch = 0;
                  SA_sm_config_sweep->checkinsert = 0;
                  SA_sm_config_sweep->firstper = (freqChannelList[SA_sm_sweep_num->comNum[0].segmentIndex] - globalUserVariable->gStartFreq) /
                      (SA_sm_sweep_num->loStepHz*SA_sm_sweep_num->comNum[0].segmentDataNum);
                  SA_sm_config_sweep->secper = (globalUserVariable->gStopFreq - freqChannelList[SA_sm_sweep_num->comNum[0].segmentIndex]) /
                      (SA_sm_sweep_num->loStepHz*SA_sm_sweep_num->comNum[1].segmentDataNum);
              }
          else {
              globalUserVariable->gcheckswitch = 0;//0 check and not insert,1 direct and insert,2 check and insert
              SA_sm_config_sweep->checkswitch = 0;
              SA_sm_config_sweep->checkinsert = -1;
          }
      }
  }
  return;
}

qint32 alothforsa::GetFftRbwIndex()
{
  qint32 iNum = sizeof(chparamlist) / sizeof(SA_CHANNEL_PARAM);
  qint32 i = 0;
  for(i = 0; i < iNum; i++)
  {
      if(globalUserVariable->gRbw >= (chparamlist+i)->rbwkHz) return i;
  }
  return iNum - 1;
}

//fen pin bi
void alothforsa::GetFreqDivValue(qreal freqHz,qreal dffthalfstepHz,quint32* intdiv,quint32* fracdiv)
{
  qint32 iIndex = GetFreqChannelIndex(freqHz);
  qint32 maxIndex = sizeof(freqChannelList) / sizeof(qreal) -1;
  //0522,steve
#ifdef SA_SEG_START_STOP_NEW
  if(freqHz >= (globalUserVariable->gStartFreq - ESP) && (freqHz <= globalUserVariable->gStartFreq + ESP))
  {
      if(globalUserVariable->gStartFreq >= freqChannelList[iIndex] - SA_SEG_START_STOP_EXTENSION)
      {
          iIndex ++;
      }
  }
  else if(freqHz >= (globalUserVariable->gStopFreq - ESP) && (freqHz <= globalUserVariable->gStopFreq + ESP))
  {
      if(globalUserVariable->gStopFreq <= freqChannelList[iIndex - 1] - SA_SEG_START_STOP_EXTENSION)
      {
          iIndex --;
      }
  }
  else
  {
      if(freqChannelList[iIndex] <= freqHz + ESP  &&
         freqChannelList[iIndex] >= freqHz - ESP  &&
         freqChannelList[maxIndex] != freqHz)
      {
          iIndex = iIndex;
      }
      else
      {
          iIndex--;
      }
  }
#else
  if(freqChannelList[iIndex] <= freqHz + ESP  &&
     freqChannelList[iIndex] >= freqHz - ESP  &&
     freqChannelList[maxIndex] != freqHz)
  {
      iIndex = iIndex;
  }
  else
  {
      iIndex--;
  }
#endif
  //Steve,0309
  //iIndex = iIndex == 0 ? iIndex : iIndex - 1;
  //0828
  freqHz += dffthalfstepHz;
  qreal temp = (freqHz + lodivList[iIndex].iffreq) / REF_CLOCK * lodivList[iIndex].d * lodivList[iIndex].r / lodivList[iIndex].feedback;

  qDebug()<<"Freq is "<<freqHz;
  qDebug()<<"The loDiv result is "<<temp;

  *intdiv = (quint32)temp;
  //Steve,0309
  u_int64_t tempfrac = (u_int64_t)ceil((temp - *intdiv) * 4 * (1 << 16) * (1 << 30));
  *fracdiv = (tempfrac & 0xffffffff);
  *intdiv <<= 16;
  *intdiv |= (tempfrac >> 32 & 0xffff);
  return;
}

/*criflg 1 means end freq and should belong to former seg
0 means start freq and should belong to later segment*/
//bu jin fen pin bi
void alothforsa::GetStepFrqDivValue(qreal startfreq,qreal stepHz,quint32* lowbits,quint32* highbits)
{
  qint32 iIndex = GetFreqChannelIndex(startfreq);

  qint32 maxIndex = sizeof(freqChannelList) / sizeof(qreal) -1;

#ifdef SA_SEG_START_STOP_NEW
  if(startfreq >= (globalUserVariable->gStartFreq - ESP) && (startfreq <= globalUserVariable->gStartFreq + ESP))
  {
      if(globalUserVariable->gStartFreq >= freqChannelList[iIndex] - SA_SEG_START_STOP_EXTENSION)
      {
          iIndex ++;
      }
  }
  else if(startfreq >= (globalUserVariable->gStopFreq - ESP) && (startfreq <= globalUserVariable->gStopFreq + ESP) && iIndex > 0)
  {
      if(globalUserVariable->gStopFreq <= freqChannelList[iIndex] - SA_SEG_START_STOP_EXTENSION)
      {
          iIndex --;
      }
  }
  else
  {
      //0522,steve
      if(freqChannelList[iIndex] <= startfreq + ESP  &&
         freqChannelList[iIndex] >= startfreq - ESP  &&
         freqChannelList[maxIndex] != startfreq)
      {
          iIndex = iIndex;
      }
      else
      {
          iIndex--;
      }
  }
#else
  //0522,steve
  if(freqChannelList[iIndex] <= startfreq + ESP  &&
     freqChannelList[iIndex] >= startfreq - ESP  &&
     freqChannelList[maxIndex] != startfreq)
  {
      iIndex = iIndex;
  }
  else
  {
      iIndex--;
  }
#endif
  //iIndex = iIndex == 0 ? iIndex : iIndex - 1;
  qreal temp = stepHz / REF_CLOCK * lodivList[iIndex].d * lodivList[iIndex].r / lodivList[iIndex].feedback;
  u_int64_t tempfrac = (u_int64_t)(temp * (1 << 24) * (1 << 24));
  *lowbits = tempfrac & 0xffffffff;
  *highbits = (tempfrac >> 32) & 0xffff;
  return;
}

void alothforsa::GetLastPartTime(qint32 iIndex)
{
  SA_sm_sweep_num->seglokeeptime = (quint32)(dealTimeList[iIndex] / fstimens);
  return;
}


/***************extern interface**********/
qint32 alothforsa::ConfigureFrequencyStartStop (qreal startFrequency,qreal stopFrequency)
{
  //0713 clear
  globalUserVariable->gautoMintimems = 0.0;

  //get segment index   SA_sm_config_sweep->sweepMode
  GetSegmentWaveIndex(0);

  //0713
  globalUserVariable->gautoMintimems += SA_sm_sweep_num->segmentNum * interRuptCommutimems;

  //associate with rbw
  if(globalUserVariable->gAutoRbw)
  {
      //calc rbw through the span,0.01
      qint32 tempIndexcalc = GetrbwIndex(globalUserVariable->gSpanFreq * rbwtospan);
      qint32 tempIndexnow = GetrbwIndex((qreal)globalUserVariable->gRbw);
      //by Steve,0302
      globalUserVariable->grbwChangedbyFreq = 0;
      if(tempIndexnow != tempIndexcalc)
      {
          rbwTrigDoor = 1;
          globalUserVariable->grbwChangedbyFreq = 1;
          ConfigureSweepCoupling(globalUserVariable->gAutoRbw,rbwList[tempIndexcalc],globalUserVariable->gAutoVbw,globalUserVariable->gVbw,globalUserVariable->gAutoVbwtoRbw,globalUserVariable->gVbwtoRbw);
          rbwTrigDoor = !rbwTrigDoor;
      }
  }
  else
  {
      //by Steve,0309
      //recover lostep by now  rbw when fir mode
      if(FIR_MODE == SA_sm_config_sweep->sweepMode)
      {
          SA_sm_sweep_num->loStepHz = globalUserVariable->gRbw * firStep;
      }
  }
  //calculate params by sweep mode
  RefCalSweepParams(SA_sm_config_sweep->sweepMode);
  return 0;
}

//0716 this interface only used in fir mode,in man sweep time mode
void alothforsa::SettingSweepTimeManmode(qreal sweeptimems,qreal autotimems)
{
  qint32 iflag = 0;
  if(sweeptimems < autotimems)//Johnson 19217
  {
      iflag = 1;
      sweeptimems = autotimems;
  }
  //firstly calc persegment points num and sum points num
  //if(sweeptimems > autotimems)
  {
      SA_sm_sweep_num->segmentsDataSumNum = 0;
      quint32 i = 0;
      qint32 iSize = SA_sm_sweep_num->segmentNum - 1;
      //means call setting sweep time direct
      if(!gsweepflag)
      {
          //recover loStepHz
          SA_sm_sweep_num->loStepHz = globalUserVariable->gRbw * firStep;
      }
      qreal dStep = SA_sm_sweep_num->loStepHz;

      if(SA_sm_sweep_num->segmentNum > 1)
      {
          qreal dfreqspan = freqChannelList[SA_sm_sweep_num->comNum[0].segmentIndex] - globalUserVariable->gStartFreq;
          //first seg points num
          SA_sm_sweep_num->comNum[0].segmentDataNum = (quint32)(ceil(dfreqspan / dStep));
          SA_sm_sweep_num->comNum[0].segmentDataNum = SA_sm_sweep_num->comNum[0].segmentDataNum == 0 ? 1 : SA_sm_sweep_num->comNum[0].segmentDataNum;
          SA_sm_sweep_num->segmentsDataSumNum += SA_sm_sweep_num->comNum[0].segmentDataNum;
          for(i = 1; i < SA_sm_sweep_num->segmentNum - 1; i++)
          {
              dfreqspan = freqChannelList[SA_sm_sweep_num->comNum[i].segmentIndex] - freqChannelList[SA_sm_sweep_num->comNum[i - 1].segmentIndex];
              SA_sm_sweep_num->comNum[i].segmentDataNum = (quint32)(ceil(dfreqspan / dStep));
              SA_sm_sweep_num->comNum[i].segmentDataNum = SA_sm_sweep_num->comNum[i].segmentDataNum == 0 ? 1 : SA_sm_sweep_num->comNum[i].segmentDataNum;
              SA_sm_sweep_num->segmentsDataSumNum += SA_sm_sweep_num->comNum[i].segmentDataNum;
          }

          dfreqspan = globalUserVariable->gStopFreq - freqChannelList[SA_sm_sweep_num->comNum[iSize].segmentIndex - 1];

          SA_sm_sweep_num->comNum[iSize].segmentDataNum = (quint32)(ceil(dfreqspan / dStep));
          SA_sm_sweep_num->comNum[iSize].segmentDataNum = SA_sm_sweep_num->comNum[iSize].segmentDataNum == 0 ? 1 : SA_sm_sweep_num->comNum[iSize].segmentDataNum;
          SA_sm_sweep_num->segmentsDataSumNum += SA_sm_sweep_num->comNum[iSize].segmentDataNum;
      }
      //only one segment
      else
      {
          //calc every segment points
          SA_sm_sweep_num->comNum[0].segmentDataNum = (quint32)(ceil(globalUserVariable->gSpanFreq / dStep));
          SA_sm_sweep_num->comNum[0].segmentDataNum = SA_sm_sweep_num->comNum[0].segmentDataNum == 0 ? 1 : SA_sm_sweep_num->comNum[0].segmentDataNum;
          SA_sm_sweep_num->segmentsDataSumNum += SA_sm_sweep_num->comNum[0].segmentDataNum;
      }

      //sum sweep points num by sweeptimems
      qint32 inowsumnum = (sweeptimems - SA_sm_sweep_num->segmentNum * (0.002 + interRuptCommutimems)) / globalUserVariable -> gfirsingletimems;
      sweeptimems = inowsumnum * globalUserVariable -> gfirsingletimems + SA_sm_sweep_num->segmentNum * (0.002 + interRuptCommutimems);

      if(1 == iflag)
      {
          SA_sm_sweep_num->loStepHz = globalUserVariable->gRbw * firStep;
      }
      else
      {
          SA_sm_sweep_num->loStepHz = (qreal)globalUserVariable->gSpanFreq / inowsumnum;//Johnson 19217
      }
      dStep = SA_sm_sweep_num->loStepHz;

      if(SA_sm_sweep_num->segmentNum > 1)
      {
          SA_sm_sweep_num->comNum[0].segmentDataNum = (qreal)SA_sm_sweep_num->comNum[0].segmentDataNum / SA_sm_sweep_num->segmentsDataSumNum * inowsumnum + 0.5;
          SA_sm_sweep_num->comNum[0].segmentDataNum = SA_sm_sweep_num->comNum[0].segmentDataNum == 0 ? 1 : SA_sm_sweep_num->comNum[0].segmentDataNum;
          SA_sm_sweep_num->comNum[0].persegsweeptimes = SA_sm_sweep_num->comNum[0].segmentDataNum * globalUserVariable -> gfirsingletimems + 0.002;
          //calc the freq div value of every segment start freq
          GetFreqDivValue(globalUserVariable->gStartFreq,0.0,&SA_sm_sweep_num->comNum[0].seglostartfreqinter,&SA_sm_sweep_num->comNum[0].seglostartfreqfrac);
          GetStepFrqDivValue(globalUserVariable->gStartFreq,dStep,&SA_sm_sweep_num->comNum[0].seglosteplow,&SA_sm_sweep_num->comNum[0].seglostephigh);

          for(i = 1; i < SA_sm_sweep_num->segmentNum - 1; i++)
          {
              SA_sm_sweep_num->comNum[i].segmentDataNum = (qreal)SA_sm_sweep_num->comNum[i].segmentDataNum / SA_sm_sweep_num->segmentsDataSumNum * inowsumnum + 0.5;
              SA_sm_sweep_num->comNum[i].segmentDataNum = SA_sm_sweep_num->comNum[i].segmentDataNum == 0 ? 1 : SA_sm_sweep_num->comNum[i].segmentDataNum;
              SA_sm_sweep_num->comNum[i].persegsweeptimes = SA_sm_sweep_num->comNum[i].segmentDataNum * globalUserVariable -> gfirsingletimems + 0.002;

              GetFreqDivValue(freqChannelList[SA_sm_sweep_num->comNum[i].segmentIndex - 1],0.0,&SA_sm_sweep_num->comNum[i].seglostartfreqinter,&SA_sm_sweep_num->comNum[i].seglostartfreqfrac);
              GetStepFrqDivValue(freqChannelList[SA_sm_sweep_num->comNum[i].segmentIndex - 1],dStep,&SA_sm_sweep_num->comNum[i].seglosteplow,&SA_sm_sweep_num->comNum[i].seglostephigh);

          }
          SA_sm_sweep_num->comNum[iSize].segmentDataNum = (qreal)SA_sm_sweep_num->comNum[iSize].segmentDataNum / SA_sm_sweep_num->segmentsDataSumNum * inowsumnum + 0.5;
          SA_sm_sweep_num->comNum[iSize].segmentDataNum = SA_sm_sweep_num->comNum[iSize].segmentDataNum == 0 ? 1 : SA_sm_sweep_num->comNum[iSize].segmentDataNum;
          SA_sm_sweep_num->comNum[iSize].persegsweeptimes = SA_sm_sweep_num->comNum[iSize].segmentDataNum * globalUserVariable -> gfirsingletimems + 0.002;

          GetFreqDivValue(freqChannelList[SA_sm_sweep_num->comNum[iSize].segmentIndex - 1],0.0,&SA_sm_sweep_num->comNum[iSize].seglostartfreqinter,&SA_sm_sweep_num->comNum[iSize].seglostartfreqfrac);
          GetStepFrqDivValue(freqChannelList[SA_sm_sweep_num->comNum[iSize].segmentIndex - 1],dStep,&SA_sm_sweep_num->comNum[iSize].seglosteplow,&SA_sm_sweep_num->comNum[iSize].seglostephigh);
      }
      else
      {
          SA_sm_sweep_num->comNum[0].segmentDataNum = (qreal)SA_sm_sweep_num->comNum[0].segmentDataNum / SA_sm_sweep_num->segmentsDataSumNum * inowsumnum + 0.5;
          SA_sm_sweep_num->comNum[0].segmentDataNum = SA_sm_sweep_num->comNum[0].segmentDataNum == 0 ? 1 : SA_sm_sweep_num->comNum[0].segmentDataNum;
          SA_sm_sweep_num->comNum[0].persegsweeptimes = SA_sm_sweep_num->comNum[0].segmentDataNum * globalUserVariable -> gfirsingletimems + 0.002;
          GetFreqDivValue(globalUserVariable->gStartFreq,0.0,&SA_sm_sweep_num->comNum[0].seglostartfreqinter,&SA_sm_sweep_num->comNum[0].seglostartfreqfrac);
          GetStepFrqDivValue(globalUserVariable->gStartFreq,dStep,&SA_sm_sweep_num->comNum[0].seglosteplow,&SA_sm_sweep_num->comNum[0].seglostephigh);
      }
      SA_sm_sweep_num->sumSweeptime = sweeptimems - SA_sm_sweep_num->segmentNum * interRuptCommutimems;

      if(!gsweepflag)
      {
          SA_sm_sweep_num->firBucketimeus = SA_sm_sweep_num->sumSweeptime / globalUserVariable->gTracePoint;
      }
  }
  return;
}

qreal alothforsa::GetZeroSpanRbwMinms(quint32 tracenums)
{
  qreal temp  = *(firfskHzlist + GetrbwIndex((qreal)globalUserVariable->gRbw));
  temp = temp < 0.0001 ? 0.0001 : temp;
  return temp * tracenums;
}

void alothforsa::GetZeroShmTimes(qreal timems,quint32 tracenum)
{
  SA_sm_sweep_num->sumSweeptime = timems;
  SA_sm_sweep_num->firBucketimeus = SA_sm_sweep_num->sumSweeptime / tracenum;
  return;
}

qint32 alothforsa::GetrbwIndex(qreal rbwHz)
{
  //check param
  qint32 iListLeng = sizeof(rbwList) / sizeof(qreal);
  iListLeng = iListLeng < 1 ? 1 : iListLeng;
  rbwHz = rbwHz > rbwList[0] ? rbwList[0] : rbwHz;
  rbwHz = rbwHz < rbwList[iListLeng - 1] ? rbwList[iListLeng - 1] : rbwHz;

  qint32 iIndex = 0;
  for(iIndex = 0; iIndex < iListLeng; iIndex++)
  {
      if(*(rbwList + iIndex) <= rbwHz)
        return iIndex;
  }
  return iIndex - 1;
}

qint32 alothforsa::ConfigureSweepCoupling (quint32 resolutionBandwidthAuto,qreal resolutionBandwidth,quint32 videoBandwidthAuto,qreal videoBandwidth,quint32 vbwtorbwAuto,qreal vbwtorbwValue)
{
  resolutionBandwidthAuto = !!resolutionBandwidthAuto;
  globalUserVariable->gAutoRbw = resolutionBandwidthAuto;
  videoBandwidthAuto = !!videoBandwidthAuto;
  globalUserVariable->gAutoVbw = videoBandwidthAuto;
  vbwtorbwAuto = !!vbwtorbwAuto;
  globalUserVariable->gAutoVbwtoRbw = vbwtorbwAuto;

  rbwFlag = 0;
  //adjust the couple param,when rbw is auto
  if(globalUserVariable->gAutoRbw /*&& 3 != SA_sm_config_sweep->sweepMode*/)
  {
      //get the rbw through the span
      qint32 spanrbwIndex = GetrbwIndex(globalUserVariable->gSpanFreq * rbwtospan);
      qint32 nowIndex = GetrbwIndex((qreal)globalUserVariable->gRbw);

      //0504
      SA_autoChangerbwflag = 0;
      //Tony 190613
      if((!!globalUserVariable->gSpanFreq) && nowIndex != spanrbwIndex)
      {
          //0504
          SA_autoChangerbwflag = 1;

          rbwFlag = 1;
          globalUserVariable->gRbw = (quint32)rbwList[spanrbwIndex];
          GetLastPartTime(spanrbwIndex);
          ParamConvertByRbw(spanrbwIndex);
          //down rbw and vbw in the ctrlapp
      }

      //bug,Steve,0302
      if(globalUserVariable->gAutoVbw)
      {
//          if(globalUserVariable->gAutoVbwtoRbw)
//          {
//              globalUserVariable->gVbwtoRbw = vbwtorbw;
//          }
//          else
//          {
//              globalUserVariable->gVbwtoRbw = vbwtorbwValue;
//          }
          //Tony 0402
          globalUserVariable->gVbwtoRbw = vbwtorbwValue;

          qint32 iIndex = GetrbwIndex(globalUserVariable->gRbw * globalUserVariable->gVbwtoRbw);
#if !ADD_5MVBW
          iIndex = iIndex == 0 ? 1 : iIndex;
#endif
          qint32 ilastIndex = GetrbwIndex(globalUserVariable->gVbw);
#if !ADD_5MVBW
          ilastIndex = ilastIndex == 0 ?1 : ilastIndex;
#endif
          SA_autoChangevbwflag = 0;
          if(iIndex != ilastIndex)
          {
              SA_autoChangevbwflag = 1;
              rbwFlag = 1;//Johnson 20200409
          }
          globalUserVariable->gVbw =(quint32)rbwList[iIndex];
          //globalUserVariable->gVbw = (quint32)((qint32)rbwList[iIndex] * globalUserVariable->gVbwtoRbw);
      }
      else
      {
          qint32 vbwIndex = GetrbwIndex(videoBandwidth);
#if !ADD_5MVBW
          vbwIndex = vbwIndex == 0?1:vbwIndex;//Johnson 1123
#endif
          globalUserVariable->gVbw = (quint32)rbwList[vbwIndex];

          rbwFlag = 1;//Johnson 20200409
      }
  }
  //the rbw is man
  else
  {
      rbwFlag = 1;
      qint32 rbwIndex = GetrbwIndex(resolutionBandwidth);
      globalUserVariable->gRbw = (quint32)rbwList[rbwIndex];
      GetLastPartTime(rbwIndex);
      //vbw is not 5MHz
      rbwIndex = rbwIndex == 0 ? 1 : rbwIndex;
      //more used
      if(globalUserVariable->gAutoVbw)
      {
//          if(globalUserVariable->gVbwtoRbw)
//          {
//              globalUserVariable->gVbwtoRbw = vbwtorbw;
//          }
//          else
//          {
//              globalUserVariable->gVbwtoRbw = vbwtorbwValue;
//          }
          //Tony 0402
          globalUserVariable->gVbwtoRbw = vbwtorbwValue;

          qint32 iIndex = GetrbwIndex(globalUserVariable->gRbw * globalUserVariable->gVbwtoRbw);
#if !ADD_5MVBW
          iIndex = iIndex == 0 ? 1 : iIndex;
#endif
          qint32 ilastIndex = GetrbwIndex(globalUserVariable->gVbw);
#if !ADD_5MVBW
          ilastIndex = ilastIndex == 0 ? 1: ilastIndex;
#endif
          SA_autoChangevbwflag = 0;
          if(iIndex != ilastIndex)
          {
              SA_autoChangevbwflag = 1;
          }
          globalUserVariable->gVbw =(quint32)rbwList[iIndex];
          //globalUserVariable->gVbw = (quint32)((qint32)rbwList[rbwIndex] * globalUserVariable->gVbwtoRbw);
      }
      else
      {
          qint32 vbwIndex = GetrbwIndex(videoBandwidth);
#if !ADD_5MVBW
          vbwIndex = vbwIndex == 0?1:vbwIndex;//Johnson 1123
#endif
          globalUserVariable->gVbw = (quint32)rbwList[vbwIndex];
      }

      ParamConvertByRbw(rbwIndex);
  }

  if(!rbwTrigDoor && rbwFlag)
  {
      //0713
      globalUserVariable->gautoMintimems = 0.0;
      //0713
      globalUserVariable->gautoMintimems += SA_sm_sweep_num->segmentNum * interRuptCommutimems;

      //recalc time
      RefCalSweepParams(SA_sm_config_sweep->sweepMode);
  }
  return 0;
}

void alothforsa::ParamConvertByRbw(qint32 iIndex)
{
  qint32 tempIndex = 0;
  //get the sweep mode of FIR
  if(iIndex <= 6)
  {
      SA_sm_config_sweep->sweepMode = FIR_MODE;
      globalUserVariable->ganamode = SA_sm_config_sweep->sweepMode;
      //calc lo step
      SA_sm_sweep_num->loStepHz = globalUserVariable->gRbw * firStep;
  }
  else//FFT mode
  {
      tempIndex = GetFftRbwIndex();
      SA_sm_config_sweep->sweepMode = FFT_MODE;
      globalUserVariable->ganamode = SA_sm_config_sweep->sweepMode;
      //calc lo step
      SA_sm_sweep_num->loStepHz = chparamlist[tempIndex].stepFreqHz;
      SA_sm_sweep_num->startIndex = chparamlist[tempIndex].fftNum * (1 - chparamlist[tempIndex].validRatio) * 0.5;

      //0828
      SA_sm_sweep_num->stopIndex = chparamlist[tempIndex].fftNum * (1 - (1 - chparamlist[tempIndex].validRatio) * 0.5);
      SA_sm_sweep_num->fftNum = SA_sm_sweep_num->stopIndex - SA_sm_sweep_num->startIndex + 1;
  }
  return;
}

qreal alothforsa::caculateFreqCount(qreal centerFreq,qint32 fsr,quint32 rbwValue)
{
    quint32 rbwIndex = GetrbwIndex((qreal)rbwValue);
    qreal qFreqCount = centerFreq + fsr / pow(2.,33.) * (FFREQ / frbw[rbwIndex]);

    return qFreqCount;
}
