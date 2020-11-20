#ifndef AUTOPRODUCTCOMMAND_H
#define AUTOPRODUCTCOMMAND_H

#include <QByteArray>
#include <QDebug>

#define NI_PROTO 0

extern bool  m_bDataSplicingFlg; //数据拼接标志
extern QByteArray m_tmpData;   //临时数据
extern QByteArray m_errData;   //错误数据

extern int recMessgFlag;

QByteArray charToByteArray(const char *sendArray);
QByteArray cmdDataSend(int indexFlg,QByteArray sendData);
QString cmdDataProcess(QByteArray rcvData);

enum{
    ESE_REQUEST,
    ESR_REQUEST,
    IDN_REQUEST,
    OPC_REQUEST,
    SRE_REQUEST,
    STB_REQUEST,
    TST_REQUEST,
    RFTMP_REQUEST,
    BOARDTMP_REQUEST,
    FPGATMP_REQUEST,
    BATTERYTMP_REQUEST,

    CENTERFREQ_REQUEST,
    STARTFREQ_REQUEST,
    STOPFREQ_REQUEST,
    STEPFREQ_REQUEST,
    OFFSETFREQ_REQUEST,
    SPANFREQ_REQUEST,

    REFLEVEL_REQUEST,
    SCALE_REQUEST,
    ATTENAUTO_REQUEST,
    ATTEN_REQUEST,
    PREAMP_REQUEST,
    REFOFFSET_REQUEST,
    DIVISION_REQUEST,

    SWEEPTIMEAUTO_REQUEST,
    SWEEPTIME_REQUEST,
    COUNTINUOUS_REQUEST,

    BANDWIDTH_RBWAUTO_REQUEST,
    BWIDTH_RBWAUTO_REQUEST,
    BANDWIDTH_RBW_REQUEST,
    BWIDTH_RBW_REQUEST,
    BANDWIDTH_VBWAUTO_REQUEST,
    BWIDTH_VBWAUTO_REQUEST,
    BANDWIDTH_VBW_REQUEST,
    BWIDTH_VBW_REQUEST,
    BANDWIDTH_RATIO_REQUEST,
    BWIDTH_RATIO_REQUEST,
    IFOUTPUT_REQUEST,

    TRIGGER_SOURCE_REQUEST,
    EXTERNAL_LEVEL_REQUEST,
    VEDIO_LEVEL_REQUEST,
    RFBURST_LEVEL_REQUEST,
    EXTERNAL_SLOPE_REQUEST,
    VEDIO_SLOPE_REQUEST,
    RFBURST_SLOPE_REQUEST,
    EXTERNAL_DELAYSTATE_REQUEST,
    VEDIO_DELAYSTATE_REQUEST,
    PERIODIC_DELAYSTATE_REQUEST,
    RFBURST_DELAYSTATE_REQUEST,
    RFBURST_DELAY_REQUEST,
    EXTERNAL_DELAY_REQUEST,
    VEDIO_DELAY_REQUEST,
    PERIODIC_DELAY_REQUEST,
    PERIODIC_REQUEST,

    TRACE1_DISPLAYSTATE_REQUEST,
    TRACE2_DISPLAYSTATE_REQUEST,
    TRACE3_DISPLAYSTATE_REQUEST,
    TRACE4_DISPLAYSTATE_REQUEST,
    TRACE5_DISPLAYSTATE_REQUEST,
    TRACE6_DISPLAYSTATE_REQUEST,
    TRACE1_TYPE_REQUEST,
    TRACE2_TYPE_REQUEST,
    TRACE3_TYPE_REQUEST,
    TRACE4_TYPE_REQUEST,
    TRACE5_TYPE_REQUEST,
    TRACE6_TYPE_REQUEST,
    TRACE1_AVECOUNT_REQUEST,
    TRACE2_AVECOUNT_REQUEST,
    TRACE3_AVECOUNT_REQUEST,
    TRACE4_AVECOUNT_REQUEST,
    TRACE5_AVECOUNT_REQUEST,
    TRACE6_AVECOUNT_REQUEST,
    TRACE_DETECTOR_REQUEST,
    TRACEDATA_REQUEST,
    TRACEDATA_RAWDATA_REQUEST,
    TRACEDATA_DRAWDATA_REQUEST,
    MARKER_SELECT_REQUEST,
    MARKER1_DISPLAYSTATE_REQUEST,
    MARKER2_DISPLAYSTATE_REQUEST,
    MARKER3_DISPLAYSTATE_REQUEST,
    MARKER4_DISPLAYSTATE_REQUEST,
    MARKER5_DISPLAYSTATE_REQUEST,
    MARKER6_DISPLAYSTATE_REQUEST,
    MARKER1_TYPE_REQUEST,
    MARKER2_TYPE_REQUEST,
    MARKER3_TYPE_REQUEST,
    MARKER4_TYPE_REQUEST,
    MARKER5_TYPE_REQUEST,
    MARKER6_TYPE_REQUEST,
    MARKER1_X_REQUEST,
    MARKER2_X_REQUEST,
    MARKER3_X_REQUEST,
    MARKER4_X_REQUEST,
    MARKER5_X_REQUEST,
    MARKER6_X_REQUEST,
    MARKER1_FREQCOUNTSTATE_REQUEST,
    MARKER2_FREQCOUNTSTATE_REQUEST,
    MARKER3_FREQCOUNTSTATE_REQUEST,
    MARKER4_FREQCOUNTSTATE_REQUEST,
    MARKER5_FREQCOUNTSTATE_REQUEST,
    MARKER6_FREQCOUNTSTATE_REQUEST,
    MARKER1_NOISESTATE_REQUEST,
    MARKER2_NOISESTATE_REQUEST,
    MARKER3_NOISESTATE_REQUEST,
    MARKER4_NOISESTATE_REQUEST,
    MARKER5_NOISESTATE_REQUEST,
    MARKER6_NOISESTATE_REQUEST,
    MARKER_PEAKTRACESTATE_REQUEST,
    PEAKPOINT_FREQ_REQUEST,
    PEAKPOINT_AMP_REQUEST,

};


#endif // AUTOPRODUCTCOMMAND_H