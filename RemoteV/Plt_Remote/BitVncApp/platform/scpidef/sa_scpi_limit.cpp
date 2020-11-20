#include "sa_scpi_limit.h"
#include "remoteinterface.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;

scpi_result_t GetFreqVal(scpi_t *context, quint64 *val);
scpi_result_t GetAmptVal(scpi_t *context, qreal *val);
//qreal wattsToDbmCalculatorFunc(qreal _watts);
//qreal voltToDbmCalculatorFunc(qreal _volt);

scpi_result_t SA_LIMIT_Select(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitSelect(value - 1);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT_SelectQ(scpi_t *context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitSelect();
    if(!SCPI_ResultInt(context, value + 1))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_LIMIT_DisplayState(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitLineStatus(value);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT_DisplayStateQ(scpi_t *context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitSelect();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT1_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitLineStatus(value,0);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT1_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitLineStatus(0);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT2_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitLineStatus(value,1);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT2_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitLineStatus(1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT3_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitLineStatus(value,2);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT3_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitLineStatus(2);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT4_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitLineStatus(value,3);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT4_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitLineStatus(3);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT5_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitLineStatus(value,4);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT5_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitLineStatus(4);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT6_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitLineStatus(value,5);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT6_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitLineStatus(5);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_LIMIT_EdgeState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitEdgeStatus(value);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT_EdgeStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitEdgeStatus();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT1_EdgeState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitEdgeStatus(value,0);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT1_EdgeStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitEdgeStatus(0);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT2_EdgeState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitEdgeStatus(value,1);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT2_EdgeStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitEdgeStatus(1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT3_EdgeState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitEdgeStatus(value,2);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT3_EdgeStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitEdgeStatus(2);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT4_EdgeState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitEdgeStatus(value,3);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT4_EdgeStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitEdgeStatus(3);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT5_EdgeState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitEdgeStatus(value,4);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT5_EdgeStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitEdgeStatus(4);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT6_EdgeState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitEdgeStatus(value,5);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT6_EdgeStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitEdgeStatus(5);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_LIMIT_EdgeValue(scpi_t * context)
{
    qreal ival = 0;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetAmptVal(context,&ival);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitEdgeValue(ival);
    }
    return iback;
}
scpi_result_t SA_LIMIT_EdgeValueQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitEdgeValue();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT1_EdgeValue(scpi_t * context)
{
    qreal ival = 0;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetAmptVal(context,&ival);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitEdgeValue(ival,0);
    }
    return iback;
}
scpi_result_t SA_LIMIT1_EdgeValueQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitEdgeValue(0);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT2_EdgeValue(scpi_t * context)
{
    qreal ival = 0;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetAmptVal(context,&ival);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitEdgeValue(ival,1);
    }
    return iback;
}
scpi_result_t SA_LIMIT2_EdgeValueQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitEdgeValue(1);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT3_EdgeValue(scpi_t * context)
{
    qreal ival = 0;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetAmptVal(context,&ival);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitEdgeValue(ival,2);
    }
    return iback;
}
scpi_result_t SA_LIMIT3_EdgeValueQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitEdgeValue(2);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT4_EdgeValue(scpi_t * context)
{
    qreal ival = 0;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetAmptVal(context,&ival);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitEdgeValue(ival,3);
    }
    return iback;
}
scpi_result_t SA_LIMIT4_EdgeValueQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitEdgeValue(3);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT5_EdgeValue(scpi_t * context)
{
    qreal ival = 0;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetAmptVal(context,&ival);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitEdgeValue(ival,4);
    }
    return iback;
}
scpi_result_t SA_LIMIT5_EdgeValueQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitEdgeValue(4);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT6_EdgeValue(scpi_t * context)
{
    qreal ival = 0;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetAmptVal(context,&ival);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitEdgeValue(ival,5);
    }
    return iback;
}
scpi_result_t SA_LIMIT6_EdgeValueQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitEdgeValue(5);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_LIMIT_TestState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitTestStatus(value);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT_TestStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitTestStatus();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_LIMIT_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitType(value);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitType();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT1_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitType(value,0);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT1_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitType(0);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT2_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitType(value,1);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT2_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitType(1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT3_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitType(value,2);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT3_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitType(2);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT4_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitType(value,3);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT4_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitType(3);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT5_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitType(value,4);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT5_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitType(4);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT6_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitType(value,5);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT6_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitType(5);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_LIMIT_AllDelete(scpi_t *context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getsaremotehandle()->pcontrolInterface->setDeleteLimitAll();
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT_Delete(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getsaremotehandle()->pcontrolInterface->setDeleteLimitOne();
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT1_Delete(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getsaremotehandle()->pcontrolInterface->setDeleteLimitOne(0);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT2_Delete(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getsaremotehandle()->pcontrolInterface->setDeleteLimitOne(1);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT3_Delete(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getsaremotehandle()->pcontrolInterface->setDeleteLimitOne(2);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT4_Delete(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getsaremotehandle()->pcontrolInterface->setDeleteLimitOne(3);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT5_Delete(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getsaremotehandle()->pcontrolInterface->setDeleteLimitOne(4);
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT6_Delete(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getsaremotehandle()->pcontrolInterface->setDeleteLimitOne(5);
    return SCPI_RES_OK;
}

scpi_result_t SA_LIMIT_Autolimit(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getsaremotehandle()->pcontrolInterface->setAutoLimit();
    return SCPI_RES_OK;
}

scpi_result_t SA_LIMIT_PointCountQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    //value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitTestStatus();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT_DeletePoint(scpi_t * context)
{
    qint32 value;
    qint32 index;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &index, true))
    {
        return SCPI_RES_ERR;
    }
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    //index = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitSelect();
    remoteinterface::getsaremotehandle()->pcontrolInterface->setDeleteLimitRow(index - 1,value - 1);
    return SCPI_RES_OK;
}

scpi_result_t SA_LIMIT_PointFreqData(scpi_t * context)
{
    qint32 point,limit;
    quint64 freq;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &limit, true))
    {
        return SCPI_RES_ERR;
    }
    if(!SCPI_ParamInt(context, &point, true))
    {
        return SCPI_RES_ERR;
    }
    scpi_result_t iback = GetFreqVal(context,&freq);
    if(iback)
      {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitFreq(limit - 1,point - 1,freq);
      }
    return iback;
}
scpi_result_t SA_LIMIT_PointFreqDataQ(scpi_t * context)
{
    qint32 point,limit;
    qreal freq;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &limit, true))
    {
        return SCPI_RES_ERR;
    }
    if(!SCPI_ParamInt(context, &point, true))
    {
        return SCPI_RES_ERR;
    }

    freq = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitFreq(limit - 1,point - 1);
    if(!SCPI_ResultDouble(context, freq))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_LIMIT_PointAmptData(scpi_t * context)
{
    qint32 point,limit;
    qreal  ampt;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &limit, true))
    {
        return SCPI_RES_ERR;
    }
    if(!SCPI_ParamInt(context, &point, true))
    {
        return SCPI_RES_ERR;
    }
    scpi_result_t iback = GetAmptVal(context,&ampt);
    if(iback)
      {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitAmpt(limit - 1,point - 1,ampt);
      }
    return iback;
}
scpi_result_t SA_LIMIT_PointAmptDataQ(scpi_t * context)
{
    qint32 point,limit;
    qreal ampt;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &limit, true))
    {
        return SCPI_RES_ERR;
    }
    if(!SCPI_ParamInt(context, &point, true))
    {
        return SCPI_RES_ERR;
    }
    ampt = remoteinterface::getsaremotehandle()->pcontrolInterface->getLimitAmpt(limit - 1,point - 1);
    if(!SCPI_ResultDouble(context, ampt))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}


scpi_result_t SA_LIMIT_LimitInsert(scpi_t * context)
{
    qint32 limit;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &limit, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setInsertLimitRow(limit - 1);
    return SCPI_RES_OK;
}


scpi_result_t SA_LIMIT_PointData(scpi_t * context)
{
    qint32 point,limit;
    qreal freq,ampt;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
     if(!SCPI_ParamInt(context, &limit, true))
    {
        return SCPI_RES_ERR;
    }

    if(!SCPI_ParamInt(context, &point, true))
    {
        return SCPI_RES_ERR;
    }
    if(!SCPI_ParamDouble(context, &freq, true))
    {
        return SCPI_RES_ERR;
    }
    if(!SCPI_ParamDouble(context, &ampt, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setLimitData(limit - 1,point - 1,(quint64)freq,ampt);
    return SCPI_RES_OK;
}

