#ifndef NR_SCPI_LIMIT_H
#define NR_SCPI_LIMIT_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define NR_SCPI_COMMANDS_LIMIT \
{"[:SENSe]:LIMIt:TYPE", NR_LIMIT_Type},/*{none}*/\
{"[:SENSe]:LIMIt:UPPer:STATe", NR_LIMIT_UpperState},/*{double}*/\
{"[:SENSe]:LIMIt:UPPer:VALue", NR_LIMIT_UpperValue},/*{double}*/\
{"[:SENSe]:LIMIt:LOWer:STATe", NR_LIMIT_LowerState},/*{int}*/\
{"[:SENSe]:LIMIt:LOWer:VALue", NR_LIMIT_LowerValue},/*{double}*/\
{"[:SENSe]:LIMIt:ALLOn", NR_LIMIT_AllOn},/*{double}*/\
{"[:SENSe]:LIMIt:ALLClear", NR_LIMIT_ClearAll},/*{double}*/\
\
{"[:SENSe]:LIMIt:TYPE?", NR_LIMIT_TypeQ},/*{double}*/\
{"[:SENSe]:LIMIt:UPPer:STATe?", NR_LIMIT_UpperStateQ},/*{double}*/\
{"[:SENSe]:LIMIt:UPPer:VALue?", NR_LIMIT_UpperValueQ},/*{int}*/\
{"[:SENSe]:LIMIt:LOWer:STATe?", NR_LIMIT_LowerStateQ},/*{double}*/\
{"[:SENSe]:LIMIt:LOWer:VALue?", NR_LIMIT_LowerValueQ},/*{int}*/\

scpi_result_t NR_LIMIT_Type(scpi_t * context);
scpi_result_t NR_LIMIT_UpperState(scpi_t * context);
scpi_result_t NR_LIMIT_UpperValue(scpi_t * context);
scpi_result_t NR_LIMIT_LowerState(scpi_t * context);
scpi_result_t NR_LIMIT_LowerValue(scpi_t * context);
scpi_result_t NR_LIMIT_AllOn(scpi_t * context);
scpi_result_t NR_LIMIT_ClearAll(scpi_t * context);

scpi_result_t NR_LIMIT_TypeQ(scpi_t * context);
scpi_result_t NR_LIMIT_UpperStateQ(scpi_t * context);
scpi_result_t NR_LIMIT_UpperValueQ(scpi_t * context);
scpi_result_t NR_LIMIT_LowerStateQ(scpi_t * context);
scpi_result_t NR_LIMIT_LowerValueQ(scpi_t * context);

#ifdef  __cplusplus
}
#endif

#endif // NR_SCPI_LIMIT_H
