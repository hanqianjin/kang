#ifndef BVMACRODEF_H
#define BVMACRODEF_H
#include <QColor>
//default night outdoor
#define MODETOTALCNT         3
#define SUPPORTTRACENUM 6
#define SUPPORTTRACEPOINT 4001
#define SUPPORTTRACEMINPOINT 2
#define NOWTRACENUM 801

#define GRIDNUM 10
#define BITDEFAULT -1
//definition the picture room
#define TOPDIS 40
#define BOTTOMDIS 40
#define LEFTDIS 55
#define RIGHTDIS 10

#define WINDOW_HALF_WIDTH 0

#define LINEREEOR 2
#define HALFLINEREEOR 1

#define BIT_GRID_START_X  (LEFTDIS + HALFLINEREEOR)
#define BIT_GRID_START_Y  (TOPDIS + HALFLINEREEOR)

#define BITOFF  0
#define BITON   1

#define BITTR1                  0
#define BITTR2                  1
#define BITTR3                  2
#define BITTR4                  3
#define BITTR5                  4
#define BITTR6                  5

#define MAXHOLDINI    -200
#define MINHOLDINI     200

#define MIJIHEIGHT    490
#define BITWORDLEFT   5
#define BITWORDHSET   4
#define WORDHEIGHT    20
#define WORDWIDTH     47
#define TITLEWIDTH    185   //Tony 1024 120-->140
#define SPECTROGRAM_COLBAR_NUM 255
#define SPECTROGRAM_CACHE_DATA 1000
#define SPECTROGRAM_TRACE_SIZE 801

//Tony 1022
#define BV_GHZ      1000000000    // 1GHz
#define BV_MHZ      1000000       // 1MHz
#define BV_KHZ      1000          // 1kHz
#define BV_HZ       1             // 1Hz
//Tony 1022
#define dBuVFix        107.
#define dBmVFix       47.
#define dBVFix       -13.

#define BIT_MARKER_TOTAL_CNT 6   //Tony 1024
#define BIT_MARKER_TOUCH_WIDTH 20
#define BIT_MARKER_FONT_HEIGHT  30 //Tony 1029
#define BIT_MARKER_INFO_GRID_POSITION 6 //Tony 1101
#define BIT_MARKER_TABLE_HEIGHT  150

//Tony 1106
#define BIT_LIMIT_TOTAL_CNT 6
#define BIT_LIMIT_TOTALDOT 801
//Tony 1108
#define BITLMT1      0
#define BITLMT2      1
#define BITLMT3      2
#define BITLMT4      3
#define BITLMT5      4
#define BITLMT6      5


#define BIT_TABLEWIDGET_HEADER_LENGTH 120
#define BIT_TABLEWIDGET_HEADER_MIN    273
#define BIT_TABLEWIDGET_FIRST_VHEADER_WIDTH   15
#define BIT_TABLEWIDGET_WIDTH         260
#define BIT_TABLEWIDGET_OPACITY       0.9
#define BIT_TABLEWIDGET_AMP_MAX       30.
#define BIT_TABLEWIDGET_AMP_MIN       -170.

#define BIT_COLORLEVEL  200
#define BIT_COLORLEVEL_MIN 10
#define BIT_CURVE_MIN      0.1
#define BIT_CURVE_MAX      5
//Albert 12/19
#define BIT_AVERAGE_DEFUALT 10
//Albert 19/03/08
#define BIT_S      1000000       // 1 s   time/1000000
#define BIT_MS     1000          // 1 ms  time/1000
#define BIT_US     1             // 1 us  reference
#define BIT_NS     1000          // 1 s   time*1000
//Albert add for marker display
#define BIT_MARKER_LINEERROR 10

//Albert 19/04/02 DPX data array
#define DPX_WIDTH_SIZE  801
#define DPX_HEIGHT_SIZE 201

//Albert 19/07/30
#define BIT_REFRESH_TIME_MIN 90000

//Tony 1022
enum {
    BV_BOTTOM_STARTANDSTOP = 0,
    BV_BOTTOM_CENTERANDSPAN = 1,
};
enum {
    BV_TOP_APMTINFO = 0,
};
//Tony 1022
enum BIT_UNIT{
    BIT_DBM   = 0,
    BIT_DBV   = 1,
    BIT_DBMV  = 2,
    BIT_DBUV  = 3,
    BIT_VOLT  = 4,
    BIT_WATTS = 5
};
//Tony 1022
enum {
    BV_UNIT_GHZ = 1,
    BV_UNIT_MHZ = 2,
    BV_UNIT_KHZ = 3,
    BV_UNIT_HZ = 4
};
//Tony 1022
enum
{
    BIT_AMPTD_REF = 0,
    BIT_AMPTD_DIV = 1,
    BIT_AMPTD_OFFSET = 2,
};
//thie acco to the attribute of BIT_TRACE_TYPE_ATTR
enum
{
  BIT_TRACE_OFF   = 0,
  BIT_CLEAR_WRITE = 1,
  BIT_MAX_HOLD    = 2,
  BIT_MIN_HOLD    = 3,
  BIT_VIEW        = 4,
  BIT_AVERAGE     = 5
};
//Tony 1016
enum
{
    BIT_START_FREQ = 0,
    BIT_STOP_FREQ  = 1,
    BIT_CENTER_FREQ = 2,
    BIT_SPAN_FREQ = 3 ,
    BIT_RBW_FREQ = 4,
    BIT_OFFSET_FREQ = 5,
};
//Tony 1016
enum PLUGIN_TYPE
{
    BIT_NONE           = -1,
    BIT_SPECTRUM       = 0,
    BIT_SPECTROGRAM    = 1,
    BIT_DENSITY        = 2

};
//this part is big type of attributes
enum
{
  BIT_AVAG_ATTR = 1,
  BIT_RE_AVAG_ATTR,
  BIT_AVAG_NUM_ATTR,
  BIT_TRACE_TYPE_ATTR,
  BIT_AVAG_NOW_NUM_ATTR,
  BIT_TRACE_INDEX,
  BIT_TOP_FIR_LEFT,
  BIT_TOP_SEC_LEFT,
  BIT_TOP_SEC_CENTER,
  BIT_BOTTOM_FIR_LEFT,
  BIT_BOTTOM_FIR_RIGHT,
  BIT_BOTTOM_SEC_LEFT,
  BIT_BOTTOM_SEC_RIGHT
};
enum
{
    BIT_NORMAL = 0,
    BIT_DELTA = 1,
};

enum {
    BIT_NOT_MARKER_MOUSE_CLICK    = 0,
    BIT_MARKER_MOUSE_ACTION       = 1
};
enum
{
  RUNNINGSTATE = 0,
  WINDOWTYPE ,
  LANGUAGE ,
  DISPLAYMODE ,
};
enum
{
  BIT_CONTINUOUS = 0,
  BIT_SINGLE = 1,
};

//Tony 1029 Add
enum
{
    BIT_MARKER_INDEX = 0,
    BIT_MARKER_VISIABLE = 1,
    BIT_MARKER_TYPE = 2,
    BIT_MARKER_DELTA = 3,
    BIT_MARKER_NORMAL = 4,
    BIT_MARKER_DISPLAY = 5,
    BIT_MARKER_NOISE = 6,
    BIT_MARKER_DELTA_INDEX = 7,
    BIT_MARKER_NORMAL_INDEX = 8,
};

enum
{
    BIT_MARKER_TABLE = 0,
    BIT_MARKER_ONLY,
    BIT_MARKER_OFF,
};
enum
{
    BIT_MARKER_CURRENT_FREQ,
    BIT_MARKER_STEP_FREQ,
    BIT_MARKER_REF,
};
enum
{
    BIT_MULTIWINDOW = 0,
    BIT_SINGLEWINDOW = 1,
};
//Tony 1106
enum
{
    BIT_MARKER_MOVE_LEFT_MICRO = 0,
    BIT_MARKER_MOVE_LEFT_MACRO  ,
    BIT_MARKER_MOVE_RIGHT_MICRO ,
    BIT_MARKER_MOVE_RIGHT_MACRO ,
};
//Tony 1106
enum
{
    BIT_LIMIT_INDEX = 0,
    BIT_LIMIT_VIEW ,
    BIT_LIMIT_TEST ,
    BIT_LIMIT_MARGIN ,
    BIT_LIMIT_MARGIN_VALUE ,
    BIT_LIMIT_TYPE ,
    BIT_LIMIT_POINT_NUM,
};
enum
{
    BIT_LIMIT_EDIT_VISIABLE = 0 ,
    BIT_LIMIT_INSERT_ROW ,
    BIT_LIMIT_DELETE_ROW ,
    BIT_LIMIT_DELETE_LIMIT ,
    BIT_LIMIT_DELETE_ALL_LIMIT ,
};
enum
{
    BIT_LIMIT_TABLE_EDIT_HIDE = 0,
    BIT_LIMIT_TABLE_EDIT_SHOW,
};
enum
{
    BIT_LIMIT_UPPER = 1,
    BIT_LIMIT_LOWER ,
};
enum
{
    BIT_LIMIT_FREQ = 1,
    BIT_LIMIT_AMPT ,
};

enum
{
    BIT_LIMIT_FAIL = 0,
    BIT_LIMIT_PASS ,
};

enum {
    BIT_BACKGROUNDLAYER = 0,
    BIT_REALTIMELAYER,
    BIT_ALLLAYER,
};
enum {
    BIT_DEFAULTMODE = 0,
    BIT_OUTDOORMODE,
    BIT_NIGHTMODE,
};

enum
{
   BIT_FMT_FREQ = 0,
   BIT_FMT_AMPT,
};

enum
{
    BIT_TRIGGER_FREE_RUN = 0,
    BIT_TRIGGER_VIDEO,
    BIT_TRIGGER_EXTERNAL,
    BIT_TRIGGER_PERIODIC_TIMER,
    BIT_TRIGGER_RF_BURST,
    BIT_TRIGGER_FMTMASK,
};

enum
{
  BIT_FMT_UPPER = 0,
  BIT_FMT_LOWER,
};
#endif // BVMACRODEF_H
