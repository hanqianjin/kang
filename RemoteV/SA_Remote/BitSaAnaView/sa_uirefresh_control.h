#ifndef SA_UIREFRESH_CONTROL_H
#define SA_UIREFRESH_CONTROL_H

#include "sa_user_limit.h"
#include "sa_user_variable.h"
#include "sa_stdafx.h"
#include "sa_measure_control.h"

//#include <QtGui>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QRect>
#include <QMap>
#include <QObject>

#define SMALL_LARGE_PIXMAP_IMAGE 0
#define DPX_DEFINE 0

class sa_UIRefresh_Control:public QObject
{
    Q_OBJECT
public:
    sa_UIRefresh_Control(user_variable &m_user_variable,user_limit &m_user_limit);
    ~sa_UIRefresh_Control();

    user_variable *globalUserVariable;
    user_limit    *globalUserLimit;

    sa_Measure_Control *psa_Measure_Control;
signals:
    void refreshRemote(QString);
private:
    void sendRemoteMkrCmd();
public:
#if SMALL_LARGE_PIXMAP_IMAGE
    QPixmap smallPixmap;
    QPixmap largePixmap;
    QImage  smallImage;
    QImage  largeImage;
#endif
    QPixmap mPixmap;
#if DPX_DEFINE
    QImage  mImage;
#endif
public:
    void refreshPixmap();
#if DPX_DEFINE
    void refreshImage();
#endif
#if SMALL_LARGE_PIXMAP_IMAGE
    void refreshSmallPixmap();
    void refreshLargePixmap();
    void refreshSmallImage();
    void refreshLargeImage();
#endif
    void refreshDrawPoint();
    void refreshRelativePara();
    void refreshCurves(bool bLimitCurve);
    void drawGrid(QPainter *painter);
    void drawTriggerLevel(QPainter *painter,qreal triggerLevel);
    void drawGateView(QPainter *painter);
    //***********draw measure**************
    void drawMeasureRect(QPainter *painter);
    void drawChannelPower(QPainter *painter,qint32 chpw_x,qint32 chpw_w,qreal pixelStep,qint32 gridWidth);
    void drawACPPower(QPainter *painter, qint32 chpw_x, qint32 chpw_w, qreal pixelStep, qint32 gridWidth);
    void drawMultiACPPower(QPainter *painter, qint32 chpw_x, qint32 chpw_w, qreal pixelStep, qint32 gridWidth);
    void drawOccupiedBWPower(QPainter *painter,qreal pixelStep);
    void drawSpectrumEmissionMask(QPainter *painter);
    void drawSpuriousEmission(QPainter *painter);
    //*************************************
    void drawCurves(QPainter *painter);
    void drawLimitCurves(QPainter *painter);
    void drawApplyLimitSettingSweepGraphDisplay(QPainter *painter);
    void drawLatestLimitLine(QPainter *painter);   // Limit Line Draw
    void drawLatestLimitEdge(QPainter *painter);   // Limit Edge Draw
    void judgeLimitTestResult();
#if DPX_DEFINE
    void drawColorBar(qreal dcurveValue,qint64 *uRGBValue,qint32 xPos,qint32 yPos,qint32 width,qint32 height,QPaintDevice *paintDevice,QPainter *painter = 0,quint32 uColorLevel = COLORLEVEL);
    void drawDensitymap(qreal pixelStep,qint64 *uRGBValue,QPaintDevice *paintDevice,QPainter *painter = 0,quint32 uColorLevel = COLORLEVEL,qreal dmaxDensityValue = DENSITY_MAX);
#endif
    void setTopLowLevel(qreal qTopLevel,qreal qLowLevel);
    void drawMarkerCurrentSelectInfo(QPainter *painter);
    void drawMarkers(QPainter *painter);
    void markerRefPolygonAssignNDrawFunc(QPainter *painter, qint32 pos, qint32 ArrayRefPos, qint32 drawXRefPos);
    void markerDeltaPolygonAssignNDrawFunc(QPainter *painter, qint32 pos, qint32 ArrayDeltaPos, qint32 drawXDeltaPos);
    void setPixmapSize(qint32 mWidth,qint32 mHeight);
private:
    void refreshInfo(QPainter* painter,qint32 pos,QString info);

#if DPX_DEFINE
    qreal smallPixmapPixelStep,largePixmapPixelStep;
    QVector<QPointF> smallPixmap_draw_point[NUM_TRACE],largePixmap_draw_point[NUM_TRACE];
#endif
    qreal mPixmapPixelStep;
    QVector<QPointF> mPixmap_draw_point[NUM_TRACE];
    QVector<QPointF> mSpecEMAbsLimit;
    QPoint gSpurLimit[NUM_SWEEP_POINT];
    qint32 calculatorXPos;//record the value of x when key or mouse press
    qint32 xPos[MARKER_TOTAL_CNT];// used to show the marker which was changed by knob
    QRect sweepRangeRect;
    QPoint mkrRefPoints[4];   // PolyGon 용
    QPoint mkrDeltaPoints[4];  // polyGon용
    QColor colSteelBlue;
    QColor colorMarker[2];
#if DPX_DEFINE
    qint64 uRGBValue[COLORLEVEL];
    qint32 lastTraceType[NUM_TRACE];
#endif
    bool   bDrawLimitCurve;
    //qreal  lowLevel,topLevel;
    qint32 marker_mouse_move_pos;

    void refreshSpecEMDrawPoint();
public:
    qint32 yaxis_cal(qreal level);
public:
    void mousePressReflect(qint32 x,qint32 y,bool bSmall = true);
    void mouseMoveReflect(qint32 x,qint32 y,bool bSmall = true);
    void mouseRealseReflect(qint32 x,qint32 y,bool bSmall = true);
    void keyPressReflect(qint32 keyValue,bool bSmall = true);
signals:
    void infoRefresh(qint32);
    //Johnson 190529
    //refresh acp and channel power parameter setting dialog when BW and channel spacing are recaculate
    void refreshMeasureSet();
public:
    void Delta_dbmToVoltCalculatorAndDisplayFunc(char *label, qreal _level_Delta, qreal _level_Ref);
    void Delta_dbmToWattsCalculatorAndDisplayFunc(char *label, qreal _level_Delta, qreal _level_Ref);
private:
    void judgeSpecEMTestResult();
};

#endif // SA_UIREFRESH_CONTROL_H
