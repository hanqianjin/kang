#include "rtsa_scpi_display.h"


#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;

scpi_result_t RTSA_DISPLAY_View(scpi_t *context)
{
    qint32 isAuto;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &isAuto, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getrtsaremotehandle()->InterfaceObj->setDisplay(isAuto);
    return SCPI_RES_OK;
}


scpi_result_t RTSA_DISPLAY_ViewQ(scpi_t *context)
{
    qint32 isAuto;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    isAuto = remoteinterface::getrtsaremotehandle()->InterfaceObj->getDisplay();
    if(!SCPI_ResultInt(context, isAuto))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
