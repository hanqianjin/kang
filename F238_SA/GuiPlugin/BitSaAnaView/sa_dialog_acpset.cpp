#include "sa_dialog_acpset.h"
#include "ui_sa_dialog_acpset.h"
#include "sa_applicationcontrol.h"
#include "sa_dialog_digitinput.h"

sa_dialog_acpset::sa_dialog_acpset(controlInterface *interface, user_variable *puser_variable, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sa_dialog_acpset)
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

    if(globalUserVariable->currentMode == SA_ACP_MEASURE_MODE)
    {
        ui->lineEdit_3->setFocus();
        mCurEdit = SA_INPUT_MULTIACP_HIGHESTCH_FREQ;
    }
    else if(globalUserVariable->currentMode == SA_MULTI_ACP_MODE)
    {
        ui->lineEdit->setFocus();
        //Johnson 20200509
        //mCurEdit = SA_INPUT_CHANNEL_BANDWIDTH;
        mCurEdit = SA_INPUT_MULTIACP_MAININTEG_BW;
    }

    connect(ui->lineEdit,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
    connect(ui->lineEdit_1,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
    connect(ui->lineEdit_2,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
    connect(ui->lineEdit_3,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
    connect(ui->lineEdit_4,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
    connect(ui->lineEdit_5,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
    connect(ui->lineEdit_6,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
    connect(ui->lineEdit_7,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
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
    if(ui->lineEdit == mEdit)        mCurEdit = SA_INPUT_CHANNEL_BANDWIDTH;
    else if(ui->lineEdit_1 == mEdit) mCurEdit = SA_INPUT_CHANNEL_SPACING;
    else if(ui->lineEdit_2 == mEdit) mCurEdit = SA_INPUT_MULTIACP_LOWESTCH_FREQ;
    else if(ui->lineEdit_3 == mEdit) mCurEdit = SA_INPUT_MULTIACP_HIGHESTCH_FREQ;
    else if(ui->lineEdit_4 == mEdit) mCurEdit = SA_INPUT_MULTIACP_MAININTEG_BW;
    else if(ui->lineEdit_5 == mEdit) mCurEdit = SA_INPUT_MULTIACP_CHNLSPACING;
    else if(ui->lineEdit_6 == mEdit) mCurEdit = SA_INPUT_MULTIACP_ALTINTEG_BW;
    else if(ui->lineEdit_7 == mEdit) mCurEdit = SA_INPUT_MULTIACP_ADJINTEG_BW;

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
#if EXCHANGE_ACPMULTIACP
    if(globalUserVariable->currentMode == SA_ACP_MEASURE_MODE)
    {
        ui->ltitle->setText("Multi ACP");
        ui->label->setVisible(false);
        ui->label_2->setVisible(false);
        ui->label_3->setVisible(true);
        ui->label_4->setVisible(true);
        ui->label_5->setVisible(true);
        ui->label_6->setVisible(true);
        ui->label_7->setVisible(true);
        ui->label_8->setVisible(true);

        ui->lineEdit->setVisible(false);
        ui->lineEdit_1->setVisible(false);
        ui->lineEdit_2->setVisible(true);
        ui->lineEdit_3->setVisible(true);
        ui->lineEdit_4->setVisible(true);
        ui->lineEdit_5->setVisible(true);
        ui->lineEdit_6->setVisible(true);
        ui->lineEdit_7->setVisible(true);

        ui->label_4->move(18,70);
        ui->label_3->move(18,140);
        ui->label_5->move(18,210);
        ui->label_6->move(18,280);
        ui->label_7->move(18,350);
        ui->label_8->move(18,420);
        ui->lineEdit_3->move(100,70);
        ui->lineEdit_2->move(100,140);
        ui->lineEdit_5->move(100,210);
        ui->lineEdit_4->move(100,280);
        ui->lineEdit_7->move(100,350);
        ui->lineEdit_6->move(100,420);

    }
    else if(globalUserVariable->currentMode == SA_MULTI_ACP_MODE)
    {
        ui->ltitle->setText("ACP");
        ui->label->setVisible(false);
        ui->label_2->setVisible(false);
        ui->label_3->setVisible(false);
        ui->label_4->setVisible(false);
        ui->label_5->setVisible(true);
        ui->label_6->setVisible(true);
        ui->label_7->setVisible(true);
        ui->label_8->setVisible(true);

        ui->lineEdit->setVisible(false);
        ui->lineEdit_1->setVisible(false);
        ui->lineEdit_2->setVisible(false);
        ui->lineEdit_3->setVisible(false);
        ui->lineEdit_4->setVisible(true);
        ui->lineEdit_5->setVisible(true);
        ui->lineEdit_6->setVisible(true);
        ui->lineEdit_7->setVisible(true);

        ui->label_5->move(18,140);
        ui->label_6->move(18,70);
        ui->label_7->move(18,210);
        ui->label_8->move(18,280);
        ui->lineEdit_5->move(100,140);
        ui->lineEdit_4->move(100,70);
        ui->lineEdit_7->move(100,210);
        ui->lineEdit_6->move(100,280);
    }
#endif

    refreshEditDisplay(SA_INPUT_CHANNEL_BANDWIDTH);
    refreshEditDisplay(SA_INPUT_CHANNEL_SPACING);
    refreshEditDisplay(SA_INPUT_MULTIACP_HIGHESTCH_FREQ);
    refreshEditDisplay(SA_INPUT_MULTIACP_LOWESTCH_FREQ);
    refreshEditDisplay(SA_INPUT_MULTIACP_CHNLSPACING);
    refreshEditDisplay(SA_INPUT_MULTIACP_MAININTEG_BW);
    refreshEditDisplay(SA_INPUT_MULTIACP_ADJINTEG_BW);
    refreshEditDisplay(SA_INPUT_MULTIACP_ALTINTEG_BW);
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
    else if(SA_INPUT_MULTIACP_HIGHESTCH_FREQ == index)
    {
        value = mControl->getMulACP_HighestCHFreq();

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
        ui->lineEdit_3->setText(strGab);
    }
    else if(SA_INPUT_MULTIACP_LOWESTCH_FREQ == index)
    {
        value = mControl->getMulACP_LowestCHFreq();

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
    else if(SA_INPUT_MULTIACP_CHNLSPACING == index)
    {
        value = mControl->getMulACP_ChnSpacing();

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
        ui->lineEdit_5->setText(strGab);
    }
    else if(SA_INPUT_MULTIACP_MAININTEG_BW == index)
    {
        value = mControl->getMulACP_MainIntegBW();

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
        ui->lineEdit_4->setText(strGab);
    }
    else if(SA_INPUT_MULTIACP_ADJINTEG_BW == index)
    {
        value = mControl->getMulACP_ADJIntegBW();

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
        ui->lineEdit_7->setText(strGab);
    }
    else if(SA_INPUT_MULTIACP_ALTINTEG_BW == index)
    {
        value = mControl->getMulACP_ALTIntegBW();

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
        ui->lineEdit_6->setText(strGab);
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
    else if(SA_INPUT_MULTIACP_LOWESTCH_FREQ == index) ui->lineEdit_2->setFocus();
    else if(SA_INPUT_MULTIACP_HIGHESTCH_FREQ == index) ui->lineEdit_3->setFocus();
    else if(SA_INPUT_MULTIACP_MAININTEG_BW == index) ui->lineEdit_4->setFocus();
    else if(SA_INPUT_MULTIACP_CHNLSPACING == index) ui->lineEdit_5->setFocus();
    else if(SA_INPUT_MULTIACP_ALTINTEG_BW == index) ui->lineEdit_6->setFocus();
    else if(SA_INPUT_MULTIACP_ADJINTEG_BW == index) ui->lineEdit_7->setFocus();

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
          else if(mCurEdit ==  SA_INPUT_MULTIACP_HIGHESTCH_FREQ) ui->lineEdit_3->clicked();
          else if(mCurEdit == SA_INPUT_MULTIACP_LOWESTCH_FREQ) ui->lineEdit_2->clicked();
          else if(mCurEdit ==  SA_INPUT_MULTIACP_CHNLSPACING) ui->lineEdit_5->clicked();
          else if(mCurEdit == SA_INPUT_MULTIACP_MAININTEG_BW) ui->lineEdit_4->clicked();
          else if(mCurEdit ==  SA_INPUT_MULTIACP_ADJINTEG_BW) ui->lineEdit_7->clicked();
          else if(mCurEdit == SA_INPUT_MULTIACP_ALTINTEG_BW) ui->lineEdit_6->clicked();
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
    case SA_INPUT_MULTIACP_HIGHESTCH_FREQ:
        mFreqValue = mControl->getMulACP_HighestCHFreq();
        if(mode)
            mFreqValue += mFreqStep;
        else
            mFreqValue -= mFreqStep;

         mControl->setMulACP_HighestCHFreq(mFreqValue);
        break;
    case SA_INPUT_MULTIACP_LOWESTCH_FREQ:
        mFreqValue = mControl->getMulACP_LowestCHFreq();
        if(mode)
            mFreqValue += mFreqStep;
        else
            mFreqValue -= mFreqStep;

         mControl->setMulACP_LowestCHFreq(mFreqValue);
        break;
    case SA_INPUT_MULTIACP_CHNLSPACING:
        mFreqValue = mControl->getMulACP_ChnSpacing();
        if(mode)
            mFreqValue += mFreqStep;
        else
            mFreqValue -= mFreqStep;

         mControl->setMulACP_ChnSpacing(mFreqValue);
        break;
    case SA_INPUT_MULTIACP_MAININTEG_BW:
        mFreqValue = mControl->getMulACP_MainIntegBW();
        if(mode)
            mFreqValue += mFreqStep;
        else
            mFreqValue -= mFreqStep;

         mControl->setMulACP_MainIntegBW(mFreqValue);
        break;
    case SA_INPUT_MULTIACP_ADJINTEG_BW:
        mFreqValue = mControl->getMulACP_ADJIntegBW();
        if(mode)
            mFreqValue += mFreqStep;
        else
            mFreqValue -= mFreqStep;

         mControl->setMulACP_ADJIntegBW(mFreqValue);
        break;
    case SA_INPUT_MULTIACP_ALTINTEG_BW:
        mFreqValue = mControl->getMulACP_ADJIntegBW();
        if(mode)
            mFreqValue += mFreqStep;
        else
            mFreqValue -= mFreqStep;

         mControl->setMulACP_ADJIntegBW(mFreqValue);
        break;
    }
    refreshEditDisplay(SA_INPUT_CHANNEL_BANDWIDTH);
    refreshEditDisplay(SA_INPUT_CHANNEL_SPACING);
    refreshEditDisplay(SA_INPUT_MULTIACP_HIGHESTCH_FREQ);
    refreshEditDisplay(SA_INPUT_MULTIACP_LOWESTCH_FREQ);
    refreshEditDisplay(SA_INPUT_MULTIACP_CHNLSPACING);
    refreshEditDisplay(SA_INPUT_MULTIACP_MAININTEG_BW);
    refreshEditDisplay(SA_INPUT_MULTIACP_ADJINTEG_BW);
    refreshEditDisplay(SA_INPUT_MULTIACP_ALTINTEG_BW);
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

void sa_dialog_acpset::on_lineEdit_3_clicked()
{
    showInputDialog(SA_INPUT_MULTIACP_HIGHESTCH_FREQ);
    globalUserVariable->SecondaryAction = SA_NOT_USE;
}

void sa_dialog_acpset::on_lineEdit_2_clicked()
{
    showInputDialog(SA_INPUT_MULTIACP_LOWESTCH_FREQ);
    globalUserVariable->SecondaryAction = SA_NOT_USE;
}

void sa_dialog_acpset::on_lineEdit_5_clicked()
{
    showInputDialog(SA_INPUT_MULTIACP_CHNLSPACING);
    globalUserVariable->SecondaryAction = SA_NOT_USE;
}

void sa_dialog_acpset::on_lineEdit_4_clicked()
{
    showInputDialog(SA_INPUT_MULTIACP_MAININTEG_BW);
    globalUserVariable->SecondaryAction = SA_NOT_USE;
}

void sa_dialog_acpset::on_lineEdit_7_clicked()
{
    showInputDialog(SA_INPUT_MULTIACP_ADJINTEG_BW);
    globalUserVariable->SecondaryAction = SA_NOT_USE;
}

void sa_dialog_acpset::on_lineEdit_6_clicked()
{
    showInputDialog(SA_INPUT_MULTIACP_ALTINTEG_BW);
    globalUserVariable->SecondaryAction = SA_NOT_USE;
}
