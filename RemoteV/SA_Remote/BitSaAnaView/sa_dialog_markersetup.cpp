#include "sa_dialog_markersetup.h"
#include "ui_sa_dialog_markersetup.h"
#include "sa_applicationcontrol.h"
#include "sa_dialog_digitinput.h"
#include <QDebug>
SA_Dialog_MarkerSetup::SA_Dialog_MarkerSetup(controlInterface *interface, user_variable *puser_variable, QWidget *parent) :
    QWidget(parent),
    mControl(interface),
    globalUserVariable(puser_variable),
    ui(new Ui::SA_Dialog_MarkerSetup)
{
    ui->setupUi(this);
    setProperty("status",qssMode[mControl->GetDisplayMode()]);
    //setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/);
    initMap();
    initWidget();
    initDisplay();
    mInputDialog = NULL;
    hide();
}

SA_Dialog_MarkerSetup::~SA_Dialog_MarkerSetup()
{
    digitInputClose();
    delete ui;
}
/**
 * @brief  Init widget.Set button or other control postion.
 * @param  void
 * @author Tony
 * @since 2019-05-20
 * @note   Must be placed after "initMap()";
*/
void SA_Dialog_MarkerSetup::initWidget()
{
    qint32 mMode = mControl->getCurrentMode();
    if(SA_SPURIOUS_EMISSION_MASK_MODE == mMode || SA_SPECTRUM_EMISSION_MASK_MODE == mMode ||
       SA_CHNLPOWER_MEASURE_MODE == mMode || SA_OCCUPIED_BW_MEASURE_MODE == mMode ||
       SA_ACP_MEASURE_MODE == mMode || SA_MULTI_ACP_MODE == mMode)
    {
        ui->lblMarkerTo->setVisible(false);
        ui->pb_Start->setVisible(false);
        ui->pb_Center->setVisible(false);
        ui->pb_Stop->setVisible(false);
        ui->pb_FreqCount->setVisible(false);
        ui->lblFreqCount->setVisible(false);

        ui->lblMkrEdit->move(18,432);
        ui->edit_MkrFreq->move(94,432);
        ui->lblNoiseMkr->move(18,482);
        ui->pb_MkrNoise->move(94,482);
        ui->lblFreqCount->move(18,532);
        ui->pb_FreqCount->move(94,532);
    }
    else
    {
        ui->lblMarkerTo->setVisible(true);
        ui->pb_Start->setVisible(true);
        ui->pb_Center->setVisible(true);
        ui->pb_Stop->setVisible(true);

        ui->lblMkrEdit->move(18,500);
        ui->edit_MkrFreq->move(94,500);
        ui->lblNoiseMkr->move(18,550);
        ui->pb_MkrNoise->move(94,550);
        ui->lblFreqCount->move(18,600);
        ui->pb_FreqCount->move(94,600);
    }
    ui->edit_MkrFreq->setFocus();
    return;
}

/**
 * @brief  Close digit input dialog.
 * @param  void
 * @author Tony
 * @since 2019-01-11
*/
void SA_Dialog_MarkerSetup::digitInputClose()
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
 * @brief  Init the display of marker setup dialog.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_MarkerSetup::initDisplay()
{
    qint32 mCurrentMarker;
    mCurrentMarker = mControl->getMarkerSelect();
    mMarkerSelectGroup->button(mCurrentMarker)->setChecked(true);

    refreshMarker();
    refreshMarkerEdit();

    return ;
}

/**
 * @brief  Initialize map of indexes and controls.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_MarkerSetup::initMap()
{
    mMarkerSelectGroup = new QButtonGroup();
    mMarkerSelectGroup->addButton(ui->pb_M1,SA_M1);
    mMarkerSelectGroup->addButton(ui->pb_M2,SA_M2);
    mMarkerSelectGroup->addButton(ui->pb_M3,SA_M3);
    mMarkerSelectGroup->addButton(ui->pb_M4,SA_M4);
    mMarkerSelectGroup->addButton(ui->pb_M5,SA_M5);
    mMarkerSelectGroup->addButton(ui->pb_M6,SA_M6);
    connect(mMarkerSelectGroup,SIGNAL(buttonClicked(qint32)),this,SLOT(mMarkerSelectGroup_click(qint32)));

    return ;
}

/**
 * @brief  Select current marker.
 * @param  void
 * @author Tony
 * @date 2019-01-09
*/
void SA_Dialog_MarkerSetup::mMarkerSelectGroup_click(qint32 index)
{
    markerSelect(index);
    mMarkerSelectGroup->button(index)->setChecked(true);

    if(!mControl->getMarkerFreqCountStatus())
    {
        //ui->pb_FreqCount->setChecked(false);
        mControl->setMarkerFreqCountStatus(SA_OFF);
    }
    else
    {
        //ui->pb_FreqCount->setChecked(true);
        mControl->setMarkerFreqCountStatus(SA_ON);
    }
    refreshMarker(index);
    return ;
}


/**
 * @brief  Select current Marker.
 * @param  index  Marker index.
 * @author Tony
 * @date 2019-01-09
*/
void SA_Dialog_MarkerSetup::markerSelect(qint32 index)
{
    mControl->setMarkerSelect(index);
    return ;
}
/**
 * @brief  Refresh current Marker noise status.
 * @param  void
 * @author Tony
 * @date 2019-01-09
*/
void SA_Dialog_MarkerSetup::refreshMarkerNoise()
{
    qint32 mMarkerNoise;
    mMarkerNoise = mControl->getMarkerNoiseStatus();
    ui->pb_MkrNoise->setChecked(mMarkerNoise);
    return ;
}
/**
 * @brief  Refresh Marker type.
 * @param  void
 * @author Tony
 * @date 2019-01-09
*/
void SA_Dialog_MarkerSetup::refreshMarkerType(qint32 markerIndex)
{
    if(markerIndex <0 ||markerIndex>=MARKER_TOTAL_CNT)
    {
        markerIndex = mControl->getMarkerSelect();
    }
    qint32 mMarkerType;
    mMarkerType = mControl->getMarkerType(markerIndex);
    if(mMarkerType==DELTA)
    {
        ui->pb_Delta->setChecked(true);
    }else if(mMarkerType==REF)
    {
        ui->pb_Normal->setChecked(true);
    }else if(mMarkerType==DELTA_PAIR)
    {
        ui->pb_DeltaPair->setChecked(true);
    }
    return ;
}

/**
 * @brief  Refresh marker information.
 * @param  index   marker index.
 * @author Tony
 * @since  2018-12-28
*/
void SA_Dialog_MarkerSetup::refreshMarker(qint32 index)
{
    if(index <0 || index>=MARKER_TOTAL_CNT)
    {
        index = mControl->getMarkerSelect();
    }

    qint32 mkrVisable = mControl->getMarkerViewStatus(index);
    qint32 mkrNoise = mControl->getMarkerNoiseStatus(index);
    qint32 mkrType = mControl->getMarkerType(index);
    qint32 mkrFreqCount = mControl->getMarkerFreqCountStatus(index);

    ui->pb_toggle->setChecked(mkrVisable);
    ui->pb_MkrNoise->setChecked(mkrNoise);
    ui->pb_FreqCount->setChecked(mkrFreqCount);

    if(mkrType == REF)
    {
        ui->pb_Normal->setChecked(true);
    }
    else if(mkrType == DELTA)
    {
        ui->pb_Delta->setChecked(true);
    }
    else if(mkrType == DELTA_PAIR)
    {
        ui->pb_DeltaPair->setChecked(true);
    }
    return ;
}


/**
 * @brief  Refresh marker edit information.
 * @param  index   marker index.
 * @author Tony
 * @since  2018-12-28
*/
void SA_Dialog_MarkerSetup::refreshMarkerEdit(qint32 index)
{
   QString strGab;
   qreal   value;
   qreal   tmpvalue;
   qint32  minus = 0;
   qint32  MkrType;
   if(index <0 ||index>=MARKER_TOTAL_CNT)
   {
       index = mControl->getMarkerSelect();
   }
   if(!mControl->getMarkerViewStatus(index) || !mControl->getTraceViewStatus())
   {
       ui->edit_MkrFreq->setText("");
       return;
   }

    MkrType = mControl->getMarkerType(index);
    if(!mControl->globalUserVariable->gSpanMode)
    {
        switch (MkrType) {
        case REF:
            value =(qreal) mControl->getMarkerRefFreq(index);
            if(value<0)
            {
                minus = 1;
                value *= -1;
            }
            break;
        case DELTA:
            value = mControl->getMarkerDeltaFreq(index);
            tmpvalue =  mControl->getMarkerRefFreq(index);
            value -= tmpvalue;
            if(value<0)
            {
                minus = 1;
                value *= -1;
            }
            break;
        }
        strGab =globalUserVariable->freqValueToQstring(value);
        if(minus)
        {
            strGab = "-"+strGab;
        }
    }else
    {
        switch (MkrType) {
        case REF:
            value =(qreal) mControl->getMarkerRefTime(index);
            if(value<0)
            {
                minus = 1;
                value *= -1;
            }
            break;
        case DELTA:
            value = mControl->getMarkerDeltaTime(index);
            tmpvalue =  mControl->getMarkerRefTime(index);
            value -= tmpvalue;
            if(value<0)
            {
                minus = 1;
                value *= -1;
            }
            break;
        }
        strGab = globalUserVariable->TimeTransformToQstring(value);
        if(minus)
        {
            strGab = "-"+strGab;
        }
    }

    ui->edit_MkrFreq->setText(strGab);
    return;
}

/**
 * @brief  Slot of finish entry.
 * @param  void
 * @author Tony
 * @since 2018-12-28
*/
void SA_Dialog_MarkerSetup::on_finishEntry(qint32 index)
{
    disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
    mInputDialog = NULL;
    initDisplay();
    return ;
}

/**
 * @brief  show digit input dialog
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_MarkerSetup::showInputDialog(qint32 index)
{
    digitInputClose();
    mInputDialog = new SA_Dialog_DigitInput(mControl,globalUserVariable,index,this);
    mInputDialog->setGeometry(mapToGlobal(QPoint(0,0)).x()+this->width()-DIGITINPUT_WIDTH,mapToGlobal(QPoint(0,0)).y(),DIGITINPUT_WIDTH,DIGITINPUT_HEIGHT);

    connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
    mInputDialog->show();
    return ;
}
/**
 * @brief  Line edit clicked function.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_MarkerSetup::editclicked(quint32 index)
{
    if(index < -1 || index >= MARKER_TOTAL_CNT)
    {
        index = mControl->getMarkerSelect();
    }
    qint32 MarkerType = mControl->getMarkerType(index);
    qint32 showIndex;
    if(mControl->getMarkerViewStatus(index) == SA_OFF)
        mControl->setMarkerViewStatus(SA_ON,index);
    if(MarkerType == REF)
    {
        showIndex =  SA_INPUT_MARKER_EDIT;
    }else if(MarkerType == DELTA)
    {
        showIndex =  SA_INPUT_DELTA_MARKER_EDIT;
    }
    showInputDialog(showIndex);
}

/**
 * @brief  Open or close Marker.
 * @param  void
 * @author Tony
 * @since 2018-12-28
*/
void SA_Dialog_MarkerSetup::on_pb_toggle_clicked()
{
    qint32 status;
    if(ui->pb_toggle->isChecked())
    {
        status=1;
    }
    else
        status=0;
    mControl->setMarkerViewStatus(status,mControl->getMarkerSelect());

    if(!status && mControl->getMarkerFreqCountStatus())
    {
        //ui->pb_FreqCount->setChecked(false);
        mControl->setMarkerFreqCountStatus(SA_OFF);
    }
    refreshMarkerEdit();
    refreshMarker();
    return ;
}


void SA_Dialog_MarkerSetup::on_pb_cancel_clicked()
{
    hideWidget();
    return;
}
/**
 * @brief  Change the mode of marker type.
 * @param  void
 * @author Tony
 * @since 2019-02-13
*/
void SA_Dialog_MarkerSetup::on_pb_Normal_clicked()
{
    mControl->setMarkerType(REF);
    refreshMarkerEdit();
    return;
}

void SA_Dialog_MarkerSetup::on_pb_Delta_clicked()
{
    mControl->setMarkerType(DELTA);
    refreshMarkerEdit();
    return;
}

void SA_Dialog_MarkerSetup::on_pb_DeltaPair_clicked()
{
    mControl->setMarkerType(DELTA_PAIR);
    refreshMarkerEdit();
    return;
}

void SA_Dialog_MarkerSetup::on_pb_toggle_toggled(bool checked)
{
    if(checked)
    {
        ui->pb_toggle->setText("On");   
    }else
    {
        ui->pb_toggle->setText("Off");
    }
    return;
}

void SA_Dialog_MarkerSetup::on_pb_MkrNoise_clicked()
{
    mControl->setMarkerNoiseStatus(ui->pb_MkrNoise->isChecked());
    return;
}

void SA_Dialog_MarkerSetup::on_pb_MkrNoise_toggled(bool checked)
{
    if(checked)
    {
        ui->pb_MkrNoise->setText("On");
    }else
    {
        ui->pb_MkrNoise->setText("Off");
    }
    return;
}

void SA_Dialog_MarkerSetup::on_pb_FreqCount_clicked()
{
    if(mControl->getMarkerViewStatus(globalUserVariable->gMarkerSelect) == SA_OFF || mControl->getSpan() == 0)
    {
        ui->pb_FreqCount->setChecked(false);
        return;
    }
    mControl->setMarkerFreqCountStatus(ui->pb_FreqCount->isChecked());
    return;
}

void SA_Dialog_MarkerSetup::on_pb_FreqCount_toggled(bool checked)
{
    if(checked)
    {
        ui->pb_FreqCount->setText("On");
    }else
    {
        ui->pb_FreqCount->setText("Off");
    }
    return;
}

void SA_Dialog_MarkerSetup::on_edit_MkrFreq_clicked()
{
//    qint32 index = mControl->getMarkerSelect();
//    qint32 view  = mControl->getMarkerViewStatus(index);
//    if(!view)
//        return;
    editclicked();
    return;
}
void SA_Dialog_MarkerSetup::refreshDisplay()
{
    qint32 mCurMkr = mControl->getMarkerSelect();
    mMarkerSelectGroup_click(mCurMkr);
    refreshMarkerEdit();
    return;
}
/**
 * @brief  Key press Event.
 * @param  event
 * @author Tony
 * @since 2019-02-14
*/
void SA_Dialog_MarkerSetup::keyPressEvent(QKeyEvent *event)
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
      if(!mInputDialog &&mControl->getMarkerViewStatus())
          editclicked();
      if(mInputDialog)
          QCoreApplication::sendEvent(mInputDialog, event);
      break;
  case Qt::Key_F4:
      if(mInputDialog)
          mInputDialog->close();
      QWidget::keyPressEvent(event);
      break;
  case Qt::Key_F3:
      if(mInputDialog)
          mInputDialog->close();
      QWidget::keyPressEvent(event);
      break;
  default:
      if(mInputDialog) QApplication::sendEvent(mInputDialog,event);
      break;
  }

  return ;
}

void SA_Dialog_MarkerSetup::on_pb_Start_clicked()
{
    mControl->setMarkerToStart();
    initDisplay();
}

void SA_Dialog_MarkerSetup::on_pb_Center_clicked()
{
    mControl->setMarkerToCF();
    initDisplay();
}

void SA_Dialog_MarkerSetup::on_pb_Stop_clicked()
{
    mControl->setMarkerToStop();
    initDisplay();
}

void SA_Dialog_MarkerSetup::on_pb_MkrAllOn_clicked()
{
    for(qint32 i = 0;i<MARKER_TOTAL_CNT;i++)
    {
        if(!mControl->getMarkerViewStatus(i))
        {
            mControl->setMarkerViewStatus(SA_ON,i);
        }
    }
    initDisplay();
}

void SA_Dialog_MarkerSetup::showWidget()
{
    initDisplay();
    show();
    return;
}
void SA_Dialog_MarkerSetup::hideWidget()
{
    hide();
    digitInputClose();
    emit mDialogHide();
    return;
}
