#include "bitview.h"
#include <QStylePainter>
#include <sys/time.h>
#include "math.h"
#include "stdio.h"
#include <QMouseEvent>
#include <QHeaderView>
#include <QGraphicsOpacityEffect>
#include <QDebug>
/*
 *Designed Ideas:
 *Under the case of fixed size
 *  the first layer is used for dynamic render for sigs and other dynamic infos
 *  the sec layer is used for static render such as back grid lines and so on
 *When size changed
 *  the first and sec layers are both render again but when first layer is designed  for specgram,
 *  the sec layer will be render and the first layer will be scaled other than render again
 *So,for save power i design to use two layers two buffers to achieve the plugin.
*/
qint32 markercnt;
QRegExp DelZeroRx;
BitView::BitView(QWidget *parent) :
    QWidget(parent),
    gplugindex(0),
    gmsgsourceindex(0)
{
    innerIniOnece();
}

BitView::BitView(qint32 plugindex,qint32 curwindowindex, QWidget *parent):
    QWidget(parent),
    gplugindex(plugindex),
    gmsgsourceindex(curwindowindex)
{
    memset(&gfreqinfo,0,sizeof(gfreqinfo));
    innerIniOnece();
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(on_mouseclick()));
}

/**
 * @brief BitView::innerIniOnece
 * @note 创建分析视图
 */
void BitView::innerIniOnece()
{
    gctrlmana = new ctrlmana(this);
//    gctrlmana->gLimitSelect = 0;
//    memset(&gctrlmana->gLimitPointCnt,0,sizeof(gctrlmana->gLimitPointCnt));
    mlimitTableWidget = new BVTableWidget(&gfreqinfo,gctrlmana,this);
//    connect(mlimitTableWidget,SIGNAL(tabelClicked()),this,SLOT(on_tableClicked()));
    mlimitTableWidget->setColumnCount(2);
    mlimitTableWidget->hide();
    mlimitTableWidget->horizontalHeader()->setStretchLastSection(true);


//    QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
//    mlimitTableWidget->setGraphicsEffect(opacityEffect);
//    opacityEffect->setOpacity(BIT_TABLEWIDGET_OPACITY);
//    this->setAttribute(Qt::WA_AcceptTouchEvents,true);
#ifdef BITVIEW_F239
    setAttribute(Qt::WA_AcceptTouchEvents);
#endif
    QStringList header;
    header<<tr("Frequency(MHz)")<<tr("Amplitude(dBm)");
    mlimitTableWidget->setHorizontalHeaderLabels(header);

    gusedsize.grefValue = -10.0;
    gusedsize.gdivValue = 10.0;
    gusedsize.goffsetValue = 0.0;
    gusedsize.gpicwidth = 10.0;
    gusedsize.gpicheight = 10.0;

    //this part should decided later
    gwordset.gtscstr = "Amp vs. Freq";
    gwordset.gbfl = 3000.0;
    gwordset.gbfr = 9000.0;
    gwordset.gbsl = 100.0;
    gwordset.gbsr = 0.33;

    gsystemstate.windowtype = 0;

    gpixmap = QPixmap(10,10);
    gpixmap.fill(mPenColor.background);
    gsigrendermap = QPixmap(10,10);
    gsigrendermap.fill(Qt::transparent);
    gbitpen = QPen(Qt::white);
    pthread_mutex_init(&glockobj,NULL);
    connect(this,SIGNAL(emitRefleshsig()),this,SLOT(graphRefleshslot()));
    connect(this,SIGNAL(emitFallSig()),this,SLOT(graphFallslot()));
    connect(this,SIGNAL(emitrefleshDensity()),this,SLOT(densityRefslot()));
//    connect(this,SIGNAL(emitRefleshDensity()),this,SLOT(DensityRefslot()));

//    pixmapnew = QPixmap(10,10);
//    pixmapnew.fill(mPenColor.background);
    gctrlmana->gtraceIndex = 0;
    mCacheDataStartPos = 0;
    mCacheRealNum = 0;

    mResizeMark = 0;

    pixmapnewSmall = QPixmap(532,315);
    pixmapnewSmall.fill(mPenColor.background);

    pixmapnewBig = QPixmap(1064,315);
    pixmapnewBig.fill(mPenColor.background);
    //Tony 1026.Marker mouse
    marker_mouse_move_pos = BIT_NOT_MARKER_MOUSE_CLICK;
    CenterPartRect ={BIT_GRID_START_X,BIT_GRID_START_Y,
                     this->width()-LEFTDIS-RIGHTDIS-LINEREEOR,
                     this->height()-TOPDIS-
                     (BOTTOMDIS + gsystemstate.windowtype * markerTabelVisiable * BIT_MARKER_TABLE_HEIGHT)
                     - LINEREEOR};
    //Tony 1105
    for(qint32 i=0;i<BIT_MARKER_TOTAL_CNT;i++)
    {
        gctrlmana->gMarkerView[i]=BITOFF;
        gctrlmana->gMarkerType[i]=BIT_NORMAL;
        gctrlmana->gMarkerNormalIndex[i] = (NOWTRACENUM -1)/2;
        gctrlmana->gMarkerDeltaIndex[i] = (NOWTRACENUM -1)/2;
    }

    //Tony 1105
    markertotalcnt = 0;

    setdisplaymode(BIT_DEFAULTMODE);

    mWindowWidth = WINDOW_HALF_WIDTH;

    mCacheData = NULL;
    gAmptdUnit = BIT_DBM;
    mBitviewType = BIT_SPECTRUM;
//    mMarkerRefAmpt = 0;
    mFreqOffset = 0.;
    misFmtShow = false;
    DelZeroRx.setPattern("(\\.){0,1}0+$");
    misDoubleClicked = false;
    mFileLoadFlag = false;

#ifdef BITVIEW_F239
    Touchtimer = new QTimer(this);
    connect(Touchtimer,SIGNAL(timeout()),this,SLOT(TouchEventSlot()));
    BitXScale = 0.0;
    BitYScale = 0.0;
    DrawXScale = 0.0;
    gDoubleClickPixMap = QPixmap(10,10);
    gDoubleClickPixMap.fill(Qt::transparent);
    nFingerTouchCnt = 0;
    gWindowPos.StartXPos = 0;
    gWindowPos.StopXPos = 0;
    gWindowPos.calXPos = 0;
    gWindowPos.StartYPos = 0;
    gWindowPos.StopYPos = 0;
    gWindowPos.calYPos = 0;
    gWindowPos.CalCenterFreq = 0.0;
    gWindowPos.calRefLevel = 0.0;
    misBitCenFreqChanged = false;
    misBitScaleChanged = false;
    misTouchEventDone = false;
    misBitReflevelChanged = false;
#endif
    clickCnt = 0;
    mDensityArrayStartPos = 0;
    mDensityArrayTotalNum = 0;
    mIsDensityArrayReset = false;
}

BitView::~BitView()
{
    delete mlimitTableWidget;
    pthread_mutex_destroy(&glockobj);
}

/**
 * @brief BitView::paintEvent
 * @param event
 * @note 刷新界面  绘制各层图形显示
 */
void BitView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QStylePainter painter(this);
    painter.drawPixmap(0, 0, gpixmap);
#ifdef BITVIEW_F239
    if(misBitScaleChanged)
    {
        if(BitXScale >= 1)
        {
            painter.drawPixmap(QRect(BIT_GRID_START_X,0,width() - RIGHTDIS - LEFTDIS - HALFLINEREEOR,height()),gDoubleClickPixMap,QRect(((DrawXScale - 1) /(2 * DrawXScale)) * width(),0,(1 / DrawXScale) * width(),height()));
        }
        else
        {
            painter.drawPixmap(QRect((1 - DrawXScale) * width() + BIT_GRID_START_X, 0,width() - 2 * (1 - DrawXScale) * width(),height()),gDoubleClickPixMap);
        }
        return;
    }
    if(misBitReflevelChanged)
    {
//        renderTagline();
        if(gWindowPos.calYPos >= 0)
        {
            painter.drawPixmap(QRect(BIT_GRID_START_X,BIT_GRID_START_Y + gWindowPos.calYPos,width(),height() - BIT_GRID_START_Y - BOTTOMDIS - gWindowPos.calYPos),gDoubleClickPixMap,QRect(0,BIT_GRID_START_Y,width(),height() - gWindowPos.calYPos));
        }
        else
        {
            painter.drawPixmap(QRect(BIT_GRID_START_X,BIT_GRID_START_Y,width(),height() - BIT_GRID_START_Y - BOTTOMDIS),gDoubleClickPixMap,QRect(0,BIT_GRID_START_Y - gWindowPos.calYPos,width(),height()));
        }
        return;
    }
    if(misBitCenFreqChanged)
    {
//        renderTagline();
        if(gWindowPos.calXPos >= 0)
        {
            painter.drawPixmap(QRect(BIT_GRID_START_X + gWindowPos.calXPos,BIT_GRID_START_Y,width() - RIGHTDIS - LEFTDIS - HALFLINEREEOR - gWindowPos.calXPos,height()),gDoubleClickPixMap,QRect(0,BIT_GRID_START_Y,width() - gWindowPos.calXPos,height()));
        }
        else
        {
            painter.drawPixmap(QRect(BIT_GRID_START_X,BIT_GRID_START_Y,width()  + gWindowPos.calXPos - RIGHTDIS - LEFTDIS - HALFLINEREEOR,height()),gDoubleClickPixMap,QRect(-gWindowPos.calXPos,BIT_GRID_START_Y,width() + gWindowPos.calXPos,height()));
        }
        return;
    }
#endif
    painter.drawPixmap(0, 0, gsigrendermap);
//    if(mBitviewType != BIT_DENSITY)
//    {
//        painter.drawPixmap(0, 0, gsigrendermap);
//    }
//    else
//    {
//        painter.drawPixmap(0, 0, gsigrendermap);
////        painter.drawImage(CenterPartRect.left(),CenterPartRect.top(),imageFromData);
//    }
//    ////the typical val is about 300us
    return;
}

/**
 * @brief BitView::resizeEvent
 * @param event
 * @note 调整界面大小尺寸
 */
void BitView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    gpixmap = gpixmap.scaled(width(),height(),
                             Qt::IgnoreAspectRatio,
                             Qt::FastTransformation);
    //UNDO:attention when specgram the scaled size is differ
    gsigrendermap = gsigrendermap.scaled(width(),height(),
                                         Qt::IgnoreAspectRatio,
                                         Qt::FastTransformation);

    calculationPainterArea();
    if(mBitviewType == BIT_SPECTROGRAM)
    {
//        SetSpectrogramSmallPixRect(width(),height());
//        SetSpectrogramBigPixRect(width(),height());
        RecalSpectrogramBigPointX();
        RecalSpectrogramSmallPointX();
    }
    qreal mdeta = 0.1 * 10 *
        (gusedsize.gpicwidth - 2 * LINEREEOR)
        / (gbitbuffer.gtracenum - 1);
    quint32 i = 0;
    for(i = 0;i < gbitbuffer.gtracenum;i++)
    {
        gbitbuffer.drawpointsX[i] = BIT_GRID_START_X + i * mdeta;
    }
    mResizeMark = 1;
    if(misFmtShow)
    {
        FmtXAxisCalculatorFunc(
              gctrlmana->gFMTFreq,gctrlmana->gFmtPointsNum);
        FmtYAxisCalculatorFunc
            (gctrlmana->gFMTAmplitude,gctrlmana->gFmtPointsNum);
        refreshFmtDrawData(gctrlmana->gFmtPointsNum);
    }
    //static layer
    refleshsecLayer();
    //dynamic layer,for pause convient
    if(mBitviewType != BIT_SPECTROGRAM)
    {
        refleshfirLayer();
    }
#ifdef BITVIEW_F239
    gDoubleClickPixMap = gDoubleClickPixMap.scaled(width(),height(),Qt::IgnoreAspectRatio,Qt::FastTransformation);
#endif
//    mDensityArrayStartPos = 0;
//    mDensityArrayTotalNum = 0;
    return;
}

/**
 * @brief BitView::mousePressEvent
 * @param event paint event
 * @note Mouse press event and processing contents.
 */
void BitView::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    clickCnt ++;
    if(!timer->isActive())
    {
        timer->start(250);
    }
    //Marker
    marker_mouse_move_pos = BIT_NOT_MARKER_MOUSE_CLICK;
    qint32 calculatorXPos = findAxesPosIndex((qint32)event->x());
    qint32 markerPos = 0;
    if(mBitviewType != BIT_SPECTROGRAM)
    {
        if((qint32)(gctrlmana->gtracetype[gctrlmana->gtraceIndex]) != BIT_TRACE_OFF)
        {
            if (((qint32)event->x() >= CenterPartRect.x()) && ((qint32)event->x()  <= CenterPartRect.right()))
            {
                if ((qint32)(event->y() >CenterPartRect.y())&& ((qint32) event->y() < (CenterPartRect.bottom())))
                {
#ifdef BITVIEW_F239
                    gWindowPos.StartXPos = event->x();
                    gWindowPos.StartYPos = event->y();
#endif
                    for (qint32 i = 0; i < BIT_MARKER_TOTAL_CNT; i++)
                    {
                        if (gctrlmana->gMarkerView[i] == BITON )
                        {
                            if (gctrlmana->gMarkerType[i] == BIT_NORMAL)
                            {
                                markerPos = (qint32) (gctrlmana->gMarkerNormalIndex[i]);
                            }
                            else
                            {
                                markerPos = (qint32) (gctrlmana->gMarkerDeltaIndex[i]);
                            }
                            if ((gbitbuffer.drawpointsX[calculatorXPos] >= (gbitbuffer.drawpointsX[markerPos] - BIT_MARKER_TOUCH_WIDTH / 2) && gbitbuffer.drawpointsX[calculatorXPos] <= (gbitbuffer.drawpointsX[markerPos] + BIT_MARKER_TOUCH_WIDTH / 2)))
                            {
                                gctrlmana->gMarkerSelect = i;
                                marker_mouse_move_pos = BIT_MARKER_MOUSE_ACTION;
                                emit markerchange(i);
                                if(BIT_SINGLE == gsystemstate.runningState)
                                {
                                    refleshfirLayer();
                                    this->repaint();
                                }
                                if(gfreqinfo.gacqTime > BIT_REFRESH_TIME_MIN)
                                {
                                    refleshfirLayer();
                                    this->repaint();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        if (((qint32)event->x() >= CenterPartRect.x()) && ((qint32)event->x()  <= CenterPartRect.right()))
        {
            if ((qint32)(event->y() >CenterPartRect.y())&& ((qint32) event->y() < (CenterPartRect.bottom())))
            {
            }
        }
    }

    emit singleClicked(gplugindex);
    return;
}

void BitView::on_tableClicked()
{
//    emit singleClicked(gplugindex);
    return ;
}
/**
* Mouse move event and trigger content.
* @param[in] paint event
* @return    void
*/
void BitView::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    qint32 calculatorXPos = 0;
    qint32 calculatorYPos = 0;
    qreal markerFreq = 0;
    qreal refLevel = 0;
    if(!timer->isActive())
    {
        clickCnt = 0;
        timer->stop();
    }
    if (marker_mouse_move_pos == BIT_MARKER_MOUSE_ACTION)
    {
        if(event->x() >= BIT_GRID_START_X &&  event->x() <= (LEFTDIS + gusedsize.gpicwidth))
        {
            if (gctrlmana->gMarkerView[gctrlmana->gMarkerSelect] == BITON)
            {
                calculatorXPos = findAxesPosIndex((qint32)event->x());
                markerFreq = freqIndexToFreq(calculatorXPos);
                if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_NORMAL)
                {
                    gctrlmana->gMarkerNormalFreq[gctrlmana->gMarkerSelect] = markerFreq;
                    gctrlmana->gMarkerNormalIndex[gctrlmana->gMarkerSelect] = calculatorXPos;
                    gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = markerFreq;
                    gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] = calculatorXPos;
                }
                else
                {
                    gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = markerFreq;
                    gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] = calculatorXPos;
                }
            }
        }

        if(BIT_SINGLE == gsystemstate.runningState)
        {
            refleshfirLayer();
            this->repaint();
        }
        if(gfreqinfo.gacqTime > BIT_REFRESH_TIME_MIN)
        {
            refleshfirLayer();
            this->repaint();
        }
        emit markerMove(true);
    }
    else
    {
#ifdef BITVIEW_F239
        if(BIT_SINGLE == gsystemstate.runningState)
        {
            return;
        }
        if(mBitviewType == BIT_SPECTROGRAM)
        {
            if(event->x() >= BIT_GRID_START_X &&  event->x() <= (LEFTDIS + gusedsize.gpicwidth))
            {
                if ((qint32)(event->y() >CenterPartRect.y())&& ((qint32) event->y() < (CenterPartRect.bottom())))
                {
                }
            }
            return;
        }
        if(event->x() >= BIT_GRID_START_X &&  event->x() <= (LEFTDIS + gusedsize.gpicwidth))
        {
            if ((qint32)(event->y() >CenterPartRect.y())&& ((qint32) event->y() < (CenterPartRect.bottom())))
            {
                if(misBitScaleChanged)
                {
                    return;
                }
                if(misTouchEventDone)
                {
                    misTouchEventDone = false;
                    return;
                }
                emit suspendDraw();

                gWindowPos.StopXPos = event->x();
                gWindowPos.StopYPos = event->y();
//                gWindowPos.OrginPos =
                calculatorXPos = gWindowPos.StopXPos - gWindowPos.StartXPos;
                calculatorYPos = gWindowPos.StopYPos - gWindowPos.StartYPos;
                gWindowPos.calXPos = calculatorXPos;
                gWindowPos.calYPos = calculatorYPos;
                markerFreq = freqIndexToCenterFreq(calculatorXPos);
                gWindowPos.CalCenterFreq = markerFreq;
                refLevel = IndexToRefLevel(calculatorYPos);
                gWindowPos.calRefLevel = refLevel;
                if(misBitCenFreqChanged || misBitReflevelChanged)
                {
                    this->repaint();
                    return;
                }
                if(abs(calculatorXPos) >= abs(calculatorYPos))
                {
                    misBitCenFreqChanged = true;
                }
                else
                {
                    misBitReflevelChanged = true;
                }
                this->repaint();
        }
        }
#endif
    }
    return;
}

void BitView::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
#ifdef BITVIEW_F239
    if(misBitCenFreqChanged)
    {
        emit ChangeCenterFreq(gWindowPos.CalCenterFreq);
        misBitCenFreqChanged = false;
    }
    if(misBitReflevelChanged)
    {
        emit ChangeRefLevel(gWindowPos.calRefLevel);
        misBitReflevelChanged =false;
    }
#endif
    marker_mouse_move_pos = BIT_NOT_MARKER_MOUSE_CLICK;
    return;
}
void BitView::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    timer->stop();
    if(gsystemstate.windowtype == BIT_SINGLEWINDOW)
    {
        misDoubleClicked = false;
        return;
    }
    misDoubleClicked = !misDoubleClicked;
    emit mouseDoubleClickedSig(misDoubleClicked);
    return;
}
#ifdef BITVIEW_F239
bool BitView::event(QEvent *event)
{
    Q_UNUSED(event)
    switch(event->type())
    {
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
    {
        if(mBitviewType == BIT_SPECTROGRAM || BIT_SINGLE == gsystemstate.runningState)
        {
            return QWidget::event(event);
        }
        nFingerTouchCnt ++;
        if(nFingerTouchCnt > BIT_TOUCH_EVENT_MAX_CNT)
        {
            nFingerTouchCnt = 1;
        }
        QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
        if(touchEvent->touchPointStates() & Qt::TouchPointReleased)
        {
            return QWidget::event(event);
        }
        QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();
        if(2 == touchPoints.count())
        {
            misBitCenFreqChanged = false;
            misBitReflevelChanged = false;
            if(Touchtimer->isActive())
            {
            }
            else
            {
                Touchtimer->start(500);
            }
            if((nFingerTouchCnt % BIT_TOUCH_EVENT_MIN_CNT) != 0)
            {
                break;
            }
            emit suspendDraw();
            const QTouchEvent::TouchPoint &touchPoint0 = touchPoints.first();
            const QTouchEvent::TouchPoint &touchPoint1 = touchPoints.last();

//            qreal xScaleFactor = (touchPoint1.pos().x() - touchPoint0.pos().x()) /
//                    (touchPoint1.startPos().x() - touchPoint0.startPos().x());
            qreal xScaleFactor = QLineF(touchPoint0.pos(),touchPoint1.pos()).length() /
                    QLineF(touchPoint0.startPos(),touchPoint1.startPos()).length();
            qreal yScaleFactor = (touchPoint1.pos().y() - touchPoint0.pos().y()) /
                    (touchPoint1.startPos().y() - touchPoint0.startPos().y());

            misBitScaleChanged = true;
            if(xScaleFactor < 0)
            {
                break;
            }
            if(xScaleFactor < 0.6)
                DrawXScale = 0.6;
            else
                DrawXScale = xScaleFactor;
            if(xScaleFactor > 1)
            {
                BitXScale = xScaleFactor + 1;
            }
            else
            {
                BitXScale = xScaleFactor;
            }
            BitYScale = yScaleFactor;
            this->repaint();
        }
    }
    break;
    default:
    {
        return QWidget::event(event);
    }
    }
    return true;
}
#endif
/*
here not have to assign the trace index,
and the max\min\avage line to show by setting the property
*/
void BitView::showSigLine(qreal *pBuffer, quint32 datanum)
{
    datanum = datanum > SUPPORTTRACEPOINT ? SUPPORTTRACENUM : datanum;
    datanum = datanum < SUPPORTTRACEMINPOINT ? SUPPORTTRACEMINPOINT : datanum;
    getSync();
    if(gbitbuffer.gtracenum != datanum)
    {
        quint32 i = 0;
        qreal mdeta = 0.1 * 10 * (gusedsize.gpicwidth - 2 * LINEREEOR) / (datanum - 1);
        for(i = 0;i < datanum;i++)
        {
            gbitbuffer.drawpointsX[i] = BIT_GRID_START_X + i * mdeta;
        }
        gbitbuffer.gtracenum = datanum;

    }
//    for(qint32 i = 0 ; i < datanum; i++)
//    {
//        gbitbuffer.trace_ori[i] = pBuffer[i] + gusedsize.goffsetValue;
//    }
    memcpy(gbitbuffer.trace_ori,pBuffer,sizeof(qreal) * datanum);
    releaseSync();
    //async run
    emit emitRefleshsig();
    return;
}

void BitView::showFalltrom(qreal *pBuffer, quint32 datanum)
{
    datanum = datanum > SUPPORTTRACEPOINT ? SUPPORTTRACENUM : datanum;
    datanum = datanum < SUPPORTTRACEMINPOINT ? SUPPORTTRACEMINPOINT : datanum;
    getSync();
    if(gbitbuffer.gtracenum != datanum)
    {
//        quint32 i = 0;
//        qreal mdeta = 0.1 * 10 * gusedsize.gpicwidth / (datanum - 1);
//        for(i = 0;i < datanum;i++)
//        {
//            gbitbuffer.drawpointsX[i] = LEFTDIS + i * mdeta;
//        }
        gbitbuffer.gtracenum = datanum;
        //Albert 1025 when trace num change, recal x zxis pts.
        RecalSpectrogramBigPointX();
        RecalSpectrogramSmallPointX();
    }
//    for(qint32 i = 0 ; i < datanum; i++)
//    {
//        gbitbuffer.trace_ori[i] = pBuffer[i] + gusedsize.goffsetValue;
//    }
    memcpy(gbitbuffer.trace_ori,pBuffer,sizeof(qreal) * datanum);
    releaseSync();
    //async run
    emit emitFallSig();
    return;
}

void BitView::setTraceAttribute(quint32 traceIndex, quint32 attributeType, quint32 attribute)
{
//    quint32 attrvalidflag = 1;
    switch (attributeType)
    {
    case BIT_AVAG_ATTR:
        gctrlmana->gtraceavagflag[traceIndex] = attribute;
        gctrlmana->greavagflag[traceIndex] = attribute;
        break;
    case BIT_RE_AVAG_ATTR:
        gctrlmana->greavagflag[traceIndex] = attribute;
        break;
    case BIT_AVAG_NUM_ATTR:
        gctrlmana->gavagnum[traceIndex] = attribute;
        break;
    case BIT_TRACE_TYPE_ATTR:
        if(BIT_MAX_HOLD == attribute)
        {
            gctrlmana->gmaxkeepreflag[traceIndex] = BITON;
        }
        else if(BIT_MIN_HOLD == attribute)
        {
            gctrlmana->gminkeepreflag[traceIndex] = BITON;
        }
        gctrlmana->gtracetype[traceIndex] = attribute;
        calculationPainterArea();
        break;
    case BIT_TRACE_INDEX:
        gctrlmana->gtraceIndex = attribute;
        break;
    default:
//        attrvalidflag = 0;
        break;
    }
//    if(attrvalidflag)
//        gctrlmana->gtraceIndex = traceIndex;
    return;
}

qint32 BitView::setTraceRenderData(qreal *pbuff, qint32 datanum, qint32 traceIndex)
{
    qint32 num ;
    if(gbitbuffer.gtracenum == 0)
        num = NOWTRACENUM;
    else
        num = gbitbuffer.gtracenum;
    num = (num > datanum ? datanum : num);
    if(traceIndex < 0)
    {
        traceIndex = gctrlmana->gtraceIndex;
    }
    memcpy(gbitbuffer.trace_render[traceIndex],pbuff,sizeof(qreal)*num);
    return num;
}

qint32 BitView::getTraceRenderData(qreal *pbuff, qint32 datanum, qint32 traceIndex)
{
    qint32 num ;
    if(gbitbuffer.gtracenum == 0)
        num = NOWTRACENUM;
    else
        num = gbitbuffer.gtracenum;
    num = (num > datanum ? datanum : num);
    if(traceIndex < 0)
    {
        traceIndex = gctrlmana->gtraceIndex;
    }
    memcpy(pbuff,gbitbuffer.trace_render[traceIndex],sizeof(qreal)*num);
    return num;
}

//Tony 1024 Add . Return trace attribute.
qint32  BitView::getTraceAttribute(quint32 traceIndex, quint32 attributeType)
{
    quint32 attribute = 0;
    switch (attributeType)
    {
    case BIT_AVAG_ATTR:
        attribute = gctrlmana->gtraceavagflag[traceIndex];
        break;
    case BIT_AVAG_NOW_NUM_ATTR:
        attribute = gctrlmana->gnowavagnum[traceIndex];
        break;
    case BIT_RE_AVAG_ATTR:
        attribute = gctrlmana->greavagflag[traceIndex];
        break;
    case BIT_AVAG_NUM_ATTR:
        attribute = gctrlmana->gavagnum[traceIndex];
        break;
    case BIT_TRACE_TYPE_ATTR:
        attribute = gctrlmana->gtracetype[traceIndex];
        break;
    case BIT_TRACE_INDEX:
        attribute = gctrlmana->gtraceIndex;
        break;
    }
    return attribute;
}

//Tony 1016 Add
void BitView::setFreqAttribute(quint32 attributeType, qreal attribute)
{
    switch (attributeType)
    {
    case BIT_START_FREQ:
        gfreqinfo.gstartfreq = attribute/* + mFreqOffset*/ ;
        break;
    case BIT_STOP_FREQ:
        gfreqinfo.gstopfreq = attribute/* + mFreqOffset*/ ;
        break;
    case BIT_CENTER_FREQ:
        gfreqinfo.gcenterfreq = attribute/* + mFreqOffset*/ ;
        break;
    case BIT_SPAN_FREQ:
        gfreqinfo.gspanfreq = attribute ;
        break;
    case BIT_RBW_FREQ:
        gfreqinfo.grbwfreq = attribute ;
        break;
    default:
        break;
    }
    //*when freq change, must refresh fall rect
    refreshSepectrogramRect();
    return ;
}

qreal BitView::getFreqAttribute(quint32 attributeType)
{
    qreal attribute = 0;
    switch (attributeType)
    {
    case BIT_START_FREQ:
        attribute = gfreqinfo.gstartfreq;
        break;
    case BIT_STOP_FREQ:
        attribute = gfreqinfo.gstopfreq;
        break;
    case BIT_CENTER_FREQ:
        attribute = gfreqinfo.gcenterfreq;
        break;
    case BIT_SPAN_FREQ:
        attribute = gfreqinfo.gspanfreq;
        break;
    case BIT_RBW_FREQ:
        attribute = gfreqinfo.grbwfreq;
        break;
    default:
        break;
    }
    return attribute;
}

void BitView::setTopWordsMsg(quint32 traceIndex, const QVector<QString> &wordvec)
{
    gctrlmana->gtraceIndex = traceIndex;
    gwordset.gtflstr = wordvec.at(0);
    gwordset.gtslstr = wordvec.at(1);
    gwordset.gtscstr = wordvec.at(2);
    showTopPart();
    return;
}

void BitView::setBottomWordsMsg(quint32 traceIndex, const QVector<QString> &wordvec)
{
    gctrlmana->gtraceIndex = traceIndex;
    gwordset.gbflstr = wordvec.at(0);
    gwordset.gbfrstr = wordvec.at(1);
    gwordset.gbslstr = wordvec.at(2);
    gwordset.gbsrstr = wordvec.at(3);
    showBottomPart();
    return;
}

void BitView::setBottomSingleWordsMsg(quint32 traceIndex, qint32 index, QString word)
{
    gctrlmana->gtraceIndex = traceIndex;
    switch (index) {
    case 0:
        gwordset.gbflstr = word;
        break;
    case 1:
        gwordset.gbfrstr = word;
        break;
    case 2:
        gwordset.gbslstr = word;
        break;
    case 3:
        gwordset.gbsrstr = word;
        break;
    default:
        break;
    }
    showBottomPart();
    return;
}
//Tony 1022 1022
void BitView::showBottomWordsMsg(qint32 msgType)
{
    switch (msgType) {
    case BV_BOTTOM_STARTANDSTOP:
        gwordset.gbflstr = "Start Freq "+freqValueToQstring(gfreqinfo.gstartfreq + mFreqOffset);
        gwordset.gbfrstr = "Stop Freq "+freqValueToQstring(gfreqinfo.gstopfreq + mFreqOffset);
        gwordset.gbslstr = "RBW "+freqValueToQstring(gfreqinfo.grbwfreq);
        gwordset.gbsrstr = "Acq Time " + getPersistenceTimeStr(gfreqinfo.gacqTime);
        break;
    case BV_BOTTOM_CENTERANDSPAN:
        gwordset.gbflstr = "Center Freq "+freqValueToQstring(gfreqinfo.gcenterfreq + mFreqOffset);
        gwordset.gbfrstr = "Span "+freqValueToQstring(gfreqinfo.gspanfreq);
        gwordset.gbslstr = "RBW "+freqValueToQstring(gfreqinfo.grbwfreq);
        gwordset.gbsrstr = "Acq Time " + getPersistenceTimeStr(gfreqinfo.gacqTime);
        break;
    default:
        break;
    }
    showBottomPart();
    return;
}

//Tony 1023
void BitView::showTopWordsMsg(qint32 msgType)
{
    char mstr[20];

    switch (msgType) {
    case BV_TOP_APMTINFO:
        switch (gAmptdUnit) {
        case BIT_DBM:
            sprintf(mstr, "%.2f dBm", gusedsize.grefValue + gusedsize.goffsetValue);
            break;
        case BIT_DBV:
            sprintf(mstr, "%.2f dBv", gusedsize.grefValue + gusedsize.goffsetValue + dBVFix);
            break;
        case BIT_DBMV:
            sprintf(mstr, "%.2f dBmV", gusedsize.grefValue + gusedsize.goffsetValue + dBmVFix);
            break;
        case BIT_DBUV:
            sprintf(mstr, "%.2f dBuV", gusedsize.grefValue + gusedsize.goffsetValue + dBuVFix);
            break;
        case BIT_VOLT:
            dbmToVoltCalculatorAndDisplayFunc(mstr, gusedsize.grefValue + gusedsize.goffsetValue);
            break;
        case BIT_WATTS:
            dbmToWattsCalculatorAndDisplayFunc(mstr, gusedsize.grefValue + gusedsize.goffsetValue);
            break;
        default:
            break;
        }
        gwordset.gtflstr="Ref Level "+QString(mstr);
        gwordset.gtslstr="Scale "+QString::number(gusedsize.gdivValue,'f',2)+" dB/Div";
    default:
        break;
    }
    showTopPart();
    return;
}

//Tony 1022
QString BitView::freqValueToQstring(qreal freq)
{
    qint32 unitNo=0;
    qint32 zeronum=0;
    QString unitStr="";
    QString freqValue="";
    bool minusFlag = 0;
    if(freq < 0)
    {
        minusFlag = true;
        freq *= -1;
    }
    unitNo=freqUnitFindProc(freq);
    if(freq > 1.0)
        zeronum=freqnotZeroPosition(freq);
    else
        zeronum = 0;
    switch (unitNo) {
    case BV_UNIT_GHZ:
        unitStr=" GHz";
        if(9<=zeronum)
        {
            freqValue=QString::number((qreal)freq/BV_GHZ,'f',6)/*+unitStr*/;
        }else
        {
            freqValue=QString::number((qreal)freq/BV_GHZ,'f',9-zeronum)/*+unitStr*/;
        }
        break;
    case BV_UNIT_MHZ:
        unitStr=" MHz";
        if(6<=zeronum)
        {
            freqValue=QString::number((qreal)freq/BV_MHZ,'f',6)/*+unitStr*/;
        }else
        {
            freqValue=QString::number((qreal)freq/BV_MHZ,'f',6-zeronum)/*+unitStr*/;
        }
        break;
    case BV_UNIT_KHZ:
        unitStr=" kHz";
        if(3<=zeronum)
        {
            freqValue=QString::number((qreal)freq/BV_KHZ,'f',6)/*+unitStr*/;
        }else
        {
            freqValue=QString::number((qreal)freq/BV_KHZ,'f',3-zeronum)/*+unitStr*/;
        }
        break;
    case BV_UNIT_HZ:
        unitStr=" Hz";
        freqValue=QString::number((qreal)freq/BV_HZ,'f',6)/*+unitStr*/;
        break;
    }
    if(minusFlag)
    {
        freqValue = QString("-") + freqValue;
    }
    if(freq > -0.00001 && freq < 0.00001)
    {
//        freqValue = freqValue + unitStr;
    }
    else
    {
        freqValue.replace(DelZeroRx,"");
    }
    freqValue = freqValue + unitStr;
    return freqValue;
}

//Tony 1022
qint32 BitView::freqUnitFindProc(qreal freq)
{
    if (freq >= BV_GHZ)
        return BV_UNIT_GHZ;
    else if (freq >= BV_MHZ)
        return BV_UNIT_MHZ;
    else if (freq >= BV_KHZ)
        return BV_UNIT_KHZ;
    else
        return BV_UNIT_HZ;
}

//Tony 1022
qint32 BitView::freqnotZeroPosition(qreal freq)
{
    qint32 remainder=0;
    qint32 pos=0;
    if(freq <= 0)
        return 0;
    while(0 == remainder)
    {
        ++pos;
        remainder = (qint32)freq%10;
        freq = freq/10;
    }
    return (pos-1);
}

/*
 * this mem function is a good method for converting between different axes
*/
void BitView::axesTranslate(quint32 traceIndex, qreal *pBuffer, quint32 dataNum)
{
    quint32 i = 0;
    qreal mbaselevel = gusedsize.grefValue + gusedsize.goffsetValue;
    qreal perYdBpixels = gusedsize.gdivValue * 10.0 / gusedsize.gpicheight ;

    qreal mconvy = 0.0;
    qreal mbottom =CenterPartRect.bottom() - HALFLINEREEOR;
    qreal mtop = CenterPartRect.top();
    sum = 0.0;
    for(i = 0;i < dataNum ;i++)
    {
        sum += pBuffer[i];
        mconvy = (mbaselevel - pBuffer[i] - gusedsize.goffsetValue) / perYdBpixels + mtop;
        if (mconvy < mtop)
        {
            mconvy = mtop;
        }
        else if (mconvy > mbottom)
        {
            mconvy = mbottom;
        }
        gbitbuffer.drawpointsY[traceIndex][i] = mconvy;
    }
    return;
}

void BitView::oriDataDeals(qreal *pBuffer, quint32 dataNum)
{
    qint32 i = 0;
    for(i = 0;i < SUPPORTTRACENUM;i++)
    {
        switch(gctrlmana->gtracetype[i])
        {
        case BIT_TRACE_OFF:

            break;
        case BIT_CLEAR_WRITE:
            if(BITON == gctrlmana->gtraceavagflag[i])
            {
                averageProcess(i,pBuffer,dataNum);
            }
            else
            {
                memcpy(gbitbuffer.trace_render[i],pBuffer,sizeof(qreal) * dataNum);
//                gctrlmana->gtraceIndex = i;
            }
            axesTranslate(i,gbitbuffer.trace_render[i],dataNum);
            break;
        case BIT_MAX_HOLD:
            if(BITON == gctrlmana->gmaxkeepreflag[i])
            {
                quint32 k = 0;
                for(k = 0;k < dataNum;k++)
                    gbitbuffer.trace_render[i][k] = MAXHOLDINI;
                gctrlmana->gmaxkeepreflag[i] = BITOFF;
            }
            maxholdProcess(i,pBuffer,dataNum);
            axesTranslate(i,gbitbuffer.trace_render[i],dataNum);
//            gctrlmana->gtraceIndex = i;
            break;
        case BIT_MIN_HOLD:
            if(BITON == gctrlmana->gminkeepreflag[i])
            {
                quint32 k = 0;
                for(k = 0;k < dataNum;k++)
                    gbitbuffer.trace_render[i][k] = MINHOLDINI;
                gctrlmana->gminkeepreflag[i] = BITOFF;
            }
            minholdProcess(i,pBuffer,dataNum);
            axesTranslate(i,gbitbuffer.trace_render[i],dataNum);
//            gctrlmana->gtraceIndex = i;
            break;
        case BIT_VIEW:
            //Tony 1024
            if(mResizeMark || BIT_CONTINUOUS == gsystemstate.runningState)
            {
                axesTranslate(i,gbitbuffer.trace_render[i],dataNum);
                mResizeMark = 0;
            }
            break;
        case BIT_AVERAGE:
            averageProcess(i,pBuffer,dataNum);
            axesTranslate(i,gbitbuffer.trace_render[i],dataNum);
            break;

        }
    }
    return;
}

void BitView::oriSpectrogramDataDeals(qreal *pBuffer, quint32 dataNum)
{
    qint32 i = 0;
    for(i = 0;i < SUPPORTTRACENUM;i++)
    {
        switch(gctrlmana->gtracetype[i])
        {
        case BIT_TRACE_OFF:
        case BIT_CLEAR_WRITE:
            if(BITON == gctrlmana->gtraceavagflag[i])
            {
                averageProcess(i,pBuffer,dataNum);
            }
            else
            {
                memcpy(gbitbuffer.trace_render[i],pBuffer,sizeof(qreal) * dataNum);
//                gctrlmana->gtraceIndex = i;
            }
            axesTranslate(i,gbitbuffer.trace_render[i],dataNum);
            break;
        case BIT_MAX_HOLD:
            if(BITON == gctrlmana->gmaxkeepreflag[i])
            {
                quint32 k = 0;
                for(k = 0;k < dataNum;k++)
                    gbitbuffer.trace_render[i][k] = MAXHOLDINI;
                gctrlmana->gmaxkeepreflag[i] = BITOFF;
            }
            maxholdProcess(i,pBuffer,dataNum);
            axesTranslate(i,gbitbuffer.trace_render[i],dataNum);
//            gctrlmana->gtraceIndex = i;
            break;
        case BIT_MIN_HOLD:
            if(BITON == gctrlmana->gminkeepreflag[i])
            {
                quint32 k = 0;
                for(k = 0;k < dataNum;k++)
                    gbitbuffer.trace_render[i][k] = MINHOLDINI;
                gctrlmana->gminkeepreflag[i] = BITOFF;
            }
            minholdProcess(i,pBuffer,dataNum);
            axesTranslate(i,gbitbuffer.trace_render[i],dataNum);
//            gctrlmana->gtraceIndex = i;
            break;
        case BIT_VIEW:
            //Tony 1024
            if(mResizeMark || BIT_CONTINUOUS == gsystemstate.runningState)
            {
                axesTranslate(i,gbitbuffer.trace_render[i],dataNum);
                mResizeMark = 0;
            }
            break;
        case BIT_AVERAGE:
            averageProcess(i,pBuffer,dataNum);
            axesTranslate(i,gbitbuffer.trace_render[i],dataNum);
            break;

        }
    }
    return;
}

void BitView::graphRefleshslot()
{
    getSync();
    //qreal tdeta = 0.0;
    //struct timeval tstart,tstop;
    //gettimeofday(&tstart,NULL);
    refleshfirLayer();
    this->repaint();
    //gettimeofday(&tstop,NULL);
    //tdeta = (1000000*(tstop.tv_sec-tstart.tv_sec) + tstop.tv_usec-tstart.tv_usec) / 1000000.0;
    ////the typical val is about 2 ms
    releaseSync();
    return;
}

void BitView::graphFallslot()
{
    if(mFileLoadFlag)
    {
        return;
    }
//    if(gctrlmana->gtracetype[gctrlmana->gtraceIndex] == BIT_VIEW)
//    {
//        return;
//    }
    //when app first run, there may be no data transfer, so here need check data buf.
    if(!checkOriData(gbitbuffer.trace_ori,gbitbuffer.gtracenum))
    {
        return;
    }
    getSync();

    oriSpectrogramDataDeals(gbitbuffer.trace_ori,gbitbuffer.gtracenum);
    gsigrendermap.fill(Qt::transparent);
    QPainter painter(&gsigrendermap);
    painter.initFrom(this);
    mCacheDataStartPos = (mCacheDataStartPos) % SPECTROGRAM_CACHE_DATA;
//    //!Albert 1019, when cache data array pos to zero, mCacheData must change to original start pos.
//    if(mCacheDataStartPos == 0)
//    {
//        mCacheData =  mStartPos;
//    }
    //!cache data
    cacheData(mCacheData + SPECTROGRAM_TRACE_SIZE * mCacheDataStartPos,gbitbuffer.trace_render[gctrlmana->gtraceIndex],gbitbuffer.gtracenum);
    //! draw
//    drawSpectrogram(&painter);

        drawSpectrogramSmallPix(&painter);
        drawSpectrogramBigPix(&painter);


    //! start pos to next index.
    mCacheRealNum ++;
    if(mCacheRealNum >= SPECTROGRAM_CACHE_DATA)
    {
        mCacheRealNum = SPECTROGRAM_CACHE_DATA;
    }
    //! draw cur trace info
    drawCurTraceIndex(&painter,mCacheRealNum);
    mCacheDataStartPos = mCacheDataStartPos + 1;
#ifdef BITVIEW_TIME_MARKER
    renderSpectrogramCursorIndex(&painter);
#endif
    this->repaint(rect());
    releaseSync();
    return;
}

void BitView::refleshfallslot()
{
    if(gctrlmana->gtracetype[gctrlmana->gtraceIndex] == BIT_VIEW)
    {
        return;
    }

    gsigrendermap.fill(Qt::transparent);
    QPainter painter(&gsigrendermap);
    painter.initFrom(this);

    qint32 nLeft = LEFTDIS;
    qint32 nTop = TOPDIS;
    qint32 nWidthBig = pixmapnewBig.width() - LEFTDIS - RIGHTDIS - HALFLINEREEOR;
    qint32 nHeigthBig = 10* (pixmapnewBig.height() - (BOTTOMDIS + gsystemstate.windowtype * markerTabelVisiable * BIT_MARKER_TABLE_HEIGHT) - TOPDIS- HALFLINEREEOR)/10;
//    qint32 nRightBig = nWidthBig;
    qint32 nBottomBig = nHeigthBig;
//    if(gbitbuffer.gtracenum < this->width())
    if((quint32)(this->width()) > gbitbuffer.gtracenum)
        painter.drawPixmap(nLeft ,nTop ,nWidthBig,nBottomBig,pixmapnewBig,0,0,nWidthBig ,nBottomBig);

    nLeft = LEFTDIS;
    nTop = TOPDIS;
    qint32 nWidthSmall = pixmapnewSmall.width() - LEFTDIS - RIGHTDIS - HALFLINEREEOR;
    qint32 nHeigthSmall = 10* (pixmapnewSmall.height() - (BOTTOMDIS + gsystemstate.windowtype * markerTabelVisiable * BIT_MARKER_TABLE_HEIGHT) - TOPDIS- HALFLINEREEOR)/10;

//    qint32 nRightSmall = nWidthSmall;
    qint32 nBottomSmall = nHeigthSmall;
//    if(gbitbuffer.gtracenum > this->width())
    if((quint32)(this->width()) <= gbitbuffer.gtracenum)
    {
        painter.drawPixmap(nLeft ,nTop ,nWidthSmall ,nBottomSmall,pixmapnewSmall,0,0,nWidthSmall,nBottomSmall);
    }
    //! draw cur trace info
    drawCurTraceIndex(&painter,mCacheRealNum);
#ifdef BITVIEW_TIME_MARKER
    renderSpectrogramCursorIndex(&painter);
#endif
    this->repaint(rect());

    return;
}
//=====================================================================================
/*
all measurements render is done here
Reflesh  dynamic layers of spectrum.
*/
void BitView::refleshfirLayer()
{

    gsigrendermap.fill(Qt::transparent);
    QPainter painter(&gsigrendermap);
    painter.initFrom(this);
    gbitpen.setColor(Qt::red);
    gbitpen.setWidth(HALFLINEREEOR);
    painter.setPen(gbitpen);

    if(!mFileLoadFlag)
    {
        //when app first run, there may be no data transfer, so here need check data buf.
        if(!checkOriData(gbitbuffer.trace_ori,gbitbuffer.gtracenum))
        {
            return;
        }
        //this func put here for sizechanged
        oriDataDeals(gbitbuffer.trace_ori,gbitbuffer.gtracenum);
    }
    else
    {
        for(qint32 i = 0; i < SUPPORTTRACENUM; i++)
        {
            axesTranslate(i,gbitbuffer.trace_render[i],gbitbuffer.gtracenum);
        }
    }
    //Tony 1113
    if(!gctrlmana->gLimitVisiable)
    {
        renderSiglines(&painter);
    }else
    {
        renderLimitPart(&painter);
    }
    if((qint32)(gctrlmana->gtracetype[gctrlmana->gtraceIndex]) != BIT_TRACE_OFF)
    {
        renderMarkerPart(&painter);
    }
    if(mBitviewType == BIT_DENSITY)
    {
        renderDensityPart(&painter);
    }
//    renderVideoTriggerLevel(&painter);
    //Albert for FMT 19/03/29
//    renderFMTLayer(&painter);
#ifdef BITVIEW_F239
    renderDoubleClickPixMap();
#endif
    return;
}

void BitView::refleshmarker()
{
    switch (mBitviewType)
    {
    case BIT_NONE:
        break;
    case BIT_SPECTRUM:
        if(BIT_SINGLE == gsystemstate.runningState || (gfreqinfo.gacqTime > BIT_REFRESH_TIME_MIN))
        {
            markerUpdateByFreq();
        }
        break;
    case BIT_DENSITY:
        if(BIT_SINGLE == gsystemstate.runningState || (gfreqinfo.gacqTime > BIT_REFRESH_TIME_MIN))
        {
            markerUpdateByFreq();
        }
        break;
    case BIT_SPECTROGRAM:
        break;
    default:
        break;
    }
    return;
}

void BitView::refleshdisplay()
{
    switch (mBitviewType)
    {
    case BIT_NONE:
        break;
    case BIT_SPECTRUM:
        if(BIT_SINGLE == gsystemstate.runningState || (gfreqinfo.gacqTime > BIT_REFRESH_TIME_MIN))
        {
            refleshfirLayer();
            refleshsecLayer();
            this->repaint(rect());
        }else
        {
            refleshsecLayer();
            this->repaint(rect());
        }
        break;
    case BIT_DENSITY:
        if(BIT_SINGLE == gsystemstate.runningState || (gfreqinfo.gacqTime > BIT_REFRESH_TIME_MIN))
        {
            refleshfirLayer();
            refleshsecLayer();
            this->repaint(rect());
        }else
        {
            refleshsecLayer();
            this->repaint(rect());
        }
        break;
    case BIT_SPECTROGRAM:
        if(BIT_SINGLE == gsystemstate.runningState || (gfreqinfo.gacqTime > BIT_REFRESH_TIME_MIN) || mFileLoadFlag)
        {
            refleshfallslot();
            refleshsecLayer();
            this->repaint(rect());
        }else
        {
            refleshsecLayer();
            this->repaint(rect());
        }
        break;
    default:
        break;
    }
    return;
}

void BitView:: renderSiglines(QPainter* pPainter)
{
    qint32 i = 0;
    quint32 k = 1;
    for(i  = 0;i < SUPPORTTRACENUM;i++)
    {
        if(i != gctrlmana->gtraceIndex)
        {
            if((qint32)(gctrlmana->gtracetype[i]) != BIT_TRACE_OFF)
            {
                if (BITTR1 == i)
                {
                    pPainter->setPen(mTraceColor.Trace1);
                }
                else if (BITTR2 == i)
                {
                    pPainter->setPen(mTraceColor.Trace2);
                }
                else if (BITTR3 == i)
                {
                    pPainter->setPen(mTraceColor.Trace3);
                }
                else if (BITTR4 == i)
                {
                    pPainter->setPen(mTraceColor.Trace4);
                }
                else if (BITTR5 == i)
                {
                    pPainter->setPen(mTraceColor.Trace5);
                }
                else if (BITTR6 == i)
                {
                    pPainter->setPen(mTraceColor.Trace6);
                }
                for(k = 1;k < gbitbuffer.gtracenum;k++)
                {
                    pPainter->drawLine(QPointF(gbitbuffer.drawpointsX[k-1],gbitbuffer.drawpointsY[i][k-1]),QPointF(gbitbuffer.drawpointsX[k],gbitbuffer.drawpointsY[i][k]));
                }
            }
        }
    }

    if((qint32)(gctrlmana->gtracetype[gctrlmana->gtraceIndex]) != BIT_TRACE_OFF)
    {
        if (BITTR1 == gctrlmana->gtraceIndex)
        {
            pPainter->setPen(mTraceColor.Trace1);
        }
        else if (BITTR2 == gctrlmana->gtraceIndex)
        {
            pPainter->setPen(mTraceColor.Trace2);
        }
        else if (BITTR3 == gctrlmana->gtraceIndex)
        {
            pPainter->setPen(mTraceColor.Trace3);
        }
        else if (BITTR4 == gctrlmana->gtraceIndex)
        {
            pPainter->setPen(mTraceColor.Trace4);
        }
        else if (BITTR5 == gctrlmana->gtraceIndex)
        {
            pPainter->setPen(mTraceColor.Trace5);
        }
        else if (BITTR6 == gctrlmana->gtraceIndex)
        {
            pPainter->setPen(mTraceColor.Trace6);
        }

        for(k = 1;k < gbitbuffer.gtracenum;k++)
        {
            pPainter->drawLine(QPointF(gbitbuffer.drawpointsX[k-1],gbitbuffer.drawpointsY[gctrlmana->gtraceIndex][k-1]),QPointF(gbitbuffer.drawpointsX[k],gbitbuffer.drawpointsY[gctrlmana->gtraceIndex][k]));
        }
    }
    return;
}
//=====================================================================================
void BitView::averageProcess(quint32 traceIndex, qreal *psourBuffer, quint32 dataNum)
{
    if(BITON == gctrlmana->greavagflag[traceIndex])
    {
        memcpy(gbitbuffer.trace_render[traceIndex],psourBuffer,sizeof(qreal) * dataNum);
        gctrlmana->greavagflag[traceIndex] = BITOFF;
        //means re avag first time
        gctrlmana->gnowavagnum[traceIndex] = 1;
    }
    if(gctrlmana->gnowavagnum[traceIndex] > gctrlmana->gavagnum[traceIndex])
    {
        gctrlmana->gnowavagnum[traceIndex] = gctrlmana->gavagnum[traceIndex];
    }
    quint32 i = 0;
    for(i = 0;i < dataNum;i++)
    {
        gbitbuffer.trace_render[traceIndex][i] = (gbitbuffer.trace_render[traceIndex][i] * (gctrlmana->gnowavagnum[traceIndex] - 1) + *(psourBuffer + i)) / gctrlmana->gnowavagnum[traceIndex];
    }
    gctrlmana->gnowavagnum[traceIndex]++;
    return;
}
void BitView::maxholdProcess(quint32 traceIndex, qreal *psourBuffer, quint32 dataNum)
{
    quint32 i = 0;
    for(i = 0; i < dataNum;i++)
    {
        gbitbuffer.trace_render[traceIndex][i] = gbitbuffer.trace_render[traceIndex][i] < *(psourBuffer+i) ? *(psourBuffer+i) : gbitbuffer.trace_render[traceIndex][i];
    }
    return;
}
void BitView::minholdProcess(quint32 traceIndex, qreal *psourBuffer, quint32 dataNum)
{
    quint32 i = 0;
    for(i = 0; i < dataNum;i++)
    {
        gbitbuffer.trace_render[traceIndex][i] = gbitbuffer.trace_render[traceIndex][i] > *(psourBuffer+i) ? *(psourBuffer+i) : gbitbuffer.trace_render[traceIndex][i];
    }
    return;
}

/**
 * @brief BitView::refleshsecLayer
 * @note 绘制视图第二层
 */
void BitView::refleshsecLayer()
{
    gpixmap.fill(mPenColor.background);
    QPainter painter(&gpixmap);
    painter.initFrom(this);

   //UNDO need add switches to decide render what

    switch (mBitviewType) {
    case BIT_NONE:
        break;
    case BIT_SPECTRUM:
        //base grid line
        renderGridLines(&painter);
        //left part
        renderLeftPart(&painter);
        //top part
        renderTopPart(&painter);
        //bottom part
        renderBottomPart(&painter);

        renderFMTLayer(&painter);

        renderVideoTriggerLevel(&painter);

        if(misFmtShow)
        {
            FmtXAxisCalculatorFunc(gctrlmana->gFMTFreq,gctrlmana->gFmtPointsNum);
            FmtYAxisCalculatorFunc(gctrlmana->gFMTAmplitude,gctrlmana->gFmtPointsNum);
            refreshFmtDrawData(gctrlmana->gFmtPointsNum);
        }
        break;
    case BIT_DENSITY:
        //base grid line
        renderGridLines(&painter);
        //left part
        renderLeftPart(&painter);
        produceDensityColorBar();
//        drawDensityColBar(&painter);
//        renderDensityColorBar(&painter);
        //top part
        renderTopPart(&painter);
        //bottom part
        renderBottomPart(&painter);

        renderFMTLayer(&painter);

        renderVideoTriggerLevel(&painter);

        if(misFmtShow)
        {
            FmtXAxisCalculatorFunc(gctrlmana->gFMTFreq,gctrlmana->gFmtPointsNum);
            FmtYAxisCalculatorFunc(gctrlmana->gFMTAmplitude,gctrlmana->gFmtPointsNum);
            refreshFmtDrawData(gctrlmana->gFmtPointsNum);
        }
        break;
    case BIT_SPECTROGRAM:
        //base grid line
        renderSpectrogramGridLines(&painter);
        //spectrogram color bar
//        refreshSepectrogramRect();
        renderSpectrogramColBar(&painter);
        //top part
        renderTopPart(&painter);
        //bottom part
        renderBottomPart(&painter);
        break;
    default:
        break;
    }
//    QPen myPen;
//    QPolygonF myPolygon;
//    QBrush oldBrush;
//    myPolygon.append(QPointF(100,300));
//    myPolygon.append(QPointF(150,500));
//    myPolygon.append(QPointF(300,100));
//    myPolygon.append(QPointF(200,100));
//    myPolygon.append(QPointF(100,300));
//    QPainterPath myPath;
//    myPath.addPolygon(myPolygon);
//    oldBrush = painter.brush();
//    painter.setBrush(QColor(255,0,0,128));
//    painter.setPen(myPen);
//    painter.drawPath(myPath);
//    painter.setBrush(oldBrush);
//    this->repaint(rect());

//    QPainter painter(this);
    return;
}

/**
 * @brief BitView::renderLeftPart
 * @param pPainter
 * @note 绘制右面矩形区域左部分显示  Y轴坐标
 */
void BitView::renderLeftPart(QPainter *pPainter)
{
    gbitpen.setWidth(HALFLINEREEOR);
    gbitpen.setColor(mPenColor.leftPart);
    pPainter->setPen(gbitpen);
    pPainter->setFont(QFont("Arial", 9));

    qreal mbaselevel = gusedsize.grefValue + gusedsize.goffsetValue;
    qreal mdiv = fabs(gusedsize.gdivValue);
    qreal mdivpix = gusedsize.gpicheight * 0.1;
    char mstr[20];
    qreal mval = 0.0;

    qint32 i = 0;
    if(gusedsize.gpicheight > MIJIHEIGHT)
    {
        for(i = 0;i < 11;i++)
        {
            mval = mbaselevel /* - mdiv*/- mdiv * i;
            switch (gAmptdUnit) {
            case BIT_DBM:
                sprintf(mstr, "%.2f", mval);
                break;
            case BIT_DBV:
                sprintf(mstr, "%.2f", mval + dBVFix);
                break;
            case BIT_DBMV:
                sprintf(mstr, "%.2f", mval + dBmVFix);
                break;
            case BIT_DBUV:
                sprintf(mstr, "%.2f", mval + dBuVFix);
                break;
            case BIT_VOLT:
                pPainter->setFont(QFont("Arial", 7));
                dbmToVoltCalculatorAndDisplayFunc(mstr, mval);
                break;
            case BIT_WATTS:
                pPainter->setFont(QFont("Arial", 7));
                dbmToWattsCalculatorAndDisplayFunc(mstr, mval);
                break;
            default:
                break;
            }
            pPainter->drawText(BITWORDLEFT, TOPDIS - BITWORDHSET /*+ mdivpix*/+ mdivpix * i , WORDWIDTH, WORDHEIGHT, Qt::AlignRight, mstr);
        }
    }
    else
    {
        for(i = 0;i < 6;i++)
        {
            mval = mbaselevel  /*- mdiv*/- mdiv * (2*i);

            switch (gAmptdUnit) {
            case BIT_DBM:
                sprintf(mstr, "%.2f", mval);
                break;
            case BIT_DBV:
                sprintf(mstr, "%.2f", mval + dBVFix);
                break;
            case BIT_DBMV:
                sprintf(mstr, "%.2f", mval + dBmVFix);
                break;
            case BIT_DBUV:
                sprintf(mstr, "%.2f", mval + dBuVFix);
                break;
            case BIT_VOLT:
                pPainter->setFont(QFont("Arial", 7));
                dbmToVoltCalculatorAndDisplayFunc(mstr, mval);
                break;
            case BIT_WATTS:
                pPainter->setFont(QFont("Arial", 7));
                dbmToWattsCalculatorAndDisplayFunc(mstr, mval);
                break;
            default:
                break;
            }
            pPainter->drawText(BITWORDLEFT, TOPDIS - BITWORDHSET /*+ mdivpix*/+ mdivpix * (2*i), WORDWIDTH, WORDHEIGHT, Qt::AlignRight, mstr);
        }
    }
    return;
}

/**
 * @brief BitView::showTopPart
 * @note 显示矩形区域上部分信息
 */
void BitView::showTopPart()
{
    QPainter painter(&gpixmap);
    QBrush mbrush(mPenColor.background);
    painter.setBrush(mbrush);
    painter.drawRect(LEFTDIS,
                     2*LINEREEOR,
                     gusedsize.gpicwidth,
                     TOPDIS - BITWORDHSET-2*LINEREEOR);
    renderTopPart(&painter);
    return;
}

/**
 * @brief BitView::showBottomPart
 * @note 显示矩形区域下部分信息
 */
void BitView::showBottomPart()
{
    QPainter painter(&gpixmap);
    QBrush mbrush(mPenColor.background);
    painter.setBrush(mbrush);
    painter.drawRect(LEFTDIS,
                     TOPDIS + gusedsize.gpicheight + 2*LINEREEOR,
                     gusedsize.gpicwidth,
                     TOPDIS - BITWORDHSET-2*LINEREEOR);
    renderBottomPart(&painter);

    return;
}

/**
 * @brief BitView::renderTopPart
 * @param pPainter
 * @note 绘制右面矩形区域上部分显示
 */
void BitView::renderTopPart(QPainter *pPainter)
{
    gbitpen.setWidth(HALFLINEREEOR);
    gbitpen.setColor(mPenColor.topPart);
    pPainter->setPen(gbitpen);
    QFont mFont;
    mFont.setFamily("Arial");
    mFont.setPixelSize(13);
    mFont.setWeight(QFont::Bold);
    pPainter->setFont(mFont);

    qint32 mx = LEFTDIS + 0.5 * (gusedsize.gpicwidth - TITLEWIDTH);
    qint32 my = TOPDIS - 1 * WORDHEIGHT + HALFLINEREEOR;
    pPainter->drawText(mx, my, TITLEWIDTH, WORDHEIGHT,
                       Qt::AlignCenter, gwordset.gtscstr);

    //topfirstleft
    mx = LEFTDIS + HALFLINEREEOR;
    my = (LINEREEOR << 2) + HALFLINEREEOR;
    pPainter->drawText(mx, my, TITLEWIDTH, WORDHEIGHT,
                       Qt::AlignLeft, gwordset.gtflstr);

    //topsecleft
    my = (LINEREEOR << 1) + WORDHEIGHT;
    pPainter->drawText(mx, my, TITLEWIDTH, WORDHEIGHT,
                       Qt::AlignLeft, gwordset.gtslstr);
    return;
}

/**
 * @brief BitView::renderBottomPart
 * @param pPainter
 * @note 绘制右面矩形区域下部分显示
 */
void BitView::renderBottomPart(QPainter *pPainter)
{
    gbitpen.setWidth(HALFLINEREEOR);
    gbitpen.setColor(mPenColor.bottomPart);
    pPainter->setPen(gbitpen);
    QFont mFont;
    mFont.setFamily("Arial");
    mFont.setPixelSize(13);
    mFont.setWeight(QFont::Bold);
    pPainter->setFont(mFont);

    //bottomfirstleft
    qint32 mx = LEFTDIS + HALFLINEREEOR;
    qint32 my = TOPDIS + gusedsize.gpicheight + LINEREEOR;
    pPainter->drawText(mx, my, TITLEWIDTH + 30, WORDHEIGHT,
                       Qt::AlignLeft, gwordset.gbflstr);

    //bottomsecleft
    my = TOPDIS + gusedsize.gpicheight  + WORDHEIGHT - LINEREEOR;
    pPainter->drawText(mx, my, TITLEWIDTH, WORDHEIGHT + 30,
                       Qt::AlignLeft, gwordset.gbslstr);

    //bottomfirstright
    mx = LEFTDIS + gusedsize.gpicwidth - TITLEWIDTH;
    my = TOPDIS + gusedsize.gpicheight + LINEREEOR;
    pPainter->drawText(mx, my, TITLEWIDTH, WORDHEIGHT,
                       Qt::AlignRight, gwordset.gbfrstr);

    //bottomsectright
    my = TOPDIS + gusedsize.gpicheight  + WORDHEIGHT - LINEREEOR;
    pPainter->drawText(mx, my, TITLEWIDTH, WORDHEIGHT,
                       Qt::AlignRight, gwordset.gbsrstr);
    return;
}

void BitView::getclickSource(quint32 iIndex)
{
    gmsgsourceindex = iIndex;
    clickCnt = 0;
    return;
}

/**
 * @brief BitView::getSync
 * @return 返回加锁是否成功
 * @note 准备获取共享内存内容  加锁定标志防止卡
 */
qint32 BitView::getSync()
{
    return pthread_mutex_lock(&glockobj);
}

/**
 * @brief BitView::showBoarderLine
 * @note显示边框线
 */
void BitView::showBoarderLine()
{
    QPainter painter(&gpixmap);
    painter.initFrom(this);

    gbitpen.setColor(mPenColor.gridPart);
    gbitpen.setWidth(LINEREEOR);
    if(gplugindex == gmsgsourceindex
       && gsystemstate.windowtype == BIT_MULTIWINDOW)
    {
        gboarderpen.setWidth(LINEREEOR);
        gboarderpen.setColor(mBoardColor.curBoardLine);
    }else
    {
        gboarderpen.setWidth(LINEREEOR);
        gboarderpen.setColor(mPenColor.background);
    }
    renderBoaderLines(&gbitpen,&painter);
//    this->repaint(rect());
    return;
}
/**
 * @brief BitView::HideBoardLine
 * @note 隐藏边框线
 */
void BitView::HideBoardLine()
{
    QPainter painter(&gpixmap);
    painter.initFrom(this);

    gbitpen.setColor(mPenColor.gridPart);
    gbitpen.setWidth(LINEREEOR);

    gboarderpen.setColor(mPenColor.background);
    renderBoaderLines(&gbitpen,&painter);

    return;
}
/**
 * @brief BitView::showLeftPart
 * @note 显示左侧Y轴部分
 */
void BitView::showLeftPart()
{
    QPainter painter(&gpixmap);
    QBrush mbrush(mPenColor.background);
    painter.setBrush(mbrush);
    painter.drawRect(BITWORDLEFT,TOPDIS,WORDWIDTH,gusedsize.gpicheight);
    renderLeftPart(&painter);
    return;
}

/**
 * @brief BitView::releaseSync
 * @return 返回释放锁标志
 * @note 释放共享内存锁
 */
qint32 BitView::releaseSync()
{
    return pthread_mutex_unlock(&glockobj);
}

/**
 * @brief BitView::renderGridLines
 * @param pPainter
 * @note 绘制右边曲线边框网格线
 */
void BitView::renderGridLines(QPainter *pPainter)
{
    //Tony 1101. Modify the render policy.
    qreal painterLeft = CenterPartRect.left();
    qreal painterRight = CenterPartRect.right();
    qreal painterTop = CenterPartRect.top();
    qreal painterBottom = CenterPartRect.bottom();

    //bound color
    renderBoaderLines(&gbitpen,pPainter);
    gbitpen.setWidth(LINEREEOR);
    gbitpen.setColor(mPenColor.gridPart);
    pPainter->setPen(gbitpen);

    //out hard grid
    pPainter->drawLine(QPointF(painterLeft - HALFLINEREEOR,painterTop -  HALFLINEREEOR),QPointF(painterRight + HALFLINEREEOR,painterTop -  HALFLINEREEOR));
    pPainter->drawLine(QPointF(painterRight+ HALFLINEREEOR,painterTop -  HALFLINEREEOR),QPointF(painterRight + HALFLINEREEOR,painterBottom +  HALFLINEREEOR));
    pPainter->drawLine(QPointF(painterLeft - HALFLINEREEOR,painterBottom +  HALFLINEREEOR),QPointF(painterRight + HALFLINEREEOR,painterBottom +  HALFLINEREEOR));
    pPainter->drawLine(QPointF(painterLeft - HALFLINEREEOR,painterTop -  HALFLINEREEOR),QPointF(painterLeft - HALFLINEREEOR,painterBottom +  HALFLINEREEOR));
    gbitpen.setWidth(HALFLINEREEOR);
    gbitpen.setColor(mPenColor.gridPart);
    pPainter->setPen(gbitpen);

    qint32 i = 0;
    for(i = 1;i < GRIDNUM;i++)
    {
        //level grid
        pPainter->drawLine(QPointF(painterLeft - HALFLINEREEOR,gusedsize.gridY[i]),QPointF(painterRight,gusedsize.gridY[i]));
        //vertical grid
        pPainter->drawLine(QPointF(gusedsize.gridX[i],painterTop - HALFLINEREEOR),QPointF(gusedsize.gridX[i],painterBottom));
    }
    return;
}

void BitView::renderSpectrogramGridLines(QPainter *pPainter)
{
    //Tony 1101. Modify the render policy.
    qreal painterLeft = CenterPartRect.left();
    qreal painterRight = CenterPartRect.right();
    qreal painterTop = CenterPartRect.top();
    qreal painterBottom = CenterPartRect.bottom();

    //bound color
    renderBoaderLines(&gbitpen,pPainter);
    gbitpen.setWidth(LINEREEOR);
    gbitpen.setColor(mPenColor.gridPart);
    pPainter->setPen(gbitpen);

    //out hard grid
    pPainter->drawLine(QPointF(painterLeft - LINEREEOR,painterTop - LINEREEOR),QPointF(painterRight + LINEREEOR,painterTop - LINEREEOR));
    pPainter->drawLine(QPointF(painterRight+ LINEREEOR,painterTop - LINEREEOR),QPointF(painterRight + LINEREEOR,painterBottom + LINEREEOR));
    pPainter->drawLine(QPointF(painterLeft - LINEREEOR,painterBottom + LINEREEOR),QPointF(painterRight + LINEREEOR,painterBottom + LINEREEOR));
    pPainter->drawLine(QPointF(painterLeft - LINEREEOR,painterTop - LINEREEOR),QPointF(painterLeft - LINEREEOR,painterBottom + LINEREEOR));
    return;
}

/**
 * @brief BitView::renderBoaderLines
 * @param mpen
 * @param mpainter
 * @note 绘制边框线
 */
void BitView::renderBoaderLines(QPen *mpen,QPainter* mpainter)
{
    mpainter->setPen(gboarderpen);

    mpainter->drawLine(QPointF(LINEREEOR,LINEREEOR),
                       QPointF(this->width()-LINEREEOR,LINEREEOR));

    mpainter->drawLine(QPointF(this->width()-LINEREEOR,LINEREEOR),
                       QPointF(this->width()-LINEREEOR,this->height()-LINEREEOR ));

    mpainter->drawLine(QPointF(this->width()-LINEREEOR ,this->height()-LINEREEOR),
                       QPointF(LINEREEOR,this->height()-LINEREEOR));

    mpainter->drawLine(QPointF(LINEREEOR,this->height() - LINEREEOR),
                       QPointF(LINEREEOR,LINEREEOR));

    mpen->setWidth(LINEREEOR);
    mpen->setColor(mBoardColor.edgeArea);
    mpainter->setPen(*mpen);
    mpainter->drawRect(0,0,this->width(),this->height());
    return;
}
//Tony 1016 Add
void BitView::setAmptdUnit(qint32 unit)
{
    gAmptdUnit = unit;
    return ;
}
qint32 BitView::getAmptUnit()
{
    return gAmptdUnit;
}

//Tony 1022 Add
void BitView::setAmptdAttribute(qint32 attributeType, qreal attribute)
{
    switch (attributeType) {
    case BIT_AMPTD_REF:
        gusedsize.grefValue = attribute;
        refreshSepectrogramRect();
        break;
    case BIT_AMPTD_DIV:
        gusedsize.gdivValue = attribute;
        refreshSepectrogramRect();
        break;
    case BIT_AMPTD_OFFSET:
        gusedsize.goffsetValue = attribute;
        break;
    }
    return ;
}
//Tony 1024 Add
qreal BitView::getAmptdAttribute(qint32 attributeType)
{
    switch (attributeType)
    {
    case BIT_AMPTD_REF:
        return gusedsize.grefValue;
        break;
    case BIT_AMPTD_DIV:
        return gusedsize.gdivValue;
        break;
    case BIT_AMPTD_OFFSET:
        return gusedsize.goffsetValue;
        break;
    }
    return 0;
}

void BitView::setBitviewType(qint32 type)
{
    mBitviewType = type;
    switch (type) {
    case BIT_SPECTRUM:
        gwordset.gtscstr = "Spectrum";
        break;
     case   BIT_DENSITY:
        gwordset.gtscstr = "Density";
        break;
    case BIT_SPECTROGRAM:
        gwordset.gtscstr = "Spectrogram";
        break;
    }
    misDoubleClicked = false;
    return ;
}

qint32 BitView::getBitviewType()
{
    return mBitviewType;
}

//Albert 1017 Add
//void BitView::drawSpectrogram(QPainter *painter)
//{
//#if 0
//    qint32 nLeft = LEFTDIS;
//    qint32 nTop = TOPDIS;
//    qint32 nWidth = this->width() - LEFTDIS - RIGHTDIS;
//    qint32 nHeigth = 10* (this->height() - (BOTTOMDIS + gsystemstate.windowtype * markerTabelVisiable * BIT_MARKER_TABLE_HEIGHT) - TOPDIS)/10 - LINEREEOR;

//    qint32 nRight = nWidth;
//    qint32 nBottom = nHeigth;
//    QPen newpen(Qt::white);
//    QPen newpen1(Qt::yellow);
//    //    newpen.setWidth(1);
//    quint32 uColorValue = 0xffffffff;
//    //    uchar Red, Green, Blue;
//    QImage ChangeImage;
//    QPainter pp(&pixmapnew);
//    pp.fillRect(nLeft + 1,nTop,nWidth,nHeigth,Qt::transparent);

//    painter->initFrom(this);


//    QPointF ptTemp,ptTemp1;
//    //    ChangeImage = QImage(nRight,nTop + nHeigth,QImage::Format_ARGB32);
//    QPen penSel;
//    qint32 colindex = 0;

//    qreal dataTemp = gbitbuffer.trace_render[gctrlmana->gtraceIndex][0];
//    bool mIsDataChange = false;
//#if 1
//    for(quint32 i = 0 ; i < gbitbuffer.gtracenum - 1; i++)
//    {
//        //Albert 0929 if trace number larger than pixel width, need extract
//        //! Albert Delete 1017. drawpointsX is double. no equal occasion.
//        //! when drawpointsX use int, should use equal compare
//        if(gbitbuffer.gtracenum > nWidth)
//        {
//            if(!mIsDataChange)
//                dataTemp = gbitbuffer.trace_render[gctrlmana->gtraceIndex][i];
//            //            if((i == 1) || (i == 301) || (i == 35) || (i == 70) || (i == 107))
//            //                dataTemp += 53.5;
//            if((floor)(gbitbuffer.drawpointsX[i]) == (floor)(gbitbuffer.drawpointsX[i + 1]))
//            {
//                mIsDataChange = true;
//                dataTemp = dataTemp < gbitbuffer.trace_render[gctrlmana->gtraceIndex][i] ? gbitbuffer.trace_render[gctrlmana->gtraceIndex][i] : dataTemp;
//            }
//            else
//            {
//                //! Albert 1017 if data changed, cur pos do not need draw.
//                if(mIsDataChange)
//                {
//                    mIsDataChange = false;
//                    continue;
//                }
//            }
//        }
//        else
//        {
//            dataTemp = gbitbuffer.trace_render[gctrlmana->gtraceIndex][i];
//        }
//        ptTemp.setX(gbitbuffer.drawpointsX[i] - nLeft);
//        ptTemp.setY(nBottom);
//        ptTemp1.setX(gbitbuffer.drawpointsX[i + 1] - nLeft);
//        ptTemp1.setY(nBottom);
//        colindex = (qint32)((-dataTemp + gusedsize.grefValue) * SPECTROGRAM_COLBAR_NUM * 0.1 / gusedsize.gdivValue);
//        if(colindex < 0)
//            colindex = 0;
//        else if(colindex > SPECTROGRAM_COLBAR_NUM - 1)
//            colindex = SPECTROGRAM_COLBAR_NUM - 1;

//        uColorValue = rgbBuffer[colindex];
//        penSel = QPen(QColor(QRgb(uColorValue)));
//        pp.setPen(penSel);
//        pp.drawLine(ptTemp,ptTemp1);
//    }
//#endif

//    pp.drawPixmap(0,-1,pixmapnew);
//    painter->drawPixmap(nLeft + 1,nTop + 1,nWidth - 2,nBottom,pixmapnew,0,0,nWidth - 2,nBottom);
//#endif
//    return;
//}

void BitView::drawSpectrogramSmallPix(QPainter *painter)
{
    qint32 nLeft = LEFTDIS;
    qint32 nTop = TOPDIS;
    qint32 nWidthSmall = pixmapnewSmall.width() - LEFTDIS - RIGHTDIS - HALFLINEREEOR;
    qint32 nHeigthSmall = 10* (pixmapnewSmall.height() - (BOTTOMDIS + gsystemstate.windowtype * markerTabelVisiable * BIT_MARKER_TABLE_HEIGHT) - TOPDIS- HALFLINEREEOR)/10;

//    qint32 nRightSmall = nWidthSmall;
    qint32 nBottomSmall = nHeigthSmall;
    QPen newpen(Qt::white);
    quint32 uColorValue = 0xffffffff;
    QPainter ppSmall(&pixmapnewSmall);

    ppSmall.fillRect(0,nTop,nWidthSmall,nHeigthSmall,Qt::transparent);

    painter->initFrom(this);

    QPointF ptTempSmall,ptTempSmall1;
    QPen penSel;
    qint32 colindex = 0;

    qreal dataTemp = gbitbuffer.trace_render[gctrlmana->gtraceIndex][0];
    bool mIsDataChange = false;
  #if 1
    for(quint32 i = 0 ; i < gbitbuffer.gtracenum/* - 1*/; i++)
    {
        //Albert 0929 if trace number larger than pixel width, need extract
        //! Albert Delete 1017. drawpointsX is double. no equal occasion.
        //! when drawpointsX use int, should use equal compare
        if(gbitbuffer.gtracenum > (quint32)nWidthSmall)
        {
            if(i == gbitbuffer.gtracenum - 1)
            {
                dataTemp = gbitbuffer.trace_render[gctrlmana->gtraceIndex][i];
            }
            else
            {
                if(!mIsDataChange)
                    dataTemp = gbitbuffer.trace_render[gctrlmana->gtraceIndex][i];
                if((floor)(gbitbuffer.drawSpectroPointsSmallX[i]) == (floor)(gbitbuffer.drawSpectroPointsSmallX[i + 1]))
                {
                    mIsDataChange = true;
                    dataTemp = dataTemp < gbitbuffer.trace_render[gctrlmana->gtraceIndex][i + 1] ? gbitbuffer.trace_render[gctrlmana->gtraceIndex][i + 1] : dataTemp;
                }
                else
                {
                    //! Albert 1017 if data changed, cur pos do not need draw.
                    if(mIsDataChange)
                    {
                        mIsDataChange = false;
                        continue;
                    }
                }
            }
        }
        else
        {
             dataTemp = gbitbuffer.trace_render[gctrlmana->gtraceIndex][i];
        }
//        dataTemp = dataTemp - gusedsize.goffsetValue;
        if(i == gbitbuffer.gtracenum - 1)
        {
            ptTempSmall.setX((floor)(gbitbuffer.drawSpectroPointsSmallX[i]) - nLeft);
            ptTempSmall.setY(nBottomSmall);
            ptTempSmall1.setX((floor)(gbitbuffer.drawSpectroPointsSmallX[i]) - nLeft);
            ptTempSmall1.setY(nBottomSmall);
        }
        else
        {
            ptTempSmall.setX(gbitbuffer.drawSpectroPointsSmallX[i] - nLeft);
            ptTempSmall.setY(nBottomSmall);
            ptTempSmall1.setX(gbitbuffer.drawSpectroPointsSmallX[i + 1] - nLeft);
            ptTempSmall1.setY(nBottomSmall);
        }
        colindex = (qint32)((-dataTemp + gusedsize.grefValue/* + gusedsize.goffsetValue*/) * SPECTROGRAM_COLBAR_NUM * 0.1 / gusedsize.gdivValue);
        if(colindex < 0)
            colindex = 0;
        else if(colindex > SPECTROGRAM_COLBAR_NUM - 1)
            colindex = SPECTROGRAM_COLBAR_NUM - 1;

        uColorValue = rgbBuffer[colindex];
        penSel = QPen(QColor(QRgb(uColorValue)));
        //! draw small
        ppSmall.setPen(penSel);
        ppSmall.drawLine(ptTempSmall,ptTempSmall1);
    }
  #endif
    //! move small
    ppSmall.drawPixmap(0,-1,pixmapnewSmall);
//    if(gbitbuffer.gtracenum > this->width())
        if((quint32)(this->width()) <= gbitbuffer.gtracenum)
       {
        painter->drawPixmap(nLeft ,nTop ,nWidthSmall ,nBottomSmall,pixmapnewSmall,0,0,nWidthSmall,nBottomSmall);
    }
    return;

}

void BitView::drawSpectrogramBigPix(QPainter *painter)
{
    qint32 nLeft = LEFTDIS;
    qint32 nTop = TOPDIS;
    qint32 nWidthBig = pixmapnewBig.width() - LEFTDIS - RIGHTDIS - HALFLINEREEOR;
    qint32 nHeigthBig = 10* (pixmapnewBig.height() - (BOTTOMDIS + gsystemstate.windowtype * markerTabelVisiable * BIT_MARKER_TABLE_HEIGHT) - TOPDIS- HALFLINEREEOR)/10;
//    qint32 nRightBig = nWidthBig;
    qint32 nBottomBig = nHeigthBig;
    QPen newpen(Qt::white);
    quint32 uColorValue = 0xffffffff;
    QPainter ppBig(&pixmapnewBig);

    ppBig.fillRect(0,nTop,nWidthBig,nHeigthBig,Qt::transparent);

    painter->initFrom(this);


    QPointF ptTempBig,ptTempBig1;
    QPen penSel;
    qint32 colindex = 0;

    qreal dataTemp = gbitbuffer.trace_render[gctrlmana->gtraceIndex][0];
  #if 1
    for(quint32 i = 0 ; i < gbitbuffer.gtracenum; i++)
    {
        dataTemp = gbitbuffer.trace_render[gctrlmana->gtraceIndex][i];
        if(i == gbitbuffer.gtracenum - 1)
        {
            ptTempBig.setX((floor)(gbitbuffer.drawSpectroPointsBigX[i]) - nLeft - 1);
            ptTempBig.setY(nBottomBig);
            ptTempBig1.setX((floor)(gbitbuffer.drawSpectroPointsBigX[i]) - nLeft - 1);
            ptTempBig1.setY(nBottomBig);
        }
        else
        {
            ptTempBig.setX(gbitbuffer.drawSpectroPointsBigX[i] - nLeft);
            ptTempBig.setY(nBottomBig);
            ptTempBig1.setX(gbitbuffer.drawSpectroPointsBigX[i + 1] - nLeft);
            ptTempBig1.setY(nBottomBig);
        }
        colindex = (qint32)((-dataTemp + gusedsize.grefValue/* + gusedsize.goffsetValue*/) * SPECTROGRAM_COLBAR_NUM * 0.1 / gusedsize.gdivValue);
        if(colindex < 0)
            colindex = 0;
        else if(colindex > SPECTROGRAM_COLBAR_NUM - 1)
            colindex = SPECTROGRAM_COLBAR_NUM - 1;

        uColorValue = rgbBuffer[colindex];
        penSel = QPen(QColor(QRgb(uColorValue)));
         //! draw Big
        ppBig.setPen(penSel);
        ppBig.drawLine(ptTempBig,ptTempBig1);
    }
  #endif
    //! move Big
    ppBig.drawPixmap(0,-1,pixmapnewBig);

//    if(gbitbuffer.gtracenum < this->width())
//    qint32 a = this->width();
    if((quint32)(this->width()) > gbitbuffer.gtracenum)
        painter->drawPixmap(nLeft ,nTop ,nWidthBig,nBottomBig,pixmapnewBig,0,0,nWidthBig ,nBottomBig);
    return;
}

/**
 * @brief BitView::produceColorBar
 * @param displaymode 显示模式
 * @note 设置颜色
 */
void BitView::produceColorBar(qint32 displaymode)
{
    quint32 uColorValue = 0xff000000;
    qint32 uRValue     = 0;
    qint32 uGValue     = 0;
    qint32 uBValue     = 0xff;
    qint32 uColorLevel = SPECTROGRAM_COLBAR_NUM;
    float dcurveValue = 1.;

    qint32 value_Average = qRound((qreal)255*4/uColorLevel);

    if(displaymode == BIT_OUTDOORMODE)
    {
        uRValue = 0xff;
        uGValue = 0xff;
        uBValue = 0xff;
        value_Average = qRound((qreal)255/uColorLevel);
        for(qint32 i = 0;i < uColorLevel;i++)
        {
            uRValue = uRValue - value_Average;
            uGValue = uGValue - value_Average;
            uBValue = uBValue - value_Average;
            uColorValue = (uColorValue&0xff000000)+(uRValue<<16)+(uGValue<<8)+uBValue;
            rgbBuffer[SPECTROGRAM_COLBAR_NUM - i - 1] = uColorValue;
        }
    }
    else if(displaymode == BIT_NIGHTMODE)
    {
        uRValue = 0xff;
        uGValue = 0xff;
        uBValue = 0;
        value_Average = qRound((qreal)255/uColorLevel);
        for(qint32 i = 0;i < uColorLevel;i++)
        {
//            uRValue = uRValue - value_Average;
            uGValue = uGValue - value_Average;
//            uBValue = uBValue - value_Average;
            uColorValue = (uColorValue&0xff000000)+(uRValue<<16)+(uGValue<<8)+uBValue;
            rgbBuffer[SPECTROGRAM_COLBAR_NUM - i - 1] = uColorValue;
        }
    }
    else
    {
        for(qint32 i = 0;i < uColorLevel;i++)
        {
            if(0xff == uBValue && 0xff>uGValue && 0 == uRValue){
                if(1.0 == dcurveValue)
                    uGValue += value_Average;
                if(uGValue > 0xff)
                    uGValue = 0xff;
            }
            else if(0<uBValue && 0xff == uGValue && 0 == uRValue){
                if(1.0 == dcurveValue)
                    uBValue -= value_Average;
                if(uBValue<0)
                    uBValue = 0;
            }
            else if(0 == uBValue && 0xff == uGValue && 0xff>uRValue){
                if(1.0 == dcurveValue)
                    uRValue += value_Average;
                if(uRValue>0xff)
                    uRValue = 0xff;

            }
            else if(0 == uBValue && 0<uGValue && 0xff == uRValue){
                if(1.0 == dcurveValue)
                    uGValue -= value_Average;
                if(uGValue<0)
                    uGValue = 0;
            }

            uColorValue = (uColorValue&0xff000000)+(uRValue<<16)+(uGValue<<8)+uBValue;
            rgbBuffer[SPECTROGRAM_COLBAR_NUM - i - 1] = uColorValue;
        }
    }
    return;
}


void BitView::renderSpectrogramColBar(QPainter *pPainter)
{
    //    quint32 uColorValue = 0xff000000;
    //      qint32 uRValue     = 0;
    //      qint32 uGValue     = 0;
    //      qint32 uBValue     = 0xff;
    //      float dcurveValue = 1.;
    qint32 uColorLevel = SPECTROGRAM_COLBAR_NUM;
    QString mstr;
    qreal colBarHeight = this->height() - TOPDIS - (BOTTOMDIS + gsystemstate.windowtype * markerTabelVisiable * BIT_MARKER_TABLE_HEIGHT) - LINEREEOR - WORDHEIGHT;
    qreal colBarBottom = this->height() - WORDHEIGHT * 0.5;
    qreal mcolordiv = colBarHeight/uColorLevel;
    //#if 0
    //      if(!misMoreThanOneWin)
    //      {
    //          colBarBottom = (qreal) (7 * colBarHeight * 0.1 + TOPDIS + (BOTTOMDIS + gsystemstate.windowtype * markerTabelVisiable * BIT_MARKER_TABLE_HEIGHT) + LINEREEOR) - WORDHEIGHT * 0.5;
    //          colBarHeight = (qreal) (7 * colBarHeight * 0.1) - WORDHEIGHT;
    //      }
    //#endif
    //      qint32 value_Average = qRound((qreal)255*4/uColorLevel);
    //      qint32 value_NotAverage = qRound(255*4/uColorLevel*dcurveValue);

    for(qint32 i = 0;i < uColorLevel;i++)
    {
        //          if(0xff == uBValue && 0xff>uGValue && 0 == uRValue){
        //              if(1.0 == dcurveValue)
        //                  uGValue += value_Average;
        //              if(uGValue > 0xff)
        //                  uGValue = 0xff;
        //          }
        //          else if(0<uBValue && 0xff == uGValue && 0 == uRValue){
        //              if(1.0 == dcurveValue)
        //                  uBValue -= value_Average;
        //              if(uBValue<0)
        //                  uBValue = 0;
        //          }
        //          else if(0 == uBValue && 0xff == uGValue && 0xff>uRValue){
        //              if(1.0 == dcurveValue)
        //                  uRValue += value_Average;
        //             if(uRValue>0xff)
        //                 uRValue = 0xff;

        //          }
        //          else if(0 == uBValue && 0<uGValue && 0xff == uRValue){
        //              if(1.0 == dcurveValue)
        //                  uGValue -= value_Average;
        //              if(uGValue<0)
        //                  uGValue = 0;
        //          }

        //          uColorValue = (uColorValue&0xff000000)+(uRValue<<16)+(uGValue<<8)+uBValue;
        //          rgbBuffer[SPECTROGRAM_COLBAR_NUM - i - 1] = uColorValue;
        const QColor color = QColor(QRgb(rgbBuffer[SPECTROGRAM_COLBAR_NUM - i - 1]));
        QRectF rctF(BITWORDLEFT + 20, (colBarBottom - TOPDIS - LINEREEOR) - i*mcolordiv,10,mcolordiv);
        QBrush brush(color);

        pPainter->fillRect(rctF,brush);
    }
#if 0
    qreal mspectrogramHeight = 7 * (this->height()- (BOTTOMDIS + gsystemstate.windowtype * markerTabelVisiable * BIT_MARKER_TABLE_HEIGHT) - TOPDIS) * 0.1;
    if(misMoreThanOneWin)
        mspectrogramHeight = 0;
#endif
    QPen bvpen;
    bvpen.setWidth(LINEREEOR);
    bvpen.setColor(mPenColor.colBarFont);
    pPainter->setPen(bvpen);
    pPainter->setFont(QFont("Arial", 8));

    qreal mbaselevel = gusedsize.grefValue + gusedsize.goffsetValue;
    qreal mdiv = fabs(gusedsize.gdivValue);
    //      qreal mdivpix = 0.2 * (this->height()- (BOTTOMDIS + gsystemstate.windowtype * markerTabelVisiable * BIT_MARKER_TABLE_HEIGHT) - TOPDIS - mspectrogramHeight);
    qreal mval = 0.0;
    mval = mbaselevel;
    mstr = QString("dBm");
    pPainter->drawText(BITWORDLEFT - 5, BITWORDHSET + TOPDIS - 3 * RIGHTDIS, WORDWIDTH, WORDHEIGHT, Qt::AlignRight, mstr);

    mstr = QString("%1").sprintf("%.2lf",mval);
    pPainter->drawText(BITWORDLEFT - 5, BITWORDHSET + TOPDIS - 1.5 * RIGHTDIS, WORDWIDTH, WORDHEIGHT, Qt::AlignRight, mstr);

    mval = mbaselevel - mdiv * 10;
    mstr = QString("%1").sprintf("%.2lf",mval);
    pPainter->drawText(BITWORDLEFT, colBarBottom - (BOTTOMDIS + gsystemstate.windowtype * markerTabelVisiable * BIT_MARKER_TABLE_HEIGHT) + 8 * LINEREEOR, WORDWIDTH, WORDHEIGHT, Qt::AlignRight, mstr);
    return;
}
void BitView::drawDensityColBar(QPainter *pPainter)
{
    qint32 uColorLevel = SPECTROGRAM_COLBAR_NUM;
    QString mstr;
    qreal colBarHeight = this->height() - TOPDIS - (BOTTOMDIS + gsystemstate.windowtype * markerTabelVisiable * BIT_MARKER_TABLE_HEIGHT) - LINEREEOR - WORDHEIGHT;
    qreal colBarBottom = this->height() - WORDHEIGHT * 0.5;
    qreal mcolordiv = colBarHeight/uColorLevel;
    for(qint32 i = 0;i < uColorLevel;i++)
    {
        const QColor color = QColor(QRgb(rgbBuffer[SPECTROGRAM_COLBAR_NUM - i - 1]));
        QRectF rctF(BITWORDLEFT - 3, (colBarBottom - TOPDIS - LINEREEOR) - i*mcolordiv,10,mcolordiv);
        QBrush brush(color);

        pPainter->fillRect(rctF,brush);
    }
    QPen bvpen;
    bvpen.setWidth(LINEREEOR);
    bvpen.setColor(mPenColor.colBarFont);
    pPainter->setPen(bvpen);
    pPainter->setFont(QFont("Arial", 8));

//    qreal mbaselevel = gusedsize.grefValue;
//    qreal mdiv = fabs(gusedsize.gdivValue);
//    qreal mval = mbaselevel;
//    mval = mbaselevel;

//    mstr = QString("%1").sprintf("%.2lf\%",mval);
    mstr = QString("100%");
    pPainter->drawText(BITWORDLEFT - 4, BITWORDHSET + TOPDIS - RIGHTDIS, WORDWIDTH, WORDHEIGHT, Qt::AlignLeft, mstr);

//    mval = mbaselevel - mdiv * 10;
//    mstr = QString("%1").sprintf("%.2lf\%",mval);
    mstr = QString("0%");
    pPainter->drawText(BITWORDLEFT, colBarBottom - (BOTTOMDIS + gsystemstate.windowtype * markerTabelVisiable * BIT_MARKER_TABLE_HEIGHT) + LINEREEOR, WORDWIDTH, WORDHEIGHT, Qt::AlignLeft, mstr);
    return;
}
void BitView::refreshSepectrogramRect()
{
//    pixmapnew.fill(mPenColor.background);
    pixmapnewSmall.fill(mPenColor.background);
    pixmapnewBig.fill(mPenColor.background);
    mCacheRealNum = 0;
    mCacheDataStartPos = 0;
    mDensityArrayStartPos = 0;
    mDensityArrayTotalNum = 0;
    return;
}

uchar* BitView::getDensityData(qint32 dataNum)
{
    if(dataNum != DPX_WIDTH_SIZE * DPX_HEIGHT_SIZE * 4)
        dataNum = DPX_WIDTH_SIZE * DPX_HEIGHT_SIZE * 4;
    return gctrlmana->uFmtRGB;
}

void BitView::setDensityData(qreal *pTraceData, uchar *pData)
{
    getSync();
    memcpy(gctrlmana->uFmtRGB,pData,sizeof(uchar) * DPX_WIDTH_SIZE * DPX_HEIGHT_SIZE * 4);
    imageFromData = QImage(gctrlmana->uFmtRGB,DPX_WIDTH_SIZE,DPX_HEIGHT_SIZE,QImage::Format_RGB32);
    memcpy(gbitbuffer.trace_ori,pTraceData,sizeof(qreal) * gbitbuffer.gtracenum);
    gsigrendermap.fill(Qt::transparent);
    QPainter painter(&gsigrendermap);
    painter.initFrom(this);
    renderDensityPart(&painter);
    releaseSync();
    return;
}
void BitView::initSpectrogramCacheDataArray(qreal *pBuffer)
{
    if(mCacheData != NULL)
    {
        return;
    }
    mCacheData = pBuffer;
    //! Albert 1019, initial cache data array, here must store begin pointer.
    mStartPos = pBuffer;
    refreshSepectrogramRect();
    return;
}
void BitView::cacheData(qreal *pDis, qreal *pSrc, qint32 Num)
{
    memcpy(pDis,pSrc,sizeof(qreal) * Num);
    return;
}
quint32 BitView::getRealCacheDataNum()
{
    return mCacheRealNum;
}
quint32 BitView::getCacheDataStartPos()
{
    return mCacheDataStartPos;
}
void BitView::drawCurTraceIndex(QPainter *painter, quint32 nCurIndex)
{
    //! Albert 1019, draw current trace num
    QString str;
    gbitpen.setColor(mPenColor.curTraceIndex);
    gbitpen.setWidth(1);
    qint32 nLeft = LEFTDIS;
    qint32 nWidth = this->width() - LEFTDIS - RIGHTDIS-HALFLINEREEOR;
    qint32 nHeigth = this->height() - (BOTTOMDIS + gsystemstate.windowtype * markerTabelVisiable * BIT_MARKER_TABLE_HEIGHT) - TOPDIS - LINEREEOR;
    qint32 nDrawPos = nCurIndex;
    if(nDrawPos > nHeigth)
        nDrawPos = nHeigth;
    QRectF rectDownBelow(nLeft + 1,nHeigth + TOPDIS - nDrawPos,100,20);
    QRectF rectUpTop(nLeft + 1,nHeigth + TOPDIS - nDrawPos - 20,100,20);
    painter->setPen(gbitpen);
    //!draw cur trace line
    if(nDrawPos < nHeigth)
    {
        painter->drawLine(nLeft ,nHeigth + TOPDIS - nDrawPos,nLeft + 1 + nWidth - 2,nHeigth + TOPDIS - nDrawPos);
    }
    //!draw cur trace num
    painter->setFont(QFont("Arial", 10));
    str.sprintf("%d",nDrawPos);
    if(nDrawPos < nHeigth - 20)
    {
        gbitpen.setWidth(2);
        painter->setPen(gbitpen);
        painter->drawText(rectUpTop,Qt::AlignBottom,str);
    }
    else
    {
        gbitpen.setColor(Qt::black);
        gbitpen.setWidth(2);
        painter->setPen(gbitpen);
        painter->drawText(rectDownBelow,Qt::AlignTop,str);
    }
    return;
}
//Tony 1022 Add
void BitView::dbmToVoltCalculatorAndDisplayFunc(char *label, qreal _level)
{
    qreal voltGab = 0.;
    qreal calculator = 0.;

    calculator = pow(10, _level / 10.);
    voltGab = 1000000. * pow(50 * calculator * 0.001, 0.5);//uv

    //Johnson 0919 Change
    if(voltGab >= 1000000000.){
        sprintf(label, "%.2f kV", (qreal) voltGab / 1000000000.);
    }
    else if (/*_level <= 20. &&*/ voltGab >= 1000000.) {
        sprintf(label, "%.2f V", (qreal) voltGab / 1000000.);
    } else if (voltGab < 1000000. && voltGab >= 1000.) {
        sprintf(label, "%.2f mV", (qreal) voltGab / 1000.);
    } else if (voltGab < 1000. && voltGab >= 1.) {
        sprintf(label, "%.2f uV", (qreal) voltGab);
    } else if (voltGab < 1. && voltGab >= 0.001) {
        sprintf(label, "%.2f nV", (qreal) voltGab * 1000);
    } else if (voltGab < 0.001 && voltGab >= 0.000001) {
        sprintf(label, "%.2f pV", (qreal) voltGab * 1000000.);
    } else if (voltGab < 0.000001 && voltGab >= 0.000000001) {
        sprintf(label, "%.2f fV", (qreal) voltGab * 1000000000.);
    } else if (voltGab < 0.000000001 && voltGab >= 0.000000000001) {
        sprintf(label, "%.2f aV", (qreal) voltGab * 1000000000000.);
    } else if (voltGab < 0.000000000001 && voltGab >= 0.000000000000001) {
        sprintf(label, "%.2f zV", (qreal) voltGab * 1000000000000000.);
    } else if (voltGab < 0.000000000000001 && voltGab >= 0.000000000000000001) {
        sprintf(label, "%.2f yV", (qreal) voltGab * 1000000000000000000.);
    } else {
        sprintf(label, "%.2f", (qreal) voltGab * 1000000000000000000000.);
    }
    return;
}

qreal BitView::dbmToVoltCalculator(qreal _level)
{
    qreal voltGab = 0.;
    qreal calculator = 0.;

    calculator = pow(10, _level / 10.);
    voltGab = 1000000. * pow(50 * calculator * 0.001, 0.5);//uv

    //Johnson 0919 Change
    if(voltGab >= 1000000000.){
         voltGab = (qreal) voltGab / 1000000000.;
    }
    else if (/*_level <= 20. &&*/ voltGab >= 1000000.) {
        voltGab =  (qreal) voltGab / 1000000.;
    } else if (voltGab < 1000000. && voltGab >= 1000.) {
        voltGab =  (qreal) voltGab / 1000.;
    } else if (voltGab < 1000. && voltGab >= 1.) {
        voltGab =  (qreal) voltGab;
    } else if (voltGab < 1. && voltGab >= 0.001) {
        voltGab =  (qreal) voltGab * 1000;
    } else if (voltGab < 0.001 && voltGab >= 0.000001) {
        voltGab =  (qreal) voltGab * 1000000.;
    } else if (voltGab < 0.000001 && voltGab >= 0.000000001) {
        voltGab =  (qreal) voltGab * 1000000000.;
    } else if (voltGab < 0.000000001 && voltGab >= 0.000000000001) {
        voltGab =  (qreal) voltGab * 1000000000000.;
    } else if (voltGab < 0.000000000001 && voltGab >= 0.000000000000001) {
        voltGab =  (qreal) voltGab * 1000000000000000.;
    } else if (voltGab < 0.000000000000001 && voltGab >= 0.000000000000000001) {
        voltGab =  (qreal) voltGab * 1000000000000000000.;
    } else {
        voltGab =  (qreal) voltGab * 1000000000000000000000.;
    }
    return voltGab;
}

//Tony 1022 Add
void BitView::dbmToWattsCalculatorAndDisplayFunc(char *label, qreal _level)
{
    qreal wattsGab = 0.;

    wattsGab = pow(10, _level / 10.);

    if (wattsGab >= 1000) {						// W
        sprintf(label, "%.2f W", (qreal)wattsGab / 1000.0);
    }  else if (wattsGab >= 1) {					// mW
        sprintf(label, "%.2f mW", (qreal)wattsGab);
    }  else if (wattsGab >= 0.001) {				// uW
        sprintf(label, "%.2f uW", (qreal)wattsGab * 1000.0);
    }  else if (wattsGab >= 0.000001) {			// nW
        sprintf(label, "%.2f nW", (qreal)wattsGab * 1000000.0);
    } else if (wattsGab >= 0.000000001) {			// pW
        sprintf(label, "%.2f pW", (qreal)wattsGab * 1000000000.0);
    } else if (wattsGab >= 0.000000000001) {		// fW
        sprintf(label, "%.2f fW", (qreal)wattsGab * 1000000000000.0);
    } else {                                                    	// aW
        sprintf(label, "%.2f aW", (qreal)wattsGab * 1000000000000000.0);
    }
}

qreal BitView::dbmToWattsCalculator(qreal _level)
{
    qreal wattsGab = 0.;

    wattsGab = pow(10, _level / 10.);

    if (wattsGab >= 1000) {						// W
        wattsGab = (qreal)wattsGab / 1000.0;
    }  else if (wattsGab >= 1) {					// mW
        wattsGab = (qreal)wattsGab;
    }  else if (wattsGab >= 0.001) {				// uW
        wattsGab = (qreal)wattsGab * 1000.0;
    }  else if (wattsGab >= 0.000001) {			// nW
        wattsGab = (qreal)wattsGab * 1000000.0;
    } else if (wattsGab >= 0.000000001) {			// pW
        wattsGab = (qreal)wattsGab * 1000000000.0;
    } else if (wattsGab >= 0.000000000001) {		// fW
        wattsGab = (qreal)wattsGab * 1000000000000.0;
    } else {                                                    	// aW
        wattsGab = (qreal)wattsGab * 1000000000000000.0;
    }
    return wattsGab;
}


void BitView::RecalSpectrogramBigPointX()
{
//    BIT_SIZE_CTRL gusedsize;
    qreal tempWidth = 0.0;// = gusedsize.gpicwidth;
    qint32 dtemp = 0.0;
    dtemp = pixmapnewBig.width() - LEFTDIS - RIGHTDIS;
    dtemp = dtemp < 0 ? 1 : dtemp;
    tempWidth = dtemp;
//    dtemp = pixmapnewBig.height() - TOPDIS - (BOTTOMDIS + gsystemstate.windowtype * markerTabelVisiable * BIT_MARKER_TABLE_HEIGHT);
//    dtemp = dtemp < 0 ? 1 : dtemp;
//    gusedsize.gpicheight = dtemp;
//    qreal mdeta = 0.1 * 10 * (gusedsize.gpicwidth - 2 * LINEREEOR) / (datanum - 1);

    qreal mdeta = 0.1 * 10 * (tempWidth  - HALFLINEREEOR) / (gbitbuffer.gtracenum - 1);
    quint32 i = 0;
    for(i = 0;i < gbitbuffer.gtracenum;i++)
      {
        gbitbuffer.drawSpectroPointsBigX[i] = LEFTDIS + i * mdeta;
      }
    return;
}
void BitView::RecalSpectrogramSmallPointX()
{
//    BIT_SIZE_CTRL gusedsize;
    qint32 dtemp = 0.0;
    qreal tempWidth = 0.0;// = gusedsize.gpicwidth;
    dtemp = pixmapnewSmall.width() - LEFTDIS - RIGHTDIS;
    dtemp = dtemp < 0 ? 1 : dtemp;
    tempWidth = dtemp;

//    dtemp = pixmapnewSmall.height() - TOPDIS - (BOTTOMDIS + gsystemstate.windowtype * markerTabelVisiable * BIT_MARKER_TABLE_HEIGHT);
//    dtemp = dtemp < 0 ? 1 : dtemp;
//    gusedsize.gpicheight = dtemp;

    qreal mdeta = 0.1 * 10 * (tempWidth  - HALFLINEREEOR)/ (gbitbuffer.gtracenum - 1);
    quint32 i = 0;
    for(i = 0;i < gbitbuffer.gtracenum;i++)
    {
        gbitbuffer.drawSpectroPointsSmallX[i] = LEFTDIS + i * mdeta;
    }
    return;
}
void BitView::SetSpectrogramSmallPixRect(qint32 nWidth, qint32 nHeight)
{
    //!when rect not change, do not reset.
    if(nWidth == pixmapnewSmall.width() && nHeight == pixmapnewSmall.height())
        return;
    pixmapnewSmall = pixmapnewSmall.scaled(nWidth,nHeight,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    pixmapnewSmall.fill(mPenColor.background);
    refreshSepectrogramRect();
    RecalSpectrogramSmallPointX();
    return;
}
void BitView::SetSpectrogramBigPixRect(qint32 nWidth, qint32 nHeight)
{
    //!when rect not change, do not reset.
    if(nWidth == pixmapnewBig.width() && nHeight == pixmapnewBig.height())
        return;
    pixmapnewBig = pixmapnewBig.scaled(nWidth,nHeight,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    pixmapnewBig.fill(mPenColor.background);
    refreshSepectrogramRect();
    RecalSpectrogramBigPointX();
    return;
}

//Tony 1026 Add.
qint32 BitView::findFreqToAxesPosIndex(qreal freq)
{
    qreal startfreq = gfreqinfo.gstartfreq;
    qreal stopfreq =  gfreqinfo.gstopfreq;
//    qint32 pointnum = gbitbuffer.gtracenum;
    qint32 pointnum;
    if(gbitbuffer.gtracenum == 0)
        pointnum = NOWTRACENUM;
    else
        pointnum = gbitbuffer.gtracenum;

    qreal mdeta = (qreal)(stopfreq - startfreq) / (pointnum - 1);
    qint32 AxesPosIndex = 0;

    if(freq < startfreq)
    {
        AxesPosIndex = 0;
        return AxesPosIndex;
    }
    else if(freq > stopfreq)
    {
        AxesPosIndex = pointnum-1;
        return AxesPosIndex;
    }
    qreal tmp = (qreal)(freq - startfreq) / mdeta;
    AxesPosIndex = (qint32)tmp;
    if((tmp - AxesPosIndex) >= 0.5)
    {
        ++AxesPosIndex;
    }
    return AxesPosIndex;
}
//Tony 1026 Add
qint32 BitView::findAxesPosIndex(qint32 axas)
{
    qreal width = gusedsize.gpicwidth - (2 * LINEREEOR);
    //qint32 pointnum = gbitbuffer.gtracenum;
    qint32 pointnum;
    if(gbitbuffer.gtracenum == 0)
        pointnum = NOWTRACENUM;
    else
        pointnum = gbitbuffer.gtracenum;
    qreal mdeta = (qreal)width / (pointnum - 1);
    qint32 freqIndex = 0;

    if(axas <= BIT_GRID_START_X)
    {
        freqIndex = 0;
        return freqIndex;
    }
    else if(axas >= (BIT_GRID_START_X + width))
    {
        freqIndex = pointnum-1;
        return freqIndex;
    }
    qreal tmp = (qreal)(axas - BIT_GRID_START_X) / mdeta;
    freqIndex = (qint32)tmp/1;
    if((tmp - freqIndex) >= 0.5)
    {
        ++freqIndex;
    }
    return freqIndex;
}
//Tony 1026 Add
qreal BitView::freqIndexToFreq(qint32 index)
{
    qreal startfreq = gfreqinfo.gstartfreq;
    qreal stopfreq =  gfreqinfo.gstopfreq;
    //qint32 pointnum = gbitbuffer.gtracenum;
    qint32 pointnum;
    if(gbitbuffer.gtracenum == 0)
        pointnum = NOWTRACENUM;
    else
        pointnum = gbitbuffer.gtracenum;
    qreal mdeta = (qreal)(stopfreq - startfreq) / (pointnum - 1);
    qreal freq = 0;

    if(index > (qint32)(gbitbuffer.gtracenum - 1))
    {
        index = gbitbuffer.gtracenum - 1;
    }else if(index < 0)
    {
        index = 0;
    }
    freq = startfreq + mdeta * index;
    return freq;
}
void BitView::markerMove(qint32 type)
{
    if(gctrlmana->gMarkerView[gctrlmana->gMarkerSelect] == BITOFF)
        return;
    switch (type) {
    case BIT_MARKER_MOVE_LEFT_MICRO:
        if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_NORMAL)
        {
            if((gctrlmana->gMarkerNormalIndex[gctrlmana->gMarkerSelect] - 1) >= 0)
            {
                --gctrlmana->gMarkerNormalIndex[gctrlmana->gMarkerSelect];
                gctrlmana->gMarkerNormalFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(gctrlmana->gMarkerNormalIndex[gctrlmana->gMarkerSelect]);
            }
            else
            {
                gctrlmana->gMarkerNormalIndex[gctrlmana->gMarkerSelect] = 0;
                gctrlmana->gMarkerNormalFreq[gctrlmana->gMarkerSelect] = gfreqinfo.gstartfreq;
            }
        }
        else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA)
        {
            if((gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] - 1) >= 0)
            {
                --gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect];
                gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect]);
            }
            else
            {
                gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] = 0;
                gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = gfreqinfo.gstartfreq;
            }
        }
        else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA_PAIR)
        {
            if((gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] - 1) >= 0)
            {
                --gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect];
                gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect]);
            }
            else
            {
                gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] = 0;
                gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = gfreqinfo.gstartfreq;
            }
        }
        break;
    case BIT_MARKER_MOVE_LEFT_MACRO:
        if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_NORMAL)
        {
            if((gctrlmana->gMarkerNormalIndex[gctrlmana->gMarkerSelect] >= (qint32)((gbitbuffer.gtracenum-1)/10)))
            {
                gctrlmana->gMarkerNormalIndex[gctrlmana->gMarkerSelect] -= (gbitbuffer.gtracenum-1)/10;
                gctrlmana->gMarkerNormalFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(gctrlmana->gMarkerNormalIndex[gctrlmana->gMarkerSelect]);
            }
            else
            {
                gctrlmana->gMarkerNormalIndex[gctrlmana->gMarkerSelect] = 0;
                gctrlmana->gMarkerNormalFreq[gctrlmana->gMarkerSelect] = gfreqinfo.gstartfreq;
            }
        }
        else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA)
        {
            if((gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] - (gbitbuffer.gtracenum-1)/10) >= 0)
            {
                gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] -= (gbitbuffer.gtracenum-1)/10;
                gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect]);
            }
            else
            {
                gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] = 0;
                gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = gfreqinfo.gstartfreq;
            }
        }
        else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA_PAIR)
        {
            if((gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] - (gbitbuffer.gtracenum-1)/10) >= 0)
            {
                gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] -= (gbitbuffer.gtracenum-1)/10;
                gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect]);
            }
            else
            {
                gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] = 0;
                gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = gfreqinfo.gstartfreq;
            }
        }
        break;
    case BIT_MARKER_MOVE_RIGHT_MICRO:
        if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_NORMAL)
        {
            if((gctrlmana->gMarkerNormalIndex[gctrlmana->gMarkerSelect] + 1) < (qint32)((gbitbuffer.gtracenum-1)))
            {
                ++gctrlmana->gMarkerNormalIndex[gctrlmana->gMarkerSelect];
                gctrlmana->gMarkerNormalFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(gctrlmana->gMarkerNormalIndex[gctrlmana->gMarkerSelect]);
            }
            else
            {
                gctrlmana->gMarkerNormalIndex[gctrlmana->gMarkerSelect] = (gbitbuffer.gtracenum-1);
                gctrlmana->gMarkerNormalFreq[gctrlmana->gMarkerSelect] = gfreqinfo.gstopfreq;
            }
        }
        else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA)
        {
            if((gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] + 1) <= (qint32)(gbitbuffer.gtracenum-1))
            {
                ++gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect];
                gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect]);
            }
            else
            {
                gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] = (gbitbuffer.gtracenum-1);
                gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = gfreqinfo.gstopfreq;
            }
        }
        else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA_PAIR)
        {
            if((gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] + 1) <= (qint32)(gbitbuffer.gtracenum-1))
            {
                ++gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect];
                gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect]);
            }
            else
            {
                gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] = (gbitbuffer.gtracenum-1);
                gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = gfreqinfo.gstopfreq;
            }
        }
        break;
    case BIT_MARKER_MOVE_RIGHT_MACRO:
        if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_NORMAL)
        {
            if((gctrlmana->gMarkerNormalIndex[gctrlmana->gMarkerSelect] + (gbitbuffer.gtracenum-1)/10) <= (gbitbuffer.gtracenum-1))
            {
                gctrlmana->gMarkerNormalIndex[gctrlmana->gMarkerSelect] += (gbitbuffer.gtracenum-1)/10;
                gctrlmana->gMarkerNormalFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(gctrlmana->gMarkerNormalIndex[gctrlmana->gMarkerSelect]);
            }
            else
            {
                gctrlmana->gMarkerNormalIndex[gctrlmana->gMarkerSelect] = (gbitbuffer.gtracenum-1);
                gctrlmana->gMarkerNormalFreq[gctrlmana->gMarkerSelect] = gfreqinfo.gstopfreq;
            }
        }
        else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA)
        {
            if((gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] + (gbitbuffer.gtracenum-1)/10) <= (gbitbuffer.gtracenum-1))
            {
                gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] += (gbitbuffer.gtracenum-1)/10;
                gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect]);
            }
            else
            {
                gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] = (gbitbuffer.gtracenum-1);
                gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = gfreqinfo.gstopfreq;
            }
        }
        else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA_PAIR)
        {
            if((gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] + (gbitbuffer.gtracenum-1)/10) <= (gbitbuffer.gtracenum-1))
            {
                gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] += (gbitbuffer.gtracenum-1)/10;
                gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect]);
            }
            else
            {
                gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] = (gbitbuffer.gtracenum-1);
                gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = gfreqinfo.gstopfreq;
            }
        }
        break;
    default:
        break;
    }
}
//==============================================================
//Marker Part.This part can be individually packaged.
//Tony 1031 Add.
qreal BitView::calculateMarkerNoiseValue(qreal markerValue, qreal rbwfreq)
{
    qreal markerNoiseValue = markerValue - 10 * log10(rbwfreq);
    return markerNoiseValue;
}
//Tony 1031 Add.For display marker noise infomation.
void BitView::renderMarkerNoiseInfo(QPainter *pPainter)
{
    if(!gctrlmana->gMarkerNoise[gctrlmana->gMarkerSelect] || !gctrlmana->gMarkerView[gctrlmana->gMarkerSelect])
        return;
    pPainter->setFont(QFont("Arial", 11));
    pPainter->setPen(mMarkerColor.defaultmarker);
    qreal markerInfoX = gusedsize.gridX[BIT_MARKER_INFO_GRID_POSITION];
    qreal markerwidth = gusedsize.gridXSpace;
    if(markerwidth <50 )
    {
        markerwidth = 1.5 * gusedsize.gridXSpace;
        markerInfoX = gusedsize.gridX[4];
        pPainter->setFont(QFont("Arial",8));
    }
    qreal markerheight ;
    if(gusedsize.gridYSpace > BIT_MARKER_FONT_HEIGHT)
    {
        markerheight = gusedsize.gridYSpace/2;
    }
    else
    {
        markerheight = gusedsize.gridYSpace;
    }
    qreal rbwfreq = 0;
    qreal markervalue = 0;
    qint32  markerindex = 0;
    qreal markernoise = 0;
    QString strLabel;

    rbwfreq = gfreqinfo.grbwfreq;
    markerindex = gctrlmana->gMarkerSelect;
    if(gctrlmana->gMarkerType[markerindex] == BIT_NORMAL)
    {
        markervalue = (qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[markerindex]];
        strLabel = QString("M%1").arg(markerindex + 1);
    }
    else if(gctrlmana->gMarkerType[markerindex] == BIT_DELTA)
    {
        markervalue = (qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerDeltaIndex[markerindex]];
        strLabel = QString("D%1").arg(markerindex + 1);
    }
    else if(gctrlmana->gMarkerType[markerindex] == BIT_DELTA_PAIR)
    {
        markervalue = (qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerDeltaIndex[markerindex]];
        strLabel = QString("D%1").arg(markerindex + 1);
    }
    markernoise = calculateMarkerNoiseValue(markervalue,rbwfreq);
    pPainter->drawText(markerInfoX + 2,BIT_GRID_START_Y + (markerheight * markercnt),markerwidth,markerheight,Qt::AlignLeft|Qt::AlignVCenter,strLabel);
    pPainter->drawText(markerInfoX + 0.5 * markerwidth,BIT_GRID_START_Y + (markerheight * markercnt),1.5 * markerwidth,markerheight,Qt::AlignRight|Qt::AlignVCenter," Marker noise");
    pPainter->drawText(markerInfoX + 2 * markerwidth,BIT_GRID_START_Y + (markerheight * markercnt), 2 * markerwidth,markerheight,Qt::AlignRight|Qt::AlignVCenter,QString::number(markernoise,'f',2)+" dBm/Hz");
    return ;
}

//Tony 1026 Add.
void BitView::setMarkerAttribute(qint32 attributeType, qint32 attribute, qint32 markerIndex)
{
    if(markerIndex < 0)
    {
        markerIndex = gctrlmana->gMarkerSelect;
    }
    switch (attributeType)
    {
    case BIT_MARKER_INDEX:
        gctrlmana->gMarkerSelect = attribute;
        break;
    case BIT_MARKER_VISIABLE:
        gctrlmana->gMarkerView[markerIndex] = attribute;
        markerTabelVisiable = BITOFF;
        if(gctrlmana->gMarkerDisplay == BIT_MARKER_TABLE)
        {
            for(qint32 i=0;i<BIT_MARKER_TOTAL_CNT;i++)
            {
                if(gctrlmana->gMarkerView[i] == BITON && gctrlmana->gMarkerType[i] != BIT_MARKER_OFF )
                {
                    markerTabelVisiable = BITON;
                    break;
                }
            }
        }
        calculationPainterArea();
        //Tony 1105
        markertotalcnt = 0;
        for(qint32 i = 0;i<BIT_MARKER_TOTAL_CNT;i++)
        {
            if(gctrlmana->gMarkerView[i] == BITON)
                ++markertotalcnt;
        }
        if(gctrlmana->gMarkerType[markerIndex] == BIT_DELTA)
        {
            gctrlmana->gMarkerRefAmpt[markerIndex] = (qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[markerIndex]];
//            mMarkerRefAmpt = (qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[markerIndex]];
            gctrlmana->gMarkerDeltaIndex[markerIndex] = gctrlmana->gMarkerNormalIndex[markerIndex];
            gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(gctrlmana->gMarkerDeltaIndex[markerIndex]);
            gctrlmana->gMarkerNormalPosY[markerIndex] = gbitbuffer.drawpointsY[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[markerIndex]];
//            mMarkerNormalPosY = gbitbuffer.drawpointsY[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[markerIndex]];
        }
        else if(gctrlmana->gMarkerType[markerIndex] == BIT_DELTA_PAIR)
        {
//            gctrlmana->gMarkerRefAmpt[markerIndex] = (qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[markerIndex]];
//            mMarkerRefAmpt = (qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[markerIndex]];
            gctrlmana->gMarkerDeltaIndex[markerIndex] = gctrlmana->gMarkerNormalIndex[markerIndex];
            gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(gctrlmana->gMarkerDeltaIndex[markerIndex]);
            gctrlmana->gMarkerNormalPosY[markerIndex] = gbitbuffer.drawpointsY[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[markerIndex]];
//            mMarkerNormalPosY = gbitbuffer.drawpointsY[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[markerIndex]];
        }
        else
        {
            gctrlmana->gMarkerDeltaIndex[markerIndex] = gctrlmana->gMarkerNormalIndex[markerIndex];
        }
        break;
    case BIT_MARKER_TYPE:
        gctrlmana->gMarkerType[markerIndex] = attribute;
        if(attribute == BIT_DELTA)
        {
            gctrlmana->gMarkerRefAmpt[markerIndex] = (qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[markerIndex]];
//            mMarkerRefAmpt = (qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[markerIndex]];
            gctrlmana->gMarkerDeltaIndex[markerIndex] = gctrlmana->gMarkerNormalIndex[markerIndex];
            gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(gctrlmana->gMarkerDeltaIndex[markerIndex]);
            gctrlmana->gMarkerNormalPosY[markerIndex] = gbitbuffer.drawpointsY[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[markerIndex]];
//            mMarkerNormalPosY = gbitbuffer.drawpointsY[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[markerIndex]];
        }
        else if(attribute == BIT_DELTA_PAIR)
        {
            gctrlmana->gMarkerRefAmpt[markerIndex] = (qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[markerIndex]];
//            mMarkerRefAmpt = (qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[markerIndex]];
            gctrlmana->gMarkerDeltaIndex[markerIndex] = gctrlmana->gMarkerNormalIndex[markerIndex];
            gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(gctrlmana->gMarkerDeltaIndex[markerIndex]);
            gctrlmana->gMarkerNormalPosY[markerIndex] = gbitbuffer.drawpointsY[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[markerIndex]];
//            mMarkerNormalPosY = gbitbuffer.drawpointsY[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[markerIndex]];
        }
        else
        {
            gctrlmana->gMarkerDeltaIndex[markerIndex] = gctrlmana->gMarkerNormalIndex[markerIndex];
        }
        break;
    case BIT_MARKER_DISPLAY:
        gctrlmana->gMarkerDisplay = attribute;
        markerTabelVisiable = BITOFF;
        if(gctrlmana->gMarkerDisplay == BIT_MARKER_TABLE)
        {
            for(qint32 i=0;i<BIT_MARKER_TOTAL_CNT;i++)
            {
                if(gctrlmana->gMarkerView[i] == BITON && gctrlmana->gMarkerType[i] != BIT_MARKER_OFF)
                {
                    markerTabelVisiable = BITON;
                    break;
                }
            }
        }

        calculationPainterArea();
        break;
    case BIT_MARKER_NOISE:
        gctrlmana->gMarkerNoise[markerIndex] = attribute;
        break;
    }
    return;
}

qint32 BitView::getMarkerAttribute(qint32 attributeType,qint32 markerIndex)
{
    qint32 attribute = -1;
    if(markerIndex < 0)
    {
        markerIndex = gctrlmana->gMarkerSelect;
    }
    switch (attributeType)
    {
    case BIT_MARKER_INDEX:
        attribute = gctrlmana->gMarkerSelect;
        break;
    case BIT_MARKER_VISIABLE:
        attribute = gctrlmana->gMarkerView[markerIndex];
        break;
    case BIT_MARKER_TYPE:
        attribute = gctrlmana->gMarkerType[markerIndex];
        break;
    case BIT_MARKER_DISPLAY:
        attribute = gctrlmana->gMarkerDisplay;
        break;
    case BIT_MARKER_NOISE:
        attribute = gctrlmana->gMarkerNoise[markerIndex];
        break;
    }
    return attribute;
}


qreal BitView::setMarkerFreqAttribute(qint32 attributeType, qreal attribute, qint32 markerIndex)
{
    if(markerIndex < 0)
        markerIndex = gctrlmana->gMarkerSelect;

//    qreal deltafreq;
//    qint32 deltaindex;
    switch (attributeType) {
    case BIT_MARKER_DELTA:
        gctrlmana->gMarkerDeltaIndex[markerIndex] =findFreqToAxesPosIndex(attribute);
        gctrlmana->gMarkerDeltaFreq[markerIndex] = freqIndexToFreq(gctrlmana->gMarkerDeltaIndex[markerIndex]);
        return gctrlmana->gMarkerDeltaFreq[markerIndex];
        break;
    case BIT_MARKER_NORMAL:
            gctrlmana->gMarkerNormalIndex[markerIndex] =findFreqToAxesPosIndex(attribute);
            gctrlmana->gMarkerNormalFreq[markerIndex] = freqIndexToFreq(gctrlmana->gMarkerNormalIndex[markerIndex]);
        return gctrlmana->gMarkerNormalFreq[markerIndex];
        break;
    case BIT_MARKER_DELTA_INDEX:
        gctrlmana->gMarkerDeltaIndex[markerIndex] = attribute;
        gctrlmana->gMarkerDeltaFreq[markerIndex] = freqIndexToFreq(gctrlmana->gMarkerDeltaIndex[markerIndex]);
        return gctrlmana->gMarkerDeltaFreq[markerIndex];
        break;
    case BIT_MARKER_NORMAL_INDEX:
            gctrlmana->gMarkerNormalIndex[markerIndex] = attribute;
            gctrlmana->gMarkerNormalFreq[markerIndex] = freqIndexToFreq(gctrlmana->gMarkerNormalIndex[markerIndex]);
        return gctrlmana->gMarkerNormalFreq[markerIndex];
        break;
    }
    return attribute;
}

qreal BitView::getMarkerFreqAttribute(qint32 attributeType,qint32 markerIndex)
{
    qint32 error = 0;

    if(markerIndex < 0)
        markerIndex = gctrlmana->gMarkerSelect;

    switch (attributeType) {
    case BIT_MARKER_DELTA:
        return gctrlmana->gMarkerDeltaFreq[markerIndex];
        break;
    case BIT_MARKER_NORMAL:
        return gctrlmana->gMarkerNormalFreq[markerIndex];
        break;
    case BIT_MARKER_DELTA_INDEX:
        return gctrlmana->gMarkerDeltaIndex[markerIndex];
        break;
    case BIT_MARKER_NORMAL_INDEX:
        return gctrlmana->gMarkerNormalIndex[markerIndex];
        break;
    }
    return (qreal)error;
}

qreal BitView::getMarkerCurrentFreq(qint32 attributeType)
{
    qreal freq = 0;
    switch (attributeType)
    {
    case BIT_MARKER_CURRENT_FREQ:
        if(gctrlmana->gMarkerView[gctrlmana->gMarkerSelect] == BITOFF)
        {
            freq = 0;
            break;
        }
        if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_NORMAL)
        {
            freq = gctrlmana->gMarkerNormalFreq[gctrlmana->gMarkerSelect];
        }
        else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA)
        {
            freq = gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect];
        }
        else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA_PAIR)
        {
            freq = gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect];
        }
        break;
    case BIT_MARKER_STEP_FREQ:
        freq = (gfreqinfo.gstopfreq - gfreqinfo.gstartfreq) / (gbitbuffer.gtracenum - 1);;
        break;
    }
    return freq;
}

qreal BitView::getMarkerAmptInfo(qint32 attributeType, qint32 markerIndex)
{
    qreal value = -1;
    qint32 index = 0;
    if(markerIndex < 0)
    {
        markerIndex = 0;
    }
    switch (attributeType)
    {
    case BIT_MARKER_REF:
        if(gctrlmana->gMarkerView[gctrlmana->gMarkerSelect] == BITOFF)
        {
            value = gusedsize.grefValue;
            break;
        }
        if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_NORMAL)
        {
            index = gctrlmana->gMarkerNormalIndex[gctrlmana->gMarkerSelect];
            value = (qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][index];
        }
        else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA)
        {
            index = gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect];
            value = (qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][index];
        }
        else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA_PAIR)
        {
            index = gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect];
            value = (qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][index];
        }
        break;
    }
    return value;
}

qreal BitView::getMarkerInfo(qint32 attributeType, qint32 markerIndex)
{
    qreal value = -1;
    qint32 index = 0;
    qreal markervalue = 0.;
    if(markerIndex < 0)
        markerIndex = gctrlmana->gMarkerSelect;
    switch (attributeType)
    {
    case BIT_MARKER_NORMAL:
        index = gctrlmana->gMarkerNormalIndex[markerIndex];
        value = (qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][index] + gusedsize.goffsetValue;
        switch (gAmptdUnit)
        {
        case BIT_DBM:

            break;
        case BIT_DBV:

            break;
        case BIT_DBMV:

            break;
        case BIT_DBUV:

            break;
        case BIT_VOLT:
            value = dbmToVoltCalculator(value);
            break;
        case BIT_WATTS:
            value = dbmToWattsCalculator(value);

            break;
        }
        break;
    case BIT_MARKER_DELTA:
        index = gctrlmana->gMarkerDeltaIndex[markerIndex];
        value = (qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][index];
        switch (gAmptdUnit)
        {
        case BIT_DBM:

            break;
        case BIT_DBV:
            value = value + dBVFix;
            break;
        case BIT_DBMV:
            value = value + dBmVFix;
            break;
        case BIT_DBUV:
            value = value + dBuVFix;
            break;
        case BIT_VOLT:
            value = dbmToVoltCalculator(value);
            break;
        case BIT_WATTS:
            value = dbmToWattsCalculator(value);
            break;
        }
        break;
    case BIT_MARKER_NOISE:
        if(gctrlmana->gMarkerType[markerIndex] == BIT_NORMAL)
        {
            markervalue = (qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[markerIndex]];
        }
        else if(gctrlmana->gMarkerType[markerIndex] == BIT_DELTA)
        {
            markervalue = (qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerDeltaIndex[markerIndex]];
        }
        else if(gctrlmana->gMarkerType[markerIndex] == BIT_DELTA_PAIR)
        {
            markervalue = (qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerDeltaIndex[markerIndex]];
        }
        value = calculateMarkerNoiseValue(markervalue,gfreqinfo.grbwfreq);
        break;
    default:
        break;
    }
    return value;
}
QString BitView::getMarkerInfoStr(qint32 attributeType, qint32 markerIndex)
{
    char strAmp[20];
    QString str = QString("");
    qreal value = -1;
    qreal valueDelta = -1;
    qreal refVal = -1;
    qreal deltaVal = -1;
    qint32 index = 0;
    qint32 indexDelta = 0;
    qreal markervalue = 0.;
    if(markerIndex < 0)
        markerIndex = gctrlmana->gMarkerSelect;
    switch (attributeType)
    {
    case BIT_MARKER_NORMAL:
        index = gctrlmana->gMarkerNormalIndex[markerIndex];
        value = (qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][index] + gusedsize.goffsetValue;
        if(gctrlmana->gMarkerType[markerIndex] == BIT_DELTA)
        {
//            value = mMarkerRefAmpt;
            value = gctrlmana->gMarkerRefAmpt[markerIndex];
        }
        switch(gAmptdUnit)
        {
        case BIT_DBM:
            sprintf(strAmp, "%.2f dBm", value);
            str = QString(strAmp);
            break;
        case BIT_DBV:
            sprintf(strAmp, "%.2f dBv", value + dBVFix);
            str = QString(strAmp);
            break;
        case BIT_DBMV:
            sprintf(strAmp, "%.2f dBmV", value + dBmVFix);
            str = QString(strAmp);
            break;
        case BIT_DBUV:
            sprintf(strAmp, "%.2f dBuV", value + dBuVFix);
            str = QString(strAmp);
            break;
        case BIT_VOLT:
            dbmToVoltCalculatorAndDisplayFunc(strAmp, value);
            str  = QString(strAmp);
            break;
        case BIT_WATTS:
            dbmToWattsCalculatorAndDisplayFunc(strAmp, value);
            str  = QString(strAmp);
            break;
        }
        break;
    case BIT_MARKER_DELTA:
        indexDelta = gctrlmana->gMarkerDeltaIndex[markerIndex];
        valueDelta = (qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][indexDelta];
        index = gctrlmana->gMarkerNormalIndex[markerIndex];
//        value = (qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][index];
        value = valueDelta - gctrlmana->gMarkerRefAmpt[markerIndex];
//        value = valueDelta - mMarkerRefAmpt;
        switch (gAmptdUnit)
        {
        case BIT_DBM:
            sprintf(strAmp, "%.2f dB", value);
            str = QString(strAmp);
            break;
        case BIT_DBV:
            sprintf(strAmp, "%.2f dB", value /*+ dBVFix*/);
            str = QString(strAmp);
            break;
        case BIT_DBMV:
            sprintf(strAmp, "%.2f dB", value /*+ dBmVFix*/);
            str = QString(strAmp);
            break;
        case BIT_DBUV:
            sprintf(strAmp, "%.2f dB", value /*+ dBuVFix*/);
            str = QString(strAmp);
            break;
        case BIT_VOLT:
//            refVal = ChangedBmToUV(mMarkerRefAmpt);
//            refVal = ChangedBmToUV(gctrlmana->gMarkerRefAmpt[markerIndex]);
//            deltaVal = ChangedBmToUV(value);
//            str = QString::number(deltaVal,'f',2);
//            str = str + QString(" (V/V)");
            ChangeValueToVoltStr(strAmp,value);
//            dbmToVoltCalculatorAndDisplayFunc(strAmp, value);
            str  = QString(strAmp) + QString(" (V/V)");
            break;
        case BIT_WATTS:
//            refVal = ChangedBmToMW(mMarkerRefAmpt);
//            refVal = ChangedBmToMW(gctrlmana->gMarkerRefAmpt[markerIndex]);
//            deltaVal = ChangedBmToMW(value);
//            str = QString::number(deltaVal,'f',2);
//            str = str + QString(" (W/W)");
            ChangeValueToWattStr(strAmp,value);

//            dbmToWattsCalculatorAndDisplayFunc(strAmp, value);
            str  = QString(strAmp) + QString(" (W/W)");
            break;
        }
        break;
    default:
        break;
    }
    return str;
}
void BitView::markerUpdateByFreq()
{
    qlonglong deltaFreq = 0;
    //Tony 1105
    for(qint32 i=0;i<BIT_MARKER_TOTAL_CNT;i++)
    {
        //Initialization marker frequency if marker value is zero.
        if(gctrlmana->gMarkerNormalFreq[i] == 0 || gctrlmana->gMarkerDeltaFreq[i] == 0)
        {
            gctrlmana->gMarkerNormalFreq[i] = gfreqinfo.gcenterfreq;
            gctrlmana->gMarkerDeltaFreq[i] = gfreqinfo.gcenterfreq;
            continue;
        }
        if (gctrlmana->gMarkerType[i] == BIT_DELTA)
        {
            deltaFreq = gctrlmana->gMarkerDeltaFreq[i] - gctrlmana->gMarkerNormalFreq[i];
            gctrlmana->gMarkerDeltaIndex[i] = findFreqToAxesPosIndex(gctrlmana->gMarkerDeltaFreq[i]);
            gctrlmana->gMarkerNormalIndex[i] = findFreqToAxesPosIndex(gctrlmana->gMarkerNormalFreq[i]);
        }
        if (gctrlmana->gMarkerType[i] == BIT_DELTA_PAIR)
        {
            deltaFreq = gctrlmana->gMarkerDeltaFreq[i] - gctrlmana->gMarkerNormalFreq[i];
            gctrlmana->gMarkerDeltaIndex[i] = findFreqToAxesPosIndex(gctrlmana->gMarkerDeltaFreq[i]);
            gctrlmana->gMarkerNormalIndex[i] = findFreqToAxesPosIndex(gctrlmana->gMarkerNormalFreq[i]);
        }
        else
        {
            //Marker frequency out of range and correction frequency.
            if(gctrlmana->gMarkerNormalFreq[i] < gfreqinfo.gstartfreq)
            {
                gctrlmana->gMarkerNormalIndex[i] = 0;
                gctrlmana->gMarkerNormalFreq[i] = gfreqinfo.gstartfreq;
            }
            else if(gctrlmana->gMarkerNormalFreq[i] > gfreqinfo.gstopfreq)
            {
                gctrlmana->gMarkerNormalIndex[i] = gbitbuffer.gtracenum-1;
                gctrlmana->gMarkerNormalFreq[i] = gfreqinfo.gstopfreq;
            }
            gctrlmana->gMarkerNormalIndex[i] = findFreqToAxesPosIndex(gctrlmana->gMarkerNormalFreq[i]);
            gctrlmana->gMarkerNormalFreq[i] = freqIndexToFreq(gctrlmana->gMarkerNormalIndex[i]);
        }
//        gctrlmana->gMarkerDeltaFreq[i] = gctrlmana->gMarkerNormalFreq[i] + deltaFreq;
        //Correction marker frequency when start or stop frequency change.
//        gctrlmana->gMarkerDeltaFreq[i] = freqIndexToFreq(gctrlmana->gMarkerDeltaIndex[i]);
    }
}

//Tony 1025 Add
/**
* Drawing vertical line and marker symbol.
* @param[in] paint event
* @return    void
*/
void BitView::renderMarkerPart(QPainter *pPainter)
{
    qint32 i=0;
    qint32 markerNormalPosX = 0;
    qint32 markerDeltaPosX = 0;

    for(i=0;i<BIT_MARKER_TOTAL_CNT;i++)
    {
        if(gctrlmana->gMarkerView[i] == BITON)
        {
            if (gctrlmana->gMarkerSelect== i)
                pPainter->setPen(mMarkerColor.curmarker);
            else
                pPainter->setPen(mMarkerColor.defaultmarker);
            //DELTA.
            if (gctrlmana->gMarkerType[i] == BIT_DELTA)
            {
                // Delta Marker Display
                markerDeltaPosX = gbitbuffer.drawpointsX[gctrlmana->gMarkerDeltaIndex[i]];
                markerDeltaPolygonAssignNDrawFunc(pPainter, i);
                if (gbitbuffer.drawpointsY[gctrlmana->gtraceIndex][gctrlmana->gMarkerDeltaIndex[i]] < (BIT_GRID_START_Y + 40)  )
                {
                    pPainter->drawLine(markerDeltaPosX, (mkrDeltaPoints[0].y() + 2), markerDeltaPosX, (BIT_GRID_START_Y+CenterPartRect.height()-HALFLINEREEOR));
                }
                else
                {
                    pPainter->drawLine(markerDeltaPosX, BIT_GRID_START_Y, markerDeltaPosX, (mkrDeltaPoints[0].y() - 2));
                    pPainter->drawLine(markerDeltaPosX, (mkrDeltaPoints[1].y() + 2), markerDeltaPosX, (BIT_GRID_START_Y+CenterPartRect.height()-HALFLINEREEOR));
                }
            }
            else if (gctrlmana->gMarkerType[i] == BIT_DELTA_PAIR)
            {
                // Delta Marker Display
                markerDeltaPosX = gbitbuffer.drawpointsX[gctrlmana->gMarkerDeltaIndex[i]];
                markerDeltaPolygonAssignNDrawFunc(pPainter, i);
                if (gbitbuffer.drawpointsY[gctrlmana->gtraceIndex][gctrlmana->gMarkerDeltaIndex[i]] < (BIT_GRID_START_Y + 40)  )
                {
                    pPainter->drawLine(markerDeltaPosX, (mkrDeltaPoints[0].y() + 2), markerDeltaPosX, (BIT_GRID_START_Y+CenterPartRect.height()-HALFLINEREEOR));
                }
                else
                {
                    pPainter->drawLine(markerDeltaPosX, BIT_GRID_START_Y, markerDeltaPosX, (mkrDeltaPoints[0].y() - 2));
                    pPainter->drawLine(markerDeltaPosX, (mkrDeltaPoints[1].y() + 2), markerDeltaPosX, (BIT_GRID_START_Y+CenterPartRect.height()-HALFLINEREEOR));
                }
            }
            markerNormalPosX = gbitbuffer.drawpointsX[gctrlmana->gMarkerNormalIndex[i]];
            markerNormalPolygonAssignNDrawFunc(pPainter, i);
            if (gbitbuffer.drawpointsY[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[i]] < (BIT_GRID_START_Y + 40) )
            {
                pPainter->drawLine(markerNormalPosX, (mkrNormalPoints[0].y() + 2), markerNormalPosX, BIT_GRID_START_Y+CenterPartRect.height()-HALFLINEREEOR);
            }
            else
            {
                pPainter->drawLine(markerNormalPosX, BIT_GRID_START_Y , markerNormalPosX, (mkrNormalPoints[0].y() - 2));
                pPainter->drawLine(markerNormalPosX, (mkrNormalPoints[1].y() + 2), markerNormalPosX, (BIT_GRID_START_Y+CenterPartRect.height()-HALFLINEREEOR));
            }
        }
    }

    if(gctrlmana->gMarkerDisplay == BIT_MARKER_ONLY)
    {
        markerCurrentSelectInfoDisplayFunc(pPainter);
        renderMarkerNoiseInfo(pPainter);
    }
    else if(gctrlmana->gMarkerDisplay == BIT_MARKER_TABLE)
    {
        if(gsystemstate.windowtype == BIT_SINGLEWINDOW && markerTabelVisiable == BITON)
        {
            renderMarkerTableBoaderLines(pPainter);
            markerCurrentSelectInfoDisplayFunc(pPainter);
            renderMarkerNoiseInfo(pPainter);
            markerTableInfoDisplayFunc(pPainter);
        }else
        {
            markerCurrentSelectInfoDisplayFunc(pPainter);
            renderMarkerNoiseInfo(pPainter);
        }
    }
    return ;
}
/**
 *Draw Marker polygon if Marker's type is NORMAL.
 *@param[in]    painter  --  Marker's layer
 *@param[in]    pos      --  Marker's index
 *@return
 *@note
 */

void BitView::markerNormalPolygonAssignNDrawFunc(QPainter *painter, qint32 pos)
{
    qint32 drawNormalPosX = gbitbuffer.drawpointsX[gctrlmana->gMarkerNormalIndex[pos]];
    qint32 drawNormalPosY = 0;// gbitbuffer.drawpointsY[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[pos]];
    if(gctrlmana->gMarkerType[pos] == BIT_DELTA)
    {
//        drawNormalPosY = mMarkerNormalPosY;
        drawNormalPosY = gctrlmana->gMarkerNormalPosY[pos];
    }
    else
    {
        drawNormalPosY = gbitbuffer.drawpointsY[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[pos]];
    }
    QString strMarker;
    QPolygon poly;
    QFont font = painter->font();
    font.setPointSize(10);
    painter->setFont(font);

    if (gctrlmana->gMarkerSelect == pos)
        painter->setPen(mMarkerColor.curmarker);
    else
        painter->setPen(mMarkerColor.defaultmarker);
    //Normal Marker String.
    switch (gctrlmana->gMarkerType[pos]) {
    case BIT_NORMAL:
        strMarker = QString("%1%2").arg("M").arg(pos + 1);
        break;
    case BIT_DELTA:
        strMarker = QString("%1%2").arg("R").arg(pos + 1);
        break;
    case BIT_DELTA_PAIR:
        strMarker = QString("%1%2").arg("R").arg(pos + 1);
        break;
    default:
        break;
    }

    if (drawNormalPosY < (BIT_GRID_START_Y + 40)) {
        mkrNormalPoints[0].setX(drawNormalPosX - 11);
        mkrNormalPoints[0].setY(drawNormalPosY + 40);
        mkrNormalPoints[1].setX(drawNormalPosX - 11);
        mkrNormalPoints[1].setY(drawNormalPosY + 20);
        mkrNormalPoints[2].setX(drawNormalPosX + 11);
        mkrNormalPoints[2].setY(drawNormalPosY + 20);
        mkrNormalPoints[3].setX(drawNormalPosX + 11);
        mkrNormalPoints[3].setY(drawNormalPosY + 40);
        painter->drawText(mkrNormalPoints[0].x() + 2 , mkrNormalPoints[0].y() - 5 , strMarker);
    }
    else
    {
        mkrNormalPoints[0].setX(drawNormalPosX - 11);
        mkrNormalPoints[0].setY(drawNormalPosY - 40);
        mkrNormalPoints[1].setX(drawNormalPosX - 11);
        mkrNormalPoints[1].setY(drawNormalPosY - 20);
        mkrNormalPoints[2].setX(drawNormalPosX + 11);
        mkrNormalPoints[2].setY(drawNormalPosY - 20);
        mkrNormalPoints[3].setX(drawNormalPosX + 11);
        mkrNormalPoints[3].setY(drawNormalPosY - 40);
        painter->drawText(mkrNormalPoints[0].x() + 2 , mkrNormalPoints[0].y() + 15, strMarker);
    }
    poly  << mkrNormalPoints[0] << mkrNormalPoints[1] << mkrNormalPoints[2] << mkrNormalPoints[3];
    painter->drawPolygon(poly);
    return ;
}

/**
 *Draw Marker polygon if Marker's type is DELTA.
 *@param[in]    painter  --  Marker's layer
 *@param[in]    pos      --  Marker's index
 *@return
 *@note
 */

void BitView::markerDeltaPolygonAssignNDrawFunc(QPainter *painter, qint32 pos)
{
    qint32 drawDeltaPosX = gbitbuffer.drawpointsX[gctrlmana->gMarkerDeltaIndex[pos]];
    qint32 drawDeltaPosY = gbitbuffer.drawpointsY[gctrlmana->gtraceIndex][gctrlmana->gMarkerDeltaIndex[pos]];
    QString strDeltaMarker;
    QPolygon poly;
    QFont font = painter->font();
    font.setPointSize(10);
    painter->setFont(font);


    if (gctrlmana->gMarkerSelect == pos)
        painter->setPen(mMarkerColor.curmarker);
    else
        painter->setPen(mMarkerColor.defaultmarker);
    //Delta Marker String
    strDeltaMarker = QString("%1%2").arg("D").arg(pos + 1);

    if (drawDeltaPosY < (BIT_GRID_START_Y + 40))
    {
        mkrDeltaPoints[0].setX(drawDeltaPosX - 11);
        mkrDeltaPoints[0].setY(drawDeltaPosY + 40);
        mkrDeltaPoints[1].setX(drawDeltaPosX - 11);
        mkrDeltaPoints[1].setY(drawDeltaPosY + 20);
        mkrDeltaPoints[2].setX(drawDeltaPosX + 11);
        mkrDeltaPoints[2].setY(drawDeltaPosY + 20);
        mkrDeltaPoints[3].setX(drawDeltaPosX + 11);
        mkrDeltaPoints[3].setY(drawDeltaPosY + 40);
        painter->drawText(mkrDeltaPoints[0].x() + 2 , mkrDeltaPoints[0].y() - 5, strDeltaMarker);
    }
    else
    {
        mkrDeltaPoints[0].setX(drawDeltaPosX - 11);
        mkrDeltaPoints[0].setY(drawDeltaPosY - 40);
        mkrDeltaPoints[1].setX(drawDeltaPosX - 11);
        mkrDeltaPoints[1].setY(drawDeltaPosY - 20);
        mkrDeltaPoints[2].setX(drawDeltaPosX + 11);
        mkrDeltaPoints[2].setY(drawDeltaPosY - 20);
        mkrDeltaPoints[3].setX(drawDeltaPosX + 11);
        mkrDeltaPoints[3].setY(drawDeltaPosY - 40);
        painter->drawText(mkrDeltaPoints[0].x() + 2 , mkrDeltaPoints[0].y() + 15, strDeltaMarker);
    }
    poly  << mkrDeltaPoints[0] << mkrDeltaPoints[1] << mkrDeltaPoints[2] << mkrDeltaPoints[3];
    painter->drawPolygon(poly);
    return;
}
/**
* @name          void markerCurrentSelectInfoDisplayFunc(QPainter *painter)
* @brief         Draw infomation in the upper right corner
* @param         painter -- paint devices.
* @author        Tony
* @date          2018-10-11
*/
//! draw infomation
void BitView::markerCurrentSelectInfoDisplayFunc(QPainter *painter)
{
    QString strLabel;
    char strAmp[20];
    qreal refVolt,deltaVolt;
    qreal refWatt,deltaWatt;
    qint32 i = 0;
    markercnt = 0;
    QString strValue;
    qreal freqValue = 0;
    long long deltaFreq = 0;
    qint32 minusFlag = 0;
    qreal deltaAmptdGab = 0.;
    qreal refAmptdGab = 0.;
    qreal subtractGab = 0;
    qreal markerLevel = 0;
    qreal markerInfoX  = gusedsize.gridX[BIT_MARKER_INFO_GRID_POSITION];
    qreal markerwidth  = gusedsize.gridXSpace;
    qreal markerheight ;
    if(gusedsize.gridYSpace > BIT_MARKER_FONT_HEIGHT)
    {
        markerheight = gusedsize.gridYSpace/2;
    }else
    {
        markerheight = gusedsize.gridYSpace;
    }
    painter->setFont(QFont("Arial", 11));
    if(markerwidth <50 )
    {
        markerwidth = 1.5 * gusedsize.gridXSpace;
        markerInfoX = gusedsize.gridX[4];
        painter->setFont(QFont("Arial",8));
    }
    i = gctrlmana->gMarkerSelect;

    if (gctrlmana->gMarkerView[i] == BITON)
    {
        // Marker
        painter->setPen(mMarkerColor.curmarker);
        // MARKER -> NORMAL
        if (gctrlmana->gMarkerType[i] == BIT_NORMAL)
        {
            strLabel = QString("M%1").arg(i + 1);
            painter->drawText(markerInfoX + 2,BIT_GRID_START_Y + ((markerheight * markercnt)),markerwidth,markerheight,Qt::AlignLeft|Qt::AlignVCenter,strLabel);

            freqValue = gctrlmana->gMarkerNormalFreq[i] + mFreqOffset;
            strValue = freqValueToQstring(freqValue);
            painter->drawText(markerInfoX + 0.5 * markerwidth,BIT_GRID_START_Y + ((markerheight * markercnt)),1.5 * markerwidth + BIT_MARKER_LINEERROR,markerheight,Qt::AlignRight|Qt::AlignVCenter,strValue);

            if ( gctrlmana->gMarkerNormalFreq[i] < gfreqinfo.gstartfreq)
            {
                sprintf(strAmp,"- -");
                painter->drawText(markerInfoX + 2 * markerwidth,BIT_GRID_START_Y + ((markerheight * markercnt)),2 * markerwidth,markerheight,Qt::AlignRight|Qt::AlignVCenter,strAmp);
            }
            else if ( gctrlmana->gMarkerNormalFreq[i] > gfreqinfo.gstopfreq)
            {
                sprintf(strAmp,"- -");
                painter->drawText(markerInfoX + 2 * markerwidth,BIT_GRID_START_Y + ((markerheight * markercnt)),2 * markerwidth,markerheight,Qt::AlignRight|Qt::AlignVCenter,strAmp);
            }
            else
            {
                markerLevel =(qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[i]] + gusedsize.goffsetValue;
                switch (gAmptdUnit)
                {
                case BIT_DBM:
                    sprintf(strAmp, "%.2f dBm", markerLevel);
                    break;
                case BIT_DBV:
                    sprintf(strAmp, "%.2f dBV", markerLevel + dBVFix);
                    break;
                case BIT_DBMV:
                    sprintf(strAmp, "%.2f dBmV", markerLevel + dBmVFix);
                    break;
                case BIT_DBUV:
                    sprintf(strAmp, "%.2f dBuV", markerLevel + dBuVFix);
                    break;
                case BIT_VOLT:
                    dbmToVoltCalculatorAndDisplayFunc(strAmp, markerLevel);
                    break;
                case BIT_WATTS:
                    dbmToWattsCalculatorAndDisplayFunc(strAmp, markerLevel);

                    break;
                }
                painter->drawText(markerInfoX + 2 * markerwidth,BIT_GRID_START_Y + ((markerheight * markercnt)),2 * markerwidth,markerheight,Qt::AlignRight|Qt::AlignVCenter,strAmp);
            }
             ++markercnt;
        }
        else if(gctrlmana->gMarkerType[i] == BIT_DELTA)
        {
            // Delta Display
            strLabel = QString("R%1").arg(i + 1);
            painter->drawText(markerInfoX + 2,BIT_GRID_START_Y + ((markerheight * markercnt)),markerwidth,markerheight, Qt::AlignLeft|Qt::AlignVCenter,strLabel);

            freqValue = gctrlmana->gMarkerNormalFreq[i] + mFreqOffset;
            strValue = freqValueToQstring(freqValue);
            painter->drawText(markerInfoX + 0.5 * markerwidth, BIT_GRID_START_Y + ((markerheight * markercnt)),1.5 * markerwidth + BIT_MARKER_LINEERROR,markerheight,Qt::AlignRight|Qt::AlignVCenter,strValue);

            if ( gctrlmana->gMarkerNormalFreq[i] < gfreqinfo.gstartfreq) {
                sprintf(strAmp,"- -");
                painter->drawText(markerInfoX + 2 * markerwidth, BIT_GRID_START_Y + ((markerheight * markercnt)),2 * markerwidth,markerheight,Qt::AlignRight|Qt::AlignVCenter,strAmp);
            } else if ( gctrlmana->gMarkerNormalFreq[i] > gfreqinfo.gstopfreq) {
                sprintf(strAmp,"- -");
                painter->drawText(markerInfoX + 2 * markerwidth, BIT_GRID_START_Y + ((markerheight * markercnt)),2 * markerwidth,markerheight,Qt::AlignRight|Qt::AlignVCenter,strAmp);
            } else {
//                markerLevel =(qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[i]];
//                markerLevel = mMarkerRefAmpt;
                markerLevel = gctrlmana->gMarkerRefAmpt[i] + gusedsize.goffsetValue;
                switch (gAmptdUnit)
                {
                case BIT_DBM:
                    sprintf(strAmp, "%.2f dBm", markerLevel);
                    break;
                case BIT_DBV:
                    sprintf(strAmp, "%.2f dBV", markerLevel + dBVFix);
                    break;
                case BIT_DBMV:
                    sprintf(strAmp, "%.2f dBmV", markerLevel + dBmVFix);
                    break;
                case BIT_DBUV:
                    sprintf(strAmp, "%.2f dBuV", markerLevel + dBuVFix);
                    break;
                case BIT_VOLT:
                    dbmToVoltCalculatorAndDisplayFunc(strAmp, markerLevel);
                    break;
                case BIT_WATTS:
                    dbmToWattsCalculatorAndDisplayFunc(strAmp, markerLevel);

                    break;
                }
            }
            painter->drawText(markerInfoX + 2 * markerwidth, BIT_GRID_START_Y + ((markerheight * markercnt)),2 * markerwidth,markerheight,Qt::AlignRight|Qt::AlignVCenter,strAmp);
            ++markercnt;
            // Delta Display
            strLabel = QString("D%1").arg(i + 1);
            painter->drawText(markerInfoX + 2,BIT_GRID_START_Y + ((markerheight * markercnt)),markerwidth,markerheight, Qt::AlignLeft|Qt::AlignVCenter,strLabel);

            deltaFreq = gctrlmana->gMarkerDeltaFreq[i] - gctrlmana->gMarkerNormalFreq[i];
            if (deltaFreq < 0) {
                deltaFreq *= -1;
                minusFlag = 1;
            }
            strValue = freqValueToQstring(deltaFreq);
            if (minusFlag == 1)
                strValue = QString("-%1").arg(strValue);

            painter->drawText(markerInfoX + 0.5 * markerwidth, BIT_GRID_START_Y + ((markerheight * markercnt)),1.5 * markerwidth + BIT_MARKER_LINEERROR,markerheight,Qt::AlignRight|Qt::AlignVCenter,strValue);

            if ( gctrlmana->gMarkerDeltaFreq[i] < gfreqinfo.gstartfreq)
            {
                sprintf(strAmp,"- -");
                painter->drawText(markerInfoX + 2 * markerwidth, BIT_GRID_START_Y + ((markerheight * markercnt)),2 * markerwidth,markerheight,Qt::AlignRight|Qt::AlignVCenter,strAmp);
            } else if ( gctrlmana->gMarkerDeltaFreq[i] > gfreqinfo.gstopfreq)
            {
                sprintf(strAmp,"- -");
                painter->drawText(markerInfoX + 2 * markerwidth, BIT_GRID_START_Y + ((markerheight * markercnt)),2 * markerwidth,markerheight,Qt::AlignRight|Qt::AlignVCenter,strAmp);
            } else
            {
                deltaAmptdGab = gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerDeltaIndex[i]];
//                refAmptdGab = gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[i]];
//                refAmptdGab = mMarkerRefAmpt;
                refAmptdGab = gctrlmana->gMarkerRefAmpt[i];
                markerLevel = deltaAmptdGab - refAmptdGab;

                //                mval = mbaselevel  - mdiv- mdiv * i;
                switch (gAmptdUnit)
                {
                case BIT_DBM:
                    sprintf(strAmp, "%.2f dB", markerLevel);
                    break;
                case BIT_DBV:
                    sprintf(strAmp, "%.2f dB", markerLevel/* + dBmVFix*/);
                    break;
                case BIT_DBMV:
                    sprintf(strAmp, "%.2f dB", markerLevel/* + dBmVFix*/);
                    break;
                case BIT_DBUV:
                    sprintf(strAmp, "%.2f dB", markerLevel/* + dBuVFix*/);
                    break;
                case BIT_VOLT:
                    refVolt = ChangedBmToUV(gctrlmana->gMarkerRefAmpt[i]);
//                    refVolt = ChangedBmToUV(mMarkerRefAmpt);
//                    deltaVolt = ChangedBmToUV(markerLevel);
                    ChangeValueToVoltStr(strAmp,markerLevel);
//                    strAmp  = QString(strAmp) + QString(" (V/V)");
                    sprintf(strAmp, "%s (V/V)", strAmp/* + dBuVFix*/);

//                    strAmp = strAmp + QString(" (V/V)");
//                    dbmToVoltCalculatorAndDisplayFunc(strAmp, markerLevel);
                    break;
                case BIT_WATTS:
                    refWatt = ChangedBmToMW(gctrlmana->gMarkerRefAmpt[i]);
//                    refWatt = ChangedBmToMW(mMarkerRefAmpt);
//                    deltaWatt = ChangedBmToMW(markerLevel);
                    ChangeValueToWattStr(strAmp,markerLevel);
//                    strAmp  = QString(strAmp) + QString(" (W/W)");
//                    sprintf(strAmp, "%.2f (W/W)", deltaWatt/* + dBuVFix*/);
                    sprintf(strAmp, "%s (W/W)", strAmp/* + dBuVFix*/);

//                    strAmp = strAmp + QString(" (W/W)");
//                    dbmToWattsCalculatorAndDisplayFunc(strAmp, markerLevel);
                    break;
                }
                painter->drawText(markerInfoX + 2 * markerwidth,BIT_GRID_START_Y + (markerheight * markercnt),2 * markerwidth,markerheight,Qt::AlignRight|Qt::AlignVCenter,strAmp);
            }
            ++markercnt;
        }
        else
        {
            // Delta Display
            strLabel = QString("R%1").arg(i + 1);
            painter->drawText(markerInfoX + 2,BIT_GRID_START_Y + ((markerheight * markercnt)),markerwidth,markerheight, Qt::AlignLeft|Qt::AlignVCenter,strLabel);

            freqValue = gctrlmana->gMarkerNormalFreq[i] + mFreqOffset;
            strValue = freqValueToQstring(freqValue);
            painter->drawText(markerInfoX + 0.5 * markerwidth, BIT_GRID_START_Y + ((markerheight * markercnt)),1.5 * markerwidth + BIT_MARKER_LINEERROR,markerheight,Qt::AlignRight|Qt::AlignVCenter,strValue);

            if ( gctrlmana->gMarkerNormalFreq[i] < gfreqinfo.gstartfreq) {
                sprintf(strAmp,"- -");
                painter->drawText(markerInfoX + 2 * markerwidth, BIT_GRID_START_Y + ((markerheight * markercnt)),2 * markerwidth,markerheight,Qt::AlignRight|Qt::AlignVCenter,strAmp);
            } else if ( gctrlmana->gMarkerNormalFreq[i] > gfreqinfo.gstopfreq) {
                sprintf(strAmp,"- -");
                painter->drawText(markerInfoX + 2 * markerwidth, BIT_GRID_START_Y + ((markerheight * markercnt)),2 * markerwidth,markerheight,Qt::AlignRight|Qt::AlignVCenter,strAmp);
            } else {
//                markerLevel =(qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[i]];
//                markerLevel = mMarkerRefAmpt;
                markerLevel =(qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[i]] + gusedsize.goffsetValue;
//                markerLevel = gctrlmana->gMarkerRefAmpt[i] + gusedsize.goffsetValue;
                switch (gAmptdUnit)
                {
                case BIT_DBM:
                    sprintf(strAmp, "%.2f dBm", markerLevel);
                    break;
                case BIT_DBV:
                    sprintf(strAmp, "%.2f dBV", markerLevel + dBVFix);
                    break;
                case BIT_DBMV:
                    sprintf(strAmp, "%.2f dBmV", markerLevel + dBmVFix);
                    break;
                case BIT_DBUV:
                    sprintf(strAmp, "%.2f dBuV", markerLevel + dBuVFix);
                    break;
                case BIT_VOLT:
                    dbmToVoltCalculatorAndDisplayFunc(strAmp, markerLevel);
                    break;
                case BIT_WATTS:
                    dbmToWattsCalculatorAndDisplayFunc(strAmp, markerLevel);

                    break;
                }
            }
            painter->drawText(markerInfoX + 2 * markerwidth, BIT_GRID_START_Y + ((markerheight * markercnt)),2 * markerwidth,markerheight,Qt::AlignRight|Qt::AlignVCenter,strAmp);
            ++markercnt;
            // Delta Display
            strLabel = QString("D%1").arg(i + 1);
            painter->drawText(markerInfoX + 2,BIT_GRID_START_Y + ((markerheight * markercnt)),markerwidth,markerheight, Qt::AlignLeft|Qt::AlignVCenter,strLabel);

            deltaFreq = gctrlmana->gMarkerDeltaFreq[i] - gctrlmana->gMarkerNormalFreq[i];
            if (deltaFreq < 0) {
                deltaFreq *= -1;
                minusFlag = 1;
            }
            strValue = freqValueToQstring(deltaFreq);
            if (minusFlag == 1)
                strValue = QString("-%1").arg(strValue);

            painter->drawText(markerInfoX + 0.5 * markerwidth, BIT_GRID_START_Y + ((markerheight * markercnt)),1.5 * markerwidth + BIT_MARKER_LINEERROR,markerheight,Qt::AlignRight|Qt::AlignVCenter,strValue);

            if ( gctrlmana->gMarkerDeltaFreq[i] < gfreqinfo.gstartfreq)
            {
                sprintf(strAmp,"- -");
                painter->drawText(markerInfoX + 2 * markerwidth, BIT_GRID_START_Y + ((markerheight * markercnt)),2 * markerwidth,markerheight,Qt::AlignRight|Qt::AlignVCenter,strAmp);
            } else if ( gctrlmana->gMarkerDeltaFreq[i] > gfreqinfo.gstopfreq)
            {
                sprintf(strAmp,"- -");
                painter->drawText(markerInfoX + 2 * markerwidth, BIT_GRID_START_Y + ((markerheight * markercnt)),2 * markerwidth,markerheight,Qt::AlignRight|Qt::AlignVCenter,strAmp);
            } else
            {
                deltaAmptdGab = gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerDeltaIndex[i]];
//                refAmptdGab = gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[i]];
//                refAmptdGab = mMarkerRefAmpt;
                refAmptdGab =(qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[i]];
//                refAmptdGab = gctrlmana->gMarkerRefAmpt[i];
                markerLevel = deltaAmptdGab - refAmptdGab;

                //                mval = mbaselevel  - mdiv- mdiv * i;
                switch (gAmptdUnit)
                {
                case BIT_DBM:
                    sprintf(strAmp, "%.2f dB", markerLevel);
                    break;
                case BIT_DBV:
                    sprintf(strAmp, "%.2f dB", markerLevel/* + dBmVFix*/);
                    break;
                case BIT_DBMV:
                    sprintf(strAmp, "%.2f dB", markerLevel/* + dBmVFix*/);
                    break;
                case BIT_DBUV:
                    sprintf(strAmp, "%.2f dB", markerLevel/* + dBuVFix*/);
                    break;
                case BIT_VOLT:
                    refVolt = ChangedBmToUV(gctrlmana->gMarkerRefAmpt[i]);
//                    refVolt = ChangedBmToUV(mMarkerRefAmpt);
//                    deltaVolt = ChangedBmToUV(markerLevel);
                    ChangeValueToVoltStr(strAmp,markerLevel);
//                    strAmp  = QString(strAmp) + QString(" (V/V)");
                    sprintf(strAmp, "%s (V/V)", strAmp/* + dBuVFix*/);

//                    strAmp = strAmp + QString(" (V/V)");
//                    dbmToVoltCalculatorAndDisplayFunc(strAmp, markerLevel);
                    break;
                case BIT_WATTS:
                    refWatt = ChangedBmToMW(gctrlmana->gMarkerRefAmpt[i]);
//                    refWatt = ChangedBmToMW(mMarkerRefAmpt);
//                    deltaWatt = ChangedBmToMW(markerLevel);
                    ChangeValueToWattStr(strAmp,markerLevel);
//                    strAmp  = QString(strAmp) + QString(" (W/W)");
//                    sprintf(strAmp, "%.2f (W/W)", deltaWatt/* + dBuVFix*/);
                    sprintf(strAmp, "%s (W/W)", strAmp/* + dBuVFix*/);

//                    strAmp = strAmp + QString(" (W/W)");
//                    dbmToWattsCalculatorAndDisplayFunc(strAmp, markerLevel);
                    break;
                }
                painter->drawText(markerInfoX + 2 * markerwidth,BIT_GRID_START_Y + (markerheight * markercnt),2 * markerwidth,markerheight,Qt::AlignRight|Qt::AlignVCenter,strAmp);
            }
            ++markercnt;
        }
        renderTopMarkerPart(painter,strLabel + QString(" ") + strValue);
    }
    return ;
}

void BitView::markerTableInfoDisplayFunc(QPainter *painter)
{
    qreal markernoise;
    QString strLabel;
    char strAmp[20];
//    qint32 i = 0;
    qint32 cnt = 0;
    QString strValue;
    qreal freqValue = 0;
    long long deltaFreq = 0;
    qint32 minusFlag = 0;
    qreal deltaAmptdGab = 0.;
    qreal refAmptdGab = 0.;
//    qreal subtractGab = 0;
    qreal markerLevel = 0;
    const qreal markerwidth  = gusedsize.gridXSpace;
    const qreal markerheight = (BIT_MARKER_TABLE_HEIGHT - LINEREEOR)/6;
    painter->setFont(QFont("Arial", 12));

    for(qint32 i = 0;i<BIT_MARKER_TOTAL_CNT;i++)
    {
        if(gctrlmana->gMarkerView[i] == BITON)
        {
            if(i == gctrlmana->gMarkerSelect)
            {
                painter->setPen(mMarkerColor.curmarker);
            }else
            {
                painter->setPen(mMarkerColor.defaultmarker);
            }

            // MARKER -> NORMAL
            if (gctrlmana->gMarkerType[i] == BIT_NORMAL)
            {
                strLabel = QString("M%1").arg(i + 1);
                painter->drawText(gusedsize.gridX[0] , this->height() - BIT_MARKER_TABLE_HEIGHT +  (markerheight * cnt) ,0.5 * markerwidth, markerheight, Qt::AlignLeft|Qt::AlignVCenter, strLabel);

                freqValue = gctrlmana->gMarkerNormalFreq[i] + mFreqOffset;
                strValue = freqValueToQstring(freqValue);
                painter->drawText(gusedsize.gridX[0] + 0.5 * markerwidth, this->height() - BIT_MARKER_TABLE_HEIGHT + (markerheight * cnt) , 1.5 * markerwidth, markerheight, Qt::AlignRight|Qt::AlignVCenter, strValue);

                if ( gctrlmana->gMarkerNormalFreq[i] < gfreqinfo.gstartfreq) {
                    sprintf(strAmp,"- -");
                    painter->drawText(gusedsize.gridX[0] + 2 * markerwidth, this->height() - BIT_MARKER_TABLE_HEIGHT +  (markerheight * cnt) ,1.5 * markerwidth, markerheight, Qt::AlignRight|Qt::AlignVCenter, strAmp);
                } else if ( gctrlmana->gMarkerNormalFreq[i] > gfreqinfo.gstopfreq) {
                    sprintf(strAmp,"- -");
                    painter->drawText(gusedsize.gridX[0] + 2 * markerwidth, this->height() - BIT_MARKER_TABLE_HEIGHT +  (markerheight * cnt) , 1.5 * markerwidth, markerheight, Qt::AlignRight|Qt::AlignVCenter, strAmp);
                } else
                {
                    markerLevel =(qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[i]];

                    switch (gAmptdUnit)
                    {
                    case BIT_DBM:
                        sprintf(strAmp, "%.2f dBm", markerLevel);
                        break;
                    case BIT_DBV:
                        sprintf(strAmp, "%.2f dBV", markerLevel + dBVFix);
                        break;
                    case BIT_DBMV:
                        sprintf(strAmp, "%.2f dBmV", markerLevel + dBmVFix);
                        break;
                    case BIT_DBUV:
                        sprintf(strAmp, "%.2f dBuV", markerLevel + dBuVFix);
                        break;
                    case BIT_VOLT:
                        dbmToVoltCalculatorAndDisplayFunc(strAmp, markerLevel);
                        break;
                    case BIT_WATTS:
                        dbmToWattsCalculatorAndDisplayFunc(strAmp, markerLevel);
                        break;
                    }
                    painter->drawText(gusedsize.gridX[0] + 2 * markerwidth, this->height() - BIT_MARKER_TABLE_HEIGHT + (markerheight * cnt) ,1.5 * markerwidth, markerheight, Qt::AlignRight|Qt::AlignVCenter, strAmp);
                }
                if(gctrlmana->gMarkerNoise[i] == 1)
                {
                    markernoise = calculateMarkerNoiseValue((qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[i]],gfreqinfo.grbwfreq);
                    sprintf(strAmp, "%.2f dBm/Hz", markernoise);
                    painter->drawText(gusedsize.gridX[8] , this->height() - BIT_MARKER_TABLE_HEIGHT + (markerheight * cnt) ,2 * markerwidth, markerheight, Qt::AlignRight|Qt::AlignVCenter, strAmp);
                }

            }
            else
            {
                // Delta Display
                strLabel = QString("R%1").arg(i + 1);
                painter->drawText(gusedsize.gridX[0] , this->height() - BIT_MARKER_TABLE_HEIGHT + (markerheight * cnt) , 0.5 * markerwidth, markerheight, Qt::AlignLeft|Qt::AlignVCenter, strLabel);

                freqValue = gctrlmana->gMarkerNormalFreq[i];
                strValue = freqValueToQstring(freqValue);
                painter->drawText(gusedsize.gridX[0] +  0.5 * markerwidth, this->height() - BIT_MARKER_TABLE_HEIGHT  + (markerheight * cnt) , 1.5 * markerwidth, markerheight, Qt::AlignRight|Qt::AlignVCenter, strValue);

                if ( gctrlmana->gMarkerNormalFreq[i] < gfreqinfo.gstartfreq) {
                    sprintf(strAmp,"- -");
                    painter->drawText(gusedsize.gridX[0] + 2 * markerwidth, this->height() - BIT_MARKER_TABLE_HEIGHT + (markerheight * cnt) , 1.5 * markerwidth, markerheight, Qt::AlignRight|Qt::AlignVCenter, strAmp);
                } else if ( gctrlmana->gMarkerNormalFreq[i] > gfreqinfo.gstopfreq) {
                    sprintf(strAmp,"- -");
                    painter->drawText(gusedsize.gridX[0] + 2 * markerwidth, this->height() - BIT_MARKER_TABLE_HEIGHT + (markerheight * cnt) , 1.5 * markerwidth, markerheight, Qt::AlignRight|Qt::AlignVCenter, strAmp);
                } else {
                    markerLevel =(qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[i]];
                    switch (gAmptdUnit)
                    {
                    case BIT_DBM:
                        sprintf(strAmp, "%.2f dBm", markerLevel);
                        break;
                    case BIT_DBV:
                        sprintf(strAmp, "%.2f dBV", markerLevel + dBVFix);
                        break;
                    case BIT_DBMV:
                        sprintf(strAmp, "%.2f dBmV", markerLevel + dBmVFix);
                        break;
                    case BIT_DBUV:
                        sprintf(strAmp, "%.2f dBuV", markerLevel + dBuVFix);
                        break;
                    case BIT_VOLT:
                        dbmToVoltCalculatorAndDisplayFunc(strAmp, markerLevel);
                        break;
                    case BIT_WATTS:
                        dbmToWattsCalculatorAndDisplayFunc(strAmp, markerLevel);
                        break;
                    }
                }
                painter->drawText(gusedsize.gridX[0] + 2 * markerwidth, this->height() - BIT_MARKER_TABLE_HEIGHT + (markerheight * cnt) , 1.5 * markerwidth, markerheight, Qt::AlignRight|Qt::AlignVCenter, strAmp);

                // Delta Display
                strLabel = QString("D%1").arg(i + 1);

                painter->drawText(gusedsize.gridX[4], this->height() - BIT_MARKER_TABLE_HEIGHT + (markerheight * cnt) , 0.5 * markerwidth, markerheight, Qt::AlignLeft|Qt::AlignVCenter, strLabel);

                deltaFreq = gctrlmana->gMarkerDeltaFreq[i] - gctrlmana->gMarkerNormalFreq[i];
                if (deltaFreq < 0) {
                    deltaFreq *= -1;
                    minusFlag = 1;
                }
                strValue = freqValueToQstring(deltaFreq);
                if (minusFlag == 1)
                    strValue = QString("-%1").arg(strValue);

                painter->drawText(gusedsize.gridX[4] +  0.5 * markerwidth, this->height() - BIT_MARKER_TABLE_HEIGHT + (markerheight * cnt) , 1.5 * markerwidth, markerheight, Qt::AlignRight|Qt::AlignVCenter, strValue);

                if ( gctrlmana->gMarkerDeltaFreq[i] < gfreqinfo.gstartfreq)
                {
                    sprintf(strAmp,"- -");
                    painter->drawText(gusedsize.gridX[4] + 2 * markerwidth, this->height() - BIT_MARKER_TABLE_HEIGHT + (markerheight * cnt) , 1.5 * markerwidth, markerheight, Qt::AlignRight|Qt::AlignVCenter, strAmp);
                } else if ( gctrlmana->gMarkerDeltaFreq[i] > gfreqinfo.gstopfreq)
                {
                    sprintf(strAmp,"- -");
                    painter->drawText(gusedsize.gridX[4] + 2 * markerwidth, this->height() - BIT_MARKER_TABLE_HEIGHT + (markerheight * cnt) , 1.5 * markerwidth, markerheight, Qt::AlignRight|Qt::AlignVCenter, strAmp);
                } else
                {
                    deltaAmptdGab = gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerDeltaIndex[i]];
                    refAmptdGab = gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerNormalIndex[i]];
                    markerLevel = deltaAmptdGab - refAmptdGab;
                    switch (gAmptdUnit)
                    {
                    case BIT_DBM:
                        sprintf(strAmp, "%.2f dB", markerLevel);
                        break;
                    case BIT_DBV:
                        sprintf(strAmp, "%.2f dB", markerLevel + dBVFix);
                        break;
                    case BIT_DBMV:
                        sprintf(strAmp, "%.2f dB", markerLevel + dBmVFix);
                        break;
                    case BIT_DBUV:
                        sprintf(strAmp, "%.2f dB", markerLevel + dBuVFix);
                        break;
                    case BIT_VOLT:
                        dbmToVoltCalculatorAndDisplayFunc(strAmp, markerLevel);
                        break;
                    case BIT_WATTS:
                        dbmToWattsCalculatorAndDisplayFunc(strAmp, markerLevel);
                        break;
                    }
                    painter->drawText(gusedsize.gridX[4] + 2 * markerwidth, this->height() - BIT_MARKER_TABLE_HEIGHT + (markerheight * cnt) , 1.5 * markerwidth, markerheight, Qt::AlignRight|Qt::AlignVCenter, strAmp);
                }
                if(gctrlmana->gMarkerNoise[i] == 1)
                {
                    markernoise = calculateMarkerNoiseValue((qreal)gbitbuffer.trace_render[gctrlmana->gtraceIndex][gctrlmana->gMarkerDeltaIndex[i]],gfreqinfo.grbwfreq);
                    sprintf(strAmp, "%.2f dBm/Hz", markernoise);
                    painter->drawText(gusedsize.gridX[8], this->height() - BIT_MARKER_TABLE_HEIGHT + (markerheight * cnt) ,2 * markerwidth, markerheight, Qt::AlignRight|Qt::AlignVCenter, strAmp);
                }
            }
            ++cnt;

        }
    }
    return;
}


//Marker part end.
//==========================================================================

//==========================================================================
//Limit Part
//Tony 1112
void BitView::renderLimitPart(QPainter *pPainter)
{
    qreal limitAmpt = 0.0;
    if(mlimitTableWidget->bUpdateLimit)
    {
        mlimitTableWidget->getTableWidgetValue();
    }

    for(qint32 i = 0;i<BIT_LIMIT_TOTAL_CNT;i++)
    {
        for(qint32 j = 0;j<gctrlmana->gLimitPointCnt[i];j++)
        {
            limitAmpt = gctrlmana->gLimitAmplitude[i][j];
            limitAmpt += gusedsize.goffsetValue;
//            gctrlmana->gLimitAmplitude[i][j] += gusedsize.goffsetValue;
            limitXAxisCalculatorFunc((qreal)(gctrlmana->gLimitFreq[i][j]* BV_MHZ),j,i);
//            limitYAxisCalculatorFunc(gctrlmana->gLimitAmplitude[i][j],j,i);
            limitYAxisCalculatorFunc(limitAmpt,j,i);
        }
        limitLineInterpolationCalculatorFunc(i);
    }
    getLowerUpperLimitLineInterpolation();
    renderLimitLine(pPainter);
    //Tony 1116
    if((qint32)(gctrlmana->gtracetype[gctrlmana->gtraceIndex]) != BIT_TRACE_OFF)
    {
        renderLimitSiglines(pPainter);
        renderLimitMargin(pPainter);
        renderLimitTestResult(pPainter);
    }

    return ;
}

void BitView::renderLimitLine(QPainter *painter)
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
    qreal topLevel   = gusedsize.goffsetValue + gusedsize.grefValue ;
    qreal lowLevel   = gusedsize.goffsetValue + gusedsize.grefValue - gusedsize.gdivValue * 10;
    qreal mbottom    = TOPDIS + gusedsize.gpicheight - LINEREEOR;
    qreal pixedstepX = (gusedsize.gpicwidth - 2 * LINEREEOR)/(gbitbuffer.gtracenum-1);
    //Drawing  Upper Sengment Limit Line
    for (k = 0; k < BIT_LIMIT_TOTAL_CNT; k++)
    {
        if(gctrlmana->gLimitView[k] == BITOFF) continue;
        if(gctrlmana->gLimitPointCnt[k]  == 0) continue;

        if (gctrlmana->gLimitType[k] == BIT_LIMIT_UPPER)
        {
            painter->setPen(mLimitColor.upperlimit);
        }
        else if (gctrlmana->gLimitType[k] == BIT_LIMIT_LOWER)
        {
            painter->setPen(mLimitColor.lowerlimit);
        }

        for(i = 1;i<gctrlmana->gLimitPointCnt[k];i++){
            StartXPos = gctrlmana->gLimitpointsXIndex[k][i-1];
            StopXPos = gctrlmana->gLimitpointsXIndex[k][i];

            //Johnson 0910
            StartXAxis = StartXPos * pixedstepX+BIT_GRID_START_X;
            StartYAxis = gctrlmana->gLimitpointsY[k][i-1];
            StopXAxis  = StopXPos* pixedstepX+BIT_GRID_START_X;
            StopYAxis  = gctrlmana->gLimitpointsY[k][i];
            gctrlmana->gLimitpointsX[k][i-1] = StartXAxis;

            if(StopXAxis-StartXAxis != 0)
            {
                dSlope = (StopYAxis-StartYAxis)/(StopXAxis-StartXAxis);
            }
            //Johnson 0910 change
            if(gctrlmana->gLimitAmplitude[k][i-1]>topLevel||gctrlmana->gLimitAmplitude[k][i-1]<lowLevel||gctrlmana->gLimitAmplitude[k][i]>topLevel||gctrlmana->gLimitAmplitude[k][i]<lowLevel){
                if(StartXAxis == StopXAxis){
                    if(StartYAxis<BIT_GRID_START_Y)
                        StartYAxis = BIT_GRID_START_Y;
                    else if(StartYAxis > mbottom)
                        StartYAxis = mbottom;
                    if(StopYAxis<BIT_GRID_START_Y)
                        StopYAxis  = BIT_GRID_START_Y;
                    else if(StopYAxis>mbottom)
                        StopYAxis  = mbottom;
                    painter->drawLine(StartXAxis, StartYAxis, StopXAxis,  StopYAxis);
                }
                else if(dSlope == 0){
                    if(StartYAxis<BIT_GRID_START_Y)
                    {
                        StartYAxis = BIT_GRID_START_Y;
                        StopYAxis = BIT_GRID_START_Y;
                    }
                    else if(StopYAxis>mbottom)
                    {
                        StartYAxis = mbottom;
                        StopYAxis = mbottom;
                    }
                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
                else {
                    qreal constC = StartYAxis-dSlope*StartXAxis;

                    if(dSlope>0){
                        if(gctrlmana->gLimitAmplitude[k][i-1] > topLevel){
                            if(gctrlmana->gLimitAmplitude[k][i] >= topLevel)
                            {
                                QPen pen;
                                if (gctrlmana->gLimitType[k] == BIT_LIMIT_UPPER)
                                    pen = QPen(mLimitColor.upperlimit);
                                else if (gctrlmana->gLimitType[k] == BIT_LIMIT_LOWER)
                                    pen = QPen(mLimitColor.lowerlimit);
                                //QPen pen(Qt::yellow);

                                pen.setWidth(2);
                                painter->setPen(pen);
                                painter->drawLine(StartXAxis,BIT_GRID_START_Y,StopXAxis,BIT_GRID_START_Y);
                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                            else if(gctrlmana->gLimitAmplitude[k][i]<topLevel && gctrlmana->gLimitAmplitude[k][i]>=lowLevel){
                                qreal tempY = BIT_GRID_START_Y;
                                qreal tempX = (tempY-constC)/dSlope;
                                painter->drawLine(tempX, tempY, StopXAxis,  StopYAxis);

                                QPen pen;
                                if (gctrlmana->gLimitType[k] == BIT_LIMIT_UPPER)
                                    pen = QPen(mLimitColor.upperlimit);
                                else if (gctrlmana->gLimitType[k] == BIT_LIMIT_LOWER)
                                    pen = QPen(mLimitColor.lowerlimit);
                                //QPen pen(Qt::yellow);

                                pen.setWidth(2);
                                painter->setPen(pen);
                                painter->drawLine(StartXAxis,tempY,tempX,tempY);
                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                            else if(gctrlmana->gLimitAmplitude[k][i]<lowLevel){
                                qreal tempY1 = BIT_GRID_START_Y;
                                qreal tempX1 = (tempY1-constC)/dSlope;
                                qreal tempY2 = mbottom;
                                qreal tempX2 = (tempY2-constC)/dSlope;

                                painter->drawLine(tempX1, tempY1, tempX2,  tempY2);

                                QPen pen;
                                if (gctrlmana->gLimitType[k] == BIT_LIMIT_UPPER)
                                    pen = QPen(mLimitColor.upperlimit);
                                else if (gctrlmana->gLimitType[k] == BIT_LIMIT_LOWER)
                                    pen = QPen(mLimitColor.lowerlimit);

                                //QPen pen(Qt::yellow);
                                pen.setWidth(2);
                                painter->setPen(pen);

                                painter->drawLine(StartXAxis, tempY1, tempX1,  tempY1);
                                painter->drawLine(tempX2, tempY2, StopXAxis,  tempY2);

                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                        }
                        else if(gctrlmana->gLimitAmplitude[k][i-1]<=topLevel && gctrlmana->gLimitAmplitude[k][i-1]>=lowLevel){
                           if(gctrlmana->gLimitAmplitude[k][i]<=lowLevel){
                                qreal tempY = mbottom;
                                qreal tempX = (tempY-constC)/dSlope;

                                painter->drawLine(StartXAxis, StartYAxis, tempX,  tempY);

                                QPen pen;
                                if (gctrlmana->gLimitType[k] == BIT_LIMIT_UPPER)
                                    pen = QPen(mLimitColor.upperlimit);
                                else if (gctrlmana->gLimitType[k] == BIT_LIMIT_LOWER)
                                    pen = QPen(mLimitColor.lowerlimit);
                                pen.setWidth(2);
                                painter->setPen(pen);
                                painter->drawLine(tempX, tempY, StopXAxis,  tempY);
                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                        }
                        else if(gctrlmana->gLimitAmplitude[gctrlmana->gLimitSelect][i-1]<lowLevel){
                            QPen pen;
                            if (gctrlmana->gLimitType[k] == BIT_LIMIT_UPPER)
                                pen = QPen(mLimitColor.upperlimit);
                            else if (gctrlmana->gLimitType[k] == BIT_LIMIT_LOWER)
                                pen = QPen(mLimitColor.lowerlimit);
                            pen.setWidth(2);
                            painter->setPen(pen);
                            painter->drawLine(StartXAxis,mbottom,StopXAxis,mbottom);
                            pen.setWidth(1);
                            painter->setPen(pen);
                        }
                    }
                    else if(dSlope<0){
                        if(gctrlmana->gLimitAmplitude[k][i-1]<lowLevel){
                            if(gctrlmana->gLimitAmplitude[k][i]<=lowLevel){
                                QPen pen;
                                if (gctrlmana->gLimitType[k] == BIT_LIMIT_UPPER)
                                    pen = QPen(mLimitColor.upperlimit);
                                else if (gctrlmana->gLimitType[k] == BIT_LIMIT_LOWER)
                                    pen = QPen(mLimitColor.lowerlimit);

                                pen.setWidth(2);
                                painter->setPen(pen);
                                painter->drawLine(StartXAxis,mbottom,StopXAxis,mbottom);
                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                            else if(gctrlmana->gLimitAmplitude[k][i]<=topLevel&&gctrlmana->gLimitAmplitude[k][i]>lowLevel){
                                qreal tempY = mbottom;
                                qreal tempX = (tempY-constC)/dSlope;
                                painter->drawLine(tempX, tempY, StopXAxis,  StopYAxis);

                                QPen pen;
                                if (gctrlmana->gLimitType[k] == BIT_LIMIT_UPPER)
                                    pen = QPen(mLimitColor.upperlimit);
                                else if (gctrlmana->gLimitType[k] == BIT_LIMIT_LOWER)
                                    pen = QPen(mLimitColor.lowerlimit);

                                pen.setWidth(2);
                                painter->setPen(pen);
                                painter->drawLine(StartXAxis,tempY,tempX,tempY);
                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                            else if(gctrlmana->gLimitAmplitude[k][i]>topLevel){
                                qreal tempY1 = mbottom;
                                qreal tempX1 = (tempY1-constC)/dSlope;
                                qreal tempY2 = BIT_GRID_START_Y;
                                qreal tempX2 = (tempY2-constC)/dSlope;

                                painter->drawLine(tempX1, tempY1, tempX2,  tempY2);

                                QPen pen;
                                if (gctrlmana->gLimitType[k] == BIT_LIMIT_UPPER)
                                    pen = QPen(mLimitColor.upperlimit);
                                else if (gctrlmana->gLimitType[k] == BIT_LIMIT_LOWER)
                                    pen = QPen(mLimitColor.lowerlimit);

                                pen.setWidth(2);
                                painter->setPen(pen);

                                painter->drawLine(StartXAxis, tempY1, tempX1,  tempY1);
                                painter->drawLine(tempX2, tempY2, StopXAxis,  tempY2);

                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                        }
                        else if(gctrlmana->gLimitAmplitude[k][i-1]<=topLevel&&gctrlmana->gLimitAmplitude[k][i-1]>=lowLevel){
                           if(gctrlmana->gLimitAmplitude[k][i]>=topLevel)
                           {
                                qreal tempY = BIT_GRID_START_Y;
                                qreal tempX = (tempY-constC)/dSlope;

                                painter->drawLine(StartXAxis, StartYAxis, tempX,  tempY);

                                QPen pen;
                                if (gctrlmana->gLimitType[k] == BIT_LIMIT_UPPER)
                                    pen = QPen(mLimitColor.upperlimit);
                                else if (gctrlmana->gLimitType[k] == BIT_LIMIT_LOWER)
                                    pen = QPen(mLimitColor.lowerlimit);

                                pen.setWidth(2);
                                painter->setPen(pen);

                                painter->drawLine(tempX, tempY, StopXAxis,  tempY);

                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                        }
                        else if(gctrlmana->gLimitAmplitude[k][i]>topLevel){
                            QPen pen;
                            if (gctrlmana->gLimitType[k] == BIT_LIMIT_UPPER)
                                pen = QPen(mLimitColor.upperlimit);
                            else if (gctrlmana->gLimitType[k] == BIT_LIMIT_LOWER)
                                pen = QPen(mLimitColor.lowerlimit);

                            pen.setWidth(2);
                            painter->setPen(pen);
                            painter->drawLine(StartXAxis,BIT_GRID_START_Y,StopXAxis,BIT_GRID_START_Y);
                            pen.setWidth(1);
                            painter->setPen(pen);
                        }
                    }
                }
            }
            else painter->drawLine(StartXAxis, StartYAxis, StopXAxis,  StopYAxis);
        }
        QPen pen;
        if (gctrlmana->gLimitType[k] == BIT_LIMIT_UPPER){
            pen = QPen(mLimitColor.upperlimit);
            if(gctrlmana->gLimitAmplitude[k][0] >= lowLevel && gctrlmana->gLimitAmplitude[k][0] <= topLevel)
            {
                StartXAxis = gctrlmana->gLimitpointsXIndex[k][0]*pixedstepX + BIT_GRID_START_X - 1;
                StartYAxis = BIT_GRID_START_Y;
                StopXAxis  = gctrlmana->gLimitpointsXIndex[k][0]*pixedstepX + BIT_GRID_START_X - 1;
                StopYAxis  = gctrlmana->gLimitpointsY[k][0];
                painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
            }
            else if(gctrlmana->gLimitAmplitude[k][0] < lowLevel)
            {
                StartXAxis = gctrlmana->gLimitpointsXIndex[k][0] * pixedstepX + BIT_GRID_START_X - 1;
                StartYAxis = mbottom;
                StopXAxis  = gctrlmana->gLimitpointsXIndex[k][0] * pixedstepX + BIT_GRID_START_X - 1;
                StopYAxis  = BIT_GRID_START_Y;
                painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
            }
            qint32 gTotalDot = gctrlmana->gLimitPointCnt[k];
            if(gctrlmana->gLimitAmplitude[k][gTotalDot-1] >= lowLevel && gctrlmana->gLimitAmplitude[k][gTotalDot-1] <= topLevel)
            {
                StartXAxis = gctrlmana->gLimitpointsXIndex[k][gTotalDot-1] * pixedstepX + BIT_GRID_START_X + 1;
                StartYAxis = BIT_GRID_START_Y;
                StopXAxis  = gctrlmana->gLimitpointsXIndex[k][gTotalDot-1] * pixedstepX + BIT_GRID_START_X + 1;
                StopYAxis  = gctrlmana->gLimitpointsY[k][gTotalDot-1];
                painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
            }
            else if(gctrlmana->gLimitAmplitude[k][gTotalDot-1] < lowLevel)
            {
                StartXAxis = gctrlmana->gLimitpointsXIndex[k][gTotalDot-1] * pixedstepX + BIT_GRID_START_X + 1;
                StartYAxis = mbottom;
                StopXAxis  = gctrlmana->gLimitpointsXIndex[k][gTotalDot-1] * pixedstepX + BIT_GRID_START_X + 1;
                StopYAxis  = BIT_GRID_START_Y;
                painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
            }
        }
        else if (gctrlmana->gLimitType[k] == BIT_LIMIT_LOWER)
        {
            pen = QPen(mLimitColor.lowerlimit);
            if(gctrlmana->gLimitAmplitude[k][0] >= lowLevel && gctrlmana->gLimitAmplitude[k][0] <= topLevel)
            {
                StartXAxis = gctrlmana->gLimitpointsXIndex[k][0] * pixedstepX + BIT_GRID_START_X - 1;
                StartYAxis = mbottom - 1;
                StopXAxis  = gctrlmana->gLimitpointsXIndex[k][0] * pixedstepX + BIT_GRID_START_X - 1;
                StopYAxis  = gctrlmana->gLimitpointsY[k][0];
                painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
            }
            else if(gctrlmana->gLimitAmplitude[k][0] > topLevel)
            {
                StartXAxis = gctrlmana->gLimitpointsXIndex[k][0] * pixedstepX + BIT_GRID_START_X - 1;
                StartYAxis = BIT_GRID_START_Y;
                StopXAxis  = gctrlmana->gLimitpointsXIndex[k][0] * pixedstepX + BIT_GRID_START_X - 1;
                StopYAxis  = mbottom - 1;
                painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
            }
            qint32 gTotalDot = gctrlmana->gLimitPointCnt[k];
            if(gctrlmana->gLimitAmplitude[k][gTotalDot-1] >= lowLevel && gctrlmana->gLimitAmplitude[k][gTotalDot-1] <= topLevel)
            {
                StartXAxis = gctrlmana->gLimitpointsXIndex[k][gTotalDot-1] * pixedstepX + BIT_GRID_START_X+1;
                StartYAxis = mbottom - 1;
                StopXAxis  = gctrlmana->gLimitpointsXIndex[k][gTotalDot-1] * pixedstepX + BIT_GRID_START_X+1;
                StopYAxis  = gctrlmana->gLimitpointsY[k][gTotalDot-1];
                painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
            }
            else if(gctrlmana->gLimitAmplitude[k][gTotalDot-1] > topLevel)
            {
                StartXAxis = gctrlmana->gLimitpointsXIndex[k][gTotalDot-1] * pixedstepX + BIT_GRID_START_X+1;
                StartYAxis = BIT_GRID_START_Y;
                StopXAxis  = gctrlmana->gLimitpointsXIndex[k][gTotalDot-1] * pixedstepX + BIT_GRID_START_X+1;
                StopYAxis  = mbottom - 1;
                painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
            }
        }
      }
}

void BitView::renderLimitMargin(QPainter *painter)
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

    qreal margin      = 0.;

    qreal topLevel   = gusedsize.goffsetValue + gusedsize.grefValue ;
    qreal lowLevel   = gusedsize.goffsetValue + gusedsize.grefValue - gusedsize.gdivValue * 10;
    qreal mbottom    = TOPDIS + gusedsize.gpicheight - LINEREEOR;
    qreal pixedstepX = (gusedsize.gpicwidth - 2 * LINEREEOR)/(gbitbuffer.gtracenum-1);

    //Drawing  BIT_LIMIT_UPPER Sengment Limit Line
    for (k = 0; k < BIT_LIMIT_TOTAL_CNT; k++)
    {
        if(gctrlmana->gLimitMargin[k] == BITOFF) continue;
        if(gctrlmana->gLimitMarginValue[k] == 0.) continue;
        if(gctrlmana->gLimitView[k] == BITOFF) continue;
        if(gctrlmana->gLimitPointCnt[k] == 0)   continue;

        QPen globalPen;
        if (gctrlmana->gLimitType[k] == BIT_LIMIT_UPPER)
            globalPen = QPen(mLimitColor.uppermargin);
        else if (gctrlmana->gLimitType[k] == BIT_LIMIT_LOWER)
            globalPen = QPen(mLimitColor.lowermargin);
        globalPen.setStyle(Qt::DotLine);
        painter->setPen(globalPen);

        if (gctrlmana->gLimitType[k] == BIT_LIMIT_UPPER)
            margin = -gctrlmana->gLimitMarginValue[k];
        else if (gctrlmana->gLimitType[k] == BIT_LIMIT_LOWER)
            margin = gctrlmana->gLimitMarginValue[k];

        for(i = 1;i<gctrlmana->gLimitPointCnt[k];i++)
        {
            StartXPos = gctrlmana->gLimitpointsXIndex[k][i-1];
            StopXPos  = gctrlmana->gLimitpointsXIndex[k][i];

            if (StartXPos == 0 && StopXPos == 0)
                break;

            //Johnson 0910
            StartXAxis = StartXPos * pixedstepX + BIT_GRID_START_X;
            StartYAxis = gctrlmana->gLimitMaiginpointsY[k][i-1];
            StopXAxis  = StopXPos* pixedstepX+BIT_GRID_START_X;
            StopYAxis  = gctrlmana->gLimitMaiginpointsY[k][i];
            gctrlmana->gLimitpointsX[k][i-1] = StartXAxis;
            gctrlmana->gLimitpointsX[k][i]   = StopXAxis;

            if(StopXAxis-StartXAxis != 0)
                dSlope = (StopYAxis-StartYAxis)/(StopXAxis-StartXAxis);


            //Johnson 0910 change
            if(gctrlmana->gLimitAmplitude[k][i-1] + margin >topLevel||gctrlmana->gLimitAmplitude[k][i-1] + margin <lowLevel||
                    gctrlmana->gLimitAmplitude[k][i] + margin >topLevel||gctrlmana->gLimitAmplitude[k][i] + margin <lowLevel){
                if(StartXAxis == StopXAxis){
                    if(StartYAxis<BIT_GRID_START_Y)
                        StartYAxis = BIT_GRID_START_Y;
                    else if(StartYAxis>mbottom)
                        StartYAxis = mbottom;
                    if(StopYAxis<BIT_GRID_START_Y)
                        StopYAxis  = BIT_GRID_START_Y;
                    else if(StopYAxis>mbottom)
                        StopYAxis  = mbottom;
                    painter->drawLine(StartXAxis, StartYAxis, StopXAxis,  StopYAxis);
                }
                else if(dSlope == 0)
                {
                    if(StartYAxis<BIT_GRID_START_Y)
                    {
                        StartYAxis = BIT_GRID_START_Y;
                        StopYAxis = BIT_GRID_START_Y;
                    }
                    else if(StopYAxis>mbottom)
                    {
                        StartYAxis = mbottom;
                        StopYAxis = mbottom;
                    }
                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
                else {
                    qreal constC = StartYAxis-dSlope*StartXAxis;

                    if(dSlope>0){
                        if(gctrlmana->gLimitAmplitude[k][i-1] + margin > topLevel){
                            if(gctrlmana->gLimitAmplitude[k][i] + margin >= topLevel){
                                QPen pen;
                                if (gctrlmana->gLimitType[k] == BIT_LIMIT_UPPER)
                                    pen = QPen(mLimitColor.uppermargin);
                                else if (gctrlmana->gLimitType[k] == BIT_LIMIT_LOWER)
                                    pen = QPen(mLimitColor.lowermargin);
                                pen.setStyle(Qt::DotLine);
                                pen.setWidth(2);
                                painter->setPen(pen);
                                painter->drawLine(StartXAxis,BIT_GRID_START_Y,StopXAxis,BIT_GRID_START_Y);
                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                            else if(gctrlmana->gLimitAmplitude[k][i] + margin <topLevel&&gctrlmana->gLimitAmplitude[k][i] + margin >=lowLevel){
                                qreal tempY = BIT_GRID_START_Y;
                                qreal tempX = (tempY-constC)/dSlope;
                                painter->drawLine(tempX, tempY, StopXAxis,  StopYAxis);

                                QPen pen;
                                if (gctrlmana->gLimitType[k] == BIT_LIMIT_UPPER)
                                    pen = QPen(mLimitColor.uppermargin);
                                else if (gctrlmana->gLimitType[k] == BIT_LIMIT_LOWER)
                                    pen = QPen(mLimitColor.lowermargin);
                                pen.setStyle(Qt::DotLine);
                                pen.setWidth(2);
                                painter->setPen(pen);
                                painter->drawLine(StartXAxis,tempY,tempX,tempY);
                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                            else if(gctrlmana->gLimitAmplitude[k][i] + margin < lowLevel)
                            {
                                qreal tempY1 = BIT_GRID_START_Y;
                                qreal tempX1 = (tempY1-constC)/dSlope;
                                qreal tempY2 = mbottom;
                                qreal tempX2 = (tempY2-constC)/dSlope;

                                painter->drawLine(tempX1, tempY1, tempX2,  tempY2);

                                QPen pen;
                                if (gctrlmana->gLimitType[k] == BIT_LIMIT_UPPER) pen = QPen(Qt::darkRed);
                                else if (gctrlmana->gLimitType[k] == BIT_LIMIT_LOWER) pen = QPen(Qt::cyan);
                                pen.setStyle(Qt::DotLine);
                                pen.setWidth(2);
                                painter->setPen(pen);

                                painter->drawLine(StartXAxis, tempY1, tempX1,  tempY1);
                                painter->drawLine(tempX2, tempY2, StopXAxis,  tempY2);

                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                        }
                        else if(gctrlmana->gLimitAmplitude[k][i-1] + margin <= topLevel&&gctrlmana->gLimitAmplitude[k][i-1] + margin >= lowLevel){
                            if(gctrlmana->gLimitAmplitude[k][i] + margin < lowLevel)
                            {
                                qreal tempY = mbottom;
                                qreal tempX = (tempY-constC)/dSlope;

                                painter->drawLine(StartXAxis, StartYAxis, tempX,  tempY);

                                QPen pen;
                                if (gctrlmana->gLimitType[k] == BIT_LIMIT_UPPER) pen = QPen(Qt::darkRed);
                                else if (gctrlmana->gLimitType[k] == BIT_LIMIT_LOWER) pen = QPen(Qt::cyan);
                                pen.setStyle(Qt::DotLine);
                                pen.setWidth(2);
                                painter->setPen(pen);
                                painter->drawLine(tempX, tempY, StopXAxis,  tempY);
                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                        }
                        else if(gctrlmana->gLimitAmplitude[gctrlmana->gLimitSelect][i-1] + margin < lowLevel){
                            QPen pen;
                            if (gctrlmana->gLimitType[k] == BIT_LIMIT_UPPER)
                                pen = QPen(mLimitColor.uppermargin);
                            else if (gctrlmana->gLimitType[k] == BIT_LIMIT_LOWER)
                                pen = QPen(mLimitColor.lowermargin);
                            pen.setStyle(Qt::DotLine);
                            pen.setWidth(2);
                            painter->setPen(pen);
                            painter->drawLine(StartXAxis,mbottom,StopXAxis,mbottom);
                            pen.setWidth(1);
                            painter->setPen(pen);
                        }
                    }
                    else if(dSlope<0){
                        if(gctrlmana->gLimitAmplitude[k][i-1] + margin < lowLevel){
                            if(gctrlmana->gLimitAmplitude[k][i] + margin <= lowLevel){
                                QPen pen;
                                if (gctrlmana->gLimitType[k] == BIT_LIMIT_UPPER)
                                    pen = QPen(mLimitColor.uppermargin);
                                else if (gctrlmana->gLimitType[k] == BIT_LIMIT_LOWER)
                                    pen = QPen(mLimitColor.lowermargin);
                                pen.setStyle(Qt::DotLine);
                                pen.setWidth(2);
                                painter->setPen(pen);
                                painter->drawLine(StartXAxis,mbottom,StopXAxis,mbottom);
                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                            else if(gctrlmana->gLimitAmplitude[k][i] + margin <= topLevel&&gctrlmana->gLimitAmplitude[k][i] + margin > lowLevel)
                            {
                                qreal tempY = mbottom;
                                qreal tempX = (tempY-constC)/dSlope;
                                painter->drawLine(tempX, tempY, StopXAxis,  StopYAxis);

                                QPen pen;
                                if (gctrlmana->gLimitType[k] == BIT_LIMIT_UPPER)
                                    pen = QPen(mLimitColor.uppermargin);
                                else if (gctrlmana->gLimitType[k] == BIT_LIMIT_LOWER)
                                    pen = QPen(mLimitColor.lowermargin);
                                pen.setStyle(Qt::DotLine);
                                pen.setWidth(2);
                                painter->setPen(pen);
                                painter->drawLine(StartXAxis,tempY,tempX,tempY);
                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                            else if(gctrlmana->gLimitAmplitude[k][i] + margin > topLevel){
                                qreal tempY1 = mbottom;
                                qreal tempX1 = (tempY1-constC)/dSlope;
                                qreal tempY2 = BIT_GRID_START_Y;
                                qreal tempX2 = (tempY2-constC)/dSlope;

                                painter->drawLine(tempX1, tempY1, tempX2,  tempY2);

                                QPen pen;
                                if (gctrlmana->gLimitType[k] == BIT_LIMIT_UPPER)
                                    pen = QPen(mLimitColor.uppermargin);
                                else if (gctrlmana->gLimitType[k] == BIT_LIMIT_LOWER)
                                    pen = QPen(mLimitColor.lowermargin);
                                pen.setStyle(Qt::DotLine);
                                pen.setWidth(2);
                                painter->setPen(pen);

                                painter->drawLine(StartXAxis, tempY1, tempX1,  tempY1);
                                painter->drawLine(tempX2, tempY2, StopXAxis,  tempY2);

                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                        }
                        else if(gctrlmana->gLimitAmplitude[k][i-1] + margin <= topLevel&&gctrlmana->gLimitAmplitude[k][i-1] + margin >= lowLevel){
                            if(gctrlmana->gLimitAmplitude[k][i] + margin >= topLevel){
                                qreal tempY = BIT_GRID_START_Y;
                                qreal tempX = (tempY-constC)/dSlope;

                                painter->drawLine(StartXAxis, StartYAxis, tempX,  tempY);

                                QPen pen;
                                if (gctrlmana->gLimitType[k] == BIT_LIMIT_UPPER)
                                    pen = QPen(mLimitColor.uppermargin);
                                else if (gctrlmana->gLimitType[k] == BIT_LIMIT_LOWER)
                                    pen = QPen(mLimitColor.lowermargin);
                                pen.setStyle(Qt::DotLine);
                                pen.setWidth(2);
                                painter->setPen(pen);

                                painter->drawLine(tempX, tempY, StopXAxis,  tempY);

                                pen.setWidth(1);
                                painter->setPen(pen);
                            }
                        }
                        else if(gctrlmana->gLimitAmplitude[k][i] + margin > topLevel){
                            QPen pen;
                            if (gctrlmana->gLimitType[k] == BIT_LIMIT_UPPER)
                                pen = QPen(mLimitColor.uppermargin);
                            else if (gctrlmana->gLimitType[k] == BIT_LIMIT_LOWER)
                                pen = QPen(mLimitColor.lowermargin);
                            pen.setStyle(Qt::DotLine);
                            pen.setWidth(2);
                            painter->setPen(pen);
                            painter->drawLine(StartXAxis,BIT_GRID_START_Y,StopXAxis,BIT_GRID_START_Y);
                            pen.setWidth(1);
                            painter->setPen(pen);
                        }
                    }
                }
            }
            else painter->drawLine(StartXAxis, StartYAxis, StopXAxis,  StopYAxis);
        }
        QPen pen;
        if (gctrlmana->gLimitType[k] == BIT_LIMIT_UPPER){
            pen = QPen(mLimitColor.uppermargin);
            pen.setStyle(Qt::DotLine);
            if(gctrlmana->gLimitAmplitude[k][0] + margin >= lowLevel && gctrlmana->gLimitAmplitude[k][0] + margin <= topLevel){
                if(gctrlmana->gLimitAmplitude[k][0] > topLevel){
                    StartXAxis = gctrlmana->gLimitpointsXIndex[k][0]*pixedstepX+BIT_GRID_START_X;
                    StartYAxis = BIT_GRID_START_Y;
                    StopXAxis  = gctrlmana->gLimitpointsXIndex[k][0]*pixedstepX+BIT_GRID_START_X;
                    StopYAxis  = gctrlmana->gLimitMaiginpointsY[k][0];

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
                else if(gctrlmana->gLimitAmplitude[k][0] + margin >= lowLevel && gctrlmana->gLimitAmplitude[k][0] + margin <= topLevel) {
                    StartXAxis = gctrlmana->gLimitpointsXIndex[k][0]*pixedstepX+BIT_GRID_START_X;
                    StartYAxis = gctrlmana->gLimitpointsY[k][0];
                    StopXAxis  = gctrlmana->gLimitpointsXIndex[k][0]*pixedstepX+BIT_GRID_START_X;
                    StopYAxis  = gctrlmana->gLimitMaiginpointsY[k][0];

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
            }
            else if(gctrlmana->gLimitAmplitude[k][0] + margin < lowLevel)
            {
                if(gctrlmana->gLimitAmplitude[k][0] >= topLevel)
                {
                    StartXAxis = gctrlmana->gLimitpointsXIndex[k][0]*pixedstepX+BIT_GRID_START_X;
                    StartYAxis = BIT_GRID_START_Y;
                    StopXAxis  = gctrlmana->gLimitpointsXIndex[k][0]*pixedstepX+BIT_GRID_START_X;
                    StopYAxis  = mbottom;

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
                else if(gctrlmana->gLimitAmplitude[k][0] >= lowLevel && gctrlmana->gLimitAmplitude[k][0] < topLevel)
                {
                    StartXAxis = gctrlmana->gLimitpointsXIndex[k][0]*pixedstepX+BIT_GRID_START_X;
                    StartYAxis = mbottom;
                    StopXAxis  = gctrlmana->gLimitpointsXIndex[k][0]*pixedstepX+BIT_GRID_START_X;
                    StopYAxis  = gctrlmana->gLimitpointsY[k][0];

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
            }

            qint32 gTotalDot = gctrlmana->gLimitPointCnt[k];
            if(gctrlmana->gLimitAmplitude[k][gTotalDot-1] + margin >= lowLevel && gctrlmana->gLimitAmplitude[k][gTotalDot-1] + margin <= topLevel){
                if(gctrlmana->gLimitAmplitude[k][gTotalDot-1] > topLevel)
                {
                    StartXAxis = gctrlmana->gLimitpointsXIndex[k][gTotalDot-1]*pixedstepX+BIT_GRID_START_X;
                    StartYAxis = BIT_GRID_START_Y;
                    StopXAxis  = gctrlmana->gLimitpointsXIndex[k][gTotalDot-1]*pixedstepX+BIT_GRID_START_X;
                    StopYAxis  = gctrlmana->gLimitMaiginpointsY[k][gTotalDot-1];

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
                else if(gctrlmana->gLimitAmplitude[k][gTotalDot-1] >= lowLevel && gctrlmana->gLimitAmplitude[k][gTotalDot-1] <= topLevel)
                {
                    StartXAxis = gctrlmana->gLimitpointsXIndex[k][gTotalDot-1]*pixedstepX+BIT_GRID_START_X;
                    StartYAxis = gctrlmana->gLimitpointsY[k][gTotalDot-1];
                    StopXAxis  = gctrlmana->gLimitpointsXIndex[k][gTotalDot-1]*pixedstepX+BIT_GRID_START_X;
                    StopYAxis  = gctrlmana->gLimitMaiginpointsY[k][gTotalDot-1];

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
            }
            else if(gctrlmana->gLimitAmplitude[k][gTotalDot-1] + margin < lowLevel)
            {
                if(gctrlmana->gLimitAmplitude[k][gTotalDot-1] >= topLevel)
                {
                    StartXAxis = gctrlmana->gLimitpointsXIndex[k][gTotalDot-1]*pixedstepX+BIT_GRID_START_X;
                    StartYAxis = BIT_GRID_START_Y;
                    StopXAxis  = gctrlmana->gLimitpointsXIndex[k][gTotalDot-1]*pixedstepX+BIT_GRID_START_X;
                    StopYAxis  = mbottom;

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
                else if(gctrlmana->gLimitAmplitude[k][gTotalDot-1] >= lowLevel && gctrlmana->gLimitAmplitude[k][gTotalDot-1] < topLevel)
                {
                    StartXAxis = gctrlmana->gLimitpointsXIndex[k][gTotalDot-1]*pixedstepX+BIT_GRID_START_X;
                    StartYAxis = mbottom;
                    StopXAxis  = gctrlmana->gLimitpointsXIndex[k][gTotalDot-1]*pixedstepX+BIT_GRID_START_X;
                    StopYAxis  = gctrlmana->gLimitpointsY[k][gTotalDot-1];

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
            }
        }
        else if (gctrlmana->gLimitType[k] == BIT_LIMIT_LOWER)
        {
            pen = QPen(mLimitColor.lowermargin);
            pen.setStyle(Qt::DotLine);
            if(gctrlmana->gLimitAmplitude[k][0] + margin >= lowLevel && gctrlmana->gLimitAmplitude[k][0] + margin <= topLevel)
            {
                if(gctrlmana->gLimitAmplitude[k][0] < lowLevel){
                    StartXAxis = gctrlmana->gLimitpointsXIndex[k][0]*pixedstepX+BIT_GRID_START_X;
                    StartYAxis = mbottom;
                    StopXAxis  = gctrlmana->gLimitpointsXIndex[k][0]*pixedstepX+BIT_GRID_START_X;
                    StopYAxis  = gctrlmana->gLimitMaiginpointsY[k][0];

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
                else if(gctrlmana->gLimitAmplitude[k][0] >= lowLevel && gctrlmana->gLimitAmplitude[k][0] <= topLevel)
                {
                    StartXAxis = gctrlmana->gLimitpointsXIndex[k][0]*pixedstepX+BIT_GRID_START_X;
                    StartYAxis = gctrlmana->gLimitpointsY[k][0];
                    StopXAxis  = gctrlmana->gLimitpointsXIndex[k][0]*pixedstepX+BIT_GRID_START_X;
                    StopYAxis  = gctrlmana->gLimitMaiginpointsY[k][0];

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
            }
            else if(gctrlmana->gLimitAmplitude[k][0] + margin > topLevel)
            {
                if(gctrlmana->gLimitAmplitude[k][0] <= lowLevel){
                    StartXAxis = gctrlmana->gLimitpointsXIndex[k][0]*pixedstepX+BIT_GRID_START_X;
                    StartYAxis = mbottom;
                    StopXAxis  = gctrlmana->gLimitpointsXIndex[k][0]*pixedstepX+BIT_GRID_START_X;
                    StopYAxis  = BIT_GRID_START_Y;

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
                else if(gctrlmana->gLimitAmplitude[k][0] > lowLevel && gctrlmana->gLimitAmplitude[k][0] <= topLevel)
                {
                    StartXAxis = gctrlmana->gLimitpointsXIndex[k][0]*pixedstepX+BIT_GRID_START_X;
                    StartYAxis = gctrlmana->gLimitpointsY[k][0];
                    StopXAxis  = gctrlmana->gLimitpointsXIndex[k][0]*pixedstepX+BIT_GRID_START_X;
                    StopYAxis  = BIT_GRID_START_Y;

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
            }

            qint32 gTotalDot = gctrlmana->gLimitPointCnt[k];
            if(gctrlmana->gLimitAmplitude[k][gTotalDot-1] + margin >= lowLevel && gctrlmana->gLimitAmplitude[k][gTotalDot-1] + margin <= topLevel)
            {
                if(gctrlmana->gLimitAmplitude[k][gTotalDot-1] <= lowLevel){
                    StartXAxis = gctrlmana->gLimitpointsXIndex[k][gTotalDot-1]*pixedstepX+BIT_GRID_START_X;
                    StartYAxis = mbottom;
                    StopXAxis  = gctrlmana->gLimitpointsXIndex[k][gTotalDot-1]*pixedstepX+BIT_GRID_START_X;
                    StopYAxis  = gctrlmana->gLimitMaiginpointsY[k][0];

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
                else if(gctrlmana->gLimitAmplitude[k][gTotalDot-1] > lowLevel && gctrlmana->gLimitAmplitude[k][gTotalDot-1] <= topLevel)
                {
                    StartXAxis = gctrlmana->gLimitpointsXIndex[k][gTotalDot-1]*pixedstepX+BIT_GRID_START_X;
                    StartYAxis = gctrlmana->gLimitpointsY[k][gTotalDot-1];
                    StopXAxis  = gctrlmana->gLimitpointsXIndex[k][gTotalDot-1]*pixedstepX+BIT_GRID_START_X;
                    StopYAxis  = gctrlmana->gLimitMaiginpointsY[k][gTotalDot-1];

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
            }
            else if(gctrlmana->gLimitAmplitude[k][gTotalDot-1] + margin > topLevel)
            {
                if(gctrlmana->gLimitAmplitude[k][gTotalDot-1] < lowLevel)
                {
                    StartXAxis = gctrlmana->gLimitpointsXIndex[k][gTotalDot-1]*pixedstepX+BIT_GRID_START_X;
                    StartYAxis = mbottom;
                    StopXAxis  = gctrlmana->gLimitpointsXIndex[k][gTotalDot-1]*pixedstepX+BIT_GRID_START_X;
                    StopYAxis  = BIT_GRID_START_Y;

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
                else if(gctrlmana->gLimitAmplitude[k][gTotalDot-1] >= lowLevel && gctrlmana->gLimitAmplitude[k][gTotalDot-1] <= topLevel)
                {
                    StartXAxis = gctrlmana->gLimitpointsXIndex[k][gTotalDot-1]*pixedstepX+BIT_GRID_START_X;
                    StartYAxis = gctrlmana->gLimitpointsY[k][gTotalDot-1];
                    StopXAxis  = gctrlmana->gLimitpointsXIndex[k][gTotalDot-1]*pixedstepX+BIT_GRID_START_X;
                    StopYAxis  = BIT_GRID_START_Y;

                    painter->drawLine(StartXAxis,StartYAxis,StopXAxis,StopYAxis);
                }
            }
        }
    }
}

void BitView::renderLimitSiglines(QPainter *painter)
{
    qint32 i = 0;
    qreal position_center = 0.;

    float total_axis = 0.;
    float upper_axis = 0.;
    float lower_axis = 0.;
    float upper_percent = 0.;
    float lower_percent = 0.;
    float upper_pos_axis = 0.;
    float lower_pos_axis = 0.;

    float limitLowerYAxis = 0.;
    float limitUpperYAxis = 0.;
    qreal pixedstepX = (gusedsize.gpicwidth - 2 * LINEREEOR)/(gbitbuffer.gtracenum-1);
    qint32 currentTraceNo = gctrlmana->gtraceIndex;

    for (i = 1; i < gbitbuffer.gtracenum; i++)
    {
        if(gctrlmana->gLimitMargin[0] == BITON || gctrlmana->gLimitMargin[1] == BITON || gctrlmana->gLimitMargin[2] == BITON ||
                gctrlmana->gLimitMargin[3] == BITON || gctrlmana->gLimitMargin[4] == BITON || gctrlmana->gLimitMargin[5] == BITON)
        {
            limitLowerYAxis = gbitbuffer.gLimitLowerMarginDrawPoint[i];
            limitUpperYAxis = gbitbuffer.gLimitUpperMarginDrawPoint[i];
        }
        else
        {
            limitLowerYAxis = gbitbuffer.gLimitLowerDrawPoint[i];
            limitUpperYAxis = gbitbuffer.gLimitUpperDrawPoint[i];
        }
        if ((limitUpperYAxis > limitLowerYAxis) && (limitUpperYAxis != 0. && limitLowerYAxis != 0. ))
        {
            painter->setPen(mTraceColor.Trace);  // QColor/QPen
            painter->drawLine(BIT_GRID_START_X  + ((i  - 1) * pixedstepX), gbitbuffer.drawpointsY[currentTraceNo][i-1], BIT_GRID_START_X + (i * pixedstepX),gbitbuffer.drawpointsY[currentTraceNo][i]);
        }
        else
        {
            if (i == 0)
            {
                // Upper Compare
                if(( gbitbuffer.drawpointsY[currentTraceNo][i] < limitUpperYAxis) && (limitUpperYAxis != 0. ))
                {
                    painter->setPen(mTraceColor.Trace);  // QColor/QPen
                    painter->drawLine(BIT_GRID_START_X + (i * pixedstepX), gbitbuffer.drawpointsY[currentTraceNo][i], BIT_GRID_START_X + (i * pixedstepX),  limitUpperYAxis);
                    // lower Compare
                }
                else if (gbitbuffer.drawpointsY[currentTraceNo][i] > limitLowerYAxis && limitLowerYAxis != 0.)
                {
                    painter->setPen(mTraceColor.Trace);  // QColor/QPen
                    painter->drawLine(BIT_GRID_START_X + (i * pixedstepX), limitLowerYAxis, BIT_GRID_START_X + (i * pixedstepX),  gbitbuffer.drawpointsY[currentTraceNo][i]);
                }
                else
                {
                    if(currentTraceNo == BITTR1)
                        painter->setPen(mTraceColor.Trace1);
                    else if(currentTraceNo == BITTR2)
                        painter->setPen(mTraceColor.Trace2);
                    else if(currentTraceNo == BITTR3)
                        painter->setPen(mTraceColor.Trace3);
                    else if(currentTraceNo == BITTR4)
                        painter->setPen(mTraceColor.Trace4);
                    else if(currentTraceNo == BITTR5)
                        painter->setPen(mTraceColor.Trace5);
                    else if(currentTraceNo == BITTR6)
                        painter->setPen(mTraceColor.Trace6);
                    painter->drawLine(BIT_GRID_START_X + (i * pixedstepX), gbitbuffer.drawpointsY[currentTraceNo][i], BIT_GRID_START_X + (i * pixedstepX),  gbitbuffer.drawpointsY[currentTraceNo][i]);
                }

            }
            else if(i == (gbitbuffer.gtracenum - 1))
            {

                position_center = (((qreal) i) - 0.5) * pixedstepX;
                //Johnson 0903 change
                // Upper Compare
                if ((gbitbuffer.drawpointsY[currentTraceNo][i]  < limitUpperYAxis)  && (limitUpperYAxis != 0.) )
                {
                    if ((gbitbuffer.drawpointsY[currentTraceNo][i - 1] > limitUpperYAxis) && (limitUpperYAxis != 0.))
                    {
                        painter->setPen(mTraceColor.Trace);  // QColor/QPen
                        painter->drawLine(BIT_GRID_START_X + ((i - 1) * pixedstepX), limitLowerYAxis, BIT_GRID_START_X + position_center,  limitLowerYAxis);

                        painter->setPen(mTraceColor.Trace);  // QColor/QPen
                        painter->drawLine(BIT_GRID_START_X + position_center,  limitUpperYAxis, BIT_GRID_START_X + (i * pixedstepX),  gbitbuffer.drawpointsY[currentTraceNo][i]);
                    }
                    else
                    {
                        painter->setPen(mTraceColor.Trace);  // QColor/QPen
                        painter->drawLine(BIT_GRID_START_X + ((i - 1)  * pixedstepX),  gbitbuffer.drawpointsY[currentTraceNo][i - 1], BIT_GRID_START_X + (i * pixedstepX),  gbitbuffer.drawpointsY[currentTraceNo][i]);
                    }
                }
                else
                {
                    if (gbitbuffer.drawpointsY[currentTraceNo][i - 1] < limitUpperYAxis && limitUpperYAxis != 0.)
                    {
                        painter->setPen(mTraceColor.Trace);  // QColor/QPen
                        painter->drawLine(BIT_GRID_START_X + ((i - 1) * pixedstepX),  gbitbuffer.drawpointsY[currentTraceNo][i - 1], BIT_GRID_START_X + position_center,  limitUpperYAxis);

                        if(currentTraceNo == BITTR1)
                            painter->setPen(mTraceColor.Trace1);
                        else if(currentTraceNo == BITTR2)
                            painter->setPen(mTraceColor.Trace2);
                        else if(currentTraceNo == BITTR3)
                            painter->setPen(mTraceColor.Trace3);
                        else if(currentTraceNo == BITTR4)
                            painter->setPen(mTraceColor.Trace4);
                        else if(currentTraceNo == BITTR5)
                            painter->setPen(mTraceColor.Trace5);
                        else if(currentTraceNo == BITTR6)
                            painter->setPen(mTraceColor.Trace6);
                        painter->drawLine(BIT_GRID_START_X + position_center,limitUpperYAxis, BIT_GRID_START_X + (i * pixedstepX),gbitbuffer.drawpointsY[currentTraceNo][i]);
                    }
                    else
                    {
                        if(currentTraceNo == BITTR1)
                            painter->setPen(mTraceColor.Trace1);
                        else if(currentTraceNo == BITTR2)
                            painter->setPen(mTraceColor.Trace2);
                        else if(currentTraceNo == BITTR3)
                            painter->setPen(mTraceColor.Trace3);
                        else if(currentTraceNo == BITTR4)
                            painter->setPen(mTraceColor.Trace4);
                        else if(currentTraceNo == BITTR5)
                            painter->setPen(mTraceColor.Trace5);
                        else if(currentTraceNo == BITTR6)
                            painter->setPen(mTraceColor.Trace6);
                        painter->drawLine(BIT_GRID_START_X + ((i - 1) * pixedstepX), gbitbuffer.drawpointsY[currentTraceNo][i - 1], BIT_GRID_START_X + (i * pixedstepX),  gbitbuffer.drawpointsY[currentTraceNo][i]);
                    }
                }
                if ((gbitbuffer.drawpointsY[currentTraceNo][i]  > limitLowerYAxis) && (limitLowerYAxis != 0.) )
                {
                    if ((gbitbuffer.drawpointsY[currentTraceNo][i - 1] < limitLowerYAxis) && (limitLowerYAxis != 0.))
                    {
                        if(currentTraceNo == BITTR1)
                            painter->setPen(mTraceColor.Trace1);
                        else if(currentTraceNo == BITTR2)
                            painter->setPen(mTraceColor.Trace2);
                        else if(currentTraceNo == BITTR3)
                            painter->setPen(mTraceColor.Trace3);
                        else if(currentTraceNo == BITTR4)
                            painter->setPen(mTraceColor.Trace4);
                        else if(currentTraceNo == BITTR5)
                            painter->setPen(mTraceColor.Trace5);
                        else if(currentTraceNo == BITTR6)
                            painter->setPen(mTraceColor.Trace6);
                        painter->drawLine(BIT_GRID_START_X + ((i - 1) * pixedstepX), limitUpperYAxis, BIT_GRID_START_X + position_center,   limitLowerYAxis);

                        gctrlmana->gLimitTestValue = BIT_LIMIT_FAIL;
                        painter->setPen(mTraceColor.Trace);  // QColor/QPen
                        painter->drawLine(BIT_GRID_START_X + position_center, limitLowerYAxis, BIT_GRID_START_X + (i * pixedstepX),  gbitbuffer.drawpointsY[currentTraceNo][i]);
                    }
                    else
                    {
                        gctrlmana->gLimitTestValue = BIT_LIMIT_FAIL;
                        painter->setPen(mTraceColor.Trace);  // QColor/QPen
                        painter->drawLine(BIT_GRID_START_X +  ((i - 1) * pixedstepX), gbitbuffer.drawpointsY[currentTraceNo][i - 1], BIT_GRID_START_X + (i * pixedstepX) ,  gbitbuffer.drawpointsY[currentTraceNo][i]);
                    }
                }
                else
                {
                    if ((gbitbuffer.drawpointsY[currentTraceNo][i - 1] > limitLowerYAxis) && (limitLowerYAxis != 0.))
                    {
                        gctrlmana->gLimitTestValue = BIT_LIMIT_FAIL;
                        painter->setPen(mTraceColor.Trace);  // QColor/QPen
                        painter->drawLine(BIT_GRID_START_X +  ((i - 1) * pixedstepX), gbitbuffer.drawpointsY[currentTraceNo][i - 1], BIT_GRID_START_X + position_center,  limitLowerYAxis);

                        if(currentTraceNo == BITTR1)
                            painter->setPen(mTraceColor.Trace1);
                        else if(currentTraceNo == BITTR2)
                            painter->setPen(mTraceColor.Trace2);
                        else if(currentTraceNo == BITTR3)
                            painter->setPen(mTraceColor.Trace3);
                        else if(currentTraceNo == BITTR4)
                            painter->setPen(mTraceColor.Trace4);
                        else if(currentTraceNo == BITTR5)
                            painter->setPen(mTraceColor.Trace5);
                        else if(currentTraceNo == BITTR6)
                            painter->setPen(mTraceColor.Trace6);
                        painter->drawLine(BIT_GRID_START_X + position_center, limitLowerYAxis, BIT_GRID_START_X + (i * pixedstepX),  limitUpperYAxis);
                    }
                    else
                    {
                        if(limitUpperYAxis != 0) break;
                        if(currentTraceNo == BITTR1) painter->setPen(mTraceColor.Trace1);
                        else if(currentTraceNo == BITTR2) painter->setPen(mTraceColor.Trace2);
                        else if(currentTraceNo == BITTR3) painter->setPen(mTraceColor.Trace3);
                        else if(currentTraceNo == BITTR4) painter->setPen(mTraceColor.Trace4);
                        else if(currentTraceNo == BITTR5) painter->setPen(mTraceColor.Trace5);
                        else if(currentTraceNo == BITTR6) painter->setPen(mTraceColor.Trace6);
                        painter->drawLine(BIT_GRID_START_X +  ((i - 1) * pixedstepX), gbitbuffer.drawpointsY[currentTraceNo][i - 1], BIT_GRID_START_X + (i * pixedstepX),  gbitbuffer.drawpointsY[currentTraceNo][i]);
                    }
                }
            }
            else
            {
                position_center = (((qreal) i ) - 0.5) * pixedstepX;
                if ((limitUpperYAxis != 0.) && (limitLowerYAxis != 0.))
                {
                    if ((gbitbuffer.drawpointsY[currentTraceNo][i - 1] < limitUpperYAxis) && (gbitbuffer.drawpointsY[currentTraceNo][i] > limitLowerYAxis))
                    {
                        total_axis  = gbitbuffer.drawpointsY[currentTraceNo][i] - gbitbuffer.drawpointsY[currentTraceNo][i - 1];
                        upper_axis =   limitUpperYAxis - gbitbuffer.drawpointsY[currentTraceNo][i - 1];
                        lower_axis =   gbitbuffer.drawpointsY[currentTraceNo][i] - limitLowerYAxis;

                        upper_percent = upper_axis / total_axis;
                        lower_percent = lower_axis / total_axis;


                        upper_pos_axis = (((qreal) i) - upper_percent) * pixedstepX;
                        lower_pos_axis = (((qreal) i) - lower_percent) * pixedstepX;

                        painter->setPen(mTraceColor.Trace);  // QColor/QPen
                        painter->drawLine(BIT_GRID_START_X +  ((i - 1) * pixedstepX), gbitbuffer.drawpointsY[currentTraceNo][i - 1], BIT_GRID_START_X + (qint32) upper_pos_axis,  limitUpperYAxis);

                        if(currentTraceNo == BITTR1) painter->setPen(mTraceColor.Trace1);
                        else if(currentTraceNo == BITTR2) painter->setPen(mTraceColor.Trace2);
                        else if(currentTraceNo == BITTR3) painter->setPen(mTraceColor.Trace3);
                        else if(currentTraceNo == BITTR4) painter->setPen(mTraceColor.Trace4);
                        else if(currentTraceNo == BITTR5) painter->setPen(mTraceColor.Trace5);
                        else if(currentTraceNo == BITTR6) painter->setPen(mTraceColor.Trace6);
                        painter->drawLine(BIT_GRID_START_X +   (qint32) upper_pos_axis, limitUpperYAxis, BIT_GRID_START_X + (qint32) lower_pos_axis,  limitLowerYAxis);

                        painter->setPen(mTraceColor.Trace);  // QColor/QPenglobalUserVariable
                        painter->drawLine(BIT_GRID_START_X +  (qint32) lower_pos_axis, limitLowerYAxis, BIT_GRID_START_X + (i  * pixedstepX),  gbitbuffer.drawpointsY[currentTraceNo][i]);
                    }
                    else if ((gbitbuffer.drawpointsY[currentTraceNo][i - 1] > limitLowerYAxis)  && (gbitbuffer.drawpointsY[currentTraceNo][i] < limitUpperYAxis ))
                    {
                        total_axis  = gbitbuffer.drawpointsY[currentTraceNo][i] - gbitbuffer.drawpointsY[currentTraceNo][i - 1];

                        lower_axis =   gbitbuffer.drawpointsY[currentTraceNo][i - 1] - limitLowerYAxis;
                        upper_axis =   limitUpperYAxis - gbitbuffer.drawpointsY[currentTraceNo][i];

                        upper_percent = upper_axis / total_axis;
                        lower_percent = lower_axis / total_axis;


                        upper_pos_axis = (((qreal) i) - upper_percent) * pixedstepX;
                        lower_pos_axis = (((qreal) i) - lower_percent) * pixedstepX;

                        painter->setPen(mTraceColor.Trace);  // QColor/QPen
                        painter->drawLine(BIT_GRID_START_X +  ((i - 1) * pixedstepX), gbitbuffer.drawpointsY[currentTraceNo][i - 1], BIT_GRID_START_X + (qint32) lower_pos_axis,  limitLowerYAxis);

                        if(currentTraceNo == BITTR1) painter->setPen(mTraceColor.Trace1);
                        else if(currentTraceNo == BITTR2) painter->setPen(mTraceColor.Trace2);
                        else if(currentTraceNo == BITTR3) painter->setPen(mTraceColor.Trace3);
                        else if(currentTraceNo == BITTR4) painter->setPen(mTraceColor.Trace4);
                        else if(currentTraceNo == BITTR5) painter->setPen(mTraceColor.Trace5);
                        else if(currentTraceNo == BITTR6) painter->setPen(mTraceColor.Trace6);
                        painter->drawLine(BIT_GRID_START_X +  (qint32) lower_pos_axis, limitLowerYAxis, BIT_GRID_START_X +  (qint32) upper_pos_axis,  limitUpperYAxis);

                        painter->setPen(mTraceColor.Trace);  // QColor/QPen
                        painter->drawLine(BIT_GRID_START_X +  (qint32) upper_pos_axis, limitUpperYAxis, BIT_GRID_START_X + (i  * pixedstepX),  gbitbuffer.drawpointsY[currentTraceNo][i]);

                    }
                    else if ((gbitbuffer.drawpointsY[currentTraceNo][i - 1] < limitUpperYAxis) && (gbitbuffer.drawpointsY[currentTraceNo][i] < limitUpperYAxis ))
                    {
                        painter->setPen(mTraceColor.Trace);  // QColor/QPen
                        painter->drawLine(BIT_GRID_START_X +  ((i - 1) * pixedstepX), gbitbuffer.drawpointsY[currentTraceNo][i - 1], BIT_GRID_START_X + (i  * pixedstepX),  gbitbuffer.drawpointsY[currentTraceNo][i]);
                    }
                    else if ((gbitbuffer.drawpointsY[currentTraceNo][i - 1] <= limitLowerYAxis) && (gbitbuffer.drawpointsY[currentTraceNo][i] < limitUpperYAxis ))
                    {
                        if(currentTraceNo == BITTR1) painter->setPen(mTraceColor.Trace1);
                        else if(currentTraceNo == BITTR2) painter->setPen(mTraceColor.Trace2);
                        else if(currentTraceNo == BITTR3) painter->setPen(mTraceColor.Trace3);
                        else if(currentTraceNo == BITTR4) painter->setPen(mTraceColor.Trace4);
                        else if(currentTraceNo == BITTR5) painter->setPen(mTraceColor.Trace5);
                        else if(currentTraceNo == BITTR6) painter->setPen(mTraceColor.Trace6);
                        painter->drawLine(BIT_GRID_START_X +   ((i - 1) * pixedstepX), gbitbuffer.drawpointsY[currentTraceNo][i - 1], BIT_GRID_START_X +  (qint32) position_center,  limitUpperYAxis);

                        painter->setPen(mTraceColor.Trace);  // QColor/QPen
                        painter->drawLine(BIT_GRID_START_X + position_center, limitUpperYAxis, BIT_GRID_START_X + (i  * pixedstepX),  gbitbuffer.drawpointsY[currentTraceNo][i]);

                    }
                    else if ((gbitbuffer.drawpointsY[currentTraceNo][i - 1] < limitUpperYAxis) && (gbitbuffer.drawpointsY[currentTraceNo][i] <= limitLowerYAxis ))
                    {
                        painter->setPen(mTraceColor.Trace);  // QColor/QPen
                        painter->drawLine(BIT_GRID_START_X + ((i - 1) * pixedstepX), gbitbuffer.drawpointsY[currentTraceNo][i - 1], BIT_GRID_START_X + position_center,  limitUpperYAxis);

                        if(currentTraceNo == BITTR1) painter->setPen(mTraceColor.Trace1);
                        else if(currentTraceNo == BITTR2) painter->setPen(mTraceColor.Trace2);
                        else if(currentTraceNo == BITTR3) painter->setPen(mTraceColor.Trace3);
                        else if(currentTraceNo == BITTR4) painter->setPen(mTraceColor.Trace4);
                        else if(currentTraceNo == BITTR5) painter->setPen(mTraceColor.Trace5);
                        else if(currentTraceNo == BITTR6) painter->setPen(mTraceColor.Trace6);
                        painter->drawLine(BIT_GRID_START_X + position_center,  limitUpperYAxis, BIT_GRID_START_X + (i  * pixedstepX),  gbitbuffer.drawpointsY[currentTraceNo][i]);
                    }
                    else if ((gbitbuffer.drawpointsY[currentTraceNo][i - 1] > limitLowerYAxis) && (gbitbuffer.drawpointsY[currentTraceNo][i] > limitLowerYAxis ))
                    {
                        painter->setPen(mTraceColor.Trace);  // QColor/QPen
                        painter->drawLine(BIT_GRID_START_X + ((i - 1) * pixedstepX), gbitbuffer.drawpointsY[currentTraceNo][i - 1], BIT_GRID_START_X + (i * pixedstepX),  gbitbuffer.drawpointsY[currentTraceNo][i]);
                    }
                    else if ((gbitbuffer.drawpointsY[currentTraceNo][i - 1] >= limitLowerYAxis) && (gbitbuffer.drawpointsY[currentTraceNo][i] >= limitUpperYAxis ))
                    {
                        painter->setPen(mTraceColor.Trace);  // QColor/QPen
                        painter->drawLine(BIT_GRID_START_X + ((i - 1) * pixedstepX),  gbitbuffer.drawpointsY[currentTraceNo][i - 1], BIT_GRID_START_X + position_center,  limitLowerYAxis);

                        if(currentTraceNo == BITTR1) painter->setPen(mTraceColor.Trace1);
                        else if(currentTraceNo == BITTR2) painter->setPen(mTraceColor.Trace2);
                        else if(currentTraceNo == BITTR3) painter->setPen(mTraceColor.Trace3);
                        else if(currentTraceNo == BITTR4) painter->setPen(mTraceColor.Trace4);
                        else if(currentTraceNo == BITTR5) painter->setPen(mTraceColor.Trace5);
                        else if(currentTraceNo == BITTR6) painter->setPen(mTraceColor.Trace6);
                        painter->drawLine(BIT_GRID_START_X + position_center, limitLowerYAxis, BIT_GRID_START_X + (i  * pixedstepX),  gbitbuffer.drawpointsY[currentTraceNo][i]);
                    }
                    else if ((gbitbuffer.drawpointsY[currentTraceNo][i - 1] > limitUpperYAxis) && (gbitbuffer.drawpointsY[currentTraceNo][i] >= limitLowerYAxis ))
                    {
                        if(currentTraceNo == BITTR1) painter->setPen(mTraceColor.Trace1);
                        else if(currentTraceNo == BITTR2) painter->setPen(mTraceColor.Trace2);
                        else if(currentTraceNo == BITTR3) painter->setPen(mTraceColor.Trace3);
                        else if(currentTraceNo == BITTR4) painter->setPen(mTraceColor.Trace4);
                        else if(currentTraceNo == BITTR5) painter->setPen(mTraceColor.Trace5);
                        else if(currentTraceNo == BITTR6) painter->setPen(mTraceColor.Trace6);
                        painter->drawLine(BIT_GRID_START_X +  ((i - 1) * pixedstepX), gbitbuffer.drawpointsY[currentTraceNo][i - 1], BIT_GRID_START_X + position_center,  limitLowerYAxis);

                        painter->setPen(mTraceColor.Trace);  // QColor/QPen
                        painter->drawLine(BIT_GRID_START_X + position_center, limitLowerYAxis, BIT_GRID_START_X + (i  * pixedstepX),   gbitbuffer.drawpointsY[currentTraceNo][i]);
                    }
                    else
                    {
                        if(currentTraceNo == BITTR1) painter->setPen(mTraceColor.Trace1);
                        else if(currentTraceNo == BITTR2) painter->setPen(mTraceColor.Trace2);
                        else if(currentTraceNo == BITTR3) painter->setPen(mTraceColor.Trace3);
                        else if(currentTraceNo == BITTR4) painter->setPen(mTraceColor.Trace4);
                        else if(currentTraceNo == BITTR5) painter->setPen(mTraceColor.Trace5);
                        else if(currentTraceNo == BITTR6) painter->setPen(mTraceColor.Trace6);
                        painter->drawLine(BIT_GRID_START_X +  ((i - 1) * pixedstepX), gbitbuffer.drawpointsY[currentTraceNo][i - 1], BIT_GRID_START_X + (i * pixedstepX),  gbitbuffer.drawpointsY[currentTraceNo][i]);
                    }
                }
                else if (limitUpperYAxis != 0.)
                {
                    // *******    Upper Limit only Apply
                    position_center = (((qreal) i) - 0.5) * pixedstepX;

                    if ( gbitbuffer.drawpointsY[currentTraceNo][i] < limitUpperYAxis)
                    {
                        if (gbitbuffer.drawpointsY[currentTraceNo][i - 1] > limitUpperYAxis)
                        {
                            if(currentTraceNo == BITTR1) painter->setPen(mTraceColor.Trace1);
                            else if(currentTraceNo == BITTR2) painter->setPen(mTraceColor.Trace2);
                            else if(currentTraceNo == BITTR3) painter->setPen(mTraceColor.Trace3);
                            else if(currentTraceNo == BITTR4) painter->setPen(mTraceColor.Trace4);
                            else if(currentTraceNo == BITTR5) painter->setPen(mTraceColor.Trace5);
                            else if(currentTraceNo == BITTR6) painter->setPen(mTraceColor.Trace6);
                            painter->drawLine(BIT_GRID_START_X +  ((i - 1) * pixedstepX), gbitbuffer.drawpointsY[currentTraceNo][i - 1], BIT_GRID_START_X + position_center,   limitUpperYAxis);

                            painter->setPen(mTraceColor.Trace);  // QColor/QPen
                            painter->drawLine(BIT_GRID_START_X +  position_center, limitUpperYAxis, BIT_GRID_START_X + (i * pixedstepX),   gbitbuffer.drawpointsY[currentTraceNo][i]);
                        }
                        else
                        {
                            painter->setPen(mTraceColor.Trace);  // QColor/QPen
                            painter->drawLine(BIT_GRID_START_X +  ((i - 1) * pixedstepX), gbitbuffer.drawpointsY[currentTraceNo][i - 1], BIT_GRID_START_X + (i * pixedstepX),   gbitbuffer.drawpointsY[currentTraceNo][i]);
                        }

                    }
                    else
                    {

                        if (gbitbuffer.drawpointsY[currentTraceNo][i - 1] < limitUpperYAxis)  {
                            painter->setPen(mTraceColor.Trace);  // QColor/QPen
                            painter->drawLine(BIT_GRID_START_X +  ((i - 1) * pixedstepX), gbitbuffer.drawpointsY[currentTraceNo][i - 1], BIT_GRID_START_X + position_center,  limitUpperYAxis);

                            if(currentTraceNo == BITTR1)
                                painter->setPen(mTraceColor.Trace1);
                            else if(currentTraceNo == BITTR2)
                                painter->setPen(mTraceColor.Trace2);
                            else if(currentTraceNo == BITTR3)
                                painter->setPen(mTraceColor.Trace3);
                            else if(currentTraceNo == BITTR4)
                                painter->setPen(mTraceColor.Trace4);
                            else if(currentTraceNo == BITTR5)
                                painter->setPen(mTraceColor.Trace5);
                            else if(currentTraceNo == BITTR6)
                                painter->setPen(mTraceColor.Trace6);
                            painter->drawLine(BIT_GRID_START_X +  position_center, limitUpperYAxis, BIT_GRID_START_X +  (i  * pixedstepX),  gbitbuffer.drawpointsY[currentTraceNo][i]);
                        }
                        else
                        {
                            if(currentTraceNo == BITTR1)
                                painter->setPen(mTraceColor.Trace1);
                            else if(currentTraceNo == BITTR2)
                                painter->setPen(mTraceColor.Trace2);
                            else if(currentTraceNo == BITTR3)
                                painter->setPen(mTraceColor.Trace3);
                            else if(currentTraceNo == BITTR4)
                                painter->setPen(mTraceColor.Trace4);
                            else if(currentTraceNo == BITTR5)
                                painter->setPen(mTraceColor.Trace5);
                            else if(currentTraceNo == BITTR6)
                                painter->setPen(mTraceColor.Trace6);
                            painter->drawLine(BIT_GRID_START_X +  ((i - 1) * pixedstepX), gbitbuffer.drawpointsY[currentTraceNo][i - 1], BIT_GRID_START_X +  (i  * pixedstepX),   gbitbuffer.drawpointsY[currentTraceNo][i]);
                        }
                    }

                }
                else if (limitLowerYAxis != 0.)
                {
                    // **************  Lower Limit only Apply

                    if ( gbitbuffer.drawpointsY[currentTraceNo][i] > limitLowerYAxis)  {

                        if (gbitbuffer.drawpointsY[currentTraceNo][i - 1] < limitLowerYAxis)  {
                            position_center = (((qreal) i) - 0.5) * pixedstepX;
                            if(currentTraceNo == BITTR1) painter->setPen(mTraceColor.Trace1);
                            else if(currentTraceNo == BITTR2) painter->setPen(mTraceColor.Trace2);
                            else if(currentTraceNo == BITTR3) painter->setPen(mTraceColor.Trace3);
                            else if(currentTraceNo == BITTR4) painter->setPen(mTraceColor.Trace4);
                            else if(currentTraceNo == BITTR5) painter->setPen(mTraceColor.Trace5);
                            else if(currentTraceNo == BITTR6) painter->setPen(mTraceColor.Trace6);
                            painter->drawLine(BIT_GRID_START_X +  ((i - 1) * pixedstepX), gbitbuffer.drawpointsY[currentTraceNo][i - 1], BIT_GRID_START_X + position_center,  limitLowerYAxis);

                            painter->setPen(mTraceColor.Trace);  // QColor/QPen
                            painter->drawLine(BIT_GRID_START_X +  position_center, limitLowerYAxis, BIT_GRID_START_X +  (i  * pixedstepX),   gbitbuffer.drawpointsY[currentTraceNo][i]);

                        }
                        else
                        {
                            painter->setPen(mTraceColor.Trace);  // QColor/QPen
                            painter->drawLine(BIT_GRID_START_X +  ((i - 1) * pixedstepX), gbitbuffer.drawpointsY[currentTraceNo][i - 1], BIT_GRID_START_X +  (i  * pixedstepX),  gbitbuffer.drawpointsY[currentTraceNo][i]);
                        }
                    }
                    else
                    {

                        if (gbitbuffer.drawpointsY[currentTraceNo][i - 1] > limitLowerYAxis)  {
                            position_center = (((qreal) i) -0.5) * pixedstepX;
                            painter->setPen(mTraceColor.Trace);  // QColor/QPen
                            painter->drawLine(BIT_GRID_START_X +  ((i - 1) * pixedstepX), gbitbuffer.drawpointsY[currentTraceNo][i - 1], BIT_GRID_START_X +  position_center,  limitLowerYAxis);

                            if(currentTraceNo == BITTR1) painter->setPen(mTraceColor.Trace1);
                            else if(currentTraceNo == BITTR2) painter->setPen(mTraceColor.Trace2);
                            else if(currentTraceNo == BITTR3) painter->setPen(mTraceColor.Trace3);
                            else if(currentTraceNo == BITTR4) painter->setPen(mTraceColor.Trace4);
                            else if(currentTraceNo == BITTR5) painter->setPen(mTraceColor.Trace5);
                            else if(currentTraceNo == BITTR6) painter->setPen(mTraceColor.Trace6);
                            painter->drawLine(BIT_GRID_START_X +  position_center,  limitLowerYAxis, BIT_GRID_START_X +  (i  * pixedstepX),  gbitbuffer.drawpointsY[currentTraceNo][i]);
                        }
                        else
                        {
                            if(currentTraceNo == BITTR1) painter->setPen(mTraceColor.Trace1);
                            else if(currentTraceNo == BITTR2) painter->setPen(mTraceColor.Trace2);
                            else if(currentTraceNo == BITTR3) painter->setPen(mTraceColor.Trace3);
                            else if(currentTraceNo == BITTR4) painter->setPen(mTraceColor.Trace4);
                            else if(currentTraceNo == BITTR5) painter->setPen(mTraceColor.Trace5);
                            else if(currentTraceNo == BITTR6) painter->setPen(mTraceColor.Trace6);
                            painter->drawLine(BIT_GRID_START_X +   ((i - 1) * pixedstepX), gbitbuffer.drawpointsY[currentTraceNo][i - 1], BIT_GRID_START_X +  (i  * pixedstepX),  gbitbuffer.drawpointsY[currentTraceNo][i]);
                        }
                    }
                }
                else
                {
                    //=== Not Limit Line
                    if(currentTraceNo == BITTR1) painter->setPen(mTraceColor.Trace1);
                    else if(currentTraceNo == BITTR2) painter->setPen(mTraceColor.Trace2);
                    else if(currentTraceNo == BITTR3) painter->setPen(mTraceColor.Trace3);
                    else if(currentTraceNo == BITTR4) painter->setPen(mTraceColor.Trace4);
                    else if(currentTraceNo == BITTR5) painter->setPen(mTraceColor.Trace5);
                    else if(currentTraceNo == BITTR6) painter->setPen(mTraceColor.Trace6);
                    painter->drawLine(BIT_GRID_START_X + ((i - 1) * pixedstepX), gbitbuffer.drawpointsY[currentTraceNo][i - 1], BIT_GRID_START_X +  (i  * pixedstepX),   gbitbuffer.drawpointsY[currentTraceNo][i]);
                }
            }
        }
    }
}

void BitView::renderLimitTestResult(QPainter *painter)
{
    if(gctrlmana->gLimitTest == BITOFF || (gctrlmana->gLimitView[0] == BITOFF && gctrlmana->gLimitView[1] == BITOFF && gctrlmana->gLimitView[2] == BITOFF &&\
                                          gctrlmana->gLimitView[3] == BITOFF && gctrlmana->gLimitView[4] == BITOFF && gctrlmana->gLimitView[5] == BITOFF ))
    {
        return ;
    }
    judgeLimitTestResult();

    if (gctrlmana->gLimitTestValue == BIT_LIMIT_PASS)
    {
        if((gctrlmana->gLimitMargin[0] == BITON || gctrlmana->gLimitMargin[1] == BITON || gctrlmana->gLimitMargin[2] == BITON || gctrlmana->gLimitMargin[3] == BITON || \
            gctrlmana->gLimitMargin[4] == BITON || gctrlmana->gLimitMargin[5] == BITON) && gctrlmana->gLimitMarginTestValue == BIT_LIMIT_FAIL)
        {
            painter->setPen(Qt::red);
            painter->setFont(QFont("Arial", 11));
            painter->drawText(gusedsize.gridX[0], gusedsize.gridY[0], gusedsize.gridYSpace>130 ? gusedsize.gridYSpace : 130,  gusedsize.gridYSpace, Qt::AlignCenter, "TR MARGIN: FAIL");
        }
        else
        {
            painter->setPen(Qt::green);
            painter->setFont(QFont("Arial", 11));
            painter->drawText(gusedsize.gridX[0], gusedsize.gridY[0], gusedsize.gridYSpace>130 ? gusedsize.gridYSpace : 130, gusedsize.gridYSpace, Qt::AlignCenter, "TR: PASS");
        }
    }
    else
    {
        painter->setPen(Qt::red);
        painter->setFont(QFont("Arial", 11));
        painter->drawText(gusedsize.gridX[0], gusedsize.gridY[0], gusedsize.gridYSpace>130 ? gusedsize.gridYSpace : 130,  gusedsize.gridYSpace, Qt::AlignCenter, "TR: FAIL");
    }
    return ;
}

void BitView::limitXAxisCalculatorFunc(qreal Freq, quint32 index,  quint32 uLimitSelect)
{
    //Freq = Freq * MHZ;
    qreal stepfreq = (qreal)(gfreqinfo.gstopfreq - gfreqinfo.gstartfreq)/(gbitbuffer.gtracenum -1);
    // Limit Line Freq Position Find
    for (qint32 k = 0; k < gbitbuffer.gtracenum ; k++) {
        qreal tempFreq =  stepfreq * k;
        qreal vigeoFreq = gfreqinfo.gstartfreq + tempFreq;

        if (vigeoFreq >= Freq)
        {
            gctrlmana->gLimitpointsXIndex[uLimitSelect][index] = k;
            break;
        }
        else if (Freq < gfreqinfo.gstartfreq)
        {
            gctrlmana->gLimitpointsXIndex[uLimitSelect][index] = 0;
            break;
        }
        else if (Freq >= gfreqinfo.gstopfreq)
        {
            gctrlmana->gLimitpointsXIndex[uLimitSelect][index] = gbitbuffer.gtracenum -1 ;
            break;
        }
    }
}

void BitView::limitYAxisCalculatorFunc(qreal level, quint32 index, quint32 uLimitSelect)
{
    qint32 yAxis = 0;
    qreal baseY = gusedsize.grefValue + gusedsize.goffsetValue;
    qreal stepY = (qreal) gusedsize.gdivValue / gusedsize.gridYSpace;
    qint32 deltaY = round((baseY - level)/stepY);
    if(deltaY <= 0)
    {
        gctrlmana->gLimitpointsY[uLimitSelect][index] = BIT_GRID_START_Y;
    }
    else
    {
        gctrlmana->gLimitpointsY[uLimitSelect][index] = round((baseY - level)/stepY) + BIT_GRID_START_Y;
    }

    if(gctrlmana->gLimitType[uLimitSelect] == BIT_LIMIT_UPPER)
    {
        if(deltaY <= 0)
        {
            gctrlmana->gLimitMaiginpointsY[uLimitSelect][index] = BIT_GRID_START_Y;
        }
        else
        {

            gctrlmana->gLimitMaiginpointsY[uLimitSelect][index] =  round((baseY - (level-gctrlmana->gLimitMarginValue[uLimitSelect]))/stepY) + BIT_GRID_START_Y;
        }
    }
    else if(gctrlmana->gLimitType[uLimitSelect] == BIT_LIMIT_LOWER)
    {
        if(deltaY <= 0)
        {
            gctrlmana->gLimitMaiginpointsY[uLimitSelect][index] = BIT_GRID_START_Y;
        }
        else
        {
            gctrlmana->gLimitMaiginpointsY[uLimitSelect][index] = round((baseY - (level+gctrlmana->gLimitMarginValue[uLimitSelect]))/stepY) + BIT_GRID_START_Y;

        }
    }
}

void BitView::getLowerUpperLimitLineInterpolation()
{
    memset(gbitbuffer.gLimitLowerMarginDrawPoint,0,sizeof(qreal)*NOWTRACENUM);
    memset(gbitbuffer.gLimitUpperMarginDrawPoint,0,sizeof(qreal)*NOWTRACENUM);
    memset(gbitbuffer.gLimitLowerDrawPoint,0,sizeof(qreal)*NOWTRACENUM);
    memset(gbitbuffer.gLimitUpperDrawPoint,0,sizeof(qreal)*NOWTRACENUM);

    for(qint32 i = 0;i<BIT_LIMIT_TOTAL_CNT;i++)
    {
        if( gctrlmana->gLimitType[i] == BIT_LIMIT_UPPER && gctrlmana->gLimitView[i] == BITON)
        {
            for(qint32 j = 0;j<gbitbuffer.gtracenum;j++)
            {
                if(gbitbuffer.gLimitUpperDrawPoint[j] < gbitbuffer.gLimitDrawPoint[i][j])
                    gbitbuffer.gLimitUpperDrawPoint[j] = gbitbuffer.gLimitDrawPoint[i][j];

                if(gbitbuffer.gLimitUpperMarginDrawPoint[j] < gbitbuffer.gLimitMarginDrawPoint[i][j])
                    gbitbuffer.gLimitUpperMarginDrawPoint[j] = gbitbuffer.gLimitMarginDrawPoint[i][j];
            }
        }
        else if( gctrlmana->gLimitType[i] == BIT_LIMIT_LOWER && gctrlmana->gLimitView[i] == BITON)
        {
            for(qint32 j = 0;j<gbitbuffer.gtracenum;j++)
            {
                if(gbitbuffer.gLimitLowerDrawPoint[j] < gbitbuffer.gLimitDrawPoint[i][j])
                    gbitbuffer.gLimitLowerDrawPoint[j] = gbitbuffer.gLimitDrawPoint[i][j];

                if(gbitbuffer.gLimitLowerMarginDrawPoint[j] < gbitbuffer.gLimitMarginDrawPoint[i][j])
                    gbitbuffer.gLimitLowerMarginDrawPoint[j] = gbitbuffer.gLimitMarginDrawPoint[i][j];
            }
        }
    }

}

void BitView::limitLineInterpolationCalculatorFunc(quint32 uLimitSelect)
{
    qreal mbottom = TOPDIS + gusedsize.gpicheight - LINEREEOR;
    qint32 i = 0;
    qint32 k = 0;
    qint32 cnt = 0;

    qint32 manualPreviousXPos = 0;
    qint32 manualCurrentXPos  = 0;

    qreal manualPreviousYPos = 0;
    qreal manualCurrentYPos = 0;
    qreal manualPreviousEdgeYPos = 0;
    qreal manualCurrentEdgeYPos = 0;
    qreal manualYStep = 0.;
    qreal manualEdgeYStep = 0.;
    qreal calYAxis = 0.;

    memset(gbitbuffer.gLimitDrawPoint[uLimitSelect],0,sizeof(qreal)*NOWTRACENUM);
    memset(gbitbuffer.gLimitMarginDrawPoint[uLimitSelect],0,sizeof(qreal)*NOWTRACENUM);

    for (i = 1; i < gctrlmana->gLimitPointCnt[uLimitSelect]; i++)
    {
        manualPreviousXPos = gctrlmana->gLimitpointsXIndex[uLimitSelect][i-1];
        manualCurrentXPos  = gctrlmana->gLimitpointsXIndex[uLimitSelect][i];
        manualPreviousYPos = gctrlmana->gLimitpointsY[uLimitSelect][i-1];
        manualCurrentYPos  = gctrlmana->gLimitpointsY[uLimitSelect][i];

        manualPreviousEdgeYPos = gctrlmana->gLimitMaiginpointsY[uLimitSelect][i-1];
        manualCurrentEdgeYPos  = gctrlmana->gLimitMaiginpointsY[uLimitSelect][i];

        manualYStep     = (qreal)(manualCurrentYPos - manualPreviousYPos) / (qreal) (manualCurrentXPos - manualPreviousXPos);
        manualEdgeYStep = (qreal)(manualCurrentEdgeYPos - manualPreviousEdgeYPos) / (qreal) (manualCurrentXPos - manualPreviousXPos);

        cnt = 0;
        for (k = manualPreviousXPos; k < manualCurrentXPos; k++)
        {
            calYAxis = manualPreviousYPos + (manualYStep * (qreal)cnt);

            if(calYAxis<BIT_GRID_START_Y)
                calYAxis = BIT_GRID_START_Y;
            else if(calYAxis>mbottom)
                calYAxis = mbottom;

            if (gbitbuffer.gLimitDrawPoint[uLimitSelect][k] < calYAxis)
                gbitbuffer.gLimitDrawPoint[uLimitSelect][k] = calYAxis;
            else if(gbitbuffer.gLimitDrawPoint[uLimitSelect][k] == calYAxis)
                gbitbuffer.gLimitDrawPoint[uLimitSelect][k] = calYAxis;

            //Limit Margin
            calYAxis = manualPreviousEdgeYPos + (manualEdgeYStep * (qreal)cnt);

            if(calYAxis < BIT_GRID_START_Y)
                calYAxis = BIT_GRID_START_Y;
            else if(calYAxis > mbottom)
                calYAxis = mbottom;

            if ( gbitbuffer.gLimitMarginDrawPoint[uLimitSelect][k] == 0)
                 gbitbuffer.gLimitMarginDrawPoint[uLimitSelect][k] = calYAxis;
            else if ( gbitbuffer.gLimitMarginDrawPoint[uLimitSelect][k] < calYAxis)
                 gbitbuffer.gLimitMarginDrawPoint[uLimitSelect][k] = calYAxis;

            cnt++;
        }
    }
    return;
}

void BitView::judgeLimitTestResult()
{
    qint32 manualStartXPos = 0;
    qint32 manualStopXPos  = 0;

    qint32 manualTotalDot  = 0;

    gctrlmana->gLimitTestValue = BIT_LIMIT_PASS;
    for(qint32 i = 0;i<BIT_LIMIT_TOTAL_CNT;i++)
    {
        if(gctrlmana->gLimitView[i] == BITOFF) continue;

        manualTotalDot = gctrlmana->gLimitPointCnt[i];
        manualStartXPos = gctrlmana->gLimitpointsXIndex[i][0];
        manualStopXPos  = gctrlmana->gLimitpointsXIndex[i][manualTotalDot-1];

        if(gctrlmana->gLimitType[i] == BIT_LIMIT_UPPER)
        {
            for(qint32 j = manualStartXPos;j < manualStopXPos;j++)
            {
                if(gbitbuffer.drawpointsY[gctrlmana->gtraceIndex][j]<gbitbuffer.gLimitDrawPoint[i][j]){
                    gctrlmana->gLimitTestValue = BIT_LIMIT_FAIL;
                    break;
                }
            }
        }
        else if(gctrlmana->gLimitType[i] == BIT_LIMIT_LOWER)
        {
            for(qint32 j = manualStartXPos;j < manualStopXPos;j++)
            {
                if(gbitbuffer.drawpointsY[gctrlmana->gtraceIndex][j]>gbitbuffer.gLimitDrawPoint[i][j])
                {
                    gctrlmana->gLimitTestValue = BIT_LIMIT_FAIL;
                    break;
                }
            }
        }
        if(gctrlmana->gLimitTestValue == BIT_LIMIT_FAIL) return;
    }

    gctrlmana->gLimitMarginTestValue = BIT_LIMIT_PASS;
    for(qint32 i = 0;i<BIT_LIMIT_TOTAL_CNT;i++){
        if(gctrlmana->gLimitMargin[i] == BITOFF) continue;

        manualTotalDot = gctrlmana->gLimitPointCnt[i];
        manualStartXPos = gctrlmana->gLimitpointsXIndex[i][0];
        manualStopXPos  = gctrlmana->gLimitpointsXIndex[i][manualTotalDot-1];

        if(gctrlmana->gLimitType[i] == BIT_LIMIT_UPPER)
        {
            for(qint32 j = manualStartXPos;j < manualStopXPos;j++){
                if(gbitbuffer.drawpointsY[gctrlmana->gtraceIndex][j]<gbitbuffer.gLimitMarginDrawPoint[i][j])
                {
                    gctrlmana->gLimitMarginTestValue = BIT_LIMIT_FAIL;
                    break;
                }
            }
        }
        else if(gctrlmana->gLimitType[i] == BIT_LIMIT_LOWER)
        {
            for(qint32 j = manualStartXPos;j < manualStopXPos;j++)
            {
                if(gbitbuffer.drawpointsY[gctrlmana->gtraceIndex][j]>gbitbuffer.gLimitMarginDrawPoint[i][j]){
                    gctrlmana->gLimitMarginTestValue = BIT_LIMIT_FAIL;
                    break;
                }
            }
        }
        if(gctrlmana->gLimitMarginTestValue == BIT_LIMIT_FAIL) return;
    }
}


//Limit part end
//==========================================================================
//void setLimitPointNum(qint32 pointnum);

//void getLimitPointNum(qint32 pointnum);
void BitView::setLimitAttribute(qint32 attributeType,qint32 attribute,qint32 limitindex)
{
    if(mBitviewType != BIT_SPECTRUM)
        return ;
    if(limitindex < 0)
        limitindex = gctrlmana->gLimitSelect;
    switch (attributeType)
    {
    case BIT_LIMIT_INDEX:
        gctrlmana->gLimitSelect = attribute;
        mlimitTableWidget->initTableWidgetValue();
        mlimitTableWidget->setCurrentCell(0,0);
        break;
    case BIT_LIMIT_VIEW:
        gctrlmana->gLimitView[limitindex] = attribute;
        gctrlmana->gLimitVisiable = BITOFF;
        for(qint32 i=0;i<BIT_LIMIT_TOTAL_CNT;i++)
        {
            if(gctrlmana->gLimitView[i] == BITON)
            {
                gctrlmana->gLimitVisiable = BITON;
                break ;
            }
        }
        break;
    case BIT_LIMIT_TEST:
        gctrlmana->gLimitTest = attribute;
        break;
    case BIT_LIMIT_MARGIN:
        gctrlmana->gLimitMargin[limitindex] = attribute;
        break;
    case BIT_LIMIT_TYPE:
        if(attribute < BIT_LIMIT_UPPER)
            attribute = BIT_LIMIT_UPPER;
        gctrlmana->gLimitType[limitindex] = attribute;
        break;
    case BIT_LIMIT_POINT_NUM:
        gctrlmana->gLimitPointCnt[limitindex] = attribute;
        break;
    }
    return ;
}

qint32 BitView::getLimitAttribute(qint32 attributeType,qint32 limitindex)
{
    qint32 attribute = 0;
    if(limitindex < 0)
        limitindex = gctrlmana->gLimitSelect;
    switch (attributeType)
    {
    case BIT_LIMIT_INDEX:
        attribute = gctrlmana->gLimitSelect;
        break;
    case BIT_LIMIT_VIEW:
        attribute = gctrlmana->gLimitView[limitindex];
        break;
    case BIT_LIMIT_TEST:
        attribute = gctrlmana->gLimitTest;
        break;
    case BIT_LIMIT_MARGIN:
        attribute = gctrlmana->gLimitMargin[limitindex];
        break;

    case BIT_LIMIT_TYPE:
        attribute = gctrlmana->gLimitType[limitindex];

        break;
    case BIT_LIMIT_POINT_NUM:
        attribute = gctrlmana->gLimitPointCnt[limitindex];
        break;
    }
    return attribute;
}

void BitView::setLimitAttributeEX(qint32 attributeType, qreal value, qint32 limitindex)
{
    if(mBitviewType != BIT_SPECTRUM)
        return ;
    if(limitindex < 0)
        limitindex = gctrlmana->gLimitSelect;

    switch (attributeType)
    {
    case BIT_LIMIT_MARGIN_VALUE:
        gctrlmana->gLimitMarginValue[limitindex] = value;
        break;
    }
    return;
}

qreal BitView::getLimitAttributeEX(qint32 attributeType, qint32 limitindex)
{
    qreal value = 0.;
    if(limitindex < 0)
        limitindex = gctrlmana->gLimitSelect;
    switch (attributeType)
    {
    case BIT_LIMIT_MARGIN_VALUE:
        value = gctrlmana->gLimitMarginValue[limitindex] ;
        break;
    }
    return value;
}

qint32 BitView::setLimitPointData(qreal *pbuff, qint32 datanum, qint32 datatype, qint32 limitindex)
{
    qint32 num = gctrlmana->gLimitPointCnt[limitindex];
    if(limitindex < 0)
    {
        limitindex = gctrlmana->gLimitSelect;
    }
    num = (num > datanum) ? datanum : num;

    switch (datatype) {
    case BIT_LIMIT_FREQ:
        memcpy(gctrlmana->gLimitFreq[limitindex],pbuff,sizeof(qreal)*num);

//        for(qint32 i =0;i<num;i++)
//        {
//            memcpy(gctrlmana->gLimitFreq[limitindex],pbuff,sizeof(qreal)*num);
//        }
        break;
    case BIT_LIMIT_AMPT:
        for(qint32 i =0;i<num;i++)
        {
            gctrlmana->gLimitAmplitude[limitindex][i] = pbuff[i] /*+ gusedsize.goffsetValue*/;
//            memcpy(gctrlmana->gLimitAmplitude[limitindex],pbuff,sizeof(qreal)*num);
        }
        break;
    }
    mlimitTableWidget->resetAllParam();

    mlimitTableWidget->sortAllItems();
    mlimitTableWidget->judgeTableContent(mlimitTableWidget,gfreqinfo.gstartfreq,gfreqinfo.gstopfreq);
//    mlimitTableWidget->getTableWidgetValue();

//    mlimitTableWidget->judgeTableContent();
    mlimitTableWidget->initTableWidgetValue();
    return num;
}

void BitView::setLimitCurPointData(qreal pData,qint32 dataIndex, qint32 datatype, qint32 limitindex)
{
    bool isneedSet = true;
    switch (datatype) {
    case BIT_LIMIT_FREQ:
        for(qint32 i = 0; i< gctrlmana->gLimitPointCnt[limitindex]; i++)
        {
            if((pData - gctrlmana->gLimitFreq[limitindex][i]) >= -0.0001 && (pData - gctrlmana->gLimitFreq[limitindex][i]) <= 0.0001)
            {
                isneedSet = false;
            }
        }
        if(isneedSet)
            gctrlmana->gLimitFreq[limitindex][dataIndex] = pData;
        break;
    case BIT_LIMIT_AMPT:
        gctrlmana->gLimitAmplitude[limitindex][dataIndex] = pData;
        break;
    }
    mlimitTableWidget->resetAllParam();
    if(!isneedSet)
        mlimitTableWidget->removeRow(0);
    mlimitTableWidget->sortAllItems();
    mlimitTableWidget->judgeTableContent(mlimitTableWidget,gfreqinfo.gstartfreq,gfreqinfo.gstopfreq);
    mlimitTableWidget->initTableWidgetValue();
    mlimitTableWidget->getTableWidgetValue();

//    mlimitTableWidget->judgeTableContent();

    return;
}

qint32 BitView::getLimitPointData(qreal *pbuff, qint32 datanum, qint32 datatype, qint32 limitindex)
{
    qint32 num = gctrlmana->gLimitPointCnt[limitindex];
    if(limitindex < 0)
    {
        limitindex = gctrlmana->gLimitSelect;
    }
    num = (num > datanum) ? datanum : num;

    switch (datatype) {
    case BIT_LIMIT_FREQ:
        for(qint32 i =0;i<num;i++)
        {
            memcpy(pbuff,gctrlmana->gLimitFreq[limitindex],sizeof(qreal)*num);
        }
        break;
    case BIT_LIMIT_AMPT:
        for(qint32 i =0;i<num;i++)
        {
            memcpy(pbuff,gctrlmana->gLimitAmplitude[limitindex],sizeof(qreal)*num);
        }
        break;
    }
    return num;
}
qreal BitView::getLimitCurPointData(qint32 dataIndex, qint32 datatype, qint32 limitindex)
{
    qreal data = 0.0;
    switch (datatype) {
    case BIT_LIMIT_FREQ:
        data = gctrlmana->gLimitFreq[limitindex][dataIndex];
        break;
    case BIT_LIMIT_AMPT:
        data = gctrlmana->gLimitAmplitude[limitindex][dataIndex];
    }
    return data;
}
void BitView::setTableEdit(qint32 operationType, qint32 visible,qint32 index)
{
    QString strValue;
    qreal currFrqValue;
    qreal startfreq = gfreqinfo.gstartfreq/1000000 /*+0.05*/;
    startfreq = round(startfreq * 10)/10;
    if(mBitviewType != BIT_SPECTRUM)
        return ;
    qint32 row = 0;
    switch (operationType)
    {
    case BIT_LIMIT_EDIT_VISIABLE:
        if(visible == BIT_LIMIT_TABLE_EDIT_HIDE)
        {
            mlimitTableWidget->hide();
            mlimitTableWidget->getTableWidgetValue();
        }
        else
        {
//            mlimitTableWidget->show();
            mlimitTableWidget->setFocus(Qt::TabFocusReason);
        }
        break;
    case BIT_LIMIT_INSERT_ROW:

        if(mlimitTableWidget->isHidden())
        {
//            mlimitTableWidget->show();
        }
//        mlimitTableWidget->judgeTableContent(mlimitTableWidget,gfreqinfo.gstartfreq,gfreqinfo.gstopfreq);
        row = mlimitTableWidget->rowCount();
        if(row < BIT_LIMIT_TOTALDOT)
        {
            if(row > 0)
            {
                strValue = mlimitTableWidget->item(0,0)->text();
                currFrqValue = strValue.toDouble();
                currFrqValue = round(currFrqValue * 100)/100;
                if(currFrqValue <= 0.0001 && currFrqValue >= -0.0001)
                {
                    return;
                }
            }
            if((currFrqValue - startfreq) <= 0.02 && (currFrqValue - startfreq) >= -0.02)
            {
                mlimitTableWidget->insertRow(0);
        //        ui->tableWidget->setItem(0,0,new QTableWidgetItem(QString("%1").arg(0)));
                mlimitTableWidget->setItem(0,0,new QTableWidgetItem(QString("%1").arg(0.00)));
                mlimitTableWidget->setItem(0,1,new QTableWidgetItem(QString("-10.00")));
    //            initTable();
                mlimitTableWidget->resetAllParam();
            }
            else
            {
                mlimitTableWidget->insertRow(0);
                mlimitTableWidget->setItem(0,0,new QTableWidgetItem(QString("%1").arg(gfreqinfo.gstartfreq/1000000)));
                mlimitTableWidget->setItem(0,1,new QTableWidgetItem(QString("-10.00")));
    //            mlimitTableWidget->sortAllItems();//ui->tableWidget->sortItems(0);
                mlimitTableWidget->resetAllParam();

        //        mlimitTableWidget->sortAllItems();
                mlimitTableWidget->judgeTableContent(mlimitTableWidget,gfreqinfo.gstartfreq,gfreqinfo.gstopfreq);

            }
            mlimitTableWidget->setFocus(Qt::TabFocusReason);
            mlimitTableWidget->setCurrentCell(0,0);

//            gctrlmana->gLimitPointCnt[gctrlmana->gLimitSelect]++;
        }
        mlimitTableWidget->getTableWidgetValue();
        break;
    case BIT_LIMIT_DELETE_ROW:
        if(mlimitTableWidget->isHidden())
        {
//            mlimitTableWidget->show();
        }
        if(index == BITDEFAULT || index > mlimitTableWidget->rowCount())
        {
            mlimitTableWidget->removeRow(mlimitTableWidget->currentRow());
        }else
        {
            mlimitTableWidget->removeRow(index);
        }
        mlimitTableWidget->getTableWidgetValue();
        break;
    case BIT_LIMIT_DELETE_LIMIT:
//        if(mlimitTableWidget->isHidden())
//        {
//            mlimitTableWidget->show();
//        }
        if(index == BITDEFAULT || index < 0 || index >=BIT_LIMIT_TOTAL_CNT)
        {
            for(qint32 i = mlimitTableWidget->rowCount()-1;i>=0;i--)
            {
                mlimitTableWidget->removeRow(i);
            }
            gctrlmana->gLimitPointCnt[gctrlmana->gLimitSelect] = 0;
        }else
        {
            gctrlmana->gLimitPointCnt[index] = 0;
        }

        break;
    case BIT_LIMIT_DELETE_ALL_LIMIT:
//        globalUserVariable->caculateLimitTotalLine();

//        if (guiDrawSet.limitLineOnCount != 0) {
//            message_dialog messageDialog(this, PRESET_LIMIT);

//            messageDialog.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
//            messageDialog.setGeometry(MESSAGEDIALOG_STARTX, MESSAGEDIALOG_STARTY, MESSAGEDIALOG_WIDTH, MESSAGEDIALOG_HEIGHT);  // 윈도우 위치 및 폭, 높이 지정
//            //    messageDialog.setGeometry(266, 298, 450, 190);  // 윈도우 위치 및 폭, 높이 지정 (실제 SA)
//            messageDialog.exec();

//            //Johnson 0910 Add
//            for(qint32 i = mlimitTableWidget->rowCount()-1;i>=0;i--){
//                mlimitTableWidget->removeRow(i);
//            }

//          } else {
//            infoMessage = QString("There is no set Limit segment.");
//          }
        mlimitTableWidget->getTableWidgetValue();
        break;
    }
}

void BitView::setSystemAttribute(qint32 attributeType, qint32 attribute)
{
    switch (attributeType) {
    case RUNNINGSTATE:
        gsystemstate.runningState = attribute;
        mIsDensityArrayReset = attribute;
        break;
    case WINDOWTYPE:
        gsystemstate.windowtype = attribute;
        calculationPainterArea();
        break;
    case LANGUAGE:
        gsystemstate.language = attribute;
        break;
    case DISPLAYMODE:
        gsystemstate.displaymode = attribute;
        setdisplaymode(attribute);
        //*when freq change, must refresh fall rect
        refreshSepectrogramRect();
        break;

    default:
        break;
    }
    return ;
}
void BitView::setWindowRect(qint32 width, qint32 height)
{
    mWindowWidth = width;
    mWindowHeight = height;
}

qint32 BitView::getSystemAttribute(qint32 attributeType)
{
    qint32 attribute = 0;
    switch (attributeType)
    {
    case RUNNINGSTATE:
        attribute = gsystemstate.runningState;
        break;
    case WINDOWTYPE:
        attribute = gsystemstate.windowtype;
        calculationPainterArea();
        break;
    case LANGUAGE:
        attribute = gsystemstate.language;
        break;
    case DISPLAYMODE:
        attribute = gsystemstate.displaymode;
        break;

    default:
        break;
    }
    return attribute;
}

//Tony 1101 Calculate painter element.
void BitView::calculationPainterArea()
{
    qint32 dtemp = 0.0;
    dtemp = width() - LEFTDIS - RIGHTDIS;
    dtemp = dtemp < 0 ? 1 : dtemp;
    gusedsize.gpicwidth = dtemp;


    dtemp = height() - TOPDIS - (BOTTOMDIS + gsystemstate.windowtype * markerTabelVisiable * BIT_MARKER_TABLE_HEIGHT);
    dtemp = dtemp < 0 ? 1 : dtemp;
    gusedsize.gpicheight = dtemp;

    CenterPartRect ={BIT_GRID_START_X,BIT_GRID_START_Y,this->width()-LEFTDIS-RIGHTDIS-LINEREEOR,this->height()-TOPDIS-(BOTTOMDIS + gsystemstate.windowtype * markerTabelVisiable * BIT_MARKER_TABLE_HEIGHT)-LINEREEOR};

    qint32 i = 0;
    qreal dDetaLevel = 0.1 * CenterPartRect.width();
    qreal dDetaVertical = 0.1 * CenterPartRect.height();
    gusedsize.gridXSpace = dDetaLevel;
    gusedsize.gridYSpace = dDetaVertical;
    for(i = 0;i < GRIDNUM;i++)
    {
        gusedsize.gridX[i] = BIT_GRID_START_X + dDetaLevel * i;
        gusedsize.gridY[i] = BIT_GRID_START_Y + dDetaVertical * i;
    }

    mlimitTableWidget->setGeometry(BIT_GRID_START_X,BIT_GRID_START_Y-HALFLINEREEOR,BIT_TABLEWIDGET_HEADER_MIN,gusedsize.gpicheight - HALFLINEREEOR);
    mlimitTableWidget->setColumnWidth(0,(BIT_TABLEWIDGET_HEADER_MIN)/2);
    return ;
    qint32 width = (gusedsize.gpicwidth- 2 * LINEREEOR)/2;
    if(width < BIT_TABLEWIDGET_HEADER_MIN)
    {
        if(gusedsize.gpicwidth- 2 * LINEREEOR > BIT_TABLEWIDGET_HEADER_MIN)
        {
            width = BIT_TABLEWIDGET_HEADER_MIN ;
        }
        else
        {
            width = 4 * gusedsize.gridXSpace;
        }
    }
    mlimitTableWidget->setGeometry(BIT_GRID_START_X,BIT_GRID_START_Y,width,gusedsize.gpicheight - LINEREEOR);
    mlimitTableWidget->setColumnWidth(0,(width-BIT_TABLEWIDGET_FIRST_VHEADER_WIDTH)/2);
    return ;
}

//Tony 1102
void BitView::renderMarkerTableBoaderLines(QPainter *painter)
{
    QPen mPen(mMarkerColor.markerBoard);
    mPen.setWidth(HALFLINEREEOR);
    painter->setPen(mPen);
    QPainterPath painterPath;
    painterPath.moveTo(2* LINEREEOR,2 * LINEREEOR);
    painterPath.lineTo(this->width() - 2* LINEREEOR,2 * LINEREEOR);
    painterPath.lineTo(this->width()- 2* LINEREEOR,this->height() -BIT_MARKER_TABLE_HEIGHT- 2* LINEREEOR);
    painterPath.lineTo(2* LINEREEOR,this->height() -BIT_MARKER_TABLE_HEIGHT- 2* LINEREEOR);
    painterPath.lineTo(2* LINEREEOR,2 * LINEREEOR);
    painter->drawPath(painterPath);

    mPen.setColor(mMarkerColor.tableBoard);
    mPen.setWidth(LINEREEOR);
    painter->setPen(mPen);
    QPainterPath painterPath1;
    painterPath1.moveTo(2* LINEREEOR,this->height()-BIT_MARKER_TABLE_HEIGHT+ HALFLINEREEOR);
    painterPath1.lineTo(this->width() - 2* LINEREEOR,this->height()-BIT_MARKER_TABLE_HEIGHT+ HALFLINEREEOR);
    painterPath1.lineTo(this->width()- 2* LINEREEOR,this->height() - 2 * LINEREEOR);
    painterPath1.lineTo(2* LINEREEOR,this->height() - 2 * LINEREEOR);
    painterPath1.lineTo(2* LINEREEOR,this->height()-BIT_MARKER_TABLE_HEIGHT+ HALFLINEREEOR);
    painter->drawPath(painterPath1);
    return;
}

/**
 * @brief BitView::setdisplaymode
 * @param displaymode 设备模式  BIT_DEFAULTMODE--默认模式
 *                            BIT_OUTDOORMODE--户外模式  BIT_NIGHTMODE--室内模式
 * @note 设置界面显示模式  主要是设置界面颜色
 */
void BitView::setdisplaymode(qint32 displaymode)
{
    mTraceColor = traceColor[displaymode];
    mPenColor   = penColor[displaymode];
    mMarkerColor = markerColor[displaymode];
    mLimitColor = limitColor[displaymode];
    mBoardColor = boardColor[displaymode];

    if(gplugindex == gmsgsourceindex && gsystemstate.windowtype == BIT_MULTIWINDOW)
    {
        gboarderpen.setColor(mBoardColor.curBoardLine);
    }else
    {
        gboarderpen.setColor(mPenColor.background);
    }
    switch (displaymode)
    {
    case BIT_DEFAULTMODE:
        mlimitTableWidget->setStyleSheet(
              "border-color: rgb(255, 0, 0);"
              "selection-background-color: rgb(200, 200, 50);"
              "color: rgb(255, 255, 255);"
              "background-color: rgb(100,100,100);");
        produceColorBar(BIT_DEFAULTMODE);
        break;
    case BIT_OUTDOORMODE:
        mlimitTableWidget->setStyleSheet(
              "border-color: rgb(255, 0, 0);"
              "selection-background-color: rgb(200, 100, 50);"
              "color: rgb(255, 255, 255);background-color: rgb(200,100,100);");
        produceColorBar(BIT_OUTDOORMODE);
        break;
    case BIT_NIGHTMODE:
        mlimitTableWidget->setStyleSheet(
              "border-color: rgb(255, 0, 0);"
              "selection-background-color: rgb(100, 200, 50);"
              "color: rgb(255, 255, 255);background-color: rgb(100,200,100);");
        produceColorBar(BIT_NIGHTMODE);
        break;
    default:
        mlimitTableWidget->setStyleSheet(
              "border-color: rgb(255, 0, 0);"
              "selection-background-color: rgb(200, 200, 50);"
              "color: rgb(255, 255, 255);background-color: rgb(100,100,100);");
        produceColorBar(BIT_DEFAULTMODE);
        break;
    }

    return ;
}
//DPX part and need to tune with FPGA.
void BitView::densityRefslot()
{
    getSync();
    gsigrendermap.fill(Qt::transparent);
    QPainter painter(&gsigrendermap);
    painter.initFrom(this);
//    renderGridLines(&painter);
    renderDensityPart(&painter);
    //base grid line
#ifdef BITVIEW_F239
    renderDoubleClickPixMap();
#endif
    this->repaint();
    releaseSync();
    return;
}
//bool isFirst = false;
//qint32 coount = 0;
void BitView::showDensity(qreal *pData, quint32 *pBuff, quint32 datanum, qint32 width, qint32 height)
{
    if(mFileLoadFlag)
    {
        return;
    }
    getSync();
    memcpy(gctrlmana->uFmtRGB,pBuff,DPX_WIDTH_SIZE * DPX_HEIGHT_SIZE * sizeof(quint32));
#if 0
    for(qint32 i = 0; i < DPX_WIDTH_SIZE * DPX_HEIGHT_SIZE; i++)
    {
        gctrlmana->uFmtRGB[4 * i + 3] = 0xff;
        if(i >= DPX_WIDTH_SIZE * 50)
        {
            gctrlmana->uFmtRGB[4 * i] = /*(pBuff[i]) &*/ 0xff;
            gctrlmana->uFmtRGB[4 * i + 1] = /*(pBuff[i] >> 8) &*/ 0x0;
            gctrlmana->uFmtRGB[4 * i + 2] = /*(pBuff[i] >> 16) &*/ 0x0;
//            gctrlmana->uFmtRGB[4 * i + 3] = 0xff;
        }
#if 0
        if((i % DPX_WIDTH_SIZE) == 0)
        {
            rdNum = rand();
            rdNum1 = rand();
        }
        if(i >= (DPX_WIDTH_SIZE * (DPX_HEIGHT_SIZE -1 )) /*&& i < (DPX_WIDTH_SIZE * 1)*/)
        {
            gctrlmana->uFmtRGB[4 * i] = 0xff;
            gctrlmana->uFmtRGB[4 * i + 1] = 0;
            gctrlmana->uFmtRGB[4 * i + 2] = 0xff;
            gctrlmana->uFmtRGB[4 * i + 3] = 0xff;
        }
        else
        {
            gctrlmana->uFmtRGB[4 * i] = 0xff;
            gctrlmana->uFmtRGB[4 * i + 1] = (i /** rdNum * rdNum*/) % 0xff;
            gctrlmana->uFmtRGB[4 * i + 2] = (i /** rdNum * rdNum1*/) % 0xff;
            gctrlmana->uFmtRGB[4 * i + 3] = 0xff;
        }
#endif
    }
#if 0
    if(!isFirst)
        coount ++;
//    memcpy(gctrlmana->uFmtRGB,pBuff,DPX_WIDTH_SIZE * DPX_HEIGHT_SIZE * sizeof(quint32));
    QString fileName = "dpx.txt";
    QFile file(fileName);
    if(coount < 20)
    {

    }
    else
    {
        if (file.open(QIODevice::WriteOnly))
        {
            coount = 19;
            isFirst = true;
            QTextStream stream(&file);
            for (int i = 0;i<DPX_WIDTH_SIZE * DPX_HEIGHT_SIZE;i++)
            {
//                stream << pBuff[i] <<"\r\n";
                stream << gctrlmana->uFmtRGB[4 * i] << ","
                       << gctrlmana->uFmtRGB[4 * i + 1] << ","
                       << gctrlmana->uFmtRGB[4 * i + 2] << ","
                       << gctrlmana->uFmtRGB[4 * i + 3] << ","
                       <<"\r\n";
            }
            file.close();
        }
    }
#endif
#endif
    imageFromData = QImage(gctrlmana->uFmtRGB,DPX_WIDTH_SIZE,DPX_HEIGHT_SIZE,QImage::Format_RGB32);
    datanum = datanum > SUPPORTTRACEPOINT ? SUPPORTTRACENUM : datanum;
    datanum = datanum < SUPPORTTRACEMINPOINT ? SUPPORTTRACEMINPOINT : datanum;
    if(gbitbuffer.gtracenum != datanum)
    {
        quint32 i = 0;
        qreal mdeta = 0.1 * 10 * (gusedsize.gpicwidth - 2 * LINEREEOR) / (datanum - 1);
        for(i = 0;i < datanum;i++)
        {
            gbitbuffer.drawpointsX[i] = BIT_GRID_START_X + i * mdeta;
        }
        gbitbuffer.gtracenum = datanum;

    }
#ifdef BITVIEW_TIME_MARKER
    if(!isSpectrogramCursorEnable())
    {
        memcpy(gbitbuffer.trace_ori,pData,sizeof(qreal) * datanum);
    }
#else
    memcpy(gbitbuffer.trace_ori,pData,sizeof(qreal) * datanum);
#endif
    releaseSync();
//    //async run
    emit emitrefleshDensity();
    return ;
}
void BitView::renderDensityPart(QPainter* pPainter)
{
    if(!checkOriData(gbitbuffer.trace_ori,gbitbuffer.gtracenum))
    {
        return;
    }
//    imageFromData =imageFromData.scaled(CenterPartRect.size(),Qt::IgnoreAspectRatio,Qt::FastTransformation);;
    imageFromData =imageFromData.scaled(CenterPartRect.width() - 1, CenterPartRect.height() - 1,Qt::IgnoreAspectRatio,Qt::FastTransformation);
//    QImage image = imageFromData.createMaskFromColor(0xff000000,Qt::MaskOutColor);
//    imageFromData.setAlphaChannel(image);
//    imageFromData = AdjustSaturation(imageFromData,-100);
    //when app first run, there may be no data transfer, so here need check data buf.
    //draw DPX white trace line
//    renderGridLines(pPainter);
    pPainter->drawImage(CenterPartRect.left(),CenterPartRect.top(),imageFromData);
#ifdef BITVIEW_TIME_MARKER
    mDensityArrayTotalNum++;
    if(isSpectrogramCursorEnable())
    {
        resetDensityLineData();
        renderDensityLines(pPainter);
        oriDataDeals(gbitbuffer.trace_ori,gbitbuffer.gtracenum);
    }
    else
    {
        oriDataDeals(gbitbuffer.trace_ori,gbitbuffer.gtracenum);
        QPen pOldPen = pPainter->pen();
        pPainter->setPen(QColor(255,255,255,255));
        for(qint32 k = 1;k < gbitbuffer.gtracenum;k++)
        {
            pPainter->drawLine(QPointF(gbitbuffer.drawpointsX[k-1],gbitbuffer.drawpointsY[gctrlmana->gtraceIndex][k-1]),QPointF(gbitbuffer.drawpointsX[k],gbitbuffer.drawpointsY[gctrlmana->gtraceIndex][k]));
        }
        pPainter->setPen(pOldPen);
    }
    if(BIT_SINGLE != gsystemstate.runningState || mIsDensityArrayReset)
    {
        mDensityArrayStartPos = mDensityArrayStartPos + 1;
        if(mDensityArrayTotalNum >= SPECTROGRAM_CACHE_DATA)
        {
            mDensityArrayTotalNum = SPECTROGRAM_CACHE_DATA;
        }
        if(mIsDensityArrayReset)
        {
            mIsDensityArrayReset = false;
        }
    }
#else
    oriDataDeals(gbitbuffer.trace_ori,gbitbuffer.gtracenum);
    QPen pOldPen = pPainter->pen();
    pPainter->setPen(QColor(255,255,255,255));
    for(qint32 k = 1;k < gbitbuffer.gtracenum;k++)
    {
        pPainter->drawLine(QPointF(gbitbuffer.drawpointsX[k-1],gbitbuffer.drawpointsY[gctrlmana->gtraceIndex][k-1]),QPointF(gbitbuffer.drawpointsX[k],gbitbuffer.drawpointsY[gctrlmana->gtraceIndex][k]));
    }
    pPainter->setPen(pOldPen);
#endif
    renderMarkerPart(pPainter);
    return;
}
#if 1
void BitView::produceDensityColorBar()
{
    quint32 uColorValue = 0xff000000;
    qint32 uRValue     = 0;
    qint32 uGValue     = 0;
    qint32 uBValue     = 0xff;
    qint32 uColorLevel = SPECTROGRAM_COLBAR_NUM;
    qreal dcurveValue = mCurveValue;
    if(uColorLevel>BIT_COLORLEVEL)
        uColorLevel = BIT_COLORLEVEL;
    else if(uColorLevel<BIT_COLORLEVEL_MIN)
        uColorLevel = BIT_COLORLEVEL_MIN;

    if(dcurveValue<BIT_CURVE_MIN)
        dcurveValue = BIT_CURVE_MIN;
    else if(dcurveValue>BIT_CURVE_MAX)
        dcurveValue = BIT_CURVE_MAX;

//    qreal mcolordiv = (qreal) height/uColorLevel;

    qint32 value_Average = qRound((qreal)SPECTROGRAM_COLBAR_NUM*4/uColorLevel);
    qint32 value_NotAverage = qRound(SPECTROGRAM_COLBAR_NUM*4/uColorLevel*dcurveValue);
    qint32 value_NotAverage1 =qRound((qreal)SPECTROGRAM_COLBAR_NUM*3/(uColorLevel-qRound((qreal)SPECTROGRAM_COLBAR_NUM/value_NotAverage)));

    for(qint32 i = 0;i < uColorLevel;i++){
        if(0xff == uBValue && 0xff>uGValue && 0 == uRValue)
        {
            if(1.0 == dcurveValue)
                uGValue += value_Average;
            else if(1.0>dcurveValue)
                uGValue += value_NotAverage;
            else if(1.0<dcurveValue)
                uGValue += value_NotAverage;
            if(uGValue > 0xff) uGValue = 0xff;
        }
        else if(0<uBValue && 0xff == uGValue && 0 == uRValue){
            if(1.0 == dcurveValue)
                uBValue -= value_Average;
            else if(1.0>dcurveValue)
                uBValue -= value_NotAverage1;
            else if(1.0<dcurveValue)
                uBValue -= value_NotAverage1;
            if(uBValue<0) uBValue = 0;
        }
        else if(0 == uBValue && 0xff == uGValue && 0xff>uRValue){
            if(1.0 == dcurveValue)
                uRValue += value_Average;
            else if(1.0>dcurveValue)
                uRValue += value_NotAverage1;
            else if(1.0<dcurveValue)
                uRValue += value_NotAverage1;
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
        dpxRgbBuffer[SPECTROGRAM_COLBAR_NUM - i - 1] = uColorValue;
    }
    return;
}
void BitView::renderDensityColorBar(QPainter *pPainter)
{
    qint32 uColorLevel = SPECTROGRAM_COLBAR_NUM;
    QString mstr;
    qreal colBarHeight = this->height() - TOPDIS - (BOTTOMDIS + gsystemstate.windowtype * markerTabelVisiable * BIT_MARKER_TABLE_HEIGHT) - LINEREEOR - WORDHEIGHT;
    qreal colBarBottom = this->height() - WORDHEIGHT * 0.5;
    qreal mcolordiv = colBarHeight/uColorLevel;

    for(qint32 i = 0;i < uColorLevel;i++)
    {
        const QColor color = QColor(QRgb(dpxRgbBuffer[SPECTROGRAM_COLBAR_NUM - i - 1]));
        QRectF rctF(BITWORDLEFT + 20, (colBarBottom - TOPDIS - LINEREEOR) - i*mcolordiv,10,mcolordiv);
        QBrush brush(color);

        pPainter->fillRect(rctF,brush);
    }
//    QPen bvpen;
//    bvpen.setWidth(LINEREEOR);
//    bvpen.setColor(mPenColor.colBarFont);
//    pPainter->setPen(bvpen);
//    pPainter->setFont(QFont("Arial", 8));

//    qreal mbaselevel = gusedsize.grefValue;
//    qreal mdiv = fabs(gusedsize.gdivValue);
//    //      qreal mdivpix = 0.2 * (this->height()- (BOTTOMDIS + gsystemstate.windowtype * markerTabelVisiable * BIT_MARKER_TABLE_HEIGHT) - TOPDIS - mspectrogramHeight);
//    qreal mval = 0.0;
//    mval = mbaselevel;
//    mstr = QString("dBm");
//    pPainter->drawText(BITWORDLEFT - 5, BITWORDHSET + TOPDIS - 3 * RIGHTDIS, WORDWIDTH, WORDHEIGHT, Qt::AlignRight, mstr);

//    mstr = QString("%1").sprintf("%.2lf",mval);
//    pPainter->drawText(BITWORDLEFT - 5, BITWORDHSET + TOPDIS - RIGHTDIS, WORDWIDTH, WORDHEIGHT, Qt::AlignRight, mstr);

//    mval = mbaselevel - mdiv * 10;
//    mstr = QString("%1").sprintf("%.2lf",mval);
//    pPainter->drawText(BITWORDLEFT, colBarBottom - (BOTTOMDIS + gsystemstate.windowtype * markerTabelVisiable * BIT_MARKER_TABLE_HEIGHT) + LINEREEOR, WORDWIDTH, WORDHEIGHT, Qt::AlignRight, mstr);
    return;
}
/**
 * @brief BitView::ChangedBmToUV
 * @param value
 * @return
 */
qreal BitView::ChangedBmToUV(qreal value)
{
    qreal voltGab = 0.;
    qreal calculator = 0.;
    calculator = pow(10, value / 10.);
    voltGab = /*1000000. * */pow(50 * calculator * 0.001, 0.5);//uv
    return voltGab;
}
/**
 * @brief BitView::ChangedBmToMW
 * @param value
 * @return
 */
qreal BitView::ChangedBmToMW(qreal value)
{
    qreal wattsGab = 0.;
    wattsGab = pow(10, value / 10.) / 1000.0;
    return wattsGab;
}
/**
 * @brief BitView::ChangeValueToVoltStr
 * @param label
 * @param value
 */
void BitView::ChangeValueToVoltStr(char *label, qreal value)
{
    qreal CompareValue = value;
    if(value < 0.0)
    {
        CompareValue *= -1;
    }
    if(CompareValue >= 1000000000.){
        sprintf(label, "%.2f ", (qreal) value / 1000000000.);
    }
    else if (/*_level <= 20. &&*/ CompareValue >= 1000000.) {
        sprintf(label, "%.2f ", (qreal) value / 1000000.);
    } else if (CompareValue >= 1000.) {
        sprintf(label, "%.2f ", (qreal) value / 1000.);
    } else if (CompareValue >= 1.) {
        sprintf(label, "%.2f ", (qreal) value);
    } else if (CompareValue >= 0.001) {
        sprintf(label, "%.2f ", (qreal) value * 1000);
    } else if (CompareValue >= 0.000001) {
        sprintf(label, "%.2f ", (qreal) value * 1000000.);
    } else if (CompareValue >= 0.000000001) {
        sprintf(label, "%.2f ", (qreal) value * 1000000000.);
    } else if (CompareValue >= 0.000000000001) {
        sprintf(label, "%.2f ", (qreal) value * 1000000000000.);
    } else if (CompareValue >= 0.000000000000001) {
        sprintf(label, "%.2f ", (qreal) value * 1000000000000000.);
    } else if (CompareValue >= 0.000000000000000001) {
        sprintf(label, "%.2f ", (qreal) value * 1000000000000000000.);
    } else {
        sprintf(label, "%.2f", (qreal) value * 1000000000000000000000.);
    }
}
void BitView::ChangeValueToWattStr(char *label, qreal value)
{
    qreal CompareValue = value;
    if(value < 0.0)
    {
        CompareValue *= -1;
    }
    if (CompareValue >= 1000) {						// W
        sprintf(label, "%.2f ", (qreal)value / 1000.0);
    }  else if (CompareValue >= 1) {					// mW
        sprintf(label, "%.2f ", (qreal)value);
    }  else if (CompareValue >= 0.001) {				// uW
        sprintf(label, "%.2f ", (qreal)value * 1000.0);
    }  else if (CompareValue >= 0.000001) {			// nW
        sprintf(label, "%.2f ", (qreal)value * 1000000.0);
    } else if (CompareValue >= 0.000000001) {			// pW
        sprintf(label, "%.2f ", (qreal)value * 1000000000.0);
    } else if (CompareValue >= 0.000000000001) {		// fW
        sprintf(label, "%.2f ", (qreal)value * 1000000000000.0);
    } else {                                                    	// aW
        sprintf(label, "%.2f ", (qreal)value * 1000000000000000.0);
    }
}
qreal BitView::searchMax()
{
    qreal* renderData = gbitbuffer.trace_render[gctrlmana->gtraceIndex];
    qreal AMax = renderData[0];
    for (qint32 k = 1; k < NOWTRACENUM - 1; k++)
    {
        if(AMax <= renderData[k])
        {
            AMax = renderData[k];
        }
    }
    return AMax;
}
qint32 BitView::searchMin()
{
    qint32 MinIndex = 0;
    qreal* renderData = gbitbuffer.trace_render[gctrlmana->gtraceIndex];
    qreal AMin = renderData[0];
    for (qint32 k = 1; k < NOWTRACENUM - 1; k++)
    {
        if(AMin >= renderData[k])
        {
            AMin = renderData[k];
            MinIndex = k;
        }
    }
    return MinIndex;
}
/**
 * @brief RtSa_Trace::searchPeak
 * peak search should search 0 -- RTSA_NUM_SWEEP_POINT-2 get the max A
 * compare A and RTSA_NUM_SWEEP_POINT-1
 * because the last pt should only compare left, no right
 * @return
 */
qreal BitView::MarkerToPeak()
{
    qint32 MaxIndex = 0;
    qreal* renderData = gbitbuffer.trace_render[gctrlmana->gtraceIndex];
    qreal AMax = renderData[0];
    qreal AMaxTemp = renderData[NOWTRACENUM - 1];
    for (qint32 k = 1; k < NOWTRACENUM - 1; k++)
    {
        if (renderData[k] >= renderData[k - 1] && renderData[k] >= renderData[k + 1] && AMax <= renderData[k])
        {
            AMax = renderData[k];
            MaxIndex = k;
        }
    }
    // Deal with the last point alone
    if(AMaxTemp >= AMax)
    {
        AMax = renderData[NOWTRACENUM - 1];
        MaxIndex = NOWTRACENUM - 1;
    }
    if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_NORMAL)
    {
        gctrlmana->gMarkerNormalIndex[gctrlmana->gMarkerSelect] = MaxIndex;
        gctrlmana->gMarkerNormalFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(MaxIndex);
    }
    else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA)
    {
        gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] = MaxIndex;
        gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(MaxIndex);
    }
    else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA_PAIR)
    {
        gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] = MaxIndex;
        gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(MaxIndex);
    }
    return AMax;
}
/**
 * @brief RtSa_Trace::MarkerToMin
 * peak search should search 0 -- RTSA_NUM_SWEEP_POINT-2 get the max A
 * compare A and RTSA_NUM_SWEEP_POINT-1
 * because the last pt should only compare left, no right
 * @return
 */
void BitView::MarkerToMin()
{
    qint32 curMarkerIndex = searchMin();
    if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_NORMAL)
    {
        gctrlmana->gMarkerNormalIndex[gctrlmana->gMarkerSelect] = curMarkerIndex;
        gctrlmana->gMarkerNormalFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(curMarkerIndex);
    }
    else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA)
    {
        gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] = curMarkerIndex;
        gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(curMarkerIndex);
    }
    else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA_PAIR)
    {
        gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] = curMarkerIndex;
        gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(curMarkerIndex);
    }
    return;
}
/**
 * @brief RtSa_Trace::searchNextPeak
 * @param curMarkerIndex
 * next peak: Find a peak point not greater than the current point based on the current cursor position
 * @return
 */
void BitView::MarkerToNextPeak()
{
    qint32 NextPeakIndex = -1;
    qreal* renderData = gbitbuffer.trace_render[gctrlmana->gtraceIndex];
    qreal AMax = 0;
    qint32 curMarkerIndex = 0;
    if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_NORMAL)
    {
        curMarkerIndex = gctrlmana->gMarkerNormalIndex[gctrlmana->gMarkerSelect];
    }
    else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA)
    {
        curMarkerIndex = gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect];
    }
    else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA_PAIR)
    {
        curMarkerIndex = gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect];
    }
    bool isFirstSearch = true;

    //The first and last points need to be handled separately
    for (qint32 k = 0; k < NOWTRACENUM; k++)
    {
        if(renderData[k] >= renderData[curMarkerIndex])
        {
            continue;
        }
        if(k == 0)
        {
            if(renderData[k] >= renderData[k + 1])
            {
                AMax = renderData[k];
                NextPeakIndex = k;
                isFirstSearch = false;
            }
        }
        else if(k == NOWTRACENUM - 1)
        {
            if(renderData[k] >= renderData[k - 1])
            {
                if(renderData[k] >= AMax)
                {
                    AMax = renderData[k];
                    NextPeakIndex = k;
                }
            }
        }
        else if(renderData[k] > renderData[k + 1] && renderData[k] > renderData[k - 1])
        {
            if(renderData[k] <= renderData[curMarkerIndex])
            {
                if(isFirstSearch)
                {
                    AMax = renderData[k];
                    NextPeakIndex = k;
                    isFirstSearch = false;
                }
                else
                {
                    if(renderData[k] >= AMax)
                    {
                        AMax = renderData[k];
                        NextPeakIndex = k;
                    }
                }

            }
        }
    }
    if(NextPeakIndex >= 0)
    {
        if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_NORMAL)
        {
            gctrlmana->gMarkerNormalIndex[gctrlmana->gMarkerSelect] = NextPeakIndex;
            gctrlmana->gMarkerNormalFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(NextPeakIndex);
        }
        else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA)
        {
            gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] = NextPeakIndex;
            gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(NextPeakIndex);
        }
        else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA_PAIR)
        {
            gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] = NextPeakIndex;
            gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(NextPeakIndex);
        }
     }
    return;
}
/**
 * @brief RtSa_Trace::searchLeftPeak
 * @param curMarkerIndex
 * find the first left peak position based on the current position
 * @return
 */
void BitView::MarkerToLeftPeak()
{
    qint32 LeftPeakIndex = -1;
    qreal* renderData = gbitbuffer.trace_render[gctrlmana->gtraceIndex];
    qint32 curMarkerIndex = 0;
    if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_NORMAL)
    {
        curMarkerIndex = gctrlmana->gMarkerNormalIndex[gctrlmana->gMarkerSelect];
    }
    else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA)
    {
        curMarkerIndex = gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect];
    }
    else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA_PAIR)
    {
        curMarkerIndex = gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect];
    }
    qreal AMax = renderData[curMarkerIndex];
    for (qint32 k = curMarkerIndex - 1; k >= 0; k--)
    {
        if(k == 0)
        {
            if(renderData[0] > AMax)
            {
                AMax = renderData[0];
                LeftPeakIndex = 0;
            }
            break;
        }
        if (renderData[k] > renderData[k - 1] && renderData[k] > renderData[k + 1])
        {
            AMax = renderData[k];
            LeftPeakIndex = k;
            break;
        }
    }
    // when curMarkerIndex = 1. there only point zero left, should deal with alone
    if(curMarkerIndex == 1)
    {
        if(renderData[0] > AMax)
        {
            AMax = renderData[0];
            LeftPeakIndex = 0;
        }
    }
    if(LeftPeakIndex >= 0)
    {
        if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_NORMAL)
        {
            gctrlmana->gMarkerNormalIndex[gctrlmana->gMarkerSelect] = LeftPeakIndex;
            gctrlmana->gMarkerNormalFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(LeftPeakIndex);
        }
        else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA)
        {
            gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] = LeftPeakIndex;
            gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(LeftPeakIndex);
        }
        else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA_PAIR)
        {
            gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] = LeftPeakIndex;
            gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(LeftPeakIndex);
        }
    }
    return ;
}
/**
 * @brief RtSa_Trace::searchRightPeak
 * @param curMarkerIndex
 * find the first right peak position based on the current position
 * @return
 */
void BitView::MarkerToRightPeak()
{
    qint32 RightPeakIndex = -1;
    qreal* renderData = gbitbuffer.trace_render[gctrlmana->gtraceIndex];
    qint32 curMarkerIndex = 0;
    if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_NORMAL)
    {
        curMarkerIndex = gctrlmana->gMarkerNormalIndex[gctrlmana->gMarkerSelect];
    }
    else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA)
    {
        curMarkerIndex = gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect];
    }
    else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA_PAIR)
    {
        curMarkerIndex = gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect];
    }
    qreal AMax = renderData[curMarkerIndex];
    for (qint32 k = curMarkerIndex + 1; k < NOWTRACENUM - 1; k++)
    {
        if(renderData[k] > renderData[k - 1] && renderData[k] > renderData[k + 1])
        {
            AMax = renderData[k];
            RightPeakIndex = k;
            break;
        }
        if(k == NOWTRACENUM - 2)
        {
            if(renderData[k + 1] > AMax)
            {
                AMax = renderData[NOWTRACENUM - 1];
                RightPeakIndex = NOWTRACENUM - 1;
            }
        }
    }
    // when curMarkerIndex = RTSA_NUM_SWEEP_POINT - 2. there only right point left, should deal with alone
    if(curMarkerIndex == NOWTRACENUM - 2)
    {
        if(renderData[NOWTRACENUM - 1] > AMax)
        {
            AMax = renderData[NOWTRACENUM - 1];
            RightPeakIndex = NOWTRACENUM - 1;
        }
    }
    if(RightPeakIndex >= 0)
    {
        if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_NORMAL)
        {
            gctrlmana->gMarkerNormalIndex[gctrlmana->gMarkerSelect] = RightPeakIndex;
            gctrlmana->gMarkerNormalFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(RightPeakIndex);
        }
        else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA)
        {
            gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] = RightPeakIndex;
            gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(RightPeakIndex);
        }
        else if(gctrlmana->gMarkerType[gctrlmana->gMarkerSelect] == BIT_DELTA_PAIR)
        {
            gctrlmana->gMarkerDeltaIndex[gctrlmana->gMarkerSelect] = RightPeakIndex;
            gctrlmana->gMarkerDeltaFreq[gctrlmana->gMarkerSelect] = freqIndexToFreq(RightPeakIndex);
        }
    }
    return;
}

void BitView::setAcqTime(qreal time)
{
    gfreqinfo.gacqTime = time;
    refreshSepectrogramRect();
    return;
}
void BitView::setFreqOffset(qreal freq)
{
    mFreqOffset = freq;
//    gfreqinfo.gstartfreq += mFreqOffset;
//    gfreqinfo.gstopfreq += mFreqOffset;
//    gfreqinfo.gcenterfreq += mFreqOffset;
    return;
}

QString BitView::getPersistenceTimeStr(qreal time)
{
    qreal value = time;
    QString strVal;
    QString strUnit;
    if(time >= BIT_S)
    {
        time /= BIT_S;
        strVal = QString::number(time,'f',3);
        strUnit = QString(" s");
    }
    else if(time >= BIT_MS)
    {
        time /= BIT_MS;
        strVal = QString::number(time,'f',3);
        strUnit = QString(" ms");
    }
    else if(time >= BIT_US)
    {
        time /= BIT_US;
        strVal = QString::number(time,'f',3);
        strUnit = QString(" us");
    }
    else
    {
        time *= BIT_NS;
        strVal = QString::number(time,'f',3);
        strUnit = QString(" ns");
    }
    strVal += strUnit;
    return strVal;
}

/**
 * @brief BitView::renderFMTLayer
 * @param painter
 * @note 刷新FMT层显示
 */
void BitView::renderFMTLayer(QPainter *painter)
{
    if(!misFmtShow)
        return;
    //FMT TEST Albert 19/03/29
    QPen myPen,myOldpen;
//    QPolygonF myPolygon;
    QBrush oldBrush;
//    myPolygon.append(QPointF(LEFTDIS + 1,TOPDIS));
//    for(qint32 k = 0;k < gbitbuffer.gtracenum;k++)
//    {
//        myPolygon.append(QPointF(gbitbuffer.drawpointsX[k],gbitbuffer.drawpointsY[0][k] - 4));
//    }
//    if(gbitbuffer.gtracenum > 0)
//    {
//        myPolygon.append(QPointF(gbitbuffer.drawpointsX[gbitbuffer.gtracenum - 1],TOPDIS));
//    }
//    myPolygon.append(QPointF(LEFTDIS,TOPDIS));

    QPainterPath myPath;
    myPath.addPolygon(gctrlmana->gFmtPolygon);//绘制多边形
    oldBrush = painter->brush();
    myOldpen = painter->pen();
    painter->setBrush(QColor(0,255,0,120));
    painter->setPen(QColor(0,255,0,120));
    painter->drawPath(myPath);
    painter->setBrush(oldBrush);
    painter->setPen(myOldpen);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-13
*/
void BitView::renderTopMarkerPart(QPainter *pPainter, QString str)
{
    gbitpen.setWidth(HALFLINEREEOR);
    gbitpen.setColor(mPenColor.topPart);
    pPainter->setPen(gbitpen);
    QFont mFont;
    mFont.setFamily("Arial");
    mFont.setPixelSize(13);
    mFont.setWeight(QFont::Bold);
    pPainter->setFont(mFont);

    qint32 mx = LEFTDIS + 0.5 * (gusedsize.gpicwidth - TITLEWIDTH);
    qint32 my = TOPDIS - 1 * WORDHEIGHT + HALFLINEREEOR;

    mx = LEFTDIS + gusedsize.gpicwidth - 140;
    my = (LINEREEOR << 1) + WORDHEIGHT;
    pPainter->drawText(mx, my, TITLEWIDTH, WORDHEIGHT, Qt::AlignLeft, str);

    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-24
*/
void BitView::setFmtShow(bool isOn)
{
    misFmtShow = isOn;
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-24
*/
void BitView::setFMTData(qreal *pbuff, qint32 datanum, qint32 datatype)
{
    if(datanum < 0)
        return;
    switch(datatype)
    {
    case BIT_FMT_FREQ:
        for(qint32 i = 0; i < datanum; i++)
        {
            gctrlmana->gFMTFreq[i] = pbuff[i];
        }
//        memcpy(gctrlmana->gFMTFreq,pbuff,datanum * sizeof(qreal));
        FmtXAxisCalculatorFunc(gctrlmana->gFMTFreq,datanum);
        break;
    case BIT_FMT_AMPT:
        for(qint32 i = 0; i < datanum; i++)
        {
            gctrlmana->gFMTAmplitude[i] = pbuff[i];
        }
//        memcpy(gctrlmana->gFMTAmplitude,pbuff, datanum * sizeof(qreal));
        FmtYAxisCalculatorFunc(gctrlmana->gFMTAmplitude,datanum);
        break;
    default:
        break;
    }
    gctrlmana->gFmtPointsNum = datanum;
    refreshFmtDrawData(datanum);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-24
*/
void BitView::FmtXAxisCalculatorFunc(qreal *Freq, quint32 datanum)
{
    //Freq = Freq * MHZ;
    qreal stepfreq = (qreal)(gfreqinfo.gstopfreq - gfreqinfo.gstartfreq)/(gbitbuffer.gtracenum -1);
    qint32 widDiv = this->width() - LEFTDIS - RIGHTDIS - 2;
    qreal Tempfreq = 0.0;
    for(qint32 i = 0; i < datanum; i++)
    {
        Tempfreq = Freq[i];
        if(Tempfreq < gfreqinfo.gstartfreq / BV_MHZ)
        {
            gctrlmana->gFmtPointsX[i] = LEFTDIS;
        }
        else
        {
            if(Tempfreq > gfreqinfo.gstopfreq / BV_MHZ)
            {
                Tempfreq = gfreqinfo.gstopfreq / BV_MHZ;
            }
            gctrlmana->gFmtPointsX[i] = widDiv *  (Tempfreq * BV_MHZ - gfreqinfo.gstartfreq) / (gfreqinfo.gstopfreq - gfreqinfo.gstartfreq) + LEFTDIS;
        }
    }
}

/**
 * @brief BitView::FmtYAxisCalculatorFunc
 * @param level
 * @param datanum
 * @note FMT的Y轴计算
 */
void BitView::FmtYAxisCalculatorFunc(qreal* level, quint32 datanum)
{
    qint32 yAxis = 0;
    qreal baseY = gusedsize.grefValue + gusedsize.goffsetValue;
    qreal bottomY = baseY -  gusedsize.gdivValue * 10;
    qreal stepY = (qreal) gusedsize.gdivValue / gusedsize.gridYSpace;
    for(qint32 i = 0; i < datanum; i++)
    {
        if(level[i] > baseY)
        {
            level[i] = baseY;
        }
        else if(level[i] < bottomY)
        {
            level[i] = bottomY;
        }
        gctrlmana->gFmtPointsY[i] = round((baseY - level[i])/stepY) + BIT_GRID_START_Y;
    }
}
/**
 * @brief BitView::refreshFmtDrawData
 * @param datanum
 * @note 绘制FMT绘制数据
 */
void BitView::refreshFmtDrawData(quint32 datanum)
{
    gctrlmana->gFmtPolygon.clear();
    if(datanum <= 0)
    {
        return;
    }
    if(mFmtType == BIT_FMT_UPPER)
    {
        gctrlmana->gFmtPolygon.append(QPointF(gctrlmana->gFmtPointsX[0],TOPDIS));
        for(qint32 k = 0;k < datanum;k++)
        {
            gctrlmana->gFmtPolygon.append(QPointF(gctrlmana->gFmtPointsX[k],gctrlmana->gFmtPointsY[k]));
        }
        gctrlmana->gFmtPolygon.append(QPointF(gctrlmana->gFmtPointsX[datanum - 1],TOPDIS));
        gctrlmana->gFmtPolygon.append(QPointF(gctrlmana->gFmtPointsX[0],TOPDIS));

    }
    else
    {
        gctrlmana->gFmtPolygon.append(QPointF(gctrlmana->gFmtPointsX[0],height() - BOTTOMDIS));
        for(qint32 k = 0;k < datanum;k++)
        {
            gctrlmana->gFmtPolygon.append(QPointF(gctrlmana->gFmtPointsX[k],gctrlmana->gFmtPointsY[k]));
        }
        gctrlmana->gFmtPolygon.append(QPointF(gctrlmana->gFmtPointsX[datanum - 1],height() - BOTTOMDIS));
        gctrlmana->gFmtPolygon.append(QPointF(gctrlmana->gFmtPointsX[0],height() - BOTTOMDIS));

    }
//    gctrlmana->gFmtPolygon.append(QPointF(LEFTDIS + 1,TOPDIS));
//    gctrlmana->gFmtPolygon.append(QPointF(gctrlmana->gFmtPointsX[0],gctrlmana->gFmtPointsY[0]));
//    QPainter painter(&gsigrendermap);
//    painter.initFrom(this);
//    gbitpen.setColor(Qt::red);
//    gbitpen.setWidth(HALFLINEREEOR);
//    painter.setPen(gbitpen);
//    renderFMTLayer(&painter);
    return;
}

void BitView::setFmtType(qint32 type)
{
    mFmtType = type;
    refreshFmtDrawData(gctrlmana->gFmtPointsNum);
    return;
}
/**
* @brief cal fmt all Y pts, use for ctrl app
* @param
* @Author Albert
* @date 2019-06-05
*/
void BitView::FmtInterpolationCalculatorFunc()
{
    qreal mbottom = TOPDIS + gusedsize.gpicheight - LINEREEOR;
    qint32 i = 0;
    qint32 k = 0;
    qint32 cnt = 0;

    qint32 manualPreviousXPos = 0;
    qint32 manualCurrentXPos  = 0;

    qreal manualPreviousYPos = 0;
    qreal manualCurrentYPos = 0;
    qreal manualPreviousEdgeYPos = 0;
    qreal manualCurrentEdgeYPos = 0;
    qreal manualYStep = 0.;
    qreal manualEdgeYStep = 0.;
    qint32 calYAxis = 0.;

    memset(gctrlmana->gFmtInterpolationData,0,sizeof(qint32)*2*BIT_LIMIT_TOTALDOT);
//    memset(gbitbuffer.gLimitMarginDrawPoint[uLimitSelect],0,sizeof(qreal)*NOWTRACENUM);

    for (i = 1; i < gctrlmana->gFmtPointsNum; i++)
    {
        manualPreviousXPos = gctrlmana->gFmtPointsX[i-1];
        manualCurrentXPos  = gctrlmana->gFmtPointsX[i];
        manualPreviousYPos = gctrlmana->gFmtPointsY[i-1];
        manualCurrentYPos  = gctrlmana->gFmtPointsY[i];

        manualYStep = (qreal)(manualCurrentYPos - manualPreviousYPos) / (qreal) (manualCurrentXPos - manualPreviousXPos);

        cnt = 0;
        for (k = manualPreviousXPos; k < manualCurrentXPos; k++)
        {
            calYAxis = (qint32)(manualPreviousYPos + (manualYStep * (qreal)cnt));

            if(calYAxis<BIT_GRID_START_Y)
                calYAxis = BIT_GRID_START_Y;
            else if(calYAxis>mbottom)
                calYAxis = mbottom;

            if (gctrlmana->gFmtInterpolationData[2*k] < calYAxis)
                gctrlmana->gFmtInterpolationData[2*k] = calYAxis;
            else if(gctrlmana->gFmtInterpolationData[2*k] == calYAxis)
                gctrlmana->gFmtInterpolationData[2*k] = calYAxis;

            gctrlmana->gFmtInterpolationData[2*k + 1] = 0;
            cnt++;
        }
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-05
*/
//QImage BitView::AdjustSaturation(QImage Img, int iSaturateValue)
//{
//    qint32 red, green, blue, nRed, nGreen, nBlue;
//    qint32 pixels = Img.width() * Img.height();
//    unsigned int *data = (unsigned int *)Img.bits();

//    float Increment = iSaturateValue/100.0;

//    float delta = 0;
//    float minVal, maxVal;
//    float L, S;
//    float alpha;

//    for (qint32 i = 0; i < pixels; ++i)
//    {
//        nRed = qRed(data[i]);
//        nGreen = qGreen(data[i]);
//        nBlue = qBlue(data[i]);

//        minVal = std::min(std::min(nRed, nGreen), nBlue);
//        maxVal = std::max(std::max(nRed, nGreen), nBlue);
//        delta = (maxVal - minVal) / 255.0;
//        L = 0.5*(maxVal + minVal) / 255.0;
//        S = std::max(0.5*delta / L, 0.5*delta / (1 - L));

//        if (Increment > 0)
//        {
//            alpha = std::max(S, 1 - Increment);
//            alpha = 1.0 / alpha - 1;
//            red = nRed + (nRed - L*255.0)*alpha;
//            red = (red < 0x00) ? 0x00 : (red > 0xff) ? 0xff : red;
//            green = nGreen + (nGreen - L*255.0)*alpha;
//            green = (green < 0x00) ? 0x00 : (green > 0xff) ? 0xff : green;
//            blue = nBlue + (nBlue - L*255.0)*alpha;
//            blue = (blue < 0x00) ? 0x00 : (blue > 0xff) ? 0xff : blue;
//        }
//        else
//        {
//            alpha = Increment;
//            red = L*255.0 + (nRed - L * 255.0)*(1+alpha);
//            red = (red < 0x00) ? 0x00 : (red > 0xff) ? 0xff : red;
//            green = L*255.0 + (nGreen - L * 255.0)*(1+alpha);
//            green = (green < 0x00) ? 0x00 : (green > 0xff) ? 0xff : green;
//            blue = L*255.0 + (nBlue - L * 255.0)*(1+alpha);
//            blue = (blue < 0x00) ? 0x00 : (blue > 0xff) ? 0xff : blue;
//        }

//        data[i] = qRgba(red, green, blue, qAlpha(data[i]));
//    }

//    return Img;
//}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-11
*/
void BitView::setTriggerrMode(qint32 mode)
{
    gctrlmana->gTriggerMode = mode;
    refreshSepectrogramRect();
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-11
*/
void BitView::setVideoTriggerLevel(qreal video)
{
    gctrlmana->gVideoLevel = video;
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-13
*/
void BitView::recalVideoAxis()
{
    qreal mdeta = 0.1 * 10 * (gusedsize.gpicwidth - 2 * LINEREEOR) / (NOWTRACENUM - 1);
    qreal mbaselevel = gusedsize.grefValue + gusedsize.goffsetValue;
    qreal perYdBpixels = gusedsize.gdivValue * 10.0 / gusedsize.gpicheight ;
    qreal mconvy = 0.0;
    qreal mbottom =CenterPartRect.bottom() /*- HALFLINEREEOR*/;
    qreal mtop = CenterPartRect.top();

    for(qint32 i = 0; i < NOWTRACENUM; i++)
    {
        gctrlmana->gVideoPointsX[i] = BIT_GRID_START_X + i * mdeta;
        mconvy = (mbaselevel - gctrlmana->gVideoLevel - gusedsize.goffsetValue) / perYdBpixels + mtop;
        if (mconvy < mtop)
        {
            mconvy = mtop;
        }
        else if (mconvy > mbottom)
        {
            mconvy = mbottom;
        }
        gctrlmana->gVideoPointsY[i] = mconvy;
    }
    return;
}


/**
 * @brief BitView::renderVideoTriggerLevel
 * @param painter
 * @note 绘制video 触发
 * @date
 */
void BitView::renderVideoTriggerLevel(QPainter *painter)
{
  recalVideoAxis();
  if(gctrlmana->gTriggerMode != BIT_TRIGGER_VIDEO)
    return;
  QPen pen;
  pen.setColor(Qt::red);
  pen.setWidth(2);
  painter->setPen(pen);
  qint32 k = 1;
  for(k = 1;k < NOWTRACENUM;k++)
    {
      painter->drawLine(
            QPointF(gctrlmana->gVideoPointsX[k-1],
            gctrlmana->gVideoPointsY[k-1]),
          QPointF(gctrlmana->gVideoPointsX[k],
                  gctrlmana->gVideoPointsY[k]));
    }
  return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-01
*/
//void BitView::updateGaussianGold(float delta, int radius)
//{
//    for (int i = 0; i < 2 * radius + 1; i++)
//    {
//        int x = i - radius;
//        gaussian[i] = exp(-(x * x) /
//                          (2 * delta * delta));
//    }
//    return;
//}

//float BitView::heuclideanLen(float4 a, float4 b, float d)
//{
//    float mod = (b.x - a.x) * (b.x - a.x) +
//                (b.y - a.y) * (b.y - a.y) +
//                (b.z - a.z) * (b.z - a.z) +
//                (b.w - a.w) * (b.w - a.w);

//    return exp(-mod / (2 * d * d));
//}

//unsigned int BitView::hrgbaFloatToInt(float4 rgba)
//{
//    unsigned int w = (((unsigned int)(fabs(rgba.w) * 255.0f)) & 0xff) << 24;
//    unsigned int z = (((unsigned int)(fabs(rgba.z) * 255.0f)) & 0xff) << 16;
//    unsigned int y = (((unsigned int)(fabs(rgba.y) * 255.0f)) & 0xff) << 8;
//    unsigned int x = ((unsigned int)(fabs(rgba.x) * 255.0f)) & 0xff;

//    return (w | z | y | x);
//}

//float4 BitView::hrgbaIntToFloat(unsigned int c)
//{
//    float4 rgba;
//    rgba.x = (c & 0xff) * 0.003921568627f;       //  /255.0f;
//    rgba.y = ((c>>8) & 0xff) * 0.003921568627f;  //  /255.0f;
//    rgba.z = ((c>>16) & 0xff) * 0.003921568627f; //  /255.0f;
//    rgba.w = ((c>>24) & 0xff) * 0.003921568627f; //  /255.0f;
//    return rgba;
//}

//float4 BitView::mul(float a, float4 b)
//{
//    float4 ans;
//    ans.x = a * b.x;
//    ans.y = a * b.y;
//    ans.z = a * b.z;
//    ans.w = a * b.w;

//    return ans;
//}

//float4 BitView::add4(float4 a, float4 b)
//{
//    float4 ans;
//    ans.x = a.x + b.x;
//    ans.y = a.y + b.y;
//    ans.z = a.z + b.z;
//    ans.w = a.w + b.w;

//    return ans;
//}

//void BitView::bilateralFilterGold(unsigned int *pSrc,
//                         unsigned int *pDest,
//                         float e_d,
//                         int w, int h, int r)
//{
//    float4 *hImage = new float4[w * h];
//    float domainDist, colorDist, factor;

//    for (int y = 0; y < h; y++)
//    {
//        for (int x = 0; x < w; x++)
//        {
//            hImage[y * w + x] = hrgbaIntToFloat(pSrc[y * w + x]);
//        }
//    }

//    for (int y = 0; y < h; y++)
//    {
//        for (int x = 0; x < w; x++)
//        {
//            float4 t(0.0f);
//            float sum = 0.0f;

//            for (int i = -r; i <= r; i++)
//            {
//                int neighborY = y + i;

//                //clamp the neighbor pixel, prevent overflow
//                if (neighborY < 0)
//                {
//                    neighborY = 0;
//                }
//                else if (neighborY >= h)
//                {
//                    neighborY = h - 1;
//                }

//                for (int j = -r; j <= r; j++)
//                {
//                    domainDist = gaussian[r + i] * gaussian[r + j];

//                    //clamp the neighbor pixel, prevent overflow
//                    int neighborX = x + j;

//                    if (neighborX < 0)
//                    {
//                        neighborX = 0;
//                    }
//                    else if (neighborX >= w)
//                    {
//                        neighborX = w - 1;
//                    }

//                    colorDist = heuclideanLen(hImage[neighborY * w + neighborX], hImage[y * w + x], e_d);
//                    factor = domainDist * colorDist;
//                    sum += factor;
//                    t = add4(t, mul(factor, hImage[neighborY * w + neighborX]));
//                }
//            }

//            pDest[y * w + x] = hrgbaFloatToInt(mul(1 / sum, t));
//        }
//    }

//    delete[] hImage;
//}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-05
*/
bool BitView::checkOriData(qreal *data, quint32 dataNum)
{
    if(dataNum <= 0)
    {
        dataNum = 801;
    }
    for(qint32 i = 0; i < dataNum; i++)
    {
        if(data[i] > 0.000001 || data[i] < -0.000001)
        {
            return true;
        }
    }
    return false;

//    return true;
}

//Tony 1026 Add
qreal BitView::freqIndexToCenterFreq(qint32 index)
{
    qreal startfreq = gfreqinfo.gstartfreq;
    qreal stopfreq =  gfreqinfo.gstopfreq;
//    qint32 pointnum = gbitbuffer.gtracenum;
    qint32 pointnum;
    if(gbitbuffer.gtracenum == 0)
        pointnum = NOWTRACENUM;
    else
        pointnum = gbitbuffer.gtracenum;
    qreal mdeta = (qreal)(stopfreq - startfreq) / (pointnum - 1);
    qreal freq = 0;

    freq = (gfreqinfo.gstopfreq + gfreqinfo.gstartfreq)/2 - mdeta * index;
    return freq;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-11-26
*/
qreal BitView::IndexToRefLevel(qint32 index)
{
    qreal refLevel = 0.0;
    qreal mbaselevel = gusedsize.grefValue + gusedsize.goffsetValue;
    qreal perYdBpixels = gusedsize.gdivValue * 10.0 / gusedsize.gpicheight ;
    refLevel = gusedsize.grefValue +  (perYdBpixels * index);
    if(refLevel >= 20)
        refLevel = 20;
    else if(refLevel <= -180)
        refLevel = -180;
    return refLevel;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-05
*/
void BitView::setMarkerRefAmpt(qreal refAmpt, quint32 markerID)
{
    gctrlmana->gMarkerRefAmpt[markerID] = refAmpt;
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-05
*/
qreal BitView::getMarkerRefAmpt(quint32 markerID)
{
    return gctrlmana->gMarkerRefAmpt[markerID];
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-05
*/
void BitView::setMarkerNormalPosY(qint32 pos, quint32 markerID)
{
    gctrlmana->gMarkerNormalPosY[markerID] = pos;
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-05
*/
qint32 BitView::getMarkerNormalPosY(quint32 markerID)
{
    return gctrlmana->gMarkerNormalPosY[markerID];
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-09
*/
void BitView::on_mouseclick()
{
    if(clickCnt == 2)
    {
//        timer->stop();
        if(gsystemstate.windowtype == BIT_SINGLEWINDOW)
        {
            misDoubleClicked = false;
            return;
        }
        misDoubleClicked = !misDoubleClicked;
        emit mouseDoubleClickedSig(misDoubleClicked);
        clickCnt = 0;
    }
    timer->stop();
    clickCnt = 0;
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-10-31
*/
#ifdef BITVIEW_F239
void BitView::TouchEventSlot()
{
    if(misBitScaleChanged)
    {
        misTouchEventDone = true;
        emit scaleResize(BitXScale,BitYScale);
        misBitScaleChanged = false;
        nFingerTouchCnt = 1;
        misBitCenFreqChanged = false;
        misBitReflevelChanged = false;
    }
//    gsigrendermap = gsigrendermap.scaled(width(),height(),Qt::IgnoreAspectRatio,Qt::FastTransformation);
    Touchtimer->stop();
    return;
}
#endif
void BitView::renderFileLoadTraceLine()
{
    if(getBitviewType() != BIT_SPECTRUM)
        return;
    gsigrendermap.fill(Qt::transparent);
    QPainter painter(&gsigrendermap);
    painter.initFrom(this);
    gbitpen.setColor(Qt::red);
    gbitpen.setWidth(HALFLINEREEOR);
    painter.setPen(gbitpen);
//    //when app first run, there may be no data transfer, so here need check data buf.
//    if(!checkOriData(gbitbuffer.trace_ori,gbitbuffer.gtracenum))
//    {
//        return;
//    }
//    //this func put here for sizechanged
    for(qint32 i = 0; i < SUPPORTTRACENUM; i++)
    {
        axesTranslate(i,gbitbuffer.trace_render[i],gbitbuffer.gtracenum);
    }
//    oriDataDeals(gbitbuffer.trace_ori,gbitbuffer.gtracenum);
    //Tony 1113
    if(!gctrlmana->gLimitVisiable)
    {
        renderSiglines(&painter);
    }else
    {
        renderLimitPart(&painter);
    }
    if(gctrlmana->gtracetype[gctrlmana->gtraceIndex] != BIT_TRACE_OFF)
    {
        renderMarkerPart(&painter);
    }
    this->repaint();
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-04
*/
void BitView::setFileLoadDoneFlag(bool isFileLoad)
{
    mFileLoadFlag = isFileLoad;
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-04
*/
void BitView::renderFileSpectrogram(qreal *pData)
{
    getSync();
    oriDataDeals(pData,gbitbuffer.gtracenum);
    gsigrendermap.fill(Qt::transparent);
    QPainter painter(&gsigrendermap);
    painter.initFrom(this);
    drawSpectrogramSmallPix(&painter);
    drawSpectrogramBigPix(&painter);
    //! start pos to next index.
    mCacheRealNum ++;
    if(mCacheRealNum >= SPECTROGRAM_CACHE_DATA)
    {
        mCacheRealNum = SPECTROGRAM_CACHE_DATA;
    }
    //! draw cur trace info
    drawCurTraceIndex(&painter,mCacheRealNum);
    releaseSync();
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-04
*/
qint32 BitView::getSpectrogramValidStartPos(qint32 &validStartPos, qint32 &realNum)
{
    validStartPos = mCacheDataStartPos;
    realNum = mCacheRealNum;
    return mCacheDataStartPos;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-11-18
*/
void BitView::renderDoubleClickPixMap()
{
#ifdef BITVIEW_F239
    gDoubleClickPixMap.fill(Qt::transparent);
    QPainter painter(&gDoubleClickPixMap);
    painter.initFrom(this);
    gbitpen.setColor(Qt::red);
    gbitpen.setWidth(HALFLINEREEOR);
    painter.setPen(gbitpen);
    qreal mdeta = 0.1 * 10 * (gusedsize.gpicwidth - 2 * LINEREEOR) / (gbitbuffer.gtracenum - 1);
    quint32 i = 0;
    for(i = 0;i < gbitbuffer.gtracenum;i++)
    {
        gbitbuffer.drawpointsX[i] = i * mdeta;
    }

    if(!mFileLoadFlag)
    {
        //when app first run, there may be no data transfer, so here need check data buf.
        if(!checkOriData(gbitbuffer.trace_ori,gbitbuffer.gtracenum))
        {
            return;
        }
        //this func put here for sizechanged
        oriDataDeals(gbitbuffer.trace_ori,gbitbuffer.gtracenum);
    }
    else
    {
        for(qint32 i = 0; i < SUPPORTTRACENUM; i++)
        {
            axesTranslate(i,gbitbuffer.trace_render[i],gbitbuffer.gtracenum);
        }
    }
    if(mBitviewType == BIT_DENSITY)
    {
        painter.drawImage(CenterPartRect.left() - BIT_GRID_START_X,CenterPartRect.top(),imageFromData);
        QPen pOldPen = painter.pen();
        painter.setPen(QColor(255,255,255,255));
        for(quint32 k = 1;k < gbitbuffer.gtracenum;k++)
        {
            painter.drawLine(QPointF(gbitbuffer.drawpointsX[k-1],gbitbuffer.drawpointsY[gctrlmana->gtraceIndex][k-1]),QPointF(gbitbuffer.drawpointsX[k],gbitbuffer.drawpointsY[gctrlmana->gtraceIndex][k]));
        }
        painter.setPen(pOldPen);
    }
    else
    {
        //Tony 1113
        if(!gctrlmana->gLimitVisiable)
        {
            renderSiglines(&painter);
        }else
        {
            renderLimitPart(&painter);
        }
    }

    for(i = 0;i < gbitbuffer.gtracenum;i++)
    {
        gbitbuffer.drawpointsX[i] = BIT_GRID_START_X + i * mdeta;
    }
//    if((qint32)(gctrlmana->gtracetype[gctrlmana->gtraceIndex]) != BIT_TRACE_OFF)
//    {
//        renderMarkerPart(&painter);
//    }
//    renderVideoTriggerLevel(&painter);
    //Albert for FMT 19/03/29
//    renderFMTLayer(&painter);
#endif
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-11-25
*/
//void BitView::renderTagline()
//{
//#ifdef BITVIEW_F239
//    QPainter painter(&gDoubleClickPixMap);
//    if(misBitCenFreqChanged)
//    {
//        painter.setPen(QPen(Qt::red,2,Qt::DashLine));
//        painter.drawLine(gWindowPos.StartXPos,BIT_GRID_START_Y,gWindowPos.StartXPos,height() - BIT_GRID_START_Y);
//    }
//    if(misBitReflevelChanged)
//    {
//        painter.setPen(QPen(Qt::green,2,Qt::DashLine));
//        painter.drawLine(0,gWindowPos.StartYPos,width() - RIGHTDIS - LEFTDIS - HALFLINEREEOR,gWindowPos.StartYPos);
//    }
//#endif
//    return;
//}
/**
* @brief
* @param
* @Author Albert
* @date 2019-12-04
*/
void BitView::setspectrogramCursorID(qint32 CursorId)
{
    gctrlmana->gCurCursorID = CursorId;
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-12-04
*/
qint32 BitView::getspectrogramCursorID()
{
    return gctrlmana->gCurCursorID;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-12-02
*/
void BitView::setSepctrogramEnableDrawCursor(qint32 CursorId,bool isEnable)
{
    gctrlmana->gCursorState[CursorId] = isEnable;
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-12-02
*/
bool BitView::isSepectrogramDrawCursorEnable(qint32 CursorId)
{
    return gctrlmana->gCursorState[CursorId];
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-12-02
*/
void BitView::setspectrogramCursorIndex(qint32 CursorId,qint32 index)
{
    qint32 nTop = this->height() - (BOTTOMDIS + gsystemstate.windowtype * markerTabelVisiable * BIT_MARKER_TABLE_HEIGHT) - TOPDIS - LINEREEOR;

    switch (mBitviewType) {
    case BIT_SPECTROGRAM:
        if(index > mCacheRealNum)
            index = mCacheRealNum - 1;
        break;
    case BIT_DENSITY:
        if(index > mDensityArrayTotalNum)
            index = mDensityArrayTotalNum - 1;
        break;
    default:
        break;
    }
    if(index > nTop)
        index = nTop;
    gctrlmana->gCursorPosition[CursorId] = index;
//    mSpectrogramIndex = index;
//    renderSpectrogramCursorIndex();
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-12-02
*/
qint32 BitView::getspectrogramCursorIndex(qint32 CursorId)
{
    return gctrlmana->gCursorPosition[CursorId];
//    return mSpectrogramIndex;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-12-02
*/
void BitView::renderSpectrogramCursorIndex(QPainter *painter)
{
    qint32 mSpectrogramIndex;
    QString str;
    QPen pen;
    pen.setColor(mPenColor.curTraceIndex);
    pen.setWidth(2);
    painter->setFont(QFont("Arial", 8));
    qint32 nLeft = LEFTDIS;
    qint32 nWidth = this->width() - LEFTDIS - RIGHTDIS-HALFLINEREEOR;
    qint32 nHeigth = this->height() - (BOTTOMDIS + gsystemstate.windowtype * markerTabelVisiable * BIT_MARKER_TABLE_HEIGHT) - TOPDIS - LINEREEOR;
    for(qint32 i = 0; i < SUPPORTTRACENUM; i++)
    {
        if(gctrlmana->gCursorState[i] == BITON)
        {
            pen.setStyle(Qt::DashLine);
            if(gctrlmana->gCursorPosition[i] > nHeigth)
                gctrlmana->gCursorPosition[i] = nHeigth;
            QRectF rectDownBelow(nLeft - 18,nHeigth + TOPDIS - gctrlmana->gCursorPosition[i],100,20);
            QRectF rectUpTop(nLeft - 18,nHeigth + TOPDIS - gctrlmana->gCursorPosition[i] - 5,100,20);
            if(i == gctrlmana->gCurCursorID)
            {
                pen.setStyle(Qt::SolidLine);
            }
            mSpectrogramIndex = gctrlmana->gCursorPosition[i];
            painter->setPen(pen);
            //!draw cur trace line
            if(mSpectrogramIndex <= nHeigth)
            {
                painter->drawLine(nLeft ,nHeigth + TOPDIS - mSpectrogramIndex,nLeft + 1 + nWidth - 2,nHeigth + TOPDIS - mSpectrogramIndex);
            }

            str.sprintf("C%d",i + 1);
            if(gctrlmana->gCursorPosition[i] < nHeigth - 20)
            {
                painter->drawText(rectUpTop,Qt::AlignLeft,str);
            }
            else
            {
                painter->drawText(rectDownBelow,Qt::AlignLeft,str);
            }

        }
    }
    return;
}

void BitView::resetDensityLineData()
{
    qint32 startPos = 0;
    mDensityArrayStartPos = (mDensityArrayStartPos) % SPECTROGRAM_CACHE_DATA;
    for(qint32 i = 0; i < SUPPORTTRACENUM; i++)
    {
        if(gctrlmana->gCursorState[i] == BITON && gctrlmana->gCurCursorID == i)
        {
            if(mDensityArrayStartPos <= gctrlmana->gCursorPosition[i])
            {
                if(mDensityArrayTotalNum >= SPECTROGRAM_CACHE_DATA)
                {
                    startPos = SPECTROGRAM_CACHE_DATA - (gctrlmana->gCursorPosition[i] - mDensityArrayStartPos);
                }
                else
                {
                    return;
                }
            }
            else
            {
                startPos = mDensityArrayStartPos - gctrlmana->gCursorPosition[i];
            }
            startPos = (startPos) % SPECTROGRAM_CACHE_DATA;
            memcpy(gbitbuffer.trace_ori,mCacheData + startPos * SPECTROGRAM_TRACE_SIZE,sizeof(qreal) * gbitbuffer.gtracenum);
        }
    }
    return;
}

bool BitView::renderDensityLines(QPainter *painter)
{
    qint32 startPos = 0;
    bool isTrue = false;
    for(qint32 i = 0; i < SUPPORTTRACENUM; i++)
    {
        if(gctrlmana->gCursorState[i] == BITON)
        {
            isTrue = true;
            if(mDensityArrayStartPos <= gctrlmana->gCursorPosition[i])
            {
                if(mDensityArrayTotalNum >= SPECTROGRAM_CACHE_DATA)
                {
                    startPos = SPECTROGRAM_CACHE_DATA - (gctrlmana->gCursorPosition[i] - mDensityArrayStartPos);
                }
                else
                {
                    continue;
                }
            }
            else
            {
                startPos = mDensityArrayStartPos - gctrlmana->gCursorPosition[i];
            }
            startPos = (startPos) % SPECTROGRAM_CACHE_DATA;

            axesTranslate(i,mCacheData + startPos * SPECTROGRAM_TRACE_SIZE,gbitbuffer.gtracenum);

            if (BITTR1 == i)
            {
                painter->setPen(mTraceColor.Trace1);
            }
            else if (BITTR2 == i)
            {
                painter->setPen(mTraceColor.Trace2);
            }
            else if (BITTR3 == i)
            {
                painter->setPen(mTraceColor.Trace3);
            }
            else if (BITTR4 == i)
            {
                painter->setPen(mTraceColor.Trace4);
            }
            else if (BITTR5 == i)
            {
                painter->setPen(mTraceColor.Trace5);
            }
            else if (BITTR6 == i)
            {
                painter->setPen(mTraceColor.Trace6);
            }
            for(qint32 k = 1;k < gbitbuffer.gtracenum;k++)
            {
                painter->drawLine(QPointF(gbitbuffer.drawpointsX[k-1],gbitbuffer.drawpointsY[i][k-1]),QPointF(gbitbuffer.drawpointsX[k],gbitbuffer.drawpointsY[i][k]));
            }
        }
    }
    return isTrue;
}

bool BitView::isSpectrogramCursorEnable()
{
    for(qint32 i = 0; i < SUPPORTTRACENUM; i++)
    {
        if(gctrlmana->gCursorState[i])
        {
            return true;
        }
    }
    return false;
}
#endif
