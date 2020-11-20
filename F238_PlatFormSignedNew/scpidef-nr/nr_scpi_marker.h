#ifndef NR_SCPI_MARKER_H
#define NR_SCPI_MARKER_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define NR_SCPI_COMMANDS_MARKER \
{"[:SENSe]:MARKer:SELEct", NR_MARKER_Select},/*{Int}*/\
{"[:SENSe]:MARKer:SELEct?", NR_MARKER_SelectQ},/*{Int}*/\
    \
{"[:SENSe]:MARKer:DISPlay",  NR_MARKER_DisplayState},/*{Int}*/\
{"[:SENSe]:MARKer:DISPlay?", NR_MARKER_DisplayStateQ},/*{Int}*/\
{"[:SENSe]:MARKer:1:DISPlay",  NR_MARKER1_DisplayState},/*{Int}*/\
{"[:SENSe]:MARKer:1:DISPlay?", NR_MARKER1_DisplayStateQ},/*{Int}*/\
{"[:SENSe]:MARKer:2:DISPlay",  NR_MARKER2_DisplayState},/*{Int}*/\
{"[:SENSe]:MARKer:2:DISPlay?", NR_MARKER2_DisplayStateQ},/*{Int}*/\
{"[:SENSe]:MARKer:3:DISPlay",  NR_MARKER3_DisplayState},/*{Int}*/\
{"[:SENSe]:MARKer:3:DISPlay?", NR_MARKER3_DisplayStateQ},/*{Int}*/\
{"[:SENSe]:MARKer:4:DISPlay",  NR_MARKER4_DisplayState},/*{Int}*/\
{"[:SENSe]:MARKer:4:DISPlay?", NR_MARKER4_DisplayStateQ},/*{Int}*/\
{"[:SENSe]:MARKer:5:DISPlay",  NR_MARKER5_DisplayState},/*{Int}*/\
{"[:SENSe]:MARKer:5:DISPlay?", NR_MARKER5_DisplayStateQ},/*{Int}*/\
{"[:SENSe]:MARKer:6:DISPlay",  NR_MARKER6_DisplayState},/*{Int}*/\
{"[:SENSe]:MARKer:6:DISPlay?", NR_MARKER6_DisplayStateQ},/*{Int}*/\
    \
{"[:SENSe]:MARKer:TYPE",   NR_MARKER_Type},/*{Int}*/\
{"[:SENSe]:MARKer:TYPE?",  NR_MARKER_TypeQ},/*{Int}*/\
{"[:SENSe]:MARKer:1:TYPE",   NR_MARKER1_Type},/*{Int}*/\
{"[:SENSe]:MARKer:1:TYPE?",  NR_MARKER1_TypeQ},/*{Int}*/\
{"[:SENSe]:MARKer:2:TYPE",  NR_MARKER2_Type},/*{Int}*/\
{"[:SENSe]:MARKer:2:TYPE?",  NR_MARKER2_TypeQ},/*{Int}*/\
{"[:SENSe]:MARKer:3:TYPE",  NR_MARKER3_Type},/*{Int}*/\
{"[:SENSe]:MARKer:3:TYPE?",  NR_MARKER3_TypeQ},/*{Int}*/\
{"[:SENSe]:MARKer:4:TYPE",  NR_MARKER4_Type},/*{Int}*/\
{"[:SENSe]:MARKer:4:TYPE?",  NR_MARKER4_TypeQ},/*{Int}*/\
{"[:SENSe]:MARKer:5:TYPE",  NR_MARKER5_Type},/*{Int}*/\
{"[:SENSe]:MARKer:5:TYPE?",  NR_MARKER5_TypeQ},/*{Int}*/\
{"[:SENSe]:MARKer:6:TYPE",  NR_MARKER6_Type},/*{Int}*/\
{"[:SENSe]:MARKer:6:TYPE?",  NR_MARKER6_TypeQ},/*{Int}*/\
    \
{"[:SENSe]:MARKer:NOISe:STATe",  NR_MARKER_NoiseMarker}, /*{int}*/\
{"[:SENSe]:MARKer:NOISe:STATe?",  NR_MARKER_NoiseMarkerQ}, /*{int}*/\
{"[:SENSe]:MARKer:1:NOISe:STATe",  NR_MARKER1_NoiseMarker}, /*{int}*/\
{"[:SENSe]:MARKer:1:NOISe:STATe?",  NR_MARKER1_NoiseMarkerQ}, /*{int}*/\
{"[:SENSe]:MARKer:2:NOISe:STATe",  NR_MARKER2_NoiseMarker}, /*{int}*/\
{"[:SENSe]:MARKer:2:NOISe:STATe?",  NR_MARKER2_NoiseMarkerQ}, /*{int}*/\
{"[:SENSe]:MARKer:3:NOISe:STATe",  NR_MARKER3_NoiseMarker}, /*{int}*/\
{"[:SENSe]:MARKer:3:NOISe:STATe?",  NR_MARKER3_NoiseMarkerQ}, /*{int}*/\
{"[:SENSe]:MARKer:4:NOISe:STATe",  NR_MARKER4_NoiseMarker}, /*{int}*/\
{"[:SENSe]:MARKer:4:NOISe:STATe?",  NR_MARKER4_NoiseMarkerQ}, /*{int}*/\
{"[:SENSe]:MARKer:5:NOISe:STATe",  NR_MARKER5_NoiseMarker}, /*{int}*/\
{"[:SENSe]:MARKer:5:NOISe:STATe?",  NR_MARKER5_NoiseMarkerQ}, /*{int}*/\
{"[:SENSe]:MARKer:6:NOISe:STATe",  NR_MARKER6_NoiseMarker}, /*{int}*/\
{"[:SENSe]:MARKer:6:NOISe:STATe?",  NR_MARKER6_NoiseMarkerQ}, /*{int}*/\
    \
{"[:SENSe]:MARKer:PMAXimum",  NR_MARKER_PeakMax},           \
{"[:SENSe]:MARKer:PMINimum",  NR_MARKER_PeakMin},           \
{"[:SENSe]:MARKer:PMAXimum:NEXT",  NR_MARKER_PeakMaxNext},  \
{"[:SENSe]:MARKer:PMAXimum:LEFT",  NR_MARKER_PeakMaxLeft},  \
{"[:SENSe]:MARKer:PMAXimum:RIGHt", NR_MARKER_PeakMaxRight}, \
{"[:SENSe]:MARKer:PTRAck",  NR_MARKER_PeakTrack},  /*{int}*/\
{"[:SENSe]:MARKer:PTRAck?", NR_MARKER_PeakTrackQ}, /*{int}*/\
    \
{"[:SENSe]:MARKer:ALLOn",  NR_MARKER_AllOn},           \
{"[:SENSe]:MARKer:ALLClear",  NR_MARKER_ClearAll},           \

scpi_result_t NR_MARKER_Select(scpi_t * context);
scpi_result_t NR_MARKER_SelectQ(scpi_t * context);

scpi_result_t NR_MARKER_DisplayState(scpi_t * context);
scpi_result_t NR_MARKER_DisplayStateQ(scpi_t * context);
scpi_result_t NR_MARKER1_DisplayState(scpi_t * context);
scpi_result_t NR_MARKER1_DisplayStateQ(scpi_t * context);
scpi_result_t NR_MARKER2_DisplayState(scpi_t * context);
scpi_result_t NR_MARKER2_DisplayStateQ(scpi_t * context);
scpi_result_t NR_MARKER3_DisplayState(scpi_t * context);
scpi_result_t NR_MARKER3_DisplayStateQ(scpi_t * context);
scpi_result_t NR_MARKER4_DisplayState(scpi_t * context);
scpi_result_t NR_MARKER4_DisplayStateQ(scpi_t * context);
scpi_result_t NR_MARKER5_DisplayState(scpi_t * context);
scpi_result_t NR_MARKER5_DisplayStateQ(scpi_t * context);
scpi_result_t NR_MARKER6_DisplayState(scpi_t * context);
scpi_result_t NR_MARKER6_DisplayStateQ(scpi_t * context);

scpi_result_t NR_MARKER_Type(scpi_t * context);
scpi_result_t NR_MARKER_TypeQ(scpi_t * context);
scpi_result_t NR_MARKER1_Type(scpi_t * context);
scpi_result_t NR_MARKER1_TypeQ(scpi_t * context);
scpi_result_t NR_MARKER2_Type(scpi_t * context);
scpi_result_t NR_MARKER2_TypeQ(scpi_t * context);
scpi_result_t NR_MARKER3_Type(scpi_t * context);
scpi_result_t NR_MARKER3_TypeQ(scpi_t * context);
scpi_result_t NR_MARKER4_Type(scpi_t * context);
scpi_result_t NR_MARKER4_TypeQ(scpi_t * context);
scpi_result_t NR_MARKER5_Type(scpi_t * context);
scpi_result_t NR_MARKER5_TypeQ(scpi_t * context);
scpi_result_t NR_MARKER6_Type(scpi_t * context);
scpi_result_t NR_MARKER6_TypeQ(scpi_t * context);

scpi_result_t NR_MARKER_NoiseMarker(scpi_t * context);
scpi_result_t NR_MARKER_NoiseMarkerQ(scpi_t * context);
scpi_result_t NR_MARKER1_NoiseMarker(scpi_t * context);
scpi_result_t NR_MARKER1_NoiseMarkerQ(scpi_t * context);
scpi_result_t NR_MARKER2_NoiseMarker(scpi_t * context);
scpi_result_t NR_MARKER2_NoiseMarkerQ(scpi_t * context);
scpi_result_t NR_MARKER3_NoiseMarker(scpi_t * context);
scpi_result_t NR_MARKER3_NoiseMarkerQ(scpi_t * context);
scpi_result_t NR_MARKER4_NoiseMarker(scpi_t * context);
scpi_result_t NR_MARKER4_NoiseMarkerQ(scpi_t * context);
scpi_result_t NR_MARKER5_NoiseMarker(scpi_t * context);
scpi_result_t NR_MARKER5_NoiseMarkerQ(scpi_t * context);
scpi_result_t NR_MARKER6_NoiseMarker(scpi_t * context);
scpi_result_t NR_MARKER6_NoiseMarkerQ(scpi_t * context);

scpi_result_t NR_MARKER_PeakMax(scpi_t * context);
scpi_result_t NR_MARKER_PeakMin(scpi_t * context);
scpi_result_t NR_MARKER_PeakMaxNext(scpi_t * context);
scpi_result_t NR_MARKER_PeakMaxLeft(scpi_t * context);
scpi_result_t NR_MARKER_PeakMaxRight(scpi_t * context);
scpi_result_t NR_MARKER_PeakTrack(scpi_t * context);
scpi_result_t NR_MARKER_PeakTrackQ(scpi_t * context);

scpi_result_t NR_MARKER_AllOn(scpi_t * context);
scpi_result_t NR_MARKER_ClearAll(scpi_t * context);

#ifdef  __cplusplus
}
#endif

#endif // NR_SCPI_MARKER_H
