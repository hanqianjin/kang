#ifndef NR_SCPI_BW_H
#define NR_SCPI_BW_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define NR_SCPI_COMMANDS_BANDWIDTH \
{"[:SENSe]:IFOUtput", NR_BANDWIDTH_IFOutPut},/*{Int}*/\
\
{"[:SENSe]:IFOUtput?", NR_BANDWIDTH_IFOutPutQ},/*{Int}*/\

scpi_result_t NR_BANDWIDTH_IFOutPut(scpi_t * context);

scpi_result_t NR_BANDWIDTH_IFOutPutQ(scpi_t * context);


#ifdef  __cplusplus
}
#endif

#endif // NR_SCPI_BW_H
