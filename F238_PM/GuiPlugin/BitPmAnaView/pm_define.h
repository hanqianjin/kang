/**************Copyright (c)**************************************
 **
 **               INNO Instrument(China) Co.,Ltd.
 **
 **------------File Info------------------------------------------
 **Class name:              define.h
 **Latest Version:          V1.0.0
 **Latest modified Date:
 **Created by:              Roc
 **Created date:            2019.11.20
 **Descriptions:            PM all define should define in this file
 **
 *****************************************************************/


#ifndef PM_DEFINE_H
#define PM_DEFINE_H

// Close variable defined but not used
#ifdef __GNUC__
#define VARIABLE_IS_NOT_USED __attribute__ ((unused))
#else
#define VARIABLE_IS_NOT_USED
#endif

#include <QtGlobal>

enum{
    POWER_SENSOR_V90 =0,
    POWER_SENSOR_V91 = 1,
};

//V90协议标志
#define PM_V90_FREQ_MIN    50000000LL // 50MHz
#define PM_V90_FREQ_MAX  6000000000LL  //6GHZ
#define PM_V90_POWER_MIN  -45. // -45 dBm
#define PM_V90_POWER_MAX  10. // 10 dBm
enum {
    V90_SINGLE_MODE = 0,
    V90_CONTINUOUS_MODE,
    V90_CALIBRATION_TABLE_READ,
    V90_CALIBRATION_TABLE_WRITE,
    V90_CALIBRATION_READY,
    V90_INVENTORY_READ,
    V90_INVENTORY_WRITE,
    V90_F_W_DOWNLOAD_READY,
    V90_F_W_DOWNLOAD_PACKAGE,
    V90_F_W_DOWNLOAD_PACKAGE_END,
};

//#define PM_V90_SPAN_INTERVAL_NUMBER   12
//const unsigned qulonglong PM_V90_SPAN_STEP_VALUE[PM_V90_SPAN_INTERVAL_NUMBER] = 		// 1MHz -- 5.95GHz
//{2000000,5000000,10000000,20000000,50000000,100000000,200000000,500000000,1000000000,2000000000,5000000000,5950000000};

#define PM_V90_MIN_SPAN     1000000LL
#define PM_V90_MAX_SPAN  5950000000LL

#define PM_V90_CAL_AMPT 63

#define PM_CAL_MULTIPLE 100.
//V91协议标志
#define PM_V91_FREQ_MIN   300000000LL // 300MHz
#define PM_V91_FREQ_MAX  3800000000LL  //3800MHz
#define PM_V91_AVER_MIN  21.76 // 21.76 dBm
#define PM_V91_AVER_MAX  51.76 // 51.76 dBm
#define PM_V91_PEAK_MIN  36.02 // 36.02 dBm
#define PM_V91_PEAK_MAX  56.02 // 56.02 dBm

enum {
    V91_SINGLE_MODE_GET = 0,
    V91_CONTINUOUS_MODE_GET,
    V91_CONTROL_DATA_GET,
    V91_CONTROL_DATA_SET,
    V91_INVENTORY_DATA_GET,
    V91_F_W_DOWNLOAD_START,
    V91_F_W_DOWNLOAD_DATA,
    V91_F_W_DOWNLOAD_FINAL,
};
enum{
    PM_CALIBRATION_ARRAY =0,
    PM_CALIBRATION_FREQ = 1,
};
//#define PM_V91_SPAN_INTERVAL_NUMBER    11
//const unsigned qulonglong PM_V91_SPAN_STEP_VALUE[PM_V91_SPAN_INTERVAL_NUMBER] = 		// 1MHz -- 3500MHz 注意最大扫宽为频率最大值 - 频率最小值
//{2000000ULL,5000000ULL,10000000ULL,20000000ULL,50000000ULL,100000000ULL,200000000ULL,500000000ULL,1000000000ULL,2000000000ULL,3500000000ULL};
#define PM_V91_MIN_SPAN     1000000LL
#define PM_V91_MAX_SPAN  3500000000LL

#define PM_ZERO_CALIBRATION_NUM 30

#define PM_SWEEP_TIME_MIN 1
#define PM_SWEEP_TIME_MAX 255

#define PM_LIMIT_DUTY_MIN 0.0
#define PM_LIMIT_DUTY_MAX 100.0

#define PM_RUNNING_AVERAGE_MAX 1000
#define PM_RUNNING_AVERAGE_MIN 1 //数据1
#define PM_DATA_ZERO 0 //数据0
////设置扫宽数据个数
//const unsigned int PM_SPAN_Table[3] ={ 1,2,5};

#define PM_SPAN_MIN      1000000LL // 1MHz
#define PM_SPAN_MAX   3800000000LL // 3.8GHz

//旋钮消息定义
#define PM_CLOCKWISE     0
#define PM_ANTICLOCKWISE 1


#define PM_S      1000000       // 1 s   time/1000000
#define PM_MS     1000          // 1 ms  time/1000
#define PM_US     1             // 1 us  reference
#define PM_NS     1000          // 1 s   time*1000

#define PM_GHZ      1000000000    // 1GHz
#define PM_MHZ      1000000       // 1MHz
#define PM_KHZ      1000          // 1kHz
#define PM_HZ       1             // 1Hz

#define PM_mGHz     *1000000000    // 1GHz
#define PM_mMHz     *1000000       // 1MHz
#define PM_mkHz     *1000          // 1kHz
#define PM_mHz      *1             // 1Hz

#define PM_dBuVFix        107.
#define PM_dBmVFix       47.
#define PM_dBVFix       -13.

#define PM_REFRESH_DEFAULT_TIME 90000 //线程默认刷新时间间隔
enum{
 PM_NORMAL_SPAN = 0,
 PM_MIN_SPAN    = 1,
 PM_FULL_SPAN   = 2,
};
enum{
 PM_BUTTON_OFF  = 0,
 PM_BUTTON_ON   = 1,
};

enum
{
    PM_MEASUER_AVG  = 0,
    PM_MEASUER_PEAK = 1,
    PM_MEASUER_PULSE= 2 ,

};


//Sweep Type
enum {
    PM_SINGLE                     = 0,
    PM_CONT                       = 1,
};

//average
enum{
    PM_AVERAGE_FAST             = 0,
    PM_AVERAGE_MED              =  1,
    PM_AVERAGE_SLOW             =  2,
};
//Limit
enum{
    PM_LIMIT_FULL               = 0,
    PM_LIMIT_4K                 =  1,
    PM_LIMIT_200K               =  2,
};
//Amplitude Unit
enum {
    PM_DBM   = 0,
    PM_DBV   ,
    PM_DBMV  ,
    PM_DBUV  ,
    PM_VOLT  ,
    PM_WATTS ,

    PM_NONE  ,
    PM_DELTA_VOLT,
    PM_DELTA_WATTS,
};

//设置左侧参数设置框矩形区域
#define PM_DIGITAL_DIALOG_WIDTH   252
#define PM_DIGITAL_DIALOG_HEIGHT  646


#define PM_SCREEN_CAPTURE_STARTX     0
#define PM_SCREEN_CAPTURE_STARTY     0
#define PM_SCREEN_CAPTURE_WIDTH      1280
#define PM_SCREEN_CAPTURE_HEIGHT     800

VARIABLE_IS_NOT_USED static unsigned char Pm_GucRegularString[] = {'\\', '/', ':', '*', '?', '<', '>','|', ';', '&', '`', '\'', '\"' };

#define PM_MODULE    1
#define PM_START_FLAG   37


#define PM_FILEHEADER_STATE 0x52534101
#define PM_FILEHEADER_STATE_DATA 0x52534102


// MENU의 �� 택
enum {
    PM_MENU_SPECTRUM_ANALYZER   = 1,
    PM_MENU_POWER_SENSOR           = 2,
    PM_MENU_SIGNAL_ANALYZER        = 3
};

enum{
    PM_UPLINK = 0,
    PM_DOWNLINK
};

// SA Input Type Define
enum {
    PM_SHIFT_ENABLE                           = -1  ,
    PM_NOT_USE                                = 0   ,
    PM_INPUT_FREQ_CENTER                      = 1   ,
    PM_INPUT_FREQ_START                       = 2   ,
    PM_INPUT_FREQ_STOP                        ,
    PM_INPUT_FREQ_STEP                        ,
    PM_INPUT_FREQ_SPAN                        ,
//    PM_SELECT_SPAN_UP                         ,
//    PM_SELECT_SPAN_DOWN                       ,
    PM_BUTTON_SPAN_TYPE                       ,
    PM_INPUT_FREQ_CHANNEL_STANDARD            ,
    PM_INPUT_FREQ_CHANNEL_NUM                 ,
    PM_BUTTON_FREQ_OFFSET                     ,
    PM_INPUT_FREQ_OFFSET                      ,
//    PM_INPUT_FREQ_OFFSET_SIZE                 ,

    PM_INPUT_AMP_MAX                          ,
    PM_INPUT_AMP_MIN                          ,
    PM_INPUT_AMP_OFFSET                       ,
    PM_BUTTON_FORWATD_RELATIVE                ,
    PM_BUTTON_REVERSE_RELATIVE                ,
    PM_INPUT_FORWATD_RELATIVE                 ,
    PM_INPUT_REVERSE_RELATIVE                 ,
    PM_SELECT_UNITS                           ,
    PM_BUTTON_AUTO_SCALE                      ,
    PM_BUTTON_AUTO_FORWATD                    ,
    PM_BUTTON_AUTO_REVERSE                    ,

    PM_BUTTON_SWEEP_TYPE                      ,
    PM_INPUT_TIME_INTERVAL                    ,
    PM_INPUT_DUTY_CYCLE                       ,
    PM_INPUT_MEASURE_OFFSET                   ,

    PM_BUTTON_ACQ_FAST                        ,
    PM_BUTTON_ACQ_MED                         ,
    PM_BUTTON_ACQ_SLOW                        ,
    PM_INPUT_RUNNING_AVERAGE                  ,
    PM_BUTTON_MAX_HOLD                        ,

    PM_BUTTON_ZERO                            ,
    PM_INPUT_CAL_CENTER_FREQ                  ,
    PM_INPUT_CAL_ARRAY                  ,
    PM_INPUT_CAL_AMPT ,

    PM_BUTTON_LIMT                            ,
    PM_INPUT_FORWARD_UPPER                    ,
    PM_INPUT_FORWARD_LOWER                    ,
    PM_INPUT_REVERSE_UPPER                    ,
    PM_INPUT_REVERSE_LOWER                    ,
    PM_BUTTON_LIMT_FULL                       ,
    PM_BUTTON_LIMT_4K                         ,
    PM_BUTTON_LIMT_200K                       ,
    PM_INPUT_CCDF                             ,

    PM_SELECT_DISPLAY_FORWARD                 ,
    PM_SELECT_DISPLAY_REVERSE                 ,
    PM_BUTTON_SUMMARY                         ,
    PM_INPUT_SENSOR_MODLE                     ,
    PM_INPUT_SENSOR_SN                        ,
    PM_INPUT_SENSOR_FW                        ,
    PM_INPUT_SENSOR_TYPE                      ,

    PM_ALLSET_INPUT_SPAN_TYPE       ,   //Combobox 定义
    PM_ALLSET_INPUT_UNIT            ,
    PM_ALLSET_INPUT_AVG_ACQ         ,
    PM_ALLSET_INPUT_LIMIT_BW        ,
    PM_ALLSET_INPUT_DISPLAY_FORWARD ,
    PM_ALLSET_INPUT_DISPLAY_REVERSE ,
};
//PM CAL
#define V90_CAL_NUM    134
const unsigned int PM_CAL_FREQ[V90_CAL_NUM] = 		// MHZ
    {50,63,75,87,
        100,150,175,
        200,250,300,350,
        400,450,500,550,
        600,650,700,750,
        800,850,900,950,
        1000,1050,1100,1150,
        1200,1250,1300,1350,
        1400,1450,1500,1550,
        1600,1650,1700,1750,
        1800,1850,1900,1950,
        2000,2050,2100,2150,
        2200,2250,2300,2350,
        2400,2450,2500,2550,
        2600,2650,2700,2750,
        2800,2850,2900,2950,
        3000,3050,3100,3150,3175,
        3200,3250,3300,3350,
        3400,3450,3500,3550,
        3600,3650,3700,3750,3775,
        3800,3850,3875,3900,3950,3975,
        4000,4050,4075,4100,4150,
        4200,4250,4300,4350,
        4400,4450,4500,4550,4575,
        4600,4650,4675,4700,4750,
        4800,4850,4900,4950,
        5000,5050,5100,5150,
        5200,5250,5300,5350,
        5400,5450,5500,5550,
        5600,5650,5675,5700,5750,5775,
        5800,5850,5875,5900,5950,6000,
        };



enum{
    PM_FREQ_INFO = 0,
    PM_RBW_INFO,
    PM_FREQ_CF,
    PM_SYS_INFO,
    PM_ACQ_INFO,
    PM_FREQ_OFFSET,
};

enum
{
    PM_FILE_NONE = 0,
    PM_FILE_STATE,
};

enum{
    PM_DIGITIPUT_DIALOG = 0,
    PM_FREQ_DIALOG,
    PM_AMPT_DIALOG,
    PM_SWEEP_DIALOG,
    PM_AVERAGE_DIALOG,
    PM_ZERO_DIALOG,
    PM_LIMIT_DIALOG,
    PM_DISPLAY_DIALOG,
    PM_ALLSET_DIALOG,
    PM_SCREEN_CAPTURE_DIALOG,
};


enum {
    PM_LABEL_MODE = 0,
    PM_LABEL_CENTER_FREQ,
    PM_LABEL_START_FREQ,
    PM_LABEL_STOP_FREQ,
    PM_LABEL_SPAN,
    PM_LABEL_CHANNEL,
    PM_LABEL_SIGNAL_STANDARD,
    PM_LABEL_SWEEP,
//    PM_LABEL_ZERO,
    PM_LABEL_OFFSET,
    PM_LABEL_FORWARD,
    PM_LABEL_REVERSE,
    PM_LABEL_ACQ,
    PM_LABEL_AVERAGE,
    PM_LABEL_MAXHOLD,
    PM_LABEL_LIMIT,
    PM_LABEL_FORWARD_UP,
    PM_LABEL_FORWARD_LOW,
    PM_LABEL_REVERSE_UP,
    PM_LABEL_REVERSE_LOW,
    PM_LABEL_DISPLAY,
    PM_LABEL_END

};
#define PM_CHSTEP_CDMA  1250000
#define PM_CHSTEP_WCDMA 5000000
#define PM_CHSTEP_TD_SCDMA 1600000
#define PM_CHSTEP_GSM 200000

#define PM_GSM900_UP_MIN 890
#define PM_GSM900_UP_MAX 915
#define PM_GSM900_DOWN_MIN 935
#define PM_GSM900_DOWN_MAX 960
#define PM_GSM1800_UP_MIN 1710
#define PM_GSM1800_UP_MAX 1785
#define PM_GSM1800_DOWN_MIN 1805
#define PM_GSM1800_DOWN_MAX 1880

#define PM_FDD_B1_UP_FREQPOINT_BASE 18000
#define PM_FDD_B1_UP_FREQPOINT_MAX 18599
#define PM_FDD_B1_DOWN_FREQPOINT_BASE 0
#define PM_FDD_B1_DOWN_FREQPOINT_MAX  599

#define PM_FDD_B3_UP_FREQPOINT_BASE  19200
#define PM_FDD_B3_UP_FREQPOINT_MAX  19949
#define PM_FDD_B3_DOWN_FREQPOINT_BASE 1200
#define PM_FDD_B3_DOWN_FREQPOINT_MAX 1949

#define PM_FDD_B1_UP_FREQ_MIN 1920000000
#define PM_FDD_B1_UP_FREQ_MAX 1979900000
#define PM_FDD_B1_DOWN_FREQ_MIN 2110000000
#define PM_FDD_B1_DOWN_FREQ_MAX 2169900000
#define PM_FDD_B3_UP_FREQ_MIN 1710000000
#define PM_FDD_B3_UP_FREQ_MAX 1784900000
#define PM_FDD_B3_DOWN_FREQ_MIN 1805000000
#define PM_FDD_B3_DOWN_FREQ_MAX 1879900000

#define PM_TD_B38_FREQPOINT_BASE 37750
#define PM_TD_B39_FREQPOINT_BASE 38250
#define PM_TD_B40_FREQPOINT_BASE 38650
#define PM_TD_B41_FREQPOINT_BASE 39650

#define PM_TD_B38_FREQPOINT_MAX 38249
#define PM_TD_B39_FREQPOINT_MAX 38649
#define PM_TD_B40_FREQPOINT_MAX 39649
#define PM_TD_B41_FREQPOINT_MAX 41589

#define PM_TD_B38_FREQ_MIN 2570000000
#define PM_TD_B38_FREQ_MAX 2619900000
#define PM_TD_B39_FREQ_MIN 1880000000
#define PM_TD_B39_FREQ_MAX 1919900000
#define PM_TD_B40_FREQ_MIN 2300000000
#define PM_TD_B40_FREQ_MAX 2399900000
#define PM_TD_B41_FREQ_MIN 2496000000
#define PM_TD_B41_FREQ_MAX 2689900000
enum{
    PM_CDMA=0,
    PM_GSM,
    PM_LTE_FDD,
    PM_LTE_TDD,
    PM_TD_SCDMA,
    PM_WCDMA,
    PM_WIMAX,
};
enum{
    PM_TD_BAND_D =0,
    PM_TD_BAND_F,
    PM_TD_BAND_E,
};

typedef struct
{
    const char *name;
    int  ChStep;
    int  index;
} __PM_ChStand__;
static const __PM_ChStand__ mPM_ChStand[7]=
{
    {"CDMA",PM_CHSTEP_CDMA,PM_CDMA},
    {"GSM",PM_CHSTEP_GSM,PM_GSM},
    {"LTE-FDD",10000000,PM_LTE_FDD},
    {"LTE-TDD",10000000,PM_LTE_TDD},
    {"TD-SCDMA",PM_CHSTEP_TD_SCDMA,PM_TD_SCDMA},
    {"WCDMA",PM_CHSTEP_WCDMA,PM_WCDMA},
    {"WIMAX",5000000,PM_WIMAX},
};
enum
{
    PM_LOCAL = 0,
    PM_REMOTE,
};
enum
{
    PM_INDOOR = 0,
    PM_OUTDOOR,
    PM_NIGHT,
};
VARIABLE_IS_NOT_USED static const char* pm_qssMode[3] = {"indoor","outdoor","night"};


enum{
    PM_LINK_NG = 0,
    PM_LINK_OK = 1,
};

enum{
    PM_LINK_FLG_DEFULT = 0, //Load SoftOara
    PM_LINK_FLG_LOAD = 1, //Load local file
    PM_LINK_FLG_READ = 2, //Read Scpi Data
};


#ifdef PM_HANLA_DEBUG
#define PM_DEBUG_STR(X)    {                                                                       \
    QString strDebug;                                                        \
    strDebug.sprintf("%s, L%d, %s()", __FILE__, __LINE__, __func__);         \
    qDebug() << #X << strDebug;                                              \
    }


#define PM_DEBUG(X)        {                                                                       \
    QString strDebug;                                                        \
    strDebug.sprintf("%s, L%d, %s()", __FILE__, __LINE__, __func__);         \
    qDebug() << #X" = " << (X) << strDebug;                                  \
    }


#define __PM__      {                                                                            \
    PM_DEBUG_STR("Current location is ");                                  \
    }



#else
#define PM_DEBUG_STR(X)
#define PM_DEBUG(X)
#define ____
#endif
#endif // PM_DEFINE_H
