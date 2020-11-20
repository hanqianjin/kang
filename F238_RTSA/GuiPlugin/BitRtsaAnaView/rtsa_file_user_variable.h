#ifndef RTSA_FILE_USER_VARIABLE_H
#define RTSA_FILE_USER_VARIABLE_H

//#include "define.h"
#include "rtsa_define.h"
//typedef struct
//{
//    //qint32 gMeasurement;
//    qint32 gDemodulationType;
//    qreal  gChannelBandwidth;
//    qreal  gChannelSpacing;
//}_CONFIG_MEASURE_;
enum
{
    STATE_DEFAULT_FILE = 0,
    STATE_LAST_FILE,
    STATE_USER_FILE,
};
#define RTSA_DEFAULT_COND    "rtsa_default.cond"
#define RTSA_LAST_COND       "rtsa_last.cond"
#define RTSA_USER_COND       "rtsa_user.cond"
#define RTSA_PRE_STATE_FILE  "rtsa_state.pres"
typedef struct
{
    qreal       gStartFreq;
    qreal       gStopFreq;
    qreal       gCenterFreq;
    qreal       gSpanFreq;
    qreal       gStepFreq;
    qreal       gOffsetFreq;
    qint32      channelStd;
    qint32      channelSelID;
    qint32      channelNumber;
    qint32      channelStep;
    qint32      channelType;

}_RTSA_CONFIG_FREQ_;

typedef struct
{
    qreal   refLevel;
    qint32  attenAuto;
    qint32  attenVal;
    qreal   scaleDiv[RTSA_BITVIEWNUM];
    qreal   refOffset[RTSA_BITVIEWNUM];
    qint32  units[RTSA_BITVIEWNUM];
    qint32  preAmpStatus;

} _RTSA_CONFIG_AMPT_;

typedef struct
{
    qint32  sweepType;
    qint32  autoAcqtime;
    qreal   acqTimeVal;
    qint32  autoPersistence;
    qreal   persistenceVal;
    qint32  highDensity;
    qint32  lowDensity;
    qint32  curveNum;

} _RTSA_CONFIG_SWEEP_;

typedef struct
{
    qint32  autoRbw;
    qreal   rbw;
    qint32  rbwIndex;
    qint32  fftFilter;

}_RTSA_CONFIG_BW_;

typedef struct
{
    qint32  triggerType;
    qint32  triggerVideoSlope;
    qint32  triggerVideoDelayStatus;
    qint32  triggerExternSlope;
    qint32  triggerExternDelayStatus;
    qint32  triggerPeriodDelayStatus;
    qint32  triggerRFSlope;
    qint32  triggerRFDelayStatus;
    qreal   triggerExternLevel;
    qreal   triggerExternDelay;
    qreal   triggerVideoDelay;
    qreal   triggerVideoLevel;
    qreal   triggerPeriodTime;
    qreal   triggerPeriodDelay;
    qreal   triggerRFLevel;
    qreal   triggerRFDelay;
    quint32 triggerVideoHoldOff;
    quint32 triggerRFBurstHoldOff;
    quint32 triggerExternHoldOff;
    quint32 triggerFMTHoldOff;
    qint32  triggerSlope;
    qint32  maskType;
    qint32  triggerCriteria;
    qint32  fmtnumber;
    qreal   fmtFreq[RTSA_NUM_SWEEP_POINT];
    qreal   fmtAmpt[RTSA_NUM_SWEEP_POINT];

}_RTSA_CONFIG_TRIGGER_;

typedef struct
{
    qint32 traceView;
    qint32 traceType;
    qint32 averageOn;
    qint32 averageCount;

}_RTSA_CONGIG_TRACE_;

typedef struct
{
    qint32              curTraceID[RTSA_BITVIEWNUM];
    qint32              detectorType;
    _RTSA_CONGIG_TRACE_ Rtsa_Config_Trace[RTSA_BITVIEWNUM][RTSA_NUM_TRACE];

}_RTSA_CONFIG_TRACE_ALL_;

typedef struct
{
    qint32  markerView;
    qint32  markerType;
    qint32  markerNoiseOn;
    qreal   gMarkerRefFreq;
    qreal   gMarkerDeltaFreq;
    qreal   gMarkerRefAmpt;
    qint32   gMarkerNormalPosY;

}_RTSA_CONFIG_MARKER_;

typedef struct
{
    qint32  markerPeakTraceOn;
    qint32  curmarkerID;
    _RTSA_CONFIG_MARKER_ gRtsa_Config_marker[RTSA_MARKER_TOTAL_CNT];

}_RTSA_CONFIG_MARKER_ALL_;

typedef struct
{
    qint32  limitID;
    qint32  limitTest;
    qint32  limitOn[RTSA_MARKER_TOTAL_CNT];
    qint32  limitEdgeOn[RTSA_MARKER_TOTAL_CNT];
    qint32  limitType[RTSA_MARKER_TOTAL_CNT];
    qint32  limitCurEditIndex[RTSA_MARKER_TOTAL_CNT];
    qint32  limitEditNum[RTSA_MARKER_TOTAL_CNT];
    qreal   limitEdgeVal[RTSA_MARKER_TOTAL_CNT];
    qreal   limitFreq[RTSA_NUM_SWEEP_POINT];
    qreal   limitAmpt[RTSA_NUM_SWEEP_POINT];

}_RTSA_CONFIG_LIMIT_;

typedef struct
{
    qint32 displayMode;
    qint32 curWindowIndex;
    qint32 bitviewStatus[RTSA_BITVIEWNUM];

}_RTSA_CONFIG_DISPLAY_;

typedef struct
{
    qint32 startMode;
    qint32 startFileType;
}_RTSA_CONFIG_PRESET_;

typedef struct
{
    //_CONFIG_MEASURE_     gConfig_Measure;
    _RTSA_CONFIG_FREQ_        gConfig_FreqSpan;
    _RTSA_CONFIG_BW_          gConfig_BW;
    _RTSA_CONFIG_AMPT_        gConfig_Amplitude;
    _RTSA_CONFIG_TRACE_ALL_   gConfig_Trace;
    _RTSA_CONFIG_SWEEP_       gConfig_Sweep;
    _RTSA_CONFIG_MARKER_ALL_  gConfig_Marker[RTSA_BITVIEWNUM];
    _RTSA_CONFIG_LIMIT_       gConfig_Limit[RTSA_BITVIEWNUM];
    _RTSA_CONFIG_PRESET_      gConfig_Preset;
    _RTSA_CONFIG_TRIGGER_     gConfig_Trigger;
    _RTSA_CONFIG_DISPLAY_     gConfig_Display;

} _RTSA_FILE_SAVE_LOAD_VARIABLE_;

#endif // FILE_USER_VARIABLE_H
