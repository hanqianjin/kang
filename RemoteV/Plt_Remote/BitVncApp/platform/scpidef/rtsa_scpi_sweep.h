#ifndef RTSA_SCPI_SWEEP_H
#define RTSA_SCPI_SWEEP_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define RTSA_SCPI_COMMANDS_SWEEP \
{"[:SENSe]:SWEEp:CONTinuous" ,RTSA_SWEEP_Type},          /* {Int}[1--cont 0--single]*/\
{"[:SENSe]:SWEEp:CONTinuous:ONCE" ,RTSA_SWEEP_Once},                                    \
{"[:SENSe]:SWEEp:ACQtime:AUTO" ,RTSA_SWEEP_Acqtime_Auto},          /* {Int}[1--auto 0--manual]*/\
{"[:SENSe]:SWEEp:ACQtime" ,RTSA_SWEEP_Acqtime},          /* {double}*/\
\
{"[:SENSe]:SWEEp:CONTinuous?" ,RTSA_SWEEP_TypeQ},          /* {Int}[1--cont 0--single]*/\
{"[:SENSe]:SWEEp:ACQtime:AUTO?" ,RTSA_SWEEP_Acqtime_AutoQ},          /* {Int}[1--auto 0--manual]*/\
{"[:SENSe]:SWEEp:ACQtime?" ,RTSA_SWEEP_AcqtimeQ},          /* {double}*/\

scpi_result_t RTSA_SWEEP_Type(scpi_t * context);
scpi_result_t RTSA_SWEEP_Once(scpi_t * context);
scpi_result_t RTSA_SWEEP_Acqtime_Auto(scpi_t * context);
scpi_result_t RTSA_SWEEP_Acqtime(scpi_t * context);

scpi_result_t RTSA_SWEEP_TypeQ(scpi_t * context);
scpi_result_t RTSA_SWEEP_Acqtime_AutoQ(scpi_t * context);
scpi_result_t RTSA_SWEEP_AcqtimeQ(scpi_t * context);

#ifdef  __cplusplus
}
#endif

#endif // RTSA_SCPI_SWEEP_H
