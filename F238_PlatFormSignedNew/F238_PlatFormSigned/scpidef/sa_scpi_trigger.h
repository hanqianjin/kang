#ifndef SA_SCPI_TRIGGER_H
#define SA_SCPI_TRIGGER_H
#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"


#ifdef  __cplusplus
extern "C" {
#endif


#define SA_SCPI_COMMANDS_TRIGGER \
    /*[ 0 -- FREE_RUN 1 -- EXTERNAL 2 -- VIDEO 3 -- PERIODIC_TIMER 4 -- RF_BURST 5 -- GPS]*/\
{"[:SENSe]:TRIGger:SOURce" ,SA_TRIGGER_Type}, /* {Int}*/\
 {"[:SENSe]:TRIGger:LEVEl"  ,SA_TRIGGER_Level}, /* {Double}*/\
 {"[:SENSe]:TRIGger:EXTErnal:LEVEl" ,SA_TRIGGER_ExteLevel}, /* {Double}*/\
 {"[:SENSe]:TRIGger:VEDIo:LEVEl" ,SA_TRIGGER_VedioLevel}, /* {Double}*/\
 {"[:SENSe]:TRIGger:RFBUrst:LEVEl" ,SA_TRIGGER_RFLevel}, /* {Double}*/\
 {"[:SENSe]:TRIGger:SLOPe"  ,SA_TRIGGER_SlopeState}, /* {Double}*/\
 {"[:SENSe]:TRIGger:EXTErnal:SLOPe" ,SA_TRIGGER_ExteSlope}, /* {Double}*/\
 {"[:SENSe]:TRIGger:VEDIo:SLOPe" ,SA_TRIGGER_VedioSlope}, /* {Double}*/\
 {"[:SENSe]:TRIGger:RFBUrst:SLOPe" ,SA_TRIGGER_RFSlope}, /* {Double}*/\
 {"[:SENSe]:TRIGger:DELAy:STATe"  ,SA_TRIGGER_DelayState}, /* {Int}*/\
 {"[:SENSe]:TRIGger:EXTErnal:DELAy:STATe" ,SA_TRIGGER_ExteDelaySta}, /* {Int}*/\
 {"[:SENSe]:TRIGger:VEDIo:DELAy:STATe" ,SA_TRIGGER_VedioDelaySta}, /* {Int}*/\
 {"[:SENSe]:TRIGger:PERIodic:DELAy:STATe" ,SA_TRIGGER_PeriDelaySta}, /* {Int}*/\
 {"[:SENSe]:TRIGger:RFBUrst:DELAy:STATe" ,SA_TRIGGER_RFDelaySta}, /* {Int}*/\
 {"[:SENSe]:TRIGger:DELAy"  ,SA_TRIGGER_DelayValue}, /* {Double}*/\
 {"[:SENSe]:TRIGger:EXTErnal:DELAy" ,SA_TRIGGER_ExteDelayVal}, /* {Double}*/\
 {"[:SENSe]:TRIGger:VEDIo:DELAy" ,SA_TRIGGER_VedioDelayVal}, /* {Double}*/\
 {"[:SENSe]:TRIGger:PERIodic:DELAy" ,SA_TRIGGER_PeriDelayVal}, /* {Double}*/\
 {"[:SENSe]:TRIGger:RFBUrst:DELAy" ,SA_TRIGGER_RFDelayVal}, /* {Double}*/\
 {"[:SENSe]:TRIGger:PERiodic" ,SA_TRIGGER_PeriTime}, /* {Double}*/\
\
{"[:SENSe]:TRIGger:SOURce?",SA_TRIGGER_TypeQ},/* {Int}*/\
 {"[:SENSe]:TRIGger:LEVEl?"  ,SA_TRIGGER_LevelQ}, /* {Double}*/\
 {"[:SENSe]:TRIGger:EXTErnal:LEVEl?" ,SA_TRIGGER_ExteLevelQ}, /* {Double}*/\
 {"[:SENSe]:TRIGger:VEDIo:LEVEl?" ,SA_TRIGGER_VedioLevelQ}, /* {Double}*/\
 {"[:SENSe]:TRIGger:RFBUrst:LEVEl?" ,SA_TRIGGER_RFLevelQ}, /* {Double}*/\
 {"[:SENSe]:TRIGger:SLOPe?"  ,SA_TRIGGER_SlopeStateQ}, /* {Double}*/\
 {"[:SENSe]:TRIGger:EXTErnal:SLOPe?" ,SA_TRIGGER_ExteSlopeQ}, /* {Double}*/\
 {"[:SENSe]:TRIGger:VEDIo:SLOPe?" ,SA_TRIGGER_VedioSlopeQ}, /* {Double}*/\
 {"[:SENSe]:TRIGger:RFBUrst:SLOPe?" ,SA_TRIGGER_RFSlopeQ}, /* {Double}*/\
 {"[:SENSe]:TRIGger:DELAy:STATe?"  ,SA_TRIGGER_DelayStateQ}, /* {Int}*/\
 {"[:SENSe]:TRIGger:EXTErnal:DELAy:STATe?" ,SA_TRIGGER_ExteDelayStaQ}, /* {Int}*/\
 {"[:SENSe]:TRIGger:VEDIo:DELAy:STATe?" ,SA_TRIGGER_VedioDelayStaQ}, /* {Int}*/\
 {"[:SENSe]:TRIGger:PERIodic:DELAy:STATe?" ,SA_TRIGGER_PeriDelayStaQ}, /* {Int}*/\
 {"[:SENSe]:TRIGger:RFBUrst:DELAy:STATe?" ,SA_TRIGGER_RFDelayStaQ}, /* {Int}*/\
 {"[:SENSe]:TRIGger:DELAy?"  ,SA_TRIGGER_DelayValueQ}, /* {Double}*/\
 {"[:SENSe]:TRIGger:EXTErnal:DELAy?" ,SA_TRIGGER_ExteDelayValQ}, /* {Double}*/\
 {"[:SENSe]:TRIGger:VEDIo:DELAy?" ,SA_TRIGGER_VedioDelayValQ}, /* {Double}*/\
 {"[:SENSe]:TRIGger:PERIodic:DELAy?" ,SA_TRIGGER_PeriDelayValQ}, /* {Double}*/\
 {"[:SENSe]:TRIGger:RFBUrst:DELAy?" ,SA_TRIGGER_RFDelayValQ}, /* {Double}*/\
 {"[:SENSe]:TRIGger:PERiodic?" ,SA_TRIGGER_PeriTimeQ}, /* {Double}*/\

scpi_result_t SA_TRIGGER_Type(scpi_t * context);
scpi_result_t SA_TRIGGER_Level(scpi_t * context);
scpi_result_t SA_TRIGGER_ExteLevel(scpi_t * context);
scpi_result_t SA_TRIGGER_VedioLevel(scpi_t * context);
scpi_result_t SA_TRIGGER_RFLevel(scpi_t * context);

scpi_result_t SA_TRIGGER_SlopeState(scpi_t * context);
scpi_result_t SA_TRIGGER_ExteSlope(scpi_t * context);
scpi_result_t SA_TRIGGER_VedioSlope(scpi_t * context);
scpi_result_t SA_TRIGGER_RFSlope(scpi_t * context);

scpi_result_t SA_TRIGGER_DelayState(scpi_t * context);
scpi_result_t SA_TRIGGER_ExteDelaySta(scpi_t * context);
scpi_result_t SA_TRIGGER_VedioDelaySta(scpi_t * context);
scpi_result_t SA_TRIGGER_PeriDelaySta(scpi_t * context);
scpi_result_t SA_TRIGGER_RFDelaySta(scpi_t * context);


scpi_result_t SA_TRIGGER_DelayValue(scpi_t * context);
scpi_result_t SA_TRIGGER_ExteDelayVal(scpi_t * context);
scpi_result_t SA_TRIGGER_VedioDelayVal(scpi_t * context);
scpi_result_t SA_TRIGGER_PeriDelayVal(scpi_t * context);
scpi_result_t SA_TRIGGER_RFDelayVal(scpi_t * context);
scpi_result_t SA_TRIGGER_PeriTime(scpi_t * context);

scpi_result_t SA_TRIGGER_TypeQ(scpi_t * context);
scpi_result_t SA_TRIGGER_LevelQ(scpi_t * context);
scpi_result_t SA_TRIGGER_ExteLevelQ(scpi_t * context);
scpi_result_t SA_TRIGGER_VedioLevelQ(scpi_t * context);
scpi_result_t SA_TRIGGER_RFLevelQ(scpi_t * context);

scpi_result_t SA_TRIGGER_SlopeStateQ(scpi_t * context);
scpi_result_t SA_TRIGGER_ExteSlopeQ(scpi_t * context);
scpi_result_t SA_TRIGGER_VedioSlopeQ(scpi_t * context);
scpi_result_t SA_TRIGGER_RFSlopeQ(scpi_t * context);

scpi_result_t SA_TRIGGER_DelayStateQ(scpi_t * context);
scpi_result_t SA_TRIGGER_ExteDelayStaQ(scpi_t * context);
scpi_result_t SA_TRIGGER_VedioDelayStaQ(scpi_t * context);
scpi_result_t SA_TRIGGER_PeriDelayStaQ(scpi_t * context);
scpi_result_t SA_TRIGGER_RFDelayStaQ(scpi_t * context);

scpi_result_t SA_TRIGGER_DelayValueQ(scpi_t * context);
scpi_result_t SA_TRIGGER_ExteDelayValQ(scpi_t * context);
scpi_result_t SA_TRIGGER_VedioDelayValQ(scpi_t * context);
scpi_result_t SA_TRIGGER_PeriDelayValQ(scpi_t * context);
scpi_result_t SA_TRIGGER_RFDelayValQ(scpi_t * context);
scpi_result_t SA_TRIGGER_PeriTimeQ(scpi_t * context);

#ifdef  __cplusplus
}
#endif


#endif // SA_SCPI_TRIGGER_H
