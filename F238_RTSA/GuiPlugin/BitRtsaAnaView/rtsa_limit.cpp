#include "rtsa_limit.h"
//#include "define.h"
#include "rtsa_define.h"

RtSa_Limit::RtSa_Limit(QObject *parent)
    : QObject(parent)
    , mCurBitViewType(RTSA_SPECTRUM_SPECTROGRAM)
    , gLimitNum(0)
//    , gLimitTest(OFF)
{
    memset(&gLimitFreq,0,sizeof(gLimitFreq));
    memset(&gLimitAmpt,0,sizeof(gLimitAmpt));

//    memset(&gCurLimitFreq,0,sizeof(gCurLimitFreq));
//    memset(&gCurLimitFreq,0,sizeof(gCurLimitFreq));
//    memset(&gMargin,0,sizeof(gMargin));
//    memset(&gLimitType,UPPER,sizeof(gLimitType));
}
RtSa_Limit::~RtSa_Limit()
{
}
void RtSa_Limit::setCurBitView(BitView *bitview)
{
    mCurBitView = bitview;
    mCurBitViewType = mCurBitView->getBitviewType();
    return;
}

void RtSa_Limit::setCurLimit(qint32 curLimitID)
{
//    if(gLimitSelect == curLimitID)
//        return;
    if(curLimitID < RTSA_LIMIT1)
        curLimitID = RTSA_LIMIT1;
    else if(curLimitID >RTSA_LIMIT6)
        curLimitID =RTSA_LIMIT6;
//    gLimitSelect = curLimitID;
    mCurBitView->setLimitAttribute(BIT_LIMIT_INDEX,curLimitID);
    return;

}
qint32 RtSa_Limit::getCurLimit()
{
    return mCurBitView->getLimitAttribute(BIT_LIMIT_INDEX);
}
void RtSa_Limit::setCurLimitOn(qint32 LimitID, bool isOn)
{
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;
//    gLimitLine[LimitID] = isOn;
    mCurBitView->setLimitAttribute(BIT_LIMIT_VIEW,isOn,LimitID);
    mCurBitView->refleshdisplay();
    return;
}
bool RtSa_Limit::IsCurLimitOn(qint32 LimitID)
{
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;
    return mCurBitView->getLimitAttribute(BIT_LIMIT_VIEW,LimitID);
}
void RtSa_Limit::setLimitTestOn(bool isOn)
{
//    gLimitTest = isOn;
    mCurBitView->setLimitAttribute(BIT_LIMIT_TEST,isOn);
    mCurBitView->refleshdisplay();
    return;
}
bool RtSa_Limit::IsLimitTestOn()
{
    return mCurBitView->getLimitAttribute(BIT_LIMIT_TEST);
}
void RtSa_Limit::setMarginOn(qint32 LimitID, bool isOn)
{
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;
//    gMarginOn[LimitID] = isOn;
    mCurBitView->setLimitAttribute(BIT_LIMIT_MARGIN,isOn,LimitID);
    mCurBitView->refleshdisplay();
    return;
}
bool RtSa_Limit::IsMarginOn(qint32 LimitID)
{
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;
    return mCurBitView->getLimitAttribute(BIT_LIMIT_MARGIN,LimitID);
}
void RtSa_Limit::setMargin(qint32 LimitID, qreal margin)
{
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;
    if(margin > RTSA_LIMIT_EDGE_MAX)
        margin = RTSA_LIMIT_EDGE_MAX;
    else if(margin < 0)
        margin = 0;
//    gMargin[LimitID] = margin;
//    mCurBitView->setLimitAttribute(BIT_LIMIT_MARGIN,ON,LimitID);
    mCurBitView->setLimitAttribute(BIT_LIMIT_MARGIN,true,LimitID);
    mCurBitView->setLimitAttributeEX(BIT_LIMIT_MARGIN_VALUE,margin,LimitID);
    mCurBitView->refleshdisplay();
    return;
}
qreal RtSa_Limit::getMargin(qint32 LimitID)
{
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;
    return mCurBitView->getLimitAttributeEX(BIT_LIMIT_MARGIN_VALUE,LimitID);
}
void RtSa_Limit::setLimitType(qint32 LimitID, qint32 nType)
{
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;

    if(nType < RTSA_LIMIT_OFF)
        nType = RTSA_LIMIT_OFF;
    else if(nType > RTSA_LOWER)
        nType = RTSA_LOWER;
//    gLimitType[LimitID] = nType;
    mCurBitView->setLimitAttribute(BIT_LIMIT_TYPE,nType,LimitID);
    mCurBitView->refleshdisplay();
    return;
}
qint32 RtSa_Limit::getLimitType(qint32 LimitID)
{
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;
    return mCurBitView->getLimitAttribute(BIT_LIMIT_TYPE,LimitID);
}
void RtSa_Limit::InsertLimitRow()
{
    mCurBitView->setTableEdit(BIT_LIMIT_EDIT_VISIABLE,BIT_LIMIT_TABLE_EDIT_SHOW);
    mCurBitView->setTableEdit(BIT_LIMIT_INSERT_ROW,1);
    mCurBitView->refleshdisplay();
    return;
}
void RtSa_Limit::DelLimitRow(qint32 index)
{
    mCurBitView->setTableEdit(BIT_LIMIT_EDIT_VISIABLE,BIT_LIMIT_TABLE_EDIT_SHOW);
    mCurBitView->setTableEdit(BIT_LIMIT_DELETE_ROW,BIT_LIMIT_EDIT_VISIABLE,index);
    mCurBitView->refleshdisplay();
    return;
}
void RtSa_Limit::DeleteLimit(qint32 index)
{
    mCurBitView->setTableEdit(BIT_LIMIT_EDIT_VISIABLE,BIT_LIMIT_TABLE_EDIT_SHOW);
    mCurBitView->setTableEdit(BIT_LIMIT_DELETE_LIMIT,index);
    mCurBitView->refleshdisplay();
    return;
}
bool RtSa_Limit::IsHaveLimitOn()
{
    for(qint32 i = RTSA_LIMIT1; i < RTSA_LIMIT6; i++)
    {
        if(IsCurLimitOn(i))
            return true;
    }
    return false;
}
void RtSa_Limit::setLimitNum(qint32 LimitID, qint32 num)
{
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;
    mCurBitView->setLimitAttribute(BIT_LIMIT_POINT_NUM,num,LimitID);
    return;
}
qint32 RtSa_Limit::getLimitDataNum(qint32 LimitID)
{
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;
    return mCurBitView->getLimitAttribute(BIT_LIMIT_POINT_NUM,LimitID);
}
void RtSa_Limit::setLimitFreqData(qreal *pData, qint32 DataNum, qint32 LimitID)
{
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;
    mCurBitView->setLimitAttribute(BIT_LIMIT_POINT_NUM,DataNum,LimitID);
    mCurBitView->setLimitPointData(pData,DataNum,BIT_LIMIT_FREQ,LimitID);
    return;
}
qreal *RtSa_Limit::getLimitFreqData(qint32 LimitID)
{
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;
    mCurBitView->getLimitPointData(gLimitFreq,RTSA_LIMIT_TOTAL,BIT_LIMIT_FREQ,LimitID);
    return gLimitFreq;
}
void RtSa_Limit::setLimitAmptData(qreal* pData,qint32 DataNum,qint32 LimitID)
{
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;
    mCurBitView->setLimitAttribute(BIT_LIMIT_POINT_NUM,DataNum,LimitID);
    mCurBitView->setLimitPointData(pData,DataNum,BIT_LIMIT_AMPT,LimitID);
    return;
}
qreal *RtSa_Limit::getLimitAmptData(qint32 LimitID)
{
    if(LimitID < RTSA_LIMIT1)
        LimitID = RTSA_LIMIT1;
    else if(LimitID >RTSA_LIMIT6)
        LimitID =RTSA_LIMIT6;
    mCurBitView->getLimitPointData(gLimitAmpt,RTSA_LIMIT_TOTAL,BIT_LIMIT_AMPT,LimitID);
    return gLimitAmpt;
}

void RtSa_Limit::setLimitTableShow(bool isShow)
{
    if(isShow)
        mCurBitView->setTableEdit(BIT_LIMIT_EDIT_VISIABLE,BIT_LIMIT_TABLE_EDIT_SHOW);
    else
        mCurBitView->setTableEdit(BIT_LIMIT_EDIT_VISIABLE,BIT_LIMIT_TABLE_EDIT_HIDE);
    return;
}
/**
* @brief setCurLimitFreq
* @param [dataPos] cur limit data pos, [limitID] cur limit index
* @Author Albert
* @date 2019-05-13
*/
void RtSa_Limit::setCurLimitFreq(qreal pData, qint32 dataPos, qint32 limitID)
{
    mCurBitView->setLimitCurPointData(pData,dataPos,BIT_LIMIT_FREQ,limitID);
    return;
}
/**
* @brief setCurLimitAmpt
* @param [dataPos] cur limit data pos, [limitID] cur limit index
* @Author Albert
* @date 2019-05-13
*/
void RtSa_Limit::setCurLimitAmpt(qreal pData, qint32 dataPos, qint32 limitID)
{
    mCurBitView->setLimitCurPointData(pData,dataPos,BIT_LIMIT_AMPT,limitID);
    return;
}

/**
* @brief getCurLimitFreq
* @param cur limit index
* @Author Albert
* @date 2019-05-13
*/
qreal RtSa_Limit::getCurLimitFreq(qint32 dataPos, qint32 limitID)
{
    qreal freq = 0.0;
    freq = mCurBitView->getLimitCurPointData(dataPos,BIT_LIMIT_FREQ,limitID);
    return freq;
}
/**
* @brief getCurLimitAmpt
* @param cur limit index
* @Author Albert
* @date 2019-05-13
*/
qreal RtSa_Limit::getCurLimitAmpt(qint32 dataPos, qint32 limitID)
{
    qreal ampt = 0.0;
    ampt = mCurBitView->getLimitCurPointData(dataPos,BIT_LIMIT_AMPT,limitID);
    return ampt;
}
