#include "rtsa_dialog_digitinput.h"
#include "rtsa_define.h"
#include "rtsa_interface.h"
#include <QKeyEvent>
#include "rtsa_user_variable.h"
#include "ui_rtsa_dialog_digitinput.h"
#include "rtsa_extern.h"

RtSa_Dialog_Digitinput::RtSa_Dialog_Digitinput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RtSa_Dialog_Digitinput)
{
    ui->setupUi(this);
//    this->setCursor(Qt::BlankCursor);
//    setWindowFlags(Qt::FramelessWindowHint/*|Qt::Dialog*/);
    this->setFocusPolicy(Qt::StrongFocus);
//    this->setAttribute(Qt::WA_NoChildEventsForParent,true);
//    this->setAttribute(Qt::WA_ForceUpdatesDisabled,true);
//    this->setAttribute(Qt::WA_OpaquePaintEvent,true);
//    this->setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint | Qt::Dialog);
//    this->close();
    mShiftKeyPressed = false;
    InitKeyboard();
//    pParent = parent;
    this->setFocus();
}

RtSa_Dialog_Digitinput::~RtSa_Dialog_Digitinput()
{
    delete ui;
}
/**
 * @brief  Init dialog interface.
 * @param  index
 * @author Albert
 * @since 2018-12-25
*/
void RtSa_Dialog_Digitinput::setInterface(RtSa_Interface *interface)
{
    mControl = interface;
    return;
}
/**
 * @brief  Init dialog global variable.
 * @param  index
 * @author Albert
 * @since 2018-12-25
*/
void RtSa_Dialog_Digitinput::setUserVariable(RtSa_User_Variable* userVariable)
{
    m_usr_variable = userVariable;
    return;
}
//void RtSa_Dialog_Digitinput::setMarkerUpdateID(qint32 index)
//{
//    mCurMarkerID = index;
//    return;
//}
void RtSa_Dialog_Digitinput::showFreqUnit(bool isOn)
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
void RtSa_Dialog_Digitinput::showAmptUnit(bool isOn)
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
/**
 * @brief  Init dialog display.
 * @param  index
 * @author Tony
 * @since 2018-12-20
*/
void RtSa_Dialog_Digitinput::initDisplay(qint32 index)
{
    this->setFocus();
    entryNo = index;
    QString strGab;
    QString strValue,strUnit;
    qreal   value;
    qreal   valueDelta;
    qint32  intGab;
    qint32 minusFlag = 0;
    qint32 curMarkerID = mControl->getCurMarkerID();
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
    case RTSA_INPUT_FREQ_CENTER:
        value = mControl->getCenterFreq();
        strGab = mControl->getFreqAdjustStr(value);
        unitNo = mControl->freqUnitFindProc(value);
        ui->lblTitle->setText("Center Freq");
//        showAmptUnit(false);
        showFreqUnit(true);
//        ui->TimeWidget->hide();
        break;
    case RTSA_INPUT_FREQ_START:
        value = mControl->getStartFreq();
        strGab = mControl->getFreqAdjustStr(value);
        unitNo = mControl->freqUnitFindProc(value);
        ui->lblTitle->setText("Start Freq");
//        showAmptUnit(false);
        showFreqUnit(true);
        break;
    case RTSA_INPUT_FREQ_STOP:
        value = mControl->getStopFreq();
        strGab = mControl->getFreqAdjustStr(value);
        unitNo = mControl->freqUnitFindProc(value);
        ui->lblTitle->setText("Stop Freq");
//        showAmptUnit(false);
        showFreqUnit(true);
        break;
    case RTSA_INPUT_FREQ_CF:
        value = mControl->getCFStep();
        strGab = mControl->getFreqAdjustStr(value);
        unitNo = mControl->freqUnitFindProc(value);
        ui->lblTitle->setText("Step Freq");
//        showAmptUnit(false);
        showFreqUnit(true);
        break;
    case RTSA_INPUT_FREQ_SPAN:
        value = mControl->getSpan();
        strGab = mControl->getFreqAdjustStr(value);
        unitNo = mControl->freqUnitFindProc(value);
        ui->lblTitle->setText("Span Freq");
        showFreqUnit(true);
//        showAmptUnit(false);
        break;
    case RTSA_INPUT_FREQ_OFFSET:
        value = mControl->getFreqOffset();
        strGab = mControl->getFreqAdjustStr(value);
        ui->lblTitle->setText("Offset Freq");
        showFreqUnit(true);
//        showAmptUnit(false);
        break;
    case RTSA_INPUT_ATTEN:
//        showFreqUnit(false);
        showAmptUnit(false);
        value = mControl->getAttenVal();
        strGab = QString::number(value) + QString(" dB");
        unitNo = mControl->getAmptUint();
        ui->lblTitle->setText("Atten ");
//        ui->FreqUnit->hide();
        ui->amptBtnUnit4->show();
        ui->amptBtnUnit4->setText("dB");
        break;
    case RTSA_INPUT_SCALEDIV:
//        showFreqUnit(false);
        showAmptUnit(false);
        value = mControl->getScaleDiv();
        strGab = QString::number(value) + QString(" dB");
        unitNo = mControl->getAmptUint();
        ui->lblTitle->setText("Scale/Div");
//        ui->FreqUnit->hide();
        ui->amptBtnUnit4->show();
        ui->amptBtnUnit4->setText("dB");
        break;
    case RTSA_INPUT_REF_OFFSET:
//        showFreqUnit(false);
        showAmptUnit(false);
        value = mControl->getRefOffset();
        strGab = QString::number(value) + QString(" dB");
        unitNo = mControl->getAmptUint();
        ui->lblTitle->setText("Ref Offset");
//        ui->FreqUnit->hide();
        ui->amptBtnUnit4->show();
        ui->amptBtnUnit4->setText("dB");
        break;
    case RTSA_INPUT_REF_LEVEL:
//        showFreqUnit(false);
        showAmptUnit(true);
        ui->lblTitle->setText("Ref Level");
        unitNo = mControl->getAmptUint();
        value = mControl->getRefLevel();
        switch (unitNo)
        {
        case RTSA_DBM:
            ui->amptBtnUnit1->hide();
            ui->amptBtnUnit2->hide();
            ui->amptBtnUnit3->hide();
            ui->amptBtnUnit4->setText("dBm");
            ui->amptBtnUnit5->hide();
            ui->amptBtnUnit6->hide();
            ui->amptBtnUnit7->hide();
            break;
        case RTSA_DBMV:
            ui->amptBtnUnit1->hide();
            ui->amptBtnUnit2->hide();
            ui->amptBtnUnit3->hide();
            ui->amptBtnUnit4->setText("dBmV");
            ui->amptBtnUnit5->hide();
            ui->amptBtnUnit6->hide();
            ui->amptBtnUnit7->hide();
            break;
        case RTSA_DBUV:
            ui->amptBtnUnit1->hide();
            ui->amptBtnUnit2->hide();
            ui->amptBtnUnit3->hide();
            ui->amptBtnUnit4->setText("dBuV");
            ui->amptBtnUnit5->hide();
            ui->amptBtnUnit6->hide();
            ui->amptBtnUnit7->hide();
            break;
        case RTSA_VOLT:
            ui->amptBtnUnit1->setText("V");
            ui->amptBtnUnit2->setText("mV");
            ui->amptBtnUnit3->setText("uV");
            ui->amptBtnUnit4->hide();
            ui->amptBtnUnit5->hide();
            ui->amptBtnUnit6->hide();
            ui->amptBtnUnit7->hide();
            break;
        case RTSA_WATTS:
            ui->amptBtnUnit1->setText("pW");
            ui->amptBtnUnit2->setText("fW");
            ui->amptBtnUnit3->setText("aW");
            ui->amptBtnUnit4->setText("nW");
            break;
        case RTSA_DBV:
            ui->amptBtnUnit1->hide();
            ui->amptBtnUnit2->hide();
            ui->amptBtnUnit3->hide();
            ui->amptBtnUnit4->setText("dBV");
            ui->amptBtnUnit5->hide();
            ui->amptBtnUnit6->hide();
            ui->amptBtnUnit7->hide();
            break;
        }
        strGab = mControl->getRefLevelAdjustStr();
        break;
    case RTSA_INPUT_PERSISTENCE_TIME:
//        showFreqUnit(false);
        showAmptUnit(true);
        ui->amptBtnUnit4->setText("ns");
        ui->amptBtnUnit3->setText("us");
        ui->amptBtnUnit2->setText("ms");
        ui->amptBtnUnit1->setText("s");
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->hide();
        value = mControl->getPersistenceTime();
        strGab = mControl->getAdjustTimeStr(value);
        unitNo = mControl->timeUnitFindProc(value);
        ui->lblTitle->setText("Persistence Time");
        break;
    case RTSA_INPUT_ACQ_TIME:
//        showFreqUnit(false);
        showAmptUnit(true);
        ui->amptBtnUnit4->setText("ns");
        ui->amptBtnUnit3->setText("us");
        ui->amptBtnUnit2->setText("ms");
        ui->amptBtnUnit1->setText("s");
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->hide();
        value = mControl->getAcqTime();
        strGab = mControl->getAdjustTimeStr(value);
        unitNo = mControl->timeUnitFindProc(value);
        ui->lblTitle->setText("Acq Time");
        break;
    case RTSA_INPUT_HIGHEST_DENSITY:
//        showFreqUnit(false);
        showAmptUnit(true);
        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->setText("Enter");
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->hide();
        value = mControl->getHighestDensity();
        strGab = QString::number(value) + QString(" %");
        ui->lblTitle->setText("Highest Density");
        break;
    case RTSA_INPUT_LOWEST_DENSITY:
//        showFreqUnit(false);
        showAmptUnit(true);
        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->setText("Enter");
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->hide();
        value = mControl->getLowestDensity();
        strGab = QString::number(value) + QString(" %");
        ui->lblTitle->setText("Lowest Density");
        break;
    case RTSA_INPUT_CURVE:
//        showFreqUnit(false);
        showAmptUnit(true);
        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->setText("Enter");
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->hide();
        value = mControl->getCurve();
        strGab = QString::number(value) + QString(" %");;
        ui->lblTitle->setText("Curve");
        break;
    case RTSA_INPUT_MARKER_EDIT:
//        showAmptUnit(false);
        showFreqUnit(true);
        value = mControl->getMarkerRefFreq(curMarkerID);
        strGab = mControl->getFreqAdjustStr(value);
        unitNo = mControl->freqUnitFindProc(value);
        ui->lblTitle->setText("Frequency");
        break;
    case RTSA_INPUT_DELTA_MARKER_EDIT:
        showFreqUnit(true);
//        showAmptUnit(false);
        valueDelta = mControl->getMarkerRefFreq(curMarkerID);
        value = mControl->getMarkerDeltaFreq(curMarkerID);
        value -= valueDelta;
        strGab = mControl->getFreqAdjustStr(value);
        unitNo = mControl->freqUnitFindProc(value);
        ui->lblTitle->setText("Delta marker edit");
        break;
    case RTSA_INPUT_MARGIN:
//        showFreqUnit(false);
        showAmptUnit(false);
        value = mControl->getMargin(mControl->getCurLimit());
        strGab = QString::number(value,'f',2) + QString(" dB");
        ui->lblTitle->setText("Limit Edge");
        ui->amptBtnUnit4->show();
        ui->amptBtnUnit4->setText("dB");
        break;
        //BW setup
    case RTSA_INPUT_MANUAL_RBW:
//        value = mControl->getBW();
//        strGab = mControl->getFreqAdjustStr(value);
//        unitNo = mControl->freqUnitFindProc(value);
//        ui->lblTitle->setText("BW");
//        ui->AmptUnit->hide();
        break ;
    case RTSA_INPUT_AVERAGE_COUNT:
//        showFreqUnit(false);
        showAmptUnit(false);
        value = mControl->getAvgNum(mControl->getCurTrace());
        strGab = QString::number(value,'f',0) + QString("");
        ui->lblTitle->setText("Average");
        ui->amptBtnUnit4->show();
        ui->amptBtnUnit4->setText("Enter");
        break;
    case RTSA_INPUT_FREQ_CHANNEL_NUM:
//        showFreqUnit(false);
        showAmptUnit(false);
        value = m_usr_variable->CalculateChannelNum();
        strGab = QString::number(value);
        strValue = QString("Channel Num ");
        strUnit =QString("(");
        if(m_usr_variable->gCommuDirection == RTSA_UPLINK)
        {
            value = m_usr_variable->gCHStandard->at(m_usr_variable->gCHIndex).Up.Min;
            strUnit = strUnit + QString::number(value);
            strUnit = strUnit + QString("-");
            value = m_usr_variable->gCHStandard->at(m_usr_variable->gCHIndex).Up.Max;
            strUnit = strUnit + QString::number(value);
        }
        else
        {
            value = m_usr_variable->gCHStandard->at(m_usr_variable->gCHIndex).Down.Min;
            strUnit = strUnit + QString::number(value);
            strUnit = strUnit + QString("-");
            value = m_usr_variable->gCHStandard->at(m_usr_variable->gCHIndex).Down.Max;
            strUnit = strUnit + QString::number(value);
        }
        strUnit = strUnit + QString(")");
        ui->lblTitle->setText(strValue +
                              QObject::tr("<font size = 18px>%1</font>").arg(strUnit));
        ui->amptBtnUnit4->show();
        ui->amptBtnUnit4->setText("Enter");
        strUnit = QString("");
        break;
    case RTSA_INPUT_LIMIT_FREQ:
        intGab = mControl->GetCurLimitDataIndex();
        value = mControl->getLimitCurPointFreq(intGab,mControl->getCurLimit()) * RTSA_MHZ;
        strGab = mControl->getFreqAdjustStr(value);
        unitNo = mControl->freqUnitFindProc(value);
        ui->lblTitle->setText("Limit Frequency");
//        showAmptUnit(false);
        showFreqUnit(true);
        break;
    case RTSA_INPUT_LIMIT_AMPT:
        intGab = mControl->GetCurLimitDataIndex();
        value = mControl->getLimitCurPointAmpt(intGab,mControl->getCurLimit());
        strGab.sprintf("%.2f dBm", value);
        showAmptUnit(true);
        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->setText("dBm");
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->hide();
//        strGab = mControl->get(value);
//        unitNo = mControl->freqUnitFindProc(value);
        ui->lblTitle->setText("Limit Amplitude");
//        showAmptUnit(false);
//        showFreqUnit(true);
        break;
    case RTSA_INPUT_LIMIT_SELECT_INDEX:
        showAmptUnit(false);
        value = mControl->GetCurLimitDataIndex() + 1;
//        value = mControl->getAvgNum(mControl->getCurTrace());
        strGab = QString::number(value,'f',0) + QString("");
        ui->lblTitle->setText("Current Row Index ");
        ui->amptBtnUnit4->show();
        ui->amptBtnUnit4->setText("Enter");
        break;
    case RTSA_INPUT_FMT_FREQ:
        intGab = mControl->getCurFmtDataIndex();
        value = mControl->getCurFmtFreqData(intGab) * RTSA_MHZ;
        strGab = mControl->getFreqAdjustStr(value);
        unitNo = mControl->freqUnitFindProc(value);
        ui->lblTitle->setText("FMT Frequency");
//        showAmptUnit(false);
        showFreqUnit(true);
        break;
    case RTSA_INPUT_FMT_AMPT:
        intGab = mControl->getCurFmtDataIndex();
        value = mControl->getCurFmtAmptData(intGab);
        strGab.sprintf("%.2f dBm", value);
        showAmptUnit(true);
        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->setText("dBm");
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->hide();
//        strGab = mControl->get(value);
//        unitNo = mControl->freqUnitFindProc(value);
        ui->lblTitle->setText("FMT Amplitude");
//        showAmptUnit(false);
//        showFreqUnit(true);
        break;
    case RTSA_INPUT_FMT_SELECT_INDEX:
        showAmptUnit(false);
        value = mControl->getCurFmtDataIndex() + 1;
        strGab = QString::number(value,'f',0) + QString("");
        ui->lblTitle->setText("Current Row Index ");
        ui->amptBtnUnit4->show();
        ui->amptBtnUnit4->setText("Enter");
        break;
    case RTSA_INPUT_TRIGGER_DELAY_VALUE:
        showAmptUnit(true);
        ui->amptBtnUnit4->setText("ns");
        ui->amptBtnUnit3->setText("us");
        ui->amptBtnUnit2->setText("ms");
        ui->amptBtnUnit1->setText("s");
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->hide();
        intGab = mControl->getTrigger();
        value = mControl->getTriggerDelay(intGab);
        strGab = mControl->getAdjustTimeStr(value);
        unitNo = mControl->timeUnitFindProc(value);
        ui->lblTitle->setText("Trigger Delay");
        break;
    case RTSA_INPUT_TRIGGER_LEVEL:
        intGab = mControl->getTrigger();
        value = mControl->getTriggerLevel(intGab);
        strGab.sprintf("%.2f dBm", value);
        showAmptUnit(true);
        ui->amptBtnUnit1->hide();
        ui->amptBtnUnit2->hide();
        ui->amptBtnUnit3->hide();
        ui->amptBtnUnit4->setText("dBm");
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->hide();
        ui->lblTitle->setText("Trigger Level");
        break;
    case RTSA_INPUT_TRIGGER_PERTIMER:
        showAmptUnit(true);

        ui->amptBtnUnit4->setText("ns");
        ui->amptBtnUnit3->setText("us");
        ui->amptBtnUnit2->setText("ms");
        ui->amptBtnUnit1->setText("s");
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->hide();
        value = mControl->getTriggerPeriodTime();
        strGab = mControl->getAdjustTimeStr(value);
        unitNo = mControl->timeUnitFindProc(value);
        ui->lblTitle->setText("Trigger Period");
        break;
    case RTSA_INPUT_TRIGGER_HOLDTIME:
        showAmptUnit(true);
        ui->amptBtnUnit4->setText("ns");
        ui->amptBtnUnit3->setText("us");
        ui->amptBtnUnit2->setText("ms");
        ui->amptBtnUnit1->setText("s");
        ui->amptBtnUnit5->hide();
        ui->amptBtnUnit6->hide();
        ui->amptBtnUnit7->hide();
        intGab = mControl->getTrigger();
        value = mControl->getriggerHoldOffTime(intGab);
        strGab = mControl->getAdjustTimeStr(value);
        unitNo = mControl->timeUnitFindProc(value);
        ui->lblTitle->setText("Trigger HoldOff");
        break;
    case RTSA_SPECTROGTAM_CURSOR_INDEX:
        showAmptUnit(false);
        intGab = mControl->getspectrogramCursorID();
        intGab = mControl->getspectrogramCursorIndex(intGab);
        strGab = QString::number(intGab) + QString("");
        ui->lblTitle->setText("Position");
        ui->amptBtnUnit4->show();
        ui->amptBtnUnit4->setText("Enter");
        break;
    default:
        break;
    }
    strValue = strGab.left(strGab.indexOf(" "));
    if(strGab.indexOf(" ") > 0)
    {
        strUnit = strGab.right(strGab.length() - strGab.indexOf(" "));
    }
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
//    ui->lblValue->setText(strGab);
    ui->lblValue->setText(strValue +
                          QObject::tr("<font size = 18px>%1</font>").arg(strUnit)
                          );

    return ;
}

/**
 * @brief  Close current widget.
 * @param  void
 * @author Tony
 * @since 2018-12-19
*/
void RtSa_Dialog_Digitinput::on_pb_cancel_clicked()
{
    this->close();
}

/**
 * @brief  Clear up one bit of data.
 * @param  void
 * @author Tony
 * @since 2018-12-19
*/
void RtSa_Dialog_Digitinput::backSpace()
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
        if(highLightIndex+1>strlen(newDataString))
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
void RtSa_Dialog_Digitinput::keyPressEvent(QKeyEvent *event)
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
//        emit finishEntry(RTSA_NOT_USE);
        return;
    }
    if(keyvalue == Qt::Key_Shift)
    {
        this->close();
        emit finishEntry(RTSA_SHIFT_ENABLE);
        mShiftKeyPressed = false;
        return;
//        QWidget::keyPressEvent(event);
//        return;
    }
    if(keyvalue == Qt::Key_F3 || keyvalue == Qt::Key_Up \
       || keyvalue == Qt::Key_F8 || keyvalue == Qt::Key_Down \
       || keyvalue == Qt::Key_F9 || keyvalue == Qt::Key_F4)
    {
        this->close();
//        pParent->setFocus();
        emit ClockWiseDown(event);
        return;
    }
    keyresponse(keyvalue);

  return;
}

/**
 * @brief  Key up control.
 * @param  event
*/
void RtSa_Dialog_Digitinput::keyupControl()
{
    if(mShiftKeyPressed) return;
    if(blNumberInput){
        if(highLightIndex>=0&&highLightIndex<strlen(newDataString))
        {
            valueIncreaseControl();
        }
    }
}
/**
 * @brief  Key down control.
 * @param  event
*/
void RtSa_Dialog_Digitinput::keydownControl()
{
    if(mShiftKeyPressed) return;
    if(blNumberInput){
        if(highLightIndex>=0&&highLightIndex<strlen(newDataString)){
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

void RtSa_Dialog_Digitinput::keyleftControl()
{
    if(mShiftKeyPressed) return;
    if(blNumberInput){
        bLeftKey = true;
        blFirstIn = false;
        QString strNewData(newDataString);

        if(highLightIndex < 0) highLightIndex = strlen(newDataString)-1;
        else{
            highLightIndex--;
            if(strNewData.mid(highLightIndex,1) == "."||strNewData.mid(highLightIndex,1) == "-") highLightIndex--;
        }
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
void RtSa_Dialog_Digitinput::keyrightControl()
{
    if(mShiftKeyPressed) return;
    if(blNumberInput){
        bRightKey = true;
        blFirstIn = false;
        QString strNewData(newDataString);

        if(highLightIndex < 0){
           if(newDataString[0] == '-') highLightIndex = 1;
           else highLightIndex = 0;
        }
        else{
            highLightIndex++;
            if(strNewData.mid(highLightIndex,1) == "."||strNewData.mid(highLightIndex,1) == "-") highLightIndex++;
        }

        if(highLightIndex>=strlen(newDataString)) highLightIndex = -1;
    }
}
void RtSa_Dialog_Digitinput::keyclockwiseControl()
{
    if(mShiftKeyPressed) return;
    if(blNumberInput){
        if(highLightIndex>=0&&highLightIndex<strlen(newDataString)){
            valueIncreaseControl();
        }
        else{
            getKnobValue(RTSA_CLOCKWISE);
        }
    }
}
void RtSa_Dialog_Digitinput::keyanticlockwiseControl()
{
    if(mShiftKeyPressed)
        return;
    if(blNumberInput){
        if(highLightIndex>=0&&highLightIndex<strlen(newDataString)){
            valueDecreaseControl();
        }
        else{
            getKnobValue(RTSA_ANTICLOCKWISE);
        }
    }
}
void RtSa_Dialog_Digitinput::valueIncreaseControl()
{
    /*char tempDataString[20];
    memset(tempDataString,0,sizeof(char)*20);

    for(int i = 0;i<strlen(newDataString);i++){
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
        for(int i = posAfter+bitsAfterDot+1;i<strlen(newDataString);i++){
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
    if(highLightIndex>=strlen(newDataString)) highLightIndex = -1;
}
void RtSa_Dialog_Digitinput::valueDecreaseControl()
{
    /*char tempDataString[20];
    memset(tempDataString,0,sizeof(char)*20);

    for(int i = 0;i<strlen(newDataString);i++){
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
            for(int i = pos+bitsAfterDot+1;i<strlen(newDataString);i++){
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
    if(highLightIndex>=strlen(newDataString)) highLightIndex = -1;
}
void RtSa_Dialog_Digitinput::getKnobValue(quint32 mode)
{
    QString strValue;

    switch (entryNo){
      case RTSA_INPUT_FREQ_CENTER:
      case RTSA_INPUT_FREQ_START:
      case RTSA_INPUT_FREQ_STOP:
      case RTSA_INPUT_LIMIT_FREQ:
      case RTSA_INPUT_FMT_FREQ:
        strValue = getNewFreqDataStringValue(mode,mControl->getCFStep(),unitNo);
        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());
        break;
      case RTSA_INPUT_FREQ_CF:
      case RTSA_INPUT_FREQ_SPAN:
      case RTSA_INPUT_MANUAL_RBW:
//      case INPUT_MANUAL_VBW:
      case RTSA_INPUT_MARKER_EDIT:
      case RTSA_INPUT_DELTA_MARKER_EDIT:
      case RTSA_INPUT_CHANNEL_BANDWIDTH:
      case RTSA_INPUT_CHANNEL_SPACING:
      case RTSA_INPUT_POWERSENSOR_FREQ:
        strValue = getNewFreqDataStringValue(mode,RTSA_MHZ,unitNo);
        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());
        break;
      case RTSA_INPUT_AVERAGE_COUNT:
    case RTSA_INPUT_LIMIT_SELECT_INDEX:
    case RTSA_INPUT_FMT_SELECT_INDEX:
        if(mode == RTSA_CLOCKWISE) strValue.sprintf("%d", atoi(newDataString)+1);
        else if(mode == RTSA_ANTICLOCKWISE) {
            if(atoi(newDataString) >= 1) strValue.sprintf("%d", atoi(newDataString)-1);
            else strValue = QString("%1").arg("0");
        }
        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());//Johnson 0630
        break;
//      case RTSA_INPUT_OCCUPIED://Johnson 1008 Add
//        if(mode == CLOCKWISE) strValue.sprintf("%.2f", atof(newDataString)+0.1);
//        else if(mode == ANTICLOCKWISE) {
//            if(atof(newDataString) >= 0.1) strValue.sprintf("%.2f", atof(newDataString)-0.1);
//            else strValue = QString("%1").arg("0");
//        }
//        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());
//        break;
      case RTSA_INPUT_SWEEP_TIME:
        if(unitNo == UNIT_NS) strValue = getNewSweepTimeDataStringValue(mode,1000000000.,unitNo);
        else if(unitNo == UNIT_US) strValue = getNewSweepTimeDataStringValue(mode,1000000.,unitNo);
        else if(unitNo == UNIT_MS) strValue = getNewSweepTimeDataStringValue(mode,1000.,unitNo);
        else if(unitNo == UNIT_S)  strValue = getNewSweepTimeDataStringValue(mode,1.,unitNo);
        qsnprintf(newDataString, sizeof(newDataString), "%s", strValue.toUtf8().constData());
        break;
      }
}
QString RtSa_Dialog_Digitinput::getNewFreqDataStringValue(int clockWiseMode,unsigned long long freStep,int unitNo)
{
    QString strValue;
    double unitGab = 0.;

    QString strGab;
    int pos = 0;
    unsigned long long freqVal;
    double newDataStringValue = strtod(newDataString,NULL);

    /*strValue.sprintf("%.3f", newDataStringValue);
    if(strchr(newDataString,'.')) {
        int prec = strlen(newDataString) - (strchr(newDataString,'.') - newDataString) - 1;
        freqVal = m_usr_variable->Round(freqVal,prec);
    }*/

    if(clockWiseMode == RTSA_CLOCKWISE){
        switch(unitNo) {
        case UNIT_GHZ:
            unitGab = (double) RTSA_GHZ;
            break;
        case UNIT_MHZ:
            unitGab = (double) RTSA_MHZ;
            break;
        case UNIT_KHZ:
            unitGab = (double) RTSA_KHZ;
            break;
        case UNIT_HZ:
            unitGab = (double) RTSA_HZ;
            break;
        }
        freqVal = freStep+newDataStringValue*unitGab;

        strGab = QString::number(freqVal, 'd',0);
        pos = m_usr_variable->notZeroPositionFindFunc(strGab);

        unitNo = m_usr_variable->freqUnitFindProc(freqVal);

        switch (unitNo) {
          case UNIT_GHZ:
            unitGab = (double) RTSA_GHZ;
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
            unitGab = (double) RTSA_MHZ;
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
            unitGab = (double) RTSA_KHZ;
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
            unitGab = (double) RTSA_HZ;
            strValue.sprintf("%.2f", (double) freqVal / unitGab);
            break;
          }
    }
    else if(clockWiseMode == RTSA_ANTICLOCKWISE){
        switch(unitNo) {
        case UNIT_GHZ:
            unitGab = (double) RTSA_GHZ;
            break;
        case UNIT_MHZ:
            unitGab = (double) RTSA_MHZ;
            break;
        case UNIT_KHZ:
            unitGab = (double) RTSA_KHZ;
            break;
        case UNIT_HZ:
            unitGab = (double) RTSA_HZ;
            break;
        }
        if(newDataStringValue*unitGab>=freStep)
            freqVal = newDataStringValue*unitGab-freStep;
        else /*return QString(newDataString)*/
            freqVal = 0;
        if(freqVal < 0) freqVal = 0;
        strGab = QString::number(freqVal, 'd',0);
        pos = m_usr_variable->notZeroPositionFindFunc(strGab);

        unitNo = m_usr_variable->freqUnitFindProc(freqVal);

        switch (unitNo) {
          case UNIT_GHZ:
            unitGab = (double) RTSA_GHZ;
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
            unitGab = (double) RTSA_MHZ;
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
            unitGab = (double) RTSA_KHZ;
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
            unitGab = (double) RTSA_HZ;
            strValue.sprintf("%.2f", (double) freqVal / unitGab);
            break;
          }
    }
    return strValue;
}
QString RtSa_Dialog_Digitinput::getNewSweepTimeDataStringValue(int clockWiseMode, double sweepTime, int unitNo)
{
    QString strValue;
    double unitGab = 0.;
    QString unitStr;

    QString strGab;
    int pos = 0;
    double _timeVal;

    double newDataStringValue = atof(newDataString);

    if(clockWiseMode == RTSA_CLOCKWISE){

        switch (unitNo) {
          case UNIT_NS:
            unitGab = (double) RTSA_GHZ;
            unitStr = QString("ns");

            _timeVal = sweepTime+newDataStringValue*RTSA_GHZ;
            strGab = QString::number(_timeVal, 'd',0);
            pos = m_usr_variable->notZeroPositionFindFunc(strGab);

            strValue.sprintf("%.0f", (double) _timeVal / unitGab);
            break;
          case UNIT_US:
            unitGab = (double) RTSA_MHZ;
            unitStr = QString("us");

            _timeVal = sweepTime+newDataStringValue*RTSA_MHZ;
            strGab = QString::number(_timeVal, 'd',0);
            pos = m_usr_variable->notZeroPositionFindFunc(strGab);

            strValue.sprintf("%.0f", (double) _timeVal / unitGab);
            break;
          case UNIT_MS:
            unitGab = (double) RTSA_KHZ;
            unitStr = QString("ms");

            _timeVal = sweepTime+newDataStringValue*RTSA_KHZ;
            strGab = QString::number(_timeVal, 'd',0);
            pos = m_usr_variable->notZeroPositionFindFunc(strGab);

            strValue.sprintf("%.0f", (double) _timeVal / unitGab);
            break;
          case UNIT_S:
            unitStr = QString("s");

            _timeVal = sweepTime+newDataStringValue;
            strGab = QString::number(_timeVal, 'd',0);
            pos = m_usr_variable->notZeroPositionFindFunc(strGab);

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
    else if(clockWiseMode == RTSA_ANTICLOCKWISE){
        switch (unitNo) {
          case UNIT_NS:
            unitGab = (double) RTSA_GHZ;
            unitStr = QString("ns");

            _timeVal = newDataStringValue*RTSA_GHZ-sweepTime;
            if(_timeVal < 0) _timeVal = 0;
            strGab = QString::number(_timeVal, 'd',0);
            pos = m_usr_variable->notZeroPositionFindFunc(strGab);

            strValue.sprintf("%.0f", (double) _timeVal / unitGab);
            break;
          case UNIT_US:
            unitGab = (double) RTSA_MHZ;
            unitStr = QString("us");

            _timeVal = newDataStringValue*RTSA_MHZ-sweepTime;
            if(_timeVal < 0) _timeVal = 0;
            strGab = QString::number(_timeVal, 'd',0);
            pos = m_usr_variable->notZeroPositionFindFunc(strGab);

            strValue.sprintf("%.0f", (double) _timeVal / unitGab);
            break;
          case UNIT_MS:
            unitGab = (double) RTSA_KHZ;
            unitStr = QString("ms");

            _timeVal = newDataStringValue*RTSA_KHZ-sweepTime;
            if(_timeVal < 0) _timeVal = 0;
            strGab = QString::number(_timeVal, 'd',0);
            pos = m_usr_variable->notZeroPositionFindFunc(strGab);

            strValue.sprintf("%.0f", (double) _timeVal / unitGab);
            break;
          case UNIT_S:
            unitStr = QString("s");

            _timeVal = newDataStringValue-sweepTime;
            if(_timeVal < 0) _timeVal = 0;
            strGab = QString::number(_timeVal, 'd',0);
            pos = m_usr_variable->notZeroPositionFindFunc(strGab);

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
void RtSa_Dialog_Digitinput::InitKeyboard()
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
void RtSa_Dialog_Digitinput::btn_clicked()
{
     QPushButton* btn = qobject_cast<QPushButton*>(sender());
     qint32 keyValue;
     keyValue = mBtnkey.find(btn).value();
     keyresponse(keyValue);
     return;
}
void RtSa_Dialog_Digitinput::keyresponse(qint32 keyValue)
{
    //Johnson 0608);
   int strLen = 0;
   strLen = strlen(newDataString);
   if (strLen >= 19 &&   keyValue != Qt::Key_Escape)
   {
       return;
   }

   switch(  keyValue)
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
       case RTSA_INPUT_AVERAGE_COUNT:
       case RTSA_INPUT_LIMIT_SELECT_INDEX:
       case RTSA_INPUT_FMT_SELECT_INDEX:
           if(strlen(newDataString) >= 6)
               return;
           break;
       case RTSA_INPUT_SWEEP_TIME:
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
       case RTSA_INPUT_AVERAGE_COUNT:
           if(atoi(newDataString) - 70000 >= 0)
           {
               strcpy(newDataString,"70000");
               return;
           }
           break;
       case RTSA_INPUT_SWEEP_TIME:
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

   switch (  keyValue)
   {
   case Qt::Key_Escape:
       backSpace();
       break;
//   case Qt::Key_Shift:
//       if(!mShiftKeyPressed)
//           mShiftKeyPressed = true;
//       else
//           mShiftKeyPressed = false;
//       break;
   case Qt::Key_0:
       if(mShiftKeyPressed){
           m_usr_variable->KeyNumber = 0;
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

               for(int i = 0;i<strlen(newDataString);i++){
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
       if(mShiftKeyPressed){
           m_usr_variable->KeyNumber = 1;
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

               for(int i = 0;i<strlen(newDataString);i++){
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
       if(mShiftKeyPressed){
           m_usr_variable->KeyNumber = 2;
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

               for(int i = 0;i<strlen(newDataString);i++){
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
       if(mShiftKeyPressed){
           m_usr_variable->KeyNumber = 3;
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

               for(int i = 0;i<strlen(newDataString);i++){
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
       if(mShiftKeyPressed){
           m_usr_variable->KeyNumber = 4;
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

               for(int i = 0;i<strlen(newDataString);i++){
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
       if(mShiftKeyPressed){
           m_usr_variable->KeyNumber = 5;
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

               for(int i = 0;i<strlen(newDataString);i++){
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
       if(mShiftKeyPressed){
           m_usr_variable->KeyNumber = 6;
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

               for(int i = 0;i<strlen(newDataString);i++){
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
       if(mShiftKeyPressed){
           m_usr_variable->KeyNumber = 7;
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

               for(int i = 0;i<strlen(newDataString);i++){
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
       if(mShiftKeyPressed){
           m_usr_variable->KeyNumber = 8;
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

               for(int i = 0;i<strlen(newDataString);i++){
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
       if(mShiftKeyPressed){
           m_usr_variable->KeyNumber = 9;
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

               for(int i = 0;i<strlen(newDataString);i++){
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
       if(mShiftKeyPressed)
           return;
       else
       {
           if(entryNo == RTSA_INPUT_FREQ_CENTER || entryNo == RTSA_INPUT_FREQ_START
                   || entryNo == RTSA_INPUT_FREQ_STOP || entryNo == RTSA_INPUT_FREQ_CENTER)
           {
               if(mControl->getFreqOffset() <= 0.00001 && mControl->getFreqOffset() >= -0.00001)
               {
                   return;
               }
           }
           else if(entryNo != RTSA_INPUT_CURVE && entryNo != RTSA_INPUT_REF_OFFSET && entryNo != RTSA_INPUT_DELTA_MARKER_EDIT && entryNo != RTSA_INPUT_REF_LEVEL
                   && entryNo != RTSA_INPUT_FREQ_OFFSET && entryNo != RTSA_INPUT_LIMIT_AMPT && entryNo != RTSA_INPUT_FMT_AMPT && entryNo != RTSA_INPUT_TRIGGER_LEVEL)
               return;
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

                          //Johnson 0709
                          QString strnewData(newDataString);
                          if(strnewData.mid(highLightIndex,1) == "."||strnewData.mid(highLightIndex,1) == "-") highLightIndex++;
                          if(highLightIndex>=strlen(newDataString)) highLightIndex = -1;
                       }
                       else if(DataNumber<0){
                           for(int i = 0;i<strlen(newDataString);i++){
                               newDataString[i] = newDataString[i+1];
                           }

                           if(bLeftKey||bRightKey) highLightIndex--;

                           //Johnson 0709
                           QString strnewData(newDataString);
                           if(strnewData.mid(highLightIndex,1) == "."||strnewData.mid(highLightIndex,1) == "-") highLightIndex++;
                           if(highLightIndex>=strlen(newDataString)) highLightIndex = -1;
                       }
                   }
                   else{
                       long DataNumber = atoi(newDataString);
                       memset(newDataString,0,sizeof(char)*20);
                       sprintf(newDataString,"%d",-DataNumber);

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
       if(mShiftKeyPressed) return;

       //if(strlen(newDataString)) blNumberInput = true;
       //else blNumberInput = false;
       keyleftControl();
       //blFirstIn = false;
       break;
   case Qt::Key_Right:
   case Qt::Key_F7:
       if(mShiftKeyPressed) return;

       //if(strlen(newDataString)) blNumberInput = true;
       //else blNumberInput = false;
       keyrightControl();
       //blFirstIn = false;
       break;
   case Qt::Key_Up:
   case Qt::Key_F8:
       if(mShiftKeyPressed) return;

       //if(strlen(newDataString)) blNumberInput = true;
       //else blNumberInput = false;
       keyupControl();
      // blFirstIn = false;
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
       if(entryNo == RTSA_INPUT_AVERAGE_COUNT || entryNo == RTSA_INPUT_FREQ_CHANNEL_NUM || entryNo == RTSA_INPUT_LIMIT_SELECT_INDEX
               || entryNo == RTSA_INPUT_FMT_SELECT_INDEX)
           return;
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
//qint32 RtSa_Dialog_Digitinput::getEntryNo()
//{
//    return entryNo;
//}
qint32 RtSa_Dialog_Digitinput::getUnitNo()
{
    return unitNo;
}
void RtSa_Dialog_Digitinput::clearEdit()
{
    memset(newDataString,0,sizeof(newDataString));
    strcpy(newDataString,"");
    ui->lblValue->setText(newDataString);
    return;
}
int RtSa_Dialog_Digitinput::freqSpecCompareFunc(int unitPos)
{
  QString strValue;
  qreal value = 0.;
  qreal freq = 0;
  unsigned long long calculatorFreq = 0;
  unsigned long long deltaFreq = 0;
  unsigned long long vigeoFreq = 0;

  int i = 0;
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
      freq = (qreal) ((qulonglong)(value * (double)RTSA_GHZ + 0.5));   // 1.2Ghz 입력시 1.9999999로 저장되어 + .5로 수정
      break;
    case 2:
      freq = (qreal) ((qulonglong)(value * (double)RTSA_MHZ + 0.5));
      break;
    case 3:
      freq = (qreal) ((qulonglong)(value * (double)RTSA_KHZ + 0.5));
      break;
    case 4:
      freq =  (qreal) ((qulonglong)(value * (double) RTSA_HZ + 0.5));
      break;
    }
  if(entryNo == RTSA_INPUT_DELTA_MARKER_EDIT)
  {
      if(minusFlag == 1)
      {
          freq = mControl->getMarkerRefFreq(mControl->getCurMarkerID()) - freq;
      }
      else
      {
          freq = mControl->getMarkerRefFreq(mControl->getCurMarkerID()) + freq;
      }
  }
  if(entryNo == RTSA_INPUT_FREQ_OFFSET || entryNo == RTSA_INPUT_FREQ_CENTER
          || entryNo == RTSA_INPUT_FREQ_START || entryNo == RTSA_INPUT_FREQ_STOP)
  {
      if(minusFlag == 1)
      {
          freq *= -1;
      }
  }

  m_usr_variable->entryInputMode = RTSA_NOT_USE;

  switch (entryNo)
  {
  case RTSA_INPUT_MANUAL_RBW:
      //0726
      if(1 == m_usr_variable->gSpanMode)
      {
          if(freq <= 3001)
          {
              this->close();
              return 0;
          }
      }
//      mControl->setBW(freq);
      return 1;
      break;
//  case INPUT_MANUAL_VBW:
//      mControl->setVbwValue(freq);
//      return 1;
//      break;
  }

  if ( m_usr_variable->gMenu ==  RTSA_MENU_SPECTRUM_ANALYZER) {
      switch (entryNo)  {
      case RTSA_INPUT_FREQ_CENTER:
          mControl->setCenterFreq(freq);
          break;
        case RTSA_INPUT_FREQ_START:
          mControl->setStartFreq(freq);
          break;
        case RTSA_INPUT_FREQ_STOP:
          mControl->setStopFreq(freq);
          break;
        case RTSA_INPUT_FREQ_CF:
          mControl->setCFStep(freq);
          break;
        case RTSA_INPUT_FREQ_SPAN:
          mControl->setSpan(freq);
          break;
        case RTSA_INPUT_FREQ_OFFSET:
          mControl->setFreqOffset(freq);
          break;
        case RTSA_INPUT_MARKER_EDIT:
          mControl->setMarkerRefFreq(mControl->getCurMarkerID(),freq);
          break;
        case  RTSA_INPUT_DELTA_MARKER_EDIT:
          mControl->setMarkerDeltaFreq(mControl->getCurMarkerID(),freq);
          break;
      case RTSA_INPUT_LIMIT_FREQ:
          mControl->setLimitCurPointFreq(freq/RTSA_MHZ,mControl->GetCurLimitDataIndex(),mControl->getCurLimit());
//          mControl->setLimitFreq(freq);
          break;
      case RTSA_INPUT_FMT_FREQ:
          mControl->setCurFmtFreqData(freq/RTSA_MHZ,mControl->getCurFmtDataIndex());
          break;

//        case RTSA_INPUT_CHANNEL_BANDWIDTH:
//          mControl->setChannelPower_ChannelBW(freq,m_usr_variable->ganamode);
//          break;
//        case RTSA_INPUT_CHANNEL_SPACING:
//          mControl->setACP_ChannelSP(freq,m_usr_variable->ganamode);
//          break;
        }
      m_usr_variable->entryInputMode = entryNo;

      return 1;
    }
  else
  {
      // Power Sensor의 Freq Input
      switch (entryNo)  {
        case RTSA_INPUT_POWERSENSOR_FREQ:

          m_usr_variable->gPowersensorFreq = freq;
          return 1;
          break;
        }
    }

  //added by Steve
  return 1;

}

int RtSa_Dialog_Digitinput::timeSpecCompareFunc(int unitPos)
{
    //0725 steve if fft mode,not change param
//    if(3 == m_usr_variable->ganamode)
//      {
//        this->close();
//        return 0;
//      }

  QString strValue;
  double value = 0.;
  double  _time = 0;

  strValue = newDataString;
  value = strValue.toDouble();


  //steve 0713 back to ms
  switch (unitPos)
  {
    case 4:  //s
      _time = (value * (double)RTSA_MHZ);
      break;
    case 3:  //ms
      _time = (value * (double)RTSA_KHZ);
      break;
    case 2: //us
      _time = value;
//      _time =  (value / (double)RTSA_KHZ);
      break;
    case 1: //ns
      _time =  value  / (double)RTSA_KHZ;
      break;
    }


  m_usr_variable->entryInputMode = RTSA_NOT_USE;

//  //Johnson 1126 limit the value's range
//  if(m_usr_variable->gZeroSpanAction) {
//      if(ZEROSPAN_SWEEPTIMEMIN > _time) _time = ZEROSPAN_SWEEPTIMEMIN;
//      else if(ZEROSPAN_SWEEPTIMEMAX < _time) _time = ZEROSPAN_SWEEPTIMEMAX;
//  }
//  else {
//      if(NOZEROSPAN_SWEEPTIMEMIN > _time) _time = NOZEROSPAN_SWEEPTIMEMIN;
//      else if(NOZEROSPAN_SWEEPTIMEMAX < _time) _time = NOZEROSPAN_SWEEPTIMEMAX;
//  }

  switch (entryNo)
  {
  case RTSA_INPUT_PERSISTENCE_TIME:
      mControl->setPersistenceTime(_time);
      break;
  case RTSA_INPUT_ACQ_TIME:
      mControl->setAcqTime(_time);
      break;
  case RTSA_INPUT_TRIGGER_DELAY_VALUE:
      mControl->setTriggerDelay(mControl->getTrigger(),_time);
      break;
  case RTSA_INPUT_TRIGGER_PERTIMER:
      mControl->setTriggerPeriodTime(_time);
      break;
  case RTSA_INPUT_TRIGGER_HOLDTIME:
      mControl->settriggerHoldOffTime(mControl->getTrigger(),_time);
      break;
    case RTSA_INPUT_SWEEP_TIME:
//      mControl->setSweepTime(_time);
//      globalUserVariable->gSweepTime = _time;
      //0713
//      globalUserVariable->gmanSettimems = globalUserVariable->gSweepTime;
      break;
    }

//  globalUserVariable->entryInputMode = entryNo;

  return 1;
}

int RtSa_Dialog_Digitinput::amptdSpecCompareFunc(int unitNo)
{
    QString strValue;
    double value = 0.;
    double tempVal = 0.;

    QString strWarning;//Johnson 0918
    qint32 AmptUnit;
    //Johnson 0709
    strValue = newDataString;
    value = strValue.toDouble();

    //Johnson 0919 Change
    switch (entryNo)
    {
    case RTSA_INPUT_REF_LEVEL: //Johnson 0918
        mControl->setRefLevel(value);
        break;
    case RTSA_INPUT_REF_OFFSET: //Johnson 0918
        mControl->setRefOffset(value);
        break;
    case RTSA_INPUT_POWERSENSOR_EXT_OFFSET:
        //Johnson 1106
        if(value > 0)
            value = 0;
        if ( 0 >= value)
        {
            m_usr_variable->gPowersensorExtOffset = value;
        }
        break;
    case RTSA_INPUT_ATTEN:
        mControl->setAttenVal(value);
        break;
    case RTSA_INPUT_SCALEDIV:
        mControl->setScaleDiv(value);
        break;
    case RTSA_LIMIT_EDGE:
        mControl->setMargin(mControl->getCurLimit(),value);
        break;
    case RTSA_INPUT_MARGIN:
        mControl->setMargin(mControl->getCurLimit(),value);
        break;
    case RTSA_INPUT_AVERAGE_COUNT:
        mControl->setAvgNum(mControl->getCurTrace(),value);
        break;
    case RTSA_INPUT_LIMIT_SELECT_INDEX:
        mControl->SetCurLimitDataIndex(value - 1);
        break;
    case RTSA_INPUT_FREQ_CHANNEL_NUM:
        mControl->setChannelNumber(value);
        break;
    case RTSA_INPUT_LIMIT_AMPT:
        mControl->setLimitCurPointAmpt(value,mControl->GetCurLimitDataIndex(),mControl->getCurLimit());
        break;
    case RTSA_INPUT_FMT_AMPT:
        mControl->setCurFmtAmptData(value,mControl->getCurFmtDataIndex());
        break;
    case RTSA_INPUT_TRIGGER_LEVEL:
        mControl->setTriggerLevel(mControl->getTrigger(),value);
        break;
    case RTSA_INPUT_FMT_SELECT_INDEX:
        mControl->setCurFmtDataIndex(value - 1);
        break;
//        mControl->setLimitCurPointAmpt(
//    case RTSA_INPUT_XDB:
//        mControl->setOccupiedBW_XdB(value,m_usr_variable->ganamode);
//        break;
     }
    return 1;
}

void RtSa_Dialog_Digitinput::on_freqBtnUnit1_clicked()
{
    int retNo = 0;
    int butNo = 1;

    //judgeRange(1);

    //if (atof(oldDataString) - atof(newDataString) == 0&&unitNo == 1)
    if(!strcmp(oldDataString,newDataString) && unitNo == 1){
        this->close();
        return;
    }

    if (entryNo ==  RTSA_INPUT_SWEEP_TIME)
        retNo = timeSpecCompareFunc(butNo);
    else
        retNo = freqSpecCompareFunc(butNo);

    if (retNo == 1)
    {
        this->close();
        emit finishEntry(entryNo);
    }
}

void RtSa_Dialog_Digitinput::on_freqBtnUnit2_clicked()
{
    int retNo = 0;
    int butNo = 2;

    if(!strcmp(oldDataString,newDataString) && unitNo == 2)
    {
        this->close();
        return;
      }

    if (entryNo ==  RTSA_INPUT_SWEEP_TIME)
      retNo = timeSpecCompareFunc(butNo);
    else
      retNo = freqSpecCompareFunc(butNo);

    if (retNo == 1)
      {
        this->close();
        emit finishEntry(entryNo);
      }
    return ;
}

void RtSa_Dialog_Digitinput::on_freqBtnUnit3_clicked()
{
    int retNo = 0;
    int butNo = 3;

    if(!strcmp(oldDataString,newDataString) && unitNo == 3)
    {
        this->close();
        return;
    }

    if (entryNo ==  RTSA_INPUT_SWEEP_TIME)
        retNo = timeSpecCompareFunc(butNo);
    else
        retNo = freqSpecCompareFunc(butNo);

    if (retNo == 1)
    {
        this->close();
        emit finishEntry(entryNo);
    }
    return ;
}

void RtSa_Dialog_Digitinput::on_freqBtnUnit4_clicked()
{
    int retNo = 0;
    int butNo = 4;
    int value = 0;
    double occupiedValue = 0.;
    QString strValue;

    if(!strcmp(oldDataString,newDataString) && unitNo == 4){
        this->close();
        return;
      }


    switch (entryNo)
    {
    case RTSA_INPUT_AVERAGE_COUNT:
        strValue = ui->lblValue->text();
        value = strValue.toInt();
        mControl->setAvgNum(mControl->getCurTrace(),value);
        retNo = 1;
        break;
    case RTSA_INPUT_LIMIT_SELECT_INDEX:
        strValue = ui->lblValue->text();
        value = strValue.toInt();
        mControl->SetCurLimitDataIndex(value - 1);
        retNo = 1;
        break;
    case RTSA_INPUT_SWEEP_TIME:
        retNo = timeSpecCompareFunc(butNo);
        break;
//    case RTSA_INPUT_OCCUPIED://Johnson 1008 Add
//        strValue = ui->lblValue->text();
//        occupiedValue = strValue.toDouble();
//        mControl->setOccupiedBW_OccBW(occupiedValue,m_usr_variable->ganamode);
//        retNo = 1;
//        break;
    case RTSA_INPUT_FMT_SELECT_INDEX:
        strValue = ui->lblValue->text();
        value = strValue.toInt();
        mControl->setCurFmtDataIndex(value - 1);
        retNo = 1;
        break;
    default:
        retNo = freqSpecCompareFunc(butNo);
        break;
    }

    if (retNo == 1)
    {
        this->close();
        emit finishEntry(entryNo);
    }
    return ;
}

void RtSa_Dialog_Digitinput::on_amptBtnUnit1_clicked()
{
    qreal value = 0;
    qint32 retNo = 0;
    if(!strcmp(oldDataString,newDataString) && unitNo == 1)
    {
        this->close();
        return;
    }
    if(entryNo == RTSA_INPUT_PERSISTENCE_TIME || entryNo == RTSA_INPUT_ACQ_TIME || entryNo == RTSA_INPUT_TRIGGER_DELAY_VALUE
            || entryNo == RTSA_INPUT_TRIGGER_PERTIMER || entryNo == RTSA_INPUT_TRIGGER_HOLDTIME)
    {
        retNo = timeSpecCompareFunc(UNIT_S);
    }
    else
        retNo = amptdSpecCompareFunc(unitNo);
    if (retNo == 1)
      {
        this->close();
        emit finishEntry(entryNo);
      }
    return;
}

void RtSa_Dialog_Digitinput::on_amptBtnUnit2_clicked()
{
    qreal value = 0;
    qint32 retNo = 0;
    if(!strcmp(oldDataString,newDataString) && unitNo == 2)
    {
        this->close();
        return;
    }
    if(entryNo == RTSA_INPUT_PERSISTENCE_TIME || entryNo == RTSA_INPUT_ACQ_TIME || entryNo == RTSA_INPUT_TRIGGER_DELAY_VALUE
            || entryNo == RTSA_INPUT_TRIGGER_PERTIMER || entryNo == RTSA_INPUT_TRIGGER_HOLDTIME)
    {
        retNo = timeSpecCompareFunc(UNIT_MS);
    }
    else
        retNo = amptdSpecCompareFunc(unitNo);
    if (retNo == 1)
      {
        this->close();
        emit finishEntry(entryNo);
      }
    return;
}

void RtSa_Dialog_Digitinput::on_amptBtnUnit3_clicked()
{
    qreal value = 0;
    qint32 retNo = 0;
    if(!strcmp(oldDataString,newDataString) && unitNo == 3)
    {
        this->close();
        return;
    }
    if(entryNo == RTSA_INPUT_PERSISTENCE_TIME || entryNo == RTSA_INPUT_ACQ_TIME || entryNo == RTSA_INPUT_TRIGGER_DELAY_VALUE
            || entryNo == RTSA_INPUT_TRIGGER_PERTIMER || entryNo == RTSA_INPUT_TRIGGER_HOLDTIME)
    {
        retNo = timeSpecCompareFunc(UNIT_US);
    }
    else
        retNo = amptdSpecCompareFunc(unitNo);
    if (retNo == 1)
      {
        this->close();
        emit finishEntry(entryNo);
      }
    return;
}

void RtSa_Dialog_Digitinput::on_amptBtnUnit4_clicked()
{
    qreal value = 0;
    qint32 retNo = 0;
    if(!strcmp(oldDataString,newDataString) && unitNo == 4)
    {
        this->close();
        return;
    }
    if(entryNo == RTSA_INPUT_HIGHEST_DENSITY || entryNo == RTSA_INPUT_LOWEST_DENSITY \
            || entryNo == RTSA_INPUT_CURVE || entryNo == RTSA_SPECTROGTAM_CURSOR_INDEX)
    {
        retNo = enterFunc();
    }
    else if(entryNo == RTSA_INPUT_PERSISTENCE_TIME || entryNo == RTSA_INPUT_ACQ_TIME || entryNo == RTSA_INPUT_TRIGGER_DELAY_VALUE
            || entryNo == RTSA_INPUT_TRIGGER_PERTIMER || entryNo == RTSA_INPUT_TRIGGER_HOLDTIME)
    {
        retNo = timeSpecCompareFunc(UNIT_NS);
    }
    else
        retNo = amptdSpecCompareFunc(unitNo);
    if (retNo == 1)
      {
        this->close();
        emit finishEntry(entryNo);
      }
    return;
}

void RtSa_Dialog_Digitinput::on_amptBtnUnit5_clicked()
{
    qreal value = 0;
    qint32 retNo = 0;
    if(!strcmp(oldDataString,newDataString) && unitNo == 5)
    {
        this->close();
        return;
    }
    retNo = amptdSpecCompareFunc(unitNo);
    if (retNo == 1)
      {
        this->close();
        emit finishEntry(entryNo);
      }
    return;
}

void RtSa_Dialog_Digitinput::on_amptBtnUnit6_clicked()
{
    qreal value = 0;
    qint32 retNo = 0;
    if(!strcmp(oldDataString,newDataString) && unitNo == 6)
    {
        this->close();
        return;
    }
    retNo = amptdSpecCompareFunc(unitNo);
    if (retNo == 1)
      {
        this->close();
        emit finishEntry(entryNo);
      }
    return;
}

void RtSa_Dialog_Digitinput::on_amptBtnUnit7_clicked()
{
    qreal value = 0;
    qint32 retNo = 0;
    if(!strcmp(oldDataString,newDataString) && unitNo == 7)
    {
        this->close();
        return;
    }
    retNo = amptdSpecCompareFunc(unitNo);
    if (retNo == 1)
      {
        this->close();
        emit finishEntry(entryNo);
      }
    return;
}

//void RtSa_Dialog_Digitinput::on_timeBtnUnit1_clicked()
//{
//    qreal value = 0;
//    qint32 retNo = 0;
////    if(!strcmp(oldDataString,newDataString) && unitNo == 1)
////    {
////        this->close();
////        return;
////    }
//    retNo = timeSpecCompareFunc(UNIT_NS);
//    if (retNo == 1)
//      {
//        this->close();
//        emit finishEntry(entryNo);
//      }
//    return;
//}

//void RtSa_Dialog_Digitinput::on_timeBtnUnit2_clicked()
//{
//    qreal value = 0;
//    qint32 retNo = 0;
////    if(!strcmp(oldDataString,newDataString) && unitNo == 2)
////    {
////        this->close();
////        return;
////    }
//    retNo = timeSpecCompareFunc(unitNo);
//    if (retNo == 1)
//      {
//        this->close();
//        emit finishEntry(UNIT_US);
//      }
//    return;
//}

//void RtSa_Dialog_Digitinput::on_timeBtnUnit3_clicked()
//{
//    qreal value = 0;
//    qint32 retNo = 0;
////    if(!strcmp(oldDataString,newDataString) && unitNo == 3)
////    {
////        this->close();
////        return;
////    }
//    retNo = timeSpecCompareFunc(UNIT_MS);
//    if (retNo == 1)
//      {
//        this->close();
//        emit finishEntry(entryNo);
//      }
//    return;
//}

//void RtSa_Dialog_Digitinput::on_timeBtnUnit4_clicked()
//{
//    qreal value = 0;
//    qint32 retNo = 0;
//    if(entryNo == RTSA_INPUT_HIGHEST_DENSITY || entryNo == RTSA_INPUT_LOWEST_DENSITY \
//            || entryNo == RTSA_INPUT_CURVE)
//    {
//        retNo = enterFunc();
//    }
//    else
//    {
//        retNo = timeSpecCompareFunc(UNIT_S);
//    }
//    if (retNo == 1)
//      {
//        this->close();
//        emit finishEntry(entryNo);
//      }
//    return;
//}
int RtSa_Dialog_Digitinput::enterFunc()
{
    QString strValue;
    qreal dbvalue = 0.;
    qint32 value = 0;

    strValue = newDataString;
    dbvalue = strValue.toDouble();
    value = (qint32)dbvalue;
    switch(entryNo)
    {
    case RTSA_INPUT_HIGHEST_DENSITY:
        mControl->setHighestDensity(value);
        break;
    case RTSA_INPUT_LOWEST_DENSITY:
        mControl->setLowestDensity(value);
        break;
    case RTSA_INPUT_CURVE:
        mControl->setCurve(value);
        break;
    case RTSA_SPECTROGTAM_CURSOR_INDEX:
        mControl->setspectrogramCursorIndex(mControl->getspectrogramCursorID(),value);
        break;
    }
    return 1;
}

//void RtSa_Dialog_Digitinput::on_btnClear_clicked()
//{
//    memset(newDataString,0,sizeof(newDataString));
//    strcpy(newDataString,"");
//    ui->lblValue->setText(newDataString);
//    return;
//}
void RtSa_Dialog_Digitinput::clearAll()
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
