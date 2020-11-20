#ifndef SA_MEASURE_CONTROL_H
#define SA_MEASURE_CONTROL_H

#include "sa_user_variable.h"
#include "sa_user_limit.h"
#include "sa_parasaveload.h"

class sa_Measure_Control
{
public:
    sa_Measure_Control(user_variable &m_user_variable,user_limit &m_user_limit);
    ~sa_Measure_Control();

    user_variable *globalUserVariable;
    user_limit    *globalUserLimit;
    paraSaveLoad  *pparaSaveLoad;
private:
    quint64 uOccBW;
    quint64 uXdBBW;
    qreal dTotalPower;
    qreal   gTraceAverage[NUM_SWEEP_POINT];
    qreal   gTraceNumber;
public:
    qint32 leftPos,rightPos;
public:
    void initVariable();
    qreal caculateTotalPower();
    qreal calculatePower(qint32 startx, qint32 horWidth, qint32 gridWidth, qreal pixelStep, qint64 bandwidth);
    quint64 caculateOccBW();
    quint64 caculateXdBBW();
    quint64 calculateOccupiedBW(qint32 &leftDotIndex, qint32 &rightDotIndex, qreal dTotalPower, qint32 mode, qreal *data, qint32 num, qreal dValue);//return SA_BW
    qint32 calibrateLeftDotIndex(qint32 peakPos,qreal searchPower,qreal leftPower,qreal *data,qreal powerValue);
    qint32 calibrateRightDotIndex(qint32 peakPos,qint32 num,qreal searchPower,qreal rightPower,qreal *data,qreal powerValue);

    void calAverageData();

    void calculateLeftRightDotPos(qint32 &leftDotIndex, qint32 &rightDotIndex, qint32 peakPos, qreal searchPowerValue, qreal *data, qint32 num);
};

#endif // SA_MEASURE_CONTROL_H
