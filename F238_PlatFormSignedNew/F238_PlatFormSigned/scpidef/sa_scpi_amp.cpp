#include "sa_scpi_amp.h"

#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;

scpi_result_t GetAmptVal(scpi_t *context, qreal *val);
qreal wattsToDbmCalculatorFunc(qreal _watts);
qreal voltToDbmCalculatorFunc(qreal _volt);

scpi_result_t SA_AMPLITUDE_AutoScale(scpi_t *context)
{
    Q_UNUSED(context)
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    remoteinterface::getsaremotehandle()->pcontrolInterface->setAutoScale();
    return SCPI_RES_OK;
}

scpi_result_t SA_AMPLITUDE_Reflevel(scpi_t *context)
{
    qreal ival = 0;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetAmptVal(context,&ival);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setRefLevel(ival);
    }
    return iback;
}

scpi_result_t SA_AMPLITUDE_ScaleValue(scpi_t *context)
{
    qreal Value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamDouble(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setScaleDiv(Value);
    return SCPI_RES_OK;
}

scpi_result_t SA_AMPLITUDE_AutoAtten(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setAttenStatus(value);;
    return SCPI_RES_OK;
}

scpi_result_t SA_AMPLITUDE_AttenValue(scpi_t *context)
{
    qreal Value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamDouble(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setAttenValue(Value);
    return SCPI_RES_OK;
}

scpi_result_t SA_AMPLITUDE_Preamp(scpi_t *context)
{
    qint32 Value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setPreampStatus(Value);
    return SCPI_RES_OK;
}

scpi_result_t SA_AMPLITUDE_RLevelOffset(scpi_t *context)
{
    qreal Value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamDouble(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setRefOffset(Value);
    return SCPI_RES_OK;
}

scpi_result_t SA_AMPLITUDE_ScaleUnit(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setAmpUnit(value);
    return SCPI_RES_OK;
}

scpi_result_t SA_AMPLITUDE_ReflevelQ(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getRefLevel();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_AMPLITUDE_ScaleValueQ(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getScaleDiv();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_AMPLITUDE_AutoAttenQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getAttenStatus();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_AMPLITUDE_AttenValueQ(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getAttenValue();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_AMPLITUDE_PreampQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getPreampStatus();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_AMPLITUDE_RLevelOffsetQ(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getRefOffset();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}


scpi_result_t SA_AMPLITUDE_ScaleUnitQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getAmpUnit();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

/*
scpi_result_t SA_AMPLITUDE_ScaleUnitQ(scpi_t *context)
{
    qint32 value;
    char* strValue;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getAmpUnit();
    switch (value)
    {
    case SA_DBM:
        strValue = "DBM";
        break;
    case SA_DBV:
        strValue = "DBV";
        break;
    case SA_DBMV:
        strValue = "DBMV";
        break;
    case SA_DBUV:
        strValue = "DBUV";
        break;
    case SA_VOLT:
        strValue = "VOLT";
        break;
    case SA_WATTS:
        strValue = "WATTS";
        break;
    }
    if(!SCPI_ResultString(context, strValue))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
*/

/**
 * @brief for all freq param using
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-02-13}
*/

scpi_result_t GetAmptVal(scpi_t *context,qreal *val)
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
      qint32 iIndex = plf_compre_amptunit(mstr.mid(0,mstr.indexOf('\r')));
      if(iIndex)
      {
          switch (iIndex)
          {
          case 1://dBV
              value -= -13;
              break;
          case 2://dBmV
              value -= 47;
              break;
          case 3://dBuV
              value -= 107;
              break;
          case 4://V
              value *= 1000000.;
              value = voltToDbmCalculatorFunc(value);
              break;
          case 5://mV
              value *= 1000.;
              value = voltToDbmCalculatorFunc(value);
              break;
          case 6://uV
              value = voltToDbmCalculatorFunc(value);
              break;
          case 7://W
              value = wattsToDbmCalculatorFunc(value);
              break;
          case 8://mW
              value /= 1000.;
              value = wattsToDbmCalculatorFunc(value);
              break;
          case 9://uW
              value /= 1000000.;
              value = wattsToDbmCalculatorFunc(value);
              break;
          case 10://nw
              value /= 1000000000.;
              value = wattsToDbmCalculatorFunc(value);
              break;
          case 11://pW
              value /= 1000000000000.;
              value = wattsToDbmCalculatorFunc(value);
              break;
          case 12://fW
              value /= 1000000000000000.;
              value = wattsToDbmCalculatorFunc(value);
              break;
          case 13://aW
              value /= 1000000000000000000.;
              value = wattsToDbmCalculatorFunc(value);
              break;
          }
      }
  }
  *val = value;
  return SCPI_RES_OK;
}
qreal wattsToDbmCalculatorFunc(qreal _watts)
{
    return   (10 * log10(_watts) + 30);
}

qreal voltToDbmCalculatorFunc(qreal _volt)
{
    qreal cal1 = 0.;
    qreal cal2 = 0.;
    qreal cal3 = 0.;
    qreal cal4 = 0.;

    cal1 = _volt * pow(10, -6);
    cal2 = pow(cal1 , 2) / 50.;//R = 50.;
    cal3 = 10 * log10(cal2);
    cal4 = cal3 + 30.;

    return cal4;

}
