/****************************************Copyright (c)****************************************************
**
**                                     INNO Instrument(China) Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                sa_uirefresh_control.cpp
** Latest Version:           V1.0.0
** Created by:               Johnson
** Created date:             2018/12/05
** Descriptions:             the class which used to define and realize the UI show
**
*********************************************************************************************************/

#include "sa_uirefresh_control.h"
#include "math.h"
#include <QThread>
#include "sa_colordef.h"
#include <QDebug>
/**
 * @brief sa_UIRefresh_Control::sa_UIRefresh_Control
 * @param m_user_variable
 * @param m_user_limit
 * @author Johnson
 */
sa_UIRefresh_Control::sa_UIRefresh_Control(user_variable &m_user_variable, user_limit &m_user_limit)
{
    firstTouch = 0;
    globalUserVariable = &m_user_variable;
    globalUserLimit    = &m_user_limit;

    psa_Measure_Control = new sa_Measure_Control(m_user_variable,m_user_limit);

#if SMALL_LARGE_PIXMAP_IMAGE
    smallPixmap = QPixmap(SMALLDRAW_WIDTH, SMALLDRAW_HEIGHT);
    smallImage = QImage(SMALLDRAW_WIDTH,SMALLDRAW_HEIGHT,QImage::Format_RGB32);
    largePixmap = QPixmap(LARGEDRAW_WIDTH, LARGEDRAW_HEIGHT);
    largeImage = QImage(LARGEDRAW_WIDTH,LARGEDRAW_HEIGHT,QImage::Format_RGB32);
#endif

    mPixmap = QPixmap(SMALLDRAW_WIDTH, SMALLDRAW_HEIGHT);
    forePixmap = QPixmap(SMALLDRAW_WIDTH, SMALLDRAW_HEIGHT);
    backPixmap = QPixmap(SMALLDRAW_WIDTH, SMALLDRAW_HEIGHT);
#if DPX_DEFINE
    mImage = QImage(SMALLDRAW_WIDTH,SMALLDRAW_HEIGHT,QImage::Format_RGB32);
#endif
//    setPixmapSize(SMALLDRAW_WIDTH,SMALLDRAW_HEIGHT);
    setPixmapSize(1198,766);

#if SMALL_LARGE_PIXMAP_IMAGE
    smallPixmapPixelStep =  (qreal) (SMALLDRAW_GRID_WIDTH - 1) / globalUserVariable->gSweepTracePoint;
    largePixmapPixelStep =  (qreal) (LARGEDRAW_GRID_WIDTH - 1) / globalUserVariable->gSweepTracePoint;
    for (qint32 t = TR1; t < NUM_TRACE; t++)
    {
        for (qint32 i = 0; i < globalUserVariable->gSweepTracePoint; i++)
        {
            smallPixmap_draw_point[t].append(QPointF( DRAW_GRID_START_X + 1 + i * smallPixmapPixelStep , SMALLDRAW_GRID_HEIGHT + DRAW_GRID_START_Y));
            largePixmap_draw_point[t].append(QPointF( DRAW_GRID_START_X + 1 + i * largePixmapPixelStep , LARGEDRAW_GRID_HEIGHT + DRAW_GRID_START_Y));
        }
    }
#endif


#if DPX_DEFINE
    lastTraceType[0] = SA_CLEAR_WRITE;
    lastTraceType[1] = SA_CLEAR_WRITE;
    lastTraceType[2] = SA_CLEAR_WRITE;
    lastTraceType[3] = SA_CLEAR_WRITE;
    lastTraceType[4] = SA_CLEAR_WRITE;
    lastTraceType[5] = SA_CLEAR_WRITE;


    for(qint32 i = 0;i<COLORLEVEL;i++){
        uRGBValue[i] = 0xffff0000;
    }
#endif
    colSteelBlue = QColor("#4682b4");
    //colSteelBlue = QColor("#80BF9F50");
    //colorMarker[0] = QColor("#FF900E");
    //colorMarker[1] = QColor("#FFFFF0");

    refreshRelativePara();
    mkrRefPoints[0].setX(0);
    mkrRefPoints[0].setY(0);

    mkrRefPoints[1].setX(0);
    mkrRefPoints[1].setY(0);

    mkrRefPoints[2].setX(0);
    mkrRefPoints[2].setY(0);

    mkrRefPoints[3].setX(0);
    mkrRefPoints[3].setY(0);

    for (qint32 i = 0; i < MARKER_TOTAL_CNT; i++)
    {
        xPos[i] = ((qint32) (globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect] * globalUserVariable->gTraceStepSize)) + DRAW_GRID_START_X;
    }

    bDrawLimitCurve = false;
    //topLevel = globalUserVariable->gRefLevel+globalUserVariable->gRefOffset;
    //lowLevel = topLevel - GRID_NUM_Y_TICKS*globalUserVariable->gScaleDiv;
    marker_mouse_move_pos = SA_NOT_USE;
    for(qint32 i = 0;i< TRACE_CNT_TOTAL;i++)
    {
        for(qint32 j = 0;j<NUM_SWEEP_POINT;j++)
        {
            mPixmap_draw_point[i].append(QPoint(0,0));   
        }
    }
    for(qint32 i = 0;i<NUM_SWEEP_POINT;i++)
    {
        mSpecEMAbsLimit.append(QPoint(0,0));
    }
}

/**
 * @brief sa_UIRefresh_Control::~sa_UIRefresh_Control
 * @author Johnson
 */
sa_UIRefresh_Control::~sa_UIRefresh_Control()
{
    delete psa_Measure_Control;
}

/**
 * @brief sa_UIRefresh_Control::setTopLowLevel
 * @param qTopLevel
 * @param qLowLevel
 * @author Johnson
 */
void sa_UIRefresh_Control::setTopLowLevel(qreal qTopLevel, qreal qLowLevel)
{
    //topLevel = qTopLevel;
    //lowLevel = qLowLevel;
}

/**
 * @brief sa_UIRefresh_Control::refreshCurves
 * @param bLimitCurve
 * @author Johnson
 */
void sa_UIRefresh_Control::refreshCurves(bool bLimitCurve)
{
    bDrawLimitCurve = bLimitCurve;
}

/**
 * @brief sa_UIRefresh_Control::refreshDrawPoint
 * @author Johnson
 */
void sa_UIRefresh_Control::refreshDrawPoint()
{
    for(int i = 0;i<NUM_TRACE;i++)
    {
        if(globalUserVariable->gTraceType[i] == SA_VIEW)
        {
            if(globalUserVariable->gViewAction[i] == SA_ON && globalUserVariable->gSweepType != SA_SINGLE)
            {
                for (int k = 0; k < globalUserVariable->gSweepTracePoint; k++)
                {
                     globalUserVariable->gTraceViewDate[i][k] = globalUserVariable->gTraceMeasureVal[i][k];
                     mPixmap_draw_point[i][k].setY(yaxis_cal(globalUserVariable->gTraceMeasureVal[i][k] + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y);//Johnson 0321
                }
                globalUserVariable->gViewAction[i] = SA_OFF;
            }
            //return;
        }
        else
        {
            for (int k = 0; k < globalUserVariable->gSweepTracePoint; k++)
            {
                mPixmap_draw_point[i][k].setY(yaxis_cal(globalUserVariable->gTraceMeasureVal[i][k] + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y);//Johnson 0321
            }
        }
    }
}
/**
 * @brief sa_UIRefresh_Control::refreshRelativePara
 * @note refresh all relative parameter
 * @author Johnson
 */
void sa_UIRefresh_Control::refreshRelativePara()
{
#if SMALL_LARGE_PIXMAP_IMAGE
    if(globalUserVariable->bSmallCanvas)
    {
        SA_guiDrawSet.gridHorStep = SMALLDRAW_GRID_WIDTH  /  GRID_NUM_X_TICKS;
        SA_guiDrawSet.gridVerStep = SMALLDRAW_GRID_HEIGHT /  GRID_NUM_Y_TICKS;
        sweepRangeRect  = {DRAW_GRID_START_X, DRAW_GRID_START_Y, SMALLDRAW_GRID_WIDTH, SMALLDRAW_GRID_HEIGHT };

        globalUserLimit->gridAxisCalculatorFunc();
        globalUserVariable->gTraceStepSize = (qreal)  SMALLDRAW_GRID_WIDTH /  (qreal)  (globalUserVariable->gSweepTracePoint - 1);
    }
    else
    {
        SA_guiDrawSet.gridHorStep = LARGEDRAW_GRID_WIDTH  /  GRID_NUM_X_TICKS;
        SA_guiDrawSet.gridVerStep = LARGEDRAW_GRID_HEIGHT /  GRID_NUM_Y_TICKS;
        sweepRangeRect  = {DRAW_GRID_START_X, DRAW_GRID_START_Y, LARGEDRAW_GRID_WIDTH, LARGEDRAW_GRID_HEIGHT };

        globalUserLimit->gridAxisCalculatorFunc();
        globalUserVariable->gTraceStepSize = (qreal)  LARGEDRAW_GRID_WIDTH /  (qreal)  (globalUserVariable->gSweepTracePoint - 1);
    }
#endif
    SA_guiDrawSet.gridHorStep = (qreal)(mPixmap.width()-SA_LEFTDIS -SA_RIGHTDIS)  /  GRID_NUM_X_TICKS;
    SA_guiDrawSet.gridVerStep = (qreal)(mPixmap.height()-SA_TOPDIS - SA_BOTTOMDIS) /  GRID_NUM_Y_TICKS;

    //sweepRangeRect  = {DRAW_GRID_START_X, DRAW_GRID_START_Y, mPixmap.width()-SA_LEFTDIS -SA_RIGHTDIS,mPixmap.height()-SA_TOPDIS - SA_BOTTOMDIS };
    sweepRangeRect = QRect(DRAW_GRID_START_X, DRAW_GRID_START_Y, mPixmap.width()-SA_LEFTDIS -SA_RIGHTDIS,mPixmap.height()-SA_TOPDIS - SA_BOTTOMDIS);

    globalUserLimit->gridAxisCalculatorFunc();
    globalUserVariable->gTraceStepSize = (qreal)  (mPixmap.width()-SA_LEFTDIS -SA_RIGHTDIS) /  (qreal)  (globalUserVariable->gSweepTracePoint - 1);
}

#if SMALL_LARGE_PIXMAP_IMAGE
/**
 * @brief sa_UIRefresh_Control::refreshSmallPixmap
 * @author Johnson
 */
void sa_UIRefresh_Control::refreshSmallPixmap()
{
    refreshDrawPoint();

    smallPixmap.fill(Qt::black);
    QPainter painter(&smallPixmap);
    drawGrid(&painter);
    drawMeasureRect(&painter);
    if(!bDrawLimitCurve) drawCurves(&painter);
    else drawLimitCurves(&painter);
    if (globalUserVariable->gMarkerDisplay == MKR_ONLY && SA_guiDrawSet.markerOnCount != 0
        && globalUserVariable->gTraceView[globalUserVariable->gTraceSelect] != SA_OFF)
    {
        drawMarkerCurrentSelectInfo(&painter);
    }
    if(SA_guiDrawSet.markerOnCount != 0 && globalUserVariable->gTraceView[globalUserVariable->gTraceSelect] != SA_OFF)
    {
//        emit refreshMarker();
    }
    drawMarkers(&painter);
}

/**
 * @brief sa_UIRefresh_Control::refreshLargePixmap
 * @author Johnson
 */
void sa_UIRefresh_Control::refreshLargePixmap()
{
    refreshDrawPoint();

    largePixmap.fill(Qt::black);
    QPainter painter(&largePixmap);
    drawGrid(&painter);
    drawMeasureRect(&painter);
    if(!bDrawLimitCurve) drawCurves(&painter);
    else drawLimitCurves(&painter);
    if (globalUserVariable->gMarkerDisplay == MKR_ONLY && SA_guiDrawSet.markerOnCount != 0
        && globalUserVariable->gTraceView[globalUserVariable->gTraceSelect] != SA_OFF)
    {
        drawMarkerCurrentSelectInfo(&painter);
    }
    drawMarkers(&painter);
}

/**
 * @brief sa_UIRefresh_Control::refreshSmallImage
 * @author Johnson
 */
void sa_UIRefresh_Control::refreshSmallImage()
{
    refreshDrawPoint();
}

/**
 * @brief sa_UIRefresh_Control::refreshLargeImage
 * @author Johnson
 */
void sa_UIRefresh_Control::refreshLargeImage()
{
    refreshDrawPoint();
}
#endif

/**
 * @brief sa_UIRefresh_Control::refreshPixmap
 * @author Johnson
 */
void sa_UIRefresh_Control::refreshPixmap()
{
    qint32 colorMode = globalUserVariable->gDisplayMode;
    QColor mBackgroundColor = BackgroundColor[colorMode];

    refreshDrawPoint();
    mPixmap.fill(mBackgroundColor);
    QPainter painter(&mPixmap);
    drawGrid(&painter);
    drawMeasureRect(&painter);
    /*Tony 0729 zero span no limit*/
    if(globalUserVariable->gZeroSpanAction || !bDrawLimitCurve)
        drawCurves(&painter);
    else
        drawLimitCurves(&painter);
#ifdef SAMPLE_LIMIT
    if(globalUserVariable->currentMode != SA_SPAN_MODE)
    {
        if(globalUserLimit->gUpperLimitStatus || globalUserLimit->gLowerLimitStatus || globalUserLimit->gATLdBcLimitStatus)
        {
                judgeSampleLimitTestResult();
                drawSampleLimit(&painter);
        }
    }
#endif
    if (/*globalUserVariable->gMarkerDisplay == MKR_ONLY && */SA_guiDrawSet.markerOnCount != 0
        && globalUserVariable->gTraceView[globalUserVariable->gTraceSelect] != SA_OFF)
    {
        drawMarkerCurrentSelectInfo(&painter);
    }
    if(SA_guiDrawSet.markerOnCount != 0 && globalUserVariable->gTraceView[globalUserVariable->gTraceSelect] != SA_OFF)
    {
        emit infoRefresh(SA_INFO_MARKER_VALUE);
    }
    drawMarkers(&painter);
    if( globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE && globalUserVariable->gMsComplete && !globalUserVariable->gMsFirstFlag)
    {
        //judgeSpecEMTestResult();
    }

    //Johnson 190909
#if !AFTERGATESWEEPCHANGED
    if(globalUserVariable->gTriggerMode == SA_TRIGGER_VIDEO || globalUserVariable->gTriggerMode == SA_TRIGGER_RF_BURST ||
       ((globalUserVariable->gDrCtrlSource == SA_RFBURST_TRIGGER) &&
        (globalUserVariable->gGateViewStatus == SA_GATE_VIEW_OPEN || globalUserVariable->gDrCtrlSwitch == SA_OPEN_DCSWEEP)))
#else
    if(globalUserVariable->gTriggerMode == SA_TRIGGER_VIDEO || globalUserVariable->gTriggerMode == SA_TRIGGER_RF_BURST)
#endif
    {
        qreal trigLevel = 0.;
        if(globalUserVariable->gTriggerMode == SA_TRIGGER_VIDEO || globalUserVariable->gTriggerMode == SA_TRIGGER_RF_BURST)
        {
            trigLevel = globalUserVariable->gTriggerLevel[globalUserVariable->gTriggerMode];
        }
        else
        {
            trigLevel = globalUserVariable->gRFBurstTrigLevel;
        }
        drawTriggerLevel(&painter,trigLevel);
    }

    //Johnson 190912
    if(globalUserVariable->gLvlEdgSelect == SA_EDGE_MODE && globalUserVariable->gGateViewStatus == SA_GATE_VIEW_OPEN)
    {
        drawGateView(&painter);
    }
    return ;
}

/**
 * @brief sa_UIRefresh_Control::drawTriggerLevel
 * @param painter
 * @author Johnson
 * @date 09-09-2019
 */
void sa_UIRefresh_Control::drawTriggerLevel(QPainter *painter, qreal triggerLevel)
{
    //JOhnson 191014
    static qreal tmpTrigLevel = 30.;
    static qreal y = 0.;

    painter->save();

    QPen pen(QColor(255,0,0));
    painter->setPen(pen);

    QFont font("Arial", 9);
    pen.setWidth(2);
    painter->setPen(pen);
    font.setPointSize(12);
    font.setBold(true);
    painter->setFont(font);

    //Johnson 191014
    if(tmpTrigLevel != triggerLevel)
    {
        tmpTrigLevel = triggerLevel;
        y = yaxis_cal(triggerLevel) + DRAW_GRID_START_Y;
    }

    QFontMetrics fm = painter->fontMetrics();
    qint32 height = fm.height();
    if(y <= DRAW_GRID_START_Y + height)
    {
        painter->drawText(DRAW_GRID_START_X + 5,y + 15,QString("Trig Level = %1 dBm").arg(triggerLevel));
    }
    else if(y >= globalUserVariable->gridXPos[10] - height)
    {
        painter->drawText(DRAW_GRID_START_X + 5,y - 5,QString("Trig Level = %1 dBm").arg(triggerLevel));
    }
    else
    {
        painter->drawText(DRAW_GRID_START_X + 5,y - 5,QString("Trig Level = %1 dBm").arg(triggerLevel));
    }
    painter->drawLine(DRAW_GRID_START_X, y, (globalUserVariable->gridXPos[10]), y);

    painter->restore();
}

/**
 * @brief sa_UIRefresh_Control::drawGateView
 * @param painter
 */
void sa_UIRefresh_Control::drawGateView(QPainter *painter)
{
    qint32 startXIndex = (qint32)NUM_SWEEP_POINT * globalUserVariable->gEdgTrigDely/globalUserVariable->gSweepTime;
    qint32 stopXIndex = (qint32)NUM_SWEEP_POINT * (globalUserVariable->gEdgTrigDoorWdth + globalUserVariable->gEdgTrigDely)/globalUserVariable->gSweepTime;
    if(startXIndex > NUM_SWEEP_POINT - 1) startXIndex = NUM_SWEEP_POINT - 1;
    if(stopXIndex > NUM_SWEEP_POINT - 1) stopXIndex = NUM_SWEEP_POINT - 1;
    qreal startXPos = mPixmap_draw_point[globalUserVariable->gTraceSelect].at(startXIndex).x();
    qreal stopXPos = mPixmap_draw_point[globalUserVariable->gTraceSelect].at(stopXIndex).x();

    painter->save();

    QPen pen(QColor(0,255,0));
    painter->setPen(pen);
    QFont font("Arial", 9);
    painter->setFont(font);

    pen.setWidth(2);
    painter->setPen(pen);
    font.setPointSize(12);
    font.setBold(true);
    painter->setFont(font);

    QFontMetrics fm = painter->fontMetrics();
    qint32 startTextLength = fm.width(QString("Gate Start"));
    qint32 stopTextLength  = fm.width(QString("Gate Stop"));
    qint32 height = fm.height();

    painter->drawLine(startXPos,DRAW_GRID_START_Y,startXPos,globalUserVariable->gridYPos[10]);
    painter->drawLine(stopXPos,DRAW_GRID_START_Y,stopXPos,globalUserVariable->gridYPos[10]);

    if(startXPos + startTextLength >= globalUserVariable->gridXPos[10])
        startXPos = globalUserVariable->gridXPos[10] - startTextLength - 10;
    if(stopXPos + stopTextLength >= globalUserVariable->gridXPos[10])
        stopXPos = globalUserVariable->gridXPos[10] - stopTextLength - 10;
    //painter->drawText(startXPos + 5,DRAW_GRID_START_Y + 30,QString("Gate Start"));
    painter->drawText(startXPos + 5,DRAW_GRID_START_Y + 50,QString("Gate Delay"));
    painter->drawText(startXPos + 5,DRAW_GRID_START_Y + height + 60,globalUserVariable->TimeTransformToQstring(globalUserVariable->gEdgTrigDely));
    //painter->drawText(stopXPos + 5,DRAW_GRID_START_Y + 100,QString("Gate Stop"));
    painter->drawText(stopXPos + 5,DRAW_GRID_START_Y + 100,QString("Gate Length"));
    painter->drawText(stopXPos + 5,DRAW_GRID_START_Y + height + 110,globalUserVariable->TimeTransformToQstring(globalUserVariable->gEdgTrigDoorWdth));

    painter->restore();
}

#if DPX_DEFINE
/**
 * @brief sa_UIRefresh_Control::refreshImage
 * @author Johnson
 */
void sa_UIRefresh_Control::refreshImage()
{
    refreshDrawPoint();
}
#endif

/**
 * @brief sa_UIRefresh_Control::drawGrid
 * @param painter
 * @note  draw grid
 * @author Johnson
 */
void sa_UIRefresh_Control::drawGrid(QPainter *painter)
{
  qint32 colorMode = globalUserVariable->gDisplayMode;
  QColor mGridColor[2] = GridColor[colorMode];
  QColor mFontColor = infoFontColor[colorMode];
  QColor mScaleColor = ScaleColor[colorMode];
  QPen mpen(mFontColor);
  mpen.setWidth(1);
  QString strSacale,strRefLvl,strRBW,strSweepTime;
  qreal value;
  painter->setPen(mpen);

  refreshInfo(painter,SA_TOP_CENTER,SA_MeasureName[globalUserVariable->currentMode]);
  if(!globalUserVariable->gSpanFreq)
  {
      refreshInfo(painter,SA_BOTTOM_CENTER,"Time");
  }else
  {
    refreshInfo(painter,SA_BOTTOM_CENTER,"Frequency");
  }

  value = globalUserVariable->gScaleDiv;
  strSacale.sprintf("%.2f dB/Div",value);
  refreshInfo(painter,SA_TOP_LEFT_SEC,"Scale " + strSacale);

  value = globalUserVariable->gRefLevel;
  strRefLvl = globalUserVariable->amptTransformToQstring(globalUserVariable->gAmptdUnit,value);
  refreshInfo(painter,SA_TOP_LEFT,"Ref Level " + strRefLvl);

  value = globalUserVariable->gRbw;
  strRBW = globalUserVariable->freqValueToQstring(value);
  refreshInfo(painter,SA_BOTTOM_LEFT_SEC,"RBW "+strRBW);

  value = globalUserVariable->gSweepTime;
  strSweepTime = globalUserVariable->TimeTransformToQstring(value);
  refreshInfo(painter,SA_BOTTOM_RIGHT_SEC,"Sweep Time "+strSweepTime);



  char label[20];
  memset(label,0,sizeof(char)*20);

  int unitNo = 0;
  qreal f64BaseLevel = globalUserVariable->gRefLevel + globalUserVariable->gRefOffset;
  qreal f64DbmGab = 0;

  int pos;
  QString strValue;
  QString strTitle;
  QString strGab;

  QString strAmptd;
  QString strAmptdUnit;

  int i = 0;

  QFontMetrics fm = painter->fontMetrics();

  QPen pen(mGridColor[0]);
  pen.setWidth(2);

#if 0
  qint32 startX ;
  qint32 startY = mPixmap.height()-30;
  qint32 width;
  qint32 height = 15;
#endif
  for (i = 0; i < GRIDY_LENGTH; i++)
    {
        if (i == 0)
        {
            painter->setPen(pen);   // QColor/QPen
            painter->drawLine(DRAW_GRID_START_X -1, globalUserVariable->gridYPos[i]-1, (globalUserVariable->gridXPos[10] + 2), globalUserVariable->gridYPos[i]-1);
        }else if(i == GRIDY_LENGTH - 1)
        {
            painter->setPen(pen);   // QColor/QPen
            painter->drawLine(DRAW_GRID_START_X -1, globalUserVariable->gridYPos[i]+2, (globalUserVariable->gridXPos[10] + 2), globalUserVariable->gridYPos[i]+2);
        }
        else
        {

            painter->setPen(mGridColor[1]);
            //painter->setPen(Qt::darkGray);   // QColor/QPen
            painter->drawLine(DRAW_GRID_START_X, globalUserVariable->gridYPos[i], (globalUserVariable->gridXPos[10]), globalUserVariable->gridYPos[i]);
        }
    }
    for (i = 0; i < GRIDX_LENGTH; i++)
    {
        if (i == 0 )
        {
            painter->setPen(pen);   // QColor/QPen
            painter->drawLine(globalUserVariable->gridXPos[i]-1, DRAW_GRID_START_Y, globalUserVariable->gridXPos[i]-1, globalUserVariable->gridYPos[10]);
        }else if(i == GRIDX_LENGTH - 1)
        {
            painter->setPen(pen);   // QColor/QPen
            painter->drawLine(globalUserVariable->gridXPos[i]+2, DRAW_GRID_START_Y, globalUserVariable->gridXPos[i]+2, globalUserVariable->gridYPos[10]);
        }
        else
        {
            painter->setPen(mGridColor[1]);  // QColor/QPen
            painter->drawLine(globalUserVariable->gridXPos[i], DRAW_GRID_START_Y, globalUserVariable->gridXPos[i], globalUserVariable->gridYPos[10]);
        }
  #if 0
        if(globalUserVariable->bSmallCanvas)
        {
            painter->drawLine(globalUserVariable->gridXPos[i], DRAW_GRID_START_Y + 1, globalUserVariable->gridXPos[i], globalUserVariable->gridYPos[10] - 1);
        }
        else
        {
            painter->drawLine(globalUserVariable->gridXPos[i], DRAW_GRID_START_Y + 1, globalUserVariable->gridXPos[i], globalUserVariable->gridYPos[10] - 1);
        }
  #else
  //      painter->drawLine(globalUserVariable->gridXPos[i], DRAW_GRID_START_Y/* + 1*/, globalUserVariable->gridXPos[i], globalUserVariable->gridYPos[10]/* - 1*/);
  #endif
    }

  painter->setPen(mScaleColor);
  if (globalUserVariable->gAmptdUnit == SA_WATTS || globalUserVariable->gAmptdUnit == SA_VOLT )
    painter->setFont(QFont("Arial", 9));
  else
    painter->setFont(QFont("Arial", 9));


  //Johnson 0917 Change
  for (i = 0; i < GRIDY_LENGTH; i++)
  {
      f64DbmGab = f64BaseLevel - (qreal)(i * globalUserVariable->gScaleDiv);

      switch(globalUserVariable->gAmptdUnit)
      {
        case SA_DBM:
          sprintf(label, "%.2f", f64DbmGab);
          break;
        case SA_DBV:
          sprintf(label, "%.2f", f64DbmGab + dBVFix);
          break;
        case SA_DBMV:
          sprintf(label, "%.2f", f64DbmGab + dBmVFix);
          break;
        case SA_DBUV:
          sprintf(label, "%.2f", f64DbmGab + dBuVFix);
          break;
        case SA_VOLT:
          globalUserVariable->dbmToVoltCalculatorAndDisplayFunc(label, f64DbmGab);
          break;
        case SA_WATTS:
          globalUserVariable->dbmToWattsCalculatorAndDisplayFunc(label, f64DbmGab);
          break;
      }

      switch(globalUserVariable->gAmptdUnit)
      {
      case SA_DBM:
      case SA_DBV:
      case SA_DBMV:
      case SA_DBUV:
          if (i == 0)
              painter->drawText(DRAW_AMPTD_LBL_START_X, globalUserVariable->gridYPos[i], DRAW_AMPTD_LBL_WIDTH, DRAW_AMPTD_LBL_HEIGHT, Qt::AlignRight, label);
          else if (i == GRIDY_LENGTH-1)
              painter->drawText(DRAW_AMPTD_LBL_START_X, globalUserVariable->gridYPos[i] - 15, DRAW_AMPTD_LBL_WIDTH, DRAW_AMPTD_LBL_HEIGHT, Qt::AlignRight, label);
          else
              painter->drawText(DRAW_AMPTD_LBL_START_X, globalUserVariable->gridYPos[i] - 6 , DRAW_AMPTD_LBL_WIDTH, DRAW_AMPTD_LBL_HEIGHT, Qt::AlignRight, label);
          break;
      case SA_VOLT:
      case SA_WATTS:
          globalUserVariable->charEmptySplitWorkerFunc(label);
          strAmptd = QString(SA_watts_unit.value);
          strAmptdUnit = QString(SA_watts_unit.unit);

          if (i == 0)
          {
              painter->drawText(DRAW_AMPTD_LBL_START_X, globalUserVariable->gridYPos[i], DRAW_AMPTD_LBL_WIDTH, DRAW_AMPTD_LBL_HEIGHT, Qt::AlignRight, strAmptd);
              painter->drawText(DRAW_AMPTD_LBL_START_X, globalUserVariable->gridYPos[i] + fm.height(), DRAW_AMPTD_LBL_WIDTH, DRAW_AMPTD_LBL_HEIGHT, Qt::AlignRight, strAmptdUnit);
          }
          else if (i == GRIDY_LENGTH-1)
          {
            painter->drawText(DRAW_AMPTD_LBL_START_X, globalUserVariable->gridYPos[i] - 15, DRAW_AMPTD_LBL_WIDTH, DRAW_AMPTD_LBL_HEIGHT, Qt::AlignRight, strAmptd);
            painter->drawText(DRAW_AMPTD_LBL_START_X, globalUserVariable->gridYPos[i] - 15  + fm.height(), DRAW_AMPTD_LBL_WIDTH, DRAW_AMPTD_LBL_HEIGHT, Qt::AlignRight, strAmptdUnit);
          }
          else
          {
            painter->drawText(DRAW_AMPTD_LBL_START_X, globalUserVariable->gridYPos[i] - 6 , DRAW_AMPTD_LBL_WIDTH, DRAW_AMPTD_LBL_HEIGHT, Qt::AlignRight, strAmptd);
            painter->drawText(DRAW_AMPTD_LBL_START_X, globalUserVariable->gridYPos[i] - 6  + fm.height() , DRAW_AMPTD_LBL_WIDTH, DRAW_AMPTD_LBL_HEIGHT, Qt::AlignRight, strAmptdUnit);
          }
          break;
      }
  }
  painter->setPen(mFontColor);
  painter->setFont(QFont("Arial", 10));

  if (/*globalUserVariable->PrimaryAction == SA_FREQUENCY && */globalUserVariable->SecondaryAction == SA_SPAN)//Johnson 0717Afternoon
  {
      qint32 minus = 0;
      qreal freq = (qreal)globalUserVariable->gCenterFreq  + globalUserVariable->gfreqOffset;
      if(freq < 0)
      {
          freq = -1 * freq;
          minus = 1;
      }
#if 0
      startX = DRAW_GRID_START_X;
      width = SA_WORDWITH;
#endif
      unitNo = globalUserVariable->freqUnitFindProc(freq);
      strGab = QString::number(freq, 'd',0);
      pos = globalUserVariable->notZeroPositionFindFunc(strGab);

      strValue = globalUserVariable->freqDotNumberDisplayFormatFixFunc (freq, unitNo, pos );
      if(minus) strValue = "-" + strValue;
      strTitle = QString("%1 %2").arg("Center Freq ").arg(strValue);
#if 0
      painter->drawText(startX, startY , width, height, Qt::AlignLeft, strTitle);
#else
      refreshInfo(painter,SA_BOTTOM_LEFT,strTitle);
#endif
      if (globalUserVariable->gZeroSpanAction )
      {
          strTitle = QString("%1 %2").arg("Span ").arg("Zero Span");
      } else
      {
          unitNo = 0;
          unitNo = globalUserVariable->freqUnitFindProc(globalUserVariable->gSpanFreq);

          strGab = QString::number(globalUserVariable->gSpanFreq, 'd',0);
          pos = globalUserVariable->notZeroPositionFindFunc(strGab);
          strValue = globalUserVariable->freqDotNumberDisplayFormatFixFunc (globalUserVariable->gSpanFreq, unitNo, pos );
          strTitle = QString("%1 %2").arg("Span ").arg(strValue);
      }
#if 0
      if(globalUserVariable->bSmallCanvas)
          painter->drawText((DRAW_GRID_START_X + SMALLDRAW_GRID_WIDTH) - 200, globalUserVariable->gridYPos[GRIDY_LENGTH-1] + 5, 200, 20, Qt::AlignRight, strTitle);
      else
          painter->drawText((DRAW_GRID_START_X + LARGEDRAW_GRID_WIDTH) - 200, globalUserVariable->gridYPos[GRIDY_LENGTH-1] + 5, 200, 20, Qt::AlignRight, strTitle);
      width = SA_WORDWITH;
      startX = globalUserVariable->gridXPos[GRIDY_LENGTH-1] -width;
#else
      refreshInfo(painter,SA_BOTTOM_RIGHT,strTitle);
#endif
  }
  else   // Start Freq & Stop Freq
  {
      qint32 minus = 0;
      qreal freq = (qreal)globalUserVariable->gStartFreq  + globalUserVariable->gfreqOffset;
      if(freq < 0)
      {
          freq = -1 * freq;
          minus = 1;
      }
      unitNo = globalUserVariable->freqUnitFindProc(freq);

      strGab = QString::number(freq, 'd',0);
      pos = globalUserVariable->notZeroPositionFindFunc(strGab);
      strValue = globalUserVariable->freqDotNumberDisplayFormatFixFunc (freq, unitNo, pos );
      if(minus) strValue = "-" + strValue;
      strTitle = QString("%1 %2").arg("Start Freq ").arg(strValue);
#if 0
      //strTitle.setPattern("(\\.){0,1}0+$");
      startX = DRAW_GRID_START_X;
      width = SA_WORDWITH;
      painter->drawText(startX, startY, width, height, Qt::AlignLeft, strTitle);
#else
      refreshInfo(painter,SA_BOTTOM_LEFT,strTitle);
#endif
      minus = 0;
      freq = (qreal)globalUserVariable->gStopFreq  + globalUserVariable->gfreqOffset;
      if(freq < 0)
      {
          freq = -1 * freq;
          minus = 1;
      }
      unitNo = 0;
      unitNo = globalUserVariable->freqUnitFindProc(freq);

      strGab = QString::number(freq, 'd',0);
      pos = globalUserVariable->notZeroPositionFindFunc(strGab);
      strValue = globalUserVariable->freqDotNumberDisplayFormatFixFunc (freq, unitNo, pos );
      if(minus) strValue = "-" + strValue;
      strTitle = QString("%1 %2").arg("Stop Freq ").arg(strValue);

#if 0
      if(globalUserVariable->bSmallCanvas)
          painter->drawText((DRAW_GRID_START_X + SMALLDRAW_GRID_WIDTH) - 200, globalUserVariable->gridYPos[GRIDY_LENGTH-1] + 5, 200, 20, Qt::AlignRight, strTitle);
      else
          painter->drawText((DRAW_GRID_START_X + LARGEDRAW_GRID_WIDTH) - 200, globalUserVariable->gridYPos[GRIDY_LENGTH-1] + 5, 200, 20, Qt::AlignRight, strTitle);
      width = SA_WORDWITH;
      startX = globalUserVariable->gridXPos[GRIDY_LENGTH-1] -width;
#endif
#if 1
      refreshInfo(painter,SA_BOTTOM_RIGHT,strTitle);
#else
      painter->drawText(startX, startY, width, height, Qt::AlignRight, strTitle);
#endif
  }
}

/**
 * @brief sa_UIRefresh_Control::drawChannelPower
 * @param painter
 * @param pixelStep
 * @param gridWidth
 * @author Johnson 200511
 */
void sa_UIRefresh_Control::drawChannelPower(QPainter *painter, qreal pixelStep, qint32 gridWidth)
{
    qreal dPowerValue = 0.;
    qint32 y;
    QString powerValue;
    QFontMetrics fm = painter->fontMetrics();

    dPowerValue = psa_Measure_Control->calculatePower(DRAW_GRID_START_X + globalUserVariable->CP_Left_X,globalUserVariable->CP_W,gridWidth,pixelStep,globalUserVariable->gChannelBandwidth);//Johnson 0801
    globalUserVariable->dPowerValue = dPowerValue;
    globalUserVariable->dPSD = dPowerValue - 10 * log10( globalUserVariable->gChannelBandwidth );
    //globalUserVariable->dPSD = dPowerValue - 10 * log10((qreal)globalUserVariable->gChannelBandwidth/globalUserVariable->gSpanFreq * globalUserVariable->gChannelBandwidth);
    //Johnson 0813
    y = yaxis_cal(dPowerValue + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y + 1;
    painter->fillRect(DRAW_GRID_START_X + globalUserVariable->CP_Left_X, y, globalUserVariable->CP_W, globalUserVariable->gridYPos[10] - y + 1, colSteelBlue);

    //******************Johnson 0815 draw line begin**************
    painter->setPen(Qt::white);
    if(globalUserVariable->CP_Left_X != 0)
        painter->drawLine(DRAW_GRID_START_X+globalUserVariable->CP_Left_X, DRAW_GRID_START_Y,
                          DRAW_GRID_START_X+globalUserVariable->CP_Left_X,globalUserVariable->gridYPos[10]);
    if(globalUserVariable->CP_Left_X+globalUserVariable->CP_W != gridWidth)
        painter->drawLine(DRAW_GRID_START_X+globalUserVariable->CP_Left_X+globalUserVariable->CP_W,DRAW_GRID_START_Y,
                          DRAW_GRID_START_X+globalUserVariable->CP_Left_X+globalUserVariable->CP_W,globalUserVariable->gridYPos[10]);
    //Johnson 0815 draw arrow line
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->CP_Left_X , DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5 ,
                      fm.width("<"), fm.height(), Qt::AlignLeft, "<");
    painter->drawLine(DRAW_GRID_START_X+globalUserVariable->CP_Left_X , DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5+fm.height()/2,
                      DRAW_GRID_START_X+globalUserVariable->CP_W+globalUserVariable->CP_Left_X, DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5+fm.height()/2);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->CP_Left_X+globalUserVariable->CP_W-fm.width(">") , DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5 ,
                      fm.width("<"), fm.height(), Qt::AlignLeft, ">");
    //Johnson 0815 draw dbm value
    powerValue = QString::number(dPowerValue,'f',2);
    painter->setPen(Qt::green);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->CP_Left_X+globalUserVariable->CP_W/2-fm.width(powerValue)/2,
                      DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5-fm.height()/2,fm.width(powerValue),fm.height(),Qt::AlignLeft,powerValue);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->CP_Left_X+globalUserVariable->CP_W/2-fm.width("dBm")/2,
                      DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5+fm.height()/2,fm.width("dBm"),fm.height(),Qt::AlignLeft,"dBm");
}

#if EXCHANGE_ACPMULTIACP
/**
 * @brief sa_UIRefresh_Control::drawACPPower
 * @param painter
 * @param pixelStep
 * @param gridWidth
 * @author Johnson
 * @date 02-26-2020
 */
void sa_UIRefresh_Control::drawACPPower(QPainter *painter, qreal pixelStep, qint32 gridWidth)
{
    //gridWidth is index,the following vars are index too

    qreal Lowest_MainCh_Power = 0.,Highest_MainCh_Power = 0.,
            Lowest_ADJCh_Power = 0.,Highest_ADJCh_Power = 0.,
            Lowest_ALTCh_Power = 0.,Highest_ALTCh_Power = 0.;
    qint32 Lowest_MainCh_y,Highest_MainCh_y,
                 Lowest_ADJCh_y,Highest_ADJCh_y,
                 Lowest_ALTCh_y,Highest_ALTCh_y;

    QFontMetrics fm = painter->fontMetrics();

    //Johnson 20200227
    Lowest_MainCh_Power  = psa_Measure_Control->calculatePower(DRAW_GRID_START_X + globalUserVariable->MultiACP_Lowest_MainCh_x,globalUserVariable->MultiACP_MainCh_w,
                                                               mPixmap.width(),pixelStep,globalUserVariable->gMainIntegBW);
    Lowest_ADJCh_Power   = psa_Measure_Control->calculatePower(DRAW_GRID_START_X + globalUserVariable->MultiACP_Lowest_ADJCh_x,globalUserVariable->MultiACP_ADJCh_w,
                                                             mPixmap.width(),pixelStep,globalUserVariable->gADJIntegBW);
    Lowest_ALTCh_Power   = psa_Measure_Control->calculatePower(DRAW_GRID_START_X + globalUserVariable->MultiACP_Lowest_ALTCh_x,globalUserVariable->MultiACP_ALTCh_w,
                                                              mPixmap.width(),pixelStep,globalUserVariable->gALTIntegBW);
    Highest_MainCh_Power = psa_Measure_Control->calculatePower(DRAW_GRID_START_X + globalUserVariable->MultiACP_Highest_MainCh_x,globalUserVariable->MultiACP_MainCh_w,
                                                               mPixmap.width(),pixelStep,globalUserVariable->gMainIntegBW);
    Highest_ADJCh_Power  = psa_Measure_Control->calculatePower(DRAW_GRID_START_X + globalUserVariable->MultiACP_Highest_ADJCh_x,globalUserVariable->MultiACP_ADJCh_w,
                                                               mPixmap.width(),pixelStep,globalUserVariable->gADJIntegBW);
    Highest_ALTCh_Power  = psa_Measure_Control->calculatePower(DRAW_GRID_START_X + globalUserVariable->MultiACP_Highest_ALTCh_x,globalUserVariable->MultiACP_ALTCh_w,
                                                               mPixmap.width(),pixelStep,globalUserVariable->gALTIntegBW);

    globalUserVariable->dLowest_MainCh_Power   = Lowest_MainCh_Power;
    globalUserVariable->dLowest_ADJCh_Power    = Lowest_ADJCh_Power;
    globalUserVariable->dLowest_ALTCh_Power    = Lowest_ALTCh_Power;
    globalUserVariable->dHighest_MainCh_Power  = Highest_MainCh_Power;
    globalUserVariable->dHighest_ADJCh_Power   = Highest_ADJCh_Power;
    globalUserVariable->dHighest_ALTCh_Power   = Highest_ALTCh_Power;


    //Johnson 20200227
    Lowest_MainCh_y = yaxis_cal(Lowest_MainCh_Power + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y + 1;
    Lowest_ADJCh_y = yaxis_cal(Lowest_ADJCh_Power + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y + 1;
    Lowest_ALTCh_y = yaxis_cal(Lowest_ALTCh_Power + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y + 1;
    Highest_MainCh_y = yaxis_cal(Highest_MainCh_Power + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y + 1;
    Highest_ADJCh_y = yaxis_cal(Highest_ADJCh_Power + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y + 1;
    Highest_ALTCh_y = yaxis_cal(Highest_ALTCh_Power + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y + 1;

    painter->fillRect(DRAW_GRID_START_X + globalUserVariable->MultiACP_Lowest_ALTCh_x, Lowest_ALTCh_y,
                      globalUserVariable->MultiACP_ALTCh_w, globalUserVariable->gridYPos[10]- Lowest_ALTCh_y + 1, colSteelBlue);
    painter->fillRect(DRAW_GRID_START_X + globalUserVariable->MultiACP_Lowest_ADJCh_x, Lowest_ADJCh_y,
                      globalUserVariable->MultiACP_ADJCh_w, globalUserVariable->gridYPos[10]- Lowest_ADJCh_y + 1, colSteelBlue);
    painter->fillRect(DRAW_GRID_START_X + globalUserVariable->MultiACP_Lowest_MainCh_x, Lowest_MainCh_y,
                      globalUserVariable->MultiACP_MainCh_w, globalUserVariable->gridYPos[10]- Lowest_MainCh_y + 1, colSteelBlue);
    painter->fillRect(DRAW_GRID_START_X + globalUserVariable->MultiACP_Highest_MainCh_x, Highest_MainCh_y,
                      globalUserVariable->MultiACP_MainCh_w, globalUserVariable->gridYPos[10]- Highest_MainCh_y + 1, colSteelBlue);
    painter->fillRect(DRAW_GRID_START_X + globalUserVariable->MultiACP_Highest_ADJCh_x, Highest_ADJCh_y,
                      globalUserVariable->MultiACP_ADJCh_w, globalUserVariable->gridYPos[10]- Highest_ADJCh_y + 1, colSteelBlue);
    painter->fillRect(DRAW_GRID_START_X + globalUserVariable->MultiACP_Highest_ALTCh_x, Highest_ALTCh_y,
                      globalUserVariable->MultiACP_ALTCh_w, globalUserVariable->gridYPos[10]- Highest_ALTCh_y + 1, colSteelBlue);

    //************************Johnson 20200227 draw line***************************************
    //********draw Lowest Main begin***********
    painter->setPen(Qt::white);
    if(globalUserVariable->MultiACP_Lowest_MainCh_x != 0)
        painter->drawLine(DRAW_GRID_START_X+globalUserVariable->MultiACP_Lowest_MainCh_x,DRAW_GRID_START_Y,
                          DRAW_GRID_START_X+globalUserVariable->MultiACP_Lowest_MainCh_x,globalUserVariable->gridYPos[10]);
    if(globalUserVariable->MultiACP_Lowest_MainCh_x+globalUserVariable->MultiACP_MainCh_w != gridWidth)
        painter->drawLine(DRAW_GRID_START_X+globalUserVariable->MultiACP_Lowest_MainCh_x+globalUserVariable->MultiACP_MainCh_w,DRAW_GRID_START_Y,
                          DRAW_GRID_START_X+globalUserVariable->MultiACP_Lowest_MainCh_x+globalUserVariable->MultiACP_MainCh_w,globalUserVariable->gridYPos[10]);
    //Johnson 20200228 draw arrow line
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->MultiACP_Lowest_MainCh_x , DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5 ,
                      fm.width("<"), fm.height(), Qt::AlignLeft, "<");
    painter->drawLine(DRAW_GRID_START_X+globalUserVariable->MultiACP_Lowest_MainCh_x , DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5+fm.height()/2,
                      DRAW_GRID_START_X+globalUserVariable->MultiACP_MainCh_w+globalUserVariable->MultiACP_Lowest_MainCh_x, DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5+fm.height()/2);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->MultiACP_MainCh_w+globalUserVariable->MultiACP_Lowest_MainCh_x-fm.width(">") , DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5 ,
                      fm.width("<"), fm.height(), Qt::AlignLeft, ">");
    //Johnson 20200228 draw dbm value
    QString powerValue = QString::number(Lowest_MainCh_Power,'f',2);
    painter->setPen(Qt::green);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->MultiACP_Lowest_MainCh_x+globalUserVariable->MultiACP_MainCh_w/2-fm.width(powerValue)/2,
                      DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5-fm.height()/2,fm.width(powerValue),fm.height(),Qt::AlignLeft,powerValue);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->MultiACP_Lowest_MainCh_x+globalUserVariable->MultiACP_MainCh_w/2-fm.width("dBm")/2,
                      DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5+fm.height()/2,fm.width("dBm"),fm.height(),Qt::AlignLeft,"dBm");
    //*******draw Lowest Main end**************

    //********draw Lowest ADJ begin***********
    painter->setPen(Qt::white);
    if(globalUserVariable->MultiACP_Lowest_ADJCh_x != 0)
        painter->drawLine(DRAW_GRID_START_X+globalUserVariable->MultiACP_Lowest_ADJCh_x,DRAW_GRID_START_Y,
                          DRAW_GRID_START_X+globalUserVariable->MultiACP_Lowest_ADJCh_x,globalUserVariable->gridYPos[10]);
    if(globalUserVariable->MultiACP_Lowest_ADJCh_x+globalUserVariable->MultiACP_ADJCh_w != gridWidth)
        painter->drawLine(DRAW_GRID_START_X+globalUserVariable->MultiACP_Lowest_ADJCh_x+globalUserVariable->MultiACP_ADJCh_w,DRAW_GRID_START_Y,
                          DRAW_GRID_START_X+globalUserVariable->MultiACP_Lowest_ADJCh_x+globalUserVariable->MultiACP_ADJCh_w,globalUserVariable->gridYPos[10]);
    //Johnson 20200228 draw arrow line
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->MultiACP_Lowest_ADJCh_x , DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5 ,
                      fm.width("<"), fm.height(), Qt::AlignLeft, "<");
    painter->drawLine(DRAW_GRID_START_X+globalUserVariable->MultiACP_Lowest_ADJCh_x , DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2,
                      DRAW_GRID_START_X+globalUserVariable->MultiACP_ADJCh_w+globalUserVariable->MultiACP_Lowest_ADJCh_x, DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->MultiACP_Lowest_ADJCh_x+globalUserVariable->MultiACP_ADJCh_w-fm.width(">") , DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5 ,
                      fm.width("<"), fm.height(), Qt::AlignLeft, ">");
    //Johnson 20200228 draw dbc value
    powerValue = QString::number(Lowest_ADJCh_Power - Lowest_MainCh_Power,'f',2);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->MultiACP_Lowest_ADJCh_x+globalUserVariable->MultiACP_ADJCh_w/2-fm.width(powerValue)/2,
                      DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2 + 5,fm.width(powerValue),fm.height(),Qt::AlignLeft,powerValue);
    //********draw Lowest ADJ end*************

    //********draw Lowest ALT begin***********
    painter->setPen(Qt::white);
    if(globalUserVariable->MultiACP_Lowest_ALTCh_x != 0)
        painter->drawLine(DRAW_GRID_START_X+globalUserVariable->MultiACP_Lowest_ALTCh_x,DRAW_GRID_START_Y,
                          DRAW_GRID_START_X+globalUserVariable->MultiACP_Lowest_ALTCh_x,globalUserVariable->gridYPos[10]);
    if(globalUserVariable->MultiACP_Lowest_ALTCh_x+globalUserVariable->MultiACP_ALTCh_w != gridWidth)
        painter->drawLine(DRAW_GRID_START_X+globalUserVariable->MultiACP_Lowest_ALTCh_x+globalUserVariable->MultiACP_ALTCh_w,DRAW_GRID_START_Y,
                          DRAW_GRID_START_X+globalUserVariable->MultiACP_Lowest_ALTCh_x+globalUserVariable->MultiACP_ALTCh_w,globalUserVariable->gridYPos[10]);
    //Johnson 190326 draw arrow line
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->MultiACP_Lowest_ALTCh_x ,
                      DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5 , fm.width("<"), fm.height(), Qt::AlignLeft, "<");
    painter->drawLine(DRAW_GRID_START_X+globalUserVariable->MultiACP_Lowest_ALTCh_x , DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2,
                      DRAW_GRID_START_X+globalUserVariable->MultiACP_ALTCh_w+globalUserVariable->MultiACP_Lowest_ALTCh_x, DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->MultiACP_Lowest_ALTCh_x+globalUserVariable->MultiACP_ALTCh_w-fm.width(">") ,
                      DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5 , fm.width("<"), fm.height(), Qt::AlignLeft, ">");
    //Johnson 190326 draw dbc value
    powerValue = QString::number(Lowest_ALTCh_Power - Lowest_MainCh_Power,'f',2);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->MultiACP_Lowest_ALTCh_x+globalUserVariable->MultiACP_ALTCh_w/2-fm.width(powerValue)/2,
                      DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2 + 5,fm.width(powerValue),fm.height(),Qt::AlignLeft,powerValue);
    //********draw Lowest ALT end*************


    //********draw Highest Main begin***********
    painter->setPen(Qt::white);
    if(globalUserVariable->MultiACP_Highest_MainCh_x != 0)
        painter->drawLine(DRAW_GRID_START_X+globalUserVariable->MultiACP_Highest_MainCh_x,DRAW_GRID_START_Y,
                          DRAW_GRID_START_X+globalUserVariable->MultiACP_Highest_MainCh_x,globalUserVariable->gridYPos[10]);
    if(globalUserVariable->MultiACP_Highest_MainCh_x+globalUserVariable->MultiACP_MainCh_w != gridWidth)
        painter->drawLine(DRAW_GRID_START_X+globalUserVariable->MultiACP_Highest_MainCh_x+globalUserVariable->MultiACP_MainCh_w,DRAW_GRID_START_Y,
                          DRAW_GRID_START_X+globalUserVariable->MultiACP_Highest_MainCh_x+globalUserVariable->MultiACP_MainCh_w,globalUserVariable->gridYPos[10]);
    //Johnson 20200228 draw arrow line
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->MultiACP_Highest_MainCh_x , DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5 , fm.width("<"), fm.height(), Qt::AlignLeft, "<");
    painter->drawLine(DRAW_GRID_START_X+globalUserVariable->MultiACP_Highest_MainCh_x , DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5+fm.height()/2,
                      DRAW_GRID_START_X+globalUserVariable->MultiACP_MainCh_w+globalUserVariable->MultiACP_Highest_MainCh_x, DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5+fm.height()/2);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->MultiACP_MainCh_w+globalUserVariable->MultiACP_Highest_MainCh_x-fm.width(">") , DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5 ,
                      fm.width("<"), fm.height(), Qt::AlignLeft, ">");
    //Johnson 20200228 draw dbm value
    powerValue = QString::number(Highest_MainCh_Power,'f',2);
    painter->setPen(Qt::green);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->MultiACP_Highest_MainCh_x+globalUserVariable->MultiACP_MainCh_w/2-fm.width(powerValue)/2,DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5-fm.height()/2,
                      fm.width(powerValue),fm.height(),Qt::AlignLeft,powerValue);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->MultiACP_Highest_MainCh_x+globalUserVariable->MultiACP_MainCh_w/2-fm.width("dBm")/2,
                      DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5+fm.height()/2,fm.width("dBm"),fm.height(),Qt::AlignLeft,"dBm");
    //*******draw Highest Main end**************

    //********draw Highest ADJ begin***********
    painter->setPen(Qt::white);
    if(globalUserVariable->MultiACP_Highest_ADJCh_x != 0)
        painter->drawLine(DRAW_GRID_START_X+globalUserVariable->MultiACP_Highest_ADJCh_x,DRAW_GRID_START_Y,
                          DRAW_GRID_START_X+globalUserVariable->MultiACP_Highest_ADJCh_x,globalUserVariable->gridYPos[10]);
    if(globalUserVariable->MultiACP_Highest_ADJCh_x+globalUserVariable->MultiACP_ADJCh_w != gridWidth)
        painter->drawLine(DRAW_GRID_START_X+globalUserVariable->MultiACP_Highest_ADJCh_x+globalUserVariable->MultiACP_ADJCh_w,DRAW_GRID_START_Y,
                          DRAW_GRID_START_X+globalUserVariable->MultiACP_Highest_ADJCh_x+globalUserVariable->MultiACP_ADJCh_w,globalUserVariable->gridYPos[10]);
    //Johnson 20200228 draw arrow line
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->MultiACP_Highest_ADJCh_x , DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5 , fm.width("<"), fm.height(), Qt::AlignLeft, "<");
    painter->drawLine(DRAW_GRID_START_X+globalUserVariable->MultiACP_Highest_ADJCh_x , DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2,
                      DRAW_GRID_START_X+globalUserVariable->MultiACP_ADJCh_w+globalUserVariable->MultiACP_Highest_ADJCh_x, DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->MultiACP_Highest_ADJCh_x+globalUserVariable->MultiACP_ADJCh_w-fm.width(">") , DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5 , fm.width("<"), fm.height(), Qt::AlignLeft, ">");
    //Johnson 20200228 draw dbc value
    powerValue = QString::number(Highest_ADJCh_Power - Highest_MainCh_Power,'f',2);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->MultiACP_Highest_ADJCh_x+globalUserVariable->MultiACP_ADJCh_w/2-fm.width(powerValue)/2,
                      DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2 + 5,fm.width(powerValue),fm.height(),Qt::AlignLeft,powerValue);
    //********draw Highest ADJ end*************

    //********draw Highest ALT begin***********
    painter->setPen(Qt::white);
    if(globalUserVariable->MultiACP_Highest_ALTCh_x != 0)
        painter->drawLine(DRAW_GRID_START_X+globalUserVariable->MultiACP_Highest_ALTCh_x,DRAW_GRID_START_Y,
                          DRAW_GRID_START_X+globalUserVariable->MultiACP_Highest_ALTCh_x,globalUserVariable->gridYPos[10]);
    if(globalUserVariable->MultiACP_Highest_ALTCh_x+globalUserVariable->MultiACP_ALTCh_w != gridWidth)
        painter->drawLine(DRAW_GRID_START_X+globalUserVariable->MultiACP_Highest_ALTCh_x+globalUserVariable->MultiACP_ALTCh_w,DRAW_GRID_START_Y,
                          DRAW_GRID_START_X+globalUserVariable->MultiACP_Highest_ALTCh_x+globalUserVariable->MultiACP_ALTCh_w,globalUserVariable->gridYPos[10]);
    //Johnson 190326 draw arrow line
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->MultiACP_Highest_ALTCh_x , DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5 , fm.width("<"), fm.height(), Qt::AlignLeft, "<");
    painter->drawLine(DRAW_GRID_START_X+globalUserVariable->MultiACP_Highest_ALTCh_x , DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2,
                      DRAW_GRID_START_X+globalUserVariable->MultiACP_ALTCh_w+globalUserVariable->MultiACP_Highest_ALTCh_x, DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->MultiACP_Highest_ALTCh_x+globalUserVariable->MultiACP_ALTCh_w-fm.width(">") , DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5 , fm.width("<"), fm.height(), Qt::AlignLeft, ">");
    //Johnson 190326 draw dbc value
    powerValue = QString::number(Highest_ALTCh_Power - Highest_MainCh_Power,'f',2);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->MultiACP_Highest_ALTCh_x+globalUserVariable->MultiACP_ALTCh_w/2-fm.width(powerValue)/2,
                      DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2 + 5,fm.width(powerValue),fm.height(),Qt::AlignLeft,powerValue);
    //********draw Highest ALT end*************

    //*************************************************************************************
}
#else
/**
 * @brief sa_UIRefresh_Control::drawACPPower
 * @param painter
 * @param chnpw_x
 * @param chpw_w
 * @param pixelStep
 * @param gridWidth
 * @author Johnson 190326
 */
void sa_UIRefresh_Control::drawACPPower(QPainter *painter,qint32 chpw_x,qint32 chpw_w,qreal pixelStep,qint32 gridWidth)
{
    //*********ACP param(Johnson 180813)***********
    static qint32 acpl_x, acpr_x;
    qint32 y_M,y_L,y_R;//Johnson 0813
    //*********************************************
    //*********ACP param(Johnson 180813)***********
    qreal dPowerValue_ACPL = 0.,dPowerValue_ACPM = 0.,dPowerValue_ACPR = 0.;
    QString powerValue;
    QFontMetrics fm = painter->fontMetrics();

    qreal FZ = (qreal)globalUserVariable->gChannelSpacing;
    qreal SA_FM = (qreal)globalUserVariable->gSpanFreq / gridWidth;
    acpl_x = chpw_x - (qint32)(FZ / SA_FM);
    acpr_x = chpw_x + (qint32)(FZ / SA_FM);

    //***********Johnson 0808*****************
    if(acpl_x<0)
    {
        acpl_x = 0;
        globalUserVariable->gChannelBandwidth = globalUserVariable->gSpanFreq-2*globalUserVariable->gChannelSpacing;
        if(globalUserVariable->gChannelBandwidth<0) globalUserVariable->gChannelBandwidth = 0;

        FZ = (qreal)globalUserVariable->gChannelBandwidth;
        SA_FM = (qreal)globalUserVariable->gSpanFreq / gridWidth;
        chpw_w = (qint32) (FZ/ SA_FM);
        if (chpw_w < BW_MIN)
        {
            chpw_w = BW_MIN;
            //Johnson 0813
            globalUserVariable->gChannelBandwidth = chpw_w*globalUserVariable->gSpanFreq / gridWidth;
            globalUserVariable->gChannelSpacing = (globalUserVariable->gSpanFreq - globalUserVariable->gChannelBandwidth)/2;
        }
        if (chpw_w > gridWidth)
        {
            chpw_w = gridWidth;
            //Johnson 0813
            globalUserVariable->gChannelBandwidth = chpw_w*globalUserVariable->gSpanFreq / gridWidth;
            globalUserVariable->gChannelSpacing = (globalUserVariable->gSpanFreq - globalUserVariable->gChannelBandwidth)/2;
        }
        chpw_x = (gridWidth / 2)  - (chpw_w / 2);		// 좌우분할이므로 /2

        FZ = (qreal)globalUserVariable->gChannelSpacing;
        SA_FM = (qreal)globalUserVariable->gSpanFreq / gridWidth;
        acpr_x = chpw_x + (qint32 )( FZ/ SA_FM);

        if(acpr_x >gridWidth-BW_MIN) acpr_x = gridWidth-BW_MIN;
    }
    else if(acpr_x >gridWidth)
    {
        acpr_x = gridWidth;

        globalUserVariable->gChannelBandwidth = 2*globalUserVariable->gChannelSpacing-globalUserVariable->gSpanFreq;
        if(globalUserVariable->gChannelBandwidth<0) globalUserVariable->gChannelBandwidth = 0;

        FZ = (qreal)globalUserVariable->gChannelBandwidth;
        SA_FM = (qreal)globalUserVariable->gSpanFreq / gridWidth;
        chpw_w =  (qint32)(FZ/ SA_FM);
        if (chpw_w < BW_MIN)
        {
            chpw_w = BW_MIN;
            //Johnson 0813
            globalUserVariable->gChannelBandwidth = chpw_w*globalUserVariable->gSpanFreq / gridWidth;
            globalUserVariable->gChannelSpacing = (globalUserVariable->gSpanFreq - globalUserVariable->gChannelBandwidth)/2;
        }
        if (chpw_w > gridWidth)
        {
            chpw_w = gridWidth;
            //Johnson 0813
            globalUserVariable->gChannelBandwidth = chpw_w*globalUserVariable->gSpanFreq / gridWidth;
            globalUserVariable->gChannelSpacing = (globalUserVariable->gSpanFreq - globalUserVariable->gChannelBandwidth)/2;
        }
        chpw_x = (gridWidth / 2)  - (chpw_w / 2);		// 좌우분할이므로 /2

        if(acpl_x <0) acpl_x = 0;
    }
    //*****************************************

    //Johnson 0801
    dPowerValue_ACPM = psa_Measure_Control->calculatePower(DRAW_GRID_START_X + chpw_x,chpw_w,mPixmap.width(),pixelStep,globalUserVariable->gChannelBandwidth);
    dPowerValue_ACPL = psa_Measure_Control->calculatePower(DRAW_GRID_START_X + acpl_x,chpw_w,mPixmap.width(),pixelStep,globalUserVariable->gChannelBandwidth);
    dPowerValue_ACPR = psa_Measure_Control->calculatePower(DRAW_GRID_START_X + acpr_x,chpw_w,mPixmap.width(),pixelStep,globalUserVariable->gChannelBandwidth);

    globalUserVariable->dPowerValue_ACPL = dPowerValue_ACPL;
    globalUserVariable->dPowerValue_ACPM = dPowerValue_ACPM;
    globalUserVariable->dPowerValue_ACPR = dPowerValue_ACPR;

    //Johnson 0813
    y_M = yaxis_cal(dPowerValue_ACPM + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y + 1;
    y_L = yaxis_cal(dPowerValue_ACPL + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y + 1;
    y_R = yaxis_cal(dPowerValue_ACPR + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y + 1;
    painter->fillRect(DRAW_GRID_START_X + chpw_x, y_M, chpw_w, globalUserVariable->gridYPos[10]- y_M + 1, colSteelBlue);
    painter->fillRect(DRAW_GRID_START_X + acpl_x, y_L, chpw_w, globalUserVariable->gridYPos[10]- y_L + 1, colSteelBlue);
    painter->fillRect(DRAW_GRID_START_X + acpr_x, y_R, chpw_w, globalUserVariable->gridYPos[10]- y_R + 1, colSteelBlue);

    //************************Johnson 0815 draw line***************************************
    //********draw mid SA_ACP begin***********
    painter->setPen(Qt::white);
    if(chpw_x != 0) painter->drawLine(DRAW_GRID_START_X+chpw_x,DRAW_GRID_START_Y,DRAW_GRID_START_X+chpw_x,globalUserVariable->gridYPos[10]);
    if(chpw_x+chpw_w != gridWidth) painter->drawLine(DRAW_GRID_START_X+chpw_x+chpw_w,DRAW_GRID_START_Y,DRAW_GRID_START_X+chpw_x+chpw_w,globalUserVariable->gridYPos[10]);
    //Johnson 0815 draw arrow line
    painter->drawText(DRAW_GRID_START_X+chpw_x , DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5 , fm.width("<"), fm.height(), Qt::AlignLeft, "<");
    painter->drawLine(DRAW_GRID_START_X+chpw_x , DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5+fm.height()/2, DRAW_GRID_START_X+chpw_w+chpw_x, DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5+fm.height()/2);
    painter->drawText(DRAW_GRID_START_X+chpw_x+chpw_w-fm.width(">") , DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5 , fm.width("<"), fm.height(), Qt::AlignLeft, ">");
    //Johnson 0815 draw dbm value
    powerValue = QString::number(dPowerValue_ACPM,'f',2);
    painter->setPen(Qt::green);
    painter->drawText(DRAW_GRID_START_X+chpw_x+chpw_w/2-fm.width(powerValue)/2,DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5-fm.height()/2,fm.width(powerValue),fm.height(),Qt::AlignLeft,powerValue);
    painter->drawText(DRAW_GRID_START_X+chpw_x+chpw_w/2-fm.width("dBm")/2,DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5+fm.height()/2,fm.width("dBm"),fm.height(),Qt::AlignLeft,"dBm");
    //*******draw mid ACP end**************

    //********draw left ACP begin***********
    painter->setPen(Qt::white);
    if(acpl_x != 0) painter->drawLine(DRAW_GRID_START_X+acpl_x,DRAW_GRID_START_Y,DRAW_GRID_START_X+acpl_x,globalUserVariable->gridYPos[10]);
    if(acpl_x+chpw_w != gridWidth) painter->drawLine(DRAW_GRID_START_X+acpl_x+chpw_w,DRAW_GRID_START_Y,DRAW_GRID_START_X+acpl_x+chpw_w,globalUserVariable->gridYPos[10]);
    //Johnson 0815 draw arrow line
    painter->drawText(DRAW_GRID_START_X+acpl_x , DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5 , fm.width("<"), fm.height(), Qt::AlignLeft, "<");
    painter->drawLine(DRAW_GRID_START_X+acpl_x , DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2, DRAW_GRID_START_X+chpw_w+acpl_x, DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2);
    painter->drawText(DRAW_GRID_START_X+acpl_x+chpw_w-fm.width(">") , DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5 , fm.width("<"), fm.height(), Qt::AlignLeft, ">");
    //Johnson 0815 draw dbm value
    powerValue = QString::number(dPowerValue_ACPL - dPowerValue_ACPM,'f',2);
    painter->drawText(DRAW_GRID_START_X+acpl_x+chpw_w/2-fm.width(powerValue)/2,DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2 + 5,fm.width(powerValue),fm.height(),Qt::AlignLeft,powerValue);
    //********draw left ACP end*************

    //********draw rigth ACP begin***********
    painter->setPen(Qt::white);
    if(acpr_x != 0) painter->drawLine(DRAW_GRID_START_X+acpr_x,DRAW_GRID_START_Y,DRAW_GRID_START_X+acpr_x,globalUserVariable->gridYPos[10]);
    if(acpr_x+chpw_w != gridWidth) painter->drawLine(DRAW_GRID_START_X+acpr_x+chpw_w,DRAW_GRID_START_Y,DRAW_GRID_START_X+acpr_x+chpw_w,globalUserVariable->gridYPos[10]);
    //Johnson 0815 draw arrow line
    painter->drawText(DRAW_GRID_START_X+acpr_x , DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5 , fm.width("<"), fm.height(), Qt::AlignLeft, "<");
    painter->drawLine(DRAW_GRID_START_X+acpr_x , DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2, DRAW_GRID_START_X+chpw_w+acpr_x, DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2);
    painter->drawText(DRAW_GRID_START_X+acpr_x+chpw_w-fm.width(">") , DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5 , fm.width("<"), fm.height(), Qt::AlignLeft, ">");
    //Johnson 0815 draw dbm value
    powerValue = QString::number(dPowerValue_ACPR - dPowerValue_ACPM,'f',2);
    painter->drawText(DRAW_GRID_START_X+acpr_x+chpw_w/2-fm.width(powerValue)/2,DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2 + 5,fm.width(powerValue),fm.height(),Qt::AlignLeft,powerValue);
    //*******draw rigth ACP end***************

    //*************************************************************************************
}
#endif

/**
 * @brief sa_UIRefresh_Control::drawMultiACPPower
 * @param painter
 * @param chnpw_x
 * @param chpw_w
 * @param pixelStep
 * @param gridWidth
 * @author Johnson 190326
 */
void sa_UIRefresh_Control::drawMultiACPPower(QPainter *painter, qreal pixelStep, qint32 gridWidth)
{
    //*********Multi ACP(Johnson 190325)***********
    qint32 multiacp_y_M,multiacp_y_FarL,multiacp_y_L,multiacp_y_R,multiacp_y_FarR;
    //*********************************************

    //*********Multi ACP(Johnson 190325)***********
    qreal dPowerValue_MultiACPFL = 0.,dPowerValue_MultiACPL = 0.,
          dPowerValue_MultiACPM = 0.,dPowerValue_MultiACPR = 0.,dPowerValue_MultiACPFR = 0.;
    QString powerValue;
    QFontMetrics fm = painter->fontMetrics();

    //**********test channelSpacing , recaculate channelSpacing and bandwidth*****
#if 0
    qint32 chpw_x, chpw_w;
    static qint32 multiacpFarl_x,multiacpl_x, multiacpr_x,multiacpFarr_x;
    qreal FZ = 0.,SA_FM = 0.;
    //***********Johnson 190325*****************
    qreal FZ = (qreal)globalUserVariable->gMultiACPSpacing;
    qreal SA_FM = (qreal)globalUserVariable->gSpanFreq / gridWidth;
    multiacpFarl_x = chpw_x - (qint32)(2 * FZ / SA_FM);
    multiacpl_x    = chpw_x - (qint32)(FZ / SA_FM);
    multiacpFarr_x = chpw_x + (qint32)(2 * FZ / SA_FM);
    multiacpr_x    = chpw_x + (qint32)(FZ / SA_FM);
    if(multiacpFarl_x<0)
    {
        multiacpFarl_x = 0;
        globalUserVariable->gChannelBandwidth = globalUserVariable->gSpanFreq-4*globalUserVariable->gChannelSpacing;
        if(globalUserVariable->gChannelBandwidth<0) globalUserVariable->gChannelBandwidth = 0;

        FZ = (qreal)globalUserVariable->gChannelBandwidth;
        SA_FM = (qreal)globalUserVariable->gSpanFreq / gridWidth;
        chpw_w = (qint32) (FZ/ SA_FM);
        if (chpw_w < BW_MIN)
        {
            chpw_w = BW_MIN;
            globalUserVariable->gChannelBandwidth = chpw_w*globalUserVariable->gSpanFreq / gridWidth;
            globalUserVariable->gChannelSpacing = (globalUserVariable->gSpanFreq - globalUserVariable->gChannelBandwidth)/4;
        }
        if (chpw_w > gridWidth)
        {
            chpw_w = gridWidth;
            globalUserVariable->gChannelBandwidth = chpw_w*globalUserVariable->gSpanFreq / gridWidth;
            globalUserVariable->gChannelSpacing = (globalUserVariable->gSpanFreq - globalUserVariable->gChannelBandwidth)/4;
        }
        chpw_x = (gridWidth / 2)  - (chpw_w / 2);		// 좌우분할이므로 /2

        FZ = (qreal)globalUserVariable->gChannelSpacing;
        SA_FM = (qreal)globalUserVariable->gSpanFreq / gridWidth;

        multiacpl_x    = multiacpFarl_x + (qint32 )(FZ/ SA_FM);
        multiacpFarr_x = chpw_x + (qint32 )(2 * FZ/ SA_FM);

        if(multiacpFarr_x >gridWidth-BW_MIN) multiacpFarr_x = gridWidth-BW_MIN;

        multiacpr_x = multiacpFarr_x - (qint32 )(FZ/ SA_FM);
    }
    else if(multiacpFarr_x > gridWidth)
    {
        multiacpFarr_x = gridWidth;

        globalUserVariable->gChannelBandwidth = 4*globalUserVariable->gChannelSpacing-globalUserVariable->gSpanFreq;
        if(globalUserVariable->gChannelBandwidth<0) globalUserVariable->gChannelBandwidth = 0;

        FZ = (qreal)globalUserVariable->gChannelBandwidth;
        SA_FM = (qreal)globalUserVariable->gSpanFreq / gridWidth;
        chpw_w =  (qint32)(FZ/ SA_FM);
        if (chpw_w < BW_MIN)
        {
            chpw_w = BW_MIN;

            globalUserVariable->gChannelBandwidth = chpw_w*globalUserVariable->gSpanFreq / gridWidth;
            globalUserVariable->gChannelSpacing = (globalUserVariable->gSpanFreq - globalUserVariable->gChannelBandwidth)/4;
        }
        if (chpw_w > gridWidth)
        {
            chpw_w = gridWidth;
            globalUserVariable->gChannelBandwidth = chpw_w*globalUserVariable->gSpanFreq / gridWidth;
            globalUserVariable->gChannelSpacing = (globalUserVariable->gSpanFreq - globalUserVariable->gChannelBandwidth)/4;
        }
        chpw_x = (gridWidth / 2)  - (chpw_w / 2);		// 좌우분할이므로 /2

        FZ = (qreal)globalUserVariable->gChannelSpacing;
        SA_FM = (qreal)globalUserVariable->gSpanFreq / gridWidth;

        multiacpr_x    = multiacpFarr_x - (qint32 )(FZ/ SA_FM);
        multiacpFarl_x = chpw_x - (qint32 )(2 * FZ/ SA_FM);

        if(multiacpFarl_x <0) multiacpFarl_x = 0;

        multiacpl_x = multiacpFarl_x + (qint32 )(FZ/ SA_FM);
    }
#endif
    //*****************************************

    //Johnson 190325
    dPowerValue_MultiACPM  = psa_Measure_Control->calculatePower(DRAW_GRID_START_X + globalUserVariable->ACP_MainCH_x,globalUserVariable->ACP_MainCH_W,
                                                                 mPixmap.width(),pixelStep,globalUserVariable->gMainIntegBW);
    dPowerValue_MultiACPFL = psa_Measure_Control->calculatePower(DRAW_GRID_START_X + globalUserVariable->ACP_LeftALTCH_x,globalUserVariable->ACP_ALTCH_W,
                                                                 mPixmap.width(),pixelStep,globalUserVariable->gALTIntegBW);
    dPowerValue_MultiACPL  = psa_Measure_Control->calculatePower(DRAW_GRID_START_X + globalUserVariable->ACP_LeftADJCH_x,globalUserVariable->ACP_ADJCH_W,
                                                                 mPixmap.width(),pixelStep,globalUserVariable->gADJIntegBW);
    dPowerValue_MultiACPFR = psa_Measure_Control->calculatePower(DRAW_GRID_START_X + globalUserVariable->ACP_RightALTCH_x,globalUserVariable->ACP_ALTCH_W,
                                                                 mPixmap.width(),pixelStep,globalUserVariable->gALTIntegBW);
    dPowerValue_MultiACPR  = psa_Measure_Control->calculatePower(DRAW_GRID_START_X + globalUserVariable->ACP_RightADJCH_x,globalUserVariable->ACP_ADJCH_W,
                                                                 mPixmap.width(),pixelStep,globalUserVariable->gADJIntegBW);

    globalUserVariable->dPowerValue_MultiACPFL = dPowerValue_MultiACPFL;
    globalUserVariable->dPowerValue_MultiACPL  = dPowerValue_MultiACPL;
    globalUserVariable->dPowerValue_MultiACPM  = dPowerValue_MultiACPM;
    globalUserVariable->dPowerValue_MultiACPR  = dPowerValue_MultiACPR;
    globalUserVariable->dPowerValue_MultiACPFR = dPowerValue_MultiACPFR;

    //Johnson 190325
    multiacp_y_M = yaxis_cal(dPowerValue_MultiACPM + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y + 1;
    multiacp_y_FarL = yaxis_cal(dPowerValue_MultiACPFL + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y + 1;
    multiacp_y_L = yaxis_cal(dPowerValue_MultiACPL + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y + 1;
    multiacp_y_FarR = yaxis_cal(dPowerValue_MultiACPFR + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y + 1;
    multiacp_y_R = yaxis_cal(dPowerValue_MultiACPR + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y + 1;

    painter->fillRect(DRAW_GRID_START_X + globalUserVariable->ACP_MainCH_x, multiacp_y_M,
                      globalUserVariable->ACP_MainCH_W, globalUserVariable->gridYPos[10]- multiacp_y_M + 1, colSteelBlue);
    painter->fillRect(DRAW_GRID_START_X + globalUserVariable->ACP_LeftALTCH_x, multiacp_y_FarL,
                      globalUserVariable->ACP_ALTCH_W, globalUserVariable->gridYPos[10]- multiacp_y_FarL + 1, colSteelBlue);
    painter->fillRect(DRAW_GRID_START_X + globalUserVariable->ACP_LeftADJCH_x, multiacp_y_L,
                      globalUserVariable->ACP_ADJCH_W, globalUserVariable->gridYPos[10]- multiacp_y_L + 1, colSteelBlue);
    painter->fillRect(DRAW_GRID_START_X + globalUserVariable->ACP_RightALTCH_x, multiacp_y_FarR,
                      globalUserVariable->ACP_ALTCH_W, globalUserVariable->gridYPos[10]- multiacp_y_FarR + 1, colSteelBlue);
    painter->fillRect(DRAW_GRID_START_X + globalUserVariable->ACP_RightADJCH_x, multiacp_y_R,
                      globalUserVariable->ACP_ADJCH_W, globalUserVariable->gridYPos[10]- multiacp_y_R + 1, colSteelBlue);

    //************************Johnson 190326 draw line***************************************
    //********draw mid MultiACP begin***********
    painter->setPen(Qt::white);
    if(globalUserVariable->ACP_MainCH_x != 0)
        painter->drawLine(DRAW_GRID_START_X+globalUserVariable->ACP_MainCH_x,DRAW_GRID_START_Y,
                          DRAW_GRID_START_X+globalUserVariable->ACP_MainCH_x,globalUserVariable->gridYPos[10]);
    if(globalUserVariable->ACP_MainCH_x+globalUserVariable->ACP_MainCH_W != gridWidth)
        painter->drawLine(DRAW_GRID_START_X+globalUserVariable->ACP_MainCH_x+globalUserVariable->ACP_MainCH_W,DRAW_GRID_START_Y,
                          DRAW_GRID_START_X+globalUserVariable->ACP_MainCH_x+globalUserVariable->ACP_MainCH_W,globalUserVariable->gridYPos[10]);
    //Johnson 190326 draw arrow line
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->ACP_MainCH_x , DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5 , fm.width("<"), fm.height(), Qt::AlignLeft, "<");
    painter->drawLine(DRAW_GRID_START_X+globalUserVariable->ACP_MainCH_x , DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5+fm.height()/2,
                      DRAW_GRID_START_X+globalUserVariable->ACP_MainCH_W+globalUserVariable->ACP_MainCH_x, DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5+fm.height()/2);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->ACP_MainCH_x+globalUserVariable->ACP_MainCH_W-fm.width(">") , DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5 , fm.width("<"), fm.height(), Qt::AlignLeft, ">");
    //Johnson 190326 draw dbm value
    powerValue = QString::number(dPowerValue_MultiACPM,'f',2);
    painter->setPen(Qt::green);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->ACP_MainCH_x+globalUserVariable->ACP_MainCH_W/2-fm.width(powerValue)/2,DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5-fm.height()/2,fm.width(powerValue),fm.height(),Qt::AlignLeft,powerValue);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->ACP_MainCH_x+globalUserVariable->ACP_MainCH_W/2-fm.width("dBm")/2,DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/5+fm.height()/2,fm.width("dBm"),fm.height(),Qt::AlignLeft,"dBm");
    //*******draw mid MultiACP end**************

    //********draw Far left MultiACP begin***********
    painter->setPen(Qt::white);
    if(globalUserVariable->ACP_LeftALTCH_x != 0)
        painter->drawLine(DRAW_GRID_START_X+globalUserVariable->ACP_LeftALTCH_x,DRAW_GRID_START_Y,
                          DRAW_GRID_START_X+globalUserVariable->ACP_LeftALTCH_x,globalUserVariable->gridYPos[10]);
    if(globalUserVariable->ACP_LeftALTCH_x+globalUserVariable->ACP_ALTCH_W != gridWidth)
        painter->drawLine(DRAW_GRID_START_X+globalUserVariable->ACP_LeftALTCH_x+globalUserVariable->ACP_ALTCH_W,DRAW_GRID_START_Y,
                          DRAW_GRID_START_X+globalUserVariable->ACP_LeftALTCH_x+globalUserVariable->ACP_ALTCH_W,globalUserVariable->gridYPos[10]);
    //Johnson 190326 draw arrow line
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->ACP_LeftALTCH_x , DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5 , fm.width("<"), fm.height(), Qt::AlignLeft, "<");
    painter->drawLine(DRAW_GRID_START_X+globalUserVariable->ACP_LeftALTCH_x , DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2,
                      DRAW_GRID_START_X+globalUserVariable->ACP_ALTCH_W+globalUserVariable->ACP_LeftALTCH_x, DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->ACP_LeftALTCH_x+globalUserVariable->ACP_ALTCH_W-fm.width(">") ,
                      DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5 , fm.width("<"), fm.height(), Qt::AlignLeft, ">");
    //Johnson 190326 draw dbm value
    powerValue = QString::number(dPowerValue_MultiACPFL - dPowerValue_MultiACPM,'f',2);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->ACP_LeftALTCH_x+globalUserVariable->ACP_ALTCH_W/2-fm.width(powerValue)/2,
                      DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2 + 5,fm.width(powerValue),fm.height(),Qt::AlignLeft,powerValue);
    //********draw Far left MultiACP end*************

    //********draw left MultiACP begin***********
    painter->setPen(Qt::white);
    if(globalUserVariable->ACP_LeftADJCH_x != 0)
        painter->drawLine(DRAW_GRID_START_X+globalUserVariable->ACP_LeftADJCH_x,DRAW_GRID_START_Y,
                          DRAW_GRID_START_X+globalUserVariable->ACP_LeftADJCH_x,globalUserVariable->gridYPos[10]);
    if(globalUserVariable->ACP_LeftADJCH_x+globalUserVariable->ACP_ADJCH_W != gridWidth)
        painter->drawLine(DRAW_GRID_START_X+globalUserVariable->ACP_LeftADJCH_x+globalUserVariable->ACP_ADJCH_W,DRAW_GRID_START_Y,
                          DRAW_GRID_START_X+globalUserVariable->ACP_LeftADJCH_x+globalUserVariable->ACP_ADJCH_W,globalUserVariable->gridYPos[10]);
    //Johnson 190326 draw arrow line
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->ACP_LeftADJCH_x , DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5 , fm.width("<"), fm.height(), Qt::AlignLeft, "<");
    painter->drawLine(DRAW_GRID_START_X+globalUserVariable->ACP_LeftADJCH_x , DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2,
                      DRAW_GRID_START_X+globalUserVariable->ACP_ADJCH_W+globalUserVariable->ACP_LeftADJCH_x, DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->ACP_LeftADJCH_x+globalUserVariable->ACP_ADJCH_W-fm.width(">") ,
                      DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5 , fm.width("<"), fm.height(), Qt::AlignLeft, ">");
    //Johnson 190326 draw dbm value
    powerValue = QString::number(dPowerValue_MultiACPL - dPowerValue_MultiACPM,'f',2);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->ACP_LeftADJCH_x+globalUserVariable->ACP_ADJCH_W/2-fm.width(powerValue)/2,
                      DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2 + 5,fm.width(powerValue),fm.height(),Qt::AlignLeft,powerValue);
    //********draw left MultiACP end*************

    //********draw rigth MultiACP begin***********
    painter->setPen(Qt::white);
    if(globalUserVariable->ACP_RightADJCH_x != 0)
        painter->drawLine(DRAW_GRID_START_X+globalUserVariable->ACP_RightADJCH_x,DRAW_GRID_START_Y,
                          DRAW_GRID_START_X+globalUserVariable->ACP_RightADJCH_x,globalUserVariable->gridYPos[10]);
    if(globalUserVariable->ACP_RightADJCH_x+globalUserVariable->ACP_ADJCH_W != gridWidth)
        painter->drawLine(DRAW_GRID_START_X+globalUserVariable->ACP_RightADJCH_x+globalUserVariable->ACP_ADJCH_W,DRAW_GRID_START_Y,
                          DRAW_GRID_START_X+globalUserVariable->ACP_RightADJCH_x+globalUserVariable->ACP_ADJCH_W,globalUserVariable->gridYPos[10]);
    //Johnson 190326 draw arrow line
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->ACP_RightADJCH_x , DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5 , fm.width("<"), fm.height(), Qt::AlignLeft, "<");
    painter->drawLine(DRAW_GRID_START_X+globalUserVariable->ACP_RightADJCH_x , DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2,
                      DRAW_GRID_START_X+globalUserVariable->ACP_ADJCH_W+globalUserVariable->ACP_RightADJCH_x, DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->ACP_RightADJCH_x+globalUserVariable->ACP_ADJCH_W-fm.width(">") ,
                      DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5 , fm.width("<"), fm.height(), Qt::AlignLeft, ">");
    //Johnson 190326 draw dbm value
    powerValue = QString::number(dPowerValue_MultiACPR - dPowerValue_MultiACPM,'f',2);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->ACP_RightADJCH_x+globalUserVariable->ACP_ADJCH_W/2-fm.width(powerValue)/2,
                      DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2 + 5,fm.width(powerValue),fm.height(),Qt::AlignLeft,powerValue);
    //*******draw rigth MultiACP end***************

    //********draw Far rigth MultiACP begin***********
    painter->setPen(Qt::white);
    if(globalUserVariable->ACP_RightALTCH_x != 0)
        painter->drawLine(DRAW_GRID_START_X+globalUserVariable->ACP_RightALTCH_x,DRAW_GRID_START_Y,
                          DRAW_GRID_START_X+globalUserVariable->ACP_RightALTCH_x,globalUserVariable->gridYPos[10]);
    if(globalUserVariable->ACP_RightALTCH_x+globalUserVariable->ACP_ALTCH_W != gridWidth)
        painter->drawLine(DRAW_GRID_START_X+globalUserVariable->ACP_RightALTCH_x+globalUserVariable->ACP_ALTCH_W,DRAW_GRID_START_Y,
                          DRAW_GRID_START_X+globalUserVariable->ACP_RightALTCH_x+globalUserVariable->ACP_ALTCH_W,globalUserVariable->gridYPos[10]);
    //Johnson 190326 draw arrow line
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->ACP_RightALTCH_x , DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5 , fm.width("<"), fm.height(), Qt::AlignLeft, "<");
    painter->drawLine(DRAW_GRID_START_X+globalUserVariable->ACP_RightALTCH_x , DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2,
                      DRAW_GRID_START_X+globalUserVariable->ACP_ALTCH_W+globalUserVariable->ACP_RightALTCH_x, DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->ACP_RightALTCH_x+globalUserVariable->ACP_ALTCH_W-fm.width(">") ,
                      DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5 , fm.width("<"), fm.height(), Qt::AlignLeft, ">");
    //Johnson 190326 draw dbm value
    powerValue = QString::number(dPowerValue_MultiACPFR - dPowerValue_MultiACPM,'f',2);
    painter->drawText(DRAW_GRID_START_X+globalUserVariable->ACP_RightALTCH_x+globalUserVariable->ACP_ALTCH_W/2-fm.width(powerValue)/2,
                      DRAW_GRID_START_Y+3*SA_guiDrawSet.gridVerStep/5+fm.height()/2 + 5,fm.width(powerValue),fm.height(),Qt::AlignLeft,powerValue);
    //*******draw Far rigth MultiACP end***************

    //*************************************************************************************
}

/**
 * @brief sa_UIRefresh_Control::drawOccupiedBWPower
 * @param painter
 * @param pixelStep
 * @author Johnson 190326
 */
void sa_UIRefresh_Control::drawOccupiedBWPower(QPainter *painter,qreal pixelStep)
{
    qint32 leftPos = 0;
    qint32 rightPos = 0;

    //caculate occupied bandwidth and draw
    psa_Measure_Control->caculateOccBW();
    leftPos  = psa_Measure_Control->leftPos;
    rightPos = psa_Measure_Control->rightPos;

    QPen pen(Qt::white);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawLine(DRAW_GRID_START_X+leftPos*pixelStep + 3,DRAW_GRID_START_Y,DRAW_GRID_START_X+leftPos*pixelStep + 3,globalUserVariable->gridYPos[10]);
    painter->drawLine(DRAW_GRID_START_X+rightPos*pixelStep,DRAW_GRID_START_Y,DRAW_GRID_START_X+rightPos*pixelStep,globalUserVariable->gridYPos[10]);

    pen.setWidth(1);
    painter->setPen(pen);
    painter->drawLine(DRAW_GRID_START_X+leftPos*pixelStep + 3,DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/2,DRAW_GRID_START_X+rightPos*pixelStep,DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/2);
    painter->drawLine(DRAW_GRID_START_X+rightPos*pixelStep - 5,DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/2-3,DRAW_GRID_START_X+rightPos*pixelStep,DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/2);
    painter->drawLine(DRAW_GRID_START_X+rightPos*pixelStep - 5,DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/2+3,DRAW_GRID_START_X+rightPos*pixelStep,DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/2);
    painter->drawLine(DRAW_GRID_START_X+leftPos*pixelStep + 3 + 5,DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/2-3,DRAW_GRID_START_X+leftPos*pixelStep + 3,DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/2);
    painter->drawLine(DRAW_GRID_START_X+leftPos*pixelStep +3 + 5,DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/2+3,DRAW_GRID_START_X+leftPos*pixelStep + 3,DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/2);

    //Johnson 0815 draw dbm value
    qreal dPowerValue = globalUserVariable->dTotalPower * globalUserVariable->gOccupied_BW / 100.;
    QFontMetrics fm = painter->fontMetrics();
    QString powerValue = QString::number(dPowerValue,'f',2);
    painter->setPen(Qt::green);
    painter->drawText(DRAW_GRID_START_X+(globalUserVariable->gridXPos[10] - DRAW_GRID_START_X)/2-fm.width(powerValue)/2,DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/2-fm.height(),
                      fm.width(powerValue),fm.height(),Qt::AlignLeft,powerValue);
    painter->drawText(DRAW_GRID_START_X+(globalUserVariable->gridXPos[10] - DRAW_GRID_START_X)/2-fm.width("dBm")/2,DRAW_GRID_START_Y+SA_guiDrawSet.gridVerStep/2,
            fm.width("dBm"),fm.height(),Qt::AlignLeft,"dBm");

    //caculate xdb bandwidth and draw
    painter->setPen(Qt::black);
    psa_Measure_Control->caculateXdBBW();
    leftPos  = psa_Measure_Control->leftPos;
    rightPos = psa_Measure_Control->rightPos;

    qint32 leftPosYAxis = 0;
    qint32 rightPosYAxis = 0;
#if 0
                if(globalUserVariable->bSmallCanvas)
                {
                    leftPosYAxis = smallPixmap_draw_point[globalUserVariable->gTraceSelect][leftPos].y();
                    rightPosYAxis = smallPixmap_draw_point[globalUserVariable->gTraceSelect][rightPos].y();
                }
                else
                {
                    leftPosYAxis = largePixmap_draw_point[globalUserVariable->gTraceSelect][leftPos].y();
                    rightPosYAxis = largePixmap_draw_point[globalUserVariable->gTraceSelect][rightPos].y();
                }
#else
                leftPosYAxis = mPixmap_draw_point[globalUserVariable->gTraceSelect][leftPos].y();
                rightPosYAxis = mPixmap_draw_point[globalUserVariable->gTraceSelect][rightPos].y();
#endif

    painter->drawLine(DRAW_GRID_START_X+rightPos*pixelStep+5,rightPosYAxis-5,DRAW_GRID_START_X+rightPos*pixelStep,rightPosYAxis);
    painter->drawLine(DRAW_GRID_START_X+rightPos*pixelStep+5,rightPosYAxis+5,DRAW_GRID_START_X+rightPos*pixelStep,rightPosYAxis);
    painter->drawLine(DRAW_GRID_START_X+leftPos*pixelStep-5,leftPosYAxis-5,DRAW_GRID_START_X+leftPos*pixelStep,leftPosYAxis);
    painter->drawLine(DRAW_GRID_START_X+leftPos*pixelStep-5,leftPosYAxis+5,DRAW_GRID_START_X+leftPos*pixelStep,leftPosYAxis);
    painter->drawLine(DRAW_GRID_START_X+leftPos*pixelStep,leftPosYAxis,DRAW_GRID_START_X+leftPos*pixelStep-10,leftPosYAxis);
    painter->drawLine(DRAW_GRID_START_X+rightPos*pixelStep,rightPosYAxis,DRAW_GRID_START_X+rightPos*pixelStep+10,rightPosYAxis);
}

/**
 * @brief sa_UIRefresh_Control::drawMeasureRect
 * @param painter
 * @note  when measure mode,draw measure
 * @author Johnson
 */
void sa_UIRefresh_Control::drawMeasureRect(QPainter *painter)
{
    //Johnson 190321
    if(globalUserVariable->gTraceView[globalUserVariable->gTraceSelect] == SA_OFF)
    {
        return;
    }

    if (globalUserVariable->currentMode != SA_SPAN_MODE)
    { 
        qint32 gridWidth = mPixmap.width() - SA_LEFTDIS - SA_RIGHTDIS;

        if(gridWidth != globalUserVariable->gridWidth)
        {
            globalUserVariable->gridWidth = gridWidth;
            globalUserVariable->initMeasurModeParam(globalUserVariable->currentMode);
        }
        //Johnson 1017
        qreal dTotalPower = psa_Measure_Control->caculateTotalPower();

#if 0
        static qint32 chpw_x, chpw_w;
        //***********test Bandwidth,and recaculate Bandwidth*******
        qreal FZ = 0.;
        qreal SA_FM = 0.;
        if(globalUserVariable->currentMode == SA_MULTI_ACP_MODE)
        {
            FZ = (qreal)globalUserVariable->gMainIntegBW;
            SA_FM = (qreal)globalUserVariable->gSpanFreq / gridWidth;

            chpw_w = (qint32)(FZ/SA_FM);
            if (chpw_w < BW_MIN)
            {
                chpw_w = BW_MIN;
                globalUserVariable->gMainIntegBW = chpw_w*globalUserVariable->gSpanFreq / gridWidth;
            }
            if (chpw_w > gridWidth)
            {
                chpw_w = gridWidth;
                //Johnson 0813
                globalUserVariable->gMainIntegBW = chpw_w*globalUserVariable->gSpanFreq / gridWidth;
            }
            chpw_x = (gridWidth / 2)  - (chpw_w / 2);		// 좌우분할이므로 /2
        }
        else if(globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE)
        {
            FZ = (qreal)globalUserVariable->gChannelBandwidth;
            SA_FM = (qreal)globalUserVariable->gSpanFreq / gridWidth;

            chpw_w = (qint32)(FZ/SA_FM);
            if (chpw_w < BW_MIN)
            {
                chpw_w = BW_MIN;
                globalUserVariable->gChannelBandwidth = chpw_w*globalUserVariable->gSpanFreq / gridWidth;
            }
            if (chpw_w > gridWidth)
            {
                chpw_w = gridWidth;
                //Johnson 0813
                globalUserVariable->gChannelBandwidth = chpw_w*globalUserVariable->gSpanFreq / gridWidth;
            }
            chpw_x = (gridWidth / 2)  - (chpw_w / 2);		// 좌우분할이므로 /2
        }

         //***********************************************************
#endif

        switch (globalUserVariable->currentMode)
        {
       case SA_ACP_MEASURE_MODE:
#if EXCHANGE_ACPMULTIACP
            drawACPPower(painter,mPixmapPixelStep,gridWidth);
            emit(refreshMeasureSet());
#else
            drawACPPower(painter,chpw_x,chpw_w,mPixmapPixelStep,gridWidth);
            if(globalUserVariable->dTmpChannelBandwidth != globalUserVariable->gChannelBandwidth ||
               globalUserVariable->dTmpChannelSpacing != globalUserVariable->gChannelSpacing)
               emit(refreshMeasureSet());
#endif
            break;       // 일부러 안함
       case SA_MULTI_ACP_MODE:
#if 1
            drawMultiACPPower(painter,mPixmapPixelStep,gridWidth);
#else
            drawMultiACPPower(painter,chpw_x,chpw_w,mPixmapPixelStep,gridWidth);
            if(globalUserVariable->dTmpChannelBandwidth != globalUserVariable->gChannelBandwidth ||
               globalUserVariable->dTmpChannelSpacing != globalUserVariable->gChannelSpacing)
#endif
               emit(refreshMeasureSet());
            break;
       case SA_CHNLPOWER_MEASURE_MODE:
        {
#if 0
            drawChannelPower(painter,chpw_x,chpw_w,mPixmapPixelStep,gridWidth);
#else
            drawChannelPower(painter,mPixmapPixelStep,gridWidth);
#endif
            if(globalUserVariable->dTmpChannelBandwidth != globalUserVariable->gChannelBandwidth)
               emit(refreshMeasureSet());
        }
            break;
        case SA_OCCUPIED_BW_MEASURE_MODE:
            drawOccupiedBWPower(painter,mPixmapPixelStep);
            break;
        case SA_SPECTRUM_EMISSION_MASK_MODE://draw spectrum emission limit
            if(SA_SPECEM_5GNR_CATEGORYA == globalUserVariable->gSpecEMMaskType)
            {
                drawSpectrumEmissionMask_5GNR_CategoryA(painter);
            }else if(SA_SPECEM_5GNR_CATEGORYB == globalUserVariable->gSpecEMMaskType)
            {
                drawSpectrumEmissionMask_5GNR_CategoryB(painter);
            }else if(SA_SPECEM_5GNR_P31_38== globalUserVariable->gSpecEMMaskType)
            {
                drawSpectrumEmissionMask_5GNR_P31_38(painter);
            }else if(SA_SPECEM_5GNR_P31 == globalUserVariable->gSpecEMMaskType)
            {
                drawSpectrumEmissionMask_5GNR_P31(painter);
            }
            else
            {
                drawSpectrumEmissionMask(painter);
            }
            break;
        case SA_SPURIOUS_EMISSION_MASK_MODE:
            drawSpuriousEmission(painter);
            break;
            }
        }
}
/**
 * @brief sa_UIRefresh_Control::drawSpectrumEmissionMask
 * @param painter
 * @note  draw spectrum Emission mask
 * @author Tony
 * */
void sa_UIRefresh_Control::drawSpectrumEmissionMask(QPainter *painter)
{

    //draw standard limit  absolute or relative
    qreal step = globalUserVariable->gTraceStepSize / SA_MHZ; // MHz
    qint32 centerPoint = (NUM_SWEEP_POINT + 1)/2 - 1;
    qint32 offset_1 = (globalUserVariable->gSpecEMData[0].start+globalUserVariable->gSpecEMRefChBw/2)/(globalUserVariable->gSpecEMRefChBw+25000000LL) * NUM_SWEEP_POINT;
    qint32 offset_2 = (globalUserVariable->gSpecEMData[1].start+globalUserVariable->gSpecEMRefChBw/2)/(globalUserVariable->gSpecEMRefChBw+25000000LL) * NUM_SWEEP_POINT;
    qint32 offset_3 = (globalUserVariable->gSpecEMData[2].start+globalUserVariable->gSpecEMRefChBw/2)/(globalUserVariable->gSpecEMRefChBw+25000000LL) * NUM_SWEEP_POINT;
    qint32 offset_4 = (globalUserVariable->gSpecEMData[3].start+globalUserVariable->gSpecEMRefChBw/2)/(globalUserVariable->gSpecEMRefChBw+25000000LL) * NUM_SWEEP_POINT;
    QPen oldPen = painter->pen();
    QPen mPen(QColor(115,210,22));
    mPen.setWidth(2);
    painter->setPen(mPen);
    if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE)
    {
        for (int k = 0; k < globalUserVariable->gSweepTracePoint; k++)
        {
            mSpecEMAbsLimit[k].setX(DRAW_GRID_START_X + k * mPixmapPixelStep);
            if(k > centerPoint - offset_1 && k< centerPoint + offset_1)
            {
                if(k == centerPoint - offset_1+1)
                {
                    mSpecEMAbsLimit[k].setX(DRAW_GRID_START_X + (k -1) * mPixmapPixelStep);
                    mSpecEMAbsLimit[k].setY(yaxis_cal(100 + globalUserVariable->gRefOffset)+ DRAW_GRID_START_Y);
                    globalUserLimit->gSpurLimit[k].setY(100 + globalUserVariable->gRefOffset);
                }else if(k == centerPoint + offset_1-1)
                {
                    mSpecEMAbsLimit[k].setX(DRAW_GRID_START_X + (k + 1) * mPixmapPixelStep);
                    mSpecEMAbsLimit[k].setY(yaxis_cal(100 + globalUserVariable->gRefOffset)+ DRAW_GRID_START_Y);
                    globalUserLimit->gSpurLimit[k].setY(100 + globalUserVariable->gRefOffset);
                }
            }
            else if((k<= centerPoint - offset_1 && k > centerPoint - offset_2) || \
               (k>= centerPoint + offset_1 && k < centerPoint + offset_2))
            {
                mSpecEMAbsLimit[k].setY(yaxis_cal(-14 + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y);
                globalUserLimit->gSpurLimit[k].setY(-14 + globalUserVariable->gRefOffset);
            }else if((k<= centerPoint - offset_2 && k > centerPoint - offset_3) || \
                     (k>= centerPoint + offset_2 && k < centerPoint + offset_3))
            {
                if(k>centerPoint)
                {
                    mSpecEMAbsLimit[k].setY(yaxis_cal(-14- 12 * (k - centerPoint  - offset_2)/(offset_3 - offset_2) + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y);
                    globalUserLimit->gSpurLimit[k].setY(-14- 12 * (k - centerPoint  - offset_2)/(offset_3 - offset_2) + globalUserVariable->gRefOffset);
                }else
                {
                    mSpecEMAbsLimit[k].setY(yaxis_cal(-14- 12 * (centerPoint - k - offset_2)/(offset_3 - offset_2) + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y);
                    globalUserLimit->gSpurLimit[k].setY(-14- 12 * (centerPoint - k - offset_2)/(offset_3 - offset_2) + globalUserVariable->gRefOffset);
                }

            }else if((k<= centerPoint - offset_3 && k > centerPoint - offset_4) || \
                     (k>= centerPoint + offset_3 && k < centerPoint + offset_4))
            {
                mSpecEMAbsLimit[k].setY(yaxis_cal(-26 + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y);
                globalUserLimit->gSpurLimit[k].setY(-26 + globalUserVariable->gRefOffset);
            }else if((k<= centerPoint - offset_4) || (k>= centerPoint + offset_4))
            {
                mSpecEMAbsLimit[k].setY(yaxis_cal(-13 + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y);
                globalUserLimit->gSpurLimit[k].setY(-13 + globalUserVariable->gRefOffset);
            }
        }
    }
    painter->drawPolyline(&mSpecEMAbsLimit[0], centerPoint - offset_1 +2);
    painter->drawPolyline(&mSpecEMAbsLimit[centerPoint + offset_1 - 1], centerPoint - offset_1 +2);
    painter->setPen(oldPen);
}

void sa_UIRefresh_Control::drawSpectrumEmissionMask_5GNR_CategoryA(QPainter *painter)
{
    //draw standard limit  absolute or relative
    qreal step = globalUserVariable->gTraceStepSize / SA_MHZ; // MHz
    qint32 centerPoint = (NUM_SWEEP_POINT + 1)/2 - 1;
    qint32 offset_1 = (globalUserVariable->gSpecEMData[0].start+globalUserVariable->gSpecEMRefChBw/2)/(globalUserVariable->gSpecEMRefChBw+280000000LL) * NUM_SWEEP_POINT;
    qint32 offset_2 = (globalUserVariable->gSpecEMData[1].start+globalUserVariable->gSpecEMRefChBw/2)/(globalUserVariable->gSpecEMRefChBw+280000000LL) * NUM_SWEEP_POINT;
    qint32 offset_3 = (globalUserVariable->gSpecEMData[2].start+globalUserVariable->gSpecEMRefChBw/2)/(globalUserVariable->gSpecEMRefChBw+280000000LL) * NUM_SWEEP_POINT;
    QPen oldPen = painter->pen();
    QPen mPen(QColor(115,210,22));
    mPen.setWidth(2);
    painter->setPen(mPen);
    if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE)
    {
        for (int k = 0; k < globalUserVariable->gSweepTracePoint; k++)
        {
            mSpecEMAbsLimit[k].setX(DRAW_GRID_START_X + k * mPixmapPixelStep);
            if(k > centerPoint - offset_1 && k< centerPoint + offset_1)
            {
                if(k == centerPoint - offset_1+1)
                {
                    mSpecEMAbsLimit[k].setX(DRAW_GRID_START_X + (k -1) * mPixmapPixelStep);
                    mSpecEMAbsLimit[k].setY(yaxis_cal(100 + globalUserVariable->gRefOffset)+ DRAW_GRID_START_Y);
                    globalUserLimit->gSpurLimit[k].setY(100 + globalUserVariable->gRefOffset);
                }else if(k == centerPoint + offset_1-1)
                {
                    mSpecEMAbsLimit[k].setX(DRAW_GRID_START_X + (k + 1) * mPixmapPixelStep);
                    mSpecEMAbsLimit[k].setY(yaxis_cal(100 + globalUserVariable->gRefOffset)+ DRAW_GRID_START_Y);
                    globalUserLimit->gSpurLimit[k].setY(100 + globalUserVariable->gRefOffset);
                }
            }
            else if((k<= centerPoint - offset_1 && k > centerPoint - offset_2) || \
               (k>= centerPoint + offset_1 && k < centerPoint + offset_2))
            {
                if(k>centerPoint)
                {
                    mSpecEMAbsLimit[k].setY(yaxis_cal(-5.2- 7.0 * (k - centerPoint-offset_1)/(offset_2 - offset_1) + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y);
                    globalUserLimit->gSpurLimit[k].setY(-5.2- 7.0 * (k - centerPoint-offset_1)/(offset_2 - offset_1) + globalUserVariable->gRefOffset);
                }else
                {
                    mSpecEMAbsLimit[k].setY(yaxis_cal(-5.2- 7.0 * (centerPoint - k-offset_1)/(offset_2 - offset_1) + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y);
                    globalUserLimit->gSpurLimit[k].setY(-5.2- 7.0 * (centerPoint - k-offset_1)/(offset_2 - offset_1) + globalUserVariable->gRefOffset);
                }

            }else if((k<= centerPoint - offset_2 && k > centerPoint - offset_3) || \
                     (k>= centerPoint + offset_2 && k < centerPoint + offset_3))
            {
                mSpecEMAbsLimit[k].setY(yaxis_cal(-12.2 + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y);
                globalUserLimit->gSpurLimit[k].setY(-12.2 + globalUserVariable->gRefOffset);
            }else if((k<= centerPoint - offset_3) || (k>= centerPoint + offset_3))
            {
                mSpecEMAbsLimit[k].setY(yaxis_cal(-13 + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y);
                globalUserLimit->gSpurLimit[k].setY(-13 + globalUserVariable->gRefOffset);
            }
        }
    }
    painter->drawPolyline(&mSpecEMAbsLimit[0], centerPoint - offset_1 +2);
    painter->drawPolyline(&mSpecEMAbsLimit[centerPoint + offset_1 - 1], centerPoint - offset_1 +2);
    painter->setPen(oldPen);
}
void sa_UIRefresh_Control::drawSpectrumEmissionMask_5GNR_CategoryB(QPainter *painter)
{
    //draw standard limit  absolute or relative
    qreal step = globalUserVariable->gTraceStepSize / SA_MHZ; // MHz
    qint32 centerPoint = (NUM_SWEEP_POINT + 1)/2 - 1;
    qint32 offset_1 = (globalUserVariable->gSpecEMData[0].start+globalUserVariable->gSpecEMRefChBw/2)/(globalUserVariable->gSpecEMRefChBw+280000000LL) * NUM_SWEEP_POINT;
    qint32 offset_2 = (globalUserVariable->gSpecEMData[1].start+globalUserVariable->gSpecEMRefChBw/2)/(globalUserVariable->gSpecEMRefChBw+280000000LL) * NUM_SWEEP_POINT;
    qint32 offset_3 = (globalUserVariable->gSpecEMData[2].start+globalUserVariable->gSpecEMRefChBw/2)/(globalUserVariable->gSpecEMRefChBw+280000000LL) * NUM_SWEEP_POINT;
    QPen oldPen = painter->pen();
    QPen mPen(QColor(115,210,22));
    mPen.setWidth(2);
    painter->setPen(mPen);
    if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE)
    {
        for (int k = 0; k < globalUserVariable->gSweepTracePoint; k++)
        {
            mSpecEMAbsLimit[k].setX(DRAW_GRID_START_X + k * mPixmapPixelStep);
            if(k > centerPoint - offset_1 && k< centerPoint + offset_1)
            {
                if(k == centerPoint - offset_1+1)
                {
                    mSpecEMAbsLimit[k].setX(DRAW_GRID_START_X + (k -1) * mPixmapPixelStep);
                    mSpecEMAbsLimit[k].setY(yaxis_cal(100 + globalUserVariable->gRefOffset)+ DRAW_GRID_START_Y);
                    globalUserLimit->gSpurLimit[k].setY(100 + globalUserVariable->gRefOffset);
                }else if(k == centerPoint + offset_1-1)
                {
                    mSpecEMAbsLimit[k].setX(DRAW_GRID_START_X + (k + 1) * mPixmapPixelStep);
                    mSpecEMAbsLimit[k].setY(yaxis_cal(100 + globalUserVariable->gRefOffset)+ DRAW_GRID_START_Y);
                    globalUserLimit->gSpurLimit[k].setY(100 + globalUserVariable->gRefOffset);
                }
            }
            else if((k<= centerPoint - offset_1 && k > centerPoint - offset_2) || \
               (k>= centerPoint + offset_1 && k < centerPoint + offset_2))
            {
                if(k>centerPoint)
                {
                    mSpecEMAbsLimit[k].setY(yaxis_cal(-5.2- 7.0 * (k - centerPoint-offset_1)/(offset_2 - offset_1) + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y);
                    globalUserLimit->gSpurLimit[k].setY(-5.2- 7.0 * (k - centerPoint-offset_1)/(offset_2 - offset_1) + globalUserVariable->gRefOffset);
                }else
                {
                    mSpecEMAbsLimit[k].setY(yaxis_cal(-5.2- 7.0 * (centerPoint - k-offset_1)/(offset_2 - offset_1) + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y);
                    globalUserLimit->gSpurLimit[k].setY(-5.2- 7.0 * (centerPoint - k-offset_1)/(offset_2 - offset_1) + globalUserVariable->gRefOffset);
                }

            }else if((k<= centerPoint - offset_2 && k > centerPoint - offset_3) || \
                     (k>= centerPoint + offset_2 && k < centerPoint + offset_3))
            {
                mSpecEMAbsLimit[k].setY(yaxis_cal(-12.2 + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y);
                globalUserLimit->gSpurLimit[k].setY(-12.2 + globalUserVariable->gRefOffset);
            }else if((k<= centerPoint - offset_3) || (k>= centerPoint + offset_3))
            {
                mSpecEMAbsLimit[k].setY(yaxis_cal(-15 + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y);
                globalUserLimit->gSpurLimit[k].setY(-15 + globalUserVariable->gRefOffset);
            }
        }
    }
    painter->drawPolyline(&mSpecEMAbsLimit[0], centerPoint - offset_1 +2);
    painter->drawPolyline(&mSpecEMAbsLimit[centerPoint + offset_1 - 1], centerPoint - offset_1 +2);
    painter->setPen(oldPen);
}
void sa_UIRefresh_Control::drawSpectrumEmissionMask_5GNR_P31_38(QPainter *painter)
{
    //draw standard limit  absolute or relative
    qreal step = globalUserVariable->gTraceStepSize / SA_MHZ; // MHz
    qint32 centerPoint = (NUM_SWEEP_POINT + 1)/2 - 1;
    qint32 offset_1 = (globalUserVariable->gSpecEMData[0].start+globalUserVariable->gSpecEMRefChBw/2)/(globalUserVariable->gSpecEMRefChBw+280000000LL) * NUM_SWEEP_POINT;
    qint32 offset_2 = (globalUserVariable->gSpecEMData[1].start+globalUserVariable->gSpecEMRefChBw/2)/(globalUserVariable->gSpecEMRefChBw+280000000LL) * NUM_SWEEP_POINT;
    qint32 offset_3 = (globalUserVariable->gSpecEMData[2].start+globalUserVariable->gSpecEMRefChBw/2)/(globalUserVariable->gSpecEMRefChBw+280000000LL) * NUM_SWEEP_POINT;
    QPen oldPen = painter->pen();
    QPen mPen(QColor(115,210,22));
    mPen.setWidth(2);
    painter->setPen(mPen);
    qint32 mLimitVal = (globalUserVariable->gSpecEMBsPower -60)<(-25)?(globalUserVariable->gSpecEMBsPower -60):(-25);
    if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE)
    {
        for (int k = 0; k < globalUserVariable->gSweepTracePoint; k++)
        {
            mSpecEMAbsLimit[k].setX(DRAW_GRID_START_X + k * mPixmapPixelStep);
            if(k > centerPoint - offset_1 && k< centerPoint + offset_1)
            {
                if(k == centerPoint - offset_1+1)
                {
                    mSpecEMAbsLimit[k].setX(DRAW_GRID_START_X + (k -1) * mPixmapPixelStep);
                    mSpecEMAbsLimit[k].setY(yaxis_cal(100 + globalUserVariable->gRefOffset)+ DRAW_GRID_START_Y);
                    globalUserLimit->gSpurLimit[k].setY(100 + globalUserVariable->gRefOffset);
                }else if(k == centerPoint + offset_1-1)
                {
                    mSpecEMAbsLimit[k].setX(DRAW_GRID_START_X + (k + 1) * mPixmapPixelStep);
                    mSpecEMAbsLimit[k].setY(yaxis_cal(100 + globalUserVariable->gRefOffset)+ DRAW_GRID_START_Y);
                    globalUserLimit->gSpurLimit[k].setY(100 + globalUserVariable->gRefOffset);
                }
            }
            else if((k<= centerPoint - offset_1 && k > centerPoint - offset_2) || \
               (k>= centerPoint + offset_1 && k < centerPoint + offset_2))
            {
                if(k>centerPoint)
                {
                    mSpecEMAbsLimit[k].setY(yaxis_cal(globalUserVariable->gSpecEMBsPower-51.2- 7.0 * (k - centerPoint-offset_1)/(offset_2 - offset_1) + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y);
                    globalUserLimit->gSpurLimit[k].setY(globalUserVariable->gSpecEMBsPower-51.2- 7.0 * (k - centerPoint-offset_1)/(offset_2 - offset_1) + globalUserVariable->gRefOffset);
                }else
                {
                    mSpecEMAbsLimit[k].setY(yaxis_cal(globalUserVariable->gSpecEMBsPower-51.2- 7.0 * (centerPoint - k-offset_1)/(offset_2 - offset_1) + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y);
                    globalUserLimit->gSpurLimit[k].setY(globalUserVariable->gSpecEMBsPower-51.2- 7.0 * (centerPoint - k-offset_1)/(offset_2 - offset_1) + globalUserVariable->gRefOffset);
                }

            }else if((k<= centerPoint - offset_2 && k > centerPoint - offset_3) || \
                     (k>= centerPoint + offset_2 && k < centerPoint + offset_3))
            {
                mSpecEMAbsLimit[k].setY(yaxis_cal(globalUserVariable->gSpecEMBsPower-58.2 + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y);
                globalUserLimit->gSpurLimit[k].setY(globalUserVariable->gSpecEMBsPower-58.2 + globalUserVariable->gRefOffset);
            }else if((k<= centerPoint - offset_3) || (k>= centerPoint + offset_3))
            {
                mSpecEMAbsLimit[k].setY(yaxis_cal(mLimitVal + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y);
                globalUserLimit->gSpurLimit[k].setY(mLimitVal + globalUserVariable->gRefOffset);
            }
        }
    }
    painter->drawPolyline(&mSpecEMAbsLimit[0], centerPoint - offset_1 +2);
    painter->drawPolyline(&mSpecEMAbsLimit[centerPoint + offset_1 - 1], centerPoint - offset_1 +2);
    painter->setPen(oldPen);
}
void sa_UIRefresh_Control::drawSpectrumEmissionMask_5GNR_P31(QPainter *painter)
{
    //draw standard limit  absolute or relative
    qreal step = globalUserVariable->gTraceStepSize / SA_MHZ; // MHz
    qint32 centerPoint = (NUM_SWEEP_POINT + 1)/2 - 1;
    qint32 offset_1 = (globalUserVariable->gSpecEMData[0].start+globalUserVariable->gSpecEMRefChBw/2)/(globalUserVariable->gSpecEMRefChBw+280000000LL) * NUM_SWEEP_POINT;
    qint32 offset_2 = (globalUserVariable->gSpecEMData[1].start+globalUserVariable->gSpecEMRefChBw/2)/(globalUserVariable->gSpecEMRefChBw+280000000LL) * NUM_SWEEP_POINT;
    qint32 offset_3 = (globalUserVariable->gSpecEMData[2].start+globalUserVariable->gSpecEMRefChBw/2)/(globalUserVariable->gSpecEMRefChBw+280000000LL) * NUM_SWEEP_POINT;
    QPen oldPen = painter->pen();
    QPen mPen(QColor(115,210,22));
    mPen.setWidth(2);
    painter->setPen(mPen);
    if(globalUserVariable->currentMode == SA_SPECTRUM_EMISSION_MASK_MODE)
    {
        for (int k = 0; k < globalUserVariable->gSweepTracePoint; k++)
        {
            mSpecEMAbsLimit[k].setX(DRAW_GRID_START_X + k * mPixmapPixelStep);
            if(k > centerPoint - offset_1 && k< centerPoint + offset_1)
            {
                if(k == centerPoint - offset_1+1)
                {
                    mSpecEMAbsLimit[k].setX(DRAW_GRID_START_X + (k -1) * mPixmapPixelStep);
                    mSpecEMAbsLimit[k].setY(yaxis_cal(100 + globalUserVariable->gRefOffset)+ DRAW_GRID_START_Y);
                    globalUserLimit->gSpurLimit[k].setY(100 + globalUserVariable->gRefOffset);
                }else if(k == centerPoint + offset_1-1)
                {
                    mSpecEMAbsLimit[k].setX(DRAW_GRID_START_X + (k + 1) * mPixmapPixelStep);
                    mSpecEMAbsLimit[k].setY(yaxis_cal(100 + globalUserVariable->gRefOffset)+ DRAW_GRID_START_Y);
                    globalUserLimit->gSpurLimit[k].setY(100 + globalUserVariable->gRefOffset);
                }
            }
            else if((k<= centerPoint - offset_1 && k > centerPoint - offset_2) || \
               (k>= centerPoint + offset_1 && k < centerPoint + offset_2))
            {
                if(k>centerPoint)
                {
                    mSpecEMAbsLimit[k].setY(yaxis_cal(-20.2- 7.0 * (k - centerPoint-offset_1)/(offset_2 - offset_1) + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y);
                    globalUserLimit->gSpurLimit[k].setY(-20.2- 7.0 * (k - centerPoint-offset_1)/(offset_2 - offset_1) + globalUserVariable->gRefOffset);
                }else
                {
                    mSpecEMAbsLimit[k].setY(yaxis_cal(-20.2- 7.0 * (centerPoint - k-offset_1)/(offset_2 - offset_1) + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y);
                    globalUserLimit->gSpurLimit[k].setY(-20.2- 7.0 * (centerPoint - k-offset_1)/(offset_2 - offset_1) + globalUserVariable->gRefOffset);
                }

            }else if((k<= centerPoint - offset_2 && k > centerPoint - offset_3) || \
                     (k>= centerPoint + offset_2 && k < centerPoint + offset_3))
            {
                mSpecEMAbsLimit[k].setY(yaxis_cal(-27.2 + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y);
                globalUserLimit->gSpurLimit[k].setY(-27.2 + globalUserVariable->gRefOffset);
            }else if((k<= centerPoint - offset_3) || (k>= centerPoint + offset_3))
            {
                mSpecEMAbsLimit[k].setY(yaxis_cal(-29 + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y);
                globalUserLimit->gSpurLimit[k].setY(-29 + globalUserVariable->gRefOffset);
            }
        }
    }
    painter->drawPolyline(&mSpecEMAbsLimit[0], centerPoint - offset_1 +2);
    painter->drawPolyline(&mSpecEMAbsLimit[centerPoint + offset_1 - 1], centerPoint - offset_1 +2);
    painter->setPen(oldPen);
}
/**
 * @brief sa_UIRefresh_Control::drawSpuriousEmission
 * @param painter
 * @note  draw spurious emission
 * @author Tony
 * */
void sa_UIRefresh_Control::drawSpuriousEmission(QPainter *painter)
{
    QPen oldPen = painter->pen();
    QPen mPen(QColor(115,210,22));
    mPen.setWidth(2);
    painter->setPen(mPen);

    qint32 size = globalUserVariable->gSweepTracePoint;
    qreal valueSlope,Slope,startY,stopY,startLimit,stopLimit,mFreq;
    startLimit = globalUserVariable->gSpurEMPara[globalUserVariable->gSpurEMCurDrawRangeIndex].startLimit;
    stopLimit  = globalUserVariable->gSpurEMPara[globalUserVariable->gSpurEMCurDrawRangeIndex].stopLimit;
    startY = yaxis_cal(startLimit) + DRAW_GRID_START_Y;
    stopY = yaxis_cal(stopLimit) + DRAW_GRID_START_Y;
    Slope = (qreal)(stopY - startY)/size;
    valueSlope = (qreal)(stopLimit - startLimit)/size;
    if(globalUserVariable->currentMode == SA_SPURIOUS_EMISSION_MASK_MODE)
    {
        for(qint32 i = 0;i < NUM_SWEEP_POINT;i++)
        {
            mFreq = DRAW_GRID_START_X + i * mPixmapPixelStep;
            gSpurLimit[i].setX(mFreq);
            gSpurLimit[i].setY(startY+i*Slope);

            globalUserLimit->gSpurLimit[i].setX(mFreq);
            globalUserLimit->gSpurLimit[i].setY(startLimit+i*valueSlope);
        }
    }
    painter->drawPolyline(&gSpurLimit[0], NUM_SWEEP_POINT);
    painter->setPen(oldPen);
}


/**
 * @brief sa_UIRefresh_Control::drawCurves
 * @param painter
 * @note  draw sa
 * @author Johnson
 */
void sa_UIRefresh_Control::drawCurves(QPainter *painter)
{
    qint32 colorMode = globalUserVariable->gDisplayMode;
    QColor mTraceColor[TRACE_CNT_TOTAL] = TraceColor[colorMode];
    //memcpy(mTraceColor,TraceColor[colorMode],sizeof(QColor)*TRACE_CNT_TOTAL);
    for (qint32 i = 0; i < NUM_TRACE; i++ )
    {
        if (globalUserVariable->gTraceSelect != i)
        {
//            if (globalUserVariable->gTraceType[i] != SA_TRACE_OFF)
            if (globalUserVariable->gTraceView[i] != SA_OFF)
            {
                painter->setPen(mTraceColor[i]); //Tony 190614
#if 1
                painter->drawPolyline(&mPixmap_draw_point[i][0], globalUserVariable->gSweepTracePoint);
#else
                for(qint32 j = 0;j<globalUserVariable->gSweepTracePoint - 1;j++)
                {
                    painter->drawLine(mPixmap_draw_point[i][j].x(),mPixmap_draw_point[i][j].y(),mPixmap_draw_point[i][j+1].x(),mPixmap_draw_point[i][j+1].y());
                }
#endif
            }
        }
    }
//    if (globalUserVariable->gTraceType[globalUserVariable->gTraceSelect] != SA_TRACE_OFF)
    if (globalUserVariable->gTraceView[globalUserVariable->gTraceSelect] != SA_OFF)
    {
        painter->setPen(mTraceColor[globalUserVariable->gTraceSelect]); //Tony 190614
#if 1
        painter->drawPolyline(&mPixmap_draw_point[globalUserVariable->gTraceSelect][0], globalUserVariable->gSweepTracePoint);
#else
        for(qint32 j = 0;j<globalUserVariable->gSweepTracePoint - 1;j++)
        {
            painter->drawLine(mPixmap_draw_point[globalUserVariable->gTraceSelect][j].x(),mPixmap_draw_point[globalUserVariable->gTraceSelect][j].y(),
                    mPixmap_draw_point[globalUserVariable->gTraceSelect][j+1].x(),mPixmap_draw_point[globalUserVariable->gTraceSelect][j+1].y());
        }
#endif
    }
}
/**
 * @brief sa_UIRefresh_Control::drawLimitCurves
 * @param painter
 * @author Johnson
 */
void sa_UIRefresh_Control::drawLimitCurves(QPainter *painter)
{
    //Johnson 190321
    if(globalUserVariable->gTraceView[globalUserVariable->gTraceSelect] == SA_OFF)
    {
        return;
    }

    for(qint32 j = 0;j<LIMIT_SELECTSUM;j++)
    {
        for(qint32 i = 0;i<globalUserLimit->gTotalDot[j];i++)
        {
            //caculate x index of every limit's dot
            globalUserLimit->limitXAxisCalculatorFunc((quint64)(globalUserLimit->gFreq[j][i]*SA_MHZ),i,j);
            //caculate y axis of every limit's dot
            globalUserLimit->LatestLimitYAxisCalculatorFunc(globalUserLimit->gAmplitude[j][i],i,j);
        }
        //get the y axis inside the limit dot rang
        globalUserLimit->LatestLimitLineInterpolationCalculatorFunc(j);
    }
    //get all dots'x_axis and y_axis
    globalUserLimit->getLowerUpperLimitLineInterpolation();

    drawLatestLimitEdge(painter);
    drawLatestLimitLine(painter);
    judgeLimitTestResult();
//    if(globalUserVariable->gTraceType[globalUserVariable->gTraceSelect] != SA_TRACE_OFF)
    if(globalUserVariable->gTraceView[globalUserVariable->gTraceSelect] != SA_OFF)
        drawApplyLimitSettingSweepGraphDisplay(painter);
    if(globalUserVariable->gTraceView[globalUserVariable->gTraceSelect] != SA_OFF)
    {
        bool bTrPass = true;
        for(qint32 i = 0;i<LIMIT_SELECTSUM;i++)
        {
            if(globalUserLimit->gLimitTest == SA_ON && globalUserLimit->gLimitLine[i] == SA_ON)
            {
                if (globalUserLimit->gLatestLimitTestResult[i] == SA_FAIL)
                {
                    painter->setPen(Qt::red);
                    painter->setFont(QFont("Arial", 11));
                    painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "TR: FAIL");
                    bTrPass = false;
                    break;
                }
            }
        }

        if(bTrPass && globalUserLimit->gLimitTest == SA_ON)
        {
            for(qint32 i = 0;i<LIMIT_SELECTSUM;i++)
            {
                if(globalUserLimit->gLimitEdge[i] == SA_ON){
                    if(globalUserLimit->gLatestLimitEdgeResult[i] == SA_FAIL)
                    {
                        painter->setPen(Qt::red);
                        painter->setFont(QFont("Arial", 11));
                        painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "TR EDGE: FAIL");
                        bTrPass = false;
                        break;
                    }
                }
            }
        }

        if(bTrPass && globalUserLimit->gLimitTest == SA_ON)
        {
            painter->setPen(Qt::green);
            painter->setFont(QFont("Arial", 11));
            painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "TR: PASS");
        }
   }
}
/**
 * @brief sa_UIRefresh_Control::judgeLimitTestResult
 * @note  judge the test result of limit
 * @author Johnson
 */
void sa_UIRefresh_Control::judgeLimitTestResult()
{
    qint32 manualStartXPos = 0;
    qint32 manualStopXPos  = 0;

    qint32 manualTotalDot  = 0;

    for(qint32 i = 0;i<LIMIT_SELECTSUM;i++)
    {
        globalUserLimit->gLatestLimitTestResult[i] = SA_PASS;
        if(globalUserLimit->gLimitLine[i] == SA_OFF) continue;

        manualTotalDot = globalUserLimit->gTotalDot[i];
        manualStartXPos = globalUserLimit->gXIndex[i][0];
        manualStopXPos  = globalUserLimit->gXIndex[i][manualTotalDot-1];

        if(globalUserLimit->gLatestLimitType[i] == UPPER)
        {
            for(qint32 j = manualStartXPos;j < manualStopXPos;j++)
            {
                /*
                if(globalUserVariable->bSmallCanvas)
                {
                    if(smallPixmap_draw_point[globalUserVariable->gTraceSelect][j].y()<globalUserLimit->gLatestLimitDrawPoint[i][j])
                    {
                        globalUserLimit->gLatestLimitTestResult = SA_FAIL;
                        break;
                    }
                }
                else
                {
                    if(largePixmap_draw_point[globalUserVariable->gTraceSelect][j].y()<globalUserLimit->gLatestLimitDrawPoint[i][j])
                    {
                        globalUserLimit->gLatestLimitTestResult = SA_FAIL;
                        break;
                    }
                }
            */
                if(mPixmap_draw_point[globalUserVariable->gTraceSelect][j].y()<globalUserLimit->gLatestLimitDrawPoint[i][j])
                {
                    globalUserLimit->gLatestLimitTestResult[i] = SA_FAIL;
                    break;
                }
            }
        }
        else if(globalUserLimit->gLatestLimitType[i] == LOWER)
        {
            for(qint32 j = manualStartXPos;j < manualStopXPos;j++)
            {
                /*
                if(globalUserVariable->bSmallCanvas)
                {
                    if(smallPixmap_draw_point[globalUserVariable->gTraceSelect][j].y()>globalUserLimit->gLatestLimitDrawPoint[i][j])
                    {
                        globalUserLimit->gLatestLimitTestResult = SA_FAIL;
                        break;
                    }
                }
                else
                {
                    if(largePixmap_draw_point[globalUserVariable->gTraceSelect][j].y()>globalUserLimit->gLatestLimitDrawPoint[i][j])
                    {
                        globalUserLimit->gLatestLimitTestResult = SA_FAIL;
                        break;
                    }
                }
            */
                if(mPixmap_draw_point[globalUserVariable->gTraceSelect][j].y()>globalUserLimit->gLatestLimitDrawPoint[i][j])
                {
                    globalUserLimit->gLatestLimitTestResult[i] = SA_FAIL;
                    break;
                }
            }
        }
        //if(globalUserLimit->gLatestLimitTestResult == SA_FAIL) return;
    }

    for(qint32 i = 0;i<LIMIT_SELECTSUM;i++)
    {
        globalUserLimit->gLatestLimitEdgeResult[i] = SA_PASS;
        if(globalUserLimit->gLimitEdge[i] == SA_OFF) continue;

        manualTotalDot = globalUserLimit->gTotalDot[i];
        manualStartXPos = globalUserLimit->gXIndex[i][0];
        manualStopXPos  = globalUserLimit->gXIndex[i][manualTotalDot-1];

        if(globalUserLimit->gLatestLimitType[i] == UPPER)
        {
            for(qint32 j = manualStartXPos;j < manualStopXPos;j++)
            {
               /*
                if(globalUserVariable->bSmallCanvas)
                {
                    if(smallPixmap_draw_point[globalUserVariable->gTraceSelect][j].y()<globalUserLimit->gLatestLimitEdgeDrawPoint[i][j])
                    {
                        globalUserLimit->gLatestLimitEdgeResult = SA_FAIL;
                        break;
                    }
                }
                else
                {
                    if(largePixmap_draw_point[globalUserVariable->gTraceSelect][j].y()<globalUserLimit->gLatestLimitEdgeDrawPoint[i][j])
                    {
                        globalUserLimit->gLatestLimitEdgeResult = SA_FAIL;
                        break;
                    }
                }
            */
                if(mPixmap_draw_point[globalUserVariable->gTraceSelect][j].y()<globalUserLimit->gLatestLimitEdgeDrawPoint[i][j])
                {
                    globalUserLimit->gLatestLimitEdgeResult[i] = SA_FAIL;
                    break;
                }
            }
        }
        else if(globalUserLimit->gLatestLimitType[i] == LOWER)
        {
            for(qint32 j = manualStartXPos;j < manualStopXPos;j++)
            {
                /*
                if(globalUserVariable->bSmallCanvas)
                {
                    if(smallPixmap_draw_point[globalUserVariable->gTraceSelect][j].y()>globalUserLimit->gLatestLimitEdgeDrawPoint[i][j])
                    {
                        globalUserLimit->gLatestLimitEdgeResult = SA_FAIL;
                        break;
                    }
                }
                else
                {
                    if(largePixmap_draw_point[globalUserVariable->gTraceSelect][j].y()>globalUserLimit->gLatestLimitEdgeDrawPoint[i][j])
                    {
                        globalUserLimit->gLatestLimitEdgeResult = SA_FAIL;
                        break;
                    }
                }
                */
                if(mPixmap_draw_point[globalUserVariable->gTraceSelect][j].y()>globalUserLimit->gLatestLimitEdgeDrawPoint[i][j])
                {
                    globalUserLimit->gLatestLimitEdgeResult[i] = SA_FAIL;
                    break;
                }
            }
        }
        //if(globalUserLimit->gLatestLimitEdgeResult == SA_FAIL) return;
    }
}
/**
 * @brief sa_UIRefresh_Control::drawLatestLimitEdge
 * @param painter
 * @note  draw the edge of limit
 * @author Johnson
 */
void sa_UIRefresh_Control::drawLatestLimitEdge(QPainter *painter)
{
    qint32 i = 0;
    qint32 k = 0;
    qint32 StartXPos = 0;
    qint32 StopXPos = 0;

    //Johnson 0829 Add
    qreal StartXAxis = 0.;
    qreal StartYAxis = 0.;
    qreal StopXAxis  = 0.;
    qreal StopYAxis  = 0.;
    qreal dSlope     = 0.;//xielv

    qreal dEdge      = 0.;

    qreal pixelStep = 0.;
    qint32 colorMode = globalUserVariable->gDisplayMode;
    QColor mEdgeColor[2] = EdgeColor[colorMode];
//    if(globalUserVariable->bSmallCanvas) pixelStep = smallPixmapPixelStep;
//    else pixelStep = largePixmapPixelStep;

    pixelStep = mPixmapPixelStep;
    //Drawing  Upper Sengment Limit Line
    for (k = 0; k < LIMIT_SELECTSUM; k++)
    {
        if(globalUserLimit->gLimitEdge[k] == SA_OFF) continue;
        if(globalUserLimit->gLimitEdgeValue[k] == 0.) continue;
        if(globalUserLimit->gLimitLine[k] == SA_OFF) continue;
        if(globalUserLimit->gTotalDot[k] == 0)   continue;

        QPen globalPen;
     //   if (globalUserLimit->gLatestLimitType[k] == UPPER) globalPen = QPen(QColor(250,174,2));
    //    else if (globalUserLimit->gLatestLimitType[k] == LOWER) globalPen = QPen(Qt::cyan);
        globalPen = QPen(mEdgeColor[globalUserLimit->gLatestLimitType[k]-1]);
        globalPen.setStyle(Qt::DotLine);
        painter->setPen(globalPen);

        if (globalUserLimit->gLatestLimitType[k] == UPPER) dEdge = -globalUserLimit->gLimitEdgeValue[k];
        else if (globalUserLimit->gLatestLimitType[k] == LOWER) dEdge = globalUserLimit->gLimitEdgeValue[k];

        for(i = 1;i<globalUserLimit->gTotalDot[k];i++)
        {
            StartXPos = globalUserLimit->gXIndex[k][i-1];
            StopXPos  = globalUserLimit->gXIndex[k][i];

            if (StartXPos == 0 && StopXPos == 0) break;

            //Johnson 0910
            StartXAxis = StartXPos * pixelStep+DRAW_GRID_START_X;
            StartYAxis = globalUserLimit->gEdgeYAxis[k][i-1];
            StopXAxis  = StopXPos* pixelStep+DRAW_GRID_START_X;
            StopYAxis  = globalUserLimit->gEdgeYAxis[k][i];
            globalUserLimit->gXAxis[k][i-1] = StartXAxis;
            globalUserLimit->gXAxis[k][i]   = StopXAxis;

            if(StopXAxis-StartXAxis != 0) dSlope = (StopYAxis-StartYAxis)/(StopXAxis-StartXAxis);


            //Johnson 0910 change
            if(globalUserLimit->gAmplitude[k][i-1] + dEdge >globalUserVariable->topLevel||globalUserLimit->gAmplitude[k][i-1] + dEdge <globalUserVariable->lowLevel||
                    globalUserLimit->gAmplitude[k][i] + dEdge >globalUserVariable->topLevel||globalUserLimit->gAmplitude[k][i] + dEdge <globalUserVariable->lowLevel)
            {
                if(StartXAxis == StopXAxis)
                {
                    if(StartYAxis<DRAW_GRID_START_Y)                          StartYAxis = DRAW_GRID_START_Y;
                    else if(StartYAxis>globalUserVariable->gridYPos[10]) StartYAxis = globalUserVariable->gridYPos[10];
                    if(StopYAxis<DRAW_GRID_START_Y)                           StopYAxis  = DRAW_GRID_START_Y;
                    else if(StopYAxis>globalUserVariable->gridYPos[10])  StopYAxis  = globalUserVariable->gridYPos[10];
                    painter->drawLine(StartXAxis, StartYAxis, StopXAxis,  StopYAxis);
                }
                else if(dSlope == 0)
                {
                    if(StartYAxis<DRAW_GRID_START_Y)
                    {
                        StartYAxis = DRAW_GRID_START_Y;
                        StopYAxis = DRAW_GRID_START_Y;
                    }
                    else if(StopYAxis>globalUserVariable->gridYPos[10])
                    {
                        StartYAxis = globalUserVariable->gridYPos[10];
                        StopYAxis = globalUserVariable->gridYPos[10];
                    }
                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
                else
                {
                    qreal constC = StartYAxis-dSlope*StartXAxis;

                    if(dSlope>0)
                    {
                        if(globalUserLimit->gAmplitude[k][i-1] + dEdge > globalUserVariable->topLevel)
                        {
                            if(globalUserLimit->gAmplitude[k][i] + dEdge >= globalUserVariable->topLevel)
                            {
                                QPen pen;
                                // if (globalUserLimit->gLatestLimitType[k] == UPPER) pen = QPen(Qt::darkRed);
                                // else if (globalUserLimit->gLatestLimitType[k] == LOWER) pen = QPen(Qt::cyan);
                                pen = QPen(mEdgeColor[globalUserLimit->gLatestLimitType[k]-1]);
                                pen.setStyle(Qt::DotLine);
                                pen.setWidth(2);
                                painter->setPen(pen);
                                painter->drawLine(StartXAxis,DRAW_GRID_START_Y,StopXAxis,DRAW_GRID_START_Y);
                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                            else if(globalUserLimit->gAmplitude[k][i] + dEdge <globalUserVariable->topLevel&&globalUserLimit->gAmplitude[k][i] + dEdge >=globalUserVariable->lowLevel)
                            {
                                qreal tempY = DRAW_GRID_START_Y;
                                qreal tempX = (tempY-constC)/dSlope;
                                painter->drawLine(tempX, tempY, StopXAxis,  StopYAxis);

                                QPen pen;
                                //if (globalUserLimit->gLatestLimitType[k] == UPPER) pen = QPen(Qt::darkRed);
                                //else if (globalUserLimit->gLatestLimitType[k] == LOWER) pen = QPen(Qt::cyan);
                                pen = QPen(mEdgeColor[globalUserLimit->gLatestLimitType[k]-1]);
                                pen.setStyle(Qt::DotLine);
                                pen.setWidth(2);
                                painter->setPen(pen);
                                painter->drawLine(StartXAxis,tempY,tempX,tempY);
                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                            else if(globalUserLimit->gAmplitude[k][i] + dEdge < globalUserVariable->lowLevel)
                            {
                                qreal tempY1 = DRAW_GRID_START_Y;
                                qreal tempX1 = (tempY1-constC)/dSlope;
                                qreal tempY2 = globalUserVariable->gridYPos[10];
                                qreal tempX2 = (tempY2-constC)/dSlope;

                                painter->drawLine(tempX1, tempY1, tempX2,  tempY2);

                                QPen pen;
                                //if (globalUserLimit->gLatestLimitType[k] == UPPER) pen = QPen(Qt::darkRed);
                                //else if (globalUserLimit->gLatestLimitType[k] == LOWER) pen = QPen(Qt::cyan);
                                pen = QPen(mEdgeColor[globalUserLimit->gLatestLimitType[k]-1]);
                                pen.setStyle(Qt::DotLine);
                                pen.setWidth(2);
                                painter->setPen(pen);

                                painter->drawLine(StartXAxis, tempY1, tempX1,  tempY1);
                                painter->drawLine(tempX2, tempY2, StopXAxis,  tempY2);

                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                        }
                        else if(globalUserLimit->gAmplitude[k][i-1] + dEdge <= globalUserVariable->topLevel&&globalUserLimit->gAmplitude[k][i-1] + dEdge >= globalUserVariable->lowLevel)
                        {
                           if(globalUserLimit->gAmplitude[k][i] + dEdge < globalUserVariable->lowLevel)
                           {
                                qreal tempY = globalUserVariable->gridYPos[10];
                                qreal tempX = (tempY-constC)/dSlope;

                                painter->drawLine(StartXAxis, StartYAxis, tempX,  tempY);

                                QPen pen;
                                //if (globalUserLimit->gLatestLimitType[k] == UPPER) pen = QPen(Qt::darkRed);
                                //else if (globalUserLimit->gLatestLimitType[k] == LOWER) pen = QPen(Qt::cyan);
                                pen = QPen(mEdgeColor[globalUserLimit->gLatestLimitType[k]-1]);
                                pen.setStyle(Qt::DotLine);
                                pen.setWidth(2);
                                painter->setPen(pen);
                                painter->drawLine(tempX, tempY, StopXAxis,  tempY);
                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                        }
                        else if(globalUserLimit->gAmplitude[globalUserLimit->gLimitSelect][i-1] + dEdge < globalUserVariable->lowLevel)
                        {
                            QPen pen;
                            //if (globalUserLimit->gLatestLimitType[k] == UPPER) pen = QPen(Qt::darkRed);
                            //else if (globalUserLimit->gLatestLimitType[k] == LOWER) pen = QPen(Qt::cyan);
                            pen = QPen(mEdgeColor[globalUserLimit->gLatestLimitType[k]-1]);
                            pen.setStyle(Qt::DotLine);
                            pen.setWidth(2);
                            painter->setPen(pen);
                            painter->drawLine(StartXAxis,globalUserVariable->gridYPos[10],StopXAxis,globalUserVariable->gridYPos[10]);
                            pen.setWidth(1);
                            painter->setPen(pen);
                        }
                    }
                    else if(dSlope<0)
                    {
                        if(globalUserLimit->gAmplitude[k][i-1] + dEdge < globalUserVariable->lowLevel)
                        {
                            if(globalUserLimit->gAmplitude[k][i] + dEdge <= globalUserVariable->lowLevel)
                            {
                                QPen pen;
                                //if (globalUserLimit->gLatestLimitType[k] == UPPER) pen = QPen(Qt::darkRed);
                                //else if (globalUserLimit->gLatestLimitType[k] == LOWER) pen = QPen(Qt::cyan);
                                pen = QPen(mEdgeColor[globalUserLimit->gLatestLimitType[k]-1]);
                                pen.setStyle(Qt::DotLine);
                                pen.setWidth(2);
                                painter->setPen(pen);
                                painter->drawLine(StartXAxis,globalUserVariable->gridYPos[10],StopXAxis,globalUserVariable->gridYPos[10]);
                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                            else if(globalUserLimit->gAmplitude[k][i] + dEdge <= globalUserVariable->topLevel&&globalUserLimit->gAmplitude[k][i] + dEdge > globalUserVariable->lowLevel)
                            {
                                qreal tempY = globalUserVariable->gridYPos[10];
                                qreal tempX = (tempY-constC)/dSlope;
                                painter->drawLine(tempX, tempY, StopXAxis,  StopYAxis);

                                QPen pen;
                                //if (globalUserLimit->gLatestLimitType[k] == UPPER) pen = QPen(Qt::darkRed);
                                //else if (globalUserLimit->gLatestLimitType[k] == LOWER) pen = QPen(Qt::cyan);
                                pen = QPen(mEdgeColor[globalUserLimit->gLatestLimitType[k]-1]);
                                pen.setStyle(Qt::DotLine);
                                pen.setWidth(2);
                                painter->setPen(pen);
                                painter->drawLine(StartXAxis,tempY,tempX,tempY);
                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                            else if(globalUserLimit->gAmplitude[k][i] + dEdge > globalUserVariable->topLevel)
                            {
                                qreal tempY1 = globalUserVariable->gridYPos[10];
                                qreal tempX1 = (tempY1-constC)/dSlope;
                                qreal tempY2 = DRAW_GRID_START_Y;
                                qreal tempX2 = (tempY2-constC)/dSlope;

                                painter->drawLine(tempX1, tempY1, tempX2,  tempY2);

                                QPen pen;
                                //if (globalUserLimit->gLatestLimitType[k] == UPPER) pen = QPen(Qt::darkRed);
                                //else if (globalUserLimit->gLatestLimitType[k] == LOWER) pen = QPen(Qt::cyan);
                                pen = QPen(mEdgeColor[globalUserLimit->gLatestLimitType[k]-1]);
                                pen.setStyle(Qt::DotLine);
                                pen.setWidth(2);
                                painter->setPen(pen);

                                painter->drawLine(StartXAxis, tempY1, tempX1,  tempY1);
                                painter->drawLine(tempX2, tempY2, StopXAxis,  tempY2);

                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                        }
                        else if(globalUserLimit->gAmplitude[k][i-1] + dEdge <= globalUserVariable->topLevel&&globalUserLimit->gAmplitude[k][i-1] + dEdge >= globalUserVariable->lowLevel)
                        {
                           if(globalUserLimit->gAmplitude[k][i] + dEdge >= globalUserVariable->topLevel)
                           {
                                qreal tempY = DRAW_GRID_START_Y;
                                qreal tempX = (tempY-constC)/dSlope;

                                painter->drawLine(StartXAxis, StartYAxis, tempX,  tempY);

                                QPen pen;
                                //if (globalUserLimit->gLatestLimitType[k] == UPPER) pen = QPen(Qt::darkRed);
                                //else if (globalUserLimit->gLatestLimitType[k] == LOWER) pen = QPen(Qt::cyan);
                                pen = QPen(mEdgeColor[globalUserLimit->gLatestLimitType[k]-1]);
                                pen.setStyle(Qt::DotLine);
                                pen.setWidth(2);
                                painter->setPen(pen);

                                painter->drawLine(tempX, tempY, StopXAxis,  tempY);

                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                        }
                        else if(globalUserLimit->gAmplitude[k][i] + dEdge > globalUserVariable->topLevel)
                        {
                            QPen pen;
                            //if (globalUserLimit->gLatestLimitType[k] == UPPER) pen = QPen(Qt::darkRed);
                            //else if (globalUserLimit->gLatestLimitType[k] == LOWER) pen = QPen(Qt::cyan);
                            pen = QPen(mEdgeColor[globalUserLimit->gLatestLimitType[k]-1]);
                            pen.setStyle(Qt::DotLine);
                            pen.setWidth(2);
                            painter->setPen(pen);
                            painter->drawLine(StartXAxis,DRAW_GRID_START_Y,StopXAxis,DRAW_GRID_START_Y);
                            pen.setWidth(1);
                            painter->setPen(pen);
                        }
                    }
                }
            }
            else painter->drawLine(StartXAxis, StartYAxis, StopXAxis,  StopYAxis);
        }
        QPen pen;
        if (globalUserLimit->gLatestLimitType[k] == UPPER)
        {
            //pen = QPen(Qt::darkRed);
            pen = QPen(mEdgeColor[globalUserLimit->gLatestLimitType[k]-1]);
            pen.setStyle(Qt::DotLine);
            if(globalUserLimit->gAmplitude[k][0] + dEdge >= globalUserVariable->lowLevel && globalUserLimit->gAmplitude[k][0] + dEdge <= globalUserVariable->topLevel)
            {
                if(globalUserLimit->gAmplitude[k][0] > globalUserVariable->topLevel)
                {
                    StartXAxis = globalUserLimit->gXIndex[k][0]*pixelStep+DRAW_GRID_START_X;
                    StartYAxis = DRAW_GRID_START_Y;
                    StopXAxis  = globalUserLimit->gXIndex[k][0]*pixelStep+DRAW_GRID_START_X;
                    StopYAxis  = globalUserLimit->gEdgeYAxis[k][0];

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
                else if(globalUserLimit->gAmplitude[k][0] + dEdge >= globalUserVariable->lowLevel && globalUserLimit->gAmplitude[k][0] + dEdge <= globalUserVariable->topLevel)
                {
                    StartXAxis = globalUserLimit->gXIndex[k][0]*pixelStep+DRAW_GRID_START_X;
                    StartYAxis = globalUserLimit->gYAxis[k][0];
                    StopXAxis  = globalUserLimit->gXIndex[k][0]*pixelStep+DRAW_GRID_START_X;
                    StopYAxis  = globalUserLimit->gEdgeYAxis[k][0];

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
            }
            else if(globalUserLimit->gAmplitude[k][0] + dEdge < globalUserVariable->lowLevel)
            {
                if(globalUserLimit->gAmplitude[k][0] >= globalUserVariable->topLevel)
                {
                    StartXAxis = globalUserLimit->gXIndex[k][0]*pixelStep+DRAW_GRID_START_X;
                    StartYAxis = DRAW_GRID_START_Y;
                    StopXAxis  = globalUserLimit->gXIndex[k][0]*pixelStep+DRAW_GRID_START_X;
                    StopYAxis  = globalUserVariable->gridYPos[10];

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
                else if(globalUserLimit->gAmplitude[k][0] >= globalUserVariable->lowLevel && globalUserLimit->gAmplitude[k][0] < globalUserVariable->topLevel)
                {
                    StartXAxis = globalUserLimit->gXIndex[k][0]*pixelStep+DRAW_GRID_START_X;
                    StartYAxis = globalUserVariable->gridYPos[10];
                    StopXAxis  = globalUserLimit->gXIndex[k][0]*pixelStep+DRAW_GRID_START_X;
                    StopYAxis  = globalUserLimit->gYAxis[k][0];

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
            }

            int gTotalDot = globalUserLimit->gTotalDot[k];
            if(globalUserLimit->gAmplitude[k][gTotalDot-1] + dEdge >= globalUserVariable->lowLevel && globalUserLimit->gAmplitude[k][gTotalDot-1] + dEdge <= globalUserVariable->topLevel)
            {
                if(globalUserLimit->gAmplitude[k][gTotalDot-1] > globalUserVariable->topLevel)
                {
                    StartXAxis = globalUserLimit->gXIndex[k][gTotalDot-1]*pixelStep+DRAW_GRID_START_X;
                    StartYAxis = DRAW_GRID_START_Y;
                    StopXAxis  = globalUserLimit->gXIndex[k][gTotalDot-1]*pixelStep+DRAW_GRID_START_X;
                    StopYAxis  = globalUserLimit->gEdgeYAxis[k][gTotalDot-1];

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
                else if(globalUserLimit->gAmplitude[k][gTotalDot-1] >= globalUserVariable->lowLevel && globalUserLimit->gAmplitude[k][gTotalDot-1] <= globalUserVariable->topLevel)
                {
                    StartXAxis = globalUserLimit->gXIndex[k][gTotalDot-1]*pixelStep+DRAW_GRID_START_X;
                    StartYAxis = globalUserLimit->gYAxis[k][gTotalDot-1];
                    StopXAxis  = globalUserLimit->gXIndex[k][gTotalDot-1]*pixelStep+DRAW_GRID_START_X;
                    StopYAxis  = globalUserLimit->gEdgeYAxis[k][gTotalDot-1];

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
            }
            else if(globalUserLimit->gAmplitude[k][gTotalDot-1] + dEdge < globalUserVariable->lowLevel)
            {
                if(globalUserLimit->gAmplitude[k][gTotalDot-1] >= globalUserVariable->topLevel)
                {
                    StartXAxis = globalUserLimit->gXIndex[k][gTotalDot-1]*pixelStep+DRAW_GRID_START_X;
                    StartYAxis = DRAW_GRID_START_Y;
                    StopXAxis  = globalUserLimit->gXIndex[k][gTotalDot-1]*pixelStep+DRAW_GRID_START_X;
                    StopYAxis  = globalUserVariable->gridYPos[10];

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
                else if(globalUserLimit->gAmplitude[k][gTotalDot-1] >= globalUserVariable->lowLevel && globalUserLimit->gAmplitude[k][gTotalDot-1] < globalUserVariable->topLevel)
                {
                    StartXAxis = globalUserLimit->gXIndex[k][gTotalDot-1]*pixelStep+DRAW_GRID_START_X;
                    StartYAxis = globalUserVariable->gridYPos[10];
                    StopXAxis  = globalUserLimit->gXIndex[k][gTotalDot-1]*pixelStep+DRAW_GRID_START_X;
                    StopYAxis  = globalUserLimit->gYAxis[k][gTotalDot-1];

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
            }
        }
        else if (globalUserLimit->gLatestLimitType[k] == LOWER)
        {
            //pen = QPen(Qt::cyan);
            pen = QPen(mEdgeColor[globalUserLimit->gLatestLimitType[k]-1]);
            pen.setStyle(Qt::DotLine);
            if(globalUserLimit->gAmplitude[k][0] + dEdge >= globalUserVariable->lowLevel && globalUserLimit->gAmplitude[k][0] + dEdge <= globalUserVariable->topLevel)
            {
                if(globalUserLimit->gAmplitude[k][0] < globalUserVariable->lowLevel)
                {
                    StartXAxis = globalUserLimit->gXIndex[k][0]*pixelStep+DRAW_GRID_START_X;
                    StartYAxis = globalUserVariable->gridYPos[10];
                    StopXAxis  = globalUserLimit->gXIndex[k][0]*pixelStep+DRAW_GRID_START_X;
                    StopYAxis  = globalUserLimit->gEdgeYAxis[k][0];

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
                else if(globalUserLimit->gAmplitude[k][0] >= globalUserVariable->lowLevel && globalUserLimit->gAmplitude[k][0] <= globalUserVariable->topLevel)
                {
                    StartXAxis = globalUserLimit->gXIndex[k][0]*pixelStep+DRAW_GRID_START_X;
                    StartYAxis = globalUserLimit->gYAxis[k][0];
                    StopXAxis  = globalUserLimit->gXIndex[k][0]*pixelStep+DRAW_GRID_START_X;
                    StopYAxis  = globalUserLimit->gEdgeYAxis[k][0];

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
            }
            else if(globalUserLimit->gAmplitude[k][0] + dEdge > globalUserVariable->topLevel)
            {
                if(globalUserLimit->gAmplitude[k][0] <= globalUserVariable->lowLevel)
                {
                    StartXAxis = globalUserLimit->gXIndex[k][0]*pixelStep+DRAW_GRID_START_X;
                    StartYAxis = globalUserVariable->gridYPos[10];
                    StopXAxis  = globalUserLimit->gXIndex[k][0]*pixelStep+DRAW_GRID_START_X;
                    StopYAxis  = DRAW_GRID_START_Y;

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
                else if(globalUserLimit->gAmplitude[k][0] > globalUserVariable->lowLevel && globalUserLimit->gAmplitude[k][0] <= globalUserVariable->topLevel)
                {
                    StartXAxis = globalUserLimit->gXIndex[k][0]*pixelStep+DRAW_GRID_START_X;
                    StartYAxis = globalUserLimit->gYAxis[k][0];
                    StopXAxis  = globalUserLimit->gXIndex[k][0]*pixelStep+DRAW_GRID_START_X;
                    StopYAxis  = DRAW_GRID_START_Y;

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
            }

            int gTotalDot = globalUserLimit->gTotalDot[k];
            if(globalUserLimit->gAmplitude[k][gTotalDot-1] + dEdge >= globalUserVariable->lowLevel && globalUserLimit->gAmplitude[k][gTotalDot-1] + dEdge <= globalUserVariable->topLevel)
            {
                if(globalUserLimit->gAmplitude[k][gTotalDot-1] <= globalUserVariable->lowLevel)
                {
                    StartXAxis = globalUserLimit->gXIndex[k][gTotalDot-1]*pixelStep+DRAW_GRID_START_X;
                    StartYAxis = globalUserVariable->gridYPos[10];
                    StopXAxis  = globalUserLimit->gXIndex[k][gTotalDot-1]*pixelStep+DRAW_GRID_START_X;
                    StopYAxis  = globalUserLimit->gEdgeYAxis[k][0];

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
                else if(globalUserLimit->gAmplitude[k][gTotalDot-1] > globalUserVariable->lowLevel && globalUserLimit->gAmplitude[k][gTotalDot-1] <= globalUserVariable->topLevel)
                {
                    StartXAxis = globalUserLimit->gXIndex[k][gTotalDot-1]*pixelStep+DRAW_GRID_START_X;
                    StartYAxis = globalUserLimit->gYAxis[k][gTotalDot-1];
                    StopXAxis  = globalUserLimit->gXIndex[k][gTotalDot-1]*pixelStep+DRAW_GRID_START_X;
                    StopYAxis  = globalUserLimit->gEdgeYAxis[k][gTotalDot-1];

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
            }
            else if(globalUserLimit->gAmplitude[k][gTotalDot-1] + dEdge > globalUserVariable->topLevel)
            {
                if(globalUserLimit->gAmplitude[k][gTotalDot-1] < globalUserVariable->lowLevel)
                {
                    StartXAxis = globalUserLimit->gXIndex[k][gTotalDot-1]*pixelStep+DRAW_GRID_START_X;
                    StartYAxis = globalUserVariable->gridYPos[10];
                    StopXAxis  = globalUserLimit->gXIndex[k][gTotalDot-1]*pixelStep+DRAW_GRID_START_X;
                    StopYAxis  = DRAW_GRID_START_Y;

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
                else if(globalUserLimit->gAmplitude[k][gTotalDot-1] >= globalUserVariable->lowLevel && globalUserLimit->gAmplitude[k][gTotalDot-1] <= globalUserVariable->topLevel)
                {
                    StartXAxis = globalUserLimit->gXIndex[k][gTotalDot-1]*pixelStep+DRAW_GRID_START_X;
                    StartYAxis = globalUserLimit->gYAxis[k][gTotalDot-1];
                    StopXAxis  = globalUserLimit->gXIndex[k][gTotalDot-1]*pixelStep+DRAW_GRID_START_X;
                    StopYAxis  = DRAW_GRID_START_Y;

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
            }
        }
    }
}

/**
 * @brief sa_UIRefresh_Control::drawLatestLimitLine
 * @param painter
 * @note  draw limit line
 * @author Johnson
 */
void sa_UIRefresh_Control::drawLatestLimitLine(QPainter *painter)
{
    qint32 i = 0;
    qint32 k = 0;
    qint32 StartXPos = 0;
    qint32 StopXPos = 0;

    //Johnson 0829 Add
    qreal StartXAxis = 0.;
    qreal StartYAxis = 0.;
    qreal StopXAxis  = 0.;
    qreal StopYAxis  = 0.;
    qreal dSlope     = 0.;//xielv

    qreal pixelStep = 0.;
//    if(globalUserVariable->bSmallCanvas) pixelStep = smallPixmapPixelStep;
//    else pixelStep = largePixmapPixelStep;
    //Tony 190614
    qint32 colorMode = globalUserVariable->gDisplayMode;
    QColor mLimitColor[2] = LimitColor[colorMode];
    pixelStep = mPixmapPixelStep;
    //Drawing  Upper Sengment Limit Line
    for (k = 0; k < LIMIT_SELECTSUM; k++)
    {
        if(globalUserLimit->gLimitLine[k] == SA_OFF) continue;
        if(globalUserLimit->gTotalDot[k] == 0) continue;

        //if (globalUserLimit->gLatestLimitType[k] == UPPER) painter->setPen(Qt::green);
        //else if (globalUserLimit->gLatestLimitType[k] == LOWER) painter->setPen(Qt::blue);
        painter->setPen(mLimitColor[globalUserLimit->gLatestLimitType[k]-1]);
        for(i = 1;i<globalUserLimit->gTotalDot[k];i++)
        {
            StartXPos = globalUserLimit->gXIndex[k][i-1];
            StopXPos = globalUserLimit->gXIndex[k][i];

            //Johnson 1107
            //if (StartXPos == 0 && StopXPos == 0) break;

            //Johnson 0910
            StartXAxis = StartXPos * pixelStep+DRAW_GRID_START_X;
            StartYAxis = globalUserLimit->gYAxis[k][i-1];
            StopXAxis  = StopXPos* pixelStep+DRAW_GRID_START_X;
            StopYAxis  = globalUserLimit->gYAxis[k][i];
            globalUserLimit->gXAxis[k][i-1] = StartXAxis;
            globalUserLimit->gXAxis[k][i]   = StopXAxis;

            if(StopXAxis-StartXAxis != 0) dSlope = (StopYAxis-StartYAxis)/(StopXAxis-StartXAxis);

            //Johnson 0910 change
            if(globalUserLimit->gAmplitude[k][i-1]>globalUserVariable->topLevel||globalUserLimit->gAmplitude[k][i-1]<globalUserVariable->lowLevel
               ||globalUserLimit->gAmplitude[k][i]>globalUserVariable->topLevel||globalUserLimit->gAmplitude[k][i]<globalUserVariable->lowLevel)
            {
                if(StartXAxis == StopXAxis)
                {
                    if(StartYAxis<DRAW_GRID_START_Y)                          StartYAxis = DRAW_GRID_START_Y;
                    else if(StartYAxis>globalUserVariable->gridYPos[10])      StartYAxis = globalUserVariable->gridYPos[10];
                    if(StopYAxis<DRAW_GRID_START_Y)                           StopYAxis  = DRAW_GRID_START_Y;
                    else if(StopYAxis>globalUserVariable->gridYPos[10])       StopYAxis  = globalUserVariable->gridYPos[10];
                    painter->drawLine(StartXAxis, StartYAxis, StopXAxis,  StopYAxis);
                }
                else if(dSlope == 0)
                {
                    if(StartYAxis<DRAW_GRID_START_Y)
                    {
                        StartYAxis = DRAW_GRID_START_Y;
                        StopYAxis = DRAW_GRID_START_Y;
                    }
                    else if(StopYAxis>globalUserVariable->gridYPos[10])
                    {
                        StartYAxis = globalUserVariable->gridYPos[10];
                        StopYAxis = globalUserVariable->gridYPos[10];
                    }
                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
                else
                {
                    qreal constC = StartYAxis-dSlope*StartXAxis;

                    if(dSlope>0)
                    {
                        if(globalUserLimit->gAmplitude[k][i-1]>globalUserVariable->topLevel)
                        {
                            if(globalUserLimit->gAmplitude[k][i]>=globalUserVariable->topLevel)
                            {
                                QPen pen(mLimitColor[globalUserLimit->gLatestLimitType[k]-1]);
                                //if (globalUserLimit->gLatestLimitType[k] == UPPER) pen = QPen(Qt::green);
                                //else if (globalUserLimit->gLatestLimitType[k] == LOWER) pen = QPen(Qt::blue);
                                pen.setWidth(2);
                                painter->setPen(pen);
                                painter->drawLine(StartXAxis,DRAW_GRID_START_Y,StopXAxis,DRAW_GRID_START_Y);
                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                            else if(globalUserLimit->gAmplitude[k][i]<globalUserVariable->topLevel&&globalUserLimit->gAmplitude[k][i]>=globalUserVariable->lowLevel)
                            {
                                qreal tempY = DRAW_GRID_START_Y;
                                qreal tempX = (tempY-constC)/dSlope;
                                painter->drawLine(tempX, tempY, StopXAxis,  StopYAxis);

                                QPen pen(mLimitColor[globalUserLimit->gLatestLimitType[k]-1]);
                                //if (globalUserLimit->gLatestLimitType[k] == UPPER) pen = QPen(Qt::green);
                                //else if (globalUserLimit->gLatestLimitType[k] == LOWER) pen = QPen(Qt::blue);

                                pen.setWidth(2);
                                painter->setPen(pen);
                                painter->drawLine(StartXAxis,tempY,tempX,tempY);
                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                            else if(globalUserLimit->gAmplitude[k][i]<globalUserVariable->lowLevel)
                            {
                                qreal tempY1 = DRAW_GRID_START_Y;
                                qreal tempX1 = (tempY1-constC)/dSlope;
                                qreal tempY2 = globalUserVariable->gridYPos[10];
                                qreal tempX2 = (tempY2-constC)/dSlope;

                                painter->drawLine(tempX1, tempY1, tempX2,  tempY2);

                                QPen pen(mLimitColor[globalUserLimit->gLatestLimitType[k]-1]);
                                //if (globalUserLimit->gLatestLimitType[k] == UPPER) pen = QPen(Qt::green);
                                //else if (globalUserLimit->gLatestLimitType[k] == LOWER) pen = QPen(Qt::blue);
                                pen.setWidth(2);
                                painter->setPen(pen);

                                painter->drawLine(StartXAxis, tempY1, tempX1,  tempY1);
                                painter->drawLine(tempX2, tempY2, StopXAxis,  tempY2);

                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                        }
                        else if(globalUserLimit->gAmplitude[k][i-1]<=globalUserVariable->topLevel&&globalUserLimit->gAmplitude[k][i-1]>=globalUserVariable->lowLevel)
                        {
                           if(globalUserLimit->gAmplitude[k][i]<=globalUserVariable->lowLevel)
                           {
                                qreal tempY = globalUserVariable->gridYPos[10];
                                qreal tempX = (tempY-constC)/dSlope;

                                painter->drawLine(StartXAxis, StartYAxis, tempX,  tempY);

                                QPen pen(mLimitColor[globalUserLimit->gLatestLimitType[k]-1]);
                                //if (globalUserLimit->gLatestLimitType[k] == UPPER) pen = QPen(Qt::green);
                                //else if (globalUserLimit->gLatestLimitType[k] == LOWER) pen = QPen(Qt::blue);

                                pen.setWidth(2);
                                painter->setPen(pen);
                                painter->drawLine(tempX, tempY, StopXAxis,  tempY);
                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                        }
                        else if(globalUserLimit->gAmplitude[globalUserLimit->gLimitSelect][i-1]<globalUserVariable->lowLevel)
                        {
                            QPen pen(mLimitColor[globalUserLimit->gLatestLimitType[k]-1]);
                            //if (globalUserLimit->gLatestLimitType[k] == UPPER) pen = QPen(Qt::green);
                            //else if (globalUserLimit->gLatestLimitType[k] == LOWER) pen = QPen(Qt::blue);

                            pen.setWidth(2);
                            painter->setPen(pen);
                            painter->drawLine(StartXAxis,globalUserVariable->gridYPos[10],StopXAxis,globalUserVariable->gridYPos[10]);
                            pen.setWidth(1);
                            painter->setPen(pen);
                        }
                    }
                    else if(dSlope<0)
                    {
                        if(globalUserLimit->gAmplitude[k][i-1]<globalUserVariable->lowLevel)
                        {
                            if(globalUserLimit->gAmplitude[k][i]<=globalUserVariable->lowLevel)
                            {
                                QPen pen(mLimitColor[globalUserLimit->gLatestLimitType[k]-1]);
                                // if (globalUserLimit->gLatestLimitType[k] == UPPER) pen = QPen(Qt::green);
                                // else if (globalUserLimit->gLatestLimitType[k] == LOWER) pen = QPen(Qt::blue);

                                pen.setWidth(2);
                                painter->setPen(pen);
                                painter->drawLine(StartXAxis,globalUserVariable->gridYPos[10],StopXAxis,globalUserVariable->gridYPos[10]);
                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                            else if(globalUserLimit->gAmplitude[k][i]<=globalUserVariable->topLevel&&globalUserLimit->gAmplitude[k][i]>globalUserVariable->lowLevel)
                            {
                                qreal tempY = globalUserVariable->gridYPos[10];
                                qreal tempX = (tempY-constC)/dSlope;
                                painter->drawLine(tempX, tempY, StopXAxis,  StopYAxis);

                                QPen pen(mLimitColor[globalUserLimit->gLatestLimitType[k]-1]);
                                //if (globalUserLimit->gLatestLimitType[k] == UPPER) pen = QPen(Qt::green);
                                //else if (globalUserLimit->gLatestLimitType[k] == LOWER) pen = QPen(Qt::blue);

                                pen.setWidth(2);
                                painter->setPen(pen);
                                painter->drawLine(StartXAxis,tempY,tempX,tempY);
                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                            else if(globalUserLimit->gAmplitude[k][i]>globalUserVariable->topLevel)
                            {
                                qreal tempY1 = globalUserVariable->gridYPos[10];
                                qreal tempX1 = (tempY1-constC)/dSlope;
                                qreal tempY2 = DRAW_GRID_START_Y;
                                qreal tempX2 = (tempY2-constC)/dSlope;

                                painter->drawLine(tempX1, tempY1, tempX2,  tempY2);

                                QPen pen(mLimitColor[globalUserLimit->gLatestLimitType[k]-1]);
                                //if (globalUserLimit->gLatestLimitType[k] == UPPER) pen = QPen(Qt::green);
                                //else if (globalUserLimit->gLatestLimitType[k] == LOWER) pen = QPen(Qt::blue);

                                pen.setWidth(2);
                                painter->setPen(pen);

                                painter->drawLine(StartXAxis, tempY1, tempX1,  tempY1);
                                painter->drawLine(tempX2, tempY2, StopXAxis,  tempY2);

                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                        }
                        else if(globalUserLimit->gAmplitude[k][i-1]<=globalUserVariable->topLevel&&globalUserLimit->gAmplitude[k][i-1]>=globalUserVariable->lowLevel)
                        {
                           if(globalUserLimit->gAmplitude[k][i]>=globalUserVariable->topLevel)
                           {
                                qreal tempY = DRAW_GRID_START_Y;
                                qreal tempX = (tempY-constC)/dSlope;

                                painter->drawLine(StartXAxis, StartYAxis, tempX,  tempY);

                                QPen pen(mLimitColor[globalUserLimit->gLatestLimitType[k]-1]);
                                //if (globalUserLimit->gLatestLimitType[k] == UPPER) pen = QPen(Qt::green);
                                //else if (globalUserLimit->gLatestLimitType[k] == LOWER) pen = QPen(Qt::blue);

                                pen.setWidth(2);
                                painter->setPen(pen);

                                painter->drawLine(tempX, tempY, StopXAxis,  tempY);

                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                        }
                        else if(globalUserLimit->gAmplitude[k][i]>globalUserVariable->topLevel)
                        {
                            QPen pen(mLimitColor[globalUserLimit->gLatestLimitType[k]-1]);
                            //if (globalUserLimit->gLatestLimitType[k] == UPPER) pen = QPen(Qt::green);
                            //else if (globalUserLimit->gLatestLimitType[k] == LOWER) pen = QPen(Qt::blue);

                            pen.setWidth(2);
                            painter->setPen(pen);
                            painter->drawLine(StartXAxis,DRAW_GRID_START_Y,StopXAxis,DRAW_GRID_START_Y);
                            pen.setWidth(1);
                            painter->setPen(pen);
                        }
                    }
                }
            }
            else painter->drawLine(StartXAxis, StartYAxis, StopXAxis,  StopYAxis);
        }
        QPen pen;
        if (globalUserLimit->gLatestLimitType[k] == UPPER)
        {
            pen = QPen((mLimitColor[globalUserLimit->gLatestLimitType[k]-1]));
            if(globalUserLimit->gAmplitude[k][0] >= globalUserVariable->lowLevel && globalUserLimit->gAmplitude[k][0] <= globalUserVariable->topLevel)
            {
                StartXAxis = globalUserLimit->gXIndex[k][0]*pixelStep+DRAW_GRID_START_X;
                StartYAxis = DRAW_GRID_START_Y;
                StopXAxis  = globalUserLimit->gXIndex[k][0]*pixelStep+DRAW_GRID_START_X;
                StopYAxis  = globalUserLimit->gYAxis[k][0];

                painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
            }
            else if(globalUserLimit->gAmplitude[k][0] < globalUserVariable->lowLevel)
            {
                StartXAxis = globalUserLimit->gXIndex[k][0]*pixelStep+DRAW_GRID_START_X;
                StartYAxis = globalUserVariable->gridYPos[10];
                StopXAxis  = globalUserLimit->gXIndex[k][0]*pixelStep+DRAW_GRID_START_X;
                StopYAxis  = DRAW_GRID_START_Y;

                painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
            }
            int gTotalDot = globalUserLimit->gTotalDot[k];
            if(globalUserLimit->gAmplitude[k][gTotalDot-1] >= globalUserVariable->lowLevel && globalUserLimit->gAmplitude[k][gTotalDot-1] <= globalUserVariable->topLevel)
            {
                StartXAxis = globalUserLimit->gXIndex[k][gTotalDot-1]*pixelStep+DRAW_GRID_START_X-1;
                StartYAxis = DRAW_GRID_START_Y;
                StopXAxis  = globalUserLimit->gXIndex[k][gTotalDot-1]*pixelStep+DRAW_GRID_START_X-1;
                StopYAxis  = globalUserLimit->gYAxis[k][gTotalDot-1];

                painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
            }
            else if(globalUserLimit->gAmplitude[k][gTotalDot-1] < globalUserVariable->lowLevel)
            {
                StartXAxis = globalUserLimit->gXIndex[k][gTotalDot-1]*pixelStep+DRAW_GRID_START_X-1;
                StartYAxis = globalUserVariable->gridYPos[10];
                StopXAxis  = globalUserLimit->gXIndex[k][gTotalDot-1]*pixelStep+DRAW_GRID_START_X-1;
                StopYAxis  = DRAW_GRID_START_Y;

                painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
            }
        }
        else if (globalUserLimit->gLatestLimitType[k] == LOWER)
        {
            pen = QPen((mLimitColor[globalUserLimit->gLatestLimitType[k]-1]));
            if(globalUserLimit->gAmplitude[k][0] >= globalUserVariable->lowLevel && globalUserLimit->gAmplitude[k][0] <= globalUserVariable->topLevel)
            {
                StartXAxis = globalUserLimit->gXIndex[k][0]*pixelStep+DRAW_GRID_START_X;
                StartYAxis = globalUserVariable->gridYPos[10] - 1;
                StopXAxis  = globalUserLimit->gXIndex[k][0]*pixelStep+DRAW_GRID_START_X;
                StopYAxis  = globalUserLimit->gYAxis[k][0];

                painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
            }
            else if(globalUserLimit->gAmplitude[k][0] > globalUserVariable->topLevel)
            {
                StartXAxis = globalUserLimit->gXIndex[k][0]*pixelStep+DRAW_GRID_START_X;
                StartYAxis = DRAW_GRID_START_Y;
                StopXAxis  = globalUserLimit->gXIndex[k][0]*pixelStep+DRAW_GRID_START_X;
                StopYAxis  = globalUserVariable->gridYPos[10] - 1;

                painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
            }
            int gTotalDot = globalUserLimit->gTotalDot[k];
            if(globalUserLimit->gAmplitude[k][gTotalDot-1] >= globalUserVariable->lowLevel && globalUserLimit->gAmplitude[k][gTotalDot-1] <= globalUserVariable->topLevel)
            {
                StartXAxis = globalUserLimit->gXIndex[k][gTotalDot-1]*pixelStep+DRAW_GRID_START_X-1;
                StartYAxis = globalUserVariable->gridYPos[10] - 1;
                StopXAxis  = globalUserLimit->gXIndex[k][gTotalDot-1]*pixelStep+DRAW_GRID_START_X-1;
                StopYAxis  = globalUserLimit->gYAxis[k][gTotalDot-1];

                painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
            }
            else if(globalUserLimit->gAmplitude[k][gTotalDot-1] > globalUserVariable->topLevel)
            {
                StartXAxis = globalUserLimit->gXIndex[k][gTotalDot-1]*pixelStep+DRAW_GRID_START_X-1;
                StartYAxis = DRAW_GRID_START_Y;
                StopXAxis  = globalUserLimit->gXIndex[k][gTotalDot-1]*pixelStep+DRAW_GRID_START_X-1;
                StopYAxis  = globalUserVariable->gridYPos[10] - 1;

                painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
            }
        }
      }
}

/**
 * @brief sa_UIRefresh_Control::drawApplyLimitSettingSweepGraphDisplay
 * @param painter
 * @note  draw limit's spectrum
 * @author Johnson
 */
void sa_UIRefresh_Control::drawApplyLimitSettingSweepGraphDisplay(QPainter *painter)
{
  qint32 i = 0;
  qreal position_center = 0.;

  qreal total_axis = 0.;
  qreal upper_axis = 0.;
  qreal lower_axis = 0.;
  qreal upper_percent = 0.;
  qreal lower_percent = 0.;
  qreal upper_pos_axis = 0.;
  qreal lower_pos_axis = 0.;

  qreal limitLowerYAxis = 0.;
  qreal limitUpperYAxis = 0.;

  qint32 currentTraceNo = globalUserVariable->gTraceSelect;

  QVector<QPointF> draw_point[NUM_TRACE];
  //Tony 190614
  qint32 colorMode = globalUserVariable->gDisplayMode;
  QColor mTraceColor[TRACE_CNT_TOTAL] = TraceColor[colorMode];
  QColor mTrOutLimitColor = TrOutLimitColor[colorMode];
//  if(globalUserVariable->bSmallCanvas)
//  {
//      draw_point[0] = smallPixmap_draw_point[0];
//      draw_point[1] = smallPixmap_draw_point[1];
//      draw_point[2] = smallPixmap_draw_point[2];
//      draw_point[3] = smallPixmap_draw_point[3];
//      draw_point[4] = smallPixmap_draw_point[4];
//      draw_point[5] = smallPixmap_draw_point[5];
//  }
//  else
//  {
//      draw_point[0] = largePixmap_draw_point[0];
//      draw_point[1] = largePixmap_draw_point[1];
//      draw_point[2] = largePixmap_draw_point[2];
//      draw_point[3] = largePixmap_draw_point[3];
//      draw_point[4] = largePixmap_draw_point[4];
//      draw_point[5] = largePixmap_draw_point[5];
//  }
  /*for (qint32 t = TR1; t < NUM_TRACE; t++)
  {
      for (qint32 i = 0; i < globalUserVariable->gSweepTracePoint; i++)
      {
          smallPixmap_draw_point[t].append(QPointF( DRAW_GRID_START_X + 1 + i * smallPixmapPixelStep , SMALLDRAW_GRID_HEIGHT + DRAW_GRID_START_Y));
          largePixmap_draw_point[t].append(QPointF( DRAW_GRID_START_X + 1 + i * largePixmapPixelStep , LARGEDRAW_GRID_HEIGHT + DRAW_GRID_START_Y));
      }
  }*/
  draw_point[0] = mPixmap_draw_point[0];
  draw_point[1] = mPixmap_draw_point[1];
  draw_point[2] = mPixmap_draw_point[2];
  draw_point[3] = mPixmap_draw_point[3];
  draw_point[4] = mPixmap_draw_point[4];
  draw_point[5] = mPixmap_draw_point[5];
  qreal pixelStep = 0.;

//  if(globalUserVariable->bSmallCanvas) pixelStep = smallPixmapPixelStep;
//  else pixelStep = largePixmapPixelStep;
  pixelStep = mPixmapPixelStep;
  for (i = 0; i < globalUserVariable->gSweepTracePoint; i++)
  {
      if(globalUserLimit->gLimitEdge[0] == SA_ON || globalUserLimit->gLimitEdge[1] == SA_ON || globalUserLimit->gLimitEdge[2] == SA_ON ||
              globalUserLimit->gLimitEdge[3] == SA_ON || globalUserLimit->gLimitEdge[4] == SA_ON || globalUserLimit->gLimitEdge[5] == SA_ON)
      {
          limitLowerYAxis = globalUserLimit->gLatestLimitLowerEdgeDrawPoint[i];
          limitUpperYAxis = globalUserLimit->gLatestLimitUpperEdgeDrawPoint[i];
      }
      else
      {
          limitLowerYAxis = globalUserLimit->gLatestLimitLowerDrawPoint[i];
          limitUpperYAxis = globalUserLimit->gLatestLimitUpperDrawPoint[i];
      }


      // Upper Limit 값이 Lower Limit 보다 더 작으면 바로 Fail로 처리
      if ((limitUpperYAxis > limitLowerYAxis) && (limitUpperYAxis != 0. && limitLowerYAxis != 0. ))
      {
          //painter->setPen(Qt::gray);  // QColor/QPen
          painter->setPen(mTrOutLimitColor);
          if (i == 0)
            painter->drawLine(QPointF(DRAW_GRID_START_X + 1 + (i  * pixelStep), draw_point[currentTraceNo][i].y()), QPointF(DRAW_GRID_START_X + 1 + (i * pixelStep),  draw_point[currentTraceNo][i].y()));
          else if (i == (globalUserVariable->gSweepTracePoint - 1))
            painter->drawLine(QPointF(DRAW_GRID_START_X + 1 + ((i  - 1) * pixelStep), draw_point[currentTraceNo][i-1].y()), QPointF(DRAW_GRID_START_X + 1 + (i* pixelStep),  draw_point[currentTraceNo][i].y()));
          else
            painter->drawLine(QPointF(DRAW_GRID_START_X + 1 + ((i  - 1) * pixelStep), draw_point[currentTraceNo][i-1].y()), QPointF(DRAW_GRID_START_X + 1 + (i * pixelStep),  draw_point[currentTraceNo][i].y()));
      }
      else
      {
          if (i == 0)
          {

              // Upper Compare
              if (( draw_point[currentTraceNo][i].y() < limitUpperYAxis) && (limitUpperYAxis != 0. ))
              {

                  //painter->setPen(Qt::gray);  // QColor/QPen
                  //painter->drawLine(DRAW_GRID_START_X + 1 + (i * pixelStep), draw_point[currentTraceNo][i].y(), DRAW_GRID_START_X + 1 + (i * pixelStep),  draw_point[currentTraceNo][i].y());
                  // lower Compare
              }
              else if ( draw_point[currentTraceNo][i].y() > limitLowerYAxis && limitLowerYAxis != 0.)
              {
                  //painter->setPen(Qt::gray);  // QColor/QPen
                  //painter->drawLine(DRAW_GRID_START_X + 1 + (i * pixelStep), draw_point[currentTraceNo][i].y(), DRAW_GRID_START_X + 1 + (i * pixelStep),  draw_point[currentTraceNo][i].y());
              }
              else
              {
                  painter->setPen(mTraceColor[currentTraceNo]);
                  painter->drawLine(QPointF(DRAW_GRID_START_X + 1 + (i * pixelStep), draw_point[currentTraceNo][i].y()), QPointF(DRAW_GRID_START_X + 1 + (i * pixelStep),  draw_point[currentTraceNo][i].y()));
              }
          }
          else if (i == (globalUserVariable->gSweepTracePoint - 1))
          {

              position_center = (((qreal) i) - 0.5) * pixelStep;
              //Johnson 0903 change
              // Upper Compare
              if ((draw_point[currentTraceNo][i].y()  < limitUpperYAxis)  && (limitUpperYAxis != 0.) )
              {

                  if ((draw_point[currentTraceNo][i - 1].y() > limitUpperYAxis) && (limitUpperYAxis != 0.))
                  {
                      //painter->setPen(Qt::gray);  // QColor/QPen
                      painter->setPen(mTrOutLimitColor);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 + ((i - 1) * pixelStep), limitLowerYAxis), QPointF(DRAW_GRID_START_X + 1 + position_center,  limitLowerYAxis));

                      //painter->setPen(Qt::gray);  // QColor/QPen
                      painter->setPen(mTrOutLimitColor);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 + position_center,  limitUpperYAxis), QPointF(DRAW_GRID_START_X + 1 + (i * pixelStep),  draw_point[currentTraceNo][i].y()));
                  }
                  else
                  {
                      //painter->setPen(Qt::gray);  // QColor/QPen
                      painter->setPen(mTrOutLimitColor);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 + ((i - 1)  * pixelStep),  draw_point[currentTraceNo][i - 1].y()), QPointF(DRAW_GRID_START_X + 1 + (i * pixelStep),  draw_point[currentTraceNo][i].y()));
                  }
                }
              else
              {
                  if (draw_point[currentTraceNo][i - 1].y() < limitUpperYAxis && limitUpperYAxis != 0.)
                  {
                      //painter->setPen(Qt::gray);  // QColor/QPen
                      painter->setPen(mTrOutLimitColor);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 + ((i - 1) * pixelStep),  draw_point[currentTraceNo][i - 1].y()), QPointF(DRAW_GRID_START_X + 1 + position_center,  limitUpperYAxis));
                      painter->setPen(mTraceColor[currentTraceNo]);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 + position_center,  limitUpperYAxis), QPointF(DRAW_GRID_START_X + 1 + (i * pixelStep),  draw_point[currentTraceNo][i].y()));
                  }
                  else
                  {
                      painter->setPen(mTraceColor[currentTraceNo]);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 + ((i - 1) * pixelStep), draw_point[currentTraceNo][i - 1].y()), QPointF(DRAW_GRID_START_X + 1 + (i * pixelStep),  draw_point[currentTraceNo][i].y()));
                  }
               }


              if ( (draw_point[currentTraceNo][i].y()  > limitLowerYAxis) && (limitLowerYAxis != 0.) )
              {

                  if ((draw_point[currentTraceNo][i - 1].y() < limitLowerYAxis) && (limitLowerYAxis != 0.))
                  {
                      painter->setPen(mTraceColor[currentTraceNo]);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 + ((i - 1) * pixelStep), limitUpperYAxis), QPointF(DRAW_GRID_START_X + 1 + position_center,   limitLowerYAxis));

                      globalUserLimit->gLimitTestResult[globalUserLimit->gLimitSelect] = SA_FAIL;
                      //painter->setPen(Qt::gray);  // QColor/QPen
                      painter->setPen(mTrOutLimitColor);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 + position_center, limitLowerYAxis), QPointF(DRAW_GRID_START_X + 1 + (i * pixelStep),  draw_point[currentTraceNo][i].y()));
                  }
                  else
                  {
                      globalUserLimit->gLimitTestResult[globalUserLimit->gLimitSelect] = SA_FAIL;
                      //painter->setPen(Qt::gray);  // QColor/QPen
                      painter->setPen(mTrOutLimitColor);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 +  ((i - 1) * pixelStep), draw_point[currentTraceNo][i - 1].y()), QPointF(DRAW_GRID_START_X + 1 + (i * pixelStep) ,  draw_point[currentTraceNo][i].y()));
                  }
              }
              else
              {
                  if ((draw_point[currentTraceNo][i - 1].y() > limitLowerYAxis) && (limitLowerYAxis != 0.))
                  {
                      globalUserLimit->gLimitTestResult[globalUserLimit->gLimitSelect] = SA_FAIL;
                      //painter->setPen(Qt::gray);  // QColor/QPen
                      painter->setPen(mTrOutLimitColor);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 +  ((i - 1) * pixelStep), draw_point[currentTraceNo][i - 1].y()), QPointF(DRAW_GRID_START_X + 1 + position_center,  limitLowerYAxis));

                      painter->setPen(mTraceColor[currentTraceNo]);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 + position_center, limitLowerYAxis), QPointF(DRAW_GRID_START_X + 1 + (i * pixelStep),  limitUpperYAxis));
                  }
                  else
                  {
                      if(limitUpperYAxis != 0) break;
                      painter->setPen(mTraceColor[currentTraceNo]);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 +  ((i - 1) * pixelStep), draw_point[currentTraceNo][i - 1].y()), QPointF(DRAW_GRID_START_X + 1 + (i * pixelStep),  draw_point[currentTraceNo][i].y()));
                  }
                }
          }
          else
          {
              position_center = (((qreal) i ) - 0.5) * pixelStep;
              // ============    Upper와 Lower Limit together Apply
              if ((limitUpperYAxis != 0.) && (limitLowerYAxis != 0.))
              {
                  // Upper Limit Over, Lower Limit Over (위(upper) 에서 아래 (Lower) 로 조건 Compare)
                  if ((draw_point[currentTraceNo][i - 1].y() < limitUpperYAxis) && (draw_point[currentTraceNo][i].y() > limitLowerYAxis))
                  {
                      total_axis  = draw_point[currentTraceNo][i].y() - draw_point[currentTraceNo][i - 1].y();

                      upper_axis =   limitUpperYAxis - draw_point[currentTraceNo][i - 1].y();
                      lower_axis =   draw_point[currentTraceNo][i].y() - limitLowerYAxis;

                      upper_percent = upper_axis / total_axis;
                      lower_percent = lower_axis / total_axis;


                      upper_pos_axis = (((qreal) i) - upper_percent) * pixelStep;
                      lower_pos_axis = (((qreal) i) - lower_percent) * pixelStep;

                      //painter->setPen(Qt::gray);  // QColor/QPen
                      painter->setPen(mTrOutLimitColor);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 +  ((i - 1) * pixelStep), draw_point[currentTraceNo][i - 1].y()), QPointF(DRAW_GRID_START_X + 1 + (qint32) upper_pos_axis,  limitUpperYAxis));

                      painter->setPen(mTraceColor[currentTraceNo]);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 +   (qint32) upper_pos_axis, limitUpperYAxis), QPointF(DRAW_GRID_START_X + 1 + (qint32) lower_pos_axis,  limitLowerYAxis));

                      //painter->setPen(Qt::gray);  // QColor/QPenglobalUserVariable
                      painter->setPen(mTrOutLimitColor);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 +  (qint32) lower_pos_axis, limitLowerYAxis), QPointF(DRAW_GRID_START_X + 1 + (i  * pixelStep),  draw_point[currentTraceNo][i].y()));
                  }
                  else if ((draw_point[currentTraceNo][i - 1].y() > limitLowerYAxis)  && (draw_point[currentTraceNo][i].y() < limitUpperYAxis ))
                  {
                      // Upper Limit Over, Lower Limit Over  (아래 (lower) 에서 위 (upper) 로 조건 Compare)
                      total_axis  = draw_point[currentTraceNo][i].y() - draw_point[currentTraceNo][i - 1].y();

                      lower_axis =   draw_point[currentTraceNo][i - 1].y() - limitLowerYAxis;
                      upper_axis =   limitUpperYAxis - draw_point[currentTraceNo][i].y();

                      upper_percent = upper_axis / total_axis;
                      lower_percent = lower_axis / total_axis;


                      upper_pos_axis = (((qreal) i) - upper_percent) * pixelStep;
                      lower_pos_axis = (((qreal) i) - lower_percent) * pixelStep;

                      //painter->setPen(Qt::gray);  // QColor/QPen
                      painter->setPen(mTrOutLimitColor);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 +  ((i - 1) * pixelStep), draw_point[currentTraceNo][i - 1].y()), QPointF(DRAW_GRID_START_X + 1 + (qint32) lower_pos_axis,  limitLowerYAxis));

                      painter->setPen(mTraceColor[currentTraceNo]);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 +  (qint32) lower_pos_axis, limitLowerYAxis), QPointF(DRAW_GRID_START_X + 1 +  (qint32) upper_pos_axis,  limitUpperYAxis));

                      //painter->setPen(Qt::gray);  // QColor/QPen
                      painter->setPen(mTrOutLimitColor);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 +  (qint32) upper_pos_axis, limitUpperYAxis), QPointF(DRAW_GRID_START_X + 1 + (i  * pixelStep),  draw_point[currentTraceNo][i].y()));

                  }
                  else if ((draw_point[currentTraceNo][i - 1].y() < limitUpperYAxis) && (draw_point[currentTraceNo][i].y() < limitUpperYAxis ))
                  {  // 둘다 Upper 영역
                      //painter->setPen(Qt::gray);  // QColor/QPen
                      painter->setPen(mTrOutLimitColor);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 +  ((i - 1) * pixelStep), draw_point[currentTraceNo][i - 1].y()), QPointF(DRAW_GRID_START_X + 1 + (i  * pixelStep),  draw_point[currentTraceNo][i].y()));
                  }
                  else if ((draw_point[currentTraceNo][i - 1].y() <= limitLowerYAxis) && (draw_point[currentTraceNo][i].y() < limitUpperYAxis ))
                  {
                      painter->setPen(mTraceColor[currentTraceNo]);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 +   ((i - 1) * pixelStep), draw_point[currentTraceNo][i - 1].y()), QPointF(DRAW_GRID_START_X + 1 +  (qint32) position_center,  limitUpperYAxis));

                      //painter->setPen(Qt::gray);  // QColor/QPen
                      painter->setPen(mTrOutLimitColor);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 + position_center, limitUpperYAxis),  QPointF(DRAW_GRID_START_X + 1 + (i  * pixelStep),draw_point[currentTraceNo][i].y()));

                  }
                  else if ((draw_point[currentTraceNo][i - 1].y() < limitUpperYAxis) && (draw_point[currentTraceNo][i].y() <= limitLowerYAxis ))
                  {
                      //painter->setPen(Qt::gray);  // QColor/QPen
                      painter->setPen(mTrOutLimitColor);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 + ((i - 1) * pixelStep), draw_point[currentTraceNo][i - 1].y()), QPointF(DRAW_GRID_START_X + 1 + position_center,  limitUpperYAxis));

                      painter->setPen(mTraceColor[currentTraceNo]);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 + position_center,  limitUpperYAxis), QPointF(DRAW_GRID_START_X + 1 + (i  * pixelStep),  draw_point[currentTraceNo][i].y()));
                  }
                  else if ((draw_point[currentTraceNo][i - 1].y() > limitLowerYAxis) && (draw_point[currentTraceNo][i].y() > limitLowerYAxis ))
                  {  // 둘다 Lower 영역
                      //painter->setPen(Qt::gray);  // QColor/QPen
                      painter->setPen(mTrOutLimitColor);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 + ((i - 1) * pixelStep), draw_point[currentTraceNo][i - 1].y()), QPointF(DRAW_GRID_START_X + 1 + (i * pixelStep),  draw_point[currentTraceNo][i].y()));
                  }
                  else if ((draw_point[currentTraceNo][i - 1].y() >= limitLowerYAxis) && (draw_point[currentTraceNo][i].y() >= limitUpperYAxis ))
                  {
                      //painter->setPen(Qt::gray);  // QColor/QPen
                      painter->setPen(mTrOutLimitColor);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 + ((i - 1) * pixelStep),  draw_point[currentTraceNo][i - 1].y()), QPointF(DRAW_GRID_START_X + 1 + position_center,  limitLowerYAxis));

                      painter->setPen(mTraceColor[currentTraceNo]);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 + position_center, limitLowerYAxis), QPointF(DRAW_GRID_START_X + 1 + (i  * pixelStep),  draw_point[currentTraceNo][i].y()));
                  }
                  else if ((draw_point[currentTraceNo][i - 1].y() > limitUpperYAxis) && (draw_point[currentTraceNo][i].y() >= limitLowerYAxis ))
                  {
                      painter->setPen(mTraceColor[currentTraceNo]);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 +  ((i - 1) * pixelStep), draw_point[currentTraceNo][i - 1].y()), QPointF(DRAW_GRID_START_X + 1 + position_center,  limitLowerYAxis));

                      //painter->setPen(Qt::gray);  // QColor/QPen
                      painter->setPen(mTrOutLimitColor);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + position_center, limitLowerYAxis), QPointF(DRAW_GRID_START_X + (i  * pixelStep),   draw_point[currentTraceNo][i].y()));
                  }
                  else
                  {
                      painter->setPen(mTraceColor[currentTraceNo]);
                      painter->drawLine(QPointF(DRAW_GRID_START_X + 1 +  ((i - 1) * pixelStep), draw_point[currentTraceNo][i - 1].y()), QPointF(DRAW_GRID_START_X + 1 + (i * pixelStep),  draw_point[currentTraceNo][i].y()));
                  }
              }
              else if (limitUpperYAxis != 0.)
              {
                  // *******    Upper Limit only Apply
                  position_center = (((qreal) i) - 0.5) * pixelStep;

                  if ( draw_point[currentTraceNo][i].y() < limitUpperYAxis)
                  {
                      if (draw_point[currentTraceNo][i - 1].y() > limitUpperYAxis)
                      {
                          painter->setPen(mTraceColor[currentTraceNo]);
//                          painter->drawLine(DRAW_GRID_START_X + 1 +  ((i - 1) * pixelStep), draw_point[currentTraceNo][i - 1].y(), DRAW_GRID_START_X + 1 + position_center,   limitUpperYAxis);
                          painter->drawLine(QPointF(DRAW_GRID_START_X + 1 +  ((i - 1) * pixelStep), draw_point[currentTraceNo][i - 1].y()),QPointF(DRAW_GRID_START_X + 1 + position_center,   limitUpperYAxis));

                          //painter->setPen(Qt::gray);  // QColor/QPen
                          painter->setPen(mTrOutLimitColor);
//                          painter->drawLine(DRAW_GRID_START_X + 1 +  position_center, limitUpperYAxis, DRAW_GRID_START_X + 1 + (i * pixelStep),   draw_point[currentTraceNo][i].y());
                          painter->drawLine(QPointF(DRAW_GRID_START_X + 1 +  position_center, limitUpperYAxis),QPointF(DRAW_GRID_START_X + 1 + (i * pixelStep),   draw_point[currentTraceNo][i].y()));

                      }
                      else
                      {
                          //painter->setPen(Qt::gray);  // QColor/QPen
                          painter->setPen(mTrOutLimitColor);
                          painter->drawLine(QPointF(DRAW_GRID_START_X + 1 + ((i - 1)  * pixelStep),draw_point[currentTraceNo][i - 1].y()),QPointF(DRAW_GRID_START_X + 1 + (i * pixelStep),  draw_point[currentTraceNo][i].y()));

//                          painter->drawLine(DRAW_GRID_START_X + 1 +  ((i - 1) * pixelStep), draw_point[currentTraceNo][i - 1].y(), DRAW_GRID_START_X + 1 + (i * pixelStep),   draw_point[currentTraceNo][i].y());
                      }

                  }
                  else
                  {

                      if (draw_point[currentTraceNo][i - 1].y() < limitUpperYAxis)
                      {
                          //painter->setPen(Qt::gray);  // QColor/QPen
                          painter->setPen(mTrOutLimitColor);
//                          painter->drawLine(DRAW_GRID_START_X + 1 +  ((i - 1) * pixelStep), draw_point[currentTraceNo][i - 1].y(), DRAW_GRID_START_X + 1 + position_center,  limitUpperYAxis);
                          painter->drawLine(QPointF(DRAW_GRID_START_X + 1 +  ((i - 1) * pixelStep), draw_point[currentTraceNo][i - 1].y()),QPointF(DRAW_GRID_START_X + 1 + position_center,  limitUpperYAxis));

                          painter->setPen(mTraceColor[currentTraceNo]);
//                          painter->drawLine(DRAW_GRID_START_X + 1 +  position_center, limitUpperYAxis, DRAW_GRID_START_X + 1 +  (i  * pixelStep),  draw_point[currentTraceNo][i].y());
                          painter->drawLine(QPointF(DRAW_GRID_START_X + 1 +  position_center, limitUpperYAxis),QPointF(DRAW_GRID_START_X + 1 +  (i  * pixelStep),  draw_point[currentTraceNo][i].y()));

                      }
                      else
                      {
                          painter->setPen(mTraceColor[currentTraceNo]);
                          painter->drawLine(QPointF(DRAW_GRID_START_X + 1 + ((i - 1)  * pixelStep),draw_point[currentTraceNo][i - 1].y()),QPointF(DRAW_GRID_START_X + 1 + (i * pixelStep),  draw_point[currentTraceNo][i].y()));

//                          painter->drawLine(DRAW_GRID_START_X + 1 +  ((i - 1) * pixelStep), draw_point[currentTraceNo][i - 1].y(), DRAW_GRID_START_X + 1 +  (i  * pixelStep),   draw_point[currentTraceNo][i].y());
                      }
                  }

              }
              else if (limitLowerYAxis != 0.)
              {
                  // **************  Lower Limit only Apply

                  if ( draw_point[currentTraceNo][i].y() > limitLowerYAxis)
                  {

                      if (draw_point[currentTraceNo][i - 1].y() < limitLowerYAxis)
                      {
                          position_center = (((qreal) i) - 0.5) * pixelStep;
                          painter->setPen(mTraceColor[currentTraceNo]);
                          painter->drawLine(QPointF(DRAW_GRID_START_X + 1 +  ((i - 1) * pixelStep), draw_point[currentTraceNo][i - 1].y()), QPointF(DRAW_GRID_START_X + 1 + position_center,  limitLowerYAxis));

                          //painter->setPen(Qt::gray);  // QColor/QPen
                          painter->setPen(mTrOutLimitColor);
                          painter->drawLine(QPointF(DRAW_GRID_START_X + 1 +  position_center, limitLowerYAxis), QPointF(DRAW_GRID_START_X + 1 +  (i  * pixelStep),   draw_point[currentTraceNo][i].y()));

                      }
                      else
                      {
                          //painter->setPen(Qt::gray);  // QColor/QPen
                          painter->setPen(mTrOutLimitColor);
                          painter->drawLine(QPointF(DRAW_GRID_START_X + 1 +  ((i - 1) * pixelStep), draw_point[currentTraceNo][i - 1].y()), QPointF(DRAW_GRID_START_X + 1 +  (i  * pixelStep),  draw_point[currentTraceNo][i].y()));
                      }
                  }
                  else
                  {
                      if (draw_point[currentTraceNo][i - 1].y() > limitLowerYAxis)
                      {
                          position_center = (((qreal) i) -0.5) * pixelStep;
                          //painter->setPen(Qt::gray);  // QColor/QPen
                          painter->setPen(mTrOutLimitColor);
                          painter->drawLine(QPointF(DRAW_GRID_START_X + 1 +  ((i - 1) * pixelStep), draw_point[currentTraceNo][i - 1].y()), QPointF(DRAW_GRID_START_X + 1 +  position_center,  limitLowerYAxis));

                          painter->setPen(mTraceColor[currentTraceNo]);
                          painter->drawLine(QPointF(DRAW_GRID_START_X + 1 +  position_center,  limitLowerYAxis), QPointF(DRAW_GRID_START_X + 1 +  (i  * pixelStep),  draw_point[currentTraceNo][i].y()));
                      }
                      else
                      {
                          painter->setPen(mTraceColor[currentTraceNo]);
                          painter->drawLine(QPointF(DRAW_GRID_START_X + 1 +   ((i - 1) * pixelStep), draw_point[currentTraceNo][i - 1].y()), QPointF(DRAW_GRID_START_X + 1 +  (i  * pixelStep),  draw_point[currentTraceNo][i].y()));
                      }
                  }
              }
              else
              {
                  //=== Not Limit Line
                  painter->setPen(mTraceColor[currentTraceNo]);
                  painter->drawLine(QPointF(DRAW_GRID_START_X + 1 + ((i - 1) * pixelStep), draw_point[currentTraceNo][i - 1].y()), QPointF(DRAW_GRID_START_X + 1 +  (i  * pixelStep),   draw_point[currentTraceNo][i].y()));
              }
          }
      }
  }
}

#if DPX_DEFINE
/**
 * @brief sa_UIRefresh_Control::drawColorBar
 * @param dcurveValue
 * @param uRGBValue
 * @param xPos
 * @param yPos
 * @param width
 * @param height
 * @param paintDevice
 * @param painter
 * @param uColorLevel
 * @note  draw color bar at the left pos of the UI
 * @author Johnson
 */
void sa_UIRefresh_Control::drawColorBar(qreal dcurveValue,qint64 *uRGBValue,qint32 xPos,qint32 yPos,qint32 width,qint32 height,QPaintDevice *paintDevice,QPainter *painter,quint32 uColorLevel)
{
    if(painter == 0){
        painter = new QPainter(paintDevice);
        //painter->initFrom(this);
    }

    quint32 uColorValue = 0xff000000;
    qint32 uRValue     = 0;
    qint32 uGValue     = 0;
    qint32 uBValue     = 0xff;

    painter->fillRect(xPos,yPos+height,width,1,QColor(QRgb(0xff000000)));

    if(uColorLevel>COLORLEVEL) uColorLevel = COLORLEVEL;
    else if(uColorLevel<COLORLEVEL_MIN) uColorLevel = COLORLEVEL_MIN;

    if(dcurveValue<CURVE_MIN) dcurveValue = CURVE_MIN;
    else if(dcurveValue>CURVE_MAX) dcurveValue = CURVE_MAX;

    qreal mcolordiv = (qreal) height/uColorLevel;

    qint32 value_Average = qRound((qreal)255*4/uColorLevel);
    qint32 value_NotAverage = qRound(255*4/uColorLevel*dcurveValue);
    qint32 value_NotAverage1 =qRound((qreal)255*3/(uColorLevel-qRound((qreal)255/value_NotAverage)));

    for(qint32 i = 0;i < uColorLevel;i++){
        if(0xff == uBValue && 0xff>uGValue && 0 == uRValue){
            if(1.0 == dcurveValue) uGValue += value_Average;
            else if(1.0>dcurveValue) uGValue += value_NotAverage;
            else if(1.0<dcurveValue) uGValue += value_NotAverage;
            if(uGValue > 0xff) uGValue = 0xff;
        }
        else if(0<uBValue && 0xff == uGValue && 0 == uRValue){
            if(1.0 == dcurveValue) uBValue -= value_Average;
            else if(1.0>dcurveValue) uBValue -= value_NotAverage1;
            else if(1.0<dcurveValue) uBValue -= value_NotAverage1;
            if(uBValue<0) uBValue = 0;
        }
        else if(0 == uBValue && 0xff == uGValue && 0xff>uRValue){
            if(1.0 == dcurveValue) uRValue += value_Average;
            else if(1.0>dcurveValue) uRValue += value_NotAverage1;
            else if(1.0<dcurveValue) uRValue += value_NotAverage1;
            if(uRValue>0xff) uRValue = 0xff;

            if(uRValue == 0xff&&dcurveValue != 1.0){
                if((uColorLevel-i)*value_NotAverage1<0xff){
                    value_NotAverage1 = qRound((qreal)0xff/(uColorLevel-i))+1;
                }
            }
        }
        else if(0 == uBValue && 0<uGValue && 0xff == uRValue){
            if(1.0 == dcurveValue) uGValue -= value_Average;
            else if(1.0>dcurveValue) uGValue -= value_NotAverage1;
            else if(1.0<dcurveValue) uGValue -= value_NotAverage1;
            if(uGValue<0) uGValue = 0;
        }

        uColorValue = (uColorValue&0xff000000)+(uRValue<<16)+(uGValue<<8)+uBValue;
        uRGBValue[i] = uColorValue;

        const QColor color = QColor(QRgb(uColorValue));
        QRectF rctF(xPos,yPos+height-i*mcolordiv,width,mcolordiv);
        QBrush brush(color);

        painter->fillRect(rctF,brush);
    }
    QThread::usleep(100);
}
/**
 * @brief sa_UIRefresh_Control::drawDensitymap
 * @param pixelStep
 * @param uRGBValue
 * @param paintDevice
 * @param painter
 * @param uColorLevel
 * @param dmaxDensityValue
 * @note  draw DPX
 * @author Johnson
 */
void sa_UIRefresh_Control::drawDensitymap(qreal pixelStep,qint64 *uRGBValue,QPaintDevice *paintDevice,QPainter *painter,quint32 uColorLevel,qreal dmaxDensityValue)
{
    if(painter == 0){
        painter = new QPainter(paintDevice);
        //painter->initFrom(this);
    }

    quint32 uGridHeight = 0;
    quint32 uGridWidth  = 0;
    /*
    if(globalUserVariable->bSmallCanvas)
    {
        uGridHeight = SMALLDRAW_GRID_HEIGHT;
        uGridWidth  = SMALLDRAW_GRID_WIDTH;
    }
    else
    {
        uGridHeight = LARGEDRAW_GRID_HEIGHT;
        uGridWidth  = LARGEDRAW_GRID_WIDTH;
    }
*/


    uGridHeight = mPixmap.height()-SA_TOPDIS-SA_BOTTOMDIS;
    uGridWidth  = mPixmap.width()-SA_LEFTDIS-SA_RIGHTDIS;
    if(globalUserVariable->gTraceSelect == TR1&&lastTraceType[TR1] != globalUserVariable->gTraceType[TR1]){
        for(qint32 i = 0;i<NUM_SWEEP_POINT;i++){
            for(qint32 j = 0;j<uGridHeight;j++){
                globalUserVariable->hitCount_Trace1[i][j] = 0.;
                globalUserVariable->density_Trace1[i][j] = 0;
            }
        }
        globalUserVariable->totalCount1 = 0;
        lastTraceType[TR1] = globalUserVariable->gTraceType[TR1];

        for(qint32 i = DRAW_GRID_START_X;i<DRAW_GRID_START_X+uGridWidth;i++){
            for(qint32 j = DRAW_GRID_START_Y;j<DRAW_GRID_START_Y+uGridHeight;j++){
                painter->fillRect(QRect(i,j,1,1),QBrush(Qt::black));
            }
        }
    }
    else if(globalUserVariable->gTraceSelect == TR2&&lastTraceType[TR2] != globalUserVariable->gTraceType[TR2]){
        for(qint32 i = 0;i<NUM_SWEEP_POINT;i++){
            for(qint32 j = 0;j<uGridHeight;j++){
                globalUserVariable->hitCount_Trace2[i][j] = 0.;
                globalUserVariable->density_Trace2[i][j] = 0;
            }
        }
        globalUserVariable->totalCount2 = 0;
        lastTraceType[TR2] = globalUserVariable->gTraceType[TR2];
        for(qint32 i = DRAW_GRID_START_X;i<DRAW_GRID_START_X+uGridWidth;i++){
            for(qint32 j = DRAW_GRID_START_Y;j<DRAW_GRID_START_Y+uGridHeight;j++){
                painter->fillRect(QRect(i,j,1,1),QBrush(Qt::black));
            }
        }
    }
    else if(globalUserVariable->gTraceSelect == TR3&&lastTraceType[TR3] != globalUserVariable->gTraceType[TR2]){
        for(qint32 i = 0;i<NUM_SWEEP_POINT;i++){
            for(qint32 j = 0;j<uGridHeight;j++){
                globalUserVariable->hitCount_Trace3[i][j] = 0.;
                globalUserVariable->density_Trace3[i][j] = 0;
            }
        }
        globalUserVariable->totalCount3 = 0;
        lastTraceType[TR3] = globalUserVariable->gTraceType[TR3];

        for(qint32 i = DRAW_GRID_START_X;i<DRAW_GRID_START_X+uGridWidth;i++){
            for(qint32 j = DRAW_GRID_START_Y;j<DRAW_GRID_START_Y+uGridHeight;j++){
                painter->fillRect(QRect(i,j,1,1),QBrush(Qt::black));
            }
        }
    }
    else if(globalUserVariable->gTraceSelect == TR4&&lastTraceType[TR4] != globalUserVariable->gTraceType[TR4]){
        for(qint32 i = 0;i<NUM_SWEEP_POINT;i++){
            for(qint32 j = 0;j<uGridHeight;j++){
                globalUserVariable->hitCount_Trace4[i][j] = 0.;
                globalUserVariable->density_Trace4[i][j] = 0;
            }
        }
        globalUserVariable->totalCount4 = 0;
        lastTraceType[TR4] = globalUserVariable->gTraceType[TR4];
        for(qint32 i = DRAW_GRID_START_X;i<DRAW_GRID_START_X+uGridWidth;i++){
            for(qint32 j = DRAW_GRID_START_Y;j<DRAW_GRID_START_Y+uGridHeight;j++){
                painter->fillRect(QRect(i,j,1,1),QBrush(Qt::black));
            }
        }
    }
    else if(globalUserVariable->gTraceSelect == TR5&&lastTraceType[TR5] != globalUserVariable->gTraceType[TR5]){
        for(qint32 i = 0;i<NUM_SWEEP_POINT;i++){
            for(qint32 j = 0;j<uGridHeight;j++){
                globalUserVariable->hitCount_Trace5[i][j] = 0.;
                globalUserVariable->density_Trace5[i][j] = 0;
            }
        }
        globalUserVariable->totalCount5 = 0;
        lastTraceType[TR5] = globalUserVariable->gTraceType[TR5];

        for(qint32 i = DRAW_GRID_START_X;i<DRAW_GRID_START_X+uGridWidth;i++){
            for(qint32 j = DRAW_GRID_START_Y;j<DRAW_GRID_START_Y+uGridHeight;j++){
                painter->fillRect(QRect(i,j,1,1),QBrush(Qt::black));
            }
        }
    }
    else if(globalUserVariable->gTraceSelect == TR6&&lastTraceType[TR6] != globalUserVariable->gTraceType[TR6]){
        for(qint32 i = 0;i<NUM_SWEEP_POINT;i++){
            for(qint32 j = 0;j<uGridHeight;j++){
                globalUserVariable->hitCount_Trace6[i][j] = 0.;
                globalUserVariable->density_Trace6[i][j] = 0;
            }
        }
        globalUserVariable->totalCount6 = 0;
        lastTraceType[TR6] = globalUserVariable->gTraceType[TR6];

        for(qint32 i = DRAW_GRID_START_X;i<DRAW_GRID_START_X+uGridWidth;i++){
            for(qint32 j = DRAW_GRID_START_Y;j<DRAW_GRID_START_Y+uGridHeight;j++){
                painter->fillRect(QRect(i,j,1,1),QBrush(Qt::black));
            }
        }
    }

    if (globalUserVariable->gTraceView[globalUserVariable->gTraceSelect] == SA_OFF) return;

    //get DPX Value
    //get total repaint time
    if(globalUserVariable->gTraceSelect == TR1) globalUserVariable->totalCount1++;
    else if(globalUserVariable->gTraceSelect == TR2) globalUserVariable->totalCount2++;
    else if(globalUserVariable->gTraceSelect == TR3) globalUserVariable->totalCount3++;
    else if(globalUserVariable->gTraceSelect == TR4) globalUserVariable->totalCount4++;
    else if(globalUserVariable->gTraceSelect == TR5) globalUserVariable->totalCount5++;
    else if(globalUserVariable->gTraceSelect == TR6) globalUserVariable->totalCount6++;


    for(qint32 j = 0;j<NUM_SWEEP_POINT;j++){
        if(globalUserVariable->gTraceSelect == TR1){
            qint32 Y = yaxis_cal(globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][j] + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y;
            globalUserVariable->hitCount_Trace1[j][Y]++;
            for(qint32 k = 0;k<uGridHeight;k++){
                globalUserVariable->density_Trace1[j][k] = (qreal)globalUserVariable->hitCount_Trace1[j][k]/globalUserVariable->totalCount1;
            }
            //globalUserVariable->density_Trace1[j][Y] = (qreal)globalUserVariable->hitCount_Trace1[j][Y]/globalUserVariable->totalCount1;
        }
        else if(globalUserVariable->gTraceSelect == TR2){
            qint32 Y = yaxis_cal(globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][j] + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y;
            globalUserVariable->hitCount_Trace2[j][Y]++;
            for(qint32 k = 0;k<uGridHeight;k++){
                globalUserVariable->density_Trace2[j][k] = (qreal)globalUserVariable->hitCount_Trace2[j][k]/globalUserVariable->totalCount2;
            }
        }
        else if(globalUserVariable->gTraceSelect == TR3){
            qint32 Y = yaxis_cal(globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][j] + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y;
            globalUserVariable->hitCount_Trace3[j][Y]++;
            for(qint32 k = 0;k<uGridHeight;k++){
                globalUserVariable->density_Trace3[j][k] = (qreal)globalUserVariable->hitCount_Trace3[j][k]/globalUserVariable->totalCount3;
            }
        }
        else if(globalUserVariable->gTraceSelect == TR4){
            qint32 Y = yaxis_cal(globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][j] + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y;
            globalUserVariable->hitCount_Trace4[j][Y]++;
            for(qint32 k = 0;k<uGridHeight;k++){
                globalUserVariable->density_Trace4[j][k] = (qreal)globalUserVariable->hitCount_Trace4[j][k]/globalUserVariable->totalCount4;
            }
            //globalUserVariable->density_Trace1[j][Y] = (qreal)globalUserVariable->hitCount_Trace1[j][Y]/globalUserVariable->totalCount1;
        }
        else if(globalUserVariable->gTraceSelect == TR5){
            qint32 Y = yaxis_cal(globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][j] + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y;
            globalUserVariable->hitCount_Trace5[j][Y]++;
            for(qint32 k = 0;k<uGridHeight;k++){
                globalUserVariable->density_Trace5[j][k] = (qreal)globalUserVariable->hitCount_Trace5[j][k]/globalUserVariable->totalCount5;
            }
        }
        else if(globalUserVariable->gTraceSelect == TR6){
            qint32 Y = yaxis_cal(globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][j] + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y;
            globalUserVariable->hitCount_Trace6[j][Y]++;
            for(qint32 k = 0;k<uGridHeight;k++){
                globalUserVariable->density_Trace6[j][k] = (qreal)globalUserVariable->hitCount_Trace6[j][k]/globalUserVariable->totalCount6;
            }
        }
    }
    //if(globalUserVariable->totalCount1 != 1) return;
    //draw DPX map
    QBrush brushBlack(QColor("0xff000000"));
    uint uColorValue = 0xff0000ff;
    qint32 value = 0;
    qreal dDensityStep = (qreal)(dmaxDensityValue/uColorLevel);

    for(qint32 i = 0;i<NUM_SWEEP_POINT;i++){
        for(qint32 j = 0;j<globalUserVariable->gridYPos[10];j++){
            if (globalUserVariable->gTraceView[globalUserVariable->gTraceSelect] != SA_OFF){
                QRectF rcF(DRAW_GRID_START_X+i*pixelStep,j,pixelStep,1);

                if(globalUserVariable->gTraceSelect == TR1){


                    if(globalUserVariable->density_Trace1[i][j] <= dDensityStep) painter->fillRect(rcF,brushBlack);
                    else {
                        if(globalUserVariable->density_Trace1[i][j]>dDensityStep&&globalUserVariable->density_Trace1[i][j]<=dmaxDensityValue){
                            quint32 uRGBIndex = (qint32)(globalUserVariable->density_Trace1[i][j]/dDensityStep);
                            if(uRGBIndex>=uColorLevel) uRGBIndex = uColorLevel-1;
                            uColorValue = uRGBValue[uRGBIndex];
                        }
                        else uColorValue = 0xffff0000;

                        const QColor color = QColor(QRgb(uColorValue));
                        QBrush brushOther(color);
                        painter->fillRect(rcF,brushOther);
                    }
                }
                else if(globalUserVariable->gTraceSelect == TR2){
                    value = (qint32)(globalUserVariable->density_Trace2[i][j]*100*10);

                    if(globalUserVariable->density_Trace2[i][j] == 0) painter->fillRect(rcF,brushBlack);
                    else {
                        if(globalUserVariable->density_Trace2[i][j]>0&&globalUserVariable->density_Trace2[i][j]<0.20){
                            if(globalUserVariable->density_Trace2[i][j]-0.005 <= 0.) uColorValue = 0xff0000ff+(100<<8);
                            else if(globalUserVariable->density_Trace2[i][j]-0.01 <= 0.) uColorValue = 0xff0000ff+(0xff<<8);
                            else if(globalUserVariable->density_Trace2[i][j]-0.015 <= 0.) uColorValue = 0xff00ffff-100;
                            else if(globalUserVariable->density_Trace2[i][j]-0.02 <= 0.) uColorValue = 0xff00ffff-0xff;
                            else if(globalUserVariable->density_Trace2[i][j]-0.03 <= 0.) uColorValue = 0xff00ff00+(100<<16);
                            else if(globalUserVariable->density_Trace2[i][j]-0.04 <= 0.) uColorValue = 0xff00ff00+(0xff<<16);
                            else if(globalUserVariable->density_Trace2[i][j]-0.05 <= 0.) uColorValue = 0xffffff00-(50<<8);
                            else if(globalUserVariable->density_Trace2[i][j]-0.06 <= 0.) uColorValue = 0xffffff00-(100<<8);
                            else if(globalUserVariable->density_Trace2[i][j]-0.07 <= 0.) uColorValue = 0xffffff00-(150<<8);
                            else if(globalUserVariable->density_Trace2[i][j]-0.08 <= 0.) uColorValue = 0xffffff00-(200<<8);
                            else uColorValue = 0xffffff00-(0xff<<8);
                        }
                        else uColorValue = 0xffff0000;

                        const QColor color = QColor(QRgb(uColorValue));
                        QBrush brushOther(color);
                        painter->fillRect(rcF,brushOther);
                    }
                }
                else if(globalUserVariable->gTraceSelect == TR3){
                    value = (qint32)(globalUserVariable->density_Trace3[i][j]*100*10);

                    if(globalUserVariable->density_Trace3[i][j] == 0) painter->fillRect(rcF,brushBlack);
                    else {
                        if(globalUserVariable->density_Trace3[i][j]>0&&globalUserVariable->density_Trace3[i][j]<0.20){
                            if(globalUserVariable->density_Trace3[i][j]-0.005 <= 0.) uColorValue = 0xff0000ff+(100<<8);
                            else if(globalUserVariable->density_Trace3[i][j]-0.01 <= 0.) uColorValue = 0xff0000ff+(0xff<<8);
                            else if(globalUserVariable->density_Trace3[i][j]-0.015 <= 0.) uColorValue = 0xff00ffff-100;
                            else if(globalUserVariable->density_Trace3[i][j]-0.02 <= 0.) uColorValue = 0xff00ffff-0xff;
                            else if(globalUserVariable->density_Trace3[i][j]-0.03 <= 0.) uColorValue = 0xff00ff00+(100<<16);
                            else if(globalUserVariable->density_Trace3[i][j]-0.04 <= 0.) uColorValue = 0xff00ff00+(0xff<<16);
                            else if(globalUserVariable->density_Trace3[i][j]-0.05 <= 0.) uColorValue = 0xffffff00-(50<<8);
                            else if(globalUserVariable->density_Trace3[i][j]-0.06 <= 0.) uColorValue = 0xffffff00-(100<<8);
                            else if(globalUserVariable->density_Trace3[i][j]-0.07 <= 0.) uColorValue = 0xffffff00-(150<<8);
                            else if(globalUserVariable->density_Trace3[i][j]-0.08 <= 0.) uColorValue = 0xffffff00-(200<<8);
                            else uColorValue = 0xffffff00-(0xff<<8);
                        }
                        else uColorValue = 0xffff0000;

                        const QColor color = QColor(QRgb(uColorValue));
                        QBrush brushOther(color);
                        painter->fillRect(rcF,brushOther);
                    }
                }
                else if(globalUserVariable->gTraceSelect == TR4){
                    if(globalUserVariable->density_Trace4[i][j] <= dDensityStep) painter->fillRect(rcF,brushBlack);
                    else {
                        if(globalUserVariable->density_Trace4[i][j]>dDensityStep&&globalUserVariable->density_Trace4[i][j]<=dmaxDensityValue){
                            quint32 uRGBIndex = (qint32)(globalUserVariable->density_Trace4[i][j]/dDensityStep);
                            if(uRGBIndex>=uColorLevel) uRGBIndex = uColorLevel-1;
                            uColorValue = uRGBValue[uRGBIndex];
                        }
                        else uColorValue = 0xffff0000;

                        const QColor color = QColor(QRgb(uColorValue));
                        QBrush brushOther(color);
                        painter->fillRect(rcF,brushOther);
                    }
                }
                else if(globalUserVariable->gTraceSelect == TR5){


                    if(globalUserVariable->density_Trace5[i][j] <= dDensityStep) painter->fillRect(rcF,brushBlack);
                    else {
                        if(globalUserVariable->density_Trace5[i][j]>dDensityStep&&globalUserVariable->density_Trace5[i][j]<=dmaxDensityValue){
                            quint32 uRGBIndex = (qint32)(globalUserVariable->density_Trace5[i][j]/dDensityStep);
                            if(uRGBIndex>=uColorLevel) uRGBIndex = uColorLevel-1;
                            uColorValue = uRGBValue[uRGBIndex];
                        }
                        else uColorValue = 0xffff0000;

                        const QColor color = QColor(QRgb(uColorValue));
                        QBrush brushOther(color);
                        painter->fillRect(rcF,brushOther);
                    }
                }
                else if(globalUserVariable->gTraceSelect == TR6){


                    if(globalUserVariable->density_Trace6[i][j] <= dDensityStep) painter->fillRect(rcF,brushBlack);
                    else {
                        if(globalUserVariable->density_Trace6[i][j]>dDensityStep&&globalUserVariable->density_Trace6[i][j]<=dmaxDensityValue){
                            quint32 uRGBIndex = (qint32)(globalUserVariable->density_Trace6[i][j]/dDensityStep);
                            if(uRGBIndex>=uColorLevel) uRGBIndex = uColorLevel-1;
                            uColorValue = uRGBValue[uRGBIndex];
                        }
                        else uColorValue = 0xffff0000;

                        const QColor color = QColor(QRgb(uColorValue));
                        QBrush brushOther(color);
                        painter->fillRect(rcF,brushOther);
                    }
                }
            }
        }
    }
}
#endif
/**
 * @brief sa_UIRefresh_Control::drawMarkerCurrentSelectInfo
 * @param painter
 * @note  draw the information of current selected marker
 * @author Johnson
 */
void sa_UIRefresh_Control::drawMarkerCurrentSelectInfo(QPainter *painter)
{
    qint32 colorMode = globalUserVariable->gDisplayMode;
    QColor colorMarker[2] = MarkerColor[colorMode];

    QString strLabel,strAmptd,strAmptdUnit,strUnit,strGab,strValue,strMkrNoise;
    qint32 i = 0,cnt = 0,unitNo = 0,pos = 0,minusFlag = 0;
    //qint64 deltaPos,refPos;
    qreal freqValue = 0,deltaFreq = 0;
    qreal deltaAmptdGab = 0.,refAmptdGab = 0.,subtractGab = 0;//,markerLevel = 0;
    char   label[20];
    const qint32 markerInfoX = globalUserVariable->gridXPos[5]+5;

    painter->setFont(QFont("Arial", 12,QFont::Bold));

    ++cnt;
    i = globalUserVariable->gMarkerSelect;
    //static qint32 tmpMarkerRefPos = globalUserVariable->gMarkerRefPos[i];
    static qreal markerLevel = (qreal)globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][globalUserVariable->gMarkerRefPos[i]] + globalUserVariable->gRefOffset;


    if (globalUserVariable->gMarkerView[i] == SA_ON)
    {
        painter->setPen(colorMarker[0]);
        if (globalUserVariable->gMarkerType[i] == REF)
        {
            minusFlag = 0;
            strLabel = QString("M%1").arg(i + 1);
            if(!globalUserVariable->gMarkerFreqCount) strLabel = QString("M%1").arg(i + 1);
            else strLabel = QString("CNT%1").arg(globalUserVariable->gMarkerSelect + 1);
            painter->drawText(markerInfoX , globalUserVariable->gridYPos[0] +  (MARKER_FONT_HEIGHT * cnt) , 50, 20, Qt::AlignLeft, strLabel);
            //refPos =  globalUserVariable->gMarkerRefPos[i];


            //Johnson 190621
            if(globalUserVariable->gMarkerFreqCount)
            {
                //qreal value = (qreal)globalUserVariable->gFreqCount + (globalUserVariable->gMarkerRefFreq[globalUserVariable->gMarkerSelect] - globalUserVariable->gSignalFreq);
                qreal value = 0.;
                qreal markoffSignl = globalUserVariable->gMarkerRefFreq[globalUserVariable->gMarkerSelect] - globalUserVariable->gSignalFreq;
                qreal MarkoffCenter = globalUserVariable->gMarkerRefFreq[globalUserVariable->gMarkerSelect] - globalUserVariable->gCenterFreq;
                if(fabs(MarkoffCenter) <= globalUserVariable->gRbw/2)
                {
                    //Tony19-12-19 if value = gFreqCount ,then value = 0 when marker on center but isn't 0;
                    value = globalUserVariable->gCenterFreq;
                    //value = (qreal)globalUserVariable->gFreqCount;

                }
                else value = (qreal)globalUserVariable->gFreqCount + markoffSignl;

                if(value < 0)
                {
                    value = -1 * value;
                    minusFlag = 1;
                }

                strValue = QString::number(value,'d',3);
                if(minusFlag) strValue = "-" + strValue + " Hz";
                else strValue = strValue + " Hz";

                painter->drawText(markerInfoX + 80, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 200, 20, Qt::AlignLeft, strValue);
            }
            else
            {
                if(!globalUserVariable->gZeroSpanAction)
                {
                    freqValue = (qreal)globalUserVariable->gMarkerRefFreq[i] + globalUserVariable->gfreqOffset;
                    if(freqValue < 0)
                    {
                        freqValue *= -1;
                        minusFlag = 1;
                    }
                    unitNo = globalUserVariable->freqUnitFindProc(freqValue);
                    strGab = QString::number(freqValue, 'd',0);

                    pos = globalUserVariable->notZeroPositionFindFunc(strGab);

                    strValue = globalUserVariable->freqDotNumberDisplayFormatFixFunc (freqValue, unitNo, pos );
                    if(minusFlag) strValue = "-" + strValue;
                    painter->drawText(markerInfoX + 50, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 170, 20, Qt::AlignLeft, strValue);

                    if ( globalUserVariable->gMarkerRefFreq[i] < globalUserVariable->gStartFreq)
                    {
                        strAmptd = QString("- -");
                        painter->drawText(markerInfoX + 200, globalUserVariable->gridYPos[0] +  (MARKER_FONT_HEIGHT * cnt) , 120, 20, Qt::AlignRight, strAmptd);
                    }
                    else if ( globalUserVariable->gMarkerRefFreq[i] > globalUserVariable->gStopFreq)
                    {
                        strAmptd = QString("- -");
                        painter->drawText(markerInfoX + 200, globalUserVariable->gridYPos[0] +  (MARKER_FONT_HEIGHT * cnt) , 120, 20, Qt::AlignRight, strAmptd);
                    }
                    else
                    {
                        markerLevel = (qreal)globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][globalUserVariable->gMarkerRefPos[i]] + globalUserVariable->gRefOffset;

                        //****************Johnson 0917 Change
                        switch (globalUserVariable->gAmptdUnit)
                        {
                        case SA_WATTS:
                            globalUserVariable->dbmToWattsCalculatorAndDisplayFunc(label, markerLevel);
                            globalUserVariable->charEmptySplitWorkerFunc(label);

                            strAmptd = QString(SA_watts_unit.value);
                            strAmptdUnit = QString(SA_watts_unit.unit);
                            break;
                        case SA_DBM:
                            strAmptd.sprintf("%.2f", markerLevel);
                            strAmptdUnit = QString("dBm");
                            break;
                        case SA_DBV:
                            strAmptd.sprintf("%.2f", markerLevel + dBVFix);
                            strAmptdUnit = QString("dBV");
                            break;
                        case SA_DBMV:
                            strAmptd.sprintf("%.2f", markerLevel+dBmVFix);
                            strAmptdUnit = QString("dBmV");
                            break;
                        case SA_DBUV:
                            strAmptd.sprintf("%.2f", markerLevel+dBuVFix);
                            strAmptdUnit = QString("dBuV");
                            break;
                        case SA_VOLT:
                            globalUserVariable->dbmToVoltCalculatorAndDisplayFunc(label, markerLevel);
                            globalUserVariable->charEmptySplitWorkerFunc(label);

                            strAmptd = QString(SA_watts_unit.value);
                            strAmptdUnit = QString(SA_watts_unit.unit);
                            break;
                        default:
                            strAmptd.sprintf("%.2f", markerLevel);
                            strAmptdUnit = QString("dBm");
                            break;
                        }
                        painter->drawText(markerInfoX + 200, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 120, 20, Qt::AlignRight, strAmptd);
                        painter->drawText(markerInfoX + 340, globalUserVariable->gridYPos[0] +  (MARKER_FONT_HEIGHT * cnt) , 50, 20, Qt::AlignLeft, strAmptdUnit);
                        //********************************
                    }

                }
                else
                {
                    freqValue = globalUserVariable->gMarkerRefTime[i];
                    strValue = globalUserVariable->TimeTransformToQstring(freqValue);
                    painter->drawText(markerInfoX + 50, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 170, 20, Qt::AlignLeft, strValue);

                    if ( globalUserVariable->gMarkerRefTime[i] < 0)
                    {
                        strAmptd = QString("- -");
                        painter->drawText(markerInfoX + 200, globalUserVariable->gridYPos[0] +  (MARKER_FONT_HEIGHT * cnt) , 120, 20, Qt::AlignRight, strAmptd);
                    }
                    else if ( globalUserVariable->gMarkerRefTime[i] > globalUserVariable->gSweepTime)
                    {
                        strAmptd = QString("- -");
                        painter->drawText(markerInfoX + 200, globalUserVariable->gridYPos[0] +  (MARKER_FONT_HEIGHT * cnt) , 120, 20, Qt::AlignRight, strAmptd);
                    }
                    else
                    {
                        markerLevel = (qreal)globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][globalUserVariable->gMarkerRefPos[i]] + globalUserVariable->gRefOffset;

                        //****************Johnson 0917 Change
                        switch (globalUserVariable->gAmptdUnit)
                        {
                        case SA_WATTS:
                            globalUserVariable->dbmToWattsCalculatorAndDisplayFunc(label, markerLevel);
                            globalUserVariable->charEmptySplitWorkerFunc(label);

                            strAmptd = QString(SA_watts_unit.value);
                            strAmptdUnit = QString(SA_watts_unit.unit);
                            break;
                        case SA_DBM:
                            strAmptd.sprintf("%.2f", markerLevel);
                            strAmptdUnit = QString("dBm");
                            break;
                        case SA_DBV:
                            strAmptd.sprintf("%.2f", markerLevel + dBVFix);
                            strAmptdUnit = QString("dBV");
                            break;
                        case SA_DBMV:
                            strAmptd.sprintf("%.2f", markerLevel+dBmVFix);
                            strAmptdUnit = QString("dBmV");
                            break;
                        case SA_DBUV:
                            strAmptd.sprintf("%.2f", markerLevel+dBuVFix);
                            strAmptdUnit = QString("dBuV");
                            break;
                        case SA_VOLT:
                            globalUserVariable->dbmToVoltCalculatorAndDisplayFunc(label, markerLevel);
                            globalUserVariable->charEmptySplitWorkerFunc(label);

                            strAmptd = QString(SA_watts_unit.value);
                            strAmptdUnit = QString(SA_watts_unit.unit);
                            break;
                        default:
                            strAmptd.sprintf("%.2f", markerLevel);
                            strAmptdUnit = QString("dBm");
                            break;
                        }
                        painter->drawText(markerInfoX + 200, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 120, 20, Qt::AlignRight, strAmptd);
                        painter->drawText(markerInfoX + 340, globalUserVariable->gridYPos[0] +  (MARKER_FONT_HEIGHT * cnt) , 50, 20, Qt::AlignLeft, strAmptdUnit);
                        //********************************
                    }
                }
                globalUserVariable->gMarkerRefAmpt[i] = markerLevel;
            }

        }
        else if(globalUserVariable->gMarkerType[i] == DELTA)
        {
            minusFlag = 0;
            // Ref Display
            strLabel = QString("R%1").arg(i + 1);
            painter->drawText(markerInfoX , globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 50, 20, Qt::AlignLeft, strLabel);
            //deltaPos = globalUserVariable->gMarkerRefPos[i];

            if(!globalUserVariable->gSpanMode)
            {
                freqValue =(qreal)globalUserVariable->gMarkerRefFreq[i] + globalUserVariable->gfreqOffset;
                if(freqValue < 0)
                {
                    freqValue *= -1;
                    minusFlag = 1;
                }
                unitNo = globalUserVariable->freqUnitFindProc(freqValue);
                strGab = QString::number(freqValue, 'd',0);

                pos = globalUserVariable->notZeroPositionFindFunc(strGab);
                strValue = globalUserVariable->freqDotNumberDisplayFormatFixFunc (freqValue, unitNo, pos );
                if(minusFlag) strValue = "-" + strValue;
                    painter->drawText(markerInfoX + 50, globalUserVariable->gridYPos[0]  + (MARKER_FONT_HEIGHT * cnt) , 170, 20, Qt::AlignLeft, strValue);


                //tmpMarkerRefPos = globalUserVariable->gMarkerMarkerTmpRefPos[i];
                markerLevel = (qreal)globalUserVariable->gMarkerTmpRefAmpt[i];
                //****************Johnson 0917 Change
                switch (globalUserVariable->gAmptdUnit)
                {
                case SA_WATTS:
                    globalUserVariable->dbmToWattsCalculatorAndDisplayFunc(label, markerLevel);
                    globalUserVariable->charEmptySplitWorkerFunc(label);

                    strAmptd = QString(SA_watts_unit.value);
                    strAmptdUnit = QString(SA_watts_unit.unit);
                    break;
                case SA_DBM:
                    strAmptd.sprintf("%.2f", markerLevel);
                    strAmptdUnit = QString("dBm");
                    break;
                case SA_DBV:
                    strAmptd.sprintf("%.2f", markerLevel + dBVFix);
                    strAmptdUnit = QString("dBV");
                    break;
                case SA_DBMV:
                    strAmptd.sprintf("%.2f", markerLevel+dBmVFix);
                    strAmptdUnit = QString("dBmV");
                    break;
                case SA_DBUV:
                    strAmptd.sprintf("%.2f", markerLevel+dBuVFix);
                    strAmptdUnit = QString("dBuV");
                    break;
                case SA_VOLT:
                    globalUserVariable->dbmToVoltCalculatorAndDisplayFunc(label, markerLevel);
                    globalUserVariable->charEmptySplitWorkerFunc(label);

                    strAmptd = QString(SA_watts_unit.value);
                    strAmptdUnit = QString(SA_watts_unit.unit);
                    break;
                default:
                    strAmptd.sprintf("%.2f", markerLevel);
                    strAmptdUnit = QString("dBm");
                    break;
                }
                painter->drawText(markerInfoX + 200, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 120, 20, Qt::AlignRight, strAmptd);
                painter->drawText(markerInfoX + 340, globalUserVariable->gridYPos[0] +  (MARKER_FONT_HEIGHT * cnt) , 50, 20, Qt::AlignLeft, strAmptdUnit);
            }
            else
            {

                QString strTime = globalUserVariable->TimeTransformToQstring(globalUserVariable->gMarkerRefTime[i]);
                strValue = strTime;
                painter->drawText(markerInfoX + 50, globalUserVariable->gridYPos[0]  + (MARKER_FONT_HEIGHT * cnt) , 170, 20, Qt::AlignLeft, strValue);

                //tmpMarkerRefPos = globalUserVariable->gMarkerMarkerTmpRefPos[i];
                markerLevel = (qreal)globalUserVariable->gMarkerTmpRefAmpt[i];

                switch (globalUserVariable->gAmptdUnit)
                {
                case SA_WATTS:
                    globalUserVariable->dbmToWattsCalculatorAndDisplayFunc(label, markerLevel);
                    globalUserVariable->charEmptySplitWorkerFunc(label);

                    strAmptd = QString(SA_watts_unit.value);
                    strAmptdUnit = QString(SA_watts_unit.unit);
                    break;
                case SA_DBM:
                    strAmptd.sprintf("%.2f", markerLevel);
                    strAmptdUnit = QString("dBm");
                    break;
                case SA_DBV:
                    strAmptd.sprintf("%.2f", markerLevel + dBVFix);
                    strAmptdUnit = QString("dBV");
                    break;
                case SA_DBMV:
                    strAmptd.sprintf("%.2f", markerLevel+dBmVFix);
                    strAmptdUnit = QString("dBmV");
                    break;
                case SA_DBUV:
                    strAmptd.sprintf("%.2f", markerLevel+dBuVFix);
                    strAmptdUnit = QString("dBuV");
                    break;
                case SA_VOLT:
                    globalUserVariable->dbmToVoltCalculatorAndDisplayFunc(label, markerLevel);
                    globalUserVariable->charEmptySplitWorkerFunc(label);

                    strAmptd = QString(SA_watts_unit.value);
                    strAmptdUnit = QString(SA_watts_unit.unit);
                    break;
                default:
                    strAmptd.sprintf("%.2f", markerLevel);
                    strAmptdUnit = QString("dBm");
                    break;
                }
                painter->drawText(markerInfoX + 200, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 120, 20, Qt::AlignRight, strAmptd);
                painter->drawText(markerInfoX + 340, globalUserVariable->gridYPos[0] +  (MARKER_FONT_HEIGHT * cnt) , 50, 20, Qt::AlignLeft, strAmptdUnit);
           }

            // Delta Display
            minusFlag = 0;
            ++cnt;
            strLabel = QString("D%1").arg(i + 1);
            painter->drawText(markerInfoX , globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 50, 20, Qt::AlignLeft, strLabel);
            //deltaPos = globalUserVariable->gMarkerDeltaPos[i];

            if(!globalUserVariable->gSpanMode)
            {
                deltaFreq = (qreal)globalUserVariable->gMarkerDeltaFreq[i] - globalUserVariable->gMarkerRefFreq[i];

                if (deltaFreq < 0)
                {
                    deltaFreq *= -1;
                    minusFlag = 1;
                }
                unitNo = globalUserVariable->freqUnitFindProc(deltaFreq);
                strGab = QString::number(deltaFreq, 'd',0);
                pos = globalUserVariable->notZeroPositionFindFunc(strGab);
                strValue = globalUserVariable->freqDotNumberDisplayFormatFixFunc (deltaFreq, unitNo, pos );

                if (minusFlag == 1)
                  strValue = QString("-%1").arg(strValue);

                painter->drawText(markerInfoX + 50, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 170, 20, Qt::AlignLeft, strValue);

                if ( globalUserVariable->gMarkerDeltaFreq[i] < globalUserVariable->gStartFreq)
                {
                    strAmptd = QString("- -");
                    painter->drawText(markerInfoX + 200, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 120, 20, Qt::AlignRight, strAmptd);
                }
                else if ( globalUserVariable->gMarkerDeltaFreq[i] > globalUserVariable->gStopFreq)
                {
                    strAmptd = QString("- -");
                    painter->drawText(markerInfoX + 200, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 120, 20, Qt::AlignRight, strAmptd);
                }
                else
                {
                    deltaAmptdGab = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][globalUserVariable->gMarkerDeltaPos[i]];
                    //refAmptdGab = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][globalUserVariable->gMarkerRefPos[i]];
                    refAmptdGab = markerLevel;
                    subtractGab = deltaAmptdGab - refAmptdGab;
                    globalUserVariable->gMarkerRefAmpt[i] = refAmptdGab;
                    globalUserVariable->gMarkerDeltaAmpt[i] = subtractGab;
                    //****************Johnson 0917 Change
                    switch (globalUserVariable->gAmptdUnit)
                    {
                    case SA_WATTS:
                        globalUserVariable->Delta_dbmToWattsCalculatorAndDisplayFunc(label, subtractGab);
                        globalUserVariable->charEmptySplitWorkerFunc(label);

                        strAmptd = QString(SA_watts_unit.value);
                        strAmptdUnit = QString(SA_watts_unit.unit);
                        break;
                    case SA_DBM:
                    case SA_DBV:
                    case SA_DBMV:
                    case SA_DBUV:
                        strAmptd.sprintf("%.2f", subtractGab);
                        strAmptdUnit = QString("dB");
                        break;
                    case SA_VOLT:
                        globalUserVariable->Delta_dbmToVoltCalculatorAndDisplayFunc(label, subtractGab);
                        globalUserVariable->charEmptySplitWorkerFunc(label);

                        strAmptd = QString(SA_watts_unit.value);
                        strAmptdUnit = QString(SA_watts_unit.unit);
                        break;
                    default:
                        strAmptd.sprintf("%.2f", subtractGab);
                        strAmptdUnit = QString("dB");
                        break;
                    }
                    painter->drawText(markerInfoX + 200, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 120, 20, Qt::AlignRight, strAmptd);
                    painter->drawText(markerInfoX + 340, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 50, 20, Qt::AlignLeft, strAmptdUnit);
                }
            }
            else
            {
                deltaFreq = globalUserVariable->gMarkerDeltaTime[i] -globalUserVariable->gMarkerRefTime[i];
                if (deltaFreq < 0)
                {
                    deltaFreq *= -1;
                    minusFlag = 1;
                }
                strValue = globalUserVariable->TimeTransformToQstring(deltaFreq);
                if (minusFlag == 1)
                    strValue = QString("-%1").arg(strValue);
                painter->drawText(markerInfoX + 50, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 170, 20, Qt::AlignLeft, strValue);

                if ( globalUserVariable->gMarkerDeltaTime[i] < 0)
                {
                    strAmptd = QString("- -");
                    painter->drawText(markerInfoX + 200, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 120, 20, Qt::AlignRight, strAmptd);
                }
                else if ( globalUserVariable->gMarkerDeltaTime[i] > globalUserVariable->gSweepTime)
                {
                    strAmptd = QString("- -");
                    painter->drawText(markerInfoX + 200, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 120, 20, Qt::AlignRight, strAmptd);
                }
                else
                {
                    deltaAmptdGab = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][globalUserVariable->gMarkerDeltaPos[i]];
                    //refAmptdGab = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][globalUserVariable->gMarkerRefPos[i]];
                    refAmptdGab = markerLevel;
                    subtractGab = deltaAmptdGab - refAmptdGab;
                    globalUserVariable->gMarkerRefAmpt[i] = refAmptdGab;
                    globalUserVariable->gMarkerDeltaAmpt[i] = subtractGab;
                    //****************Johnson 0917 Change
                    switch (globalUserVariable->gAmptdUnit)
                    {
                    case SA_WATTS:
                        globalUserVariable->Delta_dbmToWattsCalculatorAndDisplayFunc(label, subtractGab);
                        globalUserVariable->charEmptySplitWorkerFunc(label);

                        strAmptd = QString(SA_watts_unit.value);
                        strAmptdUnit = QString(SA_watts_unit.unit);
                        break;
                    case SA_DBM:
                    case SA_DBV:
                    case SA_DBMV:
                    case SA_DBUV:
                        strAmptd.sprintf("%.2f", subtractGab);
                        strAmptdUnit = QString("dB");
                        break;
                    case SA_VOLT:
                        globalUserVariable->Delta_dbmToVoltCalculatorAndDisplayFunc(label, subtractGab);
                        globalUserVariable->charEmptySplitWorkerFunc(label);

                        strAmptd = QString(SA_watts_unit.value);
                        strAmptdUnit = QString(SA_watts_unit.unit);
                        break;
                    default:
                        strAmptd.sprintf("%.2f", subtractGab);
                        strAmptdUnit = QString("dB");
                        break;
                    }
                    painter->drawText(markerInfoX + 200, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 120, 20, Qt::AlignRight, strAmptd);
                    painter->drawText(markerInfoX + 340, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 50, 20, Qt::AlignLeft, strAmptdUnit);
                }

            }
        }
        else if(globalUserVariable->gMarkerType[i] == DELTA_PAIR)
        {
            minusFlag = 0;
            // Ref Display
            strLabel = QString("R%1").arg(i + 1);
            painter->drawText(markerInfoX , globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 50, 20, Qt::AlignLeft, strLabel);
            //deltaPos = globalUserVariable->gMarkerRefPos[i];

            if(!globalUserVariable->gSpanMode)
            {
                freqValue =(qreal)globalUserVariable->gMarkerRefFreq[i] + globalUserVariable->gfreqOffset;
                if(freqValue < 0)
                {
                    freqValue *= -1;
                    minusFlag = 1;
                }
                unitNo = globalUserVariable->freqUnitFindProc(freqValue);
                strGab = QString::number(freqValue, 'd',0);

                pos = globalUserVariable->notZeroPositionFindFunc(strGab);
                strValue = globalUserVariable->freqDotNumberDisplayFormatFixFunc (freqValue, unitNo, pos );
                if(minusFlag) strValue = "-" + strValue;
                    painter->drawText(markerInfoX + 50, globalUserVariable->gridYPos[0]  + (MARKER_FONT_HEIGHT * cnt) , 170, 20, Qt::AlignLeft, strValue);


                //tmpMarkerRefPos = globalUserVariable->gMarkerMarkerTmpRefPos[i];
                markerLevel = (qreal)globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][globalUserVariable->gMarkerRefPos[i]] + globalUserVariable->gRefOffset;

//                markerLevel = (qreal)globalUserVariable->gMarkerTmpRefAmpt[i];
                //****************Johnson 0917 Change
                switch (globalUserVariable->gAmptdUnit)
                {
                case SA_WATTS:
                    globalUserVariable->dbmToWattsCalculatorAndDisplayFunc(label, markerLevel);
                    globalUserVariable->charEmptySplitWorkerFunc(label);

                    strAmptd = QString(SA_watts_unit.value);
                    strAmptdUnit = QString(SA_watts_unit.unit);
                    break;
                case SA_DBM:
                    strAmptd.sprintf("%.2f", markerLevel);
                    strAmptdUnit = QString("dBm");
                    break;
                case SA_DBV:
                    strAmptd.sprintf("%.2f", markerLevel + dBVFix);
                    strAmptdUnit = QString("dBV");
                    break;
                case SA_DBMV:
                    strAmptd.sprintf("%.2f", markerLevel+dBmVFix);
                    strAmptdUnit = QString("dBmV");
                    break;
                case SA_DBUV:
                    strAmptd.sprintf("%.2f", markerLevel+dBuVFix);
                    strAmptdUnit = QString("dBuV");
                    break;
                case SA_VOLT:
                    globalUserVariable->dbmToVoltCalculatorAndDisplayFunc(label, markerLevel);
                    globalUserVariable->charEmptySplitWorkerFunc(label);

                    strAmptd = QString(SA_watts_unit.value);
                    strAmptdUnit = QString(SA_watts_unit.unit);
                    break;
                default:
                    strAmptd.sprintf("%.2f", markerLevel);
                    strAmptdUnit = QString("dBm");
                    break;
                }
                painter->drawText(markerInfoX + 200, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 120, 20, Qt::AlignRight, strAmptd);
                painter->drawText(markerInfoX + 340, globalUserVariable->gridYPos[0] +  (MARKER_FONT_HEIGHT * cnt) , 50, 20, Qt::AlignLeft, strAmptdUnit);
            }
            else
            {

                QString strTime = globalUserVariable->TimeTransformToQstring(globalUserVariable->gMarkerRefTime[i]);
                strValue = strTime;
                painter->drawText(markerInfoX + 50, globalUserVariable->gridYPos[0]  + (MARKER_FONT_HEIGHT * cnt) , 170, 20, Qt::AlignLeft, strValue);

                //tmpMarkerRefPos = globalUserVariable->gMarkerMarkerTmpRefPos[i];
                markerLevel = (qreal)globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][globalUserVariable->gMarkerRefPos[i]] + globalUserVariable->gRefOffset;

//                markerLevel = (qreal)globalUserVariable->gMarkerTmpRefAmpt[i];

                switch (globalUserVariable->gAmptdUnit)
                {
                case SA_WATTS:
                    globalUserVariable->dbmToWattsCalculatorAndDisplayFunc(label, markerLevel);
                    globalUserVariable->charEmptySplitWorkerFunc(label);

                    strAmptd = QString(SA_watts_unit.value);
                    strAmptdUnit = QString(SA_watts_unit.unit);
                    break;
                case SA_DBM:
                    strAmptd.sprintf("%.2f", markerLevel);
                    strAmptdUnit = QString("dBm");
                    break;
                case SA_DBV:
                    strAmptd.sprintf("%.2f", markerLevel + dBVFix);
                    strAmptdUnit = QString("dBV");
                    break;
                case SA_DBMV:
                    strAmptd.sprintf("%.2f", markerLevel+dBmVFix);
                    strAmptdUnit = QString("dBmV");
                    break;
                case SA_DBUV:
                    strAmptd.sprintf("%.2f", markerLevel+dBuVFix);
                    strAmptdUnit = QString("dBuV");
                    break;
                case SA_VOLT:
                    globalUserVariable->dbmToVoltCalculatorAndDisplayFunc(label, markerLevel);
                    globalUserVariable->charEmptySplitWorkerFunc(label);

                    strAmptd = QString(SA_watts_unit.value);
                    strAmptdUnit = QString(SA_watts_unit.unit);
                    break;
                default:
                    strAmptd.sprintf("%.2f", markerLevel);
                    strAmptdUnit = QString("dBm");
                    break;
                }
                painter->drawText(markerInfoX + 200, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 120, 20, Qt::AlignRight, strAmptd);
                painter->drawText(markerInfoX + 340, globalUserVariable->gridYPos[0] +  (MARKER_FONT_HEIGHT * cnt) , 50, 20, Qt::AlignLeft, strAmptdUnit);
           }

            // Delta Display
            minusFlag = 0;
            ++cnt;
            strLabel = QString("D%1").arg(i + 1);
            painter->drawText(markerInfoX , globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 50, 20, Qt::AlignLeft, strLabel);
            //deltaPos = globalUserVariable->gMarkerDeltaPos[i];

            if(!globalUserVariable->gSpanMode)
            {
                deltaFreq = (qreal)globalUserVariable->gMarkerDeltaFreq[i] - globalUserVariable->gMarkerRefFreq[i];

                if (deltaFreq < 0)
                {
                    deltaFreq *= -1;
                    minusFlag = 1;
                }
                unitNo = globalUserVariable->freqUnitFindProc(deltaFreq);
                strGab = QString::number(deltaFreq, 'd',0);
                pos = globalUserVariable->notZeroPositionFindFunc(strGab);
                strValue = globalUserVariable->freqDotNumberDisplayFormatFixFunc (deltaFreq, unitNo, pos );

                if (minusFlag == 1)
                  strValue = QString("-%1").arg(strValue);

                painter->drawText(markerInfoX + 50, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 170, 20, Qt::AlignLeft, strValue);

                if ( globalUserVariable->gMarkerDeltaFreq[i] < globalUserVariable->gStartFreq)
                {
                    strAmptd = QString("- -");
                    painter->drawText(markerInfoX + 200, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 120, 20, Qt::AlignRight, strAmptd);
                }
                else if ( globalUserVariable->gMarkerDeltaFreq[i] > globalUserVariable->gStopFreq)
                {
                    strAmptd = QString("- -");
                    painter->drawText(markerInfoX + 200, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 120, 20, Qt::AlignRight, strAmptd);
                }
                else
                {
                    deltaAmptdGab = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][globalUserVariable->gMarkerDeltaPos[i]];
                    //refAmptdGab = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][globalUserVariable->gMarkerRefPos[i]];
                    refAmptdGab = markerLevel;
                    subtractGab = deltaAmptdGab - refAmptdGab;
                    globalUserVariable->gMarkerRefAmpt[i] = refAmptdGab;
                    globalUserVariable->gMarkerDeltaAmpt[i] = subtractGab;
                    //****************Johnson 0917 Change
                    switch (globalUserVariable->gAmptdUnit)
                    {
                    case SA_WATTS:
                        globalUserVariable->Delta_dbmToWattsCalculatorAndDisplayFunc(label, subtractGab);
                        globalUserVariable->charEmptySplitWorkerFunc(label);

                        strAmptd = QString(SA_watts_unit.value);
                        strAmptdUnit = QString(SA_watts_unit.unit);
                        break;
                    case SA_DBM:
                    case SA_DBV:
                    case SA_DBMV:
                    case SA_DBUV:
                        strAmptd.sprintf("%.2f", subtractGab);
                        strAmptdUnit = QString("dB");
                        break;
                    case SA_VOLT:
                        globalUserVariable->Delta_dbmToVoltCalculatorAndDisplayFunc(label, subtractGab);
                        globalUserVariable->charEmptySplitWorkerFunc(label);

                        strAmptd = QString(SA_watts_unit.value);
                        strAmptdUnit = QString(SA_watts_unit.unit);
                        break;
                    default:
                        strAmptd.sprintf("%.2f", subtractGab);
                        strAmptdUnit = QString("dB");
                        break;
                    }
                    painter->drawText(markerInfoX + 200, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 120, 20, Qt::AlignRight, strAmptd);
                    painter->drawText(markerInfoX + 340, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 50, 20, Qt::AlignLeft, strAmptdUnit);
                }
            }
            else
            {
                deltaFreq = globalUserVariable->gMarkerDeltaTime[i] -globalUserVariable->gMarkerRefTime[i];
                if (deltaFreq < 0)
                {
                    deltaFreq *= -1;
                    minusFlag = 1;
                }
                strValue = globalUserVariable->TimeTransformToQstring(deltaFreq);
                if (minusFlag == 1)
                    strValue = QString("-%1").arg(strValue);
                painter->drawText(markerInfoX + 50, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 170, 20, Qt::AlignLeft, strValue);

                if ( globalUserVariable->gMarkerDeltaTime[i] < 0)
                {
                    strAmptd = QString("- -");
                    painter->drawText(markerInfoX + 200, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 120, 20, Qt::AlignRight, strAmptd);
                }
                else if ( globalUserVariable->gMarkerDeltaTime[i] > globalUserVariable->gSweepTime)
                {
                    strAmptd = QString("- -");
                    painter->drawText(markerInfoX + 200, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 120, 20, Qt::AlignRight, strAmptd);
                }
                else
                {
                    deltaAmptdGab = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][globalUserVariable->gMarkerDeltaPos[i]];
                    //refAmptdGab = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][globalUserVariable->gMarkerRefPos[i]];
                    refAmptdGab = markerLevel;
                    subtractGab = deltaAmptdGab - refAmptdGab;
                    globalUserVariable->gMarkerRefAmpt[i] = refAmptdGab;
                    globalUserVariable->gMarkerDeltaAmpt[i] = subtractGab;
                    //****************Johnson 0917 Change
                    switch (globalUserVariable->gAmptdUnit)
                    {
                    case SA_WATTS:
                        globalUserVariable->Delta_dbmToWattsCalculatorAndDisplayFunc(label, subtractGab);
                        globalUserVariable->charEmptySplitWorkerFunc(label);

                        strAmptd = QString(SA_watts_unit.value);
                        strAmptdUnit = QString(SA_watts_unit.unit);
                        break;
                    case SA_DBM:
                    case SA_DBV:
                    case SA_DBMV:
                    case SA_DBUV:
                        strAmptd.sprintf("%.2f", subtractGab);
                        strAmptdUnit = QString("dB");
                        break;
                    case SA_VOLT:
                        globalUserVariable->Delta_dbmToVoltCalculatorAndDisplayFunc(label, subtractGab);
                        globalUserVariable->charEmptySplitWorkerFunc(label);

                        strAmptd = QString(SA_watts_unit.value);
                        strAmptdUnit = QString(SA_watts_unit.unit);
                        break;
                    default:
                        strAmptd.sprintf("%.2f", subtractGab);
                        strAmptdUnit = QString("dB");
                        break;
                    }
                    painter->drawText(markerInfoX + 200, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 120, 20, Qt::AlignRight, strAmptd);
                    painter->drawText(markerInfoX + 340, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 50, 20, Qt::AlignLeft, strAmptdUnit);
                }

            }
        }
        //Draw marker noise
        painter->setPen(colorMarker[1]);
        //painter->setPen(Qt::white);
        if(globalUserVariable->gMarkerNoise[i] == SA_ON)
        {
            ++cnt;
            if(globalUserVariable->gMarkerType[i]==REF)
            {
                globalUserVariable->gMarkerNoiseValue[i] = markerLevel -10*log10(globalUserVariable->gRbw);
                strUnit = "dBm/Hz";
            }else
            {
                globalUserVariable->gMarkerNoiseValue[i] = subtractGab -10*log10(globalUserVariable->gRbw);
                strUnit = "dBc/Hz";
            }

            strMkrNoise = QString::number(globalUserVariable->gMarkerNoiseValue[i],'f',2);
            painter->drawText(markerInfoX , globalUserVariable->gridYPos[0] +  (MARKER_FONT_HEIGHT * cnt) , 50, 20, Qt::AlignLeft, strLabel);
            painter->drawText(markerInfoX + 50, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 170, 20, Qt::AlignLeft, "Marker Noise");
            painter->drawText(markerInfoX + 200, globalUserVariable->gridYPos[0] +  (MARKER_FONT_HEIGHT * cnt) , 120, 20, Qt::AlignRight, strMkrNoise);
            painter->drawText(markerInfoX + 340, globalUserVariable->gridYPos[0] + (MARKER_FONT_HEIGHT * cnt) , 60, 20, Qt::AlignLeft, strUnit);
        }
        refreshInfo(painter,SA_TOP_RIGHT_SEC,strLabel+"  "+strValue);
    }
}

/**
 * @brief sa_UIRefresh_Control::markerRefPolygonAssignNDrawFunc
 * @param painter
 * @param pos
 * @param ArrayRefPos
 * @param drawXRefPos
 * @author Johnson
 */
void sa_UIRefresh_Control::markerRefPolygonAssignNDrawFunc(QPainter *painter, qint32 pos, qint32 ArrayRefPos, qint32 drawXRefPos)
{
    qint32 colorMode = globalUserVariable->gDisplayMode;
    QColor colorMarker[2] = MarkerColor[colorMode];
    qint32 currentTraceNo = 0;
    QString strMarker;
    QPolygon poly;
    //QFont font = painter->font();

    //font.setPointSize(10);
    //painter->setFont(font);

    painter->setFont(QFont("Arial", 10,QFont::Bold));
    static qint32 tmpArrayRefPos[MARKER_TOTAL_CNT] = {globalUserVariable->gMarkerRefPos[0],globalUserVariable->gMarkerRefPos[1],
                                                      globalUserVariable->gMarkerRefPos[2],globalUserVariable->gMarkerRefPos[3],
                                                      globalUserVariable->gMarkerRefPos[4],globalUserVariable->gMarkerRefPos[5]};
//    static bool btmpSmallCanvas = globalUserVariable->bSmallCanvas;

    if (globalUserVariable->gMarkerSelect == pos)
      painter->setPen(colorMarker[0]);
    else
      painter->setPen(colorMarker[1]);
    currentTraceNo = globalUserVariable->gTraceSelect;

    switch (globalUserVariable->gMarkerType[pos])
    {
      case REF:
        // Marker
        strMarker = QString("%1%2").arg("M").arg(pos + 1);
        break;
      case DELTA:
        // Marker
        strMarker = QString("%1%2").arg("R").arg(pos + 1);
        break;
    case DELTA_PAIR:
      // Marker
      strMarker = QString("%1%2").arg("R").arg(pos + 1);
      break;
    }
    static qreal tmpPixDrawPointY[MARKER_TOTAL_CNT] = {mPixmap_draw_point[currentTraceNo][0].y(),mPixmap_draw_point[currentTraceNo][1].y(),
                                                           mPixmap_draw_point[currentTraceNo][2].y(),mPixmap_draw_point[currentTraceNo][3].y(),
                                                           mPixmap_draw_point[currentTraceNo][4].y(),mPixmap_draw_point[currentTraceNo][5].y()};

    switch (globalUserVariable->gMarkerType[pos])
    {
      case REF:
        // Marker
        tmpPixDrawPointY[pos] = mPixmap_draw_point[currentTraceNo][ArrayRefPos].y();
        break;
      case DELTA:
        if(tmpArrayRefPos[pos] != ArrayRefPos || (globalUserVariable->gMarkerRefDelta && pos == globalUserVariable->gMarkerSelect))
        {
            globalUserVariable->gMarkerRefDelta = 0;
            if(tmpArrayRefPos[pos] != ArrayRefPos)
                tmpArrayRefPos[pos] = ArrayRefPos;
            tmpPixDrawPointY[pos] = mPixmap_draw_point[currentTraceNo][ArrayRefPos].y();
        }
        break;
    case DELTA_PAIR:
        tmpPixDrawPointY[pos] = mPixmap_draw_point[currentTraceNo][ArrayRefPos].y();
      break;
    }



    if (tmpPixDrawPointY[pos] < (DRAW_GRID_START_Y + 40))
    {
        mkrRefPoints[0].setX(drawXRefPos - 11);
        mkrRefPoints[0].setY(qint32(tmpPixDrawPointY[pos] + 40));
        mkrRefPoints[1].setX(drawXRefPos - 11);
        mkrRefPoints[1].setY(qint32(tmpPixDrawPointY[pos] + 20));
        mkrRefPoints[2].setX(drawXRefPos + 11);
        mkrRefPoints[2].setY(qint32(tmpPixDrawPointY[pos] + 20));
        mkrRefPoints[3].setX(drawXRefPos + 11);
        mkrRefPoints[3].setY(qint32(tmpPixDrawPointY[pos] + 40));

        painter->drawText(mkrRefPoints[0].x() + 2 , mkrRefPoints[0].y() - 5 , strMarker);
    }
    else
    {
        mkrRefPoints[0].setX(drawXRefPos - 11);
        mkrRefPoints[0].setY(qint32(tmpPixDrawPointY[pos] - 40));
        mkrRefPoints[1].setX(drawXRefPos - 11);
        mkrRefPoints[1].setY(qint32(tmpPixDrawPointY[pos] - 20));
        mkrRefPoints[2].setX(drawXRefPos + 11);
        mkrRefPoints[2].setY(qint32(tmpPixDrawPointY[pos] - 20));
        mkrRefPoints[3].setX(drawXRefPos + 11);
        mkrRefPoints[3].setY(qint32(tmpPixDrawPointY[pos] - 40));
        painter->drawText(mkrRefPoints[0].x() + 2 , mkrRefPoints[0].y() + 15, strMarker);
    }
    poly  << mkrRefPoints[0] << mkrRefPoints[1] << mkrRefPoints[2] << mkrRefPoints[3];
    painter->drawPolygon(poly);
}

/**
 * @brief sa_UIRefresh_Control::markerDeltaPolygonAssignNDrawFunc
 * @param painter
 * @param pos
 * @param ArrayDeltaPos
 * @param drawXDeltaPos
 * @author Johnson
 */
void sa_UIRefresh_Control::markerDeltaPolygonAssignNDrawFunc(QPainter *painter, qint32 pos, qint32 ArrayDeltaPos, qint32 drawXDeltaPos)
{
    qint32  currentTraceNo;
    QString strDeltaMarker;
    QPolygon poly;
    QFont font = painter->font();
    qint32 colorMode = globalUserVariable->gDisplayMode;
    QColor colorMarker[2] = MarkerColor[colorMode];
    font.setPointSize(10);
    painter->setFont(font);

    if (globalUserVariable->gMarkerSelect == pos)
      painter->setPen(colorMarker[0]);
    else
      painter->setPen(colorMarker[1]);

    //Delta Marker String
    strDeltaMarker = QString("%1%2").arg("D").arg(pos + 1);

    currentTraceNo = globalUserVariable->gTraceSelect;
/*
    if(globalUserVariable->bSmallCanvas)
    {
        if (smallPixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() < (DRAW_GRID_START_Y + 40))
        {
            mkrDeltaPoints[0].setX(drawXDeltaPos - 11);
            mkrDeltaPoints[0].setY(qint32(smallPixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() + 40));
            mkrDeltaPoints[1].setX(drawXDeltaPos - 11);
            mkrDeltaPoints[1].setY(qint32(smallPixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() + 20));
            mkrDeltaPoints[2].setX(drawXDeltaPos + 11);
            mkrDeltaPoints[2].setY(qint32(smallPixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() + 20));
            mkrDeltaPoints[3].setX(drawXDeltaPos + 11);
            mkrDeltaPoints[3].setY(qint32(smallPixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() + 40));
            painter->drawText(mkrDeltaPoints[0].x() + 2 , mkrDeltaPoints[0].y() - 5, strDeltaMarker);
        }
        else
        {
            mkrDeltaPoints[0].setX(drawXDeltaPos - 11);
            mkrDeltaPoints[0].setY(qint32(smallPixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() - 40));
            mkrDeltaPoints[1].setX(drawXDeltaPos - 11);
            mkrDeltaPoints[1].setY(qint32(smallPixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() - 20));
            mkrDeltaPoints[2].setX(drawXDeltaPos + 11);
            mkrDeltaPoints[2].setY(qint32(smallPixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() - 20));
            mkrDeltaPoints[3].setX(drawXDeltaPos + 11);
            mkrDeltaPoints[3].setY(qint32(smallPixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() - 40));
            painter->drawText(mkrDeltaPoints[0].x() + 2 , mkrDeltaPoints[0].y() + 15, strDeltaMarker);
        }
    }
    else
    {
        if (largePixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() < (DRAW_GRID_START_Y + 40))
        {
            mkrDeltaPoints[0].setX(drawXDeltaPos - 11);
            mkrDeltaPoints[0].setY(qint32(largePixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() + 40));
            mkrDeltaPoints[1].setX(drawXDeltaPos - 11);
            mkrDeltaPoints[1].setY(qint32(largePixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() + 20));
            mkrDeltaPoints[2].setX(drawXDeltaPos + 11);
            mkrDeltaPoints[2].setY(qint32(largePixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() + 20));
            mkrDeltaPoints[3].setX(drawXDeltaPos + 11);
            mkrDeltaPoints[3].setY(qint32(largePixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() + 40));
            painter->drawText(mkrDeltaPoints[0].x() + 2 , mkrDeltaPoints[0].y() - 5, strDeltaMarker);
        }
        else
        {
            mkrDeltaPoints[0].setX(drawXDeltaPos - 11);
            mkrDeltaPoints[0].setY(qint32(largePixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() - 40));
            mkrDeltaPoints[1].setX(drawXDeltaPos - 11);
            mkrDeltaPoints[1].setY(qint32(largePixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() - 20));
            mkrDeltaPoints[2].setX(drawXDeltaPos + 11);
            mkrDeltaPoints[2].setY(qint32(largePixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() - 20));
            mkrDeltaPoints[3].setX(drawXDeltaPos + 11);
            mkrDeltaPoints[3].setY(qint32(largePixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() - 40));
            painter->drawText(mkrDeltaPoints[0].x() + 2 , mkrDeltaPoints[0].y() + 15, strDeltaMarker);
        }
    }
*/
    if (mPixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() < (DRAW_GRID_START_Y + 40))
    {
        mkrDeltaPoints[0].setX(drawXDeltaPos - 11);
        mkrDeltaPoints[0].setY(qint32(mPixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() + 40));
        mkrDeltaPoints[1].setX(drawXDeltaPos - 11);
        mkrDeltaPoints[1].setY(qint32(mPixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() + 20));
        mkrDeltaPoints[2].setX(drawXDeltaPos + 11);
        mkrDeltaPoints[2].setY(qint32(mPixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() + 20));
        mkrDeltaPoints[3].setX(drawXDeltaPos + 11);
        mkrDeltaPoints[3].setY(qint32(mPixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() + 40));
        painter->drawText(mkrDeltaPoints[0].x() + 2 , mkrDeltaPoints[0].y() - 5, strDeltaMarker);
    }
    else
    {
        mkrDeltaPoints[0].setX(drawXDeltaPos - 11);
        mkrDeltaPoints[0].setY(qint32(mPixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() - 40));
        mkrDeltaPoints[1].setX(drawXDeltaPos - 11);
        mkrDeltaPoints[1].setY(qint32(mPixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() - 20));
        mkrDeltaPoints[2].setX(drawXDeltaPos + 11);
        mkrDeltaPoints[2].setY(qint32(mPixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() - 20));
        mkrDeltaPoints[3].setX(drawXDeltaPos + 11);
        mkrDeltaPoints[3].setY(qint32(mPixmap_draw_point[currentTraceNo][ArrayDeltaPos].y() - 40));
        painter->drawText(mkrDeltaPoints[0].x() + 2 , mkrDeltaPoints[0].y() + 15, strDeltaMarker);
    }
    poly  << mkrDeltaPoints[0] << mkrDeltaPoints[1] << mkrDeltaPoints[2] << mkrDeltaPoints[3];
    painter->drawPolygon(poly);
}

/**
 * @brief sa_UIRefresh_Control::drawMarkers
 * @param painter
 * @note  draw all markers that are not off
 * @author Johnson
 */
void sa_UIRefresh_Control::drawMarkers(QPainter *painter)
{
    qint32 i = 0,markerDeltaPos = 0,markerRefPos = 0,markerXRefPos = 0,markerXDeltaPos = 0;
    painter->setFont(QFont("Arial", 12));
    if(globalUserVariable->gTraceView[globalUserVariable->gTraceSelect] == SA_OFF)
    {
        return;
    }
    switch (globalUserVariable->gTraceType[globalUserVariable->gTraceSelect])
    {
      case SA_CLEAR_WRITE:
      case SA_TRACE_AVE:
      case SA_MAX_HOLD:
      case SA_MIN_HOLD:
      case SA_VIEW:
        for (i = 0; i < MARKER_TOTAL_CNT; i++)
        {
            if (globalUserVariable->gMarkerView[i] == SA_ON)
            {
                if (globalUserVariable->gMarkerType[i] == DELTA)
                {
                    // Delta Marker Display
                    markerDeltaPos = globalUserVariable->gMarkerDeltaPos[i];
                    markerXDeltaPos = ((qint32) (markerDeltaPos * globalUserVariable->gTraceStepSize)) + DRAW_GRID_START_X;
                    markerDeltaPolygonAssignNDrawFunc(painter, i, markerDeltaPos, markerXDeltaPos);

                    if ((markerDeltaPos == 0 && globalUserVariable->gMarkerDeltaFreq[i] < globalUserVariable->gStartFreq) ||
                        ((markerDeltaPos == globalUserVariable->gSweepTracePoint - 1) && globalUserVariable->gMarkerDeltaFreq[i] > globalUserVariable->gStopFreq))
                    {
                        painter->drawLine(markerXDeltaPos, (qint32) (mkrDeltaPoints[0].y()), markerXDeltaPos, globalUserVariable->gridYPos[10]);
                    }
                    else
                    {
                        /*
                        if(globalUserVariable->bSmallCanvas)
                        {
                            if (smallPixmap_draw_point[globalUserVariable->gTraceSelect][markerDeltaPos].y() < (DRAW_GRID_START_Y + 40)  )
                            {
                                painter->drawLine(markerXDeltaPos, (mkrDeltaPoints[0].y() + 2), markerXDeltaPos, globalUserVariable->gridYPos[10]);
                            }
                            else
                            {
                                painter->drawLine(markerXDeltaPos, (globalUserVariable->gridYPos[0] + 2), markerXDeltaPos, (mkrDeltaPoints[0].y() - 2));
                                painter->drawLine(markerXDeltaPos, (mkrDeltaPoints[1].y() + 2), markerXDeltaPos, (globalUserVariable->gridYPos[10] - 2));
                            }
                        }
                        else
                        {
                            if (largePixmap_draw_point[globalUserVariable->gTraceSelect][markerDeltaPos].y() < (DRAW_GRID_START_Y + 40)  )
                            {
                                painter->drawLine(markerXDeltaPos, (mkrDeltaPoints[0].y() + 2), markerXDeltaPos, globalUserVariable->gridYPos[10]);
                            }
                            else
                            {
                                painter->drawLine(markerXDeltaPos, (globalUserVariable->gridYPos[0] + 2), markerXDeltaPos, (mkrDeltaPoints[0].y() - 2));
                                painter->drawLine(markerXDeltaPos, (mkrDeltaPoints[1].y() + 2), markerXDeltaPos, (globalUserVariable->gridYPos[10] - 2));
                            }
                        }
                        */
                        if (mPixmap_draw_point[globalUserVariable->gTraceSelect][markerDeltaPos].y() < (DRAW_GRID_START_Y + 40)  )
                        {
                            painter->drawLine(markerXDeltaPos, (mkrDeltaPoints[0].y()), markerXDeltaPos, globalUserVariable->gridYPos[10]);
                        }
                        else
                        {
                            painter->drawLine(markerXDeltaPos, (globalUserVariable->gridYPos[0]), markerXDeltaPos, (mkrDeltaPoints[0].y()));
                            painter->drawLine(markerXDeltaPos, (mkrDeltaPoints[1].y()), markerXDeltaPos, (globalUserVariable->gridYPos[10]));
                        }
                    }
                }
                if (globalUserVariable->gMarkerType[i] == DELTA_PAIR)
                {
                    // Delta Marker Display
                    markerDeltaPos = globalUserVariable->gMarkerDeltaPos[i];
                    markerXDeltaPos = ((qint32) (markerDeltaPos * globalUserVariable->gTraceStepSize)) + DRAW_GRID_START_X;
                    markerDeltaPolygonAssignNDrawFunc(painter, i, markerDeltaPos, markerXDeltaPos);

                    if ((markerDeltaPos == 0 && globalUserVariable->gMarkerDeltaFreq[i] < globalUserVariable->gStartFreq) ||
                        ((markerDeltaPos == globalUserVariable->gSweepTracePoint - 1) && globalUserVariable->gMarkerDeltaFreq[i] > globalUserVariable->gStopFreq))
                    {
                        painter->drawLine(markerXDeltaPos, (qint32) (mkrDeltaPoints[0].y()), markerXDeltaPos, globalUserVariable->gridYPos[10]);
                    }
                    else
                    {
                        if (mPixmap_draw_point[globalUserVariable->gTraceSelect][markerDeltaPos].y() < (DRAW_GRID_START_Y + 40)  )
                        {
                            painter->drawLine(markerXDeltaPos, (mkrDeltaPoints[0].y()), markerXDeltaPos, globalUserVariable->gridYPos[10]);
                        }
                        else
                        {
                            painter->drawLine(markerXDeltaPos, (globalUserVariable->gridYPos[0]), markerXDeltaPos, (mkrDeltaPoints[0].y()));
                            painter->drawLine(markerXDeltaPos, (mkrDeltaPoints[1].y()), markerXDeltaPos, (globalUserVariable->gridYPos[10]));
                        }
                    }
                }
                markerRefPos = globalUserVariable->gMarkerRefPos[i];
                markerXRefPos = ((qint32) (markerRefPos * globalUserVariable->gTraceStepSize)) + DRAW_GRID_START_X;
                markerRefPolygonAssignNDrawFunc(painter, i, markerRefPos, markerXRefPos);

                if ((markerRefPos == 0 && globalUserVariable->gMarkerRefFreq[i] < globalUserVariable->gStartFreq) ||
                    ((markerRefPos == globalUserVariable->gSweepTracePoint - 1) && globalUserVariable->gMarkerRefFreq[i] > globalUserVariable->gStopFreq))
                {
                    painter->drawLine(markerXRefPos, (qint32) (mkrRefPoints[0].y()), markerXRefPos, globalUserVariable->gridYPos[10]);
                }
                else
                {
                  /*
                    if(globalUserVariable->bSmallCanvas)
                    {
                        if (smallPixmap_draw_point[globalUserVariable->gTraceSelect][markerRefPos].y() < (DRAW_GRID_START_Y + 40) )
                        {
                            painter->drawLine(markerXRefPos, (mkrRefPoints[0].y() + 2), markerXRefPos, globalUserVariable->gridYPos[10]);
                        }
                        else
                        {
                            painter->drawLine(markerXRefPos, (globalUserVariable->gridYPos[0] + 2), markerXRefPos, (mkrRefPoints[0].y() - 2));
                            painter->drawLine(markerXRefPos, (mkrRefPoints[1].y() + 2), markerXRefPos, (globalUserVariable->gridYPos[10] - 2));
                        }
                    }
                    else
                    {
                        if (largePixmap_draw_point[globalUserVariable->gTraceSelect][markerRefPos].y() < (DRAW_GRID_START_Y + 40) )
                        {
                            painter->drawLine(markerXRefPos, (mkrRefPoints[0].y() + 2), markerXRefPos, globalUserVariable->gridYPos[10]);
                        }
                        else
                        {
                            painter->drawLine(markerXRefPos, (globalUserVariable->gridYPos[0] + 2), markerXRefPos, (mkrRefPoints[0].y() - 2));
                            painter->drawLine(markerXRefPos, (mkrRefPoints[1].y() + 2), markerXRefPos, (globalUserVariable->gridYPos[10] - 2));
                        }
                    }
               */
                    if (mPixmap_draw_point[globalUserVariable->gTraceSelect][markerRefPos].y() < (DRAW_GRID_START_Y + 40) )
                    {
                        painter->drawLine(markerXRefPos, (mkrRefPoints[0].y() + 2), markerXRefPos, globalUserVariable->gridYPos[10]);
                    }
                    else
                    {
                        painter->drawLine(markerXRefPos, (globalUserVariable->gridYPos[0]), markerXRefPos, (mkrRefPoints[0].y()));
                        painter->drawLine(markerXRefPos, (mkrRefPoints[1].y()), markerXRefPos, (globalUserVariable->gridYPos[10]));
                    }
                }
            }
        }
        break;
    }
}

/**
 * @brief BitSA::yaxis_cal
 * @param level
 * @return the value of y
 * @note caculate the value of y depended on reflevel and refoffset
 * @author Johnson
 */
qint32 sa_UIRefresh_Control::yaxis_cal(qreal level)
{
  qreal f64dBmPerYPixel;
  qint32 ret;
  qreal f64ScaleDiv = globalUserVariable->gScaleDiv;
  qreal f64BaseLevel = globalUserVariable->gRefLevel + globalUserVariable->gRefOffset;

#if 0
  f64dBmPerYPixel = tConfigGUI.f64ScaleDiv / (f64)(GRID_VSTEP);
  ret = (int)round((tConfigGUI.f64BaseLevel - level) / f64dBmPerYPixel);
#else
  f64dBmPerYPixel = f64ScaleDiv / (qreal)(SA_guiDrawSet.gridVerStep);
  ret = (qint32)round((f64BaseLevel - level) / f64dBmPerYPixel);

#endif

  if (ret < 0 /*+ SA_LINEWIDTH * 0.5*/)
    {
      ret = 0 /*+ SA_LINEWIDTH * 0.5*/;
    }
  else if (ret > globalUserVariable->gridYPos[GRIDY_LENGTH-1] /*- SA_LINEWIDTH * 0.5*/-DRAW_GRID_START_Y)
    {
      ret = globalUserVariable->gridYPos[GRIDY_LENGTH-1]/*- SA_LINEWIDTH * 0.5*/ -DRAW_GRID_START_Y;
    }
  return ret;
}
/**
 * @brief sa_UIRefresh_Control::mousePressReflect
 * @param x
 * @param y
 * @note  reflect the mouse_press of its parent
 * @author Johnson
 */
void sa_UIRefresh_Control::mousePressReflect(qint32 x, qint32 y, bool bSmall)
{
//    int markerSpace = 0;

//    if (globalUserVariable->gMarkerDisplay == MKR_TABLE && SA_guiDrawSet.markerOnCount != 0)
//    {
//        markerSpace = SA_guiDrawSet.markerOnCount * MARKER_FONT_HEIGHT;
//    }

    /*
    if(bSmall) calculatorXPos = (x - DRAW_GRID_START_X) / smallPixmapPixelStep;
    else calculatorXPos = (x - DRAW_GRID_START_X) / largePixmapPixelStep;
    */
    calculatorXPos = (x - DRAW_GRID_START_X) / mPixmapPixelStep;
    const qint32 marginXgab = 10;
    qint32 markerPos = 0;

    marker_mouse_move_pos = SA_NOT_MOUSE_CLICK;
    gateview_mouse_move = -1;

    if ((x > sweepRangeRect.x()) && (x  < sweepRangeRect.right()))
    {
        if ((y > sweepRangeRect.y())&& (y < (sweepRangeRect.bottom()/* - markerSpace*/) ))
        {
            if(globalUserVariable->gGateViewStatus == SA_ON)
            {
                qint32 startXIndex = (qint32)NUM_SWEEP_POINT * globalUserVariable->gEdgTrigDely/globalUserVariable->gSweepTime;
                qint32 stopXIndex = (qint32)NUM_SWEEP_POINT * (globalUserVariable->gEdgTrigDoorWdth + globalUserVariable->gEdgTrigDely)/globalUserVariable->gSweepTime;
                if(startXIndex > NUM_SWEEP_POINT - 1) startXIndex = NUM_SWEEP_POINT - 1;
                if(stopXIndex > NUM_SWEEP_POINT - 1) stopXIndex = NUM_SWEEP_POINT - 1;

                if (((calculatorXPos >= (startXIndex - marginXgab)) && (calculatorXPos <= (startXIndex + marginXgab))) ||
                        ((calculatorXPos >= (stopXIndex - marginXgab)) && (calculatorXPos <= (stopXIndex + marginXgab))))
                {
                    if(abs(calculatorXPos - startXIndex) > abs(calculatorXPos - stopXIndex))
                        gateview_mouse_move = SA_GATELEN_MOUSE_ACTION;
                    else
                        gateview_mouse_move = SA_GATEDLY_MOUSE_ACTION;
                    marker_mouse_move_pos = SA_MOUSE_ACTION ;
                    if(globalUserVariable->gSweepType == SA_SINGLE)
                    {
                        refreshPixmap();
                    }
                }
            }
            else
            {
                for (int i = 0; i < MARKER_TOTAL_CNT; i++)
                {
                    if (globalUserVariable->gMarkerView[i] == SA_ON )
                    {
                        if (globalUserVariable->gMarkerType[i] == REF)
                          markerPos = (int) (globalUserVariable->gMarkerRefPos[i]);
                        else
                          markerPos = (int) (globalUserVariable->gMarkerDeltaPos[i]);


                        if ((calculatorXPos >= (markerPos - marginXgab)) && (calculatorXPos <= (markerPos + marginXgab)))
                        {
                            globalUserVariable->gMarkerSelect = i;
                            marker_mouse_move_pos = SA_MOUSE_ACTION ;
                            if(globalUserVariable->gSweepType == SA_SINGLE)
                            {
                                refreshPixmap();
                            }
                            emit infoRefresh(SA_INFO_MARKER_INDEX);
                        }
                    }
                }
            }
        }
    }
}

/**
 * @brief sa_UIRefresh_Control::mouseMoveReflect
 * @param x
 * @param y
 * @param bSmall
 * @note  reflect the mouse_move of its parent
 * @author Johnson
 */
void sa_UIRefresh_Control::mouseMoveReflect(qint32 x,qint32 y,bool bSmall)
{
    if (marker_mouse_move_pos == SA_MOUSE_ACTION)
    {
        if(globalUserVariable->gGateViewStatus == SA_ON)
        {
            qint32 startXIndex = (qint32)NUM_SWEEP_POINT * globalUserVariable->gEdgTrigDely/globalUserVariable->gSweepTime;
            qint32 stopXIndex = (qint32)NUM_SWEEP_POINT * (globalUserVariable->gEdgTrigDoorWdth + globalUserVariable->gEdgTrigDely)/globalUserVariable->gSweepTime;
            if(startXIndex > NUM_SWEEP_POINT - 1) startXIndex = NUM_SWEEP_POINT - 1;
            if(stopXIndex > NUM_SWEEP_POINT - 1) stopXIndex = NUM_SWEEP_POINT - 1;

            if(gateview_mouse_move == SA_GATEDLY_MOUSE_ACTION)
            {
                calculatorXPos = (x - DRAW_GRID_START_X) / mPixmapPixelStep;
                if(x >=  (qint32) sweepRangeRect.right() && globalUserVariable->gEdgTrigDely > globalUserVariable->gSweepTime)
                {
                    globalUserVariable->gEdgTrigDely = globalUserVariable->gSweepTime;
                    return;
                }

                if(globalUserVariable->gEdgTrigDely >= globalUserVariable->gSweepTime)
                {
                    globalUserVariable->gEdgTrigDely = globalUserVariable->gSweepTime +
                                                       (qreal)(calculatorXPos - startXIndex)/(globalUserVariable->gSweepTracePoint - 1) *
                                                        globalUserVariable->gSweepTime;
                }
                else globalUserVariable->gEdgTrigDely = globalUserVariable->gEdgTrigDely +
                                                   (qreal)(calculatorXPos - startXIndex)/(globalUserVariable->gSweepTracePoint - 1) *
                                                    globalUserVariable->gSweepTime;
                if(globalUserVariable->gEdgTrigDely < 0.) globalUserVariable->gEdgTrigDely = 0.;
                else if(globalUserVariable->gEdgTrigDely > globalUserVariable->gSweepTime)
                    globalUserVariable->gEdgTrigDely = globalUserVariable->gSweepTime;

                emit infoRefresh(SA_INFO_GATEDLY);
            }
            else if(gateview_mouse_move == SA_GATELEN_MOUSE_ACTION)
            {
                calculatorXPos = (x - DRAW_GRID_START_X) / mPixmapPixelStep;
                if(calculatorXPos < startXIndex) return;
                if(x >=  (qint32) sweepRangeRect.right() &&
                   globalUserVariable->gEdgTrigDoorWdth + globalUserVariable->gEdgTrigDely > globalUserVariable->gSweepTime)
                {
                    globalUserVariable->gEdgTrigDoorWdth = globalUserVariable->gSweepTime - globalUserVariable->gEdgTrigDely;
                    return;
                }

                if(globalUserVariable->gEdgTrigDoorWdth >= globalUserVariable->gSweepTime - globalUserVariable->gEdgTrigDely)
                    globalUserVariable->gEdgTrigDoorWdth = globalUserVariable->gSweepTime - globalUserVariable->gEdgTrigDely +
                                                       (qreal)(calculatorXPos - stopXIndex)/(globalUserVariable->gSweepTracePoint - 1) *
                                                        globalUserVariable->gSweepTime;
                else globalUserVariable->gEdgTrigDoorWdth = globalUserVariable->gEdgTrigDoorWdth +
                                                   (qreal)(calculatorXPos - stopXIndex)/(globalUserVariable->gSweepTracePoint - 1) *
                                                    globalUserVariable->gSweepTime;
                if(globalUserVariable->gEdgTrigDoorWdth < 0.0001) globalUserVariable->gEdgTrigDoorWdth = 0.0001;
                else if(globalUserVariable->gEdgTrigDoorWdth > globalUserVariable->gSweepTime - globalUserVariable->gEdgTrigDely)
                    globalUserVariable->gEdgTrigDoorWdth = globalUserVariable->gSweepTime - globalUserVariable->gEdgTrigDely;

                emit infoRefresh(SA_INFO_GATELEN);
            }
        }
        else
        {
            qreal steptime = globalUserVariable->gSweepTime/(globalUserVariable->gTracePoint - 1);
            if (x < sweepRangeRect.x()) return;
            if (x >=  (qint32) sweepRangeRect.right())
            {
                if (globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == REF)
                {
                    globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect] =  globalUserVariable->gSweepTracePoint - 1;
                    if(!globalUserVariable->gSpanMode)
                    {
                        globalUserVariable->gMarkerRefFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStopFreq;
                    }else
                    {
                        globalUserVariable->gMarkerRefTime[globalUserVariable->gMarkerSelect] = globalUserVariable->gSweepTime;
                    }
                }
                else
                {
                    globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect] =  globalUserVariable->gSweepTracePoint - 1;
                    if(!globalUserVariable->gSpanMode)
                    {
                        globalUserVariable->gMarkerDeltaFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStopFreq;
                    }else
                    {
                        globalUserVariable->gMarkerDeltaTime[globalUserVariable->gMarkerSelect] = globalUserVariable->gSweepTime;
                    }
                }
                return;
            }
            calculatorXPos = (x - DRAW_GRID_START_X) / mPixmapPixelStep;
            xPos[globalUserVariable->gMarkerSelect] = x;//Johnson 0629


            //Johnson Change0507
            if (globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == REF)
            {
                globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect] = calculatorXPos;
                if(globalUserVariable->gZeroSpanAction == SA_OFF)
                  globalUserVariable->gMarkerRefFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * calculatorXPos);
                else
                    globalUserVariable->gMarkerRefTime[globalUserVariable->gMarkerSelect] = steptime * calculatorXPos;
            }
            else
            {
                globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect] =  calculatorXPos;
                if(globalUserVariable->gZeroSpanAction == SA_OFF)
                  globalUserVariable->gMarkerDeltaFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * calculatorXPos);
                else
                    globalUserVariable->gMarkerDeltaTime[globalUserVariable->gMarkerSelect] = steptime * calculatorXPos;
            }
        }
    }
}

/**
 * @brief sa_UIRefresh_Control::mouseRealseReflect
 * @param x
 * @param y
 * @param bSmall
 * @note  reflect the mouse_release of its parent
 * @author Johnson
 */
void sa_UIRefresh_Control::mouseRealseReflect(qint32 x,qint32 y,bool bSmall)
{
    marker_mouse_move_pos = SA_MOUSE_ACTION;
}

/**
 * @brief sa_UIRefresh_Control::keyPressReflect
 * @param keyValue
 * @param bSmall
 * @note  reflect the key_press of its parent
 * @author Johnson
 */
void sa_UIRefresh_Control::keyPressReflect(qint32 keyValue,bool bSmall)
{
    qreal timestep = globalUserVariable->gSweepTime/(globalUserVariable->gTracePoint - 1);
    switch(keyValue){
    case Qt::Key_0:  break;
    case Qt::Key_1:  break;
    case Qt::Key_2:  break;
    case Qt::Key_3:  break;
    case Qt::Key_4:  break;
    case Qt::Key_5:  break;
    case Qt::Key_6:  break;
    case Qt::Key_7:  break;
    case Qt::Key_8:  break;
    case Qt::Key_9:  break;
    case Qt::Key_Shift:
        if(globalUserVariable->bShiftKeyPressed) globalUserVariable->bShiftKeyPressed = false;
        else globalUserVariable->bShiftKeyPressed = true;
        break;
    case Qt::Key_F5://key_menu
        break;
    case Qt::Key_F1://key_preset
        break;
    case Qt::Key_Up:
    case Qt::Key_F8:
        if(globalUserVariable->gMarkerView[globalUserVariable->gMarkerSelect] == SA_ON)
        {
            if (xPos[globalUserVariable->gMarkerSelect] <= sweepRangeRect.right())
            {
                if(globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == REF)
                    xPos[globalUserVariable->gMarkerSelect] = (globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect]+NUM_SWEEP_POINT/10)*globalUserVariable->gTraceStepSize+DRAW_GRID_START_X;
                else
                    xPos[globalUserVariable->gMarkerSelect] = (globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect]+NUM_SWEEP_POINT/10)*globalUserVariable->gTraceStepSize+DRAW_GRID_START_X;
            }

            if (xPos[globalUserVariable->gMarkerSelect] >= sweepRangeRect.right())
            {
                if (globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == REF)
                {
                    globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect] =  globalUserVariable->gSweepTracePoint - 1;
                    if(!globalUserVariable->gSpanMode)
                    {
                    globalUserVariable->gMarkerRefFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStopFreq;
                    }else
                    {
                        globalUserVariable->gMarkerRefTime[globalUserVariable->gMarkerSelect] = globalUserVariable->gSweepTime;
                }

                }
                else
                {
                    globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect] =  globalUserVariable->gSweepTracePoint - 1;
                    if(!globalUserVariable->gSpanMode)
                    {
                    globalUserVariable->gMarkerDeltaFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStopFreq;
                    }else
                    {
                        globalUserVariable->gMarkerDeltaTime[globalUserVariable->gMarkerSelect] = globalUserVariable->gSweepTime;
                }
                }
               return;
            }
            if(globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == REF)
                calculatorXPos = globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect]+NUM_SWEEP_POINT/10;
            else
                calculatorXPos = globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect]+NUM_SWEEP_POINT/10;

            if (globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == REF)
            {
                globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect] = calculatorXPos;
                if(globalUserVariable->gZeroSpanAction == SA_OFF)
                  globalUserVariable->gMarkerRefFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * calculatorXPos);
                else
                    globalUserVariable->gMarkerRefTime[globalUserVariable->gMarkerSelect] = timestep * calculatorXPos;
            }
            else
            {
                globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect] =  calculatorXPos;
                if(globalUserVariable->gZeroSpanAction == SA_OFF)
                  globalUserVariable->gMarkerDeltaFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * calculatorXPos);
                else
                    globalUserVariable->gMarkerDeltaTime[globalUserVariable->gMarkerSelect] = timestep * calculatorXPos;
            }
        }
        break;
    case Qt::Key_Down:
    case Qt::Key_F9:
        if(globalUserVariable->gMarkerView[globalUserVariable->gMarkerSelect] == SA_ON)
        {
            if (xPos[globalUserVariable->gMarkerSelect] < sweepRangeRect.x()) return;

            if (globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == REF)
            {
                if(globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect] >= NUM_SWEEP_POINT/10)
                {
                    xPos[globalUserVariable->gMarkerSelect] = (globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect]-NUM_SWEEP_POINT/10)*globalUserVariable->gTraceStepSize+DRAW_GRID_START_X;
                    calculatorXPos = globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect]-NUM_SWEEP_POINT/10;
                }
                else
                {
                    xPos[globalUserVariable->gMarkerSelect] = DRAW_GRID_START_X;
                    globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect] = 0;
                    calculatorXPos = globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect];
                }
            }
            else
            {
                if(globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect] >= NUM_SWEEP_POINT/10)
                {
                    xPos[globalUserVariable->gMarkerSelect] = (globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect]-NUM_SWEEP_POINT/10)*globalUserVariable->gTraceStepSize+DRAW_GRID_START_X;
                    calculatorXPos = globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect]-NUM_SWEEP_POINT/10;
                }
                else
                {
                    xPos[globalUserVariable->gMarkerSelect] = DRAW_GRID_START_X;
                    globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect] = 0;
                    calculatorXPos = globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect];
                }
            }

            if (globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == REF)
            {
                globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect] = calculatorXPos;
                if(globalUserVariable->gZeroSpanAction == SA_OFF)
                  globalUserVariable->gMarkerRefFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * calculatorXPos);
                else
                    globalUserVariable->gMarkerRefTime[globalUserVariable->gMarkerSelect] = timestep * calculatorXPos;
            }
            else
            {
                globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect] =  calculatorXPos;
                if(globalUserVariable->gZeroSpanAction == SA_OFF)
                  globalUserVariable->gMarkerDeltaFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * calculatorXPos);
                else
                    globalUserVariable->gMarkerDeltaTime[globalUserVariable->gMarkerSelect] = timestep * calculatorXPos;
            }
        }
        break;
    case Qt::Key_Right:
    case Qt::Key_F7:
        if(globalUserVariable->gMarkerView[globalUserVariable->gMarkerSelect] == SA_ON)
        {
            if (xPos[globalUserVariable->gMarkerSelect] < sweepRangeRect.right())
            {
                if (globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == REF)
                    xPos[globalUserVariable->gMarkerSelect] = (globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect]+1)*globalUserVariable->gTraceStepSize+DRAW_GRID_START_X;
                else
                    xPos[globalUserVariable->gMarkerSelect] = (globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect]+1)*globalUserVariable->gTraceStepSize+DRAW_GRID_START_X;
            }

            if (xPos[globalUserVariable->gMarkerSelect] >=sweepRangeRect.right())
            {
                if (globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == REF)
                {
                    globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect] =  globalUserVariable->gSweepTracePoint - 1;
                    if(!globalUserVariable->gSpanMode)
                    {
                    globalUserVariable->gMarkerRefFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStopFreq;
                    }else
                    {
                        globalUserVariable->gMarkerRefTime[globalUserVariable->gMarkerSelect] = globalUserVariable->gSweepTime;
                }
                }
                else
                {
                    globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect] =  globalUserVariable->gSweepTracePoint - 1;
                    if(!globalUserVariable->gSpanMode)
                    {
                    globalUserVariable->gMarkerDeltaFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStopFreq;
                    }else
                    {
                        globalUserVariable->gMarkerDeltaTime[globalUserVariable->gMarkerSelect] = globalUserVariable->gSweepTime;
                }

                }
                return;
            }
            if (globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == REF)
                calculatorXPos = globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect]+1;
            else
                calculatorXPos = globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect]+1;

            if (globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == REF)
            {
                globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect] = calculatorXPos;
                if(globalUserVariable->gZeroSpanAction == SA_OFF)
                  globalUserVariable->gMarkerRefFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * calculatorXPos);
                else
                    globalUserVariable->gMarkerRefTime[globalUserVariable->gMarkerSelect] = timestep * calculatorXPos;
            }
            else
            {
                globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect] =  calculatorXPos;
                if(globalUserVariable->gZeroSpanAction == SA_OFF)
                  globalUserVariable->gMarkerDeltaFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * calculatorXPos);
                else
                    globalUserVariable->gMarkerDeltaTime[globalUserVariable->gMarkerSelect] = timestep * calculatorXPos;
            }
        }
        break;
    case Qt::Key_F3://clockwise //Johnson 0629 0726

        if(globalUserVariable->PrimaryAction == SA_SWEEP)
        {
            if(globalUserVariable->gAutoSweepTime == SA_OFF)
            {
                globalUserVariable->gSweepTime += globalUserVariable->getTimeUnit(globalUserVariable->gSweepTime);
                //bwSweepSettingDisplayFunc();
            }
        }
        else if(globalUserVariable->PrimaryAction == SA_AMPLITUDE){
            double level = globalUserVariable->gRefLevel + 0.01;

            if (SPEC_AMPTD_MIN <= level && level  <= SPEC_AMPTD_MAX)
            {
                globalUserVariable->gRefLevel = level;
            }
        }
        else if(globalUserVariable->PrimaryAction == SA_FREQUENCY)
        {
            globalUserVariable->gCenterFreq = globalUserVariable->gCFFreq+globalUserVariable->gCenterFreq;

            if(globalUserVariable->gZeroSpanAction)
              {
                globalUserVariable->gCenterFreq = globalUserVariable->gCenterFreq > SPEC_FREQ_MAX ?  SPEC_FREQ_MAX : globalUserVariable->gCenterFreq;
                globalUserVariable->gCenterFreq = globalUserVariable->gCenterFreq < SPEC_FREQ_MIN ? SPEC_FREQ_MIN : globalUserVariable->gCenterFreq;
                globalUserVariable->gStartFreq = globalUserVariable->gStopFreq = globalUserVariable->gCenterFreq;
                globalUserVariable->gSpanFreq = 0;
              }
            else
              {
                globalUserVariable->adjustFreqByCer();
                //adjust step freq
                globalUserVariable->stepFreqCalculatorFunc();
                // Marker Position
                globalUserVariable->markerPositionReCalculatorFunc();
              }
        }
        else
        {
            if(globalUserVariable->gMarkerView[globalUserVariable->gMarkerSelect] == SA_ON){
                if (xPos[globalUserVariable->gMarkerSelect] < sweepRangeRect.right()) {
                    if (globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == REF)
                        xPos[globalUserVariable->gMarkerSelect] = (globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect]+1)*globalUserVariable->gTraceStepSize+DRAW_GRID_START_X;
                    else
                        xPos[globalUserVariable->gMarkerSelect] = (globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect]+1)*globalUserVariable->gTraceStepSize+DRAW_GRID_START_X;
                }
                if (xPos[globalUserVariable->gMarkerSelect] >=sweepRangeRect.right()) {
                    if (globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == REF) {
                        globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect] =  globalUserVariable->gSweepTracePoint - 1;
                        if(!globalUserVariable->gSpanMode)
                        {
                        globalUserVariable->gMarkerRefFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStopFreq;
                        }else
                        {
                            globalUserVariable->gMarkerRefTime[globalUserVariable->gMarkerSelect] = globalUserVariable->gSweepTime;
                        }
                      }  else {
                        globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect] =  globalUserVariable->gSweepTracePoint - 1;
                        if(!globalUserVariable->gSpanMode)
                        {
                        globalUserVariable->gMarkerDeltaFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStopFreq;
                        }else
                        {
                            globalUserVariable->gMarkerDeltaTime[globalUserVariable->gMarkerSelect] = globalUserVariable->gSweepTime;
                      }
                    }
                    return;
                  }
                if (globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == REF)
                    calculatorXPos = globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect]+1;
                else
                    calculatorXPos = globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect]+1;

                if (globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == REF) {
                    globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect] = calculatorXPos;
                    if(globalUserVariable->gZeroSpanAction == SA_OFF)
                      globalUserVariable->gMarkerRefFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * calculatorXPos);
                    else
                        globalUserVariable->gMarkerRefTime[globalUserVariable->gMarkerSelect] = calculatorXPos * timestep;
                  }  else {
                    globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect] =  calculatorXPos;
                    if(globalUserVariable->gZeroSpanAction == SA_OFF)
                      globalUserVariable->gMarkerDeltaFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * calculatorXPos);
                    else
                        globalUserVariable->gMarkerDeltaTime[globalUserVariable->gMarkerSelect] = calculatorXPos * timestep;
                  }
            }
        }
        break;
    case Qt::Key_F6://left
    case Qt::Key_Left:
        if(globalUserVariable->gMarkerView[globalUserVariable->gMarkerSelect] == SA_ON) {
            if (xPos[globalUserVariable->gMarkerSelect] < sweepRangeRect.x()) return;

            if (globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == REF) {
                if(globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect]>=1){
                    xPos[globalUserVariable->gMarkerSelect] = (globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect]-1)*globalUserVariable->gTraceStepSize+DRAW_GRID_START_X;
                    calculatorXPos = globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect]-1;
                }
                else{
                    xPos[globalUserVariable->gMarkerSelect] = DRAW_GRID_START_X;
                    globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect] = 0;
                    calculatorXPos = globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect];
                }
            }
            else {
                if(globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect]>=1){
                    xPos[globalUserVariable->gMarkerSelect] = (globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect]-1)*globalUserVariable->gTraceStepSize+DRAW_GRID_START_X;
                    calculatorXPos = globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect]-1;
                }
                else{
                    xPos[globalUserVariable->gMarkerSelect] = DRAW_GRID_START_X;
                    globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect] = 0;
                    calculatorXPos = globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect];
                }
            }

            if (globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == REF) {
                globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect] = calculatorXPos;
                if(globalUserVariable->gZeroSpanAction == SA_OFF)
                  globalUserVariable->gMarkerRefFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * calculatorXPos);
                else
                    globalUserVariable->gMarkerRefTime[globalUserVariable->gMarkerSelect] = calculatorXPos * timestep;
              }  else {
                globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect] =  calculatorXPos;
                if(globalUserVariable->gZeroSpanAction == SA_OFF)
                  globalUserVariable->gMarkerDeltaFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * calculatorXPos);
                else
                    globalUserVariable->gMarkerDeltaTime[globalUserVariable->gMarkerSelect] = calculatorXPos * timestep;
              }
        }
        break;
    case Qt::Key_F4://anticlockwise
        if(globalUserVariable->PrimaryAction == SA_SWEEP)
        {
            if(globalUserVariable->gAutoSweepTime == SA_OFF)
            {
                if(globalUserVariable->gSweepTime <10) globalUserVariable->gSweepTime -= globalUserVariable->getTimeUnit(globalUserVariable->gSweepTime);;
                //bwSweepSettingDisplayFunc();
            }
        }
        else if(globalUserVariable->PrimaryAction == SA_AMPLITUDE)
        {
            qreal level = globalUserVariable->gRefLevel - 0.01;

            if (SPEC_AMPTD_MIN <= level && level  <= SPEC_AMPTD_MAX)
            {
                globalUserVariable->gRefLevel = level;
            }
        }
        else if(globalUserVariable->PrimaryAction == SA_FREQUENCY)
        {
            globalUserVariable->gCenterFreq = globalUserVariable->gCenterFreq-globalUserVariable->gCFFreq;

            if(globalUserVariable->gZeroSpanAction)
              {
                globalUserVariable->gCenterFreq = globalUserVariable->gCenterFreq > SPEC_FREQ_MAX ?  SPEC_FREQ_MAX : globalUserVariable->gCenterFreq;
                globalUserVariable->gCenterFreq = globalUserVariable->gCenterFreq < SPEC_FREQ_MIN ? SPEC_FREQ_MIN : globalUserVariable->gCenterFreq;
                globalUserVariable->gStartFreq = globalUserVariable->gStopFreq = globalUserVariable->gCenterFreq;
                globalUserVariable->gSpanFreq = 0;
              }
            else
              {
                globalUserVariable->adjustFreqByCer();
                //adjust step freq
                globalUserVariable->stepFreqCalculatorFunc();
                // Marker Position
                globalUserVariable->markerPositionReCalculatorFunc();
              }
        }
        else
        {
            if(globalUserVariable->gMarkerView[globalUserVariable->gMarkerSelect] == SA_ON)
            {
                if (xPos[globalUserVariable->gMarkerSelect] < sweepRangeRect.x()) return;

                if(globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == REF)
                {
                    if(globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect]>=1)
                    {
                        xPos[globalUserVariable->gMarkerSelect] = (globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect]-1)*globalUserVariable->gTraceStepSize+DRAW_GRID_START_X;
                        calculatorXPos = globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect]-1;
                    }
                    else
                    {
                        xPos[globalUserVariable->gMarkerSelect] = DRAW_GRID_START_X;
                        globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect] = 0;
                        calculatorXPos = globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect];
                    }
                }
                else
                {
                    if(globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect]>=1)
                    {
                        xPos[globalUserVariable->gMarkerSelect] = (globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect]-1)*globalUserVariable->gTraceStepSize+DRAW_GRID_START_X;
                        calculatorXPos = globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect]-1;
                    }
                    else
                    {
                        xPos[globalUserVariable->gMarkerSelect] = DRAW_GRID_START_X;
                        globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect] = 0;
                        calculatorXPos = globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect];
                    }
                }

                if (globalUserVariable->gMarkerType[globalUserVariable->gMarkerSelect] == REF)
                {
                    globalUserVariable->gMarkerRefPos[globalUserVariable->gMarkerSelect] = calculatorXPos;
                    if(globalUserVariable->gZeroSpanAction == SA_OFF)
                      globalUserVariable->gMarkerRefFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * calculatorXPos);
                    else
                        globalUserVariable->gMarkerRefTime[globalUserVariable->gMarkerSelect] = calculatorXPos * timestep;
                }
                else
                {
                    globalUserVariable->gMarkerDeltaPos[globalUserVariable->gMarkerSelect] =  calculatorXPos;
                    if(globalUserVariable->gZeroSpanAction == SA_OFF)
                      globalUserVariable->gMarkerDeltaFreq[globalUserVariable->gMarkerSelect] = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * calculatorXPos);
                    else
                        globalUserVariable->gMarkerDeltaTime[globalUserVariable->gMarkerSelect] = calculatorXPos * timestep;
                }
            }
        }
        break;
    default: break;
    }
}

/**
 * @brief sa_UIRefresh_Control::setPixmapSize
 * @param mWidth
 * @param mHeight
 * @author Johnson
 */
void sa_UIRefresh_Control::setPixmapSize(qint32 mWidth,qint32 mHeight)
{
    mPixmap = mPixmap.scaled(mWidth,mHeight,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    forePixmap = forePixmap.scaled(mWidth,mHeight,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    backPixmap = backPixmap.scaled(mWidth,mHeight,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    mPixmapPixelStep =(qreal) (mWidth -SA_LEFTDIS -SA_RIGHTDIS) / (globalUserVariable->gSweepTracePoint-1);
    globalUserVariable->mDrawWidth = mWidth;
    globalUserVariable->mDrawHeight = mHeight;
    refreshRelativePara();
    for (qint32 t = TR1; t < NUM_TRACE; t++)
    {
        mPixmap_draw_point[t].clear();
        for (qint32 i = 0; i < globalUserVariable->gSweepTracePoint; i++)
        {
            if(globalUserVariable->gTraceType[t] == SA_VIEW)
            {
//                mPixmap_draw_point[t][i].setY(yaxis_cal(globalUserVariable->gTraceMeasureVal[t][i] + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y);
                mPixmap_draw_point[t].append(QPointF(DRAW_GRID_START_X + i * mPixmapPixelStep,yaxis_cal(globalUserVariable->gTraceMeasureVal[t][i] + globalUserVariable->gRefOffset) + DRAW_GRID_START_Y));
            }
            else
            {
//                mPixmap_draw_point[t][i].setY( mHeight-  SA_BOTTOMDIS);
                mPixmap_draw_point[t].append(QPointF( DRAW_GRID_START_X + i * mPixmapPixelStep , globalUserVariable->gridYPos[10]));
            }
//            mPixmap_draw_point[t][i]= QPointF( DRAW_GRID_START_X + 1 + i * mPixmapPixelStep , mHeight-  SA_BOTTOMDIS);
        }
    }

    return;
}

/**
 * @brief sa_UIRefresh_Control::refreshInfo
 * @param painter
 * @param pos
 * @param info
 * @author Johnson
 */
void sa_UIRefresh_Control::refreshInfo(QPainter* painter,qint32 pos,QString info)
{
    QFont mFont;
    mFont.setWeight(QFont::Bold);
    mFont.setFamily("Arial");
    mFont.setPixelSize(13);
    painter->setFont(mFont);
    qint32 colorMode = globalUserVariable->gDisplayMode;
    QColor fontColor = infoFontColor[colorMode];
    painter->setPen(fontColor);

    switch (pos) {
    case SA_TOP_LEFT:
        painter->drawText(globalUserVariable->gridXPos[0], 8, SA_WORDWITH, SA_WORDHEIGHT, Qt::AlignLeft, info);
        break;
    case SA_TOP_LEFT_SEC:
        painter->drawText(globalUserVariable->gridXPos[0], 23, SA_WORDWITH, SA_WORDHEIGHT, Qt::AlignLeft, info);
        break;
    case SA_TOP_CENTER:
        mFont.setPixelSize(14);
        painter->setFont(mFont);
        if(globalUserVariable->currentMode != SA_SPAN_MODE)
        {
            painter->drawText(globalUserVariable->gridXPos[5]-SA_WORDWITH/2, 18, SA_WORDWITH, 16, Qt::AlignCenter, info);
        }
        else
        {
            if(globalUserVariable->gGateViewStatus == SA_GATE_VIEW_OPEN)
            {
                painter->drawText(globalUserVariable->gridXPos[5]-SA_WORDWITH/2, 18, SA_WORDWITH, 16, Qt::AlignCenter, tr("Gate View"));
            }
            else
            {
                painter->drawText(globalUserVariable->gridXPos[5]-SA_WORDWITH/2, 18, SA_WORDWITH, 16, Qt::AlignCenter, info);
            }
        }
        break;
    case SA_TOP_RIGHT:
        painter->drawText(globalUserVariable->gridXPos[10]-SA_WORDWITH, 8, SA_WORDWITH, 15, Qt::AlignRight, info);
        break;
    case SA_TOP_RIGHT_SEC:
        painter->drawText(globalUserVariable->gridXPos[10]-SA_WORDWITH, 23, SA_WORDWITH, 15, Qt::AlignRight, info);
        break;
    case SA_BOTTOM_LEFT:
        painter->drawText(globalUserVariable->gridXPos[0], globalUserVariable->gridYPos[10] + 2, SA_WORDWITH, 15, Qt::AlignLeft|Qt::AlignTop, info);
        break;
    case SA_BOTTOM_LEFT_SEC:
        painter->drawText(globalUserVariable->gridXPos[0], globalUserVariable->gridYPos[10] + 17, SA_WORDWITH, 15, Qt::AlignLeft, info);
        break;
    case SA_BOTTOM_CENTER:
        mFont.setPixelSize(14);
        painter->setFont(mFont);
        painter->drawText(globalUserVariable->gridXPos[5]-SA_WORDWITH/2, globalUserVariable->gridYPos[10] +7, SA_WORDWITH, 16, Qt::AlignCenter, info);
        break;
    case SA_BOTTOM_RIGHT:
        painter->drawText(globalUserVariable->gridXPos[10]-SA_WORDWITH, globalUserVariable->gridYPos[10] +2,SA_WORDWITH,15, Qt::AlignRight|Qt::AlignTop, info);
        break;
    case SA_BOTTOM_RIGHT_SEC:
        painter->drawText(globalUserVariable->gridXPos[10]-SA_WORDWITH, globalUserVariable->gridYPos[10] +17,SA_WORDWITH,15, Qt::AlignRight, info);
        break;
    }
}

void sa_UIRefresh_Control::judgeSpecEMTestResult()
{
    qint32 freqCnt;
    if(SA_SPECEM_DEFAULT == globalUserVariable->gSpecEMMaskType){
        freqCnt = SA_SPECEM_FREQ_CNT;
    }else
    {
        freqCnt = SA_SPECEM_FREQ_CNT_5GNR;
    }
    qint32 lowerStart,upperStart,lowerStop,upperStop;
    qreal freq,halfspanFreq,setpFreq;
    qint32 startIndex[2 * freqCnt],stopIndex[2 * freqCnt];

    halfspanFreq= globalUserVariable->gSpanFreq/2;
    setpFreq = 2 * halfspanFreq/(NUM_SWEEP_POINT-1);
    //Calculate the start and end  position
    for(qint32 i = 0;i < freqCnt;i++)
    {
        freq = halfspanFreq  - globalUserVariable->gSpecEMData[i].stop;
        lowerStart = freq / setpFreq;
        if(lowerStart*setpFreq != freq)
        {
            lowerStart = lowerStart + 1;
        }
        freq = halfspanFreq  - globalUserVariable->gSpecEMData[i].start;
        lowerStop = freq / setpFreq;
        if(lowerStop * setpFreq == freq)
        {
            lowerStop = lowerStop - 1;
        }
        freq = halfspanFreq  + globalUserVariable->gSpecEMData[i].start;
        upperStart = freq / setpFreq;
        if(upperStart*setpFreq != freq)
        {
            upperStart = upperStart + 1;
        }
        freq = halfspanFreq  + globalUserVariable->gSpecEMData[i].stop;
        upperStop = freq / setpFreq;
        if(upperStop * setpFreq == freq)
        {
            upperStop = upperStop - 1;
        }
        startIndex[i] = lowerStart;
        stopIndex[i]  = lowerStop;
        startIndex[freqCnt+i] = upperStart;
        stopIndex[freqCnt+i]  = upperStop;
    }
     for(qint32 i = 0;i<2*freqCnt;i++)
    {
        globalUserVariable->gSpecEMTestResult[i] = SA_PASS;
        if(i<freqCnt)
        {
            if(globalUserVariable->gSpecEMViewStatus[i] == SA_OFF) continue;
        }else
        {
            if(globalUserVariable->gSpecEMViewStatus[i-freqCnt] == SA_OFF) continue;
        }

        for(qint32 j = startIndex[i];j < stopIndex[i];j++)
        {
            if(mPixmap_draw_point[globalUserVariable->gTraceSelect][j].y() < mSpecEMAbsLimit[j].y())
            {
                globalUserVariable->gSpecEMTestResult[i] = SA_FAIL;
                break;
            }
        }
    }
    return;
}

/**
 * @brief sa_UIRefresh_Control::refreshScalePixmap()
 * @param w[qreal]
 * @param h[qreal]
 * @author Tony
 */
void sa_UIRefresh_Control::refreshScalePixmap(qreal wScale,qreal hScale)
{

    qreal w = globalUserVariable->mDrawWidth;
    qreal h = globalUserVariable->mDrawHeight;
    QPainter painter(&mPixmap);
    if(firstTouch)
    {
        qint32 colorMode = globalUserVariable->gDisplayMode;
        QColor mBackgroundColor = BackgroundColor[colorMode];
        QPainter painterB(&backPixmap);
        refreshDrawPoint();
        backPixmap.fill(mBackgroundColor);
        forePixmap.fill(Qt::transparent);

        QPainter painterF(&forePixmap);
        drawGrid(&painterB);
        drawMeasureRect(&painterB);
        /*Tony 0729 zero span no limit*/
        if(globalUserVariable->gZeroSpanAction || !bDrawLimitCurve)
            drawCurves(&painterF);
        else
            drawLimitCurves(&painterF);

        firstTouch = 0;
    }

    qreal realWidth  = w*wScale;
    qreal realHeight = h*hScale;
    qreal drawWidth  = w - SA_LEFTDIS - SA_RIGHTDIS;
    qreal drawHeight = h - SA_TOPDIS - SA_BOTTOMDIS-4;
    QRect mDrawRect,mPixRect;
    if(wScale >= 1 && hScale >= 1)
    {
        mDrawRect.setRect(SA_LEFTDIS,SA_TOPDIS-2,drawWidth,drawHeight);
        mPixRect.setRect(SA_LEFTDIS+drawWidth*0.5*(wScale -1),SA_TOPDIS+drawHeight*0.5*(hScale -1),drawWidth,drawHeight);
    }else if(wScale < 1 && hScale < 1)
    {
        mDrawRect.setRect((SA_LEFTDIS+drawWidth*0.5)*(1 - wScale),(SA_TOPDIS+drawHeight*0.5)*(1 - hScale),realWidth,realHeight);
        mPixRect.setRect(0,0,realWidth,realHeight);
    }else if(wScale >= 1 && hScale < 1)
    {
        mDrawRect.setRect(SA_LEFTDIS,(SA_TOPDIS+drawHeight*0.5)*(1 - hScale),drawWidth,realHeight);
        mPixRect.setRect(SA_LEFTDIS+drawWidth*0.5*(wScale -1),0,drawWidth,realHeight);
    }else if(wScale < 1 && hScale >= 1)
    {
        mDrawRect.setRect((SA_LEFTDIS+drawWidth*0.5)*(1 - wScale),SA_TOPDIS-2,realWidth,drawHeight);
        mPixRect.setRect(0,SA_TOPDIS+drawHeight*0.5*(hScale -1),realWidth,drawHeight);
    }

    painter.drawPixmap(0,0,backPixmap.width(),backPixmap.height(),backPixmap);
    //painter.drawPixmap(QRect(BIT_GRID_START_X,0,width() - RIGHTDIS - LEFTDIS - HALFLINEREEOR,height()),gDoubleClickPixMap,QRect(((DrawXScale - 1) /(2 * DrawXScale)) * width(),0,(1 / DrawXScale) * width(),height()));

    painter.drawPixmap(mDrawRect,forePixmap.scaled(realWidth,realHeight),mPixRect);
}

/**
 * @brief sa_UIRefresh_Control::refreshTranslationPixmap()
 * @param xChange[qreal]
 * @param yChange[qreal]
 * @author Tony
 */
void sa_UIRefresh_Control::refreshTranslationPixmap(qreal xChange,qreal yChange)
{
    qreal w = globalUserVariable->mDrawWidth;
    qreal h = globalUserVariable->mDrawHeight;
    QPainter painter(&mPixmap);
    if(firstTouch)
    {
        qint32 colorMode = globalUserVariable->gDisplayMode;
        QColor mBackgroundColor = BackgroundColor[colorMode];
        QPainter painterB(&backPixmap);
        refreshDrawPoint();
        backPixmap.fill(mBackgroundColor);
        forePixmap.fill(Qt::transparent);

        QPainter painterF(&forePixmap);
        drawGrid(&painterB);
        drawMeasureRect(&painterB);
        /*Tony 0729 zero span no limit*/
        if(globalUserVariable->gZeroSpanAction || !bDrawLimitCurve)
            drawCurves(&painterF);
        else
            drawLimitCurves(&painterF);

        firstTouch = 0;
    }
    qreal drawWidth  = w - SA_LEFTDIS - SA_RIGHTDIS;
    qreal drawHeight = h - SA_TOPDIS - SA_BOTTOMDIS;
    QRect mDrawRect,mPixRect;
    if(xChange >= 0 && yChange >=0)
    {
        mDrawRect.setRect(SA_LEFTDIS+xChange,SA_TOPDIS+yChange,drawWidth-xChange,drawHeight-yChange);
        mPixRect.setRect(SA_LEFTDIS,SA_TOPDIS,drawWidth-xChange,drawHeight-yChange);
    }else if(xChange < 0 && yChange < 0)
    {
        mDrawRect.setRect(SA_LEFTDIS,SA_TOPDIS,drawWidth+xChange,drawHeight+yChange);
        mPixRect.setRect(SA_LEFTDIS-xChange,SA_TOPDIS-yChange,drawWidth+xChange,drawHeight+yChange);
    }else if(xChange >=0 && yChange < 0)
    {
        mDrawRect.setRect(SA_LEFTDIS+xChange,SA_TOPDIS,drawWidth-xChange,drawHeight+yChange);
        mPixRect.setRect(SA_LEFTDIS,SA_TOPDIS-yChange,drawWidth-xChange,drawHeight+yChange);
    }else if(xChange < 0 && yChange >=0)
    {
        mDrawRect.setRect(SA_LEFTDIS,SA_TOPDIS+yChange,drawWidth+xChange,drawHeight-yChange);
        mPixRect.setRect(SA_LEFTDIS-xChange,SA_TOPDIS,drawWidth+xChange,drawHeight-yChange);
    }

    painter.drawPixmap(0,0,backPixmap.width(),backPixmap.height(),backPixmap);
    painter.drawPixmap(mDrawRect,forePixmap,mPixRect);
}

/**
 * @brief sa_UIRefresh_Control::IsMarkerPoint
 * @param x
 * @param y
 * @note
 * @author Tony
 */
bool sa_UIRefresh_Control::IsMarkerPoint(qint32 x, qint32 y)
{
    calculatorXPos = (x - DRAW_GRID_START_X) / mPixmapPixelStep;
    const int marginXgab = 10;
    int markerPos = 0;

    if ((x > sweepRangeRect.x()) && (x  < sweepRangeRect.right()))
    {
        if ((y > sweepRangeRect.y())&& (y < (sweepRangeRect.bottom()/* - markerSpace*/) ))
        {
            for (int i = 0; i < MARKER_TOTAL_CNT; i++)
            {
                if (globalUserVariable->gMarkerView[i] == SA_ON )
                {
                    if (globalUserVariable->gMarkerType[i] == REF)
                      markerPos = (int) (globalUserVariable->gMarkerRefPos[i]);
                    else
                      markerPos = (int) (globalUserVariable->gMarkerDeltaPos[i]);

                    if ((calculatorXPos >= (markerPos - marginXgab)) && (calculatorXPos <= (markerPos + marginXgab)))
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

/**
 * @brief sa_UIRefresh_Control::IsMarkerPoint
 * @param x
 * @param y
 * @note
 * @author Tony
 */
bool sa_UIRefresh_Control::IsPixmapRecPoint(qint32 x, qint32 y)
{
    if ((x > sweepRangeRect.x()) && (x  < sweepRangeRect.right()))
    {
        if ((y > sweepRangeRect.y())&& (y < (sweepRangeRect.bottom()/* - markerSpace*/) ))
        {
            return true;
        }
    }
    return false;
}

#ifdef SAMPLE_LIMIT
/**
 * @brief sa_UIRefresh_Control::judgeSampleLimitTestResult
 * @note  judge the test result of limit
 * @author Tony
 */
void sa_UIRefresh_Control::judgeSampleLimitTestResult()
{
    globalUserLimit->gLowerLimitTestResult = SA_PASS;
    globalUserLimit->gUpperLimitTestResult = SA_PASS;
    globalUserLimit->gATLdBcLimitTestResult = SA_PASS;
    //Johnson 200210
    #if 0
    qint32 upperCheck = 0,lowerCheck = 0;
    for(qint32 i = 0;i< NUM_SWEEP_POINT;i++)
    {
        if(!lowerCheck && globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i] < globalUserLimit->gLowerLimit)
        {
            lowerCheck = 1;
            globalUserLimit->gLowerLimitTestResult = SA_FAIL;
        }

        if(!upperCheck &&  globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i] > globalUserLimit->gUpperLimit)
        {
            upperCheck = 1;
            globalUserLimit->gUpperLimitTestResult = SA_FAIL;
        }

        if(upperCheck && lowerCheck) return;
    }
    #else
    if(globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE)
    {
        if(globalUserLimit->gUpperLimit < globalUserVariable->dPowerValue)
            globalUserLimit->gUpperLimitTestResult = SA_FAIL;
        if(globalUserLimit->gLowerLimit < globalUserVariable->dPSD)
            globalUserLimit->gLowerLimitTestResult = SA_FAIL;
    }
    else if(globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE)
    {
        if(globalUserLimit->gUpperLimit < globalUserVariable->uOccupiedBW)
            globalUserLimit->gUpperLimitTestResult = SA_FAIL;
    }
    else if(globalUserVariable->currentMode == SA_ACP_MEASURE_MODE)
    {
#if !EXCHANGE_ACPMULTIACP
        if(globalUserLimit->gUpperLimit < globalUserVariable->dPowerValue_ACPM)
            globalUserLimit->gUpperLimitTestResult = SA_FAIL;
        if(globalUserLimit->gLowerLimit < globalUserVariable->dPowerValue_ACPL - globalUserVariable->dPowerValue_ACPM ||
                globalUserLimit->gLowerLimit < globalUserVariable->dPowerValue_ACPR - globalUserVariable->dPowerValue_ACPM)
             globalUserLimit->gLowerLimitTestResult = SA_FAIL;
#else
        if(globalUserLimit->gUpperLimit < globalUserVariable->dLowest_MainCh_Power ||
           globalUserLimit->gUpperLimit < globalUserVariable->dHighest_MainCh_Power)
            globalUserLimit->gUpperLimitTestResult = SA_FAIL;
        if(globalUserLimit->gLowerLimit < globalUserVariable->dLowest_ADJCh_Power - globalUserVariable->dLowest_MainCh_Power ||
                globalUserLimit->gLowerLimit < globalUserVariable->dLowest_ALTCh_Power - globalUserVariable->dHighest_MainCh_Power)
             globalUserLimit->gLowerLimitTestResult = SA_FAIL;
        if(globalUserLimit->gATLdBcLimit < globalUserVariable->dHighest_ADJCh_Power - globalUserVariable->dHighest_MainCh_Power ||
                globalUserLimit->gATLdBcLimit < globalUserVariable->dHighest_ALTCh_Power - globalUserVariable->dHighest_MainCh_Power)
             globalUserLimit->gATLdBcLimitTestResult = SA_FAIL;
#endif
    }
    else if(globalUserVariable->currentMode == SA_MULTI_ACP_MODE)
    {
        if(globalUserLimit->gUpperLimit < globalUserVariable->dPowerValue_MultiACPM)
            globalUserLimit->gUpperLimitTestResult = SA_FAIL;
        if(globalUserLimit->gLowerLimit < globalUserVariable->dPowerValue_MultiACPL - globalUserVariable->dPowerValue_MultiACPM ||
                globalUserLimit->gLowerLimit < globalUserVariable->dPowerValue_MultiACPR - globalUserVariable->dPowerValue_MultiACPM)
             globalUserLimit->gLowerLimitTestResult = SA_FAIL;
        if(globalUserLimit->gATLdBcLimit < globalUserVariable->dPowerValue_MultiACPFL - globalUserVariable->dPowerValue_MultiACPM ||
                globalUserLimit->gATLdBcLimit < globalUserVariable->dPowerValue_MultiACPFR - globalUserVariable->dPowerValue_MultiACPM)
             globalUserLimit->gATLdBcLimitTestResult = SA_FAIL;
    }
    else
    {
        qint32 upperCheck = 0,lowerCheck = 0;
        for(qint32 i = 0;i< NUM_SWEEP_POINT;i++)
        {
            if(!lowerCheck && globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i] < globalUserLimit->gLowerLimit)
            {
                lowerCheck = 1;
                globalUserLimit->gLowerLimitTestResult = SA_FAIL;
            }

            if(!upperCheck &&  globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i] > globalUserLimit->gUpperLimit)
            {
                upperCheck = 1;
                globalUserLimit->gUpperLimitTestResult = SA_FAIL;
            }

            if(upperCheck && lowerCheck) return;
        }
    }
    #endif
    return;
}

/**
 * @brief sa_UIRefresh_Control::drawSampleLimit
 * @param painter
 */
void sa_UIRefresh_Control::drawSampleLimit(QPainter *painter)
{
    QPen oldPen = painter->pen();
    QPen mPen(QColor(115,210,22));
    mPen.setWidth(2);
    painter->setPen(mPen);
    //Johnson 200210
    if(globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE/* || globalUserVariable->currentMode == SA_ACP_MEASURE_MODE*/)
    {
        if(globalUserLimit->gLimitTest == SA_ON)
        {
            if(globalUserLimit->gUpperLimitStatus || globalUserLimit->gLowerLimitStatus)
            {
                if(globalUserLimit->gUpperLimitStatus && globalUserLimit->gLowerLimitStatus)
                {
                    if (globalUserLimit->gUpperLimitTestResult == SA_PASS && globalUserLimit->gLowerLimitTestResult == SA_PASS)
                    {
                        painter->setPen(Qt::green);
                        painter->setFont(QFont("Arial", 11));
                        painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "PASS");
                    }else
                    {
                        painter->setPen(Qt::red);
                        painter->setFont(QFont("Arial", 11));
                        painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "FAIL");
                    }
                }
                else if(!globalUserLimit->gUpperLimitStatus && globalUserLimit->gLowerLimitStatus)
                {
                    if (globalUserLimit->gLowerLimitTestResult == SA_PASS)
                    {
                        painter->setPen(Qt::green);
                        painter->setFont(QFont("Arial", 11));
                        painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "PASS");
                    }else
                    {
                        painter->setPen(Qt::red);
                        painter->setFont(QFont("Arial", 11));
                        painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "FAIL");
                    }
                }
                else if(globalUserLimit->gUpperLimitStatus && !globalUserLimit->gLowerLimitStatus)
                {
                    if (globalUserLimit->gUpperLimitTestResult == SA_PASS)
                    {
                        painter->setPen(Qt::green);
                        painter->setFont(QFont("Arial", 11));
                        painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "PASS");
                    }else
                    {
                        painter->setPen(Qt::red);
                        painter->setFont(QFont("Arial", 11));
                        painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "FAIL");
                    }
                }
            }
        }
    }
    else if(globalUserVariable->currentMode == SA_OCCUPIED_BW_MEASURE_MODE)
    {
        if(globalUserLimit->gLimitTest == SA_ON && globalUserLimit->gUpperLimitStatus)
        {
            if (globalUserLimit->gUpperLimitTestResult == SA_FAIL)
            {
                painter->setPen(Qt::red);
                painter->setFont(QFont("Arial", 11));
                painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "FAIL");
            }else
            {
                painter->setPen(Qt::green);
                painter->setFont(QFont("Arial", 11));
                painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "PASS");
            }
        }
    }
    else if(globalUserVariable->currentMode == SA_MULTI_ACP_MODE || globalUserVariable->currentMode == SA_ACP_MEASURE_MODE)
    {
        if(globalUserLimit->gLimitTest == SA_ON)
        {
            if(globalUserLimit->gUpperLimitStatus || globalUserLimit->gLowerLimitStatus || globalUserLimit->gATLdBcLimitStatus)
            {
                if(globalUserLimit->gUpperLimitStatus && globalUserLimit->gLowerLimitStatus && globalUserLimit->gATLdBcLimitStatus)
                {
                    if(globalUserLimit->gUpperLimitTestResult == SA_PASS && globalUserLimit->gLowerLimitTestResult == SA_PASS
                            && globalUserLimit->gATLdBcLimitTestResult == SA_PASS)
                    {
                        painter->setPen(Qt::green);
                        painter->setFont(QFont("Arial", 11));
                        painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "PASS");
                    }
                    else
                    {
                        painter->setPen(Qt::red);
                        painter->setFont(QFont("Arial", 11));
                        painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "FAIL");
                    }
                }
                else if(!globalUserLimit->gUpperLimitStatus && globalUserLimit->gLowerLimitStatus && globalUserLimit->gATLdBcLimitStatus)
                {
                    if(globalUserLimit->gLowerLimitTestResult == SA_PASS && globalUserLimit->gATLdBcLimitTestResult == SA_PASS)
                    {
                        painter->setPen(Qt::green);
                        painter->setFont(QFont("Arial", 11));
                        painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "PASS");
                    }
                    else
                    {
                        painter->setPen(Qt::red);
                        painter->setFont(QFont("Arial", 11));
                        painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "FAIL");
                    }
                }
                else if(globalUserLimit->gUpperLimitStatus && !globalUserLimit->gLowerLimitStatus && globalUserLimit->gATLdBcLimitStatus)
                {
                    if(globalUserLimit->gUpperLimitTestResult == SA_PASS && globalUserLimit->gATLdBcLimitTestResult == SA_PASS)
                    {
                        painter->setPen(Qt::green);
                        painter->setFont(QFont("Arial", 11));
                        painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "PASS");
                    }
                    else
                    {
                        painter->setPen(Qt::red);
                        painter->setFont(QFont("Arial", 11));
                        painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "FAIL");
                    }
                }
                else if(globalUserLimit->gUpperLimitStatus && globalUserLimit->gLowerLimitStatus && !globalUserLimit->gATLdBcLimitStatus)
                {
                    if(globalUserLimit->gUpperLimitTestResult == SA_PASS && globalUserLimit->gLowerLimitTestResult == SA_PASS)
                    {
                        painter->setPen(Qt::green);
                        painter->setFont(QFont("Arial", 11));
                        painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "PASS");
                    }
                    else
                    {
                        painter->setPen(Qt::red);
                        painter->setFont(QFont("Arial", 11));
                        painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "FAIL");
                    }
                }
                else if(!globalUserLimit->gUpperLimitStatus && !globalUserLimit->gLowerLimitStatus && globalUserLimit->gATLdBcLimitStatus)
                {
                    if(globalUserLimit->gATLdBcLimitTestResult == SA_PASS)
                    {
                        painter->setPen(Qt::green);
                        painter->setFont(QFont("Arial", 11));
                        painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "PASS");
                    }
                    else
                    {
                        painter->setPen(Qt::red);
                        painter->setFont(QFont("Arial", 11));
                        painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "FAIL");
                    }
                }
                else if(!globalUserLimit->gUpperLimitStatus && globalUserLimit->gLowerLimitStatus && !globalUserLimit->gATLdBcLimitStatus)
                {
                    if(globalUserLimit->gLowerLimitTestResult == SA_PASS)
                    {
                        painter->setPen(Qt::green);
                        painter->setFont(QFont("Arial", 11));
                        painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "PASS");
                    }
                    else
                    {
                        painter->setPen(Qt::red);
                        painter->setFont(QFont("Arial", 11));
                        painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "FAIL");
                    }
                }
                else if(globalUserLimit->gUpperLimitStatus && !globalUserLimit->gLowerLimitStatus && !globalUserLimit->gATLdBcLimitStatus)
                {
                    if(globalUserLimit->gUpperLimitTestResult == SA_PASS)
                    {
                        painter->setPen(Qt::green);
                        painter->setFont(QFont("Arial", 11));
                        painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "PASS");
                    }
                    else
                    {
                        painter->setPen(Qt::red);
                        painter->setFont(QFont("Arial", 11));
                        painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "FAIL");
                    }
                }
            }
        }
    }
    else
    {
        qint32 upperTest = SA_PASS,lowerTest = SA_PASS;
        qint32 x1,x2,y1,y2;
        if(globalUserLimit->gUpperLimitStatus)
        {
            y1 = yaxis_cal(globalUserLimit->gUpperLimit) + DRAW_GRID_START_Y;
            y2 = y1;
            x1 = globalUserVariable->gridXPos[0];
            x2 = globalUserVariable->gridXPos[10];
            painter->drawLine(x1,y1,x2,y2);
            upperTest = globalUserLimit->gUpperLimitTestResult;
        }

        if(globalUserLimit->gLowerLimitStatus)
        {
            y1 = yaxis_cal(globalUserLimit->gLowerLimit) + DRAW_GRID_START_Y;
            y2 = y1;
            x1 = globalUserVariable->gridXPos[0];
            x2 = globalUserVariable->gridXPos[10];
            painter->drawLine(x1,y1,x2,y2);
            lowerTest = globalUserLimit->gLowerLimitTestResult;
        }

        if(globalUserLimit->gLimitTest == SA_ON)
        {
            if (upperTest == SA_FAIL || lowerTest  == SA_FAIL)
            {
                painter->setPen(Qt::red);
                painter->setFont(QFont("Arial", 11));
                painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "FAIL");
            }else
            {
                painter->setPen(Qt::green);
                painter->setFont(QFont("Arial", 11));
                painter->drawText(DRAW_GRID_START_X + 50, DRAW_GRID_START_Y + 20, 200, 20, Qt::AlignLeft, "PASS");
            }
        }
    }

    painter->setPen(oldPen);
    return;
}
#endif
