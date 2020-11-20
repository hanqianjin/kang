#include "rtsa_dialog_ch_std.h"
#include "ui_rtsa_dialog_ch_std.h"
#include <QFile>

RtSa_Dialog_Ch_Std::RtSa_Dialog_Ch_Std(Rtsa_Remote_Interface *RtsaRemoteInterface, RtSa_User_Variable *userVariable, QWidget *parent) :
    QWidget(parent),
    RemoteInterfaceObj(RtsaRemoteInterface),
    globalUserVariable(userVariable),
    ui(new Ui::RtSa_Dialog_Ch_Std)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    initMap();
    initWidget();
    initDisplay();
    setProperty("status",rtsa_qssMode[RemoteInterfaceObj->GetDisplayMode()]);
}

RtSa_Dialog_Ch_Std::~RtSa_Dialog_Ch_Std()
{
//    this->close();
    delete ui;
}

void RtSa_Dialog_Ch_Std::keyPressEvent(QKeyEvent *event)
{
    qint32 keyvalue = event->key();
    if(event->key() == Qt::Key_PowerOff)
    {
        if(!event->isAutoRepeat())
        {
            QApplication::sendEvent(this->parent(),event);
        }
        return;
    }
    switch (keyvalue) {
    case Qt::Key_Escape:
        this->close();
        break;
    case Qt::Key_Shift:
        RemoteInterfaceObj->setShiftKeyEnable(true);
        this->close();
        break;
    case Qt::Key_0:
    case Qt::Key_1:
    case Qt::Key_2:
    case Qt::Key_3:
    case Qt::Key_4:
    case Qt::Key_5:
    case Qt::Key_6:
    case Qt::Key_7:
    case Qt::Key_8:
    case Qt::Key_9:
    case Qt::Key_Period:
    case Qt::Key_Minus:  // - Minus
//    case Qt::Key_F2:    //  +/-
//    case Qt::Key_Shift:
    case Qt::Key_F6://key_left
    case Qt::Key_Right:
    case Qt::Key_F7:
        break;
    case Qt::Key_F3:
    case Qt::Key_Up:
    case Qt::Key_F8:
        break;
    case Qt::Key_Down:
    case Qt::Key_F9:
    case Qt::Key_F4:
        break;
    default:
        break;
    }
    return;
}

void RtSa_Dialog_Ch_Std::on_pb_cancel_clicked()
{
    this->close();
    return;
}
/**
 * @brief  Initialize map of indexes and controls.
 * @param  void
 * @author Tony
 * @since 2019-02-12
*/
void RtSa_Dialog_Ch_Std::initMap()
{
    mTypeGroup = new QButtonGroup();
    mTypeGroup->addButton(ui->pb_CDMA,RTSA_CDMA);
    mTypeGroup->addButton(ui->pb_GSM,RTSA_GSM);
    mTypeGroup->addButton(ui->pb_LTEFDD,RTSA_LTE_FDD);
    mTypeGroup->addButton(ui->pb_LTETDD,RTSA_LTE_TDD);
    mTypeGroup->addButton(ui->pb_TD,RTSA_TD_SCDMA);
    mTypeGroup->addButton(ui->pb_WCDMA,RTSA_WCDMA);
    mTypeGroup->addButton(ui->pb_WIMAX,RTSA_WIMAX);

    connect(mTypeGroup,SIGNAL(buttonClicked(qint32)),this,SLOT(runBtnTypeFunction(qint32)));
    return ;
}
/**
 * @brief  Init the display of frequency setup dialog.
 * @param  void
 * @author Tony
 * @since 2019-02-12
*/
void RtSa_Dialog_Ch_Std::initDisplay()
{
    curCHIndex = globalUserVariable->gMeterParam.gConfig_FreqSpan.channelSelID%9;
    tabPageIndex = globalUserVariable->gMeterParam.gConfig_FreqSpan.channelSelID/9;
    if(globalUserVariable->gMeterParam.gConfig_FreqSpan.channelStd>=0)
    {
        mTypeGroup->button(globalUserVariable->gMeterParam.gConfig_FreqSpan.channelStd)->setChecked(true);
    }else
    {
        mTypeGroup->button(0)->setChecked(true);
    }
    ChType = globalUserVariable->gMeterParam.gConfig_FreqSpan.channelStd;
    if(ChType < 0)
    {
        ChType = 0;
    }
    initTabContent(ChType);
    return;
}
/**
 * @brief  Init the widget.
 * @param  void
 * @author Tony
 * @since 2019-02-12
*/
void RtSa_Dialog_Ch_Std::initWidget()
{
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode( QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnWidth(0,259);
    ui->tableWidget->setColumnWidth(1,259);
    ui->tableWidget->setColumnWidth(2,237);
    connect(ui->tableWidget,SIGNAL(currentCellChanged(qint32,qint32,qint32,qint32)),this,SLOT(on_currentCellChanged(qint32,qint32,qint32,qint32)));
//    refreshEdit();
}

void RtSa_Dialog_Ch_Std::initTabContent(qint32 index)
{
    getBandInfo(index);
    initTabPage();
    return;
}


void RtSa_Dialog_Ch_Std::getBandInfo(qint32 STDIndex)
{
    QString name = QString(mRTSA_ChStand[STDIndex].name);
    QString filename = QString(":/rtsa/standard/%1").arg(name);
    QString str;
    QByteArray line;
    globalUserVariable->gCHName->clear();
    globalUserVariable->gCHStandard->clear();
    globalUserVariable->gFreqStandard->clear();
    QFile mFile(filename);
    if(mFile.open(QFile::ReadOnly))
    {
        while (!mFile.atEnd())
        {
            line = mFile.readLine();
            str = QString(line);
            analysisData(str);
        }
        mFile.close();
    }
    mFile.close();
    return;
}
void RtSa_Dialog_Ch_Std::analysisData(QString str)
{
    __RTSA_Standard__ mtmp;
    QStringList list = str.split(",");
    if(list.size() == 5)
    {
        globalUserVariable->gCHName->append(list[0]);
        mtmp.Up.Min = QString(list[1]).toDouble();
        mtmp.Up.Max = QString(list[2]).toDouble();
        mtmp.Down.Min = QString(list[1]).toDouble();
        mtmp.Down.Max = QString(list[2]).toDouble();
        globalUserVariable->gCHStandard->append(mtmp);

        mtmp.Up.Min = QString(list[3]).toDouble();
        mtmp.Up.Max = QString(list[4]).toDouble();
        mtmp.Down.Min = QString(list[3]).toDouble();
        mtmp.Down.Max = QString(list[4]).toDouble();
        globalUserVariable->gFreqStandard->append(mtmp);
    }else if(list.size() == 9)
    {
        globalUserVariable->gCHName->append(list[0]);
        mtmp.Up.Min = QString(list[1]).toDouble();
        mtmp.Up.Max = QString(list[2]).toDouble();
        mtmp.Down.Min = QString(list[3]).toDouble();
        mtmp.Down.Max = QString(list[4]).toDouble();
        globalUserVariable->gCHStandard->append(mtmp);

        mtmp.Up.Min = QString(list[5]).toDouble();
        mtmp.Up.Max = QString(list[6]).toDouble();
        mtmp.Down.Min = QString(list[7]).toDouble();
        mtmp.Down.Max = QString(list[8]).toDouble();
        globalUserVariable->gFreqStandard->append(mtmp);
    }


    return;
}
void RtSa_Dialog_Ch_Std::initTabPage()
{
    QVector < __RTSA_Standard__> *&ChannelRange = globalUserVariable->gCHStandard;
    QVector < __RTSA_Standard__> *&FreqRange = globalUserVariable->gFreqStandard;
    QString strname,strChannel,strFreq;
    qint32 index= globalUserVariable->gCHName->size();
    qint32 curIndex = curCHIndex;
    qint32 curPageBand;
    qint32 tmpBandIndex;
    if(index - (tabPageIndex) * 9 >= 9)
    {
        curPageBand = 9;
    }else
    {
        curPageBand = index - tabPageIndex * 9;
    }
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(curPageBand);
    ui->tableWidget->selectRow(curIndex);

    for(qint32 i =0;i < 9 && (tabPageIndex *9 +i) <index;i++)
    {
       tmpBandIndex = tabPageIndex *9 +i;
       strname = globalUserVariable->gCHName->at(tmpBandIndex);
       if(ChType == RTSA_LTE_TDD || ChType == RTSA_TD_SCDMA)
       {
           strChannel = QString("(%1 - %2)").arg(QString::number(ChannelRange->at(tmpBandIndex).Up.Min)).\
                   arg(QString::number(ChannelRange->at(tmpBandIndex).Up.Max));
           strFreq = QString("(%1 - %2)").arg(QString::number(FreqRange->at(tmpBandIndex).Up.Min)).\
                   arg(QString::number(FreqRange->at(tmpBandIndex).Up.Max));
       }else if(ChType == RTSA_GSM || ChType == RTSA_CDMA)
       {
           strChannel = QString("(%1 - %2)").arg(QString::number(ChannelRange->at(tmpBandIndex).Up.Min)).\
                   arg(QString::number(ChannelRange->at(tmpBandIndex).Up.Max));
           strFreq = QString("(%1 - %2)\n(%3 - %4)").arg(QString::number(FreqRange->at(tmpBandIndex).Up.Min)).\
                   arg(QString::number(FreqRange->at(tmpBandIndex).Up.Max)).arg(QString::number(FreqRange->at(tmpBandIndex).Down.Min)).\
                   arg(QString::number(FreqRange->at(tmpBandIndex).Down.Max));
       }
       else
       {
           strChannel = QString("(%1 - %2)\n(%3 - %4)").arg(QString::number(ChannelRange->at(tmpBandIndex).Up.Min)).\
                   arg(QString::number(ChannelRange->at(tmpBandIndex).Up.Max)).arg(QString::number(ChannelRange->at(tmpBandIndex).Down.Min)).\
                   arg(QString::number(ChannelRange->at(tmpBandIndex).Down.Max));
           strFreq = QString("(%1 - %2)\n(%3 - %4)").arg(QString::number(FreqRange->at(tmpBandIndex).Up.Min)).\
                   arg(QString::number(FreqRange->at(tmpBandIndex).Up.Max)).arg(QString::number(FreqRange->at(tmpBandIndex).Down.Min)).\
                   arg( QString::number(FreqRange->at(tmpBandIndex).Down.Max));
       }
       ui->tableWidget->setItem(i, 0, new QTableWidgetItem(strname));
       ui->tableWidget->setItem(i, 1, new QTableWidgetItem(strChannel));
       ui->tableWidget->setItem(i, 2, new QTableWidgetItem(strFreq));
    }
    return;
}

void RtSa_Dialog_Ch_Std::on_pb_up_clicked()
{
    qint32 totalPage,totalBand;
    totalBand = globalUserVariable->gCHName->size();
    if(!(totalBand%9))
    {
        totalPage = totalBand /9;
    }else
    {
        totalPage = totalBand / 9 +1;
    }
    if(tabPageIndex-1 <0 || (tabPageIndex+1-1) > totalPage)
        return;
    tabPageIndex -= 1;
    curCHIndex =0;
    initTabPage();
    return;
}

void RtSa_Dialog_Ch_Std::on_pb_down_clicked()
{
    qint32 totalPage,totalBand;
    totalBand = globalUserVariable->gCHName->size();
    if(!(totalBand%9))
    {
        totalPage = totalBand /9;
    }else
    {
        totalPage = totalBand / 9 +1;
    }
    if(tabPageIndex+1 <0 || (tabPageIndex+1+1) > totalPage)
        return;
    tabPageIndex += 1;
    curCHIndex = 0;
    initTabPage();
    return;
}

void RtSa_Dialog_Ch_Std::runBtnTypeFunction(qint32 index)
{
    globalUserVariable->gMeterParam.gConfig_FreqSpan.channelSelID = 0;
    ChType = index;
//    mControl->setCHStandard(index);
    curCHIndex = 0;
    tabPageIndex = 0;
    initTabContent(index);
    return;
}

// save current channel standard
void RtSa_Dialog_Ch_Std::on_currentCellChanged(qint32 currentRow, qint32 currentColumn, qint32 previousRow, qint32 previousColumn)
{
//    QString CHstandard;
    curCHIndex = currentRow;
    if(curCHIndex < 0)
        curCHIndex = 0;
    globalUserVariable->gMeterParam.gConfig_FreqSpan.channelSelID =  tabPageIndex*9 + curCHIndex;
//    mControl->setCHStandard(globalUserVariable->gMeterParam.gConfig_FreqSpan.channelStd);
//    CHstandard = ui->tableWidget->item(currentRow,0)->text();
//    mControl->setCHstandard();
    return;
}

void RtSa_Dialog_Ch_Std::on_pb_ok_clicked()
{
    curCHIndex = ui->tableWidget->currentRow();
    globalUserVariable->gMeterParam.gConfig_FreqSpan.channelSelID =  tabPageIndex*9 + curCHIndex;
    RemoteInterfaceObj->setCHStandard(ChType);
    this->close();
    return;
}

void RtSa_Dialog_Ch_Std::on_pb_close_clicked()
{
    this->close();
    return;
}
