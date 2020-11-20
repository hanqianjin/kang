#include "sa_dialog_tracesetup.h"
#include "ui_sa_dialog_tracesetup.h"
#include "sa_applicationcontrol.h"
#include "sa_dialog_digitinput.h"
#include "sa_dialog_warning.h"
SA_Dialog_TraceSetup::SA_Dialog_TraceSetup(controlInterface *interface,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SA_Dialog_TraceSetup)
{
    mCurEdit = 0;
    mControl = interface;
    mTrIndex = mControl->getTraceSelect();
    ui->setupUi(this);
    setProperty("status",qssMode[mControl->GetDisplayMode()]);
    initMap();
    initWidget();
    initDisplay();
    //setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/);
    mInputDialog = NULL;
    hide();
}

/**
 * @brief  Init widget.Set button or other control postion.
 * @param  void
 * @author Tony
 * @since 2019-05-20
 * @note   Must be placed after "initMap()";
*/
void SA_Dialog_TraceSetup::initWidget()
{

//    return;
#if 1
    qint32 mMode = mControl->getCurrentMode();
    if(SA_SPURIOUS_EMISSION_MASK_MODE == mMode)
    {
        ui->lblAveCount->setVisible(true);
        ui->averageEdit->setVisible(true);
        ui->lblAveToggle->setVisible(true);
        ui->pb_toggle_Ave->setVisible(true);

        ui->lblTrace->setVisible(false);
        ui->pb_T1->setVisible(false);
        ui->pb_T2->setVisible(false);
        ui->pb_T3->setVisible(false);
        ui->pb_T4->setVisible(false);
        ui->pb_T5->setVisible(false);
        ui->pb_T6->setVisible(false);
        ui->lblTraceView->setVisible(false);
        ui->pb_toggle->setVisible(false);
        ui->pb_traceAllOn->setVisible(false);
        ui->lblTraceType->setVisible(false);
        ui->TR_Type->setVisible(false);
        ui->lblDete->setVisible(false);
        ui->TR_Detector->setVisible(false);
        ui->pb_clearall->setVisible(false);

        ui->lblAveToggle->move(18,67);
        ui->pb_toggle_Ave->move(94,67);

        ui->lblAveCount->move(18,117);
        ui->averageEdit->move(94,117);

        on_getFocus(mEditList.value(SA_INPUT_AVERAGE_COUNT));
        mCurEdit = SA_INPUT_AVERAGE_COUNT;
    }
    else if(SA_SPECTRUM_EMISSION_MASK_MODE == mMode || SA_CHNLPOWER_MEASURE_MODE == mMode || SA_OCCUPIED_BW_MEASURE_MODE == mMode)
    {
        ui->lblTrace->setVisible(true);
        ui->pb_T1->setVisible(true);
        ui->pb_T2->setVisible(true);
        ui->pb_T3->setVisible(true);
        ui->pb_T4->setVisible(true);
        ui->pb_T5->setVisible(true);
        ui->pb_T6->setVisible(true);
        ui->lblTraceView->setVisible(true);
        ui->pb_toggle->setVisible(true);
        ui->pb_traceAllOn->setVisible(true);
        ui->lblTraceType->setVisible(true);
        ui->TR_Type->setVisible(true);
        ui->lblDete->setVisible(true);
        ui->lblAveCount->setVisible(true);
        ui->averageEdit->setVisible(true);
        ui->TR_Detector->setVisible(true);
        ui->pb_clearall->setVisible(true);

        ui->lblTrace->move(18,75);
        ui->pb_T1->move(94,67);
        ui->pb_T2->move(94,100);
        ui->pb_T3->move(94,133);
        ui->pb_T4->move(94,166);
        ui->pb_T5->move(94,199);
        ui->pb_T6->move(94,232);
        ui->lblTraceView->move(18,280);
        ui->pb_toggle->move(94,282);
        ui->pb_traceAllOn->move(18,332);
        ui->lblTraceType->move(18,382);
        ui->TR_Type->move(94,382);
        ui->lblAveCount->move(18,432);
        ui->averageEdit->move(94,432);
        ui->lblDete->move(18,482);
        ui->TR_Detector->move(94,482);
        ui->pb_clearall->move(18,532);

        ui->lblTrace->setVisible(false);
        ui->pb_T1->setVisible(false);
        ui->pb_T2->setVisible(false);
        ui->pb_T3->setVisible(false);
        ui->pb_T4->setVisible(false);
        ui->pb_T5->setVisible(false);
        ui->pb_T6->setVisible(false);
        ui->lblTraceView->setVisible(false);
        ui->pb_toggle->setVisible(false);
        ui->pb_traceAllOn->setVisible(false);
        ui->pb_clearall->setVisible(false);

        ui->lblAveToggle->setVisible(false);
        ui->pb_toggle_Ave->setVisible(false);


        ui->lblTraceType->move(18,67);
        ui->TR_Type->move(94,67);
        ui->lblDete->move(18,117);
        ui->TR_Detector->move(94,117);
        ui->lblAveCount->move(18,167);
        ui->averageEdit->move(94,167);

        ui->TR_Detector->setPopupPotion(SA_BOTTOM);

        on_getComboBoxFocus(mBoxList.value(SA_COMBOBOX_TRACE));
        mCurEdit = SA_COMBOBOX_TRACE;
    }
    else if(SA_ACP_MEASURE_MODE == mMode || SA_MULTI_ACP_MODE == mMode)
    {
        ui->lblTrace->setVisible(true);
        ui->pb_T1->setVisible(true);
        ui->pb_T2->setVisible(true);
        ui->pb_T3->setVisible(true);
        ui->lblTraceView->setVisible(true);
        ui->pb_toggle->setVisible(true);
        ui->lblTraceType->setVisible(true);
        ui->TR_Type->setVisible(true);
        ui->lblDete->setVisible(true);
        ui->lblAveCount->setVisible(true);
        ui->averageEdit->setVisible(true);
        ui->TR_Detector->setVisible(true);


        ui->lblTrace->move(18,75);
        ui->pb_T1->move(94,67);
        ui->pb_T2->move(94,100);
        ui->pb_T3->move(94,133);
        ui->lblTraceView->move(18,280);
        ui->pb_toggle->move(94,282);
        ui->lblTraceType->move(18,382);
        ui->TR_Type->move(94,382);
        ui->lblAveCount->move(18,432);
        ui->averageEdit->move(94,432);
        ui->lblDete->move(18,482);
        ui->TR_Detector->move(94,482);

        ui->pb_T4->setVisible(false);
        ui->pb_T5->setVisible(false);
        ui->pb_T6->setVisible(false);
        ui->pb_traceAllOn->setVisible(false);
        ui->pb_clearall->setVisible(false);

        ui->lblAveToggle->setVisible(false);
        ui->pb_toggle_Ave->setVisible(false);


        ui->lblTrace->move(18,67);
        ui->pb_T1->move(94,67);
        ui->pb_T2->move(94,100);
        ui->pb_T3->move(94,133);
        ui->lblTraceView->move(18,183);
        ui->pb_toggle->move(94,183);
        ui->lblTraceType->move(18,233);
        ui->TR_Type->move(94,233);
        ui->lblDete->move(18,283);
        ui->TR_Detector->move(94,283);
        ui->lblAveCount->move(18,333);
        ui->averageEdit->move(94,333);

        ui->TR_Detector->setPopupPotion(SA_BOTTOM);

        on_getComboBoxFocus(mBoxList.value(SA_COMBOBOX_TRACE));
        mCurEdit = SA_COMBOBOX_TRACE;
    }
    else
    {
        ui->lblTrace->setVisible(true);
        ui->pb_T1->setVisible(true);
        ui->pb_T2->setVisible(true);
        ui->pb_T3->setVisible(true);
        ui->pb_T4->setVisible(true);
        ui->pb_T5->setVisible(true);
        ui->pb_T6->setVisible(true);
        ui->lblTraceView->setVisible(true);
        ui->pb_toggle->setVisible(true);
        ui->pb_traceAllOn->setVisible(true);
        ui->lblTraceType->setVisible(true);
        ui->TR_Type->setVisible(true);
        ui->lblDete->setVisible(true);
        ui->lblAveCount->setVisible(true);
        ui->averageEdit->setVisible(true);
        ui->TR_Detector->setVisible(true);
        ui->pb_clearall->setVisible(true);

        ui->lblTrace->move(18,75);
        ui->pb_T1->move(94,67);
        ui->pb_T2->move(94,100);
        ui->pb_T3->move(94,133);
        ui->pb_T4->move(94,166);
        ui->pb_T5->move(94,199);
        ui->pb_T6->move(94,232);
        ui->lblTraceView->move(18,280);
        ui->pb_toggle->move(94,282);
        ui->pb_traceAllOn->move(18,332);
        ui->lblTraceType->move(18,382);
        ui->TR_Type->move(94,382);
        ui->lblAveCount->move(18,432);
        ui->averageEdit->move(94,432);
        ui->lblDete->move(18,482);
        ui->TR_Detector->move(94,482);
        ui->pb_clearall->move(18,532);


        ui->lblAveToggle->setVisible(false);
        ui->pb_toggle_Ave->setVisible(false);
        ui->TR_Detector->setPopupPotion(SA_TOP);

        on_getComboBoxFocus(mBoxList.value(SA_COMBOBOX_TRACE));
        mCurEdit = SA_COMBOBOX_TRACE;
    }
#endif
}

SA_Dialog_TraceSetup::~SA_Dialog_TraceSetup()
{
    delete ui;
}
/**
 * @brief  Initialize map of indexes and controls.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_TraceSetup::initMap()
{
    mTraceSelectGroup = new QButtonGroup();
    mTraceSelectGroup->addButton(ui->pb_T1,TR1);
    mTraceSelectGroup->addButton(ui->pb_T2,TR2);
    mTraceSelectGroup->addButton(ui->pb_T3,TR3);
    mTraceSelectGroup->addButton(ui->pb_T4,TR4);
    mTraceSelectGroup->addButton(ui->pb_T5,TR5);
    mTraceSelectGroup->addButton(ui->pb_T6,TR6);
    connect(mTraceSelectGroup,SIGNAL(buttonClicked(qint32)),this,SLOT(mTraceSelectGroup_click(qint32)));

    mBoxList.insert(SA_COMBOBOX_TRACE,ui->TR_Type);
    mBoxList.insert(SA_COMBOBOX_DETECTOR,ui->TR_Detector);
    connect(ui->TR_Type,SIGNAL(clicked(SA_Combobox*)),this,SLOT(on_getComboBoxFocus(SA_Combobox*)));
    connect(ui->TR_Detector,SIGNAL(clicked(SA_Combobox*)),this,SLOT(on_getComboBoxFocus(SA_Combobox*)));

    mEditList.insert(SA_INPUT_AVERAGE_COUNT,ui->averageEdit);
    connect(ui->averageEdit,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));

    ui->TR_Detector->setPopupPotion(SA_TOP);
    return ;
}
void SA_Dialog_TraceSetup::on_getComboBoxFocus(SA_Combobox* mBox)
{
    QString qss = "#SA_Dialog_TraceSetup[status=\"indoor\"] QComboBox{background-image: url(:/sa/image/dropdown_click.png);}\
                   #SA_Dialog_TraceSetup[status=\"outdoor\"] QComboBox{background-image: url(:/sa/image/dropdown_click.png);}\
                   #SA_Dialog_TraceSetup[status=\"night\"] QComboBox{background-image: url(:/sa/image/night/dropdown_click.png);}";


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
void SA_Dialog_TraceSetup::on_getFocus(SA_LineEdit* mEdit)
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

void SA_Dialog_TraceSetup::mTraceSelectGroup_click(qint32 index)
{
    //mControl->setTraceSelect(index);
    mTrIndex = index;
    if(SA_ON == mControl->getTraceViewStatus(mTrIndex))
    {
       mControl->setTraceSelect(mTrIndex);
    }
    initDisplay();
    return;
    qint32 status = mControl->getTraceViewStatus(index);
    qint32 statusAve = mControl->getTraceAverageStatus(index);
    ui->pb_toggle->setChecked(status);
    ui->pb_toggle_Ave->setChecked(statusAve);
    refreshToggleBtn(SA_TRACE_TOGGLE,status);
    refreshToggleBtn(SA_AVERAGE_TOGGLE,statusAve);
    refreshTypeInfo(index);
    refreshEditDisplay(SA_INPUT_AVERAGE_COUNT);
    return ;
}

void SA_Dialog_TraceSetup::traceSelect(qint32 index)
{
    mControl->setTraceSelect(index);
    return ;
}
/**
 * @brief  Init the display.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_TraceSetup::initDisplay()
{
    qint32 mTraceIndex = mTrIndex;
    qint32 status = mControl->getTraceViewStatus(mTraceIndex);
    qint32 statusAve = mControl->getTraceAverageStatus();
    mTraceSelectGroup->button(mTraceIndex)->setChecked(true);
    ui->pb_toggle->setChecked(status);
    ui->pb_toggle_Ave->setChecked(statusAve);
    refreshToggleBtn(SA_TRACE_TOGGLE,status);
    refreshToggleBtn(SA_AVERAGE_TOGGLE,statusAve);
    refreshTypeInfo(mTraceIndex);
    refreshDetectorInfo();
    refreshEditDisplay(SA_INPUT_AVERAGE_COUNT,mTraceIndex);
    return ;
}

void SA_Dialog_TraceSetup::refreshToggleBtn(qint32 index,qint32 status)
{
    switch (index) {
    case SA_TRACE_TOGGLE:
        if(status)
        {
            ui->pb_toggle->setText("On");
        }
        else
        {
            ui->pb_toggle->setText("Off");
        }
        break;
    case SA_AVERAGE_TOGGLE:
        if(status)
        {
            ui->pb_toggle_Ave->setText("On");
        }
        else
        {
            ui->pb_toggle_Ave->setText("Off");
        }
        break;
    }
    return ;
}
/**
 * @brief  Set trace type.
 * @param  traceIndex  Trace index
 * @param  type        Trace type [SA_CLEAR_WRITE][SA_MAX_HOLD][SA_MIN_HOLD][SA_VIEW]
 * @author Tony
 * @since 2018-12-29
*/
void SA_Dialog_TraceSetup::setTraceType(qint32 traceIndex,qint32 type)
{
    switch (type)
    {
    //    case 0:
    //        mControl->setTraceType(SA_TRACE_OFF,traceIndex);
    //        break;
    case 0:
        mControl->setTraceType(SA_CLEAR_WRITE,traceIndex);
        break;
    case 1:
        mControl->setTraceType(SA_MAX_HOLD,traceIndex);
        break;
    case 2:
        mControl->setTraceType(SA_MIN_HOLD,traceIndex);
        break;
    case 3:
        mControl->setTraceType(SA_VIEW,traceIndex);
        break;
    case 4:
        SA_sm_config_sweep->uSweepCompleteFlag = 0;//Johnson 190430
        mControl->setTraceType(SA_TRACE_AVE,traceIndex);
        break;
    default:
        break;
    }
}
/**
 * @brief  Set detector mode.
 * @param  index  The index of detector mode.
 *        [SA_AUTO_DETECTOR][SA_POSITIVE_PEAK][SA_NEGATIVE_PEAK]
 *        [SA_SAMPLE][SA_COMMON][SA_AVERAGE_VOTAGE][SA_RMS]
 * @author Tony
 * @since 2018-12-29
*/
void SA_Dialog_TraceSetup::setDetector(qint32 index)
{
    switch (index)
    {
    case 0:
        mControl->setDetectorMode(SA_AUTO_DETECTOR);
        break;
    case 1:
        mControl->setDetectorMode(SA_POSITIVE_PEAK);
        break;
    case 2:
        mControl->setDetectorMode(SA_NEGATIVE_PEAK);
        break;
    case 3:
        mControl->setDetectorMode(SA_SAMPLE);
        break;
    case 4:
        mControl->setDetectorMode(SA_COMMON);
        break;
    case 5:
        mControl->setDetectorMode(SA_AVERAGE_VOTAGE);
        break;
    case 6:
        mControl->setDetectorMode(SA_RMS);
        break;
    default:
        break;
    }
    return ;
}
/**
 * @brief  Refresh detector mode information.
 * @param
 * @author Tony
 * @since 2018-12-29
*/
void SA_Dialog_TraceSetup::refreshDetectorInfo()
{
    qint32 mDetectorType = mControl->getDetectorMode();
    if(mDetectorType == SA_AUTO_DETECTOR)
    {
        mDetectorType = SA_COMMON;
    }

    ui->TR_Detector->blockSignals(true);
    ui->TR_Detector->setCurrentIndex(mDetectorType);
    ui->TR_Detector->blockSignals(false);

    qint32 flag = 1;
    /*for(qint32 i=0;i<MARKER_TOTAL_CNT;i++)
    {
        if(mControl->getMarkerNoiseStatus(i) == SA_ON)
        {
            flag = 0;
            break;
        }
    }*/
    //Johnson 191218
//    if(mControl->getMarkerNoiseStatus()) flag = 0;

//    ui->TR_Detector->setEnabled(flag);
    return;
}

/**
 * @brief  Refresh trace type information.
 * @author Tony
 * @since 2018-12-29
*/
void SA_Dialog_TraceSetup::refreshTypeInfo(qint32 traceIndex)
{
    qint32 mTraceType;
    if(traceIndex < 0 || traceIndex >= TRACE_CNT_TOTAL)
    {
        traceIndex = mControl->getTraceSelect();
    }
    mTraceType = mControl->getTraceType(traceIndex);
    ui->TR_Type->blockSignals(true);
    ui->TR_Type->setCurrentIndex(mTraceType);
    ui->TR_Type->blockSignals(false);
    return;
}


void SA_Dialog_TraceSetup::on_pb_cancel_clicked()
{
    hideWidget();
    return;
}

void SA_Dialog_TraceSetup::on_pb_toggle_clicked(bool checked)
{
    mControl->setTraceViewStatus(checked,mTrIndex);
    refreshToggleBtn(SA_TRACE_TOGGLE,checked);
    /*
    if(checked)
        mControl->setTraceSelect(mTrIndex);
    else {
        for(qint32 i = TRACE_CNT_TOTAL - 1;i>= 0;i--)
        {
            if(mControl->getTraceViewStatus(i) == SA_ON)
            {
                mControl->setTraceSelect(i);
                break;
            }
        }
    }
    */
    return;
}

void SA_Dialog_TraceSetup::on_TR_Detector_currentIndexChanged(qint32 index)
{
    setDetector(index);
    initDisplay();
    return;
}

void SA_Dialog_TraceSetup::on_TR_Type_activated(qint32 index)
{
    setTraceType(mTrIndex,index);
    return;
}

void SA_Dialog_TraceSetup::on_pb_toggle_Ave_clicked(bool checked)
{
    if(checked)
    {
        mControl->setTraceType(SA_TRACE_AVE,0);
    }else{
        mControl->setTraceType(SA_CLEAR_WRITE,0);
    }
    mControl->setTraceAverageStatus(checked,mTrIndex);
    initDisplay();
    return;
}

/**
 * @brief  show digit input dialog
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_TraceSetup::showInputDialog(qint32 index)
{
    if(mInputDialog)
    {
        mInputDialog->initDisplay(index);
        mInputDialog->setFocus();
    }else
    {
        mInputDialog = new SA_Dialog_DigitInput(mControl,mControl->globalUserVariable,index,this);
        mInputDialog->setGeometry(mapToGlobal(QPoint(0,0)).x()+this->width()-DIGITINPUT_WIDTH,mapToGlobal(QPoint(0,0)).y(),DIGITINPUT_WIDTH,DIGITINPUT_HEIGHT);
        connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
        mInputDialog->show();
    }
    return ;
}
/**
 * @brief  Slot of finish entry.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_TraceSetup::on_finishEntry(qint32 index)
{
    disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
    mInputDialog = NULL;
    if(mEditList.contains(index))
        initDisplay();
    return ;
}

void SA_Dialog_TraceSetup::on_averageEdit_clicked()
{
    showInputDialog(SA_INPUT_AVERAGE_COUNT);
    return;
}

/**
 * @brief  Refresh the corresponding line edit according to the index.
 * @param  index  The index of current editline.
 * @author Tony
 * @since  2018-12-24
*/
void SA_Dialog_TraceSetup::refreshEditDisplay(quint32 index, quint32 traceindex)
{
    QString strGab;
    qreal   value;
    if(!mEditList.contains(index))
        return;
    switch (index)
    {
    case SA_INPUT_AVERAGE_COUNT:
        value = mControl->getTraceAverageCount(traceindex);
        strGab = QString::number(value);
        break;
    default:
        break;
    }
    mEditList.find(index).value()->setText(strGab);
    return ;
}
/**
 * @brief  Key press Event.
 * @param  event
 * @author Tony
 * @since 2019-02-14
*/
void SA_Dialog_TraceSetup::keyPressEvent(QKeyEvent *event)
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

void SA_Dialog_TraceSetup::getKnobValue(qint32 mode)
{
    qreal mStep;
    qreal mValue;
    switch (mCurEdit)
    {
    case SA_INPUT_AVERAGE_COUNT:
        if(mControl->getTraceAverageStatus() == SA_OFF)
        {
            mControl->setTraceAverageStatus(SA_ON,mTrIndex);
            initDisplay();
        }
        mStep = 1;
        mValue=mControl->getTraceAverageCount(mTrIndex);
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        mControl->setTraceAverageCount(mValue,mTrIndex);

        refreshEditDisplay(SA_INPUT_AVERAGE_COUNT,mTrIndex);
        break;
    }

}

void SA_Dialog_TraceSetup::on_pb_traceAllOn_clicked()
{
    for(qint32 i =0;i<TRACE_CNT_TOTAL;i++)
    {
        mControl->setTraceViewStatus(SA_ON,i);
    }
    initDisplay();
}

void SA_Dialog_TraceSetup::on_pb_clearall_clicked()
{
    SA_Dialog_Warning message("Notice","Are you sure to clear all traces?",this);
    message.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    if(message.exec() != QDialog::Accepted)
    {
        return;
    }
    mControl->setTraceSelect(0);
    for(qint32 i =0;i<TRACE_CNT_TOTAL;i++)
    {
        mControl->setTraceViewStatus(SA_OFF,i);
        mControl->setTraceType(SA_CLEAR_WRITE,i);
        mControl->setTraceAverageStatus(SA_OFF,i);
    }
    initDisplay();
}

void SA_Dialog_TraceSetup::showWidget()
{
    initDisplay();
    show();
    return;
}
void SA_Dialog_TraceSetup::hideWidget()
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
