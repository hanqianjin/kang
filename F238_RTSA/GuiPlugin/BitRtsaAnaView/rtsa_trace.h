/**************Copyright (c)**************************************
 **
 **               INNO Instrument(China) Co.,Ltd.
 **
 **------------File Info------------------------------------------
 **Class name:              RtSa_Trace
 **Latest Version:          V1.0.0
 **Latest modified Date:
 **Created by:              Albert
 **Created date:            2018/12/13
 **Descriptions:            RTSA trace param control class
 **
 *****************************************************************/
#ifndef RTSA_TRACE_H
#define RTSA_TRACE_H

#include <QObject>
#include "bitview.h"
//#include "define.h"
#include "rtsa_define.h"
class RtSa_Trace : public QObject
{
    Q_OBJECT
public:
    explicit RtSa_Trace(QObject *parent = 0);
    ~RtSa_Trace();
public:
    void setCurBitView(BitView *bitview);
    void initDrawBitview(qint32 index,BitView *bitview);
    void setDisplay(qint32 mode);
    void draw();
    void drawlines();
    void drawFall();
    void updateTraceData(qreal* pTraceData, qint32 TraceNum);
    void updateDpxData(quint32* pTraceData, qint32 TraceNum);
    qreal searchMaxAmplitude();
    qreal searchMinAmplitude();

    void setCurTrace(qint32 traceID);
    qint32 getCurTrace();
    void setTraceOn(qint32 traceID,bool isTraceOn);
    bool IsTraceOn(qint32 traceID);
    void setTraceType(qint32 traceID,qint32 traceType);
    qint32 getTraceType(qint32 traceID);
    void setAvgOn(qint32 traceID,bool isOn);
    bool IsAvgOn(qint32 traceID);
    void setAvgNum(qint32 traceID,qint32 Num);
    qint32 getAvgNum(qint32 traceID);
    qint32 getCurAvgNum(qint32 traceID);

    //READOUT
    void getRawTraceData(char *dest);
    void GetAllTraceData(char *dest);
    qreal* GetTraceData(qint32 dataNum, qint32 traceID);
    uchar *GetDensityData(qint32 dataNum);
    void SetDensityData(qreal* pTraceData, uchar* pData);
    //WRITEIN
    void setTraceData(qreal* pData,qint32 dataNum, qint32 traceID);


signals:

public slots:
public:
    qreal   gOriginalTrace[RTSA_NUM_SWEEP_POINT];
private:
    BitView* mCurBitView;
    BitView* mBitView[RTSA_BITVIEWNUM];  // only for draw use
    qreal    gTraceData[RTSA_NUM_SWEEP_POINT];
    qint32   mDisplay;
    qint32   gTraceSelect;
    qint32   gTraceType[RTSA_NUM_TRACE];
    quint32* gDpxData;
    quint32  gDpxDataNum;
};
#endif // RTSA_TRACE_H
