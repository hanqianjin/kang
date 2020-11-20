#ifndef SA_SCPI_MARKER_H
#define SA_SCPI_MARKER_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define SA_SCPI_COMMANDS_MARKER \
{"[:SENSe]:MARKer:SELEct", SA_MARKER_Select},/*{Int}*/\
{"[:SENSe]:MARKer:SELEct?", SA_MARKER_SelectQ},/*{Int}*/\
\
{"[:SENSe]:MARKer:DISPlay",  SA_MARKER_DisplayState},/*{Int}*/\
{"[:SENSe]:MARKer:DISPlay?", SA_MARKER_DisplayStateQ},/*{Int}*/\
{"[:SENSe]:MARKer:1:DISPlay",  SA_MARKER1_DisplayState},/*{Int}*/\
{"[:SENSe]:MARKer:1:DISPlay?", SA_MARKER1_DisplayStateQ},/*{Int}*/\
{"[:SENSe]:MARKer:2:DISPlay",  SA_MARKER2_DisplayState},/*{Int}*/\
{"[:SENSe]:MARKer:2:DISPlay?", SA_MARKER2_DisplayStateQ},/*{Int}*/\
{"[:SENSe]:MARKer:3:DISPlay",  SA_MARKER3_DisplayState},/*{Int}*/\
{"[:SENSe]:MARKer:3:DISPlay?", SA_MARKER3_DisplayStateQ},/*{Int}*/\
{"[:SENSe]:MARKer:4:DISPlay",  SA_MARKER4_DisplayState},/*{Int}*/\
{"[:SENSe]:MARKer:4:DISPlay?", SA_MARKER4_DisplayStateQ},/*{Int}*/\
{"[:SENSe]:MARKer:5:DISPlay",  SA_MARKER5_DisplayState},/*{Int}*/\
{"[:SENSe]:MARKer:5:DISPlay?", SA_MARKER5_DisplayStateQ},/*{Int}*/\
{"[:SENSe]:MARKer:6:DISPlay",  SA_MARKER6_DisplayState},/*{Int}*/\
{"[:SENSe]:MARKer:6:DISPlay?", SA_MARKER6_DisplayStateQ},/*{Int}*/\
\
{"[:SENSe]:MARKer:TYPE",   SA_MARKER_Type},/*{Int}*/\
{"[:SENSe]:MARKer:TYPE?",  SA_MARKER_TypeQ},/*{Int}*/\
{"[:SENSe]:MARKer:1:TYPE",   SA_MARKER1_Type},/*{Int}*/\
{"[:SENSe]:MARKer:1:TYPE?",  SA_MARKER1_TypeQ},/*{Int}*/\
{"[:SENSe]:MARKer:2:TYPE",  SA_MARKER2_Type},/*{Int}*/\
{"[:SENSe]:MARKer:2:TYPE?",  SA_MARKER2_TypeQ},/*{Int}*/\
{"[:SENSe]:MARKer:3:TYPE",  SA_MARKER3_Type},/*{Int}*/\
{"[:SENSe]:MARKer:3:TYPE?",  SA_MARKER3_TypeQ},/*{Int}*/\
{"[:SENSe]:MARKer:4:TYPE",  SA_MARKER4_Type},/*{Int}*/\
{"[:SENSe]:MARKer:4:TYPE?",  SA_MARKER4_TypeQ},/*{Int}*/\
{"[:SENSe]:MARKer:5:TYPE",  SA_MARKER5_Type},/*{Int}*/\
{"[:SENSe]:MARKer:5:TYPE?",  SA_MARKER5_TypeQ},/*{Int}*/\
{"[:SENSe]:MARKer:6:TYPE",  SA_MARKER6_Type},/*{Int}*/\
{"[:SENSe]:MARKer:6:TYPE?",  SA_MARKER6_TypeQ},/*{Int}*/\
\
{"[:SENSe]:MARKer:TO:CENTer",  SA_MARKER_ToCenter},/*{None}*/\
{"[:SENSe]:MARKer:TO:STARt",  SA_MARKER_ToStart},/*{None}*/\
{"[:SENSe]:MARKer:TO:STOP",  SA_MARKER_ToStop},/*{None}*/\
\
{"[:SENSe]:MARKer:X",  SA_MARKER_X }, /*{Double}*/\
{"[:SENSe]:MARKer:X?",  SA_MARKER_XQ}, /*{Double}*/\
{"[:SENSe]:MARKer:1:X",  SA_MARKER1_X }, /*{Double}*/\
{"[:SENSe]:MARKer:1:X?",  SA_MARKER1_XQ}, /*{Double}*/\
{"[:SENSe]:MARKer:2:X",  SA_MARKER2_X }, /*{Double}*/\
{"[:SENSe]:MARKer:2:X?",  SA_MARKER2_XQ}, /*{Double}*/\
{"[:SENSe]:MARKer:3:X",  SA_MARKER3_X }, /*{Double}*/\
{"[:SENSe]:MARKer:3:X?",  SA_MARKER3_XQ}, /*{Double}*/\
{"[:SENSe]:MARKer:4:X",  SA_MARKER4_X }, /*{Double}*/\
{"[:SENSe]:MARKer:4:X?",  SA_MARKER4_XQ}, /*{Double}*/\
{"[:SENSe]:MARKer:5:X",  SA_MARKER5_X }, /*{Double}*/\
{"[:SENSe]:MARKer:5:X?",  SA_MARKER5_XQ}, /*{Double}*/\
{"[:SENSe]:MARKer:6:X",  SA_MARKER6_X }, /*{Double}*/\
{"[:SENSe]:MARKer:6:X?",  SA_MARKER6_XQ}, /*{Double}*/\
\
{"[:SENSe]:MARKer:FCOUnt:STATe",  SA_MARKER_FreqCount}, /*{int}*/\
{"[:SENSe]:MARKer:FCOUnt:STATe?",  SA_MARKER_FreqCountQ}, /*{int}*/\
{"[:SENSe]:MARKer:1:FCOUnt:STATe",  SA_MARKER1_FreqCount}, /*{int}*/\
{"[:SENSe]:MARKer:1:FCOUnt:STATe?",  SA_MARKER1_FreqCountQ}, /*{int}*/\
{"[:SENSe]:MARKer:2:FCOUnt:STATe",  SA_MARKER2_FreqCount}, /*{int}*/\
{"[:SENSe]:MARKer:2:FCOUnt:STATe?",  SA_MARKER2_FreqCountQ}, /*{int}*/\
{"[:SENSe]:MARKer:3:FCOUnt:STATe",  SA_MARKER3_FreqCount}, /*{int}*/\
{"[:SENSe]:MARKer:3:FCOUnt:STATe?",  SA_MARKER3_FreqCountQ}, /*{int}*/\
{"[:SENSe]:MARKer:4:FCOUnt:STATe",  SA_MARKER4_FreqCount}, /*{int}*/\
{"[:SENSe]:MARKer:4:FCOUnt:STATe?",  SA_MARKER4_FreqCountQ}, /*{int}*/\
{"[:SENSe]:MARKer:5:FCOUnt:STATe",  SA_MARKER5_FreqCount}, /*{int}*/\
{"[:SENSe]:MARKer:5:FCOUnt:STATe?",  SA_MARKER5_FreqCountQ}, /*{int}*/\
{"[:SENSe]:MARKer:6:FCOUnt:STATe",  SA_MARKER6_FreqCount}, /*{int}*/\
{"[:SENSe]:MARKer:6:FCOUnt:STATe?",  SA_MARKER6_FreqCountQ}, /*{int}*/\
\
{"[:SENSe]:MARKer:NOISe:STATe",  SA_MARKER_NoiseMarker}, /*{int}*/\
{"[:SENSe]:MARKer:NOISe:STATe?",  SA_MARKER_NoiseMarkerQ}, /*{int}*/\
{"[:SENSe]:MARKer:1:NOISe:STATe",  SA_MARKER1_NoiseMarker}, /*{int}*/\
{"[:SENSe]:MARKer:1:NOISe:STATe?",  SA_MARKER1_NoiseMarkerQ}, /*{int}*/\
{"[:SENSe]:MARKer:2:NOISe:STATe",  SA_MARKER2_NoiseMarker}, /*{int}*/\
{"[:SENSe]:MARKer:2:NOISe:STATe?",  SA_MARKER2_NoiseMarkerQ}, /*{int}*/\
{"[:SENSe]:MARKer:3:NOISe:STATe",  SA_MARKER3_NoiseMarker}, /*{int}*/\
{"[:SENSe]:MARKer:3:NOISe:STATe?",  SA_MARKER3_NoiseMarkerQ}, /*{int}*/\
{"[:SENSe]:MARKer:4:NOISe:STATe",  SA_MARKER4_NoiseMarker}, /*{int}*/\
{"[:SENSe]:MARKer:4:NOISe:STATe?",  SA_MARKER4_NoiseMarkerQ}, /*{int}*/\
{"[:SENSe]:MARKer:5:NOISe:STATe",  SA_MARKER5_NoiseMarker}, /*{int}*/\
{"[:SENSe]:MARKer:5:NOISe:STATe?",  SA_MARKER5_NoiseMarkerQ}, /*{int}*/\
{"[:SENSe]:MARKer:6:NOISe:STATe",  SA_MARKER6_NoiseMarker}, /*{int}*/\
{"[:SENSe]:MARKer:6:NOISe:STATe?",  SA_MARKER6_NoiseMarkerQ}, /*{int}*/\
\
{"[:SENSe]:MARKer:PMAXimum",  SA_MARKER_PeakMax},           \
{"[:SENSe]:MARKer:PMINimum",  SA_MARKER_PeakMin},           \
{"[:SENSe]:MARKer:PMAXimum:NEXT",  SA_MARKER_PeakMaxNext},  \
{"[:SENSe]:MARKer:PMAXimum:LEFT",  SA_MARKER_PeakMaxLeft},  \
{"[:SENSe]:MARKer:PMAXimum:RIGHt", SA_MARKER_PeakMaxRight}, \
{"[:SENSe]:MARKer:PTRAck",  SA_MARKER_PeakTrack},  /*{int}*/\
{"[:SENSe]:MARKer:PTRAck?", SA_MARKER_PeakTrackQ}, /*{int}*/\
\
{"[:SENSe]:MARKer:ALLClear", SA_MARKER_AllClear},\


scpi_result_t SA_MARKER_Select(scpi_t * context);
scpi_result_t SA_MARKER_SelectQ(scpi_t * context);

scpi_result_t SA_MARKER_DisplayState(scpi_t * context);
scpi_result_t SA_MARKER_DisplayStateQ(scpi_t * context);
scpi_result_t SA_MARKER1_DisplayState(scpi_t * context);
scpi_result_t SA_MARKER1_DisplayStateQ(scpi_t * context);
scpi_result_t SA_MARKER2_DisplayState(scpi_t * context);
scpi_result_t SA_MARKER2_DisplayStateQ(scpi_t * context);
scpi_result_t SA_MARKER3_DisplayState(scpi_t * context);
scpi_result_t SA_MARKER3_DisplayStateQ(scpi_t * context);
scpi_result_t SA_MARKER4_DisplayState(scpi_t * context);
scpi_result_t SA_MARKER4_DisplayStateQ(scpi_t * context);
scpi_result_t SA_MARKER5_DisplayState(scpi_t * context);
scpi_result_t SA_MARKER5_DisplayStateQ(scpi_t * context);
scpi_result_t SA_MARKER6_DisplayState(scpi_t * context);
scpi_result_t SA_MARKER6_DisplayStateQ(scpi_t * context);

scpi_result_t SA_MARKER_Type(scpi_t * context);
scpi_result_t SA_MARKER_TypeQ(scpi_t * context);
scpi_result_t SA_MARKER1_Type(scpi_t * context);
scpi_result_t SA_MARKER1_TypeQ(scpi_t * context);
scpi_result_t SA_MARKER2_Type(scpi_t * context);
scpi_result_t SA_MARKER2_TypeQ(scpi_t * context);
scpi_result_t SA_MARKER3_Type(scpi_t * context);
scpi_result_t SA_MARKER3_TypeQ(scpi_t * context);
scpi_result_t SA_MARKER4_Type(scpi_t * context);
scpi_result_t SA_MARKER4_TypeQ(scpi_t * context);
scpi_result_t SA_MARKER5_Type(scpi_t * context);
scpi_result_t SA_MARKER5_TypeQ(scpi_t * context);
scpi_result_t SA_MARKER6_Type(scpi_t * context);
scpi_result_t SA_MARKER6_TypeQ(scpi_t * context);

scpi_result_t SA_MARKER_ToCenter(scpi_t * context);
scpi_result_t SA_MARKER_ToStart(scpi_t * context);
scpi_result_t SA_MARKER_ToStop(scpi_t * context);

scpi_result_t SA_MARKER_X(scpi_t * context);
scpi_result_t SA_MARKER_XQ(scpi_t * context);
scpi_result_t SA_MARKER1_X(scpi_t * context);
scpi_result_t SA_MARKER1_XQ(scpi_t * context);
scpi_result_t SA_MARKER2_X(scpi_t * context);
scpi_result_t SA_MARKER2_XQ(scpi_t * context);
scpi_result_t SA_MARKER3_X(scpi_t * context);
scpi_result_t SA_MARKER3_XQ(scpi_t * context);
scpi_result_t SA_MARKER4_X(scpi_t * context);
scpi_result_t SA_MARKER4_XQ(scpi_t * context);
scpi_result_t SA_MARKER5_X(scpi_t * context);
scpi_result_t SA_MARKER5_XQ(scpi_t * context);
scpi_result_t SA_MARKER6_X(scpi_t * context);
scpi_result_t SA_MARKER6_XQ(scpi_t * context);

scpi_result_t SA_MARKER_FreqCount(scpi_t * context);
scpi_result_t SA_MARKER_FreqCountQ(scpi_t * context);
scpi_result_t SA_MARKER1_FreqCount(scpi_t * context);
scpi_result_t SA_MARKER1_FreqCountQ(scpi_t * context);
scpi_result_t SA_MARKER2_FreqCount(scpi_t * context);
scpi_result_t SA_MARKER2_FreqCountQ(scpi_t * context);
scpi_result_t SA_MARKER3_FreqCount(scpi_t * context);
scpi_result_t SA_MARKER3_FreqCountQ(scpi_t * context);
scpi_result_t SA_MARKER4_FreqCount(scpi_t * context);
scpi_result_t SA_MARKER4_FreqCountQ(scpi_t * context);
scpi_result_t SA_MARKER5_FreqCount(scpi_t * context);
scpi_result_t SA_MARKER5_FreqCountQ(scpi_t * context);
scpi_result_t SA_MARKER6_FreqCount(scpi_t * context);
scpi_result_t SA_MARKER6_FreqCountQ(scpi_t * context);

scpi_result_t SA_MARKER_NoiseMarker(scpi_t * context);
scpi_result_t SA_MARKER_NoiseMarkerQ(scpi_t * context);
scpi_result_t SA_MARKER1_NoiseMarker(scpi_t * context);
scpi_result_t SA_MARKER1_NoiseMarkerQ(scpi_t * context);
scpi_result_t SA_MARKER2_NoiseMarker(scpi_t * context);
scpi_result_t SA_MARKER2_NoiseMarkerQ(scpi_t * context);
scpi_result_t SA_MARKER3_NoiseMarker(scpi_t * context);
scpi_result_t SA_MARKER3_NoiseMarkerQ(scpi_t * context);
scpi_result_t SA_MARKER4_NoiseMarker(scpi_t * context);
scpi_result_t SA_MARKER4_NoiseMarkerQ(scpi_t * context);
scpi_result_t SA_MARKER5_NoiseMarker(scpi_t * context);
scpi_result_t SA_MARKER5_NoiseMarkerQ(scpi_t * context);
scpi_result_t SA_MARKER6_NoiseMarker(scpi_t * context);
scpi_result_t SA_MARKER6_NoiseMarkerQ(scpi_t * context);

scpi_result_t SA_MARKER_PeakMax(scpi_t * context);
scpi_result_t SA_MARKER_PeakMin(scpi_t * context);
scpi_result_t SA_MARKER_PeakMaxNext(scpi_t * context);
scpi_result_t SA_MARKER_PeakMaxLeft(scpi_t * context);
scpi_result_t SA_MARKER_PeakMaxRight(scpi_t * context);
scpi_result_t SA_MARKER_PeakTrack(scpi_t * context);
scpi_result_t SA_MARKER_PeakTrackQ(scpi_t * context);

scpi_result_t SA_MARKER_AllClear(scpi_t * context);

#ifdef  __cplusplus
}
#endif

#endif // SA_SCPI_MARKER_H
