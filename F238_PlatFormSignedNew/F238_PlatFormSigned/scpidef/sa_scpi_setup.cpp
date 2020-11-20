#include "sa_scpi_setup.h"

#include "remoteinterface.h"
#include "macrobus.h"
extern SYSTEM_STATUS g_systemStatus;

scpi_result_t SA_Menu_Checked(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->showMenu(value);
    return SCPI_RES_OK;
}

scpi_result_t SA_Menu_CheckedQ(scpi_t *context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->GetCurMenu();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_Menu_LeftInfoBar(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->SetLeftInfobarDisplay(value);
    return SCPI_RES_OK;
}

scpi_result_t SA_Menu_LeftInfoBarQ(scpi_t *context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->GetLeftInfobarDisplay();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_Screen_Full(scpi_t *context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->SetScreenFull(value);
    return SCPI_RES_OK;
}

scpi_result_t SA_Screen_FullQ(scpi_t *context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->GetScreenFull();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_Screen_Lock(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
      return SCPI_RES_OK;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getsaremotehandle()->SetScreenLock(value);
    return SCPI_RES_OK;
}
scpi_result_t SA_Screen_LockQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;

    value = remoteinterface::getsaremotehandle()->GetScreenLock();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t SA_State_Preset(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
      return SCPI_RES_ERR;
    remoteinterface::getsaremotehandle()->pcontrolInterface->PresetDefaultStates();
    return SCPI_RES_OK;
}
