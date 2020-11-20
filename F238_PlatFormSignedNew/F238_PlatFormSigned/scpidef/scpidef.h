#ifndef SCPIDEF_H
#define SCPIDEF_H

#include "multicommu/type.h"

#include <QLocalServer>
#include <QLocalSocket>
#include <QThread>
#include <QSettings>
#include <QDebug>
#include "multicommu/scpiport_internet.h"
#include "multicommu/scpiport_uart.h"
#include "multicommu/scpiport_usb.h"
#include "multicommu/localcommunicate.h"
#include "libscpi/inc/scpi/scpi.h"
#include "scpidef/scpidef.h"

#include "dataconfig/ConfigData.h"


#define SCPI_COMMANDS_MISC \
{"*CLS", SCPI_CoreCls},\
{"*ESE", SCPI_CoreEse},\
{"*ESE?", SCPI_CoreEseQ},\
{"*ESR?", SCPI_CoreEsrQ},\
{"*IDN?", SCPI_CoreIdnQ},\
{"*OPC", SCPI_CoreOpc},\
{"*OPC?", SCPI_CoreOpcQ},\
{"*RST", SCPI_CoreRst},\
{"*SRE", SCPI_CoreSre},\
{"*SRE?", SCPI_CoreSreQ},\
{"*STB?", SCPI_CoreStbQ},\
{"*TST?", SCPI_CoreTstQ},\
{"*WAI", SCPI_CoreWai},\
{"EXCEclear", SCPI_ClearExcenotic},\
{":CALCrun", SCPI_CalcRun},\
{":NETSet:IPADdr", SCPI_SetIp},\
{":NETSet:MASKaddr", SCPI_SetMask},\
{":NETSet:GATEaddr", SCPI_SetGate},\
{":NETSet:NETPort", SCPI_SetPort},\  
{":NETSet:WIFI:SWITch", SCPI_SetWifiswitch},\
{":NETSet:WIFI:MIBCode", SCPI_SetWifimib},\
{":NETSet:BLUEteeth:SWITch", SCPI_Blueswitch},\
{"STATus:QUEStionable?", SCPI_StatusQuestionableEventQ},\
{"STATus:QUEStionable:EVENt?", SCPI_StatusQuestionableEventQ},\
  /*{"STATus:QUEStionable:CONDition?", scpi_stub_callback,},*/\
{"STATus:QUEStionable:ENABle", SCPI_StatusQuestionableEnable},\
{"STATus:QUEStionable:ENABle?", SCPI_StatusQuestionableEnableQ},\
  \
{"STATus:PRESet", SCPI_StatusPreset},\
  \
  /* Communication status*/\
{":COMMunicate:TRANsport:FILe:SEND", COMM_TransFile_Receive},/*{filelen,save path}*//*Receive remote files*/\
{":COMMunicate:TRANsport:FILe:RECEive", COMM_TransFile_Send},/*{Source file path,save path}*//*Send files to remote*/\
{":INSTrument:SELEct:ANAMode",SWITCH_Anamode},\
{":INSTrument:CLOSe:ANAMode",CLOSE_Anamode},\
{":INSTrument:VOLUme",VOLU_Ctrl},\
{":INSTrument:VOLUme:SWITch",VOLU_Switch_Ctrl},\
{":INSTrument:BRIGhtness",BRIGness_Ctrl},\
{":INSTrument:DATEtype",DATEtype_Ctrl},\
{":INSTrument:DISPlay",DISPlay_Ctrl},\
{":INSTrument:SLEEp",SLEEp_Ctrl},\
{":INSTrument:GPSEnable",GPSwitch_Ctrl},\
\
{":STATus:RF:TMPTUre?",RF_TemptureQ},/*{Double}*/\
{":STATus:BOARD:TMPTUre?",BOARD_TemptureQ},/*{Double}*/\
{":STATus:FPGA:TMPTUre?",FPGA_TemptureQ},/*{Double}*/\
{":STATus:BATTERY:TMPTUre?",BATTERY_TemptureQ},/*{Double}*/\
\
{"[:SENSe]:CONFig:PLATform:ALL",PlatForm_Config},/*{AJSON}*/\
{"[:SENSe]:CONFig:PLATform:ALL?",PlatForm_ConfigQ},/*{AJSON}*/\
{"[:SENSe]:CONFig:RUNMode:ALL",RunMode_Config},/*{AJSON}*/\
{"[:SENSe]:CONFig:RUNMode:ALL?",RunMode_ConfigQ},/*{AJSON}*/\
\
{":INSTrument:DeviceCalibrate",Deviece_Calibrate},\

extern scpi_t scpi_context;
extern SYSTEM_STATUS g_systemStatus;

#ifdef  __cplusplus
extern "C" {
#endif


scpi_result_t RF_TemptureQ(scpi_t * context);
scpi_result_t BOARD_TemptureQ(scpi_t * context);
scpi_result_t FPGA_TemptureQ(scpi_t * context);
scpi_result_t BATTERY_TemptureQ(scpi_t * context);

scpi_result_t PlatForm_Config(scpi_t *context);
scpi_result_t PlatForm_ConfigQ(scpi_t *context);
scpi_result_t RunMode_Config(scpi_t *context);
scpi_result_t RunMode_ConfigQ(scpi_t *context);

scpi_result_t Notify_Msg();

size_t SCPI_Write(scpi_t * context, const char * data, size_t len);
int SCPI_Error(scpi_t * context, int_fast16_t err);
scpi_result_t SCPI_Control(scpi_t * context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val);
scpi_result_t SCPI_Reset(scpi_t * context);
scpi_result_t SCPI_Test(scpi_t * context);
scpi_result_t SCPI_Flush(scpi_t * context);
scpi_result_t SCPI_CalcRun(scpi_t * context);
scpi_result_t SCPI_ClearExcenotic(scpi_t * context);

scpi_result_t COMM_ModeChange(scpi_t * context);
scpi_result_t COMM_TransFile_Send(scpi_t * context);
scpi_result_t COMM_TransFile_Receive(scpi_t * context);

scpi_result_t SWITCH_Anamode(scpi_t * context);
scpi_result_t CLOSE_Anamode(scpi_t * context);

scpi_result_t VOLU_Ctrl(scpi_t * context);
scpi_result_t VOLU_Switch_Ctrl(scpi_t * context);
scpi_result_t BRIGness_Ctrl(scpi_t * context);
scpi_result_t DATEtype_Ctrl(scpi_t * context);
scpi_result_t DISPlay_Ctrl(scpi_t * context);
scpi_result_t SLEEp_Ctrl(scpi_t * context);
scpi_result_t GPSwitch_Ctrl(scpi_t * context);
scpi_result_t SCPI_SetIp(scpi_t * context);
scpi_result_t SCPI_SetMask(scpi_t * context);
scpi_result_t SCPI_SetGate(scpi_t * context);
scpi_result_t SCPI_SetPort(scpi_t * context);
scpi_result_t SCPI_SetWifiswitch(scpi_t * context);
scpi_result_t SCPI_SetWifimib(scpi_t * context);
scpi_result_t SCPI_Blueswitch(scpi_t * context);

scpi_result_t Deviece_Calibrate(scpi_t * context);

///
scpi_bool_t   SCPI_SetSCPI_Port(qint32* port);
scpi_bool_t   SCPI_Communicate_Init();
#ifdef  __cplusplus
}
#endif

#endif // SCPIDEF_H
