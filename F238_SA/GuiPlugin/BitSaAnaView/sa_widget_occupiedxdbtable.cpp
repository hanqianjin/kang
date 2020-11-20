#include "sa_widget_occupiedxdbtable.h"
#include "ui_sa_widget_occupiedxdbtable.h"

#include <QPainter>
#include <QStylePainter>
#include "sa_colordef.h"

sa_widget_OccupiedXdBTable::sa_widget_OccupiedXdBTable(user_variable &m_user_variable, user_limit &m_user_limit, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sa_widget_OccupiedXdBTable)
{
    globalUserVariable = &m_user_variable;
    globalUserLimit = &m_user_limit;

    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/);

    ui->setupUi(this);
    setProperty("status",qssMode[m_user_variable.gDisplayMode]);
    OccupiedXdBTablePixmap = QPixmap(SMALLDRAW_WIDTH, OCCUPIED_TABLE_HEIGHT);
}

sa_widget_OccupiedXdBTable::~sa_widget_OccupiedXdBTable()
{
    delete ui;
}
void sa_widget_OccupiedXdBTable::refreshOccupiedXdBTable()
{
    refreshPixmap();
    repaint(0,0,OccupiedXdBTablePixmap.width(),OccupiedXdBTablePixmap.height());
}
void sa_widget_OccupiedXdBTable::refreshPixmap()
{
#if 1 //table_height = 130
    qint32 colorMode = globalUserVariable->gDisplayMode;
    QColor TableBgColor = TableBackgroundColor[colorMode];
    QColor fontColor = TableFontColor[colorMode];
    QColor curFontColor = TableCurFontColor[colorMode];

    OccupiedXdBTablePixmap.fill(TableBgColor);
    QPainter painter(&OccupiedXdBTablePixmap);

    //draw pixmap title
    QFont font = QFont(QFont("Arial",10));
    font.setWeight(QFont::Bold);
    QPen pen(fontColor);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setFont(font);
    QFontMetrics fm = painter.fontMetrics();

    painter.drawText(OCCUPIEDXDB_LEFT_MARGIN,SA_OCC_SPACE_LINES, fm.width("Measurement"), fm.height(), Qt::AlignRight, "Measurement");
    painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4,SA_OCC_SPACE_LINES, fm.width("Value"), fm.height(), Qt::AlignRight, "Value");
    painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 2 - 20,SA_OCC_SPACE_LINES, fm.width("Limit"), fm.height(), Qt::AlignRight, "Limit");
    painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 3 - 70,SA_OCC_SPACE_LINES, fm.width("Pass / Fail"), fm.height(), Qt::AlignRight, "Pass / Fail");

    //draw pixmap content
    font.setWeight(QFont::Normal);
    painter.setFont(font);
    pen.setColor(curFontColor);
    pen.setWidth(1);
    painter.setPen(pen);
    fm = painter.fontMetrics();

    quint32 maxStrFreqLen = fm.width("-999.999999999 GHz");
    quint32 maxStrAmpLen  = fm.width("-99.99 dBm");

    QString strOccupiedBW = globalUserVariable->freqValueToQstring(globalUserVariable->uOccupiedBW);
    QString strXdBBW = globalUserVariable->freqValueToQstring(globalUserVariable->uXdBBW);
    QString strTotalPower = QString::number(globalUserVariable->dTotalPower, 'f', 2) + " dBm";
    QString strXdB = QString::number(globalUserVariable->gXdB, 'f', 2) + " dB";
    QString strOccupiedPowerPerc = QString::number(globalUserVariable->gOccupied_BW, 'f' , 2) + " %";

    QString strOBWLimit = globalUserVariable->freqValueToQstring(globalUserLimit->gUpperLimit);

    painter.drawText(OCCUPIEDXDB_LEFT_MARGIN,SA_OCC_SPACE_LINES * 2 + fm.height(), fm.width("Occupied Power%"), fm.height(), Qt::AlignRight, "Occupied Power%");
    painter.drawText(OCCUPIEDXDB_LEFT_MARGIN,SA_OCC_SPACE_LINES * 3 + fm.height() * 2, fm.width("XdB"), fm.height(), Qt::AlignRight, "XdB");
    painter.drawText(OCCUPIEDXDB_LEFT_MARGIN,SA_OCC_SPACE_LINES * 5 + fm.height() * 4, fm.width("Occupied Bandwidth"), fm.height(), Qt::AlignRight, "Occupied Bandwidth");
    painter.drawText(OCCUPIEDXDB_LEFT_MARGIN,SA_OCC_SPACE_LINES * 4 + fm.height() * 3, fm.width("Total Power"), fm.height(), Qt::AlignRight, "Total Power");
    painter.drawText(OCCUPIEDXDB_LEFT_MARGIN,SA_OCC_SPACE_LINES * 6 + fm.height() * 5, fm.width("XdB Bandwidth"), fm.height(), Qt::AlignRight, "XdB Bandwidth");

    if(globalUserVariable->gTraceView[globalUserVariable->gTraceSelect] == SA_OFF)
    {
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4,SA_OCC_SPACE_LINES * 2 + fm.height(),
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4,SA_OCC_SPACE_LINES * 3 + fm.height() * 2,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4,SA_OCC_SPACE_LINES * 4 + fm.height() * 3,
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4,SA_OCC_SPACE_LINES * 5 + fm.height() * 4,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4,SA_OCC_SPACE_LINES * 6 + fm.height() * 5,
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
#if 0
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 2,SA_OCC_SPACE_LINES * 2 + fm.height(),
                         fm.width("Limit1"), fm.height(), Qt::AlignRight, "Limit1");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 2,SA_OCC_SPACE_LINES * 3 + fm.height() * 2,
                         fm.width("Limit2"), fm.height(), Qt::AlignRight, "Limit2");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 2,SA_OCC_SPACE_LINES * 4 + fm.height() * 3,
                         fm.width("Limit3"), fm.height(), Qt::AlignRight, "Limit3");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 2,SA_OCC_SPACE_LINES * 5 + fm.height() * 4,
                         fm.width("Limit4"), fm.height(), Qt::AlignRight, "Limit4");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 2,SA_OCC_SPACE_LINES * 6 + fm.height() * 5,
                         fm.width("Limit5 / Limit6"), fm.height(), Qt::AlignRight, "Limit5 / Limit6");

        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 3,SA_OCC_SPACE_LINES * 2 + fm.height(),
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 3,SA_OCC_SPACE_LINES * 3 + fm.height() * 2,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 3,SA_OCC_SPACE_LINES * 4 + fm.height() * 3,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 3,SA_OCC_SPACE_LINES * 5 + fm.height() * 4,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 3,SA_OCC_SPACE_LINES * 6 + fm.height() * 5,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
#else
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 2,SA_OCC_SPACE_LINES * 2 + fm.height(),
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 2,SA_OCC_SPACE_LINES * 3 + fm.height() * 2,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 2,SA_OCC_SPACE_LINES * 4 + fm.height() * 3,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 2,SA_OCC_SPACE_LINES * 5 + fm.height() * 4,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 2,SA_OCC_SPACE_LINES * 6 + fm.height() * 5,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");

        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 3,SA_OCC_SPACE_LINES * 2 + fm.height(),
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 3,SA_OCC_SPACE_LINES * 3 + fm.height() * 2,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 3,SA_OCC_SPACE_LINES * 4 + fm.height() * 3,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 3,SA_OCC_SPACE_LINES * 5 + fm.height() * 4,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 3,SA_OCC_SPACE_LINES * 6 + fm.height() * 5,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
#endif
    }
    else
    {
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 - 22,SA_OCC_SPACE_LINES * 2 + fm.height(),
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strOccupiedPowerPerc);
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 - 20,SA_OCC_SPACE_LINES * 3 + fm.height() * 2,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strXdB);
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 - 70,SA_OCC_SPACE_LINES * 5 + fm.height() * 4,
                         maxStrFreqLen, fm.height(), Qt::AlignRight, strOccupiedBW);
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 - 10,SA_OCC_SPACE_LINES * 4 + fm.height() * 3,
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strTotalPower);
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 - 70,SA_OCC_SPACE_LINES * 6 + fm.height() * 5,
                         maxStrFreqLen, fm.height(), Qt::AlignRight, strXdBBW);
#if 0
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 2 - 20,SA_OCC_SPACE_LINES * 2 + fm.height(),
                         fm.width("Limit1"), fm.height(), Qt::AlignRight, "Limit1");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 2 - 20,SA_OCC_SPACE_LINES * 3 + fm.height() * 2,
                         fm.width("Limit2"), fm.height(), Qt::AlignRight, "Limit2");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 2 - 20,SA_OCC_SPACE_LINES * 4 + fm.height() * 3,
                         fm.width("Limit3"), fm.height(), Qt::AlignRight, "Limit3");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 2 - 20,SA_OCC_SPACE_LINES * 5 + fm.height() * 4,
                         fm.width("Limit4"), fm.height(), Qt::AlignRight, "Limit4");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 2 - 20,SA_OCC_SPACE_LINES * 6 + fm.height() * 5,
                         fm.width("Limit5 / Limit6"), fm.height(), Qt::AlignRight, "Limit5 / Limit6");
#else
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 2 - 20,SA_OCC_SPACE_LINES * 2 + fm.height(),
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 2 - 20,SA_OCC_SPACE_LINES * 3 + fm.height() * 2,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 2 - 20,SA_OCC_SPACE_LINES * 4 + fm.height() * 3,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 2 - 20,SA_OCC_SPACE_LINES * 5 + fm.height() * 4,
                         fm.width(strOBWLimit), fm.height(), Qt::AlignRight, strOBWLimit);
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 2 - 20,SA_OCC_SPACE_LINES * 6 + fm.height() * 5,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
#endif
#if 0
        QString strL1,strL2,strL3,strL4,strL5,strL6;
        if(globalUserLimit->gLimitTest == SA_ON)
        {
            for(qint32 i = 0;i<LIMIT_SELECTSUM;i++)
            {
                if(globalUserLimit->gLimitLine[i] == SA_ON)
                {
                    if (globalUserLimit->gLatestLimitTestResult[i] == SA_PASS)
                    {
                        if(i == 0) strL1 = "PASS";
                        else if(i == 1) strL2 = "PASS";
                        else if(i == 2) strL3 = "PASS";
                        else if(i == 3) strL4 = "PASS";
                        else if(i == 4) strL5 = "PASS";
                        else if(i == 5) strL6 = "PASS";
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
                        if(i == 0) strL1 = "FAIL";
                        else if(i == 1) strL2 = "FAIL";
                        else if(i == 2) strL3 = "FAIL";
                        else if(i == 3) strL4 = "FAIL";
                        else if(i == 4) strL5 = "FAIL";
                        else if(i == 5) strL6 = "FAIL";
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
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 3 - 70,SA_OCC_SPACE_LINES * 2 + fm.height(),
                         fm.width(strL1), fm.height(), Qt::AlignRight, strL1);
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 3 - 70,SA_OCC_SPACE_LINES * 3 + fm.height() * 2,
                         fm.width(strL2), fm.height(), Qt::AlignRight, strL2);
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 3 - 70,SA_OCC_SPACE_LINES * 4 + fm.height() * 3,
                         fm.width(strL3), fm.height(), Qt::AlignRight, strL3);
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 3 - 70,SA_OCC_SPACE_LINES * 5 + fm.height() * 4,
                         fm.width(strL4), fm.height(), Qt::AlignRight, strL4);
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 3 - 70,SA_OCC_SPACE_LINES * 6 + fm.height() * 5,
                         fm.width(QString("%1 / %2").arg(strL5).arg(strL6)), fm.height(), Qt::AlignRight, QString("%1 / %2").arg(strL5).arg(strL6));
#else
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 3 - 70,SA_OCC_SPACE_LINES * 2 + fm.height(),
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 3 - 70,SA_OCC_SPACE_LINES * 3 + fm.height() * 2,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 3 - 70,SA_OCC_SPACE_LINES * 4 + fm.height() * 3,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        if(globalUserLimit->gUpperLimitStatus)
        {
            if(globalUserLimit->gUpperLimitTestResult == SA_FAIL)
            {
                painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 3 - 70,SA_OCC_SPACE_LINES * 5 + fm.height() * 4,
                             fm.width("FAIL"), fm.height(), Qt::AlignRight, "FAIL");
            }
            else
            {
                painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 3 - 70,SA_OCC_SPACE_LINES * 5 + fm.height() * 4,
                             fm.width("PASS"), fm.height(), Qt::AlignRight, "PASS");
            }
        }
        else
        {
            painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 3 - 70,SA_OCC_SPACE_LINES * 5 + fm.height() * 4,
                             fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
        }

        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/4 * 3 - 70,SA_OCC_SPACE_LINES * 6 + fm.height() * 5,
                         fm.width("-- --"), fm.height(), Qt::AlignRight, "-- --");
#endif
    }
#else //table_height = 58
    OccupiedXdBTablePixmap.fill(QColor(72,72,72));
    QPainter painter(&OccupiedXdBTablePixmap);

    //draw pixmap title
    QFont font = QFont(QFont("Arial",10));
    font.setWeight(QFont::Bold);
    QPen pen(Qt::white);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setFont(font);
    QFontMetrics fm = painter.fontMetrics();

    painter.drawText(OCCUPIEDXDB_LEFT_MARGIN,SA_OCC_SPACE_LINES, fm.width("Occupied BW"), fm.height(), Qt::AlignRight, "Occupied BW");
    painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/5,SA_OCC_SPACE_LINES, fm.width("Total Power"), fm.height(), Qt::AlignRight, "Total Power");
    painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/5 * 2,SA_OCC_SPACE_LINES, fm.width("xdB BW"), fm.height(), Qt::AlignRight, "xdB BW");
    painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/5 * 3,SA_OCC_SPACE_LINES, fm.width("Occupied Power%"), fm.height(), Qt::AlignRight, "Occupied Power%");
    painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/5 * 4,SA_OCC_SPACE_LINES, fm.width("XdB"), fm.height(), Qt::AlignRight, "XdB");

    //draw pixmap content
    font.setWeight(QFont::Normal);
    painter.setFont(font);
    pen.setColor(QColor(250,210,120));
    pen.setWidth(1);
    painter.setPen(pen);
    fm = painter.fontMetrics();

    quint32 maxStrFreqLen = fm.width("-999.999999999 GHz");
    quint32 maxStrAmpLen  = fm.width("-99.99 dBm");

    QString strOccupiedBW = globalUserVariable->freqValueToQstring(globalUserVariable->uOccupiedBW);
    QString strXdBBW = globalUserVariable->freqValueToQstring(globalUserVariable->uXdBBW);
    QString strTotalPower = QString::number(globalUserVariable->dTotalPower, 'f', 2) + " dBm";
    QString strXdB = QString::number(globalUserVariable->gXdB, 'f', 2) + " dB";
    QString strOccupiedPowerPerc = QString::number(globalUserVariable->gOccupied_BW, 'f' , 2) + " %";

    //Johnson 190321
    if(globalUserVariable->gTraceView[globalUserVariable->gTraceSelect] == SA_OFF)
    {
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN,SA_OCC_SPACE_LINES * 2 + fm.height(),
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/5,SA_OCC_SPACE_LINES * 2 + fm.height(),
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/5 * 2,SA_OCC_SPACE_LINES * 2 + fm.height(),
                         maxStrFreqLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/5 * 3,SA_OCC_SPACE_LINES * 2 + fm.height(),
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/5 * 4,SA_OCC_SPACE_LINES * 2 + fm.height(),
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, "-- --");
    }
    else
    {
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN - 63,SA_OCC_SPACE_LINES * 2 + fm.height(),
                         maxStrFreqLen, fm.height(), Qt::AlignRight, strOccupiedBW);
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/5,SA_OCC_SPACE_LINES * 2 + fm.height(),
                         maxStrAmpLen, fm.height(), Qt::AlignRight, strTotalPower);
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/5 * 2 - 73,SA_OCC_SPACE_LINES * 2 + fm.height(),
                         maxStrFreqLen, fm.height(), Qt::AlignRight, strXdBBW);
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/5 * 3,SA_OCC_SPACE_LINES * 2 + fm.height(),
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, strOccupiedPowerPerc);
        painter.drawText(2*OCCUPIEDXDB_LEFT_MARGIN + OccupiedXdBTablePixmap.width()/5 * 4,SA_OCC_SPACE_LINES * 2 + fm.height(),
                         maxStrAmpLen, fm.height(), Qt::AlignLeft, strXdB);
    }
#endif
}
void sa_widget_OccupiedXdBTable::paintEvent(QPaintEvent *event)
{
    QStylePainter painter(this);
    painter.drawPixmap(0,0,OccupiedXdBTablePixmap);
}
void sa_widget_OccupiedXdBTable::setPixmapSize(qint32 mWidth,qint32 mHeight)
{
    OccupiedXdBTablePixmap = OccupiedXdBTablePixmap.scaled(mWidth,mHeight,Qt::IgnoreAspectRatio,Qt::FastTransformation);
}
