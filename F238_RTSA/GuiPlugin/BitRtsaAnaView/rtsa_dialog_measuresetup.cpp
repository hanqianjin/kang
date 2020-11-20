#include "rtsa_dialog_measuresetup.h"
#include "ui_rtsa_dialog_measuresetup.h"
#include "rtsa_define.h"

RtSa_Dialog_MeasureSetup::RtSa_Dialog_MeasureSetup(RtSa_Interface *interface, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RtSa_Dialog_MeasureSetup),
    mControl(interface)
{
    ui->setupUi(this);
//    this->setAttribute(Qt::WA_DeleteOnClose);
    this->hide();
    initMap();
    ui->pb_Density_Spectrogram->hide();
    setProperty("status",rtsa_qssMode[mControl->GetDisplayMode()]);
}

RtSa_Dialog_MeasureSetup::~RtSa_Dialog_MeasureSetup()
{
    delete ui;
}
void RtSa_Dialog_MeasureSetup::keyPressEvent(QKeyEvent *event)
{
    qint32 keyvalue = event->key();
    if(event->key() == Qt::Key_PowerOff)
    {
        if(!event->isAutoRepeat())
            QApplication::sendEvent(this->parent(),event);
        return;
    }
    qint32 LimitID = mControl->getCurLimit();
    qreal tempStepFreq = 0;
    switch (keyvalue) {
    case Qt::Key_Escape:
        this->close();
        QApplication::sendEvent(this->parent(),event);
        break;
    case Qt::Key_Shift:
        mControl->setShiftKeyEnable(true);
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
        break;
    case Qt::Key_F3:
    case Qt::Key_Up:
    case Qt::Key_F8:
        break;
    case Qt::Key_Down:
    case Qt::Key_F9:
    case Qt::Key_F4:
        break;
    }
    return;
}
void RtSa_Dialog_MeasureSetup::initDisplay()
{
    refreshButtonDisplay();
    return;
}
void RtSa_Dialog_MeasureSetup::initMap()
{
    buttonGroup[0] = ui->pb_Spectrum;
    buttonGroup[1] = ui->pb_Persisten_spec;
    buttonGroup[2] = ui->pb_Density;
    buttonGroup[3] = ui->pb_Density_Spectrogram;

    refreshButtonDisplay();
    return;
}
void RtSa_Dialog_MeasureSetup::refreshButtonDisplay()
{
    qint32 measID = mControl->getDisplay();
    buttonGroup[measID/* - 1*/]->setChecked(true);
    return;
}
void RtSa_Dialog_MeasureSetup::showInputDialog(qint32 index)
{
    return ;
}
void RtSa_Dialog_MeasureSetup::on_pb_cancel_clicked()
{
    this->close();
    return;
}

void RtSa_Dialog_MeasureSetup::on_pb_Spectrum_clicked()
{
//    this->close();
    if(mControl->getDisplay() != RTSA_SPECTRUM_SPECTROGRAM)
    {
        mControl->setDisplay(RTSA_SPECTRUM_SPECTROGRAM);
    }
    return;
}

void RtSa_Dialog_MeasureSetup::on_pb_Persisten_spec_clicked()
{
//    this->close();
    if(mControl->getDisplay() != RTSA_SPECTROGRAM)
    {
        mControl->setDisplay(RTSA_SPECTROGRAM);
    }
    return;
}

void RtSa_Dialog_MeasureSetup::on_pb_Density_clicked()
{
    if(mControl->getDisplay() != RTSA_DENSITY)
    {
        mControl->setDisplay(RTSA_DENSITY);
    }
    return;
}

void RtSa_Dialog_MeasureSetup::on_pb_Density_Spectrogram_clicked()
{
    if(mControl->getDisplay() != RTSA_DENSITY_SPECTROGRAM)
    {
        mControl->setDisplay(RTSA_DENSITY_SPECTROGRAM);
    }
    return;
}
