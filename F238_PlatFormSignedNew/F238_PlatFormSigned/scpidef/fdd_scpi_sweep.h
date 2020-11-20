#ifndef FDD_SCPI_SWEEP_H
#define FDD_SCPI_SWEEP_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FDD_SCPI_COMMANDS_SWEEP \
{"[:SENSe]:SWEEp:CONTinuous", FDD_SWEEP_Type},/*{int}[1--continuous 0--single]*/\
{"[:SENSe]:SWEEp:ONCE", FDD_SWEEP_Once},/*{none}*/\
\
{"[:SENSe]:SWEEp:CONTinuous?", FDD_SWEEP_TypeQ},/*{int}[1--continuous 0--single]*/\

scpi_result_t FDD_SWEEP_Type(scpi_t * context);
scpi_result_t FDD_SWEEP_Once(scpi_t * context);

scpi_result_t FDD_SWEEP_TypeQ(scpi_t * context);

#ifdef __cplusplus
}
#endif

#endif // FDD_SCPI_SWEEP_H
