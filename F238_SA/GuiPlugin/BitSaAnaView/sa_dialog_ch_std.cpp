#include "sa_dialog_ch_std.h"
#include "ui_sa_dialog_ch_std.h"
#include "define.h"


SA_Dialog_CH_Std::SA_Dialog_CH_Std(controlInterface *interface, user_variable *puser_variable, QWidget *parent) :
    QWidget(parent),
    mControl(interface),
    globalUserVariable(puser_variable),
    ui(new Ui::SA_Dialog_CH_Std)
{
    ui->setupUi(this);
    setProperty("status",qssMode[mControl->GetDisplayMode()]);
    setAttribute(Qt::WA_DeleteOnClose);
    initMap();
    initWidget();
    initDisplay();
    ui->pb_WIMAX->setVisible(false);
}

SA_Dialog_CH_Std::~SA_Dialog_CH_Std()
{
    delete ui;
}


/**
 * @brief  Initialize map of indexes and controls.
 * @param  void
 * @author Tony
 * @since 2019-02-12
*/
void SA_Dialog_CH_Std::initMap()
{
    mTypeGroup = new QButtonGroup();
    mTypeGroup->addButton(ui->pb_CDMA,SA_CDMA);
    mTypeGroup->addButton(ui->pb_GSM,SA_GSM);
    mTypeGroup->addButton(ui->pb_LTEFDD,SA_LTE_FDD);
    mTypeGroup->addButton(ui->pb_LTETDD,SA_LTE_TDD);
    mTypeGroup->addButton(ui->pb_TD,SA_TD_SCDMD);
    mTypeGroup->addButton(ui->pb_WCDMA,SA_WCDMA);
    mTypeGroup->addButton(ui->pb_WIMAX,SA_WIMAX);

    connect(mTypeGroup,SIGNAL(buttonClicked(qint32)),this,SLOT(runBtnTypeFunction(qint32)));
    return ;
}
/**
 * @brief  Init the display of frequency setup dialog.
 * @param  void
 * @author Tony
 * @since 2019-02-12
*/
void SA_Dialog_CH_Std::initDisplay()
{
    qint32 size = globalUserVariable->gCHName->size();
    curCHIndex = globalUserVariable->gCHIndex%9;
    tabPageIndex = globalUserVariable->gCHIndex/9;
    if(globalUserVariable->gTecIndex>=0)
    {
        mTypeGroup->button(globalUserVariable->gTecIndex)->setChecked(true);
    }else
    {
        mTypeGroup->button(0)->setChecked(true);
    }
    ChType = globalUserVariable->gTecIndex;
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
void SA_Dialog_CH_Std::initWidget()
{
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode( QAbstractItemView::SingleSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnWidth(0,259);
    ui->tableWidget->setColumnWidth(1,259);
    ui->tableWidget->setColumnWidth(2,237);

//    connect(ui->tableWidget,SIGNAL(currentCellChanged(qint32,qint32,qint32,qint32)),this,SLOT(on_currentCellChanged(qint32,qint32,qint32,qint32)));
//    refreshEdit();
}

void SA_Dialog_CH_Std::initTabContent(qint32 index)
{
    getBandInfo(index);
    initTabPage();
    return;
}

void SA_Dialog_CH_Std::getBandInfo(qint32 STDIndex)
{
    QString name = QString(mChStand[STDIndex].name);
    QString filename = QString(":/sa/standard/%1").arg(name);
    QString str;
    QByteArray line;
    CHName.clear();
    ChannelRange.clear();
    FreqRange.clear();
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
    //mFile.close();
    return;
}

void SA_Dialog_CH_Std::analysisData(QString str)
{
    __Standard__ mtmp;
    QStringList list = str.split(",");
    if(list.size() == 5)
    {
        CHName.append(list[0]);
        mtmp.Up.Min = QString(list[1]).toDouble();
        mtmp.Up.Max = QString(list[2]).toDouble();
        mtmp.Down.Min = QString(list[1]).toDouble();
        mtmp.Down.Max = QString(list[2]).toDouble();
        ChannelRange.append(mtmp);

        mtmp.Up.Min = QString(list[3]).toDouble();
        mtmp.Up.Max = QString(list[4]).toDouble();
        mtmp.Down.Min = QString(list[3]).toDouble();
        mtmp.Down.Max = QString(list[4]).toDouble();
        FreqRange.append(mtmp);
    }else if(list.size() == 9)
    {
        CHName.append(list[0]);
        mtmp.Up.Min = QString(list[1]).toDouble();
        mtmp.Up.Max = QString(list[2]).toDouble();
        mtmp.Down.Min = QString(list[3]).toDouble();
        mtmp.Down.Max = QString(list[4]).toDouble();
        ChannelRange.append(mtmp);

        mtmp.Up.Min = QString(list[5]).toDouble();
        mtmp.Up.Max = QString(list[6]).toDouble();
        mtmp.Down.Min = QString(list[7]).toDouble();
        mtmp.Down.Max = QString(list[8]).toDouble();
        FreqRange.append(mtmp);
    }

    return;
}

void SA_Dialog_CH_Std::initTabPage()
{
    QString strname,strChannel,strFreq;
    qint32 index= CHName.size();
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
    ui->tableWidget->blockSignals(true);
    ui->tableWidget->clearContents();
    ui->tableWidget->blockSignals(false);
    ui->tableWidget->setRowCount(curPageBand);
    ui->tableWidget->selectRow(curIndex);

    for(qint32 i =0;i < 9 && (tabPageIndex *9 +i) <index;i++)
    {
       tmpBandIndex = tabPageIndex *9 +i;
       strname = CHName.at(tmpBandIndex);
       if(ChType == SA_LTE_TDD || ChType == SA_TD_SCDMD)
       {
           strChannel = QString("(%1 - %2)").arg(QString::number(ChannelRange.at(tmpBandIndex).Up.Min)).\
                   arg(QString::number(ChannelRange.at(tmpBandIndex).Up.Max));
           strFreq = QString("(%1 - %2)").arg(QString::number(FreqRange.at(tmpBandIndex).Up.Min)).\
                   arg(QString::number(FreqRange.at(tmpBandIndex).Up.Max));
       }else if(ChType == SA_GSM || ChType == SA_CDMA)
       {
           strChannel = QString("(%1 - %2)\n(%3 - %4)").arg(QString::number(ChannelRange.at(tmpBandIndex).Up.Min)).\
                   arg(QString::number(ChannelRange.at(tmpBandIndex).Up.Max)).arg(QString::number(ChannelRange.at(tmpBandIndex).Up.Min)).\
                   arg(QString::number(ChannelRange.at(tmpBandIndex).Up.Max));
           strFreq = QString("(%1 - %2)\n(%3 - %4)").arg(QString::number(FreqRange.at(tmpBandIndex).Up.Min)).\
                   arg(QString::number(FreqRange.at(tmpBandIndex).Up.Max)).arg(QString::number(FreqRange.at(tmpBandIndex).Down.Min)).\
                   arg(QString::number(FreqRange.at(tmpBandIndex).Down.Max));
       }
       else
       {
           strChannel = QString("(%1 - %2)\n(%3 - %4)").arg(QString::number(ChannelRange.at(tmpBandIndex).Up.Min)).\
                   arg(QString::number(ChannelRange.at(tmpBandIndex).Up.Max)).arg(QString::number(ChannelRange.at(tmpBandIndex).Down.Min)).\
                   arg(QString::number(ChannelRange.at(tmpBandIndex).Down.Max));
           strFreq = QString("(%1 - %2)\n(%3 - %4)").arg(QString::number(FreqRange.at(tmpBandIndex).Up.Min)).\
                   arg(QString::number(FreqRange.at(tmpBandIndex).Up.Max)).arg(QString::number(FreqRange.at(tmpBandIndex).Down.Min)).\
                   arg(QString::number(FreqRange.at(tmpBandIndex).Down.Max));
       }
       ui->tableWidget->setItem(i, 0, new QTableWidgetItem(strname));
       ui->tableWidget->setItem(i, 1, new QTableWidgetItem(strChannel));
       ui->tableWidget->setItem(i, 2, new QTableWidgetItem(strFreq));
    }
    return;
}

void SA_Dialog_CH_Std::on_pb_up_clicked()
{
    qint32 totalPage,totalBand;
    totalBand = CHName.size();
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

void SA_Dialog_CH_Std::on_pb_down_clicked()
{
    qint32 totalPage,totalBand;
    totalBand = CHName.size();
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

void SA_Dialog_CH_Std::runBtnTypeFunction(qint32 index)
{
    ChType = index;
    curCHIndex = 0;
    tabPageIndex = 0;
    initTabContent(index);
    return;
}

// save current channel standard
void SA_Dialog_CH_Std::on_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
//    QString CHstandard;
    curCHIndex = currentRow;
    globalUserVariable->gCHIndex =  tabPageIndex*9 + curCHIndex;
    mControl->setCHStandard(globalUserVariable->gTecIndex);
    return;
}

void SA_Dialog_CH_Std::on_pb_close_clicked()
{
    this->close();
    return;
}

void SA_Dialog_CH_Std::on_pb_cancel_clicked()
{
    this->close();
    return;
}

void SA_Dialog_CH_Std::on_pb_ok_clicked()
{
    //    QString CHstandard;
    curCHIndex = ui->tableWidget->currentRow();
    globalUserVariable->gCHIndex =  tabPageIndex*9 + curCHIndex;
    mControl->setCHStandard(ChType);
    this->close();
    return;
}
void SA_Dialog_CH_Std::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_PowerOff)
    {
        if(!event->isAutoRepeat())
            QApplication::sendEvent(this->parent(),event);
        return;
    }else if(event->key() == Qt::Key_Escape)
    {
        this->close();
        return;
    }else if(event->key() ==  Qt::Key_Shift)
    {
        QApplication::sendEvent(qobject_cast<QWidget*>(parent()),event);
        return;
    }
}
