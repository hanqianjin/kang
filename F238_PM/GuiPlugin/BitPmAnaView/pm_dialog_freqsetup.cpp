#include "pm_dialog_freqsetup.h"
#include "ui_pm_dialog_freqsetup.h"
#include "QDebug"

Pm_Dialog_FreqSetup::Pm_Dialog_FreqSetup(BitPm_Interface *BitPmInterface,Pm_Dialog_Digitinput *InputDialog,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pm_Dialog_FreqSetup),
    mInputDialog(InputDialog),
    PmInterfaceObj(BitPmInterface),
    mChStdDialog(NULL),
    mSelectInputID(PM_INPUT_FREQ_CENTER),
    mUpDownFlag(0),
    m_UpFlg(0),
    m_DownFlg(0)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    this->hide();

    connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(finishEntry_freq(qint32)));
    connect(mInputDialog,SIGNAL(ClockWiseDown(QKeyEvent*)),this,SLOT(DigitalKeyRespond(QKeyEvent*)));

    initMap();
    initDisplay();

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(on_timeOut()));
    setProperty("status",pm_qssMode[PmInterfaceObj->getSystemDisplay()]);
}

Pm_Dialog_FreqSetup::~Pm_Dialog_FreqSetup()
{
    if(mChStdDialog != NULL)
    {
        disconnect(mChStdDialog,SIGNAL(destroyed()),this,SLOT(on_CHStdClose()));
        delete mChStdDialog;
        mChStdDialog = NULL;
    }
    delete ui;
}

void Pm_Dialog_FreqSetup::keyPressEvent(QKeyEvent *event)
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
//                mInputDialog->setGeometry(mapToGlobal(QPoint(0,0)).x()+this->width()/*-PM_DIGITAL_DIALOG_WIDTH*/, mapToGlobal(QPoint(0,0)).y(),PM_DIGITAL_DIALOG_WIDTH,PM_DIGITAL_DIALOG_HEIGHT);
//            }
//            mInputDialog->show();
//        }
        if(mSelectInputID == PM_INPUT_FREQ_CHANNEL_STANDARD)
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
        break;
    default:
        break;
    }
    return;
}


/**
* @brief  Slot of finish entry.
* @param  void
* @author Roc
* @since 2019.11.4
*/
void Pm_Dialog_FreqSetup::finishEntry_freq(qint32 index)
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

/**
* @brief  Close current widget.
* @param  void
* @author Roc
* @since  2019.11.4
*/
void Pm_Dialog_FreqSetup::on_pb_cancel_clicked()
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

void Pm_Dialog_FreqSetup::DigitalKeyRespond(QKeyEvent *event)
{
    keyPressEvent(event);
    return;
}


/**
* @brief
* @param
* @author Roc
* @since 2019.11.4
*/
void Pm_Dialog_FreqSetup::on_timeOut()
{
    qreal fDataUserFlg = 0;

    timer->stop();
    qint32 FreqUnit = mInputDialog->getUnitNo();
    qreal tempStepFreq = 0;
    if(FreqUnit == 1)
    {
        tempStepFreq = PM_GHZ;
    }
    else if(FreqUnit == 2)
    {
        tempStepFreq = PM_MHZ;
    }
    else if(FreqUnit == 3)
    {
        tempStepFreq = PM_KHZ;
    }
    else if(FreqUnit == 4)
    {
        tempStepFreq = PM_HZ;
    }

    if(!mInputDialog->isHidden())
    {
        mInputDialog->hide();
    }
    if(!mUpDownFlag)
    {
        if(m_UpFlg >30)
            fDataUserFlg = 1000;
        else if(m_UpFlg >20)
            fDataUserFlg = 100;
        else if(m_UpFlg >10)
            fDataUserFlg = 10;
        else
            fDataUserFlg = 1;
        m_UpFlg++;
        m_DownFlg= 0;

        switch (mSelectInputID)
        {
        case PM_INPUT_FREQ_CENTER:
//            qDebug()<<PmInterfaceObj->getCenterFreq()<< "   "<<PmInterfaceObj->getStepFreq()<<endl;
            PmInterfaceObj->setCenterFreq(PmInterfaceObj->getCenterFreq() + PmInterfaceObj->getStepFreq());
            initDisplay();
            break;
        case PM_INPUT_FREQ_START:
//            qDebug()<<PmInterfaceObj->getStartFreq()<< "   "<<PmInterfaceObj->getStepFreq()<<endl;
            PmInterfaceObj->setStartFreq(PmInterfaceObj->getStartFreq() + PmInterfaceObj->getStepFreq());
            initDisplay();
            break;
        case PM_INPUT_FREQ_STOP:
//            qDebug()<<PmInterfaceObj->getStopFreq()<< "   "<<PmInterfaceObj->getStepFreq()<<endl;
            PmInterfaceObj->setStopFreq(PmInterfaceObj->getStopFreq() + PmInterfaceObj->getStepFreq());
            initDisplay();
            break;
        case PM_INPUT_FREQ_STEP:
            qDebug()<<PmInterfaceObj->freqBaseFindProc(PmInterfaceObj->getStepFreq())<< "   "<<PmInterfaceObj->getStepFreq()<<endl;
            if(PmInterfaceObj->getStepFreq()*1000 < fDataUserFlg * PmInterfaceObj->freqBaseFindProc(PmInterfaceObj->getStepFreq()))
                PmInterfaceObj->setStepFreq(PmInterfaceObj->getStepFreq() + fDataUserFlg * PmInterfaceObj->freqBaseFindProc(PmInterfaceObj->getStepFreq())/1000000);
             else if(PmInterfaceObj->getStepFreq() < fDataUserFlg * PmInterfaceObj->freqBaseFindProc(PmInterfaceObj->getStepFreq()))
                PmInterfaceObj->setStepFreq(PmInterfaceObj->getStepFreq() + fDataUserFlg * PmInterfaceObj->freqBaseFindProc(PmInterfaceObj->getStepFreq())/1000);
             else
                PmInterfaceObj->setStepFreq(PmInterfaceObj->getStepFreq() + fDataUserFlg * PmInterfaceObj->freqBaseFindProc(PmInterfaceObj->getStepFreq()));
            initDisplay();
            break;
        case PM_INPUT_FREQ_SPAN:
            qDebug()<<PmInterfaceObj->getSpan()<< "   "<< tempStepFreq<<endl;
            PmInterfaceObj->setSpan(PmInterfaceObj->getSpan() + PmInterfaceObj->getStepFreq());
            initDisplay();
            break;
        case PM_INPUT_FREQ_CHANNEL_NUM:
           PmInterfaceObj->setChannelNumber(PmInterfaceObj->getChannelNumber() + 1);
           initDisplay();
           break;
        case PM_INPUT_FREQ_OFFSET:
            PmInterfaceObj->setFreqOffset(PmInterfaceObj->getFreqOffset() + PmInterfaceObj->getStepFreq());
            initDisplay();
            break;
//        case PM_INPUT_FREQ_OFFSET_SIZE:
//            PmInterfaceObj->setFreqOffsetSize(PmInterfaceObj->getFreqOffsetSize() + tempStepFreq);
//            initDisplay();
//            break;
        default:
            break;
        }
    }
    else
    {
        if(m_DownFlg >20)
            fDataUserFlg = 100.0;
        else if(m_DownFlg >10)
            fDataUserFlg =10;
        else
            fDataUserFlg = 1;

        m_UpFlg= 0;
        m_DownFlg ++;
        switch (mSelectInputID)
        {
        case PM_INPUT_FREQ_CENTER:
            if(PmInterfaceObj->getStepFreq() >= PmInterfaceObj->getCenterFreq())
            {
                PmInterfaceObj->setCenterFreq(0);
            }
            else
            {
                PmInterfaceObj->setCenterFreq(PmInterfaceObj->getCenterFreq() - PmInterfaceObj->getStepFreq());
            }
            initDisplay();
            break;
        case PM_INPUT_FREQ_START:
            if(PmInterfaceObj->getStepFreq() >= PmInterfaceObj->getStartFreq())
            {
                PmInterfaceObj->setStartFreq(0);
            }
            else
            {
                PmInterfaceObj->setStartFreq(PmInterfaceObj->getStartFreq() - PmInterfaceObj->getStepFreq());
            }
            initDisplay();
            break;
        case PM_INPUT_FREQ_STOP:
            if(PmInterfaceObj->getStepFreq() >= PmInterfaceObj->getStopFreq())
            {
                PmInterfaceObj->setStopFreq(0);
            }
            else
            {
                PmInterfaceObj->setStopFreq(PmInterfaceObj->getStopFreq() - PmInterfaceObj->getStepFreq());
            }
            initDisplay();
            break;
        case PM_INPUT_FREQ_STEP:
            qDebug()<<PmInterfaceObj->getStepFreq()<<"    "<<PmInterfaceObj->freqBaseFindProc(PmInterfaceObj->getStepFreq())<<endl;
            if(PmInterfaceObj->getStepFreq() > fDataUserFlg*PmInterfaceObj->freqBaseFindProc(PmInterfaceObj->getStepFreq())*101)
                PmInterfaceObj->setStepFreq(PmInterfaceObj->getStepFreq() - fDataUserFlg*PmInterfaceObj->freqBaseFindProc(PmInterfaceObj->getStepFreq())*100);
            else if(PmInterfaceObj->getStepFreq() > fDataUserFlg*PmInterfaceObj->freqBaseFindProc(PmInterfaceObj->getStepFreq())*11)
                PmInterfaceObj->setStepFreq(PmInterfaceObj->getStepFreq() - fDataUserFlg*PmInterfaceObj->freqBaseFindProc(PmInterfaceObj->getStepFreq())*10);
            else if(PmInterfaceObj->getStepFreq() < fDataUserFlg*PmInterfaceObj->freqBaseFindProc(PmInterfaceObj->getStepFreq()))
                PmInterfaceObj->setStepFreq(0);
            else
                PmInterfaceObj->setStepFreq(PmInterfaceObj->getStepFreq() - fDataUserFlg*PmInterfaceObj->freqBaseFindProc(PmInterfaceObj->getStepFreq()));
            initDisplay();
            break;
        case PM_INPUT_FREQ_SPAN:
            qDebug()<<PmInterfaceObj->getSpan()<< "   "<<  tempStepFreq<<endl;
            PmInterfaceObj->setSpan(PmInterfaceObj->getSpan() - PmInterfaceObj->getStepFreq());
            initDisplay();
            break;
         case PM_INPUT_FREQ_CHANNEL_NUM:
            PmInterfaceObj->setChannelNumber(PmInterfaceObj->getChannelNumber() - 1);
            initDisplay();
            break;
        case PM_INPUT_FREQ_OFFSET:
            PmInterfaceObj->setFreqOffset(PmInterfaceObj->getFreqOffset() - PmInterfaceObj->getStepFreq());
            initDisplay();
            break;
//        case PM_INPUT_FREQ_OFFSET_SIZE:
//            PmInterfaceObj->setFreqOffsetSize(PmInterfaceObj->getFreqOffsetSize() - tempStepFreq);
//            initDisplay();
//            break;
        default:
            break;
        }
    }
    return;
}



/**
* @brief  Click center frequency line edit and pop-up input dialog box.
* @param  void
* @author Roc
* @since  2019.11.4
*/
void Pm_Dialog_FreqSetup::on_LedCenterFreq_clicked()
{
    showInputDialog(PM_INPUT_FREQ_CENTER);
    return ;
}

/**
* @brief  Click start frequency line edit and pop-up input dialog box.
* @param  void
* @author Roc
* @since  2019.11.4
*/
void Pm_Dialog_FreqSetup::on_LedStartFreq_clicked()
{
    showInputDialog(PM_INPUT_FREQ_START);
    return ;

}

/**
* @brief  Click stop frequency line edit and pop-up input dialog box.
* @param  void
* @author Roc
* @since  2019.11.4
*/
void Pm_Dialog_FreqSetup::on_LedStopFreq_clicked()
{
    showInputDialog(PM_INPUT_FREQ_STOP);
    return ;
}

/**
* @brief  Click frequency step line edit and pop-up input dialog box.
* @param  void
* @author Roc
* @since  2019.11.4
*/
void Pm_Dialog_FreqSetup::on_LedFreqStep_clicked()
{
    showInputDialog(PM_INPUT_FREQ_STEP);
    return ;
}

/**
* @brief  Click span frequency line edit and pop-up input dialog box.
* @param  void
* @author Roc
* @since  2019.11.4
*/
void Pm_Dialog_FreqSetup::on_LedSpan_clicked()
{
    showInputDialog(PM_INPUT_FREQ_SPAN);
    return;
}

//void Pm_Dialog_FreqSetup::on_pb_SpanDown_currentIndexChanged(int index)
//{
//    mInputDialog->hide();
//    PmInterfaceObj->setSpanUp(PM_SPAN_Table[index]);
//    initDisplay();
//    return ;
//}

//void Pm_Dialog_FreqSetup::on_pb_SpanUp_currentIndexChanged(int index)
//{
//    mInputDialog->hide();
//    PmInterfaceObj->setSpanDown(PM_SPAN_Table[index]);
//    initDisplay();
//    return ;

//}
/**
* @brief  Set up Last span and update span information.
* @param  void
* @author Roc
* @since 2019.11.4
*/
void Pm_Dialog_FreqSetup::on_pb_LastSpan_clicked()
{
    mInputDialog->hide();
    PmInterfaceObj->setSpanType(PM_NORMAL_SPAN);
    initDisplay();
    return ;
}

/**
* @brief  Set up Min span and update span information.
* @param  void
* @author Roc
* @since 2019.11.4
*/
void Pm_Dialog_FreqSetup::on_pb_MinSpan_clicked()
{
    mInputDialog->hide();
    PmInterfaceObj->setSpanType(PM_MIN_SPAN);
    initDisplay();
    return ;
}


/**
* @brief  Set up full span and update span information.
* @param  void
* @author Roc
* @since 2019.11.4
*/
void Pm_Dialog_FreqSetup::on_pb_FullSpan_clicked()
{
    mInputDialog->hide();
    PmInterfaceObj->setSpanType(PM_FULL_SPAN);
    initDisplay();
    return ;
}

void Pm_Dialog_FreqSetup::on_LedChStd_clicked()
{
    mInputDialog->hide();
    mSelectInputID = PM_INPUT_FREQ_CHANNEL_STANDARD;
    showCHStdDialog();
    return;
}

void Pm_Dialog_FreqSetup::on_LedChannel_clicked()
{
    if(PmInterfaceObj->getGlobalUserVariable()->gMeterParam.gConfig_Freq.nChannelStd < 0 || !PmInterfaceObj->getGlobalUserVariable()->IsFreqInCurChStd())
    {
        return;
    }
    showInputDialog(PM_INPUT_FREQ_CHANNEL_NUM);
    return;
}

void Pm_Dialog_FreqSetup::on_pb_FreqOffset_toggled(bool checked)
{
    mInputDialog->hide();
    PmInterfaceObj->setOffset(checked);
    initDisplay();
    return ;
}

void Pm_Dialog_FreqSetup::on_LedOffsetFreq_clicked()
{
    showInputDialog(PM_INPUT_FREQ_OFFSET);
    initDisplay();
    return;
}

//void Pm_Dialog_FreqSetup::on_LedOffsetFreqSize_clicked()
//{
//    showInputDialog(PM_INPUT_FREQ_OFFSET_SIZE);
//    initDisplay();
//    return;
//}

/**
* @brief  Init the display of frequency setup dialog.
* @param  void
* @author Roc
* @since  2019.11.4
*/
void Pm_Dialog_FreqSetup::initDisplay()
{
    refreshEditDisplay(PM_INPUT_FREQ_CENTER);
    refreshEditDisplay(PM_INPUT_FREQ_START);
    refreshEditDisplay(PM_INPUT_FREQ_STOP);
    refreshEditDisplay(PM_INPUT_FREQ_STEP);
    refreshEditDisplay(PM_INPUT_FREQ_SPAN);
    refreshEditDisplay(PM_INPUT_FREQ_CHANNEL_STANDARD);
    refreshEditDisplay(PM_INPUT_FREQ_CHANNEL_NUM);
    refreshEditDisplay(PM_INPUT_FREQ_OFFSET);
//    refreshEditDisplay(PM_INPUT_FREQ_OFFSET_SIZE);

    refreshButtonDisplay();
    return ;
}

/**
* @brief  Initialize map of indexes and controls.
* @param  void
* @author Roc
* @since  2019.11.4
*/
void Pm_Dialog_FreqSetup::initMap()
{
    mEditList.insert(PM_INPUT_FREQ_CENTER,ui->LedCenterFreq);
    mEditList.insert(PM_INPUT_FREQ_START,ui->LedStartFreq);
    mEditList.insert(PM_INPUT_FREQ_STOP,ui->LedStopFreq);
    mEditList.insert(PM_INPUT_FREQ_STEP,ui->LedFreqStep);
    mEditList.insert(PM_INPUT_FREQ_SPAN,ui->LedSpan);
    mEditList.insert(PM_INPUT_FREQ_CHANNEL_STANDARD,ui->LedChStd);
    mEditList.insert(PM_INPUT_FREQ_CHANNEL_NUM,ui->LedChannel);
    mEditList.insert(PM_INPUT_FREQ_OFFSET,ui->LedOffsetFreq);
//    mEditList.insert(PM_INPUT_FREQ_OFFSET_SIZE,ui->LedOffsetFreqSize);
    return ;
}

/**
* @brief  Refresh button status.
* @author Roc
* @since  2019.11.4
*/
void Pm_Dialog_FreqSetup::refreshButtonDisplay()
{
    bool isOffset = PmInterfaceObj->IsOffset();
    if(isOffset)
    {
        ui->pb_FreqOffset->setChecked(true);
        ui->pb_FreqOffset->setText("On");
        ui->labelStartFreq->setText("Offset Start\nFrequency");
        ui->labelCenterFreq->setText("Offset Center\nFrequency");
        ui->labelStopFreq->setText("Offset Stop\nFrequency");

//        ui->LedOffsetFreqSize->show();
//        ui->labelOffsetFreqSize->show();
        ui->LedOffsetFreq->show();
    }
    else
    {
        ui->pb_FreqOffset->setChecked(false);
        ui->pb_FreqOffset->setText("Off");
        ui->pb_FreqOffset->setText("Off");
        ui->labelStartFreq->setText("Start\nFrequency");
        ui->labelCenterFreq->setText("Center\nFrequency");
        ui->labelStopFreq->setText("Stop\nFrequency");
//        ui->LedOffsetFreqSize->hide();
//        ui->labelOffsetFreqSize->hide();
        ui->LedOffsetFreq->hide();
    }
    int nSpanType = PmInterfaceObj->getSpanType();

    if(nSpanType == PM_NORMAL_SPAN)
    {
        ui->pb_LastSpan->setChecked(true);
        ui->pb_MinSpan->setChecked(false);
        ui->pb_FullSpan->setChecked(false);
    }
    else if(nSpanType == PM_MIN_SPAN)
    {
        ui->pb_LastSpan->setChecked(false);
        ui->pb_MinSpan->setChecked(true);
        ui->pb_FullSpan->setChecked(false);
    }
    else if(nSpanType == PM_FULL_SPAN)
    {
        ui->pb_LastSpan->setChecked(false);
        ui->pb_MinSpan->setChecked(false);
        ui->pb_FullSpan->setChecked(true);
    }

    if(PmInterfaceObj->getCommuDirection() == PM_UPLINK)
    {
        ui->pb_Uplink->setChecked(true);
        ui->pb_Downlink->setChecked(false);
    }
    else
    {
        ui->pb_Uplink->setChecked(false);
        ui->pb_Downlink->setChecked(true);
    }
    return;
}

/**
* @brief  Refresh the corresponding line edit according to the index.
* @param  index  The index of current editline.
* @author Roc
* @since 2019.11.4
*/
void Pm_Dialog_FreqSetup::refreshEditDisplay(quint32 index)
{
    QString strGab;
    qlonglong   nllValue;
    qint32  nValue;
    if(!mEditList.contains(index))
        return;
    switch (index)
    {
    case PM_INPUT_FREQ_CENTER:
        nllValue = PmInterfaceObj->getCenterFreq();
        strGab = PmInterfaceObj->getFreqAdjustStr(nllValue);
        break;
    case PM_INPUT_FREQ_START:
        nllValue = PmInterfaceObj->getStartFreq();
        strGab = PmInterfaceObj->getFreqAdjustStr(nllValue);
        break;
    case PM_INPUT_FREQ_STOP:
        nllValue = PmInterfaceObj->getStopFreq();
        strGab = PmInterfaceObj->getFreqAdjustStr(nllValue);
        break;
    case PM_INPUT_FREQ_STEP:
        nllValue = PmInterfaceObj->getStepFreq();
        strGab = PmInterfaceObj->getFreqAdjustStr(nllValue);
        break;
    case PM_INPUT_FREQ_SPAN:
        nllValue = PmInterfaceObj->getSpan();
        strGab = PmInterfaceObj->getFreqAdjustStr(nllValue);
        break;
    case PM_INPUT_FREQ_CHANNEL_STANDARD:
        if(PmInterfaceObj->getGlobalUserVariable()->gMeterParam.gConfig_Freq.nChannelStd < 0  || !PmInterfaceObj->getGlobalUserVariable()->IsFreqInCurChStd())
        {
            strGab = "None";
            break;
        }
        strGab = QString(mPM_ChStand[PmInterfaceObj->getGlobalUserVariable()->gMeterParam.gConfig_Freq.nChannelStd].name);
        break;
    case PM_INPUT_FREQ_CHANNEL_NUM:
        if(PmInterfaceObj->getGlobalUserVariable()->gMeterParam.gConfig_Freq.nChannelStd<0 || !PmInterfaceObj->getGlobalUserVariable()->IsFreqInCurChStd())
        {
            strGab = "None";
            break;
        }
        nValue = PmInterfaceObj->getGlobalUserVariable()->CalculateChannelNum();
        strGab = QString::number(nValue);
        break;
    case PM_INPUT_FREQ_OFFSET:
        nllValue = PmInterfaceObj->getFreqOffset();
        if(0 < nllValue )
        strGab = PmInterfaceObj->getFreqAdjustStr(nllValue);
        else
        {
            strGab = "0 Hz";
        }
        break;
//    case PM_INPUT_FREQ_OFFSET_SIZE:
//        nllValue = PmInterfaceObj->getFreqOffsetSize();
//        strGab = PmInterfaceObj->getFreqAdjustStr(nllValue);
//        break;

    default:
        break;
    }
    mEditList.find(index).value()->setText(strGab);
    return ;
}

/**
* @brief  show digit input dialog
* @param  void
* @author Roc
* @since 2019.11.4
*/
void Pm_Dialog_FreqSetup::showInputDialog(qint32 index)
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
}

void Pm_Dialog_FreqSetup::showCHStdDialog()
{
    if(mChStdDialog)
    {
        disconnect(mChStdDialog,SIGNAL(destroyed()),this,SLOT(on_CHStdClose()));
        delete mChStdDialog;
        mChStdDialog = NULL;
    }
    mChStdDialog = new Pm_Dialog_Ch_Std(PmInterfaceObj,this->parentWidget());
    mChStdDialog->move(1,66);
    mChStdDialog->setFocus();
    connect(mChStdDialog,SIGNAL(destroyed()),this,SLOT(on_CHStdClose()));
    mChStdDialog->show();
    return;
}

void Pm_Dialog_FreqSetup::HideChStdDialog()
{
    if(mChStdDialog)
    {
        disconnect(mChStdDialog,SIGNAL(destroyed()),this,SLOT(on_CHStdClose()));
        delete mChStdDialog;
        mChStdDialog = NULL;
    }
    return;
}

void Pm_Dialog_FreqSetup::on_CHStdClose()
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


void Pm_Dialog_FreqSetup::on_pb_Uplink_clicked()
{
    PmInterfaceObj->setCommuDirection(PM_UPLINK);
    initDisplay();
    return;
}

void Pm_Dialog_FreqSetup::on_pb_Downlink_clicked()
{
    PmInterfaceObj->setCommuDirection(PM_DOWNLINK);
    initDisplay();
    return;
}

