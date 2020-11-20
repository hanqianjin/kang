#ifndef RTSA_SCPI_FREQ_H
#define RTSA_SCPI_FREQ_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef  __cplusplus
extern "C" {
#endif


#define RTSA_SCPI_COMMANDS_FREQUENCY \
{"[:SENSe]:FREQuency:CENTer", RTSA_FREQUENCY_Center_Freq},/*{Int}*/\
{"[:SENSe]:FREQuency:STARt", RTSA_FREQUENCY_Start_Freq},/*{Int}*/\
{"[:SENSe]:FREQuency:STOP", RTSA_FREQUENCY_Stop_Freq},/*{Int}*/\
{"[:SENSe]:FREQuency:STEP", RTSA_FREQUENCY_Step_Freq},/*{Int}*/\
{"[:SENSe]:FREQuency:SPAN", RTSA_FREQUENCY_Freq_Span},/*{Int}*/\
{"[:SENSe]:FREQuency:SPAN:FULL", RTSA_FREQUENCY_Freq_FullSpan},\
{"[:SENSe]:FREQuency:OFFSet", RTSA_FREQUENCY_Offset_Freq},/*{Int}*/\
{"[:SENSe]:FREQuency:CHannel:STD", RTSA_FREQUENCY_Channel_Standard},/*{Int}*/\
{"[:SENSe]:FREQuency:CHannel:STD:BAND", RTSA_FREQUENCY_Channel_Standard_BandIndex},/*{Int}*/\
{"[:SENSe]:FREQuency:CHannel:NUMber", RTSA_FREQUENCY_Channel_Number},/*{Int}*/\
{"[:SENSe]:FREQuency:CHannel:STEP", RTSA_FREQUENCY_Channel_Step},/*{Int}*/\
{"[:SENSe]:FREQuency:CHannel:TYPE", RTSA_FREQUENCY_Channel_Type},/*{Int}*/\
\
{"[:SENSe]:FREQuency:CENTer?", RTSA_FREQUENCY_Center_FreqQ},/*{Int}*/\
{"[:SENSe]:FREQuency:STARt?", RTSA_FREQUENCY_Start_FreqQ},/*{Int}*/\
{"[:SENSe]:FREQuency:STOP?", RTSA_FREQUENCY_Stop_FreqQ},/*{Int}*/\
{"[:SENSe]:FREQuency:STEP?", RTSA_FREQUENCY_Step_FreqQ},/*{Int}*/\
{"[:SENSe]:FREQuency:SPAN?", RTSA_FREQUENCY_Freq_SpanQ},/*{Int}*/\
{"[:SENSe]:FREQuency:OFFSet?", RTSA_FREQUENCY_Freq_OffsetQ},/*{Int}*/\
{"[:SENSe]:FREQuency:CHannel:STD?", RTSA_FREQUENCY_Channel_StandardQ},/*{Int}*/\
{"[:SENSe]:FREQuency:CHannel:STD:BAND?", RTSA_FREQUENCY_Channel_Standard_BandIndexQ},/*{Int}*/\
{"[:SENSe]:FREQuency:CHannel:NUMber?", RTSA_FREQUENCY_Channel_NumberQ},/*{Int}*/\
{"[:SENSe]:FREQuency:CHannel:STEP?", RTSA_FREQUENCY_Channel_StepQ},/*{Int}*/\
{"[:SENSe]:FREQuency:CHannel:TYPE?", RTSA_FREQUENCY_Channel_TypeQ},/*{Int}*/\



scpi_result_t RTSA_FREQUENCY_Center_Freq(scpi_t * context);
scpi_result_t RTSA_FREQUENCY_Start_Freq(scpi_t * context);
scpi_result_t RTSA_FREQUENCY_Stop_Freq(scpi_t * context);
scpi_result_t RTSA_FREQUENCY_Step_Freq(scpi_t * context);
scpi_result_t RTSA_FREQUENCY_Freq_Span(scpi_t * context);
scpi_result_t RTSA_FREQUENCY_Freq_FullSpan(scpi_t * context);
scpi_result_t RTSA_FREQUENCY_Offset_Freq(scpi_t * context);
scpi_result_t RTSA_FREQUENCY_Channel_Standard(scpi_t * context);
scpi_result_t RTSA_FREQUENCY_Channel_Standard_BandIndex(scpi_t * context);
scpi_result_t RTSA_FREQUENCY_Channel_Number(scpi_t * context);
scpi_result_t RTSA_FREQUENCY_Channel_Step(scpi_t * context);
scpi_result_t RTSA_FREQUENCY_Channel_Type(scpi_t * context);

scpi_result_t RTSA_FREQUENCY_Center_FreqQ(scpi_t * context);
scpi_result_t RTSA_FREQUENCY_Start_FreqQ(scpi_t * context);
scpi_result_t RTSA_FREQUENCY_Stop_FreqQ(scpi_t * context);
scpi_result_t RTSA_FREQUENCY_Step_FreqQ(scpi_t * context);
scpi_result_t RTSA_FREQUENCY_Freq_SpanQ(scpi_t * context);
scpi_result_t RTSA_FREQUENCY_Freq_OffsetQ(scpi_t * context);
scpi_result_t RTSA_FREQUENCY_Channel_StandardQ(scpi_t * context);
scpi_result_t RTSA_FREQUENCY_Channel_Standard_BandIndexQ(scpi_t * context);
scpi_result_t RTSA_FREQUENCY_Channel_NumberQ(scpi_t * context);
scpi_result_t RTSA_FREQUENCY_Channel_StepQ(scpi_t * context);
scpi_result_t RTSA_FREQUENCY_Channel_TypeQ(scpi_t * context);

#ifdef  __cplusplus
}
#endif
#endif // RTSA_SCPI_FREQ_H
