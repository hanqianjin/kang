#include "sa_dialog_acpset.h"
#include "ui_sa_dialog_acpset.h"
#include "sa_applicationcontrol.h"
#include "sa_dialog_digitinput.h"

sa_dialog_acpset::sa_dialog_acpset(controlInterface *interface, user_variable *puser_variable, QWidget *parent) :
    mControl(interface),
    globalUserVariable(puser_variable),
    QWidget(parent),
    ui(new Ui::sa_dialog_acpset)
{
    ui->setupUi(this);
    hide();
    setProperty("status",qssMode[mControl->GetDisplayMode()]);
    if(globalUserVariable->currentMode == SA_ACP_MEASURE_MODE) ui->ltitle->setText("ACP");
    else if(globalUserVariable->currentMode == SA_MULTI_ACP_MODE) ui->ltitle->setText("Multi ACP");

    initDisplay();
    mInputDialog = NULL;
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | /*Qt::Dialog|*/Qt::CustomizeWindowHint);
    ui->lineEdit->setFocus();
    mCurEdit = SA_INPUT_CHANNEL_BANDWIDTH;

    connect(ui->lineEdit,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
    connect(ui->lineEdit_1,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
}

sa_dialog_acpset::~sa_dialog_acpset()
{
    digitInputClose();
    delete ui;
}

/**
 * @brief sa_dialog_chnlpowerset::on_getFocus
 * @param mEdit
 */
void sa_dialog_acpset::on_getFocus(SA_LineEdit* mEdit)
{
    if(ui->lineEdit == mEdit) mCurEdit = SA_INPUT_CHANNEL_BANDWIDTH;
    else if(ui->lineEdit_1 == mEdit) mCurEdit = SA_INPUT_CHANNEL_SPACING;

    return;
}

/**
 * @brief  Init the display of frequency setup dialog.
 * @param  void
 * @author Johnson
 * @since 2019-04-18
*/
void sa_dialog_acpset::initDisplay()
{
    refreshEditDisplay(SA_INPUT_CHANNEL_BANDWIDTH);
    refreshEditDisplay(SA_INPUT_CHANNEL_SPACING);
    if(globalUserVariable->currentMode == SA_ACP_MEASURE_MODE) ui->ltitle->setText("ACP");
    else if(globalUserVariable->currentMode == SA_MULTI_ACP_MODE) ui->ltitle->setText("Multi ACP");
}

/**
 * @brief  Refresh the line edit.
 * @author Johnson
 * @since  2019-04-18
*/
void sa_dialog_acpset::refreshEditDisplay(qint32 index)
{
    QString strGab;
    qreal   value;
    qint32  minus = 0;
    if(SA_INPUT_CHANNEL_BANDWIDTH == index)
    {
        value = mControl->getACP_ChannelBW();
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
    }
    else if(SA_INPUT_CHANNEL_SPACING == index)
    {
        value = mControl->getACP_ChannelSP();
        //Johnson 190530 Record channelspacing setted here
        globalUserVariable->dTmpChannelSpacing = value;

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
        ui->lineEdit_1->setText(strGab);
    }
}

/**
 * @brief digitInputClose
 */
void sa_dialog_acpset::digitInputClose()
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
void sa_dialog_acpset::showInputDialog(qint32 index)
{
    if(mInputDialog)
    {
        mInputDialog->initDisplay();
        mInputDialog->setFocus();
    }
    else
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
void sa_dialog_acpset::on_finishEntry(qint32 index)
{
    disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
    mInputDialog = NULL;

    if(SA_INPUT_CHANNEL_BANDWIDTH == index) ui->lineEdit->setFocus();
    else if(SA_INPUT_CHANNEL_SPACING == index) ui->lineEdit_1->setFocus();

    initDisplay();
}

void sa_dialog_acpset::on_lineEdit_clicked()
{
    showInputDialog(SA_INPUT_CHANNEL_BANDWIDTH);
    globalUserVariable->SecondaryAction = SA_NOT_USE;
}

void sa_dialog_acpset::on_pb_cancel_2_clicked()
{
    hideWidget();
}

void sa_dialog_acpset::on_lineEdit_1_clicked()
{
    showInputDialog(SA_INPUT_CHANNEL_SPACING);
    globalUserVariable->SecondaryAction = SA_NOT_USE;
}

void sa_dialog_acpset::keyPressEvent(QKeyEvent *event)
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
          else if(mCurEdit == SA_INPUT_CHANNEL_SPACING) ui->lineEdit_1->clicked();
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

void sa_dialog_acpset::getKnobValue(qint32 mode)
{
    qreal mFreqStep;
    qreal mFreqValue;
    mFreqStep = mControl->getCFFreq();

    switch (mCurEdit) {
    case SA_INPUT_CHANNEL_BANDWIDTH:
        mFreqValue = mControl->getACP_ChannelBW();
        if(mode)
            mFreqValue += mFreqStep;
        else
            mFreqValue -= mFreqStep;

        mControl->setACP_ChannelBW(mFreqValue);
        break;
    case SA_INPUT_CHANNEL_SPACING:
        mFreqValue = mControl->getACP_ChannelSP();
        if(mode)
            mFreqValue += mFreqStep;
        else
            mFreqValue -= mFreqStep;

         mControl->setACP_ChannelSP(mFreqValue);
        break;
    }
    refreshEditDisplay(SA_INPUT_CHANNEL_BANDWIDTH);
    refreshEditDisplay(SA_INPUT_CHANNEL_SPACING);
}
void sa_dialog_acpset::initWidget()
{

}
void sa_dialog_acpset::showWidget()
{
    initDisplay();
    show();
    return;
}
void sa_dialog_acpset::hideWidget()
{
    hide();
    digitInputClose();
    emit mDialogHide();
    return;
}
