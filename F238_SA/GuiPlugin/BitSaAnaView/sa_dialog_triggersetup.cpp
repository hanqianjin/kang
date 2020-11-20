#include "sa_dialog_triggersetup.h"
#include "ui_sa_dialog_triggersetup.h"
#include "sa_applicationcontrol.h"
#include "sa_dialog_digitinput.h"

SA_Dialog_TriggerSetup::SA_Dialog_TriggerSetup(controlInterface *interface,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SA_Dialog_TriggerSetup)
{

    ui->setupUi(this);

    mCurEdit= 0;
    mControl = interface;

    setProperty("status",qssMode[mControl->GetDisplayMode()]);
    initMap();
    initDisplay();
    //setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/);
    this->setFocus();
    mCurEdit = 0;
    mInputDialog = NULL;

    ui->label_12->setVisible(false);
    ui->edit_External_level->setVisible(false);
    ui->label_11->move(18,0);
    ui->pb_External_Pos->move(94,0);
    ui->pb_External_Neg->move(163,0);
    ui->label_10->move(18,50);
    ui->pb_External_DelayOn->move(94,50);
    ui->label_9->move(18,100);
    ui->edit_External_DelayValue->move(94,100);

	hide();
}

SA_Dialog_TriggerSetup::~SA_Dialog_TriggerSetup()
{
    delete ui;
}
/**
 * @brief  Initialize map of indexes and controls.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_TriggerSetup::initMap()
{
    ui->TriggerTypeBox->setView(new  QListView());

    mBoxList.insert(SA_COMBOBOX_TRIGGER,ui->TriggerTypeBox);
    connect(ui->TriggerTypeBox,SIGNAL(clicked(SA_Combobox*)),this,SLOT(on_getComboBoxFocus(SA_Combobox*)));

    mEditList.insert(SA_VIDEO_LEVEL,ui->edit_Video_level);
    connect(ui->edit_Video_level,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));

    mEditList.insert(SA_VIDEO_DELAY_VALUE,ui->edit_Video_DelayValue);
    connect(ui->edit_Video_DelayValue,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));

    mEditList.insert(SA_EXTERNAL_LEVEL,ui->edit_External_level);
    connect(ui->edit_External_level,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));

    mEditList.insert(SA_EXTERNAL_DELAY_VALUE,ui->edit_External_DelayValue);
    connect(ui->edit_External_DelayValue,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));

    mEditList.insert(SA_PERI_TIME,ui->edit_Peri_time);
    connect(ui->edit_Peri_time,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));

    mEditList.insert(SA_PERI_TIME_DELAY_VALUE,ui->edit_PeriTime_DelayValue);
    connect(ui->edit_PeriTime_DelayValue,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));

    mEditList.insert(SA_RFBURST_LEVEL,ui->edit_RFBurst_level);
    connect(ui->edit_RFBurst_level,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));

    mEditList.insert(SA_RFBURST_DELAY_VALUE,ui->edit_RFBurst_DelayValue);
    connect(ui->edit_RFBurst_DelayValue,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
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
void SA_Dialog_TriggerSetup::showInputDialog(qint32 index)
{
    if(mInputDialog)
    {
        mInputDialog->initDisplay(index);
        mInputDialog->setFocus();
    }else
    {
        mInputDialog = new SA_Dialog_DigitInput(mControl,mControl->globalUserVariable,index,this);
        mInputDialog->setFocus();
        mInputDialog->setGeometry(mapToGlobal(QPoint(0,0)).x(),mapToGlobal(QPoint(0,0)).y(),DIGITINPUT_WIDTH,DIGITINPUT_HEIGHT);
        connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
        mInputDialog->show();
    }
    return ;
}

/**
 * @brief  Slot of finish entry.
 * @param  void
 * @author Tony
 * @since 2018-12-21
*/
void SA_Dialog_TriggerSetup::on_finishEntry(qint32 index)
{
    /*qint32 mEditIndex,mode;
    mode = mControl->getTriggerMode();*/
    disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
    mInputDialog = NULL;
    /*if(index == SA_INPUT_TRIGGER_DELAY_VALUE)
    {
        mEditIndex = mode * 2 + 1;
    }else
    {
       mEditIndex = mode * 2;
    }
    mEditList.value(mEditIndex)->setFocus();*/
    initDisplay();
    return ;
}
/**
 * @brief  Close digit input dialog.
 * @param  void
 * @author Tony
 * @since 2019-01-11
*/
void SA_Dialog_TriggerSetup::digitInputClose()
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
void SA_Dialog_TriggerSetup::initDisplay()
{
    //Johnson 191203
    if(mControl->getSpan() == 0)
    {
        ui->label_2->setVisible(true);
        ui->TriggerTypeBox->setVisible(true);
        ui->subWidget->setVisible(true);
        ui->label_warning->setVisible(false);
    }
    else
    {
        ui->label_2->setVisible(false);
        ui->TriggerTypeBox->setVisible(false);
        ui->subWidget->setVisible(false);
        ui->label_warning->setVisible(true);
        ui->label_warning->setText("This menu is not available under \nthis non-zero span mode");
    }

    refreshSubmenuDisplay();
    refreshComBoBox();
    return ;
}


/**
 * @brief  Refresh submenu status.
 * @author Tony
 * @since  2019-05-07
*/
void SA_Dialog_TriggerSetup::refreshSubmenuDisplay()
{
    qreal value;
    qint32 status;
    QString strInfo;
    qint32 mode = mControl->getTriggerMode();
    ui->subWidget->setCurrentIndex(mode);
    switch (mode) {
    case SA_TRIGGER_FREE_RUN:

        break;
    case SA_TRIGGER_VIDEO:
        value = mControl->getTriggerLevel(SA_TRIGGER_VIDEO);
        strInfo = mControl->globalUserVariable->amptTransformToQstring(SA_DBM,value);
        ui->edit_Video_level->setText(strInfo);

        status = mControl->getTriggerSlope(SA_TRIGGER_VIDEO);
        if(status)
        {
            ui->pb_Video_Pos->setChecked(true);
        }else{
            ui->pb_Video_Neg->setChecked(true);
        }

        status = mControl->getTriggerDelayStatus(SA_TRIGGER_VIDEO);
        ui->pb_Video_DelayOn->setChecked(status);
        if(status)
            ui->pb_Video_DelayOn->setText("On");
        else
            ui->pb_Video_DelayOn->setText("Off");
        value = mControl->getTriggerDelayValue(SA_TRIGGER_VIDEO);
        strInfo = mControl->globalUserVariable->TimeTransformToQstring(value);
        ui->edit_Video_DelayValue->setText(strInfo);
        break;
    case SA_TRIGGER_EXTERNAL:
        value = mControl->getTriggerLevel(SA_TRIGGER_EXTERNAL);
        strInfo = mControl->globalUserVariable->amptTransformToQstring(SA_VOLT,value);
        ui->edit_External_level->setText(strInfo);

        status = mControl->getTriggerSlope(SA_TRIGGER_EXTERNAL);
        if(status)
        {
            ui->pb_External_Pos->setChecked(true);
        }else{
            ui->pb_External_Neg->setChecked(true);
        }

        status = mControl->getTriggerDelayStatus(SA_TRIGGER_EXTERNAL);
        ui->pb_External_DelayOn->setChecked(status);
        if(status) ui->pb_External_DelayOn->setText("On");
        else ui->pb_External_DelayOn->setText("Off");
        value = mControl->getTriggerDelayValue(SA_TRIGGER_EXTERNAL);
        strInfo = mControl->globalUserVariable->TimeTransformToQstring(value);
        ui->edit_External_DelayValue->setText(strInfo);
        break;
    case SA_TRIGGER_PERIODIC_TIMER:
        value = mControl->getTriggerPerTimer();
        strInfo = mControl->globalUserVariable->TimeTransformToQstring(value);
        ui->edit_Peri_time->setText(strInfo);

        status = mControl->getTriggerDelayStatus(SA_TRIGGER_PERIODIC_TIMER);
        ui->pb_PeriTime_DelayOn->setChecked(status);
        if(status) ui->pb_PeriTime_DelayOn->setText("On");
        else ui->pb_PeriTime_DelayOn->setText("Off");
        value = mControl->getTriggerDelayValue(SA_TRIGGER_PERIODIC_TIMER);
        strInfo = mControl->globalUserVariable->TimeTransformToQstring(value);
        ui->edit_PeriTime_DelayValue->setText(strInfo);
        break;
    case SA_TRIGGER_RF_BURST:
        value = mControl->getTriggerLevel(SA_TRIGGER_RF_BURST);
        strInfo = mControl->globalUserVariable->amptTransformToQstring(SA_DBM,value);
        ui->edit_RFBurst_level->setText(strInfo);

        status = mControl->getTriggerSlope(SA_TRIGGER_RF_BURST);
        if(status)
        {
            ui->pb_RFBurst_Pos->setChecked(true);
        }else{
            ui->pb_RFBurst_Neg->setChecked(true);
        }

        status = mControl->getTriggerDelayStatus(SA_TRIGGER_RF_BURST);
        ui->pb_RFBurst_DelayOn->setChecked(status);
        if(status) ui->pb_RFBurst_DelayOn->setText("On");
        else ui->pb_RFBurst_DelayOn->setText("Off");
        value = mControl->getTriggerDelayValue(SA_TRIGGER_RF_BURST);
        strInfo = mControl->globalUserVariable->TimeTransformToQstring(value);
        ui->edit_RFBurst_DelayValue->setText(strInfo);
        break;
    case SA_TRIGGER_GPS:

        break;
    default:
        break;
    }

    return ;
}

void SA_Dialog_TriggerSetup::refreshComBoBox()
{
    qint32 mode = mControl->getTriggerMode();
    ui->TriggerTypeBox->blockSignals(true);
    ui->TriggerTypeBox->setCurrentIndex(mode);
    ui->TriggerTypeBox->blockSignals(false);
    return;
}
/**
 * @brief  Trigger mode button clicked.
 * @author Tony
 * @since  2018-12-28
*/
void SA_Dialog_TriggerSetup::btnclicked(qint32 mode)
{
    mControl->setTriggerMode(mode);
}


void SA_Dialog_TriggerSetup::on_pb_cancel_clicked()
{
    hideWidget();
    return;
}

void SA_Dialog_TriggerSetup::keyPressEvent(QKeyEvent *event)
{
    qint32 keyvalue = event->key();
    if(event->key() == Qt::Key_PowerOff)
    {
        if(!event->isAutoRepeat())
            QApplication::sendEvent(this->parent(),event);
        return;
    }
    switch (keyvalue) {
    case Qt::Key_Escape:
        if(mInputDialog)
            QApplication::sendEvent(mInputDialog,event);
        else
            hideWidget();
        return;
    case Qt::Key_Shift:
        if(mControl->globalUserVariable->bShiftKeyPressed)
            mControl->globalUserVariable->bShiftKeyPressed = false;
        else
            mControl->globalUserVariable->bShiftKeyPressed = true;
        hideWidget();
        return;
    default:
        break;
    }

    if(!mEditList.contains(mCurEdit))
        return;

    switch(keyvalue){
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
    case Qt::Key_F2:
    case Qt::Key_Minus:
    case Qt::Key_Period:
        if(!mInputDialog) mEditList.value(mCurEdit)->clicked();
        mInputDialog->initInputKey(event);
        break;
    case Qt::Key_F4:
        if(mInputDialog)
        {
            mInputDialog->close();
        }
        getKnobValue(CLOCKWISE);
        break;
    case Qt::Key_F3:
        if(mInputDialog)
        {
            mInputDialog->close();
        }
        getKnobValue(ANTICLOCKWISE);
        break;
    default:
        if(mInputDialog) QApplication::sendEvent(mInputDialog,event);
        break;
    }
}

qreal SA_Dialog_TriggerSetup::getTimeStep(qreal time)
{
    qreal mStep;
    if((time * SA_KHZ ) < 1)//ns
    {
        mStep = (qreal)1/SA_MHZ ;//Johnson 190918
    }
    else if((time * SA_KHZ) >= 1 && time < 1)//us
    {
        mStep = (qreal)1/SA_KHZ ;//Johnson 190918
    }
    else if(time >= 1 && time < SA_KHZ)//ms
    {
        mStep = 1 ;
    }
    else if(time >= SA_KHZ)//s
    {
        mStep = SA_KHZ ;
    }
    return mStep;
}

void SA_Dialog_TriggerSetup::getKnobValue(qint32 mode)
{
    qreal mStep;
    qreal mValue;
    switch (mCurEdit)
    {
    case SA_VIDEO_DELAY_VALUE:
    case SA_EXTERNAL_DELAY_VALUE:
    case SA_PERI_TIME_DELAY_VALUE:
    case SA_RFBURST_DELAY_VALUE:
        mValue=mControl->getTriggerDelayValue();
        mStep = getTimeStep(mValue);
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        mControl->setTriggerDelayValue(mValue);
        break;
    case SA_VIDEO_LEVEL:
    case SA_EXTERNAL_LEVEL:
    case SA_RFBURST_LEVEL:
        mStep = REF_STEP;
        mValue=mControl->getTriggerLevel();
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        mControl->setTriggerLevel(mValue);
        break;
    case SA_PERI_TIME:
        mValue=mControl->getTriggerPerTimer();
        mStep = getTimeStep(mValue);
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        mControl->setTriggerPerTimer(mValue);
        break;
    }
    initDisplay();
    return;
}

void SA_Dialog_TriggerSetup::on_TriggerTypeBox_currentIndexChanged(int index)
{
    mControl->setTriggerMode(index);
    initDisplay();
}

void SA_Dialog_TriggerSetup::on_getComboBoxFocus(SA_Combobox* mBox)
{
    QString qss = "#SA_Dialog_TriggerSetup[status=\"indoor\"] QComboBox{background-image: url(:/sa/image/dropdown_click.png);}\
                   #SA_Dialog_TriggerSetup[status=\"outdoor\"] QComboBox{background-image: url(:/sa/image/dropdown_click.png);}\
                   #SA_Dialog_TriggerSetup[status=\"night\"] QComboBox{background-image: url(:/sa/image/night/dropdown_click.png);}";

    if(mCurEdit<0 && mBoxList.contains(mCurEdit))
    {
        mBoxList.value(mCurEdit)->setStyleSheet("");
    }else if(mCurEdit>0&& mEditList.contains(mCurEdit))
    {
        mEditList.value(mCurEdit)->setStyleSheet("");
    }
    mBox->setStyleSheet(qss);
    mCurEdit = mBoxList.key(mBox);
    return;
}

void SA_Dialog_TriggerSetup::on_getFocus(SA_LineEdit* mEdit)
{
    QString qss =QString("outline: none;border:2px solid rgba(162,115,0,1);padding:6px 6px 5px 8px;");
    qint32 index = mEditList.key(mEdit);
    if(mCurEdit<0 && mBoxList.contains(mCurEdit))
    {
        mBoxList.value(mCurEdit)->setStyleSheet("");
    }else if(mCurEdit>0 && mEditList.contains(mCurEdit))
    {
        mEditList.value(mCurEdit)->setStyleSheet("");
    }
    mEdit->setStyleSheet(qss);
    mCurEdit = index;
    return;
}

void SA_Dialog_TriggerSetup::edit_clicked()
{
    qint32 index;
    SA_LineEdit* edit = qobject_cast<SA_LineEdit*>(sender());
    index = mEditList.key(edit,-1);
    if(index == -1)
    {
        return ;
    }

    switch (index)
    {
    case SA_EXTERNAL_LEVEL: //V
    case SA_VIDEO_LEVEL:
    case SA_RFBURST_LEVEL:  //dBm
        showInputDialog(SA_INPUT_TRIGGER_LEVEL);
        break;
    case SA_PERI_TIME:      //s,ms,us,ns
        showInputDialog(SA_INPUT_TRIGGER_PERTIMER);
        break;
    case SA_VIDEO_DELAY_VALUE: //s,ms,us,ns
    case SA_EXTERNAL_DELAY_VALUE:
    case SA_PERI_TIME_DELAY_VALUE:
    case SA_RFBURST_DELAY_VALUE:
        showInputDialog(SA_INPUT_TRIGGER_DELAY_VALUE);
        break;
    default:
        break;
    }
    return ;
}

void SA_Dialog_TriggerSetup::on_pb_External_DelayOn_clicked(bool checked)
{
    mControl->setTriggerDelayStatus(checked,SA_TRIGGER_EXTERNAL);
    initDisplay();
    return;
}


void SA_Dialog_TriggerSetup::on_pb_PeriTime_DelayOn_clicked(bool checked)
{
    mControl->setTriggerDelayStatus(checked,SA_TRIGGER_PERIODIC_TIMER);
    initDisplay();
    return;
}

void SA_Dialog_TriggerSetup::on_pb_RFBurst_DelayOn_clicked(bool checked)
{
    mControl->setTriggerDelayStatus(checked,SA_TRIGGER_RF_BURST);
    initDisplay();
    return;
}

void SA_Dialog_TriggerSetup::on_pb_Video_DelayOn_clicked(bool checked)
{
    mControl->setTriggerDelayStatus(checked,SA_TRIGGER_VIDEO);
    initDisplay();
    return;
}

void SA_Dialog_TriggerSetup::on_pb_RFBurst_Pos_clicked(bool checked)
{
    mControl->setTriggerSlope(checked);
    initDisplay();
    return;
}

void SA_Dialog_TriggerSetup::on_pb_RFBurst_Neg_clicked(bool checked)
{
    mControl->setTriggerSlope(!checked);
    initDisplay();
    return;
}

void SA_Dialog_TriggerSetup::on_pb_Video_Pos_clicked(bool checked)
{
    mControl->setTriggerSlope(checked);
    initDisplay();
    return;
}

void SA_Dialog_TriggerSetup::on_pb_Video_Neg_clicked(bool checked)
{
    mControl->setTriggerSlope(!checked);
    initDisplay();
    return;
}

void SA_Dialog_TriggerSetup::on_pb_External_Pos_clicked(bool checked)
{
    mControl->setTriggerSlope(checked);
    initDisplay();
    return;
}

void SA_Dialog_TriggerSetup::on_pb_External_Neg_clicked(bool checked)
{
    mControl->setTriggerSlope(!checked);
    initDisplay();
    return;
}
void SA_Dialog_TriggerSetup::initWidget()
{
    return;
}
void SA_Dialog_TriggerSetup::showWidget()
{
    initDisplay();
    show();
    return;
}
void SA_Dialog_TriggerSetup::hideWidget()
{
    hide();
    digitInputClose();
    emit mDialogHide();
    return;
}
