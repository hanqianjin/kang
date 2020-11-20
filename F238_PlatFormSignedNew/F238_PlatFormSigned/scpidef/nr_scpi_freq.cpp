#include "nr_scpi_freq.h"

#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;
extern scpi_result_t GetDoubleFreqVal(scpi_t *context, qreal *val);

scpi_result_t NR_FREQUENCY_Center_Freq(scpi_t *context)
{
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    qreal ival = 0;
    scpi_result_t iback = GetDoubleFreqVal(context,&ival);
    if(iback)
    {
        remoteinterface::getfgnrremotehandle()->setCenterFreq(ival);
    }
    return iback;
}

scpi_result_t NR_FREQUENCY_Step_Freq(scpi_t * context)
{
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    qreal ival = 0;
    scpi_result_t iback = GetDoubleFreqVal(context,&ival);
    if(iback)
    {
        remoteinterface::getfgnrremotehandle()->setFreqStep(ival);
    }
    return iback;
}

scpi_result_t NR_FREQUENCY_Band_Number(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setBand(value);
    return SCPI_RES_OK;
}

scpi_result_t NR_FREQUENCY_Arfc_Number(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setArfcn(value);
    return SCPI_RES_OK;
}

scpi_result_t NR_FREQUENCY_Gsc_Number(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setGscn(value);
    return SCPI_RES_OK;
}

scpi_result_t NR_FREQUENCY_Center_FreqQ(scpi_t * context)
{
    qreal centerFreq;

    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    centerFreq = remoteinterface::getfgnrremotehandle()->getCenterFreq();
    if(!SCPI_ResultDouble(context, centerFreq))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_FREQUENCY_Step_FreqQ(scpi_t * context)
{
    qreal stepFreq;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    stepFreq = remoteinterface::getfgnrremotehandle()->getFreqStep();
    if(!SCPI_ResultDouble(context, stepFreq))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_FREQUENCY_Band_NumberQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getBand();

    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_FREQUENCY_Arfc_NumberQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getArfcn();

    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_FREQUENCY_Gsc_NumberQ(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getGscn();

    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
