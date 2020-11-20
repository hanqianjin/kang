#include "sa_widget_channelpowertable.h"
#include "ui_sa_widget_channelpowertable.h"

#include <QPainter>
#include <QStylePainter>
#include "sa_colordef.h"

sa_widget_ChannelPowerTable::sa_widget_ChannelPowerTable(controlInterface &interface,user_variable &m_user_variable, user_limit &m_user_limit, QWidget *parent) :
    QWidget(parent),
    pcontrolInterface(&interface),
    globalUserVariable(&m_user_variable),
    globalUserLimit(&m_user_limit),
    ui(new Ui::sa_widget_ChannelPowerTable)
{
    ui->setupUi(this);
    setProperty("status",qssMode[interface.GetDisplayMode()]);
    setAttribute(Qt::WA_DeleteOnClose);
    //setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/|Qt::CustomizeWindowHint);

    ChannelPowerTablePixmap = QPixmap(SMALLDRAW_WIDTH, CHANNELPOWER_TABLE_HEIGHT);
}

sa_widget_ChannelPowerTable::~sa_widget_ChannelPowerTable()
{
    delete ui;
}
void sa_widget_ChannelPowerTable::refreshChannelPowerTable()
{
    refreshPixmap();
    repaint(0,0,ChannelPowerTablePixmap.width(),ChannelPowerTablePixmap.height());
}
void sa_widget_ChannelPowerTable::refreshPixmap()
{
#if 1 //table_height = 100
    qint32 colorMode = globalUserVariable->gDisplayMode;
    QColor TableBgColor = TableBackgroundColor[colorMode];
    QColor fontColor = TableFontColor[colorMode];
    QColor curFontColor = TableCurFontColor[colorMode];

    ChannelPowerTablePixmap.fill(TableBgColor);
    QPainter painter(&ChannelPowerTablePixmap);

    quint32 maxStrFreqLen = 0;
    quint32 maxStrAmpLen  = 0;



    //draw pixmap title
    QFont font = QFont(QFont("Arial",10));
    font.setWeight(QFont::Bold);
    QPen pen(fontColor);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setFont(font);
    QFontMetrics fm = painter.fontMetrics();

    painter.drawText(CHANNELPOWER_LEFT_MARGIN,SPACE_BETWEEN_LINES, fm.width("Measurement"), fm.height(), Qt::AlignRight, "Measurement");
    painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4,SPACE_BETWEEN_LINES, fm.width("Value"), fm.height(), Qt::AlignRight, "Value");
    painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4 * 2 - 20,SPACE_BETWEEN_LINES, fm.width("Limit"), fm.height(), Qt::AlignRight, "Limit");
    painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4 * 3 - 70,SPACE_BETWEEN_LINES, fm.width("Pass / Fail"), fm.height(), Qt::AlignRight, "Pass / Fail");

    //draw pixmap content
    font.setWeight(QFont::Normal);
    painter.setFont(font);
    pen.setColor(curFontColor);
    pen.setWidth(1);
    painter.setPen(pen);
    fm = painter.fontMetrics();

    maxStrFreqLen = fm.width("-999.999999999 GHz");
    maxStrAmpLen  = fm.width("-99.99 dBm");

    QString strBandWidth = globalUserVariable->freqValueToQstring(globalUserVariable->gChannelBandwidth);
    QString strTotalPower = QString::number(globalUserVariable->dTotalPower, 'f', 2) + " dBm";
    QString strChannelPower = globalUserVariable->amptTransformToQstring(pcontrolInterface->getAmpUnit(),globalUserVariable->dPowerValue);
    QString strPSD = QString::number(globalUserVariable->dPSD, 'f', 2) + " dBm/Hz";

    painter.drawText(CHANNELPOWER_LEFT_MARGIN,SPACE_BETWEEN_LINES * 2 + fm.height(), fm.width("Total Channel Power"), fm.height(), Qt::AlignRight, "Total Channel Power");
    painter.drawText(CHANNELPOWER_LEFT_MARGIN,SPACE_BETWEEN_LINES * 3 +fm.height() * 2, fm.width("Channel Power"), fm.height(), Qt::AlignRight, "Channel Power");
    painter.drawText(CHANNELPOWER_LEFT_MARGIN,SPACE_BETWEEN_LINES * 4 +fm.height() * 3, fm.width("Band Width"), fm.height(), Qt::AlignRight, "Band Width");
    painter.drawText(CHANNELPOWER_LEFT_MARGIN,SPACE_BETWEEN_LINES * 5 +fm.height() * 4, fm.width("Power Spectral Density"), fm.height(), Qt::AlignRight, "Power Spectral Density");

    //draw value
    //Johnson 190321
    if(globalUserVariable->gTraceView[globalUserVariable->gTraceSelect] == SA_OFF)
    {
        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4,SPACE_BETWEEN_LINES * 2 + fm.height(),
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4,SPACE_BETWEEN_LINES * 3 +fm.height() * 2,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4,SPACE_BETWEEN_LINES * 4 +fm.height() * 3,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4,SPACE_BETWEEN_LINES * 5 +fm.height() * 4,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");

        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4 * 2,SPACE_BETWEEN_LINES * 2 + fm.height(),
                         fm.width("Limit1"), fm.height(), Qt::AlignRight, "Limit1");
        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4 * 2,SPACE_BETWEEN_LINES * 3 +fm.height() * 2,
                         fm.width("Limit2"), fm.height(), Qt::AlignRight, "Limit2");
        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4 * 2,SPACE_BETWEEN_LINES * 4 +fm.height() * 3,
                         fm.width("Limit3 / Limit4"), fm.height(), Qt::AlignRight, "Limit3 / Limit4");
        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4 * 2,SPACE_BETWEEN_LINES * 5 +fm.height() * 4,
                         fm.width("Limit5 / Limit6"), fm.height(), Qt::AlignRight, "Limit5 / Limit6");

        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4 * 3,SPACE_BETWEEN_LINES * 2 + fm.height(),
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4 * 3,SPACE_BETWEEN_LINES * 3 +fm.height() * 2,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4 * 3,SPACE_BETWEEN_LINES * 4 +fm.height() * 3,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4 * 3,SPACE_BETWEEN_LINES * 5 +fm.height() * 4,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
    }
    else
    {
        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4,SPACE_BETWEEN_LINES * 2 + fm.height(),
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strTotalPower);
        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4,SPACE_BETWEEN_LINES * 3 +fm.height() * 2,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strChannelPower);
        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4,SPACE_BETWEEN_LINES * 4 +fm.height() * 3,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4,SPACE_BETWEEN_LINES * 5 +fm.height() * 4,
                         maxStrAmpLen + 30, fm.height(), Qt::AlignLeft, strPSD);

        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4 * 2 - 20,SPACE_BETWEEN_LINES * 2 + fm.height(),
                         fm.width("Limit1"), fm.height(), Qt::AlignRight, "Limit1");
        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4 * 2 - 20,SPACE_BETWEEN_LINES * 3 +fm.height() * 2,
                         fm.width("Limit2"), fm.height(), Qt::AlignRight, "Limit2");
        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4 * 2 - 20,SPACE_BETWEEN_LINES * 4 +fm.height() * 3,
                         fm.width("Limit3 / Limit4"), fm.height(), Qt::AlignRight, "Limit3 / Limit4");
        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4 * 2 - 20,SPACE_BETWEEN_LINES * 5 +fm.height() * 4,
                         fm.width("Limit5 / Limit6"), fm.height(), Qt::AlignRight, "Limit5 / Limit6");


        QString strL1,strL2,strL3,strL4,strL5,strL6;
        if(globalUserLimit->gLimitTest == SA_ON)
        {
            for(qint32 i = 0;i<LIMIT_SELECTSUM;i++)
            {
                if(globalUserLimit->gLimitLine[i] == SA_ON)
                {
                    if (globalUserLimit->gLatestLimitTestResult[i] == SA_PASS)
                    {
                        if(i == 0) strL1 = "TR: PASS";
                        else if(i == 1) strL2 = "TR: PASS";
                        else if(i == 2) strL3 = "TR: PASS";
                        else if(i == 3) strL4 = "TR: PASS";
                        else if(i == 4) strL5 = "TR: PASS";
                        else if(i == 5) strL6 = "TR: PASS";
                        if(globalUserLimit->gLimitEdge[i] == SA_ON)
                        {
                            if(globalUserLimit->gLatestLimitEdgeResult[i] == SA_FAIL)
                            {
                                if(i == 0) strL1 = "TR EDGE: FAIL";
                                else if(i == 1) strL2 = "TR EDGE: FAIL";
                                else if(i == 2) strL3 = "TR EDGE: FAIL";
                                else if(i == 3) strL4 = "TR EDGE: FAIL";
                                else if(i == 4) strL5 = "TR EDGE: FAIL";
                                else if(i == 5) strL6 = "TR EDGE: FAIL";
                            }
                        }
                    }
                    else
                    {
                        if(i == 0) strL1 = "TR: FAIL";
                        else if(i == 1) strL2 = "TR: FAIL";
                        else if(i == 2) strL3 = "TR: FAIL";
                        else if(i == 3) strL4 = "TR: FAIL";
                        else if(i == 4) strL5 = "TR: FAIL";
                        else if(i == 5) strL6 = "TR: FAIL";
                    }
                }
                else
                {
                    if(i == 0) strL1 = "-- --";
                    else if(i == 1) strL2 = "-- --";
                    else if(i == 2) strL3 = "-- --";
                    else if(i == 3) strL4 = "-- --";
                    else if(i == 4) strL5 = "-- --";
                    else if(i == 5) strL6 = "-- --";
                }
            }
        }
        else
        {
            strL1 = "-- --";
            strL2 = "-- --";
            strL3 = "-- --";
            strL4 = "-- --";
            strL5 = "-- --";
            strL6 = "-- --";
        }

        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4 * 3 - 70,SPACE_BETWEEN_LINES * 2 + fm.height(),
                         fm.width(strL1), fm.height(), Qt::AlignRight, strL1);
        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4 * 3 - 70,SPACE_BETWEEN_LINES * 3 +fm.height() * 2,
                         fm.width(strL2), fm.height(), Qt::AlignRight, strL2);
        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4 * 3 - 70,SPACE_BETWEEN_LINES * 4 +fm.height() * 3,
                         fm.width(QString("%1 / %2").arg(strL3).arg(strL4)), fm.height(), Qt::AlignRight, QString("%1 / %2").arg(strL3).arg(strL4));
        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/4 * 3 - 70,SPACE_BETWEEN_LINES * 5 +fm.height() * 4,
                         fm.width(QString("%1 / %2").arg(strL5).arg(strL6)), fm.height(), Qt::AlignRight, QString("%1 / %2").arg(strL5).arg(strL6));
    }
#else //table_height = 58
    ChannelPowerTablePixmap.fill(QColor(72,72,72));
    QPainter painter(&ChannelPowerTablePixmap);

    quint32 maxStrFreqLen = 0;
    quint32 maxStrAmpLen  = 0;

    //draw pixmap title
    QFont font = QFont(QFont("Arial",10));
    font.setWeight(QFont::Bold);
    QPen pen(Qt::white);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setFont(font);
    QFontMetrics fm = painter.fontMetrics();

    painter.drawText(CHANNELPOWER_LEFT_MARGIN,SPACE_BETWEEN_LINES, fm.width("Total Channel Power"), fm.height(), Qt::AlignRight, "Total Channel Power");
    painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/3,SPACE_BETWEEN_LINES, fm.width("Channel Power"), fm.height(), Qt::AlignRight, "Channel Power");
    painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/3 * 2,SPACE_BETWEEN_LINES, fm.width("Band Width"), fm.height(), Qt::AlignRight, "Band Width");

    //draw pixmap content
    font.setWeight(QFont::Normal);
    painter.setFont(font);
    pen.setColor(QColor(250,210,120));
    pen.setWidth(1);
    painter.setPen(pen);
    fm = painter.fontMetrics();

    maxStrFreqLen = fm.width("-999.999999999 GHz");
    maxStrAmpLen  = fm.width("-99.99 dBm");

    QString strBandWidth = globalUserVariable->freqValueToQstring(globalUserVariable->gChannelBandwidth);
    QString strTotalPower = QString::number(globalUserVariable->dTotalPower, 'f', 2) + " dBm";
    QString strChannelPower = globalUserVariable->amptTransformToQstring(pcontrolInterface->getAmpUnit(),globalUserVariable->dPowerValue);

    //*****************draw value
    //Johnson 190321
    if(globalUserVariable->gTraceView[globalUserVariable->gTraceSelect] == SA_OFF)
    {
        painter.drawText(CHANNELPOWER_LEFT_MARGIN,SPACE_BETWEEN_LINES * 2 + fm.height(),maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/3,SPACE_BETWEEN_LINES * 2 + fm.height(),
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/3 * 2,SPACE_BETWEEN_LINES * 2 + fm.height(),
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
    }
    else
    {
        painter.drawText(CHANNELPOWER_LEFT_MARGIN,SPACE_BETWEEN_LINES * 2 + fm.height(),maxStrAmpLen, fm.height(), Qt::AlignRight, strTotalPower);
        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/3,SPACE_BETWEEN_LINES * 2 + fm.height(),
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strChannelPower);
        painter.drawText(CHANNELPOWER_LEFT_MARGIN + ChannelPowerTablePixmap.width()/3 * 2,SPACE_BETWEEN_LINES * 2 + fm.height(),
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
    }
#endif
}
void sa_widget_ChannelPowerTable::paintEvent(QPaintEvent *event)
{
    QStylePainter painter(this);
    painter.drawPixmap(0,0,ChannelPowerTablePixmap);
}
void sa_widget_ChannelPowerTable::setPixmapSize(qint32 mWidth,qint32 mHeight)
{
    ChannelPowerTablePixmap = ChannelPowerTablePixmap.scaled(mWidth,mHeight,Qt::IgnoreAspectRatio,Qt::FastTransformation);
}
