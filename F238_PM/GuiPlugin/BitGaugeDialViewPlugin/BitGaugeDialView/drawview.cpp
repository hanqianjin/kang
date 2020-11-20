#include "drawview.h"

DrawView::DrawView()
{

}

/**
* @brief 绘制边框
* @note
* @author Roc
* @since  2019.11.11
*/
void DrawView::drawFrameLines(QPainter &painter,QRect rectClient,qint32 nSplit,QColor colorLine)
{
    QPen penBit;
    painter.save();
    qreal painterLeft = rectClient.left();
    qreal painterRight = rectClient.right();
    qreal painterTop = rectClient.top();
    qreal painterBottom = rectClient.bottom();

    penBit.setWidth(PM_LINEREEOR);
    penBit.setColor(colorLine);
    painter.setPen(penBit);

    painter.drawLine(QPointF(painterLeft - PM_HALFLINEREEOR,painterTop -  PM_HALFLINEREEOR),QPointF(painterRight + PM_HALFLINEREEOR,painterTop -  PM_HALFLINEREEOR));
    painter.drawLine(QPointF(painterRight+ PM_HALFLINEREEOR,painterTop -  PM_HALFLINEREEOR),QPointF(painterRight + PM_HALFLINEREEOR,painterBottom +  PM_HALFLINEREEOR));
    painter.drawLine(QPointF(painterLeft - PM_HALFLINEREEOR,painterBottom +  PM_HALFLINEREEOR),QPointF(painterRight + PM_HALFLINEREEOR,painterBottom +  PM_HALFLINEREEOR));
    painter.drawLine(QPointF(painterLeft - PM_HALFLINEREEOR,painterTop -  PM_HALFLINEREEOR),QPointF(painterLeft - PM_HALFLINEREEOR,painterBottom +  PM_HALFLINEREEOR));
    if(2 == nSplit)
    painter.drawLine(QPointF(painterLeft + rectClient.width()*0.5,painterTop -  PM_HALFLINEREEOR),QPointF(painterLeft  + rectClient.width()*0.5,painterBottom +  PM_HALFLINEREEOR));

    painter.restore();
    return;
}

///**
//* @brief 绘制边框
//* @note
//* @author Roc
//* @since  2019.11.11
//*///m_penColor.gridPart
//void DrawView::drawGridLines(QPainter &painter, QRect rectSummay,QColor colorGridLine)
//{
//    QPen penBit;
//    painter.save();
//    qint32 nGridNum = m_summayData.gNum;

//    qint32 nPainterCenterX = rectSummay.width()*0.7;
//    qint32 nPainterY = rectSummay.height()/nGridNum;

//    penBit.setWidth(PM_HALFLINEREEOR);
//    penBit.setColor(colorGridLine);
//    painter.setPen(penBit);

//    for(qint32 i = 1;i < nGridNum;i++)
//    {
//        painter.drawLine(QPointF(rectSummay.left(),nPainterY*i),
//                         QPointF(rectSummay.right(),nPainterY*i));
//    }
//    painter.drawLine(QPointF(rectSummay.left() + nPainterCenterX,rectSummay.top()),
//                     QPointF(rectSummay.left() + nPainterCenterX,rectSummay.bottom()));

//    painter.restore();
//    return;
//}


/**
* @brief
* @note
* @author Roc
* @since  20120.1.6
*/
void DrawView::drawGridString(QPainter &painter, QRect rectSummay,PM_VIEW_SUMMAY &summayData,
                              QColor colorGridText1,QColor colorGridText2,QColor colorGridText3)
{
    painter.save();
    QRect  rectSummayLeft[PM_SUMMAY_NUM],rectSummayRight[PM_SUMMAY_NUM];
    QFont fontTemp;
    int nMid = rectSummay.width()*0.4;
    int nHight = rectSummay.height()*0.07;
    QString strData;
    int nTempSize = qMax(nHight*0.6,1.0);
    fontTemp.setPixelSize(nTempSize);
    painter.setFont(fontTemp);
    for(qint32 i = 0;i < summayData.gNum;i++)
    {
        rectSummayLeft[i].setLeft(rectSummay.left());
        rectSummayLeft[i].setRight(nMid);
        rectSummayLeft[i].setTop(rectSummay.top()+i*nHight);
        rectSummayLeft[i].setBottom(rectSummayLeft[i].top() + nHight-5);

        rectSummayRight[i].setLeft(nMid+5);
        rectSummayRight[i].setRight(rectSummay.right());
        rectSummayRight[i].setTop(rectSummay.top()+i*nHight);
        rectSummayRight[i].setBottom( rectSummayRight[i].top() + nHight-5);
        painter.setBrush(colorGridText1);
        painter.drawRect(rectSummayLeft[i]);

        if(0 == i%2)
            painter.setBrush(colorGridText2);
        else
            painter.setBrush(colorGridText3);
        painter.drawRect(rectSummayRight[i]);

        rectSummayLeft[i].setLeft(rectSummayLeft[i].left()+30);
        painter.setPen(colorGridText2);
        painter.drawText(rectSummayLeft[i],Qt::AlignLeft|Qt::AlignVCenter,summayData.gSummayName[i]);

        rectSummayRight[i].setLeft(rectSummayRight[i].left()+30);
        painter.setPen(colorGridText1);
        strData = QString::number(summayData.gSummayData[i],'f',2) + summayData.gSummayUnit[i] + "    ";
        painter.drawText(rectSummayRight[i],Qt::AlignRight|Qt::AlignVCenter,strData);
    }
    painter.restore();
    return;
}
/**
* @brief   逆时针绘制弧形图形
* @note
* @author  Roc
* @since   2019.11.7
*/
void DrawView::drawFrame(QPainter &painter,bool bLimit,bool bOffset,
                         qreal fAngleLen,qreal fRradius,qreal fArcHeight,qint32 nWidthArcNum,
                         qreal fMindial,qreal fMaxdial,qreal fUplimit,qreal fDownLimit,
                         QColor colArcLimitMid,QColor colArcLimtUpOrDown,QColor colArcOffset,QColor colText)
{
    QColor tempColor;
    painter.save();
    qreal fRotateAngle = 270 + fAngleLen*0.5; //以角度间隔计算起点
    painter.rotate(fRotateAngle);
    qreal fArctWidth = nWidthArcNum*fArcHeight;

    qreal fArcBeginRradius;
    if(4 == nWidthArcNum)
        fArcBeginRradius =fRradius+  + fArcHeight*1.1;
    else
        fArcBeginRradius =fRradius+  + fArcHeight*1.3;


    if(bLimit)
    {
        qreal m_fAngleLimitUp;
        qreal m_fAngleLimitDown;

        if(fUplimit  >= fMindial)
            m_fAngleLimitUp= (fUplimit   - fMindial) / (fMaxdial- fMindial) * fAngleLen;
        else
            m_fAngleLimitUp = fMindial;

        if(fDownLimit  >= fMindial)
            m_fAngleLimitDown= (fDownLimit - fMindial) / (fMaxdial- fMindial) * fAngleLen;
        else
            m_fAngleLimitDown = fMindial;
        //调整仪表盘最大值最小值防止超限
        if(m_fAngleLimitUp > fAngleLen)
            m_fAngleLimitUp = fAngleLen;

        if( m_fAngleLimitDown > m_fAngleLimitUp)
            m_fAngleLimitDown = m_fAngleLimitUp;
        //注意设置的是弧形起点与弧形宽度
        tempColor = colArcLimtUpOrDown;

        gradientArc(&painter, fArcBeginRradius, 0,  fAngleLen- m_fAngleLimitUp , fArctWidth,colText, tempColor);
        if(bOffset)
            tempColor =  colArcOffset;
        else
            tempColor =  colArcLimitMid;

        gradientArc(&painter, fArcBeginRradius, fAngleLen - m_fAngleLimitUp,   m_fAngleLimitUp - m_fAngleLimitDown , fArctWidth, colText, tempColor);

        tempColor = colArcLimtUpOrDown;
        gradientArc(&painter, fArcBeginRradius, fAngleLen- m_fAngleLimitDown, m_fAngleLimitDown, fArctWidth,colText, tempColor);

    }
    else
    {
        if(bOffset)
            tempColor =  colArcOffset;
        else
            tempColor =  colArcLimitMid;

        gradientArc(&painter, fArcBeginRradius, 0,  fAngleLen, fArctWidth,colText, tempColor);

    }


    gradientArc(&painter, fRradius, 0,  fAngleLen , fArcHeight, colText, colText);
    painter.restore();
}

/**
* @brief   绘制刻度
* @note
* @author  Roc
* @since   2019.11.7
*/
void DrawView::drawDividing(QPainter &painter, qreal fAngleLen,qreal fRradius,qreal fArcHeight,qint32 nWidthArcNum,QColor colText)
{
    painter.save();
    qreal fRotateAngle = 270 - fAngleLen*0.5; //以角度间隔计算起点
    painter.rotate(fRotateAngle);

    QPen pen(colText);
    painter.setPen(pen);

    qreal fStep = (GAUGE_SCALE_END - GAUGE_SCALE_BEGIN) *0.2;
    qreal fAngleStep = fAngleLen / fStep;
    qint32 nBegin = fRradius+fArcHeight;
    qint32 nEnd = nBegin+fArcHeight*(nWidthArcNum-0.1);
    qint32 nMid = nBegin+fArcHeight*nWidthArcNum*0.5;
    for (int i = GAUGE_SCALE_BEGIN; i <= GAUGE_SCALE_END; i += 5)
    {
        //        if (i >= 140)
        //        { //绘制红色
        //            pen.setColor(Qt::red);
        //            painter.setPen(pen);
        //        }

        //        if (i % 20 == 0)
        //        {//粗线
        //            pen.setWidth(2);
        //            painter.setPen(pen);
        //            painter.drawLine(m_fRradius+m_fArcHeight4,0,m_fRradius,0);

        //        }
        //        else
        if (i % 10 == 0)
        {//中等
            pen.setWidth(2);
            painter.setPen(pen);
            painter.drawLine(nBegin,0,nEnd,0);

        }
        else if (i % 5 == 0)
        { //短线
            pen.setWidth(1);
            painter.setPen(pen);
            painter.drawLine(nBegin,0,nMid,0);
        }
        painter.rotate(fAngleStep);
    }

    painter.restore();
}

/**
* @brief   绘制弧形带颜色
* @note
 *          参数二：半径
 *          参数三：开始的角度
 *          参数四：指扫取的角度-逆时针（360度 / 8 = 45度）
 *          参数五：圆环的高度
 *          参数六：填充色
* @author  Roc
* @since   2019.11.7
*/
void DrawView::gradientArc(QPainter *painter, qreal radius, qreal startAngle, qreal angleLength, qreal arcHeight,QColor colText0, QColor colText1)
{
    QRadialGradient gradient(0, 0, radius);
    gradient.setColorAt(0, colText0);
    gradient.setColorAt(1.0, colText1);
    painter->setBrush(gradient);

    QRectF rect(-(radius+arcHeight), -(radius+arcHeight), (radius+arcHeight)*2, (radius+arcHeight)*2);
    QPainterPath path;
    path.arcTo(rect, startAngle, angleLength);

    QPainterPath subPath;
    subPath.addEllipse(rect.adjusted(arcHeight, arcHeight, -arcHeight, -arcHeight));
    path -= subPath;

    painter->setPen(Qt::NoPen);
    painter->drawPath(path);
}

void DrawView::drawTopPart(QPainter &painter, PM_WORD_CTRL &wordset,QRect rectPart,QColor colText)
{
    QPen  penBit;
    painter.save();
    penBit.setWidth(PM_HALFLINEREEOR);
    penBit.setColor(colText);
    painter.setPen(penBit);
    QFont mFont;
    mFont.setFamily("Arial");
    mFont.setPixelSize(13);
    mFont.setWeight(QFont::Bold);
    painter.setFont(mFont);

    qint32 mx = rectPart.left() + 0.5 * (rectPart.width() - PM_TITLEWIDTH);
    qint32 my =rectPart.top() - PM_WORDHEIGHT + PM_LINEREEOR;
    painter.drawText(mx, my, PM_TITLEWIDTH, PM_WORDHEIGHT, Qt::AlignCenter, wordset.gtscstr);

    //topfirstleft
    mx = rectPart.left() + PM_HALFLINEREEOR;
    my = rectPart.top() -2* PM_WORDHEIGHT + PM_LINEREEOR;
    painter.drawText(mx, my, PM_TITLEWIDTH, PM_WORDHEIGHT, Qt::AlignLeft, wordset.gtflstr);

    //topsecleft
    my = rectPart.top() - PM_WORDHEIGHT + PM_LINEREEOR;
    painter.drawText(mx, my, PM_TITLEWIDTH, PM_WORDHEIGHT, Qt::AlignLeft, wordset.gtslstr);

    mx = rectPart.right() - PM_TITLEWIDTH;
    my = rectPart.top() -2* PM_WORDHEIGHT + PM_LINEREEOR;
    painter.drawText(mx, my, PM_TITLEWIDTH, PM_WORDHEIGHT, Qt::AlignRight, wordset.gtfrstr);

    my = rectPart.top() - PM_WORDHEIGHT + PM_LINEREEOR;
    painter.drawText(mx, my, PM_TITLEWIDTH, PM_WORDHEIGHT, Qt::AlignRight, wordset.gtsrstr);

    painter.restore();
    return;
}

void DrawView::drawBottomPart(QPainter &painter, PM_WORD_CTRL &wordset,QRect rectPart,QColor colText)
{
    QPen  penBit;
    painter.save();
    penBit.setWidth(PM_HALFLINEREEOR);
    penBit.setColor(colText);
    painter.setPen(penBit);
    QFont mFont;
    mFont.setFamily("Arial");
    mFont.setPixelSize(13);
    mFont.setWeight(QFont::Bold);
    painter.setFont(mFont);

    //bottomfirstleft
    qint32 mx =  rectPart.left() + PM_HALFLINEREEOR;
    qint32 my =  rectPart.bottom() + PM_LINEREEOR;
    painter.drawText(mx, my, PM_TITLEWIDTH + 30, PM_WORDHEIGHT, Qt::AlignLeft, wordset.gbflstr);

    //bottomsecleft
    my =  rectPart.bottom() +  PM_WORDHEIGHT - PM_LINEREEOR;
    painter.drawText(mx, my, PM_TITLEWIDTH, PM_WORDHEIGHT + 30, Qt::AlignLeft, wordset.gbslstr);

    //bottomfirstright
    mx = rectPart.right() - PM_TITLEWIDTH;
    my =  rectPart.bottom() + PM_LINEREEOR;
    painter.drawText(mx, my, PM_TITLEWIDTH, PM_WORDHEIGHT, Qt::AlignRight, wordset.gbfrstr);

    //bottomsectright
    my = rectPart.bottom() +  PM_WORDHEIGHT - PM_LINEREEOR;
    painter.drawText(mx, my, PM_TITLEWIDTH, PM_WORDHEIGHT, Qt::AlignRight, wordset.gbsrstr);

    painter.restore();
    return;
}

/**
* @brief   绘制数字指示
* @note
* @author  Roc
* @since   2019.11.7
*/
void DrawView::drawNumberIndicator(QPainter &painter,qreal fAngleStart,
                                   qreal fAngleLen,qreal fRradius,qreal fArcHeight,
                                   qreal fMindial,qreal fMaxdial,
                                   QRect rectUnit,QString strUnit,
                                   QColor colText)
{
    painter.save();
    painter.setPen(colText);
    double x,y;
    double angle, angleArc;

    for (int i = GAUGE_SCALE_BEGIN; i <= GAUGE_SCALE_END; i+= 20)//每隔20设置一个数字
    {
        angle = fAngleStart + i / (GAUGE_SCALE_END- GAUGE_SCALE_BEGIN) * fAngleLen; //角度
        angleArc = angle * 3.14 / 180; //转换为弧度

        x = (fRradius - fArcHeight*1.3) * cos(angleArc);
        y = (fRradius - fArcHeight*1.3)  * sin(angleArc);

        QString speed = QString::number(fMindial + i /
                                        (GAUGE_SCALE_END- GAUGE_SCALE_BEGIN) *
                                        (fMaxdial-fMindial),'f',2);


        painter.drawText(QPointF(x - fArcHeight,y - fArcHeight*0.2),speed);

    }

    rectUnit.setRect(-rectUnit.width()*0.5,-fRradius*0.7,rectUnit.width(),rectUnit.height());

    painter.restore();
    painter.save();
    QFont fontTemp;
    int nTempSize;
    painter.setPen(colText);
    nTempSize = qMax(rectUnit.height() *0.8,1.0);
    fontTemp.setPixelSize(nTempSize);
    fontTemp.setBold(true);
    painter.setFont(fontTemp);
    painter.drawText(rectUnit,Qt::AlignCenter,strUnit);

    painter.restore();
}

/**
* @brief   绘制指针
* @note
* @author  Roc
* @since   2019.11.7
*/
void DrawView::drawIndicator(QPainter &painter,QPointF* points,
                             qreal fCurPowerDbm,qreal fMinPower,qreal fMaxPower,
                             qreal fAngleStart,qreal fAngleLen,
                             QColor color1,QColor color2,QColor colorLine)
{
    painter.save();
    //进行锯齿消除，会影响效率
    painter.setRenderHint(QPainter::Antialiasing);
    double curAngle = 0.0;;
    if(fCurPowerDbm <= fMinPower)
        curAngle = fAngleStart -1;
    else if(fCurPowerDbm >= fMaxPower)
        curAngle = fAngleStart + fAngleLen +1;
    else
        curAngle = fAngleStart + fAngleLen * (fCurPowerDbm - fMinPower) / (fMaxPower- fMinPower);

//    qDebug()<<"Angle" <<curAngle<< fAngleStart << fAngleLen <<fCurPowerDbm<<fMinPower+fOffsetPower <<
//              fMaxPower- fMinPower<<(fMinPower+fOffsetPower) / (fMaxPower- fMinPower)<<endl;
    painter.rotate(curAngle); //旋转坐标系
    QRadialGradient haloGradient(0, 0, 60, 0, 0);  //辐射渐变
    haloGradient.setColorAt(0, color1);
    haloGradient.setColorAt(1, color2);
    painter.setPen(colorLine); //定义线条文本颜色  设置线条的颜色
    painter.setBrush(haloGradient);//刷子定义形状如何填满 填充后的颜色

    painter.drawPolygon(points,4); //绘制指针
    painter.restore();
}

/**
* @brief   绘制底部矩形
* @note
* @author  Roc
* @since   2019.11.7
*/
void DrawView::drawBottomRect(QPainter &painter,bool bLimit,bool bOffset,
                              qreal fPowerdBm,qreal fdBmLimitUp,qreal fdBmLimitDown,
                              QRect rectBottom, QLinearGradient& bottomLinear,
                              QColor colArcLimitMid,QColor colArcLimtUpOrDown,QColor colArcOffset,
                              QColor colbottomLimit0,QColor colbottomLimit1,
                              QColor colbottomoffset0,QColor colbottomoffset1,
                              QColor colbottomMid0,QColor colbottomMid1)
{
    painter.save();
    if(bLimit)
    {
        if((fPowerdBm  >=   fdBmLimitUp)
                ||(fPowerdBm <=   fdBmLimitDown))
        {
            bottomLinear.setColorAt(0.0,colbottomLimit0);
            bottomLinear.setColorAt(1.0,colbottomLimit1);

            painter.fillRect(rectBottom,colArcLimtUpOrDown);
        }
        else  if(bOffset)
        {
            bottomLinear.setColorAt(0.0,colbottomoffset0);
            bottomLinear.setColorAt(1.0,colbottomoffset1);

            painter.fillRect(rectBottom,colArcOffset);
        }
        else
        {

            bottomLinear.setColorAt(0.0,colbottomMid0);
            bottomLinear.setColorAt(1.0,colbottomMid1);
            painter.fillRect(rectBottom,colArcLimitMid);
        }
    }
    else{
        if(bOffset)
        {

            bottomLinear.setColorAt(0.0,colbottomoffset0);
            bottomLinear.setColorAt(1.0,colbottomoffset1);
            painter.fillRect(rectBottom,colArcOffset);
        }
        else
        {

            bottomLinear.setColorAt(0.0,colbottomMid0);
            bottomLinear.setColorAt(1.0,colbottomMid1);
            painter.fillRect(rectBottom,colArcLimitMid);
        }
    }

}
void DrawView::drawBottomData(QPainter &painter, QLinearGradient bottomLinear,
                              QRect rectLeftEdit, QRect rectRightEdit,QString strLeft,QString strRight,
                              QFont& fontBottom, QColor colText)
{
    painter.save();
    painter.setBrush(bottomLinear);
    painter.setPen(Qt::transparent);
//  painter.drawRect(rectLeftEdit);
    painter.drawRect(rectRightEdit);

    painter.setPen(colText);
    painter.setFont(fontBottom);
    painter.drawText(rectLeftEdit,Qt::AlignCenter,strLeft);
    painter.drawText(rectRightEdit,Qt::AlignCenter,strRight);
    painter.restore();
}


/**
* @brief   绘制标题
* @note
* @author  Roc
* @since   2019.11.7
*/
void DrawView::drawTitle(QPainter &painter,
                         QRect rectTopLeft,QRect rectTopRight,QRect rectMid,
                         QString strTopleft, QString strTopRight, QString strMid,
                         QColor colTextTitle,QColor ColTextTopTitle)
{

    QFont fontTemp;
    int nTempSize;
    painter.save();
    nTempSize = qMax(rectTopLeft.height() *0.5,1.0);
    painter.setPen(ColTextTopTitle);
    fontTemp.setPixelSize(nTempSize);
    painter.setFont(fontTemp);
    painter.drawText(rectTopLeft,Qt::AlignLeft,strTopleft);
    painter.drawText(rectTopRight,Qt::AlignRight,strTopRight);
    painter.restore();
    painter.save();
    painter.setPen(colTextTitle);
    nTempSize = qMax(rectMid.height() *0.5,1.0);
    fontTemp.setPixelSize(nTempSize);
    fontTemp.setBold(true);
    painter.setFont(fontTemp);
    painter.drawText(rectMid,Qt::AlignCenter,strMid);
    painter.restore();
}

void DrawView::drawRectText(QPainter &painter,QRect rectText,QString strRect,qint32 nTextFlg, QColor colText)
{
    QFont fontTemp;
    int nTempSize;
    nTempSize = qMax(rectText.height() *0.7,1.0);
    painter.save();
    painter.setPen(colText);
    fontTemp.setPixelSize(nTempSize);
    painter.setFont(fontTemp);
    painter.drawText(rectText,nTextFlg,strRect);
    painter.restore();
}
