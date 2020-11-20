#include "nr_scpi_amp.h"

#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;

extern scpi_result_t GetAmptVal(scpi_t *context, qreal *val);
extern qreal wattsToDbmCalculatorFunc(qreal _watts);
extern qreal voltToDbmCalculatorFunc(qreal _volt);

scpi_result_t NR_AMPLITUDE_AutoScale(scpi_t *context)
{
    Q_UNUSED(context)
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    remoteinterface::getfgnrremotehandle()->setAutoScale();
    return SCPI_RES_OK;
}

scpi_result_t NR_AMPLITUDE_Reflevel(scpi_t *context)
{
    qreal ival = 0;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    scpi_result_t iback = GetAmptVal(context,&ival);
    if(iback)
    {
        remoteinterface::getfgnrremotehandle()->setRefLevel(ival);
    }
    return iback;
}

scpi_result_t NR_AMPLITUDE_ScaleValue(scpi_t *context)
{
    qreal Value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamDouble(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setScaleDiv(Value);
    return SCPI_RES_OK;
}

scpi_result_t NR_AMPLITUDE_AutoAtten(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setAttenAuto(isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_AMPLITUDE_AttenValue(scpi_t *context)
{
    qreal Value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamDouble(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setAttenValue(Value);
    return SCPI_RES_OK;
}

scpi_result_t NR_AMPLITUDE_Preamp(scpi_t *context)
{
    qint32 Value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    bool isOn = (Value == 1);
    remoteinterface::getfgnrremotehandle()->setPreAmpOn(isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_AMPLITUDE_RLevelOffset(scpi_t *context)
{
    qreal Value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamDouble(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setExtOffset(Value);
    return SCPI_RES_OK;
}

scpi_result_t NR_AMPLITUDE_ReflevelQ(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getRefLevel();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_AMPLITUDE_ScaleValueQ(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getScaleDiv();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_AMPLITUDE_AutoAttenQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isAttenAuto())
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

scpi_result_t NR_AMPLITUDE_AttenValueQ(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getAttenValue();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_AMPLITUDE_PreampQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isPreAmpOn())
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

scpi_result_t NR_AMPLITUDE_RLevelOffsetQ(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getExtOffset();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
