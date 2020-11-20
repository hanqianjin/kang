#ifndef RTSA_CONTROL_H
#define RTSA_CONTROL_H

#include <QObject>
#include "rtsa_aloth.h"
#include "rtsa_user_variable.h"

class RtSa_Control : public QObject
{
    Q_OBJECT
public:
    explicit RtSa_Control(QObject *parent = 0);
    ~RtSa_Control();
public:
    void setGobalVariable(RtSa_User_Variable* globalVariable);

    void setCenterFreq(qreal freq);
    qreal getCenterFreq();
    void setStartFreq(qreal freq);
    qreal getStartFreq();
    void setStopFreq(qreal freq);
    qreal getStopFreq();

    void setSpan(qreal freq);
    qreal getSpan();
    void adjustSpanFreq(qreal freq);
    void setFullSpan();
    void setCFStep(qreal freq);
    qreal getCFStep();

    void adjustAcqtime(qreal time);


    //ampt
    void amplitudeAttenControl();

    void setRefLevel(qreal refLevel);
    qreal getRefLevel(); // only return dbm reflevel
    void setAttenAuto(bool isAttenAuto);
    bool IsAttenAuto();
    void setAttenVal(qreal attenVal);
    qreal getAttenVal();
    void setAmptUnit(qint32 unitIndex);
    qint32 getAmptUint();
    void setPreAmpOn(bool IsOn);
    bool IsPreAmpOn();

    void setSingleSweep(bool isSingle); // [1] means single, [0] means cont;
    bool IsSingleSweep();

    void setDectorType(qint32 DectorType);
    qint32 getDectorType();

    void setTrigger(qint32 TriggerMode);
    qint32 getTrigger();
    void setTriggerSlope(qint32 TriggerMode, qint32 slope);
    qint32 getTriggerSlope(qint32 TriggerMode);
    void setTriggerLevel(qint32 TriggerMode, qreal level);
    qreal getTriggerLevel(qint32 TriggerMode);
    void setTriggerDelayStatus(qint32 TriggerMode, bool delayStatus);
    bool getTriggerDelayStatus(qint32 TriggerMode);
    void setTriggerDelay(qint32 TriggerMode, qreal Delay);
    qreal getTriggerDelay(qint32 TriggerMode);
    void setTriggerPeriodTime(qreal time);
    qreal getTriggerPeriodTime();
    void settriggerHoldOffTime(qint32 TriggerMode,qreal holdOffTime);
    qreal getriggerHoldOffTime(qint32 TriggerMode);

    void AdjustPeriodTime(qreal time);


    void ChangeOtherUnitTodBm(qreal refLevel);
    qreal ChangedBmToOherUnit(qreal refLevel);

    //
    void setBWAuto(bool isAuto);
    void setBW(qreal rbw);
    void setBWFFTWindow(qint32 fftwindow);

    void setAcqTime(qreal time);
    void setPersistenceInfinite(bool isInfinite);
    void setPersistenceTime(qreal time);

    //Trigger
    void setFmtType(bool isUpper);
    bool getFmtType();

    void recalFmtAxisData();



    void setDpxAmptMin();
    void setDpxAmptZoom();
    qint32 DecToBin(qreal decData, qint32 FracPrecision);

    //Albert update shm data
    void setGeneralDataToShm();

    void setMeasType(quint32 measType);

    void InitialParam(quint32 measType);

    //Albert 19/06/10
    void setHighestDensity(quint32 highest);
    void setLowestDensity(quint32 lowest);

    void setStartedFlag(quint32 flag);

    void setConfigParam();
    void setMeasureParam();
    void setTriggerParam();

    void setDpxCurve(float curve);

    void setFmtTriggerCriterion(qint32 criterion);

    void getDpxRealProbability();

signals:

public slots:

private:
    RtSa_Aloth rtsa_aloth;
    RtSa_User_Variable* globalUserVariable;
    qint32      gDector;
};

#endif // RTSA_CONTROL_H
