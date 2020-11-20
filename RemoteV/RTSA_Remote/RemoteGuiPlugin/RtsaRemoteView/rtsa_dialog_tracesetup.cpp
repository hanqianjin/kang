#include "rtsa_dialog_tracesetup.h"
#include "ui_rtsa_dialog_tracesetup.h"
#include <QListView>

RtSa_Dialog_TraceSetup::RtSa_Dialog_TraceSetup(Rtsa_Remote_Interface *RtsaRemoteInterface,RtSa_Dialog_Digitinput *Input, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RtSa_Dialog_TraceSetup),
    RemoteInterfaceObj(RtsaRemoteInterface),
    mInputDialog(Input),
    mUpDownFlag(0)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
//    this->setAttribute(Qt::WA_NoChildEventsForParent,true);
    ui->pb_Detector->setView(new  QListView());
    ui->pb_TraceType->setView(new  QListView());

    //Albert 03/05 for insert Vertical scroll bar
    ui->pb_Detector->setEditable(false);
//    this->setAttribute(Qt::WA_DeleteOnClose);
    this->hide();
    mCurSelTraceIndex = RemoteInterfaceObj->getCurTrace();
    InitDisplay();
    connect(RemoteInterfaceObj,SIGNAL(BitViewChanged(quint32)),this,SLOT(on_Update()));

    connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(finishEntry_trace(qint32)));
    connect(mInputDialog,SIGNAL(ClockWiseDown(QKeyEvent*)),this,SLOT(DigitalKeyRespond(QKeyEvent*)));

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(on_timeOut()));
    setProperty("status",rtsa_qssMode[RemoteInterfaceObj->GetDisplayMode()]);
}

RtSa_Dialog_TraceSetup::~RtSa_Dialog_TraceSetup()
{
//    delete mTraceTypeGroup;
    delete ui;
}
void RtSa_Dialog_TraceSetup::keyPressEvent(QKeyEvent *event)
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
//    qint32 curTrace = RemoteInterfaceObj->getCurTrace();
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
//    case Qt::Key_F2:    //  +/-
    case Qt::Key_F6://key_left
    case Qt::Key_Right:
    case Qt::Key_F7:
        if(mInputDialog->isHidden())
        {
            showInputDialog(RTSA_INPUT_AVERAGE_COUNT);
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
void RtSa_Dialog_TraceSetup::InitDisplay()
{
    InitTraceOnOff();
    InitTraceType();
    InitDector();
    InitCurTrace();
    refreshInfo();
    return;
}
void RtSa_Dialog_TraceSetup::InitTraceOnOff()
{
    mTraceOnOffGroup[RTSA_TR1] = ui->pb_TR1;
    mTraceOnOffGroup[RTSA_TR2] = ui->pb_TR2;
    mTraceOnOffGroup[RTSA_TR3] = ui->pb_TR3;
    mTraceOnOffGroup[RTSA_TR4] = ui->pb_TR4;
    mTraceOnOffGroup[RTSA_TR5] = ui->pb_TR5;
    mTraceOnOffGroup[RTSA_TR6] = ui->pb_TR6;
    return;
}
void RtSa_Dialog_TraceSetup::InitTraceType()
{
//    mTraceTypeGroup = new QButtonGroup;
//    mTraceTypeGroup->addButton(ui->pb_Off,RTSA_TRACE_OFF);
//    mTraceTypeGroup->addButton(ui->pb_ClearWrite,RTSA_CLEAR_WRITE);
//    mTraceTypeGroup->addButton(ui->pb_MaxHold,RTSA_MAX_HOLD);
//    mTraceTypeGroup->addButton(ui->pb_MinHold,RTSA_MIN_HOLD);
//    mTraceTypeGroup->addButton(ui->pb_View,RTSA_VIEW);
//    connect(mTraceTypeGroup,SIGNAL(buttonClicked(int)),this,SLOT(on_pb_TraceType_currentIndexChanged(qint32)));
//    mTraceTypeGroup->button(mControl->getTraceType(mControl->getCurTrace()))->setChecked(true);
    return;
}
void RtSa_Dialog_TraceSetup::InitDector()
{
    ui->pb_Detector->setCurrentIndex(RemoteInterfaceObj->getDectorType());
    connect(ui->pb_Detector,SIGNAL(currentIndexChanged(qint32)),this,SLOT(TraceDec_Change(qint32)));
    return;
}
void RtSa_Dialog_TraceSetup::InitCurTrace()
{
    mTraceSelectGroup = new QButtonGroup();
    mTraceSelectGroup->addButton(ui->pb_TR1,RTSA_TR1);
    mTraceSelectGroup->addButton(ui->pb_TR2,RTSA_TR2);
    mTraceSelectGroup->addButton(ui->pb_TR3,RTSA_TR3);
    mTraceSelectGroup->addButton(ui->pb_TR4,RTSA_TR4);
    mTraceSelectGroup->addButton(ui->pb_TR5,RTSA_TR5);
    mTraceSelectGroup->addButton(ui->pb_TR6,RTSA_TR6);
//    mTraceSelectGroup->addButton(ui->pb_allon,RTSA_TRACE_ALL);
    connect(mTraceSelectGroup,SIGNAL(buttonClicked(qint32)),this,SLOT(TraceSelect_Change(qint32)));
    mTraceSelectGroup->button(RemoteInterfaceObj->getCurTrace())->setChecked(true);
    return;
}
void RtSa_Dialog_TraceSetup::on_pb_cancel_clicked()
{
    this->close();
    return;
}

//void RtSa_Dialog_TraceSetup::on_pb_allon_clicked()
//{
//    for(qint32 i = 0; i < RTSA_NUM_TRACE; i++)
//    {
//        if(mControl->getTraceType(i) == RTSA_TRACE_OFF)
//        {
//           mControl->setTraceType(i,RTSA_CLEAR_WRITE);
//        }
//    }
//    ui->pb_allon->setChecked(true);
//    ui->pb_clearall->setChecked(false);
//    mTraceTypeGroup->button(mControl->getTraceType(mControl->getCurTrace()))->setChecked(true);
//    on_Update();
//    return;
//}


//void RtSa_Dialog_TraceSetup::on_pb_clearall_clicked()
//{
//    for(qint32 i = 0; i < RTSA_NUM_TRACE; i++)
//    {
//        mControl->setTraceType(i,RTSA_TRACE_OFF);
//    }
//    ui->pb_allon->setChecked(false);
////    mTraceTypeGroup->button(RTSA_TRACE_OFF)->setChecked(true);
//    on_Update();
//    return;
//}
void RtSa_Dialog_TraceSetup::refreshInfo()
{
//    qint32 nCurTrace = RemoteInterfaceObj->getCurTrace();
    qint32 nCurTraceType = RemoteInterfaceObj->getTraceType(mCurSelTraceIndex);
//    bool nIsAvgOn = RemoteInterfaceObj->IsAvgOn(mCurSelTraceIndex);
    qint32 nAvgNum = RemoteInterfaceObj->getAvgNum(mCurSelTraceIndex);
    ui->averageEdit->setText(QString::number(nAvgNum));
    if(nCurTraceType != RTSA_TRACE_OFF)
    {
        ui->pb_toggle->setChecked(true);
    }
    else
    {
        ui->pb_toggle->setChecked(false);
    }
    if(nCurTraceType <= RTSA_CLEAR_WRITE)
    {
        ui->pb_TraceType->setCurrentIndex(0);
    }
    else
    {
        ui->pb_TraceType->setCurrentIndex(nCurTraceType - 1);
    }
    return;
}

void RtSa_Dialog_TraceSetup::on_Update()
{
    refreshInfo();
//    ui->pb_TraceType->setCurrentIndex(nCurTraceType + 1);
//    mTraceTypeGroup->button(nCurTraceType)->setChecked(true);
    return;
}

//void RtSa_Dialog_TraceSetup::TraceType_Change(qint32 index)
//{
//    mControl->setTraceType(mControl->getCurTrace(),index);
//    on_Update();
//    return;
//}


void RtSa_Dialog_TraceSetup::TraceDec_Change(qint32 index)
{
    RemoteInterfaceObj->setDectorType(index);
    return;
}

void RtSa_Dialog_TraceSetup::TraceSelect_Change(qint32 index)
{
    mCurSelTraceIndex = index;
    if(RemoteInterfaceObj->getTraceType(mCurSelTraceIndex) != RTSA_TRACE_OFF)
    {
        RemoteInterfaceObj->setCurTrace(mCurSelTraceIndex);
    }
//    if(index != RTSA_TRACE_ALL)
//    {
//        mControl->setCurTrace(index);
//    }
//    ui->TraceTypeBar->setTitle(QString("Current Trace: T%1").arg(QString::number(index+1)));
//    ui->pb_allon->setChecked(false);
    refreshInfo();
    return;
}

void RtSa_Dialog_TraceSetup::on_pb_TraceType_currentIndexChanged(int index)
{
    if(RemoteInterfaceObj->getTraceType(mCurSelTraceIndex) == RTSA_TRACE_OFF)
        return;
//    mControl->setCurTrace(mCurSelTraceIndex);
    qint32 nCurTrace = RemoteInterfaceObj->getCurTrace();
    qint32 nCurTraceType = RemoteInterfaceObj->getTraceType(nCurTrace);
    if(nCurTraceType == (index + 1))
    {
        return;
    }
    RemoteInterfaceObj->setTraceType(RemoteInterfaceObj->getCurTrace(),index + 1);

//    if(nCurTraceType != RTSA_TRACE_OFF)
//    {
//        ui->pb_toggle->setChecked(true);
//    }
//    else
//    {
//        ui->pb_toggle->setChecked(false);
//    }
//    on_Update();
    return;
}

void RtSa_Dialog_TraceSetup::on_pb_toggle_toggled(bool checked)
{
    qint32 traceType = 0;
//    qint32 traceID = 0;
//    if(ui->pb_allon->isChecked())
//    {
//        for(qint32 i = 0; i < RTSA_NUM_TRACE; i++)
//        {
//            if(checked)
//            {
//                ui->pb_toggle->setText("On");
//                traceType  = mControl->getTraceType(i);
//                if(traceType == RTSA_TRACE_OFF)
//                {
//                   mControl->setTraceType(i,RTSA_CLEAR_WRITE);
//                }
//            }
//            else
//            {
//                ui->pb_toggle->setText("Off");
//                mControl->setTraceType(i,RTSA_TRACE_OFF);
//            }

//        }
//    }
//    else
//    {
//        traceID = mControl->getCurTrace();
//        traceType  = mControl->getTraceType(mCurSelTraceIndex);
        if(checked)
        {
            RemoteInterfaceObj->setCurTrace(mCurSelTraceIndex);
            traceType  = RemoteInterfaceObj->getTraceType(mCurSelTraceIndex);
            ui->pb_toggle->setText("On");
            if(traceType == RTSA_TRACE_OFF)
            {
               RemoteInterfaceObj->setTraceType(mCurSelTraceIndex,RTSA_CLEAR_WRITE);
            }
        }
        else
        {
            ui->pb_toggle->setText("Off");
            RemoteInterfaceObj->setTraceType(mCurSelTraceIndex,RTSA_TRACE_OFF);
        }
//    }
    refreshInfo();
    return;
}

void RtSa_Dialog_TraceSetup::finishEntry_trace(qint32 index)
{
    qint32 nAvgNum = RemoteInterfaceObj->getAvgNum(RemoteInterfaceObj->getCurTrace());
    ui->averageEdit->setText(QString::number(nAvgNum));
    return;
}
void RtSa_Dialog_TraceSetup::DigitalKeyRespond(QKeyEvent *event)
{
    keyPressEvent(event);
    return;
}
void RtSa_Dialog_TraceSetup::showInputDialog(qint32 index)
{
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

void RtSa_Dialog_TraceSetup::on_averageEdit_clicked()
{
    showInputDialog(RTSA_INPUT_AVERAGE_COUNT);
    return;
}

void RtSa_Dialog_TraceSetup::on_pb_traceAllOn_clicked()
{
    qint32 traceType;
    for(qint32 i = 0; i < RTSA_NUM_TRACE; i++)
    {
        ui->pb_toggle->setChecked(true);
        ui->pb_toggle->setText("On");
        traceType  = RemoteInterfaceObj->getTraceType(i);
        if(traceType == RTSA_TRACE_OFF)
        {
           RemoteInterfaceObj->setTraceType(i,RTSA_CLEAR_WRITE);
        }
    }
    return;
}

void RtSa_Dialog_TraceSetup::on_pb_clearall_clicked()
{
    RtSa_Dialog_Warning message("Notice","Are you sure to clear all traces?",this,RemoteInterfaceObj->GetDisplayMode());
    message.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    if(message.exec() != QDialog::Accepted)
    {
        return;
    }

    for(qint32 i = 0; i < RTSA_NUM_TRACE; i++)
    {
        RemoteInterfaceObj->setTraceType(i,RTSA_TRACE_OFF);
    }
    refreshInfo();
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-07-30
*/
void RtSa_Dialog_TraceSetup::on_timeOut()
{
    timer->stop();
    qint32 curTrace = RemoteInterfaceObj->getCurTrace();
    if(!mInputDialog->isHidden())
    {
        mInputDialog->hide();
    }
    if(!mUpDownFlag)
    {
        RemoteInterfaceObj->setAvgNum(curTrace,RemoteInterfaceObj->getAvgNum(curTrace) + 1);
        refreshInfo();
    }
    else
    {
        RemoteInterfaceObj->setAvgNum(curTrace,RemoteInterfaceObj->getAvgNum(curTrace) - 1);
        refreshInfo();
    }
    return;
}
