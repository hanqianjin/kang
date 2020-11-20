#include "rtsa_dialog_freqsetup.h"
#include "ui_rtsa_dialog_freqsetup.h"

RtSa_Dialog_FreqSetup::RtSa_Dialog_FreqSetup(RtSa_Interface* interface,RtSa_Dialog_Digitinput *InputDialog,RtSa_User_Variable* userVariable, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RtSa_Dialog_FreqSetup),
    mInputDialog(InputDialog),
    mControl(interface),
    mSelectInputID(RTSA_INPUT_FREQ_CENTER),
    mChStdDialog(NULL),
    mUserVariable(userVariable),
    mUpDownFlag(0)
{
    ui->setupUi(this);
//    this->setCursor(Qt::BlankCursor);
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
    setProperty("status",rtsa_qssMode[mControl->GetDisplayMode()]);

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
    mControl->setFullSpan();
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
    mEditList.insert(RTSA_INPUT_FREQ_CF,ui->LedFreqStep);
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
    refreshEditDisplay(RTSA_INPUT_FREQ_CF);
    refreshEditDisplay(RTSA_INPUT_FREQ_SPAN);
    refreshEditDisplay(RTSA_INPUT_FREQ_OFFSET);
    refreshEditDisplay(RTSA_INPUT_FREQ_CHANNEL_STANDARD);
    refreshEditDisplay(RTSA_INPUT_FREQ_CHANNEL_NUM);
    refreshEditDisplay(RTSA_INPUT_FREQ_CHANNEL_STEP);
    if(mControl->getCommuDirection() == RTSA_UPLINK)
    {
        ui->pb_Uplink->setChecked(true);
    }
    else
    {
        ui->pb_Downlink->setChecked(true);
    }
    return ;
}

void RtSa_Dialog_FreqSetup::keyPressEvent(QKeyEvent *event)
{
    qint32 keyvalue = event->key();
    qint32 FreqUnit = mInputDialog->getUnitNo();
    qreal tempStepFreq = 0;
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
//                mInputDialog->setGeometry(mapToGlobal(QPoint(0,0)).x()+this->width()/*-RTSA_DIGITAL_DIALOG_WIDTH*/,\
//                                          mapToGlobal(QPoint(0,0)).y(),RTSA_DIGITAL_DIALOG_WIDTH,RTSA_DIGITAL_DIALOG_HEIGHT);
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
    QString strGab,strTmp;
    qreal   value;
    if(!mEditList.contains(index))
        return;
    switch (index)
    {
    case RTSA_INPUT_FREQ_CENTER:
        value = mControl->getCenterFreq();
        strGab = mControl->getFreqAdjustStr(value);
        break;
    case RTSA_INPUT_FREQ_START:
        value = mControl->getStartFreq();
        strGab = mControl->getFreqAdjustStr(value);
        break;
    case RTSA_INPUT_FREQ_STOP:
        value = mControl->getStopFreq();
        strGab = mControl->getFreqAdjustStr(value);
        break;
    case RTSA_INPUT_FREQ_CF:
        value = mControl->getCFStep();
        strGab = mControl->getFreqAdjustStr(value);
        break;
    case RTSA_INPUT_FREQ_SPAN:
        value = mControl->getSpan();
        strGab = mControl->getFreqAdjustStr(value);
        break;
    case RTSA_INPUT_FREQ_OFFSET:
        value = mControl->getFreqOffset();
        strGab = mControl->getFreqAdjustStr(value);
        break;
    case RTSA_INPUT_FREQ_CHANNEL_STANDARD:
        if(mUserVariable->gTecIndex<0 || !mUserVariable->IsFreqInCurChStd())
        {
            strGab = "None";
            break;
        }
        strGab = QString(mRTSA_ChStand[mUserVariable->gTecIndex].name);
//        strGab = strTmp +"-"+mUserVariable->gCHName->at(mUserVariable->gCHIndex);
//        mControl->setCenterFreq(globalUserVariable->adjustFreqByCHStandar());
        break;
    case RTSA_INPUT_FREQ_CHANNEL_NUM:
        if(mUserVariable->gTecIndex<0 || !mUserVariable->IsFreqInCurChStd())
        {
            strGab = "None";
            break;
        }
        value = mUserVariable->CalculateChannelNum();
        strGab = QString::number(value);
        break;
    case RTSA_INPUT_FREQ_CHANNEL_STEP:
        if(mUserVariable->gTecIndex<0 || !mUserVariable->IsFreqInCurChStd())
        {
            strGab = "1";
            break;
        }
        value = mUserVariable->gChannelStep;
//        strGab = QString::number(value);
        strGab = mControl->getFreqAdjustStr(value);
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
    showInputDialog(RTSA_INPUT_FREQ_CF);
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
        mControl->setShiftKeyEnable(true);
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
    mInputDialog->setProperty("status", rtsa_qssMode[mControl->GetDisplayMode()]);
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
    mChStdDialog = new RtSa_Dialog_Ch_Std(mControl,mUserVariable,this->parentWidget());
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
    if(mUserVariable->gTecIndex<0 || !mUserVariable->IsFreqInCurChStd())
    {
        return;
    }
    showInputDialog(RTSA_INPUT_FREQ_CHANNEL_NUM);
    return;
}

void RtSa_Dialog_FreqSetup::on_pb_Uplink_clicked()
{
    mControl->setCommuDirection(RTSA_UPLINK);
    initDisplay();
    return;
}

void RtSa_Dialog_FreqSetup::on_pb_Downlink_clicked()
{
    mControl->setCommuDirection(RTSA_DOWNLINK);
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
            mControl->setCenterFreq(mControl->getCenterFreq() + mControl->getCFStep());
            initDisplay();
            break;
        case RTSA_INPUT_FREQ_START:
            mControl->setStartFreq(mControl->getStartFreq() + mControl->getCFStep());
            initDisplay();
            break;
        case RTSA_INPUT_FREQ_STOP:
            mControl->setStopFreq(mControl->getStopFreq() + mControl->getCFStep());
            initDisplay();
            break;
        case RTSA_INPUT_FREQ_CF:
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
            mControl->setCFStep(mControl->getCFStep() + tempStepFreq);
            initDisplay();
            break;
        case RTSA_INPUT_FREQ_SPAN:
            mControl->setSpan(mControl->getSpan() + mControl->getCFStep());
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
            if(mControl->getCFStep() >= mControl->getCenterFreq())
            {
                mControl->setCenterFreq(0);
            }
            else
            {
                mControl->setCenterFreq(mControl->getCenterFreq() - mControl->getCFStep());
            }
            initDisplay();
            break;
        case RTSA_INPUT_FREQ_START:
            if(mControl->getCFStep() >= mControl->getStartFreq())
            {
                mControl->setStartFreq(0);
            }
            else
            {
                mControl->setStartFreq(mControl->getStartFreq() - mControl->getCFStep());
            }
            initDisplay();
            break;
        case RTSA_INPUT_FREQ_STOP:
            if(mControl->getCFStep() >= mControl->getStopFreq())
            {
                mControl->setStopFreq(0);
            }
            else
            {
                mControl->setStopFreq(mControl->getStopFreq() - mControl->getCFStep());
            }
            initDisplay();
            break;
        case RTSA_INPUT_FREQ_CF:
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
            mControl->setCFStep(mControl->getCFStep() - tempStepFreq);
            initDisplay();
            break;
        case RTSA_INPUT_FREQ_SPAN:
            if(mControl->getCFStep() >= mControl->getSpan())
            {
                mControl->setSpan(0);
            }
            else
            {
                mControl->setSpan(mControl->getSpan() - mControl->getCFStep());
            }
            initDisplay();
            break;
        default:
            break;
        }
    }
    return;
}
