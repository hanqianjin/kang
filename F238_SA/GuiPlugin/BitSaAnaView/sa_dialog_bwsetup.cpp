#include "sa_dialog_bwsetup.h"
#include "ui_sa_dialog_bwsetup.h"
#include "sa_applicationcontrol.h"
#include "sa_dialog_digitinput.h"
#include <QDebug>
#include <QListView>
SA_Dialog_BWSetup::SA_Dialog_BWSetup(controlInterface *interface, user_variable *puser_variable, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SA_Dialog_BWSetup)
{
    ui->setupUi(this);
    mCurEdit = 0;
    mControl = interface;
    globalUserVariable = puser_variable;

    setProperty("status",qssMode[mControl->GetDisplayMode()]);
    initMap();
    initWidget();
    initDisplay();
    mInputDialog = NULL;
    //setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/);
    hide();
}

SA_Dialog_BWSetup::~SA_Dialog_BWSetup()
{
    digitInputClose();
    delete ui;
}
/**
 * @brief  Init widget.Set button or other control postion.
 * @param  void
 * @author Tony
 * @since 2019-05-20
*/
void SA_Dialog_BWSetup::initWidget()
{
    qint32 mMode = mControl->getCurrentMode();
    if(SA_SPURIOUS_EMISSION_MASK_MODE == mMode)
    {
        ui->lblRBWValue->setVisible(false);
        ui->RBWBox->setVisible(false);
        ui->lblRBWAuto->setVisible(false);
        ui->RBWAutoPB->setVisible(false);
        ui->RBWManualPB->setVisible(false);
        ui->lblVBWValue->setVisible(false);
        ui->VBWBox->setVisible(false);
        ui->lblVBWAuto->setVisible(false);
        ui->VBWAutoPB->setVisible(false);
        ui->VBWManualPB->setVisible(false);
        ui->lblRatioValue->setVisible(false);
        ui->ratioBox->setVisible(false);
        ui->lblIF->setVisible(false);
        ui->IF_OutPut_Box->setVisible(false);

        ui->labelWarning->setVisible(true);
        ui->labelWarning->setText("\n\nThis menu is unavailable under \nthis measurement");
    }else if(SA_SPECTRUM_EMISSION_MASK_MODE == mMode)
    {
        ui->lblRBWValue->setVisible(true);
        ui->RBWBox->setVisible(true);
        ui->lblRBWAuto->setVisible(false);
        ui->RBWAutoPB->setVisible(false);
        ui->RBWManualPB->setVisible(false);
        ui->lblVBWValue->setVisible(false);
        ui->VBWBox->setVisible(false);
        ui->lblVBWAuto->setVisible(false);
        ui->VBWAutoPB->setVisible(false);
        ui->VBWManualPB->setVisible(false);
        ui->lblRatioValue->setVisible(false);
        ui->ratioBox->setVisible(false);
        ui->lblIF->setVisible(false);
        ui->IF_OutPut_Box->setVisible(false);

        ui->labelWarning->setVisible(false);
        ui->labelWarning->setText("\n\nThis menu is unavailable under \nthis measurement");
    }
    else{
        ui->lblRBWValue->setVisible(true);
        ui->RBWBox->setVisible(true);
        ui->lblRBWAuto->setVisible(true);
        ui->RBWAutoPB->setVisible(true);
        ui->RBWManualPB->setVisible(true);
        ui->lblVBWValue->setVisible(true);
        ui->VBWBox->setVisible(true);
        ui->lblVBWAuto->setVisible(true);
        ui->VBWAutoPB->setVisible(true);
        ui->VBWManualPB->setVisible(true);
        ui->lblRatioValue->setVisible(true);
        ui->ratioBox->setVisible(true);
        ui->lblIF->setVisible(true);
        ui->IF_OutPut_Box->setVisible(true);
        ui->RBWBox->setFocus();

        ui->labelWarning->setVisible(false);
    }
}
/**
 * @brief  Close digit input dialog.
 * @param  void
 * @author Tony
 * @since 2019-01-11
*/
void SA_Dialog_BWSetup::digitInputClose()
{
    if(mInputDialog)
    {
        disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
        delete mInputDialog;
        mInputDialog = NULL;
    }
    return;
}
/**
 * @brief  Initialize map of indexes and controls.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_BWSetup::initMap()
{
    ui->RBWBox->setView(new  QListView());
    ui->VBWBox->setView(new  QListView());
    ui->ratioBox->setView(new  QListView());
    ui->IF_OutPut_Box->setView(new  QListView());

    mBoxList.insert(SA_COMBOBOX_RBW,ui->RBWBox);
    mBoxList.insert(SA_COMBOBOX_VBW,ui->VBWBox);
    mBoxList.insert(SA_COMBOBOX_RATIO,ui->ratioBox);
    mBoxList.insert(SA_COMBOBOX_IFOUTPUT,ui->IF_OutPut_Box);

    connect(ui->RBWBox,SIGNAL(clicked(SA_Combobox*)),this,SLOT(on_getComboBoxFocus(SA_Combobox*)));
    connect(ui->VBWBox,SIGNAL(clicked(SA_Combobox*)),this,SLOT(on_getComboBoxFocus(SA_Combobox*)));
    connect(ui->ratioBox,SIGNAL(clicked(SA_Combobox*)),this,SLOT(on_getComboBoxFocus(SA_Combobox*)));
    connect(ui->IF_OutPut_Box,SIGNAL(clicked(SA_Combobox*)),this,SLOT(on_getComboBoxFocus(SA_Combobox*)));
    return ;
}

/**
 * @brief  Line edit clicked event.
 * @param  void
 * @author Tony
 * @since 2018-12-26
*/
void SA_Dialog_BWSetup::edit_clicked()
{
    qint32 index;
    SA_LineEdit* edit = qobject_cast<SA_LineEdit*>(sender());
    index = mEditList.key(edit,-1);
    if(index == -1)
    {
        return ;
    }
    switch (index) {
    case SA_INPUT_MANUAL_RBW:
        RBWEdit_clicked();
        break;
    case SA_INPUT_MANUAL_VBW:
        VBWEdit_clicked();
        break;
    case SA_INPUT_AVERAGE_COUNT:
        showInputDialog(index);
        break;
    default:
        break;
    }
    return ;
}

/**
 * @brief  Init the display of frequency setup dialog.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_BWSetup::initDisplay()
{
    refreshEditDisplay(SA_INPUT_MANUAL_RBW);
    refreshEditDisplay(SA_INPUT_MANUAL_VBW);
    refreshEditDisplay(SA_INPUT_AVERAGE_COUNT);
    refreshComboboxDisplay();
    refreshButtonDisplay();
    return ;
}
/**
 * @brief  Refresh combobox display.
 * @author Tony
 * @since  2019-02-25
*/
void SA_Dialog_BWSetup::refreshComboboxDisplay()
{
    qreal VbwtoRbw;
    qint32 mRBW,mVBW;
    qint32 indexRBW,indexVBW,indexRatio,indexIFOutPut;
    if(mControl->getCurrentMode() == SA_SPECTRUM_EMISSION_MASK_MODE)
    {
        mRBW = mControl->getSpecEMRefRbw();
    }else
    {
        mRBW = mControl->getRbwValue();
    }

    mVBW = mControl->getVbwValue();
    VbwtoRbw = mControl->getVbwtoRbw();
    indexRBW = RbwVbwCompare(mRBW);
    indexVBW = RbwVbwCompare(mVBW);
    indexRatio = RatioCompare(VbwtoRbw);
    if(indexRBW < 0)
    {
        indexRBW = sizeof(SA_u32BWTable) -1;
    }
    if(indexVBW < 0)
    {
        indexVBW = sizeof(SA_u32BWTable) -2;
    }
    ui->RBWBox->blockSignals(true);
    ui->VBWBox->blockSignals(true);
    ui->ratioBox->blockSignals(true);
    ui->RBWBox->setCurrentIndex(indexRBW);
#if !ADD_5MVBW
    ui->VBWBox->setCurrentIndex(indexVBW-1);
#else
    ui->VBWBox->setCurrentIndex(indexVBW);
#endif
    ui->ratioBox->setCurrentIndex(indexRatio);
    ui->RBWBox->blockSignals(false);
    ui->VBWBox->blockSignals(false);
    ui->ratioBox->blockSignals(false);

    indexIFOutPut = mControl->getIFOutPut();
    ui->IF_OutPut_Box->blockSignals(true);
    ui->IF_OutPut_Box->setCurrentIndex(indexIFOutPut);
    ui->IF_OutPut_Box->blockSignals(false);
    return;
}

qint32 SA_Dialog_BWSetup::RatioCompare(qreal ratio)
{
    qreal min,max;
    qint32 mSize = ui->ratioBox->count();
    max = ui->ratioBox->itemText(0).toDouble();
    min = ui->ratioBox->itemText(mSize - 1).toDouble();
    if(ratio >= max)
    {
        return 0;
    }else if(ratio <= min)
    {
        return mSize - 1;
    }
    for(qint32 i = 0;i < mSize-2; i++)
    {
        max = ui->ratioBox->itemText(i).toDouble();
        min = ui->ratioBox->itemText(i+1).toDouble();
        if(ratio < max && 2 * ratio >= (max + min))
            return i;
        else if(2 * ratio < (max + min) &&  ratio >= min)
            return i+1;
    }
    return 0;
}

qint32 SA_Dialog_BWSetup::RbwVbwCompare(qint32 value)
{
    qint32 mSize = sizeof(SA_u32BWTable)/4;
    for(qint32 i = 0;i < mSize ; i++)
    {
        if(SA_u32BWTable[i] == value)
            return i;
    }

    return -1;

}
/**
 * @brief  Refresh the corresponding line edit according to the index.
 * @param  index  The index of current editline.
 * @author Tony
 * @since  2018-12-24
*/
void SA_Dialog_BWSetup::refreshEditDisplay(quint32 index)
{
    QString strGab;
    qreal   value;
    if(!mEditList.contains(index))
        return;
    switch (index)
    {
    case SA_INPUT_MANUAL_RBW:
        value = mControl->getRbwValue();
        strGab = globalUserVariable->freqValueToQstring(value);
        break;
    case SA_INPUT_MANUAL_VBW:
        value = mControl->getVbwValue();
        strGab = globalUserVariable->freqValueToQstring(value);
        break;
    case SA_INPUT_AVERAGE_COUNT:
        value = mControl->getTraceAverageCount();
        strGab = QString::number(value);
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
void SA_Dialog_BWSetup::refreshButtonDisplay()
{
    if(mControl->getRbwStatus())
        ui->RBWAutoPB->setChecked(true);
    else
        ui->RBWManualPB->setChecked(true);
    if(mControl->getVbwStatus())
        ui->VBWAutoPB->setChecked(true);
    else
        ui->VBWManualPB->setChecked(true);
    return ;
}
/**
 * @brief  Slot of finish entry.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_BWSetup::on_finishEntry(qint32 index)
{
    disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
    mInputDialog = NULL;

    if(mEditList.contains(index))
        initDisplay();
    return ;
}

/**
 * @brief  show digit input dialog
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_BWSetup::showInputDialog(qint32 index)
{
    if(mInputDialog)
    {
        mInputDialog->initDisplay(index);
        mInputDialog->setFocus();
    }else
    {
        mInputDialog = new SA_Dialog_DigitInput(mControl,globalUserVariable,index,this);
        mInputDialog->setGeometry(mapToGlobal(QPoint(0,0)).x()+this->width()-DIGITINPUT_WIDTH,mapToGlobal(QPoint(0,0)).y(),DIGITINPUT_WIDTH,DIGITINPUT_HEIGHT);
        connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
        mInputDialog->show();
    }
    return ;
}



/**
 * @brief  Click rbw line edit and pop-up input dialog box.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_BWSetup::RBWEdit_clicked()
{
    on_RBWManualPB_clicked();
    showInputDialog(SA_INPUT_MANUAL_RBW);
    return ;
}
/**
 * @brief  Click vbw line edit and pop-up input dialog box.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_BWSetup::VBWEdit_clicked()
{
    on_VBWManualPB_clicked();
    showInputDialog(SA_INPUT_MANUAL_VBW);
    return ;
}

void SA_Dialog_BWSetup::on_RBWAutoPB_clicked()
{
    //Johnson 190911
    if(mControl->getDoorControlSwitch() == SA_OPEN_DCSWEEP && !globalUserVariable->gZeroSpanAction)
    {
        qint32 gateSweepSource = mControl->getDoorControlSweepMode();

        if((gateSweepSource == SA_FFT_DCSWEEPMODE && globalUserVariable->gSpanFreq >= 1000000) ||
            ((gateSweepSource == SA_LO_DCSWEEPMODE || gateSweepSource == SA_VEDIO_DCSWEEPMODE) && globalUserVariable->gSpanFreq < 1000000))
        {
            ui->RBWAutoPB->setChecked(false);
            ui->RBWManualPB->setChecked(true);
            initDisplay();
            return;
        }
    }

    ui->RBWAutoPB->setChecked(true);
    mControl->setAutoRbwStatus(ui->RBWAutoPB->isChecked());
    initDisplay();

    if(mInputDialog)
    {
        qWarning()<<"Digit dialog already exist!";
        delete mInputDialog;
    }
    return;
}

void SA_Dialog_BWSetup::on_RBWManualPB_clicked()
{
    ui->RBWManualPB->setChecked(true);
    mControl->setAutoRbwStatus(ui->RBWAutoPB->isChecked());
    initDisplay();
    if(mInputDialog)
    {
        qWarning()<<"Digit dialog already exist!";
        delete mInputDialog;
    }
    return;
}

void SA_Dialog_BWSetup::on_VBWAutoPB_clicked()
{
    ui->VBWAutoPB->setChecked(true);
    mControl->setAutoVbwStatus(ui->VBWAutoPB->isChecked());
    initDisplay();
    if(mInputDialog)
    {
        qWarning()<<"Digit dialog already exist!";
        delete mInputDialog;
    }
    return;
}

void SA_Dialog_BWSetup::on_VBWManualPB_clicked()
{
    ui->VBWManualPB->setChecked(true);
    mControl->setAutoVbwStatus(ui->VBWAutoPB->isChecked());
    if(mInputDialog)
    {
        qWarning()<<"Digit dialog already exist!";
        delete mInputDialog;
    }
    return;
}


void SA_Dialog_BWSetup::on_pb_cancel_clicked()
{
    hideWidget();
    return;
}

void SA_Dialog_BWSetup::on_RBWBox_currentIndexChanged(qint32 index)
{
    qint32 mSize = sizeof(SA_u32BWTable)/4;
    if(index >= mSize)
    {
        return;
    }

    if(SA_SPECTRUM_EMISSION_MASK_MODE == mControl->getCurrentMode())
    {
        mControl->setSpecEMRefRbw(SA_u32BWTable[index]);
        refreshComboboxDisplay();
        return;
    }
    //Johnson 190911
    if(mControl->getDoorControlSwitch() == SA_OPEN_DCSWEEP)
    {
        qint32 gateSweepSource = mControl->getDoorControlSweepMode();

        if((gateSweepSource == SA_FFT_DCSWEEPMODE && index <= 6) ||
            ((gateSweepSource == SA_LO_DCSWEEPMODE || gateSweepSource == SA_VEDIO_DCSWEEPMODE) && index > 6))
        {
            refreshButtonDisplay();
            refreshComboboxDisplay();
            return;
        }
    }


    mControl->setAutoRbwStatus(false);
    mControl->setRbwValue(SA_u32BWTable[index]);

//    mControl->getRbwValue();
//    mControl->getVbwValue();
//    (qreal)mControl->getRbwValue()/mControl->getVbwValue();
//    mControl->setVbwValue(SA_u32BWTable[index]);
    refreshButtonDisplay();
    refreshComboboxDisplay();
    return;
}

void SA_Dialog_BWSetup::on_VBWBox_currentIndexChanged(qint32 index)
{
    qreal vbw;//rbw,ratio;
    qint32 mSize = sizeof(SA_u32BWTable)/4;
    if(index >= (mSize - 1))
    {
        return;
    }
#if !ADD_5MVBW
    vbw = SA_u32BWTable[index+1];
#else
    vbw = SA_u32BWTable[index];
#endif
    //rbw = mControl->getRbwValue();
    //ratio = (qreal)vbw/rbw;
    mControl->setAutoVbwStatus(false);
    mControl->setVbwValue(vbw);
//    mControl->setVbwtoRbw(ratio);
    refreshButtonDisplay();
    refreshComboboxDisplay();
    return;
}

void SA_Dialog_BWSetup::on_ratioBox_currentIndexChanged(QString text)
{
    qreal ratio,RBW,VBW ;
    ratio = text.toDouble();
    VBW = mControl->getVbwValue();
//    VBW = RBW * ratio;
    mControl->setVbwtoRbw(ratio);
    mControl->setVbwValue(VBW);
    refreshButtonDisplay();
    refreshComboboxDisplay();
}


void SA_Dialog_BWSetup::on_getFocus(SA_LineEdit* mEdit)
{
    qint32 index = mEditList.key(mEdit);
    if(mCurEdit<0 && mBoxList.contains(mCurEdit))
    {
        mBoxList.value(mCurEdit)->setStyleSheet("");
    }
    mCurEdit = index;
    this->repaint();
    return;
}
void SA_Dialog_BWSetup::on_getComboBoxFocus(SA_Combobox* mBox)
{
    QString qss = "#SA_Dialog_BWSetup[status=\"indoor\"] QComboBox{background-image: url(:/sa/image/dropdown_click.png);}\
                   #SA_Dialog_BWSetup[status=\"outdoor\"] QComboBox{background-image: url(:/sa/image/dropdown_click.png);}\
                   #SA_Dialog_BWSetup[status=\"night\"] QComboBox{background-image: url(:/sa/image/night/dropdown_click.png);}";

    if(mCurEdit<0 && mBoxList.contains(mCurEdit))
    {
        mBoxList.value(mCurEdit)->setStyleSheet("");
    }
    mBox->setStyleSheet(qss);
    mCurEdit = mBoxList.key(mBox);
    return;
}

/**
 * @brief  Key press Event.
 * @param  event
 * @author Tony
 * @since 2019-02-14
*/
void SA_Dialog_BWSetup::keyPressEvent(QKeyEvent *event)
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
      {
           mInputDialog->close();
      }else
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
  if(!mEditList.contains(mCurEdit) || mCurEdit < 0)
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

void SA_Dialog_BWSetup::getKnobValue(qint32 mode)
{
    qreal mStep;
    qreal mValue;
    switch (mCurEdit)
    {
    case SA_INPUT_AVERAGE_COUNT:
        mStep = 1;
        mValue=mControl->getTraceAverageCount();
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        mControl->setTraceAverageCount(mValue);

        refreshEditDisplay(SA_INPUT_AVERAGE_COUNT);
        break;
    }
}

void SA_Dialog_BWSetup::on_IF_OutPut_Box_currentIndexChanged(qint32 index)
{
    mControl->setIFOutPut(index);
    initDisplay();
    return;
}

void SA_Dialog_BWSetup::showWidget()
{
    initDisplay();
    show();
}

void SA_Dialog_BWSetup::hideWidget()
{
    hide();
    emit mDialogHide();
    return;
}
