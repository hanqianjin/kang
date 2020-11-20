#include "rtsa_scpi_amp.h"
#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;

extern scpi_result_t GetAmptVal(scpi_t *context, qreal *val);
extern qreal wattsToDbmCalculatorFunc(qreal _watts);
extern qreal voltToDbmCalculatorFunc(qreal _volt);

scpi_result_t RTSA_AMPLITUDE_AutoScale(scpi_t *context)
{
    Q_UNUSED(context)
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    remoteinterface::getrtsaremotehandle()->InterfaceObj->setAutoScale();
    return SCPI_RES_OK;
}

scpi_result_t RTSA_AMPLITUDE_Reflevel(scpi_t *context)
{
    qreal ival = 0;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetAmptVal(context,&ival);
    if(iback)
    {
        remoteinterface::getrtsaremotehandle()->InterfaceObj->setRefLevel(ival);
    }
    return iback;
}

scpi_result_t RTSA_AMPLITUDE_ScaleValue(scpi_t *context)
{
    qreal Value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamDouble(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setScaleDiv(Value);
    return SCPI_RES_OK;
}

scpi_result_t RTSA_AMPLITUDE_AutoAtten(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setAttenAuto(value);;
    return SCPI_RES_OK;
}

scpi_result_t RTSA_AMPLITUDE_AttenValue(scpi_t *context)
{
    qreal Value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamDouble(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setAttenVal(Value);
    return SCPI_RES_OK;
}

scpi_result_t RTSA_AMPLITUDE_Preamp(scpi_t *context)
{
    qint32 Value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setPreAmpOn(Value);
    return SCPI_RES_OK;
}

scpi_result_t RTSA_AMPLITUDE_RLevelOffset(scpi_t *context)
{
    qreal Value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamDouble(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setRefOffset(Value);
    return SCPI_RES_OK;
}

scpi_result_t RTSA_AMPLITUDE_ScaleUnit(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setAmptUnit(value);
    return SCPI_RES_OK;
}

scpi_result_t RTSA_AMPLITUDE_ReflevelQ(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getRefLevel();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_AMPLITUDE_ScaleValueQ(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getScaleDiv();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_AMPLITUDE_AutoAttenQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsAttenAuto();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_AMPLITUDE_AttenValueQ(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getAttenVal();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_AMPLITUDE_PreampQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsPreAmpOn();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_AMPLITUDE_RLevelOffsetQ(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getRefOffset();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}


scpi_result_t RTSA_AMPLITUDE_ScaleUnitQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getAmptUint();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
