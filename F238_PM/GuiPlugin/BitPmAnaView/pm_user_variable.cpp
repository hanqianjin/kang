#include "pm_user_variable.h"
#include "pm_define.h"
#include <QDebug>
#include <QPixmap>
#include <QDir>
#include <QApplication>
#include <QDesktopWidget>
#include "pm_extern.h"
#include <qmath.h>

qint32 RbwVbwCompare(const void *a, const void *b)
{
    if (*(quint32 *)a > *(quint32 *)b)
        return 1;
    else if (*(quint32 *)a == *(quint32 *)b)
        return 0;
    else // if (*(quint32 *)a < *(quint32 *)b)
        return -1;
}

Pm_User_Variable::Pm_User_Variable(QObject *parent)
    : QObject(parent)
{
   m_nPowerSensorFlg = POWER_SENSOR_V90;
    //  m_nPowerSensorFlg = POWER_SENSOR_V91;
    InitVariableDefaultVal();
}
Pm_User_Variable::~Pm_User_Variable()
{
}
void Pm_User_Variable::InitVariableDefaultVal()
{

    gReadMeterDataSleepTime = PM_REFRESH_DEFAULT_TIME;

    m_specFreqMin[POWER_SENSOR_V90] = PM_V90_FREQ_MIN;
    m_specFreqMax[POWER_SENSOR_V90] = PM_V90_FREQ_MAX;

    m_specFreqMin[POWER_SENSOR_V91] = PM_V91_FREQ_MIN;
    m_specFreqMax[POWER_SENSOR_V91] = PM_V91_FREQ_MAX;
    //Freq
    gMeterParam.gConfig_Freq.nlCenterFreq = (m_specFreqMax[m_nPowerSensorFlg] + m_specFreqMin[m_nPowerSensorFlg]) / 2;
    gMeterParam.gConfig_Freq.nlStartFreq =   m_specFreqMin[m_nPowerSensorFlg];
    gMeterParam.gConfig_Freq.nlStopFreq =   m_specFreqMax[m_nPowerSensorFlg];
    if(POWER_SENSOR_V90 == m_nPowerSensorFlg)
    {
        //Freq
        gMeterParam.gConfig_Freq.nlStepFreq = 1000000LL;
        gMeterParam.gConfig_Freq.nlSpan = 2000000LL;
//        gMeterParam.gConfig_Freq.nlSpanUp = 1;
//        gMeterParam.gConfig_Freq.nlSpanDown = 1;
        gMeterParam.gConfig_Freq.nlLastSpan = 1;
        gMeterParam.gConfig_Freq.nSpanType = PM_NORMAL_SPAN;

        gMeterParam.gConfig_Freq.nChannelStd = PM_CDMA - 1;
        gMeterParam.gConfig_Freq.nChannelSelID = 0;
        gMeterParam.gConfig_Freq.nChannelNumber = 0;
        gMeterParam.gConfig_Freq.nChannelStep = mPM_ChStand[PM_CDMA].ChStep;
        gMeterParam.gConfig_Freq.nOffsetFreqOn = PM_BUTTON_OFF;
        gMeterParam.gConfig_Freq.nlOffsetFreq = 0;
//        gMeterParam.gConfig_Freq.nlOffsetFreqSize = gMeterParam.gConfig_Freq.nlStepFreq;

        //amplitude
        gMeterParam.gConfig_Ampt.fMax = PM_V90_POWER_MAX;
        gMeterParam.gConfig_Ampt.fMin = PM_V90_POWER_MIN;
        gMeterParam.gConfig_Ampt.fOffset = 0;

        gMeterParam.gConfig_Ampt.nForwardRelative = PM_BUTTON_OFF;
        gMeterParam.gConfig_Ampt.nReverseRelative = PM_BUTTON_OFF;
        gMeterParam.gConfig_Ampt.fForwardRelativeData = 0;
        gMeterParam.gConfig_Ampt.fReverseRelativeData= 0;
        gMeterParam.gConfig_Ampt.nUnits = 0;

        //sweep
        gMeterParam.gConfig_Sweep.nSweepType = PM_CONT;
        gMeterParam.gConfig_Sweep.nTimeInterval = 1;
        gMeterParam.gConfig_Sweep.fDutyCycle = 100.0;
        //ave
        gMeterParam.gConfig_Ave.nAcquisition = PM_AVERAGE_FAST;
        gMeterParam.gConfig_Ave.bIsAverageFlg = false;
        gMeterParam.gConfig_Ave.nRunningAverage = PM_RUNNING_AVERAGE_MIN;
        gMeterParam.gConfig_Ave.nMaxHold = PM_BUTTON_OFF;


        //Zero
        gMeterParam.gConfig_Zero.nZero = PM_BUTTON_OFF;
        gMeterParam.gConfig_Zero.m_fZeroBaseForward = 0;
        gMeterParam.gConfig_Zero.m_fZeroBaseReverse = 0;
        gMeterParam.gConfig_Zero.nSelectCalType = PM_CALIBRATION_ARRAY;
        gMeterParam.gConfig_Zero.nArray = 0;
        gMeterParam.gConfig_Zero.nFreq = 10;

        //Measure
        gMeterParam.gConfig_Measure.nModle = PM_MEASUER_AVG;
        gMeterParam.gConfig_Measure.fOffset = 0;

        //Limit
        gMeterParam.gConfig_Limit.nLimitFlg = PM_BUTTON_OFF;
        gMeterParam.gConfig_Limit.fForwardUp = 1.0;
        gMeterParam.gConfig_Limit.fForwardLow = 1.0;
        gMeterParam.gConfig_Limit.fReverseUp = 1.0;
        gMeterParam.gConfig_Limit.fReverseLow = 1.0;
        gMeterParam.gConfig_Limit.nVideoBw = PM_BUTTON_OFF;
        gMeterParam.gConfig_Limit.fCCDF = PM_BUTTON_OFF;
    }

    else if(POWER_SENSOR_V91 == m_nPowerSensorFlg)
    {
        gMeterParam.gConfig_Freq.nlStepFreq = 1000000LL;
        gMeterParam.gConfig_Freq.nlSpan = 2000000LL;
//        gMeterParam.gConfig_Freq.nlSpanUp = 1;
//        gMeterParam.gConfig_Freq.nlSpanDown = 1;
        gMeterParam.gConfig_Freq.nSpanType = PM_NORMAL_SPAN;

        gMeterParam.gConfig_Freq.nChannelStd = PM_CDMA - 1;
        gMeterParam.gConfig_Freq.nChannelSelID = 0;
        gMeterParam.gConfig_Freq.nChannelNumber = 0;
        gMeterParam.gConfig_Freq.nChannelStep = mPM_ChStand[PM_CDMA].ChStep;
        gMeterParam.gConfig_Freq.nOffsetFreqOn = PM_BUTTON_OFF;
        gMeterParam.gConfig_Freq.nlOffsetFreq = 0;
//        gMeterParam.gConfig_Freq.nlOffsetFreqSize =  gMeterParam.gConfig_Freq.nlStepFreq;

        //amplitude
        gMeterParam.gConfig_Ampt.fMax = PM_V91_AVER_MAX;
        gMeterParam.gConfig_Ampt.fMin = PM_V91_AVER_MIN;
        gMeterParam.gConfig_Sweep.fDutyCycle = 100.0;
        gMeterParam.gConfig_Ampt.fOffset = 0;

        gMeterParam.gConfig_Ampt.nForwardRelative = PM_BUTTON_OFF;
        gMeterParam.gConfig_Ampt.nReverseRelative = PM_BUTTON_OFF;
        gMeterParam.gConfig_Ampt.fForwardRelativeData = 0;
        gMeterParam.gConfig_Ampt.fReverseRelativeData = 0;
        gMeterParam.gConfig_Ampt.nUnits = 0;

        //sweep
        gMeterParam.gConfig_Sweep.nSweepType = PM_CONT;
        gMeterParam.gConfig_Sweep.nTimeInterval = 1;

        //ave
        gMeterParam.gConfig_Ave.nAcquisition = PM_AVERAGE_FAST;
        gMeterParam.gConfig_Ave.nRunningAverage = PM_RUNNING_AVERAGE_MIN;
        gMeterParam.gConfig_Ave.nMaxHold = PM_BUTTON_OFF;

        //Zero
        gMeterParam.gConfig_Zero.nZero = PM_BUTTON_OFF;
        gMeterParam.gConfig_Zero.m_fZeroBaseForward = 0;
        gMeterParam.gConfig_Zero.m_fZeroBaseReverse = 0;
        gMeterParam.gConfig_Zero.nSelectCalType = PM_CALIBRATION_ARRAY;
        gMeterParam.gConfig_Zero.nArray = 0;
        gMeterParam.gConfig_Zero.nFreq = 10;

        //Measure
        gMeterParam.gConfig_Measure.nModle = PM_MEASUER_AVG;
        gMeterParam.gConfig_Measure.fOffset = 0;

        //Limit
        gMeterParam.gConfig_Limit.nLimitFlg = PM_BUTTON_OFF;
        gMeterParam.gConfig_Limit.fForwardUp = 1.0;
        gMeterParam.gConfig_Limit.fForwardLow = 1.0;
        gMeterParam.gConfig_Limit.fReverseUp = 1.0;
        gMeterParam.gConfig_Limit.fReverseLow = 1.0;
        gMeterParam.gConfig_Limit.nVideoBw = PM_BUTTON_OFF;
        gMeterParam.gConfig_Limit.fCCDF = PM_BUTTON_OFF;

    }

    gMeterParam.gConfig_Display.nShowDisplayModle = PM_DISPLAY_FORWARD_AVERAGE;
    gMeterParam.gConfig_Display.nFordardMode = 0;
    gMeterParam.gConfig_Display.nReverseMode = 0;
    gMeterParam.gConfig_Display.nSysDisplay = PM_BIT_DEFAULTMODE;

    gMenu = PM_MENU_POWER_SENSOR;
    entryInputMode = PM_NOT_USE;

    m_nMinSpan = PM_SPAN_MIN;
    m_nHalfMinSpan = m_nMinSpan / 2;

    KeyNumber        = -1;
    gCHName = new QVector <QString>;
    gCHStandard = new QVector <__PM_Standard__>;
    gFreqStandard = new QVector <__PM_Standard__>;
    getBandInfo(gMeterParam.gConfig_Freq.nChannelStd);
    adjustCHStandarByCerFreq(gMeterParam.gConfig_Freq.nlCenterFreq);
    gLocal = PM_LOCAL;

    startMode = -1;
    gfileType = -1;

    linkMode = -1;
    gLinkfileType = -1;
    gRefreshAllParam = false;
    gSuspendDrawFlag = false;

}

qint32 Pm_User_Variable::notZeroPositionFindFunc(QString strGab)
{
    qint32 strLen = 0;
    qint32 pos = 30;
    char str1[21] = {'\0',};
    qint32 i = 0;

    strLen = strGab.length();
    qsnprintf(str1, sizeof(str1), "%s", strGab.toUtf8().constData());

    for (i = (strLen - 1); i >= 0; i--)
    {
        //       qDebug() << "-------- i = " << i << "--"  << str1[i];
        if (str1[i] != '0') {
            pos = i;
            break;
        }
    }

    return pos;
}

#if 0
qint32 Pm_User_Variable::timeUnitFindProc(double _time)
{
    if (_time >= KS)
        return UNIT_KS;
    else if (_time >= S)
        return UNIT_S;
    else if (_time >= MS)
        return UNIT_MS;
    else if (_time >= US)
        return UNIT_US;
    else
        return UNIT_NS;
}
#endif

qint32 Pm_User_Variable::freqUnitFindProc(qreal _freq)
{
    if (_freq >= PM_GHZ)
        return UNIT_GHZ;
    else if (_freq >= PM_MHZ)
        return UNIT_MHZ;
    else if (_freq >= PM_KHZ)
        return UNIT_KHZ;
    else
        return UNIT_HZ;
}


qreal Pm_User_Variable::adjustSpanBySpan(qreal freq)
{
    if(POWER_SENSOR_V90 == m_nPowerSensorFlg)
    {
//        for(qint32 index = 0;index<PM_V90_SPAN_INTERVAL_NUMBER;index++)
//        {
//            if(index == 0)
//            {
//                if(freq >= 0 && freq<=PM_V90_SPAN_STEP_VALUE[index])
//                {
//                    freq = PM_V90_SPAN_STEP_VALUE[index];
//                    return freq;
//                }
//            }else
//            {
//                if(freq>PM_V90_SPAN_STEP_VALUE[index-1] && freq<=PM_V90_SPAN_STEP_VALUE[index])
//                {
//                    freq = PM_V90_SPAN_STEP_VALUE[index];
//                    return freq;
//                }
//            }
//        }

//        if(freq >= PM_V90_SPAN_STEP_VALUE[PM_V90_SPAN_INTERVAL_NUMBER-1])
//        {
//            freq = PM_V90_SPAN_STEP_VALUE[PM_V90_SPAN_INTERVAL_NUMBER-1];
//            return freq;
//        }
        if(freq < PM_V90_MIN_SPAN)
            freq = PM_V90_MIN_SPAN;
        else if(freq >= PM_V90_MAX_SPAN)

            freq = PM_V90_MAX_SPAN;
        return freq;

    }
    else if (POWER_SENSOR_V91 == m_nPowerSensorFlg)
    {
//        for(qint32 index = 0;index<PM_V91_SPAN_INTERVAL_NUMBER;index++)
//        {
//            if(index == 0)
//            {
//                if(freq >= 0 && freq<=PM_V91_SPAN_STEP_VALUE[index])
//                {
//                    freq = PM_V91_SPAN_STEP_VALUE[index];
//                    return freq;
//                }
//            }else
//            {
//                if(freq>PM_V91_SPAN_STEP_VALUE[index-1] && freq<=PM_V91_SPAN_STEP_VALUE[index])
//                {
//                    freq = PM_V91_SPAN_STEP_VALUE[index];
//                    return freq;
//                }
//            }
//        }

//        if(freq >= PM_V91_SPAN_STEP_VALUE[PM_V91_SPAN_INTERVAL_NUMBER-1])
//        {
//            freq = PM_V91_SPAN_STEP_VALUE[PM_V91_SPAN_INTERVAL_NUMBER-1];
//            return freq;
//        }
        if(freq < PM_V91_MIN_SPAN)
            freq = PM_V91_MIN_SPAN;
        else if(freq >= PM_V91_MAX_SPAN)

            freq = PM_V91_MAX_SPAN;
        return freq;

    }

    return 0;
}

///**
//* @brief	调整扫宽为最小扫宽
//* @note
//* @Author	ROC
//* @date	2019.11.20
//*/
//qreal Pm_User_Variable::adjustSpanToSmall(qreal freq)
//{
//    if(POWER_SENSOR_V90 == m_nPowerSensorFlg)
//    {
//        for(qint32 index = 1;index<PM_V90_SPAN_INTERVAL_NUMBER;index++)
//        {
//            if(index == 1)
//            {
//                if(freq>=0 && freq<=PM_V90_SPAN_STEP_VALUE[index])
//                {
//                    freq = PM_V90_SPAN_STEP_VALUE[index];
//                    return freq;
//                }
//            }else
//            {
//                if(freq>=PM_V90_SPAN_STEP_VALUE[index-1] && freq<PM_V90_SPAN_STEP_VALUE[index])
//                {
//                    freq = PM_V90_SPAN_STEP_VALUE[index-1];
//                    return freq;
//                }
//            }

//        }
//        if(freq >= PM_V90_SPAN_STEP_VALUE[PM_V90_SPAN_INTERVAL_NUMBER-1])
//        {
//            freq = PM_V90_SPAN_STEP_VALUE[PM_V90_SPAN_INTERVAL_NUMBER-1];
//            return freq;
//        }
//    }
//   else if(POWER_SENSOR_V91 == m_nPowerSensorFlg)
//    {
//        for(qint32 index = 1;index<PM_V91_SPAN_INTERVAL_NUMBER;index++)
//        {
//            if(index == 1)
//            {
//                if(freq>=0 && freq<=PM_V91_SPAN_STEP_VALUE[index])
//                {
//                    freq = PM_V91_SPAN_STEP_VALUE[index];
//                    return freq;
//                }
//            }else
//            {
//                if(freq>=PM_V91_SPAN_STEP_VALUE[index-1] && freq<PM_V91_SPAN_STEP_VALUE[index])
//                {
//                    freq = PM_V91_SPAN_STEP_VALUE[index-1];
//                    return freq;
//                }
//            }
//        }
//        if(freq >= PM_V91_SPAN_STEP_VALUE[PM_V91_SPAN_INTERVAL_NUMBER-1])
//        {
//            freq = PM_V91_SPAN_STEP_VALUE[PM_V91_SPAN_INTERVAL_NUMBER-1];
//            return freq;
//        }
//    }
//    return 0;
//}

/**
* @brief	按照扫宽调整频率
* @note
* @Author	ROC
* @date	2019.11.20
*/
qint32 Pm_User_Variable::adjustFreqBySpan(qreal freq)
{
    gMeterParam.gConfig_Freq.nlSpan = freq;

    if(gMeterParam.gConfig_Freq.nlCenterFreq - 0.5 * gMeterParam.gConfig_Freq.nlSpan < m_specFreqMin[m_nPowerSensorFlg])
    {
        gMeterParam.gConfig_Freq.nlStartFreq = m_specFreqMin[m_nPowerSensorFlg];

        gMeterParam.gConfig_Freq.nlCenterFreq = gMeterParam.gConfig_Freq.nlStartFreq + 0.5*gMeterParam.gConfig_Freq.nlSpan;
        gMeterParam.gConfig_Freq.nlStopFreq = gMeterParam.gConfig_Freq.nlStartFreq + gMeterParam.gConfig_Freq.nlSpan;
    }
    else if(gMeterParam.gConfig_Freq.nlCenterFreq + 0.5 * gMeterParam.gConfig_Freq.nlSpan > m_specFreqMax[m_nPowerSensorFlg])
    {
        gMeterParam.gConfig_Freq.nlStopFreq = m_specFreqMax[m_nPowerSensorFlg];
        gMeterParam.gConfig_Freq.nlCenterFreq = gMeterParam.gConfig_Freq.nlStopFreq - 0.5*gMeterParam.gConfig_Freq.nlSpan;
        gMeterParam.gConfig_Freq.nlStartFreq =  gMeterParam.gConfig_Freq.nlStopFreq - gMeterParam.gConfig_Freq.nlSpan;
    }
    else
    {
        gMeterParam.gConfig_Freq.nlStartFreq = gMeterParam.gConfig_Freq.nlCenterFreq - 0.5 * gMeterParam.gConfig_Freq.nlSpan;
        gMeterParam.gConfig_Freq.nlStopFreq = gMeterParam.gConfig_Freq.nlCenterFreq + 0.5 * gMeterParam.gConfig_Freq.nlSpan;
    }
    return 1;
}

/**
* @brief   按照中心频率调整频率起止
* @note
* @author  Roc
* @since   2019.11.10
*/
qint32 Pm_User_Variable::adjustFreqByCer()
{
    if(gMeterParam.gConfig_Freq.nlCenterFreq < m_specFreqMin[m_nPowerSensorFlg])
    {
        gMeterParam.gConfig_Freq.nlLastSpan  =  gMeterParam.gConfig_Freq.nlSpan;
        gMeterParam.gConfig_Freq.nlCenterFreq = m_specFreqMin[m_nPowerSensorFlg];
        gMeterParam.gConfig_Freq.nlStartFreq  = 0;
        gMeterParam.gConfig_Freq.nlStopFreq   = 0;
    }
    else if(gMeterParam.gConfig_Freq.nlCenterFreq > m_specFreqMax[m_nPowerSensorFlg])
    {
        gMeterParam.gConfig_Freq.nlLastSpan  =  gMeterParam.gConfig_Freq.nlSpan;
        gMeterParam.gConfig_Freq.nlCenterFreq = m_specFreqMax[m_nPowerSensorFlg];
        gMeterParam.gConfig_Freq.nlStartFreq  = 0;
        gMeterParam.gConfig_Freq.nlStopFreq   = 0;
    }
    else
    {
        if(gMeterParam.gConfig_Freq.nlCenterFreq - 0.5 * gMeterParam.gConfig_Freq.nlSpan < m_specFreqMin[m_nPowerSensorFlg])
        {
            gMeterParam.gConfig_Freq.nlLastSpan  =  gMeterParam.gConfig_Freq.nlSpan;
            gMeterParam.gConfig_Freq.nlStartFreq  = 0;
            gMeterParam.gConfig_Freq.nlStopFreq   = 0;
        }
        else if(gMeterParam.gConfig_Freq.nlCenterFreq + 0.5 * gMeterParam.gConfig_Freq.nlSpan > m_specFreqMax[m_nPowerSensorFlg])
        {
            gMeterParam.gConfig_Freq.nlLastSpan  =  gMeterParam.gConfig_Freq.nlSpan;
            gMeterParam.gConfig_Freq.nlStartFreq  = 0;
            gMeterParam.gConfig_Freq.nlStopFreq   = 0;
        }
        else
        {
            //change start and stop freq
            gMeterParam.gConfig_Freq.nlStartFreq = gMeterParam.gConfig_Freq.nlCenterFreq - 0.5 * gMeterParam.gConfig_Freq.nlSpan;
            gMeterParam.gConfig_Freq.nlStopFreq = gMeterParam.gConfig_Freq.nlCenterFreq + 0.5 * gMeterParam.gConfig_Freq.nlSpan;
        }

    }
    return 1;
}

/**
* @brief	按照开始频率调整中心频率
* @note
* @Author	ROC
* @date     2019.12.20
*/
qint32 Pm_User_Variable::adjustFreqByStart(void)
{
    //save last span
    gMeterParam.gConfig_Freq.nlLastSpan  =  gMeterParam.gConfig_Freq.nlSpan;

    if(gMeterParam.gConfig_Freq.nlStartFreq < m_specFreqMin[m_nPowerSensorFlg])
        gMeterParam.gConfig_Freq.nlStartFreq =  m_specFreqMin[m_nPowerSensorFlg];

    if(gMeterParam.gConfig_Freq.nlStartFreq >= gMeterParam.gConfig_Freq.nlStopFreq)
    {
        gMeterParam.gConfig_Freq.nlSpan = m_nMinSpan;
        gMeterParam.gConfig_Freq.nlStopFreq = gMeterParam.gConfig_Freq.nlStartFreq + m_nMinSpan;
        if( gMeterParam.gConfig_Freq.nlStopFreq > m_specFreqMax[m_nPowerSensorFlg])
        {
            gMeterParam.gConfig_Freq.nlStopFreq = m_specFreqMax[m_nPowerSensorFlg];
            gMeterParam.gConfig_Freq.nlStartFreq = gMeterParam.gConfig_Freq.nlStopFreq - m_nMinSpan;
        }
        gMeterParam.gConfig_Freq.nlCenterFreq = gMeterParam.gConfig_Freq.nlStartFreq + m_nHalfMinSpan;
    }
    else
    {
        if(gMeterParam.gConfig_Freq.nlStartFreq + gMeterParam.gConfig_Freq.nlSpan > m_specFreqMax[m_nPowerSensorFlg])
        {
            if(gMeterParam.gConfig_Freq.nlStartFreq + m_nMinSpan > m_specFreqMax[m_nPowerSensorFlg])
            {
                gMeterParam.gConfig_Freq.nlStopFreq  =  m_specFreqMax[m_nPowerSensorFlg];
                gMeterParam.gConfig_Freq.nlSpan  =  m_nMinSpan;
                gMeterParam.gConfig_Freq.nlCenterFreq = gMeterParam.gConfig_Freq.nlStopFreq - m_nHalfMinSpan;
                gMeterParam.gConfig_Freq.nlStartFreq  = gMeterParam.gConfig_Freq.nlStopFreq - m_nMinSpan;
            }else
            {
                gMeterParam.gConfig_Freq.nlStopFreq  =  m_specFreqMax[m_nPowerSensorFlg];
                gMeterParam.gConfig_Freq.nlSpan  =  gMeterParam.gConfig_Freq.nlStopFreq - gMeterParam.gConfig_Freq.nlStartFreq;              
                gMeterParam.gConfig_Freq.nlCenterFreq = gMeterParam.gConfig_Freq.nlStopFreq - 0.5 * gMeterParam.gConfig_Freq.nlSpan;
                gMeterParam.gConfig_Freq.nlStartFreq  = gMeterParam.gConfig_Freq.nlStopFreq - gMeterParam.gConfig_Freq.nlSpan;

            }
        }
        else
        {
            gMeterParam.gConfig_Freq.nlSpan  =  gMeterParam.gConfig_Freq.nlStopFreq - gMeterParam.gConfig_Freq.nlStartFreq;
            gMeterParam.gConfig_Freq.nlCenterFreq = gMeterParam.gConfig_Freq.nlStartFreq + 0.5 * gMeterParam.gConfig_Freq.nlSpan;
            gMeterParam.gConfig_Freq.nlStopFreq  = gMeterParam.gConfig_Freq.nlStartFreq + gMeterParam.gConfig_Freq.nlSpan;
        }
    }
    return 1;
}
/**
* @brief	按照停止频率调整中心频率
* @note
* @Author	ROC
* @date     2019.12.20
*/
qint32 Pm_User_Variable::adjustFreqByStop(void)
{
    gMeterParam.gConfig_Freq.nlLastSpan  =  gMeterParam.gConfig_Freq.nlSpan;
    if(gMeterParam.gConfig_Freq.nlStopFreq > m_specFreqMax[m_nPowerSensorFlg])
        gMeterParam.gConfig_Freq.nlStopFreq =  m_specFreqMax[m_nPowerSensorFlg];
    //change < to <=
    if(gMeterParam.gConfig_Freq.nlStopFreq <= gMeterParam.gConfig_Freq.nlStartFreq)
    {
        gMeterParam.gConfig_Freq.nlSpan = m_nMinSpan;
        gMeterParam.gConfig_Freq.nlStartFreq = gMeterParam.gConfig_Freq.nlStopFreq - m_nMinSpan;
        if( gMeterParam.gConfig_Freq.nlStartFreq < m_specFreqMin[m_nPowerSensorFlg])
        {
            gMeterParam.gConfig_Freq.nlStartFreq = m_specFreqMin[m_nPowerSensorFlg];
            gMeterParam.gConfig_Freq.nlStopFreq = gMeterParam.gConfig_Freq.nlStartFreq + m_nMinSpan;
        }
        gMeterParam.gConfig_Freq.nlCenterFreq = gMeterParam.gConfig_Freq.nlStartFreq + m_nHalfMinSpan;
    }
    else
    {
        if(gMeterParam.gConfig_Freq.nlStopFreq - gMeterParam.gConfig_Freq.nlSpan < m_specFreqMin[m_nPowerSensorFlg])
        {
            if(gMeterParam.gConfig_Freq.nlStopFreq - m_nMinSpan <= m_specFreqMin[m_nPowerSensorFlg])
            {
                gMeterParam.gConfig_Freq.nlStartFreq  =  m_specFreqMin[m_nPowerSensorFlg];
                gMeterParam.gConfig_Freq.nlSpan  =  m_nMinSpan;
                gMeterParam.gConfig_Freq.nlCenterFreq = gMeterParam.gConfig_Freq.nlStartFreq + m_nHalfMinSpan;
                gMeterParam.gConfig_Freq.nlStopFreq  = gMeterParam.gConfig_Freq.nlStartFreq + m_nMinSpan;
            }else
            {
                gMeterParam.gConfig_Freq.nlStartFreq  =  m_specFreqMin[m_nPowerSensorFlg];
                gMeterParam.gConfig_Freq.nlSpan  =  gMeterParam.gConfig_Freq.nlStopFreq - gMeterParam.gConfig_Freq.nlStartFreq;
                gMeterParam.gConfig_Freq.nlCenterFreq = gMeterParam.gConfig_Freq.nlStartFreq + 0.5 * gMeterParam.gConfig_Freq.nlSpan;
                gMeterParam.gConfig_Freq.nlStopFreq  = gMeterParam.gConfig_Freq.nlStartFreq + gMeterParam.gConfig_Freq.nlSpan;
            }
        }else
        {
            gMeterParam.gConfig_Freq.nlSpan  =  gMeterParam.gConfig_Freq.nlStopFreq-gMeterParam.gConfig_Freq.nlStartFreq;
            gMeterParam.gConfig_Freq.nlCenterFreq = gMeterParam.gConfig_Freq.nlStopFreq - 0.5 * gMeterParam.gConfig_Freq.nlSpan;
            gMeterParam.gConfig_Freq.nlStartFreq  = gMeterParam.gConfig_Freq.nlStopFreq - gMeterParam.gConfig_Freq.nlSpan;
        }

    }
    return 1;
}

qreal Pm_User_Variable::dbmToVoltCalculatorAndDisplayFunc(char *label, qreal _level,bool bDataByUnitIndex)
{
    qreal voltGab = 0.;
    qreal calculator = 0.;

    calculator = pow(10, _level / 10.);
    voltGab = 1000000. * pow(50 * calculator * 0.001, 0.5);//uv

    if(bDataByUnitIndex)
    {
        if(UNIT_kV == m_nUnitIndex){
            voltGab = (qreal) voltGab / 1000000000.;
            sprintf(label, "%.2f kV", voltGab);
        }
        else if (UNIT_V == m_nUnitIndex) {
            voltGab =  (qreal) voltGab / 1000000.;
            sprintf(label, "%.2f V", voltGab);
        } else if (UNIT_mV == m_nUnitIndex) {
            voltGab =  (qreal) voltGab / 1000.;
            sprintf(label, "%.2f mV", voltGab);
        } else if (UNIT_uV == m_nUnitIndex) {
            voltGab =  (qreal) voltGab;
            sprintf(label, "%.2f uV", voltGab);
        } else if (UNIT_nV == m_nUnitIndex) {
            voltGab =  (qreal) voltGab * 1000;
            sprintf(label, "%.2f nV", voltGab);
        } else if (UNIT_pV == m_nUnitIndex) {
            voltGab =  (qreal) voltGab * 1000000.;
            sprintf(label, "%.2f pV", voltGab);
        } else if (UNIT_fV == m_nUnitIndex) {
            voltGab =  (qreal) voltGab * 1000000000.;
            sprintf(label, "%.2f fV", voltGab);
        } else if (UNIT_aV == m_nUnitIndex) {
            voltGab =  (qreal) voltGab * 1000000000000.;
            sprintf(label, "%.2f aV", voltGab);
        } else if (UNIT_zV == m_nUnitIndex) {
            voltGab =  (qreal) voltGab * 1000000000000000.;
            sprintf(label, "%.2f zV", voltGab);
        } else if (UNIT_yV == m_nUnitIndex) {
            voltGab =  (qreal) voltGab * 1000000000000000000.;
            sprintf(label, "%.2f yV", voltGab);
        } else {
            voltGab =  (qreal) voltGab * 1000000000000000000000.;
            sprintf(label, "%.2f ", voltGab);
        }
    }
    else
    {
        if(voltGab >= 1000000000.)     {                     //kV
            voltGab = (qreal) voltGab / 1000000000.;
            sprintf(label, "%.2f kV", voltGab);
            m_nUnitIndex = UNIT_kV;
        }
        else if (voltGab >= 1000000.)  {                     //V
            voltGab =  (qreal) voltGab / 1000000.;
            sprintf(label, "%.2f V", voltGab);
            m_nUnitIndex = UNIT_V;
        } else if (voltGab < 1000000.) {                    //mV
            voltGab =  (qreal) voltGab / 1000.;
            sprintf(label, "%.2f mV", voltGab);
            m_nUnitIndex = UNIT_mV;
        } else if (voltGab < 1000.) {                       //uV
            voltGab =  (qreal) voltGab;
            sprintf(label, "%.2f uV", voltGab);
            m_nUnitIndex = UNIT_uV;
        } else if (voltGab < 1.) {                          //nV
            voltGab =  (qreal) voltGab * 1000;
            sprintf(label, "%.2f nV", voltGab);
            m_nUnitIndex = UNIT_nV;
        } else if (voltGab < 0.001 && voltGab >= 0.000001) {//pV
            voltGab =  (qreal) voltGab * 1000000.;
            sprintf(label, "%.2f pV", voltGab);
            m_nUnitIndex = UNIT_pV;
        } else if (voltGab < 0.000001 && voltGab >= 0.000000001) { //fV
            voltGab =  (qreal) voltGab * 1000000000.;
            sprintf(label, "%.2f fV", voltGab);
            m_nUnitIndex = UNIT_fV;
        } else if (voltGab < 0.000000001 && voltGab >= 0.000000000001) {//aV
            voltGab =  (qreal) voltGab * 1000000000000.;
            sprintf(label, "%.2f aV", voltGab);
            m_nUnitIndex = UNIT_aV;
        } else if (voltGab < 0.000000000001 && voltGab >= 0.000000000000001) {//zV
            voltGab =  (qreal) voltGab * 1000000000000000.;
            sprintf(label, "%.2f zV", voltGab);
            m_nUnitIndex = UNIT_zV;
        } else if (voltGab < 0.000000000000001 && voltGab >= 0.000000000000000001) {//yV
            voltGab =  (qreal) voltGab * 1000000000000000000.;
            sprintf(label, "%.2f yV", voltGab);
            m_nUnitIndex = UNIT_yV;
        } else {
            voltGab =  (qreal) voltGab * 1000000000000000000000.;
            sprintf(label, "%.2f ", voltGab);
        }
    }

    /*if (voltGab <= 7071067.9 && voltGab >= 1121000.) {
      sprintf(label, "%.2f V", (qreal) voltGab / 1000000);
    } else if (voltGab <= 998800. && voltGab >= 1121.) {
      sprintf(label, "%.2f mV", (qreal) voltGab / 1000.);
    } else if (voltGab <= 998.8 && voltGab >= 1.121) {
      sprintf(label, "%.2f uV", (qreal) voltGab);
    } else if (voltGab <= 9.988 && voltGab >= 0.221) {
      sprintf(label, "%.2f nV", (qreal) voltGab * 1000);
    } else if (voltGab <= 0.09988 && voltGab >= 0.00221) {
      sprintf(label, "%.2f pV", (qreal) voltGab * 1000000.);
    }*/

    return voltGab;
}

qreal Pm_User_Variable::dbmToWattsCalculatorAndDisplayFunc(char *label, qreal _level, bool bDataByUnitIndex)
{

    qreal wattsGab = 0.;
    wattsGab = pow(10, _level / 10.);

    if(bDataByUnitIndex)
    {
        if (UNIT_W == m_nUnitIndex) {                           // W
            wattsGab = (qreal)wattsGab / 1000.0;
            sprintf(label, "%.2f W", wattsGab);
        }  else if (UNIT_mW == m_nUnitIndex) {                  // mW
            wattsGab = (qreal)wattsGab;
            sprintf(label, "%.2f mW", wattsGab);
        }  else if (UNIT_uW == m_nUnitIndex) {                   // uW
            wattsGab = (qreal)wattsGab * 1000.0;
            sprintf(label, "%.2f uW", wattsGab);
        }  else if (UNIT_nW == m_nUnitIndex) {                   // nW
            wattsGab = (qreal)wattsGab * 1000000.0;
            sprintf(label, "%.2f nW", wattsGab);
        }  else if (UNIT_pW == m_nUnitIndex){                    // pW
            wattsGab = (qreal)wattsGab * 1000000000.0;
            sprintf(label, "%.2f pW", wattsGab);
        }  else if (UNIT_fW == m_nUnitIndex) {                   // fW
            wattsGab = (qreal)wattsGab * 1000000000000.0;
            sprintf(label, "%.2f fW", wattsGab);
        }  else {                                                // aW
            wattsGab = (qreal)wattsGab * 1000000000000000.0;
            sprintf(label, "%.2f aW", wattsGab);
        }
    }
    else
    {
        if (wattsGab >= 1000) {						    // W
            wattsGab = (qreal)wattsGab / 1000.0;
            sprintf(label, "%.2f W", wattsGab);
            m_nUnitIndex = UNIT_W;
        }  else if (wattsGab >= 1) {					// mW
            wattsGab = (qreal)wattsGab;
            sprintf(label, "%.2f mW", wattsGab);
            m_nUnitIndex = UNIT_mW;
        }  else if (wattsGab >= 0.001) {				// uW
            wattsGab = (qreal)wattsGab * 1000.0;
            sprintf(label, "%.2f uW", wattsGab);
            m_nUnitIndex = UNIT_uW;
        }  else if (wattsGab >= 0.000001) {			    // nW
            wattsGab = (qreal)wattsGab * 1000000.0;
            sprintf(label, "%.2f nW", wattsGab);
            m_nUnitIndex = UNIT_nW;
        } else if (wattsGab >= 0.000000001){			// pW
            wattsGab = (qreal)wattsGab * 1000000000.0;
            sprintf(label, "%.2f pW", wattsGab);
            m_nUnitIndex = UNIT_pW;
        } else if (wattsGab >= 0.000000000001) {		// fW
            wattsGab = (qreal)wattsGab * 1000000000000.0;
            sprintf(label, "%.2f fW", wattsGab);
            m_nUnitIndex = UNIT_fW;
        } else {                                        // aW
            wattsGab = (qreal)wattsGab * 1000000000000000.0;
            sprintf(label, "%.2f aW", wattsGab);
            m_nUnitIndex = UNIT_aW;
        }
    }
    return wattsGab;
}

void Pm_User_Variable::Delta_dbmToWattsCalculatorAndDisplayFunc(char *label, qreal _level)
{
    qreal wattsGab = 0.;

    wattsGab = pow(10, _level / 10.);
    sprintf(label, "%.2f W/W", (qreal)wattsGab);
}
void Pm_User_Variable::Delta_dbmToVoltCalculatorAndDisplayFunc(char *label, qreal _level)
{
    qreal voltGab = 0.;
    qreal calculator = 0.;

    calculator = pow(10, _level / 10.);
    voltGab = 1000000. * 0.001 * pow(50 * calculator * 0.001, 0.5);//uv*0.001 =>mv
    sprintf(label, "%.2f V/V", (qreal) voltGab);
}

//void Pm_User_Variable::charEmptySplitWorkerFunc(char *label)
//{
////  char *ptr;
//// qint32 cnt = 0;

////  ptr = strtok(label, " ");   // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
////  cnt = 0;
////  while (ptr != NULL) {   // 자른 문자열이 나오지 않을 때까지 반복
////      if (cnt == 0)
////        sprintf(watts_unit.value, "%s", ptr);
////      else
////        sprintf(watts_unit.unit, "%s", ptr);
////      ptr = strtok(NULL, " ");   // 다음 문자열을 잘라서 포인터를 반환
////      cnt++;
////      //            qDebug() << " while ptr ________________" << ptr;
////    }

//return;

//}

qreal Pm_User_Variable::wattsToDbmCalculatorFunc(qreal _watts)
{
    return   (10 * log10(_watts) + 30);
}

qreal Pm_User_Variable::voltToDbmCalculatorFunc(qreal _volt)
{
    qreal cal1 = 0.;
    qreal cal2 = 0.;
    qreal cal3 = 0.;
    qreal cal4 = 0.;

    cal1 = _volt * qPow(10, -6);
    cal2 = qPow(cal1 , 2) / 50.;
    cal3 = 10 * log10(cal2);
    cal4 = cal3 + 30.;

    return cal4;

}

void Pm_User_Variable::getBandInfo(qint32 STDIndex)
{
    QString name = QString(mPM_ChStand[STDIndex].name);
    QString filename = QString(":/pm/standard/%1").arg(name);
    QString str;
    QByteArray line;
    gCHName->clear();
    gCHStandard->clear();
    gFreqStandard->clear();
    QFile mFile(filename);
    if(mFile.open(QFile::ReadOnly))
    {
        while (!mFile.atEnd())
        {
            line = mFile.readLine();
            str = QString(line);
            analysisData(str);
        }
        mFile.close();
    }
    mFile.close();
    return;
}
void Pm_User_Variable::analysisData(QString str)
{
    __PM_Standard__ mtmp;
    QStringList list = str.split(",");
    if(list.size() == 5)
    {
        gCHName->append(list[0]);
        mtmp.Up.Min = QString(list[1]).toDouble();
        mtmp.Up.Max = QString(list[2]).toDouble();
        mtmp.Down.Min = QString(list[1]).toDouble();
        mtmp.Down.Max = QString(list[2]).toDouble();
        gCHStandard->append(mtmp);

        mtmp.Up.Min = QString(list[3]).toDouble();
        mtmp.Up.Max = QString(list[4]).toDouble();
        mtmp.Down.Min = QString(list[3]).toDouble();
        mtmp.Down.Max = QString(list[4]).toDouble();
        gFreqStandard->append(mtmp);
    }else if(list.size() == 9)
    {
        gCHName->append(list[0]);
        mtmp.Up.Min = QString(list[1]).toDouble();
        mtmp.Up.Max = QString(list[2]).toDouble();
        mtmp.Down.Min = QString(list[3]).toDouble();
        mtmp.Down.Max = QString(list[4]).toDouble();
        gCHStandard->append(mtmp);

        mtmp.Up.Min = QString(list[5]).toDouble();
        mtmp.Up.Max = QString(list[6]).toDouble();
        mtmp.Down.Min = QString(list[7]).toDouble();
        mtmp.Down.Max = QString(list[8]).toDouble();
        gFreqStandard->append(mtmp);
    }

    return;
}

qint32 Pm_User_Variable::CalculateChannelNum()
{
    qint32 index = 0,channelSTD = 0,direction =0;
    qreal freq;
    channelSTD = gMeterParam.gConfig_Freq.nChannelStd;
    freq = gMeterParam.gConfig_Freq.nlCenterFreq;
    direction = gMeterParam.gConfig_Freq.nChannelType;
    switch (channelSTD) {
    case PM_CDMA:
        if(direction == PM_UPLINK)
        {
            index = (freq - 825000000)/(0.03 *PM_MHZ);
        }
        else
        {
            index = (freq - 870000000)/(0.03 *PM_MHZ);
        }
        break;
    case PM_GSM:
        if(freq < 1500000000)
        {
            if(direction == PM_UPLINK)
            {
                index = (freq - 890200000)/(0.2*PM_MHZ)+1;
            }
            else
            {
                index = (freq - 935200000)/(0.2*PM_MHZ)+1;
            }
        }else
        {
            if(direction == PM_UPLINK)
            {
                index = (freq - 1710000000)/(0.2*PM_MHZ)+511;
            }
            else
            {
                index = (freq - 1805000000)/(0.2*PM_MHZ)+511;
            }
        }
        break;
    case PM_WCDMA:
        index = freq/PM_MHZ * 5;
        break;
    case PM_TD_SCDMA:
        if(freq >2010000000 && freq<=2025000000 ) //A Freq
        {
            index = freq/PM_MHZ *5;
        }else if(freq > 1800000000 && freq<=2000000000) //F Freq
        {
            index = freq/PM_MHZ *5;
        }else if(freq > 2300000000 && freq<=2400000000)  //E Freq
        {
            index = freq/PM_MHZ *5;
        }
        break;
    case PM_LTE_TDD:
        if(freq >= PM_TD_B38_FREQ_MIN && freq <= PM_TD_B38_FREQ_MAX)
        {
            index = (freq - PM_TD_B38_FREQ_MIN)/PM_MHZ*10+PM_TD_B38_FREQPOINT_BASE;
        }
        else if(freq >= PM_TD_B39_FREQ_MIN && freq <= PM_TD_B39_FREQ_MAX)
        {
            index = (freq - PM_TD_B39_FREQ_MIN)/PM_MHZ*10+PM_TD_B39_FREQPOINT_BASE;
        }
        else if(freq >= PM_TD_B40_FREQ_MIN && freq <= PM_TD_B40_FREQ_MAX)
        {
            index = (freq - PM_TD_B40_FREQ_MIN)/PM_MHZ*10+PM_TD_B40_FREQPOINT_BASE;
        }
        else if(freq >= PM_TD_B41_FREQ_MIN && freq <= PM_TD_B41_FREQ_MAX)
        {
            index = (freq - PM_TD_B41_FREQ_MIN)/PM_MHZ*10+PM_TD_B41_FREQPOINT_BASE;
        }
        break;
    case PM_LTE_FDD:
        if(freq >= PM_FDD_B1_UP_FREQ_MIN && freq <= PM_FDD_B1_UP_FREQ_MAX)
        {
            index = (freq - PM_FDD_B1_UP_FREQ_MIN)*10/PM_MHZ+PM_FDD_B1_UP_FREQPOINT_BASE;
        }
        else if(freq >= PM_FDD_B1_DOWN_FREQ_MIN && freq <= PM_FDD_B1_DOWN_FREQ_MAX)
        {
            index = (freq - PM_FDD_B1_DOWN_FREQ_MIN)*10/PM_MHZ+PM_FDD_B1_DOWN_FREQPOINT_BASE;
        }
        else if(freq >= PM_FDD_B3_UP_FREQ_MIN && freq <= PM_FDD_B3_UP_FREQ_MAX)
        {
            index = (freq - PM_FDD_B3_UP_FREQ_MIN)*10/PM_MHZ+PM_FDD_B3_UP_FREQPOINT_BASE;
        }
        else if(freq >= PM_FDD_B3_DOWN_FREQ_MIN && freq <= PM_FDD_B3_DOWN_FREQ_MAX)
        {
            index = (freq - PM_FDD_B3_DOWN_FREQ_MIN)*10/PM_MHZ+PM_FDD_B3_DOWN_FREQPOINT_BASE;
        }
        break;
    }
    return index;
}

void Pm_User_Variable::adjustCHStandarByCerFreq(qreal freq)
{
    freq = (qreal)freq/PM_MHZ;
    qint32 size;
    for(qint32 i = 0 ;i<7;i++)
    {
        getBandInfo(i);
        size = gCHName->size();
        for(qint32 j=0;j<size;j++)
        {
            if(freq>=gFreqStandard->at(j).Up.Min && freq<=gFreqStandard->at(j).Up.Max)
            {
                gMeterParam.gConfig_Freq.nChannelStd =i;
                gMeterParam.gConfig_Freq.nChannelSelID = j;
                gMeterParam.gConfig_Freq.nChannelNumber = CalculateChannelNum();
                gMeterParam.gConfig_Freq.nChannelStep = mPM_ChStand[i].ChStep;
                gMeterParam.gConfig_Freq.nChannelType = PM_UPLINK;
                return;
            }else if(freq>=gFreqStandard->at(j).Down.Min && freq<=gFreqStandard->at(j).Down.Max)
            {
                gMeterParam.gConfig_Freq.nChannelStd =i;
                gMeterParam.gConfig_Freq.nChannelSelID = j;
                gMeterParam.gConfig_Freq.nChannelNumber = CalculateChannelNum();
                gMeterParam.gConfig_Freq.nChannelStep = mPM_ChStand[i].ChStep;
                gMeterParam.gConfig_Freq.nChannelType = PM_DOWNLINK;
                return;
            }
        }
    }
    gMeterParam.gConfig_Freq.nChannelSelID = 0;
    gMeterParam.gConfig_Freq.nChannelStd = -1;
    return;
}

qreal Pm_User_Variable::adjustFreqByCHStandar()
{
    if(gMeterParam.gConfig_Freq.nChannelStd < 0 || gFreqStandard->isEmpty())
        return gMeterParam.gConfig_Freq.nlCenterFreq;
    qreal freq,min,max;
    qint32 direction,index;
    direction = gMeterParam.gConfig_Freq.nChannelType;
    freq = gMeterParam.gConfig_Freq.nlCenterFreq;
    index = gMeterParam.gConfig_Freq.nChannelSelID;
    if(direction == PM_UPLINK)
    {
        min = gFreqStandard->at(index).Up.Min * PM_MHZ;
        max = gFreqStandard->at(index).Up.Max * PM_MHZ;
    }
    else
    {
        min = gFreqStandard->at(index).Down.Min * PM_MHZ;
        max = gFreqStandard->at(index).Down.Max * PM_MHZ;
    }
    if(freq < min || freq > max)
    {
        freq = (min + max)/2;
    }
    if(gMeterParam.gConfig_Freq.nOffsetFreqOn)
        freq += gMeterParam.gConfig_Freq.nlOffsetFreq;
    return freq;
}

qreal Pm_User_Variable::adjustFreqByCHNum(qint32 index)
{
    qint32 channelSTD = 0,direction = 0;
    qreal freq = 0;
    channelSTD = gMeterParam.gConfig_Freq.nChannelStd;
    direction = gMeterParam.gConfig_Freq.nChannelType;
    switch (channelSTD) {
    case PM_CDMA:
        if(direction == PM_UPLINK)
        {
            freq = index*(0.03 *PM_MHZ) + 825000000;
        }else
        {
            freq = index*(0.03 *PM_MHZ) + 870000000;
        }
        break;
    case PM_GSM:
        if(index < 125)
        {
            if(direction == PM_UPLINK)
            {
                freq = (index-1)*(0.2*PM_MHZ) + 890200000;
            }else
            {
                freq = (index-1)*(0.2*PM_MHZ) + 935200000;
            }
        }else
        {
            if(direction == PM_UPLINK)
            {
                freq = (index-511)*(0.2*PM_MHZ)+ 1710000000;
            }else
            {
                freq = (index-511)*(0.2*PM_MHZ)+ 1805000000;
            }
        }
        break;
    case PM_WCDMA:
        freq = (qreal)index / 5 * PM_MHZ;
        break;
    case PM_TD_SCDMA:
        freq = (qreal)index / 5 * PM_MHZ;
        //        if(freq >2010000000 && freq<=2025000000 ) //A Freq
        //        {
        //            index = freq *5;
        //        }else if(freq > 1800000000 && freq<=2000000000) //F Freq
        //        {

        //        }else if(freq > 2300000000 && freq<=2400000000)  //E Freq
        //        {

        //        }
        break;
    case PM_LTE_TDD:
        if(index >= PM_TD_B38_FREQPOINT_BASE && index <= PM_TD_B38_FREQPOINT_MAX)
        {
            freq = (index - PM_TD_B38_FREQPOINT_BASE)*PM_MHZ/10 + PM_TD_B38_FREQ_MIN;
        }else if(index >= PM_TD_B39_FREQPOINT_BASE && index <= PM_TD_B39_FREQPOINT_MAX)
        {
            freq = (index - PM_TD_B39_FREQPOINT_BASE)*PM_MHZ/10 + PM_TD_B39_FREQ_MIN;
        }else if(index >= PM_TD_B40_FREQPOINT_BASE && index <= PM_TD_B40_FREQPOINT_MAX)
        {
            freq = (index - PM_TD_B40_FREQPOINT_BASE)*PM_MHZ/10 + PM_TD_B40_FREQ_MIN;
        }else if(index >= PM_TD_B41_FREQPOINT_BASE && index <= PM_TD_B41_FREQPOINT_MAX)
        {
            freq = (index - PM_TD_B41_FREQPOINT_BASE)*PM_MHZ/10 + PM_TD_B41_FREQ_MIN;
        }
        break;
    case PM_LTE_FDD:
        if(index >= PM_FDD_B1_UP_FREQPOINT_BASE && index <= PM_FDD_B1_UP_FREQPOINT_MAX)
        {
            freq = (index-PM_FDD_B1_UP_FREQPOINT_BASE)*PM_MHZ/10+ PM_FDD_B1_UP_FREQ_MIN ;
        }else if(index >= PM_FDD_B1_DOWN_FREQPOINT_BASE && index <= PM_FDD_B1_DOWN_FREQPOINT_MAX)
        {
            freq = (index -PM_FDD_B1_DOWN_FREQPOINT_BASE)*PM_MHZ/10+ PM_FDD_B1_DOWN_FREQ_MIN;
        }else if(index >= PM_FDD_B3_UP_FREQPOINT_BASE && index <= PM_FDD_B3_UP_FREQPOINT_MAX)
        {
            freq = (index - PM_FDD_B3_UP_FREQPOINT_BASE)*PM_MHZ/10 + PM_FDD_B3_UP_FREQ_MIN;
        }else if(index >= PM_FDD_B3_DOWN_FREQPOINT_BASE && index <= PM_FDD_B3_DOWN_FREQPOINT_MAX)
        {
            freq = (index - PM_FDD_B3_DOWN_FREQPOINT_BASE)*PM_MHZ/10 + PM_FDD_B3_DOWN_FREQ_MIN;
        }
        break;
    }
    if(gMeterParam.gConfig_Freq.nOffsetFreqOn)
    freq += gMeterParam.gConfig_Freq.nlOffsetFreq;
    return freq;
}

bool Pm_User_Variable::IsFreqInCurChStd()
{
    bool InCurStd = false;
    if(gMeterParam.gConfig_Freq.nChannelStd < 0 || gFreqStandard->isEmpty())
        return InCurStd;
    qreal freq,min,max;
    qint32 direction,index;
    direction =  gMeterParam.gConfig_Freq.nChannelType;
    freq = gMeterParam.gConfig_Freq.nlCenterFreq;
    index = gMeterParam.gConfig_Freq.nChannelSelID;
    if(direction == PM_UPLINK)
    {
        min = gFreqStandard->at(index).Up.Min * PM_MHZ;
        max = gFreqStandard->at(index).Up.Max * PM_MHZ;
    }
    else
    {
        min = gFreqStandard->at(index).Down.Min * PM_MHZ;
        max = gFreqStandard->at(index).Down.Max * PM_MHZ;
    }
    if(freq < min || freq > max)
    {
        InCurStd = false;
    }
    else
    {
        InCurStd = true;
    }
    return InCurStd;

}




