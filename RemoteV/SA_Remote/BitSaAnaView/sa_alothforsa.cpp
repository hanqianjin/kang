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
  if(freqChannelList[istartIndex] <= globalUserVariable->gStartFreq + ESP)
    {
      istartIndex++;
    }
  qint32 istopIndex = GetFreqChannelIndex(globalUserVariable->gStopFreq);

  qint32 ioverflag = 0;
  if(istartIndex > istopIndex)
    {
      ioverflag = 1;
      istartIndex = istopIndex;
    }

  globalUserVariable->segmentNum = istopIndex - istartIndex + 1;
  if(1 == globalUserVariable->segmentNum && ioverflag)
    {
      globalUserVariable->comNum[0].segmentIndex = istartIndex;
    }
  else
    {
      quint32 i = 0;
      for(i = 0; i < globalUserVariable->segmentNum; i++)
        {
          //start from zero index,cor with wave index and data nums
          globalUserVariable->comNum[i].segmentIndex = istartIndex + i;
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
  globalUserVariable->sumSweeptime = 0;
  globalUserVariable->segmentsDataSumNum = 0;
  //steve,0504
  qreal temppersegtime = 0.;
  //0725
  qreal tempsingsweeptime = 0.0;
  quint32 onetomulti = 0.0;
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
      qint32 iNum = (quint32)(ceil(globalUserVariable->gSpanFreq / globalUserVariable->loStepHz));
      if(iNum <  globalUserVariable->gSweepTracePoint)
      {
          globalUserVariable->loStepHz = (qreal)globalUserVariable->gSpanFreq  / (globalUserVariable->gSweepTracePoint - 1);
      }
      dStep = globalUserVariable->loStepHz;
      dSteptime = 0.002;//normal to ms

      //calc fir single point time 0716
      if(globalUserVariable->gAutoDotSweepTime == SA_AUTO)
      {
          qint32 iFirRbwIndex = 0;
          iFirRbwIndex = GetrbwIndex((qreal)globalUserVariable->gRbw);
          if(globalUserVariable->gFixDotSweepTime == SA_ON)
          {
              globalUserVariable->gfirsingletimems = autoSetDotSweepTime[iFirRbwIndex];
          }
          else
          {
              globalUserVariable->gfirsingletimems = firfskHzlist[iFirRbwIndex] * (firfliterOrder[iFirRbwIndex]);//+ 4 + 1);
          }
          globalUserVariable -> gfirsingletimems = globalUserVariable -> gfirsingletimems < 0.002 ? 0.002 : globalUserVariable -> gfirsingletimems;

          globalUserVariable->firdottimems = globalUserVariable -> gfirsingletimems;
          globalUserVariable->gDotSweepTime = globalUserVariable->firdottimems;
      }
      else
      {
          globalUserVariable->firdottimems = globalUserVariable->gDotSweepTime;
          globalUserVariable -> gfirsingletimems = globalUserVariable->gDotSweepTime;
      }
      tempsingsweeptime = globalUserVariable->firdottimems;
      onetomulti = 1;
  }
  else if(FFT_MODE == sweepMode)
  {
      //0725 steve
      //iextranum = 0.5;
      //lo stdoubleep cor points
      dStep = globalUserVariable->loStepHz;
      //0903
      dspantostep = globalUserVariable->gSpanFreq / dStep;
      ifftRbwIndex = GetFftRbwIndex();
      dSteptime = 0.002;
      //globalUserVariable->singlefftTime = (chparamlist[ifftRbwIndex].fftNum + chparamlist[ifftRbwIndex].orderNum + 4) * chparamlist[ifftRbwIndex].tsms;
      if(globalUserVariable->gAutoDotSweepTime == SA_AUTO)
      {
          globalUserVariable->singlefftTime = (chparamlist[ifftRbwIndex].fftNum + chparamlist[ifftRbwIndex].orderNum) * chparamlist[ifftRbwIndex].tsms + dSteptime;//Johnson 190529
          //qint32 offset = (char *)(&globalUserVariable->singlefftTime) - (char *)SA_sm_sweep_num;//variable "singlefftTime" offset relative to starting address
          globalUserVariable->gDotSweepTime = globalUserVariable->singlefftTime;
      }
      else
      {
          globalUserVariable->singlefftTime = globalUserVariable->gDotSweepTime;
      }
      //set single fft time
      tempsingsweeptime = globalUserVariable->singlefftTime;
      onetomulti = globalUserVariable->fftNum;
  }

  //calc every seg sweep time and sum sweep time and segment points num
  qint32 temcriflg = 0;
  //0726
  qint32 msumfftsweepoints = 0;

  //0828
  qreal daddedfreq = 0.;
  if(globalUserVariable->segmentNum > 1)
  {
      qint32 iSize = globalUserVariable->segmentNum - 1;
      qreal dfreqspan = freqChannelList[globalUserVariable->comNum[0].segmentIndex] - globalUserVariable->gStartFreq;
      //first seg points num
      globalUserVariable->comNum[0].segmentDataNum = (quint32)(ceil(dfreqspan / dStep));
      globalUserVariable->comNum[0].segmentDataNum = globalUserVariable->comNum[0].segmentDataNum == 0 ? 1 : globalUserVariable->comNum[0].segmentDataNum;

      //0828,this happen only when fft mode
      if(FIR_MODE == sweepMode) daddedfreq = 0.;
      else
      {
          daddedfreq = dStep * 0.5;
          if(globalUserVariable->comNum[0].segmentDataNum <= 1)
          {
              globalUserVariable->comNum[0].segmentDataNum = 1;
              //daddedfreq = dfreqspan * 0.5;
          }
      }

      msumfftsweepoints += globalUserVariable->comNum[0].segmentDataNum;
      //first seg time
      //0504
      temppersegtime = globalUserVariable->comNum[0].segmentDataNum * tempsingsweeptime + dSteptime;
      globalUserVariable->comNum[0].persegsweeptimes = temppersegtime;
      //by Steve,0424
      //0725 if fft mode differ to fir mode
      globalUserVariable->segmentsDataSumNum += (globalUserVariable->comNum[0].segmentDataNum * onetomulti);
      /*calc the freq div value of every segment start freq*/
      temcriflg = 0;
      GetFreqDivValue(globalUserVariable->gStartFreq,daddedfreq,&globalUserVariable->comNum[0].seglostartfreqinter,&globalUserVariable->comNum[0].seglostartfreqfrac);
      //by Steve,0328
      GetStepFrqDivValue(globalUserVariable->gStartFreq,dStep,&globalUserVariable->comNum[0].seglosteplow,&globalUserVariable->comNum[0].seglostephigh);

      quint32 i = 0;
      for(i = 1; i < globalUserVariable->segmentNum - 1; i++)
      {
          dfreqspan = freqChannelList[globalUserVariable->comNum[i].segmentIndex] - freqChannelList[globalUserVariable->comNum[i - 1].segmentIndex];
          globalUserVariable->comNum[i].segmentDataNum = (quint32)(ceil(dfreqspan / dStep));
          globalUserVariable->comNum[i].segmentDataNum = globalUserVariable->comNum[i].segmentDataNum == 0 ? 1 : globalUserVariable->comNum[i].segmentDataNum;
          msumfftsweepoints += globalUserVariable->comNum[i].segmentDataNum;
          globalUserVariable->segmentsDataSumNum += (globalUserVariable->comNum[i].segmentDataNum * onetomulti);
          temppersegtime = globalUserVariable->comNum[i].segmentDataNum * tempsingsweeptime + dSteptime;
          globalUserVariable->comNum[i].persegsweeptimes = temppersegtime;

          if(FIR_MODE == sweepMode)
          {
              daddedfreq = 0.;
          }
          else
          {
              daddedfreq = dStep * 0.5;
          }
          //by Steve,0309
          GetFreqDivValue(freqChannelList[globalUserVariable->comNum[i].segmentIndex - 1],daddedfreq,&globalUserVariable->comNum[i].seglostartfreqinter,&globalUserVariable->comNum[i].seglostartfreqfrac);
          //by Steve,0328
          GetStepFrqDivValue(freqChannelList[globalUserVariable->comNum[i].segmentIndex - 1],dStep,&globalUserVariable->comNum[i].seglosteplow,&globalUserVariable->comNum[i].seglostephigh);
      }
      dfreqspan = globalUserVariable->gStopFreq - freqChannelList[globalUserVariable->comNum[iSize].segmentIndex - 1];
      //last segments numsdouble
      globalUserVariable->comNum[iSize].segmentDataNum = (quint32)(ceil(dfreqspan / dStep));
      globalUserVariable->comNum[iSize].segmentDataNum = globalUserVariable->comNum[iSize].segmentDataNum == 0 ? 1 : globalUserVariable->comNum[iSize].segmentDataNum;

      if(FIR_MODE == sweepMode)
      {
          daddedfreq = 0.;
      }
      else
      {
          daddedfreq = dStep * 0.5;
          if(globalUserVariable->comNum[iSize].segmentDataNum <= 1)
            {
              globalUserVariable->comNum[iSize].segmentDataNum = 1;
              //daddedfreq = dfreqspan * 0.5;
            }
      }

      msumfftsweepoints += globalUserVariable->comNum[iSize].segmentDataNum;
      globalUserVariable->segmentsDataSumNum += (globalUserVariable->comNum[iSize].segmentDataNum * onetomulti);
      temppersegtime = globalUserVariable->comNum[iSize].segmentDataNum * tempsingsweeptime + dSteptime;
      globalUserVariable->comNum[i].persegsweeptimes = temppersegtime;
      GetFreqDivValue(freqChannelList[globalUserVariable->comNum[iSize].segmentIndex - 1],daddedfreq,&globalUserVariable->comNum[iSize].seglostartfreqinter,&globalUserVariable->comNum[iSize].seglostartfreqfrac);
      //by Steve,0328
      GetStepFrqDivValue(freqChannelList[globalUserVariable->comNum[iSize].segmentIndex - 1],dStep,&globalUserVariable->comNum[iSize].seglosteplow,&globalUserVariable->comNum[iSize].seglostephigh);
  }
  else//only one segment
  {
      /*calc every segment points*/
      globalUserVariable->comNum[0].segmentDataNum = (quint32)(ceil(globalUserVariable->gSpanFreq / dStep));
      globalUserVariable->comNum[0].segmentDataNum = globalUserVariable->comNum[0].segmentDataNum == 0 ? 1 : globalUserVariable->comNum[0].segmentDataNum;

      if(FIR_MODE == sweepMode) daddedfreq = 0.;
      else
      {
          daddedfreq = dStep * 0.5;
          if(globalUserVariable->comNum[0].segmentDataNum <= 1)
          {
              globalUserVariable->comNum[0].segmentDataNum = 1;
              //daddedfreq = globalUserVariable->gSpanFreq * 0.5;
          }
      }

      msumfftsweepoints += globalUserVariable->comNum[0].segmentDataNum;
      globalUserVariable->segmentsDataSumNum += (globalUserVariable->comNum[0].segmentDataNum * onetomulti);
      /*calc the freq div value of every segment start freq*/
      GetFreqDivValue(globalUserVariable->gStartFreq,daddedfreq,&globalUserVariable->comNum[0].seglostartfreqinter,&globalUserVariable->comNum[0].seglostartfreqfrac);
      //by steve 0418
      GetStepFrqDivValue(globalUserVariable->gStartFreq,dStep,&globalUserVariable->comNum[0].seglosteplow,&globalUserVariable->comNum[0].seglostephigh);
      globalUserVariable->comNum[0].persegsweeptimes = globalUserVariable->comNum[0].segmentDataNum * tempsingsweeptime + dSteptime;
  }

  //0716  steve calc per and sum segments data nums
  if(FIR_MODE == sweepMode)
  {
      globalUserVariable->sumSweeptime = globalUserVariable->segmentsDataSumNum  * tempsingsweeptime + globalUserVariable->segmentNum * 0.002;
      globalUserVariable->gautoMintimems += globalUserVariable->sumSweeptime;

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
              globalUserVariable->sumSweeptime = globalUserVariable -> gmanSettimems - globalUserVariable->segmentNum * interRuptCommutimems;
          }
          gsweepflag = 1;
          SettingSweepTimeManmode(globalUserVariable -> gmanSettimems,globalUserVariable->gautoMintimems);
          gsweepflag = 0;
      }
      else
      {
          globalUserVariable->gSweepTime = globalUserVariable->gautoMintimems;
      }
      globalUserVariable->firBucketimeus = globalUserVariable->sumSweeptime / globalUserVariable->gTracePoint;

      //*************Johnson 190611
      globalUserVariable->gcheckswitch = 0;//0 check and not insert,1 direct and insert,2 check and insert
  }
  else
  {
      globalUserVariable->sumSweeptime = msumfftsweepoints  * tempsingsweeptime + globalUserVariable->segmentNum * 0.002;
      globalUserVariable->gautoMintimems += globalUserVariable->sumSweeptime;
      globalUserVariable->gSweepTime = globalUserVariable->gautoMintimems;
      globalUserVariable->fftBucketnum = 0.1 * 10 * globalUserVariable->segmentsDataSumNum / globalUserVariable->gTracePoint;

      //0903 by steve<1>check and extract and insert<2>uncheck and extract and insert<uncheck and not extract and insert>
      if(globalUserVariable->segmentsDataSumNum < globalUserVariable->gTracePoint ||
              ((dspantostep < 1.0 - 1.0e-6)/* || (globalUserVariable->segmentsDataSumNum * dspantostep < globalUserVariable->gTracePoint)*/))
      {
          //0905
//          SA_sm_config_sweep->spanperstep = dspantostep;
          if(dspantostep < 1.0 + 1.0e-6)
          {
              //span in one channel and only one sweep point
              if(1 == globalUserVariable->segmentNum)
              {
                  //check and extract and insert
                  if(onetomulti > globalUserVariable->gTracePoint)
                  {
                      globalUserVariable->gcheckswitch = 2;
                      globalUserVariable->firstper = dspantostep;
                      globalUserVariable->secper = 0.;
                  }
                  //no check and extract and insert
                  else
                  {
                      globalUserVariable->gcheckswitch = 1;
                      globalUserVariable->firstper = dspantostep;
                      globalUserVariable->secper = 0.;
                  }
              }
              //span in more than one channel
              //and in this situation just two channel
              else
              {
                  if((onetomulti << 1) > globalUserVariable->gTracePoint)
                  {
                      globalUserVariable->gcheckswitch = 2;
                  }
                  else
                  {
                      globalUserVariable->gcheckswitch = 1;
                  }
                  globalUserVariable->firstper = (freqChannelList[globalUserVariable->comNum[0].segmentIndex] - globalUserVariable->gStartFreq) / dStep;
                  globalUserVariable->secper = (globalUserVariable->gStopFreq - freqChannelList[globalUserVariable->comNum[0].segmentIndex]) / dStep;
              }
          }
          //means datanum smaller than trace num
          else
          {
              globalUserVariable->gcheckswitch = 1;
              if(1 == globalUserVariable->segmentNum)
              {
                  //just calc last point percent
                  globalUserVariable->firstper = globalUserVariable->gSpanFreq / dStep - (qint32)(globalUserVariable->gSpanFreq / dStep);
                  globalUserVariable->secper = 0.;
              }
              else
              {
                  //calc separate and last percent
                  globalUserVariable->firstper = (freqChannelList[globalUserVariable->comNum[0].segmentIndex] - globalUserVariable->gStartFreq) / dStep -
                          (qint32)((freqChannelList[globalUserVariable->comNum[0].segmentIndex] - globalUserVariable->gStartFreq) / dStep);
                  globalUserVariable->secper = (globalUserVariable->gStopFreq - freqChannelList[globalUserVariable->comNum[0].segmentIndex]) / dStep -
                          (qint32)((globalUserVariable->gStopFreq - freqChannelList[globalUserVariable->comNum[0].segmentIndex]) / dStep);
              }
          }
      }
      else
      {
          globalUserVariable->gcheckswitch = 0;//0 check and not insert,1 direct and insert,2 check and insert
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
  //0828
  freqHz += dffthalfstepHz;
  qreal temp = (freqHz + lodivList[iIndex].iffreq) / REF_CLOCK * lodivList[iIndex].d * lodivList[iIndex].r / lodivList[iIndex].feedback;

  *intdiv = (quint32)temp;
  //Steve,0309
  quint64 tempfrac = (quint64)ceil((temp - *intdiv) * 4 * (1 << 16) * (1 << 30));
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
  qreal temp = stepHz / REF_CLOCK * lodivList[iIndex].d * lodivList[iIndex].r / lodivList[iIndex].feedback;
  quint64 tempfrac = (quint64)(temp * (1 << 24) * (1 << 24));
  *lowbits = tempfrac & 0xffffffff;
  *highbits = (tempfrac >> 32) & 0xffff;
  return;
}

void alothforsa::GetLastPartTime(qint32 iIndex)
{
  globalUserVariable->seglokeeptime = (quint32)(dealTimeList[iIndex] / fstimens);
  return;
}


/***************extern interface**********/
qint32 alothforsa::ConfigureFrequencyStartStop (qreal startFrequency,qreal stopFrequency)
{
  //0713 clear
  globalUserVariable->gautoMintimems = 0.0;

  //get segment index   globalUserVariable->ganamode
  GetSegmentWaveIndex(0);

  //0713
  globalUserVariable->gautoMintimems += globalUserVariable->segmentNum * interRuptCommutimems;

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
      if(FIR_MODE == globalUserVariable->ganamode)
      {
          globalUserVariable->loStepHz = globalUserVariable->gRbw * firStep;
      }
  }
  //calculate params by sweep mode
  RefCalSweepParams(globalUserVariable->ganamode);
  return 0;
}

//0716 this interface only used in fir mode,in man sweep time mode
void alothforsa::SettingSweepTimeManmode(qreal sweeptimems,qreal autotimems)
{
  qint32 iflag = 0;
  if(sweeptimems <= autotimems)
  {
      iflag = 1;
      sweeptimems = autotimems;
  }
  //firstly calc persegment points num and sum points num
  //if(sweeptimems > autotimems)
  {
      globalUserVariable->segmentsDataSumNum = 0;
      quint32 i = 0;
      qint32 iSize = globalUserVariable->segmentNum - 1;
      //means call setting sweep time direct
      if(!gsweepflag)
      {
          //recover loStepHz
          globalUserVariable->loStepHz = globalUserVariable->gRbw * firStep;
      }
      qreal dStep = globalUserVariable->loStepHz;

      if(globalUserVariable->segmentNum > 1)
      {
          qreal dfreqspan = freqChannelList[globalUserVariable->comNum[0].segmentIndex] - globalUserVariable->gStartFreq;
          //first seg points num
          globalUserVariable->comNum[0].segmentDataNum = (quint32)(ceil(dfreqspan / dStep));
          globalUserVariable->comNum[0].segmentDataNum = globalUserVariable->comNum[0].segmentDataNum == 0 ? 1 : globalUserVariable->comNum[0].segmentDataNum;
          globalUserVariable->segmentsDataSumNum += globalUserVariable->comNum[0].segmentDataNum;
          for(i = 1; i < globalUserVariable->segmentNum - 1; i++)
          {
              dfreqspan = freqChannelList[globalUserVariable->comNum[i].segmentIndex] - freqChannelList[globalUserVariable->comNum[i - 1].segmentIndex];
              globalUserVariable->comNum[i].segmentDataNum = (quint32)(ceil(dfreqspan / dStep));
              globalUserVariable->comNum[i].segmentDataNum = globalUserVariable->comNum[i].segmentDataNum == 0 ? 1 : globalUserVariable->comNum[i].segmentDataNum;
              globalUserVariable->segmentsDataSumNum += globalUserVariable->comNum[i].segmentDataNum;
          }

          dfreqspan = globalUserVariable->gStopFreq - freqChannelList[globalUserVariable->comNum[iSize].segmentIndex - 1];

          globalUserVariable->comNum[iSize].segmentDataNum = (quint32)(ceil(dfreqspan / dStep));
          globalUserVariable->comNum[iSize].segmentDataNum = globalUserVariable->comNum[iSize].segmentDataNum == 0 ? 1 : globalUserVariable->comNum[iSize].segmentDataNum;
          globalUserVariable->segmentsDataSumNum += globalUserVariable->comNum[iSize].segmentDataNum;
      }
      //only one segment
      else
      {
          //calc every segment points
          globalUserVariable->comNum[0].segmentDataNum = (quint32)(ceil(globalUserVariable->gSpanFreq / dStep));
          globalUserVariable->comNum[0].segmentDataNum = globalUserVariable->comNum[0].segmentDataNum == 0 ? 1 : globalUserVariable->comNum[0].segmentDataNum;
          globalUserVariable->segmentsDataSumNum += globalUserVariable->comNum[0].segmentDataNum;
      }

      //sum sweep points num by sweeptimems
      qint32 inowsumnum = (sweeptimems - globalUserVariable->segmentNum * (0.002 + interRuptCommutimems)) / globalUserVariable -> gfirsingletimems;
      sweeptimems = inowsumnum * globalUserVariable -> gfirsingletimems + globalUserVariable->segmentNum * (0.002 + interRuptCommutimems);

      if(1 == iflag)
      {
          globalUserVariable->loStepHz = globalUserVariable->gRbw * firStep;
      }
      else
      {
          globalUserVariable->loStepHz = (qreal)globalUserVariable->gSpanFreq / (inowsumnum - 1);
      }
      dStep = globalUserVariable->loStepHz;

      if(globalUserVariable->segmentNum > 1)
      {
          globalUserVariable->comNum[0].segmentDataNum = (qreal)globalUserVariable->comNum[0].segmentDataNum / globalUserVariable->segmentsDataSumNum * inowsumnum + 0.5;
          globalUserVariable->comNum[0].segmentDataNum = globalUserVariable->comNum[0].segmentDataNum == 0 ? 1 : globalUserVariable->comNum[0].segmentDataNum;
          globalUserVariable->comNum[0].persegsweeptimes = globalUserVariable->comNum[0].segmentDataNum * globalUserVariable -> gfirsingletimems + 0.002;
          //calc the freq div value of every segment start freq
          GetFreqDivValue(globalUserVariable->gStartFreq,0.0,&globalUserVariable->comNum[0].seglostartfreqinter,&globalUserVariable->comNum[0].seglostartfreqfrac);
          GetStepFrqDivValue(globalUserVariable->gStartFreq,dStep,&globalUserVariable->comNum[0].seglosteplow,&globalUserVariable->comNum[0].seglostephigh);

          for(i = 1; i < globalUserVariable->segmentNum - 1; i++)
          {
              globalUserVariable->comNum[i].segmentDataNum = (qreal)globalUserVariable->comNum[i].segmentDataNum / globalUserVariable->segmentsDataSumNum * inowsumnum + 0.5;
              globalUserVariable->comNum[i].segmentDataNum = globalUserVariable->comNum[i].segmentDataNum == 0 ? 1 : globalUserVariable->comNum[i].segmentDataNum;
              globalUserVariable->comNum[i].persegsweeptimes = globalUserVariable->comNum[i].segmentDataNum * globalUserVariable -> gfirsingletimems + 0.002;

              GetFreqDivValue(freqChannelList[globalUserVariable->comNum[i].segmentIndex - 1],0.0,&globalUserVariable->comNum[i].seglostartfreqinter,&globalUserVariable->comNum[i].seglostartfreqfrac);
              GetStepFrqDivValue(freqChannelList[globalUserVariable->comNum[i].segmentIndex - 1],dStep,&globalUserVariable->comNum[i].seglosteplow,&globalUserVariable->comNum[i].seglostephigh);

          }
          globalUserVariable->comNum[iSize].segmentDataNum = (qreal)globalUserVariable->comNum[iSize].segmentDataNum / globalUserVariable->segmentsDataSumNum * inowsumnum + 0.5;
          globalUserVariable->comNum[iSize].segmentDataNum = globalUserVariable->comNum[iSize].segmentDataNum == 0 ? 1 : globalUserVariable->comNum[iSize].segmentDataNum;
          globalUserVariable->comNum[iSize].persegsweeptimes = globalUserVariable->comNum[iSize].segmentDataNum * globalUserVariable -> gfirsingletimems + 0.002;

          GetFreqDivValue(freqChannelList[globalUserVariable->comNum[iSize].segmentIndex - 1],0.0,&globalUserVariable->comNum[iSize].seglostartfreqinter,&globalUserVariable->comNum[iSize].seglostartfreqfrac);
          GetStepFrqDivValue(freqChannelList[globalUserVariable->comNum[iSize].segmentIndex - 1],dStep,&globalUserVariable->comNum[iSize].seglosteplow,&globalUserVariable->comNum[iSize].seglostephigh);
      }
      else
      {
          globalUserVariable->comNum[0].segmentDataNum = (qreal)globalUserVariable->comNum[0].segmentDataNum / globalUserVariable->segmentsDataSumNum * inowsumnum + 0.5;
          globalUserVariable->comNum[0].segmentDataNum = globalUserVariable->comNum[0].segmentDataNum == 0 ? 1 : globalUserVariable->comNum[0].segmentDataNum;
          globalUserVariable->comNum[0].persegsweeptimes = globalUserVariable->comNum[0].segmentDataNum * globalUserVariable -> gfirsingletimems + 0.002;
          GetFreqDivValue(globalUserVariable->gStartFreq,0.0,&globalUserVariable->comNum[0].seglostartfreqinter,&globalUserVariable->comNum[0].seglostartfreqfrac);
          GetStepFrqDivValue(globalUserVariable->gStartFreq,dStep,&globalUserVariable->comNum[0].seglosteplow,&globalUserVariable->comNum[0].seglostephigh);
      }
      globalUserVariable->sumSweeptime = sweeptimems - globalUserVariable->segmentNum * interRuptCommutimems;

      if(!gsweepflag)
      {
          globalUserVariable->firBucketimeus = globalUserVariable->sumSweeptime / globalUserVariable->gTracePoint;
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
  globalUserVariable->sumSweeptime = timems;
  globalUserVariable->firBucketimeus = globalUserVariable->sumSweeptime / tracenum;
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
  if(globalUserVariable->gAutoRbw /*&& 3 != globalUserVariable->ganamode*/)
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
          iIndex = iIndex == 0 ? 1 : iIndex;
          qint32 ilastIndex = GetrbwIndex(globalUserVariable->gVbw);
          ilastIndex = ilastIndex == 0 ? : ilastIndex;
          SA_autoChangevbwflag = 0;
          if(iIndex != ilastIndex)
          {
              SA_autoChangevbwflag = 1;
          }
          globalUserVariable->gVbw =(quint32)rbwList[iIndex];
          //globalUserVariable->gVbw = (quint32)((qint32)rbwList[iIndex] * globalUserVariable->gVbwtoRbw);
      }
      else
      {
          qint32 vbwIndex = GetrbwIndex(videoBandwidth);
          vbwIndex = vbwIndex == 0?1:vbwIndex;//Johnson 1123
          globalUserVariable->gVbw = (quint32)rbwList[vbwIndex];
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
          iIndex = iIndex == 0 ? 1 : iIndex;
          qint32 ilastIndex = GetrbwIndex(globalUserVariable->gVbw);
          ilastIndex = ilastIndex == 0 ? : ilastIndex;
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
          vbwIndex = vbwIndex == 0?1:vbwIndex;//Johnson 1123
          globalUserVariable->gVbw = (quint32)rbwList[vbwIndex];
      }

      ParamConvertByRbw(rbwIndex);
  }

  if(!rbwTrigDoor && rbwFlag)
  {
      //0713
      globalUserVariable->gautoMintimems = 0.0;
      //0713
      globalUserVariable->gautoMintimems += globalUserVariable->segmentNum * interRuptCommutimems;

      //recalc time
      RefCalSweepParams(globalUserVariable->ganamode);
  }
  return 0;
}

void alothforsa::ParamConvertByRbw(qint32 iIndex)
{
  qint32 tempIndex = 0;
  //get the sweep mode of FIR
  if(iIndex <= 6)
  {
      globalUserVariable->ganamode = FIR_MODE;
      globalUserVariable->ganamode = globalUserVariable->ganamode;
      //calc lo step
      globalUserVariable->loStepHz = globalUserVariable->gRbw * firStep;
  }
  else//FFT mode
  {
      tempIndex = GetFftRbwIndex();
      globalUserVariable->ganamode = FFT_MODE;
      globalUserVariable->ganamode = globalUserVariable->ganamode;
      //calc lo step
      globalUserVariable->loStepHz = chparamlist[tempIndex].stepFreqHz;
      globalUserVariable->startIndex = chparamlist[tempIndex].fftNum * (1 - chparamlist[tempIndex].validRatio) * 0.5;

      //0828
      globalUserVariable->stopIndex = chparamlist[tempIndex].fftNum * (1 - (1 - chparamlist[tempIndex].validRatio) * 0.5);
      globalUserVariable->fftNum = globalUserVariable->stopIndex - globalUserVariable->startIndex + 1;
  }
  return;
}

qreal alothforsa::caculateFreqCount(qreal centerFreq,qint32 fsr,quint32 rbwValue)
{
    quint32 rbwIndex = GetrbwIndex((qreal)rbwValue);
    qreal qFreqCount = centerFreq + fsr / pow(2.,33.) * (FFREQ / frbw[rbwIndex]);

    return qFreqCount;
}
