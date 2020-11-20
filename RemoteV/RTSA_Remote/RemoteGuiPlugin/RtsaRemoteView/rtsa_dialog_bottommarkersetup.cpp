#include "rtsa_dialog_bottommarkersetup.h"
#include "ui_rtsa_dialog_bottommarkersetup.h"

RtSa_Dialog_BottomMarkerSetup::RtSa_Dialog_BottomMarkerSetup(Rtsa_Remote_Interface *RtsaRemoteInterface, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RtSa_Dialog_BottomMarkerSetup),
    RemoteInterfaceObj(RtsaRemoteInterface),
    pParent(parent)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint/*|Qt::Dialog*/);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
//    this->setAttribute(Qt::WA_DeleteOnClose);
    this->hide();
    connect(RemoteInterfaceObj,SIGNAL(BitViewMakerMoved(bool)),this ,SLOT(refreshMarkerTable()));
    connect(RemoteInterfaceObj,SIGNAL(BitViewChanged(quint32)),this,SLOT(On_DisplayChange()));
    connect(RemoteInterfaceObj,SIGNAL(BitViewMakerDraw(qint32,bool)),this,SLOT(MarkerInfoChange(qint32,bool)));

    InitGroup();
    refreshDisplay();
    setProperty("status",rtsa_qssMode[RemoteInterfaceObj->GetDisplayMode()]);
}

RtSa_Dialog_BottomMarkerSetup::~RtSa_Dialog_BottomMarkerSetup()
{
    delete ui;
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
    qreal freq1 = RemoteInterfaceObj->getMarkerRefFreq(RemoteInterfaceObj->getCurMarkerID());
    qreal freq2 = RemoteInterfaceObj->getMarkerDeltaFreq(RemoteInterfaceObj->getCurMarkerID());
    qreal freq = (qreal)freq2;
    if(RemoteInterfaceObj->getMarkerType(RemoteInterfaceObj->getCurMarkerID()) == RTSA_DELTA)
    {
        freq = (qreal)freq2 - (qreal)freq1;
    }
    qint32 markerID = RemoteInterfaceObj->getCurMarkerID();
    strTitle.sprintf("M%d",markerID + 1);
    ui->lbTitle->setText(strTitle);
    strTitle = RemoteInterfaceObj->getFreqAdjustStr(freq);
    ui->lbFreq->setText(strTitle);
    strTitle = QString("--.--");
    if(RemoteInterfaceObj->isMarkerOn(markerID))
    {
        strTitle = RemoteInterfaceObj->getMarkerInfoStr(RemoteInterfaceObj->getCurMarkerID());
    }
    ui->label_2->setText(strTitle);
    if(RemoteInterfaceObj->isMarkerOn(RemoteInterfaceObj->getCurMarkerID()))
    {
        ui->pb_visible->setChecked(true);
        ui->pb_visible->setText("On");
    }
    else
    {
        ui->pb_visible->setChecked(false);
        ui->pb_visible->setText("Off");
    }
    if(RemoteInterfaceObj->getMarkerType(RemoteInterfaceObj->getCurMarkerID()) == RTSA_REF)
    {
        ui->pb_normal->setChecked(true);
        ui->pb_delta->setChecked(false);
    }
    else
    {
        ui->pb_normal->setChecked(false);
        ui->pb_delta->setChecked(true);
    }
    return;
}

void RtSa_Dialog_BottomMarkerSetup::MarkerToGroup_click(qint32 index)
{
    switch(index)
    {
    case RTSA_MARKER_TO_START:
        RemoteInterfaceObj->setMarkerToStart();
        break;
    case RTSA_MARKER_TO_CENTER:
        RemoteInterfaceObj->setMarkerToCenter();
        break;
    case RTSA_MARKER_TO_STOP:
        RemoteInterfaceObj->setMarkerToStop();
        break;
    case RTSA_PEAK_SEARCH:
        RemoteInterfaceObj->setMarkerToPeak();
        break;
    case RTSA_MIN_SEARCH:
        RemoteInterfaceObj->setMarkerToMin();
        break;
    case RTSA_NEXT_SEARCH:
        RemoteInterfaceObj->setMarkerToNextPeak();
        break;
    case RTSA_PEAK_NEXT_LEFT:
        RemoteInterfaceObj->setMarkerToLeftPeak();
        break;
    case RTSA_PEAK_NEXT_RIGHT:
        RemoteInterfaceObj->setMarkerToRightPeak();
        break;
    }
    return ;
}

void RtSa_Dialog_BottomMarkerSetup::on_pb_normal_clicked()
{
    RemoteInterfaceObj->setMarkerType(RemoteInterfaceObj->getCurMarkerID(),RTSA_REF);
    ui->pb_normal->setChecked(true);
    ui->pb_delta->setChecked(false);
    refreshDisplay();
    return;
}

void RtSa_Dialog_BottomMarkerSetup::on_pb_delta_clicked()
{
    RemoteInterfaceObj->setMarkerType(RemoteInterfaceObj->getCurMarkerID(),RTSA_DELTA);
    ui->pb_normal->setChecked(false);
    ui->pb_delta->setChecked(true);
    refreshDisplay();
    return;
}

void RtSa_Dialog_BottomMarkerSetup::on_pb_MinSearch_clicked()
{
    RemoteInterfaceObj->setMarkerToMin();
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
    }
    RemoteInterfaceObj->setMarkerOn(RemoteInterfaceObj->getCurMarkerID(),checked);
    return;
}

void RtSa_Dialog_BottomMarkerSetup::refreshMarkerTable()
{
//    qint32 markerID = RemoteInterfaceObj->getCurMarkerID();
    QString strTitle = QString("");
    qreal freq1 = RemoteInterfaceObj->getMarkerRefFreq(RemoteInterfaceObj->getCurMarkerID());
    qreal freq2 = RemoteInterfaceObj->getMarkerDeltaFreq(RemoteInterfaceObj->getCurMarkerID());
    qreal freq = (qreal)freq2;
    if(RemoteInterfaceObj->getMarkerType(RemoteInterfaceObj->getCurMarkerID()) == RTSA_DELTA)
    {
        freq = (qreal)freq2 - (qreal)freq1;
    }
    strTitle = RemoteInterfaceObj->getFreqAdjustStr(freq);
    ui->lbFreq->setText(strTitle);
    strTitle = RemoteInterfaceObj->getMarkerInfoStr(RemoteInterfaceObj->getCurMarkerID());
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
    if(RemoteInterfaceObj->getCurBitviewType() == RTSA_SPECTROGRAM)
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
    qreal freq1 = RemoteInterfaceObj->getMarkerRefFreq(RemoteInterfaceObj->getCurMarkerID());
    qreal freq2 = RemoteInterfaceObj->getMarkerDeltaFreq(RemoteInterfaceObj->getCurMarkerID());
    qreal freq = (qreal)freq2;
    if(RemoteInterfaceObj->getMarkerType(RemoteInterfaceObj->getCurMarkerID()) == RTSA_DELTA)
    {
        freq = (qreal)freq2 - (qreal)freq1;
    }
    strTitle = RemoteInterfaceObj->getFreqAdjustStr(freq);
    ui->lbFreq->setText(strTitle);
    strTitle = RemoteInterfaceObj->getMarkerInfoStr(RemoteInterfaceObj->getCurMarkerID());
    ui->label_2->setText(strTitle);

    return;
}
