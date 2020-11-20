#include "pm_dialog_averagesetup.h"
#include "ui_pm_dialog_averagesetup.h"
#include <QDebug>

Pm_Dialog_AverageSetup::Pm_Dialog_AverageSetup(BitPm_Interface *BitPmInterface, Pm_Dialog_Digitinput *mInput, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pm_Dialog_AverageSetup),
    PmInterfaceObj(BitPmInterface),
    mInputDialog(mInput),
    mSelectInputID(PM_INPUT_RUNNING_AVERAGE),
    mUpDownFlag(0),
    m_UpFlg(0),
    m_DownFlg(0)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint/*|Qt::Dialog*/);

    this->hide();
    initMap();
    initDisplay();
    connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(finishEntry_average(qint32)));
    connect(mInputDialog,SIGNAL(ClockWiseDown(QKeyEvent*)),this,SLOT(DigitalKeyRespond(QKeyEvent*)));
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(on_timeOut()));
    setProperty("status",pm_qssMode[PmInterfaceObj->getSystemDisplay()]);
}

Pm_Dialog_AverageSetup::~Pm_Dialog_AverageSetup()
{
    delete ui;
    if(mInputDialog)
    {
        mInputDialog = NULL;
    }
}

void Pm_Dialog_AverageSetup::keyPressEvent(QKeyEvent *event)
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
    //    qint32 FreqUnit = mInputDialog->getUnitNo();
    //    qreal tempStepFreq = (PmInterfaceObj->getSpan() / (PM_NUM_SWEEP_POINT - 1));
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
    }
    return;
}


/**
* @brief  Slot of finish entry.
* @param  void
* @author Roc
* @since  2019.11.4
*/
void Pm_Dialog_AverageSetup::finishEntry_average(qint32 index)
{
    if(this->isHidden())
        return ;
    if(mEditList.contains(index))
    {
        refreshEditDisplay(PM_INPUT_RUNNING_AVERAGE);
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
    return ;
}

void Pm_Dialog_AverageSetup::on_pb_cancel_clicked()
{
    mInputDialog->close();
    this->close();
    return;
}

void Pm_Dialog_AverageSetup::DigitalKeyRespond(QKeyEvent *event)
{
    keyPressEvent(event);
    return;
}

/**
* @brief
* @param
* @author Roc
* @since  2019.11.4
*/
void Pm_Dialog_AverageSetup::on_timeOut()
{
    qint32 nDataUserFlg = 0;
    timer->stop();
    if(!mInputDialog->isHidden())
    {
        mInputDialog->hide();
    }
    if(!mUpDownFlag)
    {
        if(m_UpFlg >20)
            nDataUserFlg = 100;
        else if(m_UpFlg >10)
            nDataUserFlg = 10;
        else
            nDataUserFlg = 1;
        m_UpFlg++;
        m_DownFlg= 0;
        switch (mSelectInputID)
        {
        case PM_INPUT_RUNNING_AVERAGE:
            PmInterfaceObj->setAveragePoint(PmInterfaceObj->getAveragePoint() + nDataUserFlg);
            initDisplay();
            break;
        default:
            break;
        }
    }
    else
    {
        if(m_DownFlg >20)
            nDataUserFlg = 100;
        else if(m_DownFlg >10)
            nDataUserFlg = 10;
        else
            nDataUserFlg = 1;
        m_UpFlg= 0;
        m_DownFlg ++;
        switch (mSelectInputID)
        {
        case PM_INPUT_RUNNING_AVERAGE:
            PmInterfaceObj->setAveragePoint(PmInterfaceObj->getAveragePoint() - nDataUserFlg);
            initDisplay();
            break;
        default:
            break;
        }
    }
    return;
}

void Pm_Dialog_AverageSetup::on_pb_Fast_clicked()
{
    PmInterfaceObj->setAverageAcq(PM_AVERAGE_FAST);
    return;
}

void Pm_Dialog_AverageSetup::on_pb_Med_clicked()
{
    PmInterfaceObj->setAverageAcq(PM_AVERAGE_MED);
    return;
}

void Pm_Dialog_AverageSetup::on_pb_Slow_clicked()
{
    PmInterfaceObj->setAverageAcq(PM_AVERAGE_SLOW);
    return;
}

void Pm_Dialog_AverageSetup::on_leAveragePoint_clicked()
{

    showInputDialog(PM_INPUT_RUNNING_AVERAGE);
    return;
}


void Pm_Dialog_AverageSetup::on_pb_MaxHold_toggled(bool checked)
{
    if(checked)
    {
        ui->pb_MaxHold->setText("On");
    }
    else
    {
        ui->pb_MaxHold->setText("Off");
    }
    PmInterfaceObj->setMaxHold(checked);

    return;
}

void Pm_Dialog_AverageSetup::on_pb_RunningAverage_toggled(bool checked)
{

    if(checked)
    {
        ui->pb_RunningAverage->setText("On");
        ui->leAveragePoint->show();
        ui->labelPoint->show();

    }
    else
    {
        ui->pb_RunningAverage->setText("Off");
        ui->leAveragePoint->hide();
        ui->labelPoint->hide();

    }
    PmInterfaceObj->setRunningAverage(checked);

}

/**
* @brief  Init the display of frequency setup dialog.
* @param  void
* @author Roc
* @since  2019.11.4
*/
void Pm_Dialog_AverageSetup::initDisplay()
{
    refreshEditDisplay(PM_INPUT_RUNNING_AVERAGE);
    refreshButtonDisplay();
    return ;
}

/**
* @brief  Initialize map of indexes and controls.
* @param  void
* @author Roc
* @since  2019.11.4
*/
void Pm_Dialog_AverageSetup::initMap()
{
    mEditList.insert(PM_INPUT_RUNNING_AVERAGE,ui->leAveragePoint);
    return ;
}

/**
* @brief  show digit input dialog
* @param  void
* @author Roc
* @since  2019.11.4
*/
void Pm_Dialog_AverageSetup::showInputDialog(qint32 index)
{
    m_UpFlg= 0;
    m_DownFlg=0;
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
    return ;
}


/**
* @brief  Refresh the corresponding line edit according to the index.
* @param  index  The index of current editline.
* @author Roc
* @since  2019.11.4
*/
void Pm_Dialog_AverageSetup::refreshEditDisplay(quint32 index)
{
    QString strGab;
    quint32   value;
    if(!mEditList.contains(index))
        return;
    switch (index)
    {
    case PM_INPUT_RUNNING_AVERAGE:
        value = PmInterfaceObj->getAveragePoint();
        strGab =  QString::number(value);
        break;
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
void Pm_Dialog_AverageSetup::refreshButtonDisplay()
{
    bool isMaxHold = PmInterfaceObj->IsMaxHold();
    if(isMaxHold)
    {
        ui->pb_MaxHold->setChecked(true);
        ui->pb_MaxHold->setText("On");
    }
    else
    {
        ui->pb_MaxHold->setChecked(false);
        ui->pb_MaxHold->setText("Off");
    }
    bool isRunning = PmInterfaceObj->IsRunningAverage();
    if(isRunning)
    {
        ui->pb_RunningAverage->setChecked(true);
        ui->pb_RunningAverage->setText("On");

        ui->leAveragePoint->show();
        ui->labelPoint->show();

    }
    else
    {
        ui->pb_RunningAverage->setChecked(false);
        ui->pb_RunningAverage->setText("Off");
        ui->leAveragePoint->hide();
        ui->labelPoint->hide();
    }

    qint32 nAcquisition = PmInterfaceObj->IsAcqType();
    switch (nAcquisition) {
    case PM_AVERAGE_FAST:
        ui->pb_Fast->setChecked(true);
        ui->pb_Med->setChecked(false);
        ui->pb_Slow->setChecked(false);
        break;
    case PM_AVERAGE_MED:
        ui->pb_Fast->setChecked(false);
        ui->pb_Med->setChecked(true);
        ui->pb_Slow->setChecked(false);
        break;
    case PM_AVERAGE_SLOW:
        ui->pb_Fast->setChecked(false);
        ui->pb_Med->setChecked(false);
        ui->pb_Slow->setChecked(true);
        break;
    default:
        break;
    }
    return ;
}
