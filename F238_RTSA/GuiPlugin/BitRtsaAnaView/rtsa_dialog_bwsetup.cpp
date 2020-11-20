#include "rtsa_dialog_bwsetup.h"
#include "ui_rtsa_dialog_bwsetup.h"
#include "rtsa_define.h"
#include "rtsa_dialog_warning.h"

RtSa_Dialog_BWSetup::RtSa_Dialog_BWSetup(RtSa_User_Variable *UserVariable, RtSa_Interface *interface, QWidget *parent) :
    QWidget(parent),
    mControl(interface),
    globalUserVariable(UserVariable),
    ui(new Ui::RtSa_Dialog_BWSetup),
    mCurRBWIndex(0),
    mCurFFTWindow(0)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
//    this->setAttribute(Qt::WA_NoChildEventsForParent,true);
//    this->setAttribute(Qt::WA_DeleteOnClose);
    this->hide();
    InitDisplay();
    setProperty("status",rtsa_qssMode[mControl->GetDisplayMode()]);
}

RtSa_Dialog_BWSetup::~RtSa_Dialog_BWSetup()
{
    delete mRBWGroup;
    delete mFFTGroup;
    delete mAutoGroup;
    delete ui;
}
void RtSa_Dialog_BWSetup::InitDisplay()
{
    mRBWGroup = new QButtonGroup;
    mFFTGroup = new QButtonGroup;
    mAutoGroup = new QButtonGroup;

    mRBWGroup->addButton(ui->pbRBW1,RTSA_RBW0);
    mRBWGroup->addButton(ui->pbRBW2,RTSA_RBW1);
    mRBWGroup->addButton(ui->pbRBW3,RTSA_RBW2);
    mRBWGroup->addButton(ui->pbRBW4,RTSA_RBW3);
    mRBWGroup->addButton(ui->pbRBW5,RTSA_RBW4);
    mRBWGroup->addButton(ui->pbRBW6,RTSA_RBW5);
    mRBWGroup->addButton(ui->pbRBW7,RTSA_RBW6);
    mRBWGroup->button(mControl->getBWIndex())->setChecked(true);
    connect(mRBWGroup,SIGNAL(buttonClicked(int)),this,SLOT(RBW_Change(qint32)));

    mFFTGroup->addButton(ui->pbHanning,RTSA_HANNING);
    mFFTGroup->addButton(ui->pbFlattop,RTSA_FLATTOP);
    mFFTGroup->addButton(ui->pbGausian,RTSA_GAUSIAN);
    mFFTGroup->addButton(ui->pbRectangular,RTSA_RECTANGULAR);
    mFFTGroup->addButton(ui->pbKaiser,RTSA_KAISER);
    mFFTGroup->addButton(ui->pbBHarris,RTSA_BLACKMANHARRIS);
    connect(mFFTGroup,SIGNAL(buttonClicked(int)),this,SLOT(FFT_Change(qint32)));

    mAutoGroup->addButton(ui->pbAuto,RTSA_AUTO);
    mAutoGroup->addButton(ui->pbMan,RTSA_MANUAL);
    mAutoGroup->button(mControl->IsBWAuto())->setChecked(true);
    connect(mAutoGroup,SIGNAL(buttonClicked(int)),this,SLOT(RbwAuto(qint32)));

    InitRBWAutoInfo();
    InitFFTWindow();
    InitRBWIndex();
    return;
}
void RtSa_Dialog_BWSetup::keyPressEvent(QKeyEvent *event)
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
        this->close();
        QApplication::sendEvent(this->parent(),event);
        break;
    case Qt::Key_Shift:
        mControl->setShiftKeyEnable(true);
        this->close();
        QApplication::sendEvent(this->parent(),event);
        break;
    default:
        break;
    }
    return;
}
void RtSa_Dialog_BWSetup::InitRBWAutoInfo()
{
    if(mControl->IsBWAuto())
    {
        ui->pbAuto->setChecked(true);
    }
    else
    {
        ui->pbMan->setChecked(true);
    }
    return;
}
void RtSa_Dialog_BWSetup::InitRBWIndex()
{
    for(qint32 i = RTSA_RBW0; i < RTSA_RBW6 + 1; i++)
    {
        qreal freq = RTSA_RbwManualList[globalUserVariable->gFTTWindows][globalUserVariable->gRbwGrade][i];
        QString data = mControl->getFreqAdjustStr(freq,3);
        mRBWGroup->button(i)->setText(data);
    }
    mCurRBWIndex = mControl->getBWIndex();
    mRBWGroup->button(mCurRBWIndex)->setChecked(true);
    InitRBWAutoInfo();
    refreshRBWBtnDisplay();
    return;
}
void RtSa_Dialog_BWSetup::InitFFTWindow()
{
    mCurFFTWindow = mControl->getFFTWindow();
    mFFTGroup->button(mCurFFTWindow)->setChecked(true);
    return;
}

void RtSa_Dialog_BWSetup::refreshRBWBtnDisplay()
{
    if(mControl->getFFTWindow() == RTSA_RECTANGULAR)
    {
        ui->pbRBW1->setEnabled(false);
        ui->pbRBW2->setEnabled(false);
        ui->pbRBW3->setEnabled(false);
        ui->pbRBW4->setEnabled(false);
        ui->pbRBW5->setEnabled(false);
        ui->pbRBW6->setEnabled(false);
    }
    else
    {
        ui->pbRBW1->setEnabled(true);
        ui->pbRBW2->setEnabled(true);
        ui->pbRBW3->setEnabled(true);
        ui->pbRBW4->setEnabled(true);
        ui->pbRBW5->setEnabled(true);
        ui->pbRBW6->setEnabled(true);
    }
    return;
}
void RtSa_Dialog_BWSetup::on_pb_cancel_clicked()
{
    this->close();
    return;
}

void RtSa_Dialog_BWSetup::RBW_Change(qint32 index)
{
    if(index == mControl->getBWIndex())
        return;
    if(mControl->getFFTWindow() == RTSA_RECTANGULAR && index < RTSA_RBW6)
    {
        RtSa_Dialog_Warning message("Notice","Can not change BW in Rectangular Filter!",this,mControl->GetDisplayMode());
        message.setWindowFlags(Qt::WindowStaysOnTopHint|Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
        message.ShowYesButtonOnly();
        ui->pbRBW7->setChecked(true);
        if(message.exec() != QDialog::Accepted)
        {
            return ;
        }
    }
    mControl->setBWIndex(index);
    InitRBWAutoInfo();
    return;
}
void RtSa_Dialog_BWSetup::FFT_Change(qint32 index)
{
    if(index == mControl->getFFTWindow())
        return;
    mControl->setFFTWindow(index);
//    InitFFTWindow();
    InitRBWIndex();
    return;
}

void RtSa_Dialog_BWSetup::RbwAuto(qint32 index)
{
    mControl->setBWAuto(index);
    InitRBWIndex();
    return;
}
