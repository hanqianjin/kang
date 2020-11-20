#include "fdd_scpi_sweep.h"
#include "lte_scpi_def.h"

#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;

scpi_result_t FDD_SWEEP_Type(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfddremotehandle()->SCPI_ParamInt(LTE_SCPI_SWEEP_CONTINUOUS, value);
    return SCPI_RES_OK;
}

scpi_result_t FDD_SWEEP_Once(scpi_t *context)
{
    Q_UNUSED(context);
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfddremotehandle()->SCPI_ParamInt(LTE_SCPI_SWEEP_ONCE);
    return SCPI_RES_OK;
}

scpi_result_t FDD_SWEEP_TypeQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::getfddremotehandle()->SCPI_ResultInt(LTE_SCPI_SWEEP_CONTINUOUS);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
