#ifndef RTSA_SCPI_MARKER_H
#define RTSA_SCPI_MARKER_H
#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"


#ifdef  __cplusplus
extern "C" {
#endif

#define RTSA_SCPI_COMMANDS_MARKER \
{"[:SENSe]:MARKer:SELEct", RTSA_MARKER_Select},/*{Int}*/\
{"[:SENSe]:MARKer:SELEct?", RTSA_MARKER_SelectQ},/*{Int}*/\
\
{"[:SENSe]:MARKer:DISPlay",  RTSA_MARKER_DisplayState},/*{Int}*/\
{"[:SENSe]:MARKer:DISPlay?", RTSA_MARKER_DisplayStateQ},/*{Int}*/\
{"[:SENSe]:MARKer:1:DISPlay",  RTSA_MARKER1_DisplayState},/*{Int}*/\
{"[:SENSe]:MARKer:1:DISPlay?", RTSA_MARKER1_DisplayStateQ},/*{Int}*/\
{"[:SENSe]:MARKer:2:DISPlay",  RTSA_MARKER2_DisplayState},/*{Int}*/\
{"[:SENSe]:MARKer:2:DISPlay?", RTSA_MARKER2_DisplayStateQ},/*{Int}*/\
{"[:SENSe]:MARKer:3:DISPlay",  RTSA_MARKER3_DisplayState},/*{Int}*/\
{"[:SENSe]:MARKer:3:DISPlay?", RTSA_MARKER3_DisplayStateQ},/*{Int}*/\
{"[:SENSe]:MARKer:4:DISPlay",  RTSA_MARKER4_DisplayState},/*{Int}*/\
{"[:SENSe]:MARKer:4:DISPlay?", RTSA_MARKER4_DisplayStateQ},/*{Int}*/\
{"[:SENSe]:MARKer:5:DISPlay",  RTSA_MARKER5_DisplayState},/*{Int}*/\
{"[:SENSe]:MARKer:5:DISPlay?", RTSA_MARKER5_DisplayStateQ},/*{Int}*/\
{"[:SENSe]:MARKer:6:DISPlay",  RTSA_MARKER6_DisplayState},/*{Int}*/\
{"[:SENSe]:MARKer:6:DISPlay?", RTSA_MARKER6_DisplayStateQ},/*{Int}*/\
\
{"[:SENSe]:MARKer:TYPE",   RTSA_MARKER_Type},/*{Int}*/\
{"[:SENSe]:MARKer:TYPE?",  RTSA_MARKER_TypeQ},/*{Int}*/\
{"[:SENSe]:MARKer:1:TYPE",   RTSA_MARKER1_Type},/*{Int}*/\
{"[:SENSe]:MARKer:1:TYPE?",  RTSA_MARKER1_TypeQ},/*{Int}*/\
{"[:SENSe]:MARKer:2:TYPE",  RTSA_MARKER2_Type},/*{Int}*/\
{"[:SENSe]:MARKer:2:TYPE?",  RTSA_MARKER2_TypeQ},/*{Int}*/\
{"[:SENSe]:MARKer:3:TYPE",  RTSA_MARKER3_Type},/*{Int}*/\
{"[:SENSe]:MARKer:3:TYPE?",  RTSA_MARKER3_TypeQ},/*{Int}*/\
{"[:SENSe]:MARKer:4:TYPE",  RTSA_MARKER4_Type},/*{Int}*/\
{"[:SENSe]:MARKer:4:TYPE?",  RTSA_MARKER4_TypeQ},/*{Int}*/\
{"[:SENSe]:MARKer:5:TYPE",  RTSA_MARKER5_Type},/*{Int}*/\
{"[:SENSe]:MARKer:5:TYPE?",  RTSA_MARKER5_TypeQ},/*{Int}*/\
{"[:SENSe]:MARKer:6:TYPE",  RTSA_MARKER6_Type},/*{Int}*/\
{"[:SENSe]:MARKer:6:TYPE?",  RTSA_MARKER6_TypeQ},/*{Int}*/\
\
{"[:SENSe]:MARKer:TO:CENTer",  RTSA_MARKER_ToCenter},/*{None}*/\
{"[:SENSe]:MARKer:TO:STARt",  RTSA_MARKER_ToStart},/*{None}*/\
{"[:SENSe]:MARKer:TO:STOP",  RTSA_MARKER_ToStop},/*{None}*/\
\
{"[:SENSe]:MARKer:X",  RTSA_MARKER_X }, /*{Double}*/\
{"[:SENSe]:MARKer:X?",  RTSA_MARKER_XQ}, /*{Double}*/\
{"[:SENSe]:MARKer:1:X",  RTSA_MARKER1_X }, /*{Double}*/\
{"[:SENSe]:MARKer:1:X?",  RTSA_MARKER1_XQ}, /*{Double}*/\
{"[:SENSe]:MARKer:2:X",  RTSA_MARKER2_X }, /*{Double}*/\
{"[:SENSe]:MARKer:2:X?",  RTSA_MARKER2_XQ}, /*{Double}*/\
{"[:SENSe]:MARKer:3:X",  RTSA_MARKER3_X }, /*{Double}*/\
{"[:SENSe]:MARKer:3:X?",  RTSA_MARKER3_XQ}, /*{Double}*/\
{"[:SENSe]:MARKer:4:X",  RTSA_MARKER4_X }, /*{Double}*/\
{"[:SENSe]:MARKer:4:X?",  RTSA_MARKER4_XQ}, /*{Double}*/\
{"[:SENSe]:MARKer:5:X",  RTSA_MARKER5_X }, /*{Double}*/\
{"[:SENSe]:MARKer:5:X?",  RTSA_MARKER5_XQ}, /*{Double}*/\
{"[:SENSe]:MARKer:6:X",  RTSA_MARKER6_X }, /*{Double}*/\
{"[:SENSe]:MARKer:6:X?",  RTSA_MARKER6_XQ}, /*{Double}*/\
\
{"[:SENSe]:MARKer:NOISe:STATe",  RTSA_MARKER_NoiseMarker}, /*{int}*/\
{"[:SENSe]:MARKer:NOISe:STATe?",  RTSA_MARKER_NoiseMarkerQ}, /*{int}*/\
{"[:SENSe]:MARKer:1:NOISe:STATe",  RTSA_MARKER1_NoiseMarker}, /*{int}*/\
{"[:SENSe]:MARKer:1:NOISe:STATe?",  RTSA_MARKER1_NoiseMarkerQ}, /*{int}*/\
{"[:SENSe]:MARKer:2:NOISe:STATe",  RTSA_MARKER2_NoiseMarker}, /*{int}*/\
{"[:SENSe]:MARKer:2:NOISe:STATe?",  RTSA_MARKER2_NoiseMarkerQ}, /*{int}*/\
{"[:SENSe]:MARKer:3:NOISe:STATe",  RTSA_MARKER3_NoiseMarker}, /*{int}*/\
{"[:SENSe]:MARKer:3:NOISe:STATe?",  RTSA_MARKER3_NoiseMarkerQ}, /*{int}*/\
{"[:SENSe]:MARKer:4:NOISe:STATe",  RTSA_MARKER4_NoiseMarker}, /*{int}*/\
{"[:SENSe]:MARKer:4:NOISe:STATe?",  RTSA_MARKER4_NoiseMarkerQ}, /*{int}*/\
{"[:SENSe]:MARKer:5:NOISe:STATe",  RTSA_MARKER5_NoiseMarker}, /*{int}*/\
{"[:SENSe]:MARKer:5:NOISe:STATe?",  RTSA_MARKER5_NoiseMarkerQ}, /*{int}*/\
{"[:SENSe]:MARKer:6:NOISe:STATe",  RTSA_MARKER6_NoiseMarker}, /*{int}*/\
{"[:SENSe]:MARKer:6:NOISe:STATe?",  RTSA_MARKER6_NoiseMarkerQ}, /*{int}*/\
\
{"[:SENSe]:MARKer:PMAXimum",  RTSA_MARKER_PeakMax},           \
{"[:SENSe]:MARKer:PMINimum",  RTSA_MARKER_PeakMin},           \
{"[:SENSe]:MARKer:PMAXimum:NEXT",  RTSA_MARKER_PeakMaxNext},  \
{"[:SENSe]:MARKer:PMAXimum:LEFT",  RTSA_MARKER_PeakMaxLeft},  \
{"[:SENSe]:MARKer:PMAXimum:RIGHt", RTSA_MARKER_PeakMaxRight}, \
{"[:SENSe]:MARKer:PTRAck",  RTSA_MARKER_PeakTrack},  /*{int}*/\
{"[:SENSe]:MARKer:PTRAck?", RTSA_MARKER_PeakTrackQ}, /*{int}*/\
\
//{"[:SENSe]:MARKer:ALLClear", RTSA_MARKER_AllClear},\


scpi_result_t RTSA_MARKER_Select(scpi_t * context);
scpi_result_t RTSA_MARKER_SelectQ(scpi_t * context);

scpi_result_t RTSA_MARKER_DisplayState(scpi_t * context);
scpi_result_t RTSA_MARKER_DisplayStateQ(scpi_t * context);
scpi_result_t RTSA_MARKER1_DisplayState(scpi_t * context);
scpi_result_t RTSA_MARKER1_DisplayStateQ(scpi_t * context);
scpi_result_t RTSA_MARKER2_DisplayState(scpi_t * context);
scpi_result_t RTSA_MARKER2_DisplayStateQ(scpi_t * context);
scpi_result_t RTSA_MARKER3_DisplayState(scpi_t * context);
scpi_result_t RTSA_MARKER3_DisplayStateQ(scpi_t * context);
scpi_result_t RTSA_MARKER4_DisplayState(scpi_t * context);
scpi_result_t RTSA_MARKER4_DisplayStateQ(scpi_t * context);
scpi_result_t RTSA_MARKER5_DisplayState(scpi_t * context);
scpi_result_t RTSA_MARKER5_DisplayStateQ(scpi_t * context);
scpi_result_t RTSA_MARKER6_DisplayState(scpi_t * context);
scpi_result_t RTSA_MARKER6_DisplayStateQ(scpi_t * context);

scpi_result_t RTSA_MARKER_Type(scpi_t * context);
scpi_result_t RTSA_MARKER_TypeQ(scpi_t * context);
scpi_result_t RTSA_MARKER1_Type(scpi_t * context);
scpi_result_t RTSA_MARKER1_TypeQ(scpi_t * context);
scpi_result_t RTSA_MARKER2_Type(scpi_t * context);
scpi_result_t RTSA_MARKER2_TypeQ(scpi_t * context);
scpi_result_t RTSA_MARKER3_Type(scpi_t * context);
scpi_result_t RTSA_MARKER3_TypeQ(scpi_t * context);
scpi_result_t RTSA_MARKER4_Type(scpi_t * context);
scpi_result_t RTSA_MARKER4_TypeQ(scpi_t * context);
scpi_result_t RTSA_MARKER5_Type(scpi_t * context);
scpi_result_t RTSA_MARKER5_TypeQ(scpi_t * context);
scpi_result_t RTSA_MARKER6_Type(scpi_t * context);
scpi_result_t RTSA_MARKER6_TypeQ(scpi_t * context);

scpi_result_t RTSA_MARKER_ToCenter(scpi_t * context);
scpi_result_t RTSA_MARKER_ToStart(scpi_t * context);
scpi_result_t RTSA_MARKER_ToStop(scpi_t * context);

scpi_result_t RTSA_MARKER_X(scpi_t * context);
scpi_result_t RTSA_MARKER_XQ(scpi_t * context);
scpi_result_t RTSA_MARKER1_X(scpi_t * context);
scpi_result_t RTSA_MARKER1_XQ(scpi_t * context);
scpi_result_t RTSA_MARKER2_X(scpi_t * context);
scpi_result_t RTSA_MARKER2_XQ(scpi_t * context);
scpi_result_t RTSA_MARKER3_X(scpi_t * context);
scpi_result_t RTSA_MARKER3_XQ(scpi_t * context);
scpi_result_t RTSA_MARKER4_X(scpi_t * context);
scpi_result_t RTSA_MARKER4_XQ(scpi_t * context);
scpi_result_t RTSA_MARKER5_X(scpi_t * context);
scpi_result_t RTSA_MARKER5_XQ(scpi_t * context);
scpi_result_t RTSA_MARKER6_X(scpi_t * context);
scpi_result_t RTSA_MARKER6_XQ(scpi_t * context);

scpi_result_t RTSA_MARKER1_FreqCount(scpi_t * context);
scpi_result_t RTSA_MARKER1_FreqCountQ(scpi_t * context);
scpi_result_t RTSA_MARKER2_FreqCount(scpi_t * context);
scpi_result_t RTSA_MARKER2_FreqCountQ(scpi_t * context);
scpi_result_t RTSA_MARKER3_FreqCount(scpi_t * context);
scpi_result_t RTSA_MARKER3_FreqCountQ(scpi_t * context);
scpi_result_t RTSA_MARKER4_FreqCount(scpi_t * context);
scpi_result_t RTSA_MARKER4_FreqCountQ(scpi_t * context);
scpi_result_t RTSA_MARKER5_FreqCount(scpi_t * context);
scpi_result_t RTSA_MARKER5_FreqCountQ(scpi_t * context);
scpi_result_t RTSA_MARKER6_FreqCount(scpi_t * context);
scpi_result_t RTSA_MARKER6_FreqCountQ(scpi_t * context);

scpi_result_t RTSA_MARKER_NoiseMarker(scpi_t * context);
scpi_result_t RTSA_MARKER_NoiseMarkerQ(scpi_t * context);
scpi_result_t RTSA_MARKER1_NoiseMarker(scpi_t * context);
scpi_result_t RTSA_MARKER1_NoiseMarkerQ(scpi_t * context);
scpi_result_t RTSA_MARKER2_NoiseMarker(scpi_t * context);
scpi_result_t RTSA_MARKER2_NoiseMarkerQ(scpi_t * context);
scpi_result_t RTSA_MARKER3_NoiseMarker(scpi_t * context);
scpi_result_t RTSA_MARKER3_NoiseMarkerQ(scpi_t * context);
scpi_result_t RTSA_MARKER4_NoiseMarker(scpi_t * context);
scpi_result_t RTSA_MARKER4_NoiseMarkerQ(scpi_t * context);
scpi_result_t RTSA_MARKER5_NoiseMarker(scpi_t * context);
scpi_result_t RTSA_MARKER5_NoiseMarkerQ(scpi_t * context);
scpi_result_t RTSA_MARKER6_NoiseMarker(scpi_t * context);
scpi_result_t RTSA_MARKER6_NoiseMarkerQ(scpi_t * context);

scpi_result_t RTSA_MARKER_PeakMax(scpi_t * context);
scpi_result_t RTSA_MARKER_PeakMin(scpi_t * context);
scpi_result_t RTSA_MARKER_PeakMaxNext(scpi_t * context);
scpi_result_t RTSA_MARKER_PeakMaxLeft(scpi_t * context);
scpi_result_t RTSA_MARKER_PeakMaxRight(scpi_t * context);
scpi_result_t RTSA_MARKER_PeakTrack(scpi_t * context);
scpi_result_t RTSA_MARKER_PeakTrackQ(scpi_t * context);

//scpi_result_t RTSA_MARKER_AllClear(scpi_t * context);

#ifdef  __cplusplus
}
#endif

#endif // RTRTSA_SCPI_MARKER_H
