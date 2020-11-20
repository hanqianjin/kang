#include "pm_dialog_zerosetup.h"
#include "ui_pm_dialog_zerosetup.h"
#include <QListView>

Pm_Dialog_ZeroSetup::Pm_Dialog_ZeroSetup(BitPm_Interface *BitPmInterface,Pm_Dialog_Digitinput *Input,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pm_Dialog_ZeroSetup),
    PmInterfaceObj(BitPmInterface),
    mInputDialog(Input),
    mUpDownFlag(0),
    mCalTable(NULL)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    this->hide();

    connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(finishEntry_zero(qint32)));
    connect(mInputDialog,SIGNAL(ClockWiseDown(QKeyEvent*)),this,SLOT(DigitalKeyRespond(QKeyEvent*)));

    initMap();
    initDisplay();

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(on_timeOut()));
    setProperty("status",pm_qssMode[PmInterfaceObj->getSystemDisplay()]);
}

Pm_Dialog_ZeroSetup::~Pm_Dialog_ZeroSetup()
{
    delete ui;
}

void Pm_Dialog_ZeroSetup::keyPressEvent(QKeyEvent *event)
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
        if(!mInputDialog->isHidden())
        {
            mInputDialog->hide();
            return;
        }

        if(mCalTable != NULL)
        {
            mCalTable->close();
            return;
        }
        this->close();
        break;
    case Qt::Key_Shift:
        PmInterfaceObj->setShiftKeyEnable(true);
        if(!mInputDialog->isHidden())
        {
            mInputDialog->hide();
        }
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
    case Qt::Key_F6://key_left
    case Qt::Key_Right:
    case Qt::Key_F7:
//        if(mSelectInputID == PM_INPUT_FREQ_CHANNEL_STANDARD)
//            return;
        if(mInputDialog->isHidden())
        {
            mInputDialog->clearEdit();
        }
        mInputDialog->keyresponse(keyvalue);
        break;
    case Qt::Key_F3:
    case Qt::Key_Up:
    case Qt::Key_F8:
        mUpDownFlag = 0;
        if(timer->isActive())
        {
        }
        else
        {
            timer->start(100);
        }
        break;
    case Qt::Key_Down:
    case Qt::Key_F9:
    case Qt::Key_F4:
        mUpDownFlag = 1;
        if(timer->isActive())
        {
        }
        else
        {
            timer->start(100);
        }
        break;
    }
    return;
}

void Pm_Dialog_ZeroSetup::finishEntry_zero(qint32 index)
{
    if(this->isHidden())
        return ;
    if(mEditList.contains(index))
    {
        refreshEditDisplay(PM_INPUT_CAL_CENTER_FREQ);
    }
    if(index == PM_NOT_USE)
    {
        this->close();
    }
    if(index == PM_SHIFT_ENABLE)
    {
        PmInterfaceObj->setShiftKeyEnable(true);
        this->close();
    }
    return;
}

void Pm_Dialog_ZeroSetup::on_pb_cancel_clicked()
{
    mInputDialog->close();

    this->close();
    return;
}

void Pm_Dialog_ZeroSetup::DigitalKeyRespond(QKeyEvent *event)
{
    keyPressEvent(event);
    return;
}

/**
* @brief
* @param
* @author Roc
* @since  2019.11.5
*/
void Pm_Dialog_ZeroSetup::on_timeOut()
{
    timer->stop();
    if(!mInputDialog->isHidden())
    {
        mInputDialog->hide();
    }
    return;
}


void Pm_Dialog_ZeroSetup::on_pb_setZero_clicked()
{
    PmInterfaceObj->setZero(true);
    refreshButtonDisplay();

}

void Pm_Dialog_ZeroSetup::on_pb_calFactor_clicked()
{
    if(mCalTable == NULL)
    {
        mCalTable = new Pm_Dialog_CalTable(PmInterfaceObj,mInputDialog,this);
        connect(mCalTable,SIGNAL(destroyed()),this,SLOT(on_calDestroyed()));}
    else
    {
        connect(mCalTable,SIGNAL(destroyed()),this,SLOT(on_calDestroyed()));
    }

    mCalTable->show();
    mCalTable->setFocus();
    return;
}

void Pm_Dialog_ZeroSetup::on_calDestroyed()
{
    mCalTable = NULL;
    this->setFocus();
    return;
}

void Pm_Dialog_ZeroSetup::initDisplay()
{
    if(POWER_SENSOR_V90 == PmInterfaceObj->getPowerSensorFlg())
    {
        ui->pb_calFactor->show();
    }
    else  if(POWER_SENSOR_V91 == PmInterfaceObj->getPowerSensorFlg())
    {
        ui->pb_calFactor->hide();
    }
    refreshButtonDisplay();
    return;
}

/**
* @brief  Initialize map of indexes and controls.
* @param  void
* @author Roc
* @since  2019.11.5
*/
void Pm_Dialog_ZeroSetup::initMap()
{
    return ;
}

/**
* @brief  Refresh the corresponding line edit according to the index.
* @param  index  The index of current editline.
* @author Roc
* @since  2019.11.4
*/
void Pm_Dialog_ZeroSetup::refreshEditDisplay(quint32 index)
{
    QString strGab;
    qreal   value;
    if(!mEditList.contains(index))
        return;
    switch (index)
    {
    default:
        break;
    }
    mEditList.find(index).value()->setText(strGab);
    return ;
}

/**
* @brief  Refresh button status.
* @param  void
* @author Roc
* @since  2019.11.4
*/
void Pm_Dialog_ZeroSetup::refreshButtonDisplay()
{
    return ;
}

/**
* @brief  show digit input dialog
* @param  void
* @author Roc
* @since  2019.11.5
*/
void Pm_Dialog_ZeroSetup::showInputDialog(qint32 index)
{
    mSelectInputID = index;
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
}
