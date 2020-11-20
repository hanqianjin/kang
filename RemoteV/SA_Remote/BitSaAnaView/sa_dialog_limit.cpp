#include "sa_dialog_limit.h"
#include "ui_sa_dialog_limit.h"
#include "sa_applicationcontrol.h"
#include "sa_dialog_limittable.h"
#include "sa_dialog_digitinput.h"
#include "sa_dialog_warning.h"
SA_Dialog_Limit::SA_Dialog_Limit(controlInterface *interface,QWidget *parent) :
    QWidget(parent),
    mControl(interface),
    ui(new Ui::SA_Dialog_Limit)
{
    ui->setupUi(this);
    setProperty("status",qssMode[mControl->GetDisplayMode()]);
    //setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | /*Qt::Dialog|*/Qt::CustomizeWindowHint);
    initMap();
    initWidget();
    initDisplay();

    this->setFocus();
    mInputDialog = NULL;
    mLimitTable = NULL;
    hide();
}

SA_Dialog_Limit::~SA_Dialog_Limit()
{
    digitInputClose();
    if(mLimitTable)
    {
        disconnect(mLimitTable,SIGNAL(destroyed()),this,SLOT(on_limitDestroyed()));
        delete mLimitTable;
        mLimitTable = NULL;
    }
    delete ui;
}
/**
 * @brief  Init widget.Set button or other control postion.
 * @param  void
 * @author Tony
 * @since 2019-05-20
 * @note   Must be placed after "initMap()";
*/
void SA_Dialog_Limit::initWidget()
{
    qint32 mMode = mControl->getCurrentMode();
    if(SA_SPURIOUS_EMISSION_MASK_MODE == mMode || SA_SPECTRUM_EMISSION_MASK_MODE == mMode ||
       SA_CHNLPOWER_MEASURE_MODE == mMode || SA_OCCUPIED_BW_MEASURE_MODE == mMode ||
       SA_ACP_MEASURE_MODE == mMode || SA_MULTI_ACP_MODE == mMode)
    {
        ui->lblLimit->setVisible(false);
        ui->pb_toggle->setVisible(false);
        ui->pb_LM1->setVisible(false);
        ui->pb_LM2->setVisible(false);
        ui->pb_LM3->setVisible(false);
        ui->pb_LM4->setVisible(false);
        ui->pb_LM5->setVisible(false);
        ui->pb_LM6->setVisible(false);
        ui->lblLimitLine->setVisible(false);
        ui->pb_EditMask->setVisible(false);
        ui->lblLimitEdge->setVisible(false);
        ui->pb_Edge->setVisible(false);
        ui->lineEdit->setVisible(false);
        ui->lblLimitTest->setVisible(false);
        ui->pb_LimitTest->setVisible(false);
        ui->lblEditLimitEdge->setVisible(false);
        ui->lblLimitType->setVisible(false);
        ui->pb_Upper->setVisible(false);
        ui->pb_Lower->setVisible(false);
        ui->pb_DeleteAll->setVisible(false);
    }else
    {
        ui->lblLimit->setVisible(true);
        ui->pb_toggle->setVisible(true);
        ui->pb_LM1->setVisible(true);
        ui->pb_LM2->setVisible(true);
        ui->pb_LM3->setVisible(true);
        ui->pb_LM4->setVisible(true);
        ui->pb_LM5->setVisible(true);
        ui->pb_LM6->setVisible(true);
        ui->lblLimitLine->setVisible(true);
        ui->pb_EditMask->setVisible(true);
        ui->lblLimitEdge->setVisible(true);
        ui->pb_Edge->setVisible(true);
        ui->lineEdit->setVisible(true);
        ui->lblLimitTest->setVisible(true);
        ui->pb_LimitTest->setVisible(true);
        ui->lblEditLimitEdge->setVisible(true);
        ui->lblLimitType->setVisible(true);
        ui->pb_Upper->setVisible(true);
        ui->pb_Lower->setVisible(true);
        ui->pb_DeleteAll->setVisible(true);
    }
}

/**
* @name          initMap()
* @brief         init button and some controls.
* @param
* @author        Tony
* @date          2019-03-25
*/
void SA_Dialog_Limit::initMap()
{
    mLimitSelectGroup = new QButtonGroup();
    mLimitSelectGroup->addButton(ui->pb_LM1,LIMIT1);
    mLimitSelectGroup->addButton(ui->pb_LM2,LIMIT2);
    mLimitSelectGroup->addButton(ui->pb_LM3,LIMIT3);
    mLimitSelectGroup->addButton(ui->pb_LM4,LIMIT4);
    mLimitSelectGroup->addButton(ui->pb_LM5,LIMIT5);
    mLimitSelectGroup->addButton(ui->pb_LM6,LIMIT6);
    connect(mLimitSelectGroup,SIGNAL(buttonClicked(qint32)),this,SLOT(mLimitSelectGroup_click(qint32)));
    return ;
}
/**
* @name          initDisplay()
* @brief         init display of windos and buttons.
* @param
* @author        Tony
* @date          2019-03-25
*/
void SA_Dialog_Limit::initDisplay()
{
    qreal value;
    qint32 btnIndex,status;
    btnIndex = mControl->getLimitSelect();
    mLimitSelectGroup->button(btnIndex)->setChecked(true);

    status = mControl->getLimitLineStatus();
    ui->pb_toggle->setChecked(status);

    status = mControl->getLimitTestStatus();
    ui->pb_LimitTest->setChecked(status);

    status = mControl->getLimitEdgeStatus();
    ui->pb_Edge->setChecked(status);

    status = mControl->getLimitType();
    if(status == UPPER)
        ui->pb_Upper->setChecked(true);
    else
        ui->pb_Lower->setChecked(true);

    value = mControl->getLimitEdgeValue();
    ui->lineEdit->setText(QString::number(value,'f',2)+" dB");
}
/**
* @name          keyPressEvent
* @brief         keypress event
* @param[in]     event -- signal of key press
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_Limit::keyPressEvent(QKeyEvent *event)
{
    qint32 mMode = mControl->getCurrentMode();
    if(SA_SPURIOUS_EMISSION_MASK_MODE == mMode || SA_SPECTRUM_EMISSION_MASK_MODE == mMode ||
       SA_CHNLPOWER_MEASURE_MODE == mMode || SA_OCCUPIED_BW_MEASURE_MODE == mMode ||
       SA_ACP_MEASURE_MODE == mMode || SA_MULTI_ACP_MODE == mMode)
    {
        if(event->key() == Qt::Key_Escape)
        {
            hideWidget();
        }
        return;
    }

    qint32 keyvalue = event->key();
    if(event->key() == Qt::Key_PowerOff)
    {
        if(!event->isAutoRepeat())
            QApplication::sendEvent(this->parent(),event);
        return;
    }
    switch (keyvalue) {
    case Qt::Key_Escape:
        if(mInputDialog)
        {
            digitInputClose();
        }else if(mLimitTable)
        {
            QCoreApplication::sendEvent(mLimitTable, event);
            return;
        }
        else
        {
            hideWidget();
        }
        return;
    case Qt::Key_Shift:
        if(mControl->globalUserVariable->bShiftKeyPressed)
            mControl->globalUserVariable->bShiftKeyPressed = false;
        else
            mControl->globalUserVariable->bShiftKeyPressed = true;
        hideWidget();
        return;
    default:
        break;
    }
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
        if(!mInputDialog && !mLimitTable)
        {
            ui->lineEdit->clicked();
            QCoreApplication::sendEvent(mInputDialog, event);
        }else if(mInputDialog && !mLimitTable)
        {
            QCoreApplication::sendEvent(mInputDialog, event);
        }else if(!mInputDialog && mLimitTable)
        {
            QCoreApplication::sendEvent(mLimitTable, event);
        }
        break;
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
        if(!mInputDialog && mLimitTable)
        {
            QCoreApplication::sendEvent(mLimitTable, event);
        }
        break;
    case Qt::Key_F4:
        if(!mInputDialog && mLimitTable)
        {
            QCoreApplication::sendEvent(mLimitTable, event);
            break;
        }
        if(mInputDialog)
            mInputDialog->close();
        getKnobValue(CLOCKWISE);
        break;
    case Qt::Key_F3:
        if(!mInputDialog && mLimitTable)
        {
            QCoreApplication::sendEvent(mLimitTable, event);
            break;
        }
        if(mInputDialog)
            mInputDialog->close();
        getKnobValue(ANTICLOCKWISE);
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
void SA_Dialog_Limit::getKnobValue(qint32 mode)
{
    qreal mStep;
    qreal mValue;
    mStep = 0.1;
    mValue = mControl->getLimitEdgeValue();
    if(mode)
        mValue += mStep;
    else
        mValue -= mStep;
    if(mValue < 0)
        mValue = 0;
    mControl->setLimitEdgeValue(mValue);

    mValue = mControl->getLimitEdgeValue();
    ui->lineEdit->setText(QString::number(mValue,'f',2)+" dB");
    return;
}

/**
* @name          showInputDialog
* @brief         show digit input window
* @param[in]     index -- window's index
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_Limit::showInputDialog(qint32 index)
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
void SA_Dialog_Limit::on_finishEntry(qint32 index)
{
    disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
    mInputDialog = NULL;
    if(index == SA_LIMIT_EDGE)
    {
        ui->lineEdit->setFocus();
        initDisplay();
    }
    return ;
}
/**
* @name          digitInputClose
* @brief         close digit input window
* @param[in]     index -- window's index
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_Limit::digitInputClose()
{
    if(mInputDialog)
    {
        disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
        delete mInputDialog;
        mInputDialog = NULL;
    }
    ui->lineEdit->setFocus();
    initDisplay();
    return;
}
/**
* @name          [slot] on_pb_cancel_clicked
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_Limit::on_pb_cancel_clicked()
{
    hideWidget();
    return;
}
/**
* @name          [slot] mLimitSelectGroup_click
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_Limit::mLimitSelectGroup_click(qint32 index)
{
    mControl->setLimitSelect(index);
    initDisplay();
    return;
}
/**
* @name          [slot] mLimitSelectGroup_click
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_Limit::on_pb_toggle_clicked(bool checked)
{
    mControl->setLimitLineStatus(checked);
    return;
}
/**
* @name          [slot] on_pb_toggle_toggled
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_Limit::on_pb_toggle_toggled(bool checked)
{
    if(checked)
    {
        ui->pb_toggle->setText("On");

    }else
    {
        ui->pb_toggle->setText("Off");
    }
    return;
}
/**
* @name          [slot] on_pb_Edge_clicked
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_Limit::on_pb_Edge_clicked(bool checked)
{
    qreal value;
    mControl->setLimitEdgeStatus(checked);
    value = mControl->getLimitEdgeValue();
    ui->lineEdit->setText(QString::number(value,'f',2)+" dB");
    return;
}
/**
* @name          [slot] on_pb_Edge_toggled
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_Limit::on_pb_Edge_toggled(bool checked)
{
    if(checked)
    {
        ui->pb_Edge->setText("On");

    }else
    {
        ui->pb_Edge->setText("Off");
    }
    return;
}
/**
* @name          [slot] on_pb_LimitTest_clicked
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_Limit::on_pb_LimitTest_clicked(bool checked)
{
    mControl->setLimitTestStatus(checked);
    return;
}
/**
* @name          [slot] on_pb_LimitTest_toggled
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_Limit::on_pb_LimitTest_toggled(bool checked)
{
    if(checked)
    {
        ui->pb_LimitTest->setText("On");

    }else
    {
        ui->pb_LimitTest->setText("Off");
    }
    return;
}
/**
* @name          [slot] on_pb_Upper_clicked
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_Limit::on_pb_Upper_clicked(bool checked)
{
    mControl->setLimitType(UPPER);
    return;
}
/**
* @name          [slot] on_pb_Lower_clicked
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_Limit::on_pb_Lower_clicked(bool checked)
{
    mControl->setLimitType(LOWER);
    return;
}
/**
* @name          [slot] on_pb_DeleteAll_clicked
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_Limit::on_pb_DeleteAll_clicked()
{
    qint32 status = 0;
    for(qint32 i=0;i<LIMIT_SELECTSUM;i++)
    {
       if(mControl->globalUserLimit->gTotalDot[i] != 0)
       {
           status = 1;
           break;
       }
    }
    if(status){
        SA_Dialog_Warning message("Notice","Are you sure to delete all limits?",this);
        message.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
        if(message.exec() != QDialog::Accepted)
        {
            return;
        }

        mControl->setDeleteLimitAll();
        initDisplay();
    }
}
/**
* @name          [slot] on_pb_EditMask_clicked
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_Limit::on_pb_EditMask_clicked()
{
    if(!mLimitTable)
    {
        mLimitTable = new SA_Dialog_LimitTable(mControl,this);
        connect(mLimitTable,SIGNAL(destroyed()),this,SLOT(on_limitDestroyed()));
        mLimitTable->show();
        ui->widget->hide();
    }
}
void SA_Dialog_Limit::refreshTable()
{
    if(!mLimitTable)
    {
        mLimitTable = new SA_Dialog_LimitTable(mControl,this);
        connect(mLimitTable,SIGNAL(destroyed()),this,SLOT(on_limitDestroyed()));
        mLimitTable->show();
        ui->widget->hide();
    }else
    {
        mLimitTable->initTable();
    }
}
/**
* @name          [slot] on_limitDestroyed
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_Limit::on_limitDestroyed()
{
    if(mLimitTable)
    {
        disconnect(mLimitTable,SIGNAL(destroyed()),this,SLOT(on_limitDestroyed()));
        mLimitTable = NULL;
        ui->widget->show();
    }
}
/**
* @name          [slot] on_lineEdit_clicked
* @author        Tony
* @date          2019-03-21
*/
void SA_Dialog_Limit::on_lineEdit_clicked()
{
    showInputDialog(SA_LIMIT_EDGE);
}

void SA_Dialog_Limit::showWidget()
{
    initDisplay();
    show();
    return;
}
void SA_Dialog_Limit::hideWidget()
{
    hide();
    digitInputClose();
    if(mLimitTable)
    {
        disconnect(mLimitTable,SIGNAL(destroyed()),this,SLOT(on_limitDestroyed()));
        mLimitTable->close();
        mLimitTable = NULL;
        ui->widget->setVisible(true);
    }
    emit mDialogHide();
    return;
}
