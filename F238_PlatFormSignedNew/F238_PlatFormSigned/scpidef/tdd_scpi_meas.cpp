#include "tdd_scpi_meas.h"
#include "lte_scpi_def.h"

#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;
extern scpi_result_t GetFreqVal(scpi_t *context, quint64 *val);

scpi_result_t TDD_ChannelBW(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    quint64 value = 0;
    scpi_result_t iback = GetFreqVal(context, &value);
    if(iback)
    {
        remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_RF_CHANNELBW, value);
    }
    return iback;
}

scpi_result_t TDD_SubFrame(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_PVT_SUBFRAMENO, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CellID_Auto(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MODU_CELLID, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CellID(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MODU_CELLIDVALUE, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CyclicPrefix(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_PVT_CP, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_AntPort(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_PVT_ANTENNAPORT, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_PhichDuration(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MODU_PHICHDURATION, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_PhichNG(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MODU_PHICHNG, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_ModulationType(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MODU_TYPE, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CFI_Auto(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MODU_CFI, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CFI(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MODU_CFIVALUE, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_RBIndex(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MODU_RBINDEX, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_SearchPMax(scpi_t *context)
{
    Q_UNUSED(context);
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MODU_RBPEAK);
    return SCPI_RES_OK;
}

scpi_result_t TDD_SearchPMin(scpi_t *context)
{
    Q_UNUSED(context);
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MODU_RBMIN);
    return SCPI_RES_OK;
}

scpi_result_t TDD_SearchMaxPrevious(scpi_t *context)
{
    Q_UNUSED(context);
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MODU_RBPREVIOUS);
    return SCPI_RES_OK;
}

scpi_result_t TDD_SearchMaxNext(scpi_t *context)
{
    Q_UNUSED(context);
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MODU_RBNEXT);
    return SCPI_RES_OK;
}

scpi_result_t TDD_SubFrame_UpDown(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_PVT_UPDCONFIG, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_SubFrame_Special(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_PVT_SPECONFIG, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CHPower_IntegrationBW(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    quint64 value = 0;
    scpi_result_t iback = GetFreqVal(context, &value);
    if(iback)
    {
        remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_RF_INTEGRATIONBW, value);
    }
    return iback;
}

scpi_result_t TDD_CHPower_PowerLimit(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_RF_POWERLIMITON, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CHPower_PowerLimitValue(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_RF_POWERLIMITVALUE, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CHPower_PSDLimit(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_RF_PSDLIMITON, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CHPower_PSDLimitValue(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_RF_PSDLIMITVALUE, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CHPower_Preset(scpi_t *context)
{
    Q_UNUSED(context);
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_RF_CHANNELPOWERPRESET);
    return SCPI_RES_OK;
}

scpi_result_t TDD_OBWidth_Method(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_RF_OBWMETHOD, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_OBWidth_Percent(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_RF_OBWPOWER, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_OBWidth_XdB(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_RF_OBWXDB, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_OBWidth_Limit(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_RF_OBWLIMITON, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_OBWidth_LimitValue(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_RF_OBWLIMITVALUE, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_OBWidth_Preset(scpi_t *context)
{
    Q_UNUSED(context);
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_RF_OBWPRESET);
    return SCPI_RES_OK;
}

scpi_result_t TDD_TAE_ReferenceTime(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_MODU_REFTIME, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_TAE_ScaleTime(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_MODU_SCALETIME, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList_State(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_OTA_FREQUENCYLIST, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList1_AddFrequency(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_OTA_LISTADDFREQ1, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList2_AddFrequency(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_OTA_LISTADDFREQ2, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList3_AddFrequency(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_OTA_LISTADDFREQ3, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList4_AddFrequency(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_OTA_LISTADDFREQ4, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList5_AddFrequency(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_OTA_LISTADDFREQ5, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList6_AddFrequency(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_OTA_LISTADDFREQ6, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList1_AddChannelNo(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_OTA_LISTADDCHANNELNO1, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList2_AddChannelNo(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_OTA_LISTADDCHANNELNO2, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList3_AddChannelNo(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_OTA_LISTADDCHANNELNO3, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList4_AddChannelNo(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_OTA_LISTADDCHANNELNO4, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList5_AddChannelNo(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_OTA_LISTADDCHANNELNO5, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList6_AddChannelNo(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_OTA_LISTADDCHANNELNO6, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList1_AddChannelStandard(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_OTA_LISTADDCHANNELSTD1, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList2_AddChannelStandard(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_OTA_LISTADDCHANNELSTD2, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList3_AddChannelStandard(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_OTA_LISTADDCHANNELSTD3, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList4_AddChannelStandard(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_OTA_LISTADDCHANNELSTD4, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList5_AddChannelStandard(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_OTA_LISTADDCHANNELSTD5, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList6_AddChannelStandard(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_OTA_LISTADDCHANNELSTD6, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_Mapping_Plot(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_OTA_MAPPLOTSTART, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_Mapping_PlotItem(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_OTA_MAPPLOTITEM, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_Mapping_PanNavigate(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_OTA_MAPPANON, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_Mapping_PlotTable(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_OTA_MAPPLOTTABLE, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC_Select(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_SELECT, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC_Active(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_ON, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC1_Active(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_CC1ON, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC2_Active(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_CC2ON, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC3_Active(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_CC3ON, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC4_Active(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_CC4ON, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC5_Active(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_CC5ON, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC_CenterFrequency(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_CA_CENTFREQ, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC1_CenterFrequency(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_CA_CC1CENTFREQ, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC2_CenterFrequency(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_CA_CC2CENTFREQ, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC3_CenterFrequency(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_CA_CC3CENTFREQ, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC4_CenterFrequency(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_CA_CC4CENTFREQ, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC5_CenterFrequency(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_CA_CC5CENTFREQ, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC_BandWidth(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_CA_CHANNELBW, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC1_BandWidth(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_CA_CC1CHANNELBW, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC2_BandWidth(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_CA_CC2CHANNELBW, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC3_BandWidth(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_CA_CC3CHANNELBW, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC4_BandWidth(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_CA_CC4CHANNELBW, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC5_BandWidth(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_CA_CC5CHANNELBW, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC_PhichDuration(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_PHICHDURA, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC1_PhichDuration(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_CC1PHICHDURA, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC2_PhichDuration(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_CC2PHICHDURA, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC3_PhichDuration(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_CC3PHICHDURA, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC4_PhichDuration(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_CC4PHICHDURA, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC5_PhichDuration(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_CC5PHICHDURA, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC_PhichNG(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_PHICHNG, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC1_PhichNG(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_CC1PHICHNG, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC2_PhichNG(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_CC2PHICHNG, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC3_PhichNG(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_CC3PHICHNG, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC4_PhichNG(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_CC4PHICHNG, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC5_PhichNG(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_CC5PHICHNG, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC_CyclicPrefix(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_CP, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC1_CyclicPrefix(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_CC1CP, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC2_CyclicPrefix(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_CC2CP, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC3_CyclicPrefix(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_CC3CP, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC4_CyclicPrefix(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_CC4CP, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC5_CyclicPrefix(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_CC5CP, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC_AntPort(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_ANTPORT, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC1_AntPort(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_CC1ANTPORT, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC2_AntPort(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_CC2ANTPORT, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC3_AntPort(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_CC3ANTPORT, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC4_AntPort(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_CC4ANTPORT, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC5_AntPort(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_CA_CC5ANTPORT, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_DAM_ColorMap_AutoScale(scpi_t *context)
{
    Q_UNUSED(context);
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MODU_AUTOSCALECOLORMAP);
    return SCPI_RES_OK;
}

scpi_result_t TDD_DAM_ColorMap_MaxValue(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_MODU_COLORMAPMAX, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_DAM_ColorMap_Range(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_MODU_COLORMAPRANGE, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_DataGram_ColorMap_AutoScale(scpi_t *context)
{
    Q_UNUSED(context);
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_OTA_AUTOSCALECOLORMAP);
    return SCPI_RES_OK;
}

scpi_result_t TDD_DataGram_ColorMap_MaxValue(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_OTA_COLORMAPMAX, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_DataGram_ColorMap_Range(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    if(!SCPI_ParamDouble(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamDouble(LTE_SCPI_OTA_COLORMAPRANGE, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_Measure_Mode(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SetMeasureItems(value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_ChannelBWQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    quint64 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_RF_CHANNELBW);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_SubFrameQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_PVT_SUBFRAMENO);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CellID_AutoQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MODU_CELLID);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CellIDQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MODU_CELLIDVALUE);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CyclicPrefixQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_PVT_CP);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_AntPortQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_PVT_ANTENNAPORT);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_PhichDurationQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MODU_PHICHDURATION);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_PhichNGQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MODU_PHICHNG);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_ModulationTypeQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MODU_TYPE);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CFI_AutoQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MODU_CFI);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CFIQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MODU_CFIVALUE);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_RBIndexQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MODU_RBINDEX);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_SubFrame_UpDownQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_PVT_UPDCONFIG);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_SubFrame_SpecialQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_PVT_SPECONFIG);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CHPower_IntegrationBWQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    quint64 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_RF_INTEGRATIONBW);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CHPower_PowerLimitQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_RF_POWERLIMITON);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CHPower_PowerLimitValueQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_RF_POWERLIMITVALUE);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CHPower_PSDLimitQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_RF_PSDLIMITON);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CHPower_PSDLimitValueQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_RF_PSDLIMITVALUE);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_OBWidth_MethodQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_RF_OBWMETHOD);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_OBWidth_PercentQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_RF_OBWPOWER);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_OBWidth_XdBQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_RF_OBWXDB);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_OBWidth_LimitQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_RF_OBWLIMITON);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_OBWidth_LimitValueQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_RF_OBWLIMITVALUE);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_TAE_ReferenceTimeQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_MODU_REFTIME);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_TAE_ScaleTimeQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_MODU_SCALETIME);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList1_AddFrequencyQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_OTA_LISTADDFREQ1);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList2_AddFrequencyQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_OTA_LISTADDFREQ2);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList3_AddFrequencyQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_OTA_LISTADDFREQ3);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList4_AddFrequencyQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_OTA_LISTADDFREQ4);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList5_AddFrequencyQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_OTA_LISTADDFREQ5);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList6_AddFrequencyQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_OTA_LISTADDFREQ6);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList1_AddChannelNoQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_OTA_LISTADDCHANNELNO1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList2_AddChannelNoQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_OTA_LISTADDCHANNELNO2);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList3_AddChannelNoQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_OTA_LISTADDCHANNELNO3);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList4_AddChannelNoQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_OTA_LISTADDCHANNELNO4);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList5_AddChannelNoQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_OTA_LISTADDCHANNELNO5);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList6_AddChannelNoQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_OTA_LISTADDCHANNELNO6);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList1_AddChannelStandardQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_OTA_LISTADDCHANNELSTD1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList2_AddChannelStandardQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_OTA_LISTADDCHANNELSTD2);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList3_AddChannelStandardQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_OTA_LISTADDCHANNELSTD3);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList4_AddChannelStandardQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_OTA_LISTADDCHANNELSTD4);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList5_AddChannelStandardQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_OTA_LISTADDCHANNELSTD5);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_FreqList6_AddChannelStandardQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_OTA_LISTADDCHANNELSTD6);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_Mapping_PlotQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_OTA_MAPPLOTSTART);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_Mapping_PlotItemQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_OTA_MAPPLOTITEM);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_Mapping_PanNavigateQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_OTA_MAPPANON);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_Mapping_PlotTableQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_OTA_MAPPLOTTABLE);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC_SelectQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_SELECT);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC_ActiveQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_ON);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC1_ActiveQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_CC1ON);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC2_ActiveQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_CC2ON);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC3_ActiveQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_CC3ON);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC4_ActiveQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_CC4ON);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC5_ActiveQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_CC5ON);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC_CenterFrequencyQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_CA_CENTFREQ);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC1_CenterFrequencyQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_CA_CC1CENTFREQ);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC2_CenterFrequencyQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_CA_CC2CENTFREQ);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC3_CenterFrequencyQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_CA_CC3CENTFREQ);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC4_CenterFrequencyQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_CA_CC4CENTFREQ);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC5_CenterFrequencyQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_CA_CC5CENTFREQ);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC_BandWidthQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_CA_CHANNELBW);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC1_BandWidthQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_CA_CC1CHANNELBW);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC2_BandWidthQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_CA_CC2CHANNELBW);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC3_BandWidthQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_CA_CC3CHANNELBW);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC4_BandWidthQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_CA_CC4CHANNELBW);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC5_BandWidthQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_CA_CC5CHANNELBW);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC_PhichDurationQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_PHICHDURA);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC1_PhichDurationQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_CC1PHICHDURA);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC2_PhichDurationQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_CC2PHICHDURA);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC3_PhichDurationQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_CC3PHICHDURA);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC4_PhichDurationQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_CC4PHICHDURA);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC5_PhichDurationQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_CC5PHICHDURA);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC_PhichNGQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_PHICHNG);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC1_PhichNGQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_CC1PHICHNG);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC2_PhichNGQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_CC2PHICHNG);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC3_PhichNGQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_CC3PHICHNG);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC4_PhichNGQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_CC4PHICHNG);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC5_PhichNGQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_CC5PHICHNG);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC_CyclicPrefixQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_CP);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC1_CyclicPrefixQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_CC1CP);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC2_CyclicPrefixQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_CC2CP);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC3_CyclicPrefixQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_CC3CP);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC4_CyclicPrefixQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_CC4CP);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC5_CyclicPrefixQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_CC5CP);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC_AntPortQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_ANTPORT);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC1_AntPortQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_CC1ANTPORT);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC2_AntPortQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_CC2ANTPORT);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC3_AntPortQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_CC3ANTPORT);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC4_AntPortQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_CC4ANTPORT);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_CC5_AntPortQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_CA_CC5ANTPORT);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_DAM_ColorMap_MaxValueQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_MODU_COLORMAPMAX);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_DAM_ColorMap_RangeQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_MODU_COLORMAPRANGE);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_DataGram_ColorMap_MaxValueQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_OTA_COLORMAPMAX);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_DataGram_ColorMap_RangeQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultDouble(LTE_SCPI_OTA_COLORMAPRANGE);
    if(!SCPI_ResultDouble(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_Measure_ModeQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->GetMeasureItems();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
