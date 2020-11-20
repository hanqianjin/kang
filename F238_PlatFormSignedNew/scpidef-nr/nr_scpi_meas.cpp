#include "nr_scpi_meas.h".h"

#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;

extern scpi_result_t GetFreqVal(scpi_t *context, quint64 *val);

scpi_result_t NR_MEASURE_Mode(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->SetMeasureItems(value);
    return SCPI_RES_OK;
}

scpi_result_t NR_MEASURE_ModeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->GetMeasureItems();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_ChannelBw(scpi_t * context)
{
    quint64 ival = 0;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    scpi_result_t iback = GetFreqVal(context,&ival);
    if(iback)
    {
        remoteinterface::getfgnrremotehandle()->setCHBandwidth(ival);
    }
    return iback;
}

scpi_result_t NR_ChannelBwQ(scpi_t * context)
{
    quint64 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getCHBandwidth();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_CHPower_IntegrationBW(scpi_t * context)
{
    quint64 ival = 0;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    scpi_result_t iback = GetFreqVal(context,&ival);
    if(iback)
    {
        remoteinterface::getfgnrremotehandle()->setCPIntegrationBW(ival);
    }
    return iback;
}

scpi_result_t NR_CHPower_IntegrationBWQ(scpi_t * context)
{
    quint64 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getCPIntegrationBW();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_CHPower_LimitPower(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setCPLimitPowerOn(isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_CHPower_LimitPowerQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isCPLimitPowerOn())
    {
        value = 1;
    }
    else
    {
        value = 0;
    }

    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_CHPower_LimitPowerValue(scpi_t * context)
{
    qreal Value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamDouble(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setCPLimitPowerValue(Value);
    return SCPI_RES_OK;
}

scpi_result_t NR_CHPower_LimitPowerValueQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getCPLimitPowerValue();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_CHPower_LimitPsd(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setCPLimitPsdOn(isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_CHPower_LimitPsdQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isCPLimitPsdOn())
    {
        value = 1;
    }
    else
    {
        value = 0;
    }

    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_CHPower_LimitPsdValue(scpi_t * context)
{
    qreal Value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamDouble(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setCPLimitPsdValue(Value);
    return SCPI_RES_OK;
}

scpi_result_t NR_CHPower_LimitPsdValueQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getCPLimitPsdValue();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_CHPower_CfgPreset(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    remoteinterface::getfgnrremotehandle()->setCPCfgPreset();
    return SCPI_RES_OK;
}

scpi_result_t NR_OBWidth_Method(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setOBWMethod(isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_OBWidth_MethodQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->getOBWMethod())
    {
        value = 1;
    }
    else
    {
        value = 0;
    }

    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_OBWidth_Percent(scpi_t * context)
{
    qreal Value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamDouble(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setOBWPercent(Value);
    return SCPI_RES_OK;
}

scpi_result_t NR_OBWidth_PercentQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getOBWPercent();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_OBWidth_XdB(scpi_t * context)
{
    qreal Value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamDouble(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setOBWXdbValue(Value);
    return SCPI_RES_OK;
}

scpi_result_t NR_OBWidth_XdBQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getOBWXdbValue();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_OBWidth_Limit(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setOBWLimitOn(isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_OBWidth_LimitQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isOBWLimitOn())
    {
        value = 1;
    }
    else
    {
        value = 0;
    }

    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_OBWidth_LimitValue(scpi_t * context)
{
    quint64 ival = 0;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    scpi_result_t iback = GetFreqVal(context,&ival);
    if(iback)
    {
        remoteinterface::getfgnrremotehandle()->setOBWLimitValue(ival);
    }
    return iback;
}

scpi_result_t NR_OBWidth_LimitValueQ(scpi_t * context)
{
    quint64 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getOBWLimitValue();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_OBWidth_CfgPreset(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    remoteinterface::getfgnrremotehandle()->setOBWCfgPreset();
    return SCPI_RES_OK;
}

scpi_result_t NR_EIRPower_RxAntGain(scpi_t * context)
{
    qreal Value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamDouble(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setEIRPRxAntGain(Value);
    return SCPI_RES_OK;
}

scpi_result_t NR_EIRPower_RxAntGainQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getEIRPRxAntGain();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_EIRPower_DistanceToAnt(scpi_t * context)
{
    qreal Value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamDouble(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setEIRPDistanceToAnt(Value);
    return SCPI_RES_OK;
}

scpi_result_t NR_EIRPower_DistanceToAntQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getEIRPDistanceToAnt();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_EIRPower_DistanceUnit(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setEIRPDistanceUnit(value);
    return SCPI_RES_OK;
}

scpi_result_t NR_EIRPower_DistanceUnitQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getEIRPDistanceUnit();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_EIRPower_UpperLimit(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setEIRPUpperLimitOn(isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_EIRPower_UpperLimitQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isEIRPUpperLimitOn())
    {
        value = 1;
    }
    else
    {
        value = 0;
    }

    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_EIRPower_UpperLimitValue(scpi_t * context)
{
    qreal Value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamDouble(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setEIRPUpperLimitValue(Value);
    return SCPI_RES_OK;
}

scpi_result_t NR_EIRPower_UpperLimitValueQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getEIRPUpperLimitValue();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_EIRPower_LowerLimit(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setEIRPLowerLimitOn(isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_EIRPower_LowerLimitQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isEIRPLowerLimitOn())
    {
        value = 1;
    }
    else
    {
        value = 0;
    }

    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_EIRPower_LowerLimitValue(scpi_t * context)
{
    qreal Value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamDouble(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setEIRPLowerLimitValue(Value);
    return SCPI_RES_OK;
}

scpi_result_t NR_EIRPower_LowerLimitValueQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getEIRPLowerLimitValue();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_EIRPower_RxCableLoss(scpi_t * context)
{
    qreal Value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamDouble(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setEIRPRxCableLoss(Value);
    return SCPI_RES_OK;
}

scpi_result_t NR_EIRPower_RxCableLossQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getEIRPRxCableLoss();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_EIRPower_MaxHold(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    remoteinterface::getfgnrremotehandle()->setEIRPResetMaxHold();
    return SCPI_RES_OK;
}

scpi_result_t NR_EIRPower_CfgPreset(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    remoteinterface::getfgnrremotehandle()->setEIRPCfgPreset();
    return SCPI_RES_OK;
}

scpi_result_t NR_BEAM_SSBSubCaSpac(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setSSBSubCaSpacModeChange(value);
    return SCPI_RES_OK;
}

scpi_result_t NR_BEAM_SSBSubCaSpacQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getSSBSubCaSpacModeChange();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_BEAM_SSBOffset(scpi_t * context)
{
    quint64 ival = 0;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    scpi_result_t iback = GetFreqVal(context,&ival);
    if(iback)
    {
        remoteinterface::getfgnrremotehandle()->setSSBOffset(ival);
    }
    return iback;
}

scpi_result_t NR_BEAM_SSBOffsetQ(scpi_t * context)
{
    quint64 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getSSBOffset();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_BEAM_SinrThreshold(scpi_t * context)
{
    qreal Value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamDouble(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setMultiPciSinrThreshold(Value);
    return SCPI_RES_OK;
}

scpi_result_t NR_BEAM_SinrThresholdQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getMultiPciSinrThreshold();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_BEAM_ViewMode(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setMultiPciViewMode(value);
    return SCPI_RES_OK;
}

scpi_result_t NR_BEAM_ViewModeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getMultiPciViewMode();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
