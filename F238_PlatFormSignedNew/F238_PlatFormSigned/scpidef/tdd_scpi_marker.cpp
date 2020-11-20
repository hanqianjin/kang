#include "tdd_scpi_marker.h"
#include "lte_scpi_def.h"

#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;

scpi_result_t TDD_MARKER_Select(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_SELECT, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER_ViewStatus(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_DISPLAY, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER1_ViewStatus(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_DISPLAY1, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER2_ViewStatus(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_DISPLAY2, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER3_ViewStatus(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_DISPLAY3, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER4_ViewStatus(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_DISPLAY4, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER5_ViewStatus(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_DISPLAY5, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER6_ViewStatus(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_DISPLAY6, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER_Type(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_TYPE, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER1_Type(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_TYPE1, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER2_Type(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_TYPE2, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER3_Type(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_TYPE3, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER4_Type(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_TYPE4, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER5_Type(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_TYPE5, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER6_Type(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_TYPE6, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER_NoiseMarker(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_NOISE, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER1_NoiseMarker(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_NOISE1, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER2_NoiseMarker(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_NOISE2, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER3_NoiseMarker(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_NOISE3, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER4_NoiseMarker(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_NOISE4, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER5_NoiseMarker(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_NOISE5, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER6_NoiseMarker(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_NOISE6, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER_PeakTrack(scpi_t *context)
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
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_PTRACK, value);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER_AllOn(scpi_t *context)
{
    Q_UNUSED(context);
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_ALLON);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER_ClearAll(scpi_t *context)
{
    Q_UNUSED(context);
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_CLEARALL);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER_PeakMax(scpi_t *context)
{
    Q_UNUSED(context);
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_PMAX);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER_PeakMin(scpi_t *context)
{
    Q_UNUSED(context);
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_PMIN);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER_PeakMaxNext(scpi_t *context)
{
    Q_UNUSED(context);
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_PNEXT);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER_PeakMaxLeft(scpi_t *context)
{
    Q_UNUSED(context);
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_PLEFT);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER_PeakMaxRight(scpi_t *context)
{
    Q_UNUSED(context);
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::gettddremotehandle()->SCPI_ParamInt(LTE_SCPI_MARKER_PRIGHT);
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER_SelectQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MARKER_SELECT);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER_ViewStatusQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MARKER_DISPLAY);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER1_ViewStatusQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MARKER_DISPLAY1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER2_ViewStatusQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MARKER_DISPLAY2);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER3_ViewStatusQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MARKER_DISPLAY3);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER4_ViewStatusQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MARKER_DISPLAY4);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER5_ViewStatusQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MARKER_DISPLAY5);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER6_ViewStatusQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MARKER_DISPLAY6);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER_TypeQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MARKER_TYPE);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER1_TypeQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MARKER_TYPE1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER2_TypeQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MARKER_TYPE2);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER3_TypeQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MARKER_TYPE3);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER4_TypeQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MARKER_TYPE4);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER5_TypeQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MARKER_TYPE5);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER6_TypeQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MARKER_TYPE6);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER_NoiseMarkerQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MARKER_NOISE);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER1_NoiseMarkerQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MARKER_NOISE1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER2_NoiseMarkerQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MARKER_NOISE2);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER3_NoiseMarkerQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MARKER_NOISE3);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER4_NoiseMarkerQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MARKER_NOISE4);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER5_NoiseMarkerQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MARKER_NOISE5);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER6_NoiseMarkerQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MARKER_NOISE6);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t TDD_MARKER_PeakTrackQ(scpi_t *context)
{
    if(g_systemStatus.mode == Mode_local)
    {
        return SCPI_RES_ERR;
    }
    qint32 value;
    value = remoteinterface::gettddremotehandle()->SCPI_ResultInt(LTE_SCPI_MARKER_PTRACK);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}
