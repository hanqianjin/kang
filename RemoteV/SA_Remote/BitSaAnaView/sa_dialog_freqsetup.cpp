#include "sa_dialog_freqsetup.h"
#include "ui_sa_dialog_freqsetup.h"
#include "sa_applicationcontrol.h"
#include "sa_dialog_digitinput.h"
#include "sa_dialog_ch_std.h"
SA_Dialog_FreqSetup::SA_Dialog_FreqSetup(controlInterface *interface, user_variable *puser_variable, QWidget *parent) :
    mControl(interface),
    globalUserVariable(puser_variable),
    mCurEdit(0),
    QWidget(parent),

    ui(new Ui::SA_Dialog_FreqSetup)
{
    mParentWin = parent;
    mInputDialog = NULL;
    mCHStdDialog = NULL;
    ui->setupUi(this);
    setProperty("status",qssMode[mControl->GetDisplayMode()]);
    initMap();
    initWidget();
    initDisplay();
    //setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | /*Qt::Dialog|*/Qt::CustomizeWindowHint);
    hide();
}

SA_Dialog_FreqSetup::~SA_Dialog_FreqSetup()
{
    digitInputClose();
    delete ui;
}

/**
 * @brief  Init widget.Set button or other control postion.
 * @param  void
 * @author Tony
 * @since  2019-05-20
 * @note   Must be placed after "initMap()";
*/
void SA_Dialog_FreqSetup::initWidget()
{

    qint32 mMode = mControl->getCurrentMode();
    if(SA_SPURIOUS_EMISSION_MASK_MODE == mMode||\
            SA_SPECTRUM_EMISSION_MASK_MODE == mMode)
    {
        ui->lblCenterFreq->setVisible(false);
        ui->LedCenterFreq->setVisible(false);
        ui->lblStartFreq->setVisible(false);
        ui->LedStartFreq->setVisible(false);
        ui->lblStopFreq->setVisible(false);
        ui->LedStopFreq->setVisible(false);
        ui->lblSpan->setVisible(false);
        ui->LedSpan->setVisible(false);
        ui->pb_FullSpan->setVisible(false);
        ui->pb_ZeroSpan->setVisible(false);
        ui->pb_LastSpan->setVisible(false);
        ui->lblChStandard->setVisible(false);
        ui->LedCHStandard->setVisible(false);
        ui->lblChNumber->setVisible(false);
        ui->LedCHNum->setVisible(false);
        ui->lblChStep->setVisible(false);
        ui->LedCHStep->setVisible(false);
        ui->lblChType->setVisible(false);
        ui->pb_Uplink->setVisible(false);
        ui->pb_Downlink->setVisible(false);


        ui->lblFreqStep->move(18,67);
        ui->LedFreqStep->move(94,67);
        ui->lblFreqOffset->move(18,117);
        ui->LedFreqOffset->move(94,117);

        on_getFocus(mEditList.value(SA_INPUT_FREQ_CF));
        mCurEdit = SA_INPUT_FREQ_CF;
    }
    else if(SA_CHNLPOWER_MEASURE_MODE == mMode || SA_OCCUPIED_BW_MEASURE_MODE == mMode ||
            SA_ACP_MEASURE_MODE == mMode || SA_MULTI_ACP_MODE == mMode)
    {

        ui->lblCenterFreq->setVisible(true);
        ui->LedCenterFreq->setVisible(true);
        ui->lblSpan->setVisible(true);
        ui->LedSpan->setVisible(true);
        ui->pb_FullSpan->setVisible(true);
        ui->pb_ZeroSpan->setVisible(true);
        ui->pb_LastSpan->setVisible(true);

        ui->lblStartFreq->setVisible(false);
        ui->LedStartFreq->setVisible(false);
        ui->lblStopFreq->setVisible(false);
        ui->LedStopFreq->setVisible(false);
        ui->pb_ZeroSpan->setVisible(false);
        ui->lblChStandard->setVisible(false);
        ui->LedCHStandard->setVisible(false);
        ui->lblChNumber->setVisible(false);
        ui->LedCHNum->setVisible(false);
        ui->lblChStep->setVisible(false);
        ui->LedCHStep->setVisible(false);
        ui->lblChType->setVisible(false);
        ui->pb_Uplink->setVisible(false);
        ui->pb_Downlink->setVisible(false);

        ui->lblCenterFreq->move(18,67);
        ui->LedCenterFreq->move(94,67);
        ui->lblFreqStep->move(18,117);
        ui->LedFreqStep->move(94,117);
        ui->lblFreqOffset->move(18,167);
        ui->LedFreqOffset->move(94,167);
        ui->pb_FullSpan->move(18,267);
        ui->pb_LastSpan->move(90,267);
        ui->lblSpan->move(18,217);
        ui->LedSpan->move(94,217);

        on_getFocus(mEditList.value(SA_INPUT_FREQ_CENTER));
        mCurEdit = SA_INPUT_FREQ_CENTER;
    }
    else
    {
        ui->lblCenterFreq->setVisible(true);
        ui->LedCenterFreq->setVisible(true);
        ui->lblStartFreq->setVisible(true);
        ui->LedStartFreq->setVisible(true);
        ui->lblStopFreq->setVisible(true);
        ui->LedStopFreq->setVisible(true);
        ui->lblSpan->setVisible(true);
        ui->LedSpan->setVisible(true);
        ui->pb_FullSpan->setVisible(true);
        ui->pb_ZeroSpan->setVisible(true);
        ui->pb_LastSpan->setVisible(true);
        ui->lblChStandard->setVisible(true);
        ui->LedCHStandard->setVisible(true);
        ui->lblChNumber->setVisible(true);
        ui->LedCHNum->setVisible(true);
        ui->lblChStep->setVisible(true);
        ui->LedCHStep->setVisible(true);
        ui->lblChType->setVisible(true);
        ui->pb_Uplink->setVisible(true);
        ui->pb_Downlink->setVisible(true);

        ui->lblCenterFreq->move(18,67);
        ui->LedCenterFreq->move(94,67);
        ui->lblFreqStep->move(18,217);
        ui->LedFreqStep->move(94,217);
        ui->lblFreqOffset->move(18,267);
        ui->LedFreqOffset->move(94,267);
        ui->pb_FullSpan->move(17,367);
        ui->pb_LastSpan->move(163,367);
        ui->lblSpan->move(18,325);
        ui->LedSpan->move(94,317);
        on_getFocus(mEditList.value(SA_INPUT_FREQ_CENTER));
        mCurEdit = SA_INPUT_FREQ_CENTER;
    }
}

/**
 * @brief  Close digit input dialog.
 * @param  void
 * @author Tony
 * @since 2019-01-11
*/
void SA_Dialog_FreqSetup::digitInputClose()
{
    if(mInputDialog)
    {
        disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
        delete mInputDialog;
        mInputDialog = NULL;
    }
    if(mCHStdDialog){
        disconnect(mCHStdDialog,SIGNAL(destroyed()),this,SLOT(on_CHStdClose()));
        delete mCHStdDialog;
        mCHStdDialog = NULL;
    }
    if(mEditList.contains(mCurEdit))
    {
        mEditList.value(mCurEdit)->setFocus();
    }
    return;
}

/**
 * @brief  Set up full span and update span information.
 * @param  void
 * @author Tony
 * @since 2018-12-19
*/
void SA_Dialog_FreqSetup::on_pb_FullSpan_clicked()
{
    globalUserVariable->SecondaryAction = SA_SPAN;

    mControl->setFullSpan();
    initDisplay();
    digitInputClose();
    return ;
}

/**
 * @brief  Set up zero span and update span information.
 * @param  void
 * @author Tony
 * @since 2018-12-19
*/
void SA_Dialog_FreqSetup::on_pb_ZeroSpan_clicked()
{
    globalUserVariable->SecondaryAction = SA_SPAN;

    mControl->setZeroSpan();
    initDisplay();
    digitInputClose();
    return ;
}

/**
 * @brief  Set up last span and update span information.
 * @param  void
 * @author Tony
 * @since 2018-12-19
*/
void SA_Dialog_FreqSetup::on_pb_LastSpan_clicked()
{
    globalUserVariable->SecondaryAction = SA_SPAN;

    mControl->setLastSpan();
    initDisplay();
    digitInputClose();
    return ;
}

/**
 * @brief  Initialize map of indexes and controls.
 * @param  void
 * @author Tony
 * @since 2018-12-20
*/
void SA_Dialog_FreqSetup::initMap()
{
    mEditList.insert(SA_INPUT_FREQ_CENTER,ui->LedCenterFreq);
    mEditList.insert(SA_INPUT_FREQ_START,ui->LedStartFreq);
    mEditList.insert(SA_INPUT_FREQ_STOP,ui->LedStopFreq);
    mEditList.insert(SA_INPUT_FREQ_CF,ui->LedFreqStep);
    mEditList.insert(SA_INPUT_FREQ_SPAN,ui->LedSpan);

    mEditList.insert(SA_INPUT_FREQ_OFFSET,ui->LedFreqOffset);
    mEditList.insert(SA_INPUT_CH_STD,ui->LedCHStandard);
    mEditList.insert(SA_INPUT_CH_NUM,ui->LedCHNum);
    mEditList.insert(SA_INPUT_CH_STEP,ui->LedCHStep);

    connect(ui->LedCenterFreq,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
    connect(ui->LedStartFreq,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
    connect(ui->LedStopFreq,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
    connect(ui->LedFreqStep,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
    connect(ui->LedSpan,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
    connect(ui->LedFreqOffset,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
    connect(ui->LedCHStandard,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
    connect(ui->LedCHNum,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
    connect(ui->LedCHStep,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
    return ;
}
//Tony 0214
void SA_Dialog_FreqSetup::on_getFocus(SA_LineEdit* mEdit)
{
    if(!mEditList.contains(mCurEdit)) return;
    QString qss =QString("outline: none;border:2px solid rgba(162,115,0,1);padding:6px 6px 5px 8px;");
    mEditList.value(mCurEdit)->setStyleSheet("");
    mCurEdit = mEditList.key(mEdit);
    mEdit->setStyleSheet(qss);
    return;
}
/**
 * @brief  Init the display of frequency setup dialog.
 * @param  void
 * @author Tony
 * @since 2018-12-20
*/
void SA_Dialog_FreqSetup::initDisplay()
{
    refreshEditDisplay(SA_INPUT_FREQ_CENTER);
    refreshEditDisplay(SA_INPUT_FREQ_START);
    refreshEditDisplay(SA_INPUT_FREQ_STOP);
    refreshEditDisplay(SA_INPUT_FREQ_CF);
    refreshEditDisplay(SA_INPUT_FREQ_SPAN);
    refreshEditDisplay(SA_INPUT_FREQ_OFFSET);
    refreshEditDisplay(SA_INPUT_CH_STD);
    refreshEditDisplay(SA_INPUT_CH_NUM);
    refreshEditDisplay(SA_INPUT_CH_STEP);
    refreshButtonDisplay();
    return ;
}

/**
 * @brief  Refresh the corresponding line edit according to the index.
 * @param  index  The index of current editline.
 * @author Tony
 * @since  2018-12-20
*/
void SA_Dialog_FreqSetup::refreshEditDisplay(quint32 index)
{
    QString strGab,strTmp;
    qreal   value,offsetvalue;
    qint32  minus = 0;
    if(!mEditList.contains(index))
        return;
    switch (index)
    {
    case SA_INPUT_FREQ_CENTER:
        value = mControl->getCenterFreq();
//        offsetvalue = mControl->getFreqOffset();
//        value += offsetvalue;
        if(value < 0)
        {
            minus = 1;
            value *= -1;
        }
        strGab = globalUserVariable->freqValueToQstring(value);
        if(minus)
        {
            strGab = QString("-%1").arg(strGab);
        }
        break;
    case SA_INPUT_FREQ_START:
        value = mControl->getStartFreq();
//        offsetvalue = mControl->getFreqOffset();
//        value += offsetvalue;
        if(value < 0)
        {
            minus = 1;
            value *= -1;
        }
        strGab = globalUserVariable->freqValueToQstring(value);
        if(minus)
        {
            strGab = QString("-%1").arg(strGab);
        }
        break;
    case SA_INPUT_FREQ_STOP:
        value = mControl->getStopFreq();
//        offsetvalue = mControl->getFreqOffset();
//        value += offsetvalue;
        if(value < 0)
        {
            minus = 1;
            value *= -1;
        }
        strGab = globalUserVariable->freqValueToQstring(value);
        if(minus)
        {
            strGab = QString("-%1").arg(strGab);
        }
        break;
    case SA_INPUT_FREQ_CF:
        value = mControl->getCFFreq();
        strGab = globalUserVariable->freqValueToQstring(value);
        break;
    case SA_INPUT_FREQ_SPAN:
        value = mControl->getSpan();
        strGab = globalUserVariable->freqValueToQstring(value);
        break;
    case SA_INPUT_FREQ_OFFSET:
        value = mControl->getFreqOffset();
        if(value < 0)
        {
            minus = 1;
            value *= -1;
        }
        strGab = globalUserVariable->freqValueToQstring(value);
        if(minus)
        {
            strGab = QString("-%1").arg(strGab);
        }
        break;
    case SA_INPUT_CH_STD:
        if(globalUserVariable->gTecIndex<0)
        {
            strGab = "None";
            break;
        }
        strTmp = QString(mChStand[globalUserVariable->gTecIndex].name);
        strGab = strTmp;
//        mControl->setCenterFreq(globalUserVariable->adjustFreqByCHStandar());
        break;
    case SA_INPUT_CH_NUM:
        if(globalUserVariable->gTecIndex<0)
        {
            strGab = "None";
            break;
        }
        value = globalUserVariable->CalculateChannelNum();
        strGab = QString::number(value);
        break;
    case SA_INPUT_CH_STEP:
        value = mControl->getChannelNumStep();
        strGab = QString::number(value);
//        if(globalUserVariable->gTecIndex<0)
//        {
//            strGab = "None";
//            break;
//        }
//        value = globalUserVariable->gChannelStep;
//        strGab = globalUserVariable->freqValueToQstring(value);
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
void SA_Dialog_FreqSetup::refreshButtonDisplay()
{
    if(mControl->getCommuDirection() == SA_UPLINK)
    {
        ui->pb_Uplink->setChecked(true);
    }else
    {
        ui->pb_Downlink->setChecked(true);
    }
    return ;
}
/**
 * @brief  Click center frequency line edit and pop-up input dialog box.
 * @param  void
 * @author Tony
 * @since  2018-12-19
*/
void SA_Dialog_FreqSetup::on_LedCenterFreq_clicked()
{
    showInputDialog(SA_INPUT_FREQ_CENTER);
    globalUserVariable->SecondaryAction = SA_SPAN;
    return ;
}

/**
 * @brief  Click start frequency line edit and pop-up input dialog box.
 * @param  void
 * @author Tony
 * @since 2018-12-19
*/
void SA_Dialog_FreqSetup::on_LedStartFreq_clicked()
{
    showInputDialog(SA_INPUT_FREQ_START);
    globalUserVariable->SecondaryAction = SA_NOT_USE;
    return ;
}

/**
 * @brief  Click stop frequency line edit and pop-up input dialog box.
 * @param  void
 * @author Tony
 * @since 2018-12-19
*/
void SA_Dialog_FreqSetup::on_LedStopFreq_clicked()
{
    showInputDialog(SA_INPUT_FREQ_STOP);
    globalUserVariable->SecondaryAction = SA_NOT_USE;
    return ;
}

/**
 * @brief  Click span frequency line edit and pop-up input dialog box.
 * @param  void
 * @author Tony
 * @since 2018-12-19
*/
void SA_Dialog_FreqSetup::on_LedSpan_clicked()
{
    showInputDialog(SA_INPUT_FREQ_SPAN);
    globalUserVariable->SecondaryAction = SA_SPAN;
    return;
}

/**
 * @brief  Click frequency step line edit and pop-up input dialog box.
 * @param  void
 * @author Tony
 * @since 2018-12-19
*/
void SA_Dialog_FreqSetup::on_LedFreqStep_clicked()
{
    showInputDialog(SA_INPUT_FREQ_CF);
    globalUserVariable->SecondaryAction = SA_NOT_USE;
    return ;
}
/**
 * @brief  Click frequency offset line edit and pop-up input dialog box.
 * @param  void
 * @author Tony
 * @since 2019-03-05
*/
void SA_Dialog_FreqSetup::on_LedFreqOffset_clicked()
{
    showInputDialog(SA_INPUT_FREQ_OFFSET);
    globalUserVariable->SecondaryAction = SA_NOT_USE;
    return ;
}
/**
 * @brief  Slot of finish entry.
 * @param  void
 * @author Tony
 * @since 2018-12-21
*/
void SA_Dialog_FreqSetup::on_finishEntry(qint32 index)
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
void SA_Dialog_FreqSetup::showInputDialog(qint32 index)
{
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

/**
 * @brief  show channel standard setup dialog
 * @param  void
 * @author Tony
 * @since 2019-02-14
*/
void SA_Dialog_FreqSetup::showCHStdDialog()
{

    if(mCHStdDialog)
    {
        disconnect(mCHStdDialog,SIGNAL(destroyed()),this,SLOT(on_CHStdClose()));
        delete mCHStdDialog;
//        mCHStdDialog = new SA_Dialog_CH_Std(mControl,globalUserVariable,mParentWin);
    }
    mCHStdDialog = new SA_Dialog_CH_Std(mControl,globalUserVariable,mParentWin);
    mCHStdDialog->move(1,66);
    mCHStdDialog->setFocus();
    connect(mCHStdDialog,SIGNAL(destroyed()),this,SLOT(on_CHStdClose()));
    mCHStdDialog->show();
    return ;
}

void SA_Dialog_FreqSetup::on_CHStdClose()
{
    if(!mCHStdDialog)
        return;
    disconnect(mCHStdDialog,SIGNAL(destroyed()),this,SLOT(on_CHStdClose()));
    mCHStdDialog->close();
    mCHStdDialog = NULL;
    this->setFocus();
    if(mEditList.contains(mCurEdit))
    {
        mEditList.value(mCurEdit)->setFocus();
        initDisplay();
    }
    return;
}

void SA_Dialog_FreqSetup::on_pb_cancel_clicked()
{
    this->hideWidget();
    return;
}

/**
 * @brief  Key press Event.
 * @param  event
 * @author Tony
 * @since 2019-02-14
*/
void SA_Dialog_FreqSetup::keyPressEvent(QKeyEvent *event)
{
  qreal mStep = mControl->getCFFreq();
  qreal mFreq;
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
      }else if(mCHStdDialog)
      {
          on_CHStdClose();
      }else
      {
          this->hideWidget();
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

  if(mCurEdit == SA_INPUT_CH_STD/*|| mCurEdit == SA_INPUT_CH_NUM|| mCurEdit == SA_INPUT_CH_STEP*/)
  {
      return;
  }
  if(mCurEdit == SA_INPUT_CH_NUM && mControl->getCHStandard()<0)
  {
      return;
  }
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
  return;
}

void SA_Dialog_FreqSetup::getKnobValue(qint32 mode)
{
    qint32 value,step;
    qreal mFreqStep;
    qreal mFreqValue;
    mFreqStep = mControl->getCFFreq();
    switch (mCurEdit) {
    case SA_INPUT_FREQ_CENTER:
        mFreqValue = mControl->getCenterFreq();
        if(mode)
            mFreqValue += mFreqStep;
        else
            mFreqValue -= mFreqStep;
        //if(mFreqValue < 0) mFreqValue=0;
        mControl->setCenterFreq(mFreqValue);
        break;
    case SA_INPUT_FREQ_START:
        mFreqValue = mControl->getStartFreq();
        if(mode)
            mFreqValue += mFreqStep;
        else
            mFreqValue -= mFreqStep;
        //if(mFreqValue < 0) mFreqValue=0;
         mControl->setStartFreq(mFreqValue);
        break;
    case SA_INPUT_FREQ_STOP:
        mFreqValue = mControl->getStopFreq();
        if(mode)
            mFreqValue += mFreqStep;
        else
            mFreqValue -= mFreqStep;
        //if(mFreqValue < 0) mFreqValue=0;
        mControl->setStopFreq(mFreqValue);
        break;
    case SA_INPUT_FREQ_CF:

        break;
    case SA_INPUT_FREQ_OFFSET:
        mFreqValue = mControl->getFreqOffset();
        if(mode)
            mFreqValue += mFreqStep;
        else
            mFreqValue -= mFreqStep;
        if(mFreqValue < 0) mFreqValue=0;
        mControl->setFreqOffset(mFreqValue);
        break;
    case SA_INPUT_FREQ_SPAN:
        mFreqValue = mControl->getSpan();
        if(mode)
            mFreqValue += mFreqStep;
        else
            mFreqValue -= mFreqStep;
        if(mFreqValue < 0) mFreqValue=0;
        mControl->setSpan(mFreqValue);
        break;
    case SA_INPUT_CH_NUM:
        value = mControl->getChannelNumber();
        step  = mControl->getChannelNumStep();
        if(mode)
            value += step;
        else
            value -= step;
        if(value < 1) step = 1;
        mControl->setChannelNumber(value);
        break;
    case SA_INPUT_CH_STEP:
        value  = mControl->getChannelNumStep();
        if(mode)
            value += 1;
        else
            value -= 1;
        if(value < 1) step = 1;
        mControl->setChannelNumStep(value);
        break;
    }
    refreshEditDisplay(SA_INPUT_FREQ_CENTER);
    refreshEditDisplay(SA_INPUT_FREQ_START);
    refreshEditDisplay(SA_INPUT_FREQ_STOP);
    refreshEditDisplay(SA_INPUT_FREQ_CF);
    refreshEditDisplay(SA_INPUT_FREQ_OFFSET);
    refreshEditDisplay(SA_INPUT_FREQ_SPAN);
    refreshEditDisplay(SA_INPUT_CH_STD);
    refreshEditDisplay(SA_INPUT_CH_NUM);
    refreshEditDisplay(SA_INPUT_CH_STEP);
    refreshButtonDisplay();
}

void SA_Dialog_FreqSetup::on_LedCHStandard_clicked()
{
    showCHStdDialog();

}

void SA_Dialog_FreqSetup::on_LedCHNum_clicked()
{
    if(mControl->getCHStandard()<0)
        return;
    showInputDialog(SA_INPUT_CH_NUM);
    return;
}

void SA_Dialog_FreqSetup::on_LedCHStep_clicked()
{
    showInputDialog(SA_INPUT_CH_STEP);
    return;
}


void SA_Dialog_FreqSetup::on_pb_Uplink_clicked()
{
    mControl->setCommuDirection(SA_UPLINK);
    initDisplay();
    return;
}

void SA_Dialog_FreqSetup::on_pb_Downlink_clicked()
{
    mControl->setCommuDirection(SA_DOWNLINK);
    initDisplay();
    return;
}

void SA_Dialog_FreqSetup::showWidget()
{
    initDisplay();
    show();
}
void SA_Dialog_FreqSetup::hideWidget()
{
    hide();
    digitInputClose();
    emit mDialogHide();
    return;
}
