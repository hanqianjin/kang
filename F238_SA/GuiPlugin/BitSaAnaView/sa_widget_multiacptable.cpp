#include "sa_widget_multiacptable.h"
#include "ui_sa_widget_multiacptable.h"

#include <QPainter>
#include <QStylePainter>
#include "sa_colordef.h"

#define MUTI_ACP_LEFT_SHIFT 50

sa_widget_MultiACPTable::sa_widget_MultiACPTable(controlInterface &interface,user_variable &m_user_variable, user_limit &m_user_limit, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sa_widget_MultiACPTable)
{
    pcontrolInterface = &interface;
    globalUserVariable = &m_user_variable;
    globalUserLimit = &m_user_limit;

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
#endif

#if 0//Johnson 20200511

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
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 - MUTI_ACP_LEFT_SHIFT,SPACE_BETWEEN_LINES,fm.width("Absolute"), fm.height(), Qt::AlignRight, "Absolute");
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 2 - MUTI_ACP_LEFT_SHIFT * 2,SPACE_BETWEEN_LINES,fm.width("Relative"), fm.height(), Qt::AlignRight, "Relative");
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 3 - MUTI_ACP_LEFT_SHIFT * 3,SPACE_BETWEEN_LINES,fm.width("Bandwidth"), fm.height(), Qt::AlignRight, "Bandwidth");
    painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 4 - MUTI_ACP_LEFT_SHIFT * 4,SPACE_BETWEEN_LINES,fm.width("Space"), fm.height(), Qt::AlignRight, "Space");
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 5 - MUTI_ACP_LEFT_SHIFT * 5,SPACE_BETWEEN_LINES,fm.width("Limit"), fm.height(), Qt::AlignRight, "Limit");
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 6 - MUTI_ACP_LEFT_SHIFT * 6,SPACE_BETWEEN_LINES,fm.width("Pass/Fail"), fm.height(), Qt::AlignRight, "Pass/Fail");
    //draw pixmap content
    font.setWeight(QFont::Normal);
    painter.setFont(font);
    pen.setColor(curFontColor);    pen.setWidth(1);
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

    QString strMAINCHLimit = QString::number(globalUserLimit->gUpperLimit, 'f', 2) + " dBm";
    QString strADJCHLimit = QString::number(globalUserLimit->gLowerLimit, 'f', 2) + " dBc";
    QString strALTCHLimit = QString::number(globalUserLimit->gATLdBcLimit, 'f', 2) + " dBc";

    //Johnson 190321
    if(globalUserVariable->gTraceView[globalUserVariable->gTraceSelect] == SA_OFF)
    {
        //Upper Measurements ---- left channel
        painter.drawText(MULTIACP_LEFT_MARGIN,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,fm.width("Far Left"), fm.height(), Qt::AlignLeft, "Far Left");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 - MUTI_ACP_LEFT_SHIFT,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 2 - MUTI_ACP_LEFT_SHIFT * 2,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 3 - MUTI_ACP_LEFT_SHIFT * 3,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 4 - MUTI_ACP_LEFT_SHIFT * 4,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 5 - MUTI_ACP_LEFT_SHIFT * 5,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         fm.width(strALTCHLimit), fm.height(), Qt::AlignLeft, strALTCHLimit);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 6 - MUTI_ACP_LEFT_SHIFT * 6,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         fm.width("-- --"), fm.height(), Qt::AlignLeft, "-- --");

        painter.drawText(MULTIACP_LEFT_MARGIN,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,fm.width("Left"), fm.height(), Qt::AlignLeft, "Left");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 - MUTI_ACP_LEFT_SHIFT,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 2 - MUTI_ACP_LEFT_SHIFT * 2,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 3 - MUTI_ACP_LEFT_SHIFT * 3,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 4 - MUTI_ACP_LEFT_SHIFT * 4,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 5 - MUTI_ACP_LEFT_SHIFT * 5,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         fm.width(strADJCHLimit), fm.height(), Qt::AlignLeft, strADJCHLimit);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 6 - MUTI_ACP_LEFT_SHIFT * 6,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         fm.width("-- --"), fm.height(), Qt::AlignLeft, "-- --");
        //Upper Measurements ---- middle channel
        painter.drawText(MULTIACP_LEFT_MARGIN,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,fm.width("Main"), fm.height(), Qt::AlignLeft, "Main");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 - MUTI_ACP_LEFT_SHIFT,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 2 - MUTI_ACP_LEFT_SHIFT * 2,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 3 - MUTI_ACP_LEFT_SHIFT * 3,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 4 - MUTI_ACP_LEFT_SHIFT * 4,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 5 - MUTI_ACP_LEFT_SHIFT * 5,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         fm.width(strMAINCHLimit), fm.height(), Qt::AlignLeft, strMAINCHLimit);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 6 - MUTI_ACP_LEFT_SHIFT * 6,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         fm.width("-- --"), fm.height(), Qt::AlignLeft, "-- --");
        //Upper Measurements ---- right channel
        painter.drawText(MULTIACP_LEFT_MARGIN,fm.height()*4 + SPACE_BETWEEN_LINES * 5 - 5,fm.width("Right"), fm.height(), Qt::AlignLeft, "Right");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 - MUTI_ACP_LEFT_SHIFT,fm.height()*4 + SPACE_BETWEEN_LINES * 5 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 2 - MUTI_ACP_LEFT_SHIFT * 2,fm.height()*4 + SPACE_BETWEEN_LINES * 5 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 3 - MUTI_ACP_LEFT_SHIFT * 3,fm.height()*4 + SPACE_BETWEEN_LINES * 5 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 4 - MUTI_ACP_LEFT_SHIFT * 4,fm.height()*4 + SPACE_BETWEEN_LINES * 5 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");  
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 5 - MUTI_ACP_LEFT_SHIFT * 5,fm.height()*4 + SPACE_BETWEEN_LINES * 5 - 5,
                         fm.width(strADJCHLimit), fm.height(), Qt::AlignLeft, strADJCHLimit);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 6 - MUTI_ACP_LEFT_SHIFT * 6,fm.height()*4 + SPACE_BETWEEN_LINES * 5 - 5,
                         fm.width("-- --"), fm.height(), Qt::AlignLeft, "-- --");

        painter.drawText(MULTIACP_LEFT_MARGIN,fm.height()*5 + SPACE_BETWEEN_LINES * 6 - 5,fm.width("Far Right"), fm.height(), Qt::AlignLeft, "Far Right");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 - MUTI_ACP_LEFT_SHIFT,fm.height()*5 + SPACE_BETWEEN_LINES * 6 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 2 - MUTI_ACP_LEFT_SHIFT * 2,fm.height()*5 + SPACE_BETWEEN_LINES * 6 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 3 - MUTI_ACP_LEFT_SHIFT * 3,fm.height()*5 + SPACE_BETWEEN_LINES * 6 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 4 - MUTI_ACP_LEFT_SHIFT * 4,fm.height()*5 + SPACE_BETWEEN_LINES * 6 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 5 - MUTI_ACP_LEFT_SHIFT * 5,fm.height()*5 + SPACE_BETWEEN_LINES * 6 - 5,
                         fm.width(strALTCHLimit), fm.height(), Qt::AlignLeft, strALTCHLimit);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 6 - MUTI_ACP_LEFT_SHIFT * 6,fm.height()*5 + SPACE_BETWEEN_LINES * 6 - 5,
                         fm.width("-- --"), fm.height(), Qt::AlignLeft, "-- --");
    }
    else
    {
        //Upper Measurements ---- left channel
        painter.drawText(MULTIACP_LEFT_MARGIN,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,fm.width("Far Left"), fm.height(), Qt::AlignRight, "Far Left");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 - 10 - MUTI_ACP_LEFT_SHIFT,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strFarLeftAbsolute);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 2 - 15 - MUTI_ACP_LEFT_SHIFT * 2,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strFarLeftRelative);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 3 - MUTI_ACP_LEFT_SHIFT * 3,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
        painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 4 - MUTI_ACP_LEFT_SHIFT * 4,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strSpace);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 5 - MUTI_ACP_LEFT_SHIFT * 5,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                         fm.width(strALTCHLimit), fm.height(), Qt::AlignLeft, strALTCHLimit);
        if(globalUserLimit->gATLdBcLimitStatus)
        {
            if(globalUserLimit->gATLdBcLimit < globalUserVariable->dPowerValue_MultiACPFL - globalUserVariable->dPowerValue_MultiACPM)
            {
                painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 6 - MUTI_ACP_LEFT_SHIFT * 6,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                                 fm.width("FAIL"), fm.height(), Qt::AlignLeft, "FAIL");
            }
            else
            {
                painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 6 - MUTI_ACP_LEFT_SHIFT * 6,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                                 fm.width("PASS"), fm.height(), Qt::AlignLeft, "PASS");
            }
        }
        else
        {
            painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 6 - MUTI_ACP_LEFT_SHIFT * 6,fm.height() + SPACE_BETWEEN_LINES * 2 - 5,
                             fm.width("-- --"), fm.height(), Qt::AlignLeft, "-- --");
        }

        painter.drawText(MULTIACP_LEFT_MARGIN,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,fm.width("Left"), fm.height(), Qt::AlignRight, "Left");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 - 10 - MUTI_ACP_LEFT_SHIFT,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strLeftAbsolute);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 2 - 15 - MUTI_ACP_LEFT_SHIFT * 2,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strLeftRelative);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 3 - MUTI_ACP_LEFT_SHIFT * 3,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
        painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 4 - MUTI_ACP_LEFT_SHIFT * 4,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strSpace);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 5 - MUTI_ACP_LEFT_SHIFT * 5,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                         fm.width(strADJCHLimit), fm.height(), Qt::AlignLeft, strADJCHLimit);
        if(globalUserLimit->gLowerLimitStatus)
        {
            if(globalUserLimit->gLowerLimit < globalUserVariable->dPowerValue_MultiACPL - globalUserVariable->dPowerValue_MultiACPM)
            {
                painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 6 - MUTI_ACP_LEFT_SHIFT * 6,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                                 fm.width("FAIL"), fm.height(), Qt::AlignLeft, "FAIL");
            }
            else
            {
                painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 6 - MUTI_ACP_LEFT_SHIFT * 6,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                                 fm.width("PASS"), fm.height(), Qt::AlignLeft, "PASS");
            }
        }
        else
        {
            painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 6 - MUTI_ACP_LEFT_SHIFT * 6,fm.height()*2 + SPACE_BETWEEN_LINES * 3 - 5,
                             fm.width("-- --"), fm.height(), Qt::AlignLeft, "-- --");
        }
        //Upper Measurements ---- middle channel
        painter.drawText(MULTIACP_LEFT_MARGIN,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,fm.width("Main"), fm.height(), Qt::AlignRight, "Main");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 - 10 - MUTI_ACP_LEFT_SHIFT,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strMidAbsolute);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 2 - 15 - MUTI_ACP_LEFT_SHIFT * 2,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strMidRelative);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 3 - MUTI_ACP_LEFT_SHIFT * 3,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
        painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 4 - MUTI_ACP_LEFT_SHIFT * 4,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strSpace);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 5 - MUTI_ACP_LEFT_SHIFT * 5,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                         fm.width(strMAINCHLimit), fm.height(), Qt::AlignLeft, strMAINCHLimit);
        if(globalUserLimit->gUpperLimitStatus)
        {
            if(globalUserLimit->gUpperLimitTestResult == SA_FAIL)
            {
                painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 6 - MUTI_ACP_LEFT_SHIFT * 6,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                                 fm.width("FAIL"), fm.height(), Qt::AlignLeft, "FAIL");
            }
            else
            {
                painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 6 - MUTI_ACP_LEFT_SHIFT * 6,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                                 fm.width("PASS"), fm.height(), Qt::AlignLeft, "PASS");
            }
        }
        else
        {
            painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 6 - MUTI_ACP_LEFT_SHIFT * 6,fm.height()*3 + SPACE_BETWEEN_LINES * 4 - 5,
                             fm.width("-- --"), fm.height(), Qt::AlignLeft, "-- --");
        }
        //Upper Measurements ---- right channel
        painter.drawText(MULTIACP_LEFT_MARGIN,fm.height()*4 + SPACE_BETWEEN_LINES * 5 - 5,fm.width("Right"), fm.height(), Qt::AlignRight, "Right");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 - 10 - MUTI_ACP_LEFT_SHIFT,fm.height()*4 + SPACE_BETWEEN_LINES * 5 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strRightAbsolute);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 2 - 15 - MUTI_ACP_LEFT_SHIFT * 2,fm.height()*4 + SPACE_BETWEEN_LINES * 5 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strRightRelative);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 3 - MUTI_ACP_LEFT_SHIFT * 3,fm.height()*4 + SPACE_BETWEEN_LINES * 5 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
        painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 4 - MUTI_ACP_LEFT_SHIFT * 4,fm.height()*4 + SPACE_BETWEEN_LINES * 5 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strSpace);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 5 - MUTI_ACP_LEFT_SHIFT * 5,fm.height()*4 + SPACE_BETWEEN_LINES * 5 - 5,
                         fm.width(strADJCHLimit), fm.height(), Qt::AlignLeft, strADJCHLimit);

        if(globalUserLimit->gLowerLimitStatus)
        {
            if(globalUserLimit->gLowerLimit < globalUserVariable->dPowerValue_MultiACPR - globalUserVariable->dPowerValue_MultiACPM)
            {
                painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 6 - MUTI_ACP_LEFT_SHIFT * 6,fm.height()*4 + SPACE_BETWEEN_LINES * 5 - 5,
                                 fm.width("FAIL"), fm.height(), Qt::AlignLeft, "FAIL");
            }
            else
            {
                painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 6 - MUTI_ACP_LEFT_SHIFT * 6,fm.height()*4 + SPACE_BETWEEN_LINES * 5 - 5,
                                 fm.width("PASS"), fm.height(), Qt::AlignLeft, "PASS");
            }
        }
        else
        {
            painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 6 - MUTI_ACP_LEFT_SHIFT * 6,fm.height()*4 + SPACE_BETWEEN_LINES * 5 - 5,
                             fm.width("-- --"), fm.height(), Qt::AlignLeft, "-- --");
        }

        painter.drawText(MULTIACP_LEFT_MARGIN,fm.height()*5 + SPACE_BETWEEN_LINES * 6 - 5,fm.width("Far Right"), fm.height(), Qt::AlignRight, "Far Right");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 - 10 - MUTI_ACP_LEFT_SHIFT,fm.height()*5 + SPACE_BETWEEN_LINES * 6 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strFarRightAbsolute);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 2 - 15 - MUTI_ACP_LEFT_SHIFT * 2,fm.height()*5 + SPACE_BETWEEN_LINES * 6 - 5,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strFarRightRelative);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 3 - MUTI_ACP_LEFT_SHIFT * 3,fm.height()*5 + SPACE_BETWEEN_LINES * 6 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strBandWidth);
        painter.drawText(20 + MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 4 - MUTI_ACP_LEFT_SHIFT * 4,fm.height()*5 + SPACE_BETWEEN_LINES * 6 - 5,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, strSpace);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 5 - MUTI_ACP_LEFT_SHIFT * 5,fm.height()*5 + SPACE_BETWEEN_LINES * 6 - 5,
                         fm.width(strALTCHLimit), fm.height(), Qt::AlignLeft, strALTCHLimit);

        if(globalUserLimit->gATLdBcLimitStatus)
        {
            if(globalUserLimit->gATLdBcLimit < globalUserVariable->dPowerValue_MultiACPFR - globalUserVariable->dPowerValue_MultiACPM)
            {
                painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 6 - MUTI_ACP_LEFT_SHIFT * 6,fm.height()*5 + SPACE_BETWEEN_LINES * 6 - 5,
                                 fm.width("FAIL"), fm.height(), Qt::AlignLeft, "FAIL");
            }
            else
            {
                painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 6 - MUTI_ACP_LEFT_SHIFT * 6,fm.height()*5 + SPACE_BETWEEN_LINES * 6 - 5,
                                 fm.width("PASS"), fm.height(), Qt::AlignLeft, "PASS");
            }
        }
        else
        {
            painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/5 * 6 - MUTI_ACP_LEFT_SHIFT * 6,fm.height()*5 + SPACE_BETWEEN_LINES * 6 - 5,
                             fm.width("-- --"), fm.height(), Qt::AlignLeft, "-- --");
        }
    }
#endif

    //Johnson 20200511
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

    qint32 drawWidth = fm.width("Reference Power : ");
    painter.drawText(MULTIACP_LEFT_MARGIN,SPACE_BETWEEN_LINES + 5,drawWidth, fm.height() + 5, Qt::AlignRight, "Reference Power : ");

    pen.setColor(curFontColor);
    painter.setPen(pen);
    QString str = QString("%1").arg(globalUserVariable->dPowerValue_MultiACPM);
    painter.drawText(MULTIACP_LEFT_MARGIN + drawWidth,SPACE_BETWEEN_LINES + 5,fm.width(str), fm.height() + 5, Qt::AlignRight, str);

    drawWidth += fm.width("-99.9999");
    str = QString(" dBm / ");
    painter.drawText(MULTIACP_LEFT_MARGIN + drawWidth,SPACE_BETWEEN_LINES + 5,fm.width(str), fm.height() + 5, Qt::AlignRight, str);

    drawWidth += fm.width(str);
    str = globalUserVariable->freqValueToQstring(globalUserVariable->gMainIntegBW);
    painter.drawText(MULTIACP_LEFT_MARGIN + drawWidth,SPACE_BETWEEN_LINES + 5,fm.width(str), fm.height() + 5, Qt::AlignRight, str);


    pen.setColor(fontColor);
    painter.setPen(pen);
    painter.drawText(MULTIACP_LEFT_MARGIN,SPACE_BETWEEN_LINES * 3 + fm.height(),fm.width("Channel"), fm.height(), Qt::AlignRight, "Channel");
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8,SPACE_BETWEEN_LINES * 3 + fm.height(),fm.width("Bandwidth"), fm.height(), Qt::AlignRight, "Bandwidth");
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 2 ,SPACE_BETWEEN_LINES * 3 + fm.height(),fm.width("Lower / dBc"), fm.height(), Qt::AlignRight, "Lower / dBc");
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 3 ,SPACE_BETWEEN_LINES * 3 + fm.height(),fm.width("Lower / dBm"), fm.height(), Qt::AlignRight, "Lower / dBm");
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 4 ,SPACE_BETWEEN_LINES * 3 + fm.height(),fm.width("Pass"), fm.height(), Qt::AlignRight, "Pass");
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 5 ,SPACE_BETWEEN_LINES * 3 + fm.height(),fm.width("Upper / dBc"), fm.height(), Qt::AlignRight, "Upper / dBc");
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 6 ,SPACE_BETWEEN_LINES * 3 + fm.height(),fm.width("Upper / dBm"), fm.height(), Qt::AlignRight, "Upper / dBm");
    painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 7 ,SPACE_BETWEEN_LINES * 3 + fm.height(),fm.width("Pass"), fm.height(), Qt::AlignRight, "Pass");

    painter.drawText(MULTIACP_LEFT_MARGIN,SPACE_BETWEEN_LINES * 4 + fm.height() * 2,fm.width("Adjacent"), fm.height(), Qt::AlignRight, "Adjacent");
    painter.drawText(MULTIACP_LEFT_MARGIN,SPACE_BETWEEN_LINES * 5 + fm.height() * 3,fm.width("Alternate"), fm.height(), Qt::AlignRight, "Alternate");

    pen.setWidth(1);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.drawLine(MULTIACP_LEFT_MARGIN - 5,SPACE_BETWEEN_LINES / 2,MultiACPTablePixmap.width() - MULTIACP_BETWEEN_COLUMN,SPACE_BETWEEN_LINES / 2);
    painter.drawLine(MULTIACP_LEFT_MARGIN - 5,SPACE_BETWEEN_LINES * 2 + fm.height() + 5,MultiACPTablePixmap.width() - MULTIACP_BETWEEN_COLUMN,SPACE_BETWEEN_LINES * 2 + fm.height() + 5);
    painter.drawLine(MULTIACP_LEFT_MARGIN - 5,SPACE_BETWEEN_LINES * 3 + fm.height() * 2 + 5,MultiACPTablePixmap.width() - MULTIACP_BETWEEN_COLUMN,SPACE_BETWEEN_LINES * 3 + fm.height() * 2 + 5);
    painter.drawLine(MULTIACP_LEFT_MARGIN - 5,SPACE_BETWEEN_LINES * 4 + fm.height() * 3 + 5,MultiACPTablePixmap.width() - MULTIACP_BETWEEN_COLUMN,SPACE_BETWEEN_LINES * 4 + fm.height() * 3 + 5);
    painter.drawLine(MULTIACP_LEFT_MARGIN - 5,SPACE_BETWEEN_LINES * 5 + fm.height() * 4 + 5,MultiACPTablePixmap.width() - MULTIACP_BETWEEN_COLUMN,SPACE_BETWEEN_LINES * 5 + fm.height() * 4 + 5);

    painter.drawLine(MULTIACP_LEFT_MARGIN - 5,SPACE_BETWEEN_LINES / 2,MULTIACP_LEFT_MARGIN - 5,SPACE_BETWEEN_LINES * 5 + fm.height() * 4 + 5);
    painter.drawLine(MultiACPTablePixmap.width() - MULTIACP_BETWEEN_COLUMN,SPACE_BETWEEN_LINES / 2,
                     MultiACPTablePixmap.width() - MULTIACP_BETWEEN_COLUMN,SPACE_BETWEEN_LINES * 5 + fm.height() * 4 + 5);
    painter.drawLine(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 - 10,SPACE_BETWEEN_LINES * 2 + fm.height() + 5,
                     MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 - 10,SPACE_BETWEEN_LINES * 5 + fm.height() * 4 + 5);
    painter.drawLine(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 2 - 10,SPACE_BETWEEN_LINES * 2 + fm.height() + 5,
                     MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 2 - 10,SPACE_BETWEEN_LINES * 5 + fm.height() * 4 + 5);
    painter.drawLine(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 3 - 10,SPACE_BETWEEN_LINES * 2 + fm.height() + 5,
                     MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 3 - 10,SPACE_BETWEEN_LINES * 5 + fm.height() * 4 + 5);
    painter.drawLine(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 4 - 10,SPACE_BETWEEN_LINES * 2 + fm.height() + 5,
                     MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 4 - 10,SPACE_BETWEEN_LINES * 5 + fm.height() * 4 + 5);
    painter.drawLine(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 5 - 10,SPACE_BETWEEN_LINES * 2 + fm.height() + 5,
                     MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 5 - 10,SPACE_BETWEEN_LINES * 5 + fm.height() * 4 + 5);
    painter.drawLine(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 6 - 10,SPACE_BETWEEN_LINES * 2 + fm.height() + 5,
                     MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 6 - 10,SPACE_BETWEEN_LINES * 5 + fm.height() * 4 + 5);
    painter.drawLine(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 7 - 10,SPACE_BETWEEN_LINES * 2 + fm.height() + 5,
                     MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 7 - 10,SPACE_BETWEEN_LINES * 5 + fm.height() * 4 + 5);


    //draw pixmap content
    font.setWeight(QFont::Normal);
    painter.setFont(font);
    pen.setColor(curFontColor);
    pen.setWidth(1);
    painter.setPen(pen);
    fm = painter.fontMetrics();

    maxStrFreqLen = fm.width("-999.999999999 GHz");
    maxStrAmpLen  = fm.width("-99.99 dBm");

    QString strADJBW = globalUserVariable->freqValueToQstring(globalUserVariable->gADJIntegBW);
    QString strALTBW = globalUserVariable->freqValueToQstring(globalUserVariable->gALTIntegBW);
    QString strLowestADJRelativePower = QString::number(globalUserVariable->dPowerValue_MultiACPL - globalUserVariable->dPowerValue_MultiACPM, 'f', 2) + " dBc";
    QString strLowestALTRelativePower = QString::number(globalUserVariable->dPowerValue_MultiACPFL - globalUserVariable->dPowerValue_MultiACPM, 'f', 2) + " dBc";
    QString strLowestADJAbsolutePower = globalUserVariable->amptTransformToQstring(pcontrolInterface->getAmpUnit(),globalUserVariable->dPowerValue_MultiACPL);
    QString strLowestALTAbsolutePower = globalUserVariable->amptTransformToQstring(pcontrolInterface->getAmpUnit(),globalUserVariable->dPowerValue_MultiACPFL);
    QString strHighestADJRelativePower = QString::number(globalUserVariable->dPowerValue_MultiACPR - globalUserVariable->dPowerValue_MultiACPM, 'f', 2) + " dBc";
    QString strHighestALTRelativePower = QString::number(globalUserVariable->dPowerValue_MultiACPFR - globalUserVariable->dPowerValue_MultiACPM, 'f', 2) + " dBc";
    QString strHighestADJAbsolutePower = globalUserVariable->amptTransformToQstring(pcontrolInterface->getAmpUnit(),globalUserVariable->dPowerValue_MultiACPR);
    QString strHighestALTAbsolutePower = globalUserVariable->amptTransformToQstring(pcontrolInterface->getAmpUnit(),globalUserVariable->dPowerValue_MultiACPFR);


    //Johnson 190321
    if(globalUserVariable->gTraceView[globalUserVariable->gTraceSelect] == SA_OFF)
    {

        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8,SPACE_BETWEEN_LINES * 4 + fm.height() * 2,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8,SPACE_BETWEEN_LINES * 5 + fm.height() * 3,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");

        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 2 ,SPACE_BETWEEN_LINES * 4 + fm.height() * 2,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 2 ,SPACE_BETWEEN_LINES * 5 + fm.height() * 3,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");

        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 3 ,SPACE_BETWEEN_LINES * 4 + fm.height() * 2,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 3 ,SPACE_BETWEEN_LINES * 5 + fm.height() * 3,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");

        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 4 ,SPACE_BETWEEN_LINES * 4 + fm.height() * 2,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 4 ,SPACE_BETWEEN_LINES * 5 + fm.height() * 3,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");

        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 5 ,SPACE_BETWEEN_LINES * 4 + fm.height() * 2,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 5 ,SPACE_BETWEEN_LINES * 5 + fm.height() * 3,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");

        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 6 ,SPACE_BETWEEN_LINES * 4 + fm.height() * 2,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 6 ,SPACE_BETWEEN_LINES * 5 + fm.height() * 3,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");

        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 7 ,SPACE_BETWEEN_LINES * 4 + fm.height() * 2,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 7 ,SPACE_BETWEEN_LINES * 5 + fm.height() * 3,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
    }
    else
    {
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8,SPACE_BETWEEN_LINES * 4 + fm.height() * 2,
                         fm.width(strADJBW), fm.height(), Qt::AlignRight, strADJBW);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8,SPACE_BETWEEN_LINES * 5 + fm.height() * 3,
                         fm.width(strALTBW), fm.height(), Qt::AlignRight, strALTBW);

        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 2 ,SPACE_BETWEEN_LINES * 4 + fm.height() * 2,
                         maxStrAmpLen, fm.height(), Qt::AlignRight,strLowestADJRelativePower);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 2 ,SPACE_BETWEEN_LINES * 5 + fm.height() * 3,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strLowestALTRelativePower);

        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 3 ,SPACE_BETWEEN_LINES * 4 + fm.height() * 2,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strLowestADJAbsolutePower);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 3 ,SPACE_BETWEEN_LINES * 5 + fm.height() * 3,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strLowestALTAbsolutePower);

        if(globalUserLimit->gLowerLimitStatus)
        {
            if(globalUserLimit->gLowerLimit < globalUserVariable->dPowerValue_MultiACPL - globalUserVariable->dPowerValue_MultiACPM)
            {
                painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 4 ,SPACE_BETWEEN_LINES * 4 + fm.height() * 2,
                             fm.width("FAIL"), fm.height(), Qt::AlignRight, "FAIL");
            }
            else
            {
                painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 4 ,SPACE_BETWEEN_LINES * 4 + fm.height() * 2,
                             fm.width("PASS"), fm.height(), Qt::AlignRight, "PASS");
            }
            if(globalUserLimit->gLowerLimit < globalUserVariable->dPowerValue_MultiACPR - globalUserVariable->dPowerValue_MultiACPM)
            {
                painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 7 ,SPACE_BETWEEN_LINES * 4 + fm.height() * 2,
                             fm.width("FAIL"), fm.height(), Qt::AlignRight, "FAIL");
            }
            else
            {
                painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 7 ,SPACE_BETWEEN_LINES * 4 + fm.height() * 2,
                             fm.width("PASS"), fm.height(), Qt::AlignRight, "PASS");
            }
        }
        else
        {
            painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 4 ,SPACE_BETWEEN_LINES * 4 + fm.height() * 2,
                             fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
            painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 7 ,SPACE_BETWEEN_LINES * 4 + fm.height() * 2,
                             fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        }

        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 5 ,SPACE_BETWEEN_LINES * 4 + fm.height() * 2,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strHighestADJRelativePower);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 5 ,SPACE_BETWEEN_LINES * 5 + fm.height() * 3,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strHighestALTRelativePower);

        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 6 ,SPACE_BETWEEN_LINES * 4 + fm.height() * 2,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strHighestADJAbsolutePower);
        painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 6 ,SPACE_BETWEEN_LINES * 5 + fm.height() * 3,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strHighestALTAbsolutePower);

        if(globalUserLimit->gATLdBcLimitStatus)
        {
            if(globalUserLimit->gATLdBcLimit < globalUserVariable->dPowerValue_MultiACPFL - globalUserVariable->dPowerValue_MultiACPM)
            {
                painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 4 ,SPACE_BETWEEN_LINES * 5 + fm.height() * 3,
                             fm.width("FAIL"), fm.height(), Qt::AlignRight, "FAIL");
            }
            else
            {
                painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 4 ,SPACE_BETWEEN_LINES * 5 + fm.height() * 3,
                             fm.width("PASS"), fm.height(), Qt::AlignRight, "PASS");
            }
            if(globalUserLimit->gATLdBcLimit < globalUserVariable->dPowerValue_MultiACPFR - globalUserVariable->dPowerValue_MultiACPM)
            {
                painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 7 ,SPACE_BETWEEN_LINES * 5 + fm.height() * 3,
                             fm.width("FAIL"), fm.height(), Qt::AlignRight, "FAIL");
            }
            else
            {
                painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 7 ,SPACE_BETWEEN_LINES * 5 + fm.height() * 3,
                             fm.width("PASS"), fm.height(), Qt::AlignRight, "PASS");
            }
        }
        else
        {
            painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 4 ,SPACE_BETWEEN_LINES * 5 + fm.height() * 3,
                             fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
            painter.drawText(MULTIACP_BETWEEN_COLUMN + MultiACPTablePixmap.width()/8 * 7 ,SPACE_BETWEEN_LINES * 5 + fm.height() * 3,
                             fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        }
    }
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
