#include "rtsa_dialog_freqsetup.h"
#include "ui_rtsa_dialog_freqsetup.h"

RtSa_Dialog_FreqSetup::RtSa_Dialog_FreqSetup(Rtsa_Remote_Interface *RtsaRemoteInterface,RtSa_Dialog_Digitinput *InputDialog,RtSa_User_Variable* userVariable, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RtSa_Dialog_FreqSetup),
    mInputDialog(InputDialog),
    RemoteInterfaceObj(RtsaRemoteInterface),
    mChStdDialog(NULL),
    mUserVariable(userVariable),
    mSelectInputID(RTSA_INPUT_FREQ_CENTER),
    mUpDownFlag(0)
{
    ui->setupUi(this);
//    this->setCursor(Qt::ArrowCursor);
    setWindowFlags(Qt::FramelessWindowHint);
//    this->setAttribute(Qt::WA_NoChildEventsForParent,true);
//    this->setAttribute(Qt::WA_DeleteOnClose);
    this->hide();
    connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(finishEntry_freq(qint32)));
    connect(mInputDialog,SIGNAL(ClockWiseDown(QKeyEvent*)),this,SLOT(DigitalKeyRespond(QKeyEvent*)));
    initMap();
    initDisplay();
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(on_timeOut()));
    setProperty("status",rtsa_qssMode[RemoteInterfaceObj->GetDisplayMode()]);

}

RtSa_Dialog_FreqSetup::~RtSa_Dialog_FreqSetup()
{
    if(mChStdDialog != NULL)
    {
        disconnect(mChStdDialog,SIGNAL(destroyed()),this,SLOT(on_CHStdClose()));
        delete mChStdDialog;
        mChStdDialog = NULL;
    }
    delete ui;
}
void RtSa_Dialog_FreqSetup::setUserVariable(RtSa_User_Variable* userVariable)
{
    mUserVariable = userVariable;
    return;
}
/**
 * @brief  Close current widget.
 * @param  void
 * @author Tony
 * @since 2018-12-19
*/
void RtSa_Dialog_FreqSetup::on_pb_cancel_clicked()
{
    mInputDialog->close();
    if(mChStdDialog)
    {
        disconnect(mChStdDialog,SIGNAL(destroyed()),this,SLOT(on_CHStdClose()));
        delete mChStdDialog;
        mChStdDialog = NULL;
    }
    this->close();
}

/**
 * @brief  Set up full span and update span information.
 * @param  void
 * @author Tony
 * @since 2018-12-19
*/
void RtSa_Dialog_FreqSetup::on_pb_FullSpan_clicked()
{
    RemoteInterfaceObj->setFullSpan();
    initDisplay();
    mInputDialog->hide();
    return ;
}
/**
 * @brief  Initialize map of indexes and controls.
 * @param  void
 * @author Tony
 * @since 2018-12-20
*/
void RtSa_Dialog_FreqSetup::initMap()
{
    mEditList.insert(RTSA_INPUT_FREQ_CENTER,ui->LedCenterFreq);
    mEditList.insert(RTSA_INPUT_FREQ_START,ui->LedStartFreq);
    mEditList.insert(RTSA_INPUT_FREQ_STOP,ui->LedStopFreq);
    mEditList.insert(RTSA_INPUT_FREQ_STEP,ui->LedFreqStep);
    mEditList.insert(RTSA_INPUT_FREQ_SPAN,ui->LedSpan);
    mEditList.insert(RTSA_INPUT_FREQ_OFFSET,ui->LedOffsetFreq);
    mEditList.insert(RTSA_INPUT_FREQ_CHANNEL_STANDARD,ui->LedChStd);
    mEditList.insert(RTSA_INPUT_FREQ_CHANNEL_NUM,ui->LedChannel);
    mEditList.insert(RTSA_INPUT_FREQ_CHANNEL_STEP,ui->LedChStep);
    return ;
}

/**
 * @brief  Init the display of frequency setup dialog.
 * @param  void
 * @author Tony
 * @since 2018-12-20
*/
void RtSa_Dialog_FreqSetup::initDisplay()
{
    refreshEditDisplay(RTSA_INPUT_FREQ_CENTER);
    refreshEditDisplay(RTSA_INPUT_FREQ_START);
    refreshEditDisplay(RTSA_INPUT_FREQ_STOP);
    refreshEditDisplay(RTSA_INPUT_FREQ_STEP);
    refreshEditDisplay(RTSA_INPUT_FREQ_SPAN);
    refreshEditDisplay(RTSA_INPUT_FREQ_OFFSET);
    refreshEditDisplay(RTSA_INPUT_FREQ_CHANNEL_STANDARD);
    refreshEditDisplay(RTSA_INPUT_FREQ_CHANNEL_NUM);
    refreshEditDisplay(RTSA_INPUT_FREQ_CHANNEL_STEP);
    if(RemoteInterfaceObj->getChannelType() == RTSA_UPLINK)
    {
        ui->pb_Uplink->setChecked(true);
    }
    else
    {
        ui->pb_Downlink->setChecked(true);
    }

    return ;
}

//void RtSa_Dialog_FreqSetup::AskEquipment(quint32 index)
//{
//    if(!mEditList.contains(index))
//        return;
//    switch (index)
//    {
//    case RTSA_INPUT_FREQ_CENTER:
//       RemoteInterfaceObj->getCenterFreq();
//        break;
//    case RTSA_INPUT_FREQ_START:
//       RemoteInterfaceObj->getStartFreq();
//        break;
//    case RTSA_INPUT_FREQ_STOP:
//        RemoteInterfaceObj->getStopFreq();
//        break;
//    case RTSA_INPUT_FREQ_STEP:
//        RemoteInterfaceObj->getStepFreq();
//        break;
//    case RTSA_INPUT_FREQ_SPAN:
//        RemoteInterfaceObj->getSpan();
//        break;
//    case RTSA_INPUT_FREQ_OFFSET:
//        RemoteInterfaceObj->getFreqOffset();
//        break;
//    case RTSA_INPUT_FREQ_CHANNEL_STANDARD:
//        if(mUserVariable->gMeterParam.gConfig_FreqSpan.channelStd<0 || !mUserVariable->IsFreqInCurChStd())
//        {
//            break;
//        }
//        break;
//    case RTSA_INPUT_FREQ_CHANNEL_NUM:
//        if(mUserVariable->gMeterParam.gConfig_FreqSpan.channelStd<0 || !mUserVariable->IsFreqInCurChStd())
//        {
//            break;
//        }
//       mUserVariable->CalculateChannelNum();
//        break;
//    case RTSA_INPUT_FREQ_CHANNEL_STEP:
//        if(mUserVariable->gMeterParam.gConfig_FreqSpan.channelStd<0 || !mUserVariable->IsFreqInCurChStd())
//        {
//            break;
//        }
//        break;
//    default:
//        break;
//    }
//}



void RtSa_Dialog_FreqSetup::keyPressEvent(QKeyEvent *event)
{
    qint32 keyvalue = event->key();
    VARIABLE_IS_NOT_USED qint32 FreqUnit = mInputDialog->getUnitNo();
    VARIABLE_IS_NOT_USED qreal tempStepFreq = 0;
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
//    case Qt::Key_Shift:
    case Qt::Key_F6://key_left
    case Qt::Key_Right:
    case Qt::Key_F7:
//    case Qt::Key_F2:    //  +/-
//        if(mInputDialog->isHidden())
//        {
//            if(mInputDialog->isHidden())
//            {
//                mInputDialog->setGeometry(mapToGlobal(QPoint(0,0)).x()+this->width()/*-RTSA_DIGITAL_DIALOG_WIDTH*/, mapToGlobal(QPoint(0,0)).y(),RTSA_DIGITAL_DIALOG_WIDTH,RTSA_DIGITAL_DIALOG_HEIGHT);
//            }
//            mInputDialog->show();
//        }
        if(mSelectInputID == RTSA_INPUT_FREQ_CHANNEL_STANDARD)
            return;
        if(mInputDialog->isHidden())
        {
            showInputDialog(mSelectInputID);
            mInputDialog->clearEdit();
        }
        mInputDialog->keyresponse(keyvalue);
//        mInputDialog->setFocus();
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
//        if(!mInputDialog->isHidden())
//        {
//            mInputDialog->hide();
//        }
        break;
    default:
        break;
    }
    return;
}
/**
 * @brief  Refresh the corresponding line edit according to the index.
 * @param  index  The index of current editline.
 * @author Tony
 * @since  2018-12-20
*/
void RtSa_Dialog_FreqSetup::refreshEditDisplay(quint32 index)
{
    QString strGab;
    qreal   value;
    if(!mEditList.contains(index))
        return;
    switch (index)
    {
    case RTSA_INPUT_FREQ_CENTER:
        value = RemoteInterfaceObj->getCenterFreq();
        strGab = RemoteInterfaceObj->getFreqAdjustStr(value);
        break;
    case RTSA_INPUT_FREQ_START:
        value = RemoteInterfaceObj->getStartFreq();
        strGab = RemoteInterfaceObj->getFreqAdjustStr(value);
        break;
    case RTSA_INPUT_FREQ_STOP:
        value = RemoteInterfaceObj->getStopFreq();
        strGab = RemoteInterfaceObj->getFreqAdjustStr(value);
        break;
    case RTSA_INPUT_FREQ_STEP:
        value = RemoteInterfaceObj->getStepFreq();
        strGab = RemoteInterfaceObj->getFreqAdjustStr(value);
        break;
    case RTSA_INPUT_FREQ_SPAN:
        value = RemoteInterfaceObj->getSpan();
        strGab = RemoteInterfaceObj->getFreqAdjustStr(value);
        break;
    case RTSA_INPUT_FREQ_OFFSET:
        value = RemoteInterfaceObj->getFreqOffset();
        strGab = RemoteInterfaceObj->getFreqAdjustStr(value);
        break;
    case RTSA_INPUT_FREQ_CHANNEL_STANDARD:
        if(mUserVariable->gMeterParam.gConfig_FreqSpan.channelStd<0 || !mUserVariable->IsFreqInCurChStd())
        {
            strGab = "None";
            break;
        }
        strGab = QString(mRTSA_ChStand[mUserVariable->gMeterParam.gConfig_FreqSpan.channelStd].name);
//        strGab = strTmp +"-"+mUserVariable->gCHName->at(mUserVariable->gMeterParam.gConfig_FreqSpan.channelSelID);
//        mControl->setCenterFreq(globalUserVariable->adjustFreqByCHStandar());
        break;
    case RTSA_INPUT_FREQ_CHANNEL_NUM:
        if(mUserVariable->gMeterParam.gConfig_FreqSpan.channelStd<0 || !mUserVariable->IsFreqInCurChStd())
        {
            strGab = "None";
            break;
        }
        value = mUserVariable->CalculateChannelNum();
        strGab = QString::number(value);
        break;
    case RTSA_INPUT_FREQ_CHANNEL_STEP:
        if(mUserVariable->gMeterParam.gConfig_FreqSpan.channelStd<0 || !mUserVariable->IsFreqInCurChStd())
        {
            strGab = "1";
            break;
        }
        value = mUserVariable->gMeterParam.gConfig_FreqSpan.channelStep;
//        strGab = QString::number(value);
        strGab = RemoteInterfaceObj->getFreqAdjustStr(value);
        break;
    default:
        break;
    }
    mEditList.find(index).value()->setText(strGab);
    return ;
}

/**
 * @brief  Refresh button status.
 * @author Tony
 * @since  2018-12-24
*/
void RtSa_Dialog_FreqSetup::refreshButtonDisplay()
{
//    ui->RBWAutoPB->setChecked(mControl->getRbwStatus());
//    ui->VBWAutoPB->setChecked(mControl->getVbwStatus());
    return ;
}
/**
 * @brief  Click center frequency line edit and pop-up input dialog box.
 * @param  void
 * @author Tony
 * @since 2018-12-19
*/
void RtSa_Dialog_FreqSetup::on_LedCenterFreq_clicked()
{
    showInputDialog(RTSA_INPUT_FREQ_CENTER);
    return ;
}

/**
 * @brief  Click start frequency line edit and pop-up input dialog box.
 * @param  void
 * @author Tony
 * @since 2018-12-19
*/
void RtSa_Dialog_FreqSetup::on_LedStartFreq_clicked()
{
    showInputDialog(RTSA_INPUT_FREQ_START);
    return ;

}

/**
 * @brief  Click stop frequency line edit and pop-up input dialog box.
 * @param  void
 * @author Tony
 * @since 2018-12-19
*/
void RtSa_Dialog_FreqSetup::on_LedStopFreq_clicked()
{
    showInputDialog(RTSA_INPUT_FREQ_STOP);
    return ;
}

/**
 * @brief  Click span frequency line edit and pop-up input dialog box.
 * @param  void
 * @author Tony
 * @since 2018-12-19
*/
void RtSa_Dialog_FreqSetup::on_LedSpan_clicked()
{
    showInputDialog(RTSA_INPUT_FREQ_SPAN);
    return;
}

/**
 * @brief  Click frequency step line edit and pop-up input dialog box.
 * @param  void
 * @author Tony
 * @since 2018-12-19
*/
void RtSa_Dialog_FreqSetup::on_LedFreqStep_clicked()
{
    showInputDialog(RTSA_INPUT_FREQ_STEP);
    return ;
}

void RtSa_Dialog_FreqSetup::DigitalKeyRespond(QKeyEvent *event)
{
    keyPressEvent(event);
    return;
}
/**
 * @brief  Slot of finish entry.
 * @param  void
 * @author Tony
 * @since 2018-12-21
*/
void RtSa_Dialog_FreqSetup::finishEntry_freq(qint32 index)
{
    if(this->isHidden())
        return ;
    if(mEditList.contains(index))
        initDisplay();
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
/**
 * @brief  show digit input dialog
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void RtSa_Dialog_FreqSetup::showInputDialog(qint32 index)
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
}

void RtSa_Dialog_FreqSetup::showCHStdDialog()
{
    if(mChStdDialog)
    {
        disconnect(mChStdDialog,SIGNAL(destroyed()),this,SLOT(on_CHStdClose()));
        delete mChStdDialog;
        mChStdDialog = NULL;
    }
    mChStdDialog = new RtSa_Dialog_Ch_Std(RemoteInterfaceObj,mUserVariable,this->parentWidget());
    mChStdDialog->move(1,66);
    mChStdDialog->setFocus();
    connect(mChStdDialog,SIGNAL(destroyed()),this,SLOT(on_CHStdClose()));
    mChStdDialog->show();
    return;
}
void RtSa_Dialog_FreqSetup::HideChStdDialog()
{
    if(mChStdDialog)
    {
        disconnect(mChStdDialog,SIGNAL(destroyed()),this,SLOT(on_CHStdClose()));
        delete mChStdDialog;
        mChStdDialog = NULL;
    }
    return;
}
void RtSa_Dialog_FreqSetup::on_LedOffsetFreq_clicked()
{
    showInputDialog(RTSA_INPUT_FREQ_OFFSET);
    initDisplay();
    return;
}

void RtSa_Dialog_FreqSetup::on_CHStdClose()
{
    if(!mChStdDialog)
        return;
    disconnect(mChStdDialog,SIGNAL(destroyed()),this,SLOT(on_CHStdClose()));
    mChStdDialog = NULL;
    this->setFocus();
    if(mEditList.contains(mSelectInputID))
    {
        mEditList.value(mSelectInputID)->setFocus();
        initDisplay();
    }
    return;
}

void RtSa_Dialog_FreqSetup::on_LedChStd_clicked()
{
    mSelectInputID = RTSA_INPUT_FREQ_CHANNEL_STANDARD;
    showCHStdDialog();
    return;
}

void RtSa_Dialog_FreqSetup::on_LedChannel_clicked()
{
    if(mUserVariable->gMeterParam.gConfig_FreqSpan.channelStd<0 || !mUserVariable->IsFreqInCurChStd())
    {
        return;
    }
    showInputDialog(RTSA_INPUT_FREQ_CHANNEL_NUM);
    return;
}

void RtSa_Dialog_FreqSetup::on_pb_Uplink_clicked()
{
    RemoteInterfaceObj->setChannelType(RTSA_UPLINK);
    initDisplay();
    return;
}

void RtSa_Dialog_FreqSetup::on_pb_Downlink_clicked()
{
    RemoteInterfaceObj->setChannelType(RTSA_DOWNLINK);
    initDisplay();
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-07-30
*/
void RtSa_Dialog_FreqSetup::on_timeOut()
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
        case RTSA_INPUT_FREQ_CENTER:
            RemoteInterfaceObj->setCenterFreq(RemoteInterfaceObj->getCenterFreq() + RemoteInterfaceObj->getStepFreq());
            initDisplay();
            break;
        case RTSA_INPUT_FREQ_START:
            RemoteInterfaceObj->setStartFreq(RemoteInterfaceObj->getStartFreq() + RemoteInterfaceObj->getStepFreq());
            initDisplay();
            break;
        case RTSA_INPUT_FREQ_STOP:
            RemoteInterfaceObj->setStopFreq(RemoteInterfaceObj->getStopFreq() + RemoteInterfaceObj->getStepFreq());
            initDisplay();
            break;
        case RTSA_INPUT_FREQ_STEP:
            if(FreqUnit == 1)
            {
                tempStepFreq = RTSA_GHZ;
            }
            else if(FreqUnit == 2)
            {
                tempStepFreq = RTSA_MHZ;
            }
            else if(FreqUnit == 3)
            {
                tempStepFreq = RTSA_KHZ;
            }
            else if(FreqUnit == 4)
            {
                tempStepFreq = RTSA_HZ;
            }
            RemoteInterfaceObj->setCFStep(RemoteInterfaceObj->getStepFreq() + tempStepFreq);
            initDisplay();
            break;
        case RTSA_INPUT_FREQ_SPAN:
            RemoteInterfaceObj->setSpan(RemoteInterfaceObj->getSpan() + RemoteInterfaceObj->getStepFreq());
            initDisplay();
            break;
        default:
            break;
        }
    }
    else
    {
        switch (mSelectInputID)
        {
        case RTSA_INPUT_FREQ_CENTER:
            if(RemoteInterfaceObj->getStepFreq() >= RemoteInterfaceObj->getCenterFreq())
            {
                RemoteInterfaceObj->setCenterFreq(0);
            }
            else
            {
                RemoteInterfaceObj->setCenterFreq(RemoteInterfaceObj->getCenterFreq() - RemoteInterfaceObj->getStepFreq());
            }
            initDisplay();
            break;
        case RTSA_INPUT_FREQ_START:
            if(RemoteInterfaceObj->getStepFreq() >= RemoteInterfaceObj->getStartFreq())
            {
                RemoteInterfaceObj->setStartFreq(0);
            }
            else
            {
                RemoteInterfaceObj->setStartFreq(RemoteInterfaceObj->getStartFreq() - RemoteInterfaceObj->getStepFreq());
            }
            initDisplay();
            break;
        case RTSA_INPUT_FREQ_STOP:
            if(RemoteInterfaceObj->getStepFreq() >= RemoteInterfaceObj->getStopFreq())
            {
                RemoteInterfaceObj->setStopFreq(0);
            }
            else
            {
                RemoteInterfaceObj->setStopFreq(RemoteInterfaceObj->getStopFreq() - RemoteInterfaceObj->getStepFreq());
            }
            initDisplay();
            break;
        case RTSA_INPUT_FREQ_STEP:
            if(FreqUnit == 1)
            {
                tempStepFreq = RTSA_GHZ;
            }
            else if(FreqUnit == 2)
            {
                tempStepFreq = RTSA_MHZ;
            }
            else if(FreqUnit == 3)
            {
                tempStepFreq = RTSA_KHZ;
            }
            else if(FreqUnit == 4)
            {
                tempStepFreq = RTSA_HZ;
            }
            RemoteInterfaceObj->setCFStep(RemoteInterfaceObj->getStepFreq() - tempStepFreq);
            initDisplay();
            break;
        case RTSA_INPUT_FREQ_SPAN:
            if(RemoteInterfaceObj->getStepFreq() >= RemoteInterfaceObj->getSpan())
            {
                RemoteInterfaceObj->setSpan(0);
            }
            else
            {
                RemoteInterfaceObj->setSpan(RemoteInterfaceObj->getSpan() - RemoteInterfaceObj->getStepFreq());
            }
            initDisplay();
            break;
        default:
            break;
        }
    }
    return;
}
