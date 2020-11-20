#include "rtsa_dialog_toolsetup.h"
#include "ui_rtsa_dialog_toolsetup.h"

RtSa_Dialog_ToolSetup::RtSa_Dialog_ToolSetup(Rtsa_Remote_Interface *RtsaRemoteInterface,RtSa_Dialog_Digitinput *input,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RtSa_Dialog_ToolSetup),
    RemoteInterfaceObj(RtsaRemoteInterface),
    mInputDialog(input),
    mSelectInputID(RTSA_INPUT_PERSISTENCE_TIME),
    mUpDownFlag(0)
{
    ui->setupUi(this);
    initMap();
    connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(finishEntry_Display(qint32)));
    connect(mInputDialog,SIGNAL(ClockWiseDown(QKeyEvent*)),this,SLOT(DigitalKeyRespond(QKeyEvent*)));
//    this->setAttribute(Qt::WA_DeleteOnClose);
    this->hide();
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(on_timeOut()));
    setProperty("status",rtsa_qssMode[RemoteInterfaceObj->GetDisplayMode()]);
}

RtSa_Dialog_ToolSetup::~RtSa_Dialog_ToolSetup()
{
    delete ui;
}
void RtSa_Dialog_ToolSetup::keyPressEvent(QKeyEvent *event)
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
void RtSa_Dialog_ToolSetup::initMap()
{
    mEditList.insert(RTSA_INPUT_PERSISTENCE_TIME,ui->edit_time);
    mEditList.insert(RTSA_INPUT_HIGHEST_DENSITY,ui->edit_highest);
    mEditList.insert(RTSA_INPUT_LOWEST_DENSITY,ui->edit_lowest);
    mEditList.insert(RTSA_INPUT_CURVE,ui->edit_curve);
    refreshButtonDisplay();
    initButtonDisplay();
    refreshTitle();
    return;
}
void RtSa_Dialog_ToolSetup::refreshTitle()
{
    qint32 titleName  = RemoteInterfaceObj->getDisplay();
    switch (titleName) {
    case RTSA_SPECTRUM:
        ui->lblTitle->setText("Persistent Spectrum");
        break;
    case RTSA_SPECTROGRAM:
        ui->lblTitle->setText("Persistent Spectogram");
        break;
    case RTSA_DENSITY:
        ui->lblTitle->setText("Persistent Density");
        break;
    case RTSA_DENSITY_SPECTROGRAM:
        ui->lblTitle->setText("Persistent Density Spectrogram");
        break;
    default:
        break;
    }
}
void RtSa_Dialog_ToolSetup::refreshEditDisplay(quint32 index)
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
    default:
        break;
    }
    mEditList.find(index).value()->setText(strGab);
    return;
}
void RtSa_Dialog_ToolSetup::refreshButtonDisplay()
{
    refreshEditDisplay(RTSA_INPUT_PERSISTENCE_TIME);
    refreshEditDisplay(RTSA_INPUT_HIGHEST_DENSITY);
    refreshEditDisplay(RTSA_INPUT_LOWEST_DENSITY);
    refreshEditDisplay(RTSA_INPUT_CURVE);
    initButtonDisplay();
    return;
}
void RtSa_Dialog_ToolSetup::InitDisplay()
{
    refreshButtonDisplay();
    initButtonDisplay();
    refreshTitle();
}
void RtSa_Dialog_ToolSetup::showInputDialog(qint32 index)
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
void RtSa_Dialog_ToolSetup::initButtonDisplay()
{
    if(RemoteInterfaceObj->IsPersistenceTimeInfinite())
    {
        ui->pb_Infinite->setChecked(true);
        ui->pb_Finite->setChecked(false);
    }
    else
    {
        ui->pb_Infinite->setChecked(false);
        ui->pb_Finite->setChecked(true);
    }
    return;
}
void RtSa_Dialog_ToolSetup::on_edit_time_clicked()
{
    showInputDialog(RTSA_INPUT_PERSISTENCE_TIME);
    return;
}
void RtSa_Dialog_ToolSetup::finishEntry_Display(qint32 index)
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
void RtSa_Dialog_ToolSetup::DigitalKeyRespond(QKeyEvent *event)
{
    keyPressEvent(event);
    return;
}

void RtSa_Dialog_ToolSetup::on_edit_highest_clicked()
{
    showInputDialog(RTSA_INPUT_HIGHEST_DENSITY);
    return;
}

void RtSa_Dialog_ToolSetup::on_edit_lowest_clicked()
{
    showInputDialog(RTSA_INPUT_LOWEST_DENSITY);
    return;
}

void RtSa_Dialog_ToolSetup::on_edit_curve_clicked()
{
    showInputDialog(RTSA_INPUT_CURVE);
    return;
}

void RtSa_Dialog_ToolSetup::on_pb_cancel_clicked()
{
    this->close();
    return;
}

void RtSa_Dialog_ToolSetup::on_pb_Auto_Density_clicked()
{
    RemoteInterfaceObj->setDensityLevelAjust();
    refreshButtonDisplay();
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-17
*/
void RtSa_Dialog_ToolSetup::on_pb_Infinite_clicked()
{
    RemoteInterfaceObj->setPersistenceTimeInfinite(true);
    return;
}

void RtSa_Dialog_ToolSetup::on_pb_Finite_clicked()
{
    RemoteInterfaceObj->setPersistenceTimeInfinite(false);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-07-30
*/
void RtSa_Dialog_ToolSetup::on_timeOut()
{
    timer->stop();
//    qint32 FreqUnit = mInputDialog->getUnitNo();
//    qreal tempStepFreq = 0;

    if(!mInputDialog->isHidden())
    {
        mInputDialog->hide();
    }
    if(!mUpDownFlag)
    {
        switch (mSelectInputID)
        {
        case RTSA_INPUT_PERSISTENCE_TIME:
            if(RemoteInterfaceObj->getPersistenceTime() >= RTSA_S)
            {
                RemoteInterfaceObj->setPersistenceTime(RemoteInterfaceObj->getPersistenceTime() + RTSA_S);
            }
            else if(RemoteInterfaceObj->getPersistenceTime() >= RTSA_MS)
            {
                RemoteInterfaceObj->setPersistenceTime(RemoteInterfaceObj->getPersistenceTime() + RTSA_MS);
            }
            else if(RemoteInterfaceObj->getPersistenceTime() >= RTSA_US)
            {
                RemoteInterfaceObj->setPersistenceTime(RemoteInterfaceObj->getPersistenceTime() + RTSA_US);
            }
            else
            {
                RemoteInterfaceObj->setPersistenceTime(RemoteInterfaceObj->getPersistenceTime() + (qreal)(1.0 / 1000.0));
            }
            refreshButtonDisplay();
            break;
        case RTSA_INPUT_HIGHEST_DENSITY:
            RemoteInterfaceObj->setHighestDensity(RemoteInterfaceObj->getHighestDensity() + 1);
            refreshButtonDisplay();
            break;
        case RTSA_INPUT_LOWEST_DENSITY:
            RemoteInterfaceObj->setLowestDensity(RemoteInterfaceObj->getLowestDensity() + 1);
            refreshButtonDisplay();
            break;
        case RTSA_INPUT_CURVE:
            RemoteInterfaceObj->setCurve(RemoteInterfaceObj->getCurve() + 1);
            refreshButtonDisplay();
            break;
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
        switch (mSelectInputID)
        {
        case RTSA_INPUT_PERSISTENCE_TIME:
            if(RemoteInterfaceObj->getPersistenceTime() >= RTSA_S)
            {
                RemoteInterfaceObj->setPersistenceTime(RemoteInterfaceObj->getPersistenceTime() - RTSA_S);
            }
            else if(RemoteInterfaceObj->getPersistenceTime() >= RTSA_MS)
            {
                RemoteInterfaceObj->setPersistenceTime(RemoteInterfaceObj->getPersistenceTime() - RTSA_MS);
            }
            else if(RemoteInterfaceObj->getPersistenceTime() >= RTSA_US)
            {
                RemoteInterfaceObj->setPersistenceTime(RemoteInterfaceObj->getPersistenceTime() - RTSA_US);
            }
            else
            {
                RemoteInterfaceObj->setPersistenceTime(RemoteInterfaceObj->getPersistenceTime() - (qreal)(1.0 / 1000.0));
            }
            refreshButtonDisplay();
            break;
        case RTSA_INPUT_HIGHEST_DENSITY:
            RemoteInterfaceObj->setHighestDensity(RemoteInterfaceObj->getHighestDensity() - 1);
            refreshButtonDisplay();
            break;
        case RTSA_INPUT_LOWEST_DENSITY:
            RemoteInterfaceObj->setLowestDensity(RemoteInterfaceObj->getLowestDensity() - 1);
            refreshButtonDisplay();
            break;
        case RTSA_INPUT_CURVE:
            RemoteInterfaceObj->setCurve(RemoteInterfaceObj->getCurve() - 1);
            refreshButtonDisplay();
            break;
        default:
            break;
        }

    }
    return;
}
