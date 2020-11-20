#include "bitrtsa.h"
#include "ui_bitrtsa.h"
#include "rtsa_user_variable.h"
#include <QDebug>
#include "rtsa_shared_memory.h"
#include "rect_define.h"
#include <QFile>
#include <QKeyEvent>
#include <math.h>
#include <QMessageBox>
#include "msgNoticeCode.h"
#include <QDebug>

extern int rtsa_homeuiHandle;
extern int RTSA_guiHandle;
extern void V_RTSA_sem(int handle);
extern pthread_mutex_t RTSA_lockobj;
extern _RTSA_SM_SYNC *sm_rtsa_sync;
BitRtSa::BitRtSa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BitRtSa),
    mIsZoomIn(false),
    mCurMenuID(-1),
    mCurSetupDialog(NULL),
    mShiftKeyPressed(false),
//    mLastAcqTime(0),
    mDragFlag(false),
    touchSignal(0),
    mWarningSetUp(NULL),
    mStyleIndex(-1),
    mLimit(NULL)
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    ui->setupUi(this);

    initNoticeCode(APPLICATION_PROGRAM);
//    this->setFocus();
//    this->setFocusPolicy(Qt::StrongFocus);
    RtSa_init_shared_memory();
    //modifier main window to user size
//    this->resize(RTSA_WINDOW_WIDTH,RTSA_WINDOW_HEIGHT);
//    this->setAttribute(Qt::WA_NoChildEventsFromChildren,true);
//    this->setAttribute(Qt::WA_DeleteOnClose,true);
//    this->setAttribute(Qt::WA_StyledBackground,true);
    // this function must initial at first.
    initGlobalInterface();

    InitMarkerGroup();
    InitBottomLayOut();
    InitBitview();
    initWidget();
    InitAllDialog();

    //set qss mode for indoor,outdoor or night;
    this->setProperty("status",rtsa_qssMode[InterfaceObj->GetDisplayMode()]);

    initThread();

    InitLeftInfoWidget();

    InitFileManager();
#ifdef RTSA_F238_SMART
    initRightButton4Style();
#endif
//    QApplication::setOverrideCursor(Qt::BlankCursor);
    //default set freq button checked
//    ui->topButton1->setChecked(true);
    this->show();
    this->setFocus();
}

BitRtSa::~BitRtSa()
{
    m_thread->rtsa_thread_state = 0;
    V_RTSA_sem(RTSA_guiHandle);
    QThread::msleep(200);
    m_thread->quit();  // Thread quit
    delete UserVariableObj;
    delete InterfaceObj;
    delete mBtnGroup;
    deleteWidget();
    delete bomLayout;
    delete ui;
}
/**
 * @brief init interface, all I/O control interface
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void BitRtSa::initGlobalInterface()
{
    // Single instantiation RtSa_User_Variable
    UserVariableObj = new RtSa_User_Variable(this);
    InterfaceObj = new RtSa_Interface(this);
    connect(InterfaceObj,SIGNAL(MarkerOn(bool)),this,SLOT(MarkerWidgetHide(bool)));
    connect(InterfaceObj,SIGNAL(BitViewMakerDraw(qint32,bool)),this,SLOT(MarkerInfoChange(qint32,bool)));
    connect(InterfaceObj,SIGNAL(MarkerSelectOnOff(qint32,bool)),this,SLOT(MarkerSelect(qint32,bool)));
    connect(InterfaceObj,SIGNAL(ParentFocus()),this,SLOT(setDialogActive()));
    connect(InterfaceObj,SIGNAL(RedrawInfoShow(qint32)),this,SLOT(leftInfo_Update(qint32)));
    connect(InterfaceObj,SIGNAL(MarkerPosChanged(bool)),this,SLOT(marker_changed(bool)));
    connect(InterfaceObj,SIGNAL(BitViewChanged(quint32)),this,SLOT(BitViewMarkerRefresh(quint32)));
    connect(InterfaceObj,SIGNAL(BitScaleChange()),this,SLOT(BitScaleChangeSlot()));
    InterfaceObj->setGobalVariable(UserVariableObj);
}
/**
 * @brief init data thread
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void BitRtSa::initThread()
{
    m_thread = new RtSa_ThreadGraph(this);
    m_thread->setGobalVariable(UserVariableObj);
    m_thread->setInterface(InterfaceObj);
    connect(m_thread, SIGNAL(FinishCount(int)), this, SLOT(graphRefreshFunc()));
    m_thread->start();
}
/**
 * @brief init bitview
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void BitRtSa::deleteWidget()
{
//    if(mCurSetupDialog != NULL)
//    {
//        delete mCurSetupDialog;
//        mCurSetupDialog = NULL;
//    }
    this->setFocus();
    return;
}
void BitRtSa::InitBottomLayOut()
{
    bomLayout = new QHBoxLayout;
    bomLayout->addSpacing(80);
    bomLayout->addWidget(ui->pb_marker_7);
    bomLayout->addWidget(ui->pb_marker_8);
    bomLayout->addWidget(ui->pb_marker_9);
    bomLayout->addWidget(ui->pb_marker_10);
    bomLayout->addWidget(ui->pb_marker_11);
    bomLayout->addWidget(ui->pb_marker_12);
    ui->rtsa_buttomMarker->setLayout(bomLayout);
    return;
}
void BitRtSa::InitMarkerGroup()
{
    mMarkerButton[RTSA_M1] = ui->pb_marker_7;
    mMarkerButton[RTSA_M2] = ui->pb_marker_8;
    mMarkerButton[RTSA_M3] = ui->pb_marker_9;
    mMarkerButton[RTSA_M4] = ui->pb_marker_10;
    mMarkerButton[RTSA_M5] = ui->pb_marker_11;
    mMarkerButton[RTSA_M6] = ui->pb_marker_12;

//    mMarkerButtonGroup = new QButtonGroup;
    return;
}
/**
 * @brief init bitview
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void BitRtSa::InitBitview()
{
    InterfaceObj->InitBitView(this);
}
/**
 * @brief  Initialization widget.
 * @param  void
 * @return void
 * @author Tony
 * @since 2018-12-18
*/
void BitRtSa::initWidget(void)
{
//    loadstylesheet(0);

    mBtnGroup = new QButtonGroup();
    mBtnMarkerGroup = new QButtonGroup();
    mBtnGroup->setExclusive(true);
    mBtnMarkerGroup->setExclusive(true);

    mBtnGroup->addButton(ui->topButton1,RTSA_FREQ_DIALOG);
    mBtnGroup->addButton(ui->topButton2,RTSA_AMPT_DIALOG);
    mBtnGroup->addButton(ui->topButton3,RTSA_DISPLAY_DIALOG);
    mBtnGroup->addButton(ui->topButton4,RTSA_BW_DIALOG);
    mBtnGroup->addButton(ui->topButton5,RTSA_TRIGGER_DIALOG);
    mBtnGroup->addButton(ui->topButton6,RTSA_TRACE_DIALOG);
    mBtnGroup->addButton(ui->topButton7,RTSA_MARKER_DIALOG);
    mBtnGroup->addButton(ui->topButton8,RTSA_OBSERVE_DIALOG);
    mBtnGroup->addButton(ui->topButton9,RTSA_MEASURE_DIALOG);
    mBtnGroup->addButton(ui->topButton10,RTSA_MEAS_TOOL_DIALOGL);
    mBtnGroup->addButton(ui->topButton11,RTSA_ALLSET_DIALOG);

    mBtnMarkerGroup->addButton(ui->pb_marker_7,RTSA_MARKER1_DIALOG);
    mBtnMarkerGroup->addButton(ui->pb_marker_8,RTSA_MARKER2_DIALOG);
    mBtnMarkerGroup->addButton(ui->pb_marker_9,RTSA_MARKER3_DIALOG);
    mBtnMarkerGroup->addButton(ui->pb_marker_10,RTSA_MARKER4_DIALOG);
    mBtnMarkerGroup->addButton(ui->pb_marker_11,RTSA_MARKER5_DIALOG);
    mBtnMarkerGroup->addButton(ui->pb_marker_12,RTSA_MARKER6_DIALOG);


    connect(mBtnGroup,SIGNAL(buttonToggled(int, bool)),this,SLOT(menuHide(int, bool)));
    connect(mBtnGroup,SIGNAL(buttonClicked(int)),this,SLOT(menuShow(int)));

    connect(mBtnMarkerGroup,SIGNAL(buttonToggled(int, bool)),this,SLOT(menuHide(int, bool)));
    connect(mBtnMarkerGroup,SIGNAL(buttonClicked(int)),this,SLOT(menuShow(int)));
    //    connect(mCurSetupDialog,SIGNAL(destroyed()),this,SLOT(menuShow(int)));

    mDigitInput = new RtSa_Dialog_Digitinput(this);
    mDigitInput->setInterface(InterfaceObj);
    mDigitInput->setUserVariable(UserVariableObj);
//    mDigitInput->setProperty("status",rtsa_qssMode[InterfaceObj->GetDisplayMode()]);
//    connect(mDigitInput,SIGNAL(ClockWiseDown()),this,SLOT(ClockKeyDown()));

    mCurSetupDialog = new RtSa_Dialog_FreqSetup(InterfaceObj,mDigitInput,UserVariableObj,this);
//    mAllSetup = new RtSa_Dialog_AllSetup(InterfaceObj,mDigitInput,this);

//    mLimit = new RtSa_Dialog_Limit(InterfaceObj,mDigitInput,this);
//    mLimit->move(1,65);
//    connect(mLimit,SIGNAL(destroyed()),this,SLOT(setActive()));
//    mBottomMarkerSetup = new RtSa_Dialog_BottomMarkerSetup(InterfaceObj,this);
//    connect(mBottomMarkerSetup,SIGNAL(destroyed()),this,SLOT(setActive()));
    return ;
}
/**
 * @brief init stylesheet
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
//void BitRtSa::InitStyleSheet(qint32 index)
//{
//    if(mStyleIndex == index)
//        return;
//    mStyleIndex = index;
//    QString filename[3]={":/rtsa/stylesheet/default.qss",":/rtsa/stylesheet/night.qss",":/rtsa/stylesheet/outdoor.qss"};
//    QFile qss(filename[mStyleIndex]);
//    if(!qss.open(QFile::ReadOnly))
//    {
//        qCritical("Rtsa qss file open failed");
//        return;
//    }
//    this->setStyleSheet(qss.readAll());
//    qss.close();
//    this->setProperty("status",rtsa_qssMode[InterfaceObj->GetDisplayMode()]);

//    return;
//}
/**
 * @brief change size
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void BitRtSa::resizeEvent(QResizeEvent *event)
{
    this->setFocus();
    InterfaceObj->changeSize(this->width(),this->height());
//    ui->widget_bk->resize(this->width(),this->height());
    if(mIsZoomIn)
    {
       InterfaceObj->setZoomIn();
    }
    else
    {
        InterfaceObj->setZoomOut();
    }
//    InitStyleSheet(0);
    return;
}
/**
 * @brief BitRtSa::keyPressEvent
 * @param event
 */
void BitRtSa::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        if(UserVariableObj->gLocal == RTSA_REMOTE)
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
        UserVariableObj->gLocal = RTSA_LOCAL;
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
    if(UserVariableObj->gLocal == RTSA_REMOTE)
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
void BitRtSa::keyRespond(qint32 key)
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
        MenuClose();
        switch(mCurMenuID)
        {
        case RTSA_FREQ_DIALOG:
            InterfaceObj->setCenterFreq(InterfaceObj->getCenterFreq() + InterfaceObj->getCFStep());
            break;
        case RTSA_AMPT_DIALOG:
            InterfaceObj->setRefLevel(InterfaceObj->getRefLevel() + 1);
            break;
        case RTSA_MARKER_DIALOG:
        case RTSA_MARKER1_DIALOG:
        case RTSA_MARKER2_DIALOG:
        case RTSA_MARKER3_DIALOG:
        case RTSA_MARKER4_DIALOG:
        case RTSA_MARKER5_DIALOG:
        case RTSA_MARKER6_DIALOG:
            freq = InterfaceObj->getMarkerFreq(InterfaceObj->getCurMarkerID());
            freqstep = (InterfaceObj->getSpan() / (RTSA_NUM_SWEEP_POINT - 1));
            //Albert 19/01/31 when span < sweep_pts, step should set 1;
            if(InterfaceObj->getSpan() < (RTSA_NUM_SWEEP_POINT - 1))
            {
                freqstep = 1;
            }
            InterfaceObj->setMarkerFreq(InterfaceObj->getCurMarkerID(),freq + freqstep);
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
        case RTSA_FREQ_DIALOG:
            if(InterfaceObj->getCFStep() >= InterfaceObj->getCenterFreq())
            {
                InterfaceObj->setCenterFreq(0);
            }
            else
            {
                InterfaceObj->setCenterFreq(InterfaceObj->getCenterFreq() - InterfaceObj->getCFStep());
            }
            break;
        case RTSA_MARKER_DIALOG:
        case RTSA_MARKER1_DIALOG:
        case RTSA_MARKER2_DIALOG:
        case RTSA_MARKER3_DIALOG:
        case RTSA_MARKER4_DIALOG:
        case RTSA_MARKER5_DIALOG:
        case RTSA_MARKER6_DIALOG:
            freq = InterfaceObj->getMarkerFreq(InterfaceObj->getCurMarkerID());
            freqstep = (InterfaceObj->getSpan() / (RTSA_NUM_SWEEP_POINT - 1));
            if(InterfaceObj->getSpan() < (RTSA_NUM_SWEEP_POINT - 1))
            {
                freqstep = 1;
            }
            InterfaceObj->setMarkerFreq(InterfaceObj->getCurMarkerID(),freq - freqstep);
            break;
        }
        break;
    case Qt::Key_Shift:
        if(mShiftKeyPressed)
            mShiftKeyPressed = false;
        else
            mShiftKeyPressed = true;
        this->show();
        this->setFocus();
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
            mCurMenuID = RTSA_FREQ_DIALOG;
            menuShow(mCurMenuID);
            mShiftKeyPressed = false;
            mBtnGroup->button(RTSA_FREQ_DIALOG)->setChecked(true);
        }
        break;
    case Qt::Key_2:
        if(mShiftKeyPressed)
        {
              V_RTSA_sem(rtsa_homeuiHandle);
//            mCurMenuID = RTSA_FREQ_DIALOG;
//            menuShow(mCurMenuID);
            mShiftKeyPressed = false;
        }
        break;
    case Qt::Key_3:
        if(mShiftKeyPressed)
        {
            mCurMenuID = RTSA_AMPT_DIALOG;
            menuShow(mCurMenuID);
            mShiftKeyPressed = false;
            mBtnGroup->button(RTSA_AMPT_DIALOG)->setChecked(true);
        }
        break;
    case Qt::Key_4:
        if(mShiftKeyPressed)
        {
            mCurMenuID = RTSA_MEASURE_DIALOG;
            menuShow(mCurMenuID);
            mShiftKeyPressed = false;
            mBtnGroup->button(RTSA_MEASURE_DIALOG)->setChecked(true);
        }
        break;
    case Qt::Key_5:
        if(mShiftKeyPressed)
        {
            mCurMenuID = RTSA_DISPLAY_DIALOG;
            menuShow(mCurMenuID);
            mShiftKeyPressed = false;
            mBtnGroup->button(RTSA_DISPLAY_DIALOG)->setChecked(true);
        }
        break;
    case Qt::Key_6:
        if(mShiftKeyPressed)
        {
            mCurMenuID = RTSA_MEAS_TOOL_DIALOGL;
            menuShow(mCurMenuID);
            mShiftKeyPressed = false;
            mBtnGroup->button(RTSA_MEAS_TOOL_DIALOGL)->setChecked(true);
        }
    case Qt::Key_7:
        if(mShiftKeyPressed)
        {
            mCurMenuID = RTSA_OBSERVE_DIALOG;
            menuShow(mCurMenuID);
            mShiftKeyPressed = false;
            mBtnGroup->button(RTSA_OBSERVE_DIALOG)->setChecked(true);
        }
        break;
    case Qt::Key_8:
        if(mShiftKeyPressed)
        {
            InterfaceObj->setMarkerOn(InterfaceObj->getCurMarkerID(),true);
            InterfaceObj->setMarkerToCenter();
            mShiftKeyPressed = false;
        }
        break;
    case Qt::Key_9:
        if(mShiftKeyPressed)
        {
            mCurMenuID = RTSA_MARKER_DIALOG;
            menuShow(mCurMenuID);
            mShiftKeyPressed = false;
            mBtnGroup->button(RTSA_MARKER_DIALOG)->setChecked(true);
        }
        break;
    case Qt::Key_Minus:  // - Minus
    case Qt::Key_F2:    //  +/-
        if(mShiftKeyPressed)
        {
//            ui->topButton1->setChecked(true);
//            mBtnGroup->checkedButton()->setChecked(false);
//            InterfaceObj->PltSaveConditions(STATE_DEFAULT_FILE);
//            InterfaceObj->loadState(RTSA_DEFAULT_COND);
//            if(!ui->topButton7->isChecked())
//                InterfaceObj->showMarkerWidget(false);
            presetState();
            mShiftKeyPressed = false;
//            emit PltAllPresetSig();
        }
        break;
    case Qt::Key_Period:  // . Dot
        if(mShiftKeyPressed)
        {
            mCurMenuID = RTSA_TRACE_DIALOG;
            menuShow(mCurMenuID);
            mShiftKeyPressed = false;
            mBtnGroup->button(RTSA_TRACE_DIALOG)->setChecked(true);
        }
        break;
    default:
        break;
    }
    return;
}
/**
 * @brief BitRtSa::mousePressEvent
 * here must consider set dialog focus, in order to respond keypress
 * @param event
 */
void BitRtSa::mousePressEvent(QMouseEvent *event)
{
    if(UserVariableObj->gLocal == RTSA_REMOTE)
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
/**
 * @brief graph draw function
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void BitRtSa::graphRefreshFunc()
{
    if(1 == sm_rtsa_sync->CtrlAppRunOk)
    {
        InterfaceObj->refreshSpectrogramRect();
        sm_rtsa_sync->CtrlAppRunOk = 0;
    }
    if(InterfaceObj->getDrawFlag())
        return;
    pthread_mutex_lock(&RTSA_lockobj);
    InterfaceObj->Draw();
    pthread_mutex_unlock(&RTSA_lockobj);
    return;
}
/**
 * @brief  Show or hide bullet windows.
 * @param  menuID    Bullet windows id.
 * @param  visible   [true]--show windows [flase]--hide windows
 * @return void
 * @author Tony
 * @since 2018-12-20
*/
void BitRtSa::menuHide(qint32 menuID, bool visible)
{
    InterfaceObj->setLimitTableShow(false);
    return;
}

/**
 * @brief  Show or hide bullet windows.
 * @param  menuID    Bullet windows id.
 * @param  visible   [true]--show windows [flase]--hide windows
 * @return void
 * @author Tony
 * @since 2018-12-20
*/
void BitRtSa::menuShow(qint32 menuID)
{
    if(UserVariableObj->gLocal == RTSA_REMOTE)
    {
        return;
    }
    if(menuID < 0)
        return;
    if(menuID == mCurMenuID && (!mCurSetupDialog->isHidden()))
        return;
//    if(mCurSetupDialog != NULL)
//    {
//        delete mCurSetupDialog;
//        mCurSetupDialog = NULL;
//    }
//    if(!mAllSetup->isHidden())
//        mAllSetup->hide();
    qint32 mode  = InterfaceObj->getDisplay();
    switch(menuID)
    {
    case RTSA_FREQ_DIALOG:
        menuClose();
        mFreqSetup->initDisplay();
        mCurSetupDialog = mFreqSetup;
        break;
    case RTSA_AMPT_DIALOG:
        menuClose();
        mAmptSetup->initDisplay();
        mCurSetupDialog = mAmptSetup;
        break;
    case RTSA_DISPLAY_DIALOG:
        menuClose();
        mDisplaySetup->initDisplay();
        mCurSetupDialog = mDisplaySetup;
        break;
    case RTSA_BW_DIALOG:
        menuClose();
        mBwSetup->InitDisplay();
        mCurSetupDialog = mBwSetup;
        break;
    case RTSA_TRIGGER_DIALOG:
        menuClose();
        mTriggerSetup->initDisplay();
        mTriggerSetup->HideTableWidget();
        mCurSetupDialog = mTriggerSetup;
        break;
    case RTSA_TRACE_DIALOG:
        menuClose();
        mTraceSetup->InitDisplay();
        mCurSetupDialog = mTraceSetup;
        break;
    case RTSA_MARKER_DIALOG:
        menuClose();
        mMarkerSetup->showNotice(false);
        if(InterfaceObj->getCurBitviewType() == RTSA_SPECTROGRAM)
        {
            mMarkerSetup->showNotice(true);
//            mWarningSetUp = new RtSa_Dialog_Warning("Notice","This menu is not available under this\n measurement",this,InterfaceObj->GetDisplayMode());
//            mWarningSetUp->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
//            mWarningSetUp->ShowYesButtonOnly();
////            this->setUpdatesEnabled(true);
//            if(mWarningSetUp->exec() != QDialog::Accepted)
//            {
//                return;
//            }
//            return;
        }
        mMarkerSetup->initDisplay();
        mCurSetupDialog = mMarkerSetup;
        InterfaceObj->showMarkerWidget(true);
        break;
    case RTSA_OBSERVE_DIALOG:
        menuClose();
        mLimit->showNotice(false);
        if(InterfaceObj->getCurBitviewType() != RTSA_SPECTRUM_SPECTROGRAM)
        {
            mLimit->showNotice(true);
//            mWarningSetUp = new RtSa_Dialog_Warning("Notice","This menu is not available under this\n measurement",this,InterfaceObj->GetDisplayMode());
//            mWarningSetUp->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
//            mWarningSetUp->ShowYesButtonOnly();
////            this->setUpdatesEnabled(true);
//            if(mWarningSetUp->exec() != QDialog::Accepted)
//            {
//                return;
//            }
//            return;
        }
        mLimit->initDisplay();
        mLimit->HideTableWidget();
        mCurSetupDialog = mLimit;
        break;
    case RTSA_MEASURE_DIALOG:
        menuClose();
        mMeasureSetup->initDisplay();
        mCurSetupDialog = mMeasureSetup;
        break;
    case RTSA_ALLSET_DIALOG:
        menuClose();
        mAllSetup->initDisplay();
        mCurSetupDialog = mAllSetup;
        break;
    case RTSA_MARKER1_DIALOG:
        menuClose();
        InterfaceObj->setCurMarkerID(RTSA_M1);
        mBottomMarkerSetup->refreshDisplay();
        mCurSetupDialog = mBottomMarkerSetup;
//        mMarkerButton[RTSA_M1]->setStyleSheet("QPushButton{border-image: url(:/rtsa/image/marker_table_editting.png);}");
        break;
    case RTSA_MARKER2_DIALOG:
        menuClose();
        InterfaceObj->setCurMarkerID(RTSA_M2);
        mBottomMarkerSetup->refreshDisplay();
        mCurSetupDialog = mBottomMarkerSetup;
//        mMarkerButton[RTSA_M2]->setStyleSheet("QPushButton{border-image: url(:/rtsa/image/marker_table_editting.png);}");
        break;
    case RTSA_MARKER3_DIALOG:
        menuClose();
        InterfaceObj->setCurMarkerID(RTSA_M3);
        mBottomMarkerSetup->refreshDisplay();
        mCurSetupDialog = mBottomMarkerSetup;
//        mMarkerButton[RTSA_M3]->setStyleSheet("QPushButton{border-image: url(:/rtsa/image/marker_table_editting.png);}");
        break;
    case RTSA_MARKER4_DIALOG:
        menuClose();
        InterfaceObj->setCurMarkerID(RTSA_M4);
        mBottomMarkerSetup->refreshDisplay();
        mCurSetupDialog = mBottomMarkerSetup;
//        mMarkerButton[RTSA_M4]->setStyleSheet("QPushButton{border-image: url(:/rtsa/image/marker_table_editting.png);}");
        break;
    case RTSA_MARKER5_DIALOG:
        menuClose();
        InterfaceObj->setCurMarkerID(RTSA_M5);
        mBottomMarkerSetup->refreshDisplay();
        mCurSetupDialog = mBottomMarkerSetup;
//        mMarkerButton[RTSA_M5]->setStyleSheet("QPushButton{border-image: url(:/rtsa/image/marker_table_editting.png);}");
        break;
    case RTSA_MARKER6_DIALOG:
        menuClose();
        InterfaceObj->setCurMarkerID(RTSA_M6);
        mBottomMarkerSetup->refreshDisplay();
        mCurSetupDialog = mBottomMarkerSetup;
//        mMarkerButton[RTSA_M6]->setStyleSheet("QPushButton{border-image: url(:/rtsa/image/marker_table_editting.png);}");
        break;
    case RTSA_MEAS_TOOL_DIALOGL:
        menuClose();
        mToolSetup->showNotice(false);
        if(mode == RTSA_SPECTRUM_SPECTROGRAM || mode == RTSA_DENSITY_SPECTROGRAM)
        {
            mToolSetup->showNotice(true);
        }
        mToolSetup->InitDisplay();
        mCurSetupDialog = mToolSetup;
//        mSpectrogramCursor->initDisplay();
//        mCurSetupDialog = mSpectrogramCursor;
        break;
    case RTSA_SCREEN_CAPTURE_DIALOG:
        mCurSetupDialog = mQuickSave;
        mCurSetupDialog->setGeometry(135,155,1010,490);
//        repaint();
        break;

        break;
    default:
//        this->setUpdatesEnabled(true);
        return;
        break;
    }
//    connect(mCurSetupDialog,SIGNAL(destroyed()),this,SLOT(setActive()));
    mCurMenuID = menuID;
    mCurSetupDialog->setProperty("status",rtsa_qssMode[InterfaceObj->GetDisplayMode()]);
    mCurSetupDialog->setStyle(QApplication::style());
    if(menuID == RTSA_SCREEN_CAPTURE_DIALOG)
    {
        qobject_cast<QDialog*>(mCurSetupDialog)->exec();
    }
    else
    {
        mCurSetupDialog->setProperty("status",rtsa_qssMode[InterfaceObj->GetDisplayMode()]);
        mCurSetupDialog->setStyle(QApplication::style());
        mCurSetupDialog->show();
        mCurSetupDialog->setFocus();
    }
//    this->setUpdatesEnabled(true);
//    QApplication::processEvents();
//    mCurSetupDialog->show();
//    InterfaceObj->DrawFlag(false);

//    this->show();
//    mLastAcqTime = InterfaceObj->getAcqTime();
//    InterfaceObj->setSleepTime(100000);
    return ;
}
/**
 * @brief zoom button slot
 * @param
 * @param
 * @return void
 * @author Albert
 * @since 2018-12-26
*/
void BitRtSa::on_rightButton8_clicked()
{
#ifdef RTSA_F238_SMART
    presetState();
#else
    menuClose();
    emit SysSetSig();
    ui->rightButton8->setChecked(false);
#endif
    return;
}

void BitRtSa::on_rightButton9_clicked()
{
  V_RTSA_sem(rtsa_homeuiHandle);
  ui->rightButton9->setChecked(true);
  return;
}
void BitRtSa::on_rightButton10_clicked()
{
    menuClose();
    if(mIsZoomIn)
    {
        mIsZoomIn = false;
        InterfaceObj->setZoomFlag(mIsZoomIn);
        ShowWidget();
        this->setGeometry(1,52,1278,713);
//        emit ZoomIn(false);
    }
    else
    {
        mIsZoomIn = true;
        InterfaceObj->setZoomFlag(mIsZoomIn);
        HideWidget();
        this->setGeometry(0,0,1280,765);
//        emit ZoomIn(true);
    }
    return;
}

void BitRtSa::HideWidget()
{
    mDigitInput->hide();
//    mAllSetup->hide();
    if(InterfaceObj->IsMarkerAlreadyOn() || ui->topButton7->isChecked())
    {
        ui->rtsa_buttomMarker->show();
        ui->rtsa_buttomMarker->move(1,693);
        ui->rtsa_buttomMarker->resize(1280 - 84 - 1,72);
        bomLayout->setSpacing(8);
    }
    else
    {
        ui->rtsa_buttomMarker->hide();
    }
    ui->topButtonBar->hide();
    ui->rtsa_leftInfoWidget->hide();
//    ui->widget_topSpace->hide();

//    ui->widget_topSpace->resize(1280,3);
//    ui->widget_topSpace->move(0,0);
    ui->rightButtonBar->move(1196,0);
    ui->rightButtonBar->resize(84,763);
    ui->rightButton10->move(3,763 - 55);

    return;
}
void BitRtSa::ShowWidget()
{
    if(InterfaceObj->IsMarkerAlreadyOn() || ui->topButton7->isChecked())
    {
        ui->rtsa_buttomMarker->show();
        if(InterfaceObj->getDragFlag())
        {
            ui->rtsa_buttomMarker->move(0,641);
            ui->rtsa_buttomMarker->resize(940 + 255,72);
        }
        else
        {
            ui->rtsa_buttomMarker->move(255,641);
            ui->rtsa_buttomMarker->resize(940,72);
        }
//        ui->rtsa_buttomMarker->move(255,641);
//        ui->rtsa_buttomMarker->resize(939,72);
        bomLayout->setSpacing(8);
    }
    else
    {
         ui->rtsa_buttomMarker->hide();
    }
    ui->topButtonBar->show();
    if(!InterfaceObj->getDragFlag())
        ui->rtsa_leftInfoWidget->show();
//    ui->widget_bottomSpace->resize(943,2);
//    ui->widget_bottomSpace->move(276,639);

//    ui->widget_topSpace->resize(943,3);
//    ui->widget_topSpace->move(255,65);
    ui->rightButtonBar->resize(84,648);
    ui->rightButtonBar->move(1195,65);
    ui->rightButton10->move(3,591);
    this->show();
    this->setFocus();
    return;
}

void BitRtSa::InitLeftInfoWidget()
{
    connect(ui->widget_mode,SIGNAL(clicked()),this,SLOT(on_WidgetClicked()));
    connect(ui->widget_Freq,SIGNAL(clicked()),this,SLOT(on_WidgetClicked()));
    connect(ui->widget_Ampt,SIGNAL(clicked()),this,SLOT(on_WidgetClicked()));
    connect(ui->widget_BW,SIGNAL(clicked()),this,SLOT(on_WidgetClicked()));
    connect(ui->widget_Limit,SIGNAL(clicked()),this,SLOT(on_WidgetClicked()));
    connect(ui->widget_Trace,SIGNAL(clicked()),this,SLOT(on_WidgetClicked()));
    connect(ui->widget_Trigger,SIGNAL(clicked()),this,SLOT(on_WidgetClicked()));
    connect(ui->widget_mode,SIGNAL(clicked()),this,SLOT(on_WidgetClicked()));
    connect(ui->widget_time,SIGNAL(clicked()),this,SLOT(on_WidgetClicked()));


    mRtSaInfoWidget = new QMap<RtSa_ClickedWidget*,qint32>;
    mRtSaInfoWidget->insert(ui->widget_mode,RTSA_MEASURE_DIALOG);
    mRtSaInfoWidget->insert(ui->widget_Freq,RTSA_FREQ_DIALOG);
    mRtSaInfoWidget->insert(ui->widget_Ampt,RTSA_AMPT_DIALOG);
    mRtSaInfoWidget->insert(ui->widget_BW,RTSA_BW_DIALOG);
    mRtSaInfoWidget->insert(ui->widget_Limit,RTSA_OBSERVE_DIALOG);
    mRtSaInfoWidget->insert(ui->widget_Trace,RTSA_TRACE_DIALOG);
    mRtSaInfoWidget->insert(ui->widget_Trigger,RTSA_TRIGGER_DIALOG);
    mRtSaInfoWidget->insert(ui->widget_time,RTSA_DISPLAY_DIALOG);

}

void BitRtSa::MarkerWidgetHide(bool isOn)
{
    if(isOn)
    {
        ui->rtsa_buttomMarker->show();
        if(mIsZoomIn)
        {
        }
        else
        {
            if(InterfaceObj->getDragFlag())
            {
                ui->rtsa_buttomMarker->move(0,641);
                ui->rtsa_buttomMarker->resize(940 + 255,72);
            }
            else
            {
                ui->rtsa_buttomMarker->move(255,641);
                ui->rtsa_buttomMarker->resize(940,72);
            }
        }
    }
    else
    {
        ui->rtsa_buttomMarker->hide();
        if(mIsZoomIn)
        {
            HideWidget();
        }
        else
        {
            ShowWidget();
        }

    }
    return;
}
void BitRtSa::MarkerInfoChange(qint32 markerID,bool isOn)
{
    qint32 type = InterfaceObj->getCurBitviewType();
    if(!isOn || (type == RTSA_SPECTROGRAM))
    {
        return;
    }
    QString strInfo = QString("M%1\n").arg(markerID + 1);
    qreal freq1 = InterfaceObj->getMarkerRefFreq(markerID);
    qreal freq2 = InterfaceObj->getMarkerDeltaFreq(markerID);
    qreal freq = (qreal)freq1;
    if(InterfaceObj->getMarkerType(markerID) != RTSA_REF)
    {
        freq = (qreal)freq2 - (qreal)freq1;
        strInfo = QString("D%1\n").arg(markerID + 1);
    }
    switch(markerID)
    {
    case RTSA_M1:
        strInfo += InterfaceObj->getFreqAdjustStr(freq);
        strInfo += QString("\n");
        strInfo += InterfaceObj->getMarkerInfoStr(markerID);
        strInfo += QString("\n");
        break;
    case RTSA_M2:
        strInfo += InterfaceObj->getFreqAdjustStr(freq);
        strInfo += QString("\n");
        strInfo += InterfaceObj->getMarkerInfoStr(markerID);
        strInfo += QString("\n");
        break;
    case RTSA_M3:
        strInfo += InterfaceObj->getFreqAdjustStr(freq);
        strInfo += QString("\n");
        strInfo += InterfaceObj->getMarkerInfoStr(markerID);
        strInfo += QString("\n");
        break;
    case RTSA_M4:
        strInfo += InterfaceObj->getFreqAdjustStr(freq);
        strInfo += QString("\n");
        strInfo += InterfaceObj->getMarkerInfoStr(markerID);
        strInfo += QString("\n");
        break;
    case RTSA_M5:
        strInfo += InterfaceObj->getFreqAdjustStr(freq);
        strInfo += QString("\n");
        strInfo += InterfaceObj->getMarkerInfoStr(markerID);
        strInfo += QString("\n");
        break;
    case RTSA_M6:
        strInfo += InterfaceObj->getFreqAdjustStr(freq);
        strInfo += QString("\n");
        strInfo += InterfaceObj->getMarkerInfoStr(markerID);
        strInfo += QString("\n");
        break;
    default:
        strInfo += InterfaceObj->getFreqAdjustStr(freq);
        strInfo += QString("\n");
        strInfo += InterfaceObj->getMarkerInfoStr(markerID);
        strInfo += QString("\n");
        break;
    }
    mMarkerButton[markerID]->setText(strInfo);
//    mMarkerButtonGroup[curMarker]->setChecked(true);
    return;
}
void BitRtSa::MarkerSelect(qint32 MarkerID, bool isOn)
{
    ui->topButton7->setChecked(true);
    qint32 curMarker = InterfaceObj->getCurMarkerID();
    mMarkerButton[curMarker]->setChecked(true);
    QString strInfo;
    if(!isOn)
    {
        strInfo.sprintf("M%d\n-- --\n-- --\n", MarkerID + 1);
        mMarkerButton[MarkerID]->setText(strInfo);
    }

    for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
    {
        mMarkerButton[i]->setStyleSheet("");
    }
//    if()
//    mMarkerButton[curMarker]->setStyleSheet("QPushButton{border-image: url(:/rtsa/image/marker_table_editting.png);}");
//    if(mBottomMarkerSetup != NULL)
//    {
//    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-14
*/
void BitRtSa::BitViewMarkerRefresh(quint32 MarkerID)
{
    if(ui->topButton8->isChecked()|| ui->topButton7->isChecked())
    {
        if((mLimit != NULL) && !mLimit->isHidden() || (mCurSetupDialog != NULL))
        {
            menuClose();
        }
        if(InterfaceObj->getCurBitviewType() != RTSA_SPECTRUM_SPECTROGRAM)
        {
            menuClose();
            return;
//            mWarningSetUp = new RtSa_Dialog_Warning("Notice","This menu is not available under this\n measurement",this,InterfaceObj->GetDisplayMode());
//            mWarningSetUp->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
//            mWarningSetUp->ShowYesButtonOnly();
//            if(mWarningSetUp->exec() != QDialog::Accepted)
//            {
//                return;
//            }
//            return;
        }
    }
    qint32 curMarker = InterfaceObj->getCurMarkerID();
    mMarkerButton[curMarker]->setChecked(true);
    QString strInfo;
    for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
    {
        if(!InterfaceObj->isMarkerOn(i))
        {
            strInfo.sprintf("M%d\n-- --\n-- --\n", i + 1);
            mMarkerButton[i]->setText(strInfo);
        }
        mMarkerButton[i]->setStyleSheet("");
    }
//    if(!isOn)
//    {
//        strInfo.sprintf("M%d\n-- --\n-- --\n", MarkerID + 1);
//        mMarkerButton[MarkerID]->setText(strInfo);
//    }

//    for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
//    {
//        mMarkerButton[i]->setStyleSheet("");
//    }
//    if()
//    mMarkerButton[curMarker]->setStyleSheet("QPushButton{border-image: url(:/rtsa/image/marker_table_editting.png);}");
//    if(mBottomMarkerSetup != NULL)
//    {
//    }
    return;
}
void BitRtSa::MenuClose()
{
    menuClose();
    return;
}
void BitRtSa::menuClose()
{
//    InterfaceObj->DrawFlag(true);
    if(mCurSetupDialog != NULL)
    {
        mCurSetupDialog->hide();
        if(mCurSetupDialog == mFreqSetup)
        {
            mFreqSetup->HideChStdDialog();
        }
        else if(mCurSetupDialog == mTraceSetup)
        {
            mTraceSetup->HideTimeCursorDialog();
        }
        this->setUpdatesEnabled(false);
//        delete mCurSetupDialog;
//        mCurSetupDialog = NULL;
    }
    if(mWarningSetUp != NULL)
    {
        delete mWarningSetUp;
        mWarningSetUp = NULL;
    }
    if(mLimit != NULL && !mLimit->isHidden())
    {
       mLimit->hide();
    }
//    if(mBottomMarkerSetup != NULL)
//    {
//        delete mBottomMarkerSetup;
//        mBottomMarkerSetup = NULL;
//    }
//    mBottomMarkerSetup->hide();.
    if(!mDigitInput->isHidden())
        mDigitInput->hide();
//    mAllSetup->hide();
    if(!ui->topButton7->isChecked())
    {
        InterfaceObj->showMarkerWidget(false);
    }
//    emit KeyEventSig(Qt::Key_Escape);
    this->setUpdatesEnabled(true);
//    this->show();
    this->setFocus();
    return;
}
/**
 * @brief BitRtSa::setActive
 * this function is used for dialog close,
 * because mCurSetupDialog has already destroyed,
 * here just set NULL.
 */
void BitRtSa::setActive()
{
//    mLastAcqTime = InterfaceObj->getAcqTime();
//    InterfaceObj->setSleepTime(mLastAcqTime);
//    mLimit = NULL;
//    mCurSetupDialog = NULL;
//    mBottomMarkerSetup = NULL;
    mQuickSave = NULL;
    mMarkerButton[InterfaceObj->getCurMarkerID()]->setStyleSheet("");
//    emit KeyEventSig(Qt::Key_Escape);
    if(InterfaceObj->isShiftKeyEnable())
    {
        keyRespond(Qt::Key_Shift);
        InterfaceObj->setShiftKeyEnable(false);
    }
    if(mWarningSetUp != NULL)
    {
        delete mWarningSetUp;
        mWarningSetUp = NULL;
    }
    InterfaceObj->DrawFlag(false);
    this->setFocus();
    return;
}
void BitRtSa::ClockKeyDown()
{
//    MenuClose();
    mDigitInput->close();
    mCurSetupDialog->setFocus();
    return;
}
void BitRtSa::setDialogActive()
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
void BitRtSa::on_pb_Drag_clicked()
{
    menuClose();
    if(mDragFlag)
    {
        mDragFlag = false;
        InterfaceObj->setDragFlag(mDragFlag);
        ui->widget_Drag->move(254,65);
        ui->rtsa_leftInfoWidget->show();
        if(!ui->rtsa_buttomMarker->isHidden())
        {
            ui->rtsa_buttomMarker->move(255,641);
            ui->rtsa_buttomMarker->resize(940,72);
        }
//        ui->pb_Drag->setStyleSheet("border-image: url(:/rtsa/image/sanjiao_left.png);");
    }
    else
    {
        mDragFlag = true;
        InterfaceObj->setDragFlag(mDragFlag);
        ui->widget_Drag->move(2,65);
        ui->rtsa_leftInfoWidget->hide();
        if(!ui->rtsa_buttomMarker->isHidden())
        {
            ui->rtsa_buttomMarker->move(0,641);
            ui->rtsa_buttomMarker->resize(940 + 255,72);
        }
//        ui->pb_Drag->setStyleSheet("border-image: url(:/rtsa/image/sanjiao_right.png);");
    }
    return;
}

void BitRtSa::on_pb_marker_AllOff_2_clicked()
{
    menuClose();
    for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT;i++)
    {
        InterfaceObj->setMarkerOn(i,false);
    }
    if(ui->topButton7->isChecked())
    {
        InterfaceObj->showMarkerWidget(true);
    }
    InterfaceObj->setZoomFlag(mIsZoomIn);
    return;
}

void BitRtSa::leftInfo_Update(qint32 infoID)
{
    QString strGab = "";
    qint32 intGab = 0;
    qint32 intCurAvg = 0;
    qreal fGab = 0.0;
    QString strInfo;
    qint32 mCurTraceID = InterfaceObj->getCurTrace();
    QString style = QString("#lblType1{image: url(:/rtsa/image/trace_no.png);}\n");
//    strInfo = QString("QLabel{border:1px solid rgb(255,255,255);}");
//    ui->lblT1->setStyleSheet("");
//    ui->lblT2->setStyleSheet("");
//    ui->lblT3->setStyleSheet("");
//    ui->lblT4->setStyleSheet("");
//    ui->lblT5->setStyleSheet("");
//    ui->lblT6->setStyleSheet("");
    switch(infoID)
    {
    case LABEL_MODE:
        intGab = InterfaceObj->getDisplay();
        if(intGab == RTSA_SPECTRUM_SPECTROGRAM)
        {
            ui->lblmeasure->setText("Persistent spectrum");
        }
        else if(intGab == RTSA_SPECTROGRAM)
        {
            ui->lblmeasure->setText("Persistent spectrogram");
        }
        else if(intGab == RTSA_DENSITY)
        {
            ui->lblmeasure->setText("Persistent Density");
        }
        else
        {
            ui->lblmeasure->setText("Persistent Density Spectrogram");
        }
        emit MesPlatTitleSig(intGab /*- 1*/);
        break;
    case LABEL_CENTER_FREQ:
        strGab = InterfaceObj->getFreqAdjustStr(InterfaceObj->getCenterFreq());
        ui->lblCenterFreqValue->setText(strGab);
        break;
    case LABEL_SIGNAL_STANDARD:
        if(UserVariableObj->gTecIndex < 0 || !UserVariableObj->IsFreqInCurChStd())
        {
            strGab = "None";
        }
        else
        {
            strGab = QString(mRTSA_ChStand[UserVariableObj->gTecIndex].name);
        }
        ui->lblCHStandardValue->setText(strGab);
        break;
    case LABEL_CHANNEL:
        if(UserVariableObj->gTecIndex < 0 || !UserVariableObj->IsFreqInCurChStd())
        {
            strGab = "None";
        }
        else
        {
            strGab = QString::number(InterfaceObj->getChannelNumber());
        }
        ui->lblChannelValue->setText(strGab);
        break;
    case LABEL_PREAMP:
        intGab = InterfaceObj->IsPreAmpOn();
        if(intGab == true)
        {
            ui->lblPreampValue->setText("On");
        }
        else
        {
            ui->lblPreampValue->setText("Off");
        }
        break;
    case LABEL_ATTEN_STATUS:
        intGab = InterfaceObj->IsAttenAuto();
        if(intGab == true)
        {
            ui->lblAttenType->setText("Auto");
        }
        else
        {
            ui->lblAttenType->setText("Manual");
        }
        break;
    case LABEL_ATTEN_VAL:
        fGab = InterfaceObj->getAttenVal();
        strGab = QString::number(fGab) + QString("  dB");
        ui->lblAttenValue->setText(strGab);
        break;
    case LABEL_RBW_STATUS:
        intGab = InterfaceObj->IsBWAuto();
        if(intGab == true)
        {
            ui->lblRBWType->setText("Auto");
        }
        else
        {
            ui->lblRBWType->setText("Manual");
        }
        break;
    case LABEL_AVERAGE:
        intGab = InterfaceObj->getAvgNum(mCurTraceID);
        intCurAvg = InterfaceObj->getCurAvgNum(mCurTraceID);
        if(!InterfaceObj->IsAvgOn(mCurTraceID))
        {
            strGab = QString("--/--");
        }
        else
        {
            strGab = QString::number(intCurAvg) + QString("/") + QString::number(intGab);
        }
        ui->lblAverageValue->setText(strGab);
        break;
    case LABEL_TRACE_STATUS:
        refreshTraceStatus();
        break;
    case LABEL_TRACE1_STATUS:
    case LABEL_TRACE2_STATUS:
    case LABEL_TRACE3_STATUS:
    case LABEL_TRACE4_STATUS:
    case LABEL_TRACE5_STATUS:
    case LABEL_TRACE6_STATUS:
        refreshTraceStatus();
        break;
    case LABEL_RBW:
        fGab = InterfaceObj->getBW();
        strGab = InterfaceObj->getFreqAdjustStr(fGab,3);
        ui->lblRBWValue->setText(strGab);
        break;
    case LABEL_FFTWINDOW:
        strGab = InterfaceObj->getFFTWindowStr();
        ui->lblFFTValue->setText(strGab);
        break;
    case LABEL_ACQTIME:
        fGab = InterfaceObj->getAcqTime();
        strGab = InterfaceObj->getAdjustTimeStr(fGab);
        ui->lblAcqtimeValue->setText(strGab);
        break;
    case LABEL_PERSISTENCE:
        intGab = InterfaceObj->IsPersistenceTimeInfinite();
        if(intGab == RTSA_FINITE)
        {
            ui->lblPerTimeInfinite->setText("Finite");
        }
        else
        {
            ui->lblPerTimeInfinite->setText("Infinite");
        }
        fGab = InterfaceObj->getPersistenceTime();
        strGab = InterfaceObj->getAdjustTimeStr(fGab);
        ui->lblPersTimeValue->setText(strGab);
        break;
    case LABEL_FREQ_REF:
        break;
    case LABEL_TRIGGER:
        intGab = InterfaceObj->getTrigger();
        switch(intGab)
        {
        case RTSA_TRIGGER_FREE_RUN:
            ui->lblTrigger->setText("Free Run");
            break;
        case RTSA_TRIGGER_EXTERNAL:
            ui->lblTrigger->setText("External");
            break;
        case RTSA_TRIGGER_PERIODIC_TIMER:
            ui->lblTrigger->setText("Periodic Timer");
            break;
        case RTSA_TRIGGER_RF_BURST:
            ui->lblTrigger->setText("RF Burst");
            break;
        case RTSA_TRIGGER_FMTMASK:
            ui->lblTrigger->setText("FMT");
            break;
        default:
            ui->lblTrigger->setText("Free Run");
            break;

        }
        break;
    case LABEL_DETECTOR:
        intGab = InterfaceObj->getDectorType();
        switch (intGab) {
        case RTSA_DEC_PEAK:
            ui->lblDetectorValue->setText("Peak");
            break;
        case RTSA_DEC_NEGATIVE_PEAK:
            ui->lblDetectorValue->setText("Neg Peak");
            break;
        case RTSA_DEC_SAMPLE:
            ui->lblDetectorValue->setText("Sample");
            break;
        case RTSA_DEC_AVERAGE:
            ui->lblDetectorValue->setText("Average");
            break;
        case RTSA_DEC_RMS:
            ui->lblDetectorValue->setText("RMS");
            break;
        default:
            break;
        }
        break;
    case LABEL_LIMIT:
        intGab = InterfaceObj->isHaveLimitOn();
        if(intGab == 1)
        {
            ui->lblLimitValue->setText("On");
        }
        else
        {
            ui->lblLimitValue->setText("Off");
        }
        break;
    case LABEL_POI:
        fGab = RTSA_POIList[UserVariableObj->gRbwGrade][UserVariableObj->gRbwIndex];
        strGab = InterfaceObj->getAdjustTimeStr(fGab);
        ui->lblPOIValue->setText(strGab);
        break;
    case LABEL_DISPLAY:
        this->setProperty("status",rtsa_qssMode[InterfaceObj->GetDisplayMode()]);
        setStyle(QApplication::style());
        break;
    default:
        break;
    }
    return;
}
void BitRtSa::on_WidgetClicked()
{
    qint32 index;
    RtSa_ClickedWidget* widget = qobject_cast<RtSa_ClickedWidget*>(sender());
    index = mRtSaInfoWidget->value(widget);
    mBtnGroup->button(index)->setChecked(true);
    menuShow(index);
    return;
}

void BitRtSa::refreshTraceStatus()
{
    qint32 trace,status,type;
    QString strqss,strbg,strTrace;
    trace = InterfaceObj->getCurTrace();
    for(qint32 i=0;i<RTSA_NUM_TRACE;i++)
    {
//        strqss = QString("");
//        status = pcontrolInterface->getTraceViewStatus(i);
        type = InterfaceObj->getTraceType(i);
        if(type != RTSA_TRACE_OFF)
        {
            strqss += QString("#lblTypeT%1{}\n").arg(QString::number(i+1));
        }
        else
        {
//            strqss += QString("#lblTypeT%1{image: url(:/rtsa/image/W_bk_off.png);}\n").arg(QString::number(i+1));
        }
        if(i == trace)
        {
            strbg = QString("#lblbgT%1{background-image: url(:/rtsa/image/T%2_selected_box.png);}\n").arg(QString::number(i+1)).arg(QString::number(i+1));
            strTrace = QString("#lblT%1{image: url(:/rtsa/image/T%2_bk.png);}\n").arg(QString::number(i+1)).arg(QString::number(i+1));;
        }else
        {
            strbg = QString("#lblbgT%1{}\n").arg(QString::number(i+1));
            strTrace = QString("#lblT%1{image: url(:/rtsa/image/T%2_color.png);}\n").arg(QString::number(i+1)).arg(QString::number(i+1));;
        }
        strqss = strqss + strbg + strTrace;
    }
    ui->widget_Trace->setStyleSheet(strqss);
    refreshTraceType();
    return;
}

void BitRtSa::refreshTraceType()
{
    qint32 traceNo,traceType,traceView;
    QString strInfo,strQss;
    for(int i=0;i<RTSA_NUM_TRACE;i++)
    {
        traceNo = InterfaceObj->getCurTrace();
        traceType = InterfaceObj->getTraceType(i);
//        traceView = InterfaceObj->(i);
        switch (traceType)
        {
        case RTSA_CLEAR_WRITE:
            strInfo = "W";
            break;
        case RTSA_MAX_HOLD:

            strInfo = "M";
            break;
        case RTSA_MIN_HOLD:
            strInfo = "_m";
            break;
        case RTSA_VIEW:
            strInfo = "V";
            break;
        case RTSA_AVERAGE:
            strInfo = "A";
            break;
        }
        if(traceType >= RTSA_CLEAR_WRITE)
        {
            strQss = QString("#lblTypeT%1{background-image: url(:/rtsa/image/%2_bk.png);}\n").arg(QString::number(i+1)).arg(strInfo);
        }else
        {
            strQss = QString("#lblTypeT%1{background-image: url(:/rtsa/image/%2_bk_off.png);}\n").arg(QString::number(i+1)).arg("W");
        }
        //Miss the picture of current trace and that is on
        if((i != traceNo)&& (traceType > RTSA_TRACE_OFF))
        {
            switch (traceType)
            {
            case RTSA_CLEAR_WRITE:
                strInfo = "W";
                break;
            case RTSA_MAX_HOLD:
                strInfo = "M";
                break;
            case RTSA_MIN_HOLD:
                strInfo = "m";
                break;
            case RTSA_VIEW:
                strInfo = "V";
                break;
            case RTSA_AVERAGE:
                strInfo = "A";
                break;
            }
            switch (i) {
            case RTSA_TR1:
                ui->lblTypeT1->setText(strInfo);
                ui->lblTypeT1->setStyleSheet("color:rgba(168, 168, 168, 1)");
                break;
            case RTSA_TR2:
                ui->lblTypeT2->setText(strInfo);
                ui->lblTypeT2->setStyleSheet("color:rgba(168, 168, 168, 1)");
                 break;
            case RTSA_TR3:
                ui->lblTypeT3->setText(strInfo);
                ui->lblTypeT3->setStyleSheet("color:rgba(168, 168, 168, 1)");
                break;
            case RTSA_TR4:
                ui->lblTypeT4->setText(strInfo);
                ui->lblTypeT4->setStyleSheet("color:rgba(168, 168, 168, 1)");
                break;
            case RTSA_TR5:
                ui->lblTypeT5->setText(strInfo);
                ui->lblTypeT5->setStyleSheet("color:rgba(168, 168, 168, 1)");
                break;
            case RTSA_TR6:
                ui->lblTypeT6->setText(strInfo);
                ui->lblTypeT6->setStyleSheet("color:rgba(168, 168, 168, 1)");
                break;
            }
        }else if((i == traceNo)&& (traceType > RTSA_TRACE_OFF))
        {
            switch (traceType)
            {
            case RTSA_CLEAR_WRITE:
                strInfo = "W";
                break;
            case RTSA_MAX_HOLD:
                strInfo = "M";
                break;
            case RTSA_MIN_HOLD:
                strInfo = "m";
                break;
            case RTSA_VIEW:
                strInfo = "V";
                break;
            case RTSA_AVERAGE:
                strInfo = "A";
                break;
            }
            switch (i) {
            case RTSA_TR1:
                ui->lblTypeT1->setText(strInfo);
                ui->lblTypeT1->setStyleSheet("color:rgba(0, 0, 0, 1)");
                break;
            case RTSA_TR2:
                ui->lblTypeT2->setText(strInfo);
                ui->lblTypeT2->setStyleSheet("color:rgba(0, 0, 0, 1)");
                 break;
            case RTSA_TR3:
                ui->lblTypeT3->setText(strInfo);
                ui->lblTypeT3->setStyleSheet("color:rgba(0, 0, 0, 1)");
                break;
            case RTSA_TR4:
                ui->lblTypeT4->setText(strInfo);
                ui->lblTypeT4->setStyleSheet("color:rgba(0, 0, 0, 1)");
                break;
            case RTSA_TR5:
                ui->lblTypeT5->setText(strInfo);
                ui->lblTypeT5->setStyleSheet("color:rgba(0, 0, 0, 1)");
                break;
            case RTSA_TR6:
                ui->lblTypeT6->setText(strInfo);
                ui->lblTypeT6->setStyleSheet("color:rgba(0, 0, 0, 1)");
                break;
            }
        }else
        {
        switch (i) {
        case RTSA_TR1:
            ui->lblTypeT1->setText("");
            ui->lblTypeT1->setStyleSheet(strQss);
            break;
        case RTSA_TR2:
            ui->lblTypeT2->setText("");
            ui->lblTypeT2->setStyleSheet(strQss);
             break;
        case RTSA_TR3:
            ui->lblTypeT3->setText("");
            ui->lblTypeT3->setStyleSheet(strQss);
            break;
        case RTSA_TR4:
            ui->lblTypeT4->setText("");
            ui->lblTypeT4->setStyleSheet(strQss);
            break;
        case RTSA_TR5:
            ui->lblTypeT5->setText("");
            ui->lblTypeT5->setStyleSheet(strQss);
            break;
        case RTSA_TR6:
            ui->lblTypeT6->setText("");
            ui->lblTypeT6->setStyleSheet(strQss);
            break;
        }
        }
    }

}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-21
*/
void BitRtSa::InitFileManager()
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
 * @brief BitRtSa::on_rightButton1_clicked
 * Peak search
 */
void BitRtSa::on_rightButton1_clicked()
{
    menuClose();
    qint32 markerID = InterfaceObj->getCurMarkerID();
    InterfaceObj->setMarkerOn(markerID,true);
    InterfaceObj->setMarkerToPeak();
    MarkerWidgetHide(true);
//    if(!mIsZoomIn)
//    {
//        ShowWidget();
//    }
//    else
//    {
//        HideWidget();
//    }
    mBtnGroup->button(RTSA_MARKER_DIALOG)->setChecked(true);

    return;
}
/**
 * @brief BitRtSa::on_rightButton3_clicked
 * auto scale
 */
void BitRtSa::on_rightButton3_clicked()
{
    menuClose();
    InterfaceObj->setAutoScale();
    mBtnGroup->button(RTSA_AMPT_DIALOG)->setChecked(true);
    return;
}
void BitRtSa::SetMeasureItems(qint32 imea)
{
    InterfaceObj->setDisplay(imea);
    return;
}

void BitRtSa::marker_changed(bool isChanged)
{
//    if(mCurMenuID == RTSA_MARKER_DIALOG || (mCurMenuID >= RTSA_MARKER1_DIALOG && mCurMenuID <= RTSA_MARKER6_DIALOG))
//        return;
//    if(isChanged && mCurMenuID != RTSA_MARKER_DIALOG)
//    {
//        menuClose();
//        mCurMenuID = RTSA_MARKER_DIALOG;
//    }
    return;
}

void BitRtSa::on_rightButton4_clicked()
{
#ifdef RTSA_F238_SMART
    menuClose();
    InterfaceObj->DrawFlag(true);
    mFileManager->showFileManagerWidget();
#else
    touchSignal = !touchSignal;
//    if(touchSignal == 0)
//    {
//        touchSignal = 1;
//    }
    if(touchSignal)
    {
        emit KeyEventSig(Qt::Key_Escape + 1);
    }
    else
    {
        emit KeyEventSig(Qt::Key_Escape + 2);
    }
//    else if(touchSignal == 1)
//    {
//        touchSignal = 0;
//    }
//   emit TouchSig(touchSignal);
#endif
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
void BitRtSa::on_rightButton2_clicked()
{
    mLimit->showNotice(false);
    if(InterfaceObj->getCurBitviewType() != RTSA_SPECTRUM_SPECTROGRAM)
    {
        menuClose();
        mLimit->showNotice(true);
        mLimit->HideTableWidget();
        mLimit->show();
        mBtnGroup->button(RTSA_OBSERVE_DIALOG)->setChecked(true);
        mLimit->setFocus();
//        mWarningSetUp = new RtSa_Dialog_Warning("Notice","Limit only be used in spectrum",this,InterfaceObj->GetDisplayMode());
//        mWarningSetUp->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
//        mWarningSetUp->ShowYesButtonOnly();
//        if(mWarningSetUp->exec() != QDialog::Accepted)
//        {
//            return;
//        }
        return;
    }
    InterfaceObj->BuildLimitFromTrace();
    menuClose();
//    if(mLimit == NULL)
//    {
//        mLimit = new RtSa_Dialog_Limit(InterfaceObj,mDigitInput,this);
//        mLimit->move(1,65);
//        connect(mLimit,SIGNAL(destroyed()),this,SLOT(setActive()));
//    }
//    else
//    {

//    }
    mLimit->BuildLimitFromTrace();
    mLimit->show();
    mBtnGroup->button(RTSA_OBSERVE_DIALOG)->setChecked(true);
    mLimit->setFocus();
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
void BitRtSa::SetLocalRemoteMode(qint32 mode)
{
    UserVariableObj->gLocal = mode;
    if(mode == RTSA_REMOTE)
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
* @Author Albert
* @date 2019-06-04
*/
//qint32 BitRtSa::GetLocalRemoteMode()
//{
//    return UserVariableObj->gLocal;
//}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
void BitRtSa::on_rightButton7_clicked()
{
//    menuClose();
#ifdef RTSA_F238_SMART
    menuClose();
    emit SysSetSig();
    ui->rightButton7->setChecked(false);
#else
    InterfaceObj->DrawFlag(true);
    if(mQuickSave != NULL)
    {
        delete mQuickSave;
        mQuickSave = NULL;
    }
    mQuickSave = new RtSa_Dialog_QuickSave(this,InterfaceObj->GetDisplayMode());
    mQuickSave->setGeometry(135,155,1010,490);
    connect(mQuickSave,SIGNAL(destroyed()),this, SLOT(setActive()));
    qobject_cast<QDialog*>(mQuickSave)->exec();
//    menuShow(RTSA_SCREEN_CAPTURE_DIALOG);
#endif
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
void BitRtSa::on_rightButton6_clicked()
{
#ifdef RTSA_F238_SMART
    InterfaceObj->DrawFlag(true);
    if(mQuickSave != NULL)
    {
        delete mQuickSave;
        mQuickSave = NULL;
    }
    mQuickSave = new RtSa_Dialog_QuickSave(this,InterfaceObj->GetDisplayMode());
    mQuickSave->setGeometry(135,155,1010,490);
    connect(mQuickSave,SIGNAL(destroyed()),this, SLOT(setActive()));
    qobject_cast<QDialog*>(mQuickSave)->exec();
#else
    menuClose();
    InterfaceObj->DrawFlag(true);
    mFileManager->showSaveDialog();
#endif
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
void BitRtSa::ChangeLcdStateWithNoSig(qint32 ilock)
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
void BitRtSa::LoadFilePara(QString strPath)
{
    InterfaceObj->DrawFlag(true);
    InterfaceObj->parseFile(strPath);
    mFileManager->onSaveFinished(1);
//    InterfaceObj->loadState(strPath);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-21
*/
void BitRtSa::saveFilePara(QString strPath, qint32 fileType)
{
    qint32 successFlag = -1;
    InterfaceObj->initFileType(fileType);
    //save File
    if(fileType == 1)
    {
        successFlag = InterfaceObj->saveState(strPath);
    }
    else if(fileType == 2)
    {
        successFlag = InterfaceObj->saveTraceData(strPath);
    }
    mFileManager->onSaveFinished(successFlag);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-21
*/
void BitRtSa::quickSaveFilePara(QString strPath, qint32 fileType)
{
    qint32 successFlag = -1;
    InterfaceObj->initFileType(fileType);
    //save File
    if(fileType == 1)
    {
        successFlag = InterfaceObj->saveState(strPath);
    }else if(fileType == 2)
    {
        successFlag = InterfaceObj->saveTraceData(strPath);
    }
    mFileManager->onFastSaveFinished(successFlag + 1);

    InterfaceObj->DrawFlag(false);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-21
*/
void BitRtSa::on_fastSaveDialogClosed()
{
    InterfaceObj->DrawFlag(false);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-21
*/
void BitRtSa::on_fileManagerWidgetClosed()
{
    InterfaceObj->DrawFlag(false);
    return;
}

void BitRtSa::BitScaleChangeSlot()
{
    menuClose();
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-21
*/
void BitRtSa::on_rightButton5_clicked()
{
#ifdef RTSA_F238_SMART
    menuClose();
    InterfaceObj->DrawFlag(true);
    mFileManager->showSaveDialog();
#else
    menuClose();
    InterfaceObj->DrawFlag(true);
    mFileManager->showFileManagerWidget();
#endif
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-23
*/
void BitRtSa::PltCurAnaMode(qint32 imode)
{
    InterfaceObj->PltCurAnaMode(imode);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-23
*/
qint32 BitRtSa::PltSavePres(qint32 itype)
{
    qint32 iback = -1;
    iback = InterfaceObj->PltSavePres(itype);
    return iback;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-23
*/
qint32 BitRtSa::PltSaveConditions(qint32 itype)
{
    qint32 iback = -1;
    iback = InterfaceObj->PltSaveConditions(itype);
    return iback;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-23
*/
qint32 BitRtSa::PltLoadConditions(qint32 itype)
{
    qint32 iback = -1;
    iback = InterfaceObj->PltLoadConditions(itype);
    return iback;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-23
*/
void BitRtSa::PresetDefaultStates()
{
//    InterfaceObj->PltSaveConditions(STATE_DEFAULT_FILE);
    InterfaceObj->loadState(RTSA_DEFAULT_COND);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-23
*/
void BitRtSa::SetDisplayMode(qint32 imode)
{
    InterfaceObj->SetDisplayMode(imode);
#ifdef RTSA_F238_SMART
    initRightButton4Style();
#endif
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-06
*/
void BitRtSa::SetSysRefuiStates(qint32 itype)
{
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-11
*/
void BitRtSa::InitAllDialog()
{
    mFreqSetup = new RtSa_Dialog_FreqSetup(InterfaceObj,mDigitInput,UserVariableObj,this);
    mFreqSetup->move(1,65);

    mAmptSetup = new RtSa_Dialog_AmptSetup(InterfaceObj,mDigitInput,this);
    mAmptSetup->move(1,65);

    mDisplaySetup = new RtSa_Dialog_SweepSetup(InterfaceObj,mDigitInput,this);
    mDisplaySetup->move(1,65);

    mBwSetup = new RtSa_Dialog_BWSetup(UserVariableObj,InterfaceObj,this);
    mBwSetup->move(1,65);

    mTriggerSetup = new RtSa_Dialog_TriggerSetup(InterfaceObj,mDigitInput,this);
    mTriggerSetup->move(1,65);

    mTraceSetup = new RtSa_Dialog_TraceSetup(InterfaceObj,mDigitInput,this);
    mTraceSetup->move(1,65);

    mMarkerSetup = new RtSa_Dialog_MarkerSetup(InterfaceObj,mDigitInput,this);
    mMarkerSetup->move(1,65);

    mLimit = new RtSa_Dialog_Limit(InterfaceObj,mDigitInput,this);
    mLimit->move(1,65);

    mMeasureSetup = new RtSa_Dialog_MeasureSetup(InterfaceObj,this);
    mMeasureSetup->move(1,65);

    mAllSetup = new RtSa_Dialog_AllSetup(InterfaceObj,mDigitInput,this);
    mAllSetup->setGeometry(1,mapToGlobal(QPoint(1,-50)).y(),1278,763);
    mAllSetup->move(1,0);

    mToolSetup = new RtSa_Dialog_ToolSetup(InterfaceObj,mDigitInput,this);
    mToolSetup->move(1,65);

    mBottomMarkerSetup = new RtSa_Dialog_BottomMarkerSetup(InterfaceObj,mDigitInput,this);
    mBottomMarkerSetup->move(1,65);

    mQuickSave = new RtSa_Dialog_QuickSave(this, InterfaceObj->GetDisplayMode());
    mQuickSave->setGeometry(135,155,1010,490);

//    mSpectrogramCursor = new RtSa_Dialog_Spectrogram_Cursor(mDigitInput, InterfaceObj,this);
//    mSpectrogramCursor->move(1,65);

    return;
}

void BitRtSa::initRightButton4Style()
{
    qint32 style = InterfaceObj->GetDisplayMode();
    switch (style) {
    case RTSA_INDOOR:
        ui->rightButton8->setStyleSheet("QPushButton{background-image: url(:/rtsa/image/btn-right-4-smart.png);} \
        QPushButton:pressed {background-image: url(:/rtsa/image/btn-right-4-click-smart.png);}");
        ui->rightButton4->setStyleSheet("QPushButton{background-image: url(:/rtsa/image/btn-right-5.png);} \
        QPushButton:pressed {background-image: url(:/rtsa/image/btn-right-5-click.png);}");
        ui->rightButton5->setStyleSheet("QPushButton{background-image: url(:/rtsa/image/btn-right-6.png);} \
        QPushButton:pressed {background-image: url(:/rtsa/image/btn-right-6-click.png);}");
        ui->rightButton6->setStyleSheet("QPushButton{background-image: url(:/rtsa/image/btn-right-7.png);} \
        QPushButton:pressed {background-image: url(:/rtsa/image/btn-right-7-click.png);}");
        ui->rightButton7->setStyleSheet("QPushButton{background-image: url(:/rtsa/image/btn-right-8.png);} \
        QPushButton:pressed {background-image: url(:/rtsa/image/btn-right-8-click.png);}");

        break;
    case RTSA_OUTDOOR:
        ui->rightButton8->setStyleSheet("QPushButton{background-image: url(:/rtsa/image/outdoor/btn-right-4-smart.png);} \
        QPushButton:pressed {background-image: url(:/rtsa/image/btn-right-4-click-smart.png);}");
        ui->rightButton4->setStyleSheet("QPushButton{background-image: url(:/rtsa/image/outdoor/btn-right-5.png);} \
        QPushButton:pressed {background-image: url(:/rtsa/image/btn-right-5-click.png);}");
        ui->rightButton5->setStyleSheet("QPushButton{background-image: url(:/rtsa/image/outdoor/btn-right-6.png);} \
        QPushButton:pressed {background-image: url(:/rtsa/image/btn-right-6-click.png);}");
        ui->rightButton6->setStyleSheet("QPushButton{background-image: url(:/rtsa/image/outdoor/btn-right-7.png);} \
        QPushButton:pressed {background-image: url(:/rtsa/image/btn-right-7-click.png);}");
        ui->rightButton7->setStyleSheet("QPushButton{background-image: url(:/rtsa/image/outdoor/btn-right-8.png);} \
        QPushButton:pressed {background-image: url(:/rtsa/image/btn-right-8-click.png);}");
        break;
    case RTSA_NIGHT:
        ui->rightButton8->setStyleSheet("QPushButton{background-image: url(:/rtsa/image/night/btn-right-4-smart.png);} \
        QPushButton:pressed {background-image: url(:/rtsa/image/btn-right-4-click-smart.png);}");
        ui->rightButton4->setStyleSheet("QPushButton{background-image: url(:/rtsa/image/night/btn-right-5.png);} \
        QPushButton:pressed {background-image: url(:/rtsa/image/btn-right-5-click.png);}");
        ui->rightButton5->setStyleSheet("QPushButton{background-image: url(:/rtsa/image/night/btn-right-6.png);} \
        QPushButton:pressed {background-image: url(:/rtsa/image/btn-right-6-click.png);}");
        ui->rightButton6->setStyleSheet("QPushButton{background-image: url(:/rtsa/image/night/btn-right-7.png);} \
        QPushButton:pressed {background-image: url(:/rtsa/image/btn-right-7-click.png);}");
        ui->rightButton7->setStyleSheet("QPushButton{background-image: url(:/rtsa/image/night/btn-right-8.png);} \
        QPushButton:pressed {background-image: url(:/rtsa/image/btn-right-8-click.png);}");
        break;
    default:
        ui->rightButton8->setStyleSheet("QPushButton{background-image: url(:/rtsa/image/btn-right-4-smart.png);} \
        QPushButton:pressed {background-image: url(:/rtsa/image/btn-right-4-click-smart.png);}");
        ui->rightButton4->setStyleSheet("QPushButton{background-image: url(:/rtsa/image/btn-right-5.png);} \
        QPushButton:pressed {background-image: url(:/rtsa/image/btn-right-5-click.png);}");
        ui->rightButton5->setStyleSheet("QPushButton{background-image: url(:/rtsa/image/btn-right-6.png);} \
        QPushButton:pressed {background-image: url(:/rtsa/image/btn-right-6-click.png);}");
        ui->rightButton6->setStyleSheet("QPushButton{background-image: url(:/rtsa/image/btn-right-7.png);} \
        QPushButton:pressed {background-image: url(:/rtsa/image/btn-right-7-click.png);}");
        ui->rightButton7->setStyleSheet("QPushButton{background-image: url(:/rtsa/image/btn-right-8.png);} \
        QPushButton:pressed {background-image: url(:/rtsa/image/btn-right-8-click.png);}");
        break;
    }
}
/**
* @brief
* @param
* @Author Albert
* @date 2020-02-11
*/
void BitRtSa::presetState()
{
    disconnect(m_thread, SIGNAL(FinishCount(int)), this, SLOT(graphRefreshFunc()));
    InterfaceObj->DrawFlag(true);
    ui->rightButton4->setDisabled(true);
    ui->topButton1->setChecked(true);
    menuClose();
    InterfaceObj->PltLoadConditions(STATE_DEFAULT_FILE);
    // change size to default
    mIsZoomIn = false;
    mDragFlag = false;
    ui->pb_Drag->setChecked(false);
    ui->rightButton10->setChecked(false);
    InterfaceObj->setDragFlag(mDragFlag);
    InterfaceObj->setZoomFlag(mIsZoomIn);
    ui->widget_Drag->move(254,65);
    this->setGeometry(1,52,1278,713);
    ShowWidget();

    ui->rightButton4->setDisabled(false);
    emit PltAllPresetSig();
    InterfaceObj->DrawFlag(false);
    connect(m_thread, SIGNAL(FinishCount(int)), this, SLOT(graphRefreshFunc()));
    return;
}
//void BitRtSa::resizeScale(qreal Xsize, qreal Ysize)
//{
//    ui->XScale->setText(QString::number(Xsize));
//    ui->YScale->setText(QString::number(Ysize));
//    return;
//}
