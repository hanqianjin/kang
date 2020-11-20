#include "rtsa_control.h"
#include "rtsa_shared_memory.h"
#include <qmath.h>
#include <qthread.h>

#define RTSA_FFT_SAMPLE  (184320000)

extern _RTSA_SWEEP_DATA *sm_rtsa_sweep_data;
extern _CONFIG_RSA_CTRL *sm_rtsa_config_rsa_ctrl;
extern _RTSA_START_FLAG *sm_startflag;
RtSa_Control::RtSa_Control(QObject *parent)
    : QObject(parent)
    , gDector(RTSA_DEC_PEAK)
{

}
RtSa_Control::~RtSa_Control()
{
}
void RtSa_Control::setGobalVariable(RtSa_User_Variable *globalVariable)
{
    globalUserVariable = globalVariable;
    rtsa_aloth.setGobalVariable(globalVariable);
    return;
}
void RtSa_Control::setCenterFreq(qreal freq)
{
    quint32 tempFlag = 0;
    // in order to avoid dialog. adjust put here.
    globalUserVariable->gCenterFreq = freq /*- globalUserVariable->gfreqOffset*/;
    globalUserVariable->adjustFreqByCer();
    globalUserVariable->stepFreqCalculatorFunc();
    adjustSpanFreq(globalUserVariable->gSpanFreq);
//    mCenterFreq = globalUserVariable->gCenterFreq;
    rtsa_aloth.ConfigureFrequencyStartStop(globalUserVariable->gStartFreq,globalUserVariable->gStopFreq);
    if(globalUserVariable->gspanChangebyFreq && globalUserVariable->grbwChangedbyFreq)
    {
//        globalUserVariable->convertBwToShm();
//        sm_rtsa_config_rsa_ctrl->ischangeRbwitself = 0;
        tempFlag |= IXS_RTSA_CenterFreq|IXS_RTSA_SpanFreq|IXS_RTSA_StartFreq|IXS_RTSA_StopFreq|IXS_RTSA_RBW|IXS_RTSA_AcqTime;
    }
    else
    {
        tempFlag |= IXS_RTSA_CenterFreq|IXS_RTSA_SpanFreq|IXS_RTSA_StartFreq|IXS_RTSA_StopFreq|IXS_RTSA_AcqTime;
    }
    globalUserVariable->converFreqToShm();
    //tell the ctrl app to reflesh the param
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl, tempFlag);
    }

    return;
}
qreal RtSa_Control::getCenterFreq()
{
    return globalUserVariable->gCenterFreq;
}
void RtSa_Control::setStartFreq(qreal freq)
{
    quint32 tempFlag = 0;
    globalUserVariable->gStartFreq = freq /*- globalUserVariable->gfreqOffset*/;

    globalUserVariable->adjustFreqByStart();
    globalUserVariable->stepFreqCalculatorFunc();
    adjustSpanFreq(globalUserVariable->gSpanFreq);
//    mStartFreq = globalUserVariable->gStartFreq;

    rtsa_aloth.ConfigureFrequencyStartStop(globalUserVariable->gStartFreq,globalUserVariable->gStopFreq);
    //by Steve,0301
    if(globalUserVariable->grbwChangedbyFreq)
    {
//        globalUserVariable->convertBwToShm();
        //less trig to let ctrlapp to set rbw
        sm_rtsa_config_rsa_ctrl->ischangeRbwitself = 0;
        //steve,0503
        tempFlag |= IXS_RTSA_CenterFreq|IXS_RTSA_SpanFreq|IXS_RTSA_StartFreq|IXS_RTSA_StopFreq|IXS_RTSA_RBW|IXS_RTSA_AcqTime;
    }
    else
    {
        tempFlag |= IXS_RTSA_CenterFreq|IXS_RTSA_SpanFreq|IXS_RTSA_StartFreq|IXS_RTSA_StopFreq|IXS_RTSA_AcqTime;
    }
    globalUserVariable->converFreqToShm();
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl, tempFlag);
    }
    return;
}
qreal RtSa_Control::getStartFreq()
{
    return globalUserVariable->gStartFreq;
}
void RtSa_Control::setStopFreq(qreal freq)
{
    quint32 tempFlag = 0;
    globalUserVariable->gStopFreq = freq /*- globalUserVariable->gfreqOffset*/;

    globalUserVariable->adjustFreqByStop();
    globalUserVariable->stepFreqCalculatorFunc();
    adjustSpanFreq(globalUserVariable->gSpanFreq);
//    mStopFreq = globalUserVariable->gStopFreq;
    rtsa_aloth.ConfigureFrequencyStartStop(globalUserVariable->gStartFreq,globalUserVariable->gStopFreq);

    adjustAcqtime(globalUserVariable->gAcqTime);
    //by Steve,0301
    if(globalUserVariable->grbwChangedbyFreq)
    {
        //less trig to let ctrlapp to set rbw
//        globalUserVariable->convertBwToShm();
        sm_rtsa_config_rsa_ctrl->ischangeRbwitself = 0;
        tempFlag |= IXS_RTSA_CenterFreq|IXS_RTSA_SpanFreq|IXS_RTSA_StartFreq|IXS_RTSA_StopFreq|IXS_RTSA_RBW| IXS_RTSA_AcqTime;
    }
    else
    {
        tempFlag |= IXS_RTSA_CenterFreq|IXS_RTSA_SpanFreq|IXS_RTSA_StartFreq|IXS_RTSA_StopFreq | IXS_RTSA_AcqTime;
    }
    globalUserVariable->converFreqToShm();
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl, tempFlag);
    }

    return;
}
qreal RtSa_Control::getStopFreq()
{
    return globalUserVariable->gStopFreq;
}
void RtSa_Control::setSpan(qreal freq)
{
    quint32 tempFlag = 0;
    adjustSpanFreq(freq);
//    mSpanFreq = globalUserVariable->gSpanFreq;
    adjustAcqtime(globalUserVariable->gAcqTime);
    if(globalUserVariable->grbwChangedbyFreq)
    {
//        globalUserVariable->convertBwToShm();
        //less
        sm_rtsa_config_rsa_ctrl->ischangeRbwitself = 0;
        tempFlag |= IXS_RTSA_CenterFreq|IXS_RTSA_SpanFreq|IXS_RTSA_StartFreq|IXS_RTSA_StopFreq|IXS_RTSA_RBW|IXS_RTSA_AcqTime;
    }
    else
    {
        tempFlag |= IXS_RTSA_CenterFreq|IXS_RTSA_SpanFreq|IXS_RTSA_StartFreq|IXS_RTSA_StopFreq|IXS_RTSA_AcqTime;
    }
    //by Steve,0309
    globalUserVariable->stepFreqCalculatorFunc();
    globalUserVariable->converFreqToShm();
    if(getTrigger() == RTSA_TRIGGER_PERIODIC_TIMER)
    {
        AdjustPeriodTime(globalUserVariable->gPeriodTrigTime);
        tempFlag |= IXS_RTSA_Trigger_Period;
    }
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl, tempFlag);
    }

    return;
}
qreal RtSa_Control::getSpan()
{
    return globalUserVariable->gSpanFreq;
}
void RtSa_Control::adjustSpanFreq(qreal freq)
{
    freq = freq < 0 ? globalUserVariable->gbitsspan : freq;

    //Tony 0906
    freq = globalUserVariable->adjustSpanBySpan(freq);
    //Tony 0907
    if(globalUserVariable->gAutoRbw == RTSA_MANUAL)
    {
          globalUserVariable->adjustRbwBySpan(freq);
    }
    else
    {
        globalUserVariable->gRbw=RTSA_RbwManualList[globalUserVariable->gFTTWindows][globalUserVariable->gRbwGrade][1];
        if(globalUserVariable->gFTTWindows == RTSA_RECTANGULAR)
        {
            globalUserVariable->gRbw=RTSA_RbwManualList[globalUserVariable->gFTTWindows][globalUserVariable->gRbwGrade][6];
        }
        else
        {
            globalUserVariable->gRbw=RTSA_RbwManualList[globalUserVariable->gFTTWindows][globalUserVariable->gRbwGrade][5];
        }
    }
    globalUserVariable->adjustFreqBySpan(freq);
    globalUserVariable->stepFreqCalculatorFunc();
//    globalUserVariable->markerPositionReCalculatorFunc();
}
void RtSa_Control::setFullSpan()
{
    quint32 tempFlag = 0;
//    sm_rtsa_config_rsa_ctrl->SpanMode = globalUserVariable->gSpanMode = 0;//Johnson Steve
    //change by Steve,0228
    globalUserVariable->gLastSpanFreq =  globalUserVariable->gSpanFreq;
    // Tony 0910
    globalUserVariable->gSpanFreq = RTSA_SPAN_STEP_VALUE[RTSA_SPAN_INTERVAL_NUMBER-1];
    globalUserVariable->adjustFreqBySpan(globalUserVariable->gSpanFreq);

    globalUserVariable->gRbwGrade=RTSA_SPAN_INTERVAL_NUMBER-1;
    if(globalUserVariable->gAutoRbw == RTSA_MANUAL)
    {
        globalUserVariable->adjustRbwBySpan(globalUserVariable->gSpanFreq);
    }
    else
    {
        globalUserVariable->gRbw=RTSA_RbwManualList[globalUserVariable->gFTTWindows][globalUserVariable->gRbwGrade][1];
        if(globalUserVariable->gFTTWindows == RTSA_RECTANGULAR)
        {
            globalUserVariable->gRbw=RTSA_RbwManualList[globalUserVariable->gFTTWindows][globalUserVariable->gRbwGrade][6];
        }
        else
        {
            globalUserVariable->gRbw=RTSA_RbwManualList[globalUserVariable->gFTTWindows][globalUserVariable->gRbwGrade][5];
        }
    }
    //by Steve,0228
    globalUserVariable->converFreqToShm();
    adjustAcqtime(globalUserVariable->gAcqTime);
    if(globalUserVariable->grbwChangedbyFreq)
    {
//        globalUserVariable->convertBwToShm();
        //less
        sm_rtsa_config_rsa_ctrl->ischangeRbwitself = 0;
        tempFlag |= IXS_RTSA_CenterFreq|IXS_RTSA_SpanFreq|IXS_RTSA_StartFreq|IXS_RTSA_StopFreq|IXS_RTSA_RBW|IXS_RTSA_AcqTime;
    }
    else
    {
        tempFlag |= IXS_RTSA_CenterFreq|IXS_RTSA_SpanFreq|IXS_RTSA_StartFreq|IXS_RTSA_StopFreq|IXS_RTSA_AcqTime;
    }
    globalUserVariable->stepFreqCalculatorFunc();
//    bwSweepSettingDisplayFunc();
    globalUserVariable->converFreqToShm();
    if(getTrigger() == RTSA_TRIGGER_PERIODIC_TIMER)
    {
        AdjustPeriodTime(globalUserVariable->gPeriodTrigTime);
        tempFlag |= IXS_RTSA_Trigger_Period;
    }
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl, tempFlag);
    }
    return;
}
void RtSa_Control::setCFStep(qreal freq)
{
    globalUserVariable->gCFFreq = freq;
    if(freq < RTSA_HZ)
    {
        globalUserVariable->gCFFreq = 1;
    }
    else if(freq > RTSA_SPEC_FREQ_MAX)
    {
        globalUserVariable->gCFFreq = RTSA_SPEC_FREQ_MAX;
    }
    return;
}
qreal RtSa_Control::getCFStep()
{
    return globalUserVariable->gCFFreq;
}
void RtSa_Control::adjustAcqtime(qreal time)
{
    if(time > RTSA_ACQTIME_MAX)
    {
        time = RTSA_ACQTIME_MAX;
    }
    if(globalUserVariable->gAutoAcqTime == RTSA_AUTO)
    {
        time = RTSA_ACQ_DEFAULT_TIME;
    }
    if(time <= AcqTime_Min_List[globalUserVariable->gRbwGrade])
    {
        time = AcqTime_Min_List[globalUserVariable->gRbwGrade];
    }
    else if(time >= AcqTime_Max_List[globalUserVariable->gRbwGrade])
    {
        time = AcqTime_Max_List[globalUserVariable->gRbwGrade];
    }
    globalUserVariable->gAcqTime = time;

    //change ms to s
    sm_rtsa_config_rsa_ctrl->acqtimems = globalUserVariable->gAcqTime / RTSA_S;

//    globalUserVariable->gSleepTime = globalUserVariable->gAcqTime;
    return;
}
void RtSa_Control::amplitudeAttenControl()
{
    //Johnson Add
    if(globalUserVariable->gAtten == RTSA_AUTO)
    {
        if(globalUserVariable->gRefLevel-5.>=0.)
        {
            globalUserVariable->gPreamp = RTSA_OFF;
        }

        if(globalUserVariable->gPreamp == RTSA_OFF)
        {
            if(globalUserVariable->gRefLevel-15.>0.)      globalUserVariable->gAttenValue = 30.;
            else if(globalUserVariable->gRefLevel-10.>0.) globalUserVariable->gAttenValue = 25.;
            else if(globalUserVariable->gRefLevel-5.>0.)  globalUserVariable->gAttenValue = 20.;
            else if(globalUserVariable->gRefLevel>0.)     globalUserVariable->gAttenValue = 15.;
            else if(globalUserVariable->gRefLevel+5.>0.)  globalUserVariable->gAttenValue = 10.;
            else if(globalUserVariable->gRefLevel+10.>0.) globalUserVariable->gAttenValue = 5.;


            if(globalUserVariable->gRefLevel+10.<=0.)     globalUserVariable->gAttenValue = 0.;
        }
        else
        {
            if(globalUserVariable->gRefLevel+5.>0.&&globalUserVariable->gRefLevel<=0) globalUserVariable->gAttenValue = 30.;
            else if(globalUserVariable->gRefLevel+10.>0.)                             globalUserVariable->gAttenValue = 25.;
            else if(globalUserVariable->gRefLevel+15.>0.)                             globalUserVariable->gAttenValue = 20.;
            else if(globalUserVariable->gRefLevel+20.>0.)                             globalUserVariable->gAttenValue = 15.;
            else if(globalUserVariable->gRefLevel+25.>0.)                             globalUserVariable->gAttenValue = 10.;
            else if(globalUserVariable->gRefLevel+30.>0.)                             globalUserVariable->gAttenValue = 5.;


            if(globalUserVariable->gRefLevel+30.<=0)                                  globalUserVariable->gAttenValue = 0.;
        }
    }
    else
    {
        if(globalUserVariable->gPreamp != RTSA_OFF)
        {
            if(globalUserVariable->gAttenValue > 30)
                globalUserVariable->gAttenValue = 30;
        }

    }
}
void RtSa_Control::setRefLevel(qreal refLevel)
{
    quint32 uFlag = 0;
    ChangeOtherUnitTodBm(refLevel);
    if(globalUserVariable->gRefLevel>0.)
    {
        if(globalUserVariable->gPreamp == RTSA_ON)
        {
            globalUserVariable->gPreamp = RTSA_OFF;
            //Pream ON/OFF Control 0503
            sm_rtsa_config_rsa_ctrl->Preamp = globalUserVariable->gPreamp;
            sm_rtsa_config_rsa_ctrl->uisPreampChangedItself = 0;
            uFlag |= IXS_RTSA_Preamp;
        }
    }
    amplitudeAttenControl();
    //Ref_Level Control 0503
    sm_rtsa_config_rsa_ctrl->RefLevel = globalUserVariable->gRefLevel;
    uFlag |= IXS_RTSA_RefLevel;
    //Johnson 0730
    //AttenValue Control
    sm_rtsa_config_rsa_ctrl->attenValue = globalUserVariable->gAttenValue;
    if(globalUserVariable->gAttenValue > 0.)
    {
        uFlag |= IXS_RTSA_AttenSelect;
    }

    globalUserVariable->gdpxApmtMin = globalUserVariable->gRefLevel /*+ globalUserVariable->gRefOffset*/ - globalUserVariable->gScaleDiv * 10 + RTSA_COMP_TEMPDATA;
    globalUserVariable->gdpxAmptZoom = 200 / (globalUserVariable->gScaleDiv * 10);

    sm_rtsa_config_rsa_ctrl->dpxApmtMin = DecToBin(globalUserVariable->gdpxApmtMin,12);
    sm_rtsa_config_rsa_ctrl->dpxApmtZoom = DecToBin(globalUserVariable->gdpxAmptZoom,8);

    uFlag  = uFlag | IXS_RTSA_DPXAmptMin | IXS_RTSA_DPXAmptZoom;

    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,uFlag);
    }

//    globalUserVariable->entryInputMode = INPUT_REF_LEVEL;
    return;
}
void RtSa_Control::ChangeOtherUnitTodBm(qreal refLevel)
{
    qreal value = refLevel;
    switch (globalUserVariable->gAmptdUnit) {
    case RTSA_WATTS: //
        value = globalUserVariable->wattsToDbmCalculatorFunc(refLevel);
        break;
    case RTSA_VOLT:  //
        value = globalUserVariable->voltToDbmCalculatorFunc(refLevel);
        break;
    case RTSA_DBMV:
        value -= RTSA_dBmVFix;
        break;
    case RTSA_DBUV:
        value -= RTSA_dBuVFix;
        break;
    case RTSA_DBV:
        value -= RTSA_dBVFix;
        break;
    default:
        value = refLevel;
        break;
    }
    // Only 2 decimal places reserved
    if(value >= 0)
    {
        value = (qreal)(qint64)((value + 0.005) * 100) / 100;
    }
    else
    {
        value = (qreal)(qint64)((value - 0.005) * 100) / 100;
    }
    globalUserVariable->gRefLevel = value;
    if(value < RTSA_SPEC_AMPTD_MIN)
    {
        globalUserVariable->gRefLevel = RTSA_SPEC_AMPTD_MIN;
    }
    else if(value > RTSA_SPEC_AMPTD_MAX)
    {
        globalUserVariable->gRefLevel = RTSA_SPEC_AMPTD_MAX;
    }
    return;
}
qreal RtSa_Control::getRefLevel()
{
    qreal reflevel = globalUserVariable->gRefLevel;
//    qreal tempVal = 0.;
    qreal value = 0;
//    switch (globalUserVariable->gAmptdUnit) {
//    case RTSA_WATTS: //
//        value = qPow(10, reflevel / 10.) / 1000;
////        value = globalUserVariable->wattsToDbmCalculatorFunc(tempVal);
//        break;
//    case RTSA_VOLT:  //
//        tempVal = qPow(10, reflevel / 10.);
//        value = qPow(50 * tempVal * 0.001, 0.5);//uv
////        value = globalUserVariable->voltToDbmCalculatorFunc(tempVal);
//        break;
//    case RTSA_DBMV:
//        value += RTSA_dBmVFix;
//        break;
//    case RTSA_DBUV:
//        value += RTSA_dBuVFix;
//         break;
//    default:
        value = reflevel;
//    }
    return value;
}
void RtSa_Control::setAttenAuto(bool isAttenAuto)
{
    globalUserVariable->gAtten = isAttenAuto;
    amplitudeAttenControl();
    sm_rtsa_config_rsa_ctrl->attenValue = globalUserVariable->gAttenValue;
    sm_rtsa_config_rsa_ctrl->attenAuto = globalUserVariable->gAtten;
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,IXS_RTSA_AttenSelect);
    }
    return;
}
bool RtSa_Control::IsAttenAuto()
{
    return globalUserVariable->gAtten;
}
void RtSa_Control::setAttenVal(qreal attenVal)
{
    if(attenVal < 0)
        attenVal = 0;
    else if(attenVal > 50)
            attenVal = 50;
    globalUserVariable->gAtten = RTSA_MANUAL;
    int attenIndex = qCeil((attenVal) / 5);
    if(globalUserVariable->gPreamp == RTSA_OFF && globalUserVariable->gAtten == RTSA_MANUAL)
    {
        if(attenIndex > 10)
        {
            attenIndex = 10;
        }
        globalUserVariable->gAttenValue = attenIndex * 5;
    }
    else
    {
        if(attenIndex > 6)
        {
         attenIndex = 6;
        }
        globalUserVariable->gAttenValue = attenIndex * 5;
    }
    amplitudeAttenControl();
    sm_rtsa_config_rsa_ctrl->attenValue = globalUserVariable->gAttenValue;
    sm_rtsa_config_rsa_ctrl->attenAuto = globalUserVariable->gAtten;
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,IXS_RTSA_AttenSelect);
    }
    return;
}
qreal RtSa_Control::getAttenVal()
{
    return globalUserVariable->gAttenValue;
}
void RtSa_Control::setAmptUnit(qint32 unitIndex)
{
    if(unitIndex < RTSA_DBM)
        unitIndex = RTSA_DBM;
    else if(unitIndex > RTSA_WATTS)
        unitIndex = RTSA_WATTS;
    globalUserVariable->gAmptdUnit = unitIndex;
}
qint32 RtSa_Control::getAmptUint()
{
    return globalUserVariable->gAmptdUnit;
}
void RtSa_Control::setPreAmpOn(bool IsOn)
{
    if(globalUserVariable->gRefLevel > 0.0)
        return;
    if(IsOn == globalUserVariable->gPreamp)
    {
        return;
    }
    globalUserVariable->gPreamp = IsOn;
    amplitudeAttenControl();
    //Preamp   On / Off Control
    sm_rtsa_config_rsa_ctrl->Preamp = globalUserVariable->gPreamp;
    sm_rtsa_config_rsa_ctrl->uisPreampChangedItself = 1;

    sm_rtsa_config_rsa_ctrl->attenValue = globalUserVariable->gAttenValue;
    sm_rtsa_config_rsa_ctrl->attenAuto = globalUserVariable->gAtten;
//    RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,IXS_RTSA_AttenSelect);
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,IXS_RTSA_Preamp | IXS_RTSA_AttenSelect);
    }
    return;
}
bool RtSa_Control::IsPreAmpOn()
{
    return globalUserVariable->gPreamp;
}
void RtSa_Control::setSingleSweep(bool isSingle)
{
    globalUserVariable->gSweepType = isSingle;
    sm_rtsa_config_rsa_ctrl->SweepType = globalUserVariable->gSweepType;
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,IXS_RTSA_SweepType);
    }

//    return;
}
bool RtSa_Control::IsSingleSweep()
{
    return globalUserVariable->gSweepType;
}
/**
* @brief setDectorType
* @param [in] DectorType
* @Author Albert
* @date 2019-04-16
*/
void RtSa_Control::setDectorType(qint32 DectorType)
{
    if(DectorType < RTSA_DEC_PEAK)
        DectorType = RTSA_DEC_PEAK;
    else if(DectorType > RTSA_DEC_RMS)
        DectorType = RTSA_DEC_RMS;
    if(gDector == DectorType)
    {
        return;
    }
    gDector = DectorType;
    globalUserVariable->gDetectorMode = gDector;
    sm_rtsa_config_rsa_ctrl->DetectorMode = gDector;
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,IXS_RTSA_DetectorMode);
    }
    return;
}
/**
* @brief getDectorType
* @param none
* @Author Albert
* @date 2019-04-16
*/
qint32 RtSa_Control::getDectorType()
{
    return gDector;
}
/**
* @brief setTrigger
* @param [in] TriggerMode
* @Author Albert
* @date 2019-04-16
*/
void RtSa_Control::setTrigger(qint32 TriggerMode)
{
    quint32 mode = 0xffff;
//    quint32 slopemode = globalUserVariable->gTriggerSlope;
    if(TriggerMode < RTSA_TRIGGER_FREE_RUN)
        TriggerMode = RTSA_TRIGGER_FREE_RUN;
    else if(TriggerMode >= RTSA_TRIGGER_FMTMASK)
        TriggerMode = RTSA_TRIGGER_FMTMASK;
    if(TriggerMode == globalUserVariable->gTriggerMode)
    {
        return;
    }
    globalUserVariable->gTriggerMode = TriggerMode;
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_FREE_RUN:
//        slopemode = slopemode << 8;
        mode &= 0x1;
        break;
    case RTSA_TRIGGER_VIDEO:
//        slopemode = slopemode << 12;
        mode &= 0x10;
        break;
    case RTSA_TRIGGER_EXTERNAL:
//        slopemode = slopemode << 9;
        mode &= 0x2;
        sm_rtsa_config_rsa_ctrl->triggerSlope = globalUserVariable->gTriggerExternSlope;
        sm_rtsa_config_rsa_ctrl->triggerDelay = (globalUserVariable->gExternTrigDelay) / RTSA_S * RTSA_FFT_SAMPLE;
        sm_rtsa_config_rsa_ctrl->triggerHoldOffTime = (globalUserVariable->gExternHoldOff) / RTSA_S * RTSA_FFT_SAMPLE;
        break;
    case RTSA_TRIGGER_PERIODIC_TIMER:
        mode &= 0x4;
        AdjustPeriodTime(globalUserVariable->gPeriodTrigTime);
        sm_rtsa_config_rsa_ctrl->triggerDelay = (globalUserVariable->gPeriodTrigDelay) / RTSA_S * RTSA_FFT_SAMPLE;
        break;
    case RTSA_TRIGGER_RF_BURST:
//        slopemode = slopemode << 11;
        mode &= 0x8;
        sm_rtsa_config_rsa_ctrl->triggerRFBurstLevel = qPow(10,(globalUserVariable->gRFBurstTrigLevel + RTSA_COMP_TEMPDATA)/20);
        sm_rtsa_config_rsa_ctrl->triggerSlope = globalUserVariable->gTriggerRFBurstSlope;
        sm_rtsa_config_rsa_ctrl->triggerDelay = (globalUserVariable->gRFBurstTrigDelay) / RTSA_S * RTSA_FFT_SAMPLE;
        sm_rtsa_config_rsa_ctrl->triggerHoldOffTime = (globalUserVariable->gRFBurstHoldOff) / RTSA_S * RTSA_FFT_SAMPLE;
        break;
    case RTSA_TRIGGER_FMTMASK:
        mode &= 0x20;
        sm_rtsa_config_rsa_ctrl->triggerHoldOffTime = (globalUserVariable->gFMTHoldOff) / RTSA_S * RTSA_FFT_SAMPLE;
        break;
    default:
        break;
    }
//    mode |= slopemode;

    sm_rtsa_config_rsa_ctrl->TriggerMode = mode;
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,IXS_RTSA_TriggerMode);
    }
    return;
}
/**
* @brief getTrigger
* @param none
* @Author Albert
* @date 2019-04-16
*/
qint32 RtSa_Control::getTrigger()
{
    return globalUserVariable->gTriggerMode;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-03
*/
void RtSa_Control::setTriggerSlope(qint32 TriggerMode, qint32 slope)
{
    quint32 slopeFlag = 0;
    if(slope == 1)
        slopeFlag = 1;
    else
        slopeFlag = 0;

    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        globalUserVariable->gTriggerVideoSlope = slope;
        slopeFlag = slopeFlag << 4;
        break;
    case RTSA_TRIGGER_EXTERNAL:
        globalUserVariable->gTriggerExternSlope = slope;
        slopeFlag = slopeFlag << 1;
        break;
    case RTSA_TRIGGER_RF_BURST:
        globalUserVariable->gTriggerRFBurstSlope = slope;
        slopeFlag = slopeFlag << 3;
        break;
    default:
        break;
    }
    globalUserVariable->gTriggerSlope = slope;

    sm_rtsa_config_rsa_ctrl->triggerSlope = slopeFlag;
    // if set params not used in current trigger mode, here should not set to fpga
    if(TriggerMode != globalUserVariable->gTriggerMode)
    {
        return;
    }
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_Trigger,IXS_RTSA_Trigger_Slope);
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-03
*/
qint32 RtSa_Control::getTriggerSlope(qint32 TriggerMode)
{
    qint32 slope = 0;
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        slope = globalUserVariable->gTriggerVideoSlope;
        break;
    case RTSA_TRIGGER_EXTERNAL:
        slope = globalUserVariable->gTriggerExternSlope;
        break;
    case RTSA_TRIGGER_RF_BURST:
        slope = globalUserVariable->gTriggerRFBurstSlope;
        break;
    default:
        break;
    }
//    RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,IXS_RTSA_TriggerMode);

    return slope;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-03
*/
void RtSa_Control::setTriggerLevel(qint32 TriggerMode, qreal level)
{
    //log scale to line scale
    qreal levelVal = 0;
    qreal tempVal = qPow(10, level / 10.);
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        levelVal = qPow(10,(level + RTSA_COMP_TEMPDATA)/20);
        globalUserVariable->gVideoTrigLevel = level;
        sm_rtsa_config_rsa_ctrl->triggerVideoLevel = levelVal;
        if(TriggerMode != globalUserVariable->gTriggerMode)
        {
            return;
        }
        if(!globalUserVariable->gRefreshAllParam)
        {
            RtSa_Set_config_flag(IXT_RTSA_Trigger,IXS_RTSA_Trigger_Video_Level);
        }
        break;
    case RTSA_TRIGGER_EXTERNAL:
        globalUserVariable->gExternTrigLevel = level;
        break;
    case RTSA_TRIGGER_RF_BURST:
        globalUserVariable->gRFBurstTrigLevel = level;
//        levelVal = qPow(50 * tempVal * 0.001, 0.5);//v
        levelVal = qPow(10,(level + RTSA_COMP_TEMPDATA)/20);
        sm_rtsa_config_rsa_ctrl->triggerRFBurstLevel = levelVal;
        if(TriggerMode != globalUserVariable->gTriggerMode)
        {
            return;
        }
        if(!globalUserVariable->gRefreshAllParam)
        {
            RtSa_Set_config_flag(IXT_RTSA_Trigger,IXS_RTSA_Trigger_RF_Level);
        }
        break;
    default:
        break;
    }

    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-03
*/
qreal RtSa_Control::getTriggerLevel(qint32 TriggerMode)
{
    qreal triggerLevel = 0;
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        triggerLevel = globalUserVariable->gVideoTrigLevel;
        break;
    case RTSA_TRIGGER_EXTERNAL:
        triggerLevel = globalUserVariable->gExternTrigLevel;
        break;
    case RTSA_TRIGGER_RF_BURST:
        triggerLevel = globalUserVariable->gRFBurstTrigLevel;
        break;
    default:
        break;
    }
    return triggerLevel;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
void RtSa_Control::setTriggerDelayStatus(qint32 TriggerMode, bool delayStatus)
{
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        globalUserVariable->gVideoTrigDelayStatus = delayStatus;
        break;
    case RTSA_TRIGGER_EXTERNAL:
        globalUserVariable->gExternTrigDelayStatus = delayStatus;
        break;
    case RTSA_TRIGGER_RF_BURST:
        globalUserVariable->gRFBurstTrigDelayStatus = delayStatus;
        break;
    case RTSA_TRIGGER_PERIODIC_TIMER:
        globalUserVariable->gPeriodTrigDelayStatus = delayStatus;
        break;
    default:
        break;
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
bool RtSa_Control::getTriggerDelayStatus(qint32 TriggerMode)
{
    bool delayStatus = 0;
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        delayStatus = globalUserVariable->gVideoTrigDelayStatus;
        break;
    case RTSA_TRIGGER_EXTERNAL:
        delayStatus = globalUserVariable->gExternTrigDelayStatus;
        break;
    case RTSA_TRIGGER_RF_BURST:
        delayStatus = globalUserVariable->gRFBurstTrigDelayStatus;
        break;
    case RTSA_TRIGGER_PERIODIC_TIMER:
        delayStatus = globalUserVariable->gPeriodTrigDelayStatus;
        break;
    default:
        break;
    }
    return delayStatus;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
void RtSa_Control::setTriggerDelay(qint32 TriggerMode, qreal Delay)
{
    if(Delay > RTSA_ACQTIME_MAX)
    {
        Delay = RTSA_ACQTIME_MAX;
    }
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        globalUserVariable->gVideoTrigDelay = Delay;
        break;
    case RTSA_TRIGGER_EXTERNAL:
        globalUserVariable->gExternTrigDelay = Delay;
        break;
    case RTSA_TRIGGER_RF_BURST:
        globalUserVariable->gRFBurstTrigDelay = Delay;
        break;
    case RTSA_TRIGGER_PERIODIC_TIMER:
        globalUserVariable->gPeriodTrigDelay = Delay;
        break;
    default:
        break;
    }
    Delay /= RTSA_S;
    Delay = Delay * RTSA_FFT_SAMPLE;
    sm_rtsa_config_rsa_ctrl->triggerDelay = Delay;
    if(TriggerMode != globalUserVariable->gTriggerMode)
    {
        return;
    }
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_Trigger,IXS_RTSA_Trigger_Delay);
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
qreal RtSa_Control::getTriggerDelay(qint32 TriggerMode)
{
    qreal delay = 0;
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        delay = globalUserVariable->gVideoTrigDelay;
        break;
    case RTSA_TRIGGER_EXTERNAL:
        delay = globalUserVariable->gExternTrigDelay;
        break;
    case RTSA_TRIGGER_RF_BURST:
        delay = globalUserVariable->gRFBurstTrigDelay;
        break;
    case RTSA_TRIGGER_PERIODIC_TIMER:
        delay = globalUserVariable->gPeriodTrigDelay;
        break;
    default:
        break;
    }
    return delay;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
void RtSa_Control::setTriggerPeriodTime(qreal time)
{
//    quint32 Periodtime = 0;
//    if(time > RTSA_ACQTIME_MAX)
//    {
//        time = RTSA_ACQTIME_MAX;
//    }
//    if(time <= AcqTime_Min_List[globalUserVariable->gRbwGrade]/3)
//    {
//        time = AcqTime_Min_List[globalUserVariable->gRbwGrade]/3;
//    }

//    globalUserVariable->gPeriodTrigTime = time;

//    time = time / RTSA_S;
//    Periodtime = time * (RTSA_FFT_SAMPLE);
//    sm_rtsa_config_rsa_ctrl->triggerPeriod = Periodtime;
    AdjustPeriodTime(time);
    if(RTSA_TRIGGER_PERIODIC_TIMER != globalUserVariable->gTriggerMode)
    {
        return;
    }
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_Trigger,IXS_RTSA_Trigger_Period);
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
qreal RtSa_Control::getTriggerPeriodTime()
{
    return globalUserVariable->gPeriodTrigTime;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-17
*/
void RtSa_Control::settriggerHoldOffTime(qint32 TriggerMode, qreal holdOffTime)
{
    if(holdOffTime < 30000)
    {
        holdOffTime = 30000;
    }
    else if(holdOffTime > RTSA_ACQTIME_MAX)
    {
        holdOffTime = RTSA_ACQTIME_MAX;
    }
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        globalUserVariable->gVideoHoldOff = holdOffTime;
        break;
    case RTSA_TRIGGER_EXTERNAL:
        globalUserVariable->gExternHoldOff = holdOffTime;
        break;
    case RTSA_TRIGGER_RF_BURST:
        globalUserVariable->gRFBurstHoldOff = holdOffTime;
        break;
    case RTSA_TRIGGER_FMTMASK:
        globalUserVariable->gFMTHoldOff = holdOffTime;
        break;
    default:
        break;
    }
    holdOffTime /= RTSA_S;
    holdOffTime = holdOffTime * RTSA_FFT_SAMPLE;

    sm_rtsa_config_rsa_ctrl->triggerHoldOffTime = holdOffTime;
    if(TriggerMode != globalUserVariable->gTriggerMode)
    {
        return;
    }
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_Trigger,IXS_RTSA_Trigger_HoldOff);
    }

    return;
}
qreal RtSa_Control::getriggerHoldOffTime(qint32 TriggerMode)
{
    qreal holdTime = 0;
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        holdTime = globalUserVariable->gVideoHoldOff;
        break;
    case RTSA_TRIGGER_EXTERNAL:
        holdTime = globalUserVariable->gExternHoldOff;
        break;
    case RTSA_TRIGGER_RF_BURST:
        holdTime = globalUserVariable->gRFBurstHoldOff;
        break;
    case RTSA_TRIGGER_FMTMASK:
        holdTime = globalUserVariable->gFMTHoldOff;
        break;
    default:
        break;
    }
    return holdTime;
}

void RtSa_Control::AdjustPeriodTime(qreal time)
{
    quint32 Periodtime = 0;
    if(time > RTSA_ACQTIME_MAX)
    {
        time = RTSA_ACQTIME_MAX;
    }
    else if(time < RTSA_HOLDOFF_TIME_MIN)
    {
        time = RTSA_HOLDOFF_TIME_MIN;
    }
    if(time <= AcqTime_Min_List[globalUserVariable->gRbwGrade]/3)
    {
        time = AcqTime_Min_List[globalUserVariable->gRbwGrade]/3;
    }

    globalUserVariable->gPeriodTrigTime = time;

    time = time / RTSA_S;
    Periodtime = time * (RTSA_FFT_SAMPLE);
    sm_rtsa_config_rsa_ctrl->triggerPeriod = Periodtime;
    return ;
}
/**
* @brief setBWAuto
* @param [in] isAuto
* @Author Albert
* @date 2019-04-16
*/
void RtSa_Control::setBWAuto(bool isAuto)
{
    sm_rtsa_config_rsa_ctrl->RBWAuto = globalUserVariable->gAutoRbw;
    sm_rtsa_config_rsa_ctrl->RBW = globalUserVariable->gRbwIndex;
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,IXS_RTSA_RBW|IXS_RTSA_RBWAuto);
    }
    return;
}
/**
* @brief setBW
* @param [in] rbw
* @Author Albert
* @date 2019-04-16
*/
void RtSa_Control::setBW(qreal rbw)
{
    sm_rtsa_config_rsa_ctrl->RBWAuto = globalUserVariable->gAutoRbw;
    sm_rtsa_config_rsa_ctrl->RBW = globalUserVariable->gRbwIndex;
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,IXS_RTSA_RBW|IXS_RTSA_RBWAuto);
    }
    return;
}
/**
* @brief setBWFFTWindow
* @param [in] fftwindow
* @Author Albert
* @date 2019-04-16
*/
void RtSa_Control::setBWFFTWindow(qint32 fftwindow)
{
    globalUserVariable->gFTTWindows = fftwindow;
    sm_rtsa_config_rsa_ctrl->RBW = globalUserVariable->gRbwIndex;
    sm_rtsa_config_rsa_ctrl->flitertype = globalUserVariable->gFTTWindows;
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,IXS_RTSA_RBW|IXS_RTSA_FilterType);
    }
    return;
}
/**
* @brief setAcqTime
* @param [in] time
* @Author Albert
* @date 2019-04-16
*/
void RtSa_Control::setAcqTime(qreal time)
{
    qreal acqtime = 0;
    if(time > RTSA_ACQTIME_MAX)
    {
        time = RTSA_ACQTIME_MAX;
    }
    if(time <= AcqTime_Min_List[globalUserVariable->gRbwGrade])
    {
        globalUserVariable->gAcqTime = AcqTime_Min_List[globalUserVariable->gRbwGrade];
    }
    else if(time >= AcqTime_Max_List[globalUserVariable->gRbwGrade])
    {
        globalUserVariable->gAcqTime = AcqTime_Max_List[globalUserVariable->gRbwGrade];
    }
    else
    {
        globalUserVariable->gAcqTime = time;
    }
    //change ms to s
    sm_rtsa_config_rsa_ctrl->acqtimems = globalUserVariable->gAcqTime / RTSA_S;
//    sm_rtsa_config_rsa_ctrl->acqtimeword = (quint32)(globalUserVariable->gAcqTime / 1000.);
//    sm_rtsa_config_rsa_ctrl->acqtimems = sm_rtsa_config_rsa_ctrl->acqtimeword * 50000.0;
//    globalUserVariable->gAcqTime = sm_rtsa_config_rsa_ctrl->acqtimeword * 50000.0;
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,IXS_RTSA_AcqTime);
    }
    return;

}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-29
*/
void RtSa_Control::setPersistenceInfinite(bool isInfinite)
{
    if(isInfinite == RTSA_INFINITE)
    {
        sm_rtsa_config_rsa_ctrl->persistimeword = 127;
        if(!globalUserVariable->gRefreshAllParam)
        {
            RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,IXS_RTSA_PersisTime);
        }
    }
    else
    {
        setPersistenceTime(globalUserVariable->gPersistenceTime);
    }
    return;
}
/**
* @brief setPersistenceTime
* @param [in] time
* @Author Albert
* @date 2019-04-16
*/
void RtSa_Control::setPersistenceTime(qreal time)
{
    sm_rtsa_config_rsa_ctrl->persistimems = globalUserVariable->gPersistenceTime;
    sm_rtsa_config_rsa_ctrl->persistimeword = (quint32)((globalUserVariable->gPersistenceTime)/50000.0);

    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,IXS_RTSA_PersisTime);
    }
    return;
}
/**
* @brief setDpxAmptMin
* @param none
* @Author Albert
* @date 2019-04-16
*/
void RtSa_Control::setDpxAmptMin()
{
    //add Dpx apmt min calculate 19/04/12 Albert
    globalUserVariable->gdpxApmtMin = globalUserVariable->gRefLevel /*+ globalUserVariable->gRefOffset*/ - globalUserVariable->gScaleDiv * 10 + RTSA_COMP_TEMPDATA;
    sm_rtsa_config_rsa_ctrl->dpxApmtMin = DecToBin(globalUserVariable->gdpxApmtMin,12);
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,IXS_RTSA_DPXAmptMin | IXS_RTSA_DPXAmptZoom);
    }
    return;
}
/**
* @brief setDpxAmptZoom
* @param none
* @Author Albert
* @date 2019-04-16
*/
void RtSa_Control::setDpxAmptZoom()
{
    globalUserVariable->gdpxAmptZoom = 200 / (globalUserVariable->gScaleDiv * 10);
    sm_rtsa_config_rsa_ctrl->dpxApmtZoom = DecToBin(globalUserVariable->gdpxAmptZoom,8);
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,IXS_RTSA_DPXAmptZoom | IXS_RTSA_DPXAmptMin);
    }
    return;
}
/**
* @brief DecToBin
* @param [in] decData [in] FracPrecision
* @Author Albert
* @date 2019-04-16
*/
qint32 RtSa_Control::DecToBin(qreal decData, qint32 FracPrecision)
{
    qint32 BinData = 0xFFFFFFFF;
    qint32 BinDataFrac = 0;
    qint32 IntPart = 0;
    qreal FracPatt = 0;
    if(decData >= 0)
    {
        IntPart = (qint32)decData;
        BinData &= IntPart;
        FracPatt = decData - IntPart;


        BinDataFrac = (qint32)(FracPatt * pow(2,FracPrecision));
//        for(qint32 i = 0 ; i < FracPrecision; i++)
//        {
//          FracPatt = FracPatt * 2;
//          if(FracPatt >= 1)
//          {
//              BinDataFrac *= 2;
//              BinDataFrac |= 0x1;
//              FracPatt -= 1;
//          }
//        }
        BinData = (BinData << FracPrecision);
//        BinData *= pow(2,FracPrecision);
        BinData |= BinDataFrac;
    }
    else
    {
      decData = -decData;
      IntPart = (qint32)(decData);
      BinData &= IntPart;
      FracPatt = (decData) - IntPart;
      BinDataFrac = (qint32)(FracPatt * pow(2,FracPrecision));
//      for(qint32 i = 0 ; i < FracPrecision; i++)
//      {
//        FracPatt = FracPatt * 2;
//        if(FracPatt >= 1)
//        {
//            BinDataFrac *= 2;
//            BinDataFrac |= 0x1;
//            FracPatt -= 1;
//        }
//      }
      BinData = (BinData << FracPrecision);
//      BinData *= pow(2,FracPrecision);
      BinData |= BinDataFrac;
      BinData = ~BinData;
      BinData += 1;
    }
    return BinData;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-04-28
*/
void RtSa_Control::setGeneralDataToShm()
{
    sm_rtsa_config_rsa_ctrl->CenterFreq = globalUserVariable->gCenterFreq;
    sm_rtsa_config_rsa_ctrl->SpanFreq = globalUserVariable->gSpanFreq;
    sm_rtsa_config_rsa_ctrl->RBWAuto = globalUserVariable->gAutoRbw;
    sm_rtsa_config_rsa_ctrl->RBW = globalUserVariable->gRbwIndex;
    sm_rtsa_config_rsa_ctrl->attenValue = globalUserVariable->gAttenValue;
    sm_rtsa_config_rsa_ctrl->attenAuto = globalUserVariable->gAtten;
    sm_rtsa_config_rsa_ctrl->flitertype = globalUserVariable->gFTTWindows;
    sm_rtsa_config_rsa_ctrl->DetectorMode = globalUserVariable->gDetectorMode;
    sm_rtsa_config_rsa_ctrl->persistimeword = (quint32)((globalUserVariable->gPersistenceTime)/50000.0);
    globalUserVariable->gdpxApmtMin = globalUserVariable->gRefLevel/* + globalUserVariable->gRefOffset*/ - globalUserVariable->gScaleDiv * 10 + RTSA_COMP_TEMPDATA;
    sm_rtsa_config_rsa_ctrl->dpxApmtMin = DecToBin(globalUserVariable->gdpxApmtMin,12);
    sm_rtsa_config_rsa_ctrl->dpxApmtZoom = DecToBin(globalUserVariable->gdpxAmptZoom,8);
    adjustAcqtime(globalUserVariable->gAcqTime);
    setTrigger(globalUserVariable->gTriggerMode);
    setTriggerParam();
//    sm_rtsa_config_rsa_ctrl->TriggerMode = globalUserVariable->gTriggerMode;
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-10
*/
void RtSa_Control::setMeasType(quint32 measType)
{
    quint32 uFlag = 0;
//    if(globalUserVariable->gMeasurement == measType)
//    {
//        return;
//    }
    globalUserVariable->gMeasurement = measType;
    switch (measType) {
    case RTSA_SPECTRUM_SPECTROGRAM:
        uFlag = IXS_RTSA_Spectrum;
        break;
    case RTSA_SPECTROGRAM:
        uFlag = IXS_RTSA_Density;
        break;
    case RTSA_DENSITY:
        uFlag = IXS_RTSA_Density;
        break;
    case RTSA_DENSITY_SPECTROGRAM:
        uFlag = IXS_RTSA_Density_Spectrogram;
        break;
    default:
        break;
    }
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_MeasureCtrl,uFlag);
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-10
*/
void RtSa_Control::InitialParam(quint32 measType)
{
    quint32 uFlag = IXS_RTSA_SweepType;
    switch (measType) {
    case RTSA_SPECTRUM_SPECTROGRAM:
        uFlag |= IXS_RTSA_Spectrum;
        break;
    case RTSA_SPECTROGRAM:
        uFlag |= IXS_RTSA_Spectrogram;
        break;
    case RTSA_DENSITY:
        uFlag |= IXS_RTSA_Density;
        break;
    case RTSA_DENSITY_SPECTROGRAM:
        uFlag |= IXS_RTSA_Density_Spectrogram;
        break;
    default:
        break;
    }
    sm_rtsa_config_rsa_ctrl->SweepType = false;
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,IXS_RTSA_SweepType);
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-10
*/
void RtSa_Control::setHighestDensity(quint32 highest)
{
    sm_rtsa_config_rsa_ctrl->dpxHighestDensity = highest;
    sm_rtsa_config_rsa_ctrl->dpxLowestDensity = globalUserVariable->gLowestDensity;
    sm_rtsa_config_rsa_ctrl->dpxCurve = globalUserVariable->gCurve;

    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,IXS_RTSA_Highest_Density);
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-10
*/
void RtSa_Control::setLowestDensity(quint32 lowest)
{
    sm_rtsa_config_rsa_ctrl->dpxHighestDensity = globalUserVariable->gHighestDensity;
    sm_rtsa_config_rsa_ctrl->dpxLowestDensity = lowest;
    sm_rtsa_config_rsa_ctrl->dpxCurve = globalUserVariable->gCurve;
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,IXS_RTSA_Lowest_Density);
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-11
*/
void RtSa_Control::recalFmtAxisData()
{
    memcpy(sm_rtsa_config_rsa_ctrl->fmtData,globalUserVariable->gFmtData,sizeof(qint32) * 801);
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,IXS_RTSA_Fmt_Data);
    }
    return;
}

void RtSa_Control::setStartedFlag(quint32 flag)
{
    sm_startflag->startedflag = flag;
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-07-16
*/
void RtSa_Control::setConfigParam()
{
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,ISX_CONGIG_ALL_PARAM);
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-07-16
*/
void RtSa_Control::setMeasureParam()
{
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_MeasureCtrl,ISX_MEASURE_ALL_PARAM);
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-07-16
*/
void RtSa_Control::setTriggerParam()
{
    if(!globalUserVariable->gRefreshAllParam)
    {
        switch(globalUserVariable->gTriggerMode)
        {
        case RTSA_TRIGGER_FREE_RUN:
            break;
        case RTSA_TRIGGER_VIDEO:
            break;
        case RTSA_TRIGGER_EXTERNAL:
            RtSa_Set_config_flag(IXT_RTSA_Trigger,IXS_RTSA_Trigger_Slope|IXS_RTSA_Trigger_Delay
                                 |IXS_RTSA_Trigger_HoldOff);
            break;
        case RTSA_TRIGGER_PERIODIC_TIMER:
            RtSa_Set_config_flag(IXT_RTSA_Trigger,IXS_RTSA_Trigger_Period|IXS_RTSA_Trigger_Delay);
            break;
        case RTSA_TRIGGER_RF_BURST:
            RtSa_Set_config_flag(IXT_RTSA_Trigger,IXS_RTSA_Trigger_RF_Level|IXS_RTSA_Trigger_Slope
                                 |IXS_RTSA_Trigger_HoldOff|IXS_RTSA_Trigger_Delay);
            break;
        case RTSA_TRIGGER_FMTMASK:
            RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,IXS_RTSA_Fmt_Data);
            break;
        default:
            break;
        }
//        RtSa_Set_config_flag(IXT_RTSA_Trigger,ISX_TRIGGER_ALL_PARAM);
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-14
*/
void RtSa_Control::setDpxCurve(float curve)
{
    globalUserVariable->gCurve = curve;
    sm_rtsa_config_rsa_ctrl->dpxHighestDensity = globalUserVariable->gHighestDensity;
    sm_rtsa_config_rsa_ctrl->dpxLowestDensity = globalUserVariable->gLowestDensity;
    sm_rtsa_config_rsa_ctrl->dpxCurve = globalUserVariable->gCurve;
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,ISX_RTSA_Curve);
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-09
*/
void RtSa_Control::setFmtTriggerCriterion(qint32 criterion)
{
    if(globalUserVariable->gFmtTriggerCriterion == criterion)
        return;
    qint32 MaskIndex = 0;
    if(criterion < RTSA_FMT_MASK_NORMAL)
        criterion = RTSA_FMT_MASK_NORMAL;
    else if(criterion > RTSA_ENTER_UPP)
        criterion = RTSA_ENTER_UPP;
    globalUserVariable->gFmtTriggerCriterion = criterion;
    switch (criterion) {
    case RTSA_FMT_MASK_NORMAL:
        MaskIndex = 0;
        break;
    case RTSA_LEAVE_LOW:
        MaskIndex = 0xAAAA;
        break;
    case RTSA_ENTER_LOW:
        MaskIndex = 0xCCCC;
        break;
    case RTSA_LEAVE_UPP:
        MaskIndex = 0xF0F0;
        break;
    case RTSA_ENTER_UPP:
        MaskIndex = 0xFF00;
        break;
    default:
        break;
    }
    sm_rtsa_config_rsa_ctrl->FmtTriggerCriterion = MaskIndex;
    if(!globalUserVariable->gRefreshAllParam)
    {
        RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,IXS_Fmt_Trigger_Criterion);
    }
    return;
}

void RtSa_Control::getDpxRealProbability()
{
    RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,IXS_RTSA_DPX_Probability);
    QThread::msleep(200);
    globalUserVariable->gHighestDensity = sm_rtsa_config_rsa_ctrl->dpxHighestDensity;
    globalUserVariable->gLowestDensity = sm_rtsa_config_rsa_ctrl->dpxLowestDensity;
    return;
}
