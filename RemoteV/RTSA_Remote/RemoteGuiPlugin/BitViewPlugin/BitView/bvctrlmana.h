#ifndef BVCTRLMANA_H
#define BVCTRLMANA_H

#include <QObject>
#include <bvmacrodef.h>
#include <QPolygonF>
/*
this class is designed for render,such as trace show or not,maker show or not and so on.
*/
typedef struct
{
  qreal grefValue;
  qreal gdivValue;
  qreal goffsetValue;

  qreal gpicwidth;
  qreal gpicheight;
  qreal gpixelstep;
  //Tony 1101  Grid postion.
  qreal gridX[10];
  qreal gridXSpace;
  qreal gridY[10];
  qreal gridYSpace;
} BIT_SIZE_CTRL;
typedef struct
{
  QString gtflstr;
  QString gtslstr;
  QString gtscstr;

  QString gbflstr;
  QString gbfrstr;
  QString gbslstr;
  QString gbsrstr;

  qreal gbfl;
  qreal gbfr;
  qreal gbsl;
  qreal gbsr;
}BIT_WORD_CTRL;
typedef struct
{
  qreal gstartfreq;
  qreal gstopfreq;
  qreal gcenterfreq;
  qreal gspanfreq;
  qreal grbwfreq;
  qreal gacqTime;
}BIT_FREQ_INFO;
class ctrlmana : public QObject
{
  Q_OBJECT
public:
  explicit ctrlmana(QObject *parent = 0);

signals:

public slots:

public:
//  uint gtraceIndex;//means now active line

  quint32 gtraceonoffflag[SUPPORTTRACENUM];//visiable flag,true visi,other unvisi

  quint32 gtraceavagflag[SUPPORTTRACENUM];  //ave on\off
  quint32 greavagflag[SUPPORTTRACENUM];
  quint32 gnowavagnum[SUPPORTTRACENUM];
  quint32 gmaxkeepreflag[SUPPORTTRACENUM];
  quint32 gminkeepreflag[SUPPORTTRACENUM];

  quint32 gtracetype[SUPPORTTRACENUM];//clear/avag/max/min/off
  quint32 gavagnum[SUPPORTTRACENUM];//line avag times

  qint32 gtraceIndex ;
  //Marker
  //Marker info
  qint32        gMarkerView[BIT_MARKER_TOTAL_CNT];  //Marker  On--Off
  qint32        gMarkerType[BIT_MARKER_TOTAL_CNT];  // Marker Type Normal / Delta
  qint32        gMarkerDisplay; //Marker + Table \ Marker Only \ Marker off
  qint32        gMarkerNoise[BIT_MARKER_TOTAL_CNT];  //[0] OFF [1] ON
  qreal    gMarkerNormalFreq[BIT_MARKER_TOTAL_CNT];     //  Marker Freq
  qint32                   gMarkerNormalIndex[BIT_MARKER_TOTAL_CNT];    //  Marker position index
  qreal    gMarkerDeltaFreq[BIT_MARKER_TOTAL_CNT];   //  Marker Freq
  qint32                   gMarkerDeltaIndex[BIT_MARKER_TOTAL_CNT];  //  Marker position index
  qint32 gMarkerSelect;
  qreal     gMarkerRefAmpt[BIT_MARKER_TOTAL_CNT];
  qint32    gMarkerNormalPosY[BIT_MARKER_TOTAL_CNT];

  //Limit
  qint32         gLimitView[BIT_LIMIT_TOTAL_CNT];    //Limit view  [0]--On [1]--Off

  qreal      gLimitAmplitude[BIT_LIMIT_TOTAL_CNT][BIT_LIMIT_TOTALDOT]; //Limit amplitude value.
  qreal      gLimitFreq[BIT_LIMIT_TOTAL_CNT][BIT_LIMIT_TOTALDOT]; //Limit freq value unit MHz.

  qint32         gLimitpointsXIndex[BIT_LIMIT_TOTAL_CNT][BIT_LIMIT_TOTALDOT];
  qreal      gLimitpointsX[BIT_LIMIT_TOTAL_CNT][BIT_LIMIT_TOTALDOT];
  qreal      gLimitpointsY[BIT_LIMIT_TOTAL_CNT][BIT_LIMIT_TOTALDOT];
  qreal      gLimitMaiginpointsY[BIT_LIMIT_TOTAL_CNT][BIT_LIMIT_TOTALDOT];
  qint32         gLimitPointCnt[BIT_LIMIT_TOTAL_CNT];//Limit point total count.
  qint32         gLimitMargin[BIT_LIMIT_TOTAL_CNT];
  qreal      gLimitMarginValue[BIT_LIMIT_TOTAL_CNT];


  qint32         gLimitTest;                         //Limit test [0]--Off [1]--On
  qint32         gLimitTestValue;                    //Limit test value [0]--fail [1]--pass
  qint32         gLimitMarginTestValue;              //Limit Margin TestValue
  qint32         gLimitSelect;                       //Current limit index.
  qint32         gLimitType[BIT_LIMIT_TOTAL_CNT];    //Limit type   upper or lower.


  QColor      gLimitColor[BIT_LIMIT_TOTAL_CNT];   //Limit color.
  qint32         gLimitVisiable;                     //Limit visiable. [0]--There is no limit open [1]--As long as there is a limit open.

  //Albert 19/03/29 for FTM draw
  uchar uFmtRGB[DPX_WIDTH_SIZE * DPX_HEIGHT_SIZE * 4];

  qreal     gFMTFreq[BIT_LIMIT_TOTALDOT];
  qreal     gFMTAmplitude[BIT_LIMIT_TOTALDOT];
  qreal     gFmtPointsX[BIT_LIMIT_TOTALDOT];
  qreal     gFmtPointsY[BIT_LIMIT_TOTALDOT];
  qint32    gFmtPointsNum;
  qint32    gFmtInterpolationData[2 * BIT_LIMIT_TOTALDOT];
  QPolygonF gFmtPolygon;
  qreal     gVideoLevel;
  qreal     gVideoPointsX[NOWTRACENUM];
  qreal     gVideoPointsY[NOWTRACENUM];
  qint32    gTriggerMode;
};
#endif // BVCTRLMANA_H