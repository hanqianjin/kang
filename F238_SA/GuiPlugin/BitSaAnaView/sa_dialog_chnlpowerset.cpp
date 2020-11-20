#include "sa_dialog_chnlpowerset.h"
#include "ui_sa_dialog_chnlpowerset.h"
#include "sa_applicationcontrol.h"
#include "sa_dialog_digitinput.h"

sa_dialog_chnlpowerset::sa_dialog_chnlpowerset(controlInterface *interface, user_variable *puser_variable, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sa_dialog_chnlpowerset)
{
    ui->setupUi(this);
    mControl = interface;
    globalUserVariable = puser_variable;
    hide();
    setProperty("status",qssMode[mControl->GetDisplayMode()]);
    initDisplay();
    mInputDialog = NULL;
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | /*Qt::Dialog|*/Qt::CustomizeWindowHint);
    ui->lineEdit->setFocus();
    mCurEdit = SA_INPUT_CHANNEL_BANDWIDTH;
    connect(ui->lineEdit,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
    connect(ui->lineEdit_2,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
}

sa_dialog_chnlpowerset::~sa_dialog_chnlpowerset()
{
    digitInputClose();
    delete ui;
}

/**
 * @brief sa_dialog_chnlpowerset::on_getFocus
 * @param mEdit
 */
void sa_dialog_chnlpowerset::on_getFocus(SA_LineEdit* mEdit)
{
    if(ui->lineEdit == mEdit) mCurEdit = SA_INPUT_CHANNEL_BANDWIDTH;
    else if(ui->lineEdit_2 == mEdit) mCurEdit = SA_INPUT_FREQ_SPAN;
    return;
}

/**
 * @brief  Init the display of frequency setup dialog.
 * @param  void
 * @author Johnson
 * @since 2019-04-18
*/
void sa_dialog_chnlpowerset::initDisplay()
{
    refreshEditDisplay();
}

/**
 * @brief  Refresh the line edit.
 * @author Johnson
 * @since  2019-04-18
*/
void sa_dialog_chnlpowerset::refreshEditDisplay()
{
    QString strGab;
    qreal   value;
    qint32  minus = 0;
    value = mControl->getChannelPower_ChannelBW();

    //Johnson 190530 Record BW setted here
    globalUserVariable->dTmpChannelBandwidth = value;

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
    ui->lineEdit->setText(strGab);


    value = mControl->getSpan();

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
    ui->lineEdit_2->setText(strGab);
}

/**
 * @brief digitInputClose
 */
void sa_dialog_chnlpowerset::digitInputClose()
{
    if(mInputDialog)
    {
        disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
        delete mInputDialog;
        mInputDialog = NULL;
    }
}

/**
 * @brief showInputDialog
 */
void sa_dialog_chnlpowerset::showInputDialog(qint32 index)
{
    if(mInputDialog)
    {
        mInputDialog->initDisplay();
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
 * @brief on_finishEntry
 * @param index
 */
void sa_dialog_chnlpowerset::on_finishEntry(qint32 index)
{
    disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
    mInputDialog = NULL;
    initDisplay();
}

void sa_dialog_chnlpowerset::on_lineEdit_clicked()
{
    showInputDialog(SA_INPUT_CHANNEL_BANDWIDTH);
    globalUserVariable->SecondaryAction = SA_NOT_USE;
}

void sa_dialog_chnlpowerset::on_pb_cancel_2_clicked()
{
    hideWidget();
}

void sa_dialog_chnlpowerset::keyPressEvent(QKeyEvent *event)
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
      if(!mInputDialog)
      {
          if(mCurEdit == SA_INPUT_CHANNEL_BANDWIDTH) ui->lineEdit->clicked();
          else if(mCurEdit == SA_INPUT_FREQ_SPAN) ui->lineEdit_2->clicked();
      }
      if(mInputDialog) mInputDialog->initInputKey(event);
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
  }
  return;
}

void sa_dialog_chnlpowerset::getKnobValue(qint32 mode)
{
    qreal mFreqStep;
    qreal mFreqValue;

    mFreqStep = mControl->getCFFreq();
    if(mCurEdit == SA_INPUT_CHANNEL_BANDWIDTH)
    {
        mFreqValue = mControl->getChannelPower_ChannelBW();
        if(mode)
            mFreqValue += mFreqStep;
        else
            mFreqValue -= mFreqStep;
        mControl->setChannelPower_ChannelBW(mFreqValue);
    }
    else if(mCurEdit == SA_INPUT_FREQ_SPAN)
    {
        mFreqValue = mControl->getSpan();
        if(mode)
            mFreqValue += mFreqStep;
        else
            mFreqValue -= mFreqStep;
        mControl->setSpan(mFreqValue);
    }

    refreshEditDisplay();
}

void sa_dialog_chnlpowerset::initWidget()
{

}
void sa_dialog_chnlpowerset::showWidget()
{
    initDisplay();
    show();
    return;
}
void sa_dialog_chnlpowerset::hideWidget()
{
    hide();
    digitInputClose();
    emit mDialogHide();
    return;
}

void sa_dialog_chnlpowerset::on_lineEdit_2_clicked()
{
    showInputDialog(SA_INPUT_FREQ_SPAN);
    globalUserVariable->SecondaryAction = SA_NOT_USE;
}
