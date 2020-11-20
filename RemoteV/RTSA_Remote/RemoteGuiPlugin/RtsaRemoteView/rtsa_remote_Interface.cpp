#include "rtsa_remote_interface.h"
#include "rtsa_extern.h"
#include <QFile>
#include <qthread.h>
#include "QEventLoop"

#define RTSA_FFT_SAMPLE  (184320000)

#define GET_SCPI_FROM_F238  //是否获取指令从下


//Albert 1018, cacahe data array 7000 * 821
double gSpectrogramCacheData[RTSA_SPECTROGRAM_CACHE_DATA][RTSA_TRACE_DATA_NUM] =
{
    0
};
#define SPECTROGRAM_SCREEN_MAX 283

int compare(const void* a,const void* b)
{
    double ret = *(double*)a - *(double*)b;
    if(ret > 0){
        return 1;
    }
    else if(ret < 0){
        return -1;
    }
    return 0;
}


Rtsa_Remote_Interface::Rtsa_Remote_Interface(QObject *parent) : QObject(parent)
  , bitviewtopdisplay(BV_TOP_APMTINFO)
  , curwindowindex(1)
  , wintotalnum(0)
  , mWidth(0)
  , mHeight(0)
  , mIsZoomIn(false)
  , mDragFlag(false)
  , mIsShiftKeyEnable(false)
  , mCurLimitDataPos(-1)
  , mIsCurBitViewSizeChange(false)
  , mFileType(RTSA_FILEHEADER_STATE)
  , isMarkerBtnPressed(false)
  , mFmtCurDataIndex(0)
  ,pSocketLinkStatus(0)
{
    gDpxData = NULL;
    pRemoteScpi = new RtSa_Remote_Scpi(this);
    bGetDataFromScpi = 0;
}

Rtsa_Remote_Interface::~Rtsa_Remote_Interface()
{
    delete pRemoteScpi;
    for(int i =0 ;i < RTSA_BITVIEWNUM; i++)
    {
        delete mBitView[i];
    }
}


void Rtsa_Remote_Interface::RecvScpiCmd(socketCmdAndRecvInfo socketData)
{
    if(socketData.strRecvCmd.size()>0)
        emit ScpiCmdFinished();
    else
    {
        updateTraceData(socketData.arrayRecv,RTSA_NUM_SWEEP_POINT);
        emit ScpiDataFinished();
    }
}


void Rtsa_Remote_Interface::ReadDataFromMeter()
{
    SendAndRecvScpi(RTSA_INPUT_FREQ_CENTER);
    SendAndRecvScpi(RTSA_INPUT_FREQ_START);
    SendAndRecvScpi(RTSA_INPUT_FREQ_STOP);
    SendAndRecvScpi(RTSA_INPUT_FREQ_STEP);
    SendAndRecvScpi(RTSA_INPUT_FREQ_OFFSET);
    SendAndRecvScpi(RTSA_INPUT_FREQ_SPAN);
    SendAndRecvScpi(RTSA_INPUT_FREQ_CHANNEL_STANDARD);
    SendAndRecvScpi(RTSA_INPUT_FREQ_CHANNEL_NUM);
    SendAndRecvScpi(RTSA_INPUT_FREQ_CHANNEL_STEP);//索引值
    SendAndRecvScpi(RTSA_BUTTON_CHANNEL_TYPE);

    SendAndRecvScpi(RTSA_INPUT_REF_LEVEL);
    SendAndRecvScpi(RTSA_BUTTON_ATTENUATION);
    SendAndRecvScpi(RTSA_INPUT_ATTEN);
    SendAndRecvScpi(RTSA_INPUT_SCALEDIV);
    SendAndRecvScpi(RTSA_INPUT_REF_OFFSET);
    SendAndRecvScpi(RTSA_SELECT_UNITS);
    SendAndRecvScpi(RTSA_BUTTON_PREAMP);

    SendAndRecvScpi(RTSA_BUTTON_SWEEP_TYPE);
    SendAndRecvScpi(RTSA_BUTTON_ACQ_TIME);
    SendAndRecvScpi(RTSA_INPUT_ACQ_TIME);

    SendAndRecvScpi(RTSA_BUTTON_RBW_AUTO);
    SendAndRecvScpi(RTSA_BUTTON_RBW);
    SendAndRecvScpi(RTSA_BUTTON_FFT_WINDOWS);

    SendAndRecvScpi(RTSA_SELECT_TRIGGER_SOURCE);
    SendAndRecvScpi(RTSA_INPUT_TRIGGER_LEVEL,RTSA_TRIGGER_VIDEO);
    SendAndRecvScpi(RTSA_INPUT_TRIGGER_LEVEL,RTSA_TRIGGER_EXTERNAL);
    SendAndRecvScpi(RTSA_INPUT_TRIGGER_LEVEL,RTSA_TRIGGER_RF_BURST);

    SendAndRecvScpi(RTSA_BUTTON_TRIGGER_STOPE,RTSA_TRIGGER_VIDEO);
    SendAndRecvScpi(RTSA_BUTTON_TRIGGER_STOPE,RTSA_TRIGGER_EXTERNAL);
    SendAndRecvScpi(RTSA_BUTTON_TRIGGER_STOPE,RTSA_TRIGGER_RF_BURST);

    SendAndRecvScpi(RTSA_BUTTON_TRIGGER_DELAY,RTSA_TRIGGER_VIDEO);
    SendAndRecvScpi(RTSA_BUTTON_TRIGGER_DELAY,RTSA_TRIGGER_EXTERNAL);
    SendAndRecvScpi(RTSA_BUTTON_TRIGGER_DELAY,RTSA_TRIGGER_RF_BURST);
    SendAndRecvScpi(RTSA_BUTTON_TRIGGER_DELAY,RTSA_TRIGGER_PERIODIC_TIMER);

    SendAndRecvScpi(RTSA_INPUT_TRIGGER_DELAY_VALUE,RTSA_TRIGGER_VIDEO);
    SendAndRecvScpi(RTSA_INPUT_TRIGGER_DELAY_VALUE,RTSA_TRIGGER_EXTERNAL);
    SendAndRecvScpi(RTSA_INPUT_TRIGGER_DELAY_VALUE,RTSA_TRIGGER_RF_BURST);
    SendAndRecvScpi(RTSA_INPUT_TRIGGER_DELAY_VALUE,RTSA_TRIGGER_PERIODIC_TIMER);

    SendAndRecvScpi(RTSA_INPUT_TRIGGER_PERTIMER);

    SendAndRecvScpi(RTSA_INPUT_TRIGGER_HOLDTIME,RTSA_TRIGGER_VIDEO);
    SendAndRecvScpi(RTSA_INPUT_TRIGGER_HOLDTIME,RTSA_TRIGGER_EXTERNAL);
    SendAndRecvScpi(RTSA_INPUT_TRIGGER_HOLDTIME,RTSA_TRIGGER_RF_BURST);
    SendAndRecvScpi(RTSA_INPUT_TRIGGER_HOLDTIME,RTSA_TRIGGER_FMTMASK);

    SendAndRecvScpi(RTSA_BUTTON_FMT_MASK_TYPE);
    SendAndRecvScpi(RTSA_SELECT_FMT_TRIGGER_CRITERION);
    SendAndRecvScpi(RTSA_FMT_DATA_NUM);
    for(int i = 0;i<  globalUserVariable->gMeterParam.gConfig_Trigger.fmtnumber;i++)
    {
        SendAndRecvScpi(RTSA_INPUT_FMT_FREQ,0,i);
        SendAndRecvScpi(RTSA_INPUT_FMT_AMPT,0,i);
    }

    for(int i = 0;i< RTSA_NUM_TRACE;i++)
    {
        SendAndRecvScpi(RTSA_BUTTON_TRACE_VIEW,i);
        SendAndRecvScpi(RTSA_SELECT_TRACE_TYPE,i);
        SendAndRecvScpi(RTSA_INPUT_TRACE_AVERAGE,i);
    }
    SendAndRecvScpi(RTSA_SELECT_TRACE_DETECTOR);
    SendAndRecvScpi(RTSA_BUTTON_MARKER_SELECT);
    for(int i = 0;i< RTSA_MARKER_TOTAL_CNT;i++)
    {
        SendAndRecvScpi(RTSA_BUTTON_MARKER_VIEW,i);
        SendAndRecvScpi(RTSA_BUTTON_MARKER_SEL,i);
        SendAndRecvScpi(RTSA_BUTTON_NOISE_MARKER,i);
        SendAndRecvScpi(RTSA_INPUT_MARKER_EDIT,i);
    }
    SendAndRecvScpi(RTSA_BUTTON_PEAK_TRACK);


    SendAndRecvScpi(RTSA_BUTTON_LIMIT_SELECT);

    SendAndRecvScpi(RTSA_BUTTON_LIMIT_TEST);
    for(int i = 0;i< RTSA_MARKER_TOTAL_CNT;i++)
    {
        SendAndRecvScpi(RTSA_BUTTON_LIMIT_LINE,i);
        SendAndRecvScpi(RTSA_BUTTON_LIMIT_EDGE,i);
        SendAndRecvScpi(RTSA_LIMIT_EDGE,i);
        SendAndRecvScpi(RTSA_BUTTON_LIMIT_TYPE,i);
        SendAndRecvScpi(RTSA_LIMIT_DATA_NUM,i);
        for(int j = 0;j< globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitEditNum[i];j++)
        {
            SendAndRecvScpi(RTSA_INPUT_LIMIT_FREQ,i,j);
            SendAndRecvScpi(RTSA_INPUT_LIMIT_AMPT,i,j);

        }
    }

    SendAndRecvScpi(RTSA_BUTTON_DISPLAY_MODLE);

    SendAndRecvScpi(RTSA_BUTTON_PERSISTENCE);
    SendAndRecvScpi(RTSA_INPUT_PERSISTENCE_TIME);
    SendAndRecvScpi(RTSA_INPUT_HIGHEST_DENSITY);
    SendAndRecvScpi(RTSA_INPUT_LOWEST_DENSITY);
    SendAndRecvScpi(RTSA_INPUT_CURVE);
}

void Rtsa_Remote_Interface::SendAndRecvScpi(qint32 index,  qint32  nModleID,qint32 nIndexNo)
{

    switch (index)
    {
    case RTSA_INPUT_FREQ_CENTER:
        pRemoteScpi->getCenterFreq();
        break;
    case RTSA_INPUT_FREQ_START:
        pRemoteScpi->getStartFreq();
        break;
    case RTSA_INPUT_FREQ_STOP:
        pRemoteScpi->getStopFreq();
        break;
    case RTSA_INPUT_FREQ_STEP:
        pRemoteScpi->getStepFreq();
        break;
    case RTSA_INPUT_FREQ_OFFSET:
        pRemoteScpi->getFreqOffset();
        break;
    case RTSA_INPUT_FREQ_SPAN:
        pRemoteScpi->getSpan();
        break;
    case  RTSA_INPUT_FREQ_CHANNEL_STANDARD:
        pRemoteScpi->getCHStandard();
        break;
    case  RTSA_INPUT_FREQ_CHANNEL_STEP:
        pRemoteScpi->getBandIndex();
        break;
    case  RTSA_INPUT_FREQ_CHANNEL_NUM:
        pRemoteScpi->getChannelNumber();
        break;
    case  RTSA_BUTTON_CHANNEL_TYPE:
        pRemoteScpi->getChannelType();
        break;
    case RTSA_INPUT_REF_LEVEL:
        pRemoteScpi->getRefLevel();
        break;
    case  RTSA_BUTTON_ATTENUATION:
        pRemoteScpi->IsAttenAuto();
        break;
    case RTSA_INPUT_ATTEN:
        pRemoteScpi->getAttenVal();
        break;
    case RTSA_INPUT_SCALEDIV:
        pRemoteScpi->getScaleDiv();
        break;
    case RTSA_INPUT_REF_OFFSET:
        pRemoteScpi->getRefOffset();
        break;
    case  RTSA_SELECT_UNITS:
        pRemoteScpi->getAmptUint();
        break;
    case  RTSA_BUTTON_PREAMP:
        pRemoteScpi->IsPreAmpOn();
        break;
    case  RTSA_BUTTON_SWEEP_TYPE:
        pRemoteScpi->IsSingleSweep();
        break;
    case  RTSA_BUTTON_ACQ_TIME:
        pRemoteScpi->IsAcqTimeAuto();
        break;
    case RTSA_INPUT_ACQ_TIME:
        pRemoteScpi->getAcqTime();
        break;
    case  RTSA_BUTTON_RBW_AUTO:
        pRemoteScpi->IsBWAuto();
        break;
    case  RTSA_BUTTON_RBW:
        pRemoteScpi->getBWIndex();
        break;
    case  RTSA_BUTTON_FFT_WINDOWS:
        pRemoteScpi->getFFTWindow();
        break;
    case  RTSA_SELECT_TRIGGER_SOURCE:
        pRemoteScpi->getTrigger();
        break;
    case  RTSA_INPUT_TRIGGER_LEVEL:
        pRemoteScpi->getTriggerLevel(nModleID);
        break;
    case  RTSA_BUTTON_TRIGGER_STOPE:
        pRemoteScpi->getTriggerSlope(nModleID);
        break;
    case  RTSA_BUTTON_TRIGGER_DELAY:
        pRemoteScpi->getTriggerDelayStatus(nModleID);
        break;
    case  RTSA_INPUT_TRIGGER_DELAY_VALUE:
        pRemoteScpi->getTriggerDelay(nModleID);
        break;
    case  RTSA_INPUT_TRIGGER_PERTIMER:
        pRemoteScpi->getTriggerPeriodTime();
        break;
    case  RTSA_INPUT_TRIGGER_HOLDTIME:
        pRemoteScpi->getriggerHoldOffTime(nModleID);
        break;
    case  RTSA_BUTTON_FMT_MASK_TYPE:
        pRemoteScpi->getFmtType();
        break;
    case  RTSA_SELECT_FMT_TRIGGER_CRITERION:
        pRemoteScpi->getFmtTriggerCriterion();
        break;
    case  RTSA_BUTTON_FMT_INSERT_ROW:
        break;
    case  RTSA_BUTTON_FMT_DELTE_ROW:
        break;
    case  RTSA_BUTTON_FMT_DELETE_TABLE:
        break;
    case  RTSA_FMT_DATA_NUM:
        pRemoteScpi->getFmtDataNum();
        break;
    case  RTSA_INPUT_FMT_FREQ:
        pRemoteScpi->getCurFmtFreqData(nIndexNo);
        break;
    case RTSA_INPUT_FMT_AMPT :
        pRemoteScpi->getCurFmtAmptData(nIndexNo);
        break;
    case  RTSA_BUTTON_TRACE_VIEW:
        pRemoteScpi->getTraceViewStatus(nModleID);
        break;
    case  RTSA_SELECT_TRACE_TYPE:
        pRemoteScpi->getCurTraceType(nModleID);
        break;
    case  RTSA_INPUT_TRACE_AVERAGE:
        pRemoteScpi->getCurTraceAvgNum(nModleID);
        break;
    case  RTSA_SELECT_TRACE_DETECTOR:
        pRemoteScpi->getDectorType();
        break;
    case  RTSA_BUTTON_MARKER_SELECT:
        pRemoteScpi->getCurMarkerID();
        break;
    case  RTSA_BUTTON_MARKER_VIEW:
        pRemoteScpi->isMarkerOn(nModleID);
        break;
    case  RTSA_BUTTON_MARKER_SEL:
        pRemoteScpi->getMarkerType(nModleID);
        break;
    case  RTSA_BUTTON_NOISE_MARKER:
        pRemoteScpi->IsMarkerNoiseOn(nModleID);
        break;
    case RTSA_BUTTON_PEAK_TRACK:
        pRemoteScpi->IsPeakTrackOn();
        break;
    case  RTSA_INPUT_MARKER_EDIT:
        pRemoteScpi->getMarkerRefFreq(nModleID);
        break;
    case  RTSA_BUTTON_LIMIT_SELECT:
        pRemoteScpi->getCurLimit();
        break;
    case  RTSA_BUTTON_LIMIT_LINE:
        pRemoteScpi->IsCurLimitOn(nModleID);
        break;
    case  RTSA_BUTTON_LIMIT_EDGE:
        pRemoteScpi->IsMarginOn(nModleID);
        break;
    case  RTSA_LIMIT_EDGE:
        pRemoteScpi->IsMarginOn(nModleID);
        break;
    case  RTSA_BUTTON_LIMIT_TEST:
        pRemoteScpi->IsLimitTestOn();
        break;
    case  RTSA_BUTTON_LIMIT_TYPE:
        pRemoteScpi->getLimitType(nModleID);
        break;
    case  RTSA_LIMIT_DATA_NUM:
        pRemoteScpi->getLimitDataNum(nModleID);
        break;
    case  RTSA_INPUT_LIMIT_FREQ:
        pRemoteScpi->getLimitCurPointFreq(nIndexNo,nModleID);
        break;
    case  RTSA_INPUT_LIMIT_AMPT:
        pRemoteScpi->getLimitCurPointAmpt(nIndexNo,nModleID);
        break;
    case  RTSA_BUTTON_DISPLAY_MODLE:
        pRemoteScpi->getDisplay();
        break;
    case  RTSA_BUTTON_PERSISTENCE:
        pRemoteScpi->IsPersistenceTimeInfinite();
        break;
    case  RTSA_INPUT_PERSISTENCE_TIME:
        pRemoteScpi->getPersistenceTime();
        break;
    case  RTSA_INPUT_HIGHEST_DENSITY:
        pRemoteScpi->getHighestDensity();
        break;
    case  RTSA_INPUT_LOWEST_DENSITY:
        pRemoteScpi->getLowestDensity();
        break;
    case  RTSA_INPUT_CURVE:
        pRemoteScpi->getCurve();
        break;
    default:
        break;
    }
    QEventLoop loop;
    connect(this, SIGNAL(ScpiCmdFinished()), &loop, SLOT(quit()));
    loop.exec();
    bool ok;
    switch (index)
    {
    case RTSA_INPUT_FREQ_CENTER:
        globalUserVariable->gMeterParam.gConfig_FreqSpan.gCenterFreq =recvSovket.toDouble(&ok);
        break;
    case RTSA_INPUT_FREQ_START:
        globalUserVariable->gMeterParam.gConfig_FreqSpan.gStartFreq =recvSovket.toDouble(&ok);
        break;
    case RTSA_INPUT_FREQ_STOP:
        globalUserVariable->gMeterParam.gConfig_FreqSpan.gStopFreq =recvSovket.toDouble(&ok) ;
        break;
    case RTSA_INPUT_FREQ_STEP:
        globalUserVariable->gMeterParam.gConfig_FreqSpan.gStepFreq =recvSovket.toDouble(&ok);
        break;
    case RTSA_INPUT_FREQ_OFFSET:
        globalUserVariable->gMeterParam.gConfig_FreqSpan.gOffsetFreq =recvSovket.toDouble(&ok);
        break;
    case RTSA_INPUT_FREQ_SPAN:
        globalUserVariable->gMeterParam.gConfig_FreqSpan.gSpanFreq =recvSovket.toDouble(&ok);
        break;
    case  RTSA_INPUT_FREQ_CHANNEL_STANDARD:
        globalUserVariable->gMeterParam.gConfig_FreqSpan.channelStd =recvSovket.toInt(&ok);
        break;
    case  RTSA_INPUT_FREQ_CHANNEL_STEP:
        globalUserVariable->gMeterParam.gConfig_FreqSpan.channelSelID =recvSovket.toInt(&ok);
        break;
    case  RTSA_INPUT_FREQ_CHANNEL_NUM:
        globalUserVariable->gMeterParam.gConfig_FreqSpan.channelNumber =recvSovket.toInt(&ok);
        break;
    case  RTSA_BUTTON_CHANNEL_TYPE:
        globalUserVariable->gMeterParam.gConfig_FreqSpan.channelType =recvSovket.toInt(&ok);
        break;
    case RTSA_INPUT_REF_LEVEL:
        globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel =recvSovket.toDouble(&ok);
        break;
    case  RTSA_BUTTON_ATTENUATION:
        globalUserVariable->gMeterParam.gConfig_Amplitude.attenAuto =recvSovket.toInt(&ok);
        break;
    case RTSA_INPUT_ATTEN:
        globalUserVariable->gMeterParam.gConfig_Amplitude.attenVal =recvSovket.toDouble(&ok);
        break;
    case RTSA_INPUT_SCALEDIV:
        globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex] =recvSovket.toDouble(&ok);
        break;
    case RTSA_INPUT_REF_OFFSET:
        globalUserVariable->gMeterParam.gConfig_Amplitude.refOffset[curwindowindex] =recvSovket.toDouble(&ok);
        break;
    case  RTSA_SELECT_UNITS:
        globalUserVariable->gMeterParam.gConfig_Amplitude.units[curwindowindex] =recvSovket.toInt(&ok);
        break;
    case  RTSA_BUTTON_PREAMP:
        globalUserVariable->gMeterParam.gConfig_Amplitude.preAmpStatus =recvSovket.toInt(&ok);
        break;
    case  RTSA_BUTTON_SWEEP_TYPE:
        globalUserVariable->gMeterParam.gConfig_Sweep.sweepType =recvSovket.toInt(&ok);
        break;
    case  RTSA_BUTTON_ACQ_TIME:
        globalUserVariable->gMeterParam.gConfig_Sweep.autoAcqtime =recvSovket.toInt(&ok);
        break;
    case RTSA_INPUT_ACQ_TIME:
        globalUserVariable->gMeterParam.gConfig_Sweep.acqTimeVal =recvSovket.toDouble(&ok);
        break;
    case  RTSA_BUTTON_RBW_AUTO:
        globalUserVariable->gMeterParam.gConfig_BW.autoRbw =recvSovket.toInt(&ok);
        break;
    case  RTSA_BUTTON_RBW:
        globalUserVariable->gMeterParam.gConfig_BW.rbwIndex =recvSovket.toInt(&ok);
        break;
    case  RTSA_BUTTON_FFT_WINDOWS:
        globalUserVariable->gMeterParam.gConfig_BW.fftFilter =recvSovket.toInt(&ok);
        break;
    case  RTSA_SELECT_TRIGGER_SOURCE:
        globalUserVariable->gMeterParam.gConfig_Trigger.triggerType =recvSovket.toInt(&ok);
        break;
    case  RTSA_INPUT_TRIGGER_LEVEL:
        switch(nModleID)
        {
        case RTSA_TRIGGER_VIDEO:
            globalUserVariable->gMeterParam.gConfig_Trigger.triggerVideoLevel =  recvSovket.toDouble(&ok);
            break;
        case RTSA_TRIGGER_EXTERNAL:
            globalUserVariable->gMeterParam.gConfig_Trigger.triggerExternLevel =  recvSovket.toDouble(&ok);
            break;
        case RTSA_TRIGGER_RF_BURST:
            globalUserVariable->gMeterParam.gConfig_Trigger.triggerRFLevel =  recvSovket.toDouble(&ok);
            break;
        default:
            break;
        }
        break;
    case  RTSA_BUTTON_TRIGGER_STOPE:
        switch(nModleID)
        {
        case RTSA_TRIGGER_VIDEO:
            globalUserVariable->gMeterParam.gConfig_Trigger.triggerVideoSlope= recvSovket.toInt(&ok);
            break;
        case RTSA_TRIGGER_EXTERNAL:
            globalUserVariable->gMeterParam.gConfig_Trigger.triggerExternSlope = recvSovket.toInt(&ok);
            break;
        case RTSA_TRIGGER_RF_BURST:
            globalUserVariable->gMeterParam.gConfig_Trigger.triggerRFSlope = recvSovket.toInt(&ok);
            break;
        default:
            break;
        }
        break;
    case  RTSA_BUTTON_TRIGGER_DELAY:
        switch(nModleID)
        {
        case RTSA_TRIGGER_VIDEO:
            globalUserVariable->gMeterParam.gConfig_Trigger.triggerVideoDelayStatus = recvSovket.toInt(&ok);
            break;
        case RTSA_TRIGGER_EXTERNAL:
            globalUserVariable->gMeterParam.gConfig_Trigger.triggerExternDelayStatus = recvSovket.toInt(&ok);
            break;
        case RTSA_TRIGGER_RF_BURST:
            globalUserVariable->gMeterParam.gConfig_Trigger.triggerRFDelayStatus = recvSovket.toInt(&ok);
            break;
        case RTSA_TRIGGER_PERIODIC_TIMER:
            globalUserVariable->gMeterParam.gConfig_Trigger.triggerPeriodDelayStatus = recvSovket.toInt(&ok);
            break;
        default:
            break;
        }
        break;
    case  RTSA_INPUT_TRIGGER_DELAY_VALUE:
        switch(nModleID)
        {
        case RTSA_TRIGGER_VIDEO:
            globalUserVariable->gMeterParam.gConfig_Trigger.triggerVideoDelay = recvSovket.toDouble(&ok);
            break;
        case RTSA_TRIGGER_EXTERNAL:
            globalUserVariable->gMeterParam.gConfig_Trigger.triggerExternDelay = recvSovket.toDouble(&ok);
            break;
        case RTSA_TRIGGER_RF_BURST:
            globalUserVariable->gMeterParam.gConfig_Trigger.triggerRFDelay = recvSovket.toDouble(&ok);
            break;
        case RTSA_TRIGGER_PERIODIC_TIMER:
            globalUserVariable->gMeterParam.gConfig_Trigger.triggerPeriodDelay = recvSovket.toDouble(&ok);
            break;
        default:
            break;
        }
        break;
    case  RTSA_INPUT_TRIGGER_PERTIMER:
        globalUserVariable->gMeterParam.gConfig_Trigger.triggerPeriodTime =recvSovket.toDouble(&ok);
        break;
    case  RTSA_INPUT_TRIGGER_HOLDTIME:
        switch(nModleID)
        {
        case RTSA_TRIGGER_VIDEO:
            globalUserVariable->gMeterParam.gConfig_Trigger.triggerVideoHoldOff = recvSovket.toDouble(&ok);
            break;
        case RTSA_TRIGGER_EXTERNAL:
            globalUserVariable->gMeterParam.gConfig_Trigger.triggerExternHoldOff = recvSovket.toDouble(&ok);
            break;
        case RTSA_TRIGGER_RF_BURST:
            globalUserVariable->gMeterParam.gConfig_Trigger.triggerRFBurstHoldOff = recvSovket.toDouble(&ok);
            break;
        case RTSA_TRIGGER_FMTMASK:
            globalUserVariable->gMeterParam.gConfig_Trigger.triggerFMTHoldOff = recvSovket.toDouble(&ok);
            break;
        default:
            break;
        }
        break;
    case  RTSA_BUTTON_FMT_MASK_TYPE:
        globalUserVariable->gfmtType =recvSovket.toInt(&ok);
        break;
    case  RTSA_SELECT_FMT_TRIGGER_CRITERION:
        globalUserVariable->gFmtTriggerCriterion=recvSovket.toInt(&ok);
        break;
    case  RTSA_BUTTON_FMT_INSERT_ROW:
        break;
    case  RTSA_BUTTON_FMT_DELTE_ROW:
        break;
    case  RTSA_BUTTON_FMT_DELETE_TABLE:
        break;
    case  RTSA_FMT_DATA_NUM:
        globalUserVariable->gMeterParam.gConfig_Trigger.fmtnumber = recvSovket.toInt(&ok);
        break;
    case  RTSA_INPUT_FMT_FREQ:
        globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq[index] = recvSovket.toDouble(&ok);
        break;
    case RTSA_INPUT_FMT_AMPT :
        globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[index] = recvSovket.toDouble(&ok);
        break;
    case  RTSA_BUTTON_TRACE_VIEW:
        globalUserVariable->gMeterParam.gConfig_Trace.Rtsa_Config_Trace[curwindowindex][nModleID].traceView =recvSovket.toInt(&ok);
        break;
    case  RTSA_SELECT_TRACE_TYPE:
        globalUserVariable->gMeterParam.gConfig_Trace.Rtsa_Config_Trace[curwindowindex][nModleID].traceType =recvSovket.toInt(&ok);
        break;
    case  RTSA_INPUT_TRACE_AVERAGE:
        globalUserVariable->gMeterParam.gConfig_Trace.Rtsa_Config_Trace[curwindowindex][nModleID].averageCount =recvSovket.toInt(&ok);
        break;
    case  RTSA_SELECT_TRACE_DETECTOR:
        globalUserVariable->gMeterParam.gConfig_Trace.detectorType=recvSovket.toInt(&ok);
        break;
    case  RTSA_BUTTON_MARKER_SELECT:
        globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].curmarkerID = recvSovket.toInt(&ok);
        break;
    case  RTSA_BUTTON_MARKER_VIEW:
        globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].gRtsa_Config_marker[nModleID].markerView =recvSovket.toInt(&ok);
        break;
    case  RTSA_BUTTON_MARKER_SEL:
        globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].gRtsa_Config_marker[nModleID].markerType =recvSovket.toInt(&ok);
        break;
    case  RTSA_BUTTON_NOISE_MARKER:
        globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].gRtsa_Config_marker[nModleID].markerNoiseOn =recvSovket.toInt(&ok);
        break;
    case RTSA_BUTTON_PEAK_TRACK :
        globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].markerPeakTraceOn =recvSovket.toInt(&ok);
        break;
    case  RTSA_INPUT_MARKER_EDIT:
        globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].gRtsa_Config_marker[nModleID].gMarkerRefFreq = recvSovket.toDouble(&ok);
        break;
    case  RTSA_BUTTON_LIMIT_SELECT:
        globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitID=recvSovket.toInt(&ok);
        break;
    case  RTSA_BUTTON_LIMIT_LINE:
        globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitOn[nModleID] =recvSovket.toInt(&ok);
        break;
    case  RTSA_BUTTON_LIMIT_EDGE:
        globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitEdgeOn[nModleID] =recvSovket.toInt(&ok);
        break;
    case  RTSA_LIMIT_EDGE:
        globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitEdgeVal[nModleID] =recvSovket.toDouble(&ok);
        break;
    case  RTSA_BUTTON_LIMIT_TEST:
        globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitTest =recvSovket.toInt(&ok);
        break;
    case  RTSA_BUTTON_LIMIT_TYPE:
        globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitType[nModleID] =recvSovket.toInt(&ok);
        break;
    case  RTSA_LIMIT_DATA_NUM:
        globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitEditNum[nModleID] = recvSovket.toDouble(&ok);
        break;
    case  RTSA_INPUT_LIMIT_FREQ:
        globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limtData[nModleID].limitAmpt[nIndexNo] = recvSovket.toDouble(&ok);
        break;
    case  RTSA_INPUT_LIMIT_AMPT:
        globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limtData[nModleID].limitAmpt[nIndexNo]= recvSovket.toDouble(&ok);
        break;
    case  RTSA_BUTTON_DISPLAY_MODLE:
        globalUserVariable->gMeterParam.gConfig_Display.displayMode =recvSovket.toInt(&ok);
        break;
    case  RTSA_BUTTON_PERSISTENCE:
        globalUserVariable->gAutoPersistenceTime =recvSovket.toInt(&ok);
        break;
    case  RTSA_INPUT_PERSISTENCE_TIME:
        globalUserVariable->gPersistenceTime =recvSovket.toInt(&ok);
        break;
    case  RTSA_INPUT_HIGHEST_DENSITY:
        globalUserVariable->gHighestDensity =recvSovket.toInt(&ok);
        break;
    case  RTSA_INPUT_LOWEST_DENSITY:
        globalUserVariable->gLowestDensity =recvSovket.toInt(&ok);
        break;
    case  RTSA_INPUT_CURVE:
        globalUserVariable->gCurve =recvSovket.toInt(&ok);
        break;

    default:
        break;
    }
}

/**
 * @brief set center freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setCenterFreq(qreal freq)
{
    bitviewbottomdisplay = BV_BOTTOM_CENTERANDSPAN;
    freq = freq - globalUserVariable->gMeterParam.gConfig_FreqSpan.gOffsetFreq;

    globalUserVariable->gMeterParam.gConfig_FreqSpan.gCenterFreq = freq ;
    pRemoteScpi->SetCenterFreq(globalUserVariable->gMeterParam.gConfig_FreqSpan.gCenterFreq);

    globalUserVariable->adjustFreqByCer();
    globalUserVariable->stepFreqCalculatorFunc();
    adjustSpanFreq(globalUserVariable->gMeterParam.gConfig_FreqSpan.gSpanFreq);

    resetAvgCnt();
    updateGeneralDataToBitview(RTSA_FREQ_INFO);
    updateGeneralDataToBitview(RTSA_RBW_INFO);
    showBitViewBottomMsg(bitviewbottomdisplay);
    emit RedrawInfoShow(LABEL_CENTER_FREQ);
    globalUserVariable->gMeterParam.gConfig_FreqSpan.channelStep = mRTSA_ChStand[globalUserVariable->gMeterParam.gConfig_FreqSpan.channelStd].ChStep;
    globalUserVariable->gMeterParam.gConfig_FreqSpan.channelNumber = globalUserVariable->CalculateChannelNum();
    //    globalUserVariable->adjustCHStandarByCerFreq(globalUserVariable->gCenterFreq);
    return;
}

/**
 * @brief get center freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal Rtsa_Remote_Interface::getCenterFreq()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_FREQ_CENTER);
    }

    return globalUserVariable->gMeterParam.gConfig_FreqSpan.gCenterFreq + globalUserVariable->gMeterParam.gConfig_FreqSpan.gOffsetFreq;

}

/**
 * @brief set start freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setStartFreq(qreal freq)
{
    bitviewbottomdisplay = BV_BOTTOM_STARTANDSTOP;
    freq = freq - globalUserVariable->gMeterParam.gConfig_FreqSpan.gOffsetFreq;

    globalUserVariable->gMeterParam.gConfig_FreqSpan.gStartFreq = freq;
    pRemoteScpi->setStartFreq(globalUserVariable->gMeterParam.gConfig_FreqSpan.gStartFreq);

    globalUserVariable->adjustFreqByStart();
    globalUserVariable->stepFreqCalculatorFunc();

    resetAvgCnt();
    updateGeneralDataToBitview(RTSA_ACQ_INFO);
    updateGeneralDataToBitview(RTSA_FREQ_INFO);
    updateGeneralDataToBitview(RTSA_RBW_INFO);
    showBitViewBottomMsg(bitviewbottomdisplay);
    return;
}

/**
 * @brief get start freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal Rtsa_Remote_Interface::getStartFreq()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_FREQ_START);
    }
    return globalUserVariable->gMeterParam.gConfig_FreqSpan.gStartFreq + globalUserVariable->gMeterParam.gConfig_FreqSpan.gOffsetFreq;

}

/**
 * @brief set stop freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setStopFreq(qreal freq)
{
    bitviewbottomdisplay = BV_BOTTOM_STARTANDSTOP;
    freq = freq - globalUserVariable->gMeterParam.gConfig_FreqSpan.gOffsetFreq;

    globalUserVariable->gMeterParam.gConfig_FreqSpan.gStopFreq = freq;
    pRemoteScpi->setStopFreq(globalUserVariable->gMeterParam.gConfig_FreqSpan.gStopFreq);

    globalUserVariable->adjustFreqByStop();
    globalUserVariable->stepFreqCalculatorFunc();

    adjustAcqtime(globalUserVariable->gMeterParam.gConfig_Sweep.acqTimeVal);

    resetAvgCnt();
    updateGeneralDataToBitview(RTSA_ACQ_INFO);
    updateGeneralDataToBitview(RTSA_FREQ_INFO);
    updateGeneralDataToBitview(RTSA_RBW_INFO);
    showBitViewBottomMsg(bitviewbottomdisplay);
    return;
}

/**
 * @brief get stop freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal Rtsa_Remote_Interface::getStopFreq()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_FREQ_STOP);
    }
    return globalUserVariable->gMeterParam.gConfig_FreqSpan.gStopFreq + globalUserVariable->gMeterParam.gConfig_FreqSpan.gOffsetFreq;
}

/**
 * @brief set step freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setCFStep(qreal freq)
{
    if(freq < RTSA_HZ)
    {
        freq = 1;
    }
    else if(freq > RTSA_SPEC_FREQ_MAX)
    {
        freq = RTSA_SPEC_FREQ_MAX;
    }
    globalUserVariable->gMeterParam.gConfig_FreqSpan.gStepFreq = freq;

    pRemoteScpi->setCFStep(globalUserVariable->gMeterParam.gConfig_FreqSpan.gStepFreq);
    return;
}

/**
 * @brief get step freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal Rtsa_Remote_Interface::getStepFreq()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_FREQ_STEP);
    }
    return globalUserVariable->gMeterParam.gConfig_FreqSpan.gStepFreq;
}

/**
 * @brief Rtsa_Remote_Interface::setFreqOffset
 * @param freq
 */
void Rtsa_Remote_Interface::setFreqOffset(qreal freq)
{
    if(freq > RTSA_SPEC_FREQ_MAX)
        freq = RTSA_SPEC_FREQ_MAX;
    else if(freq < -RTSA_SPEC_FREQ_MAX)
        freq = -RTSA_SPEC_FREQ_MAX;

    globalUserVariable->gMeterParam.gConfig_FreqSpan.gOffsetFreq = freq;
    pRemoteScpi->setFreqOffset(globalUserVariable->gMeterParam.gConfig_FreqSpan.gOffsetFreq);

    updateGeneralDataToBitview(RTSA_FREQ_OFFSET);
    return;
}

/**
 * @brief Rtsa_Remote_Interface::getFreqOffset
 * @return
 */
qreal Rtsa_Remote_Interface::getFreqOffset()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_FREQ_OFFSET);
    }

    return globalUserVariable->gMeterParam.gConfig_FreqSpan.gOffsetFreq;
}

/**
 * @brief set span freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setSpan(qreal freq)
{
    bitviewbottomdisplay = BV_BOTTOM_CENTERANDSPAN;
    if(freq < RTSA_SPAN_MIN)
        freq = RTSA_SPAN_MIN;

    globalUserVariable->gMeterParam.gConfig_FreqSpan.gSpanFreq = freq;
    pRemoteScpi->setSpan(globalUserVariable->gMeterParam.gConfig_FreqSpan.gSpanFreq);

    adjustSpanFreq(freq);
    adjustAcqtime(globalUserVariable->gMeterParam.gConfig_Sweep.acqTimeVal);
    globalUserVariable->stepFreqCalculatorFunc();

    if(getTrigger() == RTSA_TRIGGER_PERIODIC_TIMER)
    {
        AdjustPeriodTime(globalUserVariable->gMeterParam.gConfig_Trigger.triggerPeriodTime);
    }

    resetAvgCnt();
    updateGeneralDataToBitview(RTSA_ACQ_INFO);
    updateGeneralDataToBitview(RTSA_FREQ_INFO);
    updateGeneralDataToBitview(RTSA_RBW_INFO);
    showBitViewBottomMsg(bitviewbottomdisplay);
    emit RedrawInfoShow(LABEL_POI);
    emit RedrawInfoShow(LABEL_ACQTIME);
    return;
}

/**
 * @brief get span freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal Rtsa_Remote_Interface::getSpan()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_FREQ_SPAN);
    }
    return globalUserVariable->gMeterParam.gConfig_FreqSpan.gSpanFreq;
}

/**
 * @brief set full span
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setFullSpan()
{
    bitviewbottomdisplay = BV_BOTTOM_CENTERANDSPAN;


    globalUserVariable->gLastSpanFreq =  globalUserVariable->gMeterParam.gConfig_FreqSpan.gSpanFreq;
    globalUserVariable->gMeterParam.gConfig_FreqSpan.gSpanFreq = RTSA_SPAN_STEP_VALUE[RTSA_SPAN_INTERVAL_NUMBER-1];

    globalUserVariable->gSpanMode =RTSA_FULL_SPAN;
    pRemoteScpi->setFullSpan();

    globalUserVariable->adjustFreqBySpan(globalUserVariable->gMeterParam.gConfig_FreqSpan.gSpanFreq);

    globalUserVariable->gRbwGrade=RTSA_SPAN_INTERVAL_NUMBER-1;
    if(globalUserVariable->gMeterParam.gConfig_BW.autoRbw == RTSA_MANUAL)
    {
        globalUserVariable->adjustRbwBySpan(globalUserVariable->gMeterParam.gConfig_FreqSpan.gSpanFreq);
    }
    else
    {
        globalUserVariable->gMeterParam.gConfig_BW.rbw=RTSA_RbwManualList[globalUserVariable->gMeterParam.gConfig_BW.fftFilter][globalUserVariable->gRbwGrade][1];
        if(globalUserVariable->gMeterParam.gConfig_BW.fftFilter == RTSA_RECTANGULAR)
        {
            globalUserVariable->gMeterParam.gConfig_BW.rbw=RTSA_RbwManualList[globalUserVariable->gMeterParam.gConfig_BW.fftFilter][globalUserVariable->gRbwGrade][6];
        }
        else
        {
            globalUserVariable->gMeterParam.gConfig_BW.rbw=RTSA_RbwManualList[globalUserVariable->gMeterParam.gConfig_BW.fftFilter][globalUserVariable->gRbwGrade][5];
        }
    }
    //by Steve,0228
    adjustAcqtime(globalUserVariable->gMeterParam.gConfig_Sweep.acqTimeVal);

    globalUserVariable->stepFreqCalculatorFunc();

    if(getTrigger() == RTSA_TRIGGER_PERIODIC_TIMER)
    {
        AdjustPeriodTime(globalUserVariable->gMeterParam.gConfig_Trigger.triggerPeriodTime);
    }

    resetAvgCnt();
    updateGeneralDataToBitview(RTSA_ACQ_INFO);
    updateGeneralDataToBitview(RTSA_FREQ_INFO);
    updateGeneralDataToBitview(RTSA_RBW_INFO);
    showBitViewBottomMsg(bitviewbottomdisplay);
    emit RedrawInfoShow(LABEL_POI);
    return;
}

/**
* @brief set channel std index
* @param[in] standard index
* @Author Albert
* @date 2019-03-27
*/
void Rtsa_Remote_Interface::setCHStandard(qint32 index)
{
    qreal newCerFreq;
    if(index < 0)
        return;

    globalUserVariable->gMeterParam.gConfig_FreqSpan.channelStd = index;
    pRemoteScpi->setCHStandard(globalUserVariable->gMeterParam.gConfig_FreqSpan.channelStd);

    globalUserVariable->getBandInfo(index);
    //    globalUserVariable->adjustCHStandarByCerFreq(globalUserVariable->gMeterParam.gConfig_FreqSpan.gCenterFreq);
    newCerFreq = globalUserVariable->adjustFreqByCHStandar();

    //    globalUserVariable->adjustCHStandarByCerFreq(newCerFreq);
    setCenterFreq(newCerFreq);
    emit RedrawInfoShow(LABEL_CHANNEL);
    emit RedrawInfoShow(LABEL_SIGNAL_STANDARD);
    return;
}

/**
* @brief get channel std index
* @param none
* @Author Albert
* @date 2019-03-27
*/
qint32 Rtsa_Remote_Interface::getCHStandard()
{
    qint32 index;
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_FREQ_CHANNEL_STANDARD);
    }
    if(globalUserVariable->gMeterParam.gConfig_FreqSpan.channelStd < 0)
    {
        return -1;
    }
    index = mRTSA_ChStand[globalUserVariable->gMeterParam.gConfig_FreqSpan.channelStd].index;
    return index;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-09-24
*/
void Rtsa_Remote_Interface::setBandIndex(qint32 bandIndex)
{
    if(bandIndex < 0)
        bandIndex = 0;
    else if(bandIndex >= globalUserVariable->gCHName->size())
    {
        bandIndex = globalUserVariable->gCHName->size() - 1;
    }

    globalUserVariable->gMeterParam.gConfig_FreqSpan.channelSelID = bandIndex;
    pRemoteScpi->setCHStandard(globalUserVariable->gMeterParam.gConfig_FreqSpan.channelSelID);

    globalUserVariable->getBandInfo(globalUserVariable->gMeterParam.gConfig_FreqSpan.channelStd);
    //    globalUserVariable->adjustCHStandarByCerFreq(globalUserVariable->gMeterParam.gConfig_FreqSpan.gCenterFreq);
    qreal newCerFreq = globalUserVariable->adjustFreqByCHStandar();
    //    globalUserVariable->adjustCHStandarByCerFreq(newCerFreq);
    setCenterFreq(newCerFreq);
    emit RedrawInfoShow(LABEL_CHANNEL);
    emit RedrawInfoShow(LABEL_SIGNAL_STANDARD);
    return;
}

qint32 Rtsa_Remote_Interface::getBandIndex()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_FREQ_CHANNEL_STEP);
    }
    return globalUserVariable->gMeterParam.gConfig_FreqSpan.channelSelID;
}

/**
* @brief set channel std communicate direction
* @param[in] direction type
* @Author Albert
* @date 2019-03-27
*/
void Rtsa_Remote_Interface::setChannelType(qint32 direction)
{
    if(globalUserVariable->gMeterParam.gConfig_FreqSpan.channelType == direction)
        return;
    qreal newCerFreq = 0.;

    globalUserVariable->gMeterParam.gConfig_FreqSpan.channelType = direction;
    pRemoteScpi->setChannelType(globalUserVariable->gMeterParam.gConfig_FreqSpan.channelType);

    newCerFreq = globalUserVariable->adjustFreqByCHStandar();
    //    globalUserVariable->adjustCHStandarByCerFreq(newCerFreq);
    setCenterFreq(newCerFreq);
    return;
}

/**
* @brief get channel std communicate direction
* @param none
* @Author Albert
* @date 2019-03-20
*/
qint32 Rtsa_Remote_Interface::getChannelType()
{

    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_BUTTON_CHANNEL_TYPE);
    }
    return globalUserVariable->gMeterParam.gConfig_FreqSpan.channelType;
}

/**
* @brief set channel number
* @param[in] channel number
* @Author Albert
* @date 2019-03-27
*/
void Rtsa_Remote_Interface::setChannelNumber(qint32 number)
{
    if(number == globalUserVariable->gMeterParam.gConfig_FreqSpan.channelNumber)
        return;
    qreal min = 0;
    qreal max = 0;
    qreal centerFreq;
    if(globalUserVariable->gMeterParam.gConfig_FreqSpan.channelType == RTSA_UPLINK)
    {
        max = globalUserVariable->gCHStandard->at(globalUserVariable->gMeterParam.gConfig_FreqSpan.channelSelID).Up.Max;
        min = globalUserVariable->gCHStandard->at(globalUserVariable->gMeterParam.gConfig_FreqSpan.channelSelID).Up.Min;
    }
    else
    {
        max = globalUserVariable->gCHStandard->at(globalUserVariable->gMeterParam.gConfig_FreqSpan.channelSelID).Down.Max;
        min = globalUserVariable->gCHStandard->at(globalUserVariable->gMeterParam.gConfig_FreqSpan.channelSelID).Down.Min;
    }
    if(number < min)
        number = min;
    else if(number > max)
        number = max;

    globalUserVariable->gMeterParam.gConfig_FreqSpan.channelNumber = number;
    pRemoteScpi->setChannelNumber(globalUserVariable->gMeterParam.gConfig_FreqSpan.channelNumber);

    //Center Freq need modify
    centerFreq = globalUserVariable->adjustFreqByCHNum(number);
    setCenterFreq(centerFreq);
    return ;
}

/**
* @brief get channel number
* @param none
* @Author Albert
* @date 2019-03-25
*/
qint32 Rtsa_Remote_Interface::getChannelNumber()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_FREQ_CHANNEL_NUM);
    }
    return globalUserVariable->gMeterParam.gConfig_FreqSpan.channelNumber;
}

/**
 * @brief set auto scale
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setAutoScale()
{
    pRemoteScpi->setAutoScale();

    qreal* renderDataMax = gOriginalTrace;//GetTraceData(RTSA_NUM_SWEEP_POINT,gTraceSelect);
    qreal AMax = renderDataMax[0];
    for (qint32 k = 1; k < RTSA_NUM_SWEEP_POINT; k++)
    {
        if (AMax < renderDataMax[k]) {
            AMax = renderDataMax[k];
        }
    }
    qreal* renderDataMin = gOriginalTrace;//GetTraceData(RTSA_NUM_SWEEP_POINT,gTraceSelect);
    qreal AMin = renderDataMin[0];
    for (qint32 k = 1; k < RTSA_NUM_SWEEP_POINT; k++)
    {
        if (AMin > renderDataMin[k]) {
            AMin = renderDataMin[k];
        }
    }
    globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex] = (AMax - AMin)/8;
    if(globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex] < 0.2)
    {
        globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex] = 0.2;
        globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel = AMax + 2 * globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex];
    }
    else
    {
        globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel = AMax + globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex];
    }
    setRefLevel(globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel);
    resetAvgCnt();
    setScaleDiv(globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex]);
    return;
}

/**
 * @brief set ref level
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setRefLevel(qreal refLevel)
{
    bitviewtopdisplay = BV_TOP_APMTINFO;

    globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel = refLevel;
    pRemoteScpi->setRefLevel(globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel );

    ChangeOtherUnitTodBm(refLevel);
    if(globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel>0.)
    {
        if(globalUserVariable->gMeterParam.gConfig_Amplitude.preAmpStatus == RTSA_ON)
        {
            globalUserVariable->gMeterParam.gConfig_Amplitude.preAmpStatus = RTSA_OFF;
        }
    }
    amplitudeAttenControl();

    globalUserVariable->gdpxApmtMin = globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel /*+ globalUserVariable->gMeterParam.gConfig_Amplitude.refOffset[curwindowindex]*/ - globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex] * 10 + RTSA_COMP_TEMPDATA;
    globalUserVariable->gdpxAmptZoom = 200 / (globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex] * 10);

    resetAvgCnt();
    updateGeneralDataToBitview(RTSA_REF_LVL);
    for(int i=0;i<RTSA_BITVIEWNUM;i++)
    {
        mBitView[i]->showTopWordsMsg(BV_TOP_APMTINFO);
        mBitView[i]->refleshdisplay();
    }
}

/**
 * @brief get ref level
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal Rtsa_Remote_Interface::getRefLevel()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_REF_LEVEL);
    }

    return globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel;
}

/**
 * @brief set atten auto on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setAttenAuto(bool isAttenAuto)
{
    globalUserVariable->gMeterParam.gConfig_Amplitude.attenAuto = isAttenAuto;
    pRemoteScpi->setAttenAuto(globalUserVariable->gMeterParam.gConfig_Amplitude.attenAuto);
    amplitudeAttenControl();
    resetAvgCnt();
    emit RedrawInfoShow(LABEL_ATTEN_STATUS);
    return;
}

/**
 * @brief get atten auto on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool Rtsa_Remote_Interface::IsAttenAuto()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_BUTTON_ATTENUATION);
    }
    return globalUserVariable->gMeterParam.gConfig_Amplitude.attenAuto;

}

/**
 * @brief set atten val
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setAttenVal(qreal attenVal)
{
    if(attenVal < 0)
        attenVal = 0;
    else if(attenVal > 50)
        attenVal = 50;

    setAttenAuto(RTSA_MANUAL);

    int attenIndex = qCeil((attenVal) / 5);
    if(globalUserVariable->gMeterParam.gConfig_Amplitude.preAmpStatus == RTSA_OFF && globalUserVariable->gMeterParam.gConfig_Amplitude.attenAuto == RTSA_MANUAL)
    {
        if(attenIndex > 10)
        {
            attenIndex = 10;
        }
        globalUserVariable->gMeterParam.gConfig_Amplitude.attenVal = attenIndex * 5;
    }
    else
    {
        if(attenIndex > 6)
        {
            attenIndex = 6;
        }
        globalUserVariable->gMeterParam.gConfig_Amplitude.attenVal = attenIndex * 5;
    }

    pRemoteScpi->setAttenVal(globalUserVariable->gMeterParam.gConfig_Amplitude.attenVal);
    amplitudeAttenControl();
    resetAvgCnt();
    emit RedrawInfoShow(LABEL_ATTEN_VAL);
    return;
}

/**
 * @brief get atten val
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal Rtsa_Remote_Interface::getAttenVal()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_ATTEN);
    }
    return globalUserVariable->gMeterParam.gConfig_Amplitude.attenVal;
}

/**
 * @brief set scale val
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setScaleDiv(qreal scaleDiv)
{
    // Only 2 decimal places reserved
    scaleDiv = (qreal)(qint64)((scaleDiv + 0.005) * 100) / 100;
    if(0.2 > scaleDiv)
    {
        scaleDiv = 0.2;
    }
    else if(20. < scaleDiv)
    {
        scaleDiv = 20.;
    }

    globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex] = scaleDiv;
    pRemoteScpi->setScaleDiv(globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex]);

    if(globalUserVariable->gMeterParam.gConfig_Display.displayMode == RTSA_DENSITY)
    {
        globalUserVariable->gdpxApmtMin = globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel /*+ globalUserVariable->gMeterParam.gConfig_Amplitude.refOffset[curwindowindex]*/ - globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex] * 10 + RTSA_COMP_TEMPDATA;
        globalUserVariable->gdpxAmptZoom = 200 / (globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex] * 10);
        //        mBitView[curwindowindex]->setAmptdAttribute(BIT_AMPTD_DIV,scaleDiv);
        //        mBitView[curwindowindex]->showTopWordsMsg(BV_TOP_APMTINFO);
        //        mBitView[curwindowindex]->refleshdisplay();

    }

    for(int i=0;i<RTSA_BITVIEWNUM;i++)
    {

        mBitView[i]->setAmptdAttribute(BIT_AMPTD_DIV,scaleDiv);
        mBitView[i]->showTopWordsMsg(BV_TOP_APMTINFO);
        mBitView[i]->refleshdisplay();
    }
    //    pRemoteScpi->setDpxAmptMin();
    //    pRemoteScpi->setDpxAmptZoom();

    //    mBitView[curwindowindex]->setAmptdAttribute(BIT_AMPTD_DIV,scaleDiv);
    //    mBitView[curwindowindex]->showTopWordsMsg(BV_TOP_APMTINFO);
    //    mBitView[curwindowindex]->refleshdisplay();
    return;
}

/**
 * @brief get scale val
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal Rtsa_Remote_Interface::getScaleDiv()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_SCALEDIV);
    }
    globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex] = mBitView[curwindowindex]->getAmptdAttribute(BIT_AMPTD_DIV);
    return globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex];

}

/**
 * @brief set pre-amp on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setPreAmpOn(bool IsOn)
{
    if(globalUserVariable->gMeterParam.gConfig_Amplitude.preAmpStatus == IsOn)
        return;

    if(globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel > 0.0)
        return;

    globalUserVariable->gMeterParam.gConfig_Amplitude.preAmpStatus = IsOn;
    pRemoteScpi->setPreAmpOn(globalUserVariable->gMeterParam.gConfig_Amplitude.preAmpStatus);

    amplitudeAttenControl();
    resetAvgCnt();
    emit RedrawInfoShow(LABEL_PREAMP);
    return;
}

/**
 * @brief get pre-amp on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool Rtsa_Remote_Interface::IsPreAmpOn()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_BUTTON_PREAMP);
    }
    return globalUserVariable->gMeterParam.gConfig_Amplitude.preAmpStatus;
}

/**
 * @brief set ref offset
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setRefOffset(qreal refOffset)
{
    // Only 2 decimal places reserved
    if(refOffset < 0)
    {
        refOffset = (qreal)(qint64)((refOffset - 0.005) * 100) / 100;
    }
    else
    {
        refOffset = (qreal)(qint64)((refOffset + 0.005) * 100) / 100;
    }
    if(refOffset >= RTSA_SPEC_REF_OFFSET_MAX)
    {
        refOffset = RTSA_SPEC_REF_OFFSET_MAX;
    }
    else if(refOffset <= RTSA_SPEC_REF_OFFSET_MIN)
    {
        refOffset = RTSA_SPEC_REF_OFFSET_MIN;
    }
    globalUserVariable->gMeterParam.gConfig_Amplitude.refOffset[curwindowindex] = refOffset;
    pRemoteScpi->setRefOffset( globalUserVariable->gMeterParam.gConfig_Amplitude.refOffset[curwindowindex]);

    updateGeneralDataToBitview(RTSA_REF_OFFSET);
    return;
}

/**
 * @brief get ref offset
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal Rtsa_Remote_Interface::getRefOffset()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_REF_OFFSET);
    }
    else
        globalUserVariable->gMeterParam.gConfig_Amplitude.refOffset[curwindowindex] = mBitView[curwindowindex]->getAmptdAttribute(BIT_AMPTD_OFFSET);
    return globalUserVariable->gMeterParam.gConfig_Amplitude.refOffset[curwindowindex];
}

/**
 * @brief set units
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setAmptUnit(qint32 unitIndex)
{
    if(unitIndex < RTSA_DBM)
        unitIndex = RTSA_DBM;
    else if(unitIndex > RTSA_WATTS)
        unitIndex = RTSA_WATTS;

    globalUserVariable->gMeterParam.gConfig_Amplitude.units[curwindowindex] = unitIndex;
    pRemoteScpi->setAmptUnit(globalUserVariable->gMeterParam.gConfig_Amplitude.units[curwindowindex]);

    mBitView[curwindowindex]->setAmptdUnit(globalUserVariable->gMeterParam.gConfig_Amplitude.units[curwindowindex]);
    mBitView[curwindowindex]->showTopWordsMsg(BV_TOP_APMTINFO);
    mBitView[curwindowindex]->refleshdisplay();
    return;
}

/**
 * @brief get units
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 Rtsa_Remote_Interface::getAmptUint()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_SELECT_UNITS);
    }
    else
        globalUserVariable->gMeterParam.gConfig_Amplitude.units[curwindowindex] =  mBitView[curwindowindex]->getAmptUnit();
    return globalUserVariable->gMeterParam.gConfig_Amplitude.units[curwindowindex];
}

/**
 * @brief set single sweep on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setSingleSweep(bool isSingle)
{
    mSingleFinished = true;

    globalUserVariable->gMeterParam.gConfig_Sweep.sweepType = isSingle;
    pRemoteScpi->setSingleSweep(globalUserVariable->gMeterParam.gConfig_Sweep.sweepType);

    resetAvgCnt();
    qreal refval = getRefLevel();
    qreal scale = getScaleDiv();
    for(int i=0;i<RTSA_BITVIEWNUM;i++)
    {
        mBitView[i]->setSystemAttribute(RUNNINGSTATE,globalUserVariable->gMeterParam.gConfig_Sweep.sweepType);
    }
    for(qint32 i = 0 ; i < RTSA_NUM_SWEEP_POINT; i++)
    {
        mLowData[i] = refval  - 10 * scale;
    }
    setBitViewFileLoadFlag(false);
    return;
}

/**
 * @brief get single sweep on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool Rtsa_Remote_Interface::IsSingleSweep()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_BUTTON_SWEEP_TYPE);
    }
    return globalUserVariable->gMeterParam.gConfig_Sweep.sweepType;
}

/**
 * @brief set acq time auto on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setAcqTimeAuto(bool isAuto)
{
    if(isAuto == RTSA_AUTO)
    {
        setAcqTime(RTSA_ACQ_DEFAULT_TIME);
    }

    globalUserVariable->gMeterParam.gConfig_Sweep.autoAcqtime = isAuto;
    pRemoteScpi->setAcqTimeAuto(globalUserVariable->gMeterParam.gConfig_Sweep.autoAcqtime);
    updateGeneralDataToBitview(RTSA_ACQ_INFO);
    emit RedrawInfoShow(LABEL_ACQTIME);
    return;
}

/**
 * @brief get acq time auto on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool Rtsa_Remote_Interface::IsAcqTimeAuto()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_BUTTON_ACQ_TIME);
    }
    return globalUserVariable->gMeterParam.gConfig_Sweep.autoAcqtime;
}

/**
 * @brief set acq time
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setAcqTime(qreal acqtime)
{
    // time default us
    if(acqtime < RTSA_ACQ_MIN_TIME)
        acqtime = RTSA_ACQ_MIN_TIME;
    else if(acqtime > RTSA_ACQ_MAX_TIME)
        acqtime = RTSA_ACQ_MAX_TIME;

    if(globalUserVariable->gMeterParam.gConfig_Sweep.autoAcqtime == RTSA_AUTO)
        setAcqTimeAuto(RTSA_MANUAL);

    if(acqtime > RTSA_ACQTIME_MAX)
    {
        acqtime = RTSA_ACQTIME_MAX;
    }
    if(acqtime <= AcqTime_Min_List[globalUserVariable->gRbwGrade])
    {
        acqtime = AcqTime_Min_List[globalUserVariable->gRbwGrade];
    }
    else if(acqtime >= AcqTime_Max_List[globalUserVariable->gRbwGrade])
    {
        acqtime = AcqTime_Max_List[globalUserVariable->gRbwGrade];
    }
    globalUserVariable->gMeterParam.gConfig_Sweep.acqTimeVal = acqtime;

    pRemoteScpi->setAcqTime(globalUserVariable->gMeterParam.gConfig_Sweep.acqTimeVal);


    updateGeneralDataToBitview(RTSA_ACQ_INFO);
    emit RedrawInfoShow(LABEL_ACQTIME);
    return;
}

/**
 * @brief get acq time
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal Rtsa_Remote_Interface::getAcqTime()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_ACQ_TIME);
    }
    return globalUserVariable->gMeterParam.gConfig_Sweep.acqTimeVal;
}


/**
 * @brief set BW auto on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setBWAuto(bool isAuto)
{
    globalUserVariable->gMeterParam.gConfig_BW.autoRbw = isAuto;
    pRemoteScpi->setBWAuto(globalUserVariable->gMeterParam.gConfig_BW.autoRbw);

    if(globalUserVariable->gMeterParam.gConfig_BW.autoRbw == RTSA_ON)
    {
        //        globalUserVariable->gMeterParam.gConfig_BW.rbw = RTSA_RbwManualList[globalUserVariable->gMeterParam.gConfig_BW.fftFilter][globalUserVariable->gRbwGrade][1];
        //        globalUserVariable->gMeterParam.gConfig_BW.rbwIndex = RTSA_RBW5;
        if(globalUserVariable->gMeterParam.gConfig_BW.fftFilter == RTSA_RECTANGULAR)
        {
            globalUserVariable->gMeterParam.gConfig_BW.rbw = RTSA_RbwManualList[globalUserVariable->gMeterParam.gConfig_BW.fftFilter][globalUserVariable->gRbwGrade][6];
            globalUserVariable->gMeterParam.gConfig_BW.rbwIndex = RTSA_RBW6;
        }
        else
        {
            globalUserVariable->gMeterParam.gConfig_BW.rbw = RTSA_RbwManualList[globalUserVariable->gMeterParam.gConfig_BW.fftFilter][globalUserVariable->gRbwGrade][5];
            globalUserVariable->gMeterParam.gConfig_BW.rbwIndex = RTSA_RBW5;
        }
        //        bwSweepSettingDisplayFunc();
    }
    else if(globalUserVariable->gMeterParam.gConfig_BW.autoRbw == RTSA_OFF) // Tony 0907
    {
        if(globalUserVariable->gMeterParam.gConfig_BW.fftFilter == RTSA_RECTANGULAR)
        {
            globalUserVariable->gMeterParam.gConfig_BW.rbw = RTSA_RbwManualList[globalUserVariable->gMeterParam.gConfig_BW.fftFilter][globalUserVariable->gRbwGrade][0];
            globalUserVariable->gMeterParam.gConfig_BW.rbwIndex = RTSA_RBW6;
        }
        else
        {
            globalUserVariable->gMeterParam.gConfig_BW.rbw = RTSA_RbwManualList[globalUserVariable->gMeterParam.gConfig_BW.fftFilter][globalUserVariable->gRbwGrade][globalUserVariable->gMeterParam.gConfig_BW.rbwIndex];
        }
        //        bwSweepSettingDisplayFunc();
    }
    resetAvgCnt();
    //Tony 1102
    updateGeneralDataToBitview(RTSA_RBW_INFO);
    emit RedrawInfoShow(LABEL_RBW_STATUS);
    emit RedrawInfoShow(LABEL_RBW);
    return;
}

/**
 * @brief get BW auto on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool Rtsa_Remote_Interface::IsBWAuto()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_BUTTON_RBW_AUTO);
    }
    return globalUserVariable->gMeterParam.gConfig_BW.autoRbw;
}

qreal Rtsa_Remote_Interface::getBW()
{
    //???
    return globalUserVariable->gMeterParam.gConfig_BW.rbw;
}

/**
 * @brief set BW index
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setBWIndex(qint32 bwIndex)
{
    if(globalUserVariable->gMeterParam.gConfig_BW.fftFilter == RTSA_RECTANGULAR)
    {
        return;
    }
    if(globalUserVariable->gMeterParam.gConfig_BW.rbwIndex == bwIndex)
        return;
    if(bwIndex < RTSA_RBW0)
        bwIndex = RTSA_RBW0;
    else if(bwIndex > RTSA_RBW6)
        bwIndex = RTSA_RBW6;

    setBWAuto(RTSA_MANUAL);

    globalUserVariable->gMeterParam.gConfig_BW.rbwIndex = bwIndex;
    globalUserVariable->gMeterParam.gConfig_BW.rbw = RTSA_RbwManualList[globalUserVariable->gMeterParam.gConfig_BW.fftFilter][globalUserVariable->gRbwGrade][globalUserVariable->gMeterParam.gConfig_BW.rbwIndex];
    //    bwSweepSettingDisplayFunc();

    pRemoteScpi->setBWIndex(globalUserVariable->gMeterParam.gConfig_BW.rbwIndex);

    resetAvgCnt();
    //Tony 1102
    updateGeneralDataToBitview(RTSA_RBW_INFO);
    emit RedrawInfoShow(LABEL_RBW);
    emit RedrawInfoShow(LABEL_RBW_STATUS);
    emit RedrawInfoShow(LABEL_POI);
    return;
}

/**
 * @brief get BW index
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 Rtsa_Remote_Interface::getBWIndex()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_BUTTON_RBW);
    }
    return globalUserVariable->gMeterParam.gConfig_BW.rbwIndex;
}

/**
 * @brief set BW FFT window
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setFFTWindow(qint32 fftWindow)
{
    if(fftWindow < RTSA_RECTANGULAR)
        fftWindow = RTSA_RECTANGULAR;
    else if(fftWindow > RTSA_FLATTOP)
        fftWindow = RTSA_FLATTOP;

    globalUserVariable->gMeterParam.gConfig_BW.fftFilter = fftWindow;
    pRemoteScpi->setBWFFTWindow( globalUserVariable->gMeterParam.gConfig_BW.fftFilter);

    if(fftWindow == RTSA_RECTANGULAR)
    {
        globalUserVariable->gMeterParam.gConfig_BW.rbwIndex = RTSA_RBW6;
        globalUserVariable->gMeterParam.gConfig_BW.rbw = RTSA_RbwManualList[fftWindow][globalUserVariable->gRbwGrade][globalUserVariable->gMeterParam.gConfig_BW.rbwIndex];
        //        updateGeneralDataToBitview(RTSA_RBW_INFO);
    }
    else
    {
        if(globalUserVariable->gMeterParam.gConfig_BW.autoRbw == RTSA_AUTO)
        {
            globalUserVariable->gMeterParam.gConfig_BW.rbwIndex = RTSA_RBW5;
            globalUserVariable->gMeterParam.gConfig_BW.rbw = RTSA_RbwManualList[fftWindow][globalUserVariable->gRbwGrade][5];
        }
        else
            globalUserVariable->gMeterParam.gConfig_BW.rbw = RTSA_RbwManualList[fftWindow][globalUserVariable->gRbwGrade][globalUserVariable->gMeterParam.gConfig_BW.rbwIndex];

    }
    updateGeneralDataToBitview(RTSA_RBW_INFO);


    resetAvgCnt();
    emit RedrawInfoShow(LABEL_FFTWINDOW);
    emit RedrawInfoShow(LABEL_RBW);
    return;
}

/**
 * @brief get BW FFT window
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 Rtsa_Remote_Interface::getFFTWindow()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_BUTTON_FFT_WINDOWS);
    }
    return globalUserVariable->gMeterParam.gConfig_BW.fftFilter;
}

/**
 * @brief set trigger type
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setTrigger(qint32 TriggerMode)
{
    if(TriggerMode >= RTSA_TRIGGER_FMTMASK)
        TriggerMode = RTSA_TRIGGER_FMTMASK;
    else if(TriggerMode < RTSA_TRIGGER_EXTERNAL)
        TriggerMode = RTSA_TRIGGER_FREE_RUN;

    if(TriggerMode == RTSA_TRIGGER_FMTMASK)
    {
        setFmtDataNum(globalUserVariable->gMeterParam.gConfig_Trigger.fmtnumber);
        setFmtFreqData(globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq,globalUserVariable->gMeterParam.gConfig_Trigger.fmtnumber);
        setFmtAmptData(globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt,globalUserVariable->gMeterParam.gConfig_Trigger.fmtnumber);
    }

    globalUserVariable->gMeterParam.gConfig_Trigger.triggerType = TriggerMode;
    pRemoteScpi->setTrigger(globalUserVariable->gMeterParam.gConfig_Trigger.triggerType);

    QThread::msleep(200);

    if(TriggerMode == RTSA_TRIGGER_FMTMASK)
    {
        QThread::msleep(200);
    }
    for(qint32 i  = 0;i < RTSA_BITVIEWNUM; i++)
    {
        mBitView[i]->setTriggerrMode(TriggerMode);
        if(TriggerMode == RTSA_TRIGGER_FMTMASK)
        {
            mBitView[i]->setFmtShow(true);
        }
        else
        {
            mBitView[i]->setFmtShow(false);
        }
        mBitView[i]->refleshdisplay();
    }
    emit RedrawInfoShow(LABEL_TRIGGER);
    //    mBitView[curwindowindex]->refleshdisplay();
    return;
}

/**
 * @brief get trigger type
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 Rtsa_Remote_Interface::getTrigger()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_SELECT_TRIGGER_SOURCE);
    }
    return globalUserVariable->gMeterParam.gConfig_Trigger.triggerType;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-06-03
*/
void Rtsa_Remote_Interface::setTriggerLevel(qint32 TriggerMode, qreal level)
{
    qreal levelVal;
    if(level > (globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel + globalUserVariable->gMeterParam.gConfig_FreqSpan.gOffsetFreq))
    {
        level = globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel + globalUserVariable->gMeterParam.gConfig_FreqSpan.gOffsetFreq;
    }
    if(TriggerMode == RTSA_TRIGGER_VIDEO)
    {
        for(qint32 i  = 0;i < RTSA_BITVIEWNUM; i++)
        {
            mBitView[i]->setVideoTriggerLevel(level);
            mBitView[i]->refleshdisplay();
        }
    }

    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        if((quint32)TriggerMode != globalUserVariable->gMeterParam.gConfig_Trigger.triggerType)//如果触发方式格式不对
        {
            return;
        }
        levelVal = qPow(10,(level + RTSA_COMP_TEMPDATA)/20);
        globalUserVariable->gMeterParam.gConfig_Trigger.triggerVideoLevel = level;
        break;
    case RTSA_TRIGGER_EXTERNAL:
        globalUserVariable->gMeterParam.gConfig_Trigger.triggerExternLevel = level;
        break;
    case RTSA_TRIGGER_RF_BURST:
        if((quint32)TriggerMode != globalUserVariable->gMeterParam.gConfig_Trigger.triggerType)
        {
            return;
        }

        levelVal = qPow(10,(level + RTSA_COMP_TEMPDATA)/20);
        globalUserVariable->gMeterParam.gConfig_Trigger.triggerRFLevel = level;

        break;
    default:
        break;
    }
    pRemoteScpi->setTriggerLevel(TriggerMode,level);
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-06-03
*/
qreal Rtsa_Remote_Interface::getTriggerLevel(qint32 TriggerMode)
{
    qreal triggerLevel = 0;
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_TRIGGER_LEVEL,TriggerMode);
    }
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        triggerLevel = globalUserVariable->gMeterParam.gConfig_Trigger.triggerVideoLevel;
        break;
    case RTSA_TRIGGER_EXTERNAL:
        triggerLevel = globalUserVariable->gMeterParam.gConfig_Trigger.triggerExternLevel;
        break;
    case RTSA_TRIGGER_RF_BURST:
        triggerLevel = globalUserVariable->gMeterParam.gConfig_Trigger.triggerRFLevel;
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
* @date 2019-06-03
*/
void Rtsa_Remote_Interface::setTriggerSlope(qint32 TriggerMode, qint32 slope)
{
    if(TriggerMode < 0)
    {
        TriggerMode = globalUserVariable->gMeterParam.gConfig_Trigger.triggerType;
    }

    if((quint32)TriggerMode != globalUserVariable->gMeterParam.gConfig_Trigger.triggerType)
    {
        return;
    }

    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        globalUserVariable->gMeterParam.gConfig_Trigger.triggerVideoSlope = slope;
        break;
    case RTSA_TRIGGER_EXTERNAL:
        globalUserVariable->gMeterParam.gConfig_Trigger.triggerExternSlope = slope;
        break;
    case RTSA_TRIGGER_RF_BURST:
        globalUserVariable->gMeterParam.gConfig_Trigger.triggerRFSlope = slope;
        break;
    default:
        break;
    }
    globalUserVariable->gMeterParam.gConfig_Trigger.triggerSlope = slope;
    pRemoteScpi->setTriggerSlope(TriggerMode,globalUserVariable->gMeterParam.gConfig_Trigger.triggerSlope);

    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-06-03
*/
qint32 Rtsa_Remote_Interface::getTriggerSlope(qint32 TriggerMode)
{
    //    RtSa_Set_config_flag(IXT_RTSA_ConfigRsaCtrl,IXS_RTSA_TriggerMode);

    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_BUTTON_TRIGGER_STOPE,TriggerMode);
    }
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        globalUserVariable->gMeterParam.gConfig_Trigger.triggerSlope = globalUserVariable->gMeterParam.gConfig_Trigger.triggerVideoSlope;
        break;
    case RTSA_TRIGGER_EXTERNAL:
        globalUserVariable->gMeterParam.gConfig_Trigger.triggerSlope = globalUserVariable->gMeterParam.gConfig_Trigger.triggerExternSlope;
        break;
    case RTSA_TRIGGER_RF_BURST:
        globalUserVariable->gMeterParam.gConfig_Trigger.triggerSlope = globalUserVariable->gMeterParam.gConfig_Trigger.triggerRFSlope;
        break;
    default:
        break;
    }

    return globalUserVariable->gMeterParam.gConfig_Trigger.triggerSlope;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
void Rtsa_Remote_Interface::setTriggerDelayStatus(qint32 TriggerMode,  bool delayStatus)
{
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        globalUserVariable->gMeterParam.gConfig_Trigger.triggerVideoDelayStatus = delayStatus;
        break;
    case RTSA_TRIGGER_EXTERNAL:
        globalUserVariable->gMeterParam.gConfig_Trigger.triggerExternDelayStatus = delayStatus;
        break;
    case RTSA_TRIGGER_RF_BURST:
        globalUserVariable->gMeterParam.gConfig_Trigger.triggerRFDelayStatus = delayStatus;
        break;
    case RTSA_TRIGGER_PERIODIC_TIMER:
        globalUserVariable->gMeterParam.gConfig_Trigger.triggerRFDelayStatus = delayStatus;
        break;
    default:
        break;
    }
    pRemoteScpi->setTriggerDelayStatus(TriggerMode,delayStatus);
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
bool Rtsa_Remote_Interface::getTriggerDelayStatus(qint32 TriggerMode)
{
    bool delayStatus;
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_BUTTON_TRIGGER_DELAY,TriggerMode);
    }
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        delayStatus = globalUserVariable->gMeterParam.gConfig_Trigger.triggerVideoDelayStatus;
        break;
    case RTSA_TRIGGER_EXTERNAL:
        delayStatus = globalUserVariable->gMeterParam.gConfig_Trigger.triggerExternDelayStatus;
        break;
    case RTSA_TRIGGER_RF_BURST:
        delayStatus = globalUserVariable->gMeterParam.gConfig_Trigger.triggerRFDelayStatus;
        break;
    case RTSA_TRIGGER_PERIODIC_TIMER:
        delayStatus = globalUserVariable->gMeterParam.gConfig_Trigger.triggerPeriodDelayStatus;
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
void Rtsa_Remote_Interface::setTriggerDelay(qint32 TriggerMode, qreal Delay)
{
    if((quint32)TriggerMode != globalUserVariable->gMeterParam.gConfig_Trigger.triggerType)
    {
        return;
    }
    if(Delay > RTSA_ACQTIME_MAX)
    {
        Delay = RTSA_ACQTIME_MAX;
    }
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        globalUserVariable->gMeterParam.gConfig_Trigger.triggerVideoDelay = Delay;
        break;
    case RTSA_TRIGGER_EXTERNAL:
        globalUserVariable->gMeterParam.gConfig_Trigger.triggerExternDelay = Delay;
        break;
    case RTSA_TRIGGER_RF_BURST:
        globalUserVariable->gMeterParam.gConfig_Trigger.triggerRFDelay = Delay;
        break;
    case RTSA_TRIGGER_PERIODIC_TIMER:
        globalUserVariable->gMeterParam.gConfig_Trigger.triggerPeriodDelay = Delay;
        break;
    default:
        break;
    }
    Delay /= RTSA_S;
    Delay = Delay * RTSA_FFT_SAMPLE;

    pRemoteScpi->setTriggerDelay(TriggerMode,Delay);
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
qreal Rtsa_Remote_Interface::getTriggerDelay(qint32 TriggerMode)
{
    qreal delay = 0;
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_TRIGGER_DELAY_VALUE,TriggerMode);
    }
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        delay = globalUserVariable->gMeterParam.gConfig_Trigger.triggerVideoDelay;
        break;
    case RTSA_TRIGGER_EXTERNAL:
        delay = globalUserVariable->gMeterParam.gConfig_Trigger.triggerExternDelay;
        break;
    case RTSA_TRIGGER_RF_BURST:
        delay = globalUserVariable->gMeterParam.gConfig_Trigger.triggerRFDelay;
        break;
    case RTSA_TRIGGER_PERIODIC_TIMER:
        delay = globalUserVariable->gMeterParam.gConfig_Trigger.triggerPeriodDelay;
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
void Rtsa_Remote_Interface::setTriggerPeriodTime(qreal time)
{
    if(RTSA_TRIGGER_PERIODIC_TIMER != globalUserVariable->gMeterParam.gConfig_Trigger.triggerType)
    {
        return;
    }
    globalUserVariable->gMeterParam.gConfig_Trigger.triggerPeriodTime = time;
    pRemoteScpi->setTriggerPeriodTime(globalUserVariable->gMeterParam.gConfig_Trigger.triggerPeriodTime);
    AdjustPeriodTime(time);
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
qreal Rtsa_Remote_Interface::getTriggerPeriodTime()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_TRIGGER_PERTIMER);
    }
    return globalUserVariable->gMeterParam.gConfig_Trigger.triggerPeriodTime;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-06-17
*/
void Rtsa_Remote_Interface::settriggerHoldOffTime(qint32 TriggerMode, qreal holdOffTime)
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
        globalUserVariable->gMeterParam.gConfig_Trigger.triggerVideoHoldOff = holdOffTime;
        break;
    case RTSA_TRIGGER_EXTERNAL:
        globalUserVariable->gMeterParam.gConfig_Trigger.triggerExternHoldOff = holdOffTime;
        break;
    case RTSA_TRIGGER_RF_BURST:
        globalUserVariable->gMeterParam.gConfig_Trigger.triggerRFBurstHoldOff = holdOffTime;
        break;
    case RTSA_TRIGGER_FMTMASK:
        globalUserVariable->gMeterParam.gConfig_Trigger.triggerFMTHoldOff = holdOffTime;
        break;
    default:
        break;
    }
    holdOffTime /= RTSA_S;
    holdOffTime = holdOffTime * RTSA_FFT_SAMPLE;

    if((quint32)TriggerMode != globalUserVariable->gMeterParam.gConfig_Trigger.triggerType)
    {
        return;
    }
    pRemoteScpi->settriggerHoldOffTime(TriggerMode,holdOffTime);
    return;
}

qreal Rtsa_Remote_Interface::getriggerHoldOffTime(qint32 TriggerMode)
{
    qreal holdTime = 0;

    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_TRIGGER_HOLDTIME,TriggerMode);
    }
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        holdTime = globalUserVariable->gMeterParam.gConfig_Trigger.triggerVideoHoldOff;
        break;
    case RTSA_TRIGGER_EXTERNAL:
        holdTime = globalUserVariable->gMeterParam.gConfig_Trigger.triggerExternHoldOff;
        break;
    case RTSA_TRIGGER_RF_BURST:
        holdTime = globalUserVariable->gMeterParam.gConfig_Trigger.triggerRFBurstHoldOff;
        break;
    case RTSA_TRIGGER_FMTMASK:
        holdTime = globalUserVariable->gMeterParam.gConfig_Trigger.triggerFMTHoldOff;
        break;
    default:
        break;
    }

    return   holdTime;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-07-04
*/
void Rtsa_Remote_Interface::BuildFmtFromTrace()
{
    pRemoteScpi->BuildFmtFromTrace();
    qreal freq[101] = {0};
    qreal ampt[101] = {0};
    qint32 limitID = getCurTrace();
    qint32 freqstep  = (qint32)((globalUserVariable->gMeterParam.gConfig_FreqSpan.gStopFreq - globalUserVariable->gMeterParam.gConfig_FreqSpan.gStartFreq)/100);
    quint32 amptstep  = (quint32)((RTSA_NUM_SWEEP_POINT - 1)/100);
    qreal *trace = GetTraceData(RTSA_NUM_SWEEP_POINT,limitID);
    for(qint32 i = 0 ; i < 100; i++)
    {
        freq[i] = (getStartFreq() + freqstep * i)/RTSA_MHZ;
        ampt[i] = getMaxTraceData(trace,amptstep * i,amptstep) + 10.0;
    }
    freq[100] = getStopFreq()/RTSA_MHZ;
    ampt[100] = trace[RTSA_NUM_SWEEP_POINT - 1];

    memcpy(globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq,freq,sizeof(qreal) * 101);
    memcpy(globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt,ampt,sizeof(qreal)* 101);
    globalUserVariable->gMeterParam.gConfig_Trigger.fmtnumber = 101;
    setFmtFreqData(freq,101);
    setFmtAmptData(ampt,101);
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-07-04
*/
void Rtsa_Remote_Interface::DeleteAllFmtMask()
{
    pRemoteScpi->DeleteAllFmtMask();
    globalUserVariable->gMeterParam.gConfig_Trigger.fmtnumber = 0;
    memset(globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq,0,sizeof(globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq));
    memset(globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt,0,sizeof(globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq));
    setFmtFreqData(0,0);
    setFmtAmptData(0,0);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-07-03
*/
void Rtsa_Remote_Interface::setFmtType(qint32 Upper)
{
    if(Upper < BIT_FMT_UPPER)
        Upper = BIT_FMT_UPPER;
    else if(Upper > BIT_FMT_LOWER)
        Upper = BIT_FMT_LOWER;
    globalUserVariable->gfmtType = Upper;
    pRemoteScpi->setFmtType(globalUserVariable->gfmtType);
    for(qint32 i = 0; i < RTSA_BITVIEWNUM; i++)
    {
        if(mBitView[i]->getBitviewType() != RTSA_SPECTROGRAM)
        {
            mBitView[i]->setFmtType(globalUserVariable->gfmtType);
            mBitView[i]->refleshdisplay();
        }
    }
    return;
}

qint32 Rtsa_Remote_Interface::getFmtType()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_BUTTON_FMT_MASK_TYPE);
    }
    return globalUserVariable->gfmtType;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-09-09
*/
void Rtsa_Remote_Interface::setFmtTriggerCriterion(qint32 criterion)
{
    if(globalUserVariable->gFmtTriggerCriterion == criterion)
        return;
    if(criterion < RTSA_FMT_MASK_NORMAL)
        criterion = RTSA_FMT_MASK_NORMAL;
    else if(criterion > RTSA_ENTER_UPP)
        criterion = RTSA_ENTER_UPP;
    globalUserVariable->gFmtTriggerCriterion = criterion;
    pRemoteScpi->setFmtTriggerCriterion(globalUserVariable->gFmtTriggerCriterion);
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-09-09
*/
qint32 Rtsa_Remote_Interface::getFmtTriggerCriterion()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_SELECT_FMT_TRIGGER_CRITERION);
    }
    return globalUserVariable->gFmtTriggerCriterion;

}

/**
* @brief  setFmtDataNum
* @param dataNum
* @Author Albert
* @date 2019-05-24
*/
void Rtsa_Remote_Interface::setFmtDataNum(qint32 dataNum)
{
    globalUserVariable->gMeterParam.gConfig_Trigger.fmtnumber = dataNum;
    pRemoteScpi->setFmtDataNum(globalUserVariable->gMeterParam.gConfig_Trigger.fmtnumber);
    return;
}

qint32 Rtsa_Remote_Interface::getFmtDataNum()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_FMT_DATA_NUM);
    }
    return globalUserVariable->gMeterParam.gConfig_Trigger.fmtnumber;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-05-24
*/
void Rtsa_Remote_Interface::setCurFmtFreqData(qreal data, qint32 index)
{
    if(data <= globalUserVariable->gMeterParam.gConfig_FreqSpan.gStartFreq/RTSA_MHZ)
    {
        data  = globalUserVariable->gMeterParam.gConfig_FreqSpan.gStartFreq / RTSA_MHZ;
    }
    else if(data >= globalUserVariable->gMeterParam.gConfig_FreqSpan.gStopFreq/RTSA_MHZ)
    {
        data = globalUserVariable->gMeterParam.gConfig_FreqSpan.gStopFreq / RTSA_MHZ;
    }
    if(isFreqInFmtArray(data))
    {
        return;
    }
    globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq[index] = data;
    pRemoteScpi->setCurFmtFreqData(globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq[index],index);

    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-24
*/
qreal Rtsa_Remote_Interface::getCurFmtFreqData(qint32 index)
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_FMT_FREQ,0,index);
    }
    return globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq[index];
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-24
*/
void Rtsa_Remote_Interface::setCurFmtAmptData(qreal data, qint32 index)
{
    qreal baseY = globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel + globalUserVariable->gMeterParam.gConfig_Amplitude.refOffset[curwindowindex];
    qreal BottomY = baseY - globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex] * 10;
    if(data < BottomY)
    {
        data = BottomY;
    }
    globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[index] = data;
    pRemoteScpi->setCurFmtAmptData(globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[index],index);
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-05-24
*/
qreal Rtsa_Remote_Interface::getCurFmtAmptData(qint32 index)
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_FMT_AMPT,0,index);
    }
    return globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[index];
}

void Rtsa_Remote_Interface::InsertFmtDataRow()
{
    if(isFreqInFmtArray(getStartFreq()/RTSA_MHZ))
    {
        return;
    }

    globalUserVariable->gMeterParam.gConfig_Trigger.fmtnumber ++;
    pRemoteScpi->InsertFmtDataRow();

    for(qint32 i = 0; i < globalUserVariable->gMeterParam.gConfig_Trigger.fmtnumber - 1; i++)
    {
        globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq[i + 1] = globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq[i];
        globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[i + 1] = globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[i];
    }
    globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq[0] = getStartFreq()/RTSA_MHZ;
    globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[0] = -10.0;
    setFmtFreqData(globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq,globalUserVariable->gMeterParam.gConfig_Trigger.fmtnumber);
    setFmtAmptData(globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt,globalUserVariable->gMeterParam.gConfig_Trigger.fmtnumber);

    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-10-08
*/
void Rtsa_Remote_Interface::setTraceViewStatus(bool status, qint32 traceID)
{
    if(traceID < 0)
    {
        traceID = getCurTrace();
    }
    globalUserVariable->gMeterParam.gConfig_Trace.Rtsa_Config_Trace[curwindowindex][traceID].traceView = status;
    pRemoteScpi->setTraceViewStatus(traceID,globalUserVariable->gMeterParam.gConfig_Trace.Rtsa_Config_Trace[curwindowindex][traceID].traceView);

    setTraceType(traceID, status);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-10-08
*/
bool Rtsa_Remote_Interface::getTraceViewStatus(qint32 traceID)
{
    if(traceID < 0)
    {
        traceID = getCurTrace();
    }
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_BUTTON_TRACE_VIEW,traceID);
        return globalUserVariable->gMeterParam.gConfig_Trace.Rtsa_Config_Trace[curwindowindex][traceID].traceView;
    }
    else
    {  if(getTraceType(traceID) != RTSA_TRACE_OFF)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

}
/**
* @brief
* @param
* @Author Albert
* @date 2019-10-08
*/
void Rtsa_Remote_Interface::setCurTraceType(qint32 traceType)
{
    qint32 traceID = getCurTrace();
    globalUserVariable->gMeterParam.gConfig_Trace.Rtsa_Config_Trace[curwindowindex][traceID].traceType = traceType;
    pRemoteScpi->setCurTraceType(globalUserVariable->gMeterParam.gConfig_Trace.Rtsa_Config_Trace[curwindowindex][traceID].traceType,traceID);
    setTraceType(traceID,traceType);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-10-08
*/
qint32 Rtsa_Remote_Interface::getCurTraceType()
{
    qint32 traceID = getCurTrace();
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_SELECT_TRACE_TYPE,traceID);
    }
    else
        globalUserVariable->gMeterParam.gConfig_Trace.Rtsa_Config_Trace[curwindowindex][traceID].traceType = getTraceType(traceID);
    return globalUserVariable->gMeterParam.gConfig_Trace.Rtsa_Config_Trace[curwindowindex][traceID].traceType;

}
/**
* @brief
* @param
* @Author Albert
* @date 2019-10-08
*/
void Rtsa_Remote_Interface::setCurTraceAvgNum(qint32 Num)
{
    qint32 traceID = getCurTrace();
    globalUserVariable->gMeterParam.gConfig_Trace.Rtsa_Config_Trace[curwindowindex][traceID].averageCount = Num;
    pRemoteScpi->setCurTraceAvgNum(globalUserVariable->gMeterParam.gConfig_Trace.Rtsa_Config_Trace[curwindowindex][traceID].averageCount,traceID);
    setAvgNum(traceID,Num);
    return;
}

qint32 Rtsa_Remote_Interface::getCurTraceAvgNum()
{
    qint32 traceID = getCurTrace();
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_TRACE_AVERAGE,traceID);
    }
    else
    {
        globalUserVariable->gMeterParam.gConfig_Trace.Rtsa_Config_Trace[curwindowindex][traceID].averageCount = getAvgNum(traceID);
    }
    return globalUserVariable->gMeterParam.gConfig_Trace.Rtsa_Config_Trace[curwindowindex][traceID].averageCount;
}

/**
 * @brief set current dector type
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setDectorType(qint32 DectorType)
{
    if(DectorType < RTSA_DEC_PEAK)
        DectorType = RTSA_DEC_PEAK;
    else if(DectorType > RTSA_DEC_RMS)
        DectorType = RTSA_DEC_RMS;

    globalUserVariable->gMeterParam.gConfig_Trace.detectorType = DectorType;
    pRemoteScpi->setDectorType(globalUserVariable->gMeterParam.gConfig_Trace.detectorType);

    resetAvgCnt();
    emit RedrawInfoShow(LABEL_DETECTOR);
    return;
}

/**
 * @brief get current dector type
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 Rtsa_Remote_Interface::getDectorType()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_SELECT_TRACE_DETECTOR);
    }
    return globalUserVariable->gMeterParam.gConfig_Trace.detectorType;
}

void Rtsa_Remote_Interface::GetCurTraceData()
{
    if(1 == pSocketLinkStatus)
    {
        pRemoteScpi->GetCurTraceData();
        QEventLoop loop;
        connect(this, SIGNAL(ScpiDataFinished()), &loop, SLOT(quit()));
        loop.exec();
    }
}

void Rtsa_Remote_Interface::getDpxData()
{

}

/**
 * @brief set current marker id
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setCurMarkerID(qint32 MarkerID)
{
    if(mBitView[curwindowindex]->getBitviewType() == RTSA_SPECTROGRAM)
        return;

    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;

    globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].curmarkerID = MarkerID;
    pRemoteScpi->setCurMarkerID(globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].curmarkerID);

    mBitView[curwindowindex]->setMarkerAttribute(BIT_MARKER_INDEX,MarkerID);
    mBitView[curwindowindex]->markerUpdateByFreq();
    mBitView[curwindowindex]->refleshmarker();

    emit MarkerSelectOnOff(MarkerID,true);
    return;
}

/**
 * @brief get current marker id
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 Rtsa_Remote_Interface::getCurMarkerID()
{
    if(1==pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_BUTTON_MARKER_SELECT);
        mBitView[curwindowindex]->setMarkerAttribute(BIT_MARKER_INDEX,globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].curmarkerID);
        mBitView[curwindowindex]->markerUpdateByFreq();
        mBitView[curwindowindex]->refleshmarker();

        emit MarkerSelectOnOff(globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].curmarkerID,true);
    }
    else
        globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].curmarkerID = mBitView[curwindowindex]->getMarkerAttribute(BIT_MARKER_INDEX);

    return globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].curmarkerID;
}

///**
//* @brief
//* @param
//* @Author Albert
//* @date 2019-10-08
//*/
//void Rtsa_Remote_Interface::setCurMarkerOn(bool isOn)
//{
//    qint32 markerID = getCurMarkerID();
//    setMarkerOn(markerID,isOn);
//    return;
//}

///**
//* @brief
//* @param
//* @Author Albert
//* @date 2019-10-08
//*/
//bool Rtsa_Remote_Interface::isCurMarkerOn()
//{
//    bool MarkerOn = false;
//    qint32 markerID = getCurMarkerID();
//    MarkerOn = isMarkerOn(markerID);
//    return MarkerOn;
//}

/**
 * @brief set current marker on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setMarkerOn(qint32 MarkerID, bool isOn)
{
    if(mBitView[curwindowindex]->getBitviewType() == RTSA_SPECTROGRAM)
        return;
    if(isMarkerOn(MarkerID) == isOn)
        return;
    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;

    globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].gRtsa_Config_marker[MarkerID].markerView = isOn;
    pRemoteScpi->setMarkerOn(MarkerID,globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].gRtsa_Config_marker[MarkerID].markerView);
    if(isMarkerOn(MarkerID) != isOn) //因为做了一个调整，gSetMarkerDisply 与gGetMarkerDisply比较
    {
        mBitView[curwindowindex]->setMarkerAttribute(BIT_MARKER_VISIABLE,isOn,MarkerID);
        mBitView[curwindowindex]->markerUpdateByFreq();
        mBitView[curwindowindex]->refleshdisplay();
    }

    setMarkerRefFreq(MarkerID,getCenterFreq());
    setMarkerDeltaFreq(MarkerID,getCenterFreq());

    emit MarkerSelectOnOff(MarkerID,isOn);
    emit BitViewMakerDraw(MarkerID,isOn);
    if(mIsZoomIn)
    {
        setZoomIn();
    }
    else
    {
        setZoomOut();
    }
    return;
}

/**
 * @brief get current marker on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool Rtsa_Remote_Interface::isMarkerOn(qint32 MarkerID)
{
    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;

    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_BUTTON_MARKER_VIEW,MarkerID);
    }
    else
        globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].gRtsa_Config_marker[MarkerID].markerView =  mBitView[curwindowindex]->getMarkerAttribute(BIT_MARKER_VISIABLE,MarkerID);
    return globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].gRtsa_Config_marker[MarkerID].markerView;

}

/**
* @brief
* @param
* @Author Albert
* @date 2019-10-08
*/
void Rtsa_Remote_Interface::setCurMarkerType(qint32 MarkerType)
{
    qint32 curMarkerID = getCurMarkerID();
    setMarkerType(curMarkerID,MarkerType);
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-10-08
*/
qint32 Rtsa_Remote_Interface::getCurMarkerType()
{
    qint32 type = 0;
    qint32 curMarkerID = getCurMarkerID();
    type = getMarkerType(curMarkerID);
    return type;
}

/**
 * @brief set current marker type
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setMarkerType(qint32 MarkerID, qint32 MarkerType)
{
    if(mBitView[curwindowindex]->getBitviewType() == RTSA_SPECTROGRAM)
        return;
    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;

    if(MarkerType < RTSA_REF)
        MarkerType = RTSA_REF;
    else if(MarkerType > RTSA_DELTA)
        MarkerType = RTSA_DELTA;

    globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].gRtsa_Config_marker[MarkerID].markerType = MarkerType;
    pRemoteScpi->setMarkerType(MarkerID,globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].gRtsa_Config_marker[MarkerID].markerType);
    if(getMarkerType(MarkerID) !=  MarkerType)
    {
        mBitView[curwindowindex]->setMarkerAttribute(BIT_MARKER_TYPE,MarkerType,MarkerID);
        mBitView[curwindowindex]->markerUpdateByFreq();
        mBitView[curwindowindex]->refleshdisplay();
        mBitView[curwindowindex]->refleshmarker();
    }

    //    mBitView[curwindowindex]->setMarkerAttribute(BIT_MARKER_VISIABLE,ON);
    return;
}

/**
 * @brief get current marker type
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 Rtsa_Remote_Interface::getMarkerType(qint32 MarkerID)
{
    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;

    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_BUTTON_MARKER_SEL,MarkerID);
    }
    else
        globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].gRtsa_Config_marker[MarkerID].markerType = mBitView[curwindowindex]->getMarkerAttribute(BIT_MARKER_TYPE,MarkerID);;
    return globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].gRtsa_Config_marker[MarkerID].markerType;
}

/**
 * @brief set current marker to center freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setMarkerToCenter()
{
    if(mBitView[curwindowindex]->getBitviewType() == RTSA_SPECTROGRAM)
        return;

    qint32 markerID = getCurMarkerID();
    qreal centerFreq = 0;
    if(isMarkerOn(markerID))
    {
        centerFreq = getMarkerCurFreq(BIT_MARKER_CURRENT_FREQ);
        pRemoteScpi->setMarkerToCenter();
        setCenterFreq(centerFreq);
    }

    showBitViewBottomMsg(BV_BOTTOM_CENTERANDSPAN);
    return;
}

/**
 * @brief set current marker to start freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setMarkerToStart()
{
    if(mBitView[curwindowindex]->getBitviewType() == RTSA_SPECTROGRAM)
        return;

    qint32 markerID = getCurMarkerID();
    qreal startFreq = 0;
    if(isMarkerOn(markerID))
    {
        startFreq = getMarkerCurFreq(BIT_MARKER_CURRENT_FREQ);
        pRemoteScpi->setMarkerToStart();
        setStartFreq(startFreq);
    }
    showBitViewBottomMsg(BV_BOTTOM_CENTERANDSPAN);
    return;
}

/**
 * @brief set current marker to stop freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setMarkerToStop()
{
    if(mBitView[curwindowindex]->getBitviewType() == RTSA_SPECTROGRAM)
        return;

    qint32 markerID = getCurMarkerID();
    qreal stopFreq = 0;
    if(isMarkerOn(markerID))
    {
        stopFreq = getMarkerCurFreq(BIT_MARKER_CURRENT_FREQ);
        pRemoteScpi->setMarkerToStop();
        setStopFreq(stopFreq);
    }
    showBitViewBottomMsg(BV_BOTTOM_CENTERANDSPAN);
    return;
}

/**
 * @brief Rtsa_Remote_Interface::setMarkerToPeak
 */
void Rtsa_Remote_Interface::setMarkerToPeak()
{
    pRemoteScpi->setMarkerToPeak();
    mBitView[curwindowindex]->refleshmarker();
    mBitView[curwindowindex]->refleshdisplay();
    emit BitViewMakerMoved(true);
    return;
}

void Rtsa_Remote_Interface::setMarkerToMin()
{
    pRemoteScpi->setMarkerToMin();
    mBitView[curwindowindex]->MarkerToMin();
    mBitView[curwindowindex]->refleshmarker();
    mBitView[curwindowindex]->refleshdisplay();
    return;
}

/**
 * @brief Rtsa_Remote_Interface::setMarkerToNextPeak
 */
void Rtsa_Remote_Interface::setMarkerToNextPeak()
{
    pRemoteScpi->setMarkerToNextPeak();
    mBitView[curwindowindex]->MarkerToNextPeak();
    mBitView[curwindowindex]->refleshmarker();
    mBitView[curwindowindex]->refleshdisplay();
    return;
}

/**
 * @brief Rtsa_Remote_Interface::setMarkerToLeftPeak
 */
void Rtsa_Remote_Interface::setMarkerToLeftPeak()
{
    pRemoteScpi->setMarkerToLeftPeak();
    mBitView[curwindowindex]->MarkerToLeftPeak();
    mBitView[curwindowindex]->refleshmarker();
    mBitView[curwindowindex]->refleshdisplay();
    return;
}

/**
 * @brief Rtsa_Remote_Interface::setMarkerToRightPeak
 */
void Rtsa_Remote_Interface::setMarkerToRightPeak()
{
    pRemoteScpi->setMarkerToRightPeak();
    mBitView[curwindowindex]->MarkerToRightPeak();
    mBitView[curwindowindex]->refleshmarker();
    mBitView[curwindowindex]->refleshdisplay();
    return;
}

/**
 * @brief Rtsa_Remote_Interface::setPeakTrackOn
 * @param PeakTrackOn
 */
void Rtsa_Remote_Interface::setPeakTrackOn(bool PeakTrackOn)
{
    globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].markerPeakTraceOn = PeakTrackOn;
    pRemoteScpi->setPeakTrackOn(globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].markerPeakTraceOn);
    return;
}

/**
* @brief IsPeakTrackOn
* @param none
* @Author Albert
* @date 2019-03-27
*/
bool Rtsa_Remote_Interface::IsPeakTrackOn()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_BUTTON_PEAK_TRACK);
    }
    else
        return globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].markerPeakTraceOn;
}

/**
 * @brief set current marker ref freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setMarkerRefFreq(qint32 MarkerID, qreal refFreq)
{
    if(mBitView[curwindowindex]->getBitviewType() == RTSA_SPECTROGRAM)
        return;
    if(MarkerID < 0)
    {
        MarkerID = getCurMarkerID();
    }

    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;
    globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].gRtsa_Config_marker[MarkerID].gMarkerRefFreq = refFreq;
    pRemoteScpi->setMarkerRefFreq(MarkerID,globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].gRtsa_Config_marker[MarkerID].gMarkerRefFreq);
    mBitView[curwindowindex]->setMarkerFreqAttribute(BIT_MARKER_NORMAL,globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].gRtsa_Config_marker[MarkerID].gMarkerRefFreq,MarkerID);
    mBitView[curwindowindex]->markerUpdateByFreq();
    mBitView[curwindowindex]->refleshmarker();
    mBitView[curwindowindex]->refleshdisplay();
    return;
}
/**
 * @brief get current marker ref freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal Rtsa_Remote_Interface::getMarkerRefFreq(qint32 MarkerID)
{
    if(MarkerID < 0)
    {
        MarkerID = getCurMarkerID();
    }
    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;

    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_MARKER_EDIT,MarkerID);
    }
    else
        globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].gRtsa_Config_marker[MarkerID].gMarkerRefFreq  = mBitView[curwindowindex]->getMarkerFreqAttribute(BIT_MARKER_NORMAL,MarkerID) +  globalUserVariable->gMeterParam.gConfig_FreqSpan.gOffsetFreq ;

    return globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].gRtsa_Config_marker[MarkerID].gMarkerRefFreq ;

}

/**
 * @brief set current marker delta freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setMarkerDeltaFreq(qint32 MarkerID, qreal DeltaFreq)
{
    if(mBitView[curwindowindex]->getBitviewType() == RTSA_SPECTROGRAM)
        return;
    if(MarkerID < 0)
    {
        MarkerID = getCurMarkerID();
    }
    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;
    //    gMarkerDeltaFreq[MarkerID] = DeltaFreq;
    mBitView[curwindowindex]->setMarkerFreqAttribute(BIT_MARKER_DELTA,DeltaFreq,MarkerID);
    mBitView[curwindowindex]->markerUpdateByFreq();
    mBitView[curwindowindex]->refleshdisplay();
    mBitView[curwindowindex]->refleshmarker();
    return;
}
/**
 * @brief get current marker delta freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal Rtsa_Remote_Interface::getMarkerDeltaFreq(qint32 MarkerID)
{
    if(MarkerID < 0)
    {
        MarkerID = getCurMarkerID();
    }
    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;
    return mBitView[curwindowindex]->getMarkerFreqAttribute(BIT_MARKER_DELTA,MarkerID) + globalUserVariable->gMeterParam.gConfig_FreqSpan.gOffsetFreq;
}
/**
 * @brief set current marker noise on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setMarkerNoiseOn(qint32 MarkerID, bool isOn)
{
    if(mBitView[curwindowindex]->getBitviewType() == RTSA_SPECTROGRAM)
        return;
    if(MarkerID < 0)
    {
        MarkerID = getCurMarkerID();
    }
    setDectorType(RTSA_DEC_SAMPLE);

    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;
    globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].gRtsa_Config_marker[MarkerID].markerNoiseOn = isOn;
    pRemoteScpi->setMarkerNoiseOn(MarkerID,globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].gRtsa_Config_marker[MarkerID].markerNoiseOn);
    mBitView[curwindowindex]->setMarkerAttribute(BIT_MARKER_NOISE,isOn,MarkerID);
    mBitView[curwindowindex]->markerUpdateByFreq();
    mBitView[curwindowindex]->refleshmarker();
    mBitView[curwindowindex]->refleshdisplay();
    return;
}

/**
 * @brief get current marker noise on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool Rtsa_Remote_Interface::IsMarkerNoiseOn(qint32 MarkerID)
{
    if(MarkerID < 0)
    {
        MarkerID = getCurMarkerID();
    }
    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;

    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_BUTTON_NOISE_MARKER,MarkerID);
    }
    else
        globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].gRtsa_Config_marker[MarkerID].markerNoiseOn = mBitView[curwindowindex]->getMarkerAttribute(BIT_MARKER_NOISE,MarkerID);

    return globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].gRtsa_Config_marker[MarkerID].markerNoiseOn;
}

/**
 * @brief set current limit id
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setCurLimit(qint32 curLimitID)
{
    //    if(gMeterParam.gConfig_Limit[curwindowindex].limitID == curLimitID)
    //        return;
    if(curLimitID < RTSA_LIMIT1)
        curLimitID = RTSA_LIMIT1;
    else if(curLimitID >RTSA_LIMIT6)
        curLimitID =RTSA_LIMIT6;

    globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitID = curLimitID;
    pRemoteScpi->setCurLimit(globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitID);
    mBitView[curwindowindex]->setLimitAttribute(BIT_LIMIT_INDEX,curLimitID);
    return;
}

/**
 * @brief get current limit id
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 Rtsa_Remote_Interface::getCurLimit()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_BUTTON_LIMIT_SELECT);
    }
    else
        globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitID =  mBitView[curwindowindex]->getLimitAttribute(BIT_LIMIT_INDEX);
    return globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitID;

}

/**
 * @brief set current limit on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setCurLimitOn(qint32 LimitID, bool isOn)
{
    if(LimitID < 0)
    {
        LimitID = getCurLimit();
    }
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;
    globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitOn[LimitID] = isOn;

    pRemoteScpi->setCurLimitOn(LimitID,globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitOn[LimitID]);

    mBitView[curwindowindex]->setLimitAttribute(BIT_LIMIT_VIEW,globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitOn[LimitID],LimitID);
    mBitView[curwindowindex]->refleshdisplay();
    emit RedrawInfoShow(LABEL_LIMIT);
    return;
}

/**
 * @brief get current limit on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool Rtsa_Remote_Interface::IsCurLimitOn(qint32 LimitID)
{
    if(LimitID < 0)
    {
        LimitID = getCurLimit();
    }
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;

    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_BUTTON_LIMIT_LINE,LimitID);
    }
    else
        globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitOn[LimitID] = mBitView[curwindowindex]->getLimitAttribute(BIT_LIMIT_VIEW,LimitID);
    return globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitOn[LimitID];

}

/**
 * @brief set current limit margin on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setMarginOn(qint32 LimitID, bool isOn)
{
    if(LimitID < 0)
    {
        LimitID = getCurLimit();
    }
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;

    globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitEdgeOn[LimitID] = isOn;

    pRemoteScpi->setMarginOn(LimitID,globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitEdgeOn[LimitID]);
    mBitView[curwindowindex]->setLimitAttribute(BIT_LIMIT_MARGIN,isOn,LimitID);
    mBitView[curwindowindex]->refleshdisplay();
    return;
}

/**
 * @brief get current limit margin on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool Rtsa_Remote_Interface::IsMarginOn(qint32 LimitID)
{
    if(LimitID < 0)
    {
        LimitID = getCurLimit();
    }
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_BUTTON_LIMIT_EDGE,LimitID);
    }
    else
        globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitEdgeOn[LimitID] = mBitView[curwindowindex]->getLimitAttribute(BIT_LIMIT_MARGIN,LimitID);
    return globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitEdgeOn[LimitID];

}

/**
 * @brief set current limit margin
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setMargin(qint32 LimitID, qreal margin)
{
    if(LimitID < 0)
    {
        LimitID = getCurLimit();
    }
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;
    if(margin > RTSA_LIMIT_EDGE_MAX)
        margin = RTSA_LIMIT_EDGE_MAX;
    else if(margin < 0)
        margin = 0;
    globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitEdgeVal[LimitID] = margin;

    pRemoteScpi->setMargin(LimitID,globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitEdgeVal[LimitID]);

    //    mBitView[curwindowindex]->setLimitAttribute(BIT_LIMIT_MARGIN,ON,LimitID);
    mBitView[curwindowindex]->setLimitAttribute(BIT_LIMIT_MARGIN,true,LimitID);
    mBitView[curwindowindex]->setLimitAttributeEX(BIT_LIMIT_MARGIN_VALUE,margin,LimitID);
    mBitView[curwindowindex]->refleshdisplay();
    return;
}

/**
 * @brief get current limit margin
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal Rtsa_Remote_Interface::getMargin(qint32 LimitID)
{
    if(LimitID < 0)
    {
        LimitID = getCurLimit();
    }
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;

    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_LIMIT_EDGE,LimitID);
    }
    else
        globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitEdgeVal[LimitID] =  mBitView[curwindowindex]->getLimitAttributeEX(BIT_LIMIT_MARGIN_VALUE,LimitID);;
    return globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitEdgeVal[LimitID];

}

/**
 * @brief set current limit test on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setLimitTestOn(bool isOn)
{
    globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitTest = isOn;
    pRemoteScpi->setLimitTestOn( globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitTest);
    mBitView[curwindowindex]->setLimitAttribute(BIT_LIMIT_TEST,isOn);
    mBitView[curwindowindex]->refleshdisplay();
    return;
    return;
}

/**
 * @brief get current limit test on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool Rtsa_Remote_Interface::IsLimitTestOn()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_BUTTON_LIMIT_TEST);
    }
    else
        globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitTest = mBitView[curwindowindex]->getLimitAttribute(BIT_LIMIT_TEST);;
    return globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitTest;
}

/**
 * @brief set current limit type
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setLimitType(qint32 LimitID, qint32 nType)
{
    if(LimitID < 0)
    {
        LimitID = getCurLimit();
    }
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;

    if(nType < RTSA_LIMIT_OFF)
        nType = RTSA_LIMIT_OFF;
    else if(nType > RTSA_LOWER)
        nType = RTSA_LOWER;

    globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitType[LimitID] = nType;

    pRemoteScpi->setLimitType(LimitID,globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitType[LimitID]);
    mBitView[curwindowindex]->setLimitAttribute(BIT_LIMIT_TYPE,nType,LimitID);
    mBitView[curwindowindex]->refleshdisplay();
    return;
    return;
}

/**
 * @brief get current limit type
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 Rtsa_Remote_Interface::getLimitType(qint32 LimitID)
{
    if(LimitID < 0)
    {
        LimitID = getCurLimit();
    }
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;

    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_BUTTON_LIMIT_TYPE,LimitID);
    }
    else
        globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitType[LimitID] = mBitView[curwindowindex]->getLimitAttribute(BIT_LIMIT_TYPE,LimitID);
    return globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitType[LimitID];
}

/**
* @brief delete all limit
* @param none
* @Author Albert
* @date 2019-03-25
*/
void Rtsa_Remote_Interface::DeleteAllLimit()
{
    for(qint32 i = 0; i < RTSA_BITVIEWNUM;i++)
    {
        mBitView[i]->setTableEdit(BIT_LIMIT_DELETE_LIMIT,0);
        pRemoteScpi->DeleteLimitLine(i);

        for(qint32 j = 0 ; j < RTSA_LIMIT_TOTAL_CNT; j++)
        {
            setLimitNum(i,j,0);
        }
        mBitView[i]->setTableEdit(BIT_LIMIT_EDIT_VISIABLE,BIT_LIMIT_TABLE_EDIT_SHOW);
        mBitView[i]->refleshdisplay();
    }
    return;
}

/**
* @brief BuildLimitFromTrace
* @param none
* @Author Albert
* @date 2019-04-15
*/
void Rtsa_Remote_Interface::BuildLimitFromTrace()
{
    qreal freq[101] = {0};
    qreal ampt[101] = {0};
    qint32 traceID = getCurTrace();
    qint32 limitID = getCurLimit();
    qint32 freqstep  = (qint32)((globalUserVariable->gMeterParam.gConfig_FreqSpan.gStopFreq - globalUserVariable->gMeterParam.gConfig_FreqSpan.gStartFreq)/100);
    quint32 amptstep  = (quint32)((RTSA_NUM_SWEEP_POINT - 1)/100);
    qreal *trace = GetTraceData(RTSA_NUM_SWEEP_POINT,traceID);

    freq[0] = getStartFreq()/RTSA_MHZ;
    ampt[0] = trace[0] + 10.0;

    for(qint32 i = 0 ; i < 100; i++)
    {
        freq[i] = (getStartFreq() + freqstep * i)/RTSA_MHZ;
        ampt[i] = getMaxTraceData(trace,amptstep * i,amptstep) + 10.0;
    }
    freq[100] = getStopFreq()/RTSA_MHZ;
    ampt[100] = trace[RTSA_NUM_SWEEP_POINT - 1] + 10.0;

    pRemoteScpi->BuildLimitFromTrace();

    setCurLimit(limitID);
    setCurLimitOn(limitID,true);
    setLimitFreqData(freq,101,limitID);
    setLimitAmptData(ampt,101,limitID);
    return;
}

/**
 * @brief get current limit data num
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 Rtsa_Remote_Interface::getLimitDataNum(qint32 LimitID)
{
    if(LimitID < 0)
    {
        LimitID = getCurLimit();
    }
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;

    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_LIMIT_DATA_NUM,LimitID);
    }
    else
        globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitEditNum[LimitID] =  mBitView[curwindowindex]->getLimitAttribute(BIT_LIMIT_POINT_NUM,LimitID);;
    return globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limitEditNum[LimitID];
}
/**
 * @brief delete limit row
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::DeleteLimitRow(qint32 LimitID)
{
    if(LimitID < 0)
    {
        LimitID = getCurLimit();
    }
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;

    pRemoteScpi->DeleteLimitLine(LimitID);
    mBitView[curwindowindex]->setTableEdit(BIT_LIMIT_EDIT_VISIABLE,BIT_LIMIT_TABLE_EDIT_SHOW);
    mBitView[curwindowindex]->setTableEdit(BIT_LIMIT_DELETE_ROW,BIT_LIMIT_EDIT_VISIABLE,LimitID);
    mBitView[curwindowindex]->refleshdisplay();
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-05-13
*/
void Rtsa_Remote_Interface::setLimitCurPointFreq(qreal pData, qint32 curPos, qint32 limitID)
{
    qreal freqMin = getStartFreq()/RTSA_MHZ;
    qreal freqMax = getStopFreq()/RTSA_MHZ;
    if(pData < freqMin)
        pData = freqMin;
    else if(pData > freqMax)
        pData = freqMax;

    globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limtData[limitID].limitFreq[curPos]  = pData;
    pRemoteScpi->setLimitCurPointFreq(globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limtData[limitID].limitFreq[curPos],curPos,limitID);


    mBitView[curwindowindex]->setLimitCurPointData(pData,curPos,BIT_LIMIT_FREQ,limitID);
    return;
}

/**
* @brief getLimitCurPointFreq
* @param [curPos] cur limit select index, [limitID] cur limit index
* @Author Albert
* @date 2019-05-13
*/
qreal Rtsa_Remote_Interface::getLimitCurPointFreq(qint32 curPos, qint32 limitID)
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_LIMIT_FREQ,curPos,limitID);
    }
    else
        globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limtData[limitID].limitFreq[curPos] = mBitView[curwindowindex]->getLimitCurPointData(curPos,BIT_LIMIT_FREQ,limitID);;
    return globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limtData[limitID].limitFreq[curPos];
}


/**
* @brief
* @param
* @Author Albert
* @date 2019-05-13
*/
void Rtsa_Remote_Interface::setLimitCurPointAmpt(qreal pData, qint32 curPos, qint32 limitID)
{
    if(pData < -170.0)
        pData = -170.0;
    else if(pData > 30)
        pData = 20.0;

    globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limtData[limitID].limitAmpt[curPos]  = pData;
    pRemoteScpi->setLimitCurPointAmpt( globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limtData[limitID].limitAmpt[curPos],curPos,limitID);

    mBitView[curwindowindex]->setLimitCurPointData(pData,curPos,BIT_LIMIT_AMPT,limitID);
    return;
}

/**
* @brief getLimitCurPointAmpt
* @param [curPos] cur limit select index, [limitID] cur limit index
* @Author Albert
* @date 2019-05-13
*/
qreal Rtsa_Remote_Interface::getLimitCurPointAmpt(qint32 curPos, qint32 limitID)
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_LIMIT_AMPT,curPos,limitID);
    }
    else
        globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limtData[limitID].limitAmpt[curPos] =  mBitView[curwindowindex]->getLimitCurPointData(curPos,BIT_LIMIT_AMPT,limitID);
    return globalUserVariable->gMeterParam.gConfig_Limit[curwindowindex].limtData[limitID].limitAmpt[curPos] ;
}

/**
 * @brief insert limit row
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::InsertLimitRow()
{
    pRemoteScpi->InsertLimitRow(curwindowindex);

    mBitView[curwindowindex]->setTableEdit(BIT_LIMIT_EDIT_VISIABLE,BIT_LIMIT_TABLE_EDIT_SHOW);
    mBitView[curwindowindex]->setTableEdit(BIT_LIMIT_INSERT_ROW,1);
    mBitView[curwindowindex]->refleshdisplay();
    return;
}

//Display
/**
 * @brief set measure type
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setDisplay(qint32 disPlayMode)
{
    if(globalUserVariable->gMeterParam.gConfig_Display.displayMode == disPlayMode)
        return;
    //    qint32 nWidth = mWidth;
    //    qint32 nHeight = mHeight;
    //    mWidth = mOrginWidth;
    //    mHeight = mOrginHeight;

    if(disPlayMode < RTSA_SPECTRUM)
        disPlayMode = RTSA_SPECTRUM;
    else if(disPlayMode > RTSA_DENSITY_SPECTROGRAM)
        disPlayMode = RTSA_DENSITY_SPECTROGRAM;
    globalUserVariable->gMeterParam.gConfig_Display.displayMode = disPlayMode;
    pRemoteScpi->setDisplay(globalUserVariable->gMeterParam.gConfig_Display.displayMode);

    for(int i=0;i<RTSA_BITVIEWNUM;i++)
    {
        //        mBitView[i]->close();
        mBitView[i]->hide();
    }

    setBitViewParam(disPlayMode);
    mIsCurBitViewSizeChange = false;
    if(mIsZoomIn)
    {
        setZoomIn();
    }
    else
    {
        setZoomOut();
    }
    emit RedrawInfoShow(LABEL_MODE);
    return;
}

/**
 * @brief get measure type
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 Rtsa_Remote_Interface::getDisplay()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_BUTTON_DISPLAY_MODLE);

    }

    return globalUserVariable->gMeterParam.gConfig_Display.displayMode;
}

/**
 * @brief set Persistence Time Infinite on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setPersistenceTimeInfinite(bool isInfinite)
{
    if(globalUserVariable->gMeterParam.gConfig_Display.displayMode != RTSA_DENSITY && globalUserVariable->gMeterParam.gConfig_Display.displayMode != RTSA_DENSITY_SPECTROGRAM)
        return;

    globalUserVariable->gAutoPersistenceTime = isInfinite;
    pRemoteScpi->setPersistenceInfinite(globalUserVariable->gAutoPersistenceTime);

    if(isInfinite != RTSA_INFINITE)
    {
        setPersistenceTime(globalUserVariable->gPersistenceTime);
    }
    emit RedrawInfoShow(LABEL_PERSISTENCE);
    return;
}

/**
 * @brief get Persistence Time Infinite on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool Rtsa_Remote_Interface::IsPersistenceTimeInfinite()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_BUTTON_PERSISTENCE);
    }
    return globalUserVariable->gAutoPersistenceTime;
}
/**
 * @brief set Persistence Time
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setPersistenceTime(qreal time)
{
    // only DENSITY and DENSITY_SPECTROGRAM can set this param
    //    if(globalUserVariable->gMeterParam.gConfig_Display.displayMode != RTSA_DENSITY && globalUserVariable->gMeterParam.gConfig_Display.displayMode != RTSA_DENSITY_SPECTROGRAM)
    //        return;
    if(time < 50000.0)
        time = 50000.0;
    else if(time >= 6.35 * RTSA_S)
        time = 6.35 * RTSA_S;
    if(globalUserVariable->gAutoPersistenceTime == RTSA_INFINITE)
    {
        globalUserVariable->gAutoPersistenceTime = RTSA_FINITE;
    }
    globalUserVariable->gPersistenceTime = (qreal)((qint32)(time / 50000.0) * 50000.0);
    pRemoteScpi->setPersistenceTime(globalUserVariable->gPersistenceTime);
    emit RedrawInfoShow(LABEL_PERSISTENCE);
    return;
}
/**
 * @brief get Persistence Time
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal Rtsa_Remote_Interface::getPersistenceTime()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_PERSISTENCE_TIME);
    }
    return globalUserVariable->gPersistenceTime;
}

/**
 * @brief set highest density
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setHighestDensity(qint32 high)
{
    //    if(globalUserVariable->gMeterParam.gConfig_Display.displayMode != RTSA_DENSITY && globalUserVariable->gMeterParam.gConfig_Display.displayMode != RTSA_DENSITY_SPECTROGRAM)
    //        return ;
    if(high > RTSA_DENTISY_HIGHEST)
        high = RTSA_DENTISY_HIGHEST;
    else if(high < RTSA_DENTISY_LOWEST)
        high = RTSA_DENTISY_LOWEST;
    if((quint32)high < (globalUserVariable->gLowestDensity + 2))
    {
        if(globalUserVariable->gLowestDensity > 98)
        {
            globalUserVariable->gHighestDensity = 100;
            globalUserVariable->gLowestDensity = 98;
        }
        else
        {
            globalUserVariable->gHighestDensity = globalUserVariable->gLowestDensity + 2;
        }
    }
    else
    {
        globalUserVariable->gHighestDensity = high;
    }
    pRemoteScpi->setHighestDensity(globalUserVariable->gHighestDensity);
    return;
}

/**
 * @brief get highest density
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 Rtsa_Remote_Interface::getHighestDensity()
{

    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_HIGHEST_DENSITY);
    }
    return globalUserVariable->gHighestDensity;
}
/**
 * @brief set lowest density
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setLowestDensity(qint32 low)
{
    //    if(globalUserVariable->gMeterParam.gConfig_Display.displayMode != RTSA_DENSITY && globalUserVariable->gMeterParam.gConfig_Display.displayMode != RTSA_DENSITY_SPECTROGRAM)
    //        return ;
    if(low > RTSA_DENTISY_HIGHEST)
        low = RTSA_DENTISY_HIGHEST;
    else if(low < RTSA_DENTISY_LOWEST)
        low = RTSA_DENTISY_LOWEST;
    if((quint32)low > (globalUserVariable->gHighestDensity - 2))
    {
        if(globalUserVariable->gHighestDensity < 2)
        {
            globalUserVariable->gLowestDensity = 2;
            globalUserVariable->gHighestDensity = 4;

        }
        else
        {
            globalUserVariable->gLowestDensity = globalUserVariable->gHighestDensity - 2;
        }
    }else
    {
        globalUserVariable->gLowestDensity = low;
    }
    pRemoteScpi->setLowestDensity(globalUserVariable->gLowestDensity);
    return;
}
/**
 * @brief get lowest density
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 Rtsa_Remote_Interface::getLowestDensity()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_LOWEST_DENSITY);
    }
    return globalUserVariable->gLowestDensity;

}
/**
 * @brief set curve
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setCurve(float curve)
{
    if(curve < -100.0)
    {
        curve = -100.0;
    }else if(curve > 100.0)
    {
        curve = 100.0;
    }
    globalUserVariable->gCurve = curve;
    pRemoteScpi->setDpxCurve(globalUserVariable->gCurve);
    return;
}
/**
 * @brief get curve
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 Rtsa_Remote_Interface::getCurve()
{
    if(1 == pSocketLinkStatus && 1 == bGetDataFromScpi)
    {
        SendAndRecvScpi(RTSA_INPUT_CURVE);
    }
    return globalUserVariable->gCurve;
}
/**
 * @brief set Density Level adjust
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setDensityLevelAjust()
{
    qreal highestdensity= 50;
    qreal lowestdensity = 30;
    globalUserVariable->gHighestDensity = highestdensity;
    globalUserVariable->gLowestDensity  = lowestdensity;
    pRemoteScpi->setDensityLevelAjust();
    return;
}

/**
 * @brief get freq adjust string
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
QString Rtsa_Remote_Interface::getFreqAdjustStr(qreal freq, qint32 DecPrecision)
{
    QString strCenterFreq;
    qreal freqVal = 0;
    if(freq < 0)
    {
        freqVal = freq * -1;
    }
    else
    {
        freqVal = freq;
    }
    if(freqVal >= RTSA_GHZ)
    {
        strCenterFreq = QString::number((qreal) freqVal / RTSA_GHZ,'f',DecPrecision);
        strCenterFreq.replace(rx,"");
        strCenterFreq += QString(" GHz");
    }
    else if(freqVal >= RTSA_MHZ)
    {
        strCenterFreq = QString::number((qreal) freqVal / RTSA_MHZ,'f',DecPrecision);
        strCenterFreq.replace(rx,"");
        strCenterFreq += QString(" MHz");
    }
    else if(freqVal >= RTSA_KHZ)
    {
        strCenterFreq = QString::number((qreal) freqVal / RTSA_KHZ,'f',DecPrecision);
        strCenterFreq.replace(rx,"");
        strCenterFreq += QString(" kHz");
    }
    else if(freqVal >= 0)
    {
        strCenterFreq = QString::number((qreal) freqVal / RTSA_HZ,'f',DecPrecision);
        strCenterFreq.replace(rx,"");
        strCenterFreq += QString(" Hz");
    }
    if(freq < 0)
    {
        strCenterFreq = QString("-") + strCenterFreq;
    }
    return strCenterFreq;
}

/**
 * @brief  frequency unit.
 * @param  frequency
 * @author Tony
 */
qint32 Rtsa_Remote_Interface::freqUnitFindProc(qreal freq)
{
    if (freq >= RTSA_GHZ)
        return UNIT_GHZ;
    else if (freq >= RTSA_MHZ)
        return UNIT_MHZ;
    else if (freq >= RTSA_KHZ)
        return UNIT_KHZ;
    else
        return UNIT_HZ;
}

/**
 * @brief  frequency unit.
 * @param  frequency
 * @author Tony
 */
qint32 Rtsa_Remote_Interface::timeUnitFindProc(qreal time)
{
    if (time >= RTSA_S)
        return UNIT_S;
    else if (time >= RTSA_MS)
        return UNIT_MS;
    else if (time >= RTSA_US)
        return UNIT_US;
    else
        return UNIT_NS;
}

/**
 * @brief get freq string
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
QString Rtsa_Remote_Interface::getFreqStr(qint32 freqID)
{
    qreal freq = 0;
    switch(freqID)
    {
    case RTSA_CENTER_FREQ:
        //        freq = pRemoteScpi->getCenterFreq();
        break;
    case RTSA_START_FREQ:
        //        freq = pRemoteScpi->getStartFreq();
        break;
    case RTSA_STOP_FREQ:
        //        freq = pRemoteScpi->getStopFreq();
        break;
    case RTSA_SPAN_FREQ:
        //        freq = pRemoteScpi->getSpan();
        break;
    case RTSA_STEP_FREQ:
        //        freq = pRemoteScpi->getStepFreq();
        break;
    default:
        break;
    }
    return getFreqAdjustStr(freq);
}

/**
 * @brief get ref level string
 * @note
 * @author Albert
 * @since {2018-12-27}
*/
QString Rtsa_Remote_Interface::getRefLevelAdjustStr()
{
    qreal reflevel = ChangedBmToOherUnit();

    //    qint32 unit = getAmptUint();
    QString refStr = QString("");
    refStr = getRefLevelStr(reflevel);
    return refStr;
}

QString Rtsa_Remote_Interface::getFFTWindowStr()
{
    QString str = QString("");
    switch (globalUserVariable->gMeterParam.gConfig_BW.fftFilter) {
    case RTSA_HANNING:
        str = QString("Hanning");
        break;
    case RTSA_FLATTOP:
        str = QString("Flattop");
        break;
    case RTSA_GAUSIAN:
        str = QString("Gausian");
        break;
    case RTSA_RECTANGULAR:
        str = QString("Rectangular");
        break;
    case RTSA_KAISER:
        str = QString("Kaiser");
        break;
    case RTSA_BLACKMANHARRIS:
        str = QString("Black-Harris");
        break;
    default:
        break;
    }
    return str;
}

/**
* @brief getCurIndexBW
* @param get bw
* @Author Albert
* @date 2019-04-18
*/
qreal Rtsa_Remote_Interface::getCurIndexBW(qint32 index)
{
    qreal bw;
    if(index < RTSA_RBW0)
        index = RTSA_RBW0;
    else if(index > RTSA_RBW6)
        index  = RTSA_RBW6;
    bw = RTSA_RbwManualList[globalUserVariable->gMeterParam.gConfig_BW.fftFilter][globalUserVariable->gRbwGrade][index];
    return bw;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-05-24
*/
void Rtsa_Remote_Interface::setCurFmtDataIndex(qint32 curIndex)
{
    if(curIndex >= globalUserVariable->gMeterParam.gConfig_Trigger.fmtnumber - 1)
        curIndex = globalUserVariable->gMeterParam.gConfig_Trigger.fmtnumber - 1;
    else if(curIndex < 0)
        curIndex = 0;
    mFmtCurDataIndex = curIndex;
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-05-24
*/
qint32 Rtsa_Remote_Interface::getCurFmtDataIndex()
{
    return mFmtCurDataIndex;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-05-24
*/
void Rtsa_Remote_Interface::setFmtFreqData(qreal *data, qint32 dataNum)
{
    if(dataNum < 0)
    {
        return;
    }
    //    memset(globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq,0,RTSA_NUM_SWEEP_POINT * sizeof(qreal));
    qreal startFreq = getStartFreq()/RTSA_MHZ;
    for(qint32 i =0 ; i< dataNum; i++)
    {

        globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq[i] = data[i];

    }
    //    memcpy(globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq,data,dataNum * sizeof(qreal));
    for(qint32 i = 0; i < RTSA_BITVIEWNUM; i++)
    {
        if(mBitView[i]->getBitviewType() != RTSA_SPECTROGRAM)
        {
            mBitView[i]->setFMTData(globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq,dataNum,BIT_FMT_FREQ);
            mBitView[i]->refleshdisplay();
        }
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-24
*/
void Rtsa_Remote_Interface::setFmtAmptData(qreal *data, qint32 dataNum)
{
    if(dataNum < 0)
    {
        return;
    }
    memcpy(globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt,data,dataNum * sizeof(qreal));
    for(qint32 i = 0; i < RTSA_BITVIEWNUM; i++)
    {
        if(mBitView[i]->getBitviewType() != RTSA_SPECTROGRAM)
        {
            mBitView[i]->setFMTData(data,dataNum,BIT_FMT_AMPT);
            mBitView[i]->refleshdisplay();
        }
    }
    if(globalUserVariable->gfmtType == BIT_FMT_UPPER)
    {
        calUpperFmtPointsY(dataNum);
    }
    else
    {
        calLowerFmtPointsY(dataNum);
    }
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-05-23
*/
qreal* Rtsa_Remote_Interface::getFMTFreqData()
{
    return globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-23
*/
qreal* Rtsa_Remote_Interface::getFMTAmplitudeData()
{
    return globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt;
}

/**
 * @brief get current trace average on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool Rtsa_Remote_Interface::IsAvgOn(qint32 traceID)
{
    if(traceID < RTSA_TR1)
        traceID = RTSA_TR1;
    else if(traceID > RTSA_TR6)
        traceID = RTSA_TR6;
    return mBitView[curwindowindex]->getTraceAttribute(traceID,BIT_AVAG_ATTR);
}

/**
 * @brief get current trace now average num
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 Rtsa_Remote_Interface::getCurAvgNum(qint32 traceID)
{
    if(traceID < RTSA_TR1)
        traceID = RTSA_TR1;
    else if(traceID > RTSA_TR6)
        traceID = RTSA_TR6;
    qint32 AvgNum = mBitView[curwindowindex]->getTraceAttribute(traceID,BIT_AVAG_NUM_ATTR);
    qint32 CurAvgNum = mBitView[curwindowindex]->getTraceAttribute(traceID,BIT_AVAG_NOW_NUM_ATTR);
    if(CurAvgNum > AvgNum)
    {
        CurAvgNum = AvgNum;
    }
    return CurAvgNum;
}

/**
 * @brief set current trace id
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setCurTrace(qint32 traceID)
{
    if(traceID < RTSA_TR1)
        traceID = RTSA_TR1;
    else if(traceID > RTSA_TR6)
        traceID = RTSA_TR6;

    //      gTraceSelect = traceID;
    mBitView[curwindowindex]->setTraceAttribute(traceID,BIT_TRACE_INDEX,traceID);
    emit RedrawInfoShow(LABEL_TRACE_STATUS);
    return;
}

/**
 * @brief get current trace id
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 Rtsa_Remote_Interface::getCurTrace()
{
    return mBitView[curwindowindex]->getTraceAttribute(0,BIT_TRACE_INDEX);
}


/**
 * @brief set current trace type
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setTraceType(qint32 traceID, qint32 traceType)
{
    if(traceID < RTSA_TR1)
        traceID = RTSA_TR1;
    else if(traceID > RTSA_TR6)
        traceID = RTSA_TR6;

    //if type not change, do not set
    if(mBitView[curwindowindex]->getTraceAttribute(traceID,BIT_TRACE_TYPE_ATTR) == traceType)
        return;

    if(traceType < RTSA_TRACE_OFF)
        traceType = RTSA_TRACE_OFF;
    else if(traceType > RTSA_AVERAGE)
        traceType = RTSA_AVERAGE;
    mBitView[curwindowindex]->setTraceAttribute(traceID,BIT_TRACE_TYPE_ATTR,traceType);
    if(traceType == RTSA_AVERAGE)
    {
        setAvgOn(traceID,true);
    }
    else
    {
        setAvgOn(traceID,false);
    }
    mBitView[curwindowindex]->refleshdisplay();

    resetAvgCnt();
    emit RedrawInfoShow(LABEL_TRACE_STATUS);
    emit RedrawInfoShow(LABEL_AVERAGE);
    return;
}

/**
 * @brief get current trace type
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 Rtsa_Remote_Interface::getTraceType(qint32 traceID)
{
    if(traceID < RTSA_TR1)
        traceID = RTSA_TR1;
    else if(traceID > RTSA_TR6)
        traceID = RTSA_TR6;
    return mBitView[curwindowindex]->getTraceAttribute(traceID,BIT_TRACE_TYPE_ATTR);

}

/**
 * @brief set current trace average num
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setAvgNum(qint32 traceID, qint32 Num)
{

    if(traceID < RTSA_TR1)
        traceID = RTSA_TR1;
    else if(traceID > RTSA_TR6)
        traceID = RTSA_TR6;
    Num = Num <= 0 ? 1 : Num;
    Num = Num > 70000 ? 70000 : Num;
    //    gAverageCount[traceID] = Num;
    //    mBitView[curwindowindex]->setTraceAttribute(traceID,BIT_AVAG_ATTR,gTraceAverage[traceID]);
    mBitView[curwindowindex]->setTraceAttribute(traceID,BIT_AVAG_NUM_ATTR,Num);

    resetAvgCnt();
    return;
}

/**
 * @brief get current trace average num
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 Rtsa_Remote_Interface::getAvgNum(qint32 traceID)
{

    if(traceID < RTSA_TR1)
        traceID = RTSA_TR1;
    else if(traceID > RTSA_TR6)
        traceID = RTSA_TR6;
    return mBitView[curwindowindex]->getTraceAttribute(traceID,BIT_AVAG_NUM_ATTR);
}
/**
 * @brief Rtsa_Remote_Interface::setMarkerFreq
 * @param MarkerID
 * @param Freq
 */
void Rtsa_Remote_Interface::setMarkerFreq(qint32 MarkerID, qreal Freq)
{
    if(mBitView[curwindowindex]->getBitviewType() == RTSA_SPECTROGRAM)
        return;

    if(getMarkerType(MarkerID) == RTSA_REF)
    {
        setMarkerRefFreq(MarkerID,Freq);
    }
    else
    {
        setMarkerDeltaFreq(MarkerID,Freq);
    }
    emit BitViewMakerMoved(true);
    return;
}

/**
* @brief IsMarkerAlreadyOn
* @param none
* @Author Albert
* @date 2019-03-27
*/
bool Rtsa_Remote_Interface::IsMarkerAlreadyOn()
{
    bool isOn = false;
    for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
    {
        if(isMarkerOn(i))
        {
            isOn = true;
        }
    }
    return isOn;
}

/**
 * @brief Rtsa_Remote_Interface::getMarkerFreq
 * @param MarkerID
 * @return
 */
qreal Rtsa_Remote_Interface::getMarkerFreq(qint32 MarkerID)
{
    if(getMarkerType(MarkerID) == RTSA_REF)
    {
        return getMarkerRefFreq(MarkerID);
    }
    else
    {
        return getMarkerDeltaFreq(MarkerID);
    }
}


/**
* @brief
* @param
* @Author Albert
* @date 2019-05-14
*/
void Rtsa_Remote_Interface::showMarkerWidget(bool isShow)
{
    //    if(isMarkerBtnPressed == isShow)
    //        return;
    isMarkerBtnPressed = isShow;
    if(mIsZoomIn)
    {
        setZoomIn();
    }
    else
    {
        setZoomOut();
    }
    return;
}

QString Rtsa_Remote_Interface::getMarkerInfoStr(qint32 MarkerID)
{
    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;
    if(getMarkerType(MarkerID) == RTSA_REF)
    {
        return mBitView[curwindowindex]->getMarkerInfoStr(BIT_MARKER_NORMAL,MarkerID);
    }
    else
    {
        return mBitView[curwindowindex]->getMarkerInfoStr(BIT_MARKER_DELTA,MarkerID);
    }
}


bool Rtsa_Remote_Interface::isHaveLimitOn()
{
    for(qint32 i = RTSA_LIMIT1; i < RTSA_LIMIT6; i++)
    {
        if(IsCurLimitOn(i))
            return true;
    }
    return false;
}

void Rtsa_Remote_Interface::setLimitTableShow(bool isShow)
{

    if(isShow)
        mBitView[curwindowindex]->setTableEdit(BIT_LIMIT_EDIT_VISIABLE,BIT_LIMIT_TABLE_EDIT_SHOW);
    else
        mBitView[curwindowindex]->setTableEdit(BIT_LIMIT_EDIT_VISIABLE,BIT_LIMIT_TABLE_EDIT_HIDE);
    return;
}

/**
* @brief SetCurLimitDataIndex
* @param limit edit cur pos
* @Author Albert
* @date 2019-05-13
*/
void Rtsa_Remote_Interface::SetCurLimitDataIndex(qint32 curPos)
{
    qint32 curLimitID = getCurLimit();
    qint32 maxLimitIndex = getLimitDataNum(curLimitID);
    if(curPos < 0)
        curPos = 0;
    if(curPos > maxLimitIndex)
        curPos = maxLimitIndex - 1;
    mCurLimitDataPos = curPos;
    return;
}

/**
* @brief GetCurLimitDataIndex
* @param return cur select limit data index
* @Author Albert
* @date 2019-05-13
*/
qint32 Rtsa_Remote_Interface::GetCurLimitDataIndex()
{
    return mCurLimitDataPos;
}

/**
 * @brief delete limit
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::DeleteLimit(qint32 index)
{
    if(index < 0)
    {
        index = getCurLimit();
    }
    mBitView[curwindowindex]->setTableEdit(BIT_LIMIT_EDIT_VISIABLE,BIT_LIMIT_TABLE_EDIT_SHOW);
    mBitView[curwindowindex]->setTableEdit(BIT_LIMIT_DELETE_LIMIT,index);
    mBitView[curwindowindex]->refleshdisplay();
    return;
}

/**
 * @brief set current limit data freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setLimitFreqData(qreal *pData, qint32 DataNum, qint32 LimitID)
{
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;
    mBitView[curwindowindex]->setLimitAttribute(BIT_LIMIT_POINT_NUM,DataNum,LimitID);
    mBitView[curwindowindex]->setLimitPointData(pData,DataNum,BIT_LIMIT_FREQ,LimitID);
    return;
}

/**
 * @brief get current limit data freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal* Rtsa_Remote_Interface::getLimitFreqData(qint32 LimitID)
{
    memset(&gLimitFreq,0,sizeof(gLimitFreq));
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;
    mBitView[curwindowindex]->getLimitPointData(gLimitFreq,RTSA_LIMIT_TOTAL,BIT_LIMIT_FREQ,LimitID);
    return gLimitFreq;
}

/**
 * @brief set current limit data ampt
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setLimitAmptData(qreal *pData, qint32 DataNum, qint32 LimitID)
{
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;
    mBitView[curwindowindex]->setLimitAttribute(BIT_LIMIT_POINT_NUM,DataNum,LimitID);
    mBitView[curwindowindex]->setLimitPointData(pData,DataNum,BIT_LIMIT_AMPT,LimitID);
    return;
    return;
}

/**
 * @brief get current limit data ampt
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal* Rtsa_Remote_Interface::getLimitAmptData(qint32 LimitID)
{

    memset(&gLimitAmpt,0,sizeof(gLimitAmpt));
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;
    mBitView[curwindowindex]->getLimitPointData(gLimitAmpt,RTSA_LIMIT_TOTAL,BIT_LIMIT_AMPT,LimitID);
    return gLimitAmpt;
}

void Rtsa_Remote_Interface::adjustSpanFreq(qreal freq)
{
    freq = freq < 0 ? globalUserVariable->gbitsspan : freq;

    //Tony 0906
    freq = globalUserVariable->adjustSpanBySpan(freq);
    //Tony 0907
    if(globalUserVariable->gMeterParam.gConfig_BW.autoRbw == RTSA_MANUAL)
    {
        globalUserVariable->adjustRbwBySpan(freq);
    }
    else
    {
        globalUserVariable->gMeterParam.gConfig_BW.rbw = RTSA_RbwManualList[globalUserVariable->gMeterParam.gConfig_BW.fftFilter][globalUserVariable->gRbwGrade][1];
        if(globalUserVariable->gMeterParam.gConfig_BW.fftFilter == RTSA_RECTANGULAR)
        {
            globalUserVariable->gMeterParam.gConfig_BW.rbw = RTSA_RbwManualList[globalUserVariable->gMeterParam.gConfig_BW.fftFilter][globalUserVariable->gRbwGrade][6];
        }
        else
        {
            globalUserVariable->gMeterParam.gConfig_BW.rbw = RTSA_RbwManualList[globalUserVariable->gMeterParam.gConfig_BW.fftFilter][globalUserVariable->gRbwGrade][5];
        }
    }
    globalUserVariable->adjustFreqBySpan(freq);
    globalUserVariable->stepFreqCalculatorFunc();
    //    globalUserVariable->markerPositionReCalculatorFunc();
}

void Rtsa_Remote_Interface::adjustAcqtime(qreal time)
{//调整ACQtime时与设置有啥区别？？？
    if(time > RTSA_ACQTIME_MAX)
    {
        time = RTSA_ACQTIME_MAX;
    }
    if(globalUserVariable->gMeterParam.gConfig_Sweep.autoAcqtime == RTSA_AUTO)
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
    globalUserVariable->gMeterParam.gConfig_Sweep.acqTimeVal;

    return;
}

void Rtsa_Remote_Interface::AdjustPeriodTime(qreal time)
{
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

    globalUserVariable->gMeterParam.gConfig_Trigger.triggerPeriodTime = time;

    return ;
}

void Rtsa_Remote_Interface::amplitudeAttenControl()
{
    //Johnson Add
    if(globalUserVariable->gMeterParam.gConfig_Amplitude.attenAuto == RTSA_AUTO)
    {
        if(globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel-5.>=0.)
        {
            globalUserVariable->gMeterParam.gConfig_Amplitude.preAmpStatus = RTSA_OFF;
        }

        if(globalUserVariable->gMeterParam.gConfig_Amplitude.preAmpStatus == RTSA_OFF)
        {
            if(globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel-15.>0.)      globalUserVariable->gMeterParam.gConfig_Amplitude.attenVal = 30.;
            else if(globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel-10.>0.) globalUserVariable->gMeterParam.gConfig_Amplitude.attenVal = 25.;
            else if(globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel-5.>0.)  globalUserVariable->gMeterParam.gConfig_Amplitude.attenVal = 20.;
            else if(globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel>0.)     globalUserVariable->gMeterParam.gConfig_Amplitude.attenVal = 15.;
            else if(globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel+5.>0.)  globalUserVariable->gMeterParam.gConfig_Amplitude.attenVal = 10.;
            else if(globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel+10.>0.) globalUserVariable->gMeterParam.gConfig_Amplitude.attenVal = 5.;


            if(globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel+10.<=0.)     globalUserVariable->gMeterParam.gConfig_Amplitude.attenVal = 0.;
        }
        else
        {
            if(globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel+5.>0.&&globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel<=0) globalUserVariable->gMeterParam.gConfig_Amplitude.attenVal = 30.;
            else if(globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel+10.>0.)                             globalUserVariable->gMeterParam.gConfig_Amplitude.attenVal = 25.;
            else if(globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel+15.>0.)                             globalUserVariable->gMeterParam.gConfig_Amplitude.attenVal = 20.;
            else if(globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel+20.>0.)                             globalUserVariable->gMeterParam.gConfig_Amplitude.attenVal = 15.;
            else if(globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel+25.>0.)                             globalUserVariable->gMeterParam.gConfig_Amplitude.attenVal = 10.;
            else if(globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel+30.>0.)                             globalUserVariable->gMeterParam.gConfig_Amplitude.attenVal = 5.;


            if(globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel+30.<=0)                                  globalUserVariable->gMeterParam.gConfig_Amplitude.attenVal = 0.;
        }
    }
    else
    {
        if(globalUserVariable->gMeterParam.gConfig_Amplitude.preAmpStatus != RTSA_OFF)
        {
            if(globalUserVariable->gMeterParam.gConfig_Amplitude.attenVal > 30)
                globalUserVariable->gMeterParam.gConfig_Amplitude.attenVal = 30;
        }

    }
}

void Rtsa_Remote_Interface::ChangeOtherUnitTodBm(qreal refLevel)
{
    qreal value = refLevel;
    switch (globalUserVariable->gMeterParam.gConfig_Amplitude.units[curwindowindex]) {
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
    globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel = value;
    if(value < RTSA_SPEC_AMPTD_MIN)
    {
        globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel = RTSA_SPEC_AMPTD_MIN;
    }
    else if(value > RTSA_SPEC_AMPTD_MAX)
    {
        globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel = RTSA_SPEC_AMPTD_MAX;
    }
    return;
}

/**
 * @brief Rtsa_Remote_Interface::ChangedBmToOherUnit
 * @param refLevel
 * @return
 */
qreal Rtsa_Remote_Interface::ChangedBmToOherUnit()
{
    qreal reflevel = getRefLevel() /*+ globalUserVariable->gMeterParam.gConfig_Amplitude.refOffset[curwindowindex]*/;
    qreal tempVal = 0.;
    qreal value = 0;
    qint32 unit = getAmptUint();
    switch (unit) {
    case RTSA_WATTS: //
        value = qPow(10, reflevel / 10.) / 1000;
        break;
    case RTSA_VOLT:  //
        tempVal = qPow(10, reflevel / 10.);
        value = qPow(50 * tempVal * 0.001, 0.5);//uv
        break;
    case RTSA_DBV:
        value = reflevel + RTSA_dBVFix;
        break;
    case RTSA_DBMV:
        value = reflevel + RTSA_dBmVFix;
        break;
    case RTSA_DBUV:
        value = reflevel + RTSA_dBuVFix;
        break;
    default:
        value = reflevel;
    }
    return value;
}

/**
 * @brief Rtsa_Remote_Interface::getRefLevelStr
 * @param reflevel
 * @return
 */
QString Rtsa_Remote_Interface::getRefLevelStr(qreal reflevel)
{
    QString refStr = QString("");
    qint32 unit = getAmptUint();
    switch(unit)
    {
    case RTSA_DBM:
        if(reflevel >= 0)
        {
            reflevel = (qreal)(qint64)((reflevel + 0.005) * 100) / 100;
        }
        else
        {
            reflevel = (qreal)(qint64)((reflevel - 0.005) * 100) / 100;
        }
        refStr = QString::number(reflevel,'f',2);
        refStr += QString(" dBm");
        break;
    case RTSA_DBV:
        if(reflevel >= 0)
        {
            reflevel = (qreal)(qint64)((reflevel + 0.005) * 100) / 100;
        }
        else
        {
            reflevel = (qreal)(qint64)((reflevel - 0.005) * 100) / 100;
        }
        refStr = QString::number(reflevel,'f',2);
        refStr += QString(" dBV");
        break;
    case RTSA_DBMV:
        if(reflevel >= 0)
        {
            reflevel = (qreal)(qint64)((reflevel + 0.005) * 100) / 100;
        }
        else
        {
            reflevel = (qreal)(qint64)((reflevel - 0.005) * 100) / 100;
        }
        refStr = QString::number(reflevel,'f',2);
        refStr += QString(" dBmV");
        break;
    case RTSA_DBUV:
        if(reflevel >= 0)
        {
            reflevel = (qreal)(qint64)((reflevel + 0.005) * 100) / 100;
        }
        else
        {
            reflevel = (qreal)(qint64)((reflevel - 0.005) * 100) / 100;
        }
        refStr = QString::number(reflevel,'f',2);
        refStr += QString(" dBuV");
        break;
    case RTSA_VOLT:
        refStr = getRefLevelVoltStr(reflevel);
        break;
    case RTSA_WATTS:
        refStr = getRefLevelWattStr(reflevel);
        break;
    default:
        break;
    }    return refStr;
}

/**
 * @brief get ref level string
 * @note
 * @author Albert
 * @since {2018-12-27}
*/
QString Rtsa_Remote_Interface::getRefLevelVoltStr(qreal reflevel)
{
    QString voltStr;
    QString UnitStr;
    qreal UNION_SIZE = 1.0;
    if(reflevel > UNION_SIZE)
    {
        UnitStr = QString(" V");
    }
    else if(reflevel >= (UNION_SIZE / 1000.0))
    {
        reflevel *= 1000.0;
        UnitStr = QString(" mV");
    }
    else if(reflevel >= (UNION_SIZE / 1000000.0))
    {
        reflevel *= 1000000.0;
        UnitStr = QString(" uV");
    }
    else if(reflevel >= (UNION_SIZE / 1000000000.0))
    {
        reflevel *= 1000000000.0;
        UnitStr = QString(" nV");
    }
    else if(reflevel >= (UNION_SIZE / 1000000000000.0))
    {
        reflevel *= 1000000000000.0;
        UnitStr = QString(" pV");
    }
    else if(reflevel >= (UNION_SIZE / 1000000000000000.0))
    {
        reflevel *= 1000000000000000.0;
        UnitStr = QString(" fV");
    }
    else if(reflevel >= (UNION_SIZE / 1000000000000000000.0))
    {
        reflevel *= 1000000000000000000.0;
        UnitStr = QString(" aV");
    }
    else if(reflevel >= (UNION_SIZE / 1000000000000000000000.0))
    {
        reflevel *= 1000000000000000000.0;
        UnitStr = QString(" zV");
    }
    else
    {
        reflevel *= 1000000000000000000000000.0;
        UnitStr = QString(" yV");
    }
    // Only 2 decimal places reserved
    reflevel = (qreal)(qint32)((reflevel + 0.005) * 100) /100;
    voltStr = QString::number(reflevel,'f',2);
    //    voltStr.replace(rx,"");
    voltStr += UnitStr;
    return voltStr;
}

/**
 * @brief get ref level string
 * @note
 * @author Albert
 * @since {2018-12-27}
*/
QString Rtsa_Remote_Interface::getRefLevelWattStr(qreal reflevel)
{
    QString wattStr;
    QString UnitStr;
    qreal UNION_SIZE = 1.0;
    if(reflevel >= UNION_SIZE)
    {
        UnitStr = QString(" W");
    }
    else if(reflevel >= (UNION_SIZE / 1000.0))
    {
        reflevel *= 1000.0;
        UnitStr = QString(" mW");
    }
    else if(reflevel >= (UNION_SIZE / 1000000.0))
    {
        reflevel *= 1000000.0;
        UnitStr = QString(" uW");
    }
    else if(reflevel >= (UNION_SIZE / 1000000000.0))
    {
        reflevel *= 1000000000.0;
        UnitStr = QString(" nW");
    }
    else if(reflevel >= (UNION_SIZE / 1000000000000.0))
    {
        reflevel *= 1000000000000.0;
        UnitStr = QString(" pW");
    }
    else if(reflevel >= (UNION_SIZE / 1000000000000000.0))
    {
        reflevel *= 1000000000000000.0;
        UnitStr = QString(" fW");
    }
    else /*if(reflevel >= (UNION_SIZE / 1000000000000000000.0))*/
    {
        reflevel *= 1000000000000000000.0;
        UnitStr = QString(" aW");
    }
    //    else if(reflevel >= (UNION_SIZE / 1000000000000000000000.0))
    //    {
    //        reflevel *= 1000000000000000000000.0;
    //        UnitStr = QString(" zW");
    //    }
    //    else
    //    {
    //        reflevel *= 1000000000000000000000000.0;
    //        UnitStr = QString(" yW");
    //    }
    // Only 2 decimal places reserved
    reflevel = (qreal)(qint32)((reflevel + 0.005) * 100) /100;
    wattStr = QString::number(reflevel,'f',2);
    //    wattStr.replace(rx,"");
    wattStr += UnitStr;
    return wattStr;
}

void Rtsa_Remote_Interface::setSleepTime(qreal sleepTime)
{
    if(sleepTime < RTSA_ACQ_MIN_TIME)
        sleepTime = RTSA_ACQ_MIN_TIME;
    else if(sleepTime > RTSA_ACQ_MAX_TIME)
        sleepTime = RTSA_ACQ_MAX_TIME;
    if(sleepTime < globalUserVariable->gMeterParam.gConfig_Sweep.acqTimeVal)
        sleepTime = globalUserVariable->gMeterParam.gConfig_Sweep.acqTimeVal;
    globalUserVariable->gReadMeterDataSleepTime = sleepTime;
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-06-10
*/
void Rtsa_Remote_Interface::calUpperFmtPointsY(qint32 dataNum)
{
    if(dataNum <= 0)
        return;
    qint32 highPointY = 200;
    qint32 lowPointY = 0;
    qint32 pointY = 0;
    qreal yDivs = 0;
    qint32 cnt = 0;
    qreal baseY = globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel + globalUserVariable->gMeterParam.gConfig_Amplitude.refOffset[curwindowindex];
    qreal BottomY = baseY - globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex] * 10;
    qreal freqStep = globalUserVariable->gMeterParam.gConfig_FreqSpan.gSpanFreq / (RTSA_NUM_SWEEP_POINT - 1);
    qint32 xDivs = 0;
    qreal Freq0 = globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq[0];
    qreal Freq1 = 0.0;

    if(Freq0 * RTSA_MHZ < globalUserVariable->gMeterParam.gConfig_FreqSpan.gStartFreq)
    {
        xDivs = 0;
    }
    else
    {
        xDivs = (qint32)((Freq0 * RTSA_MHZ - globalUserVariable->gMeterParam.gConfig_FreqSpan.gStartFreq) / freqStep);
    }
    qint32 index = xDivs;

    //divide into 3 parts
    memset(&globalUserVariable->gFmtData,0,sizeof(qint32) * RTSA_NUM_SWEEP_POINT);
    if(dataNum == 1)
    {
        index = xDivs;
        yDivs = (globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[1] - globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[0])/xDivs;
        lowPointY = (globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[0]/* + RTSA_COMP_TEMPDATA*/ + yDivs * index - BottomY)/(globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex] * 10) * 200;
        pointY = (1 << 16) + (highPointY << 8) + lowPointY;
        globalUserVariable->gFmtData[index] = pointY;
        //        while (xDivs) {
        //            lowPointY = (globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[0]/* + RTSA_COMP_TEMPDATA*/ + yDivs * index - BottomY)/(globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex] * 10) * 200;
        //            pointY = (1 << 16) + (highPointY << 8) + lowPointY;
        //            globalUserVariable->gFmtData[index] = pointY;
        //            index ++;
        //            xDivs --;
        //        }
    }
    else
    {
        for(qint32 i = 1 ; i < dataNum; i++)
        {
            Freq0 = globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq[i - 1];
            if(Freq0 < globalUserVariable->gMeterParam.gConfig_FreqSpan.gStartFreq/RTSA_MHZ)
            {
                Freq0 = globalUserVariable->gMeterParam.gConfig_FreqSpan.gStartFreq/RTSA_MHZ;
            }
            Freq1 = globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq[i];
            xDivs = (Freq1 - Freq0) * RTSA_MHZ /freqStep ;
            if(xDivs == 0)
            {
                yDivs = globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[i];
            }
            else
            {
                yDivs = (globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[i] - globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[i - 1])/xDivs;
            }
            cnt = 0;
            //            qreal a = 0;
            while (xDivs) {
                lowPointY = (globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[i - 1]/* + RTSA_COMP_TEMPDATA*/ + cnt * yDivs - BottomY)/(globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex] * 10) * 200;
                pointY = (1 << 16) + (highPointY << 8) + lowPointY;
                globalUserVariable->gFmtData[index] = pointY;
                index ++;
                xDivs --;
                cnt ++;
            }
        }
    }
    //    qreal a = (globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[dataNum - 1] - BottomY);
    lowPointY = (globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[dataNum - 1]/* + RTSA_COMP_TEMPDATA*/ - BottomY)/(globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex] * 10) * 200;
    pointY = (1 << 16) + (highPointY << 8) + lowPointY;
    globalUserVariable->gFmtData[index] = pointY;


    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-10
*/
void Rtsa_Remote_Interface::calLowerFmtPointsY(qint32 dataNum)
{
    if(dataNum < 0)
        return;
    qint32 highPointY = 200;
    qint32 lowPointY = 0;
    qint32 pointY = 0;
    qreal yDivs = 0;
    qint32 cnt = 0;
    qreal baseY = globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel + globalUserVariable->gMeterParam.gConfig_Amplitude.refOffset[curwindowindex];
    qreal BottomY = baseY - globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex] * 10;
    qreal freqStep = globalUserVariable->gMeterParam.gConfig_FreqSpan.gSpanFreq / (RTSA_NUM_SWEEP_POINT - 1);
    qint32 xDivs = 0;
    qreal Freq0 = globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq[0];
    qreal Freq1 = 0.0;

    if(Freq0 * RTSA_MHZ < globalUserVariable->gMeterParam.gConfig_FreqSpan.gStartFreq)
    {
        xDivs = 0;
    }
    else
    {
        xDivs = (qint32)((Freq0 * RTSA_MHZ - globalUserVariable->gMeterParam.gConfig_FreqSpan.gStartFreq) / freqStep);
    }
    //    qint32 xDivs = (qint32)((globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq[0] * RTSA_MHZ - globalUserVariable->gMeterParam.gConfig_FreqSpan.gStartFreq) / freqStep);
    qint32 index = xDivs;

    //divide into 3 parts
    memset(&globalUserVariable->gFmtData,0,sizeof(qint32) * RTSA_NUM_SWEEP_POINT);
    if(dataNum == 1)
    {
        index = xDivs;
        yDivs = (globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[1] - globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[0])/xDivs;
        highPointY = (globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[0]/* + RTSA_COMP_TEMPDATA*/ + yDivs * index - BottomY)/(globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex] * 10) * 200;
        pointY = (1 << 16) + (highPointY << 8) + lowPointY;
        globalUserVariable->gFmtData[index] = pointY;

    }
    else
    {
        for(qint32 i = 1 ; i < dataNum; i++)
        {
            Freq0 = globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq[i - 1];
            if(Freq0 < globalUserVariable->gMeterParam.gConfig_FreqSpan.gStartFreq/RTSA_MHZ)
            {
                Freq0 = globalUserVariable->gMeterParam.gConfig_FreqSpan.gStartFreq/RTSA_MHZ;
            }
            else if(Freq0 >= globalUserVariable->gMeterParam.gConfig_FreqSpan.gStopFreq/RTSA_MHZ)
            {
                Freq0 = globalUserVariable->gMeterParam.gConfig_FreqSpan.gStopFreq/RTSA_MHZ;
            }
            Freq1 = globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq[i];
            if(Freq1 >= globalUserVariable->gMeterParam.gConfig_FreqSpan.gStopFreq/RTSA_MHZ)
            {
                Freq1 = globalUserVariable->gMeterParam.gConfig_FreqSpan.gStopFreq/RTSA_MHZ;
            }
            else if(Freq1 < globalUserVariable->gMeterParam.gConfig_FreqSpan.gStartFreq/RTSA_MHZ)
            {
                Freq1 = globalUserVariable->gMeterParam.gConfig_FreqSpan.gStartFreq/RTSA_MHZ;
            }

            xDivs = (Freq1 - Freq0) * RTSA_MHZ /freqStep ;
            if(xDivs == 0)
            {
                yDivs = globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[i];
            }
            else
            {
                yDivs = (globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[i] - globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[i - 1])/xDivs;
            }
            cnt = 0;
            //            qreal a = 0;
            while (xDivs) {
                highPointY = (globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[i - 1]/* + RTSA_COMP_TEMPDATA*/ + cnt * yDivs - BottomY)/(globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex] * 10) * 200;
                pointY = (1 << 16) + (highPointY << 8) + lowPointY;
                globalUserVariable->gFmtData[index] = pointY;
                index ++;
                xDivs --;
                cnt ++;
            }
        }
    }
    highPointY = (globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[dataNum - 1]/* + RTSA_COMP_TEMPDATA*/ - BottomY)/(globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex] * 10) * 200;
    pointY = (1 << 16) + (highPointY << 8) + lowPointY;
    globalUserVariable->gFmtData[index] = pointY;


    return;
}

void Rtsa_Remote_Interface::ReSetAllFmtData()
{
    qreal tempFreqData[RTSA_NUM_SWEEP_POINT];
    qreal tempAmptData[RTSA_NUM_SWEEP_POINT];
    memset(tempFreqData,0,sizeof(tempFreqData));
    memset(tempAmptData,0,sizeof(tempAmptData));

    memcpy(tempFreqData,globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq,RTSA_NUM_SWEEP_POINT*sizeof(qreal));
    memcpy(tempAmptData,globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt,RTSA_NUM_SWEEP_POINT*sizeof(qreal));

    qsort(&tempFreqData, globalUserVariable->gMeterParam.gConfig_Trigger.fmtnumber, sizeof(tempFreqData[0]), compare);
    for(qint32 j = 0; j < globalUserVariable->gMeterParam.gConfig_Trigger.fmtnumber; j ++)
    {
        //        globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq[j] = tempFreqData[j];
        for(qint32 i = 0; i < RTSA_NUM_SWEEP_POINT; i++)
        {
            if((tempFreqData[j] - globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq[i] <= RTSA_ESP_ZERO) && (tempFreqData[j] - globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq[i] >= -RTSA_ESP_ZERO))
            {
                globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[j] = tempAmptData[i];
                break;
            }
        }
    }

    setFmtFreqData(tempFreqData,globalUserVariable->gMeterParam.gConfig_Trigger.fmtnumber);
    setFmtAmptData(globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt,globalUserVariable->gMeterParam.gConfig_Trigger.fmtnumber);
}

bool Rtsa_Remote_Interface::isFreqInFmtArray(qreal freq)
{
    bool isTrue = false;
    qint32 iBowIndex = 0,iHighIndex = 0;
    for(qint32 i = 0;i < RTSA_NUM_SWEEP_POINT; i++)
    {
        if(freq <= globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq[i])
        {
            iBowIndex = i;
            break;
        }
    }

    for(qint32 j = 0;j < globalUserVariable->gMeterParam.gConfig_Trigger.fmtnumber; j++)
    {
        if(freq >= globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq[j])
        {
            iHighIndex = j;
            //            break;
        }
    }
    if(iHighIndex == iBowIndex)
    {
        if((freq - globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq[iHighIndex] <= RTSA_ESP_ZERO) && (freq - globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq[iHighIndex] >= -RTSA_ESP_ZERO))
        {
            isTrue = true;
        }
        else
        {
            isTrue = false;
        }
    }
    else
    {
        isTrue = false;
    }
    return isTrue;
}

/**
 * @brief set current trace average on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setAvgOn(qint32 traceID, bool isOn)
{

    if(traceID < RTSA_TR1)
        traceID = RTSA_TR1;
    else if(traceID > RTSA_TR6)
        traceID = RTSA_TR6;
    //if type not change, do not set
    if(mBitView[curwindowindex]->getTraceAttribute(traceID,BIT_AVAG_ATTR) == isOn)
        return;

    mBitView[curwindowindex]->setTraceAttribute(traceID,BIT_AVAG_ATTR,isOn);
    mBitView[curwindowindex]->setTraceAttribute(traceID,BIT_AVAG_NUM_ATTR,getAvgNum(traceID));
    return;
}

/**
 * @brief reset average count
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::resetAvgCnt()
{
    for(qint32 j = 0 ;j < RTSA_BITVIEWNUM; j++)
    {
        mBitView[j]->refreshSepectrogramRect();
        for(qint32 i = 0; i < RTSA_NUM_TRACE; i++)
        {
            qint32 tracetype = mBitView[j]->getTraceAttribute(i,BIT_TRACE_TYPE_ATTR);
            //            qint32 tracetype = mBitView[j]->getTraceAttribute(i,BIT_TRACE_TYPE_ATTR);
            //Albert 19/03/13 when sweep param changed, trace data should refresh.
            //            mBitView[j]->setTraceAttribute(i,BIT_TRACE_TYPE_ATTR,getTraceType(i));
            if(tracetype == RTSA_AVERAGE)
            {
                mBitView[j]->setTraceAttribute(i,BIT_RE_AVAG_ATTR,BITON);
            }
            if(tracetype == RTSA_MAX_HOLD)
            {
                mBitView[j]->setTraceAttribute(i,BIT_TRACE_TYPE_ATTR,BIT_MAX_HOLD);
            }
            if(tracetype == RTSA_MIN_HOLD)
            {
                mBitView[j]->setTraceAttribute(i,BIT_TRACE_TYPE_ATTR,BIT_MIN_HOLD);
            }
        }
    }
    refreshMainDisplay();
    return;
}

/**
 * @brief set render trace data
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setTraceData(qreal *pData, qint32 dataNum, qint32 traceID)
{
    if(traceID < RTSA_TR1)
        traceID = RTSA_TR1;
    else if(traceID > RTSA_TR6)
        traceID = RTSA_TR6;
    mBitView[curwindowindex]->setTraceRenderData(pData,dataNum,traceID);
    return;
}

/**
 * @brief get render trace data
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal* Rtsa_Remote_Interface::GetTraceData(qint32 dataNum, qint32 traceID)
{
    if(traceID < RTSA_TR1)
        traceID = RTSA_TR1;
    else if(traceID > RTSA_TR6)
        traceID = RTSA_TR6;
    mBitView[curwindowindex]->getTraceRenderData(gTraceData,dataNum,traceID);
    return gTraceData;
}

/**
* @brief getMaxTraceData
* @param [IN] pData，startIndex，nNum
* @Author Albert
* @date 2019-04-15
*/
qreal Rtsa_Remote_Interface::getMaxTraceData(qreal *pData, qint32 startIndex, qint32 nNum)
{
    qreal maxValue = 0.0;
    if(startIndex < 0)
        startIndex = 0;
    maxValue = pData[startIndex];
    for(qint32 i = startIndex; i < startIndex + nNum; i++)
    {
        if(maxValue <= pData[i])
        {
            maxValue = pData[i];
        }
    }
    return maxValue;
}

qreal Rtsa_Remote_Interface::getMarkerCurFreq(qint32 Type)
{
    return mBitView[curwindowindex]->getMarkerCurrentFreq(Type);
}


/**
* @brief
* @param
* @Author Albert
* @date 2019-08-16
*/
bool Rtsa_Remote_Interface::hasMarkerOn()
{
    bool markerOn = false;
    for(qint32 j = 0; j < RTSA_BITVIEWNUM; j++)
    {
        for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
        {
            if(mBitView[j]->isHidden())
            {
                continue;
            }
            markerOn = mBitView[j]->getMarkerAttribute(BIT_MARKER_VISIABLE,i);
            if(markerOn)
            {
                return markerOn;
            }
        }
    }
    return markerOn;
}

/**
 * @brief set current marker display
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setMarkerDisplay(qint32 display)
{
    if(mBitView[curwindowindex]->getBitviewType() == RTSA_SPECTROGRAM)
        return;

    if(display < RTSA_MKR_TABLE)
        display = RTSA_MKR_TABLE;
    else if(display > RTSA_MKR_OFF)
        display = RTSA_MKR_OFF;
    //    gMarkerDisplay = display;
    mBitView[curwindowindex]->setMarkerAttribute(BIT_MARKER_DISPLAY,display);
    mBitView[curwindowindex]->markerUpdateByFreq();
    mBitView[curwindowindex]->refleshdisplay();
    mBitView[curwindowindex]->refleshmarker();
    return;
}

/**
 * @brief get current marker display
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 Rtsa_Remote_Interface::getMarkerDisplay()
{
    return mBitView[curwindowindex]->getMarkerAttribute(BIT_MARKER_DISPLAY);
}

/**
 * @brief set current marker to step freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setMarkerToCFStep()
{
    if(mBitView[curwindowindex]->getBitviewType() == RTSA_SPECTROGRAM)
        return;

    qint32 markerID = getCurMarkerID();
    qreal CFStepFreq = 0;
    if(isMarkerOn(markerID))
    {
        CFStepFreq = getMarkerCurFreq(BIT_MARKER_STEP_FREQ);
        setCFStep(CFStepFreq);
    }
    return;
}


/**
 * @brief set current marker to ref level
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setMarkerToRefLevel()
{
    if(mBitView[curwindowindex]->getBitviewType() == RTSA_SPECTROGRAM)
        return;

    qint32 markerID = getCurMarkerID();
    qreal refLevel = 0;
    if(isMarkerOn(markerID))
    {
        refLevel = mBitView[curwindowindex]->getMarkerAmptInfo(BIT_MARKER_REF);
        setRefLevel(refLevel);
    }
    return;
}

/**
 * @brief get current marker ref ampt
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal Rtsa_Remote_Interface::getMarkerRefAmpt(qint32 MarkerID)
{
    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;
    return mBitView[curwindowindex]->getMarkerInfo(BIT_MARKER_NORMAL,MarkerID);
}

/**
 * @brief get current marker delta ampt
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal Rtsa_Remote_Interface::getMarkerDeltaAmpt(qint32 MarkerID)
{   if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;
    return mBitView[curwindowindex]->getMarkerInfo(BIT_MARKER_DELTA,MarkerID);

}

/**
 * @brief get current marker noise ampt
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal Rtsa_Remote_Interface::getMarkerNoiseAmpt(qint32 MarkerID)
{
    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;
    return mBitView[curwindowindex]->getMarkerInfo(BIT_MARKER_NOISE,MarkerID);
}

/**
 * @brief set limit data num
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setLimitNum(qint32 bitViewNo,qint32 LimitID, qint32 num)
{
    if(LimitID < 0)
    {
        LimitID = getCurLimit();
    }
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;
    mBitView[bitViewNo]->setLimitAttribute(BIT_LIMIT_POINT_NUM,num,LimitID);
    return;

}

/**
 * @brief Init BitView
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::InitBitView(QWidget *widget)
{
    bitviewbottomdisplay = BV_BOTTOM_STARTANDSTOP;
    bitviewtopdisplay    = BV_TOP_APMTINFO ;
    mWidth = widget->width();
    mHeight = widget->height();
    for(qint32 i = 0;i < RTSA_BITVIEWNUM;i++)
    {
        mBitView[i] = new BitView(i,curwindowindex,widget);
        //        mBitView[i]->setWindowRect(mWidth,mHeight);
        //        mBitView[i]->setGeometry(QRect(0,0,0,0));
        connect(mBitView[i],SIGNAL(singleClicked(quint32)),this,SLOT(setcurrentview(quint32)));
        connect(mBitView[i],SIGNAL(markerchange(qint32)),this,SLOT(markerchange(qint32)));
        connect(mBitView[i],SIGNAL(markerMove(bool)),this,SLOT(markerMove(bool)));
        connect(mBitView[i],SIGNAL(mouseDoubleClickedSig(bool)),this,SLOT(changeBitViewSize(bool)));

    }

    // load state file at first
    qint32 LoadFileType = 0;
    qint32 loadState = 0;
    loadState = loadPresState();
    //     if no state files, state must set default.
    if(loadState < 0)
    {
        globalUserVariable->gfileType =STATE_DEFAULT_FILE;
        PltSaveConditions(globalUserVariable->gfileType);
    }
    LoadFileType = PltLoadConditions(globalUserVariable->gfileType);
    //    if(globalUserVariable->gfileType < 0)
    //    {
    //        LoadFileType = PltLoadConditions(STATE_LAST_FILE);
    //    }
    //    else
    //    {
    //        LoadFileType = PltLoadConditions(globalUserVariable->gfileType);
    //    }

    if(LoadFileType < 0)
    {
        QThread::msleep(200);
        setDisplay(RTSA_DENSITY);
    }

    //Link mark judgment
    qint32 linkFlg = -1;
    linkFlg = loadLinkState();
    if(linkFlg >0) //link OK
    {
        //Read Plt Mode

    }
    else //No Link
    {
        //        LoadFileType = PltLoadConditions(globalUserVariable->gfileType);
        //    //    if(globalUserVariable->gfileType < 0)
        //    //    {
        //    //        LoadFileType = PltLoadConditions(STATE_LAST_FILE);
        //    //    }
        //    //    else
        //    //    {
        //    //        LoadFileType = PltLoadConditions(globalUserVariable->gfileType);
        //    //    }
        //    //     if no state files, state must set default.
        //        if(LoadFileType < 0)
        //        {
        //            QThread::msleep(200);
        //            setDisplay(RTSA_DENSITY);
        //        }

    }
    updateGeneralDataToBitview(RTSA_ACQ_INFO);
    //Tony 1102
    updateGeneralDataToBitview(RTSA_RBW_INFO);
    //Tony 1102
    updateGeneralDataToBitview(RTSA_FREQ_INFO);
    updateGeneralDataToBitview(RTSA_REF_LVL);

    //! Albert 12/17 important:
    //! must set display mode, or limit widget will not show header info.
    setSystemDisplay(BIT_DEFAULTMODE);

    // delete unnecessary '0'
    rx.setPattern("(\\.){0,1}0+$");

    ReDrawLeftInfo();
}

/**
 * @brief Gobal Variable initial set
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setGobalVariable(RtSa_User_Variable *globalVariable)
{
    globalUserVariable = globalVariable;
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-07-02
*/
void Rtsa_Remote_Interface::SetDisplayMode(qint32 mDisMode)
{
    if(mDisMode < RTSA_INDOOR)
        mDisMode = RTSA_INDOOR;
    else if(mDisMode > RTSA_NIGHT)
        mDisMode = RTSA_NIGHT;
    setDisplay(mDisMode);
    setSystemDisplay(mDisMode);
    emit RedrawInfoShow(LABEL_DISPLAY);
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-07-02
*/
qint32 Rtsa_Remote_Interface::GetDisplayMode()
{
    return getDisplay();
}

/**
 * @brief Rtsa_Remote_Interface::setZoomFlag
 * @param isZoomIn
 */
void Rtsa_Remote_Interface::setZoomFlag(bool isZoomIn)
{
    mIsZoomIn = isZoomIn;
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-03-27
*/
void Rtsa_Remote_Interface::setDragFlag(bool dragFlag)
{
    mDragFlag = dragFlag;
    if(mIsZoomIn)
    {
        setZoomIn();
    }
    else
    {
        setZoomOut();
    }
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-07-29
*/
bool Rtsa_Remote_Interface::getDragFlag()
{
    return mDragFlag;
}

/**
 * @brief set zoom in
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setZoomIn()
{
    qint32 nHeight = mHeight;
    qint32 nWidth = mWidth;
    nWidth += 1;
    nHeight -= 4;
    for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
    {
        if(/*isMarkerOn(i) || */isMarkerBtnPressed || hasMarkerOn())
        {
            nHeight -= RTSA_BOTTOM_INFO_HEIGHT;
            nHeight += 2;
            break;
        }
    }
    qint32 HALF_HEIGHT = ceil((nHeight /*- 3*/)/2);
    qint32 HALF_WIDTH = ceil((nWidth - RTSA_RIGHT_INFO_WIDTH /*- 3*/)/2);

    if(mIsCurBitViewSizeChange)
    {
        mBitView[curwindowindex]->setGeometry(QRect(RTSA_PSTART_X,RTSA_PSTART_Y_BIG,nWidth - RTSA_RIGHT_INFO_WIDTH,(nHeight)));
        mBitView[curwindowindex]->setWindowRect(nWidth,nHeight);
        if((nWidth - RTSA_RIGHT_INFO_WIDTH) < RTSA_NUM_SWEEP_POINT)
        {
            mBitView[curwindowindex]->SetSpectrogramSmallPixRect(nWidth - RTSA_RIGHT_INFO_WIDTH,nHeight /*- HALF_HEIGHT*/);
            mBitView[curwindowindex]->refleshdisplay();
        }
        else
        {
            mBitView[curwindowindex]->SetSpectrogramBigPixRect(nWidth - RTSA_RIGHT_INFO_WIDTH,nHeight /*- HALF_HEIGHT*/);
            mBitView[curwindowindex]->refleshdisplay();
        }
        mBitView[curwindowindex]->refleshdisplay();
        mBitView[curwindowindex]->show();
        return;
    }


    if(globalUserVariable->gMeterParam.gConfig_Display.displayMode == RTSA_DENSITY_SPECTROGRAM)
    {
        mBitView[0]->setGeometry(QRect(RTSA_PSTART_X,RTSA_PSTART_Y_BIG,HALF_WIDTH,HALF_HEIGHT));
        mBitView[1]->setGeometry(QRect(RTSA_PSTART_X + HALF_WIDTH,RTSA_PSTART_Y_BIG,HALF_WIDTH,HALF_HEIGHT));
        mBitView[2]->setGeometry(QRect(RTSA_PSTART_X,RTSA_PSTART_Y_BIG  + HALF_HEIGHT,HALF_WIDTH,nHeight - HALF_HEIGHT));
        mBitView[3]->setGeometry(QRect(RTSA_PSTART_X + HALF_WIDTH,RTSA_PSTART_Y_BIG + HALF_HEIGHT,HALF_WIDTH,nHeight - HALF_HEIGHT));
        if((HALF_HEIGHT) < RTSA_NUM_SWEEP_POINT)
        {
            mBitView[1]->SetSpectrogramSmallPixRect(HALF_WIDTH,HALF_HEIGHT);
            mBitView[1]->refleshdisplay();
        }
        else
        {
            mBitView[1]->SetSpectrogramBigPixRect(HALF_WIDTH,HALF_HEIGHT);
            mBitView[1]->refleshdisplay();
        }
    }
    else if(globalUserVariable->gMeterParam.gConfig_Display.displayMode == RTSA_DENSITY)
    {
        mBitView[0]->setWindowRect(nWidth,nHeight);
        mBitView[1]->setWindowRect(nWidth,nHeight);
        mBitView[2]->setWindowRect(nWidth,nHeight);
        mBitView[0]->setGeometry(QRect(RTSA_PSTART_X,RTSA_PSTART_Y_BIG,HALF_WIDTH,HALF_HEIGHT));
        mBitView[1]->setGeometry(QRect(RTSA_PSTART_X + HALF_WIDTH,RTSA_PSTART_Y_BIG,HALF_WIDTH,HALF_HEIGHT));
        mBitView[2]->setGeometry(QRect(RTSA_PSTART_X,RTSA_PSTART_Y_BIG + HALF_HEIGHT,nWidth - RTSA_RIGHT_INFO_WIDTH,nHeight - HALF_HEIGHT));
        if((HALF_WIDTH) < RTSA_NUM_SWEEP_POINT)
        {
            mBitView[1]->SetSpectrogramSmallPixRect(HALF_WIDTH,HALF_HEIGHT);
            mBitView[1]->refleshdisplay();
        }
        else
        {
            mBitView[1]->SetSpectrogramBigPixRect(HALF_WIDTH,nHeight - HALF_HEIGHT);
            mBitView[1]->refleshdisplay();
        }
    }
    else if(globalUserVariable->gMeterParam.gConfig_Display.displayMode == RTSA_SPECTROGRAM)
    {
        mBitView[0]->setWindowRect(nWidth,nHeight);
        mBitView[1]->setWindowRect(nWidth,nHeight);
        mBitView[0]->setGeometry(QRect(RTSA_PSTART_X,RTSA_PSTART_Y_BIG,nWidth - RTSA_RIGHT_INFO_WIDTH,HALF_HEIGHT));
        mBitView[1]->setGeometry(QRect(RTSA_PSTART_X,RTSA_PSTART_Y_BIG + HALF_HEIGHT,nWidth - RTSA_RIGHT_INFO_WIDTH,nHeight - HALF_HEIGHT));
        if((nWidth - RTSA_RIGHT_INFO_WIDTH) < RTSA_NUM_SWEEP_POINT)
        {
            mBitView[1]->SetSpectrogramSmallPixRect(nWidth - RTSA_RIGHT_INFO_WIDTH,nHeight - HALF_HEIGHT);
            mBitView[1]->refleshdisplay();
        }
        else
        {
            mBitView[1]->SetSpectrogramBigPixRect(nWidth - RTSA_RIGHT_INFO_WIDTH,nHeight - HALF_HEIGHT);
            mBitView[1]->refleshdisplay();
        }
    }
    else if(globalUserVariable->gMeterParam.gConfig_Display.displayMode == RTSA_SPECTRUM)
    {
        mBitView[0]->setWindowRect(nWidth,nHeight);
        mBitView[0]->setGeometry(QRect(RTSA_PSTART_X,RTSA_PSTART_Y_BIG,nWidth - RTSA_RIGHT_INFO_WIDTH,(nHeight)));
    }
}

/**
 * @brief set zoom out
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setZoomOut()
{
    qint32 nHeight = mHeight;
    qint32 nWidth = mWidth;
    qint32 nLeftStartPos = 0;
    nHeight -= 4;
    //    nWidth -= 2;
    emit MarkerOn(false);
    for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
    {
        if(/*isMarkerOn(i) || */isMarkerBtnPressed || hasMarkerOn())
        {
            nHeight -= RTSA_BOTTOM_INFO_HEIGHT;
            nHeight += 2;
            emit MarkerOn(true);
            break;
        }
    }
    if(mDragFlag)
    {
        nLeftStartPos = 21;
    }
    else
    {
        nLeftStartPos = RTSA_LEFT_INFO_WIDTH + 21;
    }
    //    nHeight -= RTSA_BOTTOM_INFO_HEIGHT;

    qint32 HALF_HEIGHT = ceil((nHeight - RTSA_TOP_INFO_HEIGHT - 3)/2);
    qint32 HALF_WIDTH = ceil((nWidth  - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH)/2);

    if(mIsCurBitViewSizeChange)
    {
        mBitView[curwindowindex]->setGeometry(QRect(nLeftStartPos,RTSA_TOP_INFO_HEIGHT + 3,nWidth - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,(nHeight - RTSA_TOP_INFO_HEIGHT)));
        mBitView[curwindowindex]->setWindowRect(nWidth,nHeight);
        if(mBitView[curwindowindex]->getBitviewType() == BIT_SPECTROGRAM)
        {
            if((nWidth - RTSA_LEFT_INFO_WIDTH - RTSA_RIGHT_INFO_WIDTH) < RTSA_NUM_SWEEP_POINT)
            {
                mBitView[curwindowindex]->SetSpectrogramSmallPixRect(nWidth - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,nHeight - RTSA_TOP_INFO_HEIGHT /*- HALF_HEIGHT*/);
            }
            else
            {
                mBitView[curwindowindex]->SetSpectrogramBigPixRect(nWidth - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,nHeight - RTSA_TOP_INFO_HEIGHT /*- HALF_HEIGHT*/);
            }
        }
        mBitView[curwindowindex]->refleshdisplay();
        mBitView[curwindowindex]->show();
        return;
    }

    if(globalUserVariable->gMeterParam.gConfig_Display.displayMode == RTSA_DENSITY_SPECTROGRAM)
    {
        mBitView[0]->setWindowRect(nWidth,nHeight);
        mBitView[1]->setWindowRect(nWidth,nHeight);
        mBitView[2]->setWindowRect(nWidth,nHeight);
        mBitView[0]->setGeometry(QRect(nLeftStartPos,RTSA_TOP_INFO_HEIGHT + 3,HALF_WIDTH,HALF_HEIGHT));
        mBitView[1]->setGeometry(QRect(nLeftStartPos + HALF_WIDTH,RTSA_TOP_INFO_HEIGHT + 3,HALF_WIDTH,HALF_HEIGHT));
        mBitView[2]->setGeometry(QRect(nLeftStartPos,RTSA_TOP_INFO_HEIGHT + 3 + HALF_HEIGHT,HALF_WIDTH,nHeight - RTSA_TOP_INFO_HEIGHT - HALF_HEIGHT));
        mBitView[3]->setGeometry(QRect(nLeftStartPos + HALF_WIDTH,RTSA_TOP_INFO_HEIGHT + 3 + HALF_HEIGHT,HALF_WIDTH,nHeight - RTSA_TOP_INFO_HEIGHT - HALF_HEIGHT));
        if((HALF_WIDTH) < RTSA_NUM_SWEEP_POINT)
        {
            mBitView[1]->SetSpectrogramSmallPixRect(HALF_WIDTH,HALF_HEIGHT);
            mBitView[1]->refleshdisplay();
        }
        else
        {
            mBitView[1]->SetSpectrogramBigPixRect(nWidth - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,nHeight - RTSA_TOP_INFO_HEIGHT - HALF_HEIGHT);
            mBitView[1]->refleshdisplay();
        }
    }
    else if(globalUserVariable->gMeterParam.gConfig_Display.displayMode == RTSA_DENSITY)
    {
        mBitView[0]->setWindowRect(nWidth,nHeight);
        mBitView[1]->setWindowRect(nWidth,nHeight);
        mBitView[2]->setWindowRect(nWidth,nHeight);
        mBitView[0]->setGeometry(QRect(nLeftStartPos,RTSA_TOP_INFO_HEIGHT + 3,HALF_WIDTH,HALF_HEIGHT));
        mBitView[1]->setGeometry(QRect(nLeftStartPos + HALF_WIDTH,RTSA_TOP_INFO_HEIGHT + 3,HALF_WIDTH,HALF_HEIGHT));
        mBitView[2]->setGeometry(QRect(nLeftStartPos,RTSA_TOP_INFO_HEIGHT + 3 + HALF_HEIGHT,nWidth - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,nHeight - RTSA_TOP_INFO_HEIGHT - HALF_HEIGHT));
        if((HALF_WIDTH) < RTSA_NUM_SWEEP_POINT)
        {
            mBitView[1]->SetSpectrogramSmallPixRect(HALF_WIDTH,HALF_HEIGHT);
            mBitView[1]->refleshdisplay();
        }
        else
        {
            mBitView[1]->SetSpectrogramBigPixRect(nWidth - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,nHeight - RTSA_TOP_INFO_HEIGHT - HALF_HEIGHT);
            mBitView[1]->refleshdisplay();
        }
    }
    else if(globalUserVariable->gMeterParam.gConfig_Display.displayMode == RTSA_SPECTROGRAM)
    {
        mBitView[0]->setWindowRect(nWidth,nHeight);
        mBitView[1]->setWindowRect(nWidth,nHeight);
        mBitView[0]->setGeometry(QRect(nLeftStartPos,RTSA_TOP_INFO_HEIGHT + 3,nWidth  - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,HALF_HEIGHT));
        mBitView[1]->setGeometry(QRect(nLeftStartPos,RTSA_TOP_INFO_HEIGHT + 3 + HALF_HEIGHT,nWidth - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,nHeight - RTSA_TOP_INFO_HEIGHT - HALF_HEIGHT));
        if((nWidth - RTSA_LEFT_INFO_WIDTH - RTSA_RIGHT_INFO_WIDTH) < RTSA_NUM_SWEEP_POINT)
        {
            mBitView[1]->SetSpectrogramSmallPixRect(nWidth - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,nHeight - RTSA_TOP_INFO_HEIGHT - HALF_HEIGHT);
            mBitView[1]->refleshdisplay();
        }
        else
        {
            mBitView[1]->SetSpectrogramBigPixRect(nWidth - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,nHeight - RTSA_TOP_INFO_HEIGHT - HALF_HEIGHT);
            mBitView[1]->refleshdisplay();
        }
    }
    else if(globalUserVariable->gMeterParam.gConfig_Display.displayMode == RTSA_SPECTRUM)
    {
        mBitView[0]->setWindowRect(nWidth,nHeight);
        mBitView[0]->setGeometry(QRect(nLeftStartPos,RTSA_TOP_INFO_HEIGHT + 3,nWidth - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,(nHeight - RTSA_TOP_INFO_HEIGHT)));
    }
}

/**
* @brief set shift key down flag
* @param[in] isEnable
* @Author Albert
* @date 2019-03-27
*/
void Rtsa_Remote_Interface::setShiftKeyEnable(bool isEnable)
{
    mIsShiftKeyEnable = isEnable;
    return;
}

/**
* @brief if shift key down flag
* @param none
* @Author Albert
* @date 2019-03-27
*/
bool Rtsa_Remote_Interface::isShiftKeyEnable()
{
    return mIsShiftKeyEnable;
}

/**
 * @brief change bitview size
 * @note
 * @author Albert
 * @since {2018-12-24}
*/
void Rtsa_Remote_Interface::changeSize(qint32 width, qint32 height)
{
    mWidth = width + 2;
    mHeight = height;
    return;
}

/**
 * @brief draw lines and spectrogram
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::Draw()
{
    if(globalUserVariable->gAutoAttenTrack == RTSA_ON)
    {
        if(AutoAttenTrack())
            return;
    }
    drawTrace();
    if(globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].markerPeakTraceOn)
    {
        setMarkerToPeak();
    }
    for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
    {
        if(isMarkerOn(i))
        {
            emit BitViewMakerDraw(i,true);
        }
    }
    if(IsAvgOn(getCurTrace()))
    {
        emit RedrawInfoShow(LABEL_AVERAGE);
    }
    return;
}


/**
* @brief
* @param
* @Author Albert
* @date 2019-07-30
*  true---- suspend draw  false ---- start draw
*/
void Rtsa_Remote_Interface::DrawFlag(bool isSuspend)
{
    globalUserVariable->gSuspendDrawFlag = isSuspend;
    return;
}

bool Rtsa_Remote_Interface::getDrawFlag()
{
    return globalUserVariable->gSuspendDrawFlag;
}

/**
 * @brief Rtsa_Remote_Interface::getAdjustPersistenceTime
 * @param time
 * @return
 */
QString Rtsa_Remote_Interface::getAdjustTimeStr(qreal time)
{
    //    qreal value = time;
    QString strVal;
    QString strUnit;
    if(time >= RTSA_S)
    {
        time /= RTSA_S;
        strVal = QString::number(time,'f',3);
        strUnit = QString(" s");
    }
    else if(time >= RTSA_MS)
    {
        time /= RTSA_MS;
        strVal = QString::number(time,'f',3);
        strUnit = QString(" ms");
    }
    else if(time >= RTSA_US)
    {
        time /= RTSA_US;
        strVal = QString::number(time,'f',3);
        strUnit = QString(" us");
    }
    else
    {
        time *= RTSA_NS;
        strVal = QString::number(time,'f',3);
        strUnit = QString(" ns");
    }
    strVal += strUnit;
    return strVal;
}

/**
* @brief  getCurBitviewType
* @param
* @Author Albert
* @date 2019-04-26
*/
qint32 Rtsa_Remote_Interface::getCurBitviewType()
{
    qint32 type = RTSA_SPECTRUM;
    type = mBitView[curwindowindex]->getBitviewType();
    return type;
}


/**
 * @brief Rtsa_Remote_Interface::refreshMainDisplay
 */
void Rtsa_Remote_Interface::refreshMainDisplay()
{
    //when change param in single swp, trace data should set to the down below
    if(IsSingleSweep() && !mSingleFinished)
    {
        updateTraceData(mLowData,RTSA_NUM_SWEEP_POINT);
        drawTrace();
    }
    mSingleFinished = false;
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-09-03
*/
void Rtsa_Remote_Interface::refreshAllBitView()
{
    for(qint32 i = 0; i < RTSA_BITVIEWNUM;i++)
    {
        mBitView[i]->refleshdisplay();
    }
    return;
}


/**
 * @brief atten auto track
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool Rtsa_Remote_Interface::AutoAttenTrack()
{
    qreal AMax = 0.0;
    AMax = mBitView[curwindowindex]->MarkerToPeak();

    //  ??  mBitView[curwindowindex]->refleshmarker();
    //    ??mBitView[curwindowindex]->refleshdisplay();
    //   ?? emit BitViewMakerMoved(true);

    if(fabs(AMax - globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel) - 10. >0.)
    {
        globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel = AMax + 10.;
        setRefLevel(globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel);
        resetAvgCnt();
        return true;
    }
    return false;
}
/**
 * @brief set auto atten track on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setAutoAttenTrack(bool isOn)
{
    globalUserVariable->gAutoAttenTrack = isOn;
}

/**
 * @brief get auto atten track on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool Rtsa_Remote_Interface::IsAutoAttenTrackOn()
{
    return globalUserVariable->gAutoAttenTrack;
}

/**
* @brief ReDrawLeftInfo
* @param none
* @Author Albert
* @date 2019-03-27
*/
void Rtsa_Remote_Interface::ReDrawLeftInfo()
{
    for(qint32 i = LABEL_MODE; i < LABEL_END; i++)
    {
        emit RedrawInfoShow(i);
    }
    return;
}

/**
 * @brief System Display set
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setSystemDisplay(qint32 sysDisplay)
{
    for(int i=0;i<RTSA_BITVIEWNUM;i++)
    {
        mBitView[i]->setSystemAttribute(DISPLAYMODE,sysDisplay);
        mBitView[i]->refleshdisplay();
    }
}/**
 * @brief refresh bitview bottom message
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::showBitViewBottomMsg(qint32 bottomDisplay)
{
    for(int i=0;i< RTSA_BITVIEWNUM;i++)
    {
        mBitView[i]->showBottomWordsMsg(bottomDisplay);
        mBitView[i]->refleshdisplay();
    }
    return;
}

/**
 * @brief select current bieview
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setCurBitView(qint32 index)
{
    setcurrentview(index);
    return;
}

/**
 * @brief update render trace data
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::updateTraceData(qreal *pTraceData, qint32 TraceNum)
{
    memcpy(gOriginalTrace,pTraceData,TraceNum * sizeof(qreal));
    return;
}

void Rtsa_Remote_Interface::updateDpxData(quint32 *pTraceData, qint32 TraceNum)
{
    gDpxData = pTraceData;
    gDpxDataNum = TraceNum;
    return;
}

/**
 * @brief update data to bitview
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::updateGeneralDataToBitview(qint32 datatype)
{
    switch (datatype) {
    case RTSA_FREQ_INFO:
        for(qint32 i=0;i<RTSA_BITVIEWNUM;i++)
        {
            mBitView[i]->setFreqOffset(globalUserVariable->gMeterParam.gConfig_FreqSpan.gOffsetFreq);
            mBitView[i]->setFreqAttribute(BIT_START_FREQ,globalUserVariable->gMeterParam.gConfig_FreqSpan.gStartFreq);
            mBitView[i]->setFreqAttribute(BIT_STOP_FREQ,globalUserVariable->gMeterParam.gConfig_FreqSpan.gStopFreq);
            mBitView[i]->setFreqAttribute(BIT_CENTER_FREQ,globalUserVariable->gMeterParam.gConfig_FreqSpan.gCenterFreq);
            mBitView[i]->setFreqAttribute(BIT_SPAN_FREQ,globalUserVariable->gMeterParam.gConfig_FreqSpan.gSpanFreq);
            mBitView[i]->showBottomWordsMsg(bitviewbottomdisplay);
            mBitView[i]->markerUpdateByFreq();
            mBitView[i]->refleshdisplay();
        }
        break;
    case RTSA_RBW_INFO:
        for(qint32 i=0;i<RTSA_BITVIEWNUM;i++)
        {
            mBitView[i]->setFreqAttribute(BIT_RBW_FREQ,globalUserVariable->gMeterParam.gConfig_BW.rbw);
            mBitView[i]->showBottomWordsMsg(bitviewbottomdisplay);
            mBitView[i]->refleshdisplay();
        }
        break;
    case RTSA_REF_LVL:
        for(qint32 i=0;i<RTSA_BITVIEWNUM;i++)
        {
            //            mBitView[i]->setAmptdUnit(globalUserVariable->gMeterParam.gConfig_Amplitude.units[curwindowindex]);
            mBitView[i]->showTopWordsMsg(BV_TOP_APMTINFO);
            //Tony 1022 & 1024
            mBitView[i]->setAmptdAttribute(BIT_AMPTD_REF,globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel /*+ globalUserVariable->gMeterParam.gConfig_Amplitude.refOffset[curwindowindex]*/);
            //            globalUserVariable->gMeterParam.gConfig_Amplitude.refOffset[curwindowindex] = mBitView[i]->getAmptdAttribute(BIT_AMPTD_OFFSET);
            mBitView[i]->setAmptdAttribute(BIT_AMPTD_OFFSET,globalUserVariable->gMeterParam.gConfig_Amplitude.refOffset[curwindowindex]);
            mBitView[i]->showTopWordsMsg(bitviewtopdisplay);
            mBitView[i]->refleshdisplay();
        }
        break;
    case RTSA_SYS_INFO:
        for(qint32 i=0;i<RTSA_BITVIEWNUM;i++)
        {
            mBitView[i]->setSystemAttribute(RUNNINGSTATE,globalUserVariable->gMeterParam.gConfig_Sweep.sweepType);
            mBitView[i]->refleshdisplay();
        }
        break;
    case RTSA_ACQ_INFO:
        for(qint32 i=0;i<RTSA_BITVIEWNUM;i++)
        {
            mBitView[i]->setAcqTime(globalUserVariable->gMeterParam.gConfig_Sweep.acqTimeVal);
            mBitView[i]->showBottomWordsMsg(bitviewbottomdisplay);
            mBitView[i]->refleshdisplay();
        }
        break;
    case RTSA_FREQ_OFFSET:
        for(qint32 i=0;i<RTSA_BITVIEWNUM;i++)
        {
            mBitView[i]->setFreqOffset(globalUserVariable->gMeterParam.gConfig_FreqSpan.gOffsetFreq);
            //            mBitView[i]->setFreqAttribute(BIT_START_FREQ,globalUserVariable->gMeterParam.gConfig_FreqSpan.gStartFreq);
            //            mBitView[i]->setFreqAttribute(BIT_STOP_FREQ,globalUserVariable->gMeterParam.gConfig_FreqSpan.gStopFreq);
            //            mBitView[i]->setFreqAttribute(BIT_CENTER_FREQ,globalUserVariable->gMeterParam.gConfig_FreqSpan.gCenterFreq);
            //            mBitView[i]->setFreqAttribute(BIT_SPAN_FREQ,globalUserVariable->gMeterParam.gConfig_FreqSpan.gSpanFreq);
            mBitView[i]->showBottomWordsMsg(bitviewbottomdisplay);
            mBitView[i]->markerUpdateByFreq();
            mBitView[i]->refleshdisplay();
        }
        break;
    case RTSA_REF_OFFSET:
        for(qint32 i=0;i<RTSA_BITVIEWNUM;i++)
        {
            //            mBitView[i]->setAmptdUnit(globalUserVariable->gMeterParam.gConfig_Amplitude.units[curwindowindex]);
            //            mBitView[i]->showTopWordsMsg(BV_TOP_APMTINFO);
            mBitView[i]->setAmptdAttribute(BIT_AMPTD_OFFSET,globalUserVariable->gMeterParam.gConfig_Amplitude.refOffset[curwindowindex]);
            mBitView[i]->showTopWordsMsg(bitviewtopdisplay);
            mBitView[i]->refleshdisplay();
        }
        break;
    default:
        break;
    }
}

/**
 * @brief update data from bitview
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::updateDateFromBitview()
{
    globalUserVariable->gMeterParam.gConfig_Amplitude.units[curwindowindex] = mBitView[curwindowindex]->getAmptUnit();
    globalUserVariable->gMeterParam.gConfig_Amplitude.refOffset[curwindowindex] = mBitView[curwindowindex]->getAmptdAttribute(BIT_AMPTD_OFFSET);
    globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex]  = mBitView[curwindowindex]->getAmptdAttribute(BIT_AMPTD_DIV);

    //    pLimit.setCurLimit(mBitView[curwindowindex]->getLimitAttribute(BIT_LIMIT_INDEX));
    //    pLimit.setLimitTestOn(mBitView[curwindowindex]->getLimitAttribute(BIT_LIMIT_TEST));
    //    for(int i=0;i<BIT_LIMIT_TOTAL_CNT;i++)
    //    {
    //        pLimit.setCurLimitOn(i,mBitView[curwindowindex]->getLimitAttribute(BIT_LIMIT_VIEW,i));
    //        pLimit.setMarginOn(i,mBitView[curwindowindex]->getLimitAttribute(BIT_LIMIT_MARGIN,i));
    //        pLimit.setMargin(i,mBitView[curwindowindex]->getLimitAttributeEX(BIT_LIMIT_MARGIN_VALUE,i));
    //        pLimit.setLimitType(i,mBitView[curwindowindex]->getLimitAttribute(BIT_LIMIT_TYPE,i));
    //    }

    setCurTrace(mBitView[curwindowindex]->getTraceAttribute(0,BIT_TRACE_INDEX));
    //    for(int i=0;i<SUPPORTTRACENUM;i++)
    //    {
    //        pTrace.setTraceType(i,mBitView[curwindowindex]->getTraceAttribute(i,BIT_TRACE_TYPE_ATTR));
    //        pTrace.setAvgOn(i,mBitView[curwindowindex]->getTraceAttribute(i,BIT_AVAG_ATTR));
    //        pTrace.setAvgNum(i,mBitView[curwindowindex]->getTraceAttribute(i,BIT_AVAG_NUM_ATTR));
    //    }
    //    pMarker.setCurMarkerID(mBitView[curwindowindex]->getMarkerAttribute(BIT_MARKER_INDEX));
    //    for(int i=0;i<BIT_LIMIT_TOTAL_CNT;i++)
    //    {
    //        pMarker.setMarkerType(i,mBitView[curwindowindex]->getMarkerAttribute(BIT_MARKER_DISPLAY,i));
    //        pMarker.setMarkerOn(i,mBitView[curwindowindex]->getMarkerAttribute(BIT_MARKER_VISIABLE,i));
    //        pMarker.setMarkerNoiseOn(i,mBitView[curwindowindex]->getMarkerAttribute(BIT_MARKER_NOISE,i));
    //    }
    //    pMarker.setMarkerDisplay(mBitView[curwindowindex]->getMarkerAttribute(BIT_MARKER_DISPLAY));
    return;
}


/**
* @brief
* @param
* @Author Albert
* @date 2019-09-04
*/
void Rtsa_Remote_Interface::setBitViewFileLoadFlag(bool isFileload)
{
    for(qint32 i = 0; i < RTSA_BITVIEWNUM; i++)
    {
        if(mBitView[i]->getBitviewType() == BIT_SPECTROGRAM)
            mBitView[i]->refreshSepectrogramRect();
        mBitView[i]->setFileLoadDoneFlag(isFileload);
    }
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-09-05
*/
void Rtsa_Remote_Interface::drawFileLoadSpectrogram(qreal *pData)
{
    for(qint32 i = 0; i < RTSA_BITVIEWNUM; i++)
    {
        if(mBitView[i]->getBitviewType() == BIT_SPECTROGRAM)
        {
            mBitView[i]->renderFileSpectrogram(pData);
            //            mBitView[i]->refleshdisplay();
        }
    }
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-10-09
*/
void Rtsa_Remote_Interface::GetRawData(qreal* dest)
{
    getRawTraceData(dest);
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-10-09
*/
void Rtsa_Remote_Interface::GetDrawData(char* dest)
{
    //    memcpy(dest,globalUserVariable->gTraceMeasureVal,sizeof(qreal)*NUM_SWEEP_POINT*TRACE_CNT_TOTAL);
    return;
}
void Rtsa_Remote_Interface::getRawTraceData(qreal* dest)
{
    memcpy((char*)dest,gOriginalTrace,sizeof(qreal)*RTSA_NUM_SWEEP_POINT);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-10-09
*/
void Rtsa_Remote_Interface::GetAllTraceData(char *dest)
{
    //    memcpy(dest,globalUserVariable->gOriginalMeasureVal,sizeof(qreal)*NUM_SWEEP_POINT);
    //    memcpy((char*)dest + sizeof(qreal)*NUM_SWEEP_POINT,globalUserVariable->gTraceMeasureVal,sizeof(qreal)*NUM_SWEEP_POINT*TRACE_CNT_TOTAL);

    for(qint32 i = RTSA_TR1; i <= RTSA_TR6; i++)
    {
        mBitView[curwindowindex]->getTraceRenderData(gTraceData,RTSA_TRACE_DATA_NUM,i);
        memcpy((char*)dest + i * sizeof(qreal)*RTSA_NUM_SWEEP_POINT,gTraceData,sizeof(qreal)*RTSA_NUM_SWEEP_POINT);
    }
    //    memcpy((char*)dest + sizeof(qreal)*RTSA_NUM_SWEEP_POINT,pData,sizeof(qreal)*RTSA_NUM_SWEEP_POINT);
    return;
}


/**
* @brief saveDisplayParam
* @param [in] display
* @Author Albert
* @date 2019-04-15
*/
void Rtsa_Remote_Interface::saveDisplayParam(qint32 display)
{
    switch(display)
    {
    case RTSA_SPECTRUM:

        break;
    case RTSA_SPECTROGRAM:
        break;
    case RTSA_DENSITY:
        break;
    case RTSA_DENSITY_SPECTROGRAM:
        break;
    default:
        break;
    }
    return;
}

/**
* @brief  loadDisplayParam
* @param [in] display
* @Author Albert
* @date 2019-04-15
*/
void Rtsa_Remote_Interface::loadDisplayParam(qint32 display)
{
    switch(display)
    {
    case RTSA_SPECTRUM:
        break;
    case RTSA_SPECTROGRAM:
        break;
    case RTSA_DENSITY:
        break;
    case RTSA_DENSITY_SPECTROGRAM:
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
* @date 2019-06-14
*/
void Rtsa_Remote_Interface::setBitViewParam(qint32 measType)
{
    switch(measType)
    {
    case RTSA_SPECTRUM:
        mBitView[0]->setBitviewType(RTSA_SPECTRUM);
        mBitView[0]->setSystemAttribute(WINDOWTYPE,BIT_SINGLEWINDOW);
        globalUserVariable->gMeterParam.gConfig_Display.displayMode = RTSA_SPECTRUM;
        wintotalnum = 1;
        setcurrentview(0);
        mBitView[0]->show();
        mBitView[0]->refleshdisplay();
        break;
    case RTSA_SPECTROGRAM:
        mBitView[0]->setBitviewType(RTSA_SPECTRUM);
        mBitView[1]->setBitviewType(RTSA_SPECTROGRAM);
        mBitView[1]->initSpectrogramCacheDataArray(gSpectrogramCacheData[0]);
        globalUserVariable->gMeterParam.gConfig_Display.displayMode = RTSA_SPECTROGRAM;
        mBitView[0]->setSystemAttribute(WINDOWTYPE,BIT_MULTIWINDOW);
        mBitView[1]->setSystemAttribute(WINDOWTYPE,BIT_MULTIWINDOW);
        wintotalnum = 2;
        curwindowindex = 1;
        setcurrentview(0);
        mBitView[0]->show();
        mBitView[1]->show();
        mBitView[0]->refleshdisplay();
        mBitView[1]->refleshdisplay();
        break;
    case RTSA_DENSITY:
        mBitView[0]->setBitviewType(RTSA_SPECTRUM);
        mBitView[1]->setBitviewType(RTSA_SPECTROGRAM);
        mBitView[2]->setBitviewType(RTSA_DENSITY);
        mBitView[1]->initSpectrogramCacheDataArray(gSpectrogramCacheData[0]);
        globalUserVariable->gMeterParam.gConfig_Display.displayMode = RTSA_DENSITY;
        mBitView[0]->setSystemAttribute(WINDOWTYPE,BIT_MULTIWINDOW);
        mBitView[1]->setSystemAttribute(WINDOWTYPE,BIT_MULTIWINDOW);
        mBitView[2]->setSystemAttribute(WINDOWTYPE,BIT_MULTIWINDOW);
        curwindowindex = 2;
        wintotalnum = 3;
        setcurrentview(0);
        mBitView[0]->show();
        mBitView[1]->show();
        mBitView[2]->show();
        mBitView[0]->refleshdisplay();
        mBitView[1]->refleshdisplay();
        mBitView[2]->refleshdisplay();
        break;
    case RTSA_DENSITY_SPECTROGRAM:
        mBitView[0]->setBitviewType(RTSA_SPECTRUM);
        mBitView[1]->setBitviewType(RTSA_SPECTROGRAM);
        mBitView[2]->setBitviewType(RTSA_SPECTRUM);
        mBitView[3]->setBitviewType(RTSA_SPECTRUM);
        mBitView[1]->initSpectrogramCacheDataArray(gSpectrogramCacheData[0]);

        globalUserVariable->gMeterParam.gConfig_Display.displayMode = RTSA_DENSITY_SPECTROGRAM;
        mBitView[0]->setSystemAttribute(WINDOWTYPE,BIT_MULTIWINDOW);
        mBitView[1]->setSystemAttribute(WINDOWTYPE,BIT_MULTIWINDOW);
        mBitView[2]->setSystemAttribute(WINDOWTYPE,BIT_MULTIWINDOW);
        mBitView[3]->setSystemAttribute(WINDOWTYPE,BIT_MULTIWINDOW);
        curwindowindex = 3;
        wintotalnum = 4;
        setcurrentview(0);
        mBitView[0]->show();
        mBitView[1]->show();
        mBitView[2]->show();
        mBitView[3]->show();
        mBitView[0]->refleshdisplay();
        mBitView[1]->refleshdisplay();
        mBitView[2]->refleshdisplay();
        mBitView[3]->refleshdisplay();
        //        globalUserVariable->openDpxDevice();
        break;
    }
    return;
}

/**
* @brief getGlobalUserVariable
* @param none
* @Author Albert
* @date 2019-04-15
*/
RtSa_User_Variable* Rtsa_Remote_Interface::getGlobalUserVariable()
{
    return globalUserVariable;
}

uchar* Rtsa_Remote_Interface::GetDensityData(qint32 dataNum)
{
    uchar* pData;
    for(qint32 i = 0; i < RTSA_BITVIEWNUM; i++)
    {
        if(mBitView[i]->getBitviewType() == BIT_DENSITY)
        {
            pData = mBitView[i]->getDensityData(dataNum);
            break;
        }
        else
        {
            pData = mBitView[i]->getDensityData(dataNum);
        }
    }
    return pData;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-06-14
*/
void Rtsa_Remote_Interface::PltCurAnaMode(qint32 imod)
{
    globalUserVariable->startMode = imod;
    return;
}

/**
* @brief PltSaveConditions
* @param itype file type 0 means default.cond 1 means last.cond 2 means user.cond
* @Author Albert
* @date 2019-05-21
*/
qint32 Rtsa_Remote_Interface::PltSaveConditions(qint32 itype)
{
    qint32 ret = -1;
    switch (itype) {
    case STATE_DEFAULT_FILE:
        //        savePresState();
        initDefaultParam(mStateParam);
        ret = saveState(RTSA_DEFAULT_COND);
        break;
    case STATE_LAST_FILE:
        //        savePresState();
        initStateParam(mStateParam);
        ret = saveState(RTSA_LAST_COND);
        break;
    case STATE_USER_FILE:
        //        savePresState();
        initStateParam(mStateParam);
        ret = saveState(RTSA_USER_COND);
        break;
    default:
        break;
    }
    return ret;
}

/**
* @brief PltLoadConditions
* @param itype file type 0 means default.cond 1 means last.cond 2 means user.cond
* @Author Albert
* @date 2019-05-21
*/
qint32 Rtsa_Remote_Interface::PltLoadConditions(qint32 itype)
{
    qint32 ret = -1;
    switch (itype) {
    case STATE_DEFAULT_FILE:
        //        loadPresState();
        ret = loadState(RTSA_DEFAULT_COND);
        break;
    case STATE_LAST_FILE:
        //        loadPresState();
        ret = loadState(RTSA_LAST_COND);
        break;
    case STATE_USER_FILE:
        //        loadPresState();
        ret = loadState(RTSA_USER_COND);
        break;
    default:
        ret = loadState(RTSA_DEFAULT_COND);
        break;
    }
    //    globalUserVariable->gfileType = itype;
    return ret;
}

qint32 Rtsa_Remote_Interface::PltSavePres(qint32 itype)
{
    qint32 iback = -1;
    globalUserVariable->gfileType = itype;
    iback = savePresState();
    return iback;
}

void Rtsa_Remote_Interface::initDefaultParam(_RTSA_FILE_SAVE_LOAD_VARIABLE_ &stateParam)
{
    stateParam.gConfig_Display.displayMode = RTSA_SPECTRUM;
    stateParam.gConfig_Display.bitviewStatus[0] = RTSA_SPECTRUM;
    stateParam.gConfig_Display.bitviewStatus[1] = BIT_NONE;
    stateParam.gConfig_Display.bitviewStatus[2] = BIT_NONE;
    stateParam.gConfig_Display.bitviewStatus[3] = BIT_NONE;

    stateParam.gConfig_Display.curWindowIndex = 0;
    //Freq
    stateParam.gConfig_FreqSpan.gCenterFreq = 5050000000LL;
    stateParam.gConfig_FreqSpan.gStartFreq = 5000000000LL;
    stateParam.gConfig_FreqSpan.gStopFreq = 5100000000LL;
    stateParam.gConfig_FreqSpan.gSpanFreq = 100000000LL;
    stateParam.gConfig_FreqSpan.gStepFreq = 1000000LL;
    stateParam.gConfig_FreqSpan.gOffsetFreq = 0;
    stateParam.gConfig_FreqSpan.channelStd = RTSA_CDMA - 1;
    stateParam.gConfig_FreqSpan.channelSelID = 0;
    stateParam.gConfig_FreqSpan.channelNumber = 0;
    stateParam.gConfig_FreqSpan.channelStep = mRTSA_ChStand[RTSA_CDMA].ChStep;
    stateParam.gConfig_FreqSpan.channelType = RTSA_UPLINK;

    //amplitude
    stateParam.gConfig_Amplitude.refLevel = -10.0;
    stateParam.gConfig_Amplitude.attenAuto = RTSA_AUTO;
    stateParam.gConfig_Amplitude.attenVal = 0.0;
    for(qint32 i = 0 ; i < RTSA_BITVIEWNUM ; i++)
    {
        stateParam.gConfig_Amplitude.scaleDiv[i] = 10;
        stateParam.gConfig_Amplitude.refOffset[i] = 0;
        stateParam.gConfig_Amplitude.units[i] = RTSA_DBM;
    }
    stateParam.gConfig_Amplitude.preAmpStatus = RTSA_OFF;

    //sweep
    stateParam.gConfig_Sweep.sweepType = RTSA_CONT;    stateParam.gConfig_Sweep.autoAcqtime = RTSA_AUTO;
    stateParam.gConfig_Sweep.acqTimeVal = RTSA_ACQ_DEFAULT_TIME;
    stateParam.gConfig_Sweep.autoPersistence = RTSA_FINITE;
    stateParam.gConfig_Sweep.persistenceVal = RTSA_PERSISTENCE_TIME;
    stateParam.gConfig_Sweep.highDensity = 100;
    stateParam.gConfig_Sweep.lowDensity = 0;
    stateParam.gConfig_Sweep.curveNum = 0;

    //BW
    stateParam.gConfig_BW.autoRbw = RTSA_ON;
    stateParam.gConfig_BW.rbw = RTSA_RbwManualList[0][0][6];
    stateParam.gConfig_BW.rbwIndex = RTSA_RBW5;
    stateParam.gConfig_BW.fftFilter = RTSA_KAISER;

    //Trigger
    stateParam.gConfig_Trigger.triggerType = RTSA_TRIGGER_FREE_RUN;
    //Video trigger
    stateParam.gConfig_Trigger.triggerVideoSlope = 0;
    stateParam.gConfig_Trigger.triggerVideoLevel = -20.0;
    stateParam.gConfig_Trigger.triggerVideoDelayStatus = 0;
    stateParam.gConfig_Trigger.triggerVideoDelay = 0;

    //extern trigger
    stateParam.gConfig_Trigger.triggerExternSlope = 0;
    stateParam.gConfig_Trigger.triggerExternLevel = -20.0;
    stateParam.gConfig_Trigger.triggerExternDelayStatus = 0;
    stateParam.gConfig_Trigger.triggerExternDelay = 0;

    //period
    stateParam.gConfig_Trigger.triggerPeriodDelay = 0;
    stateParam.gConfig_Trigger.triggerPeriodDelayStatus = 0;
    stateParam.gConfig_Trigger.triggerPeriodTime = RTSA_HOLDOFF_TIME_MIN;

    //RF Burst
    stateParam.gConfig_Trigger.triggerRFSlope = 0;
    stateParam.gConfig_Trigger.triggerRFLevel = -20.0;
    stateParam.gConfig_Trigger.triggerRFDelayStatus = 0;
    stateParam.gConfig_Trigger.triggerRFDelay = 0;


    stateParam.gConfig_Trigger.triggerVideoHoldOff = RTSA_HOLDOFF_TIME_MIN;
    stateParam.gConfig_Trigger.triggerRFBurstHoldOff = RTSA_HOLDOFF_TIME_MIN;
    stateParam.gConfig_Trigger.triggerExternHoldOff = RTSA_HOLDOFF_TIME_MIN;
    stateParam.gConfig_Trigger.triggerFMTHoldOff = RTSA_HOLDOFF_TIME_MIN;

    //    stateParam.gConfig_Trigger.triggerSlope = 0;
    //    stateParam.gConfig_Trigger.maskType = globalUserVariable->gMaskType;
    //    stateParam.gConfig_Trigger.triggerCriteria = globalUserVariable->gMaskType;

    stateParam.gConfig_Trigger.fmtnumber = 0;
    for(qint32 i = 0; i < stateParam.gConfig_Trigger.fmtnumber; i++)
    {
        stateParam.gConfig_Trigger.fmtFreq[i] = 0;
        stateParam.gConfig_Trigger.fmtAmpt[i] = 0;
    }

    //Trace
    for(qint32 j = 0; j < RTSA_BITVIEWNUM; j++)
    {
        stateParam.gConfig_Trace.curTraceID[j] = RTSA_TR1;
        for(qint32 i = 0; i < RTSA_NUM_TRACE; i++)
        {
            stateParam.gConfig_Trace.Rtsa_Config_Trace[j][i].traceType = RTSA_TRACE_OFF;
            stateParam.gConfig_Trace.Rtsa_Config_Trace[j][i].averageOn = RTSA_OFF;
            stateParam.gConfig_Trace.Rtsa_Config_Trace[j][i].averageCount = 10;
        }
        stateParam.gConfig_Trace.Rtsa_Config_Trace[j][0].traceType = RTSA_CLEAR_WRITE;
    }
    stateParam.gConfig_Trace.detectorType = RTSA_DEC_PEAK;

    stateParam.gConfig_Trace.Rtsa_Config_Trace[0][RTSA_TR1].traceType = RTSA_CLEAR_WRITE;
    //Marker
    for(qint32 j = 0; j < RTSA_BITVIEWNUM; j++)
    {
        stateParam.gConfig_Marker[j].curmarkerID = RTSA_M1;
        stateParam.gConfig_Marker[j].markerPeakTraceOn = RTSA_OFF;
        for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
        {
            stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].markerView = RTSA_OFF;
            stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].markerType = RTSA_REF;
            stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].markerNoiseOn = RTSA_OFF;
            stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].gMarkerRefFreq = stateParam.gConfig_FreqSpan.gCenterFreq;
            stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].gMarkerRefAmpt = 0;
            stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].gMarkerNormalPosY = 0;
        }

    }

    //Limit
    for(qint32 j = 0; j < RTSA_BITVIEWNUM; j++)
    {
        stateParam.gConfig_Limit[j].limitID = RTSA_LIMIT1;
        stateParam.gConfig_Limit[j].limitTest = RTSA_OFF;
        for(qint32 i = 0; i < RTSA_LIMIT_TOTAL; i++)
        {
            stateParam.gConfig_Limit[j].limitOn[i] = RTSA_LIMIT_OFF;
            stateParam.gConfig_Limit[j].limitEdgeOn[i] = RTSA_OFF;
            stateParam.gConfig_Limit[j].limitEdgeVal[i] = 0;
            stateParam.gConfig_Limit[j].limitType[i] = RTSA_UPPER;
            stateParam.gConfig_Limit[j].limitEditNum[i] = 0;
            stateParam.gConfig_Limit[j].limitCurEditIndex[i] = 0;
        }
    }
    return;
}


/**
* @brief initStateParam
* @param init state struct
* @Author Albert
* @date 2019-05-22
*/
void Rtsa_Remote_Interface::initStateParam(_RTSA_FILE_SAVE_LOAD_VARIABLE_ &stateParam)
{
    //Albert 19/06/03  when save state, should consider every bitview

    stateParam.gConfig_Display.displayMode = getDisplay();
    for(qint32 i = 0;i < RTSA_BITVIEWNUM; i++)
    {
        stateParam.gConfig_Display.bitviewStatus[i] = mBitView[i]->getBitviewType();
    }
    stateParam.gConfig_Display.curWindowIndex = curwindowindex;
    //Freq
    stateParam.gConfig_FreqSpan.gCenterFreq = globalUserVariable->gMeterParam.gConfig_FreqSpan.gCenterFreq;
    stateParam.gConfig_FreqSpan.gStartFreq = globalUserVariable->gMeterParam.gConfig_FreqSpan.gStartFreq;
    stateParam.gConfig_FreqSpan.gStopFreq = globalUserVariable->gMeterParam.gConfig_FreqSpan.gStopFreq;
    stateParam.gConfig_FreqSpan.gSpanFreq = globalUserVariable->gMeterParam.gConfig_FreqSpan.gSpanFreq;
    stateParam.gConfig_FreqSpan.gStepFreq = globalUserVariable->gMeterParam.gConfig_FreqSpan.gStepFreq;
    stateParam.gConfig_FreqSpan.gOffsetFreq = globalUserVariable->gMeterParam.gConfig_FreqSpan.gOffsetFreq;
    stateParam.gConfig_FreqSpan.channelStd = globalUserVariable->gMeterParam.gConfig_FreqSpan.channelStd;
    stateParam.gConfig_FreqSpan.channelSelID = globalUserVariable->gMeterParam.gConfig_FreqSpan.channelSelID;
    stateParam.gConfig_FreqSpan.channelNumber = globalUserVariable->gMeterParam.gConfig_FreqSpan.channelNumber;
    stateParam.gConfig_FreqSpan.channelStep = globalUserVariable->gMeterParam.gConfig_FreqSpan.channelStep;
    stateParam.gConfig_FreqSpan.channelType = globalUserVariable->gMeterParam.gConfig_FreqSpan.channelType;

    //amplitude
    stateParam.gConfig_Amplitude.refLevel = globalUserVariable->gMeterParam.gConfig_Amplitude.refLevel;
    stateParam.gConfig_Amplitude.attenAuto = globalUserVariable->gMeterParam.gConfig_Amplitude.attenAuto;
    stateParam.gConfig_Amplitude.attenVal = globalUserVariable->gMeterParam.gConfig_Amplitude.attenVal;
    for(qint32 i = 0 ;i < RTSA_BITVIEWNUM; i++)
    {
        stateParam.gConfig_Amplitude.scaleDiv[i] = mBitView[i]->getAmptdAttribute(BIT_AMPTD_DIV);//globalUserVariable->gMeterParam.gConfig_Amplitude.scaleDiv[curwindowindex];
        stateParam.gConfig_Amplitude.refOffset[i] = mBitView[i]->getAmptdAttribute(BIT_AMPTD_OFFSET);//globalUserVariable->gMeterParam.gConfig_Amplitude.refOffset[curwindowindex];
        stateParam.gConfig_Amplitude.units[i] = mBitView[i]->getAmptUnit();//globalUserVariable->gMeterParam.gConfig_Amplitude.units[curwindowindex];
    }
    stateParam.gConfig_Amplitude.preAmpStatus = globalUserVariable->gMeterParam.gConfig_Amplitude.preAmpStatus;

    //sweep
    stateParam.gConfig_Sweep.sweepType = globalUserVariable->gMeterParam.gConfig_Sweep.sweepType;
    stateParam.gConfig_Sweep.autoAcqtime = globalUserVariable->gMeterParam.gConfig_Sweep.autoAcqtime;
    stateParam.gConfig_Sweep.acqTimeVal = globalUserVariable->gMeterParam.gConfig_Sweep.acqTimeVal;
    stateParam.gConfig_Sweep.autoPersistence = globalUserVariable->gAutoPersistenceTime;
    stateParam.gConfig_Sweep.persistenceVal = globalUserVariable->gPersistenceTime;
    stateParam.gConfig_Sweep.highDensity = globalUserVariable->gHighestDensity;
    stateParam.gConfig_Sweep.lowDensity = globalUserVariable->gLowestDensity;
    stateParam.gConfig_Sweep.curveNum = globalUserVariable->gCurve;

    //BW
    stateParam.gConfig_BW.autoRbw = globalUserVariable->gMeterParam.gConfig_BW.autoRbw;
    stateParam.gConfig_BW.rbw = globalUserVariable->gMeterParam.gConfig_BW.rbw;
    stateParam.gConfig_BW.rbwIndex = globalUserVariable->gMeterParam.gConfig_BW.rbwIndex;
    stateParam.gConfig_BW.fftFilter = globalUserVariable->gMeterParam.gConfig_BW.fftFilter;

    //Trigger
    stateParam.gConfig_Trigger.triggerType = globalUserVariable->gMeterParam.gConfig_Trigger.triggerType;
    //Video trigger
    stateParam.gConfig_Trigger.triggerVideoSlope = globalUserVariable->gMeterParam.gConfig_Trigger.triggerVideoSlope;
    stateParam.gConfig_Trigger.triggerVideoLevel = globalUserVariable->gMeterParam.gConfig_Trigger.triggerVideoLevel;
    stateParam.gConfig_Trigger.triggerVideoDelayStatus = globalUserVariable->gMeterParam.gConfig_Trigger.triggerVideoDelayStatus;
    stateParam.gConfig_Trigger.triggerVideoDelay = globalUserVariable->gMeterParam.gConfig_Trigger.triggerVideoDelay;

    //extern trigger
    stateParam.gConfig_Trigger.triggerExternSlope = globalUserVariable->gMeterParam.gConfig_Trigger.triggerExternSlope;
    stateParam.gConfig_Trigger.triggerExternLevel = globalUserVariable->gMeterParam.gConfig_Trigger.triggerExternLevel;
    stateParam.gConfig_Trigger.triggerExternDelayStatus = globalUserVariable->gMeterParam.gConfig_Trigger.triggerExternDelayStatus;
    stateParam.gConfig_Trigger.triggerExternDelay = globalUserVariable->gMeterParam.gConfig_Trigger.triggerExternDelay;

    //period
    stateParam.gConfig_Trigger.triggerPeriodDelay =globalUserVariable->gMeterParam.gConfig_Trigger.triggerPeriodDelay;
    stateParam.gConfig_Trigger.triggerPeriodDelayStatus = globalUserVariable->gMeterParam.gConfig_Trigger.triggerRFDelayStatus;
    stateParam.gConfig_Trigger.triggerPeriodTime = globalUserVariable->gMeterParam.gConfig_Trigger.triggerPeriodTime;

    //RF Burst
    stateParam.gConfig_Trigger.triggerRFSlope = globalUserVariable->gMeterParam.gConfig_Trigger.triggerRFSlope;
    stateParam.gConfig_Trigger.triggerRFLevel = globalUserVariable->gMeterParam.gConfig_Trigger.triggerRFLevel;
    stateParam.gConfig_Trigger.triggerRFDelayStatus = globalUserVariable->gMeterParam.gConfig_Trigger.triggerRFDelayStatus;
    stateParam.gConfig_Trigger.triggerRFDelay = globalUserVariable->gMeterParam.gConfig_Trigger.triggerRFDelay;

    stateParam.gConfig_Trigger.triggerVideoHoldOff = globalUserVariable->gMeterParam.gConfig_Trigger.triggerVideoHoldOff;
    stateParam.gConfig_Trigger.triggerRFBurstHoldOff = globalUserVariable->gMeterParam.gConfig_Trigger.triggerRFBurstHoldOff;
    stateParam.gConfig_Trigger.triggerExternHoldOff = globalUserVariable->gMeterParam.gConfig_Trigger.triggerExternHoldOff;
    stateParam.gConfig_Trigger.triggerFMTHoldOff = globalUserVariable->gMeterParam.gConfig_Trigger.triggerFMTHoldOff;

    stateParam.gConfig_Trigger.triggerSlope = globalUserVariable->gMeterParam.gConfig_Trigger.triggerSlope;
    stateParam.gConfig_Trigger.maskType = globalUserVariable->gMaskType;
    stateParam.gConfig_Trigger.triggerCriteria = globalUserVariable->gMaskType;

    stateParam.gConfig_Trigger.fmtnumber = globalUserVariable->gMeterParam.gConfig_Trigger.fmtnumber;
    for(qint32 i = 0; i < stateParam.gConfig_Trigger.fmtnumber; i++)
    {
        stateParam.gConfig_Trigger.fmtFreq[i] = globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq[i];
        stateParam.gConfig_Trigger.fmtAmpt[i] = globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[i];
    }

    //Trace
    for(qint32 j = 0; j < RTSA_BITVIEWNUM; j++)
    {
        stateParam.gConfig_Trace.curTraceID[j] = mBitView[j]->getTraceAttribute(0,BIT_TRACE_INDEX);// getCurTrace();
        for(qint32 i = 0; i < RTSA_NUM_TRACE; i++)
        {
            stateParam.gConfig_Trace.Rtsa_Config_Trace[j][i].traceType = mBitView[j]->getTraceAttribute(i,BIT_TRACE_TYPE_ATTR);// getTraceType(i);
            stateParam.gConfig_Trace.Rtsa_Config_Trace[j][i].averageOn = mBitView[j]->getTraceAttribute(i,BIT_AVAG_ATTR);//IsAvgOn(i);
            stateParam.gConfig_Trace.Rtsa_Config_Trace[j][i].averageCount = mBitView[j]->getTraceAttribute(i,BIT_AVAG_NUM_ATTR);//getAvgNum(i);
        }
    }

    stateParam.gConfig_Trace.detectorType = getDectorType();
    //Marker

    for(qint32 j = 0; j < RTSA_BITVIEWNUM; j++)
    {
        stateParam.gConfig_Marker[j].curmarkerID = mBitView[j]->getMarkerAttribute(BIT_MARKER_INDEX);
        stateParam.gConfig_Marker[j].markerPeakTraceOn = globalUserVariable->gMeterParam.gConfig_Marker[curwindowindex].markerPeakTraceOn;
        for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
        {
            stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].markerView = mBitView[j]->getMarkerAttribute(BIT_MARKER_VISIABLE,i);
            stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].gMarkerRefAmpt = mBitView[j]->getMarkerRefAmpt(i);
            stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].gMarkerNormalPosY = mBitView[j]->getMarkerNormalPosY(i);
            stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].markerType = mBitView[j]->getMarkerAttribute(BIT_MARKER_TYPE,i);
            stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].markerNoiseOn = mBitView[j]->getMarkerAttribute(BIT_MARKER_NOISE,i);
            stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].gMarkerRefFreq = mBitView[j]->getMarkerFreqAttribute(BIT_MARKER_NORMAL,i);
            stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].gMarkerDeltaFreq = mBitView[j]->getMarkerFreqAttribute(BIT_MARKER_DELTA,i);
        }

    }

    //Limit
    for(qint32 j = 0; j < RTSA_BITVIEWNUM; j++)
    {
        stateParam.gConfig_Limit[j].limitID = mBitView[j]->getLimitAttribute(BIT_LIMIT_INDEX);
        stateParam.gConfig_Limit[j].limitTest = mBitView[j]->getLimitAttribute(BIT_LIMIT_TEST);
        for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
        {
            stateParam.gConfig_Limit[j].limitOn[i] = mBitView[j]->getLimitAttribute(BIT_LIMIT_VIEW,i);
            stateParam.gConfig_Limit[j].limitEdgeOn[i] = mBitView[j]->getLimitAttribute(BIT_LIMIT_MARGIN,i);
            stateParam.gConfig_Limit[j].limitEdgeVal[i] = mBitView[j]->getLimitAttributeEX(BIT_LIMIT_MARGIN_VALUE,i);
            stateParam.gConfig_Limit[j].limitType[i] = mBitView[j]->getLimitAttribute(BIT_LIMIT_TYPE,i);
            stateParam.gConfig_Limit[j].limitEditNum[i] = mBitView[j]->getLimitAttribute(BIT_LIMIT_POINT_NUM,i);
            for(qint32 k = 0; k < stateParam.gConfig_Limit[j].limitEditNum[i]; k++)
            {
                stateParam.gConfig_Limit[j].limtData[i].limitFreq[k] = mBitView[j]->getLimitCurPointData(k,BIT_LIMIT_FREQ,i);
                stateParam.gConfig_Limit[j].limtData[i].limitAmpt[k] = mBitView[j]->getLimitCurPointData(k,BIT_LIMIT_AMPT,i);
            }
            stateParam.gConfig_Limit[j].limitCurEditIndex[i] = mCurLimitDataPos;
        }
    }

    //Display
    //    stateParam.gConfig_Display.displayMode = RTSA_SPECTROGRAM;
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-06-14
*/
void Rtsa_Remote_Interface::setStateParam(_RTSA_FILE_SAVE_LOAD_VARIABLE_ &stateParam)
{
    globalUserVariable->gRefreshAllParam = true;
    for(qint32 i = 0;i < RTSA_BITVIEWNUM; i++)
    {
        mBitView[i]->setBitviewType(stateParam.gConfig_Display.bitviewStatus[i]);
    }
    setDisplay(stateParam.gConfig_Display.displayMode);
    setcurrentview(stateParam.gConfig_Display.curWindowIndex);
    changeBitViewSize(false);
    //Freq
    setCHStandard(stateParam.gConfig_FreqSpan.channelStd);
    setChannelNumber(stateParam.gConfig_FreqSpan.channelNumber);
    setChannelType(stateParam.gConfig_FreqSpan.channelType);

    setCenterFreq(stateParam.gConfig_FreqSpan.gCenterFreq);
    setSpan(stateParam.gConfig_FreqSpan.gSpanFreq);
    setCFStep(stateParam.gConfig_FreqSpan.gStepFreq);
    setFreqOffset(stateParam.gConfig_FreqSpan.gOffsetFreq);

    //amplitude
    //    setAmptUnit(stateParam.gConfig_Amplitude.units);
    setScaleDiv(stateParam.gConfig_Amplitude.scaleDiv[stateParam.gConfig_Display.curWindowIndex]);
    setRefOffset(stateParam.gConfig_Amplitude.refOffset[stateParam.gConfig_Display.curWindowIndex]);
    bitviewbottomdisplay = BV_TOP_APMTINFO;
    setAttenVal(stateParam.gConfig_Amplitude.attenVal);
    setAttenAuto(stateParam.gConfig_Amplitude.attenAuto);
    setPreAmpOn(stateParam.gConfig_Amplitude.preAmpStatus);
    setRefLevel(stateParam.gConfig_Amplitude.refLevel);
    for(qint32 i = 0 ;i < RTSA_BITVIEWNUM; i++)
    {
        //        mBitView[i]->setAmptdAttribute(BIT_AMPTD_DIV,stateParam.gConfig_Amplitude.scaleDiv[i]);
        mBitView[i]->setAmptdAttribute(BIT_AMPTD_OFFSET,stateParam.gConfig_Amplitude.refOffset[i]);
        mBitView[i]->setAmptdUnit(stateParam.gConfig_Amplitude.units[i]);
        mBitView[i]->showTopWordsMsg(bitviewbottomdisplay);
    }
    //    setAmptUnit(stateParam.gConfig_Amplitude.units);
    setAmptUnit(stateParam.gConfig_Amplitude.units[stateParam.gConfig_Display.curWindowIndex]);

    //Sweep
    setSingleSweep(stateParam.gConfig_Sweep.sweepType);
    setAcqTime(stateParam.gConfig_Sweep.acqTimeVal);
    setAcqTimeAuto(stateParam.gConfig_Sweep.autoAcqtime);
    setPersistenceTime(stateParam.gConfig_Sweep.persistenceVal);
    setPersistenceTimeInfinite(stateParam.gConfig_Sweep.autoPersistence);
    setHighestDensity(stateParam.gConfig_Sweep.highDensity);
    setLowestDensity(stateParam.gConfig_Sweep.lowDensity);
    setCurve(stateParam.gConfig_Sweep.curveNum);

    //BW
    setFFTWindow(stateParam.gConfig_BW.fftFilter);
    setBWIndex(stateParam.gConfig_BW.rbwIndex);
    setBWAuto(stateParam.gConfig_BW.autoRbw);

    //Trace
    for(qint32 j = 0; j < RTSA_BITVIEWNUM; j++)
    {
        mBitView[j]->setTraceAttribute(0,BIT_TRACE_INDEX,stateParam.gConfig_Trace.curTraceID[j]);
        for(qint32 i = 0;i < RTSA_NUM_TRACE; i++)
        {
            mBitView[j]->setTraceAttribute(i,BIT_TRACE_TYPE_ATTR,stateParam.gConfig_Trace.Rtsa_Config_Trace[j][i].traceType);
            mBitView[j]->setTraceAttribute(i,BIT_AVAG_NUM_ATTR,stateParam.gConfig_Trace.Rtsa_Config_Trace[j][i].averageCount);
            mBitView[j]->setTraceAttribute(i,BIT_AVAG_ATTR,stateParam.gConfig_Trace.Rtsa_Config_Trace[j][i].averageOn);
        }
    }
    setDectorType(stateParam.gConfig_Trace.detectorType);

    //trigger
    //set all trigger params
    setTriggerLevel(RTSA_TRIGGER_VIDEO,stateParam.gConfig_Trigger.triggerVideoLevel);
    setTriggerSlope(RTSA_TRIGGER_VIDEO,stateParam.gConfig_Trigger.triggerVideoSlope);
    setTriggerDelayStatus(RTSA_TRIGGER_VIDEO,stateParam.gConfig_Trigger.triggerVideoDelayStatus);
    setTriggerDelay(RTSA_TRIGGER_VIDEO,stateParam.gConfig_Trigger.triggerVideoDelay);
    settriggerHoldOffTime(RTSA_TRIGGER_VIDEO,stateParam.gConfig_Trigger.triggerVideoHoldOff);

    setTriggerLevel(RTSA_TRIGGER_EXTERNAL,stateParam.gConfig_Trigger.triggerExternLevel);
    setTriggerSlope(RTSA_TRIGGER_EXTERNAL,stateParam.gConfig_Trigger.triggerExternSlope);
    setTriggerDelayStatus(RTSA_TRIGGER_EXTERNAL,stateParam.gConfig_Trigger.triggerExternDelayStatus);
    setTriggerDelay(RTSA_TRIGGER_EXTERNAL,stateParam.gConfig_Trigger.triggerExternDelay);
    settriggerHoldOffTime(RTSA_TRIGGER_EXTERNAL,stateParam.gConfig_Trigger.triggerExternHoldOff);

    setTriggerDelayStatus(RTSA_TRIGGER_PERIODIC_TIMER,stateParam.gConfig_Trigger.triggerPeriodDelayStatus);
    setTriggerDelay(RTSA_TRIGGER_PERIODIC_TIMER,stateParam.gConfig_Trigger.triggerPeriodDelay);

    setTriggerLevel(RTSA_TRIGGER_RF_BURST,stateParam.gConfig_Trigger.triggerRFLevel);
    setTriggerSlope(RTSA_TRIGGER_RF_BURST,stateParam.gConfig_Trigger.triggerRFSlope);
    setTriggerDelayStatus(RTSA_TRIGGER_RF_BURST,stateParam.gConfig_Trigger.triggerRFDelayStatus);
    setTriggerDelay(RTSA_TRIGGER_RF_BURST,stateParam.gConfig_Trigger.triggerRFDelay);
    settriggerHoldOffTime(RTSA_TRIGGER_RF_BURST,stateParam.gConfig_Trigger.triggerRFBurstHoldOff);

    settriggerHoldOffTime(RTSA_TRIGGER_FMTMASK,stateParam.gConfig_Trigger.triggerFMTHoldOff);
    setFmtDataNum(stateParam.gConfig_Trigger.fmtnumber);
    setFmtFreqData(stateParam.gConfig_Trigger.fmtFreq,stateParam.gConfig_Trigger.fmtnumber);
    setFmtAmptData(stateParam.gConfig_Trigger.fmtAmpt,stateParam.gConfig_Trigger.fmtnumber);


    setTrigger(stateParam.gConfig_Trigger.triggerType);
    //here should judge trigger mode to set params
    setTriggerPeriodTime(stateParam.gConfig_Trigger.triggerPeriodTime);
    switch(stateParam.gConfig_Trigger.triggerType)
    {
    //Video
    case RTSA_TRIGGER_VIDEO:
        setTriggerLevel(RTSA_TRIGGER_VIDEO,stateParam.gConfig_Trigger.triggerVideoLevel);
        setTriggerSlope(RTSA_TRIGGER_VIDEO,stateParam.gConfig_Trigger.triggerVideoSlope);
        setTriggerDelayStatus(RTSA_TRIGGER_VIDEO,stateParam.gConfig_Trigger.triggerVideoDelayStatus);
        setTriggerDelay(RTSA_TRIGGER_VIDEO,stateParam.gConfig_Trigger.triggerVideoDelay);
        settriggerHoldOffTime(RTSA_TRIGGER_VIDEO,stateParam.gConfig_Trigger.triggerVideoHoldOff);
        break;
    case RTSA_TRIGGER_EXTERNAL:
        setTriggerLevel(RTSA_TRIGGER_EXTERNAL,stateParam.gConfig_Trigger.triggerExternLevel);
        setTriggerSlope(RTSA_TRIGGER_EXTERNAL,stateParam.gConfig_Trigger.triggerExternSlope);
        setTriggerDelayStatus(RTSA_TRIGGER_EXTERNAL,stateParam.gConfig_Trigger.triggerExternDelayStatus);
        setTriggerDelay(RTSA_TRIGGER_EXTERNAL,stateParam.gConfig_Trigger.triggerExternDelay);
        settriggerHoldOffTime(RTSA_TRIGGER_EXTERNAL,stateParam.gConfig_Trigger.triggerExternHoldOff);
        break;
    case RTSA_TRIGGER_PERIODIC_TIMER:
        setTriggerDelayStatus(RTSA_TRIGGER_PERIODIC_TIMER,stateParam.gConfig_Trigger.triggerPeriodDelayStatus);
        setTriggerDelay(RTSA_TRIGGER_PERIODIC_TIMER,stateParam.gConfig_Trigger.triggerPeriodDelay);
        break;
    case RTSA_TRIGGER_RF_BURST:
        setTriggerLevel(RTSA_TRIGGER_RF_BURST,stateParam.gConfig_Trigger.triggerRFLevel);
        setTriggerSlope(RTSA_TRIGGER_RF_BURST,stateParam.gConfig_Trigger.triggerRFSlope);
        setTriggerDelayStatus(RTSA_TRIGGER_RF_BURST,stateParam.gConfig_Trigger.triggerRFDelayStatus);
        setTriggerDelay(RTSA_TRIGGER_RF_BURST,stateParam.gConfig_Trigger.triggerRFDelay);
        settriggerHoldOffTime(RTSA_TRIGGER_RF_BURST,stateParam.gConfig_Trigger.triggerRFBurstHoldOff);
        break;
    case RTSA_TRIGGER_FMTMASK:
        settriggerHoldOffTime(RTSA_TRIGGER_FMTMASK,stateParam.gConfig_Trigger.triggerFMTHoldOff);
        setFmtDataNum(stateParam.gConfig_Trigger.fmtnumber);
        setFmtFreqData(stateParam.gConfig_Trigger.fmtFreq,stateParam.gConfig_Trigger.fmtnumber);
        setFmtAmptData(stateParam.gConfig_Trigger.fmtAmpt,stateParam.gConfig_Trigger.fmtnumber);
        //        stateParam.gConfig_Trigger.fmtnumber = globalUserVariable->gMeterParam.gConfig_Trigger.fmtnumber;
        //        for(qint32 i = 0; i < stateParam.gConfig_Trigger.fmtnumber; i++)
        //        {
        //            stateParam.gConfig_Trigger.fmtFreq[i] = globalUserVariable->gMeterParam.gConfig_Trigger.fmtFreq[i];
        //            stateParam.gConfig_Trigger.fmtAmpt[i] = globalUserVariable->gMeterParam.gConfig_Trigger.fmtAmpt[i];
        //        }
        break;
    }
    //    setTriggerSlope(stateParam.gConfig_Trigger.triggerType,stateParam.gConfig_Trigger.triggerSlope);
    //    setTriggerDelay(stateParam.gConfig_Trigger.triggerType,stateParam.gConfig_Trigger.triggerType);
    //Marker
    for(qint32 j = 0; j < RTSA_BITVIEWNUM; j++)
    {
        mBitView[j]->setMarkerAttribute(BIT_MARKER_INDEX,stateParam.gConfig_Marker[j].curmarkerID);
        setPeakTrackOn(stateParam.gConfig_Marker[j].markerPeakTraceOn);
        for(qint32 i = 0;i < RTSA_MARKER_TOTAL_CNT; i++)
        {
            mBitView[j]->setMarkerAttribute(BIT_MARKER_VISIABLE,stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].markerView,i);
            mBitView[j]->setMarkerAttribute(BIT_MARKER_TYPE,stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].markerType,i);
            mBitView[j]->setMarkerAttribute(BIT_MARKER_NOISE,stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].markerNoiseOn,i);
            mBitView[j]->setMarkerFreqAttribute(BIT_MARKER_NORMAL,stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].gMarkerRefFreq,i);
            mBitView[j]->setMarkerFreqAttribute(BIT_MARKER_DELTA,stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].gMarkerDeltaFreq,i);
            mBitView[j]->setMarkerRefAmpt(stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].gMarkerRefAmpt,i);
            mBitView[j]->setMarkerNormalPosY(stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].gMarkerNormalPosY,i);
            emit MarkerSelectOnOff(i,stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].markerView);
            emit BitViewMakerDraw(i,stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].markerView);
        }
        mBitView[j]->refleshdisplay();
        mBitView[j]->refleshmarker();
    }

    //Limit
    for(qint32 j = 0; j < RTSA_BITVIEWNUM; j++)
    {
        mBitView[j]->setLimitAttribute(BIT_LIMIT_INDEX,stateParam.gConfig_Limit[j].limitID);
        mBitView[j]->setLimitAttribute(BIT_LIMIT_TEST,stateParam.gConfig_Limit[j].limitTest);

        for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
        {
            mBitView[j]->setLimitAttribute(BIT_LIMIT_VIEW,stateParam.gConfig_Limit[j].limitOn[i],i);
            mBitView[j]->setLimitAttribute(BIT_LIMIT_MARGIN,stateParam.gConfig_Limit[j].limitEdgeOn[i],i);
            mBitView[j]->setLimitAttributeEX(BIT_LIMIT_MARGIN_VALUE,stateParam.gConfig_Limit[j].limitEdgeVal[i],i);
            mBitView[j]->setLimitAttribute(BIT_LIMIT_TYPE,stateParam.gConfig_Limit[j].limitType[i],i);
            mBitView[j]->setLimitAttribute(BIT_LIMIT_POINT_NUM,stateParam.gConfig_Limit[j].limitEditNum[i],i);
            mBitView[j]->setLimitPointData(stateParam.gConfig_Limit[j].limtData[i].limitFreq,stateParam.gConfig_Limit[j].limitEditNum[i],BIT_LIMIT_FREQ,i);
            mBitView[j]->setLimitPointData(stateParam.gConfig_Limit[j].limtData[i].limitAmpt,stateParam.gConfig_Limit[j].limitEditNum[i],BIT_LIMIT_AMPT,i);
            SetCurLimitDataIndex(stateParam.gConfig_Limit[j].limitCurEditIndex[i]);
        }
    }
    globalUserVariable->gRefreshAllParam = false;

    //refresh all ctrl params. Albert add 19/07/16

    QThread::msleep(200);
    return;
}

/**
* @brief saveState
* @param fileName full path file name
* @Author Albert
* @date 2019-05-21
*/
qint32 Rtsa_Remote_Interface::saveState(QString fileName)
{
    qint32 back = -1;
    mFileType = (qint64)RTSA_FILEHEADER_STATE;
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
    {
        return back;
    }
    else
    {
        //        file.write((char *)&mFileType, sizeof(mFileType));

        file.write((char *)&mStateParam, sizeof(mStateParam));
    }
    file.close();
    file.flush();
    back = 0;
    return back;
}

/**
* @brief loadState
* @param fileName full path file name
* @Author Albert
* @date 2019-05-21
*/
qint32 Rtsa_Remote_Interface::loadState(QString fileName)
{
    qint32 back = -1;
    //    back = loadPresState();

    memset(&mStateParam,0,sizeof(mStateParam));
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        return back;
    }
    else
    {
        //       file.read((char *)&mFileType, sizeof(mFileType));

        file.read((char *)&mStateParam, sizeof(mStateParam));
    }
    file.close();
    back = 1;
    setStateParam(mStateParam);
    return back;
}

qint32 Rtsa_Remote_Interface::PltSaveLinkFlg(qint32 itype)
{
    qint32 ireturndata = -1;
    switch(itype)
    {
    case RTSA_LINK_NG:
        globalUserVariable->gLinkfileType = RTSA_LINK_FLG_LOAD;
        break;
    case RTSA_LINK_OK:
        globalUserVariable->gLinkfileType = RTSA_LINK_FLG_READ;
        break;
    default:
        globalUserVariable->gLinkfileType = RTSA_LINK_FLG_DEFULT;
        break;
    }
    ireturndata = saveLinkState();
    return ireturndata;
}

/**
* @brief
* @param
* @Author Roc
* @date 2019-10-18
*/
void Rtsa_Remote_Interface::PltCurLinkMode(qint32 imod)
{
    globalUserVariable->linkMode = imod;
    return;
}

/**
* @brief Save linked device flag
* @param
* @Author Roc
* @date 2019-10-17
*/
qint32 Rtsa_Remote_Interface::saveLinkState()
{
    qint32 returnData = -1;
    _RTSA_CONFIG_LINK_ linkParam;
    linkParam.linkMode = globalUserVariable->linkMode;
    linkParam.linkFileType = globalUserVariable->gLinkfileType;

    QFile file(RTSA_LINK_STATE_FILE);
    if(!file.open(QIODevice::WriteOnly))
    {
        //Un Know when to use it
        return returnData;
    }
    else
    {
        returnData = 1;
        file.write((char *)&linkParam, sizeof(linkParam));
    }
    file.close();
    file.flush();
    return returnData;
}

/**
* @brief Load linked device flag
* @param
* @Author Roc
* @date 2019-10-17
*/
qint32 Rtsa_Remote_Interface::loadLinkState()
{
    qint32 returnData = -1;
    _RTSA_CONFIG_LINK_ linkParam;
    memset(&linkParam,0,sizeof(linkParam));
    QFile file(RTSA_LINK_STATE_FILE);

    if(!file.open(QIODevice::ReadOnly))
    {   //If there are no rtsa_state.lin  Indicates that the file has just started running or has been deleted
        globalUserVariable->gLinkfileType = RTSA_LINK_FLG_DEFULT;
        return returnData;
    }
    else
    {

        globalUserVariable->gLinkfileType =  linkParam.linkFileType;
        returnData = 1;
        file.read((char *)&linkParam, sizeof(linkParam));
    }
    file.close();
    return returnData;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-06-14
*/
qint32 Rtsa_Remote_Interface::savePresState()
{
    qint32 back = -1;
    _RTSA_CONFIG_PRESET_ presParam;
    presParam.startMode = globalUserVariable->startMode;
    presParam.startFileType = globalUserVariable->gfileType;

    QFile file(RTSA_PRE_STATE_FILE);
    if(!file.open(QIODevice::WriteOnly))
    {
        return back;
    }
    else
    {
        file.write((char *)&presParam, sizeof(presParam));
    }
    file.close();
    file.flush();
    back = 0;
    return back;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-06-14
*/
qint32 Rtsa_Remote_Interface::loadPresState()
{
    qint32 back = -1;
    _RTSA_CONFIG_PRESET_ presParam;
    memset(&presParam,0,sizeof(presParam));
    QFile file(RTSA_PRE_STATE_FILE);
    if(!file.open(QIODevice::ReadOnly))
    {
        return back;
    }
    else
    {
        file.read((char *)&presParam, sizeof(presParam));
    }
    file.close();
    back = 1;
    //    pRemoteScpi->setStartedFlag(RTSA_START_FLAG);
    globalUserVariable->gfileType =  presParam.startFileType;
    if(presParam.startMode != RTSA_MODULE)
    {
    }
    return back;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-08-22
*/
void Rtsa_Remote_Interface::initFileType(qint32 fileType)
{
    switch (fileType) {
    case RTSA_FILE_STATE:
        mFileType = (qint64)RTSA_FILEHEADER_STATE;
        initStateParam(mStateParam);
        break;
    case RTSA_FILE_TRACE_STATE:
        mFileType = (qint64)RTSA_FILEHEADER_STATE_DATA;
        break;
    case RTSA_FILE_SCREENCONFIG_STATE:
        break;
    case RTSA_FILE_MEASUREDATA:
        break;
    case RTSA_FILE_LIMIT:
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
* @date 2019-08-22
*/
void Rtsa_Remote_Interface::parseFile(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        return ;
    }
    else
    {
        file.read((char *)&mFileType, sizeof(mFileType));
    }
    file.close();
    //    mFileType = RTSA_FILEHEADER_STATE_DATA;
    switch (mFileType) {
    case RTSA_FILEHEADER_STATE:
        loadState(fileName);
        break;
    case RTSA_FILEHEADER_STATE_DATA:
        loadTraceData(fileName);
        break;
    case RTSA_FILE_SCREENCONFIG_STATE:
        break;
    case RTSA_FILE_MEASUREDATA:
        break;
    case RTSA_FILE_LIMIT:
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
* @date 2019-08-22
*/
qint32 Rtsa_Remote_Interface::saveTraceData(QString fileName)
{
    qint32 ret = -1;
    qint32 validStartPos = 0;
    qint32 RealNumber = 0;
    // trace data divide into 3 parts. 1-detector trace data, 2-dpx data, 3-spectrogram data
    uchar* pDpxData = NULL;
    qreal *trace = GetTraceData(RTSA_NUM_SWEEP_POINT,0);
    initStateParam(mStateParam);
    mFileType = (qint64)RTSA_FILEHEADER_STATE_DATA;
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
    {
        return ret;
    }
    else
    {
        // first save file type,
        file.write((char *)&mFileType, sizeof(mFileType));
        //// state params.
        file.write((char *)&mStateParam, sizeof(mStateParam));

        //detector trace data
        for(qint32 j = 0; j < RTSA_BITVIEWNUM; j++)
        {
            for(qint32 i = 0; i < RTSA_NUM_TRACE; i ++)
            {
                if(mBitView[j]->getBitviewType() == BIT_SPECTROGRAM)
                {
                    validStartPos = mBitView[j]->getSpectrogramValidStartPos(validStartPos,RealNumber);
                }
                mBitView[j]->getTraceRenderData(trace,RTSA_NUM_SWEEP_POINT,i);
                file.write((char *)trace, sizeof(qreal) * RTSA_NUM_SWEEP_POINT);
            }
        }
        // spectrogram data
        file.write((char *)&validStartPos, sizeof(qint32));
        file.write((char *)&RealNumber, sizeof(qint32));
        file.write((char *)gSpectrogramCacheData, sizeof(qreal) * RTSA_SPECTROGRAM_CACHE_DATA * RTSA_TRACE_DATA_NUM);
        // dpx data
        pDpxData = GetDensityData(DPX_WIDTH_SIZE * DPX_HEIGHT_SIZE * 4);
        file.write((char *)pDpxData, sizeof(uchar) * DPX_WIDTH_SIZE * DPX_HEIGHT_SIZE * 4);
    }
    file.close();
    file.flush();
    ret = 0;
    return ret;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-08-29
*/
qint32 Rtsa_Remote_Interface::loadTraceData(QString fileName)
{
    qint32 ret = -1;
    qint32 validStartPos = 0;
    qint32 RealNumber = 0;
    uchar* pDpxData;
    qreal *trace;
    trace = GetTraceData(RTSA_NUM_SWEEP_POINT,0);
    pDpxData = GetDensityData(DPX_WIDTH_SIZE * DPX_HEIGHT_SIZE * 4);
    memset(&mStateParam,0,sizeof(mStateParam));
    memset(&gSpectrogramCacheData,0,sizeof(gSpectrogramCacheData));
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        return ret;
    }
    else
    {
        file.read((char *)&mFileType, sizeof(mFileType));
        // read state params
        file.read((char *)&mStateParam, sizeof(mStateParam));
        setStateParam(mStateParam);

        // read normal trace data
        for(qint32 j = 0; j  < RTSA_BITVIEWNUM; j++)
        {
            mBitView[j]->setFileLoadDoneFlag(true);
            for(qint32 i = 0; i < RTSA_NUM_TRACE; i ++)
            {
                file.read((char *)trace, sizeof(qreal) * RTSA_NUM_SWEEP_POINT);
                mBitView[j]->setTraceRenderData(trace,RTSA_NUM_SWEEP_POINT,i);
            }
        }
        // spectrogram data
        file.read((char *)&validStartPos,sizeof(qint32));
        file.read((char *)&RealNumber,sizeof(qint32));

        file.read((char *)gSpectrogramCacheData, sizeof(qreal) * RTSA_SPECTROGRAM_CACHE_DATA * RTSA_TRACE_DATA_NUM);
        // when cache data re-fill, load data should from last end to this start
        if(RealNumber == RTSA_SPECTROGRAM_CACHE_DATA)
        {
            if(validStartPos < SPECTROGRAM_SCREEN_MAX)
            {
                qint32 partStartPos = SPECTROGRAM_SCREEN_MAX - validStartPos;
                for(qint32 i = (RTSA_SPECTROGRAM_CACHE_DATA - partStartPos); i < RTSA_SPECTROGRAM_CACHE_DATA; i++)
                {
                    drawFileLoadSpectrogram(gSpectrogramCacheData[i]);
                }
            }
        }
        for(qint32 i = 0; i < validStartPos; i++)
        {
            drawFileLoadSpectrogram(gSpectrogramCacheData[i]);
        }
        // dpx data
        file.read((char *)pDpxData, sizeof(uchar) * DPX_WIDTH_SIZE * DPX_HEIGHT_SIZE * 4);

        for(qint32 i = 0; i < RTSA_BITVIEWNUM; i++)
        {
            if(mBitView[i]->getBitviewType() == BIT_DENSITY)
            {
                mBitView[i]->setDensityData(gSpectrogramCacheData[validStartPos - 1],pDpxData);
                break;
            }
        }

    }
    file.close();
    refreshAllBitView();
    //    setSingleSweep(true);
    ret = 1;
    return ret;
}

void Rtsa_Remote_Interface::drawTrace()
{
    for(qint32 i = 0; i < RTSA_BITVIEWNUM; i++)
    {
        if(gWinCtrlList[globalUserVariable->gMeterParam.gConfig_Display.displayMode][i] == RTSA_SPECTROGRAM + 1)
        {
            mBitView[i]->showFalltrom(gOriginalTrace,RTSA_NUM_SWEEP_POINT);
        }
        else if(gWinCtrlList[globalUserVariable->gMeterParam.gConfig_Display.displayMode][i] == RTSA_SPECTRUM + 1)
        {
            mBitView[i]->showSigLine(gOriginalTrace,RTSA_NUM_SWEEP_POINT);
        }
        else if(gWinCtrlList[globalUserVariable->gMeterParam.gConfig_Display.displayMode][i] == RTSA_DENSITY + 1)
        {
            if(gDpxData == NULL)
            {
                mBitView[i]->showSigLine(gOriginalTrace,RTSA_NUM_SWEEP_POINT);
            }
            else
            {
                mBitView[i]->showDensity(gOriginalTrace,gDpxData,RTSA_NUM_SWEEP_POINT,RTSA_NUM_SWEEP_POINT,201);
            }
        }
    }
}

/**
 * @brief select current bieview
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::setcurrentview(quint32 index)
{
    emit ParentFocus();
    if(globalUserVariable->gLocal == RTSA_REMOTE)
    {
        return;
    }
    if((quint32)curwindowindex == index || wintotalnum < 1)
        return;

    for(qint32 i = 0; i < RTSA_BITVIEWNUM; i++)
    {
        mBitView[i]->getclickSource(index);
        mBitView[i]->HideBoardLine();
    }

    //Tony 1010 optimization
    mBitView[curwindowindex]->getclickSource(index);
    mBitView[curwindowindex]->showBoarderLine();
    curwindowindex=index;
    mBitView[curwindowindex]->getclickSource(index);
    mBitView[curwindowindex]->showBoarderLine();

    updateDateFromBitview();

    //Albert 03/09 when single sweep, should refresh bitview display.
    for(int i=0;i< RTSA_BITVIEWNUM;i++)
    {
        mBitView[i]->refleshdisplay();
    }

    emit BitViewChanged(curwindowindex);
    emit RedrawInfoShow(LABEL_TRACE_STATUS);
    emit RedrawInfoShow(LABEL_AVERAGE);
    return;
}
/**
 * @brief marker change slot
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::markerchange(qint32 index)
{
    //    if(pMarker.getCurMarkerID() == index)
    //    {
    //        return;
    //    }
    setCurMarkerID(index);
    return;
}
/**
 * @brief marker move slot
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void Rtsa_Remote_Interface::markerMove(bool index)
{
    if(index)
    {
        emit BitViewMakerMoved(true);
        emit MarkerPosChanged(true);
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-28
*/
void Rtsa_Remote_Interface::changeBitViewSize(bool isDoubleClicked)
{
    qint32 bitViewIndex = curwindowindex;
    for(int i=0;i<RTSA_BITVIEWNUM;i++)
    {
        mBitView[i]->hide();
    }
    mIsCurBitViewSizeChange = isDoubleClicked;
    if(mIsCurBitViewSizeChange)
    {
    }
    else
    {
        setBitViewParam(globalUserVariable->gMeterParam.gConfig_Display.displayMode);
        setcurrentview(bitViewIndex);
    }
    if(mIsZoomIn)
    {
        setZoomIn();
    }
    else
    {
        setZoomOut();
    }
    return;
}
