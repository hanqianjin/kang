#include "sa_widget_spectrumemtable.h"
#include "ui_sa_widget_spectrumemtable.h"
#include <QPainter>
#include <QStylePainter>
#include "sa_colordef.h"
sa_widget_SpectrumEMTable::sa_widget_SpectrumEMTable(controlInterface &interface,user_variable &m_user_variable, user_limit &m_user_limit, QWidget *parent) :
    QWidget(parent),
    globalUserVariable(&m_user_variable),
    globalUserLimit(&m_user_limit),
    mControl(&interface),
    ui(new Ui::sa_widget_SpectrumEMTable)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/);

    ui->setupUi(this);
    setProperty("status",qssMode[interface.GetDisplayMode()]);
    SpectrumEMTablePixmap = QPixmap(SMALLDRAW_WIDTH, SPECEM_TABLE_HEIGHT);
    firstDisplay = 0;
}

sa_widget_SpectrumEMTable::~sa_widget_SpectrumEMTable()
{
    delete ui;
}

void sa_widget_SpectrumEMTable::initDisplay()
{
    qint32 colorMode = globalUserVariable->gDisplayMode;
    QColor TableBgColor = TableBackgroundColor[colorMode];
    QColor fontColor = TableFontColor[colorMode];
    QColor curFontColor = TableCurFontColor[colorMode];
    if(firstDisplay)
        return;
    else
        firstDisplay = 1;
    //table_height = 190//130
    SpectrumEMTablePixmap.fill(TableBgColor);
    QPainter painter(&SpectrumEMTablePixmap);
    QString RowContent[11];
    qint32 rowIndex = 0;
    qint32 mDisplayMode,mRefType,peakPos;
    qreal TotalPwr,PSDRef,SpecRef,InteBW,startFreq;
    QString strGab;
    QFontMetrics fm = painter.fontMetrics();;
    //draw pixmap title
    QFont font = QFont(QFont("Arial",10));
    font.setWeight(QFont::Bold);
    QPen pen(fontColor);
    pen.setWidth(2);
    painter.setPen(pen);
    qint32  RowWidth[11],RowPos[11];
    qreal widthStep = (qreal)  (SpectrumEMTablePixmap.width() - 64) / 9;
    RowWidth[0] = RowWidth[1] = RowWidth[2] = widthStep;
    RowWidth[4] = RowWidth[5] = widthStep;
    RowWidth[8] = RowWidth[9] = widthStep;
    RowWidth[6] = RowWidth[10] = 12;
    RowWidth[3] = RowWidth[7] = widthStep+20;
    RowPos[0] = 0;
    for(qint32 i = 1;i <11;i++)
    {
        RowPos[i] = RowPos[i-1]+RowWidth[i-1];
    }

    mDisplayMode = mControl->getSpecEMDisplay();
    mRefType = mControl->getSpecEMRefType();
    //TotalPwr = mControl->getSpecEMTotalPowerRef();
    //InteBW = mControl->getInteBW();
    //startFreq = (qreal)mControl->getCenterFreq() - InteBW/2;
    //TotalPwr = calculateTotalPwr(startFreq,InteBW);
    //first row and sec row  Power//PSD//spectrum peak
    painter.setFont(QFont("Arial",12));
    fm = painter.fontMetrics();
    //strGab = QString("Ref Carrier Power %1 dBm/%2").arg(QString::number(TotalPwr,'f',2)).arg(globalUserVariable->freqValueToQstring(InteBW)); //"Power  -64.10dBm/3.84MHz"
    strGab = QString(" Reference Carrier Power -- dBm/MHz");
    painter.drawText(0 * widthStep + 10,SA_SPECEM_SPACE_LINES * rowIndex + 5 , fm.width(strGab), fm.height(), Qt::AlignLeft, strGab);
    switch (mRefType) {
    case 0://Total Pwr Ref
        break;
    case 1://PSD Ref
        //PSDRef = calculatePSD(TotalPwr,InteBW);
        strGab = QString("PSD Ref -- dBm/Hz");
        painter.drawText(0 * widthStep + 10 + SpectrumEMTablePixmap.width()/2,SA_SPECEM_SPACE_LINES * rowIndex + 5 , fm.width(strGab), fm.height(), Qt::AlignLeft, strGab);
        break;
    case 2://Spectrum Peak Ref
        //peakPos = calculateSpecPeak(startFreq,InteBW); //mControl->getSpecEMPeakRef();
        //SpecRef = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][peakPos];
        strGab = QString("Spectrum Peak Ref -- dBm");
        painter.drawText(0 * widthStep + 10 + SpectrumEMTablePixmap.width()/2,SA_SPECEM_SPACE_LINES * rowIndex + 5 , fm.width(strGab), fm.height(), Qt::AlignLeft, strGab);
        break;
    }
    //Title  Lower//Upper
    rowIndex ++;
    fm = painter.fontMetrics();
    painter.setFont(font);
    painter.drawText(4 * widthStep + 10,SA_SPECEM_SPACE_LINES * rowIndex, fm.width("Low"), fm.height(), Qt::AlignLeft, "Low");
    painter.drawText(7 * widthStep + 10,SA_SPECEM_SPACE_LINES * rowIndex, fm.width("High"),  fm.height(), Qt::AlignLeft, "High");
    rowIndex ++;
    //Title
    RowContent[0] = "Start";
    RowContent[1] = "Stop";
    RowContent[2] = "RBW";
    RowContent[4] = "△Limit(dB)";
    RowContent[8] = "△Limit(dB)";
    switch (mDisplayMode) {
    case 0:// Abs Freq && Freq
        switch (mRefType)
        {
        case 0://Total Pwr Ref
        case 2://Spectrum Peak Ref
            RowContent[3] = "Peak Pwr(dBm)";
            RowContent[5] = "Freq";
            RowContent[7] = "Peak Pwr(dBm)";
            RowContent[9] = "Freq";
            break;
        case 1://PSD Ref
            RowContent[3] = "dBm/Hz";
            RowContent[5] = "Freq(Hz)";
            RowContent[7] = "dBm/Hz";
            RowContent[9] = "Freq(Hz)";
            break;
        }
        break;
    case 1:// Rel Freq && Freq
        switch (mRefType)
        {
        case 0://Total Pwr Ref
            RowContent[3] = "dBc";
            RowContent[5] = "Freq";
            RowContent[7] = "dBc";
            RowContent[9] = "Freq";
            break;
        case 1://PSD Ref
        case 2://Spectrum Peak Ref
            RowContent[3] = "dB";
            RowContent[5] = "Freq";
            RowContent[7] = "dB";
            RowContent[9] = "Freq";
            break;
        }
        break;
    case 2:// Inte Power
        switch (mRefType)
        {
        case 0://Total Pwr Ref
            RowContent[3] = "dBc";
            RowContent[5] = "dBm";
            RowContent[7] = "dBc";
            RowContent[9] = "dBm";
            break;
        case 1://PSD Ref
            RowContent[3] = "dB";
            RowContent[5] = "dBm/Hz";
            RowContent[7] = "dB";
            RowContent[9] = "dBm/Hz";
            break;
        case 2://Spectrum Peak Ref
            RowContent[3] = "dB";
            RowContent[5] = "dBm";
            RowContent[7] = "dB";
            RowContent[9] = "dBm";
            break;
        }
        break;
    }
    for(qint32 i=0;i<11;i++)
    {
        painter.drawText(RowPos[i],SA_SPECEM_SPACE_LINES * rowIndex, RowWidth[i], fm.height(), Qt::AlignHCenter, RowContent[i]);
    }
    //draw pixmap content
    font.setWeight(QFont::Normal);
    painter.setFont(font);
    pen.setColor(curFontColor);
    pen.setWidth(1);
    painter.setPen(pen);
    fm = painter.fontMetrics();

    //content
    rowIndex ++;
    for(qint32 i=0;i<SA_SPECEM_FREQ_CNT;i++)
    {
        RowContent[0] = globalUserVariable->freqValueToQstring(globalUserVariable->gSpecEMData[i].start+globalUserVariable->gSpecEMRefChBw/2,3);
        RowContent[1] = globalUserVariable->freqValueToQstring(globalUserVariable->gSpecEMData[i].stop+globalUserVariable->gSpecEMRefChBw/2,3);
        RowContent[2] = globalUserVariable->freqValueToQstring(globalUserVariable->gSpecEMData[i].rbw,3);
        for(qint32 j =3 ;j < 11;j++)
        {
            RowContent[j] ="-- --";
        }
        RowContent[6] ="";
        RowContent[10] ="";
        for(qint32 i=0;i<11;i++)
        {
            painter.drawText(RowPos[i],SA_SPECEM_SPACE_LINES * rowIndex, RowWidth[i], fm.height(), Qt::AlignHCenter, RowContent[i]);
        }
        rowIndex ++;
    }
}
void sa_widget_SpectrumEMTable::refreshSpectrumEMTable()
{
    if(globalUserVariable->gSpanFreq == 0)
    {
        initDisplay();
    }else
    {
        refreshPixmap();
    }
    repaint(0,0,SpectrumEMTablePixmap.width(),SpectrumEMTablePixmap.height());
}

void sa_widget_SpectrumEMTable::refreshPixmap()
{
    qint32 freqCnt;
    if(globalUserVariable->gSpecEMMaskType == SA_SPECEM_DEFAULT)
    {
        freqCnt = SA_SPECEM_FREQ_CNT;
    }else
    {
        freqCnt = SA_SPECEM_FREQ_CNT_5GNR;
    }
    //table_height = 190//130
    qint32 colorMode = globalUserVariable->gDisplayMode;
    QColor TableBgColor = TableBackgroundColor[colorMode];
    QColor fontColor = TableFontColor[colorMode];
    QColor curFontColor = TableCurFontColor[colorMode];

    SpectrumEMTablePixmap.fill(TableBgColor);
    QPainter painter(&SpectrumEMTablePixmap);
    QString RowContent[11];
    qint32  RowWidth[11],RowPos[11];
    qint32 rowIndex = 0;
    qint32 mDisplayMode,mRefType,peakPos;
    qreal TotalPwr,PSDRef,SpecRef,InteBW,startFreq;
    qreal measureBW,lowerStartFreq,upperStartFreq,lowerSpecRef,upperSpecRef,lowerPeakFreq,upperPeakFreq;
    qreal lowerPSDRef,lowerPower,upperPSDRef,upperPower;
    QString strGab;
    QFontMetrics fm = painter.fontMetrics();;
    //draw pixmap title
    QFont font = QFont(QFont("Arial",10));
    font.setWeight(QFont::Bold);
    QPen pen(fontColor);
    pen.setWidth(2);
    painter.setPen(pen);
    qreal widthStep = (qreal)  (SpectrumEMTablePixmap.width() - 64) / 9;
    qreal stepFreq =mControl->getSpan()/(NUM_SWEEP_POINT -1);
    RowWidth[0] = RowWidth[1] = RowWidth[2] = widthStep;
    RowWidth[4] = RowWidth[5] = widthStep;
    RowWidth[8] = RowWidth[9] = widthStep;
    RowWidth[6] = RowWidth[10] = 12;
    RowWidth[3] = RowWidth[7] = widthStep+20;
    RowPos[0] = 0;
    for(qint32 i = 1;i <11;i++)
    {
        RowPos[i] = RowPos[i-1]+RowWidth[i-1];
    }

    mDisplayMode = mControl->getSpecEMDisplay();
    mRefType = mControl->getSpecEMRefType();

    //first row and sec row  Power//PSD//spectrum peak
    painter.setFont(QFont("Arial",13));
    fm = painter.fontMetrics();

    InteBW = /*mControl->getInteBW()*/mControl->getSpecEMRefChBw();
    startFreq = (qreal)mControl->getCenterFreq() - InteBW/2;
    if(0 == mControl->globalUserVariable->gSpecEMSweepIndex)
    {
        TotalPwr = calculateTotalPwr(startFreq,InteBW);
        mControl->setSpecEMTotalPowerRef(TotalPwr);
    }else
    {
        TotalPwr = mControl->getSpecEMTotalPowerRef();
    }

    //strGab = QString("Ref Carrier Power %1 dBm/%2").arg(QString::number(TotalPwr,'f',2)).arg(globalUserVariable->freqValueToQstring(InteBW)); //"Power  -64.10dBm/3.84MHz"
    strGab = QString(" Reference Carrier Power %1 dBm").arg(QString::number(TotalPwr,'f',2));
    painter.drawText(10,SA_SPECEM_SPACE_LINES * rowIndex + 2 , fm.width(strGab), fm.height(), Qt::AlignLeft, strGab);

    strGab = QString("Channel Bandwidth %1").arg(globalUserVariable->freqValueToQstring(InteBW));
    painter.drawText(RowPos[7]+10,SA_SPECEM_SPACE_LINES * rowIndex + 2 , fm.width(strGab), fm.height(), Qt::AlignLeft, strGab);
    switch (mRefType) {
    case 0://Total Pwr Ref
        break;
    case 1://PSD Ref
        PSDRef = calculatePSD(TotalPwr,InteBW);
        strGab = QString("PSD Ref %1 dBm/Hz").arg(QString::number(PSDRef,'f',2));
        painter.drawText(10 + SpectrumEMTablePixmap.width()/2,SA_SPECEM_SPACE_LINES * rowIndex + 2 , fm.width(strGab), fm.height(), Qt::AlignLeft, strGab);
        break;
    case 2://Spectrum Peak Ref
        peakPos = calculateSpecPeak(startFreq,InteBW); //mControl->getSpecEMPeakRef();
        SpecRef = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][peakPos];
        strGab = QString("Spectrum Peak Ref %1 dBm").arg(QString::number(SpecRef,'f',2));
        painter.drawText(10 + SpectrumEMTablePixmap.width()/2,SA_SPECEM_SPACE_LINES * rowIndex + 2 , fm.width(strGab), fm.height(), Qt::AlignLeft, strGab);
        break;
    }
    //Title  Lower//Upper
    rowIndex ++;
    fm = painter.fontMetrics();
    painter.setFont(font);
    painter.drawText(RowPos[4],SA_SPECEM_SPACE_LINES * rowIndex, RowWidth[4], fm.height(), Qt::AlignHCenter, "Low");
    painter.drawText(RowPos[8],SA_SPECEM_SPACE_LINES * rowIndex, RowWidth[8], fm.height(), Qt::AlignHCenter, "High");
    rowIndex ++;
    //Title
    RowContent[0] = "Start";
    RowContent[1] = "Stop";
    RowContent[2] = "RBW";
    RowContent[4] = "△Limit(dB)";
    RowContent[8] = "△Limit(dB)";
    switch (mDisplayMode) {
    case 0:// Abs Freq && Freq
        switch (mRefType)
        {
        case 0://Total Pwr Ref
        case 2://Spectrum Peak Ref
            RowContent[3] = "Peak Pwr(dBm)";
            RowContent[5] = "Freq";
            RowContent[7] = "Peak Pwr(dBm)";
            RowContent[9] = "Freq";
            break;
        case 1://PSD Ref
            RowContent[3] = "dBm/Hz";
            RowContent[5] = "Freq";
            RowContent[7] = "dBm/Hz";
            RowContent[9] = "Freq";
            break;
        }
        break;
    case 1:// Rel Freq && Freq
        switch (mRefType)
        {
        case 0://Total Pwr Ref
            RowContent[3] = "dBc";
            RowContent[5] = "Freq";
            RowContent[7] = "dBc";
            RowContent[9] = "Freq";
            break;
        case 1://PSD Ref
        case 2://Spectrum Peak Ref
            RowContent[3] = "dB";
            RowContent[5] = "Freq";
            RowContent[7] = "dB";
            RowContent[9] = "Freq";
            break;
        }
        break;
    case 2:// Inte Power
        switch (mRefType)
        {
        case 0://Total Pwr Ref
            RowContent[3] = "dBc";
            RowContent[5] = "dBm";
            RowContent[7] = "dBc";
            RowContent[9] = "dBm";
            break;
        case 1://PSD Ref
            RowContent[3] = "dB";
            RowContent[5] = "dBm/Hz";
            RowContent[7] = "dB";
            RowContent[9] = "dBm/Hz";
            break;
        case 2://Spectrum Peak Ref
            RowContent[3] = "dB";
            RowContent[5] = "dBm";
            RowContent[7] = "dB";
            RowContent[9] = "dBm";
            break;
        }
        break;
    }
    for(qint32 i=0;i<11;i++)
    {
        painter.drawText(RowPos[i],SA_SPECEM_SPACE_LINES * rowIndex, RowWidth[i], fm.height(), Qt::AlignHCenter, RowContent[i]);
    }
    //draw pixmap content
    font.setWeight(QFont::Normal);
    painter.setFont(font);
    pen.setColor(curFontColor);
    pen.setWidth(1);
    painter.setPen(pen);
    fm = painter.fontMetrics();

    //content
    rowIndex ++;
    for(qint32 i=0;i<SA_SPECEM_FREQ_CNT;i++)
    {
        RowContent[0] = globalUserVariable->freqValueToQstring(globalUserVariable->gSpecEMData[i].start+globalUserVariable->gSpecEMRefChBw/2,3);
        RowContent[1] = globalUserVariable->freqValueToQstring(globalUserVariable->gSpecEMData[i].stop+globalUserVariable->gSpecEMRefChBw/2,3);
        RowContent[2] = globalUserVariable->freqValueToQstring(globalUserVariable->gSpecEMData[i].rbw,3);
        for(qint32 j =3 ;j < 11;j++)
        {
            RowContent[j] ="-- --";
        }
        RowContent[6] ="";
        RowContent[10] ="";

        if(globalUserVariable->gTraceView[globalUserVariable->gTraceSelect] == SA_OFF || globalUserVariable->gSpecEMViewStatus[i]== SA_OFF)
        {
            for(qint32 j=0;i<11;i++)
            {
                painter.drawText(RowPos[j],SA_SPECEM_SPACE_LINES * rowIndex,RowWidth[j] , fm.height(), Qt::AlignHCenter, RowContent[j]);
            }
        }
        else
        {
            //refresh tabel
            measureBW = globalUserVariable->gSpecEMData[i].stop - globalUserVariable->gSpecEMData[i].start;
            lowerStartFreq = (qreal)mControl->getCenterFreq() - (globalUserVariable->gSpecEMData[i].stop+globalUserVariable->gSpecEMRefChBw/2);
            peakPos = calculateSpecPeak(lowerStartFreq,measureBW);
            lowerSpecRef = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][peakPos]+globalUserVariable->gRefOffset;
            lowerPeakFreq = mControl->getStartFreq() + stepFreq * peakPos - mControl->getCenterFreq();

            lowerPower = calculateTotalPwr(lowerStartFreq,measureBW);
            lowerPSDRef = calculatePSD(lowerPower,measureBW);

            RowContent[4] = QString::number(lowerSpecRef - globalUserLimit->gSpurLimit[peakPos].y(),'f',2);

            if(lowerSpecRef - globalUserLimit->gSpurLimit[peakPos].y() > 0)
            {
                globalUserVariable->gSpecEMTestResult[i] = SA_FAIL;
            }else
            {
                globalUserVariable->gSpecEMTestResult[i] = SA_PASS;
            }

            upperStartFreq = (qreal)mControl->getCenterFreq() + (globalUserVariable->gSpecEMData[i].start+globalUserVariable->gSpecEMRefChBw/2);
            peakPos = calculateSpecPeak(upperStartFreq,measureBW);
            upperSpecRef = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][peakPos]+globalUserVariable->gRefOffset;
            upperPeakFreq = mControl->getStartFreq() + stepFreq * peakPos - mControl->getCenterFreq();

            upperPower = calculateTotalPwr(upperStartFreq,measureBW);
            upperPSDRef = calculatePSD(upperPower,measureBW);


            RowContent[8] = QString::number(upperSpecRef - globalUserLimit->gSpurLimit[peakPos].y(),'f',2);

            if(upperSpecRef - globalUserLimit->gSpurLimit[peakPos].y() > 0)
            {
                globalUserVariable->gSpecEMTestResult[i+freqCnt] = SA_FAIL;
            }else
            {
                globalUserVariable->gSpecEMTestResult[i+freqCnt] = SA_PASS;
            }

            switch (mDisplayMode) {
            case 0:// Abs Freq && Freq
                switch (mRefType)
                {
                case 0://Total Pwr Ref
                    RowContent[3] = QString::number(lowerSpecRef,'f',2);
                    RowContent[5] = globalUserVariable->freqValueToQstring(lowerPeakFreq,3);
                    RowContent[7] = QString::number(upperSpecRef,'f',2);
                    RowContent[9] = globalUserVariable->freqValueToQstring(upperPeakFreq,3);
                    break;
                case 1://Spectrum Peak Ref
                    RowContent[3] = QString::number(lowerSpecRef,'f',2);
                    RowContent[5] = globalUserVariable->freqValueToQstring(lowerPeakFreq,3);
                    RowContent[7] = QString::number(upperSpecRef,'f',2);
                    RowContent[9] = globalUserVariable->freqValueToQstring(upperPeakFreq,3);
                    break;
                case 2://PSD Ref
                    RowContent[3] = QString::number(lowerSpecRef,'f',2);
                    RowContent[5] = globalUserVariable->freqValueToQstring(lowerPeakFreq,3);
                    RowContent[7] = QString::number(upperSpecRef,'f',2);
                    RowContent[9] = globalUserVariable->freqValueToQstring(upperPeakFreq,3);
                    break;
                }
                break;
            case 1:// Rel Freq && Freq
                switch (mRefType)
                {
                case 0://Total Pwr Ref
                    RowContent[3] = QString::number(lowerSpecRef - TotalPwr,'f',2);
                    RowContent[5] = globalUserVariable->freqValueToQstring(lowerPeakFreq,3);
                    RowContent[7] = QString::number(upperSpecRef - TotalPwr,'f',2);
                    RowContent[9] = globalUserVariable->freqValueToQstring(upperPeakFreq,3);
                    break;
                case 1://PSD Ref
                    RowContent[3] = QString::number(lowerSpecRef - PSDRef,'f',2);
                    RowContent[5] = globalUserVariable->freqValueToQstring(lowerPeakFreq,3);
                    RowContent[7] = QString::number(upperSpecRef - PSDRef,'f',2);
                    RowContent[9] = globalUserVariable->freqValueToQstring(upperPeakFreq,3);
                    break;
                case 2://Spectrum Peak Ref
                    RowContent[3] = QString::number(lowerSpecRef - SpecRef,'f',2);
                    RowContent[5] = globalUserVariable->freqValueToQstring(lowerPeakFreq,3);
                    RowContent[7] = QString::number(upperSpecRef - SpecRef,'f',2);
                    RowContent[9] = globalUserVariable->freqValueToQstring(upperPeakFreq,3);
                    break;
                }
                break;
            case 2:// Inte Power
                switch (mRefType)
                {
                case 0://Total Pwr Ref
                    RowContent[3] = QString::number(lowerPower,'f',2);
                    RowContent[5] = QString::number(lowerPower - TotalPwr,'f',2);
                    RowContent[7] = QString::number(upperPower,'f',2);
                    RowContent[9] = QString::number(upperPower - TotalPwr,'f',2);
                    break;
                case 1://PSD Ref
                    RowContent[3] = QString::number(lowerPSDRef,'f',2);
                    RowContent[5] = QString::number(lowerPSDRef - PSDRef,'f',2);
                    RowContent[7] = QString::number(upperPSDRef,'f',2);
                    RowContent[9] = QString::number(upperPSDRef - PSDRef,'f',2);
                    break;
                case 2://Spectrum Peak Ref
                    RowContent[3] = QString::number(lowerSpecRef,'f',2);
                    RowContent[5] = QString::number(lowerSpecRef - TotalPwr,'f',2);
                    RowContent[7] = QString::number(upperSpecRef,'f',2);
                    RowContent[9] = QString::number(upperSpecRef - TotalPwr,'f',2);
                    break;
                }
                break;
            }

//            RowContent[4] = QString::number(lowerSpecRef - globalUserLimit->gSpurLimit[i].y(),'f',2);
//            RowContent[8] = QString::number(upperSpecRef - globalUserLimit->gSpurLimit[i].y(),'f',2);


            for(qint32 j=0;j<11;j++)
            {
                painter.drawText(RowPos[j],SA_SPECEM_SPACE_LINES * rowIndex, RowWidth[j], fm.height(), Qt::AlignHCenter, RowContent[j]);
            }
            //Draw test info

            if(globalUserVariable->gSpecEMTestResult[i] == SA_FAIL)
            {
                painter.setPen(Qt::red);
                RowContent[6] = "F";
                painter.drawText(RowPos[6],SA_SPECEM_SPACE_LINES * rowIndex, RowWidth[6], fm.height(), Qt::AlignHCenter, RowContent[6]);
            }else
            {
                painter.setPen(Qt::green);
                RowContent[6] = "P";
                painter.drawText(RowPos[6],SA_SPECEM_SPACE_LINES * rowIndex, RowWidth[6], fm.height(), Qt::AlignHCenter, RowContent[6]);

            }
            if(globalUserVariable->gSpecEMTestResult[i+freqCnt] == SA_FAIL)
            {
                painter.setPen(Qt::red);
                RowContent[10] = "F";
                painter.drawText(RowPos[10],SA_SPECEM_SPACE_LINES * rowIndex, RowWidth[10], fm.height(), Qt::AlignHCenter, RowContent[10]);
            }else
            {
                painter.setPen(Qt::green);
                RowContent[10] = "P";
                painter.drawText(RowPos[10],SA_SPECEM_SPACE_LINES * rowIndex, RowWidth[10], fm.height(), Qt::AlignHCenter, RowContent[10]);
            }
            painter.setPen(pen);
        }
        if(globalUserVariable->gSpecEMMaskType == SA_SPECEM_DEFAULT)
        {
            rowIndex ++;
        }else
        {
            rowIndex ++;
            rowIndex ++;// 5GNR
        }
    }

}

void sa_widget_SpectrumEMTable::paintEvent(QPaintEvent *event)
{
    QStylePainter painter(this);
    painter.drawPixmap(0,0,SpectrumEMTablePixmap);
}
void sa_widget_SpectrumEMTable::setPixmapSize(qint32 mWidth,qint32 mHeight)
{
    SpectrumEMTablePixmap = SpectrumEMTablePixmap.scaled(mWidth,mHeight,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    initDisplay();
}

qreal sa_widget_SpectrumEMTable::calculateTotalPwr(qreal startFreq,qreal mBandWidth)
{ 
    qreal mStartFreq = mControl->getStartFreq();

    qreal mSpan = mControl->getSpan();
    if(mSpan <= 0) return 0;
    qreal stepFreq = mSpan/(NUM_SWEEP_POINT -1);

    qreal powervalue = 0.,dbmPower = 0.;

    qint32 beginPointIndex =  (startFreq - mStartFreq)/stepFreq;
    qint32 endPointIndex   =  (startFreq + mBandWidth - mStartFreq)/stepFreq;

    if(endPointIndex == NUM_SWEEP_POINT) endPointIndex = NUM_SWEEP_POINT-1;

    for(qint32 i = beginPointIndex;i<endPointIndex+1;i++){
        dbmPower += pow(10, globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i] / 10.);
    }
    powervalue = 10 * log10((qreal)((qreal)mBandWidth/globalUserVariable->gRbw)/(endPointIndex - beginPointIndex + 1)*dbmPower);
    //mControl->setSpecEMTotalPowerRef(powervalue);
    return powervalue;
}

qreal sa_widget_SpectrumEMTable::calculatePSD(qreal mPower,qreal mBandWidth)
{
    qreal mPSD;
    mPSD = mPower -10*log10(mBandWidth);
    mControl->setSpecEMPSDRef(mPSD);
    return mPSD;
}

//return the point index of peak
qint32 sa_widget_SpectrumEMTable::calculateSpecPeak(qreal SEMStartFreq,qreal mBandWidth)
{
    //calculate interval point index
    qreal mStartFreq = mControl->getStartFreq();
    qreal mSpan = mControl->getSpan();
    qreal stepFreq = mSpan/(NUM_SWEEP_POINT -1);
    //first point
    qreal tmp =  (qreal)(SEMStartFreq - mStartFreq)/stepFreq;
    qint32 beginPointIndex = (qint32)(SEMStartFreq - mStartFreq)/stepFreq;
    if(tmp != beginPointIndex)
    {
        beginPointIndex = beginPointIndex+1;
    }
    tmp =  (qreal)(SEMStartFreq - mStartFreq)/stepFreq;
    qint32 endPointIndex   =  (qint32)(SEMStartFreq + mBandWidth - mStartFreq)/stepFreq;
    if(endPointIndex == tmp)
    {
        endPointIndex = endPointIndex-1;
    }
    if(endPointIndex == NUM_SWEEP_POINT) endPointIndex = NUM_SWEEP_POINT-1;
    //Search Peak
    qreal peakVal = 0.,peakFreq;
    qint32 i = beginPointIndex;
    qint32 peakPos = beginPointIndex;
    qreal beforeVal = 0.;
    qreal currentVal = 0;
    qreal afterVal = 0.;
    qreal lastPointVal = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][endPointIndex];
    for (i = beginPointIndex ; i < endPointIndex; i++)
    {
        currentVal = globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i];

        if (i == beginPointIndex)
          peakVal = currentVal ;
        else
        {
            if (peakVal < currentVal)
            {
                beforeVal =  globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i - 1];
                afterVal =  globalUserVariable->gTraceMeasureVal[globalUserVariable->gTraceSelect][i + 1];
                if (currentVal >= beforeVal && currentVal >= afterVal)
                {
                    peakVal = currentVal ;
                    peakPos = i;
                }
            }
         }
     }
    if(lastPointVal - peakVal > 0.)
    {
        peakVal = lastPointVal;
        peakPos = endPointIndex;
    }
   // peakFreq = mStartFreq + (stepFreq * peakPos);
    return peakPos;
}
