#ifndef SA_SCPI_AMP_H
#define SA_SCPI_AMP_H


#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef  __cplusplus
extern "C" {
#endif


#define SCPI_COMMANDS_AMPLITUDE \
{"[:SENSe]:AMPLitude:REFL", SA_FREQUENCY_Center_Freq},/*{Int}*/\

scpi_result_t SA_AMPLITUDE_Reflevel(scpi_t * context);
#ifdef  __cplusplus
}
#endif
#endif // SA_SCPI_AMP_H
