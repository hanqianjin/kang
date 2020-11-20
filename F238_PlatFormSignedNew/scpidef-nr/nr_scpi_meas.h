#ifndef NR_SCPI_MEAS_H
#define NR_SCPI_MEAS_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define NR_SCPI_COMMANDS_MEASURE \
{"[:SENSe]:MEASure:MODE", NR_MEASURE_Mode},/*{Int}*/\
{"[:SENSe]:MEASure:MODE?",NR_MEASURE_ModeQ},/*{Int}*/\
    \
{"[:SENSe]:CHBAndwidth", NR_ChannelBw},/*{quint64}*/\
{"[:SENSe]:CHBAndwidth?",NR_ChannelBwQ},/*{quint64}*/\
    \
{"[:SENSe]:CHPOwer:INTEGration", NR_CHPower_IntegrationBW},/*{quint64}*/\
{"[:SENSe]:CHPOwer:INTEGration?",NR_CHPower_IntegrationBWQ},/*{quint64}*/\
{"[:SENSe]:CHPOwer:LIMIt:POWer:STATe", NR_CHPower_LimitPower},/*{Int}*/\
{"[:SENSe]:CHPOwer:LIMIt:POWer:STATe?",NR_CHPower_LimitPowerQ},/*{Int}*/\
{"[:SENSe]:CHPOwer:LIMIt:POWer:VALue", NR_CHPower_LimitPowerValue},/*{double}*/\
{"[:SENSe]:CHPOwer:LIMIt:POWer:VALue?",NR_CHPower_LimitPowerValueQ},/*{double}*/\
{"[:SENSe]:CHPOwer:LIMIt:PSD:STATe", NR_CHPower_LimitPsd},/*{Int}*/\
{"[:SENSe]:CHPOwer:LIMIt:PSD:STATe?",NR_CHPower_LimitPsdQ},/*{Int}*/\
{"[:SENSe]:CHPOwer:LIMIt:PSD:VALue", NR_CHPower_LimitPsdValue},/*{double}*/\
{"[:SENSe]:CHPOwer:LIMIt:PSD:VALue?",NR_CHPower_LimitPsdValueQ},/*{double}*/\
{"[:SENSe]:CHPOwer:PRESet", NR_CHPower_CfgPreset},/*{none}*/\
    \
{"[:SENSe]:OBWIdth:METHod", NR_OBWidth_Method},/*{Int}*/\
{"[:SENSe]:OBWIdth:METHod?",NR_OBWidth_MethodQ},/*{Int}*/\
{"[:SENSe]:OBWIdth:PERCent", NR_OBWidth_Percent},/*{Double}*/\
{"[:SENSe]:OBWIdth:PERCent?",NR_OBWidth_PercentQ},/*{Double}*/\
{"[:SENSe]:OBWidth:XDB", NR_OBWidth_XdB},/*{Double}*/\
{"[:SENSe]:OBWidth:XDB?",NR_OBWidth_XdBQ},/*{Double}*/\
{"[:SENSe]:OBWidth:LIMIt:STATe", NR_OBWidth_Limit},/*{Int}*/\
{"[:SENSe]:OBWidth:LIMIt:STATe?",NR_OBWidth_LimitQ},/*{Int}*/\
{"[:SENSe]:OBWidth:LIMIt:VALue", NR_OBWidth_LimitValue},/*{quint64}*/\
{"[:SENSe]:OBWidth:LIMIt:VALue?",NR_OBWidth_LimitValueQ},/*{quint64}*/\
{"[:SENSe]:OBWidth:PRESet", NR_OBWidth_CfgPreset},/*{none}*/\
    \
{"[:SENSe]:EIRPower:RAGain", NR_EIRPower_RxAntGain},/*{Double}*/\
{"[:SENSe]:EIRPower:RAGain?",NR_EIRPower_RxAntGainQ},/*{Double}*/\
{"[:SENSe]:EIRPower:DISTance", NR_EIRPower_DistanceToAnt},/*{Double}*/\
{"[:SENSe]:EIRPower:DISTance?",NR_EIRPower_DistanceToAntQ},/*{Double}*/\
{"[:SENSe]:EIRPower:DISTance:UNIT", NR_EIRPower_DistanceUnit},/*{Int}*/\
{"[:SENSe]:EIRPower:DISTance:UNIT?",NR_EIRPower_DistanceUnitQ},/*{Int}*/\
{"[:SENSe]:EIRPower:LIMIt:UPPer:STATe", NR_EIRPower_UpperLimit},/*{Int}*/\
{"[:SENSe]:EIRPower:LIMIt:UPPer:STATe?",NR_EIRPower_UpperLimitQ},/*{Int}*/\
{"[:SENSe]:EIRPower:LIMIt:UPPer:VALue", NR_EIRPower_UpperLimitValue},/*{Double}*/\
{"[:SENSe]:EIRPower:LIMIt:UPPer:VALue?",NR_EIRPower_UpperLimitValueQ},/*{Double}*/\
{"[:SENSe]:EIRPower:LIMIt:LOWer:STATe", NR_EIRPower_LowerLimit},/*{Int}*/\
{"[:SENSe]:EIRPower:LIMIt:LOWer:STATe?",NR_EIRPower_LowerLimitQ},/*{Int}*/\
{"[:SENSe]:EIRPower:LIMIt:LOWer:VALue", NR_EIRPower_LowerLimitValue},/*{Double}*/\
{"[:SENSe]:EIRPower:LIMIt:LOWer:VALue?",NR_EIRPower_LowerLimitValueQ},/*{Double}*/\
{"[:SENSe]:EIRPower:CLOSs", NR_EIRPower_RxCableLoss},/*{Double}*/\
{"[:SENSe]:EIRPower:CLOSs?",NR_EIRPower_RxCableLossQ},/*{Double}*/\
{"[:SENSe]:EIRPower:MAXHOld", NR_EIRPower_MaxHold},/*{none}*/\
{"[:SENSe]:EIRPower:PRESet", NR_EIRPower_CfgPreset},/*{none}*/\
    \
{"[:SENSe]:BEAM:SSB:SCS", NR_BEAM_SSBSubCaSpac},/*{Int}*/\
{"[:SENSe]:BEAM:SSB:SCS?",NR_BEAM_SSBSubCaSpacQ},/*{Int}*/\
{"[:SENSe]:BEAM:SSB:OFFSet", NR_BEAM_SSBOffset},/*{quint64}*/\
{"[:SENSe]:BEAM:SSB:OFFSet?",NR_BEAM_SSBOffsetQ},/*{quint64}*/\
{"[:SENSe]:BEAM:SINR:THRESHold", NR_BEAM_SinrThreshold},/*{Double}*/\
{"[:SENSe]:BEAM:SINR:THRESHold?",NR_BEAM_SinrThresholdQ},/*{Double}*/\
{"[:SENSe]:BEAM:VIEW:TYPE", NR_BEAM_ViewMode},/*{Int}*/\
{"[:SENSe]:BEAM:VIEW:TYPE?",NR_BEAM_ViewModeQ},/*{Int}*/\

scpi_result_t NR_MEASURE_Mode(scpi_t * context);
scpi_result_t NR_MEASURE_ModeQ(scpi_t * context);

scpi_result_t NR_ChannelBw(scpi_t * context);
scpi_result_t NR_ChannelBwQ(scpi_t * context);

scpi_result_t NR_CHPower_IntegrationBW(scpi_t * context);
scpi_result_t NR_CHPower_IntegrationBWQ(scpi_t * context);
scpi_result_t NR_CHPower_LimitPower(scpi_t * context);
scpi_result_t NR_CHPower_LimitPowerQ(scpi_t * context);
scpi_result_t NR_CHPower_LimitPowerValue(scpi_t * context);
scpi_result_t NR_CHPower_LimitPowerValueQ(scpi_t * context);
scpi_result_t NR_CHPower_LimitPsd(scpi_t * context);
scpi_result_t NR_CHPower_LimitPsdQ(scpi_t * context);
scpi_result_t NR_CHPower_LimitPsdValue(scpi_t * context);
scpi_result_t NR_CHPower_LimitPsdValueQ(scpi_t * context);
scpi_result_t NR_CHPower_CfgPreset(scpi_t * context);

scpi_result_t NR_OBWidth_Method(scpi_t * context);
scpi_result_t NR_OBWidth_MethodQ(scpi_t * context);
scpi_result_t NR_OBWidth_Percent(scpi_t * context);
scpi_result_t NR_OBWidth_PercentQ(scpi_t * context);
scpi_result_t NR_OBWidth_XdB(scpi_t * context);
scpi_result_t NR_OBWidth_XdBQ(scpi_t * context);
scpi_result_t NR_OBWidth_Limit(scpi_t * context);
scpi_result_t NR_OBWidth_LimitQ(scpi_t * context);
scpi_result_t NR_OBWidth_LimitValue(scpi_t * context);
scpi_result_t NR_OBWidth_LimitValueQ(scpi_t * context);
scpi_result_t NR_OBWidth_CfgPreset(scpi_t * context);

scpi_result_t NR_EIRPower_RxAntGain(scpi_t * context);
scpi_result_t NR_EIRPower_RxAntGainQ(scpi_t * context);
scpi_result_t NR_EIRPower_DistanceToAnt(scpi_t * context);
scpi_result_t NR_EIRPower_DistanceToAntQ(scpi_t * context);
scpi_result_t NR_EIRPower_DistanceUnit(scpi_t * context);
scpi_result_t NR_EIRPower_DistanceUnitQ(scpi_t * context);
scpi_result_t NR_EIRPower_UpperLimit(scpi_t * context);
scpi_result_t NR_EIRPower_UpperLimitQ(scpi_t * context);
scpi_result_t NR_EIRPower_UpperLimitValue(scpi_t * context);
scpi_result_t NR_EIRPower_UpperLimitValueQ(scpi_t * context);
scpi_result_t NR_EIRPower_LowerLimit(scpi_t * context);
scpi_result_t NR_EIRPower_LowerLimitQ(scpi_t * context);
scpi_result_t NR_EIRPower_LowerLimitValue(scpi_t * context);
scpi_result_t NR_EIRPower_LowerLimitValueQ(scpi_t * context);
scpi_result_t NR_EIRPower_RxCableLoss(scpi_t * context);
scpi_result_t NR_EIRPower_RxCableLossQ(scpi_t * context);
scpi_result_t NR_EIRPower_MaxHold(scpi_t * context);
scpi_result_t NR_EIRPower_CfgPreset(scpi_t * context);

scpi_result_t NR_BEAM_SSBSubCaSpac(scpi_t * context);
scpi_result_t NR_BEAM_SSBSubCaSpacQ(scpi_t * context);
scpi_result_t NR_BEAM_SSBOffset(scpi_t * context);
scpi_result_t NR_BEAM_SSBOffsetQ(scpi_t * context);
scpi_result_t NR_BEAM_SinrThreshold(scpi_t * context);
scpi_result_t NR_BEAM_SinrThresholdQ(scpi_t * context);
scpi_result_t NR_BEAM_ViewMode(scpi_t * context);
scpi_result_t NR_BEAM_ViewModeQ(scpi_t * context);

#ifdef  __cplusplus
}
#endif

#endif // NR_SCPI_MEAS_H
