#include "sa_scpi_trigger.h"

#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"
extern SYSTEM_STATUS g_systemStatus;
scpi_result_t GetAmptVal(scpi_t *context, qreal *val);
scpi_result_t GetTimeVal(scpi_t *context, qreal *val);

scpi_result_t SA_TRIGGER_Type(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTriggerMode(value);
    return SCPI_RES_OK;
}

scpi_result_t SA_TRIGGER_Level(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetAmptVal(context,&value);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setTriggerLevel(value);
    }
    return iback;
}
scpi_result_t SA_TRIGGER_ExteLevel(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetAmptVal(context,&value);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setTriggerLevel(value,1);
    }
    return iback;
}
scpi_result_t SA_TRIGGER_VedioLevel(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetAmptVal(context,&value);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setTriggerLevel(value,2);
    }
    return iback;
}
scpi_result_t SA_TRIGGER_RFLevel(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetAmptVal(context,&value);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setTriggerLevel(value,4);
    }
    return iback;
}
scpi_result_t SA_TRIGGER_SlopeStatus(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTriggerSlope(value);
    return SCPI_RES_OK;
}

scpi_result_t SA_TRIGGER_TypeQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTriggerMode();
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRIGGER_LevelQ(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTriggerLevel();
    if(!SCPI_ResultDouble(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRIGGER_ExteLevelQ(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTriggerLevel(1);
    if(!SCPI_ResultDouble(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRIGGER_VedioLevelQ(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTriggerLevel(2);
    if(!SCPI_ResultDouble(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRIGGER_RFLevelQ(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTriggerLevel(4);
    if(!SCPI_ResultDouble(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}

scpi_result_t SA_TRIGGER_SlopeState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTriggerSlope(value);
    return SCPI_RES_OK;
}
scpi_result_t SA_TRIGGER_ExteSlope(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTriggerSlope(value,1);
    return SCPI_RES_OK;
}
scpi_result_t SA_TRIGGER_VedioSlope(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTriggerSlope(value,2);
    return SCPI_RES_OK;
}
scpi_result_t SA_TRIGGER_RFSlope(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTriggerSlope(value,4);
    return SCPI_RES_OK;
}


scpi_result_t SA_TRIGGER_SlopeStateQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTriggerSlope();
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRIGGER_ExteSlopeQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTriggerSlope(1);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRIGGER_VedioSlopeQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTriggerSlope(2);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRIGGER_RFSlopeQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTriggerSlope(4);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}


scpi_result_t SA_TRIGGER_DelayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTriggerDelayStatus(value);
    return SCPI_RES_OK;
}
scpi_result_t SA_TRIGGER_ExteDelaySta(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTriggerDelayStatus(value,1);
    return SCPI_RES_OK;
}
scpi_result_t SA_TRIGGER_VedioDelaySta(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTriggerDelayStatus(value,2);
    return SCPI_RES_OK;
}
scpi_result_t SA_TRIGGER_PeriDelaySta(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTriggerDelayStatus(value,3);
    return SCPI_RES_OK;
}
scpi_result_t SA_TRIGGER_RFDelaySta(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setTriggerDelayStatus(value,4);
    return SCPI_RES_OK;
}

scpi_result_t SA_TRIGGER_DelayStateQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTriggerDelayStatus();
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRIGGER_ExteDelayStaQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTriggerDelayStatus(1);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRIGGER_VedioDelayStaQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTriggerDelayStatus(2);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRIGGER_PeriDelayStaQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTriggerDelayStatus(3);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRIGGER_RFDelayStaQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTriggerDelayStatus(4);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}


scpi_result_t SA_TRIGGER_DelayValue(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetTimeVal(context,&value);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setTriggerDelayValue(value);
    }
    return iback;
}
scpi_result_t SA_TRIGGER_ExteDelayVal(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetTimeVal(context,&value);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setTriggerDelayValue(value,1);
    }
    return iback;
}
scpi_result_t SA_TRIGGER_VedioDelayVal(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetTimeVal(context,&value);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setTriggerDelayValue(value,2);
    }
    return iback;
}
scpi_result_t SA_TRIGGER_PeriDelayVal(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetTimeVal(context,&value);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setTriggerDelayValue(value,3);
    }
    return iback;
}
scpi_result_t SA_TRIGGER_RFDelayVal(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetTimeVal(context,&value);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setTriggerDelayValue(value,4);
    }
    return iback;
}
scpi_result_t SA_TRIGGER_PeriTime(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetTimeVal(context,&value);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setTriggerPerTimer(value);
    }
    return iback;
}

scpi_result_t SA_TRIGGER_DelayValueQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTriggerDelayValue();
    if(!SCPI_ResultDouble(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRIGGER_ExteDelayValQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTriggerDelayValue(1);
    if(!SCPI_ResultDouble(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRIGGER_VedioDelayValQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTriggerDelayValue(2);
    if(!SCPI_ResultDouble(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRIGGER_PeriDelayValQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTriggerDelayValue(3);
    if(!SCPI_ResultDouble(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRIGGER_RFDelayValQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTriggerDelayValue(4);
    if(!SCPI_ResultDouble(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t SA_TRIGGER_PeriTimeQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getTriggerPerTimer();
    if(!SCPI_ResultDouble(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
