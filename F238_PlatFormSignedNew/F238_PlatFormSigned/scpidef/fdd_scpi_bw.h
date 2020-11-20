#ifndef FDD_SCPI_BW_H
#define FDD_SCPI_BW_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FDD_SCPI_COMMANDS_BANDWIDTH \
{"[:SENSe]:IFOUtput", FDD_BANDWIDTH_IFOutPut},/*{int}*/\
\
{"[:SENSe]:IFOUtput?", FDD_BANDWIDTH_IFOutPutQ},/*{int}*/\

scpi_result_t FDD_BANDWIDTH_IFOutPut(scpi_t * context);

scpi_result_t FDD_BANDWIDTH_IFOutPutQ(scpi_t * context);

#ifdef __cplusplus
}
#endif

#endif // FDD_SCPI_BW_H
