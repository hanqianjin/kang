#include "sa_scpi_sweep.h"
#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;
scpi_result_t GetAmptVal(scpi_t *context, qreal *val);

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

scpi_result_t SA_SWEEP_FixedMode(scpi_t * context)
{
    qint32 Value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;
    if(!SCPI_ParamInt(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setFixSweepMode(Value);
    return SCPI_RES_OK;
}
scpi_result_t SA_SWEEP_FixedModeQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getFixSweepMode();
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_SWEEP_DotAutoTime(scpi_t * context)
{
    qint32 Value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;
    if(!SCPI_ParamInt(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setAutoDotSweepTime(Value);
    return SCPI_RES_OK;
}
scpi_result_t SA_SWEEP_DotAutoTimeQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getAutoDotSweepTimeStatus();
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_SWEEP_DotTime(scpi_t * context)
{
    qreal ival = 0;
    scpi_result_t iback = GetTimeVal(context,&ival);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setDotSweepTime(ival);
    }
    return iback;
}
scpi_result_t SA_SWEEP_DotTimeQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getDotSweepTime();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_GATE_Source(scpi_t * context)
{
    qint32 Value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;
    if(!SCPI_ParamInt(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setDoorControlSource(Value);
    return SCPI_RES_OK;
}
scpi_result_t SA_GATE_SourceQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getDoorControlSource();
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_GATE_State(scpi_t * context)
{
    qint32 Value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;
    if(!SCPI_ParamInt(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setDoorControlSwitch(Value);
    return SCPI_RES_OK;
}
scpi_result_t SA_GATE_StateQ(scpi_t * context)
{
     qint32 value;
     if (g_systemStatus.mode==Mode_local)
       return SCPI_RES_OK;

     value = remoteinterface::getsaremotehandle()->pcontrolInterface->getDoorControlSwitch();
     if(!SCPI_ResultInt(context, value))
       {
         return SCPI_RES_ERR;
       }
     return SCPI_RES_OK;
}
scpi_result_t SA_GATE_Method(scpi_t * context)
{
    qint32 Value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;
    if(!SCPI_ParamInt(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setDoorControlSweepMode(Value);
    return SCPI_RES_OK;
}
scpi_result_t SA_GATE_MethodQ(scpi_t * context)
{
     qint32 value;
     if (g_systemStatus.mode==Mode_local)
       return SCPI_RES_OK;

     value = remoteinterface::getsaremotehandle()->pcontrolInterface->getDoorControlSweepMode();
     if(!SCPI_ResultInt(context, value))
       {
         return SCPI_RES_ERR;
       }
     return SCPI_RES_OK;
}
scpi_result_t SA_GATE_Control(scpi_t * context)
{
    qint32 Value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;
    if(!SCPI_ParamInt(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setLevleEdgeSelect(Value);
    return SCPI_RES_OK;
}
scpi_result_t SA_GATE_ControlQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLevleEdgeSelect();
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_GATE_Value(scpi_t * context)
{
    qint32 Value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;
    if(!SCPI_ParamInt(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setLevleEdgeMode(Value);
    return SCPI_RES_OK;
}
scpi_result_t SA_GATE_ValueQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getLevleEdgeMode();
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}

scpi_result_t SA_GATE_Delay(scpi_t * context)
{
    qreal ival = 0;
    scpi_result_t iback = GetTimeVal(context,&ival);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setEdgeTrigDely(ival);
    }
    return iback;
}
scpi_result_t SA_GATE_DelayQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getEdgeTrigDely();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_GATE_Length(scpi_t * context)
{
    qreal ival = 0;
    scpi_result_t iback = GetTimeVal(context,&ival);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setEdgeTrigDoorWidth(ival);
    }
    return iback;
}
scpi_result_t SA_GATE_LengthQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getEdgeTrigDoorWidth();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}


scpi_result_t SA_GATE_PreventState(scpi_t * context)
{
    qint32 Value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;
    if(!SCPI_ParamInt(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setEdgeTrigPreventStatus(Value);
    return SCPI_RES_OK;
}
scpi_result_t SA_GATE_PreventStateQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getEdgeTrigPreventStatus();
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}

scpi_result_t SA_GATE_PreventTime(scpi_t * context)
{
    qreal ival = 0;
    scpi_result_t iback = GetTimeVal(context,&ival);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setEdgeTrigPreventTimes(ival);
    }
    return iback;
}
scpi_result_t SA_GATE_PreventTimeQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_OK;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getEdgeTrigPreventTimes();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_GATE_View(scpi_t * context)
{
    qint32 Value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;
    if(!SCPI_ParamInt(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setGateViewStatus(Value);
    return SCPI_RES_OK;
}
scpi_result_t SA_GATE_ViewQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getGateViewStatus();
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_GATE_ViewStart(scpi_t * context)
{
    qreal ival = 0;
    scpi_result_t iback = GetTimeVal(context,&ival);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setGateViewStartTime(ival);
    }
    return iback;
}
scpi_result_t SA_GATE_ViewStartQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_OK;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getGateViewStartTime();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_GATE_TriggerLevel(scpi_t *context)
{
    qreal ival = 0;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetAmptVal(context,&ival);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setRFBurstTrigLevel(ival);
    }
    return iback;
}
scpi_result_t SA_GATE_TriggerLevelQ(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getRFBurstTrigLevel();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_GATE_Period(scpi_t * context)
{
    qreal ival = 0;
    scpi_result_t iback = GetTimeVal(context,&ival);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setPeriodTrigPeriod(ival);
    }
    return iback;
}
scpi_result_t SA_GATE_PeriodQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_OK;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getPeriodTrigPeriod();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_GATE_SYNsrcdelay(scpi_t * context)
{
    qreal ival = 0;
    scpi_result_t iback = GetTimeVal(context,&ival);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setPeriodTrigSrcDelay(ival);
    }
    return iback;
}
scpi_result_t SA_GATE_SYNsrcdelayQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_OK;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getPeriodTrigSrcDelay();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_GATE_SrcPr(scpi_t * context)
{
    qint32 Value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;
    if(!SCPI_ParamInt(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setPeriodTrigPreventStatus(Value);
    return SCPI_RES_OK;
}
scpi_result_t SA_GATE_SrcPrQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getPeriodTrigPreventStatus();
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_GATE_SrcPrTime(scpi_t * context)
{
    qreal ival = 0;
    scpi_result_t iback = GetTimeVal(context,&ival);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setPeriodTrigPreventTimes(ival);
    }
    return iback;
}
scpi_result_t SA_GATE_SrcPrTimeQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_OK;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getPeriodTrigPreventTimes();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_GATE_SychSource(scpi_t * context)
{
    qint32 Value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;
    if(!SCPI_ParamInt(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setPeriodTrigSynchroSrc(Value);
    return SCPI_RES_OK;
}
scpi_result_t SA_GATE_SychSourceQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getPeriodTrigSynchroSrc();
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}




