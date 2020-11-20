#include "rtsa_user_variable.h"
#include "rtsa_define.h"
#include <QDebug>
#include <QPixmap>
#include <QDir>
#include <QApplication>
#include <QDesktopWidget>
#include "rtsa_extern.h"
#include <qmath.h>

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

    gReadMeterDataSleepTime = RTSA_REFRESH_DEFAULT_TIME;

    gSweepTracePoint = RTSA_NUM_SWEEP_POINT;//501;

    //Freq
    gMeterParam.gConfig_FreqSpan.gCenterFreq = 5050000000LL;
    gMeterParam.gConfig_FreqSpan.gStartFreq = 5000000000LL;
    gMeterParam.gConfig_FreqSpan.gStopFreq = 5100000000LL;
    gMeterParam.gConfig_FreqSpan.gSpanFreq = 100000000LL;
    gMeterParam.gConfig_FreqSpan.gStepFreq = (gMeterParam.gConfig_FreqSpan.gStopFreq - gMeterParam.gConfig_FreqSpan.gStartFreq)/(gSweepTracePoint - 1);;
    gMeterParam.gConfig_FreqSpan.gOffsetFreq = 0;

    gMeterParam.gConfig_FreqSpan.channelStd = RTSA_CDMA - 1;
    gMeterParam.gConfig_FreqSpan.channelSelID = 0;
    gMeterParam.gConfig_FreqSpan.channelNumber = 0;
    gMeterParam.gConfig_FreqSpan.channelStep = mRTSA_ChStand[RTSA_CDMA].ChStep;
    gMeterParam.gConfig_FreqSpan.channelType = RTSA_UPLINK;

    //amplitude
    gMeterParam.gConfig_Amplitude.refLevel = -10.0;
    gMeterParam.gConfig_Amplitude.attenAuto = RTSA_AUTO;
    gMeterParam.gConfig_Amplitude.attenVal = 0.0;
    for(qint32 i = 0 ; i < RTSA_BITVIEWNUM ; i++)
    {
        gMeterParam.gConfig_Amplitude.scaleDiv[i] = 10.0;
        gMeterParam.gConfig_Amplitude.refOffset[i] = 0.;
        gMeterParam.gConfig_Amplitude.units[i] = RTSA_DBM;
    }
    gMeterParam.gConfig_Amplitude.preAmpStatus = RTSA_OFF;

    //sweep
    gMeterParam.gConfig_Sweep.sweepType = RTSA_CONT;
    gMeterParam.gConfig_Sweep.autoAcqtime = RTSA_AUTO;
    gMeterParam.gConfig_Sweep.acqTimeVal = RTSA_ACQ_DEFAULT_TIME;

    gMeterParam.gConfig_Sweep.autoPersistence = RTSA_FINITE;
    gMeterParam.gConfig_Sweep.persistenceVal = RTSA_PERSISTENCE_TIME;
    gMeterParam.gConfig_Sweep.highDensity = 100;
    gMeterParam.gConfig_Sweep.lowDensity = 0;
    gMeterParam.gConfig_Sweep.curveNum = 0;

    gRbwGrade = RTSA_SPAN_INTERVAL_NUMBER - 1;

    //BW
    gMeterParam.gConfig_BW.autoRbw = RTSA_ON;
    gMeterParam.gConfig_BW.rbwIndex = RTSA_RBW5;
    gMeterParam.gConfig_BW.fftFilter = RTSA_KAISER;
    gMeterParam.gConfig_BW.rbw = RTSA_RbwManualList[gMeterParam.gConfig_BW.fftFilter][gRbwGrade][gMeterParam.gConfig_BW.rbwIndex];

    //Trigger
    gMeterParam.gConfig_Trigger.triggerType = RTSA_TRIGGER_FREE_RUN;
    //Video trigger
    gMeterParam.gConfig_Trigger.triggerVideoSlope = 0;
    gMeterParam.gConfig_Trigger.triggerVideoLevel = -20.0;
    gMeterParam.gConfig_Trigger.triggerVideoDelayStatus = 0;
    gMeterParam.gConfig_Trigger.triggerVideoDelay = 0;

    //extern trigger
    gMeterParam.gConfig_Trigger.triggerExternSlope = 0;
    gMeterParam.gConfig_Trigger.triggerExternLevel = -20.0;
    gMeterParam.gConfig_Trigger.triggerExternDelayStatus = 0;
    gMeterParam.gConfig_Trigger.triggerExternDelay = 0;

    //period
    gMeterParam.gConfig_Trigger.triggerPeriodDelay = 0;
    gMeterParam.gConfig_Trigger.triggerPeriodDelayStatus = 0;
    gMeterParam.gConfig_Trigger.triggerPeriodTime = RTSA_HOLDOFF_TIME_MIN;

    //RF Burst
    gMeterParam.gConfig_Trigger.triggerRFSlope = 0;
    gMeterParam.gConfig_Trigger.triggerRFLevel = -20.0;
    gMeterParam.gConfig_Trigger.triggerRFDelayStatus = 0;
    gMeterParam.gConfig_Trigger.triggerRFDelay = 0;


    gMeterParam.gConfig_Trigger.triggerVideoHoldOff = RTSA_HOLDOFF_TIME_MIN;
    gMeterParam.gConfig_Trigger.triggerRFBurstHoldOff = RTSA_HOLDOFF_TIME_MIN;
    gMeterParam.gConfig_Trigger.triggerExternHoldOff = RTSA_HOLDOFF_TIME_MIN;
    gMeterParam.gConfig_Trigger.triggerFMTHoldOff = RTSA_HOLDOFF_TIME_MIN;

    //    gMeterParam.gConfig_Trigger.triggerSlope = 0;
    //    gMeterParam.gConfig_Trigger.maskType = globalUserVariable->gMaskType;
    //    gMeterParam.gConfig_Trigger.triggerCriteria = globalUserVariable->gMaskType;

    gMeterParam.gConfig_Trigger.fmtnumber = 0;
    for(qint32 i = 0; i < gMeterParam.gConfig_Trigger.fmtnumber; i++)
    {
        gMeterParam.gConfig_Trigger.fmtFreq[i] = 0;
        gMeterParam.gConfig_Trigger.fmtAmpt[i] = 0;
    }

    //Trace
    for(qint32 j = 0; j < RTSA_BITVIEWNUM; j++)
    {
        gMeterParam.gConfig_Trace.curTraceID[j] = RTSA_TR1;
        for(qint32 i = 0; i < RTSA_NUM_TRACE; i++)
        {
            gMeterParam.gConfig_Trace.Rtsa_Config_Trace[j][i].traceView = RTSA_TRACE_OFF;
            gMeterParam.gConfig_Trace.Rtsa_Config_Trace[j][i].traceType = RTSA_TRACE_OFF;
            gMeterParam.gConfig_Trace.Rtsa_Config_Trace[j][i].averageOn = RTSA_OFF;
            gMeterParam.gConfig_Trace.Rtsa_Config_Trace[j][i].averageCount = 10;
        }
        gMeterParam.gConfig_Trace.Rtsa_Config_Trace[j][0].traceType = RTSA_CLEAR_WRITE;
    }
    gMeterParam.gConfig_Trace.detectorType = RTSA_DEC_PEAK;
    gMeterParam.gConfig_Trace.Rtsa_Config_Trace[0][RTSA_TR1].traceType = RTSA_CLEAR_WRITE;

    //Marker
    for(qint32 j = 0; j < RTSA_BITVIEWNUM; j++)
    {
        gMeterParam.gConfig_Marker[j].curmarkerID = RTSA_M1;
        gMeterParam.gConfig_Marker[j].markerPeakTraceOn = RTSA_OFF;
        for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
        {
            gMeterParam.gConfig_Marker[j].gRtsa_Config_marker[i].markerView = RTSA_OFF;
            gMeterParam.gConfig_Marker[j].gRtsa_Config_marker[i].markerType = RTSA_REF;
            gMeterParam.gConfig_Marker[j].gRtsa_Config_marker[i].markerNoiseOn = RTSA_OFF;
            gMeterParam.gConfig_Marker[j].gRtsa_Config_marker[i].gMarkerRefFreq = gMeterParam.gConfig_FreqSpan.gCenterFreq;
            gMeterParam.gConfig_Marker[j].gRtsa_Config_marker[i].gMarkerRefAmpt = 0;
            gMeterParam.gConfig_Marker[j].gRtsa_Config_marker[i].gMarkerNormalPosY = 0;
        }
    }

    //Limit
    for(qint32 j = 0; j < RTSA_BITVIEWNUM; j++)
    {
        gMeterParam.gConfig_Limit[j].limitID = RTSA_LIMIT1;
        gMeterParam.gConfig_Limit[j].limitTest = RTSA_OFF;
        for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
        {
            gMeterParam.gConfig_Limit[j].limitOn[i] = RTSA_LIMIT_OFF;
            gMeterParam.gConfig_Limit[j].limitEdgeOn[i] = RTSA_OFF;
            gMeterParam.gConfig_Limit[j].limitEdgeVal[i] = 0;
            gMeterParam.gConfig_Limit[j].limitType[i] = RTSA_UPPER;
            gMeterParam.gConfig_Limit[j].limitEditNum[i] = 0;
            gMeterParam.gConfig_Limit[j].limitCurEditIndex[i] = 0;
            for(int k = 0;k< RTSA_NUM_SWEEP_POINT;k++)
            {
                gMeterParam.gConfig_Limit[j].limtData[i].limitFreq[k] = 0;
                gMeterParam.gConfig_Limit[j].limtData[i].limitAmpt[k] = 0;
            }
        }
    }
    gMeterParam.gConfig_Display.displayMode = 0;

    gSpanMode = RTSA_NORMAL_SPAN;

    gautoMintimems = 100.0;
    gMenu = RTSA_MENU_SPECTRUM_ANALYZER;
    entryInputMode = RTSA_NOT_USE;

    gspanChangebyFreq = 0;
    gbitsspan = RTSA_SPAN_MIN;
    gbithalfsspan = RTSA_SPAN_MIN / 2;
    grbwChangedbyFreq = 0;

    gAutoPersistenceTime = RTSA_INFINITE;
    gMaskType = RTSA_UPPER;

    gPersistenceTime = RTSA_PERSISTENCE_TIME;  //Tony 0905
    gHighestDensity = 100;
    gLowestDensity = 0;
    gCurve=0;
    gAutoAttenTrack = RTSA_MANUAL;
    gAutoVbw = RTSA_ON;


    gVbw = 3000000;
    gDetectorMode = RTSA_DEC_PEAK;

    gLastSpanFreq =  4000000000LL;

    gPowersensorFreq = 1000000000LL;
    gPowersensorExtOffset = 0.0;

    KeyNumber        = -1;
    gCHName = new QVector <QString>;
    gCHStandard = new QVector <__RTSA_Standard__>;
    gFreqStandard = new QVector <__RTSA_Standard__>;
    getBandInfo(gMeterParam.gConfig_FreqSpan.channelStd);
    adjustCHStandarByCerFreq(gMeterParam.gConfig_FreqSpan.gCenterFreq);
    gLocal = RTSA_LOCAL;
    gdpxApmtMin = -110.0;
    gdpxAmptZoom = 2.0;
    DpxHandle = -1;
    gDpxOpenFlag = false;
    memset(&gFmtData,0,sizeof(gFmtData));
    startMode = -1;

    gfmtType = 0;
    gfileType = -1;

    linkMode = -1;
    gLinkfileType = -1;
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
        //       qDebug() << "-------- i = " << i << "--"  << str1[i];
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
    gMeterParam.gConfig_BW.rbw = RTSA_RbwManualList[gMeterParam.gConfig_BW.fftFilter][gRbwGrade][gMeterParam.gConfig_BW.rbwIndex];
    return gMeterParam.gConfig_BW.rbw;
}

qint32 RtSa_User_Variable::adjustFreqBySpan(qreal freq)
{
    //Tony 0907
    gLastSpanFreq =  gMeterParam.gConfig_FreqSpan.gSpanFreq;
    gMeterParam.gConfig_FreqSpan.gSpanFreq = freq;

    if(gMeterParam.gConfig_FreqSpan.gCenterFreq - 0.5 * gMeterParam.gConfig_FreqSpan.gSpanFreq < RTSA_SPEC_FREQ_MIN)
    {
        gMeterParam.gConfig_FreqSpan.gStartFreq = RTSA_SPEC_FREQ_MIN;

        //Tony 0907
        //gMeterParam.gConfig_FreqSpan.gSpanFreq = (gMeterParam.gConfig_FreqSpan.gCenterFreq - SPEC_FREQ_MIN) * 2;
        //Tony 0907
        gMeterParam.gConfig_FreqSpan.gCenterFreq = gMeterParam.gConfig_FreqSpan.gStartFreq + 0.5*gMeterParam.gConfig_FreqSpan.gSpanFreq;
        gMeterParam.gConfig_FreqSpan.gStopFreq = gMeterParam.gConfig_FreqSpan.gStartFreq + gMeterParam.gConfig_FreqSpan.gSpanFreq;
    }
    else if(gMeterParam.gConfig_FreqSpan.gCenterFreq + 0.5 * gMeterParam.gConfig_FreqSpan.gSpanFreq > RTSA_SPEC_FREQ_MAX)
    {
        gMeterParam.gConfig_FreqSpan.gStopFreq = RTSA_SPEC_FREQ_MAX;
        //      gMeterParam.gConfig_FreqSpan.gSpanFreq = (SPEC_FREQ_MAX - gMeterParam.gConfig_FreqSpan.gCenterFreq) * 2;
        gMeterParam.gConfig_FreqSpan.gCenterFreq = gMeterParam.gConfig_FreqSpan.gStopFreq - 0.5*gMeterParam.gConfig_FreqSpan.gSpanFreq;
        gMeterParam.gConfig_FreqSpan.gStartFreq =  gMeterParam.gConfig_FreqSpan.gStopFreq - gMeterParam.gConfig_FreqSpan.gSpanFreq;
    }
    else
    {
        gMeterParam.gConfig_FreqSpan.gStartFreq = gMeterParam.gConfig_FreqSpan.gCenterFreq - 0.5 * gMeterParam.gConfig_FreqSpan.gSpanFreq;
        gMeterParam.gConfig_FreqSpan.gStopFreq = gMeterParam.gConfig_FreqSpan.gCenterFreq + 0.5 * gMeterParam.gConfig_FreqSpan.gSpanFreq;
    }
    return 1;
}

qint32 RtSa_User_Variable::adjustFreqByCer()
{
    if(gMeterParam.gConfig_FreqSpan.gCenterFreq >= RTSA_SPEC_FREQ_MAX)
    {
        gLastSpanFreq = gMeterParam.gConfig_FreqSpan.gSpanFreq;
        gspanChangebyFreq = 1;
        gMeterParam.gConfig_FreqSpan.gStopFreq   = RTSA_SPEC_FREQ_MAX;

        gMeterParam.gConfig_FreqSpan.gSpanFreq   = gbitsspan;
        gMeterParam.gConfig_FreqSpan.gStartFreq  = gMeterParam.gConfig_FreqSpan.gStopFreq  - gMeterParam.gConfig_FreqSpan.gSpanFreq;
        gMeterParam.gConfig_FreqSpan.gCenterFreq = gMeterParam.gConfig_FreqSpan.gStartFreq + gbithalfsspan;
    }
    else if(gMeterParam.gConfig_FreqSpan.gCenterFreq <= RTSA_SPEC_FREQ_MIN)
    {
        gLastSpanFreq =  gMeterParam.gConfig_FreqSpan.gSpanFreq;
        gspanChangebyFreq = 1;
        gMeterParam.gConfig_FreqSpan.gStartFreq  = RTSA_SPEC_FREQ_MIN;
        gMeterParam.gConfig_FreqSpan.gStopFreq   = gMeterParam.gConfig_FreqSpan.gStartFreq + gbitsspan;
        gMeterParam.gConfig_FreqSpan.gSpanFreq   = gbitsspan;
        gMeterParam.gConfig_FreqSpan.gCenterFreq = gMeterParam.gConfig_FreqSpan.gStartFreq + gbithalfsspan;
    }
    else
    {
        if(gMeterParam.gConfig_FreqSpan.gCenterFreq - 0.5 * gMeterParam.gConfig_FreqSpan.gSpanFreq < RTSA_SPEC_FREQ_MIN)
        {
            //change start freq and span and stop freq
            //save last span
            gLastSpanFreq =  gMeterParam.gConfig_FreqSpan.gSpanFreq;
            gspanChangebyFreq = 1;

            //Tony 0908
            gMeterParam.gConfig_FreqSpan.gStartFreq = RTSA_SPEC_FREQ_MIN;
            gMeterParam.gConfig_FreqSpan.gSpanFreq = (gMeterParam.gConfig_FreqSpan.gCenterFreq - RTSA_SPEC_FREQ_MIN) * 2;
            gMeterParam.gConfig_FreqSpan.gSpanFreq = adjustSpanToSmall(gMeterParam.gConfig_FreqSpan.gSpanFreq);
            gMeterParam.gConfig_FreqSpan.gCenterFreq=gMeterParam.gConfig_FreqSpan.gStartFreq+0.5*gMeterParam.gConfig_FreqSpan.gSpanFreq;
            gMeterParam.gConfig_FreqSpan.gStopFreq = gMeterParam.gConfig_FreqSpan.gStartFreq+gMeterParam.gConfig_FreqSpan.gSpanFreq;

            //Tony 0908 removed
            //          gMeterParam.gConfig_FreqSpan.gStartFreq = SPEC_FREQ_MIN;
            //          gMeterParam.gConfig_FreqSpan.gSpanFreq = (gMeterParam.gConfig_FreqSpan.gCenterFreq - SPEC_FREQ_MIN) * 2;
            //          gMeterParam.gConfig_FreqSpan.gStopFreq = gMeterParam.gConfig_FreqSpan.gStartFreq + gMeterParam.gConfig_FreqSpan.gSpanFreq;
        }
        else if(gMeterParam.gConfig_FreqSpan.gCenterFreq + 0.5 * gMeterParam.gConfig_FreqSpan.gSpanFreq > RTSA_SPEC_FREQ_MAX)
        {
            //change start freq and span and stop freq
            gLastSpanFreq =  gMeterParam.gConfig_FreqSpan.gSpanFreq;
            gspanChangebyFreq = 1;
            gMeterParam.gConfig_FreqSpan.gStopFreq = RTSA_SPEC_FREQ_MAX;
            gMeterParam.gConfig_FreqSpan.gSpanFreq = (RTSA_SPEC_FREQ_MAX - gMeterParam.gConfig_FreqSpan.gCenterFreq) * 2;
            //Tony 0910
            gMeterParam.gConfig_FreqSpan.gSpanFreq =   adjustSpanToSmall(gMeterParam.gConfig_FreqSpan.gSpanFreq);
            gMeterParam.gConfig_FreqSpan.gCenterFreq=  gMeterParam.gConfig_FreqSpan.gStopFreq - 0.5*gMeterParam.gConfig_FreqSpan.gSpanFreq;
            gMeterParam.gConfig_FreqSpan.gStartFreq =  gMeterParam.gConfig_FreqSpan.gStopFreq - gMeterParam.gConfig_FreqSpan.gSpanFreq;
        }
        else
        {
            //change start and stop freq
            gspanChangebyFreq = 0;
            gMeterParam.gConfig_FreqSpan.gStartFreq = gMeterParam.gConfig_FreqSpan.gCenterFreq - 0.5 * gMeterParam.gConfig_FreqSpan.gSpanFreq;
            gMeterParam.gConfig_FreqSpan.gStopFreq = gMeterParam.gConfig_FreqSpan.gCenterFreq + 0.5 * gMeterParam.gConfig_FreqSpan.gSpanFreq;
        }
    }
    return 1;
}

qint32 RtSa_User_Variable::adjustFreqByStart(void)
{
    //save last span
    gLastSpanFreq =  gMeterParam.gConfig_FreqSpan.gSpanFreq;
    //Tony 0910
    gMeterParam.gConfig_FreqSpan.gStartFreq = gMeterParam.gConfig_FreqSpan.gStartFreq < RTSA_SPEC_FREQ_MIN ? RTSA_SPEC_FREQ_MIN : gMeterParam.gConfig_FreqSpan.gStartFreq;

    //steve,0503 change > to >=
    if(gMeterParam.gConfig_FreqSpan.gStartFreq >= gMeterParam.gConfig_FreqSpan.gStopFreq)
    {
        gMeterParam.gConfig_FreqSpan.gSpanFreq = gbitsspan;
        gMeterParam.gConfig_FreqSpan.gStopFreq = gMeterParam.gConfig_FreqSpan.gStartFreq + gbitsspan;
        if( gMeterParam.gConfig_FreqSpan.gStopFreq > RTSA_SPEC_FREQ_MAX)
        {
            gMeterParam.gConfig_FreqSpan.gStopFreq = RTSA_SPEC_FREQ_MAX;
            gMeterParam.gConfig_FreqSpan.gStartFreq = gMeterParam.gConfig_FreqSpan.gStopFreq - gbitsspan;
        }
        gMeterParam.gConfig_FreqSpan.gCenterFreq = gMeterParam.gConfig_FreqSpan.gStartFreq + gbithalfsspan;
    }
    else
    {
        //Tony 0910
        if(gMeterParam.gConfig_FreqSpan.gStartFreq+gMeterParam.gConfig_FreqSpan.gSpanFreq>RTSA_SPEC_FREQ_MAX)
        {
            if(gMeterParam.gConfig_FreqSpan.gStartFreq+gbitsspan>RTSA_SPEC_FREQ_MAX)
            {
                gMeterParam.gConfig_FreqSpan.gStopFreq  =  RTSA_SPEC_FREQ_MAX;
                gMeterParam.gConfig_FreqSpan.gSpanFreq  =  gbitsspan;
                gMeterParam.gConfig_FreqSpan.gCenterFreq = gMeterParam.gConfig_FreqSpan.gStopFreq - 0.5 * gMeterParam.gConfig_FreqSpan.gSpanFreq;
                gMeterParam.gConfig_FreqSpan.gStartFreq  = gMeterParam.gConfig_FreqSpan.gStopFreq - gMeterParam.gConfig_FreqSpan.gSpanFreq;
            }else
            {
                gMeterParam.gConfig_FreqSpan.gStopFreq  =  RTSA_SPEC_FREQ_MAX;
                gMeterParam.gConfig_FreqSpan.gSpanFreq  =  gMeterParam.gConfig_FreqSpan.gStopFreq - gMeterParam.gConfig_FreqSpan.gStartFreq;
                gMeterParam.gConfig_FreqSpan.gSpanFreq  =  adjustSpanToSmall(gMeterParam.gConfig_FreqSpan.gSpanFreq);
                gMeterParam.gConfig_FreqSpan.gCenterFreq = gMeterParam.gConfig_FreqSpan.gStopFreq - 0.5 * gMeterParam.gConfig_FreqSpan.gSpanFreq;
                gMeterParam.gConfig_FreqSpan.gStartFreq  = gMeterParam.gConfig_FreqSpan.gStopFreq - gMeterParam.gConfig_FreqSpan.gSpanFreq;

            }
        }else
        {
            gMeterParam.gConfig_FreqSpan.gSpanFreq  =  gMeterParam.gConfig_FreqSpan.gStopFreq - gMeterParam.gConfig_FreqSpan.gStartFreq;
            gMeterParam.gConfig_FreqSpan.gSpanFreq  =  adjustSpanToSmall(gMeterParam.gConfig_FreqSpan.gSpanFreq);
            gMeterParam.gConfig_FreqSpan.gCenterFreq = gMeterParam.gConfig_FreqSpan.gStartFreq + 0.5 * gMeterParam.gConfig_FreqSpan.gSpanFreq;
            gMeterParam.gConfig_FreqSpan.gStopFreq  = gMeterParam.gConfig_FreqSpan.gStartFreq + gMeterParam.gConfig_FreqSpan.gSpanFreq;
        }
    }
    return 1;
}

qint32 RtSa_User_Variable::adjustFreqByStop(void)
{
    gLastSpanFreq =  gMeterParam.gConfig_FreqSpan.gSpanFreq;
    gMeterParam.gConfig_FreqSpan.gStopFreq = gMeterParam.gConfig_FreqSpan.gStopFreq > RTSA_SPEC_FREQ_MAX ? RTSA_SPEC_FREQ_MAX : gMeterParam.gConfig_FreqSpan.gStopFreq;
    //by steve,0503,change < to <=
    if(gMeterParam.gConfig_FreqSpan.gStopFreq <= gMeterParam.gConfig_FreqSpan.gStartFreq)
    {
        gMeterParam.gConfig_FreqSpan.gSpanFreq = gbitsspan;
        gMeterParam.gConfig_FreqSpan.gStartFreq = gMeterParam.gConfig_FreqSpan.gStopFreq - gbitsspan;
        if( gMeterParam.gConfig_FreqSpan.gStartFreq < RTSA_SPEC_FREQ_MIN)
        {
            gMeterParam.gConfig_FreqSpan.gStartFreq = RTSA_SPEC_FREQ_MIN;
            gMeterParam.gConfig_FreqSpan.gStopFreq = gMeterParam.gConfig_FreqSpan.gStartFreq + gbitsspan;
        }
        gMeterParam.gConfig_FreqSpan.gCenterFreq = gMeterParam.gConfig_FreqSpan.gStartFreq + gbithalfsspan;
    }
    else
    {
        //Tony 0910
        if(gMeterParam.gConfig_FreqSpan.gStopFreq-gMeterParam.gConfig_FreqSpan.gSpanFreq<RTSA_SPEC_FREQ_MIN)
        {
            if(gMeterParam.gConfig_FreqSpan.gStopFreq-gbitsspan<=RTSA_SPEC_FREQ_MIN)
            {
                gMeterParam.gConfig_FreqSpan.gStartFreq  =  RTSA_SPEC_FREQ_MIN;
                gMeterParam.gConfig_FreqSpan.gSpanFreq  =  gbitsspan;
                gMeterParam.gConfig_FreqSpan.gCenterFreq = gMeterParam.gConfig_FreqSpan.gStartFreq + 0.5 * gMeterParam.gConfig_FreqSpan.gSpanFreq;
                gMeterParam.gConfig_FreqSpan.gStopFreq  = gMeterParam.gConfig_FreqSpan.gStartFreq + gMeterParam.gConfig_FreqSpan.gSpanFreq;
            }else
            {
                gMeterParam.gConfig_FreqSpan.gStartFreq  =  RTSA_SPEC_FREQ_MIN;
                gMeterParam.gConfig_FreqSpan.gSpanFreq  =  gMeterParam.gConfig_FreqSpan.gStopFreq - gMeterParam.gConfig_FreqSpan.gStartFreq;
                gMeterParam.gConfig_FreqSpan.gSpanFreq  =  adjustSpanToSmall(gMeterParam.gConfig_FreqSpan.gSpanFreq);
                gMeterParam.gConfig_FreqSpan.gCenterFreq = gMeterParam.gConfig_FreqSpan.gStartFreq + 0.5 * gMeterParam.gConfig_FreqSpan.gSpanFreq;
                gMeterParam.gConfig_FreqSpan.gStopFreq  = gMeterParam.gConfig_FreqSpan.gStartFreq + gMeterParam.gConfig_FreqSpan.gSpanFreq;
            }
        }else
        {
            gMeterParam.gConfig_FreqSpan.gSpanFreq  =  gMeterParam.gConfig_FreqSpan.gStopFreq-gMeterParam.gConfig_FreqSpan.gStartFreq;
            gMeterParam.gConfig_FreqSpan.gSpanFreq  =  adjustSpanToSmall(gMeterParam.gConfig_FreqSpan.gSpanFreq);
            gMeterParam.gConfig_FreqSpan.gCenterFreq = gMeterParam.gConfig_FreqSpan.gStopFreq - 0.5 * gMeterParam.gConfig_FreqSpan.gSpanFreq;
            gMeterParam.gConfig_FreqSpan.gStartFreq  = gMeterParam.gConfig_FreqSpan.gStopFreq - gMeterParam.gConfig_FreqSpan.gSpanFreq;
        }

    }
    return 1;
}

void RtSa_User_Variable::stepFreqCalculatorFunc()
{
    qreal startFreq = gMeterParam.gConfig_FreqSpan.gStartFreq;
    qreal stopFreq = gMeterParam.gConfig_FreqSpan.gStopFreq;

    gMeterParam.gConfig_FreqSpan.gStepFreq = (stopFreq - startFreq) / (gSweepTracePoint - 1);
}

void RtSa_User_Variable::checkRbwVbwBySpanFunc()
{
    qint32 retNo;
    qint32 retValidity;
    quint32 currentArrayVal = 0;
    quint32 beforeArrayVal = 0;
    quint32 currentDiffVal = 0;
    quint32 beforeDiffVal = 0;
    qint32 i;

    if (gMeterParam.gConfig_BW.autoRbw == RTSA_ON) {

        // Span 으로 적용할 RBW 위치 찾아 오기
        retNo = searchIndexSpanRbwVbwAutoGabFunc(gMeterParam.gConfig_FreqSpan.gSpanFreq);

        qDebug() << "retno => " <<  retNo;

        // 그 위치에 해당하는 RBW 값을 적용
        gMeterParam.gConfig_BW.rbw = RTSA_u32SpanRbwVbwAutoTable[retNo];

        qDebug() << " gRbw => " <<  gMeterParam.gConfig_BW.rbw;

    } else {

        // Span 으로 적용할 RBW Table 위치 찾아 오기
        retNo = searchIndexSpanRbwVbwManTableFunc(gMeterParam.gConfig_FreqSpan.gSpanFreq);

        qDebug() << "retno => " <<  retNo;

        // 현재 RBW 값이 현재 Span에서 유효한 값인지 확인
        retValidity = searchIndexRbwVbwManValidityFunc(RTSA_RBW, retNo, gMeterParam.gConfig_BW.rbw);

        switch (retValidity) {
        case RTSA_VALID_BW:
            break;
        case RTSA_INVALID_BW:
            for (i = 0; i < RTSA_NUM_RBW_VBW_MAN_VARIETY; i++) {
                currentArrayVal = RTSA_u32SpanRbwManTable[retNo][i];
                qDebug() << "i / currentArrayVal = " << i  << " / "<<  currentArrayVal;
                if (gMeterParam.gConfig_BW.rbw  < currentArrayVal) {
                    qDebug() << "in";
                    beforeArrayVal = RTSA_u32SpanRbwManTable[retNo][i-1];
                    currentDiffVal = currentArrayVal - gMeterParam.gConfig_BW.rbw;
                    beforeDiffVal = gMeterParam.gConfig_BW.rbw - beforeArrayVal;

                    if (currentDiffVal <= beforeDiffVal)  // 가까운 값으로 할당하기 위함
                        gMeterParam.gConfig_BW.rbw = currentArrayVal;
                    else
                        gMeterParam.gConfig_BW.rbw = beforeArrayVal;
                    break;
                }
            }

            if (i  == RTSA_NUM_RBW_VBW_MAN_VARIETY)
                gMeterParam.gConfig_BW.rbw = searchIndexRbwVbwMaxFunc(RTSA_RBW, retNo);

            break;
        default:
            qDebug() << "Error RBW setting!!!";
            break;
        }
        qDebug() << " gRbw => " <<  gMeterParam.gConfig_BW.rbw;



        // VBW ---------------------------------------------------------------------------
        if (gAutoVbw == RTSA_OFF)  {
            // 현재 Span에 따른 사용 가능한 VBW Table 찾기..
            retNo = searchIndexSpanRbwVbwManTableFunc(gMeterParam.gConfig_FreqSpan.gSpanFreq);

            // 현재 VBW 값이 현재 Span에서 유효한 값인지 확인..
            //int SearchIndex_RbwVbwManValidity(u64 span)
            retValidity = searchIndexRbwVbwManValidityFunc(RTSA_VBW, retNo, gVbw);

            //          retValidity = searchIndexRbwVbwManValidityFunc(_VBW, retNo, MainUserVariable.gVbw);

            switch (retValidity) {
            case RTSA_VALID_BW:
                // RBW 그대로 유효함.
                //ptSMConfig->csweep.RBWSet = ptSMConfig->csweep.RBWSet
                checkVbwUnderRbw();
                break;
            case RTSA_INVALID_BW:
                for (i = 0; i < RTSA_NUM_RBW_VBW_MAN_VARIETY; i++) {
                    currentArrayVal = RTSA_u32SpanRbwManTable[retNo][i];
                    qDebug() << "i / currentArrayVal = " << i  << " / "<<  currentArrayVal;
                    if (gVbw  < currentArrayVal) {
                        qDebug() << "in";
                        beforeArrayVal = RTSA_u32SpanRbwManTable[retNo][i-1];
                        currentDiffVal = currentArrayVal - gVbw;
                        beforeDiffVal = gVbw - beforeArrayVal;

                        if (currentDiffVal <= beforeDiffVal)  // 가까운 값으로 할당하기 위함
                            gVbw = currentArrayVal;
                        else
                            gVbw = beforeArrayVal;
                        break;
                    }
                }

                if (i  == RTSA_NUM_RBW_VBW_MAN_VARIETY)
                    gVbw = searchIndexRbwVbwMaxFunc(RTSA_VBW, retNo);

                checkVbwUnderRbw();
                break;
            default:
                qDebug() << "Error RBW setting!!!";
                break;
            }
        }  else  {      //if (ptSMConfig->csweep.VBWAuto == VBW_AUTO)
            gVbw = gMeterParam.gConfig_BW.rbw;
        }
    }



}

void RtSa_User_Variable::checkVbwUnderRbw()
{
    if (gVbw > gMeterParam.gConfig_BW.rbw) {
        qDebug() << "Check VBW > RBW!!!";
        gMeterParam.gConfig_BW.rbw = gVbw;
    }
}

quint32 RtSa_User_Variable::searchIndexRbwVbwMaxFunc(qint32 type,qint32 pos)
{
    quint32 retNo = 0;

    switch (type)    {
    case RTSA_RBW:
        retNo = RTSA_u32SpanRbwManTable[pos][RTSA_NUM_RBW_VBW_MAN_VARIETY - 2];
        break;
    case RTSA_VBW:
        // RBW, VBW Table 같음
        retNo = RTSA_u32SpanRbwManTable[pos][RTSA_NUM_RBW_VBW_MAN_VARIETY - 2];
        break;
    }
    return retNo;
}

qint32 RtSa_User_Variable::searchIndexRbwVbwManValidityFunc(qint32 type, qint32 pos, quint32 bw)
{
    quint32 retNo;
    quint32 *ptr = NULL;

    switch (type) {
    case RTSA_RBW:
        // void *bsearch(const void *key, const void *base, size_t nel, size_t width, int (*compare)(const void *, const void *));
        ptr = ( quint32 *)bsearch(&bw, &RTSA_u32SpanRbwManTable[pos][0], RTSA_NUM_RBW_VBW_MAN_VARIETY, sizeof(quint32), RbwVbwCompare);
        break;
    case RTSA_VBW:
        // VBW Manual Table이 RBW Manual Table과 같다. 2015-04-08
        // void *bsearch(const void *key, const void *base, size_t nel, size_t width, int (*compare)(const void *, const void *));
        ptr = (quint32 *)bsearch(&bw, &RTSA_u32SpanRbwManTable[pos][0], RTSA_NUM_RBW_VBW_MAN_VARIETY, sizeof(quint32), RbwVbwCompare);
        break;
    }

    if (ptr == NULL)  {
        retNo = RTSA_INVALID_BW;		// 10 MHz .. 임시 에러 값..
    }   else  {
        retNo = RTSA_VALID_BW;
    }

    return retNo;

}

qint32 RtSa_User_Variable::searchIndexSpanRbwVbwAutoGabFunc(qreal span)
{
    qint32 i = 0;

    for (i = 0; i < RTSA_NUM_RBW_VBW_AUTO_SPAN_BOUNDARY; i++) {
        if (span <= RTSA_u64RbwVbwAutoSpanBoundary[i]) {
            break;
        }
    }

    if (i == RTSA_NUM_RBW_VBW_AUTO_SPAN_BOUNDARY) {
        qDebug() << "Invalid Span";
    }

    return i;

}

qint32 RtSa_User_Variable::searchIndexSpanRbwVbwManTableFunc(qreal span)
{

    qint32 i = 0;

    for (i = 0; i < RTSA_NUM_RBW_VBW_MAN_SPAN_BOUNDARY; i++) {
        if (span <= RTSA_u64RbwVbwManSpanBoundary[i]) {
            break;
        }
    }

    if (i == RTSA_NUM_RBW_VBW_MAN_SPAN_BOUNDARY) {
        qDebug() << "Invalid Span";
    }

    return i;
}

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
    channelSTD = gMeterParam.gConfig_FreqSpan.channelStd;
    freq = gMeterParam.gConfig_FreqSpan.gCenterFreq;
    direction = gMeterParam.gConfig_FreqSpan.channelType;
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
                gMeterParam.gConfig_FreqSpan.channelStd =i;
                gMeterParam.gConfig_FreqSpan.channelSelID = j;
                gMeterParam.gConfig_FreqSpan.channelNumber = CalculateChannelNum();
                gMeterParam.gConfig_FreqSpan.channelStep = mRTSA_ChStand[i].ChStep;
                gMeterParam.gConfig_FreqSpan.channelType = RTSA_UPLINK;
                return;
            }else if(freq>=gFreqStandard->at(j).Down.Min && freq<=gFreqStandard->at(j).Down.Max)
            {
                gMeterParam.gConfig_FreqSpan.channelStd =i;
                gMeterParam.gConfig_FreqSpan.channelSelID = j;
                gMeterParam.gConfig_FreqSpan.channelNumber = CalculateChannelNum();
                gMeterParam.gConfig_FreqSpan.channelStep = mRTSA_ChStand[i].ChStep;
                gMeterParam.gConfig_FreqSpan.channelType = RTSA_DOWNLINK;
                return;
            }
        }
    }
    gMeterParam.gConfig_FreqSpan.channelSelID = 0;
    gMeterParam.gConfig_FreqSpan.channelStd = -1;
    return;
}
qreal RtSa_User_Variable::adjustFreqByCHStandar()
{
    if(gMeterParam.gConfig_FreqSpan.channelStd < 0 || gFreqStandard->isEmpty())
        return gMeterParam.gConfig_FreqSpan.gCenterFreq;
    qreal freq,min,max;
    qint32 direction,index;
    direction = gMeterParam.gConfig_FreqSpan.channelType;
    freq = gMeterParam.gConfig_FreqSpan.gCenterFreq;
    index = gMeterParam.gConfig_FreqSpan.channelSelID;
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
    freq += gMeterParam.gConfig_FreqSpan.gOffsetFreq;
    return freq;
}
qreal RtSa_User_Variable::adjustFreqByCHNum(qint32 index)
{
    qint32 channelSTD,direction;
    qreal freq;
    channelSTD = gMeterParam.gConfig_FreqSpan.channelStd;
    direction = gMeterParam.gConfig_FreqSpan.channelType;
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
    freq += gMeterParam.gConfig_FreqSpan.gOffsetFreq;
    return freq;
}

bool RtSa_User_Variable::IsFreqInCurChStd()
{
    bool InCurStd = false;
    if(gMeterParam.gConfig_FreqSpan.channelStd < 0 || gFreqStandard->isEmpty())
        return InCurStd;
    qreal freq,min,max;
    qint32 direction,index;
    direction = gMeterParam.gConfig_FreqSpan.channelType;
    freq = gMeterParam.gConfig_FreqSpan.gCenterFreq;
    index = gMeterParam.gConfig_FreqSpan.channelSelID;
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
{/*
    if(!RTSA_DpxRefreshFlag)
    {
        return;
    }*/
    //    sm_rtsa_sweep_data->DpxData = (quint32*)pAddr;
    //    RTSA_DpxRefreshFlag = false;
    return;
}




