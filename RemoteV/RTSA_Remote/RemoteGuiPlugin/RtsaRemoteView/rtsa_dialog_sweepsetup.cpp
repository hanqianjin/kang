#include "rtsa_dialog_sweepsetup.h"
#include "ui_rtsa_dialog_sweepsetup.h"
#include "rtsa_define.h"

RtSa_Dialog_SweepSetup::RtSa_Dialog_SweepSetup(Rtsa_Remote_Interface *RtsaRemoteInterface , RtSa_Dialog_Digitinput *input, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RtSa_Dialog_SweepSetup),
    RemoteInterfaceObj(RtsaRemoteInterface),
    mInputDialog(input),
    mSelectInputID(RTSA_INPUT_PERSISTENCE_TIME),
    mUpDownFlag(0)
{
    ui->setupUi(this);
    initMap();
    connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(finishEntry_Display(qint32)));
    connect(mInputDialog,SIGNAL(ClockWiseDown(QKeyEvent*)),this,SLOT(DigitalKeyRespond(QKeyEvent*)));
//    this->setAttribute(Qt::WA_NoChildEventsForParent,true);
//    this->setAttribute(Qt::WA_DeleteOnClose);
    this->hide();
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(on_timeOut()));
    setProperty("status",rtsa_qssMode[RemoteInterfaceObj->GetDisplayMode()]);

//    QString button_style= "QPushButton:pressed{background-image: url(:/rtsa/image/fre_checked_right.png);background-position:right;}"
//            "QPushButton:!pressed{background-image: url(:/rtsa/image/fre_checked_left.png);background-position:right;}";
//    ui->pb_single->setStyleSheet(button_style);

}

RtSa_Dialog_SweepSetup::~RtSa_Dialog_SweepSetup()
{
    delete ui;
}
void RtSa_Dialog_SweepSetup::initDisplay()
{
    refreshButtonDisplay();
    initButtonDisplay();
    return;
}
void RtSa_Dialog_SweepSetup::initMap()
{
    mEditList.insert(RTSA_INPUT_PERSISTENCE_TIME,ui->edit_time);
    mEditList.insert(RTSA_INPUT_HIGHEST_DENSITY,ui->edit_highest);
    mEditList.insert(RTSA_INPUT_LOWEST_DENSITY,ui->edit_lowest);
    mEditList.insert(RTSA_INPUT_CURVE,ui->edit_curve);
    mEditList.insert(RTSA_INPUT_ACQ_TIME,ui->leAcqtime);
    refreshButtonDisplay();
    initButtonDisplay();
    return;
}
void RtSa_Dialog_SweepSetup::refreshEditDisplay(quint32 index)
{
    QString strGab;
    qreal   value;
    if(!mEditList.contains(index))
        return;
    switch (index)
    {
    case RTSA_INPUT_PERSISTENCE_TIME:
        value = RemoteInterfaceObj->getPersistenceTime();
        strGab = RemoteInterfaceObj->getAdjustTimeStr(value);
        break;
    case RTSA_INPUT_HIGHEST_DENSITY:
        value = RemoteInterfaceObj->getHighestDensity();
        strGab = QString::number(value) + QString(" %");
        break;
    case RTSA_INPUT_LOWEST_DENSITY:
        value = RemoteInterfaceObj->getLowestDensity();
        strGab = QString::number(value) + QString(" %");
        break;
    case RTSA_INPUT_CURVE:
        value = RemoteInterfaceObj->getCurve();
        strGab = QString::number(value) + QString(" %");
        break;
    case RTSA_INPUT_ACQ_TIME:
        value = RemoteInterfaceObj->getAcqTime();
        strGab = RemoteInterfaceObj->getAdjustTimeStr(value);
        if(RemoteInterfaceObj->IsAcqTimeAuto())
        {
            ui->pbAcqAuto->setChecked(true);
            ui->pbAcqMan->setChecked(false);
        }
        else
        {
            ui->pbAcqAuto->setChecked(false);
            ui->pbAcqMan->setChecked(true);
        }
        break;
    default:
        break;
    }
    mEditList.find(index).value()->setText(strGab);
    return;
}
void RtSa_Dialog_SweepSetup::refreshButtonDisplay()
{
    refreshEditDisplay(RTSA_INPUT_PERSISTENCE_TIME);
    refreshEditDisplay(RTSA_INPUT_HIGHEST_DENSITY);
    refreshEditDisplay(RTSA_INPUT_LOWEST_DENSITY);
    refreshEditDisplay(RTSA_INPUT_CURVE);
    refreshEditDisplay(RTSA_INPUT_ACQ_TIME);
    return;
}
void RtSa_Dialog_SweepSetup::showInputDialog(qint32 index)
{
    mSelectInputID = index;
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
    return;
}
void RtSa_Dialog_SweepSetup::initButtonDisplay()
{
    if(RemoteInterfaceObj->IsPersistenceTimeInfinite())
    {
        ui->pb_Finite->setChecked(true);
        ui->pb_Infinite->setChecked(false);
    }
    else
    {
        ui->pb_Finite->setChecked(false);
        ui->pb_Infinite->setChecked(true);
    }
    if(RemoteInterfaceObj->getDisplay() == RTSA_SPECTRUM)
    {
//        ui->pb_Spectrum->setChecked(true);
//        ui->pb_Spectrogram->setChecked(false);
    }
    else if(RemoteInterfaceObj->getDisplay() == RTSA_SPECTROGRAM)
    {
//        ui->pb_Spectrum->setChecked(false);
//        ui->pb_Spectrogram->setChecked(true);
    }
    else
    {

    }
    if(RemoteInterfaceObj->IsSingleSweep())
    {
        ui->pb_single->setChecked(true);
        ui->pb_conti->setChecked(false);
    }
    else
    {
        ui->pb_single->setChecked(false);
        ui->pb_conti->setChecked(true);
    }
    return;
}
void RtSa_Dialog_SweepSetup::keyPressEvent(QKeyEvent *event)
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
//    qreal tempTime = RemoteInterfaceObj->getPersistenceTime();
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
        RemoteInterfaceObj->setShiftKeyEnable(true);
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
void RtSa_Dialog_SweepSetup::on_pb_conti_clicked()
{
    if(!RemoteInterfaceObj->IsSingleSweep())
    {
        ui->pb_conti->setChecked(true);
//        return;
    }
    RemoteInterfaceObj->setSingleSweep(RTSA_CONT);
    ui->pb_single->setChecked(RemoteInterfaceObj->IsSingleSweep());
    return;
}

void RtSa_Dialog_SweepSetup::on_pb_single_clicked()
{
    RemoteInterfaceObj->setSingleSweep(RTSA_SINGLE);
    ui->pb_conti->setChecked(!RemoteInterfaceObj->IsSingleSweep());
    ui->pb_single->setChecked(true);
    return;
}

//void RtSa_Dialog_SweepSetup::on_pb_Spectrum_clicked()
//{
//    if(mControl->getDisplay() == RTSA_SPECTRUM)
//    {
//        ui->pb_Spectrum->setChecked(true);
//        return;
//    }
//    mControl->setDisplay(RTSA_SPECTRUM);
//    ui->pb_Spectrogram->setChecked(false);
//    return;
//}


//void RtSa_Dialog_SweepSetup::on_pb_Spectrogram_clicked()
//{
//    if(mControl->getDisplay() == RTSA_SPECTROGRAM)
//    {
//        ui->pb_Spectrogram->setChecked(true);
//        return;
//    }
//    mControl->setDisplay(RTSA_SPECTROGRAM);
//    ui->pb_Spectrum->setChecked(false);
//    return;
//}

void RtSa_Dialog_SweepSetup::on_pb_Infinite_clicked()
{
//    if(mControl->IsPersistenceTimeInfinite())
//    {
//        return;
//    }
    RemoteInterfaceObj->setPersistenceTimeInfinite(RTSA_INFINITE);
    return;
}
void RtSa_Dialog_SweepSetup::finishEntry_Display(qint32 index)
{
    if(this->isHidden())
        return ;
    if(mEditList.contains(index))
        refreshButtonDisplay();
    initButtonDisplay();
    if(index == RTSA_NOT_USE)
    {
        this->close();
    }
    if(index == RTSA_SHIFT_ENABLE)
    {
        RemoteInterfaceObj->setShiftKeyEnable(true);
        this->close();
    }
    return ;
}

void RtSa_Dialog_SweepSetup::on_pb_cancel_clicked()
{
    mInputDialog->hide();
    this->close();
    return;
}

void RtSa_Dialog_SweepSetup::on_pb_Auto_Density_clicked()
{
    RemoteInterfaceObj->setDensityLevelAjust();
    refreshButtonDisplay();
    return;
}


void RtSa_Dialog_SweepSetup::on_edit_time_clicked()
{
    showInputDialog(RTSA_INPUT_PERSISTENCE_TIME);
    return;
}

void RtSa_Dialog_SweepSetup::on_edit_highest_clicked()
{
    showInputDialog(RTSA_INPUT_HIGHEST_DENSITY);
    return;
}

void RtSa_Dialog_SweepSetup::on_edit_lowest_clicked()
{
    showInputDialog(RTSA_INPUT_LOWEST_DENSITY);
    return;
}

void RtSa_Dialog_SweepSetup::on_edit_curve_clicked()
{
    showInputDialog(RTSA_INPUT_CURVE);
    return;
}

void RtSa_Dialog_SweepSetup::on_pb_Finite_clicked()
{
//    if(!mControl->IsPersistenceTimeInfinite())
//    {
//        return;
//    }
    RemoteInterfaceObj->setPersistenceTimeInfinite(RTSA_FINITE);
    return;
}

void RtSa_Dialog_SweepSetup::DigitalKeyRespond(QKeyEvent *event)
{
    keyPressEvent(event);
    return;
}

void RtSa_Dialog_SweepSetup::on_pb_Sweep_Once_clicked()
{
    RemoteInterfaceObj->setSingleSweep(true);
    ui->pb_single->setChecked(true);
    ui->pb_conti->setChecked(false);
    return;
}

void RtSa_Dialog_SweepSetup::on_leAcqtime_clicked()
{
    showInputDialog(RTSA_INPUT_ACQ_TIME);
    return;
}

void RtSa_Dialog_SweepSetup::on_pbAcqAuto_clicked()
{
    RemoteInterfaceObj->setAcqTimeAuto(true);
    ui->pbAcqAuto->setChecked(true);
    ui->pbAcqMan->setChecked(false);
    refreshEditDisplay(RTSA_INPUT_ACQ_TIME);
    return;
}

void RtSa_Dialog_SweepSetup::on_pbAcqMan_clicked()
{
    RemoteInterfaceObj->setAcqTimeAuto(false);
    ui->pbAcqAuto->setChecked(false);
    ui->pbAcqMan->setChecked(true);
    refreshEditDisplay(RTSA_INPUT_ACQ_TIME);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-07-30
*/
void RtSa_Dialog_SweepSetup::on_timeOut()
{
    timer->stop();
    if(!mInputDialog->isHidden())
    {
        mInputDialog->hide();
    }
    if(!mUpDownFlag)
    {
        switch (mSelectInputID)
        {
        case RTSA_INPUT_ACQ_TIME:
            if(RemoteInterfaceObj->getAcqTime() >= RTSA_S)
            {
                RemoteInterfaceObj->setAcqTime(RemoteInterfaceObj->getAcqTime() + RTSA_S);
            }
            else if(RemoteInterfaceObj->getAcqTime() >= RTSA_MS)
            {
                RemoteInterfaceObj->setAcqTime(RemoteInterfaceObj->getAcqTime() + RTSA_MS);
            }
            else if(RemoteInterfaceObj->getAcqTime() >= RTSA_US)
            {
                RemoteInterfaceObj->setAcqTime(RemoteInterfaceObj->getAcqTime() + RTSA_US);
            }
            else
            {
                RemoteInterfaceObj->setAcqTime(RemoteInterfaceObj->getAcqTime() + (qreal)(1.0 / 1000.0));
            }
            refreshButtonDisplay();
            break;
        default:
            break;
        }
    }
    else
    {
        if(!mInputDialog->isHidden())
        {
            mInputDialog->hide();
        }
        switch (mSelectInputID)
        {
         case RTSA_INPUT_ACQ_TIME:
            if(RemoteInterfaceObj->getAcqTime() >= RTSA_S)
            {
                RemoteInterfaceObj->setAcqTime(RemoteInterfaceObj->getAcqTime() - RTSA_S);
            }
            else if(RemoteInterfaceObj->getAcqTime() >= RTSA_MS)
            {
                RemoteInterfaceObj->setAcqTime(RemoteInterfaceObj->getAcqTime() - RTSA_MS);
            }
            else if(RemoteInterfaceObj->getAcqTime() >= RTSA_US)
            {
                RemoteInterfaceObj->setAcqTime(RemoteInterfaceObj->getAcqTime() - RTSA_US);
            }
            else
            {
                RemoteInterfaceObj->setAcqTime(RemoteInterfaceObj->getAcqTime() - (qreal)(1.0 / 1000.0));
            }
            refreshButtonDisplay();
            break;
        default:
            break;
        }
    }

    return;
}
