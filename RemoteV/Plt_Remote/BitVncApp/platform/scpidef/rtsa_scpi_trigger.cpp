#include "rtsa_scpi_trigger.h"

#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"
extern SYSTEM_STATUS g_systemStatus;
extern scpi_result_t GetDoubleFreqVal(scpi_t *context, qreal *val);
scpi_result_t GetAmptVal(scpi_t *context, qreal *val);
scpi_result_t GetTimeVal(scpi_t *context, qreal *val);

scpi_result_t RTSA_TRIGGER_Type(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setTrigger(value);
    return SCPI_RES_OK;
}

scpi_result_t RTSA_TRIGGER_Level(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetAmptVal(context,&value);
//    if(iback)
//    {
//        remoteinterface::getrtsaremotehandle()->InterfaceObj->setTriggerLevel(value);
//    }
    return iback;
}
scpi_result_t RTSA_TRIGGER_ExteLevel(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetAmptVal(context,&value);
    if(iback)
    {
        remoteinterface::getrtsaremotehandle()->InterfaceObj->setTriggerLevel(RTSA_TRIGGER_EXTERNAL,value);
    }
    return iback;
}
scpi_result_t RTSA_TRIGGER_VedioLevel(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetAmptVal(context,&value);
    if(iback)
    {
        remoteinterface::getrtsaremotehandle()->InterfaceObj->setTriggerLevel(RTSA_TRIGGER_VIDEO,value);
    }
    return iback;
}
scpi_result_t RTSA_TRIGGER_RFLevel(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetAmptVal(context,&value);
    if(iback)
    {
        remoteinterface::getrtsaremotehandle()->InterfaceObj->setTriggerLevel(RTSA_TRIGGER_RF_BURST,value);
    }
    return iback;
}
scpi_result_t RTSA_TRIGGER_SlopeStatus(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
//    remoteinterface::getrtsaremotehandle()->InterfaceObj->setTriggerSlope(value);
    return SCPI_RES_OK;
}

scpi_result_t RTSA_TRIGGER_TypeQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getTrigger();
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_LevelQ(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

//    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getTriggerLevel();
//    if(!SCPI_ResultDouble(context, value))
//      {
//        return SCPI_RES_ERR;
//      }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_ExteLevelQ(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getTriggerLevel(RTSA_TRIGGER_EXTERNAL);
    if(!SCPI_ResultDouble(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_VedioLevelQ(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getTriggerLevel(RTSA_TRIGGER_VIDEO);
    if(!SCPI_ResultDouble(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_RFLevelQ(scpi_t *context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getTriggerLevel(RTSA_TRIGGER_RF_BURST);
    if(!SCPI_ResultDouble(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_TRIGGER_SlopeState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
//    remoteinterface::getrtsaremotehandle()->InterfaceObj->setTriggerSlope(value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_ExteSlope(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setTriggerSlope(RTSA_TRIGGER_EXTERNAL,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_VedioSlope(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setTriggerSlope(RTSA_TRIGGER_VIDEO,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_RFSlope(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setTriggerSlope(RTSA_TRIGGER_RF_BURST,value);
    return SCPI_RES_OK;
}


scpi_result_t RTSA_TRIGGER_SlopeStateQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

//    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getTriggerSlope();
//    if(!SCPI_ResultInt(context, value))
//      {
//        return SCPI_RES_ERR;
//      }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_ExteSlopeQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getTriggerSlope(RTSA_TRIGGER_EXTERNAL);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_VedioSlopeQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getTriggerSlope(RTSA_TRIGGER_VIDEO);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_RFSlopeQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getTriggerSlope(RTSA_TRIGGER_RF_BURST);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}


scpi_result_t RTSA_TRIGGER_DelayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
//    remoteinterface::getrtsaremotehandle()->InterfaceObj->setTriggerDelayStatus(value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_ExteDelaySta(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setTriggerDelayStatus(RTSA_TRIGGER_EXTERNAL,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_VedioDelaySta(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setTriggerDelayStatus(RTSA_TRIGGER_VIDEO,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_PeriDelaySta(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setTriggerDelayStatus(RTSA_TRIGGER_PERIODIC_TIMER,value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_RFDelaySta(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setTriggerDelayStatus(RTSA_TRIGGER_RF_BURST,value);
    return SCPI_RES_OK;
}

scpi_result_t RTSA_TRIGGER_DelayStateQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

//    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getTriggerDelayStatus();
//    if(!SCPI_ResultInt(context, value))
//      {
//        return SCPI_RES_ERR;
//      }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_ExteDelayStaQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getTriggerDelayStatus(RTSA_TRIGGER_EXTERNAL);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_VedioDelayStaQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getTriggerDelayStatus(RTSA_TRIGGER_VIDEO);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_PeriDelayStaQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getTriggerDelayStatus(RTSA_TRIGGER_PERIODIC_TIMER);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_RFDelayStaQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getTriggerDelayStatus(RTSA_TRIGGER_RF_BURST);
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}


scpi_result_t RTSA_TRIGGER_DelayValue(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetTimeVal(context,&value);
    if(iback)
    {
//        remoteinterface::getrtsaremotehandle()->InterfaceObj->setTriggerDelayValue(value);
    }
    return iback;
}
scpi_result_t RTSA_TRIGGER_ExteDelayVal(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetTimeVal(context,&value);
    if(iback)
    {
        remoteinterface::getrtsaremotehandle()->InterfaceObj->setTriggerDelay(RTSA_TRIGGER_EXTERNAL,value);
    }
    return iback;
}
scpi_result_t RTSA_TRIGGER_VedioDelayVal(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetTimeVal(context,&value);
    if(iback)
    {
        remoteinterface::getrtsaremotehandle()->InterfaceObj->setTriggerDelay(RTSA_TRIGGER_VIDEO,value);
    }
    return iback;
}
scpi_result_t RTSA_TRIGGER_PeriDelayVal(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetTimeVal(context,&value);
    if(iback)
    {
        remoteinterface::getrtsaremotehandle()->InterfaceObj->setTriggerDelay(RTSA_TRIGGER_PERIODIC_TIMER,value);
    }
    return iback;
}
scpi_result_t RTSA_TRIGGER_RFDelayVal(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetTimeVal(context,&value);
    if(iback)
    {
        remoteinterface::getrtsaremotehandle()->InterfaceObj->setTriggerDelay(RTSA_TRIGGER_RF_BURST,value);
    }
    return iback;
}
scpi_result_t RTSA_TRIGGER_PeriTime(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetTimeVal(context,&value);
    if(iback)
    {
        remoteinterface::getrtsaremotehandle()->InterfaceObj->setTriggerPeriodTime(value);
    }
    return iback;
}

scpi_result_t RTSA_TRIGGER_DelayValueQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

//    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->gettr();
//    if(!SCPI_ResultDouble(context, value))
//      {
//        return SCPI_RES_ERR;
//      }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_ExteDelayValQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getTriggerDelay(RTSA_TRIGGER_EXTERNAL);
    if(!SCPI_ResultDouble(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_VedioDelayValQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getTriggerDelay(RTSA_TRIGGER_VIDEO);
    if(!SCPI_ResultDouble(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_PeriDelayValQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getTriggerDelay(RTSA_TRIGGER_PERIODIC_TIMER);
    if(!SCPI_ResultDouble(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_RFDelayValQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getTriggerDelay(RTSA_TRIGGER_RF_BURST);
    if(!SCPI_ResultDouble(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_PeriTimeQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getTriggerPeriodTime();
    if(!SCPI_ResultDouble(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
//Albert add 10/10
scpi_result_t RTSA_TRIGGER_Extern_HoldOff(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetTimeVal(context,&value);
    if(iback)
    {
        remoteinterface::getrtsaremotehandle()->InterfaceObj->settriggerHoldOffTime(RTSA_TRIGGER_EXTERNAL,value);
    }
    return iback;
}
scpi_result_t RTSA_TRIGGER_Extern_HoldOffQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getriggerHoldOffTime(RTSA_TRIGGER_EXTERNAL);
    if(!SCPI_ResultDouble(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_RFburst_HoldOff(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetTimeVal(context,&value);
    if(iback)
    {
        remoteinterface::getrtsaremotehandle()->InterfaceObj->settriggerHoldOffTime(RTSA_TRIGGER_RF_BURST,value);
    }
    return iback;
}
scpi_result_t RTSA_TRIGGER_RFburst_HoldOffQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getriggerHoldOffTime(RTSA_TRIGGER_RF_BURST);
    if(!SCPI_ResultDouble(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_Fmt_HoldOff(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    scpi_result_t iback = GetTimeVal(context,&value);
    if(iback)
    {
        remoteinterface::getrtsaremotehandle()->InterfaceObj->settriggerHoldOffTime(RTSA_TRIGGER_FMTMASK,value);
    }
    return iback;
}
scpi_result_t RTSA_TRIGGER_Fmt_HoldOffQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getriggerHoldOffTime(RTSA_TRIGGER_FMTMASK);
    if(!SCPI_ResultDouble(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_TRIGGER_Fmt_Mask_build(scpi_t *context)
{
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getrtsaremotehandle()->InterfaceObj->BuildFmtFromTrace();
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_Fmt_Mask_Delete(scpi_t *context)
{
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getrtsaremotehandle()->InterfaceObj->DeleteAllFmtMask();
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_Fmt_Mask_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setFmtType(value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_Fmt_Mask_TypeQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getFmtType();
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_TRIGGER_Fmt_Mask_Critertion(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setFmtTriggerCriterion(value);
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_Fmt_Mask_CritertionQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getFmtTriggerCriterion();
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}

scpi_result_t RTSA_TRIGGER_Fmt_Mask_PointCountQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getrtsaremotehandle()->InterfaceObj->getFmtDataNum();
    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_Fmt_Mask_PointFreqData(scpi_t * context)
{
    qint32 point,limit;
    qreal freq;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &point, true))
    {
        return SCPI_RES_ERR;
    }
    scpi_result_t iback = GetDoubleFreqVal(context,&freq);
    if(iback)
      {
        remoteinterface::getrtsaremotehandle()->InterfaceObj->setCurFmtFreqData(freq,point - 1);
        remoteinterface::getrtsaremotehandle()->InterfaceObj->ReSetAllFmtData();
      }
    return iback;
}
scpi_result_t RTSA_TRIGGER_Fmt_Mask_PointFreqDataQ(scpi_t * context)
{
    qint32 point,limit;
    qreal freq;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &point, true))
    {
        return SCPI_RES_ERR;
    }

    freq = remoteinterface::getrtsaremotehandle()->InterfaceObj->getCurFmtFreqData(point - 1);
    if(!SCPI_ResultDouble(context, freq))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_Fmt_Mask_PointAmptData(scpi_t * context)
{
    qint32 point,limit;
    qreal  ampt;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &point, true))
    {
        return SCPI_RES_ERR;
    }
    scpi_result_t iback = GetAmptVal(context,&ampt);
    if(iback)
    {
        remoteinterface::getrtsaremotehandle()->InterfaceObj->setCurFmtAmptData(ampt,point - 1);
        remoteinterface::getrtsaremotehandle()->InterfaceObj->ReSetAllFmtData();
    }
    return iback;
}
scpi_result_t RTSA_TRIGGER_Fmt_Mask_PointAmptDataQ(scpi_t * context)
{
    qint32 point,limit;
    qreal ampt;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &point, true))
    {
        return SCPI_RES_ERR;
    }
    ampt = remoteinterface::getrtsaremotehandle()->InterfaceObj->getCurFmtAmptData(point - 1);
    if(!SCPI_ResultDouble(context, ampt))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t RTSA_TRIGGER_Fmt_Mask_Insert(scpi_t * context)
{
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getrtsaremotehandle()->InterfaceObj->InsertFmtDataRow();
    return SCPI_RES_OK;
}


