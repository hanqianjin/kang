/****************************************Copyright (c)****************************************************
**
**                                     INNO Instrument(China) Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                sa_user_variable.cpp
** Latest Version:           V1.0.0
** Created by:               Johnson
** Created date:             2018/12/05
** Descriptions:             the class which used to define the global parameters
**
*********************************************************************************************************/

#include <QApplication>
#include <QPixmap>
#include <QDesktopWidget>
#include <QImageWriter>
#include <QDir>
#include <QFile>
#include <QObject>
#include <math.h>

#include "sa_user_variable.h"
#include "sa_user_limit.h"
#include <QDebug>
#include "define.h"
#include "sa_stdafx.h"
#include "msgNoticeCode.h"

/**
 * @brief user_variable::user_variable
 * @note  initialize user_variable parameters
 */
user_variable::user_variable()
{
    gChannelNumStep = 1;
    //**********************************************Related with Paint
    for(qint32 i = 0;i<GRIDX_LENGTH;i++)
    {
        gridXPos[i] = 0;    // 0~10, 11개
        gridYPos[i] = 0;
    }
    bSmallCanvas = true;
    mDrawWidth = 1;
    mDrawHeight = 1;
    //**********************************************Related with Shm
    //gSharedMemoryInit = 0;

    //**********************************************Related with Sweep
    gsweepAuto       = 1;//1 auto 0 man
    gautoMintimems   = 100.0;//this param should decided last,and whatever auto or man mode should calc it all;
    gmanSettimems    = 100.0;
    gfirsingletimems = 0.002;
    ganamode         = 0;
    gSweepTracePoint = NUM_SWEEP_POINT;//501;
    gSweepType       = SA_CONT;
    gSweepTime       = 11.04;
    gAutoSweepTime   = SA_ON;//Johnson 0718
    gcheckswitch     = 0;//0 check,1 without check,
    goldcheckswitch  = 0;
    gTriggerMode     = SA_TRIGGER_FREE_RUN;
#if 0
    gSweepSpeed      = SA_NORMAL;
#endif

    gTriggerPerTimer = 20;
    for(qint32 i = 0;i < TRIGGER_SOURCE_CNT;i++)
    {
        gTriggerLevel[i] = 20;
        gTriggerSlope[i] = 0;
        gTriggerDelayStatus[i] = SA_OFF; // SA_ON SA_OFF
        gTriggerDelayValue[i] = 0.;
    }

    //**********************************************Related with Trace
    gTracePoint    = NUM_SWEEP_POINT;//POINT_501;
    gTraceStepSize = (qreal)  SMALLDRAW_GRID_WIDTH /  (qreal)  (gSweepTracePoint - 1);
    gTraceSelect   = TR1;

    for(qint32 i = 0;i<NUM_TRACE;i++)
    {
        gViewAction[i]    = SA_OFF;
        gTraceType[i] = SA_CLEAR_WRITE;
        gTraceTypeChangeStatus[i] = 0;
        //        if(i == 0) gTraceType[i] = SA_CLEAR_WRITE;
        //        else gTraceType[i] = SA_TRACE_OFF;
        gTraceAverage[i] = SA_OFF;//Johnson 1114
        gAverageCount[i] = 10;  // User가 입력하는 Average Count
        gAverageNo[i]    = 0;    // Trace Average On시 1 부터 순차적으로 증가 (gAverageCount 설정까지)
        greAvager[i]     = 1;
        if(i == 0) gTraceView[i] = SA_ON;
        else gTraceView[i] = SA_OFF;
    }
    gDetectorMode    = SA_COMMON;
    //Johnson 191218
    gTmpDetectorMode = gDetectorMode;

    memset(gOriginalMeasureVal,0.,sizeof(qreal)*NUM_SWEEP_POINT);
    memset(gTraceTempVal,0.,sizeof(qreal)*NUM_SWEEP_POINT);
    for(qint32 i = 0;i<NUM_TRACE;i++)
    {
        for(qint32 j = 0;j<NUM_SWEEP_POINT;j++)
        {
            gBitTraceAverage[i][j] = 0.;
            gTraceMeasureVal[i][j] = 0.;
            gTraceViewDate[i][j]   = 0.;
        }
    }
    traceSusFlag = 0;
    //**********************************************Related with Freq/Span
    gStartFreq        = 2600000000LL;
    gStopFreq         = 7500000000LL;
    gCenterFreq       = 5050000000LL;
    gSpanFreq         = 4900000000LL;
    gSpanMode         = NORMAL_SPAN;
    gCFFreq           = 1000000LL;
    gStepFreq         =  (qreal)(gStopFreq - gStartFreq) / (gSweepTracePoint - 1);
    gspanChangebyFreq = 0;
    gbitsspan         = 10;//such as start freq larger than stop freq,means span is 10 Hz
    gbithalfsspan     = 5;
    gZeroSpanTime     = 100.;
    gLastSpanFreq     = 4000000000LL; // Last Span Freq 저장
    gZeroSpanAction   = SA_OFF;    // Zero Span Flag

    //**********************************************Related with Amplitude
    gRefLevel         = 0.;
    gScaleDiv         = 10.;
    gAmptdUnit        = SA_DBM;
    gAttenValue       = 10.; //Johnson Add
    gRefOffset        = 0.;
    gPreamp           = SA_OFF;//Johnson 1010 change
    gAtten            = SA_AUTO;//Johnson Add
    topLevel = gRefLevel + gRefOffset;
    lowLevel = topLevel - GRID_NUM_Y_TICKS*gScaleDiv;
    gAutoAttenTrack  = SA_OFF;//Johnson 1112

    //Johnson 190410
    gZeroRestrainAtten = 0.;
    gZeroRestrainPhase = 0.;
#if 0
    //**********************************************Related with DPX
    totalCount1 = 0LL;
    totalCount2 = 0LL;
    totalCount3 = 0LL;
    totalCount4 = 0LL;
    totalCount5 = 0LL;
    totalCount6 = 0LL;
    for(qint32 i = 0;i<NUM_SWEEP_POINT;i++)
    {
        for(qint32 j = 0;j<SMALLDRAW_GRID_HEIGHT;j++)
        {
            density_Trace1[i][j]  = 0.;
            density_Trace2[i][j]  = 0.;
            density_Trace3[i][j]  = 0.;
            density_Trace4[i][j]  = 0.;
            density_Trace5[i][j]  = 0.;
            density_Trace6[i][j]  = 0.;
            hitCount_Trace1[i][j] = 0;
            hitCount_Trace2[i][j] = 0;
            hitCount_Trace3[i][j] = 0;
            hitCount_Trace4[i][j] = 0;
            hitCount_Trace5[i][j] = 0;
            hitCount_Trace6[i][j] = 0;
        }
    }
    memset(gDpxData,0,sizeof(quint32)*DPX_LENGHT);
#endif

    //**********************************************Related with Marker
    gMarkerSelect  = SA_M1;      // 선택된 Marker
    gMarkerDisplay = MKR_TABLE;
    memset(gMarkerView,SA_OFF,sizeof(qint32)*MARKER_TOTAL_CNT);
    memset(gMarkerType,REF,sizeof(qint32)*MARKER_TOTAL_CNT);
    memset(gMarkerRefFreq,0,sizeof(qint64)*MARKER_TOTAL_CNT);

    memset(gMarkerRefTime,0.0,sizeof(qreal)*MARKER_TOTAL_CNT);
    memset(gMarkerDeltaTime,0.0,sizeof(qreal)*MARKER_TOTAL_CNT);

    memset(gMarkerRefPos,0,sizeof(qint32)*MARKER_TOTAL_CNT);
    memset(gMarkerDeltaFreq,0,sizeof(qint64)*MARKER_TOTAL_CNT);
    memset(gMarkerDeltaPos,0,sizeof(qint32)*MARKER_TOTAL_CNT);
    memset(gMarkerNoise,SA_OFF,sizeof(qint32)*MARKER_TOTAL_CNT);
    memset(gMarkerNoiseValue,0.,sizeof(qreal)*MARKER_TOTAL_CNT);
    gMarkerFreqCount = SA_OFF;

    gMarkerCompensation = 0;

    //**********************************************Related with SA_BW
    gVbwtoRbw         = 1.0;
    gAutoVbwtoRbw     = 1;
    gAutoRbw          = SA_ON;
    gAutoVbw          = SA_ON;
    gRbw              = 5000000;
    gVbw              = 3000000;
    grbwChangedbyFreq = 0;

    //**********************************************Related with peak
    gPeakTrack        = SA_OFF;//Johnson 1112

    //**********************************************Related with Measure
    //gDemodulationType = SA_AM;
    gOccupied_BW      = 99.00;
    gXdB              = -26.00;
    gOcc              = SA_OCCUPIED;
    gChannelBandwidth = 2000000LL;
    gChannelSpacing   = 3000000LL;
    dPowerValue       = 0.;
    dPowerValue_ACPL  = 0.;
    dPowerValue_ACPM  = 0.;
    dPowerValue_ACPR  = 0.;
    dTotalPower       = 0.;
    uOccupiedBW       = 0;
    uXdBBW            = 0;
    dPowerValue_MultiACPM  = 0.;
    dPowerValue_MultiACPFL = 0.;
    dPowerValue_MultiACPL  = 0.;
    dPowerValue_MultiACPFR = 0.;
    dPowerValue_MultiACPR  = 0.;
    dPSD                   = 0.;

    gHighestCHFreq = 500000000LL;
    gLowestCHFreq = 300000000LL;
    gMultiACPSpacing = 100000000LL;
    gMainIntegBW = 50000000LL;
    gADJIntegBW = 50000000LL;
    gALTIntegBW = 50000000LL;

    //**********************************************Related with other(unused)
#if 0
    gMenu               = SA_MENU_SPECTRUM_ANALYZER;

    for(qint32 i = 0;i<TR_AVERAGE;i++)
    {
        for(qint32 j = 0;j<NUM_SWEEP_POINT;j++)
        {
            gTrace1AvgArray[i][j] = 0.;
            gTrace2AvgArray[i][j] = 0.;
            gTrace3AvgArray[i][j] = 0.;
            gTrace4AvgArray[i][j] = 0.;
            gTrace5AvgArray[i][j] = 0.;
            gTrace6AvgArray[i][j] = 0.;
        }
    }

    gImageRejection       = SA_OFF;
    gPowersensorFreq      = 1000000000LL;
    gPowersensorExtOffset = 0.0;
#endif

    gCurrentWorkState     = SA_DISPLAY_DIALOG;

    FullStatus         = false;
    pbLeftHideChecked  = false;
    gDisplayMode = 0;
    //************************************************Related with other
    bShiftKeyPressed = false;//Johnson 0611
    //KeyNumber        = -1;//Johnson 0611
    PrimaryAction    = SA_SWEEP;
    SecondaryAction  = SA_SPAN;//SA_SPAN,SA_NOT_USE
    currentMode = SA_SPAN_MODE;
    ReadParamFromFile = 0;
    //lastMode    = -1;
    gMarkerRefDelta = 0;
    RefreshTime = TIME_DEFAULT;
    gCHIndex = 0;
    gTecIndex = SA_CDMA;
    gCHName = new QVector <QString>;
    gCHStandard = new QVector <__Standard__>;
    gFreqStandard = new QVector <__Standard__>;

    gRunMode = SA_LOCAL;
    gLockStatus = 0;
    gIgnoreLimit = 0;
    gAutoRepeat  = 0;
    gSpecEMDisplay = 0;
    gSpecEMRefType = 0;
    gSpecEMInteBW = 3840000;//3.84 MHz
    for(qint32 i = 0;i<SA_SPECEM_FREQ_CNT;i++)
    {
        gSpecEMData[i] = mSpecEM_5GNR_CategoryA[i];//mSpecEM[i];//Johnson 20200427
        gSpecEMViewStatus[i] = SA_ON;
    }

    for(qint32 i = 0;i<(2*SA_SPECEM_FREQ_CNT);i++)
    {
        gSpecEMTestResult[i] = SA_PASS;
    }

    gSpecEMBsPower = 38.0;
    gSpecEMRefChBw = 100000000LL;
    gSpecEMMaskType = SA_SPECEM_5GNR_CATEGORYA;//SA_SPECEM_DEFAULT;//Johnson 20200427
    gSpecEMSweepIndex = 0;
    gMeasureStatus = 0;
    gMsComplete = 0;
    getBandInfo(gTecIndex);
    gCommuDirection = SA_DOWNLINK;//Johnson 20200515
    adjustCHStandarByCerFreq(gCenterFreq);

    //Johnson 0425
    uIFMode = SA_AUTO_IFMODE;
#if 0
    uIFRef  = SA_INT_10M_REFINPUT;
    uBrtLevel = SA_BRTLEVEL1;
#endif
    gFreqReference = SA_FREQREF_INTERNAL;

    //Johnson 190523
    startMode = 0;
    startPreset = -1;

    gSpurEMReportType = SA_SPUREM_REPORT_ALL;
    gSpurEMCurRangeIndex = 0;
    gSpurEMCurDrawRangeIndex = 0;
    gSpurEMTotalSpurCnt = 0;
    gMsFirstFlag = 1;
    gSpurEMTableMode = SA_SPUREM_MEASURE;
    gSpurEMAveType = SA_SPUREM_AVE_EXP;
    for(qint32 i =0;i<SPUR_EM_DATE_MAX;i++)
    {
        gSpurEMPara[i].index = mSpurEM[i].index;
        gSpurEMPara[i].startFreq = mSpurEM[i].startFreq;
        gSpurEMPara[i].stopFreq=mSpurEM[i].stopFreq;
        gSpurEMPara[i].RBW=mSpurEM[i].RBW;
        gSpurEMPara[i].VBW=mSpurEM[i].VBW;

#if !SPUREMODIFY
        gSpurEMPara[i].SweepTime=mSpurEM[i].SweepTime;
        gSpurEMPara[i].peakDefi=mSpurEM[i].peakDefi;
        gSpurEMPara[i].peakThreshold=mSpurEM[i].peakThreshold;
        gSpurEMPara[i].Atten=mSpurEM[i].Atten;
#endif
        gSpurEMPara[i].startLimit=mSpurEM[i].startLimit;
        gSpurEMPara[i].stopLimit=mSpurEM[i].stopLimit;
        gSpurEMViewStatus[i] = SA_OFF;
        gSpurEMSpurCnt[i] = 0;

    }
    for(qint32 i=0;i<5;i++)
    {
        gSpurEMViewStatus[i] = SA_ON;
    }

    memset(gSpurEMSpur,0.,sizeof(__SPUR_POINT__)*SA_SPUREM_RANGE_CNT*SA_SPUREM_SPUR_CNT);
    gSpecEMRefRbw = 300000;
    gFsr = 0;
    gFreqCount = 0;
    calData = 0.;
    gSignalFreq = gCenterFreq;

    uTmpRbw = gRbw;
    gIFOutputSpanModeChange = 0;

    gDotSweepTime = gfirsingletimems;
    gAutoDotSweepTime = SA_AUTO;

    gFixDotSweepTime = SA_ON;

    loadFileType = SA_STATE;

    /*********Door Control Sweep Interface*************/
    gLvlEdgSelect       = SA_EDGE_MODE;
    gLvlEdgMode         = SA_POSITIVE_VALUE;
    gDrCtrlSweepMode    = SA_LO_DCSWEEPMODE;
    gDrCtrlSwitch       = SA_CLOSE_DCSWEEP;
    gEdgTrigDely        = 5.;
    gEdgTrigDoorWdth    = 1.;
    gEdgTrigPrvntStatus = SA_CLOSE_PRVTSTATUS;
    gEdgTrigPrvntTimes  = 0.;
    gDrCtrlRbw          = gRbw;
    gRFBurstTrigLevel   = 0.;
#if AFTERGATESWEEPCHANGED
    gDrCtrlSource       = SA_PERIOD_TRIGGER;
#else
    gDrCtrlSource       = -1;
#endif
    gPrdTrgSynchroSrc   = SA_NO_SYCHRNOSOURCE;
    gPrdTrgPeriod       = 20.;
    gPrdTrgSrcDelay     = 0.;
    gPrdTrigPrvntStatus = SA_CLOSE_PRVTSTATUS;
    gPrdTrigPrvntTimes  = 0.;
    gGateViewStatus     = SA_GATE_VIEW_CLOSE;
    gGateViewStartTime  = 0.;

    gGateSweepSpanChange = 0;

    //Johnson 0513
    gridWidth = 1;
}
// 설정된 값의 0이 아닌 위치를 끝에서 부터 찾아오기
qint32 user_variable::notZeroPositionFindFunc(QString strGab)
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

QString user_variable::freqDotNumberDisplayFormatFixFunc(qreal freqVal, qint32 unitNo, qint32 numberLen)
{
    QString strValue;
    QString retStrValue;
    qreal unitGab = 0.;
    QString unitStr;
    qint32 minus = 0;
    if(freqVal < 0)
    {
        minus = 1;
        freqVal = freqVal * -1;
    }


    // numberLen  => 소숫점 뒤 0이 아닌 길이
    switch (unitNo) {
    case UNIT_GHZ:
        unitGab = (qreal) SA_GHZ;
        unitStr = QString("GHz");

        switch (numberLen) {
        case 0:
        case 1:
        case 2:
            strValue.sprintf("%.2f", (qreal) freqVal / unitGab);
            break;
        case 3:
            strValue.sprintf("%.3f", (qreal) freqVal / unitGab);
            break;
        case 4:
            strValue.sprintf("%.4f", (qreal) freqVal / unitGab);
            break;
        case 5:
            strValue.sprintf("%.5f", (qreal) freqVal / unitGab);
            break;
        case 6:
            strValue.sprintf("%.6f", (qreal) freqVal / unitGab);
            break;
        case 7:
            strValue.sprintf("%.7f", (qreal) freqVal / unitGab);
            break;
        case 8:
            strValue.sprintf("%.8f", (qreal) freqVal / unitGab);
            break;
        case 9:
        default:
            strValue.sprintf("%.9f", (qreal) freqVal / unitGab);
            break;
        }
        break;
    case UNIT_MHZ:
        unitGab = (qreal) SA_MHZ;
        unitStr = QString("MHz");

        switch (numberLen) {
        case 0:
        case 1:
        case 2:
            strValue.sprintf("%.2f", (qreal) freqVal / unitGab);
            break;
        case 3:
            strValue.sprintf("%.3f", (qreal) freqVal / unitGab);
            break;
        case 4:
            strValue.sprintf("%.4f", (qreal) freqVal / unitGab);
            break;
        case 5:
            strValue.sprintf("%.5f", (qreal) freqVal / unitGab);
            break;
        case 6:
        default:
            strValue.sprintf("%.6f", (qreal) freqVal / unitGab);
            break;
        }

        break;
    case UNIT_KHZ:
        unitGab = (qreal) SA_KHZ;
        unitStr = QString("kHz");

        switch (numberLen) {
        case 0:
        case 1:
        case 2:
            strValue.sprintf("%.2f", (qreal) freqVal / unitGab);
            break;
        case 3:
        default:
            strValue.sprintf("%.3f", (qreal) freqVal / unitGab);
            break;
        }
        break;
    case UNIT_HZ:
        unitGab = (qreal) SA_HZ;
        unitStr = QString("Hz");
        strValue.sprintf("%.1f", (qreal) freqVal / unitGab);
        break;
    }
    QRegExp rx;
    rx.setPattern("(\\.){0,1}0+$");
    if(strValue!="0")
    {
        strValue.replace(rx,"");
    }
    retStrValue = QString("%1 %2").arg(strValue).arg(unitStr);
    if(minus)
    {
        retStrValue = QString("-%1").arg(retStrValue);
    }
    return retStrValue;

}

QString user_variable::timeDotNumberDisplayFormatFixFunc(qreal _timeVal, qint32 unitNo, qint32 numberLen)
{
    QString strValue;
    QString retStrValue;
    qreal unitGab = 0.;
    QString unitStr;


    // numberLen  => 소숫점 뒤 0이 아닌 길이
    switch (unitNo) {
    case UNIT_NS:
        unitGab = (qreal) SA_GHZ;
        unitStr = QString("ns");

        strValue.sprintf("%.0f", (qreal) _timeVal / unitGab);
        break;
    case UNIT_US:
        unitGab = (qreal) SA_MHZ;
        unitStr = QString("us");

        strValue.sprintf("%.0f", (qreal) _timeVal / unitGab);
        break;
    case UNIT_MS:
        //0713
        if(_timeVal >= 1000.0)
        {
            unitStr = QString("s");
            strValue.sprintf("%f",_timeVal / 1000.);
        }
        else
        {
            unitStr = QString("ms");
            strValue.sprintf("%f", (qreal) _timeVal);
        }
        break;
    case UNIT_S:
        unitStr = QString("s");

        switch (numberLen) {
        case 0:
            strValue.sprintf("%.2f",  _timeVal );
            break;
        case 1:
            strValue.sprintf("%.1f",  _timeVal);
            break;
        case 2:
        default:
            strValue.sprintf("%.0f",  _timeVal);
            break;
        }
        break;
    }


    retStrValue = QString("%1 %2").arg(strValue).arg(unitStr);

    return retStrValue;

}

void user_variable::createInputDialogMakeFunc(QWidget *_widget, QString inputTitle, qint32 entryNo)
{
    qint32 unitNo = 0;
    long long deltaFreq = 0;

    switch (entryNo) {
    case SA_INPUT_FREQ_CENTER:
        unitNo = freqUnitFindProc(gCenterFreq);
        break;
    case SA_INPUT_FREQ_START:
        unitNo = freqUnitFindProc(gStartFreq);
        break;
    case SA_INPUT_FREQ_STOP:
        unitNo = freqUnitFindProc(gStopFreq);
        break;
    case SA_INPUT_FREQ_CF:
        unitNo = freqUnitFindProc(gCFFreq);
        qDebug() << "CF FREQ   ==  unitNo" << unitNo;
        break;
    case SA_INPUT_FREQ_SPAN:
        unitNo = freqUnitFindProc(gSpanFreq);
        qDebug() << "Span   ==  unitNo" << unitNo;
        break;
    case SA_INPUT_MANUAL_RBW:
        unitNo = freqUnitFindProc(gRbw);
        break;
    case SA_INPUT_MANUAL_VBW:
        unitNo = freqUnitFindProc(gVbw);
        break;
    case SA_INPUT_SWEEP_TIME:
        //unitNo = freqUnitFindProc(gSweepTime);
        unitNo = 3;
        break;
    case SA_INPUT_MARKER_EDIT:
        unitNo = freqUnitFindProc(gMarkerRefFreq[ gMarkerSelect] );
        qDebug() << "Marker Edit   ==  unitNo" << unitNo;
        break;
    case SA_INPUT_DELTA_MARKER_EDIT:
        unitNo = freqUnitFindProc(gMarkerDeltaFreq[ gMarkerSelect] - gMarkerRefFreq[gMarkerSelect] );
        deltaFreq = gMarkerDeltaFreq[ gMarkerSelect] - gMarkerRefFreq[ gMarkerSelect];
        qDebug() << "delta --------------  " << deltaFreq;
        if (deltaFreq < 0) deltaFreq *= -1;
        qDebug() << "delta --------------  " << deltaFreq;
        unitNo = freqUnitFindProc(deltaFreq );
        qDebug() << "Delta Edit   ==  unitNo" << unitNo;
        break;
    case SA_INPUT_CHANNEL_BANDWIDTH:
        unitNo = freqUnitFindProc(gChannelBandwidth);
        break;
    case SA_INPUT_CHANNEL_SPACING:
        unitNo = freqUnitFindProc(gChannelSpacing);
        break;
    case SA_INPUT_POWERSENSOR_FREQ:
        //unitNo = freqUnitFindProc(gPowersensorFreq);
        break;
    }
}

void user_variable::createInputAmptdDialogMakeFunc(QWidget *_widget, QString inputTitle, qint32 entryNo)
{

}

qint32 user_variable::freqUnitFindProc(quint64 _freq)
{
    if (_freq >= SA_GHZ)
        return UNIT_GHZ;
    else if (_freq >= SA_MHZ)
        return UNIT_MHZ;
    else if (_freq >= SA_KHZ)
        return UNIT_KHZ;
    else
        return UNIT_HZ;
}

qint32 user_variable::adjustFreqBySpan(quint64 freq)
{

    //Jonson 1123
    //    if(SPEC_FREQ_MAX - SPEC_AMPTD_MIN < freq) freq = SPEC_AMPTD_MAX - SPEC_AMPTD_MIN;
    //if(0 == gSpanFreq - freq) return 0;

    gLastSpanFreq =  gSpanFreq;
    gSpanFreq = freq;
    if(gCenterFreq - 0.5 * gSpanFreq < SPEC_FREQ_MIN)
    {
        gStartFreq = SPEC_FREQ_MIN;
        gSpanFreq = (gCenterFreq - SPEC_FREQ_MIN) * 2;
        gStopFreq = gStartFreq + gSpanFreq;
    }
    else if(gCenterFreq + 0.5 * gSpanFreq > SPEC_FREQ_MAX)
    {
        gStopFreq = SPEC_FREQ_MAX;
        gSpanFreq = (SPEC_FREQ_MAX - gCenterFreq) * 2;
        gStartFreq =  gStopFreq - gSpanFreq;
    }
    else
    {
        gStartFreq = gCenterFreq - 0.5 * gSpanFreq;
        gStopFreq = gCenterFreq + 0.5 * gSpanFreq;
    }

    return 1;
}

qint32 user_variable::adjustFreqByCer()
{
    if(gCenterFreq >= SPEC_FREQ_MAX - 5)//Johnson 1128
    {
        gLastSpanFreq =  gSpanFreq;
        gspanChangebyFreq = 1;
        gStopFreq = SPEC_FREQ_MAX;
        gSpanFreq = gbitsspan;
        gStartFreq =  gStopFreq -  gSpanFreq;
        gCenterFreq = gStartFreq + gbithalfsspan;
    }
    else if(gCenterFreq <= SPEC_FREQ_MIN + 5)//Johnson 1128
    {
        gLastSpanFreq =  gSpanFreq;
        gspanChangebyFreq = 1;
        gStartFreq = SPEC_FREQ_MIN;
        gStopFreq = gStartFreq + gbitsspan;
        gSpanFreq = gbitsspan;
        gCenterFreq = gStartFreq + gbithalfsspan;
    }
    else
    {
        if(gCenterFreq - 0.5 * gSpanFreq < SPEC_FREQ_MIN)
        {
            //change start freq and span and stop freq
            //save last span
            gLastSpanFreq =  gSpanFreq;
            gspanChangebyFreq = 1;
            gStartFreq = SPEC_FREQ_MIN;
            gSpanFreq = (gCenterFreq - SPEC_FREQ_MIN) * 2;
            gStopFreq = gStartFreq + gSpanFreq;
        }
        else if(gCenterFreq + 0.5 * gSpanFreq > SPEC_FREQ_MAX)
        {
            //change start freq and span and stop freq
            gLastSpanFreq =  gSpanFreq;
            gspanChangebyFreq = 1;
            gStopFreq = SPEC_FREQ_MAX;
            gSpanFreq = (SPEC_FREQ_MAX - gCenterFreq) * 2;
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

qint32 user_variable::adjustFreqByStart(void)
{
    //save last span
    gLastSpanFreq = gSpanFreq;
    //steve,0503 change > to >=
    if(gStartFreq >= gStopFreq)
    {
        gSpanFreq = gbitsspan;
        gStopFreq = gStartFreq + gbitsspan;
        if( gStopFreq > SPEC_FREQ_MAX)
        {
            gStopFreq = SPEC_FREQ_MAX;
            gStartFreq = gStopFreq - gbitsspan;
        }
        gCenterFreq = gStartFreq + gbithalfsspan;
    }
    else
    {
        gStartFreq = gStartFreq < SPEC_FREQ_MIN ? SPEC_FREQ_MIN : gStartFreq;
        gSpanFreq = gStopFreq - gStartFreq > gbitsspan ? gStopFreq - gStartFreq : gbitsspan;
        gCenterFreq = gStartFreq + 0.5 * gSpanFreq;
    }

//    quint64 tmpF = gStopFreq;
//    tmpF = gStartFreq;
    return 1;
}

qint32 user_variable::adjustFreqByStop(void)
{
    gLastSpanFreq =  gSpanFreq;

    gStopFreq = gStopFreq < gbitsspan ? gbitsspan : gStopFreq;
    //by steve,0503,change < to <=
    if(gStopFreq <= gStartFreq)
    {
        gSpanFreq = gbitsspan;
        gStartFreq = gStopFreq - gbitsspan;

        if( gStartFreq < SPEC_FREQ_MIN)
        {
            gStartFreq = SPEC_FREQ_MIN;
        }
        gStopFreq = gStartFreq + gbitsspan;
        gCenterFreq = gStartFreq + gbithalfsspan;
    }
    else
    {
        gStopFreq = gStopFreq > SPEC_FREQ_MAX ? SPEC_FREQ_MAX : gStopFreq;
        //gSpanFreq = gStopFreq - gStartFreq;
        gSpanFreq = gStopFreq - gStartFreq > gbitsspan ? gStopFreq - gStartFreq : gbitsspan;
        gCenterFreq = gStartFreq + 0.5 * gSpanFreq;
    }
    return 1;
}

qint32 user_variable::converFreqToShm(void)
{
    SA_sm_config_sweep->CenterFreq = (qreal) gCenterFreq;
#if USABLE
    SA_sm_config_sweep->SpanFreq = (qreal) gSpanFreq;
#endif
    SA_sm_config_sweep->StartFreq = (qreal) gStartFreq;
    SA_sm_config_sweep->StopFreq = (qreal) gStopFreq;
    return 1;
}

qint32 user_variable::convertBwToShm(void)
{
    SA_sm_config_sweep->RBW = gRbw ;
#if USABLE
    SA_sm_config_sweep->RBWAuto = gAutoRbw;
#endif
    SA_sm_config_sweep->VBW = gVbw;
#if USABLE
    SA_sm_config_sweep->VBWAuto = gAutoVbw;

    SA_sm_config_sweep->VBWTORBW = gVbwtoRbw;
    SA_sm_config_sweep->VBWTORBWAuto = gAutoVbwtoRbw;
#endif
    return 1;
}


qint32 user_variable::spanSettingCompareProcess(quint64 freq)
{
    //changed by Steve,0228
    //adjust param
    //save last span

    return adjustFreqBySpan(freq);

#if 0
    quint64 tempStartFreq = 0;
    quint64 tempStopFreq = 0;
    quint64 tempSpanFreq = 0;



    tempSpanFreq =(quint64) ((qreal) freq / 2.);

    tempStartFreq = (gCenterFreq - tempSpanFreq);
    tempStopFreq = (gCenterFreq + tempSpanFreq);

    if (SPEC_FREQ_MIN > tempStartFreq ) return 0;
    if (SPEC_FREQ_MAX < tempStopFreq ) return 0;

    gLastSpanFreq =  gSpanFreq;
    gZeroSpanAction = SA_OFF;


    gSpanFreq = freq;
    qDebug() << "freq => " << freq;
    gStartFreq = tempStartFreq;
    gStopFreq = tempStopFreq;


    return 1;
#endif

#if 0
    quint64 startFreqInterval = 0;
    quint64 stopFreqInterval = 0;
    quint64 calculatorFreq = 0;

    startFreqInterval = (gCenterFreq - gStartFreq);
    stopFreqInterval = (gStopFreq - gCenterFreq);

    if (startFreqInterval < stopFreqInterval){
        calculatorFreq = startFreqInterval * 2;
    } else {
        calculatorFreq = stopFreqInterval * 2;
    }

    if (calculatorFreq >= freq)
    {
        gSpanFreq = freq;
        qDebug() << "freq => " << freq;
        gStartFreq = gCenterFreq - (gSpanFreq / 2);
        gStopFreq = gCenterFreq + (gSpanFreq / 2);
    }
    else {
        return 0;
    }

    return 1;
#endif

}

void user_variable::stepFreqCalculatorFunc()
{
    quint64 startFreq = gStartFreq;
    quint64 stopFreq = gStopFreq;

    gStepFreq = (qreal)(stopFreq - startFreq) / (gSweepTracePoint - 1);
    return;
}


void user_variable::markerSettingInitFunc()
{
    qint32 i = 0;
    quint64 calFreq = 0;
    stepFreqCalculatorFunc();  //Step Frequency 계산
    calFreq = gStepFreq * (quint64 ) ((gSweepTracePoint - 1) / 2);

    for (i = 0; i < MARKER_TOTAL_CNT; i++) {
        gMarkerRefFreq[i] = gStartFreq +  calFreq ;
        gMarkerDeltaFreq[i]= gMarkerRefFreq[i];
        gMarkerRefPos[i] =  (qint32) (gSweepTracePoint / 2 );
        gMarkerDeltaPos[i] = gMarkerRefPos[i];
        gMarkerView[i] = SA_OFF;
        gMarkerType[i] = REF;
    }
    gMarkerDisplay = MKR_ONLY;
}
void user_variable::centerFreqSettingFunc()
{

    //quint64 startFreqInterval = 0;
    //quint64 stopFreqInterval = 0;

    //atten,this part has problem,change by Steve,0228
    //adjustFreqByCerAndSpan(gCenterFreq);
#if 0
    startFreqInterval = (gCenterFreq - gStartFreq);
    stopFreqInterval = (gStopFreq - gCenterFreq);

    if (startFreqInterval < stopFreqInterval) {
        gSpanFreq = startFreqInterval * 2;
        gStopFreq = gCenterFreq + startFreqInterval;
    } else {
        gSpanFreq = stopFreqInterval * 2;
        gStartFreq = gCenterFreq - stopFreqInterval;
    }

    stepFreqCalculatorFunc();
#endif
    //gStepFreq = (gStopFreq - gStartFreq) / (gTracePoint - 1);

    qDebug() << "[centerFreqSettingFunc] gStepFreq => " << gStepFreq;

}

void user_variable::markerEditInNputMarkerPosCalculatorFunc(qint64 freq, qint32 InputType)
{
    qint32 i = 0;
    quint64 calculatorFreq = 0;
    qint64 vigeoFreq = 0;

    if (InputType == REF) {
        //Marker 주파수가 Start Freq 같음
        if (freq == gStartFreq)  {
            gMarkerRefFreq[gMarkerSelect] = gStartFreq;
            gMarkerRefPos[gMarkerSelect] = 0;
        } else if (freq == gStopFreq) {
            gMarkerRefFreq[gMarkerSelect] = gStopFreq;
            gMarkerRefPos[gMarkerSelect] = gSweepTracePoint - 1;
        } else {

            // Marker Edit Pos Cal
            for (i = 0; i < (gSweepTracePoint + 1); i++)  {
                calculatorFreq = gStepFreq * i;
                vigeoFreq  = gStartFreq + calculatorFreq ;

                if (vigeoFreq >= freq) {
                    gMarkerRefPos[gMarkerSelect] = i;
                    gMarkerRefFreq[gMarkerSelect] = freq;
                    break;
                }
            }
        }
    } else {
        //Marker 주파수가 Start Freq 같음
        if (freq == gStartFreq)  {
            gMarkerDeltaFreq[gMarkerSelect] = gStartFreq;
            gMarkerDeltaPos[gMarkerSelect] = 0;
        } else if (freq == gStopFreq) {
            gMarkerDeltaFreq[gMarkerSelect] = gStopFreq;
            gMarkerDeltaPos[gMarkerSelect] = gSweepTracePoint - 1;
        } else {

            // Marker Edit Pos Cal
            for (i = 0; i < (gSweepTracePoint + 1); i++)  {
                calculatorFreq = gStepFreq * i;
                vigeoFreq  = gStartFreq + calculatorFreq ;

                if (vigeoFreq >= freq) {
                    gMarkerDeltaPos[gMarkerSelect] = i;
                    gMarkerDeltaFreq[gMarkerSelect] = freq;
                    break;
                }
            }
        }
    }
}
//Tony 190710
void user_variable::markerEditZeroSpanMarkerPosCalculatorFunc(qreal time, qint32 InputType)
{
    qint32 i = 0;
    qreal steptime = gSweepTime/(gSweepTracePoint - 1);
    quint64 markerFreq = 0;
    quint64 deltamarkerFreq = 0;

    if (InputType == REF) {
        //Marker 주파수가 Start Freq 같음
        if (time <= 0)
        {
            gMarkerRefTime[gMarkerSelect] = 0;
            gMarkerRefPos[gMarkerSelect] = 0;
        } else if (time >= gSweepTime)
        {
            gMarkerRefTime[gMarkerSelect] = gSweepTime;
            gMarkerRefPos[gMarkerSelect] = gSweepTracePoint - 1;
        } else {
            // Marker Edit Pos Cal
            for (i = 0; i < (gSweepTracePoint + 1); i++)  {
                if (steptime * i >= time)
                {
                    gMarkerRefPos[gMarkerSelect] = i;
                    gMarkerRefTime[gMarkerSelect] = time;
                    break;
                }
            }
        }
    } else {
        //Marker 주파수가 Start Freq 같음
        if (time <= 0)
        {
            gMarkerDeltaTime[gMarkerSelect] = 0;
            gMarkerDeltaPos[gMarkerSelect] = 0;
        }
        else if (time >= gSweepTime)
        {
            gMarkerDeltaTime[gMarkerSelect] = gSweepTime;
            gMarkerDeltaPos[gMarkerSelect] = gSweepTracePoint - 1;
        } else {
            // Marker Edit Pos Cal
            for (i = 0; i < (gSweepTracePoint + 1); i++)  {
                if (steptime * i >= time) {
                    gMarkerDeltaPos[gMarkerSelect] = i;
                    gMarkerDeltaTime[gMarkerSelect] = time;
                    break;
                }
            }
        }
    }
}

void user_variable::markerValueToTime(void)
{
    qreal   freqstep = gLastSpanFreq/(gTracePoint - 1);
    qreal   timestep = gSweepTime/(gTracePoint - 1);

    if(!freqstep) return;

    for(qint32 i=0;i<MARKER_TOTAL_CNT;i++)
    {
        gMarkerRefTime[i] = timestep * (gMarkerRefFreq[i]/freqstep);
        gMarkerDeltaTime[i] = timestep * (gMarkerDeltaFreq[i]/freqstep);
    }
}

void user_variable::markerValueToFreq(qreal timestep)
{
    if(!timestep) return;

    qreal   freqstep = gSpanFreq/(gTracePoint - 1);
    for(qint32 i=0;i<MARKER_TOTAL_CNT;i++)
    {
        gMarkerRefFreq[i] = gStartFreq + freqstep * (gMarkerRefTime[i]/timestep);
        gMarkerDeltaFreq[i] =gStartFreq +  freqstep * (gMarkerDeltaTime[i]/timestep);
    }
}
void user_variable::markerPositionReCalculatorFunc(void)
{
    qint32 i = 0;
    qint32 k = 0;
    qreal calculatorFreq = 0;
    qreal vigeoFreq = 0;
    qreal freq = 0;
    qreal deltaMarkerFreq = 0;
    qreal   timestep = gSweepTime/(gTracePoint - 1);


    // Marker - Marker to Center 실행시에는 전체적으로 Marker Pos를 다시 계산해야함
    for (i = 0; i < MARKER_TOTAL_CNT; i++)
    {
        if(!gSpanMode)
        {
            if (gMarkerType[i] == DELTA || gMarkerType[i] == DELTA_PAIR)
            {
                deltaMarkerFreq = gMarkerDeltaFreq[i];
                //Marker 주파수가 Start Freq 같음
                if (deltaMarkerFreq <= gStartFreq)
                {
                    //gMarkerDeltaFreq[i] = gStartFreq;  //Tony 190709
                    gMarkerDeltaPos[i] = 0;
                }
                else if (deltaMarkerFreq >= gStopFreq)
                {
                    //gMarkerDeltaFreq[i] = gStopFreq;   //Tony 190709
                    gMarkerDeltaPos[i] = gSweepTracePoint - 1;
                }
                else
                {
                    //gMarkerDeltaPos[i] = (deltaMarkerFreq - gStartFreq)/gStepFreq;
                    // Marker Edit Pos Cal
                    for (k = 0; k < (gSweepTracePoint + 1); k++)
                    {
                        calculatorFreq = gStepFreq * k;
                        vigeoFreq  = gStartFreq + calculatorFreq ;

                        if (vigeoFreq >= deltaMarkerFreq)
                        {
                            gMarkerDeltaPos[i] = k;
                            gMarkerDeltaFreq[i] = deltaMarkerFreq;
                            break;
                        }
                    }
                }

                //Tony 190709
                freq = gMarkerRefFreq[i];
                //Marker 주파수가 Start Freq 같음
                if (freq <= gStartFreq)
                {
                    //gMarkerRefFreq[i] = gStartFreq;
                    gMarkerRefPos[i] = 0;

                }
                else if (freq >= gStopFreq)
                {
                    //gMarkerRefFreq[i] = gStopFreq;
                    gMarkerRefPos[i] = gSweepTracePoint - 1;
                }
                else
                {
                    //gMarkerRefPos[i] = (freq - gStartFreq)/gStepFreq;
                    qDebug() << "[markerPositionReCalculatorFunc] gStepFreq => " << gStepFreq;
                    // Marker Edit Pos Cal
                    for (k = 0; k < (gSweepTracePoint + 1); k++)
                    {
                        calculatorFreq = gStepFreq * k;
                        vigeoFreq  = gStartFreq + calculatorFreq ;
                        if (vigeoFreq >= freq)
                        {
                            gMarkerRefPos[i] = k;
                            gMarkerRefFreq[i] = freq;
                            break;
                        }
                    }
                }
            }
            else
            {
                freq = gMarkerRefFreq[i];
                //Marker 주파수가 Start Freq 같음
                if (freq <= gStartFreq)
                {
                    gMarkerRefFreq[i] = gStartFreq;
                    gMarkerRefPos[i] = 0;

                }
                else if (freq >= gStopFreq)
                {
                    gMarkerRefFreq[i] = gStopFreq;
                    gMarkerRefPos[i] = gSweepTracePoint - 1;
                }
                else
                {
                    //gMarkerRefPos[i] = (freq - gStartFreq)/gStepFreq;
                    qDebug() << "[markerPositionReCalculatorFunc] gStepFreq => " << gStepFreq;
                    // Marker Edit Pos Cal
                    for (k = 0; k < (gSweepTracePoint + 1); k++)
                    {
                        calculatorFreq = gStepFreq * k;
                        vigeoFreq  = gStartFreq + calculatorFreq ;
                        if (vigeoFreq >= freq)
                        {
                            gMarkerRefPos[i] = k;
                            gMarkerRefFreq[i] = freq;
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            if (gMarkerType[i] == DELTA || gMarkerType[i] == DELTA_PAIR)
            {
                deltaMarkerFreq = gMarkerDeltaTime[i];
                //Marker 주파수가 Start Freq 같음
                if (deltaMarkerFreq <= 0)
                {
                    //gMarkerDeltaTime[i] = 0;  //Tony 190709
                    gMarkerDeltaPos[i] = 0;
                }
                else if (deltaMarkerFreq >= gSweepTime)
                {
                    //gMarkerDeltaTime[i] = gSweepTime;   //Tony 190709
                    gMarkerDeltaPos[i] = gSweepTracePoint - 1;
                }
                else
                {
                    for (k = 0; k < (gSweepTracePoint + 1); k++)
                    {
                        if (timestep * k >= deltaMarkerFreq)
                        {
                            gMarkerDeltaPos[i] = k;
                            gMarkerDeltaTime[i] = deltaMarkerFreq;
                            break;
                        }
                    }
                }

                //Tony 190709
                freq = gMarkerRefTime[i];
                //Marker 주파수가 Start Freq 같음
                if (freq <= 0)
                {
                    //gMarkerRefFreq[i] = gStartFreq;
                    gMarkerRefPos[i] = 0;

                }
                else if (freq >= gSweepTime)
                {
                    //gMarkerRefFreq[i] = gStopFreq;
                    gMarkerRefPos[i] = gSweepTracePoint - 1;
                }
                else
                {
                    // Marker Edit Pos Cal
                    for (k = 0; k < (gSweepTracePoint + 1); k++)
                    {
                        if (timestep * k >= freq)
                        {
                            gMarkerRefPos[i] = k;
                            gMarkerRefTime[i] = freq;
                            break;
                        }
                    }
                }
            }
            else
            {
                freq = gMarkerRefTime[i];
                //Marker 주파수가 Start Freq 같음
                if (freq <= 0)
                {
                    gMarkerRefTime[i] = 0;
                    gMarkerRefPos[i] = 0;

                }
                else if (freq >= gSweepTime)
                {
                    gMarkerRefTime[i] = gSweepTime;
                    gMarkerRefPos[i] = gSweepTracePoint - 1;
                }
                else
                {
                    qDebug() << "[markerPositionReCalculatorFunc] gStepFreq => " << gStepFreq;
                    // Marker Edit Pos Cal
                    for (k = 0; k < (gSweepTracePoint + 1); k++)
                    {
                        if (timestep * k >= freq)
                        {
                            gMarkerRefPos[i] = k;
                            gMarkerRefTime[i] = freq;
                            break;
                        }
                    }
                }
            }
        }
    }
    SA_guiDrawSet.peakPos = (qint32) (gSweepTracePoint / 2);
}

void user_variable::checkRbwWithStart70MHz()
{
    if ((gStartFreq <= (70 mMHz)) && (gSpanFreq > (5 mMHz)))  {
        // RBW 30 kHz 일 때, 가능한 최대 Span은 250 MHz 임.
        if (gSpanFreq > (250 mMHz))       {
            gSpanFreq = (250 mMHz);
            gCenterFreq = gStartFreq + (gSpanFreq / 2);
            gStopFreq = gStartFreq +gSpanFreq;

            qDebug() << "If Start<=70 MHz, RBW<=30 kHz";
        }

        if (gRbw > (30 mkHz * RVM)) {
            gAutoRbw = SA_OFF;
            gRbw = (30 mkHz * RVM);

            checkRbwVbwBySpanFunc();

            qDebug() << "If Start<=70 MHz, RBW<=30 kHz";
        }
    }
}

void user_variable::checkRbwVbwBySpanFunc()
{
    qint32 retNo;
    qint32 retValidity;
    quint32 currentArrayVal = 0;
    quint32 beforeArrayVal = 0;
    quint32 currentDiffVal = 0;
    quint32 beforeDiffVal = 0;
    qint32 i;

    if (gAutoRbw == SA_ON) {

        // Span 으로 적용할 RBW 위치 찾아 오기
        retNo = searchIndexSpanRbwVbwAutoGabFunc(gSpanFreq);

        qDebug() << "retno => " <<  retNo;

        // 그 위치에 해당하는 RBW 값을 적용
        gRbw = u32SpanRbwVbwAutoTable[retNo];

        qDebug() << " gRbw => " <<  gRbw;

    } else {

        // Span 으로 적용할 RBW Table 위치 찾아 오기
        retNo = searchIndexSpanRbwVbwManTableFunc(gSpanFreq);

        qDebug() << "retno => " <<  retNo;

        // 현재 RBW 값이 현재 Span에서 유효한 값인지 확인
        retValidity = searchIndexRbwVbwManValidityFunc(_RBW, retNo, gRbw);

        switch (retValidity) {
        case VALID_BW:
            break;
        case INVALID_BW:
            for (i = 0; i < NUM_RBW_VBW_MAN_VARIETY; i++) {
                currentArrayVal = u32SpanRbwManTable[retNo][i];
                qDebug() << "i / currentArrayVal = " << i  << " / "<<  currentArrayVal;
                if (gRbw  < currentArrayVal) {
                    qDebug() << "in";
                    beforeArrayVal = u32SpanRbwManTable[retNo][i-1];
                    currentDiffVal = currentArrayVal - gRbw;
                    beforeDiffVal = gRbw - beforeArrayVal;

                    if (currentDiffVal <= beforeDiffVal)  // 가까운 값으로 할당하기 위함
                        gRbw = currentArrayVal;
                    else
                        gRbw = beforeArrayVal;
                    break;
                }
            }

            if (i  == NUM_RBW_VBW_MAN_VARIETY)
                gRbw = searchIndexRbwVbwMaxFunc(_RBW, retNo);

            break;
        default:
            qDebug() << "Error RBW setting!!!";
            break;
        }
        qDebug() << " gRbw => " <<  gRbw;



        // VBW ---------------------------------------------------------------------------
        if (gAutoVbw == SA_OFF)  {
            // 현재 Span에 따른 사용 가능한 VBW Table 찾기..
            retNo = searchIndexSpanRbwVbwManTableFunc(gSpanFreq);

            // 현재 VBW 값이 현재 Span에서 유효한 값인지 확인..
            //qint32 SearchIndex_RbwVbwManValidity(u64 span)
            retValidity = searchIndexRbwVbwManValidityFunc(_VBW, retNo, gVbw);

            switch (retValidity) {
            case VALID_BW:
                // RBW 그대로 유효함.
                //ptSMConfig->csweep.RBWSet = ptSMConfig->csweep.RBWSet
                checkVbwUnderRbw();
                break;
            case INVALID_BW:
                for (i = 0; i < NUM_RBW_VBW_MAN_VARIETY; i++) {
                    currentArrayVal = u32SpanRbwManTable[retNo][i];
                    qDebug() << "i / currentArrayVal = " << i  << " / "<<  currentArrayVal;
                    if (gVbw  < currentArrayVal) {
                        qDebug() << "in";
                        beforeArrayVal = u32SpanRbwManTable[retNo][i-1];
                        currentDiffVal = currentArrayVal - gVbw;
                        beforeDiffVal = gVbw - beforeArrayVal;

                        if (currentDiffVal <= beforeDiffVal)  // 가까운 값으로 할당하기 위함
                            gVbw = currentArrayVal;
                        else
                            gVbw = beforeArrayVal;
                        break;
                    }
                }

                if (i  == NUM_RBW_VBW_MAN_VARIETY)
                    gVbw = searchIndexRbwVbwMaxFunc(_VBW, retNo);

                checkVbwUnderRbw();
                break;
            default:
                qDebug() << "Error RBW setting!!!";
                break;
            }
        }  else  {      //if (ptSMConfig->csweep.VBWAuto == VBW_AUTO)
            gVbw = gRbw;
        }
    }
}

void user_variable::checkVbwUnderRbw()
{
    if (gVbw > gRbw) {
        qDebug() << "Check VBW > RBW!!!";
        gRbw = gVbw;
    }
}

quint32 user_variable::searchIndexRbwVbwMaxFunc(qint32 type, qint32 pos)
{
    quint32 retNo = 0;

    switch (type)    {
    case _RBW:
        retNo = u32SpanRbwManTable[pos][NUM_RBW_VBW_MAN_VARIETY - 2];
        break;
    case _VBW:
        // RBW, VBW Table 같음
        retNo = u32SpanRbwManTable[pos][NUM_RBW_VBW_MAN_VARIETY - 2];
        break;
    }
    return retNo;
}
qint32 user_variable::searchIndexRbwVbwManValidityFunc(qint32 type, qint32 pos, quint32 bw)
{
    quint32 retNo;
    quint32 *ptr = NULL;

    switch (type) {
    case _RBW:
        ptr = (quint32 *)bsearch(&bw, &u32SpanRbwManTable[pos][0], NUM_RBW_VBW_MAN_VARIETY, sizeof(quint32), RbwVbwCompare);
        break;
    case _VBW:
        ptr = (quint32 *)bsearch(&bw, &u32SpanRbwManTable[pos][0], NUM_RBW_VBW_MAN_VARIETY, sizeof(quint32), RbwVbwCompare);
        break;
    }

    if (ptr == NULL)
    {
        retNo = INVALID_BW;		// 10 MHz .. 임시 에러 값..
    }
    else
    {
        retNo = VALID_BW;
    }

    return retNo;
}

qint32 user_variable::searchIndexSpanRbwVbwAutoGabFunc(quint64 span)
{
    qint32 i = 0;

    for (i = 0; i < NUM_RBW_VBW_AUTO_SPAN_BOUNDARY; i++) {
        if (span <= u64RbwVbwAutoSpanBoundary[i]) {
            break;
        }
    }

    if (i == NUM_RBW_VBW_AUTO_SPAN_BOUNDARY) {
        qDebug() << "Invalid Span";
    }

    return i;

}

qint32 user_variable::searchIndexSpanRbwVbwManTableFunc(quint64 span)
{

    qint32 i = 0;

    for (i = 0; i < NUM_RBW_VBW_MAN_SPAN_BOUNDARY; i++) {
        if (span <= u64RbwVbwManSpanBoundary[i]) {
            break;
        }
    }

    if (i == NUM_RBW_VBW_MAN_SPAN_BOUNDARY) {
        qDebug() << "Invalid Span";
    }

    return i;
}

qint32 user_variable::RbwVbwCompare(const void *a, const void *b)
{

    if (*(quint32 *)a > *(quint32 *)b)
        return 1;
    else if (*(quint32 *)a == *(quint32 *)b)
        return 0;
    else // if (*(quint32 *)a < *(quint32 *)b)
        return -1;

}

void user_variable::dbmToVoltCalculatorAndDisplayFunc(char *label, qreal _level)
{
    qreal voltGab = 0.;
    qreal calculator = 0.;

    calculator = pow(10, _level / 10.);
    voltGab = 1000000. * pow(50 * calculator * 0.001, 0.5);//uv

    //Johnson 0919 Change
    if (/*_level <= 20. && */voltGab >= 1000000.) {
        sprintf(label, "%.2f V", (qreal) voltGab / 1000000.);
    } else if (voltGab < 1000000. && voltGab >= 1000.) {
        sprintf(label, "%.2f mV", (qreal) voltGab / 1000.);
    } else if (voltGab < 1000. && voltGab >= 1.) {
        sprintf(label, "%.2f uV", (qreal) voltGab);
    } else if (voltGab < 1. && voltGab >= 0.001) {
        sprintf(label, "%.2f nV", (qreal) voltGab * 1000);
    } else if (voltGab < 0.001 && voltGab >= 0.000001) {
        sprintf(label, "%.2f pV", (qreal) voltGab * 1000000.);
    } else if (voltGab < 0.000001 && voltGab >= 0.000000001) {
        sprintf(label, "%.2f fV", (qreal) voltGab * 1000000000.);
    } else if (voltGab < 0.000000001 && voltGab >= 0.000000000001) {
        sprintf(label, "%.2f aV", (qreal) voltGab * 1000000000000.);
    } else if (voltGab < 0.000000000001 && voltGab >= 0.000000000000001) {
        sprintf(label, "%.2f zV", (qreal) voltGab * 1000000000000000.);
    } else if (voltGab < 0.000000000000001 && voltGab >= 0.000000000000000001) {
        sprintf(label, "%.2f yV", (qreal) voltGab * 1000000000000000000.);
    } else {
        sprintf(label, "%.2f", (qreal) voltGab * 1000000000000000000000.);
    }

    /*if (voltGab <= 7071067.9 && voltGab >= 1121000.) {
      sprintf(label, "%.2f V", (qreal) voltGab / 1000000);
    } else if (voltGab <= 998800. && voltGab >= 1121.) {
      sprintf(label, "%.2f mV", (qreal) voltGab / 1000.);
    } else if (voltGab <= 998.8 && voltGab >= 1.121) {
      sprintf(label, "%.2f uV", (qreal) voltGab);
    } else if (voltGab <= 9.988 && voltGab >= 0.221) {
      sprintf(label, "%.2f nV", (qreal) voltGab * 1000);
    } else if (voltGab <= 0.09988 && voltGab >= 0.00221) {
      sprintf(label, "%.2f pV", (qreal) voltGab * 1000000.);
    }*/

    // qDebug() << "voltGab  =>> " <<  label ;
}
void user_variable::Delta_dbmToWattsCalculatorAndDisplayFunc(char *label, qreal _level)
{
    qreal wattsGab = 0.;

    wattsGab = pow(10, _level / 10.);
    sprintf(label, "%.2f W/W", (qreal)wattsGab);
}
void user_variable::Delta_dbmToVoltCalculatorAndDisplayFunc(char *label, qreal _level)
{
    qreal voltGab = 0.;
    qreal calculator = 0.;

    calculator = pow(10, _level / 10.);
    voltGab = 1000000. * 0.001 * pow(50 * calculator * 0.001, 0.5);//uv*0.001 =>mv
    sprintf(label, "%.2f V/V", (qreal) voltGab);
}
void user_variable::charEmptySplitWorkerFunc(char *label)
{
    char *ptr;
    qint32 cnt = 0;

    ptr = strtok(label, " ");   // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환 Johnson 0914 Change
    cnt = 0;
    while (ptr != NULL) {   // 자른 문자열이 나오지 않을 때까지 반복
        if (cnt == 0)
            sprintf(SA_watts_unit.value, "%s", ptr);
        else
            sprintf(SA_watts_unit.unit, "%s", ptr);
        ptr = strtok(NULL, " ");   // 다음 문자열을 잘라서 포인터를 반환

        //Johnson 190118
        if(!cnt && !ptr)
        {
            sprintf(SA_watts_unit.unit, "%s", " ");
        }
        cnt++;
    }
}


void user_variable::dbmToWattsCalculatorAndDisplayFunc(char *label, qreal _level)
{
    qreal wattsGab = 0.;

    wattsGab = pow(10, _level / 10.);

    //Johnson 0919 Change
    if (wattsGab >= 1000) {						// W
        sprintf(label, "%.2f W", (qreal)wattsGab / 1000.0);
    }  else if (wattsGab >= 1) {					// mW
        sprintf(label, "%.2f mW", (qreal)wattsGab);
    }  else if (wattsGab >= 0.001) {				// uW
        sprintf(label, "%.2f uW", (qreal)wattsGab * 1000.0);
    }  else if (wattsGab >= 0.000001) {			// nW
        sprintf(label, "%.2f nW", (qreal)wattsGab * 1000000.0);
    } else if (wattsGab >= 0.000000001) {			// pW
        sprintf(label, "%.2f pW", (qreal)wattsGab * 1000000000.0);
    } else if (wattsGab >= 0.000000000001) {		// fW
        sprintf(label, "%.2f fW", (qreal)wattsGab * 1000000000000.0);
    } else if (wattsGab >= 0.000000000000001) {		// aW
        sprintf(label, "%.2f aW", (qreal)wattsGab * 1000000000000000.0);
    } else if (wattsGab >= 0.000000000000000001) {		// zW
        sprintf(label, "%.2f zW", (qreal)wattsGab * 1000000000000000000.0);
    } else if (wattsGab >= 0.000000000000000000001) {		// yW
        sprintf(label, "%.2f yW", (qreal)wattsGab * 1000000000000000000000.0);
    } else {
        sprintf(label, "%.2f", (qreal)wattsGab * 1000000000000000000.0);
    }

    qDebug() << "wattsGab  =>> " <<  label ;
}

qreal user_variable::wattsToDbmCalculatorFunc(qreal _watts)
{
    return   (10 * log10(_watts) + 30);
}

qreal user_variable::voltToDbmCalculatorFunc(qreal _volt)
{
    qreal cal1 = 0.;
    qreal cal2 = 0.;
    qreal cal3 = 0.;
    qreal cal4 = 0.;

    cal1 = _volt * pow(10, -6);
    cal2 = pow(cal1 , 2) / 50.;//R = 50.;
    cal3 = 10 * log10(cal2);
    cal4 = cal3 + 30.;

    return cal4;

}

bool user_variable::screenCaptureFunc()
{

    bool retFlag = QPixmap::grabWindow(QApplication::desktop()->winId(), SCREEN_CAPTURE_STARTX, SCREEN_CAPTURE_STARTY, SCREEN_CAPTURE_WIDTH, SCREEN_CAPTURE_HEIGHT).save("./ScreenShot.png");


    //Johnson 0823
    //bool retFlag = QPixmap::grabWindow(QApplication::desktop()->winId(), 65,23, 1024, 850).save("./ScreenShot.png");

    return retFlag;
}

void user_variable::saveFilenameAssignFunc(quint32 btnType, QString title)
{

#if 0
    // FileNameDialog 나중에 구현해야함
    FileNameDialog dialog(this, btnType, title);

    pFileNameDialog = &dialog;

    //dialog.setWindowTitle(title);

    // 현재 기본 타이틀 구조를 그대로 사용하고 있음.. 색 등을 바꾸려면 기본 타이틀을 없애고 ... 그림으로 넣어야 함.. 2015-01-29

    dialog.setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    dialog.setGeometry(135, 160, 402, 94);

    // FileNameDialog 창 실행 ..
    dialog.exec();
#endif

}

void user_variable::sharedMemoryVariableAssignFunc()
{
    SA_sm_config_sweep->CenterFreq      = (qreal) gCenterFreq;
#if USABLE
    SA_sm_config_sweep->SpanFreq        = (qreal) gSpanFreq;
#endif
    SA_sm_config_sweep->StartFreq       = (qreal) gStartFreq;
    SA_sm_config_sweep->StopFreq        = (qreal) gStopFreq;

    SA_sm_config_sweep->SpanMode        = gSpanMode;		    // [2]Normal, [0]Full SA_SPAN, [1]Zero SA_SPAN
    SA_sm_config_sweep->TracePoint      = gTracePoint;        // [0]501, [1]1001, [2]2001, [3]3001 (point)
    SA_sm_config_sweep->RBW             = gRbw; 			    // Hz
#if USABLE
    SA_sm_config_sweep->RBWAuto         = gAutoRbw;		    // [0]Manual, [1]Auto
#endif
    SA_sm_config_sweep->VBW             = gVbw; 			    // Hz
#if USABLE
    SA_sm_config_sweep->VBWAuto         = gAutoVbw; 		    // [0]Manual, [1]Auto
#endif
    SA_sm_config_sweep->DetectorMode    = gDetectorMode;	    // [0]Max, [1]Min, [2]Sample, [3]Avg-Power, [4]Avg-Voltage
    SA_sm_config_sweep->RefLevel        = gRefLevel;				// +10 ~ -150 dBm
    SA_sm_config_sweep->SweepType       = gSweepType;		    // [0]Continuous, [1]Single, [2]Sweep Off
#if USABLE
    SA_sm_config_sweep->ZeroSpanTime    = gZeroSpanTime;	        // milisecond
#endif
    SA_sm_config_sweep->Preamp          = gPreamp;			// [0]Off, [1]On
#if USABLE
    SA_sm_config_sweep->ImageRejection  = gImageRejection;	// [0]Off, [1]On  SM_CONFIG_SWEEP->rbwaUTO = 1;
#endif

    SA_sm_config_sweep->attenValue      = gAttenValue;    //Johnson Add
    //Johnson Add
    SA_sm_config_sweep->attenAuto           = gAtten;          // [0]Off, [1]On

#if USABLE
    //added by Steve,0323
    SA_sm_config_sweep->VBWTORBWAuto = user_variable::gAutoVbwtoRbw;
    SA_sm_config_sweep->VBWTORBW = 1.0;
#endif
    //Johnson 190305
    SA_sm_config_sweep->checkinsert = -1;

#if USABLE
    //Johnson 0718
    SA_sm_config_sweep->AutoSweepTime = gAutoSweepTime;
    SA_sm_config_sweep->SweepTime    = gSweepTime;
#endif

    //Johnson 0412
    SA_sm_config_sweep->uSweepCompleteFlag = 0;
    SA_sm_config_sweep->uAllSweepCompleteFlag = 1;
#if USABLE
    //Tony 0423
    SA_sm_config_sweep->uMsCompleteFlag = 0;
#endif
    //Johnson 190416
    SA_sm_config_sweep->sweepMode = 0;
    //Johnson 190425
    SA_sm_config_sweep->uIFMode = uIFMode;

    //Johnson 190704
    SA_sm_config_sweep->TriggerMode = gTriggerMode;
    SA_sm_config_sweep->TriggerDirect = gTriggerSlope[gTriggerMode];
    SA_sm_config_sweep->TriggerDelayTime = gTriggerDelayValue[gTriggerMode];
    SA_sm_config_sweep->TriggerPerTime = gTriggerPerTimer;
    SA_sm_config_sweep->VedioTriggerAmp = gTriggerLevel[gTriggerMode];
    SA_sm_config_sweep->RFBurstTriggerAmp = gTriggerLevel[gTriggerMode];

    //Johnson 191212
    SA_sm_config_sweep->DrCtrlSource = gDrCtrlSource;
    SA_sm_config_sweep->LvlEdgSelect = gLvlEdgSelect;
    SA_sm_config_sweep->LvlEdgMode = gLvlEdgMode;
    SA_sm_config_sweep->DrCtrlSweepMode = gDrCtrlSweepMode;
    SA_sm_config_sweep->PrdTrgSynchroSrc = gPrdTrgSynchroSrc;
    SA_sm_config_sweep->DrCtrlSwitch = gDrCtrlSwitch;
    SA_sm_config_sweep->EdgTrigDely = gEdgTrigDely;
    SA_sm_config_sweep->EdgTrigDoorWdth = gEdgTrigDoorWdth;
    SA_sm_config_sweep->EdgTrigPrvntStatus = gEdgTrigPrvntStatus;
    SA_sm_config_sweep->EdgTrigPrvntTimes = gEdgTrigPrvntTimes;
    SA_sm_config_sweep->RFBurstTrigLevel = gRFBurstTrigLevel;
    SA_sm_config_sweep->PrdTrgPeriod = gPrdTrgPeriod;
    SA_sm_config_sweep->PrdTrgSrcDelay = gPrdTrgSrcDelay;
    SA_sm_config_sweep->PrdTrigPrvntStatus = gPrdTrigPrvntStatus;
    SA_sm_config_sweep->PrdTrigPrvntTimes = gPrdTrigPrvntTimes;
    SA_sm_config_sweep->GateView = gGateViewStatus;

    //Johnson 190722
    SA_sm_config_sweep->markerFreqCount = 0;
    //Johnson 191119
    SA_sm_config_sweep->bSendFreqCountStopCmd = 0;

    //Set_config_flag(IXT_ConfigSweep, IXS_CenterFreq|IXS_SpanFreq|IXS_StartFreq|IXS_StopFreq|IXS_SpanMode|IXS_TracePoint|IXS_RBW|IXS_RBWAuto|IXS_VBW|IXS_VBWAuto | IXS_DetectorMode|IXS_RefLevel|IXS_AttenSelect|IXS_SweepType|IXS_ExtTrigger|IXS_TriggerMode|IXS_ZeroSpanTime|IXS_ZeroSpanMode|IXS_Preamp|IXS_ImageRejection);
}
void user_variable::createVirtualkeyboardDialogMakeFunc(QWidget *_widget, uint filetype)
{

}
/**
 * @brief user_variable::Round
 * @param dSrc
 * @param iBit  0 - 不保留小数、1 - 保留一位小数
 * @return
 * @note  四舍五入（qreal）
 */
qreal user_variable::Round(qreal dSrc,qint32 iBit)
{
    qreal retVal 	= 0.0;
    qint32  intTmp		= 0;

    // 若保留小数位数不正确
    if(0 > iBit )
    {
        return 0;
    }

    //  若 为负数
    if(0 > dSrc)
    {
        // 首先转为正数
        dSrc *= -1;

        intTmp = (qint32)((dSrc + 0.5 / pow(10.0, iBit)) * pow(10.0, iBit));
        retVal = (qreal)intTmp / pow(10.0, iBit);

        // 再转为 负数
        retVal *= -1;
    }
    else
    {
        intTmp = (qint32)((dSrc + 0.5 / pow(10.0, iBit)) * pow(10.0, iBit));
        retVal = (qreal)intTmp / pow(10.0, iBit);
    }

    // 返回计算结果
    return retVal;
}

/**
 * @brief  frequency to qstring for display.
 * @param  frequency
 * @author Tony
 */
QString user_variable::freqValueToQstring(qint64 freq, qint32 precision)
{
    qint32 unitNo=0;
    qint32 zeronum=0;
    QString unitStr="";
    QString freqValue="";
    qint32 minus = 0;
    if(freq<0)
    {
        freq *= -1;
        minus = 1;
    }
    unitNo=freqUnitFindProc(freq);
    zeronum=freqnotZeroPosition(freq);
    switch (unitNo) {
    case UNIT_GHZ:
        unitStr=" GHz";
        if(precision>=0)
        {
            freqValue=QString::number((qreal)freq/SA_GHZ,'f',precision)+unitStr;
        }else
        {
            if(9<=zeronum)
            {
                freqValue=QString::number((qreal)freq/SA_GHZ,'f',0)+unitStr;
            }else
            {
                freqValue=QString::number((qreal)freq/SA_GHZ,'f',9-zeronum)+unitStr;
            }
        }
        break;
    case UNIT_MHZ:
        unitStr=" MHz";
        if(precision>=0)
        {
            freqValue=QString::number((qreal)freq/SA_MHZ,'f',precision)+unitStr;
        }else
        {
            if(6<=zeronum)
            {
                freqValue=QString::number((qreal)freq/SA_MHZ,'f',0)+unitStr;
            }else
            {
                freqValue=QString::number((qreal)freq/SA_MHZ,'f',6-zeronum)+unitStr;
            }
        }
        break;
    case UNIT_KHZ:
        unitStr=" kHz";
        if(precision>=0)
        {
            freqValue=QString::number((qreal)freq/SA_KHZ,'f',precision)+unitStr;
        }else
        {
            if(3<=zeronum)
            {
                freqValue=QString::number((qreal)freq/SA_KHZ,'f',0)+unitStr;
            }else
            {
                freqValue=QString::number((qreal)freq/SA_KHZ,'f',3-zeronum)+unitStr;
            }
        }
        break;
    case UNIT_HZ:
        unitStr=" Hz";

        if(precision>=0)
        {
            freqValue=QString::number((qreal)freq/SA_HZ,'f',0)+unitStr;//Tony precision ==> 0
        }else
        {
            freqValue=QString::number((qreal)freq/SA_HZ,'f',0)+unitStr;
        }
        break;
    }
    if(minus)
    {
        freqValue = "-" + freqValue;
    }
    return freqValue;
}

/**
 * @brief  freqnotZeroPosition.
 * @param  frequency
 * @author Tony
 */
qint32 user_variable::freqnotZeroPosition(quint64 freq)
{
    qint32 remainder=0;
    qint32 pos=0;
    if(freq <= 0)
        return 0;
    while(0 == remainder)
    {
        ++pos;
        remainder = freq%10;
        freq = freq/10;
    }
    return (pos-1);
}

/**
 * @brief user_variable::setPrimaryAction
 * @param primaryAction
 * @note  set the current application index
 */
void user_variable::setPrimaryAction(quint32 primaryAction)
{
    PrimaryAction = primaryAction;
}

/**
 * @brief user_variable::setSecondaryAction
 * @param secondaryAction
 */
void user_variable::setSecondaryAction(quint32 secondaryAction)
{
    SecondaryAction = secondaryAction;
}
/**
 * @brief amptTransformToQstring
 * @param unit  value
 */
QString user_variable::amptTransformToQstring(qint32 unit,qreal value)
{
    QString strvalue;
    char str[20];
    switch (unit) {
    case SA_NONE:
        strvalue = QString::number(value, 'f', 2) + " dB";
        break;
    case SA_DBM:
        strvalue = QString::number(value, 'f', 2) + " dBm";  // Double to String
        break;
    case SA_DBMV:
        strvalue = QString::number((value + dBmVFix), 'f', 2) + " dBmV" ;  // Double to String
        break;
    case SA_DBUV:
        strvalue = QString::number((value + dBuVFix), 'f', 2) + "dBuV";  // Double to String
        break;
    case SA_VOLT:
        dbmToVoltCalculatorAndDisplayFunc(str,value);
        strvalue = QString(str);
        break;
    case SA_WATTS:
        dbmToWattsCalculatorAndDisplayFunc(str,value);
        strvalue = QString(str);
        break;
    case SA_DBV:
        strvalue = QString::number((value + dBVFix), 'f', 2) + " dBV" ;  // Double to String
        break;
    case SA_DELTA_VOLT:
        Delta_dbmToVoltCalculatorAndDisplayFunc(str,value);
        strvalue = QString(str);
        break;
    case SA_DELTA_WATTS:
        Delta_dbmToWattsCalculatorAndDisplayFunc(str,value);
        strvalue = QString(str);
        break;
    default:
        break;
    }
    return strvalue;
}
/**
 * @brief getTimeUnit
 * @param value
 */
qint32 user_variable::getTimeUnit(qreal value)
{
    qint32 timeUnit = 0;
    if((value * SA_KHZ ) < 1)
    {
        timeUnit = UNIT_NS;
    }
    else if((value * SA_KHZ) >= 1 && value < 1)
    {
        timeUnit = UNIT_US;
    }
    else if(value >= 1 && value < SA_KHZ)
    {
        timeUnit = UNIT_MS;
    }
    else if(value >= SA_KHZ)
    {
        timeUnit = UNIT_S;
    }
    return timeUnit;
}
/**
 * @brief TimeTransformToQstring
 * @param unit  value
 */
QString user_variable::TimeTransformToQstring(qreal value)
{
    QString strvalue;
    QString unitStr;
    if((value * SA_KHZ ) < 1)
    {
        strvalue = QString::number(value * SA_MHZ, 'f',2);
        unitStr =QString("ns");
    }
    else if((value * SA_KHZ) >= 1 && value < 1)
    {
        strvalue = QString::number(value * SA_KHZ, 'f',2);
        unitStr =QString("us");
    }
    else if(value >= 1 && value < SA_KHZ)
    {
        strvalue = QString::number(value, 'f',2);
        unitStr =QString("ms");
    }
    else if(value >= SA_KHZ)
    {
        strvalue = QString::number(value/SA_KHZ, 'f',2);
        unitStr =QString("s");
    }
    strvalue = strvalue + " " + unitStr;
    return strvalue;
}
void user_variable::getBandInfo(qint32 STDIndex)
{
    QString name = QString(mChStand[STDIndex].name);
    QString filename = QString(":/sa/standard/%1").arg(name);
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
        setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,SA_BandInfoFile_Read);
        errorOutput();
    }
    //mFile.close();
    return;
}
void user_variable::analysisData(QString str)
{
    __Standard__ mtmp;
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
qint32 user_variable::CalculateChannelNum()
{

    qint32 index,channelSTD,direction;
    qreal freq;
    channelSTD = gTecIndex;
    freq = gCenterFreq;
    direction = gCommuDirection;
    switch (channelSTD) {
    case SA_CDMA:
        if(direction == SA_UPLINK)
        {
            index = (freq - 825000000)/(0.03 *SA_MHZ);
        }else
        {
            index = (freq - 870000000)/(0.03 *SA_MHZ);
        }
        break;
    case SA_GSM:
        if(freq < 1500000000)
        {
            if(direction == SA_UPLINK)
            {
                index = (freq - 890200000)/(0.2*SA_MHZ)+1;
            }else
            {
                index = (freq - 935200000)/(0.2*SA_MHZ)+1;
            }
        }else
        {
            if(direction == SA_UPLINK)
            {
                index = (freq - 1710000000)/(0.2*SA_MHZ)+511;
            }else
            {
                index = (freq - 1805000000)/(0.2*SA_MHZ)+511;
            }
        }
        break;
    case SA_WCDMA:
        index = freq / SA_MHZ * 5;
        break;
    case SA_TD_SCDMD:
        if(freq >2010000000 && freq<=2025000000 ) //A Freq
        {
            index = freq/SA_MHZ *5;
        }else if(freq > 1800000000 && freq<=2000000000) //F Freq
        {
            index = freq/SA_MHZ *5;
        }else if(freq > 2300000000LL && freq<=2400000000LL)  //E Freq
        {
            index = freq/SA_MHZ *5;
        }
        break;
    case SA_LTE_TDD:
        if(freq >= TD_B38_FREQ_MIN && freq <= TD_B38_FREQ_MAX)
        {
            index = (freq - TD_B38_FREQ_MIN)/SA_MHZ*10+TD_B38_FREQPOINT_BASE;
        }else if(freq >= TD_B39_FREQ_MIN && freq <= TD_B39_FREQ_MAX)
        {
            index = (freq - TD_B39_FREQ_MIN)/SA_MHZ*10+TD_B39_FREQPOINT_BASE;
        }else if(freq >= TD_B40_FREQ_MIN && freq <= TD_B40_FREQ_MAX)
        {
            index = (freq - TD_B40_FREQ_MIN)/SA_MHZ*10+TD_B40_FREQPOINT_BASE;
        }else if(freq >= TD_B41_FREQ_MIN && freq <= TD_B41_FREQ_MAX)
        {
            index = (freq - TD_B41_FREQ_MIN)/SA_MHZ*10+TD_B41_FREQPOINT_BASE;
        }
        break;
    case SA_LTE_FDD:
        if(freq >= FDD_B1_UP_FREQ_MIN && freq <= FDD_B1_UP_FREQ_MAX)
        {
            index = (freq - FDD_B1_UP_FREQ_MIN)*10/SA_MHZ+FDD_B1_UP_FREQPOINT_BASE;
        }else if(freq >= FDD_B1_DOWN_FREQ_MIN && freq <= FDD_B1_DOWN_FREQ_MAX)
        {
            index = (freq - FDD_B1_DOWN_FREQ_MIN)*10/SA_MHZ+FDD_B1_DOWN_FREQPOINT_BASE;
        }else if(freq >= FDD_B3_UP_FREQ_MIN && freq <= FDD_B3_UP_FREQ_MAX)
        {
            index = (freq - FDD_B3_UP_FREQ_MIN)*10/SA_MHZ+FDD_B3_UP_FREQPOINT_BASE;
        }else if(freq >= FDD_B3_DOWN_FREQ_MIN && freq <= FDD_B3_DOWN_FREQ_MAX)
        {
            index = (freq - FDD_B3_DOWN_FREQ_MIN)*10/SA_MHZ+FDD_B3_DOWN_FREQPOINT_BASE;
        }
        break;
    }
    return index;
}
void user_variable::adjustCHStandarByCerFreq(qreal freq)
{
    freq = (qreal)freq/SA_MHZ;
    qint32 size;
    /*if((freq>=gFreqStandard->at(gCHIndex).Up.Min && freq<gFreqStandard->at(gCHIndex).Up.Max)||\
            (freq>=gFreqStandard->at(gCHIndex).Down.Min && freq<gFreqStandard->at(gCHIndex).Down.Max))
    {
        gChannelNum = CalculateChannelNum();
        gChannelStep = mChStand[gTecIndex].ChStep;
        return;
    }*/
    for(qint32 i = 0 ;i<7;i++)
    {
        getBandInfo(i);
        size = gCHName->size();
        for(qint32 j=0;j<size;j++)
        {
            if(freq > gFreqStandard->at(j).Up.Min && freq<=gFreqStandard->at(j).Up.Max)
            {
                gTecIndex =i;
                gCHIndex = j;
                if(gTecIndex != SA_LTE_TDD && gTecIndex != SA_TD_SCDMD)
                {
                    gCommuDirection = SA_UPLINK;
                }
                gChannelNum = CalculateChannelNum();

                gChannelStep = mChStand[i].ChStep;

                return;
            }else if(freq>gFreqStandard->at(j).Down.Min && freq<=gFreqStandard->at(j).Down.Max)
            {
                gTecIndex =i;
                gCHIndex = j;
                if(gTecIndex != SA_LTE_TDD && gTecIndex != SA_TD_SCDMD)
                {
                    gCommuDirection = SA_DOWNLINK;
                }
                gChannelNum = CalculateChannelNum();
                gChannelStep = mChStand[i].ChStep;
                return;
            }
        }
    }
    gCHIndex = 0;
    gTecIndex = -1;
    return;
}
qreal user_variable::CalculateFreqByCHStandar()
{
    if(gTecIndex < 0)
        return gCenterFreq;
    qreal freq,min,max;
    qint32 direction,index;
    direction = gCommuDirection;
    freq = gCenterFreq;
    index = gCHIndex;
    if(SA_UPLINK == direction)
    {
        min = gFreqStandard->at(index).Up.Min;
        max = gFreqStandard->at(index).Up.Max;
    }
    else
    {
        min = gFreqStandard->at(index).Down.Min;
        max = gFreqStandard->at(index).Down.Max;
    }
    if(freq < min*SA_MHZ || freq > max*SA_MHZ)
    {
        freq = min*SA_MHZ;
    }
    return freq;
}
qreal user_variable::CalculateFreqByCHNum(qint32 index)
{
    qint32 channelSTD,direction;
    qreal freq;
    channelSTD = gTecIndex;
    direction = gCommuDirection;
    if(direction == SA_UPLINK)
    {
        if(index < gCHStandard->at(gCHIndex).Up.Min)
        {
            index = gCHStandard->at(gCHIndex).Up.Min;
        }else if(index > gCHStandard->at(gCHIndex).Up.Max)
        {
            index = gCHStandard->at(gCHIndex).Up.Max;
        }
    }else
    {
        if(index < gCHStandard->at(gCHIndex).Down.Min)
        {
            index = gCHStandard->at(gCHIndex).Down.Min;
        }else if(index > gCHStandard->at(gCHIndex).Down.Max)
        {
            index = gCHStandard->at(gCHIndex).Down.Max;
        }
    }
    switch (channelSTD) {
    case SA_CDMA:
        if(direction == SA_UPLINK)
        {
            freq = index*(0.03 *SA_MHZ) + 825000000;
        }else
        {
            freq = index*(0.03 *SA_MHZ) + 870000000;
        }
        break;
    case SA_GSM:
        if(index < 500)
        {
            if(direction == SA_UPLINK)
            {
                freq = (index-1)*(0.2*SA_MHZ) + 890200000;
            }else
            {
                freq = (index-1)*(0.2*SA_MHZ) + 935200000;
            }
        }else
        {
            if(direction == SA_UPLINK)
            {
                freq = (index-511)*(0.2*SA_MHZ)+ 1710000000;
            }else
            {
                freq = (index-511)*(0.2*SA_MHZ)+ 1805000000;
            }
        }
        break;
    case SA_WCDMA:
        freq = (qreal)index / 5 * SA_MHZ;
        break;
    case SA_TD_SCDMD:
        freq = (qreal)index / 5 * SA_MHZ;
        //        if(freq >2010000000 && freq<=2025000000 ) //A Freq
        //        {
        //            index = freq *5;
        //        }else if(freq > 1800000000 && freq<=2000000000) //F Freq
        //        {

        //        }else if(freq > 2300000000 && freq<=2400000000)  //E Freq
        //        {

        //        }
        break;
    case SA_LTE_TDD:
        if(index >= TD_B38_FREQPOINT_BASE && index <= TD_B38_FREQPOINT_MAX)
        {
            freq = (index - TD_B38_FREQPOINT_BASE)*SA_MHZ/10 + TD_B38_FREQ_MIN;
        }else if(index >= TD_B39_FREQPOINT_BASE && index <= TD_B39_FREQPOINT_MAX)
        {
            freq = (index - TD_B39_FREQPOINT_BASE)*SA_MHZ/10 + TD_B39_FREQ_MIN;
        }else if(index >= TD_B40_FREQPOINT_BASE && index <= TD_B40_FREQPOINT_MAX)
        {
            freq = (index - TD_B40_FREQPOINT_BASE)*SA_MHZ/10 + TD_B40_FREQ_MIN;
        }else if(index >= TD_B41_FREQPOINT_BASE && index <= TD_B41_FREQPOINT_MAX)
        {
            freq = (index - TD_B41_FREQPOINT_BASE)*SA_MHZ/10 + TD_B41_FREQ_MIN;
        }
        break;
    case SA_LTE_FDD:
        if(index >= FDD_B1_UP_FREQPOINT_BASE && index <= FDD_B1_UP_FREQPOINT_MAX)
        {
            freq = (index-FDD_B1_UP_FREQPOINT_BASE)*SA_MHZ/10+ FDD_B1_UP_FREQ_MIN ;
        }else if(index >= FDD_B1_DOWN_FREQPOINT_BASE && index <= FDD_B1_DOWN_FREQPOINT_MAX)
        {
            freq = (index -FDD_B1_DOWN_FREQPOINT_BASE)*SA_MHZ/10+ FDD_B1_DOWN_FREQ_MIN;
        }else if(index >= FDD_B3_UP_FREQPOINT_BASE && index <= FDD_B3_UP_FREQPOINT_MAX)
        {
            freq = (index - FDD_B3_UP_FREQPOINT_BASE)*SA_MHZ/10 + FDD_B3_UP_FREQ_MIN;
        }else if(index >= FDD_B3_DOWN_FREQPOINT_BASE && index <= FDD_B3_DOWN_FREQPOINT_MAX)
        {
            freq = (index - FDD_B3_DOWN_FREQPOINT_BASE)*SA_MHZ/10 + FDD_B3_DOWN_FREQ_MIN;
        }
        break;
    }
    return freq;
}

/**
 * @brief controlInterface::setRelativeCPParam
 * @return void
 * @author Johnson
 * @date 2020-05-11
 */
void user_variable::setRelativeCPParam()
{
    qreal FZ = 0. , SA_FM = 0.;
    FZ = (qreal)gChannelBandwidth;
    SA_FM = (qreal)gSpanFreq / gridWidth;

    CP_W = (qint32)(FZ/SA_FM);
    if (CP_W < BW_MIN)
    {
        CP_W = BW_MIN;
        gChannelBandwidth = CP_W * gSpanFreq / gridWidth;
    }
    if (CP_W > gridWidth)
    {
        CP_W = gridWidth;
        //Johnson 0813
        gChannelBandwidth = CP_W * gSpanFreq / gridWidth;
    }
    CP_Left_X = (gridWidth / 2)  - (CP_W / 2);		// 좌우분할이므로 /2
}

/**
 * @brief controlInterface::setRelativeOBWParam
 * @return void
 * @author Johnson
 * @date 2020-05-11
 */
void user_variable::setRelativeOBWParam()
{

}

/**
 * @brief controlInterface::setRelativeACPParam
 * @return void
 * @author Johnson
 * @date 2020-05-11
 */
void user_variable::setRelativeACPParam()
{
    //************Johnson 20200511*******************
    //***********use the left side to judge params
    qreal FZ = 0.,SA_FM = 0.;
    qint64 tmpALTCH_CenterFreq,tmpADJCH_CenterFreq;
    qint32 Space_w;

    tmpALTCH_CenterFreq = gCenterFreq - 2 * gMultiACPSpacing;
    if(tmpALTCH_CenterFreq < gStartFreq)
    {
        tmpALTCH_CenterFreq = gStartFreq;
        gMultiACPSpacing = (gCenterFreq - tmpALTCH_CenterFreq) / 2;
        if(gMultiACPSpacing < 0)
        {
            gMultiACPSpacing = 0;
            tmpALTCH_CenterFreq = gCenterFreq;
        }
    }
    FZ = (qreal)gMultiACPSpacing;
    SA_FM = (qreal)gSpanFreq / gridWidth;
    Space_w = (qint32) (FZ/ SA_FM);

    //judge BW
    if(gMainIntegBW / 2 > gCenterFreq - gStartFreq)
        gMainIntegBW = 2 * (gCenterFreq - gStartFreq);
    FZ = (qreal)gMainIntegBW;
    SA_FM = (qreal)gSpanFreq / gridWidth;
    ACP_MainCH_W = (qint32) (FZ/ SA_FM);
    if(ACP_MainCH_W < BW_MIN)
    {
        ACP_MainCH_W = BW_MIN;
        gMainIntegBW = (qint64)ACP_MainCH_W*gSpanFreq / gridWidth;
        //gHighestCHFreq = gStopFreq - gMainIntegBW / 2;
    }

    tmpADJCH_CenterFreq = gCenterFreq - gMultiACPSpacing;
    if(gADJIntegBW / 2 > tmpADJCH_CenterFreq - gStartFreq)
        gADJIntegBW = 2 * (tmpADJCH_CenterFreq - gStartFreq);
    FZ = (qreal)gADJIntegBW;
    SA_FM = (qreal)gSpanFreq / gridWidth;
    ACP_ADJCH_W = (qint32) (FZ/ SA_FM);
    if(ACP_ADJCH_W < BW_MIN)
    {
        ACP_ADJCH_W = BW_MIN;
        gADJIntegBW = (qint64)ACP_ADJCH_W*gSpanFreq / gridWidth;
    }

    tmpALTCH_CenterFreq = gCenterFreq - 2 * gMultiACPSpacing;
    if(gALTIntegBW / 2 > tmpALTCH_CenterFreq - gStartFreq)
        gALTIntegBW = 2 * (tmpALTCH_CenterFreq - gStartFreq);
    FZ = (qreal)gALTIntegBW;
    SA_FM = (qreal)gSpanFreq / gridWidth;
    ACP_ALTCH_W = (qint32) (FZ/ SA_FM);
    if(ACP_ALTCH_W < BW_MIN)
    {
        ACP_ALTCH_W = BW_MIN;
        gALTIntegBW = (qint64)ACP_ALTCH_W*gSpanFreq / gridWidth;
    }

    FZ = (qreal)(gCenterFreq - gStartFreq);
    SA_FM = (qreal)gSpanFreq / gridWidth;
    ACP_MainCH_x = (qint32) (FZ/ SA_FM) - ACP_MainCH_W / 2;
    ACP_LeftADJCH_x = (qint32) (FZ/ SA_FM) - Space_w - ACP_ADJCH_W / 2;
    ACP_LeftALTCH_x = (qint32) (FZ/ SA_FM) - 2 * Space_w - ACP_ALTCH_W / 2;
    ACP_RightADJCH_x = (qint32) (FZ/ SA_FM) + Space_w - ACP_ADJCH_W / 2;
    ACP_RightALTCH_x = (qint32) (FZ/ SA_FM) + 2 * Space_w - ACP_ALTCH_W / 2;
}

/**
 * @brief controlInterface::setRelativeMultiACPParam
 * @return void
 * @author Johnson
 * @date 2020-05-11
 */
void user_variable::setRelativeMultiACPParam()
{
    qint32 Space_w;
    qint64 tmpLowest_ADJCH_CenterFreq,tmpLowest_ALT_CenterFreq,
           tmpHighest_ADJCH_CenterFreq,tmpHighest_ALTCH_CenterFreq;
    static qint64 tmpCenterFreq = gCenterFreq;

    if(tmpCenterFreq - gCenterFreq != 0)
    {
        if(gLowestCHFreq < gStartFreq)
        {
            gLowestCHFreq = gStartFreq;
            if(gHighestCHFreq < gStartFreq) gHighestCHFreq = gStartFreq;
            else if(gHighestCHFreq > gStopFreq) gHighestCHFreq = gStopFreq;
        }
        else if(gLowestCHFreq >= gStartFreq && gLowestCHFreq <= gStopFreq)
        {
            if(gHighestCHFreq > gStartFreq) gHighestCHFreq = gStopFreq;
        }
        else if(gLowestCHFreq > gStopFreq)
        {
            gLowestCHFreq = gStopFreq;
            gHighestCHFreq = gStopFreq;
        }
        tmpCenterFreq = gCenterFreq;
    }

    qreal FZ = 0;
    qreal SA_FM = 1.;

    //1.judge the span of lowestFreq to startFreq and highestFreq to stopFreq,use the smaller span of those two
    qint64 tmpLowestW = gLowestCHFreq - gStartFreq;
    qint64 tmpHighestW = gStopFreq - gHighestCHFreq;

    FZ = (qreal)gMainIntegBW;
    SA_FM = (qreal)gSpanFreq / gridWidth;
    MultiACP_MainCh_w = (qint32) (FZ/ SA_FM);

    FZ = (qreal)gADJIntegBW;
    SA_FM = (qreal)gSpanFreq / gridWidth;
    MultiACP_ADJCh_w = (qint32) (FZ/ SA_FM);

    FZ = (qreal)gALTIntegBW;
    SA_FM = (qreal)gSpanFreq / gridWidth;
    MultiACP_ALTCh_w = (qint32) (FZ/ SA_FM);

    FZ = (qreal)gMultiACPSpacing;
    SA_FM = (qreal)gSpanFreq / gridWidth;
    Space_w = (qint32) (FZ/ SA_FM);


    if(tmpLowestW > tmpHighestW)//2.use highFreq side
    {
        //First judge multiSpace and highest freq,then cal mainChBW,ALTBW,ADJBW

        //judge multiSpace and highest freq
        tmpHighest_ALTCH_CenterFreq = gHighestCHFreq + 2 * gMultiACPSpacing;
        if(tmpHighest_ALTCH_CenterFreq > gStopFreq)
        {
            tmpHighest_ALTCH_CenterFreq = gStopFreq;
            gMultiACPSpacing = (tmpHighest_ALTCH_CenterFreq - gHighestCHFreq) / 2;
            if(gMultiACPSpacing < 0)
            {
                gMultiACPSpacing = 0;
                gHighestCHFreq = gStopFreq;
            }
        }
        FZ = (qreal)gMultiACPSpacing;
        SA_FM = (qreal)gSpanFreq / gridWidth;
        Space_w = (qint32) (FZ/ SA_FM);

        //judge BW
        if(gMainIntegBW / 2 > gStopFreq - gHighestCHFreq)
            gMainIntegBW = 2 * (gStopFreq - gHighestCHFreq);
        FZ = (qreal)gMainIntegBW;
        SA_FM = (qreal)gSpanFreq / gridWidth;
        MultiACP_MainCh_w = (qint32) (FZ/ SA_FM);
        if(MultiACP_MainCh_w < BW_MIN)
        {
            MultiACP_MainCh_w = BW_MIN;
            gMainIntegBW = (qint64)MultiACP_MainCh_w*gSpanFreq / gridWidth;
            //gHighestCHFreq = gStopFreq - gMainIntegBW / 2;
        }

        tmpHighest_ADJCH_CenterFreq = gHighestCHFreq + gMultiACPSpacing;
        if(gADJIntegBW / 2 > gStopFreq - tmpHighest_ADJCH_CenterFreq)
            gADJIntegBW = 2 * (gStopFreq - tmpHighest_ADJCH_CenterFreq);
        FZ = (qreal)gADJIntegBW;
        SA_FM = (qreal)gSpanFreq / gridWidth;
        MultiACP_ADJCh_w = (qint32) (FZ/ SA_FM);
        if(MultiACP_ADJCh_w < BW_MIN)
        {
            MultiACP_ADJCh_w = BW_MIN;
            gADJIntegBW = (qint64)MultiACP_ADJCh_w*gSpanFreq / gridWidth;
        }

        tmpHighest_ALTCH_CenterFreq = gHighestCHFreq + 2 * gMultiACPSpacing;
        if(gALTIntegBW / 2 > gStopFreq - tmpHighest_ALTCH_CenterFreq)
            gALTIntegBW = 2 * (gStopFreq - tmpHighest_ALTCH_CenterFreq);
        FZ = (qreal)gALTIntegBW;
        SA_FM = (qreal)gSpanFreq / gridWidth;
        MultiACP_ALTCh_w = (qint32) (FZ/ SA_FM);
        if(MultiACP_ALTCh_w < BW_MIN)
        {
            MultiACP_ALTCh_w = BW_MIN;
            gALTIntegBW = (qint64)MultiACP_ALTCh_w*gSpanFreq / gridWidth;
        }
    }
    else//2.use lowFreq side
    {
        //First judge multiSpace and highest freq,then cal mainChBW,ALTBW,ADJBW

        //judge multiSpace and highest freq
        tmpLowest_ALT_CenterFreq = gLowestCHFreq - 2 * gMultiACPSpacing;
        if(tmpLowest_ALT_CenterFreq < gStartFreq)
        {
            tmpLowest_ALT_CenterFreq = gStartFreq;
            gMultiACPSpacing = (gLowestCHFreq - tmpLowest_ALT_CenterFreq) / 2;

            if(gMultiACPSpacing < 0)
            {
                gMultiACPSpacing = 0;
                gLowestCHFreq = gStartFreq;
            }
        }
        FZ = (qreal)gMultiACPSpacing;
        SA_FM = (qreal)gSpanFreq / gridWidth;
        Space_w = (qint32) (FZ/ SA_FM);

        //judge BW
        if(gMainIntegBW / 2 > gLowestCHFreq - gStartFreq)
            gMainIntegBW = 2 * (gLowestCHFreq - gStartFreq);
        FZ = (qreal)gMainIntegBW;
        SA_FM = (qreal)gSpanFreq / gridWidth;
        MultiACP_MainCh_w = (qint32) (FZ/ SA_FM);
        if(MultiACP_MainCh_w < BW_MIN)
        {
            MultiACP_MainCh_w = BW_MIN;
            gMainIntegBW = (qint64)MultiACP_MainCh_w*gSpanFreq / gridWidth;
            //gLowestCHFreq = gStartFreq + gMainIntegBW / 2;
        }

        tmpLowest_ADJCH_CenterFreq = gLowestCHFreq - gMultiACPSpacing;
        if(gADJIntegBW / 2 > tmpLowest_ADJCH_CenterFreq - gStartFreq)
            gADJIntegBW = 2 * (tmpLowest_ADJCH_CenterFreq - gStartFreq);
        FZ = (qreal)gADJIntegBW;
        SA_FM = (qreal)gSpanFreq / gridWidth;
        MultiACP_ADJCh_w = (qint32) (FZ/ SA_FM);
        if(MultiACP_ADJCh_w < BW_MIN)
        {
            MultiACP_ADJCh_w = BW_MIN;
            gADJIntegBW = (qint64)MultiACP_ADJCh_w*gSpanFreq / gridWidth;
        }

        tmpLowest_ALT_CenterFreq = gLowestCHFreq - 2 * gMultiACPSpacing;
        if(gALTIntegBW / 2 > tmpLowest_ALT_CenterFreq - gStartFreq)
            gALTIntegBW = 2 * (tmpLowest_ALT_CenterFreq - gStartFreq);
        FZ = (qreal)gALTIntegBW;
        SA_FM = (qreal)gSpanFreq / gridWidth;
        MultiACP_ALTCh_w = (qint32) (FZ/ SA_FM);
        if(MultiACP_ALTCh_w < BW_MIN)
        {
            MultiACP_ALTCh_w = BW_MIN;
            gALTIntegBW = (qint64)MultiACP_ALTCh_w*gSpanFreq / gridWidth;
        }
    }
    FZ = (qreal)(gLowestCHFreq - gStartFreq);
    SA_FM = (qreal)gSpanFreq / gridWidth;
    MultiACP_Lowest_MainCh_x = (qint32) (FZ/ SA_FM) - MultiACP_MainCh_w / 2;
    MultiACP_Lowest_ADJCh_x = (qint32) (FZ/ SA_FM) - Space_w - MultiACP_ADJCh_w / 2;
    MultiACP_Lowest_ALTCh_x = (qint32) (FZ/ SA_FM) - 2 * Space_w - MultiACP_ALTCh_w / 2;

    FZ = (qreal)(gHighestCHFreq - gStartFreq);
    SA_FM = (qreal)gSpanFreq / gridWidth;
    MultiACP_Highest_MainCh_x = (qint32) (FZ/ SA_FM) - MultiACP_MainCh_w / 2;
    MultiACP_Highest_ADJCh_x = (qint32) (FZ/ SA_FM) + Space_w - MultiACP_ADJCh_w / 2;
    MultiACP_Highest_ALTCh_x = (qint32) (FZ/ SA_FM) + 2 * Space_w - MultiACP_ALTCh_w / 2;
}

/**
 * @brief controlInterface::initMeasurModeParam
 * @return void
 * @author Johnson
 * @date 2020-05-11
 */
void user_variable::initMeasurModeParam(qint32 curMod)
{
    switch(curMod)
    {
    case SA_CHNLPOWER_MEASURE_MODE:
        setRelativeCPParam();
        break;
    case SA_OCCUPIED_BW_MEASURE_MODE:
        setRelativeOBWParam();
        break;
    case SA_ACP_MEASURE_MODE://real Multi-ACP
        setRelativeMultiACPParam();
        break;
    case SA_MULTI_ACP_MODE://real ACP
        setRelativeACPParam();
        break;
    default: break;
    }
}


