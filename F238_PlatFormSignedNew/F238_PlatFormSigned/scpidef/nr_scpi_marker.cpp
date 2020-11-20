#include "nr_scpi_marker.h"

#include "remoteinterface.h"
#include "qdebug.h"
#include "macrobus.h"

extern SYSTEM_STATUS g_systemStatus;

scpi_result_t NR_MARKER_Select(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setCheckedMarker(value);
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER_SelectQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getCheckedMarker();
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }

    bool isOn = (value == 1);
    qint32 id = remoteinterface::getfgnrremotehandle()->getCheckedMarker();
    remoteinterface::getfgnrremotehandle()->setMarkerViewOn(id,isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    qint32 id = remoteinterface::getfgnrremotehandle()->getCheckedMarker();
    if(remoteinterface::getfgnrremotehandle()->isMarkerViewOn(id))
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

scpi_result_t NR_MARKER1_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }

    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setMarkerViewOn(1,isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER1_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isMarkerViewOn(1))
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

scpi_result_t NR_MARKER2_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }

    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setMarkerViewOn(2,isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER2_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isMarkerViewOn(2))
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

scpi_result_t NR_MARKER3_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }

    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setMarkerViewOn(3,isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER3_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isMarkerViewOn(3))
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

scpi_result_t NR_MARKER4_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }

    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setMarkerViewOn(4,isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER4_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isMarkerViewOn(4))
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

scpi_result_t NR_MARKER5_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }

    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setMarkerViewOn(5,isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER5_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isMarkerViewOn(5))
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

scpi_result_t NR_MARKER6_DisplayState(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }

    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setMarkerViewOn(6,isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER6_DisplayStateQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isMarkerViewOn(6))
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

scpi_result_t NR_MARKER_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    qint32 id = remoteinterface::getfgnrremotehandle()->getCheckedMarker();
    remoteinterface::getfgnrremotehandle()->setMarkerType(id,value);
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    qint32 id = remoteinterface::getfgnrremotehandle()->getCheckedMarker();
    value = remoteinterface::getfgnrremotehandle()->getMarkerType(id);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER1_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setMarkerType(1,value);
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER1_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getMarkerType(1);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER2_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setMarkerType(2,value);
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER2_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getMarkerType(2);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER3_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setMarkerType(3,value);
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER3_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getMarkerType(3);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER4_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setMarkerType(4,value);
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER4_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getMarkerType(4);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER5_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setMarkerType(5,value);
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER5_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getMarkerType(5);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER6_Type(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }
    remoteinterface::getfgnrremotehandle()->setMarkerType(6,value);
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER6_TypeQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    value = remoteinterface::getfgnrremotehandle()->getMarkerType(6);
    if(!SCPI_ResultInt(context, value))
    {
        return SCPI_RES_ERR;
    }
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER_NoiseMarker(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }

    bool isOn = (value == 1);
    qint32 id = remoteinterface::getfgnrremotehandle()->getCheckedMarker();
    remoteinterface::getfgnrremotehandle()->setMarkerNoiseOn(id,isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER_NoiseMarkerQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    qint32 id = remoteinterface::getfgnrremotehandle()->getCheckedMarker();
    if(remoteinterface::getfgnrremotehandle()->isMarkerNoiseOn(id))
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

scpi_result_t NR_MARKER1_NoiseMarker(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }

    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setMarkerNoiseOn(1,isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER1_NoiseMarkerQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isMarkerNoiseOn(1))
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

scpi_result_t NR_MARKER2_NoiseMarker(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }

    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setMarkerNoiseOn(2,isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER2_NoiseMarkerQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isMarkerNoiseOn(2))
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

scpi_result_t NR_MARKER3_NoiseMarker(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }

    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setMarkerNoiseOn(3,isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER3_NoiseMarkerQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isMarkerNoiseOn(3))
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

scpi_result_t NR_MARKER4_NoiseMarker(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }

    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setMarkerNoiseOn(4,isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER4_NoiseMarkerQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isMarkerNoiseOn(4))
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

scpi_result_t NR_MARKER5_NoiseMarker(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }

    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setMarkerNoiseOn(5,isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER5_NoiseMarkerQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isMarkerNoiseOn(5))
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

scpi_result_t NR_MARKER6_NoiseMarker(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }

    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setMarkerNoiseOn(6,isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER6_NoiseMarkerQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isMarkerNoiseOn(6))
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

scpi_result_t NR_MARKER_PeakMax(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    remoteinterface::getfgnrremotehandle()->setMaxPeak();
    return SCPI_RES_OK;
}
scpi_result_t NR_MARKER_PeakMin(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    remoteinterface::getfgnrremotehandle()->setMinPeak();
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER_PeakMaxNext(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    remoteinterface::getfgnrremotehandle()->setNextMaxPeak();
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER_PeakMaxLeft(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    remoteinterface::getfgnrremotehandle()->setLeftMaxPeak();
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER_PeakMaxRight(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    remoteinterface::getfgnrremotehandle()->setRightMaxPeak();
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER_PeakTrack(scpi_t * context)
{
    qint32 value;
    if (g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(!SCPI_ParamInt(context, &value, true))
    {
        return SCPI_RES_ERR;
    }

    bool isOn = (value == 1);
    remoteinterface::getfgnrremotehandle()->setPeakTrackOn(isOn);
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER_PeakTrackQ(scpi_t * context)
{
    qint32 value;
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;

    if(remoteinterface::getfgnrremotehandle()->isPeakTrackOn())
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

scpi_result_t NR_MARKER_AllOn(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    remoteinterface::getfgnrremotehandle()->setMarkerAllOn();
    return SCPI_RES_OK;
}

scpi_result_t NR_MARKER_ClearAll(scpi_t * context)
{
    Q_UNUSED(context)
    if(g_systemStatus.mode==Mode_local)
        return SCPI_RES_ERR;
    remoteinterface::getfgnrremotehandle()->setMarkerClearAll();
    return SCPI_RES_OK;
}
