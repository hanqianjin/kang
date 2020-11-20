#ifndef NR_SCPI_TRACE_H
#define NR_SCPI_TRACE_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define NR_SCPI_COMMANDS_TRACE \
{"[:SENSe]:TRACe:SELect", NR_TRACE_Select},/*{Int}*/\
{"[:SENSe]:TRACe:DISPlay", NR_TRACE_ViewStatus},/*{Int}*/\
{"[:SENSe]:TRACe:1:DISPlay", NR_TRACE1_ViewStatus},/*{Int}*/\
{"[:SENSe]:TRACe:2:DISPlay", NR_TRACE2_ViewStatus},/*{Int}*/\
{"[:SENSe]:TRACe:3:DISPlay", NR_TRACE3_ViewStatus},/*{Int}*/\
{"[:SENSe]:TRACe:4:DISPlay", NR_TRACE4_ViewStatus},/*{Int}*/\
{"[:SENSe]:TRACe:5:DISPlay", NR_TRACE5_ViewStatus},/*{Int}*/\
{"[:SENSe]:TRACe:6:DISPlay", NR_TRACE6_ViewStatus},/*{Int}*/\
{"[:SENSe]:TRACe:TYPE", NR_TRACE_Type},/*{Int}*/\
{"[:SENSe]:TRACe:1:TYPE", NR_TRACE1_Type},/*{Int}*/\
{"[:SENSe]:TRACe:2:TYPE", NR_TRACE2_Type},/*{Int}*/\
{"[:SENSe]:TRACe:3:TYPE", NR_TRACE3_Type},/*{Int}*/\
{"[:SENSe]:TRACe:4:TYPE", NR_TRACE4_Type},/*{Int}*/\
{"[:SENSe]:TRACe:5:TYPE", NR_TRACE5_Type},/*{Int}*/\
{"[:SENSe]:TRACe:6:TYPE", NR_TRACE6_Type},/*{Int}*/\
{"[:SENSe]:TRACe:AVECount", NR_TRACE_AveCount},/*{Int} */\
{"[:SENSe]:TRACe:DETEctor", NR_TRACE_DetectorType},/*{Int}*/\
{"[:SENSe]:TRACe:ALLOn", NR_TRACE_AllOn},/*{Int} */\
{"[:SENSe]:TRACe:ALLClear", NR_TRACE_ClearAll},/*{Int}*/\
    \
{"[:SENSe]:TRACe:SELect?", NR_TRACE_SelectQ},/*{Int}*/\
{"[:SENSe]:TRACe:DISPlay?", NR_TRACE_ViewStatusQ},/*{Int}*/\
{"[:SENSe]:TRACe:1:DISPlay?", NR_TRACE1_ViewStatusQ},/*{Int}*/\
{"[:SENSe]:TRACe:2:DISPlay?", NR_TRACE2_ViewStatusQ},/*{Int}*/\
{"[:SENSe]:TRACe:3:DISPlay?", NR_TRACE3_ViewStatusQ},/*{Int}*/\
{"[:SENSe]:TRACe:4:DISPlay?", NR_TRACE4_ViewStatusQ},/*{Int}*/\
{"[:SENSe]:TRACe:5:DISPlay?", NR_TRACE5_ViewStatusQ},/*{Int}*/\
{"[:SENSe]:TRACe:6:DISPlay?", NR_TRACE6_ViewStatusQ},/*{Int}*/\
{"[:SENSe]:TRACe:TYPE?", NR_TRACE_TypeQ},/*{Int}*/\
{"[:SENSe]:TRACe:1:TYPE?", NR_TRACE1_TypeQ},/*{Int}*/\
{"[:SENSe]:TRACe:2:TYPE?", NR_TRACE2_TypeQ},/*{Int}*/\
{"[:SENSe]:TRACe:3:TYPE?", NR_TRACE3_TypeQ},/*{Int}*/\
{"[:SENSe]:TRACe:4:TYPE?", NR_TRACE4_TypeQ},/*{Int}*/\
{"[:SENSe]:TRACe:5:TYPE?", NR_TRACE5_TypeQ},/*{Int}*/\
{"[:SENSe]:TRACe:6:TYPE?", NR_TRACE6_TypeQ},/*{Int}*/\
{"[:SENSe]:TRACe:AVECount?", NR_TRACE_AveCountQ},/*{Int} */\
{"[:SENSe]:TRACe:DETEctor?", NR_TRACE_DetectorTypeQ},/*{Int}*/\

scpi_result_t NR_TRACE_Select(scpi_t * context);

scpi_result_t NR_TRACE_ViewStatus(scpi_t * context);
scpi_result_t NR_TRACE1_ViewStatus(scpi_t * context);
scpi_result_t NR_TRACE2_ViewStatus(scpi_t * context);
scpi_result_t NR_TRACE3_ViewStatus(scpi_t * context);
scpi_result_t NR_TRACE4_ViewStatus(scpi_t * context);
scpi_result_t NR_TRACE5_ViewStatus(scpi_t * context);
scpi_result_t NR_TRACE6_ViewStatus(scpi_t * context);

scpi_result_t NR_TRACE_Type(scpi_t * context);
scpi_result_t NR_TRACE1_Type(scpi_t * context);
scpi_result_t NR_TRACE2_Type(scpi_t * context);
scpi_result_t NR_TRACE3_Type(scpi_t * context);
scpi_result_t NR_TRACE4_Type(scpi_t * context);
scpi_result_t NR_TRACE5_Type(scpi_t * context);
scpi_result_t NR_TRACE6_Type(scpi_t * context);

scpi_result_t NR_TRACE_AveCount(scpi_t * context);
scpi_result_t NR_TRACE_DetectorType(scpi_t * context);
scpi_result_t NR_TRACE_AllOn(scpi_t * context);
scpi_result_t NR_TRACE_ClearAll(scpi_t * context);

scpi_result_t NR_TRACE_SelectQ(scpi_t * context);

scpi_result_t NR_TRACE_ViewStatusQ(scpi_t * context);
scpi_result_t NR_TRACE1_ViewStatusQ(scpi_t * context);
scpi_result_t NR_TRACE2_ViewStatusQ(scpi_t * context);
scpi_result_t NR_TRACE3_ViewStatusQ(scpi_t * context);
scpi_result_t NR_TRACE4_ViewStatusQ(scpi_t * context);
scpi_result_t NR_TRACE5_ViewStatusQ(scpi_t * context);
scpi_result_t NR_TRACE6_ViewStatusQ(scpi_t * context);

scpi_result_t NR_TRACE_TypeQ(scpi_t * context);
scpi_result_t NR_TRACE1_TypeQ(scpi_t * context);
scpi_result_t NR_TRACE2_TypeQ(scpi_t * context);
scpi_result_t NR_TRACE3_TypeQ(scpi_t * context);
scpi_result_t NR_TRACE4_TypeQ(scpi_t * context);
scpi_result_t NR_TRACE5_TypeQ(scpi_t * context);
scpi_result_t NR_TRACE6_TypeQ(scpi_t * context);

scpi_result_t NR_TRACE_AveCountQ(scpi_t * context);
scpi_result_t NR_TRACE_DetectorTypeQ(scpi_t * context);

#ifdef  __cplusplus
}
#endif

#endif // NR_SCPI_TRACE_H
