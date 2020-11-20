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
{":CALCrun", SCPI_CalcRun},\
{":NETSet:IPADdr", SCPI_SetIp},\
{":NETSet:MASKaddr", SCPI_SetMask},\
{":NETSet:GATEaddr", SCPI_SetGate},\
{":NETSet:NETPort", SCPI_SetPort},\  
/*{":NETSet:WIFI:SWITch", SCPI_SetWifiswitch},\
{":NETSet:WIFI:MIBCode", SCPI_SetWifimib},\
{":NETSet:BLUEteeth:SWITch", SCPI_Blueswitch},\
*/\
{"STATus:QUEStionable?", SCPI_StatusQuestionableEventQ},\
{"STATus:QUEStionable:EVENt?", SCPI_StatusQuestionableEventQ},\
  /*{"STATus:QUEStionable:CONDition?", scpi_stub_callback,},*/\
{"STATus:QUEStionable:ENABle", SCPI_StatusQuestionableEnable},\
{"STATus:QUEStionable:ENABle?", SCPI_StatusQuestionableEnableQ},\
  \
{"STATus:PRESet", SCPI_StatusPreset},\
  \
  /* Communication status*/\
{":COMMunicate:TRANsport:FILe", COMM_TransFile},/*{filelen,save path}*/\
{":INSTrument:SELEct:ANAMode",SWITCH_Anamode},\
{":INSTrument:CLOSe:ANAMode",CLOSE_Anamode},\
{":INSTrument:VOLUme",VOLU_Ctrl},\
{":INSTrument:VOLUme:SWITch",VOLU_Switch_Ctrl},\
{":INSTrument:BRIGhtness",BRIGness_Ctrl},\
{":INSTrument:DATEtype",DATEtype_Ctrl},\
{":INSTrument:DISPlay",DISPlay_Ctrl},\
{":INSTrument:SLEEp",SLEEp_Ctrl},\
{":INSTrument:GPSEnable",GPSwitch_Ctrl},\


extern scpi_t scpi_context;
extern SYSTEM_STATUS g_systemStatus;

#ifdef  __cplusplus
extern "C" {
#endif



size_t SCPI_Write(scpi_t * context, const char * data, size_t len);
int SCPI_Error(scpi_t * context, int_fast16_t err);
scpi_result_t SCPI_Control(scpi_t * context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val);
scpi_result_t SCPI_Reset(scpi_t * context);
scpi_result_t SCPI_Test(scpi_t * context);
scpi_result_t SCPI_Flush(scpi_t * context);
scpi_result_t SCPI_CalcRun(scpi_t * context);

scpi_result_t COMM_ModeChange(scpi_t * context);
scpi_result_t COMM_TransFile(scpi_t * context);

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
//scpi_result_t SCPI_SetWifiswitch(scpi_t * context);
//scpi_result_t SCPI_SetWifimib(scpi_t * context);
//scpi_result_t SCPI_Blueswitch(scpi_t * context);

///
scpi_bool_t   SCPI_SetSCPI_Port(qint32* port);
scpi_bool_t   SCPI_Communicate_Init();
#ifdef  __cplusplus
}
#endif

#endif // SCPIDEF_H
