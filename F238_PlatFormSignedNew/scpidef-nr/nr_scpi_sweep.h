#ifndef NR_SCPI_SWEEP_H
#define NR_SCPI_SWEEP_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define NR_SCPI_COMMANDS_SWEEP \
{"[:SENSe]:SWEEp:CONTinuous" ,NR_SWEEP_Type},          /* {Int}[1--cont 0--single]*/\
{"[:SENSe]:SWEEp:CONTinuous:ONCE" ,NR_SWEEP_Once},                                    \
\
{"[:SENSe]:SWEEp:CONTinuous?" ,NR_SWEEP_TypeQ},          /* {Int}[1--cont 0--single]*/\

scpi_result_t NR_SWEEP_Type(scpi_t * context);
scpi_result_t NR_SWEEP_Once(scpi_t * context);

scpi_result_t NR_SWEEP_TypeQ(scpi_t * context);

#ifdef  __cplusplus
}
#endif

#endif // NR_SCPI_SWEEP_H
