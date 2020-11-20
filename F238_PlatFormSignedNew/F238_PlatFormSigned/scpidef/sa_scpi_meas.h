#ifndef SA_SCPI_MEAS_H
#define SA_SCPI_MEAS_H


#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define SA_SCPI_COMMANDS_MEASURE \
    /* 0 -- Swept 1 -- channel power 3 -- occupied BW
     * 3 -- SEM   4 -- ACP           5 -- Multi-ACP
     * 6 -- spurious emission   7 -- Field strength 8 -- demodulation
     */\
{"[:SENSe]:MEASure:MODE", SA_MEASURE_Mode},/*{Int}*/\
{"[:SENSe]:MEASure:MODE?",SA_MEASURE_ModeQ},/*{Int}*/\
\
{"[:SENSe]:CHPOwer:CHBAndwidth", SA_CHPower_ChannelBw},/*{quint64}*/\
{"[:SENSe]:CHPOwer:CHBAndwidth?",SA_CHPower_ChannelBwQ},/*{quint64}*/\
\
{"[:SENSe]:OBWIdth:PERCent", SA_OBWidth_Percent},/*{Double}*/\
{"[:SENSe]:OBWIdth:PERCent?",SA_OBWidth_PercentQ},/*{Double}*/\
\
{"[:SENSe]:OBWidth:XDB", SA_OBWidth_XdB},/*{Double}*/\
{"[:SENSe]:OBWidth:XDB?",SA_OBWidth_XdBQ},/*{Double}*/\
\
{"[:SENSe]:SEM:VIEWtype", SA_SEM_ViewType},/*{int}*/\
{"[:SENSe]:SEM:VIEWtype?",SA_SEM_ViewTypeQ},/*{int}*/\
\
{"[:SENSe]:SEM:REFErence", SA_SEM_Reference},/*{int}*/\
{"[:SENSe]:SEM:REFErence?",SA_SEM_ReferenceQ},/*{int}*/\
\
{"[:SENSe]:ACPOwer:CHBAndwidth", SA_ACP_ChannelBw},/*{quint64}*/\
{"[:SENSe]:ACPOwer:CHBAndwidthQ?",SA_ACP_ChannelBwQ},/*{quint64}*/\
\
{"[:SENSe]:ACPOwer:CHSPace", SA_ACP_ChannelSpace},/*{quint64}*/\
{"[:SENSe]:ACPOwer:CHSPaceQ?",SA_ACP_ChannelSpaceQ},/*{quint64}*/\
\
{"[:SENSe]:MACPower:CHBAndwidth", SA_MACP_ChannelBw},/*{quint64}*/\
{"[:SENSe]:MACPower:CHBAndwidthQ?",SA_MACP_ChannelBwQ},/*{quint64}*/\
\
{"[:SENSe]:MACPower:CHSPace", SA_MACP_ChannelSpace},/*{quint64}*/\
{"[:SENSe]:MACPower:CHSPaceQ?",SA_MACP_ChannelSpaceQ},/*{quint64}*/\
\
{"[:SENSe]:SPURious:RESTart", SA_SPURIOUS_Restart},\
{"[:SENSe]:SPURious:AVERage:TYPE", SA_SPURIOUS_AveType},\
{"[:SENSe]:SPURious:AVERage:TYPE?", SA_SPURIOUS_AveTypeQ},\
{"[:SENSe]:SPURious:REPOrt:MODE", SA_SPURIOUS_ReportMode},\
{"[:SENSe]:SPURious:REPOrt:MODE?", SA_SPURIOUS_ReportModeQ},\
{"[:SENSe]:SPURious:SPUR", SA_SPURIOUS_SpurIndex},\
{"[:SENSe]:SPURious:SPUR?", SA_SPURIOUS_SpurIndexQ},\
    \
{"[:SENSe]:SPURious:RANGe:SELEct", SA_SPURIOUS_Select},\
{"[:SENSe]:SPURious:RANGe:SELEct?", SA_SPURIOUS_SelectQ},\
{"[:SENSe]:SPURious:RANGe:STATe", SA_SPURIOUS_State},/*{Int,Int}*/\
{"[:SENSe]:SPURious:RANGe:STATe?", SA_SPURIOUS_StateQ},\
{"[:SENSe]:SPURious:RANGe:FREQuency:STARt", SA_SPURIOUS_StartFreq},\
{"[:SENSe]:SPURious:RANGe:FREQuency:STARt?", SA_SPURIOUS_StartFreqQ},\
{"[:SENSe]:SPURious:RANGe:FREQuency:STOP", SA_SPURIOUS_StopFreq},\
{"[:SENSe]:SPURious:RANGe:FREQuency:STOP?", SA_SPURIOUS_StopFreqQ},\
{"[:SENSe]:SPURious:RANGe:SWEEp:TIME", SA_SPURIOUS_SweepTime},\
{"[:SENSe]:SPURious:RANGe:SWEEp:TIME?", SA_SPURIOUS_SweepTimeQ},\
{"[:SENSe]:SPURious:RANGe:RBW", SA_SPURIOUS_Rbw},\
{"[:SENSe]:SPURious:RANGe:RBW?", SA_SPURIOUS_RbwQ},\
{"[:SENSe]:SPURious:RANGe:VBW", SA_SPURIOUS_Vbw},\
{"[:SENSe]:SPURious:RANGe:VBW?", SA_SPURIOUS_VbwQ},\
{"[:SENSe]:SPURious:RANGe:LIMIt:STARt", SA_SPURIOUS_StartLimit},\
{"[:SENSe]:SPURious:RANGe:LIMIt:STARt?", SA_SPURIOUS_StartLimitQ},\
{"[:SENSe]:SPURious:RANGe:LIMIt:STOP", SA_SPURIOUS_StopLimit},\
{"[:SENSe]:SPURious:RANGe:LIMIt:STOP?", SA_SPURIOUS_StopLimitQ},\
{"[:SENSe]:SPURious:RANGe:PEAK:DEFInition", SA_SPURIOUS_PeakDefi},\
{"[:SENSe]:SPURious:RANGe:PEAK:DEFInition?", SA_SPURIOUS_PeakDefiQ},\
{"[:SENSe]:SPURious:RANGe:PEAK:THREshold", SA_SPURIOUS_PeakThreshold},\
{"[:SENSe]:SPURious:RANGe:PEAK:THREshold?", SA_SPURIOUS_PeakThresholdQ},\
{"[:SENSe]:SPURious:RANGe:ATTEn", SA_SPURIOUS_Atten},\
{"[:SENSe]:SPURious:RANGe:ATTEn?", SA_SPURIOUS_AttenQ},\
{"[:SENSe]:SPURious:DISPlay:TYPE", SA_SPURIOUS_DisplayType},\
{"[:SENSe]:SPURious:DISPlay:TYPE?", SA_SPURIOUS_DisplayTypeQ},\



scpi_result_t SA_MEASURE_Mode(scpi_t * context);
scpi_result_t SA_MEASURE_ModeQ(scpi_t * context);

scpi_result_t SA_CHPower_ChannelBw(scpi_t * context);
scpi_result_t SA_CHPower_ChannelBwQ(scpi_t * context);

scpi_result_t SA_OBWidth_Percent(scpi_t * context);
scpi_result_t SA_OBWidth_PercentQ(scpi_t * context);

scpi_result_t SA_OBWidth_XdB(scpi_t * context);
scpi_result_t SA_OBWidth_XdBQ(scpi_t * context);

scpi_result_t SA_SEM_ViewType(scpi_t * context);
scpi_result_t SA_SEM_ViewTypeQ(scpi_t * context);

scpi_result_t SA_SEM_Reference(scpi_t * context);
scpi_result_t SA_SEM_ReferenceQ(scpi_t * context);

scpi_result_t SA_ACP_ChannelBw(scpi_t * context);
scpi_result_t SA_ACP_ChannelBwQ(scpi_t * context);

scpi_result_t SA_ACP_ChannelSpace(scpi_t * context);
scpi_result_t SA_ACP_ChannelSpaceQ(scpi_t * context);

scpi_result_t SA_MACP_ChannelBw(scpi_t * context);
scpi_result_t SA_MACP_ChannelBwQ(scpi_t * context);

scpi_result_t SA_MACP_ChannelSpace(scpi_t * context);
scpi_result_t SA_MACP_ChannelSpaceQ(scpi_t * context);

scpi_result_t SA_SPURIOUS_Restart(scpi_t * context);

scpi_result_t SA_SPURIOUS_AveType(scpi_t * context);
scpi_result_t SA_SPURIOUS_AveTypeQ(scpi_t * context);
scpi_result_t SA_SPURIOUS_ReportMode(scpi_t * context);
scpi_result_t SA_SPURIOUS_ReportModeQ(scpi_t * context);
scpi_result_t SA_SPURIOUS_SpurIndex(scpi_t * context);
scpi_result_t SA_SPURIOUS_SpurIndexQ(scpi_t * context);
scpi_result_t SA_SPURIOUS_Select(scpi_t * context);
scpi_result_t SA_SPURIOUS_SelectQ(scpi_t * context);
scpi_result_t SA_SPURIOUS_State(scpi_t * context);
scpi_result_t SA_SPURIOUS_StateQ(scpi_t * context);
scpi_result_t SA_SPURIOUS_StartFreq(scpi_t * context);
scpi_result_t SA_SPURIOUS_StartFreqQ(scpi_t * context);
scpi_result_t SA_SPURIOUS_StopFreq(scpi_t * context);
scpi_result_t SA_SPURIOUS_StopFreqQ(scpi_t * context);
scpi_result_t SA_SPURIOUS_SweepTime(scpi_t * context);
scpi_result_t SA_SPURIOUS_SweepTimeQ(scpi_t * context);
scpi_result_t SA_SPURIOUS_Rbw(scpi_t * context);
scpi_result_t SA_SPURIOUS_RbwQ(scpi_t * context);
scpi_result_t SA_SPURIOUS_Vbw(scpi_t * context);
scpi_result_t SA_SPURIOUS_VbwQ(scpi_t * context);
scpi_result_t SA_SPURIOUS_StartLimit(scpi_t * context);
scpi_result_t SA_SPURIOUS_StartLimitQ(scpi_t * context);
scpi_result_t SA_SPURIOUS_StopLimit(scpi_t * context);
scpi_result_t SA_SPURIOUS_StopLimitQ(scpi_t * context);
scpi_result_t SA_SPURIOUS_PeakDefi(scpi_t * context);
scpi_result_t SA_SPURIOUS_PeakDefiQ(scpi_t * context);
scpi_result_t SA_SPURIOUS_PeakThreshold(scpi_t * context);
scpi_result_t SA_SPURIOUS_PeakThresholdQ(scpi_t * context);
scpi_result_t SA_SPURIOUS_Atten(scpi_t * context);
scpi_result_t SA_SPURIOUS_AttenQ(scpi_t * context);
scpi_result_t SA_SPURIOUS_DisplayType(scpi_t * context);
scpi_result_t SA_SPURIOUS_DisplayTypeQ(scpi_t * context);

#ifdef  __cplusplus
}
#endif

#endif // SA_SCPI_MEAS_H
