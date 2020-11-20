#include "sa_scpi_bw.h"

#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;
/**
 * @brief for all freq param using
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-02-13}
*/

scpi_result_t GetFreqVal(scpi_t *context,quint64 *val)
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
      qint32 iIndex = plf_compre_frequnit(mstr.mid(0,mstr.indexOf('\r')));
      if(iIndex)
        {
          value *= *(PLF_FREQ_UNIT_MULTIPLE + iIndex);
        }
    }
  *val = (quint64)value;
  return SCPI_RES_OK;
}

scpi_result_t SA_BANDWIDTH_AutoRbw(scpi_t *context)
{
    qint32 isAuto;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &isAuto, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setAutoRbwStatus(isAuto);
    return SCPI_RES_OK;
}

scpi_result_t SA_BANDWIDTH_Rbw(scpi_t *context)
{
    quint64 ival = 0;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    scpi_result_t iback = GetFreqVal(context,&ival);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setRbwValue(ival);
    }
    return iback;
}

scpi_result_t SA_BANDWIDTH_AutoVbw(scpi_t *context)
{
    qint32 isAuto;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &isAuto, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setAutoVbwStatus(isAuto);
    return SCPI_RES_OK;
}

scpi_result_t SA_BANDWIDTH_Vbw(scpi_t *context)
{
    quint64 ival = 0;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetFreqVal(context,&ival);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setVbwValue(ival);
    }
    return iback;
}

scpi_result_t SA_BANDWIDTH_Ratio(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setVbwtoRbw(value);
    return SCPI_RES_OK;
}

scpi_result_t SA_IFoutput(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setIFOutPut(value);
    return SCPI_RES_OK;
}

scpi_result_t SA_BANDWIDTH_AutoRbwQ(scpi_t *context)
{
    qint32 isAuto;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    isAuto = remoteinterface::getsaremotehandle()->pcontrolInterface->getRbwStatus();
    if(!SCPI_ResultInt(context, isAuto))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}

scpi_result_t SA_BANDWIDTH_RbwQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getRbwValue();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_BANDWIDTH_AutoVbwQ(scpi_t *context)
{
    qint32 isAuto;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    isAuto = remoteinterface::getsaremotehandle()->pcontrolInterface->getVbwStatus();
    if(!SCPI_ResultInt(context, isAuto))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_BANDWIDTH_VbwQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getVbwValue();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_BANDWIDTH_RatioQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getVbwtoRbw();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_IFoutputQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getIFOutPut();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
