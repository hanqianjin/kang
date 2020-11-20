#ifndef TDD_SCPI_BW_H
#define TDD_SCPI_BW_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TDD_SCPI_COMMANDS_BANDWIDTH \
{"[:SENSe]:IFOUtput", TDD_BANDWIDTH_IFOutPut},/*{int}*/\
\
{"[:SENSe]:IFOUtput?", TDD_BANDWIDTH_IFOutPutQ},/*{int}*/\

scpi_result_t TDD_BANDWIDTH_IFOutPut(scpi_t * context);

scpi_result_t TDD_BANDWIDTH_IFOutPutQ(scpi_t * context);

#ifdef __cplusplus
}
#endif

#endif // TDD_SCPI_BW_H
