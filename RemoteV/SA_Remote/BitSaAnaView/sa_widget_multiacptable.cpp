#include "sa_widget_multiacptable.h"
#include "ui_sa_widget_multiacptable.h"

#include <QPainter>
#include <QStylePainter>
#include "sa_colordef.h"

sa_widget_MultiACPTable::sa_widget_MultiACPTable(controlInterface &interface,user_variable &m_user_variable, user_limit &m_user_limit, QWidget *parent) :
    QWidget(parent),
    pcontrolInterface(&interface),
    globalUserVariable(&m_user_variable),
    globalUserLimit(&m_user_limit),
    ui(new Ui::sa_widget_MultiACPTable)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/);

    ui->setupUi(this);

    MultiACPTablePixmap = QPixmap(SMALLDRAW_WIDTH, ACP_TABLE_HEIGHT);
}

sa_widget_MultiACPTable::~sa_widget_MultiACPTable()
{
    delete ui;
}
void sa_widget_MultiACPTable::refreshMultiAcpTable()
{
    refreshPixmap();
    repaint(0,0,MultiACPTablePixmap.width(),MultiACPTablePixmap.height());
}
void sa_widget_MultiACPTable::refreshPixmap()
{
#if 0
    MultiACPTablePixmap.fill(QColor(72,72,72));
    QPainter painter(&MultiACPTablePixmap);

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

    painter.drawText(MULTIACP_LEFT_MARGIN,SPACE_BETWEEN_LINES, fm.width("Upper Measurements"), fm.height(), Qt::AlignRight, "Upper Measurements");
    painter.drawText(MULTIACP_LEFT_MARGIN + MultiACPTablePixmap.width()/2,SPACE_BETWEEN_LINES, fm.width("Lower Measurements"),
                     fm.height(), Qt::AlignRight, "Lower Measurements");

    font = QFont(QFont("Arial",10));
    font.setWeight(QFont::Bold);
    painter.setFont(font);
    fm = painter.fontMetrics();

    painter.drawText(MULTIACP_LEFT_MARGIN,SPACE_BETWEEN_LINES + fm.height() * 2 + SPACE_BETWEEN_LINES * 2,
                     fm.width("Channel"), fm.height(), Qt::AlignRight, "Channel");
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10,SPACE_BETWEEN_LINES + fm.height() * 2 + SPACE_BETWEEN_LINES * 2,
                     fm.width("Absolute"), fm.height(), Qt::AlignRight, "Absolute");
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 * 2,SPACE_BETWEEN_LINES + fm.height() * 2 + SPACE_BETWEEN_LINES * 2,
                     fm.width("Relative"), fm.height(), Qt::AlignRight, "Relative");
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 * 3,SPACE_BETWEEN_LINES + fm.height() * 2 + SPACE_BETWEEN_LINES * 2,
                     fm.width("Band Width"), fm.height(), Qt::AlignRight, "Band Width");
    painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 * 4,SPACE_BETWEEN_LINES + fm.height() * 2 + SPACE_BETWEEN_LINES * 2,
                     fm.width("Space"), fm.height(), Qt::AlignRight, "Space");

    painter.drawText(MULTIACP_LEFT_MARGIN + MultiACPTablePixmap.width()/2,SPACE_BETWEEN_LINES + fm.height() * 2 + SPACE_BETWEEN_LINES * 2,
                     fm.width("Channel"), fm.height(), Qt::AlignRight, "Channel");
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width() * 6/10,SPACE_BETWEEN_LINES + fm.height() * 2 + SPACE_BETWEEN_LINES * 2,
                     fm.width("Absolute"), fm.height(), Qt::AlignRight, "Absolute");
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width() * 7/10,SPACE_BETWEEN_LINES + fm.height() * 2 + SPACE_BETWEEN_LINES * 2,
                     fm.width("Relative"), fm.height(), Qt::AlignRight, "Relative");
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width() * 8/10,SPACE_BETWEEN_LINES + fm.height() * 2 + SPACE_BETWEEN_LINES * 2,
                     fm.width("Band Width"), fm.height(), Qt::AlignRight, "Band Width");
    painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width() * 9/10,SPACE_BETWEEN_LINES + fm.height() * 2 + SPACE_BETWEEN_LINES * 2,
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
    painter.drawText(MULTIACP_LEFT_MARGIN,SPACE_BETWEEN_LINES + fm.height() * 3 + SPACE_BETWEEN_LINES * 2 + 5,
                     fm.width("Left"), fm.height(), Qt::AlignRight, "Left");
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 - 10,SPACE_BETWEEN_LINES + fm.height() * 3 + SPACE_BETWEEN_LINES * 2 + 5,
                     maxStrAmpLen, fm.height(), Qt::AlignRight, strLeftAbsolute);
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 * 2 - 15,SPACE_BETWEEN_LINES + fm.height() * 3 + SPACE_BETWEEN_LINES * 2 + 5,
                     maxStrAmpLen, fm.height(), Qt::AlignRight, strLeftRelative);
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 * 3,SPACE_BETWEEN_LINES + fm.height() * 3 + SPACE_BETWEEN_LINES * 2 + 5,
                     maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
    painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 * 4,SPACE_BETWEEN_LINES + fm.height() * 3 + SPACE_BETWEEN_LINES * 2 + 5,
                     maxStrFreqLen, fm.height(), Qt::AlignLeft, strSpace);
    //Upper Measurements ---- middle channel
    painter.drawText(MULTIACP_LEFT_MARGIN,SPACE_BETWEEN_LINES + fm.height() * 4 + SPACE_BETWEEN_LINES * 2 + 5*2,
                     fm.width("Middle"), fm.height(), Qt::AlignRight, "Middle");
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 - 10,SPACE_BETWEEN_LINES + fm.height() * 4 + SPACE_BETWEEN_LINES * 2 + 5*2,
                     maxStrAmpLen, fm.height(), Qt::AlignRight, strMidAbsolute);
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 * 2 - 15,SPACE_BETWEEN_LINES + fm.height() * 4 + SPACE_BETWEEN_LINES * 2 + 5*2,
                     maxStrAmpLen, fm.height(), Qt::AlignRight, strMidRelative);
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 * 3,SPACE_BETWEEN_LINES + fm.height() * 4 + SPACE_BETWEEN_LINES * 2 + 5*2,
                     maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
    painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 * 4,SPACE_BETWEEN_LINES + fm.height() * 4 + SPACE_BETWEEN_LINES * 2 + 5*2,
                     maxStrFreqLen, fm.height(), Qt::AlignLeft, strSpace);
    //Upper Measurements ---- right channel
    painter.drawText(MULTIACP_LEFT_MARGIN,SPACE_BETWEEN_LINES + fm.height() * 5 + SPACE_BETWEEN_LINES * 2 + 5*3,
                     fm.width("Right"), fm.height(), Qt::AlignRight, "Right");
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 - 10,SPACE_BETWEEN_LINES + fm.height() * 5 + SPACE_BETWEEN_LINES * 2 + 5*3,
                     maxStrAmpLen, fm.height(), Qt::AlignRight, strRightAbsolute);
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 * 2 - 15,SPACE_BETWEEN_LINES + fm.height() * 5 + SPACE_BETWEEN_LINES * 2 + 5*3,
                     maxStrAmpLen, fm.height(), Qt::AlignRight, strRightRelative);
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 * 3,SPACE_BETWEEN_LINES + fm.height() * 5 + SPACE_BETWEEN_LINES * 2 + 5*3,
                     maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
    painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 * 4,SPACE_BETWEEN_LINES + fm.height() * 5 + SPACE_BETWEEN_LINES * 2 + 5*3,
                     maxStrFreqLen, fm.height(), Qt::AlignLeft, strSpace);


    //Lower Measurements ---- left channel
    painter.drawText(MULTIACP_LEFT_MARGIN + MultiACPTablePixmap.width()/2,SPACE_BETWEEN_LINES + fm.height() * 3 + SPACE_BETWEEN_LINES * 2 + 5,
                     fm.width("Left"), fm.height(), Qt::AlignRight, "Left");
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 * 6 - 10,SPACE_BETWEEN_LINES + fm.height() * 3 + SPACE_BETWEEN_LINES * 2 + 5,
                     maxStrAmpLen, fm.height(), Qt::AlignRight, strLeftAbsolute);
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 * 7 - 15,SPACE_BETWEEN_LINES + fm.height() * 3 + SPACE_BETWEEN_LINES * 2 + 5,
                     maxStrAmpLen, fm.height(), Qt::AlignRight, strLeftRelative);
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 * 8,SPACE_BETWEEN_LINES + fm.height() * 3 + SPACE_BETWEEN_LINES * 2 + 5,
                     maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
    painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 * 9,SPACE_BETWEEN_LINES + fm.height() * 3 + SPACE_BETWEEN_LINES * 2 + 5,
                     maxStrFreqLen, fm.height(), Qt::AlignLeft, strSpace);
    //Lower Measurements ---- middle channel
    painter.drawText(MULTIACP_LEFT_MARGIN + MultiACPTablePixmap.width()/2,SPACE_BETWEEN_LINES + fm.height() * 4 + SPACE_BETWEEN_LINES * 2 + 5*2,
                     fm.width("Middle"), fm.height(), Qt::AlignRight, "Middle");
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 * 6 - 10,SPACE_BETWEEN_LINES + fm.height() * 4 + SPACE_BETWEEN_LINES * 2 + 5*2,
                     maxStrAmpLen, fm.height(), Qt::AlignRight, strMidAbsolute);
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 * 7 - 15,SPACE_BETWEEN_LINES + fm.height() * 4 + SPACE_BETWEEN_LINES * 2 + 5*2,
                     maxStrAmpLen, fm.height(), Qt::AlignRight, strMidRelative);
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 * 8,SPACE_BETWEEN_LINES + fm.height() * 4 + SPACE_BETWEEN_LINES * 2 + 5*2,
                     maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
    painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 * 9,SPACE_BETWEEN_LINES + fm.height() * 4 + SPACE_BETWEEN_LINES * 2 + 5*2,
                     maxStrFreqLen, fm.height(), Qt::AlignLeft, strSpace);
    //Lower Measurements ---- right channel
    painter.drawText(MULTIACP_LEFT_MARGIN + MultiACPTablePixmap.width()/2,SPACE_BETWEEN_LINES + fm.height() * 5 + SPACE_BETWEEN_LINES * 2 + 5*3,
                     fm.width("Right"), fm.height(), Qt::AlignRight, "Right");
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 * 6 - 10,SPACE_BETWEEN_LINES + fm.height() * 5 + SPACE_BETWEEN_LINES * 2 + 5*3,
                     maxStrAmpLen, fm.height(), Qt::AlignRight, strRightAbsolute);
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 * 7 - 15,SPACE_BETWEEN_LINES + fm.height() * 5 + SPACE_BETWEEN_LINES * 2 + 5*3,
                     maxStrAmpLen, fm.height(), Qt::AlignRight, strRightRelative);
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 * 8,SPACE_BETWEEN_LINES + fm.height() * 5 + SPACE_BETWEEN_LINES * 2 + 5*3,
                     maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
    painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/10 * 9,SPACE_BETWEEN_LINES + fm.height() * 5 + SPACE_BETWEEN_LINES * 2 + 5*3,
                     maxStrFreqLen, fm.height(), Qt::AlignLeft, strSpace);
#else

    qint32 colorMode = globalUserVariable->gDisplayMode;
    QColor TableBgColor = TableBackgroundColor[colorMode];
    QColor fontColor = TableFontColor[colorMode];
    QColor curFontColor = TableCurFontColor[colorMode];

    MultiACPTablePixmap.fill(TableBgColor);
    QPainter painter(&MultiACPTablePixmap);

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

    painter.drawText(MULTIACP_LEFT_MARGIN,SPACE_BETWEEN_LINES,fm.width("Channel"), fm.height(), Qt::AlignRight, "Channel");
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5,SPACE_BETWEEN_LINES,fm.width("Absolute"), fm.height(), Qt::AlignRight, "Absolute");
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 2,SPACE_BETWEEN_LINES,fm.width("Relative"), fm.height(), Qt::AlignRight, "Relative");
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 3,SPACE_BETWEEN_LINES,fm.width("Band Width"), fm.height(), Qt::AlignRight, "Band Width");
    painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 4,SPACE_BETWEEN_LINES,fm.width("Space"), fm.height(), Qt::AlignRight, "Space");
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

    QString strFarLeftRelative = QString::number(globalUserVariable->dPowerValue_MultiACPFL - globalUserVariable->dPowerValue_MultiACPM, 'f', 2) + " dBc";
    QString strFarLeftAbsolute  = globalUserVariable->amptTransformToQstring(pcontrolInterface->getAmpUnit(),globalUserVariable->dPowerValue_MultiACPFL);
    QString strLeftRelative  = QString::number(globalUserVariable->dPowerValue_MultiACPL - globalUserVariable->dPowerValue_MultiACPM, 'f', 2) + " dBc";
    QString strLeftAbsolute  = globalUserVariable->amptTransformToQstring(pcontrolInterface->getAmpUnit(),globalUserVariable->dPowerValue_MultiACPL);
    QString strMidRelative   = "0.00 dBc";
    QString strMidAbsolute   = globalUserVariable->amptTransformToQstring(pcontrolInterface->getAmpUnit(),globalUserVariable->dPowerValue_MultiACPM);
    QString strRightRelative = QString::number(globalUserVariable->dPowerValue_MultiACPR - globalUserVariable->dPowerValue_MultiACPM, 'f', 2) + " dBc";
    QString strRightAbsolute = globalUserVariable->amptTransformToQstring(pcontrolInterface->getAmpUnit(),globalUserVariable->dPowerValue_MultiACPR);
    QString strFarRightRelative = QString::number(globalUserVariable->dPowerValue_MultiACPFR - globalUserVariable->dPowerValue_MultiACPM, 'f', 2) + " dBc";
    QString strFarRightAbsolute = globalUserVariable->amptTransformToQstring(pcontrolInterface->getAmpUnit(),globalUserVariable->dPowerValue_MultiACPFR);

    //Johnson 190321
    if(globalUserVariable->gTraceView[globalUserVariable->gTraceSelect] == SA_OFF)
    {
        //Upper Measurements ---- left channel
        painter.drawText(MULTIACP_LEFT_MARGIN,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,fm.width("Far Left"), fm.height(), Qt::AlignLeft, "Far Left");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 2,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 3,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 4,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");

        painter.drawText(MULTIACP_LEFT_MARGIN,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,fm.width("Left"), fm.height(), Qt::AlignLeft, "Left");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 2,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 3,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 4,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
        //Upper Measurements ---- middle channel
        painter.drawText(MULTIACP_LEFT_MARGIN,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,fm.width("Main"), fm.height(), Qt::AlignLeft, "Main");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 2,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 3,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 4,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
        //Upper Measurements ---- right channel
        painter.drawText(MULTIACP_LEFT_MARGIN,fm.height()*4 + SPACE_BETWEEN_LINES * 5 - 5,fm.width("Right"), fm.height(), Qt::AlignLeft, "Right");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5,fm.height()*4 + SPACE_BETWEEN_LINES * 5 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 2,fm.height()*4 + SPACE_BETWEEN_LINES * 5 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 3,fm.height()*4 + SPACE_BETWEEN_LINES * 5 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 4,fm.height()*4 + SPACE_BETWEEN_LINES * 5 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");  

        painter.drawText(MULTIACP_LEFT_MARGIN,fm.height()*5 + SPACE_BETWEEN_LINES * 6 - 5,fm.width("Far Right"), fm.height(), Qt::AlignLeft, "Far Right");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5,fm.height()*5 + SPACE_BETWEEN_LINES * 6 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 2,fm.height()*5 + SPACE_BETWEEN_LINES * 6 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 3,fm.height()*5 + SPACE_BETWEEN_LINES * 6 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 4,fm.height()*5 + SPACE_BETWEEN_LINES * 6 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
    }
    else
    {
        //Upper Measurements ---- left channel
        painter.drawText(MULTIACP_LEFT_MARGIN,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,fm.width("Far Left"), fm.height(), Qt::AlignRight, "Far Left");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 - 10,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strFarLeftAbsolute);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 2 - 15,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strFarLeftRelative);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 3,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
        painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 4,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strSpace);

        painter.drawText(MULTIACP_LEFT_MARGIN,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,fm.width("Left"), fm.height(), Qt::AlignRight, "Left");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 - 10,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strLeftAbsolute);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 2 - 15,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strLeftRelative);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 3,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
        painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 4,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strSpace);
        //Upper Measurements ---- middle channel
        painter.drawText(MULTIACP_LEFT_MARGIN,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,fm.width("Main"), fm.height(), Qt::AlignRight, "Main");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 - 10,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strMidAbsolute);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 2 - 15,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strMidRelative);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 3,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
        painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 4,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strSpace);
        //Upper Measurements ---- right channel
        painter.drawText(MULTIACP_LEFT_MARGIN,fm.height()*4 + SPACE_BETWEEN_LINES * 5 - 5,fm.width("Right"), fm.height(), Qt::AlignRight, "Right");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 - 10,fm.height()*4 + SPACE_BETWEEN_LINES * 5 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strRightAbsolute);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 2 - 15,fm.height()*4 + SPACE_BETWEEN_LINES * 5 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strRightRelative);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 3,fm.height()*4 + SPACE_BETWEEN_LINES * 5 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
        painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 4,fm.height()*4 + SPACE_BETWEEN_LINES * 5 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strSpace);

        painter.drawText(MULTIACP_LEFT_MARGIN,fm.height()*5 + SPACE_BETWEEN_LINES * 6 - 5,fm.width("Far Right"), fm.height(), Qt::AlignRight, "Far Right");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 - 10,fm.height()*5 + SPACE_BETWEEN_LINES * 6 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strFarRightAbsolute);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 2 - 15,fm.height()*5 + SPACE_BETWEEN_LINES * 6 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strFarRightRelative);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 3,fm.height()*5 + SPACE_BETWEEN_LINES * 6 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
        painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 4,fm.height()*5 + SPACE_BETWEEN_LINES * 6 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strSpace);
    }
#endif
}
void sa_widget_MultiACPTable::paintEvent(QPaintEvent *event)
{
    QStylePainter painter(this);
    painter.drawPixmap(0,0,MultiACPTablePixmap);
}
void sa_widget_MultiACPTable::setPixmapSize(qint32 mWidth,qint32 mHeight)
{
    MultiACPTablePixmap = MultiACPTablePixmap.scaled(mWidth,mHeight,Qt::IgnoreAspectRatio,Qt::FastTransformation);
}
