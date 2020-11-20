#include "sa_dialog_digitinput.h"
#include "ui_sa_dialog_digitinput.h"
#include "define.h"
#include "sa_applicationcontrol.h"
#include <QKeyEvent>

SA_Dialog_DigitInput::SA_Dialog_DigitInput(controlInterface *interface, user_variable *puser_variable, qint32 index, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SA_Dialog_DigitInput)
{
    ui->setupUi(this);
    mControl = interface;
    globalUserVariable = puser_variable;
    mDialogIndex = index;
    mParent = parent;

    for(qint32 i = 0;i<19;i++){
        key_btn[i] = NULL;
    }

    move(mapToParent(QPoint(0,0)).x(),mapToParent(QPoint(0,0)).y());
    setProperty("status",qssMode[mControl->GetDisplayMode()]);
    InitKeyboard();
    initDisplay(index);
    setAttribute(Qt::WA_DeleteOnClose);
    //setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint | Qt::Dialog);
    this->setFocus();
}

SA_Dialog_DigitInput::~SA_Dialog_DigitInput()
{
    emit finishEntry(entryNo);
    delete ui;
}
/**
 * @brief  Init dialog display.
 * @param  index
 * @author Tony
 * @since 2018-12-20
*/
void SA_Dialog_DigitInput::initDisplay(qint32 index)
{
    if(index < 0)
    {
        index = mDialogIndex;
    }
    this->setFocus();
    ui->AmptUnit->show();
    ui->FREQuNIT->show();
	ui->amptBtnUnit1->show();
    ui->amptBtnUnit2->show();
    ui->amptBtnUnit3->show();
    ui->amptBtnUnit4->show();
    ui->amptBtnUnit5->show();
    ui->amptBtnUnit6->show();
    ui->amptBtnUnit7->show();
	ui->freqBtnUnit1->show();
    ui->freqBtnUnit2->show();
    ui->freqBtnUnit3->show();
    ui->freqBtnUnit4->show();
	
    char label[20];
    memset(label,0,sizeof(char)*20);

    entryNo = index;
    QString strGab,strUnit;
    QString strValue;
    qreal   value;
    qreal   tmpvalue;
    qint32 minusFlag = 0,pos,limitPoint,triggerMode;
    //Johnson 0630
    memset(newDataString, 0, sizeof(char) * 20);
    memset(oldDataString, 0, sizeof(char) * 20);


    //Johnson 0608
    blNumberInput = false;
    blDotInput = false;
    bLeftKey = false;
    bRightKey = false;
    blFirstIn = true;//Johnson 0703
    highLightIndex = -1;


    switch (index)
    {
#ifdef SAMPLE_LIMIT
    case SA_INPUT_UPPER_LIMIT_AMPT:
        //Johnson 200210
    #if 0
        value = mControl->getUpperLimit();
        strGab.sprintf("%.2f dBm", value);
        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->hide();
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->setText("dBm");
        ui->amptBtnUnit7->setGeometry(186,20,55,50);
        ui->lblTitle->setText("Upper Limit Amplitude");
        getInitialAmplitudeVal(value,index,newDataString);
    #else
        if(mControl->getCurrentMode() == SA_OCCUPIED_BW_MEASURE_MODE)
        {
            ui->freqBtnUnit1->setText("GHz");
            ui->freqBtnUnit2->setText("MHz");
            ui->freqBtnUnit3->setText("kHz");
            ui->freqBtnUnit4->setText("Hz");
            value = mControl->getUpperLimit();
            if (value < 0)
            {
                value *= -1;
                minusFlag = 1;
            }
            strGab = globalUserVariable->freqValueToQstring(value);
            unitNo = globalUserVariable->freqUnitFindProc(value);
            if(minusFlag)
                strGab = QString("-%1").arg(strGab);
            ui->lblTitle->setText("OBW Limit Freq");
            ui->AmptUnit->hide();
        }
        else
        {
            value = mControl->getUpperLimit();
            strGab.sprintf("%.2f dBm", value);
            ui->amptBtnUnit1->hide();
            ui->amptBtnUnit2->hide();
            ui->amptBtnUnit3->hide();
            ui->amptBtnUnit4->hide();
            ui->amptBtnUnit5->hide();
            ui->amptBtnUnit6->hide();
            ui->amptBtnUnit7->setText("dBm");
            ui->amptBtnUnit7->setGeometry(186,20,55,50);
            if(mControl->getCurrentMode() == SA_CHNLPOWER_MEASURE_MODE)
                ui->lblTitle->setText("Power Limit Amplitude");
            else if(mControl->getCurrentMode() == SA_ACP_MEASURE_MODE || mControl->getCurrentMode() == SA_MULTI_ACP_MODE)
                ui->lblTitle->setText("MAIN CH Limit");
            else
                ui->lblTitle->setText("Upper Limit Amplitude");
            getInitialAmplitudeVal(value,index,newDataString);
        }
    #endif
        break;
    case SA_INPUT_LOWER_LIMIT_AMPT:
    //Johnson 200210
    #if 0
        value = mControl->getLowerLimit();
        strGab.sprintf("%.2f dBm", value);
        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->hide();
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->setText("dBm");
        ui->amptBtnUnit7->setGeometry(186,20,55,50);
        ui->lblTitle->setText("Lower Limit Amplitude");
        getInitialAmplitudeVal(value,index,newDataString);
    #else
        value = mControl->getLowerLimit();
        if(mControl->getCurrentMode() == SA_CHNLPOWER_MEASURE_MODE)
            strGab.sprintf("%.2f dBm/Hz", value);
        else if(mControl->getCurrentMode() == SA_MULTI_ACP_MODE || mControl->getCurrentMode() == SA_ACP_MEASURE_MODE)
            strGab.sprintf("%.2f dBc",value);
        else
            strGab.sprintf("%.2f dBm", value);
        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->hide();
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        if(mControl->getCurrentMode() == SA_CHNLPOWER_MEASURE_MODE)
            ui->amptBtnUnit7->setText("Enter");
        else if(mControl->getCurrentMode() == SA_MULTI_ACP_MODE || mControl->getCurrentMode() == SA_ACP_MEASURE_MODE)
            ui->amptBtnUnit7->setText("dBc");
        else
            ui->amptBtnUnit7->setText("dBm");
        ui->amptBtnUnit7->setGeometry(186,20,55,50);
        if(mControl->getCurrentMode() == SA_CHNLPOWER_MEASURE_MODE)
            ui->lblTitle->setText("PSD Limit");
        else if(mControl->getCurrentMode() == SA_MULTI_ACP_MODE || mControl->getCurrentMode() == SA_ACP_MEASURE_MODE)
            ui->lblTitle->setText("ADJ CH Limit");
        else
            ui->lblTitle->setText("Lower Limit Amplitude");
        getInitialAmplitudeVal(value,index,newDataString);
    #endif
        break;
    case SA_INPUT_ATLDBC_LIMIT_AMP:
        value = mControl->getATLdBcLimit();
        if(mControl->getCurrentMode() == SA_MULTI_ACP_MODE || mControl->getCurrentMode() == SA_ACP_MEASURE_MODE)
            strGab.sprintf("%.2f dBc",value);
        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->hide();
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        if(mControl->getCurrentMode() == SA_MULTI_ACP_MODE || mControl->getCurrentMode() == SA_ACP_MEASURE_MODE)
            ui->amptBtnUnit7->setText("dBc");
        ui->amptBtnUnit7->setGeometry(186,20,55,50);
        if(mControl->getCurrentMode() == SA_MULTI_ACP_MODE || mControl->getCurrentMode() == SA_ACP_MEASURE_MODE)
            ui->lblTitle->setText("ALT CH Limit");
        getInitialAmplitudeVal(value,index,newDataString);
        break;
#endif
    case SA_INPUT_SPUREM_LIMIT_START:
        value = mControl->getSpurEMStartLimit();
        strGab.sprintf("%.2f dBm", value);
        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->hide();
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->setText("dBm");
        ui->amptBtnUnit7->setGeometry(186,20,55,50);
        ui->lblTitle->setText("Spurious Start Limit");
        getInitialAmplitudeVal(value,index,newDataString);
        break;
    case SA_INPUT_SPUREM_LIMIT_STOP:
        value = mControl->getSpurEMStopLimit();
        strGab.sprintf("%.2f dBm", value);
        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->hide();
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->setText("dBm");
        ui->amptBtnUnit7->setGeometry(186,20,55,50);
        ui->lblTitle->setText("Spurious Stop Limit");
        getInitialAmplitudeVal(value,index,newDataString);
        break;
    case SA_INPUT_SPUREM_PEAK_DEFINITION:
        value = mControl->getSpurEMpeakDefi();
        strGab.sprintf("%.2f dB", value);
        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->hide();
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->setText("dB");
        ui->amptBtnUnit7->setGeometry(186,20,55,50);
        ui->lblTitle->setText("Spurious Peak Definition");
        getInitialAmplitudeVal(value,index,newDataString);
        break;
    case SA_INPUT_SPUREM_PEAK_THRESHOLD:
        value = mControl->getSpurEMpeakThreshold();
        strGab.sprintf("%.2f dBm", value);
        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->hide();
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->setText("dBm");
        ui->amptBtnUnit7->setGeometry(186,20,55,50);
        ui->lblTitle->setText("Spurious Peak Threshold");
        getInitialAmplitudeVal(value,index,newDataString);
        break;
    case SA_INPUT_SPUREM_ATTEN:
        value = mControl->getSpurEMAtten();
        strGab = QString::number(value,'d',0)+" dB";
        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->hide();
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->setText("dB");
        ui->amptBtnUnit7->setGeometry(186,20,55,50);
        ui->lblTitle->setText("Spurious Atten");
        getInitialAmplitudeVal(value,index,newDataString);
        break;
    case SA_INPUT_SPUREM_SWEEP_TIME:
        ui->freqBtnUnit4->setText("ns");
        ui->freqBtnUnit3->setText("us");
        ui->freqBtnUnit2->setText("ms");
        ui->freqBtnUnit1->setText("s");
        ui->AmptUnit->hide();
        value = mControl->getSpurEMSweepTime();
        unitNo = globalUserVariable->getTimeUnit(value);
        strGab = globalUserVariable->TimeTransformToQstring(value);

        ui->lblTitle->setText("Spurious Sweep Time");
        break;
    case SA_INPUT_SPUREM_FREQ_START:
        ui->freqBtnUnit1->setText("GHz");
        ui->freqBtnUnit2->setText("MHz");
        ui->freqBtnUnit3->setText("kHz");
        ui->freqBtnUnit4->setText("Hz");
        value = mControl->getSpurEMstartFreq();
        if (value < 0)
        {
            value *= -1;
            minusFlag = 1;
        }
        strGab = globalUserVariable->freqValueToQstring(value);
        unitNo = globalUserVariable->freqUnitFindProc(value);
        if(minusFlag)
            strGab = QString("-%1").arg(strGab);
        ui->lblTitle->setText("Spurious Start Freq");
        ui->AmptUnit->hide();
        break;
    case SA_INPUT_SPUREM_FREQ_STOP:
        ui->freqBtnUnit1->setText("GHz");
        ui->freqBtnUnit2->setText("MHz");
        ui->freqBtnUnit3->setText("kHz");
        ui->freqBtnUnit4->setText("Hz");
        value = mControl->getSpurEMstopFreq();
        if (value < 0)
        {
            value *= -1;
            minusFlag = 1;
        }
        strGab = globalUserVariable->freqValueToQstring(value);
        unitNo = globalUserVariable->freqUnitFindProc(value);
        if(minusFlag)
            strGab = QString("-%1").arg(strGab);
        ui->lblTitle->setText("Spurious Stop Freq");
        ui->AmptUnit->hide();
        break;
    case SA_INPUT_CH_STEP:
        value = mControl->getChannelNumStep();
        strGab= QString::number(value);
        ui->lblTitle->setText("Channel Step");
        ui->freqBtnUnit4->setText("Enter");
        ui->freqBtnUnit1->hide();
        ui->freqBtnUnit2->hide();
        ui->freqBtnUnit3->hide();
        ui->AmptUnit->hide();
        break;
    case SA_INPUT_SPUREM_SPUR_INDEX:
        value = mControl->getSpurEMCurSpurIndex() + 1;
        strGab= QString::number(value);
        ui->lblTitle->setText("Current Spur");
        ui->freqBtnUnit4->setText("Enter");
        ui->freqBtnUnit1->hide();
        ui->freqBtnUnit2->hide();
        ui->freqBtnUnit3->hide();
        ui->AmptUnit->hide();
        break;
    case  SA_INPUT_SPUREM_RANGE_INDEX:
        value = mControl->getSpurEMCurRangeIndex() + 1;
        strGab= QString::number(value);
        ui->lblTitle->setText("Current Range");
        ui->freqBtnUnit4->setText("Enter");
        ui->freqBtnUnit1->hide();
        ui->freqBtnUnit2->hide();
        ui->freqBtnUnit3->hide();
        ui->AmptUnit->hide();
        break;
    case SA_INPUT_TRIGGER_LEVEL:
        triggerMode = mControl->getTriggerMode();
        if(SA_TRIGGER_EXTERNAL == triggerMode)
        {
           unitNo = SA_VOLT;
        }else
        {
            unitNo = SA_DBM;
        }
        value = mControl->getTriggerLevel(triggerMode);
        switch (unitNo)
        {
        case SA_DBM:
            ui->amptBtnUnit1->hide();
            ui->amptBtnUnit2->hide();
            ui->amptBtnUnit3->hide();
            ui->amptBtnUnit4->hide();
            ui->amptBtnUnit5->hide();
            ui->amptBtnUnit6->hide();
            ui->amptBtnUnit7->setGeometry(186,20,55,50);
            strGab.sprintf("%.2f dBm",value);
            ui->amptBtnUnit7->setText("dBm");
            getInitialAmplitudeVal(value,index,newDataString,unitNo);
            break;
        case SA_VOLT:
            ui->amptBtnUnit1->hide();
            ui->amptBtnUnit2->hide();
            ui->amptBtnUnit3->hide();
            ui->amptBtnUnit4->hide();
            ui->amptBtnUnit5->setText("V");
            ui->amptBtnUnit6->setText("mV");
            ui->amptBtnUnit7->setText("uV");
            ui->amptBtnUnit5->setGeometry(6,20,75,50);
            ui->amptBtnUnit6->setGeometry(85,20,75,50);
            ui->amptBtnUnit7->setGeometry(166,20,75,50);
            mControl->globalUserVariable-> dbmToVoltCalculatorAndDisplayFunc(label, value);
            // Label을 String으로 변환
            strGab = QString(label);
            getInitialAmplitudeVal(value,index,newDataString,unitNo);
            break;
        }
        ui->lblTitle->setText("Trigger Level ");
        break;
    case SA_INPUT_TRIGGER_PERTIMER:
        ui->freqBtnUnit4->setText("ns");
        ui->freqBtnUnit3->setText("us");
        ui->freqBtnUnit2->setText("ms");
        ui->freqBtnUnit1->setText("s");
        ui->AmptUnit->hide();
        value = mControl->getTriggerPerTimer();
        unitNo = globalUserVariable->getTimeUnit(value);
        strGab = globalUserVariable->TimeTransformToQstring(value);

        ui->lblTitle->setText("Trigger Periodic Timer");
        break;
    case SA_INPUT_TRIGGER_DELAY_VALUE:
        ui->freqBtnUnit4->setText("ns");
        ui->freqBtnUnit3->setText("us");
        ui->freqBtnUnit2->setText("ms");
        ui->freqBtnUnit1->setText("s");
        ui->AmptUnit->hide();
        value = mControl->getTriggerDelayValue();
        unitNo = globalUserVariable->getTimeUnit(value);
        strGab = globalUserVariable->TimeTransformToQstring(value);

        ui->lblTitle->setText("Trigger Delay Time");
        break;
    case SA_INPUT_DOORCTRL_TRIGDELAY:
        ui->freqBtnUnit4->setText("ns");
        ui->freqBtnUnit3->setText("us");
        ui->freqBtnUnit2->setText("ms");
        ui->freqBtnUnit1->setText("s");
        ui->AmptUnit->hide();
        value = mControl->getEdgeTrigDely();
        unitNo = globalUserVariable->getTimeUnit(value);
        strGab = globalUserVariable->TimeTransformToQstring(value);

        ui->lblTitle->setText("Gate Delay");
        break;
    case SA_INPUT_DOORCTRL_DOORWID:
        ui->freqBtnUnit4->setText("ns");
        ui->freqBtnUnit3->setText("us");
        ui->freqBtnUnit2->setText("ms");
        ui->freqBtnUnit1->setText("s");
        ui->AmptUnit->hide();
        value = mControl->getEdgeTrigDoorWidth();
        unitNo = globalUserVariable->getTimeUnit(value);
        strGab = globalUserVariable->TimeTransformToQstring(value);

        ui->lblTitle->setText("Gate Length");
        break;
    case SA_INPUT_DOORCTRL_PRVTTIME:
        ui->freqBtnUnit4->setText("ns");
        ui->freqBtnUnit3->setText("us");
        ui->freqBtnUnit2->setText("ms");
        ui->freqBtnUnit1->setText("s");
        ui->AmptUnit->hide();
        value = mControl->getEdgeTrigPreventTimes();
        unitNo = globalUserVariable->getTimeUnit(value);
        strGab = globalUserVariable->TimeTransformToQstring(value);

        ui->lblTitle->setText("Prevent Time");
        break;
    case SA_INPUT_DOORCTRL_PERI_PERIOD:
        ui->freqBtnUnit4->setText("ns");
        ui->freqBtnUnit3->setText("us");
        ui->freqBtnUnit2->setText("ms");
        ui->freqBtnUnit1->setText("s");
        ui->AmptUnit->hide();
        value = mControl->getPeriodTrigPeriod();
        unitNo = globalUserVariable->getTimeUnit(value);
        strGab = globalUserVariable->TimeTransformToQstring(value);

        ui->lblTitle->setText("Period Time");
        break;
    case SA_INPUT_DOORCTRL_PERI_SYNSRCDELAY:
        ui->freqBtnUnit4->setText("ns");
        ui->freqBtnUnit3->setText("us");
        ui->freqBtnUnit2->setText("ms");
        ui->freqBtnUnit1->setText("s");
        ui->AmptUnit->hide();
        value = mControl->getPeriodTrigSrcDelay();
        unitNo = globalUserVariable->getTimeUnit(value);
        strGab = globalUserVariable->TimeTransformToQstring(value);

        ui->lblTitle->setText("Syn Source Delay");
        break;
    case SA_INPUT_DOORCTRL_PERI_SRCPRVTTIME:
        ui->freqBtnUnit4->setText("ns");
        ui->freqBtnUnit3->setText("us");
        ui->freqBtnUnit2->setText("ms");
        ui->freqBtnUnit1->setText("s");
        ui->AmptUnit->hide();
        value = mControl->getPeriodTrigPreventTimes();
        unitNo = globalUserVariable->getTimeUnit(value);
        strGab = globalUserVariable->TimeTransformToQstring(value);

        ui->lblTitle->setText("SynSource Prevent Time");
        break;
    case SA_INPUT_DOORCTRL_GATEVIEW_STARTTIME:
        ui->freqBtnUnit4->setText("ns");
        ui->freqBtnUnit3->setText("us");
        ui->freqBtnUnit2->setText("ms");
        ui->freqBtnUnit1->setText("s");
        ui->AmptUnit->hide();
        value = mControl->getGateViewStartTime();
        unitNo = globalUserVariable->getTimeUnit(value);
        strGab = globalUserVariable->TimeTransformToQstring(value);

        ui->lblTitle->setText("Gate Start Time");
        break;
    case SA_INPUT_DOORCTRL_TRIGGERLEVEL:
        value = mControl->getRFBurstTrigLevel();

        unitNo = SA_DBM;

        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->hide();
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->setGeometry(186,20,55,50);
        strGab.sprintf("%.2f dBm",value);
        ui->amptBtnUnit7->setText("dBm");
        getInitialAmplitudeVal(value,index,newDataString,unitNo);

        ui->lblTitle->setText("Trigger Level ");
        break;
    case SA_INPUT_LIMIT_FREQ:
        limitPoint = mControl->getLimitCurPointIndex(mControl->getLimitSelect())-1;
        value = mControl->getLimitFreq(mControl->getLimitSelect(),limitPoint);
//        tmpvalue = mControl->getFreqOffset();
//        value += tmpvalue;
        if (value < 0)
        {
            value *= -1;
            minusFlag = 1;
        }
        strGab = globalUserVariable->freqValueToQstring(value);
        unitNo = globalUserVariable->freqUnitFindProc(value);
        if(minusFlag)
            strGab = QString("-%1").arg(strGab);
        ui->freqBtnUnit1->setText("GHz");
        ui->freqBtnUnit2->setText("MHz");
        ui->freqBtnUnit3->setText("kHz");
        ui->freqBtnUnit4->setText("Hz");
        ui->lblTitle->setText("Limit Frequency");
        ui->AmptUnit->hide();
        break;
    case SA_INPUT_LIMIT_AMPT:
        limitPoint = mControl->getLimitCurPointIndex(mControl->getLimitSelect())-1;
        value = mControl->getLimitAmpt(mControl->getLimitSelect(),limitPoint);
        strGab.sprintf("%.2f dBm", value);
        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->hide();
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->setText("dBm");
        ui->amptBtnUnit7->setGeometry(186,20,55,50);
        ui->lblTitle->setText("Limit Amplitude");
        getInitialAmplitudeVal(value,index,newDataString);
        break;
    case SA_INPUT_FREQ_CENTER:
        ui->freqBtnUnit1->setText("GHz");
        ui->freqBtnUnit2->setText("MHz");
        ui->freqBtnUnit3->setText("kHz");
        ui->freqBtnUnit4->setText("Hz");
        value = mControl->getCenterFreq();
//        tmpvalue = mControl->getFreqOffset();
//        value += tmpvalue;
        if (value < 0)
        {
            value *= -1;
            minusFlag = 1;
        }
        strGab = globalUserVariable->freqValueToQstring(value);
        unitNo = globalUserVariable->freqUnitFindProc(value);
        if(minusFlag)
            strGab = QString("-%1").arg(strGab);
        ui->lblTitle->setText("Center Frequency");
        ui->AmptUnit->hide();
        break;
    case SA_INPUT_SEM_CHBW:
        ui->freqBtnUnit1->setText("GHz");
        ui->freqBtnUnit2->setText("MHz");
        ui->freqBtnUnit3->setText("kHz");
        ui->freqBtnUnit4->setText("Hz");
        value = mControl->getSpecEMRefChBw();
        if (value < 0)
        {
            value *= -1;
            minusFlag = 1;
        }
        strGab = globalUserVariable->freqValueToQstring(value);
        unitNo = globalUserVariable->freqUnitFindProc(value);
        if(minusFlag)
            strGab = QString("-%1").arg(strGab);
        ui->lblTitle->setText("SEM REF CH BW");
        ui->AmptUnit->hide();
        break;
    case SA_INPUT_SEM_BSPOWER:

        value = mControl->getSpecEMBsPower();

        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->hide();
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->setGeometry(186,20,55,50);

        strGab.sprintf("%.2f dBm",value);
        ui->amptBtnUnit7->setText("dBm");
        getInitialAmplitudeVal(value,index,newDataString,unitNo);

        ui->lblTitle->setText("BS Power");
        break;
    case SA_INPUT_FREQ_START:
        ui->freqBtnUnit1->setText("GHz");
        ui->freqBtnUnit2->setText("MHz");
        ui->freqBtnUnit3->setText("kHz");
        ui->freqBtnUnit4->setText("Hz");
        value = mControl->getStartFreq();
        if (value < 0)
        {
            value *= -1;
            minusFlag = 1;
        }
        strGab = globalUserVariable->freqValueToQstring(value);
        unitNo = globalUserVariable->freqUnitFindProc(value);
        if(minusFlag)
            strGab = QString("-%1").arg(strGab);
        ui->lblTitle->setText("Start Frequency");
        ui->AmptUnit->hide();
        break;
    case SA_INPUT_FREQ_OFFSET:
        ui->freqBtnUnit1->setText("GHz");
        ui->freqBtnUnit2->setText("MHz");
        ui->freqBtnUnit3->setText("kHz");
        ui->freqBtnUnit4->setText("Hz");
        value = mControl->getFreqOffset();
        if (value < 0)
        {
            value *= -1;
            minusFlag = 1;
        }
        strGab = globalUserVariable->freqValueToQstring(value);
        if(minusFlag)
            strGab = QString("-%1").arg(strGab);
        unitNo = globalUserVariable->freqUnitFindProc(value);
        ui->lblTitle->setText("Frequency Offset");
        ui->AmptUnit->hide();
        break;
    case SA_INPUT_FREQ_STOP:
        ui->freqBtnUnit1->setText("GHz");
        ui->freqBtnUnit2->setText("MHz");
        ui->freqBtnUnit3->setText("kHz");
        ui->freqBtnUnit4->setText("Hz");
        value = mControl->getStopFreq();
        if (value < 0)
        {
            value *= -1;
            minusFlag = 1;
        }
        strGab = globalUserVariable->freqValueToQstring(value);
        unitNo = globalUserVariable->freqUnitFindProc(value);
        if(minusFlag)
            strGab = QString("-%1").arg(strGab);
        ui->lblTitle->setText("Stop Frequency");
        ui->AmptUnit->hide();
        break;
    case SA_INPUT_FREQ_CF:
        ui->freqBtnUnit1->setText("GHz");
        ui->freqBtnUnit2->setText("MHz");
        ui->freqBtnUnit3->setText("kHz");
        ui->freqBtnUnit4->setText("Hz");
        value = mControl->getCFFreq();
        strGab = globalUserVariable->freqValueToQstring(value);
        unitNo = globalUserVariable->freqUnitFindProc(value);
        ui->lblTitle->setText("Frequency Step");
        ui->AmptUnit->hide();
        break;
    case SA_INPUT_FREQ_SPAN:
        ui->freqBtnUnit1->setText("GHz");
        ui->freqBtnUnit2->setText("MHz");
        ui->freqBtnUnit3->setText("kHz");
        ui->freqBtnUnit4->setText("Hz");
        value = mControl->getSpan();
        strGab = globalUserVariable->freqValueToQstring(value);
        unitNo = globalUserVariable->freqUnitFindProc(value);
        ui->lblTitle->setText("Span");
        ui->AmptUnit->hide();
        break;
        //SA_BW setup
    case SA_INPUT_MANUAL_RBW:
        ui->freqBtnUnit1->setText("GHz");
        ui->freqBtnUnit2->setText("MHz");
        ui->freqBtnUnit3->setText("kHz");
        ui->freqBtnUnit4->setText("Hz");
        value = mControl->getRbwValue();
        strGab = globalUserVariable->freqValueToQstring(value);
        unitNo = globalUserVariable->freqUnitFindProc(value);
        ui->lblTitle->setText("RBW");
        ui->AmptUnit->hide();
        break ;
    case SA_INPUT_MANUAL_VBW:
        ui->freqBtnUnit1->setText("GHz");
        ui->freqBtnUnit2->setText("MHz");
        ui->freqBtnUnit3->setText("kHz");
        ui->freqBtnUnit4->setText("Hz");
        value = mControl->getVbwValue();
        strGab = globalUserVariable->freqValueToQstring(value);
        unitNo = globalUserVariable->freqUnitFindProc(value);
        ui->lblTitle->setText("VBW");
        ui->AmptUnit->hide();
        break ;
    case SA_INPUT_PERSISTENCE_TIME:

        //          mtemptime = globalUserVariable->gPersistenceTime;

        //          strGab = QString::number(globalUserVariable->gPersistenceTime, 'd',0);
        //          pos = mControl->globalUserVariable->notZeroPositionFindFunc(strGab);
        //          strG = mControl->globalUserVariable->timeDotNumberDisplayFormatFixFunc(globalUserVariable->gPersistenceTime, unitNo, pos );

        //          getInitialTimeVal(globalUserVariable->gPersistenceTime,pos);
        ui->freqBtnUnit4->setText("ns");
        ui->freqBtnUnit3->setText("us");
        ui->freqBtnUnit2->setText("ms");
        ui->freqBtnUnit1->setText("s");
        ui->lblTitle->setText("Persistence Time");
        ui->AmptUnit->hide();
        break;
    case SA_INPUT_HIGHEST_DENSITY:
        ui->freqBtnUnit1->hide();
        ui->freqBtnUnit2->hide();
        ui->freqBtnUnit3->hide();
        ui->freqBtnUnit4->setText("Enter");

        //        strValue.sprintf("%d", globalUserVariable->gHighestDensity);
        //        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());

        //        if(strlen(newDataString)) blNumberInput = true;
        //        else blNumberInput = false;

        //        if(strchr(newDataString,'.')) blDotInput = true;
        //        else blDotInput = false;

        //        strValue = QString::number(globalUserVariable->gHighestDensity, 'd',0)+" %";

        break;
    case SA_INPUT_LOWEST_DENSITY:
        ui->freqBtnUnit1->hide();
        ui->freqBtnUnit2->hide();
        ui->freqBtnUnit3->hide();
        ui->freqBtnUnit4->setText("Enter");

        //        strValue.sprintf("%d", globalUserVariable->gLowestDensity);
        //        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());

        //        if(strlen(newDataString)) blNumberInput = true;
        //        else blNumberInput = false;

        //        if(strchr(newDataString,'.')) blDotInput = true;
        //        else blDotInput = false;

        //        strValue = QString::number(globalUserVariable->gLowestDensity, 'd',0)+" %";
        break;
    case SA_INPUT_AVERAGE_COUNT:
        //      strValue.sprintf("%d", globalUserVariable->gAverageCount[globalUserVariable->gTraceSelect]);
        value = globalUserVariable->gAverageCount[globalUserVariable->gTraceSelect];
        strGab= QString::number(value);
        //      //Johnson 0726
        //      qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());
        //      if(strlen(newDataString)) blNumberInput = true;
        //      else blNumberInput = false;

        //      if(strchr(newDataString,'.')) blDotInput = true;
        //      else blDotInput = false;

        ui->lblTitle->setText("Average Count");
        ui->freqBtnUnit4->setText("Enter");
        ui->freqBtnUnit1->hide();
        ui->freqBtnUnit2->hide();
        ui->freqBtnUnit3->hide();
        ui->AmptUnit->hide();
        break;
    case SA_INPUT_CURVE:
        ui->freqBtnUnit1->hide();
        ui->freqBtnUnit2->hide();
        ui->freqBtnUnit3->hide();
        ui->freqBtnUnit4->setText("Enter");

        //        //value = mControl;
        //        strGab.sprintf("%d", value);
        //        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());

        //        if(strlen(newDataString)) blNumberInput = true;
        //        else blNumberInput = false;

        //        if(strchr(newDataString,'.'))
        //            blDotInput = true;
        //        else
        //            blDotInput = false;
        //        strValue = QString::number(globalUserVariable->gCurve, 'd',0)+" %";
        break;

    case SA_INPUT_MARKER_EDIT:
        if(!globalUserVariable->gSpanMode)
        {
            ui->freqBtnUnit1->setText("GHz");
            ui->freqBtnUnit2->setText("MHz");
            ui->freqBtnUnit3->setText("kHz");
            ui->freqBtnUnit4->setText("Hz");
            value = mControl->getMarkerRefFreq();
            if(value < 0)
            {
                minusFlag = 1;
                value *= -1;
            }
            strGab = globalUserVariable->freqValueToQstring(value);
            unitNo = globalUserVariable->freqUnitFindProc(value);
        }else
        {
            ui->freqBtnUnit4->setText("ns");
            ui->freqBtnUnit3->setText("us");
            ui->freqBtnUnit2->setText("ms");
            ui->freqBtnUnit1->setText("s");
            value = mControl->getMarkerRefTime();
            if(value < 0)
            {
                minusFlag = 1;
                value *= -1;
            }
            strGab = globalUserVariable->TimeTransformToQstring(value);
            unitNo = globalUserVariable->getTimeUnit(value);
        }


        if(minusFlag) strGab = "-" + strGab;
        ui->lblTitle->setText("Normal Marker Edit");
        ui->AmptUnit->hide();
        break;
    case SA_INPUT_DELTA_MARKER_EDIT:
        if(!globalUserVariable->gSpanMode)
        {
            ui->freqBtnUnit1->setText("GHz");
            ui->freqBtnUnit2->setText("MHz");
            ui->freqBtnUnit3->setText("kHz");
            ui->freqBtnUnit4->setText("Hz");
            value = mControl->getMarkerDeltaFreq();
            tmpvalue = mControl->getMarkerRefFreq();
            value -= tmpvalue;
            if (value < 0)
            {
                value *= -1;
                minusFlag = 1;
            }

            strGab = globalUserVariable->freqValueToQstring(value);
            unitNo = globalUserVariable->freqUnitFindProc(value);
        }else
        {
            ui->freqBtnUnit4->setText("ns");
            ui->freqBtnUnit3->setText("us");
            ui->freqBtnUnit2->setText("ms");
            ui->freqBtnUnit1->setText("s");
            value = mControl->getMarkerDeltaTime();
            tmpvalue = mControl->getMarkerRefTime();
            value -= tmpvalue;
            if (value < 0)
            {
                value *= -1;
                minusFlag = 1;
            }
            strGab = globalUserVariable->TimeTransformToQstring(value);
            unitNo = globalUserVariable->getTimeUnit(value);
        }

        ui->lblTitle->setText("Delta Marker Edit");
        ui->AmptUnit->hide();
        if (minusFlag == 1)
            strGab   = QString("-%1").arg(strGab);

        break;


    case SA_INPUT_REF_LEVEL:
        unitNo = mControl->getAmpUnit();
        value = mControl->getRefLevel();
        switch (unitNo)
        {
        case SA_DBM:
        case SA_DBV:
        case SA_DBMV:
        case SA_DBUV:
            ui->amptBtnUnit1->hide();
            ui->amptBtnUnit2->hide();
            ui->amptBtnUnit3->hide();
            ui->amptBtnUnit4->hide();
            ui->amptBtnUnit5->hide();
            ui->amptBtnUnit6->hide();
            ui->amptBtnUnit7->setGeometry(186,20,55,50);
            if (unitNo == SA_DBM)
            {
                strGab.sprintf("%.2f dBm",value);
                ui->amptBtnUnit7->setText("dBm");
                getInitialAmplitudeVal(value,index,newDataString,unitNo);
            }
            else if  (unitNo == SA_DBV)
            {
                strGab.sprintf("%.2f dBV", value + dBVFix);
                ui->amptBtnUnit7->setText("dBV");
                getInitialAmplitudeVal(value + dBVFix,index,newDataString,unitNo);
            }
            else if  (unitNo == SA_DBMV)
            {
                strGab.sprintf("%.2f dBmV", value + dBmVFix);
                ui->amptBtnUnit7->setText("dBmV");
                getInitialAmplitudeVal(value + dBmVFix,index,newDataString,unitNo);
            } else if  (unitNo == SA_DBUV)
            {
                strGab.sprintf("%.2f dBuV", value + dBuVFix);
                ui->amptBtnUnit7->setText("dBuV");
                getInitialAmplitudeVal(value + dBuVFix,index,newDataString,unitNo);
            }
            break;
        case SA_VOLT:
            ui->amptBtnUnit1->hide();
            ui->amptBtnUnit2->hide();
            ui->amptBtnUnit3->hide();
            ui->amptBtnUnit4->hide();
            ui->amptBtnUnit5->setText("V");
            ui->amptBtnUnit6->setText("mV");
            ui->amptBtnUnit7->setText("uV");
            ui->amptBtnUnit5->setGeometry(6,20,75,50);
            ui->amptBtnUnit6->setGeometry(85,20,75,50);
            ui->amptBtnUnit7->setGeometry(166,20,75,50);
            mControl->globalUserVariable-> dbmToVoltCalculatorAndDisplayFunc(label, value);
            // Label을 String으로 변환
            strGab = QString(label);
            getInitialAmplitudeVal(value,index,newDataString,unitNo);
            break;
        case SA_WATTS:
            mControl->globalUserVariable-> dbmToWattsCalculatorAndDisplayFunc(label, value);
            // Label을 String으로 변환
            strGab = QString(label);
            getInitialAmplitudeVal(value,index,newDataString,unitNo);
            break;
        }
        ui->lblTitle->setText("Ref Level ");
        break;
    case SA_LIMIT_EDGE:
        value = mControl->getLimitEdgeValue();
        strGab.sprintf("%.2f dB", value);
        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->hide();
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->setText("dB");
        ui->amptBtnUnit7->setGeometry(186,20,55,50);
        ui->lblTitle->setText("Limit Edge");
        getInitialAmplitudeVal(value,index,newDataString);
        break;
    case SA_INPUT_REF_OFFSET:
        value = mControl->getRefOffset();
        strGab.sprintf("%.2f dB", value);
        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->hide();
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->setText("dB");
        ui->amptBtnUnit7->setGeometry(186,20,55,50);
        ui->lblTitle->setText("Ref Offset ");
        getInitialAmplitudeVal(value,index,newDataString);
        break;

    case SA_INPUT_POWERSENSOR_EXT_OFFSET:
        value = 0.;
        strGab.sprintf("%.2f dB", value);
        //        strValue.sprintf("%.2f dB", (qreal) globalUserVariable->gPowersensorExtOffset);
        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->hide();
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->setText("dB");
        ui->amptBtnUnit7->setGeometry(186,20,55,50);
        ui->lblTitle->setText("Ref Offset ");
        getInitialAmplitudeVal(value,index,newDataString);
        break;
    case SA_INPUT_ATTEN:
        ui->lblTitle->setText("Attenuation");
        //Johnson Add 0730
        value = mControl->getAttenValue();
        if(mControl->getPreampStatus() == SA_ON)
        {
            if(value >= 30.)
                value = 30.;
        }

//        strGab = QString::number(value,'d',2);
        strGab = QString::number(value,'d',0)+" dB";
        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->hide();
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->setText("dB");
        ui->amptBtnUnit7->setGeometry(186,20,55,50);
        getInitialAmplitudeVal(value,index,newDataString);
        break;
    case SA_INPUT_SCALEDIV:
        value = mControl->getScaleDiv();
        strGab.sprintf("%.2f dB",value);

        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->hide();
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->setText("dB");
        ui->amptBtnUnit7->setGeometry(186,20,55,50);
        ui->lblTitle->setText("Scale Division");
        getInitialAmplitudeVal(value,index,newDataString);
        break;
    case SA_INPUT_XDB://Johnson 0927
        value = mControl->getXdB_OccupiedBW();
        strGab.sprintf("%.2f dB",value);

        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->hide();
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->setText("dB");
        ui->amptBtnUnit7->setGeometry(186,20,55,50);
        ui->lblTitle->setText("XdB");
        getInitialAmplitudeVal(value,index,newDataString);
        break;
    case SA_INPUT_MULTIACP_HIGHESTCH_FREQ:
        ui->freqBtnUnit1->setText("GHz");
        ui->freqBtnUnit2->setText("MHz");
        ui->freqBtnUnit3->setText("kHz");
        ui->freqBtnUnit4->setText("Hz");

        value = mControl->getMulACP_HighestCHFreq();

        if (value < 0)
        {
            value *= -1;
            minusFlag = 1;
        }
        strGab = globalUserVariable->freqValueToQstring(value);
        unitNo = globalUserVariable->freqUnitFindProc(value);
        if(minusFlag)
            strGab = QString("-%1").arg(strGab);
        ui->lblTitle->setText("Highest CH FREQ");
        ui->AmptUnit->hide();
        break;
    case SA_INPUT_MULTIACP_LOWESTCH_FREQ:
        ui->freqBtnUnit1->setText("GHz");
        ui->freqBtnUnit2->setText("MHz");
        ui->freqBtnUnit3->setText("kHz");
        ui->freqBtnUnit4->setText("Hz");

        value = mControl->getMulACP_LowestCHFreq();

        if (value < 0)
        {
            value *= -1;
            minusFlag = 1;
        }
        strGab = globalUserVariable->freqValueToQstring(value);
        unitNo = globalUserVariable->freqUnitFindProc(value);
        if(minusFlag)
            strGab = QString("-%1").arg(strGab);
        ui->lblTitle->setText("Lowest CH FREQ");
        ui->AmptUnit->hide();
        break;
    case SA_INPUT_MULTIACP_CHNLSPACING:
        ui->freqBtnUnit1->setText("GHz");
        ui->freqBtnUnit2->setText("MHz");
        ui->freqBtnUnit3->setText("kHz");
        ui->freqBtnUnit4->setText("Hz");

        value = mControl->getMulACP_ChnSpacing();

        if (value < 0)
        {
            value *= -1;
            minusFlag = 1;
        }
        strGab = globalUserVariable->freqValueToQstring(value);
        unitNo = globalUserVariable->freqUnitFindProc(value);
        if(minusFlag)
            strGab = QString("-%1").arg(strGab);
        ui->lblTitle->setText("Multi-ACP CH SPACING");
        ui->AmptUnit->hide();
        break;
    case SA_INPUT_MULTIACP_MAININTEG_BW:
        ui->freqBtnUnit1->setText("GHz");
        ui->freqBtnUnit2->setText("MHz");
        ui->freqBtnUnit3->setText("kHz");
        ui->freqBtnUnit4->setText("Hz");

        value = mControl->getMulACP_MainIntegBW();

        if (value < 0)
        {
            value *= -1;
            minusFlag = 1;
        }
        strGab = globalUserVariable->freqValueToQstring(value);
        unitNo = globalUserVariable->freqUnitFindProc(value);
        if(minusFlag)
            strGab = QString("-%1").arg(strGab);
        ui->lblTitle->setText("MAIN INTEG BW");
        ui->AmptUnit->hide();
        break;
    case SA_INPUT_MULTIACP_ADJINTEG_BW:
        ui->freqBtnUnit1->setText("GHz");
        ui->freqBtnUnit2->setText("MHz");
        ui->freqBtnUnit3->setText("kHz");
        ui->freqBtnUnit4->setText("Hz");

        value = mControl->getMulACP_ADJIntegBW();

        if (value < 0)
        {
            value *= -1;
            minusFlag = 1;
        }
        strGab = globalUserVariable->freqValueToQstring(value);
        unitNo = globalUserVariable->freqUnitFindProc(value);
        if(minusFlag)
            strGab = QString("-%1").arg(strGab);
        ui->lblTitle->setText("ADJ INTEG BW");
        ui->AmptUnit->hide();
        break;
    case SA_INPUT_MULTIACP_ALTINTEG_BW:
        ui->freqBtnUnit1->setText("GHz");
        ui->freqBtnUnit2->setText("MHz");
        ui->freqBtnUnit3->setText("kHz");
        ui->freqBtnUnit4->setText("Hz");

        value = mControl->getMulACP_ALTIntegBW();

        if (value < 0)
        {
            value *= -1;
            minusFlag = 1;
        }
        strGab = globalUserVariable->freqValueToQstring(value);
        unitNo = globalUserVariable->freqUnitFindProc(value);
        if(minusFlag)
            strGab = QString("-%1").arg(strGab);
        ui->lblTitle->setText("ALT INTEG BW");
        ui->AmptUnit->hide();
        break;
    case SA_INPUT_CHANNEL_BANDWIDTH:
        ui->freqBtnUnit1->setText("GHz");
        ui->freqBtnUnit2->setText("MHz");
        ui->freqBtnUnit3->setText("kHz");
        ui->freqBtnUnit4->setText("Hz");

        if(SA_CHNLPOWER_MEASURE_MODE == globalUserVariable->currentMode)
            value = mControl->getChannelPower_ChannelBW();
        else if(SA_ACP_MEASURE_MODE == globalUserVariable->currentMode || SA_MULTI_ACP_MODE == globalUserVariable->currentMode)
            value = mControl->getACP_ChannelBW();

        if (value < 0)
        {
            value *= -1;
            minusFlag = 1;
        }
        strGab = globalUserVariable->freqValueToQstring(value);
        unitNo = globalUserVariable->freqUnitFindProc(value);
        if(minusFlag)
            strGab = QString("-%1").arg(strGab);
        ui->lblTitle->setText("Channel BandWidth");
        ui->AmptUnit->hide();
        break;
    case SA_INPUT_CHANNEL_SPACING:
        ui->freqBtnUnit1->setText("GHz");
        ui->freqBtnUnit2->setText("MHz");
        ui->freqBtnUnit3->setText("kHz");
        ui->freqBtnUnit4->setText("Hz");

        if(SA_ACP_MEASURE_MODE == globalUserVariable->currentMode || SA_MULTI_ACP_MODE == globalUserVariable->currentMode)
            value = mControl->getACP_ChannelSP();

        if (value < 0)
        {
            value *= -1;
            minusFlag = 1;
        }
        strGab = globalUserVariable->freqValueToQstring(value);
        unitNo = globalUserVariable->freqUnitFindProc(value);
        if(minusFlag)
            strGab = QString("-%1").arg(strGab);
        ui->lblTitle->setText("Channel Space");
        ui->AmptUnit->hide();
        break;
    case SA_INPUT_OCCUPIED:
        ui->lblTitle->setText("Occ SA_BW%pwr");
        strGab = QString::number(globalUserVariable->gOccupied_BW,'f',2);
//        ui->amptBtnUnit1->hide();
//        ui->amptBtnUnit2->hide();
//        ui->amptBtnUnit3->hide();
//        ui->amptBtnUnit4->hide();
//        ui->amptBtnUnit5->hide();
//        ui->amptBtnUnit6->hide();
//        ui->amptBtnUnit7->setGeometry(186,20,55,50);
//        ui->amptBtnUnit7->setText("Enter");
        ui->freqBtnUnit1->hide();
        ui->freqBtnUnit2->hide();
        ui->freqBtnUnit3->hide();
        ui->freqBtnUnit4->setGeometry(186,20,55,50);
        ui->freqBtnUnit4->setText("Enter");
        ui->AmptUnit->hide();
        //ui->FREQuNIT->hide();
        break;
    case SA_INPUT_PERIOD_TIME:
        ui->freqBtnUnit4->setText("ns");
        ui->freqBtnUnit3->setText("us");
        ui->freqBtnUnit2->setText("ms");
        ui->freqBtnUnit1->setText("s");
        ui->AmptUnit->hide();
        value = mControl->getSweepTime();
        unitNo = globalUserVariable->getTimeUnit(value);
        strGab = globalUserVariable->TimeTransformToQstring(value);

        ui->lblTitle->setText("Period Time");
        break;
    case SA_INPUT_ZEROSPAN_TIME:
        ui->freqBtnUnit4->setText("ns");
        ui->freqBtnUnit3->setText("us");
        ui->freqBtnUnit2->setText("ms");
        ui->freqBtnUnit1->setText("s");
        ui->AmptUnit->hide();
        value = mControl->getZeroSpanTime();
        unitNo = globalUserVariable->getTimeUnit(value);
        strGab = globalUserVariable->TimeTransformToQstring(value);

        ui->lblTitle->setText("Zero Span Time");
        break;
    case SA_INPUT_SWEEP_TIME:
        ui->freqBtnUnit4->setText("ns");
        ui->freqBtnUnit3->setText("us");
        ui->freqBtnUnit2->setText("ms");
        ui->freqBtnUnit1->setText("s");
        ui->AmptUnit->hide();
        value = mControl->getSweepTime();
        unitNo = globalUserVariable->getTimeUnit(value);
        strGab = globalUserVariable->TimeTransformToQstring(value);

        ui->lblTitle->setText("Sweep Time");
        // getInitialTimeVal(globalUserVariable->gPersistenceTime,pos);
        break;
    case SA_INPUT_DOT_SWEEP_TIME:
        ui->freqBtnUnit4->setText("ns");
        ui->freqBtnUnit3->setText("us");
        ui->freqBtnUnit2->setText("ms");
        ui->freqBtnUnit1->setText("s");
        ui->AmptUnit->hide();
        value = mControl->getDotSweepTime();
        unitNo = globalUserVariable->getTimeUnit(value);
        strGab = globalUserVariable->TimeTransformToQstring(value);

        ui->lblTitle->setText("Dot Sweep Time");
        break;
    case SA_INPUT_CH_NUM:
        ui->lblTitle->setText("Channel Number");
        //Johnson Add 0730
        value = mControl->getChannelNumber();
        strGab = QString::number(value);
        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->hide();
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->setGeometry(186,20,55,50);
        ui->amptBtnUnit7->setText("Enter");
        break;
        //Johnson 190410
    case SA_INPUT_ZERORESTRAINATTEN:
        ui->freqBtnUnit1->setText("GHz");
        ui->freqBtnUnit2->setText("MHz");
        ui->freqBtnUnit3->setText("kHz");
        ui->freqBtnUnit4->setText("Hz");
        ui->lblTitle->setText("ZeroRestrainAtten");
        strGab = QString::number(globalUserVariable->gZeroRestrainAtten);
        ui->AmptUnit->hide();
        ui->FREQuNIT->hide();
        break;
    case SA_INPUT_ZERORESTRAINPHASE:
        ui->freqBtnUnit1->setText("GHz");
        ui->freqBtnUnit2->setText("MHz");
        ui->freqBtnUnit3->setText("kHz");
        ui->freqBtnUnit4->setText("Hz");
        ui->lblTitle->setText("ZeroRestrainPhase");
        strGab = QString::number(globalUserVariable->gZeroRestrainPhase);
        ui->AmptUnit->hide();
        ui->FREQuNIT->hide();
        break;
 case SA_INPUT_LIMIT_CURPOINTSET:
        ui->lblTitle->setText("Limit Current Point Setup");
        value = mControl->getLimitCurPointIndex();
        strGab = QString::number(value);
        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->hide();
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->setText("Enter");
        ui->amptBtnUnit7->setGeometry(186,20,55,50);
        break;
    default:
        break;
    }
    strValue = strGab.left(strGab.indexOf(" "));
    strUnit = strGab.right(strGab.length() - strGab.indexOf(" "));
    if(strValue == strUnit)
        strUnit = "";
    qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());//Johnson 0702

    if(strlen(newDataString))
        blNumberInput = true;
    else
        blNumberInput = false;

    //Johnson 0726
    if(strchr(newDataString,'.'))
        blDotInput = true;
    else
        blDotInput = false;
    ui->lblValue->setText(strValue +
                          QObject::tr("<font size = 18px>%1</font>").arg(strUnit)
                          );
//    if(strGab.indexOf(".") > 0)
//        highLightIndex = strGab.indexOf(".") - 1;
//    else
//        highLightIndex = (qint32)strlen(newDataString) - 1;

//    if(highLightIndex + 1 > (qint32)strlen(newDataString))
//        highLightIndex = -1;
//    if(highLightIndex >= 0)
//    {
////        blFirstIn = false;
//        QString strNewData(strValue);

//        QString strPrevious = strNewData.left(highLightIndex);
//        QString strRear = strNewData.right(strValue.length() - highLightIndex - 1);
//        QString strHighLight = strNewData.mid(highLightIndex,1);
//        ui->lblValue->setText(  strPrevious +
//                                QObject::tr("<font color = yellow>%1</font>").arg(strHighLight) +
//                                strRear +
//                                QObject::tr("<font size = 18px>%1</font>").arg(strUnit)
//                                );
//    }
//    else ui->lblValue->setText(newDataString);
    return ;
}

/**
 * @brief  Close current widget.
 * @param  void
 * @author Tony
 * @since 2018-12-19
*/
void SA_Dialog_DigitInput::on_pb_cancel_clicked()
{
#ifdef SA_F239
    //Johnson 190410
    QString strValue = newDataString;
    qreal value = strValue.toDouble();
    if(mDialogIndex == SA_INPUT_ZERORESTRAINATTEN)
    {
        globalUserVariable->gZeroRestrainAtten = value;
        //mControl->setZeroRestrainAtten(value);
        mControl->setZeroRestrain(globalUserVariable->gZeroRestrainAtten,globalUserVariable->gZeroRestrainPhase);
    }
    else if(mDialogIndex == SA_INPUT_ZERORESTRAINPHASE)
    {
        globalUserVariable->gZeroRestrainPhase = value;
        //mControl->setZeroRestrainPhase(value);
        mControl->setZeroRestrain(globalUserVariable->gZeroRestrainAtten,globalUserVariable->gZeroRestrainPhase);
    }
    /*
    else if(mDialogIndex == SA_INPUT_OCCUPIED)
    {
        mControl->setOccupiedBW_OccBW(value);
    }
    */
#endif

    this->close();
    return;
}
/**
 * @brief  Clear all.
 * @param  void
 * @author Tony
 * @since 2018-12-19
*/
void SA_Dialog_DigitInput::clearAll()
{
    blNumberInput = false;
    blFirstIn = false;
    blDotInput = false;
    bLeftKey = false;
    bRightKey = false;
    highLightIndex = -1;
    memset(newDataString, 0, sizeof(newDataString));
    ui->lblValue->setText(newDataString);
}

/**
 * @brief  Clear up one bit of data.
 * @param  void
 * @author Tony
 * @since 2018-12-19
*/
void SA_Dialog_DigitInput::backSpace()
{
    qint32 strLen = 0;
    char backupStr[21] = {'\0',};

    strLen = strlen(newDataString);
    if (strLen > 0) {
        strcpy (backupStr, newDataString);
        memset(newDataString, 0, sizeof(newDataString));
        strncpy(newDataString, backupStr, strLen -1);
    }

    if(!bLeftKey&&!bRightKey&&!globalUserVariable->bShiftKeyPressed)
        ui->lblValue->setText(newDataString);
    else if(!globalUserVariable->bShiftKeyPressed)
    {
        if(highLightIndex+1>(qint32)strlen(newDataString))
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

    if (!strlen(newDataString)){
        //Johnson 0611
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
 * @author Tony
 * @since 2018-12-19
*/
void SA_Dialog_DigitInput::keyPressEvent(QKeyEvent *event)
{
    qint32 keyvalue = event->key();
    if(event->key() == Qt::Key_PowerOff)
    {
        if(!event->isAutoRepeat())
            QApplication::sendEvent(this->parent(),event);
        return;
    }
    if(keyvalue == Qt::Key_Escape )
    {
        this->close();
        return;
    }
    else if(keyvalue == Qt::Key_F3 || keyvalue == Qt::Key_F4||keyvalue == Qt::Key_Shift)
    {
//        emit knobevent(event);
        QCoreApplication::sendEvent(mParent, event);
        return;
    }
    keyresponse(keyvalue);

    return;
}

/**
 * @brief  Key up control.
 * @param  event
*/
void SA_Dialog_DigitInput::keyupControl()
{
    if(globalUserVariable->bShiftKeyPressed) return;
    if(highLightIndex >= 0) bRightKey = true;
    if(blNumberInput){
        if(highLightIndex>=0&&highLightIndex<(qint32)strlen(newDataString))
        {
            valueIncreaseControl();
        }
    }
}
/**
 * @brief  Key down control.
 * @param  event
*/
void SA_Dialog_DigitInput::keydownControl()
{
    if(globalUserVariable->bShiftKeyPressed) return;
    if(highLightIndex >= 0) bRightKey = true;
    if(blNumberInput){
        if(highLightIndex>=0&&highLightIndex<(qint32)strlen(newDataString)){
            valueDecreaseControl();
            /*QString strNewData(newDataString);
            QString strPrevious = strNewData.left(highLightIndex);
            QString strRear = strNewData.right(strlen(newDataString)-highLightIndex-1);
            QString strHighLight = strNewData.mid(highLightIndex,1);
            ui->lblValue->setText(  strPrevious +
                    QObject::tr("<font color = red>%1</font>").arg(strHighLight)+
                    strRear
                    );*/
        }
    }
}

void SA_Dialog_DigitInput::keyleftControl()
{
    if(globalUserVariable->bShiftKeyPressed) return;
    blFirstIn = false;
    if(blNumberInput){
        bLeftKey = true;

        QString strNewData(newDataString);

        if(highLightIndex < 0) highLightIndex = strlen(newDataString)-1;
        else{
            highLightIndex--;
            if(strNewData.mid(highLightIndex,1) == "."||strNewData.mid(highLightIndex,1) == "-") highLightIndex--;
        }
//        if(highLightIndex < 0) highLightIndex = strlen(newDataString)-1;
        /*if(highLightIndex>=0){
            QString strPrevious = strNewData.left(highLightIndex);
            QString strRear = strNewData.right(strlen(newDataString)-highLightIndex-1);
            QString strHighLight = strNewData.mid(highLightIndex,1);
            ui->lblValue->setText(  strPrevious +
                    QObject::tr("<font color = red>%1</font>").arg(strHighLight)+
                    strRear
                    );
        }
        else ui->lblValue->setText(newDataString);*/
    }
}
void SA_Dialog_DigitInput::keyrightControl()
{
    if(globalUserVariable->bShiftKeyPressed) return;
    blFirstIn = false;
    if(blNumberInput){
        bRightKey = true;

        QString strNewData(newDataString);

        if(highLightIndex < 0){
            if(newDataString[0] == '-') highLightIndex = 1;
            else highLightIndex = 0;
        }
        else{
            highLightIndex++;
            if(strNewData.mid(highLightIndex,1) == "."||strNewData.mid(highLightIndex,1) == "-") highLightIndex++;
        }

        if(highLightIndex>=(qint32)strlen(newDataString)) highLightIndex = -1;
    }
}
void SA_Dialog_DigitInput::keyclockwiseControl()
{
    if(globalUserVariable->bShiftKeyPressed) return;
    if(blNumberInput){
        if(highLightIndex>=0&&highLightIndex<(qint32)strlen(newDataString)){
            valueIncreaseControl();
        }
        else{
            getKnobValue(CLOCKWISE);
        }
    }
}
void SA_Dialog_DigitInput::keyanticlockwiseControl()
{
    if(globalUserVariable->bShiftKeyPressed)
        return;
    if(blNumberInput)
    {
        if(highLightIndex>=0&&highLightIndex<(qint32)strlen(newDataString))
        {
            valueDecreaseControl();
        }
        else
        {
            getKnobValue(ANTICLOCKWISE);
        }
    }
}
void SA_Dialog_DigitInput::valueIncreaseControl()
{
    /*char tempDataString[20];
    memset(tempDataString,0,sizeof(char)*20);

    for(qint32 i = 0;i<strlen(newDataString);i++){
        if(i == highLightIndex){
            if(newDataString[i] == '9') tempDataString[i] = '0';
            else tempDataString[i] = newDataString[i]+1;
        }
        else tempDataString[i] = newDataString[i];
    }
    memset(newDataString,0,sizeof(char)*20);
    strcpy(newDataString,tempDataString);*/

    if(strchr(newDataString,'.')){
        //get Dot's index
        qint32 posPrev = strchr(newDataString,'.')-newDataString+1;
        posPrev--;
        //change newDataString's value
        qreal dataNumber = atof(newDataString);
        if(posPrev<highLightIndex) dataNumber = dataNumber+1/pow(10.,(qreal)(highLightIndex-posPrev));
        else dataNumber = dataNumber+pow(10.,(qreal)(posPrev-highLightIndex-1));


        //get bits after dot and set newDataString
        qint32 dataLenPrev = strlen(newDataString);
        qint32 bitsAfterDot = dataLenPrev - posPrev-1;
        sprintf(newDataString,"%.9f",dataNumber);
        //get dot's index and set highLightIndex's value
        qint32 posAfter = strchr(newDataString,'.')-newDataString+1;
        posAfter--;
        highLightIndex = highLightIndex+(posAfter-posPrev);
        //set newDataString
        for(qint32 i = posAfter+bitsAfterDot+1;i<(qint32)strlen(newDataString);i++){
            newDataString[i] = 0;
        }
    }
    else{
        qint32 dataLenPre = strlen(newDataString);
        qint32 dataNumber = atoi(newDataString);
        dataNumber += pow(10.,(qreal)(strlen(newDataString)-highLightIndex-1));
        sprintf(newDataString,"%d",dataNumber);
        qint32 dataLenAfter = strlen(newDataString);
        highLightIndex = highLightIndex + (dataLenAfter-dataLenPre);

        if(highLightIndex == 0&&dataNumber<0) highLightIndex++;
    }

    QString strnewData(newDataString);
    if(strnewData.mid(highLightIndex,1) == "."||strnewData.mid(highLightIndex,1) == "-") highLightIndex--;
    if(highLightIndex>=(qint32)strlen(newDataString)) highLightIndex = -1;
}
void SA_Dialog_DigitInput::valueDecreaseControl()
{
    /*char tempDataString[20];
    memset(tempDataString,0,sizeof(char)*20);

    for(qint32 i = 0;i<strlen(newDataString);i++){
        if(i == highLightIndex){
            if(newDataString[i] == '9') tempDataString[i] = '0';
            else tempDataString[i] = newDataString[i]+1;
        }
        else tempDataString[i] = newDataString[i];
    }
    memset(newDataString,0,sizeof(char)*20);
    strcpy(newDataString,tempDataString);*/

    if(strchr(newDataString,'.'))
    {
        //get Dot's index
        qint32 pos = strchr(newDataString,'.')-newDataString+1;
        pos--;
        //change newDataString's value
        qreal dataNumber = atof(newDataString);
        if(pos<highLightIndex) dataNumber = dataNumber-1/pow(10.,(qreal)(highLightIndex-pos));
        else dataNumber = dataNumber-pow(10.,(qreal)(pos-highLightIndex-1));

        if(dataNumber>=0.)
        {
            //get bits after dot and set newDataString
            qint32 dataLen = strlen(newDataString);
            qint32 bitsAfterDot = dataLen - pos-1;
            sprintf(newDataString,"%.9f",dataNumber);
            for(qint32 i = pos+bitsAfterDot+1;i<(qint32)strlen(newDataString);i++){
                newDataString[i] = 0;
            }

            //get dot's index and set highLightIndex's value
            qint32 posAfterNumberChnage = strchr(newDataString,'.')-newDataString+1;
            posAfterNumberChnage--;
            if(posAfterNumberChnage - pos<0){
                if(highLightIndex > 0) highLightIndex--;
            }
        }
        else highLightIndex++;
    }
    else{
        qint32 dataLenPre = strlen(newDataString);
        qint32 dataNumber = atoi(newDataString);
        dataNumber -= pow(10.,(qreal)(strlen(newDataString)-highLightIndex-1));
        sprintf(newDataString,"%d",dataNumber);
        qint32 dataLenAfter = strlen(newDataString);
        highLightIndex = highLightIndex - (dataLenPre-dataLenAfter);

        if(highLightIndex == -1&&dataNumber>=0) highLightIndex = 0;
    }

    QString strnewData(newDataString);
    if(strnewData.mid(highLightIndex,1) == "."||strnewData.mid(highLightIndex,1) == "-") highLightIndex++;
    if(highLightIndex>=(qint32)strlen(newDataString)) highLightIndex = -1;
}

void SA_Dialog_DigitInput::getKnobValue(quint32 mode)
{
    QString strValue;

    switch (entryNo){
    case SA_INPUT_FREQ_OFFSET:
    case SA_INPUT_FREQ_CENTER:
    case SA_INPUT_FREQ_START:
    case SA_INPUT_FREQ_STOP:
    case SA_INPUT_SPUREM_FREQ_START:
    case SA_INPUT_SPUREM_FREQ_STOP:
        strValue = getNewFreqDataStringValue(mode,mControl->getCFFreq(),unitNo);
        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());
        break;
    case SA_INPUT_FREQ_CF:
    case SA_INPUT_FREQ_SPAN:
    case SA_INPUT_MANUAL_RBW:
    case SA_INPUT_MANUAL_VBW:
    case SA_INPUT_MARKER_EDIT:
    case SA_INPUT_DELTA_MARKER_EDIT:
    case SA_INPUT_CHANNEL_BANDWIDTH:
    case SA_INPUT_CHANNEL_SPACING:
    case SA_INPUT_POWERSENSOR_FREQ:
    case SA_INPUT_MULTIACP_HIGHESTCH_FREQ:
    case SA_INPUT_MULTIACP_LOWESTCH_FREQ:
    case SA_INPUT_MULTIACP_CHNLSPACING:
    case SA_INPUT_MULTIACP_MAININTEG_BW:
    case SA_INPUT_MULTIACP_ADJINTEG_BW:
    case SA_INPUT_MULTIACP_ALTINTEG_BW:
        strValue = getNewFreqDataStringValue(mode,SA_MHZ,unitNo);
        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());
        break;
    case SA_INPUT_AVERAGE_COUNT:
        if(mode == CLOCKWISE) strValue.sprintf("%d", atoi(newDataString)+1);
        else if(mode == ANTICLOCKWISE) {
            if(atoi(newDataString) >= 1) strValue.sprintf("%d", atoi(newDataString)-1);
            else strValue = QString("%1").arg("0");
        }
        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());//Johnson 0630
        break;
        //F3 F4 send keyevent to parent
    case SA_INPUT_SPUREM_SPUR_INDEX:
        break;
    case SA_INPUT_SPUREM_RANGE_INDEX:
        break;
    case SA_INPUT_OCCUPIED://Johnson 1008 Add
        if(mode == CLOCKWISE) strValue.sprintf("%.2f", atof(newDataString)+0.1);
        else if(mode == ANTICLOCKWISE) {
            if(atof(newDataString) >= 0.1) strValue.sprintf("%.2f", atof(newDataString)-0.1);
            else strValue = QString("%1").arg("0");
        }
        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());
        break;
    case SA_INPUT_SPUREM_SWEEP_TIME:
    case SA_INPUT_SWEEP_TIME:
    case SA_INPUT_TRIGGER_DELAY_VALUE:
    case SA_INPUT_TRIGGER_PERTIMER:
    case SA_INPUT_DOT_SWEEP_TIME:
    case SA_INPUT_DOORCTRL_TRIGDELAY:
    case SA_INPUT_DOORCTRL_DOORWID:
    case SA_INPUT_DOORCTRL_PRVTTIME:
    case SA_INPUT_DOORCTRL_GATEVIEW_STARTTIME:
    case SA_INPUT_DOORCTRL_PERI_PERIOD:
    case SA_INPUT_DOORCTRL_PERI_SYNSRCDELAY:
    case SA_INPUT_DOORCTRL_PERI_SRCPRVTTIME:
        if(unitNo == UNIT_NS) strValue = getNewSweepTimeDataStringValue(mode,1000000000.,unitNo);
        else if(unitNo == UNIT_US) strValue = getNewSweepTimeDataStringValue(mode,1000000.,unitNo);
        else if(unitNo == UNIT_MS) strValue = getNewSweepTimeDataStringValue(mode,1000.,unitNo);
        else if(unitNo == UNIT_S)  strValue = getNewSweepTimeDataStringValue(mode,1.,unitNo);
        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());
        break;
    case SA_INPUT_XDB:
        if(mode == CLOCKWISE) strValue.sprintf("%.2f", atof(newDataString)+1);
        else if(mode == ANTICLOCKWISE) {
            if(atof(newDataString) >= 0.1) strValue.sprintf("%.2f", atof(newDataString)-1);
            else strValue = QString("%1").arg("0");
        }
        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());
        break;
    }
}
QString SA_Dialog_DigitInput::getNewFreqDataStringValue(qint32 clockWiseMode,quint64 freStep,qint32 unitNo)
{
    QString strValue;
    qreal unitGab = 0.;

    QString strGab;
    qint32 pos = 0;
    quint64 freqVal;
    qreal newDataStringValue = strtod(newDataString,NULL);

    /*strValue.sprintf("%.3f", newDataStringValue);
    if(strchr(newDataString,'.')) {
        qint32 prec = strlen(newDataString) - (strchr(newDataString,'.') - newDataString) - 1;
        freqVal = mControl->globalUserVariable->Round(freqVal,prec);
    }*/

    if(clockWiseMode == CLOCKWISE){
        switch(unitNo) {
        case UNIT_GHZ: unitGab = (qreal) SA_GHZ; break;
        case UNIT_MHZ: unitGab = (qreal) SA_MHZ; break;
        case UNIT_KHZ: unitGab = (qreal) SA_KHZ; break;
        case UNIT_HZ:  unitGab = (qreal) SA_HZ; break;
        }
        freqVal = freStep+newDataStringValue*unitGab;

        strGab = QString::number(freqVal, 'd',0);
        pos = globalUserVariable->freqnotZeroPosition(freqVal);
        //        pos = mControl->globalUserVariable->notZeroPositionFindFunc(strGab);
        unitNo = globalUserVariable->freqUnitFindProc(freqVal);
        //        unitNo = mControl->globalUserVariable->freqUnitFindProc(freqVal);

        switch (unitNo) {
        case UNIT_GHZ:
            unitGab = (qreal) SA_GHZ;
            switch (pos) {
            case 0:
            case 1:
            case 2:
                strValue.sprintf("%.3f", (qreal) freqVal / unitGab);
                break;
            case 3:
                strValue.sprintf("%.3f", (qreal) freqVal / unitGab);
                break;
            case 4:
                strValue.sprintf("%.4f", (qreal) freqVal / unitGab);
                break;
            case 5:
                strValue.sprintf("%.5f", (qreal) freqVal / unitGab);
                break;
            case 6:
                strValue.sprintf("%.6f", (qreal) freqVal / unitGab);
                break;
            case 7:
                strValue.sprintf("%.7f", (qreal) freqVal / unitGab);
                break;
            case 8:
                strValue.sprintf("%.8f", (qreal) freqVal / unitGab);
                break;
            case 9:
                strValue.sprintf("%.9f", (qreal) freqVal / unitGab);
                break;
            default:
                strValue.sprintf("%.2f", (qreal) freqVal / unitGab);
                break;
            }
            break;
        case UNIT_MHZ:
            unitGab = (qreal) SA_MHZ;
            switch (pos) {
            case 0:
            case 1:
            case 2:
                strValue.sprintf("%.3f", (qreal) freqVal / unitGab);
                break;
            case 3:
                strValue.sprintf("%.3f", (qreal) freqVal / unitGab);
                break;
            case 4:
                strValue.sprintf("%.4f", (qreal) freqVal / unitGab);
                break;
            case 5:
                strValue.sprintf("%.5f", (qreal) freqVal / unitGab);
                break;
            case 6:
                strValue.sprintf("%.6f", (qreal) freqVal / unitGab);
                break;
            default:
                strValue.sprintf("%.2f", (qreal) freqVal / unitGab);
                break;
            }
            break;
        case UNIT_KHZ:
            unitGab = (qreal) SA_KHZ;
            switch (pos) {
            case 0:
            case 1:
            case 2:
                strValue.sprintf("%.3f", (qreal) freqVal / unitGab);
                break;
            case 3:
                strValue.sprintf("%.3f", (qreal) freqVal / unitGab);
                break;
            default:
                strValue.sprintf("%.2f", (qreal) freqVal / unitGab);
                break;
            }
            break;
        case UNIT_HZ:
            unitGab = (qreal) SA_HZ;
            strValue.sprintf("%.2f", (qreal) freqVal / unitGab);
            break;
        }
    }
    else if(clockWiseMode == ANTICLOCKWISE){
        switch(unitNo) {
        case UNIT_GHZ: unitGab = (qreal) SA_GHZ; break;
        case UNIT_MHZ: unitGab = (qreal) SA_MHZ; break;
        case UNIT_KHZ: unitGab = (qreal) SA_KHZ; break;
        case UNIT_HZ:  unitGab = (qreal) SA_HZ; break;
        }
        if(newDataStringValue*unitGab>=freStep)
            freqVal = newDataStringValue*unitGab-freStep;
        else /*return QString(newDataString)*/
            freqVal = 0;
        //if(freqVal < 0) freqVal = 0;
        strGab = QString::number(freqVal, 'd',0);
        pos = globalUserVariable->freqnotZeroPosition(freqVal);
        //        pos = mControl->globalUserVariable->notZeroPositionFindFunc(strGab);
        unitNo = globalUserVariable->freqUnitFindProc(freqVal);
        //        unitNo = mControl->globalUserVariable->freqUnitFindProc(freqVal);

        switch (unitNo) {
        case UNIT_GHZ:
            unitGab = (qreal) SA_GHZ;
            //the number of bit after "." is 9-pos
            switch (pos) {
            case 0:
            case 1:
            case 2:
                strValue.sprintf("%.3f", (qreal) freqVal / unitGab);
                break;
            case 3:
                strValue.sprintf("%.3f", (qreal) freqVal / unitGab);
                break;
            case 4:
                strValue.sprintf("%.4f", (qreal) freqVal / unitGab);
                break;
            case 5:
                strValue.sprintf("%.5f", (qreal) freqVal / unitGab);
                break;
            case 6:
                strValue.sprintf("%.6f", (qreal) freqVal / unitGab);
                break;
            case 7:
                strValue.sprintf("%.7f", (qreal) freqVal / unitGab);
                break;
            case 8:
                strValue.sprintf("%.8f", (qreal) freqVal / unitGab);
                break;
            case 9:
                strValue.sprintf("%.9f", (qreal) freqVal / unitGab);
                break;
            default:
                strValue.sprintf("%.2f", (qreal) freqVal / unitGab);
                break;
            }
            break;
        case UNIT_MHZ:
            unitGab = (qreal) SA_MHZ;
            //the number of bit after "." is 6-pos
            switch (pos) {
            case 0:
            case 1:
            case 2:
                strValue.sprintf("%.3f", (qreal) freqVal / unitGab);
                break;
            case 3:
                strValue.sprintf("%.3f", (qreal) freqVal / unitGab);
                break;
            case 4:
                strValue.sprintf("%.4f", (qreal) freqVal / unitGab);
                break;
            case 5:
                strValue.sprintf("%.5f", (qreal) freqVal / unitGab);
                break;
            case 6:
                strValue.sprintf("%.6f", (qreal) freqVal / unitGab);
                break;
            default:
                strValue.sprintf("%.2f", (qreal) freqVal / unitGab);
                break;
            }
            break;
        case UNIT_KHZ:
            unitGab = (qreal) SA_KHZ;
            //the number of bit after "." is 3-pos
            switch (pos) {
            case 0:
            case 1:
            case 2:
                strValue.sprintf("%.3f", (qreal) freqVal / unitGab);
                break;
            case 3:
                strValue.sprintf("%.3f", (qreal) freqVal / unitGab);
                break;
            default:
                strValue.sprintf("%.2f", (qreal) freqVal / unitGab);
                break;
            }
            break;
        case UNIT_HZ:
            unitGab = (qreal) SA_HZ;
            strValue.sprintf("%.2f", (qreal) freqVal / unitGab);
            break;
        }
    }
    return strValue;
}
QString SA_Dialog_DigitInput::getNewSweepTimeDataStringValue(qint32 clockWiseMode, qreal sweepTime, qint32 unitNo)
{
    QString strValue;
    qreal unitGab = 0.;
    QString unitStr;

    QString strGab;
    qint32 pos = 0;
    qreal _timeVal;

    qreal newDataStringValue = atof(newDataString);

    if(clockWiseMode == CLOCKWISE){

        switch (unitNo) {
        case UNIT_NS:
            unitGab = (qreal) SA_GHZ;
            unitStr = QString("ns");

            _timeVal = sweepTime+newDataStringValue*SA_GHZ;
            strGab = QString::number(_timeVal, 'd',0);
            //pos = mControl->globalUserVariable->notZeroPositionFindFunc(strGab);
            pos = globalUserVariable->freqnotZeroPosition(_timeVal);
            strValue.sprintf("%.0f", (qreal) _timeVal / unitGab);
            break;
        case UNIT_US:
            unitGab = (qreal) SA_MHZ;
            unitStr = QString("us");

            _timeVal = sweepTime+newDataStringValue*SA_MHZ;
            strGab = QString::number(_timeVal, 'd',0);
            //pos = mControl->globalUserVariable->notZeroPositionFindFunc(strGab);
            pos = globalUserVariable->freqnotZeroPosition(_timeVal);

            strValue.sprintf("%.0f", (qreal) _timeVal / unitGab);
            break;
        case UNIT_MS:
            unitGab = (qreal) SA_KHZ;
            unitStr = QString("ms");

            _timeVal = sweepTime+newDataStringValue*SA_KHZ;
            strGab = QString::number(_timeVal, 'd',0);
            //pos = mControl->globalUserVariable->notZeroPositionFindFunc(strGab);
            pos = globalUserVariable->freqnotZeroPosition(_timeVal);

            strValue.sprintf("%.0f", (qreal) _timeVal / unitGab);
            break;
        case UNIT_S:
            unitStr = QString("s");

            _timeVal = sweepTime+newDataStringValue;
            strGab = QString::number(_timeVal, 'd',0);
            //pos = mControl->globalUserVariable->notZeroPositionFindFunc(strGab);
            pos = globalUserVariable->freqnotZeroPosition(_timeVal);

            switch (pos) {
            case 0:
                strValue.sprintf("%.2f",  _timeVal );
                break;
            case 1:
                strValue.sprintf("%.1f",  _timeVal);
                break;
            case 2:
            default:
                strValue.sprintf("%.0f",  _timeVal);
                break;
            }
            break;
        }
    }
    else if(clockWiseMode == ANTICLOCKWISE){
        switch (unitNo) {
        case UNIT_NS:
            unitGab = (qreal) SA_GHZ;
            unitStr = QString("ns");

            _timeVal = newDataStringValue*SA_GHZ-sweepTime;
            if(_timeVal < 0) _timeVal = 0;
            strGab = QString::number(_timeVal, 'd',0);
            //pos = mControl->globalUserVariable->notZeroPositionFindFunc(strGab);
            pos = globalUserVariable->freqnotZeroPosition(_timeVal);

            strValue.sprintf("%.0f", (qreal) _timeVal / unitGab);
            break;
        case UNIT_US:
            unitGab = (qreal) SA_MHZ;
            unitStr = QString("us");

            _timeVal = newDataStringValue*SA_MHZ-sweepTime;
            if(_timeVal < 0) _timeVal = 0;
            strGab = QString::number(_timeVal, 'd',0);
            //pos = mControl->globalUserVariable->notZeroPositionFindFunc(strGab);            //pos = mControl->globalUserVariable->notZeroPositionFindFunc(strGab);
            pos = globalUserVariable->freqnotZeroPosition(_timeVal);
            strValue.sprintf("%.0f", (qreal) _timeVal / unitGab);
            break;
        case UNIT_MS:
            unitGab = (qreal) SA_KHZ;
            unitStr = QString("ms");

            _timeVal = newDataStringValue*SA_KHZ-sweepTime;
            if(_timeVal < 0) _timeVal = 0;
            strGab = QString::number(_timeVal, 'd',0);
            //pos = mControl->globalUserVariable->notZeroPositionFindFunc(strGab);
            pos = globalUserVariable->freqnotZeroPosition(_timeVal);

            strValue.sprintf("%.0f", (qreal) _timeVal / unitGab);
            break;
        case UNIT_S:
            unitStr = QString("s");

            _timeVal = newDataStringValue-sweepTime;
            if(_timeVal < 0) _timeVal = 0;
            strGab = QString::number(_timeVal, 'd',0);
            //pos = mControl->globalUserVariable->notZeroPositionFindFunc(strGab);
            pos = globalUserVariable->freqnotZeroPosition(_timeVal);

            switch (pos) {
            case 0:
                strValue.sprintf("%.2f",  _timeVal );
                break;
            case 1:
                strValue.sprintf("%.1f",  _timeVal);
                break;
            case 2:
            default:
                strValue.sprintf("%.0f",  _timeVal);
                break;
            }
            break;
        }
    }
    return strValue;
}
void SA_Dialog_DigitInput::InitKeyboard()
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
    mBtnkey.insert(ui->btnBackSpace,Qt::Key_Backspace);
    mBtnkey.insert(ui->pb_dot,Qt::Key_Period);

    mBtnkey.insert(ui->pb_clearAll,Qt::Key_Delete);
    mBtnkey.insert(ui->pb_Up,Qt::Key_Up);
    mBtnkey.insert(ui->pb_Down,Qt::Key_Down);
    mBtnkey.insert(ui->pb_Left,Qt::Key_Left);
    mBtnkey.insert(ui->pb_Right,Qt::Key_Right);
    for(qint32 i = 0; i < 18; i++)
    {
        connect(key_btn[i],SIGNAL(clicked()),this,SLOT(btn_clicked()));
    }

    return;
}
void SA_Dialog_DigitInput::btn_clicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    qint32 keyValue;
    keyValue = mBtnkey.find(btn).value();
    keyresponse(keyValue);
    return;
}
void SA_Dialog_DigitInput::keyresponse(qint32 keyValue)
{

    //Johnson 0608);
    qint32 strLen = 0;
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
        //case Qt::Key_Up:
        //case Qt::Key_F8:
    case Qt::Key_Period:
        //case Qt::Key_F3:
        switch(entryNo) {
        case SA_INPUT_AVERAGE_COUNT:
            if(strlen(newDataString) >= 6)
                return;
            break;
        case SA_INPUT_SPUREM_RANGE_INDEX:
            if(strlen(newDataString) >= 3)
                return;
            break;
        case SA_INPUT_SPUREM_SPUR_INDEX:
            if(strlen(newDataString) >= 4)
                return;
            break;
        case SA_INPUT_CH_STEP:
            if(strlen(newDataString) >= 4)
                return;
            break;
        case SA_INPUT_SPUREM_SWEEP_TIME:
        case SA_INPUT_SWEEP_TIME:
        case SA_INPUT_TRIGGER_DELAY_VALUE:
        case SA_INPUT_TRIGGER_PERTIMER:
        case SA_INPUT_DOT_SWEEP_TIME:
        case SA_INPUT_DOORCTRL_TRIGDELAY:
        case SA_INPUT_DOORCTRL_DOORWID:
        case SA_INPUT_DOORCTRL_PRVTTIME:
        case SA_INPUT_DOORCTRL_GATEVIEW_STARTTIME:
        case SA_INPUT_DOORCTRL_PERI_PERIOD:
        case SA_INPUT_DOORCTRL_PERI_SYNSRCDELAY:
        case SA_INPUT_DOORCTRL_PERI_SRCPRVTTIME:
            if(strlen(newDataString) >= 17 && newDataString[strlen(newDataString) - 1] != '.')
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
        switch(entryNo) {
        case SA_INPUT_AVERAGE_COUNT:
            if(atoi(newDataString) - 10000 >= 0)
            {
                strcpy(newDataString,"10000");
                return;
            }
            break;
        case SA_INPUT_SPUREM_SWEEP_TIME:
        case SA_INPUT_SWEEP_TIME:
        case SA_INPUT_TRIGGER_DELAY_VALUE:
        case SA_INPUT_TRIGGER_PERTIMER:
        case SA_INPUT_DOT_SWEEP_TIME:
        case SA_INPUT_DOORCTRL_TRIGDELAY:
        case SA_INPUT_DOORCTRL_DOORWID:
        case SA_INPUT_DOORCTRL_PRVTTIME:
        case SA_INPUT_DOORCTRL_GATEVIEW_STARTTIME:
        case SA_INPUT_DOORCTRL_PERI_PERIOD:
        case SA_INPUT_DOORCTRL_PERI_SYNSRCDELAY:
        case SA_INPUT_DOORCTRL_PERI_SRCPRVTTIME:
            if(strlen(newDataString) >= 17 && newDataString[strlen(newDataString) - 1] != '.')
                return;
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
    case Qt::Key_Backspace:
        backSpace();
        break;
    case Qt::Key_Delete:
        clearAll();
        break;
    case Qt::Key_Shift:
        if(!globalUserVariable->bShiftKeyPressed)
            globalUserVariable->bShiftKeyPressed = true;
        else
            globalUserVariable->bShiftKeyPressed = false;
        break;
    case Qt::Key_0:
        if(globalUserVariable->bShiftKeyPressed){
            //mControl->globalUserVariable->KeyNumber = 0;
            on_pb_cancel_clicked();
            return;
        }
        if(blFirstIn){
            memset(newDataString,0,sizeof(newDataString));
            strcpy(newDataString,"0");
            blDotInput = false;
            blFirstIn = false;
            highLightIndex = -1;
        }
        else if(!strlen(newDataString)||strcmp(newDataString,"0")){
            if(highLightIndex<0) strncat(newDataString, "0" , 1);
            else{
                char tempDataString[20];
                memset(tempDataString,0,sizeof(char)*20);

                for(qint32 i = 0;i<(qint32)strlen(newDataString);i++){
                    if(i == highLightIndex){
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
        if(globalUserVariable->bShiftKeyPressed){
            //mControl->globalUserVariable->KeyNumber = 1;
            on_pb_cancel_clicked();
            return;
        }
        if(blFirstIn){
            memset(newDataString,0,sizeof(newDataString));
            strcpy(newDataString,"1");
            blDotInput = false;
            blFirstIn = false;
            highLightIndex = -1;
        }
        else /*if(strcmp(newDataString,"0"))*/{
            if(highLightIndex<0)
                strncat(newDataString, "1" , 1);
            else{
                char tempDataString[20];
                memset(tempDataString,0,sizeof(char)*20);

                for(qint32 i = 0;i<(qint32)strlen(newDataString);i++){
                    if(i == highLightIndex){
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
        if(globalUserVariable->bShiftKeyPressed){
            //mControl->globalUserVariable->KeyNumber = 2;
            on_pb_cancel_clicked();
            return;
        }
        if(blFirstIn){
            memset(newDataString,0,sizeof(newDataString));
            strcpy(newDataString,"2");
            blDotInput = false;
            blFirstIn = false;
            highLightIndex = -1;
        }
        else/* if(strcmp(newDataString,"0"))*/{
            if(highLightIndex<0) strncat(newDataString, "2" , 1);
            else{
                char tempDataString[20];
                memset(tempDataString,0,sizeof(char)*20);

                for(qint32 i = 0;i<(qint32)strlen(newDataString);i++){
                    if(i == highLightIndex){
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
        if(globalUserVariable->bShiftKeyPressed){
            //mControl->globalUserVariable->KeyNumber = 3;
            on_pb_cancel_clicked();
            return;
        }
        if(blFirstIn){
            memset(newDataString,0,sizeof(newDataString));
            strcpy(newDataString,"3");
            blDotInput = false;
            blFirstIn = false;
            highLightIndex = -1;
        }
        else/* if(strcmp(newDataString,"0"))*/{
            if(highLightIndex<0) strncat(newDataString, "3" , 1);
            else{
                char tempDataString[20];
                memset(tempDataString,0,sizeof(char)*20);

                for(qint32 i = 0;i<(qint32)strlen(newDataString);i++){
                    if(i == highLightIndex){
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
        if(globalUserVariable->bShiftKeyPressed){
            //mControl->globalUserVariable->KeyNumber = 4;
            on_pb_cancel_clicked();
            return;
        }
        if(blFirstIn){
            memset(newDataString,0,sizeof(newDataString));
            strcpy(newDataString,"4");
            blDotInput = false;
            blFirstIn = false;
            highLightIndex = -1;
        }
        else/* if(strcmp(newDataString,"0"))*/{
            if(highLightIndex<0) strncat(newDataString, "4" , 1);
            else{
                char tempDataString[20];
                memset(tempDataString,0,sizeof(char)*20);

                for(qint32 i = 0;i<(qint32)strlen(newDataString);i++){
                    if(i == highLightIndex){
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
        if(globalUserVariable->bShiftKeyPressed){
            //mControl->globalUserVariable->KeyNumber = 5;
            on_pb_cancel_clicked();
            return;
        }
        if(blFirstIn){
            memset(newDataString,0,sizeof(newDataString));
            strcpy(newDataString,"5");
            blDotInput = false;
            blFirstIn = false;
            highLightIndex = -1;
        }
        else/* if(strcmp(newDataString,"0"))*/{
            if(highLightIndex<0) strncat(newDataString, "5" , 1);
            else{
                char tempDataString[20];
                memset(tempDataString,0,sizeof(char)*20);

                for(qint32 i = 0;i<(qint32)strlen(newDataString);i++){
                    if(i == highLightIndex){
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
        if(globalUserVariable->bShiftKeyPressed){
            //mControl->globalUserVariable->KeyNumber = 6;
            on_pb_cancel_clicked();
            return;
        }
        if(blFirstIn){
            memset(newDataString,0,sizeof(newDataString));
            strcpy(newDataString,"6");
            blDotInput = false;
            blFirstIn = false;
            highLightIndex = -1;
        }
        else/* if(strcmp(newDataString,"0"))*/{
            if(highLightIndex<0) strncat(newDataString, "6" , 1);
            else{
                char tempDataString[20];
                memset(tempDataString,0,sizeof(char)*20);

                for(qint32 i = 0;i<(qint32)strlen(newDataString);i++){
                    if(i == highLightIndex){
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
        if(globalUserVariable->bShiftKeyPressed){
            //mControl->globalUserVariable->KeyNumber = 7;
            on_pb_cancel_clicked();
            return;
        }
        if(blFirstIn){
            memset(newDataString,0,sizeof(newDataString));
            strcpy(newDataString,"7");
            blDotInput = false;
            blFirstIn = false;
            highLightIndex = -1;
        }
        else/* if(strcmp(newDataString,"0"))*/{
            if(highLightIndex<0) strncat(newDataString, "7" , 1);
            else{
                char tempDataString[20];
                memset(tempDataString,0,sizeof(char)*20);

                for(qint32 i = 0;i<(qint32)strlen(newDataString);i++){
                    if(i == highLightIndex){
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
        if(globalUserVariable->bShiftKeyPressed){
            //mControl->globalUserVariable->KeyNumber = 8;
            on_pb_cancel_clicked();
            return;
        }
        if(blFirstIn){
            memset(newDataString,0,sizeof(newDataString));
            strcpy(newDataString,"8");
            blDotInput = false;
            blFirstIn = false;
            highLightIndex = -1;
        }
        else/* if(strcmp(newDataString,"0"))*/{
            if(highLightIndex<0) strncat(newDataString, "8" , 1);
            else{
                char tempDataString[20];
                memset(tempDataString,0,sizeof(char)*20);

                for(qint32 i = 0;i<(qint32)strlen(newDataString);i++){
                    if(i == highLightIndex){
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
        if(globalUserVariable->bShiftKeyPressed){
            //mControl->globalUserVariable->KeyNumber = 9;
            on_pb_cancel_clicked();
            return;
        }
        if(blFirstIn){
            memset(newDataString,0,sizeof(newDataString));
            strcpy(newDataString,"9");
            blDotInput = false;
            blFirstIn = false;
            highLightIndex = -1;
        }
        else/* if(strcmp(newDataString,"0")&&!globalUserVariable->bShiftKeyPressed)*/{
            if(highLightIndex<0) strncat(newDataString, "9" , 1);
            else{
                char tempDataString[20];
                memset(tempDataString,0,sizeof(char)*20);

                for(qint32 i = 0;i<(qint32)strlen(newDataString);i++){
                    if(i == highLightIndex){
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
        if(globalUserVariable->bShiftKeyPressed) return;
        else
        {
            if(globalUserVariable->PrimaryAction == SA_AMPLITUDE)
            {
                if(entryNo == SA_INPUT_SCALEDIV||entryNo == SA_LIMIT_EDGE||entryNo == SA_INPUT_ATTEN) return;
            }
            else if(globalUserVariable->PrimaryAction == SA_MEASUREMENT)
            {
                if(entryNo != SA_INPUT_XDB &&entryNo != SA_INPUT_SPUREM_FREQ_START && \
                   entryNo != SA_INPUT_SPUREM_FREQ_STOP && entryNo != SA_INPUT_SPUREM_LIMIT_START && \
                   entryNo != SA_INPUT_SPUREM_LIMIT_STOP &&entryNo != SA_INPUT_SPUREM_PEAK_DEFINITION \
                   &&entryNo != SA_INPUT_SPUREM_PEAK_THRESHOLD) return;
            }
            else if(globalUserVariable->PrimaryAction == SA_MARKER)
            {
                if(entryNo != SA_INPUT_DELTA_MARKER_EDIT && entryNo != SA_INPUT_MARKER_EDIT) return;
            }
            else if(globalUserVariable->PrimaryAction == SA_DISPLAY)
            {
                if(entryNo != SA_INPUT_CURVE && entryNo != SA_INPUT_DOORCTRL_TRIGGERLEVEL) return;
            }else if(globalUserVariable->PrimaryAction == SA_FREQUENCY)
            {
                if(entryNo != SA_INPUT_FREQ_OFFSET && entryNo != SA_INPUT_FREQ_CENTER && entryNo != SA_INPUT_FREQ_START && entryNo != SA_INPUT_FREQ_STOP&& entryNo != SA_INPUT_SPUREM_FREQ_START&& entryNo != SA_INPUT_SPUREM_FREQ_STOP)
                    return;
            } else if(globalUserVariable->PrimaryAction == SA_LIMIT)
            {
                if(entryNo == SA_LIMIT_EDGE)
                    return;
            }
            else if(globalUserVariable->PrimaryAction == SA_TRIGGER)
            {
                if(entryNo != SA_INPUT_TRIGGER_LEVEL) return;
            }
            else if(globalUserVariable->PrimaryAction == SA_SWEEP)
            {
                if(entryNo != SA_INPUT_DOORCTRL_TRIGGERLEVEL) return;
            }
            else return;
        }
        if(blFirstIn){
            memset(newDataString,0,sizeof(newDataString));
            strcpy(newDataString,"-");
            blDotInput = false;
            blFirstIn = false;
            blNumberInput = true;
            highLightIndex = -1;
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
                        qreal DataNumber = atof(newDataString);
                        if(DataNumber>0){
                            for(qint32 i = strlen(newDataString)-1;i>=0;i--){
                                newDataString[i+1] = newDataString[i];
                            }
                            newDataString[0] = '-';

                            if((bLeftKey||bRightKey)&&highLightIndex >= 0){
                                highLightIndex++;
                            }

                            //Johnson 0709
                            QString strnewData(newDataString);
                            if(strnewData.mid(highLightIndex,1) == "."||strnewData.mid(highLightIndex,1) == "-") highLightIndex++;
                            if(highLightIndex>=(qint32)strlen(newDataString)) highLightIndex = -1;
                        }
                        else if(DataNumber<0){
                            for(quint32 i = 0;i<strlen(newDataString);i++){
                                newDataString[i] = newDataString[i+1];
                            }

                            if(bLeftKey||bRightKey) highLightIndex--;

                            //Johnson 0709
                            QString strnewData(newDataString);
                            if(strnewData.mid(highLightIndex,1) == "."||strnewData.mid(highLightIndex,1) == "-") highLightIndex++;
                            if(highLightIndex>=(qint32)strlen(newDataString)) highLightIndex = -1;
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
        if(globalUserVariable->bShiftKeyPressed) return;

        //if(strlen(newDataString)) blNumberInput = true;
        //else blNumberInput = false;
        keyleftControl();
        //blFirstIn = false;
        break;
    case Qt::Key_Right:
    case Qt::Key_F7:
        if(globalUserVariable->bShiftKeyPressed) return;

        //if(strlen(newDataString)) blNumberInput = true;
        //else blNumberInput = false;
        keyrightControl();
        //blFirstIn = false;
        break;
    case Qt::Key_Up:
    case Qt::Key_F8:
      //  valueIncreaseControl();
        if(globalUserVariable->bShiftKeyPressed) return;
        //if(strlen(newDataString)) blNumberInput = true;
        //else blNumberInput = false;
        keyupControl();
        // blFirstIn = false;
        break;
    case Qt::Key_Down:
    case Qt::Key_F9:
        if(globalUserVariable->bShiftKeyPressed)
            return;
        keydownControl();
        break;
    case Qt::Key_F3://clockwise
        if(globalUserVariable->bShiftKeyPressed)
            return;
        keyclockwiseControl();
        //blFirstIn = false;
        break;
    case Qt::Key_F4://anticlockwise
        if(globalUserVariable->bShiftKeyPressed)
            return;
        keyanticlockwiseControl();
        break;
    case Qt::Key_Period:  // . Dot
        if(entryNo == SA_INPUT_AVERAGE_COUNT)
            return;
        if(globalUserVariable->bShiftKeyPressed)
            return;
        blDotInput = strrchr(newDataString,'.');//Johnson 0828
        if(!blDotInput&&blNumberInput&&strcmp(newDataString,"-")){
            strncat(newDataString, "." , 1);
            blDotInput = true;
        }
        break;
    }



    if(!bLeftKey&&!bRightKey&&!globalUserVariable->bShiftKeyPressed) ui->lblValue->setText(newDataString);
    else if(!globalUserVariable->bShiftKeyPressed){
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

qint32 SA_Dialog_DigitInput::freqSpecCompareFunc(qint32 unitPos)
{
    QString strValue;
    qreal value = 0.;
    qreal freq = 0;
    qint32 index,ptIndex;

    qint32 i = 0;
    qint32 minusFlag = 0;
    qreal rounding = 0.5;
    //Johnson 0709
    strValue = newDataString;
    value = strValue.toDouble();

    if (value < 0.)  {
        value *= -1;
        //rounding *= -1;
        minusFlag = 1;   // 음수 값 인지 (Delta Marker Edit)
    }

    switch (unitPos)
    {
    case 1:
        freq = /*(qlonglong)*/ (value * (qreal)SA_GHZ + rounding);   // 1.2Ghz 입력시 1.9999999로 저장되어 + .5로 수정
        break;
    case 2:
        freq = /*(qlonglong)*/ (value * (qreal)SA_MHZ + rounding);
        break;
    case 3:
        freq = /*(qlonglong)*/ (value * (qreal)SA_KHZ + rounding);
        break;
    case 4:
        freq = /*(qlonglong)*/ (value * (qreal) SA_HZ + rounding);
        break;
    }

    switch (entryNo)
    {
    case SA_INPUT_MANUAL_RBW:
        //0726
        if(1 == mControl->globalUserVariable->gSpanMode)
        {
            if(freq <= 3001)
            {
                this->close();
                return 0;
            }
        }
        mControl->setRbwValue(freq);
        return 1;
        break;
    case SA_INPUT_MANUAL_VBW:
        mControl->setVbwValue(freq);
        return 1;
        break;
    }

    /*if ( mControl->globalUserVariable->gMenu ==  SA_MENU_SPECTRUM_ANALYZER)*/ {
        switch (entryNo)  {
        case SA_INPUT_FREQ_OFFSET:
            if(minusFlag)
            {
                freq *= -1;
            }
            mControl->setFreqOffset(freq);
            break;
        case SA_INPUT_SPUREM_FREQ_START:
            if(minusFlag) freq *= -1;
            mControl->setSpurEMstartFreq(freq);
            break;
        case SA_INPUT_SPUREM_FREQ_STOP:
            if(minusFlag) freq *= -1;
            mControl->setSpurEMstopFreq(freq);
            break;
        case SA_INPUT_SEM_CHBW:
            if(minusFlag) freq *= -1;
            mControl->setSpecEMRefChBw(freq);
            break;
        case SA_INPUT_FREQ_CENTER:
            if(minusFlag) freq *= -1;
            mControl->setCenterFreq(freq);
            break;
        case SA_INPUT_FREQ_START:
            if(minusFlag) freq *= -1;
            mControl->setStartFreq(freq);
            break;
        case SA_INPUT_FREQ_STOP:
            if(minusFlag) freq *= -1;
            mControl->setStopFreq(freq);
            break;
        case SA_INPUT_FREQ_CF:
            mControl->setCFFreq(freq);
            break;
        case SA_INPUT_FREQ_SPAN:
            mControl->setSpan(freq);
            break;
        case SA_INPUT_LIMIT_FREQ:
            if(minusFlag) freq *= -1;
            index = mControl->getLimitSelect();
            ptIndex = mControl->getLimitCurPointIndex(index)-1;
            mControl->setLimitFreq(index,ptIndex,freq);
            break;
        case SA_INPUT_MARKER_EDIT:
            if(minusFlag) freq *= -1;
            mControl->setMarkerRefFreq(freq);

            break;
        case  SA_INPUT_DELTA_MARKER_EDIT:
            if(minusFlag == 1)
            {
                freq *= -1;
            }
            freq+=mControl->getMarkerRefFreq();
            mControl->setMarkerDeltaFreq(freq);

            break;
        case SA_INPUT_CHANNEL_BANDWIDTH:
            if(globalUserVariable->currentMode == SA_CHNLPOWER_MEASURE_MODE) mControl->setChannelPower_ChannelBW(freq);
            else if(globalUserVariable->currentMode == SA_ACP_MEASURE_MODE || globalUserVariable->currentMode == SA_MULTI_ACP_MODE) mControl->setACP_ChannelBW(freq);
            break;
        case SA_INPUT_CHANNEL_SPACING:
            if(globalUserVariable->currentMode == SA_ACP_MEASURE_MODE || globalUserVariable->currentMode == SA_MULTI_ACP_MODE) mControl->setACP_ChannelSP(freq);
            break;
        case SA_INPUT_UPPER_LIMIT_AMPT:
            mControl->setUpperLimit(freq);
            break;
        case SA_INPUT_MULTIACP_HIGHESTCH_FREQ:
            if(globalUserVariable->currentMode == SA_ACP_MEASURE_MODE) mControl->setMulACP_HighestCHFreq(freq);
            break;
        case SA_INPUT_MULTIACP_LOWESTCH_FREQ:
            if(globalUserVariable->currentMode == SA_ACP_MEASURE_MODE) mControl->setMulACP_LowestCHFreq(freq);
            break;
        case SA_INPUT_MULTIACP_CHNLSPACING:
            if(globalUserVariable->currentMode == SA_ACP_MEASURE_MODE || globalUserVariable->currentMode == SA_MULTI_ACP_MODE)
                mControl->setMulACP_ChnSpacing(freq);
            break;
        case SA_INPUT_MULTIACP_MAININTEG_BW:
            if(globalUserVariable->currentMode == SA_ACP_MEASURE_MODE || globalUserVariable->currentMode == SA_MULTI_ACP_MODE)
                mControl->setMulACP_MainIntegBW(freq);
            break;
        case SA_INPUT_MULTIACP_ADJINTEG_BW:
            if(globalUserVariable->currentMode == SA_ACP_MEASURE_MODE || globalUserVariable->currentMode == SA_MULTI_ACP_MODE)
                mControl->setMulACP_ADJIntegBW(freq);
            break;
        case SA_INPUT_MULTIACP_ALTINTEG_BW:
            if(globalUserVariable->currentMode == SA_ACP_MEASURE_MODE || globalUserVariable->currentMode == SA_MULTI_ACP_MODE)
                mControl->setMulACP_ALTIntegBW(freq);
            break;
        }

        return 1;
    }
    /*else
    {
        // Power Sensor의 Freq Input
        switch (entryNo)  {
        case SA_INPUT_POWERSENSOR_FREQ:

            mControl->globalUserVariable->gPowersensorFreq = freq;
            return 1;
            break;
        }
    }*/

    //added by Steve
    return 1;

}

qint32 SA_Dialog_DigitInput::timeSpecCompareFunc(qint32 unitPos)
{
    //0725 steve if fft mode,not change param
    if(3 == mControl->globalUserVariable->ganamode &&
       entryNo != SA_INPUT_TRIGGER_PERTIMER && entryNo != SA_INPUT_TRIGGER_DELAY_VALUE && entryNo != SA_INPUT_DOORCTRL_GATEVIEW_STARTTIME &&
       entryNo != SA_INPUT_DOORCTRL_TRIGDELAY && entryNo != SA_INPUT_DOORCTRL_DOORWID && entryNo != SA_INPUT_DOORCTRL_PRVTTIME &&
       entryNo != SA_INPUT_DOORCTRL_PERI_PERIOD && entryNo != SA_INPUT_DOORCTRL_PERI_SYNSRCDELAY && entryNo != SA_INPUT_DOORCTRL_PERI_SRCPRVTTIME)
    {
        this->close();
        return 0;
    }

    QString strValue;
    qreal value = 0.;
    qreal  _time = 0;
    qint32 minusFlag = 0;
    strValue = newDataString;
    value = strValue.toDouble();
    if(value < 0)
    {
        minusFlag = 1;
        value *= -1;
    }

    //steve 0713 back to ms
    switch (unitPos)
    {
    case 1:  //s
        _time = (value * (qreal)SA_KHZ);
        break;
    case 2:  //ms
        _time = value;
        break;
    case 3: //us
        _time =  (value / (qreal)SA_KHZ);
        break;
    case 4: //ns
        _time =  value  / (qreal)SA_MHZ;
        break;
    }


    //  //Johnson 1126 limit the value's range
    //  if(mControl->globalUserVariable->gZeroSpanAction) {
    //      if(ZEROSPAN_SWEEPTIMEMIN > _time) _time = ZEROSPAN_SWEEPTIMEMIN;
    //      else if(ZEROSPAN_SWEEPTIMEMAX < _time) _time = ZEROSPAN_SWEEPTIMEMAX;
    //  }
    //  else {
    //      if(NOZEROSPAN_SWEEPTIMEMIN > _time) _time = NOZEROSPAN_SWEEPTIMEMIN;
    //      else if(NOZEROSPAN_SWEEPTIMEMAX < _time) _time = NOZEROSPAN_SWEEPTIMEMAX;
    //  }

    switch (entryNo)
    {
    case SA_INPUT_SPUREM_SWEEP_TIME:
        mControl->setSpurEMSweepTime(_time);
        break;
    case SA_INPUT_SWEEP_TIME:
        mControl->setFixSweepMode(SA_OFF);
        mControl->setSweepTime(_time);
        break;
    case SA_INPUT_DOT_SWEEP_TIME:
        mControl->setDotSweepTime(_time);
        break;
    case SA_INPUT_TRIGGER_DELAY_VALUE:
        mControl->setTriggerDelayValue(_time);
        break;
    case SA_INPUT_TRIGGER_PERTIMER:
        mControl->setTriggerPerTimer(_time);
        break;
    case SA_INPUT_DOORCTRL_TRIGDELAY:
        mControl->setEdgeTrigDely(_time);
        break;
    case SA_INPUT_DOORCTRL_DOORWID:
        mControl->setEdgeTrigDoorWidth(_time);
        break;
    case SA_INPUT_DOORCTRL_PRVTTIME:
        mControl->setEdgeTrigPreventTimes(_time);
        break;
    case SA_INPUT_DOORCTRL_GATEVIEW_STARTTIME:
        mControl->setGateViewStartTime(_time);
        break;
    case SA_INPUT_DOORCTRL_PERI_PERIOD:
        mControl->setPeriodTrigPeriod(_time);
        break;
    case SA_INPUT_DOORCTRL_PERI_SYNSRCDELAY:
        mControl->setPeriodTrigSrcDelay(_time);
        break;
    case SA_INPUT_DOORCTRL_PERI_SRCPRVTTIME:
        mControl->setPeriodTrigPreventTimes(_time);
        break;
    case SA_INPUT_MARKER_EDIT:
        if(minusFlag == 1)
        {
            _time *= -1;
        }
        mControl->setMarkerRefTime(_time);
        break;
    case SA_INPUT_DELTA_MARKER_EDIT:
        if(minusFlag == 1)
        {
            _time *= -1;
        }
        _time+=mControl->getMarkerRefTime();
        mControl->setMarkerDeltaTime(_time);
        break;
    }

    return 1;
}

qint32 SA_Dialog_DigitInput::amptdSpecCompareFunc(qint32 unitNo)
{
    QString strValue;
    qreal value = 0.;
    qreal tempVal = 0.;

    QString strWarning;//Johnson 0918
    qint32 AmptUnit,index,ptIndex;
    //Johnson 0709
    strValue = newDataString;
    value = strValue.toDouble();

    //Johnson 0919 Change
    switch (entryNo)
    {
    case SA_INPUT_SEM_BSPOWER: //Johnson 0918
        mControl->setSpecEMBsPower(value);
        break;

    case SA_INPUT_REF_LEVEL: //Johnson 0918
        AmptUnit = mControl->getAmpUnit();

        switch (AmptUnit)
        {
        case SA_WATTS:
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

            value = mControl->globalUserVariable->wattsToDbmCalculatorFunc(tempVal);
            break;
        case SA_VOLT:
            if (unitNo == 5)     // V
                tempVal = value *  1000000.;
            else if (unitNo == 6) // mV
                tempVal = value * 1000.;
            else if (unitNo == 7) // uV
                tempVal = value;

            value = mControl->globalUserVariable->voltToDbmCalculatorFunc(tempVal);
            break;
        case SA_DBV:
            value -= dBVFix;
            break;
        case SA_DBMV:
            value -= dBmVFix;
            break;
        case SA_DBUV:
            value -= dBuVFix;
            break;
        }

        mControl->setRefLevel(value);
        break;
    case SA_INPUT_TRIGGER_LEVEL:
        if(SA_TRIGGER_EXTERNAL == mControl->getTriggerMode())
        {
            if (unitNo == 5)     // V
                tempVal = value *  1000000.;
            else if (unitNo == 6) // mV
                tempVal = value * 1000.;
            else if (unitNo == 7) // uV
                tempVal = value;

            value = mControl->globalUserVariable->voltToDbmCalculatorFunc(tempVal);
        }

        qDebug()<<"value1 is "<<value;

        mControl->setTriggerLevel(value);
        break;
    case SA_INPUT_DOORCTRL_TRIGGERLEVEL:
        mControl->setRFBurstTrigLevel(value);
        break;
    case SA_INPUT_SPUREM_LIMIT_START: //Johnson 0918
        strValue.sprintf("%.2f",value);
        mControl->setSpurEMstartLimit(strValue.toDouble());
        break;
    case SA_INPUT_SPUREM_LIMIT_STOP: //Johnson 0918
        strValue.sprintf("%.2f",value);
        mControl->setSpurEMStopLimit(strValue.toDouble());
        break;
    case SA_INPUT_SPUREM_PEAK_DEFINITION: //Johnson 0918
        strValue.sprintf("%.2f",value);
        mControl->setSpurEMpeakDefi(strValue.toDouble());
        break;
    case SA_INPUT_SPUREM_PEAK_THRESHOLD: //Johnson 0918
        strValue.sprintf("%.2f",value);
        mControl->setSpurEMpeakThreshold(strValue.toDouble());
        break;
    case SA_INPUT_SPUREM_ATTEN:
        strValue.sprintf("%.2f",value);
        mControl->setSpurEMAtten(strValue.toDouble());
        break;
#ifdef SAMPLE_LIMIT
    case SA_INPUT_UPPER_LIMIT_AMPT:
        strValue.sprintf("%.2f",value);
        mControl->setUpperLimit(strValue.toDouble());
        break;
    case SA_INPUT_LOWER_LIMIT_AMPT:
        strValue.sprintf("%.2f",value);
        mControl->setLowerLimit(strValue.toDouble());
        break;
    case SA_INPUT_ATLDBC_LIMIT_AMP:
        strValue.sprintf("%.2f",value);
        mControl->setATLdBcLimit(strValue.toDouble());
        break;
#endif
    case SA_INPUT_REF_OFFSET: //Johnson 0918
        strValue.sprintf("%.2f",value);
        mControl->setRefOffset(strValue.toDouble());
        break;
    case SA_INPUT_LIMIT_AMPT:
        index = mControl->globalUserLimit->gLimitSelect;
        ptIndex = mControl->getLimitCurPointIndex(index)-1;
        strValue.sprintf("%.2f",value);
        mControl->setLimitAmpt(index,ptIndex,strValue.toDouble());
        break;
    case SA_INPUT_POWERSENSOR_EXT_OFFSET:
        //Johnson 1106
        if(value > 0)
            value = 0;
        if ( 0 >= value)
        {
            //mControl->globalUserVariable->gPowersensorExtOffset = value;
        }
        break;
    case SA_INPUT_ATTEN:
        if(mControl->getAttenStatus() == SA_AUTO)
            mControl->setAttenStatus(SA_MANUAL);
        mControl->setAttenValue(value);
        break;
    case SA_INPUT_CH_NUM:
        mControl->setChannelNumber(value);
        break;
    case SA_INPUT_LIMIT_CURPOINTSET:
        mControl->setLimitCurPointIndex(mControl->getLimitSelect(),value);
        break;
    case SA_INPUT_SCALEDIV:
        strValue.sprintf("%.2f",value);
        mControl->setScaleDiv(strValue.toDouble());
        break;
    case SA_LIMIT_EDGE:
        mControl->setLimitEdgeValue(value);
        break;
    case SA_INPUT_XDB:
        mControl->setOccupiedBW_XdB(value);
        break;
    }
    return 1;
}

void SA_Dialog_DigitInput::on_freqBtnUnit1_clicked()
{
     qint32 retNo = 0;
    qint32 butNo = 1;

    //judgeRange(1);

    //if (atof(oldDataString) - atof(newDataString) == 0&&unitNo == 1)
    if(!strcmp(oldDataString,newDataString) && unitNo == 1){
        this->close();
        return;
    }

    if (entryNo ==  SA_INPUT_SWEEP_TIME || entryNo == SA_INPUT_TRIGGER_DELAY_VALUE ||\
        entryNo ==  SA_INPUT_TRIGGER_PERTIMER || entryNo == SA_INPUT_SPUREM_SWEEP_TIME ||\
        entryNo == SA_INPUT_DOT_SWEEP_TIME || entryNo == SA_INPUT_DOORCTRL_TRIGDELAY ||\
        entryNo == SA_INPUT_DOORCTRL_DOORWID || entryNo == SA_INPUT_DOORCTRL_PRVTTIME ||\
        entryNo == SA_INPUT_DOORCTRL_PERI_PERIOD || entryNo == SA_INPUT_DOORCTRL_PERI_SYNSRCDELAY ||\
        entryNo == SA_INPUT_DOORCTRL_PERI_SRCPRVTTIME || entryNo == SA_INPUT_DOORCTRL_GATEVIEW_STARTTIME)
        retNo = timeSpecCompareFunc(butNo);
    else if((entryNo ==  SA_INPUT_DELTA_MARKER_EDIT ||entryNo ==  SA_INPUT_MARKER_EDIT) \
            &&globalUserVariable->gSpanMode)
    {
        retNo = timeSpecCompareFunc(butNo);
    }else
        retNo = freqSpecCompareFunc(butNo);

    if (retNo == 1)
    {
        //emit finishEntry(entryNo);
        this->close();
    }
}

void SA_Dialog_DigitInput::on_freqBtnUnit2_clicked()
{
    qint32 retNo = 0;
    qint32 butNo = 2;

    if(!strcmp(oldDataString,newDataString) && unitNo == 2)
    {
        this->close();
        return;
    }

    if (entryNo ==  SA_INPUT_SWEEP_TIME || entryNo == SA_INPUT_TRIGGER_DELAY_VALUE \
            || entryNo == SA_INPUT_TRIGGER_PERTIMER ||entryNo == SA_INPUT_SPUREM_SWEEP_TIME ||\
        entryNo == SA_INPUT_DOT_SWEEP_TIME || entryNo == SA_INPUT_DOORCTRL_TRIGDELAY ||\
            entryNo == SA_INPUT_DOORCTRL_DOORWID || entryNo == SA_INPUT_DOORCTRL_PRVTTIME ||\
            entryNo == SA_INPUT_DOORCTRL_PERI_PERIOD || entryNo == SA_INPUT_DOORCTRL_PERI_SYNSRCDELAY ||\
            entryNo == SA_INPUT_DOORCTRL_PERI_SRCPRVTTIME || entryNo == SA_INPUT_DOORCTRL_GATEVIEW_STARTTIME)
        retNo = timeSpecCompareFunc(butNo);
    else if((entryNo ==  SA_INPUT_DELTA_MARKER_EDIT ||entryNo ==  SA_INPUT_MARKER_EDIT) \
            &&globalUserVariable->gSpanMode)
    {
        retNo = timeSpecCompareFunc(butNo);
    }
    else
        retNo = freqSpecCompareFunc(butNo);

    if (retNo == 1)
    {
        //emit finishEntry(entryNo);
        this->close();
    }
    return ;
}

void SA_Dialog_DigitInput::on_freqBtnUnit3_clicked()
{
    qint32 retNo = 0;
    qint32 butNo = 3;

    if(!strcmp(oldDataString,newDataString) && unitNo == 3)
    {
        this->close();
        return;
    }

    if (entryNo == SA_INPUT_SWEEP_TIME || entryNo == SA_INPUT_TRIGGER_DELAY_VALUE \
        || entryNo == SA_INPUT_TRIGGER_PERTIMER || entryNo == SA_INPUT_SPUREM_SWEEP_TIME ||\
        entryNo == SA_INPUT_DOT_SWEEP_TIME || entryNo == SA_INPUT_DOORCTRL_TRIGDELAY ||\
            entryNo == SA_INPUT_DOORCTRL_DOORWID || entryNo == SA_INPUT_DOORCTRL_PRVTTIME ||\
            entryNo == SA_INPUT_DOORCTRL_PERI_PERIOD || entryNo == SA_INPUT_DOORCTRL_PERI_SYNSRCDELAY ||\
            entryNo == SA_INPUT_DOORCTRL_PERI_SRCPRVTTIME || entryNo == SA_INPUT_DOORCTRL_GATEVIEW_STARTTIME)
        retNo = timeSpecCompareFunc(butNo);
    else if((entryNo ==  SA_INPUT_DELTA_MARKER_EDIT ||entryNo ==  SA_INPUT_MARKER_EDIT) \
            &&globalUserVariable->gSpanMode)
    {
        retNo = timeSpecCompareFunc(butNo);
    }
    else
        retNo = freqSpecCompareFunc(butNo);

    if (retNo == 1)
    {
        //emit finishEntry(entryNo);
        this->close();
    }
    return ;
}

void SA_Dialog_DigitInput::on_freqBtnUnit4_clicked()
{
    qint32 retNo = 0;
    qint32 butNo = 4;
    qint32 value = 0;
    qreal occupiedValue = 0.;
    QString strValue;

    if(!strcmp(oldDataString,newDataString) && unitNo == 4){
        this->close();
        return;
    }


    switch (entryNo)
    {
    case SA_INPUT_AVERAGE_COUNT:
        strValue = ui->lblValue->text();
        value = strValue.toInt();
        mControl->setTraceAverageCount(value);
        retNo = 1;
        break;
    case SA_INPUT_SPUREM_SPUR_INDEX:
        strValue = ui->lblValue->text();
        value = strValue.toInt() -1;
        mControl->setSpurEMCurSpurIndex(value);
        retNo = 1;
        break;
    case SA_INPUT_CH_STEP:
        strValue = ui->lblValue->text();
        value = strValue.toInt();
        mControl->setChannelNumStep(value);
        retNo = 1;
        break;
    case SA_INPUT_SPUREM_RANGE_INDEX:
        strValue = ui->lblValue->text();
        value = strValue.toInt() - 1;
        mControl->setSpurEMCurRangeIndex(value);
        retNo = 1;
        break;
    case SA_INPUT_SPUREM_SWEEP_TIME:
    case SA_INPUT_SWEEP_TIME:
    case SA_INPUT_TRIGGER_DELAY_VALUE:
    case SA_INPUT_TRIGGER_PERTIMER:
    case SA_INPUT_DOT_SWEEP_TIME:
    case SA_INPUT_DOORCTRL_TRIGDELAY:
    case SA_INPUT_DOORCTRL_DOORWID:
    case SA_INPUT_DOORCTRL_PRVTTIME:
    case SA_INPUT_DOORCTRL_GATEVIEW_STARTTIME:
    case SA_INPUT_DOORCTRL_PERI_PERIOD:
    case SA_INPUT_DOORCTRL_PERI_SYNSRCDELAY:
    case SA_INPUT_DOORCTRL_PERI_SRCPRVTTIME:
        retNo = timeSpecCompareFunc(butNo);
        break;
    case SA_INPUT_OCCUPIED://Johnson 1008 Add
        strValue = ui->lblValue->text();
        occupiedValue = strValue.toDouble();
        mControl->setOccupiedBW_OccBW(occupiedValue);
        retNo = 1;
        break;
    case SA_INPUT_DELTA_MARKER_EDIT:
    case SA_INPUT_MARKER_EDIT:
        if(globalUserVariable->gSpanMode)
            retNo = timeSpecCompareFunc(butNo);
        else
            retNo = freqSpecCompareFunc(butNo);
        break;
    default:
        retNo = freqSpecCompareFunc(butNo);
        break;
    }

    if (retNo == 1)
    {
        //emit finishEntry(entryNo);
        this->close();
    }
    return ;
}

void SA_Dialog_DigitInput::on_amptBtnUnit1_clicked()
{
    amptdSpecCompareFunc(1);
    this->close();
    return ;
}

void SA_Dialog_DigitInput::on_amptBtnUnit2_clicked()
{
    amptdSpecCompareFunc(2);
    this->close();
    return;
}

void SA_Dialog_DigitInput::on_amptBtnUnit3_clicked()
{
    amptdSpecCompareFunc(3);
    this->close();
    return;
}

void SA_Dialog_DigitInput::on_amptBtnUnit4_clicked()
{
    amptdSpecCompareFunc(4);
    this->close();
    return;
}

void SA_Dialog_DigitInput::on_amptBtnUnit5_clicked()
{
    amptdSpecCompareFunc(5);
    this->close();
    return;
}

void SA_Dialog_DigitInput::on_amptBtnUnit6_clicked()
{
    amptdSpecCompareFunc(6);
    this->close();
    return;
}

void SA_Dialog_DigitInput::on_amptBtnUnit7_clicked()
{
    amptdSpecCompareFunc(7);
    this->close();
    return;
}

void SA_Dialog_DigitInput::initInputKey(QKeyEvent *event)
{
    keyPressEvent(event);
    return;
}

void SA_Dialog_DigitInput::getInitialAmplitudeVal(qreal amplitudeValue,uint entryNo,char *dataStr,qint32 amplitudeUnit)
{
    switch (entryNo) {
    case SA_INPUT_TRIGGER_LEVEL:
        switch (amplitudeUnit) {
        case SA_VOLT:
        {
            qreal voltGab = 0.;
            qreal calculator = 0.;

            calculator = pow(10, amplitudeValue / 10.);
            voltGab = 1000000. * pow(50 * calculator * 0.001, 0.5);


            //Johnson 0919 Change
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
        default:
            sprintf(dataStr,"%.2f",amplitudeValue);
            break;
        }
        break;
    case SA_INPUT_DOORCTRL_TRIGGERLEVEL:
        sprintf(dataStr,"%.2f",amplitudeValue);
        break;
    case SA_INPUT_REF_LEVEL:
        switch (amplitudeUnit) {
        case SA_DBM:
        case SA_DBMV:
        case SA_DBUV:
            sprintf(dataStr,"%.2f",amplitudeValue);//Johnson 0705
            break;
        case SA_VOLT:
        {
            qreal voltGab = 0.;
            qreal calculator = 0.;

            calculator = pow(10, amplitudeValue / 10.);
            voltGab = 1000000. * pow(50 * calculator * 0.001, 0.5);


            //Johnson 0919 Change
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
        case SA_WATTS:
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
    case SA_INPUT_SPUREM_LIMIT_START:
    case SA_INPUT_SPUREM_LIMIT_STOP:
    case SA_INPUT_SPUREM_PEAK_DEFINITION:
    case SA_INPUT_SPUREM_PEAK_THRESHOLD:
    case SA_INPUT_REF_OFFSET:
    case SA_INPUT_POWERSENSOR_EXT_OFFSET:
        sprintf(dataStr,"%.2f",amplitudeValue);
        break;
    case SA_INPUT_SPUREM_ATTEN:
    case SA_INPUT_ATTEN:
        //Johnson Add 0730
        /*switch((qint32)amplitudeValue)
        {
        case 0: dataStr = "0.00"; break;
        case 1: dataStr = "5.00"; break;
        case 2: dataStr = "10.00"; break;
        case 3: dataStr = "15.00"; break;
        case 4: dataStr = "20.00"; break;
        case 5: dataStr = "25.00"; break;
        case 6: dataStr = "30.00"; break;
        }*/
        sprintf(dataStr,"%.2f",amplitudeValue);
        break;
    case SA_INPUT_SCALEDIV:
        sprintf(dataStr,"%.2f",amplitudeValue);
        break;
    case SA_LIMIT_EDGE://Johnson 0824
        sprintf(dataStr,"%.2f",amplitudeValue);
        break;
    case SA_INPUT_XDB://Johnson 0927
        sprintf(dataStr,"%.2f",amplitudeValue);
        break;
    case SA_INPUT_UPPER_LIMIT_AMPT:
    case SA_INPUT_LOWER_LIMIT_AMPT:
    case SA_INPUT_ATLDBC_LIMIT_AMP:
        sprintf(dataStr,"%.2f",amplitudeValue);
        break;
    }

    if(strlen(dataStr)) blNumberInput = true;
    else blNumberInput = false;

    //Johnson 0709
    if(strchr(dataStr,'.')) blDotInput = true;
    else blDotInput = false;
}

/*
void SA_Dialog_DigitInput::getInitialTimeVal(qreal sweepTime, char *dataStr)
{
    qreal unitGab = 0.;
    QString unitStr;


    // numberLen  => 소숫점 뒤 0이 아닌 길이
    switch (unitNo) {
      case UNIT_NS:
        unitGab = (qreal) SA_GHZ;
        unitStr = QString("ns");
        sprintf(dataStr,"%.2f",amplitudeValue);
        strValue.sprintf("%f", (qreal) sweepTime);
        break;
      case UNIT_US:
        unitGab = (qreal) SA_MHZ;
        unitStr = QString("us");

        strValue.sprintf("%f", (qreal) sweepTime);
        break;
      case UNIT_MS:
        unitGab = (qreal) SA_KHZ;
        unitStr = QString("ms");

        strValue.sprintf("%f", (qreal) sweepTime);
        break;
      case UNIT_S:
        unitStr = QString("s");

        switch (numberLen) {
          case 0:
            strValue.sprintf("%.2f",  sweepTime );
            break;
          case 1:
            strValue.sprintf("%.1f",  sweepTime);
            break;
          case 2:
          default:
            strValue.sprintf("%.0f",  sweepTime);
            break;
          }
        break;
      }
    qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());//Johnson 0702

    if(strlen(newDataString)) blNumberInput = true;
    else blNumberInput = false;

    //Johnson 0726
    if(strchr(newDataString,'.')) blDotInput = true;
    else blDotInput = false;
}
*/

//void SA_Dialog_DigitInput::valueIncreaseControl()
//{
//    qint32 NumValue;
//    QString strHighLight;
//    QString strNum(newDataString);
//    strHighLight = strNum.at(highLightIndex);
//    NumValue = strHighLight.toInt();
//    NumValue = (NumValue + 1) % 10;
//    strNum = strNum.replace(highLightIndex,1,QString::number(NumValue));
//    QByteArray ba = strNum.toLatin1(); // must
//    strcpy(newDataString,ba.data());
////    strncpy(strNum,newDataString+highLightIndex,1);
////    NumValue = atoi(strNum);
////
////    sprintf(strNum,"%d",NumValue);
////    strncpy(strNum,newDataString+highLightIndex,1);
////    newDataString[highLightIndex] = strNum;
//    return;
//}
