#include "bitrtsaremote.h"
#include "ui_rtsaremote.h"
#include "rtsa_user_variable.h"
#include <QDebug>
#include "rect_define.h"
#include <QFile>
#include <QKeyEvent>
#include <math.h>
#include <QMessageBox>

//extern int rtsa_homeuiHandle;
//extern int RTSA_guiHandle;
//extern void V_RTSA_sem(int handle);
//extern pthread_mutex_t RTSA_lockobj;
BitRtSaRemote::BitRtSaRemote(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BitRtSaRemote),
    mWarningSetUp(NULL),
    mLimit(NULL),
    mCurSetupDialog(NULL),
    mIsZoomIn(false),
    mShiftKeyPressed(false),
    mCurMenuID(-1),
//    mLastAcqTime(0),
    mDragFlag(false),
    touchSignal(0),
    mStyleIndex(-1)
{
    setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->setupUi(this);
//    this->setFocus();
    this->setFocusPolicy(Qt::StrongFocus);

    //modifier main window to user size
    this->resize(RTSA_WINDOW_WIDTH,RTSA_WINDOW_HEIGHT);
    this->setAttribute(Qt::WA_NoChildEventsFromChildren,true);
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    this->setAttribute(Qt::WA_StyledBackground,true);
    // this function must initial at first.

    initGlobalInterface();

    InitMarkerGroup();
    InitBottomLayOut();
    InitBitview();
    initWidget();
    InitAllDialog();

    //set qss mode for indoor,outdoor or night;
    this->setProperty("status",rtsa_qssMode[RemoteInterfaceObj->GetDisplayMode()]);

//    connect(psa_UIRefresh_Control,SIGNAL(refreshRemote(QString)),pcontrolInterface,SIGNAL(sendSCPIcmd(QString)));

    initThread();
    InitLeftInfoWidget();
    InitFileManager();

  //  QApplication::setOverrideCursor(Qt::BlankCursor);
    //default set freq button checked
//    ui->topButton1->setChecked(true);
}

BitRtSaRemote::~BitRtSaRemote()
{
    m_thread->rtsa_thread_state = 0;
//    V_RTSA_sem(RTSA_guiHandle);
    QThread::msleep(200);
    m_thread->quit();  // Thread quit
    delete UserVariableObj;
    delete RemoteInterfaceObj;
    delete mBtnGroup;
    deleteWidget();
    delete bomLayout;
    delete ui;

}

void BitRtSaRemote::connectStatusChange(qint32 pStatus)
{
    if(RemoteInterfaceObj->pSocketLinkStatus != pStatus)
    {
        RemoteInterfaceObj->pSocketLinkStatus = pStatus;
        m_thread->SetLinkFlg(pStatus);
    }
    return;
}

/**
 * @brief init interface, all I/O control interface
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void BitRtSaRemote::initGlobalInterface()
{
    // Single instantiation RtSa_User_Variable
    UserVariableObj = new RtSa_User_Variable(this);
    RemoteInterfaceObj = new Rtsa_Remote_Interface(this);
    connect(RemoteInterfaceObj,SIGNAL(MarkerOn(bool)),this,SLOT(MarkerWidgetHide(bool)));
    connect(RemoteInterfaceObj,SIGNAL(BitViewMakerDraw(qint32,bool)),this,SLOT(MarkerInfoChange(qint32,bool)));
    connect(RemoteInterfaceObj,SIGNAL(MarkerSelectOnOff(qint32,bool)),this,SLOT(MarkerSelect(qint32,bool)));
    connect(RemoteInterfaceObj,SIGNAL(ParentFocus()),this,SLOT(setDialogActive()));
    connect(RemoteInterfaceObj,SIGNAL(RedrawInfoShow(qint32)),this,SLOT(leftInfo_Update(qint32)));
    connect(RemoteInterfaceObj,SIGNAL(MarkerPosChanged(bool)),this,SLOT(marker_changed(bool)));
    connect(RemoteInterfaceObj,SIGNAL(BitViewChanged(quint32)),this,SLOT(BitViewMarkerRefresh(quint32)));
    RemoteInterfaceObj->setGobalVariable(UserVariableObj);
}
/**
 * @brief init data thread
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void BitRtSaRemote::initThread()
{
    m_thread = new RtSa_ThreadGraph(this);
    m_thread->setGobalVariable(UserVariableObj);
    m_thread->setInterface(RemoteInterfaceObj);
    connect(m_thread, SIGNAL(FinishCount(int)), this, SLOT(graphRefreshFunc()));
    m_thread->start();
}
/**
 * @brief init bitview
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void BitRtSaRemote::deleteWidget()
{
//    if(mCurSetupDialog != NULL)
//    {
//        delete mCurSetupDialog;
//        mCurSetupDialog = NULL;
//    }
    this->setFocus();
    return;
}
void BitRtSaRemote::InitBottomLayOut()
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
void BitRtSaRemote::InitMarkerGroup()
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
void BitRtSaRemote::InitBitview()
{
    RemoteInterfaceObj->InitBitView(this);
}
/**
 * @brief  Initialization widget.
 * @param  void
 * @return void
 * @author Tony
 * @since 2018-12-18
*/
void BitRtSaRemote::initWidget(void)
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
    mDigitInput->setInterface(RemoteInterfaceObj);
    mDigitInput->setUserVariable(UserVariableObj);
//    mDigitInput->setProperty("status",rtsa_qssMode[InterfaceObj->GetDisplayMode()]);
//    connect(mDigitInput,SIGNAL(ClockWiseDown()),this,SLOT(ClockKeyDown()));

    mCurSetupDialog = new RtSa_Dialog_FreqSetup(RemoteInterfaceObj,mDigitInput,UserVariableObj,this);
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
void BitRtSaRemote::InitStyleSheet(qint32 index)
{
    if(mStyleIndex == index)
        return;
    mStyleIndex = index;
    QString filename[3]={":/rtsa/stylesheet/default.qss",":/rtsa/stylesheet/night.qss",":/rtsa/stylesheet/outdoor.qss"};
    QFile qss(filename[mStyleIndex]);
    if(!qss.open(QFile::ReadOnly))
    {
        qCritical("Rtsa qss file open failed");
        return;
    }
    this->setStyleSheet(qss.readAll());
    qss.close();
    this->setProperty("status",rtsa_qssMode[RemoteInterfaceObj->GetDisplayMode()]);

    return;
}
/**
 * @brief change size
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void BitRtSaRemote::resizeEvent(QResizeEvent *event)
{
    this->setFocus();
    RemoteInterfaceObj->changeSize(this->width(),this->height());
//    ui->widget_bk->resize(this->width(),this->height());
    if(mIsZoomIn)
    {
       RemoteInterfaceObj->setZoomIn();
    }
    else
    {
        RemoteInterfaceObj->setZoomOut();
    }
//    InitStyleSheet(0);
    return;
}
/**
 * @brief BitRtSaRemote::keyPressEvent
 * @param event
 */
void BitRtSaRemote::keyPressEvent(QKeyEvent *event)
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
void BitRtSaRemote::keyRespond(qint32 key)
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
        case RTSA_FREQ_DIALOG:
            RemoteInterfaceObj->setCenterFreq(RemoteInterfaceObj->getCenterFreq() + RemoteInterfaceObj->getStepFreq());
            break;
        case RTSA_AMPT_DIALOG:
            RemoteInterfaceObj->setRefLevel(RemoteInterfaceObj->getRefLevel() + 1);
            break;
        case RTSA_MARKER_DIALOG:
            freq = RemoteInterfaceObj->getMarkerFreq(RemoteInterfaceObj->getCurMarkerID());
            freqstep = (RemoteInterfaceObj->getSpan() / (RTSA_NUM_SWEEP_POINT - 1));
            //Albert 19/01/31 when span < sweep_pts, step should set 1;
            if(RemoteInterfaceObj->getSpan() < (RTSA_NUM_SWEEP_POINT - 1))
            {
                freqstep = 1;
            }
            RemoteInterfaceObj->setMarkerFreq(RemoteInterfaceObj->getCurMarkerID(),freq + freqstep);
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
            if(RemoteInterfaceObj->getStepFreq() >= RemoteInterfaceObj->getCenterFreq())
            {
                RemoteInterfaceObj->setCenterFreq(0);
            }
            else
            {
                RemoteInterfaceObj->setCenterFreq(RemoteInterfaceObj->getCenterFreq() - RemoteInterfaceObj->getStepFreq());
            }
            break;
        case RTSA_MARKER_DIALOG:
            freq = RemoteInterfaceObj->getMarkerFreq(RemoteInterfaceObj->getCurMarkerID());
            freqstep = (RemoteInterfaceObj->getSpan() / (RTSA_NUM_SWEEP_POINT - 1));
            if(RemoteInterfaceObj->getSpan() < (RTSA_NUM_SWEEP_POINT - 1))
            {
                freqstep = 1;
            }
            RemoteInterfaceObj->setMarkerFreq(RemoteInterfaceObj->getCurMarkerID(),freq - freqstep);
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
            mCurMenuID = RTSA_FREQ_DIALOG;
            menuShow(mCurMenuID);
            mShiftKeyPressed = false;
            mBtnGroup->button(RTSA_FREQ_DIALOG)->setChecked(true);
        }
        break;
    case Qt::Key_2:
        if(mShiftKeyPressed)
        {
//              V_RTSA_sem(rtsa_homeuiHandle);
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
            RemoteInterfaceObj->setMarkerOn(RemoteInterfaceObj->getCurMarkerID(),true);
            RemoteInterfaceObj->setMarkerToCenter();
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
            ui->topButton1->setChecked(true);
//            mBtnGroup->checkedButton()->setChecked(false);
//            InterfaceObj->PltSaveConditions(STATE_DEFAULT_FILE);
//            InterfaceObj->loadState(RTSA_DEFAULT_COND);
            if(!ui->topButton7->isChecked())
                RemoteInterfaceObj->showMarkerWidget(false);
            mShiftKeyPressed = false;
            emit PltAllPresetSig();
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
 * @brief BitRtSaRemote::mousePressEvent
 * here must consider set dialog focus, in order to respond keypress
 * @param event
 */
void BitRtSaRemote::mousePressEvent(QMouseEvent *event)
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
void BitRtSaRemote::graphRefreshFunc()
{
    if(RemoteInterfaceObj->getDrawFlag())
        return;
//    pthread_mutex_lock(&RTSA_lockobj);
    RemoteInterfaceObj->Draw();
//    pthread_mutex_unlock(&RTSA_lockobj);
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
void BitRtSaRemote::menuHide(qint32 menuID, bool visible)
{
    RemoteInterfaceObj->setLimitTableShow(false);
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
void BitRtSaRemote::menuShow(qint32 menuID)
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
        if(RemoteInterfaceObj->getCurBitviewType() == RTSA_SPECTROGRAM)
        {
            mWarningSetUp = new RtSa_Dialog_Warning("Notice","Can not operator Marker in Spectrogram",this,RemoteInterfaceObj->GetDisplayMode());
            mWarningSetUp->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
            mWarningSetUp->ShowYesButtonOnly();
//            this->setUpdatesEnabled(true);
            if(mWarningSetUp->exec() != QDialog::Accepted)
            {
                return;
            }
            return;
        }
        mMarkerSetup->initDisplay();
        mCurSetupDialog = mMarkerSetup;
        RemoteInterfaceObj->showMarkerWidget(true);
        break;
    case RTSA_OBSERVE_DIALOG:
        menuClose();
        if(RemoteInterfaceObj->getCurBitviewType() != RTSA_SPECTRUM)
        {
            mWarningSetUp = new RtSa_Dialog_Warning("Notice","Limit only be used in spectrum",this,RemoteInterfaceObj->GetDisplayMode());
            mWarningSetUp->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
            mWarningSetUp->ShowYesButtonOnly();
//            this->setUpdatesEnabled(true);
            if(mWarningSetUp->exec() != QDialog::Accepted)
            {
                return;
            }
            return;
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
        RemoteInterfaceObj->setCurMarkerID(RTSA_M1);
        mBottomMarkerSetup->refreshDisplay();
        mCurSetupDialog = mBottomMarkerSetup;
//        mMarkerButton[RTSA_M1]->setStyleSheet("QPushButton{border-image: url(:/rtsa/image/marker_table_editting.png);}");
        break;
    case RTSA_MARKER2_DIALOG:
        menuClose();
        RemoteInterfaceObj->setCurMarkerID(RTSA_M2);
        mBottomMarkerSetup->refreshDisplay();
        mCurSetupDialog = mBottomMarkerSetup;
//        mMarkerButton[RTSA_M2]->setStyleSheet("QPushButton{border-image: url(:/rtsa/image/marker_table_editting.png);}");
        break;
    case RTSA_MARKER3_DIALOG:
        menuClose();
        RemoteInterfaceObj->setCurMarkerID(RTSA_M3);
        mBottomMarkerSetup->refreshDisplay();
        mCurSetupDialog = mBottomMarkerSetup;
//        mMarkerButton[RTSA_M3]->setStyleSheet("QPushButton{border-image: url(:/rtsa/image/marker_table_editting.png);}");
        break;
    case RTSA_MARKER4_DIALOG:
        menuClose();
        RemoteInterfaceObj->setCurMarkerID(RTSA_M4);
        mBottomMarkerSetup->refreshDisplay();
        mCurSetupDialog = mBottomMarkerSetup;
//        mMarkerButton[RTSA_M4]->setStyleSheet("QPushButton{border-image: url(:/rtsa/image/marker_table_editting.png);}");
        break;
    case RTSA_MARKER5_DIALOG:
        menuClose();
        RemoteInterfaceObj->setCurMarkerID(RTSA_M5);
        mBottomMarkerSetup->refreshDisplay();
        mCurSetupDialog = mBottomMarkerSetup;
//        mMarkerButton[RTSA_M5]->setStyleSheet("QPushButton{border-image: url(:/rtsa/image/marker_table_editting.png);}");
        break;
    case RTSA_MARKER6_DIALOG:
        menuClose();
        RemoteInterfaceObj->setCurMarkerID(RTSA_M6);
        mBottomMarkerSetup->refreshDisplay();
        mCurSetupDialog = mBottomMarkerSetup;
//        mMarkerButton[RTSA_M6]->setStyleSheet("QPushButton{border-image: url(:/rtsa/image/marker_table_editting.png);}");
        break;
    case RTSA_MEAS_TOOL_DIALOGL:
        menuClose();
        if(RemoteInterfaceObj->getDisplay() != RTSA_DENSITY)
        {
            return;
        }
        mToolSetup->InitDisplay();
        mCurSetupDialog = mToolSetup;
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
    mCurSetupDialog->setProperty("status",rtsa_qssMode[RemoteInterfaceObj->GetDisplayMode()]);
    mCurSetupDialog->setStyle(QApplication::style());
    if(menuID == RTSA_SCREEN_CAPTURE_DIALOG)
    {
        qobject_cast<QDialog*>(mCurSetupDialog)->exec();
    }
    else
    {
        mCurSetupDialog->setProperty("status",rtsa_qssMode[RemoteInterfaceObj->GetDisplayMode()]);
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
void BitRtSaRemote::on_rightButton8_clicked()
{
    menuClose();
    emit SysSetSig();
    ui->rightButton8->setChecked(false);
    return;
}

void BitRtSaRemote::on_rightButton9_clicked()
{
//  V_RTSA_sem(rtsa_homeuiHandle);
  ui->rightButton9->setChecked(true);
  return;
}
void BitRtSaRemote::on_rightButton10_clicked()
{
    menuClose();
    if(mIsZoomIn)
    {
        mIsZoomIn = false;
        RemoteInterfaceObj->setZoomFlag(mIsZoomIn);
        this->setGeometry(1,52,1278,713);
        ShowWidget();
//        emit ZoomIn(false);
    }
    else
    {
        mIsZoomIn = true;
        RemoteInterfaceObj->setZoomFlag(mIsZoomIn);
        this->setGeometry(0,0,1280,765);
        HideWidget();
//        emit ZoomIn(true);
    }
    return;
}

void BitRtSaRemote::HideWidget()
{
    mDigitInput->hide();
//    mAllSetup->hide();
    if(RemoteInterfaceObj->IsMarkerAlreadyOn() || ui->topButton7->isChecked())
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
void BitRtSaRemote::ShowWidget()
{
    if(RemoteInterfaceObj->IsMarkerAlreadyOn() || ui->topButton7->isChecked())
    {
        ui->rtsa_buttomMarker->show();
        if(RemoteInterfaceObj->getDragFlag())
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
    if(!RemoteInterfaceObj->getDragFlag())
        ui->rtsa_leftInfoWidget->show();
//    ui->widget_bottomSpace->resize(943,2);
//    ui->widget_bottomSpace->move(276,639);

//    ui->widget_topSpace->resize(943,3);
//    ui->widget_topSpace->move(255,65);
    ui->rightButtonBar->resize(84,648);
    ui->rightButtonBar->move(1195,65);
    ui->rightButton10->move(3,591);

    return;
}

void BitRtSaRemote::InitLeftInfoWidget()
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

void BitRtSaRemote::MarkerWidgetHide(bool isOn)
{
    if(isOn)
    {
        ui->rtsa_buttomMarker->show();
        if(mIsZoomIn)
        {
        }
        else
        {
            if(RemoteInterfaceObj->getDragFlag())
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
void BitRtSaRemote::MarkerInfoChange(qint32 markerID,bool isOn)
{
    if(!isOn)
    {
        return;
    }
    QString strInfo = QString("M%1\n").arg(markerID + 1);
    qreal freq1 = RemoteInterfaceObj->getMarkerRefFreq(markerID);
    qreal freq2 = RemoteInterfaceObj->getMarkerDeltaFreq(markerID);
    qreal freq = (qreal)freq1;
    if(RemoteInterfaceObj->getMarkerType(markerID) == RTSA_DELTA)
    {
        freq = (qreal)freq2 - (qreal)freq1;
        strInfo = QString("D%1\n").arg(markerID + 1);
    }
    switch(markerID)
    {
    case RTSA_M1:
        strInfo += RemoteInterfaceObj->getFreqAdjustStr(freq);
        strInfo += QString("\n");
        strInfo += RemoteInterfaceObj->getMarkerInfoStr(markerID);
        strInfo += QString("\n");
        break;
    case RTSA_M2:
        strInfo += RemoteInterfaceObj->getFreqAdjustStr(freq);
        strInfo += QString("\n");
        strInfo += RemoteInterfaceObj->getMarkerInfoStr(markerID);
        strInfo += QString("\n");
        break;
    case RTSA_M3:
        strInfo += RemoteInterfaceObj->getFreqAdjustStr(freq);
        strInfo += QString("\n");
        strInfo += RemoteInterfaceObj->getMarkerInfoStr(markerID);
        strInfo += QString("\n");
        break;
    case RTSA_M4:
        strInfo += RemoteInterfaceObj->getFreqAdjustStr(freq);
        strInfo += QString("\n");
        strInfo += RemoteInterfaceObj->getMarkerInfoStr(markerID);
        strInfo += QString("\n");
        break;
    case RTSA_M5:
        strInfo += RemoteInterfaceObj->getFreqAdjustStr(freq);
        strInfo += QString("\n");
        strInfo += RemoteInterfaceObj->getMarkerInfoStr(markerID);
        strInfo += QString("\n");
        break;
    case RTSA_M6:
        strInfo += RemoteInterfaceObj->getFreqAdjustStr(freq);
        strInfo += QString("\n");
        strInfo += RemoteInterfaceObj->getMarkerInfoStr(markerID);
        strInfo += QString("\n");
        break;
    default:
        strInfo += RemoteInterfaceObj->getFreqAdjustStr(freq);
        strInfo += QString("\n");
        strInfo += RemoteInterfaceObj->getMarkerInfoStr(markerID);
        strInfo += QString("\n");
        break;
    }
    mMarkerButton[markerID]->setText(strInfo);
//    mMarkerButtonGroup[curMarker]->setChecked(true);
    return;
}
void BitRtSaRemote::MarkerSelect(qint32 MarkerID, bool isOn)
{
    qint32 curMarker = RemoteInterfaceObj->getCurMarkerID();
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
void BitRtSaRemote::BitViewMarkerRefresh(quint32 MarkerID)
{
    if(ui->topButton8->isChecked() )
    {
        if(((mLimit != NULL) &&(!mLimit->isHidden()))|| (mCurSetupDialog != NULL))
        if(RemoteInterfaceObj->getCurBitviewType() != RTSA_SPECTRUM)
        {
            menuClose();
            mWarningSetUp = new RtSa_Dialog_Warning("Notice","Limit only be used in spectrum",this,RemoteInterfaceObj->GetDisplayMode());
            mWarningSetUp->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
            mWarningSetUp->ShowYesButtonOnly();
            if(mWarningSetUp->exec() != QDialog::Accepted)
            {
                return;
            }
            return;
        }
    }
    qint32 curMarker = RemoteInterfaceObj->getCurMarkerID();
    mMarkerButton[curMarker]->setChecked(true);
    QString strInfo;
    for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
    {
        if(!RemoteInterfaceObj->isMarkerOn(i))
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
void BitRtSaRemote::MenuClose()
{
    menuClose();
    return;
}
void BitRtSaRemote::menuClose()
{
//    InterfaceObj->DrawFlag(true);
    if(mCurSetupDialog != NULL)
    {
        mCurSetupDialog->hide();
        if(mCurSetupDialog == mFreqSetup)
        {
            mFreqSetup->HideChStdDialog();
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
//    if(mLimit != NULL && !mLimit->isHidden())
//    {
//       mLimit->hide();
//    }
//    if(mBottomMarkerSetup != NULL)
//    {
//        delete mBottomMarkerSetup;
//        mBottomMarkerSetup = NULL;
//    }
//    mBottomMarkerSetup->hide();
    mDigitInput->hide();
//    mAllSetup->hide();
    if(!ui->topButton7->isChecked())
    {
        RemoteInterfaceObj->showMarkerWidget(false);
    }
//    emit KeyEventSig(Qt::Key_Escape);
    this->setUpdatesEnabled(true);
    return;
}
/**
 * @brief BitRtSaRemote::setActive
 * this function is used for dialog close,
 * because mCurSetupDialog has already destroyed,
 * here just set NULL.
 */
void BitRtSaRemote::setActive()
{
//    mLastAcqTime = InterfaceObj->getAcqTime();
//    InterfaceObj->setSleepTime(mLastAcqTime);
//    mLimit = NULL;
//    mCurSetupDialog = NULL;
//    mBottomMarkerSetup = NULL;
    mQuickSave = NULL;
    mMarkerButton[RemoteInterfaceObj->getCurMarkerID()]->setStyleSheet("");
//    emit KeyEventSig(Qt::Key_Escape);
    if(RemoteInterfaceObj->isShiftKeyEnable())
    {
        keyRespond(Qt::Key_Shift);
        RemoteInterfaceObj->setShiftKeyEnable(false);
    }
    if(mWarningSetUp != NULL)
    {
        delete mWarningSetUp;
        mWarningSetUp = NULL;
    }
    RemoteInterfaceObj->DrawFlag(false);
    this->setFocus();
    return;
}
void BitRtSaRemote::ClockKeyDown()
{
//    MenuClose();
    mDigitInput->close();
    mCurSetupDialog->setFocus();
    return;
}
void BitRtSaRemote::setDialogActive()
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
void BitRtSaRemote::on_pb_Drag_clicked()
{
    menuClose();
    if(mDragFlag)
    {
        mDragFlag = false;
        RemoteInterfaceObj->setDragFlag(mDragFlag);
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
        RemoteInterfaceObj->setDragFlag(mDragFlag);
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

void BitRtSaRemote::on_pb_marker_AllOff_2_clicked()
{
    menuClose();
    for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT;i++)
    {
        RemoteInterfaceObj->setMarkerOn(i,false);
    }
    if(ui->topButton7->isChecked())
    {
        RemoteInterfaceObj->showMarkerWidget(true);
    }
    RemoteInterfaceObj->setZoomFlag(mIsZoomIn);
    return;
}

void BitRtSaRemote::leftInfo_Update(qint32 infoID)
{
    QString strGab = "";
    qint32 intGab = 0;
    qint32 intCurAvg = 0;
    qreal fGab = 0.0;
    QString strInfo;
    qint32 mCurTraceID = RemoteInterfaceObj->getCurTrace();
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
        intGab = RemoteInterfaceObj->getDisplay();
        if(intGab == RTSA_SPECTRUM)
        {
            ui->lblmeasure->setText("Persistent spectrum");
        }
        else if(intGab == RTSA_SPECTROGRAM)
        {
            ui->lblmeasure->setText("Persistent spectogram");
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
        strGab = RemoteInterfaceObj->getFreqAdjustStr(RemoteInterfaceObj->getCenterFreq());
        ui->lblCenterFreqValue->setText(strGab);
        break;
    case LABEL_SIGNAL_STANDARD:
        if(UserVariableObj->gMeterParam.gConfig_FreqSpan.channelStd < 0 || !UserVariableObj->IsFreqInCurChStd())
        {
            strGab = "None";
        }
        else
        {
            strGab = QString(mRTSA_ChStand[UserVariableObj->gMeterParam.gConfig_FreqSpan.channelStd].name);
        }
        ui->lblCHStandardValue->setText(strGab);
        break;
    case LABEL_CHANNEL:
        if(UserVariableObj->gMeterParam.gConfig_FreqSpan.channelStd < 0 || !UserVariableObj->IsFreqInCurChStd())
        {
            strGab = "None";
        }
        else
        {
            strGab = QString::number(RemoteInterfaceObj->getChannelNumber());
        }
        ui->lblChannelValue->setText(strGab);
        break;
    case LABEL_PREAMP:
        intGab = RemoteInterfaceObj->IsPreAmpOn();
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
        intGab = RemoteInterfaceObj->IsAttenAuto();
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
        fGab = RemoteInterfaceObj->getAttenVal();
        strGab = QString::number(fGab) + QString("  dB");
        ui->lblAttenValue->setText(strGab);
        break;
    case LABEL_RBW_STATUS:
        intGab = RemoteInterfaceObj->IsBWAuto();
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
        intGab = RemoteInterfaceObj->getAvgNum(mCurTraceID);
        intCurAvg = RemoteInterfaceObj->getCurAvgNum(mCurTraceID);
        if(!RemoteInterfaceObj->IsAvgOn(mCurTraceID))
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
    case LABEL_TRACE1_STATUS:
    case LABEL_TRACE2_STATUS:
    case LABEL_TRACE3_STATUS:
    case LABEL_TRACE4_STATUS:
    case LABEL_TRACE5_STATUS:
    case LABEL_TRACE6_STATUS:
        refreshTraceStatus();
        break;
    case LABEL_RBW:
        fGab = RemoteInterfaceObj->getBW();
        strGab = RemoteInterfaceObj->getFreqAdjustStr(fGab,3);
        ui->lblRBWValue->setText(strGab);
        break;
    case LABEL_FFTWINDOW:
        strGab = RemoteInterfaceObj->getFFTWindowStr();
        ui->lblFFTValue->setText(strGab);
        break;
    case LABEL_ACQTIME:
        fGab = RemoteInterfaceObj->getAcqTime();
        strGab = RemoteInterfaceObj->getAdjustTimeStr(fGab);
        ui->lblAcqtimeValue->setText(strGab);
        break;
    case LABEL_PERSISTENCE:
        intGab = RemoteInterfaceObj->IsPersistenceTimeInfinite();
        if(intGab == 0)
        {
            ui->lblPerTimeInfinite->setText("Infinite");
        }
        else
        {
            ui->lblPerTimeInfinite->setText("Finite");
        }
        fGab = RemoteInterfaceObj->getPersistenceTime();
        strGab = RemoteInterfaceObj->getAdjustTimeStr(fGab);
        ui->lblPersTimeValue->setText(strGab);
        break;
    case LABEL_FREQ_REF:
        break;
    case LABEL_TRIGGER:
        intGab = RemoteInterfaceObj->getTrigger();
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
        case RTSA_TRIGGER_FMTMASK:
            ui->lblTrigger->setText("FMT");
            break;
        default:
            ui->lblTrigger->setText("Free Run");
            break;

        }
        break;
    case LABEL_DETECTOR:
        intGab = RemoteInterfaceObj->getDectorType();
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
        intGab = RemoteInterfaceObj->isHaveLimitOn();
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
        fGab = RTSA_POIList[UserVariableObj->gRbwGrade][UserVariableObj->gMeterParam.gConfig_BW.rbwIndex];
        strGab = RemoteInterfaceObj->getAdjustTimeStr(fGab);
        ui->lblPOIValue->setText(strGab);
        break;
    case LABEL_DISPLAY:
        this->setProperty("status",rtsa_qssMode[RemoteInterfaceObj->GetDisplayMode()]);
        setStyle(QApplication::style());
        break;
    default:
        break;
    }
    return;
}
void BitRtSaRemote::on_WidgetClicked()
{
    qint32 index;
    RtSa_ClickedWidget* widget = qobject_cast<RtSa_ClickedWidget*>(sender());
    index = mRtSaInfoWidget->value(widget);
    mBtnGroup->button(index)->setChecked(true);
    menuShow(index);
    return;
}

void BitRtSaRemote::refreshTraceStatus()
{
    qint32 trace,type;
//    qint32 status;
    QString strqss,strbg,strTrace;
    trace = RemoteInterfaceObj->getCurTrace();
    for(qint32 i=0;i<RTSA_NUM_TRACE;i++)
    {
//        strqss = QString("");
//        status = pcontrolInterface->getTraceViewStatus(i);
        type = RemoteInterfaceObj->getTraceType(i);
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

void BitRtSaRemote::refreshTraceType()
{
    qint32 traceNo,traceType;
//   qint32 traceView;
    QString strInfo,strQss;
    for(int i=0;i<RTSA_NUM_TRACE;i++)
    {
        traceNo = RemoteInterfaceObj->getCurTrace();
        traceType = RemoteInterfaceObj->getTraceType(i);
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
        if(traceType == RTSA_ON)
        {
            strQss = QString("#lblTypeT%1{background-image: url(:/rtsa/image/%2_bk.png);}\n").arg(QString::number(i+1)).arg(strInfo);
        }else
        {
            strQss = QString("#lblTypeT%1{background-image: url(:/rtsa/image/%2_bk_off.png);}\n").arg(QString::number(i+1)).arg("W");
        }
        //Miss the picture of current trace and that is on
        if((i != traceNo)&& (traceType != RTSA_OFF))
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
        }else if((i == traceNo)&& (traceType != RTSA_OFF))
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
void BitRtSaRemote::InitFileManager()
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
 * @brief BitRtSaRemote::on_rightButton1_clicked
 * Peak search
 */
void BitRtSaRemote::on_rightButton1_clicked()
{
    menuClose();
    qint32 markerID = RemoteInterfaceObj->getCurMarkerID();
    RemoteInterfaceObj->setMarkerOn(markerID,true);
    RemoteInterfaceObj->setMarkerToPeak();
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
 * @brief BitRtSaVnc::on_rightButton3_clicked
 * auto scale
 */
void BitRtSaRemote::on_rightButton3_clicked()
{
    menuClose();
    RemoteInterfaceObj->setAutoScale();
    mBtnGroup->button(RTSA_AMPT_DIALOG)->setChecked(true);
    return;
}
void BitRtSaRemote::SetMeasureItems(qint32 imea)
{
    RemoteInterfaceObj->setDisplay(imea);
    return;
}

void BitRtSaRemote::marker_changed(bool isChanged)
{
    if(mCurMenuID == RTSA_MARKER_DIALOG || (mCurMenuID >= RTSA_MARKER1_DIALOG && mCurMenuID <= RTSA_MARKER6_DIALOG))
        return;
    if(isChanged && mCurMenuID != RTSA_MARKER_DIALOG)
    {
        menuClose();
        mCurMenuID = RTSA_MARKER_DIALOG;
    }
    return;
}

void BitRtSaRemote::on_rightButton4_clicked()
{
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
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
void BitRtSaRemote::on_rightButton2_clicked()
{
    if(RemoteInterfaceObj->getCurBitviewType() != RTSA_SPECTRUM)
    {
        mWarningSetUp = new RtSa_Dialog_Warning("Notice","Limit only be used in spectrum",this,RemoteInterfaceObj->GetDisplayMode());
        mWarningSetUp->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
        mWarningSetUp->ShowYesButtonOnly();
        if(mWarningSetUp->exec() != QDialog::Accepted)
        {
            return;
        }
        return;
    }
    RemoteInterfaceObj->BuildLimitFromTrace();
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
void BitRtSaRemote::SetLocalRemoteMode(qint32 mode)
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
//qint32 BitRtSaRemote::GetLocalRemoteMode()
//{
//    return UserVariableObj->gLocal;
//}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
void BitRtSaRemote::on_rightButton7_clicked()
{
//    menuClose();
    RemoteInterfaceObj->DrawFlag(true);
    if(mQuickSave != NULL)
    {
        delete mQuickSave;
        mQuickSave = NULL;
    }
    mQuickSave = new RtSa_Dialog_QuickSave(this,RemoteInterfaceObj->GetDisplayMode());
    mQuickSave->setGeometry(135,155,1010,490);
    connect(mQuickSave,SIGNAL(destroyed()),this, SLOT(setActive()));
    qobject_cast<QDialog*>(mQuickSave)->exec();
//    menuShow(RTSA_SCREEN_CAPTURE_DIALOG);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
void BitRtSaRemote::on_rightButton6_clicked()
{
//    InterfaceObj->PltSaveConditions(STATE_USER_FILE);
    menuClose();
    RemoteInterfaceObj->DrawFlag(true);
//    pcontrolInterface->setSuspendFunc(1);
    mFileManager->showSaveDialog();
//    pcontrolInterface->setSuspendFunc(0);
//    m_user_variable->bShiftKeyPressed = false;
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
void BitRtSaRemote::ChangeLcdStateWithNoSig(qint32 ilock)
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
void BitRtSaRemote::LoadFilePara(QString strPath)
{
    RemoteInterfaceObj->DrawFlag(true);
    RemoteInterfaceObj->parseFile(strPath);
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
void BitRtSaRemote::saveFilePara(QString strPath, qint32 fileType)
{
    qint32 successFlag;
    RemoteInterfaceObj->initFileType(fileType);
    //save File
    if(fileType == 1)
    {
        successFlag = RemoteInterfaceObj->saveState(strPath);
    }
    else if(fileType == 2)
    {
        successFlag = RemoteInterfaceObj->saveTraceData(strPath);
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
void BitRtSaRemote::quickSaveFilePara(QString strPath, qint32 fileType)
{
    qint32 successFlag;
    RemoteInterfaceObj->initFileType(fileType);
    //save File
    if(fileType == 1)
    {
        successFlag = RemoteInterfaceObj->saveState(strPath);
    }else if(fileType == 2)
    {
        successFlag = RemoteInterfaceObj->saveTraceData(strPath);
    }
    mFileManager->onFastSaveFinished(successFlag + 1);

    RemoteInterfaceObj->DrawFlag(false);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-21
*/
void BitRtSaRemote::on_fastSaveDialogClosed()
{
    RemoteInterfaceObj->DrawFlag(false);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-21
*/
void BitRtSaRemote::on_fileManagerWidgetClosed()
{
    RemoteInterfaceObj->DrawFlag(false);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-21
*/
void BitRtSaRemote::on_rightButton5_clicked()
{
    menuClose();
    RemoteInterfaceObj->DrawFlag(true);
    mFileManager->showFileManagerWidget();
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-23
*/
void BitRtSaRemote::PltCurAnaMode(qint32 imode)
{
    RemoteInterfaceObj->PltCurAnaMode(imode);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-23
*/
qint32 BitRtSaRemote::PltSavePres(qint32 itype)
{
    qint32 iback = -1;
    iback = RemoteInterfaceObj->PltSavePres(itype);
    return iback;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-08-23
*/
void BitRtSaRemote::PltCurLinkMode(qint32 imode)
{
    RemoteInterfaceObj->PltCurLinkMode(imode);
    return;
}
/**
* @brief Platform setting link flag
* @param  Link Flg
* @Author Roc
* @date 2019-10-18
*/
qint32 BitRtSaRemote::PltSaveLinkFlg(qint32 itype)
{
    qint32 ireturnData = -1;
    ireturnData = RemoteInterfaceObj->PltSaveLinkFlg(itype);
    return ireturnData;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-23
*/
qint32 BitRtSaRemote::PltSaveConditions(qint32 itype)
{
    qint32 iback = -1;
    iback = RemoteInterfaceObj->PltSaveConditions(itype);
    return iback;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-23
*/
qint32 BitRtSaRemote::PltLoadConditions(qint32 itype)
{
    qint32 iback = -1;
    iback = RemoteInterfaceObj->PltLoadConditions(itype);
    return iback;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-23
*/
void BitRtSaRemote::PresetDefaultStates()
{
//    InterfaceObj->PltSaveConditions(STATE_DEFAULT_FILE);
    RemoteInterfaceObj->loadState(RTSA_DEFAULT_COND);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-23
*/
void BitRtSaRemote::SetDisplayMode(qint32 imode)
{
    RemoteInterfaceObj->SetDisplayMode(imode);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-06
*/
void BitRtSaRemote::SetSysRefuiStates(qint32 itype)
{
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-11
*/
void BitRtSaRemote::InitAllDialog()
{
    mFreqSetup = new RtSa_Dialog_FreqSetup(RemoteInterfaceObj,mDigitInput,UserVariableObj,this);
    mFreqSetup->move(1,65);

    mAmptSetup = new RtSa_Dialog_AmptSetup(RemoteInterfaceObj,mDigitInput,this);
    mAmptSetup->move(1,65);

    mDisplaySetup = new RtSa_Dialog_SweepSetup(RemoteInterfaceObj,mDigitInput,this);
    mDisplaySetup->move(1,65);

    mBwSetup = new RtSa_Dialog_BWSetup(UserVariableObj,RemoteInterfaceObj,this);
    mBwSetup->move(1,65);

    mTriggerSetup = new RtSa_Dialog_TriggerSetup(RemoteInterfaceObj,mDigitInput,this);
    mTriggerSetup->move(1,65);

    mTraceSetup = new RtSa_Dialog_TraceSetup(RemoteInterfaceObj,mDigitInput,this);
    mTraceSetup->move(1,65);

    mMarkerSetup = new RtSa_Dialog_MarkerSetup(RemoteInterfaceObj,mDigitInput,this);
    mMarkerSetup->move(1,65);

    mLimit = new RtSa_Dialog_Limit(RemoteInterfaceObj,mDigitInput,this);
    mLimit->move(1,65);

    mMeasureSetup = new RtSa_Dialog_MeasureSetup(RemoteInterfaceObj,this);
    mMeasureSetup->move(1,65);

    mAllSetup = new RtSa_Dialog_AllSetup(RemoteInterfaceObj,mDigitInput,this);
    mAllSetup->setGeometry(1,mapToGlobal(QPoint(1,-50)).y(),1278,763);
    mAllSetup->move(0,0);

    mToolSetup = new RtSa_Dialog_ToolSetup(RemoteInterfaceObj,mDigitInput,this);
    mToolSetup->move(1,65);

    mBottomMarkerSetup = new RtSa_Dialog_BottomMarkerSetup(RemoteInterfaceObj,this);
    mBottomMarkerSetup->move(1,65);

    mQuickSave = new RtSa_Dialog_QuickSave(this, RemoteInterfaceObj->GetDisplayMode());
    mQuickSave->setGeometry(135,155,1010,490);

    return;
}
