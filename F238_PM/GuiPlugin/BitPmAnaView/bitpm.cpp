#include "bitpm.h"
#include "ui_pm.h"
#include "pm_user_variable.h"
#include <QDebug>
#include "rect_define.h"
#include <QFile>
#include <QKeyEvent>
#include <math.h>
#include <QMessageBox>
#include "data_conversion.h"
BitPm::BitPm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BitPm),
     mWarningSetUp(NULL),
    mCurSetupDialog(NULL),
    mCurMenuID(-1),
    mIsZoomIn(false),
    mShiftKeyPressed(false),
    mDragFlag(false),
    touchSignal(0),
    mStyleIndex(-1)
{
    qDebug()<<"A new Pm Start \n"
            <<"--------------------------------------------------------------------------------------------------------------------------\n"
            <<"--------------------------------------------------------------------------------------------------------------------------\n"<< endl;

    setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setFocusPolicy(Qt::StrongFocus);
    ui->setupUi(this);


    //modifier main window to user size
    this->resize(PM_WINDOW_WIDTH,PM_WINDOW_HEIGHT);
    this->setAttribute(Qt::WA_NoChildEventsFromChildren,true);
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    this->setAttribute(Qt::WA_StyledBackground,true);
    // this function must initial at first.

    initGlobalInterface();

    initThread();
    InitBitview();
    initWidget();
    InitAllDialog();

    //set qss mode for indoor,outdoor or night;
    this->setProperty("status",pm_qssMode[PmInterfaceObj->getSystemDisplay()]);

    InitLeftInfoWidget();
    InitFileManager();

    //    PmInterfaceObj->m_pPmComm->openPowerPort();
    //    PmInterfaceObj->cmd_GetSensorInventoryData();
    //    PmInterfaceObj->m_BitViewGauageDial->setCurentPoint(0);

    m_nAverage = 0;
    m_fAveTotleForward = 0.0;
    m_fAveTotleReverse = 0.0;
    m_fZeroTotleForward= 0.0;
    m_fZeroTotleReverse= 0.0;
    m_nZeroNum = 0;
}

BitPm::~BitPm()
{
    m_thread->pm_thread_state = 0;
    QThread::msleep(200);
    m_thread->quit();  // Thread quit
    delete UserVariableObj;
    delete PmInterfaceObj;
    delete mBtnGroup;
    deleteWidget();
    delete ui;

}

/**
* @brief init bitview
* @note
* @author Roc
* @since  2019.11.5
*/
void BitPm::InitBitview()
{
    PmInterfaceObj->InitBitView(this);
}

///**
//* @brief init stylesheet
//* @note
//* @author Roc
//* @since  2019.11.5
//*/
//void BitPm::InitStyleSheet(qint32 index)
//{
//    if(mStyleIndex == index)
//        return;
//    mStyleIndex = index;
//    QString filename[3]={":/pm/stylesheet/default.qss",":/pm/stylesheet/night.qss",":/pm/stylesheet/outdoor.qss"};
//    QFile qss(filename[mStyleIndex]);
//    if(!qss.open(QFile::ReadOnly))
//    {
//        qCritical("Pm qss file open failed");
//        return;
//    }
//    this->setStyleSheet(qss.readAll());
//    qss.close();
//    this->setProperty("status",pm_qssMode[PmInterfaceObj->getSystemDisplay()]);

//    return;
//}
/**
* @brief init bitview
* @note
* @author Roc
* @since  2019.11.5
*/
void BitPm::deleteWidget()
{
    this->setFocus();
    return;
}

void BitPm::connectStatusChange(qint32 pStatus)
{
    if(PmInterfaceObj->pSocketLinkStatus != pStatus)
    {
        PmInterfaceObj->pSocketLinkStatus = pStatus;
    }
    return;
}

void BitPm::menuClose()
{
    if(mCurSetupDialog != NULL)
    {
        mCurSetupDialog->hide();
        if(mCurSetupDialog == mFreqSetup)
        {
            mFreqSetup->HideChStdDialog();
        }
        this->setUpdatesEnabled(false);
    }
    if(mWarningSetUp != NULL)
    {

        delete mWarningSetUp;
        mWarningSetUp = NULL;
    }
    mDigitInput->hide();
    this->setUpdatesEnabled(true);
    return;
}

/**
* @brief
* @param
* @author Roc
* @since  2019.11.5
*/
void BitPm::InitAllDialog()
{
    mFreqSetup = new Pm_Dialog_FreqSetup(PmInterfaceObj,mDigitInput,this);
    mFreqSetup->move(1,65);

    mAmptSetup = new Pm_Dialog_AmptSetup(PmInterfaceObj,mDigitInput,this);
    mAmptSetup->move(1,65);

    mSweepSetup = new Pm_Dialog_SweepSetup(PmInterfaceObj,mDigitInput,this);
    mSweepSetup->move(1,65);

    mAverageSetup = new Pm_Dialog_AverageSetup(PmInterfaceObj,mDigitInput,this);
    mAverageSetup->move(1,65);

    mZeroSetup = new Pm_Dialog_ZeroSetup(PmInterfaceObj,mDigitInput,this);
    mZeroSetup->move(1,65);

    mLimitSetup = new Pm_Dialog_Limit(PmInterfaceObj,mDigitInput,this);
    mLimitSetup->move(1,65);

    mDisplaySetup = new Pm_Dialog_DisplaySetup(PmInterfaceObj,mDigitInput,this);
    mDisplaySetup->move(1,65);

    mAllSetup = new Pm_Dialog_AllSetup(PmInterfaceObj,mDigitInput,this);
    mAllSetup->setGeometry(1,mapToGlobal(QPoint(1,-50)).y(),1278,763);
    mAllSetup->move(0,0);

    mQuickSave = new Pm_Dialog_QuickSave(this, PmInterfaceObj->getSystemDisplay());
    mQuickSave->setGeometry(135,155,1010,490);

    return;
}

/**
* @brief init interface, all I/O control interface
* @note
* @author Roc
* @since  2019.11.5
*/
void BitPm::initGlobalInterface()
{
    // Single instantiation Pm_User_Variable
    UserVariableObj = new Pm_User_Variable(this);
    PmInterfaceObj = new BitPm_Interface(this);
    PmInterfaceObj->setGobalVariable(UserVariableObj);
    connect(PmInterfaceObj,SIGNAL(ParentFocus()),this,SLOT(setDialogActive()));
    connect(PmInterfaceObj,SIGNAL(RedrawInfoShow(qint32)),this,SLOT(leftInfo_Update(qint32)));


    connect(PmInterfaceObj->m_pPmComm, SIGNAL(FinishPower(QByteArray)), this, SLOT(anaylysisPower(QByteArray)));
    connect(PmInterfaceObj->m_pPmComm, SIGNAL(FinishSysInfo(QByteArray)), PmInterfaceObj, SLOT(anaSystemInfo(QByteArray)));
    connect(PmInterfaceObj->m_pPmComm, SIGNAL(FinishCalRead(QByteArray)), PmInterfaceObj, SLOT(anaAmptCal(QByteArray)));

    connect(PmInterfaceObj,SIGNAL(ZeroDlgClose()),this,SLOT(waringZeroClose()));
    connect(PmInterfaceObj,SIGNAL(ZeroDlgShow()),this,SLOT(waringZeroShow()));
    connect(PmInterfaceObj,SIGNAL(ZeroDlgSleep(qint32)),this,SLOT(waringZeroSleep(qint32)));
}

/**
* @brief init data thread
* @note
* @author Roc
* @since  2019.11.5
*/
void BitPm::initThread()
{
    m_thread = new Pm_ThreadGraph(this);
    m_thread->setInterface(PmInterfaceObj);
    m_thread->start();
    connect(PmInterfaceObj,SIGNAL(setThreadContinous(qint32)),this,SLOT(thread_setContinous(qint32)));
    connect(m_thread,SIGNAL(findCommPort(qint32,QString)),PmInterfaceObj,SLOT(analysisCommPort(qint32,QString)));

}

void BitPm::thread_setContinous(qint32 nContinous)
{
    m_thread->SetContinuousFlg(nContinous);
}

/**
* @brief  Initialization widget.
* @param  void
* @return void
* @author Roc
* @since  2019.11.5
*/
void BitPm::initWidget(void)
{
    mBtnGroup = new QButtonGroup();
    mBtnGroup->setExclusive(true);
    mBtnGroup->addButton(ui->topButton1,PM_FREQ_DIALOG);
    mBtnGroup->addButton(ui->topButton2,PM_AMPT_DIALOG);
    mBtnGroup->addButton(ui->topButton3,PM_SWEEP_DIALOG);

    mBtnGroup->addButton(ui->topButton4,PM_AVERAGE_DIALOG);
    mBtnGroup->addButton(ui->topButton5,PM_ZERO_DIALOG);
    //    mBtnGroup->addButton(ui->topButton6,PM_TRACE_DIALOG);
    //    mBtnGroup->addButton(ui->topButton7,PM_MARKER_DIALOG);
    mBtnGroup->addButton(ui->topButton8,PM_LIMIT_DIALOG);
    mBtnGroup->addButton(ui->topButton9,PM_DISPLAY_DIALOG);
    //    mBtnGroup->addButton(ui->topButton10,PM_MEAS_TOOL_DIALOGL);
     mBtnGroup->addButton(ui->topButton11,PM_ALLSET_DIALOG);

    connect(mBtnGroup,SIGNAL(buttonToggled(int, bool)),this,SLOT(menuHide(int, bool)));
    connect(mBtnGroup,SIGNAL(buttonClicked(int)),this,SLOT(menuShow(int)));

    mDigitInput = new Pm_Dialog_Digitinput(this);
    mDigitInput->setInterface(PmInterfaceObj);

    mCurSetupDialog = new Pm_Dialog_FreqSetup(PmInterfaceObj,mDigitInput,this);
    return ;
}
/**
* @brief change size
* @note
* @author	Roc
* @since	2019.11.19
*/
void BitPm::resizeEvent(QResizeEvent *event)
{
    this->setFocus();
    PmInterfaceObj->changeSize(this->width(),this->height());
    if(mIsZoomIn)
    {
       PmInterfaceObj->setZoomIn();
    }
    else
    {
        PmInterfaceObj->setZoomOut();
    }
//    InitStyleSheet(0);
    return;
}

/**
* @brief BitPm::keyPressEvent
* @param event
 */
void BitPm::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        if(UserVariableObj->gLocal == PM_REMOTE)
        {
            if(!event->isAutoRepeat())
            {
                if(touchSignal == 1)
                {
//                    ui->rightButton4->setChecked(false);
//                    touchSignal = 0;
                    emit KeyEventSig(event->key() + 3);
                }
                emit KeyEventSig(Qt::Key_Escape);
            }
        }
        else
        {
            if(!event->isAutoRepeat())
            {
                if(touchSignal == 1)
                {
//                    ui->rightButton4->setChecked(false);
//                    touchSignal = 0;
                    emit KeyEventSig(event->key() + 2);
                }
                else
                {
//                    emit KeyEventSig(event->key() + 1);
                }
            }
        }
        UserVariableObj->gLocal = PM_LOCAL;
        menuClose();
        return;
    }
    else if(event->key() == Qt::Key_PowerOff)
    {
        if(!event->isAutoRepeat())
        {
            emit KeyEventSig(Qt::Key_PowerOff);
        }
        return;
    }
    if(UserVariableObj->gLocal == PM_REMOTE)
    {
        return;
    }
    if(!mDigitInput->isHidden())
    {
        if(event->key() == Qt::Key_F3 || event->key() == Qt::Key_Up \
           || event->key() == Qt::Key_F8 || event->key() == Qt::Key_Down \
           || event->key() == Qt::Key_F9 || event->key() == Qt::Key_F4)
        {
            mDigitInput->close();
        }
        else
        {
            mDigitInput->keyresponse(event->key());
            return;
        }
    }
    else
    {
        if(mCurSetupDialog != NULL)
        {
            if(!mCurSetupDialog->isHidden())
                mCurSetupDialog->setFocus();
        }
    }
    keyRespond(event->key());
    return;
}
void BitPm::keyRespond(qint32 key)
{
    if(touchSignal)
    {
        return;
    }
    qreal freq = 0;
    qreal freqstep = 0;
    switch(key)
    {
    case Qt::Key_F3:
    case Qt::Key_Up:
    case Qt::Key_F8:
//        MenuClose();
        switch(mCurMenuID)
        {
        case PM_FREQ_DIALOG:
            PmInterfaceObj->setCenterFreq(PmInterfaceObj->getCenterFreq() + PmInterfaceObj->getStepFreq());
            break;
        case PM_AMPT_DIALOG:
//            PmInterfaceObj->setRefLevel(PmInterfaceObj->getRefLevel() + 1);
//            break;
            break;
        default:
            break;
        }
        break;
    case Qt::Key_Down:
    case Qt::Key_F9:
    case Qt::Key_F4:
        menuClose();
        switch(mCurMenuID)
        {
        case PM_FREQ_DIALOG:
            if(PmInterfaceObj->getStepFreq() >= PmInterfaceObj->getCenterFreq())
            {
                PmInterfaceObj->setCenterFreq(0);
            }
            else
            {
                PmInterfaceObj->setCenterFreq(PmInterfaceObj->getCenterFreq() - PmInterfaceObj->getStepFreq());
            }
            break;

        }
        break;
    case Qt::Key_Shift:
        if(mShiftKeyPressed)
            mShiftKeyPressed = false;
        else
            mShiftKeyPressed = true;
        break;
    case Qt::Key_0:
        if(mShiftKeyPressed)
        {
            emit SysSetSig();
            mShiftKeyPressed = false;
        }
        break;
    case Qt::Key_1:
        if(mShiftKeyPressed)
        {
            mCurMenuID = PM_FREQ_DIALOG;
            menuShow(mCurMenuID);
            mShiftKeyPressed = false;
            mBtnGroup->button(PM_FREQ_DIALOG)->setChecked(true);
        }
        break;
    case Qt::Key_2:
        if(mShiftKeyPressed)
        {
//              V_PM_sem(pm_homeuiHandle);
//            mCurMenuID = PM_FREQ_DIALOG;
//            menuShow(mCurMenuID);
            mShiftKeyPressed = false;
        }
        break;
    case Qt::Key_3:
        if(mShiftKeyPressed)
        {
            mCurMenuID = PM_AMPT_DIALOG;
            menuShow(mCurMenuID);
            mShiftKeyPressed = false;
            mBtnGroup->button(PM_AMPT_DIALOG)->setChecked(true);
        }
        break;
    case Qt::Key_4:
        if(mShiftKeyPressed)
        {
//            mCurMenuID = PM_MEASURE_DIALOG;
//            menuShow(mCurMenuID);
//            mShiftKeyPressed = false;
//            mBtnGroup->button(PM_MEASURE_DIALOG)->setChecked(true);
        }
        break;
    case Qt::Key_5:
        if(mShiftKeyPressed)
        {
            mCurMenuID = PM_DISPLAY_DIALOG;
            menuShow(mCurMenuID);
            mShiftKeyPressed = false;
            mBtnGroup->button(PM_DISPLAY_DIALOG)->setChecked(true);
        }
        break;
    case Qt::Key_6:
        if(mShiftKeyPressed)
        {
//            mCurMenuID = PM_MEAS_TOOL_DIALOGL;
//            menuShow(mCurMenuID);
//            mShiftKeyPressed = false;
//            mBtnGroup->button(PM_MEAS_TOOL_DIALOGL)->setChecked(true);
        }
    case Qt::Key_7:
        if(mShiftKeyPressed)
        {
//            mCurMenuID = PM_OBSERVE_DIALOG;
//            menuShow(mCurMenuID);
//            mShiftKeyPressed = false;
//            mBtnGroup->button(PM_OBSERVE_DIALOG)->setChecked(true);
        }
        break;
    case Qt::Key_8:
        if(mShiftKeyPressed)
        {
//            PmInterfaceObj->setMarkerOn(PmInterfaceObj->getCurMarkerID(),PM_LAYER_LEFT);
//            PmInterfaceObj->setMarkerToCenter();
//            mShiftKeyPressed = false;
        }
        break;
    case Qt::Key_9:
        if(mShiftKeyPressed)
        {
//            mCurMenuID = PM_MARKER_DIALOG;
//            menuShow(mCurMenuID);
//            mShiftKeyPressed = false;
//            mBtnGroup->button(PM_MARKER_DIALOG)->setChecked(true);
        }
        break;
    case Qt::Key_Minus:  // - Minus
    case Qt::Key_F2:    //  +/-
        if(mShiftKeyPressed)
        {
            ui->topButton1->setChecked(true);
//            mBtnGroup->checkedButton()->setChecked(false);
//            InterfaceObj->PltSaveConditions(PM_STATE_DEFAULT_FILE);
//            InterfaceObj->loadState(PM_DEFAULT_COND);

            mShiftKeyPressed = false;
            emit PltAllPresetSig();
        }
        break;
    case Qt::Key_Period:  // . Dot
        if(mShiftKeyPressed)
        {/*
            mCurMenuID = PM_TRACE_DIALOG;
            menuShow(mCurMenuID);
            mShiftKeyPressed = false;
            mBtnGroup->button(PM_TRACE_DIALOG)->setChecked(true);*/
        }
        break;
    default:
        break;
    }
    return;
}
/**
* @brief BitPm::mousePressEvent
 * here must consider set dialog focus, in order to respond keypress
* @param event
 */
void BitPm::mousePressEvent(QMouseEvent *event)
{
    if(UserVariableObj->gLocal == PM_REMOTE)
    {
        if(mCurSetupDialog != NULL)
        {
            delete mCurSetupDialog;
            mCurSetupDialog = NULL;
        }
        return;
    }
    if(mCurSetupDialog != NULL)
    {
        if(!mCurSetupDialog->isHidden())
            mCurSetupDialog->setFocus();
    }
    return;
}

void BitPm::waringZeroClose()
{
    if(mWarningSetUp != NULL)
    {
        mWarningSetUp->close();
        delete mWarningSetUp;
        mWarningSetUp = NULL;
    }

}

void BitPm::waringZeroShow()
{
    setAttribute(Qt::WA_X11DoNotAcceptFocus, true);
    QString strText = "Please wait...\n\nCount down   " + QString::number(PM_ZERO_CALIBRATION_NUM) + "   s";
    mWarningSetUp = new Pm_Dialog_Warning("Zeroing",strText,this,PmInterfaceObj->getSystemDisplay());

    mWarningSetUp->NoShowButton();
    mWarningSetUp->show();
}

void BitPm::waringZeroSleep(qint32 nTime)
{
    QString strText = "Please wait...\n\nCount down   " + QString::number(PM_ZERO_CALIBRATION_NUM - nTime) + "   s";

    if(mWarningSetUp != NULL)
        mWarningSetUp->SerWaringText(strText);

}
/**
* @brief graph draw function
* @note
* @Author	ROC
* @date	2019.11.20
*/
void BitPm::anaylysisPower(QByteArray arrayData)
{
    qreal fForwardAvgdBm,fReverseAvgdBm;
    qreal fForwardAvgmW,fReverseAvgmW;
    qreal fForwardPowerData = 0.0,fReversePowerData = 0.0;

    if(PmInterfaceObj->IsZero())
    {
        //  dBm = 10*lg(mW /1)  ==>  mW =pow(10 ,dbm/10);
        if(POWER_SENSOR_V90 == PmInterfaceObj->getPowerSensorFlg())
        {
            fForwardAvgdBm = QByteArrayByLowHToqint16(arrayData,2)/100.;
            fForwardAvgmW = pow(10, fForwardAvgdBm/10.0);
        }
        else
        {
            fForwardAvgdBm = QByteArrayByLowHToqint32(arrayData,8)/100.;
            fForwardAvgmW = pow(10, fForwardAvgdBm/10.);
            fReverseAvgdBm = QByteArrayByLowHToqint32(arrayData,12)/100.;
            fReverseAvgmW = pow(10, fReverseAvgdBm/10.);
        }
        m_fZeroTotleForward += fForwardAvgmW;
        m_fZeroTotleReverse += fReverseAvgmW;
        m_nZeroNum++;
        if(m_nZeroNum < PM_ZERO_CALIBRATION_NUM)
        {
            waringZeroSleep(m_nZeroNum);
        }
        else
        {
            PmInterfaceObj->setForwardZero( m_fZeroTotleForward / (qreal)m_nZeroNum);
            PmInterfaceObj->setReverseZero( m_fZeroTotleReverse / (qreal)m_nZeroNum);
            m_fZeroTotleForward = 0.0;
            m_fZeroTotleReverse = 0.0;
            m_nZeroNum = 0;
            PmInterfaceObj->setZero(false);
            waringZeroClose();
        }
    }
    else
    {
        if(POWER_SENSOR_V90 == PmInterfaceObj->getPowerSensorFlg())
        {
            PmInterfaceObj->m_curSensorData.fTempeture =  QByteArrayByLowHToqint16(arrayData,0)/10.;

            fForwardAvgdBm = QByteArrayByLowHToqint16(arrayData,2)/100.;

            fForwardAvgmW =  pow(10, (fForwardAvgdBm + PmInterfaceObj->getAmptOffset()) / 10.);
            fForwardAvgmW = fForwardAvgmW - PmInterfaceObj->getForwardZero();
            if(fForwardAvgmW <0)
                fForwardAvgmW =  pow(10,-9);

            fForwardPowerData =  fForwardAvgmW *100/(qreal) PmInterfaceObj->getDutyCycle();

            if(PmInterfaceObj->IsRunningAverage())
            {
                m_fAveTotleForward += fForwardPowerData;
                m_nAverage++;
                if(m_nAverage < PmInterfaceObj->getAveragePoint())
                {
                }
                else
                {
                    PmInterfaceObj->m_curSensorData.fPowerDatamW = m_fAveTotleForward / (qreal)m_nAverage;
                    m_nAverage = 0;
                    m_fAveTotleForward = 0;
                }
            } else
            {
                PmInterfaceObj->m_curSensorData.fPowerDatamW = fForwardPowerData;
            }

            if(PmInterfaceObj->getForwardRelativeCurFlg())
            {
                PmInterfaceObj->setAmptForwardRelativeData(PmInterfaceObj->m_curSensorData.fPowerDatamW);
                PmInterfaceObj->setForwardRelativeCurFlg(false);
            }
        }
        else if(POWER_SENSOR_V91 == PmInterfaceObj->getPowerSensorFlg())
        {
            fForwardAvgdBm = QByteArrayByLowHToqint32(arrayData,8)/100.;
            fForwardAvgmW = pow(10, (fForwardAvgdBm + PmInterfaceObj->getAmptOffset())/10.);
            fForwardAvgmW = fForwardAvgmW - PmInterfaceObj->getForwardZero();

            fReverseAvgdBm = QByteArrayByLowHToqint32(arrayData,12)/100.;
            fReverseAvgmW = pow(10, (fReverseAvgdBm + PmInterfaceObj->getAmptOffset())/10.);
            fReverseAvgmW = fReverseAvgmW - PmInterfaceObj->getReverseZero();


            PmInterfaceObj->m_curSensorData.fTempeture =  QByteArrayByLowHToqint16(arrayData,24)/10.;
            PmInterfaceObj->m_curSensorData.fForwardDirect= QByteArrayByLowHToqint32(arrayData,0)/100.;
            PmInterfaceObj->m_curSensorData.fReverseDirect = QByteArrayByLowHToqint32(arrayData,4)/100.;

            if(fForwardAvgmW <0)
                fForwardAvgmW =  pow(10,-9);
            fForwardPowerData = fForwardAvgmW *100/ (qreal)PmInterfaceObj->getDutyCycle();
            if(fReverseAvgmW <0)
                fReverseAvgmW =  pow(10,-9);
            fReversePowerData = fReverseAvgmW *100/ (qreal)PmInterfaceObj->getDutyCycle();

            if(PmInterfaceObj->IsRunningAverage())
            {
                m_fAveTotleForward += fForwardPowerData;
                m_fAveTotleReverse += fReversePowerData;
                m_nAverage++;
                if(m_nAverage < PmInterfaceObj->getAveragePoint())
                {
                    ;
                }
                else
                {
                    PmInterfaceObj->m_curSensorData.fForwardAvemW = m_fAveTotleForward / (qreal)m_nAverage;
                    PmInterfaceObj->m_curSensorData.fReverseAvemW = m_fAveTotleReverse / (qreal)m_nAverage;
                    m_fAveTotleForward = 0;
                    m_fAveTotleReverse = 0;
                    m_nAverage = 0;
                }
            }
            else
            {
                PmInterfaceObj->m_curSensorData.fForwardAvemW = fForwardPowerData;
                PmInterfaceObj->m_curSensorData.fReverseAvemW = fReversePowerData;
            }

            PmInterfaceObj->m_curSensorData.fForwardPeak = QByteArrayByLowHToqint32(arrayData,16)/100.;
            PmInterfaceObj->m_curSensorData.fReversePeak = QByteArrayByLowHToqint32(arrayData,20)/100.;
            if(PmInterfaceObj->getForwardRelativeCurFlg())
            {
                PmInterfaceObj->setAmptForwardRelativeData(10*log10(PmInterfaceObj->m_curSensorData.fForwardAvemW));
                PmInterfaceObj->setForwardRelativeCurFlg(false);
            }
            if(PmInterfaceObj->getReverseRelativeCurFlg())
            {
                PmInterfaceObj->setAmptReverseRelativeData(10*log10(PmInterfaceObj->m_curSensorData.fReverseAvemW));
                PmInterfaceObj->setReverseRelativeCurFlg(false);
            }
        }

        //    PmInterfaceObj->m_curSensorData.fForwardAve = -7.32;
        //    PmInterfaceObj->m_curSensorData.fReversedAve = 0.91;
        //    PmInterfaceObj->m_curSensorData.fForwardPeak = 18.01;
        //    PmInterfaceObj->m_curSensorData.fReversePeak =0;

        PmInterfaceObj->m_curSensorData.nPointNo++;
        anaylysisRevc(PmInterfaceObj->m_curSensorData);
        graphRefreshFunc();
    }
    return;
}


void BitPm::anaylysisRevc(_PM_SENSOR_DATA &sensorData)
{
    qreal fForwarAvgdW,fReverseAvgW,fForwarPeakdW;

    //dBm ->    W
    fForwarAvgdW = sensorData.fForwardAvemW /1000.0 ;
    fReverseAvgW = sensorData.fReverseAvemW / 1000.0;

    fForwarPeakdW =  pow(10, sensorData.fForwardPeak / 10.)/1000.0;

    if(0 != fForwarAvgdW)
        sensorData.fCrestFactor = qAbs(10 * log10(fForwarPeakdW / fForwarAvgdW));

    //方法1
        if(0 != fForwarAvgdW)
            sensorData.fReturnLoss = 10 * log10(fForwarAvgdW / fReverseAvgW);

         sensorData.fReflCoeff = pow(10,-1 * (sensorData.fReturnLoss /20.0));

//    //方法2
//    if(0 != fForwarAvgdW)
//        sensorData.fReflCoeff = sqrt(fReverseAvgW / fForwarAvgdW);
//    sensorData.fReturnLoss = 20.0 * qAbs(log10(sensorData.fReflCoeff));

    if(1 != sensorData.fReflCoeff)
        sensorData.fVSWR = (1 + sensorData.fReflCoeff)/(1 - sensorData.fReflCoeff);
}
/**
* @brief graph draw function
* @note
* @Author	ROC
* @date	2019.11.20
*/
void BitPm::graphRefreshFunc()
{
    if(PmInterfaceObj->getDrawFlag())
        return;
    PmInterfaceObj->Draw();
    return;
}
/**
* @brief  Show or hide bullet windows.
* @param  menuID    Bullet windows id.
* @param  visible   [true]--show windows [flase]--hide windows
* @return void
* @Author	ROC
* @date	2019.12.4
*/
void BitPm::menuHide(qint32 menuID, bool visible)
{
    return;
}

/**
* @brief  Show or hide bullet windows.
* @param  menuID    Bullet windows id.
* @param  visible   [true]--show windows [flase]--hide windows
* @return void
* @Author	ROC
* @date	2019.12.4
*/
void BitPm::menuShow(qint32 menuID)
{
    if(UserVariableObj->gLocal == PM_REMOTE)
    {
        return;
    }
    if(menuID < 0)
        return;
    if(menuID == mCurMenuID && (!mCurSetupDialog->isHidden()))
        return;
    switch(menuID)
    {
    case PM_FREQ_DIALOG:
        menuClose();
        mFreqSetup->initDisplay();
        mCurSetupDialog = mFreqSetup;
        break;
    case PM_AMPT_DIALOG:
        menuClose();
        mAmptSetup->initDisplay();
        mCurSetupDialog = mAmptSetup;
        break;
    case PM_SWEEP_DIALOG:
        menuClose();
        mSweepSetup->initDisplay();
        mCurSetupDialog = mSweepSetup;
        break;
    case PM_AVERAGE_DIALOG:
        menuClose();
        mAverageSetup->initDisplay();
        mCurSetupDialog = mAverageSetup;
        break;
    case PM_ZERO_DIALOG:
        menuClose();
        mZeroSetup->initDisplay();
        mCurSetupDialog = mZeroSetup;
        break;
    case PM_LIMIT_DIALOG:
        menuClose();
        mLimitSetup->initDisplay();
        mCurSetupDialog = mLimitSetup;
        break;
    case PM_DISPLAY_DIALOG:
        menuClose();
        mDisplaySetup->initDisplay();
        mCurSetupDialog = mDisplaySetup;
        break;
    case PM_ALLSET_DIALOG:
        menuClose();
        mAllSetup->initDisplay();
        mCurSetupDialog = mAllSetup;
        break;
    case PM_SCREEN_CAPTURE_DIALOG:
        mCurSetupDialog = mQuickSave;
        mCurSetupDialog->setGeometry(135,155,1010,490);
       break;
    default:
        return;
        break;
    }
//    connect(mCurSetupDialog,SIGNAL(destroyed()),this,SLOT(setActive()));
    mCurMenuID = menuID;
    mCurSetupDialog->setProperty("status",pm_qssMode[PmInterfaceObj->getSystemDisplay()]);
    mCurSetupDialog->setStyle(QApplication::style());
    if(menuID == PM_SCREEN_CAPTURE_DIALOG)
    {
        qobject_cast<QDialog*>(mCurSetupDialog)->exec();
    }
    else
    {
        mCurSetupDialog->setProperty("status",pm_qssMode[PmInterfaceObj->getSystemDisplay()]);
        mCurSetupDialog->setStyle(QApplication::style());
        mCurSetupDialog->show();
        mCurSetupDialog->setFocus();
    }

    return ;
}

/**
* @brief zoom button slot
* @param
* @Author	ROC
* @date     2019.12.17
*/
void BitPm::on_rightButton8_clicked()
{
    menuClose();
    emit SysSetSig();
    ui->rightButton8->setChecked(false);
    return;
}

void BitPm::on_rightButton9_clicked()
{
  ui->rightButton9->setChecked(true);
  return;
}
void BitPm::on_rightButton10_clicked()
{
    menuClose();
    if(mIsZoomIn)
    {
        mIsZoomIn = false;
        PmInterfaceObj->setZoomFlag(mIsZoomIn);
        this->setGeometry(1,52,1278,713);
        ShowWidget();
    }
    else
    {
        mIsZoomIn = true;
        PmInterfaceObj->setZoomFlag(mIsZoomIn);

        this->setGeometry(0,0,1280,765);
        HideWidget();
    }
    return;
}

void BitPm::HideWidget()
{
    mDigitInput->hide();
    ui->topButtonBar->hide();
    ui->pm_leftInfoWidget->hide();
    ui->rightButtonBar->move(1196,0);
    ui->rightButtonBar->resize(84,763);
    ui->rightButton10->move(3,763 - 55);

    return;
}
void BitPm::ShowWidget()
{
    ui->topButtonBar->show();
    if(!PmInterfaceObj->getDragFlag())
        ui->pm_leftInfoWidget->show();
    ui->rightButtonBar->resize(84,648);
    ui->rightButtonBar->move(1195,65);
    ui->rightButton10->move(3,591);

    return;
}

void BitPm::InitLeftInfoWidget()
{
    connect(ui->widget_mode,SIGNAL(clicked()),this,SLOT(on_WidgetClicked()));
    connect(ui->widget_Freq,SIGNAL(clicked()),this,SLOT(on_WidgetClicked()));
    connect(ui->widget_Sweep,SIGNAL(clicked()),this,SLOT(on_WidgetClicked()));
    connect(ui->widget_Ampt,SIGNAL(clicked()),this,SLOT(on_WidgetClicked()));
    connect(ui->widget_Average,SIGNAL(clicked()),this,SLOT(on_WidgetClicked()));
//    connect(ui->widget_Zero,SIGNAL(clicked()),this,SLOT(on_WidgetClicked()));
    connect(ui->widget_Limit,SIGNAL(clicked()),this,SLOT(on_WidgetClicked()));
    connect(ui->widget_mode,SIGNAL(clicked()),this,SLOT(on_WidgetClicked()));


    mPmInfoWidget = new QMap<Pm_ClickedWidget*,qint32>;
    mPmInfoWidget->insert(ui->widget_Freq,PM_FREQ_DIALOG);
    mPmInfoWidget->insert(ui->widget_Sweep,PM_SWEEP_DIALOG);
    mPmInfoWidget->insert(ui->widget_Ampt,PM_AMPT_DIALOG);
    mPmInfoWidget->insert(ui->widget_Average,PM_AVERAGE_DIALOG);
//    mPmInfoWidget->insert(ui->widget_Zero,PM_ZERO_DIALOG);
    mPmInfoWidget->insert(ui->widget_Limit,PM_LIMIT_DIALOG);
    mPmInfoWidget->insert(ui->widget_mode,PM_DISPLAY_DIALOG);
}
void BitPm::MenuClose()
{
    menuClose();
    return;
}

/**
* @brief BitPm::setActive
 * this function is used for dialog close,
 * because mCurSetupDialog has already destroyed,
 * here just set NULL.
 */
void BitPm::setActive()
{
    mQuickSave = NULL;
    if(PmInterfaceObj->isShiftKeyEnable())
    {
        keyRespond(Qt::Key_Shift);
        PmInterfaceObj->setShiftKeyEnable(false);
    }
    if(mWarningSetUp != NULL)
    {
        delete mWarningSetUp;
        mWarningSetUp = NULL;
    }
    PmInterfaceObj->DrawFlag(false);
    this->setFocus();
    return;
}
void BitPm::ClockKeyDown()
{
    mDigitInput->close();
    mCurSetupDialog->setFocus();
    return;
}
void BitPm::setDialogActive()
{
    if(mCurSetupDialog != NULL)
    {
        mCurSetupDialog->setFocus();
    }
    if(mWarningSetUp != NULL)
    {
        delete mWarningSetUp;
        mWarningSetUp = NULL;
    }
    return;
}

/**
* @brief	界面左侧信息栏隐藏按钮
* @note
* @Author	ROC
* @date     2019.12.16
*/
void BitPm::on_pb_Drag_clicked()
{
    menuClose();
    if(mDragFlag)
    {
        mDragFlag = false;
        PmInterfaceObj->setDragFlag(mDragFlag);
        ui->widget_Drag->move(254,65);
        ui->pm_leftInfoWidget->show();
    }
    else
    {
        mDragFlag = true;
        PmInterfaceObj->setDragFlag(mDragFlag);
        ui->widget_Drag->move(2,65);
        ui->pm_leftInfoWidget->hide();
    }
    return;
}

/**
* @brief	刷新界面左侧信息栏
* @note
* @Author	ROC
* @date     2019.12.16
*/
void BitPm::leftInfo_Update(qint32 infoID)
{
    bool boolGab = false;
    QString strGab = "";
    qint32 intGab = 0;
    qint32 intCurAvg = 0;
    qreal fGab = 0.0;
    switch(infoID)
    {
    case PM_LABEL_MODE:
        intGab = PmInterfaceObj->getPowerSensorFlg();
        switch(intGab)
        {
        case POWER_SENSOR_V90:
            strGab = "V90 Average Power Sensor";
            break;
        case POWER_SENSOR_V91:
            strGab = "V91 Directional Power Sensor";
            break;
        default :
            strGab = "";
            break;
        }
        ui->lblmode->setText(strGab);

        intGab = PmInterfaceObj->getDisplayMode();
        switch(intGab)
        {
        case PM_DISPLAY_FORWARD_AVERAGE:
            strGab = ">Forward Average";
            break;
        case PM_DISPLAY_FORWARD_CF:
            strGab = ">Forward Crest Factor";
            break;
        case PM_DISPLAY_FORWARD_PEP:
            strGab = ">Forward Peak Envelope Power";
            break;
        case PM_DISPLAY_FORWARD_CCDF:
            strGab = ">Forward CCDF";
            break;
        case PM_DISPLAY_FORWARD_MODULATION:
            strGab = ">Forward Modulation";
            break;
        case PM_DISPLAY_REVERSE_AVERAGE:
            strGab = ">Reverse Average";
            break;
        case PM_DISPLAY_REVERSE_RC:
            strGab = ">Reverse Refl. Coeff.";
            break;
        case PM_DISPLAY_REVERSE_RL:
            strGab = ">Reverse Return Loss";
            break;
        case PM_DISPLAY_REVERSE_VSWR:
            strGab = ">Reverse VSWR";
            break;
        case PM_DISPLAY_SUMMARY:
            strGab = ">Summary";
            break;
        default:
            strGab = "";
            break;
        }

        ui->lblmeasure->setText(strGab);
        emit MesPlatTitleSig(intGab /*- 1*/);
        break;
    case PM_LABEL_CENTER_FREQ:
        strGab = PmInterfaceObj->getFreqAdjustStr(PmInterfaceObj->getCenterFreq());
        ui->lblCenterFreqValue->setText(strGab);
        intGab = PmInterfaceObj->IsOffset();
        if(1 == intGab)
            ui->lblCenterFreq->setText("Offset Center Freq");
        else
            ui->lblCenterFreq->setText("Center Freq");
        break;
    case PM_LABEL_START_FREQ:
        strGab = PmInterfaceObj->getFreqAdjustStr(PmInterfaceObj->getStartFreq());
        ui->lblStartFreqValue->setText(strGab);
        intGab = PmInterfaceObj->IsOffset();
        if(1 == intGab)
            ui->lblStartFreq->setText("Offset Start Freq");
        else
            ui->lblStartFreq->setText("Start Freq");
        break;
    case PM_LABEL_STOP_FREQ:
        strGab = PmInterfaceObj->getFreqAdjustStr(PmInterfaceObj->getStopFreq());
        ui->lblStopFreqValue->setText(strGab);
        intGab = PmInterfaceObj->IsOffset();
        if(1 == intGab)
            ui->lblStopFreq->setText("Offset Stop Freq");
        else
            ui->lblStopFreq->setText("Stop Freq");
        break;
    case PM_LABEL_SPAN:
        strGab = PmInterfaceObj->getFreqAdjustStr(PmInterfaceObj->getSpan());
        ui->lblSpanValue->setText(strGab);
        break;
    case PM_LABEL_SIGNAL_STANDARD:
        if(UserVariableObj->gMeterParam.gConfig_Freq.nChannelStd < 0 || !UserVariableObj->IsFreqInCurChStd())
        {
            strGab = "None";
        }
        else
        {
            strGab = QString(mPM_ChStand[UserVariableObj->gMeterParam.gConfig_Freq.nChannelStd].name);
        }
        ui->lblCHStandardValue->setText(strGab);
        break;
    case PM_LABEL_CHANNEL:
        if(UserVariableObj->gMeterParam.gConfig_Freq.nChannelStd < 0 || !UserVariableObj->IsFreqInCurChStd())
        {
            strGab = "None";
        }
        else
        {
            strGab = QString::number(PmInterfaceObj->getChannelNumber());
        }
        ui->lblChannelValue->setText(strGab);
        break;

    case PM_LABEL_SWEEP:
        intGab = PmInterfaceObj->IsSweepContinous();
        if(intGab == PM_SINGLE)
        {
            ui->lblSweepType->setText("Single");
            ui->lblTimInterval->setText("---- s");
        }
        else
        {
            ui->lblSweepType->setText("Continuous");
            strGab = QString::number(PmInterfaceObj->getSweepTime()) + QString("  s");
            ui->lblTimInterval->setText(strGab);
        }
        if(POWER_SENSOR_V91 == PmInterfaceObj->getPowerSensorFlg())
         {
             ui->lblMeasureOffset->setText("Duty Cycle");
             strGab = QString::number(PmInterfaceObj->getDutyCycle()) + QString("  %");
             ui->lblMeasureOffsetValue->setText(strGab);
         }

        break;
//    case PM_LABEL_ZERO:
//        intGab = PmInterfaceObj->IsZero();
//        if(intGab == true)
//        {
//            ui->lblZeroValue->setText("On");
//        }
//        else
//        {
//            ui->lblZeroValue->setText("Off");
//        }
//        break;
    case PM_LABEL_OFFSET:
        fGab = PmInterfaceObj->getAmptOffset();
        strGab = QString::number(fGab) + QString("  dB");
        ui->lblOffsetValue->setText(strGab);
        break;
    case PM_LABEL_FORWARD:
        intGab = PmInterfaceObj->IsAmptForwardRelative();
        if(intGab == true)
        {
            ui->lblSetForward->setText("On");
        }
        else
        {
            ui->lblSetForward->setText("Off");
        }
        if(POWER_SENSOR_V90 == PmInterfaceObj->getPowerSensorFlg())
        {
            ui->lblForward->setText("Relative");
        }
        else if(POWER_SENSOR_V91 == PmInterfaceObj->getPowerSensorFlg())
        {
            ui->lblForward->setText("Forward Relative");
        }
        strGab = QString::number(PmInterfaceObj->getAmptForwardRelativeData()) + QString("  dB");
        ui->lblForwardValue->setText(strGab);
        break;
    case PM_LABEL_REVERSE:
        if(POWER_SENSOR_V90 == PmInterfaceObj->getPowerSensorFlg())
        {
            ui->lblReverse->setText("----");
            ui->lblSetReverse->setText("--");
            strGab = QString("---- dB");
            ui->lblReverseValue->setText(strGab);
        }
        else if(POWER_SENSOR_V91 == PmInterfaceObj->getPowerSensorFlg())
        {
            ui->lblReverse->setText("Reverse Relative");
            boolGab = PmInterfaceObj->IsAmptReverseRelative();
            if(boolGab == true)
            {
                ui->lblSetReverse->setText("On");
            }
            else
            {
                ui->lblSetReverse->setText("Off");
            }
            strGab = QString::number(PmInterfaceObj->getAmptReverseRelativeData()) + QString("  dB");
            ui->lblReverseValue->setText(strGab);
        }
        break;
    case PM_LABEL_ACQ:
        intGab = PmInterfaceObj->IsAcqType();
        if(intGab == 0)
        {
            ui->lblAcquisitionValue->setText("FAST");
        }
        else if(intGab == 1)
        {
            ui->lblAcquisitionValue->setText("MED");
        }
        else
        {
            ui->lblAcquisitionValue->setText("SLOW");
        }
        break;
    case PM_LABEL_AVERAGE:
        boolGab = PmInterfaceObj->IsRunningAverage();
        intCurAvg = PmInterfaceObj->getAveragePoint();
        if(boolGab == true)
        {
            ui->lblAverageFlg->setText("On");
            strGab = QString("1/") + QString::number(intCurAvg);
        }
        else
        {
            ui->lblAverageFlg->setText("Off");
            strGab = QString("--/--");
        }
        ui->lblAverageValue->setText(strGab);
        break;
    case PM_LABEL_MAXHOLD:
        intGab = PmInterfaceObj->IsMaxHold();
        if(intGab == true)
        {
            ui->lblMaxHoldValue->setText("On");
        }
        else
        {
            ui->lblMaxHoldValue->setText("Off");
        }
        break;
    case PM_LABEL_LIMIT:
        intGab = PmInterfaceObj->IsLimit();
        if(intGab == true)
        {
            ui->lblLimitValue->setText("On");
        }
        else
        {
            ui->lblLimitValue->setText("Off");
        }
        break;

    case PM_LABEL_FORWARD_UP:
        strGab = QString::number(PmInterfaceObj->getForwardUpperLimt()) + QString("  dBm");
        ui->lblForwardUpperValue->setText(strGab);

        if(POWER_SENSOR_V90 == PmInterfaceObj->getPowerSensorFlg())
            ui->lblForwardUpper->setText("Upper");
        else if(POWER_SENSOR_V91 == PmInterfaceObj->getPowerSensorFlg())
            ui->lblForwardUpper->setText("Forward Upper");

        break;
    case PM_LABEL_FORWARD_LOW:
        strGab = QString::number(PmInterfaceObj->getForwardLowerLimt()) + QString("  dBm");
        ui->lblForwardLowerValue->setText(strGab);

        if(POWER_SENSOR_V90 == PmInterfaceObj->getPowerSensorFlg())
            ui->lblForwardLower->setText("Lower");
        else if(POWER_SENSOR_V91 == PmInterfaceObj->getPowerSensorFlg())
            ui->lblForwardLower->setText("Forward Lower");
        break;
    case PM_LABEL_REVERSE_UP:
        if(POWER_SENSOR_V90 == PmInterfaceObj->getPowerSensorFlg())
        {
            ui->lblReverseUpperValue->setText("----");
            ui->lblReverseUpper->setText("----");
        }
        else if(POWER_SENSOR_V91 == PmInterfaceObj->getPowerSensorFlg())
        {

            ui->lblReverseUpper->setText("Reverse Upper");
            strGab = QString::number(PmInterfaceObj->getReverseUpperLimt()) + QString("  dBm");
            ui->lblReverseUpperValue->setText(strGab);
        }

        break;
    case PM_LABEL_REVERSE_LOW:
        if(POWER_SENSOR_V90 == PmInterfaceObj->getPowerSensorFlg())
        {
            ui->lblReverseLower->setText("----");
            ui->lblReverseLowerValue->setText("----");
        }
        else if(POWER_SENSOR_V91 == PmInterfaceObj->getPowerSensorFlg())
        {

            ui->lblReverseLower->setText("Reverse Lower");
            strGab = QString::number(PmInterfaceObj->getReverseLowerLimt()) + QString("  dBm");
            ui->lblReverseLowerValue->setText(strGab);
        }
        break;

    case PM_LABEL_DISPLAY:
        this->setProperty("status",pm_qssMode[PmInterfaceObj->getSystemDisplay()]);
        setStyle(QApplication::style());
        break;
    default:
        break;
    }
    return;
}

void BitPm::on_WidgetClicked()
{
    qint32 index;
    Pm_ClickedWidget* widget = qobject_cast<Pm_ClickedWidget*>(sender());
    index = mPmInfoWidget->value(widget);
    mBtnGroup->button(index)->setChecked(true);
    menuShow(index);
    return;
}

/**
* @brief
* @param
* @Author	ROC
* @date     2019.12.17
*/
void BitPm::InitFileManager()
{
    mFileManager = new SAFileManager();
    connect(mFileManager,SIGNAL(loadFileSig(QString)),this,SLOT(LoadFilePara(QString)));
    connect(mFileManager,SIGNAL(saveFileSig(QString,qint32)),this,SLOT(saveFilePara(QString,qint32)));
    connect(mFileManager,SIGNAL(fastSaveFileSig(QString,int)),this,SLOT(quickSaveFilePara(QString,qint32)));
    connect(mFileManager,SIGNAL(fastSaveDialogClosed()),this,SLOT(on_fastSaveDialogClosed()));
    connect(mFileManager,SIGNAL(fileManagerWidgetClosed()),this,SLOT(on_fileManagerWidgetClosed()));
    return;
}

/**
* @brief BitPm::on_rightButton1_clicked
 * Peak search
 */
void BitPm::on_rightButton1_clicked()
{
    menuClose();
    return;
}
/**
* @brief BitPmVnc::on_rightButton3_clicked
 * auto scale
 */
void BitPm::on_rightButton3_clicked()
{
    menuClose();
    PmInterfaceObj->setAutoScale();
    mBtnGroup->button(PM_AMPT_DIALOG)->setChecked(true);
    return;
}

void BitPm::SetMeasureItems(qint32 imea)
{
    PmInterfaceObj->setSystemDisplay(imea);
    return;
}

void BitPm::on_rightButton4_clicked()
{
    touchSignal = !touchSignal;
    if(touchSignal)
    {
        emit KeyEventSig(Qt::Key_Escape + 1);
    }
    else
    {
        emit KeyEventSig(Qt::Key_Escape + 2);
    }
}
/**
* @brief
* @param
* @Author	ROC
* @date     2019.12.17
*/
void BitPm::on_rightButton2_clicked()
{
//    if(PmInterfaceObj->getCurBitviewType() != PM_SPECTRUM)
//    {
//        mWarningSetUp = new Pm_Dialog_Warning("Notice","Limit only be used in spectrum",this,PmInterfaceObj->GetDisplayMode());
//        mWarningSetUp->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
//        mWarningSetUp->ShowYesButtonOnly();
//        if(mWarningSetUp->exec() != QDialog::Accepted)
//        {
//            return;
//        }
//        return;
//    }
    menuClose();
    return;
}
/**
* @brief
* @param
* @Author	ROC
* @date     2019.12.17
*/
void BitPm::SetLocalRemoteMode(qint32 mode)
{
    UserVariableObj->gLocal = mode;
    if(mode == PM_REMOTE)
    {
        setAttribute(Qt::WA_TransparentForMouseEvents, true);
    }
    else
    {
        setAttribute(Qt::WA_TransparentForMouseEvents, false);
    }
    menuClose();
    return;
}
/**
* @brief
* @param
* @Author	ROC
* @date     2019.12.10
*/
void BitPm::on_rightButton7_clicked()
{
//    menuClose();
    PmInterfaceObj->DrawFlag(true);
    if(mQuickSave != NULL)
    {
        delete mQuickSave;
        mQuickSave = NULL;
    }
    mQuickSave = new Pm_Dialog_QuickSave(this,PmInterfaceObj->getSystemDisplay());
    mQuickSave->setGeometry(135,155,1010,490);
    connect(mQuickSave,SIGNAL(destroyed()),this, SLOT(setActive()));
    qobject_cast<QDialog*>(mQuickSave)->exec();
//    menuShow(PM_SCREEN_CAPTURE_DIALOG);
    return;
}
/**
* @brief
* @param
* @Author	ROC
* @date     2019.12.10
*/
void BitPm::on_rightButton6_clicked()
{
    menuClose();
    PmInterfaceObj->DrawFlag(true);
    mFileManager->showSaveDialog();
    return;
}
/**
* @brief
* @param
* @Author	ROC
* @date     2019.12.17
*/
void BitPm::ChangeLcdStateWithNoSig(qint32 ilock)
{
    touchSignal = ilock;
    if(ilock == 1)
    {
        ui->rightButton4->setChecked(true);
    }
    else
    {
       ui->rightButton4->setChecked(false);
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-21
*/
void BitPm::LoadFilePara(QString strPath)
{
    PmInterfaceObj->DrawFlag(true);
    PmInterfaceObj->parseFile(strPath);
    mFileManager->onSaveFinished(1);
//    InterfaceObj->loadState(strPath);
    return;
}
/**
* @brief
* @param
* @Author	ROC
* @date     2019.12.17
*/
void BitPm::saveFilePara(QString strPath, qint32 fileType)
{
    qint32 successFlag = 0;
    PmInterfaceObj->initFileType(fileType);
    //save File
    if(fileType == 1)
    {
        successFlag = PmInterfaceObj->saveState(strPath);
    }
    mFileManager->onSaveFinished(successFlag);
    return;
}
/**
* @brief
* @param
* @Author	ROC
* @date     2019.12.17
*/
void BitPm::quickSaveFilePara(QString strPath, qint32 fileType)
{
    qint32 successFlag = 0;;
    PmInterfaceObj->initFileType(fileType);
    //save File
    if(fileType == 1)
    {
        successFlag = PmInterfaceObj->saveState(strPath);
    }
    mFileManager->onFastSaveFinished(successFlag + 1);

    PmInterfaceObj->DrawFlag(false);
    return;
}
/**
* @brief
* @param
* @Author	ROC
* @date     2019.12.17
*/
void BitPm::on_fastSaveDialogClosed()
{
    PmInterfaceObj->DrawFlag(false);
    return;
}
/**
* @brief
* @param
* @Author	ROC
* @date     2019.12.17
*/
void BitPm::on_fileManagerWidgetClosed()
{
    PmInterfaceObj->DrawFlag(false);
    return;
}
/**
* @brief
* @param
* @author	Roc
* @since	2019.11.19
*/
void BitPm::on_rightButton5_clicked()
{
    menuClose();
    PmInterfaceObj->DrawFlag(true);
    mFileManager->showFileManagerWidget();
    return;
}
/**
* @brief
* @param
* @author	Roc
* @since	2019.11.19
*/
void BitPm::PltCurAnaMode(qint32 imode)
{
    PmInterfaceObj->PltCurAnaMode(imode);
    return;
}
/**
* @brief
* @param
* @author	Roc
* @since	2019.11.19
*/
qint32 BitPm::PltSavePres(qint32 itype)
{
    qint32 iback = -1;
    iback = PmInterfaceObj->PltSavePres(itype);
    return iback;
}

/**
* @brief
* @param
* @author	Roc
* @since	2019.11.19
*/
void BitPm::PltCurLinkMode(qint32 imode)
{
    PmInterfaceObj->PltCurLinkMode(imode);
    return;
}
/**
* @brief Platform setting link flag
* @param  Link Flg
* @author	Roc
* @since	2019.11.19
*/
qint32 BitPm::PltSaveLinkFlg(qint32 itype)
{
    qint32 ireturnData = -1;
    ireturnData = PmInterfaceObj->PltSaveLinkFlg(itype);
    return ireturnData;
}
/**
* @brief
* @param
* @author	Roc
* @since	2019.11.19
*/
qint32 BitPm::PltSaveConditions(qint32 itype)
{
    qint32 iback = -1;
    iback = PmInterfaceObj->PltSaveConditions(itype);
    return iback;
}
/**
* @brief
* @param
* @author	Roc
* @since	2019.11.19
*/
qint32 BitPm::PltLoadConditions(qint32 itype)
{
    qint32 iback = -1;
    iback = PmInterfaceObj->PltLoadConditions(itype);
    return iback;
}
/**
* @brief
* @param
* @author	Roc
* @since	2019.11.19
*/
void BitPm::PresetDefaultStates()
{
    PmInterfaceObj->loadState(PM_DEFAULT_COND);
    return;
}
/**
* @brief
* @param
* @author	Roc
* @since	2019.11.14
*/
void BitPm::SetDisplayMode(qint32 imode)
{
    PmInterfaceObj->setSystemDisplay(imode);
    return;
}
/**
* @brief
* @param
* @author	Roc
* @since	2019.11.19
*/
void BitPm::SetSysRefuiStates(qint32 itype)
{
    return;
}
