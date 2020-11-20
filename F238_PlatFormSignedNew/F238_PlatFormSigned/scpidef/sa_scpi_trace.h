#ifndef SA_SCPI_TRACE_H
#define SA_SCPI_TRACE_H


#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define VNC_TRACECNT   6
#define VNC_POINTCNT   801

#define SA_SCPI_COMMANDS_TRACE \
 {"[:SENSe]:TRACe:DISPlay", SA_TRACE_ViewStatus},/*{Int} [0 -- OFF 1 -- ON]*/\
 {"[:SENSe]:TRACe:1:DISPlay", SA_TRACE1_ViewStatus},/*{Int}*/\
 {"[:SENSe]:TRACe:2:DISPlay", SA_TRACE2_ViewStatus},/*{Int}*/\
 {"[:SENSe]:TRACe:3:DISPlay", SA_TRACE3_ViewStatus},/*{Int}*/\
 {"[:SENSe]:TRACe:4:DISPlay", SA_TRACE4_ViewStatus},/*{Int}*/\
 {"[:SENSe]:TRACe:5:DISPlay", SA_TRACE5_ViewStatus},/*{Int}*/\
 {"[:SENSe]:TRACe:6:DISPlay", SA_TRACE6_ViewStatus},/*{Int}*/\
 \
 /*[0 -- CLEAR_WRITE  1 -- MAX_HOLD 2 -- MIN_HOLD 3 -- VIEW 4 -- TRACE_AVE]*/ \
 {"[:SENSe]:TRACe:TYPE", SA_TRACE_Type},/*{Int} */\
 {"[:SENSe]:TRACe:1:TYPE", SA_TRACE1_Type},/*{Int}*/\
 {"[:SENSe]:TRACe:2:TYPE", SA_TRACE2_Type},/*{Int}*/\
 {"[:SENSe]:TRACe:3:TYPE", SA_TRACE3_Type},/*{Int}*/\
 {"[:SENSe]:TRACe:4:TYPE", SA_TRACE4_Type},/*{Int}*/\
 {"[:SENSe]:TRACe:5:TYPE", SA_TRACE5_Type},/*{Int}*/\
 {"[:SENSe]:TRACe:6:TYPE", SA_TRACE6_Type},/*{Int}*/\
\
{"[:SENSe]:TRACe:AVECount", SA_TRACE_AveCount},/*{Int} */\
{"[:SENSe]:TRACe:1:AVECount", SA_TRACE1_AveCount},/*{Int}*/\
{"[:SENSe]:TRACe:2:AVECount", SA_TRACE2_AveCount},/*{Int}*/\
{"[:SENSe]:TRACe:3:AVECount", SA_TRACE3_AveCount},/*{Int}*/\
{"[:SENSe]:TRACe:4:AVECount", SA_TRACE4_AveCount},/*{Int}*/\
{"[:SENSe]:TRACe:5:AVECount", SA_TRACE5_AveCount},/*{Int}*/\
{"[:SENSe]:TRACe:6:AVECount", SA_TRACE6_AveCount},/*{Int}*/\
/*[0 -- Auto 1 -- SA_POSITIVE_PEAK 2 -- SA_NEGATIVE_PEAK 3 -- SA_SAMPLE 4 -- SA_COMMON(Normal) 5 -- SA_AVERAGE_VOTAGE 6 -- SA_RMS ]*/\
{"[:SENSe]:TRACe:DETEctor", SA_TRACE_DetectorType},/*{Int}*/\
\
\
 {"[:SENSe]:TRACe:DISPlay?", SA_TRACE_ViewStatusQ},/*{Int} [0 -- OFF 1 -- ON]*/\
 {"[:SENSe]:TRACe:1:DISPlay?", SA_TRACE1_ViewStatusQ},/*{Int}*/\
 {"[:SENSe]:TRACe:2:DISPlay?", SA_TRACE2_ViewStatusQ},/*{Int}*/\
 {"[:SENSe]:TRACe:3:DISPlay?", SA_TRACE3_ViewStatusQ},/*{Int}*/\
 {"[:SENSe]:TRACe:4:DISPlay?", SA_TRACE4_ViewStatusQ},/*{Int}*/\
 {"[:SENSe]:TRACe:5:DISPlay?", SA_TRACE5_ViewStatusQ},/*{Int}*/\
 {"[:SENSe]:TRACe:6:DISPlay?", SA_TRACE6_ViewStatusQ},/*{Int}*/\
 {"[:SENSe]:TRACe:TYPE?", SA_TRACE_TypeQ},/*{Int} */\
 {"[:SENSe]:TRACe:1:TYPE?", SA_TRACE1_TypeQ},/*{Int}*/\
 {"[:SENSe]:TRACe:2:TYPE?", SA_TRACE2_TypeQ},/*{Int}*/\
 {"[:SENSe]:TRACe:3:TYPE?", SA_TRACE3_TypeQ},/*{Int}*/\
 {"[:SENSe]:TRACe:4:TYPE?", SA_TRACE4_TypeQ},/*{Int}*/\
 {"[:SENSe]:TRACe:5:TYPE?", SA_TRACE5_TypeQ},/*{Int}*/\
 {"[:SENSe]:TRACe:6:TYPE?", SA_TRACE6_TypeQ},/*{Int}*/\
{"[:SENSe]:TRACe:AVECount?", SA_TRACE_AveCountQ},/*{Int} */\
{"[:SENSe]:TRACe:1:AVECount?", SA_TRACE1_AveCountQ},/*{Int}*/\
{"[:SENSe]:TRACe:2:AVECount?", SA_TRACE2_AveCountQ},/*{Int}*/\
{"[:SENSe]:TRACe:3:AVECount?", SA_TRACE3_AveCountQ},/*{Int}*/\
{"[:SENSe]:TRACe:4:AVECount?", SA_TRACE4_AveCountQ},/*{Int}*/\
{"[:SENSe]:TRACe:5:AVECount?", SA_TRACE5_AveCountQ},/*{Int}*/\
{"[:SENSe]:TRACe:6:AVECount?", SA_TRACE6_AveCountQ},/*{Int}*/\
{"[:SENSe]:TRACe:DETEctor?", SA_TRACE_DetectorTypeQ},/*{Int}*/\
\
{"[:SENSe]:TRACe:DATA?", SA_TRACE_DataQ},/*{}*/\
{"[:SENSe]:TRACe:DATA:RAWData?", SA_TRACE_RawDataQ},/*{}*/\
{"[:SENSe]:TRACe:DATA:DRAWdata?", SA_TRACE_DrawDataQ},/*{}*/\

scpi_result_t SA_TRACE_ViewStatus(scpi_t * context);
scpi_result_t SA_TRACE1_ViewStatus(scpi_t * context);
scpi_result_t SA_TRACE2_ViewStatus(scpi_t * context);
scpi_result_t SA_TRACE3_ViewStatus(scpi_t * context);
scpi_result_t SA_TRACE4_ViewStatus(scpi_t * context);
scpi_result_t SA_TRACE5_ViewStatus(scpi_t * context);
scpi_result_t SA_TRACE6_ViewStatus(scpi_t * context);

scpi_result_t SA_TRACE_Type(scpi_t * context);
scpi_result_t SA_TRACE1_Type(scpi_t * context);
scpi_result_t SA_TRACE2_Type(scpi_t * context);
scpi_result_t SA_TRACE3_Type(scpi_t * context);
scpi_result_t SA_TRACE4_Type(scpi_t * context);
scpi_result_t SA_TRACE5_Type(scpi_t * context);
scpi_result_t SA_TRACE6_Type(scpi_t * context);

scpi_result_t SA_TRACE_AveCount(scpi_t * context);
scpi_result_t SA_TRACE1_AveCount(scpi_t * context);
scpi_result_t SA_TRACE2_AveCount(scpi_t * context);
scpi_result_t SA_TRACE3_AveCount(scpi_t * context);
scpi_result_t SA_TRACE4_AveCount(scpi_t * context);
scpi_result_t SA_TRACE5_AveCount(scpi_t * context);
scpi_result_t SA_TRACE6_AveCount(scpi_t * context);

scpi_result_t SA_TRACE_DetectorType(scpi_t * context);

scpi_result_t SA_TRACE_ViewStatusQ(scpi_t * context);
scpi_result_t SA_TRACE1_ViewStatusQ(scpi_t * context);
scpi_result_t SA_TRACE2_ViewStatusQ(scpi_t * context);
scpi_result_t SA_TRACE3_ViewStatusQ(scpi_t * context);
scpi_result_t SA_TRACE4_ViewStatusQ(scpi_t * context);
scpi_result_t SA_TRACE5_ViewStatusQ(scpi_t * context);
scpi_result_t SA_TRACE6_ViewStatusQ(scpi_t * context);

scpi_result_t SA_TRACE_TypeQ(scpi_t * context);
scpi_result_t SA_TRACE1_TypeQ(scpi_t * context);
scpi_result_t SA_TRACE2_TypeQ(scpi_t * context);
scpi_result_t SA_TRACE3_TypeQ(scpi_t * context);
scpi_result_t SA_TRACE4_TypeQ(scpi_t * context);
scpi_result_t SA_TRACE5_TypeQ(scpi_t * context);
scpi_result_t SA_TRACE6_TypeQ(scpi_t * context);

scpi_result_t SA_TRACE_AveCountQ(scpi_t * context);
scpi_result_t SA_TRACE1_AveCountQ(scpi_t * context);
scpi_result_t SA_TRACE2_AveCountQ(scpi_t * context);
scpi_result_t SA_TRACE3_AveCountQ(scpi_t * context);
scpi_result_t SA_TRACE4_AveCountQ(scpi_t * context);
scpi_result_t SA_TRACE5_AveCountQ(scpi_t * context);
scpi_result_t SA_TRACE6_AveCountQ(scpi_t * context);

scpi_result_t SA_TRACE_DetectorTypeQ(scpi_t * context);

scpi_result_t SA_TRACE_DataQ(scpi_t * context);
scpi_result_t SA_TRACE_RawDataQ(scpi_t * context);
scpi_result_t SA_TRACE_DrawDataQ(scpi_t * context);

#ifdef  __cplusplus
}
#endif

#endif // SA_SCPI_TRACE_H
