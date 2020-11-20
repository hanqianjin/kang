#include "nr_scpi_trace.h"

#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;

scpi_result_t NR_TRACE_Select(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setCheckedTrace(value);
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE_ViewStatus(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    bool isOn = (value == 1);
    qint32 id = remoteinterface::getfgnrremotehandle()->getCheckedTrace();
    remoteinterface::getfgnrremotehandle()->setTraceViewOn(id,isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE1_ViewStatus(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setTraceViewOn(1,isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE2_ViewStatus(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setTraceViewOn(2,isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE3_ViewStatus(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setTraceViewOn(3,isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE4_ViewStatus(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setTraceViewOn(4,isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE5_ViewStatus(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setTraceViewOn(5,isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE6_ViewStatus(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setTraceViewOn(6,isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    qint32 id = remoteinterface::getfgnrremotehandle()->getCheckedTrace();
    remoteinterface::getfgnrremotehandle()->setTraceType(id,value);
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE1_Type(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setTraceType(1,value);
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE2_Type(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setTraceType(2,value);
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE3_Type(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setTraceType(3,value);
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE4_Type(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setTraceType(4,value);
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE5_Type(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setTraceType(5,value);
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE6_Type(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setTraceType(6,value);
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE_AveCount(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setAverageCount(value);
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE_DetectorType(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setDetectorType(value);
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE_AllOn(scpi_t * context)
{
    Q_UNUSED(context)
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    remoteinterface::getfgnrremotehandle()->setTraceAllOn();
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE_ClearAll(scpi_t * context)
{
    Q_UNUSED(context)
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    remoteinterface::getfgnrremotehandle()->setTraceClearAll();
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE_SelectQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getCheckedTrace();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE_ViewStatusQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    qint32 id = remoteinterface::getfgnrremotehandle()->getCheckedTrace();
    if(remoteinterface::getfgnrremotehandle()->isTraceViewOn(id))
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

scpi_result_t NR_TRACE1_ViewStatusQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isTraceViewOn(1))
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

scpi_result_t NR_TRACE2_ViewStatusQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isTraceViewOn(2))
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

scpi_result_t NR_TRACE3_ViewStatusQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isTraceViewOn(3))
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

scpi_result_t NR_TRACE4_ViewStatusQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isTraceViewOn(4))
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

scpi_result_t NR_TRACE5_ViewStatusQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isTraceViewOn(5))
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

scpi_result_t NR_TRACE6_ViewStatusQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isTraceViewOn(6))
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

scpi_result_t NR_TRACE_TypeQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    qint32 id = remoteinterface::getfgnrremotehandle()->getCheckedTrace();
    value = remoteinterface::getfgnrremotehandle()->getTraceType(id);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE1_TypeQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getTraceType(1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE2_TypeQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getTraceType(2);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE3_TypeQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getTraceType(3);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE4_TypeQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getTraceType(4);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE5_TypeQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getTraceType(5);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE6_TypeQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getTraceType(6);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE_AveCountQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getAverageCount();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_TRACE_DetectorTypeQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getDetectorType();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
