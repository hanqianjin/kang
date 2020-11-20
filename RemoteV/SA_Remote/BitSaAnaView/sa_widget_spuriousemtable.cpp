#include "sa_widget_spuriousemtable.h"
#include "ui_sa_widget_spuriousemtable.h"
#include <QPainter>
#include <QStylePainter>
#include "sa_colordef.h"
sa_widget_SpuriousEMTable::sa_widget_SpuriousEMTable(controlInterface &interface,user_variable &m_user_variable, user_limit &m_user_limit, QWidget *parent) :
    QWidget(parent),
    globalUserVariable(&m_user_variable),
    globalUserLimit(&m_user_limit),
    mControl(&interface),
    ui(new Ui::sa_widget_SpuriousEMTable)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/);

    ui->setupUi(this);
    setProperty("status",qssMode[interface.GetDisplayMode()]);
    SpuriousEMTablePixmap = QPixmap(SMALLDRAW_WIDTH, SPECEM_TABLE_HEIGHT);
    initDisplay();
}

sa_widget_SpuriousEMTable::~sa_widget_SpuriousEMTable()
{
    delete ui;
}
/**
* @name          refreshSpuriousEMTable()
* @brief         Interface of refresh the table of spurious emission mask.
* @param
* @author        Tony
* @date          2019-05-05
*/
void sa_widget_SpuriousEMTable::refreshSpuriousEMTable()
{
    refreshPixmap();
    repaint(0,0,SpuriousEMTablePixmap.width(),SpuriousEMTablePixmap.height());
}
/**
* @name          initDisplay()
* @brief         Init display.
* @param
* @author        Tony
* @date          2019-05-05
*/
void sa_widget_SpuriousEMTable::initDisplay()
{
    qint32 colorMode = globalUserVariable->gDisplayMode;
    QColor TableBgColor = TableBackgroundColor[colorMode];
    QColor fontColor = TableFontColor[colorMode];
    QColor curFontColor = TableCurFontColor[colorMode];

    SpuriousEMTablePixmap.fill(TableBgColor);

    qint32 ColumNum = 6,mCurRangeIndex;
    QPainter painter(&SpuriousEMTablePixmap);
    QString RowContent[ColumNum];
    qint32  RowWidth[ColumNum],RowPos[ColumNum];
    qint32 rowIndex = 0;
    QFontMetrics fm = painter.fontMetrics();;
    //draw pixmap title
    QFont mContfont = QFont(QFont("Arial",10));
    mContfont.setWeight(QFont::Normal);
    QFont font = QFont(QFont("Arial",10));
    font.setWeight(QFont::Bold);
    QPen pen(fontColor);
    pen.setWidth(2);
    painter.setPen(pen);
    qreal widthStep = (qreal)  (SpuriousEMTablePixmap.width() - 175) / (ColumNum -3);
    RowPos[0]= 0;
    for(qint32 i=0;i<ColumNum;i++)
    {
        RowWidth[i] = widthStep;
    }
    RowWidth[0] = RowWidth[1] = 70;
    RowWidth[4] = 35;
    for(qint32 i=1;i<ColumNum;i++)
    {
         RowPos[i] = RowPos[i-1]+RowWidth[i-1];
    }
    fm = painter.fontMetrics();
    painter.setFont(font);
    mCurRangeIndex = globalUserVariable->gSpurEMCurDrawRangeIndex;
    //Title
    RowContent[0] = "Spur";
    RowContent[1] = "Range";
    RowContent[2] = "Frequency";
    RowContent[3] = "Amplitude";
    RowContent[4] = "Pass";
    RowContent[5] = "Limit";
    for(qint32 i=0;i<ColumNum;i++)
    {
        if(i == 4)
        {
            QPen tmpPen = painter.pen();
            painter.setPen(QColor(Qt::green));
            painter.drawText(RowPos[i],SA_SPUREM_SPACE_LINES * rowIndex, RowWidth[i], fm.height(), Qt::AlignLeft | Qt::AlignHCenter, RowContent[i]);
            painter.setPen(tmpPen);
        }else
        {
            painter.drawText(RowPos[i],SA_SPUREM_SPACE_LINES * rowIndex, RowWidth[i], fm.height(), Qt::AlignLeft | Qt::AlignHCenter, RowContent[i]);
        }
    }
}
/**
* @name          refreshPixmap()
* @brief         The control about refresh table.
* @param
* @author        Tony
* @date          2019-05-05
*/
void sa_widget_SpuriousEMTable::refreshPixmap()
{
    qint32 colorMode = globalUserVariable->gDisplayMode;
    QColor TableBgColor = TableBackgroundColor[colorMode];
    if(globalUserVariable->gMeasureStatus == SA_ON)
    {
        spurSearch();
        judgeSpurEMTestResult();
    }
    SpuriousEMTablePixmap.fill(TableBgColor);
    switch (globalUserVariable->gSpurEMTableMode)
    {
    case SA_SPUREM_MEASURE:
        // refreshAllRangeTable();
        refreshSingleRangeTable();
        break;
    case SA_SPUREM_SETTABLE_FREQ:
        refreshFreqSetTable();
        break;
    case SA_SPUREM_SETTABLE_LIMIT:
        refreshLimitSetTable();
        break;
    }
    return;
}

void sa_widget_SpuriousEMTable::paintEvent(QPaintEvent *event)
{
    QStylePainter painter(this);
    painter.drawPixmap(0,0,SpuriousEMTablePixmap);
}
/**
* @name          setPixmapSize()
* @brief         The interface about set pixmap size.
* @param
* @author        Tony
* @date          2019-05-05
*/
void sa_widget_SpuriousEMTable::setPixmapSize(qint32 mWidth,qint32 mHeight)
{
    SpuriousEMTablePixmap = SpuriousEMTablePixmap.scaled(mWidth,mHeight,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    initDisplay();
}
/**
* @name          refreshSingleRangeTable()
* @brief         A kind of refresh model about single range.
* @param
* @author        Tony
* @date          2019-05-05
*/
void sa_widget_SpuriousEMTable::refreshSingleRangeTable()
{
    qint32 colorMode = globalUserVariable->gDisplayMode;
    QColor fontColor = TableFontColor[colorMode];
    QColor curFontColor = TableCurFontColor[colorMode];

    QList<qint32> spurIdList;
    qint32 mValuePassFlag = 1;
    qint32 ColumNum = 6,mCurRangeIndex,mCurSpurIndex,mSpurCnt;
    qint32 mFocusSpur,RangeSpurCnt;
    QPainter painter(&SpuriousEMTablePixmap);
    QString RowContent[ColumNum];
    qint32  RowWidth[ColumNum],RowPos[ColumNum];
    qint32 rowIndex = 0,rowCnt;
    QFontMetrics fm = painter.fontMetrics();;
    //draw pixmap title
    QFont mContfont = QFont(QFont("Arial",10));
    mContfont.setWeight(QFont::Normal);
    QFont font = QFont(QFont("Arial",10));
    font.setWeight(QFont::Bold);
    QPen pen(fontColor);
    pen.setWidth(2);
    painter.setPen(pen);
    qreal widthStep = (qreal)  (SpuriousEMTablePixmap.width() - 175) / (ColumNum -3);
    RowPos[0]= 0;
    for(qint32 i=0;i<ColumNum;i++)
    {
        RowWidth[i] = widthStep;
    }
    RowWidth[0] = RowWidth[1] = 70;
    RowWidth[4] = 35;
    for(qint32 i=1;i<ColumNum;i++)
    {
         RowPos[i] = RowPos[i-1]+RowWidth[i-1];
    }
    fm = painter.fontMetrics();
    painter.setFont(font);
    mCurRangeIndex = globalUserVariable->gSpurEMCurDrawRangeIndex;
    //Title
    RowContent[0] = "Spur";
    RowContent[1] = "Range";
    RowContent[2] = "Frequency  ";
    RowContent[3] = "Amplitude  ";
    for(qint32 i =0;i<=mCurRangeIndex;i++)
    {
        if(globalUserVariable->gSpurEMViewStatus[i] == SA_ON)
        {
            qint32 cnt = globalUserVariable->gSpurEMSpurCnt[i];
            for(qint32 iSpur = 0;iSpur<cnt;iSpur++)
            {
                if(globalUserVariable->gSpurEMSpur[i * SA_SPUREM_SPUR_CNT+iSpur].testValue == SA_FAIL)
                {
                    mValuePassFlag = 0;
                    break;
                }
            }
        }
    }
    if(mValuePassFlag)
    {
        RowContent[4] = "Pass";
    }else
    {
        RowContent[4] = "Fail";
    }

    RowContent[5] = "Limit  ";
    for(qint32 i=0;i<ColumNum;i++)
    {
        if(i == 4)
        {
            QPen tmpPen = painter.pen();
            if(mValuePassFlag)
            {
                painter.setPen(QColor(Qt::green));
            }else
            {
                painter.setPen(QColor(Qt::red));
            }
            painter.drawText(RowPos[i]-30,SA_SPUREM_SPACE_LINES * rowIndex, RowWidth[i], fm.height(), Qt::AlignCenter, RowContent[i]);
            painter.setPen(tmpPen);
        }else if(i == 0||i == 1)
        {
            painter.drawText(RowPos[i],SA_SPUREM_SPACE_LINES * rowIndex, RowWidth[i], fm.height(), Qt::AlignCenter, RowContent[i]);
        }else
        {
            painter.drawText(RowPos[i]-55,SA_SPUREM_SPACE_LINES * rowIndex, RowWidth[i], fm.height(),Qt::AlignRight|Qt::AlignHCenter , RowContent[i]);
        }
    }

    //draw measure information
    //Arranging information of range index which is on.
    painter.setFont(mContfont);
    mSpurCnt = 0;

    for(qint32 i = 0;i<=mCurRangeIndex;i++)
    {
        if(globalUserVariable->gSpurEMViewStatus[i]==SA_OFF)
            continue;
        RangeSpurCnt = globalUserVariable->gSpurEMSpurCnt[i];
        if(mControl->getSpurReportType()==SA_SPUREM_REPORT_ALL)
        {
            for(qint32 j=0;j<RangeSpurCnt;j++)
            {
                spurIdList<<i * SA_SPUREM_SPUR_CNT + j;
                mSpurCnt ++ ;
            }
        }else
        {
            for(qint32 j=0;j<RangeSpurCnt;j++)
            {
                if(globalUserVariable->gSpurEMSpur[i * SA_SPUREM_SPUR_CNT + j].testValue == SA_FAIL)
                {
                    spurIdList<<i * SA_SPUREM_SPUR_CNT + j;
                    mSpurCnt ++ ;
                }
            }
        }
    }
    globalUserVariable->gSpurEMTotalSpurCnt = mSpurCnt;

    if(globalUserVariable->gMeasureStatus == SA_OFF)
    {
        mCurSpurIndex = globalUserVariable->gSpurEMCurSpurIndex;
    }else //finish measure
    {
        mCurSpurIndex = mSpurCnt - 1;
        globalUserVariable->gSpurEMCurSpurIndex = mCurSpurIndex;
    }
    if(mSpurCnt<1)
    {
        return;
    }

    if(mCurSpurIndex >= (SA_SPUREM_PAGESPUR_CNT -1))
    {
        rowCnt = SA_SPUREM_PAGESPUR_CNT;
        mFocusSpur = rowCnt -1;
    }else{
        if(mSpurCnt>= SA_SPUREM_PAGESPUR_CNT)
        {
            rowCnt = SA_SPUREM_PAGESPUR_CNT;
            mFocusSpur = mCurSpurIndex;
            mCurSpurIndex = SA_SPUREM_PAGESPUR_CNT-1;
        }else
        {
            rowCnt = mCurSpurIndex+1;
            mFocusSpur = mCurSpurIndex;
        }
    }

    //draw content
    for(qint32 row =0;row < rowCnt;row++)
    {
        if(mFocusSpur == row)
            painter.setPen(curFontColor);
        else
            painter.setPen(pen);
        rowIndex++;
        RowContent[0] = QString::number(mCurSpurIndex + 1 - rowCnt + row + 1);
        RowContent[1] = QString::number(globalUserVariable->gSpurEMSpur[spurIdList.at(mCurSpurIndex + 1 - rowCnt+row)].rangeIndex);
        RowContent[2] = globalUserVariable->freqValueToQstring(globalUserVariable->gSpurEMSpur[spurIdList.at(mCurSpurIndex + 1 - rowCnt+row)].freq);
        RowContent[3] = QString::number(globalUserVariable->gSpurEMSpur[spurIdList.at(mCurSpurIndex + 1 - rowCnt+row)].value)+" dBm";

        if(globalUserVariable->gSpurEMSpur[spurIdList.at(mCurSpurIndex + 1 - rowCnt+row)].testValue==SA_FAIL)
        {
            RowContent[4] = "F";
        }else {
            RowContent[4] = "";
        }

        RowContent[5] = QString::number(globalUserLimit->gSpurLimit[globalUserVariable->gSpurEMSpur[spurIdList.at(mCurSpurIndex + 1 - rowCnt+row)].xPtIndex].y())+" dBm";
        for(qint32 i=0;i<ColumNum;i++)
        {
            if(i == 4)
            {
                QPen tmpPen = painter.pen();
                painter.setPen(QColor(Qt::red));
                painter.drawText(RowPos[i]-30,SA_SPUREM_SPACE_LINES * rowIndex, RowWidth[i], fm.height(), Qt::AlignCenter, RowContent[i]);
                painter.setPen(tmpPen);
            }else if(i == 0 ||i == 1)
            {
                painter.drawText(RowPos[i],SA_SPUREM_SPACE_LINES * rowIndex, RowWidth[i], fm.height(), Qt::AlignCenter, RowContent[i]);
            }else
            {
                painter.drawText(RowPos[i]-55,SA_SPUREM_SPACE_LINES * rowIndex, RowWidth[i], fm.height(), Qt::AlignRight|Qt::AlignHCenter, RowContent[i]);
            }
        }
    }
}
/**
* @name          refreshLimitSetTable()
* @brief         A kind of refresh model about limit peak setup table.
* @param
* @author        Tony
* @date          2019-05-09
*/
void sa_widget_SpuriousEMTable::refreshLimitSetTable()
{
    qint32 colorMode = globalUserVariable->gDisplayMode;
    QColor fontColor = TableFontColor[colorMode];
    QColor curFontColor = TableCurFontColor[colorMode];

    QPainter painter(&SpuriousEMTablePixmap);
    QFontMetrics fm = painter.fontMetrics();;
    qint32 mCurRange,mStartRange,mCurRangeIndex;
    //draw pixmap title
    QFont fontTile = QFont(QFont("Arial",10));
    fontTile.setWeight(QFont::Bold);
    QPen pen(fontColor);
    pen.setWidth(2);
    painter.setPen(pen);
    qreal widthStep = (qreal)  SpuriousEMTablePixmap.width() / 6;

    qint32 rowIndex = 0;
    QString RowContent[6];

    mCurRangeIndex = globalUserVariable->gSpurEMCurRangeIndex;
    //Title
    painter.setFont(fontTile);
    RowContent[0] = "Range";
    RowContent[1] = "Start Limit";
    RowContent[2] = "Stop Limit";
    RowContent[3] = "Peak Definition";
    RowContent[4] = "Peak Threshold";
    RowContent[5] = "Atten";
    for(qint32 i=0;i<6;i++)
    {
        painter.drawText(i * widthStep,SA_SPUREM_SPACE_LINES * rowIndex , widthStep, fm.height(), Qt::AlignCenter, RowContent[i]);
    }
    //Content
    fontTile.setWeight(QFont::Normal);
    painter.setFont(fontTile);
    if(mCurRangeIndex > 4)
    {
        mCurRange = 4;
        mStartRange = mCurRangeIndex - mCurRange;
    }else
    {
        mCurRange = mCurRangeIndex;
        mStartRange = 0;
    }
    for(qint32 row = 0;row<5;row++)
    {
        rowIndex++;
        if(mCurRange == row)
           painter.setPen(curFontColor);
        else
           painter.setPen(pen);
        if(globalUserVariable->gSpurEMViewStatus[mStartRange+row]){
            RowContent[0] = QString::number(globalUserVariable->gSpurEMPara[mStartRange+row].index);
            RowContent[1] = QString().sprintf("%.2f dBm",globalUserVariable->gSpurEMPara[mStartRange+row].startLimit);
            RowContent[2] = QString().sprintf("%.2f dBm",globalUserVariable->gSpurEMPara[mStartRange+row].stopLimit);
            RowContent[3] = QString().sprintf("%.2f dB",globalUserVariable->gSpurEMPara[mStartRange+row].peakDefi);
            RowContent[4] = QString().sprintf("%.2f dBm",globalUserVariable->gSpurEMPara[mStartRange+row].peakThreshold);
            RowContent[5] = QString().sprintf("%.2f dB",globalUserVariable->gSpurEMPara[mStartRange+row].Atten);
        }
        else
        {
            RowContent[0] = QString::number(globalUserVariable->gSpurEMPara[mStartRange+row].index);
            RowContent[1] = QString("-- --");
            RowContent[2] = QString("-- --");
            RowContent[3] = QString("-- --");
            RowContent[4] = QString("-- --");
            RowContent[5] = QString("-- --");
        }
        for(qint32 i=0;i<6;i++)
        {
            painter.drawText(i * widthStep,SA_SPUREM_SPACE_LINES * rowIndex, widthStep, fm.height(), Qt::AlignCenter, RowContent[i]);
        }
    }
}
/**
* @name          refreshFreqSetTable()
* @brief         A kind of refresh model frequency BW sweep setup table.
* @param
* @author        Tony
* @date          2019-05-09
*/
void sa_widget_SpuriousEMTable::refreshFreqSetTable()
{
    qint32 colorMode = globalUserVariable->gDisplayMode;
    QColor fontColor = TableFontColor[colorMode];
    QColor curFontColor = TableCurFontColor[colorMode];

    QPainter painter(&SpuriousEMTablePixmap);
    QFontMetrics fm = painter.fontMetrics();;
    qint32 mCurRange,mStartRange,mCurRangeIndex;
    //draw pixmap title
    QFont fontTile = QFont(QFont("Arial",10));
    fontTile.setWeight(QFont::Bold);
    QPen pen(fontColor);
    pen.setWidth(2);
    painter.setPen(pen);
    qreal widthStep = (qreal)  SpuriousEMTablePixmap.width() / 6;

    qint32 rowIndex = 0;
    QString RowContent[6];

    mCurRangeIndex = globalUserVariable->gSpurEMCurRangeIndex;
    //Title
    painter.setFont(fontTile);
    RowContent[0] = "Range";
    RowContent[1] = "Start Freq";
    RowContent[2] = "Stop Freq";
    RowContent[3] = "RBW";
    RowContent[4] = "VBW";
    RowContent[5] = "Sweep Time";
    for(qint32 i=0;i<6;i++)
    {
        painter.drawText(i * widthStep,SA_SPUREM_SPACE_LINES * rowIndex , widthStep, fm.height(), Qt::AlignCenter, RowContent[i]);
    }
    //Content
    fontTile.setWeight(QFont::Normal);
    painter.setFont(fontTile);
    if(mCurRangeIndex > 4)
    {
        mCurRange = 4;
        mStartRange = mCurRangeIndex - mCurRange;
    }else
    {
        mCurRange = mCurRangeIndex;
        mStartRange = 0;
    }
    for(qint32 row = 0;row<5;row++)
    {
        rowIndex++;
        if(mCurRange == row)
           painter.setPen(curFontColor);
        else
           painter.setPen(pen);
        if(globalUserVariable->gSpurEMViewStatus[mStartRange+row]){
        RowContent[0] = QString::number(globalUserVariable->gSpurEMPara[mStartRange+row].index);
        RowContent[1] = globalUserVariable->freqValueToQstring(globalUserVariable->gSpurEMPara[mStartRange+row].startFreq,3);
        RowContent[2] = globalUserVariable->freqValueToQstring(globalUserVariable->gSpurEMPara[mStartRange+row].stopFreq,3);
        RowContent[3] = globalUserVariable->freqValueToQstring(globalUserVariable->gSpurEMPara[mStartRange+row].RBW,3);
        RowContent[4] = globalUserVariable->freqValueToQstring(globalUserVariable->gSpurEMPara[mStartRange+row].VBW,3);
        RowContent[5] = globalUserVariable->TimeTransformToQstring(globalUserVariable->gSpurEMPara[mStartRange+row].SweepTime);
        }
        else
        {
            RowContent[0] = QString::number(globalUserVariable->gSpurEMPara[mStartRange+row].index);
            RowContent[1] = QString("-- --");
            RowContent[2] = QString("-- --");
            RowContent[3] = QString("-- --");
            RowContent[4] = QString("-- --");
            RowContent[5] = QString("-- --");
        }
        for(qint32 i=0;i<6;i++)
        {
            painter.drawText(i * widthStep,SA_SPUREM_SPACE_LINES * rowIndex, widthStep, fm.height(), Qt::AlignCenter, RowContent[i]);
        }
    }
}
/**
* @name          spurSearch()
* @brief         Search for all required spur points
* @param
* @author        Tony
* @date          2019-05-10
*/

void sa_widget_SpuriousEMTable::spurSearch()
{
    qint32 flag;
    qreal peakDefi,peakThreshold;
    qreal beforeVal,afterVal,curentVal,minVal;
    qint32 curentIndex,startIndex,stopIndex;
    qint32 curRangeIndex,mSpurCnt,mPeakCnt,mStartSpurIndex;
    QMap <qreal,qint32> ExtremumPts;
    curRangeIndex = globalUserVariable->gSpurEMCurDrawRangeIndex;
    mStartSpurIndex = curRangeIndex * SA_SPUREM_SPUR_CNT;
    peakDefi = globalUserVariable->gSpurEMPara[curRangeIndex].peakDefi;
    peakThreshold = globalUserVariable->gSpurEMPara[curRangeIndex].peakThreshold;
    globalUserVariable->gSpurEMSpurCnt[curRangeIndex] = 0;
    //Finding Extremum Points
    for(qint32 i=1;i<NUM_SWEEP_POINT-1;i++)
    {
        flag = 1;
        beforeVal =  globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i - 1];
        afterVal =  globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i + 1];
        curentVal = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i];
        if(curentVal>=beforeVal && curentVal >=afterVal)
        {
            if(curentVal>peakThreshold)
            {
                ExtremumPts.insert(curentVal,i);
            }
        }
    }

    mPeakCnt = ExtremumPts.size();
    for(qint32 i=mPeakCnt-1;i>=0;i--)
    {
        //find left min point
        //and complete the value of max and min
        curentIndex = ExtremumPts.values().at(i);
        curentVal = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][curentIndex];
        startIndex = curentIndex-1;
        stopIndex = 0;
        for(qint32 j=startIndex;j>=stopIndex;j--)
        {
            if(j==0)
            {
                minVal = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][j];
                if(curentVal < minVal+peakDefi)
                {
                    flag = 0;
                }
            }
            beforeVal = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][j];
            afterVal = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][j-1];
            if(afterVal > beforeVal)
            {
                minVal = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][j];
                if(curentVal < minVal+peakDefi)
                {
                    flag = 0;
                }
                break;
            }
        }
        if(!flag) continue;
        //find right min point
        //and complete the value of max and min
        startIndex = curentIndex+1;
        stopIndex = globalUserVariable->gSweepTracePoint;
        for(qint32 j=startIndex;j<=stopIndex;j++)
        {
            if(j==stopIndex)
            {
                minVal = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][j];
                if(curentVal < minVal + peakDefi)
                {
                    flag = 0;
                }
            }
            beforeVal = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][j];
            afterVal = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][j+1];
            if(afterVal > beforeVal)
            {
                minVal = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][j];
                if(curentVal < minVal+peakDefi)
                {
                    flag = 0;
                }
                break;
            }
        }
        if(!flag) break;
        ++globalUserVariable->gSpurEMSpurCnt[curRangeIndex];
        mSpurCnt = globalUserVariable->gSpurEMSpurCnt[curRangeIndex];
        if(mSpurCnt<=SA_SPUREM_SPUR_CNT)
        {
            globalUserVariable->gSpurEMSpur[mStartSpurIndex+mSpurCnt-1].freq = globalUserVariable->gStartFreq + (globalUserVariable->gStepFreq * curentIndex);
            globalUserVariable->gSpurEMSpur[mStartSpurIndex+mSpurCnt-1].value = curentVal;
            globalUserVariable->gSpurEMSpur[mStartSpurIndex+mSpurCnt-1].xPtIndex = curentIndex;
            globalUserVariable->gSpurEMSpur[mStartSpurIndex+mSpurCnt-1].rangeIndex = curRangeIndex + 1;
        }
        if(mSpurCnt +1 >SA_SPUREM_SPUR_CNT)
        {
            break;
        }
    }
    return;
}

void sa_widget_SpuriousEMTable::judgeSpurEMTestResult()
{
    qreal mLimit,mAmpt;
    qint32 curRange = globalUserVariable->gSpurEMCurDrawRangeIndex;
    for(qint32 i = 0;i < SA_SPUREM_SPUR_CNT;i++)
    {
        globalUserVariable->gSpurEMSpur[curRange *SA_SPUREM_SPUR_CNT +i].testValue = SA_PASS;
    }
    if(globalUserVariable->gSpecEMViewStatus[curRange] == SA_OFF) return;
    for(qint32 i = 0;i < SA_SPUREM_SPUR_CNT;i++)
    {
        mLimit = globalUserLimit->gSpurLimit[globalUserVariable->gSpurEMSpur[curRange *SA_SPUREM_SPUR_CNT +i].xPtIndex].y();
        mAmpt = globalUserVariable->gSpurEMSpur[curRange *SA_SPUREM_SPUR_CNT +i].value;
        if(mAmpt > mLimit)
        {
            globalUserVariable->gSpurEMSpur[curRange *SA_SPUREM_SPUR_CNT +i].testValue = SA_FAIL;
        }
    }
    return;
}


