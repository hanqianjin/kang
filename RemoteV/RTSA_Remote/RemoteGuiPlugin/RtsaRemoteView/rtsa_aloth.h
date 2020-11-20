#ifndef RTSA_ALOTH_H
#define RTSA_ALOTH_H

#include <QObject>
#include "rtsa_user_variable.h"


typedef struct
{
    double r;
    double d;
    double feedback;
    double iffreq;

} RTSA_LO_FREQ_DIV; /*calc differ seg freq div values*/

class RtSa_Aloth : public QObject
{
    Q_OBJECT
public:
    explicit RtSa_Aloth(QObject *parent = 0);
    ~RtSa_Aloth();
public:
    void setGobalVariable(RtSa_User_Variable* globalVariable);


    int GetFreqChannelIndex(double freqHz);
    void GetSegmentWaveIndex(void* param) ;
    int ConfigureFrequencyStartStop (double startFrequency,double stopFrequency);
    void RefCalSweepParams(int sweepMode);
    int GetrbwIndex(double rbwHz);
    int GetFftRbwIndex();

    //steve,0522,lin jie dian belong to former or later,add a param,later belong to qian,starter belong to hou duan
    void GetFreqDivValue(double freqHz,unsigned int* intdiv,unsigned int* fracdiv);
    int ConfigureSweepCoupling (unsigned int resolutionBandwidthAuto,double resolutionBandwidth,unsigned int videoBandwidthAuto,double videoBandwidth,unsigned int vbwtorbwAuto,double vbwtorbwValue);
    void ParamConvertByRbw(int iIndex);
    void GetLastPartTime(int iIndex);

    //by Steve,20180328
    void GetStepFrqDivValue(double startfreq,double stepHz,unsigned int* lowbits,unsigned int* highbits);

    //steve 0716 man setting sweep times
//    void SettingSweepTimeManmode(double sweeptimems, double autotimems);

    //steve 0718 zero span mode vari rbw's min time ms
//    double GetZeroSpanRbwMinms(unsigned int tracenums);
//    void GetZeroShmTimes(double timems, unsigned int tracenum);
signals:

public slots:


private:
    RtSa_User_Variable* globalUserVariable;
};

#endif // RTSA_ALOTH_H
