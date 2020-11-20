#include "fdd_scpi_trace.h"
#include "lte_scpi_def.h"

#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;

scpi_result_t FDD_TRACE_Select(scpi_t *context)
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
    remoteinterface::getfddremotehandle()->SCPI_ParamInt(LTE_SCPI_TRACE_SELECT, value);
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE_ViewStatus(scpi_t *context)
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
    remoteinterface::getfddremotehandle()->SCPI_ParamInt(LTE_SCPI_TRACE_DISPLAY, value);
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE1_ViewStatus(scpi_t *context)
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
    remoteinterface::getfddremotehandle()->SCPI_ParamInt(LTE_SCPI_TRACE_DISPLAY1, value);
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE2_ViewStatus(scpi_t *context)
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
    remoteinterface::getfddremotehandle()->SCPI_ParamInt(LTE_SCPI_TRACE_DISPLAY2, value);
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE3_ViewStatus(scpi_t *context)
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
    remoteinterface::getfddremotehandle()->SCPI_ParamInt(LTE_SCPI_TRACE_DISPLAY3, value);
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE4_ViewStatus(scpi_t *context)
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
    remoteinterface::getfddremotehandle()->SCPI_ParamInt(LTE_SCPI_TRACE_DISPLAY4, value);
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE5_ViewStatus(scpi_t *context)
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
    remoteinterface::getfddremotehandle()->SCPI_ParamInt(LTE_SCPI_TRACE_DISPLAY5, value);
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE6_ViewStatus(scpi_t *context)
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
    remoteinterface::getfddremotehandle()->SCPI_ParamInt(LTE_SCPI_TRACE_DISPLAY6, value);
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE_Type(scpi_t *context)
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
    remoteinterface::getfddremotehandle()->SCPI_ParamInt(LTE_SCPI_TRACE_TYPE, value);
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE1_Type(scpi_t *context)
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
    remoteinterface::getfddremotehandle()->SCPI_ParamInt(LTE_SCPI_TRACE_TYPE1, value);
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE2_Type(scpi_t *context)
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
    remoteinterface::getfddremotehandle()->SCPI_ParamInt(LTE_SCPI_TRACE_TYPE2, value);
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE3_Type(scpi_t *context)
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
    remoteinterface::getfddremotehandle()->SCPI_ParamInt(LTE_SCPI_TRACE_TYPE3, value);
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE4_Type(scpi_t *context)
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
    remoteinterface::getfddremotehandle()->SCPI_ParamInt(LTE_SCPI_TRACE_TYPE4, value);
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE5_Type(scpi_t *context)
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
    remoteinterface::getfddremotehandle()->SCPI_ParamInt(LTE_SCPI_TRACE_TYPE5, value);
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE6_Type(scpi_t *context)
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
    remoteinterface::getfddremotehandle()->SCPI_ParamInt(LTE_SCPI_TRACE_TYPE6, value);
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE_AveCount(scpi_t *context)
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
    remoteinterface::getfddremotehandle()->SCPI_ParamInt(LTE_SCPI_TRACE_AVECOUNT, value);
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE_DetectorType(scpi_t *context)
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
    remoteinterface::getfddremotehandle()->SCPI_ParamInt(LTE_SCPI_TRACE_DETECTOR, value);
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE_AllOn(scpi_t *context)
{
    Q_UNUSED(context);
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfddremotehandle()->SCPI_ParamInt(LTE_SCPI_TRACE_ALLON);
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE_ClearAll(scpi_t *context)
{
    Q_UNUSED(context);
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfddremotehandle()->SCPI_ParamInt(LTE_SCPI_TRACE_CLEARALL);
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE_SelectQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::getfddremotehandle()->SCPI_ResultInt(LTE_SCPI_TRACE_SELECT);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE_ViewStatusQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::getfddremotehandle()->SCPI_ResultInt(LTE_SCPI_TRACE_DISPLAY);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE1_ViewStatusQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::getfddremotehandle()->SCPI_ResultInt(LTE_SCPI_TRACE_DISPLAY1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE2_ViewStatusQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::getfddremotehandle()->SCPI_ResultInt(LTE_SCPI_TRACE_DISPLAY2);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE3_ViewStatusQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::getfddremotehandle()->SCPI_ResultInt(LTE_SCPI_TRACE_DISPLAY3);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE4_ViewStatusQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::getfddremotehandle()->SCPI_ResultInt(LTE_SCPI_TRACE_DISPLAY4);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE5_ViewStatusQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::getfddremotehandle()->SCPI_ResultInt(LTE_SCPI_TRACE_DISPLAY5);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE6_ViewStatusQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::getfddremotehandle()->SCPI_ResultInt(LTE_SCPI_TRACE_DISPLAY6);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE_TypeQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::getfddremotehandle()->SCPI_ResultInt(LTE_SCPI_TRACE_TYPE);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE1_TypeQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::getfddremotehandle()->SCPI_ResultInt(LTE_SCPI_TRACE_TYPE1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE2_TypeQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::getfddremotehandle()->SCPI_ResultInt(LTE_SCPI_TRACE_TYPE2);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE3_TypeQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::getfddremotehandle()->SCPI_ResultInt(LTE_SCPI_TRACE_TYPE3);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE4_TypeQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::getfddremotehandle()->SCPI_ResultInt(LTE_SCPI_TRACE_TYPE4);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE5_TypeQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::getfddremotehandle()->SCPI_ResultInt(LTE_SCPI_TRACE_TYPE5);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE6_TypeQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::getfddremotehandle()->SCPI_ResultInt(LTE_SCPI_TRACE_TYPE6);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE_AveCountQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::getfddremotehandle()->SCPI_ResultInt(LTE_SCPI_TRACE_AVECOUNT);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t FDD_TRACE_DetectorTypeQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::getfddremotehandle()->SCPI_ResultInt(LTE_SCPI_TRACE_DETECTOR);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
