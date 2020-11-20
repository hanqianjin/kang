/**************Copyright (c)**************************************
 **
 **               INNO Instrument(China) Co.,Ltd.
 **
 **------------File Info------------------------------------------
 **Class name:              RtSa_Marker
 **Latest Version:          V1.0.0
 **Latest modified Date:
 **Created by:              Albert
 **Created date:            2018/12/13
 **Descriptions:            RTSA marker param control class
 **
 *****************************************************************/
#ifndef RTSA_MARKER_H
#define RTSA_MARKER_H

#include <QObject>
//#include "define.h"
#include "rtsa_define.h"
#include "bitview.h"

class RtSa_Marker : public QObject
{
    Q_OBJECT
public:
    explicit RtSa_Marker(QObject *parent = 0);
    ~RtSa_Marker();
public:
    void setCurBitView(BitView* bitview);
    void setCurMarkerID(qint32 MarkerID);
    qint32 getCurMarkerID();
    void setMarkerOn(qint32 MarkerID,bool isOn);
    bool isMarkerOn(qint32 MarkerID);
    void setMarkerType(qint32 MarkerID,qint32 MarkerType);
    qint32 getMarkerType(qint32 MarkerID);
    void setMarkerRefFreq(qint32 MarkerID, qreal refFreq);
    qreal getMarkerRefFreq(qint32 MarkerID);
    void setMarkerDeltaFreq(qint32 MarkerID,qreal DeltaFreq);
    qreal getMarkerDeltaFreq(qint32 MarkerID);
    void setMarkerDisplay(qint32 display);
    qint32 getMarkerDisplay();
    void setMarkerNoiseOn(qint32 MarkerID, bool isOn);
    bool IsMarkerNoiseOn(qint32 MarkerID);

    qreal getMarkerRefAmpt(qint32 MarkerID);
    qreal getMarkerDeltaAmpt(qint32 MarkerID);
    qreal getMarkerNoiseAmpt(qint32 MarkerID);

    qreal getMarkerCurFreq(qint32 Type);
    qreal getMarkerAmptInfo(qint32 Type);

    void setMarkerRefFreqIndex(qint32 MarkerID,qint32 index);
    void setMarkerDeltaFreqIndex(qint32 MarkerID,qint32 index);
    qint32 getMarkerRefFreqIndex(qint32 MarkerID);
    qint32 getMarkerDeltaFreqIndex(qint32 MarkerID);

    QString getmarkerInfoStr(qint32 MarkerID);

    qreal setMarkerToPeak();
    void setMarkerToNextPeak();
    void setMarkerToLeftPeak();
    void setMarkerToRightPeak();
    void setMarkerToMin();


signals:

public slots:
private:
    BitView*    mCurBitView;
};

#endif // RTSA_MARKER_H
