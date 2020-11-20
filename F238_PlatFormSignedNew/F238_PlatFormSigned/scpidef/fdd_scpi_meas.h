#ifndef FDD_SCPI_MEAS_H
#define FDD_SCPI_MEAS_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FDD_SCPI_COMMANDS_MEASURE \
{"[:SENSe]:BANDWidth", FDD_ChannelBW},/*{double}*/\
{"[:SENSe]:SUBFrame", FDD_SubFrame},/*{int}*/\
{"[:SENSe]:CELLID:AUTO", FDD_CellID_Auto},/*{int}*/\
{"[:SENSe]:CELLID", FDD_CellID},/*{int}*/\
{"[:SENSe]:CYCLicprefix", FDD_CyclicPrefix},/*{int}*/\
{"[:SENSe]:ANTPort", FDD_AntPort},/*{int}*/\
{"[:SENSe]:PHICH:DURAtion", FDD_PhichDuration},/*{int}*/\
{"[:SENSe]:PHICH:NG", FDD_PhichNG},/*{int}*/\
{"[:SENSe]:MODULAtion:TYPE", FDD_ModulationType},/*{int}*/\
{"[:SENSe]:CFI:AUTO", FDD_CFI_Auto},/*{int}*/\
{"[:SENSe]:CFI", FDD_CFI},/*{int}*/\
{"[:SENSe]:RB:INDEx", FDD_RBIndex},/*{int}*/\
{"[:SENSe]:RB:SEARch:PMAXimum", FDD_SearchPMax},/*{none}*/\
{"[:SENSe]:RB:SEARch:PMINimum", FDD_SearchPMin},/*{none}*/\
{"[:SENSe]:RB:SEARch:MAXimum:PREVious", FDD_SearchMaxPrevious},/*{none}*/\
{"[:SENSe]:RB:SEARch:MAXimum:NEXT", FDD_SearchMaxNext},/*{none}*/\
{"[:SENSe]:CHPower:BANDwidth:INTegration", FDD_CHPower_IntegrationBW},/*{double}*/\
{"[:SENSe]:CHPower:LIMit:POWer:STATe", FDD_CHPower_PowerLimit},/*{int}*/\
{"[:SENSe]:CHPower:LIMit:POWer:VALue", FDD_CHPower_PowerLimitValue},/*{double}*/\
{"[:SENSe]:CHPower:LIMit:PSD:STATe", FDD_CHPower_PSDLimit},/*{int}*/\
{"[:SENSe]:CHPower:LIMit:PSD:VALue", FDD_CHPower_PSDLimitValue},/*{double}*/\
{"[:SENSe]:CHPower:PRESet", FDD_CHPower_Preset},/*{none}*/\
{"[:SENSe]:OBWidth:METHod", FDD_OBWidth_Method},/*{int}*/\
{"[:SENSe]:OBWidth:PERCent", FDD_OBWidth_Percent},/*{double}*/\
{"[:SENSe]:OBWidth:XDB", FDD_OBWidth_XdB},/*{double}*/\
{"[:SENSe]:OBWidth:LIMit:STATe", FDD_OBWidth_Limit},/*{int}*/\
{"[:SENSe]:OBWidth:LIMit:VALue", FDD_OBWidth_LimitValue},/*{double}*/\
{"[:SENSe]:OBWidth:PRESet", FDD_OBWidth_Preset},/*{none}*/\
{"[:SENSe]:FREQLIST:STATe", FDD_FreqList_State},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:1:FREQuency", FDD_FreqList1_AddFrequency},/*{double}*/\
{"[:SENSe]:FREQLIST:ADD:2:FREQuency", FDD_FreqList2_AddFrequency},/*{double}*/\
{"[:SENSe]:FREQLIST:ADD:3:FREQuency", FDD_FreqList3_AddFrequency},/*{double}*/\
{"[:SENSe]:FREQLIST:ADD:4:FREQuency", FDD_FreqList4_AddFrequency},/*{double}*/\
{"[:SENSe]:FREQLIST:ADD:5:FREQuency", FDD_FreqList5_AddFrequency},/*{double}*/\
{"[:SENSe]:FREQLIST:ADD:6:FREQuency", FDD_FreqList6_AddFrequency},/*{double}*/\
{"[:SENSe]:FREQLIST:ADD:1:CHANnel:NUMber", FDD_FreqList1_AddChannelNo},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:2:CHANnel:NUMber", FDD_FreqList2_AddChannelNo},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:3:CHANnel:NUMber", FDD_FreqList3_AddChannelNo},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:4:CHANnel:NUMber", FDD_FreqList4_AddChannelNo},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:5:CHANnel:NUMber", FDD_FreqList5_AddChannelNo},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:6:CHANnel:NUMber", FDD_FreqList6_AddChannelNo},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:1:CHANnel:STD", FDD_FreqList1_AddChannelStandard},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:2:CHANnel:STD", FDD_FreqList2_AddChannelStandard},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:3:CHANnel:STD", FDD_FreqList3_AddChannelStandard},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:4:CHANnel:STD", FDD_FreqList4_AddChannelStandard},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:5:CHANnel:STD", FDD_FreqList5_AddChannelStandard},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:6:CHANnel:STD", FDD_FreqList6_AddChannelStandard},/*{int}*/\
{"[:SENSe]:MAPping:PLOT", FDD_Mapping_Plot},/*{int}*/\
{"[:SENSe]:MAPping:PLOT:ITEM", FDD_Mapping_PlotItem},/*{int}*/\
{"[:SENSe]:MAPping:PANNAVIgate", FDD_Mapping_PanNavigate},/*{int}*/\
{"[:SENSe]:MAPping:PLOT:TABle", FDD_Mapping_PlotTable},/*{int}*/\
{"[:SENSe]:CC:SELEct", FDD_CC_Select},/*{int}*/\
{"[:SENSe]:CC:ACTive", FDD_CC_Active},/*{int}*/\
{"[:SENSe]:CC:1:ACTive", FDD_CC1_Active},/*{int}*/\
{"[:SENSe]:CC:2:ACTive", FDD_CC2_Active},/*{int}*/\
{"[:SENSe]:CC:3:ACTive", FDD_CC3_Active},/*{int}*/\
{"[:SENSe]:CC:4:ACTive", FDD_CC4_Active},/*{int}*/\
{"[:SENSe]:CC:5:ACTive", FDD_CC5_Active},/*{int}*/\
{"[:SENSe]:CC:FREQuency", FDD_CC_CenterFrequency},/*{double}*/\
{"[:SENSe]:CC:1:FREQuency", FDD_CC1_CenterFrequency},/*{double}*/\
{"[:SENSe]:CC:2:FREQuency", FDD_CC2_CenterFrequency},/*{double}*/\
{"[:SENSe]:CC:3:FREQuency", FDD_CC3_CenterFrequency},/*{double}*/\
{"[:SENSe]:CC:4:FREQuency", FDD_CC4_CenterFrequency},/*{double}*/\
{"[:SENSe]:CC:5:FREQuency", FDD_CC5_CenterFrequency},/*{double}*/\
{"[:SENSe]:CC:BANDWidth", FDD_CC_BandWidth},/*{double}*/\
{"[:SENSe]:CC:1:BANDWidth", FDD_CC1_BandWidth},/*{double}*/\
{"[:SENSe]:CC:2:BANDWidth", FDD_CC2_BandWidth},/*{double}*/\
{"[:SENSe]:CC:3:BANDWidth", FDD_CC3_BandWidth},/*{double}*/\
{"[:SENSe]:CC:4:BANDWidth", FDD_CC4_BandWidth},/*{double}*/\
{"[:SENSe]:CC:5:BANDWidth", FDD_CC5_BandWidth},/*{double}*/\
{"[:SENSe]:CC:PHICH:DURAtion", FDD_CC_PhichDuration},/*{int}*/\
{"[:SENSe]:CC:1:PHICH:DURAtion", FDD_CC1_PhichDuration},/*{int}*/\
{"[:SENSe]:CC:2:PHICH:DURAtion", FDD_CC2_PhichDuration},/*{int}*/\
{"[:SENSe]:CC:3:PHICH:DURAtion", FDD_CC3_PhichDuration},/*{int}*/\
{"[:SENSe]:CC:4:PHICH:DURAtion", FDD_CC4_PhichDuration},/*{int}*/\
{"[:SENSe]:CC:5:PHICH:DURAtion", FDD_CC5_PhichDuration},/*{int}*/\
{"[:SENSe]:CC:PHICH:NG", FDD_CC_PhichNG},/*{int}*/\
{"[:SENSe]:CC:1:PHICH:NG", FDD_CC1_PhichNG},/*{int}*/\
{"[:SENSe]:CC:2:PHICH:NG", FDD_CC2_PhichNG},/*{int}*/\
{"[:SENSe]:CC:3:PHICH:NG", FDD_CC3_PhichNG},/*{int}*/\
{"[:SENSe]:CC:4:PHICH:NG", FDD_CC4_PhichNG},/*{int}*/\
{"[:SENSe]:CC:5:PHICH:NG", FDD_CC5_PhichNG},/*{int}*/\
{"[:SENSe]:CC:CYCLicprefix", FDD_CC_CyclicPrefix},/*{int}*/\
{"[:SENSe]:CC:1:CYCLicprefix", FDD_CC1_CyclicPrefix},/*{int}*/\
{"[:SENSe]:CC:2:CYCLicprefix", FDD_CC2_CyclicPrefix},/*{int}*/\
{"[:SENSe]:CC:3:CYCLicprefix", FDD_CC3_CyclicPrefix},/*{int}*/\
{"[:SENSe]:CC:4:CYCLicprefix", FDD_CC4_CyclicPrefix},/*{int}*/\
{"[:SENSe]:CC:5:CYCLicprefix", FDD_CC5_CyclicPrefix},/*{int}*/\
{"[:SENSe]:CC:ANTPort", FDD_CC_AntPort},/*{int}*/\
{"[:SENSe]:CC:1:ANTPort", FDD_CC1_AntPort},/*{int}*/\
{"[:SENSe]:CC:2:ANTPort", FDD_CC2_AntPort},/*{int}*/\
{"[:SENSe]:CC:3:ANTPort", FDD_CC3_AntPort},/*{int}*/\
{"[:SENSe]:CC:4:ANTPort", FDD_CC4_AntPort},/*{int}*/\
{"[:SENSe]:CC:5:ANTPort", FDD_CC5_AntPort},/*{int}*/\
{"[:SENSe]:DAM:COLORMap:SCALe:AUTO", FDD_DAM_ColorMap_AutoScale},/*{none}*/\
{"[:SENSe]:DAM:COLORMap:MAXValue", FDD_DAM_ColorMap_MaxValue},/*{double}*/\
{"[:SENSe]:DAM:COLORMap:RANGe", FDD_DAM_ColorMap_Range},/*{double}*/\
{"[:SENSe]:DATAGRam:COLORMap:SCALe:AUTO", FDD_DataGram_ColorMap_AutoScale},/*{none}*/\
{"[:SENSe]:DATAGRam:COLORMap:MAXValue", FDD_DataGram_ColorMap_MaxValue},/*{double}*/\
{"[:SENSe]:DATAGRam:COLORMap:RANGe", FDD_DataGram_ColorMap_Range},/*{double}*/\
{"[:SENSe]:FDD:MEASure:MODE", FDD_Measure_Mode},/*{int}*/\
\
{"[:SENSe]:BANDWidth?", FDD_ChannelBWQ},/*{double}*/\
{"[:SENSe]:SUBFrame?", FDD_SubFrameQ},/*{int}*/\
{"[:SENSe]:CELLID:AUTO?", FDD_CellID_AutoQ},/*{int}*/\
{"[:SENSe]:CELLID?", FDD_CellIDQ},/*{int}*/\
{"[:SENSe]:CYCLicprefix?", FDD_CyclicPrefixQ},/*{int}*/\
{"[:SENSe]:ANTPort?", FDD_AntPortQ},/*{int}*/\
{"[:SENSe]:PHICH:DURAtion?", FDD_PhichDurationQ},/*{int}*/\
{"[:SENSe]:PHICH:NG?", FDD_PhichNGQ},/*{int}*/\
{"[:SENSe]:MODULAtion:TYPE?", FDD_ModulationTypeQ},/*{int}*/\
{"[:SENSe]:CFI:AUTO?", FDD_CFI_AutoQ},/*{int}*/\
{"[:SENSe]:CFI?", FDD_CFIQ},/*{int}*/\
{"[:SENSe]:RB:INDEx?", FDD_RBIndexQ},/*{int}*/\
{"[:SENSe]:CHPower:BANDwidth:INTegration?", FDD_CHPower_IntegrationBWQ},/*{double}*/\
{"[:SENSe]:CHPower:LIMit:POWer:STATe?", FDD_CHPower_PowerLimitQ},/*{int}*/\
{"[:SENSe]:CHPower:LIMit:POWer:VALue?", FDD_CHPower_PowerLimitValueQ},/*{double}*/\
{"[:SENSe]:CHPower:LIMit:PSD:STATe?", FDD_CHPower_PSDLimitQ},/*{int}*/\
{"[:SENSe]:CHPower:LIMit:PSD:VALue?", FDD_CHPower_PSDLimitValueQ},/*{double}*/\
{"[:SENSe]:OBWidth:METHod?", FDD_OBWidth_MethodQ},/*{int}*/\
{"[:SENSe]:OBWidth:PERCent?", FDD_OBWidth_PercentQ},/*{double}*/\
{"[:SENSe]:OBWidth:XDB?", FDD_OBWidth_XdBQ},/*{double}*/\
{"[:SENSe]:OBWidth:LIMit:STATe?", FDD_OBWidth_LimitQ},/*{int}*/\
{"[:SENSe]:OBWidth:LIMit:VALue?", FDD_OBWidth_LimitValueQ},/*{double}*/\
{"[:SENSe]:FREQLIST:ADD:1:FREQuency?", FDD_FreqList1_AddFrequencyQ},/*{double}*/\
{"[:SENSe]:FREQLIST:ADD:2:FREQuency?", FDD_FreqList2_AddFrequencyQ},/*{double}*/\
{"[:SENSe]:FREQLIST:ADD:3:FREQuency?", FDD_FreqList3_AddFrequencyQ},/*{double}*/\
{"[:SENSe]:FREQLIST:ADD:4:FREQuency?", FDD_FreqList4_AddFrequencyQ},/*{double}*/\
{"[:SENSe]:FREQLIST:ADD:5:FREQuency?", FDD_FreqList5_AddFrequencyQ},/*{double}*/\
{"[:SENSe]:FREQLIST:ADD:6:FREQuency?", FDD_FreqList6_AddFrequencyQ},/*{double}*/\
{"[:SENSe]:FREQLIST:ADD:1:CHANnel:NUMber?", FDD_FreqList1_AddChannelNoQ},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:2:CHANnel:NUMber?", FDD_FreqList2_AddChannelNoQ},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:3:CHANnel:NUMber?", FDD_FreqList3_AddChannelNoQ},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:4:CHANnel:NUMber?", FDD_FreqList4_AddChannelNoQ},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:5:CHANnel:NUMber?", FDD_FreqList5_AddChannelNoQ},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:6:CHANnel:NUMber?", FDD_FreqList6_AddChannelNoQ},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:1:CHANnel:STD?", FDD_FreqList1_AddChannelStandardQ},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:2:CHANnel:STD?", FDD_FreqList2_AddChannelStandardQ},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:3:CHANnel:STD?", FDD_FreqList3_AddChannelStandardQ},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:4:CHANnel:STD?", FDD_FreqList4_AddChannelStandardQ},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:5:CHANnel:STD?", FDD_FreqList5_AddChannelStandardQ},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:6:CHANnel:STD?", FDD_FreqList6_AddChannelStandardQ},/*{int}*/\
{"[:SENSe]:MAPping:PLOT?", FDD_Mapping_PlotQ},/*{int}*/\
{"[:SENSe]:MAPping:PLOT:ITEM?", FDD_Mapping_PlotItemQ},/*{int}*/\
{"[:SENSe]:MAPping:PANNAVIgate?", FDD_Mapping_PanNavigateQ},/*{int}*/\
{"[:SENSe]:MAPping:PLOT:TABle?", FDD_Mapping_PlotTableQ},/*{int}*/\
{"[:SENSe]:CC:SELEct?", FDD_CC_SelectQ},/*{int}*/\
{"[:SENSe]:CC:ACTive?", FDD_CC_ActiveQ},/*{int}*/\
{"[:SENSe]:CC:1:ACTive?", FDD_CC1_ActiveQ},/*{int}*/\
{"[:SENSe]:CC:2:ACTive?", FDD_CC2_ActiveQ},/*{int}*/\
{"[:SENSe]:CC:3:ACTive?", FDD_CC3_ActiveQ},/*{int}*/\
{"[:SENSe]:CC:4:ACTive?", FDD_CC4_ActiveQ},/*{int}*/\
{"[:SENSe]:CC:5:ACTive?", FDD_CC5_ActiveQ},/*{int}*/\
{"[:SENSe]:CC:FREQuency?", FDD_CC_CenterFrequencyQ},/*{double}*/\
{"[:SENSe]:CC:1:FREQuency?", FDD_CC1_CenterFrequencyQ},/*{double}*/\
{"[:SENSe]:CC:2:FREQuency?", FDD_CC2_CenterFrequencyQ},/*{double}*/\
{"[:SENSe]:CC:3:FREQuency?", FDD_CC3_CenterFrequencyQ},/*{double}*/\
{"[:SENSe]:CC:4:FREQuency?", FDD_CC4_CenterFrequencyQ},/*{double}*/\
{"[:SENSe]:CC:5:FREQuency?", FDD_CC5_CenterFrequencyQ},/*{double}*/\
{"[:SENSe]:CC:BANDWidth?", FDD_CC_BandWidthQ},/*{double}*/\
{"[:SENSe]:CC:1:BANDWidth?", FDD_CC1_BandWidthQ},/*{double}*/\
{"[:SENSe]:CC:2:BANDWidth?", FDD_CC2_BandWidthQ},/*{double}*/\
{"[:SENSe]:CC:3:BANDWidth?", FDD_CC3_BandWidthQ},/*{double}*/\
{"[:SENSe]:CC:4:BANDWidth?", FDD_CC4_BandWidthQ},/*{double}*/\
{"[:SENSe]:CC:5:BANDWidth?", FDD_CC5_BandWidthQ},/*{double}*/\
{"[:SENSe]:CC:PHICH:DURAtion?", FDD_CC_PhichDurationQ},/*{int}*/\
{"[:SENSe]:CC:1:PHICH:DURAtion?", FDD_CC1_PhichDurationQ},/*{int}*/\
{"[:SENSe]:CC:2:PHICH:DURAtion?", FDD_CC2_PhichDurationQ},/*{int}*/\
{"[:SENSe]:CC:3:PHICH:DURAtion?", FDD_CC3_PhichDurationQ},/*{int}*/\
{"[:SENSe]:CC:4:PHICH:DURAtion?", FDD_CC4_PhichDurationQ},/*{int}*/\
{"[:SENSe]:CC:5:PHICH:DURAtion?", FDD_CC5_PhichDurationQ},/*{int}*/\
{"[:SENSe]:CC:PHICH:NG?", FDD_CC_PhichNGQ},/*{int}*/\
{"[:SENSe]:CC:1:PHICH:NG?", FDD_CC1_PhichNGQ},/*{int}*/\
{"[:SENSe]:CC:2:PHICH:NG?", FDD_CC2_PhichNGQ},/*{int}*/\
{"[:SENSe]:CC:3:PHICH:NG?", FDD_CC3_PhichNGQ},/*{int}*/\
{"[:SENSe]:CC:4:PHICH:NG?", FDD_CC4_PhichNGQ},/*{int}*/\
{"[:SENSe]:CC:5:PHICH:NG?", FDD_CC5_PhichNGQ},/*{int}*/\
{"[:SENSe]:CC:CYCLicprefix?", FDD_CC_CyclicPrefixQ},/*{int}*/\
{"[:SENSe]:CC:1:CYCLicprefix?", FDD_CC1_CyclicPrefixQ},/*{int}*/\
{"[:SENSe]:CC:2:CYCLicprefix?", FDD_CC2_CyclicPrefixQ},/*{int}*/\
{"[:SENSe]:CC:3:CYCLicprefix?", FDD_CC3_CyclicPrefixQ},/*{int}*/\
{"[:SENSe]:CC:4:CYCLicprefix?", FDD_CC4_CyclicPrefixQ},/*{int}*/\
{"[:SENSe]:CC:5:CYCLicprefix?", FDD_CC5_CyclicPrefixQ},/*{int}*/\
{"[:SENSe]:CC:ANTPort?", FDD_CC_AntPortQ},/*{int}*/\
{"[:SENSe]:CC:1:ANTPort?", FDD_CC1_AntPortQ},/*{int}*/\
{"[:SENSe]:CC:2:ANTPort?", FDD_CC2_AntPortQ},/*{int}*/\
{"[:SENSe]:CC:3:ANTPort?", FDD_CC3_AntPortQ},/*{int}*/\
{"[:SENSe]:CC:4:ANTPort?", FDD_CC4_AntPortQ},/*{int}*/\
{"[:SENSe]:CC:5:ANTPort?", FDD_CC5_AntPortQ},/*{int}*/\
{"[:SENSe]:DAM:COLORMap:MAXValue?", FDD_DAM_ColorMap_MaxValueQ},/*{double}*/\
{"[:SENSe]:DAM:COLORMap:RANGe?", FDD_DAM_ColorMap_RangeQ},/*{double}*/\
{"[:SENSe]:DATAGRam:COLORMap:MAXValue?", FDD_DataGram_ColorMap_MaxValueQ},/*{double}*/\
{"[:SENSe]:DATAGRam:COLORMap:RANGe?", FDD_DataGram_ColorMap_RangeQ},/*{double}*/\
{"[:SENSe]:FDD:MEASure:MODE?", FDD_Measure_ModeQ},/*{int}*/\

scpi_result_t FDD_ChannelBW(scpi_t * context);
scpi_result_t FDD_SubFrame(scpi_t * context);
scpi_result_t FDD_CellID_Auto(scpi_t * context);
scpi_result_t FDD_CellID(scpi_t * context);
scpi_result_t FDD_CyclicPrefix(scpi_t * context);
scpi_result_t FDD_AntPort(scpi_t * context);
scpi_result_t FDD_PhichDuration(scpi_t * context);
scpi_result_t FDD_PhichNG(scpi_t * context);
scpi_result_t FDD_ModulationType(scpi_t * context);
scpi_result_t FDD_CFI_Auto(scpi_t * context);
scpi_result_t FDD_CFI(scpi_t * context);
scpi_result_t FDD_RBIndex(scpi_t * context);
scpi_result_t FDD_SearchPMax(scpi_t * context);
scpi_result_t FDD_SearchPMin(scpi_t * context);
scpi_result_t FDD_SearchMaxPrevious(scpi_t * context);
scpi_result_t FDD_SearchMaxNext(scpi_t * context);
scpi_result_t FDD_CHPower_IntegrationBW(scpi_t * context);
scpi_result_t FDD_CHPower_PowerLimit(scpi_t * context);
scpi_result_t FDD_CHPower_PowerLimitValue(scpi_t * context);
scpi_result_t FDD_CHPower_PSDLimit(scpi_t * context);
scpi_result_t FDD_CHPower_PSDLimitValue(scpi_t * context);
scpi_result_t FDD_CHPower_Preset(scpi_t * context);
scpi_result_t FDD_OBWidth_Method(scpi_t * context);
scpi_result_t FDD_OBWidth_Percent(scpi_t * context);
scpi_result_t FDD_OBWidth_XdB(scpi_t * context);
scpi_result_t FDD_OBWidth_Limit(scpi_t * context);
scpi_result_t FDD_OBWidth_LimitValue(scpi_t * context);
scpi_result_t FDD_OBWidth_Preset(scpi_t * context);
scpi_result_t FDD_FreqList_State(scpi_t * context);
scpi_result_t FDD_FreqList1_AddFrequency(scpi_t * context);
scpi_result_t FDD_FreqList2_AddFrequency(scpi_t * context);
scpi_result_t FDD_FreqList3_AddFrequency(scpi_t * context);
scpi_result_t FDD_FreqList4_AddFrequency(scpi_t * context);
scpi_result_t FDD_FreqList5_AddFrequency(scpi_t * context);
scpi_result_t FDD_FreqList6_AddFrequency(scpi_t * context);
scpi_result_t FDD_FreqList1_AddChannelNo(scpi_t * context);
scpi_result_t FDD_FreqList2_AddChannelNo(scpi_t * context);
scpi_result_t FDD_FreqList3_AddChannelNo(scpi_t * context);
scpi_result_t FDD_FreqList4_AddChannelNo(scpi_t * context);
scpi_result_t FDD_FreqList5_AddChannelNo(scpi_t * context);
scpi_result_t FDD_FreqList6_AddChannelNo(scpi_t * context);
scpi_result_t FDD_FreqList1_AddChannelStandard(scpi_t * context);
scpi_result_t FDD_FreqList2_AddChannelStandard(scpi_t * context);
scpi_result_t FDD_FreqList3_AddChannelStandard(scpi_t * context);
scpi_result_t FDD_FreqList4_AddChannelStandard(scpi_t * context);
scpi_result_t FDD_FreqList5_AddChannelStandard(scpi_t * context);
scpi_result_t FDD_FreqList6_AddChannelStandard(scpi_t * context);
scpi_result_t FDD_Mapping_Plot(scpi_t * context);
scpi_result_t FDD_Mapping_PlotItem(scpi_t * context);
scpi_result_t FDD_Mapping_PanNavigate(scpi_t * context);
scpi_result_t FDD_Mapping_PlotTable(scpi_t * context);
scpi_result_t FDD_CC_Select(scpi_t * context);
scpi_result_t FDD_CC_Active(scpi_t * context);
scpi_result_t FDD_CC1_Active(scpi_t * context);
scpi_result_t FDD_CC2_Active(scpi_t * context);
scpi_result_t FDD_CC3_Active(scpi_t * context);
scpi_result_t FDD_CC4_Active(scpi_t * context);
scpi_result_t FDD_CC5_Active(scpi_t * context);
scpi_result_t FDD_CC_CenterFrequency(scpi_t * context);
scpi_result_t FDD_CC1_CenterFrequency(scpi_t * context);
scpi_result_t FDD_CC2_CenterFrequency(scpi_t * context);
scpi_result_t FDD_CC3_CenterFrequency(scpi_t * context);
scpi_result_t FDD_CC4_CenterFrequency(scpi_t * context);
scpi_result_t FDD_CC5_CenterFrequency(scpi_t * context);
scpi_result_t FDD_CC_BandWidth(scpi_t * context);
scpi_result_t FDD_CC1_BandWidth(scpi_t * context);
scpi_result_t FDD_CC2_BandWidth(scpi_t * context);
scpi_result_t FDD_CC3_BandWidth(scpi_t * context);
scpi_result_t FDD_CC4_BandWidth(scpi_t * context);
scpi_result_t FDD_CC5_BandWidth(scpi_t * context);
scpi_result_t FDD_CC_PhichDuration(scpi_t * context);
scpi_result_t FDD_CC1_PhichDuration(scpi_t * context);
scpi_result_t FDD_CC2_PhichDuration(scpi_t * context);
scpi_result_t FDD_CC3_PhichDuration(scpi_t * context);
scpi_result_t FDD_CC4_PhichDuration(scpi_t * context);
scpi_result_t FDD_CC5_PhichDuration(scpi_t * context);
scpi_result_t FDD_CC_PhichNG(scpi_t * context);
scpi_result_t FDD_CC1_PhichNG(scpi_t * context);
scpi_result_t FDD_CC2_PhichNG(scpi_t * context);
scpi_result_t FDD_CC3_PhichNG(scpi_t * context);
scpi_result_t FDD_CC4_PhichNG(scpi_t * context);
scpi_result_t FDD_CC5_PhichNG(scpi_t * context);
scpi_result_t FDD_CC_CyclicPrefix(scpi_t * context);
scpi_result_t FDD_CC1_CyclicPrefix(scpi_t * context);
scpi_result_t FDD_CC2_CyclicPrefix(scpi_t * context);
scpi_result_t FDD_CC3_CyclicPrefix(scpi_t * context);
scpi_result_t FDD_CC4_CyclicPrefix(scpi_t * context);
scpi_result_t FDD_CC5_CyclicPrefix(scpi_t * context);
scpi_result_t FDD_CC_AntPort(scpi_t * context);
scpi_result_t FDD_CC1_AntPort(scpi_t * context);
scpi_result_t FDD_CC2_AntPort(scpi_t * context);
scpi_result_t FDD_CC3_AntPort(scpi_t * context);
scpi_result_t FDD_CC4_AntPort(scpi_t * context);
scpi_result_t FDD_CC5_AntPort(scpi_t * context);
scpi_result_t FDD_DAM_ColorMap_AutoScale(scpi_t * context);
scpi_result_t FDD_DAM_ColorMap_MaxValue(scpi_t * context);
scpi_result_t FDD_DAM_ColorMap_Range(scpi_t * context);
scpi_result_t FDD_DataGram_ColorMap_AutoScale(scpi_t * context);
scpi_result_t FDD_DataGram_ColorMap_MaxValue(scpi_t * context);
scpi_result_t FDD_DataGram_ColorMap_Range(scpi_t * context);
scpi_result_t FDD_Measure_Mode(scpi_t * context);

scpi_result_t FDD_ChannelBWQ(scpi_t * context);
scpi_result_t FDD_SubFrameQ(scpi_t * context);
scpi_result_t FDD_CellID_AutoQ(scpi_t * context);
scpi_result_t FDD_CellIDQ(scpi_t * context);
scpi_result_t FDD_CyclicPrefixQ(scpi_t * context);
scpi_result_t FDD_AntPortQ(scpi_t * context);
scpi_result_t FDD_PhichDurationQ(scpi_t * context);
scpi_result_t FDD_PhichNGQ(scpi_t * context);
scpi_result_t FDD_ModulationTypeQ(scpi_t * context);
scpi_result_t FDD_CFI_AutoQ(scpi_t * context);
scpi_result_t FDD_CFIQ(scpi_t * context);
scpi_result_t FDD_RBIndexQ(scpi_t * context);
scpi_result_t FDD_CHPower_IntegrationBWQ(scpi_t * context);
scpi_result_t FDD_CHPower_PowerLimitQ(scpi_t * context);
scpi_result_t FDD_CHPower_PowerLimitValueQ(scpi_t * context);
scpi_result_t FDD_CHPower_PSDLimitQ(scpi_t * context);
scpi_result_t FDD_CHPower_PSDLimitValueQ(scpi_t * context);
scpi_result_t FDD_OBWidth_MethodQ(scpi_t * context);
scpi_result_t FDD_OBWidth_PercentQ(scpi_t * context);
scpi_result_t FDD_OBWidth_XdBQ(scpi_t * context);
scpi_result_t FDD_OBWidth_LimitQ(scpi_t * context);
scpi_result_t FDD_OBWidth_LimitValueQ(scpi_t * context);
scpi_result_t FDD_FreqList1_AddFrequencyQ(scpi_t * context);
scpi_result_t FDD_FreqList2_AddFrequencyQ(scpi_t * context);
scpi_result_t FDD_FreqList3_AddFrequencyQ(scpi_t * context);
scpi_result_t FDD_FreqList4_AddFrequencyQ(scpi_t * context);
scpi_result_t FDD_FreqList5_AddFrequencyQ(scpi_t * context);
scpi_result_t FDD_FreqList6_AddFrequencyQ(scpi_t * context);
scpi_result_t FDD_FreqList1_AddChannelNoQ(scpi_t * context);
scpi_result_t FDD_FreqList2_AddChannelNoQ(scpi_t * context);
scpi_result_t FDD_FreqList3_AddChannelNoQ(scpi_t * context);
scpi_result_t FDD_FreqList4_AddChannelNoQ(scpi_t * context);
scpi_result_t FDD_FreqList5_AddChannelNoQ(scpi_t * context);
scpi_result_t FDD_FreqList6_AddChannelNoQ(scpi_t * context);
scpi_result_t FDD_FreqList1_AddChannelStandardQ(scpi_t * context);
scpi_result_t FDD_FreqList2_AddChannelStandardQ(scpi_t * context);
scpi_result_t FDD_FreqList3_AddChannelStandardQ(scpi_t * context);
scpi_result_t FDD_FreqList4_AddChannelStandardQ(scpi_t * context);
scpi_result_t FDD_FreqList5_AddChannelStandardQ(scpi_t * context);
scpi_result_t FDD_FreqList6_AddChannelStandardQ(scpi_t * context);
scpi_result_t FDD_Mapping_PlotQ(scpi_t * context);
scpi_result_t FDD_Mapping_PlotItemQ(scpi_t * context);
scpi_result_t FDD_Mapping_PanNavigateQ(scpi_t * context);
scpi_result_t FDD_Mapping_PlotTableQ(scpi_t * context);
scpi_result_t FDD_CC_SelectQ(scpi_t * context);
scpi_result_t FDD_CC_ActiveQ(scpi_t * context);
scpi_result_t FDD_CC1_ActiveQ(scpi_t * context);
scpi_result_t FDD_CC2_ActiveQ(scpi_t * context);
scpi_result_t FDD_CC3_ActiveQ(scpi_t * context);
scpi_result_t FDD_CC4_ActiveQ(scpi_t * context);
scpi_result_t FDD_CC5_ActiveQ(scpi_t * context);
scpi_result_t FDD_CC_CenterFrequencyQ(scpi_t * context);
scpi_result_t FDD_CC1_CenterFrequencyQ(scpi_t * context);
scpi_result_t FDD_CC2_CenterFrequencyQ(scpi_t * context);
scpi_result_t FDD_CC3_CenterFrequencyQ(scpi_t * context);
scpi_result_t FDD_CC4_CenterFrequencyQ(scpi_t * context);
scpi_result_t FDD_CC5_CenterFrequencyQ(scpi_t * context);
scpi_result_t FDD_CC_BandWidthQ(scpi_t * context);
scpi_result_t FDD_CC1_BandWidthQ(scpi_t * context);
scpi_result_t FDD_CC2_BandWidthQ(scpi_t * context);
scpi_result_t FDD_CC3_BandWidthQ(scpi_t * context);
scpi_result_t FDD_CC4_BandWidthQ(scpi_t * context);
scpi_result_t FDD_CC5_BandWidthQ(scpi_t * context);
scpi_result_t FDD_CC_PhichDurationQ(scpi_t * context);
scpi_result_t FDD_CC1_PhichDurationQ(scpi_t * context);
scpi_result_t FDD_CC2_PhichDurationQ(scpi_t * context);
scpi_result_t FDD_CC3_PhichDurationQ(scpi_t * context);
scpi_result_t FDD_CC4_PhichDurationQ(scpi_t * context);
scpi_result_t FDD_CC5_PhichDurationQ(scpi_t * context);
scpi_result_t FDD_CC_PhichNGQ(scpi_t * context);
scpi_result_t FDD_CC1_PhichNGQ(scpi_t * context);
scpi_result_t FDD_CC2_PhichNGQ(scpi_t * context);
scpi_result_t FDD_CC3_PhichNGQ(scpi_t * context);
scpi_result_t FDD_CC4_PhichNGQ(scpi_t * context);
scpi_result_t FDD_CC5_PhichNGQ(scpi_t * context);
scpi_result_t FDD_CC_CyclicPrefixQ(scpi_t * context);
scpi_result_t FDD_CC1_CyclicPrefixQ(scpi_t * context);
scpi_result_t FDD_CC2_CyclicPrefixQ(scpi_t * context);
scpi_result_t FDD_CC3_CyclicPrefixQ(scpi_t * context);
scpi_result_t FDD_CC4_CyclicPrefixQ(scpi_t * context);
scpi_result_t FDD_CC5_CyclicPrefixQ(scpi_t * context);
scpi_result_t FDD_CC_AntPortQ(scpi_t * context);
scpi_result_t FDD_CC1_AntPortQ(scpi_t * context);
scpi_result_t FDD_CC2_AntPortQ(scpi_t * context);
scpi_result_t FDD_CC3_AntPortQ(scpi_t * context);
scpi_result_t FDD_CC4_AntPortQ(scpi_t * context);
scpi_result_t FDD_CC5_AntPortQ(scpi_t * context);
scpi_result_t FDD_DAM_ColorMap_MaxValueQ(scpi_t * context);
scpi_result_t FDD_DAM_ColorMap_RangeQ(scpi_t * context);
scpi_result_t FDD_DataGram_ColorMap_MaxValueQ(scpi_t * context);
scpi_result_t FDD_DataGram_ColorMap_RangeQ(scpi_t * context);
scpi_result_t FDD_Measure_ModeQ(scpi_t * context);

#ifdef __cplusplus
}
#endif

#endif // FDD_SCPI_MEAS_H
