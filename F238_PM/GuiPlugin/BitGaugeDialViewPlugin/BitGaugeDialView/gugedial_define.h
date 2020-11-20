#ifndef GUGEDIAL_DEFINE_H
#define GUGEDIAL_DEFINE_H

#include <QWidget>
#include <QColor>

//定义是否在AMPT中 添加OFFSET
//#define PM_AMPT_IS_OFFSET 0


//definition the picture room
#define PM_TOPDIS 40
#define PM_BOTTOMDIS 40
#define PM_LEFTDIS 40
#define PM_RIGHTDIS 30

#define PM_LINEREEOR 2
#define PM_HALFLINEREEOR 1

#define PM_BIT_GRID_START_X  (PM_LEFTDIS + PM_HALFLINEREEOR)
#define PM_BIT_GRID_START_Y  (PM_TOPDIS + PM_HALFLINEREEOR)

#define GAUGE_SCALE_BEGIN 0.0
#define GAUGE_SCALE_END 120.0

#define PM_SUMMAY_NUM 12

#define PM_BOTTOM_DATA_RECT 3
class PM_VIEW_SUMMAY
{
public:
    qint32 gNum;
    QString gSummayName[PM_SUMMAY_NUM] ;
    qreal gSummayData[PM_SUMMAY_NUM];
    QString gSummayUnit[PM_SUMMAY_NUM];
};
enum
{
    PM_LAYER_LEFT = 0,
    PM_LAYER_RIGHT = 1,

};
typedef struct
{
    QColor background;//背景色
       QColor gridPart; 	//绘制数据
       QColor curTraceIndex;  //for display trace index in spectrogram
       QColor colBarFont;

       QColor colArcLimitMid;//弧形绿
       QColor colArcLimtUpOrDown;//弧形红
       QColor colArcOffset;//弧形蓝
       QColor colIndicator1;//指针
       QColor colIndicator2;

       QColor colMidPart0;
       QColor colMidPart1;
       QColor colbottomLimitMid;//底部框绿
       QColor colbottomLimtUpOrDown;//底部框红
       QColor colbottomOffset;//底部框蓝

       QColor colbottomLimit0;//底部编辑框渐变红1
       QColor colbottomLimit1;//底部编辑框渐变红2
       QColor colbottomoffset0;//底部编辑框渐变蓝1
       QColor colbottomoffset1;//底部编辑框渐变蓝2
       QColor colbottomMid0;//底部编辑框渐变绿1
       QColor colbottomMid1;//底部编辑框渐变绿2

       QColor colorTextDial;
       QColor colorTextMidData;
       QColor colorTextTop;
       QColor colorTextTopTitle;
       QColor colorTextTitle;
       QColor colorTextBottom;

       QColor colSummay1;//Summay框色1
       QColor colSummay2;//Summay框色2
       QColor colSummay3;//Summay框色3

} _COLOR_PEN_PM;

// defaultmode outdoormode nightmode
static _COLOR_PEN_PM PmPenColor[]=
{
    {Qt::black,Qt::darkGray,Qt::white,Qt::yellow,
     QColor("#00CE24"),QColor("#D63C4F"),QColor("#007DFF"),QColor("#FFFFFF"),QColor("#FFFFFF"),
     QColor("#1B1B1B"),QColor("#2E2E2E"), QColor("#009A1B"),QColor("#A41627"),QColor("#0058C6"),
     QColor("#9F041B"),QColor("#D63C4F"),QColor("#044FAE"),QColor("#007DFF"),QColor("#017716"),QColor("#00CE24"),
     QColor("#A1A1A1"),QColor("#F0B31D"),QColor("#666666"),QColor("#FFFFFF"),QColor("#FFFFFF"),QColor("#D5D5D5"),
     QColor("#4C4C4C"),QColor("#F4F4F4"),QColor("#DEDEDE")},

    {QColor("#E0E0E0"),Qt::black,Qt::black,Qt::black,
     QColor("#00CE24"),QColor("#D63C4F"),QColor("#007DFF"),QColor("#FFFFFF"),QColor("#FFFFFF"),
     QColor("#1B1B1B"),QColor("#2E2E2E"),QColor("#009A1B"),QColor("#A41627"),QColor("#0058C6"),
     QColor("#9F041B"),QColor("#D63C4F"),QColor("#044FAE"),QColor("#007DFF"),QColor("#017716"),QColor("#00CE24"),
     QColor("#A1A1A1"),QColor("#F0B31D"),QColor("#666666"),QColor("#FFFFFF"),QColor("#FFFFFF"),QColor("#D5D5D5"),
     QColor("#4C4C4C"),QColor("#F4F4F4"),QColor("#DEDEDE")},

    {Qt::black,QColor("#645842"),QColor("#978464"),QColor("#978464"),
     QColor("#00CE24"), QColor("#D63C4F"),QColor("#007DFF"),QColor("#FFFFFF"),QColor("#FFFFFF"),
     QColor("#1B1B1B"),QColor("#2E2E2E"),  QColor("#009A1B"),QColor("#A41627"),QColor("#0058C6"),
     QColor("#9F041B"),QColor("#D63C4F"),QColor("#044FAE"),QColor("#007DFF"),QColor("#017716"),QColor("#00CE24"),
     QColor("#A1A1A1"),QColor("#F0B31D"),QColor("#666666"),QColor("#FFFFFF"),QColor("#FFFFFF"),QColor("#D5D5D5"),
     QColor("#4C4C4C"),QColor("#F4F4F4"),QColor("#DEDEDE")},
};

//矩形显示区域
typedef struct
{
    QRect drawMap;//绘图区域

    QRect topRight;   //上右
    QRect topLeft;    //上左

    QRect midUnit;   //中间Unit

    QRect midTitle;   //中间标题
    QRect midData;    //中间标题

    QRect bottomLeftData[PM_BOTTOM_DATA_RECT];//下左dbm 显示
    QRect bottomRightData[PM_BOTTOM_DATA_RECT]; //下右功率显示

    QRect Bottomcolor;//底部矩形

    QLinearGradient midLinear;
    QLinearGradient bottomLinear;

    qreal fRradius; //半径

    qreal fLimitUpDial;   //表盘根据单位显示最大值
    qreal fLimitDownDial; //表盘根据单位显示最小值

    qreal fdBmLimitUp;    //表盘显示最大值
    qreal fdBmLimitDown;  //表盘显示最大值

    QString strMidUnit;//中间Unit


    QString strMidTitle;//中间表头
    QString strTopTitleLeft;//上左表头
    QString strTopTitleRight;//上右表头
    QString strBottomLeft[PM_BOTTOM_DATA_RECT];//下左数据
    QString strBottomRight[PM_BOTTOM_DATA_RECT];//下右数据

    qreal fPowerMax;   //功率最大值
    qreal fPowerCurShowdBm;   //功率
    QString strCurShow;//

    bool bdBmRelativeBase;//是否基准功率
    bool bdBmRelativeBaseaCal;//采集基准功率
    qreal fdBmRelativeBase; //基准功率
} _PM_PIXMAP_LAYER;



typedef struct
{
    qint32 nPointNo;
    qreal fForwardDirect;
    qreal fForwardAvemW;
    qreal fForwardPeak;

    qreal fReverseDirect;
    qreal fReverseAvemW;
    qreal fReversePeak;

    qreal fTempeture;

    qreal fPowerDatamW;

    qreal fCrestFactor;

    //    Peak Envelope Power: Press this submenu key to have the sensor
    //    measure the peak power in the forward direction.
    //    CCDF: Press this submenu key to have the sensor measure the value of the
    //    Complementary Cumulative Distribution Function (CCDF). A Cumulative
    //    Distribution Function (CDF) describes the probability that the signal power is
    //    less than or equal to a threshold value. The Complementary Cumulative
    //    Distribution Function (CCDF) describes the probability that the signal power is
    //    greater than a threshold value. For directions to set the threshold, refer to the
    //    “CCDF Threshold” submenu key in the “Limits Menu” on page 4-16.
    //    Burst Average Auto: Press this submenu key to have the sensor measure
    //    the average power within the signal bursts (in the forward direction). In auto,
    //    the sensor determines the

    qreal fReflCoeff;//Press this submenu key to measure the reflection coefficient (reflected power / forward power).
    qreal fReturnLoss; //Press this submenu key to measure return loss.
    qreal fVSWR;//Press this submenu key to measure VSWR.

} _PM_SENSOR_DATA;


typedef struct
{
    QColor edgeArea;
    QColor boardLine;
    QColor curBoardLine;
} _COLOR_BOARD_PM;

static _COLOR_BOARD_PM PmBoardColor[]=
{
    {Qt::gray,Qt::black,QColor("#F0B31D")},
    {Qt::black,QColor("#E0E6E3"),Qt::green},
    {Qt::blue,QColor("#E3A6A6"),Qt::red},
};

enum {
    PM_BIT_DEFAULTMODE = 0,
    PM_BIT_OUTDOORMODE,
    PM_BIT_NIGHTMODE,
};

enum PM_BIT_UNIT{ 
    PM_BIT_DBM   = 0,
    PM_BIT_DBV   ,
    PM_BIT_DBMV  ,
    PM_BIT_DBUV  ,
    PM_BIT_VOLT  ,
    PM_BIT_WATTS ,

    PM_BIT_NONE  ,
    PM_BIT_DELTA_VOLT,
    PM_BIT_DELTA_WATTS,
};
enum PM_BIT_UNIT_INDEX{
    UNIT_DBM   = 0,
    UNIT_DBV   ,
    UNIT_DBMV  ,
    UNIT_DBUV  ,
    UNIT_W     ,
    UNIT_mW    ,
    UNIT_uW    ,
    UNIT_nW    ,
    UNIT_pW    ,
    UNIT_fW    ,
    UNIT_aW    ,
    UNIT_kV     ,
    UNIT_V     ,
    UNIT_mV    ,
    UNIT_uV    ,
    UNIT_nV    ,
    UNIT_pV    ,
    UNIT_fV    ,
    UNIT_aV    ,
    UNIT_zV    ,
    UNIT_yV    ,
};

enum {
    NO_UNIT_INDEX = 0,
    SET_UNIT_INDEX = 1,
    DATA_BY_UNIT_INDEX = 2,

};
enum {
    PV_UNIT_GHZ = 1,
    PV_UNIT_MHZ = 2,
    PV_UNIT_KHZ = 3,
    PV_UNIT_HZ = 4
};
#define PV_GHZ      1000000000    // 1GHz
#define PV_MHZ      1000000       // 1MHz
#define PV_KHZ      1000          // 1kHz
#define PV_HZ       1             // 1Hz

#define PM_dBuVFix        107.
#define PM_dBmVFix       47.
#define PM_dBVFix       -13.

enum {
    PV_BOTTOM_STARTANDSTOP = 0,
    PV_BOTTOM_CENTERANDSPAN = 1,
};

enum {
    PV_TOP_APMTINFO = 0,
    PV_TOP_NOW_DATA,
//    PV_TOP_TEMPERATURE_INFO,
//    PV_TOP_POINT_INFO,
};

enum{
    PM_DISPLAY_V90_POWER           = 0,
    PM_DISPLAY_FORWARD_BEGIN,
    PM_DISPLAY_FORWARD_AVERAGE,
    PM_DISPLAY_FORWARD_PEP,
    PM_DISPLAY_FORWARD_CF,
    PM_DISPLAY_FORWARD_CCDF,
    PM_DISPLAY_FORWARD_MODULATION,
    PM_DISPLAY_FORWARD_END,
    PM_DISPLAY_REVERSE_BEGIN,
    PM_DISPLAY_REVERSE_AVERAGE,
    PM_DISPLAY_REVERSE_RC,
    PM_DISPLAY_REVERSE_RL,
    PM_DISPLAY_REVERSE_VSWR,
    PM_DISPLAY_REVERSE_EMD,
    PM_DISPLAY_SUMMARY,
};

enum
{
    PM_BIT_START_FREQ = 0,
    PM_BIT_STOP_FREQ  = 1,
    PM_BIT_CENTER_FREQ = 2,
    PM_BIT_SPAN_FREQ = 3 ,
    PM_BIT_OFFSET_FREQ = 4,
    PM_BIT_STEP_FREQ = 5,
};
typedef struct
{
  QString gtflstr; //TopFirstLeft
  QString gtslstr;//TopSecondLeft
  QString gtscstr;//TopSecondCenter
  QString gtfrstr; //TopFirstLeft
  QString gtsrstr;//TopSecondLeft

  QString gbflstr;//BottomFirstLeft
  QString gbfrstr;
  QString gbslstr;
  QString gbsrstr;

  qreal gbfl;
  qreal gbfr;
  qreal gbsl;
  qreal gbsr;
}PM_WORD_CTRL;

typedef struct
{
  qreal gstartfreq;
  qreal gstopfreq;
  qreal gcenterfreq;
  qreal gspanfreq;
  qreal gfreqoffset;
}PM_BIT_FREQ_INFO;

#define PM_MIJIHEIGHT    490
#define PM_BITWORDLEFT   5
#define PM_BITWORDHSET   4
#define PM_WORDHEIGHT    20
#define PM_WORDWIDTH     47
#define PM_TITLEWIDTH    230

#endif // GUGEDIAL_DEFINE_H
