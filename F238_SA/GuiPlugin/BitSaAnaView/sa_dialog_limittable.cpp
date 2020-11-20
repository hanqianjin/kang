#include "sa_dialog_limittable.h"
#include "ui_sa_dialog_limittable.h"
#include "sa_applicationcontrol.h"
#include "sa_dialog_digitinput.h"
SA_Dialog_LimitTable::SA_Dialog_LimitTable(controlInterface *interface,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SA_Dialog_LimitTable)
{
    ui->setupUi(this);
    mParent = parent;
    mControl = interface;

    setProperty("status",qssMode[mControl->GetDisplayMode()]);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->verticalHeader()->setVisible(true);
    ui->tableWidget->verticalHeader()->setMinimumWidth(12);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //Need to set
    ui->tableWidget->verticalScrollBar()->setStyleSheet("");
    mInputDialog = NULL;
    connect(ui->LED_CurPtIndex,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));

    initWidget();
    initDisplay();
}
/**
 * @brief  Init widget.Set button or other control postion.
 * @param  void
 * @author Tony
 * @since 2019-05-20
 * @note   Must be placed after "initMap()";
*/
void SA_Dialog_LimitTable::initWidget()
{
    qint32 mMode = mControl->getCurrentMode();
    if(SA_SPURIOUS_EMISSION_MASK_MODE == mMode||\
            SA_SPECTRUM_EMISSION_MASK_MODE == mMode)
    {

        ui->pb_InsertRow->setVisible(false);
        ui->pb_DeleteRow->setVisible(false);
        ui->lblCurRowIndex->setVisible(false);
        ui->LED_CurPtIndex->setVisible(false);
        ui->lblFreq->setVisible(false);
        ui->lblAmpt->setVisible(false);
        ui->tableWidget->setVisible(false);
        ui->pb_DeleteLimit->setVisible(false);

        mCurEdit = -1;
        curColum = 0;
    }else
    {
        mCurEdit = 0;
        curColum = 0;

        ui->LED_CurPtIndex->setFocus();
    }
}

void SA_Dialog_LimitTable::initDisplay()
{
    initTable();
    refreshLineEdit();
}

SA_Dialog_LimitTable::~SA_Dialog_LimitTable()
{
    mParent->setFocus();
    delete ui;
}
/**
* @name          [slot] on_pb_InsertRow_clicked
* @brief         insert one row
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_LimitTable::on_pb_InsertRow_clicked()
{
    mControl->setInsertLimitRow();
    initDisplay();
    return;
}
/**
* @name          [slot] on_pb_DeleteRow_clicked
* @brief         delete one row
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_LimitTable::on_pb_DeleteRow_clicked()
{
    qint32 mLimitIndex,mLimitPoint;
    mLimitIndex = mControl->getLimitSelect();
    mLimitPoint = mControl->getLimitCurPointIndex(mLimitIndex)-1;
    mControl->setDeleteLimitRow(mLimitIndex,mLimitPoint);
    initDisplay();
    return;
}
/**
* @name          [slot] on_pb_DeleteLimit_clicked
* @brief         delete one limit data
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_LimitTable::on_pb_DeleteLimit_clicked()
{
    mControl->setDeleteLimitAll();
    initDisplay();
    return;
}

/**
* @name          [slot] on_pb_cancel_clicked
* @brief         close this window
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_LimitTable::on_pb_cancel_clicked()
{
    this->close();
    return;
}
/**
* @name          [slot]on_tableWidget_cellClicked
* @brief         clicked and edit limit
* @param[in]     row column
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_LimitTable::on_tableWidget_cellClicked(int row, int column)
{
    if(mCurEdit == 0)
    {
        ui->LED_CurPtIndex->setStyleSheet("");
        mCurEdit = 1;
    }
    //
    curColum = column;
    qint32 limit = mControl->getLimitSelect();
    mControl->setLimitCurPointIndex(limit,row+1);
    if(column == 0) //input frequency
    {
        showInputDialog(SA_INPUT_LIMIT_FREQ);
    }
    else if(column == 1) //inpuy amplitude
    {
        showInputDialog(SA_INPUT_LIMIT_AMPT);
    }
    return ;
}
/**
* @name          showInputDialog
* @brief         show digit input window
* @param[in]     index -- window's index
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_LimitTable::showInputDialog(qint32 index)
{
    if(mInputDialog)
    {
        mInputDialog->initDisplay(index);
        mInputDialog->setFocus();
    }else
    {
        mInputDialog = new SA_Dialog_DigitInput(mControl,mControl->globalUserVariable,index,this);
        mInputDialog->setFocus();
        mInputDialog->setGeometry(mapToGlobal(QPoint(0,0)).x(),mapToGlobal(QPoint(0,0)).y(),DIGITINPUT_WIDTH,DIGITINPUT_HEIGHT);
        connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
        mInputDialog->show();
    }
    return ;
}
/**
* @name          on_finishEntry
* @brief         [slot]
* @param[in]     index -- window's index
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_LimitTable::on_finishEntry(qint32 index)
{
    disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
    mInputDialog = NULL;
    initDisplay();
    return ;
}
/**
* @name          digitInputClose
* @brief         close digit input window
* @param[in]     index -- window's index
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_LimitTable::digitInputClose()
{
    if(mInputDialog)
    {
        disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
        delete mInputDialog;
        mInputDialog = NULL;
    }
    return;
}
/**
* @name          keyPressEvent
* @brief         keypress event
* @param[in]     event -- signal of key press
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_LimitTable::keyPressEvent(QKeyEvent *event)
{
    qint32 keyvalue = event->key();
    if(event->key() == Qt::Key_PowerOff)
    {
        if(!event->isAutoRepeat())
            QApplication::sendEvent(this->parent(),event);
        return;
    }
    qint32 row,colum;
    switch (keyvalue) {
    case Qt::Key_Escape:
        this->close();
        return;
    case Qt::Key_Shift:
        QCoreApplication::sendEvent(mParent, event);
        this->close();
        return;
    default:
        break;
    }
    if(mCurEdit < 0)
    {
        return;
    }
    row = ui->tableWidget->currentRow();
    colum = ui->tableWidget->currentColumn();

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
        if(mControl->globalUserVariable->bShiftKeyPressed)
        {
            this->close();
        }else if(mCurEdit==0)
        {
            if(!mInputDialog)
            {
                showInputDialog(SA_INPUT_LIMIT_CURPOINTSET);
                QCoreApplication::sendEvent(mInputDialog, event);
            }else
            {
                QCoreApplication::sendEvent(mInputDialog, event);
            }

        }else if(mCurEdit==1)
        {
            if(row >= 0 && colum >= 0 && !mInputDialog)
            {
                on_tableWidget_cellClicked(row,colum);
                QCoreApplication::sendEvent(mInputDialog, event);
            }else if(mInputDialog)
            {
                QCoreApplication::sendEvent(mInputDialog, event);
            }
        }
        break;
    case Qt::Key_F4:

        if(mInputDialog)
            mInputDialog->close();
        if(mCurEdit==0)
        {
            getEditKnobValue(CLOCKWISE);
        }else if(mCurEdit==1)
        {
            getKnobValue(CLOCKWISE);
        }

        break;
    case Qt::Key_F3:
        if(mInputDialog)
            mInputDialog->close();
        if(mCurEdit==0)
        {
            getEditKnobValue(ANTICLOCKWISE);
        }else if(mCurEdit==1)
        {
            getKnobValue(ANTICLOCKWISE);
        }
        break;
    case Qt::Key_Up:
        if(mCurEdit==0)
        {
            getEditKnobValue(CLOCKWISE);
        }else if(mCurEdit==1)
        {
            tabelChange(-2);
        }
        break;
    case Qt::Key_Down:
        if(mCurEdit==0)
        {
            getEditKnobValue(ANTICLOCKWISE);
        }else if(mCurEdit==1)
        {
            tabelChange(2);
        }
        break;
    case Qt::Key_Left:
        if(mCurEdit==0)
        {

        }else if(mCurEdit==1)
        {
            tabelChange(-1);
        }
        break;
    case Qt::Key_Right:
        if(mCurEdit==0)
        {

        }else if(mCurEdit==1)
        {
            tabelChange(1);
        }
        break;
    default:
        if(mInputDialog) QApplication::sendEvent(mInputDialog,event);
        break;
    }
}
/**
* @name          getKnobValue
* @brief         Operation of knob
* @param[in]     mode
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_LimitTable::getKnobValue(qint32 mode)
{
    qreal mStep;
    qreal mValue;
    qreal row,column;
    qint32 curLimit;
    row = ui->tableWidget->currentRow();
    column = ui->tableWidget->currentColumn();
    curLimit = mControl->getLimitSelect();
    if(row <0 || column < 0)
        return;
    if(column == 0) //input frequency
    {
        mValue = mControl->getLimitFreq(curLimit,row);
        mStep  = mControl->getCFFreq();
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        mControl->setLimitFreq(curLimit,row,mValue);
    }
    else if(column == 1) //inpuy amplitude
    {
        mValue = mControl->getLimitAmpt(curLimit,row);
        mStep  = 0.1;
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        mControl->setLimitAmpt(curLimit,row,mValue);
    }
    initDisplay();
    return;
}
void SA_Dialog_LimitTable::getEditKnobValue(qint32 mode)
{
    qint32 curPoint,curLimit;
    curLimit = mControl->getLimitSelect();
    if(mode){
        tabelChange(2);
    }else{
        tabelChange(-2);
    }
    curPoint =  ui->tableWidget->currentRow();
    mControl->setLimitCurPointIndex(curLimit,curPoint+1);
    initDisplay();
    return;
}

/**
* @name          tabelChange()
* @brief         when press up/down/lefft/right button.
* @param[in]     step  up -- -2 left -- -1 right -- 1 down -- 2
* @author        Tony
* @date          2019-03-26
*/
void SA_Dialog_LimitTable::tabelChange(qint32 step)
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
    ui->tableWidget->blockSignals(false);
    mControl->setLimitCurPointIndex(mControl->getLimitSelect(),1);
    refreshLineEdit();
    curColum = colum;
    return;
}
/**
* @name          initTable()
* @brief         init table.
* @param
* @author        Tony
* @date          2019-03-26
*/
void SA_Dialog_LimitTable::initTable()
{
    if(mInputDialog)
    {
        mInputDialog->close();
    }
    //ui->LED_CurPtIndex->setFocus();
    qint32 index,size;
    qint32 rowNum;
    QString strFreq,strAmplitude;

    rowNum = ui->tableWidget->rowCount();
    for(int i = rowNum-1;i>=0;i--)
    {
        ui->tableWidget->removeRow(i);
    }
    index = mControl->getLimitSelect();
    size = mControl->globalUserLimit->gTotalDot[index];
    for(qint32 i = 0; i < size;i++)
    {
        strFreq = QString::number(mControl->getLimitFreq(index,i)/SA_MHZ,'f',2);
        QTableWidgetItem *freqItem = new QTableWidgetItem(strFreq);

        strAmplitude = QString::number(mControl->getLimitAmpt(index,i),'f',2);
        QTableWidgetItem *amplitudeItem = new QTableWidgetItem(strAmplitude);

        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,freqItem);
        ui->tableWidget->setItem(i,1,amplitudeItem);
    }
    ui->tableWidget->setCurrentCell(mControl->getLimitCurPointIndex()-1,curColum);
    return;
}

//Tony 0214
void SA_Dialog_LimitTable::on_getFocus(SA_LineEdit* mEdit)
{
    mCurEdit = 0;
    QString qss =QString("outline: none;border:2px solid rgba(162,115,0,1);padding:6px 6px 5px 8px;");
    ui->LED_CurPtIndex->setStyleSheet(qss);
    return;
}

void SA_Dialog_LimitTable::on_tableWidget_clicked()
{
    ui->LED_CurPtIndex->setStyleSheet("");
    mCurEdit = 1;
    return;
}

void SA_Dialog_LimitTable::on_tableWidget_cellChanged(int row, int column)
{
    refreshLineEdit();
}
void SA_Dialog_LimitTable::refreshLineEdit()
{
    QString strGab;
    qint32 mCurPoint = mControl->getLimitCurPointIndex()-1;
    qint32 mCurLimit = mControl->getLimitSelect();
    if(mControl->globalUserLimit->gTotalDot[mCurLimit] == 0)
    {
        strGab = "-- --";
    }
    else
    {
        strGab = QString::number(mCurPoint+1);
    }
    ui->LED_CurPtIndex->setText(strGab);
}

void SA_Dialog_LimitTable::on_LED_CurPtIndex_clicked()
{
    mCurEdit = 0;
    digitInputClose();
    showInputDialog(SA_INPUT_LIMIT_CURPOINTSET);
}
