#include "sa_dialog_spurem.h"
#include "ui_sa_dialog_spurem.h"
#include "sa_applicationcontrol.h"
#include "sa_lineedit.h"
#include "sa_combobox.h"
#include "sa_dialog_digitinput.h"
#include "QSpinBox"
#include <QThread>
SA_Dialog_SpurEM::SA_Dialog_SpurEM(controlInterface *interface,QWidget *parent) :
    QWidget(parent),
    mControl(interface),
    ui(new Ui::SA_Dialog_SpurEM)
{
    ui->setupUi(this);
    hide();
    setProperty("status",qssMode[mControl->GetDisplayMode()]);
    tableType = SA_SPUREM_SETTABLE_FREQ;
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/);
    initMap();
    initDisplay();
    mCurEdit = SA_INPUT_SPUREM_SPUR_INDEX;
    on_getFocus(ui->LedSpurIndex);
    mInputDialog = NULL;
}

SA_Dialog_SpurEM::~SA_Dialog_SpurEM()
{
    if(mControl)
    {
        mControl->setSpurEMTableType(SA_SPUREM_MEASURE);
    }
    delete ui;
}

void SA_Dialog_SpurEM::initMap()
{
    mEditList.insert(SA_INPUT_SPUREM_SPUR_INDEX,ui->LedSpurIndex);
    mEditList.insert(SA_INPUT_SPUREM_RANGE_INDEX,ui->LedRangeIndex);
    mEditList.insert(SA_INPUT_SPUREM_FREQ_START,ui->LedStartFreq);
    mEditList.insert(SA_INPUT_SPUREM_FREQ_STOP,ui->LedStopFreq);
    mEditList.insert(SA_INPUT_SPUREM_SWEEP_TIME,ui->LedSweepTime);

    mEditList.insert(SA_INPUT_SPUREM_LIMIT_START,ui->LedStartLimit);
    mEditList.insert(SA_INPUT_SPUREM_LIMIT_STOP,ui->LedStopLimit);
    mEditList.insert(SA_INPUT_SPUREM_PEAK_DEFINITION,ui->LedPeakDefinition);
    mEditList.insert(SA_INPUT_SPUREM_PEAK_THRESHOLD,ui->LedPeakThreshold);
    mEditList.insert(SA_INPUT_SPUREM_ATTEN,ui->LedAtten);

    qint32 size = mEditList.size();
    for(qint32 i =0;i<size;i++)
    {
        connect(mEditList.values().at(i),SIGNAL(clicked()),this,SLOT(edit_clicked()));
        connect(mEditList.values().at(i),SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
    }

    mBoxList.insert(SA_COMBOBOX_RBW,ui->RBWBox);
    mBoxList.insert(SA_COMBOBOX_VBW,ui->VBWBox);
    size = mBoxList.size();
    for(qint32 i =0;i<size;i++)
    {
        mBoxList.values().at(i)->setView(new  QListView());
        connect(mBoxList.values().at(i),SIGNAL(clicked(SA_Combobox*)),this,SLOT(on_getComboBoxFocus(SA_Combobox*)));
        mBoxList.values().at(i)->setPopupPotion(SA_TOP,0,0);
    }
    return ;
}

void SA_Dialog_SpurEM::on_getComboBoxFocus(SA_Combobox* mBox)
{
    QString qss = "#SA_Dialog_SpurEM[status=\"indoor\"] QComboBox{background-image: url(:/sa/image/dropdown_click.png);}\
                   #SA_Dialog_SpurEM[status=\"outdoor\"] QComboBox{background-image: url(:/sa/image/dropdown_click.png);}\
                   #SA_Dialog_SpurEM[status=\"night\"] QComboBox{background-image: url(:/sa/image/night/dropdown_click.png);}";


    if(mCurEdit<0 && mBoxList.contains(mCurEdit))
    {
        mBoxList.value(mCurEdit)->setStyleSheet("");
    }else if(mCurEdit>0&& mEditList.contains(mCurEdit))
    {
        mEditList.value(mCurEdit)->setStyleSheet("");
    }
    mBox->setStyleSheet(qss);
    mCurEdit = mBoxList.key(mBox);
    this->repaint();
    return;
}

void SA_Dialog_SpurEM::on_getFocus(SA_LineEdit* mEdit)
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
void SA_Dialog_SpurEM::edit_clicked()
{
    qint32 menuID;
    SA_LineEdit* mCurEditLine = qobject_cast<SA_LineEdit*>(sender());
    mCurEdit = mEditList.key(mCurEditLine);
    showInputDialog(mCurEdit);
}

/**
 * @brief  show digit input dialog
 * @param  void
 * @author Tony
 * @since 2019-05-15
*/
void SA_Dialog_SpurEM::showInputDialog(qint32 index)
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
 * @since 2019-05-15
*/
void SA_Dialog_SpurEM::on_finishEntry(qint32 index)
{
    disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
    mInputDialog = NULL;
    if(mEditList.contains(index))
        initDisplay();
    return ;
}

void SA_Dialog_SpurEM::initDisplay()
{
    qint32 SpurValue,RangeValue;
    if(SA_SPUREM_AVE_EXP==mControl->getSpurEMAveType())
    {
        ui->pb_Ave_1->setChecked(true);
    }else{
        ui->pb_Ave_2->setChecked(true);
    }
    if(SA_SPUREM_REPORT_ALL == mControl->getSpurReportType())
    {
        ui->pb_Report_Mode1->setChecked(true);
    }else
    {
        ui->pb_Report_Mode2->setChecked(true);
    }
    refreshEdit(SA_INPUT_SPUREM_SPUR_INDEX);
    refreshEdit(SA_INPUT_SPUREM_RANGE_INDEX);
    refreshSubMenu(tableType);
}
void SA_Dialog_SpurEM::refreshSubMenu(qint32 mTableType)
{
    qint32 value,minus,status;
    QString strGab;
    status = mControl->getSpurEMDisplay();
    if(status)
    {
        ui->pb_RangeOn->setChecked(true);
        ui->pb_RangeOn->setText("On");
    }else
    {
        ui->pb_RangeOn->setChecked(false);
        ui->pb_RangeOn->setText("Off");
    }
    if(mTableType == SA_SPUREM_SETTABLE_FREQ)
    {
        ui->stackedWidget->setCurrentIndex(1);
        refreshEdit(SA_INPUT_SPUREM_FREQ_START);
        refreshEdit(SA_INPUT_SPUREM_FREQ_STOP);
        refreshEdit(SA_INPUT_SPUREM_SWEEP_TIME);
        refreshCombobox();
    }
    else if(mTableType == SA_SPUREM_SETTABLE_LIMIT)
    {
        ui->stackedWidget->setCurrentIndex(2);
        refreshEdit(SA_INPUT_SPUREM_LIMIT_START);
        refreshEdit(SA_INPUT_SPUREM_LIMIT_STOP);
        refreshEdit(SA_INPUT_SPUREM_PEAK_DEFINITION);
        refreshEdit(SA_INPUT_SPUREM_PEAK_THRESHOLD);
        refreshEdit(SA_INPUT_SPUREM_ATTEN);
    }
    //ui->stackedWidget->repaint();
}
void SA_Dialog_SpurEM::refreshCombobox()
{
    qint32 mRBW,mVBW;
    qint32 indexRBW,indexVBW;
    mRBW = mControl->getSpurEMRBW();
    mVBW = mControl->getSpurEMVBW();
    indexRBW = RbwVbwCompare(mRBW);
    indexVBW = RbwVbwCompare(mVBW);
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
    ui->RBWBox->setCurrentIndex(indexRBW);
    ui->VBWBox->setCurrentIndex(indexVBW-1);
    ui->RBWBox->blockSignals(false);
    ui->VBWBox->blockSignals(false);
}
qint32 SA_Dialog_SpurEM::RbwVbwCompare(qint32 value)
{
    qint32 mSize = sizeof(SA_u32BWTable)/4;
    for(qint32 i = 0;i < mSize ; i++)
    {
        if(SA_u32BWTable[i] == value)
            return i;
    }

    return -1;

}
void SA_Dialog_SpurEM::refreshEdit(qint32 index)
{
    qreal value;
    qint32 minus = 0;
    QString strGab;
    switch (index) {
    case SA_INPUT_SPUREM_SPUR_INDEX:
        value = mControl->getSpurEMCurSpurIndex();
        strGab =QString::number(value+1);
        break;
    case SA_INPUT_SPUREM_RANGE_INDEX:
        value = mControl->getSpurEMCurRangeIndex();
        strGab =QString::number(value+1);
        break;
    case SA_INPUT_SPUREM_FREQ_START:
        value = mControl->getSpurEMstartFreq();
        if(value < 0)
        {
            minus = 1;
            value *= -1;
        }
        strGab = mControl->globalUserVariable->freqValueToQstring(value);
        if(minus)
        {
            strGab = QString("-%1").arg(strGab);
        }
        break;
    case SA_INPUT_SPUREM_FREQ_STOP:
        value = mControl->getSpurEMstopFreq();
        if(value < 0)
        {
            minus = 1;
            value *= -1;
        }
        strGab = mControl->globalUserVariable->freqValueToQstring(value);
        if(minus)
        {
            strGab = QString("-%1").arg(strGab);
        }
        break;
    case SA_INPUT_SPUREM_SWEEP_TIME:
        value = mControl->getSpurEMSweepTime();
        strGab = mControl->globalUserVariable->TimeTransformToQstring(value);
        if(minus)
        {
            strGab = QString("-%1").arg(strGab);
        }
        break;
    case SA_INPUT_SPUREM_LIMIT_START:
        value = mControl->getSpurEMStartLimit();
        strGab = QString::number(value)+" dBm";
        if(minus)
        {
            strGab = QString("-%1").arg(strGab);
        }
        break;
    case SA_INPUT_SPUREM_LIMIT_STOP:
        value = mControl->getSpurEMStopLimit();
        strGab = QString::number(value)+" dBm";
        if(minus)
        {
            strGab = QString("-%1").arg(strGab);
        }
        break;
    case SA_INPUT_SPUREM_PEAK_DEFINITION:
        value = mControl->getSpurEMpeakDefi();
        strGab = QString::number(value)+" dB";
        break;
    case SA_INPUT_SPUREM_PEAK_THRESHOLD:
        value = mControl->getSpurEMpeakThreshold();
        strGab = QString::number(value)+" dBm";
        break;
    case SA_INPUT_SPUREM_ATTEN:
        value = mControl->getSpurEMAtten();
        strGab = QString::number(value)+" dB";
        break;
    default:
        break;
    }
     mEditList.find(index).value()->setText(strGab);
     return;
}
void SA_Dialog_SpurEM::on_pb_cancel_clicked()
{
    hideWidget();
}
void SA_Dialog_SpurEM::keyPressEvent(QKeyEvent *event)
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
      hideWidget();
      return;
  case Qt::Key_Shift:
      if(mControl->globalUserVariable->bShiftKeyPressed)
          mControl->globalUserVariable->bShiftKeyPressed = false;
      else
          mControl->globalUserVariable->bShiftKeyPressed = true;
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
void SA_Dialog_SpurEM::getKnobValue(qint32 mode)
{
    qreal mValue;
    qreal mFreqStep;
    qreal mFreqValue;
    mFreqStep = mControl->getCFFreq();
    switch (mCurEdit) {
    case SA_INPUT_SPUREM_SPUR_INDEX:
        mValue = mControl->getSpurEMCurSpurIndex();
        if(mode)
            mValue += 1;
        else
            mValue -= 1;
        mControl->setSpurEMCurSpurIndex(mValue);
        break;
    case SA_INPUT_SPUREM_RANGE_INDEX:
        mValue = mControl->getSpurEMCurRangeIndex();
        if(mode)
            mValue += 1;
        else
            mValue -= 1;
        mControl->setSpurEMCurRangeIndex(mValue);
        break;
    case SA_INPUT_SPUREM_FREQ_START:
        mFreqValue = mControl->getSpurEMstartFreq();
        if(mode)
            mFreqValue += mFreqStep;
        else
            mFreqValue -= mFreqStep;
        //if(mFreqValue < 0) mFreqValue=0;
        mControl->setSpurEMstartFreq(mFreqValue);
        break;
    case SA_INPUT_SPUREM_FREQ_STOP:
        mFreqValue = mControl->getSpurEMstopFreq();
        if(mode)
            mFreqValue += mFreqStep;
        else
            mFreqValue -= mFreqStep;
        mControl->setSpurEMstopFreq(mFreqValue);
        break;
    case SA_INPUT_SPUREM_SWEEP_TIME:
        mValue = mControl->getSpurEMSweepTime();
        if(mode)
            mValue += 1;
        else
            mValue -= 1;
        mControl->setSpurEMSweepTime(mValue);
        break;
    case SA_INPUT_SPUREM_LIMIT_START:
        mValue = mControl->getSpurEMStartLimit();
        if(mode)
            mValue += 1;
        else
            mValue -= 1;
        mControl->setSpurEMstartLimit(mValue);
        break;
    case SA_INPUT_SPUREM_LIMIT_STOP:
        mValue = mControl->getSpurEMStopLimit();
        if(mode)
            mValue += 1;
        else
            mValue -= 1;
        mControl->setSpurEMStopLimit(mValue);
        break;
    case SA_INPUT_SPUREM_PEAK_DEFINITION:
        mValue = mControl->getSpurEMpeakDefi();
        if(mode)
            mValue += 1;
        else
            mValue -= 1;
        mControl->setSpurEMpeakDefi(mValue);
        break;
    case SA_INPUT_SPUREM_PEAK_THRESHOLD:
        mValue = mControl->getSpurEMpeakThreshold();
        if(mode)
            mValue += 1;
        else
            mValue -= 1;
        mControl->setSpurEMpeakThreshold(mValue);
        break;
    case SA_INPUT_SPUREM_ATTEN:
        mValue = mControl->getSpurEMAtten();
        if(mode)
            mValue += 1;
        else
            mValue -= 1;
        mControl->setSpurEMAtten(mValue);
        break;
    }
    initDisplay();
}

void SA_Dialog_SpurEM::on_pb_RangePara_1_clicked(bool checked)
{
    if(checked)
    {
        mControl->setSpurEMTableType(SA_SPUREM_SETTABLE_FREQ);
        tableType = SA_SPUREM_SETTABLE_FREQ;
        refreshSubMenu(tableType);
        on_getFocus(ui->LedStartFreq);
        ui->stackedWidget->setCurrentIndex(1);

    }
}

void SA_Dialog_SpurEM::on_pb_RangePara_2_clicked(bool checked)
{
    if(checked)
    {
        mControl->setSpurEMTableType(SA_SPUREM_SETTABLE_LIMIT);
        tableType = SA_SPUREM_SETTABLE_LIMIT;
        refreshSubMenu(tableType);
        on_getFocus(ui->LedStartLimit);
        ui->stackedWidget->setCurrentIndex(2);
    }
}

void SA_Dialog_SpurEM::on_RBWBox_currentIndexChanged(int index)
{
    qint32 mSize = sizeof(SA_u32BWTable)/4;
    if(index >= mSize)
    {
        return;
    }
    mControl->setSpurEMRBW(SA_u32BWTable[index]);
}

void SA_Dialog_SpurEM::on_VBWBox_currentIndexChanged(int index)
{
    qreal vbw,rbw,ratio;
    qint32 mSize = sizeof(SA_u32BWTable)/4;
    if(index >= (mSize - 1))
    {
        return;
    }
    vbw = SA_u32BWTable[index+1];
    rbw = mControl->getSpurEMVBW();
    ratio = (qreal)vbw/rbw;
    mControl->setSpurEMVBW(vbw);
}

void SA_Dialog_SpurEM::on_pb_Ave_1_clicked(bool checked)
{
    if(checked)
    {
        mControl->setSpurEMAveType(SA_SPUREM_AVE_EXP);
    }
    return;
}

void SA_Dialog_SpurEM::on_pb_Ave_2_clicked(bool checked)
{
    if(checked)
    {
        mControl->setSpurEMAveType(SA_SPUREM_AVE_REPEAT);
    }
    return;
}

void SA_Dialog_SpurEM::on_pb_Report_Mode1_clicked(bool checked)
{
    if(checked)
    {
        mControl->setSpurReportType(SA_SPUREM_REPORT_ALL);
    }
    refreshEdit(SA_INPUT_SPUREM_SPUR_INDEX);
    return;
}

void SA_Dialog_SpurEM::on_pb_Report_Mode2_clicked(bool checked)
{
    if(checked)
    {
        mControl->setSpurReportType(SA_SPUREM_REPORT_TEST);
    }
    refreshEdit(SA_INPUT_SPUREM_SPUR_INDEX);
    return;
}

void SA_Dialog_SpurEM::on_pb_ReMeasure_clicked()
{
    mControl->setMeasureStatus(SA_ON);
    //mControl->setSuspendFunc(SA_OFF);
    hideWidget();
}

void SA_Dialog_SpurEM::on_pb_RangeOn_clicked(bool checked)
{
    if(checked)
    {
        mControl->setSpurEMDisplay(SA_ON);
        ui->pb_RangeOn->setText("On");
    }else
    {
        mControl->setSpurEMDisplay(SA_OFF);
        ui->pb_RangeOn->setText("Off");
    }
    refreshEdit(SA_INPUT_SPUREM_SPUR_INDEX);
}
void SA_Dialog_SpurEM::initWidget()
{

}
void SA_Dialog_SpurEM::showWidget()
{
    initDisplay();
    show();
    return;
}
void SA_Dialog_SpurEM::hideWidget()
{
    hide();
    if(mInputDialog)
    {
        disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
        delete mInputDialog;
        mInputDialog = NULL;
    }
    emit mDialogHide();
    return;
}
