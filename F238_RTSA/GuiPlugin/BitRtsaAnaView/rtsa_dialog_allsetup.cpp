#include "rtsa_dialog_allsetup.h"
#include "ui_rtsa_dialog_allsetup.h"

RtSa_Dialog_AllSetup::RtSa_Dialog_AllSetup(RtSa_Interface *interface, RtSa_Dialog_Digitinput *input, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RtSa_Dialog_AllSetup),
    mControl(interface),
    mInputDialog(input),
    mLastWidgetID(RTSA_INPUT_FREQ_CENTER),
    mChStdDialog(NULL),
    mLastCombID(RTSA_ALLSET_INPUT_UNIT)
//    mChStdDialog(NULL)
{
//    setAttribute(Qt::WA_DeleteOnClose);
    this->setAttribute(Qt::WA_NoChildEventsForParent,true);

    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint| Qt::Dialog /*| Qt::Dialog*/);
//    setAttribute(Qt::WA_StyledBackground,true);
//    setAttribute(Qt::WA_OpaquePaintEvent,true);
    ui->setupUi(this);
//    this->setAttribute(Qt::WA_DeleteOnClose);
    mUserVariable = mControl->getGlobalUserVariable();
    initMap();
    initDisplay();
    connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(refreshEditDisplay(qint32)));
//    connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(refreshEditDisplay(qint32)));
//    connect(mInputDialog,SIGNAL(ClockWiseDown(QKeyEvent*)),this,SLOT(DigitalKeyRespond(QKeyEvent*)));
    this->hide();
    ui->Freq_Center->setFocus();
    this->setProperty("status",rtsa_qssMode[mControl->GetDisplayMode()]);
    this->setStyle(QApplication::style());
}

RtSa_Dialog_AllSetup::~RtSa_Dialog_AllSetup()
{
    delete ui;
}
void RtSa_Dialog_AllSetup::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape || event->key() == Qt::Key_Shift)
    {
        if(!mInputDialog->isHidden())
        {
            mInputDialog->close();
        }
        this->close();
        return;
    }
    if(event->key() == Qt::Key_PowerOff)
    {
        if(!event->isAutoRepeat())   
        {
            QApplication::sendEvent(this->parent(),event);
        }
        return;
    }
    return;
}
/**
* @brief initMap
* @param none
* @Author Albert
* @date 2019-04-01
*/
void RtSa_Dialog_AllSetup::initMap()
{
    //freq
    mWidgetList.insert(RTSA_INPUT_FREQ_CENTER,ui->Freq_Center);
    connect(ui->Freq_Center,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(RTSA_INPUT_FREQ_START,ui->Freq_Start);
    connect(ui->Freq_Start,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(RTSA_INPUT_FREQ_STOP,ui->Freq_Stop);
    connect(ui->Freq_Stop,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(RTSA_INPUT_FREQ_SPAN,ui->Span);
    connect(ui->Span,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(RTSA_INPUT_FREQ_CF,ui->Freq_Step);
    connect(ui->Freq_Step,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(RTSA_INPUT_FREQ_OFFSET,ui->Freq_Offset);
    connect(ui->Freq_Offset,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(RTSA_INPUT_FREQ_CHANNEL_STANDARD,ui->Channel_STD);
    connect(ui->Channel_STD,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(RTSA_INPUT_FREQ_CHANNEL_NUM,ui->Channel_Num);
    connect(ui->Channel_Num,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(RTSA_INPUT_FREQ_CHANNEL_STEP,ui->Channel_Step);
    connect(ui->Channel_Step,SIGNAL(clicked()),this,SLOT(on_clicked()));

    //Ampt
    mWidgetList.insert(RTSA_INPUT_REF_LEVEL,ui->Ref_Level);
    connect(ui->Ref_Level,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(RTSA_INPUT_REF_OFFSET,ui->Ref_Offset);
    connect(ui->Ref_Offset,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(RTSA_INPUT_SCALEDIV,ui->Scale_Division);
    connect(ui->Scale_Division,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(RTSA_INPUT_ATTEN,ui->Atten_Value);
    connect(ui->Atten_Value,SIGNAL(clicked()),this,SLOT(on_clicked()));

    //Sweep
    mWidgetList.insert(RTSA_INPUT_ACQ_TIME,ui->Acq_Time);
    connect(ui->Acq_Time,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(RTSA_INPUT_PERSISTENCE_TIME,ui->Persistence_Value);
    connect(ui->Persistence_Value,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(RTSA_INPUT_HIGHEST_DENSITY,ui->High_Density);
    connect(ui->High_Density,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(RTSA_INPUT_LOWEST_DENSITY,ui->Low_Density);
    connect(ui->Low_Density,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(RTSA_INPUT_CURVE,ui->Curve);
    connect(ui->Curve,SIGNAL(clicked()),this,SLOT(on_clicked()));

    //trace
    mWidgetList.insert(RTSA_INPUT_AVERAGE_COUNT,ui->Average);
    connect(ui->Average,SIGNAL(clicked()),this,SLOT(on_clicked()));

    mWidgetList.insert(RTSA_ALLSET_INPUT_UNIT,ui->Scale_Unit);
    connect(ui->Scale_Unit,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(RTSA_ALLSET_INPUT_RBW,ui->RBW_Freq);
    connect(ui->RBW_Freq,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(RTSA_ALLSET_INPUT_FFTWINDOW,ui->VBW_Freq);
    connect(ui->VBW_Freq,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(RTSA_ALLSET_INPUT_TRIGGER_MODE,ui->Trigger_Type);
    connect(ui->Trigger_Type,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(RTSA_ALLSET_INPUT_TRACE_SEL,ui->Trace_Select);
    connect(ui->Trace_Select,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(RTSA_ALLSET_INPUT_TRACE_TYPE,ui->Trace_Type);
    connect(ui->Trace_Type,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(RTSA_ALLSET_INPUT_DETECTOR,ui->Detectors);
    connect(ui->Detectors,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(RTSA_ALLSET_INPUT_MARKER_SEL,ui->Marker_Select);
    connect(ui->Marker_Select,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(RTSA_ALLSET_INPUT_MARKER_TO,ui->Marker_Type_2);
    connect(ui->Marker_Type_2,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(RTSA_ALLSET_INPUT_LIMIT_SEL,ui->Limit_Select);
    connect(ui->Limit_Select,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(RTSA_INPUT_MARGIN,ui->Limit_Edge);
    connect(ui->Limit_Edge,SIGNAL(clicked()),this,SLOT(on_clicked()));

    mCombList.insert(RTSA_ALLSET_INPUT_UNIT,ui->value_Unit);
    connect(ui->value_Unit,SIGNAL(clicked(RtSa_CombBox*)),this,SLOT(on_Combclicked()));
    mCombList.insert(RTSA_ALLSET_INPUT_RBW,ui->value_RBW);
    connect(ui->value_RBW,SIGNAL(clicked(RtSa_CombBox*)),this,SLOT(on_Combclicked()));
    mCombList.insert(RTSA_ALLSET_INPUT_FFTWINDOW,ui->value_VBW);
    connect(ui->value_VBW,SIGNAL(clicked(RtSa_CombBox*)),this,SLOT(on_Combclicked()));
    mCombList.insert(RTSA_ALLSET_INPUT_TRIGGER_MODE,ui->value_Trigger);
    connect(ui->value_Trigger,SIGNAL(clicked(RtSa_CombBox*)),this,SLOT(on_Combclicked()));
    mCombList.insert(RTSA_ALLSET_INPUT_TRACE_SEL,ui->value_Trace);
    connect(ui->value_Trace,SIGNAL(clicked(RtSa_CombBox*)),this,SLOT(on_Combclicked()));
    mCombList.insert(RTSA_ALLSET_INPUT_TRACE_TYPE,ui->value_TraceType);
    connect(ui->value_TraceType,SIGNAL(clicked(RtSa_CombBox*)),this,SLOT(on_Combclicked()));
    mCombList.insert(RTSA_ALLSET_INPUT_DETECTOR,ui->value_Detectors);
    connect(ui->value_Detectors,SIGNAL(clicked(RtSa_CombBox*)),this,SLOT(on_Combclicked()));
    mCombList.insert(RTSA_ALLSET_INPUT_MARKER_SEL,ui->value_MarkerSelect);
    connect(ui->value_MarkerSelect,SIGNAL(clicked(RtSa_CombBox*)),this,SLOT(on_Combclicked()));
    mCombList.insert(RTSA_ALLSET_INPUT_MARKER_TO,ui->value_MarkerTo);
    connect(ui->value_MarkerTo,SIGNAL(clicked(RtSa_CombBox*)),this,SLOT(on_Combclicked()));
    mCombList.insert(RTSA_ALLSET_INPUT_LIMIT_SEL,ui->value_LimitSelect);
    connect(ui->value_LimitSelect,SIGNAL(clicked(RtSa_CombBox*)),this,SLOT(on_Combclicked()));

    ui->value_Unit->setPopupPotion(RTSA_TOP,-ui->value_Unit->x(),-ui->value_Unit->y()- 2);
    ui->value_MarkerSelect->setPopupPotion(RTSA_BOTTOM,-ui->value_MarkerSelect->x(),ui->Marker_Select->y() - ui->Marker_Select->height());
    ui->value_Trace->setPopupPotion(RTSA_BOTTOM,-ui->value_Trace->x(),2);
    ui->value_TraceType->setPopupPotion(RTSA_BOTTOM,-ui->value_TraceType->x(),2);
    ui->value_Detectors->setPopupPotion(RTSA_BOTTOM,-ui->value_Detectors->x(),2);
    ui->value_VBW->setPopupPotion(RTSA_BOTTOM,-ui->value_VBW->x(),-1);
    ui->value_RBW->setPopupPotion(RTSA_BOTTOM,-ui->value_RBW->x(),2);
    ui->value_LimitSelect->setPopupPotion(RTSA_BOTTOM,-ui->value_LimitSelect->x(),2);
    ui->value_Trigger->setPopupPotion(RTSA_BOTTOM,-ui->value_Trigger->x(),2);
//    ui->value_Atten->setPopupPotion(RTSA_BOTTOM,-ui->value_Atten->x(),2);
    return;
}
void RtSa_Dialog_AllSetup::initDisplay()
{
    refreshFreq();
    refreshAmpt();
    refreshSweep();
    refreshBW();
    refreshTrace();
    refreshMarker();
    refreshTrigger();
    return;
}
void RtSa_Dialog_AllSetup::showInputDialog(qint32 index)
{
    if(mInputDialog)
    {
    }
    else
    {
//        mInputDialog = new RtSa_Dialog_Digitinput(this);
//        mInputDialog->setInterface(mControl);
//        mInputDialog->setUserVariable(mUserVariable);
//        mInputDialog->setFocusPolicy(Qt::NoFocus);
//        mInputDialog->move(0,0);
//        connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
    }
    qint32 xPos = mapToGlobal(QPoint(0,0)).x() + mWidgetList.value(index)->x() + mWidgetList.value(index)->width();
    qint32 yPos = mapToGlobal(QPoint(0,0)).y() + 45;
    if(index == RTSA_INPUT_AVERAGE_COUNT)
    {
        xPos = mapToGlobal(QPoint(0,0)).x() + mWidgetList.value(index)->x() - mInputDialog->width();
        yPos = mapToGlobal(QPoint(0,0)).y() + 45;
    }
    mInputDialog->move(xPos,yPos);
    mInputDialog->initDisplay(index);
    mInputDialog->setProperty("status", rtsa_qssMode[mControl->GetDisplayMode()]);
    mInputDialog->setStyle(QApplication::style());
    mInputDialog->show();
    return;
}
void RtSa_Dialog_AllSetup::on_finishEntry(qint32 index)
{
//    disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
//    mInputDialog = NULL;

   if(mWidgetList.contains(index))
        refreshEditDisplay(index);
    return ;
}
void RtSa_Dialog_AllSetup::refreshEditDisplay(qint32 index)
{
    qreal freq;
    QString strGab;
    switch (index) {
    case RTSA_INPUT_FREQ_CENTER:
    case RTSA_INPUT_FREQ_START:
    case RTSA_INPUT_FREQ_STOP:
    case RTSA_INPUT_FREQ_SPAN:
        refreshFreq();
        break;
    case RTSA_INPUT_FREQ_CF:
        strGab = mControl->getFreqStr(RTSA_STEP_FREQ);
        ui->value_StopFreq->setText(strGab);
        break;
    case RTSA_INPUT_REF_LEVEL:
    case RTSA_INPUT_ATTEN:
    case RTSA_INPUT_SCALEDIV:
    case RTSA_INPUT_REF_OFFSET:
        refreshAmpt();
        break;
    case RTSA_INPUT_PERSISTENCE_TIME:
    case RTSA_INPUT_HIGHEST_DENSITY:
    case RTSA_INPUT_LOWEST_DENSITY:
    case RTSA_INPUT_CURVE:
    case RTSA_INPUT_ACQ_TIME:
        refreshSweep();
        break;
    case RTSA_INPUT_AVERAGE_COUNT:
        refreshTrace();
        break;
    default:
        break;
    }
    return;
}
void RtSa_Dialog_AllSetup::refreshBtnInfo()
{
    return;
}
void RtSa_Dialog_AllSetup::refreshDisplay(qint32 index)
{
    return;
}
void RtSa_Dialog_AllSetup::refreshUnit()
{
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-07-31
*/
void RtSa_Dialog_AllSetup::refreshTrigger()
{
    qint32 triggerMode = mControl->getTrigger();

    if(triggerMode >= RTSA_TRIGGER_FMTMASK)
    {
        ui->value_Trigger->setCurrentIndex(triggerMode - 1);
    }
    else if(triggerMode == RTSA_TRIGGER_EXTERNAL)
    {
        ui->value_Trigger->setCurrentIndex(triggerMode - 1);
    }
    else if(triggerMode == RTSA_TRIGGER_PERIODIC_TIMER)
    {
        ui->value_Trigger->setCurrentIndex(triggerMode - 1);
    }
    else if(triggerMode == RTSA_TRIGGER_FREE_RUN)
    {
        ui->value_Trigger->setCurrentIndex(RTSA_TRIGGER_FREE_RUN);
    }
    else if(triggerMode == RTSA_TRIGGER_RF_BURST)
    {
        ui->value_Trigger->setCurrentIndex(triggerMode - 1);
    }
    return;
}
void RtSa_Dialog_AllSetup::refreshTrace()
{
    qint32 intGab;
    QString strGab;
    qint32 curTraceIndex = mControl->getCurTrace();

    ui->value_Trace->setCurrentIndex(curTraceIndex);

    intGab = mControl->getTraceType(curTraceIndex);
    ui->value_TraceType->setCurrentIndex(intGab/* - 1*/);
    if(intGab == RTSA_TRACE_OFF)
    {
        ui->btn_TraceView->setChecked(false);
    }
    else
    {
        ui->btn_TraceView->setChecked(true);
    }
    if(intGab <= RTSA_CLEAR_WRITE)
    {
        ui->value_TraceType->setCurrentIndex(0);
    }
    else
    {
        ui->value_TraceType->setCurrentIndex(intGab /*- 1*/);
    }

    intGab = mControl->getDectorType();
    ui->value_Detectors->setCurrentIndex(intGab);

//    intGab = mControl->getTraceType(curTraceIndex);
//    if(intGab == (RTSA_AVERAGE - 1))
//    {
//    }
    intGab = mControl->getAvgNum(curTraceIndex);
    strGab = QString::number(intGab);
    ui->value_Average->setText(strGab);
    return;
}
void RtSa_Dialog_AllSetup::refreshMarker()
{
    QString strGab;
    qreal valGab;
    qint32 intGab;
    bool blGab;
    qint32 curMarkerID = mControl->getCurMarkerID();

    ui->value_MarkerSelect->setCurrentIndex(curMarkerID);

    blGab = mControl->isMarkerOn(curMarkerID);
    if(blGab)
    {
        ui->btn_MarkerView->setText("On");
    }
    else
    {
        ui->btn_MarkerView->setText("Off");
    }
    ui->btn_MarkerView->setChecked(blGab);

    intGab = mControl->getMarkerType(curMarkerID);
    if(intGab == RTSA_REF)
    {
        ui->Marker_Normal->setChecked(true);
    }
    else
    {
        ui->Marker_Delta->setChecked(true);
    }
    blGab = true;
    for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
    {
        if(!mControl->isMarkerOn(i))
        {
            blGab = false;
            break;
        }
    }
    if(blGab)
    {
        ui->btn_MarkerView_2->setText("All On");
    }
    else
    {
        ui->btn_MarkerView_2->setText("All Off");
    }
    ui->btn_MarkerView_2->setChecked(blGab);

    blGab = mControl->IsMarkerNoiseOn(curMarkerID);
    if(blGab)
    {
        ui->btn_NoiseMarker->setText("On");
    }
    else
    {
        ui->btn_NoiseMarker->setText("Off");
    }
    ui->btn_NoiseMarker->setChecked(blGab);

    return;
}
void RtSa_Dialog_AllSetup::digitInputClose()
{
    return;
}
void RtSa_Dialog_AllSetup::on_Span_Full_clicked()
{
    mControl->setFullSpan();
    refreshFreq();
    return;
}

void RtSa_Dialog_AllSetup::on_pb_cancel_clicked()
{
    if(!mInputDialog->isHidden())
    {
        mInputDialog->close();
    }
    this->close();
    return;
}

//void RtSa_Dialog_AllSetup::on_leCenterFreq_clicked()
//{
//    return;
//}

void RtSa_Dialog_AllSetup::on_clicked()
{
    if(!mInputDialog->isHidden())
    {
        mInputDialog->hide();
    }
    qint32 index;
    RtSa_ClickedWidget* widget = qobject_cast<RtSa_ClickedWidget*>(sender());
    index = mWidgetList.key(widget,-1);
    if(index == -1)
    {
        return ;
    }
    mCombList.value(mLastCombID)->setStyleSheet("border:0px flat rgba(162,115,0,1);");
    mWidgetList.value(mLastWidgetID)->setStyleSheet("#widget>QWidget{border:0px flat rgba(162,115,0,1);}");
    mWidgetList.value(index)->setStyleSheet("#widget>QWidget{border:2px solid rgba(162,115,0,1);}");
    if(index >= RTSA_ALLSET_INPUT_UNIT && index <= RTSA_ALLSET_INPUT_LIMIT_SEL)
    {
        mLastWidgetID = index;
        return;
    }
    switch (index) {
    case RTSA_INPUT_FREQ_CHANNEL_STANDARD:
        showCHStdDialog();
        mLastWidgetID = index;
        return;
    case RTSA_INPUT_FREQ_CHANNEL_NUM:
        break;
    case RTSA_INPUT_FREQ_CHANNEL_STEP:
        mLastWidgetID = index;
        return;
    default:
        break;
    }
    showInputDialog(index);
    mLastWidgetID = index;
    return;
}

void RtSa_Dialog_AllSetup::on_Combclicked()
{
    if(mInputDialog)
    {
        mInputDialog->close();
    }
    qint32 index;
    RtSa_CombBox* widget = qobject_cast<RtSa_CombBox*>(sender());
    index = mCombList.key(widget,-1);
    if(index == -1)
    {
        return ;
    }

    mWidgetList.value(mLastWidgetID)->setStyleSheet("#widget>QWidget{border:0px flat rgba(162,115,0,1);}");
    mCombList.value(mLastCombID)->setStyleSheet("border:0px flat rgba(162,115,0,1);");
    mCombList.value(index)->setStyleSheet("border:2px solid rgba(162,115,0,1);");
    mLastCombID = index;
    this->repaint();
    return;
}
/**
* @brief showCHStdDialog
* @param
* @Author Albert
* @date 2019-04-18
*/
void RtSa_Dialog_AllSetup::showCHStdDialog()
{
    if(mInputDialog)
    {
        mInputDialog->close();
    }
    if(mChStdDialog != NULL)
    {
        disconnect(mChStdDialog,SIGNAL(destroyed()),this,SLOT(on_CHStdClose()));
        delete mChStdDialog;
        mChStdDialog = NULL;
    }
    mChStdDialog = new RtSa_Dialog_Ch_Std(mControl,mUserVariable,this);
    mChStdDialog->setGeometry(0,0,this->width(),this->height());
//    mChStdDialog->resize(this->width(),this->height());
    mChStdDialog->setFocus();
    connect(mChStdDialog,SIGNAL(destroyed()),this,SLOT(on_CHStdClose()));
    mChStdDialog->show();
    return;
}
/**
* @brief on_CHStdClose
* @param
* @Author Albert
* @date 2019-04-18
*/
void RtSa_Dialog_AllSetup::on_CHStdClose()
{
    if(!mChStdDialog)
        return;
    disconnect(mChStdDialog,SIGNAL(destroyed()),this,SLOT(on_CHStdClose()));
    mChStdDialog = NULL;
    delete mChStdDialog;
    this->setFocus();
    refreshEditDisplay(RTSA_INPUT_FREQ_CENTER);
    return;
}
/**
* @brief on_pb_nextPage_clicked
* @param
* @Author Albert
* @date 2019-04-18
*/
void RtSa_Dialog_AllSetup::on_pb_nextPage_clicked()
{
    if(mInputDialog)
        on_finishEntry(mLastWidgetID);
    else if(mChStdDialog)
    {
        on_CHStdClose();
    }
//    lastWidget = curWidget;
//    curWidget = SA_ALLSET_MARKERSELECT;
//    refreshFocus();
    ui->stackedWidget->setCurrentIndex(1);
    return;
}
/**
* @brief on_pb_prePage_2_clicked
* @param
* @Author Albert
* @date 2019-04-18
*/
void RtSa_Dialog_AllSetup::on_pb_prePage_2_clicked()
{
    if(mInputDialog)
        on_finishEntry(mLastWidgetID);
    else if(mChStdDialog)
    {
        on_CHStdClose();
    }
//    lastWidget = curWidget;
//    curWidget = 0;
//    refreshFocus();
    ui->stackedWidget->setCurrentIndex(0);
    return;
}
/**
* @brief refreshFreq
* @param
* @Author Albert
* @date 2019-04-18
*/
void RtSa_Dialog_AllSetup::refreshFreq()
{
    QString strGab;
    strGab = mControl->getFreqStr(RTSA_CENTER_FREQ);
    ui->value_CenterFreq->setText(strGab);
    strGab = mControl->getFreqStr(RTSA_START_FREQ);
    ui->value_StartFreq->setText(strGab);
    strGab = mControl->getFreqStr(RTSA_STOP_FREQ);
    ui->value_StopFreq->setText(strGab);
    strGab = mControl->getFreqStr(RTSA_SPAN_FREQ);
    ui->value_Span->setText(strGab);
    strGab = mControl->getFreqStr(RTSA_STEP_FREQ);
    ui->value_StopFreq->setText(strGab);

    if(mUserVariable->gTecIndex < 0 || !mUserVariable->IsFreqInCurChStd())
    {
        strGab = "None";
        ui->value_Channel->setText(strGab);
        ui->value_ChannelNum->setText(strGab);
        ui->value_ChannelStep->setText("1");
    }
    else
    {
        strGab = QString(mRTSA_ChStand[mUserVariable->gTecIndex].name);
        ui->value_Channel->setText(strGab);
        strGab = QString::number(mControl->getChannelNumber());
        ui->value_ChannelNum->setText(strGab);
        strGab = mControl->getFreqAdjustStr(mUserVariable->gChannelStep);
        ui->value_ChannelStep->setText(strGab);
    }
    return;
}
/**
* @brief refreshAmpt
* @param
* @Author Albert
* @date 2019-04-18
*/
void RtSa_Dialog_AllSetup::refreshAmpt()
{
    QString strGab;
    qreal valGab;
    bool blGab;

    strGab = mControl->getRefLevelAdjustStr();
    ui->value_Ref_Level->setText(strGab);

    valGab = mControl->getScaleDiv();
    strGab = QString::number(valGab);
    ui->value_Scale->setText(strGab);

    valGab = mControl->getAttenVal();
    strGab = QString::number(valGab);
    ui->value_AttenValue->setText(strGab);

    valGab = mControl->getRefOffset();
    strGab = QString::number(valGab);
    ui->value_RefOffset->setText(strGab);

    blGab = mControl->IsAttenAuto();
    if(blGab)
    {
        ui->Atten_Auto->setChecked(true);
    }
    else
    {
        ui->Atten_Manual->setChecked(true);
    }
    blGab = mControl->IsPreAmpOn();
    if(blGab)
    {
        ui->btn_Preamp->setText("On");
    }
    else
    {
        ui->btn_Preamp->setText("Off");
    }
    ui->btn_Preamp->setChecked(blGab);
    return;
}
/**
* @brief refreshSweep
* @param
* @Author Albert
* @date 2019-04-18
*/
void RtSa_Dialog_AllSetup::refreshSweep()
{
    bool blGab;
    QString strGab;
    qreal valGab;
    qint32 intGab;

    valGab = mControl->getAcqTime();
    strGab = mControl->getAdjustTimeStr(valGab);
    ui->value_Acqtime->setText(strGab);

    valGab = mControl->getPersistenceTime();
    strGab = mControl->getAdjustTimeStr(valGab);
    ui->value_Persistence->setText(strGab);

    intGab = mControl->getHighestDensity();
    strGab = QString::number(intGab) + QString(" %");
    ui->value_HighDensity->setText(strGab);

    intGab = mControl->getLowestDensity();
    strGab = QString::number(intGab) + QString(" %");
    ui->value_LowDensity->setText(strGab);

    intGab = mControl->getCurve();
    strGab = QString::number(intGab) + QString(" %");
    ui->value_Curve->setText(strGab);

    blGab = mControl->IsSingleSweep();
    if(blGab)
    {
        ui->Sweep_Single->setChecked(true);
    }
    else
    {
        ui->Sweep_Conti->setChecked(true);
    }

    blGab = mControl->IsAcqTimeAuto();
    if(blGab)
    {
        ui->Acqtime_Auto->setChecked(true);
    }
    else
    {
        ui->Acqtime_Man->setChecked(true);
    }

    blGab = mControl->IsPersistenceTimeInfinite();
    if(blGab)
    {
        ui->Persistence_Infinite->setChecked(true);
    }
    else
    {
        ui->Persistence_Finite->setChecked(true);
    }

    return;
}
/**
* @brief refreshBW
* @param
* @Author Albert
* @date 2019-04-18
*/
void RtSa_Dialog_AllSetup::refreshBW()
{
    QString strGab;
    qint32 intGab;
    qreal dbGab;
    bool lbGab;

    for(qint32 i = RTSA_RBW0 ; i < RTSA_RBW6 + 1; i++)
    {
        dbGab = mControl->getCurIndexBW(i);
        strGab = mControl->getFreqAdjustStr(dbGab);
        ui->value_RBW->setItemText(i,strGab);
    }
    intGab = mControl->getBWIndex();
    ui->value_RBW->setCurrentIndex(intGab);

    intGab = mControl->getFFTWindow();
    ui->value_VBW->setCurrentIndex(intGab);

    lbGab = mControl->IsBWAuto();
    if(lbGab)
    {
        ui->RBW_Auto->setChecked(true);
    }
    else
    {
        ui->RBW_Manual->setChecked(true);
    }

    return;
}
/**
* @brief  on_Auto_Scale_clicked
* @param
* @Author Albert
* @date 2019-04-18
*/
void RtSa_Dialog_AllSetup::on_Auto_Scale_clicked()
{
    mControl->setAutoScale();
    refreshAmpt();
    return;
}
/**
* @brief on_value_Unit_currentIndexChanged
* @param change unit
* @Author Albert
* @date 2019-04-18
*/
void RtSa_Dialog_AllSetup::on_value_Unit_currentIndexChanged(int index)
{
    mControl->setAmptUnit(index);
    refreshAmpt();
    return;
}
/**
* @brief on_Atten_Auto_clicked
* @param set atten auto
* @Author Albert
* @date 2019-04-18
*/
void RtSa_Dialog_AllSetup::on_Atten_Auto_clicked()
{
    mControl->setAttenAuto(true);
    refreshAmpt();
    return;
}
/**
* @brief on_Atten_Manual_clicked
* @param set atten manual
* @Author Albert
* @date 2019-04-18
*/
void RtSa_Dialog_AllSetup::on_Atten_Manual_clicked()
{
    mControl->setAttenAuto(false);
    refreshAmpt();
    return;
}
/**
* @brief on_btn_Preamp_toggled
* @param set preamp on/off
* @Author Albert
* @date 2019-04-18
*/
void RtSa_Dialog_AllSetup::on_btn_Preamp_toggled(bool checked)
{
    mControl->setPreAmpOn(checked);
    refreshAmpt();
    return;
}
/**
* @brief  on_Sweep_Conti_clicked
* @param set sweep continue
* @Author Albert
* @date 2019-04-18
*/
void RtSa_Dialog_AllSetup::on_Sweep_Conti_clicked()
{
    mControl->setSingleSweep(false);
    return;
}
/**
* @brief on_Sweep_Single_clicked
* @param set sweep single
* @Author Albert
* @date 2019-04-18
*/
void RtSa_Dialog_AllSetup::on_Sweep_Single_clicked()
{
    mControl->setSingleSweep(true);
    return;
}
/**
* @brief on_value_RBW_currentIndexChanged
* @param select rbw index
* @Author Albert
* @date 2019-04-18
*/
void RtSa_Dialog_AllSetup::on_value_RBW_currentIndexChanged(int index)
{
    mControl->setBWIndex(index);
    ui->RBW_Manual->setChecked(true);
    return;
}
/**
* @brief on_value_VBW_currentIndexChanged
* @param select FFT WINDOW
* @Author Albert
* @date 2019-04-18
*/
void RtSa_Dialog_AllSetup::on_value_VBW_currentIndexChanged(int index)
{
    qint32 intGab;
    qreal dbGab;
    QString strGab;
    mControl->setFFTWindow(index);
    for(qint32 i = 0 ; i < 6; i++)
    {
        dbGab = mControl->getCurIndexBW(i);
        strGab = mControl->getFreqAdjustStr(dbGab);
        ui->value_RBW->setItemText(i,strGab);
    }
    intGab = mControl->getBWIndex();
    ui->value_RBW->setCurrentIndex(intGab);

    return;
}
/**
* @brief on_RBW_Auto_clicked
* @param set rbw status
* @Author Albert
* @date 2019-04-18
*/
void RtSa_Dialog_AllSetup::on_RBW_Auto_clicked()
{
    mControl->setBWAuto(true);
    qint32 intGab = mControl->getBWIndex();
    ui->value_RBW->setCurrentIndex(intGab);
    ui->RBW_Auto->setChecked(true);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-04-18
*/
void RtSa_Dialog_AllSetup::on_RBW_Manual_clicked()
{
    mControl->setBWAuto(false);
    refreshBW();
    return;
}
/**
* @brief on_value_Trace_currentIndexChanged
* @param select trace id
* @Author Albert
* @date 2019-04-18
*/
void RtSa_Dialog_AllSetup::on_value_Trace_currentIndexChanged(int index)
{
    mControl->setCurTrace(index);
    refreshTrace();
    return;
}
/**
* @brief on_btn_Average_toggled
* @param set average on/off
* @Author Albert
* @date 2019-04-18
*/
//void RtSa_Dialog_AllSetup::on_btn_Average_toggled(bool checked)
//{
//    qint32 intGab = mControl->getCurTrace();
//    if(checked)
//    {
//        ui->btn_Average->setText("On");
//    }
//    else
//    {
//        ui->btn_Average->setText("Off");
//    }
//    mControl->setAvgOn(intGab,checked);
//    return;
//}
/**
* @brief on_btn_TraceView_toggled
* @param set trace type
* @Author Albert
* @date 2019-04-18
*/
void RtSa_Dialog_AllSetup::on_btn_TraceView_toggled(bool checked)
{
    qint32 intGab = mControl->getCurTrace();
    qint32 traceType = mControl->IsTraceOn(intGab);

    if(checked)
    {
        ui->btn_TraceView->setText("On");
        if(traceType == RTSA_OFF)
        {
           mControl->setTraceOn(intGab,RTSA_ON);
        }
    }
    else
    {
        ui->btn_TraceView->setText("Off");
        if(traceType == RTSA_ON)
        {
           mControl->setTraceOn(intGab,RTSA_OFF);
        }
    }
    return;
}
/**
* @brief  on_value_MarkerSelect_currentIndexChanged
* @param select marker ID
* @Author Albert
* @date 2019-04-18
*/
void RtSa_Dialog_AllSetup::on_value_MarkerSelect_currentIndexChanged(int index)
{
    mControl->setCurMarkerID(index);
    refreshMarker();
    return;
}
/**
* @brief on_btn_MarkerView_toggled
* @param set marker on/off
* @Author Albert
* @date 2019-04-18
*/
void RtSa_Dialog_AllSetup::on_btn_MarkerView_toggled(bool checked)
{
    qint32 curMarkerID = mControl->getCurMarkerID();
    if(checked)
    {
        ui->btn_MarkerView->setText("On");
    }
    else
    {
        ui->btn_MarkerView->setText("Off");
    }
    mControl->setMarkerOn(curMarkerID,checked);
    refreshMarker();
    return;
}
/**
* @brief on_btn_MarkerView_2_toggled
* @param set all marker on/off
* @Author Albert
* @date 2019-04-18
*/
void RtSa_Dialog_AllSetup::on_btn_MarkerView_2_toggled(bool checked)
{
    if(checked)
    {
        ui->btn_MarkerView_2->setText("All On");
        for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
        {
            mControl->setMarkerOn(i,true);
        }
    }
    else
    {
        ui->btn_MarkerView_2->setText("All Off");
        for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
        {
            mControl->setMarkerOn(i,false);
        }
    }
    refreshMarker();
    return;
}
/**
* @brief  on_btn_NoiseMarker_toggled
* @param checked set marker noise on/off
* @Author Albert
* @date 2019-04-18
*/
void RtSa_Dialog_AllSetup::on_btn_NoiseMarker_toggled(bool checked)
{
    qint32 curMarkerID = mControl->getCurMarkerID();
    if(checked)
    {
        ui->btn_NoiseMarker->setText("On");
        mControl->setMarkerOn(curMarkerID,true);
    }
    else
    {
        ui->btn_NoiseMarker->setText("Off");
    }
    mControl->setMarkerNoiseOn(curMarkerID,checked);
    refreshMarker();
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-07-31
*/
void RtSa_Dialog_AllSetup::on_value_TraceType_currentIndexChanged(int index)
{
    qint32 nCurTrace = mControl->getCurTrace();
    qint32 nAvgCnt = 0;
    if(mControl->getTraceType(nCurTrace) == RTSA_TRACE_OFF)
        return;
//    mControl->setCurTrace(mCurSelTraceIndex);
    mControl->setTraceType(nCurTrace,index /*+ 1*/);
    if(index >= (RTSA_AVERAGE - 1))
    {
        nAvgCnt = mControl->getAvgNum(nCurTrace);
        ui->value_Average->setText(QString::number(nAvgCnt));
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-07-31
*/
void RtSa_Dialog_AllSetup::on_value_Trigger_currentIndexChanged(int index)
{
    mControl->setTrigger(index + 1);
    return;
}
