#ifndef SA_SCPI_SWEEP_H
#define SA_SCPI_SWEEP_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define SA_SCPI_COMMANDS_SWEEP \
{"[:SENSe]:SWEEp:TIME:AUTO" ,SA_SWEEP_AutoTime}, /* {Int}*/\
{"[:SENSe]:SWEEp:TIME" ,SA_SWEEP_Time},          /* {double}*/\
{"[:SENSe]:SWEEp:CONTinuous" ,SA_SWEEP_Type},          /* {Int}[1--cont 0--single]*/\
\
{"[:SENSe]:SWEEp:TIME:AUTO?",SA_SWEEP_AutoTimeQ},/* {Int}*/\
{"[:SENSe]:SWEEp:TIME?" ,SA_SWEEP_TimeQ},         /* {double}*/\
{"[:SENSe]:SWEEp:CONTinuous?" ,SA_SWEEP_TypeQ},          /* {Int}[1--cont 0--single]*/\
\
{"[:SENSe]:SWEEp:FIXEd" ,SA_SWEEP_FixedMode}, /* {Int 0 -- Off 1 -- On}*/\
{"[:SENSe]:SWEEp:FIXEd?" ,SA_SWEEP_FixedModeQ}, /* {Int}*/\
{"[:SENSe]:SWEEp:DOT:TIME:AUTO" ,SA_SWEEP_DotAutoTime}, /* {Int}*/\
{"[:SENSe]:SWEEp:DOT:TIME:AUTO?" ,SA_SWEEP_DotAutoTimeQ}, /* {Int}*/\
{"[:SENSe]:SWEEp:DOT:TIME" ,SA_SWEEP_DotTime}, /* {double}*/\
{"[:SENSe]:SWEEp:DOT:TIME?" ,SA_SWEEP_DotTimeQ}, /* {double}*/\
\
{"[:SENSe]:SWEEp:EGATe:SOURce" ,SA_GATE_Source}, /* {Int NONE|EXTERN|RFBURST|PERIOD}*/\
{"[:SENSe]:SWEEp:EGATe:SOURce?" ,SA_GATE_SourceQ}, /* {Int}*/\
{"[:SENSe]:SWEEp:EGATe:STATe" ,SA_GATE_State}, /* {Int}*/\
{"[:SENSe]:SWEEp:EGATe:STATe?" ,SA_GATE_StateQ}, /* {Int}*/\
{"[:SENSe]:SWEEp:EGATe:METHod" ,SA_GATE_Method}, /* {Int LO|VIDeo|FFT}*/\
{"[:SENSe]:SWEEp:EGATe:METHod?" ,SA_GATE_MethodQ}, /* {Int}*/\
{"[:SENSe]:SWEEp:EGATe:CONTrol" ,SA_GATE_Control}, /* {Int  EDGE|LEVel}*/\
{"[:SENSe]:SWEEp:EGATe:CONTrol?" ,SA_GATE_ControlQ}, /* {Int}*/\
{"[:SENSe]:SWEEp:EGATe:VALUe" ,SA_GATE_Value}, /* {Int LOW|HIGH}*/\
{"[:SENSe]:SWEEp:EGATe:VALUe?" ,SA_GATE_ValueQ}, /* {Int}*/\
\
{"[:SENSe]:SWEEp:EGATe:DELAy" ,SA_GATE_Delay}, /* {double}*/\
{"[:SENSe]:SWEEp:EGATe:DELAy?" ,SA_GATE_DelayQ}, /* {double}*/\
{"[:SENSe]:SWEEp:EGATe:LENGth" ,SA_GATE_Length}, /* {double}*/\
{"[:SENSe]:SWEEp:EGATe:LENGth?" ,SA_GATE_LengthQ}, /* {double}*/\
\
{"[:SENSe]:SWEEp:EGATe:PREVent:STATe" ,SA_GATE_PreventState}, /* {Int}*/\
{"[:SENSe]:SWEEp:EGATe:PREVent:STATe?" ,SA_GATE_PreventStateQ}, /* {Int}*/\
{"[:SENSe]:SWEEp:EGATe:PREVent:TIME" ,SA_GATE_PreventTime}, /* {double}*/\
{"[:SENSe]:SWEEp:EGATe:PREVent:TIME?" ,SA_GATE_PreventTimeQ}, /* {double}*/\
{"[:SENSe]:SWEEp:EGATe:VIEW" ,SA_GATE_View}, /* {Int}*/\
{"[:SENSe]:SWEEp:EGATe:VIEW?" ,SA_GATE_ViewQ}, /* {Int}*/\
{"[:SENSe]:SWEEp:EGATe:VIEW:STARt" ,SA_GATE_ViewStart}, /* {double}*/\
{"[:SENSe]:SWEEp:EGATe:VIEW:STARt?" ,SA_GATE_ViewStartQ}, /* {double}*/\
\
{"[:SENSe]:SWEEp:EGATe:TRIGger:LEVEl" ,SA_GATE_TriggerLevel}, /* {double}*/\
{"[:SENSe]:SWEEp:EGATe:TRIGger:LEVEl?" ,SA_GATE_TriggerLevelQ}, /* {double}*/\
\
{"[:SENSe]:SWEEp:EGATe:PERIod" ,SA_GATE_Period}, /* {double}*/\
{"[:SENSe]:SWEEp:EGATe:PERIod?" ,SA_GATE_PeriodQ}, /* {double}*/\
{"[:SENSe]:SWEEp:EGATe:SYNSrcdelay:TIME" ,SA_GATE_SYNsrcdelay}, /* {double}*/\
{"[:SENSe]:SWEEp:EGATe:SYNSrcdelay:TIME?" ,SA_GATE_SYNsrcdelayQ}, /* {double}*/\
{"[:SENSe]:SWEEp:EGATe:SRCPr:STATe" ,SA_GATE_SrcPr}, /* {Int}*/\
{"[:SENSe]:SWEEp:EGATe:SRCPr:STATe?" ,SA_GATE_SrcPrQ}, /* {Int}*/\
{"[:SENSe]:SWEEp:EGATe:SRCPr:TIME" ,SA_GATE_SrcPrTime}, /* {double}*/\
{"[:SENSe]:SWEEp:EGATe:SRCPr:TIME?" ,SA_GATE_SrcPrTimeQ}, /* {double}*/\
{"[:SENSe]:SWEEp:EGATe:SYCH:SOURce" ,SA_GATE_SychSource}, /* {Int}*/\
{"[:SENSe]:SWEEp:EGATe:SYCH:SOURce?" ,SA_GATE_SychSourceQ}, /* {Int}*/\


scpi_result_t GetTimeVal(scpi_t *context,qreal *val);

scpi_result_t SA_SWEEP_AutoTime(scpi_t * context);
scpi_result_t SA_SWEEP_Time(scpi_t * context);
scpi_result_t SA_SWEEP_Type(scpi_t * context);

scpi_result_t SA_SWEEP_AutoTimeQ(scpi_t * context);
scpi_result_t SA_SWEEP_TimeQ(scpi_t * context);
scpi_result_t SA_SWEEP_TypeQ(scpi_t * context);

scpi_result_t SA_SWEEP_FixedMode(scpi_t * context);
scpi_result_t SA_SWEEP_FixedModeQ(scpi_t * context);
scpi_result_t SA_SWEEP_DotAutoTime(scpi_t * context);
scpi_result_t SA_SWEEP_DotAutoTimeQ(scpi_t * context);
scpi_result_t SA_SWEEP_DotTime(scpi_t * context);
scpi_result_t SA_SWEEP_DotTimeQ(scpi_t * context);

scpi_result_t SA_GATE_Source(scpi_t * context);
scpi_result_t SA_GATE_SourceQ(scpi_t * context);
scpi_result_t SA_GATE_State(scpi_t * context);
scpi_result_t SA_GATE_StateQ(scpi_t * context);
scpi_result_t SA_GATE_Method(scpi_t * context);
scpi_result_t SA_GATE_MethodQ(scpi_t * context);
scpi_result_t SA_GATE_Control(scpi_t * context);
scpi_result_t SA_GATE_ControlQ(scpi_t * context);
scpi_result_t SA_GATE_Value(scpi_t * context);
scpi_result_t SA_GATE_ValueQ(scpi_t * context);

scpi_result_t SA_GATE_Delay(scpi_t * context);
scpi_result_t SA_GATE_DelayQ(scpi_t * context);
scpi_result_t SA_GATE_Length(scpi_t * context);
scpi_result_t SA_GATE_LengthQ(scpi_t * context);

scpi_result_t SA_GATE_PreventState(scpi_t * context);
scpi_result_t SA_GATE_PreventStateQ(scpi_t * context);
scpi_result_t SA_GATE_PreventTime(scpi_t * context);
scpi_result_t SA_GATE_PreventTimeQ(scpi_t * context);
scpi_result_t SA_GATE_View(scpi_t * context);
scpi_result_t SA_GATE_ViewQ(scpi_t * context);
scpi_result_t SA_GATE_ViewStart(scpi_t * context);
scpi_result_t SA_GATE_ViewStartQ(scpi_t * context);

scpi_result_t SA_GATE_TriggerLevel(scpi_t * context);
scpi_result_t SA_GATE_TriggerLevelQ(scpi_t * context);

scpi_result_t SA_GATE_Period(scpi_t * context);
scpi_result_t SA_GATE_PeriodQ(scpi_t * context);
scpi_result_t SA_GATE_SYNsrcdelay(scpi_t * context);
scpi_result_t SA_GATE_SYNsrcdelayQ(scpi_t * context);
scpi_result_t SA_GATE_SrcPr(scpi_t * context);
scpi_result_t SA_GATE_SrcPrQ(scpi_t * context);
scpi_result_t SA_GATE_SrcPrTime(scpi_t * context);
scpi_result_t SA_GATE_SrcPrTimeQ(scpi_t * context);
scpi_result_t SA_GATE_SychSource(scpi_t * context);
scpi_result_t SA_GATE_SychSourceQ(scpi_t * context);

#ifdef  __cplusplus
}
#endif


#endif // SA_SCPI_SWEEP_H
