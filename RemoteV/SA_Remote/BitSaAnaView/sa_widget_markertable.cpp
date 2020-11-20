#include "sa_widget_markertable.h"
#include "ui_sa_widget_markertable.h"

#include <QPainter>
#include <QStylePainter>
#include "sa_colordef.h"

sa_widget_markerTable::sa_widget_markerTable(controlInterface &interface,user_variable &m_user_variable, user_limit &m_user_limit, QWidget *parent) :
    QWidget(parent),
    pcontrolInterface(&interface),
    globalUserVariable(&m_user_variable),
    globalUserLimit(&m_user_limit),
    ui(new Ui::sa_widget_markerTable)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/);

    ui->setupUi(this);
    setProperty("status",qssMode[interface.GetDisplayMode()]);
    MarkerTablePixmap = QPixmap(SMALLDRAW_WIDTH, MARKER_TABLE_HEIGHT);
}

sa_widget_markerTable::~sa_widget_markerTable()
{
    delete ui;
}
void sa_widget_markerTable::refreshMarkerTable()
{
    refreshPixmap();
    repaint(0,0,MarkerTablePixmap.width(),MarkerTablePixmap.height());
}
void sa_widget_markerTable::refreshPixmap()
{
    qint32 colorMode = globalUserVariable->gDisplayMode;
    QColor TableBgColor = TableBackgroundColor[colorMode];
    QColor fontColor = TableFontColor[colorMode];
    QColor curFontColor = TableCurFontColor[colorMode];

    MarkerTablePixmap.fill(TableBgColor);
    QPainter painter(&MarkerTablePixmap);

    QString strMkr,strFreq,strAmpt;
    qreal value;
    quint32 maxStrFreqLen = 0;
    quint32 maxStrAmpLen  = 0;
    for(int i=0;i<MARKER_TOTAL_CNT;i++)
    {
        strMkr = QString("M%1  ").arg(QString::number(i+1));
        if(pcontrolInterface->getMarkerViewStatus(i))
        {
            value = globalUserVariable->gMarkerRefFreq[i];
            strFreq = globalUserVariable->freqValueToQstring(value);

            //Johnson 190321
            if(globalUserVariable->gTraceView[globalUserVariable->gTraceSelect] == SA_OFF)
            {
                strFreq="-- --";
                strAmpt="-- --";
            }
            else
            {
                value = (qreal)globalUserVariable ->gTraceMeasureVal[globalUserVariable ->gTraceSelect][globalUserVariable->gMarkerRefPos[i]] + globalUserVariable ->gRefOffset;
                strAmpt = globalUserVariable->amptTransformToQstring(pcontrolInterface->getAmpUnit(),value);
            }
        }
        else
        {
            strFreq="-- --";
            strAmpt="-- --";
        }

        //draw pixmap
        QFont font = QFont(QFont("Arial",10));
        font.setWeight(QFont::Bold);
        QPen pen(fontColor);
        pen.setWidth(2);
        painter.setPen(pen);
        painter.setFont(font);
        QFontMetrics fm = painter.fontMetrics();

        if(i == 0) painter.drawText(MARKER_LEFT_MARGIN,SA_MARKER_SPACE_LINES, fm.width(strMkr), fm.height(), Qt::AlignRight, strMkr);
        else if(i == 1) painter.drawText(MARKER_LEFT_MARGIN + MarkerTablePixmap.width()/3,SA_MARKER_SPACE_LINES, fm.width(strMkr), fm.height(), Qt::AlignRight, strMkr);
        else if(i == 2) painter.drawText(MARKER_LEFT_MARGIN + MarkerTablePixmap.width()/3 * 2,SA_MARKER_SPACE_LINES, fm.width(strMkr), fm.height(), Qt::AlignRight, strMkr);
        else if(i == 3) painter.drawText(MARKER_LEFT_MARGIN,fm.height() + 2*SA_MARKER_SPACE_LINES, fm.width(strMkr), fm.height(), Qt::AlignRight, strMkr);
        else if(i == 4) painter.drawText(MARKER_LEFT_MARGIN + MarkerTablePixmap.width()/3,fm.height() + 2*SA_MARKER_SPACE_LINES, fm.width(strMkr), fm.height(), Qt::AlignRight, strMkr);
        else if(i == 5) painter.drawText(MARKER_LEFT_MARGIN + MarkerTablePixmap.width()/3 * 2,fm.height() + 2*SA_MARKER_SPACE_LINES, fm.width(strMkr), fm.height(), Qt::AlignRight, strMkr);

        font.setWeight(QFont::Normal);
        painter.setFont(font);
        pen.setColor(curFontColor);
        pen.setWidth(1);
        painter.setPen(pen);
        fm = painter.fontMetrics();

        if(pcontrolInterface->getMarkerViewStatus(i))
        {
            if(globalUserVariable->gTraceView[globalUserVariable->gTraceSelect] == SA_OFF)
            {
                maxStrFreqLen = fm.width("-- --");
                maxStrAmpLen  = fm.width("-- --");
            }
            else
            {
                maxStrFreqLen = fm.width("-999.999999999 GHz");
                maxStrAmpLen  = fm.width("-99.99 dBm");
            }
        }
        else
        {
            maxStrFreqLen = fm.width("-- --");
            maxStrAmpLen  = fm.width("-- --");
        }

        if(i == 0)
        {
            painter.drawText(MARKER_LEFT_MARGIN + fm.width(strMkr),SA_MARKER_SPACE_LINES, maxStrFreqLen, fm.height(), Qt::AlignRight, strFreq);
            painter.drawText(MARKER_LEFT_MARGIN + fm.width(strMkr) + maxStrFreqLen,SA_MARKER_SPACE_LINES, fm.width(" / "), fm.height(), Qt::AlignRight, " / ");
            painter.drawText(MARKER_LEFT_MARGIN + fm.width(strMkr) + maxStrFreqLen + fm.width(" / "),SA_MARKER_SPACE_LINES, maxStrAmpLen, fm.height(), Qt::AlignRight, strAmpt);
        }
        else if(i == 1)
        {
            painter.drawText(MARKER_LEFT_MARGIN + MarkerTablePixmap.width()/3 + fm.width(strMkr),
                             SA_MARKER_SPACE_LINES, maxStrFreqLen, fm.height(), Qt::AlignRight, strFreq);
            painter.drawText(MARKER_LEFT_MARGIN + MarkerTablePixmap.width()/3 + fm.width(strMkr) + maxStrFreqLen,
                             SA_MARKER_SPACE_LINES, fm.width(" / "), fm.height(), Qt::AlignRight, " / ");
            painter.drawText(MARKER_LEFT_MARGIN + MarkerTablePixmap.width()/3 + fm.width(strMkr) + maxStrFreqLen + fm.width(" / "),
                             SA_MARKER_SPACE_LINES, maxStrAmpLen, fm.height(), Qt::AlignRight, strAmpt);
        }
        else if(i == 2)
        {
            painter.drawText(MARKER_LEFT_MARGIN + MarkerTablePixmap.width()/3 * 2 + fm.width(strMkr),
                             SA_MARKER_SPACE_LINES, maxStrFreqLen, fm.height(), Qt::AlignRight, strFreq);
            painter.drawText(MARKER_LEFT_MARGIN + MarkerTablePixmap.width()/3 * 2 + fm.width(strMkr) + maxStrFreqLen,
                             SA_MARKER_SPACE_LINES, fm.width(" / "), fm.height(), Qt::AlignRight, " / ");
            painter.drawText(MARKER_LEFT_MARGIN + MarkerTablePixmap.width()/3 * 2 + fm.width(strMkr) + maxStrFreqLen + fm.width(" / "),
                             SA_MARKER_SPACE_LINES, maxStrAmpLen, fm.height(), Qt::AlignRight, strAmpt);
        }
        else if(i == 3)
        {
            painter.drawText(MARKER_LEFT_MARGIN + fm.width(strMkr),fm.height() + 2*SA_MARKER_SPACE_LINES, maxStrFreqLen, fm.height(), Qt::AlignRight, strFreq);
            painter.drawText(MARKER_LEFT_MARGIN + fm.width(strMkr) + maxStrFreqLen,fm.height() + 2*SA_MARKER_SPACE_LINES, fm.width(" / "), fm.height(), Qt::AlignRight, " / ");
            painter.drawText(MARKER_LEFT_MARGIN + fm.width(strMkr) + maxStrFreqLen + fm.width(" / "),fm.height() + 2*SA_MARKER_SPACE_LINES, maxStrAmpLen, fm.height(), Qt::AlignRight, strAmpt);
        }
        else if(i == 4)
        {
            painter.drawText(MARKER_LEFT_MARGIN + MarkerTablePixmap.width()/3 + fm.width(strMkr),
                             2*SA_MARKER_SPACE_LINES + fm.height(), maxStrFreqLen, fm.height(), Qt::AlignRight, strFreq);
            painter.drawText(MARKER_LEFT_MARGIN + MarkerTablePixmap.width()/3 + fm.width(strMkr) + maxStrFreqLen,
                             2*SA_MARKER_SPACE_LINES + fm.height(), fm.width(" / "), fm.height(), Qt::AlignRight, " / ");
            painter.drawText(MARKER_LEFT_MARGIN + MarkerTablePixmap.width()/3 + fm.width(strMkr) + maxStrFreqLen + fm.width(" / "),
                             2*SA_MARKER_SPACE_LINES + fm.height(), maxStrAmpLen, fm.height(), Qt::AlignRight, strAmpt);
        }
        else if(i == 5)
        {
            painter.drawText(MARKER_LEFT_MARGIN + MarkerTablePixmap.width()/3 * 2 + fm.width(strMkr),
                             2*SA_MARKER_SPACE_LINES + fm.height(), maxStrFreqLen, fm.height(), Qt::AlignRight, strFreq);
            painter.drawText(MARKER_LEFT_MARGIN + MarkerTablePixmap.width()/3 * 2 + fm.width(strMkr) + maxStrFreqLen,
                             2*SA_MARKER_SPACE_LINES + fm.height(), fm.width(" / "), fm.height(), Qt::AlignRight, " / ");
            painter.drawText(MARKER_LEFT_MARGIN + MarkerTablePixmap.width()/3 * 2 + fm.width(strMkr) + maxStrFreqLen + fm.width(" / "),
                             2*SA_MARKER_SPACE_LINES + fm.height(), maxStrAmpLen, fm.height(), Qt::AlignRight, strAmpt);
        }
    }
}
void sa_widget_markerTable::paintEvent(QPaintEvent *event)
{
    QStylePainter painter(this);
    painter.drawPixmap(0,0,MarkerTablePixmap);
}
void sa_widget_markerTable::setPixmapSize(qint32 mWidth,qint32 mHeight)
{
    MarkerTablePixmap = MarkerTablePixmap.scaled(mWidth,mHeight,Qt::IgnoreAspectRatio,Qt::FastTransformation);
}
