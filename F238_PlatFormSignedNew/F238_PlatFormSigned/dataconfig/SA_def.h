#pragma once
#include "define.h"
#include "ajson/ajson.hpp"

typedef struct SASperPoint
{
    int rangeIndex = 0;
    int xPtIndex = 0;
    double freq = 0;
    double value = 0;
    double limit = 0;
    int testValue = 0;
} __SPUR_POINT__DEF;
AJSON(SASperPoint,
    rangeIndex,
    xPtIndex,
    freq,
    value,
    limit,
    testValue)

typedef struct SASpecEm
{
    double start = 0;
    double  stop = 0;
    double  rbw = 0;
    double  vbw = 0;
    double startAbsRef = 0;
    double stopAbsRef = 0;
    double startRelRef = 0;
    double stopRelRef = 0;
} __SPEC_EM__DEF;
AJSON(SASpecEm,
    start,
    stop,
    rbw,
    vbw,
    startAbsRef,
    stopAbsRef,
    startRelRef,
    stopRelRef)
typedef struct SASuperEm
{
    int index = 0;
    double  startFreq = 0.0;
    double  stopFreq = 0;
    double  RBW = 0;
    double  VBW = 0;
#if !SPUREMODIFY
    double  SweepTime = 0;
#endif
    double  startLimit = 0;
    double  stopLimit = 0;
#if !SPUREMODIFY
    double  peakDefi = 0;
    double  peakThreshold = 0;
    double  Atten = 0;
#endif
} __SPUR_EM__DEF;
AJSON(SASuperEm,
    index,
    startFreq,
    stopFreq,
    RBW,
    VBW,
    startLimit,
    stopLimit
)

typedef struct SACfgMeasure
{
    qint32 gSpecEMMaskType = 0;  // 规格电磁屏蔽类型。[0 -- 1.8 GHz  1 -- 5GNR Category A]
    qreal  gSpecEMRefChBw = 0;
    qreal  gSpecEMBsPower = 0; //31.01--38.00 dBm
    quint32 gSpecEMRefRbw = 0;

    qint64 gChannelBandwidth = 0;/*信道带宽*/
    qint64 gChannelSpacing = 0;/*通道间距*/
    qreal gOccupiedBW = 0;/*占用带宽*/
    qreal XdB = 0;/*Xdb*/

    qint64 gHighestCHFreq = 0;/*最高频率*/
    qint64 gLowestCHFreq = 0;/*最低频率*/
    qint64 gMultiACPSpacing = 0;/*多ACPjian'ju间距*/
    qint64 gMainIntegBW = 0;/*主积分带宽*/
    qint64 gADJIntegBW = 0;/*调整积分带宽*/
    qint64 gALTIntegBW = 0;/*ALT积分带宽*/

    __SPUR_EM__DEF gSpurEMPara[SPUR_EM_DATE_MAX];//todo
    qint32 gSpurEMViewStatus[SA_SPUREM_RANGE_CNT];
    qint32 gSpurEMAveType = 0;
    qint32 gSpurEMReportType = 0;
    qint32 gMeasureStatus = 0;/*测量状态*/
    qint32 gSpecEMDisplay = 0;
    qint32 gSpecEMRefType = 0;
    __SPEC_EM__DEF gSpecEMData[SA_SPECEM_FREQ_CNT];
    qint32 gSpecEMViewStatus[SA_SPECEM_FREQ_CNT];

    __SPUR_POINT__DEF gSpurEMSpur[SA_SPUREM_RANGE_CNT*SA_SPUREM_SPUR_CNT];//todo
    qint32 gSpurEMSpurCnt[SA_SPUREM_RANGE_CNT];
    qint32 gSpurEMTotalSpurCnt = 0;
    qint32 gSpurEMCurRangeIndex = 0;
    qint32 gSpurEMCurDrawRangeIndex = 0;
    qint32 gSpurEMCurSpurIndex = 0;
    SACfgMeasure()
    {
        for (int i = 0; i < SA_SPUREM_RANGE_CNT; ++i)
        {
            gSpurEMViewStatus[i] = 0;
            gSpurEMSpurCnt[i] = 0;
        }

        for (int i = 0; i < SA_SPECEM_FREQ_CNT; ++i)
        {
            gSpecEMViewStatus[i] = 0;
        }
    }
}_CONFIG_MEASURE_DEF;
AJSON(SACfgMeasure,
    gSpecEMMaskType,
    gSpecEMRefChBw,
    gSpecEMBsPower,
    gSpecEMRefRbw,
    gChannelBandwidth,
    gChannelSpacing,
    gOccupiedBW,
    XdB,
    gHighestCHFreq,
    gLowestCHFreq,
    gMultiACPSpacing,
    gMainIntegBW,
    gADJIntegBW,
    gALTIntegBW,
    gSpurEMPara,
    gSpurEMViewStatus,
    gSpurEMAveType,
    gSpurEMReportType,
    gMeasureStatus,
    gSpecEMDisplay,
    gSpecEMRefType,
    gSpecEMData,
    gSpecEMViewStatus,
    gSpurEMSpur,
    gSpurEMSpurCnt,
    gSpurEMTotalSpurCnt,
    gSpurEMCurRangeIndex,
    gSpurEMCurDrawRangeIndex,
    gSpurEMCurSpurIndex
    )

//FREQ-SETTING
typedef struct SACfgFreqSpan
{
    quint64 gStepFreq = 0;      /*旋钮网格刻度步进*/
    qint64  gfreqOffset = 0;    /*频率偏移*/

    quint32 gSpanMode = 0;    /*扫宽类型*/
    quint64 gCFFreq = 0;    /*频率步进*/
    quint64 gSpanFreq = 0;    /*扫宽频率*/
    quint64 gLastSpanFreq = 0;    /*上一次扫宽频率*/
    qint32  gZeroSpanAction = 0;    /*零扫宽*/
}_CONFIG_FREQ_SPAN_DEF;
AJSON(SACfgFreqSpan,
    gStepFreq,
    gfreqOffset,
    gSpanMode,
    gCFFreq,
    gSpanFreq,
    gLastSpanFreq,
    gZeroSpanAction)

//BW-SETTING
typedef struct SACfgBw
{
    qreal gVbwtoRbw = 0;    /*显示带宽转分析带宽*/

    quint32 gAutoRbw = 0;   /*分析带宽标志*/
    quint32 gAutoVbw = 0;   /*显示带宽标志*/
    quint32 gRbw = 0;       /*分析带宽值*/
    quint32 gVbw = 0;       /* 显示带宽值  */
    quint32 gIFMode = 0;    /*中频输出*/
}_CONFIG_BW_DEF;
AJSON(SACfgBw,
    gVbwtoRbw,
    gAutoRbw,
    gAutoVbw,
    gRbw,
    gVbw,
    gIFMode)

//AMPLITUDE-SETTING
typedef struct SACfgAmplitude
{
    qreal    gRefLevel = 0;/*参考电平值*/
    qreal    gRefOffset = 0;/*参考电平偏移*/
    qreal    gScaleDiv = 0;/*刻度/分度*/
    qint32   gAmptdUnit = 0;/*单位*/
    quint32  gAtten = 0;    /*衰减标志*/
    quint32  gPreamp = 0;   /*前置放大器标志*/
    qreal    gAttenValue = 0;/*衰减值*/
    quint32  gAutoAttenTrack = 0;/*自动跟踪*/
}_CONFIG_AMPLITUDE_DEF;
AJSON(SACfgAmplitude,
    gRefLevel,
    gRefOffset,
    gScaleDiv,
    gAmptdUnit,
    gAtten,
    gPreamp,
    gAttenValue,
    gAutoAttenTrack)

//TRACE-SETTING
typedef struct SACfgTrace
{
    qint32    gViewAction[NUM_TRACE];/*轨迹线打开标志*/
    qint32    gTraceView[NUM_TRACE];/*轨迹线视图标志*/

    qint32    gTraceSelect = 0; /*轨迹线标志*/
    qint32    gTraceType[NUM_TRACE];/*轨迹线类型*/
    qint32    gTraceAverage[NUM_TRACE];/*轨迹线平均标志*/
    qint32    gAverageCount[NUM_TRACE];/*轨迹线平均次数*/
    quint32   gDetectorMode = 0;/*检波方式*/
    quint32   gTmpDetectorMode = 0;/*临时检波方式*/
    SACfgTrace()
    {
        for (int i = 0; i < NUM_TRACE; ++i)
        {
            gViewAction[i] = 0;
            gTraceView[i] = 0;
            gTraceType[i] = 0;
            gTraceAverage[i] = 0;
            gAverageCount[i] = 0;
        }
    }
}_CONFIG_TRACE_DEF;
AJSON(SACfgTrace,
    gViewAction,
    gTraceView,
    gTraceSelect,
    gTraceType,
    gTraceAverage,
    gAverageCount,
    gDetectorMode,
    gTmpDetectorMode)


//TRACEDATA-SETTING
typedef struct  ConfigTraceData
{
    qreal     gTraceMeasureVal[NUM_TRACE][NUM_SWEEP_POINT];/*轨迹线数据*/
    ConfigTraceData()
    {
        for (int i = 0; i < NUM_TRACE; ++i)
        {
            for (int j = 0; j < NUM_SWEEP_POINT; ++j)
            {
                gTraceMeasureVal[i][j] = 0;
            }
        }
    }
}_CONFIG_TRACE_DATA_DEF;
    AJSON(ConfigTraceData,
        gTraceMeasureVal)

//SWEEP-SETTING
typedef struct SAConfigSweep
{
    quint32 gSweepType = 0;/*扫描类型*/

    qint32  gsweepAuto = 0;/*自动扫描标志*/
    quint32 gAutoSweepTime = 0;/*自动扫描时间*/
    qreal   gSweepTime = 0;/*扫描时间*/

    qreal   gZeroSpanTime = 0;/*0扫宽扫描时间*/

    quint32 gSweepmode = 0;/*扫描模式*/

    quint32 gAutoDotSweepTime = 0;/*自动点扫描时间*/
    qreal   gDotSweepTime = 0;/*点扫描时间*/
    quint32 gFixDotSweepTime = 0;/*固定点扫描时间*/
}_CONFIG_SWEEP_DEF;
AJSON(SAConfigSweep,
    gSweepType,
    gsweepAuto,
    gAutoSweepTime,
    gSweepTime,
    gZeroSpanTime,
    gSweepmode,
    gAutoDotSweepTime,
    gDotSweepTime,
    gFixDotSweepTime)

//GATESWEEP-SETTING
typedef struct SACfgGateSweep
{
    qint32 gDrCtrlSource = 0;   /*门控制*/
    qint32 gLvlEdgMode = 0;  /*左边缘模式*/
    qint32 gDrCtrlSwitch = 0;/*门切换*/
    qreal  gEdgTrigDely = 0;/*边缘触发延时*/
    qreal  gEdgTrigDoorWdth = 0;/*边缘触发门宽*/
    qint32 gEdgTrigPrvntStatus = 0;/*边缘触发阻止状态*/
    qreal  gEdgTrigPrvntTimes = 0;/*边缘触发阻止时间*/
    qreal  gRFBurstTrigLevel = 0;/*射频触发电平*/
    qreal  gPrdTrgPeriod = 0;/*周期触发周期*/
    quint32 gDrCtrlRbw = 0;/*门控制RBW*/
    qint32 gGateViewStatus = 0;/*门视图状态*/
} _CONFIG_GATE_SWEEP_DEF;
AJSON(SACfgGateSweep,
    gDrCtrlSource,
    gLvlEdgMode,
    gDrCtrlSwitch,
    gEdgTrigDely,
    gEdgTrigDoorWdth,
    gEdgTrigPrvntStatus,
    gEdgTrigPrvntTimes,
    gRFBurstTrigLevel,
    gPrdTrgPeriod,
    gDrCtrlRbw,
    gGateViewStatus)

//TRIGGER-SETTING
typedef struct SACfgTrigger
{
    quint32 gTriggerMode = 0;/*触发类型*/
    qreal   gTriggerPerTimer = 0; /*触发周期计时器*/
    qreal   gTriggerLevel[TRIGGER_SOURCE_CNT];/*触发电平*/
    qint32  gTriggerSlope[TRIGGER_SOURCE_CNT];/*触发极性*/
    qint32  gTriggerDelayStatus[TRIGGER_SOURCE_CNT]; /*触发延迟开关*/
    qreal   gTriggerDelayValue[TRIGGER_SOURCE_CNT];/*触发延时*/
    qreal   gCalData = 0;/*触发校准数据*/
    SACfgTrigger()
    {
        for (int i = 0; i < TRIGGER_SOURCE_CNT; ++i)
        {
            gTriggerLevel[i] = 0;
            gTriggerSlope[i] = 0;
            gTriggerDelayStatus[i] = 0;
            gTriggerDelayValue[i] = 0;
        }
    }
}_CONFIG_TRIGGER_DEF;
AJSON(SACfgTrigger,
    gTriggerMode,
    gTriggerPerTimer,
    gTriggerLevel,
    gTriggerSlope,
    gTriggerSlope,
    gTriggerDelayStatus,
    gTriggerDelayValue,
    gCalData)

//MARKER-SETTING
typedef struct SACfgMarker
{
    qint32  gMarkerSelect = 0;/*Mark选择索引*/
    qint32  gMarkerView[MARKER_TOTAL_CNT];/*Mark打开标志*/
    qint32  gMarkerType[MARKER_TOTAL_CNT];/*Mark类型*/
    quint64 gMarkerRefFreq[MARKER_TOTAL_CNT];/*Mark参考频率*/
    qint32  gMarkerRefPos[MARKER_TOTAL_CNT];/*Mark参考点*/
    quint64 gMarkerDeltaFreq[MARKER_TOTAL_CNT];/*Mark差值频率*/
    qint32  gMarkerDeltaPos[MARKER_TOTAL_CNT];/*Mark差值点*/
    qint32  gMarkerDisplay = 0;/*Mark显示*/
    qint32  gMarkerNoise[MARKER_TOTAL_CNT];/*mark噪声开关*/
    quint32 gMarkerFreqCount = 0;/*频率计数器开关*/
    quint32 gPeakTrack = 0;/*峰值追踪开关*/
    qreal gMarkerTmpRefAmpt[MARKER_TOTAL_CNT];/*Mark临时参考幅度*/
    qreal gMarkerMarkerTmpRefPos[MARKER_TOTAL_CNT];/*Mark临时参考点*/

    qreal gMarkerRefTime[MARKER_TOTAL_CNT];/*Mark参考时间*/
    qreal gMarkerDeltaTime[MARKER_TOTAL_CNT];/*Mark差值时间*/
    SACfgMarker()
    {
        for (int i = 0; i < MARKER_TOTAL_CNT; i++)
        {
            gMarkerView[i] = 0;
            gMarkerType[i] = 0;
            gMarkerRefFreq[i] = 0;
            gMarkerRefPos[i] = 0;
            gMarkerDeltaFreq[i] = 0;
            gMarkerDeltaPos[i] = 0;
            gMarkerNoise[i] = 0;
            gMarkerTmpRefAmpt[i] = 0;
            gMarkerMarkerTmpRefPos[i] = 0;
            gMarkerRefTime[i] = 0;
            gMarkerDeltaTime[i] = 0;
        }
    }
}_CONFIG_MARKER_DEF;
AJSON(SACfgMarker,
    gMarkerSelect,
    gMarkerView,
    gMarkerType,
    gMarkerRefFreq,
    gMarkerRefPos,
    gMarkerDeltaFreq,
    gMarkerDeltaPos,
    gMarkerDisplay,
    gMarkerNoise,
    gMarkerFreqCount,
    gPeakTrack,
    gMarkerTmpRefAmpt,
    gMarkerMarkerTmpRefPos,
    gMarkerRefTime,
    gMarkerDeltaTime)

//MARKERDATA-SETTING
typedef struct
{
    qreal   gMarkerRefAmpt[MARKER_TOTAL_CNT];   /*Mark参考幅度*/
    qreal   gMarkerDeltaAmpt[MARKER_TOTAL_CNT]; /*Mark差值幅度*/
    qreal   gMarkerTmpRefAmpt[MARKER_TOTAL_CNT]; /*Mark临时参考幅度*/
    qreal   gMarkerMarkerTmpRefPos[MARKER_TOTAL_CNT];/*Mark临时参考点*/
    qreal   gMarkerNoiseValue[MARKER_TOTAL_CNT];/*Mark噪声值*/
}_CONFIG_MARKER_DATA_DEF;

typedef struct
{
}_CONFIG_PEAK_DEF;

//LIMITE-SETTING
typedef struct SACfgLimit
{
    qint32    gLimitTest;/*极限线测试*/
    qint32    gLimitLine[LIMIT_SELECTSUM];/*极限线开关*/
    qint32    gLimitEdge[LIMIT_SELECTSUM];/*极限线边缘开关*/
    qreal     gLimitEdgeValue[LIMIT_SELECTSUM];/*极限线边缘值*/
    qint32    gLimitSelect;/*极限线选择索引*/

    qint32    gLatestLimitType[LIMIT_SELECTSUM];/*极限线类型*/
    qint32    gTotalDot[LIMIT_SELECTSUM];/*极限线点*/

    qreal     gFreq[LIMIT_SELECTSUM][LIMIT_TOTALDOT];/*极限线频率值*/
    qreal     gAmplitude[LIMIT_SELECTSUM][LIMIT_TOTALDOT];/*极限线幅度值*/

    qreal gUpperLimitAmpt;/*极限线上限*/
    qreal gLowerLimitAmpt;/*极限线下限*/
    qint32 gUpperLimitStatus;/*极限线上限状态*/
    qint32 gLowerLimitStatus;/*极限线下限状态*/
   // qreal gAtlLimitdBc;
    qint32 gAtlLimitStatus;/**/

}_CONFIG_LIMIT_DEF;

typedef struct SCCfgExt
{
    qint32 SecondaryAction;/*第二次作用*/
}_CONFIG_EXT_DEF;

typedef struct SACfgGuiDrawSet
{
#if GUIDRAW_CONFIG//todo 是否定义此宏
    qreal gridHorStep;//quint32 ==> qreal  //Tony 0610
    qreal gridVerStep;//quint32 ==> qreal
    qint32  markerOnCount;
    qint32  limitLineOnCount;
    qint32  peakPos;
#endif
}_CONFIG_GUI_DRAW_SET_DEF;

typedef struct
{
    quint32              gCurrentWorkState;/*当前工作状态*/

    _CONFIG_MEASURE_DEF     gConfig_Measure;/*测量菜单*/
    _CONFIG_SWEEP_DEF       gConfig_Sweep; /*扫描菜单*/

    _CONFIG_GATE_SWEEP_DEF  gConfig_Gate_Sweep;/*门扫描菜单*/

    _CONFIG_TRIGGER_DEF     gConfig_Trigger;/*触发菜单*/
    _CONFIG_MARKER_DEF      gConfig_Marker;/*标记菜单*/
    _CONFIG_PEAK_DEF        gConfig_peak;/*峰值菜单*/
    _CONFIG_LIMIT_DEF       gConfig_Limit;/*极限线菜单*/

    _CONFIG_GUI_DRAW_SET_DEF gConfig_GuiDrawSet;/*图形用户界面绘图集*/
    _CONFIG_EXT_DEF         gConfig_Ext;/*提取*/

} _FILE_SAVE_LOAD_VARIABLE_DEF;

typedef struct
{
    bool bSpanModeParamNull;/*跨度模式参数标志*/
    bool bChnlPowerModeParamNull;/*通道功率模式参数标志*/
    bool bOccupiedModeParamNull;/*占用模式参数标志*/
    bool bACPModeParamNull;/*ACP模式参数标志*/
    bool bMultiACPModeParamNull;/*多ACP模式参数标志*/
    bool bSpectrumEmissionMaskModeParamNull;/*光谱发射掩模模式参数标志*/
    bool bSpuriousEmissionMaskModeParamNull;/*杂散发射掩模模式参数标志*/
    bool bFieldStrengthModeParamNull;/*场强模式参数标志*/
    bool bDemodulationModeParamNull;/*解调模式参数标志*/
}_MEASURE_PARA_STATUS_DEF;

typedef struct
{
    _CONFIG_FREQ_SPAN_DEF   gConfig_FreqSpan;/*频率扫宽配置*/
    _CONFIG_BW_DEF          gConfig_BW; /*带宽配置*/
    _CONFIG_AMPLITUDE_DEF   gConfig_Amplitude;  /*幅度配置*/
    _CONFIG_TRACE_DEF       gConfig_Trace; /*迹线配置*/

    quint64                   gCenterFreq;/*中心频率*/
    quint32                   mSaveLoad_CurrentMode;/*当前状态*/
    quint32                   mSaveLoad_MeasureMode;/*测试状态*/
    bool                      FullStatus;/*完全状态*/
    bool                      leftHideChecked;/*左侧隐藏标志*/
    _FILE_SAVE_LOAD_VARIABLE_DEF pSpanModeParam;/*跨度模式参数*/
    _FILE_SAVE_LOAD_VARIABLE_DEF pChnlPowerModeParam;/*通道功率模式参数*/
    _FILE_SAVE_LOAD_VARIABLE_DEF pOccupiedModeParam;/*占用模式参数*/
    _FILE_SAVE_LOAD_VARIABLE_DEF pACPModeParam;/*ACP模式参数*/
    _FILE_SAVE_LOAD_VARIABLE_DEF pMultiACPModeParam;/*多ACP模式参数*/
    _FILE_SAVE_LOAD_VARIABLE_DEF pSpectrumEmissionMaskModeParam;/*光谱发射掩模模式参数*/
    _FILE_SAVE_LOAD_VARIABLE_DEF pSpuriousEmissionMaskModeParam;/*杂散发射掩模模式参数*/
    _FILE_SAVE_LOAD_VARIABLE_DEF pFieldStrengthModeParam;/*场强模式参数*/
    _FILE_SAVE_LOAD_VARIABLE_DEF pDemodulationModeParam;/*解调模式参数*/
    _MEASURE_PARA_STATUS_DEF     pMeasurParaStatus;/*测量参数状态*/
}_ALLMODE_FILE_SAVE_LOAD_DEF;

typedef struct
{
    qint32 startMode;/*开始模式*/
    qint32 startPreset;/*开始预设*/
}_START_STATUS_FLAG_DEF;

typedef struct SACfgLimitState
{
    qint32    gLimitSelect = 0;/*极限线选择索引*/
    qint32    gLimitTest = 0;/*极限线测试*/
    qint32    gLimitLine[LIMIT_SELECTSUM];/*极限线开关*/
    qint32    gLimitEdge[LIMIT_SELECTSUM];/*极限线边缘开关*/
    qreal     gLimitEdgeValue[LIMIT_SELECTSUM];/*极限线边缘值*/
    qint32    gLatestLimitType[LIMIT_SELECTSUM];/*极限线类型*/
    qint32    gTotalDot[LIMIT_SELECTSUM];/*极限线点*/
    qint32    gXIndex[LIMIT_SELECTSUM][LIMIT_TOTALDOT];/*极限线X索引*/

    qint32    gEdgeYAxis[LIMIT_SELECTSUM][LIMIT_TOTALDOT];/*极限线边缘Y轴*/
    qreal     gFreq[LIMIT_SELECTSUM][LIMIT_TOTALDOT];/*极限线频率值*/
    qreal     gAmplitude[LIMIT_SELECTSUM][LIMIT_TOTALDOT];/*极限线幅度值*/

    qreal gUpperLimitAmpt = 0;/*极限线上限*/
    qreal gLowerLimitAmpt = 0;/*极限线下限*/
    qint32 gUpperLimitStatus = 0;/*极限线上限状态*/
    qint32 gLowerLimitStatus = 0;/*极限线下限状态*/
//    qreal gAtlLimitdBc;
//    qint32 gAtlLimitStatus;
    SACfgLimitState()
    {
        for (int i = 0; i < LIMIT_SELECTSUM; ++i)
        {
            gLimitLine[i] = 0;
            gLimitEdge[i] = 0;
            gLimitEdgeValue[i] = 0;
            gLatestLimitType[i] = 0;
            gTotalDot[i] = 0;
            for (int j = 0; j < LIMIT_TOTALDOT; ++j)
            {
                gXIndex[i][j] = 0;
                gEdgeYAxis[i][j] = 0;
                gFreq[i][j] = 0;
                gAmplitude[i][j] = 0;
            }
        }
    }

}_CONFIG_LIMIT_STATE_DEF;
AJSON(SACfgLimitState,
    gLimitSelect,
    gLimitTest,
    gLimitLine,
    gLimitEdge,
    gLimitEdgeValue,
    gLatestLimitType,
    gTotalDot,
    gXIndex,
    gEdgeYAxis,
    gFreq,
    gAmplitude,
    gUpperLimitAmpt,
    gLowerLimitAmpt,
    gUpperLimitStatus,
    gLowerLimitStatus)

typedef struct
{
     qint32    gLatestLimitTestResult[LIMIT_SELECTSUM];/*最新极限线测试结果*/
     qint32    gLatestLimitEdgeResult[LIMIT_SELECTSUM];/*最新极限线边缘结果*/

     qint32    gXAxis[LIMIT_SELECTSUM][LIMIT_TOTALDOT];/*X轴值*/
     qint32    gYAxis[LIMIT_SELECTSUM][LIMIT_TOTALDOT];/*Y轴值*/

     qint32    gLatestLimitDrawPoint[LIMIT_SELECTSUM][NUM_SWEEP_POINT];/*最新极限线绘制点*/
     qint32    gLatestLimitEdgeDrawPoint[LIMIT_SELECTSUM][NUM_SWEEP_POINT];/*最新极限线边缘绘制点*/
     qint32    gLatestLimitUpperDrawPoint[NUM_SWEEP_POINT];/*最新极限线上限绘制点*/
     qint32    gLatestLimitLowerDrawPoint[NUM_SWEEP_POINT];/*最新极限线下限绘制点*/
     qint32    gLatestLimitUpperEdgeDrawPoint[NUM_SWEEP_POINT];/*最新极限线上限边缘绘制点*/
     qint32    gLatestLimitLowerEdgeDrawPoint[NUM_SWEEP_POINT];/*最新极限线下限边缘绘制点*/

}_CONFIG_LIMIT_DATA_DEF;

typedef struct ConfigShrDef
{
    quint32 uSweepCompleteFlag;/*扫描完成标志*/
    quint32 uAllSweepCompleteFlag;/*全扫描完成标记*/
    quint32 uIFMode;/*中频模式*/
}_CONFIG_SHR_DEF;

typedef struct
{
    quint32              gCurrentWorkState;/*当前工作状态*/

    _CONFIG_MEASURE_DEF     gConfig_Measure; /*测量菜单*/

    _CONFIG_SWEEP_DEF       gConfig_Sweep; /*扫描菜单*/

    _CONFIG_GATE_SWEEP_DEF  gConfig_Gate_Sweep; /*门扫描菜单*/

    _CONFIG_TRIGGER_DEF     gConfig_Trigger;/*触发菜单*/
    _CONFIG_MARKER_DEF      gConfig_Marker;/*标记菜单*/
    _CONFIG_PEAK_DEF        gConfig_peak;/*峰值菜单*/

    _CONFIG_LIMIT_STATE_DEF gConfig_Limit;/*极限线菜单*/

    _CONFIG_GUI_DRAW_SET_DEF gConfig_GuiDrawSet;/*图形用户界面绘图集*/
    _CONFIG_EXT_DEF         gConfig_Ext;/*提取*/

}_CONFIG_STATE_DEF;

typedef struct
{
    _CONFIG_FREQ_SPAN_DEF   gConfig_FreqSpan;/*频率扫宽配置*/
    _CONFIG_BW_DEF          gConfig_BW;/*带宽配置*/
    _CONFIG_AMPLITUDE_DEF   gConfig_Amplitude;/*幅度配置*/
    _CONFIG_TRACE_DEF       gConfig_Trace;/*迹线配置*/

    quint64        gCenterFreq;/*中心频率*/
    quint32        mSaveLoad_CurrentMode;/*当前状态*/
    _CONFIG_SHR_DEF   gConfig_ShareMem;/*共享内存配置*/
    _CONFIG_STATE_DEF pSpanModeParam;/*跨度模式参数*/
    _CONFIG_STATE_DEF pChnlPowerModeParam;/*通道功率模式参数*/
    _CONFIG_STATE_DEF pOccupiedModeParam;/*占用模式参数*/
    _CONFIG_STATE_DEF pACPModeParam;/*ACP模式参数*/
    _CONFIG_STATE_DEF pMultiACPModeParam;/*多ACP模式参数*/
    _CONFIG_STATE_DEF pSpectrumEmissionMaskModeParam;/*光谱发射掩模模式参数*/
    _CONFIG_STATE_DEF pSpuriousEmissionMaskModeParam;/*杂散发射掩模模式参数*/
    _CONFIG_STATE_DEF pFieldStrengthModeParam;/*场强模式参数*/
    _CONFIG_STATE_DEF pDemodulationModeParam;/*解调模式参数*/
}_ALLMODE_STATE_DEF;


typedef struct SACfgStateMsdata
{
    quint32              gCurrentWorkState = 0;/*当前工作状态*/

    _CONFIG_MEASURE_DEF     gConfig_Measure; /*测量菜单*/

    _CONFIG_SWEEP_DEF       gConfig_Sweep;    /*扫描菜单*/

    _CONFIG_GATE_SWEEP_DEF  gConfig_Gate_Sweep; /*门扫描菜单*/

    _CONFIG_TRIGGER_DEF     gConfig_Trigger;  /*触发菜单*/
    _CONFIG_MARKER_DEF      gConfig_Marker;/*标记菜单*/
    _CONFIG_PEAK_DEF        gConfig_peak;/*峰值菜单*/
    _CONFIG_LIMIT_STATE_DEF gConfig_Limit; /*极限线菜单*/

    _CONFIG_GUI_DRAW_SET_DEF gConfig_GuiDrawSet;/*图形用户界面绘图集*/
    _CONFIG_EXT_DEF         gConfig_Ext; /*提取--unused*/

    _CONFIG_TRACE_DATA_DEF	 gConfig_Trace_Data;
    _CONFIG_MARKER_DATA_DEF gConfig_Marker_Data;/*mark数据*/
    _CONFIG_LIMIT_DATA_DEF  gConfig_Limit_Data;/*极限线数据*/
}_CONFIG_STATE_MSDATA_DEF;
AJSON(SACfgStateMsdata,
    gCurrentWorkState,
    gConfig_Measure,
    gConfig_Sweep,
    gConfig_Gate_Sweep,
    gConfig_Trigger,
    gConfig_Marker,
    //gConfig_peak,
    gConfig_Limit
    //gConfig_GuiDrawSet,
    //gConfig_Ext,
    //gConfig_Trace_Data,
    //gConfig_Marker_Data,
    //gConfig_Limit_Data
    )


typedef struct SACfgAll
{
    _CONFIG_FREQ_SPAN_DEF   gConfig_FreqSpan;/*频率扫宽配置*/
    _CONFIG_BW_DEF          gConfig_BW;/*带宽配置*/
    _CONFIG_AMPLITUDE_DEF   gConfig_Amplitude;/*幅度配置*/
    _CONFIG_TRACE_DEF       gConfig_Trace;/*迹线配置*/

    quint64              gCenterFreq = 0;/*中心频率*/
    quint32              mSaveLoad_CurrentMode = 0;/*当前状态--当前哪种MeasureMode*/
    _CONFIG_SHR_DEF         gConfig_ShareMem;/*共享内存配置--unused*/

    _CONFIG_STATE_MSDATA_DEF pSpanModeParam;/*跨度模式参数,此模式下会进行极限绘制*/
    _CONFIG_STATE_MSDATA_DEF pChnlPowerModeParam;/*通道功率模式参数*/
    _CONFIG_STATE_MSDATA_DEF pOccupiedModeParam;/*占用模式参数*/
    _CONFIG_STATE_MSDATA_DEF pACPModeParam;/*ACP模式参数*/
    _CONFIG_STATE_MSDATA_DEF pMultiACPModeParam;/*多ACP模式参数*/
    _CONFIG_STATE_MSDATA_DEF pSpectrumEmissionMaskModeParam;/*光谱发射掩模模式参数*/
    _CONFIG_STATE_MSDATA_DEF pSpuriousEmissionMaskModeParam;/*杂散发射掩模模式参数*/
    _CONFIG_STATE_MSDATA_DEF pFieldStrengthModeParam;/*场强模式参数*/
    _CONFIG_STATE_MSDATA_DEF pDemodulationModeParam;/*解调模式参数*/
}_ALL_STATE_MSDATA_DEF;

typedef struct SAAllConfig
{
    _CONFIG_FREQ_SPAN_DEF   gConfig_FreqSpan;/*频率扫宽配置*/
    _CONFIG_BW_DEF          gConfig_BW;/*带宽配置*/
    _CONFIG_AMPLITUDE_DEF   gConfig_Amplitude;/*幅度配置*/
    _CONFIG_TRACE_DEF       gConfig_Trace;/*迹线配置*/

    quint64              gCenterFreq = 0;/*中心频率*/
    quint32              mSaveLoad_CurrentMode = 0;/*当前状态--当前哪种MeasureMode*/
    _CONFIG_SHR_DEF         gConfig_ShareMem;/*共享内存配置--unused*/

    _CONFIG_STATE_MSDATA_DEF measureModeParam;/*测量模式对应的配置参数*/
}_SA_ALL_CONF_DEF,*p_SA_ALL_CONF_DEF;
AJSON(SAAllConfig,
    gConfig_FreqSpan,
    gConfig_BW,
    gConfig_Amplitude,
    gConfig_Trace,
    gCenterFreq,
    mSaveLoad_CurrentMode,
    //gConfig_ShareMem,
    measureModeParam
)

