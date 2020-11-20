#include "rtsa_scpi_limit.h"

#include "remoteinterface.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;

scpi_result_t GetDoubleFreqVal(scpi_t *context, qreal *val);
scpi_result_t GetAmptVal(scpi_t *context, qreal *val);
//qreal wattsToDbmCalculatorFunc(qreal _watts);
//qreal voltToDbmCalculatorFunc(qreal _volt);



scpi_result_t RTSA_LIMIT_Select(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setCurLimit(value - 1);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT_SelectQ(scpi_t *context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getCurLimit();
    if(!SCPI_ResultInt(context, value + 1))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_LIMIT_DisplayState(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setCurLimitOn(-1,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT_DisplayStateQ(scpi_t *context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsCurLimitOn(-1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT1_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setCurLimitOn(0,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT1_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsCurLimitOn(0);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT2_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setCurLimitOn(1,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT2_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsCurLimitOn(1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT3_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setCurLimitOn(2,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT3_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsCurLimitOn(2);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT4_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setCurLimitOn(3,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT4_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsCurLimitOn(3);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT5_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setCurLimitOn(4,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT5_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsCurLimitOn(4);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT6_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setCurLimitOn(5,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT6_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsCurLimitOn(5);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_LIMIT_EdgeState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarginOn(-1,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT_EdgeStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsMarginOn(-1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT1_EdgeState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarginOn(0,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT1_EdgeStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsMarginOn(0);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT2_EdgeState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarginOn(1,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT2_EdgeStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsMarginOn(1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT3_EdgeState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarginOn(2,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT3_EdgeStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsMarginOn(2);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT4_EdgeState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarginOn(3,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT4_EdgeStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsMarginOn(3);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT5_EdgeState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarginOn(4,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT5_EdgeStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsMarginOn(4);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT6_EdgeState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarginOn(5,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT6_EdgeStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsMarginOn(5);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_LIMIT_EdgeValue(scpi_t * context)
{
    qreal ival = 0;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetAmptVal(context,&ival);
    if(iback)
    {
        remoteinterface::getrtsaremotehandle()->InterfaceObj->setMargin(-1,ival);
    }
    return iback;
}
scpi_result_t RTSA_LIMIT_EdgeValueQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMargin(-1);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT1_EdgeValue(scpi_t * context)
{
    qreal ival = 0;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetAmptVal(context,&ival);
    if(iback)
    {
        remoteinterface::getrtsaremotehandle()->InterfaceObj->setMargin(0,ival);
    }
    return iback;
}
scpi_result_t RTSA_LIMIT1_EdgeValueQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMargin(0);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT2_EdgeValue(scpi_t * context)
{
    qreal ival = 0;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetAmptVal(context,&ival);
    if(iback)
    {
        remoteinterface::getrtsaremotehandle()->InterfaceObj->setMargin(1,ival);
    }
    return iback;
}
scpi_result_t RTSA_LIMIT2_EdgeValueQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMargin(1);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT3_EdgeValue(scpi_t * context)
{
    qreal ival = 0;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetAmptVal(context,&ival);
    if(iback)
    {
        remoteinterface::getrtsaremotehandle()->InterfaceObj->setMargin(2,ival);
    }
    return iback;
}
scpi_result_t RTSA_LIMIT3_EdgeValueQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMargin(2);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT4_EdgeValue(scpi_t * context)
{
    qreal ival = 0;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetAmptVal(context,&ival);
    if(iback)
    {
        remoteinterface::getrtsaremotehandle()->InterfaceObj->setMargin(3,ival);
    }
    return iback;
}
scpi_result_t RTSA_LIMIT4_EdgeValueQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMargin(3);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT5_EdgeValue(scpi_t * context)
{
    qreal ival = 0;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetAmptVal(context,&ival);
    if(iback)
    {
        remoteinterface::getrtsaremotehandle()->InterfaceObj->setMargin(4,ival);
    }
    return iback;
}
scpi_result_t RTSA_LIMIT5_EdgeValueQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMargin(4);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT6_EdgeValue(scpi_t * context)
{
    qreal ival = 0;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetAmptVal(context,&ival);
    if(iback)
    {
        remoteinterface::getrtsaremotehandle()->InterfaceObj->setMargin(5,ival);
    }
    return iback;
}
scpi_result_t RTSA_LIMIT6_EdgeValueQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMargin(5);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_LIMIT_TestState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setLimitTestOn(value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT_TestStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsLimitTestOn();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_LIMIT_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setLimitType(-1,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getLimitType(-1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT1_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setLimitType(0,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT1_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getLimitType(0);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT2_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setLimitType(1,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT2_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getLimitType(1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT3_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setLimitType(2,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT3_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getLimitType(2);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT4_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setLimitType(3,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT4_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getLimitType(3);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT5_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setLimitType(4,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT5_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getLimitType(4);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT6_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setLimitType(5,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT6_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getLimitType(5);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_LIMIT_AllDelete(scpi_t *context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getrtsaremotehandle()->InterfaceObj->DeleteAllLimit();
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT_Delete(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getrtsaremotehandle()->InterfaceObj->DeleteLimit(-1);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT1_Delete(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getrtsaremotehandle()->InterfaceObj->DeleteLimit(0);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT2_Delete(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getrtsaremotehandle()->InterfaceObj->DeleteLimit(1);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT3_Delete(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getrtsaremotehandle()->InterfaceObj->DeleteLimit(2);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT4_Delete(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getrtsaremotehandle()->InterfaceObj->DeleteLimit(3);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT5_Delete(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getrtsaremotehandle()->InterfaceObj->DeleteLimit(4);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT6_Delete(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getrtsaremotehandle()->InterfaceObj->DeleteLimit(5);
    return SCPI_RES_OK;
}

scpi_result_t RTSA_LIMIT_Autolimit(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getrtsaremotehandle()->InterfaceObj->BuildLimitFromTrace();
    return SCPI_RES_OK;
}

scpi_result_t RTSA_LIMIT_PointCountQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getLimitDataNum(-1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT_DeletePoint(scpi_t * context)
{
    qint32 value;
    qint32 index;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &index, true))
    {
        return SCPI_RES_ERR;
    }
//    if(!SCPI_ParamInt(context, &value, true))
//    {
//        return SCPI_RES_ERR;
//    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->DeleteLimitRow(index - 1);
    return SCPI_RES_OK;
}

scpi_result_t RTSA_LIMIT_PointFreqData(scpi_t * context)
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
    scpi_result_t iback = GetDoubleFreqVal(context,&freq);
    if(iback)
      {
        remoteinterface::getrtsaremotehandle()->InterfaceObj->setLimitCurPointFreq(freq,point - 1,limit - 1);
      }
    return iback;
}
scpi_result_t RTSA_LIMIT_PointFreqDataQ(scpi_t * context)
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

    freq = remoteinterface::getrtsaremotehandle()->InterfaceObj->getLimitCurPointFreq(point - 1,limit - 1);
    if(!SCPI_ResultDouble(context, freq))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_LIMIT_PointAmptData(scpi_t * context)
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
        remoteinterface::getrtsaremotehandle()->InterfaceObj->setLimitCurPointAmpt(ampt,point - 1,limit - 1);
      }
    return iback;
}
scpi_result_t RTSA_LIMIT_PointAmptDataQ(scpi_t * context)
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
    ampt = remoteinterface::getrtsaremotehandle()->InterfaceObj->getLimitCurPointAmpt(point - 1,limit - 1);
    if(!SCPI_ResultDouble(context, ampt))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}


scpi_result_t RTSA_LIMIT_LimitInsert(scpi_t * context)
{
    qint32 limit;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
//    if(!SCPI_ParamInt(context, &limit, true))
//    {
//        return SCPI_RES_ERR;
//    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->InsertLimitRow();
    return SCPI_RES_OK;
}


scpi_result_t RTSA_LIMIT_PointData(scpi_t * context)
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
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setLimitCurPointFreq(freq,point - 1,limit - 1);
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setLimitCurPointAmpt(ampt,point - 1,limit - 1);
    return SCPI_RES_OK;
}



