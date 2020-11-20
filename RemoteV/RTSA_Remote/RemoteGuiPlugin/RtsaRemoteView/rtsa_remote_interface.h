/**************Copyright (c)**************************************
 **
 **               INNO Instrument(China) Co.,Ltd.
 **
 **------------File Info------------------------------------------
 **Class name:              RtSa_Remote_Interface
 **Latest Version:          V1.0.0
 **Latest modified Date:
 **Created by:              Roc
 **Created date:            2019/10/15
 **Descriptions:            RTSA all set/get SCPI function
 **
 *****************************************************************/

#ifndef RTSA_REMOTE_INTERFACE_H
#define RTSA_REMOTE_INTERFACE_H

#include <QObject>
#include "bitview.h"
#include "rect_define.h"
#include <QMutex>
#include <QRegExp>
#include <qmath.h>
#include "rtsa_file_user_variable.h"
#include "rtsa_remote_scpi.h"

class Rtsa_Remote_Interface : public QObject
{
    Q_OBJECT
public:
    explicit Rtsa_Remote_Interface(QObject *parent = 0);
    ~Rtsa_Remote_Interface();
private:
    QMutex _mutex;

public:
    void ReadDataFromMeter();
private:
    void SendAndRecvScpi(qint32 index,  qint32  nModleID = 0,qint32 nIndexNo = 0);
public://SCPI
    //频率 Frequency
    void setCenterFreq(qreal freq);
    qreal getCenterFreq();

    void setStartFreq(qreal freq);
    qreal getStartFreq();

    void setStopFreq(qreal freq);
    qreal getStopFreq();

    void setCFStep(qreal freq);
    qreal getStepFreq();

    void setFreqOffset(qreal freq);
    qreal getFreqOffset();

    void setSpan(qreal freq);
    qreal getSpan();

    void setFullSpan();

    void setCHStandard(qint32 index);
    qint32 getCHStandard();

    void setBandIndex(qint32 bandIndex);
    qint32 getBandIndex();

    void setChannelType(qint32 direction);
    qint32 getChannelType();

    void setChannelNumber(qint32 number);
    qint32 getChannelNumber();

    //幅度 Amplitude
    void setAutoScale();

    void setRefLevel(qreal refLevel);
    qreal getRefLevel();

    void setAttenAuto(bool isAttenAuto);
    bool IsAttenAuto();

    void setAttenVal(qreal attenVal);
    qreal getAttenVal();

    void setScaleDiv(qreal scaleDiv);
    qreal getScaleDiv();

    void setPreAmpOn(bool IsOn);
    bool IsPreAmpOn();

    void setRefOffset(qreal refOffset);
    qreal getRefOffset();

    void setAmptUnit(qint32 unitIndex);
    qint32 getAmptUint();

    //扫描 Sweep
    void setSingleSweep(bool isSingle); // [1] means single, [0] means cont;
    bool IsSingleSweep();

    void setAcqTimeAuto(bool isAuto);
    bool IsAcqTimeAuto();

    void setAcqTime(qreal acqtime);
    qreal getAcqTime();


    //带宽 BandWidth
    void setBWAuto(bool isAuto);
    bool IsBWAuto();

    void setBWIndex(qint32 bwIndex);
    qint32 getBWIndex();

    qreal getBW();//查看一下是否有用

    void setFFTWindow(qint32 fftWindow);
    qint32 getFFTWindow();

    //触发 Trigger
    void setTrigger(qint32 TriggerMode);
    qint32 getTrigger();

    void setTriggerLevel(qint32 TriggerMode, qreal level);
    qreal getTriggerLevel(qint32 TriggerMode);

    void setTriggerSlope(qint32 TriggerMode, qint32 slope);
    qint32 getTriggerSlope(qint32 TriggerMode);

    void setTriggerDelayStatus(qint32 TriggerMode, bool delayStatus);
    bool getTriggerDelayStatus(qint32 TriggerMode);

    void setTriggerDelay(qint32 TriggerMode, qreal Delay);
    qreal getTriggerDelay(qint32 TriggerMode);

    void setTriggerPeriodTime(qreal time);
    qreal getTriggerPeriodTime();

    void settriggerHoldOffTime(qint32 TriggerMode,qreal holdOffTime);
    qreal getriggerHoldOffTime(qint32 TriggerMode);

    //FMT trigger
    void BuildFmtFromTrace();
    void DeleteAllFmtMask();

    void setFmtType(qint32 Upper);
    qint32 getFmtType();

    void setFmtTriggerCriterion(qint32 criterion);
    qint32 getFmtTriggerCriterion();

    void setFmtDataNum(qint32 dataNum);
    qint32 getFmtDataNum();

    void setCurFmtFreqData(qreal data, qint32 index);
    qreal getCurFmtFreqData(qint32 index);

    void setCurFmtAmptData(qreal data, qint32 index);
    qreal getCurFmtAmptData(qint32 index);

    void InsertFmtDataRow();
    //迹线 Trace
    void setTraceViewStatus(bool status,qint32 traceID = -1);
    bool getTraceViewStatus(qint32 traceID = -1);

    void setCurTraceType(qint32 traceType);
    qint32 getCurTraceType();

    void setCurTraceAvgNum(qint32 Num);
    qint32 getCurTraceAvgNum();

    void setDectorType(qint32 DectorType);
    qint32 getDectorType();

    void GetCurTraceData();
    void getDpxData();
    //光标 Marker
    void setCurMarkerID(qint32 MarkerID);
    qint32 getCurMarkerID();

//    void setCurMarkerOn(bool isOn);
//    bool isCurMarkerOn();

    void setMarkerOn(qint32 MarkerID,bool isOn);
    bool isMarkerOn(qint32 MarkerID);

    void setCurMarkerType(qint32 MarkerType);
    qint32 getCurMarkerType();


    void setMarkerType(qint32 MarkerID,qint32 MarkerType);
    qint32 getMarkerType(qint32 MarkerID);

    void setMarkerToCenter();

    void setMarkerToStart();

    void setMarkerToStop();

    //Marker Peak
    void setMarkerToPeak();
    void setMarkerToMin();
    void setMarkerToNextPeak();
    void setMarkerToLeftPeak();
    void setMarkerToRightPeak();

    void setPeakTrackOn(bool PeakTrackOn);
    bool IsPeakTrackOn();

    void setMarkerRefFreq(qint32 MarkerID,qreal refFreq);
    qreal getMarkerRefFreq(qint32 MarkerID);

    void setMarkerDeltaFreq(qint32 MarkerID,qreal DeltaFreq);
    qreal getMarkerDeltaFreq(qint32 MarkerID);

    void setMarkerNoiseOn(qint32 MarkerID, bool isOn);
    bool IsMarkerNoiseOn(qint32 MarkerID);

    // 极限线 Limit
    void setCurLimit(qint32 curLimitID);
    qint32 getCurLimit();

    void setCurLimitOn(qint32 LimitID,bool isOn);
    bool IsCurLimitOn(qint32 LimitID);

    void setMarginOn(qint32 LimitID,bool isOn);
    bool IsMarginOn(qint32 LimitID);

    void setMargin(qint32 LimitID,qreal margin);
    qreal getMargin(qint32 LimitID);

    void setLimitTestOn(bool isOn);
    bool IsLimitTestOn();

    void setLimitType(qint32 LimitID,qint32 nType);
    qint32 getLimitType(qint32 LimitID);

    void DeleteAllLimit();

    void BuildLimitFromTrace();
    qint32 getLimitDataNum(qint32 LimitID);

    void DeleteLimitRow(qint32 LimitID);
    void setLimitCurPointFreq(qreal pData, qint32 curPos, qint32 limitID);
    qreal getLimitCurPointFreq(qint32 curPos, qint32 limitID);

    void setLimitCurPointAmpt(qreal pData, qint32 curPos, qint32 limitID);

    qreal getLimitCurPointAmpt(qint32 curPos, qint32 limitID);


    void InsertLimitRow();

    //显示 Display
    void setDisplay(qint32 disPlayMode);
    qint32 getDisplay();

    //显示设置 Setup
    void setPersistenceTimeInfinite(bool isInfinite);
    bool IsPersistenceTimeInfinite();

    void setPersistenceTime(qreal time);
    qreal getPersistenceTime();

    void setHighestDensity(qint32 high);
    qint32 getHighestDensity();

    void setLowestDensity(qint32 low);
    qint32 getLowestDensity();

    void setCurve(float curve);
    qint32 getCurve();

    void setDensityLevelAjust();

    //调整函数
public:
    //频率 Frequency
    QString getFreqAdjustStr(qreal freq,qint32 DecPrecision = 12);
    qint32 freqUnitFindProc(qreal freq);
    qint32 timeUnitFindProc(qreal time);
    QString getFreqStr(qint32 freqID);

    //幅度 Amplitude
    QString getRefLevelAdjustStr();

    //带宽 BandWidth
    QString getFFTWindowStr();
    qreal getCurIndexBW(qint32 index);
 //FMT trigger
    void setCurFmtDataIndex(qint32 curIndex);
    qint32 getCurFmtDataIndex();
    void setFmtFreqData(qreal* data,qint32 dataNum);
    void setFmtAmptData(qreal* data,qint32 dataNum);

    qreal* getFMTFreqData();
    qreal* getFMTAmplitudeData();
    //迹线 Trace
    bool IsAvgOn(qint32 traceID);
    qint32 getCurAvgNum(qint32 traceID);
    void setCurTrace(qint32 traceID);
    qint32 getCurTrace();
    void setTraceType(qint32 traceID,qint32 traceType);
    qint32 getTraceType(qint32 traceID);
    void setAvgNum(qint32 traceID,qint32 Num);
    qint32 getAvgNum(qint32 traceID);

    //光标 Marker
    void setMarkerFreq(qint32 MarkerID, qreal Freq);
    bool IsMarkerAlreadyOn();
    // get marker freq(use these function to get/set either ref or delta marker)
    qreal getMarkerFreq(qint32 MarkerID);

    //Albert add for button marker show
    void showMarkerWidget(bool isShow);

    QString getMarkerInfoStr(qint32 MarkerID);

    // 极限线 Limit
    bool isHaveLimitOn();
    void setLimitTableShow(bool isShow);
    void SetCurLimitDataIndex(qint32 curPos);
    qint32 GetCurLimitDataIndex();
    void DeleteLimit(qint32 index);
    void setLimitFreqData(qreal* pData,qint32 DataNum,qint32 LimitID);
    qreal* getLimitFreqData(qint32 LimitID);
    void setLimitAmptData(qreal* pData,qint32 DataNum,qint32 LimitID);
    qreal* getLimitAmptData(qint32 LimitID);

private:
    //频率 Frequency
    void adjustSpanFreq(qreal freq);
    void adjustAcqtime(qreal time);
    void AdjustPeriodTime(qreal time);

    //幅度 Amplitude

    void amplitudeAttenControl();
    void ChangeOtherUnitTodBm(qreal refLevel);

    qreal ChangedBmToOherUnit();
    QString getRefLevelStr(qreal reflevel);
    QString getRefLevelVoltStr(qreal reflevel);
    QString getRefLevelWattStr(qreal reflevel);

    void setSleepTime(qreal sleepTime);
    //带宽 BandWidth
  //触发 Trigger
    void calUpperFmtPointsY(qint32 dataNum);
    void calLowerFmtPointsY(qint32 dataNum);


    void ReSetAllFmtData();

    bool isFreqInFmtArray(qreal freq);
    //迹线 Trace
    void setAvgOn(qint32 traceID,bool isOn);

    void resetAvgCnt();

    void setTraceData(qreal* pData,qint32 dataNum, qint32 traceID);
    qreal* GetTraceData(qint32 dataNum, qint32 traceID);

    qreal getMaxTraceData(qreal* pData, qint32 startIndex, qint32 nNum);
    //光标 Marker
    qreal getMarkerCurFreq(qint32 Type);
    bool hasMarkerOn();


    void setMarkerDisplay(qint32 display);
    qint32 getMarkerDisplay();
    void setMarkerToCFStep();
    void setMarkerToRefLevel();

    qreal getMarkerRefAmpt(qint32 MarkerID);
    qreal getMarkerDeltaAmpt(qint32 MarkerID);
    qreal getMarkerNoiseAmpt(qint32 MarkerID);

    // 极限线 Limit
    void setLimitNum(qint32 bitViewNo,qint32 LimitID,qint32 num);


public:
    // all bitview initial to bitrtsa class
    void InitBitView(QWidget* widget);
    void setGobalVariable(RtSa_User_Variable* globalVariable);

    void SetDisplayMode(qint32 mDisMode); //0 -- indoor 1 -- outdoor 2 -- night
    qint32 GetDisplayMode();

    //set zoom flag
    void setZoomFlag(bool isZoomIn);
    //set drag flag
    void setDragFlag(bool dragFlag);
    bool getDragFlag();

    void setZoomIn();
    void setZoomOut();

    void setShiftKeyEnable(bool isEnable);
    bool isShiftKeyEnable();

    void changeSize(qint32 width, qint32 height);


    // RTSA draw all pixmap. trace,limit,marker etc.
    void Draw();
    void DrawFlag(bool isSuspend);
    bool getDrawFlag();


    QString getAdjustTimeStr(qreal time);
    qint32 getCurBitviewType();

    void GetRawData(qreal* dest);
    void updateTraceData(qreal* pTraceData, qint32 TraceNum);
private:

    //* when single, change sweep param, display should repaint
    void refreshMainDisplay();

    void refreshAllBitView();

    bool AutoAttenTrack();

    void setAutoAttenTrack(bool isOn);
    bool IsAutoAttenTrackOn();


    void ReDrawLeftInfo();
    void setSystemDisplay(qint32 sysDisplay);
    void showBitViewBottomMsg(qint32 bottomDisplay);

    void setCurBitView(qint32 index);

    void updateDpxData(quint32* pTraceData, qint32 TraceNum);
    void updateGeneralDataToBitview(qint32 datatype);
    void updateDateFromBitview();

    void setBitViewFileLoadFlag(bool isFileload);
    void drawFileLoadSpectrogram(qreal* pData);

    void GetDrawData(char* dest);

    void getRawTraceData(qreal*dest);
    void GetAllTraceData(char* dest);

    void saveDisplayParam(qint32 display);
    void loadDisplayParam(qint32 display);

    //set display language
    void setLanguage(qint32 language);
    qint32 getLanguage();

    //abstract display rect set.
    void setBitViewParam(qint32 measType);

    //get GlobaluserParam
    RtSa_User_Variable* getGlobalUserVariable();

    uchar *GetDensityData(qint32 dataNum);

public:    //save/load cond file

    // 0 means default.cond 1 means last.cond 2 means user.cond
    void PltCurAnaMode(qint32 imod);
    qint32 PltSaveConditions(qint32 itype);
    qint32 PltLoadConditions(qint32 itype);
    qint32 PltSavePres(qint32 itype);

    void initDefaultParam(_RTSA_FILE_SAVE_LOAD_VARIABLE_& stateParam);
    void initStateParam(_RTSA_FILE_SAVE_LOAD_VARIABLE_& stateParam);
    void setStateParam(_RTSA_FILE_SAVE_LOAD_VARIABLE_& stateParam);
    qint32 saveState(QString fileName);
    qint32 loadState(QString fileName);
    qint32 PltSaveLinkFlg(qint32 itype);
    void PltCurLinkMode(qint32 imod);

    //by Roc 2019.10.17
    qint32 saveLinkState();
    qint32 loadLinkState();

    qint32 savePresState();
    qint32 loadPresState();

    void initFileType(qint32 fileType);
    void parseFile(QString fileName);

    //迹线 Trace
    qint32 saveTraceData(QString fileName);
    qint32 loadTraceData(QString fileName);
    void drawTrace();
signals:
    void BitViewChanged(quint32 index);
    void BitViewMakerDraw(qint32 markID,bool isOn);
    void MarkerOn(bool isOn);
    void MarkerSelectOnOff(qint32 markerID,bool isOn);
    void BitViewMakerMoved(bool isOn);
    void ParentFocus();

    void MarkerPosChanged(bool changed);

    //use info signal to redraw info display
    void RedrawInfoShow(qint32 infoID);
   void ScpiDataFinished();
   void ScpiCmdFinished();

public slots:
    void setcurrentview(quint32 index);
    void markerchange(qint32 index);
    void markerMove(bool index);
    void changeBitViewSize(bool isDoubleClicked);

    void RecvScpiCmd(socketCmdAndRecvInfo socketData);

public: //做虚函数
    void setCurrentMode(quint32 mode);
    quint32 getCurrentMode();

    void SetLocalRemoteMode(qint32 mode);
    qint32 GetLocalRemoteMode();

    void ChangeLcdStateWithNoSig(qint32 ilock);
    qint32 GetLcdState();
public:
    RtSa_Remote_Scpi *pRemoteScpi;
private:

    qreal gLimitFreq[RTSA_LIMIT_TOTAL];
    qreal gLimitAmpt[RTSA_LIMIT_TOTAL];

    BitView* mBitView[RTSA_BITVIEWNUM];
    RtSa_User_Variable* globalUserVariable; //软件数据 配置

    _RTSA_FILE_SAVE_LOAD_VARIABLE_ mStateParam;//软件保存参数

    qint32 bitviewbottomdisplay;
    qint32 bitviewtopdisplay;

    qint32 curwindowindex;//当前视图索引

    qint32 wintotalnum;
    // qint32 mDisplayMode;//显示标志位
    qint32 mWidth;//缩放宽度
    qint32 mHeight;//缩放高度

    QRegExp rx;
    bool  mIsZoomIn;
    bool  mDragFlag;

    bool  mSingleFinished;

    double mLowData[RTSA_NUM_SWEEP_POINT];

    bool mIsShiftKeyEnable;
    qint32 mCurLimitDataPos;


    bool mIsCurBitViewSizeChange;
    qint64 mFileType;
    bool isMarkerBtnPressed;
    qint32 mFmtCurDataIndex;

    //迹线 Trace
    qreal   gOriginalTrace[RTSA_NUM_SWEEP_POINT];
    quint32* gDpxData;
    quint32  gDpxDataNum;
    qreal    gTraceData[RTSA_NUM_SWEEP_POINT];

    QString recvSovket;  //Socket 数据接收

private:
    bool bGetDataFromScpi; //是否实时读取SCPI数据
public:
    qint32 pSocketLinkStatus; //socket Link Flg
};

#endif // RTSA_REMOTE_INTERFACE_H
