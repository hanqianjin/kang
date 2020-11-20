#include "sa_scpi_trace.h"

#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"
extern SYSTEM_STATUS g_systemStatus;

scpi_result_t SA_TRACE_ViewStatus(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTraceViewStatus(value);
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE1_ViewStatus(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTraceViewStatus(value,0);
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE2_ViewStatus(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTraceViewStatus(value,1);
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE3_ViewStatus(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTraceViewStatus(value,2);
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE4_ViewStatus(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTraceViewStatus(value,3);
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE5_ViewStatus(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTraceViewStatus(value,4);
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE6_ViewStatus(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTraceViewStatus(value,5);
    return SCPI_RES_OK;
}

scpi_result_t SA_TRACE_Type(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTraceType(value);
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE1_Type(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTraceType(value,0);
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE2_Type(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTraceType(value,1);
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE3_Type(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTraceType(value,2);
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE4_Type(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTraceType(value,3);
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE5_Type(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTraceType(value,4);
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE6_Type(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTraceType(value,5);
    return SCPI_RES_OK;
}

scpi_result_t SA_TRACE_AveCount(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTraceAverageCount(value);
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE1_AveCount(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTraceAverageCount(value,0);
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE2_AveCount(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTraceAverageCount(value,1);
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE3_AveCount(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTraceAverageCount(value,2);
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE4_AveCount(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTraceAverageCount(value,3);
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE5_AveCount(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTraceAverageCount(value,4);
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE6_AveCount(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTraceAverageCount(value,5);
    return SCPI_RES_OK;
}

scpi_result_t SA_TRACE_DetectorType(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setDetectorMode(value);
    return SCPI_RES_OK;
}

scpi_result_t SA_TRACE_ViewStatusQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTraceViewStatus();
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE1_ViewStatusQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTraceViewStatus(0);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE2_ViewStatusQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTraceViewStatus(1);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE3_ViewStatusQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTraceViewStatus(2);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE4_ViewStatusQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTraceViewStatus(3);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE5_ViewStatusQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTraceViewStatus(4);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE6_ViewStatusQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTraceViewStatus(5);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}

scpi_result_t SA_TRACE_TypeQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTraceType();
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE1_TypeQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTraceType(0);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE2_TypeQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTraceType(1);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE3_TypeQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTraceType(2);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE4_TypeQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTraceType(3);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE5_TypeQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTraceType(4);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE6_TypeQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTraceType(5);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}

scpi_result_t SA_TRACE_AveCountQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTraceAverageCount();
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE1_AveCountQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTraceAverageCount(0);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE2_AveCountQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTraceAverageCount(1);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE3_AveCountQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTraceAverageCount(2);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE4_AveCountQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTraceAverageCount(3);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE5_AveCountQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTraceAverageCount(4);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRACE6_AveCountQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTraceAverageCount(5);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}

scpi_result_t SA_TRACE_DetectorTypeQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getDetectorMode();
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}

scpi_result_t SA_TRACE_DataQ(scpi_t * context)
{
    qint32 len = VNC_POINTCNT*sizeof(qreal)*7;
    char data[len];
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    remoteinterface::getsaremotehandle()->pcontrolInterface->GetAllData(data);
    if(!SCPI_ResultStringSize(context,data,len))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_TRACE_RawDataQ(scpi_t * context)
{
    qint32 len = VNC_POINTCNT*sizeof(qreal);
    char data[len];
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    remoteinterface::getsaremotehandle()->pcontrolInterface->GetRawData(data);

    if(!SCPI_ResultStringSize(context, data,len))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_TRACE_DrawDataQ(scpi_t * context)
{
    qint32 len = VNC_POINTCNT*sizeof(qreal)*6;
    char data[len];
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    remoteinterface::getsaremotehandle()->pcontrolInterface->GetDrawData(data);
    if(!SCPI_ResultStringSize(context, data,len))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
