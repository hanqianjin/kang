/**************Copyright (c)**************************************
 **
 **               INNO Instrument(China) Co.,Ltd.
 **
 **------------File Info------------------------------------------
 **Class name:              RtSa_Interface
 **Latest Version:          V1.0.0
 **Latest modified Date:
 **Created by:              Albert
 **Created date:            2018/12/13
 **Descriptions:            RTSA all set/get function
 **
 *****************************************************************/
#ifndef RTSA_INTERFACE_H
#define RTSA_INTERFACE_H

#include <QObject>
#include "rtsa_trace.h"
#include "bitview.h"
#include "rect_define.h"
#include "rtsa_control.h"
#include "rtsa_limit.h"
#include "rtsa_marker.h"
#include <QRegExp>
#include <qmath.h>
#include "rtsa_file_user_variable.h"

class RtSa_Interface : public QObject
{
    Q_OBJECT
public:
    explicit RtSa_Interface(QObject *parent = 0);
    ~RtSa_Interface();
public:
    // all bitview initial to bitrtsa class
    void InitBitView(QWidget* widget);
    void setSystemDisplay(qint32 sysDisplay);
    void showBitViewBottomMsg(qint32 bottomDisplay);
    void setZoomIn();
    void setZoomOut();
    void changeSize(qint32 width, qint32 height);

//    void setThreadInterface(RtSa_ThreadGraph* threadObj);
    // RTSA draw all pixmap. trace,limit,marker etc.
    void Draw();
    bool AutoAttenTrack();

    void setGobalVariable(RtSa_User_Variable* globalVariable);

    //Albert 09/03/08
    void ReDrawLeftInfo();

    // Freq menu
    void setCenterFreq(qreal freq);
    qreal getCenterFreq();
    void setStartFreq(qreal freq);
    qreal getStartFreq();
    void setStopFreq(qreal freq);
    qreal getStopFreq();
    void setSpan(qreal freq);
    qreal getSpan();
    void setFullSpan();
    void setCFStep(qreal freq);
    qreal getCFStep();
    QString getFreqStr(qint32 freqID);
    QString getFreqAdjustStr(qreal freq,qint32 DecPrecision = 12);
    qint32 freqUnitFindProc(qreal freq);
    qint32 timeUnitFindProc(qreal time);
    void setFreqOffset(qreal freq);
    qreal getFreqOffset();

    void setCHStandard(qint32 index);
    qint32 getCHStandard();

    void setBandIndex(qint32 bandIndex);
    qint32 getBandIndex();

    void setCommuDirection(qint32 direction);
    qint32 getCommuDirection();

    void setChannelNumber(qint32 number);
    qint32 getChannelNumber();

    //ampt
    void setRefLevel(qreal refLevel);
    qreal getRefLevel();
    QString getRefLevelStr(qreal reflevel);
    QString getRefLevelAdjustStr();
    QString getRefLevelVoltStr(qreal reflevel);
    QString getRefLevelWattStr(qreal reflevel);
    qreal ChangedBmToOherUnit();
    void setAttenAuto(bool isAttenAuto);
    bool IsAttenAuto();
    void setAttenVal(qreal attenVal);
    qreal getAttenVal();
    void setScaleDiv(qreal scaleDiv);
    qreal getScaleDiv();
    void setRefOffset(qreal refOffset);
    qreal getRefOffset();
    void setAmptUnit(qint32 unitIndex);
    qint32 getAmptUint();
    void setPreAmpOn(bool IsOn);
    bool IsPreAmpOn();
    void setAutoScale();

    //BW
    void setBW(qreal bw);
    qreal getBW();
    void setBWAuto(bool isAuto);
    bool IsBWAuto();
    void setBWIndex(qint32 bwIndex);
    qint32 getBWIndex();
    void setFFTWindow(qint32 fftWindow);
    qint32 getFFTWindow();
    QString getFFTWindowStr();
    qreal getCurIndexBW(qint32 index);

    //Display
    void setDisplay(qint32 disPlayMode);
    qint32 getDisplay();
    void setSingleSweep(bool isSingle); // [1] means single, [0] means cont;
    bool IsSingleSweep();
    void setAutoAttenTrack(bool isOn);
    bool IsAutoAttenTrackOn();
    void setPersistenceTimeInfinite(bool isInfinite);
    bool IsPersistenceTimeInfinite();
    void setPersistenceTime(qreal time);
    qreal getPersistenceTime();
    QString getAdjustTimeStr(qreal time);
    void setHighestDensity(qint32 high);
    qint32 getHighestDensity();
    void setLowestDensity(qint32 low);
    qint32 getLowestDensity();
    void setCurve(float curve);
    qint32 getCurve();
    void setDensityLevelAjust();

    //measure
    void setAcqTimeAuto(bool isAuto);
    bool IsAcqTimeAuto();
    void setAcqTime(qreal acqtime);
    qreal getAcqTime();

    void setSleepTime(qreal sleepTime);

    //measure limit
    void setCurLimit(qint32 curIndex);
    qint32 getCurLimit();
    void setCurLimitOn(qint32 LimitID,bool isOn);
    bool IsCurLimitOn(qint32 LimitID);
    void setLimitTestOn(bool isOn);
    bool IsLimitTestOn();
    void setMarginOn(qint32 LimitID,bool isOn);
    bool IsMarginOn(qint32 LimitID);
    void setMargin(qint32 LimitID,qreal margin);
    qreal getMargin(qint32 LimitID);
    void setLimitType(qint32 LimitID,qint32 nType);
    qint32 getLimitType(qint32 LimitID);
    void setLimitNum(qint32 LimitID,qint32 num);
    qint32 getLimitDataNum(qint32 LimitID);
    void setLimitFreqData(qreal* pData,qint32 DataNum,qint32 LimitID);
    qreal* getLimitFreqData(qint32 LimitID);
    void setLimitAmptData(qreal* pData,qint32 DataNum,qint32 LimitID);
    qreal* getLimitAmptData(qint32 LimitID);

    //Albert 19/04/10 for limit build from trace data
    void BuildLimitFromTrace();
    qreal getMaxTraceData(qreal* pData, qint32 startIndex, qint32 nNum);

//    qreal getLimitMaxTraceData(qreal* pData, qreal pMaxData, qint32 Index);

    void SetCurLimitDataIndex(qint32 curPos);
    qint32 GetCurLimitDataIndex();

    void setLimitCurPointFreq(qreal pData, qint32 curPos, qint32 limitID);
    void setLimitCurPointAmpt(qreal pData, qint32 curPos, qint32 limitID);
    qreal getLimitCurPointFreq(qint32 curPos, qint32 limitID);
    qreal getLimitCurPointAmpt(qint32 curPos, qint32 limitID);

    void setcurFreq(qreal freq);
    void setcurAmpt(qreal ampt);
    qreal getcurFreq();
    qreal getcurAmpt();

    //Edit Limit
    void InsertLimitRow();
    void DeleteLimitRow(qint32 index);
    void DeleteLimit(qint32 index);
    void setLimitTableShow(bool isShow);

    void DeleteAllLimit();

    bool isHaveLimitOn();

    //Trace
    void setCurTrace(qint32 traceID);
    qint32 getCurTrace();
    void setTraceViewStatus(bool status,qint32 traceID = -1);
    bool getTraceViewStatus(qint32 traceID = -1);
    void setCurTraceType(qint32 traceType);
    qint32 getCurTraceType();
    void setCurTraceAvgNum(qint32 Num);
    qint32 getCurTraceAvgNum();
    void setTraceOn(qint32 traceID,bool isTraceOn);
    bool IsTraceOn(qint32 traceID);
    void setTraceType(qint32 traceID,qint32 traceType);
    qint32 getTraceType(qint32 traceID);
    void setDectorType(qint32 DectorType);
    qint32 getDectorType();
    void setAvgOn(qint32 traceID,bool isOn);
    bool IsAvgOn(qint32 traceID);
    void setAvgNum(qint32 traceID,qint32 Num);
    qint32 getAvgNum(qint32 traceID);
    qint32 getCurAvgNum(qint32 traceID);
    void resetAvgCnt();

    void setTraceData(qreal* pData,qint32 dataNum, qint32 traceID);
    qreal* GetTraceData(qint32 dataNum, qint32 traceID);

    //Marker
    void setCurMarkerID(qint32 MarkerID);
    qint32 getCurMarkerID();
    void setCurMarkerOn(bool isOn);
    bool isCurMarkerOn();
    void setMarkerOn(qint32 MarkerID,bool isOn);
    bool isMarkerOn(qint32 MarkerID);
    void setCurMarkerType(qint32 MarkerType);
    qint32 getCurMarkerType();
    void setMarkerType(qint32 MarkerID,qint32 MarkerType);
    qint32 getMarkerType(qint32 MarkerID);
    void setMarkerRefFreq(qint32 MarkerID,qreal refFreq);
    qreal getMarkerRefFreq(qint32 MarkerID);
    void setMarkerDeltaFreq(qint32 MarkerID,qreal DeltaFreq);
    qreal getMarkerDeltaFreq(qint32 MarkerID);
    void setMarkerDisplay(qint32 display);
    qint32 getMarkerDisplay();
    void setMarkerNoiseOn(qint32 MarkerID, bool isOn);
    bool IsMarkerNoiseOn(qint32 MarkerID);
    void setMarkerToCenter();
    void setMarkerToCFStep();
    void setMarkerToStart();
    void setMarkerToStop();
    void setMarkerToRefLevel();
    // get marker freq(use these function to get/set either ref or delta marker)
    qreal getMarkerFreq(qint32 MarkerID);
    void setMarkerFreq(qint32 MarkerID, qreal Freq);
    bool IsMarkerAlreadyOn();
    void setPeakTrackOn(bool PeakTrackOn);
    bool IsPeakTrackOn();

    //Albert add for button marker show
    void showMarkerWidget(bool isShow);
    bool hasMarkerOn();


    qreal getMarkerRefAmpt(qint32 MarkerID);
    qreal getMarkerDeltaAmpt(qint32 MarkerID);
    qreal getMarkerNoiseAmpt(qint32 MarkerID);
    QString getMarkerInfoStr(qint32 MarkerID);

    //Trigger
    void setTrigger(qint32 TriggerMode);
    qint32 getTrigger();
    void setTriggerSlope(qint32 TriggerMode, qint32 slope);
    qint32 getTriggerSlope(qint32 TriggerMode);
    void setTriggerDelayStatus(qint32 TriggerMode, bool delayStatus);
    bool getTriggerDelayStatus(qint32 TriggerMode);
    void setTriggerDelay(qint32 TriggerMode, qreal Delay);
    qreal getTriggerDelay(qint32 TriggerMode);
    void setTriggerLevel(qint32 TriggerMode, qreal level);
    qreal getTriggerLevel(qint32 TriggerMode);
    void setTriggerPeriodTime(qreal time);
    qreal getTriggerPeriodTime();
    void settriggerHoldOffTime(qint32 TriggerMode,qreal holdOffTime);
    qreal getriggerHoldOffTime(qint32 TriggerMode);

    //FMT trigger
    void setFmtType(qint32 Upper);
    qint32 getFmtType();

    void setCurFmtDataIndex(qint32 curIndex);
    qint32 getCurFmtDataIndex();
    void setFmtDataNum(qint32 dataNum);
    qint32 getFmtDataNum();
    void setFmtFreqData(qreal* data,qint32 dataNum);
    void setFmtAmptData(qreal* data,qint32 dataNum);
    qreal* getFMTFreqData();
    qreal* getFMTAmplitudeData();
    void calUpperFmtPointsY(qint32 dataNum);
    void calLowerFmtPointsY(qint32 dataNum);

    void setCurFmtFreqData(qreal data, qint32 index);
    qreal getCurFmtFreqData(qint32 index);

    void setCurFmtAmptData(qreal data, qint32 index);
    qreal getCurFmtAmptData(qint32 index);

    void ReSetAllFmtData();

    bool isFreqInFmtArray(qreal freq);

    void BuildFmtFromTrace();
    void DeleteAllFmtMask();

    void setFmtTriggerCriterion(qint32 criterion);
    qint32 getFmtTriggerCriterion();

    void InsertFmtDataRow();

    void updateTraceData(qreal* pTraceData, qint32 TraceNum);
    void updateDpxData(quint32* pTraceData, qint32 TraceNum);
    void setCurBitView(qint32 index);
    void updateGeneralDataToBitview(qint32 datatype);
    void updateDateFromBitview();

    //Peak
    void setMarkerToPeak();
    void setMarkerToNextPeak();
    void setMarkerToLeftPeak();
    void setMarkerToRightPeak();
    void setMarkerToMin();

    //set zoom flag
    void setZoomFlag(bool isZoomIn);
    //set drag flag
    void setDragFlag(bool dragFlag);
    bool getDragFlag();

    //* when single, change sweep param, display should repaint
    void refreshMainDisplay();

    //flag for shift key
    void setShiftKeyEnable(bool isEnable);
    bool isShiftKeyEnable();


    //set display language
    void setLanguage(qint32 language);
    qint32 getLanguage();

    //abstract display rect set.
    void setBitViewParam(qint32 measType);

    //get GlobaluserParam
    RtSa_User_Variable* getGlobalUserVariable();

    void setGeneralDataToShm();

    void saveDisplayParam(qint32 display);
    void loadDisplayParam(qint32 display);

    //Albert 19/04/26
    qint32 getCurBitviewType();

    //save/load cond file
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
    qint32 savePresState();
    qint32 loadPresState();

    qint32 ParseFileType(QString fileName);

    void initFileType(qint32 fileType);
    void parseFile(QString fileName);
    qint32 saveTraceData(QString fileName);
    qint32 loadTraceData(QString fileName);

    void refreshAllBitView();

    void SetDisplayMode(qint32 mDisMode); //0 -- indoor 1 -- outdoor 2 -- night
    qint32 GetDisplayMode();

    void DrawFlag(bool isSuspend);
    bool getDrawFlag();

    void setBitViewFileLoadFlag(bool isFileload);
    void drawFileLoadSpectrogram(qreal* pData);

    void GetRawData(char* dest);
    void GetDrawData(char* dest);
    void GetAllData(char* dest);
    void GetDensityData(char* dest);

    void refreshSpectrogramRect();

    void setspectrogramCursorID(qint32 CursorId);
    qint32 getspectrogramCursorID();
    void closeAllSpectrogramTimeCursor(qint32 bitviewIndex);
    void setSepctrogramEnableDrawCursor(qint32 CursorId,bool isEnable);
    bool isSepectrogramDrawCursorEnable(qint32 CursorId);
    void setspectrogramCursorIndex(qint32 CursorId,qint32 index);
    qint32 getspectrogramCursorIndex(qint32 CursorId);

    void repaintBitview();

    bool IsSizeChangeEnable();


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

    void BitScaleChange();
public slots:
    void setcurrentview(quint32 index);
    void markerchange(qint32 index);
    void markerMove(bool index);
    void changeBitViewSize(bool isDoubleClicked);
#ifdef BITVIEW_F239
    void scaleChange(qreal xsize,qreal ysize);
    void BitSuspendDrawSlot();
    void BitChangeCenterFreq(qreal freq);
    void BitChangeRefLevel(qreal refLevel);
#endif
private:
    BitView* mBitView[RTSA_BITVIEWNUM];
    RtSa_Trace pTrace;
    RtSa_Control pSweepControl;
    RtSa_Limit pLimit;
    RtSa_Marker pMarker;
    qint32 bitviewbottomdisplay;
    qint32 bitviewtopdisplay;
    qint32 curwindowindex;
    qint32 wintotalnum;
    qint32 mDisplayMode;
    RtSa_User_Variable* globalUserVariable;
    qint32 mWidth;
    qint32 mHeight;
//    qint32 mOrginWidth;
//    qint32 mOrginHeight;
    QRegExp rx;
    bool  mIsZoomIn;
    bool  mDragFlag;
    bool  mSingleFinished;
    double mLowData[RTSA_NUM_SWEEP_POINT];
    bool mIsPeakTrackOn;
    bool mIsShiftKeyEnable;
    qint32 mCurLimitDataPos;
    qreal mCurFreq;
    qreal mCurAmpt;
    bool isMarkerBtnPressed;
    _RTSA_FILE_SAVE_LOAD_VARIABLE_ mStateParam;

    //Albert 19/05/23  fmt
    qreal fmtFreq[RTSA_NUM_SWEEP_POINT];
    qreal fmtAmplitude[RTSA_NUM_SWEEP_POINT];
    qint32 fmtPoints[RTSA_NUM_SWEEP_POINT];
    qint32 mFmtDataTotalNum;
    qint32 mFmtCurDataIndex;
    bool mIsCurBitViewSizeChange;
    qint64 mFileType;


};
//here use class object for extern
//extern RtSa_Interface InterfaceObj;
#endif // RTSA_INTERFACE_H
