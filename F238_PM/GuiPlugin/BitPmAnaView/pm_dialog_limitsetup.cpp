#include "pm_dialog_limitsetup.h"
#include "ui_pm_dialog_limitsetup.h"
#include "pm_define.h"

Pm_Dialog_Limit::Pm_Dialog_Limit(BitPm_Interface *BitPmInterface, Pm_Dialog_Digitinput *input, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pm_Dialog_Limit),
    PmInterfaceObj(BitPmInterface),
    mInputDialog(input),
    mSelectInputID(PM_INPUT_FORWARD_UPPER),
    mUpDownFlag(0),
    m_UpFlg(0),
    m_DownFlg(0)
{
    ui->setupUi(this);
    this->hide();

    initMap();
    initDisplay();

    connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(finishEntry_Limit(qint32)));
    connect(mInputDialog,SIGNAL(ClockWiseDown(QKeyEvent*)),this,SLOT(DigitalKeyRespond(QKeyEvent*)));

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(on_timeOut()));
    setProperty("status",pm_qssMode[PmInterfaceObj->getSystemDisplay()]);
}

Pm_Dialog_Limit::~Pm_Dialog_Limit()
{

    delete ui;
}

void Pm_Dialog_Limit::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_PowerOff)
    {
        if(!event->isAutoRepeat())
        {
            QApplication::sendEvent(this->parent(),event);
        }
        return;
    }
    qint32 keyvalue = event->key();
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
//        QApplication::sendEvent(this->parent(),event);
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

void Pm_Dialog_Limit::finishEntry_Limit(qint32 index)
{
    if(index == PM_NOT_USE)
    {
        this->close();
        return;
    }
    if(index == PM_SHIFT_ENABLE)
    {
        PmInterfaceObj->setShiftKeyEnable(true);
        this->close();
        return;
    }
    refreshEditDisplay(index);
    refreshButtonDisplay();
    return;
}

void Pm_Dialog_Limit::on_pb_cancel_clicked()
{
    mInputDialog->hide();
    this->close();
    return;
}

void Pm_Dialog_Limit::DigitalKeyRespond(QKeyEvent *event)
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
void Pm_Dialog_Limit::on_timeOut()
{
    qreal fDataUserFlg = 0;
    timer->stop();
    if(!mInputDialog->isHidden())
    {
        mInputDialog->hide();
    }
    if(!mUpDownFlag)
    {
        if(m_UpFlg >30)
            fDataUserFlg = 10.0;
        else if(m_UpFlg >20)
            fDataUserFlg = 1.0;
        else if(m_UpFlg >10)
            fDataUserFlg = 0.1;
        else
            fDataUserFlg = 0.01;
        m_UpFlg++;
        m_DownFlg= 0;
        switch (mSelectInputID)
        {
        case PM_INPUT_FORWARD_UPPER:
            PmInterfaceObj->setForwardUpperLimt(PmInterfaceObj->getForwardUpperLimt() + fDataUserFlg);
            break;
        case PM_INPUT_FORWARD_LOWER:
            PmInterfaceObj->setForwardLowerLimt(PmInterfaceObj->getForwardLowerLimt() + fDataUserFlg);
            break;
        case PM_INPUT_REVERSE_UPPER:
            PmInterfaceObj->setReverseUpperLimt(PmInterfaceObj->getReverseUpperLimt() + fDataUserFlg);
            break;
        case PM_INPUT_REVERSE_LOWER:
            PmInterfaceObj->setReverseLowerLimt(PmInterfaceObj->getReverseLowerLimt() + fDataUserFlg);
            break;
        default:
            break;
        }
    }
    else
    {
        if(m_DownFlg >30)
            fDataUserFlg = 10.0;
        else if(m_DownFlg >20)
            fDataUserFlg = 1.0;
        else if(m_DownFlg >10)
            fDataUserFlg = 0.1;
        else
            fDataUserFlg = 0.01;
        m_UpFlg= 0;
        m_DownFlg ++;
        switch (mSelectInputID)
        {
        case PM_INPUT_FORWARD_UPPER:
            PmInterfaceObj->setForwardUpperLimt(PmInterfaceObj->getForwardUpperLimt() - fDataUserFlg);
            break;
        case PM_INPUT_FORWARD_LOWER:
            PmInterfaceObj->setForwardLowerLimt(PmInterfaceObj->getForwardLowerLimt() - fDataUserFlg);
            break;
        case PM_INPUT_REVERSE_UPPER:
            PmInterfaceObj->setReverseUpperLimt(PmInterfaceObj->getReverseUpperLimt() - fDataUserFlg);
            break;
        case PM_INPUT_REVERSE_LOWER:
            PmInterfaceObj->setReverseLowerLimt(PmInterfaceObj->getReverseLowerLimt() - fDataUserFlg);
            break;
        default:
            break;
        }
    }
    initDisplay();
    return;
}

void Pm_Dialog_Limit::on_pb_Limt_toggled(bool checked)
{
    if(checked)
    {
        ui->pb_Limt->setText("On");
    }
    else
    {
        ui->pb_Limt->setText("Off");
    }
    PmInterfaceObj->setLimit(checked);
    initDisplay();
    return;
}

void Pm_Dialog_Limit::on_ledForwardUp_clicked()
{
    showInputDialog(PM_INPUT_FORWARD_UPPER);
    return ;
}

void Pm_Dialog_Limit::on_ledForwardLow_clicked()
{
    showInputDialog(PM_INPUT_FORWARD_LOWER);
    return ;
}

void Pm_Dialog_Limit::on_ledReverseUp_clicked()
{

    showInputDialog(PM_INPUT_REVERSE_UPPER);
    return ;
}

void Pm_Dialog_Limit::on_ledReverseLow_clicked()
{

    showInputDialog(PM_INPUT_REVERSE_LOWER);
    return ;
}


void Pm_Dialog_Limit::on_pb_Full_clicked()
{
    mInputDialog->hide();
    PmInterfaceObj->setLimtVidoBW(PM_LIMIT_FULL);
    initDisplay();
    return;
}

void Pm_Dialog_Limit::on_pb_4k_clicked()
{
    mInputDialog->hide();
    PmInterfaceObj->setLimtVidoBW(PM_LIMIT_4K);
    initDisplay();
    return;
}

void Pm_Dialog_Limit::on_pb_200k_clicked()
{
    mInputDialog->hide();
    PmInterfaceObj->setLimtVidoBW(PM_LIMIT_200K);
    initDisplay();
    return;
}

void Pm_Dialog_Limit::initDisplay()
{
    if(POWER_SENSOR_V90 == PmInterfaceObj->getPowerSensorFlg())
    {
        ui->lblForwardUp->setText("Upper Limit");
        ui->lblForwardLow->setText("Lower Limit");

        ui->lblReverseUp->hide();
        ui->ledReverseUp->hide();
        ui->lblReverseLow->hide();
        ui->ledReverseLow->hide();
        ui->lblVideo->hide();
        ui->pb_Full->hide();
        ui->pb_4k->hide();
        ui->pb_200k->hide();

        if(PM_BUTTON_OFF ==PmInterfaceObj->IsLimit())
        {
            ui->lblForwardUp->hide();
            ui->ledForwardUp->hide();
            ui->lblForwardLow->hide();
            ui->ledForwardLow->hide();
        }
        else
        {
            ui->lblForwardUp->show();
            ui->ledForwardUp->show();
            ui->lblForwardLow->show();
            ui->ledForwardLow->show();
        }
    }
    else  if(POWER_SENSOR_V91 == PmInterfaceObj->getPowerSensorFlg())
    {

        ui->lblForwardUp->setText("Forward\nUpper Limit");
        ui->lblForwardLow->setText("Forward\nLower Limit");

        if(PM_BUTTON_OFF ==PmInterfaceObj->IsLimit())
        {
            ui->lblForwardUp->hide();
            ui->ledForwardUp->hide();
            ui->lblForwardLow->hide();
            ui->ledForwardLow->hide();

            ui->lblReverseUp->hide();
            ui->ledReverseUp->hide();
            ui->lblReverseLow->hide();
            ui->ledReverseLow->hide();

            ui->lblVideo->hide();
            ui->pb_Full->hide();
            ui->pb_4k->hide();
            ui->pb_200k->hide();
        }
        else
        {
            ui->lblForwardUp->show();
            ui->ledForwardUp->show();
            ui->lblForwardLow->show();
            ui->ledForwardLow->show();
            ui->lblReverseUp->show();
            ui->ledReverseUp->show();
            ui->lblReverseLow->show();
            ui->ledReverseLow->show();

            ui->lblVideo->show();
            ui->pb_Full->show();
            ui->pb_4k->show();
            ui->pb_200k->show();
        }
    }

    refreshEditDisplay(PM_INPUT_FORWARD_UPPER);
    refreshEditDisplay(PM_INPUT_FORWARD_LOWER);
    refreshEditDisplay(PM_INPUT_REVERSE_UPPER);
    refreshEditDisplay(PM_INPUT_REVERSE_LOWER);
    refreshButtonDisplay();
    return;
}

void Pm_Dialog_Limit::initMap()
{
    mEditList.insert(PM_INPUT_FORWARD_UPPER,ui->ledForwardUp);
    mEditList.insert(PM_INPUT_FORWARD_LOWER,ui->ledForwardLow);
    mEditList.insert(PM_INPUT_REVERSE_UPPER,ui->ledReverseUp);
    mEditList.insert(PM_INPUT_REVERSE_LOWER,ui->ledReverseLow);
    return;
}

void Pm_Dialog_Limit::refreshEditDisplay(quint32 index)
{
    QString strGab;
    qreal   value;
    qint32  nValue;
    if(!mEditList.contains(index))
        return;
    switch(index)
    {
    case PM_INPUT_FORWARD_UPPER:
        value = PmInterfaceObj->getForwardUpperLimt();
//        if(PmInterfaceObj->getForwardLowerLimt() < PmInterfaceObj->getAmptMax())
//        {
//            if(value < qMax(PmInterfaceObj->getForwardLowerLimt(),PmInterfaceObj->getAmptMin()))
//                value = qMax(PmInterfaceObj->getForwardLowerLimt(),PmInterfaceObj->getAmptMin());
//        }
//        else
//            value = qMax(value,PmInterfaceObj->getAmptMin());

        strGab = PmInterfaceObj->dBmTransformToQstring(PmInterfaceObj->getAmptUint(),value);
        break;
    case PM_INPUT_FORWARD_LOWER:
        value = PmInterfaceObj->getForwardLowerLimt();

//        if(PmInterfaceObj->getForwardUpperLimt() > PmInterfaceObj->getAmptMin())
//        {
//            if(value > qMin(PmInterfaceObj->getForwardUpperLimt(),PmInterfaceObj->getAmptMax()))
//                value = qMin(PmInterfaceObj->getForwardUpperLimt(),PmInterfaceObj->getAmptMax());
//        }
//        else
//            value = qMin(value,PmInterfaceObj->getAmptMax());

        strGab = PmInterfaceObj->dBmTransformToQstring(PmInterfaceObj->getAmptUint(),value);
        break;
    case PM_INPUT_REVERSE_UPPER:
        value = PmInterfaceObj->getReverseUpperLimt();

//        if(PmInterfaceObj->getReverseLowerLimt() < PmInterfaceObj->getAmptMax())
//        {
//            if(value < qMax(PmInterfaceObj->getReverseLowerLimt(),PmInterfaceObj->getAmptMin()))
//                value = qMax(PmInterfaceObj->getReverseLowerLimt(),PmInterfaceObj->getAmptMin());
//        }
//        else
//            value = qMax(value,PmInterfaceObj->getAmptMin());
        strGab = PmInterfaceObj->dBmTransformToQstring(PmInterfaceObj->getAmptUint(),value);
        break;
    case PM_INPUT_REVERSE_LOWER:
        value = PmInterfaceObj->getReverseLowerLimt();
//        if(PmInterfaceObj->getReverseUpperLimt() > PmInterfaceObj->getAmptMin())
//        {
//            if(value > qMin(PmInterfaceObj->getReverseUpperLimt(),PmInterfaceObj->getAmptMax()))
//                value = qMin(PmInterfaceObj->getReverseUpperLimt(),PmInterfaceObj->getAmptMax());
//        }
//        else
//            value = qMin(value,PmInterfaceObj->getAmptMax());
        strGab = PmInterfaceObj->dBmTransformToQstring(PmInterfaceObj->getAmptUint(),value);
        break;
    }
    mEditList.find(index).value()->setText(strGab);
    return;
}

void Pm_Dialog_Limit::refreshButtonDisplay()
{
    if(PmInterfaceObj->IsLimit())
    {
        ui->pb_Limt->setChecked(true);
        ui->pb_Limt->setText("On");

    }
    else
    {
        ui->pb_Limt->setChecked(false);
        ui->pb_Limt->setText("Off");
}
    return;
}
void Pm_Dialog_Limit::showInputDialog(qint32 index)
{
    m_UpFlg = 0;
    m_DownFlg = 0;
    mSelectInputID = index;
    if(mInputDialog->isHidden())
    {
        mInputDialog->setGeometry(mapToGlobal(QPoint(0,0)).x()/*+this->width()*//*-PM_DIGITAL_DIALOG_WIDTH*/,\
                                  mapToGlobal(QPoint(0,0)).y(),PM_DIGITAL_DIALOG_WIDTH,PM_DIGITAL_DIALOG_HEIGHT);
    }
    mInputDialog->initDisplay(index);
    mInputDialog->setProperty("status", pm_qssMode[PmInterfaceObj->getSystemDisplay()]);
    mInputDialog->setStyle(QApplication::style());
    mInputDialog->show();
    return ;
}

