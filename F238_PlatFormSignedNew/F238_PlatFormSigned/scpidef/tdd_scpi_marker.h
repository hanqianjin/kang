#ifndef TDD_SCPI_MARKER_H
#define TDD_SCPI_MARKER_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TDD_SCPI_COMMANDS_MARKER \
{"[:SENSe]:MARKer:SELEct", TDD_MARKER_Select},/*{int}*/\
{"[:SENSe]:MARKer:DISPlay", TDD_MARKER_ViewStatus},/*{int}*/\
{"[:SENSe]:MARKer:1:DISPlay", TDD_MARKER1_ViewStatus},/*{int}*/\
{"[:SENSe]:MARKer:2:DISPlay", TDD_MARKER2_ViewStatus},/*{int}*/\
{"[:SENSe]:MARKer:3:DISPlay", TDD_MARKER3_ViewStatus},/*{int}*/\
{"[:SENSe]:MARKer:4:DISPlay", TDD_MARKER4_ViewStatus},/*{int}*/\
{"[:SENSe]:MARKer:5:DISPlay", TDD_MARKER5_ViewStatus},/*{int}*/\
{"[:SENSe]:MARKer:6:DISPlay", TDD_MARKER6_ViewStatus},/*{int}*/\
{"[:SENSe]:MARKer:TYPE", TDD_MARKER_Type},/*{int}*/\
{"[:SENSe]:MARKer:1:TYPE", TDD_MARKER1_Type},/*{int}*/\
{"[:SENSe]:MARKer:2:TYPE", TDD_MARKER2_Type},/*{int}*/\
{"[:SENSe]:MARKer:3:TYPE", TDD_MARKER3_Type},/*{int}*/\
{"[:SENSe]:MARKer:4:TYPE", TDD_MARKER4_Type},/*{int}*/\
{"[:SENSe]:MARKer:5:TYPE", TDD_MARKER5_Type},/*{int}*/\
{"[:SENSe]:MARKer:6:TYPE", TDD_MARKER6_Type},/*{int}*/\
{"[:SENSe]:MARKer:NOISe:STATe", TDD_MARKER_NoiseMarker},/*{int}*/\
{"[:SENSe]:MARKer:1:NOISe:STATe", TDD_MARKER1_NoiseMarker},/*{int}*/\
{"[:SENSe]:MARKer:2:NOISe:STATe", TDD_MARKER2_NoiseMarker},/*{int}*/\
{"[:SENSe]:MARKer:3:NOISe:STATe", TDD_MARKER3_NoiseMarker},/*{int}*/\
{"[:SENSe]:MARKer:4:NOISe:STATe", TDD_MARKER4_NoiseMarker},/*{int}*/\
{"[:SENSe]:MARKer:5:NOISe:STATe", TDD_MARKER5_NoiseMarker},/*{int}*/\
{"[:SENSe]:MARKer:6:NOISe:STATe", TDD_MARKER6_NoiseMarker},/*{int}*/\
{"[:SENSe]:MARKer:ALLOn", TDD_MARKER_AllOn},/*{none}*/\
{"[:SENSe]:MARKer:ALLClear", TDD_MARKER_ClearAll},/*{none}*/\
{"[:SENSe]:MARKer:PMAXimum", TDD_MARKER_PeakMax},/*{none}*/\
{"[:SENSe]:MARKer:PMINimum", TDD_MARKER_PeakMin},/*{none}*/\
{"[:SENSe]:MARKer:PMAXimum:NEXT", TDD_MARKER_PeakMaxNext},/*{none}*/\
{"[:SENSe]:MARKer:PMAXimum:LEFT", TDD_MARKER_PeakMaxLeft},/*{none}*/\
{"[:SENSe]:MARKer:PMAXimum:RIGHT", TDD_MARKER_PeakMaxRight},/*{none}*/\
{"[:SENSe]:MARKer:PTRAck", TDD_MARKER_PeakTrack},/*{int}*/\
\
{"[:SENSe]:MARKer:SELEct?", TDD_MARKER_SelectQ},/*{int}*/\
{"[:SENSe]:MARKer:DISPlay?", TDD_MARKER_ViewStatusQ},/*{int}*/\
{"[:SENSe]:MARKer:1:DISPlay?", TDD_MARKER1_ViewStatusQ},/*{int}*/\
{"[:SENSe]:MARKer:2:DISPlay?", TDD_MARKER2_ViewStatusQ},/*{int}*/\
{"[:SENSe]:MARKer:3:DISPlay?", TDD_MARKER3_ViewStatusQ},/*{int}*/\
{"[:SENSe]:MARKer:4:DISPlay?", TDD_MARKER4_ViewStatusQ},/*{int}*/\
{"[:SENSe]:MARKer:5:DISPlay?", TDD_MARKER5_ViewStatusQ},/*{int}*/\
{"[:SENSe]:MARKer:6:DISPlay?", TDD_MARKER6_ViewStatusQ},/*{int}*/\
{"[:SENSe]:MARKer:TYPE?", TDD_MARKER_TypeQ},/*{int}*/\
{"[:SENSe]:MARKer:1:TYPE?", TDD_MARKER1_TypeQ},/*{int}*/\
{"[:SENSe]:MARKer:2:TYPE?", TDD_MARKER2_TypeQ},/*{int}*/\
{"[:SENSe]:MARKer:3:TYPE?", TDD_MARKER3_TypeQ},/*{int}*/\
{"[:SENSe]:MARKer:4:TYPE?", TDD_MARKER4_TypeQ},/*{int}*/\
{"[:SENSe]:MARKer:5:TYPE?", TDD_MARKER5_TypeQ},/*{int}*/\
{"[:SENSe]:MARKer:6:TYPE?", TDD_MARKER6_TypeQ},/*{int}*/\
{"[:SENSe]:MARKer:NOISe:STATe?", TDD_MARKER_NoiseMarkerQ},/*{int}*/\
{"[:SENSe]:MARKer:1:NOISe:STATe?", TDD_MARKER1_NoiseMarkerQ},/*{int}*/\
{"[:SENSe]:MARKer:2:NOISe:STATe?", TDD_MARKER2_NoiseMarkerQ},/*{int}*/\
{"[:SENSe]:MARKer:3:NOISe:STATe?", TDD_MARKER3_NoiseMarkerQ},/*{int}*/\
{"[:SENSe]:MARKer:4:NOISe:STATe?", TDD_MARKER4_NoiseMarkerQ},/*{int}*/\
{"[:SENSe]:MARKer:5:NOISe:STATe?", TDD_MARKER5_NoiseMarkerQ},/*{int}*/\
{"[:SENSe]:MARKer:6:NOISe:STATe?", TDD_MARKER6_NoiseMarkerQ},/*{int}*/\
{"[:SENSe]:MARKer:PTRAck?", TDD_MARKER_PeakTrackQ},/*{int}*/\

scpi_result_t TDD_MARKER_Select(scpi_t * context);
scpi_result_t TDD_MARKER_ViewStatus(scpi_t * context);
scpi_result_t TDD_MARKER1_ViewStatus(scpi_t * context);
scpi_result_t TDD_MARKER2_ViewStatus(scpi_t * context);
scpi_result_t TDD_MARKER3_ViewStatus(scpi_t * context);
scpi_result_t TDD_MARKER4_ViewStatus(scpi_t * context);
scpi_result_t TDD_MARKER5_ViewStatus(scpi_t * context);
scpi_result_t TDD_MARKER6_ViewStatus(scpi_t * context);
scpi_result_t TDD_MARKER_Type(scpi_t * context);
scpi_result_t TDD_MARKER1_Type(scpi_t * context);
scpi_result_t TDD_MARKER2_Type(scpi_t * context);
scpi_result_t TDD_MARKER3_Type(scpi_t * context);
scpi_result_t TDD_MARKER4_Type(scpi_t * context);
scpi_result_t TDD_MARKER5_Type(scpi_t * context);
scpi_result_t TDD_MARKER6_Type(scpi_t * context);
scpi_result_t TDD_MARKER_NoiseMarker(scpi_t * context);
scpi_result_t TDD_MARKER1_NoiseMarker(scpi_t * context);
scpi_result_t TDD_MARKER2_NoiseMarker(scpi_t * context);
scpi_result_t TDD_MARKER3_NoiseMarker(scpi_t * context);
scpi_result_t TDD_MARKER4_NoiseMarker(scpi_t * context);
scpi_result_t TDD_MARKER5_NoiseMarker(scpi_t * context);
scpi_result_t TDD_MARKER6_NoiseMarker(scpi_t * context);
scpi_result_t TDD_MARKER_PeakTrack(scpi_t * context);
scpi_result_t TDD_MARKER_AllOn(scpi_t * context);
scpi_result_t TDD_MARKER_ClearAll(scpi_t * context);
scpi_result_t TDD_MARKER_PeakMax(scpi_t * context);
scpi_result_t TDD_MARKER_PeakMin(scpi_t * context);
scpi_result_t TDD_MARKER_PeakMaxNext(scpi_t * context);
scpi_result_t TDD_MARKER_PeakMaxLeft(scpi_t * context);
scpi_result_t TDD_MARKER_PeakMaxRight(scpi_t * context);

scpi_result_t TDD_MARKER_SelectQ(scpi_t * context);
scpi_result_t TDD_MARKER_ViewStatusQ(scpi_t * context);
scpi_result_t TDD_MARKER1_ViewStatusQ(scpi_t * context);
scpi_result_t TDD_MARKER2_ViewStatusQ(scpi_t * context);
scpi_result_t TDD_MARKER3_ViewStatusQ(scpi_t * context);
scpi_result_t TDD_MARKER4_ViewStatusQ(scpi_t * context);
scpi_result_t TDD_MARKER5_ViewStatusQ(scpi_t * context);
scpi_result_t TDD_MARKER6_ViewStatusQ(scpi_t * context);
scpi_result_t TDD_MARKER_TypeQ(scpi_t * context);
scpi_result_t TDD_MARKER1_TypeQ(scpi_t * context);
scpi_result_t TDD_MARKER2_TypeQ(scpi_t * context);
scpi_result_t TDD_MARKER3_TypeQ(scpi_t * context);
scpi_result_t TDD_MARKER4_TypeQ(scpi_t * context);
scpi_result_t TDD_MARKER5_TypeQ(scpi_t * context);
scpi_result_t TDD_MARKER6_TypeQ(scpi_t * context);
scpi_result_t TDD_MARKER_NoiseMarkerQ(scpi_t * context);
scpi_result_t TDD_MARKER1_NoiseMarkerQ(scpi_t * context);
scpi_result_t TDD_MARKER2_NoiseMarkerQ(scpi_t * context);
scpi_result_t TDD_MARKER3_NoiseMarkerQ(scpi_t * context);
scpi_result_t TDD_MARKER4_NoiseMarkerQ(scpi_t * context);
scpi_result_t TDD_MARKER5_NoiseMarkerQ(scpi_t * context);
scpi_result_t TDD_MARKER6_NoiseMarkerQ(scpi_t * context);
scpi_result_t TDD_MARKER_PeakTrackQ(scpi_t * context);

#ifdef __cplusplus
}
#endif

#endif // TDD_SCPI_MARKER_H
