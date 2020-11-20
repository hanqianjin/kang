#ifndef BITVIEW_H
#define BITVIEW_H

#include <QWidget>
#include <QTableWidget>
//#include <QtUiPlugin/QDesignerExportWidget>
#include "bvbuffermana.h"
#include "bvctrlmana.h"
#include <QPen>
#include "bvtablewidget.h"
#include <QTimer>
#include <QImage>
#include <QRegExp>
/**************Copyright (c)*************************
 **
 **                     INNO Instrument(China) Co.,Ltd.
 **
 **------------File Info------------------------------------------
 **File name:
 **Latest Version:
 **Latest modified Date:
 **Modified by:
 **Descriptions:
 **
 **---------------------------------------------------------------
 **Created by:
 **Created date: 2018BITDEFAULT0BITDEFAULT6
 **Descriptions:
 **
 *****************************************************************/
#define EPSILON 1e-3

//#if defined(BITVIEW_BUILD)
//#  define WIDGET_API Q_DECL_EXPORT
//#else
//#  define WIDGET_API Q_DECL_IMPORT
//#endif

struct float4
{
    float x;
    float y;
    float z;
    float w;

    float4() {};
    float4(float value)
    {
        x = y = z = w = value;
    }
};

class   BitView : public QWidget
{
  Q_OBJECT

public:
  explicit BitView(QWidget *parent = 0);
  BitView(qint32 plugindex, qint32 curwindowindex, QWidget *parent = 0);
  ~BitView();

protected:
  void paintEvent(QPaintEvent *event)override;
  void resizeEvent(QResizeEvent *event)override;
  void mousePressEvent(QMouseEvent *event)override;
  void mouseMoveEvent(QMouseEvent *event)override;
  void mouseReleaseEvent(QMouseEvent *event)override;
  void mouseDoubleClickEvent(QMouseEvent *event)override;

private:
  BVTableWidget *mlimitTableWidget;
  QPixmap gpixmap; //this parts used for background
  QPixmap gsigrendermap;//this parts used for sig renders
  QPen gbitpen; 
  QPen gboarderpen;//Plugin's boarder lines.
  pthread_mutex_t glockobj;
  //trace attribute
  buffermana gbitbuffer;
  ctrlmana* gctrlmana;
  //main class used
  quint32 gplugindex;
  quint32 gmsgsourceindex;

  //test 1022
  qreal sum;
  BIT_SIZE_CTRL gusedsize;
  BIT_WORD_CTRL gwordset;
  BIT_FREQ_INFO gfreqinfo;

  QRect CenterPartRect;
  QRect topPartRect;
  QRect leftPartRect;
  QRect bottomPartRect;
  QRect markerinfoRect;

  qint32 gAmptdUnit;

  //1015 test
//  QPixmap pixmapnew;
  //! Albert add, in order to not redraw when rect changes between big and small.
  QPixmap pixmapnewSmall;
  QPixmap pixmapnewBig;
  quint32 rgbBuffer[SPECTROGRAM_COLBAR_NUM];
  quint32 dpxRgbBuffer[SPECTROGRAM_COLBAR_NUM];

  qint32 mBitviewType;
  qint32 mResizeMark;  //Tony 1024

  //Marker point position.
  QPoint mkrNormalPoints[4];
  QPoint mkrDeltaPoints[4];


public:
//!setters:
  //! Freq part
  void setFreqAttribute(quint32 attributeType, qreal attribute);//!Tony 1016 Add.Setting frequency information.
  void setAmptdAttribute(qint32 attributeType,qreal attribute);//!Setting amplitude information.
  //! amplitude part
  void setAmptdUnit(qint32 unit);//!Tony 1016 Add. Setting unit.
  void setBitviewType(qint32 type);//!Tony 1016 Add. Setting plugin type,like spectrum.
  //! Limit part
  void setLimitAttribute(qint32 attributeType, qint32 attribute, qint32 limitindex = BITDEFAULT);
  void setLimitAttributeEX(qint32 attributeType, qreal value, qint32 limitindex = BITDEFAULT);
  void setTableEdit(qint32 operationType,  qint32 visible = 0, qint32 index = BITDEFAULT);
  qint32 setLimitPointData(qreal *pbuff,qint32 datanum,qint32 datatype,qint32 limitindex = BITDEFAULT);
  //Albert for limit edit dialog set 19/03/26
  void setLimitCurPointData(qreal pData,qint32 dataIndex,qint32 datatype,qint32 limitindex = BITDEFAULT);
  //! Marker part
  void setMarkerAttribute(qint32 attributeType, qint32 attribute,qint32 markerIndex = BITDEFAULT);
  qreal setMarkerFreqAttribute(qint32 attributeType, qreal attribute, qint32 markerIndex = BITDEFAULT);
  //!Trace part
  //for multi trace control by the way of setting attributes
  void setTraceAttribute(quint32 traceIndex,quint32 attributeType,quint32 attribute);
  qint32 setTraceRenderData(qreal *pbuff,qint32 datanum,qint32 traceIndex = BITDEFAULT);
  //! System part
  void setSystemAttribute(qint32 attributeType,qint32 attribute);// Tony 1029
  //!Albert 12/13
  void setWindowRect(qint32 width,qint32 height);

//!getters:
  //! Freq part
  qreal getFreqAttribute(quint32 attributeType);//!Tony 1122 Add.Getting frequency information.
  qreal getAmptdAttribute(qint32 attributeType);//!Getting amplitude information.
  //! amplitude part
  qint32 getAmptUnit();//!Getting unit.
  qint32 getBitviewType();//!Getting plugin type,like spectrum.
  //! Limit part
  qint32 getLimitAttribute(qint32 attributeType,qint32 limitindex = BITDEFAULT);
  qreal getLimitAttributeEX(qint32 attributeType,qint32 limitindex =BITDEFAULT);
  qint32 getLimitPointData(qreal *pbuff, qint32 num, qint32 datatype, qint32 limitindex =BITDEFAULT);
  //Albert for limit edit dialog set 19/03/26
  qreal getLimitCurPointData(qint32 dataIndex, qint32 datatype, qint32 limitindex =BITDEFAULT);

  //! Marker part
  qint32 getMarkerAttribute(qint32 attributeType,qint32 markerIndex = BITDEFAULT);
  qreal getMarkerFreqAttribute(qint32 attributeType, qint32 markerIndex = BITDEFAULT);
  qreal getMarkerCurrentFreq(qint32 attributeType);
  qreal getMarkerAmptInfo(qint32 attributeType,qint32 markerIndex = BITDEFAULT);
  qreal getMarkerInfo(qint32 attributeType,qint32 markerIndex = BITDEFAULT);
  //Albert 19/01/21
  QString getMarkerInfoStr(qint32 attributeType,qint32 markerIndex = BITDEFAULT);
  //!Trace Part
  qint32  getTraceAttribute(quint32 traceIndex, quint32 attributeType);
  qint32 getTraceRenderData(qreal *pbuff,qint32 datanum,qint32 traceIndex = BITDEFAULT);
  //! System part
  qint32 getSystemAttribute(qint32 attributeType);

  //this func is for reflesh first layer
  void showSigLine(qreal *pBuffer, quint32 datanum);
  void showFalltrom(qreal* pBuffer,quint32 datanum);
  //dpx interface for display
  void showDensity(qreal *pData,quint32 *pBuff, quint32 datanum, qint32 width, qint32 height);

  void getclickSource(quint32 iIndex);
  void showBoarderLine();

  //Albert 19/05/05 cancel all board line
  void HideBoardLine();

  //Tony 1123
  //this part is not very convenient to use.Should move to private.
  void showLeftPart();
  void showTopPart();
  void showBottomPart();

  void refleshdisplay(); //Tony 1106 Add.Trigger drawing events.
  void refleshmarker();

  void showTopWordsMsg(qint32 msgType);
  void showBottomWordsMsg(qint32 msgType);

  void setTopWordsMsg(quint32 traceIndex,const QVector<QString> &wordvec);
  void setBottomWordsMsg(quint32 traceIndex,const QVector<QString> &wordvec);
  void setBottomSingleWordsMsg(quint32 traceIndex,qint32 index,QString word);

  void initSpectrogramCacheDataArray(qreal* pBuffer); //initial cache data array.

  void cacheData(qreal* pDis,qreal* pSrc,qint32 Num); //Albert 1018, refresh cache data, when draw done.
  quint32 getRealCacheDataNum();   // Albert 1018, return the actual cache data num.
  quint32 getCacheDataStartPos();  // Albert 1018, return cur cache data start pos.
  //!Albert 1025 Set rect only use the first initial. external use
  void SetSpectrogramSmallPixRect(qint32 nWidth, qint32 nHeight);
  void SetSpectrogramBigPixRect(qint32 nWidth, qint32 nHeight);

  void markerUpdateByFreq();
  void markerMove(qint32 type);

  //Albert 19/01/24
  qreal searchMax();
  qint32 searchMin();
  //Albert 19/01/24 for marker to function
  qreal MarkerToPeak();
  void MarkerToMin();
  void MarkerToNextPeak();
  void MarkerToLeftPeak();
  void MarkerToRightPeak();
  //Albert 19/03/08 for acq time
  void setAcqTime(qreal time);
  //Albert 19/03/14 for freq offset
  void setFreqOffset(qreal freq);
  //Albert 19/05/23 for FMT
  void setFmtShow(bool isOn);
  void setFMTData(qreal *pbuff, qint32 datanum, qint32 datatype);
  void FmtXAxisCalculatorFunc(qreal* Freq,quint32 datanum);
  void FmtYAxisCalculatorFunc(qreal* level, quint32 datanum);
  void refreshFmtDrawData(quint32 datanum);
  void FmtInterpolationCalculatorFunc();
  void setFmtType(qint32 type);

  QImage AdjustSaturation(QImage Img, int iSaturateValue);
  void setTriggerrMode(qint32 mode);
  void setVideoTriggerLevel(qreal video);
  void recalVideoAxis();
  void setMarkerRefAmpt(qreal refAmpt, quint32 markerID);
  qreal getMarkerRefAmpt(quint32 markerID);
  void setMarkerNormalPosY(qint32 pos, quint32 markerID);
  qint32 getMarkerNormalPosY(quint32 markerID);
  void refreshSepectrogramRect();   // fill black when rect changed, Ref change or scale change, ....

  uchar* getDensityData(qint32 dataNum);
  void setDensityData(qreal* pTraceData, uchar* pData);

  void renderFileLoadTraceLine();
  void setFileLoadDoneFlag(bool isFileLoad);
  void renderFileSpectrogram(qreal* pData);
  qint32 getSpectrogramValidStartPos(qint32 &validStartPos, qint32 &realNum);



private:
  //! Albert 1019
  void drawCurTraceIndex(QPainter* painter,quint32 nCurIndex);
  //! Albert add 1018
  void drawSpectrogram(QPainter* painter);  //main spectrogram func.
  void drawSpectrogramSmallPix(QPainter* painter);  //main spectrogram func.
  void drawSpectrogramBigPix(QPainter* painter);  //main spectrogram func.
  void renderSpectrogramColBar(QPainter *pPainter);
  void renderDensityPart(QPainter* pPainter);
  void drawDensityColBar(QPainter* pPainter);
  //for static pause when setting div or ref or offset to call
  void refleshfirLayer();
  //render background.
  void refleshsecLayer();
  //render DPX display
  //void renderDensityPart(QPainter* pPainter);
  void refleshfallslot();
  //render background grid lines
  void renderGridLines(QPainter *pPainter);
  //render background grid lines for spectrogram.
  void renderSpectrogramGridLines(QPainter *pPainter);
  //render boader lines .
  void renderBoaderLines(QPen *mpen,QPainter* mpainter);
  //render background left part.
  void renderLeftPart(QPainter *pPainter);
  //render background top part.
  void renderTopPart(QPainter *pPainter);
  //render background bottom part.
  void renderBottomPart(QPainter *pPainter);
  //render spectrum lines.
  void renderSiglines(QPainter* pPainter);

  //render FMT background, Albert 19/03/29
  void renderFMTLayer(QPainter* painter);

  //render top marker info Albert 19/05/10
  void renderTopMarkerPart(QPainter* pPainter, QString str);


  //sync control when plot datas,used inner
  qint32 getSync();
  qint32 releaseSync();

  void oriDataDeals(qreal *pBuffer,quint32 dataNum);
  void axesTranslate(quint32 traceIndex,qreal *pBuffer,quint32 dataNum);

  void averageProcess(quint32 traceIndex,qreal *psourBuffer,quint32 dataNum);
  void maxholdProcess(quint32 traceIndex, qreal *psourBuffer, quint32 dataNum);
  void minholdProcess(quint32 traceIndex,qreal *psourBuffer,quint32 dataNum);
  void innerIniOnece();
  void produceColorBar(qint32 displaymode);
  qint32 freqnotZeroPosition(qreal freq);
  qint32 freqUnitFindProc(qreal freq);
  QString freqValueToQstring(qreal freq);
  void dbmToVoltCalculatorAndDisplayFunc(char *label, qreal _level);
  qreal dbmToVoltCalculator(qreal _level);
  void dbmToWattsCalculatorAndDisplayFunc(char *label, qreal _level);
  qreal dbmToWattsCalculator(qreal _level);
  //!Albert 1024, use two pixmap, must cal x pts first.
  void RecalSpectrogramBigPointX();
  void RecalSpectrogramSmallPointX();
  void calculationPainterArea(); //Tony 1101 Add.Painter element position.
  //Tony 1026 Add. Marker function.
  void renderMarkerPart(QPainter *pPainter);
  void renderMarkerNoiseInfo(QPainter *pPainter);
  void renderMarkerTableBoaderLines(QPainter *painter);
  //calculator marker parameter
  void markerNormalPolygonAssignNDrawFunc(QPainter *painter, qint32 pos);
  void markerDeltaPolygonAssignNDrawFunc(QPainter *painter, qint32 pos);
  qreal freqIndexToFreq(qint32 index);
  void markerCurrentSelectInfoDisplayFunc(QPainter *painter);
  void markerTableInfoDisplayFunc(QPainter *painter);
  qreal calculateMarkerNoiseValue(qreal markerValue, qreal rbwfreq);

  qint32 findFreqToAxesPosIndex(qreal freq);
  qint32 findAxesPosIndex(qint32 axas);

  //Tony 1112 Limit Parter
  //This part is used to render Limit and limit infomation
  void renderLimitPart(QPainter *pPainter);
  void renderLimitLine(QPainter *painter);
  void renderLimitMargin(QPainter *painter);
  void renderLimitSiglines(QPainter *painter);
  void renderLimitTestResult(QPainter *painter);
  //This part is used to calculator Limit parameter
  void limitXAxisCalculatorFunc(qreal Freq,quint32 index,quint32 uLimitSelect);
  void limitYAxisCalculatorFunc(qreal level, quint32 index,quint32 uLimitSelect);
  void limitLineInterpolationCalculatorFunc(quint32 uLimitSelect);
  void getLowerUpperLimitLineInterpolation();
  void judgeLimitTestResult();
  void produceDensityColorBar();
  void renderDensityColorBar(QPainter *pPainter);
  //ALbert 09/01/17
  qreal ChangedBmToUV(qreal value);
  qreal ChangedBmToMW(qreal value);
  void ChangeValueToVoltStr(char* label,qreal value);
  void ChangeValueToWattStr(char* label,qreal value);
  //Albert 09/03/08
  QString getPersistenceTimeStr(qreal time);
  void renderVideoTriggerLevel(QPainter *painter);

  void updateGaussianGold(float delta, int radius);
  float heuclideanLen(float4 a, float4 b, float d);
  void bilateralFilterGold(unsigned int *pSrc, unsigned int *pDest, float e_d, int w, int h, int r);
  unsigned int hrgbaFloatToInt(float4 rgba);
  float4 hrgbaIntToFloat(unsigned int c);
  float4 mul(float a, float4 b);
  float4 add4(float4 a, float4 b);
  bool checkOriData(qreal* data, quint32 dataNum);

signals:
  void singleClicked(quint32 iIndex);
  void markerchange(qint32 index);
  //Albert 19.01.04
  void markerMove(bool isMove);


  void emitRefleshsig();
  void emitrefleshDensity();
  //1015
  void emitFallSig();

  //Albert 19/05/28
  void mouseDoubleClickedSig(bool isEnable);

private slots:
  void graphRefleshslot();
  void graphFallslot();
  void on_tableClicked();//Tony1112
  //Tony1207 DPX refresh
  void densityRefslot();

  void on_mouseclick();
//!private paramDef
private:
  _COLOR_TRACE mTraceColor;
  _COLOR_TRACE mTraceC;
  _COLOR_PEN   mPenColor;
  _COLOR_LIMIT mLimitColor;
  _COLOR_MARKER mMarkerColor;
  _COLOR_BOARD mBoardColor;
  QPen mLeftPen;
  QPen mTopPen;
  QPen mBottomPen;
//  uint mCurTraceIndex;  //spectrogram use cur trace data index, in order to get data.
  qreal* mCacheData;
  qreal* mStartPos;    //* mStartPos means the cache data start pos
  quint32 mCacheDataStartPos;
  quint32 mCacheRealNum;
  //Tony 1026.Marker Part.
  qint32 marker_mouse_move_pos;
  qint32 markerTabelVisiable;
  qint32 markertotalcnt; //Tony 1105
  //1029
  typedef struct
  {
    qint32 runningState;
    qint32 windowtype;  //multi or single
    qint32 language;
    qint32 displaymode;
  }SYSTEM_STATE;
  SYSTEM_STATE gsystemstate;
  void setdisplaymode(qint32 displaymode);
  QImage imageFromData; //DPX image
  qreal mCurveValue;//DPX curve for color
  qint32 mWindowWidth;
  qint32 mWindowHeight;
//  qreal mMarkerRefAmpt;
  qint32 mMarkerNormalPosY; //Albert 19/02/23 when delta marker on,record normal pos
  qreal mFreqOffset;
  bool  misFmtShow;
  bool misDoubleClicked;
  qint32 mFmtType;
  float gaussian[50];
  QTimer* timer;
  qint32 clickCnt;
  bool mFileLoadFlag;
};

#endif


