#include "sa_scpi_meas.h"

#include "remoteinterface.h"
#include "macrobus.h"
extern SYSTEM_STATUS g_systemStatus;
scpi_result_t GetFreqVal(scpi_t *context, quint64 *val);
scpi_result_t GetAmptVal(scpi_t *context, qreal *val);
scpi_result_t GetTimeVal(scpi_t *context, qreal *val);

scpi_result_t SA_MEASURE_Mode(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->SetMeasureItems(value);
    return SCPI_RES_OK;
}

scpi_result_t SA_MEASURE_ModeQ(scpi_t *context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->GetMeasureItems();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_CHPower_ChannelBw(scpi_t *context)
{
    quint64 ival = 0;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    scpi_result_t iback = GetFreqVal(context,&ival);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setChannelPower_ChannelBW(ival);
    }
    return iback;
}

scpi_result_t SA_CHPower_ChannelBwQ(scpi_t * context)
{
    quint64 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getChannelPower_ChannelBW();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_OBWidth_Percent(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setOccupiedBW_OccBW(value);
    return SCPI_RES_OK;

}

scpi_result_t SA_OBWidth_PercentQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getOccupiedBW_OccBW();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_OBWidth_XdB(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setOccupiedBW_XdB(value);
    return SCPI_RES_OK;
}

scpi_result_t SA_OBWidth_XdBQ(scpi_t * context)
{
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getOccupiedBW_XdB();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_SEM_ViewType(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setSpecEMDisplay(value);
    return SCPI_RES_OK;
}
scpi_result_t SA_SEM_ViewTypeQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpecEMDisplay();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_SEM_Reference(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setSpecEMRefType(value);
    return SCPI_RES_OK;
}
scpi_result_t SA_SEM_ReferenceQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpecEMRefType();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_ACP_ChannelBw(scpi_t * context)
{
    quint64 ival = 0;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    scpi_result_t iback = GetFreqVal(context,&ival);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setACP_ChannelBW(ival);
    }
    return iback;
}
scpi_result_t SA_ACP_ChannelBwQ(scpi_t * context)
{
    quint64 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getACP_ChannelBW();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_ACP_ChannelSpace(scpi_t * context)
{
    quint64 ival = 0;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    scpi_result_t iback = GetFreqVal(context,&ival);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setACP_ChannelSP(ival);
    }
    return iback;
}
scpi_result_t SA_ACP_ChannelSpaceQ(scpi_t * context)
{
    quint64 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getACP_ChannelSP();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_MACP_ChannelBw(scpi_t * context)
{
    quint64 ival = 0;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    scpi_result_t iback = GetFreqVal(context,&ival);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setACP_ChannelBW(ival);
    }
    return iback;
}
scpi_result_t SA_MACP_ChannelBwQ(scpi_t * context)
{
    quint64 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getACP_ChannelBW();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_MACP_ChannelSpace(scpi_t * context)
{
    quint64 ival = 0;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    scpi_result_t iback = GetFreqVal(context,&ival);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setACP_ChannelSP(ival);
    }
    return iback;
}
scpi_result_t SA_MACP_ChannelSpaceQ(scpi_t * context)
{
    quint64 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getACP_ChannelSP();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_SPURIOUS_Restart(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    remoteinterface::getsaremotehandle()->pcontrolInterface->setMeasureStatus(1);;
    return SCPI_RES_OK;
}

scpi_result_t SA_SPURIOUS_AveType(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setSpurEMAveType(value);
    return SCPI_RES_OK;
}
scpi_result_t SA_SPURIOUS_AveTypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpurEMAveType();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_SPURIOUS_ReportMode(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setSpurReportType(value);
    return SCPI_RES_OK;
}
scpi_result_t SA_SPURIOUS_ReportModeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpurReportType();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_SPURIOUS_SpurIndex(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setSpurEMCurSpurIndex(value-1);
    return SCPI_RES_OK;
}
scpi_result_t SA_SPURIOUS_SpurIndexQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpurEMCurSpurIndex();
    value += 1;
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_SPURIOUS_Select(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setSpurEMCurRangeIndex(value - 1);
    return SCPI_RES_OK;
}
scpi_result_t SA_SPURIOUS_SelectQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpurEMCurRangeIndex();
    value += 1;
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_SPURIOUS_State(scpi_t * context)
{
    qint32 index,value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if (!SCPI_ParamInt(context, &index, true))
    {
        return SCPI_RES_ERR;
    }
    if (!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }

    remoteinterface::getsaremotehandle()->pcontrolInterface->setSpurEMDisplay(value,index - 1);
    return SCPI_RES_OK;
}
scpi_result_t SA_SPURIOUS_StateQ(scpi_t * context)
{
    qint32 index,value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if (!SCPI_ParamInt(context, &index, true))
    {
        return SCPI_RES_ERR;
    }

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpurEMDisplay(index - 1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_SPURIOUS_StartFreq(scpi_t * context)
{
    qint32 index;
    quint64 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if (!SCPI_ParamInt(context, &index, true))
    {
        return SCPI_RES_ERR;
    }
    scpi_result_t iback = GetFreqVal(context,&value);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setSpurEMstartFreq((qreal)value,index - 1);
    }
    return iback;
}
scpi_result_t SA_SPURIOUS_StartFreqQ(scpi_t * context)
{
    qint32 index;
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if (!SCPI_ParamInt(context, &index, true))
    {
        return SCPI_RES_ERR;
    }

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpurEMstartFreq(index - 1);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_SPURIOUS_StopFreq(scpi_t * context)
{
    qint32 index;
    quint64 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if (!SCPI_ParamInt(context, &index, true))
    {
        return SCPI_RES_ERR;
    }
    scpi_result_t iback = GetFreqVal(context,&value);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setSpurEMstopFreq((qreal)value,index - 1);
    }
    return iback;
}
scpi_result_t SA_SPURIOUS_StopFreqQ(scpi_t * context)
{
    qint32 index;
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if (!SCPI_ParamInt(context, &index, true))
    {
        return SCPI_RES_ERR;
    }

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpurEMstopFreq(index - 1);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_SPURIOUS_SweepTime(scpi_t * context)
{
    qint32 index;
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if (!SCPI_ParamInt(context, &index, true))
    {
        return SCPI_RES_ERR;
    }
    scpi_result_t iback = GetTimeVal(context,&value);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setSpurEMSweepTime(value,index - 1);
    }
    return iback;
}
scpi_result_t SA_SPURIOUS_SweepTimeQ(scpi_t * context)
{
    qint32 index;
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if (!SCPI_ParamInt(context, &index, true))
    {
        return SCPI_RES_ERR;
    }

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpurEMSweepTime(index - 1);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_SPURIOUS_Rbw(scpi_t * context)
{
    qint32 index;
    quint64 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if (!SCPI_ParamInt(context, &index, true))
    {
        return SCPI_RES_ERR;
    }
    scpi_result_t iback = GetFreqVal(context,&value);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setSpurEMRBW((qreal)value,index - 1);
    }
    return iback;
}
scpi_result_t SA_SPURIOUS_RbwQ(scpi_t * context)
{
    qint32 index;
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if (!SCPI_ParamInt(context, &index, true))
    {
        return SCPI_RES_ERR;
    }

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpurEMRBW(index - 1);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_SPURIOUS_Vbw(scpi_t * context)
{
    qint32 index;
    quint64 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if (!SCPI_ParamInt(context, &index, true))
    {
        return SCPI_RES_ERR;
    }
    scpi_result_t iback = GetFreqVal(context,&value);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setSpurEMVBW((qreal)value,index - 1);
    }
    return iback;
}
scpi_result_t SA_SPURIOUS_VbwQ(scpi_t * context)
{
    qint32 index;
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if (!SCPI_ParamInt(context, &index, true))
    {
        return SCPI_RES_ERR;
    }

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpurEMVBW(index - 1);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_SPURIOUS_StartLimit(scpi_t * context)
{
    qint32 index;
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if (!SCPI_ParamInt(context, &index, true))
    {
        return SCPI_RES_ERR;
    }
    scpi_result_t iback = GetAmptVal(context,&value);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setSpurEMstartLimit((qreal)value,index - 1);
    }
    return iback;
}
scpi_result_t SA_SPURIOUS_StartLimitQ(scpi_t * context)
{
    qint32 index;
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if (!SCPI_ParamInt(context, &index, true))
    {
        return SCPI_RES_ERR;
    }

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpurEMStartLimit(index  - 1);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_SPURIOUS_StopLimit(scpi_t * context)
{
    qint32 index;
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if (!SCPI_ParamInt(context, &index, true))
    {
        return SCPI_RES_ERR;
    }
    scpi_result_t iback = GetAmptVal(context,&value);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setSpurEMStopLimit((qreal)value,index - 1);
    }
    return iback;
}
scpi_result_t SA_SPURIOUS_StopLimitQ(scpi_t * context)
{
    qint32 index;
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if (!SCPI_ParamInt(context, &index, true))
    {
        return SCPI_RES_ERR;
    }

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpurEMStopLimit(index - 1);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_SPURIOUS_PeakDefi(scpi_t * context)
{
    qint32 index;
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if (!SCPI_ParamInt(context, &index, true))
    {
        return SCPI_RES_ERR;
    }
    if (!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setSpurEMpeakDefi(value,index - 1);
    return SCPI_RES_OK;
}
scpi_result_t SA_SPURIOUS_PeakDefiQ(scpi_t * context)
{
    qint32 index;
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if (!SCPI_ParamInt(context, &index, true))
    {
        return SCPI_RES_ERR;
    }

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpurEMpeakDefi(index - 1);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_SPURIOUS_PeakThreshold(scpi_t * context)
{
    qint32 index;
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if (!SCPI_ParamInt(context, &index, true))
    {
        return SCPI_RES_ERR;
    }
    scpi_result_t iback = GetAmptVal(context,&value);
    if(iback)
    {
        remoteinterface::getsaremotehandle()->pcontrolInterface->setSpurEMpeakThreshold((qreal)value,index - 1);
    }
    return iback;
}
scpi_result_t SA_SPURIOUS_PeakThresholdQ(scpi_t * context)
{
    qint32 index;
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if (!SCPI_ParamInt(context, &index, true))
    {
        return SCPI_RES_ERR;
    }

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpurEMpeakThreshold(index - 1);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
scpi_result_t SA_SPURIOUS_Atten(scpi_t * context)
{
    qint32 index;
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if (!SCPI_ParamInt(context, &index, true))
    {
        return SCPI_RES_ERR;
    }
    if (!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setSpurEMAtten(value,index - 1);
    return SCPI_RES_OK;
}
scpi_result_t SA_SPURIOUS_AttenQ(scpi_t * context)
{
    qint32 index;
    qreal value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if (!SCPI_ParamInt(context, &index, true))
    {
        return SCPI_RES_ERR;
    }

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpurEMAtten();
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_SPURIOUS_DisplayType(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->pcontrolInterface->setSpurEMTableType(value);
    return SCPI_RES_OK;
}
scpi_result_t SA_SPURIOUS_DisplayTypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->pcontrolInterface->getSpurEMTableType();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
