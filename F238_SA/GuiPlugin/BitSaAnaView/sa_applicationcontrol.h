#ifndef APPLICATIONCONTROL_H
#define APPLICATIONCONTROL_H

#include "sa_stdafx.h"
#include "define.h"
#include "sa_user_variable.h"
#include "sa_user_limit.h"
//#include "file_user_variable.h"
#include "sa_alothforsa.h"

#include <QWidget>
#include <QObject>
#include <QDir>
#include "sa_customedTablewidget.h"
#include "sa_parasaveload.h"
//#include "bpltinterface.h"

typedef struct stru_ZeroRestrain{
    qint32 uZeroRestrainPhase;
    qint32 uZeroRestainAtten;
}_ZERORESTRAIN_,*pZERORESTRAIN;

class ClickableTableWidget;

class controlInterface:public QObject
{
    Q_OBJECT
public:
    controlInterface(user_variable &UserVariable,user_limit &UserLimit);
    user_variable *globalUserVariable;
    user_limit    *globalUserLimit;
    alothforsa    *bitaloth;
    paraSaveLoad  *pparaSaveLoad;
    //johnson 2020-11-19
    _MEASURE_STATE_ gMeasureState;

    ~controlInterface();
public://Measure Interface
    void setMeasureOff();
    void setChannelPower();
    void setACP();
    void setOccupiedBW();
    void setDemodulation(qint32 Demodu = SA_FM);
    void setSpectrumEmissionMask();
    void setMultiACP();
    void setSpuriousEmissionMask();
    void setFieldStrength();
    void setDemodulationType(qint32 demodulationType);
    void SetMeasureItems(qint32 imea);
    qint32 GetMeasureItems();

    void   setChannelPower_ChannelBW(qint64 uChBw);//quint32 is Hz
    quint64 getChannelPower_ChannelBW();
    qreal getChannelPower();

    void   setACP_ChannelBW(qint64 uChBw);
    void   setACP_ChannelSP(qint64 uChSp);
    quint64 getACP_ChannelBW();
    quint64 getACP_ChannelSP();
    qreal getLeftACP_ChannelPower();
    qreal getMidACP_ChannelPower();
    qreal getRightACP_ChannelPower();
    qreal getLeftACP_ChannelDbc();
    qreal getRightACP_ChannelDbc();

    void setMulACP_HighestCHFreq(qint64 ChFreq);
    qint64 getMulACP_HighestCHFreq();
    void setMulACP_LowestCHFreq(qint64 ChFreq);
    qint64 getMulACP_LowestCHFreq();
    void setMulACP_ChnSpacing(qint64 ChSpacing);
    qint64 getMulACP_ChnSpacing();
    void setMulACP_MainIntegBW(qint64 ChBW);
    qint64 getMulACP_MainIntegBW();
    void setMulACP_ADJIntegBW(qint64 ChBW);
    qint64 getMulACP_ADJIntegBW();
    void setMulACP_ALTIntegBW(qint64 ChBW);
    qint64 getMulACP_ALTIntegBW();

    qint32 getDemodulation();

    void   setOccupiedBW_OccBW(qreal dOccBw);
    void   setOccupiedBW_XdB(qreal dXdb);
    qreal getXdB_OccupiedBW();
    qreal getOccBW_OccupiedBW();
    quint64 getOccupiedBW_XdB();
    quint64 getOccupiedBW_OccBW();

    qreal getTotalPower();
    //measure --> spetrum EM
    void setSpecEMDisplay(qint32 mode);
    qint32 getSpecEMDisplay();

    void setSpecEMRefType(qint32 type);
    qint32 getSpecEMRefType();

    void setInteBW(qreal mBandWidth);
    qreal getInteBW();

    void setSpecEMTotalPowerRef(qreal mPower);
    qreal getSpecEMTotalPowerRef();

    void setSpecEMPSDRef(qreal mPSD);
    qreal getSpecEMPSDRef();

    void setSpecEMPeakRef(qreal mPeak);
    qreal getSpecEMPeakRef();


    void setSpecEMViewStatus(qint32 OffsetIndex,qint32 status);
    qint32 getSpecEMViewStatus(qint32 OffsetIndex);

    void setSpecEMMaskType(qint32 type);
    qint32 getSpecEMMaskType();

    void setSpecEMRefRbw(quint32 mRbw);
    quint32 getSpecEMRefRbw();

    void setSpecEMRefChBw(qreal freq);
    qreal getSpecEMRefChBw();

    void setSpecEMBsPower(qreal dBmVal);
    qreal getSpecEMBsPower();
    //measure --> spurious EM
    void setMeasureStatus(qint32 mStatus);//0 means suspend,1 means remeasure
    qint32 getSpurMeasureStatus();//0 means suspend,1 means remeasure

    void setSpurReportType(qint32 mType);
    qint32 getSpurReportType();

    void setSpurEMAveType(qint32 mType);
    qint32 getSpurEMAveType();

    void setSpurEMTableType(qint32 mType);
    qint32 getSpurEMTableType();

    void setSpurEMCurRangeIndex(qint32 curRangeIndex);
    qint32 getSpurEMCurRangeIndex();

    void setSpurEMCurSpurIndex(qint32 curSpurIndex);
    qint32 getSpurEMCurSpurIndex();

    void setSpurEMDisplay(qint32 status,qint32 curRangeIndex =-1);
    qint32 getSpurEMDisplay(qint32 curRangeIndex =-1);

    void setSpurEMstartFreq(qreal freq,qint32 curRangeIndex =-1);
    qreal getSpurEMstartFreq(qint32 curRangeIndex =-1);

    void setSpurEMstopFreq(qreal freq,qint32 curRangeIndex =-1);
    qreal getSpurEMstopFreq(qint32 curRangeIndex =-1);

    void setSpurEMRBW(qreal mRbw,qint32 curRangeIndex =-1);
    qreal getSpurEMRBW(qint32 curRangeIndex =-1);

    void setSpurEMVBW(qreal mVbw,qint32 curRangeIndex =-1);
    qreal getSpurEMVBW(qint32 curRangeIndex =-1);

    void setSpurEMSweepTime(qreal mSwTime,qint32 curRangeIndex =-1);
    qreal getSpurEMSweepTime(qint32 curRangeIndex =-1);

    void setSpurEMstartLimit(qreal mStartLimit,qint32 curRangeIndex =-1);
    qreal getSpurEMStartLimit(qint32 curRangeIndex =-1);

    void setSpurEMStopLimit(qreal mStopLimit,qint32 curRangeIndex =-1);
    qreal getSpurEMStopLimit(qint32 curRangeIndex =-1);

    void setSpurEMpeakDefi(qreal mValue,qint32 curRangeIndex =-1);
    qreal getSpurEMpeakDefi(qint32 curRangeIndex =-1);

    void setSpurEMpeakThreshold(qreal mValue,qint32 curRangeIndex =-1);
    qreal getSpurEMpeakThreshold(qint32 curRangeIndex =-1);

    void setSpurEMAtten(qreal mAtten,qint32 curRangeIndex =-1);
    qreal getSpurEMAtten(qint32 curRangeIndex =-1);
public://Frequency Interface
    void SetSysRefuiStates(qint32 itype);
    qint32 GetSysRefuiStates();

    void setCenterFreq(qreal uCenterFreq);
    qreal getCenterFreq();

    void setStartFreq(qreal uStartFreq);
    qreal getStartFreq();

    void setStopFreq(qreal uStopFreq);
    qreal getStopFreq();

    void setCFFreq(qint64 uCFFreq);
    quint64 getCFFreq();

    void setFreqOffset(qint64 uFreqOffset);
    qint64 getFreqOffset();

    void setSpan(qint64 uSpanFeq);
    quint64 getSpan();

    void setFullSpan();
    void setZeroSpan();
    void setLastSpan();
    quint64 getLastSpan();

    void setCHStandard(qint32 index);
    qint32 getCHStandard();

    void setCommuDirection(qint32 direction);
    qint32 getCommuDirection();

    void setChannelNumber(qint32 number);
    qint32 getChannelNumber();

    qint32 getChannelNumStep();
    void setChannelNumStep(qint32 step);
public://Amplitude Interface
    void setRefLevel(qreal dRefLevel);
    qreal getRefLevel();

    void setAttenValue(qreal dAtten);
    qreal getAttenValue();

    void setAttenStatus(quint32 uAttenStatus);
    quint32 getAttenStatus();

    void setScaleDiv(qreal dScaleDiv);
    qreal getScaleDiv();

    void setAmpUnit(qint32 Unit);
    qint32 getAmpUnit();

    void setPreampStatus(quint32 uPreamp);
    quint32 getPreampStatus();

    void setRefOffset(qreal dRefOffset);
    qreal getRefOffset();

    void setAutoScale(quint32 uAutoScale = true);

    void setAutoAttenTrackStatus(quint32 uAutoAttenTrackStatus);
    quint32 getAutoAttenTrackStatus();

    //*******Zero Freq Cal
    //Johnson 190410
    void setZeroRestrainAtten(qint32 dValue);
    qreal getZeroRestrainAtten();
    void setZeroRestrainPhase(qreal dValue);
    qreal getZeroRestrainPhase();
    //Johnson 190423
    void setZeroRestrain(qint32 dZeroRestrainAttenValue,qreal dZeroRestrainPhaseVale);

public://BW Interface
    void setAutoRbwStatus(qint32 uRbwStatus);
    qint32 getRbwStatus();

    void setRbwValue(quint32 uRbwValue);
    quint64 getRbwValue();

    void setVbwtoRbw(qreal value);
    qreal getVbwtoRbw();

    void setAutoVbwStatus(quint32 uVbwStatus);
    quint32 getVbwStatus();

    void setVbwValue(quint32 uVbwValues);
    quint64 getVbwValue();

    //IF Output
    void setIFOutPut(qint32 uifMode);
    qint32 getIFOutPut();

public://Sweep Interface
    void setSweepType(quint32 uSweepType);
    quint32 getSweepType();

    void setAutoSweepTimeStatus(quint32 uAutoSweepTimeStatus);
    quint32 getAutoSweepTimeStatus();

    void setSweepTime(qreal dSweepTime);
    qreal getSweepTime();

    void setDotSweepTime(qreal dDotSweepTime);
    qreal getDotSweepTime();
    void setAutoDotSweepTime(quint32 uAutoDotSweepTimeStatus);
    qreal getAutoDotSweepTimeStatus();

    void setFixSweepMode(quint32 uFixSweepMode);
    quint32 getFixSweepMode();

    void setZeroSpanTime(qreal mTime);
    qreal getZeroSpanTime();

    void setTriggerMode(qint32 uTiggerMode);
    quint32 getTriggerMode();

    void setTriggerDelayStatus(qint32 uStatus, qint32 uMode = -1);
    qint32 getTriggerDelayStatus(qint32 uMode =-1);

    void setTriggerDelayValue(qreal uValue,qint32 uMode =-1);
    qreal getTriggerDelayValue(qint32 uMode =-1);

    void setTriggerSlope(qint32 mSlope,qint32 uMode =-1);
    qint32 getTriggerSlope(qint32 uMode =-1);

    void setTriggerLevel(qreal mLevel_dBm,qint32 uMode =-1);
    qreal getTriggerLevel(qint32 uMode = -1);

    void setTriggerPerTimer(qreal mTimeMs);
    qreal getTriggerPerTimer();

    void setSweepSpeed(quint32 uSweepSpeed);
    quint32 getSweepSpeed();

public://Trace Interface
    void setTraceSelect(qint32 uTraceSelect);
    qint32 getTraceSelect();

    void setTraceType(qint32 traceType, qint32 traceIndex =-1);
    qint32 getTraceType(qint32 traceIndex=-1);

    void setTraceAverageStatus(qint32 traceAverageStatus, qint32 traceIndex =-1);
    qint32 getTraceAverageStatus(qint32 traceIndex = -1);

    void setTraceAverageCount(qint32 traceAverageCount, qint32 traceIndex =-1);
    qint32 getTraceAverageCount(qint32 traceIndex = -1);

    void setSuspendFunc(qint32 isSuspend);
    qint32 getSuspendFunc();

    void setTraceViewStatus(qint32 traceViewStatus,qint32 traceIndex = -1);
    qint32 getTraceViewStatus(qint32 traceIndex = -1);

    void setDetectorMode(qint32 uTraceDetectorMode,bool bFlag = true);
    quint32 getDetectorMode();
private:
    void setTraceStatus(qint32 traceStatus);
    qint32 getTraceStatus();

public://Marker Interface
    void setMarkerSelect(qint32 markerSelect);
    qint32 getMarkerSelect();

    void setMarkerNoiseStatus(qint32 markerNoiseStatus,qint32 markerIndex =-1,bool bFlag = true);
    qint32 getMarkerNoiseStatus(qint32 markerIndex =-1);

    void setMarkerFreqCountStatus(qint32 markerCountStatus,qint32 markerIndex =-1);
    qint32 getMarkerFreqCountStatus(qint32 markerIndex =-1);

    void setMarkerViewStatus(qint32 markerViewStatus,qint32 markerIndex =-1);
    qint32 getMarkerViewStatus(qint32 markerIndex =-1);


    void setMarkerType(qint32 markerType, qint32 markerIndex = -1);
    qint32 getMarkerType(qint32 markerIndex = -1);


    void setMarkerDisplay(qint32 markerDisplay);
    qint32 getMarkerDisplay();

    void setMarkerRefFreq(qreal uMarkerRefFreq, qint32 markerIndex = -1);
    qreal getMarkerRefFreq(qint32 markerIndex = -1);


    qreal getMarkerRefAmp(qint32 markerIndex = -1);
    void setMarkerRefAmpCompensation(qreal compensation);
    void refreshDataAfterCompensation();

    void setMarkerDeltaFreq(qreal uMarkerDeltaFreq, qint32 markerIndex = -1);
    qreal getMarkerDeltaFreq(qint32 markerIndex = -1);

    qreal getMarkerDeltaAmp(qint32 markerIndex = -1);

    void setMarkerRefTime(qreal uMarkerRefTime, qint32 markerIndex = -1);
    qreal getMarkerRefTime(qint32 markerIndex = -1);

    void setMarkerDeltaTime(qreal uMarkerDeltaTime,qint32 markerIndex = -1);
    qreal getMarkerDeltaTime(qint32 markerIndex = -1);

    qreal getPeakPointAmpt();
    qint64 getPeakPointFreq();


    void setMarkerToCF();
    void setMarkerToCFStep();
    void setMarkerToStart();
    void setMarkerToStop();
    void setMarkerToRefLvl();
private:
    //For resume
    void setMkrViewForResume(qint32 markerViewStatus,qint32 markerIndex =-1);
public://Limit Interface
    void setLimitData(qint32 limitSelect,qint32 pointIndex,qreal freq,qreal ampt);

    void setLimitFreq(qint32 limitSelect,qint32 pointIndex,qreal freq);
    qreal getLimitFreq(qint32 limitSelect,qint32 pointIndex);

    void setLimitAmpt(qint32 limitSelect,qint32 pointIndex,qreal ampt);
    qreal getLimitAmpt(qint32 limitSelect,qint32 pointIndex);

    void setLimitCurPointIndex(qint32 limitSelect,qint32 pointIndex);
    qint32 getLimitCurPointIndex(qint32 limitSelect = -1);

    void setLimitSelect(qint32 limitSelect);
    qint32 getLimitSelect();

    void setLimitLineStatus(qint32 limitLineStatus, qint32 limitIndex = -1);
    qint32 getLimitLineStatus(qint32 limitIndex = -1);

    void setLimitEdgeStatus(qint32 limitEdgeStatus,qint32 limitIndex = -1);
    qint32 getLimitEdgeStatus(qint32 limitIndex = -1);

    void setLimitEdgeValue(qreal dLimitEdgeValue,qint32 limitIndex = -1);
    qreal getLimitEdgeValue(qint32 limitIndex = -1);

    void setLimitTestStatus(qint32 limitTestStatus);
    qint32 getLimitTestStatus();

    void setLimitType(qint32 limitType,qint32 limitIndex = -1);
    qint32 getLimitType(qint32 limitIndex = -1);

    void setInsertLimitRow(qint32 limitSelect = -1);
    void setDeleteLimitRow(qint32 limitSelect,qint32 pointIndex);
    void setDeleteLimitOne(qint32 limitSelect= -1);
    void setDeleteLimitAll();

    void setAutoLimit(qint32 limitSelect = -1);

    qint32 getLimitPointCnt(qint32 limitSelect = -1);
#ifdef SAMPLE_LIMIT
    void setUpperLimit(qreal uAmptdBm);
    qreal getUpperLimit();

    void setLowerLimit(qreal uAmptdBm);
    qreal getLowerLimit();

    void setATLdBcLimit(qreal uAmptdBm);
    qreal getATLdBcLimit();

    void setUpperLimitStatus(qint32 isOn);
    qint32 getUpperLimitStatus();

    void setLowerLimitStatus(qint32 isOn);
    qint32 getLowerLimitStatus();

    void setATLdBcLimitStatus(qint32 isOn);
    qint32 getATLdBcLimitStatus();
#endif
public://IF mode and ref select
    void setIFMode(qint32 uifMode);
    quint32 getIFMode();
    #if 0
    void setIFRef(quint32 uifRef);
    quint32 getIFRef();
    void setBrtLevel(quint32 uBrtLevel);
    quint32 getBrtLevel();
    #endif
private:
    qreal tmpAmpt[NUM_SWEEP_POINT];
    quint32 CalculateAutoLimitMax(qint32 start, qint32 stop);
    void setDeleteAllLimits(ClickableTableWidget *tableWidget);
    void setInsertRowBelow(ClickableTableWidget *tableWidget);
    void setDeleteRow(ClickableTableWidget *tableWidget);
    void setDeleteLimit(ClickableTableWidget *tableWidget);
private:
    void removeSamePoint(qint32 limitSelect);
    void removeLimitRow(qint32 limitSelect,qint32 pointIndex);
public://Peak Interface
    void setPeak();
    void searchPeak();
    void setMinSearch();
    void setNextPeak();
    void setPeakRightSearch();
    void setPeakLeftSearch();
    void setPeakTrackStatus(quint32 peakTrackStatus);
    quint32 getPeakTrackStatus();
public://Load Interface
    bool loadFile(QString mFileFullPath);
    void setLoadState(QString mFileFullPath);
    void setLoadTrace(QString mFileFullPath);
    void setLoadScreen();
    void setLoadSetup();

    void setLoadMedia(qint32 loadMedia);
    qint32 getLoadMedia();

public://Save Interface
    bool setSaveState(QString mFileFullPath);
    bool setSaveTrace(QString mFileFullPath);
    void setSaveScreen();
    void setSaveSetup();

    void setSaveMedia(qint32 saveMedia);
    qint32 getSaveMedia();

public://System Interface
    void SetFuncKeyStatus(qint32 mShift);
    qint32 GetFuncKeyStatus();

    void ScreenCaptureFunc(QString filePath, QString fileName);
    void TraceSuspendFunc(qint32 status);

    void SetDisplayMode(qint32 mDisMode); //0 -- indoor 1 -- outdoor 2 -- night
    qint32 GetDisplayMode();
public:
    void setCurrentMode(quint32 mode);
    quint32 getCurrentMode();

    void SetLocalRemoteMode(qint32 mode);
    qint32 GetLocalRemoteMode();

    void ChangeLcdStateWithNoSig(qint32 ilock);
    qint32 GetLcdState();
public://Johnson 190621
    qreal getFreqCount(qreal centerFreq, qint32 fsr, quint32 rbwValue);
public:
    void LoadParamControl();
    void DemodulationParaControl();
    void BWParaControl();
    void SpanParaControl();
    void AmplitudeParaControl();
    void TraceParaControl();
    void SweepParaControl(qreal gSweepTimeFromFile);
    void TriggerParaControl();
    void MarkerParaControl();
    void LimitParaControl();
signals:
    void infoRefresh(qint32 mType,qint32 mIndex);
    void signalModeChange();
    void signalZeroCalComplete(bool bRet);
public:
    void initTraceAverage();
public://Johnson 190505
    /* int:    0 Preset Status,1 Last Status,2 User Status
     * return: <0 fail,=0 success
    */
    qint32 PltSavePres(qint32 itype);
    qint32 PltSaveConditions(qint32 itype);
    qint32 PltLoadConditions(qint32 itype = 0,qint32 presetFlag = 0);
    void PltCurAnaMode(qint32 imod);

    //Johnson 190822
    void PresetDefaultStates();
    bool bDefaultStatesPreset;//true,when PresetDefaultStates() executes finished,false,init state or bitsa sets preset state finished

    //Johnson 20200618
    void refreshSAConfig(_SA_ALL_CONF_ &remoteConfigData);
    void getSAParam(_SA_ALL_CONF_ &remoteConfigData);

private:
    void LoadModeParam();

//Johnson 190606 Zero Restrain celibrate
private:
    _ZERORESTRAIN_ gZeroRestrain;
    qreal minAmp;
    qint32 ZeroRestrainPhase;//Record the Phase value that sends to FPGA everytime
    qint32 ZeroRestrainAtten;//Record the Atten value that sends to FPGA everytime
    qreal tmpCenterFreq,tmpSpanFreq,tmpZeroPhase,tmpZeroAtten;
    bool bZeroRestrainStatusSet,bZeroRestrainCalComplete,bInitZeroRestrainSuc;

    //method2 param
    qint32 curStep_Atten,curStep_Phase;//Record current cal step
    qint32 lastStep_Atten,lastStep_Phase;//Record last cal step
    qint32 tmpZeroAttenMin;//Record the min atten value which gets after last cal
    qint32 tmpZeroPhaseMin;//Record the min phase value which gets after last cal

    //method1 param
    qint32 attenBegin,attenEnd,phaseBegin,phaseEnd,attenStep,phaseStep;
    bool bBeginAcqData;

    bool bCalStop;
public slots:
    bool ZeroRestrainCelibrate();
    bool setZeroRestrainFromFile();
    //void setBeginZeroRestrainCal();
    void setZeroRestrainCalStop();
public slots:
    void setBeginZeroRestrainCal();

public: // only for remote
    void SetRawData(char *src);
    void SetDrawData(char* src);
    void SetAllData(char* src);

    void GetRawData(char* dest);
    void GetDrawData(char* dest);
    void GetAllData(char* dest);

public:
    void setDoorControlSource(qint32 uDrCtlSource);
    qint32 getDoorControlSource();

    void setLevleEdgeSelect(qint32 uLvlEdgSelect);
    qint32 getLevleEdgeSelect();

    void setLevleEdgeMode(qint32 uLvlEdgMode);
    qint32 getLevleEdgeMode();

    void setDoorControlSweepMode(qint32 uDrCtlSweepMode);
    qint32 getDoorControlSweepMode();

    void setPeriodTrigSynchroSrc(qint32 uPrdTrgSyncSrc);
    qint32 getPeriodTrigSynchroSrc();

    void setDoorControlSwitch(qint32 uDrCtlSwitch);
    qint32 getDoorControlSwitch();

    void setEdgeTrigDely(qreal edgTrgDely);
    qreal getEdgeTrigDely();

    void setEdgeTrigDoorWidth(qreal edgTrgDrWidth);
    qreal getEdgeTrigDoorWidth();

    void setEdgeTrigPreventStatus(qint32 uEdgTrgPrvntStatus);
    qint32 getEdgeTrigPreventStatus();

    void setEdgeTrigPreventTimes(qreal prvntTime);
    qreal getEdgeTrigPreventTimes();

    void setRFBurstTrigLevel(qreal trigLevel);
    qreal getRFBurstTrigLevel();

    void setPeriodTrigPeriod(qreal period);
    qreal getPeriodTrigPeriod();

    void setPeriodTrigSrcDelay(qreal srcDely);
    qreal getPeriodTrigSrcDelay();

    void setPeriodTrigPreventStatus(qint32 uPrdTrgPrvntStatus);
    qint32 getPeriodTrigPreventStatus();

    void setPeriodTrigPreventTimes(qreal prvntTime);
    qreal getPeriodTrigPreventTimes();

    void setGateViewStatus(qint32 gateViewStatus);
    qint32 getGateViewStatus();

    void setGateViewStartTime(qreal startTime);
    qreal getGateViewStartTime();

#if 0
public:
    quint32 noticeCode;
    void initNoticeCode(qint16 source,qint16 logicmode);
    quint32 SendNoticeCode(qint16 npflag = NOTIC_MESSAGE, qint16 ntype = NO_WARNING, qint16 dictIndex = NO_ERR, bool bNoticePlatF = false);
#endif
};

#endif // APPLICATIONCONTROL_H
