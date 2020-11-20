#ifndef PM_FILE_USER_VARIABLE_H
#define PM_FILE_USER_VARIABLE_H

#include "pm_define.h"

enum
{
    PM_STATE_DEFAULT_FILE = 0,
    PM_STATE_LAST_FILE,
    PM_STATE_USER_FILE,
};
#define PM_DEFAULT_COND    "pm_default.cond"
#define PM_LAST_COND       "pm_last.cond"
#define PM_USER_COND       "pm_user.cond"
#define PM_PRE_STATE_FILE  "pm_state.pres"

typedef struct
{
    qulonglong       nlCenterFreq;  //功率采集中心频率
    qulonglong       nlStartFreq;	//功率采集起始频率
    qulonglong       nlStopFreq;	//功率采集停止功率
    qulonglong       nlStepFreq;	//此处为旋钮的步进 在中心频率和起始频率停止频率上面Input用旋钮控制的步进
    qulonglong       nlSpan;        //功率扫宽
//    qint32       nlSpanUp;      //扫宽旋钮前进步进
//    qint32       nlSpanDown;    //扫宽旋钮后退步进
    qulonglong    nlLastSpan;	//上一次扫宽
    qint32       nSpanType;
    qint32       nChannelType;  //
    qint32       nChannelStd;	//标准频率索引号
    qint32       nChannelSelID;	//标准频率索ID号
    qint32       nChannelNumber;
    qint32       nChannelStep;
    qint32       nOffsetFreqOn;
    qulonglong       nlOffsetFreq;	//频率偏移
//    qulonglong       nlOffsetFreqSize;

}_PM_CONFIG_FREQ_;

typedef struct
{
    qreal       fMax;
    qreal       fMin;
    qreal       fOffset;
    qint32      nUnits;
    qint32      nForwardRelative;
    qint32      nReverseRelative;
    qreal       fForwardRelativeData;
    qreal       fReverseRelativeData;

} _PM_CONFIG_AMPT_;

typedef struct
{
    qint32  nSweepType;
    quint8  nTimeInterval;
    qreal    fDutyCycle;

} _PM_CONFIG_SWEEP_;

typedef struct
{
    qint32 nAcquisition;
    bool bIsAverageFlg;
    qint32 nRunningAverage;
    qint32 nMaxHold;

}_PM_CONGIG_AVE_;

typedef struct
{
    qint32  nZero;
    qreal m_fZeroBaseForward;
    qreal  m_fZeroBaseReverse;
    qint8 nSelectCalType;
    qint16 nFreq;
    qint16 nArray;

}_PM_CONFIG_ZERO_;

typedef struct
{
    quint8    nModle;
    qreal   fOffset;

}_PM_CONFIG_MEASURE_;

typedef struct
{
    qint32   nLimitFlg;
    qreal    fForwardUp;
    qreal    fForwardLow;
    qreal    fReverseUp;
    qreal    fReverseLow;
    qint32   nVideoBw;
    qreal    fCCDF;

}_PM_CONFIG_LIMIT_;

typedef struct
{
//    qint32 nForward;
//    qint32 nReverse;
    qint32 nShowDisplayModle;
    qint32 nFordardMode;
    qint32 nReverseMode;
    qint32 nSysDisplay;
}_PM_CONFIG_DISPLAY_;

typedef struct
{
    qint32 nStartMode;
    qint32 nStartFileType;
}_PM_CONFIG_PRESET_;

//Link FLG by Roc
#define PM_LINK_STATE_FILE  "pm_state.link"
typedef struct
{
    qint32 linkMode;
    qint32 linkFileType;
}_PM_CONFIG_LINK_;

typedef struct
{
    _PM_CONFIG_FREQ_        gConfig_Freq;
    _PM_CONFIG_AMPT_        gConfig_Ampt;
    _PM_CONFIG_SWEEP_       gConfig_Sweep;
    _PM_CONGIG_AVE_         gConfig_Ave;
    _PM_CONFIG_ZERO_        gConfig_Zero;
    _PM_CONFIG_MEASURE_     gConfig_Measure;
    _PM_CONFIG_LIMIT_       gConfig_Limit;
    _PM_CONFIG_DISPLAY_     gConfig_Display;
    _PM_CONFIG_PRESET_      gConfig_Preset;

} _PM_FILE_SAVE_LOAD_VARIABLE_;

#pragma pack(1)

// for powersensor [
typedef struct
{
    unsigned char _STX[4];
    unsigned char _CMD[2];
    unsigned char _Length[2];
}_UART_Header;

typedef struct
{
    unsigned short SetFreq;
}_PowerSensorMsg_SingleModeRQ;

typedef struct
{
    unsigned short SetFreq;
    char RunStop;
}_PowerSensorMsg_ContinuousModeRQ;

typedef struct
{
    short Temperature;              // temp * 10
    short PowerLevel;				// Power level * 100
}_PowerSensorMsg_MeasureModeRP;

typedef struct
{
    unsigned short SetFreq;
    short TargetPowerLevel;
}_PowerSensorMsg_RawModeRQ;

typedef struct
{
    short Temperature;              // temp * 10
    unsigned short ADCdata;         // ADC raw data
    short PowerLevel;				// Power level * 100
}_PowerSensorMsg_RawModeRP;

typedef struct
{
    unsigned char modelnum[16];          // name
    unsigned char serialnum[16];         // S/N
    unsigned char FW_Ver[3];             // char[0] HW Ver 255, char[1] SW Major 255, char[2] SW Patch 255
    unsigned char type;                  // 0x0? : terminating, 0x1? : Directional  +  0x?0 : Average, 0x?1 : Peak
}_PowerSensorMsg_Inventory;

typedef struct
{
    unsigned char modelnum[16];          // name
    unsigned char serialnum[16];         // S/N
}_PowerSensorMsg_Inventory_Update;

typedef struct         // ReferenceTemperature for Calibration
{
    short RT4C;          // temperature * 10
}_PowerSensorMsg_RT4C;

typedef struct
{
    unsigned char ArrayNumber[2];
    unsigned short Frequency;
    unsigned short ADC_Data[63];
}_PowerSensorMsg_CalibrationTable;

typedef struct
{
    unsigned int FWSize;
    unsigned int TotalPackageNumber;
    unsigned int _Reserved;
}_PowerSensorMsg_FWDownloadReady;

typedef struct
{
    unsigned int PackageNumber;
    unsigned int PackageSize;
    unsigned char _Package[512];
}_PowerSensorMsg_FWDownloadPackage;

typedef struct
{
    unsigned char FW_CRC[2];
    unsigned char _Reserved[2];
}_PowerSensorMsg_FWDownloadEnd;

// for powersensor ]

#pragma pack()





#endif // FILE_USER_VARIABLE_H
