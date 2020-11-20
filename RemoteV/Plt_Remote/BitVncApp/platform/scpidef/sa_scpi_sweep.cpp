#include "sa_scpi_sweep.h"
#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;

scpi_result_t GetTimeVal(scpi_t *context, qreal *val)
{
  qreal value = 0.0;
  const char* pstr;
  size_t ilen = 0;

  if (Mode_local == g_systemStatus.mode)
    {
      return SCPI_RES_ERR;
    }
  if (!SCPI_ParamDouble(context, &value, true))
    {
      return SCPI_RES_ERR;
    }
  //parse freq unit
  if(SCPI_ParamString(context, &pstr,&ilen,false))
    {
      QString mstr = QString(QLatin1String(pstr));
      qint32 iIndex = plt_compre_timeunit(mstr.mid(0,mstr.indexOf('\r')));
      if(iIndex)
        {
          value *= *(PLF_TIME_UNIT_MULTIPLE + iIndex);
        }
    }
  *val = value;
  return SCPI_RES_OK;
}

scpi_result_t SA_SWEEP_AutoTime(scpi_t *context)
{
    qint32 isAuto;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;
    if(!SCPI_ParamInt(context, &isAuto, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setAutoSweepTimeStatus(isAuto);
    return SCPI_RES_OK;
}

scpi_result_t SA_SWEEP_Time(scpi_t *context)
{
    qreal ival = 0;
    scpi_result_t iback = GetTimeVal(context,&ival);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setSweepTime(ival);
    }
    return iback;
}

scpi_result_t SA_SWEEP_Type(scpi_t *context)
{
    qint32 Value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;
    if(!SCPI_ParamInt(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setSweepType(Value);
    return SCPI_RES_OK;
}

scpi_result_t SA_SWEEP_AutoTimeQ(scpi_t *context)
{
    qint32 isAuto;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;

    isAuto = remoteinterface::getsaremotehandle()->pcontrolInterface->getAutoSweepTimeStatus();
    if(!SCPI_ResultInt(context, isAuto))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}

scpi_result_t SA_SWEEP_TimeQ(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getSweepTime();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_SWEEP_TypeQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getSweepType();
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
