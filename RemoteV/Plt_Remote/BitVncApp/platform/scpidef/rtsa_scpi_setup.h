#ifndef RTSA_SCPI_SETUP_H
#define RTSA_SCPI_SETUP_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"


#ifdef  __cplusplus
extern "C" {
#endif


#define RTSA_SCPI_COMMANDS_SETUP \
{"[:SENSe]:DENSity:PERSistence:TIME:INFInite",RTSA_Density_PersistenceTimeInfinite},   /* {Int}*/\
{"[:SENSe]:DENSity:PERSistence:TIME",RTSA_Density_PersistenceTime},  /* {double}*/\
{"[:SENSe]:DENSity:HIGHest",RTSA_Density_Highest}, /* {Int}*/\
{"[:SENSe]:DENSity:LOWEst",RTSA_Density_Lowest}, /* {Int}*/\
{"[:SENSe]:DENSity:CURVe",RTSA_Density_Curve},  /* {double}*/\
\
{"[:SENSe]:DENSity:PERSistence:TIME:INFInite?",RTSA_Density_PersistenceTimeInfiniteQ}, /* {Int}*/\
{"[:SENSe]:DENSity:PERSistence:TIME?",RTSA_Density_PersistenceTimeQ}, /* {Int}*/\
{"[:SENSe]:DENSity:HIGHest?",RTSA_Density_HighestQ}, /* {Int}*/\
{"[:SENSe]:DENSity:LOWEst?",RTSA_Density_LowestQ}, /* {Int}*/\
{"[:SENSe]:DENSity:CURVe?",RTSA_Density_CurveQ}, /* {Int}*/\
{"[:SENSe]:DENSity:ADJUst",RTSA_Density_Adjust}, /* {Int}*/\

scpi_result_t RTSA_Density_PersistenceTimeInfinite(scpi_t * context);
scpi_result_t RTSA_Density_PersistenceTime(scpi_t * context);
scpi_result_t RTSA_Density_Highest(scpi_t * context);
scpi_result_t RTSA_Density_Lowest(scpi_t * context);
scpi_result_t RTSA_Density_Curve(scpi_t * context);



scpi_result_t RTSA_Density_PersistenceTimeInfiniteQ(scpi_t * context);
scpi_result_t RTSA_Density_PersistenceTimeQ(scpi_t * context);
scpi_result_t RTSA_Density_HighestQ(scpi_t * context);
scpi_result_t RTSA_Density_LowestQ(scpi_t * context);
scpi_result_t RTSA_Density_CurveQ(scpi_t * context);

scpi_result_t RTSA_Density_Adjust(scpi_t * context);

#ifdef  __cplusplus
}
#endif
#endif // RTSA_SCPI_SETUP_H
