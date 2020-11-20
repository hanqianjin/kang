#include "rtsa_scpi_marker.h"

#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;
scpi_result_t GetFreqVal(scpi_t *context,qreal *val);
scpi_result_t GetTimeVal(scpi_t *context, qreal *val);

//scpi_result_t GetFreqVal(scpi_t *context,qreal *val)
//{
//  qreal value = 0.0;
//  const char* pstr;
//  size_t ilen = 0;

//  if (Mode_local == g_systemStatus.mode)
//    {
//      return SCPI_RES_ERR;
//    }
//  if (!SCPI_ParamDouble(context, &value, true))
//    {
//      return SCPI_RES_ERR;
//    }
//  //parse freq unit
//  if(SCPI_ParamString(context, &pstr,&ilen,false))
//    {
//      QString mstr = QString(QLatin1String(pstr));
//      qint32 iIndex = plf_compre_frequnit(mstr.mid(0,mstr.indexOf('\r')));
//      if(iIndex)
//        {
//          value *= *(PLF_FREQ_UNIT_MULTIPLE + iIndex);
//        }
//    }
//  *val = value;
//  return SCPI_RES_OK;
//}
//scpi_result_t GetTimeVal(scpi_t *context, qreal *val)
//{
//  qreal value = 0.0;
//  const char* pstr;
//  size_t ilen = 0;

//  if (Mode_local == g_systemStatus.mode)
//    {
//      return SCPI_RES_ERR;
//    }
//  if (!SCPI_ParamDouble(context, &value, true))
//    {
//      return SCPI_RES_ERR;
//    }
//  //parse freq unit
//  if(SCPI_ParamString(context, &pstr,&ilen,false))
//    {
//      QString mstr = QString(QLatin1String(pstr));
//      qint32 iIndex = plt_compre_timeunit(mstr.mid(0,mstr.indexOf('\r')));
//      if(iIndex)
//        {
//          value *= *(PLF_TIME_UNIT_MULTIPLE + iIndex);
//        }
//    }
//  *val = value;
//  return SCPI_RES_OK;
//}



scpi_result_t RTSA_MARKER_Select(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setCurMarkerID(value - 1);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER_SelectQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getCurMarkerID();
    if(!SCPI_ResultInt(context, value + 1))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_MARKER_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setCurMarkerOn(value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->isCurMarkerOn();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER1_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerOn(0,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER1_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->isMarkerOn(0);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER2_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerOn(1,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER2_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->isMarkerOn(1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER3_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerOn(2,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER3_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->isMarkerOn(2);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER4_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerOn(3,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER4_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->isMarkerOn(3);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER5_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerOn(4,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER5_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->isMarkerOn(4);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER6_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerOn(5,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER6_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->isMarkerOn(5);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_MARKER_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setCurMarkerType(value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getCurMarkerType();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER1_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerType(0,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER1_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerType(0);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER2_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerType(1,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER2_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerType(1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER3_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerType(2,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER3_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerType(2);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER4_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerType(3,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER4_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerType(3);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER5_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerType(4,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER5_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerType(4);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER6_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerType(5,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER6_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerType(5);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_MARKER_ToCenter(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerToCenter();
    return SCPI_RES_OK;
}

scpi_result_t RTSA_MARKER_ToStart(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerToStart();
    return SCPI_RES_OK;
}

scpi_result_t RTSA_MARKER_ToStop(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerToStop();
    return SCPI_RES_OK;
}

scpi_result_t RTSA_MARKER_X(scpi_t * context)
{
    qreal ival = 0;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getrtsaremotehandle()->InterfaceObj->getCurMarkerType();
    scpi_result_t iback;
    iback = GetFreqVal(context,&ival);
    if(iback)
    {
        if(!mkrType)
        {
            remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerRefFreq(-1,ival);
        }else
        {
            remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerDeltaFreq(-1,ival);
        }
    }
    return iback;
}
scpi_result_t RTSA_MARKER_XQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getrtsaremotehandle()->InterfaceObj->getCurMarkerType();
    if(!mkrType)
    {
        value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerRefFreq(-1);
    }else
    {
        value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerDeltaFreq(-1);
    }
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER1_X(scpi_t * context)
{
    qreal ival = 0;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerType(0);
    scpi_result_t iback;
    iback = GetFreqVal(context,&ival);
    if(iback)
    {
        if(!mkrType)
        {
            remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerRefFreq(ival,0);
        }else
        {
            remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerDeltaFreq(ival,0);
        }
    }
    return iback;
}
scpi_result_t RTSA_MARKER1_XQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerType(0);
    if(!mkrType)
    {
        value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerRefFreq(0);
    }else
    {
        value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerDeltaFreq(0);
    }

    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER2_X(scpi_t * context)
{
    qreal ival = 0;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerType(1);
    scpi_result_t iback;
    iback = GetFreqVal(context,&ival);
    if(iback)
    {
        if(!mkrType)
        {
            remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerRefFreq(ival,1);
        }else
        {
            remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerDeltaFreq(ival,1);
        }
    }
    return iback;
}
scpi_result_t RTSA_MARKER2_XQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerType(1);
    if(!mkrType)
    {
        value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerRefFreq(1);
    }else
    {
        value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerDeltaFreq(1);
    }
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER3_X(scpi_t * context)
{
    qreal ival = 0;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerType(2);
    scpi_result_t iback;
    iback = GetFreqVal(context,&ival);
    if(iback)
    {
        if(!mkrType)
        {
            remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerRefFreq(ival,2);
        }else
        {
            remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerDeltaFreq(ival,2);
        }
    }
    return iback;
}
scpi_result_t RTSA_MARKER3_XQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerType(2);
    if(!mkrType)
    {
        value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerRefFreq(2);
    }else
    {
        value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerDeltaFreq(2);
    }
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER4_X(scpi_t * context)
{
    qreal ival = 0;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerType(3);
    scpi_result_t iback;
    iback = GetFreqVal(context,&ival);
    if(iback)
    {
        if(!mkrType)
        {
            remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerRefFreq(ival,3);
        }else
        {
            remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerDeltaFreq(ival,3);
        }
    }
    return iback;
}
scpi_result_t RTSA_MARKER4_XQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerType(3);
    if(!mkrType)
    {
        value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerRefFreq(3);
    }else
    {
        value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerDeltaFreq(3);
    }
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER5_X(scpi_t * context)
{
    qreal ival = 0;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerType(4);
    scpi_result_t iback;
    iback = GetFreqVal(context,&ival);
    if(iback)
    {
        if(!mkrType)
        {
            remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerRefFreq(ival,4);
        }else
        {
            remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerDeltaFreq(ival,4);
        }
    }
    return iback;
}
scpi_result_t RTSA_MARKER5_XQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerType(4);
    if(!mkrType)
    {
        value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerRefFreq(4);
    }else
    {
        value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerDeltaFreq(4);
    }
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER6_X(scpi_t * context)
{
    qreal ival = 0;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerType(5);
    scpi_result_t iback;
    iback = GetFreqVal(context,&ival);
    if(iback)
    {
        if(!mkrType)
        {
            remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerRefFreq(ival,5);
        }else
        {
            remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerDeltaFreq(ival,5);
        }
    }
    return iback;
}
scpi_result_t RTSA_MARKER6_XQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    qint32 mkrType = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerType(5);
    if(!mkrType)
    {
        value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerRefFreq(5);
    }else
    {
        value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getMarkerDeltaFreq(5);
    }
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_MARKER_NoiseMarker(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerNoiseOn(-1,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER_NoiseMarkerQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsMarkerNoiseOn(-1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER1_NoiseMarker(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerNoiseOn(0,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER1_NoiseMarkerQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsMarkerNoiseOn(0);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER2_NoiseMarker(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerNoiseOn(1,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER2_NoiseMarkerQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsMarkerNoiseOn(1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER3_NoiseMarker(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerNoiseOn(2,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER3_NoiseMarkerQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsMarkerNoiseOn(2);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER4_NoiseMarker(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerNoiseOn(3,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER4_NoiseMarkerQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsMarkerNoiseOn(3);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER5_NoiseMarker(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerNoiseOn(4,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER5_NoiseMarkerQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsMarkerNoiseOn(4);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER6_NoiseMarker(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerNoiseOn(5,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER6_NoiseMarkerQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsMarkerNoiseOn(5);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_MARKER_PeakMax(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerToPeak();
    return SCPI_RES_OK;
}
scpi_result_t RTSA_MARKER_PeakMin(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerToMin();
    return SCPI_RES_OK;
}

scpi_result_t RTSA_MARKER_PeakMaxNext(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerToNextPeak();
    return SCPI_RES_OK;
}

scpi_result_t RTSA_MARKER_PeakMaxLeft(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerToLeftPeak();
    return SCPI_RES_OK;
}

scpi_result_t RTSA_MARKER_PeakMaxRight(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setMarkerToRightPeak();
    return SCPI_RES_OK;
}

scpi_result_t RTSA_MARKER_PeakTrack(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setPeakTrackOn(value);
    return SCPI_RES_OK;
}

scpi_result_t RTSA_MARKER_PeakTrackQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->IsPeakTrackOn();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

//scpi_result_t RTSA_MARKER_AllClear(scpi_t * context)
//{
//    Q_UNUSED(context)
//    if(g_systemStatus.mode==Mode_local)
//      return SCPI_RES_ERR;
//    remoteinterface::getrtsaremotehandle()->InterfaceObj->();
//    return SCPI_RES_OK;
//}

