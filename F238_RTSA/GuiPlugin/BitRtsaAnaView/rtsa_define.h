/**************Copyright (c)**************************************
 **
 **               INNO Instrument(China) Co.,Ltd.
 **
 **------------File Info------------------------------------------
 **Class name:              define.h
 **Latest Version:          V1.0.0
 **Latest modified Date:
 **Created by:              Albert
 **Created date:            2018/12/12
 **Descriptions:            RTSA all define should define in this file
 **
 *****************************************************************/

#ifndef RTSA_DEFINE_H
#define RTSA_DEFINE_H
#include <QtGlobal>


//#define SPEC_FREQ_MIN  100000 // 100kHz
//#define SPEC_FREQ_MAX  8000000000LL // 8GHz


/************************************
 * here diff F238 / F238_SMART  / F238_PRO
 * *********************************/

//#define RTSA_F238

//#define RTSA_F238_SMART

#define RTSA_F239

// prepared for upgrade for rtsa  fpga overlap
#define RTSA_OLD_ACQTIME

//by Tony 0921
#define RTSA_BITVIEWNUM 4

//Johnson 0702
#define RTSA_CLOCKWISE     0
#define RTSA_ANTICLOCKWISE 1

//by Steve,0228
#define RTSA_SPEC_FREQ_MIN  0 // 9kHz
//#define SPEC_FREQ_MAX  32000000000LL // 32GHz
#ifdef RTSA_F238
#define RTSA_SPEC_FREQ_MAX 43050000000LL  //43GHz  //Tony 0906
#endif

#ifdef RTSA_F238_SMART
#define RTSA_SPEC_FREQ_MAX 15050000000LL  //43GHz  //Tony 0906
#endif

#ifdef RTSA_F239
#define RTSA_SPEC_FREQ_MAX 43050000000LL  //43GHz  //Tony 0906
#endif
#define RTSA_SPEC_AMPTD_MIN  -180. // -140. dBm  //Tony 1024 -180 dBm
#define RTSA_SPEC_AMPTD_MAX  30.   // 30 dBm

#define RTSA_SPEC_REF_OFFSET_MIN  -100.
#define RTSA_SPEC_REF_OFFSET_MAX   100.
#define RTSA_LIMIT_EDGE_MAX 40.
//Johnson 0702
#define RTSA_CLOCKWISE     0
#define RTSA_ANTICLOCKWISE 1

#define RTSA_COLORLEVEL    200
#define RTSA_DENSITY_MAX   0.1

#define RTSA_S      1000000       // 1 s   time/1000000
#define RTSA_MS     1000          // 1 ms  time/1000
#define RTSA_US     1             // 1 us  reference
#define RTSA_NS     1000          // 1 s   time*1000

#define RTSA_GHZ      1000000000    // 1GHz
#define RTSA_MHZ      1000000       // 1MHz
#define RTSA_KHZ      1000          // 1kHz
#define RTSA_HZ       1             // 1Hz

#define RTSA_mGHz     *1000000000    // 1GHz
#define RTSA_mMHz     *1000000       // 1MHz
#define RTSA_mkHz      *1000          // 1kHz
#define RTSA_mHz        *1             // 1Hz

#define RTSA_RVM						(10)	// RBW/VBW Multifly

#define RTSA_dBuVFix        107.
#define RTSA_dBmVFix       47.
#define RTSA_dBVFix       -13.


//Tony 0911
#define RTSA_ACQ_MAX_TIME    1000000000
#define RTSA_ACQ_MIN_TIME    40000

#define RTSA_REFRESH_DEFAULT_TIME 60000 //Albert 19/05/28
#define RTSA_ACQ_DEFAULT_TIME 70000 //Tony 0912
#define RTSA_PERSISTENCE_TIME 100000
//Tony 0830
#if 0
#define ARRAY_SIZE          6
#else
#define RTSA_ARRAY_SIZE          7
#define RTSA_COMPARE_SIZE      5
#endif

#define RTSA_MARKER_TOTAL_CNT 6

#define RTSA_LIMIT_TOTAL  801    // Limit Line Edit  Total Count

#define RTSA_AMPTD_LBL_START_X   15
#define RTSA_GRID_START_X        120   // 117


#define RTSA_GRID_START_Y        127
#define RTSA_GRID_WIDTH          740 //731
#define RTSA_GRID_HEIGHT         201 //542

//Tony 0910
#define RTSA_DOUBLEVIEW_GRID_START_Y1  127
#define RTSA_DOUBLEVIEW_GRID_START_Y2  217

#define RTSA_SLEEPTIME 20000


//#define GRID_HSTEP          74
//#define GRID_VSTEP          56
#define RTSA_GRID_NUM_X_TICKS    10  // 0기반의 값. 실제로 11개.
#define RTSA_GRID_NUM_Y_TICKS    10

#define RTSA_NUM_TRACE           6

#define RTSA_NUM_SWEEP_POINT    801

#define RTSA_NORMAL_SPAN         0
#define RTSA_FULL_SPAN           1
#define RTSA_ZERO_SPAN           2

#define RTSA_POINT_501           0
#define RTSA_POINT_1001          1
#define RTSA_POINT_2001          2
#define RTSA_POINT_3001          3


#define RTSA_OFF  0
#define RTSA_ON   1

//Display --Density --Persistence Time //Tony 0903
#define RTSA_INFINITE 1
#define RTSA_FINITE 0

#define RTSA_PASS 1
#define RTSA_FAIL  0

// Trace Use  --- Start
#define RTSA_TR1                  0
#define RTSA_TR2                  1
#define RTSA_TR3                  2
#define RTSA_TR4                  3
#define RTSA_TR5                  4
#define RTSA_TR6                  5
#define RTSA_TRACE_ALL            6
#define RTSA_TR_AVERAGE   20


// Marker Use  -- Start
#define RTSA_MARKER_FONT_HEIGHT  15

#define RTSA_M1                  0
#define RTSA_M2                  1
#define RTSA_M3                  2
#define RTSA_M4                  3
#define RTSA_M5                  4
#define RTSA_M6                  5

#define RTSA_REF                0
#define RTSA_DELTA            1
#define RTSA_DELTA_PAIR            2

#define RTSA_MKR_TABLE     0
#define RTSA_MKR_ONLY     1
#define RTSA_MKR_OFF        2

//Tony 1207 DPX buffer size
#define RTSA_DPXWIDTH   801
#define RTSA_DPXHEIGHT  201
#define RTSA_DPXSIZE    644004
// Limit
#define   RTSA_UPPER        1
#define   RTSA_LOWER       2
#define   RTSA_LIMIT_OFF   0

//Johnson 0823
#define   RTSA_LIMIT1      0
#define   RTSA_LIMIT2      1
#define   RTSA_LIMIT3      2
#define   RTSA_LIMIT4      3
#define   RTSA_LIMIT5      4
#define   RTSA_LIMIT6      5
#define   RTSA_LIMIT7      6
#define   RTSA_LIMIT8      7


//#define RTSA_PRESET_FACTORY      0
//#define RTSA_PRESET_MARKER       1
//#define RTSA_PRESET_LIMIT            2
//Albert 1123
//#define RTSA_PRESET_MEMOERY_LOW  3
//#define RTSA_FILE_EXIST_ALREADY  4
#define RTSA_LIMIT_TOTAL_CNT 6

// RBW, VBW
//#define RTSA_RBW						300
//#define RTSA_VBW						301

#define RTSA_NUM_RBW_VBW_MAN_SPAN_BOUNDARY        12
#define RTSA_NUM_RBW_VBW_MAN_VARIETY                        6

#define RTSA_NUM_RBW_VBW_AUTO_SPAN_BOUNDARY         7
#define RTSA_NUM_RBW_VBW_AUTO_VARIETY                        7

//#define RTSA_ERROR_MIN_BW			0				// 0 Hz (사용 불가능)
#define RTSA_ERROR_MAX_BW			100000000		// 10 MHz (사용 불가능)

//#define RTSA_VALID_BW				1000
//#define RTSA_INVALID_BW				1001

//Albert 19/01/28
#define RTSA_DIGITAL_DIALOG_WIDTH   252
#define RTSA_DIGITAL_DIALOG_HEIGHT  646

//Albert 19/05/28
#define RTSA_SCREEN_CAPTURE_STARTX     0
#define RTSA_SCREEN_CAPTURE_STARTY     0
#define RTSA_SCREEN_CAPTURE_WIDTH      1280
#define RTSA_SCREEN_CAPTURE_HEIGHT     800
static unsigned char RtSa_GucRegularString[] = {'\\', '/', ':', '*', '?', '<', '>',
        '|', ';', '&', '`', '\'', '\"' };

#define RTSA_MODULE    1
#define RTSA_START_FLAG   37

#define RTSA_COMP_TEMPDATA  0     //Compensation temp data 19/06/28

#define RTSA_ACQTIME_MAX    23000000

#define RTSA_SPAN_MIN   500

#define RTSA_FILEHEADER_STATE 0x52534101
#define RTSA_FILEHEADER_STATE_DATA 0x52534102

//Tony 0907
#define RTSA_SPAN_INTERVAL_NUMBER    19
#define RTSA_RBW_NUMBER    7
const unsigned long long RTSA_SPAN_STEP_VALUE[RTSA_SPAN_INTERVAL_NUMBER] = 		// 100HZ,200HZ,500HZ,1KHZ,2KHZ,5KHZ,10KHZ,20KHZ,50KHZ,100KHZ,200KHZ,1MHZ,2MHZ,5MHZ,10MHZ,20MHZ,50MHZ
    {100, 200, 500,1000,2000,5000,10000, 20000, 50000, 100000, 200000, 500000,1000000, 2000000, 5000000,10000000, 20000000, 50000000,100000000};

// 십진수 40억 표현에 LL을 안 붙히면 warning이 뜬다.   //needed changed by Steve,rbw accolated with band is 100 bei
//const u64 u64RbwVbwAutoSpanBoundary[NUM_RBW_VBW_AUTO_SPAN_BOUNDARY] =
const unsigned long long RTSA_u64RbwVbwAutoSpanBoundary[RTSA_NUM_RBW_VBW_AUTO_SPAN_BOUNDARY] =
    {200000, 1000000, 2000000, 5000000, 50000000, 500000000, 8000000000LL};   // (60 kHz) ~ 200 kHz ~ 4400 MHz

//const u32 u32SpanRbwVbwAutoTable[NUM_RBW_VBW_AUTO_VARIETY] =
//const unsigned int RTSA_u32SpanRbwVbwAutoTable[RTSA_NUM_RBW_VBW_AUTO_VARIETY] =
//    {10000, 30000, 100000, 300000, 1000000, 3000000, 10000000};                 // 1 kHz ~ 1 MHz


// RBW/VBW 값의 종류가 변동되는 Span 경계값. - Manual 상태일 때.
//const u64 u64RbwVbwManSpanBoundary[NUM_RBW_VBW_MAN_SPAN_BOUNDARY] = 		// 100 kHz ~
//const unsigned long long RTSA_u64RbwVbwManSpanBoundary[RTSA_NUM_RBW_VBW_MAN_SPAN_BOUNDARY] = 		// 100 kHz ~
//    {80000, 150000, 511000, 2000000, 4000000, 5000000, 29000000, 100000000, 190000000, 250000000, 500000000, 4000000000LL};  // ~ 4400MHz


// Span에 따른 RBW값 종류를 나열한 Table..
//const u32 u32SpanRbwManTable[NUM_RBW_VBW_MAN_SPAN_BOUNDARY][NUM_RBW_VBW_MAN_VARIETY] =
//const unsigned int RTSA_u32SpanRbwManTable[RTSA_NUM_RBW_VBW_MAN_SPAN_BOUNDARY][RTSA_NUM_RBW_VBW_MAN_VARIETY] =
//{
//    {0, 0, 0, 0, 10000, RTSA_ERROR_MAX_BW},                      // 60.000 KHz ~ 99.999 KHz
//    {0, 0, 0, 10000, 30000, RTSA_ERROR_MAX_BW},                  // 100.000 KHz ~ 199.999 KHz
//    {0, 0, 10000, 30000, 100000, RTSA_ERROR_MAX_BW},             // 200.000 KHz ~ 599.999 KHz
//    {0, 10000, 30000, 100000, 300000, RTSA_ERROR_MAX_BW},        // 600.000 KHz ~ 2.999999 MHz
//    {0, 0, 30000, 100000, 300000, RTSA_ERROR_MAX_BW},			// 3.000000 MHz ~ 4.999999 MHz
//    {0, 30000, 100000, 300000, 1000000, RTSA_ERROR_MAX_BW},	    // 5.000000 MHz ~ 5.999999 MHz
//    {0, 0, 100000, 300000, 1000000, RTSA_ERROR_MAX_BW},          // 6.000000 MHz ~ 29.999999 KHz
//    {0, 100000, 300000, 1000000, 3000000, RTSA_ERROR_MAX_BW},    // 30.000000 MHz ~ 109.999999 MHz
//    {0, 0, 300000, 1000000, 3000000, RTSA_ERROR_MAX_BW},         // 110.000000 MHz ~ 199.999999 MHz
//    {0, 300000, 1000000, 3000000, 10000000, RTSA_ERROR_MAX_BW},  // 200.000000 MHz ~ 255.999999 MHz
//    {0, 0, 1000000, 3000000, 10000000, RTSA_ERROR_MAX_BW},       // 256.000000 MHz ~ 511.999999 MHz
//    {0, 0, 0, 3000000, 10000000, RTSA_ERROR_MAX_BW}              // 512.000000 MHz ~ 4.000000000 GHz
//};

//Johnson 0803 work mode
enum{
    RTSA_SPAN_MODE    = 1,
    RTSA_MEASURE_MODE =2
};

// MENU의 선택
enum {
    RTSA_MENU_SPECTRUM_ANALYZER   = 1,
    RTSA_MENU_POWER_SENSOR           = 2,
    RTSA_MENU_SIGNAL_ANALYZER        = 3
};

//Modified by Tony in 0830
#if 0
// Primary  Key    //Johnson 0718
enum {
    MEASUREMENT = 1,
    FREQUENCY   = 2,
    BW           = 3,
    AMPLITUDE   = 4,
    SWEEP        = 5,
    TRACE        = 6,
    MARKER       = 7,
    PEAK         = 8,
    LIMIT        = 9,
    LOAD         = 10,
    SAVE         = 11,
    SYSTEM       = 12,
    PRESET       = 13,
    POWERSENSOR  = 14,
    SPAN         = 15
};
#else
enum {
    RTSA_FREQUENCY   = 1,
    RTSA_AMPLITUDE   = 2,
    RTSA_BW          = 3,
    RTSA_DISPLAY     = 4,
    RTSA_MEASUREMENT = 5,
    RTSA_TRACE       = 6,
    RTSA_MARKER       = 7,
    RTSA_PEAK        = 8,
    RTSA_SAVE        = 9,
    RTSA_LOAD        = 10,
    RTSA_SYSTEM      = 11,
    RTSA_SPAN        = 12,
    RTSA_TRIGGER     = 13,
};
#endif

// Measurement
enum {
    RTSA_MEAS_OFF              = 0,
    RTSA_CHANNEL_POWER   = 1,
    RTSA_ACP                        = 2,
    RTSA_DEMODULATION     = 3,
};

// Demodulation
enum {
    RTSA_AM              = 0,
    RTSA_FM               = 1,
    RTSA_NFM             = 2
};


//// ZeroSpanMode
//enum {
//    RTSA_AMPLITUDE              = 0,
//    RTSA_FREQUENCY              = 1,
//    RTSA_PHASE                  = 2
//};




// SA Input Type Define
enum {
    RTSA_SHIFT_ENABLE                           = -1,
    RTSA_NOT_USE                                         = 0,
    RTSA_INPUT_MEASUREMENT                      = 1,
    RTSA_INPUT_FREQ_CENTER                      = 2,
    RTSA_INPUT_FREQ_START                        = 3,
    RTSA_INPUT_FREQ_STOP                         = 4,
    RTSA_INPUT_FREQ_CF                             = 5,
    RTSA_INPUT_REF_LEVEL                           = 6,
    RTSA_INPUT_ATTEN                                = 7,
    RTSA_INPUT_SCALEDIV                            = 8,
    RTSA_INPUT_PREAMP                              = 9,
    RTSA_INPUT_REF_OFFSET                        = 10,
    RTSA_INPUT_FREQ_SPAN                        = 11,
    RTSA_INPUT_MANUAL_RBW                    = 12,
    RTSA_INPUT_MANUAL_VBW                     = 13,
    RTSA_INPUT_AUTO_RBW                           = 14,
    RTSA_INPUT_AUTO_VBW                            = 15,
    RTSA_INPUT_SWEEP_TIME                          = 16,
    RTSA_INPUT_SWEEP_TYPE                         = 17,
    RTSA_INPUT_OVERLAP                              = 18,

    RTSA_INPUT_TRACE_AVERAGE      ,
    RTSA_INPUT_AVERAGE_COUNT      ,
    RTSA_INPUT_MARKER_EDIT ,
    RTSA_INPUT_DELTA_MARKER_EDIT  ,

    RTSA_INPUT_CHANNEL_BANDWIDTH  ,
    RTSA_INPUT_CHANNEL_SPACING    ,

    RTSA_INPUT_POWERSENSOR_FREQ   ,
    RTSA_INPUT_POWERSENSOR_EXT_OFFSET   ,

    RTSA_ENTRY_HIDE                     ,
    RTSA_LIMIT_EDGE                     ,  //Johnson 0824

    RTSA_INPUT_PERSISTENCE_TIME         ,  //Tony 0905
    RTSA_INPUT_HIGHEST_DENSITY          ,  //Tony 0905
    RTSA_INPUT_LOWEST_DENSITY           ,  //Tony 0905
    RTSA_INPUT_CURVE                    ,  //Tony 0905
    RTSA_INPUT_ACQ_TIME                 ,  //Tony 0905
    RTSA_INPUT_MARGIN                   ,  //Tony 0905
    RTSA_INPUT_DELTA                    ,    //Tony 0905
    RTSA_INPUT_VOLUME_NUM               ,  //Albert 1108

    RTSA_INPUT_FREQ_OFFSET              ,
    RTSA_INPUT_FREQ_CHANNEL_STANDARD    ,
    RTSA_INPUT_FREQ_CHANNEL_NUM         ,
    RTSA_INPUT_FREQ_CHANNEL_STEP        ,

    RTSA_INPUT_LIMIT_FREQ,
    RTSA_INPUT_LIMIT_AMPT,
    RTSA_INPUT_LIMIT_SELECT_INDEX,

    RTSA_INPUT_FMT_FREQ,
    RTSA_INPUT_FMT_AMPT,
    RTSA_INPUT_FMT_SELECT_INDEX,

    RTSA_INPUT_TRIGGER_DELAY_VALUE,
    RTSA_INPUT_TRIGGER_LEVEL,
    RTSA_INPUT_TRIGGER_PERTIMER,
    RTSA_INPUT_TRIGGER_HOLDTIME,

    RTSA_ALLSET_INPUT_UNIT,
    RTSA_ALLSET_INPUT_RBW,
    RTSA_ALLSET_INPUT_FFTWINDOW,
    RTSA_ALLSET_INPUT_TRIGGER_MODE,
    RTSA_ALLSET_INPUT_TRACE_SEL,
    RTSA_ALLSET_INPUT_TRACE_TYPE,
    RTSA_ALLSET_INPUT_DETECTOR,
    RTSA_ALLSET_INPUT_MARKER_SEL,
    RTSA_ALLSET_INPUT_MARKER_TO,
    RTSA_ALLSET_INPUT_LIMIT_SEL,

    RTSA_SPECTROGTAM_CURSOR_INDEX,
    RTSA_END,

};

// Sweep - Detector
enum {
    RTSA_MAX                       = 0,
    RTSA_MIN                        = 1,
    RTSA_SAMPLE                  = 2,
    RTSA_AVERAGE_POWER   = 3,
    RTSA_AVERAGE_VOLTAGE = 4
};

// Sweep - Trigger.
enum {
    RTSA_TRIGGER_FREE_RUN = 0,
    RTSA_TRIGGER_VIDEO,
    RTSA_TRIGGER_EXTERNAL,
    RTSA_TRIGGER_PERIODIC_TIMER,
    RTSA_TRIGGER_RF_BURST,
    RTSA_TRIGGER_FMTMASK,
//    RTSA_TRIGGER_VIDEO,
};
enum {
    RTSA_RAISING_SLOPE = 0,
    RTSA_FALLING_SLOPE,
};
//enum {
//    RTSA_FREE_RUN              = 0,
//    RTSA_EXT_RISE                = 1,
//    RTSA_EXT_FALL                 = 2,
//    RTSA_TRIGGER_DELAY      = 3,
//    RTSA_TRIGGER_FMTMASK      = 4
//};



// Sweep Graph의 Mouse Click 동작
enum {
    RTSA_NOT_MOUSE_CLICK    = 0,
    RTSA_MOUSE_ACTION         = 1
};

//Sweep Type
enum {
    RTSA_CONT                       = 0,
    RTSA_SINGLE                     = 1,
    RTSA_SWEEP_OFF                  = 2
};
//Johnson Add
//Atten Auto Manul
enum{
    RTSA_AUTO           = 1,
    RTSA_MANUAL          = 0
};
//Tony 0904
//Amplitude Unit
enum {
    RTSA_DBM   = 0,
    RTSA_DBV   = 1,
    RTSA_DBMV  = 2,
    RTSA_DBUV  = 3,
    RTSA_VOLT  = 4,
    RTSA_WATTS = 5
};
//Tony 0905
enum {
    RTSA_RECTANGULAR  = 0,
    RTSA_HANNING   = 1,
    RTSA_GAUSIAN   = 2,
    RTSA_BLACKMANHARRIS =3,
    RTSA_KAISER    = 4,
    RTSA_FLATTOP   = 5
};


//RBW value
#if 0
const unsigned long long RTSA_RbwHanningList[19][6]=
{
    {1,2,3,4,5,6},
    {7,8,9,10,11,12},
    {13,14,15,16,17,18},
    {19,20,21,22,23,24},
    {25,26,27,28,29,30},
    {31,32,33,34,35,36},
    {37,38,39,40,41,42},
    {43,44,45,46,47,48},
    {49,50,51,52,53,54},
    {55,56,57,58,59,60},
    {61,62,63,64,65,66},
    {13,14,15,16,17,18},
    {13,14,15,16,17,18},
    {13,14,15,16,17,18},
    {13,14,15,16,17,18},
    {13,14,15,16,17,18}
};
const unsigned long long RTSA_RbwFlattopList[19][6]=
{
    {1,2,3,4,5,6},
    {17,8,9,10,11,12},
    {113,14,15,16,17,18},
    {119,20,21,22,23,24},
    {125,26,27,28,29,30},
    {311,32,33,34,35,36},
    {317,38,39,40,41,42},
    {413,44,45,46,47,48},
    {419,50,51,52,53,54},
    {515,56,57,58,59,60},
    {611,62,63,64,65,66},
    {131,14,15,16,17,18},
    {113,14,15,16,17,18},
    {113,14,15,16,17,18},
    {113,14,15,16,17,18},
    {111,14,15,16,17,18}
};
const unsigned long long RTSA_RbwGausianList[19][6]=
{
    {1,2,3,4,5,6},
    {71,8,9,10,11,12},
    {113,14,15,16,17,18},
    {119,20,21,22,23,24},
    {3225,26,27,28,29,30},
    {3321,32,33,34,35,36},
    {3317,38,39,40,41,42},
    {413,44,45,46,47,48},
    {4139,50,51,52,53,54},
    {5135,56,57,58,59,60},
    {61231,62,63,64,65,66},
    {1123,14,15,16,17,18},
    {1123,14,15,16,17,18},
    {1123,14,15,16,17,18},
    {11233,14,15,16,17,18},
    {11233,14,15,16,17,18}
};
const unsigned long long RTSA_RbwRectangularList[19][6]=
{
    {1,2,3,4,5,6},
    {7,8,9,10,11,12},
    {13,14,15,16,17,18},
    {19,20,21,22,23,24},
    {25,26,27,28,29,30},
    {31,32,33,34,35,36},
    {37,38,39,40,41,42},
    {43,44,45,46,47,48},
    {49,50,51,52,53,54},
    {55,56,57,58,59,60},
    {61,62,63,64,65,66},
    {13,14,15,16,17,18},
    {13,14,15,16,17,18},
    {13,14,15,16,17,18},
    {13,14,15,16,17,18},
    {13,14,15,16,17,18}
};
const unsigned long long RTSA_RbwKaiserList[19][6]=
{
    {1,2,3,4,5,6},
    {7,8,9,10,11,12},
    {13,14,15,16,17,18},
    {19,20,21,22,23,24},
    {25,26,27,28,29,30},
    {31,32,33,34,35,36},
    {37,38,39,40,41,42},
    {43,44,45,46,47,48},
    {49,50,51,52,53,54},
    {55,56,57,58,59,60},
    {61,62,63,64,65,66},
    {13,14,15,16,17,18},
    {13,14,15,16,17,18},
    {13,14,15,16,17,18},
    {13,14,15,16,17,18},
    {13,14,15,16,17,18}
};
const unsigned long long RTSA_RbwBlackmanHarrisList[19][6]=
{
    {1,2,3,4,5,6},
    {7,8,9,10,11,12},
    {133,14,15,16,17,18},
    {1359,20,21,22,23,24},
    {255,26,27,28,29,30},
    {2331,32,33,34,35,36},
    {3127,38,39,40,41,42},
    {4123,44,45,46,47,48},
    {419,50,51,52,53,54},
    {51355,56,57,58,59,60},
    {6231,62,63,64,65,66},
    {112353,14,15,16,17,18},
    {1513,14,15,16,17,18},
    {14123,14,15,16,17,18},
    {153,14,15,16,17,18},
    {11233,14,15,16,17,18}
};
#endif
/**
* @brief RTSA_RbwManualList[A][B][C]
* @param A means FFT Window index; B means Span index; C means RBW index
* @Author Albert
* @date 2019-04-26
*/
const qreal RTSA_RbwManualList[][RTSA_SPAN_INTERVAL_NUMBER][RTSA_RBW_NUMBER]=
{
    // RBW Value                                          //SPAN
    // Rectangular
    0,0,0,0,0,0,0,                                        // 100Hz
    0,0,0,0,0,0,0,                                        // 200Hz
    26,13,6,3,1.6,0.8,0.4,                                // 500Hz
    51,25,13,6,3,2,0.8,                                   // 1kHz
    102,51,26,13,6,3,2,                                   // 2kHz
    255,127,64,32,16,8,4,                                 // 5kHz
    511,254,128,65,33,17,8,                               // 10kHz
    1022,509,257,131,65,34,16,                            // 20kHz
    2554,1271,641,326,163,84,39,                          // 50kHz
    5108,2543,1283,653,326,169,79,                        // 100kHz
    10216,5086,2565,1305,653,337,157,                     // 200kHz
    25540,12714,6413,3262,1631,843,394,                   // 500kHz
    51081,25429,12827,6525,3263,1687,787,                 // 1MHz
    102161,50858,25654,13050,65250,3373,1574,             // 2MHz
    255403,127144,64134,32625,16312,8433,3935,            // 5MHz
    510806,254288,128268,65249,32625,16865,7871,          // 10MHz
    1277015,635719,320670,163123,81562,42163,19676,       // 20MHz
    2554030,1271439,641341,326246,163123,84326,39352,     // 50MHz
    5108060,2542878,1282683,652493,326247,168653,78705,   // 100MHz

    //hanning
    0,0,0,0,0,0,0,                                                      // 100Hz
    0,0,0,0,0,0,0,                                                      // 200Hz
    41,21,10,5,2.6,1.3,0.6,
    83,41,21,10,5,2.6,1.3,
    166,83,41,21,10,5,2.6,
    414,207,104,52,26,13,6,
    828,414,207,103,52,26,13,
    1656,828,414,207,104,52,26,
    4140,2067,1035,517,259,129,65,
    8280,4140,2070,1035,518,259,129,
    16560,8280,4140,2070,1035,518,259,
    41400,20700,10350,5175,2588,1294,647,
    82800,41400,20700,10350,5176,2588,1294,
    165600,82800,41400,20699,10351,5176,2588,
    414001,207000,103500,51748,25879,12939,6470,
    828002,413999,207001,103496,51757,25879,12939,
    2070006,1034998,517501,258739,129393,64696,32348,
    4140012,2069997,1035003,517478,258785,129393,64696,
    8280023,4139993,2070006,1034957,517571,258785,129393,

    //Gausian
    0,0,0,0,0,0,0,                                                      // 100Hz
    0,0,0,0,0,0,0,                                                      // 200Hz
    55,27,13,6.7,3.3,1.7,0.8,
    110,54,27,13,7,3.3,1.5,
    220,108,54,27,13,6.7,3.1,
    551,271,134,67,33,17,7.6,
    1102,542,269,134,67,33,15,
    2205,1085,538,268,134,67,30,
    5512,2711,1344,669,335,167,76,
    11025,5423,2689,1339,669,335,152,
    22050,10845,5377,2677,1339,669,304,
    55125,27113,13443,6694,3347,1674,759,
    110249,54225,26887,13387,6695,3347,1519,
    220498,108450,53774,26774,13389,6695,3038,
    551246,271126,134434,66936,33473,16736,7594,
    1102492,542251,268868,133872,66945,33473,15188,
    2756229,1355628,672169,334679,167363,83681,37970,
    5512458,2711255,1344338,669358,334725,167363,75940,
    11024916,5422510,2688676,1338716,669450,334725,151880,

    //blackmanharris
    0,0,0,0,0,0,0,                                                      // 100Hz
    0,0,0,0,0,0,0,                                                      // 200Hz
    56,27,13,6,3,1.7,0.8,
    112,55,27,13,6,3,1,
    225,111,54,27,13,6,3,
    563,277,137,68,34,17,8,
    1127,555,274,137,68,34,16,
    2254,1111,549,274,137,68,33,
    5637,2779,1372,686,343,171,84,
    11273,5558,2745,1372,686,343,168,
    22547,11116,5490,2745,1372,686,337,
    56369,27790,13726,6863,3431,1716,844,
    112739,55581,27452,13726,6862,3432,1688,
    225478,111163,54905,27452,13724,6864,3376,
    563696,277908,137263,68631,34311,17160,8441,
    1127393,555817,274526,137263,68622,34320,16883,
    2818483,1389542,686315,343157,171555,85801,42209,
    5636966,2779084,1372631,686315,343111,171602,84418,
    11273932,5558169,2745262,1372631,686223,343203,168837,

    //Kaiser
    0,0,0,0,0,0,0,                                         // 100Hz
    0,0,0,0,0,0,0,                                         // 200Hz
    65,31,16,8,4,2,1,
    130,62,32,16,8,3.9,2,
    259,123,63,32,16,8,4,
    648,308,158,79,39,20,10,
    1296,617,315,158,79,40,20,
    2592,1234,630,315,157,79,39,
    6480,3084,1575,788,394,197,98,
    12960,6169,3150,1575,787,394,197,
    25920,12337,6300,3150,1575,787,394,
    64800,30843,15750,7875,3937,1969,984,
    129600,61686,31500,15750,7874,3937,1969,
    259200,123372,63001,31500,15748,7874,3937,
    648000,308430,157501,78751,39371,19685,9843,
    1296000,616860,315003,157501,78742,39371,19685,
    3240000,1542150,787507,393754,196854,98427,49213,
    6480000,3084300,1575014,787507,393708,196854,98427,
    12960000,6168601,3150029,1575014,787415,393708,196854,

    //flattop
    0,0,0,0,0,0,0,                                                      // 100Hz
    0,0,0,0,0,0,0,                                                      // 200Hz
    110,54,27,13,6,3.4,1.7,
    221,108,54,26,13,6,3,
    442,217,108,53,26,13,6,
    1106,544,270,133,66,33,16,
    2212,1089,540,267,133,67,33,
    4424,2178,1080,535,267,135,66,
    11060,5445,2700,1338,669,337,167,
    22120,10891,5400,2677,1338,675,334,
    44240,21782,10801,5355,2677,1350,669,
    110601,54456,27002,13389,6694,3374,1673,
    221202,108912,54005,26778,13389,6749,3347,
    442404,217825,108011,53556,26778,13499,6694,
    1106012,544564,270028,133890,66945,33749,16736,
    2212024,1089128,540057,267780,133890,67498,33472,
    5530060,2722821,1350144,669450,334725,168745,83681,
    11060121,5445642,2700288,1338900,669450,337490,167362,
    22120243,10891284,5400576,2677801,1338900,674979,334725
};
/**
* @brief 100% POI List
* @param (us)
* @Author Albert
* 当2次FFT交叠后不出现GAP空隙的情况下，
* （2 * 窗长 - 交叠点数 - 1）/ fs    或者使用R&S提供的公式（2 - 重叠率）* 窗长 / fs；
* 当2次FFT交叠后出现GAP空隙的情况下，最短信号持续时间：（窗长 + FFT帧长 - 交叠点数 - 1）/fs
* 或者使用R&S提供的公式（1 / fFFT）+ 窗长 / fs，信号错过或者丢失的时间：（FFT帧长 - 窗长 - 交叠点数）/fs
* 或者使用R&S提供的公式（1 / fFFT）- 窗长 / fs。
* @date 2019-05-28
* @date 2019-12-16 小扫宽下通过改变交叠帧数，提高中断上报速度。POI的指标也得到改善
*/
#ifdef RTSA_OLD_ACQTIME
const qreal RTSA_POIList[RTSA_SPAN_INTERVAL_NUMBER][RTSA_RBW_NUMBER]=
{
    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,
    775463.0,810186.0,879630.0,1019000.0,1297000.0,1856000.0,2978000.0,
    387732.0,405093.0,439815.0,509260.0,648149.0,927780.0,1489000.0,
    193866.0,202547.0,219908.0,254630.0,324075.0,463890.0,744450.0,
    77547.0,81019.0,87963.0,101852.0,129630.0,185560.0,297780.0,
    38774.0,40510.0,43982.0,50926.0,64815.0,92780.0,148890.0,
    19387.0,20255.0,21991.0,25463.0,32408.0,46390.0,74450.0,
    7755.0,8102.0,8797.0,10186.0,12963.0,18560.0,29780.0,
    3878.0,4051.0,4399.0,5093.0,6482.0,9280.0,14890.0,
    1939.0,2026.0,2199.0,2547.0,3241.0,4640.0,7450.0,
    775.47,810.19,879.63,1019.0,1297.0,1860.0,3720.0,
    387.74,405.10,439.82,509.26,648.15,927.78,1860.0,
    193.87,202.55,219.91,254.63,324.08,463.89,927.78,
    77.55,81.02,87.97,101.86,129.63,185.56,296.23,
    38.78,40.51,43.99,50.93,64.82,92.78,148.12,
    15.51,16.21,17.60,20.38,25.93,37.12,59.25,
    7.76,8.11,8.80,10.19,12.97,18.56,29.63,
    3.88,4.05,4.40,5.09,6.49,9.27,14.82,
};
#else
const qreal RTSA_POIList[RTSA_SPAN_INTERVAL_NUMBER][RTSA_RBW_NUMBER]=
{
    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,
    // change parts
    34892.0,69784.0,139578.0,279135.0,558269.0,1117000.0,2234000.0,
    17459.0,34892.0,69784.0,139568.0,279135.0,558270.0,1117000.0,
    8723.0,17446.0,34892.0,69784.0,139568.0,279140.0,558270.0,
    3490.0,6976.0,13957.0,27914.0,55827.0,111660.0,223310.0,
    1745.0,3490.0,6979.0,13957.0,27914.0,55830.0,111660.0,
    872.30,1745.0,3490.0,6979.0,13957.0,27920.0,55830.0,
    348.92,697.84,1396.0,2792.0,5583.0,11170.0,22340.0,
    174.46,348.92,697.84,1396.0,2792.0,5590.0,11170.0,
    87.23,174.46,348.92,697.84,1396.0,2800.0,5590.0,
    34.90,69.79,139.57,279.14,558.27,1120.0,2230.0,
    17.45,34.90,69.79,139.57,279.14,558.27,1120.0,
    8.73,17.45,34.90,69.79,139.57,279.14,557.80,
    // no-change parts
    77.55,81.02,87.97,101.86,129.63,185.56,296.23,
    38.78,40.51,43.99,50.93,64.82,92.78,148.12,
    15.51,16.21,17.60,20.38,25.93,37.12,59.25,
    7.76,8.11,8.80,10.19,12.97,18.56,29.63,
    3.88,4.05,4.40,5.09,6.49,9.27,14.82,
};
#endif
/**
* @brief AcqTime_Min_List
* @param min acqtime for each span index  unit: us
* @Author Albert
* @date 2019-04-30
*/
#ifdef RTSA_OLD_ACQTIME
const qreal AcqTime_Min_List[] =
{
    0,
    0,
    3711112,
    1855556,
    927778,
    371112,
    185556,
    92778,
    37112,
    18556,
    9278,
    3712,
    1856,
    928,
    372,
    186,
    93,
    38,
    19
};
#else
const qreal AcqTime_Min_List[] =
{
    0,
    0,
    30000,
    30000,
    30000,
    30000,
    30000,
    30000,
    30000,
    30000,
    30000,
    30000,
    30000,
    30000,
    30000,
    30000,
    30000,
    30000,
    30000
};
#endif
/**
* @brief FFT帧数采用19bit，最大可以设置的数值为524288，在此基础上还要满足至少3帧的重叠率，即
* 最大可设置的数值为174762


* modify ACQ采用时钟计数方式，不再使用帧计数，因此最大门限只需保证32bit,即184.32MHz sample，最大计数23s
* @param
* @Author Albert
* @date 2019-08-14
*/
#ifdef RTSA_OLD_ACQTIME
const qreal AcqTime_Max_List[] =
{
    0,
    0,
    23000000,
    23000000,
    23000000,
    23000000,
    23000000,
    23000000,
    23000000,
    23000000,
    23000000,
    23000000,
    23000000,
    23000000,
    23000000,
    19418000,
    7767200,
    3883600,
    1941800
};
#else
const qreal AcqTime_Max_List[] =
{
    0,
    0,
    23000000,
    23000000,
    23000000,
    23000000,
    23000000,
    23000000,
    23000000,
    23000000,
    23000000,
    23000000,
    23000000,
    23000000,
    23000000,
    23000000,
    23000000,
    23000000,
    23000000
};
#endif
/**
* @brief  define POI PARAM
* @param
* @Author Albert
* @date 2019-05-06
*/
typedef struct
{
    qreal   sampRate;
    qreal   fftCntPerSecond;
}_RTSA_POI_PARAM;
const _RTSA_POI_PARAM Fs_Span[] =
{
    {0, 0},
    {0, 0},
    {921.6,     1.35},
    {1843.2,    2.7},
    {3686.4,    5.4},
    {9216,      13.5},
    {18432,     27.0},
    {36864,     54.0},
    {92160,     135.0},
    {184320,    270.0},
    {368640,    540.0},
    {921600,    1350.0},
    {1843200,   2700.0},
    {3686400,   5400.0},
    {9216000,   13500.0},
    {18432000,  27000.0},
    {46080000,  67500.0},
    {92160000,  135000.0},
    {184320000, 270000.0}
};
//Tony 1008 windows list
const int gWinList[][RTSA_BITVIEWNUM]=
{
    {1,0,0,0},
    {1,1,0,0},
    {1,1,1,0},
    {1,1,1,1}
};
//Tony 1016 windows display list
const int gWinCtrlList[][RTSA_BITVIEWNUM]=
{
    {1,2,0,0},
    {3,0,0,0},
    {2,3,0,0},
    {1,2,1,1},
};

//seven RBW1
enum {
    RTSA_RBW0 = 0,
    RTSA_RBW1 = 1,
    RTSA_RBW2 = 2,
    RTSA_RBW3 = 3,
    RTSA_RBW4 = 4,
    RTSA_RBW5 = 5,
    RTSA_RBW6 = 6
};

// Trace
enum {
    RTSA_TRACE_OFF   = -1,
    RTSA_CLEAR_WRITE = 0,
    RTSA_MAX_HOLD    = 1,
    RTSA_MIN_HOLD    = 2,
    RTSA_VIEW        = 3,
    RTSA_AVERAGE     = 4
};


// Marker Select
enum {
    RTSA_SELECT_M1 = 0,
    RTSA_SELECT_M2 = 1,
    RTSA_SELECT_M3 = 2,
    RTSA_SELECT_M4 = 3,
    RTSA_SELECT_M5 = 4,
    RTSA_SELECT_M6 = 5,
    RTSA_SELECT_ALL = 6,
};


//enum {
//    next_menu_dp_action = 1,
//    run_action          = 2
//};

enum{
    RTSA_SPECTRUM_SPECTROGRAM = 0,
    RTSA_SPECTROGRAM = 1,
    RTSA_DENSITY = 2,
    RTSA_DENSITY_SPECTROGRAM = 3,    //Albert 1126
};

enum{
    RTSA_FREQ_INFO = 0,
    RTSA_RBW_INFO,
    RTSA_REF_LVL,
    RTSA_FREQ_CF,
    RTSA_SYS_INFO,
    RTSA_ACQ_INFO,
    RTSA_FREQ_OFFSET,
    RTSA_REF_OFFSET,
};
#define RTSA_SAVE_FILE_TYPE_SCREEN 101
#define RTSA_SAVE_FILE_TYPE_CONFIG 102
#define RTSA_SAVE_FILE_TYPE_TRACE   103
//!Albert 1018
#define RTSA_SPECTROGRAM_CACHE_DATA 1000
#define RTSA_TRACE_DATA_NUM 801
//!albert 1217
#define RTSA_DENTISY_HIGHEST 100
#define RTSA_DENTISY_LOWEST  0
//!Albert 1026 system define
//!battery status
//enum {
//        AC_ONLY      = 0,
//        BATTERY_ONLY = 1,
//        AC_BATTERY   = 2,
//};
//battery charge status
//enum {
//    UNKNOWN     = 0,
//    CHARGING    = 1,
//    DISCHARGING = 2,
//    FULL        = 3,
//};
//File Type
enum
{
   RTSA_FILE_NONE = 0,
   RTSA_FILE_STATE,
   RTSA_FILE_TRACE_STATE,
   RTSA_FILE_SCREENCONFIG_STATE,
   RTSA_FILE_MEASUREDATA,
   RTSA_FILE_LIMIT,
   RTSA_FILE_SCREEN_IMAGE,
   RTSA_FILE_MASK,
};
//Trace Detector
enum
{
   RTSA_DEC_PEAK = 0,
   RTSA_DEC_NEGATIVE_PEAK,
   RTSA_DEC_SAMPLE,
   RTSA_DEC_AVERAGE,
   RTSA_DEC_RMS,
};

// Freq ID
enum
{
    RTSA_CENTER_FREQ = 0,
    RTSA_START_FREQ,
    RTSA_STOP_FREQ,
    RTSA_SPAN_FREQ,
    RTSA_STEP_FREQ,
};

enum{
    RTSA_FREQ_DIALOG = 0,
    RTSA_DIGITIPUT_DIALOG,
    RTSA_AMPT_DIALOG,
    RTSA_DISPLAY_DIALOG,
    RTSA_BW_DIALOG,
    RTSA_TRIGGER_DIALOG,
    RTSA_TRACE_DIALOG,
    RTSA_MARKER_DIALOG,
    RTSA_OBSERVE_DIALOG,
    RTSA_MEASURE_DIALOG,
    RTSA_LIMIT_DIALOG,
    RTSA_MEAS_TOOL_DIALOGL,
    RTSA_ALLSET_DIALOG,
    RTSA_PEAK_SEARCH_DIALOG,
    RTSA_LIMIT_SET_DIALOG,
    RTSA_AMPT_SET_DIALOG,
    RTSA_LOCK_SET_DIALOG,
    RTSA_FILE_OPEN_DIALOG,
    RTSA_FILE_SAVE_DIALOG,
    RTSA_SCREEN_CAPTURE_DIALOG,
    RTSA_SYSTEM_DIALOG,
    RTSA_HOME_DIALOG,
    RTSA_ZOOM_DIALOG,

    //Albert 19/01/22
    RTSA_MARKER1_DIALOG,
    RTSA_MARKER2_DIALOG,
    RTSA_MARKER3_DIALOG,
    RTSA_MARKER4_DIALOG,
    RTSA_MARKER5_DIALOG,
    RTSA_MARKER6_DIALOG,
};
enum{
    RTSA_MARKER_TO_START = 0,
    RTSA_MARKER_TO_CENTER,
    RTSA_MARKER_TO_STOP,
    RTSA_PEAK_SEARCH,
    RTSA_MIN_SEARCH,
    RTSA_NEXT_SEARCH,
    RTSA_PEAK_NEXT_LEFT,
    RTSA_PEAK_NEXT_RIGHT,
};

enum {
    LABEL_MODE = 0,
    LABEL_CENTER_FREQ,
    LABEL_CHANNEL,
    LABEL_SIGNAL_STANDARD,
    LABEL_PREAMP,
    LABEL_ATTEN_STATUS,
    LABEL_ATTEN_VAL,
    LABEL_RBW_STATUS,
    LABEL_AVERAGE,
    LABEL_TRACE_STATUS,
    LABEL_TRACE1_STATUS,
    LABEL_TRACE2_STATUS,
    LABEL_TRACE3_STATUS,
    LABEL_TRACE4_STATUS,
    LABEL_TRACE5_STATUS,
    LABEL_TRACE6_STATUS,
    LABEL_RBW,
    LABEL_FFTWINDOW,
    LABEL_ACQTIME,
    LABEL_PERSISTENCE,
    LABEL_FREQ_REF,
    LABEL_TRIGGER,
    LABEL_DETECTOR,
    LABEL_LIMIT,
    LABEL_POI,

    LABEL_DISPLAY,

    LABEL_END

};
#define RTSA_CHSTEP_CDMA  1250000
#define RTSA_CHSTEP_WCDMA 5000000
#define RTSA_CHSTEP_TD_SCDMA 1600000
#define RTSA_CHSTEP_GSM 200000

#define RTSA_GSM900_UP_MIN 890
#define RTSA_GSM900_UP_MAX 915
#define RTSA_GSM900_DOWN_MIN 935
#define RTSA_GSM900_DOWN_MAX 960
#define RTSA_GSM1800_UP_MIN 1710
#define RTSA_GSM1800_UP_MAX 1785
#define RTSA_GSM1800_DOWN_MIN 1805
#define RTSA_GSM1800_DOWN_MAX 1880



#define RTSA_FDD_B1_UP_FREQPOINT_BASE 18000
#define RTSA_FDD_B1_UP_FREQPOINT_MAX 18599
#define RTSA_FDD_B1_DOWN_FREQPOINT_BASE 0
#define RTSA_FDD_B1_DOWN_FREQPOINT_MAX  599

#define RTSA_FDD_B3_UP_FREQPOINT_BASE  19200
#define RTSA_FDD_B3_UP_FREQPOINT_MAX  19949
#define RTSA_FDD_B3_DOWN_FREQPOINT_BASE 1200
#define RTSA_FDD_B3_DOWN_FREQPOINT_MAX 1949

#define RTSA_FDD_B1_UP_FREQ_MIN 1920000000
#define RTSA_FDD_B1_UP_FREQ_MAX 1979900000
#define RTSA_FDD_B1_DOWN_FREQ_MIN 2110000000
#define RTSA_FDD_B1_DOWN_FREQ_MAX 2169900000
#define RTSA_FDD_B3_UP_FREQ_MIN 1710000000
#define RTSA_FDD_B3_UP_FREQ_MAX 1784900000
#define RTSA_FDD_B3_DOWN_FREQ_MIN 1805000000
#define RTSA_FDD_B3_DOWN_FREQ_MAX 1879900000

#define RTSA_TD_B38_FREQPOINT_BASE 37750
#define RTSA_TD_B39_FREQPOINT_BASE 38250
#define RTSA_TD_B40_FREQPOINT_BASE 38650
#define RTSA_TD_B41_FREQPOINT_BASE 39650

#define RTSA_TD_B38_FREQPOINT_MAX 38249
#define RTSA_TD_B39_FREQPOINT_MAX 38649
#define RTSA_TD_B40_FREQPOINT_MAX 39649
#define RTSA_TD_B41_FREQPOINT_MAX 41589

#define RTSA_TD_B38_FREQ_MIN 2570000000
#define RTSA_TD_B38_FREQ_MAX 2619900000
#define RTSA_TD_B39_FREQ_MIN 1880000000
#define RTSA_TD_B39_FREQ_MAX 1919900000
#define RTSA_TD_B40_FREQ_MIN 2300000000
#define RTSA_TD_B40_FREQ_MAX 2399900000
#define RTSA_TD_B41_FREQ_MIN 2496000000
#define RTSA_TD_B41_FREQ_MAX 2689900000
enum{
    RTSA_CDMA=0,
    RTSA_GSM,
    RTSA_LTE_FDD,
    RTSA_LTE_TDD,
    RTSA_TD_SCDMA,
    RTSA_WCDMA,
    RTSA_WIMAX,
};
enum{
    RTSA_UPLINK = 0,
    RTSA_DOWNLINK
};
enum{
    RTSA_TD_BAND_D =0,
    RTSA_TD_BAND_F,
    RTSA_TD_BAND_E,
};

typedef struct
{
    const char *name;
    int  ChStep;
    int  index;
} __RTSA_ChStand__;
static const __RTSA_ChStand__ mRTSA_ChStand[7]=
{
    {"CDMA",RTSA_CHSTEP_CDMA,RTSA_CDMA},
    {"GSM",RTSA_CHSTEP_GSM,RTSA_GSM},
    {"LTE-FDD",10000000,RTSA_LTE_FDD},
    {"LTE-TDD",10000000,RTSA_LTE_TDD},
    {"TD-SCDMA",RTSA_CHSTEP_TD_SCDMA,RTSA_TD_SCDMA},
    {"WCDMA",RTSA_CHSTEP_WCDMA,RTSA_WCDMA},
    {"WIMAX",5000000,RTSA_WIMAX},
};
enum
{
    RTSA_LOCAL = 0,
    RTSA_REMOTE,
};
enum
{
    RTSA_INDOOR = 0,
    RTSA_OUTDOOR,
    RTSA_NIGHT,
};
static const char* rtsa_qssMode[3] = {"indoor","outdoor","night"};

enum
{
    RTSA_FMT_MASK_NORMAL = 0,
    RTSA_LEAVE_LOW = 1,
    RTSA_ENTER_LOW = 2,
    RTSA_LEAVE_UPP = 3,
    RTSA_ENTER_UPP = 4,
};
// Albert 19/09/12 for trigger
#define RTSA_HOLDOFF_TIME_MIN   30000

#define RTSA_ESP_ZERO      (1.0e-5)
// 디버그 메시지 뿌릴 것인지 선택.
#define RTSA_HANLA_DEBUG
//#define HANLA_NDEBUG


#ifdef RTSA_HANLA_DEBUG
#define RTSA_DEBUG_STR(X)    {                                                                       \
                            QString strDebug;                                                        \
                            strDebug.sprintf("%s, L%d, %s()", __FILE__, __LINE__, __func__);         \
                            qDebug() << #X << strDebug;                                              \
                        }


#define RTSA_DEBUG(X)        {                                                                       \
                            QString strDebug;                                                        \
                            strDebug.sprintf("%s, L%d, %s()", __FILE__, __LINE__, __func__);         \
                            qDebug() << #X" = " << (X) << strDebug;                                  \
                        }


#define __RTSA__      {                                                                            \
                            RTSA_DEBUG_STR("Current location is ");                                  \
                        }



#else
#define RTSA_DEBUG_STR(X)
#define RTSA_DEBUG(X)
#define ____
#endif
#endif // RTSA_DEFINE_H
