#include "pm_dialog_displaysetup.h"
#include "ui_pm_dialog_displaysetup.h"

Pm_Dialog_DisplaySetup::Pm_Dialog_DisplaySetup(BitPm_Interface *BitPmInterface,Pm_Dialog_Digitinput *input,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pm_Dialog_DisplaySetup),
    PmInterfaceObj(BitPmInterface),
    mInputDialog(input),
    //    mSelectInputID(PM_INPUT_PERSISTENCE_TIME),
    mUpDownFlag(0)
{
    ui->setupUi(this);
    this->hide();

    initMap();
    initDisplay();

    connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(finishEntry_Display(qint32)));
    connect(PmInterfaceObj,SIGNAL(finishCmd()),this,SLOT(finishCmd_Display()));
    connect(mInputDialog,SIGNAL(ClockWiseDown(QKeyEvent*)),this,SLOT(DigitalKeyRespond(QKeyEvent*)));

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(on_timeOut()));
    setProperty("status",pm_qssMode[PmInterfaceObj->getSystemDisplay()]);
}

Pm_Dialog_DisplaySetup::~Pm_Dialog_DisplaySetup()
{
    delete ui;
}

void Pm_Dialog_DisplaySetup::keyPressEvent(QKeyEvent *event)
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
    //    qint32 Units = mInputDialog->getUnitNo();
    //    qreal tempTime = PmInterfaceObj->getPersistenceTime();
    switch (keyvalue) {
    case Qt::Key_Escape:
        if(!mInputDialog->isHidden())
        {
            mInputDialog->hide();
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
    case Qt::Key_F2:    //  +/-
    case Qt::Key_F6://key_left
    case Qt::Key_Right:
    case Qt::Key_F7:
        if(mInputDialog->isHidden())
        {
            showInputDialog(mSelectInputID);
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
    default:
        break;
    }
    return;
}


void Pm_Dialog_DisplaySetup::finishEntry_Display(qint32 index)
{
    if(this->isHidden())
        return ;
    if(mEditList.contains(index))
        refreshButtonDisplay();

    if(index == PM_NOT_USE)
    {
        this->close();
    }
    if(index == PM_SHIFT_ENABLE)
    {
        PmInterfaceObj->setShiftKeyEnable(true);
        this->close();
    }
    return ;
}
void Pm_Dialog_DisplaySetup::finishCmd_Display()
{
    if(this->isHidden())
        return ;

    refreshEditDisplay(PM_INPUT_SENSOR_MODLE);
    refreshEditDisplay(PM_INPUT_SENSOR_SN);
    refreshEditDisplay(PM_INPUT_SENSOR_FW);
    refreshEditDisplay(PM_INPUT_SENSOR_TYPE);
//    if(mEditList.contains(index))
//        refreshButtonDisplay();

//    if(index == PM_NOT_USE)
//    {
//        this->close();
//    }
//    if(index == PM_SHIFT_ENABLE)
//    {
//        PmInterfaceObj->setShiftKeyEnable(true);
//        this->close();
//    }
    return ;
}

void Pm_Dialog_DisplaySetup::on_pb_cancel_clicked()
{
    this->close();
    return;
}

void Pm_Dialog_DisplaySetup::DigitalKeyRespond(QKeyEvent *event)
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
void Pm_Dialog_DisplaySetup::on_timeOut()
{
    timer->stop();

    if(!mInputDialog->isHidden())
    {
        mInputDialog->hide();
    }
    if(!mUpDownFlag)
    {
        ;
    }
    else
    {
    }
    return;
}

void Pm_Dialog_DisplaySetup::on_pb_sensorType_activated(int index)
{
    PmInterfaceObj->setPowerSensorFlg(index);
    refreshButtonDisplay();
}

void Pm_Dialog_DisplaySetup::on_pb_fowardDisplay_activated(int index)
{
    PmInterfaceObj->setForwardDisplay(index);
    refreshButtonDisplay();
}

void Pm_Dialog_DisplaySetup::on_pb_reverseDisplay_activated(int index)
{
    PmInterfaceObj->setReverseDisplay(index);
    refreshButtonDisplay();
}

void Pm_Dialog_DisplaySetup::on_pb_summary_clicked()
{
    PmInterfaceObj->setSummaryDisplay();
    refreshButtonDisplay();
}

void Pm_Dialog_DisplaySetup::initDisplay()
{
    refreshEditDisplay(PM_INPUT_SENSOR_MODLE);
    refreshEditDisplay(PM_INPUT_SENSOR_SN);
    refreshEditDisplay(PM_INPUT_SENSOR_FW);
    refreshEditDisplay(PM_INPUT_SENSOR_TYPE);
    refreshButtonDisplay();
    return;
}

void Pm_Dialog_DisplaySetup::initMap()
{
    mEditList.insert(PM_INPUT_SENSOR_MODLE,ui->leSensorModle);
    mEditList.insert(PM_INPUT_SENSOR_SN,ui->leSensorSN);
    mEditList.insert(PM_INPUT_SENSOR_FW,ui->leSensorFW);
    mEditList.insert(PM_INPUT_SENSOR_TYPE,ui->leSensorType);
    return;
}

void Pm_Dialog_DisplaySetup::refreshEditDisplay(quint32 index)
{
    QString strGab;
    quint32   value;
    if(!mEditList.contains(index))
        return;
    switch (index)
    {
    case PM_INPUT_SENSOR_MODLE:
        strGab = PmInterfaceObj->getSensorModle();
        break;
    case PM_INPUT_SENSOR_SN:
        strGab = PmInterfaceObj->getSensorSN();
        break;
    case PM_INPUT_SENSOR_FW:
        strGab = PmInterfaceObj->getSensorFW();
        break;
    case PM_INPUT_SENSOR_TYPE:
        strGab = PmInterfaceObj->getSensorType();
        break;
    default:
        break;
    }
    mEditList.find(index).value()->setText(strGab);
    return ;
}

void Pm_Dialog_DisplaySetup::refreshButtonDisplay()
{
    if(POWER_SENSOR_V90 == PmInterfaceObj->getPowerSensorFlg())
    {
        ui->labelForward->hide();
        ui->labelReverse->hide();
        ui->pb_fowardDisplay->hide();
        ui->pb_reverseDisplay->hide();
        ui->pb_summary->hide();
    }
    else if(POWER_SENSOR_V91 == PmInterfaceObj->getPowerSensorFlg())
    {
        ui->labelForward->show();
        ui->labelReverse->show();
        ui->pb_fowardDisplay->show();
        ui->pb_reverseDisplay->show();
        ui->pb_summary->show();

        if(PM_DISPLAY_SUMMARY == PmInterfaceObj->getDisplayMode())
        {
            ui->pb_fowardDisplay->setCurrentIndex(-1);
            ui->pb_reverseDisplay->setCurrentIndex(-1);
        }
        else
        {
            ui->pb_fowardDisplay->setCurrentIndex(PmInterfaceObj->getForwardDisplay());
            ui->pb_reverseDisplay->setCurrentIndex(PmInterfaceObj->getReverseDisplay());
        }
    }
    ui->pb_sensorType->setCurrentIndex(PmInterfaceObj->getPowerSensorFlg());
    return;
}

void Pm_Dialog_DisplaySetup::showInputDialog(qint32 index)
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
    return;
}
