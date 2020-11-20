#include "nr_scpi_bw.h"

#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;

scpi_result_t NR_BANDWIDTH_IFOutPut(scpi_t * context)
{
    qint32 Value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setIFOutPut(Value);
    return SCPI_RES_OK;
}

scpi_result_t NR_BANDWIDTH_IFOutPutQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getIFOutPut();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
