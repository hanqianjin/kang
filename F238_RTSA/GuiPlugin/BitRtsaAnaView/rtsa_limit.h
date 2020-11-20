/**************Copyright (c)**************************************
 **
 **               INNO Instrument(China) Co.,Ltd.
 **
 **------------File Info------------------------------------------
 **Class name:              RtSa_Limit
 **Latest Version:          V1.0.0
 **Latest modified Date:
 **Created by:              Albert
 **Created date:            2018/12/13
 **Descriptions:            RTSA limit param control class
 **
 *****************************************************************/
#ifndef RTSA_LIMIT_H
#define RTSA_LIMIT_H

#include <QObject>
#include "bitview.h"
#include "rtsa_user_variable.h"

class RtSa_Limit : public QObject
{
    Q_OBJECT
public:
    explicit RtSa_Limit(QObject *parent = 0);
    ~RtSa_Limit();
public:
    void setCurBitView(BitView* bitview);

    void setCurLimit(qint32 curLimitID);
    qint32 getCurLimit();
    void setCurLimitOn(qint32 LimitID,bool isOn);
    bool IsCurLimitOn(qint32 LimitID);
    void setLimitTestOn(bool isOn);
    bool IsLimitTestOn();
    void setMarginOn(qint32 LimitID,bool isOn);
    bool IsMarginOn(qint32 LimitID);
    void setMargin(qint32 LimitID,qreal margin);
    qreal getMargin(qint32 LimitID);
    void setLimitType(qint32 LimitID,qint32 nType);
    qint32 getLimitType(qint32 LimitID);
    void InsertLimitRow();
    void DelLimitRow(qint32 index);
    void DeleteLimit(qint32 index);

    bool IsHaveLimitOn();

    void setLimitNum(qint32 LimitID,qint32 num);
    qint32 getLimitDataNum(qint32 LimitID);

    void setLimitFreqData(qreal* pData,qint32 DataNum,qint32 LimitID);
    qreal* getLimitFreqData(qint32 LimitID);

    void setLimitAmptData(qreal* pData,qint32 DataNum,qint32 LimitID);
    qreal* getLimitAmptData(qint32 LimitID);

    void setLimitTableShow(bool isShow);

    void setCurLimitFreq(qreal pData,qint32 dataPos, qint32 limitID);
    void setCurLimitAmpt(qreal pData, qint32 dataPos, qint32 limitID);

    qreal getCurLimitFreq(qint32 dataPos, qint32 limitID);
    qreal getCurLimitAmpt(qint32 dataPos, qint32 limitID);



signals:

public slots:
private:
    BitView* mCurBitView;
    qint32 mCurBitViewType;
    RtSa_User_Variable* globalUserVariable;
    qreal gLimitNum;
    qreal gLimitFreq[RTSA_LIMIT_TOTAL];
    qreal gLimitAmpt[RTSA_LIMIT_TOTAL];

//    qreal gCurLimitFreq[RTSA_LIMIT_TOTAL_CNT];
//    qreal gCurLimitAmpt[RTSA_LIMIT_TOTAL_CNT];
};

#endif // RTSA_LIMIT_H
