#include "rtsa_dialog_triggersetup.h"
#include "ui_rtsa_dialog_triggersetup.h"
#include <QListView>
#include <QDebug>

RtSa_Dialog_TriggerSetup::RtSa_Dialog_TriggerSetup( Rtsa_Remote_Interface *RtsaRemoteInterface, RtSa_Dialog_Digitinput *input, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RtSa_Dialog_TriggerSetup),
    RemoteInterfaceObj(RtsaRemoteInterface),
    mInputDialog(input)
  //    mFmtTable(NULL)
{
    ui->setupUi(this);
//    setWindowFlags(Qt::FramelessWindowHint);
//    this->setAttribute(Qt::WA_DeleteOnClose);
    setProperty("status",rtsa_qssMode[RemoteInterfaceObj->GetDisplayMode()]);
    this->hide();
    initMap();
    initDisplay();
//    setAttribute(Qt::WA_DeleteOnClose);
//    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/);
    this->setFocus();
    mCurEdit = 0;
    connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
//    connect(mInputDialog,SIGNAL(ClockWiseDown(QKeyEvent*)),this,SLOT(DigitalKeyRespond(QKeyEvent*)));
    mFmtTable = NULL;
//    setProperty("status",rtsa_qssMode[mControl->GetDisplayMode()]);

//    mInputDialog = NULL;

}
RtSa_Dialog_TriggerSetup::~RtSa_Dialog_TriggerSetup()
{
//    delete mTriggerType;
    delete ui;
}
void RtSa_Dialog_TriggerSetup::initMap()
{
    ui->TriggerTypeBox->setView(new  QListView());

    mBoxList.insert(-10,ui->TriggerTypeBox);
    connect(ui->TriggerTypeBox,SIGNAL(clicked(RtSa_CombBox*)),this,SLOT(on_getComboBoxFocus(RtSa_CombBox*)));

    mEditList.insert(RTSA_VIDEO_LEVEL,ui->edit_Video_level);
    connect(ui->edit_Video_level,SIGNAL(mFocus(RtSa_LineEdit*)),this,SLOT(on_getFocus(RtSa_LineEdit*)));

    mEditList.insert(RTSA_VIDEO_HOLDOFF,ui->edit_Video_HoldOff);
    connect(ui->edit_Video_HoldOff,SIGNAL(mFocus(RtSa_LineEdit*)),this,SLOT(on_getFocus(RtSa_LineEdit*)));

    mEditList.insert(RTSA_VIDEO_DELAY_VALUE,ui->edit_Video_DelayValue);
    connect(ui->edit_Video_DelayValue,SIGNAL(mFocus(RtSa_LineEdit*)),this,SLOT(on_getFocus(RtSa_LineEdit*)));

//    mEditList.insert(RTSA_EXTERNAL_LEVEL,ui->edit_External_level);
//    connect(ui->edit_External_level,SIGNAL(mFocus(RtSa_LineEdit*)),this,SLOT(on_getFocus(RtSa_LineEdit*)));

    mEditList.insert(RTSA_EXTERN_HOLDOFF,ui->edit_External_HoldOff);
    connect(ui->edit_External_HoldOff,SIGNAL(mFocus(RtSa_LineEdit*)),this,SLOT(on_getFocus(RtSa_LineEdit*)));

    mEditList.insert(RTSA_EXTERNAL_DELAY_VALUE,ui->edit_External_DelayValue);
    connect(ui->edit_External_DelayValue,SIGNAL(mFocus(RtSa_LineEdit*)),this,SLOT(on_getFocus(RtSa_LineEdit*)));

    mEditList.insert(RTSA_PERI_TIME,ui->edit_Peri_time);
    connect(ui->edit_Peri_time,SIGNAL(mFocus(RtSa_LineEdit*)),this,SLOT(on_getFocus(RtSa_LineEdit*)));

    mEditList.insert(RTSA_PERI_TIME_DELAY_VALUE,ui->edit_PeriTime_DelayValue);
    connect(ui->edit_PeriTime_DelayValue,SIGNAL(mFocus(RtSa_LineEdit*)),this,SLOT(on_getFocus(RtSa_LineEdit*)));

    mEditList.insert(RTSA_RFBURST_LEVEL,ui->edit_RFBurst_level);
    connect(ui->edit_RFBurst_level,SIGNAL(mFocus(RtSa_LineEdit*)),this,SLOT(on_getFocus(RtSa_LineEdit*)));

    mEditList.insert(RTSA_RFBURST_HOLDOFF,ui->edit_RFBurst_HoldOff);
    connect(ui->edit_RFBurst_level,SIGNAL(mFocus(RtSa_LineEdit*)),this,SLOT(on_getFocus(RtSa_LineEdit*)));

    mEditList.insert(RTSA_RFBURST_DELAY_VALUE,ui->edit_RFBurst_DelayValue);
    connect(ui->edit_RFBurst_DelayValue,SIGNAL(mFocus(RtSa_LineEdit*)),this,SLOT(on_getFocus(RtSa_LineEdit*)));

    mEditList.insert(RTSA_FMT_HOLDOFF,ui->edit_FMT_HoldOff);
    connect(ui->edit_FMT_HoldOff,SIGNAL(mFocus(RtSa_LineEdit*)),this,SLOT(on_getFocus(RtSa_LineEdit*)));

    qint32 num = mEditList.size();
    for(qint32 i =0;i <num;i++)
    {
        connect(mEditList.values().at(i),SIGNAL(clicked()),this,SLOT(edit_clicked()));
    }

    return ;
}
/**
 * @brief  show digit input dialog
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void RtSa_Dialog_TriggerSetup::showInputDialog(qint32 index)
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
    return ;
}

/**
 * @brief  Slot of finish entry.
 * @param  void
 * @author Tony
 * @since 2018-12-21
*/
void RtSa_Dialog_TriggerSetup::on_finishEntry(qint32 index)
{
    if(index < RTSA_INPUT_TRIGGER_DELAY_VALUE)
        return;
    qint32 mEditIndex,mode;
    mode = RemoteInterfaceObj->getTrigger();
//    disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
//    mInputDialog = NULL;
    if(index == RTSA_INPUT_TRIGGER_DELAY_VALUE)
    {
        mEditIndex = mode * 2 + 1;
    }else
    {
        mEditIndex = mode * 2;
    }
    mEditList.value(mEditIndex)->setFocus();
    initDisplay();
    return ;
}
/**
 * @brief  Close digit input dialog.
 * @param  void
 * @author Tony
 * @since 2019-01-11
*/
void RtSa_Dialog_TriggerSetup::digitInputClose()
{
    if(mInputDialog)
    {
        disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
        delete mInputDialog;
        mInputDialog = NULL;
    }
    if(mEditList.contains(mCurEdit))
    {
        mEditList.value(mCurEdit)->setFocus();
    }
    return;
}

/**
 * @brief  Init the display.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void RtSa_Dialog_TriggerSetup::initDisplay()
{
    refreshComBoBox();
    refreshSubmenuDisplay();
    return ;
}

void RtSa_Dialog_TriggerSetup::HideTableWidget()
{
    if(mFmtTable != NULL)
    {
        delete mFmtTable;
        mFmtTable = NULL;
    }
}
/**
 * @brief  Refresh submenu status.
 * @author Tony
 * @since  2019-05-07
*/
void RtSa_Dialog_TriggerSetup::refreshSubmenuDisplay()
{
    qreal value;
    qint32 status;
    QString strInfo;
    qint32 mode = RemoteInterfaceObj->getTrigger();
    ui->subWidget->setCurrentIndex(mode);
//    if(mode >= RTSA_TRIGGER_FMTMASK)
//    {
//        ui->subWidget->setCurrentIndex(RTSA_TRIGGER_FMTMASK);
//    }
//    else if(mode == RTSA_TRIGGER_EXTERNAL)
//    {
//        ui->subWidget->setCurrentIndex(RTSA_TRIGGER_PERIODIC_TIMER);
//    }
//    else if(mode == RTSA_TRIGGER_PERIODIC_TIMER)
//    {
//        ui->subWidget->setCurrentIndex(RTSA_TRIGGER_PERIODIC_TIMER);
//    }
//    else if(mode == RTSA_TRIGGER_RF_BURST)
//    {
//        ui->subWidget->setCurrentIndex(RTSA_TRIGGER_FMTMASK);
//    }
//    else if(mode == RTSA_TRIGGER_FREE_RUN)
//    {
//        ui->subWidget->setCurrentIndex(0);
//    }

//    if(mode >= RTSA_TRIGGER_FMTMASK)
//    {
////        mode = RTSA_TRIGGER_RF_BURST;
//        ui->subWidget->setCurrentIndex(RTSA_TRIGGER_VIDEO);
//    }
//    else if(mode == RTSA_TRIGGER_EXTERNAL)
//    {
////        mode = RTSA_TRIGGER_PERIODIC_TIMER;
//        ui->subWidget->setCurrentIndex(RTSA_TRIGGER_EXTERNAL);
//    }
//    else if(mode == RTSA_TRIGGER_PERIODIC_TIMER)
//    {
//        ui->subWidget->setCurrentIndex(RTSA_TRIGGER_PERIODIC_TIMER);
////        mode = RTSA_TRIGGER_FMTMASK;
//    }
//    else if(mode == RTSA_TRIGGER_FREE_RUN)
//    {
//        ui->subWidget->setCurrentIndex(0);
//    }
//    else
//    {
//        ui->subWidget->setCurrentIndex(mode);
//    }

    switch (mode) {
//    case SA_TRIGGER_FREE_RUN:

//        break;
    case RTSA_TRIGGER_VIDEO:
        value = RemoteInterfaceObj->getTriggerLevel(RTSA_TRIGGER_VIDEO);
        strInfo = QString::number(value,'f',2);
        strInfo += QString(" dBm");
        ui->edit_Video_level->setText(strInfo);

        status = RemoteInterfaceObj->getTriggerSlope(RTSA_TRIGGER_VIDEO);
        if(status)
        {
            ui->pb_Video_Pos->setChecked(true);
        }else{
            ui->pb_Video_Neg->setChecked(true);
        }

        status = RemoteInterfaceObj->getTriggerDelayStatus(RTSA_TRIGGER_VIDEO);
        ui->pb_Video_DelayOn->setChecked(status);
        if(status)
            ui->pb_Video_DelayOn->setText("On");
        else
            ui->pb_Video_DelayOn->setText("Off");
        value = RemoteInterfaceObj->getTriggerDelay(RTSA_TRIGGER_VIDEO);
        strInfo = RemoteInterfaceObj->getAdjustTimeStr(value);
        ui->edit_Video_DelayValue->setText(strInfo);

        value = RemoteInterfaceObj->getriggerHoldOffTime(RTSA_TRIGGER_VIDEO);
        strInfo = RemoteInterfaceObj->getAdjustTimeStr(value);
        ui->edit_Video_HoldOff->setText(strInfo);
        break;
    case RTSA_TRIGGER_EXTERNAL:
        value = RemoteInterfaceObj->getTriggerLevel(RTSA_TRIGGER_EXTERNAL);
        strInfo = QString::number(value,'f',2);
        strInfo += QString(" dBm");
//        ui->edit_External_level->setText(strInfo);

        status = RemoteInterfaceObj->getTriggerSlope(RTSA_TRIGGER_EXTERNAL);
        if(status)
        {
            ui->pb_External_Pos->setChecked(true);
        }else{
            ui->pb_External_Neg->setChecked(true);
        }

        status = RemoteInterfaceObj->getTriggerDelayStatus(RTSA_TRIGGER_EXTERNAL);
        ui->pb_External_DelayOn->setChecked(status);
        if(status) ui->pb_External_DelayOn->setText("On");
        else ui->pb_External_DelayOn->setText("Off");
        value = RemoteInterfaceObj->getTriggerDelay(RTSA_TRIGGER_EXTERNAL);
        strInfo = RemoteInterfaceObj->getAdjustTimeStr(value);
        ui->edit_External_DelayValue->setText(strInfo);
        value = RemoteInterfaceObj->getriggerHoldOffTime(RTSA_TRIGGER_EXTERNAL);
        strInfo = RemoteInterfaceObj->getAdjustTimeStr(value);
        ui->edit_External_HoldOff->setText(strInfo);
        break;
    case RTSA_TRIGGER_PERIODIC_TIMER:
        value = RemoteInterfaceObj->getTriggerPeriodTime();
        strInfo = RemoteInterfaceObj->getAdjustTimeStr(value);
        ui->edit_Peri_time->setText(strInfo);

        status = RemoteInterfaceObj->getTriggerDelayStatus(RTSA_TRIGGER_PERIODIC_TIMER);
        ui->pb_PeriTime_DelayOn->setChecked(status);
        if(status) ui->pb_PeriTime_DelayOn->setText("On");
        else ui->pb_PeriTime_DelayOn->setText("Off");
        value = RemoteInterfaceObj->getTriggerDelay(RTSA_TRIGGER_PERIODIC_TIMER);
        strInfo = RemoteInterfaceObj->getAdjustTimeStr(value);
        ui->edit_PeriTime_DelayValue->setText(strInfo);
        break;
    case RTSA_TRIGGER_RF_BURST:
        value = RemoteInterfaceObj->getTriggerLevel(RTSA_TRIGGER_RF_BURST);
        strInfo = QString::number(value,'f',2);
        strInfo += QString(" dBm");
        ui->edit_RFBurst_level->setText(strInfo);

        status = RemoteInterfaceObj->getTriggerSlope(RTSA_TRIGGER_RF_BURST);
        if(status)
        {
            ui->pb_RFBurst_Pos->setChecked(true);
        }else{
            ui->pb_RFBurst_Neg->setChecked(true);
        }

        status = RemoteInterfaceObj->getTriggerDelayStatus(RTSA_TRIGGER_RF_BURST);
        ui->pb_RFBurst_DelayOn->setChecked(status);
        if(status)
            ui->pb_RFBurst_DelayOn->setText("On");
        else
            ui->pb_RFBurst_DelayOn->setText("Off");
        value = RemoteInterfaceObj->getTriggerDelay(RTSA_TRIGGER_RF_BURST);
        strInfo = RemoteInterfaceObj->getAdjustTimeStr(value);
        ui->edit_RFBurst_DelayValue->setText(strInfo);
        value = RemoteInterfaceObj->getriggerHoldOffTime(RTSA_TRIGGER_RF_BURST);
        strInfo = RemoteInterfaceObj->getAdjustTimeStr(value);
        ui->edit_RFBurst_HoldOff->setText(strInfo);
        break;
    case RTSA_TRIGGER_FMTMASK:
        value = RemoteInterfaceObj->getriggerHoldOffTime(RTSA_TRIGGER_FMTMASK);
        strInfo = RemoteInterfaceObj->getAdjustTimeStr(value);
        ui->edit_FMT_HoldOff->setText(strInfo);
        break;
    default:
        break;
    }

    return ;
}

void RtSa_Dialog_TriggerSetup::refreshComBoBox()
{
    qint32 mode = RemoteInterfaceObj->getTrigger();
    qint32 critertion = RemoteInterfaceObj->getFmtTriggerCriterion();
    ui->TriggerTypeBox->blockSignals(true);
    if(mode > 0)
    {
        mode -= 1;
    }
    ui->TriggerTypeBox->setCurrentIndex(mode);
//    ui->TriggerTypeBox->setCurrentIndex(mode);
//    if(mode >= RTSA_TRIGGER_FMTMASK)
//    {
////        mode = RTSA_TRIGGER_RF_BURST;
//        ui->TriggerTypeBox->setCurrentIndex(RTSA_TRIGGER_VIDEO);
//    }
//    else if(mode == RTSA_TRIGGER_EXTERNAL)
//    {
////        mode = RTSA_TRIGGER_PERIODIC_TIMER;
//        ui->TriggerTypeBox->setCurrentIndex(RTSA_TRIGGER_PERIODIC_TIMER);
//    }
//    else if(mode == RTSA_TRIGGER_PERIODIC_TIMER)
//    {
//        ui->TriggerTypeBox->setCurrentIndex(RTSA_TRIGGER_RF_BURST);
////        mode = RTSA_TRIGGER_FMTMASK;
//    }
//    else if(mode == RTSA_TRIGGER_RF_BURST)
//    {
//        ui->TriggerTypeBox->setCurrentIndex(RTSA_TRIGGER_FMTMASK);
////        mode = RTSA_TRIGGER_FMTMASK;
//    }
//    else if(mode == RTSA_TRIGGER_FREE_RUN)
//    {
//        ui->TriggerTypeBox->setCurrentIndex(0);
//    }

    ui->TriggerTypeBox->blockSignals(false);

    if(RemoteInterfaceObj->getFmtType() == BIT_FMT_UPPER)
    {
        ui->pb_FMTUpper->setChecked(true);
    }
    else
    {
        ui->pb_FMTLower->setChecked(true);
    }
    ui->TriggerCriterion->setCurrentIndex(critertion);
    return;
}
/**
 * @brief  Trigger mode button clicked.
 * @author Tony
 * @since  2018-12-28
*/
void RtSa_Dialog_TriggerSetup::btnclicked(qint32 mode)
{
    RemoteInterfaceObj->setTrigger(mode);
}


//void RtSa_Dialog_TriggerSetup::on_pb_cancel_clicked()
//{
//    this->close();
//    return;
//}

void RtSa_Dialog_TriggerSetup::keyPressEvent(QKeyEvent *event)
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
        if(mFmtTable != NULL)
        {
            QApplication::sendEvent(mFmtTable,event);
            return;
        }
        this->close();
        return;
    case Qt::Key_Shift:
//        if(mControl->globalUserVariable->bShiftKeyPressed)
//            mControl->globalUserVariable->bShiftKeyPressed = false;
//        else
//            mControl->globalUserVariable->bShiftKeyPressed = true;
        this->close();
        return;
    default:
        if(mInputDialog) QApplication::sendEvent(mInputDialog,event);
        break;
    }
}

void RtSa_Dialog_TriggerSetup::on_TriggerTypeBox_currentIndexChanged(int index)
{
    if(index > 0)
        index += 1;
    RemoteInterfaceObj->setTrigger(index);
    initDisplay();
}

void RtSa_Dialog_TriggerSetup::on_getComboBoxFocus(RtSa_CombBox *mBox)
{
    if(mCurEdit<0 && mBoxList.contains(mCurEdit))
    {
        mBoxList.value(mCurEdit)->setStyleSheet("");
    }else if(mCurEdit>0&& mEditList.contains(mCurEdit))
    {
        mEditList.value(mCurEdit)->setStyleSheet("");
    }
    mBox->setStyleSheet("QComboBox{background-image: url(:/rtsa/image/dropdown_click.png);}");
    mCurEdit = mBoxList.key(mBox);
    return;
}

void RtSa_Dialog_TriggerSetup::on_getFocus(RtSa_LineEdit *mEdit)
{
    QString qss =QString("outline: none;border:2px solid rgba(162,115,0,1);padding:6px 6px 5px 8px;");
    qint32 index = mEditList.key(mEdit);
    if(mCurEdit<0 && mBoxList.contains(mCurEdit))
    {
        mBoxList.value(mCurEdit)->setStyleSheet("");
    }else if(mCurEdit>0&& mEditList.contains(mCurEdit))
    {
        mEditList.value(mCurEdit)->setStyleSheet("");
    }
    mEdit->setStyleSheet(qss);
    mCurEdit = index;
    this->repaint();
    return;
}

void RtSa_Dialog_TriggerSetup::edit_clicked()
{
    qint32 index;
    RtSa_LineEdit* edit = qobject_cast<RtSa_LineEdit*>(sender());
    index = mEditList.key(edit,-1);
    if(index == -1)
    {
        return ;
    }

    switch (index)
    {
    case RTSA_EXTERNAL_LEVEL: //V
    case RTSA_VIDEO_LEVEL:
    case RTSA_RFBURST_LEVEL:  //dBm
        showInputDialog(RTSA_INPUT_TRIGGER_LEVEL);
        break;
    case RTSA_PERI_TIME:      //s,ms,us,ns
        showInputDialog(RTSA_INPUT_TRIGGER_PERTIMER);
        break;
    case RTSA_VIDEO_DELAY_VALUE: //s,ms,us,ns
    case RTSA_EXTERNAL_DELAY_VALUE:
    case RTSA_PERI_TIME_DELAY_VALUE:
    case RTSA_RFBURST_DELAY_VALUE:
        showInputDialog(RTSA_INPUT_TRIGGER_DELAY_VALUE);
        break;
    case RTSA_VIDEO_HOLDOFF:
    case RTSA_EXTERN_HOLDOFF:
    case RTSA_RFBURST_HOLDOFF:
    case RTSA_FMT_HOLDOFF:
        showInputDialog(RTSA_INPUT_TRIGGER_HOLDTIME);
        break;
    default:
        break;
    }
    return ;
}

void RtSa_Dialog_TriggerSetup::on_pb_External_DelayOn_clicked(bool checked)
{
    RemoteInterfaceObj->setTriggerDelayStatus(RTSA_TRIGGER_EXTERNAL,checked);
    initDisplay();
    return;
}


void RtSa_Dialog_TriggerSetup::on_pb_PeriTime_DelayOn_clicked(bool checked)
{
    RemoteInterfaceObj->setTriggerDelayStatus(RTSA_TRIGGER_PERIODIC_TIMER,checked);
    initDisplay();
    return;
}

void RtSa_Dialog_TriggerSetup::on_pb_RFBurst_DelayOn_clicked(bool checked)
{
    RemoteInterfaceObj->setTriggerDelayStatus(RTSA_TRIGGER_RF_BURST,checked);
    initDisplay();
    return;
}

void RtSa_Dialog_TriggerSetup::on_pb_Video_DelayOn_clicked(bool checked)
{
     RemoteInterfaceObj->setTriggerDelayStatus(RTSA_TRIGGER_VIDEO,checked);
    initDisplay();
    return;
}

void RtSa_Dialog_TriggerSetup::on_pb_RFBurst_Pos_clicked(bool checked)
{
    qint32 triggerMode = RemoteInterfaceObj->getTrigger();
    RemoteInterfaceObj->setTriggerSlope(triggerMode,checked);
    initDisplay();
    return;
}

void RtSa_Dialog_TriggerSetup::on_pb_RFBurst_Neg_clicked(bool checked)
{
    qint32 triggerMode = RemoteInterfaceObj->getTrigger();
    RemoteInterfaceObj->setTriggerSlope(triggerMode,!checked);
    initDisplay();
    return;
}

void RtSa_Dialog_TriggerSetup::on_pb_Video_Pos_clicked(bool checked)
{
    qint32 triggerMode = RemoteInterfaceObj->getTrigger();
    RemoteInterfaceObj->setTriggerSlope(triggerMode,checked);
    initDisplay();
    return;
}

void RtSa_Dialog_TriggerSetup::on_pb_Video_Neg_clicked(bool checked)
{
    qint32 triggerMode = RemoteInterfaceObj->getTrigger();
    RemoteInterfaceObj->setTriggerSlope(triggerMode,!checked);
    initDisplay();
    return;
}

void RtSa_Dialog_TriggerSetup::on_pb_External_Pos_clicked(bool checked)
{
    qint32 triggerMode = RemoteInterfaceObj->getTrigger();
    RemoteInterfaceObj->setTriggerSlope(triggerMode,checked);
    initDisplay();
    return;
}

void RtSa_Dialog_TriggerSetup::on_pb_External_Neg_clicked(bool checked)
{
    qint32 triggerMode = RemoteInterfaceObj->getTrigger();
    RemoteInterfaceObj->setTriggerSlope(triggerMode,!checked);
    initDisplay();
    return;
}

//void RtSa_Dialog_TriggerSetup::on_pb_FMTNew_clicked()
//{
//    if(mFmtTable != NULL)
//    {
//        delete mFmtTable;
//        mFmtTable = NULL;
//    }
//    mFmtTable = new RtSa_Dialog_FmtTable(mControl,mInput,this);
//    connect(mFmtTable,SIGNAL(destroyed()),this,SLOT(on_limitDestroyed()));
////    mFmtTable->
////    connect(mFmtTable,SIGNAL(destroyed()),this,SLOT(on_limitDestroyed()));
////    if(mLimitTable->isHidden())
////    {
////        mLimitTable->setGeometry(mapToGlobal(QPoint(0,0)).x()/*+this->width()*//*-RTSA_DIGITAL_DIALOG_WIDTH*/,mapToGlobal(QPoint(0,0)).y(),RTSA_DIGITAL_DIALOG_WIDTH,RTSA_DIGITAL_DIALOG_HEIGHT);
////    }
//    mFmtTable->show();
//    mFmtTable->setFocus();
////    mFmtTable->changeTitleName("FMT Edit");
//    return;
//}


/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
void RtSa_Dialog_TriggerSetup::on_pb_cancel_2_clicked()
{
    this->close();
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
void RtSa_Dialog_TriggerSetup::on_pb_FMTNew_clicked()
{
    if(mFmtTable != NULL)
    {
        delete mFmtTable;
        mFmtTable = NULL;
    }
    mFmtTable = new RtSa_Dialog_FmtTable(RemoteInterfaceObj,mInputDialog,this);
    connect(mFmtTable,SIGNAL(destroyed()),this,SLOT(on_limitDestroyed()));
//    mFmtTable->
//    connect(mFmtTable,SIGNAL(destroyed()),this,SLOT(on_limitDestroyed()));
//    if(mFmtTable->isHidden())
//    {
//        mFmtTable->setGeometry(mapToGlobal(QPoint(0,0)).x()+this->width()-RTSA_DIGITAL_DIALOG_WIDTH,mapToGlobal(QPoint(0,0)).y(),RTSA_DIGITAL_DIALOG_WIDTH,RTSA_DIGITAL_DIALOG_HEIGHT);
//    }
    mFmtTable->show();
    mFmtTable->setFocus();
//    mFmtTable->changeTitleName("FMT Edit");
    return;
}
void RtSa_Dialog_TriggerSetup::on_limitDestroyed()
{
//    if(mFmtTable != NULL)
//    {
//        delete mFmtTable;
//        mFmtTable = NULL;
//    }
    mFmtTable = NULL;
    this->setFocus();
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-07-03
*/
void RtSa_Dialog_TriggerSetup::on_pb_FMTUpper_clicked()
{
    RemoteInterfaceObj->setFmtType(BIT_FMT_UPPER);
    return;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-07-04
*/
void RtSa_Dialog_TriggerSetup::on_pb_FMTLower_clicked()
{
    RemoteInterfaceObj->setFmtType(BIT_FMT_LOWER);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-07-04
*/
void RtSa_Dialog_TriggerSetup::on_pb_FMTBuildFromTrace_clicked()
{
    RemoteInterfaceObj->BuildFmtFromTrace();
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-07-04
*/
void RtSa_Dialog_TriggerSetup::on_pb_FMTBuildFromTrace_2_clicked()
{
    RemoteInterfaceObj->DeleteAllFmtMask();
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-09
*/
void RtSa_Dialog_TriggerSetup::on_TriggerCriterion_currentIndexChanged(int index)
{
    RemoteInterfaceObj->setFmtTriggerCriterion(index);
    return;
}
