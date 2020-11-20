#include "rtsa_dialog_limittable.h"
#include "ui_rtsa_dialog_limittable.h"
#include <QScrollBar>

RtSa_Dialog_LimitTable::RtSa_Dialog_LimitTable(Rtsa_Remote_Interface *RtsaRemoteInterface , RtSa_Dialog_Digitinput *mInput, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RtSa_Dialog_LimitTable),
    RemoteInterfaceObj(RtsaRemoteInterface),
    mInputDialog(mInput),
    mColumnIndex(RTSA_INPUT_LIMIT_FREQ),
    mShowType(RTSA_TYPE_LIMIT)
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
    connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
//    connect(mInputDialog,SIGNAL(ClockWiseDown(QKeyEvent*)),this,SLOT(DigitalKeyRespond(QKeyEvent*)));
    connect(ui->tableWidget,SIGNAL(contenJudge(qint32)),this,SLOT(resetTableSort(qint32)));
    connect(ui->tableWidget,SIGNAL(editFinish()),this,SLOT(resetTableSort(qint32)));
    connect(ui->tableWidget,SIGNAL(KeySignal(QKeyEvent*)),this,SLOT(respondKeyEvent(QKeyEvent*)));
    initTable();
    if(ui->tableWidget->rowCount() > 0)
       {
            ui->tableWidget->setFocus();
            mColumnIndex = RTSA_INPUT_LIMIT_FREQ;
       }
    else
        {
            ui->LED_CurPtIndex->setFocus();
            mColumnIndex = RTSA_INPUT_LIMIT_SELECT_INDEX;
        }
    setProperty("status",rtsa_qssMode[RemoteInterfaceObj->GetDisplayMode()]);
}

RtSa_Dialog_LimitTable::~RtSa_Dialog_LimitTable()
{
    delete ui;
}

void RtSa_Dialog_LimitTable::on_pb_InsertRow_clicked()
{
//    qint32 limitID = RemoteInterfaceObj->getCurLimit();
    QString strValue;
    qreal currFrqValue;
    qreal startfreq = RemoteInterfaceObj->getStartFreq()/1000000 /*+ 0.05*/;
    startfreq = round(startfreq * 10)/10;
//    qreal *freq = mControl->getLimitFreqData(limitID);
//    qreal *ampt = mControl->getLimitAmptData(limitID);


    qint32 row = ui->tableWidget->rowCount();
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
    //        ui->tableWidget->setItem(0,0,new QTableWidgetItem(QString("%1").arg(0)));
            ui->tableWidget->setItem(0,0,new QTableWidgetItem(QString("%1").arg(0.00)));
            ui->tableWidget->setItem(0,1,new QTableWidgetItem(QString("-10.00")));
            RemoteInterfaceObj->InsertLimitRow();
            initTable();
        }
        else
        {
            ui->tableWidget->insertRow(0);
    //        ui->tableWidget->setItem(0,0,new QTableWidgetItem(QString("%1").arg(0)));
            ui->tableWidget->setItem(0,0,new QTableWidgetItem(QString("%1").arg(RemoteInterfaceObj->getStartFreq()/1000000)));
            ui->tableWidget->setItem(0,1,new QTableWidgetItem(QString("-10.00")));
            RemoteInterfaceObj->InsertLimitRow();
        //    ui->tableWidget->sortAllItems();
            ui->tableWidget->resetAllParam();
        //        ui->tableWidget->getTableWidgetValue();
            ui->tableWidget->judgeTableContent(ui->tableWidget,RemoteInterfaceObj->getStartFreq(),RemoteInterfaceObj->getStopFreq());
            initTable();

        }
//        ui->tableWidget->sortAllItems();
//        ui->tableWidget->setFocus(Qt::NoFocusReason);
    }
    ui->tableWidget->setCurrentCell(0,0);
    this->setFocus();
//    mControl->setInsertRowBelow(ui->tableWidget);
    return;
}

void RtSa_Dialog_LimitTable::on_pb_DeleteRow_clicked()
{
    qint32 index = ui->tableWidget->currentRow();
    RemoteInterfaceObj->DeleteLimitRow(index);
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
    ui->tableWidget->setCurrentCell(0,0);
    refreshCurRowIndex();
    this->setFocus();
//    ui->tableWidget->getTableWidgetValue();
    return;
}

void RtSa_Dialog_LimitTable::on_pb_DeleteLimit_clicked()
{
    RemoteInterfaceObj->DeleteLimit(-1);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->clearContents();
    this->setFocus();
//    ui->tableWidget->getTableWidgetValue();
    return;
}

void RtSa_Dialog_LimitTable::on_pb_cancel_clicked()
{
    this->close();
    return;
}

void RtSa_Dialog_LimitTable::on_tableWidget_cellClicked(int row, int column)
{
//    qint32 limit = RemoteInterfaceObj->getCurLimit();
    QTableWidgetItem *item=ui->tableWidget->item(row,column);
    ui->tableWidget->editItem(item);
    RemoteInterfaceObj->SetCurLimitDataIndex(row);
    mColumnIndex = RTSA_INPUT_LIMIT_FREQ + column;
    showInputDialog(mColumnIndex);
//    if(column == 0) //input frequency
//    {
//        showInputDialog(mColumnIndex);
//    }
//    else if(column == 1) //inpuy amplitude
//    {
//        showInputDialog(mColumnIndex);
//    }
    refreshCurRowIndex();
    this->setFocus();
    return ;
}
void RtSa_Dialog_LimitTable::showInputDialog(qint32 index)
{
//    mSelectInputID = index;
    if(mInputDialog->isHidden())
    {
        mInputDialog->setGeometry(mapToGlobal(QPoint(0,0)).x()/*+this->width()*//*-RTSA_DIGITAL_DIALOG_WIDTH*/,\
                                  mapToGlobal(QPoint(0,0)).y(),RTSA_DIGITAL_DIALOG_WIDTH,RTSA_DIGITAL_DIALOG_HEIGHT);
    }
    mInputDialog->initDisplay(index);
    mInputDialog->setProperty("status", rtsa_qssMode[RemoteInterfaceObj->GetDisplayMode()]);
    mInputDialog->setStyle(QApplication::style());
    if(mInputDialog->isHidden())
        mInputDialog->show();
    return ;
}

void RtSa_Dialog_LimitTable::on_finishEntry(qint32 index)
{
    refreshEditDisplay(index);
//    disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
//    disconnect(mInputDialog,SIGNAL(knobevent(QKeyEvent*)),this,SLOT(keyPressEvent(QKeyEvent*)));
//    mInputDialog = NULL;
//    if(index == LIMIT_EDGE)
//    {
////        ui->lineEdit->setFocus();
//        initTable();
//    }
    ui->tableWidget->setFocus();
    return ;
}
//void RtSa_Dialog_LimitTable::digitInputClose()
//{
//    if(mInputDialog)
//    {
//        disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
//        disconnect(mInputDialog,SIGNAL(knobevent(QKeyEvent*)),this,SLOT(keyPressEvent(QKeyEvent*)));
//        delete mInputDialog;
//        mInputDialog = NULL;
//    }
////    ui->lineEdit->setFocus();
////    initDisplay();

//    return;
//}
void RtSa_Dialog_LimitTable::keyPressEvent(QKeyEvent *event)
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
///    qint32 row,colum;
    switch (keyvalue) {
    case Qt::Key_Escape:
        if(!mInputDialog->isHidden())
        {
            QCoreApplication::sendEvent(mInputDialog, event);
            return;
        }
//        emit finishEntry(RTSA_NOT_USE);
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
//    row = ui->tableWidget->currentRow();
//    colum = ui->tableWidget->currentColumn();
//    if(row >= 0 && colum >= 0)
//        on_tableWidget_cellClicked(row,colum);


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
        if(RemoteInterfaceObj->isShiftKeyEnable())
        {
            this->close();
        }else
        {
            if(mInputDialog->isHidden())
            {
                showInputDialog(mColumnIndex);
            }
            mInputDialog->keyresponse(keyvalue);
        }
        break;
    case Qt::Key_F4:
////        if(mInputDialog)
////            mInputDialog->close();
////        getKnobValue(CLOCKWISE);
        break;
    case Qt::Key_F3:
////        if(mInputDialog)
////            mInputDialog->close();
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
void RtSa_Dialog_LimitTable::respondKeyEvent(QKeyEvent *event)
{
    qint32 keyvalue = event->key();

    switch(keyvalue){
    case Qt::Key_Escape:
        if(!mInputDialog->isHidden())
        {
            QCoreApplication::sendEvent(mInputDialog, event);
            return;
        }
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
        if(RemoteInterfaceObj->isShiftKeyEnable())
        {
            this->close();
        }else
        {
            if(mInputDialog->isHidden())
            {
                showInputDialog(mColumnIndex);
            }
            mInputDialog->keyresponse(keyvalue);
        }
        break;
    case Qt::Key_F4:
////        if(mInputDialog)
////            mInputDialog->close();
////        getKnobValue(CLOCKWISE);
        break;
    case Qt::Key_F3:
////        if(mInputDialog)
////            mInputDialog->close();
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
void RtSa_Dialog_LimitTable::tabelChange(qint32 step)
{
    qint32 row,colum,index,maxIndex;
    row = ui->tableWidget->currentRow();
    colum = ui->tableWidget->currentColumn();
    maxIndex = ui->tableWidget->rowCount() * ui->tableWidget->columnCount() - 1;
    if(row < 0 || colum < 0)
    {
        index = 0;
    }else
    {
        index = row * 2 + colum;
    }
    index += step;
    index = index >= 0 ? index : 0;
    index = index <= maxIndex ? index : maxIndex;
    row = index / 2;
    colum = index % 2;
    ui->tableWidget->blockSignals(true);
    ui->tableWidget->setCurrentCell(row,colum);
    QTableWidgetItem *item=ui->tableWidget->item(row,colum);
    ui->tableWidget->editItem(item);
    ui->tableWidget->blockSignals(false);
//    ui->tableWidget->setFocus(Qt::NoFocusReason);
    return;
}
/*****************************
 *
 *
 * ***************************/
void RtSa_Dialog_LimitTable::initTable()
{
    qint32 index,size;
    qint32 rowNum;
    QString strFreq,strAmplitude;

    rowNum = ui->tableWidget->rowCount();
    for(int i = rowNum-1;i>=0;i--)
    {
        ui->tableWidget->removeRow(i);
    }
    index = RemoteInterfaceObj->getCurLimit();
    size = RemoteInterfaceObj->getLimitDataNum(index);
    qreal* freq = RemoteInterfaceObj->getLimitFreqData(index);
    qreal* ampt = RemoteInterfaceObj->getLimitAmptData(index);
//    size = mControl->globalUserLimit->gTotalDot[index];
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
//    ui->tableWidget->sortAllItems();
//    ui->tableWidget->setCurrentCell(mControl->getLimitCurPointIndex(),0);
    return;
}

//void RtSa_Dialog_LimitTable::on_pb_close_clicked()
//{
//    this->close();
//    return;
//}

//void RtSa_Dialog_LimitTable::on_pb_ok_clicked()
//{
//    ui->tableWidget->sortAllItems();
//    qint32 row = ui->tableWidget->rowCount();
//    qint32 LimitID = mControl->getCurLimit();
//    mLimitFreq = ui->tableWidget->getLimitFreq();
//    mLimitAmpt = ui->tableWidget->getLimitAmpt();
//    mControl->setLimitFreqData(mLimitFreq,row,LimitID);
//    mControl->setLimitAmptData(mLimitAmpt,row,LimitID);
////    this->close();
//    return;
//}

void RtSa_Dialog_LimitTable::resetTableSort(qint32 rowIndex)
{
    ui->tableWidget->judgeTableContent(ui->tableWidget,RemoteInterfaceObj->getStartFreq(),RemoteInterfaceObj->getStopFreq());
    ui->tableWidget->resetAllParam();
    RemoteInterfaceObj->SetCurLimitDataIndex(rowIndex);
//    /qint32 a = ui->tableWidget->currentColumn();
//    qint32 b = ui->tableWidget->currentRow();
    mColumnIndex = RTSA_INPUT_LIMIT_FREQ + ui->tableWidget->currentColumn();
    refreshCurRowIndex();
//    this->setFocus();
    return;
}
void RtSa_Dialog_LimitTable::refreshEditDisplay(quint32 index)
{
    QString strGab,strTmp;
    qreal   value;
    switch (index)
    {
    case RTSA_INPUT_LIMIT_FREQ:
        initTable();
        value = RemoteInterfaceObj->getLimitCurPointFreq(RemoteInterfaceObj->GetCurLimitDataIndex(),RemoteInterfaceObj->getCurLimit());
        strGab = QString::number((qreal) value,'f',2);
        ui->tableWidget->setItem(ui->tableWidget->currentRow(),0,new QTableWidgetItem(strGab));
        refreshLimitData();

        ui->tableWidget->setCurrentCell(RemoteInterfaceObj->GetCurLimitDataIndex(),0);
        break;
    case RTSA_INPUT_LIMIT_AMPT:
        value = RemoteInterfaceObj->getLimitCurPointAmpt(RemoteInterfaceObj->GetCurLimitDataIndex(),RemoteInterfaceObj->getCurLimit());
//        value = mControl->getRefLevel();
        strGab = QString::number((qreal) value,'f',2);
//        strGab = mControl->getRefLevelAdjustStr();
        ui->tableWidget->setItem(ui->tableWidget->currentRow(),1,new QTableWidgetItem(strGab));
        refreshLimitData();

        ui->tableWidget->setCurrentCell(RemoteInterfaceObj->GetCurLimitDataIndex(),1);
        break;
    case RTSA_INPUT_LIMIT_SELECT_INDEX:
        ui->tableWidget->setCurrentCell(RemoteInterfaceObj->GetCurLimitDataIndex(),0);
        refreshCurRowIndex();
        break;
    default:
        break;
    }
    return ;
}

/**
* @brief change cur dialog title, because this dialog use for limit and fmt
* @param  title str name
* @Author Albert
* @date 2019-05-10
*/
void RtSa_Dialog_LimitTable::changeTitleName(QString str)
{
    ui->lblTitle->setText(str);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-13
*/
void RtSa_Dialog_LimitTable::on_LED_CurPtIndex_clicked()
{
    showInputDialog(RTSA_INPUT_LIMIT_SELECT_INDEX);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-13
*/
void RtSa_Dialog_LimitTable::refreshCurRowIndex()
{
    qint32 index = RemoteInterfaceObj->GetCurLimitDataIndex() + 1;
    QString str = QString::number(index,'f',0);
    ui->LED_CurPtIndex->setText(str);
//    ui->tableWidget->setCurrentCell(index - 1,0);
    ui->tableWidget->setFocus();
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-13
*/
void RtSa_Dialog_LimitTable::refreshLimitData()
{
    ui->tableWidget->sortAllItems();
    ui->tableWidget->judgeTableContent(ui->tableWidget,RemoteInterfaceObj->getStartFreq(),RemoteInterfaceObj->getStopFreq());
    qint32 row = ui->tableWidget->rowCount();
    qint32 LimitID = RemoteInterfaceObj->getCurLimit();
    mLimitFreq = ui->tableWidget->getLimitFreq();
    mLimitAmpt = ui->tableWidget->getLimitAmpt();
    RemoteInterfaceObj->setLimitFreqData(mLimitFreq,row,LimitID);
    RemoteInterfaceObj->setLimitAmptData(mLimitAmpt,row,LimitID);
    return;
}

void RtSa_Dialog_LimitTable::setShowType(qint32 type)
{
    mShowType = type;
    return;
}
