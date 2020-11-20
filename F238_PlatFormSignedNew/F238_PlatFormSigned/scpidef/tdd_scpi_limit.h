#ifndef TDD_SCPI_LIMIT_H
#define TDD_SCPI_LIMIT_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TDD_SCPI_COMMANDS_LIMIT \
{"[:SENSe]:LIMit:TYPE", TDD_LIMIT_Type},/*{int}*/\
{"[:SENSe]:LIMit:MEASure:TYPE", TDD_LIMIT_MeasureType},/*{int}*/\
{"[:SENSe]:LIMit:TEST", TDD_LIMIT_TestOn},/*{int}*/\
{"[:SENSe]:LIMit:UPPer:VALue", TDD_LIMIT_UpperValue},/*{double}*/\
{"[:SENSe]:LIMit:LOWer:VALue", TDD_LIMIT_LowerValue},/*{double}*/\
{"[:SENSe]:LIMit:ALLOwed:CHANge", TDD_LIMIT_AllowedChange},/*{double}*/\
{"[:SENSe]:LIMit:ALLOn", TDD_LIMIT_AllOn},/*{none}*/\
{"[:SENSe]:LIMit:ALLClear", TDD_LIMIT_ClearAll},/*{none}*/\
\
{"[:SENSe]:LIMit:TYPE?", TDD_LIMIT_TypeQ},/*{int}*/\
{"[:SENSe]:LIMit:MEASure:TYPE?", TDD_LIMIT_MeasureTypeQ},/*{int}*/\
{"[:SENSe]:LIMit:TEST?", TDD_LIMIT_TestOnQ},/*{int}*/\
{"[:SENSe]:LIMit:UPPer:VALue?", TDD_LIMIT_UpperValueQ},/*{double}*/\
{"[:SENSe]:LIMit:LOWer:VALue?", TDD_LIMIT_LowerValueQ},/*{double}*/\
{"[:SENSe]:LIMit:ALLOwed:CHANge?", TDD_LIMIT_AllowedChangeQ},/*{double}*/\

scpi_result_t TDD_LIMIT_Type(scpi_t * context);
scpi_result_t TDD_LIMIT_MeasureType(scpi_t * context);
scpi_result_t TDD_LIMIT_TestOn(scpi_t * context);
scpi_result_t TDD_LIMIT_UpperValue(scpi_t * context);
scpi_result_t TDD_LIMIT_LowerValue(scpi_t * context);
scpi_result_t TDD_LIMIT_AllowedChange(scpi_t * context);
scpi_result_t TDD_LIMIT_AllOn(scpi_t * context);
scpi_result_t TDD_LIMIT_ClearAll(scpi_t * context);

scpi_result_t TDD_LIMIT_TypeQ(scpi_t * context);
scpi_result_t TDD_LIMIT_MeasureTypeQ(scpi_t * context);
scpi_result_t TDD_LIMIT_TestOnQ(scpi_t * context);
scpi_result_t TDD_LIMIT_UpperValueQ(scpi_t * context);
scpi_result_t TDD_LIMIT_LowerValueQ(scpi_t * context);
scpi_result_t TDD_LIMIT_AllowedChangeQ(scpi_t * context);

#ifdef __cplusplus
}
#endif

#endif // TDD_SCPI_LIMIT_H
