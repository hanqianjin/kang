#include "rtsa_scpi_sweep.h"
#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;
extern scpi_result_t GetTimeVal(scpi_t *context,qreal *val);

scpi_result_t RTSA_SWEEP_Type(scpi_t *context)
{
    qint32 Value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;
    if(!SCPI_ParamInt(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    Value = !Value;
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setSingleSweep(Value);
    return SCPI_RES_OK;
}

scpi_result_t RTSA_SWEEP_Once(scpi_t *context)
{
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setSingleSweep(1);
    return SCPI_RES_OK;
}

scpi_result_t RTSA_SWEEP_Acqtime_Auto(scpi_t * context)
{
    qint32 Value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;
    if(!SCPI_ParamInt(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setAcqTimeAuto(Value);
    return SCPI_RES_OK;
}

scpi_result_t RTSA_SWEEP_Acqtime(scpi_t * context)
{
    qreal Value = 0.0;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;
    if(!SCPI_ParamDouble(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setAcqTime(Value);
    return SCPI_RES_OK;
}



scpi_result_t RTSA_SWEEP_TypeQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsSingleSweep();
    value = !value;
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_SWEEP_Acqtime_AutoQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsAcqTimeAuto();
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_SWEEP_AcqtimeQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getAcqTime();
    if(!SCPI_ResultDouble(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
