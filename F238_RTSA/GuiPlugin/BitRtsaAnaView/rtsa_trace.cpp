#include "rtsa_trace.h"
#include <QDebug>
RtSa_Trace::RtSa_Trace(QObject *parent)
    : QObject(parent)
    , mCurBitView(NULL)
    , mDisplay(RTSA_SPECTRUM_SPECTROGRAM)
    , gTraceSelect(RTSA_TR1)
{
}
RtSa_Trace::~RtSa_Trace()
{
    mCurBitView = NULL;
}
void RtSa_Trace::updateTraceData(qreal *pTraceData, qint32 TraceNum)
{
//    for(qint32 i= 0; i < TraceNum; i++)
//    {
//        gOriginalTrace[i] = pTraceData[i];
//    }
    memcpy(gOriginalTrace,pTraceData,TraceNum * sizeof(qreal));
}
void RtSa_Trace::updateDpxData(quint32 *pTraceData, qint32 TraceNum)
{
    gDpxData = pTraceData;
    gDpxDataNum = TraceNum;
    return;
}
void RtSa_Trace::setCurBitView(BitView *bitview)
{
    mCurBitView = bitview;
}
void RtSa_Trace::initDrawBitview(qint32 index, BitView *bitview)
{
    mBitView[index] = bitview;
//    mCurBitViewType = mDrawBitView->getBitviewType();
}
void RtSa_Trace::setDisplay(qint32 mode)
{
    mDisplay = mode;
}
void RtSa_Trace::draw()
{
    for(qint32 i = 0; i < RTSA_BITVIEWNUM; i++)
    {
        if(gWinCtrlList[mDisplay][i] == RTSA_SPECTROGRAM + 1)
        {
            mBitView[i]->showFalltrom(gOriginalTrace,RTSA_NUM_SWEEP_POINT);
        }
        else if(gWinCtrlList[mDisplay][i] == RTSA_SPECTRUM_SPECTROGRAM + 1)
        {
            mBitView[i]->showSigLine(gOriginalTrace,RTSA_NUM_SWEEP_POINT);
        }
        else if(gWinCtrlList[mDisplay][i] == RTSA_DENSITY + 1)
        {
            if(gDpxData == NULL)
            {
                mBitView[i]->showSigLine(gOriginalTrace,RTSA_NUM_SWEEP_POINT);
            }
            else
            {
                mBitView[i]->showDensity(gOriginalTrace,gDpxData,RTSA_NUM_SWEEP_POINT,RTSA_NUM_SWEEP_POINT,201);
            }
        }
    }
    return;
}
void RtSa_Trace::drawlines()
{
//    mDrawBitView->showSigLine(gOriginalTrace,NUM_SWEEP_POINT);
    return;
}
void RtSa_Trace::drawFall()
{
//    mDrawBitView->showFalltrom(gOriginalTrace,NUM_SWEEP_POINT);
    return;
}
/**
 * @brief search the max Amplitude
 * @return Max Amplitude
 */
qreal RtSa_Trace::searchMaxAmplitude()
{
    qreal* renderData = gOriginalTrace;//GetTraceData(RTSA_NUM_SWEEP_POINT,gTraceSelect);
    qreal AMax = renderData[0];
    for (qint32 k = 1; k < RTSA_NUM_SWEEP_POINT; k++) {
        if (AMax < renderData[k]) {
            AMax = renderData[k];
        }
    }
    return AMax;
}

/**
 * @brief search the Min Amplitude
 * @return Min Amplitude
 */
qreal RtSa_Trace::searchMinAmplitude()
{
    qreal* renderData = gOriginalTrace;//GetTraceData(RTSA_NUM_SWEEP_POINT,gTraceSelect);
    qreal AMin = renderData[0];
    for (qint32 k = 1; k < RTSA_NUM_SWEEP_POINT; k++) {
        if (AMin > renderData[k]) {
            AMin = renderData[k];
        }
    }
    return AMin;
}
/**
 * @brief RtSa_Trace::setCurTrace
 * @param traceID
 */
void RtSa_Trace::setCurTrace(qint32 traceID)
{
    if(traceID < RTSA_TR1)
        traceID = RTSA_TR1;
    else if(traceID > RTSA_TR6)
        traceID = RTSA_TR6;

    gTraceSelect = traceID;
    mCurBitView->setTraceAttribute(traceID,BIT_TRACE_INDEX,traceID);
    return;
}
/**
 * @brief RtSa_Trace::getCurTrace
 * @return
 */
qint32 RtSa_Trace::getCurTrace()
{
    return mCurBitView->getTraceAttribute(0,BIT_TRACE_INDEX);
}
void RtSa_Trace::setTraceOn(qint32 traceID, bool isTraceOn)
{
    if(traceID < RTSA_TR1)
        traceID = RTSA_TR1;
    else if(traceID > RTSA_TR6)
        traceID = RTSA_TR6;

    if(!isTraceOn)
    {
         mCurBitView->setTraceAttribute(traceID,BIT_TRACE_TYPE_ATTR,RTSA_TRACE_OFF);
    }
    else {
        mCurBitView->setTraceAttribute(traceID,BIT_TRACE_TYPE_ATTR,RTSA_CLEAR_WRITE);
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-11-01
*/
bool RtSa_Trace::IsTraceOn(qint32 traceID)
{
    qint32 isTraceOn = false;
    if(traceID < RTSA_TR1)
        traceID = RTSA_TR1;
    else if(traceID > RTSA_TR6)
        traceID = RTSA_TR6;
    isTraceOn = mCurBitView->getTraceAttribute(traceID,BIT_TRACE_TYPE_ATTR);
    if(isTraceOn != RTSA_TRACE_OFF)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void RtSa_Trace::setTraceType(qint32 traceID, qint32 traceType)
{
    if(traceID < RTSA_TR1)
        traceID = RTSA_TR1;
    else if(traceID > RTSA_TR6)
        traceID = RTSA_TR6;

    //if type not change, do not set
    if(mCurBitView->getTraceAttribute(traceID,BIT_TRACE_TYPE_ATTR) == traceType)
        return;

    if(traceType < RTSA_CLEAR_WRITE)
        traceType = RTSA_CLEAR_WRITE;
    else if(traceType > RTSA_AVERAGE)
        traceType = RTSA_AVERAGE;
    mCurBitView->setTraceAttribute(traceID,BIT_TRACE_TYPE_ATTR,traceType);
    mCurBitView->refreshSepectrogramRect();
    if(traceType == RTSA_AVERAGE)
    {
        setAvgOn(traceID,true);
    }
    else
    {
        setAvgOn(traceID,false);
    }
    mCurBitView->refleshdisplay();
    return;
}
qint32 RtSa_Trace::getTraceType(qint32 traceID)
{
    if(traceID < RTSA_TR1)
        traceID = RTSA_TR1;
    else if(traceID > RTSA_TR6)
        traceID = RTSA_TR6;
    return mCurBitView->getTraceAttribute(traceID,BIT_TRACE_TYPE_ATTR);
}
void RtSa_Trace::setAvgOn(qint32 traceID, bool isOn)
{
    if(traceID < RTSA_TR1)
        traceID = RTSA_TR1;
    else if(traceID > RTSA_TR6)
        traceID = RTSA_TR6;
    //if type not change, do not set
    if(mCurBitView->getTraceAttribute(traceID,BIT_AVAG_ATTR) == isOn)
        return;

    mCurBitView->setTraceAttribute(traceID,BIT_AVAG_ATTR,isOn);
    mCurBitView->setTraceAttribute(traceID,BIT_AVAG_NUM_ATTR,getAvgNum(traceID));
    return;
}
bool RtSa_Trace::IsAvgOn(qint32 traceID)
{
    if(traceID < RTSA_TR1)
        traceID = RTSA_TR1;
    else if(traceID > RTSA_TR6)
        traceID = RTSA_TR6;
    return mCurBitView->getTraceAttribute(traceID,BIT_AVAG_ATTR);
}
void RtSa_Trace::setAvgNum(qint32 traceID, qint32 Num)
{
    if(traceID < RTSA_TR1)
        traceID = RTSA_TR1;
    else if(traceID > RTSA_TR6)
        traceID = RTSA_TR6;
    Num = Num <= 0 ? 1 : Num;
    Num = Num > 70000 ? 70000 : Num;
//    gAverageCount[traceID] = Num;
//    mCurBitView->setTraceAttribute(traceID,BIT_AVAG_ATTR,gTraceAverage[traceID]);
    mCurBitView->setTraceAttribute(traceID,BIT_AVAG_NUM_ATTR,Num);
    return;
}
qint32 RtSa_Trace::getAvgNum(qint32 traceID)
{
    if(traceID < RTSA_TR1)
        traceID = RTSA_TR1;
    else if(traceID > RTSA_TR6)
        traceID = RTSA_TR6;
    return mCurBitView->getTraceAttribute(traceID,BIT_AVAG_NUM_ATTR);
}
qint32 RtSa_Trace::getCurAvgNum(qint32 traceID)
{
    if(traceID < RTSA_TR1)
        traceID = RTSA_TR1;
    else if(traceID > RTSA_TR6)
        traceID = RTSA_TR6;
    qint32 AvgNum = mCurBitView->getTraceAttribute(traceID,BIT_AVAG_NUM_ATTR);
    qint32 CurAvgNum = mCurBitView->getTraceAttribute(traceID,BIT_AVAG_NOW_NUM_ATTR);
    if(CurAvgNum > AvgNum)
    {
        CurAvgNum = AvgNum;
    }
    return CurAvgNum;
}
void RtSa_Trace::getRawTraceData(char *dest)
{
    memcpy(dest,gOriginalTrace,sizeof(qreal)*RTSA_NUM_SWEEP_POINT);
    return;
}
void RtSa_Trace::GetAllTraceData(char* dest)
{
    for(qint32 i = RTSA_TR1; i <= RTSA_TR6; i++)
    {
        mCurBitView->getTraceRenderData(gTraceData,RTSA_TRACE_DATA_NUM,i);
        memcpy((char*)dest + i * sizeof(qreal)*RTSA_NUM_SWEEP_POINT,gTraceData,sizeof(qreal)*RTSA_NUM_SWEEP_POINT);
    }
    return;
}
qreal* RtSa_Trace::GetTraceData(qint32 dataNum, qint32 traceID)
{
    if(traceID < RTSA_TR1)
        traceID = RTSA_TR1;
    else if(traceID > RTSA_TR6)
        traceID = RTSA_TR6;
    mCurBitView->getTraceRenderData(gTraceData,dataNum,traceID);
    return gTraceData;
}
void RtSa_Trace::setTraceData(qreal *pData, qint32 dataNum, qint32 traceID)
{
    if(traceID < RTSA_TR1)
        traceID = RTSA_TR1;
    else if(traceID > RTSA_TR6)
        traceID = RTSA_TR6;
    mCurBitView->setTraceRenderData(pData,dataNum,traceID);
}

uchar* RtSa_Trace::GetDensityData(qint32 dataNum)
{
    uchar* pData;
    for(qint32 i = 0; i < RTSA_BITVIEWNUM; i++)
    {
        if(mBitView[i]->getBitviewType() == BIT_DENSITY)
        {
            pData = mBitView[i]->getDensityData(dataNum);
            break;
        }
        else
        {
            pData = mBitView[i]->getDensityData(dataNum);
        }
    }
    return pData;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-03
*/
void RtSa_Trace::SetDensityData(qreal* pTraceData,uchar *pData)
{
    for(qint32 i = 0; i < RTSA_BITVIEWNUM; i++)
    {
        if(mBitView[i]->getBitviewType() == BIT_DENSITY)
        {
            mBitView[i]->setDensityData(pTraceData,pData);
            break;
        }
    }
   return;
}
