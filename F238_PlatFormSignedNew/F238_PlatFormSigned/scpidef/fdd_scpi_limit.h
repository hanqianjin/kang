#ifndef FDD_SCPI_LIMIT_H
#define FDD_SCPI_LIMIT_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FDD_SCPI_COMMANDS_LIMIT \
{"[:SENSe]:LIMit:TYPE", FDD_LIMIT_Type},/*{int}*/\
{"[:SENSe]:LIMit:MEASure:TYPE", FDD_LIMIT_MeasureType},/*{int}*/\
{"[:SENSe]:LIMit:TEST", FDD_LIMIT_TestOn},/*{int}*/\
{"[:SENSe]:LIMit:UPPer:VALue", FDD_LIMIT_UpperValue},/*{double}*/\
{"[:SENSe]:LIMit:LOWer:VALue", FDD_LIMIT_LowerValue},/*{double}*/\
{"[:SENSe]:LIMit:ALLOwed:CHANge", FDD_LIMIT_AllowedChange},/*{double}*/\
{"[:SENSe]:LIMit:ALLOn", FDD_LIMIT_AllOn},/*{none}*/\
{"[:SENSe]:LIMit:ALLClear", FDD_LIMIT_ClearAll},/*{none}*/\
\
{"[:SENSe]:LIMit:TYPE?", FDD_LIMIT_TypeQ},/*{int}*/\
{"[:SENSe]:LIMit:MEASure:TYPE?", FDD_LIMIT_MeasureTypeQ},/*{int}*/\
{"[:SENSe]:LIMit:TEST?", FDD_LIMIT_TestOnQ},/*{int}*/\
{"[:SENSe]:LIMit:UPPer:VALue?", FDD_LIMIT_UpperValueQ},/*{double}*/\
{"[:SENSe]:LIMit:LOWer:VALue?", FDD_LIMIT_LowerValueQ},/*{double}*/\
{"[:SENSe]:LIMit:ALLOwed:CHANge?", FDD_LIMIT_AllowedChangeQ},/*{double}*/\

scpi_result_t FDD_LIMIT_Type(scpi_t * context);
scpi_result_t FDD_LIMIT_MeasureType(scpi_t * context);
scpi_result_t FDD_LIMIT_TestOn(scpi_t * context);
scpi_result_t FDD_LIMIT_UpperValue(scpi_t * context);
scpi_result_t FDD_LIMIT_LowerValue(scpi_t * context);
scpi_result_t FDD_LIMIT_AllowedChange(scpi_t * context);
scpi_result_t FDD_LIMIT_AllOn(scpi_t * context);
scpi_result_t FDD_LIMIT_ClearAll(scpi_t * context);

scpi_result_t FDD_LIMIT_TypeQ(scpi_t * context);
scpi_result_t FDD_LIMIT_MeasureTypeQ(scpi_t * context);
scpi_result_t FDD_LIMIT_TestOnQ(scpi_t * context);
scpi_result_t FDD_LIMIT_UpperValueQ(scpi_t * context);
scpi_result_t FDD_LIMIT_LowerValueQ(scpi_t * context);
scpi_result_t FDD_LIMIT_AllowedChangeQ(scpi_t * context);

#ifdef __cplusplus
}
#endif

#endif // FDD_SCPI_LIMIT_H
