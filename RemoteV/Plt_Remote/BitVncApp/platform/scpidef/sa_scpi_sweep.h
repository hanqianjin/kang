#ifndef SA_SCPI_SWEEP_H
#define SA_SCPI_SWEEP_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define SA_SCPI_COMMANDS_SWEEP \
{"[:SENSe]:SWEEp:TIME:AUTO" ,SA_SWEEP_AutoTime}, /* {Int}*/\
{"[:SENSe]:SWEEp:TIME" ,SA_SWEEP_Time},          /* {double}*/\
{"[:SENSe]:SWEEp:CONTinuous" ,SA_SWEEP_Type},          /* {Int}[1--cont 0--single]*/\
\
{"[:SENSe]:SWEEp:TIME:AUTO?",SA_SWEEP_AutoTimeQ},/* {Int}*/\
{"[:SENSe]:SWEEp:TIME?" ,SA_SWEEP_TimeQ},         /* {double}*/\
{"[:SENSe]:SWEEp:CONTinuous?" ,SA_SWEEP_TypeQ},          /* {Int}[1--cont 0--single]*/\

scpi_result_t GetTimeVal(scpi_t *context,qreal *val);

scpi_result_t SA_SWEEP_AutoTime(scpi_t * context);
scpi_result_t SA_SWEEP_Time(scpi_t * context);
scpi_result_t SA_SWEEP_Type(scpi_t * context);

scpi_result_t SA_SWEEP_AutoTimeQ(scpi_t * context);
scpi_result_t SA_SWEEP_TimeQ(scpi_t * context);
scpi_result_t SA_SWEEP_TypeQ(scpi_t * context);
#ifdef  __cplusplus
}
#endif


#endif // SA_SCPI_SWEEP_H
