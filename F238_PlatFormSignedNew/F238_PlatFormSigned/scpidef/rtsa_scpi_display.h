#ifndef RTSA_SCPI_DISPLAY_H
#define RTSA_SCPI_DISPLAY_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"


#ifdef  __cplusplus
extern "C" {
#endif

#define RTSA_SCPI_COMMANDS_DISPLAY \
{":DISPlay:VIEW", RTSA_DISPLAY_View},/*{Int}*/\
\
{":DISPlay:VIEW?", RTSA_DISPLAY_ViewQ},/*{Int}*/\


scpi_result_t RTSA_DISPLAY_View(scpi_t * context);

scpi_result_t RTSA_DISPLAY_ViewQ(scpi_t * context);


#ifdef  __cplusplus
}
#endif

#endif // RTSA_SCPI_DISPLAY_H
