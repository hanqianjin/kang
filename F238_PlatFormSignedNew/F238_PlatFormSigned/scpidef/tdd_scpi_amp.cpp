#include "tdd_scpi_amp.h"
#include "lte_scpi_def.h"

#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;
extern scpi_result_t GetAmptVal(scpi_t *context, qreal *val);

scpi_result_t TDD_AMPLITUDE_AutoScale(scpi_t *context)
{
    Q_UNUSED(context);
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_AMPL_AUTOSCALE);
    return SCPI_RES_OK;
}

scpi_result_t TDD_AMPLITUDE_Reflevel(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value = 0;
    scpi_result_t iback = GetAmptVal(context, &value);
    if(iback)
    {
        remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_AMPL_REFLEVEL, value);
    }
    return iback;
}

scpi_result_t TDD_AMPLITUDE_ScaleValue(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_AMPL_SCALE, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_AMPLITUDE_AutoAtten(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_AMPL_AUTOATTEN, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_AMPLITUDE_AttenValue(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_AMPL_ATTENVALUE, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_AMPLITUDE_Preamp(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_AMPL_PREAMP, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_AMPLITUDE_RLevelOffset(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_AMPL_REFOFFSET, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_AMPLITUDE_ReflevelQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_AMPL_REFLEVEL);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_AMPLITUDE_ScaleValueQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_AMPL_SCALE);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_AMPLITUDE_AutoAttenQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_AMPL_AUTOATTEN);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_AMPLITUDE_AttenValueQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_AMPL_ATTENVALUE);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_AMPLITUDE_PreampQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_AMPL_PREAMP);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_AMPLITUDE_RLevelOffsetQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_AMPL_REFOFFSET);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
