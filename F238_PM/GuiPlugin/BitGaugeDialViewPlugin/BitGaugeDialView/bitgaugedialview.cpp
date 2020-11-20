#include "bitgaugedialview.h"
#include <QTimer>
#include <QLinearGradient>
#include <qmath.h>
#include <QDebug>
#include <QStylePainter>

QRegExp DelZeroRx;

BitGaugeDialView::BitGaugeDialView(QWidget *parent)
    : QWidget(parent)
{
    m_summayData.gNum = 8;

    m_summayData.gSummayName[0] = "Forward Average";
    m_summayData.gSummayName[1] = "Crest Factor";
    m_summayData.gSummayName[2] = "Calculated Burst Power";
    m_summayData.gSummayName[3] = "Peak Envelope Power";
    m_summayData.gSummayName[4] = "Reverse Average";
    m_summayData.gSummayName[5] = "Reflectopm Cpeffocoent";
    m_summayData.gSummayName[6] = "Return Loss";
    m_summayData.gSummayName[7] = "VSWR";

    m_summayData.gSummayData[0] =  0.0;
    m_summayData.gSummayData[1] =  0.0;
    m_summayData.gSummayData[2] =  0.0;
    m_summayData.gSummayData[3] =  0.0;
    m_summayData.gSummayData[4] =  0.0;
    m_summayData.gSummayData[5] =  0.0;
    m_summayData.gSummayData[6] =  0.0;
    m_summayData.gSummayData[7] =  0.0;

    m_summayData.gSummayUnit[0] =  "    dBm";
    m_summayData.gSummayUnit[1] =  "     dB";
    m_summayData.gSummayUnit[2] =  "    dBm";
    m_summayData.gSummayUnit[3] =  "    dBm";
    m_summayData.gSummayUnit[4] =  "    dBm";
    m_summayData.gSummayUnit[5] =  "       ";
    m_summayData.gSummayUnit[6] =  "     dB";
    m_summayData.gSummayUnit[7] =  "       ";


    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    m_bOffsetFreq = false;

    m_pixmapLayerBottom = QPixmap(10,10);
    m_pixmapLayerBottom.fill(m_PenColor.background);
    m_pixmapForward = QPixmap(10,10);
    m_pixmapForward.fill(m_PenColor.background);
    m_pixmapReverse = QPixmap(10,10);
    m_pixmapReverse.fill(m_PenColor.background);
    m_pixmapPower = QPixmap(10,10);
    m_pixmapPower.fill(m_PenColor.background);

    m_pixmapPowerTitle = QPixmap(10,10);
    m_pixmapPowerTitle.fill(m_PenColor.background);
    m_pixmapPowerData= QPixmap(10,10);
    m_pixmapPowerData.fill(m_PenColor.background);
    m_pixmapLayerSummay = QPixmap(10,10);
    m_pixmapLayerSummay.fill(m_PenColor.background);
    m_pixmapBottomInfo = QPixmap(10,10);
    m_pixmapBottomInfo.fill(m_PenColor.background);;
    m_pixmapTopInfo = QPixmap(10,10);
    m_pixmapTopInfo.fill(m_PenColor.background);

    m_nIndexAverage = 0;
    m_nAveragePoint = 1;
    m_fPowerPointTotle = 0;

    m_nUnitIndex = UNIT_DBM;
    m_nUnitType = PM_BIT_DBM;

    m_fPowerAverage = 0;
    m_fPowerTotle = 0;
    m_fTotlePoint = 0;

    m_bHoldMax = false;
//    m_bOffsetPower = false;

    m_fStartAngle = 0;
    m_fAngleLen = 140;

    m_fMinDial = 0;
    m_fMaxDial = 220;

    m_fMinPower = 0;
    m_fMaxPower = 100;

//    m_fCurPowerData = m_fMinDial;

//    m_bPowerZero = false;
//    m_bPowerZeroCal = false;
//    m_fPowerBase = 0;

//    m_bdBmRelativeBaseForward = false;
//    m_bdBmRelativeBaseForwardCal = false;
//    m_fdBmRelativeBaseForward = 0;

//    m_bdBmRelativeBaseReverse = false;
//    m_bdBmRelativeBaseReverseCal = false;
//    m_fdBmRelativeBaseReverse = 0;
//    m_nDisplayModle = PM_DISPLAY_FORWARD_AVERAGE;

    m_nDisplayModle = PM_DISPLAY_V90_POWER;

    setdisplaymode(PM_BIT_DEFAULTMODE);    
    CenterPartRect ={PM_BIT_GRID_START_X,PM_BIT_GRID_START_Y,
                     this->width()-PM_LEFTDIS-PM_RIGHTDIS-PM_LINEREEOR,
                     this->height()-PM_TOPDIS- PM_BOTTOMDIS - PM_LINEREEOR};

    SetArcBottomLeft("__.__ __",PM_LAYER_LEFT,0);
    SetArcBottomRight("__.__ __",PM_LAYER_LEFT,0);
    SetArcBottomLeft("__.__ __",PM_LAYER_LEFT,1);
    SetArcBottomRight("__.__ __",PM_LAYER_LEFT,1);
    SetArcBottomLeft("__.__ __",PM_LAYER_LEFT,2);
    SetArcBottomRight("__.__ __",PM_LAYER_LEFT,2);

    SetArcBottomLeft("__.__ __",PM_LAYER_RIGHT,0);
    SetArcBottomRight("__.__ __",PM_LAYER_RIGHT,0);
    SetArcBottomLeft("__.__ __",PM_LAYER_RIGHT,1);
    SetArcBottomRight("__.__ __",PM_LAYER_RIGHT,1);
    SetArcBottomLeft("__.__ __",PM_LAYER_RIGHT,2);
    SetArcBottomRight("__.__ __",PM_LAYER_RIGHT,2);


    m_layerPixMap[PM_LAYER_LEFT].strCurShow = "__.__ __";
    m_layerPixMap[PM_LAYER_RIGHT].strCurShow = "__.__ __";

    connect(this,SIGNAL(InfoBottom()),this,SLOT(refreshInfoBottom()));
    connect(this,SIGNAL(InfoTop()),this,SLOT(refreshInfoTop()));
    connect(this,SIGNAL(PixmapBottom()),this,SLOT(refreshLayerBottom()));
    connect(this,SIGNAL(PixmapFirst()),this,SLOT(refreshLayerFirst()));
    connect(this,SIGNAL(PixmapSecond()),this,SLOT(refreshLayerSecond()));
    connect(this,SIGNAL(PixmapThird()),this,SLOT(refreshLayerThird()));
    connect(this,SIGNAL(PixmapSummay()),this,SLOT(refreshLayerSummay()));
    connect(this,SIGNAL(PixmapCCDF()),this,SLOT(refreshLayerCCDF()));


    connect(this,SIGNAL(PixmapSummayData()),this,SLOT(refreshLayerSummay()));
      m_fRelativeForward = 0;
      m_fRelativeReverse = 0;
}

BitGaugeDialView::~BitGaugeDialView()
{
}

void BitGaugeDialView::paintEvent(QPaintEvent */*event*/)
{
    QStylePainter pPainter(this);

    pPainter.drawPixmap(0, 0, m_pixmapLayerBottom);
    if(PM_DISPLAY_SUMMARY == m_nDisplayModle ||PM_DISPLAY_FORWARD_CCDF == m_nDisplayModle)
    {
        pPainter.drawPixmap(0,0, m_pixmapLayerSummay);
    }
    else
    {
        if(PM_DISPLAY_V90_POWER == m_nDisplayModle)
        {
            pPainter.drawPixmap(CenterPartRect.left(), CenterPartRect.top(),CenterPartRect.width(),CenterPartRect.height(),m_pixmapPower);
            pPainter.drawPixmap(CenterPartRect.left(), CenterPartRect.top(),CenterPartRect.width(),CenterPartRect.height(),m_pixmapPowerTitle);
            pPainter.drawPixmap(CenterPartRect.left(), CenterPartRect.top(),CenterPartRect.width(),CenterPartRect.height(),m_pixmapPowerData);
        }
        else
        {
            int nCemterMid = CenterPartRect.width()*0.5;
            pPainter.drawPixmap(CenterPartRect.left(), CenterPartRect.top(),nCemterMid ,CenterPartRect.height(),m_pixmapForward);
            pPainter.drawPixmap(CenterPartRect.left(), CenterPartRect.top(),nCemterMid ,CenterPartRect.height(),m_pixForwardTitle);
            pPainter.drawPixmap(CenterPartRect.left(), CenterPartRect.top(),nCemterMid ,CenterPartRect.height(),m_pixForwardData);
            pPainter.drawPixmap(CenterPartRect.left() +nCemterMid , CenterPartRect.top(), nCemterMid,CenterPartRect.height(),m_pixmapReverse);
            pPainter.drawPixmap(CenterPartRect.left() +nCemterMid , CenterPartRect.top(), nCemterMid,CenterPartRect.height(),m_pixReverseTitle);
            pPainter.drawPixmap(CenterPartRect.left() +nCemterMid , CenterPartRect.top(), nCemterMid,CenterPartRect.height(),m_pixReverseData);
        }
        pPainter.drawPixmap(0, 0, m_pixmapBottomInfo);
        pPainter.drawPixmap(0, 0, m_pixmapTopInfo);
    }
}

void BitGaugeDialView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    m_pixmapLayerBottom = m_pixmapLayerBottom.scaled(width(),height(),Qt::IgnoreAspectRatio,Qt::FastTransformation);
    m_pixmapTopInfo = m_pixmapLayerBottom;
    m_pixmapBottomInfo = m_pixmapLayerBottom;
    CenterPartRect ={PM_BIT_GRID_START_X,PM_BIT_GRID_START_Y,
                     m_pixmapLayerBottom.width() - PM_LEFTDIS-PM_RIGHTDIS-PM_LINEREEOR,
                     m_pixmapLayerBottom.height() - PM_BIT_GRID_START_Y *2};

    m_pixmapPower = m_pixmapPower.scaled(CenterPartRect.width(),CenterPartRect.height(),Qt::IgnoreAspectRatio,Qt::FastTransformation);
    m_pixmapPowerTitle = m_pixmapPower;
    m_pixmapPowerData = m_pixmapPower;

    m_pixmapForward = m_pixmapForward.scaled(CenterPartRect.width()*0.5,CenterPartRect.height(),Qt::IgnoreAspectRatio,Qt::FastTransformation);

    m_pixmapReverse =  m_pixmapForward;
    m_pixForwardTitle=  m_pixmapForward;
    m_pixReverseTitle = m_pixmapReverse;
    m_pixForwardData =  m_pixmapForward;
    m_pixReverseData = m_pixmapReverse;
    m_pixmapLayerSummay = m_pixmapLayerBottom;

    emit PixmapBottom();
    return;
}

void BitGaugeDialView::setDisplayModle(qint32 nDisplayModle)
{
    m_nDisplayModle = nDisplayModle;


    switch (m_nDisplayModle) {
    case PM_DISPLAY_FORWARD_AVERAGE:
        m_fPowerTotle = 0;
        m_fTotlePoint = 0;
        SetArcMidTitle("Forward Avg",PM_LAYER_LEFT);

        setDisplayRectLeft("Forward Avg Watts",PM_LAYER_LEFT,0);
        setDisplayRectLeft("Forward Direct",PM_LAYER_LEFT,1);
        setDisplayRectLeft("Forward Peak",PM_LAYER_LEFT,2);
        break;
    case PM_DISPLAY_FORWARD_PEP:
        m_fPowerTotle = 0;
        m_fTotlePoint = 0;
        SetArcMidTitle("Forward PEP",PM_LAYER_LEFT);
        SetArcMidTitle("Reverse PEP",PM_LAYER_RIGHT);

        setDisplayRectLeft("Forward PEP Watts",PM_LAYER_LEFT,0);
        setDisplayRectLeft("Forward Direct",PM_LAYER_LEFT,1);
        setDisplayRectLeft("Forward Avg",PM_LAYER_LEFT,2);

        setDisplayRectLeft("Reverse PEP Watts",PM_LAYER_RIGHT,0);
        setDisplayRectLeft("Reverse Direct",PM_LAYER_RIGHT,1);
        setDisplayRectLeft("Reverse Avg",PM_LAYER_RIGHT,2);
        break;
    case PM_DISPLAY_FORWARD_CF:

        SetArcMidTitle("Forward CF",PM_LAYER_LEFT);

        setDisplayRectLeft("Forward Avg ",PM_LAYER_LEFT,0);
        setDisplayRectLeft("Forward Direct",PM_LAYER_LEFT,1);
        setDisplayRectLeft("Forward Peak",PM_LAYER_LEFT,2);
        break;
    case PM_DISPLAY_FORWARD_CCDF:

        break;
    case PM_DISPLAY_FORWARD_MODULATION:

        break;
    case PM_DISPLAY_REVERSE_AVERAGE:
        m_fPowerTotle = 0;
        m_fTotlePoint = 0;
        SetArcMidTitle("Reverse Avg",PM_LAYER_RIGHT);
        setDisplayRectLeft("Reverse Avg Watts",PM_LAYER_RIGHT,0);
        setDisplayRectLeft("Reverse Direct",PM_LAYER_RIGHT,1);
        setDisplayRectLeft("Reverse Peak",PM_LAYER_RIGHT,2);
        break;
    case PM_DISPLAY_REVERSE_RC:
        SetArcMidTitle("Reverse RC",PM_LAYER_RIGHT);
        setDisplayRectLeft("Reverse Avg ",PM_LAYER_RIGHT,0);
        setDisplayRectLeft("Reverse Direct",PM_LAYER_RIGHT,1);
        setDisplayRectLeft("Reverse Peak",PM_LAYER_RIGHT,2);
        break;
    case PM_DISPLAY_REVERSE_RL:
        SetArcMidTitle("Reverse RL",PM_LAYER_RIGHT);
        setDisplayRectLeft("Reverse Avg ",PM_LAYER_RIGHT,0);
        setDisplayRectLeft("Reverse Direct",PM_LAYER_RIGHT,1);
        setDisplayRectLeft("Reverse Peak",PM_LAYER_RIGHT,2);
        break;
    case PM_DISPLAY_REVERSE_VSWR:

        SetArcMidTitle("Reverse VSWR",PM_LAYER_RIGHT);
        setDisplayRectLeft("Reverse Avg ",PM_LAYER_RIGHT,0);
        setDisplayRectLeft("Reverse Direct",PM_LAYER_RIGHT,1);
        setDisplayRectLeft("Reverse Peak",PM_LAYER_RIGHT,2);
        break;

    case PM_DISPLAY_V90_POWER:
        SetArcMidTitle("V90 Power Sensor",PM_LAYER_LEFT);
        setDisplayRectLeft("Power Avg ",PM_LAYER_RIGHT,0);
        break;

    case PM_DISPLAY_SUMMARY:
        break;
    default:
        break;
    }

    emit PixmapBottom();
    update();
}

/**
* @brief   设置绘制矩形区域
* @note    int nLeft
* 矩形左边，int nTop 矩形顶点，int nWidth 矩形宽度 ，int nHight 矩形高度
* @author  Roc
* @since   2019.11.7
*/
void BitGaugeDialView::SetDrawRect(int nLeft,int nTop,int nWidth,int nHight)
{
    SetArcAngleLen(150);
    SetArcStartAngle(270 - 150/2);
    SetArcHight(7);

  emit PixmapBottom();
}

/**
* @brief	设置当前采集点编号
* @note
* @Author	ROC
* @date     2020.1.15
*/
void BitGaugeDialView::setCurentSensorData(_PM_SENSOR_DATA sensorData)
{
    qreal fPowerW,fPowerdBm;     //当前仪表盘指针功率值 w mw nw
    char strTemp[20];
    /***** 仪表盘显示数据  显示为从串口中采集到的原始数据 *****/
    m_nPointPowerNum = sensorData.nPointNo;
    m_fTemperature = sensorData.fTempeture;

    //     m_fNowPowerData = fPower;
    showTopWordsMsg(PV_TOP_NOW_DATA);
    switch (m_nDisplayModle) {
    case PM_DISPLAY_FORWARD_AVERAGE:
    case PM_DISPLAY_REVERSE_AVERAGE:
        fPowerdBm = setDisplayLayer(sensorData.fForwardAvemW,PM_LAYER_LEFT);
        fPowerW = dbmToWattsCalculator(strTemp,fPowerdBm,NO_UNIT_INDEX);
        SetArcBottomRight(QString("%1").arg(strTemp),PM_LAYER_LEFT,0 );
        fPowerdBm = setDisplayLayer(sensorData.fReverseAvemW,PM_LAYER_RIGHT);
        fPowerW = dbmToWattsCalculator(strTemp,fPowerdBm,NO_UNIT_INDEX);
        SetArcBottomRight(QString("%1").arg(strTemp),PM_LAYER_RIGHT,0 );
        setDisplayRectRight(sensorData.fForwardDirect,PM_LAYER_LEFT,1);
        setDisplayRectRight(sensorData.fReverseDirect,PM_LAYER_RIGHT,1);
        setDisplayRectRight(sensorData.fForwardPeak,PM_LAYER_LEFT,2);
        setDisplayRectRight(sensorData.fReversePeak,PM_LAYER_RIGHT,2);
        break;
    case PM_DISPLAY_FORWARD_PEP:
       fPowerdBm = setDisplayLayer(sensorData.fForwardPeak,PM_LAYER_LEFT);
        fPowerW = dbmToWattsCalculator(strTemp,fPowerdBm,NO_UNIT_INDEX);
        SetArcBottomRight(QString("%1").arg(strTemp),PM_LAYER_LEFT,0 );
        fPowerdBm = setDisplayLayer(sensorData.fReversePeak,PM_LAYER_RIGHT);
        fPowerW = dbmToWattsCalculator(strTemp,fPowerdBm,NO_UNIT_INDEX);
        SetArcBottomRight(QString("%1").arg(strTemp),PM_LAYER_RIGHT,0 );
        setDisplayRectRight(sensorData.fForwardDirect,PM_LAYER_LEFT,1);
        setDisplayRectRight(sensorData.fReverseDirect,PM_LAYER_RIGHT,1);
        setDisplayRectRight(10*log10(sensorData.fForwardAvemW),PM_LAYER_LEFT,2);
        setDisplayRectRight(10*log10(sensorData.fReverseAvemW),PM_LAYER_RIGHT,2);
        break;
    case PM_DISPLAY_FORWARD_CF:
        showDialData(sensorData.fCrestFactor,"dB",PM_LAYER_LEFT);
        setDisplayRectRight(10*log10(sensorData.fForwardAvemW),PM_LAYER_LEFT,0);
        setDisplayRectRight(sensorData.fForwardDirect,PM_LAYER_LEFT,1);
        setDisplayRectRight(sensorData.fForwardPeak,PM_LAYER_LEFT,2);
        break;
    case PM_DISPLAY_FORWARD_CCDF:
        break;
    case PM_DISPLAY_FORWARD_MODULATION:
        break;
        break;
    case PM_DISPLAY_REVERSE_RC:
        showDialData(sensorData.fReflCoeff,"",PM_LAYER_RIGHT);
        setDisplayRectRight(10*log10(sensorData.fForwardAvemW),PM_LAYER_RIGHT,0);
        setDisplayRectRight(sensorData.fForwardDirect,PM_LAYER_RIGHT,1);
        setDisplayRectRight(sensorData.fForwardPeak,PM_LAYER_RIGHT,2);
        break;
    case PM_DISPLAY_REVERSE_RL:
        showDialData(sensorData.fReturnLoss,"dB",PM_LAYER_RIGHT);
        setDisplayRectRight(10*log10(sensorData.fForwardAvemW),PM_LAYER_RIGHT,0);
        setDisplayRectRight(sensorData.fForwardDirect,PM_LAYER_RIGHT,1);
        setDisplayRectRight(sensorData.fForwardPeak,PM_LAYER_RIGHT,2);
        break;
    case PM_DISPLAY_REVERSE_VSWR:
        showDialData(sensorData.fVSWR,"",PM_LAYER_RIGHT);
        setDisplayRectRight(10*log10(sensorData.fForwardAvemW),PM_LAYER_RIGHT,0);
        setDisplayRectRight(sensorData.fForwardDirect,PM_LAYER_RIGHT,1);
        setDisplayRectRight(sensorData.fForwardPeak,PM_LAYER_RIGHT,2);
        break;
    case PM_DISPLAY_V90_POWER:
        fPowerdBm = setDisplayLayer(sensorData.fPowerDatamW,PM_LAYER_LEFT);
        fPowerW = dbmToWattsCalculator(strTemp,fPowerdBm,NO_UNIT_INDEX);
        SetArcBottomRight(QString("%1").arg(strTemp),PM_LAYER_LEFT,0 );
        break;
    case PM_DISPLAY_SUMMARY:
        m_summayData.gSummayData[0] =  10*log10(sensorData.fForwardAvemW);
        m_summayData.gSummayData[1] =  sensorData.fCrestFactor;
        m_summayData.gSummayData[2] =  0.0;//Calculated Burst Powe
        m_summayData.gSummayData[3] =  sensorData.fForwardPeak;
        m_summayData.gSummayData[4] =  10*log10(sensorData.fReverseAvemW);
        m_summayData.gSummayData[5] =  sensorData.fReflCoeff;
        m_summayData.gSummayData[6] =  sensorData.fReturnLoss;
        m_summayData.gSummayData[7] =  sensorData.fVSWR;
        emit PixmapSummayData();
        break;
    default:
        break;
    }
    emit PixmapThird();
    update();
}

/**
* @brief	设置最大值  框及第一个显示
* @note
* @Author	ROC
* @date     2020.1.19
*/
qreal BitGaugeDialView::setDisplayLayer(qreal fPower,qint32 nLeftOrRight)
{
    qreal fReturndBm;
    fReturndBm = 10*log10(fPower);

    /***** 最大值保持开始 *****/
    showMaxPower(fReturndBm,nLeftOrRight);

    /*****  相对采集数据 *****/
    if(m_bRelativeForward && PM_LAYER_LEFT == nLeftOrRight )
    {
        fReturndBm = fReturndBm - m_fRelativeForward ;
    }
    if(m_bRelativeReverse&& PM_LAYER_RIGHT ==nLeftOrRight)
    {
        fReturndBm = fReturndBm -  m_fRelativeReverse;
    }

    showDialPower(fReturndBm,nLeftOrRight);

    return fReturndBm;
}

void BitGaugeDialView::setDisplayRectLeft(qreal fData,qint32 nLeftOrRight,qint32 nFlg)
{
    qreal fPowerData = fData;
    SetArcBottomLeft(QString("%1 %2").arg(QString::number(fPowerData,'f',2),"dbm"),nLeftOrRight,nFlg);
}

void BitGaugeDialView::setDisplayRectLeft(QString strtext,qint32 nLeftOrRight,qint32 nFlg)
{
    SetArcBottomLeft(strtext,nLeftOrRight,nFlg);
}

void BitGaugeDialView::setDisplayRectRight(qreal fData,qint32 nLeftOrRight,qint32 nFlg)
{
    qreal fPowerData = fData;
    SetArcBottomRight(QString("%1 %2").arg(QString::number(fPowerData,'f',2),"dbm"),nLeftOrRight,nFlg);
}

void BitGaugeDialView::setDisplayRectRight(QString strtext,qint32 nLeftOrRight,qint32 nFlg)
{
    SetArcBottomRight(strtext,nLeftOrRight,nFlg);
}

//            fPowerData = fPower;
//        if(m_bAverageflg)
//        {
//            m_fPowerPointTotle = dBmAdd(m_fPowerPointTotle,fPowerData);
//            qDebug()<<"m_nAveragePoint"<< m_nAveragePoint<<"m_fPowerPointTotle"<<m_fPowerPointTotle<<m_nIndexAverage<<endl;
//            m_nIndexAverage++;
//            if(m_nIndexAverage == m_nAveragePoint)
//            {
//                fPowerData = dBmDiv(m_fPowerPointTotle,m_nIndexAverage);
//                qDebug()<<"m_nAveragePoint"<< m_nAveragePoint<<"m_fPowerPointTotle"<<fPowerData<<endl;
//                m_fPowerPointTotle = 0;
//                m_nIndexAverage = 0;
//            }
//            else
//            {
//                return;
//            }
//        }
//            switch (m_nDisplayModle)
//            {
//            case PM_DISPLAY_FORWARD_AVERAGE:
//            case PM_DISPLAY_REVERSE_AVERAGE:
//                if(m_fTotlePoint == 0)
//                    m_fPowerTotle = fPowerData;
//                else
//                    m_fPowerTotle  = dBmAdd(fPowerData,m_fPowerTotle);
//                m_fTotlePoint++;
//                m_fPowerAverage = dBmDiv(m_fPowerTotle , m_fTotlePoint);
//                SetArcBottomRight(QString("%1 nW").arg(QString::number(m_fPowerAverage,'f',2)),PM_LAYER_LEFT);
//                break;
//            default:
//                break;
//            }
//    }
//}

/**
* @brief	仪表盘显示数据
* @note
* @Author	ROC
* @date     2019.12.25
*/
void BitGaugeDialView::showDialPower(qreal fPower,qint32 nLeftOrRight)
{
    char strLable[20];
    getDataByUnitType(strLable,fPower,DATA_BY_UNIT_INDEX);
    m_layerPixMap[nLeftOrRight].fPowerCurShowdBm = fPower;
    m_layerPixMap[nLeftOrRight].strCurShow = QString(strLable);
}

void BitGaugeDialView::showDialData(qreal fPower,QString strUnit,qint32 nLeftOrRight)
{
    QString strLable = QString::number(fPower,'f',2) + "  " +strUnit;
    m_layerPixMap[nLeftOrRight].strCurShow = QString(strLable);
}

/**
* @brief	最大值保持结束  平均测试时保持未平均之前最大值
* @note
* @Author	ROC
* @date     2019.12.25
*/
void BitGaugeDialView::showMaxPower(qreal fPower,qint32 nLeftOrRight)
{
    if(m_bHoldMax)
    {
        char strLable[20];
        if(fPower < m_fMinPower)
            SetArcTopTitleLeft("Max __.__ dB",nLeftOrRight);
        else if(m_layerPixMap[nLeftOrRight].fPowerMax   < fPower && fPower < m_fMaxPower)
        {
            m_layerPixMap[nLeftOrRight].fPowerMax = fPower;
            getDataByUnitType(strLable,m_layerPixMap[nLeftOrRight].fPowerMax,NO_UNIT_INDEX);
            SetArcTopTitleLeft("Max " + QString(strLable),nLeftOrRight);
        }
        else if(fPower > m_fMaxPower)
            SetArcTopTitleLeft("Max __.__ dB",nLeftOrRight);
    }
    emit PixmapSecond();
}

/**
* @brief	 相对采集数据结束
* @note
* @Author	ROC
* @date     2019.12.25
*/
void BitGaugeDialView::showRelativePower(qreal fPower,qint32 nLeftOrRight)
{
   QString strLable;
    strLable = QString::number(fPower,'f',2) + " dB";
    SetArcTopTitleRight("Relative: " + QString(strLable),nLeftOrRight);
    emit PixmapSecond();
}

void BitGaugeDialView::setFreqOffset(bool bOffset)
{
    m_bOffsetFreq = bOffset;
    emit PixmapFirst();
    update();
}

/**
* @brief	设置显示
* @note
* @Author	ROC
* @date     2020.1.17
*/
void BitGaugeDialView::setHoldMaxPower(bool bHoldMax)
{
    m_bHoldMax = bHoldMax;
    if(false == m_bHoldMax)
    {
        SetArcTopTitleLeft("",PM_LAYER_LEFT);
        SetArcTopTitleLeft("",PM_LAYER_RIGHT);
    }
    else

    {
        SetArcTopTitleLeft("Max __.__ __",PM_LAYER_LEFT);
        SetArcTopTitleLeft("Max __.__ __",PM_LAYER_RIGHT);
        //初始化设置最大值功率点  将最大功率初始设置为最小值加偏移量

        m_layerPixMap[PM_LAYER_LEFT].fPowerMax = m_fMinPower;
        m_layerPixMap[PM_LAYER_RIGHT].fPowerMax = m_fMinPower;
    }

   emit PixmapSecond();
    update();
}


//void BitGaugeDialView::setPowerZero(bool bPowerZero)
//{
//    m_bPowerZero = bPowerZero;
//    m_bPowerZeroCal = bPowerZero;
//    emit PixmapSecond();
//    update();
//}

void BitGaugeDialView::setRelativeForward(bool bRelativeForwrard)
{
    m_bRelativeForward = bRelativeForwrard;
    if(false == m_bRelativeForward)
    {
        SetArcTopTitleRight("",PM_LAYER_LEFT);
    }
    else
    {
        SetArcTopTitleRight("Relative __.__ __",PM_LAYER_LEFT);
    }
    emit PixmapSecond();
    update();
}

void BitGaugeDialView::setRelativeReverse(bool bRelativeReverse)
{
    m_bRelativeReverse = bRelativeReverse;
    if(false == m_bRelativeReverse)
    {
        SetArcTopTitleRight("",PM_LAYER_RIGHT);
    }
    else
    {
        SetArcTopTitleRight("Relative __.__ __",PM_LAYER_RIGHT);
    }
    emit PixmapSecond();
    update();
}

void BitGaugeDialView::setdBmRelativeBaseForward(qreal fdBmRelativeBase)
{
    if(m_bRelativeForward)
    {
        m_fRelativeForward = fdBmRelativeBase;
        showRelativePower(m_fRelativeForward,PM_LAYER_LEFT);
    }
    emit PixmapSecond();
    update();
}

void BitGaugeDialView::setdBmRelativeBaseReverse(qreal fdBmRelativeBase)
{
    if(m_bRelativeReverse)
     {
        m_fRelativeReverse = fdBmRelativeBase;
        showRelativePower(m_fRelativeReverse,PM_LAYER_RIGHT);
    }
    emit PixmapSecond();
    update();
}

void BitGaugeDialView::SetLimitOn(bool bLimtOn)
{
    m_bLimtOn = bLimtOn;
    emit PixmapFirst();
    update();
}

/**
* @brief   设置功率范围上
* @note
* @author  Roc
* @since   2019.11.13
*/
void BitGaugeDialView::SetPowerUpLimit(qreal fLimitUp,qint32 nLeftOrRight)
{
    if( fLimitUp > (m_fMaxPower))
        fLimitUp = m_fMaxPower;

    char strLable[20];
    m_layerPixMap[nLeftOrRight].fdBmLimitUp = fLimitUp;
    m_layerPixMap[nLeftOrRight].fLimitUpDial =  getDataByUnitType(strLable,m_layerPixMap[nLeftOrRight].fdBmLimitUp,DATA_BY_UNIT_INDEX);

    emit PixmapFirst();
    update();
}

/**
* @brief   设置功率范围下
* @note
* @author  Roc
* @since   2019.11.13
*/
void BitGaugeDialView::SetPowerDownLimit(qreal fLimitDown,qint32 nLeftOrRight)
{
    if( fLimitDown < (m_fMinPower))
        fLimitDown = m_fMinPower;

    char strLable[20];
    m_layerPixMap[nLeftOrRight].fdBmLimitDown = fLimitDown;
    m_layerPixMap[nLeftOrRight].fLimitDownDial = getDataByUnitType(strLable,m_layerPixMap[nLeftOrRight].fdBmLimitDown,DATA_BY_UNIT_INDEX);

    emit PixmapFirst();
    update();
}

void BitGaugeDialView::refreshLayerBottom()
{
    m_pixmapLayerBottom.fill(m_PenColor.background);
    QPainter painterBottpm(&m_pixmapLayerBottom);
    painterBottpm.initFrom(this);
    if(PM_DISPLAY_SUMMARY == m_nDisplayModle)
    {
        emit PixmapSummay();
    }
    else if(PM_DISPLAY_FORWARD_CCDF == m_nDisplayModle)
    {
        emit PixmapCCDF();
    }
    else
    {  if(PM_DISPLAY_V90_POWER == m_nDisplayModle)
        {
            m_drawView.drawFrameLines(painterBottpm,CenterPartRect,1,m_PenColor.gridPart);
        }
        else
        {
            m_drawView.drawFrameLines(painterBottpm,CenterPartRect,2,m_PenColor.gridPart);

        }
        emit PixmapFirst();
    }
}

void BitGaugeDialView::refreshLayerFirst()
{
    emit InfoBottom();
    if(PM_DISPLAY_V90_POWER == m_nDisplayModle)
    {
        m_pixmapPower.fill(Qt::transparent);
        drawLayerPixmapOne(m_pixmapPower,m_layerPixMap[PM_LAYER_LEFT]);
    }
    else
    {
        m_pixmapForward.fill(Qt::transparent);
        m_pixmapReverse.fill(Qt::transparent);
        drawLayerPixmap(m_pixmapForward,m_layerPixMap[PM_LAYER_LEFT]);
        drawLayerPixmap(m_pixmapReverse,m_layerPixMap[PM_LAYER_RIGHT]);
    }
    emit PixmapSecond();
    emit PixmapThird();


}

/**
* @brief	在画布上绘制表盘显示 只有一个表盘界面时，如功率探头
* @note
* @Author	ROC
* @date     2020.1.15
*/
void BitGaugeDialView::drawLayerPixmapOne(QPixmap &pixMap,_PM_PIXMAP_LAYER &layerDraw)
{
    QPainter painterLayer(&pixMap);
    painterLayer.initFrom(this);
    //进行锯齿消除，会影响效率
    painterLayer.setRenderHint(QPainter::Antialiasing);

    qint32 nWidth04 =  pixMap.width()*0.4;
    qint32 nHight008 =  pixMap.height()*0.08;
    qint32 nWidth03 = pixMap.width()*0.3;
    qint32 nWidth002 =  pixMap.width()*0.02;
    qint32 nWidth01 =  pixMap.width()*0.1;

    qint32 nhight011 =  pixMap.height()*0.11;

    qint32 nhight053 =  pixMap.height()*0.53;

    qint32 nEditMidTop = nHight008 + nhight053;
    layerDraw.midData = QRect(nWidth03,
                              nEditMidTop,
                              nWidth04,
                              nhight011);

    layerDraw.midLinear = QLinearGradient(nWidth03,
                                          nEditMidTop,
                                          nWidth04,
                                          nEditMidTop + nhight011); //垂直渐变
    layerDraw.midLinear.setColorAt(0,m_PenColor.colMidPart0);
    layerDraw.midLinear.setColorAt(1,m_PenColor.colMidPart1);
    painterLayer.save();
    painterLayer.setBrush(layerDraw.midLinear);
    painterLayer.setPen(Qt::transparent);
    painterLayer.drawRect(layerDraw.midData);
    painterLayer.restore();

    qint32 nWidth05 = pixMap.width()*0.5;
    qint32 nheight65 = pixMap.height()*0.65;
    layerDraw.fRradius = nheight65;

    qint32 nhight083 = pixMap.height()*0.83;

    m_pointArc = QPoint(nWidth05,
                        nhight083);
    //设置绘制坐标原点
    painterLayer.translate(m_pointArc);//设置弧形坐标原点
    //注意顺序，颜色会覆盖
    m_drawView.drawFrame(painterLayer,m_bLimtOn,m_bOffsetFreq,m_fAngleLen,layerDraw.fRradius,m_fArcHeight1,4,
                         m_fMinDial,m_fMaxDial,layerDraw.fLimitUpDial,layerDraw.fLimitDownDial,
                         m_PenColor.colArcLimitMid,m_PenColor.colArcLimtUpOrDown,m_PenColor.colArcOffset,m_PenColor.colorTextTop);
    m_drawView.drawDividing(painterLayer,m_fAngleLen,layerDraw.fRradius,m_fArcHeight1,4,m_PenColor.colorTextTop);//绘制刻度
    m_drawView.drawNumberIndicator(painterLayer,m_fStartAngle,m_fAngleLen,layerDraw.fRradius,m_fArcHeight3,
                                   m_fMinDial,m_fMaxDial,layerDraw.midUnit,layerDraw.strMidUnit,m_PenColor.colorTextDial);//绘制指示数字

    qint32 nTitleUnit= pixMap.height()*0.62;
    qint32 nTitleMid = pixMap.height()*0.52;

    layerDraw.topLeft = QRect(nWidth002,
                              nhight011,
                              nWidth04,
                              nhight011);

    layerDraw.topRight= QRect(nWidth04 + nWidth002,
                              nhight011,
                              nWidth05+nhight011,
                              nhight011);

    layerDraw.midUnit = QRect(0,
                              0,
                              nWidth05,
                              nhight011);

    layerDraw.midTitle = QRect(nWidth01,
                               nTitleMid,
                               nWidth04*2,
                               nhight011);

    int nTempSize = qMax(nhight011*0.5,1.);
    m_fontBottom.setPixelSize(nTempSize);
    nTempSize = qMax(nhight011*0.5,1.);
    m_fontMid.setPixelSize(nTempSize);

    qint32 nhight086 = pixMap.height()*0.86;
    qint32 nhight081 = pixMap.height()*0.81;

    layerDraw.Bottomcolor =  QRect(0, nhight081,pixMap.width(),pixMap.height() - nhight081);
    layerDraw.bottomLeftData[0] = QRect(0,
                                        nhight086,
                                        nWidth04,
                                        nhight011);

    layerDraw.bottomRightData[0] = QRect(nWidth05,
                                         nhight086,
                                         nWidth04,
                                         nhight011);

    layerDraw.bottomLinear = QLinearGradient(nWidth03,
                                             nhight086,
                                             nWidth03,
                                             nhight086 + nhight011); //垂直渐变
}

/**
* @brief	在画布上绘制表盘显示  有俩个表盘，如通过式功率计
* @note
* @Author	ROC
* @date     2020.1.15
*/
void BitGaugeDialView::drawLayerPixmap(QPixmap &pixMap,_PM_PIXMAP_LAYER &layerDraw)
{
    QPainter painterLayer(&pixMap);
    painterLayer.initFrom(this);
    //进行锯齿消除，会影响效率
    painterLayer.setRenderHint(QPainter::Antialiasing);

    qint32 nhight030 =  pixMap.height()*0.30;
    layerDraw.fRradius = nhight030;
    qint32 nWidth04 =  pixMap.width()*0.4;

    qint32 nWidth02 = pixMap.width()*0.2;
    qint32 nWidth03 = pixMap.width()*0.3;
    qint32 nWidth002 =  pixMap.width()*0.02;
    qint32 nWidth01 =  pixMap.width()*0.1;
    qint32 nWidth05 = pixMap.width()*0.5;

//  qint32 nhight045 =  ;
    qint32 nEditMidTop =pixMap.height()*0.53;
    qint32 nhight005 =  pixMap.height()*0.05;

    layerDraw.midData = QRect(nWidth01,
                              nEditMidTop,
                              pixMap.width()-nWidth02,
                              nhight005*2);

    layerDraw.midLinear = QLinearGradient(nWidth01,
                                          nEditMidTop,
                                          pixMap.width()-nWidth02,
                                          nEditMidTop + nhight005*2); //垂直渐变
    layerDraw.midLinear.setColorAt(0,m_PenColor.colMidPart0);
    layerDraw.midLinear.setColorAt(1,m_PenColor.colMidPart1);
    painterLayer.save();
    painterLayer.setBrush(layerDraw.midLinear);
    painterLayer.setPen(Qt::transparent);
    painterLayer.drawRect(layerDraw.midData);
    painterLayer.restore();

    qint32 nhight045 = pixMap.height()*0.45;

    m_pointArc = QPoint(nWidth05,
                      nhight045);
    //设置绘制坐标原点
    painterLayer.translate(m_pointArc);//设置弧形坐标原点
    //注意顺序，颜色会覆盖
    m_drawView.drawFrame(painterLayer,m_bLimtOn,m_bOffsetFreq,m_fAngleLen,layerDraw.fRradius,m_fArcHeight1,2,
                         m_fMinDial,m_fMaxDial,layerDraw.fLimitUpDial,layerDraw.fLimitDownDial,
                         m_PenColor.colArcLimitMid,m_PenColor.colArcLimtUpOrDown,m_PenColor.colArcOffset,m_PenColor.colorTextTop);
    m_drawView.drawDividing(painterLayer,m_fAngleLen,layerDraw.fRradius,m_fArcHeight1,2,m_PenColor.colorTextTop);//绘制刻度
    m_drawView.drawNumberIndicator(painterLayer,m_fStartAngle,m_fAngleLen,layerDraw.fRradius,m_fArcHeight3,
                                   m_fMinDial,m_fMaxDial,layerDraw.midUnit,layerDraw.strMidUnit,m_PenColor.colorTextDial);//绘制指示数字

    qint32 nTitleMid = pixMap.height()*0.42;

    qint32 nhight001 = pixMap.height()*0.015;
    qint32 nhight007 = pixMap.height()*0.075;

    layerDraw.topLeft = QRect(nWidth002,
                              nhight001,
                              nWidth04,
                              nhight007);

    layerDraw.topRight= QRect(nWidth04 + nWidth002,
                              nhight001,
                              nWidth05+nhight005,
                              nhight007);

    layerDraw.midUnit = QRect(0,
                              0,
                              nWidth05,
                              nhight007);

    layerDraw.midTitle = QRect(0,
                               nTitleMid,
                               pixMap.width(),
                               nhight005*2);

    int nTempSize = qMax(nhight005*0.5,1.);
    m_fontBottom.setPixelSize(nTempSize);
    nTempSize = qMax(nhight005,1);
    m_fontMid.setPixelSize(nTempSize);

    qint32 nhight07 = pixMap.height()*0.7;
    qint32 nhight068 = pixMap.height()*0.68;


    qint32 nhight15 = pixMap.height()*0.15;
    qint32 nhight23 = pixMap.height()*0.23;

    qint32 nhight053 = pixMap.height()*0.53;
    qint32 nhight05 = pixMap.height()*0.5;
    layerDraw.Bottomcolor =  QRect(PM_HALFLINEREEOR, nhight07,pixMap.width()- PM_HALFLINEREEOR,pixMap.height() - nhight07);
    layerDraw.bottomLeftData[0] = QRect(0,
                                        nhight068+nhight007,
                                        nWidth04,
                                        nhight005);
    layerDraw.bottomRightData[0] = QRect(nWidth05,
                                         nhight068+nhight007,
                                         nWidth04,
                                         nhight005);
    layerDraw.bottomLeftData[1] = QRect(0,
                                        nhight068+nhight15,
                                        nWidth04,
                                        nhight005);
    layerDraw.bottomRightData[1] = QRect(nWidth05,
                                         nhight068+nhight15,
                                         nWidth04,
                                         nhight005);
    layerDraw.bottomLeftData[2] = QRect(0,
                                        nhight068 + nhight23,
                                        nWidth04,
                                        nhight005);
    layerDraw.bottomRightData[2] = QRect(nWidth05,
                                         nhight068+nhight23,
                                         nWidth04,
                                         nhight005);

    layerDraw.bottomLinear = QLinearGradient(nWidth03,
                                             nhight053+nhight001,
                                             nWidth03,
                                             nhight05); //垂直渐变
}

void BitGaugeDialView::refreshLayerSecond()
{
    if(PM_DISPLAY_V90_POWER == m_nDisplayModle)
    {
        m_pixmapPowerTitle.fill(Qt::transparent);
        drawLayerTitle(m_pixmapPowerTitle,m_layerPixMap[PM_LAYER_LEFT]);
    }
    else
    {
        m_pixForwardTitle.fill(Qt::transparent);
        m_pixReverseTitle.fill(Qt::transparent);
        drawLayerTitle(m_pixForwardTitle,m_layerPixMap[PM_LAYER_LEFT]);
        drawLayerTitle(m_pixReverseTitle,m_layerPixMap[PM_LAYER_RIGHT]);
    }
    //设置绘制坐标原点
    //    painterThird.translate(m_pointArc);//设置弧形坐标原点
}

void BitGaugeDialView::drawLayerTitle(QPixmap &pixMap,_PM_PIXMAP_LAYER &layerDraw)
{
    QPainter painterTitle(&pixMap);
    painterTitle.initFrom(this);
    m_drawView.drawTitle(painterTitle,layerDraw.topLeft,layerDraw.topRight,layerDraw.midTitle,
                         layerDraw.strTopTitleLeft,layerDraw.strTopTitleRight,layerDraw.strMidTitle,
                         m_PenColor.colorTextTitle,m_PenColor.colorTextTopTitle);//显示标题
}

void BitGaugeDialView::refreshLayerThird()
{
    emit InfoTop();
    if(PM_DISPLAY_V90_POWER == m_nDisplayModle)
    {
       m_pixmapPowerData.fill(Qt::transparent);
        drawLayerData(m_pixmapPowerData,m_layerPixMap[PM_LAYER_LEFT]);
    }
    else
    {
        m_pixForwardData.fill(Qt::transparent);
        m_pixReverseData.fill(Qt::transparent);
        drawLayerData(m_pixForwardData,m_layerPixMap[PM_LAYER_LEFT]);
        drawLayerData(m_pixReverseData,m_layerPixMap[PM_LAYER_RIGHT]);
    }

}

void BitGaugeDialView::drawLayerData(QPixmap &pixMap,_PM_PIXMAP_LAYER &layerDraw)
{
    QPainter painterData(&pixMap);
    painterData.initFrom(this);
    m_drawView.drawBottomRect(painterData,m_bLimtOn,m_bOffsetFreq,layerDraw.fPowerCurShowdBm,
                              layerDraw.fdBmLimitUp,layerDraw.fdBmLimitDown,
                              layerDraw.Bottomcolor,layerDraw.bottomLinear,
                              m_PenColor.colbottomLimitMid,m_PenColor.colbottomLimtUpOrDown,m_PenColor.colbottomOffset,
                              m_PenColor.colbottomLimit0,m_PenColor.colbottomLimit1,m_PenColor.colbottomoffset0,m_PenColor.colbottomoffset1,
                              m_PenColor.colbottomMid0,m_PenColor.colbottomMid1);

    m_drawView.drawBottomData(painterData,layerDraw.bottomLinear,
                              layerDraw.bottomLeftData[0],layerDraw.bottomRightData[0],
            layerDraw.strBottomLeft[0],layerDraw.strBottomRight[0],
            m_fontBottom, m_PenColor.colorTextBottom);

    if(PM_DISPLAY_V90_POWER != m_nDisplayModle)
    {
        m_drawView.drawBottomData(painterData,layerDraw.bottomLinear,
                                  layerDraw.bottomLeftData[1],layerDraw.bottomRightData[1],
                layerDraw.strBottomLeft[1],layerDraw.strBottomRight[1],
                m_fontBottom, m_PenColor.colorTextBottom);

        m_drawView.drawBottomData(painterData,layerDraw.bottomLinear,
                                  layerDraw.bottomLeftData[2],layerDraw.bottomRightData[2],
                layerDraw.strBottomLeft[2],layerDraw.strBottomRight[2],
                m_fontBottom, m_PenColor.colorTextBottom);

    }

    painterData.save();
    painterData.setFont(m_fontMid);
    painterData.setPen(m_PenColor.colorTextMidData);
    painterData.drawText(layerDraw.midData,Qt::AlignCenter,layerDraw.strCurShow);
    painterData.restore();
    //设置绘制坐标原点
    painterData.translate(m_pointArc);//设置弧形坐标原点
        QPointF points[4] = {
            QPointF(layerDraw.fRradius - m_fArcHeight6, 0),
            QPointF(layerDraw.fRradius - m_fArcHeight10, m_fArcHeight1),
            QPointF(layerDraw.fRradius - m_fArcHeight9, 0),
            QPointF(layerDraw.fRradius - m_fArcHeight10, -m_fArcHeight1),
        };
        m_drawView.drawIndicator(painterData,points,
                                 layerDraw.fPowerCurShowdBm,m_fMinPower,m_fMaxPower,m_fStartAngle,m_fAngleLen,
                                 m_PenColor.colIndicator1,m_PenColor.colIndicator2,m_PenColor.curTraceIndex);//绘制速度指针
}

void BitGaugeDialView::refreshLayerCCDF()
{
    m_pixmapLayerSummay.fill(Qt::transparent);

    QPainter painterSummay(&m_pixmapLayerSummay);
    painterSummay.initFrom(this);
    QRect rectCCDF =CenterPartRect;

}

void BitGaugeDialView::refreshLayerSummay()
{
    m_pixmapLayerSummay.fill(Qt::transparent);

    QPainter painterSummay(&m_pixmapLayerSummay);
    painterSummay.initFrom(this);
   QRect rectSummay =CenterPartRect;
    m_drawView.drawGridString(painterSummay,rectSummay,m_summayData,m_PenColor.colSummay1,m_PenColor.colSummay2,m_PenColor.colSummay3);

}

void BitGaugeDialView::refreshInfoBottom()
{
    m_pixmapBottomInfo.fill(Qt::transparent);
    QPainter painterBottom(&m_pixmapBottomInfo);
    painterBottom.initFrom(this);

    m_drawView.drawBottomPart(painterBottom,m_wordset,CenterPartRect,m_PenColor.colorTextTop);
}

void BitGaugeDialView::refreshInfoTop()
{
    m_pixmapTopInfo.fill(Qt::transparent);
    QPainter painterTop(&m_pixmapTopInfo);
    painterTop.initFrom(this);

    m_drawView.drawTopPart(painterTop,m_wordset,CenterPartRect,m_PenColor.colorTextTop);
}

/**
* @brief   设置弧形起始角度
* @note
* @author  Roc
* @since   2019.11.7
*/
void BitGaugeDialView::SetArcStartAngle(qreal fStartAngle)
{
    m_fStartAngle = fStartAngle;
    update();
}

/**
* @brief   设置弧形长度角度
* @note
* @author  Roc
* @since   2019.11.7
*/
void BitGaugeDialView::SetArcAngleLen(qreal fAngleLen)
{
    m_fAngleLen = fAngleLen;
    update();
}

/**
* @brief   设置数据单位
* @note
* @author  Roc
* @since   2019.11.7
*/
void BitGaugeDialView::SetArcUnit(qint32 nUnit)
{
    m_nUnitType = nUnit;
    SetArcMaxMin(m_fMaxPower,m_fMinPower);
    emit PixmapFirst();
    update();
}

/**
* @brief   设置数据起点
* @note    由于绘制刻度，为真实值×10
* @author  Roc
* @since   2019.11.7
*/
void BitGaugeDialView::SetMinPower(qreal fMinPower)
{
    m_fMinPower = fMinPower;
    if(m_fMaxPower <= m_fMinPower)
        m_fMaxPower = m_fMinPower+1;
    SetArcMaxMin(m_fMaxPower,m_fMinPower);
    update();
}

/**
* @brief   设置数据终点
* @note
* @author  Roc
* @since   2019.11.7
*/
void BitGaugeDialView::SetMaxPower(qreal fMaxPower)
{
    m_fMaxPower = fMaxPower;
    if(m_fMaxPower <= m_fMinPower)
        m_fMinPower = m_fMaxPower-1;
    SetArcMaxMin(m_fMaxPower,m_fMinPower);
    update();
}

void  BitGaugeDialView::SetArcMaxMin(qreal fMax,qreal fMin)
{
    char strLable[20];
    m_fMinDial = getDataByUnitType(strLable,fMin ,SET_UNIT_INDEX);
    m_fMaxDial = getDataByUnitType(strLable,fMax ,DATA_BY_UNIT_INDEX);
    m_layerPixMap[PM_LAYER_LEFT].strMidUnit = getUnitString(m_nUnitIndex);
    m_layerPixMap[PM_LAYER_RIGHT].strMidUnit = getUnitString(m_nUnitIndex);

    if(m_bLimtOn)
    {
        SetPowerUpLimit(m_layerPixMap[PM_LAYER_LEFT].fdBmLimitUp,true);
        SetPowerDownLimit(m_layerPixMap[PM_LAYER_LEFT].fdBmLimitDown,true);
        SetPowerUpLimit(m_layerPixMap[PM_LAYER_RIGHT].fdBmLimitUp,false);
        SetPowerDownLimit(m_layerPixMap[PM_LAYER_RIGHT].fdBmLimitDown,false);
    }
    emit PixmapFirst();
}

/**
* @brief   设置上数据左标题
* @note
* @author  Roc
* @since   2019.11.7
*/
void BitGaugeDialView::SetArcTopTitleLeft(QString strTopTitleLeft,qint32 nLeftOrRight)
{
    m_layerPixMap[nLeftOrRight].strTopTitleLeft = strTopTitleLeft;
//    emit PixmapSecond();
//    update();
}

/**
* @brief   设置上数据you标题
* @note
* @author  Roc
* @since   2019.11.7
*/
void BitGaugeDialView::SetArcTopTitleRight(QString strTopTitleRight,qint32 nLeftOrRight)
{
    m_layerPixMap[nLeftOrRight].strTopTitleRight = strTopTitleRight;
    emit PixmapSecond();
    update();
}

/**
* @brief   设置数据标题
* @note
* @author  Roc
* @since   2019.11.7
*/
void BitGaugeDialView::SetArcMidTitle(QString strMidTitle,qint32 nLeftOrRight)
{
    m_layerPixMap[nLeftOrRight].strMidTitle = strMidTitle;
    emit PixmapFirst();
    update();
}

/**
* @brief   设置底部左标题
* @note
* @author  Roc
* @since   2019.11.7
*/
void BitGaugeDialView::SetArcBottomLeft(QString strBottomLeft,qint32 nLeftOrRight,qint32 nNo)
{
    m_layerPixMap[nLeftOrRight].strBottomLeft[nNo]  = strBottomLeft;
    update();
}

/**
* @brief   设置底部右标题
* @note
* @author  Roc
* @since   2019.11.7
*/
void BitGaugeDialView::SetArcBottomRight(QString strBottomRight,qint32 nLeftOrRight,qint32 nNo)
{
        m_layerPixMap[nLeftOrRight].strBottomRight[nNo] = strBottomRight;
    update();
}

void BitGaugeDialView::SetArcWaring(QString strWaring)
{
    m_strWaring= strWaring;
    update();

}

void BitGaugeDialView::setFreqAttribute(quint32 attributeType, qreal attribute)
{
    switch (attributeType)
    {
    case PM_BIT_START_FREQ:
        m_freqinfo.gstartfreq = attribute;
        break;
    case PM_BIT_STOP_FREQ:
        m_freqinfo.gstopfreq = attribute;
        break;
    case PM_BIT_CENTER_FREQ:
        m_freqinfo.gcenterfreq = attribute;
        break;
    case PM_BIT_OFFSET_FREQ:
        m_freqinfo.gfreqoffset = attribute ;
        break;
    case PM_BIT_SPAN_FREQ:
        m_freqinfo.gspanfreq = attribute ;
        break;
    default:
        break;
    }
    update();
    return ;
}

qreal BitGaugeDialView::getFreqAttribute(quint32 attributeType)
{
    qreal attribute = 0;
    switch (attributeType)
    {
    case PM_BIT_START_FREQ:
        attribute = m_freqinfo.gstartfreq;
        break;
    case PM_BIT_STOP_FREQ:
        attribute = m_freqinfo.gstopfreq;
        break;
    case PM_BIT_CENTER_FREQ:
        attribute = m_freqinfo.gcenterfreq;
        break;
    case PM_BIT_SPAN_FREQ:
        attribute = m_freqinfo.gspanfreq;
        break;
    default:
        break;
    }
    return attribute;
}

/**
* @brief   设置弧形形状宽度
* @note
* @author  Roc
* @since   2019.11.7
*/
void BitGaugeDialView::SetArcHight(qreal fArcHight)
{
    m_fArcHeight1 = fArcHight;
    m_fArcHeight2 = 2*m_fArcHeight1;
    m_fArcHeight3 = 3*m_fArcHeight1;
    m_fArcHeight4 = 4*m_fArcHeight1;
    m_fArcHeight6 = 6* m_fArcHeight1;
    m_fArcHeight9 = 9*m_fArcHeight1;
    m_fArcHeight10 = 10*m_fArcHeight1;
    update();
}

/**
* @brief 显示模式
* @note
* @author Roc
* @since  2019.11.10
*/
void BitGaugeDialView::setdisplaymode(qint32 displaymode)
{
    m_PenColor   = PmPenColor[displaymode];
    m_BoardColor = PmBoardColor[displaymode];

    m_penBoarder.setColor(m_BoardColor.curBoardLine);
   produceColorBar(displaymode);

   setDisplayModle(m_nDisplayModle);

    return ;
}

void BitGaugeDialView::produceColorBar(qint32 displaymode)
{
    quint32 uColorValue = 0xff000000;
    qint32 uRValue     = 0;
    qint32 uGValue     = 0;
    qint32 uBValue     = 0xff;
    qint32 uColorLevel = 255;
    float dcurveValue = 1.;

    qint32 value_Average = qRound((qreal)255*4/uColorLevel);

    if(displaymode == PM_BIT_OUTDOORMODE)
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
//            rgbBuffer[SPECTROGRAM_COLBAR_NUM - i - 1] = uColorValue;
        }
    }
    else if(displaymode == PM_BIT_NIGHTMODE)
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
//            rgbBuffer[SPECTROGRAM_COLBAR_NUM - i - 1] = uColorValue;
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
//            rgbBuffer[SPECTROGRAM_COLBAR_NUM - i - 1] = uColorValue;
        }
    }
    return;
}

/**
* @brief	设置单位
* @note
* @author	Roc
* @since	2019.11.13
*/
QString BitGaugeDialView::getUnitString(int nUnitIndex)
{
    QString strUnit = "";
    switch (nUnitIndex)
    {
    case UNIT_DBM:
        strUnit = "dBm";
        break;
    case UNIT_DBV:
        strUnit = "dBv";
        break;
    case UNIT_DBMV:
        strUnit = "dBmV";
        break;
    case UNIT_DBUV:
        strUnit = "dBuV";
        break;
    case UNIT_W:
        strUnit = "W";
        break;
    case UNIT_mW:
        strUnit = "mW";
        break;
    case UNIT_uW:
        strUnit = "uW";
        break;
    case UNIT_nW:
        strUnit = "nW";
        break;
    case UNIT_pW:
        strUnit = "pW";
        break;
    case UNIT_fW:
        strUnit = "fW";
        break;
    case UNIT_aW:
        strUnit = "aW";
        break;
    case UNIT_V:
        strUnit = "V";
        break;
    case UNIT_mV:
        strUnit = "mV";
        break;
    case UNIT_uV:
        strUnit = "uV";
        break;
    case UNIT_nV:
        strUnit = "nV";
        break;
    case UNIT_pV:
        strUnit = "pV";
        break;
    case UNIT_fV:
        strUnit = "fV";
        break;
    case UNIT_aV:
        strUnit = "aV";
        break;
    case UNIT_zV:
        strUnit = "zV";
        break;
    case UNIT_yV:
        strUnit = "yV";
        break;
    default:
        break;

    }
    return strUnit;
}

/**
* @brief	通过dBm根据单位得到数据
* @note
* @author	Roc
* @since	2019.11.13
*/
qreal BitGaugeDialView::getDataByUnitType(char *label,qreal fdBmPower,qint32 nUnitIndexFlg)
{
    qreal fReturnData;
    if(SET_UNIT_INDEX == nUnitIndexFlg)
    {
        switch (m_nUnitType)
        {
        case PM_BIT_DBM:
            fReturnData = fdBmPower;
            sprintf(label, "%.2f dBm", fReturnData);
            m_nUnitIndex = UNIT_DBM;
            break;
        case PM_BIT_DBV:
            fReturnData = fdBmPower + PM_dBVFix;
            sprintf(label, "%.2f dBv", fReturnData);
            m_nUnitIndex = UNIT_DBV;
            break;
        case PM_BIT_DBMV:
            fReturnData = fdBmPower + PM_dBmVFix;
            sprintf(label, "%.2f dBmV", fReturnData);
            m_nUnitIndex = UNIT_DBMV;
            break;
        case PM_BIT_DBUV:
            fReturnData = fdBmPower + PM_dBuVFix;
            sprintf(label, "%.2f dBuV", fReturnData);
            m_nUnitIndex = UNIT_DBUV;
            break;
        case PM_BIT_VOLT:
            fReturnData =  dbmToVoltCalculator(label,fdBmPower,nUnitIndexFlg);
            break;
        case PM_BIT_WATTS:
            fReturnData = dbmToWattsCalculator(label,fdBmPower,nUnitIndexFlg);

            break;
        default:
            break;
        }
    }
    else
    {
        switch (m_nUnitType)
        {
        case PM_BIT_DBM:
            fReturnData = fdBmPower;
            sprintf(label, "%.2f dBm", fReturnData);
            break;
        case PM_BIT_DBV:
            fReturnData = fdBmPower + PM_dBVFix;
            sprintf(label, "%.2f dBv", fReturnData);
            break;
        case PM_BIT_DBMV:
            fReturnData = fdBmPower + PM_dBmVFix;
            sprintf(label, "%.2f dBmV", fReturnData);
            break;
        case PM_BIT_DBUV:
            fReturnData = fdBmPower + PM_dBuVFix;
            sprintf(label, "%.2f dBuV", fReturnData);
            break;
        case PM_BIT_VOLT:
            fReturnData =  dbmToVoltCalculator(label,fdBmPower,nUnitIndexFlg);
            break;
        case PM_BIT_WATTS:
            fReturnData = dbmToWattsCalculator(label,fdBmPower,nUnitIndexFlg);

            break;
        default:
            break;
        }
    }
    return fReturnData;
}

/**
* @brief	dBm转换为Volt
* @note
* @author	Roc
* @since	2019.11.13
*/
qreal BitGaugeDialView::dbmToVoltCalculator(char *label,qreal _level, qint32 nUnitIndexFlg)
{
    qreal voltGab = 0.;
    qreal calculator = 0.;

    calculator = pow(10, _level* 0.1);
    voltGab = 1000000. * pow(50 * calculator * 0.001, 0.5);//uv

     if(NO_UNIT_INDEX == nUnitIndexFlg)
    {
        if(voltGab >= 1000000000.)     {                     //kV
            voltGab = (qreal) voltGab *0.000000001;
            sprintf(label, "%.2f kV", voltGab);
        }
        else if (voltGab >= 1000000.)  {                     //V
            voltGab =  (qreal) voltGab *0.000001;
            sprintf(label, "%.2f V", voltGab);
        } else if (voltGab < 1000000.) {                    //mV
            voltGab =  (qreal) voltGab *0.001;
            sprintf(label, "%.2f mV", voltGab);
        } else if (voltGab < 1000.) {                       //uV
            voltGab =  (qreal) voltGab;
            sprintf(label, "%.2f uV", voltGab);
        } else if (voltGab < 1.) {                          //nV
            voltGab =  (qreal) voltGab * 1000;
            sprintf(label, "%.2f nV", voltGab);
        } else if (voltGab < 0.001 && voltGab >= 0.000001) {//pV
            voltGab =  (qreal) voltGab * 1000000.;
            sprintf(label, "%.2f pV", voltGab);
        } else if (voltGab < 0.000001 && voltGab >= 0.000000001) { //fV
            voltGab =  (qreal) voltGab * 1000000000.;
            sprintf(label, "%.2f fV", voltGab);
        } else if (voltGab < 0.000000001 && voltGab >= 0.000000000001) {//aV
            voltGab =  (qreal) voltGab * 1000000000000.;
            sprintf(label, "%.2f aV", voltGab);
        } else if (voltGab < 0.000000000001 && voltGab >= 0.000000000000001) {//zV
            voltGab =  (qreal) voltGab * 1000000000000000.;
            sprintf(label, "%.2f zV", voltGab);
        } else if (voltGab < 0.000000000000001 && voltGab >= 0.000000000000000001) {//yV
            voltGab =  (qreal) voltGab * 1000000000000000000.;
            sprintf(label, "%.2f yV", voltGab);
        } else {
            voltGab =  (qreal) voltGab * 1000000000000000000000.;
            sprintf(label, "%.2f ", voltGab);
        }
    }
    else if(SET_UNIT_INDEX == nUnitIndexFlg)
    {
        if(voltGab >= 1000000000.)     {                     //kV
            voltGab = (qreal) voltGab *0.000000001;
            sprintf(label, "%.2f kV", voltGab);
            m_nUnitIndex = UNIT_kV;
        }
        else if (voltGab >= 1000000.)  {                     //V
            voltGab =  (qreal) voltGab *0.000001;
            sprintf(label, "%.2f V", voltGab);
            m_nUnitIndex = UNIT_V;
        } else if (voltGab < 1000000.) {                    //mV
            voltGab =  (qreal) voltGab *0.001;
            sprintf(label, "%.2f mV", voltGab);
            m_nUnitIndex = UNIT_mV;
        } else if (voltGab < 1000.) {                       //uV
            voltGab =  (qreal) voltGab;
            sprintf(label, "%.2f uV", voltGab);
            m_nUnitIndex = UNIT_uV;
        } else if (voltGab < 1.) {                          //nV
            voltGab =  (qreal) voltGab * 1000;
            sprintf(label, "%.2f nV", voltGab);
            m_nUnitIndex = UNIT_nV;
        } else if (voltGab < 0.001 && voltGab >= 0.000001) {//pV
            voltGab =  (qreal) voltGab * 1000000.;
            sprintf(label, "%.2f pV", voltGab);
            m_nUnitIndex = UNIT_pV;
        } else if (voltGab < 0.000001 && voltGab >= 0.000000001) { //fV
            voltGab =  (qreal) voltGab * 1000000000.;
            sprintf(label, "%.2f fV", voltGab);
            m_nUnitIndex = UNIT_fV;
        } else if (voltGab < 0.000000001 && voltGab >= 0.000000000001) {//aV
            voltGab =  (qreal) voltGab * 1000000000000.;
            sprintf(label, "%.2f aV", voltGab);
            m_nUnitIndex = UNIT_aV;
        } else if (voltGab < 0.000000000001 && voltGab >= 0.000000000000001) {//zV
            voltGab =  (qreal) voltGab * 1000000000000000.;
            sprintf(label, "%.2f zV", voltGab);
            m_nUnitIndex = UNIT_zV;
        } else if (voltGab < 0.000000000000001 && voltGab >= 0.000000000000000001) {//yV
            voltGab =  (qreal) voltGab * 1000000000000000000.;
            sprintf(label, "%.2f yV", voltGab);
            m_nUnitIndex = UNIT_yV;
        } else {
            voltGab =  (qreal) voltGab * 1000000000000000000000.;
            sprintf(label, "%.2f ", voltGab);
        }
    }
    else if(DATA_BY_UNIT_INDEX == nUnitIndexFlg)
    {
        if(UNIT_kV == m_nUnitIndex){
            voltGab = (qreal) voltGab *0.000000001;
            sprintf(label, "%.2f kV", voltGab);
        }
        else if (UNIT_V == m_nUnitIndex) {
            voltGab =  (qreal) voltGab *0.000001;
            sprintf(label, "%.2f V", voltGab);
        } else if (UNIT_mV == m_nUnitIndex) {
            voltGab =  (qreal) voltGab *0.001;
            sprintf(label, "%.2f mV", voltGab);
        } else if (UNIT_uV == m_nUnitIndex) {
            voltGab =  (qreal) voltGab;
            sprintf(label, "%.2f uV", voltGab);
        } else if (UNIT_nV == m_nUnitIndex) {
            voltGab =  (qreal) voltGab * 1000;
            sprintf(label, "%.2f nV", voltGab);
        } else if (UNIT_pV == m_nUnitIndex) {
            voltGab =  (qreal) voltGab * 1000000.;
            sprintf(label, "%.2f pV", voltGab);
        } else if (UNIT_fV == m_nUnitIndex) {
            voltGab =  (qreal) voltGab * 1000000000.;
            sprintf(label, "%.2f fV", voltGab);
        } else if (UNIT_aV == m_nUnitIndex) {
            voltGab =  (qreal) voltGab * 1000000000000.;
            sprintf(label, "%.2f aV", voltGab);
        } else if (UNIT_zV == m_nUnitIndex) {
            voltGab =  (qreal) voltGab * 1000000000000000.;
            sprintf(label, "%.2f zV", voltGab);
        } else if (UNIT_yV == m_nUnitIndex) {
            voltGab =  (qreal) voltGab * 1000000000000000000.;
            sprintf(label, "%.2f yV", voltGab);
        } else {
            voltGab =  (qreal) voltGab * 1000000000000000000000.;
            sprintf(label, "%.2f ", voltGab);
        }
    }
    return voltGab;
}

/**
* @brief	dBm转换为Waatts
* @note
* @author	Roc
* @since	2019.11.13
*/
qreal BitGaugeDialView::dbmToWattsCalculator(char *label,qreal _level, qint32 nUnitIndexFlg)
{
    qreal wattsGab = 0.;
    wattsGab = pow(10, _level*0.1);

    if(NO_UNIT_INDEX == nUnitIndexFlg)
    {
        if (wattsGab >= 1000) {						    // W
            wattsGab = (qreal)wattsGab * 0.001;
            sprintf(label, "%.2f W", wattsGab);
        }  else if (wattsGab >= 1) {					// mW
            wattsGab = (qreal)wattsGab;
            sprintf(label, "%.2f mW", wattsGab);
        }  else if (wattsGab >= 0.001) {				// uW
            wattsGab = (qreal)wattsGab * 1000.0;
            sprintf(label, "%.2f uW", wattsGab);
        }  else if (wattsGab >= 0.000001) {			    // nW
            wattsGab = (qreal)wattsGab * 1000000.0;
            sprintf(label, "%.2f nW", wattsGab);
        } else if (wattsGab >= 0.000000001){			// pW
            wattsGab = (qreal)wattsGab * 1000000000.0;
            sprintf(label, "%.2f pW", wattsGab);
        } else if (wattsGab >= 0.000000000001) {		// fW
            wattsGab = (qreal)wattsGab * 1000000000000.0;
            sprintf(label, "%.2f fW", wattsGab);
        } else {                                        // aW
            wattsGab = (qreal)wattsGab * 1000000000000000.0;
            sprintf(label, "%.2f aW", wattsGab);
        }
    }
    else if(SET_UNIT_INDEX == nUnitIndexFlg)
    {
        if (wattsGab >= 1000) {						    // W
            wattsGab = (qreal)wattsGab *0.001;
            sprintf(label, "%.2f W", wattsGab);
            m_nUnitIndex = UNIT_W;
        }  else if (wattsGab >= 1) {					// mW
            wattsGab = (qreal)wattsGab;
            sprintf(label, "%.2f mW", wattsGab);
            m_nUnitIndex = UNIT_mW;
        }  else if (wattsGab >= 0.001) {				// uW
            wattsGab = (qreal)wattsGab * 1000.0;
            sprintf(label, "%.2f uW", wattsGab);
            m_nUnitIndex = UNIT_uW;
        }  else if (wattsGab >= 0.000001) {			    // nW
            wattsGab = (qreal)wattsGab * 1000000.0;
            sprintf(label, "%.2f nW", wattsGab);
            m_nUnitIndex = UNIT_nW;
        } else if (wattsGab >= 0.000000001){			// pW
            wattsGab = (qreal)wattsGab * 1000000000.0;
            sprintf(label, "%.2f pW", wattsGab);
            m_nUnitIndex = UNIT_pW;
        } else if (wattsGab >= 0.000000000001) {		// fW
            wattsGab = (qreal)wattsGab * 1000000000000.0;
            sprintf(label, "%.2f fW", wattsGab);
            m_nUnitIndex = UNIT_fW;
        } else {                                        // aW
            wattsGab = (qreal)wattsGab * 1000000000000000.0;
            sprintf(label, "%.2f aW", wattsGab);
            m_nUnitIndex = UNIT_aW;
        }
    }
    else if(DATA_BY_UNIT_INDEX == nUnitIndexFlg)
    {
        if (UNIT_W == m_nUnitIndex) {                           // W
            wattsGab = (qreal)wattsGab *0.001;
            sprintf(label, "%.2f W", wattsGab);
        }  else if (UNIT_mW == m_nUnitIndex) {                  // mW
            wattsGab = (qreal)wattsGab;
            sprintf(label, "%.2f mW", wattsGab);
        }  else if (UNIT_uW == m_nUnitIndex) {                   // uW
            wattsGab = (qreal)wattsGab * 1000.0;
            sprintf(label, "%.2f uW", wattsGab);
        }  else if (UNIT_nW == m_nUnitIndex) {                   // nW
            wattsGab = (qreal)wattsGab * 1000000.0;
            sprintf(label, "%.2f nW", wattsGab);
        }  else if (UNIT_pW == m_nUnitIndex){                    // pW
            wattsGab = (qreal)wattsGab * 1000000000.0;
            sprintf(label, "%.2f pW", wattsGab);
        }  else if (UNIT_fW == m_nUnitIndex) {                   // fW
            wattsGab = (qreal)wattsGab * 1000000000000.0;
            sprintf(label, "%.2f fW", wattsGab);
        }  else {                                                // aW
            wattsGab = (qreal)wattsGab * 1000000000000000.0;
            sprintf(label, "%.2f aW", wattsGab);
        }
    }

    return wattsGab;
}

qreal BitGaugeDialView::dBmAdd(qreal _level1,qreal _level2)
{
    qreal returnDbm;
    returnDbm = 10*log10((pow(10, _level1 *0.1) + pow(10, _level2 *0.1)));
    return returnDbm;
}

qreal BitGaugeDialView::dBmSub(qreal _level1,qreal _level2)
{
    qreal returnDbm;
    returnDbm = 10*log10((pow(10, _level1 *0.1) - pow(10, _level2 *0.1)));
    return returnDbm;
}

qreal BitGaugeDialView::dBmDiv(qreal _level1,qreal _Point)
{
    qreal returnDbm;
    returnDbm = 10*log10((pow(10, _level1 *0.1) /_Point));
    return returnDbm;
}

qint32 BitGaugeDialView::freqUnitFindProc(qreal freq)
{
    if (freq >= PV_GHZ)
        return PV_UNIT_GHZ;
    else if (freq >= PV_MHZ)
        return PV_UNIT_MHZ;
    else if (freq >= PV_KHZ)
        return PV_UNIT_KHZ;
    else
        return PV_UNIT_HZ;
}

qint32 BitGaugeDialView::freqnotZeroPosition(qreal freq)
{
    qint32 remainder=0;
    qint32 pos=0;
    if(freq <= 0)
        return 0;
    while(0 == remainder)
    {
        ++pos;
        remainder = (qint32)freq%10;
        freq = freq*0.1;
    }
    return (pos-1);
}

QString BitGaugeDialView::freqValueToQstring(qreal freq)
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
    case PV_UNIT_GHZ:
        unitStr=" GHz";
        if(9<=zeronum)
        {
            freqValue=QString::number((qreal)freq * 0.000000001/*/PV_GHZ*/,'f',6)/*+unitStr*/;
        }else
        {
            freqValue=QString::number((qreal)freq * 0.000000001/*/PV_GHZ*/,'f',9-zeronum)/*+unitStr*/;
        }
        break;
    case PV_UNIT_MHZ:
        unitStr=" MHz";
        if(6<=zeronum)
        {
            freqValue=QString::number((qreal)freq * 0.000001/*/PV_MHZ*/,'f',6)/*+unitStr*/;
        }else
        {
            freqValue=QString::number((qreal)freq * 0.000001/*/PV_MHZ*/,'f',6-zeronum)/*+unitStr*/;
        }
        break;
    case PV_UNIT_KHZ:
        unitStr=" kHz";
        if(3<=zeronum)
        {
            freqValue=QString::number((qreal)freq* 0.001/*/PV_KHZ*/,'f',6)/*+unitStr*/;
        }else
        {
            freqValue=QString::number((qreal)freq * 0.001/*/PV_KHZ*/,'f',3-zeronum)/*+unitStr*/;
        }
        break;
    case PV_UNIT_HZ:
        unitStr=" Hz";
        freqValue=QString::number((qreal)freq/*/PV_HZ*/,'f',6)/*+unitStr*/;
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

void BitGaugeDialView::showBottomWordsMsg(qint32 msgType)
{
    switch (msgType) {
    case PV_BOTTOM_STARTANDSTOP:
        if(m_bOffsetFreq)
        {
            m_wordset.gbflstr = "Offset Start Freq "+freqValueToQstring(m_freqinfo.gstartfreq);
            m_wordset.gbfrstr = "Offset Stop Freq "+freqValueToQstring(m_freqinfo.gstopfreq);
            m_wordset.gbslstr = "Offset Freq "+freqValueToQstring(m_freqinfo.gfreqoffset);
        }
        else
        {
            m_wordset.gbflstr = "Start Freq "+freqValueToQstring(m_freqinfo.gstartfreq );
            m_wordset.gbfrstr = "Stop Freq "+freqValueToQstring(m_freqinfo.gstopfreq);
            m_wordset.gbslstr = "";
        }
        break;
    case PV_BOTTOM_CENTERANDSPAN:
        if(m_bOffsetFreq)
        {
            m_wordset.gbflstr = "Offset Center Freq "+freqValueToQstring(m_freqinfo.gcenterfreq);
            m_wordset.gbfrstr = "Span "+freqValueToQstring(m_freqinfo.gspanfreq);
            m_wordset.gbslstr = "Offset Freq "+freqValueToQstring(m_freqinfo.gfreqoffset);
        }
        else
        {
            m_wordset.gbflstr = "Center Freq "+freqValueToQstring(m_freqinfo.gcenterfreq);
            m_wordset.gbfrstr = "Span "+freqValueToQstring(m_freqinfo.gspanfreq);
            m_wordset.gbslstr = "";
        }
        break;
    default:
        break;
    }
    emit InfoBottom();
    update();
    return;
}

void BitGaugeDialView::showTopWordsMsg(qint32 msgType)
{
    switch (msgType) {
    case PV_TOP_NOW_DATA:
        m_wordset.gtslstr = QString("Sensor Temperature %1 ℃").arg(QString::number(m_fTemperature,'f',2)) ;
//        m_wordset.gtscstr = QString("Sensor Recv %1 dBm").arg(QString::number(m_fNowPowerData,'f',2)) ;
        m_wordset.gtsrstr = QString("Sensor Power Point %1 ").arg(QString::number(m_nPointPowerNum)) ;
        break;
        //    case PV_TOP_TEMPERATURE_INFO:
        //        break;
        //    case PV_TOP_POINT_INFO:
        //        break;
    default:
        break;
    }
    emit InfoTop();
    update();
    return;
}

