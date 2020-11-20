#include "sa_dialog_doorcontrol.h"
#include "ui_sa_dialog_doorcontrol.h"
#include "sa_applicationcontrol.h"
#include "sa_dialog_digitinput.h"

#include "QAbstractItemView"

sa_dialog_doorcontrol::sa_dialog_doorcontrol(controlInterface *interface, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sa_dialog_doorcontrol)
{
    ui->setupUi(this);
    mControl = interface;
    setProperty("status",qssMode[mControl->GetDisplayMode()]);
    this->hide();

    initMap();
    initDisplay();
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint);
    this->setFocus();
    mCurEdit = 0;
    mInputDialog = NULL;
}

sa_dialog_doorcontrol::~sa_dialog_doorcontrol()
{
    delete ui;
}

void sa_dialog_doorcontrol::initMap()
{
    ui->DoorControlSourceBox->setView(new QListView());
    /*ui->Extern_SweepModeBox->setView(new QListView());
    ui->RFBurst_SweepModeBox->setView(new QListView());
    ui->Period_SweepModeBox->setView(new QListView());*/
    //ui->Period_SynchSourceBox->setView(new QListView());

    mBoxList.insert(SA_COMBOBOX_DOORCONTROL_SOURCE,ui->DoorControlSourceBox);
    /*mBoxList.insert(SA_COMBOBOX_EXTERN_SWEEP_MODE,ui->Extern_SweepModeBox);
    mBoxList.insert(SA_COMBOBOX_REBURST_SWEEP_MODE,ui->RFBurst_SweepModeBox);
    mBoxList.insert(SA_COMBOBOX_PERI_SWEEP_MODE,ui->Period_SweepModeBox);*/
    //mBoxList.insert(SA_COMBOBOX_PERI_SYN_SOURCE,ui->Period_SynchSourceBox);
    qint32 num = mBoxList.size();
    for(qint32 i = 0;i<num;i++)
    {
        connect(mBoxList.values().at(i),SIGNAL(clicked(SA_Combobox*)),this,SLOT(on_getComboBoxFocus(SA_Combobox*)));
    }

    mBtnGrp = new QButtonGroup();
    mBtnGrp->setExclusive(true);
    mBtnGrp->addButton(ui->pb_extern_gatedelay_left,SA_EXTERN_GATEDELAY_LEFT);
    mBtnGrp->addButton(ui->pb_extern_gatedelay_right,SA_EXTERN_GATEDELAY_RIGHT);
    mBtnGrp->addButton(ui->pb_extern_gatelength_left,SA_EXTERN_GATELENGTH_LEFT);
    mBtnGrp->addButton(ui->pb_extern_gatelength_right,SA_EXTERN_GATELENGTH_RIGHT);
    mBtnGrp->addButton(ui->pb_RF_gatedelay_left,SA_RF_GATEDELAY_LEFT);
    mBtnGrp->addButton(ui->pb_RF_gatedelay_right,SA_RF_GATEDELAY_RIGHT);
    mBtnGrp->addButton(ui->pb_RF_gatelength_left,SA_RF_GATELENGTH_LEFT);
    mBtnGrp->addButton(ui->pb_RF_gatelength_right,SA_RF_GATELENGTH_RIGHT);
    mBtnGrp->addButton(ui->pb_Peri_gatedelay_left,SA_PERI_GATEDELAY_LEFT);
    mBtnGrp->addButton(ui->pb_Peri_gatedelay_right,SA_PERI_GATEDELAY_RIGHT);
    mBtnGrp->addButton(ui->pb_Peri_gatelength_left,SA_PERI_GATELENGTH_LEFT);
    mBtnGrp->addButton(ui->pb_Peri_gatelength_right,SA_PERI_GATELENGTH_RIGHT);

    connect(mBtnGrp,SIGNAL(buttonClicked(qint32)),this,SLOT(runBtnClick(qint32)));

    mEditList.insert(SA_EXTERN_TRIGGER_DELAY,ui->edit_External_TriggerDelay);
    mEditList.insert(SA_EXTERN_DOORWIDTH,ui->edit_External_DoorWidth);
    mEditList.insert(SA_EXTERN_PREVENT_TIME,ui->edit_External_PreventTime);
    mEditList.insert(SA_RFBURST_TRIGGER_DELAY,ui->edit_RFBurst_TriggerDelay);
    mEditList.insert(SA_RFBURST_DOORWIDTH,ui->edit_RFBurst_DoorWidth);
    mEditList.insert(SA_RFBURST_PREVENT_TIME,ui->edit_RFBurst_PreventTime);
    mEditList.insert(SA_RFBURST_TRIGGER_LEVEL,ui->edit_RFBurst_TriggerLevel);
    mEditList.insert(SA_PERI_TRIGGER_DELAY,ui->edit_Period_TriggerDelay);
    mEditList.insert(SA_PERI_DOOR_WIDTH,ui->edit_Period_DoorWidth);
    //mEditList.insert(SA_PERI_PREVENT_TIME,ui->edit_Period_PreventTime);
    mEditList.insert(SA_PERI_PERIOD,ui->edit_Period_Period);
    //mEditList.insert(SA_PERI_SYN_SOURCE_DELAY,ui->edit_Period_SynSrcDelay);
    //mEditList.insert(SA_PERI_SYN_SOURCE_PREVENT_TIME,ui->edit_Period_SrcPrTime);
    /*mEditList.insert(SA_EXTERN_GATEVIEW_STARTTIME,ui->edit_External_GateView_StartTime);
    mEditList.insert(SA_RFBURST_GATEVIEW_STARTTIME,ui->edit_RFBurst_GateView_StartTime);
    mEditList.insert(SA_PERI_GATEVIEW_STARTTIME,ui->edit_Period_GateView_StartTime);*/
    num = mEditList.size();
    for(qint32 i =0;i <num;i++)
    {
        connect(mEditList.values().at(i),SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
        connect(mEditList.values().at(i),SIGNAL(clicked()),this,SLOT(edit_clicked()));
    }
    return ;
}

void sa_dialog_doorcontrol::runBtnClick(qint32 ID)
{
    switch(ID)
    {
    case SA_EXTERN_GATEDELAY_LEFT:
    case SA_RF_GATEDELAY_LEFT:
    case SA_PERI_GATEDELAY_LEFT:
        if(mControl->getDoorControlSource() == SA_EXTERN_TRIGGER) mCurEdit = SA_EXTERN_TRIGGER_DELAY;
#if !AFTERGATESWEEPCHANGED
        else if(mControl->getDoorControlSource() == SA_RFBURST_TRIGGER) mCurEdit = SA_RFBURST_TRIGGER_DELAY;
#endif
        else if(mControl->getDoorControlSource() == SA_PERIOD_TRIGGER) mCurEdit = SA_PERI_TRIGGER_DELAY;

        getKnobValue(CLOCKWISE);
        break;
    case SA_EXTERN_GATEDELAY_RIGHT:
    case SA_RF_GATEDELAY_RIGHT:
    case SA_PERI_GATEDELAY_RIGHT:
        if(mControl->getDoorControlSource() == SA_EXTERN_TRIGGER) mCurEdit = SA_EXTERN_TRIGGER_DELAY;
#if !AFTERGATESWEEPCHANGED
        else if(mControl->getDoorControlSource() == SA_RFBURST_TRIGGER) mCurEdit = SA_RFBURST_TRIGGER_DELAY;
#endif
        else if(mControl->getDoorControlSource() == SA_PERIOD_TRIGGER) mCurEdit = SA_PERI_TRIGGER_DELAY;

        getKnobValue(ANTICLOCKWISE);
        break;
    case SA_EXTERN_GATELENGTH_LEFT:
    case SA_RF_GATELENGTH_LEFT:
    case SA_PERI_GATELENGTH_LEFT:
        if(mControl->getDoorControlSource() == SA_EXTERN_TRIGGER) mCurEdit = SA_EXTERN_DOORWIDTH;
#if !AFTERGATESWEEPCHANGED
        else if(mControl->getDoorControlSource() == SA_RFBURST_TRIGGER) mCurEdit = SA_RFBURST_DOORWIDTH;
#endif
        else if(mControl->getDoorControlSource() == SA_PERIOD_TRIGGER) mCurEdit = SA_PERI_DOOR_WIDTH;

        getKnobValue(CLOCKWISE);
        break;
    case SA_EXTERN_GATELENGTH_RIGHT:
    case SA_RF_GATELENGTH_RIGHT:
    case SA_PERI_GATELENGTH_RIGHT:
        if(mControl->getDoorControlSource() == SA_EXTERN_TRIGGER) mCurEdit = SA_EXTERN_DOORWIDTH;
#if !AFTERGATESWEEPCHANGED
        else if(mControl->getDoorControlSource() == SA_RFBURST_TRIGGER) mCurEdit = SA_RFBURST_DOORWIDTH;
#endif
        else if(mControl->getDoorControlSource() == SA_PERIOD_TRIGGER) mCurEdit = SA_PERI_DOOR_WIDTH;

        getKnobValue(ANTICLOCKWISE);
        break;
    default: break;
    }
}

void sa_dialog_doorcontrol::refreshSubmenuDisplay()
{
    qreal value;
    qint32 status;
    QString strInfo;
#if !AFTERGATESWEEPCHANGED
    qint32 mode = -1;
    mode = mControl->getDoorControlSource();
    mode++;
    ui->subWidget->setCurrentIndex(mode);
    mode--;
#else
    qint32 mode = 0;
    mode = mControl->getDoorControlSource();
    if(mode == SA_PERIOD_TRIGGER) ui->subWidget->setCurrentIndex(3);
    else if(mode == SA_EXTERN_TRIGGER) ui->subWidget->setCurrentIndex(1);
#endif
    switch (mode) {
#if !AFTERGATESWEEPCHANGED
    case SA_NONE_SOURCE:
        mControl->setDoorControlSwitch(SA_CLOSE_DCSWEEP);
        break;
#endif
    case SA_EXTERN_TRIGGER:
        /*status = mControl->getLevleEdgeSelect();
        if(status)
        {
            ui->pb_External_Level->setChecked(true);
            ui->pb_External_Edge->setChecked(false);
        }else{
            ui->pb_External_Level->setChecked(false);
            ui->pb_External_Edge->setChecked(true);
        }*/

        status = mControl->getLevleEdgeMode();
        if(!status)
        {
            ui->pb_External_Low->setChecked(true);
            ui->pb_External_High->setChecked(false);
        }else{
            ui->pb_External_Low->setChecked(false);
            ui->pb_External_High->setChecked(true);
        }

        /*status = mControl->getDoorControlSweepMode();
        ui->Extern_SweepModeBox->setCurrentIndex(status);*/

        status = mControl->getDoorControlSwitch();
        ui->pb_Extern_Sweep_Switch->setChecked(status);
        if(status)
            ui->pb_Extern_Sweep_Switch->setText("On");
        else
            ui->pb_Extern_Sweep_Switch->setText("Off");

        /*ui->spinbox_ExternGateDelay->setSuffix(" us");
        ui->spinbox_ExternGateDelay->setMinimum(0.);
        ui->spinbox_ExternGateDelay->setMaximum(20000000.);
        ui->spinbox_ExternGateDelay->setSingleStep(1);
        ui->spinbox_ExternGateDelay->setValue(mControl->getEdgeTrigDely() * 1000.);

        ui->spinbox_ExternGateLength->setSuffix(" us");
        ui->spinbox_ExternGateLength->setMinimum(0.);
        ui->spinbox_ExternGateLength->setMaximum(20000000.);
        ui->spinbox_ExternGateLength->setSingleStep(1);
        ui->spinbox_ExternGateLength->setValue(mControl->getEdgeTrigDoorWidth() * 1000.);*/

        value = mControl->getEdgeTrigDely();
        strInfo = mControl->globalUserVariable->TimeTransformToQstring(value);
        ui->edit_External_TriggerDelay->setText(strInfo);

        value = mControl->getEdgeTrigDoorWidth();
        strInfo = mControl->globalUserVariable->TimeTransformToQstring(value);
        ui->edit_External_DoorWidth->setText(strInfo);

        status = mControl->getEdgeTrigPreventStatus();
        ui->pb_Extern_PreventStatus->setChecked(status);
        if(status)
            ui->pb_Extern_PreventStatus->setText("On");
        else
            ui->pb_Extern_PreventStatus->setText("Off");

        value = mControl->getEdgeTrigPreventTimes();
        strInfo = mControl->globalUserVariable->TimeTransformToQstring(value);
        ui->edit_External_PreventTime->setText(strInfo);

        status = mControl->getGateViewStatus();
        ui->pb_Extern_GateViewStatus->setChecked(status);
        if(status) ui->pb_Extern_GateViewStatus->setText("On");
        else ui->pb_Extern_GateViewStatus->setText("Off");

        /*value = mControl->getGateViewStartTime();
        strInfo = mControl->globalUserVariable->TimeTransformToQstring(value);
        ui->edit_External_GateView_StartTime->setText(strInfo);*/

        break;
#if !AFTERGATESWEEPCHANGED
    case SA_RFBURST_TRIGGER:
        /*status = mControl->getLevleEdgeSelect();
        if(status)
        {
            ui->pb_RFBurst_Level->setChecked(true);
            ui->pb_RFBurst_Edge->setChecked(false);
        }else{
            ui->pb_RFBurst_Level->setChecked(false);
            ui->pb_RFBurst_Edge->setChecked(true);
        }*/

        status = mControl->getLevleEdgeMode();
        if(!status)
        {
            ui->pb_RFBurst_Low->setChecked(true);
            ui->pb_RFBurst_High->setChecked(false);
        }else{
            ui->pb_RFBurst_Low->setChecked(false);
            ui->pb_RFBurst_High->setChecked(true);
        }

        /*status = mControl->getDoorControlSweepMode();
        ui->RFBurst_SweepModeBox->setCurrentIndex(status);*/

        status = mControl->getDoorControlSwitch();
        ui->pb_RFBurst_Sweep_Switch->setChecked(status);
        if(status)
            ui->pb_RFBurst_Sweep_Switch->setText("On");
        else
            ui->pb_RFBurst_Sweep_Switch->setText("Off");

        /*ui->spinbox_RFGateDelay->setSuffix(" us");
        ui->spinbox_RFGateDelay->setMinimum(0.);
        ui->spinbox_RFGateDelay->setMaximum(20000000.);
        ui->spinbox_RFGateDelay->setSingleStep(1);
        ui->spinbox_RFGateDelay->setValue(mControl->getEdgeTrigDely() * 1000.);

        ui->spinbox_RFGateLength->setSuffix(" us");
        ui->spinbox_RFGateLength->setMinimum(0.);
        ui->spinbox_RFGateLength->setMaximum(20000000.);
        ui->spinbox_RFGateLength->setSingleStep(1);
        ui->spinbox_RFGateLength->setValue(mControl->getEdgeTrigDoorWidth() * 1000.);*/


        value = mControl->getEdgeTrigDely();
        strInfo = mControl->globalUserVariable->TimeTransformToQstring(value);
        ui->edit_RFBurst_TriggerDelay->setText(strInfo);

        value = mControl->getEdgeTrigDoorWidth();
        strInfo = mControl->globalUserVariable->TimeTransformToQstring(value);
        ui->edit_RFBurst_DoorWidth->setText(strInfo);

        status = mControl->getEdgeTrigPreventStatus();
        ui->pb_RFBurst_PreventStatus->setChecked(status);
        if(status)
            ui->pb_RFBurst_PreventStatus->setText("On");
        else
            ui->pb_RFBurst_PreventStatus->setText("Off");

        value = mControl->getEdgeTrigPreventTimes();
        strInfo = mControl->globalUserVariable->TimeTransformToQstring(value);
        ui->edit_RFBurst_PreventTime->setText(strInfo);

        value = mControl->getRFBurstTrigLevel();
        strInfo = mControl->globalUserVariable->amptTransformToQstring(SA_DBM,value);
        ui->edit_RFBurst_TriggerLevel->setText(strInfo);

        status = mControl->getGateViewStatus();
        ui->pb_RFBurst_GateViewStatus->setChecked(status);
        if(status) ui->pb_RFBurst_GateViewStatus->setText("On");
        else ui->pb_RFBurst_GateViewStatus->setText("Off");


        /*value = mControl->getGateViewStartTime();
        strInfo = mControl->globalUserVariable->TimeTransformToQstring(value);
        ui->edit_RFBurst_GateView_StartTime->setText(strInfo);*/
        break;
#endif
    case SA_PERIOD_TRIGGER:
        /*status = mControl->getLevleEdgeMode();
        if(!status)
        {
            ui->pb_Period_Low->setChecked(true);
            ui->pb_Period_High->setChecked(false);
        }else{
            ui->pb_Period_Low->setChecked(false);
            ui->pb_Period_High->setChecked(true);
        }*/

        /*status = mControl->getDoorControlSweepMode();
        ui->Period_SweepModeBox->setCurrentIndex(status);*/

        /*status = mControl->getPeriodTrigSynchroSrc();
        ui->Period_SynchSourceBox->setCurrentIndex(status);*/

        status = mControl->getDoorControlSwitch();
        ui->Period_Sweep_Switch->setChecked(status);
        if(status)
            ui->Period_Sweep_Switch->setText("On");
        else
            ui->Period_Sweep_Switch->setText("Off");

        /*ui->spinbox_PerGateDelay->setSuffix(" us");
        ui->spinbox_PerGateDelay->setMinimum(0.);
        ui->spinbox_PerGateDelay->setMaximum(20000000.);
        ui->spinbox_PerGateDelay->setSingleStep(1);
        ui->spinbox_PerGateDelay->setValue(mControl->getEdgeTrigDely() * 1000.);

        ui->spinbox_PerGateLength->setSuffix(" us");
        ui->spinbox_PerGateLength->setMinimum(0.);
        ui->spinbox_PerGateLength->setMaximum(20000000.);
        ui->spinbox_PerGateLength->setSingleStep(1);
        ui->spinbox_PerGateLength->setValue(mControl->getEdgeTrigDoorWidth() * 1000.);*/

        value = mControl->getEdgeTrigDely();
        strInfo = mControl->globalUserVariable->TimeTransformToQstring(value);
        ui->edit_Period_TriggerDelay->setText(strInfo);

        value = mControl->getEdgeTrigDoorWidth();
        strInfo = mControl->globalUserVariable->TimeTransformToQstring(value);
        ui->edit_Period_DoorWidth->setText(strInfo);

        /*status = mControl->getEdgeTrigPreventStatus();
        ui->pb_Period_PreventStatus->setChecked(status);
        if(status)
            ui->pb_Period_PreventStatus->setText("On");
        else
            ui->pb_Period_PreventStatus->setText("Off");*/

        /*value = mControl->getEdgeTrigPreventTimes();
        strInfo = mControl->globalUserVariable->TimeTransformToQstring(value);
        ui->edit_Period_PreventTime->setText(strInfo);*/

        value = mControl->getPeriodTrigPeriod();
        strInfo = mControl->globalUserVariable->TimeTransformToQstring(value);
        ui->edit_Period_Period->setText(strInfo);

        /*value = mControl->getPeriodTrigSrcDelay();
        strInfo = mControl->globalUserVariable->TimeTransformToQstring(value);
        ui->edit_Period_SynSrcDelay->setText(strInfo);*/

        /*status = mControl->getPeriodTrigPreventStatus();
        ui->pb_Period_SynSrcPreventStatus->setChecked(status);
        if(status)
            ui->pb_Period_SynSrcPreventStatus->setText("On");
        else
            ui->pb_Period_SynSrcPreventStatus->setText("Off");*/

        /*value = mControl->getPeriodTrigPreventTimes();
        strInfo = mControl->globalUserVariable->TimeTransformToQstring(value);
        ui->edit_Period_SrcPrTime->setText(strInfo);*/

        status = mControl->getGateViewStatus();
        ui->pb_Period_GateViewStatus->setChecked(status);
        if(status) ui->pb_Period_GateViewStatus->setText("On");
        else ui->pb_Period_GateViewStatus->setText("Off");


        /*value = mControl->getGateViewStartTime();
        strInfo = mControl->globalUserVariable->TimeTransformToQstring(value);
        ui->edit_Period_GateView_StartTime->setText(strInfo);*/
        break;
    default:
        break;
    }

    return ;
}

void sa_dialog_doorcontrol::refreshComBoBox()
{
#if !AFTERGATESWEEPCHANGED
    qint32 mode = -1;
    mode = mControl->getDoorControlSource();
    mode++;
#else
    qint32 mode = 0;
    mode = mControl->getDoorControlSource();
#endif

    ui->DoorControlSourceBox->blockSignals(true);
    ui->DoorControlSourceBox->setCurrentIndex(mode);
    ui->DoorControlSourceBox->blockSignals(false);
    return;
}

void sa_dialog_doorcontrol::refreshButton()
{
    qint32 index = mControl->getDoorControlSource();
    if(index == SA_EXTERN_TRIGGER)
    {
        if(mControl->getLevleEdgeSelect() == SA_LEVEL_MODE)
        {
            //ui->edit_External_TriggerDelay->setEnabled(false);
            //ui->edit_External_DoorWidth->setEnabled(false);
            ui->pb_Extern_PreventStatus->setEnabled(false);
            ui->edit_External_PreventTime->setEnabled(false);
            ui->pb_Extern_GateViewStatus->setEnabled(false);
            //ui->edit_External_GateView_StartTime->setEnabled(false);
        }
        else
        {
            //ui->edit_External_TriggerDelay->setEnabled(true);
            //ui->edit_External_DoorWidth->setEnabled(true);
            ui->pb_Extern_PreventStatus->setEnabled(true);
            ui->edit_External_PreventTime->setEnabled(true);
            ui->pb_Extern_GateViewStatus->setEnabled(true);
            //ui->edit_External_GateView_StartTime->setEnabled(true);
        }
    }
#if !AFTERGATESWEEPCHANGED
    else if(index == SA_RFBURST_TRIGGER)
    {
        if(mControl->getLevleEdgeSelect() == SA_LEVEL_MODE)
        {
            //ui->edit_RFBurst_TriggerDelay->setEnabled(false);
            //ui->edit_RFBurst_DoorWidth->setEnabled(false);
            ui->pb_RFBurst_PreventStatus->setEnabled(false);
            ui->edit_RFBurst_PreventTime->setEnabled(false);
            ui->pb_RFBurst_GateViewStatus->setEnabled(false);
            //ui->edit_RFBurst_GateView_StartTime->setEnabled(false);
        }
        else
        {
            //ui->edit_RFBurst_TriggerDelay->setEnabled(true);
            //ui->edit_RFBurst_DoorWidth->setEnabled(true);
            ui->pb_RFBurst_PreventStatus->setEnabled(true);
            ui->edit_RFBurst_PreventTime->setEnabled(true);
            ui->pb_RFBurst_GateViewStatus->setEnabled(true);
            //ui->edit_RFBurst_GateView_StartTime->setEnabled(true);
        }
    }
#endif
}

void sa_dialog_doorcontrol::keyPressEvent(QKeyEvent *event)
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
            this->close();
        return;
    case Qt::Key_Shift:
        QApplication::sendEvent(this->parent(),event);
//        if(mControl->globalUserVariable->bShiftKeyPressed)
//            mControl->globalUserVariable->bShiftKeyPressed = false;
//        else
//            mControl->globalUserVariable->bShiftKeyPressed = true;
//        this->close();
        return;
    default:
        //if(mInputDialog) QApplication::sendEvent(mInputDialog,event);
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
            mInputDialog->close();
        getKnobValue(CLOCKWISE);
        break;
    case Qt::Key_F3:
        if(mInputDialog)
            mInputDialog->close();
        getKnobValue(ANTICLOCKWISE);
        break;
    default:
        if(mInputDialog) QApplication::sendEvent(mInputDialog,event);
        break;
    }
}

qreal sa_dialog_doorcontrol::getTimeStep(qreal time)
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

void sa_dialog_doorcontrol::getKnobValue(qint32 mode)
{
    qreal mStep;
    qreal mValue;
    switch (mCurEdit)
    {
    case SA_EXTERN_TRIGGER_DELAY:
    case SA_RFBURST_TRIGGER_DELAY:
    case SA_PERI_TRIGGER_DELAY:
        mValue=mControl->getEdgeTrigDely();
        mStep = getTimeStep(mValue);
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        mControl->setEdgeTrigDely(mValue);
        break;
    case SA_RFBURST_TRIGGER_LEVEL:
        mStep = REF_STEP;
        mValue=mControl->getRFBurstTrigLevel();
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        mControl->setRFBurstTrigLevel(mValue);
        break;
    case SA_EXTERN_DOORWIDTH:
    case SA_RFBURST_DOORWIDTH:
    case SA_PERI_DOOR_WIDTH:
        mValue=mControl->getEdgeTrigDoorWidth();
        mStep = getTimeStep(mValue);
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        mControl->setEdgeTrigDoorWidth(mValue);
        break;
    case SA_EXTERN_PREVENT_TIME:
    case SA_RFBURST_PREVENT_TIME:
    case SA_PERI_PREVENT_TIME:
        mValue=mControl->getEdgeTrigPreventTimes();
        mStep = getTimeStep(mValue);
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        mControl->setEdgeTrigPreventTimes(mValue);
        break;
    case SA_PERI_PERIOD:
        mValue=mControl->getPeriodTrigPeriod();
        mStep = getTimeStep(mValue);
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        mControl->setPeriodTrigPeriod(mValue);
        break;
    case SA_PERI_SYN_SOURCE_DELAY:
        mValue=mControl->getPeriodTrigSrcDelay();
        mStep = getTimeStep(mValue);
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        mControl->setPeriodTrigSrcDelay(mValue);
        break;
    case SA_PERI_SYN_SOURCE_PREVENT_TIME:
        mValue=mControl->getPeriodTrigPreventTimes();
        mStep = getTimeStep(mValue);
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        mControl->setPeriodTrigPreventTimes(mValue);
        break;
    case SA_EXTERN_GATEVIEW_STARTTIME:
    case SA_RFBURST_GATEVIEW_STARTTIME:
    case SA_PERI_GATEVIEW_STARTTIME:
        break;
    }
    initDisplay();
    return;
}

void sa_dialog_doorcontrol::showInputDialog(qint32 index)
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

void sa_dialog_doorcontrol::initDisplay()
{
    refreshSubmenuDisplay();
    refreshComBoBox();
    refreshButton();

    return ;
}

void sa_dialog_doorcontrol::on_DoorControlSourceBox_currentIndexChanged(int index)
{
#if !AFTERGATESWEEPCHANGED
    mControl->setDoorControlSource(--index);
#else
    mControl->setDoorControlSource(index);
#endif
    initDisplay();
}

/*void sa_dialog_doorcontrol::on_pb_External_Level_clicked()
{
    ui->pb_External_Level->setChecked(true);
    ui->pb_External_Edge->setChecked(false);
    mControl->setLevleEdgeSelect(SA_LEVEL_MODE);
    initDisplay();
}*/

/*void sa_dialog_doorcontrol::on_pb_External_Edge_clicked()
{
    ui->pb_External_Level->setChecked(false);
    ui->pb_External_Edge->setChecked(true);
    mControl->setLevleEdgeSelect(SA_EDGE_MODE);
    initDisplay();
}*/

void sa_dialog_doorcontrol::on_pb_External_Low_clicked()
{
    ui->pb_External_Low->setChecked(true);
    ui->pb_External_High->setChecked(false);
    mControl->setLevleEdgeMode(SA_NEGATIVE_VALUE);
    initDisplay();
}

void sa_dialog_doorcontrol::on_pb_External_High_clicked()
{
    ui->pb_External_High->setChecked(true);
    ui->pb_External_Low->setChecked(false);
    mControl->setLevleEdgeMode(SA_POSITIVE_VALUE);
    initDisplay();
}

/*void sa_dialog_doorcontrol::on_Extern_SweepModeBox_currentIndexChanged(int index)
{
    mControl->setDoorControlSweepMode(index);
    initDisplay();
}*/

void sa_dialog_doorcontrol::on_pb_Extern_Sweep_Switch_clicked(bool checked)
{
    mControl->setDoorControlSwitch(checked);
    initDisplay();
}

void sa_dialog_doorcontrol::on_pb_Extern_PreventStatus_clicked(bool checked)
{
    mControl->setEdgeTrigPreventStatus(checked);
    initDisplay();
}

/*void sa_dialog_doorcontrol::on_pb_RFBurst_Level_clicked()
{
    ui->pb_RFBurst_Level->setChecked(true);
    ui->pb_RFBurst_Edge->setChecked(false);
    mControl->setLevleEdgeSelect(SA_LEVEL_MODE);
    initDisplay();
}*/

/*void sa_dialog_doorcontrol::on_pb_RFBurst_Edge_clicked()
{
    ui->pb_RFBurst_Level->setChecked(false);
    ui->pb_RFBurst_Edge->setChecked(true);
    mControl->setLevleEdgeSelect(SA_EDGE_MODE);
    initDisplay();
}*/

void sa_dialog_doorcontrol::on_pb_RFBurst_Low_clicked()
{
    ui->pb_RFBurst_Low->setChecked(true);
    ui->pb_RFBurst_High->setChecked(false);
    mControl->setLevleEdgeMode(SA_NEGATIVE_VALUE);
    initDisplay();
}

void sa_dialog_doorcontrol::on_pb_RFBurst_High_clicked()
{
    ui->pb_RFBurst_Low->setChecked(false);
    ui->pb_RFBurst_High->setChecked(true);
    mControl->setLevleEdgeMode(SA_POSITIVE_VALUE);
    initDisplay();
}

/*void sa_dialog_doorcontrol::on_RFBurst_SweepModeBox_currentIndexChanged(int index)
{
    mControl->setDoorControlSweepMode(index);
    initDisplay();
}*/

void sa_dialog_doorcontrol::on_pb_RFBurst_Sweep_Switch_clicked(bool checked)
{
    mControl->setDoorControlSwitch(checked);
    initDisplay();
}

void sa_dialog_doorcontrol::on_pb_RFBurst_PreventStatus_clicked(bool checked)
{
    mControl->setEdgeTrigPreventStatus(checked);
    initDisplay();
}

/*void sa_dialog_doorcontrol::on_pb_Period_Low_clicked(bool checked)
{
    mControl->setLevleEdgeMode(!checked);
    initDisplay();
}*/

void sa_dialog_doorcontrol::on_pb_Period_High_clicked(bool checked)
{
    mControl->setLevleEdgeMode(checked);
    initDisplay();
}

/*void sa_dialog_doorcontrol::on_Period_SweepModeBox_currentIndexChanged(int index)
{
    mControl->setDoorControlSweepMode(index);
    initDisplay();
}*/

/*void sa_dialog_doorcontrol::on_Period_SynchSourceBox_currentIndexChanged(int index)
{
    mControl->setPeriodTrigSynchroSrc(index);
    initDisplay();
}*/

void sa_dialog_doorcontrol::on_Period_Sweep_Switch_clicked(bool checked)
{
    mControl->setDoorControlSwitch(checked);
    initDisplay();
}

/*void sa_dialog_doorcontrol::on_pb_Period_PreventStatus_clicked(bool checked)
{
    mControl->setEdgeTrigPreventStatus(checked);
    initDisplay();
}*/

/*void sa_dialog_doorcontrol::on_pb_Period_SynSrcPreventStatus_clicked(bool checked)
{
    mControl->setPeriodTrigPreventStatus(checked);
    initDisplay();
}*/

void sa_dialog_doorcontrol::on_pb_cancel_clicked()
{
    emit pbCancelClicked();
    this->close();
}

void sa_dialog_doorcontrol::on_finishEntry(qint32 index)
{
    qint32 mEditIndex,mode;
    disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
    mInputDialog = NULL;

    mode = mControl->getDoorControlSource();

    switch(index)
    {
    case SA_INPUT_DOORCTRL_TRIGDELAY:
        if(mode == SA_EXTERN_TRIGGER) mEditIndex = SA_EXTERN_TRIGGER_DELAY;
#if !AFTERGATESWEEPCHANGED
        else if(mode == SA_RFBURST_TRIGGER) mEditIndex = SA_RFBURST_TRIGGER_DELAY;
#endif
        else if(mode == SA_PERIOD_TRIGGER) mEditIndex = SA_PERI_TRIGGER_DELAY;
        break;
    case SA_INPUT_DOORCTRL_DOORWID:
        if(mode == SA_EXTERN_TRIGGER) mEditIndex = SA_EXTERN_DOORWIDTH;
#if !AFTERGATESWEEPCHANGED
        else if(mode == SA_RFBURST_TRIGGER) mEditIndex = SA_RFBURST_DOORWIDTH;
#endif
        else if(mode == SA_PERIOD_TRIGGER) mEditIndex = SA_PERI_DOOR_WIDTH;
        break;
    case SA_INPUT_DOORCTRL_PRVTTIME:
        if(mode == SA_EXTERN_TRIGGER) mEditIndex = SA_EXTERN_PREVENT_TIME;
#if !AFTERGATESWEEPCHANGED
        else if(mode == SA_RFBURST_TRIGGER) mEditIndex = SA_RFBURST_PREVENT_TIME;
#endif
        else if(mode == SA_PERIOD_TRIGGER) mEditIndex = SA_PERI_PREVENT_TIME;
        break;
    case SA_INPUT_DOORCTRL_GATEVIEW_STARTTIME:
        if(mode == SA_EXTERN_TRIGGER) mEditIndex = SA_EXTERN_GATEVIEW_STARTTIME;
#if !AFTERGATESWEEPCHANGED
        else if(mode == SA_RFBURST_TRIGGER) mEditIndex = SA_RFBURST_GATEVIEW_STARTTIME;
#endif
        else if(mode == SA_PERIOD_TRIGGER) mEditIndex = SA_PERI_GATEVIEW_STARTTIME;
        break;
    case SA_INPUT_DOORCTRL_TRIGGERLEVEL:      mEditIndex = SA_RFBURST_TRIGGER_LEVEL;        break;
    case SA_INPUT_DOORCTRL_PERI_PERIOD:       mEditIndex = SA_PERI_PERIOD;                  break;
    case SA_INPUT_DOORCTRL_PERI_SYNSRCDELAY:  mEditIndex = SA_PERI_SYN_SOURCE_DELAY;        break;
    case SA_INPUT_DOORCTRL_PERI_SRCPRVTTIME:  mEditIndex = SA_PERI_SYN_SOURCE_PREVENT_TIME; break;
    default: break;
    }
    mEditList.value(mEditIndex)->setFocus();
    initDisplay();
    return ;
}

void sa_dialog_doorcontrol::on_getComboBoxFocus(SA_Combobox* mBox)
{
    QString qss = "#sa_dialog_doorcontrol[status=\"indoor\"] QComboBox{background-image: url(:/sa/image/dropdown_click.png);}\
                   #sa_dialog_doorcontrol[status=\"outdoor\"] QComboBox{background-image: url(:/sa/image/dropdown_click.png);}\
                   #sa_dialog_doorcontrol[status=\"night\"] QComboBox{background-image: url(:/sa/image/night/dropdown_click.png);}";

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

void sa_dialog_doorcontrol::on_getFocus(SA_LineEdit* mEdit)
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

void sa_dialog_doorcontrol::edit_clicked()
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
    case SA_EXTERN_TRIGGER_DELAY:
    case SA_RFBURST_TRIGGER_DELAY:
    case SA_PERI_TRIGGER_DELAY:
        showInputDialog(SA_INPUT_DOORCTRL_TRIGDELAY);
        break;
    case SA_EXTERN_DOORWIDTH:      //s,ms,us,ns
    case SA_RFBURST_DOORWIDTH:
    case SA_PERI_DOOR_WIDTH:
        showInputDialog(SA_INPUT_DOORCTRL_DOORWID);
        break;
    case SA_EXTERN_PREVENT_TIME: //s,ms,us,ns
    case SA_RFBURST_PREVENT_TIME:
    case SA_PERI_PREVENT_TIME:
        showInputDialog(SA_INPUT_DOORCTRL_PRVTTIME);
        break;
    case SA_EXTERN_GATEVIEW_STARTTIME:
    case SA_RFBURST_GATEVIEW_STARTTIME:
    case SA_PERI_GATEVIEW_STARTTIME:
        showInputDialog(SA_INPUT_DOORCTRL_GATEVIEW_STARTTIME);
        break;
    case SA_RFBURST_TRIGGER_LEVEL:
        showInputDialog(SA_INPUT_DOORCTRL_TRIGGERLEVEL);
        break;
    case SA_PERI_PERIOD:
        showInputDialog(SA_INPUT_DOORCTRL_PERI_PERIOD);
        break;
    case SA_PERI_SYN_SOURCE_DELAY:
        showInputDialog(SA_INPUT_DOORCTRL_PERI_SYNSRCDELAY);
        break;
    case SA_PERI_SYN_SOURCE_PREVENT_TIME:
        showInputDialog(SA_INPUT_DOORCTRL_PERI_SRCPRVTTIME);
        break;
    default:
        break;
    }
    return ;
}

void sa_dialog_doorcontrol::on_pb_Extern_GateViewStatus_clicked(bool checked)
{
    /*if(mControl->getDoorControlSwitch() == SA_CLOSE_DCSWEEP)
        ui->pb_Extern_GateViewStatus->setChecked(false);
    else
        mControl->setGateViewStatus(checked);*/
    mControl->setGateViewStatus(checked);
    initDisplay();
}

void sa_dialog_doorcontrol::on_pb_RFBurst_GateViewStatus_clicked(bool checked)
{
    /*if(mControl->getDoorControlSwitch() == SA_CLOSE_DCSWEEP)
        ui->pb_RFBurst_GateViewStatus->setChecked(false);
    else
        mControl->setGateViewStatus(checked);*/
    mControl->setGateViewStatus(checked);
    initDisplay();
}

void sa_dialog_doorcontrol::on_pb_Period_GateViewStatus_clicked(bool checked)
{
    /*if(mControl->getDoorControlSwitch() == SA_CLOSE_DCSWEEP)
        ui->pb_Period_GateViewStatus->setChecked(false);
    else
        mControl->setGateViewStatus(checked);*/
    mControl->setGateViewStatus(checked);
    initDisplay();
}

/*void sa_dialog_doorcontrol::on_spinbox_PerGateDelay_valueChanged(double arg1)
{
    mControl->setEdgeTrigDely(arg1/1000.);
}

void sa_dialog_doorcontrol::on_spinbox_PerGateLength_valueChanged(double arg1)
{
    mControl->setEdgeTrigDoorWidth(arg1/1000.);
}

void sa_dialog_doorcontrol::on_spinbox_ExternGateDelay_valueChanged(double arg1)
{
    mControl->setEdgeTrigDely(arg1/1000.);
}

void sa_dialog_doorcontrol::on_spinbox_ExternGateLength_valueChanged(double arg1)
{
    mControl->setEdgeTrigDoorWidth(arg1/1000.);
}

void sa_dialog_doorcontrol::on_spinbox_RFGateDelay_valueChanged(double arg1)
{
    mControl->setEdgeTrigDely(arg1/1000.);
}

void sa_dialog_doorcontrol::on_spinbox_RFGateLength_valueChanged(double arg1)
{
    mControl->setEdgeTrigDoorWidth(arg1/1000.);
}*/
