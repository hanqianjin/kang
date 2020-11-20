#ifndef SCPIDEF_FREQUENCY_H
#define SCPIDEF_FREQUENCY_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef  __cplusplus
extern "C" {
#endif


#define SCPI_COMMANDS_FREQUENCY \
{"[:SENSe]:FREQuency:CENTer", SA_FREQUENCY_Center_Freq},/*{Int}*/\
{"[:SENSe]:FREQuency:STARt", SA_FREQUENCY_Start_Freq},/*{Int}*/\
{"[:SENSe]:FREQuency:STOP", SA_FREQUENCY_Stop_Freq},/*{Int}*/\
{"[:SENSe]:FREQuency:STEP", SA_FREQUENCY_Step_Freq},/*{Int}*/\
{"[:SENSe]:FREQuency:CENTer:STEP:AUTO", SA_FREQUENCY_Step_CenterFreq_Auto},/*{ON|OFF|1|0}*/\
{"[:SENSe]:FREQuency:CENTer:STEP", SA_FREQUENCY_CenterFreq_Step},/*{UP|DOWn}*/\
{"[:SENSe]:FREQuency:SPAN", SA_FREQUENCY_Freq_Span},/*{Int}*/\
{"[:SENSe]:FREQuency:SPAN:FULL", SA_FREQUENCY_Freq_FullSpan},\
{"[:SENSe]:FREQuency:SPAN:ZERO", SA_FREQUENCY_Freq_ZeroSpan},\
{"[:SENSe]:FREQuency:SPAN:PREVious", SA_FREQUENCY_Freq_PreviousSpan},\
\
{"[:SENSe]:FREQuency:CENTer?", SA_FREQUENCY_Center_FreqQ},/*{Int}*/\
{"[:SENSe]:FREQuency:STARt?", SA_FREQUENCY_Start_FreqQ},/*{Int}*/\
{"[:SENSe]:FREQuency:STOP?", SA_FREQUENCY_Stop_FreqQ},/*{Int}*/\
{"[:SENSe]:FREQuency:STEP?", SA_FREQUENCY_Step_FreqQ},/*{Int}*/\
{"[:SENSe]:FREQuency:CENTer:STEP?", SA_FREQUENCY_Step_CenterFreqQ},/*{Int}*/\
{"[:SENSe]:FREQuency:CENTer:STEP:AUTO?", SA_FREQUENCY_Step_CenterFreq_AutoQ},/*{ON|OFF|1|0}*/\
{"[:SENSe]:FREQuency:SPAN?", SA_FREQUENCY_Freq_SpanQ},/*{Int}*/



scpi_result_t SA_FREQUENCY_Center_Freq(scpi_t * context);
scpi_result_t SA_FREQUENCY_Start_Freq(scpi_t * context);
scpi_result_t SA_FREQUENCY_Stop_Freq(scpi_t * context);
scpi_result_t SA_FREQUENCY_Step_Freq(scpi_t * context);
scpi_result_t SA_FREQUENCY_Step_CenterFreq_Auto(scpi_t * context);
scpi_result_t SA_FREQUENCY_CenterFreq_Step(scpi_t * context);
scpi_result_t SA_FREQUENCY_Freq_Span(scpi_t * context);
scpi_result_t SA_FREQUENCY_Freq_FullSpan(scpi_t * context);
scpi_result_t SA_FREQUENCY_Freq_ZeroSpan(scpi_t * context);
scpi_result_t SA_FREQUENCY_Freq_PreviousSpan(scpi_t * context);

scpi_result_t SA_FREQUENCY_Center_FreqQ(scpi_t * context);
scpi_result_t SA_FREQUENCY_Start_FreqQ(scpi_t * context);
scpi_result_t SA_FREQUENCY_Stop_FreqQ(scpi_t * context);
scpi_result_t SA_FREQUENCY_Step_FreqQ(scpi_t * context);
scpi_result_t SA_FREQUENCY_Step_CenterFreqQ(scpi_t * context);
scpi_result_t SA_FREQUENCY_Step_CenterFreq_AutoQ(scpi_t * context);
scpi_result_t SA_FREQUENCY_Freq_SpanQ(scpi_t * context);


#ifdef  __cplusplus
}
#endif
#endif // SCPIDEF_FREQUENCY_H
