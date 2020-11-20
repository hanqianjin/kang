#include "nr_scpi_limit.h"

#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;

scpi_result_t NR_LIMIT_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setLimitType(value);
    return SCPI_RES_OK;
}

scpi_result_t NR_LIMIT_UpperState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }

    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setLimitUpperOn(isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_LIMIT_UpperValue(scpi_t * context)
{
    qreal Value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamDouble(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setLimitUpperValue(Value);
    return SCPI_RES_OK;
}

scpi_result_t NR_LIMIT_LowerState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }

    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setLimitLowerOn(isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_LIMIT_LowerValue(scpi_t * context)
{
    qreal Value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamDouble(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setLimitLowerValue(Value);
    return SCPI_RES_OK;
}

scpi_result_t NR_LIMIT_AllOn(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    remoteinterface::getfgnrremotehandle()->setLimitAllOn();
    return SCPI_RES_OK;
}

scpi_result_t NR_LIMIT_ClearAll(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    remoteinterface::getfgnrremotehandle()->setLimitClearAll();
    return SCPI_RES_OK;
}

scpi_result_t NR_LIMIT_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getLimitType();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_LIMIT_UpperStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isLimitUpperOn())
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

scpi_result_t NR_LIMIT_UpperValueQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getLimitUpperValue();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_LIMIT_LowerStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isLimitLowerOn())
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

scpi_result_t NR_LIMIT_LowerValueQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getLimitLowerValue();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
