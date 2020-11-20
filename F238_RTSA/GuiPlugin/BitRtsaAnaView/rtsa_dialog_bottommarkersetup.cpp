#include "rtsa_dialog_bottommarkersetup.h"
#include "ui_rtsa_dialog_bottommarkersetup.h"

RtSa_Dialog_BottomMarkerSetup::RtSa_Dialog_BottomMarkerSetup(RtSa_Interface *interface, RtSa_Dialog_Digitinput *mInput, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RtSa_Dialog_BottomMarkerSetup),
    mInputDialog(mInput),
    mControl(interface),
    pParent(parent),
    mSelectInputID(RTSA_INPUT_MARKER_EDIT)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint/*|Qt::Dialog*/);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
//    this->setAttribute(Qt::WA_DeleteOnClose);
    this->hide();
    connect(mControl,SIGNAL(BitViewMakerMoved(bool)),this ,SLOT(refreshMarkerTable()));
    connect(mControl,SIGNAL(BitViewChanged(quint32)),this,SLOT(On_DisplayChange()));
    connect(mControl,SIGNAL(BitViewMakerDraw(qint32,bool)),this,SLOT(MarkerInfoChange(qint32,bool)));
    connect(mControl,SIGNAL(BitViewMakerMoved(bool)),this ,SLOT(On_Update(bool)));
    connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
    InitGroup();
    refreshDisplay();
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(on_timeOut()));
    setProperty("status",rtsa_qssMode[mControl->GetDisplayMode()]);
}

RtSa_Dialog_BottomMarkerSetup::~RtSa_Dialog_BottomMarkerSetup()
{
    delete ui;
}
void RtSa_Dialog_BottomMarkerSetup::keyPressEvent(QKeyEvent *event)
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
void RtSa_Dialog_BottomMarkerSetup::on_pb_cancel_clicked()
{
    this->close();
//    qreal acqtime = mControl->getAcqTime();
//    mControl->setSleepTime(acqtime);
    pParent->setFocus();
    return;
}
void RtSa_Dialog_BottomMarkerSetup::InitGroup()
{
    mMarkerToGroup = new QButtonGroup();
    mMarkerToGroup->addButton(ui->pb_MkrToStart,RTSA_MARKER_TO_START);
    mMarkerToGroup->addButton(ui->pb_MkrToCenter,RTSA_MARKER_TO_CENTER);
    mMarkerToGroup->addButton(ui->pb_MkrToStop,RTSA_MARKER_TO_STOP);
    mMarkerToGroup->addButton(ui->pb_PeakSearch,RTSA_PEAK_SEARCH);
    mMarkerToGroup->addButton(ui->pb_MinSearch,RTSA_MIN_SEARCH);
    mMarkerToGroup->addButton(ui->pb_NextPeak,RTSA_NEXT_SEARCH);
    mMarkerToGroup->addButton(ui->pb_NextPeakLeft,RTSA_PEAK_NEXT_LEFT);
    mMarkerToGroup->addButton(ui->pb_NextPeakRight,RTSA_PEAK_NEXT_RIGHT);
    connect(mMarkerToGroup,SIGNAL(buttonClicked(qint32)),this,SLOT(MarkerToGroup_click(qint32)));
    return;
}
void RtSa_Dialog_BottomMarkerSetup::refreshDisplay()
{
    QString strTitle = QString("");
    qreal freq1 = mControl->getMarkerRefFreq(mControl->getCurMarkerID());
    qreal freq2 = mControl->getMarkerDeltaFreq(mControl->getCurMarkerID());
    qreal freq = (qreal)freq2;
    if(mControl->getMarkerType(mControl->getCurMarkerID()) != RTSA_REF)
    {
        freq = (qreal)freq2 - (qreal)freq1;
    }
    qint32 markerID = mControl->getCurMarkerID();
    strTitle.sprintf("M%d",markerID + 1);
    ui->lbTitle->setText(strTitle);
    strTitle = mControl->getFreqAdjustStr(freq);
    ui->lbFreq->setText(strTitle);
    strTitle = QString("--.--");
    if(mControl->isMarkerOn(markerID))
    {
        strTitle = mControl->getMarkerInfoStr(mControl->getCurMarkerID());
    }
    ui->label_2->setText(strTitle);
    if(mControl->isMarkerOn(mControl->getCurMarkerID()))
    {
        ui->pb_visible->setChecked(true);
        ui->pb_visible->setText("On");
    }
    else
    {
        ui->pb_visible->setChecked(false);
        ui->pb_visible->setText("Off");
    }
    qint32 markerType = mControl->getMarkerType(mControl->getCurMarkerID());
    if(markerType == RTSA_REF)
    {
        ui->pb_normal->setChecked(true);
        ui->pb_delta->setChecked(false);
        ui->pb_DeltaPair->setChecked(false);
    }
    else if(markerType == RTSA_DELTA)
    {
        ui->pb_normal->setChecked(false);
        ui->pb_delta->setChecked(true);
        ui->pb_DeltaPair->setChecked(false);
    }
    else
    {
        ui->pb_normal->setChecked(false);
        ui->pb_delta->setChecked(false);
        ui->pb_DeltaPair->setChecked(true);
    }

    if(mControl->IsPeakTrackOn())
    {
        ui->pb_PeakTrackOn->setText("On");
        ui->pb_PeakTrackOn->setChecked(true);
    }
    else
    {
        ui->pb_PeakTrackOn->setText("Off");
        ui->pb_PeakTrackOn->setChecked(false);
    }
    refreshMarkerFreq();
    return;
}

void RtSa_Dialog_BottomMarkerSetup::MarkerToGroup_click(qint32 index)
{
    switch(index)
    {
    case RTSA_MARKER_TO_START:
        mControl->setMarkerToStart();
        break;
    case RTSA_MARKER_TO_CENTER:
        mControl->setMarkerToCenter();
        break;
    case RTSA_MARKER_TO_STOP:
        mControl->setMarkerToStop();
        break;
    case RTSA_PEAK_SEARCH:
        mControl->setMarkerToPeak();
        break;
    case RTSA_MIN_SEARCH:
        mControl->setMarkerToMin();
        break;
    case RTSA_NEXT_SEARCH:
        mControl->setMarkerToNextPeak();
        break;
    case RTSA_PEAK_NEXT_LEFT:
        mControl->setMarkerToLeftPeak();
        break;
    case RTSA_PEAK_NEXT_RIGHT:
        mControl->setMarkerToRightPeak();
        break;
    }
    return ;
}

void RtSa_Dialog_BottomMarkerSetup::on_pb_normal_clicked()
{
    mControl->setMarkerType(mControl->getCurMarkerID(),RTSA_REF);
    ui->pb_normal->setChecked(true);
    ui->pb_delta->setChecked(false);
    refreshDisplay();
    return;
}

void RtSa_Dialog_BottomMarkerSetup::on_pb_delta_clicked()
{
    mControl->setMarkerType(mControl->getCurMarkerID(),RTSA_DELTA);
    ui->pb_normal->setChecked(false);
    ui->pb_delta->setChecked(true);
    refreshDisplay();
    return;
}

void RtSa_Dialog_BottomMarkerSetup::on_pb_MinSearch_clicked()
{
    mControl->setMarkerToMin();
    return;
}

void RtSa_Dialog_BottomMarkerSetup::on_pb_visible_toggled(bool checked)
{
    if(checked)
    {
        ui->pb_visible->setText("On");
    }
    else
    {
        ui->pb_visible->setText("Off");
        ui->pb_PeakTrackOn->setText("Off");
        ui->pb_PeakTrackOn->setChecked(false);
    }
    mControl->setMarkerOn(mControl->getCurMarkerID(),checked);
    return;
}

void RtSa_Dialog_BottomMarkerSetup::refreshMarkerTable()
{
    if(!mInputDialog->isHidden())
    {
        mInputDialog->hide();
    }
    qint32 markerID = mControl->getCurMarkerID();
    QString strTitle = QString("");
    qreal freq1 = mControl->getMarkerRefFreq(mControl->getCurMarkerID());
    qreal freq2 = mControl->getMarkerDeltaFreq(mControl->getCurMarkerID());
    qreal freq = (qreal)freq2;
    if(mControl->getMarkerType(mControl->getCurMarkerID()) != RTSA_REF)
    {
        freq = (qreal)freq2 - (qreal)freq1;
    }
    strTitle = mControl->getFreqAdjustStr(freq);
    ui->lbFreq->setText(strTitle);
    strTitle = mControl->getMarkerInfoStr(mControl->getCurMarkerID());
    ui->label_2->setText(strTitle);

    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-07-25
*/
void RtSa_Dialog_BottomMarkerSetup::On_DisplayChange()
{
    if(mControl->getCurBitviewType() == RTSA_SPECTROGRAM)
    {
        this->close();
        return;
    }
    refreshDisplay();
//    mMarkerSelectGroup->button(mControl->getCurMarkerID())->setChecked(true);
//    for(qint32 i = 0 ; i < RTSA_MARKER_TOTAL_CNT; i++)
//    {
//        mMarkerViewGroup->button(i)->setChecked(mControl->isMarkerOn(i));
//    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-07-25
*/
void RtSa_Dialog_BottomMarkerSetup::MarkerInfoChange(qint32 markerID,bool isOn)
{
    if(!isOn)
    {
        return;
    }
//    qint32 markerID = mControl->getCurMarkerID();
    QString strTitle = QString("");
    qreal freq1 = mControl->getMarkerRefFreq(mControl->getCurMarkerID());
    qreal freq2 = mControl->getMarkerDeltaFreq(mControl->getCurMarkerID());
    qreal freq = (qreal)freq2;
    if(mControl->getMarkerType(mControl->getCurMarkerID()) != RTSA_REF)
    {
        freq = (qreal)freq2 - (qreal)freq1;
    }
    strTitle = mControl->getFreqAdjustStr(freq);
    ui->lbFreq->setText(strTitle);
    strTitle = mControl->getMarkerInfoStr(mControl->getCurMarkerID());
    ui->label_2->setText(strTitle);

    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2020-02-14
*/
void RtSa_Dialog_BottomMarkerSetup::on_pb_PeakTrackOn_toggled(bool checked)
{
    qint32 markerID = mControl->getCurMarkerID();
    if(checked)
    {
        ui->pb_PeakTrackOn->setText("On");
        ui->pb_visible->setChecked(true);
        ui->pb_visible->setText("On");
        mControl->setMarkerOn(markerID,true);
    }
    else
    {
        ui->pb_PeakTrackOn->setText("Off");
    }
    mControl->setPeakTrackOn(checked);
    return ;
}

void RtSa_Dialog_BottomMarkerSetup::on_edit_MkrFreq_clicked()
{
    editclicked();
    return;
}

void RtSa_Dialog_BottomMarkerSetup::editclicked()
{
    qint32 showIndex;
    qint32 markerID = mControl->getCurMarkerID();
    if(mControl->getMarkerType(markerID) == RTSA_REF)
    {
        showIndex =  RTSA_INPUT_MARKER_EDIT;
    }else
    {
        showIndex =  RTSA_INPUT_DELTA_MARKER_EDIT;
    }
    showInputDialog(showIndex);
}

void RtSa_Dialog_BottomMarkerSetup::showInputDialog(qint32 index)
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


void RtSa_Dialog_BottomMarkerSetup::refreshMarkerFreq()
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

void RtSa_Dialog_BottomMarkerSetup::On_Update(bool isOn)
{
    if(isOn)
    {
        refreshMarkerFreq();
    }
    return;
}

void RtSa_Dialog_BottomMarkerSetup::on_timeOut()
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
void RtSa_Dialog_BottomMarkerSetup::on_finishEntry(qint32 index)
{
//    disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
//    mInputDialog = NULL;
    refreshMarkerFreq();
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

void RtSa_Dialog_BottomMarkerSetup::on_pb_DeltaPair_clicked()
{
    qint32 markerID = mControl->getCurMarkerID();
    mControl->setMarkerType(markerID,RTSA_DELTA_PAIR);
    refreshMarkerFreq();
    return;
}
