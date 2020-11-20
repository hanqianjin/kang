#ifndef RTSA_SCPI_AMP_H
#define RTSA_SCPI_AMP_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define RTSA_SCPI_COMMANDS_AMPLITUDE \
{"[:SENSe]:AMPLitude:SCALe:AUTO", RTSA_AMPLITUDE_AutoScale},/*{none}*/\
{"[:SENSe]:AMPLitude:RLEVel", RTSA_AMPLITUDE_Reflevel},/*{double}*/\
{"[:SENSe]:AMPLitude:SCALe", RTSA_AMPLITUDE_ScaleValue},/*{double}*/\
{"[:SENSe]:AMPLitude:ATTEnuation:AUTO", RTSA_AMPLITUDE_AutoAtten},/*{int}*/\
{"[:SENSe]:AMPLitude:ATTEnuation", RTSA_AMPLITUDE_AttenValue},/*{double}*/\
{"[:SENSe]:AMPLitude:PREAmp", RTSA_AMPLITUDE_Preamp},/*{int}*/\
{"[:SENSe]:AMPLitude:RLEVel:OFFSet", RTSA_AMPLITUDE_RLevelOffset},/*{double}*/\
{"[:SENSe]:AMPLitude:PDIVision", RTSA_AMPLITUDE_ScaleUnit},/*{int}*/\
\
{"[:SENSe]:AMPLitude:RLEVel?", RTSA_AMPLITUDE_ReflevelQ},/*{double}*/\
{"[:SENSe]:AMPLitude:SCALe?", RTSA_AMPLITUDE_ScaleValueQ},/*{double}*/\
{"[:SENSe]:AMPLitude:ATTEnuation:AUTO?", RTSA_AMPLITUDE_AutoAttenQ},/*{int}*/\
{"[:SENSe]:AMPLitude:ATTEnuation?", RTSA_AMPLITUDE_AttenValueQ},/*{double}*/\
{"[:SENSe]:AMPLitude:PREAmp?", RTSA_AMPLITUDE_PreampQ},/*{int}*/\
{"[:SENSe]:AMPLitude:RLEVel:OFFSet?", RTSA_AMPLITUDE_RLevelOffsetQ},/*{double}*/\
    /* 0 -- dBm 1 -- dBV 2 -- dBmV 3 -- dBuV 4 -- volt 5 -- watts */\
{"[:SENSe]:AMPLitude:PDIVision?", RTSA_AMPLITUDE_ScaleUnitQ},/*{int}*/\

scpi_result_t RTSA_AMPLITUDE_AutoScale(scpi_t * context);

scpi_result_t RTSA_AMPLITUDE_Reflevel(scpi_t * context);
scpi_result_t RTSA_AMPLITUDE_ScaleValue(scpi_t * context);
scpi_result_t RTSA_AMPLITUDE_AutoAtten(scpi_t * context);
scpi_result_t RTSA_AMPLITUDE_AttenValue(scpi_t * context);
scpi_result_t RTSA_AMPLITUDE_Preamp(scpi_t * context);
scpi_result_t RTSA_AMPLITUDE_RLevelOffset(scpi_t * context);
scpi_result_t RTSA_AMPLITUDE_ScaleUnit(scpi_t * context);

scpi_result_t RTSA_AMPLITUDE_ReflevelQ(scpi_t * context);
scpi_result_t RTSA_AMPLITUDE_ScaleValueQ(scpi_t * context);
scpi_result_t RTSA_AMPLITUDE_AutoAttenQ(scpi_t * context);
scpi_result_t RTSA_AMPLITUDE_AttenValueQ(scpi_t * context);
scpi_result_t RTSA_AMPLITUDE_PreampQ(scpi_t * context);
scpi_result_t RTSA_AMPLITUDE_RLevelOffsetQ(scpi_t * context);
scpi_result_t RTSA_AMPLITUDE_ScaleUnitQ(scpi_t * context);

#ifdef  __cplusplus
}
#endif


#endif // RTSA_SCPI_AMP_H
