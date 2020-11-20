#ifndef BitGaugeDialView_H
#define BitGaugeDialView_H

#include "gugedial_define.h"
#include <QWidget>
#include <QLCDNumber>
#include <QLabel>
#include <QHBoxLayout>
#include <QPainter>

#include "drawview.h"

class BitGaugeDialView : public QWidget
{
    Q_OBJECT

public:
    BitGaugeDialView(QWidget *parent = 0);
    ~BitGaugeDialView();

protected:
    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent *event);

public:
    void setDisplayModle(qint32 nDisplayModle);

    void setCurentSensorData(_PM_SENSOR_DATA sensorData);

    qreal setDisplayLayer(qreal fPower,qint32 nLeftOrRight);
    void setFreqOffset(bool bOffset);
    void setHoldMaxPower(bool bHoldMax);
//    void setPowerZero(bool bPowerZero);
    void setRelativeForward(bool bRelativeForward);
    void setRelativeReverse(bool bRelativeReverse);
    void setdBmRelativeBaseForward(qreal fdBmRelativeBase);
    void setdBmRelativeBaseReverse(qreal fdBmRelativeBase);

    void SetLimitOn(bool bLimtOn);
    void SetPowerUpLimit(qreal fLimitUp,qint32 nLeftOrRight);
    void SetPowerDownLimit(qreal fLimitDown,qint32 nLeftOrRight);

    void SetDrawRect(int nLeft,int nTop,int nWidth,int nHight);
    void SetArcStartAngle(qreal fStartAngle);
    void SetArcAngleLen(qreal fAngleLen);
    void SetArcHight(qreal fArcHight);
    void SetMinPower(qreal fMinPower);
    void SetMaxPower(qreal fMaxPower);
    void SetArcMaxMin(qreal fMax,qreal fMin);

    void SetArcTopTitleLeft(QString strTopTitleLeft,qint32 nLeftOrRight);
    void SetArcTopTitleRight(QString strTopTitleRight,qint32 nLeftOrRight);
    void SetArcMidTitle(QString strMidTitle,qint32 nLeftOrRight);
    void SetArcBottomLeft(QString strBottomLeft,qint32 nLeftOrRight,qint32 nNo);
    void SetArcBottomRight(QString strBottomRight,qint32 nLeftOrRight,qint32 nNo);
    void SetArcWaring(QString strWaring);
    void setFreqAttribute(quint32 attributeType, qreal attribute);
    qreal getFreqAttribute(quint32 attributeType);

    void setDisplayRectLeft(qreal fData,qint32 nLeftOrRight,qint32 nFlg);
    void setDisplayRectLeft(QString strtext,qint32 nLeftOrRight,qint32 nFlg);
    void setDisplayRectRight(qreal fData,qint32 nLeftOrRight,qint32 nFlg);
    void setDisplayRectRight(QString strtext,qint32 nLeftOrRight,qint32 nFlg);
private:
    void showDialPower(qreal fPower,qint32 nLeftOrRight);
    void showDialData(qreal fData,QString strUnit,qint32 nLeftOrRight);
    void showMaxPower(qreal fPower,qint32 nLeftOrRight);
    void showRelativePower(qreal fPower,qint32 nLeftOrRight);
private:
    void showTopWordsMsg(qint32 msgType);
    QString freqValueToQstring(qreal freq);
    qint32 freqUnitFindProc(qreal freq);
    qint32 freqnotZeroPosition(qreal freq);

    void drawLayerPixmapOne(QPixmap &pixMap,_PM_PIXMAP_LAYER &layerDraw);
    void drawLayerPixmap(QPixmap &pixMap,_PM_PIXMAP_LAYER &layerDraw);
    void drawLayerTitle(QPixmap &pixMap,_PM_PIXMAP_LAYER &layerDraw);
    void drawLayerData(QPixmap &pixMap,_PM_PIXMAP_LAYER &layerDraw);
signals:
    void InfoBottom();
    void InfoTop();
    void PixmapBottom();
    void PixmapFirst();
    void PixmapSecond();
    void PixmapThird();
    void PixmapSummay();
    void PixmapCCDF();
    void PixmapSummayData();
private slots:
    void refreshInfoBottom();
    void refreshLayerBottom();
    void refreshLayerFirst();
    void refreshLayerSecond();
    void refreshLayerThird();
    void refreshInfoTop();

    void refreshLayerSummay();
    void refreshLayerCCDF();
    void SetArcUnit(qint32 nUnit);
public:
    void showBottomWordsMsg(qint32 msgType);


public:
    void setdisplaymode(qint32 displaymode);
private:
    void produceColorBar(qint32 displaymode);
    QString getUnitString(int nUnitIndex);

    qreal getDataByUnitType(char *label,qreal fdBmPower, qint32 nUnitIndexFlg);

    qreal dbmToVoltCalculator(char *label, qreal _level, qint32 nUnitIndexFlg);
    qreal dbmToWattsCalculator(char *label, qreal _level, qint32 nUnitIndexFlg);

    qreal dBmAdd(qreal _level1,qreal _level2);
    qreal dBmSub(qreal _level1,qreal _level2);
    qreal dBmDiv(qreal _level1,qreal _Point);

    PM_BIT_FREQ_INFO m_freqinfo;
    PM_WORD_CTRL m_wordset;
private:
    DrawView m_drawView;

    qint32 m_nDisplayModle; //显示模式
    bool m_bOffsetFreq;
    qreal m_nlOffsetFreq;
//    qreal m_fPowerdBm;   //当前仪表盘指针功率值 dbm
    qreal m_fNowPowerData;   //当前采集实际功率值
    qreal m_fTemperature;
    qint32 m_nPointPowerNum; //Power Number Recv

    qint32  m_nUnitType;//数据索引
    qint32  m_nUnitIndex;//数据单位索引
    QString m_strUnit;//数据单位
    bool m_bHoldMax; //最大值保持标志
    bool m_bAverageflg; //
    qint32 m_nAveragePoint;//平均点
    qint32 m_nIndexAverage;//平均功率点索引
    qreal m_fPowerPointTotle;//平均点功率和

    qreal m_fPowerAverage;//平均功率
    qreal m_fPowerTotle;//功率和
    qreal m_fTotlePoint;//平均点采集个数

    bool m_bRelativeForward;
    bool m_bRelativeReverse;

    qreal m_fRelativeForward;
    qreal m_fRelativeReverse;
//    bool m_bPowerZero;//是否采集0点
//    bool m_bPowerZeroCal;//采集0点标志
//    qreal m_fPowerBase;//功率0点

    qreal m_fStartAngle;
    qreal m_fAngleLen;

    int m_fArcHeight1;//弧形宽度
    int m_fArcHeight2;//弧形宽度
    int m_fArcHeight3;//弧形宽度
    int m_fArcHeight4;//弧形宽度
    int m_fArcHeight6;//弧形宽度
    int m_fArcHeight9;//弧形宽度
    int m_fArcHeight10;//弧形宽度

    qreal m_fMinDial;  //功率盘最小值
    qreal m_fMaxDial;   //功率盘最大值

    bool m_bLimtOn;//是否设置极限

    qreal m_fMinPower;  //功率最小值 加上Offset
    qreal m_fMaxPower;   //功率最大值  加上Offset

    QString m_strWaring;  //警告

private:
    QPixmap m_pixmapLayerBottom; // 底层 不动 主要绘制边框

    QPixmap m_pixmapPower;//功率显示
    QPixmap m_pixmapPowerTitle;//
    QPixmap m_pixmapPowerData;//

    QPixmap m_pixmapForward;// 左侧显示    Forward显示
    QPixmap m_pixmapReverse;//右侧显示    Reverse
    QPixmap m_pixForwardTitle;//
    QPixmap m_pixReverseTitle;//
    QPixmap m_pixForwardData;//
    QPixmap m_pixReverseData;//

    QPixmap m_pixmapBottomInfo;//底部显示
    QPixmap m_pixmapTopInfo;//顶部显示

    QPixmap m_pixmapLayerSummay;//参数表显示
    QPen m_penBit;
    QPen m_penBoarder;//Plugin's boarder lines.

    _COLOR_BOARD_PM m_BoardColor;
    _COLOR_PEN_PM   m_PenColor;

    PM_VIEW_SUMMAY m_summayData;
    QRect CenterPartRect;
//    QRect topPartRect;
//    QRect leftPartRect;

    _PM_PIXMAP_LAYER m_layerPixMap[2];
private:
    QPoint m_pointArc;
    QFont m_fontBottom;
    QFont m_fontMid;
};

#endif // BitGaugeDialView_H
