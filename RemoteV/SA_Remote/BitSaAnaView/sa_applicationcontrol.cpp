F/****************************************Copyright (c)****************************************************
**
**                                     INNO Instrument(China) Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                applicationControl.cpp
** Latest Version:           V1.0.0
** Created by:               Johnson
** Created date:             2018/12/05
** Descriptions:             customized controlInterface control interface,be used to get and set parameter,
**                           and control to FPGA
**
*********************************************************************************************************/

#include "sa_applicationcontrol.h"
#include <QFile>
#include <QThread>
#include <QDebug>
#include <QByteArray>

static char* triggerMode[6] = {"FREerun","EXTErnal","VIDEo","PERIodic","RFBUrst","GPS"};

controlInterface::controlInterface(user_variable &UserVariable, user_limit &UserLimit)
{
    globalUserVariable = &UserVariable;
    globalUserLimit    = &UserLimit;
    bitaloth           = new alothforsa(UserVariable);
    pparaSaveLoad      = new paraSaveLoad(UserLimit,UserVariable);
    //Tony 0308 init sweep time
    //setAutoSweepTimeStatus(SA_ON);

    //bZeroRestrainStatusSet   = false;
    bZeroRestrainCalComplete = true;
    bCalStop                 = false;

    bDefaultStatesPreset = false;
}
controlInterface::~controlInterface()
{
    //delete globalUserVariable;
    //delete globalUserLimit;
    delete bitaloth;
    delete pparaSaveLoad;
}
/**
 * @brief setMeasureOff
 * @note  measure off
 */
void controlInterface::setMeasureOff()
{
    if(globalUserVariable->currentMode != SA_SPAN_MODE)
    {
        pparaSaveLoad->paraSave(globalUserVariable->currentMode);

        globalUserVariable->currentMode = SA_SPAN_MODE;

        if(!pparaSaveLoad->getParaStatus(globalUserVariable->currentMode))
        {
            pparaSaveLoad->paraLoad(globalUserVariable->currentMode);
            LoadParamControl();
        }
    }

    /*if(globalUserVariable->currentMode != SA_SPAN_MODE){
        pparaSaveLoad->saveVariable(&gGlobalParam,globalUserVariable->currentMode);
        pparaSaveLoad->loadVariable(&gGlobalParam);
        globalUserVariable->currentMode = SA_SPAN_MODE;

        //Johnson 1127 load Span Mode param and send all the param to FPGA
        LoadParamControl();
        //globalUserLimit->gridAxisCalculatorFunc();//Johnson 130320
    }*/
}

void controlInterface::setChannelPower()
{
    if(globalUserVariable->currentMode != SA_CHNLPOWER_MEASURE_MODE){
        pparaSaveLoad->paraSave(globalUserVariable->currentMode);
        if(globalUserVariable->currentMode == SA_SPAN_MODE)
        {
            globalUserVariable->uIFMode = SA_AUTO_IFMODE;
            emit infoRefresh(SA_INFO_BW,SA_INFO_BW_IF_OUTPUT);
        }

        globalUserVariable->currentMode = SA_CHNLPOWER_MEASURE_MODE;

        if(!pparaSaveLoad->getParaStatus(globalUserVariable->currentMode))
        {
            pparaSaveLoad->paraLoad(globalUserVariable->currentMode);
            LoadParamControl();
        }
        else
        {
            globalUserVariable->gZeroSpanAction = SA_OFF;

            LoadModeParam();

            globalUserVariable->gChannelBandwidth = 2000000LL;
            globalUserVariable->gSpanFreq = 3000000LL;
            setSpan(globalUserVariable->gSpanFreq);
        }
        //globalUserLimit->gridAxisCalculatorFunc();//Johnson 130320
    }
    /*if(globalUserVariable->currentMode != SA_CHNLPOWER_MEASURE_MODE){
        pparaSaveLoad->saveVariable(&gGlobalParam,globalUserVariable->currentMode);
        pparaSaveLoad->loadVariable(&gGlobalParam,SA_CHNLPOWER_MEASURE_MODE);
        globalUserVariable->currentMode = SA_CHNLPOWER_MEASURE_MODE;

        //Johnson 1127 load ChanlPower param and send all the param to FPGA
        LoadParamControl();
        //globalUserLimit->gridAxisCalculatorFunc();//Johnson 130320
    }*/
}
void controlInterface::setACP()
{
    if(globalUserVariable->currentMode != SA_ACP_MEASURE_MODE){
        pparaSaveLoad->paraSave(globalUserVariable->currentMode);
        if(globalUserVariable->currentMode == SA_SPAN_MODE)
        {
            globalUserVariable->uIFMode = SA_AUTO_IFMODE;
            emit infoRefresh(SA_INFO_BW,SA_INFO_BW_IF_OUTPUT);
        }

        globalUserVariable->currentMode = SA_ACP_MEASURE_MODE;

        if(!pparaSaveLoad->getParaStatus(globalUserVariable->currentMode))
        {
            pparaSaveLoad->paraLoad(globalUserVariable->currentMode);
            LoadParamControl();
        }
        else
        {
            globalUserVariable->gZeroSpanAction = SA_OFF;

            LoadModeParam();

            globalUserVariable->gChannelBandwidth = 2000000LL;
            globalUserVariable->gChannelSpacing   = 3000000LL;
            globalUserVariable->gSpanFreq         = 8000000LL;
            setSpan(globalUserVariable->gSpanFreq);
        }
        //globalUserLimit->gridAxisCalculatorFunc();//Johnson 130320
    }
    /*if(globalUserVariable->currentMode != SA_ACP_MEASURE_MODE){
        pparaSaveLoad->saveVariable(&gGlobalParam,globalUserVariable->currentMode);
        pparaSaveLoad->loadVariable(&gGlobalParam,SA_ACP_MEASURE_MODE);
        globalUserVariable->currentMode = SA_ACP_MEASURE_MODE;

        //Johnson 1127 load SA_ACP param and send all the param to FPGA
        LoadParamControl();
        //globalUserLimit->gridAxisCalculatorFunc();//Johnson 130320
    }*/
}
void controlInterface::setOccupiedBW()
{
    if(globalUserVariable->currentMode != SA_OCCUPIED_BW_MEASURE_MODE){
        pparaSaveLoad->paraSave(globalUserVariable->currentMode);

        if(globalUserVariable->currentMode == SA_SPAN_MODE)
        {
            globalUserVariable->uIFMode = SA_AUTO_IFMODE;
            emit infoRefresh(SA_INFO_BW,SA_INFO_BW_IF_OUTPUT);
        }

        globalUserVariable->currentMode = SA_OCCUPIED_BW_MEASURE_MODE;

        if(!pparaSaveLoad->getParaStatus(globalUserVariable->currentMode))
        {
            pparaSaveLoad->paraLoad(globalUserVariable->currentMode);
            LoadParamControl();
        }
        else
        {
            globalUserVariable->gZeroSpanAction = SA_OFF;

            LoadModeParam();
            globalUserVariable->gSpanFreq = 3000000LL;
            setSpan(globalUserVariable->gSpanFreq);
        }
        //globalUserLimit->gridAxisCalculatorFunc();//Johnson 130320
    }
}
void controlInterface::setDemodulation(qint32 Demodu)
{
    if(globalUserVariable->currentMode != SA_DEMODULATION_MODE){
        pparaSaveLoad->paraSave(globalUserVariable->currentMode);

        if(globalUserVariable->currentMode == SA_SPAN_MODE)
        {
            globalUserVariable->uIFMode = SA_AUTO_IFMODE;
            emit infoRefresh(SA_INFO_BW,SA_INFO_BW_IF_OUTPUT);
        }

        globalUserVariable->currentMode = SA_DEMODULATION_MODE;
        //globalUserVariable->gDemodulationType = Demodu;

        if(!pparaSaveLoad->getParaStatus(globalUserVariable->currentMode))
        {
            pparaSaveLoad->paraLoad(globalUserVariable->currentMode);
            LoadParamControl();
        }
        else
        {
            globalUserVariable->gZeroSpanAction = SA_OFF;

            LoadModeParam();
            globalUserVariable->gSpanFreq = 50000000LL;
            setSpan(globalUserVariable->gSpanFreq);
        }
    }
}
void controlInterface::setSpectrumEmissionMask()
{
    //    SA_sm_config_sweep->uTrigSweepFlag = 0;
    //    SA_sm_config_sweep->SweepType = SA_SINGLE;
    //    SA_sm_config_sweep->uMsCompleteFlag = 0;

    if(globalUserVariable->currentMode != SA_SPECTRUM_EMISSION_MASK_MODE){
        pparaSaveLoad->paraSave(globalUserVariable->currentMode);

        if(globalUserVariable->currentMode == SA_SPAN_MODE)
        {
            globalUserVariable->uIFMode = SA_AUTO_IFMODE;
            emit infoRefresh(SA_INFO_BW,SA_INFO_BW_IF_OUTPUT);
        }
        globalUserVariable->currentMode = SA_SPECTRUM_EMISSION_MASK_MODE;

        if(!pparaSaveLoad->getParaStatus(globalUserVariable->currentMode))
        {

            pparaSaveLoad->paraLoad(globalUserVariable->currentMode);
            //globalUserVariable->gAutoRbw = SA_MANUAL;
            LoadParamControl();
        }
        else
        {
            globalUserVariable->gZeroSpanAction = SA_OFF;

            LoadModeParam();
            //      globalUserVariable->gCenterFreq  = 1800000000LL;
            //Tony 0408  frequency 30 MHz
            //      globalUserVariable->gSpanFreq = 30000000LL;//50000000LL;
            //setAutoRbwStatus(SA_MANUAL);
            //setCenterFreq(m_user_variable->gCenterFreq);
            //setSpan(globalUserVariable->gSpanFreq);

        }

        //Johnson 1127 load Occupied SA_BW param and send all the param to FPGA

        //globalUserLimit->gridAxisCalculatorFunc();//Johnson 130320
    }
    /*if(globalUserVariable->currentMode != SA_SPECTRUM_EMISSION_MASK_MODE){
        pparaSaveLoad->saveVariable(&gGlobalParam,globalUserVariable->currentMode);
        pparaSaveLoad->loadVariable(&gGlobalParam,SA_SPECTRUM_EMISSION_MASK_MODE);
        globalUserVariable->currentMode = SA_SPECTRUM_EMISSION_MASK_MODE;

        //Johnson 1127 load Occupied SA_BW param and send all the param to FPGA
        LoadParamControl();
        //globalUserLimit->gridAxisCalculatorFunc();//Johnson 130320
    }*/
}
void controlInterface::setMultiACP()
{
    if(globalUserVariable->currentMode != SA_MULTI_ACP_MODE){
        pparaSaveLoad->paraSave(globalUserVariable->currentMode);

        if(globalUserVariable->currentMode == SA_SPAN_MODE)
        {
            globalUserVariable->uIFMode = SA_AUTO_IFMODE;
            emit infoRefresh(SA_INFO_BW,SA_INFO_BW_IF_OUTPUT);
        }

        globalUserVariable->currentMode = SA_MULTI_ACP_MODE;

        if(!pparaSaveLoad->getParaStatus(globalUserVariable->currentMode))
        {
            pparaSaveLoad->paraLoad(globalUserVariable->currentMode);
            LoadParamControl();
        }
        else
        {
            globalUserVariable->gZeroSpanAction = SA_OFF;

            LoadModeParam();

            globalUserVariable->gChannelBandwidth = 2000000LL;
            globalUserVariable->gChannelSpacing   = 3000000LL;
            globalUserVariable->gSpanFreq         = 14000000LL;
            setSpan(globalUserVariable->gSpanFreq);
        }
    }
    /*if(globalUserVariable->currentMode != SA_MULTI_ACP_MODE){
        pparaSaveLoad->saveVariable(&gGlobalParam,globalUserVariable->currentMode);
        pparaSaveLoad->loadVariable(&gGlobalParam,SA_MULTI_ACP_MODE);
        globalUserVariable->currentMode = SA_MULTI_ACP_MODE;

        //Johnson 1127 load Occupied SA_BW param and send all the param to FPGA
        LoadParamControl();
        //globalUserLimit->gridAxisCalculatorFunc();//Johnson 130320
    }*/
}
void controlInterface::setSpuriousEmissionMask()
{
    //SA_sm_config_sweep->uTrigSweepFlag = 0;
    //    SA_sm_config_sweep->SweepType = SA_SINGLE;
    //    SA_sm_config_sweep->uMsCompleteFlag = 0;

    if(globalUserVariable->currentMode != SA_SPURIOUS_EMISSION_MASK_MODE)
    {
        pparaSaveLoad->paraSave(globalUserVariable->currentMode);

        if(globalUserVariable->currentMode == SA_SPAN_MODE)
        {
            globalUserVariable->uIFMode = SA_AUTO_IFMODE;
            emit infoRefresh(SA_INFO_BW,SA_INFO_BW_IF_OUTPUT);
        }

        globalUserVariable->currentMode = SA_SPURIOUS_EMISSION_MASK_MODE;
        //SA_sm_config_sweep->uSweepCompleteFlag = 1;

        if(!pparaSaveLoad->getParaStatus(globalUserVariable->currentMode))
        {
            pparaSaveLoad->paraLoad(globalUserVariable->currentMode);
            LoadParamControl();
        }
        else
        {
            globalUserVariable->gZeroSpanAction = SA_OFF;

            LoadModeParam();
        }
    }
    /*if(globalUserVariable->currentMode != SA_SPURIOUS_EMISSION_MASK_MODE){
        pparaSaveLoad->saveVariable(&gGlobalParam,globalUserVariable->currentMode);
        pparaSaveLoad->loadVariable(&gGlobalParam,SA_SPURIOUS_EMISSION_MASK_MODE);
        globalUserVariable->currentMode = SA_SPURIOUS_EMISSION_MASK_MODE;

        //Johnson 1127 load Occupied SA_BW param and send all the param to FPGA
        LoadParamControl();
        //globalUserLimit->gridAxisCalculatorFunc();//Johnson 130320
    }*/
}
void controlInterface::setFieldStrength()
{
    if(globalUserVariable->currentMode != SA_FIELD_STRENGTH_MODE){
        pparaSaveLoad->paraSave(globalUserVariable->currentMode);

        if(globalUserVariable->currentMode == SA_SPAN_MODE)
        {
            globalUserVariable->uIFMode = SA_AUTO_IFMODE;
            emit infoRefresh(SA_INFO_BW,SA_INFO_BW_IF_OUTPUT);
        }

        globalUserVariable->currentMode = SA_FIELD_STRENGTH_MODE;

        if(!pparaSaveLoad->getParaStatus(globalUserVariable->currentMode))
        {
            pparaSaveLoad->paraLoad(globalUserVariable->currentMode);
            LoadParamControl();
        }
        else
        {
            globalUserVariable->gZeroSpanAction = SA_OFF;

            globalUserVariable->gSpanFreq = 50000000LL;
            setSpan(globalUserVariable->gSpanFreq);
        }
    }
    /*if(globalUserVariable->currentMode != SA_FIELD_STRENGTH_MODE){
        pparaSaveLoad->saveVariable(&gGlobalParam,globalUserVariable->currentMode);
        pparaSaveLoad->loadVariable(&gGlobalParam,SA_FIELD_STRENGTH_MODE);
        globalUserVariable->currentMode = SA_FIELD_STRENGTH_MODE;

        //Johnson 1127 load Occupied SA_BW param and send all the param to FPGA
        LoadParamControl();
        //globalUserLimit->gridAxisCalculatorFunc();//Johnson 130320
    }*/
}
void controlInterface::setDemodulationType(qint32 demodulationType)
{
    //globalUserVariable->gDemodulationType = demodulationType;
}

/**
 * @brief controlInterface::SetMeasureItems
 * @param imea
 */
void controlInterface::SetMeasureItems(qint32 imea)
{
    if(imea < 0 || imea > 8) return;
#if USABLE
    SA_sm_config_sweep->uMsCompleteFlag = 0;
#endif

    QString iVal = QString::number(imea);
    QString strCmd = ":MEASure:MODE ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    this->blockSignals(true);
    globalUserVariable->gIgnoreLimit = 1;
    globalUserVariable->gAutoRepeat = 0;
    switch(imea)
    {
    case SA_SWEPT_SA:
        setMeasureOff();
        break;
    case SA_CHANNEL_POWER:
        setChannelPower();
        break;
    case SA_OCCUPIED_BW:
        setOccupiedBW();
        break;
    case SA_SPECTRUM_EMISSION_MASK:
        setSpectrumEmissionMask();
        setMeasureStatus(SA_ON);
        break;
    case SA_ACP:
        setACP();
        break;
    case SA_MULTI_ACP:
        setMultiACP();
        break;
    case SA_SPURIOUS_EMISSION_MASK:
        setSpuriousEmissionMask();
        setMeasureStatus(SA_ON);
        break;
    case SA_FIELD_STRENGTH:
        setFieldStrength();
        break;
    case SA_DEMODULATION:
        //setDemodulation(globalUserVariable->gDemodulationType);
        break;
    default:
        return;
        break;
    }
    globalUserVariable->gIgnoreLimit = 0;
    globalUserVariable->gAutoRepeat = 1;
    this->blockSignals(false);
    emit signalModeChange();
    return;
}

/**
 * @brief controlInterface::GetMeasureItems
 */
qint32 controlInterface::GetMeasureItems()
{
    return globalUserVariable->currentMode;
}
/**
 * @brief setChannelPower_ChannelBW
 * @param uChBw quint64
 * @note  set bandwidth of channel power
 */
void controlInterface::setChannelPower_ChannelBW(quint64 uChBw)
{
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gChannelBandwidth == uChBw) return;
    }
    if(globalUserVariable->currentMode != SA_CHNLPOWER_MEASURE_MODE) return;
    globalUserVariable->gChannelBandwidth = uChBw > globalUserVariable->gSpanFreq ? globalUserVariable->gSpanFreq : uChBw;

    //control FPGA

    QString iVal = QString::number(globalUserVariable->gChannelBandwidth);
    QString strCmd = ":CHPOwer:CHBAndwidth ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
}
/**
 * @brief getChannelPower_ChannelBW
 * @return the channel bandwidth of channel power
 */
quint64 controlInterface::getChannelPower_ChannelBW()
{
    return globalUserVariable->gChannelBandwidth;
}
/**
 * @brief getChannelPower
 * @return the channel power of channel power
 */
qreal controlInterface::getChannelPower()
{
    return globalUserVariable->dPowerValue;
}
/**
 * @brief setACP_ChannelBW
 * @param uChBw
 * @param currentMode
 */
void controlInterface::setACP_ChannelBW(quint64 uChBw)
{
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gChannelBandwidth == uChBw) return;
    }
    if(globalUserVariable->currentMode != SA_ACP_MEASURE_MODE && globalUserVariable->currentMode != SA_MULTI_ACP_MODE) return;
    globalUserVariable->gChannelBandwidth = uChBw > globalUserVariable->gSpanFreq ? globalUserVariable->gSpanFreq : uChBw;

    QString iVal = QString::number(globalUserVariable->gChannelBandwidth);
    QString strCmd = ":ACPOwer:CHBAndwidth ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    //save and load para,and control FPGA
}
/**
 * @brief setACP_ChannelSP
 * @param uChSp
 * @param currentMode
 */
void controlInterface::setACP_ChannelSP(quint64 uChSp)
{
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gChannelSpacing == uChSp) return;
    }
    if(globalUserVariable->currentMode != SA_ACP_MEASURE_MODE && globalUserVariable->currentMode != SA_MULTI_ACP_MODE) return;
    globalUserVariable->gChannelSpacing = uChSp>globalUserVariable->gSpanFreq?globalUserVariable->gSpanFreq:uChSp;

    QString iVal = QString::number(globalUserVariable->gChannelSpacing);
    QString strCmd = ":ACPOwer:CHSPace ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    //save and load para,and control FPGA
}
/**
 * @brief getACP_ChannelBW
 * @return
 */
quint64 controlInterface::getACP_ChannelBW()
{
    return globalUserVariable->gChannelBandwidth;
}
/**
 * @brief getACP_ChannelSP
 * @return
 */
quint64 controlInterface::getACP_ChannelSP()
{
    return globalUserVariable->gChannelSpacing;
}
/**
 * @brief getLeftACP_ChannelPower
 * @return
 */
qreal controlInterface::getLeftACP_ChannelPower()
{
    return globalUserVariable->dPowerValue_ACPL;
}
/**
 * @brief getMidACP_ChannelPower
 * @return
 */
qreal controlInterface::getMidACP_ChannelPower()
{
    return globalUserVariable->dPowerValue_ACPM;
}
/**
 * @brief getRightACP_ChannelPower
 * @return
 */
qreal controlInterface::getRightACP_ChannelPower()
{
    return globalUserVariable->dPowerValue_ACPR;
}
/**
 * @brief getLeftACP_ChannelDbc
 * @return
 */
qreal controlInterface::getLeftACP_ChannelDbc()
{
    qreal dLeftACP_ChannelDbc = 0.;
    dLeftACP_ChannelDbc = globalUserVariable->dPowerValue_ACPL - globalUserVariable->dPowerValue_ACPM;
    return dLeftACP_ChannelDbc;
}
/**
 * @brief getRightACP_ChannelDbc
 * @return
 */
qreal controlInterface::getRightACP_ChannelDbc()
{
    qreal dRightACP_ChannelDbc = 0.;
    dRightACP_ChannelDbc = globalUserVariable->dPowerValue_ACPR - globalUserVariable->dPowerValue_ACPM;
    return dRightACP_ChannelDbc;
}
/**
 * @brief getDemodulation
 * @return
 */
qint32 controlInterface::getDemodulation()
{
    return 0;//globalUserVariable->gDemodulationType;
}
/**
 * @brief setOccupiedBW_OccBW
 * @param dOccBw
 * @param currentMode
 */
void controlInterface::setOccupiedBW_OccBW(qreal dOccBw)
{
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gOccupied_BW == dOccBw) return;
    }
    if(globalUserVariable->currentMode != SA_OCCUPIED_BW_MEASURE_MODE) return;

    if(dOccBw - 10. < 0.) globalUserVariable->gOccupied_BW = 10.;
    else if(dOccBw - 99.99 > 0.) globalUserVariable->gOccupied_BW = 99.99;
    else if(dOccBw - 10. >= 0. && dOccBw - 99.99 <= 0.) {
        globalUserVariable->gOccupied_BW = dOccBw;
    }

    QString iVal = QString::number(globalUserVariable->gOccupied_BW);
    QString strCmd = ":OBWIdth:PERCent ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    //save and load para,and control FPGA
}
/**
 * @brief setOccupiedBW_XdB
 * @param dXdb
 * @param currentMode
 */
void controlInterface::setOccupiedBW_XdB(qreal dXdb)
{
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gXdB == dXdb) return;
    }
    if(globalUserVariable->currentMode != SA_OCCUPIED_BW_MEASURE_MODE) return;

    if(dXdb - XDB_MIN < 0.) {
        globalUserVariable->gXdB = XDB_MIN;
    }
    else if(dXdb - XDB_MAX > 0.) {
        globalUserVariable->gXdB = XDB_MAX;
    }
    else globalUserVariable->gXdB = dXdb;

    QString iVal = QString::number(globalUserVariable->gXdB);
    QString strCmd = ":OBWidth:XDB ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    //save and load para,and control FPGA
}
/**
 * @brief getXdB_OccupiedBW
 * @return
 */
qreal controlInterface::getXdB_OccupiedBW()
{
    return globalUserVariable->gXdB;
}
/**
 * @brief getOccBW_OccupiedBW
 * @return
 */
qreal controlInterface::getOccBW_OccupiedBW()
{
    return globalUserVariable->gOccupied_BW;
}
/**
 * @brief getOccupiedBW_XdB
 * @return
 */
quint64 controlInterface::getOccupiedBW_XdB()
{
    return globalUserVariable->uXdBBW;
}
/**
 * @brief getOccupiedBW_OccBW
 * @return
 */
quint64 controlInterface::getOccupiedBW_OccBW()
{
    return globalUserVariable->uOccupiedBW;
}
/**
 * @brief getTotalPower
 * @return
 */
qreal controlInterface::getTotalPower()
{
    return globalUserVariable->dTotalPower;
}
/**
 * @brief setSpectrumEMDisplay
 * @return
 */
void controlInterface::setSpecEMDisplay(qint32 mode)
{
    if(globalUserVariable->gAutoRepeat)
    {
        //if(globalUserVariable->gSpecEMDisplay == mode) return;
    }
    if(mode < 0 || mode > 2) return;
    globalUserVariable->gSpecEMDisplay = mode;

    QString iVal = QString::number(globalUserVariable->gSpecEMDisplay);
    QString strCmd = ":SEM:VIEWtype ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
/**
 * @brief getSpectrumEMDisplay
 * @return
 */
qint32 controlInterface::getSpecEMDisplay()
{
    return globalUserVariable->gSpecEMDisplay;
}
/**
 * @brief setSpectrumEMRefType
 * @return
 */
void controlInterface::setSpecEMRefType(qint32 type)
{
    if(globalUserVariable->gAutoRepeat)
    {
        //if(globalUserVariable->gSpecEMRefType == type) return;
    }
    if(type < 0 || type > 2) return;
    globalUserVariable->gSpecEMRefType = type;

    QString iVal = QString::number(globalUserVariable->gSpecEMRefType);
    QString strCmd = ":SEM:REFErence ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
/**
 * @brief getSpectrumEMRefType
 * @return
 */
qint32 controlInterface::getSpecEMRefType()
{
    return globalUserVariable->gSpecEMRefType;
}
/**
 * @brief setInteBW  set integrated bandwidth
 * @return
 */
void controlInterface::setInteBW(qreal mBandWidth)
{
    if(globalUserVariable->gAutoRepeat)
    {
        //if(globalUserVariable->gSpecEMInteBW == mBandWidth) return;
    }
    globalUserVariable->gSpecEMInteBW = mBandWidth;
    return;
}
/**
 * @brief getInteBW
 * @return
 */
qreal controlInterface::getInteBW()
{
    return globalUserVariable->gSpecEMInteBW;
}
/**
 * @brief setSpecEMTotalPowerRef
 * @return
 */
void controlInterface::setSpecEMTotalPowerRef(qreal mPower)
{
    if(globalUserVariable->gAutoRepeat)
    {
        //if(globalUserVariable->gSpecEMTotalPwrRef == mPower) return;
    }
    globalUserVariable->gSpecEMTotalPwrRef = mPower;
    return ;
}
/**
 * @brief getSpecEMTotalPowerRef
 * @return
 */
qreal controlInterface::getSpecEMTotalPowerRef()
{
    return globalUserVariable->gSpecEMTotalPwrRef;
}
/**
 * @brief setSpecEMPSDRef
 * @return
 */
void controlInterface::setSpecEMPSDRef(qreal mPSD)
{
    if(globalUserVariable->gAutoRepeat)
    {
        //if(globalUserVariable->gSpecEMPSDRef == mPSD) return;
    }
    globalUserVariable->gSpecEMPSDRef = mPSD;
    return;
}
/**
 * @brief getSpecEMPSDRef
 * @return
 */
qreal controlInterface::getSpecEMPSDRef()
{
    return globalUserVariable->gSpecEMPSDRef;
}
/**
 * @brief setSpecEMPeakRef
 * @return
 */
void controlInterface::setSpecEMPeakRef(qreal mPeak)
{
    if(globalUserVariable->gAutoRepeat)
    {
        //if(globalUserVariable->gSpecEMPeakRef == mPeak) return;
    }
    globalUserVariable->gSpecEMPeakRef = mPeak;
    return;
}
/**
 * @brief getSpecEMPeakRef
 * @return
 */
qreal controlInterface::getSpecEMPeakRef()
{
    return globalUserVariable->gSpecEMPeakRef;
}

/**
 * @brief setSpecEMViewStatus
 * @return
 */
void controlInterface::setSpecEMViewStatus(qint32 OffsetIndex,qint32 status)
{
    if(globalUserVariable->gAutoRepeat)
    {
        //if(globalUserVariable->gSpecEMViewStatus[OffsetIndex] == status) return;
    }
    globalUserVariable->gSpecEMViewStatus[OffsetIndex] = status;
    return;
}
/**
 * @brief getSpecEMViewStatus
 * @return
 */
qint32 controlInterface::getSpecEMViewStatus(qint32 OffsetIndex)
{
    return globalUserVariable->gSpecEMViewStatus[OffsetIndex];
}
/**
 * @brief setMeasureStatus
 * @return
 */
void controlInterface::setMeasureStatus(qint32 mStatus)
{
    //if(globalUserVariable->gAutoRepeat)
    //{
    //   if(globalUserVariable->gMeasureStatus == mStatus) return;
    //}
    if(mStatus == SA_ON)
    {
#if 0
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE)
        {
            //first setup
            bParaLoad = true;
            blockSignals(true);
            globalUserVariable->gIgnoreLimit = 1;
            setAutoRbwStatus(SA_MANUAL);
            setCenterFreq(1800000000LL);
            setSpan(30000000LL);
            setAutoSweepTimeStatus(SA_MANUAL);
            setRbwValue(300000);
            setVbwValue(300000);
            setSweepTime(120);
            globalUserVariable->gIgnoreLimit = 0;
            blockSignals(false);
            bParaLoad = false;
            SA_Set_config_flag(IXT_SA_ConfigSweep,IXS_SA_PARALOAD);
        }else if(globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE)
        {
            qint32 freqIndex = -1;
            qreal mRBW,mVBW,mStopFreq,mStartFreq,mSweepTime,mAtten,mCenter,span;
            quint64 mSpan;
            for(qint32 i = 0;i < SA_SPUREM_RANGE_CNT;i++)
            {
                if(globalUserVariable->gSpurEMViewStatus[i] == SA_ON)
                {
                    freqIndex = i;
                    break;
                }
            }
            if(freqIndex>=0)
            {
                mStopFreq = globalUserVariable->gSpurEMPara[freqIndex].stopFreq;
                mStartFreq = globalUserVariable->gSpurEMPara[freqIndex].startFreq;
                mSweepTime = globalUserVariable->gSpurEMPara[freqIndex].SweepTime;
                if(mSweepTime < 100)
                {
                    mSweepTime = 100;
                }

                mRBW = globalUserVariable->gSpurEMPara[freqIndex].RBW;
                mVBW = globalUserVariable->gSpurEMPara[freqIndex].VBW;
                mAtten = globalUserVariable->gSpurEMPara[freqIndex].Atten;

                span = mStopFreq - mStartFreq;
                mSpan = span;
                if((mSpan + 0.1) < span)
                {
                    mSpan++;
                }

                mCenter = (mStartFreq + mStopFreq)/2;

                blockSignals(true);
                globalUserVariable->gSpurEMCurDrawRangeIndex = 0;
                globalUserVariable->gIgnoreLimit = 1;
                bParaLoad = true;
                setAttenStatus(SA_MANUAL);
                setAutoRbwStatus(SA_MANUAL);

                setRbwValue(mRBW);
                setCenterFreq(mCenter);
                setSpan(mSpan);
                setSweepTime(mSweepTime);
                setAttenValue(mAtten);
                bParaLoad = false;
                globalUserVariable->gIgnoreLimit = 0;
                blockSignals(false);
                SA_Set_config_flag(IXT_SA_ConfigSweep,IXS_SA_PARALOAD);
            }

        }
#endif
        globalUserVariable->gMsFirstFlag = 1;
        globalUserVariable->gAverageNo[0] = 0;
        globalUserVariable->greAvager[0] = 1;
        //SA_sm_config_sweep->uSweepCompleteFlag = 1;
        //globalUserVariable->gMsComplete = 1;
        globalUserVariable->SecondaryAction = SA_NOT_USE;
    }else
    {
        //Tony 190624
        //SA_sm_config_sweep->uMsCompleteFlag = 1;
    }
    globalUserVariable->gMeasureStatus = mStatus;
    return;
}
/**
 * @brief getSpurMeasureStatus
 * @return
 */
qint32 controlInterface::getSpurMeasureStatus()
{
    return globalUserVariable->gMeasureStatus;
}

/**
 * @brief setSpurReportType
 * @return
 */
void controlInterface::setSpurReportType(qint32 mType)
{
    if(globalUserVariable->gAutoRepeat)
    {
        //if(globalUserVariable->gSpurEMReportType == mType) return;
    }
    if(mType<0 || mType >1)
    {
        return;
    }
    globalUserVariable->gSpurEMReportType = mType;
    //refresh current spur index
    //refresh current spur index
    qint32 mSpurCnt = 0,mCurRangeIndex,RangeSpurCnt;
    mCurRangeIndex = globalUserVariable->gSpurEMCurDrawRangeIndex;
    for(qint32 i = 0;i<=mCurRangeIndex;i++)
    {
        if(globalUserVariable->gSpurEMViewStatus[i]==SA_OFF)
            continue;
        RangeSpurCnt = globalUserVariable->gSpurEMSpurCnt[i];
        if(getSpurReportType()==SA_SPUREM_REPORT_ALL)
        {
            for(qint32 j=0;j<RangeSpurCnt;j++)
            {
                mSpurCnt ++ ;
            }
        }else
        {
            for(qint32 j=0;j<RangeSpurCnt;j++)
            {
                if(globalUserVariable->gSpurEMSpur[i * SA_SPUREM_SPUR_CNT + j].testValue == SA_FAIL)
                {
                    mSpurCnt ++ ;
                }
            }
        }
    }
    globalUserVariable->gSpurEMTotalSpurCnt = mSpurCnt;
    globalUserVariable->gSpurEMCurSpurIndex = mSpurCnt-1;

    QString iVal = QString::number(globalUserVariable->gSpurEMReportType);
    QString strCmd = ":SPURious:REPOrt:MODE ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
/**
 * @brief getSpurReportType
 * @return
 */
qint32 controlInterface::getSpurReportType()
{
    return globalUserVariable->gSpurEMReportType;
}
/**
 * @brief setSpurEMAveType
 * @return
 */
void controlInterface::setSpurEMAveType(qint32 mType)
{
    if(globalUserVariable->gAutoRepeat)
    {
        //if(globalUserVariable->gSpurEMAveType == mType) return;
    }
    if(mType < 0 || mType > 1) return;
    globalUserVariable->gSpurEMAveType = mType;
    if(mType == SA_SPUREM_AVE_REPEAT)
    {
        globalUserVariable->gMeasureStatus = SA_ON;
    }

    QString iVal = QString::number(globalUserVariable->gSpurEMAveType);
    QString strCmd = ":SPURious:AVERage:TYPE ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
/**
 * @brief getSpurEMAveType
 * @return
 */
qint32 controlInterface::getSpurEMAveType()
{
    return globalUserVariable->gSpurEMAveType;
}
/**
 * @brief setSpurEMTableType
 * @param mType
 * @return
 */
void controlInterface::setSpurEMTableType(qint32 mType)
{
    if(globalUserVariable->gAutoRepeat)
    {
        //if(globalUserVariable->gSpurEMTableMode == mType) return;
    }
    if(mType < 0 || mType > 2) return;
    globalUserVariable->gSpurEMTableMode = mType;

    QString iVal = QString::number(mType);
    QString strCmd = ":SPURious:DISPlay:TYPE ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
/**
 * @brief getSpurEMTableType
 * @return table type
 **/
qint32 controlInterface::getSpurEMTableType()
{
    return globalUserVariable->gSpurEMTableMode;
}
/**
 * @brief setSpurEMCurRangeIndex
 * @param curRangeIndex
 * @return
 **/
void controlInterface::setSpurEMCurRangeIndex(qint32 curRangeIndex)
{
    if(globalUserVariable->gAutoRepeat)
    {
        //if(globalUserVariable->gSpurEMCurRangeIndex == curRangeIndex) return;
    }
    qint32 cnt=0;
    if(curRangeIndex<0)
    {
        curRangeIndex = 0;
    }else if(curRangeIndex >=SA_SPUREM_RANGE_CNT)
    {
        curRangeIndex = SA_SPUREM_RANGE_CNT -1;
    }
    globalUserVariable->gSpurEMCurRangeIndex = curRangeIndex;

    QString iVal = QString::number(globalUserVariable->gSpurEMCurRangeIndex);
    QString strCmd = ":SPURious:RANGe:SELEct ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
/**
 * @brief getSpurEMCurRangeIndex
 * @return curRangeIndex
 **/
qint32 controlInterface::getSpurEMCurRangeIndex()
{
    return globalUserVariable->gSpurEMCurRangeIndex;
}

/**
 * @brief setSpurEMCurSpurIndex
 * @param curSpurIndex
 * @return
 **/
void controlInterface::setSpurEMCurSpurIndex(qint32 curSpurIndex)
{
    if(globalUserVariable->gAutoRepeat)
    {
        //if(globalUserVariable->gSpurEMCurSpurIndex == curSpurIndex) return;
    }
    qint32 curRangeIndex,cnt=0;
    if(curSpurIndex<0)
    {
        if(globalUserVariable->gSpurEMTotalSpurCnt)
        {
            curSpurIndex = 0;
        }else
        {
            curSpurIndex = -1;
        }
    }else if(curSpurIndex >=globalUserVariable->gSpurEMTotalSpurCnt)
    {
        curSpurIndex = globalUserVariable->gSpurEMTotalSpurCnt -1;
    }
    globalUserVariable->gSpurEMCurSpurIndex = curSpurIndex;

    QString iVal = QString::number(globalUserVariable->gSpurEMCurSpurIndex);
    QString strCmd = ":SPURious:SPUR ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
/**
 * @brief getSpurEMCurSpurIndex
 * @return curSpurIndex
 **/
qint32 controlInterface::getSpurEMCurSpurIndex()
{
    return globalUserVariable->gSpurEMCurSpurIndex;
}

/**
 * @brief setSpurEMDisplay
 * @param status,curRangeIndex
 * @return
 **/
void controlInterface::setSpurEMDisplay(qint32 status, qint32 curRangeIndex)
{
    if(curRangeIndex < 0 ||curRangeIndex >= SPUR_EM_DATE_MAX)
    {
        curRangeIndex = globalUserVariable->gSpurEMCurRangeIndex;
    }
    globalUserVariable->gSpurEMViewStatus[curRangeIndex] = status;

    //refresh current spur index
    qint32 mSpurCnt = 0,mCurRangeIndex,RangeSpurCnt;
    mCurRangeIndex = globalUserVariable->gSpurEMCurDrawRangeIndex;
    for(qint32 i = 0;i<=mCurRangeIndex;i++)
    {
        if(globalUserVariable->gSpurEMViewStatus[i]==SA_OFF)
            continue;
        RangeSpurCnt = globalUserVariable->gSpurEMSpurCnt[i];
        if(getSpurReportType()==SA_SPUREM_REPORT_ALL)
        {
            for(qint32 j=0;j<RangeSpurCnt;j++)
            {
                mSpurCnt ++ ;
            }
        }else
        {
            for(qint32 j=0;j<RangeSpurCnt;j++)
            {
                if(globalUserVariable->gSpurEMSpur[i * SA_SPUREM_SPUR_CNT + j].testValue == SA_FAIL)
                {
                    mSpurCnt ++ ;
                }
            }
        }
    }
    globalUserVariable->gSpurEMTotalSpurCnt = mSpurCnt;
    globalUserVariable->gSpurEMCurSpurIndex = mSpurCnt-1;
    //   globalUserVariable->gMsFirstFlag = 1;

    QString iVal = QString::number(status);
    QString strCmd = ":SPURious:RANGe:STATe ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
/**
 * @brief getSpurEMDisplay
 * @param curRangeIndex
 * @return status
 **/
qint32 controlInterface::getSpurEMDisplay(qint32 curRangeIndex)
{
    if(curRangeIndex < 0 ||curRangeIndex >= SPUR_EM_DATE_MAX)
    {
        curRangeIndex = globalUserVariable->gSpurEMCurRangeIndex;
    }
    return globalUserVariable->gSpurEMViewStatus[curRangeIndex];
}
/**
 * @brief setSpurEMstartFreq
 * @param freq,curRangeIndex
 * @return
 **/
void controlInterface::setSpurEMstartFreq(qreal freq,qint32 curRangeIndex)
{
    qreal value;
    if(curRangeIndex < 0 ||curRangeIndex >= SPUR_EM_DATE_MAX)
    {
        curRangeIndex = globalUserVariable->gSpurEMCurRangeIndex;
    }

    value = (qreal)freq - globalUserVariable->gfreqOffset;
    if(value < SPEC_FREQ_MIN)
    {
        value = SPEC_FREQ_MIN;
    }
    else if(value > SPEC_FREQ_MAX)
    {
        value = SPEC_FREQ_MAX;
    }
    freq = value;

    globalUserVariable->gSpurEMPara[curRangeIndex].startFreq = freq;
    if(globalUserVariable->gSpurEMPara[curRangeIndex].stopFreq < (freq +10))
    {
        globalUserVariable->gSpurEMPara[curRangeIndex].stopFreq = (freq +10);
    }

    QString iVal = QString::number(freq);
    QString strCmd = ":SPURious:RANGe:FREQuency:STARt ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
/**
 * @brief getSpurEMstartFreq
 * @param curRangeIndex
 * @return freq
 **/
qreal controlInterface::getSpurEMstartFreq(qint32 curRangeIndex)
{
    if(curRangeIndex < 0 ||curRangeIndex >= SPUR_EM_DATE_MAX)
    {
        curRangeIndex = globalUserVariable->gSpurEMCurRangeIndex;
    }
    return globalUserVariable->gSpurEMPara[curRangeIndex].startFreq + globalUserVariable->gfreqOffset;
}
/**
 * @brief setSpurEMstopFreq
 * @param freq,curRangeIndex
 * @return
 **/
void controlInterface::setSpurEMstopFreq(qreal freq,qint32 curRangeIndex)
{
    qreal value;
    if(curRangeIndex < 0 ||curRangeIndex >= SPUR_EM_DATE_MAX)
    {
        curRangeIndex = globalUserVariable->gSpurEMCurRangeIndex;
    }

    value = (qreal)freq - globalUserVariable->gfreqOffset;
    if(value < SPEC_FREQ_MIN)
    {
        value = SPEC_FREQ_MIN;
    }
    else if(value > SPEC_FREQ_MAX)
    {
        value = SPEC_FREQ_MAX;
    }
    freq = value;

    globalUserVariable->gSpurEMPara[curRangeIndex].stopFreq = freq;
    if(globalUserVariable->gSpurEMPara[curRangeIndex].startFreq > (freq -10))
    {
        globalUserVariable->gSpurEMPara[curRangeIndex].startFreq = (freq -10);
    }

    QString iVal = QString::number(freq);
    QString strCmd = ":SPURious:RANGe:FREQuency:STOP ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
/**
 * @brief getSpurEMstopFreq
 * @param curRangeIndex
 * @return freq
 **/
qreal controlInterface::getSpurEMstopFreq(qint32 curRangeIndex)
{
    if(curRangeIndex < 0 ||curRangeIndex >= SPUR_EM_DATE_MAX)
    {
        curRangeIndex = globalUserVariable->gSpurEMCurRangeIndex;
    }
    return globalUserVariable->gSpurEMPara[curRangeIndex].stopFreq + globalUserVariable->gfreqOffset;
}
/**
 * @brief setSpurEMRBW
 * @param mRbw,curRangeIndex
 * @return
 **/
void controlInterface::setSpurEMRBW(qreal mRbw,qint32 curRangeIndex)
{
    if(curRangeIndex < 0 ||curRangeIndex >= SPUR_EM_DATE_MAX)
    {
        curRangeIndex = globalUserVariable->gSpurEMCurRangeIndex;
    }
    globalUserVariable->gSpurEMPara[curRangeIndex].RBW = mRbw;

    QString iVal = QString::number(mRbw);
    QString strCmd = ":SPURious:RANGe:RBW ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
/**
 * @brief getSpurEMRBW
 * @param curRangeIndex
 * @returnm Rbw
 **/
qreal controlInterface::getSpurEMRBW(qint32 curRangeIndex)
{
    if(curRangeIndex < 0 ||curRangeIndex >= SPUR_EM_DATE_MAX)
    {
        curRangeIndex = globalUserVariable->gSpurEMCurRangeIndex;
    }
    return globalUserVariable->gSpurEMPara[curRangeIndex].RBW;
}
/**
 * @brief setSpurEMVBW
 * @param mVbw,curRangeIndex
 * @return
 **/
void controlInterface::setSpurEMVBW(qreal mVbw,qint32 curRangeIndex)
{
    if(curRangeIndex < 0 ||curRangeIndex >= SPUR_EM_DATE_MAX)
    {
        curRangeIndex = globalUserVariable->gSpurEMCurRangeIndex;
    }
    globalUserVariable->gSpurEMPara[curRangeIndex].VBW = mVbw;

    QString iVal = QString::number(mVbw);
    QString strCmd = ":SPURious:RANGe:VBW ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
/**
 * @brief getSpurEMVBW
 * @param curRangeIndex
 * @return mVbw
 **/
qreal controlInterface::getSpurEMVBW(qint32 curRangeIndex)
{
    if(curRangeIndex < 0 ||curRangeIndex >= SPUR_EM_DATE_MAX)
    {
        curRangeIndex = globalUserVariable->gSpurEMCurRangeIndex;
    }
    return globalUserVariable->gSpurEMPara[curRangeIndex].VBW;
}
/**
 * @brief setSpurEMSweepTime
 * @param mSwTime,curRangeIndex
 * @return
 **/
void controlInterface::setSpurEMSweepTime(qreal mSwTime,qint32 curRangeIndex)
{
    if(curRangeIndex < 0 ||curRangeIndex >= SPUR_EM_DATE_MAX)
    {
        curRangeIndex = globalUserVariable->gSpurEMCurRangeIndex;
    }
    if(mSwTime > SWEEPTIMEMAX)
    {
        mSwTime = SWEEPTIMEMAX;
    }
    globalUserVariable->gSpurEMPara[curRangeIndex].SweepTime = mSwTime;

    QString iVal = QString::number(mSwTime);
    QString strCmd = ":SPURious:RANGe:SWEEp:TIME ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
/**
 * @brief getSpurEMSweepTime
 * @param curRangeIndex
 * @return mSwTime
 **/
qreal controlInterface::getSpurEMSweepTime(qint32 curRangeIndex)
{
    if(curRangeIndex < 0 ||curRangeIndex >= SPUR_EM_DATE_MAX)
    {
        curRangeIndex = globalUserVariable->gSpurEMCurRangeIndex;
    }
    return globalUserVariable->gSpurEMPara[curRangeIndex].SweepTime;
}
/**
 * @brief setSpurEMstartLimit
 * @param mStartLimit,curRangeIndex
 * @return
 **/
void controlInterface::setSpurEMstartLimit(qreal mStartLimit,qint32 curRangeIndex)
{
    if(curRangeIndex < 0 ||curRangeIndex >= SPUR_EM_DATE_MAX)
    {
        curRangeIndex = globalUserVariable->gSpurEMCurRangeIndex;
    }
    if(mStartLimit > SPEC_AMPTD_MAX)
    {
        mStartLimit = SPEC_AMPTD_MAX;
    }
    else if(mStartLimit < SPEC_AMPTD_MIN)
    {
        mStartLimit = SPEC_AMPTD_MIN;
    }
    globalUserVariable->gSpurEMPara[curRangeIndex].startLimit = mStartLimit;

    QString iVal = QString::number(mStartLimit);
    QString strCmd = ":SPURious:RANGe:LIMIt:STARt ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
/**
 * @brief getSpurEMStartLimit
 * @param curRangeIndex
 * @return mStartLimit
 **/
qreal controlInterface::getSpurEMStartLimit(qint32 curRangeIndex)
{
    if(curRangeIndex < 0 ||curRangeIndex >= SPUR_EM_DATE_MAX)
    {
        curRangeIndex = globalUserVariable->gSpurEMCurRangeIndex;
    }

    return globalUserVariable->gSpurEMPara[curRangeIndex].startLimit;
}
/**
 * @brief setSpurEMStopLimit
 * @param mStopLimit,curRangeIndex
 * @return
 **/
void controlInterface::setSpurEMStopLimit(qreal mStopLimit,qint32 curRangeIndex)
{
    if(curRangeIndex < 0 ||curRangeIndex >= SPUR_EM_DATE_MAX)
    {
        curRangeIndex = globalUserVariable->gSpurEMCurRangeIndex;
    }
    if(mStopLimit > SPEC_AMPTD_MAX)
    {
        mStopLimit = SPEC_AMPTD_MAX;
    }
    else if(mStopLimit < SPEC_AMPTD_MIN)
    {
        mStopLimit = SPEC_AMPTD_MIN;
    }
    globalUserVariable->gSpurEMPara[curRangeIndex].stopLimit = mStopLimit;

    QString iVal = QString::number(mStopLimit);
    QString strCmd = ":SPURious:RANGe:LIMIt:STOP ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
/**
 * @brief getSpurEMStopLimit
 * @param curRangeIndex
 * @return mStopLimit
 **/
qreal controlInterface::getSpurEMStopLimit(qint32 curRangeIndex)
{
    if(curRangeIndex < 0 ||curRangeIndex >= SPUR_EM_DATE_MAX)
    {
        curRangeIndex = globalUserVariable->gSpurEMCurRangeIndex;
    }
    return globalUserVariable->gSpurEMPara[curRangeIndex].stopLimit;
}
/**
 * @brief setSpurEMpeakDefi
 * @param mValue,curRangeIndex
 * @return
 **/
void controlInterface::setSpurEMpeakDefi(qreal mValue,qint32 curRangeIndex)
{
    if(curRangeIndex < 0 ||curRangeIndex >= SPUR_EM_DATE_MAX)
    {
        curRangeIndex = globalUserVariable->gSpurEMCurRangeIndex;
    }

    if(mValue < 0)
    {
        mValue = 0;
    }
    else if(mValue > (SPEC_AMPTD_MAX - SPEC_AMPTD_MIN))
    {
        mValue = SPEC_AMPTD_MAX - SPEC_AMPTD_MIN;
    }

    globalUserVariable->gSpurEMPara[curRangeIndex].peakDefi = mValue;

    QString iVal = QString::number(mValue);
    QString strCmd = ":SPURious:RANGe:PEAK:DEFInition ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
/**
 * @brief getSpurEMpeakDefi
 * @param curRangeIndex
 * @return mValue
 **/
qreal controlInterface::getSpurEMpeakDefi(qint32 curRangeIndex)
{
    if(curRangeIndex < 0 ||curRangeIndex >= SPUR_EM_DATE_MAX)
    {
        curRangeIndex = globalUserVariable->gSpurEMCurRangeIndex;
    }
    return globalUserVariable->gSpurEMPara[curRangeIndex].peakDefi;
}
/**
 * @brief setSpurEMpeakThreshold
 * @param mValue,curRangeIndex
 * @return
 **/
void controlInterface::setSpurEMpeakThreshold(qreal mValue,qint32 curRangeIndex)
{
    if(curRangeIndex < 0 ||curRangeIndex >= SPUR_EM_DATE_MAX)
    {
        curRangeIndex = globalUserVariable->gSpurEMCurRangeIndex;
    }
    if(mValue > SPEC_AMPTD_MAX)
    {
        mValue = SPEC_AMPTD_MAX;
    }
    else if(mValue < SPEC_AMPTD_MIN)
    {
        mValue = SPEC_AMPTD_MIN;
    }
    globalUserVariable->gSpurEMPara[curRangeIndex].peakThreshold = mValue;

    QString iVal = QString::number(mValue);
    QString strCmd = ":SPURious:RANGe:PEAK:THREshold ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
/**
 * @brief getSpurEMpeakThreshold
 * @param curRangeIndex
 * @return mValue
 **/
qreal controlInterface::getSpurEMpeakThreshold(qint32 curRangeIndex)
{
    if(curRangeIndex < 0 ||curRangeIndex >= SPUR_EM_DATE_MAX)
    {
        curRangeIndex = globalUserVariable->gSpurEMCurRangeIndex;
    }
    return globalUserVariable->gSpurEMPara[curRangeIndex].peakThreshold;
}
/**
 * @brief setSpurEMAtten
 * @param mAtten,curRangeIndex
 * @return
 **/
void controlInterface::setSpurEMAtten(qreal mAtten,qint32 curRangeIndex)
{
    if(curRangeIndex < 0 ||curRangeIndex >= SPUR_EM_DATE_MAX)
    {
        curRangeIndex = globalUserVariable->gSpurEMCurRangeIndex;
    }
    if(mAtten < 0)
    {
        mAtten = 0;
    }else if(mAtten > 50)
    {
        mAtten = 50;
    }
    globalUserVariable->gSpurEMPara[curRangeIndex].Atten = mAtten;

    QString iVal = QString::number(mAtten);
    QString strCmd = ":SPURious:RANGe:ATTEn ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    return;
}
/**
 * @brief getSpurEMAtten
 * @param curRangeIndex
 * @return mAtten
 **/
qreal controlInterface::getSpurEMAtten(qint32 curRangeIndex)
{
    if(curRangeIndex < 0 ||curRangeIndex >= SPUR_EM_DATE_MAX)
    {
        curRangeIndex = globalUserVariable->gSpurEMCurRangeIndex;
    }
    return globalUserVariable->gSpurEMPara[curRangeIndex].Atten;
}

/**
 * @brief SetSysRefuiStates
 * @param mType
 */
void controlInterface::SetSysRefuiStates(qint32 itype)
{
    if(globalUserVariable->gAutoRepeat)
    {
        //if(globalUserVariable->gFreqReference == itype) return;
    }
    globalUserVariable->gFreqReference = itype;
    emit infoRefresh(SA_INFO_SYSTEM,SA_INFO_SYSTEM_FREQ_REF);
    return;
}
/**
 * @brief GetSysRefuiStates
 * @return
 */
qint32 controlInterface::GetSysRefuiStates()
{
    return globalUserVariable->gFreqReference;
}
/**
 * @brief setCenterFreq
 * @param uCenterFreq
 */
void controlInterface::setCenterFreq(qreal uCenterFreq)
{
    QString iVal = QString::number(uCenterFreq);
    QString strCmd = ":FREQuency:CENTer ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gCenterFreq == uCenterFreq - globalUserVariable->gfreqOffset) return;
    }
    //Flag:Internal or External
    //Mode:
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||\
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE)
        {
            return;
        }
    }
    quint32 tempFlag = 0;
    qint64 baseFreq;
    qreal min,max,value;;
    //***********set centerFreq
    //    uCenterFreq = uCenterFreq > SPEC_FREQ_MAX ? SPEC_FREQ_MAX : uCenterFreq;
    //    uCenterFreq = uCenterFreq < SPEC_FREQ_MIN ? SPEC_FREQ_MIN : uCenterFreq;

    value = (qreal)uCenterFreq - globalUserVariable->gfreqOffset;
    //if(value < 0) value = 0;
    if( value < SPEC_FREQ_MIN)
    {
        value = SPEC_FREQ_MIN;
    }
    else if(value > SPEC_FREQ_MAX)
    {
        value = SPEC_FREQ_MAX;
    }
    globalUserVariable->gCenterFreq = value;
    //double precise
    //if((globalUserVariable->gCenterFreq + DOUBLEPRECISE) < value)
    //{
    //    globalUserVariable->gCenterFreq ++;
    //}


    if(globalUserVariable->gZeroSpanAction)
    {
        globalUserVariable->gCenterFreq = globalUserVariable->gCenterFreq > SPEC_FREQ_MAX ? SPEC_FREQ_MAX : globalUserVariable->gCenterFreq;
        globalUserVariable->gCenterFreq = globalUserVariable->gCenterFreq < SPEC_FREQ_MIN ? SPEC_FREQ_MIN : globalUserVariable->gCenterFreq;
        globalUserVariable->gStartFreq = globalUserVariable->gStopFreq = globalUserVariable->gCenterFreq;
        globalUserVariable->gSpanFreq = 0;
    }
    else
    {
        globalUserVariable->adjustFreqByCer();
        globalUserVariable->stepFreqCalculatorFunc();
        globalUserVariable->markerPositionReCalculatorFunc();
    }

    //*************send centerFreq control to FPGA
    if(globalUserVariable->gZeroSpanAction)
    {
        globalUserVariable->converFreqToShm();
    }
    else
    {
        bitaloth->ConfigureFrequencyStartStop(globalUserVariable->gStartFreq,globalUserVariable->gStopFreq);
        if(globalUserVariable -> gcheckswitch != globalUserVariable -> goldcheckswitch)
        {
            globalUserVariable -> goldcheckswitch = globalUserVariable -> gcheckswitch;
        }
        if(globalUserVariable->gspanChangebyFreq && globalUserVariable->grbwChangedbyFreq)
        {
            globalUserVariable->convertBwToShm();
        }
        globalUserVariable->converFreqToShm();
    }
    baseFreq = globalUserVariable->gCenterFreq - globalUserVariable->gfreqOffset;
    if( baseFreq < SPEC_FREQ_MIN)
    {
        baseFreq = SPEC_FREQ_MIN;
    }
    else if(baseFreq > SPEC_FREQ_MAX)
    {
        baseFreq = SPEC_FREQ_MAX;
    }
    globalUserVariable->adjustCHStandarByCerFreq(globalUserVariable->gCenterFreq);
    initTraceAverage();
    emit infoRefresh(SA_INFO_FREQ,SA_INFO_FREQ_CENTER);

    //Johnson 190709
    //QThread::usleep(200000);
    setTriggerLevel(globalUserVariable->gTriggerLevel[globalUserVariable->gTriggerMode]);
}
/**
 * @brief getCenterFreq
 * @return
 */
qreal controlInterface::getCenterFreq()
{
    return (qreal)globalUserVariable->gCenterFreq + globalUserVariable->gfreqOffset;
}
/**
 * @brief setStartFreq
 * @param uStartFreq
 */
void controlInterface::setStartFreq(qreal uStartFreq)
{
    QString iVal = QString::number(uStartFreq);
    QString strCmd = ":FREQuency:STARt ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(globalUserVariable->gAutoRepeat)
    {
        if(uStartFreq - globalUserVariable->gfreqOffset == globalUserVariable->gStartFreq) return;
    }

    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {
            return;
        }
    }

    quint32 tempFlag = 0;
    qreal value;
    ////***********set startFreq
    value = (qreal)uStartFreq - globalUserVariable->gfreqOffset;
    if( value < SPEC_FREQ_MIN)
    {
        value = SPEC_FREQ_MIN;
    }
    else if(value > SPEC_FREQ_MAX)
    {
        value = SPEC_FREQ_MAX + 5;
    }
    globalUserVariable->gStartFreq = value;
    //if((globalUserVariable->gStartFreq + DOUBLEPRECISE) < value)
    //{
    //    globalUserVariable->gStartFreq++;
    //}
    globalUserVariable->adjustFreqByStart();
    globalUserVariable->stepFreqCalculatorFunc();
    globalUserVariable->markerPositionReCalculatorFunc();

    //*************send startFreq control to FPGA
    if(globalUserVariable->gZeroSpanAction)
    {
        globalUserVariable->gZeroSpanAction = SA_OFF;

        //Johnson 190425
        if(globalUserVariable->uIFMode != SA_AUTO_IFMODE)
        {
            globalUserVariable->uIFMode = SA_AUTO_IFMODE;
        }

        //Johnson 190912
        if(globalUserVariable->gGateViewStatus == SA_GATE_VIEW_OPEN)
        {
            globalUserVariable->gGateViewStatus = SA_GATE_VIEW_CLOSE;
            globalUserVariable->gGateSweepSpanChange = 0;
        }
    }
    bitaloth->ConfigureFrequencyStartStop(globalUserVariable->gStartFreq,globalUserVariable->gStopFreq);
    if(globalUserVariable -> gcheckswitch != globalUserVariable -> goldcheckswitch)
    {
        globalUserVariable -> goldcheckswitch = globalUserVariable -> gcheckswitch;
    }
    if(globalUserVariable->grbwChangedbyFreq)
    {
        globalUserVariable->convertBwToShm();
    }
    globalUserVariable->converFreqToShm();

    globalUserVariable->adjustCHStandarByCerFreq(globalUserVariable->gCenterFreq);
    initTraceAverage();
    emit infoRefresh(SA_INFO_FREQ,SA_INFO_FREQ_START);

    setTriggerLevel(globalUserVariable->gTriggerLevel[globalUserVariable->gTriggerMode]);
}

/**
 * @brief getStartFreq
 * @return
 */
qreal controlInterface::getStartFreq()
{
    return (qreal)globalUserVariable->gStartFreq + globalUserVariable->gfreqOffset;
}

/**
 * @brief setStopFreq
 * @param uStopFreq
 */
void controlInterface::setStopFreq(qreal uStopFreq)
{
    QString iVal = QString::number(uStopFreq);
    QString strCmd = ":FREQuency:STOP ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(globalUserVariable->gAutoRepeat)
    {
        if(uStopFreq - globalUserVariable->gfreqOffset == globalUserVariable->gStopFreq) return;
    }
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }

    quint32 tempFlag = 0;
    qreal value;
    value = (qreal)uStopFreq - globalUserVariable->gfreqOffset;
    if( value < SPEC_FREQ_MIN)
    {
        value = SPEC_FREQ_MIN;
    }
    else if(value > SPEC_FREQ_MAX)
    {
        value = SPEC_FREQ_MAX + 5;
    }
    //*************set stopFreq
    globalUserVariable->gStopFreq =value;
    //if((globalUserVariable->gStopFreq + DOUBLEPRECISE) < value)
    //{
    //    globalUserVariable->gStopFreq++;
    //}

    globalUserVariable->adjustFreqByStop();
    globalUserVariable->stepFreqCalculatorFunc();
    globalUserVariable->markerPositionReCalculatorFunc();

    //*************send stopFreq control to FPGA
    if(globalUserVariable->gZeroSpanAction)
    {
        globalUserVariable->gZeroSpanAction = SA_OFF;

        //Johnson 190425
        if(globalUserVariable->uIFMode != SA_AUTO_IFMODE)
        {
            globalUserVariable->uIFMode = SA_AUTO_IFMODE;
        }

        //Johnson 190912
        if(globalUserVariable->gGateViewStatus == SA_GATE_VIEW_OPEN)
        {
            globalUserVariable->gGateViewStatus = SA_GATE_VIEW_CLOSE;
            globalUserVariable->gGateSweepSpanChange = 0;
        }
    }
    bitaloth->ConfigureFrequencyStartStop(globalUserVariable->gStartFreq,globalUserVariable->gStopFreq);
    if(globalUserVariable -> gcheckswitch != globalUserVariable -> goldcheckswitch)
    {
        globalUserVariable -> goldcheckswitch = globalUserVariable -> gcheckswitch;
    }
    if(globalUserVariable->grbwChangedbyFreq)
    {
        globalUserVariable->convertBwToShm();
    }
    globalUserVariable->converFreqToShm();
    globalUserVariable->adjustCHStandarByCerFreq(globalUserVariable->gCenterFreq);
    initTraceAverage();
    emit infoRefresh(SA_INFO_FREQ,SA_INFO_FREQ_STOP);

    setTriggerLevel(globalUserVariable->gTriggerLevel[globalUserVariable->gTriggerMode]);

}
/**
 * @brief getStopFreq
 * @return
 */
qreal controlInterface::getStopFreq()
{
    return (qreal)globalUserVariable->gStopFreq + globalUserVariable->gfreqOffset;
}
/**
 * @brief setCFFreq
 * @param uCFFreq
 */
void controlInterface::setCFFreq(quint64 uCFFreq)
{
    QString iVal = QString::number(uCFFreq);
    QString strCmd = ":FREQuency:STEP ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gCFFreq == uCFFreq) return;
    }

    if(uCFFreq < 1) globalUserVariable->gCFFreq = 1;
    else if(uCFFreq > SPEC_FREQ_MAX - SPEC_FREQ_MIN) globalUserVariable->gCFFreq = SPEC_FREQ_MAX - SPEC_FREQ_MIN;
    else globalUserVariable->gCFFreq = uCFFreq;
}
/**
 * @brief getCFFreq
 * @return
 */
quint64 controlInterface::getCFFreq()
{
    return globalUserVariable->gCFFreq;
}

/**
 * @brief setFreqOffset
 * @param uFreqOffset
*/
void controlInterface::setFreqOffset(qint64 uFreqOffset)
{
    QString iVal = QString::number(uFreqOffset);
    QString strCmd = ":FREQuency:OFFSet ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gfreqOffset == uFreqOffset) return;
    }

    if(uFreqOffset< -43000000000)
        uFreqOffset = -43000000000;
    else if(uFreqOffset> 43000000000)
        uFreqOffset = 43000000000;
    globalUserVariable->gfreqOffset = uFreqOffset;
    //    initTraceAverage();
    emit infoRefresh(SA_INFO_FREQ,SA_INFO_FREQ_OFFSET);
    return;
}
/**
 * @brief getFreqOffset
 * @return
 */
qint64 controlInterface::getFreqOffset()
{
    return globalUserVariable->gfreqOffset;
}
/**
 * @brief setSpan
 * @param uSpanFeq
 */
void controlInterface::setSpan(quint64 uSpanFeq)
{
    QString iVal = QString::number(uSpanFeq);
    QString strCmd = ":FREQuency:SPAN ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gSpanFreq == uSpanFeq) return;
    }
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||\
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE)
        {

            return;
        }
    }

    if(globalUserVariable->gZeroSpanAction == SA_ON)
    {
        if(globalUserVariable->gCenterFreq == SPEC_FREQ_MAX || globalUserVariable->gCenterFreq == SPEC_FREQ_MIN) return;
    }

    if(uSpanFeq > SPEC_FREQ_MAX) uSpanFeq = SPEC_FREQ_MAX;
    else if(uSpanFeq < SPEC_FREQ_MIN) uSpanFeq = SPEC_FREQ_MIN;


    quint32 tempFlag = 0;
    quint32 reFlag = 0;
    //**************set span
    if(globalUserVariable->currentMode == SA_SPAN_MODE) uSpanFeq = uSpanFeq < 10 ? 10 : uSpanFeq;
    else if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE) uSpanFeq = uSpanFeq < 10 ? 10 : uSpanFeq;
    else if(globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE) uSpanFeq = uSpanFeq < 10 ? 10 : uSpanFeq;
    else if(globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE) uSpanFeq = uSpanFeq < 2000000 ? 2000000 : uSpanFeq;
    else if(globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE) uSpanFeq = uSpanFeq < 100 ? 100 : uSpanFeq;
    else if(globalUserVariable->currentMode == SA_ACP_MEASURE_MODE) uSpanFeq = uSpanFeq < 8000000 ? 8000000 : uSpanFeq;
    else if(globalUserVariable->currentMode == SA_MULTI_ACP_MODE) uSpanFeq = uSpanFeq < 8000000 ? 8000000 : uSpanFeq;
    /*if(globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE) uSpanFeq = uSpanFeq < 2000000 ? 2000000 : uSpanFeq;
    else if(globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE) uSpanFeq = uSpanFeq < 10 ? 10 : uSpanFeq;*/


    if(0 == uSpanFeq)
    {

        globalUserVariable->gStartFreq = globalUserVariable->gStopFreq = globalUserVariable->gCenterFreq;
        globalUserVariable->gLastSpanFreq = globalUserVariable->gSpanFreq;
        globalUserVariable->gSpanFreq = uSpanFeq;
        //Tony 0713
        if(globalUserVariable->gZeroSpanAction == SA_OFF)
        {
            globalUserVariable->markerValueToTime();
            globalUserVariable->gZeroSpanAction = SA_ON;
            globalUserVariable->gSpanMode = SA_ON;
        }
    }
    else
    {
        //Tony 190713 need save last timestep
        qreal   timestep = globalUserVariable->gSweepTime/(globalUserVariable->gTracePoint - 1);
        globalUserVariable->adjustFreqBySpan(uSpanFeq);
        globalUserVariable->stepFreqCalculatorFunc();
        //Tony 190713
        if(globalUserVariable->gZeroSpanAction == SA_ON)
        {
            reFlag =1;

            globalUserVariable->markerValueToFreq(timestep);
            globalUserVariable->gZeroSpanAction = SA_OFF;
            globalUserVariable->gSpanMode = SA_OFF;
        }

        globalUserVariable->markerPositionReCalculatorFunc();
    }

    /////=================== BUG
    //*************send spanFreq control to FPGA
    if(globalUserVariable->gZeroSpanAction && 0 == globalUserVariable->gSpanFreq)
    {

    }
    else
    {
        /*if(globalUserVariable->gZeroSpanAction) */
        if(reFlag)
        {
            globalUserVariable->gZeroSpanAction = SA_OFF;
            //Johnson 190425
            if(globalUserVariable->uIFMode != SA_AUTO_IFMODE)
            {
                globalUserVariable->uIFMode = SA_AUTO_IFMODE;
            }

            //Johnson 190912
            if(globalUserVariable->gGateViewStatus == SA_GATE_VIEW_OPEN)
            {
                globalUserVariable->gGateViewStatus = SA_GATE_VIEW_CLOSE;
                globalUserVariable->gGateSweepSpanChange = 0;
            }
        }

        bitaloth->ConfigureFrequencyStartStop(globalUserVariable->gStartFreq,globalUserVariable->gStopFreq);
        if(globalUserVariable -> gcheckswitch != globalUserVariable -> goldcheckswitch)
        {
            globalUserVariable -> goldcheckswitch = globalUserVariable -> gcheckswitch;
        }
        if(globalUserVariable->grbwChangedbyFreq)
        {
            globalUserVariable->convertBwToShm();
        }
    }
    globalUserVariable->stepFreqCalculatorFunc();
    globalUserVariable->converFreqToShm();
    initTraceAverage();
    emit infoRefresh(SA_INFO_FREQ,SA_INFO_FREQ_SPAN);

    //Johnson 190709
    //QThread::usleep(200000);
    setTriggerLevel(globalUserVariable->gTriggerLevel[globalUserVariable->gTriggerMode]);
}
/**
 * @brief getSpan
 * @return
 */
quint64 controlInterface::getSpan()
{
    return globalUserVariable->gSpanFreq;
}
/**
 * @brief setFullSpan
 */
void controlInterface::setFullSpan()
{
    QString strCmd = ":FREQuency:SPAN:FULL";
    emit sendSCPIcmd(strCmd);

    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||\
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE)
        {

            return;
        }
    }
    quint32 tempFlag = 0;
    qint32 refreshFlag = 0;
    qreal timeStep;
    if(globalUserVariable->gZeroSpanAction)
    {
        refreshFlag = 1;
        timeStep = globalUserVariable->gSweepTime/(globalUserVariable->gTracePoint - 1);
    }

    globalUserVariable->gStartFreq = SPEC_FREQ_MIN ;
    globalUserVariable->gStopFreq = SPEC_FREQ_MAX ;
    if(globalUserVariable->gStopFreq - globalUserVariable->gStartFreq != globalUserVariable->gSpanFreq)
    {
        globalUserVariable->gLastSpanFreq =  globalUserVariable->gSpanFreq;
    }
    else if(globalUserVariable->gAutoRepeat) return;

    globalUserVariable->gSpanFreq = globalUserVariable->gStopFreq - globalUserVariable->gStartFreq;
    globalUserVariable->gCenterFreq = globalUserVariable->gStartFreq + (globalUserVariable->gSpanFreq / 2) ;

    if(globalUserVariable->gZeroSpanAction)
    {
        globalUserVariable->gZeroSpanAction = SA_OFF;
        //Johnson 190425
        if(globalUserVariable->uIFMode != SA_AUTO_IFMODE)
        {
            globalUserVariable->uIFMode = SA_AUTO_IFMODE;
        }

        //Johnson 190912
        if(globalUserVariable->gGateViewStatus == SA_GATE_VIEW_OPEN)
        {
            globalUserVariable->gGateViewStatus = SA_GATE_VIEW_CLOSE;
            globalUserVariable->gGateSweepSpanChange = 0;
        }
    }

    globalUserVariable->converFreqToShm();

    bitaloth->ConfigureFrequencyStartStop(globalUserVariable->gStartFreq,globalUserVariable->gStopFreq);
    if(globalUserVariable->grbwChangedbyFreq)
    {
        globalUserVariable->convertBwToShm();
    }

    globalUserVariable->stepFreqCalculatorFunc();
    globalUserVariable->converFreqToShm();
    if(globalUserVariable -> gcheckswitch != globalUserVariable -> goldcheckswitch)
    {
        globalUserVariable -> goldcheckswitch = globalUserVariable -> gcheckswitch;
    }
    globalUserVariable->adjustCHStandarByCerFreq(globalUserVariable->gCenterFreq);
    if(refreshFlag)
    {
        globalUserVariable->markerValueToFreq(timeStep);
    }
    globalUserVariable->markerPositionReCalculatorFunc();
    initTraceAverage();
    emit infoRefresh(SA_INFO_FREQ,SA_INFO_FREQ_SPAN);

    //Johnson 190709
    //QThread::usleep(200000);
    setTriggerLevel(globalUserVariable->gTriggerLevel[globalUserVariable->gTriggerMode]);
}
/**
 * @brief setZeroSpan
 */
void controlInterface::setZeroSpan()
{
    QString strCmd = ":FREQuency:SPAN:ZERO";
    emit sendSCPIcmd(strCmd);

    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }
    if(globalUserVariable->gMarkerFreqCount[globalUserVariable->gMarkerSelect]) return;
    if(globalUserVariable->gDrCtrlSwitch == SA_OPEN_DCSWEEP && globalUserVariable->gDrCtrlSweepMode == SA_FFT_DCSWEEPMODE) return;

    quint32 tempFlag = 0;
    qreal mzeromimtimes = 0.;
    qint32 refreshFlag = 0;
    if(globalUserVariable->gZeroSpanAction == SA_OFF)
    {
        refreshFlag = 1;
    }

    if(3 == globalUserVariable->ganamode)
    {
        //globalUserVariable->gRbw = 10000;
        //bitaloth->ConfigureSweepCoupling(globalUserVariable->gAutoRbw,(qreal)globalUserVariable->gRbw,globalUserVariable->gAutoVbw,globalUserVariable->gVbw,1,globalUserVariable->gVbwtoRbw);
        quint32 tmpAutoRbw = globalUserVariable->gAutoRbw;
        globalUserVariable->gAutoRbw = SA_OFF;
        setRbwValue(10000);//Johnson 190706
        globalUserVariable->gAutoRbw = tmpAutoRbw;
    }
    if(0 != globalUserVariable->gSpanFreq)
    {
        globalUserVariable->gLastSpanFreq = globalUserVariable->gSpanFreq;
    }
    else if(globalUserVariable->gAutoRepeat) return;

    globalUserVariable->gStartFreq = globalUserVariable->gCenterFreq ;
    globalUserVariable->gStopFreq = globalUserVariable->gCenterFreq ;
    globalUserVariable->gSpanFreq = 0;
    globalUserVariable->gZeroSpanAction = SA_ON;

    globalUserVariable->ganamode = 0;//0 FirMode,3 FftMode
    globalUserVariable->gSpanMode = 1;//0 Normal,1 ZeroSpan
    mzeromimtimes = bitaloth->GetZeroSpanRbwMinms(NUM_SWEEP_POINT);

    if(1 == globalUserVariable->gsweepAuto)
    {
        globalUserVariable->gSweepTime = mzeromimtimes;
        globalUserVariable->gZeroSpanTime = globalUserVariable->gSweepTime;
    }
    else
    {
        globalUserVariable->gSweepTime = globalUserVariable->gSweepTime < mzeromimtimes ? mzeromimtimes : globalUserVariable->gSweepTime;
        globalUserVariable->gZeroSpanTime = globalUserVariable->gSweepTime;
    }
    bitaloth->GetZeroShmTimes(globalUserVariable->gSweepTime,NUM_SWEEP_POINT);

    if(globalUserVariable -> gcheckswitch != globalUserVariable -> goldcheckswitch)
    {
        globalUserVariable -> goldcheckswitch = globalUserVariable -> gcheckswitch;
    }

    globalUserVariable->stepFreqCalculatorFunc();
    globalUserVariable->converFreqToShm();
    initTraceAverage();
    globalUserVariable->adjustCHStandarByCerFreq(globalUserVariable->gCenterFreq);
    emit infoRefresh(SA_INFO_FREQ,SA_INFO_FREQ_SPAN);

    //Tony 190713
    if(refreshFlag)
    {
        globalUserVariable->markerValueToTime();
    }

    globalUserVariable->markerPositionReCalculatorFunc();
    //Johnson 190709
    //QThread::usleep(200000);
    setTriggerLevel(globalUserVariable->gTriggerLevel[globalUserVariable->gTriggerMode]);
}
/**
 * @brief getLastSpan
 * @return
 */
quint64 controlInterface::getLastSpan()
{
    return globalUserVariable->gLastSpanFreq;
}
/**
 * @brief setLastSpan
 */
void controlInterface::setLastSpan()
{
    QString strCmd = ":FREQuency:SPAN:PREVious";
    emit sendSCPIcmd(strCmd);

    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||\
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE)
        {

            return;
        }
    }
    quint32 tempFlag = 0;
    qint32 refreshFlag = 0;
    qreal timestep;
    if(globalUserVariable->gZeroSpanAction == SA_OFF && 0 == globalUserVariable->gLastSpanFreq)
    {
        refreshFlag = 1;
    }else if(globalUserVariable->gZeroSpanAction == SA_ON && 0 != globalUserVariable->gLastSpanFreq)
    {
        timestep = globalUserVariable->gSweepTime/(globalUserVariable->gTracePoint -1);
        refreshFlag = 2;
    }
    if(0 == globalUserVariable->gLastSpanFreq)
    {
        quint64 tmpSpanFreq = globalUserVariable->gSpanFreq;
        setZeroSpan();
        globalUserVariable->gLastSpanFreq = tmpSpanFreq;

        /*globalUserVariable->gZeroSpanAction = SA_ON;
        globalUserVariable->gStartFreq = globalUserVariable->gCenterFreq ;
        globalUserVariable->gStopFreq = globalUserVariable->gCenterFreq ;
        quint64 tmpSpanFreq = globalUserVariable->gSpanFreq;
        globalUserVariable->gSpanFreq = globalUserVariable->gLastSpanFreq;
        globalUserVariable->gLastSpanFreq = tmpSpanFreq;

        SA_sm_config_sweep->SpanMode = globalUserVariable->gSpanMode = 1;

        SA_sm_config_sweep->SpanMode = globalUserVariable->gSpanMode = 1;//Johnson Steve
        tempFlag |= IXS_SA_SpanMode;
        SA_Set_config_flag(IXT_SA_ConfigSweep, tempFlag);*/
    }
    else
    {
        quint64 tmpSpanFreq = globalUserVariable->gSpanFreq;
        setSpan(globalUserVariable->gLastSpanFreq);
        globalUserVariable->gLastSpanFreq = tmpSpanFreq;

        /*if(globalUserVariable->gZeroSpanAction)
        {
            SA_sm_config_sweep->SpanMode = globalUserVariable->gSpanMode = 0;
            globalUserVariable->gZeroSpanAction = SA_OFF;
            tempFlag |= IXS_SA_SpanMode;

            //Johnson 190425
            if(globalUserVariable->uIFMode != SA_AUTO_IFMODE)
            {
                globalUserVariable->uIFMode = SA_AUTO_IFMODE;
                SA_sm_config_sweep->uIFMode = SA_AUTO_IFMODE;
                tempFlag |= IXS_SA_IFmode;
            }
        }

        quint64 tmpSpanFreq = globalUserVariable->gSpanFreq;
        globalUserVariable->gSpanFreq = globalUserVariable->gLastSpanFreq;
        globalUserVariable->gLastSpanFreq = tmpSpanFreq;


        if(globalUserVariable->gCenterFreq < globalUserVariable->gSpanFreq/2)
            globalUserVariable->gCenterFreq = globalUserVariable->gSpanFreq/2;

        globalUserVariable->gStartFreq = globalUserVariable->gCenterFreq - (globalUserVariable->gSpanFreq/2) ;
        globalUserVariable->gStopFreq = globalUserVariable->gCenterFreq + (globalUserVariable->gSpanFreq/2) ;

        bitaloth->ConfigureFrequencyStartStop(globalUserVariable->gStartFreq,globalUserVariable->gStopFreq);

        if(globalUserVariable -> gcheckswitch != globalUserVariable -> goldcheckswitch)
        {
            tempFlag |= IXS_SA_CheckAciton;
            globalUserVariable -> goldcheckswitch = globalUserVariable -> gcheckswitch;
        }
        if(globalUserVariable->grbwChangedbyFreq)
        {
            globalUserVariable->convertBwToShm();
            SA_sm_config_sweep->ischangeRbwitself = 0;
            tempFlag |= IXS_SA_CenterFreq|IXS_SA_SpanFreq|IXS_SA_StartFreq|IXS_SA_StopFreq|IXS_SA_RBW;
        }
        else
        {
            tempFlag |= IXS_SA_CenterFreq|IXS_SA_SpanFreq|IXS_SA_StartFreq|IXS_SA_StopFreq;
        }
        globalUserVariable->stepFreqCalculatorFunc();
        globalUserVariable->converFreqToShm();
        SA_Set_config_flag(IXT_SA_ConfigSweep, tempFlag);*/
    }
    globalUserVariable->adjustCHStandarByCerFreq(globalUserVariable->gCenterFreq);
    //Tony 0713
    if(refreshFlag == 1)
    {
        globalUserVariable->markerValueToTime();
    }
    else if(refreshFlag == 2)
    {
        globalUserVariable->markerValueToFreq(timestep);
    }

    initTraceAverage();
    emit infoRefresh(SA_INFO_FREQ,SA_INFO_FREQ_SPAN);

    //Johnson 190709
    //QThread::usleep(200000);
    setTriggerLevel(globalUserVariable->gTriggerLevel[globalUserVariable->gTriggerMode]);
}
/**
 * @brief setRefLevel
 * @param dRefLevel
 */
void controlInterface::setRefLevel(qreal dRefLevel)
{
    QString iVal = QString::number(dRefLevel);
    QString strCmd = ":AMPLitude:RLEVel ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    quint32 uFlag = 0;
    //***********set RefLevel
    if (SPEC_AMPTD_MIN > dRefLevel) dRefLevel = SPEC_AMPTD_MIN;
    if(dRefLevel  > SPEC_AMPTD_MAX) dRefLevel = SPEC_AMPTD_MAX;
    if (SPEC_AMPTD_MIN <= dRefLevel && dRefLevel  <= SPEC_AMPTD_MAX)
    {
        if(globalUserVariable->gAutoRepeat)
        {
            if(globalUserVariable->gRefLevel == dRefLevel) return;
        }
        globalUserVariable->gRefLevel = dRefLevel;
        if(globalUserVariable->gRefOffset < SPEC_AMPTD_MIN - globalUserVariable->gRefLevel)
        {
            globalUserVariable->gRefOffset = SPEC_AMPTD_MIN - globalUserVariable->gRefLevel;
        }
        else if( globalUserVariable->gRefOffset > SPEC_AMPTD_MAX - globalUserVariable->gRefLevel)
        {
            globalUserVariable->gRefOffset = SPEC_AMPTD_MAX - globalUserVariable->gRefLevel;
        }
    }
    //*************send RefLevel control to FPGA
    if(globalUserVariable->gRefLevel>0.)
    {
        if(globalUserVariable->gPreamp == SA_ON)
        {
            globalUserVariable->gPreamp = SA_OFF;
        }
    }

    qreal tmpAtten = globalUserVariable->gAttenValue;

    if(globalUserVariable->gAtten == SA_AUTO)
    {
        if(globalUserVariable->gPreamp == SA_OFF)
        {
            if(globalUserVariable->gRefLevel-15.>0.)      tmpAtten = 30.;
            else if(globalUserVariable->gRefLevel-10.>0.) tmpAtten = 25.;
            else if(globalUserVariable->gRefLevel-5.>0.)  tmpAtten = 20.;
            else if(globalUserVariable->gRefLevel>0.)     tmpAtten = 15.;
            else if(globalUserVariable->gRefLevel+5.>0.)  tmpAtten = 10.;
            else if(globalUserVariable->gRefLevel+10.>0.) tmpAtten = 5.;


            if(globalUserVariable->gRefLevel+10.<=0.)     tmpAtten = 0.;
        }
        else
        {
            if(globalUserVariable->gRefLevel+5.>0.&&globalUserVariable->gRefLevel<=0) tmpAtten = 30.;
            else if(globalUserVariable->gRefLevel+10.>0.)                             tmpAtten = 25.;
            else if(globalUserVariable->gRefLevel+15.>0.)                             tmpAtten = 20.;
            else if(globalUserVariable->gRefLevel+20.>0.)                             tmpAtten = 15.;
            else if(globalUserVariable->gRefLevel+25.>0.)                             tmpAtten = 10.;
            else if(globalUserVariable->gRefLevel+30.>0.)                             tmpAtten = 5.;


            if(globalUserVariable->gRefLevel+30.<=0)                                  tmpAtten = 0.;
        }
    }
    else
    {
        if(globalUserVariable->gPreamp == SA_OFF)
        {
            if(globalUserVariable->gAttenValue - 50. > 0.)
                tmpAtten = 50.;
        }
        else
        {
            if(globalUserVariable->gAttenValue - 30. > 0.)
                tmpAtten = 30.;
        }
    }

    if(globalUserVariable->gAutoRepeat)
    {
        if(tmpAtten != globalUserVariable->gAttenValue)
        {
            globalUserVariable->gAttenValue = tmpAtten;
        }
    }
    else
    {
        globalUserVariable->gAttenValue = tmpAtten;
    }

    globalUserVariable->topLevel = globalUserVariable->gRefLevel+globalUserVariable->gRefOffset;
    globalUserVariable->lowLevel = globalUserVariable->topLevel - GRID_NUM_Y_TICKS*globalUserVariable->gScaleDiv;
    initTraceAverage();
    emit infoRefresh(SA_INFO_AMPT,SA_INFO_AMPT_REF);

    //Johnson 190709
    //QThread::usleep(200000);
    setTriggerLevel(globalUserVariable->gTriggerLevel[globalUserVariable->gTriggerMode]);
}

/**
 * @brief getRefLevel
 * @return
 */
qreal controlInterface::getRefLevel()
{
    return globalUserVariable->gRefLevel;
}
/**
 * @brief setAttenValue
 * @param dAtten
 */
void controlInterface::setAttenValue(qreal dAtten)
{
    QString iVal = QString::number(dAtten);
    QString strCmd = ":AMPLitude:ATTEnuation ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||\
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE)
        {

            return;
        }
    }
    //globalUserVariable->gAtten = SA_MANUAL;
    if(globalUserVariable->gAtten == SA_MANUAL)
    {
        if(globalUserVariable->gPreamp == SA_OFF)
        {
            if(dAtten<=0.)
            {
                dAtten = 0.00;
            }
            else if(dAtten-5.<=0.)
            {
                dAtten = 5.00;
            }
            else if(dAtten-10.<=0.)
            {
                dAtten = 10.00;
            }
            else if(dAtten-15.<=0.)
            {
                dAtten = 15.00;
            }
            else if(dAtten-20.<=0.)
            {
                dAtten = 20.00;
            }
            else if(dAtten-25.<=0.)
            {
                dAtten = 25.00;
            }
            else if(dAtten-30.<=0.)
            {
                dAtten = 30.00;
            }
            else if(dAtten-35.<=0.)
            {
                dAtten = 35.00;
            }
            else if(dAtten-40.<=0.)
            {
                dAtten = 40.00;
            }
            else if(dAtten-45.<=0.)
            {
                dAtten = 45.00;
            }
            else
            {
                dAtten = 50.00;
            }
        }
        else
        {
            if(dAtten<=0.)
            {
                dAtten = 0.00;
            }
            else if(dAtten-5.<=0.)
            {
                dAtten = 5.00;
            }
            else if(dAtten-10.<=0.)
            {
                dAtten = 10.00;
            }
            else if(dAtten-15.<=0.)
            {
                dAtten = 15.00;
            }
            else if(dAtten-20.<=0.)
            {
                dAtten = 20.00;
            }
            else if(dAtten-25.<=0.)
            {
                dAtten = 25.00;
            }
            else
            {
                dAtten = 30.00;
            }
        }
        if(globalUserVariable->gAutoRepeat)
        {
            if(globalUserVariable->gAttenValue == dAtten) return;
        }
        globalUserVariable->gAttenValue = dAtten;
    }

    initTraceAverage();
    emit infoRefresh(SA_INFO_AMPT,SA_INFO_AMPT_ATTEN);

    //Johnson 190709
    //QThread::usleep(200000);
    setTriggerLevel(globalUserVariable->gTriggerLevel[globalUserVariable->gTriggerMode]);
}

/**
 * @brief getAttenValue
 * @return
 */
qreal controlInterface::getAttenValue()
{
    return globalUserVariable->gAttenValue;
}
/**
 * @brief setAttenStatus
 * @param uAttenStatus
 */
void controlInterface::setAttenStatus(quint32 uAttenStatus)
{
    uAttenStatus = !!uAttenStatus;

    QString iVal = QString::number(uAttenStatus);
    QString strCmd = ":AMPLitude:ATTEnuation:AUTO  ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);


    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gAtten == uAttenStatus) return;
    }
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||\
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE)
        {

            return;
        }
    }
    globalUserVariable->gAtten = uAttenStatus;

    //    if(globalUserVariable->gRefLevel>0.)
    //    {
    //        if(globalUserVariable->gPreamp == SA_ON)
    //        {
    //            globalUserVariable->gPreamp = SA_OFF;
    //            SA_sm_config_sweep->Preamp = globalUserVariable->gPreamp;
    //            SA_Set_config_flag(IXT_SA_ConfigSweep,IXS_SA_Preamp);
    //        }
    //    }
    qreal tmpAttenValue = globalUserVariable->gAttenValue;

    if(globalUserVariable->gAtten == SA_AUTO)
    {
        if(globalUserVariable->gPreamp == SA_OFF)
        {
            if(globalUserVariable->gRefLevel-15.>0.)      tmpAttenValue = 30.;
            else if(globalUserVariable->gRefLevel-10.>0.) tmpAttenValue = 25.;
            else if(globalUserVariable->gRefLevel-5.>0.)  tmpAttenValue = 20.;
            else if(globalUserVariable->gRefLevel>0.)     tmpAttenValue = 15.;
            else if(globalUserVariable->gRefLevel+5.>0.)  tmpAttenValue = 10.;
            else if(globalUserVariable->gRefLevel+10.>0.) tmpAttenValue = 5.;


            if(globalUserVariable->gRefLevel+10.<=0.)     tmpAttenValue = 0.;
        }
        else
        {
            if(globalUserVariable->gRefLevel+5.>0.&&globalUserVariable->gRefLevel<=0) tmpAttenValue = 30.;
            else if(globalUserVariable->gRefLevel+10.>0.)                             tmpAttenValue = 25.;
            else if(globalUserVariable->gRefLevel+15.>0.)                             tmpAttenValue = 20.;
            else if(globalUserVariable->gRefLevel+20.>0.)                             tmpAttenValue = 15.;
            else if(globalUserVariable->gRefLevel+25.>0.)                             tmpAttenValue = 10.;
            else if(globalUserVariable->gRefLevel+30.>0.)                             tmpAttenValue = 5.;


            if(globalUserVariable->gRefLevel+30.<=0)                                  tmpAttenValue = 0.;
        }
    }
    else
    {
        if(globalUserVariable->gPreamp == SA_OFF)
        {
            if(globalUserVariable->gAttenValue - 50. > 0.)
                tmpAttenValue = 50.;
        }
        else
        {
            if(globalUserVariable->gAttenValue - 30. > 0.)
                tmpAttenValue = 30.;
        }
    }

    /*
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gAttenValue == tmpAttenValue) return;
    }
*/
    globalUserVariable->gAttenValue = tmpAttenValue;
    initTraceAverage();
    emit infoRefresh(SA_INFO_AMPT,SA_INFO_AMPT_ATTENTYPE);

    //Johnson 190709
    //QThread::usleep(200000);
    setTriggerLevel(globalUserVariable->gTriggerLevel[globalUserVariable->gTriggerMode]);
}

/**
 * @brief getAttenStatus
 * @return
 */
quint32 controlInterface::getAttenStatus()
{
    return globalUserVariable->gAtten;
}
/**
 * @brief setScaleDiv
 * @param dScaleDiv
 */
void controlInterface::setScaleDiv(qreal dScaleDiv)
{
    QString iVal = QString::number(dScaleDiv);
    QString strCmd = ":AMPLitude:SCALe ";
    strCmd += iVal;
    sendSCPIcmd(strCmd);

    if(0.2 > dScaleDiv) dScaleDiv = 0.2;
    else if(20. < dScaleDiv) dScaleDiv = 20.;
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gScaleDiv == dScaleDiv) return;
    }
    globalUserVariable->gScaleDiv = dScaleDiv;

    globalUserVariable->topLevel = globalUserVariable->gRefLevel+globalUserVariable->gRefOffset;
    globalUserVariable->lowLevel = globalUserVariable->topLevel - GRID_NUM_Y_TICKS*globalUserVariable->gScaleDiv;
    emit infoRefresh(SA_INFO_AMPT,SA_INFO_AMPT_SCALEDIV);
    return;
}
/**
 * @brief getScaleDiv
 * @return
 */
qreal controlInterface::getScaleDiv()
{
    return globalUserVariable->gScaleDiv;
}
/**
 * @brief setAmpUnit
 * @param Unit
 */
void controlInterface::setAmpUnit(qint32 Unit)
{
    QString iVal = QString::number(Unit);
    QString strCmd = ":AMPLitude:PDIVision ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(Unit <0 || Unit > 5) return;
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gAmptdUnit == Unit) return;
    }
    globalUserVariable->gAmptdUnit = Unit;
    emit infoRefresh(SA_INFO_AMPT,SA_INFO_AMPT_UNIT);
}
/**
 * @brief getAmpUnit
 * @return
 */
qint32 controlInterface::getAmpUnit()
{
    return globalUserVariable->gAmptdUnit;
}
/**
 * @brief setPreampStatus
 * @param uPreamp
 */
void controlInterface::setPreampStatus(quint32 uPreamp)
{
    uPreamp = !!uPreamp;
    QString iVal = QString::number(uPreamp);
    QString strCmd = ":AMPLitude:PREAmp ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    //*************set preamStatus
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gPreamp == uPreamp) return;
    }
    globalUserVariable->gPreamp = uPreamp;

    if(globalUserVariable->gRefLevel>0.)
    {
        if(globalUserVariable->gPreamp == SA_ON)
        {
            globalUserVariable->gPreamp = SA_OFF;
        }
    }

    qreal tmpAttenValue = globalUserVariable->gAttenValue;

    if(globalUserVariable->gAtten == SA_AUTO)
    {
        if(globalUserVariable->gPreamp == SA_OFF)
        {
            if(globalUserVariable->gRefLevel-15.>0.)      tmpAttenValue = 30.;
            else if(globalUserVariable->gRefLevel-10.>0.) tmpAttenValue = 25.;
            else if(globalUserVariable->gRefLevel-5.>0.)  tmpAttenValue = 20.;
            else if(globalUserVariable->gRefLevel>0.)     tmpAttenValue = 15.;
            else if(globalUserVariable->gRefLevel+5.>0.)  tmpAttenValue = 10.;
            else if(globalUserVariable->gRefLevel+10.>0.) tmpAttenValue = 5.;


            if(globalUserVariable->gRefLevel+10.<=0.)     tmpAttenValue = 0.;
        }
        else
        {
            if(globalUserVariable->gRefLevel+5.>0.&&globalUserVariable->gRefLevel<=0) tmpAttenValue = 30.;
            else if(globalUserVariable->gRefLevel+10.>0.)                             tmpAttenValue = 25.;
            else if(globalUserVariable->gRefLevel+15.>0.)                             tmpAttenValue = 20.;
            else if(globalUserVariable->gRefLevel+20.>0.)                             tmpAttenValue = 15.;
            else if(globalUserVariable->gRefLevel+25.>0.)                             tmpAttenValue = 10.;
            else if(globalUserVariable->gRefLevel+30.>0.)                             tmpAttenValue = 5.;


            if(globalUserVariable->gRefLevel+30.<=0)                                  tmpAttenValue = 0.;
        }
    }
    else
    {
        if(globalUserVariable->gPreamp == SA_OFF)
        {
            if(globalUserVariable->gAttenValue - 50. > 0.)
                tmpAttenValue = 50.;
        }
        else
        {
            if(globalUserVariable->gAttenValue - 30. > 0.)
                tmpAttenValue = 30.;
        }
    }
    //*********************send control to FPGA

    if(globalUserVariable->gAutoRepeat)
    {
        if(tmpAttenValue == globalUserVariable->gAttenValue)
        {

        }
        else
        {
            globalUserVariable->gAttenValue = tmpAttenValue;
        }
    }
    else
    {
        globalUserVariable->gAttenValue = tmpAttenValue;
    }

    initTraceAverage();
    emit infoRefresh(SA_INFO_AMPT,SA_INFO_AMPT_PREAMP);

    //Johnson 190709
    //QThread::usleep(200000);
    setTriggerLevel(globalUserVariable->gTriggerLevel[globalUserVariable->gTriggerMode]);
}

/**
 * @brief getPreampStatus
 * @return
 */
quint32 controlInterface::getPreampStatus()
{
    return globalUserVariable->gPreamp;
}
/**
 * @brief setRefOffset
 * @param dRefOffset
 */
void controlInterface::setRefOffset(qreal dRefOffset)
{
    QString iVal = QString::number(dRefOffset);
    QString strCmd = ":AMPLitude:RLEVel:OFFSet ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    qreal lastRefOffset = globalUserVariable->gRefOffset;

    if(SPEC_AMPTD_MIN-globalUserVariable->gRefLevel > dRefOffset)
    {
        dRefOffset = SPEC_AMPTD_MIN-globalUserVariable->gRefLevel;
    }
    else if(dRefOffset > SPEC_AMPTD_MAX-globalUserVariable->gRefLevel)
    {
        dRefOffset = SPEC_AMPTD_MAX-globalUserVariable->gRefLevel;
    }
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gRefOffset == dRefOffset) return;
    }


    globalUserVariable->gRefOffset = dRefOffset;

    globalUserVariable->topLevel = globalUserVariable->gRefLevel+globalUserVariable->gRefOffset;
    globalUserVariable->lowLevel = globalUserVariable->topLevel - GRID_NUM_Y_TICKS*globalUserVariable->gScaleDiv;
    qreal diffValue = globalUserVariable->gRefOffset - lastRefOffset;

    for(qint32 i = 0;i<LIMIT_SELECTSUM;i++)
    {
        for(qint32 j =0;j<globalUserLimit->gTotalDot[i];j++)
        {
            globalUserLimit->gAmplitude[i][j] += diffValue;
        }
    }
    for(qint32 i = 0;i<SPUR_EM_DATE_MAX;i++)
    {
        globalUserVariable->gSpurEMPara[i].startLimit += diffValue;
        globalUserVariable->gSpurEMPara[i].stopLimit += diffValue;
    }
    emit infoRefresh(SA_INFO_AMPT,SA_INFO_AMPT_OFFSET);
}
/**
 * @brief getRefOffset
 * @return
 */
qreal controlInterface::getRefOffset()
{
    return globalUserVariable->gRefOffset;
}
/**
 * @brief setAutoScale
 */
void controlInterface::setAutoScale(quint32 uAutoScale)
{
    //globalUserVariable->gAutoScale = uAutoScale;
    //globalUserVariable->gAutoScale = globalUserVariable->gAutoScale == 1 ? 0 : 1;
    //if(!uAutoScale) return;
    //Tony 0403 Add limit for single
    if(globalUserVariable->gSweepType == SA_SINGLE)
    {
        return;
    }
    quint32 uFlag = 0;
    //****************set auto scale
    qreal AMax = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][0];
    for (qint32 k = 1; k < globalUserVariable->gSweepTracePoint; k++)
    {
        if (AMax < globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][k])
        {
            AMax = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][k];
        }
    }

    qreal AMin = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][0];
    for (qint32 k = 1; k < globalUserVariable->gSweepTracePoint; k++)
    {
        if (AMin > globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][k])
        {
            AMin = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][k];
        }
    }

    globalUserVariable->gScaleDiv = (AMax - AMin)/8;
    globalUserVariable->gRefLevel = AMax + globalUserVariable->gScaleDiv;

    //limit the rang of RefLevel and RefOffset
    if (SPEC_AMPTD_MIN > globalUserVariable->gRefLevel)
    {
        globalUserVariable->gRefLevel = SPEC_AMPTD_MIN;
    }
    else if(globalUserVariable->gRefLevel  > SPEC_AMPTD_MAX)
    {
        globalUserVariable->gRefLevel = SPEC_AMPTD_MAX;
    }

    if (SPEC_AMPTD_MIN <= globalUserVariable->gRefLevel && globalUserVariable->gRefLevel  <= SPEC_AMPTD_MAX)
    {
        if(globalUserVariable->gRefOffset < SPEC_AMPTD_MIN - globalUserVariable->gRefLevel)
        {
            globalUserVariable->gRefOffset = SPEC_AMPTD_MIN - globalUserVariable->gRefLevel;
        }
        else if( globalUserVariable->gRefOffset > SPEC_AMPTD_MAX - globalUserVariable->gRefLevel)
        {
            globalUserVariable->gRefOffset = SPEC_AMPTD_MAX - globalUserVariable->gRefLevel;
        }
    }

    globalUserVariable->topLevel = globalUserVariable->gRefLevel+globalUserVariable->gRefOffset;
    globalUserVariable->lowLevel = globalUserVariable->topLevel - 10*globalUserVariable->gScaleDiv;

    if(globalUserVariable->gRefLevel>0.)
    {
        if(globalUserVariable->gPreamp == SA_ON)
        {
            globalUserVariable->gPreamp = SA_OFF;
            //Pream SA_ON/SA_OFF Control 0503
        }
    }

    if(globalUserVariable->gAtten == SA_AUTO)
    {
        if(globalUserVariable->gPreamp == SA_OFF)
        {
            if(globalUserVariable->gRefLevel-15.>0.)      globalUserVariable->gAttenValue = 30.;
            else if(globalUserVariable->gRefLevel-10.>0.) globalUserVariable->gAttenValue = 25.;
            else if(globalUserVariable->gRefLevel-5.>0.)  globalUserVariable->gAttenValue = 20.;
            else if(globalUserVariable->gRefLevel>0.)     globalUserVariable->gAttenValue = 15.;
            else if(globalUserVariable->gRefLevel+5.>0.)  globalUserVariable->gAttenValue = 10.;
            else if(globalUserVariable->gRefLevel+10.>0.) globalUserVariable->gAttenValue = 5.;


            if(globalUserVariable->gRefLevel+10.<=0.)     globalUserVariable->gAttenValue = 0.;
        }
        else
        {
            if(globalUserVariable->gRefLevel+5.>0.&&globalUserVariable->gRefLevel<=0) globalUserVariable->gAttenValue = 30.;
            else if(globalUserVariable->gRefLevel+10.>0.)                             globalUserVariable->gAttenValue = 25.;
            else if(globalUserVariable->gRefLevel+15.>0.)                             globalUserVariable->gAttenValue = 20.;
            else if(globalUserVariable->gRefLevel+20.>0.)                             globalUserVariable->gAttenValue = 15.;
            else if(globalUserVariable->gRefLevel+25.>0.)                             globalUserVariable->gAttenValue = 10.;
            else if(globalUserVariable->gRefLevel+30.>0.)                             globalUserVariable->gAttenValue = 5.;


            if(globalUserVariable->gRefLevel+30.<=0)                                  globalUserVariable->gAttenValue = 0.;
        }
    }
    else
    {
        if(globalUserVariable->gPreamp == SA_OFF)
        {
            if(globalUserVariable->gAttenValue - 50. > 0.)
                globalUserVariable->gAttenValue = 50.;
        }
        else
        {
            if(globalUserVariable->gAttenValue - 30. > 0.)
                globalUserVariable->gAttenValue = 30.;
        }
    }

    QString iVal ;
    QString strCmd,tmpCmd;
    iVal = QString::number(globalUserVariable->gRefLevel);
    tmpCmd = ":AMPLitude:RLEVel ";
    strCmd = strCmd + tmpCmd + iVal;

    iVal = QString::number(globalUserVariable->gRefOffset);
    tmpCmd = ":AMPLitude:RLEVel:OFFSet ";
    strCmd = strCmd + "\n" + tmpCmd + iVal;

    iVal = QString::number(globalUserVariable->gScaleDiv);
    tmpCmd = ":AMPLitude:SCALe ";
    strCmd = strCmd + "\n" + tmpCmd + iVal;

    iVal = QString::number(globalUserVariable->gPreamp);
    tmpCmd = ":AMPLitude:PREAmp ";
    strCmd = strCmd + "\n" + tmpCmd + iVal;

    //
    iVal = QString::number(globalUserVariable->gAttenValue);
    tmpCmd = ":AMPLitude:ATTEnuation ";
    strCmd = strCmd + "\n" + tmpCmd + iVal;

    iVal = QString::number(globalUserVariable->gAtten);
    tmpCmd = ":AMPLitude:ATTEnuation:Auto ";
    strCmd = strCmd + "\n" + tmpCmd + iVal;

    emit sendSCPIcmd(strCmd);


    emit infoRefresh(SA_INFO_AMPT,SA_INFO_AMPT_AUTOLIMIT);
    //****************send control to FPGA

}

/**
 * @brief setAutoRbwStatus
 * @param uRbwStatus
 */
void controlInterface::setAutoRbwStatus(qint32 uRbwStatus)
{
    uRbwStatus = !!uRbwStatus;
    QString iVal = QString::number(uRbwStatus);
    QString strCmd = ":BANDwidth:RBW:AUTO ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||\
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE)
        {

            return;
        }
    }
    if(globalUserVariable->gAutoRepeat)
    {
        //if(globalUserVariable->gAutoRbw == uRbwStatus) return;
    }
    quint32 tempflag = 0;
    globalUserVariable->gAutoRbw = uRbwStatus;

    if (globalUserVariable->gAutoRbw == SA_ON)
    {
        bitaloth->ConfigureSweepCoupling(globalUserVariable->gAutoRbw,(qreal)globalUserVariable->gRbw,globalUserVariable->gAutoVbw,globalUserVariable->gVbw,1,globalUserVariable->gVbwtoRbw);
        if(globalUserVariable->grbwChangedbyFreq || SA_autoChangerbwflag)
        {
            if(globalUserVariable->gSpanMode != 1)
            {
                //bitaloth->ConfigureSweepCoupling(globalUserVariable->gAutoRbw,(qreal)globalUserVariable->gRbw,globalUserVariable->gAutoVbw,globalUserVariable->gVbw,1,globalUserVariable->gVbwtoRbw);
                if(globalUserVariable -> gcheckswitch != globalUserVariable -> goldcheckswitch)
                {
                    globalUserVariable -> goldcheckswitch = globalUserVariable -> gcheckswitch;
                }
                if(globalUserVariable->grbwChangedbyFreq || SA_autoChangerbwflag)
                {
                    globalUserVariable->convertBwToShm();
                }
            }
        }
    }
    initTraceAverage();
    emit infoRefresh(SA_INFO_BW,SA_INFO_BW_RBW_AUTO);
}
/**
 * @brief getRbwStatus
 * @return
 */
qint32 controlInterface::getRbwStatus()
{
    return globalUserVariable->gAutoRbw;
}

/**
 * @brief setRbwValue
 * @param uRbwValue
 */
void controlInterface::setRbwValue(quint32 uRbwValue)
{
    QString iVal = QString::number(uRbwValue);
    QString strCmd = ":BANDwidth:RBW ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||\
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE)
        {

            return;
        }
    }
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gRbw == uRbwValue) return;
    }
    //globalUserVariable->gAutoRbw = SA_OFF;
    qreal mminzerotime = 0.;
    quint32 tempflag = 0;
    //*****************set Rbw
    if(1 == globalUserVariable->gSpanMode)
    {
        //*****when span is zero span mode,the sweep mode is Fir
        if(uRbwValue <= 3001)
        {
            return;
        }
    }

    globalUserVariable->gRbw = uRbwValue;
    //*****************send control to FPGA
    bitaloth->ConfigureSweepCoupling(globalUserVariable->gAutoRbw,(qreal)globalUserVariable->gRbw,globalUserVariable->gAutoVbw,globalUserVariable->gVbw,1,globalUserVariable->gVbwtoRbw);
    if(globalUserVariable -> gcheckswitch != globalUserVariable -> goldcheckswitch)
    {
        globalUserVariable -> goldcheckswitch = globalUserVariable -> gcheckswitch;
    }
    globalUserVariable->convertBwToShm();

    if(globalUserVariable->gSpanMode)
    {
        mminzerotime = bitaloth->GetZeroSpanRbwMinms(NUM_SWEEP_POINT);

        //Johnson 190819
        if(getAutoSweepTimeStatus() == SA_OFF)
            globalUserVariable->gZeroSpanTime = globalUserVariable->gZeroSpanTime < mminzerotime ? mminzerotime : globalUserVariable->gZeroSpanTime;
        else
            globalUserVariable->gZeroSpanTime = mminzerotime;

        globalUserVariable->gSweepTime = globalUserVariable->gZeroSpanTime;
        bitaloth->GetZeroShmTimes(globalUserVariable->gSweepTime,NUM_SWEEP_POINT);
    }

    initTraceAverage();

    //Johnson 190820
    if(globalUserVariable->gSpanMode)
    {
        globalUserVariable->markerPositionReCalculatorFunc();
    }

    emit infoRefresh(SA_INFO_BW,SA_INFO_BW_RBW_VALUE);
}
/**
 * @brief getbwValue
 * @return
 */
quint64 controlInterface::getRbwValue()
{
    return globalUserVariable->gRbw;
}

/**
 * @brief controlInterface::setVbwtoRbw
 * @param value
 */
void controlInterface::setVbwtoRbw(qreal value)
{
    QString iVal = QString::number(value);
    QString strCmd = ":BANDwidth:RATIo ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||\
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE)
        {

            return;
        }
    }

    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gVbwtoRbw == value) return;
    }

    globalUserVariable->gVbwtoRbw = value;
    bitaloth->ConfigureSweepCoupling(globalUserVariable->gAutoRbw,globalUserVariable->gRbw,globalUserVariable->gAutoVbw,
                                     globalUserVariable->gVbw,1,globalUserVariable->gVbwtoRbw);
    return ;
}

/**
 * @brief controlInterface::getVbwtoRbw
 * @return
 */
qreal controlInterface::getVbwtoRbw()
{
    return globalUserVariable->gVbwtoRbw;
}

/**
 * @brief setAutoVbwStatus
 * @param uVbwStatus
 */
void controlInterface::setAutoVbwStatus(quint32 uVbwStatus)
{
    uVbwStatus = !!uVbwStatus;
    QString iVal = QString::number(uVbwStatus);
    QString strCmd = ":BANDwidth:VBW:AUTO ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||\
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE)
        {

            return;
        }
    }
    if(globalUserVariable->gAutoRepeat)
    {
        //if(globalUserVariable->gAutoVbw == uVbwStatus) return;
    }
    globalUserVariable->gAutoVbw = uVbwStatus;

    if (globalUserVariable->gAutoVbw == SA_ON)
    {
        bitaloth->ConfigureSweepCoupling(globalUserVariable->gAutoRbw,(qreal)globalUserVariable->gRbw,globalUserVariable->gAutoVbw,globalUserVariable->gVbw,1,globalUserVariable->gVbwtoRbw);
        if(globalUserVariable->grbwChangedbyFreq || SA_autoChangevbwflag)
        {
            globalUserVariable->convertBwToShm();
        }
    }
    initTraceAverage();
    emit infoRefresh(SA_INFO_BW,SA_INFO_BW_VBW_AUTO);
}
/**
 * @brief getVbwStatus
 * @return
 */
quint32 controlInterface::getVbwStatus()
{
    return globalUserVariable->gAutoVbw;
}
/**
 * @brief setVbwValues
 * @param uVbwValues
 */
void controlInterface::setVbwValue(quint32 uVbwValues)
{
    QString iVal = QString::number(uVbwValues);
    QString strCmd = ":BANDwidth:VBW ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||\
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE)
        {

            return;
        }
    }
    //    globalUserVariable->gAutoVbw = SA_OFF;
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gVbw == uVbwValues) return;
    }

    globalUserVariable->gVbw = uVbwValues;
    //****************send control to FPGA
    bitaloth->ConfigureSweepCoupling(globalUserVariable->gAutoRbw,(qreal)globalUserVariable->gRbw,globalUserVariable->gAutoVbw,globalUserVariable->gVbw,1,globalUserVariable->gVbwtoRbw);
    globalUserVariable->convertBwToShm();
    initTraceAverage();
    emit infoRefresh(SA_INFO_BW,SA_INFO_BW_VBW_VALUE);
}
/**
 * @brief getVbwValues
 * @return
 */
quint64 controlInterface::getVbwValue()
{
    return globalUserVariable->gVbw;
}
/**
 * @brief setSweepType
 * @param uSweepType
 */
void controlInterface::setSweepType(quint32 uSweepType)
{
    //if(globalUserVariable->gAutoRepeat)
    //{
    //if(globalUserVariable->gSweepType == uSweepType) return;
    //}
    uSweepType = !!uSweepType;
    QString iVal = QString::number(uSweepType);
    QString strCmd = ":SWEEp:CONTinuous ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    globalUserVariable->gSweepType = uSweepType;

    if(getCurrentMode() == SA_SPURIOUS_EMISSION_MASK_MODE ||\
            getCurrentMode() == SA_SPECTRUM_EMISSION_MASK_MODE)
    {
        if(globalUserVariable->gMeasureStatus == SA_OFF)
        {
            setMeasureStatus(SA_ON);
        }
        globalUserVariable->SecondaryAction = SA_NOT_USE;
    }

    //SA_Set_config_flag(IXT_SA_ConfigSweep,IXS_SA_SweepType);

    //Johnson 190412
    //Tony 0624 Do not send init trace average signal.
    blockSignals(true);
    initTraceAverage();
    blockSignals(false);
    emit infoRefresh(SA_INFO_SWEEP,SA_INFO_SWEEP_MODE);

}
/**
 * @brief getSweepType
 * @return
 */
quint32 controlInterface::getSweepType()
{
    return globalUserVariable->gSweepType;
}
/**
 * @brief setAutoSweepTimeStatus
 * @param uAutoSweepTimeStatus
 */
void controlInterface::setAutoSweepTimeStatus(quint32 uAutoSweepTimeStatus)
{
    uAutoSweepTimeStatus = !!uAutoSweepTimeStatus;

    QString iVal = QString::number(uAutoSweepTimeStatus);
    QString strCmd = ":SWEEp:TIME:AUTO ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||\
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE)
        {

            return;
        }
    }

    if(globalUserVariable->gAutoRepeat)
    {
        //if(globalUserVariable->gAutoSweepTime == uAutoSweepTimeStatus) return;
    }
    quint32 tempflag = 0;

    globalUserVariable->gAutoSweepTime = uAutoSweepTimeStatus;

    if (globalUserVariable->gAutoSweepTime == SA_ON)
    {
        globalUserVariable->gsweepAuto = 1;
        if(globalUserVariable->gSpanMode != 1)
        {
            qint32 iIndex = bitaloth->GetrbwIndex((qreal)globalUserVariable->gRbw);
            if(iIndex <= 6)
            {
                bitaloth->ParamConvertByRbw(iIndex);
                bitaloth->ConfigureFrequencyStartStop(globalUserVariable->gStartFreq,globalUserVariable->gStopFreq);
                if(globalUserVariable -> gcheckswitch != globalUserVariable -> goldcheckswitch)
                {
                    globalUserVariable -> goldcheckswitch = globalUserVariable -> gcheckswitch;
                }
            }
        }
        else
        {
            globalUserVariable->gSweepTime = bitaloth->GetZeroSpanRbwMinms(NUM_SWEEP_POINT);
            globalUserVariable->gZeroSpanTime = globalUserVariable->gSweepTime;
            bitaloth->GetZeroShmTimes(globalUserVariable->gSweepTime,NUM_SWEEP_POINT);
        }
    }
    else
    {
        globalUserVariable->gsweepAuto = 0;
    }
    //Tony 190710
    if(globalUserVariable->gSpanMode)
    {
        globalUserVariable->markerPositionReCalculatorFunc();
    }
    emit infoRefresh(SA_INFO_SWEEP,SA_INFO_SWEEP_TIME);
}
/**
 * @brief getAutoSweepTimeStatus
 * @return
 */
quint32 controlInterface::getAutoSweepTimeStatus()
{
    return globalUserVariable->gAutoSweepTime;
}
/**
 * @brief setSweepTime
 * @param dSweepTime unit is ms
 */
void controlInterface::setSweepTime(qreal dSweepTime)
{
    QString iVal = QString::number(dSweepTime);
    QString strCmd = ":SWEEp:TIME ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||\
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE)
        {

            return;
        }
    }
    //    globalUserVariable->gAutoSweepTime = SA_OFF;
    if(SA_ON == getAutoSweepTimeStatus())
    {
        this->blockSignals(true);
        setAutoSweepTimeStatus(SA_OFF);
        this->blockSignals(false);
    }
    qreal mminzerotime = 0.;
    //***************set sweepTime
    if(3 == globalUserVariable->ganamode)
    {
        return;
    }
    if(SWEEPTIMEMAX < dSweepTime) dSweepTime = SWEEPTIMEMAX;

    if(globalUserVariable->gAutoRepeat)
    {
        if(0. == globalUserVariable->gSweepTime - dSweepTime) return;
    }

    globalUserVariable->gSweepTime = dSweepTime;
    globalUserVariable->gmanSettimems = globalUserVariable->gSweepTime;
    //**************send control to FPGA
    if(globalUserVariable->gSpanMode != 1)
    {
        globalUserVariable->gmanSettimems = globalUserVariable->gmanSettimems < globalUserVariable->gautoMintimems ? globalUserVariable->gautoMintimems : globalUserVariable->gmanSettimems;
        bitaloth->SettingSweepTimeManmode(globalUserVariable->gmanSettimems, globalUserVariable->gautoMintimems);
    }
    else
    {
        mminzerotime = bitaloth->GetZeroSpanRbwMinms(NUM_SWEEP_POINT);
        globalUserVariable->gmanSettimems = globalUserVariable->gmanSettimems < mminzerotime ? mminzerotime : globalUserVariable->gmanSettimems;
        globalUserVariable->gZeroSpanTime = globalUserVariable->gmanSettimems;
        bitaloth->GetZeroShmTimes(globalUserVariable->gmanSettimems ,NUM_SWEEP_POINT);
    }
    globalUserVariable->gSweepTime = globalUserVariable->gmanSettimems;
    //Tony 190710
    if(globalUserVariable->gSpanMode)
    {
        globalUserVariable->markerPositionReCalculatorFunc();
    }
    emit infoRefresh(SA_INFO_SWEEP,SA_INFO_SWEEP_TIME);
}



/**
 * @brief getSweepTime
 * @return
 */
qreal controlInterface::getSweepTime()
{
    return globalUserVariable->gSweepTime;
}

/**
 * @brief controlInterface::setDotSweepTime
 * @param dDotSweepTime
 */
void controlInterface::setDotSweepTime(qreal dDotSweepTime)
{
    if(globalUserVariable->gSpanMode) return;

    QString iVal = QString::number(dDotSweepTime);
    QString strCmd = ":SWEEp:DOT:TIME ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(globalUserVariable->gAutoRepeat)
    {
        if(dDotSweepTime == globalUserVariable->gDotSweepTime) return;
    }

    if(getAutoDotSweepTimeStatus() == SA_AUTO)
    {
        setAutoDotSweepTime(SA_MANUAL);
    }

    globalUserVariable->gDotSweepTime = dDotSweepTime;

    globalUserVariable->gautoMintimems = 0.0;

    globalUserVariable->gautoMintimems += globalUserVariable->segmentNum * 0.8;
    bitaloth->RefCalSweepParams(globalUserVariable->ganamode);
}

/**
 * @brief controlInterface::getDotSweepTime
 * @return
 */
qreal controlInterface::getDotSweepTime()
{
    return globalUserVariable->gDotSweepTime;
}

/**
 * @brief controlInterface::setAutoDotSweepTime
 * @param uAutoDotSweepTimeStatus
 */
void controlInterface::setAutoDotSweepTime(quint32 uAutoDotSweepTimeStatus)
{
    if(globalUserVariable->gSpanMode) return;

    QString iVal = QString::number(uAutoDotSweepTimeStatus);
    QString strCmd = ":SWEEp:DOT:TIME:AUTO ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gAutoDotSweepTime == uAutoDotSweepTimeStatus) return;
    }

    globalUserVariable->gAutoDotSweepTime = uAutoDotSweepTimeStatus;

    if(globalUserVariable->gAutoDotSweepTime == SA_AUTO)
    {
        globalUserVariable->gautoMintimems = 0.0;
        globalUserVariable->gautoMintimems += globalUserVariable->segmentNum * 0.8;
        bitaloth->RefCalSweepParams(globalUserVariable->ganamode);
    }
}

/**
 * @brief controlInterface::getAutoDotSweepTimeStatus
 * @return
 */
qreal controlInterface::getAutoDotSweepTimeStatus()
{
    return globalUserVariable->gAutoDotSweepTime;
}

/**
 * @brief controlInterface::setFixSweepMode
 */
void controlInterface::setFixSweepMode(quint32 uFixSweepMode)
{

    QString iVal = QString::number(uFixSweepMode);
    QString strCmd = ":SWEEp:FIXEd ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(globalUserVariable->gSpanMode) return;

    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gFixDotSweepTime == uFixSweepMode) return;
    }
    globalUserVariable->gFixDotSweepTime = uFixSweepMode;

    globalUserVariable->gautoMintimems = 0.0;

    globalUserVariable->gautoMintimems += globalUserVariable->segmentNum * 0.8;
    bitaloth->RefCalSweepParams(globalUserVariable->ganamode);

}

/**
 * @brief controlInterface::getFixSweepMode
 * @return
 */
quint32 controlInterface::getFixSweepMode()
{
    return globalUserVariable->gFixDotSweepTime;
}

/**
 * @brief setSweepTime
 * @return
 */
void controlInterface::setZeroSpanTime(qreal mTime)
{
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gZeroSpanTime == mTime) return;
    }
    globalUserVariable->gZeroSpanTime = mTime;
    return;
}

/**
 * @brief getZeroSpanTime
 * @return
 */
qreal controlInterface::getZeroSpanTime()
{
    return globalUserVariable->gZeroSpanTime;
}
/**
 * @brief setTriggerMode
 * @param uTiggerMode
 */
void controlInterface::setTriggerMode(quint32 uTiggerMode)
{
    QString iVal = QString::number(uTiggerMode);
    QString strCmd = ":TRIGger:SOURce ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gTriggerMode == uTiggerMode) return;
    }
    if(uTiggerMode < 0 || uTiggerMode > 5)
    {
        return;
    }
    globalUserVariable->gTriggerMode = uTiggerMode;

    emit infoRefresh(SA_INFO_TRIGGER,SA_INFO_TRIGGER_MODE);
}
/**
 * @brief setTriggerDelayStatus
 * @param uStatus
 */
void controlInterface::setTriggerDelayStatus(qint32 uStatus,qint32 uMode)
{
    QString iVal = QString::number(uStatus);
    QString strCmd;
    if(uMode < 0 || uMode > 5)
    {
        strCmd = ":TRIGger:DELAy:STATe ";
    }
    else
    {
        strCmd = QString(":TRIGger:%1:DELAy:STATe ").arg(QString(triggerMode[uMode]));
    }
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    qint32 mTriggerMode ;
    if(uMode < 0)
    {
        mTriggerMode = globalUserVariable->gTriggerMode;
    }
    else
    {
        mTriggerMode = uMode;
    }
    if(globalUserVariable->gAutoRepeat)
    {
        //if(globalUserVariable->gTriggerDelayStatus[mTriggerMode] == uStatus) return;
    }
    if(mTriggerMode == SA_TRIGGER_FREE_RUN || mTriggerMode == SA_TRIGGER_GPS) return;
    globalUserVariable->gTriggerDelayStatus[mTriggerMode] = uStatus;

    return;
}

/**
 * @brief getTriggerDelayStatus
 * @return
 */
qint32 controlInterface::getTriggerDelayStatus(qint32 uMode)
{
    qint32 mTriggerMode ;
    if(uMode < 0)
    {
        mTriggerMode = globalUserVariable->gTriggerMode;
    }
    else
    {
        mTriggerMode = uMode;
    }
    if(mTriggerMode == SA_TRIGGER_FREE_RUN || mTriggerMode == SA_TRIGGER_GPS) return -1;
    return globalUserVariable->gTriggerDelayStatus[mTriggerMode];
}
/**
 * @brief controlInterface::setTriggerDelayValue
 * @param uValue
 * @note param's unit is ms
 */
void controlInterface::setTriggerDelayValue(qreal uValue, qint32 uMode)
{
    QString iVal = QString::number(uValue);
    QString strCmd;
    if(uMode < 0 || uMode > 5)
    {
        strCmd = ":TRIGger:DELAy ";
    }
    else
    {
        strCmd = QString(":TRIGger:%1:DELAy ").arg(QString(triggerMode[uMode]));
    }
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    qint32 mTriggerMode ;
    if(uMode < 0)
    {
        mTriggerMode = globalUserVariable->gTriggerMode;
    }
    else
    {
        mTriggerMode = uMode;
    }

    if(uValue<0.) uValue = 0.;
    else if(uValue>23000.) uValue = 23000.;

    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gTriggerDelayValue[mTriggerMode] == uValue) return;
    }
    if(mTriggerMode == SA_TRIGGER_FREE_RUN || mTriggerMode == SA_TRIGGER_GPS) return;
    globalUserVariable->gTriggerDelayStatus[mTriggerMode] = SA_ON;
    globalUserVariable->gTriggerDelayValue[mTriggerMode] = uValue;
    return;
}
/**
 * @brief getTriggerDelayValue
 * @return
 */
qreal controlInterface::getTriggerDelayValue(qint32 uMode)
{
    qint32 mTriggerMode ;
    if(uMode < 0)
    {
        mTriggerMode = globalUserVariable->gTriggerMode;
    }
    else
    {
        mTriggerMode = uMode;
    }
    if(mTriggerMode == SA_TRIGGER_FREE_RUN || mTriggerMode == SA_TRIGGER_GPS) return -1;
    return globalUserVariable->gTriggerDelayValue[mTriggerMode];
}
/**
 * @brief setTriggerSlope
 * @param mSlope uMode
 */
void controlInterface::setTriggerSlope(qint32 mSlope,qint32 uMode)
{
    QString iVal = QString::number(mSlope);
    QString strCmd;
    if(uMode < 0 || uMode > 5)
    {
        strCmd = ":TRIGger:SLOPe ";
    }
    else
    {
        strCmd = QString(":TRIGger:%1:SLOPe ").arg(QString(triggerMode[uMode]));
    }
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    qint32 mTriggerMode ;
    if(uMode < 0)
    {
        mTriggerMode = globalUserVariable->gTriggerMode;
    }
    else
    {
        mTriggerMode = uMode;
    }
    if(globalUserVariable->gAutoRepeat)
    {
        //if(globalUserVariable->gTriggerSlope[mTriggerMode] == mSlope) return;
    }
    if(mTriggerMode == SA_TRIGGER_FREE_RUN || mTriggerMode == SA_TRIGGER_GPS || mTriggerMode == SA_TRIGGER_PERIODIC_TIMER) return;
    globalUserVariable->gTriggerSlope[mTriggerMode] = mSlope;
    return;
}
/**
 * @brief getTriggerSlope
 * @param uMode
 */
qint32 controlInterface::getTriggerSlope(qint32 uMode)
{
    qint32 mTriggerMode ;
    if(uMode < 0)
    {
        mTriggerMode = globalUserVariable->gTriggerMode;
    }else{
        mTriggerMode = uMode;
    }
    if(mTriggerMode == SA_TRIGGER_FREE_RUN || mTriggerMode == SA_TRIGGER_GPS || mTriggerMode == SA_TRIGGER_PERIODIC_TIMER) return -1;
    return globalUserVariable->gTriggerSlope[mTriggerMode];
}
/**
 * @brief setTriggerLevel
 * @param mLevel_dBm uMode
 */
void controlInterface::setTriggerLevel(qreal mLevel_dBm,qint32 uMode)
{
    QString iVal = QString::number(mLevel_dBm);
    QString strCmd;
    if(uMode < 0 || uMode > 5)
    {
        strCmd = ":TRIGger:LEVEl ";
    }
    else
    {
        strCmd = QString(":TRIGger:%1:LEVEl ").arg(QString(triggerMode[uMode]));
    }
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    qint32 mTriggerMode ;
    if(uMode < 0)
    {
        mTriggerMode = globalUserVariable->gTriggerMode;
    }
    else
    {
        mTriggerMode = uMode;
    }

    if(mLevel_dBm > 20.) mLevel_dBm = 20.;
    else if(mLevel_dBm < -170.) mLevel_dBm = -170.;

    /*if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gTriggerLevel[mTriggerMode] == mLevel_dBm) return;
    }*/
    if(mTriggerMode != SA_TRIGGER_VIDEO && mTriggerMode != SA_TRIGGER_RF_BURST) return;
    globalUserVariable->gTriggerLevel[mTriggerMode] = mLevel_dBm;

    return ;
}
/**
 * @brief getTriggerLevel
 * @param uMode
 */
qreal controlInterface::getTriggerLevel(qint32 uMode)
{
    qint32 mTriggerMode ;
    if(uMode < 0)
    {
        mTriggerMode = globalUserVariable->gTriggerMode;
    }else{
        mTriggerMode = uMode;
    }
    if(mTriggerMode != SA_TRIGGER_VIDEO && mTriggerMode != SA_TRIGGER_RF_BURST) return -1;
    return globalUserVariable->gTriggerLevel[mTriggerMode];
}
/**
 * @brief setTriggerPerTimer
 * @param mTimeMs
 * @note param's unit is ms
 */
void controlInterface::setTriggerPerTimer(qreal mTimeMs)
{
    QString iVal = QString::number(mTimeMs);
    QString strCmd = ":TRIGger:PERiodic ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

#if 0
    if(mTimeMs<0.) mTimeMs = 0.;
    else if(mTimeMs>23000.) mTimeMs = 23000.;
#else
    #if 0
    if(mTimeMs < globalUserVariable->sumSweeptime) mTimeMs = globalUserVariable->sumSweeptime;
    #endif
#endif

    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gTriggerPerTimer == mTimeMs) return;
    }

    if(globalUserVariable->gTriggerMode != SA_TRIGGER_PERIODIC_TIMER) return;

    globalUserVariable->gTriggerPerTimer = mTimeMs;
    return ;
}
/**
 * @brief getTriggerPerTimer
 * @param
 */
qreal controlInterface::getTriggerPerTimer()
{
    return globalUserVariable->gTriggerPerTimer;
}

#if 0
/**
 * @brief controlInterface::setSweepSpeed
 * @param uSweepSpeed
 */
void controlInterface::setSweepSpeed(quint32 uSweepSpeed)
{
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gSweepSpeed == uSweepSpeed) return;
    }
    globalUserVariable->gSweepSpeed = uSweepSpeed;
}

/**
 * @brief getSweepSpeed
 * @return
 */
quint32 controlInterface::getSweepSpeed()
{
    return globalUserVariable->gSweepSpeed;
}
#endif

/**
 * @brief getTriggerMode
 * @return
 */
quint32 controlInterface::getTriggerMode()
{
    return globalUserVariable->gTriggerMode;
}
/**
 * @brief setAutoAttenTrackStatus
 * @param uAutoAttenTrackStatus
 */
void controlInterface::setAutoAttenTrackStatus(quint32 uAutoAttenTrackStatus)
{
    globalUserVariable->gAutoAttenTrack = uAutoAttenTrackStatus;
}
/**
 * @brief getAutoAttenTrackStatus
 * @return
 */
quint32 controlInterface::getAutoAttenTrackStatus()
{
    return globalUserVariable->gAutoAttenTrack;
}

//**********************Johnson 190410************************//
void controlInterface::setZeroRestrainAtten(qint32 dValue)
{
    globalUserVariable->gZeroRestrainAtten = dValue;
}
qreal controlInterface::getZeroRestrainAtten()
{
    return globalUserVariable->gZeroRestrainAtten;
}
void controlInterface::setZeroRestrainPhase(qreal dValue)
{
    globalUserVariable->gZeroRestrainPhase = dValue;
}
qreal controlInterface::getZeroRestrainPhase()
{
    return globalUserVariable->gZeroRestrainPhase;
}
//***********************************************************//

/**
 * @brief controlInterface::setZeroRestrain
 * @param dZeroRestrainAttenValue
 * @param dZeroRestrainPhaseVale
 * @date  20190423
 * @author Johnson
 */
void controlInterface::setZeroRestrain(qint32 dZeroRestrainAttenValue,qreal dZeroRestrainPhaseVale)
{
    globalUserVariable->gZeroRestrainAtten = dZeroRestrainAttenValue;
    globalUserVariable->gZeroRestrainPhase = dZeroRestrainPhaseVale;

    QThread::usleep(100000);
}

/**
 * @brief setTraceSelect
 * @param uTraceSelect
 */
void controlInterface::setTraceSelect(qint32 uTraceSelect)
{
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE
                )
        {
            return;
        }
    }
    if(uTraceSelect <0 || uTraceSelect >= TRACE_CNT_TOTAL ) return;
    if(globalUserVariable->gAutoRepeat)
    {
        //if(globalUserVariable->gTraceSelect == uTraceSelect) return;
    }
    globalUserVariable->gTraceSelect = uTraceSelect;
    emit infoRefresh(SA_INFO_TRACE,SA_INFO_TRACE_INDEX);
}
/**
 * @brief getTraceSelect
 * @return
 */
qint32 controlInterface::getTraceSelect()
{
    return globalUserVariable->gTraceSelect;
}
/**
 * @brief setTraceType
 * @param traceType
 */
void controlInterface::setTraceType(qint32 traceType,qint32 traceIndex)
{
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE)
        {
            return;
        }
    }
    //Tony 0123
    if(traceIndex < 0 || traceIndex >= MARKER_TOTAL_CNT)
    {
        traceIndex = globalUserVariable->gTraceSelect;
    }
    if(traceType < SA_CLEAR_WRITE || traceType > SA_TRACE_AVE)
    {
        return;
    }
    QString strCmd;
    QString iVal = QString::number(traceType);
    strCmd = QString(":TRACe:%1:TYPE ").arg(QString::number(traceIndex + 1));
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    //globalUserVariable->gTraceSelect = traceSelect;
    if(traceType == SA_TRACE_AVE)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK)
        {
            setMeasureStatus(SA_ON);
        }
        globalUserVariable->gTraceAverage[traceIndex] = SA_ON;
        globalUserVariable->gAverageNo[traceIndex] = 0;
        globalUserVariable->greAvager[traceIndex] = 1;
        traceType = SA_CLEAR_WRITE;
    }else
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK)
        {
            setMeasureStatus(SA_ON);
        }
        globalUserVariable->gTraceAverage[traceIndex] = SA_OFF;
        globalUserVariable->gAverageNo[traceIndex] = 0;
        globalUserVariable->greAvager[traceIndex] = 1;
    }

    globalUserVariable->gTraceType[traceIndex] = traceType;
    if(traceType == SA_MAX_HOLD || traceType == SA_MIN_HOLD)
    {
        globalUserVariable->uMinMaxHoldReadComplete = 0;
        memcpy( globalUserVariable->gTraceMeasureVal[traceIndex], globalUserVariable->gOriginalMeasureVal, sizeof(qreal) * globalUserVariable->gSweepTracePoint );
    }
    else if(traceType == SA_VIEW)
    {
        globalUserVariable->gViewAction[traceIndex] = SA_ON;
    }
    if(traceType != SA_MAX_HOLD && traceType != SA_MIN_HOLD)
    {
        #if 0
        SA_sm_config_sweep->uMinMaxHoldComplete = 1;
        #endif
    }
    emit infoRefresh(SA_INFO_TRACE,SA_INFO_TRACE_TYPE);
}
/**
 * @brief getTraceType
 * @return
 */
qint32 controlInterface::getTraceType(qint32 traceIndex)
{
    qint32 mType;
    //Tony 0123
    if(traceIndex < 0 || traceIndex >= MARKER_TOTAL_CNT)
    {
        traceIndex = globalUserVariable->gTraceSelect;
    }
    if(globalUserVariable->gTraceType[traceIndex] == SA_CLEAR_WRITE)
    {
        if(getTraceAverageStatus(traceIndex) == SA_ON)
            mType = SA_TRACE_AVE;
        else
            mType = globalUserVariable->gTraceType[traceIndex];

    }else{
        mType = globalUserVariable->gTraceType[traceIndex];
    }
    return mType;
}

/**
 * @brief controlInterface::setTraceStatus
 * @param traceStatus
 */
void controlInterface::setTraceStatus(qint32 traceStatus)
{

}

/**
 * @brief controlInterface::getTraceStatus
 * @return
 */
qint32 controlInterface::getTraceStatus()
{
    return 1;
}
/**
 * @brief setTraceAverageStatus
 * @param traceAverageStatus
 */
void controlInterface::setTraceAverageStatus(qint32 traceAverageStatus,qint32 traceIndex)
{
    if(traceIndex < 0 || traceIndex >= TRACE_CNT_TOTAL)
    {
        traceIndex = globalUserVariable->gTraceSelect;
    }

    globalUserVariable->gTraceAverage[traceIndex] = traceAverageStatus;
    globalUserVariable->gAverageNo[traceIndex] = 0;
    globalUserVariable->greAvager[traceIndex] = 1;
    if(traceAverageStatus == SA_ON)
    {
        #if 0
        SA_sm_config_sweep->uAllSweepCompleteFlag = 0;
        #endif
        if(getTraceType(traceIndex) != SA_CLEAR_WRITE)
            globalUserVariable->gTraceType[traceIndex] = SA_CLEAR_WRITE;
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK)
        {
            setMeasureStatus(SA_ON);
        }
    }

    emit infoRefresh(SA_INFO_TRACE,SA_INFO_TRACE_AVE);
}
/**
 * @brief getTraceAverageStatus
 * @return
 */
qint32 controlInterface::getTraceAverageStatus(qint32 traceIndex)
{
    if(traceIndex < 0 || traceIndex >= TRACE_CNT_TOTAL)
    {
        traceIndex = globalUserVariable->gTraceSelect;
    }
    return globalUserVariable->gTraceAverage[traceIndex];
}
/**
 * @brief setTraceAverageCount
 * @param traceAverageCount
 */
void controlInterface::setTraceAverageCount(qint32 traceAverageCount,qint32 traceIndex)
{

    if(traceIndex < 0 || traceIndex >= TRACE_CNT_TOTAL)
    {
        traceIndex = globalUserVariable->gTraceSelect;
    }

    QString strCmd;
    QString iVal = QString::number(traceAverageCount);
    strCmd = QString(":TRACe:%1:AVECount ").arg(QString::number(traceIndex + 1));
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(globalUserVariable->gTraceAverage[traceIndex] == SA_OFF)
        setTraceAverageStatus(SA_ON,traceIndex);
    //        return;

    traceAverageCount = traceAverageCount <= 0 ? 1 : traceAverageCount;
    traceAverageCount = traceAverageCount > 10000 ? 10000 : traceAverageCount;
    globalUserVariable->gAverageCount[traceIndex] = traceAverageCount;
    globalUserVariable->greAvager[traceIndex] = 1;
    return ;
}
/**
 * @brief getTraceAverageCount
 * @return
 */
qint32 controlInterface::getTraceAverageCount(qint32 traceIndex)
{
    if(traceIndex < 0 || traceIndex >= TRACE_CNT_TOTAL)
    {
        traceIndex = globalUserVariable->gTraceSelect;
    }
    return globalUserVariable->gAverageCount[traceIndex];
}

/**
 * @brief setSuspendFunc
 * @return
 */
void controlInterface::setSuspendFunc(qint32 isSuspend)
{
    globalUserVariable->traceSusFlag = isSuspend;
    return;
}
/**
 * @brief getSuspendFunc
 * @return
 */
qint32 controlInterface::getSuspendFunc()
{
    return globalUserVariable->traceSusFlag;
}

/**
 * @brief setTraceViewStatus
 * @param traceViewStatus,traceIndex
 */
void controlInterface::setTraceViewStatus(qint32 traceViewStatus,qint32 traceIndex)
{
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE
                )
        {

            return;
        }
    }
    if(traceIndex < 0 || traceIndex >= TRACE_CNT_TOTAL)
    {
        traceIndex = globalUserVariable->gTraceSelect;
    }

    QString strCmd;
    QString iVal = QString::number(traceViewStatus);
    strCmd = QString(":TRACe:%1:DISPlay ").arg(QString::number(traceIndex + 1));
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(globalUserVariable->gAutoRepeat)
    {
        //if(globalUserVariable->gTraceView[traceIndex] == traceViewStatus) return;
    }
    globalUserVariable->gTraceView[traceIndex] = traceViewStatus;

    if(traceViewStatus)
    {
        setTraceSelect(traceIndex);
    }
    else
    {
        for(qint32 i = TRACE_CNT_TOTAL - 1;i>= 0;i--)
        {
            if(getTraceViewStatus(i) == SA_ON)
            {
                setTraceSelect(i);
                break;
            }
        }
    }

    emit infoRefresh(SA_INFO_TRACE,SA_INFO_TRACE_VIEW);
    return;
}
/**
 * @brief getTraceViewStatus
 * @return
 */
qint32 controlInterface::getTraceViewStatus(qint32 traceIndex)
{
    if(traceIndex < 0 || traceIndex >= TRACE_CNT_TOTAL)
    {
        traceIndex = globalUserVariable->gTraceSelect;
    }
    return globalUserVariable->gTraceView[traceIndex];
}
/**
 * @brief setDetectorMode
 * @param uTraceDetectorMode
 */
void controlInterface::setDetectorMode(quint32 uTraceDetectorMode)
{
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE)
        {
            return;
        }
    }
    QString strCmd;
    QString iVal = QString::number(uTraceDetectorMode);
    strCmd = ":TRACe:DETEctor ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(uTraceDetectorMode < SA_AUTO_DETECTOR || uTraceDetectorMode > SA_RMS)
    {
        return;
    }

    for(qint32 i=0;i<MARKER_TOTAL_CNT;i++)
    {
        if(globalUserVariable->gMarkerNoise[i] == SA_ON)
        {
            uTraceDetectorMode = SA_SAMPLE;
            break;
        }
    }

    if(globalUserVariable->gAutoRepeat)
    {
        //if(globalUserVariable->gDetectorMode == uTraceDetectorMode) return;
    }

    globalUserVariable->gDetectorMode = uTraceDetectorMode;
    emit infoRefresh(SA_INFO_TRACE,SA_INFO_TRACE_DETECTOR);
}
/**
 * @brief getDetectorMode
 * @return
 */
quint32 controlInterface::getDetectorMode()
{
    return globalUserVariable->gDetectorMode;
}
/**
 * @brief setMarkerSelect
 * @param markerSelect
 */
void controlInterface::setMarkerSelect(qint32 markerSelect)
{
    if(markerSelect < 0 || markerSelect >6) return;
    if(globalUserVariable->gAutoRepeat)
    {
        //if(globalUserVariable->gMarkerSelect == markerSelect) return;
    }
    QString iVal = QString::number(markerSelect + 1);
    QString strCmd = ":MARKer:SELEct ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    globalUserVariable->gMarkerSelect = markerSelect;
    emit infoRefresh(SA_INFO_MARKER,SA_INFO_MARKER_INDEX);
}
/**
 * @brief getMarkerSelect
 * @return
 */
qint32 controlInterface::getMarkerSelect()
{
    return globalUserVariable->gMarkerSelect;
}
/**
 * @brief setMarkerNoiseStatus
 * @param markerNoiseStatus
 */
void controlInterface::setMarkerNoiseStatus(qint32 markerNoiseStatus,qint32 markerIndex)
{
    //Tony 0123
    if(markerIndex < 0 || markerIndex >= MARKER_TOTAL_CNT)
    {
        markerIndex = globalUserVariable->gMarkerSelect;
    }

    QString strCmd;
    QString iVal = QString::number(markerNoiseStatus);
    strCmd = QString(":MARKer:%1:NOISe:STATe ").arg(QString::number(markerIndex + 1));
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(globalUserVariable->gAutoRepeat)
    {
        //if(globalUserVariable->gMarkerNoise[markerIndex] == markerNoiseStatus) return;
    }

    globalUserVariable->gMarkerNoise[markerIndex] = markerNoiseStatus;

    if(globalUserVariable->gMarkerNoise[markerIndex] == SA_ON)
    {
        globalUserVariable->gTmpDetectorMode = globalUserVariable->gDetectorMode;
        if(globalUserVariable->gDetectorMode != SA_SAMPLE)
        {
            setDetectorMode(SA_SAMPLE);
        }
        /*      qreal markerLevel = (qreal)globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][globalUserVariable->gMarkerRefPos[markerIndex]] + globalUserVariable->gRefOffset;
        globalUserVariable->gMarkerNoiseValue[markerIndex] = markerLevel -10*log10(globalUserVariable->gRbw);*/ //unit is dBm/Hz  dBc/Hz
    }
    else
    {
        for(qint32 i = 0;i<MARKER_TOTAL_CNT;i++)
        {
            if(globalUserVariable->gMarkerNoise[i] == SA_ON)
            {
                return;
            }
        }
        if(globalUserVariable->gTmpDetectorMode != SA_SAMPLE) setDetectorMode(globalUserVariable->gTmpDetectorMode);
    }
    emit infoRefresh(SA_INFO_TRACE,SA_INFO_TRACE_DETECTOR);
}
/**
 * @brief getMarkerNoiseStatus
 * @return
 */
qint32 controlInterface::getMarkerNoiseStatus(qint32 markerIndex)
{
    //Tony 0123
    if(markerIndex < 0 || markerIndex >= MARKER_TOTAL_CNT)
    {
        markerIndex = globalUserVariable->gMarkerSelect;
    }
    return globalUserVariable->gMarkerNoise[markerIndex];
}

/**
 * @brief controlInterface::setMarkerFreqCountStatus
 * @param markerCountStatus
 * @param markerIndex
 */
void controlInterface::setMarkerFreqCountStatus(qint32 markerCountStatus,qint32 markerIndex)
{
    if(markerIndex < 0 || markerIndex >= MARKER_TOTAL_CNT)
    {
        markerIndex = globalUserVariable->gMarkerSelect;
    }
    QString strCmd;
    QString iVal = QString::number(markerCountStatus);
    strCmd = QString(":MARKer:%1:FCOUnt:STATe ").arg(QString::number(markerIndex + 1));
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gMarkerFreqCount[markerIndex] == markerCountStatus) return;
    }

    if(globalUserVariable->gSpanFreq == 0) return;

    globalUserVariable->gMarkerFreqCount[markerIndex] = markerCountStatus;
    //FPGA control undo
    return ;
}

/**
 * @brief controlInterface::getMarkerFreqCountStatus
 * @return
 */
qint32 controlInterface::getMarkerFreqCountStatus(qint32 markerIndex)
{
    if(markerIndex < 0 || markerIndex >= MARKER_TOTAL_CNT)
    {
        markerIndex = globalUserVariable->gMarkerSelect;
    }
    return globalUserVariable->gMarkerFreqCount[markerIndex];
}

/**
 * @brief setMarkerViewStatus
 * @param markerViewStatus
 */
void controlInterface::setMarkerViewStatus(qint32 markerViewStatus, qint32 markerIndex)
{
    markerViewStatus = !!markerViewStatus;
    //Tony 0123
    if(markerIndex < 0 || markerIndex >= MARKER_TOTAL_CNT)
    {
        markerIndex = globalUserVariable->gMarkerSelect;
    }

    QString strCmd;
    QString iVal = QString::number(markerViewStatus);
    strCmd = QString(":MARKer:%1:DISPlay ").arg(QString::number(markerIndex + 1));
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    globalUserVariable->gMarkerView[markerIndex] = markerViewStatus;
    if(markerViewStatus == SA_ON)
    {
        globalUserVariable->gMarkerRefPos[ markerIndex] = (qint32) (globalUserVariable->gSweepTracePoint / 2 );
        globalUserVariable->gMarkerDeltaPos[ markerIndex] = globalUserVariable->gMarkerRefPos[ markerIndex];

        if(!globalUserVariable->gSpanMode)
        {
            globalUserVariable->gMarkerRefFreq[markerIndex] = globalUserVariable->gCenterFreq;
            globalUserVariable->gMarkerDeltaFreq[markerIndex] = globalUserVariable->gCenterFreq;
        }else
        {
            globalUserVariable->gMarkerRefTime[markerIndex]=globalUserVariable->gSweepTime/2;
            globalUserVariable->gMarkerDeltaTime[markerIndex]=globalUserVariable->gSweepTime/2;
        }
    }

    //markerOnCountFunc()
    SA_guiDrawSet.markerOnCount = 0;
    for (qint32 i = 0; i < MARKER_TOTAL_CNT; i++)
    {
        if (globalUserVariable->gMarkerView[i] == SA_ON)
            ++SA_guiDrawSet.markerOnCount ;
    }

    globalUserLimit-> gridAxisCalculatorFunc();
    if(markerViewStatus == SA_ON)
    {
        globalUserVariable->gMarkerMarkerTmpRefPos[markerIndex]= globalUserVariable->gMarkerRefPos[markerIndex];
        globalUserVariable->gMarkerTmpRefAmpt[markerIndex] = (qreal)globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][globalUserVariable->gMarkerRefPos[markerIndex]] + globalUserVariable->gRefOffset;
        globalUserVariable->gMarkerRefDelta = 1;
    }
    emit infoRefresh(SA_INFO_MARKER,SA_INFO_MARKER_VIEW);
}
/**
 * @brief setMkrViewForResume
 * @param markerViewStatus
 */
void controlInterface::setMkrViewForResume(qint32 markerViewStatus, qint32 markerIndex)
{
    //Tony 0123
    if(markerIndex < 0 || markerIndex >= MARKER_TOTAL_CNT)
    {
        markerIndex = globalUserVariable->gMarkerSelect;
    }
    globalUserVariable->gMarkerView[markerIndex] = markerViewStatus;
    SA_guiDrawSet.markerOnCount = 0;
    for (qint32 i = 0; i < MARKER_TOTAL_CNT; i++)
    {
        if(globalUserVariable->gMarkerView[i] == SA_ON)
            ++SA_guiDrawSet.markerOnCount ;
    }

    globalUserLimit->gridAxisCalculatorFunc();
    if(markerViewStatus == SA_ON)
    {
        //globalUserVariable->gMarkerMarkerTmpRefPos[markerIndex]= globalUserVariable->gMarkerRefPos[markerIndex];
        //globalUserVariable->gMarkerTmpRefAmpt[markerIndex] = (qreal)globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][globalUserVariable->gMarkerRefPos[markerIndex]] + globalUserVariable->gRefOffset;
        globalUserVariable->gMarkerRefDelta = 1;
    }
    emit infoRefresh(SA_INFO_MARKER,SA_INFO_MARKER_VIEW);
}


/**
 * @brief getMarkerViewStatus
 * @return
 */
qint32 controlInterface::getMarkerViewStatus(qint32 markerIndex)
{
    if(markerIndex < 0 || markerIndex >= MARKER_TOTAL_CNT)
    {
        markerIndex = globalUserVariable->gMarkerSelect;
    }
    return globalUserVariable->gMarkerView[ markerIndex];
}
/**
 * @brief setMarkerType
 * @param markerType
 */
void controlInterface::setMarkerType(qint32 markerType,qint32 markerIndex)
{
    //    if(globalUserVariable->gMarkerView[ globalUserVariable->gMarkerSelect] == SA_OFF) return;
    if(markerType < 0 || markerType > 2) return;
    //markerOnCountFunc()
    //Tony 0123
    if(markerIndex < 0 || markerIndex >= MARKER_TOTAL_CNT)
    {
        markerIndex = globalUserVariable->gMarkerSelect;
    }
    QString strCmd;
    QString iVal = QString::number(markerType);
    strCmd = QString(":MARKer:%1:TYPE ").arg(QString::number(markerIndex + 1));
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);


    SA_guiDrawSet.markerOnCount = 0;
    for (qint32 i = 0; i < MARKER_TOTAL_CNT; i++)
    {
        if (globalUserVariable->gMarkerView[i] == SA_ON)
            ++SA_guiDrawSet.markerOnCount ;
    }

    globalUserLimit-> gridAxisCalculatorFunc();
    globalUserVariable->gMarkerType[markerIndex] = markerType;

    if(markerType == DELTA)
    {
        globalUserVariable->gMarkerDeltaPos[markerIndex] = globalUserVariable->gMarkerRefPos[markerIndex];
        globalUserVariable->gMarkerDeltaFreq[markerIndex] = globalUserVariable->gMarkerRefFreq[markerIndex];
        globalUserVariable->gMarkerDeltaTime[markerIndex] = globalUserVariable->gMarkerRefTime[markerIndex];

        globalUserVariable->gMarkerMarkerTmpRefPos[markerIndex]= globalUserVariable->gMarkerRefPos[markerIndex];
        globalUserVariable->gMarkerTmpRefAmpt[markerIndex] = (qreal)globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][globalUserVariable->gMarkerRefPos[markerIndex]] + globalUserVariable->gRefOffset;
        globalUserVariable->gMarkerRefDelta = 1;
    }
    emit infoRefresh(SA_INFO_MARKER,SA_INFO_MARKER_VIEW);
}
qint32 controlInterface::getMarkerType(qint32 markerIndex)
{
    //Tony 0123
    if(markerIndex < 0 || markerIndex >= MARKER_TOTAL_CNT)
    {
        markerIndex = globalUserVariable->gMarkerSelect;
    }
    return globalUserVariable->gMarkerType[markerIndex];
}
/**
 * @brief setMarkerToCF
 */
void controlInterface::setMarkerToCF()
{
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }
    QString strCmd = ":MARKer:TO:CENTer";
    emit sendSCPIcmd(strCmd);

    if (globalUserVariable->gMarkerView[ globalUserVariable->gMarkerSelect] == SA_ON)
    {
        if (globalUserVariable->gMarkerType[ globalUserVariable->gMarkerSelect] == REF)
            globalUserVariable->gCenterFreq = globalUserVariable->gMarkerRefFreq[globalUserVariable->gMarkerSelect] ;
        else
            globalUserVariable->gCenterFreq = globalUserVariable->gMarkerDeltaFreq[globalUserVariable->gMarkerSelect] ;

        globalUserVariable->adjustFreqByCer();
        globalUserVariable->stepFreqCalculatorFunc();
        globalUserVariable->markerPositionReCalculatorFunc();
        //***********************************logic control****************************
        unsigned long tempFlag = 0.;
        if(globalUserVariable->gZeroSpanAction)
        {
            globalUserVariable->gZeroSpanAction = SA_OFF;

            //Johnson 190425
            if(globalUserVariable->uIFMode != SA_AUTO_IFMODE)
            {
                globalUserVariable->uIFMode = SA_AUTO_IFMODE;
            }

            //Johnson 190912
            if(globalUserVariable->gGateViewStatus == SA_GATE_VIEW_OPEN)
            {
                globalUserVariable->gGateViewStatus = SA_GATE_VIEW_CLOSE;
                globalUserVariable->gGateSweepSpanChange = 0;
            }
        }

        bitaloth->ConfigureFrequencyStartStop(globalUserVariable->gStartFreq,globalUserVariable->gStopFreq);
        if(globalUserVariable->grbwChangedbyFreq)
        {
            globalUserVariable->convertBwToShm();
        }

        globalUserVariable->converFreqToShm();
        emit infoRefresh(SA_INFO_FREQ,SA_INFO_FREQ_CENTER);
        //******************************************************************************
    }
}
/**
 * @brief setMarkerToCFStep
 */
void controlInterface::setMarkerToCFStep()
{
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }
    if (globalUserVariable->gMarkerView[ globalUserVariable->gMarkerSelect] == SA_ON)
    {
        if (globalUserVariable->gMarkerType[ globalUserVariable->gMarkerSelect] == REF)
            globalUserVariable->gCFFreq = globalUserVariable->gMarkerRefFreq[globalUserVariable->gMarkerSelect] ;
        else
            globalUserVariable->gCFFreq = globalUserVariable->gMarkerDeltaFreq[globalUserVariable->gMarkerSelect] ;
    }
}
/**
 * @brief setMarkerToStart
 */
void controlInterface::setMarkerToStart()
{

    QString strCmd = ":MARKer:TO:STARt";
    emit sendSCPIcmd(strCmd);
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }
    if (globalUserVariable->gMarkerView[ globalUserVariable->gMarkerSelect] == SA_ON)
    {
        if (globalUserVariable->gMarkerType[ globalUserVariable->gMarkerSelect] == REF)
            globalUserVariable->gStartFreq = globalUserVariable->gMarkerRefFreq[globalUserVariable->gMarkerSelect] ;
        else
            globalUserVariable->gStartFreq = globalUserVariable->gMarkerDeltaFreq[globalUserVariable->gMarkerSelect] ;

        globalUserVariable->adjustFreqByStart();
        globalUserVariable->stepFreqCalculatorFunc();
        globalUserVariable->markerPositionReCalculatorFunc();

        unsigned long tempFlag = 0.;
        if(globalUserVariable->gZeroSpanAction)
        {
            globalUserVariable->gZeroSpanAction = SA_OFF;
            //Johnson 190425
            if(globalUserVariable->uIFMode != SA_AUTO_IFMODE)
            {
                globalUserVariable->uIFMode = SA_AUTO_IFMODE;
            }

            //Johnson 190912
            if(globalUserVariable->gGateViewStatus == SA_GATE_VIEW_OPEN)
            {
                globalUserVariable->gGateViewStatus = SA_GATE_VIEW_CLOSE;
                globalUserVariable->gGateSweepSpanChange = 0;
            }
        }

        bitaloth->ConfigureFrequencyStartStop(globalUserVariable->gStartFreq,globalUserVariable->gStopFreq);
        if(globalUserVariable->grbwChangedbyFreq)
        {
            globalUserVariable->convertBwToShm();
        }

        globalUserVariable->converFreqToShm();
        emit infoRefresh(SA_INFO_FREQ,SA_INFO_FREQ_CENTER);
    }
}
/**
 * @brief setMarkerToStop
 */
void controlInterface::setMarkerToStop()
{
    QString strCmd = ":MARKer:TO:STOP";
    emit sendSCPIcmd(strCmd);
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }
    if (globalUserVariable->gMarkerView[ globalUserVariable->gMarkerSelect] == SA_ON)
    {
        if (globalUserVariable->gMarkerType[ globalUserVariable->gMarkerSelect] == REF)
            globalUserVariable->gStopFreq = globalUserVariable->gMarkerRefFreq[globalUserVariable->gMarkerSelect] ;
        else
            globalUserVariable->gStopFreq = globalUserVariable->gMarkerDeltaFreq[globalUserVariable->gMarkerSelect] ;

        globalUserVariable->adjustFreqByStop();
        globalUserVariable->stepFreqCalculatorFunc();
        globalUserVariable->markerPositionReCalculatorFunc();

        unsigned long tempFlag = 0.;
        if(globalUserVariable->gZeroSpanAction)
        {
            globalUserVariable->gZeroSpanAction = SA_OFF;
            //Johnson 190425
            if(globalUserVariable->uIFMode != SA_AUTO_IFMODE)
            {
                globalUserVariable->uIFMode = SA_AUTO_IFMODE;
            }

            //Johnson 190912
            if(globalUserVariable->gGateViewStatus == SA_GATE_VIEW_OPEN)
            {
                globalUserVariable->gGateViewStatus = SA_GATE_VIEW_CLOSE;
                globalUserVariable->gGateSweepSpanChange = 0;
            }
        }

        bitaloth->ConfigureFrequencyStartStop(globalUserVariable->gStartFreq,globalUserVariable->gStopFreq);
        if(globalUserVariable->grbwChangedbyFreq)
        {
            globalUserVariable->convertBwToShm();
        }
        globalUserVariable->converFreqToShm();
        emit infoRefresh(SA_INFO_FREQ,SA_INFO_FREQ_CENTER);
    }

}
/**
 * @brief setMarkerToRefLvl
 */
void controlInterface::setMarkerToRefLvl()
{
    if (globalUserVariable->gMarkerView[ globalUserVariable->gMarkerSelect] == SA_ON) {
        if (globalUserVariable->gMarkerType[ globalUserVariable->gMarkerSelect] == REF)
            globalUserVariable->gRefLevel = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect]] ;
        else
            globalUserVariable->gRefLevel = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect]];
    }
}
/**
 * @brief setMarkerDisplay
 * @param markerDisplay
 */
void controlInterface::setMarkerDisplay(qint32 markerDisplay)
{
    markerDisplay = !!markerDisplay;
    globalUserVariable->gMarkerDisplay = markerDisplay;
    globalUserLimit->gridAxisCalculatorFunc();
}
/**
 * @brief getMarkerDisplay
 * @return
 */
qint32 controlInterface::getMarkerDisplay()
{
    return globalUserVariable->gMarkerDisplay;
}
/**
 * @brief setMarkerRefFreq
 * @param uMarkerRefFreq
 */
void controlInterface::setMarkerRefFreq(qreal uMarkerRefFreq,qint32 markerIndex)
{
    //Tony 0123
    if(markerIndex < 0 || markerIndex >= MARKER_TOTAL_CNT)
    {
        markerIndex = globalUserVariable->gMarkerSelect;
    }

    QString strCmd;
    QString iVal = QString::number(uMarkerRefFreq);

    strCmd = QString(":MARKer:%1:X ").arg(QString::number(markerIndex + 1));
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    if (globalUserVariable->gStartFreq <= uMarkerRefFreq && globalUserVariable->gStopFreq >= uMarkerRefFreq)
    {
        globalUserVariable->markerEditInNputMarkerPosCalculatorFunc(uMarkerRefFreq, globalUserVariable->gMarkerType[markerIndex] );
    }
    else
    {
        if (globalUserVariable->gStartFreq > uMarkerRefFreq)
            globalUserVariable->markerEditInNputMarkerPosCalculatorFunc(globalUserVariable->gStartFreq, globalUserVariable->gMarkerType[markerIndex] );
        else if(globalUserVariable->gStopFreq < uMarkerRefFreq)
            globalUserVariable->markerEditInNputMarkerPosCalculatorFunc(globalUserVariable->gStopFreq, globalUserVariable->gMarkerType[markerIndex] );
    }

    emit infoRefresh(SA_INFO_MARKER,SA_INFO_MARKER_VALUE);
}
/**
 * @brief getMarkerRefFreq
 * @return
 */
qreal controlInterface::getMarkerRefFreq(qint32 markerIndex)
{
    //Tony 0123
    if(markerIndex < 0 || markerIndex >= MARKER_TOTAL_CNT)
    {
        markerIndex = globalUserVariable->gMarkerSelect;
    }

    return (qreal)globalUserVariable->gMarkerRefFreq[markerIndex]+globalUserVariable->gfreqOffset;
}
/**
 * @brief setMarkerDeltaFreq
 * @param uMarkerDeltaFreq
 */
void controlInterface::setMarkerDeltaFreq(qreal uMarkerDeltaFreq, qint32 markerIndex)
{
    quint64 calculatorFreq = 0;
    quint64 vigeoFreq = 0;
    //Tony 0123
    if(markerIndex < 0 || markerIndex >= MARKER_TOTAL_CNT)
    {
        markerIndex = globalUserVariable->gMarkerSelect;
    }

    QString strCmd;
    QString iVal = QString::number(uMarkerDeltaFreq);

    strCmd = QString(":MARKer:%1:X ").arg(QString::number(markerIndex + 1));
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(uMarkerDeltaFreq < globalUserVariable->gStartFreq)
    {
        if(uMarkerDeltaFreq <SPEC_FREQ_MIN)
        {
            globalUserVariable->gMarkerDeltaFreq[markerIndex] = SPEC_FREQ_MIN;
        }else
        {
            globalUserVariable->gMarkerDeltaFreq[markerIndex] = uMarkerDeltaFreq;
        }
        globalUserVariable->gMarkerDeltaPos[markerIndex] = 0;
    }
    else if(uMarkerDeltaFreq > globalUserVariable->gStopFreq)
    {
        if(uMarkerDeltaFreq > SPEC_FREQ_MAX)
        {
            globalUserVariable->gMarkerDeltaFreq[markerIndex] = SPEC_FREQ_MAX;
        }else
        {
            globalUserVariable->gMarkerDeltaFreq[markerIndex] = uMarkerDeltaFreq;
        }
        globalUserVariable->gMarkerDeltaPos[markerIndex] = globalUserVariable->gSweepTracePoint - 1;
    }
    else
    {
        for (qint32 i = 0; i < (globalUserVariable->gSweepTracePoint + 1); i++)
        {
            calculatorFreq = globalUserVariable->gStepFreq * i;
            vigeoFreq  = globalUserVariable->gStartFreq + calculatorFreq ;

            if (vigeoFreq >= uMarkerDeltaFreq)
            {
                globalUserVariable->gMarkerDeltaPos[markerIndex] = i;
                globalUserVariable->gMarkerDeltaFreq[markerIndex] = uMarkerDeltaFreq;
                break;
            }
        }
    }

    emit infoRefresh(SA_INFO_MARKER,SA_INFO_MARKER_VALUE);
}
/**
 * @brief getMarkerDeltaFreq
 * @return
 */
qreal controlInterface::getMarkerDeltaFreq(qint32 markerIndex)
{
    if(markerIndex < 0 || markerIndex >= MARKER_TOTAL_CNT)
    {
        markerIndex = globalUserVariable->gMarkerSelect;
    }
    return globalUserVariable->gMarkerDeltaFreq[markerIndex];
}
/**
 * @brief setMarkerRefTime
 * @param uMarkerRefTime
 * @param markerIndex
 */
void controlInterface::setMarkerRefTime(qreal uMarkerRefTime, qint32 markerIndex)
{
    //Tony
    if(markerIndex < 0 || markerIndex >= MARKER_TOTAL_CNT)
    {
        markerIndex = globalUserVariable->gMarkerSelect;
    }

    if (0 <= uMarkerRefTime && globalUserVariable->gSweepTime >= uMarkerRefTime)
    {
        globalUserVariable->markerEditZeroSpanMarkerPosCalculatorFunc(uMarkerRefTime, globalUserVariable->gMarkerType[markerIndex] );
    }
    else
    {
        if (0 > uMarkerRefTime)
            globalUserVariable->markerEditZeroSpanMarkerPosCalculatorFunc(0, globalUserVariable->gMarkerType[markerIndex] );
        else if(globalUserVariable->gSweepTime < uMarkerRefTime)
            globalUserVariable->markerEditZeroSpanMarkerPosCalculatorFunc(globalUserVariable->gSweepTime, globalUserVariable->gMarkerType[markerIndex] );
    }

    emit infoRefresh(SA_INFO_MARKER,SA_INFO_MARKER_VALUE);
}
/**
 * @brief getMarkerRefTime
 * @param markerIndex
 */
qreal controlInterface::getMarkerRefTime(qint32 markerIndex)
{
    //Tony 0123
    if(markerIndex < 0 || markerIndex >= MARKER_TOTAL_CNT)
    {
        markerIndex = globalUserVariable->gMarkerSelect;
    }
    return (qreal)globalUserVariable->gMarkerRefTime[markerIndex];
}
/**
 * @brief setMarkerDeltaTime
 * @param uMarkerDeltaTime
 * @param markerIndex
 */
void controlInterface::setMarkerDeltaTime(qreal uMarkerDeltaTime, qint32 markerIndex)
{
    qreal steptime = globalUserVariable->gSweepTime/(globalUserVariable->gTracePoint -1);
    //Tony 0123
    if(markerIndex < 0 || markerIndex >= MARKER_TOTAL_CNT)
    {
        markerIndex = globalUserVariable->gMarkerSelect;
    }


    if(uMarkerDeltaTime < 0)
    {
        globalUserVariable->gMarkerDeltaTime[markerIndex] = 0;
        globalUserVariable->gMarkerDeltaPos[markerIndex] = 0;
    }else if(uMarkerDeltaTime > globalUserVariable->gSweepTime)
    {
        globalUserVariable->gMarkerDeltaTime[markerIndex] = globalUserVariable->gSweepTime;
        globalUserVariable->gMarkerDeltaPos[markerIndex] = globalUserVariable->gSweepTracePoint - 1;
    }else if (0 <= uMarkerDeltaTime && globalUserVariable->gSweepTime >= uMarkerDeltaTime)
    {
        for (qint32 i = 0; i < (globalUserVariable->gSweepTracePoint + 1); i++)
        {
            if (steptime*i >= uMarkerDeltaTime)
            {
                globalUserVariable->gMarkerDeltaPos[markerIndex] = i;
                globalUserVariable->gMarkerDeltaTime[markerIndex] = uMarkerDeltaTime;
                break;
            }
        }
    }

    emit infoRefresh(SA_INFO_MARKER,SA_INFO_MARKER_VALUE);
}
/**
 * @brief getMarkerDeltaTime
 * @param markerIndex
 */
qreal controlInterface::getMarkerDeltaTime(qint32 markerIndex)
{
    //Tony 0123
    if(markerIndex < 0 || markerIndex >= MARKER_TOTAL_CNT)
    {
        markerIndex = globalUserVariable->gMarkerSelect;
    }
    return (qreal)globalUserVariable->gMarkerDeltaTime[markerIndex];
}

/**
 * @brief setLimitFreq
 * @param limitSelect
 * @param pointIndex
 * @param freq
 */
void controlInterface::setLimitFreq(qint32 limitSelect,qint32 pointIndex,qreal freq)
{
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }
    if(limitSelect <0 || limitSelect >= LIMIT_SELECTSUM)
        limitSelect = globalUserLimit->gLimitSelect;
    if(pointIndex <0 || pointIndex >= globalUserLimit->gTotalDot[limitSelect])
        return;

    QString strCmd = QString(":LIMIt:POINt:DATA:FREQ %1,%2,%3").arg(QString::number(limitSelect + 1)).arg(QString::number(pointIndex + 1)).arg(QString::number(freq));
    emit sendSCPIcmd(strCmd);

    freq = freq - globalUserVariable->gfreqOffset;

    if(freq < SPEC_FREQ_MIN)
    {
        freq = SPEC_FREQ_MIN;
    }
    else if(freq > SPEC_FREQ_MAX)
    {
        freq = SPEC_FREQ_MAX;
    }

    //    if(freq < globalUserVariable->gStartFreq)
    //    {
    //        freq = getStartFreq();
    //    }
    //    else if(freq > globalUserVariable->gStopFreq)
    //    {
    //        freq = getStopFreq();
    //    }

    globalUserLimit->gFreq[limitSelect][pointIndex] = freq/SA_MHZ;
    globalUserLimit->gFirstIn[limitSelect] = false;
    removeSamePoint(limitSelect);
    globalUserLimit->sortLimitFreq();
    emit infoRefresh(SA_INFO_LIMIT,SA_INFO_LIMIT_VALUE);
    return;
}

void controlInterface::setLimitData(qint32 limitSelect,qint32 pointIndex,qreal freq,qreal ampt)
{
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }
    if(limitSelect <0 || limitSelect >= LIMIT_SELECTSUM)
        limitSelect = globalUserLimit->gLimitSelect;
    if(pointIndex <0 || pointIndex >= LIMIT_TOTALDOT)
        return;
    if((pointIndex + 1) > globalUserLimit->gTotalDot[limitSelect])
    {
        globalUserLimit->gTotalDot[limitSelect] = pointIndex + 1;
    }
    freq = freq - globalUserVariable->gfreqOffset;

    if(freq < SPEC_FREQ_MIN)
    {
        freq = SPEC_FREQ_MIN;
    }
    else if(freq > SPEC_FREQ_MAX)
    {
        freq = SPEC_FREQ_MAX;
    }
    if(ampt < TABLEWIDGET_AMP_MIN)
    {
        ampt = TABLEWIDGET_AMP_MIN;
    }
    else if(ampt > TABLEWIDGET_AMP_MAX)
    {
        ampt = TABLEWIDGET_AMP_MAX;
    }
    globalUserLimit->gAmplitude[limitSelect][pointIndex] = ampt;
    globalUserLimit->gFreq[limitSelect][pointIndex] = freq/SA_MHZ;
    globalUserLimit->gFirstIn[limitSelect] = false;

    //removeSamePoint(limitSelect);
    //globalUserLimit->sortLimitFreq();
    emit infoRefresh(SA_INFO_LIMIT,SA_INFO_LIMIT_VALUE);
    return;
}

/**
 * @brief getLimitFreq
 * @param limitSelect
 * @param pointIndex
 */
qreal controlInterface::getLimitFreq(qint32 limitSelect,qint32 pointIndex)
{
    qreal freq;
    if(limitSelect <0 || limitSelect >= LIMIT_SELECTSUM)
        limitSelect = globalUserLimit->gLimitSelect;
    if(pointIndex <0 || pointIndex >= globalUserLimit->gTotalDot[limitSelect])
        return ERROR;
    freq = globalUserLimit->gFreq[limitSelect][pointIndex] * SA_MHZ;
    freq = freq + globalUserVariable->gfreqOffset;
    return freq;
}

/**
 * @brief setLimitAmpt
 * @param limitSelect
 * @param pointIndex
 * @param ampt
 */
void controlInterface::setLimitAmpt(qint32 limitSelect,qint32 pointIndex,qreal ampt)
{
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }
    if(limitSelect <0 || limitSelect >= LIMIT_SELECTSUM)
        limitSelect = globalUserLimit->gLimitSelect;
    if(pointIndex <0 || pointIndex >= globalUserLimit->gTotalDot[limitSelect])
        return;

    QString strCmd = QString(":LIMIt:POINt:DATA:AMPL %1,%2,%3").arg(QString::number(limitSelect + 1)).arg(QString::number(pointIndex + 1)).arg(QString::number(ampt));
    emit sendSCPIcmd(strCmd);

    if(ampt < TABLEWIDGET_AMP_MIN)
    {
        ampt = TABLEWIDGET_AMP_MIN;
    }
    else if(ampt > TABLEWIDGET_AMP_MAX)
    {
        ampt = TABLEWIDGET_AMP_MAX;
    }
    globalUserLimit->gAmplitude[limitSelect][pointIndex] = ampt;
    globalUserLimit->gFirstIn[limitSelect] = false;
    removeSamePoint(limitSelect);
    globalUserLimit->sortLimitFreq();
    emit infoRefresh(SA_INFO_LIMIT,SA_INFO_LIMIT_VALUE);
    return;
}
/**
 * @brief getLimitAmpt
 * @param limitSelect
 * @param pointIndex
 */
qreal controlInterface::getLimitAmpt(qint32 limitSelect,qint32 pointIndex)
{
    qreal ampt;
    if(limitSelect <0 || limitSelect >= LIMIT_SELECTSUM)
        limitSelect = globalUserLimit->gLimitSelect;
    if(pointIndex <0 || pointIndex >= globalUserLimit->gTotalDot[limitSelect])
        return ERROR;
    ampt = globalUserLimit->gAmplitude[limitSelect][pointIndex];
    return ampt;
}
/**
 * @brief setLimitCurPointIndex
 * @param limitSelect
 * @param pointIndex
 */
void controlInterface::setLimitCurPointIndex(qint32 limitSelect,qint32 pointIndex)
{
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }
    if(limitSelect <0 || limitSelect >= LIMIT_SELECTSUM)
        limitSelect = globalUserLimit->gLimitSelect;
    if(pointIndex <=0)
        pointIndex = 1;
    else if(pointIndex >= globalUserLimit->gTotalDot[limitSelect])
        pointIndex = globalUserLimit->gTotalDot[limitSelect] ;
    globalUserLimit->gCurLimitIndex[limitSelect] = pointIndex;
    return;
}
/**
 * @brief getLimitCurPointIndex
 * @param limitSelect
 * @return pointIndex
 */
qint32 controlInterface::getLimitCurPointIndex(qint32 limitSelect)
{
    qint32 pointIndex;
    if(limitSelect <0 || limitSelect >= LIMIT_SELECTSUM)
        limitSelect = globalUserLimit->gLimitSelect;
    pointIndex = globalUserLimit->gCurLimitIndex[limitSelect];
    return pointIndex;
}

/**
 * @brief setLimitSelect
 * @param limitSelect
 */
void controlInterface::setLimitSelect(qint32 limitSelect)
{
    if(limitSelect < 0 || limitSelect > 6)
    {
        return;
    }

    QString iVal = QString::number(limitSelect + 1);
    QString strCmd = ":LIMIt:SELEct ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }
    globalUserLimit->gLimitSelect = limitSelect;
    emit infoRefresh(SA_INFO_LIMIT,SA_INFO_LIMIT_NUM);
}
/**
 * @brief getLimitSelect
 * @return
 */
qint32 controlInterface::getLimitSelect()
{
    return globalUserLimit->gLimitSelect;
}
/**
 * @brief setLimitLineStatus
 * @param limitLineStatus
 */
void controlInterface::setLimitLineStatus(qint32 limitLineStatus,qint32 limitIndex)
{
    limitLineStatus = !!limitLineStatus;
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }
    if(limitIndex < 0 || limitIndex >= LIMIT_SELECTSUM)
    {
        limitIndex = globalUserLimit->gLimitSelect;
    }

    QString strCmd;
    QString iVal = QString::number(limitLineStatus);
    strCmd = QString(":LIMIt:%1:DISPlay ").arg(QString::number(limitIndex + 1));
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    globalUserLimit->gLimitLine[limitIndex] = limitLineStatus;
    emit infoRefresh(SA_INFO_LIMIT,SA_INFO_LIMIT_VIEW);
}
/**
 * @brief getLimitLineStatus
 * @return
 */
qint32 controlInterface::getLimitLineStatus(qint32 limitIndex)
{
    if(limitIndex < 0 || limitIndex >= LIMIT_SELECTSUM)
    {
        limitIndex = globalUserLimit->gLimitSelect;
    }
    return globalUserLimit->gLimitLine[limitIndex];
}
/**
 * @brief setLimitEdgeStatus
 * @param limitEdgeStatus
 */
void controlInterface::setLimitEdgeStatus(qint32 limitEdgeStatus, qint32 limitIndex)
{
    limitEdgeStatus = !!limitEdgeStatus;
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }
    if(limitIndex < 0 || limitIndex >= LIMIT_SELECTSUM)
    {
        limitIndex = globalUserLimit->gLimitSelect;
    }
    QString strCmd;
    QString iVal = QString::number(limitEdgeStatus);
    strCmd = QString(":LIMIt:%1:EDGE:STATe ").arg(QString::number(limitIndex + 1));
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    globalUserLimit->gLimitEdge[limitIndex] = limitEdgeStatus;
    if(globalUserLimit->gLimitEdge[limitIndex] == SA_OFF) globalUserLimit->gLimitEdgeValue[limitIndex] = 0.;
    emit infoRefresh(SA_INFO_LIMIT,SA_INFO_LIMIT_EDGE_VIEW);
}
/**
 * @brief getLimitEdgeStatus
 * @return
 */
qint32 controlInterface::getLimitEdgeStatus(qint32 limitIndex)
{
    if(limitIndex < 0 || limitIndex >= LIMIT_SELECTSUM)
    {
        limitIndex = globalUserLimit->gLimitSelect;
    }
    return globalUserLimit->gLimitEdge[limitIndex];
}
/**
 * @brief setLimitEdgeValue
 * @param dLimitEdgeValue
 */
void controlInterface::setLimitEdgeValue(qreal dLimitEdgeValue,qint32 limitIndex)
{
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }
    if(limitIndex < 0 || limitIndex >= LIMIT_SELECTSUM)
    {
        limitIndex = globalUserLimit->gLimitSelect;
    }

    QString strCmd;
    QString iVal = QString::number(dLimitEdgeValue);
    strCmd = QString(":LIMIt:%1:EDGE ").arg(QString::number(limitIndex + 1));
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(getLimitEdgeStatus() == SA_OFF)
        setLimitEdgeStatus(SA_ON);
    if(fabs(dLimitEdgeValue)>LIMIT_EDGE_MAX)
    {
        globalUserLimit->gLimitEdgeValue[limitIndex] = LIMIT_EDGE_MAX;
    }
    else
    {
        if(dLimitEdgeValue>0) globalUserLimit->gLimitEdgeValue[limitIndex] = dLimitEdgeValue;
        else globalUserLimit->gLimitEdgeValue[limitIndex] = -dLimitEdgeValue;
    }
    emit infoRefresh(SA_INFO_LIMIT,SA_INFO_LIMIT_EDGE_VALUE);
}
/**
 * @brief getLimitEdgeValue
 * @return
 */
qreal controlInterface::getLimitEdgeValue(qint32 limitIndex)
{
    if(limitIndex < 0 || limitIndex >= LIMIT_SELECTSUM)
    {
        limitIndex = globalUserLimit->gLimitSelect;
    }
    return globalUserLimit->gLimitEdgeValue[limitIndex];
}
/**
 * @brief setLimitTestStatus
 * @param limitTestStatus
 */
void controlInterface::setLimitTestStatus(qint32 limitTestStatus)
{
    limitTestStatus = !!limitTestStatus;

    QString iVal = QString::number(limitTestStatus);
    QString strCmd = ":LIMIt:TEST ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }
    globalUserLimit->gLimitTest = limitTestStatus;
    emit infoRefresh(SA_INFO_LIMIT,SA_INFO_LIMIT_EDGE_TEST);
}
qint32 controlInterface::getLimitTestStatus()
{
    return globalUserLimit->gLimitTest;
}
/**
 * @brief setLimitType
 * @param limitType
 */
void controlInterface::setLimitType(qint32 limitType,qint32 limitIndex)
{
    if(limitType < 1 || limitType > 2) return;
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }
    if(limitIndex < 0 || limitIndex >= LIMIT_SELECTSUM)
    {
        limitIndex = globalUserLimit->gLimitSelect;
    }
    QString strCmd;
    QString iVal = QString::number(limitType);
    strCmd = QString(":LIMIt:%1:TYPE ").arg(QString::number(limitIndex+1));
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    globalUserLimit->gLatestLimitType[limitIndex] = limitType;
    emit infoRefresh(SA_INFO_LIMIT,SA_INFO_LIMIT_EDGE_TYPE);
}
/**
 * @brief getLimitType
 * @return
 */
qint32 controlInterface::getLimitType(qint32 limitIndex)
{
    if(limitIndex < 0 || limitIndex >= LIMIT_SELECTSUM)
    {
        limitIndex = globalUserLimit->gLimitSelect;
    }
    return globalUserLimit->gLatestLimitType[limitIndex];
}
/**
 * @brief setInsertLimitRow
 */
void controlInterface::setInsertLimitRow(qint32 limitSelect)
{
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }
    qint32 size,point ;
    if(limitSelect < 0 || limitSelect >= LIMIT_SELECTSUM)
        limitSelect = globalUserLimit->gLimitSelect;

    QString strCmd;
    strCmd = QString(":LIMIt:INSERT %1").arg(QString::number(limitSelect + 1));
    emit sendSCPIcmd(strCmd);
    //    if(globalUserLimit->gFirstIn[limitSelect])
    //    {
    //        return;
    //    }
    if(globalUserLimit->gTotalDot[limitSelect] >= LIMIT_TOTALDOT)
        return;
    globalUserLimit->gTotalDot[limitSelect]++;
    globalUserLimit->gFirstIn[limitSelect] = true;
    size = globalUserLimit->gTotalDot[limitSelect];
    globalUserLimit->gFreq[limitSelect][size - 1] = SPEC_FREQ_MIN/SA_MHZ;
    globalUserLimit->gAmplitude[limitSelect][size - 1] = TABLEWIDGET_AMP_MIN;
    removeSamePoint(limitSelect);
    globalUserLimit->sortLimitFreq(limitSelect);
    setLimitCurPointIndex(limitSelect,0);
    return;
}
/**
 * @brief removeSamePoint
 * @return
 */
void controlInterface::removeSamePoint(qint32 limitSelect)
{
    qint32 start = 0;
    if(limitSelect < 0 || limitSelect >= LIMIT_SELECTSUM)
    {
        limitSelect = globalUserLimit->gLimitSelect;
    }
    if(globalUserLimit->gFirstIn[limitSelect])
    {
        start = 1;
    }
    //remove limit same point
    for(qint32 i = start;i<globalUserLimit->gTotalDot[limitSelect];i++)
    {
        for(int j = i+1;j<globalUserLimit->gTotalDot[limitSelect];j++)
        {
            if(globalUserLimit->gFreq[limitSelect][i] == globalUserLimit->gFreq[limitSelect][j])
            {
                if(globalUserLimit->gAmplitude[limitSelect][i] == globalUserLimit->gAmplitude[limitSelect][j])
                {
                    removeLimitRow(limitSelect,j);
                }
            }
        }
    }
    return;
}
qint32 controlInterface::getLimitPointCnt(qint32 limitSelect)
{
    if(limitSelect < 0 || limitSelect >= LIMIT_SELECTSUM)
        limitSelect = globalUserLimit->gLimitSelect;
    return globalUserLimit->gTotalDot[limitSelect];
}
/**
 * @brief setDeleteLimitRow
 */
void controlInterface::setDeleteLimitRow(qint32 limitSelect,qint32 pointIndex)
{
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }

    QString strCmd;
    strCmd = QString(":LIMIt:POINt:DELEte %1,%2").arg(QString::number(limitSelect + 1)).arg(QString::number(pointIndex + 1));
    emit sendSCPIcmd(strCmd);

    removeLimitRow(limitSelect,pointIndex);
    globalUserLimit->gFirstIn[limitSelect] = false;
    removeSamePoint(limitSelect);
    qint32 limitCurPos = getLimitCurPointIndex(limitSelect);
    globalUserLimit->sortLimitFreq(limitSelect);
    setLimitCurPointIndex(limitSelect,limitCurPos);
}

/**
 * @brief remove one limit point
 */
void controlInterface::removeLimitRow(qint32 limitSelect,qint32 pointIndex)
{
    qint32 lastPoint = globalUserLimit->gTotalDot[limitSelect] - 1;
    if(lastPoint < 0)
        return;
    if(limitSelect < 0 || limitSelect >= LIMIT_SELECTSUM)
        limitSelect = globalUserLimit->gLimitSelect;
    if(pointIndex < 0 || pointIndex >= globalUserLimit->gTotalDot[limitSelect])
        return;
    globalUserLimit->gTotalDot[limitSelect]--;

    if(pointIndex != lastPoint)
    {
        //globalUserLimit->gCurLimitIndex[limitSelect] = pointIndex;
        globalUserLimit->gFreq[limitSelect][pointIndex] = globalUserLimit->gFreq[limitSelect][lastPoint];
        globalUserLimit->gAmplitude[limitSelect][pointIndex] = globalUserLimit->gAmplitude[limitSelect][lastPoint];
    }else
    {
        setLimitCurPointIndex(limitSelect,lastPoint);
    }
    globalUserLimit->gFreq[limitSelect][lastPoint] = 0;
    globalUserLimit->gAmplitude[limitSelect][lastPoint] = 0;
    return;
}

/**
 * @brief setDeleteLimitOne
 */
void controlInterface::setDeleteLimitOne(qint32 limitSelect)
{
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }
    if(limitSelect < 0 || limitSelect >= LIMIT_SELECTSUM)
        limitSelect = globalUserLimit->gLimitSelect;

    QString strCmd;
    strCmd = QString(":LIMIt:%1:DELEte").arg(QString::number(limitSelect + 1));
    emit sendSCPIcmd(strCmd);

    globalUserLimit->gTotalDot[limitSelect] = 0;
    globalUserLimit->gFirstIn[limitSelect] = false;
    setLimitCurPointIndex(limitSelect,0);
    return;
}

/**
 * @brief setDeleteLimitAll
 */
void controlInterface::setDeleteLimitAll()
{
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }
    QString strCmd = QString(":LIMIt:ALL:DELEte");
    emit sendSCPIcmd(strCmd);

    for(qint32 i=0;i<LIMIT_SELECTSUM;i++)
    {
        globalUserLimit->gTotalDot[i] = 0;
        setLimitCurPointIndex(i,0);
        globalUserLimit->gFirstIn[i] = false;
        setLimitLineStatus(false,i);
        setLimitEdgeStatus(false,i);
        setLimitTestStatus(false);
        setLimitType(UPPER,i);
    }
    return;
}
/**
 * @brief setAutoLimit
 */
void controlInterface::setAutoLimit(qint32 limitSelect)
{
    if(globalUserVariable->gZeroSpanAction)
        return;
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }
    qint32 limitNum = 100;
    qreal limitStep = (qreal)(NUM_SWEEP_POINT - 2)/(limitNum - 2);
    qint32 traceSelect = getTraceSelect();
    quint32 maxPoint;
    qint32 startPos,stopPos;
    qreal startFreq,stopFreq,stepFreq,freq,ampt,offstampt,offsetfreq;
    if(limitSelect < 0 || limitSelect >= LIMIT_SELECTSUM)
        limitSelect = globalUserLimit->gLimitSelect;
    memcpy(tmpAmpt,globalUserVariable->gTraceMeasureVal[traceSelect],NUM_SWEEP_POINT * sizeof(qreal));
    if(!getLimitLineStatus(limitSelect))
    {
        setLimitLineStatus(true);
    }
    startFreq = getStartFreq();
    stopFreq = getStopFreq();
    stepFreq = (stopFreq - startFreq) / (NUM_SWEEP_POINT - 1) ;
    offstampt = getRefOffset();
    offsetfreq = 0;
    globalUserLimit->gTotalDot[limitSelect] = 0;
#if 0
    for(qint32 i = 0;i < limitNum;i++)
    {
        if((i+1) % 10 == 6)
        {
            offsetfreq += (qreal)(stepFreq/10)*limitStep;
        }
        globalUserLimit->gTotalDot[limitSelect]++;

        maxPoint = CalculateAutoLimitMax(i * limitStep +1,(i +1) * limitStep);

        freq = startFreq + i* limitStep * stepFreq + offsetfreq;
        ampt = tmpAmpt[maxPoint];

        freq = freq - globalUserVariable->gfreqOffset;
        globalUserLimit->gFreq[limitSelect][i] = freq/SA_MHZ;
        globalUserLimit->gAmplitude[limitSelect][i] = ampt + 10 +offstampt;
    }
#elif 1
    //First Point
    globalUserLimit->gTotalDot[limitSelect]++;
    freq = startFreq;
    ampt = tmpAmpt[0];

    freq = freq - globalUserVariable->gfreqOffset;
    globalUserLimit->gFreq[limitSelect][0] = freq/SA_MHZ;
    globalUserLimit->gAmplitude[limitSelect][0] = ampt + 10 + offstampt;

    qint32 i;
    for(i = 1;i < limitNum -1;i++)
    {
        globalUserLimit->gTotalDot[limitSelect]++;
        startPos = (i -1)*limitStep + 1;
        stopPos =  i * limitStep;
        if(stopPos == NUM_SWEEP_POINT - 3) stopPos = NUM_SWEEP_POINT - 2;//Special treatment
        maxPoint = CalculateAutoLimitMax(startPos,stopPos);

        freq = startFreq + maxPoint * stepFreq + offsetfreq;
        ampt = tmpAmpt[maxPoint];

        freq = freq - globalUserVariable->gfreqOffset;
        globalUserLimit->gFreq[limitSelect][i] = freq/SA_MHZ;
        globalUserLimit->gAmplitude[limitSelect][i] = ampt + 10 +offstampt;
    }
    //Last Point
    globalUserLimit->gTotalDot[limitSelect]++;
    freq = stopFreq;
    ampt = tmpAmpt[NUM_SWEEP_POINT - 1];

    freq = freq - globalUserVariable->gfreqOffset;
    globalUserLimit->gFreq[limitSelect][i] = freq/SA_MHZ;
    globalUserLimit->gAmplitude[limitSelect][i] = ampt + 10 + offstampt;
#endif

    QString strCmd;
    QString str=   ":LIMIt:POINt:DATA ";
    QString iVal   = QString::number(limitSelect+1);
    str += iVal;
    strCmd += ":LIMIt:DELEte\n";
    for(qint32 i =0;i<100;i++)
    {
        strCmd = strCmd+str+","+QString::number(i+1)+","+QString::number(globalUserLimit->gFreq[limitSelect][i]*SA_MHZ)+","+QString::number(globalUserLimit->gAmplitude[limitSelect][i] - offstampt)+"\n";
    }
    strCmd += ":LIMIt:DISPlay 1";
    emit sendSCPIcmd(strCmd);
    return;
}

quint32 controlInterface::CalculateAutoLimitMax(quint32 start,quint32 stop)
{
    qreal max,tmp,maxpoint;
    if(start > stop)
    {
        tmp = stop;
        stop = start;
        start= tmp;
    }else if(start == stop)
    {
        maxpoint = start;
        return maxpoint;
    }
    if(start >= NUM_SWEEP_POINT)
    {
        maxpoint = NUM_SWEEP_POINT-1;
        return maxpoint;
    }else if(stop>= NUM_SWEEP_POINT)
    {
        stop = NUM_SWEEP_POINT - 1;
    }
    max = tmpAmpt[start];
    maxpoint = start;
    for(qint32 i = start + 1; i <= stop;i++)
    {
        if(max < tmpAmpt[i])
        {
            max = tmpAmpt[i];
            maxpoint = i;
        }
    }
    return maxpoint;
}

/**
 * @brief setDeleteAllLimits
 * @param tableWidget
 */
void controlInterface::setDeleteAllLimits(ClickableTableWidget *tableWidget)
{
    globalUserLimit->caculateLimitTotalLine();

    if (SA_guiDrawSet.limitLineOnCount != 0)
    {
        for(qint32 i = tableWidget->rowCount()-1;i>=0;i--)
        {
            tableWidget->removeRow(i);
        }

    }
}
/**
 * @brief setInsertRowBelow
 * @param tableWidget
 */
void controlInterface::setInsertRowBelow(ClickableTableWidget *tableWidget)
{
    tableWidget->judgeTableContent(tableWidget,globalUserVariable->gStartFreq,globalUserVariable->gStopFreq);
    qint32 row = tableWidget->rowCount();
    if(row < LIMIT_TOTALDOT)
    {
        tableWidget->insertRow(row);
        tableWidget->setItem(row,0,new QTableWidgetItem(QString("%1").arg(globalUserVariable->gStartFreq/1000000)));
        tableWidget->setItem(row,1,new QTableWidgetItem(QString("-10.00")));
        tableWidget->sortAllItems();
        tableWidget->setFocus(Qt::TabFocusReason);
        tableWidget->setCurrentCell(0,0);

        globalUserLimit->gTotalDot[globalUserLimit->gLimitSelect]++;
        tableWidget->resetAllParam();
    }
}
/**
 * @brief setDeleteRow
 * @param tableWidget
 */
void controlInterface::setDeleteRow(ClickableTableWidget *tableWidget)
{
    tableWidget->removeRow(tableWidget->currentRow());
}
/**
 * @brief setDeleteLimit
 * @param tableWidget
 */
void controlInterface::setDeleteLimit(ClickableTableWidget *tableWidget)
{
    for(qint32 i = tableWidget->rowCount()-1;i>=0;i--)
    {
        tableWidget->removeRow(i);
    }
}
/**
 * @brief controlInterface::setPeak
 */
void controlInterface::setPeak()
{
    QString strCmd = ":MARKer:PMAXimum";
    emit sendSCPIcmd(strCmd);

    qint32 i = 0;
    qreal peakVal = 0.;
    qint32 peakPos = 0;

    qreal beforeVal = 0.;
    qreal currentVal = 0;
    qreal afterVal = 0.;
    qreal lastPointVal = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][NUM_SWEEP_POINT - 1];

    if (globalUserVariable->gMarkerView[globalUserVariable->gMarkerSelect] == SA_OFF)
    {
        globalUserVariable->gMarkerView[globalUserVariable->gMarkerSelect] = SA_ON;
        SA_guiDrawSet.markerOnCount++;
    }

    for (i = 0 ; i < NUM_SWEEP_POINT; i++)
    {
        currentVal = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i];
        if (i == 0)
            peakVal = currentVal ;
        else
        {
            if (peakVal < currentVal)
            {
                beforeVal =  globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i - 1];
                afterVal =  globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i + 1];

                // 임의로 지정된 Peak 값의 앞과 뒤의 값이 같거나 작아야 함
                if (currentVal >= beforeVal && currentVal >= afterVal)
                {
                    peakVal = currentVal ;
                    peakPos = i;
                }
            }
        }
    }

    if(lastPointVal - peakVal > 0.)
    {
        peakVal = lastPointVal;
        peakPos = NUM_SWEEP_POINT - 1;
    }

    if(globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == REF)
    {
        globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect] = peakPos;
        globalUserVariable->gMarkerRefFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * peakPos);
    }
    else if(globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == DELTA)
    {
        globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect] = peakPos;
        globalUserVariable->gMarkerDeltaFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * peakPos);
    }
    SA_guiDrawSet.peakPos = peakPos;
    emit infoRefresh(SA_INFO_MARKER,SA_INFO_MARKER_VALUE);
}

/**
 * @brief controlInterface::searchPeak
 *        dot trigger refreshpixmap
 */
void controlInterface::searchPeak()
{
    QString strCmd = ":MARKer:PMAXimum";
    emit sendSCPIcmd(strCmd);

    qint32 i = 0;
    qreal peakVal = 0.;
    qint32 peakPos = 0;

    qreal beforeVal = 0.;
    qreal currentVal = 0;
    qreal afterVal = 0.;
    qreal lastPointVal = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][NUM_SWEEP_POINT - 1];

    for (i = 0 ; i < NUM_SWEEP_POINT; i++)
    {
        currentVal = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i];
        if (i == 0)
            peakVal = currentVal ;
        else
        {
            if (peakVal < currentVal)
            {
                beforeVal =  globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i - 1];
                afterVal =  globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i + 1];

                // 임의로 지정된 Peak 값의 앞과 뒤의 값이 같거나 작아야 함
                if (currentVal >= beforeVal && currentVal >= afterVal)
                {
                    peakVal = currentVal ;
                    peakPos = i;
                }
            }
        }
    }

    if(lastPointVal - peakVal > 0.)
    {
        peakVal = lastPointVal;
        peakPos = NUM_SWEEP_POINT - 1;
    }
    if(globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect]==REF)
    {
        globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect] = peakPos;
        globalUserVariable->gMarkerRefFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * peakPos);
    }
    else if(globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect]==DELTA)
    {
        globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect] = peakPos;
        globalUserVariable->gMarkerDeltaFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * peakPos);
    }
    SA_guiDrawSet.peakPos = peakPos;

}

/**
 * @brief controlInterface::setMinSearch
 */
void controlInterface::setMinSearch()
{
    QString strCmd = ":MARKer:PMINimum";
    emit sendSCPIcmd(strCmd);

    qint32 i = 0;
    qreal peakVal = 0.;
    qint32 peakPos = 0;

    qreal beforeVal = 0.;
    qreal currentVal = 0;
    qreal afterVal = 0.;
    qreal lastPointVal = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][NUM_SWEEP_POINT - 1];

    if (globalUserVariable->gMarkerView[globalUserVariable->gMarkerSelect] == SA_OFF)
    {
        globalUserVariable->gMarkerView[globalUserVariable->gMarkerSelect] = SA_ON;
        SA_guiDrawSet.markerOnCount++;
    }

    for (i = 0 ; i < NUM_SWEEP_POINT; i++)
    {
        currentVal = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i];
        if (i == 0)
            peakVal = currentVal ;
        else
        {
            if (peakVal > currentVal)
            {
                beforeVal =  globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i - 1];
                afterVal =  globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i + 1];

                // 임의로 지정된 Peak 값의 앞과 뒤의 값이 같거나 작아야 함
                if (currentVal <= beforeVal && currentVal <= afterVal)
                {
                    peakVal = currentVal ;
                    peakPos = i;
                }
            }
        }
    }

    if(lastPointVal - peakVal < 0.)
    {
        peakVal = lastPointVal;
        peakPos = NUM_SWEEP_POINT - 1;
    }

    if(globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect]==REF)
    {
        globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect] = peakPos;
        globalUserVariable->gMarkerRefFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * peakPos);
    }
    else if(globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect]==DELTA)
    {
        globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect] = peakPos;
        globalUserVariable->gMarkerDeltaFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * peakPos);
    }
    //    SA_guiDrawSet.peakPos = peakPos;
    emit infoRefresh(SA_INFO_MARKER,SA_INFO_MARKER_VALUE);
}
/**
 * @brief nextPeakFunc
 * @param inputdata
 * @param num
 * @param currentMarkerIndex
 * @return
 * @note Find a peak point not greater than the current point based on the current cursor position
 */
qint32 nextPeakFunc(qreal* inputdata,qint32 num,qint32 currentMarkerIndex)
{
    qint32 NextPeakIndex = currentMarkerIndex;
    qreal AMax = 0;
    bool isFirstSearch = true;

    for (qint32 k = 0; k < num; k++)
    {
        if(*(inputdata + k) >= *(inputdata + currentMarkerIndex))
        {
            continue;
        }
        if(k == 0)
        {
            if(*(inputdata + k) > *(inputdata + k + 1))
            {
                AMax = *(inputdata + k);
                NextPeakIndex = k;
                isFirstSearch = false;
            }
        }
        else if(k == num - 1)
        {
            if(*(inputdata + k) > *(inputdata + k - 1))
            {
                if(*(inputdata + k) >= AMax)
                {
                    AMax = *(inputdata + k);
                    NextPeakIndex = k;
                }
            }
        }
        else if(*(inputdata + k) > *(inputdata + k + 1) && *(inputdata + k) > *(inputdata + k - 1))
        {
            if(*(inputdata + k) < *(inputdata + currentMarkerIndex))
            {
                if(isFirstSearch)
                {
                    AMax = *(inputdata + k);
                    NextPeakIndex = k;
                    isFirstSearch = false;
                }
                else
                {
                    if(*(inputdata + k) >= AMax)
                    {
                        AMax = *(inputdata + k);
                        NextPeakIndex = k;
                    }
                }

            }
        }
    }
    return NextPeakIndex;
}
/**
 * @brief controlInterface::setNextPeak
 */
void controlInterface::setNextPeak()
{
    QString strCmd = ":MARKer:PMAXimum:NEXT";
    emit sendSCPIcmd(strCmd);

    //qint32 LimitIndex = SA_guiDrawSet.peakPos;
    qint32 LimitIndex = 0;
    if(globalUserVariable->gMarkerType[globalUserVariable->gTraceSelect] == REF)
    {
        LimitIndex = globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect];
    }
    else if(globalUserVariable->gMarkerType[globalUserVariable->gTraceSelect] == DELTA)
    {
        LimitIndex = globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect];
    }
    LimitIndex = nextPeakFunc(globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect],NUM_SWEEP_POINT,LimitIndex);

    if(globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == REF)
    {
        globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect] = LimitIndex;
        globalUserVariable->gMarkerRefFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * LimitIndex);
    }
    else if(globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == DELTA)
    {
        globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect] = LimitIndex;
        globalUserVariable->gMarkerDeltaFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * LimitIndex);
    }
    SA_guiDrawSet.peakPos = LimitIndex;
    emit infoRefresh(SA_INFO_MARKER,SA_INFO_MARKER_VALUE);
}
/**
 * @brief controlInterface::setPeakRightSearch
 */
void controlInterface::setPeakRightSearch()
{
    QString strCmd = ":MARKer:PMAXimum:RIGHt";
    emit sendSCPIcmd(strCmd);

    qint32 i;
    qint32 peakPos = SA_guiDrawSet.peakPos;
    qreal beforeVal = 0.;
    qreal currentVal = 0;
    qreal afterVal = 0.;
    qint32 startPos = 0;

    if(globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == REF)
    {
        startPos = globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect];
    }
    else if(globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == DELTA)
    {
        startPos = globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect];
    }

    for (i = (/*SA_guiDrawSet.peakPos*/startPos + 1) ; i < NUM_SWEEP_POINT - 1; i++)
    {
        currentVal = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i];
        beforeVal =  globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i - 1];
        afterVal =  globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i + 1];

        // 임의로 지정된 Peak 값의 앞과 뒤의 값이 같거나 작아야 함
        if (currentVal >= beforeVal && currentVal >= afterVal)
        {
            peakPos = i;
            break;
        }
        if(i == NUM_SWEEP_POINT - 2)
        {
            if(globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][NUM_SWEEP_POINT - 1] >= globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i])
            {
                peakPos = NUM_SWEEP_POINT - 1;
            }
        }
    }
    if(/*SA_guiDrawSet.peakPos*/startPos == NUM_SWEEP_POINT - 2)
    {
        if(globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][NUM_SWEEP_POINT - 1] >= globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][/*SA_guiDrawSet.peakPos*/startPos])
        {
            peakPos = NUM_SWEEP_POINT - 1;
        }
    }

    if(globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == REF)
    {
        globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect] = peakPos;
        globalUserVariable->gMarkerRefFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * peakPos);
    }
    else if(globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == DELTA)
    {
        globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect] = peakPos;
        globalUserVariable->gMarkerDeltaFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * peakPos);
    }

    SA_guiDrawSet.peakPos = peakPos;
    emit infoRefresh(SA_INFO_MARKER,SA_INFO_MARKER_VALUE);
}
void controlInterface::setPeakLeftSearch()
{
    QString strCmd = ":MARKer:PMAXimum:LEFT";
    emit sendSCPIcmd(strCmd);

    qint32 i = 0;
    qint32 peakPos = SA_guiDrawSet.peakPos;
    qreal beforeVal = 0.;
    qreal currentVal = 0;
    qreal afterVal = 0.;
    qint32 startPos = 0;

    if(globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == REF)
    {
        startPos = globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect];
    }
    else if(globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == DELTA)
    {
        startPos = globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect];
    }

    for (i = (/*SA_guiDrawSet.peakPos*/startPos - 1) ; i > 0; i--)
    {
        currentVal = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i];
        beforeVal =  globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i - 1];
        afterVal =  globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i + 1];

        // 임의로 지정된 Peak 값의 앞과 뒤의 값이 같거나 작아야 함
        if (currentVal >= beforeVal && currentVal >= afterVal)
        {
            peakPos = i;
            break;
        }
        if(i == 1)
        {
            if(globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][0] >= globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][/*SA_guiDrawSet.peakPos*/startPos])
            {
                peakPos = 0;
            }
        }
    }

    if(/*SA_guiDrawSet.peakPos*/startPos == 1)
    {
        if(globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][0] >= globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][/*SA_guiDrawSet.peakPos*/startPos])
        {
            peakPos = 0;
        }
    }

    if(globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == REF)
    {
        globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect] = peakPos;
        globalUserVariable->gMarkerRefFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * peakPos);
    }
    else if(globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == DELTA)
    {
        globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect] = peakPos;
        globalUserVariable->gMarkerDeltaFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * peakPos);
    }

    SA_guiDrawSet.peakPos = peakPos;
    emit infoRefresh(SA_INFO_MARKER,SA_INFO_MARKER_VALUE);
}
void controlInterface::setPeakTrackStatus(quint32 peakTrackStatus)
{
    QString strCmd;
    QString iVal = QString::number(peakTrackStatus);
    strCmd = ":MARKer:PTRAck ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    globalUserVariable->gPeakTrack = peakTrackStatus;
}
quint32 controlInterface::getPeakTrackStatus()
{
    return globalUserVariable->gPeakTrack;
}
/**
 * @brief controlInterface::loadFile(QString mFileFullPath)
 * @note
 * @author Tony
 * @time   2019/06/03
 */
bool controlInterface::loadFile(QString mFileFullPath)
{
    qint32 successFlag;
    quint64 header;
    char *strPath =  mFileFullPath.toLatin1().data();
    FILE *pFile;
    pFile = fopen(strPath,"rb");
    if(!pFile){
        return false;
    }
    fseek(pFile,0,SEEK_END);
    if(!ftell(pFile)){
        fclose(pFile);
        return false;
    }
    fseek(pFile,0,SEEK_SET);
    fread(&header,sizeof(header),1,pFile);
    switch (header) {
    case SA_FILEHEADER_STATE:
        globalUserVariable->loadFileType = SA_STATE;
        successFlag = pparaSaveLoad->loadStatefile(mFileFullPath);
        //        setSuspendFunc(0);//Tony 190613
        break;
    case SA_FILEHEADER_STATE_DATA:
        globalUserVariable->loadFileType = SA_FILE;
        successFlag = pparaSaveLoad->loadStateAndDataFile(mFileFullPath);
        //        setSuspendFunc(1);
        break;
    default:
        successFlag = false;
        break;
    }
    globalUserVariable->gMeasureStatus = SA_OFF;
    LoadParamControl();
    //Tony 0619 for set measure mode
    SetMeasureItems(globalUserVariable->currentMode);
    return successFlag;
}

/**
 * @brief controlInterface::setSaveState(QString mFileFullPath)
 * @note  save current measure state
 * @author Tony
 * @time   2019/06/03
 */
bool controlInterface::setSaveState(QString mFileFullPath)
{
    return pparaSaveLoad->saveStatefile(mFileFullPath);
}

/**
 * @brief controlInterface::setLoadState(QString mFileFullPath)
 * @note  load measure state
 * @author Tony
 * @time   2019/06/03
 */
void controlInterface::setLoadState(QString mFileFullPath)
{
    if(pparaSaveLoad->loadStatefile(mFileFullPath))
    {
        LoadParamControl();
        //Tony 0619 for set measure mode
        SetMeasureItems(globalUserVariable->currentMode);
    }

    return;
}
/**
 * @brief controlInterface::setSaveTrace(QString mFileFullPath)
 * @note  save current measure state and trace data
 * @author Tony
 * @time   2019/06/03
 */
bool controlInterface::setSaveTrace(QString mFileFullPath)
{
    return pparaSaveLoad->saveStateAndDataFile(mFileFullPath);
}

/**
 * @brief controlInterface::setLoadTrace(QString mFileFullPath)
 * @note  load measure state and trace data
 * @author Tony
 * @time   2019/06/03
 */
void controlInterface::setLoadTrace(QString mFileFullPath)
{
    if(pparaSaveLoad->loadStateAndDataFile(mFileFullPath))
    {
        LoadParamControl();
        //Tony 0619 for set measure mode
        SetMeasureItems(globalUserVariable->currentMode);
    }
    return ;
}

void controlInterface::setLoadScreen()
{
    return;
}
void controlInterface::setLoadSetup()
{

}
void controlInterface::setLoadMedia(qint32 loadMedia)
{

}
qint32 controlInterface::getLoadMedia()
{

}
void controlInterface::setSaveScreen()
{

}
void controlInterface::setSaveSetup()
{

}
void controlInterface::setSaveMedia(qint32 saveMedia)
{

}
qint32 controlInterface::getSaveMedia()
{

}

void controlInterface::SetFuncKeyStatus(qint32 mShift)
{
    globalUserVariable->bShiftKeyPressed = mShift;
    emit infoRefresh(SA_INFO_SYSTEM,SA_INFO_SYSTEM_SHIFT);
    return;
}

qint32 controlInterface::GetFuncKeyStatus()
{
    return globalUserVariable->bShiftKeyPressed;
}

void controlInterface::ScreenCaptureFunc(QString filePath,QString fileName)
{
    //    QString fileFullPath;
    //    QDir *dir=new QDir(filePath);
    //    QStringList filter;
    //    filter<<"Selection_*.png";
    //    dir->setNameFilters(filter);
    //    QList<QFileInfo> *fileInfo=new QList<QFileInfo>(dir->entryInfoList(filter));
    //    //    if(fileName == "")
    ////        fileName =
    //    fileFullPath = ;
    //    bool retFlag = QPixmap::grabWindow(QApplication::desktop()->winId(), SCREEN_CAPTURE_STARTX, SCREEN_CAPTURE_STARTY, SCREEN_CAPTURE_WIDTH, SCREEN_CAPTURE_HEIGHT).save(fileFullPath);
    //    return retFlag;
}

void controlInterface::TraceSuspendFunc(qint32 status)
{
    blockSignals(true);
    static qint32 SA_tmpTraceType[NUM_TRACE]={SA_CLEAR_WRITE,SA_TRACE_OFF,SA_TRACE_OFF,SA_TRACE_OFF,SA_TRACE_OFF,SA_TRACE_OFF};
    if(status)
    {
        for(qint32 i=0;i<NUM_TRACE;i++)
        {
            SA_tmpTraceType[i] = getTraceType(i);
            if(getTraceViewStatus(i) == SA_ON)
            {
                setTraceType(SA_VIEW,i);
            }
        }
    }
    else
    {
        for(qint32 i=0;i<NUM_TRACE;i++)
        {
            setTraceType(SA_tmpTraceType[i],i);
        }
    }
    blockSignals(false);
}
/**
 * @brief controlInterface::SetDisplayMode(qint32 mDisMode)
 * @note  set display mode like indoor,outdoor or night
 * @author Tony
 * @time   2019/06/14
 */
void controlInterface::SetDisplayMode(qint32 mDisMode)
{
    if(globalUserVariable->gDisplayMode != mDisMode){
        globalUserVariable->gDisplayMode = mDisMode;
        emit infoRefresh(SA_INFO_SYSTEM,SA_INFO_SYSTEM_DISPLAYMODE);
    }
    return;
}
/**
 * @brief controlInterface::GetDisplayMode()
 * @note  get display mode like indoor,outdoor or night
 * @author Tony
 * @time   2019/06/14
 */
qint32 controlInterface::GetDisplayMode()
{
    return globalUserVariable->gDisplayMode;
}

/**
 * @brief controlInterface::setCurrentMode
 * @param mode
 */
void controlInterface::setCurrentMode(quint32 mode)
{
    globalUserVariable->currentMode = mode;
}

/**
 * @brief controlInterface::getCurrentMode
 * @return
 */
quint32 controlInterface::getCurrentMode()
{
    return globalUserVariable->currentMode;
}
/**
 * @brief controlInterface::LoadParamControl
 * @note  send control code to FPGA after para loaded
 * @author Johnson
 * @time   2018/11/27
 */
void controlInterface::LoadParamControl()
{
#if 1
                                                bParaLoad = true;
    globalUserVariable->gIgnoreLimit = 1;
    globalUserVariable->gAutoRepeat = 0;
    qreal qSweepTime = globalUserVariable->gSweepTime;
    //*************************************Demodulation Control
    //DemodulationParaControl(currentMode);
    //Johnson 190925
    qint32 rbwIndex = bitaloth->GetrbwIndex((qreal)globalUserVariable->gRbw);
    bitaloth->ParamConvertByRbw(rbwIndex);
    //**************************************Span Control
    SpanParaControl();
    //**************************************SA_BW Control
    BWParaControl();
    //**************************************Amplitude Control
    AmplitudeParaControl();
    //**************************************Trace Control
    TraceParaControl();
    //**************************************Sweep Control
    SweepParaControl(qSweepTime);
    //**************************************Trigger Control
    TriggerParaControl();
    //**************************************Marker Control
    MarkerParaControl();
    //**************************************Peak Control (When SA_ACP and SweepMode ,open Peak)

    //**************************************Limit Control(When measure ,close Limit;when sweepmode,close limit)
    //LimitParaControl();//Johnson 190517
    globalUserVariable->gIgnoreLimit = 0;
    globalUserVariable->gAutoRepeat  = 1;
    bParaLoad = false;
#else
    if(0 == globalUserVariable->gSpanFreq)
    {
        globalUserVariable->gStartFreq = globalUserVariable->gStopFreq = globalUserVariable->gCenterFreq;
    }
    else
    {
        globalUserVariable->adjustFreqBySpan(globalUserVariable->gSpanFreq);
    }
    globalUserVariable->stepFreqCalculatorFunc();
    globalUserVariable->markerPositionReCalculatorFunc();

    initTraceAverage();
#endif
    //globalUserVariable->gMeasureStatus = SA_ON;
}
/**
 * @brief controlInterface::DemodulationParaControl
 * @note  send demodulation control code to FPGA after para loaded
 * @author Johnson
 * @time   2018/11/30
 */

void controlInterface::DemodulationParaControl()
{
    //setDemodulation(globalUserVariable->gDemodulationType);
}
/**
 * @brief controlInterface::BWParaControl
 * @note  send SA_BW control code to FPGA after para loaded
 * @author Johnson
 * @time   2018/11/30
 */

void controlInterface::BWParaControl()
{
#if 0
    if (globalUserVariable->gAutoRbw == SA_ON)
    {
        setAutoRbwStatus(SA_ON);
    }
    else
    {
        setRbwValue(globalUserVariable->gRbw);
    }

    if (globalUserVariable->gAutoVbw == SA_ON)
    {
        setAutoVbwStatus(SA_ON);
    }
    else
    {
        setVbwValue(globalUserVariable->gVbw);
    }
#else
    setRbwValue(globalUserVariable->gRbw);
    setVbwValue(globalUserVariable->gVbw);
#endif

    setIFMode(globalUserVariable->uIFMode);
    //bwSweepSettingDisplayFunc();
}

/**
 * @brief controlInterface::SpanParaControl
 * @note  send Span control code to FPGA after para loaded
 * @author Johnson
 * @time   2018/11/30
 */
void controlInterface::SpanParaControl()
{
    //SecondaryAction = SA_SPAN;

    //setSpan(globalUserVariable->gSpanFreq);
    //Tony 190613
    if(!globalUserVariable->gSpanFreq)
    {
        setZeroSpan();
    }
    else
        setSpan(globalUserVariable->gSpanFreq);
    //Tony 0610 for refresh channel standar para
    globalUserVariable->adjustCHStandarByCerFreq(globalUserVariable->gCenterFreq);

    //bwSweepSettingDisplayFunc();
}

/**
 * @brief controlInterface::AmplitudeParaControl
 * @note  send Amplitude control code to FPGA after para loaded
 * @author Johnson
 * @time   2018/11/30
 */
void controlInterface::AmplitudeParaControl()
{
    setAmpUnit(globalUserVariable->gAmptdUnit);
    setScaleDiv(globalUserVariable->gScaleDiv);
    setAttenStatus(globalUserVariable->gAtten);
    setPreampStatus(globalUserVariable->gPreamp);
    setRefLevel(globalUserVariable->gRefLevel);
    setRefOffset(globalUserVariable->gRefOffset);
    //setAutoScale(globalUserVariable->gAutoScale);
    setAutoAttenTrackStatus(globalUserVariable->gAutoAttenTrack);

    globalUserVariable->topLevel = globalUserVariable->gRefLevel+globalUserVariable->gRefOffset;
    globalUserVariable->lowLevel = globalUserVariable->topLevel - GRID_NUM_Y_TICKS*globalUserVariable->gScaleDiv;
    //variableSettingDisplayFunc();
}

/**
 * @brief controlInterface::TraceParaControl
 * @note  send Trace control code to FPGA after para loaded
 * @author Johnson
 * @time   2018/11/30
 */
void controlInterface::TraceParaControl()
{
    setTraceSelect(globalUserVariable->gTraceSelect);

    //Johnson 190320 change
    for(qint32 i = 0;i<NUM_TRACE;i++)
    {
        setTraceViewStatus(globalUserVariable->gTraceView[i],i);
        setTraceType(globalUserVariable->gTraceType[i],i);
        setTraceAverageStatus(globalUserVariable->gTraceAverage[i],i);
        if(globalUserVariable->gTraceAverage[i] == SA_ON)
        {
            setTraceAverageCount(globalUserVariable->gAverageCount[i],i);
        }
    }
    setDetectorMode(globalUserVariable->gDetectorMode);

    //traceScopeSettingFunc(globalUserVariable->gTraceSelect, globalUserVariable->gTraceType[globalUserVariable->gTraceSelect] );
    //bwSweepSettingDisplayFunc();
}

/**
 * @brief controlInterface::SweepParaControl
 * @note  send Sweep control code to FPGA after para loaded
 * @author Johnson
 * @time   2018/11/30
 */
void controlInterface::SweepParaControl(qreal gSweepTimeFromFile)
{
    //globalUserVariable->gAutoDotSweepTime = SA_AUTO;//Johnson 190802

    setSweepType(globalUserVariable->gSweepType);

    if(globalUserVariable->gAutoSweepTime == SA_OFF)
    {
        setAutoSweepTimeStatus(SA_ON);//Johnson 190802
        setSweepTime(gSweepTimeFromFile);
    }
    setAutoSweepTimeStatus(globalUserVariable->gAutoSweepTime);

#if 0
    setSweepSpeed(globalUserVariable->gSweepSpeed);
#endif

    //Johnson 190919 dotSweep Time.all the relatived param has used in the control of loadParam function
    //Johnson 190919 Gate Sweep
    setDoorControlSource(globalUserVariable->gDrCtrlSource);
}

/**
 * @brief controlInterface::TriggerParaControl
 * @author Johnson
 * @date 190709
 */
void controlInterface::TriggerParaControl()
{
    setTriggerMode(globalUserVariable->gTriggerMode);
    setTriggerDelayStatus(globalUserVariable->gTriggerDelayStatus[globalUserVariable->gTriggerMode]);
    setTriggerDelayValue(globalUserVariable->gTriggerDelayValue[globalUserVariable->gTriggerMode]);
    setTriggerSlope(globalUserVariable->gTriggerSlope[globalUserVariable->gTriggerMode]);
    setTriggerLevel(globalUserVariable->gTriggerLevel[globalUserVariable->gTriggerMode]);
    setTriggerPerTimer(globalUserVariable->gTriggerPerTimer);
}

/**
 * @brief controlInterface::MarkerParaControl
 * @note  send Marker control code to FPGA after para loaded
 * @author Johnson
 * @time   2018/11/30
 */
void controlInterface::MarkerParaControl()
{
    setMarkerSelect(globalUserVariable->gMarkerSelect);
    setMarkerDisplay(globalUserVariable->gMarkerDisplay);

    if(globalUserVariable->currentMode == SA_SPAN_MODE)
        setMarkerFreqCountStatus(globalUserVariable->gMarkerFreqCount[globalUserVariable->gMarkerSelect]);
    else
    {
        for(int i = 0;i<MARKER_TOTAL_CNT;i++)
        {
            if(globalUserVariable->gMarkerFreqCount[i] == SA_ON)
                setMarkerFreqCountStatus(SA_OFF,i);
        }
    }

    for(int i = 0;i<MARKER_TOTAL_CNT;i++)
    {
        //setMarkerNoiseStatus(globalUserVariable->gMarkerNoise[i],i);
        setMkrViewForResume(globalUserVariable->gMarkerView[i],i);
        //setMarkerViewStatus(globalUserVariable->gMarkerView[i],i);
        //setMarkerType(globalUserVariable->gMarkerType[i],i);
        globalUserVariable->gMarkerType[i] = globalUserVariable->gMarkerType[i];

        if(globalUserVariable->gMarkerType[i] == DELTA)
        {
            globalUserVariable->gMarkerRefDelta = 1;
        }
    }
}

/**
 * @brief controlInterface::LimitParaControl
 * @note  send Limit control code to FPGA after para loaded
 * @author Johnson
 * @time   2018/11/30
 */
void controlInterface::LimitParaControl()
{
    if(globalUserVariable->currentMode != SA_SPAN_MODE)
    {
        for(qint32 i = 0;i<LIMIT_SELECTSUM;i++)
        {
            globalUserLimit->gLimitLine[i]        = SA_OFF;
            globalUserLimit->gLimitEdge[i]        = SA_OFF;
            globalUserLimit->gLimitEdgeValue[i]   = 0.;
            globalUserLimit->gLatestLimitType[i]  = UPPER;
            globalUserLimit->gTotalDot[i]         = 0;
            globalUserLimit->gLatestLimitTestResult[i]      = SA_PASS;
            globalUserLimit->gLatestLimitEdgeResult[i]      = SA_PASS;
        }
        globalUserLimit->gLimitTest                = SA_OFF;
        globalUserLimit->gLimitSelect              = LIMIT1;
    }
}

void controlInterface::initTraceAverage()
{
    //clear spec
    for(qint32 i = 0;i < TRACE_CNT_TOTAL;i++)
    {
        globalUserVariable->gAverageNo[i] = 0;
        globalUserVariable->greAvager[i] = 1;
    }
    emit infoRefresh(SA_INFO_TRACE,SA_INFO_TRACE_CURAVE);
    return;
}
/**
 * @brief controlInterface::setRunMode
 * @note  set up running mode  0 local and 1 romote
 * @author Tony
 */
void controlInterface::SetLocalRemoteMode(qint32 imode)
{
    globalUserVariable->gRunMode = imode;
    //Operation when state changes.
    emit infoRefresh(SA_INFO_SYSTEM,SA_INFO_SYSTEM_MODE);
    return;
}
/**
 * @brief controlInterface::ChangeLcdStateWithNoSig
 * @note  set up lock state  0 unlock and 1 lock
 * @author Tony
 */
void controlInterface::ChangeLcdStateWithNoSig(qint32 ilock)
{
    globalUserVariable->gLockStatus = ilock;
    //Operation when state changes.
    emit infoRefresh(SA_INFO_SYSTEM,SA_INFO_SYSTEM_LOCKSTATUS);
    return;
}
/**
 * @brief controlInterface::GetLcdState
 * @author Tony
 */
qint32 controlInterface::GetLcdState()
{
    return globalUserVariable->gLockStatus;
}
qint32 controlInterface::GetLocalRemoteMode()
{
    return globalUserVariable->gRunMode;
}
void controlInterface::setCHStandard(qint32 index)
{
    if(globalUserVariable->gAutoRepeat)
    {
        //if(globalUserVariable->gTecIndex == index) return;
    }
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }
    qreal newCerFreq;
    globalUserVariable->gTecIndex = index;
    globalUserVariable->gChannelStep = mChStand[index].ChStep;
    if(index < 0)
        return;
    globalUserVariable->getBandInfo(index);
    newCerFreq = globalUserVariable->CalculateFreqByCHStandar() + globalUserVariable->gfreqOffset+globalUserVariable->gChannelStep/2;
    setCenterFreq(newCerFreq);
    emit infoRefresh(SA_INFO_FREQ,SA_INFO_CH_STANDARD);
    return;
}

qint32 controlInterface::getCHStandard()
{
    if(globalUserVariable->gTecIndex<0)
    {
        return -1;
    }
    qint32 index = mChStand[globalUserVariable->gTecIndex].index;
    return index;
}

void controlInterface::setCommuDirection(qint32 direction)
{
    if(globalUserVariable->gCommuDirection == direction) return;
//    if(globalUserVariable->gAutoRepeat)
//    {
//        if(globalUserVariable->gCommuDirection == direction) return;
//    }
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }
    qreal newCerFreq;
    globalUserVariable->gCommuDirection = direction;
    if(globalUserVariable->gTecIndex < 0)
        return;
    newCerFreq = globalUserVariable->CalculateFreqByCHStandar() + 0.5 * mChStand[globalUserVariable->gTecIndex].ChStep;
    setCenterFreq(newCerFreq);
    //    globalUserVariable->gCHName = standard;
    return;
}

qint32 controlInterface::getCommuDirection()
{
    return globalUserVariable->gCommuDirection;
}

void controlInterface::setChannelNumber(qint32 number)
{
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }
    qreal centerFreq,min,max,index;
    index = globalUserVariable->gCHIndex;
    if(globalUserVariable->gCommuDirection == SA_UPLINK)
    {
        min = globalUserVariable->gCHStandard->at(index).Up.Min;
        max = globalUserVariable->gCHStandard->at(index).Up.Max;
        number = number < min ? min : number;
        number = number > max ? max : number;
    }else if(globalUserVariable->gCommuDirection == SA_DOWNLINK)
    {
        min = globalUserVariable->gCHStandard->at(index).Down.Min;
        max = globalUserVariable->gCHStandard->at(index).Down.Max;
        number = number < min ? min : number;
        number = number > max ? max : number;
    }

    if(globalUserVariable->gAutoRepeat)
    {
        //if(globalUserVariable->gChannelNum == number) return;
    }

    globalUserVariable->gChannelNum = number;
    //Center Freq need modify
    centerFreq = globalUserVariable->CalculateFreqByCHNum(number) + +globalUserVariable->gChannelStep/2;
    setCenterFreq(centerFreq);
    return ;
}

/**
 * @brief controlInterface::getChannelNumber
 * @return
 */
qint32 controlInterface::getChannelNumber()
{
    return globalUserVariable->gChannelNum;
}


void controlInterface::setChannelNumStep(qint32 step)
{
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }


    if(globalUserVariable->gAutoRepeat)
    {
        //if(globalUserVariable->gChannelNum == number) return;
    }
    if(step < 1)
    {
        step = 1;
    }else if(step >500)
    {
        step = 500;
    }
    globalUserVariable->gChannelNumStep = step;
    return ;
}

/**
 * @brief controlInterface::getChannelStep
 * @return
 */
qint32 controlInterface::getChannelNumStep()
{
    return globalUserVariable->gChannelNumStep;
}


/**
 * @brief controlInterface::setIFMode
 * @param uifMode
 */
void controlInterface::setIFMode(quint32 uifMode)
{
    QString iVal = QString::number(uifMode);
    QString strCmd = ":IFOUtput ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }
    if(globalUserVariable->gAutoRepeat)
    {
        if(uifMode == globalUserVariable->uIFMode) return;
    }

    if(globalUserVariable->uIFMode == SA_AUTO_IFMODE && globalUserVariable->gZeroSpanAction == SA_OFF) return;

    if(uifMode != SA_AUTO_IFMODE && uifMode != SA_10M_IFMODE && uifMode != SA_100M_IFMODE)
    {
        uifMode = SA_AUTO_IFMODE;
    }

    if(globalUserVariable->gZeroSpanAction == SA_ON)
    {
        globalUserVariable->uIFMode = uifMode;
    }
    else
    {
        globalUserVariable->uIFMode = SA_AUTO_IFMODE;
    }
}

/**
 * @brief controlInterface::getIFMode
 * @return
 */
quint32 controlInterface::getIFMode()
{
    return globalUserVariable->uIFMode;
}

#if 0
/**
 * @brief controlInterface::setIFRef
 * @param uifRef
 */
void controlInterface::setIFRef(quint32 uifRef)
{
    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }
    if(uifRef != SA_EXT_GPS_REFINPUT && uifRef != SA_EXT_10M_REFINPUT
            && uifRef != SA_EXT_13M_REFINPUT && uifRef != SA_EXT_15M_REFINPUT && uifRef != SA_INT_10M_REFINPUT)
    {
        uifRef = SA_INT_10M_REFINPUT;
    }
    globalUserVariable->uIFRef = uifRef;
    //SA_sm_config_sweep->uIFRef = uifRef;
    //SA_Set_config_flag(IXT_SA_ConfigSweep,IXS_SA_IFRef);
}

/**
 * @brief controlInterface::getIFRef
 * @return
 */
quint32 controlInterface::getIFRef()
{
    return globalUserVariable->uIFRef;
}

/**
 * @brief controlInterface::setBrtLevel
 * @param uBrtLevel
 */
void controlInterface::setBrtLevel(quint32 uBrtLevel)
{
    if(uBrtLevel < SA_BRTLEVEL1 || uBrtLevel > SA_BRTLEVEL5)
    {
        uBrtLevel = SA_BRTLEVEL1;
    }
    globalUserVariable->uBrtLevel = uBrtLevel;
    //SA_sm_config_sweep->uBrightnessLevel = uBrtLevel;
    //SA_Set_config_flag(IXT_SA_ConfigSweep,IXS_SA_BrightnessLevel);
}

/**
 * @brief controlInterface::getBrtLevel
 * @return
 */
quint32 controlInterface::getBrtLevel()
{
    return globalUserVariable->uBrtLevel;
}
#endif

/**
 * @brief controlInterface::PltSavePres
 * @param itype
 * @return
 */
qint32 controlInterface::PltSavePres(qint32 itype)
{
    if(itype<0 || itype>2) return -1;

    if(!pparaSaveLoad->preStateSave(itype)) return -1;

    return 0;
}

/**
 * @brief controlInterface::PltSaveConditions
 * @param itype 0 Preset Status,1 Last Status,2 User Status
 * @return <0 fail,=0 success
 */
qint32 controlInterface::PltSaveConditions(qint32 itype)
{
    if(itype<0 || itype>2) return -1;

    if(!pparaSaveLoad->allModeParaSave(globalUserVariable->currentMode,itype)) return -1;

    return 0;
}

/**
 * @brief controlInterface::PltLoadConditions
 * @param itype 0 Preset Status,1 Last Status,2 User Status
 * @return <0 fail,=0 success
 */
qint32 controlInterface::PltLoadConditions(qint32 itype, qint32 presetFlag)
{
    if(itype<0 || itype>2) return -1;
    if(!pparaSaveLoad->allModeParaLoad(presetFlag,itype)) return -1;
    //LoadParamControl();
    return 0;
}
/**
 * @brief controlInterface::PltCurAnaMode
 * @param imod
 * @param ipreset
 */
void controlInterface::PltCurAnaMode(qint32 imod)
{
    globalUserVariable->startMode   = imod;
}

void controlInterface::PresetDefaultStates()
{
    //Add preset controle Jonson 190815
    if(-1 != PltLoadConditions(0,1))
    {
        blockSignals(true);
        LoadParamControl();
        blockSignals(false);

        bDefaultStatesPreset = true;
    }
}

/**
 * @brief controlInterface::setIFOutPut
 * @return
 */

void controlInterface::setIFOutPut(qint32 uifMode)
{
    if(uifMode < 0 || uifMode > 2)
    {
        return;
    }
    QString iVal = QString::number(uifMode);
    QString strCmd = ":IFOUtput ";
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(!globalUserVariable->gIgnoreLimit)
    {
        if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE ||
                globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE      ||
                globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE    ||
                globalUserVariable->currentMode == SA_ACP_MEASURE_MODE            ||
                globalUserVariable->currentMode == SA_MULTI_ACP_MODE
                )
        {

            return;
        }
    }
    if(globalUserVariable->gAutoRepeat)
    {
        if(uifMode == globalUserVariable->uIFMode) return;
    }

    if(uifMode != SA_AUTO_IFMODE && uifMode != SA_10M_IFMODE && uifMode != SA_100M_IFMODE)
    {
        uifMode = SA_AUTO_IFMODE;
    }

    if(SA_AUTO_IFMODE != uifMode)
    {
        if(globalUserVariable->gZeroSpanAction != SA_ON)
        {
            globalUserVariable->uTmpRbw = globalUserVariable->gRbw; //Johnson 190709
            setZeroSpan();
            QThread::usleep(100000);

            globalUserVariable->gIFOutputSpanModeChange = 1;
        }
    }
    else if(globalUserVariable->gZeroSpanAction == SA_ON && globalUserVariable->gIFOutputSpanModeChange)
    {
        setLastSpan();
        QThread::usleep(100000);
        setRbwValue(globalUserVariable->uTmpRbw);

        globalUserVariable->gIFOutputSpanModeChange = 0;
    }
    globalUserVariable->uIFMode = uifMode;

    emit infoRefresh(SA_INFO_BW,SA_INFO_BW_IF_OUTPUT);
    return ;
}
/**
 * @brief controlInterface::getIFOutPut
 * @return
 */
qint32 controlInterface::getIFOutPut()
{
    return globalUserVariable->uIFMode;
}
/**
 * @brief controlInterface::LoadModeParam
 * @return
 */

void controlInterface::LoadModeParam()
{
    //init trace
    for(qint32 i =0;i<TRACE_CNT_TOTAL;i++)
    {
        setTraceViewStatus(SA_OFF,i);
        setTraceType(SA_CLEAR_WRITE,i);
        setTraceAverageStatus(SA_OFF,i);

        if(globalUserVariable->currentMode != SA_SPAN_MODE)
        {
            if(globalUserVariable->gMarkerFreqCount[i] == SA_ON)
                setMarkerFreqCountStatus(SA_OFF,i);
        }

    }
    setTraceSelect(TR1);
    setTraceViewStatus(SA_ON,TR1);
    setTraceType(SA_CLEAR_WRITE,TR1);
    setDetectorMode(SA_POSITIVE_PEAK);
    //init limit
    setDeleteLimitAll();
    return;
}

/**
 * @brief controlInterface::setBeginZeroRestrainCal
 */
void controlInterface::setBeginZeroRestrainCal()
{
    if(!bInitZeroRestrainSuc)
    {
        attenBegin = 55000;
        attenEnd = 65500;
        phaseBegin = 0;
        phaseEnd = 60;
        attenStep = 300;
        phaseStep = 2;
    }
    else
    {
        if(gZeroRestrain.uZeroRestainAtten < 500)
        {
            attenBegin = 0;
            attenEnd   = gZeroRestrain.uZeroRestainAtten + 500;
        }
        else if(gZeroRestrain.uZeroRestainAtten > 65535 - 500)
        {
            attenBegin = gZeroRestrain.uZeroRestainAtten - 500;
            attenEnd   = 65535;
        }
        else
        {
            attenBegin = gZeroRestrain.uZeroRestainAtten - 500;
            attenEnd   = gZeroRestrain.uZeroRestainAtten + 500;
        }

        if(gZeroRestrain.uZeroRestrainPhase < 10)
        {
            phaseBegin = 0;
            phaseEnd   = gZeroRestrain.uZeroRestrainPhase + 10;
        }
        else if(gZeroRestrain.uZeroRestrainPhase > 63 - 10)
        {
            phaseBegin = gZeroRestrain.uZeroRestrainPhase - 10;
            phaseEnd   = 63;
        }
        else
        {
            phaseBegin = gZeroRestrain.uZeroRestrainPhase - 10;
            phaseEnd   = gZeroRestrain.uZeroRestrainPhase + 10;
        }

        attenStep = 100;
        phaseStep = 1;
    }

    bZeroRestrainCalComplete = false;
    bZeroRestrainStatusSet   = false;
    //bInitZeroRestrainSuc     = false;
    bBeginAcqData            = false;
    bCalStop = false;
}

/**
 * @brief controlInterface::setZeroRestrainCalStop
 */
void controlInterface::setZeroRestrainCalStop()
{
    bCalStop = true;
}

/**
 * @brief controlInterface::ZeroRestrainCelibrate
 * @param phaseBegin
 * @param phaseEnd
 * @param attenBegin
 * @param attenEnd
 * @param phaseStep
 * @param attenStep
 * @return
 */
bool controlInterface::ZeroRestrainCelibrate()
{
    if(bZeroRestrainCalComplete) return true;
    if(bCalStop)
    {
        QThread::usleep(100000);
        //globalUserVariable->gCenterFreq = tmpCenterFreq;
        setCenterFreq(tmpCenterFreq);

        QThread::usleep(100000);
        //globalUserVariable->gSpanFreq = tmpSpanFreq;
        setSpan(tmpSpanFreq);

        if(bInitZeroRestrainSuc) setZeroRestrain(tmpZeroAtten,tmpZeroPhase * 5.625);

        bZeroRestrainCalComplete = true;

        emit(signalZeroCalComplete(false));

        return true;
    }

    if(!bZeroRestrainStatusSet)
    {
        if(bInitZeroRestrainSuc)
        {
            tmpZeroAtten = gZeroRestrain.uZeroRestainAtten;
            tmpZeroPhase = gZeroRestrain.uZeroRestrainPhase;
        }
        tmpCenterFreq = globalUserVariable->gCenterFreq;
        tmpSpanFreq   = globalUserVariable->gSpanFreq;

        setZeroSpan();
        QThread::usleep(100000);
        setCenterFreq(0);
        QThread::usleep(100000);

        ZeroRestrainPhase  = phaseBegin;//0;
        gZeroRestrain.uZeroRestrainPhase = phaseBegin;//0;
        ZeroRestrainAtten = attenBegin;//0;
        gZeroRestrain.uZeroRestainAtten  = attenBegin;//0;

        setZeroRestrain(gZeroRestrain.uZeroRestainAtten,gZeroRestrain.uZeroRestrainPhase * 5.625);

        bZeroRestrainStatusSet = true;
        return true;
    }

    if(!bZeroRestrainCalComplete)
    {
        qDebug()<<"ZeroRestrainAtten is "<<ZeroRestrainAtten<<";"<<"ZeroRestrainPhase is "<<ZeroRestrainPhase<<";"<<" Data is "<<globalUserVariable->gOriginalMeasureVal[10];

        if(ZeroRestrainAtten <= attenBegin)
        {
            if(bBeginAcqData)
            {
                if(ZeroRestrainPhase == phaseBegin/*0*/ && ZeroRestrainAtten == attenBegin/*0*/)
                {
                    minAmp = globalUserVariable->gOriginalMeasureVal[10];
                }
                else if(minAmp > globalUserVariable->gOriginalMeasureVal[10])
                {
                    minAmp = globalUserVariable->gOriginalMeasureVal[10];
                    gZeroRestrain.uZeroRestainAtten = ZeroRestrainAtten;
                    gZeroRestrain.uZeroRestrainPhase = ZeroRestrainPhase;
                }
            }
            else if(ZeroRestrainPhase >= phaseBegin + 5 * phaseStep && ZeroRestrainAtten == attenBegin)
            {
                bBeginAcqData = true;
                ZeroRestrainPhase = phaseBegin - phaseStep;
                ZeroRestrainAtten == attenBegin;
            }

            if(ZeroRestrainPhase < phaseEnd)//63)
            {
                //++ZeroRestrainPhase;
                ZeroRestrainPhase += phaseStep;
                setZeroRestrain(ZeroRestrainAtten,ZeroRestrainPhase * 5.625);
            }
            else
            {
                ZeroRestrainPhase = phaseBegin;//0;
                if(ZeroRestrainAtten < attenBegin) ZeroRestrainAtten += 5000;
                else if(ZeroRestrainAtten == attenBegin) ZeroRestrainAtten += attenStep;
                setZeroRestrain(ZeroRestrainAtten,ZeroRestrainPhase * 5.625);
            }
        }
        else if(ZeroRestrainAtten <= attenEnd)//65500)
        {
            if(minAmp > globalUserVariable->gOriginalMeasureVal[10])
            {
                minAmp = globalUserVariable->gOriginalMeasureVal[10];
                gZeroRestrain.uZeroRestainAtten = ZeroRestrainAtten;
                gZeroRestrain.uZeroRestrainPhase = ZeroRestrainPhase;
            }

            if(ZeroRestrainPhase < phaseEnd)//63)
            {
                //++ZeroRestrainPhase;
                ZeroRestrainPhase += phaseStep;
                setZeroRestrain(ZeroRestrainAtten,ZeroRestrainPhase * 5.625);
            }
            else
            {
                ZeroRestrainPhase = phaseBegin;//0;
                ZeroRestrainAtten += attenStep;
                if(ZeroRestrainAtten <= attenEnd)/*< 65535)*/ setZeroRestrain(ZeroRestrainAtten,ZeroRestrainPhase * 5.625);
            }
        }
        else
        {
            bZeroRestrainCalComplete = true;
            //bInitZeroRestrainSuc     = true;
        }
    }

    if(bZeroRestrainCalComplete)
    {
        QThread::usleep(100000);
        //globalUserVariable->gCenterFreq = tmpCenterFreq;
        setCenterFreq(tmpCenterFreq);

        QThread::usleep(100000);
        //globalUserVariable->gSpanFreq = tmpSpanFreq;
        setSpan(tmpSpanFreq);

        QThread::usleep(100000);
        setZeroRestrain(gZeroRestrain.uZeroRestainAtten,gZeroRestrain.uZeroRestrainPhase * 5.625);

        QDir dir(QString("."));
        QString path = dir.absolutePath();
        QString savePath("");
        savePath = QString("%1%2").arg(path).arg("/ZeroReatrainCalResult.ini");
        QFile f(savePath);
        if(!f.open(QIODevice::WriteOnly | QIODevice::Truncate)){   //QIODevice::Truncate   open the file and clear its content
            qDebug()<<"save variable fail!";
            emit(signalZeroCalComplete(false));
            return false;
        }
        f.write((char *)(&gZeroRestrain),sizeof(_ZERORESTRAIN_));
        f.close();
        qDebug()<<"save variable success!";
        qDebug()<<"ZeroRestainAtten:"<<gZeroRestrain.uZeroRestainAtten;
        qDebug()<<"ZeroRestrainPhase:"<<gZeroRestrain.uZeroRestrainPhase;
        emit(signalZeroCalComplete(true));

        bInitZeroRestrainSuc = true;

        return true;
    }
    return true;
}

/**
 * @brief controlInterface::setZeroRestrainFromFile
 * @return
 */
bool controlInterface::setZeroRestrainFromFile()
{
    FILE *pFile;
    pFile = fopen("ZeroReatrainCalResult.ini","r");

    if(!pFile)
    {
        qDebug()<<"Open file fail!";

        bInitZeroRestrainSuc = false;

        return false;
    }
    fseek(pFile,0,SEEK_END);
    if(!ftell(pFile)){
        qDebug()<<"The file is null!";
        fclose(pFile);

        bInitZeroRestrainSuc = false;

        return false;
    }
    fseek(pFile,0,SEEK_SET);
    //fread(pVariable,1,sizeof(_FILE_SAVE_LOAD_VARIABLE_),pFile);
    fread(&gZeroRestrain,sizeof(_ZERORESTRAIN_),1,pFile);
    fclose(pFile);
    qDebug()<<"Load variable success!";

    setZeroRestrain(gZeroRestrain.uZeroRestainAtten,gZeroRestrain.uZeroRestrainPhase);

    bInitZeroRestrainSuc = true;

    return true;
}

/**
 * @brief controlInterface::getFreqCount
 * @param centerFreq
 * @param fsr
 * @param rbwValue
 * @return
 */
qreal controlInterface::getFreqCount(qreal centerFreq,qint32 fsr,quint32 rbwValue)
{
    return bitaloth->caculateFreqCount(centerFreq,fsr,rbwValue);
}

void controlInterface::SetRawData(char* src)
{
    memcpy(globalUserVariable->gOriginalMeasureVal,src,sizeof(qreal)*NUM_SWEEP_POINT);
    return;
}
void controlInterface::SetDrawData(char* src)
{
    memcpy(globalUserVariable->gTraceMeasureVal,src,sizeof(qreal)*NUM_SWEEP_POINT*TRACE_CNT_TOTAL);
    return;
}
void controlInterface::SetAllData(char* src)
{
    memcpy(globalUserVariable->gOriginalMeasureVal,src,sizeof(qreal)*NUM_SWEEP_POINT);
    memcpy(globalUserVariable->gTraceMeasureVal,(char*)src + sizeof(qreal)*NUM_SWEEP_POINT,sizeof(qreal)*NUM_SWEEP_POINT*TRACE_CNT_TOTAL);
    return;
}

void controlInterface::GetRawData(char* dest)
{
    memcpy(dest,globalUserVariable->gOriginalMeasureVal,sizeof(qreal)*NUM_SWEEP_POINT);
    return;
}

void controlInterface::GetDrawData(char* dest)
{
    QByteArray test;
    memcpy(dest,globalUserVariable->gTraceMeasureVal,sizeof(qreal)*NUM_SWEEP_POINT*TRACE_CNT_TOTAL);
    qint32 iback = -1;
    test.append(dest,sizeof(qreal)*NUM_SWEEP_POINT*TRACE_CNT_TOTAL);
    while(true)
    {
        iback = test.indexOf("\r\n",iback+1);
        if(iback < 0)
            break;
    }
    return;
}
void controlInterface::GetAllData(char *dest)
{
    memcpy(dest,globalUserVariable->gOriginalMeasureVal,sizeof(qreal)*NUM_SWEEP_POINT);
    memcpy((char*)dest + sizeof(qreal)*NUM_SWEEP_POINT,globalUserVariable->gTraceMeasureVal,sizeof(qreal)*NUM_SWEEP_POINT*TRACE_CNT_TOTAL);
    return;
}

void controlInterface::sendFileToRemote(QString strFile,QString strSavePath)
{
    QByteArray data;
    qint32 len;
    QString strCmd;

    QFile mfile(strFile);
    if(!mfile.open(QIODevice::ReadOnly))
    {
        return;
    }
    data = mfile.readAll();
    len  =  data.size();
    mfile.close();

    strCmd = QString(":COMMunicate:TRANsport:FILe:SEND %1,%2,%3").arg(QString::number(len)).arg(strSavePath);
    emit sendSCPIcmd(strCmd);
    QThread::msleep(50);
    emit sendSCPIcmd(QString(data));
    //qmessage ok
}

void controlInterface::getFileFromRemote(QString strFile,QString strSavePath)
{
    QString strCmd;
    QString len;

    strCmd = QString(":COMMunicate:TRANsport:FILe:RECEive %1,%2").arg(strFile).arg(strSavePath);
    emit sendSCPIcmd(strCmd);
}


/*********Door Control Sweep Interface*************/
/**
 * @brief setDoorControlSource
 * @param uDrCtlSource
 */
void controlInterface::setDoorControlSource(qint32 uDrCtlSource)
{
    QString strCmd;
    QString iVal = QString::number(uDrCtlSource);

    strCmd = QString(":SWEEp:EGATe:SOURce ");
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(uDrCtlSource !=SA_EXTERN_TRIGGER && uDrCtlSource != SA_RFBURST_TRIGGER && uDrCtlSource != SA_PERIOD_TRIGGER)
    {
        globalUserVariable->gDrCtrlSource = -1;
        return;
    }
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gDrCtrlSource == uDrCtlSource) return;
    }

    globalUserVariable->gDrCtrlSource = uDrCtlSource;

    if(globalUserVariable->gDrCtrlSwitch == SA_OPEN_DCSWEEP)
    {
        switch(globalUserVariable->gDrCtrlSweepMode)
        {
        case SA_LO_DCSWEEPMODE:
        case SA_VEDIO_DCSWEEPMODE:
            if(globalUserVariable->ganamode == 3)
            {
                globalUserVariable->uTmpRbw = globalUserVariable->gRbw;
                setAutoRbwStatus(SA_OFF);
                setRbwValue(10000);
                QThread::usleep(200000);
            }
            break;
        case SA_FFT_DCSWEEPMODE:
            if(globalUserVariable->ganamode == 0)
            {
                globalUserVariable->uTmpRbw = globalUserVariable->gRbw;
                setAutoRbwStatus(SA_OFF);
                setRbwValue(3000);
                QThread::usleep(200000);
            }
            break;
        default: break;
        }
    }

    setGateViewStatus(globalUserVariable->gGateViewStatus);
    QThread::usleep(200000);
}

/**
 * @brief controlInterface::getDoorControlSource
 * @return
 */
qint32 controlInterface::getDoorControlSource()
{
    return globalUserVariable->gDrCtrlSource;
}

/**
 * @brief controlInterface::setLevleEdgeSelect
 * @param uLvlEdgSelect
 */
void controlInterface::setLevleEdgeSelect(qint32 uLvlEdgSelect)
{
    if(uLvlEdgSelect != SA_EDGE_MODE && uLvlEdgSelect != SA_LEVEL_MODE) return;
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gLvlEdgSelect == uLvlEdgSelect) return;
    }

    if(globalUserVariable->gDrCtrlSource == SA_PERIOD_TRIGGER)
    {
        globalUserVariable->gLvlEdgSelect = SA_EDGE_MODE;
    }
    else
    {
        globalUserVariable->gLvlEdgSelect = uLvlEdgSelect;
    }

    QString strCmd;
    QString iVal = QString::number(globalUserVariable->gLvlEdgSelect);

    strCmd = QString(":SWEEp:EGATe:CONTrol ");
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
}

/**
 * @brief controlInterface::getLevleEdgeSelect
 * @return
 */
qint32 controlInterface::getLevleEdgeSelect()
{
    return globalUserVariable->gLvlEdgSelect;
}

/**
 * @brief controlInterface::setLevleEdgeMode
 * @param uLvlEdgMode
 */
void controlInterface::setLevleEdgeMode(qint32 uLvlEdgMode)
{
    if(uLvlEdgMode != SA_POSITIVE_VALUE && uLvlEdgMode != SA_NEGATIVE_VALUE) return;
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gLvlEdgMode == uLvlEdgMode) return;
    }

    globalUserVariable->gLvlEdgMode = uLvlEdgMode;

    QString strCmd;
    QString iVal = QString::number(globalUserVariable->gLvlEdgMode);

    strCmd = QString(":SWEEp:EGATe:VALUe ");
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
}

/**
 * @brief controlInterface::getLevleEdgeMode
 * @return
 */
qint32 controlInterface::getLevleEdgeMode()
{
    return globalUserVariable->gLvlEdgMode;
}

/**
 * @brief controlInterface::setDoorControlSweepMode
 * @param uDrCtlSweepMode
 */
void controlInterface::setDoorControlSweepMode(qint32 uDrCtlSweepMode)
{
    if(uDrCtlSweepMode !=SA_LO_DCSWEEPMODE && SA_VEDIO_DCSWEEPMODE != uDrCtlSweepMode && SA_FFT_DCSWEEPMODE != uDrCtlSweepMode) return;

    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gDrCtrlSweepMode == uDrCtlSweepMode) return;
    }

    globalUserVariable->gDrCtrlSweepMode = uDrCtlSweepMode;

    QString strCmd;
    QString iVal = QString::number(globalUserVariable->gDrCtrlSweepMode);

    strCmd = QString(":SWEEp:EGATe:METHod ");
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(getDoorControlSwitch() == SA_OPEN_DCSWEEP)
    {
        switch(uDrCtlSweepMode)
        {
        case SA_LO_DCSWEEPMODE:
        case SA_VEDIO_DCSWEEPMODE:
            if(globalUserVariable->ganamode == 3)
            {
                globalUserVariable->uTmpRbw = globalUserVariable->gRbw;
                setAutoRbwStatus(SA_OFF);
                setRbwValue(10000);
                QThread::usleep(200000);
            }
            break;
        case SA_FFT_DCSWEEPMODE:
            if(globalUserVariable->ganamode == 0)
            {
                globalUserVariable->uTmpRbw = globalUserVariable->gRbw;
                setAutoRbwStatus(SA_OFF);
                setRbwValue(3000);
                QThread::usleep(200000);
            }
            break;
        default: break;
        }
    }

}

/**
 * @brief controlInterface::getDoorControlSweepMode
 * @return
 */
qint32 controlInterface::getDoorControlSweepMode()
{
    return globalUserVariable->gDrCtrlSweepMode;
}

/**
 * @brief controlInterface::setPeriodTrigSynchroSrc
 * @param uPrdTrgSyncSrc
 */
void controlInterface::setPeriodTrigSynchroSrc(qint32 uPrdTrgSyncSrc)
{
    QString strCmd;
    QString iVal = QString::number(uPrdTrgSyncSrc);

    strCmd = QString(":SWEEp:EGATe:SYCH:SOURce ");
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(globalUserVariable->gDrCtrlSource != SA_PERIOD_TRIGGER) return;
    if(uPrdTrgSyncSrc < 0 || uPrdTrgSyncSrc >2) return;
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gPrdTrgSynchroSrc == uPrdTrgSyncSrc) return;
    }

    globalUserVariable->gPrdTrgSynchroSrc = uPrdTrgSyncSrc;
}

/**
 * @brief controlInterface::getPeriodTrigSynchroSrc
 * @return
 */
qint32 controlInterface::getPeriodTrigSynchroSrc()
{
    if(globalUserVariable->gDrCtrlSource != SA_PERIOD_TRIGGER) return 3;
    return globalUserVariable->gPrdTrgSynchroSrc;
}

/**
 * @brief controlInterface::setDoorControlSwitch
 * @param uDrCtlSwitch
 */
void controlInterface::setDoorControlSwitch(qint32 uDrCtlSwitch)
{
    if(uDrCtlSwitch != SA_CLOSE_DCSWEEP && uDrCtlSwitch != SA_OPEN_DCSWEEP) return;

    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gDrCtrlSwitch == uDrCtlSwitch) return;
    }

    globalUserVariable->gDrCtrlSwitch = uDrCtlSwitch;

    QString strCmd;
    QString iVal = QString::number(globalUserVariable->gDrCtrlSwitch);

    strCmd = QString(":SWEEp:EGATe:STATe ");
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(uDrCtlSwitch == SA_OPEN_DCSWEEP)
    {
        switch(getDoorControlSweepMode())
        {
        case SA_LO_DCSWEEPMODE:
        case SA_VEDIO_DCSWEEPMODE:
            if(globalUserVariable->ganamode == 3)
            {
                globalUserVariable->uTmpRbw = globalUserVariable->gRbw;
                setAutoRbwStatus(SA_OFF);
                setRbwValue(10000);
                QThread::usleep(200000);
            }
            break;
        case SA_FFT_DCSWEEPMODE:
            if(globalUserVariable->ganamode == 0)
            {
                globalUserVariable->uTmpRbw = globalUserVariable->gRbw;
                setAutoRbwStatus(SA_OFF);
                setRbwValue(3000);
                QThread::usleep(200000);
            }
            break;
        default: break;
        }
    }
    else
    {
        setGateViewStatus(SA_GATE_VIEW_CLOSE);
    }

}

/**
 * @brief controlInterface::getDoorControlSwitch
 * @return
 */
qint32 controlInterface::getDoorControlSwitch()
{
    return globalUserVariable->gDrCtrlSwitch;
}

/**
 * @brief controlInterface::setEdgeTrigDely
 * @param edgTrgDely
 */
void controlInterface::setEdgeTrigDely(qreal edgTrgDely)
{
    if(edgTrgDely - 20000.> 0.) edgTrgDely = 20000.;
    else if(edgTrgDely < 0.) edgTrgDely = 0.;
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gEdgTrigDely == edgTrgDely) return;
    }

    if(globalUserVariable->gLvlEdgSelect != SA_EDGE_MODE) return;

    globalUserVariable->gEdgTrigDely = edgTrgDely;

    QString strCmd;
    QString iVal = QString::number(globalUserVariable->gEdgTrigDely);

    strCmd = QString(":SWEEp:EGATe:DELAy ");
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
}

/**
 * @brief controlInterface::getEdgeTrigDely
 * @return
 */
qreal controlInterface::getEdgeTrigDely()
{
    if(globalUserVariable->gLvlEdgSelect != SA_EDGE_MODE) return 0.;
    return globalUserVariable->gEdgTrigDely;
}

/**
 * @brief controlInterface::setEdgeTrigDoorWidth
 * @param edgTrgDrWidth
 */
void controlInterface::setEdgeTrigDoorWidth(qreal edgTrgDrWidth)
{
    if(edgTrgDrWidth - 20000.> 0.) edgTrgDrWidth = 20000.;
    else if(edgTrgDrWidth < 0.) edgTrgDrWidth = 0.;
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gEdgTrigDoorWdth== edgTrgDrWidth) return;
    }
    if(globalUserVariable->gLvlEdgSelect != SA_EDGE_MODE) return;

    globalUserVariable->gEdgTrigDoorWdth = edgTrgDrWidth;

    QString strCmd;
    QString iVal = QString::number(globalUserVariable->gEdgTrigDoorWdth);

    strCmd = QString(":SWEEp:EGATe:LENGth ");
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
}

/**
 * @brief controlInterface::getEdgeTrigDoorWidth
 * @return
 */
qreal controlInterface::getEdgeTrigDoorWidth()
{
    if(globalUserVariable->gLvlEdgSelect != SA_EDGE_MODE) return 0.;
    return globalUserVariable->gEdgTrigDoorWdth;
}

/**
 * @brief controlInterface::setEdgeTrigPreventStatus
 * @param uEdgTrgPrvntStatus
 */
void controlInterface::setEdgeTrigPreventStatus(qint32 uEdgTrgPrvntStatus)
{
    if(uEdgTrgPrvntStatus != SA_CLOSE_PRVTSTATUS && uEdgTrgPrvntStatus != SA_OPEN_PRVTSTATUS) return;
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gEdgTrigPrvntStatus == uEdgTrgPrvntStatus) return;
    }

    if(globalUserVariable->gLvlEdgSelect != SA_EDGE_MODE) return;

    globalUserVariable->gEdgTrigPrvntStatus = uEdgTrgPrvntStatus;

    QString strCmd;
    QString iVal = QString::number(globalUserVariable->gEdgTrigPrvntStatus);

    strCmd = QString(":SWEEp:EGATe:PREVent:STATe ");
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
}

/**
 * @brief controlInterface::getEdgeTrigPreventStatus
 * @return
 */
qint32 controlInterface::getEdgeTrigPreventStatus()
{
    if(globalUserVariable->gLvlEdgSelect != SA_EDGE_MODE) return 0;
    return globalUserVariable->gEdgTrigPrvntStatus;
}

/**
 * @brief controlInterface::setEdgeTrigPreventTimes
 * @param prvntTime
 */
void controlInterface::setEdgeTrigPreventTimes(qreal prvntTime)
{
    if(prvntTime - 20000.> 0.) prvntTime = 20000.;
    else if(prvntTime < 0.) prvntTime = 0.;
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gEdgTrigPrvntTimes == prvntTime) return;
    }
    if(globalUserVariable->gLvlEdgSelect != SA_EDGE_MODE) return;

    globalUserVariable->gEdgTrigPrvntTimes = prvntTime;

    QString strCmd;
    QString iVal = QString::number(globalUserVariable->gEdgTrigPrvntTimes);

    strCmd = QString(":SWEEp:EGATe:PREVent:TIME ");
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
}

/**
 * @brief controlInterface::getEdgeTrigPreventTimes
 * @return
 */
qreal controlInterface::getEdgeTrigPreventTimes()
{
    if(globalUserVariable->gLvlEdgSelect != SA_EDGE_MODE) return 0;
    return globalUserVariable->gEdgTrigPrvntTimes;
}

/**
 * @brief setRFBurstTrigLevel
 * @param trigLevel
 * @param uDrCtlSource
 */
void controlInterface::setRFBurstTrigLevel(qreal trigLevel)
{
    QString strCmd;
    QString iVal = QString::number(trigLevel);

    strCmd = QString(":SWEEp:EGATe:TRIGger:LEVEl ");
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gRFBurstTrigLevel == trigLevel) return;
    }

    if(trigLevel > 20.) trigLevel = 20.;
    else if(trigLevel < -170.) trigLevel = -170.;

    globalUserVariable->gRFBurstTrigLevel = trigLevel;
}

/**
 * @brief controlInterface::getRFBurstTrigLevel
 * @param uDrCtlSource
 * @return
 */
qreal controlInterface::getRFBurstTrigLevel()
{
    return globalUserVariable->gRFBurstTrigLevel;
}

/**
 * @brief controlInterface::setPeriodTrigPeriod
 * @param period
 */
void controlInterface::setPeriodTrigPeriod(qreal period)
{
    QString strCmd;
    QString iVal = QString::number(period);

    strCmd = QString(":SWEEp:EGATe:PERIod ");
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(globalUserVariable->gDrCtrlSource != SA_PERIOD_TRIGGER) return;
    if(period - 20000. > 0.) period = 20000.;
    else if(period < 0.) period = 0.;
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gPrdTrgPeriod == period) return;
    }

    globalUserVariable->gPrdTrgPeriod = period;
}

/**
 * @brief controlInterface::getPeriodTrigPeriod
 * @return
 */
qreal controlInterface::getPeriodTrigPeriod()
{
    if(globalUserVariable->gDrCtrlSource != SA_PERIOD_TRIGGER) return 0.;
    return globalUserVariable->gPrdTrgPeriod;
}

/**
 * @brief controlInterface::setPeriodTrigSrcDelay
 * @param srcDely
 */
void controlInterface::setPeriodTrigSrcDelay(qreal srcDely)
{
    QString strCmd;
    QString iVal = QString::number(srcDely);

    strCmd = QString(":SWEEp:EGATe:SYNSrcdelay:TIME ");
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(globalUserVariable->gDrCtrlSource != SA_PERIOD_TRIGGER) return;
    if(srcDely - 20000. > 0.) srcDely = 20000.;
    else if(srcDely < 0.) srcDely = 0.;
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gPrdTrgSrcDelay == srcDely) return;
    }

    globalUserVariable->gPrdTrgSrcDelay = srcDely;
}

/**
 * @brief controlInterface::getPeriodTrigSrcDelay
 * @return
 */
qreal controlInterface::getPeriodTrigSrcDelay()
{
    if(globalUserVariable->gDrCtrlSource != SA_PERIOD_TRIGGER) return 0.;
    return globalUserVariable->gPrdTrgSrcDelay;
}

/**
 * @brief controlInterface::setPeriodTrigPreventStatus
 * @param uPrdTrgPrvntStatus
 */
void controlInterface::setPeriodTrigPreventStatus(qint32 uPrdTrgPrvntStatus)
{
    QString strCmd;
    QString iVal = QString::number(uPrdTrgPrvntStatus);

    strCmd = QString(":SWEEp:EGATe:SRCPr:STATe ");
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(globalUserVariable->gDrCtrlSource != SA_PERIOD_TRIGGER) return;
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gPrdTrigPrvntStatus == uPrdTrgPrvntStatus) return;
    }

    globalUserVariable->gPrdTrigPrvntStatus = uPrdTrgPrvntStatus;
}

/**
 * @brief controlInterface::setPeriodTrigPreventStatus
 * @return
 */
qint32 controlInterface::getPeriodTrigPreventStatus()
{
    if(globalUserVariable->gDrCtrlSource != SA_PERIOD_TRIGGER) return 0;
    return globalUserVariable->gPrdTrigPrvntStatus;
}

/**
 * @brief controlInterface::setPeriodTrigPreventTimes
 * @param prvntTime
 */
void controlInterface::setPeriodTrigPreventTimes(qreal prvntTime)
{
    QString strCmd;
    QString iVal = QString::number(prvntTime);

    strCmd = QString(":SWEEp:EGATe:SRCPr:TIME ");
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(globalUserVariable->gDrCtrlSource != SA_PERIOD_TRIGGER) return;
    if(prvntTime - 20000. > 0.) prvntTime = 20000.;
    else if(prvntTime < 0.) prvntTime = 0.;
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gPrdTrigPrvntTimes == prvntTime) return;
    }

    globalUserVariable->gPrdTrigPrvntTimes = prvntTime;
//    SA_sm_config_sweep->PrdTrigPrvntTimes  = prvntTime;
//    SA_Set_config_flag(IXT_SA_ConfigDrCtrlSweep,IXS_SA_PrdTrigPrvtValue);
}

/**
 * @brief controlInterface::getPeriodTrigPreventTimes
 * @return
 */
qreal controlInterface::getPeriodTrigPreventTimes()
{
    if(globalUserVariable->gDrCtrlSource != SA_PERIOD_TRIGGER) return 0.;
    return globalUserVariable->gPrdTrigPrvntTimes;
}

/**
 * @brief controlInterface::setGateViewStatus
 * @param gateViewStatus
 * @author Johnson
 * @date 09-12-2019
 */
void controlInterface::setGateViewStatus(qint32 gateViewStatus)
{
    QString strCmd;
    QString iVal = QString::number(gateViewStatus);

    strCmd = QString(":SWEEp:EGATe:VIEW ");
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);

    if(gateViewStatus != SA_GATE_VIEW_CLOSE && gateViewStatus != SA_GATE_VIEW_OPEN) return;
    if(globalUserVariable->gAutoRepeat)
    {
        if(globalUserVariable->gGateViewStatus == gateViewStatus) return;
    }

    globalUserVariable->gGateViewStatus = gateViewStatus;

    if(gateViewStatus == SA_GATE_VIEW_OPEN)
    {
        if(globalUserVariable->gZeroSpanAction != SA_ON)
        {
            globalUserVariable->gDrCtrlRbw = globalUserVariable->gRbw;
            setZeroSpan();
            //QThread::usleep(100000);

            globalUserVariable->gGateSweepSpanChange = 1;
        }
        setLevleEdgeSelect(SA_EDGE_MODE);
    }
    else if(globalUserVariable->gZeroSpanAction == SA_ON && globalUserVariable->gGateSweepSpanChange)
    {
        setLastSpan();
        //QThread::usleep(100000);
        setRbwValue(globalUserVariable->gDrCtrlRbw);

        globalUserVariable->gGateSweepSpanChange = 0;
    }


}

/**
 * @brief controlInterface::getGateViewStatus
 * @return
 * @author Johnson
 * @date 09-12-2019
 */
qint32 controlInterface::getGateViewStatus()
{
    return globalUserVariable->gGateViewStatus;
}

/**
 * @brief controlInterface::setGateViewStartTime
 * @param startTime
 * @author Johnson
 * @date 09-12-2019
 */
void controlInterface::setGateViewStartTime(qreal startTime)
{
    QString strCmd;
    QString iVal = QString::number(startTime);

    strCmd = QString(":SWEEp:EGATe:VIEW:STARt ");
    strCmd += iVal;
    emit sendSCPIcmd(strCmd);
}

/**
 * @brief controlInterface::getGateViewStartTime
 * @return
 * @author Johnson
 * @date 09-12-2019
 */
qreal controlInterface::getGateViewStartTime()
{
    return 0;
}