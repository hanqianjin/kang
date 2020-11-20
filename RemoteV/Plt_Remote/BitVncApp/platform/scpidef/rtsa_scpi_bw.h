#ifndef RTSA_SCPI_BW_H
#define RTSA_SCPI_BW_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef  __cplusplus
extern "C" {
#endif


#define RTSA_SCPI_COMMANDS_BANDWIDTH \
{"[:SENSe]:BANDwidth:RBW:AUTO", RTSA_BANDWIDTH_AutoRbw},/*{Int}*/\
{"[:SENSe]:BANDwidth:RBW", RTSA_BANDWIDTH_Rbw},/*{Int}*/\
{"[:SENSe]:BANDwidth:FFTWindow", RTSA_BANDWIDTH_FFTWindow},/*{Int}*/\
\
{"[:SENSe]:BANDwidth:RBW:AUTO?", RTSA_BANDWIDTH_AutoRbwQ},/*{Int}*/\
{"[:SENSe]:BANDwidth:RBW?", RTSA_BANDWIDTH_RbwQ},/*{Int}*/\
{"[:SENSe]:BANDwidth:FFTWindow?", RTSA_BANDWIDTH_FFTWindowQ},/*{Int}*/\


scpi_result_t RTSA_BANDWIDTH_AutoRbw(scpi_t * context);
scpi_result_t RTSA_BANDWIDTH_Rbw(scpi_t * context);
scpi_result_t RTSA_BANDWIDTH_FFTWindow(scpi_t * context);

scpi_result_t RTSA_BANDWIDTH_AutoRbwQ(scpi_t * context);
scpi_result_t RTSA_BANDWIDTH_RbwQ(scpi_t * context);
scpi_result_t RTSA_BANDWIDTH_FFTWindowQ(scpi_t * context);


#ifdef  __cplusplus
}
#endif

#endif // RTSA_SCPI_BW_H
