#include "pm_dialog_sweepsetup.h"
#include "ui_pm_dialog_sweepsetup.h"
#include "pm_define.h"

Pm_Dialog_SweepSetup::Pm_Dialog_SweepSetup(BitPm_Interface *BitPmInterface , Pm_Dialog_Digitinput *input, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pm_Dialog_SweepSetup),
    PmInterfaceObj(BitPmInterface),
    mInputDialog(input),
    mSelectInputID(PM_INPUT_TIME_INTERVAL),
    mUpDownFlag(0),
    m_UpFlg(0),
    m_DownFlg(0)
{
    ui->setupUi(this);
    connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(finishEntry_sweep(qint32)));
    connect(mInputDialog,SIGNAL(ClockWiseDown(QKeyEvent*)),this,SLOT(DigitalKeyRespond(QKeyEvent*)));

    initMap();
    initDisplay();

    this->hide();
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(on_timeOut()));
    setProperty("status",pm_qssMode[PmInterfaceObj->getSystemDisplay()]);

}

Pm_Dialog_SweepSetup::~Pm_Dialog_SweepSetup()
{
    delete ui;
}

void Pm_Dialog_SweepSetup::keyPressEvent(QKeyEvent *event)
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

void Pm_Dialog_SweepSetup::finishEntry_sweep(qint32 index)
{
    if(this->isHidden())
        return ;
    if(mEditList.contains(index))
        initDisplay();
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

void Pm_Dialog_SweepSetup::on_pb_cancel_clicked()
{
    mInputDialog->hide();
    this->close();
    return;
}

void Pm_Dialog_SweepSetup::DigitalKeyRespond(QKeyEvent *event)
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
void Pm_Dialog_SweepSetup::on_timeOut()
{
    qreal fDataUserFlg = 0;
    qint32 nDataUserFlg = 0;
    timer->stop();
    if(!mInputDialog->isHidden())
    {
        mInputDialog->hide();
    }
    if(!mUpDownFlag)
    {
        if(m_UpFlg >30)
        {
            nDataUserFlg = 100;
            fDataUserFlg = 10.0;
        }
        else if(m_UpFlg >20)
        {
            nDataUserFlg = 100;
            fDataUserFlg = 1.0;
        }
        else if(m_UpFlg >10)
        {
            nDataUserFlg = 10;
            fDataUserFlg = 0.1;
        }
        else
        {
            nDataUserFlg = 1;
            fDataUserFlg = 0.01;
        }
        switch (mSelectInputID)
        {
        case PM_INPUT_TIME_INTERVAL:
            PmInterfaceObj->setSweepTime(PmInterfaceObj->getSweepTime() + nDataUserFlg);
            initDisplay();
            break;
        case PM_INPUT_DUTY_CYCLE:
            PmInterfaceObj->setDutyCycle(PmInterfaceObj->getDutyCycle() + fDataUserFlg);
            break;
        case PM_INPUT_MEASURE_OFFSET:
            PmInterfaceObj->setMeasureOffset(PmInterfaceObj->getMeasureOffset() + fDataUserFlg);
            initDisplay();
            break;
        default:
            break;
        }
        m_UpFlg++;
        m_DownFlg= 0;
    }
    else
    {
        if(m_DownFlg >30)
        {
            nDataUserFlg = 100;
            fDataUserFlg = 10.0;
        }
        else if(m_DownFlg >20)
        {
            nDataUserFlg = 100;
            fDataUserFlg = 1.0;
        }
        else if(m_DownFlg >10)
        {
            nDataUserFlg = 10;
            fDataUserFlg = 0.1;
        }
        else
        {
            nDataUserFlg = 1;
            fDataUserFlg = 0.01;
        }
        switch (mSelectInputID)
        {
        case PM_INPUT_TIME_INTERVAL:
            PmInterfaceObj->setSweepTime(PmInterfaceObj->getSweepTime() - nDataUserFlg);
            initDisplay();
            break;
        case PM_INPUT_DUTY_CYCLE:
            PmInterfaceObj->setDutyCycle(PmInterfaceObj->getDutyCycle() - fDataUserFlg);
            break;
        case PM_INPUT_MEASURE_OFFSET:
            PmInterfaceObj->setMeasureOffset(PmInterfaceObj->getMeasureOffset() - fDataUserFlg);
            initDisplay();
            break;
        default:
            break;
        }
        m_UpFlg= 0;
        m_DownFlg ++;
    }

    return;
}

void Pm_Dialog_SweepSetup::on_pb_conti_clicked()
{
    PmInterfaceObj->setSweepContinous(PM_CONT);
    refreshButtonDisplay();
    return;
}

void Pm_Dialog_SweepSetup::on_pb_single_clicked()
{
    PmInterfaceObj->setSweepContinous(PM_SINGLE);
    refreshButtonDisplay();
    return;
}

void Pm_Dialog_SweepSetup::on_LedTimeInterval_clicked()
{
  showInputDialog(PM_INPUT_TIME_INTERVAL);
  return;
}


void Pm_Dialog_SweepSetup::on_ledDutyCycle_clicked()
{
        showInputDialog(PM_INPUT_DUTY_CYCLE);
        return ;
}

//PM_INPUT_MEASURE_MODLE
void Pm_Dialog_SweepSetup::on_LedMeasureOffset_clicked()
{
    showInputDialog(PM_INPUT_MEASURE_OFFSET);
    return;
}

void Pm_Dialog_SweepSetup::initDisplay()
{
    refreshEditDisplay(PM_INPUT_TIME_INTERVAL);
    refreshEditDisplay(PM_INPUT_DUTY_CYCLE);
    refreshEditDisplay(PM_INPUT_MEASURE_OFFSET);
}
void Pm_Dialog_SweepSetup::initMap()
{
    mEditList.insert(PM_INPUT_TIME_INTERVAL,ui->LedTimeInterval);
    mEditList.insert(PM_INPUT_DUTY_CYCLE,ui->ledDutyCycle);
    mEditList.insert(PM_INPUT_MEASURE_OFFSET,ui->LedMeasureOffset);
    return;
}

void Pm_Dialog_SweepSetup::refreshEditDisplay(quint32 index)
{
    QString strGab;
    qreal   fValue;
    qint32  nValue;
    if(!mEditList.contains(index))
        return;
    switch (index)
    {
    case PM_INPUT_TIME_INTERVAL:
        nValue = PmInterfaceObj->getSweepTime();
        strGab = QString::number(nValue) + QString(" s");
        break;
    case PM_INPUT_DUTY_CYCLE:
        fValue = PmInterfaceObj->getDutyCycle();
        strGab.sprintf("%.2f %%",fValue);
        break;
    case PM_INPUT_MEASURE_OFFSET:
        fValue = PmInterfaceObj->getMeasureOffset();
        strGab.sprintf("%.2f dB",fValue);
        break;
   }
    mEditList.find(index).value()->setText(strGab);

    refreshButtonDisplay();
    return ;
}
void Pm_Dialog_SweepSetup::showInputDialog(qint32 index)
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
    if(mInputDialog->isHidden())
        mInputDialog->show();
    return;
}
void Pm_Dialog_SweepSetup::refreshButtonDisplay()
{
    if(PM_SINGLE == PmInterfaceObj->IsSweepContinous())
    {
        ui->pb_single->setChecked(true);
        ui->pb_conti->setChecked(false);
        ui->labelTime->hide();
        ui->LedTimeInterval->hide();
    }
    else
    {
        ui->pb_single->setChecked(false);
        ui->pb_conti->setChecked(true);
        ui->labelTime->show();
        ui->LedTimeInterval->show();
    }

    if(POWER_SENSOR_V90 == PmInterfaceObj->getPowerSensorFlg())
    {
        ui->labelMeasureOffset->hide();
        ui->LedMeasureOffset->hide();
    }
    else  if(POWER_SENSOR_V91 == PmInterfaceObj->getPowerSensorFlg())
    {
        ui->labelMeasureOffset->show();
        ui->LedMeasureOffset->show();
    }
    return;
}

