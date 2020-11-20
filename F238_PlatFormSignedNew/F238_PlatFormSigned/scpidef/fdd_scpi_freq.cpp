#include "fdd_scpi_freq.h"
#include "lte_scpi_def.h"

#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;
extern scpi_result_t GetDoubleFreqVal(scpi_t *context, qreal *val);

scpi_result_t FDD_FREQUENCY_Center_Freq(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal ival = 0;
    scpi_result_t iback = GetDoubleFreqVal(context, &ival);
    if(iback)
    {
        remoteinterface::getfddremotehandle()->SCPI_ParamDouble(LTE_SCPI_FREQ_CENTER, ival);
    }
    return iback;
}

scpi_result_t FDD_FREQUENCY_Step_Freq(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal ival = 0;
    scpi_result_t iback = GetDoubleFreqVal(context, &ival);
    if(iback)
    {
        remoteinterface::getfddremotehandle()->SCPI_ParamDouble(LTE_SCPI_FREQ_STEP, ival);
    }
    return iback;
}

scpi_result_t FDD_FREQUENCY_Channel_Standard(scpi_t *context)
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
    remoteinterface::getfddremotehandle()->SCPI_ParamInt(LTE_SCPI_FREQ_CHANNEL_STD, value);
    return SCPI_RES_OK;
}

scpi_result_t FDD_FREQUENCY_Channel_Number(scpi_t *context)
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
    remoteinterface::getfddremotehandle()->SCPI_ParamInt(LTE_SCPI_FREQ_CHANNEL_NO, value);
    return SCPI_RES_OK;
}

scpi_result_t FDD_FREQUENCY_Channel_Step(scpi_t *context)
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
    remoteinterface::getfddremotehandle()->SCPI_ParamInt(LTE_SCPI_FREQ_CHANNEL_STEP, value);
    return SCPI_RES_OK;
}

scpi_result_t FDD_FREQUENCY_Center_FreqQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal centerFreq;
    centerFreq = remoteinterface::getfddremotehandle()->SCPI_ResultDouble(LTE_SCPI_FREQ_CENTER);
    if(!SCPI_ResultDouble(context, centerFreq))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t FDD_FREQUENCY_Step_FreqQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qreal stepFreq;
    stepFreq = remoteinterface::getfddremotehandle()->SCPI_ResultDouble(LTE_SCPI_FREQ_STEP);
    if(!SCPI_ResultDouble(context, stepFreq))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t FDD_FREQUENCY_Channel_StandardQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::getfddremotehandle()->SCPI_ResultInt(LTE_SCPI_FREQ_CHANNEL_STD);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t FDD_FREQUENCY_Channel_NumberQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::getfddremotehandle()->SCPI_ResultInt(LTE_SCPI_FREQ_CHANNEL_NO);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t FDD_FREQUENCY_Channel_StepQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::getfddremotehandle()->SCPI_ResultInt(LTE_SCPI_FREQ_CHANNEL_STEP);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
