#include "sa_dialog_displaysetup.h"
#include "ui_sa_dialog_displaysetup.h"
#include "sa_applicationcontrol.h"
#include "sa_dialog_digitinput.h"
#include "sa_combobox.h"
#include "sa_dialog_doorcontrol.h"

#define GATESWEEP_SHOW 1

SA_Dialog_DisplaySetup::SA_Dialog_DisplaySetup(controlInterface *interface, user_variable *puser_variable, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SA_Dialog_DisplaySetup)
{
    ui->setupUi(this);
    mControl = interface;
    mCurEdit = 0;
    globalUserVariable = puser_variable;

    setProperty("status",qssMode[mControl->GetDisplayMode()]);
    initMap();
    initWidget();
    initDisplay();
    //setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/);
    mInputDialog = NULL;
    mDoorControl = NULL;
    hide();
}
/**
 * @brief  Init widget.Set button or other control postion.
 * @param  void
 * @author Tony
 * @since 2019-05-20
*/
void SA_Dialog_DisplaySetup::initWidget()
{
    ui->lblSweepTime_2->setVisible(false);
    ui->pb_DotSweepTime_Auto->setVisible(false);
    ui->pb_DotSweepTime_Manual->setVisible(false);
    ui->edit_DotSweepTime->setVisible(false);

    qint32 mMode = mControl->getCurrentMode();
    if(SA_SPURIOUS_EMISSION_MASK_MODE == mMode||\
            SA_SPECTRUM_EMISSION_MASK_MODE == mMode)
    {
        ui->lblSweepTime->setVisible(false);
        ui->pb_SweepTime_Auto->setVisible(false);
        ui->pb_SweepTime_Manual->setVisible(false);
        ui->edit_SweepTime->setVisible(false);

        ui->lblSweepMode->move(18,67);;
        ui->pb_conti->move(94,68);
        ui->pb_single->move(165,68);
        ui->pb_Sweep_Once->move(17,112);

        on_getFocus(mEditList.value(SA_INPUT_SWEEP_TIME));
        mCurEdit = SA_INPUT_SWEEP_TIME;
    }else
    {
        ui->lblSweepTime->setVisible(true);
        ui->pb_SweepTime_Auto->setVisible(true);
        ui->pb_SweepTime_Manual->setVisible(true);
        ui->edit_SweepTime->setVisible(true);

        ui->lblSweepMode->move(18,162);;
        ui->pb_conti->move(94,162);
        ui->pb_single->move(165,162);
        ui->pb_Sweep_Once->move(17,212);

        on_getFocus(mEditList.value(SA_INPUT_SWEEP_TIME));
        mCurEdit = SA_INPUT_SWEEP_TIME;
    }

    on_getFocus(mEditList.value(mCurEdit));
    return;
}

SA_Dialog_DisplaySetup::~SA_Dialog_DisplaySetup()
{
    if(mInputDialog)
    {
        delete mInputDialog;
        mInputDialog = NULL;
    }
    delete ui;
}
/**
 * @brief  Initialize map of indexes and controls.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_DisplaySetup::initMap()
{
    mEditList.insert(SA_INPUT_SWEEP_TIME,ui->edit_SweepTime);
    mEditList.insert(SA_INPUT_DOT_SWEEP_TIME,ui->edit_DotSweepTime);

    connect(ui->edit_SweepTime,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
    connect(ui->edit_DotSweepTime,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));

    return ;
}

void SA_Dialog_DisplaySetup::on_getFocus(SA_LineEdit* mEdit)
{
    if(!mEditList.contains(mCurEdit)) return;
    QString qss =QString("outline: none;border:2px solid rgba(162,115,0,1);padding:6px 6px 5px 8px;");
    //if(mCurEdit<0 && mEditList.contains(mCurEdit))
    //{
        mEditList.value(mCurEdit)->setStyleSheet("");
    //}
    mEdit->setStyleSheet(qss);
    mCurEdit = mEditList.key(mEdit);
    this->repaint();
    return;
}
void SA_Dialog_DisplaySetup::on_getComboBoxFocus(SA_Combobox* mBox)
{
    //if(mCurEdit<0 && mBoxList.contains(mCurEdit))
    //{
        mBoxList.value(mCurEdit)->setStyleSheet("");
    //}
    mBox->setStyleSheet("QComboBox{background-image: url(:/sa/image/dropdown_click.png);}");
    //mCurEdit = mBoxList.key(mBox);
    return;
}


/**
 * @brief  Init the display.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_DisplaySetup::initDisplay()
{
#if GATESWEEP_SHOW
    //Johnson 191203
    if(globalUserVariable->currentMode != SA_SPAN_MODE) ui->pb_DoorCtrlSweep->setVisible(false);
    else
    {
        if(globalUserVariable->gZeroSpanAction == SA_ON)
        {
            if(mControl->getGateViewStatus() == SA_GATE_VIEW_CLOSE)
                ui->pb_DoorCtrlSweep->setVisible(false);
            else
                ui->pb_DoorCtrlSweep->setVisible(true);
        }
        else
            ui->pb_DoorCtrlSweep->setVisible(true);
    }
#else
    ui->pb_DoorCtrlSweep->setVisible(false);
#endif

    //Johnson 190925
    if(globalUserVariable->ganamode == 3)
    {
        mControl->blockSignals(true);
		//Tony 12-06 set failed because this interferce isn't allowed when "3 == SA_sm_config_sweep->sweepMode"
        //mControl->setAutoSweepTimeStatus(SA_AUTO);
        globalUserVariable->gAutoSweepTime = SA_AUTO;
        mControl->setAutoDotSweepTime(SA_AUTO);
        mControl->blockSignals(false);
    }
    ui->lblFixedDotSweepTime->setVisible(false);
    ui->pb_FixedDotSweepTime->setVisible(false);
    refreshEditDisplay(SA_INPUT_DOT_SWEEP_TIME);
    refreshEditDisplay(SA_INPUT_SWEEP_TIME);
    refreshEditDisplay(SA_INPUT_ZEROSPAN_TIME);
    refreshEditDisplay(SA_INPUT_PERIOD_TIME);
    refreshButtonDisplay();
    return ;
}

/**
 * @brief  Refresh the corresponding line edit according to the index.
 * @param  index  The index of current editline.
 * @author Tony
 * @since  2018-12-24
*/
void SA_Dialog_DisplaySetup::refreshEditDisplay(quint32 index)
{
    QString strGab;
    qreal   value;
    if(!mEditList.contains(index))
        return;
    switch (index)
    {
    case SA_INPUT_SWEEP_TIME:
        value = mControl->getSweepTime();
        strGab = globalUserVariable->TimeTransformToQstring(value);
        break;
    case SA_INPUT_ZEROSPAN_TIME:
        value = mControl->getZeroSpanTime();
        strGab = globalUserVariable->TimeTransformToQstring(value);
        break;
    case SA_INPUT_PERIOD_TIME:
//        value = mControl->getSweepTime();
//        strGab = globalUserVariable->TimeTransformToQstring(value);
        break;
    case SA_INPUT_DOT_SWEEP_TIME:
        value = mControl->getDotSweepTime();
        strGab = globalUserVariable->TimeTransformToQstring(value);
        break;
    default: break;
    }
    mEditList.find(index).value()->setText(strGab);
    return ;
}

/**
 * @brief  Refresh button status.
 * @author Tony
 * @since  2018-12-24
*/
void SA_Dialog_DisplaySetup::refreshButtonDisplay()
{
    qint32 mAutoSweep = mControl->getAutoSweepTimeStatus();
    qint32 mSweepMode = mControl->getSweepType();
    qint32 mAutoDotSweepTime = mControl->getAutoDotSweepTimeStatus();
    if(mAutoSweep)
    {
        ui->pb_SweepTime_Auto->setChecked(true);
        if(!(ui->pb_FixedDotSweepTime->isEnabled())) ui->pb_FixedDotSweepTime->setEnabled(true);
    }else
    {
        ui->pb_SweepTime_Manual->setChecked(true);
        if(ui->pb_FixedDotSweepTime->isEnabled()) ui->pb_FixedDotSweepTime->setEnabled(false);
    }
    if(!mSweepMode)
    {
        ui->pb_conti->setChecked(true);
    }else
    {
        ui->pb_single->setChecked(true);
    }

    if(mAutoDotSweepTime)
    {
        ui->pb_DotSweepTime_Auto->setChecked(true);
    }
    else
    {
        ui->pb_DotSweepTime_Manual->setChecked(true);
    }

    if(globalUserVariable->gFixDotSweepTime == SA_ON)
    {
        ui->pb_FixedDotSweepTime->setChecked(true);
    }
    else
    {
        ui->pb_FixedDotSweepTime->setChecked(false);
    }
    if(globalUserVariable->gAutoSweepTime == SA_OFF)
    {
        ui->pb_FixedDotSweepTime->setEnabled(false);
    }


    return ;
}

void SA_Dialog_DisplaySetup::on_pb_conti_clicked()
{
    mControl->setSweepType(SA_CONT);
    mControl->setSuspendFunc(0);
    return ;
}

void SA_Dialog_DisplaySetup::on_pb_single_clicked()
{
    mControl->setSweepType(SA_SINGLE);
    return ;
}

void SA_Dialog_DisplaySetup::on_pb_cancel_clicked()
{
    hideWidget();
    return;
}

void SA_Dialog_DisplaySetup::on_pb_SweepTime_Auto_clicked()
{
    mControl->setAutoSweepTimeStatus(SA_AUTO);

    if(!(ui->pb_FixedDotSweepTime->isEnabled())) ui->pb_FixedDotSweepTime->setEnabled(true);//Johnson

    initDisplay();
//    ui->edit_SweepTime->setEnabled(false);
    return;
}

void SA_Dialog_DisplaySetup::on_pb_SweepTime_Manual_clicked()
{
    //Johnson
    if(globalUserVariable->ganamode == 3)
    {
        ui->pb_SweepTime_Manual->setChecked(false);
        ui->pb_SweepTime_Auto->setChecked(true);
        return;
    }
    mControl->setFixSweepMode(SA_OFF);
    ui->pb_FixedDotSweepTime->setEnabled(false);

    mControl->setAutoSweepTimeStatus(SA_MANUAL);

    initDisplay();
//    ui->edit_SweepTime->setEnabled(true);
    return ;
}

void SA_Dialog_DisplaySetup::on_edit_SweepTime_clicked()
{
    showInputDialog(SA_INPUT_SWEEP_TIME);

    initDisplay();

    return;
}

/**
 * @brief  Slot of finish entry.
 * @param  void
 * @author Tony
 * @since 2018-12-21
*/
void SA_Dialog_DisplaySetup::on_finishEntry(qint32 index)
{
    disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
    mInputDialog = NULL;
    if(mEditList.contains(index))
    {
        mEditList.value(index)->setFocus();
        initDisplay();
    }
    return ;
}
/**
 * @brief  show digit input dialog
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_DisplaySetup::showInputDialog(qint32 index)
{
    if(!mEditList.contains(index))
        return;
    if(mInputDialog)
    {
        mInputDialog->initDisplay(index);
        mInputDialog->setFocus();
    }else
    {
        mInputDialog = new SA_Dialog_DigitInput(mControl,globalUserVariable,index,this);
        mInputDialog->setFocus();
        mInputDialog->setGeometry(mapToGlobal(QPoint(0,0)).x(),mapToGlobal(QPoint(0,0)).y(),DIGITINPUT_WIDTH,DIGITINPUT_HEIGHT);
        connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
        mInputDialog->show();
    }
    return ;
}
void SA_Dialog_DisplaySetup::on_pb_Sweep_Once_clicked()
{
    ui->pb_single->setChecked(true);
    mControl->setSweepType(SA_SINGLE);
    return ;
}
void SA_Dialog_DisplaySetup::keyPressEvent(QKeyEvent *event)
{
  qint32 keyvalue = event->key();
  if(event->key() == Qt::Key_PowerOff)
  {
      if(!event->isAutoRepeat())
          QApplication::sendEvent(this->parent(),event);
      return;
  }
  switch(keyvalue){
  case Qt::Key_Escape:
      if(mInputDialog)
      {
          mInputDialog->close();
      }
      else
      {
          hideWidget();
      }
      return;
  case Qt::Key_Shift:
      if(globalUserVariable->bShiftKeyPressed)
          globalUserVariable->bShiftKeyPressed = false;
      else
          globalUserVariable->bShiftKeyPressed = true;
      hideWidget();
      return;
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
  return ;
}
qreal SA_Dialog_DisplaySetup::getTimeStep(qreal time)
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
void SA_Dialog_DisplaySetup::getKnobValue(qint32 mode)
{
    qreal mStep;
    qreal mValue;
    mStep = 1;
    switch (mCurEdit) {
    case SA_INPUT_SWEEP_TIME:
        //Johnson 190925
        if(globalUserVariable->ganamode == 3)
        {
             break;
        }

        mValue = mControl->getSweepTime();
        mStep = getTimeStep(mValue);
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        if(mValue < 0) mValue=0;
        mControl->setSweepTime(mValue);
        refreshEditDisplay(SA_INPUT_SWEEP_TIME);
        refreshButtonDisplay();
        break;
    case SA_INPUT_ZEROSPAN_TIME:
        mValue = mControl->getSweepTime();
        mStep = getTimeStep(mValue);
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        if(mValue < 0) mValue=0;
        mControl->setSweepTime(mValue);
        refreshEditDisplay(SA_INPUT_ZEROSPAN_TIME);
        break;
    case SA_INPUT_PERIOD_TIME:
        mValue = mControl->getSweepTime();
        mStep = getTimeStep(mValue);
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        if(mValue < 0) mValue=0;
        mControl->setSweepTime(mValue);
        refreshEditDisplay(SA_INPUT_PERIOD_TIME);
        break;
    }
}

void SA_Dialog_DisplaySetup::on_edit_DotSweepTime_clicked()
{
    showInputDialog(SA_INPUT_DOT_SWEEP_TIME);
    initDisplay();
}

void SA_Dialog_DisplaySetup::on_pb_DotSweepTime_Auto_clicked()
{
    mControl->setAutoDotSweepTime(SA_AUTO);
    initDisplay();
}

void SA_Dialog_DisplaySetup::on_pb_DotSweepTime_Manual_clicked()
{
    if(globalUserVariable->ganamode == 3)
    {
        ui->pb_DotSweepTime_Auto->setChecked(true);
        ui->pb_DotSweepTime_Manual->setChecked(false);
        return;
    }
    mControl->setAutoDotSweepTime(SA_MANUAL);
    initDisplay();
}

void SA_Dialog_DisplaySetup::on_pb_FixedDotSweepTime_clicked()
{
    if(globalUserVariable->ganamode == 3) return;

    if(ui->pb_FixedDotSweepTime->isChecked())
        mControl->setFixSweepMode(SA_ON);
    else
        mControl->setFixSweepMode(SA_OFF);

    initDisplay();
}

void SA_Dialog_DisplaySetup::on_pb_FixedDotSweepTime_toggled(bool checked)
{
    if(checked)
    {
        ui->pb_FixedDotSweepTime->setText("On");
    }else
    {
        ui->pb_FixedDotSweepTime->setText("Off");
    }
}
void SA_Dialog_DisplaySetup::showWidget()
{
    initDisplay();
    show();
}

void SA_Dialog_DisplaySetup::hideWidget()
{
    //Johnson 191203
    if(globalUserVariable->gZeroSpanAction == SA_ON)
        mControl->setGateViewStatus(SA_GATE_VIEW_CLOSE);

    hide();
    if(mInputDialog)
    {
        disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
        delete mInputDialog;
        mInputDialog = NULL;
    }
    if(mDoorControl)
    {
        mDoorControl->close();
//        delete mDoorControl;
//        mDoorControl = NULL;
    }
    emit mDialogHide();
    return;
}

void SA_Dialog_DisplaySetup::on_pb_DoorCtrlSweep_clicked()
{
    mDoorControl = new sa_dialog_doorcontrol(mControl,this);
    mDoorControl->setGeometry(0,0,252,646);
    mDoorControl->show();
    connect(mDoorControl,SIGNAL(destroyed()),this,SLOT(subMenuDestroy()));
    connect(mDoorControl,SIGNAL(pbCancelClicked()),this,SLOT(gateSweepCancel()));
}

void SA_Dialog_DisplaySetup::gateSweepCancel()
{
    initDisplay();
}

void SA_Dialog_DisplaySetup::subMenuDestroy()
{
    if(mDoorControl)
    {
        disconnect(mDoorControl,SIGNAL(destroyed()),this,SLOT(subMenuDestroy()));
        disconnect(mDoorControl,SIGNAL(pbCancelClicked()),this,SLOT(gateSweepCancel()));
        mDoorControl = NULL;
    }
}

void SA_Dialog_DisplaySetup::gateSweepDisplay()
{
    if(mDoorControl) mDoorControl->initDisplay();
}
