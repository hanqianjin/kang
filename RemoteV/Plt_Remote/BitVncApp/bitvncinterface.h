#ifndef BITVNCINTERFACE_H
#define BITVNCINTERFACE_H
#include <QObject>

class bitvncinterface
{
public:
    bitvncinterface();
    //Freq
    void SetCenterFreq(qreal mFreqHz);
    qreal GetCenterFreq();

    void SetStartFreq(qreal mFreqHz);
    qreal GetStartFreq(qreal mFreqHz);


    void SetStopFreq(qreal mFreqHz);
    qreal GetStopFreq(qreal mFreqHz);

    //Ampt

    //Sweep

    //BW
    void SetAutoRbwStatus(qint32 IsAuto);
    qint32 GetRbwStatus();

    void SetRbwValue(quint32 mFreqHz);
    quint64 GetRbwValue();

    void SetAutoVbwStatus(qint32 IsAuto);
    quint32 GetVbwStatus();

    void SetVbwValue(quint32 uVbwValues);
    quint64 GetVbwValue();

    void SetVbwtoRbw(quint32 mFreqHz);
    qreal GetVbwtoRbw();



    //IF Output
    void SetIFOutPut(qint32 uifMode);
    qint32 GetIFOutPut();


    //Trigger

    //Maker

    //Limit

    //Measure

    //Measure setup
};

#endif // BITVNCINTERFACE_H
