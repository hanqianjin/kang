#include "sa_dialog_specem.h"
#include "ui_sa_dialog_specem.h"
#include "sa_applicationcontrol.h"
SA_Dialog_SpecEM::SA_Dialog_SpecEM(controlInterface *interface,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SA_Dialog_SpecEM)
{
    ui->setupUi(this);
    mControl = interface;
    hide();
    setProperty("status",qssMode[mControl->GetDisplayMode()]);
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/);

    initMap();
    initDisplay();
    mInputDialog = NULL;
}

SA_Dialog_SpecEM::~SA_Dialog_SpecEM()
{
    delete ui;
}
void SA_Dialog_SpecEM::initMap()
{
    ui->MaskBox->setView(new  QListView());
    ui->RefBox->setView(new  QListView());
    ui->DisplayBox->setView(new  QListView());

    mBoxList.insert(SA_COMBOBOX_SEM_MASK,ui->MaskBox);
    mBoxList.insert(SA_COMBOBOX_SEM_REF,ui->RefBox);
    mBoxList.insert(SA_COMBOBOX_SEM_DISPLAY,ui->DisplayBox);

    mEditList.insert(SA_INPUT_SEM_CHBW,ui->ChBwEdit);
    mEditList.insert(SA_INPUT_SEM_BSPOWER,ui->BSPowerEdit);

    connect(ui->ChBwEdit,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
    connect(ui->BSPowerEdit,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));

    connect(ui->MaskBox,SIGNAL(clicked(SA_Combobox*)),this,SLOT(on_getComboBoxFocus(SA_Combobox*)));
    connect(ui->RefBox,SIGNAL(clicked(SA_Combobox*)),this,SLOT(on_getComboBoxFocus(SA_Combobox*)));
    connect(ui->DisplayBox,SIGNAL(clicked(SA_Combobox*)),this,SLOT(on_getComboBoxFocus(SA_Combobox*)));
}

void SA_Dialog_SpecEM::on_getFocus(SA_LineEdit* mEdit)
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
void SA_Dialog_SpecEM::on_getComboBoxFocus(SA_Combobox* mBox)
{
    QString qss = "#SA_Dialog_AmptSetup[status=\"indoor\"] QComboBox{border-image: url(:/sa/image/dropdown_click.png);}\
                   #SA_Dialog_AmptSetup[status=\"outdoor\"] QComboBox{border-image: url(:/sa/image/dropdown_click.png);}\
                   #SA_Dialog_AmptSetup[status=\"night\"] QComboBox{border-image: url(:/sa/image/night/dropdown_click.png);}";
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

void SA_Dialog_SpecEM::initDisplay()
{
    qint32 mDisplayType,mRefType;
    mDisplayType = mControl->getSpecEMDisplay();
    mRefType = mControl->getSpecEMRefType();
    qint32 mMaskType;
    mMaskType =mControl->getSpecEMMaskType() - 1;

    ui->DisplayBox->blockSignals(true);
    ui->DisplayBox->setCurrentIndex(mDisplayType);
    ui->DisplayBox->blockSignals(false);

    ui->RefBox->blockSignals(true);
    ui->RefBox->setCurrentIndex(mRefType);
    ui->RefBox->blockSignals(false);

    ui->MaskBox->blockSignals(true);
    ui->MaskBox->setCurrentIndex(mMaskType);
    ui->MaskBox->blockSignals(false);

    if(mMaskType == SA_SPECEM_5GNR_P31_38)
    {
        ui->lblBSPowerValue->setVisible(true);
        ui->BSPowerEdit->setVisible(true);
    }else
    {
        ui->lblBSPowerValue->setVisible(false);
        ui->BSPowerEdit->setVisible(false);
    }

    refreshEditDisplay();

//    switch (mDisplayType) {
//    case SA_SPECEM_ABS:
//        ui->pb_Display_Abs->setChecked(true);
//        break;
//    case SA_SPECEM_REL:
//        ui->pb_Display_Ref->setChecked(true);
//        break;
//    case SA_SPECEM_INTE_PWR:
//        ui->pb_Display_IntePwr->setChecked(true);
//        break;
//    }

//    switch (mRefType) {
//    case SA_SPECEM_TOTALPWR:
//        ui->pb_ref_TotalPwr->setChecked(true);
//        break;
//    case SA_SPECEM_PSD:
//        ui->pb_ref_PSD->setChecked(true);
//        break;
//    case SA_SPECEM_SPECPEAK:
//        ui->pb_ref_SpecPk->setChecked(true);
//        break;
//    }

}

void SA_Dialog_SpecEM::on_pb_Display_Abs_clicked()
{
    mControl->setSpecEMDisplay(SA_SPECEM_ABS);
}

void SA_Dialog_SpecEM::on_pb_Display_Ref_clicked()
{
    mControl->setSpecEMDisplay(SA_SPECEM_REL);
}

void SA_Dialog_SpecEM::on_pb_Display_IntePwr_clicked()
{
    mControl->setSpecEMDisplay(SA_SPECEM_INTE_PWR);
}

void SA_Dialog_SpecEM::on_pb_ref_TotalPwr_clicked()
{
    mControl->setSpecEMRefType(SA_SPECEM_TOTALPWR);
}

void SA_Dialog_SpecEM::on_pb_ref_PSD_clicked()
{
    mControl->setSpecEMRefType(SA_SPECEM_PSD);
}

void SA_Dialog_SpecEM::on_pb_ref_SpecPk_clicked()
{
    mControl->setSpecEMRefType(SA_SPECEM_SPECPEAK);
}

void SA_Dialog_SpecEM::on_pb_cancel_clicked()
{
    hideWidget();
    return;
}

void SA_Dialog_SpecEM::keyPressEvent(QKeyEvent *event)
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
      }else
      {
          hideWidget();
      }
      return;
  case Qt::Key_Shift:
      if(mControl->globalUserVariable->bShiftKeyPressed)
          mControl->globalUserVariable->bShiftKeyPressed = false;
      else
          mControl->globalUserVariable->bShiftKeyPressed = true;
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
  return;
}
void SA_Dialog_SpecEM::initWidget()
{

}
void SA_Dialog_SpecEM::showWidget()
{
    initDisplay();
    show();
    return;
}
void SA_Dialog_SpecEM::hideWidget()
{
    hide();
    emit mDialogHide();
    return;
}

void SA_Dialog_SpecEM::on_MaskBox_currentIndexChanged(qint32 index)
{
    mControl->setSpecEMMaskType(index);
    if(index == SA_SPECEM_5GNR_P31_38)
    {
        ui->lblBSPowerValue->setVisible(true);
        ui->BSPowerEdit->setVisible(true);
    }else
    {
        ui->lblBSPowerValue->setVisible(false);
        ui->BSPowerEdit->setVisible(false);
    }
    refreshEditDisplay();
}

void SA_Dialog_SpecEM::on_DisplayBox_currentIndexChanged(qint32 index)
{
    mControl->setSpecEMDisplay(index);
}

void SA_Dialog_SpecEM::on_RefBox_currentIndexChanged(qint32 index)
{
    mControl->setSpecEMRefType(index);
}

void SA_Dialog_SpecEM::on_ChBwEdit_clicked()
{
    showInputDialog(SA_INPUT_SEM_CHBW);
}

void SA_Dialog_SpecEM::on_BSPowerEdit_clicked()
{
    showInputDialog(SA_INPUT_SEM_BSPOWER);
}

void SA_Dialog_SpecEM::refreshEditDisplay()
{
    QString power = QString::number(mControl->getSpecEMBsPower(),'f',2);
    QString chBw = mControl->globalUserVariable->freqValueToQstring(mControl->getSpecEMRefChBw());

    ui->ChBwEdit->setText(chBw);
    ui->BSPowerEdit->setText(power+" dBm");
}

void SA_Dialog_SpecEM::showInputDialog(qint32 index)
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

void SA_Dialog_SpecEM::on_finishEntry(qint32 index)
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

void SA_Dialog_SpecEM::getKnobValue(qint32 mode)
{
    switch (mCurEdit) {
    case SA_INPUT_SEM_CHBW:
        qreal mFreqStep;
        qreal mFreqValue;
        mFreqStep = mControl->getCFFreq();
        mFreqValue = mControl->getSpecEMRefChBw();
        if(mode)
            mFreqValue += mFreqStep;
        else
            mFreqValue -= mFreqStep;
        //if(mFreqValue < 0) mFreqValue=0;
        mControl->setSpecEMRefChBw(mFreqValue);
        break;
    case SA_INPUT_SEM_BSPOWER:
        qreal mStep;
        qreal mValue;
        mStep = 0.01;
        mValue = mControl->getSpecEMBsPower();
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        //if(mFreqValue < 0) mFreqValue=0;
         mControl->setSpecEMBsPower(mValue);
        break;
    }
    refreshEditDisplay();
}

