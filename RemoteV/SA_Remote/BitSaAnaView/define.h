#ifndef DEFINE
#define DEFINE

#define ERROR -1
#define DOUBLEPRECISE 0.0001
#define SA_FILEHEADER_STATE 0x8BFAEE01
#define SA_FILEHEADER_STATE_DATA 0x8BFAEE02
//#define SPEC_FREQ_MIN  100000 // 100kHz
//#define SPEC_FREQ_MAX  8000000000LL // 8GHz

//by Steve,0228
#define SPEC_FREQ_MIN  0LL // 0kHz
#define SPEC_FREQ_MAX  43050000000LL // 43.05GHz

#define SPEC_AMPTD_MIN  -180. // -180. dBm  //Johnson 0918 Change
#define SPEC_AMPTD_MAX  20.   // 20 dBm

#define SPEC_REF_OFFSET_MIN  -100.
#define SPEC_REF_OFFSET_MAX   100.

#define LIMIT_EDGE_MAX 40.

#define OCCUPIED_BW_MIN 10.
#define OCCUPIED_BW_MAX 100.
#define XDB_MAX         -0.10
#define XDB_MIN         -100.

//Johnson 0702
#define CLOCKWISE     0
#define ANTICLOCKWISE 1

#define COLORLEVEL     200
#define COLORLEVEL_MIN 10
#define DENSITY_MAX    0.1

#define CURVE_MIN      0.1
#define CURVE_MAX      5

#define SA_GHZ      1000000000    // 1GHz
#define SA_MHZ      1000000       // 1MHz
#define SA_KHZ      1000          // 1kHz
#define SA_HZ       1

#define mGHz     *1000000000    // 1GHz
#define mMHz     *1000000       // 1MHz
#define mkHz     *1000          // 1kHz
#define mHz      *1             // 1Hz

#define RVM						(10)	// RBW/VBW Multifly

#define dBuVFix        107.
#define dBmVFix       47.
#define dBVFix        -13.


#define ARRAY_SIZE          6
#define MARKER_TOTAL_CNT 6

#define LIMIT_TOTAL  50    // Limit Line Edit  Total Count
#define LIMIT_SELECTSUM 6   //Johnson 0827 Limit Select Total Count
#define LIMIT_TOTALDOT  501  //Johnson 0906 total dot in every set

#define AMPTD_LBL_START_X   15
#define GRID_START_X        120   // 117
#define GRID_START_Y        127
#define GRID_WIDTH          740 //731
#define GRID_HEIGHT         560 //542
//#define GRID_HSTEP          74
//#define GRID_VSTEP          56
#define GRID_NUM_X_TICKS    10  // 0기반의 값. 실제로 11개.
#define GRID_NUM_Y_TICKS    10



#define NUM_SWEEP_POINT    801


#define NORMAL_SPAN         0
#define ZERO_SPAN           1


#define POINT_501           0
#define POINT_1001          1
#define POINT_2001          2
#define POINT_3001          3


#define SA_OFF  0
#define SA_ON   1

#define SA_PASS 1
#define SA_FAIL  0

// Trace Use  --- Start
#define TR1                  0
#define TR2                  1
#define TR3                  2
#define TR4                  3
#define TR5                  4
#define TR6                  5
#define TRACE_CNT_TOTAL      6
#define TR_AVERAGE           20
#define NUM_TRACE           TRACE_CNT_TOTAL

// Marker Use  -- Start
#define MARKER_FONT_HEIGHT  15

#define SA_M1                  0
#define SA_M2                  1
#define SA_M3                  2
#define SA_M4                  3
#define SA_M5                  4
#define SA_M6                  5

#define REF                0
#define DELTA            1
#define DELTA_PAIR            2

#define MKR_TABLE     0
#define MKR_ONLY     1
#define MKR_OFF        2

//Johnson 1115
#define MKR_CF      0
#define MKR_CFSTEP  1
#define MKR_START   2
#define MKR_STOP    3
#define MKR_REFLVL  4

// Limit
#define   UPPER        1
#define   LOWER       2
#define   LIMIT_OFF   0

//Johnson 0823
#define   LIMIT1      0
#define   LIMIT2      1
#define   LIMIT3      2
#define   LIMIT4      3
#define   LIMIT5      4
#define   LIMIT6      5


#define PRESET_FACTORY      0
#define PRESET_MARKER       1
#define PRESET_LIMIT            2

// RBW, VBW
#define _RBW						300
#define _VBW						301

#define NUM_RBW_VBW_MAN_SPAN_BOUNDARY        12
#define NUM_RBW_VBW_MAN_VARIETY                        6

#define NUM_RBW_VBW_AUTO_SPAN_BOUNDARY         7
#define NUM_RBW_VBW_AUTO_VARIETY                        7

#define ERROR_MIN_BW			0				// 0 Hz (사용 불가능)
#define ERROR_MAX_BW			100000000		// 10 MHz (사용 불가능)

#define VALID_BW				1000
#define INVALID_BW				1001

#define TIME_DEFAULT 40000
#define TIME_MAX     100000

#define DIGITINPUT_WIDTH    252
#define DIGITINPUT_HEIGHT   646

#define REF_STEP 0.01
#define SCALE_STEP 0.1
#define ATTEN_STEP 5

#define CHSTEP_CDMA  30000//1250000
#define CHSTEP_LTE   100000
#define CHSTEP_GSM   200000
#define CHSTEP_WCDMA 200000//5000000
#define CHSTEP_TD_SCDMA 200000//1600000

#define GSM900_UP_MIN 890
#define GSM900_UP_MAX 915
#define GSM900_DOWN_MIN 935
#define GSM900_DOWN_MAX 960
#define GSM1800_UP_MIN 1710
#define GSM1800_UP_MAX 1785
#define GSM1800_DOWN_MIN 1805
#define GSM1800_DOWN_MAX 1880



#define FDD_B1_UP_FREQPOINT_BASE 18000
#define FDD_B1_UP_FREQPOINT_MAX 18599
#define FDD_B1_DOWN_FREQPOINT_BASE 0
#define FDD_B1_DOWN_FREQPOINT_MAX  599

#define FDD_B3_UP_FREQPOINT_BASE  19200
#define FDD_B3_UP_FREQPOINT_MAX  19949
#define FDD_B3_DOWN_FREQPOINT_BASE 1200
#define FDD_B3_DOWN_FREQPOINT_MAX 1949

#define FDD_B1_UP_FREQ_MIN 1920000000
#define FDD_B1_UP_FREQ_MAX 1979900000
#define FDD_B1_DOWN_FREQ_MIN 2110000000
#define FDD_B1_DOWN_FREQ_MAX 2169900000
#define FDD_B3_UP_FREQ_MIN 1710000000
#define FDD_B3_UP_FREQ_MAX 1784900000
#define FDD_B3_DOWN_FREQ_MIN 1805000000
#define FDD_B3_DOWN_FREQ_MAX 1879900000

#define TD_B38_FREQPOINT_BASE 37750
#define TD_B39_FREQPOINT_BASE 38250
#define TD_B40_FREQPOINT_BASE 38650
#define TD_B41_FREQPOINT_BASE 39650

#define TD_B38_FREQPOINT_MAX 38249
#define TD_B39_FREQPOINT_MAX 38649
#define TD_B40_FREQPOINT_MAX 39649
#define TD_B41_FREQPOINT_MAX 41589

#define TD_B38_FREQ_MIN 2570000000
#define TD_B38_FREQ_MAX 2619900000
#define TD_B39_FREQ_MIN 1880000000
#define TD_B39_FREQ_MAX 1919900000
#define TD_B40_FREQ_MIN 2300000000
#define TD_B40_FREQ_MAX 2399900000
#define TD_B41_FREQ_MIN 2496000000
#define TD_B41_FREQ_MAX 2689900000

#define SPEC_EM_CENT_OFFSET_1    (2.515 / 30 * NUM_SWEEP_POINT)
#define SPEC_EM_CENT_OFFSET_2    (2.715 / 30 * NUM_SWEEP_POINT)
#define SPEC_EM_CENT_OFFSET_3    (3.515 / 30 * NUM_SWEEP_POINT)
#define SPEC_EM_CENT_OFFSET_4    (4.000 / 30 * NUM_SWEEP_POINT)

#define LINEREEOR 2
#define HALFLINEREEOR 1
enum{
    SA_TD_BAND_D =0,
    SA_TD_BAND_F,
    SA_TD_BAND_E,
};
// 십진수 40억 표현에 LL을 안 붙히면 warning이 뜬다.   //needed changed by Steve,rbw accolated with band is 100 bei
//const u64 u64RbwVbwAutoSpanBoundary[NUM_RBW_VBW_AUTO_SPAN_BOUNDARY] =
const unsigned long long u64RbwVbwAutoSpanBoundary[NUM_RBW_VBW_AUTO_SPAN_BOUNDARY] =
    {200000, 1000000, 2000000, 5000000, 50000000, 500000000, 8000000000LL};   // (60 kHz) ~ 200 kHz ~ 4400 MHz

//const u32 u32SpanRbwVbwAutoTable[NUM_RBW_VBW_AUTO_VARIETY] =
const unsigned int u32SpanRbwVbwAutoTable[NUM_RBW_VBW_AUTO_VARIETY] =
    {10000, 30000, 100000, 300000, 1000000, 3000000, 10000000};                 // 1 kHz ~ 1 MHz


// RBW/VBW 값의 종류가 변동되는 Span 경계값. - Manual 상태일 때.
//const u64 u64RbwVbwManSpanBoundary[NUM_RBW_VBW_MAN_SPAN_BOUNDARY] = 		// 100 kHz ~
const unsigned long long u64RbwVbwManSpanBoundary[NUM_RBW_VBW_MAN_SPAN_BOUNDARY] = 		// 100 kHz ~
    {80000, 150000, 511000, 2000000, 4000000, 5000000, 29000000, 100000000, 190000000, 250000000, 500000000, 4000000000LL};  // ~ 4400MHz


// Span에 따른 RBW값 종류를 나열한 Table..
//const u32 u32SpanRbwManTable[NUM_RBW_VBW_MAN_SPAN_BOUNDARY][NUM_RBW_VBW_MAN_VARIETY] =
const unsigned int u32SpanRbwManTable[NUM_RBW_VBW_MAN_SPAN_BOUNDARY][NUM_RBW_VBW_MAN_VARIETY] =
{
    {0, 0, 0, 0, 10000, ERROR_MAX_BW},                      // 60.000 KHz ~ 99.999 KHz
    {0, 0, 0, 10000, 30000, ERROR_MAX_BW},                  // 100.000 KHz ~ 199.999 KHz
    {0, 0, 10000, 30000, 100000, ERROR_MAX_BW},             // 200.000 KHz ~ 599.999 KHz
    {0, 10000, 30000, 100000, 300000, ERROR_MAX_BW},        // 600.000 KHz ~ 2.999999 MHz
    {0, 0, 30000, 100000, 300000, ERROR_MAX_BW},			// 3.000000 MHz ~ 4.999999 MHz
    {0, 30000, 100000, 300000, 1000000, ERROR_MAX_BW},	    // 5.000000 MHz ~ 5.999999 MHz
    {0, 0, 100000, 300000, 1000000, ERROR_MAX_BW},          // 6.000000 MHz ~ 29.999999 KHz
    {0, 100000, 300000, 1000000, 3000000, ERROR_MAX_BW},    // 30.000000 MHz ~ 109.999999 MHz
    {0, 0, 300000, 1000000, 3000000, ERROR_MAX_BW},         // 110.000000 MHz ~ 199.999999 MHz
    {0, 300000, 1000000, 3000000, 10000000, ERROR_MAX_BW},  // 200.000000 MHz ~ 255.999999 MHz
    {0, 0, 1000000, 3000000, 10000000, ERROR_MAX_BW},       // 256.000000 MHz ~ 511.999999 MHz
    {0, 0, 0, 3000000, 10000000, ERROR_MAX_BW}              // 512.000000 MHz ~ 4.000000000 GHz
};

//work mode
enum{
    SA_SPAN_MODE = 0,
    SA_CHNLPOWER_MEASURE_MODE,
    SA_OCCUPIED_BW_MEASURE_MODE,
    SA_SPECTRUM_EMISSION_MASK_MODE,
    SA_ACP_MEASURE_MODE,
    SA_MULTI_ACP_MODE,
    SA_SPURIOUS_EMISSION_MASK_MODE,
    SA_FIELD_STRENGTH_MODE,
    SA_DEMODULATION_MODE
};
enum {
    SA_SWEPT_SA = 0,
    SA_CHANNEL_POWER,
    SA_OCCUPIED_BW,
    SA_SPECTRUM_EMISSION_MASK,
    SA_ACP,
    SA_MULTI_ACP,
    SA_SPURIOUS_EMISSION_MASK,
    SA_FIELD_STRENGTH,
    SA_DEMODULATION
};
static const char* SA_MeasureName[9]=
{
    "Swept SA",
    "Channel Power",
    "Occupied BW",
    "Spectrum Emission Mask",
    "ACP",
    "Multi-ACP",
    "Spurious Emission",
    "Field Strength",
    "AM/FM Audio Demod"
};
//Johnson 0926
enum {
  SA_OCCUPIED = 1,
  SA_XDB      =2
};

// MENU의 선택
enum {
    SA_MENU_SPECTRUM_ANALYZER   = 1,
    SA_MENU_POWER_SENSOR           = 2,
    SA_MENU_SIGNAL_ANALYZER        = 3
};


// Primary  Key    //Johnson 0718
enum {
    SA_MEASUREMENT = 1,
    SA_FREQUENCY   = 2,
    SA_BW           = 3,
    SA_AMPLITUDE   = 4,
    SA_SWEEP        = 5,
    SA_TRACE        = 6,
    SA_MARKER       = 7,
    SA_PEAK         = 8,
    SA_LIMIT        = 9,
    SA_LOAD         = 10,
    SA_SAVE         = 11,
    SA_SYSTEM       = 12,
    SA_PRESET       = 13,
    SA_POWERSENSOR  = 14,
    SA_SPAN         = 15,
    SA_DISPLAY      = 16,
    SA_TRIGGER      = 17,
    SA_MARKER_TAB   = 18,
    SA_MARKER_ALLSET,
};

// Measurement
//enum {
//    MEAS_OFF              = 0,
//    SA_CHANNEL_POWER   = 1,
//    SA_ACP                        = 2,
//    SA_DEMODULATION     = 3,
//    SA_OCCUPIED_BW      = 4
//};

// Demodulation
enum {
    SA_AM              = 0,
    SA_FM               = 1,
    SA_NFM             = 2
};


// ZeroSpanMode
enum {
    _AMPLITUDE              = 0,
    _FREQUENCY              = 1,
    _PHASE                  = 2
};

// SA Input Type Define
enum {
    SA_NOT_USE                                = 0,
    SA_INPUT_MEASUREMENT                      = 1,
    SA_INPUT_FREQ_CENTER                      = 2,
    SA_INPUT_FREQ_START                        = 3,
    SA_INPUT_FREQ_STOP                         = 4,
    SA_INPUT_FREQ_CF                             = 5,
    SA_INPUT_REF_LEVEL                           = 6,
    SA_INPUT_ATTEN                                = 7,
    SA_INPUT_SCALEDIV                            = 8,
    SA_INPUT_PREAMP                              = 9,
    SA_INPUT_REF_OFFSET                        = 10,
    SA_INPUT_FREQ_SPAN                        = 11,
    SA_INPUT_MANUAL_RBW                    = 12,
    SA_INPUT_MANUAL_VBW                     = 13,
    SA_INPUT_AUTO_RBW                           = 14,
    SA_INPUT_AUTO_VBW                            = 15,
    SA_INPUT_SWEEP_TIME                          = 16,
    SA_INPUT_SWEEP_TYPE                         = 17,
    SA_INPUT_OVERLAP                              = 18,

    SA_INPUT_TRACE_AVERAGE                    = 19,
    SA_INPUT_AVERAGE_COUNT                    = 20,
    SA_INPUT_MARKER_EDIT                      = 21,
    SA_INPUT_DELTA_MARKER_EDIT                = 22,

    SA_INPUT_CHANNEL_BANDWIDTH           = 23,
    SA_INPUT_CHANNEL_SPACING                 = 24,

    SA_INPUT_POWERSENSOR_FREQ             = 25,
    SA_INPUT_POWERSENSOR_EXT_OFFSET    ,

    SA_ENTRY_HIDE,
    SA_LIMIT_EDGE,  //Johnson 0824

    //Johnson 0927
    SA_INPUT_OCCUPIED        ,
    SA_INPUT_XDB             ,
    SA_INPUT_PERSISTENCE_TIME         ,
    SA_INPUT_HIGHEST_DENSITY          ,
    SA_INPUT_LOWEST_DENSITY           ,
    SA_INPUT_CURVE                    ,

    //Tony 0214
    SA_INPUT_FREQ_OFFSET,
    SA_INPUT_CH_STD,
    SA_INPUT_CH_NUM,
    SA_INPUT_CH_STEP,
    SA_INPUT_ZEROSPAN_TIME,
    SA_INPUT_PERIOD_TIME,
    SA_INPUT_LIMIT_FREQ,
    SA_INPUT_LIMIT_AMPT,

    //Johnson 190410
    SA_INPUT_ZERORESTRAINATTEN,
    SA_INPUT_ZERORESTRAINPHASE,
    SA_INPUT_LIMIT_CURPOINTSET,

    //Tony 190506
    SA_INPUT_TRIGGER_DELAY_VALUE,
    SA_INPUT_TRIGGER_LEVEL,
    SA_INPUT_TRIGGER_PERTIMER,

    //Tony 190515
    SA_INPUT_SPUREM_SPUR_INDEX ,
    SA_INPUT_SPUREM_RANGE_INDEX ,
    SA_INPUT_SPUREM_FREQ_START ,
    SA_INPUT_SPUREM_FREQ_STOP ,
    SA_INPUT_SPUREM_SWEEP_TIME ,
    SA_INPUT_SPUREM_LIMIT_START ,
    SA_INPUT_SPUREM_LIMIT_STOP ,
    SA_INPUT_SPUREM_PEAK_DEFINITION ,
    SA_INPUT_SPUREM_PEAK_THRESHOLD ,
    SA_INPUT_SPUREM_ATTEN ,

    SA_INPUT_DOT_SWEEP_TIME,

    //Johnson 190903
    SA_INPUT_DOORCTRL_TRIGDELAY,
    SA_INPUT_DOORCTRL_DOORWID,
    SA_INPUT_DOORCTRL_PRVTTIME,
    SA_INPUT_DOORCTRL_TRIGGERLEVEL,
    SA_INPUT_DOORCTRL_PERI_PERIOD,
    SA_INPUT_DOORCTRL_PERI_SYNSRCDELAY,
    SA_INPUT_DOORCTRL_PERI_SRCPRVTTIME,
    SA_INPUT_DOORCTRL_GATEVIEW_STARTTIME
};
enum{
  SA_COMBOBOX_ATTEN = -1,
  SA_COMBOBOX_UNIT = -2,
  SA_COMBOBOX_SIGNALSTD = -3,
  SA_COMBOBOX_RBW = -4,
  SA_COMBOBOX_VBW = -5,
  SA_COMBOBOX_RATIO = -6,
  SA_COMBOBOX_TRACE =-7,
  SA_COMBOBOX_DETECTOR =-8,
  SA_COMBOBOX_IFOUTPUT =-9,
  SA_COMBOBOX_TRIGGER = -10,

};
// Sweep - Detector
enum {
    /*MAX                       = 0,
    MIN                        = 1,
    SA_SAMPLE                  = 2,
    AVERAGE_POWER   = 3,
    AVERAGE_VOLTAGE = 4*/
    SA_AUTO_DETECTOR  = 0,
    SA_POSITIVE_PEAK  = 1,
    SA_NEGATIVE_PEAK  = 2,
    SA_SAMPLE         = 3,
    SA_COMMON         = 4,  //Normal
    SA_AVERAGE_VOTAGE = 5,
    SA_RMS            = 6
};


enum {
    SA_NORMAL  = 0,
    SA_FAST    = 1
};

#define TRIGGER_SOURCE_CNT 6
// Sweep - Trigger
enum {
    SA_TRIGGER_FREE_RUN = 0,
    SA_TRIGGER_EXTERNAL,
    SA_TRIGGER_VIDEO,
    SA_TRIGGER_PERIODIC_TIMER,
    SA_TRIGGER_RF_BURST,
    SA_TRIGGER_GPS,
};
// Sweep Graph의 Mouse Click 동작
enum {
    SA_NOT_MOUSE_CLICK    = 0,
    SA_MOUSE_ACTION         = 1,
};

//Sweep Type
enum {
    SA_CONT                       = 0,
    SA_SINGLE                     = 1,
    SA_SWEEP_OFF                  = 2
};
//Johnson Add
//Atten Auto Manul

enum{
    SA_MANUAL    = 0,
    SA_AUTO      = 1,
    SA_COUPLE    = 2,
};
enum{
    SA_TRACE_TOGGLE,
    SA_AVERAGE_TOGGLE,
};
/*
enum
{

    SA_ATTEN_AUTO = 1,
    SA_ATTEN_COUPLE=2,
    SA_ATTEN_MANUAL=3 ,
};
*/

//Amplitude Unit
enum {
    SA_DBM   = 0,
    SA_DBV   ,
    SA_DBMV  ,
    SA_DBUV  ,
    SA_VOLT  ,
    SA_WATTS ,

    SA_NONE  ,
    SA_DELTA_VOLT,
    SA_DELTA_WATTS,
};


// Trace
enum {
    SA_CLEAR_WRITE = 0,
    SA_MAX_HOLD  ,
    SA_MIN_HOLD ,
    SA_VIEW ,
    SA_TRACE_AVE ,
    SA_TRACE_OFF ,

};


enum {
    SA_next_menu_dp_action = 1,
    SA_run_action          = 2
};

enum{
    SA_SPECEM_ABS = 0,
    SA_SPECEM_REL,
    SA_SPECEM_INTE_PWR
};
enum{
    SA_SPECEM_TOTALPWR = 0,
    SA_SPECEM_PSD,
    SA_SPECEM_SPECPEAK
};
#define SAVE_FILE_TYPE_SCREEN 101
#define SAVE_FILE_TYPE_CONFIG 102
#define SAVE_FILE_TYPE_TRACE   103


// 디버그 메시지 뿌릴 것인지 선택.
#define HANLA_DEBUG
//#define HANLA_NDEBUG


#ifdef HANLA_DEBUG
#define DEBUG_STR(X)    {                                                                       \
                            QString strDebug;                                                        \
                            strDebug.sprintf("%s, L%d, %s()", __FILE__, __LINE__, __func__);         \
                            qDebug() << #X << strDebug;                                              \
                        }


#define DEBUG(X)        {                                                                       \
                            QString strDebug;                                                        \
                            strDebug.sprintf("%s, L%d, %s()", __FILE__, __LINE__, __func__);         \
                            qDebug() << #X" = " << (X) << strDebug;                                  \
                        }


#define ____      {                                                                            \
                            DEBUG_STR("Current location is ");                                  \
                        }



#else
#define DEBUG_STR(X)
#define DEBUG(X)
#define ____
#endif

//Johnson 1015 Add
#define WINDOW_WIDTH              1280
#define WINDOW_HEIGHT             800
#define DPX_LENGHT                1000000
#define GRIDX_LENGTH              11
#define GRIDY_LENGTH              11

#define MODALDIALOG_STARTX        266
#define MODALDIALOG_STARTY        300
#define MODALDIALOG_WIDTH         450
#define MODALDIALOG_HEIGHT        190

#define MESSAGEDIALOG_STARTX      720
#define MESSAGEDIALOG_STARTY      400
#define MESSAGEDIALOG_WIDTH       450
#define MESSAGEDIALOG_HEIGHT      190

#define SCREEN_CAPTURE_STARTX     0
#define SCREEN_CAPTURE_STARTY     0
#define SCREEN_CAPTURE_WIDTH      1280
#define SCREEN_CAPTURE_HEIGHT     800

#define TABLEWIDGET_HEADER_LENGTH 120
#define TABLEWIDGET_WIDTH         260
#define TABLEWIDGET_OPACITY       0.9
#define TABLEWIDGET_AMP_MAX       30.
#define TABLEWIDGET_AMP_MIN       -170.

#define XDB_PRICISION             0.8

#define PAINTAREA_WIDTH           868
#define PAINTAREA_HEIGHT          739
#define REPAINTAREA_STARTX        62
#define REPAINTAREA_STARTY        107
#define REPAINTAREA_WIDTH         806
#define REPAINTAREA_HEIGHT        632
#define TABLEAREA_HEIGHT          150          

#define LEFTMARGINE               55
#define RIGHTMARGINE              5
#define TOPMARGINE                10
#define BOTTOMMARGINE             10

#define DPXWIDTH                  748
#define DPXHEIGHT                 612

#define ZEROSPAN_SWEEPTIMEMIN     24.
#define SWEEPTIMEMAX              200000.
#define NOZEROSPAN_SWEEPTIMEMIN   0.4
#define NOZEROSPAN_SWEEPTIMEMAX   1000000.
//Tony 19-02-14
/*
#define SMALLDRAW_START_X         255
#define SMALLDRAW_START_Y         65
#define SMALLDRAW_WIDTH           943
#define SMALLDRAW_HEIGHT          578
#define SMALLDRAW_GRID_WIDTH      890
#define SMALLDRAW_GRID_HEIGHT     527
*/
//Johnson 1217
#define SMALLDRAW_START_X         255
#define SMALLDRAW_START_Y         65
#define SMALLDRAW_WIDTH           943
#define SMALLDRAW_HEIGHT          578
#define SMALLDRAW_GRID_WIDTH      890
#define SMALLDRAW_GRID_HEIGHT     527


#define LARGEDRAW_START_X         0
#define LARGEDRAW_START_Y         0//70//0
#define LARGEDRAW_WIDTH           1200
#define LARGEDRAW_HEIGHT          766//715//645//715
#define LARGEDRAW_GRID_WIDTH      1140
#define LARGEDRAW_GRID_HEIGHT     660//590//660

//Tony 02-15
#define SA_LEFTDIS   70
#define SA_TOPDIS    40
#define SA_BOTTOMDIS 30 //60
#define SA_RIGHTDIS  30

#define SA_WORDHEIGHT 15
#define SA_WORDWITH   280

#define DRAW_GRID_START_X         SA_LEFTDIS//50
#define DRAW_GRID_START_Y         SA_TOPDIS//20
#define SA_LINEWIDTH   2


#define DRAW_AMPTD_LBL_START_X    20
#define DRAW_AMPTD_LBL_WIDTH      47//45
#define DRAW_AMPTD_LBL_HEIGHT     16//30

//*********Johnson 0222
//table
#define MARKER_TABLE_HEIGHT                            60
#define CHANNELPOWER_TABLE_HEIGHT                      105//85//58
#define ACP_TABLE_HEIGHT                               80
#define MULTIACP_TABLE_HEIGHT                          125
#define OCCUPIED_TABLE_HEIGHT                          130//58
#define SPECEM_TABLE_HEIGHT                            180//58
#define SPUR_TABLE_HEIGHT                              120

#define LEFTWIDGET_HIDE_TABLE_WIDTH                    1105
#define LEFTWIDGET_SHOW_TABLE_WIDTH                    850

#define RIGHT_CONTROLWIDGET_WIDTH                      93
//pixmap
#define FULLSCREEN_CENTERAREA_STARTX                   0
#define FULLSCREEN_CENTERAREA_STARTY                   0
#define FULLSCREEN_CENTERAREA_WIDTH                    1198
#define FULLSCREEN_CENTERAREA_HEIGHT                   766

#define NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTX 1
#define NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_STARTY 65
#define NOTFULLSCREEN_LEFTWIDGETHIDE_CENTERAREA_WIDTH  1196

#define NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTX 255
#define NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_STARTY 65
#define NOTFULLSCREEN_LEFTWIDGETSHOW_CENTERAREA_WIDTH  943

#define CHANNELPOWER_MARKERTABLE_SHOW_CENTERAREA_HEIGHT 483//503//530
#define CHANNELPOWER_MARKERTABLE_HIDE_CENTERAREA_HEIGHT 543//563//590
#define ACP_MARKERTABLE_SHOW_CENTERAREA_HEIGHT          508
#define ACP_MARKERTABLE_HIDE_CENTERAREA_HEIGHT          568
#define MULTIACP_MARKERTABLE_SHOW_CENTERAREA_HEIGHT     463
#define MULTIACP_MARKERTABLE_HIDE_CENTERAREA_HEIGHT     523
#define OCCUPIEDBW_MARKERTABLE_SHOW_CENTERAREA_HEIGHT   458//530
#define OCCUPIEDBW_MARKERTABLE_HIDE_CENTERAREA_HEIGHT   518//590

#define SPECEM_MARKERTABLE_SHOW_CENTERAREA_HEIGHT   408//530
#define SPECEM_MARKERTABLE_HIDE_CENTERAREA_HEIGHT   468//590

#define SPUR_MARKERTABLE_SHOW_CENTERAREA_HEIGHT   468//530
#define SPUR_MARKERTABLE_HIDE_CENTERAREA_HEIGHT   528//590

#define SA_SPAN_MARKERTABLE_SHOW_CENTERAREA_HEIGHT         578
#define SA_SPAN_MARKERTABLE_HIDE_CENTERAREA_HEIGHT         648
//rightButtonBar
#define FULLSCREEN_RIGHTBUTTONBAR_STARTX               1197
#define FULLSCREEN_RIGHTBUTTONBAR_STARTY               0
#define FULLSCREEN_RIGHTBUTTONBAR_WIDTH                83
#define FULLSCREEN_RIGHTBUTTONBAR_HEIGHT               765

#define NOTFULLSCREEN_RIGHTBUTTONBAR_STARTX            1197
#define NOTFULLSCREEN_RIGHTBUTTONBAR_STARTY            65
#define NOTFULLSCREEN_RIGHTBUTTONBAR_WIDTH             83
#define NOTFULLSCREEN_RIGHTBUTTONBAR_HEIGHT            648

//the size of pixmap to right of the table widget
#define TABLEWIDGET_RIGHTMARGIN                        100



enum{
    SA_FREQ_DIALOG,
    SA_DIGITIPUT_DIALOG,
    SA_AMPT_DIALOG,
    SA_DISPLAY_DIALOG,
    SA_BW_DIALOG,
    SA_TRIGGER_DIALOG,
    SA_TRACE_DIALOG,
    SA_MARKER_DIALOG,
    SA_LIMIT_DIALOG,
    SA_MEASURE_DIALOG,
    SA_MEASUREPARASET_DIALOG,
    SA_ALL_SETUP_DIALOG,
    SA_RIGHTBTN2,
    SA_RIGHTBTN3,
    SA_RIGHTBTN4,
    SA_RIGHTBTN5,
    SA_RIGHTBTN6,
    SA_QUICKSAVE,
    SA_SETUP,
    SA_HOME,
    SA_FULL,
};
enum{
    SA_TOPWIDGET = 0,
    SA_RIGNTWIDGET,
    SA_BUTTOMWIDGET,
    SA_LEFTWIDGETM,
    SA_CENTERWIDGET,
};
enum{
    SA_INFO_FREQ,
    SA_INFO_AMPT,
    SA_INFO_SWEEP,
    SA_INFO_BW,
    SA_INFO_TRIGGER,
    SA_INFO_TRACE,
    SA_INFO_MARKER,
    SA_INFO_MEASURE,
    SA_INFO_SYSTEM,
    SA_INFO_LIMIT,
};
enum{
    SA_INFO_LIMIT_NUM,
    SA_INFO_LIMIT_VALUE,
    SA_INFO_LIMIT_VIEW,
    SA_INFO_LIMIT_EDGE_VIEW,
    SA_INFO_LIMIT_EDGE_VALUE,
    SA_INFO_LIMIT_EDGE_TEST,
    SA_INFO_LIMIT_EDGE_TYPE,
};
enum
{
  SA_INFO_MARKER_INDEX,
  SA_INFO_MARKER_VIEW,
  SA_INFO_MARKER_VALUE,
};
enum{
    SA_INFO_FREQ_START,
    SA_INFO_FREQ_STOP,
    SA_INFO_FREQ_CENTER,
    SA_INFO_FREQ_SPAN,
    SA_INFO_FREQ_OFFSET,
    SA_INFO_CH_STANDARD,
};
enum{
    SA_INFO_BW_RBW_AUTO,
    SA_INFO_BW_RBW_VALUE,
    SA_INFO_BW_VBW_AUTO,
    SA_INFO_BW_VBW_VALUE,
    SA_INFO_BW_IF_OUTPUT,
};
enum{
    SA_INFO_TRIGGER_MODE,
};
enum{
    SA_INFO_TRACE_TYPE,
    SA_INFO_TRACE_AVE,
    SA_INFO_TRACE_VIEW,
    SA_INFO_TRACE_INDEX,
    SA_INFO_TRACE_AVE_TOGGLE,
    SA_INFO_TRACE_CURAVE,
    SA_INFO_TRACE_DETECTOR,
};
enum{
    SA_INFO_AMPT_PREAMP,
    SA_INFO_AMPT_ATTENTYPE,
    SA_INFO_AMPT_ATTEN,
    SA_INFO_AMPT_OFFSET,
    SA_INFO_AMPT_REF,
    SA_INFO_AMPT_UNIT,
    SA_INFO_AMPT_SCALEDIV,
    SA_INFO_AMPT_AUTOLIMIT
};
enum{
    SA_CDMA=0,
    SA_GSM,
    SA_LTE_FDD,
    SA_LTE_TDD,
    SA_TD_SCDMD,
    SA_WCDMA,
    SA_WIMAX,
};
enum{
    SA_UPLINK = 0,
    SA_DOWNLINK
};
enum{
    SA_DOWN = 0,
    SA_UP
};
enum{
    SA_TOP_LEFT = 0,
    SA_TOP_CENTER,
    SA_TOP_RIGHT,
    SA_BOTTOM_LEFT,
    SA_BOTTOM_CENTER,
    SA_BOTTOM_RIGHT,
    SA_TOP_LEFT_SEC,
    SA_TOP_RIGHT_SEC,
    SA_BOTTOM_LEFT_SEC,
    SA_BOTTOM_RIGHT_SEC,
};
enum{
    SA_INFO_SYSTEM_MODE = 0,
    SA_INFO_SYSTEM_FREQ_REF,
    SA_INFO_SYSTEM_SHIFT,
    SA_INFO_SYSTEM_LOCKSTATUS,
    SA_INFO_SYSTEM_DISPLAYMODE,
};
enum{
    SA_INFO_SWEEP_MODE = 0,
    SA_INFO_SWEEP_TIME ,
};
enum{
    SA_LOCAL = 0,
    SA_REMOTE ,
};
//Johnson 0315
enum{
    SA_MARKER_TABLE,
    SA_CHANNELPOWER_TABLE,
    SA_ACP_TABLE,
    SA_OCCUPIEDXDB_TABLE,
    SA_MULTIACP_TABLE,
    SA_SPECTRUM_EM_TABLE,
    SA_SPURIOUS_EM_TABLE,
};
const unsigned int SA_u32BWTable[] =
{
    5000000,3000000,1000000,300000,100000,
    30000,10000,3000,1000,
    300,100,30,10,3,1,
};

//struct
//{
//    {"CDMA",SA_CDMA}
//    {"GSM",SA_GSM}
//};

typedef struct
{
    const char *name;
    int  ChStep;
    int  index;
} __SA_ChStand__;
static const __SA_ChStand__ mChStand[7]=
{
    {"CDMA",CHSTEP_CDMA,SA_CDMA},
    {"GSM",CHSTEP_GSM,SA_GSM},
    {"LTE-A FDD",CHSTEP_LTE,SA_LTE_FDD},
    {"LTE-A TDD",CHSTEP_LTE,SA_LTE_TDD},
    {"TD-SCDMA",CHSTEP_TD_SCDMA,SA_TD_SCDMD},
    {"WCDMA",CHSTEP_WCDMA,SA_WCDMA},
    {"WIMAX",200000,SA_WIMAX},
};
#define SA_SPECEM_FREQ_CNT 6
#define SA_SPUREM_RANGE_CNT 20
#define SA_SPUREM_SPUR_CNT 10
typedef struct
{
    int rangeIndex;
    int xPtIndex;
    double freq;
    double value;
    int testValue;
} __SPUR_POINT__;

typedef struct
{
    double start;
    double  stop;
    double  rbw;
    double  vbw;
    double startAbsRef;
    double stopAbsRef;
    double startRelRef;
    double stopRelRef;
} __SPEC_EM__;
static const __SPEC_EM__ mSpecEM[SA_SPECEM_FREQ_CNT]=
{
    {2515000,2715000,30000,3000,-14,-14,99,99},
    {2715000,3515000,30000,3000,-14,-26,99,99},
    {3515000,4000000,30000,3000,-26,-26,99,99},
    {4000000,8000000,1000000,100000,-13,-13,99,99},
    {8000000,12500000,1000000,100000,-13,-13,99,99},
    {12500000,15000000,1000000,100000,-13,-13,99,99},
};

#define SPUR_EM_DATE_MAX 20
typedef struct
{
    int index;
    double  startFreq;
    double  stopFreq;
    double  RBW;
    double  VBW;
    double  SweepTime;
    double  startLimit;
    double  stopLimit;
    double  peakDefi;
    double  peakThreshold;
    double  Atten;
} __SPUR_EM__;
static const __SPUR_EM__ mSpurEM[SPUR_EM_DATE_MAX]=
{
    {1,1920000000,1980000000,300000,300000,22.14,-50,-50,6,-90,10},
    {2,1894000000,1920000000,100000,100000,84,-50,-50,6,-90,10},
    {3,2100000000,2102000000,10000,10000,1070,-50,-50,6,-90,10},
    {4,2175000000,2180000000,30000,30000,297.34,-50,-50,6,-90,10},
    {5,800000000,1000000000,1000000,1000000,5.07,-50,-50,6,-90,10},
    {6,800000000,1000000000,1000000,1000000,5.07,-50,-50,6,-90,10},
    {7,800000000,1000000000,1000000,1000000,5.07,-50,-50,6,-90,10},
    {8,800000000,1000000000,1000000,1000000,5.07,-50,-50,6,-90,10},
    {9,800000000,1000000000,1000000,1000000,5.07,-50,-50,6,-90,10},
    {10,800000000,1000000000,1000000,1000000,5.07,-50,-50,6,-90,10},
    {11,800000000,1000000000,1000000,1000000,5.07,-50,-50,6,-90,10},
    {12,800000000,1000000000,1000000,1000000,5.07,-50,-50,6,-90,10},
    {13,800000000,1000000000,1000000,1000000,5.07,-50,-50,6,-90,10},
    {14,800000000,1000000000,1000000,1000000,5.07,-50,-50,6,-90,10},
    {15,800000000,1000000000,1000000,1000000,5.07,-50,-50,6,-90,10},
    {16,800000000,1000000000,1000000,1000000,5.07,-50,-50,6,-90,10},
    {17,800000000,1000000000,1000000,1000000,5.07,-50,-50,6,-90,10},
    {18,800000000,1000000000,1000000,1000000,5.07,-50,-50,6,-90,10},
    {19,800000000,1000000000,1000000,1000000,5.07,-50,-50,6,-90,10},
    {20,800000000,1000000000,1000000,1000000,5.07,-50,-50,6,-90,10},
};
#define SA_ALLSET_COUNT 57
enum{
    SA_ALLSET_CENTERFREQ = 0,
    SA_ALLSET_STARTFREQ,
    SA_ALLSET_STOPFREQ,
    SA_ALLSET_FREQSTEP,
    SA_ALLSET_FREQOFFSET,
    SA_ALLSET_SPAN,
    SA_ALLSET_SPANFULL,
    SA_ALLSET_SPANZERO,
    SA_ALLSET_SPANLAST,
    SA_ALLSET_CHANNELSTD,
    SA_ALLSET_CHANNELNUM,
    SA_ALLSET_CHANNELSTEP,
    SA_ALLSET_CHANNELTYPE,

    SA_ALLSET_AUTOSCALE,
    SA_ALLSET_REFLEVEL,
    SA_ALLSET_DIVISION,
    SA_ALLSET_ATTEN,
    SA_ALLSET_ATTENVALUE,
    SA_ALLSET_PREAMP,
    SA_ALLSET_REFOFFSET,
    SA_ALLSET_UNIT,

    SA_ALLSET_AUTOSWEEPTIME,
    SA_ALLSET_SWEEPTIME,
    SA_ALLSET_MODE,
    SA_ALLSET_SWEEPONCE,

    SA_ALLSET_RBW,
    SA_ALLSET_AUTORBW,
    SA_ALLSET_VBW,
    SA_ALLSET_AUTOVBW,
    SA_ALLSET_VBW_RBW,

    SA_ALLSET_TRIGGER_SOURCE,
    SA_ALLSET_TRIGGER_VIEDO_LEVEL,
    SA_ALLSET_TRIGGER_VIEDO_SLOPE,
    SA_ALLSET_TRIGGER_VIEDO_DELAYON,
    SA_ALLSET_TRIGGER_VIEDO_DELAYTIME,
    SA_ALLSET_TRIGGER_EXTERNAL_LEVEL,
    SA_ALLSET_TRIGGER_EXTERNAL_SLOPE,
    SA_ALLSET_TRIGGER_EXTERNAL_DELAYON,
    SA_ALLSET_TRIGGER_EXTERNAL_DELAYTIME,
    SA_ALLSET_TRIGGER_PER_TIME,
    SA_ALLSET_TRIGGER_PER_DELAYON,
    SA_ALLSET_TRIGGER_PER_DELAYTIME,
    SA_ALLSET_TRIGGER_RFBURST_LEVEL,
    SA_ALLSET_TRIGGER_RFBURST_SLOPE,
    SA_ALLSET_TRIGGER_RFBURST_DELAYON,
    SA_ALLSET_TRIGGER_RFBURST_DELAYTIME,

    SA_ALLSET_TRACESELECT,
    SA_ALLSET_TRACEVIEW,
    SA_ALLSET_TRACEALLON,
    SA_ALLSET_TRACETYPE,
    SA_ALLSET_AVERAGE,
    SA_ALLSET_AVERAGEVALUE,
    SA_ALLSET_TRACEALLCLEAR,
    SA_ALLSET_DETECTORS,

    SA_ALLSET_MARKERSELECT,
    SA_ALLSET_MARKERVIEW,
    SA_ALLSET_MARKERALLON,
    SA_ALLSET_MARKERTYPE,
    SA_ALLSET_MARKERTO,
    SA_ALLSET_NOISEMARKER,
    SA_ALLSET_FREQCOUNT,

    SA_ALLSET_LIMITSELECT,
    SA_ALLSET_LIMIT,
    SA_ALLSET_LIMITEDGE,
    SA_ALLSET_LIMITEDGEVALUE,
    SA_ALLSET_LIMITTEST,
    SA_ALLSET_LIMITTYPE,
    SA_ALLSET_LIMITALLCLEAR,
};
enum {
    SA_AUTO_IFMODE = 0,
    SA_10M_IFMODE,
    SA_100M_IFMODE
};
enum {
    SA_EXT_GPS_REFINPUT = 0,
    SA_EXT_10M_REFINPUT = 1,
    SA_EXT_13M_REFINPUT = 2,
    SA_EXT_15M_REFINPUT = 3,
    SA_INT_10M_REFINPUT = 4
};
enum {
    SA_BRTLEVEL1 = 1,
    SA_BRTLEVEL2 = 2,
    SA_BRTLEVEL3 = 3,
    SA_BRTLEVEL4 = 4,
    SA_BRTLEVEL5 = 5
};
enum {
    SA_PRESET_PARA = 0,
    SA_LAST_PARA   = 1,
    SA_USER_PARA   = 2
};
enum{
    SA_FREQREF_INTERNAL  = 0,
    SA_FREQREF_EXTERNAL10,
    SA_FREQREF_EXTERNAL13,
    SA_FREQREF_EXTERNAL15,
    SA_FREQREF_GPS,
};
enum{
    SA_NEGATIVE = 0,
    SA_POSITIVE,
};

#define STEP_ATTEN 5000
#define STEP_PHASE 10

#define ZEROATTEN_MAX 65535
#define ZEROATTEN_MIIN 50000
#define ZEROPHASE_MAX 63

enum{
    SA_SPUREM_MEASURE = 0,
    SA_SPUREM_SETTABLE_FREQ,
    SA_SPUREM_SETTABLE_LIMIT,
};
enum{
    SA_SPUREM_AVE_EXP = 0,
    SA_SPUREM_AVE_REPEAT ,
};
enum
{
    SA_SPUREM_REPORT_ALL = 0,
    SA_SPUREM_REPORT_TEST ,
};
enum{
    SA_STATE = 0,
    SA_FILE,
};
static unsigned char Sa_GucRegularString[] = {'\\', '/', ':', '*', '?', '<', '>',
        '|', ';', '&', '`', '\'', '\"' };
#define SA_MODULE    0
#define START_FLAG   37
#define BW_MIN       2//4

static char* qssMode[3] = {"indoor","outdoor","night"};

/*******************Door Control Sweep***********************/
enum{
    SA_NONE_SOURCE = -1,
    SA_EXTERN_TRIGGER = 0,
    SA_RFBURST_TRIGGER,
    SA_PERIOD_TRIGGER
};
enum{
    SA_EDGE_MODE = 0,
    SA_LEVEL_MODE,
};
enum{
    SA_NEGATIVE_VALUE = 0,
    SA_POSITIVE_VALUE,
};
enum{
    SA_LO_DCSWEEPMODE = 0,
    SA_VEDIO_DCSWEEPMODE,
    SA_FFT_DCSWEEPMODE
};
enum{
    SA_NO_SYCHRNOSOURCE = 0,
    SA_EXTERNTRIGGER_SYCHRNOSOURCE,
    SA_RFBURST_SYCHRNOSOURCE
};
enum{
    SA_CLOSE_DCSWEEP = 0,
    SA_OPEN_DCSWEEP
};
enum{
    SA_CLOSE_PRVTSTATUS = 0,
    SA_OPEN_PRVTSTATUS
};
enum{
    SA_GATE_VIEW_CLOSE = 0,
    SA_GATE_VIEW_OPEN
};
/************************************************************/

#define GLOBAL_REPAINT_OPEN 1
#endif // DEFINE

