#ifndef SA_SCPI_LIMIT_H
#define SA_SCPI_LIMIT_H


#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"


#ifdef  __cplusplus
extern "C" {
#endif

#define SA_SCPI_COMMANDS_LIMIT \
{"[:SENSe]:LIMIt:SELEct"  ,SA_LIMIT_Select }, /* {Int} [1--6]*/\
{"[:SENSe]:LIMIt:SELEct?" ,SA_LIMIT_SelectQ}, /* {Int} [1--6]*/\
    \
{"[:SENSe]:LIMIt:DISPlay"    ,SA_LIMIT_DisplayState },  /* {Int}*/\
{"[:SENSe]:LIMIt:DISPlay?"   ,SA_LIMIT_DisplayStateQ},  /* {Int}*/\
{"[:SENSe]:LIMIt:1:DISPlay"  ,SA_LIMIT1_DisplayState }, /* {Int}*/\
{"[:SENSe]:LIMIt:1:DISPlay?" ,SA_LIMIT1_DisplayStateQ}, /* {Int}*/\
{"[:SENSe]:LIMIt:2:DISPlay"  ,SA_LIMIT2_DisplayState }, /* {Int}*/\
{"[:SENSe]:LIMIt:2:DISPlay?" ,SA_LIMIT2_DisplayStateQ}, /* {Int}*/\
{"[:SENSe]:LIMIt:3:DISPlay"  ,SA_LIMIT3_DisplayState }, /* {Int}*/\
{"[:SENSe]:LIMIt:3:DISPlay?" ,SA_LIMIT3_DisplayStateQ}, /* {Int}*/\
{"[:SENSe]:LIMIt:4:DISPlay"  ,SA_LIMIT4_DisplayState }, /* {Int}*/\
{"[:SENSe]:LIMIt:4:DISPlay?" ,SA_LIMIT4_DisplayStateQ}, /* {Int}*/\
{"[:SENSe]:LIMIt:5:DISPlay"  ,SA_LIMIT5_DisplayState }, /* {Int}*/\
{"[:SENSe]:LIMIt:5:DISPlay?" ,SA_LIMIT5_DisplayStateQ}, /* {Int}*/\
{"[:SENSe]:LIMIt:6:DISPlay"  ,SA_LIMIT6_DisplayState }, /* {Int}*/\
{"[:SENSe]:LIMIt:6:DISPlay?" ,SA_LIMIT6_DisplayStateQ}, /* {Int}*/\
    \
{"[:SENSe]:LIMIt:EDGE:STATe"  ,SA_LIMIT_EdgeState },     /* {Int}*/\
{"[:SENSe]:LIMIt:EDGE:STATe?" ,SA_LIMIT_EdgeStateQ},     /* {Double}*/\
{"[:SENSe]:LIMIt:1:EDGE:STATe"  ,SA_LIMIT1_EdgeState },  /* {Int}*/\
{"[:SENSe]:LIMIt:1:EDGE:STATe?" ,SA_LIMIT1_EdgeStateQ},  /* {Double}*/\
{"[:SENSe]:LIMIt:2:EDGE:STATe"  ,SA_LIMIT2_EdgeState },  /* {Int}*/\
{"[:SENSe]:LIMIt:2:EDGE:STATe?" ,SA_LIMIT2_EdgeStateQ},  /* {Double}*/\
{"[:SENSe]:LIMIt:3:EDGE:STATe"  ,SA_LIMIT3_EdgeState },  /* {Int}*/\
{"[:SENSe]:LIMIt:3:EDGE:STATe?" ,SA_LIMIT3_EdgeStateQ},  /* {Double}*/\
{"[:SENSe]:LIMIt:4:EDGE:STATe"  ,SA_LIMIT4_EdgeState },  /* {Int}*/\
{"[:SENSe]:LIMIt:4:EDGE:STATe?" ,SA_LIMIT4_EdgeStateQ},  /* {Double}*/\
{"[:SENSe]:LIMIt:5:EDGE:STATe"  ,SA_LIMIT5_EdgeState },  /* {Int}*/\
{"[:SENSe]:LIMIt:5:EDGE:STATe?" ,SA_LIMIT5_EdgeStateQ},  /* {Double}*/\
{"[:SENSe]:LIMIt:6:EDGE:STATe"  ,SA_LIMIT6_EdgeState },  /* {Int}*/\
{"[:SENSe]:LIMIt:6:EDGE:STATe?" ,SA_LIMIT6_EdgeStateQ},  /* {Double}*/\
    \
{"[:SENSe]:LIMIt:EDGE" ,SA_LIMIT_EdgeValue },  /* {Int}*/\
{"[:SENSe]:LIMIt:EDGE?" ,SA_LIMIT_EdgeValueQ},  /* {Int}*/\
{"[:SENSe]:LIMIt:1:EDGE" ,SA_LIMIT1_EdgeValue },  /* {Int}*/\
{"[:SENSe]:LIMIt:1:EDGE?" ,SA_LIMIT1_EdgeValueQ},  /* {Int}*/\
{"[:SENSe]:LIMIt:2:EDGE" ,SA_LIMIT2_EdgeValue },  /* {Int}*/\
{"[:SENSe]:LIMIt:2:EDGE?" ,SA_LIMIT2_EdgeValueQ},  /* {Int}*/\
{"[:SENSe]:LIMIt:3:EDGE" ,SA_LIMIT3_EdgeValue },  /* {Int}*/\
{"[:SENSe]:LIMIt:3:EDGE?" ,SA_LIMIT3_EdgeValueQ},  /* {Int}*/\
{"[:SENSe]:LIMIt:4:EDGE" ,SA_LIMIT4_EdgeValue },  /* {Int}*/\
{"[:SENSe]:LIMIt:4:EDGE?" ,SA_LIMIT4_EdgeValueQ},  /* {Int}*/\
{"[:SENSe]:LIMIt:5:EDGE" ,SA_LIMIT5_EdgeValue },  /* {Int}*/\
{"[:SENSe]:LIMIt:5:EDGE?" ,SA_LIMIT5_EdgeValueQ},  /* {Int}*/\
{"[:SENSe]:LIMIt:6:EDGE" ,SA_LIMIT6_EdgeValue },  /* {Int}*/\
{"[:SENSe]:LIMIt:6:EDGE?" ,SA_LIMIT6_EdgeValueQ},  /* {Int}*/\
\
{"[:SENSe]:LIMIt:TEST" ,SA_LIMIT_TestState },  /* {Int}*/\
{"[:SENSe]:LIMIt:TEST?" ,SA_LIMIT_TestStateQ},  /* {Int}*/\
\
{"[:SENSe]:LIMIt:TYPE" ,SA_LIMIT_Type },  /* {Int}*/\
{"[:SENSe]:LIMIt:TYPE?" ,SA_LIMIT_TypeQ},  /* {Int}*/\
{"[:SENSe]:LIMIt:1:TYPE" ,SA_LIMIT1_Type },  /* {Int}*/\
{"[:SENSe]:LIMIt:1:TYPE?" ,SA_LIMIT1_TypeQ},  /* {Int}*/\
{"[:SENSe]:LIMIt:2:TYPE" ,SA_LIMIT2_Type },  /* {Int}*/\
{"[:SENSe]:LIMIt:2:TYPE?" ,SA_LIMIT2_TypeQ},  /* {Int}*/\
{"[:SENSe]:LIMIt:3:TYPE" ,SA_LIMIT3_Type },  /* {Int}*/\
{"[:SENSe]:LIMIt:3:TYPE?" ,SA_LIMIT3_TypeQ},  /* {Int}*/\
{"[:SENSe]:LIMIt:4:TYPE" ,SA_LIMIT4_Type },  /* {Int}*/\
{"[:SENSe]:LIMIt:4:TYPE?" ,SA_LIMIT4_TypeQ},  /* {Int}*/\
{"[:SENSe]:LIMIt:5:TYPE" ,SA_LIMIT5_Type },  /* {Int}*/\
{"[:SENSe]:LIMIt:5:TYPE?" ,SA_LIMIT5_TypeQ},  /* {Int}*/\
{"[:SENSe]:LIMIt:6:TYPE" ,SA_LIMIT6_Type },  /* {Int}*/\
{"[:SENSe]:LIMIt:6:TYPE?" ,SA_LIMIT6_TypeQ},  /* {Int}*/\
\
{"[:SENSe]:LIMIt:ALL:DELEte" ,SA_LIMIT_AllDelete },  \
{"[:SENSe]:LIMIt:DELEte" ,SA_LIMIT_Delete },  \
{"[:SENSe]:LIMIt:1:DELEte" ,SA_LIMIT1_Delete },  \
{"[:SENSe]:LIMIt:2:DELEte" ,SA_LIMIT2_Delete },  \
{"[:SENSe]:LIMIt:3:DELEte" ,SA_LIMIT3_Delete },  \
{"[:SENSe]:LIMIt:4:DELEte" ,SA_LIMIT4_Delete },  \
{"[:SENSe]:LIMIt:5:DELEte" ,SA_LIMIT5_Delete },  \
{"[:SENSe]:LIMIt:6:DELEte" ,SA_LIMIT6_Delete },  \
\
{"[:SENSe]:LIMIt:AUTO",SA_LIMIT_Autolimit},  \
\
{"[:SENSe]:LIMIt:POINt:COUNt?",SA_LIMIT_PointCountQ}, \
\
{"[:SENSe]:LIMIt:POINt:DELEte",SA_LIMIT_DeletePoint},   /*{Int}*/\
\
{"[:SENSe]:LIMIt:POINt:DATA:FREQuency",SA_LIMIT_PointFreqData}, \
{"[:SENSe]:LIMIt:POINt:DATA:FREQuency?",SA_LIMIT_PointFreqDataQ}, \
{"[:SENSe]:LIMIt:POINt:DATA:AMPLitude",SA_LIMIT_PointAmptData}, \
{"[:SENSe]:LIMIt:POINt:DATA:AMPLitude?",SA_LIMIT_PointAmptDataQ}, \
{"[:SENSe]:LIMIt:POINt:DATA",SA_LIMIT_PointData}, \
\
{"[:SENSe]:LIMIt:INSErt",SA_LIMIT_LimitInsert}, \



scpi_result_t SA_LIMIT_Select(scpi_t * context);
scpi_result_t SA_LIMIT_SelectQ(scpi_t * context);

scpi_result_t SA_LIMIT_DisplayState(scpi_t * context);
scpi_result_t SA_LIMIT_DisplayStateQ(scpi_t * context);
scpi_result_t SA_LIMIT1_DisplayState(scpi_t * context);
scpi_result_t SA_LIMIT1_DisplayStateQ(scpi_t * context);
scpi_result_t SA_LIMIT2_DisplayState(scpi_t * context);
scpi_result_t SA_LIMIT2_DisplayStateQ(scpi_t * context);
scpi_result_t SA_LIMIT3_DisplayState(scpi_t * context);
scpi_result_t SA_LIMIT3_DisplayStateQ(scpi_t * context);
scpi_result_t SA_LIMIT4_DisplayState(scpi_t * context);
scpi_result_t SA_LIMIT4_DisplayStateQ(scpi_t * context);
scpi_result_t SA_LIMIT5_DisplayState(scpi_t * context);
scpi_result_t SA_LIMIT5_DisplayStateQ(scpi_t * context);
scpi_result_t SA_LIMIT6_DisplayState(scpi_t * context);
scpi_result_t SA_LIMIT6_DisplayStateQ(scpi_t * context);

scpi_result_t SA_LIMIT_EdgeState(scpi_t * context);
scpi_result_t SA_LIMIT_EdgeStateQ(scpi_t * context);
scpi_result_t SA_LIMIT1_EdgeState(scpi_t * context);
scpi_result_t SA_LIMIT1_EdgeStateQ(scpi_t * context);
scpi_result_t SA_LIMIT2_EdgeState(scpi_t * context);
scpi_result_t SA_LIMIT2_EdgeStateQ(scpi_t * context);
scpi_result_t SA_LIMIT3_EdgeState(scpi_t * context);
scpi_result_t SA_LIMIT3_EdgeStateQ(scpi_t * context);
scpi_result_t SA_LIMIT4_EdgeState(scpi_t * context);
scpi_result_t SA_LIMIT4_EdgeStateQ(scpi_t * context);
scpi_result_t SA_LIMIT5_EdgeState(scpi_t * context);
scpi_result_t SA_LIMIT5_EdgeStateQ(scpi_t * context);
scpi_result_t SA_LIMIT6_EdgeState(scpi_t * context);
scpi_result_t SA_LIMIT6_EdgeStateQ(scpi_t * context);

scpi_result_t SA_LIMIT_EdgeValue(scpi_t * context);
scpi_result_t SA_LIMIT_EdgeValueQ(scpi_t * context);
scpi_result_t SA_LIMIT1_EdgeValue(scpi_t * context);
scpi_result_t SA_LIMIT1_EdgeValueQ(scpi_t * context);
scpi_result_t SA_LIMIT2_EdgeValue(scpi_t * context);
scpi_result_t SA_LIMIT2_EdgeValueQ(scpi_t * context);
scpi_result_t SA_LIMIT3_EdgeValue(scpi_t * context);
scpi_result_t SA_LIMIT3_EdgeValueQ(scpi_t * context);
scpi_result_t SA_LIMIT4_EdgeValue(scpi_t * context);
scpi_result_t SA_LIMIT4_EdgeValueQ(scpi_t * context);
scpi_result_t SA_LIMIT5_EdgeValue(scpi_t * context);
scpi_result_t SA_LIMIT5_EdgeValueQ(scpi_t * context);
scpi_result_t SA_LIMIT6_EdgeValue(scpi_t * context);
scpi_result_t SA_LIMIT6_EdgeValueQ(scpi_t * context);

scpi_result_t SA_LIMIT_TestState(scpi_t * context);
scpi_result_t SA_LIMIT_TestStateQ(scpi_t * context);

scpi_result_t SA_LIMIT_Type(scpi_t * context);
scpi_result_t SA_LIMIT_TypeQ(scpi_t * context);
scpi_result_t SA_LIMIT1_Type(scpi_t * context);
scpi_result_t SA_LIMIT1_TypeQ(scpi_t * context);
scpi_result_t SA_LIMIT2_Type(scpi_t * context);
scpi_result_t SA_LIMIT2_TypeQ(scpi_t * context);
scpi_result_t SA_LIMIT3_Type(scpi_t * context);
scpi_result_t SA_LIMIT3_TypeQ(scpi_t * context);
scpi_result_t SA_LIMIT4_Type(scpi_t * context);
scpi_result_t SA_LIMIT4_TypeQ(scpi_t * context);
scpi_result_t SA_LIMIT5_Type(scpi_t * context);
scpi_result_t SA_LIMIT5_TypeQ(scpi_t * context);
scpi_result_t SA_LIMIT6_Type(scpi_t * context);
scpi_result_t SA_LIMIT6_TypeQ(scpi_t * context);

scpi_result_t SA_LIMIT_AllDelete(scpi_t * context);
scpi_result_t SA_LIMIT_Delete(scpi_t * context);
scpi_result_t SA_LIMIT1_Delete(scpi_t * context);
scpi_result_t SA_LIMIT2_Delete(scpi_t * context);
scpi_result_t SA_LIMIT3_Delete(scpi_t * context);
scpi_result_t SA_LIMIT4_Delete(scpi_t * context);
scpi_result_t SA_LIMIT5_Delete(scpi_t * context);
scpi_result_t SA_LIMIT6_Delete(scpi_t * context);

scpi_result_t SA_LIMIT_Autolimit(scpi_t * context);

scpi_result_t SA_LIMIT_PointCountQ(scpi_t * context);
scpi_result_t SA_LIMIT_DeletePoint(scpi_t * context);
scpi_result_t SA_LIMIT_PointFreqData(scpi_t * context);
scpi_result_t SA_LIMIT_PointFreqDataQ(scpi_t * context);
scpi_result_t SA_LIMIT_PointAmptData(scpi_t * context);
scpi_result_t SA_LIMIT_PointAmptDataQ(scpi_t * context);
scpi_result_t SA_LIMIT_LimitInsert(scpi_t * context);
scpi_result_t SA_LIMIT_PointData(scpi_t * context);


#ifdef  __cplusplus
}
#endif

#endif // SA_SCPI_LIMIT_H
