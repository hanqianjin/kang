#ifndef FDD_SCPI_TRACE_H
#define FDD_SCPI_TRACE_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FDD_SCPI_COMMANDS_TRACE \
{"[:SENSe]:TRACe:SELEct", FDD_TRACE_Select},/*{int}*/\
{"[:SENSe]:TRACe:DISPlay", FDD_TRACE_ViewStatus},/*{int}*/\
{"[:SENSe]:TRACe:1:DISPlay", FDD_TRACE1_ViewStatus},/*{int}*/\
{"[:SENSe]:TRACe:2:DISPlay", FDD_TRACE2_ViewStatus},/*{int}*/\
{"[:SENSe]:TRACe:3:DISPlay", FDD_TRACE3_ViewStatus},/*{int}*/\
{"[:SENSe]:TRACe:4:DISPlay", FDD_TRACE4_ViewStatus},/*{int}*/\
{"[:SENSe]:TRACe:5:DISPlay", FDD_TRACE5_ViewStatus},/*{int}*/\
{"[:SENSe]:TRACe:6:DISPlay", FDD_TRACE6_ViewStatus},/*{int}*/\
{"[:SENSe]:TRACe:TYPE", FDD_TRACE_Type},/*{int}*/\
{"[:SENSe]:TRACe:1:TYPE", FDD_TRACE1_Type},/*{int}*/\
{"[:SENSe]:TRACe:2:TYPE", FDD_TRACE2_Type},/*{int}*/\
{"[:SENSe]:TRACe:3:TYPE", FDD_TRACE3_Type},/*{int}*/\
{"[:SENSe]:TRACe:4:TYPE", FDD_TRACE4_Type},/*{int}*/\
{"[:SENSe]:TRACe:5:TYPE", FDD_TRACE5_Type},/*{int}*/\
{"[:SENSe]:TRACe:6:TYPE", FDD_TRACE6_Type},/*{int}*/\
{"[:SENSe]:TRACe:AVECount", FDD_TRACE_AveCount},/*{int}*/\
{"[:SENSe]:TRACe:DETEctor", FDD_TRACE_DetectorType},/*{int}*/\
{"[:SENSe]:TRACe:ALLOn", FDD_TRACE_AllOn},/*{int}*/\
{"[:SENSe]:TRACe:ALLClear", FDD_TRACE_ClearAll},/*{int}*/\
\
{"[:SENSe]:TRACe:SELEct?", FDD_TRACE_SelectQ},/*{int}*/\
{"[:SENSe]:TRACe:DISPlay?", FDD_TRACE_ViewStatusQ},/*{int}*/\
{"[:SENSe]:TRACe:1:DISPlay?", FDD_TRACE1_ViewStatusQ},/*{int}*/\
{"[:SENSe]:TRACe:2:DISPlay?", FDD_TRACE2_ViewStatusQ},/*{int}*/\
{"[:SENSe]:TRACe:3:DISPlay?", FDD_TRACE3_ViewStatusQ},/*{int}*/\
{"[:SENSe]:TRACe:4:DISPlay?", FDD_TRACE4_ViewStatusQ},/*{int}*/\
{"[:SENSe]:TRACe:5:DISPlay?", FDD_TRACE5_ViewStatusQ},/*{int}*/\
{"[:SENSe]:TRACe:6:DISPlay?", FDD_TRACE6_ViewStatusQ},/*{int}*/\
{"[:SENSe]:TRACe:TYPE?", FDD_TRACE_TypeQ},/*{int}*/\
{"[:SENSe]:TRACe:1:TYPE?", FDD_TRACE1_TypeQ},/*{int}*/\
{"[:SENSe]:TRACe:2:TYPE?", FDD_TRACE2_TypeQ},/*{int}*/\
{"[:SENSe]:TRACe:3:TYPE?", FDD_TRACE3_TypeQ},/*{int}*/\
{"[:SENSe]:TRACe:4:TYPE?", FDD_TRACE4_TypeQ},/*{int}*/\
{"[:SENSe]:TRACe:5:TYPE?", FDD_TRACE5_TypeQ},/*{int}*/\
{"[:SENSe]:TRACe:6:TYPE?", FDD_TRACE6_TypeQ},/*{int}*/\
{"[:SENSe]:TRACe:AVECount?", FDD_TRACE_AveCountQ},/*{int}*/\
{"[:SENSe]:TRACe:DETEctor?", FDD_TRACE_DetectorTypeQ},/*{int}*/\

scpi_result_t FDD_TRACE_Select(scpi_t * context);
scpi_result_t FDD_TRACE_ViewStatus(scpi_t * context);
scpi_result_t FDD_TRACE1_ViewStatus(scpi_t * context);
scpi_result_t FDD_TRACE2_ViewStatus(scpi_t * context);
scpi_result_t FDD_TRACE3_ViewStatus(scpi_t * context);
scpi_result_t FDD_TRACE4_ViewStatus(scpi_t * context);
scpi_result_t FDD_TRACE5_ViewStatus(scpi_t * context);
scpi_result_t FDD_TRACE6_ViewStatus(scpi_t * context);
scpi_result_t FDD_TRACE_Type(scpi_t * context);
scpi_result_t FDD_TRACE1_Type(scpi_t * context);
scpi_result_t FDD_TRACE2_Type(scpi_t * context);
scpi_result_t FDD_TRACE3_Type(scpi_t * context);
scpi_result_t FDD_TRACE4_Type(scpi_t * context);
scpi_result_t FDD_TRACE5_Type(scpi_t * context);
scpi_result_t FDD_TRACE6_Type(scpi_t * context);
scpi_result_t FDD_TRACE_AveCount(scpi_t * context);
scpi_result_t FDD_TRACE_DetectorType(scpi_t * context);
scpi_result_t FDD_TRACE_AllOn(scpi_t * context);
scpi_result_t FDD_TRACE_ClearAll(scpi_t * context);

scpi_result_t FDD_TRACE_SelectQ(scpi_t * context);
scpi_result_t FDD_TRACE_ViewStatusQ(scpi_t * context);
scpi_result_t FDD_TRACE1_ViewStatusQ(scpi_t * context);
scpi_result_t FDD_TRACE2_ViewStatusQ(scpi_t * context);
scpi_result_t FDD_TRACE3_ViewStatusQ(scpi_t * context);
scpi_result_t FDD_TRACE4_ViewStatusQ(scpi_t * context);
scpi_result_t FDD_TRACE5_ViewStatusQ(scpi_t * context);
scpi_result_t FDD_TRACE6_ViewStatusQ(scpi_t * context);
scpi_result_t FDD_TRACE_TypeQ(scpi_t * context);
scpi_result_t FDD_TRACE1_TypeQ(scpi_t * context);
scpi_result_t FDD_TRACE2_TypeQ(scpi_t * context);
scpi_result_t FDD_TRACE3_TypeQ(scpi_t * context);
scpi_result_t FDD_TRACE4_TypeQ(scpi_t * context);
scpi_result_t FDD_TRACE5_TypeQ(scpi_t * context);
scpi_result_t FDD_TRACE6_TypeQ(scpi_t * context);
scpi_result_t FDD_TRACE_AveCountQ(scpi_t * context);
scpi_result_t FDD_TRACE_DetectorTypeQ(scpi_t * context);

#ifdef __cplusplus
}
#endif

#endif // FDD_SCPI_TRACE_H
