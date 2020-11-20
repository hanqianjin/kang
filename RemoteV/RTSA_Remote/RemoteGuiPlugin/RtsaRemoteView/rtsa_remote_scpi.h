/**************Copyright (c)**************************************
 **
 **               INNO Instrument(China) Co.,Ltd.
 **
 **------------File Info------------------------------------------
 **Class name:              resaremote
 **Latest Version:          V1.0.0
 **Latest modified Date:
 **Created by:              ROC
 **Created date:            2019/10/18
 **Descriptions:            RTSA Remote SCPI
 **
 *****************************************************************/


#ifndef RTSA_REMOTE_SCPI_H
#define RTSA_REMOTE_SCPI_H

#include <QObject>
#include "rtsa_user_variable.h"

class RtSa_Remote_Scpi : public QObject
{
    Q_OBJECT
public:

    explicit RtSa_Remote_Scpi(QObject *parent = 0);
    ~RtSa_Remote_Scpi();
public:   //频率 Frequency
    void SetCenterFreq(qreal freq);
    void getCenterFreq();

    void setStartFreq(qreal freq);
    void getStartFreq();

    void setStopFreq(qreal freq);
    void getStopFreq();

    void setSpan(qreal freq);
    void getSpan();

    void setFullSpan();

    void setCFStep(qreal freq);
    void getStepFreq();

    void setFreqOffset(qreal freq);
    void getFreqOffset();

    void setCHStandard(qint32 index);
    void getCHStandard();

    void setBandIndex(qint32 bandIndex);
    void getBandIndex();

    void setChannelType(qint32 direction);
    void getChannelType();

    void setChannelNumber(qint32 number);
    void getChannelNumber();

    //幅度 Amplitude
    void setAutoScale();

    void setRefLevel(qreal refLevel);
    void getRefLevel(); // only return dbm reflevel

    void setScaleDiv(qreal scaleDiv);
    void getScaleDiv();

    void setAttenAuto(bool isAttenAuto);
    void IsAttenAuto();

    void setAttenVal(qreal attenVal);
    void getAttenVal();

    void setPreAmpOn(bool IsOn);
    void IsPreAmpOn();

    void setRefOffset(qreal refOffset);
    void getRefOffset();

    void setAmptUnit(qint32 unitIndex);
    void getAmptUint();

    //扫描 Sweep
    void setSingleSweep(bool isSingle); // [1] means single, [0] means cont;
    void IsSingleSweep();

    void setAcqTimeAuto(bool isAuto);
    void IsAcqTimeAuto();

    void setAcqTime(qreal time);
    void getAcqTime();

    //带宽 BandWidth
    void setBWAuto(bool isAuto);
    void IsBWAuto();

    void setBWIndex(qreal rbw);
    void getBWIndex();

    void setBWFFTWindow(qint32 fftwindow);
    void getFFTWindow();


    //触发 Trigger
    void setTrigger(qint32 TriggerMode);
    void getTrigger();

    void setTriggerLevel(qint32 TriggerMode,qreal level);
    void getTriggerLevel(qint32 TriggerMode);

    void setTriggerSlope(qint32 TriggerMode, qint32 slope);
    void getTriggerSlope(qint32 TriggerMode);

    void setTriggerDelayStatus(qint32 TriggerMode, bool delayStatus);
    void getTriggerDelayStatus(qint32 TriggerMode);

    void setTriggerDelay(qint32 TriggerMode, qreal Delay);
    void getTriggerDelay(qint32 TriggerMode);

    void setTriggerPeriodTime(qreal time);
    void getTriggerPeriodTime();

    void settriggerHoldOffTime(qint32 TriggerMode, qreal holdOffTime);
    void getriggerHoldOffTime(qint32 TriggerMode);

    //FMT trigger

    void BuildFmtFromTrace();
    void DeleteAllFmtMask();

    void setFmtType(qint32 Upper);
    void getFmtType();

    void setFmtTriggerCriterion(qint32 criterion);
    void getFmtTriggerCriterion();

    void setFmtDataNum(qint32 dataNum);
    void getFmtDataNum();

    void setCurFmtFreqData(qreal data, qint32 index);
    void getCurFmtFreqData(qint32 index);

    void setCurFmtAmptData(qreal data, qint32 index);
    void getCurFmtAmptData(qint32 index);

    void InsertFmtDataRow();

    //迹线 Trace
    void setTraceViewStatus(bool status,qint32 traceID);
    void getTraceViewStatus(qint32 traceID = -1);

    void setCurTraceType(qint32 traceType,qint32 traceID);
    void getCurTraceType(qint32 traceID);

    void setCurTraceAvgNum(qint32 Num,qint32 traceID);
    void getCurTraceAvgNum(qint32 traceID);

    void setDectorType(qint32 DectorType);
    void getDectorType();

    void GetCurTraceData();
    void getDpxData();

    //光标 Marker
    void setCurMarkerID(qint32 MarkerID);
    void getCurMarkerID();

    void setMarkerOn(qint32 MarkerID,bool isOn);
    void isMarkerOn(qint32 MarkerID);

    void setMarkerType(qint32 MarkerID,qint32 MarkerType);
    void getMarkerType(qint32 MarkerID);

    void setMarkerToCenter();

    void setMarkerToStart();

    void setMarkerToStop();

    void setMarkerToPeak();
    void setMarkerToMin();
    void setMarkerToNextPeak();
    void setMarkerToLeftPeak();
    void setMarkerToRightPeak();

    void setPeakTrackOn(bool PeakTrackOn);
    void IsPeakTrackOn();

    void setMarkerRefFreq(qint32 MarkerID,qreal refFreq);
    void getMarkerRefFreq(qint32 MarkerID);

    void setMarkerNoiseOn(qint32 MarkerID, bool isOn);
    void IsMarkerNoiseOn(qint32 MarkerID);


    // 极限线 Limit
    void setCurLimit(qint32 curIndex);
    void getCurLimit();

    void setCurLimitOn(qint32 LimitID,bool isOn);
    void IsCurLimitOn(qint32 LimitID);

    void setMarginOn(qint32 LimitID,bool isOn);
    void IsMarginOn(qint32 LimitID);

    void setMargin(qint32 LimitID,qreal margin);
    void getMargin(qint32 LimitID);

    void setLimitTestOn(bool isOn);
    void IsLimitTestOn();

    void setLimitType(qint32 LimitID,qint32 nType);
    void getLimitType(qint32 LimitID);

    void DeleteLimitLine(qint32 LimitID);

    void BuildLimitFromTrace();
    void getLimitDataNum(qint32 LimitID);

    void setLimitCurPointFreq(qreal pData, qint32 curPos, qint32 limitID);
    void getLimitCurPointFreq(qint32 curPos, qint32 limitID);

    void setLimitCurPointAmpt(qreal pData, qint32 curPos, qint32 limitID);

    void getLimitCurPointAmpt(qint32 curPos, qint32 limitID);


    void InsertLimitRow(qint32 limitSelect);
    //显示 Display
    void setDisplay(qint32 disPlayMode);
    void getDisplay();

    //显示设置 Setup
    void setPersistenceInfinite(bool isInfinite);
    void IsPersistenceTimeInfinite();

    void setPersistenceTime(qreal time);
    void getPersistenceTime();

    void setHighestDensity(quint32 highest);
    void getHighestDensity();

    void setLowestDensity(quint32 lowest);
    void getLowestDensity();

    void setDpxCurve(float curve);
    void getCurve();

    void setDensityLevelAjust();


signals:
    void sendSCPIcmd(QString cmd);
    void sendScpiAndRecv(QString cmd);

public slots:
};

#endif // RTSA_REMOTE_SCPI_H
