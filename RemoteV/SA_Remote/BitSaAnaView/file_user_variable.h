#ifndef FILE_USER_VARIABLE_H
#define FILE_USER_VARIABLE_H   ///保证代码只被嵌入一次,注释掉后，gcc就会报重定义错误;"#pragma once" is profile related


#include "define.h"
#include <QObject>

typedef struct
{
    //qint32 gDemodulationType;
    qreal gChannelBandwidth;
    qreal gChannelSpacing;
    qreal gOccupiedBW;
    qreal XdB;

    __SPUR_EM__ gSpurEMPara[SPUR_EM_DATE_MAX];
    qint32 gSpurEMViewStatus[SA_SPUREM_RANGE_CNT];
    qint32 gSpurEMAveType;
    qint32 gSpurEMReportType;
    qint32 gMeasureStatus;
    qint32 gSpecEMDisplay;
    qint32 gSpecEMRefType;
    __SPEC_EM__ gSpecEMData[SA_SPECEM_FREQ_CNT];
    qint32 gSpecEMViewStatus[SA_SPECEM_FREQ_CNT];

    __SPUR_POINT__ gSpurEMSpur[SA_SPUREM_RANGE_CNT*SA_SPUREM_SPUR_CNT];
    qint32 gSpurEMSpurCnt[SA_SPUREM_RANGE_CNT];
    qint32 gSpurEMTotalSpurCnt;
    qint32 gSpurEMCurRangeIndex;
    qint32 gSpurEMCurDrawRangeIndex;
    qint32 gSpurEMCurSpurIndex;
}_CONFIG_MEASURE_;
typedef struct
{
    /*quint64 gStartFreq;
    quint64 gStopFreq;
    quint64 gCenterFreq;*/
    quint64 gStepFreq;
    qint64  gfreqOffset;

    quint32 gSpanMode;
    quint64 gCFFreq;
    quint64 gSpanFreq;
    quint64 gLastSpanFreq;
    qint32  gZeroSpanAction;
}_CONFIG_FREQ_SPAN_;
typedef struct
{
    qreal gVbwtoRbw;
    //quint32 gAutoVbwtoRbw;
    //quint32 grbwChangedbyFreq;

    quint32 gAutoRbw;
    quint32 gAutoVbw;
    quint32 gRbw;
    quint32 gVbw;
    quint32 gIFMode;
}_CONFIG_BW_;
typedef struct
{
    qreal    gRefLevel;
    qreal    gRefOffset;
    qreal    gScaleDiv;
    qint32   gAmptdUnit;
    quint32  gAtten;
    quint32  gPreamp;
    qreal    gAttenValue;
    quint32  gAutoAttenTrack;
}_CONFIG_AMPLITUDE_;
typedef struct
{
    qint32    gViewAction[NUM_TRACE];
    qint32    gTraceView[NUM_TRACE];

    qint32    gTraceSelect;
    qint32    gTraceType[NUM_TRACE];
    qint32    gTraceAverage[NUM_TRACE];
    qint32    gAverageCount[NUM_TRACE];
    //qreal     gTraceMeasureVal[NUM_TRACE][NUM_SWEEP_POINT];
    quint32   gDetectorMode;
    quint32   gTmpDetectorMode;
}_CONFIG_TRACE_;
typedef struct
{
    qreal     gTraceMeasureVal[NUM_TRACE][NUM_SWEEP_POINT];
}_CONFIG_TRACE_DATA_;
typedef struct
{
    quint32 gSweepType;

    qint32  gsweepAuto;
    quint32 gAutoSweepTime;
    qreal   gSweepTime;
    //quint32 gTriggerMode;
    qreal   gZeroSpanTime;
#if 0
    quint32 gSweepSpeed;
#endif
    quint32 gSweepmode;

    quint32 gAutoDotSweepTime;
    qreal   gDotSweepTime;
    quint32 gFixDotSweepTime;
}_CONFIG_SWEEP_;
#if 1
typedef struct
{
    qint32 gDrCtrlSource;
    qint32 gLvlEdgSelect;
    qint32 gLvlEdgMode;
    qint32 gDrCtrlSweepMode;
    qint32 gPrdTrgSynchroSrc;
    qint32 gDrCtrlSwitch;
    qreal  gEdgTrigDely;
    qreal  gEdgTrigDoorWdth;
    qint32 gEdgTrigPrvntStatus;
    qreal  gEdgTrigPrvntTimes;
    qreal  gRFBurstTrigLevel;
    qreal  gPrdTrgPeriod;
    qreal  gPrdTrgSrcDelay;
    qint32 gPrdTrigPrvntStatus;
    qreal  gPrdTrigPrvntTimes;
    quint32 gDrCtrlRbw;
    qint32 gGateSweepSpanChange;
    qint32 gGateViewStatus;
    qreal gGateViewStartTime;
} _CONFIG_GATE_SWEEP_;
#endif
typedef struct
{
    quint32 gTriggerMode;
    qreal   gTriggerPerTimer; //only Periodic Timer
    qreal   gTriggerLevel[TRIGGER_SOURCE_CNT];//except Periodic Timer
    qint32  gTriggerSlope[TRIGGER_SOURCE_CNT];//except Periodic Timer
    qint32  gTriggerDelayStatus[TRIGGER_SOURCE_CNT]; // SA_ON SA_OFF
    qreal   gTriggerDelayValue[TRIGGER_SOURCE_CNT];
    qreal   gCalData;
}_CONFIG_TRIGGER_;
typedef struct
{
    qint32  gMarkerSelect;
    qint32  gMarkerView[MARKER_TOTAL_CNT];
    qint32  gMarkerType[MARKER_TOTAL_CNT];
    quint64 gMarkerRefFreq[MARKER_TOTAL_CNT];
    qint32  gMarkerRefPos[MARKER_TOTAL_CNT];
    quint64 gMarkerDeltaFreq[MARKER_TOTAL_CNT];
    qint32  gMarkerDeltaPos[MARKER_TOTAL_CNT];
    qint32  gMarkerDisplay;
    qint32  gMarkerNoise[MARKER_TOTAL_CNT];
    quint32 gMarkerFreqCount[MARKER_TOTAL_CNT];
    quint32 gPeakTrack;
    qreal gMarkerTmpRefAmpt[MARKER_TOTAL_CNT];
    qreal gMarkerMarkerTmpRefPos[MARKER_TOTAL_CNT];

    qreal gMarkerRefTime[MARKER_TOTAL_CNT];
    qreal gMarkerDeltaTime[MARKER_TOTAL_CNT];
}_CONFIG_MARKER_;
typedef struct
{
    qreal   gMarkerRefAmpt[MARKER_TOTAL_CNT];
    qreal   gMarkerDeltaAmpt[MARKER_TOTAL_CNT];
    qreal   gMarkerTmpRefAmpt[MARKER_TOTAL_CNT];
    qreal   gMarkerMarkerTmpRefPos[MARKER_TOTAL_CNT];
    qreal   gMarkerNoiseValue[MARKER_TOTAL_CNT];
}_CONFIG_MARKER_DATA_;
typedef struct
{
}_CONFIG_PEAK_;
typedef struct
{
    /*qint32    gLatestLimitTestResult[LIMIT_SELECTSUM];
    qint32    gLatestLimitEdgeResult[LIMIT_SELECTSUM];*/
    qint32    gLimitTest;
    qint32    gLimitLine[LIMIT_SELECTSUM];
    qint32    gLimitEdge[LIMIT_SELECTSUM];
    qreal     gLimitEdgeValue[LIMIT_SELECTSUM];
    qint32    gLimitSelect;

    qint32    gLatestLimitType[LIMIT_SELECTSUM];
    qint32    gTotalDot[LIMIT_SELECTSUM];
    /*qint32    gXIndex[LIMIT_SELECTSUM][LIMIT_TOTALDOT];
    qint32    gXAxis[LIMIT_SELECTSUM][LIMIT_TOTALDOT];
    qint32    gYAxis[LIMIT_SELECTSUM][LIMIT_TOTALDOT];
    qint32    gEdgeYAxis[LIMIT_SELECTSUM][LIMIT_TOTALDOT];*/
    qreal     gFreq[LIMIT_SELECTSUM][LIMIT_TOTALDOT];
    qreal     gAmplitude[LIMIT_SELECTSUM][LIMIT_TOTALDOT];
    /*qint32    gLatestLimitDrawPoint[LIMIT_SELECTSUM][NUM_SWEEP_POINT];
    qint32    gLatestLimitEdgeDrawPoint[LIMIT_SELECTSUM][NUM_SWEEP_POINT];
    qint32    gLatestLimitUpperDrawPoint[NUM_SWEEP_POINT];
    qint32    gLatestLimitLowerDrawPoint[NUM_SWEEP_POINT];
    qint32    gLatestLimitUpperEdgeDrawPoint[NUM_SWEEP_POINT];
    qint32    gLatestLimitLowerEdgeDrawPoint[NUM_SWEEP_POINT];*/

}_CONFIG_LIMIT_;
typedef struct
{
    qreal gridHorStep;//quint32 ==> qreal  //Tony 0610
    qreal gridVerStep;//quint32 ==> qreal
    qint32  markerOnCount;
    qint32  limitLineOnCount;
    qint32  peakPos;
}_CONFIG_GUI_DRAW_SET_;
/*typedef struct
{
    qint32  gMenu;
    quint64 gPowersensorFreq;
    qreal   gPowersensorExtOffset;
}_CONFIG_POWERSENSOR_;
typedef struct
{
}_CONFIG_PRESET_;
typedef struct
{
}_CONFIG_SYSTEM_;*/
typedef struct
{
    qint32 SecondaryAction;
}_CONFIG_EXT_;
/*typedef struct
{
    quint32 checkswitch;
    qint32 checkinsert;
    qreal firstper;
    qreal secper;
    qreal spanperstep;
}_CONFIG_SHAREMEMORY_;*/

typedef struct
{
    quint32              gCurrentWorkState;

    _CONFIG_MEASURE_     gConfig_Measure;
    _CONFIG_FREQ_SPAN_   gConfig_FreqSpan;
    _CONFIG_BW_          gConfig_BW;
    _CONFIG_AMPLITUDE_   gConfig_Amplitude;
    _CONFIG_TRACE_       gConfig_Trace;
    _CONFIG_SWEEP_       gConfig_Sweep;
#if 1
    _CONFIG_GATE_SWEEP_  gConfig_Gate_Sweep;
#endif
    _CONFIG_TRIGGER_     gConfig_Trigger;
    _CONFIG_MARKER_      gConfig_Marker;
    _CONFIG_PEAK_        gConfig_peak;
    _CONFIG_LIMIT_       gConfig_Limit;

    //_CONFIG_POWERSENSOR_ gConfig_PowerSensor;
    //_CONFIG_PRESET_      gConfig_Preset;
    //_CONFIG_SYSTEM_      gConfig_System;
    _CONFIG_GUI_DRAW_SET_ gConfig_GuiDrawSet;
    _CONFIG_EXT_         gConfig_Ext;

} _FILE_SAVE_LOAD_VARIABLE_;

typedef struct
{
    bool bSpanModeParamNull;
    bool bChnlPowerModeParamNull;
    bool bOccupiedModeParamNull;
    bool bACPModeParamNull;
    bool bMultiACPModeParamNull;
    bool bSpectrumEmissionMaskModeParamNull;
    bool bSpuriousEmissionMaskModeParamNull;
    bool bFieldStrengthModeParamNull;
    bool bDemodulationModeParamNull;
}_MEASURE_PARA_STATUS_;

typedef struct
{
    quint64                   gCenterFreq;
    quint32                   mSaveLoad_CurrentMode;
    quint32                   mSaveLoad_MeasureMode;
    bool                      FullStatus;
    bool                      leftHideChecked;
    _FILE_SAVE_LOAD_VARIABLE_ pSpanModeParam;
    _FILE_SAVE_LOAD_VARIABLE_ pChnlPowerModeParam;
    _FILE_SAVE_LOAD_VARIABLE_ pOccupiedModeParam;
    _FILE_SAVE_LOAD_VARIABLE_ pACPModeParam;
    _FILE_SAVE_LOAD_VARIABLE_ pMultiACPModeParam;
    _FILE_SAVE_LOAD_VARIABLE_ pSpectrumEmissionMaskModeParam;
    _FILE_SAVE_LOAD_VARIABLE_ pSpuriousEmissionMaskModeParam;
    _FILE_SAVE_LOAD_VARIABLE_ pFieldStrengthModeParam;
    _FILE_SAVE_LOAD_VARIABLE_ pDemodulationModeParam;
    _MEASURE_PARA_STATUS_     pMeasurParaStatus;
}_ALLMODE_FILE_SAVE_LOAD_;

typedef struct
{
    qint32 startMode;
    qint32 startPreset;
}_START_STATUS_FLAG_;

typedef struct
{
    qint32    gLimitSelect;
    qint32    gLimitTest;
    qint32    gLimitLine[LIMIT_SELECTSUM];
    qint32    gLimitEdge[LIMIT_SELECTSUM];
    qreal     gLimitEdgeValue[LIMIT_SELECTSUM];
    qint32    gLatestLimitType[LIMIT_SELECTSUM];
    qint32    gTotalDot[LIMIT_SELECTSUM];
    qint32    gXIndex[LIMIT_SELECTSUM][LIMIT_TOTALDOT];

    qint32    gEdgeYAxis[LIMIT_SELECTSUM][LIMIT_TOTALDOT];
    qreal     gFreq[LIMIT_SELECTSUM][LIMIT_TOTALDOT];
    qreal     gAmplitude[LIMIT_SELECTSUM][LIMIT_TOTALDOT];
}_CONFIG_LIMIT_STATE_;

typedef struct       
{
     qint32    gLatestLimitTestResult[LIMIT_SELECTSUM];
     qint32    gLatestLimitEdgeResult[LIMIT_SELECTSUM];

     qint32    gXAxis[LIMIT_SELECTSUM][LIMIT_TOTALDOT];
     qint32    gYAxis[LIMIT_SELECTSUM][LIMIT_TOTALDOT];

     qint32    gLatestLimitDrawPoint[LIMIT_SELECTSUM][NUM_SWEEP_POINT];
     qint32    gLatestLimitEdgeDrawPoint[LIMIT_SELECTSUM][NUM_SWEEP_POINT];
     qint32    gLatestLimitUpperDrawPoint[NUM_SWEEP_POINT];
     qint32    gLatestLimitLowerDrawPoint[NUM_SWEEP_POINT];
     qint32    gLatestLimitUpperEdgeDrawPoint[NUM_SWEEP_POINT];
     qint32    gLatestLimitLowerEdgeDrawPoint[NUM_SWEEP_POINT];

}_CONFIG_LIMIT_DATA_;

typedef struct
{
    quint32 uSweepCompleteFlag;
    quint32 uAllSweepCompleteFlag;
    quint32 uIFMode;
#if 0
    quint32 uMsCompleteFlag;
#endif
}_CONFIG_SHR_;
typedef struct
{
    quint32              gCurrentWorkState;

    _CONFIG_MEASURE_     gConfig_Measure;
    _CONFIG_FREQ_SPAN_   gConfig_FreqSpan;
    _CONFIG_BW_          gConfig_BW;
    _CONFIG_AMPLITUDE_   gConfig_Amplitude;
    _CONFIG_TRACE_       gConfig_Trace;
    _CONFIG_SWEEP_       gConfig_Sweep;
#if 1
    _CONFIG_GATE_SWEEP_  gConfig_Gate_Sweep;
#endif
    _CONFIG_TRIGGER_     gConfig_Trigger;
    _CONFIG_MARKER_      gConfig_Marker;
    _CONFIG_PEAK_        gConfig_peak;
    //_CONFIG_LIMIT_       gConfig_Limit;
    _CONFIG_LIMIT_STATE_ gConfig_Limit;
    //_CONFIG_POWERSENSOR_ gConfig_PowerSensor;
    //_CONFIG_PRESET_      gConfig_Preset;
    //_CONFIG_SYSTEM_      gConfig_System;
    _CONFIG_GUI_DRAW_SET_ gConfig_GuiDrawSet;
    _CONFIG_EXT_         gConfig_Ext;

}_CONFIG_STATE_;

typedef struct
{
    quint64        gCenterFreq;
    quint32        mSaveLoad_CurrentMode;
    _CONFIG_SHR_   gConfig_ShareMem;
    _CONFIG_STATE_ pSpanModeParam;
    _CONFIG_STATE_ pChnlPowerModeParam;
    _CONFIG_STATE_ pOccupiedModeParam;
    _CONFIG_STATE_ pACPModeParam;
    _CONFIG_STATE_ pMultiACPModeParam;
    _CONFIG_STATE_ pSpectrumEmissionMaskModeParam;
    _CONFIG_STATE_ pSpuriousEmissionMaskModeParam;
    _CONFIG_STATE_ pFieldStrengthModeParam;
    _CONFIG_STATE_ pDemodulationModeParam;
}_ALLMODE_STATE_;


typedef struct
{
    quint32              gCurrentWorkState;

    _CONFIG_MEASURE_     gConfig_Measure;
    _CONFIG_FREQ_SPAN_   gConfig_FreqSpan;
    _CONFIG_BW_          gConfig_BW;
    _CONFIG_AMPLITUDE_   gConfig_Amplitude;
    _CONFIG_TRACE_       gConfig_Trace;
    _CONFIG_SWEEP_       gConfig_Sweep;
#if 1
    _CONFIG_GATE_SWEEP_  gConfig_Gate_Sweep;
#endif
    _CONFIG_TRIGGER_     gConfig_Trigger;
    _CONFIG_MARKER_      gConfig_Marker;
    _CONFIG_PEAK_        gConfig_peak;
    _CONFIG_LIMIT_STATE_ gConfig_Limit;
    //_CONFIG_POWERSENSOR_ gConfig_PowerSensor;
    //_CONFIG_PRESET_      gConfig_Preset;
    //_CONFIG_SYSTEM_      gConfig_System;
    _CONFIG_GUI_DRAW_SET_ gConfig_GuiDrawSet;
    _CONFIG_EXT_         gConfig_Ext;

    _CONFIG_TRACE_DATA_  gConfig_Trace_Data;
    _CONFIG_MARKER_DATA_ gConfig_Marker_Data;
    _CONFIG_LIMIT_DATA_  gConfig_Limit_Data;
}_CONFIG_STATE_MSDATA_;


typedef struct
{
    quint64              gCenterFreq;
    quint32              mSaveLoad_CurrentMode;
    _CONFIG_SHR_         gConfig_ShareMem;

    _CONFIG_STATE_MSDATA_ pSpanModeParam;
    _CONFIG_STATE_MSDATA_ pChnlPowerModeParam;
    _CONFIG_STATE_MSDATA_ pOccupiedModeParam;
    _CONFIG_STATE_MSDATA_ pACPModeParam;
    _CONFIG_STATE_MSDATA_ pMultiACPModeParam;
    _CONFIG_STATE_MSDATA_ pSpectrumEmissionMaskModeParam;
    _CONFIG_STATE_MSDATA_ pSpuriousEmissionMaskModeParam;
    _CONFIG_STATE_MSDATA_ pFieldStrengthModeParam;
    _CONFIG_STATE_MSDATA_ pDemodulationModeParam;
}_ALL_STATE_MSDATA_;

#endif // FILE_USER_VARIABLE_H
