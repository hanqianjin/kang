#ifndef TDD_SCPI_MEAS_H
#define TDD_SCPI_MEAS_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TDD_SCPI_COMMANDS_MEASURE \
{"[:SENSe]:BANDWidth", TDD_ChannelBW},/*{double}*/\
{"[:SENSe]:SUBFrame", TDD_SubFrame},/*{int}*/\
{"[:SENSe]:CELLID:AUTO", TDD_CellID_Auto},/*{int}*/\
{"[:SENSe]:CELLID", TDD_CellID},/*{int}*/\
{"[:SENSe]:CYCLicprefix", TDD_CyclicPrefix},/*{int}*/\
{"[:SENSe]:ANTPort", TDD_AntPort},/*{int}*/\
{"[:SENSe]:PHICH:DURAtion", TDD_PhichDuration},/*{int}*/\
{"[:SENSe]:PHICH:NG", TDD_PhichNG},/*{int}*/\
{"[:SENSe]:MODULAtion:TYPE", TDD_ModulationType},/*{int}*/\
{"[:SENSe]:CFI:AUTO", TDD_CFI_Auto},/*{int}*/\
{"[:SENSe]:CFI", TDD_CFI},/*{int}*/\
{"[:SENSe]:RB:INDEx", TDD_RBIndex},/*{int}*/\
{"[:SENSe]:RB:SEARch:PMAXimum", TDD_SearchPMax},/*{none}*/\
{"[:SENSe]:RB:SEARch:PMINimum", TDD_SearchPMin},/*{none}*/\
{"[:SENSe]:RB:SEARch:MAXimum:PREVious", TDD_SearchMaxPrevious},/*{none}*/\
{"[:SENSe]:RB:SEARch:MAXimum:NEXT", TDD_SearchMaxNext},/*{none}*/\
{"[:SENSe]:SUBFrame:UPDOwn", TDD_SubFrame_UpDown},/*{int}*/\
{"[:SENSe]:SUBFrame:SPECial", TDD_SubFrame_Special},/*{int}*/\
{"[:SENSe]:CHPower:BANDwidth:INTegration", TDD_CHPower_IntegrationBW},/*{double}*/\
{"[:SENSe]:CHPower:LIMit:POWer:STATe", TDD_CHPower_PowerLimit},/*{int}*/\
{"[:SENSe]:CHPower:LIMit:POWer:VALue", TDD_CHPower_PowerLimitValue},/*{double}*/\
{"[:SENSe]:CHPower:LIMit:PSD:STATe", TDD_CHPower_PSDLimit},/*{int}*/\
{"[:SENSe]:CHPower:LIMit:PSD:VALue", TDD_CHPower_PSDLimitValue},/*{double}*/\
{"[:SENSe]:CHPower:PRESet", TDD_CHPower_Preset},/*{none}*/\
{"[:SENSe]:OBWidth:METHod", TDD_OBWidth_Method},/*{int}*/\
{"[:SENSe]:OBWidth:PERCent", TDD_OBWidth_Percent},/*{double}*/\
{"[:SENSe]:OBWidth:XDB", TDD_OBWidth_XdB},/*{double}*/\
{"[:SENSe]:OBWidth:LIMit:STATe", TDD_OBWidth_Limit},/*{int}*/\
{"[:SENSe]:OBWidth:LIMit:VALue", TDD_OBWidth_LimitValue},/*{double}*/\
{"[:SENSe]:OBWidth:PRESet", TDD_OBWidth_Preset},/*{none}*/\
{"[:SENSe]:TAE:TIME:REFerence", TDD_TAE_ReferenceTime},/*{double}*/\
{"[:SENSe]:TAE:TIME:SCALe", TDD_TAE_ScaleTime},/*{double}*/\
{"[:SENSe]:FREQLIST:STATe", TDD_FreqList_State},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:1:FREQuency", TDD_FreqList1_AddFrequency},/*{double}*/\
{"[:SENSe]:FREQLIST:ADD:2:FREQuency", TDD_FreqList2_AddFrequency},/*{double}*/\
{"[:SENSe]:FREQLIST:ADD:3:FREQuency", TDD_FreqList3_AddFrequency},/*{double}*/\
{"[:SENSe]:FREQLIST:ADD:4:FREQuency", TDD_FreqList4_AddFrequency},/*{double}*/\
{"[:SENSe]:FREQLIST:ADD:5:FREQuency", TDD_FreqList5_AddFrequency},/*{double}*/\
{"[:SENSe]:FREQLIST:ADD:6:FREQuency", TDD_FreqList6_AddFrequency},/*{double}*/\
{"[:SENSe]:FREQLIST:ADD:1:CHANnel:NUMber", TDD_FreqList1_AddChannelNo},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:2:CHANnel:NUMber", TDD_FreqList2_AddChannelNo},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:3:CHANnel:NUMber", TDD_FreqList3_AddChannelNo},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:4:CHANnel:NUMber", TDD_FreqList4_AddChannelNo},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:5:CHANnel:NUMber", TDD_FreqList5_AddChannelNo},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:6:CHANnel:NUMber", TDD_FreqList6_AddChannelNo},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:1:CHANnel:STD", TDD_FreqList1_AddChannelStandard},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:2:CHANnel:STD", TDD_FreqList2_AddChannelStandard},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:3:CHANnel:STD", TDD_FreqList3_AddChannelStandard},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:4:CHANnel:STD", TDD_FreqList4_AddChannelStandard},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:5:CHANnel:STD", TDD_FreqList5_AddChannelStandard},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:6:CHANnel:STD", TDD_FreqList6_AddChannelStandard},/*{int}*/\
{"[:SENSe]:MAPping:PLOT", TDD_Mapping_Plot},/*{int}*/\
{"[:SENSe]:MAPping:PLOT:ITEM", TDD_Mapping_PlotItem},/*{int}*/\
{"[:SENSe]:MAPping:PANNAVIgate", TDD_Mapping_PanNavigate},/*{int}*/\
{"[:SENSe]:MAPping:PLOT:TABle", TDD_Mapping_PlotTable},/*{int}*/\
{"[:SENSe]:CC:SELEct", TDD_CC_Select},/*{int}*/\
{"[:SENSe]:CC:ACTive", TDD_CC_Active},/*{int}*/\
{"[:SENSe]:CC:1:ACTive", TDD_CC1_Active},/*{int}*/\
{"[:SENSe]:CC:2:ACTive", TDD_CC2_Active},/*{int}*/\
{"[:SENSe]:CC:3:ACTive", TDD_CC3_Active},/*{int}*/\
{"[:SENSe]:CC:4:ACTive", TDD_CC4_Active},/*{int}*/\
{"[:SENSe]:CC:5:ACTive", TDD_CC5_Active},/*{int}*/\
{"[:SENSe]:CC:FREQuency", TDD_CC_CenterFrequency},/*{double}*/\
{"[:SENSe]:CC:1:FREQuency", TDD_CC1_CenterFrequency},/*{double}*/\
{"[:SENSe]:CC:2:FREQuency", TDD_CC2_CenterFrequency},/*{double}*/\
{"[:SENSe]:CC:3:FREQuency", TDD_CC3_CenterFrequency},/*{double}*/\
{"[:SENSe]:CC:4:FREQuency", TDD_CC4_CenterFrequency},/*{double}*/\
{"[:SENSe]:CC:5:FREQuency", TDD_CC5_CenterFrequency},/*{double}*/\
{"[:SENSe]:CC:BANDWidth", TDD_CC_BandWidth},/*{double}*/\
{"[:SENSe]:CC:1:BANDWidth", TDD_CC1_BandWidth},/*{double}*/\
{"[:SENSe]:CC:2:BANDWidth", TDD_CC2_BandWidth},/*{double}*/\
{"[:SENSe]:CC:3:BANDWidth", TDD_CC3_BandWidth},/*{double}*/\
{"[:SENSe]:CC:4:BANDWidth", TDD_CC4_BandWidth},/*{double}*/\
{"[:SENSe]:CC:5:BANDWidth", TDD_CC5_BandWidth},/*{double}*/\
{"[:SENSe]:CC:PHICH:DURAtion", TDD_CC_PhichDuration},/*{int}*/\
{"[:SENSe]:CC:1:PHICH:DURAtion", TDD_CC1_PhichDuration},/*{int}*/\
{"[:SENSe]:CC:2:PHICH:DURAtion", TDD_CC2_PhichDuration},/*{int}*/\
{"[:SENSe]:CC:3:PHICH:DURAtion", TDD_CC3_PhichDuration},/*{int}*/\
{"[:SENSe]:CC:4:PHICH:DURAtion", TDD_CC4_PhichDuration},/*{int}*/\
{"[:SENSe]:CC:5:PHICH:DURAtion", TDD_CC5_PhichDuration},/*{int}*/\
{"[:SENSe]:CC:PHICH:NG", TDD_CC_PhichNG},/*{int}*/\
{"[:SENSe]:CC:1:PHICH:NG", TDD_CC1_PhichNG},/*{int}*/\
{"[:SENSe]:CC:2:PHICH:NG", TDD_CC2_PhichNG},/*{int}*/\
{"[:SENSe]:CC:3:PHICH:NG", TDD_CC3_PhichNG},/*{int}*/\
{"[:SENSe]:CC:4:PHICH:NG", TDD_CC4_PhichNG},/*{int}*/\
{"[:SENSe]:CC:5:PHICH:NG", TDD_CC5_PhichNG},/*{int}*/\
{"[:SENSe]:CC:CYCLicprefix", TDD_CC_CyclicPrefix},/*{int}*/\
{"[:SENSe]:CC:1:CYCLicprefix", TDD_CC1_CyclicPrefix},/*{int}*/\
{"[:SENSe]:CC:2:CYCLicprefix", TDD_CC2_CyclicPrefix},/*{int}*/\
{"[:SENSe]:CC:3:CYCLicprefix", TDD_CC3_CyclicPrefix},/*{int}*/\
{"[:SENSe]:CC:4:CYCLicprefix", TDD_CC4_CyclicPrefix},/*{int}*/\
{"[:SENSe]:CC:5:CYCLicprefix", TDD_CC5_CyclicPrefix},/*{int}*/\
{"[:SENSe]:CC:ANTPort", TDD_CC_AntPort},/*{int}*/\
{"[:SENSe]:CC:1:ANTPort", TDD_CC1_AntPort},/*{int}*/\
{"[:SENSe]:CC:2:ANTPort", TDD_CC2_AntPort},/*{int}*/\
{"[:SENSe]:CC:3:ANTPort", TDD_CC3_AntPort},/*{int}*/\
{"[:SENSe]:CC:4:ANTPort", TDD_CC4_AntPort},/*{int}*/\
{"[:SENSe]:CC:5:ANTPort", TDD_CC5_AntPort},/*{int}*/\
{"[:SENSe]:DAM:COLORMap:SCALe:AUTO", TDD_DAM_ColorMap_AutoScale},/*{none}*/\
{"[:SENSe]:DAM:COLORMap:MAXValue", TDD_DAM_ColorMap_MaxValue},/*{double}*/\
{"[:SENSe]:DAM:COLORMap:RANGe", TDD_DAM_ColorMap_Range},/*{double}*/\
{"[:SENSe]:DATAGRam:COLORMap:SCALe:AUTO", TDD_DataGram_ColorMap_AutoScale},/*{none}*/\
{"[:SENSe]:DATAGRam:COLORMap:MAXValue", TDD_DataGram_ColorMap_MaxValue},/*{double}*/\
{"[:SENSe]:DATAGRam:COLORMap:RANGe", TDD_DataGram_ColorMap_Range},/*{double}*/\
{"[:SENSe]:TDD:MEASure:MODE", TDD_Measure_Mode},/*{int}*/\
\
{"[:SENSe]:BANDWidth?", TDD_ChannelBWQ},/*{double}*/\
{"[:SENSe]:SUBFrame?", TDD_SubFrameQ},/*{int}*/\
{"[:SENSe]:CELLID:AUTO?", TDD_CellID_AutoQ},/*{int}*/\
{"[:SENSe]:CELLID?", TDD_CellIDQ},/*{int}*/\
{"[:SENSe]:CYCLicprefix?", TDD_CyclicPrefixQ},/*{int}*/\
{"[:SENSe]:ANTPort?", TDD_AntPortQ},/*{int}*/\
{"[:SENSe]:PHICH:DURAtion?", TDD_PhichDurationQ},/*{int}*/\
{"[:SENSe]:PHICH:NG?", TDD_PhichNGQ},/*{int}*/\
{"[:SENSe]:MODULAtion:TYPE?", TDD_ModulationTypeQ},/*{int}*/\
{"[:SENSe]:CFI:AUTO?", TDD_CFI_AutoQ},/*{int}*/\
{"[:SENSe]:CFI?", TDD_CFIQ},/*{int}*/\
{"[:SENSe]:RB:INDEx?", TDD_RBIndexQ},/*{int}*/\
{"[:SENSe]:SUBFrame:UPDOwn?", TDD_SubFrame_UpDownQ},/*{int}*/\
{"[:SENSe]:SUBFrame:SPECial?", TDD_SubFrame_SpecialQ},/*{int}*/\
{"[:SENSe]:CHPower:BANDwidth:INTegration?", TDD_CHPower_IntegrationBWQ},/*{double}*/\
{"[:SENSe]:CHPower:LIMit:POWer:STATe?", TDD_CHPower_PowerLimitQ},/*{int}*/\
{"[:SENSe]:CHPower:LIMit:POWer:VALue?", TDD_CHPower_PowerLimitValueQ},/*{double}*/\
{"[:SENSe]:CHPower:LIMit:PSD:STATe?", TDD_CHPower_PSDLimitQ},/*{int}*/\
{"[:SENSe]:CHPower:LIMit:PSD:VALue?", TDD_CHPower_PSDLimitValueQ},/*{double}*/\
{"[:SENSe]:OBWidth:METHod?", TDD_OBWidth_MethodQ},/*{int}*/\
{"[:SENSe]:OBWidth:PERCent?", TDD_OBWidth_PercentQ},/*{double}*/\
{"[:SENSe]:OBWidth:XDB?", TDD_OBWidth_XdBQ},/*{double}*/\
{"[:SENSe]:OBWidth:LIMit:STATe?", TDD_OBWidth_LimitQ},/*{int}*/\
{"[:SENSe]:OBWidth:LIMit:VALue?", TDD_OBWidth_LimitValueQ},/*{double}*/\
{"[:SENSe]:TAE:TIME:REFerence?", TDD_TAE_ReferenceTimeQ},/*{double}*/\
{"[:SENSe]:TAE:TIME:SCALe?", TDD_TAE_ScaleTimeQ},/*{double}*/\
{"[:SENSe]:FREQLIST:ADD:1:FREQuency?", TDD_FreqList1_AddFrequencyQ},/*{double}*/\
{"[:SENSe]:FREQLIST:ADD:2:FREQuency?", TDD_FreqList2_AddFrequencyQ},/*{double}*/\
{"[:SENSe]:FREQLIST:ADD:3:FREQuency?", TDD_FreqList3_AddFrequencyQ},/*{double}*/\
{"[:SENSe]:FREQLIST:ADD:4:FREQuency?", TDD_FreqList4_AddFrequencyQ},/*{double}*/\
{"[:SENSe]:FREQLIST:ADD:5:FREQuency?", TDD_FreqList5_AddFrequencyQ},/*{double}*/\
{"[:SENSe]:FREQLIST:ADD:6:FREQuency?", TDD_FreqList6_AddFrequencyQ},/*{double}*/\
{"[:SENSe]:FREQLIST:ADD:1:CHANnel:NUMber?", TDD_FreqList1_AddChannelNoQ},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:2:CHANnel:NUMber?", TDD_FreqList2_AddChannelNoQ},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:3:CHANnel:NUMber?", TDD_FreqList3_AddChannelNoQ},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:4:CHANnel:NUMber?", TDD_FreqList4_AddChannelNoQ},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:5:CHANnel:NUMber?", TDD_FreqList5_AddChannelNoQ},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:6:CHANnel:NUMber?", TDD_FreqList6_AddChannelNoQ},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:1:CHANnel:STD?", TDD_FreqList1_AddChannelStandardQ},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:2:CHANnel:STD?", TDD_FreqList2_AddChannelStandardQ},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:3:CHANnel:STD?", TDD_FreqList3_AddChannelStandardQ},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:4:CHANnel:STD?", TDD_FreqList4_AddChannelStandardQ},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:5:CHANnel:STD?", TDD_FreqList5_AddChannelStandardQ},/*{int}*/\
{"[:SENSe]:FREQLIST:ADD:6:CHANnel:STD?", TDD_FreqList6_AddChannelStandardQ},/*{int}*/\
{"[:SENSe]:MAPping:PLOT?", TDD_Mapping_PlotQ},/*{int}*/\
{"[:SENSe]:MAPping:PLOT:ITEM?", TDD_Mapping_PlotItemQ},/*{int}*/\
{"[:SENSe]:MAPping:PANNAVIgate?", TDD_Mapping_PanNavigateQ},/*{int}*/\
{"[:SENSe]:MAPping:PLOT:TABle?", TDD_Mapping_PlotTableQ},/*{int}*/\
{"[:SENSe]:CC:SELEct?", TDD_CC_SelectQ},/*{int}*/\
{"[:SENSe]:CC:ACTive?", TDD_CC_ActiveQ},/*{int}*/\
{"[:SENSe]:CC:1:ACTive?", TDD_CC1_ActiveQ},/*{int}*/\
{"[:SENSe]:CC:2:ACTive?", TDD_CC2_ActiveQ},/*{int}*/\
{"[:SENSe]:CC:3:ACTive?", TDD_CC3_ActiveQ},/*{int}*/\
{"[:SENSe]:CC:4:ACTive?", TDD_CC4_ActiveQ},/*{int}*/\
{"[:SENSe]:CC:5:ACTive?", TDD_CC5_ActiveQ},/*{int}*/\
{"[:SENSe]:CC:FREQuency?", TDD_CC_CenterFrequencyQ},/*{double}*/\
{"[:SENSe]:CC:1:FREQuency?", TDD_CC1_CenterFrequencyQ},/*{double}*/\
{"[:SENSe]:CC:2:FREQuency?", TDD_CC2_CenterFrequencyQ},/*{double}*/\
{"[:SENSe]:CC:3:FREQuency?", TDD_CC3_CenterFrequencyQ},/*{double}*/\
{"[:SENSe]:CC:4:FREQuency?", TDD_CC4_CenterFrequencyQ},/*{double}*/\
{"[:SENSe]:CC:5:FREQuency?", TDD_CC5_CenterFrequencyQ},/*{double}*/\
{"[:SENSe]:CC:BANDWidth?", TDD_CC_BandWidthQ},/*{double}*/\
{"[:SENSe]:CC:1:BANDWidth?", TDD_CC1_BandWidthQ},/*{double}*/\
{"[:SENSe]:CC:2:BANDWidth?", TDD_CC2_BandWidthQ},/*{double}*/\
{"[:SENSe]:CC:3:BANDWidth?", TDD_CC3_BandWidthQ},/*{double}*/\
{"[:SENSe]:CC:4:BANDWidth?", TDD_CC4_BandWidthQ},/*{double}*/\
{"[:SENSe]:CC:5:BANDWidth?", TDD_CC5_BandWidthQ},/*{double}*/\
{"[:SENSe]:CC:PHICH:DURAtion?", TDD_CC_PhichDurationQ},/*{int}*/\
{"[:SENSe]:CC:1:PHICH:DURAtion?", TDD_CC1_PhichDurationQ},/*{int}*/\
{"[:SENSe]:CC:2:PHICH:DURAtion?", TDD_CC2_PhichDurationQ},/*{int}*/\
{"[:SENSe]:CC:3:PHICH:DURAtion?", TDD_CC3_PhichDurationQ},/*{int}*/\
{"[:SENSe]:CC:4:PHICH:DURAtion?", TDD_CC4_PhichDurationQ},/*{int}*/\
{"[:SENSe]:CC:5:PHICH:DURAtion?", TDD_CC5_PhichDurationQ},/*{int}*/\
{"[:SENSe]:CC:PHICH:NG?", TDD_CC_PhichNGQ},/*{int}*/\
{"[:SENSe]:CC:1:PHICH:NG?", TDD_CC1_PhichNGQ},/*{int}*/\
{"[:SENSe]:CC:2:PHICH:NG?", TDD_CC2_PhichNGQ},/*{int}*/\
{"[:SENSe]:CC:3:PHICH:NG?", TDD_CC3_PhichNGQ},/*{int}*/\
{"[:SENSe]:CC:4:PHICH:NG?", TDD_CC4_PhichNGQ},/*{int}*/\
{"[:SENSe]:CC:5:PHICH:NG?", TDD_CC5_PhichNGQ},/*{int}*/\
{"[:SENSe]:CC:CYCLicprefix?", TDD_CC_CyclicPrefixQ},/*{int}*/\
{"[:SENSe]:CC:1:CYCLicprefix?", TDD_CC1_CyclicPrefixQ},/*{int}*/\
{"[:SENSe]:CC:2:CYCLicprefix?", TDD_CC2_CyclicPrefixQ},/*{int}*/\
{"[:SENSe]:CC:3:CYCLicprefix?", TDD_CC3_CyclicPrefixQ},/*{int}*/\
{"[:SENSe]:CC:4:CYCLicprefix?", TDD_CC4_CyclicPrefixQ},/*{int}*/\
{"[:SENSe]:CC:5:CYCLicprefix?", TDD_CC5_CyclicPrefixQ},/*{int}*/\
{"[:SENSe]:CC:ANTPort?", TDD_CC_AntPortQ},/*{int}*/\
{"[:SENSe]:CC:1:ANTPort?", TDD_CC1_AntPortQ},/*{int}*/\
{"[:SENSe]:CC:2:ANTPort?", TDD_CC2_AntPortQ},/*{int}*/\
{"[:SENSe]:CC:3:ANTPort?", TDD_CC3_AntPortQ},/*{int}*/\
{"[:SENSe]:CC:4:ANTPort?", TDD_CC4_AntPortQ},/*{int}*/\
{"[:SENSe]:CC:5:ANTPort?", TDD_CC5_AntPortQ},/*{int}*/\
{"[:SENSe]:DAM:COLORMap:MAXValue?", TDD_DAM_ColorMap_MaxValueQ},/*{double}*/\
{"[:SENSe]:DAM:COLORMap:RANGe?", TDD_DAM_ColorMap_RangeQ},/*{double}*/\
{"[:SENSe]:DATAGRam:COLORMap:MAXValue?", TDD_DataGram_ColorMap_MaxValueQ},/*{double}*/\
{"[:SENSe]:DATAGRam:COLORMap:RANGe?", TDD_DataGram_ColorMap_RangeQ},/*{double}*/\
{"[:SENSe]:TDD:MEASure:MODE?", TDD_Measure_ModeQ},/*{int}*/\

scpi_result_t TDD_ChannelBW(scpi_t * context);
scpi_result_t TDD_SubFrame(scpi_t * context);
scpi_result_t TDD_CellID_Auto(scpi_t * context);
scpi_result_t TDD_CellID(scpi_t * context);
scpi_result_t TDD_CyclicPrefix(scpi_t * context);
scpi_result_t TDD_AntPort(scpi_t * context);
scpi_result_t TDD_PhichDuration(scpi_t * context);
scpi_result_t TDD_PhichNG(scpi_t * context);
scpi_result_t TDD_ModulationType(scpi_t * context);
scpi_result_t TDD_CFI_Auto(scpi_t * context);
scpi_result_t TDD_CFI(scpi_t * context);
scpi_result_t TDD_RBIndex(scpi_t * context);
scpi_result_t TDD_SearchPMax(scpi_t * context);
scpi_result_t TDD_SearchPMin(scpi_t * context);
scpi_result_t TDD_SearchMaxPrevious(scpi_t * context);
scpi_result_t TDD_SearchMaxNext(scpi_t * context);
scpi_result_t TDD_SubFrame_UpDown(scpi_t * context);
scpi_result_t TDD_SubFrame_Special(scpi_t * context);
scpi_result_t TDD_CHPower_IntegrationBW(scpi_t * context);
scpi_result_t TDD_CHPower_PowerLimit(scpi_t * context);
scpi_result_t TDD_CHPower_PowerLimitValue(scpi_t * context);
scpi_result_t TDD_CHPower_PSDLimit(scpi_t * context);
scpi_result_t TDD_CHPower_PSDLimitValue(scpi_t * context);
scpi_result_t TDD_CHPower_Preset(scpi_t * context);
scpi_result_t TDD_OBWidth_Method(scpi_t * context);
scpi_result_t TDD_OBWidth_Percent(scpi_t * context);
scpi_result_t TDD_OBWidth_XdB(scpi_t * context);
scpi_result_t TDD_OBWidth_Limit(scpi_t * context);
scpi_result_t TDD_OBWidth_LimitValue(scpi_t * context);
scpi_result_t TDD_OBWidth_Preset(scpi_t * context);
scpi_result_t TDD_TAE_ReferenceTime(scpi_t * context);
scpi_result_t TDD_TAE_ScaleTime(scpi_t * context);
scpi_result_t TDD_FreqList_State(scpi_t * context);
scpi_result_t TDD_FreqList1_AddFrequency(scpi_t * context);
scpi_result_t TDD_FreqList2_AddFrequency(scpi_t * context);
scpi_result_t TDD_FreqList3_AddFrequency(scpi_t * context);
scpi_result_t TDD_FreqList4_AddFrequency(scpi_t * context);
scpi_result_t TDD_FreqList5_AddFrequency(scpi_t * context);
scpi_result_t TDD_FreqList6_AddFrequency(scpi_t * context);
scpi_result_t TDD_FreqList1_AddChannelNo(scpi_t * context);
scpi_result_t TDD_FreqList2_AddChannelNo(scpi_t * context);
scpi_result_t TDD_FreqList3_AddChannelNo(scpi_t * context);
scpi_result_t TDD_FreqList4_AddChannelNo(scpi_t * context);
scpi_result_t TDD_FreqList5_AddChannelNo(scpi_t * context);
scpi_result_t TDD_FreqList6_AddChannelNo(scpi_t * context);
scpi_result_t TDD_FreqList1_AddChannelStandard(scpi_t * context);
scpi_result_t TDD_FreqList2_AddChannelStandard(scpi_t * context);
scpi_result_t TDD_FreqList3_AddChannelStandard(scpi_t * context);
scpi_result_t TDD_FreqList4_AddChannelStandard(scpi_t * context);
scpi_result_t TDD_FreqList5_AddChannelStandard(scpi_t * context);
scpi_result_t TDD_FreqList6_AddChannelStandard(scpi_t * context);
scpi_result_t TDD_Mapping_Plot(scpi_t * context);
scpi_result_t TDD_Mapping_PlotItem(scpi_t * context);
scpi_result_t TDD_Mapping_PanNavigate(scpi_t * context);
scpi_result_t TDD_Mapping_PlotTable(scpi_t * context);
scpi_result_t TDD_CC_Select(scpi_t * context);
scpi_result_t TDD_CC_Active(scpi_t * context);
scpi_result_t TDD_CC1_Active(scpi_t * context);
scpi_result_t TDD_CC2_Active(scpi_t * context);
scpi_result_t TDD_CC3_Active(scpi_t * context);
scpi_result_t TDD_CC4_Active(scpi_t * context);
scpi_result_t TDD_CC5_Active(scpi_t * context);
scpi_result_t TDD_CC_CenterFrequency(scpi_t * context);
scpi_result_t TDD_CC1_CenterFrequency(scpi_t * context);
scpi_result_t TDD_CC2_CenterFrequency(scpi_t * context);
scpi_result_t TDD_CC3_CenterFrequency(scpi_t * context);
scpi_result_t TDD_CC4_CenterFrequency(scpi_t * context);
scpi_result_t TDD_CC5_CenterFrequency(scpi_t * context);
scpi_result_t TDD_CC_BandWidth(scpi_t * context);
scpi_result_t TDD_CC1_BandWidth(scpi_t * context);
scpi_result_t TDD_CC2_BandWidth(scpi_t * context);
scpi_result_t TDD_CC3_BandWidth(scpi_t * context);
scpi_result_t TDD_CC4_BandWidth(scpi_t * context);
scpi_result_t TDD_CC5_BandWidth(scpi_t * context);
scpi_result_t TDD_CC_PhichDuration(scpi_t * context);
scpi_result_t TDD_CC1_PhichDuration(scpi_t * context);
scpi_result_t TDD_CC2_PhichDuration(scpi_t * context);
scpi_result_t TDD_CC3_PhichDuration(scpi_t * context);
scpi_result_t TDD_CC4_PhichDuration(scpi_t * context);
scpi_result_t TDD_CC5_PhichDuration(scpi_t * context);
scpi_result_t TDD_CC_PhichNG(scpi_t * context);
scpi_result_t TDD_CC1_PhichNG(scpi_t * context);
scpi_result_t TDD_CC2_PhichNG(scpi_t * context);
scpi_result_t TDD_CC3_PhichNG(scpi_t * context);
scpi_result_t TDD_CC4_PhichNG(scpi_t * context);
scpi_result_t TDD_CC5_PhichNG(scpi_t * context);
scpi_result_t TDD_CC_CyclicPrefix(scpi_t * context);
scpi_result_t TDD_CC1_CyclicPrefix(scpi_t * context);
scpi_result_t TDD_CC2_CyclicPrefix(scpi_t * context);
scpi_result_t TDD_CC3_CyclicPrefix(scpi_t * context);
scpi_result_t TDD_CC4_CyclicPrefix(scpi_t * context);
scpi_result_t TDD_CC5_CyclicPrefix(scpi_t * context);
scpi_result_t TDD_CC_AntPort(scpi_t * context);
scpi_result_t TDD_CC1_AntPort(scpi_t * context);
scpi_result_t TDD_CC2_AntPort(scpi_t * context);
scpi_result_t TDD_CC3_AntPort(scpi_t * context);
scpi_result_t TDD_CC4_AntPort(scpi_t * context);
scpi_result_t TDD_CC5_AntPort(scpi_t * context);
scpi_result_t TDD_DAM_ColorMap_AutoScale(scpi_t * context);
scpi_result_t TDD_DAM_ColorMap_MaxValue(scpi_t * context);
scpi_result_t TDD_DAM_ColorMap_Range(scpi_t * context);
scpi_result_t TDD_DataGram_ColorMap_AutoScale(scpi_t * context);
scpi_result_t TDD_DataGram_ColorMap_MaxValue(scpi_t * context);
scpi_result_t TDD_DataGram_ColorMap_Range(scpi_t * context);
scpi_result_t TDD_Measure_Mode(scpi_t * context);

scpi_result_t TDD_ChannelBWQ(scpi_t * context);
scpi_result_t TDD_SubFrameQ(scpi_t * context);
scpi_result_t TDD_CellID_AutoQ(scpi_t * context);
scpi_result_t TDD_CellIDQ(scpi_t * context);
scpi_result_t TDD_CyclicPrefixQ(scpi_t * context);
scpi_result_t TDD_AntPortQ(scpi_t * context);
scpi_result_t TDD_PhichDurationQ(scpi_t * context);
scpi_result_t TDD_PhichNGQ(scpi_t * context);
scpi_result_t TDD_ModulationTypeQ(scpi_t * context);
scpi_result_t TDD_CFI_AutoQ(scpi_t * context);
scpi_result_t TDD_CFIQ(scpi_t * context);
scpi_result_t TDD_RBIndexQ(scpi_t * context);
scpi_result_t TDD_SubFrame_UpDownQ(scpi_t * context);
scpi_result_t TDD_SubFrame_SpecialQ(scpi_t * context);
scpi_result_t TDD_CHPower_IntegrationBWQ(scpi_t * context);
scpi_result_t TDD_CHPower_PowerLimitQ(scpi_t * context);
scpi_result_t TDD_CHPower_PowerLimitValueQ(scpi_t * context);
scpi_result_t TDD_CHPower_PSDLimitQ(scpi_t * context);
scpi_result_t TDD_CHPower_PSDLimitValueQ(scpi_t * context);
scpi_result_t TDD_OBWidth_MethodQ(scpi_t * context);
scpi_result_t TDD_OBWidth_PercentQ(scpi_t * context);
scpi_result_t TDD_OBWidth_XdBQ(scpi_t * context);
scpi_result_t TDD_OBWidth_LimitQ(scpi_t * context);
scpi_result_t TDD_OBWidth_LimitValueQ(scpi_t * context);
scpi_result_t TDD_TAE_ReferenceTimeQ(scpi_t * context);
scpi_result_t TDD_TAE_ScaleTimeQ(scpi_t * context);
scpi_result_t TDD_FreqList1_AddFrequencyQ(scpi_t * context);
scpi_result_t TDD_FreqList2_AddFrequencyQ(scpi_t * context);
scpi_result_t TDD_FreqList3_AddFrequencyQ(scpi_t * context);
scpi_result_t TDD_FreqList4_AddFrequencyQ(scpi_t * context);
scpi_result_t TDD_FreqList5_AddFrequencyQ(scpi_t * context);
scpi_result_t TDD_FreqList6_AddFrequencyQ(scpi_t * context);
scpi_result_t TDD_FreqList1_AddChannelNoQ(scpi_t * context);
scpi_result_t TDD_FreqList2_AddChannelNoQ(scpi_t * context);
scpi_result_t TDD_FreqList3_AddChannelNoQ(scpi_t * context);
scpi_result_t TDD_FreqList4_AddChannelNoQ(scpi_t * context);
scpi_result_t TDD_FreqList5_AddChannelNoQ(scpi_t * context);
scpi_result_t TDD_FreqList6_AddChannelNoQ(scpi_t * context);
scpi_result_t TDD_FreqList1_AddChannelStandardQ(scpi_t * context);
scpi_result_t TDD_FreqList2_AddChannelStandardQ(scpi_t * context);
scpi_result_t TDD_FreqList3_AddChannelStandardQ(scpi_t * context);
scpi_result_t TDD_FreqList4_AddChannelStandardQ(scpi_t * context);
scpi_result_t TDD_FreqList5_AddChannelStandardQ(scpi_t * context);
scpi_result_t TDD_FreqList6_AddChannelStandardQ(scpi_t * context);
scpi_result_t TDD_Mapping_PlotQ(scpi_t * context);
scpi_result_t TDD_Mapping_PlotItemQ(scpi_t * context);
scpi_result_t TDD_Mapping_PanNavigateQ(scpi_t * context);
scpi_result_t TDD_Mapping_PlotTableQ(scpi_t * context);
scpi_result_t TDD_CC_SelectQ(scpi_t * context);
scpi_result_t TDD_CC_ActiveQ(scpi_t * context);
scpi_result_t TDD_CC1_ActiveQ(scpi_t * context);
scpi_result_t TDD_CC2_ActiveQ(scpi_t * context);
scpi_result_t TDD_CC3_ActiveQ(scpi_t * context);
scpi_result_t TDD_CC4_ActiveQ(scpi_t * context);
scpi_result_t TDD_CC5_ActiveQ(scpi_t * context);
scpi_result_t TDD_CC_CenterFrequencyQ(scpi_t * context);
scpi_result_t TDD_CC1_CenterFrequencyQ(scpi_t * context);
scpi_result_t TDD_CC2_CenterFrequencyQ(scpi_t * context);
scpi_result_t TDD_CC3_CenterFrequencyQ(scpi_t * context);
scpi_result_t TDD_CC4_CenterFrequencyQ(scpi_t * context);
scpi_result_t TDD_CC5_CenterFrequencyQ(scpi_t * context);
scpi_result_t TDD_CC_BandWidthQ(scpi_t * context);
scpi_result_t TDD_CC1_BandWidthQ(scpi_t * context);
scpi_result_t TDD_CC2_BandWidthQ(scpi_t * context);
scpi_result_t TDD_CC3_BandWidthQ(scpi_t * context);
scpi_result_t TDD_CC4_BandWidthQ(scpi_t * context);
scpi_result_t TDD_CC5_BandWidthQ(scpi_t * context);
scpi_result_t TDD_CC_PhichDurationQ(scpi_t * context);
scpi_result_t TDD_CC1_PhichDurationQ(scpi_t * context);
scpi_result_t TDD_CC2_PhichDurationQ(scpi_t * context);
scpi_result_t TDD_CC3_PhichDurationQ(scpi_t * context);
scpi_result_t TDD_CC4_PhichDurationQ(scpi_t * context);
scpi_result_t TDD_CC5_PhichDurationQ(scpi_t * context);
scpi_result_t TDD_CC_PhichNGQ(scpi_t * context);
scpi_result_t TDD_CC1_PhichNGQ(scpi_t * context);
scpi_result_t TDD_CC2_PhichNGQ(scpi_t * context);
scpi_result_t TDD_CC3_PhichNGQ(scpi_t * context);
scpi_result_t TDD_CC4_PhichNGQ(scpi_t * context);
scpi_result_t TDD_CC5_PhichNGQ(scpi_t * context);
scpi_result_t TDD_CC_CyclicPrefixQ(scpi_t * context);
scpi_result_t TDD_CC1_CyclicPrefixQ(scpi_t * context);
scpi_result_t TDD_CC2_CyclicPrefixQ(scpi_t * context);
scpi_result_t TDD_CC3_CyclicPrefixQ(scpi_t * context);
scpi_result_t TDD_CC4_CyclicPrefixQ(scpi_t * context);
scpi_result_t TDD_CC5_CyclicPrefixQ(scpi_t * context);
scpi_result_t TDD_CC_AntPortQ(scpi_t * context);
scpi_result_t TDD_CC1_AntPortQ(scpi_t * context);
scpi_result_t TDD_CC2_AntPortQ(scpi_t * context);
scpi_result_t TDD_CC3_AntPortQ(scpi_t * context);
scpi_result_t TDD_CC4_AntPortQ(scpi_t * context);
scpi_result_t TDD_CC5_AntPortQ(scpi_t * context);
scpi_result_t TDD_DAM_ColorMap_MaxValueQ(scpi_t * context);
scpi_result_t TDD_DAM_ColorMap_RangeQ(scpi_t * context);
scpi_result_t TDD_DataGram_ColorMap_MaxValueQ(scpi_t * context);
scpi_result_t TDD_DataGram_ColorMap_RangeQ(scpi_t * context);
scpi_result_t TDD_Measure_ModeQ(scpi_t * context);

#ifdef __cplusplus
}
#endif

#endif // TDD_SCPI_MEAS_H
