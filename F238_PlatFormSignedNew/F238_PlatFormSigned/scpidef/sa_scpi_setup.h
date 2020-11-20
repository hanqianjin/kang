#ifndef SA_SCPI_SETUP_H
#define SA_SCPI_SETUP_H

#include "libscpi/inc/scpi/scpi.h"
#include "multicommu/type.h"
#include "libscpi/inc/scpi/utils_private.h"


#ifdef  __cplusplus
extern "C" {
#endif


#define SA_SCPI_COMMANDS_SETUP \
{"[:SENSe]:MENU" ,SA_Menu_Checked}, /* {Int}*/\
{"[:SENSe]:MENU?",SA_Menu_CheckedQ},/* {Int}*/\
\
{"[:SENSe]:MENU:LINFobar:DISPlay",SA_Menu_LeftInfoBar}, /* {Int}*/\
{"[:SENSe]:MENU:LINFobar:DISPlay?",SA_Menu_LeftInfoBarQ}, /* {Int}*/\
\
{"[:SENSe]:SCREen:FULL",SA_Screen_Full}, /* {Int}*/\
{"[:SENSe]:SCREen:FULL?",SA_Screen_FullQ}, /* {Int}*/\
\
{"[:SENSe]:SCREen:LOCK",SA_Screen_Lock}, /* {Int}*/\
{"[:SENSe]:SCREen:LOCK?",SA_Screen_LockQ}, /* {Int}*/\
\
 {"[:SENSe]:SYSTem:PRESet",SA_State_Preset}, \

scpi_result_t SA_Menu_Checked(scpi_t * context);
scpi_result_t SA_Menu_CheckedQ(scpi_t * context);

scpi_result_t SA_Menu_LeftInfoBar(scpi_t * context);
scpi_result_t SA_Menu_LeftInfoBarQ(scpi_t * context);

scpi_result_t SA_Screen_Full(scpi_t * context);
scpi_result_t SA_Screen_FullQ(scpi_t * context);

scpi_result_t SA_Screen_Lock(scpi_t * context);
scpi_result_t SA_Screen_LockQ(scpi_t * context);

scpi_result_t SA_State_Preset(scpi_t * context);
#ifdef  __cplusplus
}
#endif

#endif // SA_SCPI_SETUP_H
