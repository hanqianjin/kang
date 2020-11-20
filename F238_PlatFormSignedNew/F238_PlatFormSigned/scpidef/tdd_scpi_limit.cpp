#include "tdd_scpi_limit.h"
#include "lte_scpi_def.h"

#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;

scpi_result_t TDD_LIMIT_Type(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_LIMIT_TYPE, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_LIMIT_MeasureType(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_LIMIT_MEAS_TYPE, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_LIMIT_TestOn(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_LIMIT_TESTON, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_LIMIT_UpperValue(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_LIMIT_UPPERVALUE, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_LIMIT_LowerValue(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_LIMIT_LOWERVALUE, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_LIMIT_AllowedChange(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_LIMIT_ALLOWED, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_LIMIT_AllOn(scpi_t *context)
{
    Q_UNUSED(context);
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_LIMIT_ALLON);
    return SCPI_RES_OK;
}

scpi_result_t TDD_LIMIT_ClearAll(scpi_t *context)
{
    Q_UNUSED(context);
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_LIMIT_CLAERALL);
    return SCPI_RES_OK;
}

scpi_result_t TDD_LIMIT_TypeQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_LIMIT_TYPE);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_LIMIT_MeasureTypeQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_LIMIT_MEAS_TYPE);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_LIMIT_TestOnQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_LIMIT_TESTON);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_LIMIT_UpperValueQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_LIMIT_UPPERVALUE);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_LIMIT_LowerValueQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_LIMIT_LOWERVALUE);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_LIMIT_AllowedChangeQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_LIMIT_ALLOWED);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
