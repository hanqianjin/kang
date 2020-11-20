#ifndef SCPIDEF_H
#define SCPIDEF_H

#include "type.h"

#include <QLocalServer>
#include <QLocalSocket>
#include <QThread>
#include <QSettings>
#include <QDebug>
#include "scpiport_internet.h"
#include "scpiport_uart.h"
#include "scpiport_usb.h"
#include "scpiport_gpib.h"
#include "localcommunicate.h"
#include "libscpi/inc/scpi/scpi.h"
#include "scpidef/scpidef.h"


#define SCPI_COMMANDS_MISC \
{"*CLS", SCPI_CoreCls,},\
{"*ESE", SCPI_CoreEse,},\
{"*ESE?", SCPI_CoreEseQ,},\
{"*ESR?", SCPI_CoreEsrQ,},\
{"*IDN?", SCPI_CoreIdnQ,},\
{"*OPC", SCPI_CoreOpc,},\
{"*OPC?", SCPI_CoreOpcQ,},\
{"*RST", SCPI_CoreRst,},\
{"*SRE", SCPI_CoreSre,},\
{"*SRE?", SCPI_CoreSreQ,},\
{"*STB?", SCPI_CoreStbQ,},\
{"*TST?", SCPI_CoreTstQ,},\
{"*WAI", SCPI_CoreWai,},\
\
{"STATus:QUEStionable?", SCPI_StatusQuestionableEventQ,},\
{"STATus:QUEStionable:EVENt?", SCPI_StatusQuestionableEventQ,},\
/*{"STATus:QUEStionable:CONDition?", scpi_stub_callback,},*/\
{"STATus:QUEStionable:ENABle", SCPI_StatusQuestionableEnable,},\
{"STATus:QUEStionable:ENABle?", SCPI_StatusQuestionableEnableQ,},\
\
{"STATus:PRESet", SCPI_StatusPreset,},\
\
/* Communication status*/\
{":COMMunicate:REMote", COMM_ModeChange}, /*{ON|OFF|1|0}*/\
{":COMMunicate:TRANsport:FILe", COMM_TransFile}, /*{filelen,save path}*/



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

scpi_result_t COMM_ModeChange(scpi_t * context);
scpi_result_t COMM_TransFile(scpi_t * context);

scpi_bool_t   SCPI_Communicate_Init();
#ifdef  __cplusplus
}
#endif

#endif // SCPIDEF_H
