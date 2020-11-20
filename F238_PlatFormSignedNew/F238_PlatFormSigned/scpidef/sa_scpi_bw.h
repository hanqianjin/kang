#ifndef SA_SCPI_BW_H
#define SA_SCPI_BW_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef  __cplusplus
extern "C" {
#endif


#define SA_SCPI_COMMANDS_BANDWIDTH \
{"[:SENSe]:BANDwidth:RBW:AUTO", SA_BANDWIDTH_AutoRbw},/*{Int}*/\
{"[:SENSe]:BANDwidth:RBW", SA_BANDWIDTH_Rbw},/*{Int}*/\
{"[:SENSe]:BANDwidth:VBW:AUTO", SA_BANDWIDTH_AutoVbw},/*{Int}*/\
{"[:SENSe]:BANDwidth:VBW", SA_BANDWIDTH_Vbw},/*{Int}*/\
{"[:SENSe]:BANDwidth:RATIo", SA_BANDWIDTH_Ratio},/*{Double}*/\
{"[:SENSe]:IFOUtput", SA_IFoutput},/*{Int <3}*/\
{"[:SENSe]:BWIDth:RBW:AUTO", SA_BANDWIDTH_AutoRbw},/*{Int}*/\
{"[:SENSe]:BWIDth:RBW", SA_BANDWIDTH_Rbw},/*{Int}*/\
{"[:SENSe]:BWIDth:VBW:AUTO", SA_BANDWIDTH_AutoVbw},/*{Int}*/\
{"[:SENSe]:BWIDth:VBW", SA_BANDWIDTH_Vbw},/*{Int}*/\
{"[:SENSe]:BWIDth:RATIo", SA_BANDWIDTH_Ratio},/*{Double}*/\
\
{"[:SENSe]:BANDwidth:RBW:AUTO?", SA_BANDWIDTH_AutoRbwQ},/*{Int}*/\
{"[:SENSe]:BANDwidth:RBW?", SA_BANDWIDTH_RbwQ},/*{Int}*/\
{"[:SENSe]:BANDwidth:VBW:AUTO?", SA_BANDWIDTH_AutoVbwQ},/*{Int}*/\
{"[:SENSe]:BANDwidth:VBW?", SA_BANDWIDTH_VbwQ},/*{Int}*/\
{"[:SENSe]:BANDwidth:RATIo?", SA_BANDWIDTH_RatioQ},/*{Double}*/\
{"[:SENSe]:IFOUtput?", SA_IFoutputQ},/*{Int <3}*/\
{"[:SENSe]:BWIDth:RBW:AUTO?", SA_BANDWIDTH_AutoRbwQ},/*{Int}*/\
{"[:SENSe]:BWIDth:RBW?", SA_BANDWIDTH_RbwQ},/*{Int}*/\
{"[:SENSe]:BWIDth:VBW:AUTO?", SA_BANDWIDTH_AutoVbwQ},/*{Int}*/\
{"[:SENSe]:BWIDth:VBW?", SA_BANDWIDTH_VbwQ},/*{Int}*/\
{"[:SENSe]:BWIDth:RATIo?", SA_BANDWIDTH_RatioQ},/*{Double}*/\

scpi_result_t SA_BANDWIDTH_AutoRbw(scpi_t * context);
scpi_result_t SA_BANDWIDTH_Rbw(scpi_t * context);
scpi_result_t SA_BANDWIDTH_AutoVbw(scpi_t * context);
scpi_result_t SA_BANDWIDTH_Vbw(scpi_t * context);
scpi_result_t SA_BANDWIDTH_Ratio(scpi_t * context);
scpi_result_t SA_IFoutput(scpi_t * context);

scpi_result_t SA_BANDWIDTH_AutoRbwQ(scpi_t * context);
scpi_result_t SA_BANDWIDTH_RbwQ(scpi_t * context);
scpi_result_t SA_BANDWIDTH_AutoVbwQ(scpi_t * context);
scpi_result_t SA_BANDWIDTH_VbwQ(scpi_t * context);
scpi_result_t SA_BANDWIDTH_RatioQ(scpi_t * context);
scpi_result_t SA_IFoutputQ(scpi_t * context);

scpi_result_t GetFreqVal(scpi_t *context,quint64 *val);
#ifdef  __cplusplus
}
#endif
#endif // SA_SCPI_BW_H
