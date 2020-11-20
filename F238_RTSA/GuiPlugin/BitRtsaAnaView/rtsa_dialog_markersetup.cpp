#include "rtsa_dialog_markersetup.h"
#include "ui_rtsa_dialog_markersetup.h"
#include <QDebug>

RtSa_Dialog_MarkerSetup::RtSa_Dialog_MarkerSetup(RtSa_Interface *interface, RtSa_Dialog_Digitinput *mInput, QWidget *parent) :
    QWidget(parent),
    mControl(interface),
    mInputDialog(mInput),
    ui(new Ui::RtSa_Dialog_MarkerSetup),
    mIsAllMarkerButtonPressed(false),
    mSelectInputID(RTSA_INPUT_MARKER_EDIT),
    mUpDownFlag(0)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint/*|Qt::Dialog*/);
//    this->setAttribute(Qt::WA_TranslucentBackground, true);
//    this->setAttribute(Qt::WA_DeleteOnClose);
//    this->setAttribute(Qt::WA_OpaquePaintEvent, true);
    this->hide();
    initMap();
    initDisplay();
    setCtlAttribute();
    connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
    connect(mInputDialog,SIGNAL(ClockWiseDown(QKeyEvent*)),this,SLOT(DigitalKeyRespond(QKeyEvent*)));
    connect(mControl,SIGNAL(BitViewMakerMoved(bool)),this ,SLOT(On_Update(bool)));
    connect(mControl,SIGNAL(BitViewChanged(quint32)),this,SLOT(On_DisplayChange()));
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(on_timeOut()));
    setProperty("status",rtsa_qssMode[mControl->GetDisplayMode()]);
}

RtSa_Dialog_MarkerSetup::~RtSa_Dialog_MarkerSetup()
{
    delete ui;
//    sa_dialog_setup = NULL;
    if(mInputDialog)
    {
        mInputDialog = NULL;
    }
}

/**
 * @brief  Close digit input dialog.
 * @param  void
 * @author Tony
 * @since 2019-01-11
*/
//void RtSa_Dialog_MarkerSetup::digitInputClose()
//{
////    if(mInputDialog)
////    {
////        disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
////        delete mInputDialog;
////        mInputDialog = NULL;
////    }
//    return;
//}


/**
 * @brief  Init the display of frequency setup dialog.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void RtSa_Dialog_MarkerSetup::initDisplay()
{
    refreshMarkerInfoBox();
//    for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
//    {
//        if(mControl->isMarkerOn(i))
//        {
//            mMarkerViewGroup->button(i)->setChecked(true);
//        }
//        else
//        {
//            mMarkerViewGroup->button(i)->setChecked(false);
//        }
//    }
    mMarkerSelectGroup->button(mControl->getCurMarkerID())->setChecked(true);
    if(mControl->IsPeakTrackOn())
    {
        ui->pb_peakTrack->setChecked(true);
    }
    else
    {
        ui->pb_peakTrack->setChecked(false);
    }
    return ;
}
void RtSa_Dialog_MarkerSetup::setCtlAttribute()
{
//    ui->edit_MkrFreq->setAttribute(Qt::WA_OpaquePaintEvent);
//    ui->pb_mkrnoise->setAttribute(Qt::WA_OpaquePaintEvent);
//    ui->pb_delta->setAttribute(Qt::WA_OpaquePaintEvent);
//    ui->pb_normal->setAttribute(Qt::WA_OpaquePaintEvent);
//    ui->pb_visible_M1->setAttribute(Qt::WA_OpaquePaintEvent);
//    ui->pb_visible_M2->setAttribute(Qt::WA_OpaquePaintEvent);
//    ui->pb_visible_M3->setAttribute(Qt::WA_OpaquePaintEvent);
//    ui->pb_visible_M4->setAttribute(Qt::WA_OpaquePaintEvent);
//    ui->pb_visible_M5->setAttribute(Qt::WA_OpaquePaintEvent);
//    ui->pb_visible_M6->setAttribute(Qt::WA_OpaquePaintEvent);
//    ui->pb_M1->setAttribute(Qt::WA_OpaquePaintEvent);
//    ui->pb_M2->setAttribute(Qt::WA_OpaquePaintEvent);
//    ui->pb_M3->setAttribute(Qt::WA_OpaquePaintEvent);
//    ui->pb_M4->setAttribute(Qt::WA_OpaquePaintEvent);
//    ui->pb_M5->setAttribute(Qt::WA_OpaquePaintEvent);
//    ui->pb_M6->setAttribute(Qt::WA_OpaquePaintEvent);
//    ui->pb_MkrToStart->setAttribute(Qt::WA_OpaquePaintEvent);
//    ui->pb_MkrToCenter->setAttribute(Qt::WA_OpaquePaintEvent);
//    ui->pb_MkrToStop->setAttribute(Qt::WA_OpaquePaintEvent);
//    ui->pb_PeakSearch->setAttribute(Qt::WA_OpaquePaintEvent);
//    ui->pb_MinSearch->setAttribute(Qt::WA_OpaquePaintEvent);
//    ui->pb_NextPeak->setAttribute(Qt::WA_OpaquePaintEvent);
//    ui->pb_NextPeakLeft->setAttribute(Qt::WA_OpaquePaintEvent);
//    ui->pb_NextPeakRight->setAttribute(Qt::WA_OpaquePaintEvent);
}
/**
* @brief
* @param
* @Author Albert
* @date 2020-04-21
*/
void RtSa_Dialog_MarkerSetup::showNotice(bool isShow)
{
    if(isShow)
    {
        ui->edit_MkrFreq->setVisible(false);
        ui->label->setVisible(false);
        ui->label_2->setVisible(false);
        ui->label_3->setVisible(false);
        ui->label_4->setVisible(false);
        ui->label_5->setVisible(false);
        ui->label_6->setVisible(false);
        ui->pb_Center->setVisible(false);
        ui->pb_Delta->setVisible(false);
        ui->pb_DeltaPair->setVisible(false);
        ui->pb_M1->setVisible(false);
        ui->pb_M2->setVisible(false);
        ui->pb_M3->setVisible(false);
        ui->pb_M4->setVisible(false);
        ui->pb_M5->setVisible(false);
        ui->pb_M6->setVisible(false);
        ui->pb_MkrAllOn->setVisible(false);
        ui->pb_Normal->setVisible(false);
        ui->pb_Start->setVisible(false);
        ui->pb_Stop->setVisible(false);
        ui->pb_mkrnoise->setVisible(false);
        ui->pb_peakTrack->setVisible(false);
        ui->pb_toggle->setVisible(false);
        ui->label_warning->setVisible(true);
        ui->label_warning->setText("This menu is not available under\n this measurement");
    }
    else
    {
        ui->edit_MkrFreq->setVisible(true);
        ui->label->setVisible(true);
        ui->label_2->setVisible(true);
        ui->label_3->setVisible(true);
        ui->label_4->setVisible(true);
        ui->label_5->setVisible(true);
        ui->label_6->setVisible(true);
        ui->pb_Center->setVisible(true);
        ui->pb_Delta->setVisible(true);
        ui->pb_DeltaPair->setVisible(true);
        ui->pb_M1->setVisible(true);
        ui->pb_M2->setVisible(true);
        ui->pb_M3->setVisible(true);
        ui->pb_M4->setVisible(true);
        ui->pb_M5->setVisible(true);
        ui->pb_M6->setVisible(true);
        ui->pb_MkrAllOn->setVisible(true);
        ui->pb_Normal->setVisible(true);
        ui->pb_Start->setVisible(true);
        ui->pb_Stop->setVisible(true);
        ui->pb_mkrnoise->setVisible(true);
        ui->pb_peakTrack->setVisible(true);
        ui->pb_toggle->setVisible(true);
        ui->label_warning->setVisible(false);
    }
    return;
}
void RtSa_Dialog_MarkerSetup::keyPressEvent(QKeyEvent *event)
{
    qint32 keyvalue = event->key();
    if(event->key() == Qt::Key_PowerOff)
    {
        if(!event->isAutoRepeat())
        {
            QApplication::sendEvent(this->parent(),event);
        }
        return;
    }
    qint32 FreqUnit = mInputDialog->getUnitNo();
    qreal tempStepFreq = (mControl->getSpan() / (RTSA_NUM_SWEEP_POINT - 1));
    switch (keyvalue) {
    case Qt::Key_Escape:
        if(!mInputDialog->isHidden())
        {
            mInputDialog->hide();
            return;
        }
        this->close();
        QApplication::sendEvent(this->parent(),event);
        break;
    case Qt::Key_Shift:
        mControl->setShiftKeyEnable(true);
        if(!mInputDialog->isHidden())
        {
            mInputDialog->hide();
        }
        this->close();
        QApplication::sendEvent(this->parent(),event);
        break;
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
    case Qt::Key_Period:
    case Qt::Key_Minus:  // - Minus
    case Qt::Key_F2:    //  +/-
    case Qt::Key_F6://key_left
    case Qt::Key_Right:
    case Qt::Key_F7:
        if(mInputDialog->isHidden())
        {
            showInputDialog(mSelectInputID);
            mInputDialog->clearEdit();
        }
        mInputDialog->keyresponse(keyvalue);
        break;
    case Qt::Key_F3:
    case Qt::Key_Up:
    case Qt::Key_F8:
        mUpDownFlag = 0;
        if(timer->isActive())
        {
        }
        else
        {
            timer->start(100);
        }
        break;
    case Qt::Key_Down:
    case Qt::Key_F9:
    case Qt::Key_F4:
        mUpDownFlag = 1;
        if(timer->isActive())
        {
        }
        else
        {
            timer->start(100);
        }
        break;
    }
    return;
}
/**
 * @brief  Initialize map of indexes and controls.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void RtSa_Dialog_MarkerSetup::initMap()
{
    mMarkerSelectGroup = new QButtonGroup();
    mMarkerSelectGroup->addButton(ui->pb_M1,RTSA_SELECT_M1);
    mMarkerSelectGroup->addButton(ui->pb_M2,RTSA_SELECT_M2);
    mMarkerSelectGroup->addButton(ui->pb_M3,RTSA_SELECT_M3);
    mMarkerSelectGroup->addButton(ui->pb_M4,RTSA_SELECT_M4);
    mMarkerSelectGroup->addButton(ui->pb_M5,RTSA_SELECT_M5);
    mMarkerSelectGroup->addButton(ui->pb_M6,RTSA_SELECT_M6);
    connect(mMarkerSelectGroup,SIGNAL(buttonClicked(qint32)),this,SLOT(mMarkerSelectGroup_click(qint32)));

//    mMarkerViewGroup = new QButtonGroup();
//    mMarkerViewGroup->addButton(ui->pb_visible_M1,RTSA_M1);
//    mMarkerViewGroup->addButton(ui->pb_visible_M2,RTSA_M2);
//    mMarkerViewGroup->addButton(ui->pb_visible_M3,RTSA_M3);
//    mMarkerViewGroup->addButton(ui->pb_visible_M4,RTSA_M4);
//    mMarkerViewGroup->addButton(ui->pb_visible_M5,RTSA_M5);
//    mMarkerViewGroup->addButton(ui->pb_visible_M6,RTSA_M6);
//    mMarkerViewGroup->setExclusive(false);
//    connect(mMarkerViewGroup,SIGNAL(buttonClicked(qint32)),this,SLOT(mMarkerViewGroup_click(qint32)));

//    mMarkerToGroup = new QButtonGroup();
//    mMarkerToGroup->addButton(ui->pb_MkrToStart,RTSA_MARKER_TO_START);
//    mMarkerToGroup->addButton(ui->pb_MkrToCenter,RTSA_MARKER_TO_CENTER);
//    mMarkerToGroup->addButton(ui->pb_MkrToStop,RTSA_MARKER_TO_STOP);
//    mMarkerToGroup->addButton(ui->pb_PeakSearch,RTSA_PEAK_SEARCH);
//    mMarkerToGroup->addButton(ui->pb_MinSearch,RTSA_MIN_SEARCH);
//    mMarkerToGroup->addButton(ui->pb_NextPeak,RTSA_NEXT_SEARCH);
//    mMarkerToGroup->addButton(ui->pb_NextPeakLeft,RTSA_PEAK_NEXT_LEFT);
//    mMarkerToGroup->addButton(ui->pb_NextPeakRight,RTSA_PEAK_NEXT_RIGHT);
//    connect(mMarkerToGroup,SIGNAL(buttonClicked(qint32)),this,SLOT(mMarkerToGroup_click(qint32)));

    return ;
}
/**
 * @brief  Visiable button clicked.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
//void RtSa_Dialog_MarkerSetup::mMarkerViewGroup_click(qint32 index)
//{
//    mControl->setCurMarkerID(index);
//    if(index != mCurrentMarker)
//    {
//        mMarkerSelectGroup_click(index);
//    }
//    mControl->setMarkerOn(index,mMarkerViewGroup->button(index)->isChecked());
//    return ;
//}
/**
 * @brief RtSa_Dialog_MarkerSetup::mMarkerToGroup_click
 * @param index
 */
//void RtSa_Dialog_MarkerSetup::mMarkerToGroup_click(qint32 index)
//{
//    switch(index)
//    {
//    case RTSA_MARKER_TO_START:
//        mControl->setMarkerToStart();
//        break;
//    case RTSA_MARKER_TO_CENTER:
//        mControl->setMarkerToCenter();
//        break;
//    case RTSA_MARKER_TO_STOP:
//        mControl->setMarkerToStop();
//        break;
//    case RTSA_PEAK_SEARCH:
//        mControl->setMarkerToPeak();
//        break;
//    case RTSA_MIN_SEARCH:
//        break;
//    case RTSA_NEXT_SEARCH:
//        mControl->setMarkerToNextPeak();
//        break;
//    case RTSA_PEAK_NEXT_LEFT:
//        mControl->setMarkerToLeftPeak();
//        break;
//    case RTSA_PEAK_NEXT_RIGHT:
//        mControl->setMarkerToRightPeak();
//        break;
//    }
//    return ;
//}

/**
 * @brief  Select current marker.
 * @param  void
 * @author Tony
 * @date 2019-01-09
*/
void RtSa_Dialog_MarkerSetup::mMarkerSelectGroup_click(qint32 index)
{
    if(index == RTSA_SELECT_ALL)
    {
        for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
        {
            if(!mControl->isMarkerOn(i))
            {
                mIsAllMarkerButtonPressed = true; // all marker button pressed first time
                ui->pb_toggle->setChecked(false);
                ui->pb_mkrnoise->setChecked(false);
                mIsAllMarkerButtonPressed = false;
                return;
            }
        }
    }
    else
    {
        markerSelect(index);
        mCurrentMarker = index;
    }
    refreshMarkerInfoBox();
    return ;
}

void RtSa_Dialog_MarkerSetup::On_Update(bool isOn)
{
    if(isOn)
    {
        refreshMarkerFreq();
    }
    return;
}

void RtSa_Dialog_MarkerSetup::On_DisplayChange()
{
    if(mControl->getCurBitviewType() == RTSA_SPECTROGRAM)
    {
        this->close();
        return;
    }
    refreshMarkerInfoBox();
    mMarkerSelectGroup->button(mControl->getCurMarkerID())->setChecked(true);
//    for(qint32 i = 0 ; i < RTSA_MARKER_TOTAL_CNT; i++)
//    {
//        mMarkerViewGroup->button(i)->setChecked(mControl->isMarkerOn(i));
//    }
    return;
}
/**
 * @brief  Select current Marker.
 * @param  index  Marker index.
 * @author Tony
 * @date 2019-01-09
*/
void RtSa_Dialog_MarkerSetup::markerSelect(qint32 index)
{
    mControl->setCurMarkerID(index);
    return ;
}
/**
 * @brief  Refresh current Marker noise status.
 * @param  void
 * @author Tony
 * @date 2019-01-09
*/
void RtSa_Dialog_MarkerSetup::refreshMarkerNoise()
{
    qint32 mMarkerNoise;
    mMarkerNoise = mControl->IsMarkerNoiseOn(mControl->getCurMarkerID());
    ui->pb_mkrnoise->setChecked(mMarkerNoise);
    return ;
}
/**
 * @brief  Refresh current Marker type.
 * @param  void
 * @author Tony
 * @date 2019-01-09
*/
void RtSa_Dialog_MarkerSetup::refreshMarkerType()
{
    qint32 mMarkerType;
    refreshMarkerState();
    mMarkerType = mControl->getMarkerType(mControl->getCurMarkerID());
    if(mMarkerType == RTSA_DELTA)
    {
        ui->pb_Delta->setChecked(true);
    }else if(mMarkerType == RTSA_DELTA_PAIR)
    {
        ui->pb_DeltaPair->setChecked(true);
    }else
    {
        ui->pb_Normal->setChecked(true);
    }
    return ;
}
/**
 * @brief  Refresh current Marker frequency.
 * @param  void
 * @author Tony
 * @date 2019-01-09
*/
void RtSa_Dialog_MarkerSetup::refreshMarkerFreq()
{
    qint32 mMarkerType;
    qreal value;
    QString strGab,unitNo;
    mMarkerType = mControl->getMarkerType(mControl->getCurMarkerID());
    if(mMarkerType)
    {
//        ui->pb_Delta->setChecked(true);
        value = mControl->getMarkerDeltaFreq(mControl->getCurMarkerID());
        value -= mControl->getMarkerRefFreq(mControl->getCurMarkerID());
        strGab = mControl->getFreqAdjustStr(value);

    }else
    {
//        ui->pb_Normal->setChecked(true);
        value = mControl->getMarkerRefFreq(mControl->getCurMarkerID());
        strGab = mControl->getFreqAdjustStr(value);
    }
    ui->edit_MkrFreq->setText(strGab + unitNo);
    return ;
}
/**
 * @brief  Refresh current Marker information box.
 * @param  void
 * @author Tony
 * @date 2019-01-09
*/
void RtSa_Dialog_MarkerSetup::refreshMarkerInfoBox()
{
    qint32 mMarkerIndex;
    mMarkerIndex = mControl->getCurMarkerID();
//    ui->MarkerInfoBox->setTitle(QString("Current Marker: M%1").arg(QString::number(mMarkerIndex+1)));

    if(mControl->isMarkerOn(mMarkerIndex))
    {
        ui->pb_toggle->setChecked(true);
    }
    else
    {
        ui->pb_toggle->setChecked(false);
    }
    refreshMarkerNoise();
    refreshMarkerType();
    refreshMarkerFreq();
    return ;
}

/**
 * @brief  Refresh marker information.
 * @param  index   marker index.
 * @author Tony
 * @since  2018-12-28
*/
//void RtSa_Dialog_MarkerSetup::refreshMarker(qint32 index)
//{
//    if(index>=RTSA_MARKER_TOTAL_CNT )
//    {
//        qDebug()<<"Marker index error!";
//        return;
//    }
//    if(index <0)
//    {
//        index = mCurrentMarker;

//    }else
//    {
//        mControl->setCurMarkerID(mCurrentMarker);
//    }

//    refreshMarkerEdit(index);
//    qint32 mkrVisable = mControl->isMarkerOn(mControl->getCurMarkerID());
//    qint32 mkrNoise = mControl->IsMarkerNoiseOn(mControl->getCurMarkerID());
//    qint32 mkrType = mControl->getMarkerType(mControl->getCurMarkerID());
////    mMarkerViewGroup->button(index)->setChecked(mkrVisable);
//    ui->pb_mkrnoise->setChecked(mkrNoise);

//    if(mkrType == RTSA_REF)
//    {
//        ui->pb_Normal->setChecked(true);
//    }else
//    {
//        ui->pb_Delta->setChecked(true);
//    }
//    return ;
//}


/**
 * @brief  Refresh marker edit information.
 * @param  index   marker index.
 * @author Tony
 * @since  2018-12-28
*/
void RtSa_Dialog_MarkerSetup::refreshMarkerEdit(qint32 index)
{
    if(index>=RTSA_MARKER_TOTAL_CNT)
    {
        qWarning()<<"Marker index error!";
        return;
    }
//    if(index <0)
//    {
//        index = mCurrentMarker;
//    }
//    else
//    {
//        mControl->setCurMarkerID(mCurrentMarker);
//    }
    QString strGab;
    qreal   value;
    qreal   tmpvalue;
    if(!ui->pb_Delta->isChecked())
    {
        ui->label_3->setText("Marker\nEdit");
        value = mControl->getMarkerRefFreq(index);
    }
    else
    {
        ui->label_3->setText("Marker\nEdit");
        value = mControl->getMarkerDeltaFreq(index);
        tmpvalue =  mControl->getMarkerRefFreq(index);
        value -= tmpvalue;
    }
    strGab = mControl->getFreqAdjustStr(value);
    ui->edit_MkrFreq->setText(strGab);
    return;
}
/**
 * @brief  Slot of finish entry.
 * @param  void
 * @author Tony
 * @since 2018-12-28
*/
void RtSa_Dialog_MarkerSetup::on_finishEntry(qint32 index)
{
//    disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
//    mInputDialog = NULL;
    refreshMarkerEdit(mControl->getCurMarkerID());
//    for(int i = 0;i<RTSA_MARKER_TOTAL_CNT;i++)
//    {
//        refreshMarkerEdit(i);
//    }
    if(index == RTSA_NOT_USE)
    {
        this->close();
    }
    if(index == RTSA_SHIFT_ENABLE)
    {
        mControl->setShiftKeyEnable(true);
        this->close();
    }
    return ;
}

/**
 * @brief  show digit input dialog
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void RtSa_Dialog_MarkerSetup::showInputDialog(qint32 index)
{
    mSelectInputID = index;
    if(mInputDialog->isHidden())
    {
        mInputDialog->setGeometry(mapToGlobal(QPoint(0,0)).x()/*+this->width()*//*-RTSA_DIGITAL_DIALOG_WIDTH*/,\
                                  mapToGlobal(QPoint(0,0)).y(),RTSA_DIGITAL_DIALOG_WIDTH,RTSA_DIGITAL_DIALOG_HEIGHT);
    }
    mInputDialog->initDisplay(index);
    mInputDialog->setProperty("status", rtsa_qssMode[mControl->GetDisplayMode()]);
    mInputDialog->setStyle(QApplication::style());
    if(mInputDialog->isHidden())
        mInputDialog->show();
    return ;
}
/**
 * @brief  Line edit clicked function.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void RtSa_Dialog_MarkerSetup::editclicked()
{
    qint32 showIndex;
    if(ui->pb_Normal->isChecked())
    {
        showIndex =  RTSA_INPUT_MARKER_EDIT;
    }else
    {
        showIndex =  RTSA_INPUT_DELTA_MARKER_EDIT;
    }
    showInputDialog(showIndex);
}

/**
 * @brief  Open all Marker.
 * @param  void
 * @author Tony
 * @since 2018-12-28
*/
//void RtSa_Dialog_MarkerSetup::on_pb_allon_clicked()
//{
//    for(qint32 i = 0;i<RTSA_MARKER_TOTAL_CNT;i++)
//    {
////        markerSelect(i);
//        mControl->setMarkerOn(i,true);
////        mMarkerViewGroup->button(i)->setChecked(true);
//    }
//    markerSelect(mCurrentMarker);
//    return ;
//}
/**
 * @brief  Select Marker nomal.
 * @param  void
 * @author Tony
 * @since 2019-01-11
*/
//void RtSa_Dialog_MarkerSetup::on_pb_normal_clicked()
//{
//    mControl->setMarkerType(mControl->getCurMarkerID(),RTSA_REF);
//    refreshMarkerEdit();
//    return;
//}
/**
 * @brief  Select Marker delta.
 * @param  void
 * @author Tony
 * @since 2019-01-11
*/
//void RtSa_Dialog_MarkerSetup::on_pb_delta_clicked()
//{
//    mControl->setMarkerType(mControl->getCurMarkerID(),RTSA_DELTA);
//    refreshMarkerEdit();
//    return;
//}
/**
 * @brief  Marker noise button clicked.
 * @param  void
 * @author Tony
 * @since 2019-01-11
 * */
//void RtSa_Dialog_MarkerSetup::on_pb_mkrnoise_clicked()
//{
//    mControl->setMarkerNoiseOn(mControl->getCurMarkerID(),ui->pb_mkrnoise->isChecked());
//    return;
//}

void RtSa_Dialog_MarkerSetup::on_edit_MkrFreq_clicked()
{
    editclicked();
    return;
}

void RtSa_Dialog_MarkerSetup::on_pb_cancel_clicked()
{
    mInputDialog->close();
    this->close();
    return;
}

void RtSa_Dialog_MarkerSetup::on_pb_toggle_toggled(bool checked)
{
    if(checked)
    {
        ui->pb_toggle->setText("On");
    }
    else
    {
        ui->pb_toggle->setText("Off");
    }
    mControl->setMarkerOn(mControl->getCurMarkerID(),checked);
//    refreshMarkerInfoBox();
    refreshMarkerType();
    refreshMarkerFreq();
    refreshMarkerNoise();
//    mIsAllMarkerButtonPressed = false;
    return;
}

void RtSa_Dialog_MarkerSetup::on_pb_mkrnoise_toggled(bool checked)
{
    if(checked)
    {
        ui->pb_mkrnoise->setText("On");
        mControl->setMarkerOn(mControl->getCurMarkerID(),checked);
    }
    else
    {
        ui->pb_mkrnoise->setText("Off");
    }
    mControl->setMarkerNoiseOn(mControl->getCurMarkerID(),checked);
//    refreshMarkerInfoBox();
//    refreshMarkerNoise();
    refreshMarkerType();
    refreshMarkerFreq();

    return;
}

void RtSa_Dialog_MarkerSetup::DigitalKeyRespond(QKeyEvent *event)
{
    if(!mControl->isMarkerOn(mControl->getCurMarkerID()))
    {
        return;
    }
    keyPressEvent(event);
    return;
}

void RtSa_Dialog_MarkerSetup::on_pb_peakTrack_toggled(bool checked)
{
    qint32 markerID = mControl->getCurMarkerID();
    if(checked)
    {
        ui->pb_peakTrack->setText("On");
        mControl->setMarkerOn(markerID,true);
    }
    else
    {
        ui->pb_peakTrack->setText("Off");
    }
    mControl->setPeakTrackOn(checked);
    if(mControl->isMarkerOn(markerID))
    {
        ui->pb_toggle->setChecked(true);
    }
    else
    {
        ui->pb_toggle->setChecked(false);
    }
    return;
}

void RtSa_Dialog_MarkerSetup::on_pb_MkrAllOn_clicked()
{
    for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT;i++)
    {
        mControl->setMarkerOn(i,true);
    }
    ui->pb_toggle->setChecked(true);
    return;
}

void RtSa_Dialog_MarkerSetup::on_pb_Normal_clicked()
{
    qint32 markerID = mControl->getCurMarkerID();
    mControl->setMarkerType(markerID,RTSA_REF);
//    mControl->setMarkerOn(markerID,true);
    refreshMarkerEdit();
    return;
}

void RtSa_Dialog_MarkerSetup::on_pb_Delta_clicked()
{
    qint32 markerID = mControl->getCurMarkerID();
    mControl->setMarkerType(markerID,RTSA_DELTA);
    refreshMarkerEdit();
    return;
}

void RtSa_Dialog_MarkerSetup::on_pb_Start_clicked()
{
    mControl->setMarkerToStart();
    return;
}

void RtSa_Dialog_MarkerSetup::on_pb_Center_clicked()
{
    mControl->setMarkerToCenter();
    return;
}

void RtSa_Dialog_MarkerSetup::on_pb_Stop_clicked()
{
    mControl->setMarkerToStop();
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-07-30
*/
void RtSa_Dialog_MarkerSetup::on_timeOut()
{
    timer->stop();
    qint32 FreqUnit = mInputDialog->getUnitNo();
    qreal tempStepFreq = (mControl->getSpan() / (RTSA_NUM_SWEEP_POINT - 1));

    if(!mInputDialog->isHidden())
    {
        mInputDialog->hide();
    }
    if(!mUpDownFlag)
    {
        switch (mSelectInputID)
        {
        case RTSA_INPUT_MARKER_EDIT:
        case RTSA_INPUT_DELTA_MARKER_EDIT:
            if(mControl->getSpan() < (RTSA_NUM_SWEEP_POINT - 1))
            {
                tempStepFreq = 1;
            }
            mControl->setMarkerFreq(mControl->getCurMarkerID(),mControl->getMarkerFreq(mControl->getCurMarkerID()) + tempStepFreq);
            refreshMarkerFreq();
            break;
        default:
            break;
        }
    }
    else
    {
        switch (mSelectInputID)
        {
        case RTSA_INPUT_MARKER_EDIT:
        case RTSA_INPUT_DELTA_MARKER_EDIT:
            if(mControl->getSpan() < (RTSA_NUM_SWEEP_POINT - 1))
            {
                tempStepFreq = 1;
            }
            mControl->setMarkerFreq(mControl->getCurMarkerID(),mControl->getMarkerFreq(mControl->getCurMarkerID()) - tempStepFreq);
            refreshMarkerFreq();
            break;
        default:
            break;
        }
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-12-17
*/
void RtSa_Dialog_MarkerSetup::refreshMarkerState()
{
    qint32 mMarkerIndex;
    mMarkerIndex = mControl->getCurMarkerID();
    if(mControl->isMarkerOn(mMarkerIndex))
    {
        ui->pb_toggle->setChecked(true);
    }
    else
    {
        ui->pb_toggle->setChecked(false);
    }
    refreshMarkerPeakTrack();
    return ;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-12-17
*/
void RtSa_Dialog_MarkerSetup::refreshMarkerPeakTrack()
{
    bool istrackOn = mControl->IsPeakTrackOn();
    if(istrackOn)
    {
        ui->pb_peakTrack->setText("On");
        ui->pb_peakTrack->setChecked(true);
    }
    else
    {
        ui->pb_peakTrack->setText("Off");
        ui->pb_peakTrack->setChecked(false);
    }
    return;
}

void RtSa_Dialog_MarkerSetup::on_pb_DeltaPair_clicked()
{
    qint32 markerID = mControl->getCurMarkerID();
    mControl->setMarkerType(markerID,RTSA_DELTA_PAIR);
    refreshMarkerEdit();
    return;
}
