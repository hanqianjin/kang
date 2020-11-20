#ifndef NR_SCPI_AMP_H
#define NR_SCPI_AMP_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define NR_SCPI_COMMANDS_AMPLITUDE \
{"[:SENSe]:AMPLitude:SCALe:AUTO", NR_AMPLITUDE_AutoScale},/*{none}*/\
{"[:SENSe]:AMPLitude:RLEVel", NR_AMPLITUDE_Reflevel},/*{double}*/\
{"[:SENSe]:AMPLitude:SCALe", NR_AMPLITUDE_ScaleValue},/*{double}*/\
{"[:SENSe]:AMPLitude:ATTEnuation:AUTO", NR_AMPLITUDE_AutoAtten},/*{int}*/\
{"[:SENSe]:AMPLitude:ATTEnuation", NR_AMPLITUDE_AttenValue},/*{double}*/\
{"[:SENSe]:AMPLitude:PREAmp", NR_AMPLITUDE_Preamp},/*{int}*/\
{"[:SENSe]:AMPLitude:RLEVel:OFFSet", NR_AMPLITUDE_RLevelOffset},/*{double}*/\
\
{"[:SENSe]:AMPLitude:RLEVel?", NR_AMPLITUDE_ReflevelQ},/*{double}*/\
{"[:SENSe]:AMPLitude:SCALe?", NR_AMPLITUDE_ScaleValueQ},/*{double}*/\
{"[:SENSe]:AMPLitude:ATTEnuation:AUTO?", NR_AMPLITUDE_AutoAttenQ},/*{int}*/\
{"[:SENSe]:AMPLitude:ATTEnuation?", NR_AMPLITUDE_AttenValueQ},/*{double}*/\
{"[:SENSe]:AMPLitude:PREAmp?", NR_AMPLITUDE_PreampQ},/*{int}*/\
{"[:SENSe]:AMPLitude:RLEVel:OFFSet?", NR_AMPLITUDE_RLevelOffsetQ},/*{double}*/\

scpi_result_t NR_AMPLITUDE_AutoScale(scpi_t * context);

scpi_result_t NR_AMPLITUDE_Reflevel(scpi_t * context);
scpi_result_t NR_AMPLITUDE_ScaleValue(scpi_t * context);
scpi_result_t NR_AMPLITUDE_AutoAtten(scpi_t * context);
scpi_result_t NR_AMPLITUDE_AttenValue(scpi_t * context);
scpi_result_t NR_AMPLITUDE_Preamp(scpi_t * context);
scpi_result_t NR_AMPLITUDE_RLevelOffset(scpi_t * context);

scpi_result_t NR_AMPLITUDE_ReflevelQ(scpi_t * context);
scpi_result_t NR_AMPLITUDE_ScaleValueQ(scpi_t * context);
scpi_result_t NR_AMPLITUDE_AutoAttenQ(scpi_t * context);
scpi_result_t NR_AMPLITUDE_AttenValueQ(scpi_t * context);
scpi_result_t NR_AMPLITUDE_PreampQ(scpi_t * context);
scpi_result_t NR_AMPLITUDE_RLevelOffsetQ(scpi_t * context);

#ifdef  __cplusplus
}
#endif

#endif // NR_SCPI_AMP_H
