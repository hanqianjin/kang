#include "sa_scpi_freq.h"
#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;

scpi_result_t GetFreqVal(scpi_t *context, quint64 *val);
scpi_result_t SA_FREQUENCY_Center_Freq(scpi_t *context)
{
  quint64 ival = 0;
  if(g_systemStatus.mode==Mode_local)
    return SCPI_RES_ERR;
  scpi_result_t iback = GetFreqVal(context,&ival);
  if(iback)
  {
      remoteinterface::getsaremotehandle()->pcontrolInterface->setCenterFreq(ival);
  }
  return iback;
}

scpi_result_t SA_FREQUENCY_Start_Freq(scpi_t * context)
{
  quint64 ival = 0;
  if(g_systemStatus.mode==Mode_local)
    return SCPI_RES_ERR;
  scpi_result_t iback = GetFreqVal(context,&ival);
  if(iback)
  {
      remoteinterface::getsaremotehandle()->pcontrolInterface->setStartFreq(ival);
  }
  return iback;
}

scpi_result_t SA_FREQUENCY_Stop_Freq(scpi_t * context)
{
  quint64 ival = 0;
  if(g_systemStatus.mode==Mode_local)
    return SCPI_RES_ERR;
  scpi_result_t iback = GetFreqVal(context,&ival);
  if(iback)
  {
      remoteinterface::getsaremotehandle()->pcontrolInterface->setStopFreq(ival);
  }
  return iback;
}

scpi_result_t SA_FREQUENCY_Step_Freq(scpi_t * context)
{
  quint64 ival = 0;
  if(g_systemStatus.mode==Mode_local)
    return SCPI_RES_ERR;
  scpi_result_t iback = GetFreqVal(context,&ival);
  if(iback)
    {
      remoteinterface::getsaremotehandle()->pcontrolInterface->setCFFreq(ival);
    }
  return iback;
}

scpi_result_t SA_FREQUENCY_Freq_Span(scpi_t * context)
{
  quint64 ival = 0;
  if(g_systemStatus.mode==Mode_local)
    return SCPI_RES_ERR;
  scpi_result_t iback = GetFreqVal(context,&ival);
  if(iback)
    {
      remoteinterface::getsaremotehandle()->pcontrolInterface->setSpan(ival);
    }
  return iback;
}

scpi_result_t SA_FREQUENCY_Freq_FullSpan(scpi_t * context)
{
  Q_UNUSED(context)
  if(g_systemStatus.mode==Mode_local)
    return SCPI_RES_ERR;
  remoteinterface::getsaremotehandle()->pcontrolInterface->setFullSpan();
  return SCPI_RES_OK;
}

scpi_result_t SA_FREQUENCY_Freq_ZeroSpan(scpi_t * context)
{
  Q_UNUSED(context)
  if(g_systemStatus.mode==Mode_local)
    return SCPI_RES_ERR;
  remoteinterface::getsaremotehandle()->pcontrolInterface->setZeroSpan();
  return SCPI_RES_OK;
}

scpi_result_t SA_FREQUENCY_Freq_PreviousSpan(scpi_t * context)
{  
  Q_UNUSED(context)
  if(g_systemStatus.mode==Mode_local)
    return SCPI_RES_ERR;
  remoteinterface::getsaremotehandle()->pcontrolInterface->setLastSpan();
  return SCPI_RES_OK;
}

scpi_result_t SA_FREQUENCY_Offset_Freq(scpi_t *context)
{
  quint64 ival = 0;
  if(g_systemStatus.mode==Mode_local)
    return SCPI_RES_ERR;
  scpi_result_t iback = GetFreqVal(context,&ival);
  if(iback)
    {
      remoteinterface::getsaremotehandle()->pcontrolInterface->setFreqOffset(ival);
    }
  return iback;

}

scpi_result_t SA_FREQUENCY_Center_FreqQ(scpi_t * context)
{
  qreal centerFreq;

  if (g_systemStatus.mode==Mode_local)
    return SCPI_RES_ERR;

  centerFreq = remoteinterface::getsaremotehandle()->pcontrolInterface->getCenterFreq();
  if(!SCPI_ResultDouble(context, centerFreq))
    {
      return SCPI_RES_ERR;
    }
  return SCPI_RES_OK;
}

scpi_result_t SA_FREQUENCY_Start_FreqQ(scpi_t * context)
{
  qreal centerFreq;
  if (g_systemStatus.mode==Mode_local)
    return SCPI_RES_ERR;

  centerFreq = remoteinterface::getsaremotehandle()->pcontrolInterface->getStartFreq();
  if(!SCPI_ResultDouble(context, centerFreq))
  {
      return SCPI_RES_ERR;
  }
  return SCPI_RES_OK;
}

scpi_result_t SA_FREQUENCY_Stop_FreqQ(scpi_t * context)
{
  qreal centerFreq;
  if (g_systemStatus.mode==Mode_local)
    return SCPI_RES_ERR;

  centerFreq = remoteinterface::getsaremotehandle()->pcontrolInterface->getStopFreq();
  if(!SCPI_ResultDouble(context, centerFreq))
    {
      return SCPI_RES_ERR;
    }
  return SCPI_RES_OK;
}

scpi_result_t SA_FREQUENCY_Step_FreqQ(scpi_t * context)
{
  qreal centerFreq;
  if (g_systemStatus.mode==Mode_local)
    return SCPI_RES_ERR;

  centerFreq = remoteinterface::getsaremotehandle()->pcontrolInterface->getCFFreq();
  if(!SCPI_ResultDouble(context, centerFreq))
    {
      return SCPI_RES_ERR;
    }
  return SCPI_RES_OK;
}

scpi_result_t SA_FREQUENCY_Freq_SpanQ(scpi_t * context)
{
  qreal centerFreq;
  if (g_systemStatus.mode==Mode_local)
    return SCPI_RES_ERR;

  centerFreq = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpan();
  if(!SCPI_ResultDouble(context, centerFreq))
    {
      return SCPI_RES_ERR;
    }
  return SCPI_RES_OK;
}

scpi_result_t SA_FREQUENCY_Freq_OffsetQ(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getFreqOffset();
    if(!SCPI_ResultDouble(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
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


