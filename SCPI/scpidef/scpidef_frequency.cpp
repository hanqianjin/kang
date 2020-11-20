#include "scpidef_frequency.h"

extern scpi_t scpi_context;
extern SYSTEM_STATUS g_systemStatus;


scpi_result_t FREQUENCY_Center_Freq(scpi_t *context)
{
    qint32 value;

    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_OK;

    if (!SCPI_ParamInt(context, &value, true))
        return SCPI_RES_ERR;

    return SCPI_RES_OK;//(scpi_result_t)(sa_interface);
}

scpi_result_t FREQUENCY_Start_Freq(scpi_t * context)
{
    qint32 value;

    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_OK;

    if (!SCPI_ParamInt(context, &value, true))
        return SCPI_RES_ERR;

    return SCPI_RES_OK;//(scpi_result_t)(sa_interface);
}

scpi_result_t FREQUENCY_Stop_Freq(scpi_t * context)
{
    qint32 value;

    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_OK;

    if (!SCPI_ParamInt(context, &value, true))
        return SCPI_RES_ERR;

    return SCPI_RES_OK;//(scpi_result_t)(sa_interface);
}

scpi_result_t FREQUENCY_Step_Freq(scpi_t * context)
{
    qint32 value;

    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_OK;

    if (!SCPI_ParamInt(context, &value, true))
        return SCPI_RES_ERR;

    return SCPI_RES_OK;//(scpi_result_t)(sa_interface);
}

scpi_result_t FREQUENCY_Step_CenterFreq(scpi_t * context)
{
    qint32 value;

    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_OK;

    if (!SCPI_ParamInt(context, &value, true))
        return SCPI_RES_ERR;

    return SCPI_RES_OK;//(scpi_result_t)(sa_interface);
}

scpi_result_t FREQUENCY_Step_CenterFreq_Auto(scpi_t * context)
{
    scpi_bool_t value;

    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_OK;

    if (!SCPI_ParamBool(context, &value, true))
        return SCPI_RES_ERR;

    return SCPI_RES_OK;//(scpi_result_t)ScpiDisplay_Bar::instance()->setConnectOnOff(value);
}

scpi_result_t FREQUENCY_CenterFreq_Step(scpi_t * context)
{
    const char *param;
    size_t strcLen;
    int32_t value;

    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_OK;

    if (!SCPI_ParamString(context, &param, &strcLen, true))
        return SCPI_RES_ERR;

    if(matchPattern("UP",2,param,strcLen))
        value = 0;
    else if(matchPattern("DOWn",4,param,strcLen))
        value = 1;

    return SCPI_RES_OK;//(scpi_result_t)ScpiDisplay_Bar::instance()->setConnectOnOff(value);
}

scpi_result_t FREQUENCY_Freq_Span(scpi_t * context)
{
    qint32 value;

    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_OK;

    if (!SCPI_ParamInt(context, &value, true))
        return SCPI_RES_ERR;

    return SCPI_RES_OK;//(scpi_result_t)(sa_interface);
}

scpi_result_t FREQUENCY_Freq_FullSpan(scpi_t * context)
{
    return SCPI_RES_OK;//(scpi_result_t)(setFullSpan);
}

scpi_result_t FREQUENCY_Freq_ZeroSpan(scpi_t * context)
{
    return SCPI_RES_OK;//(scpi_result_t)(setZeroSpan);
}

scpi_result_t FREQUENCY_Freq_PreviousSpan(scpi_t * context)
{
    return SCPI_RES_OK;//(scpi_result_t)(setPreviouseSpan);
}

scpi_result_t FREQUENCY_Center_FreqQ(scpi_t * context)
{
    quint32 centerFreq;

    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_OK;

    if(1)//ScpiDisplay_Bar::instance()->getCenterFreq(&centerFreq))
    {
        SCPI_ResultInt(context, (int32_t)centerFreq);
    }
    else
        return SCPI_RES_ERR;

    return SCPI_RES_OK;
}

scpi_result_t FREQUENCY_Start_FreqQ(scpi_t * context)
{
    quint32 startFreq;

    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_OK;

    if(1)//ScpiDisplay_Bar::instance()->getStartFreq(&startFreq))
    {
        SCPI_ResultInt(context, (int32_t)startFreq);
    }
    else
        return SCPI_RES_ERR;

    return SCPI_RES_OK;
}

scpi_result_t FREQUENCY_Stop_FreqQ(scpi_t * context)
{
    quint32 stopFreq;

    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_OK;

    if(1)//ScpiDisplay_Bar::instance()->getStopFreq(&stopFreq))
    {
        SCPI_ResultInt(context, (int32_t)stopFreq);
    }
    else
        return SCPI_RES_ERR;

    return SCPI_RES_OK;
}

scpi_result_t FREQUENCY_Step_FreqQ(scpi_t * context)
{
    quint32 stepFreq;

    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_OK;

    if(1)//ScpiDisplay_Bar::instance()->getStepFreq(&stepFreq))
    {
        SCPI_ResultInt(context, (int32_t)stepFreq);
    }
    else
        return SCPI_RES_ERR;

    return SCPI_RES_OK;
}

scpi_result_t FREQUENCY_Step_CenterFreqQ(scpi_t * context)
{
    quint32 stepCenterFreq;

    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_OK;

    if(1)//ScpiDisplay_Bar::instance()->getStepCenterFreq(&stepCenterFreq))
    {
        SCPI_ResultInt(context, (int32_t)stepCenterFreq);
    }
    else
        return SCPI_RES_ERR;

    return SCPI_RES_OK;
}
scpi_result_t FREQUENCY_Step_CenterFreq_AutoQ(scpi_t * context)
{
    scpi_bool_t stepCenterFreqAuto;

    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_OK;

    if(1)//ScpiDisplay_Bar::instance()->getStepCenterFreqAuto(&stepCenterFreqAuto))
    {
        SCPI_ResultBool(context, stepCenterFreqAuto);
    }
    else
        return SCPI_RES_ERR;

    return SCPI_RES_OK;
}

scpi_result_t FREQUENCY_Freq_SpanQ(scpi_t * context)
{
    quint32 spanFreq;

    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_OK;

    if(1)//ScpiDisplay_Bar::instance()->getSpanFreq(&spanFreq))
    {
        SCPI_ResultInt(context, (int32_t)spanFreq);
    }
    else
        return SCPI_RES_ERR;

    return SCPI_RES_OK;
}
