#include "rtsa_dialog_fmttable.h"
#include "ui_rtsa_dialog_fmttable.h"
#include <QScrollBar>

RtSa_Dialog_FmtTable::RtSa_Dialog_FmtTable(RtSa_Interface *interface, RtSa_Dialog_Digitinput *input, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RtSa_Dialog_FmtTable),
    mControl(interface),
    mInput(input)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->verticalHeader()->setVisible(true);
    ui->tableWidget->verticalHeader()->setMinimumWidth(12);
//    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::AnyKeyPressed);
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->tableWidget->verticalScrollBar()->setStyleSheet("");
    ui->tableWidget->setFocusPolicy(Qt::StrongFocus);
    connect(mInput,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
//    connect(mInput,SIGNAL(ClockWiseDown(QKeyEvent*)),this,SLOT(DigitalKeyRespond(QKeyEvent*)));
    connect(ui->tableWidget,SIGNAL(contenJudge(qint32)),this,SLOT(resetTableSort(qint32)));
//    connect(ui->tableWidget,SIGNAL(editFinish()),this,SLOT(resetTableSort(qint32)));
    connect(ui->tableWidget,SIGNAL(KeySignal(QKeyEvent*)),this,SLOT(respondKeyEvent(QKeyEvent*)));
    initTable();
    if(ui->tableWidget->rowCount() > 0)
       {
            ui->tableWidget->setFocus();
            mColumnIndex = RTSA_INPUT_FMT_FREQ;
       }
    else
        {
            ui->LED_CurPtIndex->setFocus();
            mColumnIndex = RTSA_INPUT_FMT_SELECT_INDEX;
        }
    setProperty("status",rtsa_qssMode[mControl->GetDisplayMode()]);
}

RtSa_Dialog_FmtTable::~RtSa_Dialog_FmtTable()
{
    delete ui;
}
void RtSa_Dialog_FmtTable::on_pb_InsertRow_clicked()
{
    qint32 row = ui->tableWidget->rowCount();
    QString strValue;
    qreal currFrqValue;
    qreal startfreq = mControl->getStartFreq()/1000000 /*+ 0.05*/;
    startfreq = round(startfreq * 10)/10;

    if(row < RTSA_NUM_SWEEP_POINT)
    {
        if(row > 0)
        {
            strValue = ui->tableWidget->item(0,0)->text();
            currFrqValue = strValue.toDouble();
            currFrqValue = round(currFrqValue * 100)/100;
            if(currFrqValue <= 0.0001 && currFrqValue >= -0.0001)
            {
                ui->tableWidget->setCurrentCell(0,0);
                this->setFocus();
                return;
            }
        }
        if((currFrqValue - startfreq) <= 0.02 && (currFrqValue - startfreq) >= -0.02)
        {
            ui->tableWidget->insertRow(0);
            strValue  = QString::number(0,'f',2);
    //        ui->tableWidget->setItem(0,0,new QTableWidgetItem(QString("%1").arg(0)));
            ui->tableWidget->setItem(0,0,new QTableWidgetItem(strValue));
            ui->tableWidget->setItem(0,1,new QTableWidgetItem(QString("-10.00")));
            row = ui->tableWidget->rowCount();
            ui->tableWidget->sortByColumn(0,Qt::AscendingOrder);
            ui->tableWidget->resortAllData();
            ui->tableWidget->resetAllData();
//            ui->tableWidget->sortAllItems();
//            row -= 1;
//            initTable();
        }
        else
        {
            ui->tableWidget->insertRow(0);
    //        ui->tableWidget->setItem(0,0,new QTableWidgetItem(QString("%1").arg(0)));
            strValue  = QString::number(mControl->getStartFreq()/1000000,'f',2);
            ui->tableWidget->setItem(0,0,new QTableWidgetItem(strValue));
            ui->tableWidget->setItem(0,1,new QTableWidgetItem(QString("-10.00")));
        //    ui->tableWidget->sortAllItems();
            ui->tableWidget->resetAllParam();
            ui->tableWidget->judgeTableContent(ui->tableWidget,mControl->getStartFreq(),mControl->getStopFreq());
            row = ui->tableWidget->rowCount();
            ui->tableWidget->sortByColumn(0,Qt::AscendingOrder);
            ui->tableWidget->resortAllData();
            ui->tableWidget->resetAllData();
//            ui->tableWidget->sortAllItems();

        }
//        ui->tableWidget->insertRow(0);
//        ui->tableWidget->setItem(0,0,new QTableWidgetItem(QString("%1").arg(mControl->getStartFreq()/1000000)));
//        ui->tableWidget->setItem(0,1,new QTableWidgetItem(QString("-10.00")));
//        ui->tableWidget->setFocus(Qt::NoFocusReason);
    }
//    row += 1;
//    mControl->InsertLimitRow();
//    row += 1;
    mControl->setFmtDataNum(row);
//    ui->tableWidget->resetAllData();
//    ui->tableWidget->resortAllData();
    mControl->setFmtFreqData(ui->tableWidget->getLimitFreq(),row);
    mControl->setFmtAmptData(ui->tableWidget->getLimitAmpt(),row);
//    initTable();
    ui->tableWidget->setCurrentCell(0,0);
    mControl->setCurFmtDataIndex(0);
    refreshCurRowIndex();
//    mControl->setInsertRowBelow(ui->tableWidget);
    return;
}

void RtSa_Dialog_FmtTable::on_pb_DeleteRow_clicked()
{
    qint32 a = ui->tableWidget->rowCount();
    if(ui->tableWidget->rowCount() == 0)
    {
        return;
    }
    qint32 index = ui->tableWidget->currentRow();
    if(index < 0)
    {
        index = 0;
    }
    qint32 tatolnum = mControl->getFmtDataNum();
    qreal freq = ui->tableWidget->item(0,0)->text().toDouble();
    if((freq) <= 0.02 && (freq) >= -0.02)
    {
        ui->tableWidget->removeRow(index);
        mControl->setFmtDataNum(tatolnum - 1);
        return;
    }
    ui->tableWidget->removeRow(index);
    mControl->setFmtDataNum(tatolnum - 1);
//    ui->tableWidget->sortByColumn(0,Qt::AscendingOrder);
    ui->tableWidget->resetAllData();
//    ui->tableWidget->resortAllData();
    mControl->setFmtFreqData(ui->tableWidget->getLimitFreq() ,tatolnum -1);
    mControl->setFmtAmptData(ui->tableWidget->getLimitAmpt(),tatolnum -1);

    ui->tableWidget->setCurrentCell(0,0);
    mControl->setCurFmtDataIndex(0);
    refreshCurRowIndex();
    return;
}

void RtSa_Dialog_FmtTable::on_pb_DeleteLimit_clicked()
{
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->clearContents();
    mControl->DeleteAllFmtMask();
//    ui->tableWidget->getTableWidgetValue();
    refreshCurRowIndex();
    return;
}

void RtSa_Dialog_FmtTable::on_pb_cancel_clicked()
{
    this->close();
    return;
}

void RtSa_Dialog_FmtTable::on_tableWidget_cellClicked(int row, int column)
{
    QTableWidgetItem *item=ui->tableWidget->item(row,column);
    ui->tableWidget->editItem(item);
    mControl->setCurFmtDataIndex(row);
    mColumnIndex = RTSA_INPUT_FMT_FREQ + column;
    showInputDialog(mColumnIndex);
    refreshCurRowIndex();
    return ;
}
void RtSa_Dialog_FmtTable::showInputDialog(qint32 index)
{
//    mSelectInputID = index;
    if(mInput->isHidden())
    {
        mInput->setGeometry(mapToGlobal(QPoint(0,0)).x()/*+this->width()*//*-RTSA_DIGITAL_DIALOG_WIDTH*/,\
                                  mapToGlobal(QPoint(0,0)).y(),RTSA_DIGITAL_DIALOG_WIDTH,RTSA_DIGITAL_DIALOG_HEIGHT);
    }
    mInput->initDisplay(index);
    mInput->setProperty("status", rtsa_qssMode[mControl->GetDisplayMode()]);
    mInput->setStyle(QApplication::style());
    if(mInput->isHidden())
        mInput->show();
    return ;
}

void RtSa_Dialog_FmtTable::on_finishEntry(qint32 index)
{
    refreshEditDisplay(index);
    ui->tableWidget->setFocus();
    return ;
}

void RtSa_Dialog_FmtTable::keyPressEvent(QKeyEvent *event)
{
    qint32 keyvalue = event->key();
    qint32 row,colum;
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
//        emit finishEntry(RTSA_NOT_USE);
//        if(!mInput->isHidden())
//        {
//            QApplication::sendEvent(mInput,event);
//            return;
//        }
        this->close();
//        QCoreApplication::sendEvent(this->parentWidget(), event);
        return;
    case Qt::Key_Shift:
        this->close();
        QCoreApplication::sendEvent(this->parentWidget(), event);
        return;
    default:
        break;
    }
//===========================================================
    switch(keyvalue){
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
    case Qt::Key_F2:
    case Qt::Key_Minus:
    case Qt::Key_Period:
//        QCoreApplication::sendEvent(this->parentWidget(), event);
//        break;
//        QCoreApplication::sendEvent(ui->tableWidget, event);
        if(mControl->isShiftKeyEnable())
        {
            this->close();
        }else
        {
            if(mInput->isHidden())
            {
                showInputDialog(mColumnIndex);
            }
            mInput->keyresponse(keyvalue);
        }
        break;
    case Qt::Key_F4:
////        if(mInput)
////            mInput->close();
////        getKnobValue(CLOCKWISE);
        break;
    case Qt::Key_F3:
////        if(mInput)
////            mInput->close();
////        getKnobValue(ANTICLOCKWISE);
        break;
    case Qt::Key_Up:
//        tabelChange(-2);
        break;
    case Qt::Key_Down:
//        tabelChange(2);
        break;
    case Qt::Key_Left:
//        tabelChange(-1);
        break;
    case Qt::Key_Right:
//        tabelChange(1);
        break;
    }
}
void RtSa_Dialog_FmtTable::respondKeyEvent(QKeyEvent *event)
{
    qint32 keyvalue = event->key();

    switch(keyvalue){
    case Qt::Key_Escape:
//        emit finishEntry(RTSA_NOT_USE);
        this->close();
        QCoreApplication::sendEvent(this->parentWidget(), event);
        return;
    case Qt::Key_Shift:
        this->close();
        QCoreApplication::sendEvent(this->parentWidget(), event);
        return;
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
    case Qt::Key_F2:
    case Qt::Key_Minus:
    case Qt::Key_Period:
//        QCoreApplication::sendEvent(this->parentWidget(), event);
//        break;
//        QCoreApplication::sendEvent(ui->tableWidget, event);
        if(mControl->isShiftKeyEnable())
        {
            this->close();
        }else
        {
            if(mInput->isHidden())
            {
                showInputDialog(mColumnIndex);
            }
            mInput->keyresponse(keyvalue);
        }
        break;
    case Qt::Key_F4:
////        if(mInput)
////            mInput->close();
////        getKnobValue(CLOCKWISE);
        break;
    case Qt::Key_F3:
////        if(mInput)
////            mInput->close();
////        getKnobValue(ANTICLOCKWISE);
        break;
    case Qt::Key_Up:
//        tabelChange(-2);
        break;
    case Qt::Key_Down:
//        tabelChange(2);
        break;
    case Qt::Key_Left:
//        tabelChange(-1);
        break;
    case Qt::Key_Right:
//        tabelChange(1);
        break;
    }
    return;
}
//void RtSa_Dialog_FmtTable::tabelChange(qint32 step)
//{
//    qint32 row,colum,index,maxIndex;
//    row = ui->tableWidget->currentRow();
//    colum = ui->tableWidget->currentColumn();
//    maxIndex = ui->tableWidget->rowCount() * ui->tableWidget->columnCount() - 1;
//    if(row < 0 || colum < 0)
//    {
//        index = 0;
//    }else
//    {
//        index = row * 2 + colum;
//    }
//    index += step;
//    index = index >= 0 ? index : 0;
//    index = index <= maxIndex ? index : maxIndex;
//    row = index / 2;
//    colum = index % 2;
//    ui->tableWidget->blockSignals(true);
//    ui->tableWidget->setCurrentCell(row,colum);
//    QTableWidgetItem *item=ui->tableWidget->item(row,colum);
//    ui->tableWidget->editItem(item);
//    ui->tableWidget->blockSignals(false);
////    ui->tableWidget->setFocus(Qt::NoFocusReason);
//    return;
//}
/*****************************
 *
 *
 * ***************************/
void RtSa_Dialog_FmtTable::initTable()
{
    qint32 index,size;
    qint32 rowNum;
    QString strFreq,strAmplitude;

    rowNum = ui->tableWidget->rowCount();
    for(int i = rowNum-1;i>=0;i--)
    {
        ui->tableWidget->removeRow(i);
    }
    size = mControl->getFmtDataNum();
    qreal* freq = mControl->getFMTFreqData();
    qreal* ampt = mControl->getFMTAmplitudeData();
    for(qint32 i = 0; i < size;i++)
    {
        strFreq = QString::number(freq[i],'f',2);
        QTableWidgetItem *freqItem = new QTableWidgetItem(strFreq);

        strAmplitude = QString::number(ampt[i],'f',2);
        QTableWidgetItem *amplitudeItem = new QTableWidgetItem(strAmplitude);

        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,freqItem);
        ui->tableWidget->setItem(i,1,amplitudeItem);
    }

    refreshCurRowIndex();
    return;
}

void RtSa_Dialog_FmtTable::resetTableSort(qint32 rowIndex)
{
    ui->tableWidget->judgeTableContent(ui->tableWidget,mControl->getStartFreq(),mControl->getStopFreq());
    ui->tableWidget->resetAllParam();
//    mControl->setCurFmtDataIndex(rowIndex);
    qint32 a = ui->tableWidget->currentColumn();
    qint32 b = ui->tableWidget->currentRow();
    mColumnIndex = RTSA_INPUT_FMT_FREQ + ui->tableWidget->currentColumn();
    refreshCurRowIndex();
//    this->setFocus();
    return;
}
void RtSa_Dialog_FmtTable::refreshEditDisplay(quint32 index)
{
//    ui->tableWidget->judgeFmtTableContent(ui->tableWidget,mControl->getStartFreq(),mControl->getStopFreq());
    QString strGab,strTmp;
    qreal   value;
    qint32 cnt = 0;
    cnt  = mControl->getCurFmtDataIndex();
    switch (index)
    {
    case RTSA_INPUT_FMT_FREQ:
        initTable();
        value = mControl->getCurFmtFreqData(cnt);
        strGab = QString::number((qreal) value,'f',2);
        ui->tableWidget->setItem(cnt,0,new QTableWidgetItem(strGab));
        refreshFmtData();

        ui->tableWidget->setCurrentCell(mControl->getCurFmtDataIndex(),0);
        break;
    case RTSA_INPUT_FMT_AMPT:
        initTable();
        value = mControl->getCurFmtAmptData(mControl->getCurFmtDataIndex());
//        value = mControl->getRefLevel();
        strGab = QString::number((qreal) value,'f',2);
//        strGab = mControl->getRefLevelAdjustStr();
        cnt  = ui->tableWidget->currentRow();
        ui->tableWidget->setItem(cnt,1,new QTableWidgetItem(strGab));
        refreshFmtData();

        ui->tableWidget->setCurrentCell(cnt,1);
        break;
    case RTSA_INPUT_FMT_SELECT_INDEX:
        ui->tableWidget->setCurrentCell(cnt,0);
        refreshCurRowIndex();
        break;
    default:
        break;
    }
    return ;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-13
*/
void RtSa_Dialog_FmtTable::on_LED_CurPtIndex_clicked()
{
    showInputDialog(RTSA_INPUT_FMT_SELECT_INDEX);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-13
*/
void RtSa_Dialog_FmtTable::refreshCurRowIndex()
{
    qint32 index = mControl->getCurFmtDataIndex() + 1;
    QString str = QString::number(index,'f',0);
    ui->LED_CurPtIndex->setText(str);
    ui->tableWidget->setFocus();

    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-13
*/
void RtSa_Dialog_FmtTable::refreshFmtData()
{
    ui->tableWidget->judgeFmtTableContent(ui->tableWidget,mControl->getStartFreq(),mControl->getStopFreq());
    ui->tableWidget->resortAllData();
    qint32 row = ui->tableWidget->rowCount();
    mControl->setFmtDataNum(row);
    mLimitFreq = ui->tableWidget->getLimitFreq();
    mLimitAmpt = ui->tableWidget->getLimitAmpt();
    mControl->setFmtFreqData(mLimitFreq,row);
    mControl->setFmtAmptData(mLimitAmpt,row);
    return;
}
