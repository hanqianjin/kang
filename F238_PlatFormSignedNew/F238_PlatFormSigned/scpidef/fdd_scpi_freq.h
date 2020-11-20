#ifndef FDD_SCPI_FREQ_H
#define FDD_SCPI_FREQ_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FDD_SCPI_COMMANDS_FREQUENCY \
{"[:SENSe]:FREQuency:CENTer", FDD_FREQUENCY_Center_Freq},/*{double}*/\
{"[:SENSe]:FREQuency:STEP", FDD_FREQUENCY_Step_Freq},/*{double}*/\
{"[:SENSe]:FREQuency:CHANnel:STD", FDD_FREQUENCY_Channel_Standard},/*{int}*/\
{"[:SENSe]:FREQuency:CHANnel:NUMber", FDD_FREQUENCY_Channel_Number},/*{int}*/\
{"[:SENSe]:FREQuency:CHANnel:STEP", FDD_FREQUENCY_Channel_Step},/*{int}*/\
\
{"[:SENSe]:FREQuency:CENTer?", FDD_FREQUENCY_Center_FreqQ},/*{double}*/\
{"[:SENSe]:FREQuency:STEP?", FDD_FREQUENCY_Step_FreqQ},/*{double}*/\
{"[:SENSe]:FREQuency:CHANnel:STD?", FDD_FREQUENCY_Channel_StandardQ},/*{int}*/\
{"[:SENSe]:FREQuency:CHANnel:NUMber?", FDD_FREQUENCY_Channel_NumberQ},/*{int}*/\
{"[:SENSe]:FREQuency:CHANnel:STEP?", FDD_FREQUENCY_Channel_StepQ},/*{int}*/\

scpi_result_t FDD_FREQUENCY_Center_Freq(scpi_t * context);
scpi_result_t FDD_FREQUENCY_Step_Freq(scpi_t * context);
scpi_result_t FDD_FREQUENCY_Channel_Standard(scpi_t * context);
scpi_result_t FDD_FREQUENCY_Channel_Number(scpi_t * context);
scpi_result_t FDD_FREQUENCY_Channel_Step(scpi_t * context);

scpi_result_t FDD_FREQUENCY_Center_FreqQ(scpi_t * context);
scpi_result_t FDD_FREQUENCY_Step_FreqQ(scpi_t * context);
scpi_result_t FDD_FREQUENCY_Channel_StandardQ(scpi_t * context);
scpi_result_t FDD_FREQUENCY_Channel_NumberQ(scpi_t * context);
scpi_result_t FDD_FREQUENCY_Channel_StepQ(scpi_t * context);

#ifdef __cplusplus
}
#endif

#endif // FDD_SCPI_FREQ_H
