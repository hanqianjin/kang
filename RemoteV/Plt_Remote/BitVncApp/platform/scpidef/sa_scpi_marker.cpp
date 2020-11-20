#include "sa_scpi_marker.h"

#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;
scpi_result_t GetFreqVal(scpi_t *context,qreal *val)
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
  *val = value;
  return SCPI_RES_OK;
}
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



scpi_result_t SA_MARKER_Select(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerSelect(value - 1);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER_SelectQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerSelect();
    if(!SCPI_ResultInt(context, value + 1))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_MARKER_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerViewStatus(value);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerViewStatus();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER1_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerViewStatus(value,0);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER1_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerViewStatus(0);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER2_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerViewStatus(value,1);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER2_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerViewStatus(1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER3_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerViewStatus(value,2);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER3_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerViewStatus(2);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER4_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerViewStatus(value,3);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER4_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerViewStatus(3);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER5_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerViewStatus(value,4);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER5_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerViewStatus(4);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER6_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerViewStatus(value,5);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER6_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerViewStatus(5);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_MARKER_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerType(value);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerType();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER1_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerType(value,0);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER1_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerType(0);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER2_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerType(value,1);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER2_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerType(1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER3_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerType(value,2);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER3_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerType(2);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER4_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerType(value,3);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER4_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerType(3);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER5_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerType(value,4);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER5_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerType(4);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER6_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerType(value,5);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER6_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerType(5);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_MARKER_ToCenter(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerToCF();
    return SCPI_RES_OK;
}

scpi_result_t SA_MARKER_ToStart(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerToStart();
    return SCPI_RES_OK;
}

scpi_result_t SA_MARKER_ToStop(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerToStop();
    return SCPI_RES_OK;
}

scpi_result_t SA_MARKER_X(scpi_t * context)
{
    qreal ival = 0;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerType();
    qint32 span = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpan();
    scpi_result_t iback;
    if(span)
    {
        iback = GetFreqVal(context,&ival);
        if(iback)
        {
            if(!mkrType)
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerRefFreq(ival);
            }else
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerDeltaFreq(ival);
            }
        }
    }else
    {
        iback = GetTimeVal(context,&ival);
        if(iback)
        {
            if(!mkrType)
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerRefTime(ival);
            }else
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerDeltaTime(ival);
            }
        }
    }
    return iback;
}
scpi_result_t SA_MARKER_XQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerType();
    qint32 span = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpan();
    if(span)
    {
            if(!mkrType)
            {
                value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerRefFreq();
            }else
            {
                value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerDeltaFreq();
            }
    }else
    {
        if(!mkrType)
        {
            value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerRefTime();
        }else
        {
            value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerRefTime();
        }
    }
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER1_X(scpi_t * context)
{
    qreal ival = 0;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerType(0);
    qint32 span = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpan();
    scpi_result_t iback;
    if(span)
    {
        iback = GetFreqVal(context,&ival);
        if(iback)
        {
            if(!mkrType)
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerRefFreq(ival,0);
            }else
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerDeltaFreq(ival,0);
            }
        }
    }else
    {
        iback = GetTimeVal(context,&ival);
        if(iback)
        {
            if(!mkrType)
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerRefTime(ival,0);
            }else
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerDeltaTime(ival,0);
            }
        }
    }
    return iback;
}
scpi_result_t SA_MARKER1_XQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerType(0);
    qint32 span = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpan();
    if(span)
    {
            if(!mkrType)
            {
                value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerRefFreq(0);
            }else
            {
                value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerDeltaFreq(0);
            }
    }else
    {
        if(!mkrType)
        {
            value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerRefTime(0);
        }else
        {
            value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerRefTime(0);
        }
    }
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER2_X(scpi_t * context)
{
    qreal ival = 0;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerType(1);
    qint32 span = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpan();
    scpi_result_t iback;
    if(span)
    {
        iback = GetFreqVal(context,&ival);
        if(iback)
        {
            if(!mkrType)
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerRefFreq(ival,1);
            }else
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerDeltaFreq(ival,1);
            }
        }
    }else
    {
        iback = GetTimeVal(context,&ival);
        if(iback)
        {
            if(!mkrType)
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerRefTime(ival,1);
            }else
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerDeltaTime(ival,1);
            }
        }
    }
    return iback;
}
scpi_result_t SA_MARKER2_XQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerType(1);
    qint32 span = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpan();
    if(span)
    {
            if(!mkrType)
            {
                value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerRefFreq(1);
            }else
            {
                value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerDeltaFreq(1);
            }
    }else
    {
        if(!mkrType)
        {
            value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerRefTime(1);
        }else
        {
            value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerRefTime(1);
        }
    }
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER3_X(scpi_t * context)
{
    qreal ival = 0;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerType(2);
    qint32 span = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpan();
    scpi_result_t iback;
    if(span)
    {
        iback = GetFreqVal(context,&ival);
        if(iback)
        {
            if(!mkrType)
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerRefFreq(ival,2);
            }else
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerDeltaFreq(ival,2);
            }
        }
    }else
    {
        iback = GetTimeVal(context,&ival);
        if(iback)
        {
            if(!mkrType)
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerRefTime(ival,2);
            }else
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerDeltaTime(ival,2);
            }
        }
    }
    return iback;
}
scpi_result_t SA_MARKER3_XQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerType(2);
    qint32 span = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpan();
    if(span)
    {
            if(!mkrType)
            {
                value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerRefFreq(2);
            }else
            {
                value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerDeltaFreq(2);
            }
    }else
    {
        if(!mkrType)
        {
            value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerRefTime(2);
        }else
        {
            value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerRefTime(2);
        }
    }
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER4_X(scpi_t * context)
{
    qreal ival = 0;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerType(3);
    qint32 span = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpan();
    scpi_result_t iback;
    if(span)
    {
        iback = GetFreqVal(context,&ival);
        if(iback)
        {
            if(!mkrType)
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerRefFreq(ival,3);
            }else
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerDeltaFreq(ival,3);
            }
        }
    }else
    {
        iback = GetTimeVal(context,&ival);
        if(iback)
        {
            if(!mkrType)
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerRefTime(ival,3);
            }else
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerDeltaTime(ival,3);
            }
        }
    }
    return iback;
}
scpi_result_t SA_MARKER4_XQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerType(0);
    qint32 span = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpan();
    if(span)
    {
            if(!mkrType)
            {
                value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerRefFreq(0);
            }else
            {
                value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerDeltaFreq(3);
            }
    }else
    {
        if(!mkrType)
        {
            value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerRefTime(3);
        }else
        {
            value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerRefTime(3);
        }
    }
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER5_X(scpi_t * context)
{
    qreal ival = 0;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerType(4);
    qint32 span = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpan();
    scpi_result_t iback;
    if(span)
    {
        iback = GetFreqVal(context,&ival);
        if(iback)
        {
            if(!mkrType)
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerRefFreq(ival,4);
            }else
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerDeltaFreq(ival,4);
            }
        }
    }else
    {
        iback = GetTimeVal(context,&ival);
        if(iback)
        {
            if(!mkrType)
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerRefTime(ival,4);
            }else
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerDeltaTime(ival,4);
            }
        }
    }
    return iback;
}
scpi_result_t SA_MARKER5_XQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerType(4);
    qint32 span = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpan();
    if(span)
    {
            if(!mkrType)
            {
                value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerRefFreq(4);
            }else
            {
                value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerDeltaFreq(4);
            }
    }else
    {
        if(!mkrType)
        {
            value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerRefTime(4);
        }else
        {
            value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerRefTime(4);
        }
    }
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER6_X(scpi_t * context)
{
    qreal ival = 0;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerType(5);
    qint32 span = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpan();
    scpi_result_t iback;
    if(span)
    {
        iback = GetFreqVal(context,&ival);
        if(iback)
        {
            if(!mkrType)
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerRefFreq(ival,5);
            }else
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerDeltaFreq(ival,5);
            }
        }
    }else
    {
        iback = GetTimeVal(context,&ival);
        if(iback)
        {
            if(!mkrType)
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerRefTime(ival,5);
            }else
            {
                remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerDeltaTime(ival,5);
            }
        }
    }
    return iback;
}
scpi_result_t SA_MARKER6_XQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerType(5);
    qint32 span = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpan();
    if(span)
    {
            if(!mkrType)
            {
                value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerRefFreq(5);
            }else
            {
                value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerDeltaFreq(5);
            }
    }else
    {
        if(!mkrType)
        {
            value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerRefTime(5);
        }else
        {
            value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerRefTime(5);
        }
    }
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_MARKER_FreqCount(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerFreqCountStatus(value);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER_FreqCountQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerFreqCountStatus();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER1_FreqCount(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerFreqCountStatus(value,0);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER1_FreqCountQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerFreqCountStatus(0);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER2_FreqCount(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerFreqCountStatus(value,1);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER2_FreqCountQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerFreqCountStatus(1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER3_FreqCount(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerFreqCountStatus(value,2);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER3_FreqCountQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerFreqCountStatus(2);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER4_FreqCount(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerFreqCountStatus(value,3);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER4_FreqCountQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerFreqCountStatus(3);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER5_FreqCount(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerFreqCountStatus(value,4);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER5_FreqCountQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerFreqCountStatus(4);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER6_FreqCount(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerFreqCountStatus(value,5);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER6_FreqCountQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerFreqCountStatus(5);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_MARKER_NoiseMarker(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerNoiseStatus(value);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER_NoiseMarkerQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerNoiseStatus();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER1_NoiseMarker(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerNoiseStatus(value,0);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER1_NoiseMarkerQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerNoiseStatus(0);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER2_NoiseMarker(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerNoiseStatus(value,1);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER2_NoiseMarkerQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerNoiseStatus(1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER3_NoiseMarker(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerNoiseStatus(value,2);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER3_NoiseMarkerQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerNoiseStatus(2);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER4_NoiseMarker(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerNoiseStatus(value,3);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER4_NoiseMarkerQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerNoiseStatus(3);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER5_NoiseMarker(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerNoiseStatus(value,4);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER5_NoiseMarkerQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerNoiseStatus(4);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER6_NoiseMarker(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMarkerNoiseStatus(value,5);
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER6_NoiseMarkerQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getMarkerNoiseStatus(5);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_MARKER_PeakMax(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getsaremotehandle()->pcontrolInterface->setPeak();
    return SCPI_RES_OK;
}
scpi_result_t SA_MARKER_PeakMin(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMinSearch();
    return SCPI_RES_OK;
}

scpi_result_t SA_MARKER_PeakMaxNext(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getsaremotehandle()->pcontrolInterface->setNextPeak();
    return SCPI_RES_OK;
}

scpi_result_t SA_MARKER_PeakMaxLeft(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getsaremotehandle()->pcontrolInterface->setPeakLeftSearch();
    return SCPI_RES_OK;
}

scpi_result_t SA_MARKER_PeakMaxRight(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getsaremotehandle()->pcontrolInterface->setPeakRightSearch();
    return SCPI_RES_OK;
}

scpi_result_t SA_MARKER_PeakTrack(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setPeakTrackStatus(value);
    return SCPI_RES_OK;
}

scpi_result_t SA_MARKER_PeakTrackQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getPeakTrackStatus();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_MARKER_AllClear(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getsaremotehandle()->SetAllMkrOff();
    return SCPI_RES_OK;
}
