#include "rtsa_user_variable.h"
#include "rtsa_shared_memory.h"
//#include "define.h"
#include "rtsa_define.h"
#include <QDebug>
#include <QPixmap>
#include <QDir>
#include <QApplication>
#include <QDesktopWidget>
#include "rtsa_extern.h"
#include <qmath.h>
#include "dpxMem.h"
#include "msgNoticeCode.h"
//RtSa_User_Variable MainUserVariable;
// Using what is defined in SharedMemory.h
extern _CONFIG_RSA_CTRL *sm_rtsa_config_rsa_ctrl;
extern _RTSA_SWEEP_DATA *sm_rtsa_sweep_data;
extern bool RTSA_DpxRefreshFlag;
extern pthread_mutex_t RTSA_lockobj;
//extern _RTSA_CONFIG_SYSTEM *sm_rtsa_config_system;

qint32 RbwVbwCompare(const void *a, const void *b)
{

  if (*(quint32 *)a > *(quint32 *)b)
    return 1;
  else if (*(quint32 *)a == *(quint32 *)b)
    return 0;
  else // if (*(quint32 *)a < *(quint32 *)b)
    return -1;

}

RtSa_User_Variable::RtSa_User_Variable(QObject *parent)
    : QObject(parent)
{
    InitVariableDefaultVal();
}
RtSa_User_Variable::~RtSa_User_Variable()
{
}
void RtSa_User_Variable::InitVariableDefaultVal()
{
//    gPeakTrack = RTSA_ON;
//    gSharedMemoryInit = 0;
//    inputCloseStyle = 0;
//    gsweepAuto = 1;
    gautoMintimems = 100.0;
//    gmanSettimems = 100.0;
//    gfirsingletimems = 0.002;
//    ganamode = 3;
    gMenu = RTSA_MENU_SPECTRUM_ANALYZER;
//    blRefresh = RTSA_OFF;
    entryInputMode = RTSA_NOT_USE;
    gMeasurement = -1;
//    gMeasurement = RTSA_MEAS_OFF;
//    gDemodulationType = RTSA_AM;
    gSweepTracePoint = RTSA_NUM_SWEEP_POINT;//501;
//    gTracePoint = RTSA_NUM_SWEEP_POINT;//POINT_501;
//    gTraceStepSize = (double)RTSA_GRID_WIDTH/(double)(gSweepTracePoint - 1);
    gStartFreq = 5000000000LL;
    gStopFreq =  5100000000LL;
    gCenterFreq = 5050000000LL;
    gCFFreq = 1000000LL;
    gSpanFreq = 100000000LL;
    gStepFreq =  (gStopFreq - gStartFreq)/(gSweepTracePoint - 1);
    gSpanMode = RTSA_NORMAL_SPAN;
    gfreqOffset = 0.;
    gRefLevel = -10.;
    gRefOffset = 0.;
    gScaleDiv = 10.;
    gAmptdUnit = RTSA_DBM;
    gAtten = RTSA_AUTO;
    gPreamp = RTSA_OFF;
//    gOverlap = 0;
//    memset(&density_Trace1,0,sizeof(density_Trace1));
//    memset(&density_Trace2,0,sizeof(density_Trace2));
//    memset(&density_Trace3,0,sizeof(density_Trace3));
//    memset(&hitCount_Trace1,0,sizeof(hitCount_Trace1));
//    memset(&hitCount_Trace2,0,sizeof(hitCount_Trace2));
//    memset(&hitCount_Trace3,0,sizeof(hitCount_Trace3));
//    totalCount1 = 0;
//    totalCount2 = 0;
//    totalCount3 = 0;
//    gVbwtoRbw = RTSA_ON;
//    gAutoVbwtoRbw = 1;
    gspanChangebyFreq = 0;
    gbitsspan = RTSA_SPAN_MIN;
    gbithalfsspan = RTSA_SPAN_MIN / 2;
    grbwChangedbyFreq = 0;
//    inputDialogOpenflag = 0;//1 open,means keypad input is ok
//    amptDialogOpenflag = 0;
    gAutoPersistenceTime = RTSA_FINITE;
    gAutoAcqTime=RTSA_AUTO;
    gMaskType = RTSA_UPPER;
//    gMarkerCount = RTSA_ON;
    gFTTWindows = RTSA_KAISER;
    gAcqTime = RTSA_ACQ_DEFAULT_TIME ;//Tony 0905
    gPersistenceTime = RTSA_PERSISTENCE_TIME;  //Tony 0905
    gSleepTime=RTSA_REFRESH_DEFAULT_TIME;//Tony 0912
    gHighestDensity = 100;
    gLowestDensity = 0;
    gCurve=0;
    gAutoAttenTrack = RTSA_MANUAL;
    gAutoRbw = RTSA_ON;
    gAutoVbw = RTSA_ON;
//    gAutoSweepTime = RTSA_ON;
    gRbwIndex = RTSA_RBW5;
//    gRbw = RTSA_RbwManualList[0][0][5];
    gRbwGrade = RTSA_SPAN_INTERVAL_NUMBER - 1;
    gRbw = RTSA_RbwManualList[gFTTWindows][gRbwGrade][gRbwIndex];
    gVbw = 3000000;
    gDetectorMode = RTSA_DEC_PEAK;
    gSweepType = RTSA_CONT;
//    gSweepTime = 100.;
    gAttenValue = 0.;
//    gAttenSelect = 2; // [0] 0  [1] 5 [2] 10  [3] 15  [4] 20  [5] 25  [6] 30
//    gExtTrigger = RTSA_OFF;
    gTriggerMode = RTSA_TRIGGER_FREE_RUN + 1;
    gTriggerVideoSlope = 0;
    gTriggerExternSlope = 0;
    gTriggerRFBurstSlope = 0;
    gTriggerSlope = 0;
    gVideoTrigLevel = -20.0;
    gExternTrigLevel = -20.0;
    gRFBurstTrigLevel = -20.0;
    gVideoTrigDelayStatus = 0;
    gExternTrigDelayStatus = 0;
    gRFBurstTrigDelayStatus = 0;
    gPeriodTrigDelayStatus = 0;
    gVideoTrigDelay = 0;
    gExternTrigDelay = 0;
    gRFBurstTrigDelay = 0;
    gPeriodTrigDelay = 0;
    gPeriodTrigTime = RTSA_HOLDOFF_TIME_MIN;
    gVideoHoldOff = 30000;
    gRFBurstHoldOff = 30000;
    gExternHoldOff = 30000;
    gFMTHoldOff = 30000;
//    gImageRejection = RTSA_OFF;
//    memset(&gDpxData,0,sizeof(gDpxData));
//    memset(&gOriginalMeasureVal,0,sizeof(gOriginalMeasureVal));
//    memset(&gBitTraceAverage,0,sizeof(gBitTraceAverage));
//    memset(&gTraceMeasureVal,0,sizeof(gTraceMeasureVal));
//    gSpanStepPos = 0;
    gLastSpanFreq =  4000000000LL;
//    gMarkerSelect  = M1;
//    gVolume = 50;
    gDisplayMode = 0;
    gPowersensorFreq = 1000000000LL;
    gPowersensorExtOffset = 0.0;
//    bShiftKeyPressed = false;
    KeyNumber        = -1;
    gCHIndex = -1;
    gTecIndex = -1;
    gCHName = new QVector <QString>;
    gCHStandard = new QVector <__RTSA_Standard__>;
    gFreqStandard = new QVector <__RTSA_Standard__>;
    gCommuDirection = RTSA_UPLINK;
    getBandInfo(gTecIndex);
    adjustCHStandarByCerFreq(gCenterFreq);
    gLocal = RTSA_LOCAL;
    gdpxApmtMin = -110.0;
    gdpxAmptZoom = 2.0;
    DpxHandle = -1;
    gDpxOpenFlag = false;
    memset(&gFmtData,0,sizeof(gFmtData));
    startMode = -1;
//    startPreset = 0;
    gfmtType = 0;
    gfileType = -1;
    gRefreshAllParam = false;
    gSuspendDrawFlag = false;
    gFmtTriggerCriterion = 0;
}
qint32 RtSa_User_Variable::notZeroPositionFindFunc(QString strGab)
{
 qint32 strLen = 0;
 qint32 pos = 30;
  char str1[21] = {'\0',};
 qint32 i = 0;

  strLen = strGab.length();
  qsnprintf(str1, sizeof(str1), "%s", strGab.toUtf8().constData());

  for (i = (strLen - 1); i >= 0; i--)
    {
      if (str1[i] != '0') {
          pos = i;
          break;
        }
    }

  return pos;
}

//QString RtSa_User_Variable::freqDotNumberDisplayFormatFixFunc(qreal freqVal, qint32 unitNo, qint32 numberLen)
//{
//  QString strValue;
//  QString retStrValue;
//  double unitGab = 0.;
//  QString unitStr;


//  // numberLen  => 소숫점 뒤 0이 아닌 길이
//  switch (unitNo) {
//    case UNIT_GHZ:
//      unitGab = (double) RTSA_GHZ;
//      unitStr = QString("GHz");

//      switch (numberLen) {
//        case 0:
//        case 1:
//        case 2:
//          strValue.sprintf("%.2f", (double) freqVal / unitGab);
//          break;
//        case 3:
//          strValue.sprintf("%.3f", (double) freqVal / unitGab);
//          break;
//        case 4:
//          strValue.sprintf("%.4f", (double) freqVal / unitGab);
//          break;
//        case 5:
//          strValue.sprintf("%.5f", (double) freqVal / unitGab);
//          break;
//        case 6:
//          strValue.sprintf("%.6f", (double) freqVal / unitGab);
//          break;
//        case 7:
//          strValue.sprintf("%.7f", (double) freqVal / unitGab);
//          break;
//        case 8:
//          strValue.sprintf("%.8f", (double) freqVal / unitGab);
//          break;
//        case 9:
//          strValue.sprintf("%.9f", (double) freqVal / unitGab);
//          break;
//        default:
//          strValue.sprintf("%.2f", (double) freqVal / unitGab);
//          break;
//        }
//      break;
//    case UNIT_MHZ:
//      unitGab = (double) RTSA_MHZ;
//      unitStr = QString("MHz");

//      switch (numberLen) {
//        case 0:
//        case 1:
//        case 2:
//          strValue.sprintf("%.2f", (double) freqVal / unitGab);
//          break;
//        case 3:
//          strValue.sprintf("%.3f", (double) freqVal / unitGab);
//          break;
//        case 4:
//          strValue.sprintf("%.4f", (double) freqVal / unitGab);
//          break;
//        case 5:
//          strValue.sprintf("%.5f", (double) freqVal / unitGab);
//          break;
//        case 6:
//          strValue.sprintf("%.6f", (double) freqVal / unitGab);
//          break;
//        default:
//          strValue.sprintf("%.2f", (double) freqVal / unitGab);
//          break;
//        }

//      break;
//    case UNIT_KHZ:
//      unitGab = (double) RTSA_KHZ;
//      unitStr = QString("kHz");

//      switch (numberLen) {
//        case 0:
//        case 1:
//        case 2:
//          strValue.sprintf("%.2f", (double) freqVal / unitGab);
//          break;
//        case 3:
//          strValue.sprintf("%.3f", (double) freqVal / unitGab);
//          break;
//        default:
//          strValue.sprintf("%.2f", (double) freqVal / unitGab);
//          break;
//        }
//      break;
//    case UNIT_HZ:
//      unitGab = (double) RTSA_HZ;
//      unitStr = QString("Hz");
//      strValue.sprintf("%.2f", (double) freqVal / unitGab);
//      break;
//    }


//  retStrValue = QString("%1 %2").arg(strValue).arg(unitStr);

//  return retStrValue;

//}

//QString RtSa_User_Variable::timeDotNumberDisplayFormatFixFunc(double _timeVal, qint32 unitNo, qint32 numberLen)
//{
//  QString strValue;
//  QString retStrValue;
//  double unitGab = 0.;
//  QString unitStr;

//  //numberLen  => 소숫점 뒤 0이 아닌 길이
//  //Tony 0911
//  switch (unitNo) {
//    case UNIT_NS:
//      unitGab = (double) RTSA_NS;
//      unitStr = QString("ns");

//      strValue.sprintf("%.3f", (double) _timeVal * unitGab);
//      break;
//    case UNIT_US:
//      unitGab = (double) RTSA_US;
//      unitStr = QString("us");

//      strValue.sprintf("%.3f", (double) _timeVal / unitGab);
//      break;
//    case UNIT_MS:
//      //0713
//      if(_timeVal >= RTSA_S)
//        {
//          unitStr = QString("s");
//          strValue.sprintf("%.3f",_timeVal/RTSA_S);
//        }
//      else
//        {
//           unitStr = QString("ms");
//           strValue.sprintf("%.3f", (double) _timeVal/RTSA_MS);
//        }
//      break;
//    case UNIT_S:
//      unitStr = QString("s");

//      switch (numberLen) {
//        case 0:
//          strValue.sprintf("%.3f",  _timeVal/RTSA_S );
//          break;
//        case 1:
//          strValue.sprintf("%.3f",  _timeVal/RTSA_S);
//          break;
//        case 2:
//        default:
//          strValue.sprintf("%.3f",  _timeVal/RTSA_S);
//          break;
//        }
//      break;
//    }

//  retStrValue = QString("%1 %2").arg(strValue).arg(unitStr);
//  return retStrValue;

//}
#if 0
qint32 RtSa_User_Variable::timeUnitFindProc(double _time)
{
  if (_time >= KS)
    return UNIT_KS;
  else if (_time >= S)
    return UNIT_S;
  else if (_time >= MS)
    return UNIT_MS;
  else if (_time >= US)
    return UNIT_US;
  else
    return UNIT_NS;
}
#endif

qint32 RtSa_User_Variable::freqUnitFindProc(qreal _freq)
{
  if (_freq >= RTSA_GHZ)
    return UNIT_GHZ;
  else if (_freq >= RTSA_MHZ)
    return UNIT_MHZ;
  else if (_freq >= RTSA_KHZ)
    return UNIT_KHZ;
  else
    return UNIT_HZ;
}
//Tony 0911
//qint32 RtSa_User_Variable::timeUnitFindProc(double _time)
//{
//  if (_time >= RTSA_S)
//    return UNIT_S;
//  else if (_time >= RTSA_MS)
//    return UNIT_MS;
//  else if (_time >= RTSA_US)
//    return UNIT_US;
//  else
//    return UNIT_NS;
//}

//Tony 0907
qreal RtSa_User_Variable::adjustSpanBySpan(qreal freq)
{
    for(qint32 index = 0;index<RTSA_SPAN_INTERVAL_NUMBER;index++)
    {
        if(index == 0)
        {
            if(freq >= 0 && freq<=RTSA_SPAN_STEP_VALUE[index])
            {
                freq = RTSA_SPAN_STEP_VALUE[index];
                gRbwGrade=index;
                adjustRbwBySpan(freq);
                return freq;
            }
        }else
        {
            if(freq>RTSA_SPAN_STEP_VALUE[index-1] && freq<=RTSA_SPAN_STEP_VALUE[index])
            {
                freq = RTSA_SPAN_STEP_VALUE[index];
                gRbwGrade=index;
                adjustRbwBySpan(freq);
                return freq;
            }
        }
    }

    if(freq >= RTSA_SPAN_STEP_VALUE[RTSA_SPAN_INTERVAL_NUMBER-1])
    {
        freq = RTSA_SPAN_STEP_VALUE[RTSA_SPAN_INTERVAL_NUMBER-1];
        gRbwGrade=RTSA_SPAN_INTERVAL_NUMBER-1;
        adjustRbwBySpan(freq);
        return freq;
    }
    return 0;
}

//Tony 0910
qreal RtSa_User_Variable::adjustSpanToSmall(qreal freq)
{

    for(qint32 index = 2;index<RTSA_SPAN_INTERVAL_NUMBER;index++)
    {
        if(index == 2)
        {
            if(freq>=0 && freq<=RTSA_SPAN_STEP_VALUE[index])
            {
                freq = RTSA_SPAN_STEP_VALUE[index];
                gRbwGrade=index;
                adjustRbwBySpan(freq);
                return freq;
            }
        }else
        {
            if(freq>=RTSA_SPAN_STEP_VALUE[index-1] && freq<RTSA_SPAN_STEP_VALUE[index])
            {
                freq = RTSA_SPAN_STEP_VALUE[index-1];
                gRbwGrade=index-1;
                adjustRbwBySpan(freq);
                return freq;
            }
        }

    }
    if(freq >= RTSA_SPAN_STEP_VALUE[RTSA_SPAN_INTERVAL_NUMBER-1])
    {
        freq = RTSA_SPAN_STEP_VALUE[RTSA_SPAN_INTERVAL_NUMBER-1];
        gRbwGrade=RTSA_SPAN_INTERVAL_NUMBER-1;
        adjustRbwBySpan(freq);
        return freq;
    }
    return 0;
}


//Tony 0906
quint32 RtSa_User_Variable::adjustRbwBySpan(qreal freq)
{
//    quint32 gRbwtmp=0;
//   qint32 spanindex=0;
//   qint32 rbwindex=0;
//    for(int index=0;index<SPAN_INTERVAL_NUMBER;index++)
//    {
//        if(index==0 && freq<= SPAN_STEP_VALUE[index])
//        {
//            spanindex=index;
//            break;
//        }
//        else if(index == (SPAN_INTERVAL_NUMBER-1) && freq > SPAN_STEP_VALUE[index])
//        {
//            spanindex=index;
//            break;
//        }else
//        {
//            if(freq > SPAN_STEP_VALUE[index-1] && freq <= SPAN_STEP_VALUE[index])
//            {
//                spanindex=index;
//                break;
//            }
//        }
//    }
//    gRbwGrade=spanindex/3;
    gRbw=RTSA_RbwManualList[gFTTWindows][gRbwGrade][gRbwIndex];
    return gRbw;
}

qint32 RtSa_User_Variable::adjustFreqBySpan(qreal freq)
{
  //Tony 0907
  gLastSpanFreq =  gSpanFreq;
  gSpanFreq = freq;

  if(gCenterFreq - 0.5 * gSpanFreq < RTSA_SPEC_FREQ_MIN)
    {
      gStartFreq = RTSA_SPEC_FREQ_MIN;

      //Tony 0907
      //gSpanFreq = (gCenterFreq - SPEC_FREQ_MIN) * 2;
      //Tony 0907
      gCenterFreq = gStartFreq + 0.5*gSpanFreq;
      gStopFreq = gStartFreq + gSpanFreq;
    }
  else if(gCenterFreq + 0.5 * gSpanFreq > RTSA_SPEC_FREQ_MAX)
    {
      gStopFreq = RTSA_SPEC_FREQ_MAX;
//      gSpanFreq = (SPEC_FREQ_MAX - gCenterFreq) * 2;
      gCenterFreq = gStopFreq - 0.5*gSpanFreq;
      gStartFreq =  gStopFreq - gSpanFreq;
    }
  else
    {
      gStartFreq = gCenterFreq - 0.5 * gSpanFreq;
      gStopFreq = gCenterFreq + 0.5 * gSpanFreq;
    }
  return 1;
}

qint32 RtSa_User_Variable::adjustFreqByCer()
{
    if(gCenterFreq >= RTSA_SPEC_FREQ_MAX)
    {
        gLastSpanFreq = gSpanFreq;
        gspanChangebyFreq = 1;
        gStopFreq   = RTSA_SPEC_FREQ_MAX;

        gSpanFreq   = gbitsspan;
        gStartFreq  = gStopFreq  - gSpanFreq;
        gCenterFreq = gStartFreq + gbithalfsspan;
    }
    else if(gCenterFreq <= RTSA_SPEC_FREQ_MIN)
    {
        gLastSpanFreq =  gSpanFreq;
        gspanChangebyFreq = 1;
        gStartFreq  = RTSA_SPEC_FREQ_MIN;
        gStopFreq   = gStartFreq + gbitsspan;
        gSpanFreq   = gbitsspan;
        gCenterFreq = gStartFreq + gbithalfsspan;
    }
    else
    {
        if(gCenterFreq - 0.5 * gSpanFreq < RTSA_SPEC_FREQ_MIN)
        {
            //change start freq and span and stop freq
            //save last span
            gLastSpanFreq =  gSpanFreq;
            gspanChangebyFreq = 1;

            //Tony 0908
            gStartFreq = RTSA_SPEC_FREQ_MIN;
            gSpanFreq = (gCenterFreq - RTSA_SPEC_FREQ_MIN) * 2;
            gSpanFreq = adjustSpanToSmall(gSpanFreq);
            gCenterFreq=gStartFreq+0.5*gSpanFreq;
            gStopFreq = gStartFreq+gSpanFreq;

            //Tony 0908 removed
            //          gStartFreq = SPEC_FREQ_MIN;
            //          gSpanFreq = (gCenterFreq - SPEC_FREQ_MIN) * 2;
            //          gStopFreq = gStartFreq + gSpanFreq;
        }
        else if(gCenterFreq + 0.5 * gSpanFreq > RTSA_SPEC_FREQ_MAX)
        {
            //change start freq and span and stop freq
            gLastSpanFreq =  gSpanFreq;
            gspanChangebyFreq = 1;
            gStopFreq = RTSA_SPEC_FREQ_MAX;
            gSpanFreq = (RTSA_SPEC_FREQ_MAX - gCenterFreq) * 2;
            //Tony 0910
            gSpanFreq =   adjustSpanToSmall(gSpanFreq);
            gCenterFreq=  gStopFreq - 0.5*gSpanFreq;
            gStartFreq =  gStopFreq - gSpanFreq;
        }
        else
        {
            //change start and stop freq
            gspanChangebyFreq = 0;
            gStartFreq = gCenterFreq - 0.5 * gSpanFreq;
            gStopFreq = gCenterFreq + 0.5 * gSpanFreq;
        }
    }
    return 1;
}

qint32 RtSa_User_Variable::adjustFreqByStart(void)
{
  //save last span
  gLastSpanFreq =  gSpanFreq;
  //Tony 0910
  gStartFreq = gStartFreq < RTSA_SPEC_FREQ_MIN ? RTSA_SPEC_FREQ_MIN : gStartFreq;

  //steve,0503 change > to >=
  if(gStartFreq >= gStopFreq)
    {
      gSpanFreq = gbitsspan;
      gStopFreq = gStartFreq + gbitsspan;
      if( gStopFreq > RTSA_SPEC_FREQ_MAX)
        {
          gStopFreq = RTSA_SPEC_FREQ_MAX;
          gStartFreq = gStopFreq - gbitsspan;
        }
      gCenterFreq = gStartFreq + gbithalfsspan;
    }
  else
    {
      //Tony 0910
      if(gStartFreq+gSpanFreq>RTSA_SPEC_FREQ_MAX)
      {
          if(gStartFreq+gbitsspan>RTSA_SPEC_FREQ_MAX)
          {
              gStopFreq  =  RTSA_SPEC_FREQ_MAX;
              gSpanFreq  =  gbitsspan;
              gCenterFreq = gStopFreq - 0.5 * gSpanFreq;
              gStartFreq  = gStopFreq - gSpanFreq;
          }else
          {
              gStopFreq  =  RTSA_SPEC_FREQ_MAX;
              gSpanFreq  =  gStopFreq - gStartFreq;
              gSpanFreq  =  adjustSpanToSmall(gSpanFreq);
              gCenterFreq = gStopFreq - 0.5 * gSpanFreq;
              gStartFreq  = gStopFreq - gSpanFreq;

          }
      }else
      {
          gSpanFreq  =  gStopFreq - gStartFreq;
          gSpanFreq  =  adjustSpanToSmall(gSpanFreq);
          gCenterFreq = gStartFreq + 0.5 * gSpanFreq;
          gStopFreq  = gStartFreq + gSpanFreq;
      }
      //Tony 0910
//      gStartFreq = gStartFreq < SPEC_FREQ_MIN ? SPEC_FREQ_MIN : gStartFreq;
//      gSpanFreq = gStopFreq - gStartFreq;
//      gCenterFreq = gStartFreq + 0.5 * gSpanFreq;
    }
  return 1;
}

qint32 RtSa_User_Variable::adjustFreqByStop(void)
{
  gLastSpanFreq =  gSpanFreq;
  gStopFreq = gStopFreq > RTSA_SPEC_FREQ_MAX ? RTSA_SPEC_FREQ_MAX : gStopFreq;
  //by steve,0503,change < to <=
  if(gStopFreq <= gStartFreq)
    {
      gSpanFreq = gbitsspan;
      gStartFreq = gStopFreq - gbitsspan;
      if( gStartFreq < RTSA_SPEC_FREQ_MIN)
        {
          gStartFreq = RTSA_SPEC_FREQ_MIN;
          gStopFreq = gStartFreq + gbitsspan;
        }
      gCenterFreq = gStartFreq + gbithalfsspan;
    }
  else
    {
      //Tony 0910
      if(gStopFreq-gSpanFreq<RTSA_SPEC_FREQ_MIN)
      {
          if(gStopFreq-gbitsspan<=RTSA_SPEC_FREQ_MIN)
          {
              gStartFreq  =  RTSA_SPEC_FREQ_MIN;
              gSpanFreq  =  gbitsspan;
              gCenterFreq = gStartFreq + 0.5 * gSpanFreq;
              gStopFreq  = gStartFreq + gSpanFreq;
          }else
          {
              gStartFreq  =  RTSA_SPEC_FREQ_MIN;
              gSpanFreq  =  gStopFreq - gStartFreq;
              gSpanFreq  =  adjustSpanToSmall(gSpanFreq);
              gCenterFreq = gStartFreq + 0.5 * gSpanFreq;
              gStopFreq  = gStartFreq + gSpanFreq;
          }
      }else
      {
          gSpanFreq  =  gStopFreq-gStartFreq;
          gSpanFreq  =  adjustSpanToSmall(gSpanFreq);
          gCenterFreq = gStopFreq - 0.5 * gSpanFreq;
          gStartFreq  = gStopFreq - gSpanFreq;
      }


      //Tony 0910
//      gStopFreq = gStopFreq > SPEC_FREQ_MAX ? SPEC_FREQ_MAX : gStopFreq;
//      gSpanFreq = gStopFreq - gStartFreq;
//      gCenterFreq = gStartFreq + 0.5 * gSpanFreq;
    }
  return 1;
}

qint32 RtSa_User_Variable::converFreqToShm(void)
{
  sm_rtsa_config_rsa_ctrl->CenterFreq = (qreal) gCenterFreq;
  sm_rtsa_config_rsa_ctrl->SpanFreq = (qreal) gSpanFreq;
  sm_rtsa_config_rsa_ctrl->StartFreq = (qreal) gStartFreq;
  sm_rtsa_config_rsa_ctrl->StopFreq = (qreal) gStopFreq;
  if(gAcqTime <= AcqTime_Min_List[gRbwGrade])
  {
      gAcqTime = AcqTime_Min_List[gRbwGrade];
  }
  else if(gAcqTime >= AcqTime_Max_List[gRbwGrade])
  {
      gAcqTime = AcqTime_Max_List[gRbwGrade];
  }
  sm_rtsa_config_rsa_ctrl->acqtimems = gAcqTime / RTSA_S;

  return 1;
}

//qint32 RtSa_User_Variable::convertBwToShm(void)
//{
//  sm_rtsa_config_rsa_ctrl->RBW = gRbwIndex;
//  sm_rtsa_config_rsa_ctrl->RBWAuto = gAutoRbw;
//  return 1;
//}

//void RtSa_User_Variable::converShmToGlobalVariable()
//{
////    gCenterFreq =
//    return;
//}

//qint32 RtSa_User_Variable::spanSettingCompareProcess(qreal freq)
//{
//  //changed by Steve,0228
//  //adjust param
//  //save last span

//  return adjustFreqBySpan(freq);
//}

void RtSa_User_Variable::stepFreqCalculatorFunc()
{
  qreal startFreq = gStartFreq;
  qreal stopFreq = gStopFreq;

  gStepFreq = (stopFreq - startFreq) / (gSweepTracePoint - 1);


}


//void RtSa_User_Variable::markerSettingInitFunc()
//{
// qint32 i = 0;
//  qreal calFreq = 0;
//  stepFreqCalculatorFunc();  //Step Frequency 계산
//  calFreq = gStepFreq * (qreal ) ((gSweepTracePoint - 1) / 2);

////  for (i = 0; i < MARKER_TOTAL_CNT; i++) {
////      gMarkerRefFreq[i] = gStartFreq +  calFreq ;
////      gMarkerDeltaFreq[i]= gMarkerRefFreq[i];
////      gMarkerRefPos[i] =  (int) (gSweepTracePoint / 2 );
////      gMarkerDeltaPos[i] = gMarkerRefPos[i];
////      gMarkerView[i] = OFF;
////      gMarkerType[i] = REF;
////    }
////  gMarkerDisplay = MKR_ONLY;
//}


//void RtSa_User_Variable::gridAxisCalculatorFunc()
//{
//// qint32 calGridVstep = 0;

////  if (gTraceType[gTraceSelect] != TRACE_OFF) {

////      qDebug() << "_____";
////      if (gMarkerDisplay == MKR_TABLE && guiDrawSet.markerOnCount != 0) {
////          //Johnson 0807 add
////          if(gMeasurement == CHANNEL_POWER || gMeasurement == ACP){
////              if(gMeasurement == CHANNEL_POWER)
////                  guiDrawSet.gridVerStep = (GRID_HEIGHT - (guiDrawSet.markerOnCount * MARKER_FONT_HEIGHT)-MARKER_FONT_HEIGHT) / GRID_NUM_Y_TICKS;
////              else
////                  guiDrawSet.gridVerStep = (GRID_HEIGHT - (guiDrawSet.markerOnCount * MARKER_FONT_HEIGHT)-MARKER_FONT_HEIGHT*3) / GRID_NUM_Y_TICKS;

////              for (qint32 i = 0; i < GRID_NUM_X_TICKS + 1; i++) {
////                  gridXPos[i] = GRID_START_X + guiDrawSet.gridHorStep * i;
////                  gridYPos[i] = GRID_START_Y + guiDrawSet.gridVerStep * i;
////                }
////          }
////          else{
////              calGridVstep = (GRID_HEIGHT - (guiDrawSet.markerOnCount * MARKER_FONT_HEIGHT)) / GRID_NUM_Y_TICKS;
////              guiDrawSet.gridVerStep = calGridVstep;

////              for (qint32 i = 0; i < GRID_NUM_X_TICKS + 1; i++) {
////                  gridXPos[i] = GRID_START_X + guiDrawSet.gridHorStep * i;
////                  gridYPos[i] = GRID_START_Y + calGridVstep * i;
////                }
////          }
////        } else {
////          //Johnson 0807 add
////          if(gMeasurement == CHANNEL_POWER || gMeasurement == ACP){
////              if(gMeasurement == CHANNEL_POWER) guiDrawSet.gridVerStep = (GRID_HEIGHT-MARKER_FONT_HEIGHT)/GRID_NUM_Y_TICKS;
////              else guiDrawSet.gridVerStep = (GRID_HEIGHT-MARKER_FONT_HEIGHT*3)/GRID_NUM_Y_TICKS;
////              for (qint32 i = 0; i < GRID_NUM_X_TICKS + 1; i++) {
////                  gridXPos[i] = GRID_START_X + guiDrawSet.gridHorStep * i;
////                  gridYPos[i] = GRID_START_Y + guiDrawSet.gridVerStep * i;
////                }
////          }
////          else{
////              guiDrawSet.gridVerStep = GRID_HEIGHT /  GRID_NUM_Y_TICKS;
////              for (qint32 i = 0; i < GRID_NUM_X_TICKS + 1; i++){
////                  gridXPos[i] = GRID_START_X + guiDrawSet.gridHorStep * i;
////                  gridYPos[i] = GRID_START_Y + guiDrawSet.gridVerStep * i;
////                }
////          }
////        }
////    } else {
////      //Johnson 0807 add
////      if(gMeasurement == CHANNEL_POWER || gMeasurement == ACP){
////          if(gMeasurement == CHANNEL_POWER) guiDrawSet.gridVerStep = (GRID_HEIGHT-MARKER_FONT_HEIGHT)/GRID_NUM_Y_TICKS;
////          else guiDrawSet.gridVerStep = (GRID_HEIGHT-MARKER_FONT_HEIGHT*3)/GRID_NUM_Y_TICKS;
////          for (qint32 i = 0; i < GRID_NUM_X_TICKS + 1; i++) {
////              gridXPos[i] = GRID_START_X + guiDrawSet.gridHorStep * i;
////              gridYPos[i] = GRID_START_Y + guiDrawSet.gridVerStep * i;
////            }
////      }
////      else{
////          guiDrawSet.gridVerStep = GRID_HEIGHT /  GRID_NUM_Y_TICKS;
////          for (qint32 i = 0; i < GRID_NUM_X_TICKS + 1; i++){
////              gridXPos[i] = GRID_START_X + guiDrawSet.gridHorStep * i;
////              gridYPos[i] = GRID_START_Y + guiDrawSet.gridVerStep * i;
////            }
////      }
////    }


//////  if (guiDrawSet.limitLineOnCount != 0) {
//////      memset(globalUserLimit->LimitLowerDrawPoint, 0, sizeof(int) * RTSA_NUM_SWEEP_POINT);
//////      memset(globalUserLimit->LimitUpperDrawPoint, 0, sizeof(int) * RTSA_NUM_SWEEP_POINT);

//////      globalUserLimit->limitLineYAxisCalculatorFunc();
//////      globalUserLimit->limitLineInterpolationCalculatorFunc();;
//////    }

//}

//void RtSa_User_Variable::centerFreqSettingFunc()
//{

//  //qreal startFreqInterval = 0;
//  //qreal stopFreqInterval = 0;

//  //atten,this part has problem,change by Steve,0228
//  //adjustFreqByCerAndSpan(gCenterFreq);
//#if 0
//  startFreqInterval = (gCenterFreq - gStartFreq);
//  stopFreqInterval = (gStopFreq - gCenterFreq);

//  if (startFreqInterval < stopFreqInterval) {
//      gSpanFreq = startFreqInterval * 2;
//      gStopFreq = gCenterFreq + startFreqInterval;
//    } else {
//      gSpanFreq = stopFreqInterval * 2;
//      gStartFreq = gCenterFreq - stopFreqInterval;
//    }

//  stepFreqCalculatorFunc();
//#endif
//  //gStepFreq = (gStopFreq - gStartFreq) / (gTracePoint - 1);

//  qDebug() << "[centerFreqSettingFunc] gStepFreq => " << gStepFreq;

//}

//void RtSa_User_Variable::markerEditInNputMarkerPosCalculatorFunc(qreal freq,qint32 InputType)
//{
// qint32 i = 0;
//  qreal calculatorFreq = 0;
//  qreal vigeoFreq = 0;
//  qreal markerFreq = 0;
//  qreal deltamarkerFreq = 0;

//  if (InputType == RTSA_REF) {
//      //Marker 주파수가 Start Freq 같음
//      if (freq == gStartFreq)  {
////          gMarkerRefFreq[gMarkerSelect] = gStartFreq;
////          gMarkerRefPos[gMarkerSelect] = 0;
//        } else if (freq == gStopFreq) {
////          gMarkerRefFreq[gMarkerSelect] = gStopFreq;
////          gMarkerRefPos[gMarkerSelect] = gSweepTracePoint - 1;
//        } else {

//          // Marker Edit Pos Cal
//          for (i = 0; i < (gSweepTracePoint + 1); i++)  {
//              calculatorFreq = gStepFreq * i;
//              vigeoFreq  = gStartFreq + calculatorFreq ;

//              if (vigeoFreq >= freq) {
////                  gMarkerRefPos[gMarkerSelect] = i;
////                  gMarkerRefFreq[gMarkerSelect] = freq;
//                  break;
//                }
//            }
//        }
//    } else {

//      //Marker 주파수가 Start Freq 같음
//      if (freq == gStartFreq)  {
////          gMarkerDeltaFreq[gMarkerSelect] = gStartFreq;
////          gMarkerDeltaPos[gMarkerSelect] = 0;
//        } else if (freq == gStopFreq) {
////          gMarkerDeltaFreq[gMarkerSelect] = gStopFreq;
////          gMarkerDeltaPos[gMarkerSelect] = gSweepTracePoint - 1;
//        } else {

//          // Marker Edit Pos Cal
//          for (i = 0; i < (gSweepTracePoint + 1); i++)  {
//              calculatorFreq = gStepFreq * i;
//              vigeoFreq  = gStartFreq + calculatorFreq ;

//              if (vigeoFreq >= freq) {
////                  gMarkerDeltaPos[gMarkerSelect] = i;
////                  gMarkerDeltaFreq[gMarkerSelect] = freq;
//                  break;
//                }
//            }
//        }

//    }




//}

//void RtSa_User_Variable::markerPositionReCalculatorFunc(void)
//{
//// qint32 i = 0;
//// qint32 k = 0;
////  qreal calculatorFreq = 0;
////  qreal vigeoFreq = 0;
////  qreal freq = 0;
////  qreal deltaMarkerFreq = 0;


////  // Marker - Marker to Center 실행시에는 전체적으로 Marker Pos를 다시 계산해야함
////  for (i = 0; i < MARKER_TOTAL_CNT; i++) {
////      if (gMarkerType[i] == DELTA)  {
////          deltaMarkerFreq = gMarkerDeltaFreq[i];

////          //Marker 주파수가 Start Freq 같음
////          if (deltaMarkerFreq <= gStartFreq)  {
////              gMarkerDeltaFreq[i] = gStartFreq;
////              gMarkerDeltaPos[i] = 0;

////            } else if (deltaMarkerFreq >= gStopFreq) {
////              gMarkerDeltaFreq[i] = gStopFreq;
////              gMarkerDeltaPos[i] = gSweepTracePoint - 1;
////            } else {

////              // Marker Edit Pos Cal
////              for (k = 0; k < (gSweepTracePoint + 1); k++)  {
////                  calculatorFreq = gStepFreq * k;
////                  vigeoFreq  = gStartFreq + calculatorFreq ;

////                  if (vigeoFreq >= deltaMarkerFreq) {
////                      gMarkerDeltaPos[i] = k;
////                      gMarkerDeltaFreq[i] = deltaMarkerFreq;
////                      break;
////                    }
////                }
////            }
////        }


////      freq = gMarkerRefFreq[i];

////      //Marker 주파수가 Start Freq 같음
////      if (freq == gStartFreq)  {
////          gMarkerRefFreq[i] = gStartFreq;
////          gMarkerRefPos[i] = 0;

////        } else if (freq == gStopFreq) {
////          gMarkerRefFreq[i] = gStopFreq;
////          gMarkerRefPos[i] = gSweepTracePoint - 1;
////        } else {

////          qDebug() << "[markerPositionReCalculatorFunc] gStepFreq => " << gStepFreq;

////          // Marker Edit Pos Cal
////          for (k = 0; k < (gSweepTracePoint + 1); k++)  {
////              calculatorFreq = gStepFreq * k;
////              vigeoFreq  = gStartFreq + calculatorFreq ;

////              if (vigeoFreq >= freq) {
////                  gMarkerRefPos[i] = k;
////                  gMarkerRefFreq[i] = freq;
////                  break;
////                }
////            }
////        }
////    }

////  guiDrawSet.peakPos = (int) (gSweepTracePoint / 2);



//}

//void RtSa_User_Variable::checkRbwWithStart70MHz()
//{
//  if ((gStartFreq <= (70 RTSA_mMHz)) && (gSpanFreq > (5 RTSA_mMHz)))  {
//      // RBW 30 kHz 일 때, 가능한 최대 Span은 250 MHz 임.
//      if (gSpanFreq > (250 RTSA_mMHz))       {
//          gSpanFreq = (250 RTSA_mMHz);
//          gCenterFreq = gStartFreq + (gSpanFreq / 2);
//          gStopFreq = gStartFreq +gSpanFreq;

//          qDebug() << "If Start<=70 MHz, RBW<=30 kHz";
//        }

//      if (gRbw > (30 RTSA_mkHz * RTSA_RVM)) {
//          gAutoRbw = RTSA_OFF;
//          gRbw = (30 RTSA_mkHz * RTSA_RVM);

//          checkRbwVbwBySpanFunc();

//          qDebug() << "If Start<=70 MHz, RBW<=30 kHz";
//        }
//    }
//}

//void RtSa_User_Variable::checkRbwVbwBySpanFunc()
//{
// qint32 retNo;
// qint32 retValidity;
//  quint32 currentArrayVal = 0;
//  quint32 beforeArrayVal = 0;
//  quint32 currentDiffVal = 0;
//  quint32 beforeDiffVal = 0;
// qint32 i;

//  if (gAutoRbw == RTSA_ON) {

//      // Span 으로 적용할 RBW 위치 찾아 오기
//      retNo = searchIndexSpanRbwVbwAutoGabFunc(gSpanFreq);

////      qDebug() << "retno => " <<  retNo;

//      // 그 위치에 해당하는 RBW 값을 적용
//      gRbw = RTSA_u32SpanRbwVbwAutoTable[retNo];

////      qDebug() << " gRbw => " <<  gRbw;

//    } else {

//      // Span 으로 적용할 RBW Table 위치 찾아 오기
//      retNo = searchIndexSpanRbwVbwManTableFunc(gSpanFreq);

//      qDebug() << "retno => " <<  retNo;

//      // 현재 RBW 값이 현재 Span에서 유효한 값인지 확인
//      retValidity = searchIndexRbwVbwManValidityFunc(RTSA_RBW, retNo, gRbw);

//      switch (retValidity) {
//        case RTSA_VALID_BW:
//          break;
//        case RTSA_INVALID_BW:
//          for (i = 0; i < RTSA_NUM_RBW_VBW_MAN_VARIETY; i++) {
//              currentArrayVal = RTSA_u32SpanRbwManTable[retNo][i];
//              qDebug() << "i / currentArrayVal = " << i  << " / "<<  currentArrayVal;
//              if (gRbw  < currentArrayVal) {
//                  qDebug() << "in";
//                  beforeArrayVal = RTSA_u32SpanRbwManTable[retNo][i-1];
//                  currentDiffVal = currentArrayVal - gRbw;
//                  beforeDiffVal = gRbw - beforeArrayVal;

//                  if (currentDiffVal <= beforeDiffVal)  // 가까운 값으로 할당하기 위함
//                    gRbw = currentArrayVal;
//                  else
//                    gRbw = beforeArrayVal;
//                  break;
//                }
//            }

//          if (i  == RTSA_NUM_RBW_VBW_MAN_VARIETY)
//            gRbw = searchIndexRbwVbwMaxFunc(RTSA_RBW, retNo);

//          break;
//        default:
//          qDebug() << "Error RBW setting!!!";
//          break;
//        }
//      qDebug() << " gRbw => " <<  gRbw;



//      // VBW ---------------------------------------------------------------------------
//      if (gAutoVbw == RTSA_OFF)  {
//          // 현재 Span에 따른 사용 가능한 VBW Table 찾기..
//          retNo = searchIndexSpanRbwVbwManTableFunc(gSpanFreq);

//          // 현재 VBW 값이 현재 Span에서 유효한 값인지 확인..
//          //int SearchIndex_RbwVbwManValidity(u64 span)
//          retValidity = searchIndexRbwVbwManValidityFunc(RTSA_VBW, retNo, gVbw);

////          retValidity = searchIndexRbwVbwManValidityFunc(_VBW, retNo, MainUserVariable.gVbw);

//          switch (retValidity) {
//            case RTSA_VALID_BW:
//              // RBW 그대로 유효함.
//              //ptSMConfig->csweep.RBWSet = ptSMConfig->csweep.RBWSet
//              checkVbwUnderRbw();
//              break;
//            case RTSA_INVALID_BW:
//              for (i = 0; i < RTSA_NUM_RBW_VBW_MAN_VARIETY; i++) {
//                  currentArrayVal = RTSA_u32SpanRbwManTable[retNo][i];
//                  qDebug() << "i / currentArrayVal = " << i  << " / "<<  currentArrayVal;
//                  if (gVbw  < currentArrayVal) {
//                      qDebug() << "in";
//                      beforeArrayVal = RTSA_u32SpanRbwManTable[retNo][i-1];
//                      currentDiffVal = currentArrayVal - gVbw;
//                      beforeDiffVal = gVbw - beforeArrayVal;

//                      if (currentDiffVal <= beforeDiffVal)  // 가까운 값으로 할당하기 위함
//                        gVbw = currentArrayVal;
//                      else
//                        gVbw = beforeArrayVal;
//                      break;
//                    }
//                }

//              if (i  == RTSA_NUM_RBW_VBW_MAN_VARIETY)
//                gVbw = searchIndexRbwVbwMaxFunc(RTSA_VBW, retNo);

//              checkVbwUnderRbw();
//              break;
//            default:
//              qDebug() << "Error RBW setting!!!";
//              break;
//            }
//        }  else  {      //if (ptSMConfig->csweep.VBWAuto == VBW_AUTO)
//          gVbw = gRbw;
//        }
//    }



//}

//void RtSa_User_Variable::checkVbwUnderRbw()
//{
//  if (gVbw > gRbw) {
//      qDebug() << "Check VBW > RBW!!!";
//      gRbw = gVbw;
//    }
//}

//quint32 RtSa_User_Variable::searchIndexRbwVbwMaxFunc(qint32 type,qint32 pos)
//{
//  quint32 retNo = 0;

//  switch (type)    {
//    case RTSA_RBW:
//      retNo = RTSA_u32SpanRbwManTable[pos][RTSA_NUM_RBW_VBW_MAN_VARIETY - 2];
//      break;
//    case RTSA_VBW:
//      // RBW, VBW Table 같음
//      retNo = RTSA_u32SpanRbwManTable[pos][RTSA_NUM_RBW_VBW_MAN_VARIETY - 2];
//      break;
//    }
//  return retNo;
//}

//qint32 RtSa_User_Variable::searchIndexRbwVbwManValidityFunc(qint32 type, qint32 pos, quint32 bw)
//{
//    quint32 retNo;
//    quint32 *ptr = NULL;

//    switch (type) {
//      case RTSA_RBW:
//        // void *bsearch(const void *key, const void *base, size_t nel, size_t width, int (*compare)(const void *, const void *));
//        ptr = ( quint32 *)bsearch(&bw, &RTSA_u32SpanRbwManTable[pos][0], RTSA_NUM_RBW_VBW_MAN_VARIETY, sizeof(quint32), RbwVbwCompare);
//        break;
//      case RTSA_VBW:
//        // VBW Manual Table이 RBW Manual Table과 같다. 2015-04-08
//        // void *bsearch(const void *key, const void *base, size_t nel, size_t width, int (*compare)(const void *, const void *));
//        ptr = (quint32 *)bsearch(&bw, &RTSA_u32SpanRbwManTable[pos][0], RTSA_NUM_RBW_VBW_MAN_VARIETY, sizeof(quint32), RbwVbwCompare);
//        break;
//      }

//    if (ptr == NULL)  {
//        retNo = RTSA_INVALID_BW;		// 10 MHz .. 임시 에러 값..
//      }   else  {
//        retNo = RTSA_VALID_BW;
//      }

//    return retNo;

//}

//qint32 RtSa_User_Variable::searchIndexSpanRbwVbwAutoGabFunc(qreal span)
//{
// qint32 i = 0;

//  for (i = 0; i < RTSA_NUM_RBW_VBW_AUTO_SPAN_BOUNDARY; i++) {
//      if (span <= RTSA_u64RbwVbwAutoSpanBoundary[i]) {
//          break;
//        }
//    }

//  if (i == RTSA_NUM_RBW_VBW_AUTO_SPAN_BOUNDARY) {
//      qDebug() << "Invalid Span";
//    }

//  return i;

//}

//qint32 RtSa_User_Variable::searchIndexSpanRbwVbwManTableFunc(qreal span)
//{

// qint32 i = 0;

//  for (i = 0; i < RTSA_NUM_RBW_VBW_MAN_SPAN_BOUNDARY; i++) {
//      if (span <= RTSA_u64RbwVbwManSpanBoundary[i]) {
//          break;
//        }
//    }

//  if (i == RTSA_NUM_RBW_VBW_MAN_SPAN_BOUNDARY) {
//      qDebug() << "Invalid Span";
//    }

//  return i;
//}

//qint32 RtSa_User_Variable::RbwVbwCompare(const void *a, const void *b)
//{

//  if (*(quint32 *)a > *(quint32 *)b)
//    return 1;
//  else if (*(quint32 *)a == *(quint32 *)b)
//    return 0;
//  else // if (*(quint32 *)a < *(quint32 *)b)
//    return -1;

//}

//void RtSa_User_Variable::dbmToVoltCalculatorAndDisplayFunc(char *label, double _level)
//{
//    double voltGab = 0.;
//      double calculator = 0.;

//      calculator = qPow(10, _level / 10.);
//      voltGab = 1000000. * qPow(50 * calculator * 0.001, 0.5);//uv

//      //Johnson 0919 Change
//      if (_level <= 20. && voltGab >= 1000000.) {
//            sprintf(label, "%.2f V", (double) voltGab / 1000000.);
//          } else if (voltGab < 1000000. && voltGab >= 1000.) {
//            sprintf(label, "%.2f mV", (double) voltGab / 1000.);
//          } else if (voltGab < 1000. && voltGab >= 1.) {
//            sprintf(label, "%.2f uV", (double) voltGab);
//          } else if (voltGab < 1. && voltGab >= 0.001) {
//            sprintf(label, "%.2f nV", (double) voltGab * 1000);
//          } else if (voltGab < 0.001 && voltGab >= 0.000001) {
//            sprintf(label, "%.2f pV", (double) voltGab * 1000000.);
//          } else if (voltGab < 0.000001 && voltGab >= 0.000000001) {
//            sprintf(label, "%.2f fV", (double) voltGab * 1000000000.);
//          } else if (voltGab < 0.000000001 && voltGab >= 0.000000000001) {
//            sprintf(label, "%.2f aV", (double) voltGab * 1000000000000.);
//          } else if (voltGab < 0.000000000001 && voltGab >= 0.000000000000001) {
//            sprintf(label, "%.2f zV", (double) voltGab * 1000000000000000.);
//          } else if (voltGab < 0.000000000000001 && voltGab >= 0.000000000000000001) {
//            sprintf(label, "%.2f yV", (double) voltGab * 1000000000000000000.);
//          } else {
//            sprintf(label, "%.2f", (double) voltGab * 1000000000000000000000.);
//          }

//  #if  0
//  double voltGab = 0.;
//  double calculator = 0.;

//  calculator = qPow(10, _level / 10.);
//  voltGab = 1000000. * qPow(50 * calculator * 0.001, 0.5);


//  if (voltGab <= 7071067.9 && voltGab >= 1121000.) {
//      sprintf(label, "%.2f V", (double) voltGab / 1000000);
//    } else if (voltGab <= 998800. && voltGab >= 1121.) {
//      sprintf(label, "%.2f mV", (double) voltGab / 1000.);
//    } else if (voltGab <= 998.8 && voltGab >= 1.121) {
//      sprintf(label, "%.2f uV", (double) voltGab);
//    } else if (voltGab <= 9.988 && voltGab >= 0.221) {
//      sprintf(label, "%.2f nV", (double) voltGab * 1000);
//    } else if (voltGab <= 0.09988 && voltGab >= 0.00221) {
//      sprintf(label, "%.2f pV", (double) voltGab * 1000000.);
//    }
//#endif
//  // qDebug() << "voltGab  =>> " <<  label ;
//}

//void RtSa_User_Variable::charEmptySplitWorkerFunc(char *label)
//{
////  char *ptr;
//// qint32 cnt = 0;

////  ptr = strtok(label, " ");   // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
////  cnt = 0;
////  while (ptr != NULL) {   // 자른 문자열이 나오지 않을 때까지 반복
////      if (cnt == 0)
////        sprintf(watts_unit.value, "%s", ptr);
////      else
////        sprintf(watts_unit.unit, "%s", ptr);
////      ptr = strtok(NULL, " ");   // 다음 문자열을 잘라서 포인터를 반환
////      cnt++;
////      //            qDebug() << " while ptr ________________" << ptr;
////    }

//return;

//}

//void RtSa_User_Variable::dbmToWattsCalculatorAndDisplayFunc(char *label, double _level)
//{
//  double wattsGab = 0.;

//  wattsGab = qPow(10, _level / 10.);

//  if (wattsGab >= 1000) {						// W
//      sprintf(label, "%.2f W", (double)wattsGab / 1000.0);
//    }  else if (wattsGab >= 1) {					// mW
//      sprintf(label, "%.2f mW", (double)wattsGab);
//    }  else if (wattsGab >= 0.001) {				// uW
//      sprintf(label, "%.2f uW", (double)wattsGab * 1000.0);
//    }  else if (wattsGab >= 0.000001) {			// nW
//      sprintf(label, "%.2f nW", (double)wattsGab * 1000000.0);
//    } else if (wattsGab >= 0.000000001) {			// pW
//      sprintf(label, "%.2f pW", (double)wattsGab * 1000000000.0);
//    } else if (wattsGab >= 0.000000000001) {		// fW
//      sprintf(label, "%.2f fW", (double)wattsGab * 1000000000000.0);
//    } else {                                                    	// aW
//      sprintf(label, "%.2f aW", (double)wattsGab * 1000000000000000.0);
//    }

//  qDebug() << "wattsGab  =>> " <<  label ;
//}

double RtSa_User_Variable::wattsToDbmCalculatorFunc(double _watts)
{
  return   (10 * log10(_watts) + 30);
}

double RtSa_User_Variable::voltToDbmCalculatorFunc(double _volt)
{
  double cal1 = 0.;
  double cal2 = 0.;
  double cal3 = 0.;
  double cal4 = 0.;

  cal1 = _volt * qPow(10, -6);
  cal2 = qPow(cal1 , 2) / 50.;
  cal3 = 10 * log10(cal2);
  cal4 = cal3 + 30.;

  return cal4;

}

//bool RtSa_User_Variable::screenCaptureFunc()
//{

//  bool retFlag = QPixmap::grabWindow(QApplication::desktop()->winId(), 0, 0, 1024, 768).save("./ScreenShot.png");


//  //Johnson 0823
//  //bool retFlag = QPixmap::grabWindow(QApplication::desktop()->winId(), 65,23, 1024, 850).save("./ScreenShot.png");

//  return retFlag;
//}

//void RtSa_User_Variable::saveFilenameAssignFunc(quint32 btnType, QString title)
//{

//#if 0
//  // FileNameDialog 나중에 구현해야함
//  FileNameDialog dialog(this, btnType, title);

//  pFileNameDialog = &dialog;

//  //dialog.setWindowTitle(title);

//  // 현재 기본 타이틀 구조를 그대로 사용하고 있음.. 색 등을 바꾸려면 기본 타이틀을 없애고 ... 그림으로 넣어야 함.. 2015-01-29

//  dialog.setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
//  dialog.setGeometry(135, 160, 402, 94);

//  // FileNameDialog 창 실행 ..
//  dialog.exec();
//#endif

//}

//void RtSa_User_Variable::sharedMemoryVariableAssignFunc()
//{
//  sm_rtsa_config_rsa_ctrl->CenterFreq      = (double) gCenterFreq;
//  sm_rtsa_config_rsa_ctrl->SpanFreq        = (double) gSpanFreq;
//  sm_rtsa_config_rsa_ctrl->StartFreq       = (double) gStartFreq;
//  sm_rtsa_config_rsa_ctrl->StopFreq        = (double) gStopFreq;

//  sm_rtsa_config_rsa_ctrl->SpanMode        = gSpanMode;		    // [0]Normal, [1]Full SPAN, [2]Zero SPAN
//  sm_rtsa_config_rsa_ctrl->TracePoint      = gTracePoint;        // [0]501, [1]1001, [2]2001, [3]3001 (point)
//  sm_rtsa_config_rsa_ctrl->RBW             = gRbw; 			    // Hz
//  sm_rtsa_config_rsa_ctrl->RBWAuto         = gAutoRbw;		    // [0]Manual, [1]Auto
//  sm_rtsa_config_rsa_ctrl->DetectorMode    = gDetectorMode;	    // [0]Max, [1]Min, [2]Sample, [3]Avg-Power, [4]Avg-Voltage
//  sm_rtsa_config_rsa_ctrl->RefLevel        = gRefLevel;				// +10 ~ -150 dBm
//  sm_rtsa_config_rsa_ctrl->AttenSelect     = gAttenSelect;		// [0]0, [1]5, [2]10, [3]15, [4]20, [5]25, [6]30 (dB)
//  sm_rtsa_config_rsa_ctrl->SweepType       = gSweepType;		    // [0]Continuous, [1]Single, [2]Sweep Off
//  sm_rtsa_config_rsa_ctrl->ExtTrigger      = gExtTrigger;		// [0]Off, [1]On
//  sm_rtsa_config_rsa_ctrl->TriggerMode     = gTriggerMode;		// [0]Free Run, [1]Rise, [2]Fall, [3]Delay

//  sm_rtsa_config_rsa_ctrl->Preamp          = gPreamp;			// [0]Off, [1]On
//  sm_rtsa_config_rsa_ctrl->attenValue      = gAttenValue;    //Johnson Add  //Johnson Add
//  sm_rtsa_config_rsa_ctrl->attenAuto           = gAtten;          // [0]Off, [1]On

//  //Johnson 0718
////  sm_rtsa_config_rsa_ctrl->AutoSweepTime = gAutoSweepTime;
////  sm_rtsa_config_rsa_ctrl->SweepTime    = gSweepTime;

//  //Set_config_flag(IXT_ConfigSweep, IXS_RTSA_CenterFreq|IXS_RTSA_SpanFreq|IXS_RTSA_StartFreq|IXS_RTSA_StopFreq|IXS_RTSA_SpanMode|IXS_RTSA_TracePoint|IXS_RTSA_RBW|IXS_RTSA_RBWAuto|IXS_VBW|IXS_VBWAuto | IXS_RTSA_DetectorMode|IXS_RTSA_RefLevel|IXS_RTSA_AttenSelect|IXS_RTSA_SweepType|IXS_RTSA_ExtTrigger|IXS_RTSA_TriggerMode|IXS_ZeroSpanTime|IXS_ZeroSpanMode|IXS_RTSA_Preamp|IXS_ImageRejection);
//}
//Johnson 0802
//void RtSa_User_Variable::fileSaveLoadParaToglobalUserVariable(_RTSA_FILE_SAVE_LOAD_VARIABLE_ *pVariable)
//{
//    //********Measure
//    //gMeasurement      = pVariable->gConfig_Measure.gMeasurement;
//    //gDemodulationType = pVariable->gConfig_Measure.gDemodulationType;
//    //gChannelBandwidth = pVariable->gConfig_Measure.gChannelBandwidth;
//    //gChannelSpacing   = pVariable->gConfig_Measure.gChannelSpacing;

//    //********Freq Span
//    gStartFreq        = pVariable->gConfig_FreqSpan.gStartFreq;
//    gStopFreq         = pVariable->gConfig_FreqSpan.gStopFreq;
//    gCenterFreq       = pVariable->gConfig_FreqSpan.gCenterFreq;
////    gCFFreq           = pVariable->gConfig_FreqSpan.gCFFreq;
//    gSpanFreq         = pVariable->gConfig_FreqSpan.gSpanFreq;
//    gStepFreq         = pVariable->gConfig_FreqSpan.gStepFreq;
////    gSpanMode         = pVariable->gConfig_FreqSpan.gSpanMode;
////    gZeroSpanTime     = pVariable->gConfig_FreqSpan.gZeroSpanTime;
////    gZeroSpanMode     = pVariable->gConfig_FreqSpan.gZeroSpanMode;
////    gSpanStepPos      = pVariable->gConfig_FreqSpan.gSpanStepPos;
////    gLastSpanFreq     = pVariable->gConfig_FreqSpan.gLastSpanFreq;
////    gZeroSpanAction   = pVariable->gConfig_FreqSpan.gZeroSpanAction;

////    gspanChangebyFreq = pVariable->gConfig_FreqSpan.gspanChangebyFreq;
////    gbitsspan         = pVariable->gConfig_FreqSpan.gbitsspan;
////    gbithalfsspan     = pVariable->gConfig_FreqSpan.gbithalfsspan;

//    //*******BW
////    gVbwtoRbw         = pVariable->gConfig_BW.gVbwtoRbw;
////    gAutoVbwtoRbw     = pVariable->gConfig_BW.gAutoVbwtoRbw;
////    grbwChangedbyFreq = pVariable->gConfig_BW.grbwChangedbyFreq;

////    gAutoRbw          = pVariable->gConfig_BW.gAutoRbw;
////    gAutoVbw          = pVariable->gConfig_BW.gAutoVbw;
////    gRbw              = pVariable->gConfig_BW.gRbw;
////    gVbw              = pVariable->gConfig_BW.gVbw;

//    //Tony 0903 add
//    //*******Amplitude
////    gRefLevel         = pVariable->gConfig_Amplitude.gRefLevel;
////    gRefOffset        = pVariable->gConfig_Amplitude.gRefOffset;
////    gScaleDiv         = pVariable->gConfig_Amplitude.gScaleDiv;
////    gAmptdUnit        = pVariable->gConfig_Amplitude.gAmptdUnit;
////    gAtten            = pVariable->gConfig_Amplitude.gAtten;
////    gPreamp           = pVariable->gConfig_Amplitude.gPreamp;
////    gAttenValue       = pVariable->gConfig_Amplitude.gAttenValue;
////    gAttenSelect      = pVariable->gConfig_Amplitude.gAttenSelect;

//    //*******Trace
////    memcpy(greAvager,pVariable->gConfig_Trace.greAvager,sizeof(int)*NUM_TRACE);
////    memcpy(gTraceType,pVariable->gConfig_Trace.gTraceType,sizeof(int)*NUM_TRACE);
////    memcpy(gTraceAverage,pVariable->gConfig_Trace.gTraceAverage,sizeof(int)*NUM_TRACE);
////    memcpy(gAverageCount,pVariable->gConfig_Trace.gAverageCount,sizeof(int)*NUM_TRACE);
////    memcpy(gAverageNo,pVariable->gConfig_Trace.gAverageNo,sizeof(int)*NUM_TRACE);
////    for(qint32 i = 0;i<NUM_TRACE;i++){
////        memcpy(gTraceMeasureVal[i],pVariable->gConfig_Trace.gTraceMeasureVal[i],sizeof(double)*RTSA_NUM_SWEEP_POINT);
////    }
////    gTraceSelect      = pVariable->gConfig_Trace.gTraceSelect;
////    gViewAction       = pVariable->gConfig_Trace.gViewAction;

//    //*******Sweep
////    gsweepAuto        = pVariable->gConfig_Sweep.gsweepAuto;
////    gAutoSweepTime    = pVariable->gConfig_Sweep.gAutoSweepTime;
////    gOverlap          = pVariable->gConfig_Sweep.gOverlap;
////    gDetectorMode     = pVariable->gConfig_Sweep.gDetectorMode;
////    gSweepType        = pVariable->gConfig_Sweep.gSweepType;
////    gSweepTime        = pVariable->gConfig_Sweep.gSweepTime;
////    gExtTrigger       = pVariable->gConfig_Sweep.gExtTrigger;
////    gTriggerMode      = pVariable->gConfig_Sweep.gTriggerMode;

////    //*******Marker
////    gMarkerSelect     = pVariable->gConfig_Marker.gMarkerSelect;
////    gMarkerDisplay    = pVariable->gConfig_Marker.gMarkerDisplay;
////    memcpy(gMarkerView,pVariable->gConfig_Marker.gMarkerView,sizeof(int)*MARKER_TOTAL_CNT);
////    memcpy(gMarkerType,pVariable->gConfig_Marker.gMarkerType,sizeof(int)*MARKER_TOTAL_CNT);
////    memcpy(gMarkerRefFreq,pVariable->gConfig_Marker.gMarkerRefFreq,sizeof(unsigned long long)*MARKER_TOTAL_CNT);
////    memcpy(gMarkerRefPos,pVariable->gConfig_Marker.gMarkerRefPos,sizeof(int)*MARKER_TOTAL_CNT);
////    memcpy(gMarkerDeltaFreq,pVariable->gConfig_Marker.gMarkerDeltaFreq,sizeof(unsigned long long)*MARKER_TOTAL_CNT);
////    memcpy(gMarkerDeltaPos,pVariable->gConfig_Marker.gMarkerDeltaPos,sizeof(int)*MARKER_TOTAL_CNT);

//    //*******Peak


////    //*******Limit
////    globalUserLimit->gLimitTestResult  = pVariable->gConfig_Limit.gLimitTestResult;
////    globalUserLimit->gLimitTest       = pVariable->gConfig_Limit.gLimitTest;
////    globalUserLimit->gLimitLine[0]        = pVariable->gConfig_Limit.gLimitLine;
////   // memcpy(globalUserLimit->gLimitLine,pVariable->gConfig_Limit.gLimitLine,sizeof(int)*LIMIT_TOTAL);
////    globalUserLimit->gLimitAlarm       = pVariable->gConfig_Limit.gLimitAlarm;
////    globalUserLimit->gLimitMessage     = pVariable->gConfig_Limit.gLimitMessage;
////    globalUserLimit->gLimitEdge[0]       = pVariable->gConfig_Limit.gLimitEdge;
////    //memcpy(globalUserLimit->gLimitEdge,pVariable->gConfig_Limit.gLimitEdge,sizeof(int)*LIMIT_TOTAL);
////    globalUserLimit->gLimitSelect      = pVariable->gConfig_Limit.gLimitSelect;

////    memcpy(globalUserLimit->gLimitType,pVariable->gConfig_Limit.gLimitType,sizeof(int)*LIMIT_TOTAL);
////    memcpy(globalUserLimit->gStartX,pVariable->gConfig_Limit.gStartX,sizeof(double)*LIMIT_TOTAL);
////    memcpy(globalUserLimit->gStopX,pVariable->gConfig_Limit.gStopX,sizeof(double)*LIMIT_TOTAL);
////    memcpy(globalUserLimit->gStartY,pVariable->gConfig_Limit.gStartY,sizeof(double)*LIMIT_TOTAL);
////    memcpy(globalUserLimit->gStopY,pVariable->gConfig_Limit.gStopY,sizeof(double)*LIMIT_TOTAL);

////    memcpy(globalUserLimit->lineXAxisStartX,pVariable->gConfig_Limit.lineXAxisStartX,sizeof(int)*LIMIT_TOTAL);
////    memcpy(globalUserLimit->lineXAxisStopX,pVariable->gConfig_Limit.lineXAxisStopX,sizeof(int)*LIMIT_TOTAL);
////    memcpy(globalUserLimit->lineYAxisStartY,pVariable->gConfig_Limit.lineYAxisStartY,sizeof(int)*LIMIT_TOTAL);
////    memcpy(globalUserLimit->lineYAxisStopY,pVariable->gConfig_Limit.lineYAxisStopY,sizeof(int)*LIMIT_TOTAL);

////    memcpy(globalUserLimit->LimitUpperDrawPoint,pVariable->gConfig_Limit.LimitUpperDrawPoint,sizeof(int)*RTSA_NUM_SWEEP_POINT);
////    memcpy(globalUserLimit->LimitLowerDrawPoint,pVariable->gConfig_Limit.LimitLowerDrawPoint,sizeof(int)*RTSA_NUM_SWEEP_POINT);

//    //*******Power Sensor
////    gMenu                  = pVariable->gConfig_PowerSensor.gMenu;
////    gPowersensorFreq       = pVariable->gConfig_PowerSensor.gPowersensorFreq;
////    gPowersensorExtOffset  = pVariable->gConfig_PowerSensor.gPowersensorExtOffset;

//    //*******Preset


//    //*******System



//    //******GUI Draw Set
////    guiDrawSet.gridHorStep      = pVariable->gConfig_GuiDrawSet.gridHorStep;
////    guiDrawSet.gridVerStep      = pVariable->gConfig_GuiDrawSet.gridVerStep;
////    guiDrawSet.limitLineOnCount = pVariable->gConfig_GuiDrawSet.limitLineOnCount;
////    guiDrawSet.markerOnCount    = pVariable->gConfig_GuiDrawSet.markerOnCount;
////    guiDrawSet.peakPos          = pVariable->gConfig_GuiDrawSet.peakPos;
//}
//void RtSa_User_Variable::globalUserVariableTofileSaveLoadPara(_RTSA_FILE_SAVE_LOAD_VARIABLE_ *pVariable)
//{


//}
//void RtSa_User_Variable::setVariable(_RTSA_FILE_SAVE_LOAD_VARIABLE_ *pVariable, quint32 workMode)
//{
//    if(loadVariable(pVariable,workMode)){
//        //pVariable->globalUserVariable
//        fileSaveLoadParaToglobalUserVariable(pVariable);
//    }
//    else{
//        //pVariable
//        globalUserVariableTofileSaveLoadPara(pVariable);
//    }
//}
//Johnson 0802
//bool RtSa_User_Variable::loadVariable(_RTSA_FILE_SAVE_LOAD_VARIABLE_ *pVariable, quint32 workMode)
//{
//    //Write FilegPowersensorExtOffset
//    /*FILE *pFile = fopen("variable.ini","w");
//    fwrite(pVariable,1,sizeof(_FILE_SAVE_LOAD_VARIABLE_),pFile);
//    fflush(pFile);
//    fclose(pFile);*/
//    FILE *pFile = NULL;
//    if(workMode == RTSA_SPAN_MODE) pFile = fopen("SpanMode_Variable.ini","r");
//    else if(workMode == RTSA_MEASURE_MODE) pFile = fopen("MeasureMode_Variable.ini","r");
//    if(!pFile){
//        qDebug()<<"Open file fail!";
//        return false;
//    }
//    fseek(pFile,0,SEEK_END);
//    if(!ftell(pFile)){
//        qDebug()<<"The file is null!";
//        fclose(pFile);
//        return false;
//    }
//    fseek(pFile,0,SEEK_SET);
//    //fread(pVariable,1,sizeof(_FILE_SAVE_LOAD_VARIABLE_),pFile);
//    fread(pVariable,sizeof(_RTSA_FILE_SAVE_LOAD_VARIABLE_),1,pFile);
//    fclose(pFile);
//    qDebug()<<"save variable success!";

//    fileSaveLoadParaToglobalUserVariable(pVariable);

//    return true;
//}
//Johnson 0802
//bool RtSa_User_Variable::saveVariable(_RTSA_FILE_SAVE_LOAD_VARIABLE_ *pVariable, quint32 workMode)
//{
//    QDir dir(QString("."));
//    QString path = dir.absolutePath();
//    QString savePath;
//    if(workMode == RTSA_SPAN_MODE) savePath = QString("%1%2").arg(path).arg("/SpanMode_Variable.ini");
//    else if(workMode == RTSA_MEASURE_MODE) savePath = QString("%1%2").arg(path).arg("/MeasureMode_Variable.ini");

//    globalUserVariableTofileSaveLoadPara(pVariable);

//    QFile f(savePath);
//    if(!f.open(QIODevice::WriteOnly)){
//        qDebug()<<"save variable fail!";
//        return false;
//    }
//    f.write((char *)pVariable,sizeof(_RTSA_FILE_SAVE_LOAD_VARIABLE_));
//    f.close();
//    qDebug()<<"save variable success!";

//    //******Read File
//    /*f.open(QIODevice::ReadOnly);
//    f.read((char *)&pVariable,sizeof(_FILE_SAVE_LOAD_VARIABLE_));
//    f.close();*/

//    return true;
//}
void RtSa_User_Variable::getBandInfo(qint32 STDIndex)
{
    QString name = QString(mRTSA_ChStand[STDIndex].name);
    QString filename = QString(":/rtsa/standard/%1").arg(name);
    QString str;
    QByteArray line;
    gCHName->clear();
    gCHStandard->clear();
    gFreqStandard->clear();
    QFile mFile(filename);
    if(mFile.open(QFile::ReadOnly))
    {
        while (!mFile.atEnd())
        {
            line = mFile.readLine();
            str = QString(line);
            analysisData(str);
        }
        mFile.close();
    }
    else
    {
        setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,RTSA_APP_CHANNEL_FILE);
        errorOutput();
    }
    mFile.close();
    return;
}
void RtSa_User_Variable::analysisData(QString str)
{
    __RTSA_Standard__ mtmp;
    QStringList list = str.split(",");
    if(list.size() == 5)
    {
        gCHName->append(list[0]);
        mtmp.Up.Min = QString(list[1]).toDouble();
        mtmp.Up.Max = QString(list[2]).toDouble();
        mtmp.Down.Min = QString(list[1]).toDouble();
        mtmp.Down.Max = QString(list[2]).toDouble();
        gCHStandard->append(mtmp);

        mtmp.Up.Min = QString(list[3]).toDouble();
        mtmp.Up.Max = QString(list[4]).toDouble();
        mtmp.Down.Min = QString(list[3]).toDouble();
        mtmp.Down.Max = QString(list[4]).toDouble();
        gFreqStandard->append(mtmp);
    }else if(list.size() == 9)
    {
        gCHName->append(list[0]);
        mtmp.Up.Min = QString(list[1]).toDouble();
        mtmp.Up.Max = QString(list[2]).toDouble();
        mtmp.Down.Min = QString(list[3]).toDouble();
        mtmp.Down.Max = QString(list[4]).toDouble();
        gCHStandard->append(mtmp);

        mtmp.Up.Min = QString(list[5]).toDouble();
        mtmp.Up.Max = QString(list[6]).toDouble();
        mtmp.Down.Min = QString(list[7]).toDouble();
        mtmp.Down.Max = QString(list[8]).toDouble();
        gFreqStandard->append(mtmp);
    }

    return;
}
qint32 RtSa_User_Variable::CalculateChannelNum()
{

    qint32 index,channelSTD,direction;
    qreal freq;
    channelSTD = gTecIndex;
    freq = gCenterFreq;
    direction = gCommuDirection;
    switch (channelSTD) {
    case RTSA_CDMA:
        if(direction == RTSA_UPLINK)
        {
            index = (freq - 825000000)/(0.03 *RTSA_MHZ);
        }
        else
        {
            index = (freq - 870000000)/(0.03 *RTSA_MHZ);
        }
        break;
    case RTSA_GSM:
        if(freq < 1500000000)
        {
            if(direction == RTSA_UPLINK)
            {
                index = (freq - 890200000)/(0.2*RTSA_MHZ)+1;
            }
            else
            {
                index = (freq - 935200000)/(0.2*RTSA_MHZ)+1;
            }
        }else
        {
            if(direction == RTSA_UPLINK)
            {
                index = (freq - 1710000000)/(0.2*RTSA_MHZ)+511;
            }
            else
            {
                index = (freq - 1805000000)/(0.2*RTSA_MHZ)+511;
            }
        }
        break;
    case RTSA_WCDMA:
        index = freq/RTSA_MHZ * 5;
        break;
    case RTSA_TD_SCDMA:
        if(freq >2010000000 && freq<=2025000000 ) //A Freq
        {
            index = freq/RTSA_MHZ *5;
        }else if(freq > 1800000000 && freq<=2000000000) //F Freq
        {
            index = freq/RTSA_MHZ *5;
        }else if(freq > 2300000000 && freq<=2400000000)  //E Freq
        {
            index = freq/RTSA_MHZ *5;
        }
        break;
    case RTSA_LTE_TDD:
        if(freq >= RTSA_TD_B38_FREQ_MIN && freq <= RTSA_TD_B38_FREQ_MAX)
        {
            index = (freq - RTSA_TD_B38_FREQ_MIN)/RTSA_MHZ*10+RTSA_TD_B38_FREQPOINT_BASE;
        }
        else if(freq >= RTSA_TD_B39_FREQ_MIN && freq <= RTSA_TD_B39_FREQ_MAX)
        {
            index = (freq - RTSA_TD_B39_FREQ_MIN)/RTSA_MHZ*10+RTSA_TD_B39_FREQPOINT_BASE;
        }
        else if(freq >= RTSA_TD_B40_FREQ_MIN && freq <= RTSA_TD_B40_FREQ_MAX)
        {
            index = (freq - RTSA_TD_B40_FREQ_MIN)/RTSA_MHZ*10+RTSA_TD_B40_FREQPOINT_BASE;
        }
        else if(freq >= RTSA_TD_B41_FREQ_MIN && freq <= RTSA_TD_B41_FREQ_MAX)
        {
            index = (freq - RTSA_TD_B41_FREQ_MIN)/RTSA_MHZ*10+RTSA_TD_B41_FREQPOINT_BASE;
        }
        break;
    case RTSA_LTE_FDD:
        if(freq >= RTSA_FDD_B1_UP_FREQ_MIN && freq <= RTSA_FDD_B1_UP_FREQ_MAX)
        {
            index = (freq - RTSA_FDD_B1_UP_FREQ_MIN)*10/RTSA_MHZ+RTSA_FDD_B1_UP_FREQPOINT_BASE;
        }
        else if(freq >= RTSA_FDD_B1_DOWN_FREQ_MIN && freq <= RTSA_FDD_B1_DOWN_FREQ_MAX)
        {
            index = (freq - RTSA_FDD_B1_DOWN_FREQ_MIN)*10/RTSA_MHZ+RTSA_FDD_B1_DOWN_FREQPOINT_BASE;
        }
        else if(freq >= RTSA_FDD_B3_UP_FREQ_MIN && freq <= RTSA_FDD_B3_UP_FREQ_MAX)
        {
            index = (freq - RTSA_FDD_B3_UP_FREQ_MIN)*10/RTSA_MHZ+RTSA_FDD_B3_UP_FREQPOINT_BASE;
        }
        else if(freq >= RTSA_FDD_B3_DOWN_FREQ_MIN && freq <= RTSA_FDD_B3_DOWN_FREQ_MAX)
        {
            index = (freq - RTSA_FDD_B3_DOWN_FREQ_MIN)*10/RTSA_MHZ+RTSA_FDD_B3_DOWN_FREQPOINT_BASE;
        }
        break;
    }
    return index;
}
void RtSa_User_Variable::adjustCHStandarByCerFreq(qreal freq)
{
    freq = (qreal)freq/RTSA_MHZ;
    qint32 size;
    for(qint32 i = 0 ;i<7;i++)
    {
        getBandInfo(i);
        size = gCHName->size();
        for(qint32 j=0;j<size;j++)
        {
            if(freq>=gFreqStandard->at(j).Up.Min && freq<=gFreqStandard->at(j).Up.Max)
            {
                gTecIndex =i;
                gCHIndex = j;
                gChannelNum = CalculateChannelNum();
                gChannelStep = mRTSA_ChStand[i].ChStep;
                gCommuDirection = RTSA_UPLINK;
                return;
            }else if(freq>=gFreqStandard->at(j).Down.Min && freq<=gFreqStandard->at(j).Down.Max)
            {
                gTecIndex =i;
                gCHIndex = j;
                gChannelNum = CalculateChannelNum();
                gChannelStep = mRTSA_ChStand[i].ChStep;
                gCommuDirection = RTSA_DOWNLINK;
                return;
            }
        }
    }
    gCHIndex = 0;
    gTecIndex = -1;
    return;
}
qreal RtSa_User_Variable::adjustFreqByCHStandar()
{
    if(gTecIndex < 0 || gFreqStandard->isEmpty())
        return gCenterFreq;
    qreal freq,min,max;
    qint32 direction,index;
    direction = gCommuDirection;
    freq = gCenterFreq;
    index = gCHIndex;
    if(direction == RTSA_UPLINK)
    {
        min = gFreqStandard->at(index).Up.Min * RTSA_MHZ;
        max = gFreqStandard->at(index).Up.Max * RTSA_MHZ;
    }
    else
    {
        min = gFreqStandard->at(index).Down.Min * RTSA_MHZ;
        max = gFreqStandard->at(index).Down.Max * RTSA_MHZ;
    }
    if(freq < min || freq > max)
    {
        freq = (min + max)/2;
    }
    freq += gfreqOffset;
    return freq;
}
qreal RtSa_User_Variable::adjustFreqByCHNum(qint32 index)
{
    qint32 channelSTD,direction;
    qreal freq;
    channelSTD = gTecIndex;
    direction = gCommuDirection;
    switch (channelSTD) {
    case RTSA_CDMA:
        if(direction == RTSA_UPLINK)
        {
            freq = index*(0.03 *RTSA_MHZ) + 825000000;
        }else
        {
            freq = index*(0.03 *RTSA_MHZ) + 870000000;
        }
        break;
    case RTSA_GSM:
        if(index < 125)
        {
            if(direction == RTSA_UPLINK)
            {
                freq = (index-1)*(0.2*RTSA_MHZ) + 890200000;
            }else
            {
                freq = (index-1)*(0.2*RTSA_MHZ) + 935200000;
            }
        }else
        {
            if(direction == RTSA_UPLINK)
            {
                freq = (index-511)*(0.2*RTSA_MHZ)+ 1710000000;
            }else
            {
                freq = (index-511)*(0.2*RTSA_MHZ)+ 1805000000;
            }
        }
        break;
    case RTSA_WCDMA:
         freq = (qreal)index / 5 * RTSA_MHZ;
        break;
    case RTSA_TD_SCDMA:
        freq = (qreal)index / 5 * RTSA_MHZ;
//        if(freq >2010000000 && freq<=2025000000 ) //A Freq
//        {
//            index = freq *5;
//        }else if(freq > 1800000000 && freq<=2000000000) //F Freq
//        {

//        }else if(freq > 2300000000 && freq<=2400000000)  //E Freq
//        {

//        }
        break;
    case RTSA_LTE_TDD:
        if(index >= RTSA_TD_B38_FREQPOINT_BASE && index <= RTSA_TD_B38_FREQPOINT_MAX)
        {
            freq = (index - RTSA_TD_B38_FREQPOINT_BASE)*RTSA_MHZ/10 + RTSA_TD_B38_FREQ_MIN;
        }else if(index >= RTSA_TD_B39_FREQPOINT_BASE && index <= RTSA_TD_B39_FREQPOINT_MAX)
        {
            freq = (index - RTSA_TD_B39_FREQPOINT_BASE)*RTSA_MHZ/10 + RTSA_TD_B39_FREQ_MIN;
        }else if(index >= RTSA_TD_B40_FREQPOINT_BASE && index <= RTSA_TD_B40_FREQPOINT_MAX)
        {
            freq = (index - RTSA_TD_B40_FREQPOINT_BASE)*RTSA_MHZ/10 + RTSA_TD_B40_FREQ_MIN;
        }else if(index >= RTSA_TD_B41_FREQPOINT_BASE && index <= RTSA_TD_B41_FREQPOINT_MAX)
        {
            freq = (index - RTSA_TD_B41_FREQPOINT_BASE)*RTSA_MHZ/10 + RTSA_TD_B41_FREQ_MIN;
        }
        break;
    case RTSA_LTE_FDD:
        if(index >= RTSA_FDD_B1_UP_FREQPOINT_BASE && index <= RTSA_FDD_B1_UP_FREQPOINT_MAX)
        {
            freq = (index-RTSA_FDD_B1_UP_FREQPOINT_BASE)*RTSA_MHZ/10+ RTSA_FDD_B1_UP_FREQ_MIN ;
        }else if(index >= RTSA_FDD_B1_DOWN_FREQPOINT_BASE && index <= RTSA_FDD_B1_DOWN_FREQPOINT_MAX)
        {
            freq = (index -RTSA_FDD_B1_DOWN_FREQPOINT_BASE)*RTSA_MHZ/10+ RTSA_FDD_B1_DOWN_FREQ_MIN;
        }else if(index >= RTSA_FDD_B3_UP_FREQPOINT_BASE && index <= RTSA_FDD_B3_UP_FREQPOINT_MAX)
        {
            freq = (index - RTSA_FDD_B3_UP_FREQPOINT_BASE)*RTSA_MHZ/10 + RTSA_FDD_B3_UP_FREQ_MIN;
        }else if(index >= RTSA_FDD_B3_DOWN_FREQPOINT_BASE && index <= RTSA_FDD_B3_DOWN_FREQPOINT_MAX)
        {
            freq = (index - RTSA_FDD_B3_DOWN_FREQPOINT_BASE)*RTSA_MHZ/10 + RTSA_FDD_B3_DOWN_FREQ_MIN;
        }
        break;
    }
    freq += gfreqOffset;
    return freq;
}

bool RtSa_User_Variable::IsFreqInCurChStd()
{
    bool InCurStd = false;
    if(gTecIndex < 0 || gFreqStandard->isEmpty())
        return InCurStd;
    qreal freq,min,max;
    qint32 direction,index;
    direction = gCommuDirection;
    freq = gCenterFreq;
    index = gCHIndex;
    if(direction == RTSA_UPLINK)
    {
        min = gFreqStandard->at(index).Up.Min * RTSA_MHZ;
        max = gFreqStandard->at(index).Up.Max * RTSA_MHZ;
    }
    else
    {
        min = gFreqStandard->at(index).Down.Min * RTSA_MHZ;
        max = gFreqStandard->at(index).Down.Max * RTSA_MHZ;
    }
    if(freq < min || freq > max)
    {
        InCurStd = false;
    }
    else
    {
        InCurStd = true;
    }
    return InCurStd;
}
void DpxDataRefresh(void *pAddr)
{
    if(!RTSA_DpxRefreshFlag)
    {
        return;
    }
    sm_rtsa_sweep_data->DpxData = (quint32*)pAddr;
    RTSA_DpxRefreshFlag = false;
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-04-24
*/
void RtSa_User_Variable::openDpxDevice()
{
    if(gDpxOpenFlag)
        return;
    qint32 iBack = -1;
    pthread_mutex_lock(&RTSA_lockobj);
    iBack = openDPXMem(&DpxHandle);
    if(iBack < 0)
    {
        setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,RTSA_DPX_MEM_OPEN);
        errorOutput();
    }
    iBack = registerDPXHandler(DpxHandle, DpxDataRefresh);
    if(iBack < 0)
    {
        setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,RTSA_APP_DPX_EPOLL_ENABLE);
        errorOutput();
    }
    RTSA_DpxRefreshFlag = true;
    gDpxOpenFlag = true;
    pthread_mutex_unlock(&RTSA_lockobj);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-04-24
*/
void RtSa_User_Variable::closeDpxDevice()
{
    if(!gDpxOpenFlag)
        return;
    qint32 iBack = -1;
    pthread_mutex_lock(&RTSA_lockobj);
    sm_rtsa_sweep_data->DpxData= NULL;
    gDpxOpenFlag = false;
    iBack = unregisterDPXHandler(DpxHandle);
    if(iBack < 0)
    {
        setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,RTSA_APP_DPX_EPOLL_DISABLE);
        errorOutput();
    }
    iBack = closeDPXMem(DpxHandle);
    if(iBack < 0)
    {
        setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,RTSA_APP_DPX_MEM_CLOSE);
        errorOutput();
    }
    RTSA_DpxRefreshFlag = false;
    pthread_mutex_unlock(&RTSA_lockobj);
    return;
}





