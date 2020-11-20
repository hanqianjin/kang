#ifndef RTSA_SCPI_TRIGGER_H
#define RTSA_SCPI_TRIGGER_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"


#ifdef  __cplusplus
extern "C" {
#endif


#define RTSA_SCPI_COMMANDS_TRIGGER \
    /*[ 0 -- FREE_RUN 1 -- EXTERNAL 2 -- VIDEO 3 -- PERIODIC_TIMER 4 -- RF_BURST 5 -- GPS]*/\
{"[:SENSe]:TRIGger:SOURce" ,RTSA_TRIGGER_Type}, /* {Int}*/\
 {"[:SENSe]:TRIGger:LEVEl"  ,RTSA_TRIGGER_Level}, /* {Double}*/\
 {"[:SENSe]:TRIGger:EXTErnal:LEVEl" ,RTSA_TRIGGER_ExteLevel}, /* {Double}*/\
 {"[:SENSe]:TRIGger:VEDIo:LEVEl" ,RTSA_TRIGGER_VedioLevel}, /* {Double}*/\
 {"[:SENSe]:TRIGger:RFBUrst:LEVEl" ,RTSA_TRIGGER_RFLevel}, /* {Double}*/\
 {"[:SENSe]:TRIGger:SLOPe"  ,RTSA_TRIGGER_SlopeState}, /* {Double}*/\
 {"[:SENSe]:TRIGger:EXTErnal:SLOPe" ,RTSA_TRIGGER_ExteSlope}, /* {Double}*/\
 {"[:SENSe]:TRIGger:VEDIo:SLOPe" ,RTSA_TRIGGER_VedioSlope}, /* {Double}*/\
 {"[:SENSe]:TRIGger:RFBUrst:SLOPe" ,RTSA_TRIGGER_RFSlope}, /* {Double}*/\
 {"[:SENSe]:TRIGger:DELAy:STATe"  ,RTSA_TRIGGER_DelayState}, /* {Int}*/\
 {"[:SENSe]:TRIGger:EXTErnal:DELAy:STATe" ,RTSA_TRIGGER_ExteDelaySta}, /* {Int}*/\
 {"[:SENSe]:TRIGger:VEDIo:DELAy:STATe" ,RTSA_TRIGGER_VedioDelaySta}, /* {Int}*/\
 {"[:SENSe]:TRIGger:PERIodic:DELAy:STATe" ,RTSA_TRIGGER_PeriDelaySta}, /* {Int}*/\
 {"[:SENSe]:TRIGger:RFBUrst:DELAy:STATe" ,RTSA_TRIGGER_RFDelaySta}, /* {Int}*/\
 {"[:SENSe]:TRIGger:DELAy"  ,RTSA_TRIGGER_DelayValue}, /* {Double}*/\
 {"[:SENSe]:TRIGger:EXTErnal:DELAy" ,RTSA_TRIGGER_ExteDelayVal}, /* {Double}*/\
 {"[:SENSe]:TRIGger:VEDIo:DELAy" ,RTSA_TRIGGER_VedioDelayVal}, /* {Double}*/\
 {"[:SENSe]:TRIGger:PERIodic:DELAy" ,RTSA_TRIGGER_PeriDelayVal}, /* {Double}*/\
 {"[:SENSe]:TRIGger:RFBUrst:DELAy" ,RTSA_TRIGGER_RFDelayVal}, /* {Double}*/\
 {"[:SENSe]:TRIGger:PERiodic" ,RTSA_TRIGGER_PeriTime}, /* {Double}*/\
\
{"[:SENSe]:TRIGger:SOURce?",RTSA_TRIGGER_TypeQ},/* {Int}*/\
 {"[:SENSe]:TRIGger:LEVEl?"  ,RTSA_TRIGGER_LevelQ}, /* {Double}*/\
 {"[:SENSe]:TRIGger:EXTErnal:LEVEl?" ,RTSA_TRIGGER_ExteLevelQ}, /* {Double}*/\
 {"[:SENSe]:TRIGger:VEDIo:LEVEl?" ,RTSA_TRIGGER_VedioLevelQ}, /* {Double}*/\
 {"[:SENSe]:TRIGger:RFBUrst:LEVEl?" ,RTSA_TRIGGER_RFLevelQ}, /* {Double}*/\
 {"[:SENSe]:TRIGger:SLOPe?"  ,RTSA_TRIGGER_SlopeStateQ}, /* {Double}*/\
 {"[:SENSe]:TRIGger:EXTErnal:SLOPe?" ,RTSA_TRIGGER_ExteSlopeQ}, /* {Double}*/\
 {"[:SENSe]:TRIGger:VEDIo:SLOPe?" ,RTSA_TRIGGER_VedioSlopeQ}, /* {Double}*/\
 {"[:SENSe]:TRIGger:RFBUrst:SLOPe?" ,RTSA_TRIGGER_RFSlopeQ}, /* {Double}*/\
 {"[:SENSe]:TRIGger:DELAy:STATe?"  ,RTSA_TRIGGER_DelayStateQ}, /* {Int}*/\
 {"[:SENSe]:TRIGger:EXTErnal:DELAy:STATe?" ,RTSA_TRIGGER_ExteDelayStaQ}, /* {Int}*/\
 {"[:SENSe]:TRIGger:VEDIo:DELAy:STATe?" ,RTSA_TRIGGER_VedioDelayStaQ}, /* {Int}*/\
 {"[:SENSe]:TRIGger:PERIodic:DELAy:STATe?" ,RTSA_TRIGGER_PeriDelayStaQ}, /* {Int}*/\
 {"[:SENSe]:TRIGger:RFBUrst:DELAy:STATe?" ,RTSA_TRIGGER_RFDelayStaQ}, /* {Int}*/\
 {"[:SENSe]:TRIGger:DELAy?"  ,RTSA_TRIGGER_DelayValueQ}, /* {Double}*/\
 {"[:SENSe]:TRIGger:EXTErnal:DELAy?" ,RTSA_TRIGGER_ExteDelayValQ}, /* {Double}*/\
 {"[:SENSe]:TRIGger:VEDIo:DELAy?" ,RTSA_TRIGGER_VedioDelayValQ}, /* {Double}*/\
 {"[:SENSe]:TRIGger:PERIodic:DELAy?" ,RTSA_TRIGGER_PeriDelayValQ}, /* {Double}*/\
 {"[:SENSe]:TRIGger:RFBUrst:DELAy?" ,RTSA_TRIGGER_RFDelayValQ}, /* {Double}*/\
 {"[:SENSe]:TRIGger:PERiodic?" ,RTSA_TRIGGER_PeriTimeQ}, /* {Double}*/\
\
{"[:SENSe]:TRIGger:EXTErnal:HOLDoff" ,RTSA_TRIGGER_Extern_HoldOff}, /* {Double}*/\
{"[:SENSe]:TRIGger:EXTErnal:HOLDoff?" ,RTSA_TRIGGER_Extern_HoldOffQ}, /* {Double}*/\
{"[:SENSe]:TRIGger:RFBUrst:HOLDoff" ,RTSA_TRIGGER_RFburst_HoldOff}, /* {Double}*/\
{"[:SENSe]:TRIGger:RFBUrst:HOLDoff?" ,RTSA_TRIGGER_RFburst_HoldOffQ}, /* {Double}*/\
{"[:SENSe]:TRIGger:FMT:HOLDoff" ,RTSA_TRIGGER_Fmt_HoldOff}, /* {Double}*/\
{"[:SENSe]:TRIGger:FMT:HOLDoff?" ,RTSA_TRIGGER_Fmt_HoldOffQ}, /* {Double}*/\
\
 {"[:SENSe]:TRIGger:FMT:MASK:BUILd" ,RTSA_TRIGGER_Fmt_Mask_build}, /* {none}*/\
 {"[:SENSe]:TRIGger:FMT:MASK:DELete" ,RTSA_TRIGGER_Fmt_Mask_Delete}, /* {none}*/\
\
{"[:SENSe]:TRIGger:FMT:MASK:TYPE" ,RTSA_TRIGGER_Fmt_Mask_Type}, /* {0--upper 1--lower}*/\
{"[:SENSe]:TRIGger:FMT:MASK:TYPE?" ,RTSA_TRIGGER_Fmt_Mask_TypeQ}, /* {none}*/\
{"[:SENSe]:TRIGger:FMT:MASK:CRITertion" ,RTSA_TRIGGER_Fmt_Mask_Critertion}, /* {none}*/\
{"[:SENSe]:TRIGger:FMT:MASK:CRITertion?" ,RTSA_TRIGGER_Fmt_Mask_CritertionQ}, /* {none}*/\
\
{"[:SENSe]:TRIGger:FMT:MASK:COUNt?",RTSA_TRIGGER_Fmt_Mask_PointCountQ}, \
\
{"[:SENSe]:TRIGger:FMT:MASK:DATA:FREQuency",RTSA_TRIGGER_Fmt_Mask_PointFreqData}, \
{"[:SENSe]:TRIGger:FMT:MASK:DATA:FREQuency?",RTSA_TRIGGER_Fmt_Mask_PointFreqDataQ}, \
{"[:SENSe]:TRIGger:FMT:MASK:DATA:AMPLitude",RTSA_TRIGGER_Fmt_Mask_PointAmptData}, \
{"[:SENSe]:TRIGger:FMT:MASK:DATA:AMPLitude?",RTSA_TRIGGER_Fmt_Mask_PointAmptDataQ}, \
\
{"[:SENSe]:TRIGger:FMT:MASK:INSErt",RTSA_TRIGGER_Fmt_Mask_Insert}, \




scpi_result_t RTSA_TRIGGER_Type(scpi_t * context);
scpi_result_t RTSA_TRIGGER_Level(scpi_t * context);
scpi_result_t RTSA_TRIGGER_ExteLevel(scpi_t * context);
scpi_result_t RTSA_TRIGGER_VedioLevel(scpi_t * context);
scpi_result_t RTSA_TRIGGER_RFLevel(scpi_t * context);

scpi_result_t RTSA_TRIGGER_SlopeState(scpi_t * context);
scpi_result_t RTSA_TRIGGER_ExteSlope(scpi_t * context);
scpi_result_t RTSA_TRIGGER_VedioSlope(scpi_t * context);
scpi_result_t RTSA_TRIGGER_RFSlope(scpi_t * context);

scpi_result_t RTSA_TRIGGER_DelayState(scpi_t * context);
scpi_result_t RTSA_TRIGGER_ExteDelaySta(scpi_t * context);
scpi_result_t RTSA_TRIGGER_VedioDelaySta(scpi_t * context);
scpi_result_t RTSA_TRIGGER_PeriDelaySta(scpi_t * context);
scpi_result_t RTSA_TRIGGER_RFDelaySta(scpi_t * context);


scpi_result_t RTSA_TRIGGER_DelayValue(scpi_t * context);
scpi_result_t RTSA_TRIGGER_ExteDelayVal(scpi_t * context);
scpi_result_t RTSA_TRIGGER_VedioDelayVal(scpi_t * context);
scpi_result_t RTSA_TRIGGER_PeriDelayVal(scpi_t * context);
scpi_result_t RTSA_TRIGGER_RFDelayVal(scpi_t * context);
scpi_result_t RTSA_TRIGGER_PeriTime(scpi_t * context);

scpi_result_t RTSA_TRIGGER_TypeQ(scpi_t * context);
scpi_result_t RTSA_TRIGGER_LevelQ(scpi_t * context);
scpi_result_t RTSA_TRIGGER_ExteLevelQ(scpi_t * context);
scpi_result_t RTSA_TRIGGER_VedioLevelQ(scpi_t * context);
scpi_result_t RTSA_TRIGGER_RFLevelQ(scpi_t * context);

scpi_result_t RTSA_TRIGGER_SlopeStateQ(scpi_t * context);
scpi_result_t RTSA_TRIGGER_ExteSlopeQ(scpi_t * context);
scpi_result_t RTSA_TRIGGER_VedioSlopeQ(scpi_t * context);
scpi_result_t RTSA_TRIGGER_RFSlopeQ(scpi_t * context);

scpi_result_t RTSA_TRIGGER_DelayStateQ(scpi_t * context);
scpi_result_t RTSA_TRIGGER_ExteDelayStaQ(scpi_t * context);
scpi_result_t RTSA_TRIGGER_VedioDelayStaQ(scpi_t * context);
scpi_result_t RTSA_TRIGGER_PeriDelayStaQ(scpi_t * context);
scpi_result_t RTSA_TRIGGER_RFDelayStaQ(scpi_t * context);

scpi_result_t RTSA_TRIGGER_DelayValueQ(scpi_t * context);
scpi_result_t RTSA_TRIGGER_ExteDelayValQ(scpi_t * context);
scpi_result_t RTSA_TRIGGER_VedioDelayValQ(scpi_t * context);
scpi_result_t RTSA_TRIGGER_PeriDelayValQ(scpi_t * context);
scpi_result_t RTSA_TRIGGER_RFDelayValQ(scpi_t * context);
scpi_result_t RTSA_TRIGGER_PeriTimeQ(scpi_t * context);

scpi_result_t RTSA_TRIGGER_Extern_HoldOff(scpi_t * context);
scpi_result_t RTSA_TRIGGER_Extern_HoldOffQ(scpi_t * context);
scpi_result_t RTSA_TRIGGER_RFburst_HoldOff(scpi_t * context);
scpi_result_t RTSA_TRIGGER_RFburst_HoldOffQ(scpi_t * context);
scpi_result_t RTSA_TRIGGER_Fmt_HoldOff(scpi_t * context);
scpi_result_t RTSA_TRIGGER_Fmt_HoldOffQ(scpi_t * context);


scpi_result_t RTSA_TRIGGER_Fmt_Mask_build(scpi_t * context);
scpi_result_t RTSA_TRIGGER_Fmt_Mask_Delete(scpi_t * context);

scpi_result_t RTSA_TRIGGER_Fmt_Mask_Type(scpi_t * context);
scpi_result_t RTSA_TRIGGER_Fmt_Mask_TypeQ(scpi_t * context);

scpi_result_t RTSA_TRIGGER_Fmt_Mask_Critertion(scpi_t * context);
scpi_result_t RTSA_TRIGGER_Fmt_Mask_CritertionQ(scpi_t * context);

scpi_result_t RTSA_TRIGGER_Fmt_Mask_PointCountQ(scpi_t * context);
scpi_result_t RTSA_TRIGGER_Fmt_Mask_PointFreqData(scpi_t * context);
scpi_result_t RTSA_TRIGGER_Fmt_Mask_PointFreqDataQ(scpi_t * context);
scpi_result_t RTSA_TRIGGER_Fmt_Mask_PointAmptData(scpi_t * context);
scpi_result_t RTSA_TRIGGER_Fmt_Mask_PointAmptDataQ(scpi_t * context);
scpi_result_t RTSA_TRIGGER_Fmt_Mask_Insert(scpi_t * context);


#ifdef  __cplusplus
}
#endif

#endif // RTSA_SCPI_TRIGGER_H
