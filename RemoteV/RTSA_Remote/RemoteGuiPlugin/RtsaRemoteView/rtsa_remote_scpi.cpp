#include "rtsa_remote_scpi.h"
#include <qmath.h>

RtSa_Remote_Scpi::RtSa_Remote_Scpi(QObject *parent)
    : QObject(parent)
{ // BitVncHandle::SetVncInternetHandle(bitvnc_internet::GetInstance());

}

RtSa_Remote_Scpi::~RtSa_Remote_Scpi()
{
}


void RtSa_Remote_Scpi::SetCenterFreq(qreal freq)
{    
    QString iVal = QString::number(freq);
    QString  strCmd = ":FREQuency:CENTer ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::getCenterFreq()
{
    QString  strCmd = ":FREQuency:CENTer?";
    emit sendScpiAndRecv(strCmd);
}

void RtSa_Remote_Scpi::setStartFreq(qreal freq)
{
    QString iVal = QString::number(freq);
    QString strCmd = ":FREQuency:STARt ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    return;
}

void RtSa_Remote_Scpi::getStartFreq()
{
    QString strCmd = ":FREQuency:STARt?";
    emit sendScpiAndRecv(strCmd);
    return ;
}

void RtSa_Remote_Scpi::setStopFreq(qreal freq)
{
    QString iVal = QString::number(freq);
    QString strCmd = ":FREQuency:STOP ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    return;
}

void RtSa_Remote_Scpi::getStopFreq()
{
    QString strCmd = ":FREQuency:STOP?";
    emit sendScpiAndRecv(strCmd);
    return;
}

void RtSa_Remote_Scpi::setSpan(qreal freq)
{
    QString iVal = QString::number(freq);
    QString strCmd = ":FREQuency:SPAN ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::getSpan()
{
    QString strCmd = ":FREQuency:SPAN?";
    emit sendScpiAndRecv(strCmd);
    return;
}

void RtSa_Remote_Scpi::setFullSpan()
{
    QString strCmd = ":FREQuency:SPAN:FULL";
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::setCFStep(qreal freq)
{
    QString iVal = QString::number(freq);
    QString strCmd = ":FREQuency:STEP ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::getStepFreq()
{
    QString strCmd = ":FREQuency:STEP?";
    emit sendScpiAndRecv(strCmd);
    return;
}

void RtSa_Remote_Scpi::setFreqOffset(qreal freq)
{
    QString iVal = QString::number(freq);
    QString strCmd = ":FREQuency:OFFSet ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

}

void RtSa_Remote_Scpi::getFreqOffset()
{
    QString strCmd = ":FREQuency:OFFSet?";
       emit sendScpiAndRecv(strCmd);
    return;
}


void RtSa_Remote_Scpi::setCHStandard(qint32 index)
{
    QString iVal = QString::number(index);
    QString strCmd = ":FREQuency:CHannel:STD ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

}
void RtSa_Remote_Scpi::getCHStandard()
{
    QString strCmd = ":FREQuency:CHannel:STD?";
    emit sendScpiAndRecv(strCmd);
    return;
}

void RtSa_Remote_Scpi::setBandIndex(qint32 bandIndex)
{
    QString iVal = QString::number(bandIndex);
    QString strCmd = ":FREQuency:CHannel:STD:BAND ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

}
void RtSa_Remote_Scpi::getBandIndex()
{
    QString strCmd = ":FREQuency:CHannel:STD:BAND?";
    emit sendScpiAndRecv(strCmd);
    return;
}

void RtSa_Remote_Scpi::setChannelType(qint32 direction)
{
    QString iVal = QString::number(direction);
    QString strCmd = ":FREQuency:CHannel:TYPE ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
}
void RtSa_Remote_Scpi::getChannelType()
{
    QString strCmd = ":FREQuency:CHannel:TYPE?";
      emit sendScpiAndRecv(strCmd);
    return;

}

void RtSa_Remote_Scpi::setChannelNumber(qint32 number)
{
    QString iVal = QString::number(number);
    QString strCmd = ":FREQuency:CHannel:NUMber ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
}

void RtSa_Remote_Scpi::getChannelNumber()
{
    QString strCmd = ":FREQuency:CHannel:NUMber?";
    emit sendScpiAndRecv(strCmd);
    return;
}


void RtSa_Remote_Scpi::setAutoScale()
{
    QString strCmd = ":AMPLitude:SCALe:AUTO";
    emit sendSCPIcmd(strCmd);
}

void RtSa_Remote_Scpi::setRefLevel(qreal refLevel)
{
    QString iVal = QString::number(refLevel);
    QString strCmd = ":AMPLitude:RLEVel ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::getRefLevel()
{
    QString strCmd = ":AMPLitude:RLEVel?";
    emit sendScpiAndRecv(strCmd);
    return;

}

void RtSa_Remote_Scpi::setScaleDiv(qreal scaleDiv)
{
    QString iVal = QString::number(scaleDiv);
    QString strCmd = ":AMPLitude:SCALe ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::getScaleDiv()
{
    QString strCmd = ":AMPLitude:SCALe?";
    emit sendScpiAndRecv(strCmd);
    return;
}

void RtSa_Remote_Scpi::setAttenAuto(bool isAttenAuto)
{
    QString iVal = QString::number(isAttenAuto);
    QString strCmd = ":AMPLitude:ATTEnuation:AUTO ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    return;
}

void RtSa_Remote_Scpi::IsAttenAuto()
{
    QString strCmd = ":AMPLitude:ATTEnuation:AUTO?";
      emit sendScpiAndRecv(strCmd);
    return;
}

void RtSa_Remote_Scpi::setAttenVal(qreal attenVal)
{

    QString iVal = QString::number(attenVal);
    QString strCmd = ":AMPLitude:ATTEnuation ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::getAttenVal()
{
    QString strCmd = ":AMPLitude:ATTEnuation?";
    emit sendScpiAndRecv(strCmd);
    return;
}

void RtSa_Remote_Scpi::setPreAmpOn(bool IsOn)
{
    QString iVal = QString::number(IsOn);
    QString strCmd = ":AMPLitude:PREAmp ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::IsPreAmpOn()
{
    QString strCmd = ":AMPLitude:PREAmp?";
    emit sendScpiAndRecv(strCmd);
    return;

}

void  RtSa_Remote_Scpi::setRefOffset(qreal refOffset)
{
    QString iVal = QString::number(refOffset);
    QString strCmd = ":AMPLitude:RLEVel:OFFSet ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::getRefOffset()
{
    QString strCmd = ":AMPLitude:RLEVel:OFFSet?";
    emit sendScpiAndRecv(strCmd);
    return;
}

void RtSa_Remote_Scpi::setAmptUnit(qint32 unitIndex)
{
    QString iVal = QString::number(unitIndex);
    QString strCmd = ":AMPLitude:PDIVision ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::getAmptUint()
{  QString strCmd = ":AMPLitude:PDIVision?";

    emit sendScpiAndRecv(strCmd);
    return;
}

void RtSa_Remote_Scpi::setSingleSweep(bool isSingle)
{
//    QString iVal = QString::number(isSingle);
    QString strCmd;
    if(1 == isSingle)
    {
        strCmd = ":SWEEp:CONTinuous:ONCE";
    }
    else
    {
        strCmd = ":SWEEp:CONTinuous ";
        strCmd += 10000000000000;
    }
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::IsSingleSweep()
{
    QString strCmd = ":SWEEp:CONTinuous?";
    emit sendScpiAndRecv(strCmd);
    return;
}

void RtSa_Remote_Scpi::setAcqTimeAuto(bool isAuto)
{
    QString iVal = QString::number(isAuto);
    QString strCmd = ":SWEEp:ACQtime:AUTO ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::IsAcqTimeAuto()
{
    QString strCmd = ":SWEEp:ACQtime:AUTO?";
    emit sendScpiAndRecv(strCmd);
    return;
}

/**
* @brief setAcqTime
* @param [in] time
* @Author Albert
* @date 2019-04-16
*/
void RtSa_Remote_Scpi::setAcqTime(qreal time)
{
    QString iVal = QString::number(time);
    QString strCmd = ":SWEEp: ACQtime ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;

}
void  RtSa_Remote_Scpi::getAcqTime()
{
    QString strCmd = ":SWEEp: ACQtime?";
    emit sendScpiAndRecv(strCmd);
    return;
}


/**
    * @brief setBWAuto
    * @param [in] isAuto
    * @Author Albert
    * @date 2019-04-16
    */
void RtSa_Remote_Scpi::setBWAuto(bool isAuto)
{
    QString iVal = QString::number(isAuto);
    QString strCmd = ":BANDwidth:RBW:AUTO ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::IsBWAuto()
{
    QString strCmd = ":BANDwidth:RBW:AUTO?";
    emit sendScpiAndRecv(strCmd);
    return;
}

/**
    * @brief setBW
    * @param [in] rbw
    * @Author Albert
    * @date 2019-04-16
    */
void RtSa_Remote_Scpi::setBWIndex(qreal rbw)
{
    QString iVal = QString::number(rbw);
    QString strCmd = ":BANDwidth:RBW ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;

}

void RtSa_Remote_Scpi::getBWIndex()
{
    QString strCmd = ":BANDwidth:RBW?";
    emit sendScpiAndRecv(strCmd);
    return;
}

/**
    * @brief setBWFFTWindow
    * @param [in] fftwindow
    * @Author Albert
    * @date 2019-04-16
    */
void RtSa_Remote_Scpi::setBWFFTWindow(qint32 fftwindow)
{
    QString iVal = QString::number(fftwindow);
    QString strCmd = ":BANDwidth:FFTWindow ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}

void  RtSa_Remote_Scpi::getFFTWindow()
{
    QString strCmd = ":BANDwidth:FFTWindow?";
     emit sendScpiAndRecv(strCmd);
    return;
}

/**
* @brief setTrigger
* @param [in] TriggerMode
* @Author Albert
* @date 2019-04-16
*/
void RtSa_Remote_Scpi::setTrigger(qint32 TriggerMode)
{
    QString iVal = QString::number(TriggerMode);
    QString strCmd = ":TRIGger:SOURce ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}

/**
* @brief getTrigger
* @param none
* @Author Albert
* @date 2019-04-16
*/
void RtSa_Remote_Scpi::getTrigger()
{
    QString strCmd = ":TRIGger:SOURce?";
    emit sendScpiAndRecv(strCmd);
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-06-03
*/
void RtSa_Remote_Scpi::setTriggerLevel(qint32 TriggerMode,qreal level)
{
    QString iVal = QString::number(level);
    QString strCmd;
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        strCmd =   ":TRIGger:LEVEl ";
        break;
    case RTSA_TRIGGER_EXTERNAL:
        strCmd =   ":TRIGger:LEVEl ";
        break;
    case RTSA_TRIGGER_RF_BURST:
        strCmd =   ":TRIGger:RFBUrst:LEVEl ";
        break;
    default:
        strCmd =   ":TRIGger:LEVEl ";
        break;
    }
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-06-03
*/
void RtSa_Remote_Scpi::getTriggerLevel(qint32 TriggerMode)
{
    QString strCmd;
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        strCmd =   ":TRIGger:LEVEl?";
        break;
    case RTSA_TRIGGER_EXTERNAL:
        strCmd =   ":TRIGger:LEVEl?";
        break;
    case RTSA_TRIGGER_RF_BURST:
        strCmd =   ":TRIGger:RFBUrst:LEVEl?";
        break;
    default:
        strCmd =   ":TRIGger:LEVEl?";
        break;
    }
    emit sendScpiAndRecv(strCmd);
    return;
}


/**
* @brief
* @param
* @Author Albert
* @date 2019-06-03
*/
void RtSa_Remote_Scpi::setTriggerSlope(qint32 TriggerMode, qint32 slope)
{
    QString iVal = QString::number(slope);
    QString strCmd;
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        strCmd =   ":TRIGger:SLOPe ";
        break;
    case RTSA_TRIGGER_EXTERNAL:
        strCmd =   ":TRIGger:EXTErnal:SLOPe ";
        break;
    case RTSA_TRIGGER_RF_BURST:
        strCmd =   ":TRIGger:RFBUrst:SLOPe ";
        break;
    default:
        strCmd =   ":TRIGger:SLOPe ";
        break;
    }
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-06-03
*/
void RtSa_Remote_Scpi::getTriggerSlope(qint32 TriggerMode)
{
    QString strCmd;
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        strCmd =   ":TRIGger:SLOPe?";
        break;
    case RTSA_TRIGGER_EXTERNAL:
        strCmd =   ":TRIGger:EXTErnal:SLOPe?";
        break;
    case RTSA_TRIGGER_RF_BURST:
        strCmd =   ":TRIGger:RFBUrst:SLOPe?";
        break;
    default:
        strCmd =   ":TRIGger:SLOPe?";
        break;
    }
    emit sendScpiAndRecv(strCmd);
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
void RtSa_Remote_Scpi::setTriggerDelayStatus(qint32 TriggerMode, bool delayStatus)
{
    QString iVal = QString::number(delayStatus);

    QString strCmd;
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        strCmd =   ":TRIGger:DELAy:STATe ";
        break;
    case RTSA_TRIGGER_EXTERNAL:
        strCmd =   ":TRIGger:EXTErnal:DELAy:STATe ";
        break;
    case RTSA_TRIGGER_RF_BURST:
        strCmd =   ":TRIGger:RFBUrst:DELAy:STATe ";
        break;
    case RTSA_TRIGGER_PERIODIC_TIMER:
        strCmd =   ":TRIGger:PERIodic:DELAy:STATe ";
        break;
    default:
        strCmd =   ":TRIGger:DELAy:STATe ";
        break;
    }
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
void RtSa_Remote_Scpi::getTriggerDelayStatus(qint32 TriggerMode)
{
    QString strCmd;
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        strCmd = ":TRIGger:DELAy:STATe?";
        break;
    case RTSA_TRIGGER_EXTERNAL:
        strCmd = ":TRIGger:EXTErnal:DELAy:STATe?";
        break;
    case RTSA_TRIGGER_RF_BURST:
        strCmd = ":TRIGger:RFBUrst:DELAy:STATe?";
        break;
    case RTSA_TRIGGER_PERIODIC_TIMER:
        strCmd = ":TRIGger:PERIodic:DELAy:STATe?";
        break;
    default:
        strCmd = ":TRIGger:DELAy:STATe?";
        break;
    }
    emit sendScpiAndRecv(strCmd);
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
void RtSa_Remote_Scpi::setTriggerDelay(qint32 TriggerMode, qreal Delay)
{
    QString iVal = QString::number(Delay);
    QString strCmd;
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        strCmd =   ":TRIGger:DELAy ";
        break;
    case RTSA_TRIGGER_EXTERNAL:
        strCmd =   ":TRIGger:EXTErnal:DELAy ";
        break;
    case RTSA_TRIGGER_RF_BURST:
        strCmd =   ":TRIGger:RFBUrst:DELAy ";
        break;
    case RTSA_TRIGGER_PERIODIC_TIMER:
        strCmd =   ":TRIGger:PERIodic:DELAy ";
        break;
    default:
        strCmd =   ":TRIGger:DELAy ";
        break;
    }
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
void RtSa_Remote_Scpi::getTriggerDelay(qint32 TriggerMode)
{
    QString strCmd;
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
        strCmd = ":TRIGger:DELAy?";
        break;
    case RTSA_TRIGGER_EXTERNAL:
        strCmd = ":TRIGger:EXTErnal:DELAy?";
        break;
    case RTSA_TRIGGER_RF_BURST:
        strCmd = ":TRIGger:RFBUrst:DELAy?";
        break;
    case RTSA_TRIGGER_PERIODIC_TIMER:
        strCmd = ":TRIGger:PERIodic:DELAy?";
        break;
    default:
        strCmd = ":TRIGger:DELAy?";
        break;
    }
    emit sendScpiAndRecv(strCmd);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
void RtSa_Remote_Scpi::setTriggerPeriodTime(qreal time)
{
    QString iVal = QString::number(time);
    QString strCmd = ":TRIGger:PERiodic ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
void RtSa_Remote_Scpi::getTriggerPeriodTime()
{
    QString strCmd = ":TRIGger:PERiodic?";
    emit sendScpiAndRecv(strCmd);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-17
*/
void RtSa_Remote_Scpi::settriggerHoldOffTime(qint32 TriggerMode, qreal holdOffTime)
{
    QString iVal = QString::number(holdOffTime);
    QString strCmd;
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
      strCmd = ":TRIGger:HOLD:OFF ";
        break;
    case RTSA_TRIGGER_EXTERNAL:
        strCmd = ":TRIGger:EXTErnal:HOLD:OFF ";
        break;
    case RTSA_TRIGGER_RF_BURST:
        strCmd = ":TRIGger:RFBUrst:HOLD:OFF ";
        break;
    case RTSA_TRIGGER_FMTMASK:
        strCmd = ":TRIGger:FMT:HOLD:OFF ";
        break;
    default:
        strCmd = ":TRIGger:HOLD:OFF ";
        break;
    }
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    return;
}
void RtSa_Remote_Scpi::getriggerHoldOffTime(qint32 TriggerMode)
{
    QString strCmd;
    switch(TriggerMode)
    {
    case RTSA_TRIGGER_VIDEO:
      strCmd = ":TRIGger:HOLD:OFF ";
        break;
    case RTSA_TRIGGER_EXTERNAL:
        strCmd = ":TRIGger:EXTErnal:HOLD:OFF?";
        break;
    case RTSA_TRIGGER_RF_BURST:
        strCmd = ":TRIGger:RFBUrst:HOLD:OFF?";
        break;
    case RTSA_TRIGGER_FMTMASK:
        strCmd = ":TRIGger:FMT:HOLD:OFF?";
        break;
    default:
        strCmd = ":TRIGger:HOLD:OFF?";
        break;
    }
    emit sendScpiAndRecv(strCmd);

    return;
}
//FMT trigger


void RtSa_Remote_Scpi::BuildFmtFromTrace()
{
    QString strCmd = ":TRIGger:FMT:MASK:BUILd";
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::DeleteAllFmtMask()
{
    QString strCmd = ":TRIGger:FMT:MASK:DELete";
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::setFmtType(qint32 Upper)
{
    QString iVal = QString::number(Upper);
    QString strCmd = ":TRIGger:FMT:MASK:TYPE ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;

}
void RtSa_Remote_Scpi::getFmtType()
{
    QString strCmd = ":TRIGger:FMT:MASK:TYPE?";
    emit sendScpiAndRecv(strCmd);
    return;
}

void RtSa_Remote_Scpi::setFmtTriggerCriterion(qint32 criterion)
{
    QString iVal = QString::number(criterion);
    QString strCmd = ":TRIGger:FMT:MASK:CRITertion ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
void RtSa_Remote_Scpi::getFmtTriggerCriterion()
{
    QString strCmd = ":TRIGger:FMT:MASK:CRITertion?";
     emit sendScpiAndRecv(strCmd);
     return;
}
void RtSa_Remote_Scpi::setFmtDataNum(qint32 dataNum)
{

}

void RtSa_Remote_Scpi::getFmtDataNum()
{
    QString strCmd = ":TRIGger:FMT:MASK:COUNt?";
     emit sendScpiAndRecv(strCmd);
     return;
}

void RtSa_Remote_Scpi::setCurFmtFreqData(qreal data, qint32 index)
{
    QString iVal = QString::number(data);
    QString strCmd = ":TRIGger:FMT:MASK:DATA:FREQuency ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
void RtSa_Remote_Scpi::getCurFmtFreqData(qint32 index)
{
    QString strCmd = ":TRIGger:FMT:MASK:DATA:FREQuency?";
    emit sendScpiAndRecv(strCmd);
    return;
}

void RtSa_Remote_Scpi::setCurFmtAmptData(qreal data, qint32 index)
{
    QString iVal = QString::number(data);
    QString strCmd = ":TRIGger:FMT:MASK:DATA:AMPLitude ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;

}
void RtSa_Remote_Scpi::getCurFmtAmptData(qint32 index)
{
    QString strCmd = ":TRIGger:FMT:MASK:DATA:AMPLitude?";
     emit sendScpiAndRecv(strCmd);
     return;

}

void RtSa_Remote_Scpi::InsertFmtDataRow()
{
    QString strCmd = ":TRIGger:FMT:MASK:INSErt";
     emit sendSCPIcmd(strCmd);
     return;
}
void RtSa_Remote_Scpi::setTraceViewStatus(bool status,qint32 traceID)
{
    QString iVal = QString::number(status);
    QString strCmd;
    switch (traceID)
    {
    case 0:
        strCmd = ":TRACe:DISPlay ";
        break;
    case 1:
        strCmd = ":TRACe:1:DISPlay ";
        break;
    case 2:
        strCmd = ":TRACe:2:DISPlay ";
        break;
    case 3:
        strCmd = ":TRACe:3:DISPlay ";
        break;
    case 4:
        strCmd = ":TRACe:4:DISPlay ";
        break;
    case 5:
        strCmd = ":TRACe:5:DISPlay ";
        break;
    case 6:
        strCmd = ":TRACe:6:DISPlay ";
        break;
    default:
        strCmd = ":TRACe:DISPlay ";
        break;
    }
    ;
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::getTraceViewStatus(qint32 traceID)
{
    QString strCmd;
    switch (traceID)
    {
    case 0:
        strCmd = ":TRACe:DISPlay?";
        break;
    case 1:
        strCmd = ":TRACe:1:DISPlay?";
        break;
    case 2:
        strCmd = ":TRACe:2:DISPlay?";
        break;
    case 3:
        strCmd = ":TRACe:3:DISPlay?";
        break;
    case 4:
        strCmd = ":TRACe:4:DISPlay?";
        break;
    case 5:
        strCmd = ":TRACe:5:DISPlay?";
        break;
    case 6:
        strCmd = ":TRACe:6:DISPlay?";
        break;
    default:
        strCmd = ":TRACe:DISPlay?";
        break;
    }
    emit sendScpiAndRecv(strCmd);
    return;
}

void RtSa_Remote_Scpi::setCurTraceType(qint32 traceType,qint32 traceID)
{
    QString iVal = QString::number(traceType);
    QString strCmd;
    switch (traceID)
    {
    case 0:
        strCmd = ":TRACe:TYPE ";
        break;
    case 1:
        strCmd = ":TRACe:1:TYPE ";
        break;
    case 2:
        strCmd = ":TRACe:2:TYPE ";
        break;
    case 3:
        strCmd = ":TRACe:3:TYPE ";
        break;
    case 4:
        strCmd = ":TRACe:4:TYPE ";
        break;
    case 5:
        strCmd = ":TRACe:5:TYPE ";
        break;
    case 6:
        strCmd = ":TRACe:6:TYPE ";
        break;
    default:
        strCmd = ":TRACe:TYPE ";
        break;
    }
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::getCurTraceType(qint32 traceID)
{
    QString strCmd;
    switch (traceID)
    {
    case 0:
        strCmd = ":TRACe:TYPE?";
        break;
    case 1:
        strCmd = ":TRACe:1:TYPE?";
        break;
    case 2:
        strCmd = ":TRACe:2:TYPE?";
        break;
    case 3:
        strCmd = ":TRACe:3:TYPE?";
        break;
    case 4:
        strCmd = ":TRACe:4:TYPE?";
        break;
    case 5:
        strCmd = ":TRACe:5:TYPE?";
        break;
    case 6:
        strCmd = ":TRACe:6:TYPE?";
        break;
    default:
        strCmd = ":TRACe:TYPE?";
        break;
    }
    emit sendScpiAndRecv(strCmd);
    return;
}

void RtSa_Remote_Scpi::setCurTraceAvgNum(qint32 Num,qint32 traceID)
{
    QString iVal = QString::number(Num);
    QString strCmd;
    switch (traceID)
    {
    case 0:
        strCmd = ":TRACe:AVECount ";
        break;
    case 1:
        strCmd = ":TRACe:1:AVECount ";
        break;
    case 2:
        strCmd = ":TRACe:2:AVECount ";
        break;
    case 3:
        strCmd = ":TRACe:3:AVECount ";
        break;
    case 4:
        strCmd = ":TRACe:4:AVECount ";
        break;
    case 5:
        strCmd = ":TRACe:5:AVECount ";
        break;
    case 6:
        strCmd = ":TRACe:6:AVECount ";
        break;
    default:
        strCmd = ":TRACe:AVECount ";
        break;
    }
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::getCurTraceAvgNum(qint32 traceID)
{
    QString strCmd;
    switch (traceID)
    {
    case 0:
        strCmd = ":TRACe:AVECount?";
        break;
    case 1:
        strCmd = ":TRACe:1:AVECount?";
        break;
    case 2:
        strCmd = ":TRACe:2:AVECount?";
        break;
    case 3:
        strCmd = ":TRACe:3:AVECount?";
        break;
    case 4:
        strCmd = ":TRACe:4:AVECount?";
        break;
    case 5:
        strCmd = ":TRACe:5:AVECount?";
        break;
    case 6:
        strCmd = ":TRACe:6:AVECount?";
        break;
    default:
        strCmd = ":TRACe:AVECount?";
        break;
    }
    emit sendScpiAndRecv(strCmd);
    return;
}


/**
* @brief setDectorType
* @param [in] DectorType
* @Author Albert
* @date 2019-04-16
*/
void RtSa_Remote_Scpi::setDectorType(qint32 DectorType)
{
    QString iVal = QString::number(DectorType);
    QString strCmd  = ":TRACe:DETEctor ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
/**
* @brief getDectorType
* @param none
* @Author Albert
* @date 2019-04-16
*/
void RtSa_Remote_Scpi::getDectorType()
{
    QString strCmd  = ":TRACe:DETEctor?";
    emit sendScpiAndRecv(strCmd);
    return;
}


void RtSa_Remote_Scpi::GetCurTraceData()
{
    QString strCmd  = ":TRACe:DATA?";
    emit sendScpiAndRecv(strCmd);
    return;
}

void RtSa_Remote_Scpi::getDpxData()
{
    QString strCmd  = ":TRACe:DATA:RAWData?";
    emit sendScpiAndRecv(strCmd);
    return;
}

void RtSa_Remote_Scpi::setCurMarkerID(qint32 MarkerID)
{
    QString iVal = QString::number(MarkerID);
    QString strCmd  = ":MARKer:SELEct ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::getCurMarkerID()
{
    QString strCmd  = ":MARKer:SELEct?";
    emit sendScpiAndRecv(strCmd);
    return;

}

void RtSa_Remote_Scpi::setMarkerOn(qint32 MarkerID,bool isOn)
{
    QString iVal = QString::number(isOn);
    QString strCmd;
    switch (MarkerID)
    {
    case 0:
        strCmd = ":MARKer:1:DISPlay ";
        break;
    case 1:
        strCmd = ":MARKer:2:DISPlay ";
        break;
    case 2:
        strCmd = ":MARKer:3:DISPlay ";
        break;
    case 3:
        strCmd = ":MARKer:4:DISPlay ";
        break;
    case 4:
        strCmd = ":MARKer:5:DISPlay ";
        break;
    case 5:
        strCmd = ":MARKer:6:DISPlay ";
        break;
    default:
        strCmd = ":MARKer:DISPlay ";
        break;
    }
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
void RtSa_Remote_Scpi::isMarkerOn(qint32 MarkerID)
{
    QString strCmd;
    switch (MarkerID)
    {
    case 0:
        strCmd = ":MARKer:1:DISPlay?";
        break;
    case 1:
        strCmd = ":MARKer:2:DISPlay?";
        break;
    case 2:
        strCmd = ":MARKer:3:DISPlay?";
        break;
    case 3:
        strCmd = ":MARKer:4:DISPlay?";
        break;
    case 4:
        strCmd = ":MARKer:5:DISPlay?";
        break;
    case 5:
        strCmd = ":MARKer:6:DISPlay?";
        break;
    default:
        strCmd = ":MARKer:DISPlay?";
        break;
    }
    emit sendScpiAndRecv(strCmd);
    return;
}

void RtSa_Remote_Scpi::setMarkerType(qint32 MarkerID,qint32 MarkerType)
{
    QString iVal = QString::number(MarkerType);
    QString strCmd;
    switch (MarkerID)
    {
    case 0:
        strCmd = ":MARKer:1:TYPE ";
        break;
    case 1:
        strCmd = ":MARKer:2:TYPE ";
        break;
    case 2:
        strCmd = ":MARKer:3:TYPE ";
        break;
    case 3:
        strCmd = ":MARKer:4:TYPE ";
        break;
    case 4:
        strCmd = ":MARKer:5:TYPE ";
        break;
    case 5:
        strCmd = ":MARKer:6:TYPE ";
        break;
    default:
        strCmd = ":MARKer:TYPE ";
        break;
    }
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::getMarkerType(qint32 MarkerID)
{
    QString strCmd;
    switch (MarkerID)
    {
    case 0:
        strCmd = ":MARKer:1:TYPE?";
        break;
    case 1:
        strCmd = ":MARKer:2:TYPE?";
        break;
    case 2:
        strCmd = ":MARKer:3:TYPE?";
        break;
    case 3:
        strCmd = ":MARKer:4:TYPE?";
        break;
    case 4:
        strCmd = ":MARKer:5:TYPE?";
        break;
    case 5:
        strCmd = ":MARKer:6:TYPE?";
        break;
    default:
        strCmd = ":MARKer:TYPE?";
        break;
    }
    emit sendScpiAndRecv(strCmd);
    return;

}

void RtSa_Remote_Scpi::setMarkerToCenter()
{
    QString strCmd  = ":MARKer:TO:CENTer";
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::setMarkerToStart()
{
    QString strCmd  = ":MARKer:TO:STARt";
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::setMarkerToStop()
{
    QString strCmd  = ":MARKer:TO:STOP";
    emit sendSCPIcmd(strCmd);
    return;
}
void RtSa_Remote_Scpi::setMarkerToPeak()
{
    QString strCmd  = ":MARKer:PMAXimum";
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::setMarkerToMin()
{
    QString strCmd  = ":MARKer:PMINimum";
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::setMarkerToNextPeak()
{
    QString strCmd  = ":MARKer:PMAXimum:NEXT";
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::setMarkerToLeftPeak()
{
    QString strCmd  = ":MARKer:PMAXimum:LEFT";
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::setMarkerToRightPeak()
{
    QString strCmd  = ":MARKer:PMAXimum:RIGHt";
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::setPeakTrackOn(bool PeakTrackOn)
{
    QString iVal = QString::number(PeakTrackOn);
    QString strCmd  = ":MARKer:PTRAck ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
}

void RtSa_Remote_Scpi::IsPeakTrackOn()
{
    QString strCmd  = ":MARKer:PTRAck?";
    emit sendScpiAndRecv(strCmd);
    return;
}

void RtSa_Remote_Scpi::setMarkerRefFreq(qint32 MarkerID,qreal refFreq)
{

QString iVal = QString::number(refFreq);
QString strCmd;
switch (MarkerID)
{
case 0:
    strCmd = ":MARKer:1:X ";
    break;
case 1:
    strCmd = ":MARKer:2:X ";
    break;
case 2:
    strCmd = ":MARKer:3:X ";
    break;
case 3:
    strCmd = ":MARKer:4:X ";
    break;
case 4:
    strCmd = ":MARKer:5:X ";
    break;
case 5:
    strCmd = ":MARKer:6:X ";
    break;
default:
    strCmd = ":MARKer:X ";
    break;
}
strCmd += iVal;
emit sendSCPIcmd(strCmd);
return;
}
void RtSa_Remote_Scpi::getMarkerRefFreq(qint32 MarkerID)
{

    QString strCmd;
    switch (MarkerID)
    {
    case 0:
        strCmd = ":MARKer:1:X?";
        break;
    case 1:
        strCmd = ":MARKer:2:X?";
        break;
    case 2:
        strCmd = ":MARKer:3:X?";
        break;
    case 3:
        strCmd = ":MARKer:4:X?";
        break;
    case 4:
        strCmd = ":MARKer:5:X?";
        break;
    case 5:
        strCmd = ":MARKer:6:X?";
        break;
    default:
        strCmd = ":MARKer:X?";
        break;
    }
    emit sendScpiAndRecv(strCmd);
    return;
}

void RtSa_Remote_Scpi::setMarkerNoiseOn(qint32 MarkerID, bool isOn)
{
    QString iVal = QString::number(isOn);
    QString strCmd;
    switch (MarkerID)
    {
    case 0:
        strCmd = ":MARKer:1:NOISe:STATe ";
        break;
    case 1:
        strCmd = ":MARKer:2:NOISe:STATe ";
        break;
    case 2:
        strCmd = ":MARKer:3:NOISe:STATe ";
        break;
    case 3:
        strCmd = ":MARKer:4:NOISe:STATe ";
        break;
    case 4:
        strCmd = ":MARKer:5:NOISe:STATe ";
        break;
    case 5:
        strCmd = ":MARKer:6:NOISe:STATe ";
        break;
    default:
        strCmd = ":MARKer:NOISe:STATe ";
        break;
    }
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
void RtSa_Remote_Scpi::IsMarkerNoiseOn(qint32 MarkerID)
{
    QString strCmd;
    switch (MarkerID)
    {
    case 0:
        strCmd = ":MARKer:1:NOISe:STATe?";
        break;
    case 1:
        strCmd = ":MARKer:2:NOISe:STATe?";
        break;
    case 2:
        strCmd = ":MARKer:3:NOISe:STATe?";
        break;
    case 3:
        strCmd = ":MARKer:4:NOISe:STATe?";
        break;
    case 4:
        strCmd = ":MARKer:5:NOISe:STATe?";
        break;
    case 5:
        strCmd = ":MARKer:6:NOISe:STATe?";
        break;
    default:
        strCmd = ":MARKer:NOISe:STATe?";
        break;
    }
    emit sendScpiAndRecv(strCmd);
    return;
}


void RtSa_Remote_Scpi::setCurLimit(qint32 curIndex)
{
    QString iVal = QString::number(curIndex);
    QString strCmd  = ":LIMIt:SELEct ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

}

void RtSa_Remote_Scpi::getCurLimit()
{
    QString strCmd  = ":LIMIt:SELEct?";
    emit sendScpiAndRecv(strCmd);

    return;
}

void RtSa_Remote_Scpi::setCurLimitOn(qint32 LimitID,bool isOn)
{
    QString iVal = QString::number(isOn);
    QString strCmd;
    switch (LimitID)
    {
    case 0:
        strCmd = ":LIMIt:DISPlay ";
        break;
    case 1:
        strCmd = ":LIMIt:1:DISPlay ";
        break;
    case 2:
        strCmd = ":LIMIt:2:DISPlay ";
        break;
    case 3:
        strCmd = ":LIMIt:3:DISPlay ";
        break;
    case 4:
        strCmd = ":LIMIt:4:DISPlay ";
        break;
    case 5:
        strCmd = ":LIMIt:5:DISPlay ";
        break;
    case 6:
        strCmd = ":LIMIt:6:DISPlay ";
        break;
    default:
        strCmd = ":LIMIt:DISPlay ";
        break;
    }
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::IsCurLimitOn(qint32 LimitID)
{
    QString strCmd;
    switch (LimitID)
    {
    case 0:
        strCmd = ":LIMIt:DISPlay?";
        break;
    case 1:
        strCmd = ":LIMIt:1:DISPlay?";
        break;
    case 2:
        strCmd = ":LIMIt:2:DISPlay?";
        break;
    case 3:
        strCmd = ":LIMIt:3:DISPlay?";
        break;
    case 4:
        strCmd = ":LIMIt:4:DISPlay?";
        break;
    case 5:
        strCmd = ":LIMIt:5:DISPlay?";
        break;
    case 6:
        strCmd = ":LIMIt:6:DISPlay?";
        break;
    default:
        strCmd = ":LIMIt:DISPlay?";
        break;
    }
    emit sendScpiAndRecv(strCmd);
    return;
}

void RtSa_Remote_Scpi::setMarginOn(qint32 LimitID,bool isOn)
{
    QString iVal = QString::number(isOn);
    QString strCmd;
    switch (LimitID)
    {
    case 0:
        strCmd = ":LIMIt:EDGE:STATe ";
        break;
    case 1:
        strCmd = ":LIMIt:1:EDGE:STATe ";
        break;
    case 2:
        strCmd = ":LIMIt:2:EDGE:STATe ";
        break;
    case 3:
        strCmd = ":LIMIt:3:EDGE:STATe ";
        break;
    case 4:
        strCmd = ":LIMIt:4:EDGE:STATe ";
        break;
    case 5:
        strCmd = ":LIMIt:5:EDGE:STATe ";
        break;
    case 6:
        strCmd = ":LIMIt:6:EDGE:STATe ";
        break;
    default:
        strCmd = ":LIMIt:EDGE:STATe ";
        break;
    }
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
void RtSa_Remote_Scpi::IsMarginOn(qint32 LimitID)
{
    QString strCmd;
    switch (LimitID)
    {
    case 0:
        strCmd = ":LIMIt:EDGE:STATe?";
        break;
    case 1:
        strCmd = ":LIMIt:1:EDGE:STATe?";
        break;
    case 2:
        strCmd = ":LIMIt:2:EDGE:STATe?";
        break;
    case 3:
        strCmd = ":LIMIt:3:EDGE:STATe?";
        break;
    case 4:
        strCmd = ":LIMIt:4:EDGE:STATe?";
        break;
    case 5:
        strCmd = ":LIMIt:5:EDGE:STATe?";
        break;
    case 6:
        strCmd = ":LIMIt:6:EDGE:STATe?";
        break;
    default:
        strCmd = ":LIMIt:EDGE:STATe?";
        break;
    }
    emit sendScpiAndRecv(strCmd);

    return;
}

void RtSa_Remote_Scpi::setMargin(qint32 LimitID,qreal margin)
{

    QString iVal = QString::number(margin);
    QString strCmd;
    switch (LimitID)
    {
    case 0:
        strCmd = ":LIMIt:EDGE ";
        break;
    case 1:
        strCmd = ":LIMIt:1:EDGE ";
        break;
    case 2:
        strCmd = ":LIMIt:2:EDGE ";
        break;
    case 3:
        strCmd = ":LIMIt:3:EDGE ";
        break;
    case 4:
        strCmd = ":LIMIt:4:EDGE ";
        break;
    case 5:
        strCmd = ":LIMIt:5:EDGE ";
        break;
    case 6:
        strCmd = ":LIMIt:6:EDGE ";
        break;
    default:
        strCmd = ":LIMIt:EDGE ";
        break;
    }
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
void RtSa_Remote_Scpi::getMargin(qint32 LimitID)
{
    QString strCmd;
    switch (LimitID)
    {
    case 0:
        strCmd = ":LIMIt:EDGE?";
        break;
    case 1:
        strCmd = ":LIMIt:1:EDGE?";
        break;
    case 2:
        strCmd = ":LIMIt:2:EDGE?";
        break;
    case 3:
        strCmd = ":LIMIt:3:EDGE?";
        break;
    case 4:
        strCmd = ":LIMIt:4:EDGE?";
        break;
    case 5:
        strCmd = ":LIMIt:5:EDGE?";
        break;
    case 6:
        strCmd = ":LIMIt:6:EDGE?";
        break;
    default:
        strCmd = ":LIMIt:EDGE?";
        break;
    }
    emit sendScpiAndRecv(strCmd);
    return;
}

void RtSa_Remote_Scpi::setLimitTestOn(bool isOn)
{

    QString iVal = QString::number(isOn);
    QString strCmd  = ":LIMIt:TEST ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
}

void RtSa_Remote_Scpi::IsLimitTestOn()
{
    QString strCmd  = ":LIMIt:TEST?";
    emit sendScpiAndRecv(strCmd);
    return;
}

void RtSa_Remote_Scpi::setLimitType(qint32 LimitID,qint32 nType)
{
    QString iVal = QString::number(nType);
    QString strCmd;
    switch (LimitID)
    {
    case 0:
        strCmd = ":LIMIt:TYPE ";
        break;
    case 1:
        strCmd = ":LIMIt:1:TYPE ";
        break;
    case 2:
        strCmd = ":LIMIt:2:TYPE ";
        break;
    case 3:
        strCmd = ":LIMIt:3:TYPE ";
        break;
    case 4:
        strCmd = ":LIMIt:4:TYPE ";
        break;
    case 5:
        strCmd = ":LIMIt:5:TYPE ";
        break;
    case 6:
        strCmd = ":LIMIt:6:TYPE ";
        break;
    default:
        strCmd = ":LIMIt:TYPE ";
        break;
    }
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::getLimitType(qint32 LimitID)
{
    QString strCmd;
    switch (LimitID)
    {
    case 0:
        strCmd = ":LIMIt:TYPE?";
        break;
    case 1:
        strCmd = ":LIMIt:1:TYPE?";
        break;
    case 2:
        strCmd = ":LIMIt:2:TYPE?";
        break;
    case 3:
        strCmd = ":LIMIt:3:TYPE?";
        break;
    case 4:
        strCmd = ":LIMIt:4:TYPE?";
        break;
    case 5:
        strCmd = ":LIMIt:5:TYPE?";
        break;
    case 6:
        strCmd = ":LIMIt:6:TYPE?";
        break;
    default:
        strCmd = ":LIMIt:TYPE?";
        break;
    }
    emit sendScpiAndRecv(strCmd);
    return;
}

void RtSa_Remote_Scpi::DeleteLimitLine(qint32 LimitID)
{
    QString strCmd;
    switch (LimitID)
    {
    case 0:
        strCmd = ":LIMIt:DELEte";
        break;
    case 1:
        strCmd = ":LIMIt:1:DELEte";
        break;
    case 2:
        strCmd = ":LIMIt:2:DELEte";
        break;
    case 3:
        strCmd = ":LIMIt:3:DELEte";
        break;
    case 4:
        strCmd = ":LIMIt:4:DELEte";
        break;
    case 5:
        strCmd = ":LIMIt:5:DELEte";
        break;
    case 6:
        strCmd = ":LIMIt:6:DELEte";
        break;
    default:
        strCmd = ":LIMIt:ALL:DELEte";
        break;
    }
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::BuildLimitFromTrace()
{

    QString strCmd  = ":LIMIt:AUTO ";
    emit sendSCPIcmd(strCmd);
}
void RtSa_Remote_Scpi::getLimitDataNum(qint32 LimitID)
{
    QString iVal = QString::number(LimitID);
    QString strCmd  = ":LIMIt:POINt:COUNt? ";
    strCmd += iVal;
    emit sendScpiAndRecv(strCmd);
    return;
}

void RtSa_Remote_Scpi::setLimitCurPointFreq(qreal pData, qint32 curPos, qint32 limitID)
{
    QString iVal1 = QString::number(limitID);
    QString iVal2 = QString::number(curPos);
    QString iVal3 = QString::number(pData);
    QString strCmd  = ":LIMIt:POINt:DATA:FREQuency ";
    strCmd += iVal1 +" " + iVal2 + " " +iVal3;
    emit sendSCPIcmd(strCmd);
    return;
}
void RtSa_Remote_Scpi::getLimitCurPointFreq(qint32 curPos, qint32 limitID)
{
    QString iVal1 = QString::number(limitID);
    QString iVal2 = QString::number(curPos);
    QString strCmd  = ":LIMIt:POINt:DATA:FREQuency?";
    strCmd += iVal1 +" " + iVal2;
    emit sendScpiAndRecv(strCmd);
    return;
}

void RtSa_Remote_Scpi::setLimitCurPointAmpt(qreal pData, qint32 curPos, qint32 limitID)
{
    QString iVal1 = QString::number(limitID);
    QString iVal2 = QString::number(curPos);
    QString iVal3 = QString::number(pData);
    QString strCmd  = ":LIMIt:POINt:DATA:AMPLitude  ";
    strCmd += iVal1 +" " + iVal2 + " " +iVal3;
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::getLimitCurPointAmpt(qint32 curPos, qint32 limitID)
{
    QString iVal1 = QString::number(limitID);
    QString iVal2 = QString::number(curPos);
    QString strCmd  = ":LIMIt:POINt:DATA:AMPLitude?";
    strCmd += iVal1 +" " + iVal2;
    emit sendScpiAndRecv(strCmd);
    return;
}


void RtSa_Remote_Scpi::InsertLimitRow(qint32 limitSelect)
{
    QString iVal = QString::number(limitSelect);
    QString strCmd  = ":LIMIt:INSERT ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
}



void RtSa_Remote_Scpi::setDisplay(qint32 disPlayMode)
{
    QString iVal = QString::number(disPlayMode);
    QString strCmd  = ":DISPlay:VIEW ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
}

void RtSa_Remote_Scpi::getDisplay()
{
    QString strCmd  = ":DISPlay:VIEW?";
    emit sendScpiAndRecv(strCmd);
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-05-29
*/
void RtSa_Remote_Scpi::setPersistenceInfinite(bool isInfinite)
{

    QString iVal = QString::number(isInfinite);
    QString strCmd  = ":DENSity:PERSistence:TIME:INFInite ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::IsPersistenceTimeInfinite()
{
    QString strCmd  = ":DENSity:PERSistence:TIME:INFInite?";
      emit sendScpiAndRecv(strCmd);
    return;
}

/**
* @brief setPersistenceTime
* @param [in] time
* @Author Albert
* @date 2019-04-16
*/
void RtSa_Remote_Scpi::setPersistenceTime(qreal time)
{
    QString iVal = QString::number(time);
    QString strCmd  = ":DENSity:PERSistence:TIME ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
void RtSa_Remote_Scpi::getPersistenceTime()
{
    QString strCmd  = ":DENSity:PERSistence:TIME?";
    emit sendScpiAndRecv(strCmd);
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-06-10
*/
void RtSa_Remote_Scpi::setHighestDensity(quint32 highest)
{
    QString iVal = QString::number(highest);
    QString strCmd  = ":DENSity:HIGHest ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
void RtSa_Remote_Scpi::getHighestDensity()
{
    QString strCmd  = ":DENSity:HIGHest?";
    emit sendScpiAndRecv(strCmd);
    return;

}

/**
* @brief
* @param
* @Author Albert
* @date 2019-06-10
*/
void RtSa_Remote_Scpi::setLowestDensity(quint32 lowest)
{
    QString iVal = QString::number(lowest);
    QString strCmd  = ":DENSity:LOWEst ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::getLowestDensity()
{
    QString strCmd  = ":DENSity:LOWEst?";
    emit sendScpiAndRecv(strCmd);
    return;

}

/**
* @brief
* @param
* @Author Albert
* @date 2019-08-14
*/
void RtSa_Remote_Scpi::setDpxCurve(float curve)
{

    QString iVal = QString::number(curve);
    QString strCmd  = ":DENSity:CURVe ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}

void RtSa_Remote_Scpi::getCurve()
{
    QString strCmd  = ":DENSity:CURVe?";
    emit sendScpiAndRecv(strCmd);
    return;

}
void RtSa_Remote_Scpi::setDensityLevelAjust()
{
    QString strCmd  = ":DENSity:ADJUst";
    emit sendSCPIcmd(strCmd);
    return;
}







