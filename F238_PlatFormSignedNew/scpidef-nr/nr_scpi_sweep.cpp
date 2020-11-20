#include "nr_scpi_sweep.h"

#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;

scpi_result_t NR_SWEEP_Type(scpi_t *context)
{
    qint32 Value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;
    if(!SCPI_ParamInt(context, &Value, true))
    {
        return SCPI_RES_ERR;
    }
    bool isOn = (Value == 1);
    remoteinterface::getfgnrremotehandle()->setSweepContinuous(isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_SWEEP_Once(scpi_t *context)
{
    Q_UNUSED(context)
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getfgnrremotehandle()->setSweepOnce();
    return SCPI_RES_OK;
}

scpi_result_t NR_SWEEP_TypeQ(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->getSweepContinuous())
    {
        value = 1;
    }
    else
    {
        value = 0;
    }

    if(!SCPI_ResultInt(context, value))
      {
        return SCPI_RES_ERR;
      }
    return SCPI_RES_OK;
}
