#ifndef SA_SCPI_AMP_H
#define SA_SCPI_AMP_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define SA_SCPI_COMMANDS_AMPLITUDE \
{"[:SENSe]:AMPLitude:SCALe:AUTO", SA_AMPLITUDE_AutoScale},/*{none}*/\
{"[:SENSe]:AMPLitude:RLEVel", SA_AMPLITUDE_Reflevel},/*{double}*/\
{"[:SENSe]:AMPLitude:SCALe", SA_AMPLITUDE_ScaleValue},/*{double}*/\
{"[:SENSe]:AMPLitude:ATTEnuation:AUTO", SA_AMPLITUDE_AutoAtten},/*{int}*/\
{"[:SENSe]:AMPLitude:ATTEnuation", SA_AMPLITUDE_AttenValue},/*{double}*/\
{"[:SENSe]:AMPLitude:PREAmp", SA_AMPLITUDE_Preamp},/*{int}*/\
{"[:SENSe]:AMPLitude:RLEVel:OFFSet", SA_AMPLITUDE_RLevelOffset},/*{double}*/\
{"[:SENSe]:AMPLitude:PDIVision", SA_AMPLITUDE_ScaleUnit},/*{int}*/\
\
{"[:SENSe]:AMPLitude:RLEVel?", SA_AMPLITUDE_ReflevelQ},/*{double}*/\
{"[:SENSe]:AMPLitude:SCALe?", SA_AMPLITUDE_ScaleValueQ},/*{double}*/\
{"[:SENSe]:AMPLitude:ATTEnuation:AUTO?", SA_AMPLITUDE_AutoAttenQ},/*{int}*/\
{"[:SENSe]:AMPLitude:ATTEnuation?", SA_AMPLITUDE_AttenValueQ},/*{double}*/\
{"[:SENSe]:AMPLitude:PREAmp?", SA_AMPLITUDE_PreampQ},/*{int}*/\
{"[:SENSe]:AMPLitude:RLEVel:OFFSet?", SA_AMPLITUDE_RLevelOffsetQ},/*{double}*/\
    /* 0 -- dBm 1 -- dBV 2 -- dBmV 3 -- dBuV 4 -- volt 5 -- watts */\
{"[:SENSe]:AMPLitude:PDIVision?", SA_AMPLITUDE_ScaleUnitQ},/*{int}*/\

scpi_result_t SA_AMPLITUDE_AutoScale(scpi_t * context);

scpi_result_t SA_AMPLITUDE_Reflevel(scpi_t * context);
scpi_result_t SA_AMPLITUDE_ScaleValue(scpi_t * context);
scpi_result_t SA_AMPLITUDE_AutoAtten(scpi_t * context);
scpi_result_t SA_AMPLITUDE_AttenValue(scpi_t * context);
scpi_result_t SA_AMPLITUDE_Preamp(scpi_t * context);
scpi_result_t SA_AMPLITUDE_RLevelOffset(scpi_t * context);
scpi_result_t SA_AMPLITUDE_ScaleUnit(scpi_t * context);

scpi_result_t SA_AMPLITUDE_ReflevelQ(scpi_t * context);
scpi_result_t SA_AMPLITUDE_ScaleValueQ(scpi_t * context);
scpi_result_t SA_AMPLITUDE_AutoAttenQ(scpi_t * context);
scpi_result_t SA_AMPLITUDE_AttenValueQ(scpi_t * context);
scpi_result_t SA_AMPLITUDE_PreampQ(scpi_t * context);
scpi_result_t SA_AMPLITUDE_RLevelOffsetQ(scpi_t * context);
scpi_result_t SA_AMPLITUDE_ScaleUnitQ(scpi_t * context);

#ifdef  __cplusplus
}
#endif

#endif // SA_SCPI_AMP_H
