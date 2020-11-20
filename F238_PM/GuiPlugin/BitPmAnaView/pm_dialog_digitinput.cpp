#include "pm_dialog_digitinput.h"
#include "pm_define.h"
#include <QKeyEvent>
#include "pm_user_variable.h"
#include "ui_pm_dialog_digitinput.h"
#include "pm_extern.h"
#include "QDebug"

Pm_Dialog_Digitinput::Pm_Dialog_Digitinput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pm_Dialog_Digitinput)
{
    ui->setupUi(this);
    this->setFocusPolicy(Qt::StrongFocus);

    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint | Qt::Dialog);
    mShiftKeyPressed = false;
    InitKeyboard();
    this->setFocus();
    for(int i = 0;i<BUTTON_MUM;i++)
        key_btn[i] = NULL;
}

Pm_Dialog_Digitinput::~Pm_Dialog_Digitinput()
{
    delete ui;
}



void Pm_Dialog_Digitinput::InitKeyboard()
{
    key_btn[VIRTUAL_KEY_1] = ui->pb_1;
    key_btn[VIRTUAL_KEY_2] = ui->pb_2;
    key_btn[VIRTUAL_KEY_3] = ui->pb_3;
    key_btn[VIRTUAL_KEY_4] = ui->pb_4;
    key_btn[VIRTUAL_KEY_5] = ui->pb_5;
    key_btn[VIRTUAL_KEY_6] = ui->pb_6;
    key_btn[VIRTUAL_KEY_7] = ui->pb_7;
    key_btn[VIRTUAL_KEY_8] = ui->pb_8;
    key_btn[VIRTUAL_KEY_9] = ui->pb_9;
    key_btn[VIRTUAL_KEY_0] = ui->pb_0;
    key_btn[VIRTUAL_KEY_ACROSS] = ui->pb_across;
    key_btn[VIRTUAL_KEY_BACKSPACE] = ui->btnBackSpace;
    key_btn[VIRTUAL_KEY_DOT] = ui->pb_dot;

    key_btn[VIRTUAL_KEY_CLEARALL] = ui->pb_clearAll;
    key_btn[VIRTUAL_KEY_UP] = ui->pb_Up;
    key_btn[VIRTUAL_KEY_DOWN] = ui->pb_Down;
    key_btn[VIRTUAL_KEY_LEFT] = ui->pb_Left;
    key_btn[VIRTUAL_KEY_RIGHT] = ui->pb_Right;


    mBtnkey.insert(ui->pb_1,Qt::Key_1);
    mBtnkey.insert(ui->pb_2,Qt::Key_2);
    mBtnkey.insert(ui->pb_3,Qt::Key_3);
    mBtnkey.insert(ui->pb_4,Qt::Key_4);
    mBtnkey.insert(ui->pb_5,Qt::Key_5);
    mBtnkey.insert(ui->pb_6,Qt::Key_6);
    mBtnkey.insert(ui->pb_7,Qt::Key_7);
    mBtnkey.insert(ui->pb_8,Qt::Key_8);
    mBtnkey.insert(ui->pb_9,Qt::Key_9);
    mBtnkey.insert(ui->pb_0,Qt::Key_0);
    mBtnkey.insert(ui->pb_across,Qt::Key_Minus);
    mBtnkey.insert(ui->btnBackSpace,Qt::Key_Escape);
    mBtnkey.insert(ui->pb_dot,Qt::Key_Period);

    mBtnkey.insert(ui->pb_clearAll,Qt::Key_Delete);
    mBtnkey.insert(ui->pb_Up,Qt::Key_Up);
    mBtnkey.insert(ui->pb_Down,Qt::Key_Down);
    mBtnkey.insert(ui->pb_Left,Qt::Key_Left);
    mBtnkey.insert(ui->pb_Right,Qt::Key_Right);
    for(int i = 0; i < 18; i++)
    {
        connect(key_btn[i],SIGNAL(clicked()),this,SLOT(btn_clicked()));
    }

    return;
}

/**
* @brief  Init dialog interface.
* @param  index
* @author Roc
* @since  2019.11.5
*/
void Pm_Dialog_Digitinput::setInterface(BitPm_Interface *BitPmInterface)
{
    PmInterfaceObj = BitPmInterface;
    return;
}

void Pm_Dialog_Digitinput::showFreqUnit(bool isOn)
{
    ui->AmptUnit->hide();
    ui->FreqUnit->show();
    if(isOn)
    {
        ui->freqBtnUnit1->show();
        ui->freqBtnUnit2->show();

        ui->freqBtnUnit3->show();
        ui->freqBtnUnit4->show();
    }
    else
    {
        ui->freqBtnUnit1->hide();
        ui->freqBtnUnit2->hide();
        ui->freqBtnUnit3->hide();
        ui->freqBtnUnit4->hide();
    }
    return;
}

void Pm_Dialog_Digitinput::showAmptUnit(bool isOn)
{
    ui->FreqUnit->hide();
    ui->AmptUnit->show();
    if(isOn)
    {
        ui->amptBtnUnit1->show();
        ui->amptBtnUnit2->show();
        ui->amptBtnUnit3->show();
        ui->amptBtnUnit4->show();
        ui->amptBtnUnit5->show();
        ui->amptBtnUnit6->show();
        ui->amptBtnUnit7->show();
    }
    else
    {
        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->hide();
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->hide();
    }
    return;
}
void Pm_Dialog_Digitinput::showAmptUnitIndex(qint32 index)
{
    return;
}

/**
* @brief  Init dialog display.
* @param  index
* @author Roc
* @since  2019.11.5
*/
void Pm_Dialog_Digitinput::initDisplay(qint32 index)
{
    this->setFocus();
    entryNo = index;
    QString strGab;
    QString strValue,strUnit;
    qreal   value = 0;
    qint32 intGab;
    char label[20];
    memset(newDataString, 0, sizeof(char) * 20);
    memset(oldDataString, 0, sizeof(char) * 20);

    blNumberInput = false;
    blDotInput = false;
    bLeftKey = false;
    bRightKey = false;
    blFirstIn = true;
    highLightIndex = -1;

    switch (index)
    {
    case PM_INPUT_FREQ_CENTER:
        showFreqUnit(true);
        value = PmInterfaceObj->getCenterFreq();
        strGab = PmInterfaceObj->getFreqAdjustStr(value);
        unitNo = PmInterfaceObj->freqUnitFindProc(value);
        ui->lblTitle->setText("Center Freq");
        ui->freqBtnUnit3->hide();
        ui->freqBtnUnit4->hide();
        break;
    case PM_INPUT_FREQ_START:
        showFreqUnit(true);
        value = PmInterfaceObj->getStartFreq();
        strGab = PmInterfaceObj->getFreqAdjustStr(value);
        unitNo = PmInterfaceObj->freqUnitFindProc(value);
        ui->lblTitle->setText("Start Freq");
        ui->freqBtnUnit3->hide();
        ui->freqBtnUnit4->hide();
        break;
    case PM_INPUT_FREQ_STOP:
        showFreqUnit(true);
        value = PmInterfaceObj->getStopFreq();
        strGab = PmInterfaceObj->getFreqAdjustStr(value);
        unitNo = PmInterfaceObj->freqUnitFindProc(value);
        ui->lblTitle->setText("Stop Freq");
        ui->freqBtnUnit3->hide();
        ui->freqBtnUnit4->hide();
        break;
    case PM_INPUT_FREQ_STEP:
        showFreqUnit(true);
        value = PmInterfaceObj->getStepFreq();
        strGab = PmInterfaceObj->getFreqAdjustStr(value);
        unitNo = PmInterfaceObj->freqUnitFindProc(value);
        ui->lblTitle->setText("Step Freq");
        ui->freqBtnUnit4->hide();
        break;
    case PM_INPUT_FREQ_SPAN:
        showFreqUnit(true);
        value = PmInterfaceObj->getSpan();
        strGab = PmInterfaceObj->getFreqAdjustStr(value);
        unitNo = PmInterfaceObj->freqUnitFindProc(value);
        ui->lblTitle->setText("Span Freq");
        ui->freqBtnUnit4->hide();
        break;
    case PM_INPUT_FREQ_CHANNEL_NUM:
        showAmptUnit(false);
        value = PmInterfaceObj->getGlobalUserVariable()->CalculateChannelNum();
        strGab = QString::number(value);
        strValue = QString("Channel Num ");
        strUnit =QString("(");
        if(PmInterfaceObj->getGlobalUserVariable()->gMeterParam.gConfig_Freq.nChannelType == PM_UPLINK)
        {
            value = PmInterfaceObj->getGlobalUserVariable()->gCHStandard->at(PmInterfaceObj->getGlobalUserVariable()->gMeterParam.gConfig_Freq.nChannelSelID).Up.Min;
            strUnit = strUnit + QString::number(value);
            strUnit = strUnit + QString("-");
            value = PmInterfaceObj->getGlobalUserVariable()->gCHStandard->at(PmInterfaceObj->getGlobalUserVariable()->gMeterParam.gConfig_Freq.nChannelSelID).Up.Max;
            strUnit = strUnit + QString::number(value);
        }
        else
        {
            value = PmInterfaceObj->getGlobalUserVariable()->gCHStandard->at(PmInterfaceObj->getGlobalUserVariable()->gMeterParam.gConfig_Freq.nChannelSelID).Down.Min;
            strUnit = strUnit + QString::number(value);
            strUnit = strUnit + QString("-");
            value = PmInterfaceObj->getGlobalUserVariable()->gCHStandard->at(PmInterfaceObj->getGlobalUserVariable()->gMeterParam.gConfig_Freq.nChannelSelID).Down.Max;
            strUnit = strUnit + QString::number(value);
        }
        strUnit = strUnit + QString(")");
        ui->lblTitle->setText(strValue +
                              QObject::tr("<font size = 18px>%1</font>").arg(strUnit));
        ui->amptBtnUnit4->show();
        ui->amptBtnUnit4->setText("Enter");
        strUnit = QString("");
        break;
    case PM_INPUT_FREQ_OFFSET:
        showFreqUnit(true);
        value = PmInterfaceObj->getFreqOffset();
        if(0 < value)
        strGab = PmInterfaceObj->getFreqAdjustStr(value);
        else
        {
            strGab = "0 Hz";
        }
        unitNo = PmInterfaceObj->freqUnitFindProc(value);
        ui->lblTitle->setText("Offset Freq");
        break;
//    case  PM_INPUT_FREQ_OFFSET_SIZE:
//        showFreqUnit(true);
//        value = PmInterfaceObj->getFreqOffsetSize();
//        strGab = PmInterfaceObj->getFreqAdjustStr(value);
//        unitNo = PmInterfaceObj->freqUnitFindProc(value);
//        ui->lblTitle->setText("Offset Freq Size");
//        break;
    case  PM_INPUT_AMP_MAX:
    case  PM_INPUT_AMP_MIN:
    case PM_INPUT_FORWARD_UPPER:
    case PM_INPUT_FORWARD_LOWER:
    case PM_INPUT_REVERSE_UPPER:
    case PM_INPUT_REVERSE_LOWER:
        showAmptUnit(false);
        if(PM_INPUT_AMP_MAX == index)
        {
            ui->lblTitle->setText("Amp Max ");
            value = PmInterfaceObj->getAmptMax();
        }
        else if(PM_INPUT_AMP_MIN == index)
        {
            ui->lblTitle->setText("Amp Min ");
            value = PmInterfaceObj->getAmptMin();
        }
        else if(PM_INPUT_FORWARD_UPPER == index)
        {
            value = PmInterfaceObj->getForwardUpperLimt();

            if(POWER_SENSOR_V90 == PmInterfaceObj->getPowerSensorFlg())
            {
                ui->lblTitle->setText("Limit Upper ");
            }
            else if(POWER_SENSOR_V91 == PmInterfaceObj->getPowerSensorFlg())
            {

                ui->lblTitle->setText("Forward Upper ");
            }

        }
        else if(PM_INPUT_FORWARD_LOWER == index)
        {
            value = PmInterfaceObj->getForwardLowerLimt();
            if(POWER_SENSOR_V90 == PmInterfaceObj->getPowerSensorFlg())
            {
                ui->lblTitle->setText("Limit Lower ");
            }
            else if(POWER_SENSOR_V91 == PmInterfaceObj->getPowerSensorFlg())
            {

            ui->lblTitle->setText("Forward Lower ");
            }
        }
        else if(PM_INPUT_REVERSE_UPPER == index)
        {
            value = PmInterfaceObj->getReverseUpperLimt();
            ui->lblTitle->setText("Reverse Upper");
        }
        else if(PM_INPUT_REVERSE_LOWER == index)
        {
            value = PmInterfaceObj->getReverseLowerLimt();
            ui->lblTitle->setText("Reverse Lower ");
        }
        else
        {
            value = 0;
            ui->lblTitle->setText("None Type Defie ");
        }

        unitNo = PmInterfaceObj->getAmptUint();
        switch (unitNo)
        {
        case PM_DBM:
        case PM_DBV:
        case PM_DBMV:
        case PM_DBUV:
            if (unitNo == PM_DBM)
            {
                strGab.sprintf("%.2f dBm",value);
                ui->amptBtnUnit4->show();
                ui->amptBtnUnit4->setText("dBm");
                //                getInitialAmplitudeVal(value,index,newDataString,unitNo);
            }
            else if  (unitNo == PM_DBV)
            {
                strGab.sprintf("%.2f dBV", value + PM_dBVFix);
                ui->amptBtnUnit4->show();
                ui->amptBtnUnit4->setText("dBV");
                //                getInitialAmplitudeVal(value + PM_dBVFix,index,newDataString,unitNo);
            }
            else if  (unitNo == PM_DBMV)
            {
                strGab.sprintf("%.2f dBmV", value + PM_dBmVFix);
                ui->amptBtnUnit4->show();
                ui->amptBtnUnit4->setText("dBmV");
                //                getInitialAmplitudeVal(value + PM_dBmVFix,index,newDataString,unitNo);
            } else if  (unitNo == PM_DBUV)
            {
                strGab.sprintf("%.2f dBuV", value + PM_dBuVFix);
                ui->amptBtnUnit4->show();
                ui->amptBtnUnit4->setText("dBuV");
                //                getInitialAmplitudeVal(value + PM_dBuVFix,index,newDataString,unitNo);
            }
            break;
        case PM_VOLT:
            ui->amptBtnUnit1->show();
            ui->amptBtnUnit2->show();
            ui->amptBtnUnit3->show();
            ui->amptBtnUnit1->setText("V");
            ui->amptBtnUnit2->setText("mV");
            ui->amptBtnUnit3->setText("uV");
            PmInterfaceObj->getGlobalUserVariable()->dbmToVoltCalculatorAndDisplayFunc(label, value);
            strGab = QString(label);
            //            getInitialAmplitudeVal(value,index,newDataString,unitNo);
            break;
        case PM_WATTS:
            showAmptUnit(true);
            PmInterfaceObj->getGlobalUserVariable()->dbmToWattsCalculatorAndDisplayFunc(label, value);
            strGab = QString(label);
            //            getInitialAmplitudeVal(value,index,newDataString,unitNo);
            break;
        }
        break;
    case PM_INPUT_AMP_OFFSET:
        showAmptUnit(false);
        value = PmInterfaceObj->getAmptOffset();
        strGab = QString::number(value) + QString(" dB");
        unitNo = PmInterfaceObj->getAmptUint();
        ui->lblTitle->setText("Amp Offset ");
        ui->amptBtnUnit4->show();
        ui->amptBtnUnit4->setText("dB");
        break;
    case PM_INPUT_FORWATD_RELATIVE:
        showAmptUnit(false);
        value = PmInterfaceObj->getAmptOffset();
        strGab = QString::number(value) + QString(" dB");
        unitNo = PmInterfaceObj->getAmptUint();
        if(POWER_SENSOR_V90 == PmInterfaceObj->getPowerSensorFlg())
        ui->lblTitle->setText("Relative");
        else  if(POWER_SENSOR_V91 == PmInterfaceObj->getPowerSensorFlg())
            ui->lblTitle->setText("Forward Relative");

        ui->amptBtnUnit4->show();
        ui->amptBtnUnit4->setText("dB");
        break;
    case PM_INPUT_REVERSE_RELATIVE:
        showAmptUnit(false);
        value = PmInterfaceObj->getAmptOffset();
        strGab = QString::number(value) + QString(" dB");
        unitNo = PmInterfaceObj->getAmptUint();
        ui->lblTitle->setText("Reverse Relative ");
        ui->amptBtnUnit4->show();
        ui->amptBtnUnit4->setText("dB");
        break;


    case PM_INPUT_RUNNING_AVERAGE:
        showAmptUnit(false);
        value = PmInterfaceObj->getAveragePoint();
        strGab = QString::number(value);
        ui->lblTitle->setText("Running Average ");
        ui->amptBtnUnit4->show();
        ui->amptBtnUnit4->setText("Enter");
        break;

    case PM_INPUT_TIME_INTERVAL:
        showAmptUnit(false);
        value = PmInterfaceObj->getSweepTime();
        strGab = QString::number(value) + QString(" s");
        ui->lblTitle->setText("Time Interval ");
        ui->amptBtnUnit4->show();
        ui->amptBtnUnit4->setText("s");
        break;
    case PM_INPUT_MEASURE_OFFSET:
        showAmptUnit(false);
        value = PmInterfaceObj->getMeasureOffset();
        strGab = QString::number(value) + QString(" dB");
        ui->lblTitle->setText("Measure Offset ");
        ui->amptBtnUnit4->show();
        ui->amptBtnUnit4->setText("dB");
        break;
    case PM_INPUT_CAL_ARRAY:
        showAmptUnit(false);
        value = PmInterfaceObj->getCalArray();
        strGab = QString::number(value);
        ui->lblTitle->setText("Cal Array Index ");
        ui->amptBtnUnit4->show();
        ui->amptBtnUnit4->setText("Enter");
        break;
    case PM_INPUT_CAL_CENTER_FREQ:
        showFreqUnit(true);
        intGab = PmInterfaceObj->getCalCenterFreqMHz();
        strGab = PmInterfaceObj->getFreqMHzAdjustStr(intGab);

        unitNo = PmInterfaceObj->freqUnitFindProc(value);
        ui->lblTitle->setText("Cal center freq");
        ui->freqBtnUnit3->hide();
        ui->freqBtnUnit4->hide();
        break;
    case PM_INPUT_CAL_AMPT:
        showAmptUnit(false);
        value = PmInterfaceObj->getCalAmptData(PmInterfaceObj->getCalAmptNo());
        strGab.sprintf("%.2f dBm", value);
        ui->amptBtnUnit4->show();
        ui->amptBtnUnit4->setText("dBm");
        ui->lblTitle->setText("Cal Amplitude");
        break;
    case PM_INPUT_DUTY_CYCLE:
        showAmptUnit(false);
        value = PmInterfaceObj->getDutyCycle();
        strGab.sprintf("%.2f %%", value);
        ui->lblTitle->setText("Duty Cycle ");
        ui->amptBtnUnit4->show();
        ui->amptBtnUnit4->setText("Enter");
        break;
    case PM_INPUT_CCDF:
        value = PmInterfaceObj->getCCDF();
        strGab = QString::number(value) + QString(" W");
        // ??       unitNo = PmInterfaceObj->getAmptUint();
        ui->lblTitle->setText("CCDF ");
        showAmptUnit(true);
        break;

        //    case PM_INPUT_LIMIT_FREQ:
        //        intGab = PmInterfaceObj->GetCurLimitDataIndex();
        //        value = PmInterfaceObj->getLimitCurPointFreq(intGab,PmInterfaceObj->getCurLimit()) * PM_MHZ;
        //        strGab = PmInterfaceObj->getFreqAdjustStr(value);
        //        unitNo = PmInterfaceObj->freqUnitFindProc(value);
        //        ui->lblTitle->setText("Limit Frequency");
        //        showFreqUnit(true);
        //        break;
    default:
        break;
    }
    strValue = strGab.left(strGab.indexOf(" "));
    if(strGab.indexOf(" ") > 0)
    {
        strUnit = strGab.right(strGab.length() - strGab.indexOf(" "));
    }
    qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());

    if(strlen(newDataString))
        blNumberInput = true;
    else
        blNumberInput = false;

    if(strchr(newDataString,'.'))
        blDotInput = true;
    else
        blDotInput = false;

    ui->lblValue->setText(strValue +
                          QObject::tr("<font size = 18px>%1</font>").arg(strUnit));

    return ;
}

void Pm_Dialog_Digitinput::getInitialAmplitudeVal(qreal amplitudeValue,uint entryNo,char *dataStr,qint32 amplitudeUnit)
{
    switch (entryNo) {
    case PM_INPUT_AMP_MAX:
    case PM_INPUT_AMP_MIN:
        switch (amplitudeUnit) {
        case PM_DBM:
        case PM_DBMV:
        case PM_DBUV:
            sprintf(dataStr,"%.2f",amplitudeValue);//Johnson 0705
            break;
        case PM_VOLT:
        {
            qreal voltGab = 0.;
            qreal calculator = 0.;

            calculator = pow(10, amplitudeValue / 10.);
            voltGab = 1000000. * pow(50 * calculator * 0.001, 0.5);

            if (amplitudeValue <= 20. && voltGab >= 1000000.) { //V
                sprintf(dataStr, "%.2f", (qreal) voltGab / 1000000.);
            } else if (voltGab < 1000000. && voltGab >= 1000.) { //mV
                sprintf(dataStr, "%.2f", (qreal) voltGab / 1000.);
            } else if (voltGab < 1000. && voltGab >= 1.) { //uV
                sprintf(dataStr, "%.2f", (qreal) voltGab);
            } else if (voltGab < 1. && voltGab >= 0.001) { //nV
                sprintf(dataStr, "%.2f", (qreal) voltGab * 1000);
            } else if (voltGab < 0.001 && voltGab >= 0.000001) { //pV
                sprintf(dataStr, "%.2f", (qreal) voltGab * 1000000.);
            } else if (voltGab < 0.000001 && voltGab >= 0.000000001) { //fV
                sprintf(dataStr, "%.2f", (qreal) voltGab * 1000000000.);
            } else if (voltGab < 0.000000001 && voltGab >= 0.000000000001) { //aV
                sprintf(dataStr, "%.2f", (qreal) voltGab * 1000000000000.);
            } else if (voltGab < 0.000000000001 && voltGab >= 0.000000000000001) { //zV
                sprintf(dataStr, "%.2f", (qreal) voltGab * 1000000000000000.);
            } else if (voltGab < 0.000000000000001 && voltGab >= 0.000000000000000001) { //yV
                sprintf(dataStr, "%.2f", (qreal) voltGab * 1000000000000000000.);
            } else {
                sprintf(dataStr, "%.2f", (qreal) voltGab * 1000000000000000000000.);
            }
        }
            break;
        case PM_WATTS:
        {
            qreal wattsGab = 0.;

            wattsGab = pow(10, amplitudeValue / 10.);

            if (wattsGab >= 1000) {						// W
                sprintf(dataStr, "%.2f", (qreal)wattsGab / 1000.0);
            }  else if (wattsGab >= 1) {					// mW
                sprintf(dataStr, "%.2f", (qreal)wattsGab);
            }  else if (wattsGab >= 0.001) {				// uW
                sprintf(dataStr, "%.2f", (qreal)wattsGab * 1000.0);
            }  else if (wattsGab >= 0.000001) {			// nW
                sprintf(dataStr, "%.2f", (qreal)wattsGab * 1000000.0);
            } else if (wattsGab >= 0.000000001) {			// pW
                sprintf(dataStr, "%.2f", (qreal)wattsGab * 1000000000.0);
            } else if (wattsGab >= 0.000000000001) {		// fW
                sprintf(dataStr, "%.2f", (qreal)wattsGab * 1000000000000.0);
            } else if (wattsGab >= 0.000000000000001) {   // aW
                sprintf(dataStr, "%.2f", (qreal)wattsGab * 1000000000000000.0);
            } else if (wattsGab >= 0.000000000000000001) {   // zW
                sprintf(dataStr, "%.2f", (qreal)wattsGab * 1000000000000000000.0);
            } else if (wattsGab >= 0.000000000000000000001) {   // yW
                sprintf(dataStr, "%.2f", (qreal)wattsGab * 1000000000000000000000.0);
            }
        }
            break;
        }
        break;
    }
    if(strlen(dataStr)) blNumberInput = true;
    else blNumberInput = false;


    if(strchr(dataStr,'.')) blDotInput = true;
    else blDotInput = false;
}

/**
* @brief  Clear up one bit of data.
* @param  void
* @author Roc
* @since  2019.11.5
*/
void Pm_Dialog_Digitinput::backSpace()
{
    int strLen = 0;
    char backupStr[21] = {'\0',};

    strLen = strlen(newDataString);
    if (strLen > 0) {
        strcpy (backupStr, newDataString);
        memset(newDataString, 0, sizeof(newDataString));
        strncpy(newDataString, backupStr, strLen -1);
    }

    if(!bLeftKey&&!bRightKey&&!mShiftKeyPressed)
        ui->lblValue->setText(newDataString);
    else if(!mShiftKeyPressed)
    {
        if(size_t(highLightIndex+1)>strlen(newDataString))
            highLightIndex = -1;
        if(highLightIndex>=0)
        {
            QString strNewData(newDataString);

            QString strPrevious = strNewData.left(highLightIndex);
            QString strRear = strNewData.right(strlen(newDataString)-highLightIndex-1);
            QString strHighLight = strNewData.mid(highLightIndex,1);
            ui->lblValue->setText(  strPrevious +
                                    QObject::tr("<font color = yellow>%1</font>").arg(strHighLight)+
                                    strRear
                                    );
        }
        else ui->lblValue->setText(newDataString);
    }

    if (!strlen(newDataString))
    {
        blNumberInput = false;
        blFirstIn = false;
        blDotInput = false;
        bLeftKey = false;
        bRightKey = false;
        highLightIndex = -1;
    }
}

/**
* @brief  Key press Event.
* @param  event
* @author Roc
* @since  2019.11.5
*/
void Pm_Dialog_Digitinput::keyPressEvent(QKeyEvent *event)
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
    if(keyvalue == Qt::Key_Escape)
    {
        this->close();
        return;
    }
    if(keyvalue == Qt::Key_Shift)
    {
        this->close();
        emit finishEntry(PM_SHIFT_ENABLE);
        mShiftKeyPressed = false;
        return;
    }
    if(keyvalue == Qt::Key_F3 || keyvalue == Qt::Key_Up \
            || keyvalue == Qt::Key_F8 || keyvalue == Qt::Key_Down \
            || keyvalue == Qt::Key_F9 || keyvalue == Qt::Key_F4)
    {
        this->close();
        emit ClockWiseDown(event);
        return;
    }
    keyresponse(keyvalue);

    return;
}

/**
* @brief  Close current widget.
* @param  void
* @author Roc
* @since  2019.11.5
*/
void Pm_Dialog_Digitinput::on_pb_cancel_clicked()
{
    this->close();
}

/**
* @brief  Key up control.
* @param  event
*/
void Pm_Dialog_Digitinput::keyupControl()
{
    if(mShiftKeyPressed)
        return;
    if(blNumberInput){
        if(highLightIndex>=0&& (size_t)highLightIndex<strlen(newDataString))
        {
            valueIncreaseControl();
        }
    }
}

/**
* @brief  Key down control.
* @param  event
*/
void Pm_Dialog_Digitinput::keydownControl()
{
    if(mShiftKeyPressed)
        return;
    if(blNumberInput){
        if(highLightIndex>=0&&(size_t)highLightIndex<strlen(newDataString)){
            valueDecreaseControl();
        }
    }
}

void Pm_Dialog_Digitinput::keyleftControl()
{
    if(mShiftKeyPressed)
        return;
    if(blNumberInput)
    {
        bLeftKey = true;
        blFirstIn = false;
        QString strNewData(newDataString);

        if(highLightIndex < 0) highLightIndex = strlen(newDataString)-1;
        else{
            highLightIndex--;
            if(strNewData.mid(highLightIndex,1) == "."||strNewData.mid(highLightIndex,1) == "-") highLightIndex--;
        }
    }
}

void Pm_Dialog_Digitinput::keyrightControl()
{
    if(mShiftKeyPressed)
        return;
    if(blNumberInput)
    {
        bRightKey = true;
        blFirstIn = false;
        QString strNewData(newDataString);

        if(highLightIndex < 0)
        {
            if(newDataString[0] == '-') highLightIndex = 1;
            else highLightIndex = 0;
        }
        else
        {
            highLightIndex++;
            if(strNewData.mid(highLightIndex,1) == "."||strNewData.mid(highLightIndex,1) == "-") highLightIndex++;
        }
        if((size_t)highLightIndex>=strlen(newDataString)) highLightIndex = -1;
    }
}

void Pm_Dialog_Digitinput::keyclockwiseControl()
{
    qDebug()<<endl;
    if(mShiftKeyPressed)
        return;
    if(blNumberInput)
    {
        if(highLightIndex>=0&&(size_t)highLightIndex<strlen(newDataString))
        {
            valueIncreaseControl();
        }
        else{
            getKnobValue(PM_CLOCKWISE);
        }
    }
}

void Pm_Dialog_Digitinput::keyanticlockwiseControl()
{
    qDebug()<<endl;
    if(mShiftKeyPressed)
        return;
    if(blNumberInput){
        if(highLightIndex>=0&&(size_t)highLightIndex<strlen(newDataString)){
            valueDecreaseControl();
        }
        else{
            getKnobValue(PM_ANTICLOCKWISE);
        }
    }
}

void Pm_Dialog_Digitinput::valueIncreaseControl()
{
    if(strchr(newDataString,'.')){
        //get Dot's index
        int posPrev = strchr(newDataString,'.')-newDataString+1;
        posPrev--;
        //change newDataString's value
        double dataNumber = atof(newDataString);
        if(posPrev<highLightIndex) dataNumber = dataNumber+1/qPow(10.,(double)(highLightIndex-posPrev));
        else dataNumber = dataNumber+qPow(10.,(double)(posPrev-highLightIndex-1));


        //get bits after dot and set newDataString
        int dataLenPrev = strlen(newDataString);
        int bitsAfterDot = dataLenPrev - posPrev-1;
        sprintf(newDataString,"%.9f",dataNumber);
        //get dot's index and set highLightIndex's value
        int posAfter = strchr(newDataString,'.')-newDataString+1;
        posAfter--;
        highLightIndex = highLightIndex+(posAfter-posPrev);
        //set newDataString
        for(std::size_t i = posAfter+bitsAfterDot+1;i<strlen(newDataString);i++){
            newDataString[i] = 0;
        }
    }
    else{
        int dataLenPre = strlen(newDataString);
        int dataNumber = atoi(newDataString);
        dataNumber += qPow(10.,(double)(strlen(newDataString)-highLightIndex-1));
        sprintf(newDataString,"%d",dataNumber);
        int dataLenAfter = strlen(newDataString);
        highLightIndex = highLightIndex + (dataLenAfter-dataLenPre);

        if(highLightIndex == 0&&dataNumber<0) highLightIndex++;
    }

    QString strnewData(newDataString);
    if(strnewData.mid(highLightIndex,1) == "."||strnewData.mid(highLightIndex,1) == "-") highLightIndex--;
    if((size_t)highLightIndex>=strlen(newDataString))
        highLightIndex = -1;
}

void Pm_Dialog_Digitinput::valueDecreaseControl()
{
    qDebug()<<endl;
    if(strchr(newDataString,'.')){
        //get Dot's index
        int pos = strchr(newDataString,'.')-newDataString+1;
        pos--;
        //change newDataString's value
        double dataNumber = atof(newDataString);
        if(pos<highLightIndex) dataNumber = dataNumber-1/qPow(10.,(double)(highLightIndex-pos));
        else dataNumber = dataNumber-qPow(10.,(double)(pos-highLightIndex-1));

        if(dataNumber>=0.){
            //get bits after dot and set newDataString
            int dataLen = strlen(newDataString);
            int bitsAfterDot = dataLen - pos-1;
            sprintf(newDataString,"%.9f",dataNumber);
            for(size_t i = pos+bitsAfterDot+1;i<strlen(newDataString);i++){
                newDataString[i] = 0;
            }

            //get dot's index and set highLightIndex's value
            int posAfterNumberChnage = strchr(newDataString,'.')-newDataString+1;
            posAfterNumberChnage--;
            if(posAfterNumberChnage - pos<0){
                if(highLightIndex > 0) highLightIndex--;
            }
        }
        else highLightIndex++;
    }
    else{
        qDebug()<<endl;
        int dataLenPre = strlen(newDataString);
        int dataNumber = atoi(newDataString);
        dataNumber -= qPow(10.,(double)(strlen(newDataString)-highLightIndex-1));
        sprintf(newDataString,"%d",dataNumber);
        int dataLenAfter = strlen(newDataString);
        highLightIndex = highLightIndex - (dataLenPre-dataLenAfter);

        if(highLightIndex == -1&&dataNumber>=0) highLightIndex = 0;
    }

    QString strnewData(newDataString);
    if(strnewData.mid(highLightIndex,1) == "."||strnewData.mid(highLightIndex,1) == "-") highLightIndex++;
    if((size_t)highLightIndex>=strlen(newDataString)) highLightIndex = -1;
}

/**
* @brief	旋钮设置值
* @note
* @author	Roc
* @since	2019.11.13
*/
void Pm_Dialog_Digitinput::getKnobValue(quint32 mode)
{
    qDebug()<<endl;
    QString strValue;

    switch (entryNo){
    case PM_INPUT_FREQ_CENTER:
    case PM_INPUT_FREQ_START:
    case PM_INPUT_FREQ_STOP:
        strValue = getNewFreqDataStringValue(mode,PmInterfaceObj->getStepFreq(),unitNo);
        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());
        break;
    case PM_INPUT_FREQ_STEP:
    case PM_INPUT_FREQ_SPAN:
    case PM_INPUT_FREQ_OFFSET:
//    case PM_INPUT_FREQ_OFFSET_SIZE:
    case PM_INPUT_CAL_CENTER_FREQ:
        strValue = getNewFreqDataStringValue(mode,PM_MHZ,unitNo);
        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());
        break;
    case PM_INPUT_FREQ_CHANNEL_NUM:
        break;
    case PM_INPUT_RUNNING_AVERAGE:
        if(mode == PM_CLOCKWISE)
            strValue.sprintf("%d", atoi(newDataString)+1);
        else if(mode == PM_ANTICLOCKWISE)
        {
            if(atoi(newDataString) >= 2)
                strValue.sprintf("%d", atoi(newDataString)-1);
            else
                strValue = QString("%1").arg("1");
        }
        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());
        break;
    case PM_INPUT_CAL_ARRAY:
        if(mode == PM_CLOCKWISE)
            strValue.sprintf("%d", atoi(newDataString)+1);
        else if(mode == PM_ANTICLOCKWISE)
        {
            if(atoi(newDataString) >= 1)
                strValue.sprintf("%d", atoi(newDataString)-1);
            else
                strValue = QString("%1").arg("0");
        }
        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());
        break;
    case PM_INPUT_TIME_INTERVAL:
        break;
    case PM_INPUT_MEASURE_OFFSET:

        break;
    case PM_INPUT_AMP_MAX:
        break;
    case PM_INPUT_AMP_MIN:
        break;
    case PM_INPUT_AMP_OFFSET:
        break;
    case PM_INPUT_FORWATD_RELATIVE:
        break;
    case PM_INPUT_REVERSE_RELATIVE:
        break;
    case PM_INPUT_FORWARD_UPPER:
        break;
    case PM_INPUT_FORWARD_LOWER:
        break;
    case PM_INPUT_REVERSE_UPPER:
        break;
    case PM_INPUT_REVERSE_LOWER:
        break;
    case PM_INPUT_DUTY_CYCLE:
        break;
    case PM_INPUT_CAL_AMPT:
        break;
    default:
        break;
    }
}
QString Pm_Dialog_Digitinput::getNewFreqDataStringValue(int clockWiseMode,qulonglong freStep,int unitNo)
{
    qDebug()<<endl;
    QString strValue;
    double unitGab = 0.;

    QString strGab;
    int pos = 0;
    qulonglong freqVal;
    double newDataStringValue = strtod(newDataString,NULL);

    if(clockWiseMode == PM_CLOCKWISE){
        switch(unitNo) {
        case UNIT_GHZ:
            unitGab = (double) PM_GHZ;
            break;
        case UNIT_MHZ:
            unitGab = (double) PM_MHZ;
            break;
        case UNIT_KHZ:
            unitGab = (double) PM_KHZ;
            break;
        case UNIT_HZ:
            unitGab = (double) PM_HZ;
            break;
        }
        freqVal = freStep+newDataStringValue*unitGab;

        strGab = QString::number(freqVal, 'd',0);
        pos = PmInterfaceObj->getGlobalUserVariable()->notZeroPositionFindFunc(strGab);

        unitNo = PmInterfaceObj->getGlobalUserVariable()->freqUnitFindProc(freqVal);

        switch (unitNo) {
        case UNIT_GHZ:
            unitGab = (double) PM_GHZ;
            switch (pos) {
            case 0:
            case 1:
            case 2:
                strValue.sprintf("%.3f", (double) freqVal / unitGab);
                break;
            case 3:
                strValue.sprintf("%.3f", (double) freqVal / unitGab);
                break;
            case 4:
                strValue.sprintf("%.4f", (double) freqVal / unitGab);
                break;
            case 5:
                strValue.sprintf("%.5f", (double) freqVal / unitGab);
                break;
            case 6:
                strValue.sprintf("%.6f", (double) freqVal / unitGab);
                break;
            case 7:
                strValue.sprintf("%.7f", (double) freqVal / unitGab);
                break;
            case 8:
                strValue.sprintf("%.8f", (double) freqVal / unitGab);
                break;
            case 9:
                strValue.sprintf("%.9f", (double) freqVal / unitGab);
                break;
            default:
                strValue.sprintf("%.2f", (double) freqVal / unitGab);
                break;
            }
            break;
        case UNIT_MHZ:
            unitGab = (double) PM_MHZ;
            switch (pos) {
            case 0:
            case 1:
            case 2:
                strValue.sprintf("%.3f", (double) freqVal / unitGab);
                break;
            case 3:
                strValue.sprintf("%.3f", (double) freqVal / unitGab);
                break;
            case 4:
                strValue.sprintf("%.4f", (double) freqVal / unitGab);
                break;
            case 5:
                strValue.sprintf("%.5f", (double) freqVal / unitGab);
                break;
            case 6:
                strValue.sprintf("%.6f", (double) freqVal / unitGab);
                break;
            default:
                strValue.sprintf("%.2f", (double) freqVal / unitGab);
                break;
            }
            break;
        case UNIT_KHZ:
            unitGab = (double) PM_KHZ;
            switch (pos) {
            case 0:
            case 1:
            case 2:
                strValue.sprintf("%.3f", (double) freqVal / unitGab);
                break;
            case 3:
                strValue.sprintf("%.3f", (double) freqVal / unitGab);
                break;
            default:
                strValue.sprintf("%.2f", (double) freqVal / unitGab);
                break;
            }
            break;
        case UNIT_HZ:
            unitGab = (double) PM_HZ;
            strValue.sprintf("%.2f", (double) freqVal / unitGab);
            break;
        }
    }
    else if(clockWiseMode == PM_ANTICLOCKWISE){
        switch(unitNo) {
        case UNIT_GHZ:
            unitGab = (double) PM_GHZ;
            break;
        case UNIT_MHZ:
            unitGab = (double) PM_MHZ;
            break;
        case UNIT_KHZ:
            unitGab = (double) PM_KHZ;
            break;
        case UNIT_HZ:
            unitGab = (double) PM_HZ;
            break;
        }
        if(newDataStringValue*unitGab>=freStep)
            freqVal = newDataStringValue*unitGab-freStep;
        else /*return QString(newDataString)*/
            freqVal = 0;
        //        if(freqVal < 0)
        //            freqVal = 0;
        strGab = QString::number(freqVal, 'd',0);
        pos = PmInterfaceObj->getGlobalUserVariable()->notZeroPositionFindFunc(strGab);

        unitNo = PmInterfaceObj->getGlobalUserVariable()->freqUnitFindProc(freqVal);

        switch (unitNo) {
        case UNIT_GHZ:
            unitGab = (double) PM_GHZ;
            //the number of bit after "." is 9-pos
            switch (pos) {
            case 0:
            case 1:
            case 2:
                strValue.sprintf("%.3f", (double) freqVal / unitGab);
                break;
            case 3:
                strValue.sprintf("%.3f", (double) freqVal / unitGab);
                break;
            case 4:
                strValue.sprintf("%.4f", (double) freqVal / unitGab);
                break;
            case 5:
                strValue.sprintf("%.5f", (double) freqVal / unitGab);
                break;
            case 6:
                strValue.sprintf("%.6f", (double) freqVal / unitGab);
                break;
            case 7:
                strValue.sprintf("%.7f", (double) freqVal / unitGab);
                break;
            case 8:
                strValue.sprintf("%.8f", (double) freqVal / unitGab);
                break;
            case 9:
                strValue.sprintf("%.9f", (double) freqVal / unitGab);
                break;
            default:
                strValue.sprintf("%.2f", (double) freqVal / unitGab);
                break;
            }
            break;
        case UNIT_MHZ:
            unitGab = (double) PM_MHZ;
            //the number of bit after "." is 6-pos
            switch (pos) {
            case 0:
            case 1:
            case 2:
                strValue.sprintf("%.3f", (double) freqVal / unitGab);
                break;
            case 3:
                strValue.sprintf("%.3f", (double) freqVal / unitGab);
                break;
            case 4:
                strValue.sprintf("%.4f", (double) freqVal / unitGab);
                break;
            case 5:
                strValue.sprintf("%.5f", (double) freqVal / unitGab);
                break;
            case 6:
                strValue.sprintf("%.6f", (double) freqVal / unitGab);
                break;
            default:
                strValue.sprintf("%.2f", (double) freqVal / unitGab);
                break;
            }
            break;
        case UNIT_KHZ:
            unitGab = (double) PM_KHZ;
            //the number of bit after "." is 3-pos
            switch (pos) {
            case 0:
            case 1:
            case 2:
                strValue.sprintf("%.3f", (double) freqVal / unitGab);
                break;
            case 3:
                strValue.sprintf("%.3f", (double) freqVal / unitGab);
                break;
            default:
                strValue.sprintf("%.2f", (double) freqVal / unitGab);
                break;
            }
            break;
        case UNIT_HZ:
            unitGab = (double) PM_HZ;
            strValue.sprintf("%.2f", (double) freqVal / unitGab);
            break;
        }
    }
    return strValue;
}

void Pm_Dialog_Digitinput::btn_clicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    qint32 keyValue;
    keyValue = mBtnkey.find(btn).value();
    keyresponse(keyValue);
    return;
}

void Pm_Dialog_Digitinput::keyresponse(qint32 keyValue)
{
    int strLen = 0;
    strLen = strlen(newDataString);
    if (strLen >= 19 &&   keyValue != Qt::Key_Escape)
    {
        return;
    }

    switch(keyValue)
    {
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
        switch(entryNo)
        {
        case PM_INPUT_RUNNING_AVERAGE:
            if(strlen(newDataString) >= 6)
                return;
            break;
        default:
            if(strlen(newDataString) >= 13 && newDataString[strlen(newDataString) - 1] != '.')
                return;
            break;
        }
        break;
    case Qt::Key_Up:
    case Qt::Key_F8:
    case Qt::Key_F3:
        switch(entryNo)
        {
        case PM_INPUT_RUNNING_AVERAGE:
            if(atoi(newDataString) - 70000 >= 0)
            {
                strcpy(newDataString,"70000");
                return;
            }
            break;
        default:
            switch(unitNo) {
            case UNIT_GHZ:
                if(atof(newDataString) - 44. >= 0)
                {
                    strcpy(newDataString,"44.00");
                    return;
                }
                break;
            case UNIT_MHZ:
                if(atof(newDataString) - 44000. >= 0) {
                    strcpy(newDataString,"44000.00");
                    return;
                }
                break;
            case UNIT_KHZ:
                if(atof(newDataString) - 44000000. >= 0)
                {
                    strcpy(newDataString,"44000000.00");
                    return;
                }
                break;
            case UNIT_HZ:
                if(atof(newDataString) - 44000000000. >= 0)
                {
                    strcpy(newDataString,"44000000000.00");
                    return;
                }
                break;
            }
            break;
        }
        break;
    }

    switch (keyValue)
    {
    case Qt::Key_Escape:
        backSpace();
        break;
    case Qt::Key_0:
        if(mShiftKeyPressed){
            PmInterfaceObj->getGlobalUserVariable()->KeyNumber = 0;
            on_pb_cancel_clicked();
            return;
        }
        if(blFirstIn){
            memset(newDataString,0,sizeof(newDataString));
            strcpy(newDataString,"0");
            blDotInput = false;
            blFirstIn = false;
        }
        else if(!strlen(newDataString)||strcmp(newDataString,"0")){
            if(highLightIndex<0) strncat(newDataString, "0" , 1);
            else{
                char tempDataString[20];
                memset(tempDataString,0,sizeof(char)*20);

                for(size_t i = 0;i<strlen(newDataString);i++){
                    if(i ==(size_t)highLightIndex){
                        if(i == 0) tempDataString[i] = newDataString[i];
                        else tempDataString[i] = '0';
                    }
                    else tempDataString[i] = newDataString[i];
                }
                memset(newDataString,0,sizeof(char)*20);
                strcpy(newDataString,tempDataString);
            }
            blNumberInput = true;
        }
        break;
    case Qt::Key_1:
        if(mShiftKeyPressed){
            PmInterfaceObj->getGlobalUserVariable()->KeyNumber = 1;
            on_pb_cancel_clicked();
            return;
        }
        if(blFirstIn){
            memset(newDataString,0,sizeof(newDataString));
            strcpy(newDataString,"1");
            blDotInput = false;
            blFirstIn = false;
        }
        else /*if(strcmp(newDataString,"0"))*/{
            if(highLightIndex<0) strncat(newDataString, "1" , 1);
            else{
                char tempDataString[20];
                memset(tempDataString,0,sizeof(char)*20);

                for(size_t i = 0;i<strlen(newDataString);i++){
                    if(i ==(size_t)highLightIndex){
                        tempDataString[i] = '1';
                    }
                    else tempDataString[i] = newDataString[i];
                }
                memset(newDataString,0,sizeof(char)*20);
                strcpy(newDataString,tempDataString);
            }
            blNumberInput = true;
        }
        break;
    case Qt::Key_2:
        if(mShiftKeyPressed){
            PmInterfaceObj->getGlobalUserVariable()->KeyNumber = 2;
            on_pb_cancel_clicked();
            return;
        }
        if(blFirstIn){
            memset(newDataString,0,sizeof(newDataString));
            strcpy(newDataString,"2");
            blDotInput = false;
            blFirstIn = false;
        }
        else /*if(strcmp(newDataString,"0"))*/{
            if(highLightIndex<0) strncat(newDataString, "2" , 1);
            else{
                char tempDataString[20];
                memset(tempDataString,0,sizeof(char)*20);

                for(size_t i = 0;i<strlen(newDataString);i++){
                    if(i ==(size_t)highLightIndex){
                        tempDataString[i] = '2';
                    }
                    else tempDataString[i] = newDataString[i];
                }
                memset(newDataString,0,sizeof(char)*20);
                strcpy(newDataString,tempDataString);
            }
            blNumberInput = true;
        }
        break;
    case Qt::Key_3:
        if(mShiftKeyPressed){
            PmInterfaceObj->getGlobalUserVariable()->KeyNumber = 3;
            on_pb_cancel_clicked();
            return;
        }
        if(blFirstIn){
            memset(newDataString,0,sizeof(newDataString));
            strcpy(newDataString,"3");
            blDotInput = false;
            blFirstIn = false;
        }
        else /*if(strcmp(newDataString,"0"))*/{
            if(highLightIndex<0) strncat(newDataString, "3" , 1);
            else{
                char tempDataString[20];
                memset(tempDataString,0,sizeof(char)*20);

                for(size_t i = 0;i<strlen(newDataString);i++){
                    if(i ==(size_t)highLightIndex){
                        tempDataString[i] = '3';
                    }
                    else tempDataString[i] = newDataString[i];
                }
                memset(newDataString,0,sizeof(char)*20);
                strcpy(newDataString,tempDataString);
            }
            blNumberInput = true;
        }
        break;
    case Qt::Key_4:
        if(mShiftKeyPressed){
            PmInterfaceObj->getGlobalUserVariable()->KeyNumber = 4;
            on_pb_cancel_clicked();
            return;
        }
        if(blFirstIn){
            memset(newDataString,0,sizeof(newDataString));
            strcpy(newDataString,"4");
            blDotInput = false;
            blFirstIn = false;
        }
        else /*if(strcmp(newDataString,"0"))*/{
            if(highLightIndex<0) strncat(newDataString, "4" , 1);
            else{
                char tempDataString[20];
                memset(tempDataString,0,sizeof(char)*20);

                for(size_t i = 0;i<strlen(newDataString);i++){
                    if(i ==(size_t)highLightIndex){
                        tempDataString[i] = '4';
                    }
                    else tempDataString[i] = newDataString[i];
                }
                memset(newDataString,0,sizeof(char)*20);
                strcpy(newDataString,tempDataString);
            }
            blNumberInput = true;
        }
        break;
    case Qt::Key_5:
        if(mShiftKeyPressed){
            PmInterfaceObj->getGlobalUserVariable()->KeyNumber = 5;
            on_pb_cancel_clicked();
            return;
        }
        if(blFirstIn){
            memset(newDataString,0,sizeof(newDataString));
            strcpy(newDataString,"5");
            blDotInput = false;
            blFirstIn = false;
        }
        else /*if(strcmp(newDataString,"0"))*/{
            if(highLightIndex<0) strncat(newDataString, "5" , 1);
            else{
                char tempDataString[20];
                memset(tempDataString,0,sizeof(char)*20);

                for(size_t i = 0;i<strlen(newDataString);i++){
                    if(i ==(size_t)highLightIndex){
                        tempDataString[i] = '5';
                    }
                    else tempDataString[i] = newDataString[i];
                }
                memset(newDataString,0,sizeof(char)*20);
                strcpy(newDataString,tempDataString);
            }
            blNumberInput = true;
        }
        break;
    case Qt::Key_6:
        if(mShiftKeyPressed){
            PmInterfaceObj->getGlobalUserVariable()->KeyNumber = 6;
            on_pb_cancel_clicked();
            return;
        }
        if(blFirstIn){
            memset(newDataString,0,sizeof(newDataString));
            strcpy(newDataString,"6");
            blDotInput = false;
            blFirstIn = false;
        }
        else /*if(strcmp(newDataString,"0"))*/{
            if(highLightIndex<0) strncat(newDataString, "6" , 1);
            else{
                char tempDataString[20];
                memset(tempDataString,0,sizeof(char)*20);

                for(size_t i = 0;i<strlen(newDataString);i++){
                    if(i ==(size_t)highLightIndex){
                        tempDataString[i] = '6';
                    }
                    else tempDataString[i] = newDataString[i];
                }
                memset(newDataString,0,sizeof(char)*20);
                strcpy(newDataString,tempDataString);
            }
            blNumberInput = true;
        }
        break;
    case Qt::Key_7:
        if(mShiftKeyPressed){
            PmInterfaceObj->getGlobalUserVariable()->KeyNumber = 7;
            on_pb_cancel_clicked();
            return;
        }
        if(blFirstIn){
            memset(newDataString,0,sizeof(newDataString));
            strcpy(newDataString,"7");
            blDotInput = false;
            blFirstIn = false;
        }
        else /*if(strcmp(newDataString,"0"))*/{
            if(highLightIndex<0) strncat(newDataString, "7" , 1);
            else{
                char tempDataString[20];
                memset(tempDataString,0,sizeof(char)*20);

                for(size_t i = 0;i<strlen(newDataString);i++){
                    if(i ==(size_t)highLightIndex){
                        tempDataString[i] = '7';
                    }
                    else tempDataString[i] = newDataString[i];
                }
                memset(newDataString,0,sizeof(char)*20);
                strcpy(newDataString,tempDataString);
            }
            blNumberInput = true;
        }
        break;
    case Qt::Key_8:
        if(mShiftKeyPressed){
            PmInterfaceObj->getGlobalUserVariable()->KeyNumber = 8;
            on_pb_cancel_clicked();
            return;
        }
        if(blFirstIn){
            memset(newDataString,0,sizeof(newDataString));
            strcpy(newDataString,"8");
            blDotInput = false;
            blFirstIn = false;
        }
        else /*if(strcmp(newDataString,"0"))*/{
            if(highLightIndex<0) strncat(newDataString, "8" , 1);
            else{
                char tempDataString[20];
                memset(tempDataString,0,sizeof(char)*20);

                for(size_t i = 0;i<strlen(newDataString);i++){
                    if(i ==(size_t)highLightIndex){
                        tempDataString[i] = '8';
                    }
                    else tempDataString[i] = newDataString[i];
                }
                memset(newDataString,0,sizeof(char)*20);
                strcpy(newDataString,tempDataString);
            }
            blNumberInput = true;
        }
        break;
    case Qt::Key_9:
        if(mShiftKeyPressed){
            PmInterfaceObj->getGlobalUserVariable()->KeyNumber = 9;
            on_pb_cancel_clicked();
            return;
        }
        if(blFirstIn){
            memset(newDataString,0,sizeof(newDataString));
            strcpy(newDataString,"9");
            blDotInput = false;
            blFirstIn = false;
        }
        else /*if(strcmp(newDataString,"0")&&!mShiftKeyPressed)*/{
            if(highLightIndex<0) strncat(newDataString, "9" , 1);
            else{
                char tempDataString[20];
                memset(tempDataString,0,sizeof(char)*20);

                for(size_t i = 0;i<strlen(newDataString);i++){
                    if(i ==(size_t)highLightIndex){
                        tempDataString[i] = '9';
                    }
                    else tempDataString[i] = newDataString[i];
                }
                memset(newDataString,0,sizeof(char)*20);
                strcpy(newDataString,tempDataString);
            }
            blNumberInput = true;
        }
        break;
    case Qt::Key_F1://preset
        break;
    case Qt::Key_Minus:  // - Minus
    case Qt::Key_F2:    //  +/-
        if(mShiftKeyPressed)
            return;
        else
        {
            if(entryNo == PM_INPUT_FREQ_CENTER || entryNo == PM_INPUT_FREQ_START
                    || entryNo == PM_INPUT_FREQ_STOP || entryNo == PM_INPUT_FREQ_CENTER)
            {
                if(PmInterfaceObj->getFreqOffset() <= 0.00001 && PmInterfaceObj->getFreqOffset() >= -0.00001)
                {
                    return;
                }
            }
            //      ???     else if(entryNo != PM_INPUT_CURVE && entryNo != PM_INPUT_REF_OFFSET && entryNo != PM_INPUT_DELTA_MARKER_EDIT && entryNo != PM_INPUT_REF_LEVEL
            //                   && entryNo != PM_INPUT_FREQ_OFFSET && entryNo != PM_INPUT_LIMIT_AMPT && entryNo != PM_INPUT_FMT_AMPT && entryNo != PM_INPUT_TRIGGER_LEVEL)
            //               return;
        }
        if(blFirstIn){
            memset(newDataString,0,sizeof(newDataString));
            strcpy(newDataString,"-");
            blDotInput = false;
            blFirstIn = false;
            blNumberInput = true;
        }
        else{
            if (blNumberInput == false){
                strncat(newDataString, "-" , 1);
                blNumberInput = true;
            }
            else{
                if(strlen(newDataString) == 1&&strcmp(newDataString,"-") == 0){
                    memset(newDataString,0,sizeof(char)*20);
                    blNumberInput = false;
                }
                else{
                    if(strchr(newDataString,'.')){
                        double DataNumber = atof(newDataString);
                        if(DataNumber>0){
                            for(int i = strlen(newDataString)-1;i>=0;i--){
                                newDataString[i+1] = newDataString[i];
                            }
                            newDataString[0] = '-';

                            if((bLeftKey||bRightKey)&&highLightIndex >= 0){
                                highLightIndex++;
                            }

                            QString strnewData(newDataString);
                            if(strnewData.mid(highLightIndex,1) == "."||strnewData.mid(highLightIndex,1) == "-") highLightIndex++;
                            if((size_t)highLightIndex>=strlen(newDataString)) highLightIndex = -1;
                        }
                        else if(DataNumber<0){
                            for(size_t i = 0;i<strlen(newDataString);i++){
                                newDataString[i] = newDataString[i+1];
                            }

                            if(bLeftKey||bRightKey) highLightIndex--;

                            QString strnewData(newDataString);
                            if(strnewData.mid(highLightIndex,1) == "."||strnewData.mid(highLightIndex,1) == "-") highLightIndex++;
                            if((size_t)highLightIndex>=strlen(newDataString)) highLightIndex = -1;
                        }
                    }
                    else{
                        long DataNumber = atoi(newDataString);
                        memset(newDataString,0,sizeof(char)*20);
                        sprintf(newDataString,"%ld",-DataNumber);

                        if(DataNumber>0&&(bLeftKey||bRightKey)) highLightIndex++;
                        else if(DataNumber<0&&(bLeftKey||bRightKey)) highLightIndex--;
                    }
                }
            }
        }
        break;
    case Qt::Key_F5://menu
        break;
    case Qt::Key_Enter://Enter
    case Qt::Key_Return:
        break;
    case Qt::Key_Left:
    case Qt::Key_F6://key_left
        if(mShiftKeyPressed)
            return;
        keyleftControl();
        break;
    case Qt::Key_Right:
    case Qt::Key_F7:
        if(mShiftKeyPressed)
            return;
        keyrightControl();
        break;
    case Qt::Key_Up:
    case Qt::Key_F8:
        if(mShiftKeyPressed)
            return;
        keyupControl();
        break;
    case Qt::Key_Down:
    case Qt::Key_F9:
        if(mShiftKeyPressed)
            return;
        keydownControl();
        break;
    case Qt::Key_F3://clockwise
        if(mShiftKeyPressed)
            return;
        keyclockwiseControl();
        //blFirstIn = false;
        break;
    case Qt::Key_F4://anticlockwise
        if(mShiftKeyPressed)
            return;
        keyanticlockwiseControl();
        break;
    case Qt::Key_Period:  // . Dot
        //  ???     if(entryNo == PM_INPUT_AVERAGE_COUNT || entryNo == PM_INPUT_FREQ_CHANNEL_NUM || entryNo == PM_INPUT_LIMIT_SELECT_INDEX
        //               || entryNo == PM_INPUT_FMT_SELECT_INDEX)
        //           return;
        if(mShiftKeyPressed)
            return;
        blDotInput = strrchr(newDataString,'.');//Johnson 0828
        if(!blDotInput&&blNumberInput&&strcmp(newDataString,"-")){
            strncat(newDataString, "." , 1);
            blDotInput = true;
        }
        break;
    case Qt::Key_Delete:
        clearAll();
        break;
    default:
        break;
    }



    if(!bLeftKey&&!bRightKey&&!mShiftKeyPressed)
        ui->lblValue->setText(newDataString);
    else if(!mShiftKeyPressed){
        if(highLightIndex>=0){
            QString strNewData(newDataString);

            QString strPrevious = strNewData.left(highLightIndex);
            QString strRear = strNewData.right(strlen(newDataString)-highLightIndex-1);
            QString strHighLight = strNewData.mid(highLightIndex,1);
            ui->lblValue->setText(  strPrevious +
                                    QObject::tr("<font color = yellow>%1</font>").arg(strHighLight)+
                                    strRear
                                    );
        }
        else ui->lblValue->setText(newDataString);
    }
    return;
}

qint32 Pm_Dialog_Digitinput::getEntryNo()
{
    return entryNo;
}

qint32 Pm_Dialog_Digitinput::getUnitNo()
{
    return unitNo;
}

void Pm_Dialog_Digitinput::clearEdit()
{
    memset(newDataString,0,sizeof(newDataString));
    strcpy(newDataString,"");
    ui->lblValue->setText(newDataString);
    return;
}

int Pm_Dialog_Digitinput::freqSpecCompareFunc(int unitPos)
{
    QString strValue;
    qreal value = 0.;
    qulonglong freq = 0;
    int minusFlag = 0;

    //Johnson 0709
    strValue = newDataString;
    value = strValue.toDouble();
    if(value < 0.)  {
        value *= -1;
        minusFlag = 1;   // 음수 값 인지 (Delta Marker Edit)
    }

    switch (unitPos)
    {
    case 1:
        freq =((qulonglong)(value * (double)PM_GHZ + 0.5));   // 1.2Ghz 입력시 1.9999999로 저장되어 + .5로 수정
        break;
    case 2:
        freq =((qulonglong)(value * (double)PM_MHZ + 0.5));
        break;
    case 3:
        freq =((qulonglong)(value * (double)PM_KHZ + 0.5));
        break;
    case 4:
        freq =((qulonglong)(value * (double) PM_HZ + 0.5));
        break;
    }
    if(entryNo == PM_INPUT_FREQ_OFFSET || entryNo == PM_INPUT_FREQ_CENTER
            || entryNo == PM_INPUT_FREQ_START || entryNo == PM_INPUT_FREQ_STOP)
    {
        if(minusFlag == 1)
        {
            freq *= -1;
        }
    }

    PmInterfaceObj->getGlobalUserVariable()->entryInputMode = PM_NOT_USE;

    //  switch (entryNo)
    //  {
    ////  case PM_INPUT_MANUAL_RBW:

    //      if(1 == PmInterfaceObj->getGlobalUserVariable()->gMeterParam.gConfig_Freq.nSpanType)
    //      {
    //          if(freq <= 3001)
    //          {
    //              this->close();
    //              return 0;
    //          }
    //      }

    //      return 1;
    //      break;

    //  }

    if ( PmInterfaceObj->getGlobalUserVariable()->gMenu ==  PM_MENU_POWER_SENSOR)
    {
        switch (entryNo)
        {
        case PM_INPUT_FREQ_CENTER:
            PmInterfaceObj->setCenterFreq(freq);
            break;
        case PM_INPUT_FREQ_START:
            PmInterfaceObj->setStartFreq(freq);
            break;
        case PM_INPUT_FREQ_STOP:
            PmInterfaceObj->setStopFreq(freq);
            break;
        case PM_INPUT_FREQ_STEP:
            PmInterfaceObj->setStepFreq(freq);
//            PmInterfaceObj->setFreqOffsetSize(freq);
            break;
        case PM_INPUT_FREQ_SPAN:
            PmInterfaceObj->setSpan(freq);
            break;
        case PM_INPUT_FREQ_OFFSET:
            PmInterfaceObj->setFreqOffset(freq);
            break;
//        case PM_INPUT_FREQ_OFFSET_SIZE:
//            PmInterfaceObj->setFreqOffsetSize(freq);
//            break;
        case PM_INPUT_CAL_CENTER_FREQ:
            PmInterfaceObj->adjustFreqByCal(freq);
            break;


        }
        PmInterfaceObj->getGlobalUserVariable()->entryInputMode = entryNo;

        return 1;
    }
    else
    {
        // Power Sensor의 Freq Input
        //      switch (entryNo)
        //      {
        //        case PM_INPUT_POWERSENSOR_FREQ:

        //          PmInterfaceObj->getGlobalUserVariable()->gPowersensorFreq = freq;
        //          return 1;
        //          break;
        //        }
    }

    return 1;

}

int Pm_Dialog_Digitinput::timeSpecCompareFunc(int unitPos)
{
    QString strValue;
    double value = 0.;
    double  _time = 0.0;

    strValue = newDataString;
    value = strValue.toDouble();

    switch (unitPos)
    {
    case 4:  //s
        _time = (value * (double)PM_MHZ);
        break;
    case 3:  //ms
        _time = (value * (double)PM_KHZ);
        break;
    case 2: //us
        _time = value;
        //      _time =  (value / (double)PM_KHZ);
        break;
    case 1: //ns
        _time =  value  / (double)PM_KHZ;
        break;
    }


    PmInterfaceObj->getGlobalUserVariable()->entryInputMode = PM_NOT_USE;

    switch (entryNo)
    {
    case PM_INPUT_TIME_INTERVAL:
        PmInterfaceObj->setSweepTime(_time);
        break;
    }

    return 1;
}

int Pm_Dialog_Digitinput::amptdSpecCompareFunc(int unitNo)
{
    qreal tempVal = 0.;

    QString strValue;
    double value = 0.;
    qint32 AmptUnit= 0;
    strValue = newDataString;
    value = strValue.toDouble();
    if(PM_INPUT_AMP_MAX == entryNo ||
            PM_INPUT_AMP_MIN == entryNo ||
            PM_INPUT_FORWARD_UPPER == entryNo ||
            PM_INPUT_FORWARD_LOWER == entryNo ||
            PM_INPUT_REVERSE_UPPER == entryNo ||
            PM_INPUT_REVERSE_LOWER == entryNo ||
            PM_INPUT_CAL_AMPT == entryNo)
    {
        AmptUnit = PmInterfaceObj->getAmptUint();
        switch (AmptUnit)
        {
        case PM_WATTS:
            if (unitNo == 1) // W
                tempVal = value;
            else if (unitNo == 2) // mW
                tempVal = value / 1000.;
            else if (unitNo == 3) // uW
                tempVal = value / 1000000.;
            else if (unitNo == 4) // nW
                tempVal = value / 1000000000.;
            else if (unitNo == 5) // pW
                tempVal = value / 1000000000000.;
            else if (unitNo == 6) // fW
                tempVal = value / 1000000000000000.;
            else if (unitNo == 7) // aW
                tempVal = value / 1000000000000000000.;

            value = PmInterfaceObj->getGlobalUserVariable()->wattsToDbmCalculatorFunc(tempVal);
            break;
        case PM_VOLT:
            if (unitNo == 5)     // V
                tempVal = value *  1000000.;
            else if (unitNo == 6) // mV
                tempVal = value * 1000.;
            else if (unitNo == 7) // uV
                tempVal = value;

            value = PmInterfaceObj->getGlobalUserVariable()->voltToDbmCalculatorFunc(tempVal);
            break;
        case PM_DBV:
            value -= PM_dBVFix;
            break;
        case PM_DBMV:
            value -= PM_dBmVFix;
            break;
        case PM_DBUV:
            value -= PM_dBuVFix;
            break;
        }
    }

    switch (entryNo)
    {
    case PM_INPUT_AMP_MAX:
        PmInterfaceObj->setAmptMax(value);
        break;
    case PM_INPUT_AMP_MIN:
        PmInterfaceObj->setAmptMin(value);
        break;
    case PM_INPUT_AMP_OFFSET:
        PmInterfaceObj->setAmptOffset(value);
        break;
    case PM_INPUT_FORWATD_RELATIVE:
        PmInterfaceObj->setAmptForwardRelativeData(value);
        break;
    case PM_INPUT_REVERSE_RELATIVE:
        PmInterfaceObj->setAmptReverseRelativeData(value);
        break;
    case PM_INPUT_MEASURE_OFFSET:
        PmInterfaceObj->setMeasureOffset(value);
        break;
    case PM_INPUT_FORWARD_UPPER:
        PmInterfaceObj->setForwardUpperLimt(value);
        break;
    case PM_INPUT_FORWARD_LOWER:
        PmInterfaceObj->setForwardLowerLimt(value);
        break;
    case PM_INPUT_REVERSE_UPPER:
        PmInterfaceObj->setReverseUpperLimt(value);
        break;
    case PM_INPUT_REVERSE_LOWER:
        PmInterfaceObj->setReverseLowerLimt(value);
        break;
    case PM_INPUT_CAL_AMPT:
        PmInterfaceObj->setCalAmptData(PmInterfaceObj->getCalAmptNo(),value);
        break;
    default:
        break;
    }
    return 1;
}
void Pm_Dialog_Digitinput::on_freqBtnUnit1_clicked()
{
    int retNo = 0;
    int butNo = 1;

    //judgeRange(1);

    //if (atof(oldDataString) - atof(newDataString) == 0&&unitNo == 1)
    if(!strcmp(oldDataString,newDataString) && unitNo == 1){
        this->close();
        return;
    }

    //    if (entryNo ==  PM_INPUT_SWEEP_TIME)
    //        retNo = timeSpecCompareFunc(butNo);
    //    else
    retNo = freqSpecCompareFunc(butNo);

    if (retNo == 1)
    {
        this->close();
        emit finishEntry(entryNo);
    }
}

void Pm_Dialog_Digitinput::on_freqBtnUnit2_clicked()
{
    int retNo = 0;
    int butNo = 2;

    if(!strcmp(oldDataString,newDataString) && unitNo == 2)
    {
        this->close();
        return;
    }

    retNo = freqSpecCompareFunc(butNo);

    if (retNo == 1)
    {
        this->close();
        emit finishEntry(entryNo);
    }
    return ;
}

void Pm_Dialog_Digitinput::on_freqBtnUnit3_clicked()
{
    int retNo = 0;
    int butNo = 3;

    if(!strcmp(oldDataString,newDataString) && unitNo == 3)
    {
        this->close();
        return;
    }

    //    if (entryNo ==  PM_INPUT_SWEEP_TIME)
    //        retNo = timeSpecCompareFunc(butNo);
    //    else
    retNo = freqSpecCompareFunc(butNo);

    if (retNo == 1)
    {
        this->close();
        emit finishEntry(entryNo);
    }
    return ;
}

void Pm_Dialog_Digitinput::on_freqBtnUnit4_clicked()
{
    int retNo = 0;
    int butNo = 4;
    int value = 0;
    //    double occupiedValue = 0.;
    QString strValue;

    if(!strcmp(oldDataString,newDataString) && unitNo == 4){
        this->close();
        return;
    }

    //    switch (entryNo)
    //    {
    //    case PM_INPUT_AVERAGE_COUNT:
    //        strValue = ui->lblValue->text();
    //        value = strValue.toInt();
    //        PmInterfaceObj->setAvgNum(PmInterfaceObj->getCurTrace(),value);
    //        retNo = 1;
    //        break;
    //    case PM_INPUT_SWEEP_TIME:
    //        retNo = timeSpecCompareFunc(butNo);
    //        break;
    //    default:
    //        retNo = freqSpecCompareFunc(butNo);
    //        break;
    //    }

    retNo = freqSpecCompareFunc(butNo);
    if (retNo == 1)
    {
        this->close();
        emit finishEntry(entryNo);
    }
    return ;
}

void Pm_Dialog_Digitinput::on_amptBtnUnit1_clicked()
{
    //    qreal value = 0;
    int butNo =1;
    qint32 retNo = 0;
    if(!strcmp(oldDataString,newDataString) && unitNo == 1)
    {
        this->close();
        return;
    }
    //    if(entryNo == PM_INPUT_PERSISTENCE_TIME || entryNo == PM_INPUT_ACQ_TIME || entryNo == PM_INPUT_TRIGGER_DELAY_VALUE
    //            || entryNo == PM_INPUT_TRIGGER_PERTIMER || entryNo == PM_INPUT_TRIGGER_HOLDTIME)
    //    {
    //        retNo = timeSpecCompareFunc(UNIT_S);
    //    }
    //    else
    retNo = amptdSpecCompareFunc(butNo);
    if (retNo == 1)
    {
        this->close();
        emit finishEntry(entryNo);
    }
    return;
}

void Pm_Dialog_Digitinput::on_amptBtnUnit2_clicked()
{
    //    qreal value = 0;
    int butNo = 2;
    qint32 retNo = 0;
    if(!strcmp(oldDataString,newDataString) && unitNo == 2)
    {
        this->close();
        return;
    }
    //    if(entryNo == PM_INPUT_PERSISTENCE_TIME || entryNo == PM_INPUT_ACQ_TIME || entryNo == PM_INPUT_TRIGGER_DELAY_VALUE
    //            || entryNo == PM_INPUT_TRIGGER_PERTIMER || entryNo == PM_INPUT_TRIGGER_HOLDTIME)
    //    {
    //        retNo = timeSpecCompareFunc(UNIT_MS);
    //    }
    //    else
    retNo = amptdSpecCompareFunc(butNo);
    if (retNo == 1)
    {
        this->close();
        emit finishEntry(entryNo);
    }
    return;
}

void Pm_Dialog_Digitinput::on_amptBtnUnit3_clicked()
{
    //    qreal value = 0;
    int butNo = 3;
    qint32 retNo = 0;
    if(!strcmp(oldDataString,newDataString) && unitNo == 3)
    {
        this->close();
        return;
    }
    //    if(entryNo == PM_INPUT_PERSISTENCE_TIME || entryNo == PM_INPUT_ACQ_TIME || entryNo == PM_INPUT_TRIGGER_DELAY_VALUE
    //            || entryNo == PM_INPUT_TRIGGER_PERTIMER || entryNo == PM_INPUT_TRIGGER_HOLDTIME)
    //    {
    //        retNo = timeSpecCompareFunc(UNIT_US);
    //    }
    //    else
    retNo = amptdSpecCompareFunc(butNo);
    if (retNo == 1)
    {
        this->close();
        emit finishEntry(entryNo);
    }
    return;
}

void Pm_Dialog_Digitinput::on_amptBtnUnit4_clicked()
{
    //    qreal value = 0;
    int butNo = 4;
    qint32 retNo = 0;
    if(!strcmp(oldDataString,newDataString) && unitNo == 4)
    {
        this->close();
        return;
    }

    if(entryNo == PM_INPUT_AMP_MAX
            || entryNo == PM_INPUT_AMP_MIN
            || entryNo == PM_INPUT_AMP_OFFSET
            || entryNo == PM_INPUT_FORWATD_RELATIVE
            || entryNo == PM_INPUT_REVERSE_RELATIVE
            || entryNo == PM_INPUT_MEASURE_OFFSET
            || entryNo == PM_INPUT_FORWARD_UPPER
            || entryNo == PM_INPUT_FORWARD_LOWER
            || entryNo == PM_INPUT_REVERSE_UPPER
            || entryNo == PM_INPUT_REVERSE_LOWER
            || entryNo == PM_INPUT_CAL_AMPT)
    {
        retNo = amptdSpecCompareFunc(butNo);
    }
    else if(entryNo == PM_INPUT_FREQ_CHANNEL_NUM
            ||entryNo == PM_INPUT_RUNNING_AVERAGE
            ||entryNo == PM_INPUT_DUTY_CYCLE
            ||entryNo == PM_INPUT_TIME_INTERVAL
            ||entryNo == PM_INPUT_CAL_ARRAY)
    {
        retNo = enterFunc();
    }


    if (retNo == 1)
    {
        this->close();
        emit finishEntry(entryNo);
    }
    return;
}

void Pm_Dialog_Digitinput::on_amptBtnUnit5_clicked()
{
    //    qreal value = 0;
    int butNo = 5;
    qint32 retNo = 0;
    if(!strcmp(oldDataString,newDataString) && unitNo == 5)
    {
        this->close();
        return;
    }
    retNo = amptdSpecCompareFunc(butNo);
    if (retNo == 1)
    {
        this->close();
        emit finishEntry(entryNo);
    }
    return;
}

void Pm_Dialog_Digitinput::on_amptBtnUnit6_clicked()
{
    //    qreal value = 0;
    int butNo = 6;
    qint32 retNo = 0;
    if(!strcmp(oldDataString,newDataString) && unitNo == 6)
    {
        this->close();
        return;
    }
    retNo = amptdSpecCompareFunc(butNo);
    if (retNo == 1)
    {
        this->close();
        emit finishEntry(entryNo);
    }
    return;
}

void Pm_Dialog_Digitinput::on_amptBtnUnit7_clicked()
{
    //    qreal value = 0;
    int butNo = 7;
    qint32 retNo = 0;
    if(!strcmp(oldDataString,newDataString) && unitNo == 7)
    {
        this->close();
        return;
    }
    retNo = amptdSpecCompareFunc(butNo);
    if (retNo == 1)
    {
        this->close();
        emit finishEntry(entryNo);
    }
    return;
}

int Pm_Dialog_Digitinput::enterFunc()
{
    QString strValue;
    qreal dbValue = 0.;
    qint32 nValue = 0;

    strValue = newDataString;
    dbValue = strValue.toDouble();
    nValue = (qint32)dbValue;
    switch(entryNo)
    {
    case PM_INPUT_FREQ_CHANNEL_NUM:
        PmInterfaceObj->setChannelNumber(nValue);
        break;
    case PM_INPUT_RUNNING_AVERAGE:
        if(nValue < 1)
            nValue = 1;
        PmInterfaceObj->setAveragePoint(nValue);
        break;
    case PM_INPUT_DUTY_CYCLE:
        if(dbValue >PM_LIMIT_DUTY_MAX)
            dbValue = PM_LIMIT_DUTY_MAX;
        if(dbValue < PM_LIMIT_DUTY_MIN)
            dbValue = PM_LIMIT_DUTY_MIN;
        PmInterfaceObj->setDutyCycle(dbValue);
        break;
    case PM_INPUT_TIME_INTERVAL:
        PmInterfaceObj->setSweepTime(nValue);
        break;
    case PM_INPUT_CAL_ARRAY:
        PmInterfaceObj->setCalArray((qint16)nValue);
        break;
    default:
        break;
    }
    return 1;
}

void Pm_Dialog_Digitinput::clearAll()
{
    blNumberInput = false;
    blFirstIn = false;
    blDotInput = false;
    bLeftKey = false;
    bRightKey = false;
    highLightIndex = -1;
    memset(newDataString,0,sizeof(newDataString));
    strcpy(newDataString,"");
    ui->lblValue->setText(newDataString);
    return;
}
