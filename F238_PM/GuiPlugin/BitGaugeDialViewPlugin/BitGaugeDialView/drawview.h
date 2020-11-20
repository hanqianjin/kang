#ifndef DRAWVIEW_H
#define DRAWVIEW_H

#include <QPainter>
#include "gugedial_define.h"

class DrawView
{
public:
    DrawView();
public:
    void drawFrameLines(QPainter &painter,QRect rectClient,qint32 nSplit,QColor colorLine);
//    void drawGridLines(QPainter &painter,QRect rectSummay,QColor colorGridLine);
    void drawGridString(QPainter &painter,QRect rectSummay,PM_VIEW_SUMMAY &summayData,
                        QColor colorGridText1,QColor colorGridText2,QColor colorGridText3);

    void drawFrame(QPainter& painter,bool bLimit,bool bOffset,
                   qreal fAngleLen,qreal fRradius,qreal fArcHeight,qint32 nWidthArc,
                   qreal fMindial,qreal fMaxdial,qreal fUplimit,qreal fDownLimit,
                   QColor colArcLimitMid,QColor colArcLimtUpOrDown,QColor colArcOffset,QColor colText);//绘制边框与背景
    void drawDividing(QPainter& painter, qreal fAngleLen,qreal fRradius,qreal fArcHeight,qint32 nWidthArcNum,QColor colText);//绘制刻度
    void drawNumberIndicator(QPainter& painter,qreal fAngleStart,
                             qreal fAngleLen,qreal fRradius,qreal fArcHeight,
                             qreal fMindial,qreal fMaxdial,
                             QRect rectUnit,QString strUnit,
                             QColor colText);//绘制指示数字
    void drawIndicator(QPainter& painter,QPointF* points,
                       qreal fCurPowerDbm,qreal fMinPower,qreal fMaxPower,
                       qreal fAngleStart,qreal fAngleLen,
                       QColor color1,QColor color2,QColor colorLine);//绘制速度指针

    void gradientArc(QPainter *painter, qreal radius, qreal startAngle, qreal angleLength, qreal arcHeight,QColor colText0, QColor colText1);

    void  drawTopPart(QPainter &painter, PM_WORD_CTRL &wordset,QRect rectPart,QColor colTex);
    void  drawBottomPart(QPainter &painter, PM_WORD_CTRL &wordset,QRect rectPart,QColor colText);

    void drawBottomRect(QPainter& painter,bool bLimit,bool bOffset,
                        qreal fPowerdBm,qreal fdBmLimitUp,qreal fdBmLimitDown,
                        QRect rectBottom, QLinearGradient& bottomLinear,
                        QColor colArcLimitMid,QColor colArcLimtUpOrDown,QColor colArcOffset,
                        QColor colbottomLimit0,QColor colbottomLimit1,
                        QColor colbottomoffset0,QColor colbottomoffset1,
                        QColor colbottomMid0,QColor colbottomMid1);//绘制底部矩形
    void drawBottomData(QPainter &painter, QLinearGradient bottomLinear,
                                  QRect rectLeftEdit, QRect rectRightEdit,QString strLeft,QString strRight,
                                  QFont& fontBottom, QColor colText);
    void drawTitle(QPainter &painter,
                   QRect rectTopLeft,QRect rectTopRight,QRect rectMid,
                   QString strTopleft, QString strTopRight, QString strMid,
                   QColor colTextTitle,QColor ColTextTopTitle);//显示标题

    void drawRectText(QPainter &painter,QRect rectText,QString strRect,qint32 nTextFlg, QColor colText);//显示标题
};

#endif // DRAWVIEW_H
