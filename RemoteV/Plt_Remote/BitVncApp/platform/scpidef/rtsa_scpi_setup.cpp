#include "rtsa_scpi_setup.h"


#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;

scpi_result_t RTSA_Density_PersistenceTimeInfinite(scpi_t * context)
{
        qint32 ival = 0;
        if(g_systemStatus.mode==Mode_local)
          return SCPI_RES_ERR;

        if(!SCPI_ParamInt(context, &ival, true))
        {
            return SCPI_RES_ERR;
        }
        remoteinterface::getrtsaremotehandle()->InterfaceObj->setPersistenceTimeInfinite(ival);

        return SCPI_RES_OK;
}

scpi_result_t RTSA_Density_PersistenceTime(scpi_t *context)
{
  qreal Value = 0.0;
  if (g_systemStatus.mode==Mode_local)
    return SCPI_RES_OK;
  if(!SCPI_ParamDouble(context, &Value, true))
  {
      return SCPI_RES_ERR;
  }
  remoteinterface::getrtsaremotehandle()->InterfaceObj->setPersistenceTime(Value);
  return SCPI_RES_OK;
}

scpi_result_t RTSA_Density_Highest(scpi_t *context)
{
    qint32 isAuto;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &isAuto, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setHighestDensity(isAuto);
    return SCPI_RES_OK;
}

scpi_result_t RTSA_Density_Lowest(scpi_t *context)
{
    qint32 isAuto;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &isAuto, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setLowestDensity(isAuto);
    return SCPI_RES_OK;
}

scpi_result_t RTSA_Density_Curve(scpi_t * context)
{
    qreal Value = 0.0;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;
    if(!SCPI_ParamDouble(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setCurve(Value);
    return SCPI_RES_OK;
}

scpi_result_t RTSA_Density_PersistenceTimeInfiniteQ(scpi_t * context)
{

    qint32 channelNum;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    channelNum = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsPersistenceTimeInfinite();
    if(!SCPI_ResultInt(context, channelNum))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_Density_PersistenceTimeQ(scpi_t * context)
{
    qreal centerFreq;

    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    centerFreq = remoteinterface::getrtsaremotehandle()->InterfaceObj->getPersistenceTime();
    if(!SCPI_ResultDouble(context, centerFreq))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_Density_HighestQ(scpi_t *context)
{
    qint32 isAuto;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    isAuto = remoteinterface::getrtsaremotehandle()->InterfaceObj->getHighestDensity();
    if(!SCPI_ResultInt(context, isAuto))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_Density_LowestQ(scpi_t *context)
{
    qint32 isAuto;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    isAuto = remoteinterface::getrtsaremotehandle()->InterfaceObj->getLowestDensity();
    if(!SCPI_ResultInt(context, isAuto))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_Density_CurveQ(scpi_t * context)
{
    qint32 isAuto;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;

    isAuto = remoteinterface::getrtsaremotehandle()->InterfaceObj->getCurve();
      if(!SCPI_ResultInt(context, isAuto))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_Density_Adjust(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setDensityLevelAjust();
    return SCPI_RES_OK;
}
