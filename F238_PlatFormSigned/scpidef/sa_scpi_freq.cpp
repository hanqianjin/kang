#include "sa_scpi_freq.h"
#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern scpi_t scpi_context;
extern SYSTEM_STATUS g_systemStatus;

static scpi_result_t GetFreqVal(scpi_t *context, quint64 *val);
scpi_result_t SA_FREQUENCY_Center_Freq(scpi_t *context)
{
  quint64 ival = 0;
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
  scpi_result_t iback = GetFreqVal(context,&ival);
  if(iback)
    {
      remoteinterface::getsaremotehandle()->pcontrolInterface->setCFFreq(ival);
    }
  return iback;
}

scpi_result_t SA_FREQUENCY_Step_CenterFreq_Auto(scpi_t * context)
{
  scpi_bool_t value;

  if (g_systemStatus.mode==Mode_local)
    return SCPI_RES_OK;

  if (!SCPI_ParamBool(context, &value, true))
    return SCPI_RES_ERR;

  return SCPI_RES_OK;//(scpi_result_t)ScpiDisplay_Bar::instance()->setConnectOnOff(value);
}

scpi_result_t SA_FREQUENCY_CenterFreq_Step(scpi_t * context)
{
  const char *param;
  size_t strcLen;
  int32_t value;

  if (g_systemStatus.mode==Mode_local)
    return SCPI_RES_OK;

  if (!SCPI_ParamString(context, &param, &strcLen, true))
    return SCPI_RES_ERR;

  if(matchPattern("UP",2,param,strcLen))
    value = 0;
  else if(matchPattern("DOWn",4,param,strcLen))
    value = 1;

  return SCPI_RES_OK;//(scpi_result_t)ScpiDisplay_Bar::instance()->setConnectOnOff(value);
}

scpi_result_t SA_FREQUENCY_Freq_Span(scpi_t * context)
{
  quint64 ival = 0;
  scpi_result_t iback = GetFreqVal(context,&ival);
  if(iback)
    {
      remoteinterface::getsaremotehandle()->pcontrolInterface->setSpan(ival,1);
    }
  return iback;
}

scpi_result_t SA_FREQUENCY_Freq_FullSpan(scpi_t * context)
{
  return SCPI_RES_OK;//(scpi_result_t)(setFullSpan);
}

scpi_result_t SA_FREQUENCY_Freq_ZeroSpan(scpi_t * context)
{
  return SCPI_RES_OK;//(scpi_result_t)(setZeroSpan);
}

scpi_result_t SA_FREQUENCY_Freq_PreviousSpan(scpi_t * context)
{
  return SCPI_RES_OK;//(scpi_result_t)(setPreviouseSpan);
}

scpi_result_t SA_FREQUENCY_Center_FreqQ(scpi_t * context)
{
  quint32 centerFreq;

  if (g_systemStatus.mode==Mode_local)
    return SCPI_RES_OK;

  if(1)//ScpiDisplay_Bar::instance()->getCenterFreq(&centerFreq))
    {
      SCPI_ResultInt(context, (int32_t)centerFreq);
    }
  else
    return SCPI_RES_ERR;

  return SCPI_RES_OK;
}

scpi_result_t SA_FREQUENCY_Start_FreqQ(scpi_t * context)
{
  quint32 startFreq;

  if (g_systemStatus.mode==Mode_local)
    return SCPI_RES_OK;

  if(1)//ScpiDisplay_Bar::instance()->getStartFreq(&startFreq))
    {
      SCPI_ResultInt(context, (int32_t)startFreq);
    }
  else
    return SCPI_RES_ERR;

  return SCPI_RES_OK;
}

scpi_result_t SA_FREQUENCY_Stop_FreqQ(scpi_t * context)
{
  quint32 stopFreq;

  if (g_systemStatus.mode==Mode_local)
    return SCPI_RES_OK;

  if(1)//ScpiDisplay_Bar::instance()->getStopFreq(&stopFreq))
    {
      SCPI_ResultInt(context, (int32_t)stopFreq);
    }
  else
    return SCPI_RES_ERR;

  return SCPI_RES_OK;
}

scpi_result_t SA_FREQUENCY_Step_FreqQ(scpi_t * context)
{
  quint32 stepFreq;

  if (g_systemStatus.mode==Mode_local)
    return SCPI_RES_OK;

  if(1)//ScpiDisplay_Bar::instance()->getStepFreq(&stepFreq))
    {
      SCPI_ResultInt(context, (int32_t)stepFreq);
    }
  else
    return SCPI_RES_ERR;

  return SCPI_RES_OK;
}

scpi_result_t SA_FREQUENCY_Step_CenterFreqQ(scpi_t * context)
{
  quint32 stepCenterFreq;

  if (g_systemStatus.mode==Mode_local)
    return SCPI_RES_OK;

  if(1)//ScpiDisplay_Bar::instance()->getStepCenterFreq(&stepCenterFreq))
    {
      SCPI_ResultInt(context, (int32_t)stepCenterFreq);
    }
  else
    return SCPI_RES_ERR;

  return SCPI_RES_OK;
}
scpi_result_t SA_FREQUENCY_Step_CenterFreq_AutoQ(scpi_t * context)
{
  scpi_bool_t stepCenterFreqAuto;

  if (g_systemStatus.mode==Mode_local)
    return SCPI_RES_OK;

  if(1)//ScpiDisplay_Bar::instance()->getStepCenterFreqAuto(&stepCenterFreqAuto))
    {
      SCPI_ResultBool(context, stepCenterFreqAuto);
    }
  else
    return SCPI_RES_ERR;

  return SCPI_RES_OK;
}

scpi_result_t SA_FREQUENCY_Freq_SpanQ(scpi_t * context)
{
  quint32 spanFreq;

  if (g_systemStatus.mode==Mode_local)
    return SCPI_RES_OK;

  if(1)//ScpiDisplay_Bar::instance()->getSpanFreq(&spanFreq))
    {
      SCPI_ResultInt(context, (int32_t)spanFreq);
    }
  else
    return SCPI_RES_ERR;

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
static scpi_result_t GetFreqVal(scpi_t *context,quint64 *val)
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
