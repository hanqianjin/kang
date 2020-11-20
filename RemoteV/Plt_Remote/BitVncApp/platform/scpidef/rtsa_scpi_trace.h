#ifndef RTSA_SCPI_TRACE_H
#define RTSA_SCPI_TRACE_H
#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"


#ifdef  __cplusplus
extern "C" {
#endif

#define VNC_TRACECNT   6
#define VNC_POINTCNT   801

#define RTSA_SCPI_COMMANDS_TRACE \
 {"[:SENSe]:TRACe:DISPlay", RTSA_TRACE_ViewStatus},/*{Int} [0 -- OFF 1 -- ON]*/\
 {"[:SENSe]:TRACe:1:DISPlay", RTSA_TRACE1_ViewStatus},/*{Int}*/\
 {"[:SENSe]:TRACe:2:DISPlay", RTSA_TRACE2_ViewStatus},/*{Int}*/\
 {"[:SENSe]:TRACe:3:DISPlay", RTSA_TRACE3_ViewStatus},/*{Int}*/\
 {"[:SENSe]:TRACe:4:DISPlay", RTSA_TRACE4_ViewStatus},/*{Int}*/\
 {"[:SENSe]:TRACe:5:DISPlay", RTSA_TRACE5_ViewStatus},/*{Int}*/\
 {"[:SENSe]:TRACe:6:DISPlay", RTSA_TRACE6_ViewStatus},/*{Int}*/\
 \
 /*[0 -- CLEAR_WRITE  1 -- MAX_HOLD 2 -- MIN_HOLD 3 -- VIEW 4 -- TRACE_AVE]*/ \
 {"[:SENSe]:TRACe:TYPE", RTSA_TRACE_Type},/*{Int} */\
 {"[:SENSe]:TRACe:1:TYPE", RTSA_TRACE1_Type},/*{Int}*/\
 {"[:SENSe]:TRACe:2:TYPE", RTSA_TRACE2_Type},/*{Int}*/\
 {"[:SENSe]:TRACe:3:TYPE", RTSA_TRACE3_Type},/*{Int}*/\
 {"[:SENSe]:TRACe:4:TYPE", RTSA_TRACE4_Type},/*{Int}*/\
 {"[:SENSe]:TRACe:5:TYPE", RTSA_TRACE5_Type},/*{Int}*/\
 {"[:SENSe]:TRACe:6:TYPE", RTSA_TRACE6_Type},/*{Int}*/\
\
{"[:SENSe]:TRACe:AVECount", RTSA_TRACE_AveCount},/*{Int} */\
{"[:SENSe]:TRACe:1:AVECount", RTSA_TRACE1_AveCount},/*{Int}*/\
{"[:SENSe]:TRACe:2:AVECount", RTSA_TRACE2_AveCount},/*{Int}*/\
{"[:SENSe]:TRACe:3:AVECount", RTSA_TRACE3_AveCount},/*{Int}*/\
{"[:SENSe]:TRACe:4:AVECount", RTSA_TRACE4_AveCount},/*{Int}*/\
{"[:SENSe]:TRACe:5:AVECount", RTSA_TRACE5_AveCount},/*{Int}*/\
{"[:SENSe]:TRACe:6:AVECount", RTSA_TRACE6_AveCount},/*{Int}*/\
/*[0 -- Auto 1 -- RTSA_POSITIVE_PEAK 2 -- RTSA_NEGATIVE_PEAK 3 -- RTSA_SAMPLE 4 -- RTSA_COMMON(Normal) 5 -- RTSA_AVERAGE_VOTAGE 6 -- RTSA_RMS ]*/\
{"[:SENSe]:TRACe:DETEctor", RTSA_TRACE_DetectorType},/*{Int}*/\
\
\
 {"[:SENSe]:TRACe:DISPlay?", RTSA_TRACE_ViewStatusQ},/*{Int} [0 -- OFF 1 -- ON]*/\
 {"[:SENSe]:TRACe:1:DISPlay?", RTSA_TRACE1_ViewStatusQ},/*{Int}*/\
 {"[:SENSe]:TRACe:2:DISPlay?", RTSA_TRACE2_ViewStatusQ},/*{Int}*/\
 {"[:SENSe]:TRACe:3:DISPlay?", RTSA_TRACE3_ViewStatusQ},/*{Int}*/\
 {"[:SENSe]:TRACe:4:DISPlay?", RTSA_TRACE4_ViewStatusQ},/*{Int}*/\
 {"[:SENSe]:TRACe:5:DISPlay?", RTSA_TRACE5_ViewStatusQ},/*{Int}*/\
 {"[:SENSe]:TRACe:6:DISPlay?", RTSA_TRACE6_ViewStatusQ},/*{Int}*/\
 {"[:SENSe]:TRACe:TYPE?", RTSA_TRACE_TypeQ},/*{Int} */\
 {"[:SENSe]:TRACe:1:TYPE?", RTSA_TRACE1_TypeQ},/*{Int}*/\
 {"[:SENSe]:TRACe:2:TYPE?", RTSA_TRACE2_TypeQ},/*{Int}*/\
 {"[:SENSe]:TRACe:3:TYPE?", RTSA_TRACE3_TypeQ},/*{Int}*/\
 {"[:SENSe]:TRACe:4:TYPE?", RTSA_TRACE4_TypeQ},/*{Int}*/\
 {"[:SENSe]:TRACe:5:TYPE?", RTSA_TRACE5_TypeQ},/*{Int}*/\
 {"[:SENSe]:TRACe:6:TYPE?", RTSA_TRACE6_TypeQ},/*{Int}*/\
{"[:SENSe]:TRACe:AVECount?", RTSA_TRACE_AveCountQ},/*{Int} */\
{"[:SENSe]:TRACe:1:AVECount?", RTSA_TRACE1_AveCountQ},/*{Int}*/\
{"[:SENSe]:TRACe:2:AVECount?", RTSA_TRACE2_AveCountQ},/*{Int}*/\
{"[:SENSe]:TRACe:3:AVECount?", RTSA_TRACE3_AveCountQ},/*{Int}*/\
{"[:SENSe]:TRACe:4:AVECount?", RTSA_TRACE4_AveCountQ},/*{Int}*/\
{"[:SENSe]:TRACe:5:AVECount?", RTSA_TRACE5_AveCountQ},/*{Int}*/\
{"[:SENSe]:TRACe:6:AVECount?", RTSA_TRACE6_AveCountQ},/*{Int}*/\
{"[:SENSe]:TRACe:DETEctor?", RTSA_TRACE_DetectorTypeQ},/*{Int}*/\
\
{"[:SENSe]:TRACe:DATA?", RTSA_TRACE_DataQ},/*{}*/\
{"[:SENSe]:TRACe:DENSity:DATA?", RTSA_TRACE_Density_DataQ},/*{}*/\
//{"[:SENSe]:TRACe:DATA:RAWData?", RTSA_TRACE_RawDataQ},/*{}*/\
//{"[:SENSe]:TRACe:DATA:DRAWdata?", RTSA_TRACE_DrawDataQ},/*{}*/\

scpi_result_t RTSA_TRACE_ViewStatus(scpi_t * context);
scpi_result_t RTSA_TRACE1_ViewStatus(scpi_t * context);
scpi_result_t RTSA_TRACE2_ViewStatus(scpi_t * context);
scpi_result_t RTSA_TRACE3_ViewStatus(scpi_t * context);
scpi_result_t RTSA_TRACE4_ViewStatus(scpi_t * context);
scpi_result_t RTSA_TRACE5_ViewStatus(scpi_t * context);
scpi_result_t RTSA_TRACE6_ViewStatus(scpi_t * context);

scpi_result_t RTSA_TRACE_Type(scpi_t * context);
scpi_result_t RTSA_TRACE1_Type(scpi_t * context);
scpi_result_t RTSA_TRACE2_Type(scpi_t * context);
scpi_result_t RTSA_TRACE3_Type(scpi_t * context);
scpi_result_t RTSA_TRACE4_Type(scpi_t * context);
scpi_result_t RTSA_TRACE5_Type(scpi_t * context);
scpi_result_t RTSA_TRACE6_Type(scpi_t * context);

scpi_result_t RTSA_TRACE_AveCount(scpi_t * context);
scpi_result_t RTSA_TRACE1_AveCount(scpi_t * context);
scpi_result_t RTSA_TRACE2_AveCount(scpi_t * context);
scpi_result_t RTSA_TRACE3_AveCount(scpi_t * context);
scpi_result_t RTSA_TRACE4_AveCount(scpi_t * context);
scpi_result_t RTSA_TRACE5_AveCount(scpi_t * context);
scpi_result_t RTSA_TRACE6_AveCount(scpi_t * context);

scpi_result_t RTSA_TRACE_DetectorType(scpi_t * context);

scpi_result_t RTSA_TRACE_ViewStatusQ(scpi_t * context);
scpi_result_t RTSA_TRACE1_ViewStatusQ(scpi_t * context);
scpi_result_t RTSA_TRACE2_ViewStatusQ(scpi_t * context);
scpi_result_t RTSA_TRACE3_ViewStatusQ(scpi_t * context);
scpi_result_t RTSA_TRACE4_ViewStatusQ(scpi_t * context);
scpi_result_t RTSA_TRACE5_ViewStatusQ(scpi_t * context);
scpi_result_t RTSA_TRACE6_ViewStatusQ(scpi_t * context);

scpi_result_t RTSA_TRACE_TypeQ(scpi_t * context);
scpi_result_t RTSA_TRACE1_TypeQ(scpi_t * context);
scpi_result_t RTSA_TRACE2_TypeQ(scpi_t * context);
scpi_result_t RTSA_TRACE3_TypeQ(scpi_t * context);
scpi_result_t RTSA_TRACE4_TypeQ(scpi_t * context);
scpi_result_t RTSA_TRACE5_TypeQ(scpi_t * context);
scpi_result_t RTSA_TRACE6_TypeQ(scpi_t * context);

scpi_result_t RTSA_TRACE_AveCountQ(scpi_t * context);
scpi_result_t RTSA_TRACE1_AveCountQ(scpi_t * context);
scpi_result_t RTSA_TRACE2_AveCountQ(scpi_t * context);
scpi_result_t RTSA_TRACE3_AveCountQ(scpi_t * context);
scpi_result_t RTSA_TRACE4_AveCountQ(scpi_t * context);
scpi_result_t RTSA_TRACE5_AveCountQ(scpi_t * context);
scpi_result_t RTSA_TRACE6_AveCountQ(scpi_t * context);

scpi_result_t RTSA_TRACE_DetectorTypeQ(scpi_t * context);

scpi_result_t RTSA_TRACE_DataQ(scpi_t * context);
scpi_result_t RTSA_TRACE_Density_DataQ(scpi_t * context);
//scpi_result_t RTSA_TRACE_RawDataQ(scpi_t * context);
//scpi_result_t RTSA_TRACE_DrawDataQ(scpi_t * context);

#ifdef  __cplusplus
}
#endif

#endif // RTSA_SCPI_TRACE_H
