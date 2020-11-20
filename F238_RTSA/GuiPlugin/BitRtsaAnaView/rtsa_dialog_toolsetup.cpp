#include "rtsa_dialog_toolsetup.h"
#include "ui_rtsa_dialog_toolsetup.h"

RtSa_Dialog_ToolSetup::RtSa_Dialog_ToolSetup(RtSa_Interface *interface,RtSa_Dialog_Digitinput *input,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RtSa_Dialog_ToolSetup),
    mControl(interface),
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
    setProperty("status",rtsa_qssMode[mControl->GetDisplayMode()]);
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
    qint32 Units = mInputDialog->getUnitNo();
    qreal tempTime = mControl->getPersistenceTime();
    switch (keyvalue) {
    case Qt::Key_Escape:
        if(!mInputDialog->isHidden())
        {
            mInputDialog->hide();
            return;
        }
        this->close();
        QApplication::sendEvent(this->parent(),event);
        break;
    case Qt::Key_Shift:
        mControl->setShiftKeyEnable(true);
        if(!mInputDialog->isHidden())
        {
            mInputDialog->hide();
        }
        this->close();
        QApplication::sendEvent(this->parent(),event);
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
    qint32 titleName  = mControl->getDisplay();
    switch (titleName) {
    case RTSA_SPECTRUM_SPECTROGRAM:
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
        value = mControl->getPersistenceTime();
        strGab = mControl->getAdjustTimeStr(value);
        break;
    case RTSA_INPUT_HIGHEST_DENSITY:
        value = mControl->getHighestDensity();
        strGab = QString::number(value) + QString(" %");
        break;
    case RTSA_INPUT_LOWEST_DENSITY:
        value = mControl->getLowestDensity();
        strGab = QString::number(value) + QString(" %");
        break;
    case RTSA_INPUT_CURVE:
        value = mControl->getCurve();
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
/**
* @brief
* @param
* @Author Albert
* @date 2020-04-21
*/
void RtSa_Dialog_ToolSetup::showNotice(bool isShow)
{
    if(isShow)
    {
        ui->edit_curve->setVisible(false);
        ui->edit_highest->setVisible(false);
        ui->edit_lowest->setVisible(false);
        ui->edit_time->setVisible(false);
        ui->label_2->setVisible(false);
        ui->label_3->setVisible(false);
        ui->label_4->setVisible(false);
        ui->label_5->setVisible(false);
        ui->label_6->setVisible(false);
        ui->label_7->setVisible(false);
        ui->pb_Auto_Density->setVisible(false);
        ui->pb_Finite->setVisible(false);
        ui->pb_Infinite->setVisible(false);
        ui->label_warning->setVisible(true);
        ui->label_warning->setText("This menu is not available under\n this measurement");
    }
    else
    {
        ui->edit_curve->setVisible(true);
        ui->edit_highest->setVisible(true);
        ui->edit_lowest->setVisible(true);
        ui->edit_time->setVisible(true);
        ui->label_2->setVisible(true);
        ui->label_3->setVisible(true);
        ui->label_4->setVisible(true);
        ui->label_5->setVisible(true);
        ui->label_6->setVisible(true);
        ui->label_7->setVisible(true);
        ui->pb_Auto_Density->setVisible(true);
        ui->pb_Finite->setVisible(true);
        ui->pb_Infinite->setVisible(true);
        ui->label_warning->setVisible(false);
    }
    return;
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
    mInputDialog->setProperty("status", rtsa_qssMode[mControl->GetDisplayMode()]);
    mInputDialog->setStyle(QApplication::style());
    if(mInputDialog->isHidden())
        mInputDialog->show();
    return;
}
void RtSa_Dialog_ToolSetup::initButtonDisplay()
{
    if(mControl->IsPersistenceTimeInfinite())
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
        mControl->setShiftKeyEnable(true);
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
    mControl->setDensityLevelAjust();
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
    mControl->setPersistenceTimeInfinite(true);
    return;
}

void RtSa_Dialog_ToolSetup::on_pb_Finite_clicked()
{
    mControl->setPersistenceTimeInfinite(false);
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
    qint32 FreqUnit = mInputDialog->getUnitNo();
    qreal tempStepFreq = 0;

    if(!mInputDialog->isHidden())
    {
        mInputDialog->hide();
    }
    if(!mUpDownFlag)
    {
        switch (mSelectInputID)
        {
        case RTSA_INPUT_PERSISTENCE_TIME:
            if(mControl->getPersistenceTime() >= RTSA_S)
            {
                mControl->setPersistenceTime(mControl->getPersistenceTime() + RTSA_S);
            }
            else if(mControl->getPersistenceTime() >= RTSA_MS)
            {
                mControl->setPersistenceTime(mControl->getPersistenceTime() + RTSA_MS);
            }
            else if(mControl->getPersistenceTime() >= RTSA_US)
            {
                mControl->setPersistenceTime(mControl->getPersistenceTime() + RTSA_US);
            }
            else
            {
                mControl->setPersistenceTime(mControl->getPersistenceTime() + (qreal)(1.0 / 1000.0));
            }
            refreshButtonDisplay();
            break;
        case RTSA_INPUT_HIGHEST_DENSITY:
            mControl->setHighestDensity(mControl->getHighestDensity() + 1);
            refreshButtonDisplay();
            break;
        case RTSA_INPUT_LOWEST_DENSITY:
            mControl->setLowestDensity(mControl->getLowestDensity() + 1);
            refreshButtonDisplay();
            break;
        case RTSA_INPUT_CURVE:
            mControl->setCurve(mControl->getCurve() + 1);
            refreshButtonDisplay();
            break;
            if(mControl->getAcqTime() >= RTSA_S)
            {
                mControl->setAcqTime(mControl->getAcqTime() + RTSA_S);
            }
            else if(mControl->getAcqTime() >= RTSA_MS)
            {
                mControl->setAcqTime(mControl->getAcqTime() + RTSA_MS);
            }
            else if(mControl->getAcqTime() >= RTSA_US)
            {
                mControl->setAcqTime(mControl->getAcqTime() + RTSA_US);
            }
            else
            {
                mControl->setAcqTime(mControl->getAcqTime() + (qreal)(1.0 / 1000.0));
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
            if(mControl->getPersistenceTime() >= RTSA_S)
            {
                mControl->setPersistenceTime(mControl->getPersistenceTime() - RTSA_S);
            }
            else if(mControl->getPersistenceTime() >= RTSA_MS)
            {
                mControl->setPersistenceTime(mControl->getPersistenceTime() - RTSA_MS);
            }
            else if(mControl->getPersistenceTime() >= RTSA_US)
            {
                mControl->setPersistenceTime(mControl->getPersistenceTime() - RTSA_US);
            }
            else
            {
                mControl->setPersistenceTime(mControl->getPersistenceTime() - (qreal)(1.0 / 1000.0));
            }
            refreshButtonDisplay();
            break;
        case RTSA_INPUT_HIGHEST_DENSITY:
            mControl->setHighestDensity(mControl->getHighestDensity() - 1);
            refreshButtonDisplay();
            break;
        case RTSA_INPUT_LOWEST_DENSITY:
            mControl->setLowestDensity(mControl->getLowestDensity() - 1);
            refreshButtonDisplay();
            break;
        case RTSA_INPUT_CURVE:
            mControl->setCurve(mControl->getCurve() - 1);
            refreshButtonDisplay();
            break;
        default:
            break;
        }

    }
    return;
}
