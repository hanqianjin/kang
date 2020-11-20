#ifndef SA_AMPLITUDE_CONTROL_H
#define SA_AMPLITUDE_CONTROL_H

#include "sa_user_variable.h"
#include "sa_user_limit.h"

class sa_Amplitude_Control
{
public:
    sa_Amplitude_Control(user_variable &m_user_variable,user_limit &m_user_limit);
    ~sa_Amplitude_Control();

    user_variable *globalUserVariable;
    user_limit    *globalUserLimit;
public:
    void AmplitudeAttenControl();
    void AutoAttenTrackControl();
    qreal searchMaxAmplitude();
    qreal searchMinAmplitude();
    void setRefLevelRelativePara(qreal &topLevel,qreal &lowLevel);
    void setScalDivRelativePara(qreal &topLevel,qreal &lowLevel);
    void setAmptUnit(qint32 ampUnit);
    void setRefOffsetRelativePara(qreal &topLevel,qreal &lowLevel);
};

#endif // SA_AMPLITUDE_CONTROL_H
