#ifndef NR_SCPI_FREQ_H
#define NR_SCPI_FREQ_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define NR_SCPI_COMMANDS_FREQUENCY \
{"[:SENSe]:FREQuency:CENTer", NR_FREQUENCY_Center_Freq},/*{Int}*/\
{"[:SENSe]:FREQuency:STEP", NR_FREQUENCY_Step_Freq},/*{Int}*/\
{"[:SENSe]:FREQuency:NRBAnd", NR_FREQUENCY_Band_Number},/*{Int}*/\
{"[:SENSe]:FREQuency:ARFCNumber", NR_FREQUENCY_Arfc_Number},/*{Int}*/\
{"[:SENSe]:FREQuency:GSCNumber", NR_FREQUENCY_Gsc_Number},/*{Int}*/\
\
{"[:SENSe]:FREQuency:CENTer?", NR_FREQUENCY_Center_FreqQ},/*{Int}*/\
{"[:SENSe]:FREQuency:STEP?", NR_FREQUENCY_Step_FreqQ},/*{Int}*/\
{"[:SENSe]:FREQuency:NRBAnd?", NR_FREQUENCY_Band_NumberQ},/*{Int}*/\
{"[:SENSe]:FREQuency:ARFCNumber?", NR_FREQUENCY_Arfc_NumberQ},/*{Int}*/\
{"[:SENSe]:FREQuency:GSCNumber?", NR_FREQUENCY_Gsc_NumberQ},/*{Int}*/\

scpi_result_t NR_FREQUENCY_Center_Freq(scpi_t * context);
scpi_result_t NR_FREQUENCY_Step_Freq(scpi_t * context);
scpi_result_t NR_FREQUENCY_Band_Number(scpi_t * context);
scpi_result_t NR_FREQUENCY_Arfc_Number(scpi_t * context);
scpi_result_t NR_FREQUENCY_Gsc_Number(scpi_t * context);

scpi_result_t NR_FREQUENCY_Center_FreqQ(scpi_t * context);
scpi_result_t NR_FREQUENCY_Step_FreqQ(scpi_t * context);
scpi_result_t NR_FREQUENCY_Band_NumberQ(scpi_t * context);
scpi_result_t NR_FREQUENCY_Arfc_NumberQ(scpi_t * context);
scpi_result_t NR_FREQUENCY_Gsc_NumberQ(scpi_t * context);

#ifdef  __cplusplus
}
#endif

#endif // NR_SCPI_FREQ_H
