#include "pm_dialog_caltable.h"
#include "ui_pm_dialog_caltable.h"
#include <QScrollBar>

Pm_Dialog_CalTable::Pm_Dialog_CalTable(BitPm_Interface *BitPmInterface, Pm_Dialog_Digitinput *mInput, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pm_Dialog_CalTable),
    PmInterfaceObj(BitPmInterface),
    mInputDialog(mInput),
    mColumnIndex(PM_INPUT_CAL_ARRAY)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->verticalHeader()->setVisible(true);
    ui->tableWidget->verticalHeader()->setMinimumWidth(12);
    ui->tableWidget->setEditTriggers(QAbstractItemView::AnyKeyPressed);
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->tableWidget->verticalScrollBar()->setStyleSheet("");
    ui->tableWidget->setFocusPolicy(Qt::StrongFocus);
    connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
    connect(ui->tableWidget,SIGNAL(contenJudge(qint32)),this,SLOT(resetTableSort(qint32)));
    connect(ui->tableWidget,SIGNAL(KeySignal(QKeyEvent*)),this,SLOT(respondKeyEvent(QKeyEvent*)));

    initTable();
    initDisplay();
    if(PM_CALIBRATION_ARRAY == PmInterfaceObj->getCalSelectType())
    {
        mColumnIndex = PM_INPUT_CAL_ARRAY;
    }
    else
    {
        mColumnIndex = PM_INPUT_CAL_CENTER_FREQ;
    }
    connect(PmInterfaceObj,SIGNAL(finishCal()),this,SLOT(on_finishCal()));
    PmInterfaceObj->cmd_GetSensorCalibrationData();
    setProperty("status",pm_qssMode[PmInterfaceObj->getSystemDisplay()]);
}

Pm_Dialog_CalTable::~Pm_Dialog_CalTable()
{
    delete ui;
}

void Pm_Dialog_CalTable::on_pb_cancel_clicked()
{
    this->close();
    return;
}

void Pm_Dialog_CalTable::on_tableWidget_cellClicked(int row, int column)
{
    QTableWidgetItem *item=ui->tableWidget->item(row,column);
    ui->tableWidget->editItem(item);
    PmInterfaceObj->setCalAmptNo(row);
     mColumnIndex = PM_INPUT_CAL_AMPT;
    showInputDialog(mColumnIndex);
   this->setFocus();
    return ;
}

/**
* @brief
* @note
* @Author	ROC
* @date     2020.1.3
*/
void Pm_Dialog_CalTable::showInputDialog(qint32 index)
{
    if(mInputDialog->isHidden())
    {
        mInputDialog->setGeometry(mapToGlobal(QPoint(0,0)).x()/*+this->width()*//*-PM_DIGITAL_DIALOG_WIDTH*/,\
                                  mapToGlobal(QPoint(0,0)).y(),PM_DIGITAL_DIALOG_WIDTH,PM_DIGITAL_DIALOG_HEIGHT);
    }
    mInputDialog->initDisplay(index);
    mInputDialog->setProperty("status", pm_qssMode[PmInterfaceObj->getSystemDisplay()]);
    mInputDialog->setStyle(QApplication::style());
    if(mInputDialog->isHidden())
        mInputDialog->show();
    return ;
}

void Pm_Dialog_CalTable::on_finishEntry(qint32 index)
{
    if(mEditList.contains(index))
    {
        PmInterfaceObj->cmd_GetSensorCalibrationData();
    }
    else
    {
        qint32 nRow = PmInterfaceObj->getCalAmptNo();
        QString strAmplitude = QString::number(PmInterfaceObj->getCalAmptData(nRow),'f',2);
        QTableWidgetItem *amplitudeItem = new QTableWidgetItem(strAmplitude);
        ui->tableWidget->setItem(nRow,1,amplitudeItem);

    }
    ui->tableWidget->setFocus();
    return ;
}

void Pm_Dialog_CalTable::keyPressEvent(QKeyEvent *event)
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
    qint32 row,colum;
    switch (keyvalue) {
    case Qt::Key_Escape:
        if(!mInputDialog->isHidden())
        {
            mInputDialog->hide();
            return;
        }
//        emit finishEntry(PM_NOT_USE);
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
        if(PmInterfaceObj->isShiftKeyEnable())
        {
            this->close();
        }else
        {
            if(mInputDialog->isHidden())
            {
                if(PM_CALIBRATION_ARRAY == PmInterfaceObj->getCalSelectType())
                {
                    if(PM_INPUT_CAL_CENTER_FREQ != mColumnIndex)
                        showInputDialog(mColumnIndex);
                }
                else if(PM_CALIBRATION_FREQ == PmInterfaceObj->getCalSelectType())
                {
                    if(PM_INPUT_CAL_ARRAY != mColumnIndex)
                        showInputDialog(mColumnIndex);
                }
                else
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

void Pm_Dialog_CalTable::respondKeyEvent(QKeyEvent *event)
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
        if(PmInterfaceObj->isShiftKeyEnable())
        {
            this->close();
        }else
        {
            if(mInputDialog->isHidden())
            {
                if(PM_CALIBRATION_ARRAY == PmInterfaceObj->getCalSelectType())
                {
                    if(PM_INPUT_CAL_CENTER_FREQ != mColumnIndex)
                        showInputDialog(mColumnIndex);
                }
                else if(PM_CALIBRATION_FREQ == PmInterfaceObj->getCalSelectType())
                {
                    if(PM_INPUT_CAL_ARRAY != mColumnIndex)
                        showInputDialog(mColumnIndex);
                }
                else
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


void Pm_Dialog_CalTable::resetTableSort(qint32 rowIndex)
{

//    ui->tableWidget->judgeTableContent(ui->tableWidget,PmInterfaceObj->getStartFreq(),PmInterfaceObj->getStopFreq());
//    ui->tableWidget->resetAllParam();
//    PmInterfaceObj->SetCurLimitDataIndex(rowIndex);
//    qint32 a = ui->tableWidget->currentColumn();
//    qint32 b = ui->tableWidget->currentRow();
//    mColumnIndex = RTSA_INPUT_LIMIT_FREQ + ui->tableWidget->currentColumn();
//    refreshCurRowIndex();
//    this->setFocus();
    return;
}

void Pm_Dialog_CalTable::refreshEditDisplay(quint32 index)
{
    QString strGab;
    qreal   value;
      qlonglong   nllValue;
    if(!mEditList.contains(index))
        return;
    switch (index)
    {
    case PM_INPUT_CAL_ARRAY:
        value = PmInterfaceObj->getCalArray();
        strGab = QString::number(value);
        break;
    case PM_INPUT_CAL_CENTER_FREQ:
        nllValue = PmInterfaceObj->getCalCenterFreqMHz();
        strGab = PmInterfaceObj->getFreqMHzAdjustStr(nllValue);;
        break;
    default:
        break;
    }
    mEditList.find(index).value()->setText(strGab);
    return ;
}


/**
* @brief
* @note
* @Author	ROC
* @date     2020.1.3
*/
void Pm_Dialog_CalTable::on_pb_arrayNo_clicked()
{
    PmInterfaceObj->setCalSelectType(PM_CALIBRATION_ARRAY);
    if(PM_CALIBRATION_ARRAY == PmInterfaceObj->getCalSelectType())
    {
        ui->leFreq->setReadOnly(true);
    }
    PmInterfaceObj->cmd_GetSensorCalibrationData();
}
/**
* @brief
* @note
* @Author	ROC
* @date     2020.1.3
*/
void Pm_Dialog_CalTable::on_pb_arrayFreq_clicked()
{
    PmInterfaceObj->setCalSelectType(PM_CALIBRATION_FREQ);
    if(PM_CALIBRATION_FREQ == PmInterfaceObj->getCalSelectType())
    {
        ui->leArrayIndex->setReadOnly(true);
    }
    PmInterfaceObj->cmd_GetSensorCalibrationData();
}

void Pm_Dialog_CalTable::on_leArrayIndex_clicked()
{
    mColumnIndex = PM_INPUT_CAL_ARRAY;
   if(PM_CALIBRATION_ARRAY == PmInterfaceObj->getCalSelectType())
    {
        showInputDialog(PM_INPUT_CAL_ARRAY);
    }
    return;
}

void Pm_Dialog_CalTable::on_leFreq_clicked()
{
    mColumnIndex = PM_INPUT_CAL_CENTER_FREQ;
   if(PM_CALIBRATION_FREQ == PmInterfaceObj->getCalSelectType())
    {
        showInputDialog(PM_INPUT_CAL_CENTER_FREQ);
    }
    return;
}
/**
* @brief	接收到校准值后刷新
* @note
* @Author	ROC
* @date     2020.1.4
*/
void Pm_Dialog_CalTable::on_finishCal()
{
    refreshEditDisplay(PM_INPUT_CAL_ARRAY);
    refreshEditDisplay(PM_INPUT_CAL_CENTER_FREQ);

    QString index,strAmplitude;
    qreal* ampt = PmInterfaceObj->getCalAmptArrayData();
    for(qint32 i = 0; i < PM_V90_CAL_AMPT;i++)
    {
        index = QString::number(i);
        QTableWidgetItem *freqItem = new QTableWidgetItem(index);

        strAmplitude = QString::number(ampt[i],'f',2);
        QTableWidgetItem *amplitudeItem = new QTableWidgetItem(strAmplitude);
        if(ui->tableWidget->rowCount() <PM_V90_CAL_AMPT)
            ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,freqItem);
        ui->tableWidget->setItem(i,1,amplitudeItem);
    }
    return;
}


/**
* @brief change cur dialog title
* @param  title str name
* @Author	ROC
* @date     2020.1.3
*/
void Pm_Dialog_CalTable::changeTitleName(QString str)
{
    ui->lblTitle->setText(str);
    return;
}

/**
* @brief  Init the display
* @param  void
* @author Roc
* @date   2020.1.3
*/
void Pm_Dialog_CalTable::initDisplay()
{
    refreshEditDisplay(PM_INPUT_CAL_ARRAY);
    refreshEditDisplay(PM_INPUT_CAL_CENTER_FREQ);
    return ;
}

/**
* @brief	初始化表格
* @note
* @Author	ROC
* @date     2020.1.4
*/
void Pm_Dialog_CalTable::initTable()
{
    qint32 rowNum;
    rowNum = ui->tableWidget->rowCount();
    for(int i = rowNum-1;i>=0;i--)
    {
        ui->tableWidget->removeRow(i);
    }
    mEditList.insert(PM_INPUT_CAL_ARRAY,ui->leArrayIndex);
    mEditList.insert(PM_INPUT_CAL_CENTER_FREQ,ui->leFreq);
    if(PM_CALIBRATION_ARRAY == PmInterfaceObj->getCalSelectType())
    {
        mColumnIndex = PM_INPUT_CAL_ARRAY;
        ui->leFreq->setReadOnly(true);
    }
    else if(PM_CALIBRATION_FREQ == PmInterfaceObj->getCalSelectType())
    {
        mColumnIndex = PM_INPUT_CAL_CENTER_FREQ;
        ui->leArrayIndex->setReadOnly(true);
    }
    return;
}


void Pm_Dialog_CalTable::on_pb_setCalTo_clicked()
{
    if(ui->tableWidget->rowCount()>=PM_V90_CAL_AMPT)
    {
        QTableWidgetItem *widgetItem;
        QString strAmplitude;
        for(qint32 i = 0; i < PM_V90_CAL_AMPT;i++)
        {
            widgetItem = ui->tableWidget->item(i,1);
            strAmplitude = widgetItem->text();
            PmInterfaceObj->setCalCmdData(i,strAmplitude.toDouble());
        }
        PmInterfaceObj->cmd_setSensorCalibrationData();
    }
}
