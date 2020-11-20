#include "rtsa_marker.h"

RtSa_Marker::RtSa_Marker(QObject *parent)
    : QObject(parent)
//    , gMarkerSelect(M1)
{
}
RtSa_Marker::~RtSa_Marker()
{
}
void RtSa_Marker::setCurBitView(BitView* bitview)
{
    mCurBitView = bitview;
    return;
}
void RtSa_Marker::setCurMarkerID(qint32 MarkerID)
{
    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;
    mCurBitView->setMarkerAttribute(BIT_MARKER_INDEX,MarkerID);
    mCurBitView->markerUpdateByFreq();
    mCurBitView->refleshmarker();
    return;
}
qint32 RtSa_Marker::getCurMarkerID()
{
    return mCurBitView->getMarkerAttribute(BIT_MARKER_INDEX);
}
void RtSa_Marker::setMarkerOn(qint32 MarkerID, bool isOn)
{
    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;
    if(isMarkerOn(MarkerID) != isOn)
    {
        mCurBitView->setMarkerAttribute(BIT_MARKER_VISIABLE,isOn,MarkerID);
        mCurBitView->markerUpdateByFreq();
        mCurBitView->refleshdisplay();
    }
//    gMarkerView[MarkerID] = isOn;
    return;
}
bool RtSa_Marker::isMarkerOn(qint32 MarkerID)
{
    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;
    return mCurBitView->getMarkerAttribute(BIT_MARKER_VISIABLE,MarkerID);
}
void RtSa_Marker::setMarkerType(qint32 MarkerID, qint32 MarkerType)
{
    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;

    if(MarkerType < RTSA_REF)
        MarkerType = RTSA_REF;
    else if(MarkerType > RTSA_DELTA_PAIR)
        MarkerType = RTSA_DELTA_PAIR;
    if(getMarkerType(MarkerID) !=  MarkerType)
    {
        mCurBitView->setMarkerAttribute(BIT_MARKER_TYPE,MarkerType,MarkerID);
        mCurBitView->markerUpdateByFreq();
        mCurBitView->refleshdisplay();
        mCurBitView->refleshmarker();
    }
//    gMarkerType[MarkerID] = MarkerType;
//    mCurBitView->setMarkerAttribute(BIT_MARKER_VISIABLE,ON);
    return;
}
qint32 RtSa_Marker::getMarkerType(qint32 MarkerID)
{
    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;
    return mCurBitView->getMarkerAttribute(BIT_MARKER_TYPE,MarkerID);
}
void RtSa_Marker::setMarkerRefFreq(qint32 MarkerID, qreal refFreq)
{
    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;
//    gMarkerRefFreq[MarkerID] = refFreq;
    mCurBitView->setMarkerFreqAttribute(BIT_MARKER_NORMAL,refFreq,MarkerID);
    mCurBitView->markerUpdateByFreq();
    mCurBitView->refleshmarker();
    mCurBitView->refleshdisplay();
    return;
}
qreal RtSa_Marker::getMarkerRefFreq(qint32 MarkerID)
{
    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;
    return mCurBitView->getMarkerFreqAttribute(BIT_MARKER_NORMAL,MarkerID);
}
void RtSa_Marker::setMarkerDeltaFreq(qint32 MarkerID, qreal DeltaFreq)
{
    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;
//    gMarkerDeltaFreq[MarkerID] = DeltaFreq;
    mCurBitView->setMarkerFreqAttribute(BIT_MARKER_DELTA,DeltaFreq,MarkerID);
    mCurBitView->markerUpdateByFreq();
    mCurBitView->refleshdisplay();
    mCurBitView->refleshmarker();
    return;
}
qreal RtSa_Marker::getMarkerDeltaFreq(qint32 MarkerID)
{
    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;
    return mCurBitView->getMarkerFreqAttribute(BIT_MARKER_DELTA,MarkerID);
}
void RtSa_Marker::setMarkerDisplay(qint32 display)
{
    if(display < RTSA_MKR_TABLE)
        display = RTSA_MKR_TABLE;
    else if(display > RTSA_MKR_OFF)
        display = RTSA_MKR_OFF;
//    gMarkerDisplay = display;
    mCurBitView->setMarkerAttribute(BIT_MARKER_DISPLAY,display);
    mCurBitView->markerUpdateByFreq();
    mCurBitView->refleshdisplay();
    mCurBitView->refleshmarker();
    return;
}
qint32 RtSa_Marker::getMarkerDisplay()
{
    return mCurBitView->getMarkerAttribute(BIT_MARKER_DISPLAY);
}
void RtSa_Marker::setMarkerNoiseOn(qint32 MarkerID, bool isOn)
{
    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;
//    gMarkerNoise[MarkerID] = isOn;
    mCurBitView->setMarkerAttribute(BIT_MARKER_NOISE,isOn,MarkerID);
    mCurBitView->markerUpdateByFreq();
    mCurBitView->refleshmarker();
    mCurBitView->refleshdisplay();
    return;
}
bool RtSa_Marker::IsMarkerNoiseOn(qint32 MarkerID)
{
    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;
    return mCurBitView->getMarkerAttribute(BIT_MARKER_NOISE,MarkerID);
}
qreal RtSa_Marker::getMarkerRefAmpt(qint32 MarkerID)
{
    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;
    return mCurBitView->getMarkerInfo(BIT_MARKER_NORMAL,MarkerID);
}
qreal RtSa_Marker::getMarkerDeltaAmpt(qint32 MarkerID)
{
    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;
    return mCurBitView->getMarkerInfo(BIT_MARKER_DELTA,MarkerID);
}
qreal RtSa_Marker::getMarkerNoiseAmpt(qint32 MarkerID)
{
    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;
    return mCurBitView->getMarkerInfo(BIT_MARKER_NOISE,MarkerID);
}
qreal RtSa_Marker::getMarkerCurFreq(qint32 Type)
{
    return mCurBitView->getMarkerCurrentFreq(Type);
}
qreal RtSa_Marker::getMarkerAmptInfo(qint32 Type)
{
    return mCurBitView->getMarkerAmptInfo(Type);
}
void RtSa_Marker::setMarkerRefFreqIndex(qint32 MarkerID, qint32 index)
{
    mCurBitView->setMarkerFreqAttribute(BIT_MARKER_NORMAL_INDEX,index,MarkerID);
    mCurBitView->markerUpdateByFreq();
    mCurBitView->refleshmarker();
    mCurBitView->refleshdisplay();
    return;
}
qint32 RtSa_Marker::getMarkerRefFreqIndex(qint32 MarkerID)
{
    return mCurBitView->getMarkerFreqAttribute(BIT_MARKER_NORMAL_INDEX,MarkerID);
}
void RtSa_Marker::setMarkerDeltaFreqIndex(qint32 MarkerID, qint32 index)
{
    mCurBitView->setMarkerFreqAttribute(BIT_MARKER_DELTA_INDEX,index,MarkerID);
    mCurBitView->markerUpdateByFreq();
    mCurBitView->refleshmarker();
    mCurBitView->refleshdisplay();
    return;
}
qint32 RtSa_Marker::getMarkerDeltaFreqIndex(qint32 MarkerID)
{
    return mCurBitView->getMarkerFreqAttribute(BIT_MARKER_DELTA_INDEX,MarkerID);
}
QString RtSa_Marker::getmarkerInfoStr(qint32 MarkerID)
{
    if(MarkerID < RTSA_M1)
        MarkerID = RTSA_M1;
    else if(MarkerID > RTSA_M6)
        MarkerID = RTSA_M6;
    if(getMarkerType(MarkerID) == RTSA_REF)
    {
        return mCurBitView->getMarkerInfoStr(BIT_MARKER_NORMAL,MarkerID);
    }
    else
    {
        return mCurBitView->getMarkerInfoStr(BIT_MARKER_DELTA,MarkerID);
    }
}

qreal RtSa_Marker::setMarkerToPeak()
{
    qreal maxValue = 0.0;
    maxValue = mCurBitView->MarkerToPeak();
    mCurBitView->refleshmarker();
    mCurBitView->refleshdisplay();
    return maxValue;
}
void RtSa_Marker::setMarkerToNextPeak()
{
    mCurBitView->MarkerToNextPeak();
    mCurBitView->refleshmarker();
    mCurBitView->refleshdisplay();
    return;
}
void RtSa_Marker::setMarkerToLeftPeak()
{
    mCurBitView->MarkerToLeftPeak();
    mCurBitView->refleshmarker();
    mCurBitView->refleshdisplay();
    return;
}
void RtSa_Marker::setMarkerToRightPeak()
{
    mCurBitView->MarkerToRightPeak();
    mCurBitView->refleshmarker();
    mCurBitView->refleshdisplay();
    return;
}
void RtSa_Marker::setMarkerToMin()
{
    mCurBitView->MarkerToMin();
    mCurBitView->refleshmarker();
    mCurBitView->refleshdisplay();
    return;
}
