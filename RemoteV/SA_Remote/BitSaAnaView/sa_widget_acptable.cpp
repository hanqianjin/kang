#include "sa_widget_acptable.h"
#include "ui_sa_widget_acptable.h"

#include <QPainter>
#include <QStylePainter>
#include "sa_colordef.h"

#include "QDebug"
sa_widget_ACPTable::sa_widget_ACPTable(controlInterface &interface,user_variable &m_user_variable, user_limit &m_user_limit, QWidget *parent) :
    QWidget(parent),
    pcontrolInterface(&interface),
    globalUserVariable(&m_user_variable),
    globalUserLimit(&m_user_limit),
    ui(new Ui::sa_widget_ACPTable)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/);

    ui->setupUi(this);
    setProperty("status",qssMode[interface.GetDisplayMode()]);
    ACPTablePixmap = QPixmap(SMALLDRAW_WIDTH, ACP_TABLE_HEIGHT);
}

sa_widget_ACPTable::~sa_widget_ACPTable()
{
    delete ui;
}
void sa_widget_ACPTable::refreshAcpTable()
{
    refreshPixmap();
    repaint(0,0,ACPTablePixmap.width(),ACPTablePixmap.height());
}
void sa_widget_ACPTable::refreshPixmap()
{
#if 0
    ACPTablePixmap.fill(QColor(72,72,72));
    QPainter painter(&ACPTablePixmap);

    quint32 maxStrFreqLen = 0;
    quint32 maxStrAmpLen  = 0;

    //draw pixmap title
    QFont font = QFont(QFont("Arial",11));
    font.setWeight(QFont::Bold);
    QPen pen(Qt::white);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setFont(font);
    QFontMetrics fm = painter.fontMetrics();

    painter.drawText(ACP_LEFT_MARGIN,SPACE_BETWEEN_LINES, fm.width("Upper Measurements"), fm.height(), Qt::AlignRight, "Upper Measurements");
    painter.drawText(ACP_LEFT_MARGIN + ACPTablePixmap.width()/2,SPACE_BETWEEN_LINES, fm.width("Lower Measurements"),
                     fm.height(), Qt::AlignRight, "Lower Measurements");

    font = QFont(QFont("Arial",10));
    font.setWeight(QFont::Bold);
    painter.setFont(font);
    fm = painter.fontMetrics();

    painter.drawText(ACP_LEFT_MARGIN,SPACE_BETWEEN_LINES + fm.height() * 2 + SPACE_BETWEEN_LINES * 2,
                     fm.width("Channel"), fm.height(), Qt::AlignRight, "Channel");
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10,SPACE_BETWEEN_LINES + fm.height() * 2 + SPACE_BETWEEN_LINES * 2,
                     fm.width("Absolute"), fm.height(), Qt::AlignRight, "Absolute");
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 * 2,SPACE_BETWEEN_LINES + fm.height() * 2 + SPACE_BETWEEN_LINES * 2,
                     fm.width("Relative"), fm.height(), Qt::AlignRight, "Relative");
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 * 3,SPACE_BETWEEN_LINES + fm.height() * 2 + SPACE_BETWEEN_LINES * 2,
                     fm.width("Band Width"), fm.height(), Qt::AlignRight, "Band Width");
    painter.drawText(20 + ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 * 4,SPACE_BETWEEN_LINES + fm.height() * 2 + SPACE_BETWEEN_LINES * 2,
                     fm.width("Space"), fm.height(), Qt::AlignRight, "Space");

    painter.drawText(ACP_LEFT_MARGIN + ACPTablePixmap.width()/2,SPACE_BETWEEN_LINES + fm.height() * 2 + SPACE_BETWEEN_LINES * 2,
                     fm.width("Channel"), fm.height(), Qt::AlignRight, "Channel");
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width() * 6/10,SPACE_BETWEEN_LINES + fm.height() * 2 + SPACE_BETWEEN_LINES * 2,
                     fm.width("Absolute"), fm.height(), Qt::AlignRight, "Absolute");
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width() * 7/10,SPACE_BETWEEN_LINES + fm.height() * 2 + SPACE_BETWEEN_LINES * 2,
                     fm.width("Relative"), fm.height(), Qt::AlignRight, "Relative");
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width() * 8/10,SPACE_BETWEEN_LINES + fm.height() * 2 + SPACE_BETWEEN_LINES * 2,
                     fm.width("Band Width"), fm.height(), Qt::AlignRight, "Band Width");
    painter.drawText(20 + ACP_BETWEEN_COLUMN + ACPTablePixmap.width() * 9/10,SPACE_BETWEEN_LINES + fm.height() * 2 + SPACE_BETWEEN_LINES * 2,
                     fm.width("Space"), fm.height(), Qt::AlignRight, "Space");


    //draw pixmap content
    font.setWeight(QFont::Normal);
    painter.setFont(font);
    pen.setColor(QColor(250,210,120));
    pen.setWidth(1);
    painter.setPen(pen);
    fm = painter.fontMetrics();

    maxStrFreqLen = fm.width("-999.999999999 GHz");
    maxStrAmpLen  = fm.width("-99.99 dBm");

    QString strBandWidth     = globalUserVariable->freqValueToQstring(globalUserVariable->gChannelBandwidth);
    QString strSpace         = globalUserVariable->freqValueToQstring(globalUserVariable->gChannelSpacing);

    QString strLeftRelative  = QString::number(globalUserVariable->dPowerValue_ACPL - globalUserVariable->dPowerValue_ACPM, 'f', 2) + " dB";
    QString strLeftAbsolute  = globalUserVariable->amptTransformToQstring(pcontrolInterface->getAmpUnit(),globalUserVariable->dPowerValue_ACPL);
    QString strMidRelative   = "0.00 dB";
    QString strMidAbsolute   = globalUserVariable->amptTransformToQstring(pcontrolInterface->getAmpUnit(),globalUserVariable->dPowerValue_ACPM);
    QString strRightRelative = QString::number(globalUserVariable->dPowerValue_ACPR - globalUserVariable->dPowerValue_ACPM, 'f', 2) + " dB";
    QString strRightAbsolute = globalUserVariable->amptTransformToQstring(pcontrolInterface->getAmpUnit(),globalUserVariable->dPowerValue_ACPR);

    //Upper Measurements ---- left channel
    painter.drawText(ACP_LEFT_MARGIN,SPACE_BETWEEN_LINES + fm.height() * 3 + SPACE_BETWEEN_LINES * 2 + 5,
                     fm.width("Left"), fm.height(), Qt::AlignRight, "Left");
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 - 10,SPACE_BETWEEN_LINES + fm.height() * 3 + SPACE_BETWEEN_LINES * 2 + 5,
                     maxStrAmpLen, fm.height(), Qt::AlignRight, strLeftAbsolute);
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 * 2 - 15,SPACE_BETWEEN_LINES + fm.height() * 3 + SPACE_BETWEEN_LINES * 2 + 5,
                     maxStrAmpLen, fm.height(), Qt::AlignRight, strLeftRelative);
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 * 3,SPACE_BETWEEN_LINES + fm.height() * 3 + SPACE_BETWEEN_LINES * 2 + 5,
                     maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
    painter.drawText(20 + ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 * 4,SPACE_BETWEEN_LINES + fm.height() * 3 + SPACE_BETWEEN_LINES * 2 + 5,
                     maxStrFreqLen, fm.height(), Qt::AlignLeft, strSpace);
    //Upper Measurements ---- middle channel
    painter.drawText(ACP_LEFT_MARGIN,SPACE_BETWEEN_LINES + fm.height() * 4 + SPACE_BETWEEN_LINES * 2 + 5*2,
                     fm.width("Middle"), fm.height(), Qt::AlignRight, "Middle");
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 - 10,SPACE_BETWEEN_LINES + fm.height() * 4 + SPACE_BETWEEN_LINES * 2 + 5*2,
                     maxStrAmpLen, fm.height(), Qt::AlignRight, strMidAbsolute);
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 * 2 - 15,SPACE_BETWEEN_LINES + fm.height() * 4 + SPACE_BETWEEN_LINES * 2 + 5*2,
                     maxStrAmpLen, fm.height(), Qt::AlignRight, strMidRelative);
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 * 3,SPACE_BETWEEN_LINES + fm.height() * 4 + SPACE_BETWEEN_LINES * 2 + 5*2,
                     maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
    painter.drawText(20 + ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 * 4,SPACE_BETWEEN_LINES + fm.height() * 4 + SPACE_BETWEEN_LINES * 2 + 5*2,
                     maxStrFreqLen, fm.height(), Qt::AlignLeft, strSpace);
    //Upper Measurements ---- right channel
    painter.drawText(ACP_LEFT_MARGIN,SPACE_BETWEEN_LINES + fm.height() * 5 + SPACE_BETWEEN_LINES * 2 + 5*3,
                     fm.width("Right"), fm.height(), Qt::AlignRight, "Right");
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 - 10,SPACE_BETWEEN_LINES + fm.height() * 5 + SPACE_BETWEEN_LINES * 2 + 5*3,
                     maxStrAmpLen, fm.height(), Qt::AlignRight, strRightAbsolute);
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 * 2 - 15,SPACE_BETWEEN_LINES + fm.height() * 5 + SPACE_BETWEEN_LINES * 2 + 5*3,
                     maxStrAmpLen, fm.height(), Qt::AlignRight, strRightRelative);
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 * 3,SPACE_BETWEEN_LINES + fm.height() * 5 + SPACE_BETWEEN_LINES * 2 + 5*3,
                     maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
    painter.drawText(20 + ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 * 4,SPACE_BETWEEN_LINES + fm.height() * 5 + SPACE_BETWEEN_LINES * 2 + 5*3,
                     maxStrFreqLen, fm.height(), Qt::AlignLeft, strSpace);


    //Lower Measurements ---- left channel
    painter.drawText(ACP_LEFT_MARGIN + ACPTablePixmap.width()/2,SPACE_BETWEEN_LINES + fm.height() * 3 + SPACE_BETWEEN_LINES * 2 + 5,
                     fm.width("Left"), fm.height(), Qt::AlignRight, "Left");
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 * 6 - 10,SPACE_BETWEEN_LINES + fm.height() * 3 + SPACE_BETWEEN_LINES * 2 + 5,
                     maxStrAmpLen, fm.height(), Qt::AlignRight, strLeftAbsolute);
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 * 7 - 15,SPACE_BETWEEN_LINES + fm.height() * 3 + SPACE_BETWEEN_LINES * 2 + 5,
                     maxStrAmpLen, fm.height(), Qt::AlignRight, strLeftRelative);
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 * 8,SPACE_BETWEEN_LINES + fm.height() * 3 + SPACE_BETWEEN_LINES * 2 + 5,
                     maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
    painter.drawText(20 + ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 * 9,SPACE_BETWEEN_LINES + fm.height() * 3 + SPACE_BETWEEN_LINES * 2 + 5,
                     maxStrFreqLen, fm.height(), Qt::AlignLeft, strSpace);
    //Lower Measurements ---- middle channel
    painter.drawText(ACP_LEFT_MARGIN + ACPTablePixmap.width()/2,SPACE_BETWEEN_LINES + fm.height() * 4 + SPACE_BETWEEN_LINES * 2 + 5*2,
                     fm.width("Middle"), fm.height(), Qt::AlignRight, "Middle");
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 * 6 - 10,SPACE_BETWEEN_LINES + fm.height() * 4 + SPACE_BETWEEN_LINES * 2 + 5*2,
                     maxStrAmpLen, fm.height(), Qt::AlignRight, strMidAbsolute);
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 * 7 - 15,SPACE_BETWEEN_LINES + fm.height() * 4 + SPACE_BETWEEN_LINES * 2 + 5*2,
                     maxStrAmpLen, fm.height(), Qt::AlignRight, strMidRelative);
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 * 8,SPACE_BETWEEN_LINES + fm.height() * 4 + SPACE_BETWEEN_LINES * 2 + 5*2,
                     maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
    painter.drawText(20 + ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 * 9,SPACE_BETWEEN_LINES + fm.height() * 4 + SPACE_BETWEEN_LINES * 2 + 5*2,
                     maxStrFreqLen, fm.height(), Qt::AlignLeft, strSpace);
    //Lower Measurements ---- right channel
    painter.drawText(ACP_LEFT_MARGIN + ACPTablePixmap.width()/2,SPACE_BETWEEN_LINES + fm.height() * 5 + SPACE_BETWEEN_LINES * 2 + 5*3,
                     fm.width("Right"), fm.height(), Qt::AlignRight, "Right");
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 * 6 - 10,SPACE_BETWEEN_LINES + fm.height() * 5 + SPACE_BETWEEN_LINES * 2 + 5*3,
                     maxStrAmpLen, fm.height(), Qt::AlignRight, strRightAbsolute);
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 * 7 - 15,SPACE_BETWEEN_LINES + fm.height() * 5 + SPACE_BETWEEN_LINES * 2 + 5*3,
                     maxStrAmpLen, fm.height(), Qt::AlignRight, strRightRelative);
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 * 8,SPACE_BETWEEN_LINES + fm.height() * 5 + SPACE_BETWEEN_LINES * 2 + 5*3,
                     maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
    painter.drawText(20 + ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/10 * 9,SPACE_BETWEEN_LINES + fm.height() * 5 + SPACE_BETWEEN_LINES * 2 + 5*3,
                     maxStrFreqLen, fm.height(), Qt::AlignLeft, strSpace);
#else
    qint32 colorMode = globalUserVariable->gDisplayMode;
    QColor TableBgColor = TableBackgroundColor[colorMode];
    QColor fontColor = TableFontColor[colorMode];
    QColor curFontColor = TableCurFontColor[colorMode];

    ACPTablePixmap.fill(TableBgColor);
    QPainter painter(&ACPTablePixmap);

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

    painter.drawText(ACP_LEFT_MARGIN,SPACE_BETWEEN_LINES,fm.width("Channel"), fm.height(), Qt::AlignRight, "Channel");
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5,SPACE_BETWEEN_LINES,fm.width("Absolute"), fm.height(), Qt::AlignRight, "Absolute");
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5 * 2,SPACE_BETWEEN_LINES,fm.width("Relative"), fm.height(), Qt::AlignRight, "Relative");
    painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5 * 3,SPACE_BETWEEN_LINES,fm.width("Band Width"), fm.height(), Qt::AlignRight, "Band Width");
    painter.drawText(20 + ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5 * 4,SPACE_BETWEEN_LINES,fm.width("Space"), fm.height(), Qt::AlignRight, "Space");
    //draw pixmap content
    font.setWeight(QFont::Normal);
    painter.setFont(font);
    pen.setColor(curFontColor);
    pen.setWidth(1);
    painter.setPen(pen);
    fm = painter.fontMetrics();

    maxStrFreqLen = fm.width("-999.999999999 GHz");
    maxStrAmpLen  = fm.width("-99.99 dBm");

    QString strBandWidth     = globalUserVariable->freqValueToQstring(globalUserVariable->gChannelBandwidth);
    QString strSpace         = globalUserVariable->freqValueToQstring(globalUserVariable->gChannelSpacing);

    QString strLeftRelative  = QString::number(globalUserVariable->dPowerValue_ACPL - globalUserVariable->dPowerValue_ACPM, 'f', 2) + " dBc";
    QString strLeftAbsolute  = globalUserVariable->amptTransformToQstring(pcontrolInterface->getAmpUnit(),globalUserVariable->dPowerValue_ACPL);
    QString strMidRelative   = "0.00 dBc";
    QString strMidAbsolute   = globalUserVariable->amptTransformToQstring(pcontrolInterface->getAmpUnit(),globalUserVariable->dPowerValue_ACPM);
    QString strRightRelative = QString::number(globalUserVariable->dPowerValue_ACPR - globalUserVariable->dPowerValue_ACPM, 'f', 2) + " dBc";
    QString strRightAbsolute = globalUserVariable->amptTransformToQstring(pcontrolInterface->getAmpUnit(),globalUserVariable->dPowerValue_ACPR);

    //Johnson 190321
    if(globalUserVariable->gTraceView[globalUserVariable->gTraceSelect] == SA_OFF)
    {
        //Upper Measurements ---- left channel
        painter.drawText(ACP_LEFT_MARGIN,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,fm.width("Lower"), fm.height(), Qt::AlignLeft, "Lower");
        painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5 * 2,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5 * 3,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(20 + ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5 * 4,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
        //Upper Measurements ---- middle channel
        painter.drawText(ACP_LEFT_MARGIN,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,fm.width("Main"), fm.height(), Qt::AlignLeft, "Main");
        painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5 * 2,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5 * 3,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(20 + ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5 * 4,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
        //Upper Measurements ---- right channel
        painter.drawText(ACP_LEFT_MARGIN,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,fm.width("Upper"), fm.height(), Qt::AlignLeft, "Upper");
        painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5 * 2,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5 * 3,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(20 + ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5 * 4,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
    }
    else
    {
        //Upper Measurements ---- left channel
        painter.drawText(ACP_LEFT_MARGIN,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,fm.width("Lower"), fm.height(), Qt::AlignRight, "Lower");
        painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5 - 10,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strLeftAbsolute);
        painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5 * 2 - 15,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strLeftRelative);
        painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5 * 3,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
        painter.drawText(20 + ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5 * 4,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strSpace);
        //Upper Measurements ---- middle channel
        painter.drawText(ACP_LEFT_MARGIN,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,fm.width("Main"), fm.height(), Qt::AlignRight, "Main");
        painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5 - 10,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strMidAbsolute);
        painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5 * 2 - 15,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strMidRelative);
        painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5 * 3,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
        painter.drawText(20 + ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5 * 4,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strSpace);
        //Upper Measurements ---- right channel
        painter.drawText(ACP_LEFT_MARGIN,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,fm.width("Upper"), fm.height(), Qt::AlignRight, "Upper");
        painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5 - 10,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strRightAbsolute);
        painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5 * 2 - 15,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strRightRelative);
        painter.drawText(ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5 * 3,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
        painter.drawText(20 + ACP_BETWEEN_COLUMN + ACPTablePixmap.width()/5 * 4,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strSpace);
    }
#endif
}
void sa_widget_ACPTable::paintEvent(QPaintEvent *event)
{
    QStylePainter painter(this);
    painter.drawPixmap(0,0,ACPTablePixmap);
}
void sa_widget_ACPTable::setPixmapSize(qint32 mWidth,qint32 mHeight)
{
    ACPTablePixmap = ACPTablePixmap.scaled(mWidth,mHeight,Qt::IgnoreAspectRatio,Qt::FastTransformation);
}
