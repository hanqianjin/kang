#include "pm_interface.h"
#include "pm_extern.h"
#include <QFile>
#include <qthread.h>
#include "QEventLoop"
#include <QDebug>
#include <QTimer>
#include "data_conversion.h"

#include <unistd.h>
BitPm_Interface::BitPm_Interface(QObject *parent) : QObject(parent)
  , nCurWindowIndex(1)
  , wintotalnum(0)
  , mWidth(0)
  , mHeight(0)
  , mIsZoomIn(false)
  , mDragFlag(false)
  , mIsShiftKeyEnable(false)
  , mIsCurBitViewSizeChange(false)
  , mFileType(PM_FILEHEADER_STATE)
  ,pSocketLinkStatus(0)
{
    bGetDataFromScpi = 0;
    memset(m_fV90AmptCalData,0,PM_V90_CAL_AMPT);

}

BitPm_Interface::~BitPm_Interface()
{
    delete m_pPmComm;
    delete m_BitViewGauageDial;
}


/**
* @brief 设置中心频率，注意保存的频率值为未偏移之前的值
* @note
* @author Roc
* @since  2019.11.10
*/
void BitPm_Interface::setCenterFreq(qulonglong freq)
{
    m_viewbottomdisplay = PV_BOTTOM_CENTERANDSPAN;
    if(IsOffset())
    {
        globalUserVariable->gMeterParam.gConfig_Freq.nlCenterFreq = freq
                - globalUserVariable->gMeterParam.gConfig_Freq.nlOffsetFreq;

    }
    else
    {
        globalUserVariable->gMeterParam.gConfig_Freq.nlCenterFreq = freq ;

    }
    globalUserVariable->adjustFreqByCer();

    //   globalUserVariable->gMeterParam.gConfig_Freq.nChannelStep = mPM_ChStand[globalUserVariable->gMeterParam.gConfig_Freq.nChannelStd].ChStep;
    //   globalUserVariable->gMeterParam.gConfig_Freq.nChannelNumber = globalUserVariable->CalculateChannelNum();

    globalUserVariable->adjustCHStandarByCerFreq(freq);

    setSweepContinous(IsSweepContinous());

    updateGeneralDataToBitview(PM_FREQ_INFO);
    emit RedrawInfoShow(PM_LABEL_CENTER_FREQ);
    emit RedrawInfoShow(PM_LABEL_START_FREQ);
    emit RedrawInfoShow(PM_LABEL_STOP_FREQ);
    showBitViewBottomMsg(m_viewbottomdisplay);
    return;
}

/**
* @brief
* @note
* @author Roc
* @since  2019.11.9
*/
qulonglong BitPm_Interface::getCenterFreq()
{
    if(IsOffset())
    {
        return globalUserVariable->gMeterParam.gConfig_Freq.nlCenterFreq
                + globalUserVariable->gMeterParam.gConfig_Freq.nlOffsetFreq;

    }
    else
    {
        return globalUserVariable->gMeterParam.gConfig_Freq.nlCenterFreq;
    }
}

/**
* @brief set start freq  当是Offset 时  起始频率 = 输入频率 - 偏移量
* @note
* @author Roc
* @since  2019.11.10
*/
void BitPm_Interface::setStartFreq(qulonglong freq)
{
    m_viewbottomdisplay = PV_BOTTOM_STARTANDSTOP;
    if(IsOffset())
    {
        globalUserVariable->gMeterParam.gConfig_Freq.nlStartFreq =  freq
                - globalUserVariable->gMeterParam.gConfig_Freq.nlOffsetFreq;
    }
    else
    {
        globalUserVariable->gMeterParam.gConfig_Freq.nlStartFreq = freq;;
    }

    globalUserVariable->adjustFreqByStart();

    setSweepContinous(IsSweepContinous());

    updateGeneralDataToBitview(PM_FREQ_INFO);
    emit RedrawInfoShow(PM_LABEL_START_FREQ);
    emit RedrawInfoShow(PM_LABEL_CENTER_FREQ);
    showBitViewBottomMsg(m_viewbottomdisplay);
    return;
}

/**qint32
* @brief get start freq
* @note
* @author Roc
* @since  2019.11.10
*/
qulonglong BitPm_Interface::getStartFreq()
{
    if(IsOffset())
    {
        return globalUserVariable->gMeterParam.gConfig_Freq.nlStartFreq
                + globalUserVariable->gMeterParam.gConfig_Freq.nlOffsetFreq;
    }
    else
    {
        return globalUserVariable->gMeterParam.gConfig_Freq.nlStartFreq;
    }
}

/**
* @brief set stop freq
* @note
* @author Roc
* @since  2019.11.10
*/
void BitPm_Interface::setStopFreq(qulonglong freq)
{
    m_viewbottomdisplay = PV_BOTTOM_STARTANDSTOP;
    if(IsOffset())
    {
        globalUserVariable->gMeterParam.gConfig_Freq.nlStopFreq =  freq
                - globalUserVariable->gMeterParam.gConfig_Freq.nlOffsetFreq;
    }
    else
    {
        globalUserVariable->gMeterParam.gConfig_Freq.nlStopFreq = freq;;
    }

    globalUserVariable->adjustFreqByStop();

    setSweepContinous(IsSweepContinous());

    updateGeneralDataToBitview(PM_FREQ_INFO);
    emit RedrawInfoShow(PM_LABEL_STOP_FREQ);
    emit RedrawInfoShow(PM_LABEL_CENTER_FREQ);
    showBitViewBottomMsg(m_viewbottomdisplay);
    return;
}

/**
* @brief get stop freq
* @note
* @author Roc
* @since  2019.11.10
*/
qulonglong BitPm_Interface::getStopFreq()
{
    if(IsOffset())
    {
        return globalUserVariable->gMeterParam.gConfig_Freq.nlStopFreq + globalUserVariable->gMeterParam.gConfig_Freq.nlOffsetFreq;
    }
    else
    {
        return globalUserVariable->gMeterParam.gConfig_Freq.nlStopFreq;
    }
}

/**
* @brief set step freq
* @note
* @author Roc
* @since  2019.11.10
*/
void BitPm_Interface::setStepFreq(qulonglong freq)
{
    if(POWER_SENSOR_V90 == globalUserVariable->m_nPowerSensorFlg)
    {
        if(freq < PM_V90_MIN_SPAN)
        {
            freq = PM_V90_MIN_SPAN;
        }
        else if(freq > PM_V90_MAX_SPAN)
        {
            freq = PM_V90_MAX_SPAN;
        }
    }
    else if(POWER_SENSOR_V91 == globalUserVariable->m_nPowerSensorFlg)
    {
        if(freq < PM_V91_MIN_SPAN)
        {
            freq = PM_V91_MIN_SPAN;
        }
        else if(freq > PM_V91_MAX_SPAN)
        {
            freq = PM_V91_MAX_SPAN;
        }
    }
    globalUserVariable->gMeterParam.gConfig_Freq.nlStepFreq = freq;

    return;
}

/**
* @brief get step freq
* @note
* @author Roc
* @since  2019.11.10
*/
qulonglong BitPm_Interface::getStepFreq()
{
    return globalUserVariable->gMeterParam.gConfig_Freq.nlStepFreq;
}

/**
* @brief set span freq
* @note
* @author Roc
* @since  2019.11.10
*/
void BitPm_Interface::setSpan(qulonglong freq)
{
    m_viewbottomdisplay = PV_BOTTOM_CENTERANDSPAN;
    if(freq < PM_SPAN_MIN)
        freq = PM_SPAN_MIN;

    if(freq > PM_SPAN_MAX)
        freq = PM_SPAN_MAX;
    globalUserVariable->gMeterParam.gConfig_Freq.nlSpan = freq;

    adjustSpanFreq(freq);

    updateGeneralDataToBitview(PM_FREQ_INFO);
    emit RedrawInfoShow(PM_LABEL_SPAN);
    showBitViewBottomMsg(m_viewbottomdisplay);
    return;
}

/**
* @brief get span freq
* @note
* @author Roc
* @since  2019.11.10
*/
qulonglong BitPm_Interface::getSpan()
{
    return globalUserVariable->gMeterParam.gConfig_Freq.nlSpan;
}

//void BitPm_Interface::setSpanUp(qint32 nlSpanUp)
//{
//    globalUserVariable->gMeterParam.gConfig_Freq.nlSpanUp = nlSpanUp;
//    //    m_viewbottomdisplay = PV_BOTTOM_CENTERANDSPAN;
//    //    globalUserVariable->gMeterParam.gConfig_Freq.nlLastSpan =  globalUserVariable->gMeterParam.gConfig_Freq.nlSpan;
//    //    for(qint32 k =globalUserVariable->gMeterParam.gConfig_Freq.nlSpan+1;k<= globalUserVariable->gMeterParam.gConfig_Freq.nlSpan*2;k++)
//    //    {
//    //        if(k%nlSpan == 0)
//    //        {
//    //           globalUserVariable->gMeterParam.gConfig_Freq.nlSpan  = k;
//    //           break;
//    //        }
//    //    }

//    //    globalUserVariable->gMeterParam.gConfig_Freq.nSpanType =PM_NORMAL_SPAN;

//    //    globalUserVariable->adjustFreqBySpan(globalUserVariable->gMeterParam.gConfig_Freq.nlSpan);

//    //    updateGeneralDataToBitview(PM_FREQ_INFO);
//    //    emit RedrawInfoShow(PM_LABEL_SPAN);
//    //    showBitViewBottomMsg(m_viewbottomdisplay);
//}

//qint32 BitPm_Interface::getSpanUp()
//{
//    return globalUserVariable->gMeterParam.gConfig_Freq.nlSpanUp;
//}

//void BitPm_Interface::setSpanDown(qint32 nlSpanDown)
//{
//    globalUserVariable->gMeterParam.gConfig_Freq.nlSpanDown = nlSpanDown;
//    //    m_viewbottomdisplay = PV_BOTTOM_CENTERANDSPAN;
//    //    globalUserVariable->gMeterParam.gConfig_Freq.nlLastSpan =  globalUserVariable->gMeterParam.gConfig_Freq.nlSpan;
//    //    for(qint32 k =globalUserVariable->gMeterParam.gConfig_Freq.nlSpan-1;k>= globalUserVariable->gMeterParam.gConfig_Freq.nlSpan/2-1;k--)
//    //    {
//    //        if(k%nlSpan == 0)
//    //        {
//    //           globalUserVariable->gMeterParam.gConfig_Freq.nlSpan  = k;
//    //           break;
//    //        }
//    //    }

//    //    globalUserVariable->gMeterParam.gConfig_Freq.nSpanType =PM_NORMAL_SPAN;

//    //    globalUserVariable->adjustFreqBySpan(globalUserVariable->gMeterParam.gConfig_Freq.nlSpan);


//    //    updateGeneralDataToBitview(PM_FREQ_INFO);
//    //    emit RedrawInfoShow(PM_LABEL_SPAN);
//    //    showBitViewBottomMsg(m_viewbottomdisplay);
//}
//qint32 BitPm_Interface::getSpanDown()
//{
//    return globalUserVariable->gMeterParam.gConfig_Freq.nlSpanDown;
//}

/**
* @brief set span Type
* @note
* @author	Roc
* @since	2019.11.19
*/
void BitPm_Interface::setSpanType(qint32 index)
{
    m_viewbottomdisplay = PV_BOTTOM_CENTERANDSPAN;
    if(POWER_SENSOR_V90 == globalUserVariable->m_nPowerSensorFlg)
    {
        if(PM_MIN_SPAN == index)
        {
            globalUserVariable->gMeterParam.gConfig_Freq.nlLastSpan =  globalUserVariable->gMeterParam.gConfig_Freq.nlSpan;
            globalUserVariable->gMeterParam.gConfig_Freq.nlSpan = PM_V90_MIN_SPAN;
            //            globalUserVariable->gMeterParam.gConfig_Freq.nlSpan = PM_V90_SPAN_STEP_VALUE[0];
        }
        else if(PM_FULL_SPAN == index)
        {
            globalUserVariable->gMeterParam.gConfig_Freq.nlLastSpan =  globalUserVariable->gMeterParam.gConfig_Freq.nlSpan;
            globalUserVariable->gMeterParam.gConfig_Freq.nlSpan = PM_V90_MAX_SPAN;
            //            globalUserVariable->gMeterParam.gConfig_Freq.nlSpan = PM_V90_SPAN_STEP_VALUE[PM_V90_SPAN_INTERVAL_NUMBER-1];
        }
        else
        {
            globalUserVariable->gMeterParam.gConfig_Freq.nlSpan = globalUserVariable->gMeterParam.gConfig_Freq.nlLastSpan;
        }
    }
    else if(POWER_SENSOR_V91 == globalUserVariable->m_nPowerSensorFlg)
    {
        if(PM_MIN_SPAN == index)
        {
            globalUserVariable->gMeterParam.gConfig_Freq.nlLastSpan =  globalUserVariable->gMeterParam.gConfig_Freq.nlSpan;
            globalUserVariable->gMeterParam.gConfig_Freq.nlSpan = PM_V91_MIN_SPAN;
            //            globalUserVariable->gMeterParam.gConfig_Freq.nlSpan = PM_V91_SPAN_STEP_VALUE[0];
        }
        else if(PM_FULL_SPAN == index)
        {
            globalUserVariable->gMeterParam.gConfig_Freq.nlLastSpan =  globalUserVariable->gMeterParam.gConfig_Freq.nlSpan;
            globalUserVariable->gMeterParam.gConfig_Freq.nlSpan = PM_V91_MAX_SPAN;
            //            globalUserVariable->gMeterParam.gConfig_Freq.nlSpan = PM_V91_SPAN_STEP_VALUE[PM_V91_SPAN_INTERVAL_NUMBER-1];
        }
        else
        {
            globalUserVariable->gMeterParam.gConfig_Freq.nlSpan = globalUserVariable->gMeterParam.gConfig_Freq.nlLastSpan;
        }
    }

    globalUserVariable->gMeterParam.gConfig_Freq.nSpanType  = index;
    globalUserVariable->adjustFreqBySpan(globalUserVariable->gMeterParam.gConfig_Freq.nlSpan);

    updateGeneralDataToBitview(PM_FREQ_INFO);
    emit RedrawInfoShow(PM_LABEL_SPAN);
    showBitViewBottomMsg(m_viewbottomdisplay);
    return;
}
qint32 BitPm_Interface::getSpanType()
{
    return globalUserVariable->gMeterParam.gConfig_Freq.nSpanType;
}

/**
* @brief set channel std index
* @param[in] standard index
* @author	Roc
* @since	2019.11.19
*/
void BitPm_Interface::setCHStandard(qint32 index)
{
    qreal newCerFreq;
    if(index < 0)
        return;

    globalUserVariable->gMeterParam.gConfig_Freq.nChannelStd = index;

    globalUserVariable->getBandInfo(index);

    //    globalUserVariable->adjustCHStandarByCerFreq(globalUserVariable->gMeterParam.gConfig_Freq.nlCenterFreq);

    newCerFreq = globalUserVariable->adjustFreqByCHStandar();

    //    globalUserVariable->adjustCHStandarByCerFreq(newCerFreq);

    setCenterFreq(newCerFreq);
    emit RedrawInfoShow(PM_LABEL_CHANNEL);
    showBitViewBottomMsg(m_viewbottomdisplay);
    return;
}

/**
* @brief get channel std index
* @param none
* @author	Roc
* @since	2019.11.19
*/
qint32 BitPm_Interface::getCHStandard()
{
    qint32 index;

    if(globalUserVariable->gMeterParam.gConfig_Freq.nChannelStd < 0)
    {
        return -1;
    }
    index = mPM_ChStand[globalUserVariable->gMeterParam.gConfig_Freq.nChannelStd].index;
    return index;
}

/**
* @brief
* @param
* @author	Roc
* @since	2019.11.19
*/
void BitPm_Interface::setBandIndex(qint32 bandIndex)
{
    if(bandIndex < 0)
        bandIndex = 0;
    else if(bandIndex >= globalUserVariable->gCHName->size())
    {
        bandIndex = globalUserVariable->gCHName->size() - 1;
    }

    globalUserVariable->gMeterParam.gConfig_Freq.nChannelSelID = bandIndex;

    globalUserVariable->getBandInfo(globalUserVariable->gMeterParam.gConfig_Freq.nChannelStd);
    qreal newCerFreq = globalUserVariable->adjustFreqByCHStandar();
    setCenterFreq(newCerFreq);
    emit RedrawInfoShow(PM_LABEL_CHANNEL);
    emit RedrawInfoShow(PM_LABEL_SIGNAL_STANDARD);
    return;
}

qint32 BitPm_Interface::getBandIndex()
{
    return globalUserVariable->gMeterParam.gConfig_Freq.nChannelSelID;
}

/**
* @brief set channel number
* @param[in] channel number
* @author	Roc
* @since	2019.11.19
*/
void BitPm_Interface::setChannelNumber(qint32 number)
{
    if(number == globalUserVariable->gMeterParam.gConfig_Freq.nChannelNumber)
        return;
    qreal min = 0;
    qreal max = 0;
    qreal centerFreq;

    max = globalUserVariable->gCHStandard->at(globalUserVariable->gMeterParam.gConfig_Freq.nChannelSelID).Down.Max;
    min = globalUserVariable->gCHStandard->at(globalUserVariable->gMeterParam.gConfig_Freq.nChannelSelID).Down.Min;

    if(number < min)
        number = min;
    else if(number > max)
        number = max;

    globalUserVariable->gMeterParam.gConfig_Freq.nChannelNumber = number;
    //m_pPmComm->setChannelNumber(globalUserVariable->gMeterParam.gConfig_Freq.nChannelNumber);

    //Center Freq need modify
    centerFreq = globalUserVariable->adjustFreqByCHNum(number);
    setCenterFreq(centerFreq);
    return ;
}

/**
* @brief get channel number
* @param none
* @author	Roc
* @since	2019.11.19
*/
qint32 BitPm_Interface::getChannelNumber()
{
    return globalUserVariable->gMeterParam.gConfig_Freq.nChannelNumber;
}


/**
* @brief set channel std communicate direction
* @param[in] direction type
* @Author	ROC
* @date     2019.12.24
*/
void BitPm_Interface::setCommuDirection(qint32 direction)
{
    if(globalUserVariable->gMeterParam.gConfig_Freq.nChannelType == direction)
        return;
    qreal newCerFreq = 0.;
    globalUserVariable->gMeterParam.gConfig_Freq.nChannelType = direction;
    newCerFreq = globalUserVariable->adjustFreqByCHStandar();
    //    globalUserVariable->adjustCHStandarByCerFreq(newCerFreq);
    setCenterFreq(newCerFreq);
    return;
}

/**
* @brief get channel std communicate direction
* @param none
* @Author	ROC
* @date     2019.12.24
*/
qint32 BitPm_Interface::getCommuDirection()
{
    return globalUserVariable->gMeterParam.gConfig_Freq.nChannelType;
}

/**
* @brief   设置频率偏移标志
* @param
* @author	Roc
* @since	2019.11.19
 */
void BitPm_Interface::setOffset(bool isOffset)
{
    globalUserVariable->gMeterParam.gConfig_Freq.nOffsetFreqOn = isOffset;

    emit RedrawInfoShow(PM_LABEL_CENTER_FREQ);
    emit RedrawInfoShow(PM_LABEL_START_FREQ);
    emit RedrawInfoShow(PM_LABEL_STOP_FREQ);
    updateGeneralDataToBitview(PM_FREQ_INFO);
    showBitViewBottomMsg(m_viewbottomdisplay);
    return;
}
/**
* @brief   获得频率偏移标志
* @param
* @author	Roc
* @since	2019.11.19
 */
bool BitPm_Interface::IsOffset()
{
    return globalUserVariable->gMeterParam.gConfig_Freq.nOffsetFreqOn;
}

/**
* @brief   设置频率偏移
* @param
* @author	Roc
* @since	2019.11.19
 */
void BitPm_Interface::setFreqOffset(qlonglong freq)
{
    if(POWER_SENSOR_V90 == globalUserVariable->m_nPowerSensorFlg)
    {
        if(freq > PM_V90_FREQ_MAX)
            freq = PM_V90_FREQ_MAX;
        else if(freq < -PM_V90_FREQ_MAX)
            freq = -PM_V90_FREQ_MAX;
    }
    else if(POWER_SENSOR_V91 == globalUserVariable->m_nPowerSensorFlg)
    {
        if(freq > PM_V91_FREQ_MAX)
            freq = PM_V91_FREQ_MAX;
        else if(freq < -PM_V91_FREQ_MAX)
            freq = -PM_V91_FREQ_MAX;
    }
    globalUserVariable->gMeterParam.gConfig_Freq.nlOffsetFreq = freq;

    emit RedrawInfoShow(PM_LABEL_CENTER_FREQ);
    emit RedrawInfoShow(PM_LABEL_START_FREQ);
    emit RedrawInfoShow(PM_LABEL_STOP_FREQ);
    updateGeneralDataToBitview(PM_FREQ_INFO);
    showBitViewBottomMsg(m_viewbottomdisplay);

    return;
}

/**
* @brief   获得频率偏移
* @param
* @author	Roc
* @since	2019.11.19
 */
qlonglong BitPm_Interface::getFreqOffset()
{
    return globalUserVariable->gMeterParam.gConfig_Freq.nlOffsetFreq;
}

///**
//* @brief   设置旋钮旋转时频率偏移对话框的步进值
//* @param
//* @author	Roc
//* @since	2019.11.19
// */
//void BitPm_Interface::setFreqOffsetSize(qulonglong freq)
//{
//    globalUserVariable->gMeterParam.gConfig_Freq.nlOffsetFreqSize = freq;
//    return;
//}

///**
//* @brief   获得旋钮旋转时频率偏移对话框的步进值
//* @param
//* @author	Roc
//* @since	2019.11.19
// */
//qulonglong BitPm_Interface::getFreqOffsetSize()
//{
//    return globalUserVariable->gMeterParam.gConfig_Freq.nlOffsetFreqSize;
//}

//幅度 Amplitude
/**
* @brief	设置测试最大值
* @note
* @author	Roc
* @since	2019.11.12
*/
void BitPm_Interface::setAmptMax(qreal ampMax)
{

    qreal tempValue;
#ifdef PM_AMPT_IS_OFFSET

    if(ampMax > getMaxDialData()+globalUserVariable->gMeterParam.gConfig_Ampt.fOffset)
        ampMax = getMaxDialData()+globalUserVariable->gMeterParam.gConfig_Ampt.fOffset;
    else if(ampMax < getMinDialData() +globalUserVariable->gMeterParam.gConfig_Ampt.fOffset+1 )
    {
        ampMax = getMinDialData() +globalUserVariable->gMeterParam.gConfig_Ampt.fOffset+ 1;
        setAmptMin(getMinDialData()+globalUserVariable->gMeterParam.gConfig_Ampt.fOffset);
    }
    else {
        tempValue = getAmptMin();
        if(ampMax < tempValue)
            setAmptMin(ampMax-1);
    }

    globalUserVariable->gMeterParam.gConfig_Ampt.fMax = ampMax - globalUserVariable->gMeterParam.gConfig_Ampt.fOffset;
#else
    if(ampMax > getMaxDialData())
        ampMax = getMaxDialData();
    else if(ampMax < getMinDialData() +1 )
    {
        ampMax = getMinDialData() + 1;
        setAmptMin(getMinDialData());
    }
    else {
        tempValue = getAmptMin();
        if(ampMax < tempValue)
            setAmptMin(ampMax-1);
    }

    globalUserVariable->gMeterParam.gConfig_Ampt.fMax = ampMax;
#endif
    m_BitViewGauageDial->SetMaxPower(globalUserVariable->gMeterParam.gConfig_Ampt.fMax);
    return;
}

/**
* @brief	得到测试最大值
* @note
* @author	Roc
* @since	2019.11.12
*/
qreal BitPm_Interface::getAmptMax()
{
    qreal fAmptMin = 0;
#ifdef PM_AMPT_IS_OFFSET
    fAmptMin = globalUserVariable->gMeterParam.gConfig_Ampt.fMax + globalUserVariable->gMeterParam.gConfig_Ampt.fOffset;
#else
    fAmptMin = globalUserVariable->gMeterParam.gConfig_Ampt.fMax;
#endif
   return fAmptMin;
}

/**
* @brief	设置测试最小值
* @note
* @author	Roc
* @since	2019.11.12
*/
void BitPm_Interface::setAmptMin(qreal ampMin)
{
    qreal tempValue;
#ifdef PM_AMPT_IS_OFFSET
    if(ampMin < getMinDialData()+globalUserVariable->gMeterParam.gConfig_Ampt.fOffset)
        ampMin = getMinDialData()+globalUserVariable->gMeterParam.gConfig_Ampt.fOffset;
    else if(ampMin > getMaxDialData() +globalUserVariable->gMeterParam.gConfig_Ampt.fOffset-1 )
    {
        setAmptMax(getMaxDialData()+globalUserVariable->gMeterParam.gConfig_Ampt.fOffset);
        ampMin = getMaxDialData() +globalUserVariable->gMeterParam.gConfig_Ampt.fOffset- 1;
    }
    else {
        tempValue = getAmptMax();
        if(ampMin > tempValue)
            setAmptMax(ampMin+1);
    }

    globalUserVariable->gMeterParam.gConfig_Ampt.fMin = ampMin -globalUserVariable->gMeterParam.gConfig_Ampt.fOffset;
#else
    if(ampMin < getMinDialData())
        ampMin = getMinDialData();
    else if(ampMin > getMaxDialData() -1)
    {
        setAmptMax(getMaxDialData());
        ampMin = getMaxDialData() - 1;
    }
    else {
        tempValue = getAmptMax();
        if(ampMin > tempValue)
            setAmptMax(ampMin+1);
    }
    globalUserVariable->gMeterParam.gConfig_Ampt.fMin = ampMin;
#endif

    m_BitViewGauageDial->SetMinPower( globalUserVariable->gMeterParam.gConfig_Ampt.fMin);
    return;
}

/**
* @brief	得到测试最小值
* @note
* @author	Roc
* @since	2019.11.12
*/
qreal BitPm_Interface::getAmptMin()
{
    qreal fAmptMin = 0;
#ifdef PM_AMPT_IS_OFFSET
    fAmptMin=  globalUserVariable->gMeterParam.gConfig_Ampt.fMin + globalUserVariable->gMeterParam.gConfig_Ampt.fOffset;
#else
    fAmptMin = globalUserVariable->gMeterParam.gConfig_Ampt.fMin;
#endif
    return fAmptMin;
}

/**
* @brief	设置测试功率偏移  指外部衰减器值
* @note
* @author	Roc
* @since	2019.11.12
*/
void BitPm_Interface::setAmptOffset(qreal ampOffset)
{
    globalUserVariable->gMeterParam.gConfig_Ampt.fOffset = ampOffset;
    emit RedrawInfoShow(PM_LABEL_OFFSET);
    return;
}
/**
* @brief	得到测试功率偏移  指外部衰减器值
* @note
* @author	Roc
* @since	2019.11.12
*/
qreal BitPm_Interface::getAmptOffset()
{
    return globalUserVariable->gMeterParam.gConfig_Ampt.fOffset;
}

/**
* @brief   set units
* @note
* @author	Roc
* @since	2019.11.13
*/
void BitPm_Interface::setAmptUnit(qint32 unitIndex)
{
    if(unitIndex < PM_DBM)
        unitIndex = PM_DBM;
    else if(unitIndex > PM_WATTS)
        unitIndex = PM_WATTS;

    globalUserVariable->gMeterParam.gConfig_Ampt.nUnits = unitIndex;
    emit setUnitSingle(globalUserVariable->gMeterParam.gConfig_Ampt.nUnits);

    return;
}

/**
* @brief   get units
* @note
* @author	Roc
* @since	2019.11.13
*/
qint32 BitPm_Interface::getAmptUint()
{
    return globalUserVariable->gMeterParam.gConfig_Ampt.nUnits;
}

/**
* @brief   set auto scale
* @note
* @author	Roc
* @since	2019.11.13
*/
void BitPm_Interface::setAutoScale()
{
    qreal dataPower = 10*log10(m_curSensorData.fPowerDatamW);
    if(dataPower > getAmptMin() && dataPower < getAmptMax())
    {
        qreal dataUp =  getAmptMax() - dataPower;
        qreal dataDown =  dataPower - getAmptMin();
        if(dataDown > dataUp)
        {
            setAmptMin(dataPower - dataUp);
        }
        else
        {
            setAmptMax(dataPower + dataDown);
        }
    }
    return;
}

/**
* @brief	设置 Forward Relative
* @note
* @author	Roc
* @since	2019.11.12
*/
void BitPm_Interface::setAmptForwardRelative(qint32 IsAmptForwardRelative)
{
    globalUserVariable->gMeterParam.gConfig_Ampt.nForwardRelative = IsAmptForwardRelative;
    m_BitViewGauageDial->setRelativeForward(IsAmptForwardRelative);
    m_BitViewGauageDial->setdBmRelativeBaseForward(
                globalUserVariable->gMeterParam.gConfig_Ampt.fForwardRelativeData);
    emit RedrawInfoShow(PM_LABEL_FORWARD);
}

qint32 BitPm_Interface::IsAmptForwardRelative()
{
    return globalUserVariable->gMeterParam.gConfig_Ampt.nForwardRelative;
}

void BitPm_Interface::setAmptForwardRelativeData(qreal fAmptForwardRelative)
{
    globalUserVariable->gMeterParam.gConfig_Ampt.fForwardRelativeData = fAmptForwardRelative;
    m_BitViewGauageDial->setdBmRelativeBaseForward(fAmptForwardRelative);
    emit RedrawInfoShow(PM_LABEL_FORWARD);
}

qreal BitPm_Interface::getAmptForwardRelativeData()
{
    return globalUserVariable->gMeterParam.gConfig_Ampt.fForwardRelativeData;
}

void BitPm_Interface::setForwardRelativeCurFlg(bool bRead)
{
    m_bReadForwardBase = bRead;
    if(bRead)
        m_BitViewGauageDial->setRelativeForward(bRead);
}
bool BitPm_Interface::getForwardRelativeCurFlg()
{
    return  m_bReadForwardBase;
}


/**
* @brief	设置 Reverse Relative
* @note
* @author	Roc
* @since	2019.11.12
*/
void BitPm_Interface::setAmptReverseRelative(qint32 IsAmptReverseRelative)
{
    globalUserVariable->gMeterParam.gConfig_Ampt.nReverseRelative = IsAmptReverseRelative;
    m_BitViewGauageDial->setRelativeReverse(IsAmptReverseRelative);
    m_BitViewGauageDial->setdBmRelativeBaseReverse(
                globalUserVariable->gMeterParam.gConfig_Ampt.fReverseRelativeData);

    emit RedrawInfoShow(PM_LABEL_REVERSE);
}

qint32 BitPm_Interface::IsAmptReverseRelative()
{
    return globalUserVariable->gMeterParam.gConfig_Ampt.nReverseRelative;
}

void BitPm_Interface::setAmptReverseRelativeData(qreal fAmptReverseRelative)
{
    globalUserVariable->gMeterParam.gConfig_Ampt.fReverseRelativeData = fAmptReverseRelative;
    m_BitViewGauageDial->setdBmRelativeBaseReverse(fAmptReverseRelative);
    emit RedrawInfoShow(PM_LABEL_REVERSE);
}
qreal BitPm_Interface::getAmptReverseRelativeData()
{

    return globalUserVariable->gMeterParam.gConfig_Ampt.fReverseRelativeData;
}

void BitPm_Interface::setReverseRelativeCurFlg(bool bRead)
{
    m_bReadReverseBase = bRead;
    if(bRead)
        m_BitViewGauageDial->setRelativeReverse(bRead);
}

bool BitPm_Interface::getReverseRelativeCurFlg()
{
    return  m_bReadReverseBase;
}
/**
* @brief   设置采集模式，目前分单次与连续采集，单次采集一发一收，连续采集一发多收到发送停止为止
* @note
* @author	Roc
* @since	2019.11.13
*/
void BitPm_Interface::setSweepContinous(qint32 nContinous)
{
    globalUserVariable->gMeterParam.gConfig_Sweep.nSweepType = nContinous;
    m_curSensorData.nPointNo=0;
    cmd_GetSensorPower(nContinous);// 连续采集发一遍后会继续接收
    ////
    //    if(PM_CONT == nContinous)
    //        emit setThreadContinous(nContinous);

    emit RedrawInfoShow(PM_LABEL_SWEEP);
    return;
}

/**
* @brief   获得模式识别
* @note
* @author	Roc
* @since	2019.11.13
*/
bool BitPm_Interface::IsSweepContinous()
{
    return globalUserVariable->gMeterParam.gConfig_Sweep.nSweepType;
}

void BitPm_Interface::setSweepTime(quint32 nTime)
{
    if(nTime < PM_SWEEP_TIME_MIN)
        nTime = PM_SWEEP_TIME_MIN;
    if(nTime > PM_SWEEP_TIME_MAX)
        nTime = PM_SWEEP_TIME_MAX;
    globalUserVariable->gMeterParam.gConfig_Sweep.nTimeInterval = nTime;
    setSweepContinous(IsSweepContinous());
    emit RedrawInfoShow(PM_LABEL_SWEEP);
    return;
}
quint8 BitPm_Interface::getSweepTime()
{
    return globalUserVariable->gMeterParam.gConfig_Sweep.nTimeInterval;
}

void BitPm_Interface::setMeasureModle(quint8 nModle)
{
    globalUserVariable->gMeterParam.gConfig_Measure.nModle = nModle;
    return;
}

quint8 BitPm_Interface::getMeasureModle()
{
    return globalUserVariable->gMeterParam.gConfig_Measure.nModle;
}

/**
* @brief	设置占空比
* @note
* @Author	ROC
* @date	2019.11.20
*/
void BitPm_Interface::setDutyCycle(qreal fDutyCycle)
{
    if(fDutyCycle < PM_LIMIT_DUTY_MIN)
        fDutyCycle = PM_LIMIT_DUTY_MIN;
    if(fDutyCycle > PM_LIMIT_DUTY_MAX)
        fDutyCycle = PM_LIMIT_DUTY_MAX;
    globalUserVariable->gMeterParam.gConfig_Sweep.fDutyCycle = fDutyCycle;
    return;
}

qreal BitPm_Interface::getDutyCycle()
{
    return globalUserVariable->gMeterParam.gConfig_Sweep.fDutyCycle;
}

void BitPm_Interface::setMeasureOffset(qreal fOffset)
{
    globalUserVariable->gMeterParam.gConfig_Measure.fOffset = fOffset;
    emit RedrawInfoShow(PM_LABEL_SWEEP);
    return;
}

qreal BitPm_Interface::getMeasureOffset()
{
    return globalUserVariable->gMeterParam.gConfig_Measure.fOffset;
}

//average
void BitPm_Interface::setAverageAcq(qint32 index)
{
    globalUserVariable->gMeterParam.gConfig_Ave.nAcquisition = index;
    emit RedrawInfoShow(PM_LABEL_ACQ);
    return ;

}


qint32 BitPm_Interface::IsAcqType()
{
    return globalUserVariable->gMeterParam.gConfig_Ave.nAcquisition;
}

/**
* @brief	设置平均值标志
* @note
* @author	Roc
* @since	2019.11.13
*/
void BitPm_Interface::setRunningAverage(bool bIsAverageFlg)
{
    globalUserVariable->gMeterParam.gConfig_Ave.bIsAverageFlg = bIsAverageFlg;
    emit RedrawInfoShow(PM_LABEL_AVERAGE);
    return;
}

/**
* @brief	获得平均值标志
* @note
* @author	Roc
* @since	2019.11.13
*/
bool BitPm_Interface::IsRunningAverage()
{
    return  globalUserVariable->gMeterParam.gConfig_Ave.bIsAverageFlg;
}
/**
* @brief	设置平均值点数
* @note
* @author	Roc
* @since	2019.11.13
*/
void BitPm_Interface::setAveragePoint(qint32 runningAverage)
{
    if(runningAverage < PM_RUNNING_AVERAGE_MIN)
        runningAverage = PM_RUNNING_AVERAGE_MIN;
    else  if(runningAverage > PM_RUNNING_AVERAGE_MAX)
        runningAverage = PM_RUNNING_AVERAGE_MAX;
    globalUserVariable->gMeterParam.gConfig_Ave.nRunningAverage = runningAverage;
    emit RedrawInfoShow(PM_LABEL_AVERAGE);
    return;
}

/**
* @brief	得到平均值点数
* @note
* @author	Roc
* @since	2019.11.13
*/
qint32 BitPm_Interface::getAveragePoint()
{
    return globalUserVariable->gMeterParam.gConfig_Ave.nRunningAverage;
}

/**
* @brief	设置最大值保持标志
* @note
* @author	Roc
* @since	2019.11.13
*/
void BitPm_Interface::setMaxHold(bool isMaxHold)
{
    globalUserVariable->gMeterParam.gConfig_Ave.nMaxHold = isMaxHold;
    m_BitViewGauageDial->setHoldMaxPower(globalUserVariable->gMeterParam.gConfig_Ave.nMaxHold);
    emit RedrawInfoShow(PM_LABEL_MAXHOLD);
    return;
}

/**
* @brief	得到最大值保持标志
* @note
* @author	Roc
* @since	2019.11.13
*/
bool BitPm_Interface::IsMaxHold()
{
    return globalUserVariable->gMeterParam.gConfig_Ave.nMaxHold ;
}

//Zero/Cal
/**
* @brief    设置0点 当前方法是设置当前值为0点
* @note
* @author	Roc
* @since	2019.11.13
*/
void BitPm_Interface::setZero(bool isZero)
{
    if(m_pPmComm->m_serialportPm->IsOpenPort())
    {
        globalUserVariable->gMeterParam.gConfig_Zero.nZero = isZero;
        if(isZero )
            emit ZeroDlgShow();
    }
    return;
}

bool BitPm_Interface::IsZero()
{
    return globalUserVariable->gMeterParam.gConfig_Zero.nZero;
}


void BitPm_Interface::setForwardZero(qreal fZeroBase)
{
    globalUserVariable->gMeterParam.gConfig_Zero.m_fZeroBaseForward = fZeroBase;
}

qreal BitPm_Interface::getForwardZero()
{
    return globalUserVariable->gMeterParam.gConfig_Zero.m_fZeroBaseForward;
}


void BitPm_Interface::setReverseZero(qreal fZeroBase)
{
    globalUserVariable->gMeterParam.gConfig_Zero.m_fZeroBaseReverse = fZeroBase;
}

qreal BitPm_Interface::getReverseZero()
{
   return globalUserVariable->gMeterParam.gConfig_Zero.m_fZeroBaseReverse;
}


void BitPm_Interface::setCalCenterFreqMHz(quint16 freq)
{
    globalUserVariable->gMeterParam.gConfig_Zero.nFreq = freq;
}

qint16 BitPm_Interface::getCalCenterFreqMHz()
{
    return  globalUserVariable->gMeterParam.gConfig_Zero.nFreq;
}

void BitPm_Interface::setCalArray(quint16 arrayNo)
{
    if(V90_CAL_NUM >arrayNo)
        globalUserVariable->gMeterParam.gConfig_Zero.nArray = arrayNo;
    else
        arrayNo = V90_CAL_NUM;
}
qint16 BitPm_Interface::getCalArray()
{
    return  globalUserVariable->gMeterParam.gConfig_Zero.nArray;
}

void BitPm_Interface::setCalSelectType(qint8 nSelectType)
{
    globalUserVariable->gMeterParam.gConfig_Zero.nSelectCalType = nSelectType;
}
qint8 BitPm_Interface::getCalSelectType()
{
    return  globalUserVariable->gMeterParam.gConfig_Zero.nSelectCalType;
}

/**
* @brief    极限线 Limit
* @note
* @author	Roc
* @since	2019.11.13
*/
void BitPm_Interface::setLimit(bool isLimt)
{
    globalUserVariable->gMeterParam.gConfig_Limit.nLimitFlg = isLimt;
    m_BitViewGauageDial->SetLimitOn(isLimt);
    if(getDisplayMode() > PM_DISPLAY_FORWARD_BEGIN&&  getDisplayMode() < PM_DISPLAY_FORWARD_END&& isLimt)
    {
        m_BitViewGauageDial->SetPowerUpLimit(getForwardUpperLimt(),PM_LAYER_LEFT);
        m_BitViewGauageDial->SetPowerDownLimit(getForwardLowerLimt(),PM_LAYER_LEFT);
    }
    if(getDisplayMode() > PM_DISPLAY_REVERSE_BEGIN&&  getDisplayMode() < PM_DISPLAY_REVERSE_EMD && isLimt)
    {
        m_BitViewGauageDial->SetPowerUpLimit(getReverseUpperLimt(),PM_LAYER_RIGHT);
        m_BitViewGauageDial->SetPowerDownLimit(getReverseLowerLimt(),PM_LAYER_RIGHT);
    }

    emit RedrawInfoShow(PM_LABEL_LIMIT);
    return;
}

qint32 BitPm_Interface::IsLimit()
{
    return globalUserVariable->gMeterParam.gConfig_Limit.nLimitFlg;
}

void BitPm_Interface::setForwardUpperLimt(qreal forwardUpperLimt)
{
    if(forwardUpperLimt > getAmptMax())
        forwardUpperLimt = getAmptMax();
    if(forwardUpperLimt < getAmptMin())
        forwardUpperLimt = getAmptMin();

    globalUserVariable->gMeterParam.gConfig_Limit.fForwardUp =forwardUpperLimt;

    m_BitViewGauageDial->SetPowerUpLimit( globalUserVariable->gMeterParam.gConfig_Limit.fForwardUp,PM_LAYER_LEFT);
    emit RedrawInfoShow(PM_LABEL_FORWARD_UP);
    return;
}

qreal BitPm_Interface::getForwardUpperLimt()
{
    qreal value;
    value = qMin(getAmptMax(),globalUserVariable->gMeterParam.gConfig_Limit.fForwardUp);

    if(globalUserVariable->gMeterParam.gConfig_Limit.fForwardLow < getAmptMax())
    {
        if(value < qMax(globalUserVariable->gMeterParam.gConfig_Limit.fForwardLow,getAmptMin()))
            value = qMax(globalUserVariable->gMeterParam.gConfig_Limit.fForwardLow,getAmptMin());
    }
    else
        value = qMax(value,getAmptMin());
    return value;

}

void BitPm_Interface::setForwardLowerLimt(qreal forwardLowerLimt)
{
    if(forwardLowerLimt > getAmptMax())
        forwardLowerLimt = getAmptMax();
    if(forwardLowerLimt < getAmptMin())
        forwardLowerLimt = getAmptMin();
    globalUserVariable->gMeterParam.gConfig_Limit.fForwardLow =forwardLowerLimt;

    m_BitViewGauageDial->SetPowerDownLimit( globalUserVariable->gMeterParam.gConfig_Limit.fForwardLow,PM_LAYER_LEFT);
    emit RedrawInfoShow(PM_LABEL_FORWARD_LOW);
    return;
}

qreal BitPm_Interface::getForwardLowerLimt()
{
    qreal value;
    value = qMax(getAmptMin(),globalUserVariable->gMeterParam.gConfig_Limit.fForwardLow);
    if(globalUserVariable->gMeterParam.gConfig_Limit.fForwardUp > getAmptMin())
    {
        if(value > qMin(globalUserVariable->gMeterParam.gConfig_Limit.fForwardUp,getAmptMax()))
            value = qMin(globalUserVariable->gMeterParam.gConfig_Limit.fForwardUp,getAmptMax());
    }
    else
        value = qMin(value,getAmptMax());
    return value;
}

void BitPm_Interface::setReverseUpperLimt(qreal reverseUpperLimt)
{
    if(reverseUpperLimt > getAmptMax())
        reverseUpperLimt = getAmptMax();
    if(reverseUpperLimt < getAmptMin())
        reverseUpperLimt = getAmptMin();


    globalUserVariable->gMeterParam.gConfig_Limit.fReverseUp =reverseUpperLimt;

    m_BitViewGauageDial->SetPowerUpLimit( globalUserVariable->gMeterParam.gConfig_Limit.fReverseUp,PM_LAYER_RIGHT);
    emit RedrawInfoShow(PM_LABEL_REVERSE_UP);
    return;
}

qreal BitPm_Interface::getReverseUpperLimt()
{
    qreal value;
    value = qMin(getAmptMax(),globalUserVariable->gMeterParam.gConfig_Limit.fReverseUp);
    if(globalUserVariable->gMeterParam.gConfig_Limit.fReverseLow < getAmptMax())
    {
        if(value < qMax(globalUserVariable->gMeterParam.gConfig_Limit.fReverseLow,getAmptMin()))
            value = qMax(globalUserVariable->gMeterParam.gConfig_Limit.fReverseLow,getAmptMin());
    }
    else
        value = qMax(value,getAmptMin());

    return value;
}

void BitPm_Interface::setReverseLowerLimt(qreal reverseLowerLimt)
{
    if(reverseLowerLimt > getAmptMax())
        reverseLowerLimt = getAmptMax();
    if(reverseLowerLimt < getAmptMin())
        reverseLowerLimt = getAmptMin();
    globalUserVariable->gMeterParam.gConfig_Limit.fReverseLow = reverseLowerLimt;

    m_BitViewGauageDial->SetPowerDownLimit( globalUserVariable->gMeterParam.gConfig_Limit.fReverseLow,PM_LAYER_RIGHT);

    emit RedrawInfoShow(PM_LABEL_REVERSE_LOW);
    return;
}

qreal BitPm_Interface::getReverseLowerLimt()
{
    qreal value;
    value = qMax(getAmptMin(),globalUserVariable->gMeterParam.gConfig_Limit.fReverseLow);
    if(globalUserVariable->gMeterParam.gConfig_Limit.fReverseUp > getAmptMin())
    {
        if(value > qMin(globalUserVariable->gMeterParam.gConfig_Limit.fReverseUp,getAmptMax()))
            value = qMin(globalUserVariable->gMeterParam.gConfig_Limit.fReverseUp , getAmptMax());
    }
    else
        value = qMin(value,getAmptMax());
    return value;
}

void BitPm_Interface::setLimtVidoBW(qint32 index)
{

}
qint32 BitPm_Interface::getLimtVidoBW()
{
    qint32 nVidoBW = 0;
    return nVidoBW;
}

void BitPm_Interface::setCCDF(qreal ccdf)
{

}
qint32 BitPm_Interface::getCCDF(){

    qint32 nCCDF = 0;
    return nCCDF;
}



void BitPm_Interface::setForwardDisplay(qint32 mDisMode)
{
    globalUserVariable->gMeterParam.gConfig_Display.nFordardMode = mDisMode;
    setDisplayMode(globalUserVariable->gMeterParam.gConfig_Display.nFordardMode + PM_DISPLAY_FORWARD_AVERAGE);

    if(globalUserVariable->gMeterParam.gConfig_Display.nFordardMode <2)
        setMeasureModle(globalUserVariable->gMeterParam.gConfig_Display.nFordardMode);

    if(IsLimit())
    {
        m_BitViewGauageDial->SetPowerUpLimit(getForwardUpperLimt(),PM_LAYER_LEFT);
        m_BitViewGauageDial->SetPowerDownLimit(getForwardLowerLimt(),PM_LAYER_LEFT);
    }
    emit RedrawInfoShow(PM_LABEL_MODE);
}
qint32 BitPm_Interface::getForwardDisplay()
{
    return globalUserVariable->gMeterParam.gConfig_Display.nFordardMode;
}

void BitPm_Interface::setReverseDisplay(qint32 mDisMode)
{
    globalUserVariable->gMeterParam.gConfig_Display.nReverseMode = mDisMode;
    setDisplayMode(globalUserVariable->gMeterParam.gConfig_Display.nReverseMode + PM_DISPLAY_REVERSE_AVERAGE);

    if(IsLimit())
    {
        m_BitViewGauageDial->SetPowerUpLimit(getReverseUpperLimt(),PM_LAYER_RIGHT);
        m_BitViewGauageDial->SetPowerDownLimit(getReverseLowerLimt(),PM_LAYER_RIGHT);
    }
    emit RedrawInfoShow(PM_LABEL_MODE);
}

qint32 BitPm_Interface::getReverseDisplay()
{
    return globalUserVariable->gMeterParam.gConfig_Display.nReverseMode;
}

void BitPm_Interface::setSummaryDisplay()
{
    setDisplayMode(PM_DISPLAY_SUMMARY);
}

qint32 BitPm_Interface::getSummaryDisplay()
{
    return  PM_DISPLAY_SUMMARY;
}


/**
* @brief Set Power Sensor name  V90 Or V91
* @note
* @author	Roc
* @since	2019.12.16
*/
void BitPm_Interface::setPowerSensorFlg(qint32 mSensorFlg)
{
    m_pPmComm->closePowerPort();
    initStateParam(globalUserVariable->m_nPowerSensorFlg);
    globalUserVariable->m_nPowerSensorFlg = mSensorFlg;
    setStateParam(mSensorFlg);

    emit RedrawInfoShow(PM_LABEL_MODE);
    QString strComFlg;
    if(0 == mSensorFlg)
        strComFlg = "ttyACM";
    else
        strComFlg = "ttyUSB";

    setSensorModle("");
    setSensorSN("");
    setSensorType("");
    setSensorFW("");
    analysisCommPort(2,strComFlg);

}

/**
* @brief Get Power Sensor Name  V90 Or V91
* @note
* @author	Roc
* @since	2019.12.16
*/
qint32 BitPm_Interface::getPowerSensorFlg()
{
    return globalUserVariable->m_nPowerSensorFlg;
}

void BitPm_Interface::setSensorModle(QString strModle)
{
    globalUserVariable->m_strPowerSensorModle = strModle;
}

QString BitPm_Interface::getSensorModle()
{
    return globalUserVariable->m_strPowerSensorModle;
}

void BitPm_Interface::setSensorSN(QString strSN)
{
    globalUserVariable->m_strPowerSensorSN = strSN;
}

QString BitPm_Interface::getSensorSN()
{
    return globalUserVariable->m_strPowerSensorSN;
}

void  BitPm_Interface::setSensorType(QString strType)
{
    globalUserVariable->m_strPowerSensorType = strType;
}

QString BitPm_Interface::getSensorType()
{
    return globalUserVariable->m_strPowerSensorType;
}

void BitPm_Interface::setSensorFW(QString strFW)
{
    globalUserVariable->m_strPowerSensorFW = strFW;
}

QString BitPm_Interface::getSensorFW()
{
    return globalUserVariable->m_strPowerSensorFW;
}

/**
* @brief get freq adjust string
* @note
* @author	Roc
* @since	2019.11.19
*/
QString BitPm_Interface::getFreqAdjustStr(qreal freq, qint32 DecPrecision)
{
    QString strCenterFreq;
    qreal freqVal = freq;

    if(freqVal >= PM_GHZ)
    {
        strCenterFreq = QString::number((qreal) freqVal / PM_GHZ,'f',DecPrecision);
        strCenterFreq.replace(rx,"");
        strCenterFreq += QString(" GHz");
    }
    else if(freqVal >= PM_MHZ)
    {
        strCenterFreq = QString::number((qreal) freqVal / PM_MHZ,'f',DecPrecision);
        strCenterFreq.replace(rx,"");
        strCenterFreq += QString(" MHz");
    }
    else if(freqVal >= PM_KHZ)
    {
        strCenterFreq = QString::number((qreal) freqVal / PM_KHZ,'f',DecPrecision);
        strCenterFreq.replace(rx,"");
        strCenterFreq += QString(" kHz");
    }
    else if(freqVal > 0)
    {
        strCenterFreq = QString::number((qreal) freqVal / PM_HZ,'f',DecPrecision);
        strCenterFreq.replace(rx,"");
        strCenterFreq += QString(" Hz");
    }
    else
    {
        strCenterFreq = QString("----");
    }
    return strCenterFreq;
}

QString BitPm_Interface::getFreqMHzAdjustStr( qint32  nFreq, qint32 DecPrecision)
{
    QString strCenterFreq;
    qreal freqVal = nFreq;

    if(freqVal >= 1000)
    {
        strCenterFreq = QString::number((qreal) freqVal / 1000,'f',DecPrecision);
        strCenterFreq.replace(rx,"");
        strCenterFreq += QString(" GHz");
    }
    else
    {
        strCenterFreq = QString::number((qreal) freqVal ,'f',DecPrecision);
        strCenterFreq.replace(rx,"");
        strCenterFreq += QString(" MHz");
    }
    return strCenterFreq;
}

/**
* @brief    将频率转换为MHz方式整型存放
* @note
* @author	Roc
* @since	2019.11.20
*/
quint16 BitPm_Interface::getFreqAdjustMHz(qulonglong  freq)
{
    quint16 nlCenterFreq = 0;
    nlCenterFreq =   freq / PM_MHZ;
    return nlCenterFreq;
}

/**
* @brief    调整功率探头V90校准频率
* @note
* @author	Roc
* @since	2020.3.4
*/
void BitPm_Interface::adjustFreqByCal(qulonglong llFreq)
{
   quint16 freq = getFreqAdjustMHz(llFreq);
   for(int nIndex = 1;nIndex<V90_CAL_NUM;nIndex++)
   {
       if(freq >= PM_CAL_FREQ[nIndex-1] && freq < PM_CAL_FREQ[nIndex])
       {
           int nFreqUp =  freq - PM_CAL_FREQ[nIndex-1];
           int nFreqDown = PM_CAL_FREQ[nIndex] - freq;
           if(nFreqUp < nFreqDown)
           {
               setCalCenterFreqMHz(PM_CAL_FREQ[nIndex-1]) ;
               break;
           }
           else
           {  setCalCenterFreqMHz( PM_CAL_FREQ[nIndex]);
               break;
           }
       }
       else if(freq == PM_CAL_FREQ[nIndex])
           setCalCenterFreqMHz( PM_CAL_FREQ[nIndex]);
   }
}


/**
* @brief  frequency unit.
* @param  frequency
* @author	Roc
* @since	2019.11.19
 */
qint32 BitPm_Interface::freqUnitFindProc(qreal freq)
{
    if (freq >= PM_GHZ)
        return UNIT_GHZ;
    else if (freq >= PM_MHZ)
        return UNIT_MHZ;
    else if (freq >= PM_KHZ)
        return UNIT_KHZ;
    else
        return UNIT_HZ;
}

/**
* @brief  frequency Base.
* @param  frequency
* @author	Roc
* @since	2019.11.19
 */
qreal BitPm_Interface::freqBaseFindProc(qreal freq)
{
    if (freq >= PM_GHZ)
        return  (double)PM_GHZ;
    else if (freq >= PM_MHZ)
        return (double)PM_MHZ;
    else if (freq >= PM_KHZ)
        return  (double)PM_KHZ;
    else
        return  (double)PM_HZ;
}
/**
* @brief  frequency unit.
* @param  frequency
* @author	Roc
* @since	2019.11.19
 */
qint32 BitPm_Interface::timeUnitFindProc(qreal time)
{
    if (time >= PM_S)
        return UNIT_S;
    else if (time >= PM_MS)
        return UNIT_MS;
    else if (time >= PM_US)
        return UNIT_US;
    else
        return UNIT_NS;
}

/**
* @brief get freq string
* @note
* @author	Roc
* @since	2019.11.19
*/
QString BitPm_Interface::getFreqStr(qint32 freqID)
{
    qreal freq = 0;
    switch(freqID)
    {
    case PM_BIT_CENTER_FREQ:
        freq = getCenterFreq();
        break;
    case PM_BIT_START_FREQ:
        freq = getStartFreq();
        break;
    case PM_BIT_STOP_FREQ:
        freq = getStopFreq();
        break;
    case PM_BIT_SPAN_FREQ:
        freq = getSpan();
        break;
    case PM_BIT_STEP_FREQ:
        freq = getStepFreq();
        break;
    default:
        break;
    }
    return getFreqAdjustStr(freq);
}

QString BitPm_Interface::dBmTransformToQstring(qint32 nUnitIndex,qreal value)
{
    QString strvalue;
    char str[20];
    switch (nUnitIndex) {
    case PM_NONE:
        strvalue = QString::number(value, 'f', 2) + " dB";
        break;
    case PM_DBM:
        strvalue = QString::number(value, 'f', 2) + " dBm";  // Double to String
        break;
    case PM_DBV:
        strvalue = QString::number((value + PM_dBVFix), 'f', 2) + " dBV" ;  // Double to String
        break;
    case PM_DBMV:
        strvalue = QString::number((value + PM_dBmVFix), 'f', 2) + " dBmV" ;  // Double to String
        break;
    case PM_DBUV:
        strvalue = QString::number((value + PM_dBuVFix), 'f', 2) + "dBuV";  // Double to String
        break;
    case PM_VOLT:
        globalUserVariable->dbmToVoltCalculatorAndDisplayFunc(str,value);
        strvalue = QString(str);
        break;
    case PM_WATTS:
        globalUserVariable->dbmToWattsCalculatorAndDisplayFunc(str,value);
        strvalue = QString(str);
        break;
    case PM_DELTA_VOLT:
        globalUserVariable->Delta_dbmToVoltCalculatorAndDisplayFunc(str,value);
        strvalue = QString(str);
        break;
    case PM_DELTA_WATTS:
        globalUserVariable->Delta_dbmToWattsCalculatorAndDisplayFunc(str,value);
        strvalue = QString(str);
        break;
    default:
        break;
    }
    return strvalue;
}

/**
* @brief    Get Power Sensor Info  V90 Or V91
* @note
* @author	Roc
* @since	2019.12.16
*/
void BitPm_Interface::cmd_GetSensorInventoryData()
{
    if(m_pPmComm->m_serialportPm->IsOpenPort())
    {
        setSensorModle("");
        setSensorSN("");
        setSensorType("");
        setSensorFW("");

        QByteArray commRecvData;
        if(POWER_SENSOR_V90 == globalUserVariable->m_nPowerSensorFlg)
        {
            commRecvData.clear();
            m_pPmComm->sendCommCmd(V90_INVENTORY_READ,commRecvData);
        }
        else if(POWER_SENSOR_V91 == globalUserVariable->m_nPowerSensorFlg)
        {
            commRecvData.clear();
            m_pPmComm->sendCommCmd(V91_INVENTORY_DATA_GET,commRecvData);
        }
    }
}
/**
* @brief	V90探头控制指令
* @note
* @Author	ROC
* @date     2020.1.3
*/

void BitPm_Interface::cmd_GetSensorControlData()
{
    if(m_pPmComm->m_serialportPm->IsOpenPort())
    {
        if(POWER_SENSOR_V91 == globalUserVariable->m_nPowerSensorFlg)
        {
            QByteArray commRecvData;
            m_pPmComm->sendCommCmd(V91_CONTROL_DATA_GET,commRecvData);
        }
    }
}

/**
* @brief	发送采集功率指令
* @note
* @Author	ROC
* @date     2019.11.20
*/
void BitPm_Interface::cmd_GetSensorPower(qint32 nContinous)
{
    if(m_pPmComm->m_serialportPm->IsOpenPort())
    {
        QByteArray commRecvData;

        quint8 nTimeInterval = 0;
        cmd_StopSensorContinousP();
        //注意发送的频率 V90 是Short  V91为int
        if(POWER_SENSOR_V90 == globalUserVariable->m_nPowerSensorFlg)
        {
            quint16 nFreqData;
            nFreqData= getFreqAdjustMHz(globalUserVariable->gMeterParam.gConfig_Freq.nlCenterFreq);
            if(nContinous == PM_CONT)
            {
                commRecvData.clear();
                nTimeInterval = getSweepTime();
                qint16ToQByteArrayByLowH(nFreqData,commRecvData);
                commRecvData.append(nTimeInterval);
                m_pPmComm->sendCommCmd(V90_CONTINUOUS_MODE,commRecvData);
            }
            else if(nContinous == PM_SINGLE)
            {
                commRecvData.clear();
                qint16ToQByteArrayByLowH(nFreqData,commRecvData);
                m_pPmComm->sendCommCmd(V90_SINGLE_MODE,commRecvData);
            }
        }
        else if(POWER_SENSOR_V91 == globalUserVariable->m_nPowerSensorFlg)
        {
            qint32 nFreqData;
            qint32 nMeasureOffset;
            nFreqData = getFreqAdjustMHz(globalUserVariable->gMeterParam.gConfig_Freq.nlCenterFreq)*100;
            nMeasureOffset= getMeasureOffset()*100;

            nTimeInterval = getSweepTime();

            if(nContinous == PM_CONT)
            {
                commRecvData.clear();
                nTimeInterval = getSweepTime();
                commRecvData.append((char*)&nFreqData, 4);
                commRecvData.append(getMeasureModle());
                commRecvData.append((char*)&nMeasureOffset, 4);
                commRecvData.append(nTimeInterval);
                m_pPmComm->sendCommCmd(V91_CONTINUOUS_MODE_GET,commRecvData);
            }
            else if(nContinous == PM_SINGLE)
            {
                commRecvData.clear();
                commRecvData.append((char*)&nFreqData, 4);
                commRecvData.append(getMeasureModle());
                commRecvData.append((char*)&nMeasureOffset, 4);
                m_pPmComm->sendCommCmd(V91_SINGLE_MODE_GET,commRecvData);
            }
        }
    }
}

/**
* @brief	发送停止采集功率指令
* @note
* @Author	ROC
* @date     2019.11.20
*/
void BitPm_Interface::cmd_StopSensorContinousP()
{
    if(PM_CONT == IsSweepContinous())
    {
        QByteArray commRecvData;
        quint8 nTimeInterval = 0;
        //注意发送的频率 V90 是Short  V91为int
        if(POWER_SENSOR_V90 == globalUserVariable->m_nPowerSensorFlg)
        {
            quint16 nFreqData;
            nFreqData= getFreqAdjustMHz(PM_V90_FREQ_MIN);
            nTimeInterval = 0;
            qint16ToQByteArrayByLowH(nFreqData,commRecvData);
            commRecvData.append(nTimeInterval);
            m_pPmComm->sendCommCmd(V90_CONTINUOUS_MODE,commRecvData);
        }
        else if(POWER_SENSOR_V91 == globalUserVariable->m_nPowerSensorFlg)
        {
            qint8 nMeasureModle;
            qint32 nFreqData;
            qint32 nMeasureOffset;
            nFreqData = getFreqAdjustMHz(PM_V91_FREQ_MIN)*100;
            nMeasureModle = 0;
            nMeasureOffset= 0;
            nTimeInterval = 0;
            commRecvData.append((char*)&nFreqData, 4);
            commRecvData.append((char*)&nMeasureModle,1);

            commRecvData.append((char*)&nMeasureOffset, 4);
            commRecvData.append(nTimeInterval);
            m_pPmComm->sendCommCmd(V91_CONTINUOUS_MODE_GET,commRecvData);
        }
        commRecvData.clear();
        int nTemp = 0;
        while(m_pPmComm->m_serialportPm->getSerialName()->waitForReadyRead(1000)&& nTemp <12)
        {
            commRecvData = m_pPmComm->m_serialportPm->getSerialName()->readAll(); //读取串口数据
            if(commRecvData.isEmpty())
            {
                usleep(100);
                nTemp++;
            }
            else
            {
                m_pPmComm->m_serialportPm->getSerialName()->clear();
                break;
            }
        }
    }
}

/**
* @brief	发送校准数据读取指令
* @note
* @Author	ROC
* @date     2020.1.3
*/
void BitPm_Interface::cmd_GetSensorCalibrationData()
{
    if(m_pPmComm->m_serialportPm->IsOpenPort())
    {
        quint16 nData;
        cmd_StopSensorContinousP();
        quint8 nSelectType = getCalSelectType();
        if(PM_CALIBRATION_FREQ == nSelectType)
        {
            nData = getCalCenterFreqMHz();
        }
        else
        {
            nData = getCalArray();
        }
        QByteArray commRecvData;
        //注意发送的频率 V90 是Short  V91为int
        if(POWER_SENSOR_V90 == globalUserVariable->m_nPowerSensorFlg)
        {
            //注意协议中，频率发送时高位在前，低位在后，接收时却是低位在前，高位在后
            commRecvData.append(nSelectType);
            qint16ToQByteArrayByHightL(nData,commRecvData);
            m_pPmComm->sendCommCmd(V90_CALIBRATION_TABLE_READ,commRecvData);
        }
        else if(POWER_SENSOR_V91 == globalUserVariable->m_nPowerSensorFlg)
        {
        }
    }
}

/**
* @brief	发送校准数据写指令
* @note
* @Author	ROC
* @date     2020.1.3
*/
void BitPm_Interface::cmd_setSensorCalibrationData()
{
    if(m_pPmComm->m_serialportPm->IsOpenPort())
    {
        quint16 nData;
        cmd_StopSensorContinousP();
        QByteArray commRecvData;
        //注意发送的频率 V90 是Short  V91为int
        if(POWER_SENSOR_V90 == globalUserVariable->m_nPowerSensorFlg)
        {
            nData = getCalArray();
            qint16ToQByteArrayByHightL(nData,commRecvData);
            nData = getCalCenterFreqMHz();
            qint16ToQByteArrayByLowH(nData,commRecvData);
            for(qint32 i = 0; i < PM_V90_CAL_AMPT;i++)
            {
                nData = qRound(m_fV90WriteCalData[i] * PM_CAL_MULTIPLE);
                qint16ToQByteArrayByLowH(nData,commRecvData);
            }
            m_pPmComm->sendCommCmd(V90_CALIBRATION_TABLE_WRITE,commRecvData);
        }
        else if(POWER_SENSOR_V91 == globalUserVariable->m_nPowerSensorFlg)
        {
        }
    }
}
void BitPm_Interface::adjustSpanFreq(qreal freq)
{
    freq = freq < 0 ? globalUserVariable->m_nMinSpan : freq;

    freq = globalUserVariable->adjustSpanBySpan(freq);

    globalUserVariable->adjustFreqBySpan(freq);
}

void BitPm_Interface::ChangeOtherUnitTodBm(qreal refLevel)
{
    qreal value = refLevel;
    switch (globalUserVariable->gMeterParam.gConfig_Ampt.nUnits) {
    case PM_WATTS: //
        value = globalUserVariable->wattsToDbmCalculatorFunc(refLevel);
        break;
    case PM_VOLT:  //
        value = globalUserVariable->voltToDbmCalculatorFunc(refLevel);
        break;
    case PM_DBMV:
        value -= PM_dBmVFix;
        break;
    case PM_DBUV:
        value -= PM_dBuVFix;
        break;
    case PM_DBV:
        value -= PM_dBVFix;
        break;
    default:
        value = refLevel;
        break;
    }
    // Only 2 decimal places reserved
    if(value >= 0)
    {
        value = (qreal)(qulonglong)((value + 0.005) * 100) / 100;
    }
    else
    {
        value = (qreal)(qulonglong)((value - 0.005) * 100) / 100;
    }

    return;
}

/**
* @brief BitPm_Interface::ChangedBmToOherUnit
* @param refLevel
* @return
 */
qreal BitPm_Interface::ChangedBmToOherUnit()
{
    qreal tempVal = 0.;
    qreal value = 0;
    qint32 unit = getAmptUint();
    switch (unit) {
    case PM_WATTS: //
        break;
    case PM_VOLT:  //
        value = qPow(50 * tempVal * 0.001, 0.5);//uv
        break;

    }
    return value;
}

/**
* @brief  设置线程等待时间
* @param
* @author Roc
* @since  2019.11.6
 */
void BitPm_Interface::setSleepTime(qreal sleepTime)
{
    globalUserVariable->gReadMeterDataSleepTime = sleepTime;
    return;
}

/**
* @brief
* @param
* @author	Roc
* @since	2019.11.13
*/
void BitPm_Interface::setDisplayMode(qint32 mDisMode)
{
    globalUserVariable->gMeterParam.gConfig_Display.nShowDisplayModle = mDisMode;
    m_BitViewGauageDial->setDisplayModle(globalUserVariable->gMeterParam.gConfig_Display.nShowDisplayModle);
    emit RedrawInfoShow(PM_LABEL_MODE);
    return;
}

/**
* @brief
* @param
* @author	Roc
* @since	2019.11.13
*/
qint32 BitPm_Interface::getDisplayMode()
{
    return globalUserVariable->gMeterParam.gConfig_Display.nShowDisplayModle;
}

//void BitPm_Interface::setSensorForward(qint32 isForward)
//{
//    globalUserVariable->gMeterParam.gConfig_Display.nForward = isForward;
//    return;
//}

//qint32 BitPm_Interface::IsSensorForward()
//{
//    return globalUserVariable->gMeterParam.gConfig_Display.nForward;
//}

//void BitPm_Interface::setSensorRelative(qint32 isReverse)
//{
//    globalUserVariable->gMeterParam.gConfig_Display.nReverse = isReverse;
//    return;
//}
//qint32 BitPm_Interface::IsSensorRelative()
//{
//    return globalUserVariable->gMeterParam.gConfig_Display.nReverse;
//}

/**
* @brief Init BitView
* @note
* @author Roc
* @since  2019.11.6
*/
void BitPm_Interface::InitBitView(QWidget *widget)
{
    m_viewbottomdisplay = PV_BOTTOM_STARTANDSTOP;
    m_viewtopdisplay    = PV_TOP_APMTINFO ;
    mWidth = widget->width();
    mHeight = widget->height();

    m_BitViewGauageDial = new BitGaugeDialView(widget);
    //    connect(m_BitViewGauageDial,SIGNAL(mouseDoubleClickedSig(bool)),this,SLOT(changeBitViewSize(bool)));

    // load state file at first
    qint32 LoadFileType = 0;
    qint32 loadState = 0;
    loadState = loadPresState();
    //     if no state files, state must set default.
    if(loadState < 0)
    {
        globalUserVariable->gfileType =PM_STATE_DEFAULT_FILE;
        PltSaveConditions(globalUserVariable->gfileType);
    }
    LoadFileType = PltLoadConditions(globalUserVariable->gfileType);
    //    if(globalUserVariable->gfileType < 0)
    //    {
    //        LoadFileType = PltLoadConditions(PM_STATE_LAST_FILE);
    //    }
    //    else
    //    {
    //        LoadFileType = PltLoadConditions(globalUserVariable->gfileType);
    //    }

    if(LoadFileType < 0)
    {
        QThread::msleep(200);
        //setDisplay(PM_DENSITY);
    }

    //Link mark judgment
    qint32 linkFlg = -1;
    linkFlg = loadLinkState();
    if(linkFlg >0) //link OK
    {
        //Read Plt Mode

    }
    else //No Link
    {
        //        LoadFileType = PltLoadConditions(globalUserVariable->gfileType);
        //    //    if(globalUserVariable->gfileType < 0)
        //    //    {
        //    //        LoadFileType = PltLoadConditions(PM_STATE_LAST_FILE);
        //    //    }
        //    //    else
        //    //    {
        //    //        LoadFileType = PltLoadConditions(globalUserVariable->gfileType);
        //    //    }
        //    //     if no state files, state must set default.
        //        if(LoadFileType < 0)
        //        {
        //            QThread::msleep(200);
        //        }

    }
    updateGeneralDataToBitview(PM_ACQ_INFO);


    //! must set display mode, or limit widget will not show header info.
    setSystemDisplay(PM_BIT_DEFAULTMODE);

    // delete unnecessary '0'
    rx.setPattern("(\\.){0,1}0+$");

    m_curSensorData.fPowerDatamW = 0;

    ReDrawLeftInfo();

    connect(this,SIGNAL(setUnitSingle(qint32)),this->m_BitViewGauageDial,SLOT(SetArcUnit(qint32)));
}

/**
* @brief Gobal Variable initial set
* @note
* @author	Roc
* @since	2019.11.19
*/
void BitPm_Interface::setGobalVariable(Pm_User_Variable *globalVariable)
{
    QMap<QString,bool>::iterator it;
    QStringList  listPotrStr;
    m_pPmComm->getPortNameList(listPotrStr);

    for(int i = 0;i<listPotrStr.size();i++)
    {
        it = m_mapComm.find(listPotrStr.at(i));
        if( it == m_mapComm.end())
        {
            m_mapComm.insert(listPotrStr.at(i),false);
        }
    }

    globalUserVariable = globalVariable;

    m_pPmComm = new Pm_Communication(this,globalVariable);
    connect(m_pPmComm->m_serialportPm,SIGNAL(StopRecvData()),this,SLOT(StopSendPower()));

    bGetDataFromScpi = 0;
    //    cmd_GetSensorControlData();
    return;
}

/**
* @brief BitPm_Interface::setZoomFlag
* @param isZoomIn
 * * @author Roc
* @since  2019.11.8
 */
void BitPm_Interface::setZoomFlag(bool isZoomIn)
{
    mIsZoomIn = isZoomIn;
    return;
}

/**
* @brief
* @param
* @author Roc
* @since  2019.11.8
*/
void BitPm_Interface::setDragFlag(bool dragFlag)
{
    mDragFlag = dragFlag;
    if(mIsZoomIn)
    {
        setZoomIn();
    }
    else
    {
        setZoomOut();
    }
    return;
}

/**
* @brief
* @param
* @author Roc
* @since  2019.11.8
*/
bool BitPm_Interface::getDragFlag()
{
    return mDragFlag;
}

/**
* @brief set zoom in
* @note
* @author Roc
* @since  2019.11.8
*/
void BitPm_Interface::setZoomIn()
{
    qint32 nHeight = mHeight;
    qint32 nWidth = mWidth;
    nWidth += 1;
    nHeight -= 4;
    //    m_BitViewGauageDial->setWindowRect(nWidth,nHeight);
    m_BitViewGauageDial->setGeometry(QRect(PM_PSTART_X,PM_PSTART_Y_BIG,nWidth - PM_RIGHT_INFO_WIDTH,(nHeight)));
    m_BitViewGauageDial->SetDrawRect(0,0,nWidth - PM_RIGHT_INFO_WIDTH,(nHeight));
    m_BitViewGauageDial->show();
    return;

}

/**
* @brief set zoom out
* @note
* @author Roc
* @since  2019.11.8
*/
void BitPm_Interface::setZoomOut()
{
    qint32 nHeight = mHeight;
    qint32 nWidth = mWidth;
    qint32 nLeftStartPos = 0;
    nHeight -= 4;

    if(mDragFlag)
    {
        nLeftStartPos = 21;
    }
    else
    {
        nLeftStartPos = PM_LEFT_INFO_WIDTH + 21;
    }
    m_BitViewGauageDial->setGeometry(QRect(nLeftStartPos,PM_TOP_INFO_HEIGHT + 3,
                                           nWidth - nLeftStartPos - PM_RIGHT_INFO_WIDTH,(nHeight - PM_TOP_INFO_HEIGHT)));

    m_BitViewGauageDial->SetDrawRect(0,0,
                                     nWidth - nLeftStartPos - PM_RIGHT_INFO_WIDTH,(nHeight - PM_TOP_INFO_HEIGHT));
    m_BitViewGauageDial->show();
    return;
}

/**
* @brief set shift key down flag
* @param[in] isEnable
* @author Roc
* @since  2019.11.8
*/
void BitPm_Interface::setShiftKeyEnable(bool isEnable)
{
    mIsShiftKeyEnable = isEnable;
    return;
}

/**
* @brief if shift key down flag
* @param none
* @author Roc
* @since  2019.11.8
*/
bool BitPm_Interface::isShiftKeyEnable()
{
    return mIsShiftKeyEnable;
}

/**
* @brief change bitview size
* @note
* @author Roc
* @since  2019.11.8
*/
void BitPm_Interface::changeSize(qint32 width, qint32 height)
{
    mWidth = width + 2;
    mHeight = height;
    return;
}

qreal BitPm_Interface::getMaxDialData()
{
    if(POWER_SENSOR_V90 == globalUserVariable->m_nPowerSensorFlg)
    {
        return PM_V90_POWER_MAX;
    }
    else if(POWER_SENSOR_V91 == globalUserVariable->m_nPowerSensorFlg)
    {
        return PM_V91_AVER_MAX;
    }
    return -100000;
}

qreal BitPm_Interface::getMinDialData()
{
    if(POWER_SENSOR_V90 == globalUserVariable->m_nPowerSensorFlg)
    {
        return PM_V90_POWER_MIN;
    }
    else if(POWER_SENSOR_V91 == globalUserVariable->m_nPowerSensorFlg)
    {
        return PM_V91_AVER_MIN;
    }
    return -100000;
}

/**
* @brief draw lines and spectrogram
* @note
* @Author	ROC
* @date	2019.12.4
*/
void BitPm_Interface::Draw()
{
    m_BitViewGauageDial->setCurentSensorData(m_curSensorData);
    return;
}

/**
* @brief
* @param
* @Author	ROC
* @date	2019.12.4
*  true---- suspend draw  false ---- start draw
*/
void BitPm_Interface::DrawFlag(bool isSuspend)
{
    globalUserVariable->gSuspendDrawFlag = isSuspend;
    return;
}

bool BitPm_Interface::getDrawFlag()
{
    return globalUserVariable->gSuspendDrawFlag;
}

/**
* @brief BitPm_Interface::getAdjustPersistenceTime
* @param time
* @return
 */
QString BitPm_Interface::getAdjustTimeStr(qreal time)
{
    //    qreal value = time;
    QString strVal;
    QString strUnit;
    if(time >= PM_S)
    {
        time /= PM_S;
        strVal = QString::number(time,'f',3);
        strUnit = QString(" s");
    }
    else if(time >= PM_MS)
    {
        time /= PM_MS;
        strVal = QString::number(time,'f',3);
        strUnit = QString(" ms");
    }
    else if(time >= PM_US)
    {
        time /= PM_US;
        strVal = QString::number(time,'f',3);
        strUnit = QString(" us");
    }
    else
    {
        time *= PM_NS;
        strVal = QString::number(time,'f',3);
        strUnit = QString(" ns");
    }
    strVal += strUnit;
    return strVal;
}

/**
* @brief ReDrawLeftInfo
* @param none
* @Author	ROC
* @date	2019.12.4
*/
void BitPm_Interface::ReDrawLeftInfo()
{
    for(qint32 i = PM_LABEL_MODE; i < PM_LABEL_END; i++)
    {
        emit RedrawInfoShow(i);
    }
    return;
}

/**
* @brief System Display set
* @note
* @Author	ROC
* @date	2019.12.4
*/
void BitPm_Interface::setSystemDisplay(qint32 sysDisplay)
{
    if(sysDisplay < PM_INDOOR)
        sysDisplay = PM_INDOOR;
    else if(sysDisplay > PM_NIGHT)
        sysDisplay = PM_NIGHT;

    globalUserVariable->gMeterParam.gConfig_Display.nSysDisplay = sysDisplay;

    m_BitViewGauageDial->setdisplaymode(sysDisplay);
    //  ???  m_BitViewGauageDial->refreshLayerBottom();
    emit RedrawInfoShow(PM_LABEL_DISPLAY);

}
qint32 BitPm_Interface::getSystemDisplay()
{
    return globalUserVariable->gMeterParam.gConfig_Display.nSysDisplay;
}

/**
* @brief update data to bitview
* @note
* @author	Roc
* @since	2019.11.18
*/
void BitPm_Interface::updateGeneralDataToBitview(qint32 datatype)
{
    switch (datatype) {
    case PM_FREQ_INFO:
        m_BitViewGauageDial->setFreqOffset(IsOffset());
        m_BitViewGauageDial->setFreqAttribute(PM_BIT_START_FREQ,getStartFreq());
        m_BitViewGauageDial->setFreqAttribute(PM_BIT_STOP_FREQ,getStopFreq());
        m_BitViewGauageDial->setFreqAttribute(PM_BIT_CENTER_FREQ,getCenterFreq());
        m_BitViewGauageDial->setFreqAttribute(PM_BIT_OFFSET_FREQ,getFreqOffset());
        m_BitViewGauageDial->setFreqAttribute(PM_BIT_SPAN_FREQ,getSpan());
        m_BitViewGauageDial->showBottomWordsMsg(m_viewbottomdisplay);
        break;
        //    case PM_SYS_INFO:

        //        m_BitViewGauageDial->setSystemAttribute(RUNNINGSTATE,globalUserVariable->gSweepType);
        //        m_BitViewGauageDial->refleshdisplay();

        //        break;
        //    case PM_FREQ_OFFSET:

        //        m_BitViewGauageDial->setFreqOffset(globalUserVariable->gfreqOffset);
        //        //            m_BitViewGauageDial->setFreqAttribute(PM_START_FREQ,globalUserVariable->gStartFreq);
        //        //            m_BitViewGauageDial->setFreqAttribute(PM_STOP_FREQ,globalUserVariable->gStopFreq);
        //        //            m_BitViewGauageDial->setFreqAttribute(PM_CENTER_FREQ,globalUserVariable->gCenterFreq);
        //        //            m_BitViewGauageDial->setFreqAttribute(PM_SPAN_FREQ,globalUserVariable->gSpanFreq);
        //        m_BitViewGauageDial->showBottomWordsMsg(m_viewbottomdisplay);
        //        m_BitViewGauageDial->markerUpdateByFreq();

        //        break;
    default:
        break;
    }
}

/**
* @brief refresh bitview bottom message
* @note
* @Author	ROC
* @date	2019.12.4
*/
void BitPm_Interface::showBitViewBottomMsg(qint32 bottomDisplay)
{
    m_BitViewGauageDial->showBottomWordsMsg(bottomDisplay);
    return;
}

/**
* @brief select current bieview
* @note
* @Author	ROC
* @date	2019.12.4
*/
void BitPm_Interface::setCurBitView(qint32 index)
{
    setcurrentview(index);
    return;
}

/**
* @brief saveDisplayParam
* @param [in] display
* @Author	ROC
* @date	2019.12.4
*/
void BitPm_Interface::saveDisplayParam(qint32 display)
{

    return;
}

/**
* @brief  loadDisplayParam
* @param [in] display
* @Author	ROC
* @date	2019.12.4
*/
void BitPm_Interface::loadDisplayParam(qint32 display)
{
    return;
}
/**
* @brief  analysisComport
* @param qint32 nAddOrRemove 2 shuaxin  1 -- Add 0 -- remove
* @Author	ROC
* @date	2019.12.4
*/
void BitPm_Interface::analysisCommPort(qint32 nAddOrRemove,QString strComFlg)
{
    QMap<QString,bool>::iterator it;
    if(2 == nAddOrRemove)
    {
        QStringList  listPotrStr;
        m_pPmComm->getPortNameList(listPotrStr);
        autoFindSensor(strComFlg);
    }
    if(1 == nAddOrRemove)
    {
        it = m_mapComm.find(strComFlg);
        if( it == m_mapComm.end())
        {
            m_mapComm.insert(strComFlg,false);
            autoFindSensor(strComFlg);
        }

    }
    else if(0 == nAddOrRemove)
    {
        for(it = m_mapComm.begin();it != m_mapComm.end(); )
        {
            if(it.key() == strComFlg)
            {

                if(true == it.value())
                {
                    m_pPmComm-> closePowerPort();
                }
                m_mapComm.erase(it++);
                autoFindSensor(strComFlg);
                break;
            }
        }
    }
}
/**
* @brief	自动查找USB 端口并打开
* @note
* @Author	ROC
* @date     2020.3.4
*/
void BitPm_Interface::autoFindSensor(QString strComFlg)
{
    bool bOpen = false;
   QMap<QString,bool>::iterator it;
   {
       for(it = m_mapComm.begin();it != m_mapComm.end(); it++)
       {
            if(true == it.value())
            {
                bOpen = true;
                break;
            }
       }
       if(false == bOpen)
       {
           for(it = m_mapComm.begin();it != m_mapComm.end();)
           {
               m_strCommName = it.key();
               if(1>strComFlg.size())
               {
                   if(-1< m_strCommName.indexOf("ttyACM"))
                   {
                       initStateParam(globalUserVariable->m_nPowerSensorFlg);
                       globalUserVariable->m_nPowerSensorFlg = 0;
                       setStateParam(globalUserVariable->m_nPowerSensorFlg );

                       emit RedrawInfoShow(PM_LABEL_MODE);
                       m_pPmComm->openPowerPort(m_strCommName);
                       if(sendConnectCommand())
                       {
                           it.value() = true;
                           return;
                       }
                       else
                       {
                           m_mapComm.erase(it++);
                       }

                   }
                   else if(-1< m_strCommName.indexOf("ttyUSB"))
                   {
                       initStateParam(globalUserVariable->m_nPowerSensorFlg);
                       globalUserVariable->m_nPowerSensorFlg = 1;
                       setStateParam(globalUserVariable->m_nPowerSensorFlg );

                       emit RedrawInfoShow(PM_LABEL_MODE);
                       m_pPmComm->openPowerPort(m_strCommName);
                       if(sendConnectCommand())
                       {
                           it.value() = true;
                           it++;
                           break;
                       }
                       else
                       {
                           m_mapComm.erase(it++);
                       }

                   }
                   else
                   {
                       m_mapComm.erase(it++);
                   }
               }
               else
               {
                   if(-1< m_strCommName.indexOf(strComFlg))
                   {
                       initStateParam(globalUserVariable->m_nPowerSensorFlg);

                       if(-1< m_strCommName.indexOf("ttyACM"))
                           globalUserVariable->m_nPowerSensorFlg = 0;
                       else if(-1< m_strCommName.indexOf("ttyUSB"))
                           globalUserVariable->m_nPowerSensorFlg = 1;

                       setStateParam(globalUserVariable->m_nPowerSensorFlg );

                       emit RedrawInfoShow(PM_LABEL_MODE);
                       m_pPmComm->openPowerPort(m_strCommName);
                       if(sendConnectCommand())
                       {
                           it.value() = true;
                           it++;
                           break;
                       }
                       else
                       {
                           m_mapComm.erase(it++);
                       }
                   }
                   else
                   {
                       m_mapComm.erase(it++);
                   }
               }
           }
       }
   }
}


bool BitPm_Interface::sendConnectCommand()
{
    int nFlg = 0;
    while(nFlg < 10)
    {
        cmd_GetSensorInventoryData();
        QEventLoop loop;
        QTimer::singleShot(1000, &loop, SLOT(quit()));
        loop.exec();
        if(-1<globalUserVariable->m_strPowerSensorSN.size())
        {

            break;
        }
        else
            nFlg++;

    }
    if(nFlg < 10)
        return true;
    else
        return false;
}



/**
* @brief getGlobalUserVariable
* @param none
* @Author	ROC
* @date	2019.12.4
*/
Pm_User_Variable* BitPm_Interface::getGlobalUserVariable()
{
    return globalUserVariable;
}

/**
* @brief
* @param
* @Author	ROC
* @date	2019.12.4
*/
void BitPm_Interface::PltCurAnaMode(qint32 imod)
{
    globalUserVariable->startMode = imod;
    return;
}

/**
* @brief PltSaveConditions
* @param itype file type 0 means default.cond 1 means last.cond 2 means user.cond
* @Author	ROC
* @date	2019.12.4
*/
qint32 BitPm_Interface::PltSaveConditions(qint32 itype)
{
    qint32 ret = -1;
    switch (itype) {
    case PM_STATE_DEFAULT_FILE:
        //        savePresState();
        initDefaultParam();
        ret = saveState(PM_DEFAULT_COND);
        break;
    case PM_STATE_LAST_FILE:
        //        savePresState();
        initStateParam(globalUserVariable->m_nPowerSensorFlg);
        ret = saveState(PM_LAST_COND);
        break;
    case PM_STATE_USER_FILE:
        //        savePresState();
        initStateParam(globalUserVariable->m_nPowerSensorFlg);
        ret = saveState(PM_USER_COND);
        break;
    default:
        break;
    }
    return ret;
}

/**
* @brief PltLoadConditions
* @param itype file type 0 means default.cond 1 means last.cond 2 means user.cond
* @Author	ROC
* @date	2019.12.4
*/
qint32 BitPm_Interface::PltLoadConditions(qint32 itype)
{
    qint32 ret = -1;
    switch (itype) {
    case PM_STATE_DEFAULT_FILE:
        //        loadPresState();
        ret = loadState(PM_DEFAULT_COND);
        break;
    case PM_STATE_LAST_FILE:
        //        loadPresState();
        ret = loadState(PM_LAST_COND);
        break;
    case PM_STATE_USER_FILE:
        //        loadPresState();
        ret = loadState(PM_USER_COND);
        break;
    default:
        ret = loadState(PM_DEFAULT_COND);
        break;
    }
    //    globalUserVariable->gfileType = itype;
    return ret;
}

qint32 BitPm_Interface::PltSavePres(qint32 itype)
{
    qint32 iback = -1;
    globalUserVariable->gfileType = itype;
    iback = savePresState();
    return iback;
}

void BitPm_Interface::initDefaultParam()
{
    //V90 Power Sensor para
    //Freq
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Freq.nlCenterFreq = (PM_V90_FREQ_MAX + PM_V90_FREQ_MIN) / 2;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Freq.nlStartFreq =   PM_V90_FREQ_MIN;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Freq.nlStopFreq =   PM_V90_FREQ_MAX;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Freq.nlStepFreq = 1000000LL;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Freq.nlSpan = 1000000LL;
//    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Freq.nlSpanUp = 1;
//    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Freq.nlSpanDown = 1;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Freq.nlLastSpan = 1;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Freq.nSpanType = PM_NORMAL_SPAN;

    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Freq.nChannelStd = PM_CDMA - 1;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Freq.nChannelSelID = 0;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Freq.nChannelNumber = 0;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Freq.nChannelStep = mPM_ChStand[PM_CDMA].ChStep;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Freq.nOffsetFreqOn = PM_BUTTON_OFF;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Freq.nlOffsetFreq = 0;
//    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Freq.nlOffsetFreqSize =  m_sensorStateParam[POWER_SENSOR_V90].gConfig_Freq.nlStepFreq;

    //amplitude
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Ampt.fMax = PM_V90_POWER_MAX;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Ampt.fMin = PM_V90_POWER_MIN;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Ampt.fOffset = 0;

    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Ampt.nForwardRelative = PM_BUTTON_OFF;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Ampt.nReverseRelative = PM_BUTTON_OFF;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Ampt.fForwardRelativeData = 0;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Ampt.fReverseRelativeData = 0;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Ampt.nUnits = 0;

    //sweep
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Sweep.nSweepType = PM_CONT;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Sweep.nTimeInterval = 1;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Sweep.fDutyCycle = 100.0;
    //ave
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Ave.nAcquisition = PM_AVERAGE_FAST;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Ave.bIsAverageFlg = false;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Ave.nRunningAverage = PM_RUNNING_AVERAGE_MIN;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Ave.nMaxHold = PM_BUTTON_OFF;

    //Zero
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Zero.nZero = PM_BUTTON_OFF;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Zero.m_fZeroBaseForward = 0;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Zero.m_fZeroBaseReverse = 0;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Zero.nSelectCalType = PM_CALIBRATION_ARRAY;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Zero.nArray = 0;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Zero.nFreq = 10;
    //    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Zero.nlCenterFreq = 0;
    //    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Zero.nZeroChannelStd = 0;

    //Measure
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Measure.nModle = PM_MEASUER_AVG;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Measure.fOffset = 0;
    //Limit
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Limit.nLimitFlg = PM_BUTTON_OFF;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Limit.fForwardUp = 1.0;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Limit.fForwardLow = 1.0;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Limit.fReverseUp = 1.0;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Limit.fReverseLow = 1.0;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Limit.nVideoBw = PM_BUTTON_OFF;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Limit.fCCDF = PM_BUTTON_OFF;

    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Display.nShowDisplayModle = PM_DISPLAY_FORWARD_AVERAGE;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Display.nFordardMode = 0;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Display.nReverseMode = 0;
    m_sensorStateParam[POWER_SENSOR_V90].gConfig_Display.nSysDisplay = PM_BIT_DEFAULTMODE;
    //V91 power Sensor Para
    //Freq
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Freq.nlCenterFreq = (PM_V91_FREQ_MAX + PM_V91_FREQ_MIN) / 2;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Freq.nlStartFreq =   PM_V91_FREQ_MIN;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Freq.nlStopFreq =   PM_V91_FREQ_MAX;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Freq.nlStepFreq = 1000000LL;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Freq.nlSpan = 2000000LL;
//    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Freq.nlSpanUp = 1;
//    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Freq.nlSpanDown = 1;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Freq.nlLastSpan = 1;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Freq.nSpanType = PM_NORMAL_SPAN;

    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Freq.nChannelStd = PM_CDMA - 1;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Freq.nChannelSelID = 0;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Freq.nChannelNumber = 0;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Freq.nChannelStep = mPM_ChStand[PM_CDMA].ChStep;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Freq.nOffsetFreqOn = PM_BUTTON_OFF;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Freq.nlOffsetFreq = 0;
//    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Freq.nlOffsetFreqSize =  m_sensorStateParam[POWER_SENSOR_V91].gConfig_Freq.nlStepFreq;

    //amplitude
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Ampt.fMax = PM_V91_AVER_MAX;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Ampt.fMin = PM_V91_AVER_MIN;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Ampt.fOffset = 0;

    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Ampt.nForwardRelative = PM_BUTTON_OFF;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Ampt.nReverseRelative = PM_BUTTON_OFF;

    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Ampt.fForwardRelativeData = 0;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Ampt.fReverseRelativeData = 0;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Ampt.nUnits = 0;

    //sweep
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Sweep.nSweepType = PM_CONT;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Sweep.nTimeInterval = 1;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Sweep.fDutyCycle = 100.0;

    //ave
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Ave.nAcquisition = PM_AVERAGE_FAST;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Ave.nRunningAverage = PM_RUNNING_AVERAGE_MIN;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Ave.nMaxHold = PM_BUTTON_OFF;

    //Zero
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Zero.nZero = PM_BUTTON_OFF;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Zero.m_fZeroBaseForward = 0;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Zero.m_fZeroBaseReverse = 0;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Zero.nSelectCalType = PM_CALIBRATION_ARRAY;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Zero.nArray = 0;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Zero.nFreq = 10;

    //    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Zero.nlCenterFreq = 0;
    //    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Zero.nZeroChannelStd = 0;

    //Measure
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Measure.nModle = PM_MEASUER_AVG;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Measure.fOffset = 0;

    //Limit
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Limit.nLimitFlg = PM_BUTTON_OFF;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Limit.fForwardUp = 1.0;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Limit.fForwardLow = 1.0;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Limit.fReverseUp = 1.0;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Limit.fReverseLow = 1.0;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Limit.nVideoBw = PM_BUTTON_OFF;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Limit.fCCDF = PM_BUTTON_OFF;

    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Display.nShowDisplayModle = PM_DISPLAY_FORWARD_AVERAGE;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Display.nFordardMode = 0;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Display.nReverseMode = 0;
    m_sensorStateParam[POWER_SENSOR_V91].gConfig_Display.nSysDisplay = PM_BIT_DEFAULTMODE;

    return;
}

/**
* @brief initStateParam
* @param init state struct
* @author	Roc
* @since	2019.11.13
*/
void BitPm_Interface::initStateParam(qint32 nSensorType)
{
    //Freq
    m_sensorStateParam[nSensorType].gConfig_Freq.nlCenterFreq =globalUserVariable->gMeterParam.gConfig_Freq.nlCenterFreq;
    m_sensorStateParam[nSensorType].gConfig_Freq.nlStartFreq =globalUserVariable->gMeterParam.gConfig_Freq.nlStartFreq;
    m_sensorStateParam[nSensorType].gConfig_Freq.nlStopFreq =globalUserVariable->gMeterParam.gConfig_Freq.nlStopFreq;
    m_sensorStateParam[nSensorType].gConfig_Freq.nlStepFreq =globalUserVariable->gMeterParam.gConfig_Freq.nlStepFreq ;
    m_sensorStateParam[nSensorType].gConfig_Freq.nlSpan =globalUserVariable->gMeterParam.gConfig_Freq.nlSpan;
//    m_sensorStateParam[nSensorType].gConfig_Freq.nlSpanUp =globalUserVariable->gMeterParam.gConfig_Freq.nlSpanUp;
//    m_sensorStateParam[nSensorType].gConfig_Freq.nlSpanDown =globalUserVariable->gMeterParam.gConfig_Freq.nlSpanDown;
    m_sensorStateParam[nSensorType].gConfig_Freq.nlLastSpan =globalUserVariable->gMeterParam.gConfig_Freq.nlLastSpan;
    m_sensorStateParam[nSensorType].gConfig_Freq.nSpanType =globalUserVariable->gMeterParam.gConfig_Freq.nSpanType;

    m_sensorStateParam[nSensorType].gConfig_Freq.nChannelStd =globalUserVariable->gMeterParam.gConfig_Freq.nChannelStd;
    m_sensorStateParam[nSensorType].gConfig_Freq.nChannelSelID =globalUserVariable->gMeterParam.gConfig_Freq.nChannelSelID;
    m_sensorStateParam[nSensorType].gConfig_Freq.nChannelNumber =globalUserVariable->gMeterParam.gConfig_Freq.nChannelNumber;
    m_sensorStateParam[nSensorType].gConfig_Freq.nChannelStep =globalUserVariable->gMeterParam.gConfig_Freq.nChannelStep;
    m_sensorStateParam[nSensorType].gConfig_Freq.nOffsetFreqOn =globalUserVariable->gMeterParam.gConfig_Freq.nOffsetFreqOn;
    m_sensorStateParam[nSensorType].gConfig_Freq.nlOffsetFreq =globalUserVariable->gMeterParam.gConfig_Freq.nlOffsetFreq;
//    m_sensorStateParam[nSensorType].gConfig_Freq.nlOffsetFreqSize =globalUserVariable->gMeterParam.gConfig_Freq.nlOffsetFreqSize;

    //amplitude
    m_sensorStateParam[nSensorType].gConfig_Ampt.fMax = globalUserVariable->gMeterParam.gConfig_Ampt.fMax;
    m_sensorStateParam[nSensorType].gConfig_Ampt.fMin =globalUserVariable->gMeterParam.gConfig_Ampt.fMin;
    m_sensorStateParam[nSensorType].gConfig_Ampt.fOffset =globalUserVariable->gMeterParam.gConfig_Ampt.fOffset;
    m_sensorStateParam[nSensorType].gConfig_Ampt.nForwardRelative =globalUserVariable->gMeterParam.gConfig_Ampt.nForwardRelative;
    m_sensorStateParam[nSensorType].gConfig_Ampt.nReverseRelative =globalUserVariable->gMeterParam.gConfig_Ampt.nReverseRelative;
    m_sensorStateParam[nSensorType].gConfig_Ampt.fForwardRelativeData =globalUserVariable->gMeterParam.gConfig_Ampt.fForwardRelativeData;
    m_sensorStateParam[nSensorType].gConfig_Ampt.fReverseRelativeData =globalUserVariable->gMeterParam.gConfig_Ampt.fReverseRelativeData;
    m_sensorStateParam[nSensorType].gConfig_Ampt.nUnits =globalUserVariable->gMeterParam.gConfig_Ampt.nUnits;

    //sweep
    m_sensorStateParam[nSensorType].gConfig_Sweep.nSweepType =globalUserVariable->gMeterParam.gConfig_Sweep.nSweepType;
    m_sensorStateParam[nSensorType].gConfig_Sweep.nTimeInterval =globalUserVariable->gMeterParam.gConfig_Sweep.nTimeInterval;
    m_sensorStateParam[nSensorType].gConfig_Sweep.fDutyCycle =globalUserVariable->gMeterParam.gConfig_Sweep.fDutyCycle;

    //ave
    m_sensorStateParam[nSensorType].gConfig_Ave.nAcquisition =globalUserVariable->gMeterParam.gConfig_Ave.nAcquisition;
    m_sensorStateParam[nSensorType].gConfig_Ave.bIsAverageFlg =globalUserVariable->gMeterParam.gConfig_Ave.bIsAverageFlg;
    m_sensorStateParam[nSensorType].gConfig_Ave.nRunningAverage =globalUserVariable->gMeterParam.gConfig_Ave.nRunningAverage;
    m_sensorStateParam[nSensorType].gConfig_Ave.nMaxHold =globalUserVariable->gMeterParam.gConfig_Ave.nMaxHold;

    //Zero
    m_sensorStateParam[nSensorType].gConfig_Zero.nZero =globalUserVariable->gMeterParam.gConfig_Zero.nZero;
    m_sensorStateParam[nSensorType].gConfig_Zero.m_fZeroBaseForward =globalUserVariable->gMeterParam.gConfig_Zero.m_fZeroBaseForward;
    m_sensorStateParam[nSensorType].gConfig_Zero.m_fZeroBaseReverse =globalUserVariable->gMeterParam.gConfig_Zero.m_fZeroBaseReverse;
    m_sensorStateParam[nSensorType].gConfig_Zero.nSelectCalType =globalUserVariable->gMeterParam.gConfig_Zero.nSelectCalType;
    m_sensorStateParam[nSensorType].gConfig_Zero.nArray =globalUserVariable->gMeterParam.gConfig_Zero.nArray;
    m_sensorStateParam[nSensorType].gConfig_Zero.nFreq =globalUserVariable->gMeterParam.gConfig_Zero.nFreq;

    //    m_sensorStateParam[nSensorType].gConfig_Zero.nlCenterFreq =globalUserVariable->gMeterParam.gConfig_Zero.nlCenterFreq;
    //    m_sensorStateParam[nSensorType].gConfig_Zero.nZeroChannelStd =globalUserVariable->gMeterParam.gConfig_Zero.nZeroChannelStd;

    //Measure
    m_sensorStateParam[nSensorType].gConfig_Measure.nModle =globalUserVariable->gMeterParam.gConfig_Measure.nModle;
    m_sensorStateParam[nSensorType].gConfig_Measure.fOffset =globalUserVariable->gMeterParam.gConfig_Measure.fOffset;

    //Limit
    m_sensorStateParam[nSensorType].gConfig_Limit.nLimitFlg =globalUserVariable->gMeterParam.gConfig_Limit.nLimitFlg;
    m_sensorStateParam[nSensorType].gConfig_Limit.fForwardUp =globalUserVariable->gMeterParam.gConfig_Limit.fForwardUp;
    m_sensorStateParam[nSensorType].gConfig_Limit.fForwardLow =globalUserVariable->gMeterParam.gConfig_Limit.fForwardLow;
    m_sensorStateParam[nSensorType].gConfig_Limit.fReverseUp =globalUserVariable->gMeterParam.gConfig_Limit.fReverseUp;
    m_sensorStateParam[nSensorType].gConfig_Limit.fReverseLow =globalUserVariable->gMeterParam.gConfig_Limit.fReverseLow;
    m_sensorStateParam[nSensorType].gConfig_Limit.nVideoBw =globalUserVariable->gMeterParam.gConfig_Limit.nVideoBw;
    m_sensorStateParam[nSensorType].gConfig_Limit.fCCDF =globalUserVariable->gMeterParam.gConfig_Limit.fCCDF;
    //display
    m_sensorStateParam[nSensorType].gConfig_Display.nFordardMode = globalUserVariable->gMeterParam.gConfig_Display.nFordardMode;
    m_sensorStateParam[nSensorType].gConfig_Display.nReverseMode = globalUserVariable->gMeterParam.gConfig_Display.nReverseMode;
    m_sensorStateParam[nSensorType].gConfig_Display.nShowDisplayModle = globalUserVariable->gMeterParam.gConfig_Display.nShowDisplayModle;
    m_sensorStateParam[nSensorType].gConfig_Display.nSysDisplay = globalUserVariable->gMeterParam.gConfig_Display.nSysDisplay;

    return;
}

/**
* @brief
* @param
* @author	Roc
* @since	2019.11.13
*/
void BitPm_Interface::setStateParam(qint32 nSensorType)
{
    globalUserVariable->gRefreshAllParam = true;
    changeBitViewSize(false);
    //Freq
    setCHStandard(m_sensorStateParam[nSensorType].gConfig_Freq.nChannelStd);
    setChannelNumber(m_sensorStateParam[nSensorType].gConfig_Freq.nChannelNumber);

    setCenterFreq(m_sensorStateParam[nSensorType].gConfig_Freq.nlCenterFreq);
    setStartFreq(m_sensorStateParam[nSensorType].gConfig_Freq.nlStartFreq);
    setStopFreq(m_sensorStateParam[nSensorType].gConfig_Freq.nlStopFreq);
    setStepFreq(m_sensorStateParam[nSensorType].gConfig_Freq.nlStepFreq);
    setSpan(m_sensorStateParam[nSensorType].gConfig_Freq.nlSpan);
    setOffset(m_sensorStateParam[nSensorType].gConfig_Freq.nOffsetFreqOn);
    setFreqOffset(m_sensorStateParam[nSensorType].gConfig_Freq.nlOffsetFreq);
//    setFreqOffsetSize(m_sensorStateParam[nSensorType].gConfig_Freq.nlOffsetFreqSize);

    //ampt
    setAmptMax(m_sensorStateParam[nSensorType].gConfig_Ampt.fMax);
    setAmptMin(m_sensorStateParam[nSensorType].gConfig_Ampt.fMin);
    setAmptOffset(m_sensorStateParam[nSensorType].gConfig_Ampt.fOffset);
    setAmptUnit(m_sensorStateParam[nSensorType].gConfig_Ampt.nUnits);
    setAmptForwardRelative(m_sensorStateParam[nSensorType].gConfig_Ampt.nForwardRelative);
    setAmptReverseRelative(m_sensorStateParam[nSensorType].gConfig_Ampt.nReverseRelative);
    setAmptForwardRelativeData(m_sensorStateParam[nSensorType].gConfig_Ampt.fForwardRelativeData);
    setAmptReverseRelativeData(m_sensorStateParam[nSensorType].gConfig_Ampt.fReverseRelativeData);
    //Sweep
    globalUserVariable->gMeterParam.gConfig_Sweep.nSweepType =  m_sensorStateParam[nSensorType].gConfig_Sweep.nSweepType;
    setSweepTime(m_sensorStateParam[nSensorType].gConfig_Sweep.nTimeInterval);
    setDutyCycle(m_sensorStateParam[nSensorType].gConfig_Sweep.fDutyCycle);
    setMeasureOffset(m_sensorStateParam[nSensorType].gConfig_Measure.fOffset);

    //Average
    setAveragePoint(m_sensorStateParam[nSensorType].gConfig_Ave.nRunningAverage);
    setRunningAverage(m_sensorStateParam[nSensorType].gConfig_Ave.bIsAverageFlg);
    setMaxHold(m_sensorStateParam[nSensorType].gConfig_Ave.nMaxHold);
    //Zero
    globalUserVariable->gMeterParam.gConfig_Zero.nFreq =  m_sensorStateParam[nSensorType].gConfig_Zero.nFreq;
    setCalSelectType(m_sensorStateParam[nSensorType].gConfig_Zero.nSelectCalType);
    setCalArray(m_sensorStateParam[nSensorType].gConfig_Zero.nSelectCalType);

    //Limt
    setLimit(m_sensorStateParam[nSensorType].gConfig_Limit.nLimitFlg);
    setForwardUpperLimt(m_sensorStateParam[nSensorType].gConfig_Limit.fForwardUp);
    setForwardLowerLimt(m_sensorStateParam[nSensorType].gConfig_Limit.fForwardLow);
    setReverseUpperLimt(m_sensorStateParam[nSensorType].gConfig_Limit.fReverseUp);
    setReverseLowerLimt(m_sensorStateParam[nSensorType].gConfig_Limit.fReverseLow);
    setCCDF(m_sensorStateParam[nSensorType].gConfig_Limit.fCCDF);

    //display
    globalUserVariable->gMeterParam.gConfig_Display.nFordardMode = m_sensorStateParam[nSensorType].gConfig_Display.nFordardMode;
    globalUserVariable->gMeterParam.gConfig_Display.nReverseMode = m_sensorStateParam[nSensorType].gConfig_Display.nReverseMode;
    if(POWER_SENSOR_V90 == nSensorType)
    {
        setDisplayMode(PM_DISPLAY_V90_POWER);
    }
    else
    {
        setForwardDisplay(globalUserVariable->gMeterParam.gConfig_Display.nFordardMode);
        setReverseDisplay(globalUserVariable->gMeterParam.gConfig_Display.nReverseMode);
    }
    setSystemDisplay(m_sensorStateParam[nSensorType].gConfig_Display.nSysDisplay);
    QThread::msleep(200);
    return;
}

/**
* @brief saveState
* @param fileName full path file name
* @Author	ROC
* @date	2019.12.4
*/
qint32 BitPm_Interface::saveState(QString fileName)
{
    qint32 back = -1;
    mFileType = (qulonglong)PM_FILEHEADER_STATE;
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
    {
        return back;
    }
    else
    {
        file.write((char *)&m_sensorStateParam, sizeof(m_sensorStateParam));
    }
    file.close();
    file.flush();
    back = 0;
    return back;
}

/**
* @brief loadState
* @param fileName full path file name
* @Author	ROC
* @date	2019.12.4
*/
qint32 BitPm_Interface::loadState(QString fileName)
{
    qint32 back = -1;
    //    back = loadPresState();

    memset(&m_sensorStateParam,0,sizeof(m_sensorStateParam));
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        return back;
    }
    else
    {
        file.read((char *)&m_sensorStateParam, sizeof(m_sensorStateParam));
    }
    file.close();
    back = 1;
    setStateParam(globalUserVariable->m_nPowerSensorFlg);

    analysisCommPort(2);
    return back;
}

qint32 BitPm_Interface::PltSaveLinkFlg(qint32 itype)
{
    qint32 ireturndata = -1;
    switch(itype)
    {
    case PM_LINK_NG:
        globalUserVariable->gLinkfileType = PM_LINK_FLG_LOAD;
        break;
    case PM_LINK_OK:
        globalUserVariable->gLinkfileType = PM_LINK_FLG_READ;
        break;
    default:
        globalUserVariable->gLinkfileType = PM_LINK_FLG_DEFULT;
        break;
    }
    ireturndata = saveLinkState();
    return ireturndata;
}

/**
* @brief
* @param
* @Author Roc
* @date 2019-10-18
*/
void BitPm_Interface::PltCurLinkMode(qint32 imod)
{
    globalUserVariable->linkMode = imod;
    return;
}

/**
* @brief Save linked device flag
* @param
* @Author Roc
* @date 2019-10-17
*/
qint32 BitPm_Interface::saveLinkState()
{
    qint32 returnData = -1;
    _PM_CONFIG_LINK_ linkParam;
    linkParam.linkMode = globalUserVariable->linkMode;
    linkParam.linkFileType = globalUserVariable->gLinkfileType;

    QFile file(PM_LINK_STATE_FILE);
    if(!file.open(QIODevice::WriteOnly))
    {
        //Un Know when to use it
        return returnData;
    }
    else
    {
        returnData = 1;
        file.write((char *)&linkParam, sizeof(linkParam));
    }
    file.close();
    file.flush();
    return returnData;
}

/**
* @brief Load linked device flag
* @param
* @Author Roc
* @date 2019-10-17
*/
qint32 BitPm_Interface::loadLinkState()
{
    qint32 returnData = -1;
    _PM_CONFIG_LINK_ linkParam;
    memset(&linkParam,0,sizeof(linkParam));
    QFile file(PM_LINK_STATE_FILE);

    if(!file.open(QIODevice::ReadOnly))
    {   //If there are no pm_state.lin  Indicates that the file has just started running or has been deleted
        globalUserVariable->gLinkfileType = PM_LINK_FLG_DEFULT;
        return returnData;
    }
    else
    {

        globalUserVariable->gLinkfileType =  linkParam.linkFileType;
        returnData = 1;
        file.read((char *)&linkParam, sizeof(linkParam));
    }
    file.close();
    return returnData;
}

/**
* @brief
* @param
* @Author	ROC
* @date	2019.12.4
*/
qint32 BitPm_Interface::savePresState()
{
    qint32 back = -1;
    _PM_CONFIG_PRESET_ presParam;
    presParam.nStartMode = globalUserVariable->startMode;
    presParam.nStartFileType = globalUserVariable->gfileType;

    QFile file(PM_PRE_STATE_FILE);
    if(!file.open(QIODevice::WriteOnly))
    {
        return back;
    }
    else
    {
        file.write((char *)&presParam, sizeof(presParam));
    }
    file.close();
    file.flush();
    back = 0;
    return back;
}

/**
* @brief
* @param
* @Author	ROC
* @date	2019.12.4
*/
qint32 BitPm_Interface::loadPresState()
{
    qint32 back = -1;
    _PM_CONFIG_PRESET_ presParam;
    memset(&presParam,0,sizeof(presParam));
    QFile file(PM_PRE_STATE_FILE);
    if(!file.open(QIODevice::ReadOnly))
    {
        return back;
    }
    else
    {
        file.read((char *)&presParam, sizeof(presParam));
    }
    file.close();
    back = 1;
    //    //m_pPmComm->setStartedFlag(PM_START_FLAG);
    globalUserVariable->gfileType =  presParam.nStartFileType;
    if(presParam.nStartMode != PM_MODULE)
    {
    }
    return back;
}

/**
* @brief
* @param
* @Author	ROC
* @date	2019.12.4
*/
void BitPm_Interface::initFileType(qint32 fileType)
{
    switch (fileType) {
    case PM_FILE_STATE:
        mFileType = (qulonglong)PM_FILEHEADER_STATE;
        initStateParam(globalUserVariable->m_nPowerSensorFlg);
        break;
    default:
        break;
    }
    return;
}

/**
* @brief
* @param
* @Author	ROC
* @date	2019.12.4
*/
void BitPm_Interface::parseFile(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        return ;
    }
    else
    {
        file.read((char *)&mFileType, sizeof(mFileType));
    }
    file.close();
    //    mFileType = PM_FILEHEADER_STATE_DATA;
    switch (mFileType) {
    case PM_FILEHEADER_STATE:
        loadState(fileName);
        break;
    default:
        break;
    }
    return;
}

/**
* @brief select current bieview
* @note
* @author Roc
* @since  2019.11.6
*/
void BitPm_Interface::setcurrentview(quint32 index)
{
    emit ParentFocus();
    if(globalUserVariable->gLocal == PM_REMOTE)
    {
        return;
    }
    if((quint32)nCurWindowIndex == index || wintotalnum < 1)
        return;


    emit BitViewChanged(nCurWindowIndex);
    emit RedrawInfoShow(PM_LABEL_AVERAGE);
    return;
}

/**
* @brief
* @param
* @author Roc
* @since  2019.11.6

*/
void BitPm_Interface::changeBitViewSize(bool isDoubleClicked)
{
    qint32 bitViewIndex = nCurWindowIndex;
    mIsCurBitViewSizeChange = isDoubleClicked;
    if(mIsCurBitViewSizeChange)
    {
    }
    else
    {
        //        setBitViewParam(globalUserVariable->gMeterParam.gConfig_Display.nDisplayMode);
        setcurrentview(bitViewIndex);
    }
    if(mIsZoomIn)
    {
        setZoomIn();
    }
    else
    {
        setZoomOut();
    }
    return;
}

void BitPm_Interface::StopSendPower()
{
    qDebug()<<"Stop Power Send" <<endl;
    cmd_StopSensorContinousP();
    m_pPmComm->m_serialportPm->clearSerialPort();
    m_pPmComm->m_serialportPm->connectPort();
}

/**
* @brief	解析获取探头协议指令，如果是开机自动连接时，停止计时并自动显示
* @note
* @Author	ROC
* @date     2020.3.4
*/
void BitPm_Interface::anaSystemInfo(QByteArray arrayData)
{
    if(POWER_SENSOR_V90 ==globalUserVariable->m_nPowerSensorFlg)
    {
        globalUserVariable->m_strPowerSensorModle =  QByteArrayToqQString(arrayData,0,16);
        globalUserVariable->m_strPowerSensorSN =  QByteArrayToqQString(arrayData,16,16);

        globalUserVariable->m_strPowerSensorFW= QString::number(arrayData[32]) +"." + QString::number(arrayData[33]) + "." + QString::number(arrayData[34]);
        //        "H/WVer "  +  QString::number(arrayData[32])
        //        +"S/WMajor " + QString::number(arrayData[33])
        //        + "S/WPatch " + QString::number(arrayData[34]);
        if('\x00' == arrayData[35])
            globalUserVariable->m_strPowerSensorType = "Terminating";
        else if('\x01' == arrayData[35])
            globalUserVariable->m_strPowerSensorType = "Directional";

    }
    else if(POWER_SENSOR_V91 ==globalUserVariable->m_nPowerSensorFlg)
    {
        globalUserVariable->m_strPowerSensorModle =  QByteArrayToqQString(arrayData,0,16);
        globalUserVariable->m_strPowerSensorType=  QByteArrayToqQString(arrayData,16,16);
        globalUserVariable->m_strPowerSensorSN =  QByteArrayToqQString(arrayData,32,16);

    }

    emit finishCmd();

    m_curSensorData.nPointNo=0;
    setSweepContinous(IsSweepContinous());
    return;
}
/**
* @brief    解析校准数据
* @note
* @Author	ROC
* @date     2020.1.3
*/
void BitPm_Interface::anaAmptCal(QByteArray arrayData)
{
    int nSize = arrayData.size()/2;
    if(POWER_SENSOR_V90 ==globalUserVariable->m_nPowerSensorFlg)
    {
        setCalArray(QByteArrayByHightLToqint16(arrayData,0));
        globalUserVariable->gMeterParam.gConfig_Zero.nFreq = QByteArrayByLowHToqint16(arrayData,2);
        for(int i = 0;i<nSize-1;i++)
           m_fV90AmptCalData[i] =  QByteArrayByLowHToqint16(arrayData,i*2+4)/PM_CAL_MULTIPLE;

    }
    else if(POWER_SENSOR_V91 ==globalUserVariable->m_nPowerSensorFlg)
    {

    }
    emit finishCal();
    return;
}
 qreal* BitPm_Interface::getCalAmptArrayData()
 {
     return m_fV90AmptCalData;
 }

 void BitPm_Interface::setCalAmptData(qint32 nIndex,qreal fData)
 {
     if(PM_V90_CAL_AMPT > nIndex)
         m_fV90AmptCalData[nIndex] = fData;
 }


 qreal BitPm_Interface::getCalAmptData(qint32 nIndex)
 {
     if(PM_V90_CAL_AMPT > nIndex)
         return m_fV90AmptCalData[nIndex];
     else
         return m_fV90AmptCalData[0];
 }
 void BitPm_Interface::setCalCmdData(qint32 nIndex,qreal fData)
 {
     if(PM_V90_CAL_AMPT > nIndex)
         m_fV90WriteCalData[nIndex] = fData;
 }

 void BitPm_Interface::setCalAmptNo(qint32 nRow)
 {
     m_nCalAmptRow = nRow;
 }

 qint32 BitPm_Interface::getCalAmptNo()
 {
     return m_nCalAmptRow;
 }
