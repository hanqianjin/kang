#include "pm_dialog_allsetup.h"
#include "ui_pm_dialog_allsetup.h"

Pm_Dialog_AllSetup::Pm_Dialog_AllSetup(BitPm_Interface *BitPmInterface, Pm_Dialog_Digitinput *input, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pm_Dialog_AllSetup),
    PmInterfaceObj(BitPmInterface),
    mInputDialog(input),
    mChStdDialog(NULL),
    mLastWidgetID(PM_INPUT_FREQ_CENTER),
    mLastCombID(PM_ALLSET_INPUT_UNIT)
{

//    setAttribute(Qt::WA_DeleteOnClose);
    this->setAttribute(Qt::WA_NoChildEventsForParent,true);

    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint| Qt::Dialog /*| Qt::Dialog*/);
//    setAttribute(Qt::WA_StyledBackground,true);
//    setAttribute(Qt::WA_OpaquePaintEvent,true);
    ui->setupUi(this);
//    this->setAttribute(Qt::WA_DeleteOnClose);
    initMap();
    initDisplay();
    connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(refreshEditDisplay(qint32)));
    //    connect(mInputDialog,SIGNAL(ClockWiseDown(QKeyEvent*)),this,SLOT(DigitalKeyRespond(QKeyEvent*)));
    this->hide();
    ui->Freq_Center->setFocus();
    this->setProperty("status",pm_qssMode[PmInterfaceObj->getSystemDisplay()]);
    this->setStyle(QApplication::style());
}

Pm_Dialog_AllSetup::~Pm_Dialog_AllSetup()
{
    delete ui;
}

void Pm_Dialog_AllSetup::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
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

void Pm_Dialog_AllSetup::on_finishEntry(qint32 index)
{
    disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
    mInputDialog = NULL;

   if(mWidgetList.contains(index))
        refreshEditDisplay(index);
    return ;
}

void Pm_Dialog_AllSetup::on_pb_cancel_clicked()
{
    if(mInputDialog)
    {
        mInputDialog->close();
    }
    this->close();
    return;
}

void Pm_Dialog_AllSetup::on_clicked()
{
    if(mInputDialog)
    {
        mInputDialog->close();
    }
    qint32 index;
    Pm_ClickedWidget* widget = qobject_cast<Pm_ClickedWidget*>(sender());
    index = mWidgetList.key(widget,-1);
    if(index == -1)
    {
        return ;
    }
    mCombList.value(mLastCombID)->setStyleSheet("border:0px flat rgba(162,115,0,1);");
    mWidgetList.value(mLastWidgetID)->setStyleSheet("#widget>QWidget{border:0px flat rgba(162,115,0,1);}");
    mWidgetList.value(index)->setStyleSheet("#widget>QWidget{border:2px solid rgba(162,115,0,1);}");
    if(index >= PM_ALLSET_INPUT_SPAN_TYPE && index <= PM_ALLSET_INPUT_DISPLAY_REVERSE)
    {
        mLastWidgetID = index;
        return;
    }
    switch (index)
    {
    case PM_INPUT_FREQ_CHANNEL_STANDARD:
        showCHStdDialog();
        mLastWidgetID = index;
        return;
//    case PM_INPUT_FREQ_CHANNEL_NUM:
//        mLastWidgetID = index;
//        break;
    default:
        showInputDialog(index);
        mLastWidgetID = index;
        break;
    }
    return;
}

void Pm_Dialog_AllSetup::on_Combclicked()
{
    if(mInputDialog)
    {
        mInputDialog->close();
    }
    qint32 index;
    Pm_CombBox* widget = qobject_cast<Pm_CombBox*>(sender());
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
* @brief on_CHStdClose
* @param
* @Author	ROC
* @date	2019.12.4
*/
void Pm_Dialog_AllSetup::on_CHStdClose()
{
    if(!mChStdDialog)
        return;
    disconnect(mChStdDialog,SIGNAL(destroyed()),this,SLOT(on_CHStdClose()));
    mChStdDialog = NULL;
    this->setFocus();
    refreshEditDisplay(PM_INPUT_FREQ_CENTER);
    return;
}

/**
* @brief    on_value_Span_Type_currentIndexChanged
* @param
* @Author	ROC
* @date     2019.12.4
*/
void Pm_Dialog_AllSetup::on_value_Span_Type_currentIndexChanged(int index)
{
    PmInterfaceObj->setSpanType(index);
    refreshFreq();
    return;
}

void Pm_Dialog_AllSetup::on_Channel_UpLink_clicked()
{
    PmInterfaceObj->setCommuDirection(PM_UPLINK);
    refreshFreq();
    return;
}

void Pm_Dialog_AllSetup::on_Channel_DownLink_clicked()
{

    PmInterfaceObj->setCommuDirection(PM_DOWNLINK);
    refreshFreq();
}

/**
* @brief    on_btn_Freq_Offset_toggled
* @param
* @Author	ROC
* @date     2019.12.4
*/
void Pm_Dialog_AllSetup::on_btn_Freq_Offset_toggled(bool checked)
{
    PmInterfaceObj->setOffset(checked);
    refreshFreq();
    return;
}

/**
* @brief    on_Auto_Scale_clicked
* @param
* @Author	ROC
* @date     2019.12.4
*/
void Pm_Dialog_AllSetup::on_Auto_Scale_clicked()
{
    PmInterfaceObj->setAutoScale();
    refreshAmpt();
    return;
}

/**
* @brief    on_btn_Ampt_Forward_toggled
* @param
* @Author	ROC
* @date     2019.12.4
*/
void Pm_Dialog_AllSetup::on_btn_Ampt_Forward_clicked(bool checked)
{
    PmInterfaceObj->setAmptForwardRelative(checked);
    if(checked)
        PmInterfaceObj->setForwardDisplay(PmInterfaceObj->getForwardDisplay());
    refreshAmpt();
    return;
}

void Pm_Dialog_AllSetup::on_Ampt_Set_Forward_clicked()
{
    PmInterfaceObj->setForwardRelativeCurFlg(true);
}

/**
* @brief    on_btn_Ampt_Reverse_clicked
* @param
* @Author	ROC
* @date     2019.12.4
*/
void Pm_Dialog_AllSetup::on_btn_Ampt_Reverse_clicked(bool checked)
{
    PmInterfaceObj->setAmptReverseRelative(checked);
    if(checked)
        PmInterfaceObj->setReverseDisplay(PmInterfaceObj->getReverseDisplay());
    refreshAmpt();
    return;

}

void Pm_Dialog_AllSetup::on_Ampt_Set_Reverse_clicked()
{

    PmInterfaceObj->setReverseRelativeCurFlg(true);
}


/**
* @brief    on_value_Unit_currentIndexChanged
* @param    change unit
* @Author	ROC
* @date     2019.12.4
*/
void Pm_Dialog_AllSetup::on_value_Unit_currentIndexChanged(int index)
{
    PmInterfaceObj->setAmptUnit(index);
    refreshAmpt();
    return;
}

/**
* @brief    on_Sweep_Conti_clicked
* @param    set sweep continue
* @Author   ROC
* @date     2019.11.19
*/
void Pm_Dialog_AllSetup::on_Sweep_Conti_clicked()
{
    PmInterfaceObj->setSweepContinous(PM_CONT);
    return;
}

/**
* @brief on_Sweep_Single_clicked
* @param set sweep single
* @Author   ROC
* @date	2019.11.19
*/
void Pm_Dialog_AllSetup::on_Sweep_Single_clicked()
{
    PmInterfaceObj->setSweepContinous(PM_SINGLE);
    return;
}

/**
* @brief    on_value_Avg_Acq_currentIndexChanged
* @param
* @Author   ROC
* @date     2019.11.19
*/
void Pm_Dialog_AllSetup::on_value_Avg_Acq_currentIndexChanged(int index)
{
    PmInterfaceObj->setAverageAcq(index);
    refreshAvg();
    return;
}

void Pm_Dialog_AllSetup::on_btn_Average_Running_toggled(bool checked)
{

    PmInterfaceObj->setRunningAverage(checked);
    refreshAvg();
}

/**
* @brief    on_btn_Max_Hold_toggled
* @param
* @Author   ROC
* @date     2019.11.19
*/
void Pm_Dialog_AllSetup::on_btn_Max_Hold_toggled(bool checked)
{
    PmInterfaceObj->setMaxHold(checked);
    refreshAvg();
    return;
}

void Pm_Dialog_AllSetup::on_Zero_clicked()
{
    PmInterfaceObj->setZero(true);
}


/**
* @brief    on_btn_Limit_Show_toggled
* @param
* @Author   ROC
* @date     2019.11.19
*/
void Pm_Dialog_AllSetup::on_btn_Limit_Show_toggled(bool checked)
{

    PmInterfaceObj->setLimit(checked);
    refreshLimit();
    return;
}

/**
* @brief    on_value_Vido_BW_currentIndexChanged
* @param
* @Author   ROC
* @date     2019.11.19
*/
void Pm_Dialog_AllSetup::on_value_Vido_BW_currentIndexChanged(int index)
{
    PmInterfaceObj->setLimtVidoBW(index);
    refreshLimit();
    return;
}

/**
* @brief    on_value_Display_Forward_activated
* @param
* @Author   ROC
* @date     2019.11.19
*/
void Pm_Dialog_AllSetup::on_value_Display_Forward_activated(int index)
{
    PmInterfaceObj->setForwardDisplay(index);
    refreshDisplay();
    return;
}

/**
* @brief    on_value_Display_Reverse_activated
* @param
* @Author   ROC
* @date     2019.11.19
*/
void Pm_Dialog_AllSetup::on_value_Display_Reverse_activated(int index)
{
    PmInterfaceObj->setReverseDisplay(index);
    refreshDisplay();
    return;
}

/**
* @brief    on_Display_Summay_clicked
* @param
* @Author   ROC
* @date     2019.11.19
*/
void Pm_Dialog_AllSetup::on_Display_Summay_clicked()
{
    PmInterfaceObj->setSummaryDisplay();
    refreshDisplay();
    return;
}

void Pm_Dialog_AllSetup::refreshBtnInfo()
{
    return;
}

void Pm_Dialog_AllSetup::digitInputClose()
{
    return;
}

/**
* @brief showCHStdDialog
* @param
* @Author	ROC
* @date	2019.12.4
*/
void Pm_Dialog_AllSetup::showCHStdDialog()
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
    mChStdDialog = new Pm_Dialog_Ch_Std(PmInterfaceObj,this);
    mChStdDialog->setGeometry(0,0,this->width(),this->height());
    mChStdDialog->setFocus();
    connect(mChStdDialog,SIGNAL(destroyed()),this,SLOT(on_CHStdClose()));
    mChStdDialog->show();
    return;
}

/**
* @brief refreshFreq
* @param
* @Author	ROC
* @date	2019.12.5
*/
void Pm_Dialog_AllSetup::refreshFreq()
{
    QString strGab;
    bool blGab;
    strGab = PmInterfaceObj->getFreqStr(PM_BIT_CENTER_FREQ);
    ui->value_CenterFreq->setText(strGab);
    strGab = PmInterfaceObj->getFreqStr(PM_BIT_START_FREQ);
    ui->value_StartFreq->setText(strGab);
    strGab = PmInterfaceObj->getFreqStr(PM_BIT_STOP_FREQ);
    ui->value_StopFreq->setText(strGab);
    strGab = PmInterfaceObj->getFreqStr(PM_BIT_SPAN_FREQ);
    ui->value_Span->setText(strGab);
    strGab = PmInterfaceObj->getFreqStr(PM_BIT_STEP_FREQ);
    ui->value_FreqStep->setText(strGab);
    if(PmInterfaceObj->getGlobalUserVariable()->gMeterParam.gConfig_Freq.nChannelStd < 0 || !PmInterfaceObj->getGlobalUserVariable()->IsFreqInCurChStd())
      {
          strGab = "None";
          ui->value_Channel->setText(strGab);
          ui->value_ChannelNum->setText(strGab);
      }
      else
      {
          strGab = QString(mPM_ChStand[PmInterfaceObj->getGlobalUserVariable()->gMeterParam.gConfig_Freq.nChannelStd].name);
          ui->value_Channel->setText(strGab);
          strGab = QString::number(PmInterfaceObj->getChannelNumber());
          ui->value_ChannelNum->setText(strGab);
    }
    blGab = PmInterfaceObj->IsOffset();

    ui->btn_Freq_Offset->setChecked(blGab);
    if(blGab)
    {
        ui->btn_Freq_Offset->setText("On");
    }
    else
    {
        ui->btn_Freq_Offset->setText("Off");
    }
    qlonglong nllValue = PmInterfaceObj->getFreqOffset();
    if(0 < nllValue)
    strGab = PmInterfaceObj->getFreqAdjustStr(nllValue);
    else
    {
        strGab = "0 Hz";
    }
    ui->value_Freq_Offset->setText(strGab);
    return;
}

/**
* @brief refreshAmpt
* @param
* @Author	ROC
* @date	2019.12.4
*/
void Pm_Dialog_AllSetup::refreshAmpt()
{
    QString strGab;
    qreal valGab;
    bool blGab;

    if(POWER_SENSOR_V90 == PmInterfaceObj->getPowerSensorFlg())
    {
        ui->Title_Ampt_Forward->setText("Relative");
        ui->Title_Forward_Lev->setText("Relative Level");
        ui->Title_Set_Forward->setText("Set To Relative");
        ui->Ampt_Reverse->hide();
        ui->Ampt_Reverse_Lev->hide();
        ui->Ampt_Set_Reverse->hide();
//        ui->lableEnterOffset->setText("Enter Offset");
    }
    else  if(POWER_SENSOR_V91 == PmInterfaceObj->getPowerSensorFlg())
    {
        ui->Title_Ampt_Forward->setText("Forward Relative");
        ui->Title_Forward_Lev->setText("Forward Level");
        ui->Title_Set_Forward->setText("Set To Forward");

        ui->Ampt_Reverse->show();
        ui->Ampt_Reverse_Lev->show();
        ui->Ampt_Set_Reverse->show();
    }

    valGab = PmInterfaceObj->getAmptMax();
    strGab = QString::number(valGab) +  QString(" dBm");
    ui->value_Ampt_Max->setText(strGab);

    valGab = PmInterfaceObj->getAmptMin();
    strGab = QString::number(valGab) +  QString(" dBm");
    ui->value_Ampt_Min->setText(strGab);

    blGab = PmInterfaceObj->IsAmptForwardRelative();
    ui->btn_Ampt_Forward->setChecked(blGab);
    if(blGab)
    {
        ui->btn_Ampt_Forward->setText("On");
    }
    else
    {
        ui->btn_Ampt_Forward->setText("Off");
    }

    valGab = PmInterfaceObj->getAmptForwardRelativeData();
    strGab = QString::number(valGab,'f',2) + QString(" dB");
    ui->value_Forward_Lev->setText(strGab);

    blGab = PmInterfaceObj->IsAmptReverseRelative();
    ui->btn_Ampt_Reverse->setChecked(blGab);
    if(blGab)
    {
        ui->btn_Ampt_Reverse->setText("On");
    }
    else
    {
        ui->btn_Ampt_Reverse->setText("Off");
    }

    valGab = PmInterfaceObj->getAmptReverseRelativeData();
    strGab = QString::number(valGab,'f',2) + QString(" dB");
    ui->value_Reverse_Lev->setText(strGab);

    valGab = PmInterfaceObj->getAmptOffset();
    strGab = QString::number(valGab,'f',2) + QString(" dB");
    ui->value_Ampt_Offset->setText(strGab);
    return;
}

void Pm_Dialog_AllSetup::refreshUnit()
{
    return;
}

/**
* @brief refreshSweep
* @param
* @Author	ROC
* @date	2019.12.4
*/
void Pm_Dialog_AllSetup::refreshSweep()
{
    bool blGab;
    qreal dbGab;
    QString strGab;
    qint32 intGab;

    blGab = PmInterfaceObj->IsSweepContinous();
    ui->Sweep_Conti->setChecked(blGab);
    if(blGab)
    {
        ui->Sweep_Conti->setChecked(true);
    }
    else
    {
        ui->Sweep_Single->setChecked(true);
    }

    intGab = PmInterfaceObj->getSweepTime();
    strGab = QString::number(intGab) +  QString(" s");
    ui->value_Time->setText(strGab);

    dbGab = PmInterfaceObj->getDutyCycle();
    strGab = QString::number(dbGab,'f',2)+  QString(" %");
    ui->value_Duty->setText(strGab);
    dbGab = PmInterfaceObj->getMeasureOffset();
    strGab = QString::number(dbGab,'f',2) +  QString(" dB");
    ui->value_Measure_Offset->setText(strGab);
    return;
}

/**
* @brief refreshAvg
* @param
* @Author	ROC
* @date	2019.12.4
*/
void Pm_Dialog_AllSetup::refreshAvg()
{
    QString strGab;
    qint32 intGab;
    bool blGab;

    intGab = PmInterfaceObj->getAveragePoint();
    strGab = QString::number(intGab);
    ui->value_Point->setText(strGab);
    blGab = PmInterfaceObj->IsRunningAverage();
    ui->btn_Average_Running->setChecked(blGab);
    if(blGab)
    {
        ui->btn_Average_Running->setText("On");
    }
    else
    {
        ui->btn_Average_Running->setText("Off");
    }
    ui->btn_Average_Running->setChecked(blGab);

    blGab = PmInterfaceObj->IsMaxHold();
    ui->btn_Max_Hold->setChecked(blGab);
    if(blGab)
    {
        ui->btn_Max_Hold->setText("On");
    }
    else
    {
        ui->btn_Max_Hold->setText("Off");
    }
    ui->btn_Max_Hold->setChecked(blGab);

    return;
}

/**
* @brief refreshZero
* @param
* @Author	ROC
* @date	2019.12.4
*/
void Pm_Dialog_AllSetup::refreshZero()
{
    return;
}

/**
* @brief refreshLimit
* @param
* @Author	ROC
* @date	2019.12.4
*/
void Pm_Dialog_AllSetup::refreshLimit()
{
    QString strGab;
    qint32 intGab;
    qreal dbGab;
    bool blGab;
    if(POWER_SENSOR_V90 == PmInterfaceObj->getPowerSensorFlg())
    {
        ui->Title_Forward_Upper->setText("Upper Limit");
        ui->Title_Forward_Lower->setText("Lower Limit");

        ui->Limit_Resverse_Upper->hide();
        ui->Limit_Resverse_Lower->hide();

        ui->Limit_Vido_BW->hide();

    }
    else  if(POWER_SENSOR_V91 == PmInterfaceObj->getPowerSensorFlg())
    {
        ui->Title_Forward_Upper->setText("Forward Upper Limit");
        ui->Title_Forward_Lower->setText("Forward Lower Limit");

        ui->Limit_Resverse_Upper->show();
        ui->Limit_Resverse_Lower->show();
        ui->Limit_Vido_BW->show();
    }

    blGab = PmInterfaceObj->IsLimit();
    ui->btn_Limit_Show->setChecked(blGab);
    if(blGab)
    {
        ui->btn_Limit_Show->setText("On");
    }
    else
    {
        ui->btn_Limit_Show->setText("Off");
    }
    ui->btn_Limit_Show->setChecked(blGab);

    dbGab = PmInterfaceObj->getForwardUpperLimt();
    strGab = QString::number(dbGab,'f',2) + QString(" dB");
    ui->value_Forward_Upper->setText(strGab);

    dbGab = PmInterfaceObj->getForwardLowerLimt();
    strGab = QString::number(dbGab,'f',2) + QString(" dB");
    ui->value_Forward_Lower->setText(strGab);

    dbGab = PmInterfaceObj->getReverseUpperLimt();
    strGab = QString::number(dbGab,'f',2) + QString(" dB");
    ui->value_Resverse_Upper->setText(strGab);

    dbGab = PmInterfaceObj->getReverseLowerLimt();
    strGab = QString::number(dbGab,'f',2) + QString(" dB");
    ui->value_Resverse_Lower->setText(strGab);

    return;
}

/**
* @brief refreshDisplay
* @param
* @Author	ROC
* @date	2019.12.4
*/
void Pm_Dialog_AllSetup::refreshDisplay()
{
    if(POWER_SENSOR_V90 == PmInterfaceObj->getPowerSensorFlg())
    {
        ui->Display_Forward->hide();
        ui->Display_Reverse->hide();
        ui->Display_Summay->hide();
    }
    else  if(POWER_SENSOR_V91 == PmInterfaceObj->getPowerSensorFlg())
    {
        ui->Display_Forward->show();
        ui->Display_Reverse->show();
        ui->Display_Summay->show();
    }

    if(PM_DISPLAY_SUMMARY == PmInterfaceObj->getDisplayMode())
    {
        ui->value_Display_Forward->setCurrentIndex(-1);
        ui->value_Display_Reverse->setCurrentIndex(-1);
    }
    else
    {
        ui->value_Display_Forward->setCurrentIndex(PmInterfaceObj->getForwardDisplay());
        ui->value_Display_Reverse->setCurrentIndex(PmInterfaceObj->getReverseDisplay());
    }
//    ui->pb_sensorType->setCurrentIndex(PmInterfaceObj->getPowerSensorFlg());

    return;
}

/**
* @brief initDisplay
* @param
* @Author	ROC
* @date	2019.12.4
*/
void Pm_Dialog_AllSetup::initDisplay()
{
    refreshFreq();
    refreshAmpt();
    refreshSweep();
    refreshAvg();
    refreshZero();
    refreshLimit();
    refreshDisplay();
    return;
}

/**
* @brief initMap
* @param none
* @Author	ROC
* @date	2019.11.27
*/
void Pm_Dialog_AllSetup::initMap()
{
    //freq
    mWidgetList.insert(PM_INPUT_FREQ_CENTER,ui->Freq_Center);
    connect(ui->Freq_Center,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(PM_INPUT_FREQ_START,ui->Freq_Start);
    connect(ui->Freq_Start,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(PM_INPUT_FREQ_STOP,ui->Freq_Stop);
    connect(ui->Freq_Stop,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(PM_INPUT_FREQ_STEP,ui->Freq_Step);
    connect(ui->Freq_Step,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(PM_INPUT_FREQ_SPAN,ui->Span);
    connect(ui->Span,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(PM_INPUT_FREQ_CHANNEL_STANDARD,ui->Channel_STD);
    connect(ui->Channel_STD,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(PM_INPUT_FREQ_CHANNEL_NUM,ui->Channel_Num);
    connect(ui->Channel_Num,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(PM_INPUT_FREQ_OFFSET,ui->Freq_Offset);
    connect(ui->Freq_Offset,SIGNAL(clicked()),this,SLOT(on_clicked()));
//    mWidgetList.insert(PM_INPUT_FREQ_OFFSET_SIZE,ui->Freq_Offset_Size);
//    connect(ui->Freq_Offset_Size,SIGNAL(clicked()),this,SLOT(on_clicked()));

    //Ampt
    mWidgetList.insert(PM_INPUT_AMP_MAX,ui->Ampt_Max);
    connect(ui->Ampt_Max,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(PM_INPUT_AMP_MIN,ui->Ampt_Min);
    connect(ui->Ampt_Min,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(PM_INPUT_FORWATD_RELATIVE,ui->Ampt_Forward_Lev);
    connect(ui->Ampt_Forward_Lev,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(PM_INPUT_REVERSE_RELATIVE,ui->Ampt_Reverse_Lev);
    connect(ui->Ampt_Reverse_Lev,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(PM_INPUT_AMP_OFFSET,ui->Ampt_Offset);
    connect(ui->Ampt_Offset,SIGNAL(clicked()),this,SLOT(on_clicked()));
    //Sweep
    mWidgetList.insert(PM_INPUT_TIME_INTERVAL,ui->Sweep_Time);
    connect(ui->Sweep_Time,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(PM_INPUT_DUTY_CYCLE,ui->Limit_Duty);
    connect(ui->Limit_Duty,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(PM_INPUT_MEASURE_OFFSET,ui->Sweep_Measure_Offset);
    connect(ui->Sweep_Measure_Offset,SIGNAL(clicked()),this,SLOT(on_clicked()));

    //avg
    mWidgetList.insert(PM_INPUT_RUNNING_AVERAGE,ui->AVG_Point);
    connect(ui->AVG_Point,SIGNAL(clicked()),this,SLOT(on_clicked()));
//    //Zero
//    mWidgetList.insert(PM_INPUT_CAL_CENTER_FREQ,ui->Zero_Cal);
//    connect(ui->Zero_Cal,SIGNAL(clicked()),this,SLOT(on_clicked()));

    //Limit
    mWidgetList.insert(PM_INPUT_FORWARD_UPPER,ui->Limit_Forward_Upper);
    connect(ui->Limit_Forward_Upper,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(PM_INPUT_FORWARD_LOWER,ui->Limit_Forward_Lower);
    connect(ui->Limit_Forward_Lower,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(PM_INPUT_REVERSE_UPPER,ui->Limit_Resverse_Upper);
    connect(ui->Limit_Resverse_Upper,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(PM_INPUT_REVERSE_LOWER,ui->Limit_Resverse_Lower);
    connect(ui->Limit_Resverse_Lower,SIGNAL(clicked()),this,SLOT(on_clicked()));

    mWidgetList.insert(PM_ALLSET_INPUT_UNIT,ui->Scale_Unit);
    connect(ui->Scale_Unit,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(PM_ALLSET_INPUT_SPAN_TYPE,ui->Span_Type);
    connect(ui->Span_Type,SIGNAL(clicked()),this,SLOT(on_clicked()));
     mWidgetList.insert(PM_ALLSET_INPUT_AVG_ACQ,ui->Average_Acq);
    connect(ui->Average_Acq,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(PM_ALLSET_INPUT_LIMIT_BW,ui->Limit_Vido_BW);
    connect(ui->Limit_Vido_BW,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(PM_ALLSET_INPUT_DISPLAY_FORWARD,ui->Display_Forward);
    connect(ui->Display_Forward,SIGNAL(clicked()),this,SLOT(on_clicked()));
    mWidgetList.insert(PM_ALLSET_INPUT_DISPLAY_REVERSE,ui->Display_Reverse);
    connect(ui->Display_Reverse,SIGNAL(clicked()),this,SLOT(on_clicked()));

    mCombList.insert(PM_ALLSET_INPUT_UNIT,ui->value_Unit);
    connect(ui->value_Unit,SIGNAL(clicked(Pm_CombBox*)),this,SLOT(on_Combclicked()));
    mCombList.insert(PM_ALLSET_INPUT_SPAN_TYPE,ui->value_Span_Type);
    connect(ui->value_Span_Type,SIGNAL(clicked(Pm_CombBox*)),this,SLOT(on_Combclicked()));
       mCombList.insert(PM_ALLSET_INPUT_AVG_ACQ,ui->value_Avg_Acq);
    connect(ui->value_Avg_Acq,SIGNAL(clicked(Pm_CombBox*)),this,SLOT(on_Combclicked()));
    mCombList.insert(PM_ALLSET_INPUT_LIMIT_BW,ui->value_Vido_BW);
    connect(ui->value_Vido_BW,SIGNAL(clicked(Pm_CombBox*)),this,SLOT(on_Combclicked()));
    mCombList.insert(PM_ALLSET_INPUT_DISPLAY_FORWARD,ui->value_Display_Forward);
    connect(ui->value_Display_Forward,SIGNAL(clicked(Pm_CombBox*)),this,SLOT(on_Combclicked()));
    mCombList.insert(PM_ALLSET_INPUT_DISPLAY_REVERSE,ui->value_Display_Reverse);
    connect(ui->value_Display_Reverse,SIGNAL(clicked(Pm_CombBox*)),this,SLOT(on_Combclicked()));

    ui->value_Unit->setPopupPotion(PM_TOP,-ui->value_Unit->x(),-ui->value_Unit->y()- 2);
    ui->value_Span_Type->setPopupPotion(PM_TOP,-ui->value_Span_Type->x(),2);
    ui->value_Avg_Acq->setPopupPotion(PM_BOTTOM,-ui->value_Span_Type->x(),2);
    ui->value_Vido_BW->setPopupPotion(PM_TOP,-ui->value_Span_Type->x(),2);
    ui->value_Display_Forward->setPopupPotion(PM_BOTTOM,-ui->value_Display_Forward->x(),2);
    ui->value_Display_Reverse->setPopupPotion(PM_BOTTOM,-ui->value_Display_Reverse->x(),2);
    return;
}

void Pm_Dialog_AllSetup::showInputDialog(qint32 index)
{
    if(mInputDialog)
    {
    }
    else
    {
//        mInputDialog = new Pm_Dialog_Digitinput(this);
//        mInputDialog->setInterface(PmInterfaceObj);
//        mInputDialog->setUserVariable(mUserVariable);
//        mInputDialog->setFocusPolicy(Qt::NoFocus);
//        mInputDialog->move(0,0);
//        connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
    }
    qint32 xPos = mapToGlobal(QPoint(0,0)).x() + mWidgetList.value(index)->x() + mWidgetList.value(index)->width();
    qint32 yPos = mapToGlobal(QPoint(0,0)).y() + 45;
    if(PM_INPUT_FORWARD_UPPER == index
            || PM_INPUT_FORWARD_LOWER == index
            || PM_INPUT_REVERSE_UPPER == index
            || PM_INPUT_REVERSE_LOWER == index
            || PM_INPUT_CCDF == index)
    {
        xPos = mapToGlobal(QPoint(0,0)).x() + mWidgetList.value(index)->x() - mInputDialog->width();
        yPos = mapToGlobal(QPoint(0,0)).y() + 45;
    }

    mInputDialog->setWindowFlags(mInputDialog->windowFlags() | Qt::WindowStaysOnTopHint);
    mInputDialog->move(xPos,yPos);
    mInputDialog->initDisplay(index);
    mInputDialog->setProperty("status", pm_qssMode[PmInterfaceObj->getSystemDisplay()]);
    mInputDialog->setStyle(QApplication::style());
    mInputDialog->show();

    return;
}

void Pm_Dialog_AllSetup::refreshEditDisplay(qint32 index)
{
    qreal freq;
    QString strGab;
    switch (index) {
    case PM_INPUT_FREQ_CENTER:
    case PM_INPUT_FREQ_START:
    case PM_INPUT_FREQ_STOP:
    case PM_INPUT_FREQ_SPAN:
    case PM_INPUT_FREQ_OFFSET:
//    case PM_INPUT_FREQ_OFFSET_SIZE:
        refreshFreq();
        break;
    case PM_INPUT_FREQ_STEP:
        strGab = PmInterfaceObj->getFreqStr(PM_BIT_STEP_FREQ);
        ui->value_StopFreq->setText(strGab);
        break;
    case PM_INPUT_AMP_MAX:
    case PM_INPUT_AMP_MIN:
    case PM_INPUT_AMP_OFFSET:
    case PM_INPUT_FORWATD_RELATIVE:
    case PM_INPUT_REVERSE_RELATIVE:
        refreshAmpt();
        break;
    case PM_INPUT_TIME_INTERVAL:
    case PM_INPUT_DUTY_CYCLE:
    case PM_INPUT_MEASURE_OFFSET:
        refreshSweep();
        break;
    case PM_INPUT_RUNNING_AVERAGE:
        refreshAvg();
        break;
    case PM_INPUT_CAL_CENTER_FREQ:
        refreshZero();
        break;
    case PM_INPUT_FORWARD_UPPER:
    case PM_INPUT_FORWARD_LOWER:
    case PM_INPUT_REVERSE_UPPER:
    case PM_INPUT_REVERSE_LOWER:
    case PM_INPUT_CCDF:
        refreshLimit();
        break;
        //    case :
//        refreshDisplay();
//        break;
    default:
        break;
    }
    return;
}

