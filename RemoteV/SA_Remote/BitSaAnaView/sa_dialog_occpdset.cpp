#include "sa_dialog_occpdset.h"
#include "ui_sa_dialog_occpdset.h"
#include "sa_applicationcontrol.h"
#include "sa_dialog_digitinput.h"

sa_dialog_occpdset::sa_dialog_occpdset(controlInterface *interface, user_variable *puser_variable, QWidget *parent) :
    mControl(interface),
    globalUserVariable(puser_variable),
    QWidget(parent),
    ui(new Ui::sa_dialog_occpdset)
{
    ui->setupUi(this);
    hide();
    setProperty("status",qssMode[mControl->GetDisplayMode()]);
    initDisplay();
    mInputDialog = NULL;
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | /*Qt::Dialog|*/Qt::CustomizeWindowHint);
    ui->lineEdit->setFocus();
    mCurEdit = SA_INPUT_OCCUPIED;

    connect(ui->lineEdit,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
    connect(ui->lineEdit_1,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
}

sa_dialog_occpdset::~sa_dialog_occpdset()
{
    digitInputClose();
    delete ui;
}

/**
 * @brief sa_dialog_occpdset::on_getFocus
 * @param mEdit
 */
void sa_dialog_occpdset::on_getFocus(SA_LineEdit* mEdit)
{
    if(ui->lineEdit == mEdit) mCurEdit = SA_INPUT_OCCUPIED;
    else if(ui->lineEdit_1 == mEdit) mCurEdit = SA_INPUT_XDB;

    return;
}

/**
 * @brief  Init the display of frequency setup dialog.
 * @param  void
 * @author Johnson
 * @since 2019-04-18
*/
void sa_dialog_occpdset::initDisplay()
{
    refreshEditDisplay(SA_INPUT_OCCUPIED);
    refreshEditDisplay(SA_INPUT_XDB);
}

/**
 * @brief  Refresh the line edit.
 * @author Johnson
 * @since  2019-04-18
*/
void sa_dialog_occpdset::refreshEditDisplay(qint32 index)
{
    QString strGab;
    qreal   value;

    if(SA_INPUT_OCCUPIED == index)
    {
        value = mControl->getOccBW_OccupiedBW();

        strGab = QString::number(value,'f',2) + QString("%");
        ui->lineEdit->setText(strGab);
    }
    else if(SA_INPUT_XDB == index)
    {
        value = mControl->getXdB_OccupiedBW();

        strGab = QString::number(value,'f',2) + " dB";
        ui->lineEdit_1->setText(strGab);
    }
}

/**
 * @brief digitInputClose
 */
void sa_dialog_occpdset::digitInputClose()
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
void sa_dialog_occpdset::showInputDialog(qint32 index)
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
void sa_dialog_occpdset::on_finishEntry(qint32 index)
{
    disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
    mInputDialog = NULL;

    if(SA_INPUT_OCCUPIED == index) ui->lineEdit->setFocus();
    else if(SA_INPUT_XDB == index) ui->lineEdit_1->setFocus();

    initDisplay();
}

void sa_dialog_occpdset::on_lineEdit_clicked()
{
    showInputDialog(SA_INPUT_OCCUPIED);
    globalUserVariable->SecondaryAction = SA_NOT_USE;
}

void sa_dialog_occpdset::on_pb_cancel_2_clicked()
{
    hideWidget();
}

void sa_dialog_occpdset::on_lineEdit_1_clicked()
{
    showInputDialog(SA_INPUT_XDB);
    globalUserVariable->SecondaryAction = SA_NOT_USE;
}

void sa_dialog_occpdset::keyPressEvent(QKeyEvent *event)
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
          if(mCurEdit == SA_INPUT_OCCUPIED) ui->lineEdit->clicked();
          else if(mCurEdit == SA_INPUT_XDB) ui->lineEdit_1->clicked();
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

void sa_dialog_occpdset::getKnobValue(qint32 mode)
{
    qreal mValue;

    switch (mCurEdit) {
    case SA_INPUT_OCCUPIED:
        mValue = mControl->getOccBW_OccupiedBW();
        if(mode)
            mValue += 0.1;
        else
            mValue -= 0.1;

        mControl->setOccupiedBW_OccBW(mValue);
        break;
    case SA_INPUT_XDB:
        mValue = mControl->getXdB_OccupiedBW();
        if(mode)
            mValue += 1.;
        else
            mValue -= 1.;

         mControl->setOccupiedBW_XdB(mValue);
        break;
    }
    refreshEditDisplay(SA_INPUT_XDB);
    refreshEditDisplay(SA_INPUT_OCCUPIED);
}
void sa_dialog_occpdset::initWidget()
{

}
void sa_dialog_occpdset::showWidget()
{
    initDisplay();
    show();
    return;
}
void sa_dialog_occpdset::hideWidget()
{
    hide();
    digitInputClose();
    emit mDialogHide();
    return;
}
