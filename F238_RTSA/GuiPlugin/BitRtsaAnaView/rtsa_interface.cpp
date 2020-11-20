#include "rtsa_interface.h"
#include "rtsa_extern.h"
#include <QFile>
#include <qthread.h>
#include "msgNoticeCode.h"
//RtSa_Interface InterfaceObj;
//Albert 1018, cacahe data array 7000 * 821
double gSpectrogramCacheData[RTSA_SPECTROGRAM_CACHE_DATA][RTSA_TRACE_DATA_NUM] =
{
    0
};
#define SPECTROGRAM_SCREEN_MAX 283

int compare(const void* a,const void* b){
  double ret = *(double*)a - *(double*)b;
  if(ret > 0){
    return 1;
  }
  else if(ret < 0){
    return -1;
  }
  return 0;
}


RtSa_Interface::RtSa_Interface(QObject *parent)
    : QObject(parent)
    , bitviewtopdisplay(BV_TOP_APMTINFO)
    , curwindowindex(1)
    , wintotalnum(0)
    , mDisplayMode(-1)
    , mWidth(0)
    , mHeight(0)
    , mIsZoomIn(false)
    , mDragFlag(false)
    , mIsPeakTrackOn(false)
    , mIsShiftKeyEnable(false)
    , mCurLimitDataPos(-1)
    , mCurFreq(0)
    , mCurAmpt(0)
    , mFmtDataTotalNum(0)
    , mFmtCurDataIndex(0)
    , mIsCurBitViewSizeChange(false)
    , isMarkerBtnPressed(false)
    , mFileType(RTSA_FILEHEADER_STATE)
{

}
RtSa_Interface::~RtSa_Interface()
{
    for(int i =0 ;i < RTSA_BITVIEWNUM; i++)
    {
        delete mBitView[i];
    }
}
/**
 * @brief Init BitView
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::InitBitView(QWidget *widget)
{
    bitviewbottomdisplay = BV_BOTTOM_STARTANDSTOP;
    bitviewtopdisplay    = BV_TOP_APMTINFO ;
    mWidth = widget->width();
    mHeight = widget->height();
    qint32 LoadFileType = 0;
    for(qint32 i = 0;i < RTSA_BITVIEWNUM;i++)
    {
        mBitView[i] = new BitView(i,curwindowindex,widget);
//        mBitView[i]->setWindowRect(mWidth,mHeight);
//        mBitView[i]->setGeometry(QRect(0,0,0,0));
        connect(mBitView[i],SIGNAL(singleClicked(quint32)),this,SLOT(setcurrentview(quint32)));
        connect(mBitView[i],SIGNAL(markerchange(qint32)),this,SLOT(markerchange(qint32)));
        connect(mBitView[i],SIGNAL(markerMove(bool)),this,SLOT(markerMove(bool)));
        connect(mBitView[i],SIGNAL(mouseDoubleClickedSig(bool)),this,SLOT(changeBitViewSize(bool)));
#ifdef BITVIEW_F239
        connect(mBitView[i],SIGNAL(scaleResize(qreal,qreal)),this,SLOT(scaleChange(qreal,qreal)));
        connect(mBitView[i],SIGNAL(suspendDraw()),this,SLOT(BitSuspendDrawSlot()));
        connect(mBitView[i],SIGNAL(ChangeCenterFreq(qreal)),this,SLOT(BitChangeCenterFreq(qreal)));
        connect(mBitView[i],SIGNAL(ChangeRefLevel(qreal)),this,SLOT(BitChangeRefLevel(qreal)));
#endif
        pTrace.initDrawBitview(i,mBitView[i]);
    }

    // load state file at first
    loadPresState();
    LoadFileType = PltLoadConditions(globalUserVariable->gfileType);
//    if(globalUserVariable->gfileType < 0)
//    {
//        LoadFileType = PltLoadConditions(STATE_LAST_FILE);
//    }
//    else
//    {
//        LoadFileType = PltLoadConditions(globalUserVariable->gfileType);
//    }
//     if no state files, state must set default.
    if(LoadFileType < 0)
    {
        pSweepControl.setSingleSweep(false);
        QThread::msleep(200);
        setDisplay(RTSA_DENSITY);
    }

    updateGeneralDataToBitview(RTSA_ACQ_INFO);
    //Tony 1102
    updateGeneralDataToBitview(RTSA_RBW_INFO);
    //Tony 1102
    updateGeneralDataToBitview(RTSA_FREQ_INFO);
    updateGeneralDataToBitview(RTSA_REF_LVL);

    //! Albert 12/17 important:
    //! must set display mode, or limit widget will not show header info.
    setSystemDisplay(BIT_DEFAULTMODE);

    // delete unnecessary '0'
    rx.setPattern("(\\.){0,1}0+$");

    ReDrawLeftInfo();
}
/**
 * @brief System Display set
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setSystemDisplay(qint32 sysDisplay)
{
    for(int i=0;i<RTSA_BITVIEWNUM;i++)
    {
        mBitView[i]->setSystemAttribute(DISPLAYMODE,sysDisplay);
        mBitView[i]->refleshdisplay();
    }
}
/**
 * @brief change bitview size
 * @note
 * @author Albert
 * @since {2018-12-24}
*/
void RtSa_Interface::changeSize(qint32 width, qint32 height)
{
    mWidth = width + 2;
    mHeight = height;
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-26
*/
//void RtSa_Interface::setThreadInterface(RtSa_ThreadGraph *threadObj)
//{
//    mthreadObj = threadObj;
//    return;
//}
/**
 * @brief set zoom out
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setZoomOut()
{
    qint32 nHeight = mHeight;
    qint32 nWidth = mWidth;
    qint32 nLeftStartPos = 0;
    nHeight -= 4;
//    nWidth -= 2;
    emit MarkerOn(false);
    for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
    {
        if(/*isMarkerOn(i) || */isMarkerBtnPressed || hasMarkerOn())
        {
            nHeight -= RTSA_BOTTOM_INFO_HEIGHT;
            nHeight += 2;
            emit MarkerOn(true);
            break;
        }
    }
    if(mDragFlag)
    {
        nLeftStartPos = RTSA_DRAG_START + 1;
    }
    else
    {
        nLeftStartPos = RTSA_LEFT_INFO_WIDTH + RTSA_DRAG_START + 1;
    }
//    nHeight -= RTSA_BOTTOM_INFO_HEIGHT;

    qint32 HALF_HEIGHT = ceil((nHeight - RTSA_TOP_INFO_HEIGHT - 3)/2);
    qint32 HALF_WIDTH = ceil((nWidth  - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH)/2);

    if(mIsCurBitViewSizeChange)
    {
        mBitView[curwindowindex]->setGeometry(QRect(nLeftStartPos,RTSA_TOP_INFO_HEIGHT + 3,nWidth - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,(nHeight - RTSA_TOP_INFO_HEIGHT)));
        mBitView[curwindowindex]->setWindowRect(nWidth,nHeight);
        if(mBitView[curwindowindex]->getBitviewType() == BIT_SPECTROGRAM)
        {
            if((nWidth - RTSA_LEFT_INFO_WIDTH - RTSA_RIGHT_INFO_WIDTH) < RTSA_NUM_SWEEP_POINT)
            {
                mBitView[curwindowindex]->SetSpectrogramSmallPixRect(nWidth - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,nHeight - RTSA_TOP_INFO_HEIGHT /*- HALF_HEIGHT*/);
            }
            else
            {
                mBitView[curwindowindex]->SetSpectrogramBigPixRect(nWidth - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,nHeight - RTSA_TOP_INFO_HEIGHT /*- HALF_HEIGHT*/);
            }
        }
        mBitView[curwindowindex]->refleshdisplay();
        mBitView[curwindowindex]->show();
        return;
    }

    if(mDisplayMode == RTSA_DENSITY_SPECTROGRAM)
    {
        mBitView[0]->setWindowRect(nWidth,nHeight);
        mBitView[1]->setWindowRect(nWidth,nHeight);
        mBitView[2]->setWindowRect(nWidth,nHeight);
        mBitView[0]->setGeometry(QRect(nLeftStartPos,RTSA_TOP_INFO_HEIGHT + 3,HALF_WIDTH,HALF_HEIGHT));
        mBitView[1]->setGeometry(QRect(nLeftStartPos + HALF_WIDTH,RTSA_TOP_INFO_HEIGHT + 3,HALF_WIDTH,HALF_HEIGHT));
        mBitView[2]->setGeometry(QRect(nLeftStartPos,RTSA_TOP_INFO_HEIGHT + 3 + HALF_HEIGHT,HALF_WIDTH,nHeight - RTSA_TOP_INFO_HEIGHT - HALF_HEIGHT));
        mBitView[3]->setGeometry(QRect(nLeftStartPos + HALF_WIDTH,RTSA_TOP_INFO_HEIGHT + 3 + HALF_HEIGHT,HALF_WIDTH,nHeight - RTSA_TOP_INFO_HEIGHT - HALF_HEIGHT));
        if((HALF_WIDTH) < RTSA_NUM_SWEEP_POINT)
        {
            mBitView[1]->SetSpectrogramSmallPixRect(HALF_WIDTH,HALF_HEIGHT);
            mBitView[1]->refleshdisplay();
        }
        else
        {
            mBitView[1]->SetSpectrogramBigPixRect(nWidth - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,nHeight - RTSA_TOP_INFO_HEIGHT - HALF_HEIGHT);
            mBitView[1]->refleshdisplay();
        }
    }
    else if(mDisplayMode == RTSA_DENSITY)
    {
        mBitView[0]->setWindowRect(nWidth,nHeight);
        mBitView[1]->setWindowRect(nWidth,nHeight);
        mBitView[0]->setGeometry(QRect(nLeftStartPos,RTSA_TOP_INFO_HEIGHT + 3,nWidth  - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,HALF_HEIGHT + 4));
        mBitView[1]->setGeometry(QRect(nLeftStartPos,RTSA_TOP_INFO_HEIGHT + 3 + HALF_HEIGHT + 4,nWidth - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,nHeight - RTSA_TOP_INFO_HEIGHT - HALF_HEIGHT - 4));
        if((nWidth - RTSA_LEFT_INFO_WIDTH - RTSA_RIGHT_INFO_WIDTH) < RTSA_NUM_SWEEP_POINT)
        {
            mBitView[0]->SetSpectrogramSmallPixRect(nWidth - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,HALF_HEIGHT + 4);
#ifdef BITVIEW_TIME_MARKER
            mBitView[1]->SetSpectrogramSmallPixRect(nWidth - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,HALF_HEIGHT + 4);
#endif
            mBitView[0]->refleshdisplay();
        }
        else
        {
            mBitView[0]->SetSpectrogramBigPixRect(nWidth - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,HALF_HEIGHT + 4);
#ifdef BITVIEW_TIME_MARKER
            mBitView[1]->SetSpectrogramBigPixRect(nWidth - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,HALF_HEIGHT + 4);
#endif
            mBitView[0]->refleshdisplay();
        }

    }
    else if(mDisplayMode == RTSA_SPECTROGRAM)
    {
        mBitView[0]->setWindowRect(nWidth,nHeight);
        mBitView[0]->setGeometry(QRect(nLeftStartPos,RTSA_TOP_INFO_HEIGHT + 3,nWidth - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,(nHeight - RTSA_TOP_INFO_HEIGHT)));
    }
    else if(mDisplayMode == RTSA_SPECTRUM_SPECTROGRAM)
    {
        mBitView[0]->setWindowRect(nWidth,nHeight);
        mBitView[1]->setWindowRect(nWidth,nHeight);
        mBitView[0]->setGeometry(QRect(nLeftStartPos,RTSA_TOP_INFO_HEIGHT + 3,nWidth  - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,HALF_HEIGHT));
        mBitView[1]->setGeometry(QRect(nLeftStartPos,RTSA_TOP_INFO_HEIGHT + 3 + HALF_HEIGHT,nWidth - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,nHeight - RTSA_TOP_INFO_HEIGHT - HALF_HEIGHT));
        if((nWidth - RTSA_LEFT_INFO_WIDTH - RTSA_RIGHT_INFO_WIDTH) < RTSA_NUM_SWEEP_POINT)
        {
#ifdef BITVIEW_TIME_MARKER
            mBitView[0]->SetSpectrogramSmallPixRect(nWidth - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,nHeight - RTSA_TOP_INFO_HEIGHT - HALF_HEIGHT);
#endif
            mBitView[1]->SetSpectrogramSmallPixRect(nWidth - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,nHeight - RTSA_TOP_INFO_HEIGHT - HALF_HEIGHT);
            mBitView[1]->refleshdisplay();
        }
        else
        {
#ifdef BITVIEW_TIME_MARKER
            mBitView[0]->SetSpectrogramBigPixRect(nWidth - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,nHeight - RTSA_TOP_INFO_HEIGHT - HALF_HEIGHT);
#endif
            mBitView[1]->SetSpectrogramBigPixRect(nWidth - nLeftStartPos - RTSA_RIGHT_INFO_WIDTH,nHeight - RTSA_TOP_INFO_HEIGHT - HALF_HEIGHT);
            mBitView[1]->refleshdisplay();
        }
    }
}
/**
 * @brief set zoom in
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setZoomIn()
{
    qint32 nHeight = mHeight;
    qint32 nWidth = mWidth;
    nWidth += 1;
    nHeight -= 4;
    for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
    {
        if(/*isMarkerOn(i) || */isMarkerBtnPressed || hasMarkerOn())
        {
            nHeight -= RTSA_BOTTOM_INFO_HEIGHT;
            nHeight += 2;
            break;
        }
    }
    qint32 HALF_HEIGHT = ceil((nHeight /*- 3*/)/2);
    qint32 HALF_WIDTH = ceil((nWidth - RTSA_RIGHT_INFO_WIDTH /*- 3*/)/2);

    if(mIsCurBitViewSizeChange)
    {
        mBitView[curwindowindex]->setGeometry(QRect(RTSA_PSTART_X,RTSA_PSTART_Y_BIG,nWidth - RTSA_RIGHT_INFO_WIDTH,(nHeight)));
        mBitView[curwindowindex]->setWindowRect(nWidth,nHeight);
        if((nWidth - RTSA_RIGHT_INFO_WIDTH) < RTSA_NUM_SWEEP_POINT)
        {
            mBitView[curwindowindex]->SetSpectrogramSmallPixRect(nWidth - RTSA_RIGHT_INFO_WIDTH,nHeight /*- HALF_HEIGHT*/);
            mBitView[curwindowindex]->refleshdisplay();
        }
        else
        {
            mBitView[curwindowindex]->SetSpectrogramBigPixRect(nWidth - RTSA_RIGHT_INFO_WIDTH,nHeight /*- HALF_HEIGHT*/);
            mBitView[curwindowindex]->refleshdisplay();
        }
        mBitView[curwindowindex]->refleshdisplay();
        mBitView[curwindowindex]->show();
        return;
    }


    if(mDisplayMode == RTSA_DENSITY_SPECTROGRAM)
    {
        mBitView[0]->setGeometry(QRect(RTSA_PSTART_X,RTSA_PSTART_Y_BIG,HALF_WIDTH,HALF_HEIGHT));
        mBitView[1]->setGeometry(QRect(RTSA_PSTART_X + HALF_WIDTH,RTSA_PSTART_Y_BIG,HALF_WIDTH,HALF_HEIGHT));
        mBitView[2]->setGeometry(QRect(RTSA_PSTART_X,RTSA_PSTART_Y_BIG  + HALF_HEIGHT,HALF_WIDTH,nHeight - HALF_HEIGHT));
        mBitView[3]->setGeometry(QRect(RTSA_PSTART_X + HALF_WIDTH,RTSA_PSTART_Y_BIG + HALF_HEIGHT,HALF_WIDTH,nHeight - HALF_HEIGHT));
        if((HALF_HEIGHT) < RTSA_NUM_SWEEP_POINT)
        {
            mBitView[1]->SetSpectrogramSmallPixRect(HALF_WIDTH,HALF_HEIGHT);
            mBitView[1]->refleshdisplay();
        }
        else
        {
            mBitView[1]->SetSpectrogramBigPixRect(HALF_WIDTH,HALF_HEIGHT);
            mBitView[1]->refleshdisplay();
        }
    }
    else if(mDisplayMode == RTSA_DENSITY)
    {
        mBitView[0]->setWindowRect(nWidth,nHeight);
        mBitView[1]->setWindowRect(nWidth,nHeight);
        mBitView[0]->setGeometry(QRect(RTSA_PSTART_X,RTSA_PSTART_Y_BIG,nWidth - RTSA_RIGHT_INFO_WIDTH,HALF_HEIGHT + 1));
        mBitView[1]->setGeometry(QRect(RTSA_PSTART_X,RTSA_PSTART_Y_BIG + HALF_HEIGHT + 1,nWidth - RTSA_RIGHT_INFO_WIDTH,nHeight - HALF_HEIGHT - 1));
        if((nWidth - RTSA_RIGHT_INFO_WIDTH) < RTSA_NUM_SWEEP_POINT)
        {
            mBitView[0]->SetSpectrogramSmallPixRect(nWidth - RTSA_RIGHT_INFO_WIDTH,HALF_HEIGHT + 1);
            mBitView[0]->refleshdisplay();
        }
        else
        {
            mBitView[0]->SetSpectrogramBigPixRect(nWidth - RTSA_RIGHT_INFO_WIDTH,HALF_HEIGHT + 1);
            mBitView[0]->refleshdisplay();
        }
     }
    else if(mDisplayMode == RTSA_SPECTROGRAM)
    {
        mBitView[0]->setWindowRect(nWidth,nHeight);
        mBitView[0]->setGeometry(QRect(RTSA_PSTART_X,RTSA_PSTART_Y_BIG,nWidth - RTSA_RIGHT_INFO_WIDTH,(nHeight)));
    }
    else if(mDisplayMode == RTSA_SPECTRUM_SPECTROGRAM)
    {
        mBitView[0]->setWindowRect(nWidth,nHeight);
        mBitView[1]->setWindowRect(nWidth,nHeight);
        mBitView[0]->setGeometry(QRect(RTSA_PSTART_X,RTSA_PSTART_Y_BIG,nWidth - RTSA_RIGHT_INFO_WIDTH,HALF_HEIGHT));
        mBitView[1]->setGeometry(QRect(RTSA_PSTART_X,RTSA_PSTART_Y_BIG + HALF_HEIGHT,nWidth - RTSA_RIGHT_INFO_WIDTH,nHeight - HALF_HEIGHT));
        if((nWidth - RTSA_RIGHT_INFO_WIDTH) < RTSA_NUM_SWEEP_POINT)
        {
            mBitView[1]->SetSpectrogramSmallPixRect(nWidth - RTSA_RIGHT_INFO_WIDTH,nHeight - HALF_HEIGHT);
            mBitView[1]->refleshdisplay();
        }
        else
        {
            mBitView[1]->SetSpectrogramBigPixRect(nWidth - RTSA_RIGHT_INFO_WIDTH,nHeight - HALF_HEIGHT);
            mBitView[1]->refleshdisplay();
        }
    }
}
/**
 * @brief draw lines and spectrogram
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::Draw()
{
    if(globalUserVariable->gAutoAttenTrack == RTSA_ON)
    {
        if(AutoAttenTrack())
            return;
    }
    pTrace.draw();
    if(mIsPeakTrackOn)
    {
        setMarkerToPeak();
    }
    for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
    {
        if(isMarkerOn(i))
        {
            emit BitViewMakerDraw(i,true);
        }
    }
    if(IsAvgOn(getCurTrace()))
    {
        emit RedrawInfoShow(LABEL_AVERAGE);
    }
    return;
}
/**
 * @brief atten auto track
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool RtSa_Interface::AutoAttenTrack()
{
    qreal AMax = pMarker.setMarkerToPeak();
    if(fabs(AMax - globalUserVariable->gRefLevel) - 10. >0.)
    {
        globalUserVariable->gRefLevel = AMax + 10.;
        setRefLevel(globalUserVariable->gRefLevel);
        resetAvgCnt();
        return true;
    }
    return false;
}
/**
 * @brief Gobal Variable initial set
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setGobalVariable(RtSa_User_Variable *globalVariable)
{
    globalUserVariable = globalVariable;
    pSweepControl.setGobalVariable(globalVariable);
    return;
}
/**
* @brief ReDrawLeftInfo
* @param none
* @Author Albert
* @date 2019-03-27
*/
void RtSa_Interface::ReDrawLeftInfo()
{
    for(qint32 i = LABEL_MODE; i < LABEL_END; i++)
    {
        emit RedrawInfoShow(i);
    }
    return;
}
/**
 * @brief set center freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setCenterFreq(qreal freq)
{
    bitviewbottomdisplay = BV_BOTTOM_CENTERANDSPAN;
    freq = freq - globalUserVariable->gfreqOffset;
//    if(globalUserVariable->gfreqOffset >= 0)
//    {
//        freq = freq - globalUserVariable->gfreqOffset;
//    }
//    else
//    {
//        freq = freq + globalUserVariable->gfreqOffset;
//    }
    pSweepControl.setCenterFreq(freq);
    resetAvgCnt();
    updateGeneralDataToBitview(RTSA_FREQ_INFO);
    updateGeneralDataToBitview(RTSA_RBW_INFO);
    updateGeneralDataToBitview(RTSA_ACQ_INFO);
    showBitViewBottomMsg(bitviewbottomdisplay);
    emit RedrawInfoShow(LABEL_CENTER_FREQ);
    globalUserVariable->gChannelStep = mRTSA_ChStand[globalUserVariable->gTecIndex].ChStep;
    globalUserVariable->gChannelNum = globalUserVariable->CalculateChannelNum();
//    globalUserVariable->adjustCHStandarByCerFreq(globalUserVariable->gCenterFreq);
    return;
}
/**
 * @brief get center freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal RtSa_Interface::getCenterFreq()
{
    return pSweepControl.getCenterFreq() + globalUserVariable->gfreqOffset;
//    if(globalUserVariable->gfreqOffset >= 0)
//    {
//        return pSweepControl.getCenterFreq() + globalUserVariable->gfreqOffset;
//    }
//    else
//    {
//        return pSweepControl.getCenterFreq() - globalUserVariable->gfreqOffset;
//    }
}
/**
 * @brief set start freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setStartFreq(qreal freq)
{
    bitviewbottomdisplay = BV_BOTTOM_STARTANDSTOP;
    freq = freq - globalUserVariable->gfreqOffset;

    pSweepControl.setStartFreq(freq);
    resetAvgCnt();
    updateGeneralDataToBitview(RTSA_ACQ_INFO);
    updateGeneralDataToBitview(RTSA_FREQ_INFO);
    updateGeneralDataToBitview(RTSA_RBW_INFO);
    showBitViewBottomMsg(bitviewbottomdisplay);
    return;
}
/**
 * @brief get start freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal RtSa_Interface::getStartFreq()
{
    return pSweepControl.getStartFreq() + globalUserVariable->gfreqOffset;
}
/**
 * @brief set stop freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setStopFreq(qreal freq)
{
    bitviewbottomdisplay = BV_BOTTOM_STARTANDSTOP;
    freq = freq - globalUserVariable->gfreqOffset;
    pSweepControl.setStopFreq(freq);
    resetAvgCnt();
    updateGeneralDataToBitview(RTSA_ACQ_INFO);
    updateGeneralDataToBitview(RTSA_FREQ_INFO);
    updateGeneralDataToBitview(RTSA_RBW_INFO);
    showBitViewBottomMsg(bitviewbottomdisplay);
    return;
}
/**
 * @brief get stop freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal RtSa_Interface::getStopFreq()
{
    return pSweepControl.getStopFreq() + globalUserVariable->gfreqOffset;
}
/**
 * @brief get freq string
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
QString RtSa_Interface::getFreqStr(qint32 freqID)
{
    qreal freq = 0;
    switch(freqID)
    {
    case RTSA_CENTER_FREQ:
        freq = pSweepControl.getCenterFreq();
        break;
    case RTSA_START_FREQ:
        freq = pSweepControl.getStartFreq();
        break;
    case RTSA_STOP_FREQ:
        freq = pSweepControl.getStopFreq();
        break;
    case RTSA_SPAN_FREQ:
        freq = pSweepControl.getSpan();
        break;
    case RTSA_STEP_FREQ:
        freq = pSweepControl.getCFStep();
        break;
    default:
        break;
    }
    return getFreqAdjustStr(freq);
}
/**
 * @brief get freq adjust string
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
QString RtSa_Interface::getFreqAdjustStr(qreal freq, qint32 DecPrecision)
{
    QString strCenterFreq;
    qreal freqVal = 0;
    if(freq < 0)
    {
        freqVal = freq * -1;
    }
    else
    {
        freqVal = freq;
    }
    if(freqVal >= RTSA_GHZ)
    {
        strCenterFreq = QString::number((qreal) freqVal / RTSA_GHZ,'f',DecPrecision);
        strCenterFreq.replace(rx,"");
        strCenterFreq += QString(" GHz");
    }
    else if(freqVal >= RTSA_MHZ)
    {
        strCenterFreq = QString::number((qreal) freqVal / RTSA_MHZ,'f',DecPrecision);
        strCenterFreq.replace(rx,"");
        strCenterFreq += QString(" MHz");
    }
    else if(freqVal >= RTSA_KHZ)
    {
        strCenterFreq = QString::number((qreal) freqVal / RTSA_KHZ,'f',DecPrecision);
        strCenterFreq.replace(rx,"");
        strCenterFreq += QString(" kHz");
    }
    else if(freqVal >= 0)
    {
        strCenterFreq = QString::number((qreal) freqVal / RTSA_HZ,'f',DecPrecision);
        strCenterFreq.replace(rx,"");
        strCenterFreq += QString(" Hz");
    }
    if(freq < 0)
    {
        strCenterFreq = QString("-") + strCenterFreq;
    }
    return strCenterFreq;
}
/**
 * @brief  frequency unit.
 * @param  frequency
 * @author Tony
 */
qint32 RtSa_Interface::freqUnitFindProc(qreal freq)
{
    if (freq >= RTSA_GHZ)
        return UNIT_GHZ;
    else if (freq >= RTSA_MHZ)
        return UNIT_MHZ;
    else if (freq >= RTSA_KHZ)
        return UNIT_KHZ;
    else
        return UNIT_HZ;
}
/**
 * @brief  frequency unit.
 * @param  frequency
 * @author Tony
 */
qint32 RtSa_Interface::timeUnitFindProc(qreal time)
{
    if (time >= RTSA_S)
        return UNIT_S;
    else if (time >= RTSA_MS)
        return UNIT_MS;
    else if (time >= RTSA_US)
        return UNIT_US;
    else
        return UNIT_NS;
}
/**
 * @brief RtSa_Interface::setFreqOffset
 * @param freq
 */
void RtSa_Interface::setFreqOffset(qreal freq)
{
    if(freq > RTSA_SPEC_FREQ_MAX)
        freq = RTSA_SPEC_FREQ_MAX;
    else if(freq < -RTSA_SPEC_FREQ_MAX)
        freq = -RTSA_SPEC_FREQ_MAX;
    globalUserVariable->gfreqOffset = freq;
    updateGeneralDataToBitview(RTSA_FREQ_OFFSET);
    return;
}
/**
 * @brief RtSa_Interface::getFreqOffset
 * @return
 */
qreal RtSa_Interface::getFreqOffset()
{
    return globalUserVariable->gfreqOffset;
}
/**
 * @brief set span freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setSpan(qreal freq)
{
    bitviewbottomdisplay = BV_BOTTOM_CENTERANDSPAN;
    if(freq < RTSA_SPAN_MIN)
        freq = RTSA_SPAN_MIN;
    pSweepControl.setSpan(freq);
    resetAvgCnt();
    updateGeneralDataToBitview(RTSA_ACQ_INFO);
    updateGeneralDataToBitview(RTSA_FREQ_INFO);
    updateGeneralDataToBitview(RTSA_RBW_INFO);
    showBitViewBottomMsg(bitviewbottomdisplay);
    emit RedrawInfoShow(LABEL_POI);
    emit RedrawInfoShow(LABEL_RBW_STATUS);
    emit RedrawInfoShow(LABEL_RBW);
    emit RedrawInfoShow(LABEL_ACQTIME);
    return;
}
/**
 * @brief get span freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal RtSa_Interface::getSpan()
{
    return pSweepControl.getSpan();
}
/**
 * @brief set full span
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setFullSpan()
{
    bitviewbottomdisplay = BV_BOTTOM_CENTERANDSPAN;

    pSweepControl.setFullSpan();
    resetAvgCnt();
    updateGeneralDataToBitview(RTSA_ACQ_INFO);
    updateGeneralDataToBitview(RTSA_FREQ_INFO);
    updateGeneralDataToBitview(RTSA_RBW_INFO);
    showBitViewBottomMsg(bitviewbottomdisplay);
    emit RedrawInfoShow(LABEL_POI);
    emit RedrawInfoShow(LABEL_RBW_STATUS);
    emit RedrawInfoShow(LABEL_RBW);
    emit RedrawInfoShow(LABEL_ACQTIME);
    return;
}
/**
 * @brief set step freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setCFStep(qreal freq)
{
    pSweepControl.setCFStep(freq);
    return;
}
/**
 * @brief get step freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal RtSa_Interface::getCFStep()
{
    return pSweepControl.getCFStep();
}
/**
 * @brief set ref level
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setRefLevel(qreal refLevel)
{
    bitviewtopdisplay = BV_TOP_APMTINFO;

    pSweepControl.setRefLevel(refLevel);
//    pSweepControl.setDpxAmptMin();
//    pSweepControl.setDpxAmptZoom();
    resetAvgCnt();
    updateGeneralDataToBitview(RTSA_REF_LVL);
    for(int i=0;i<RTSA_BITVIEWNUM;i++)
    {
        mBitView[i]->showTopWordsMsg(BV_TOP_APMTINFO);
        mBitView[i]->refleshdisplay();
    }
}
/**
 * @brief get ref level
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal RtSa_Interface::getRefLevel()
{
    return pSweepControl.getRefLevel();
}
/**
 * @brief RtSa_Interface::ChangedBmToOherUnit
 * @param refLevel
 * @return
 */
qreal RtSa_Interface::ChangedBmToOherUnit()
{
    qreal reflevel = getRefLevel() /*+ globalUserVariable->gRefOffset*/;
    qreal tempVal = 0.;
    qreal value = 0;
    qint32 unit = getAmptUint();
    switch (unit) {
    case RTSA_WATTS: //
        value = qPow(10, reflevel / 10.) / 1000;
        break;
    case RTSA_VOLT:  //
        tempVal = qPow(10, reflevel / 10.);
        value = qPow(50 * tempVal * 0.001, 0.5);//uv
        break;
    case RTSA_DBV:
        value = reflevel + RTSA_dBVFix;
        break;
    case RTSA_DBMV:
        value = reflevel + RTSA_dBmVFix;
        break;
    case RTSA_DBUV:
        value = reflevel + RTSA_dBuVFix;
         break;
    default:
        value = reflevel;
    }
    return value;
}
/**
 * @brief RtSa_Interface::getRefLevelStr
 * @param reflevel
 * @return
 */
QString RtSa_Interface::getRefLevelStr(qreal reflevel)
{
    QString refStr = QString("");
    qint32 unit = getAmptUint();
    switch(unit)
    {
    case RTSA_DBM:
        if(reflevel >= 0)
        {
            reflevel = (qreal)(qint64)((reflevel + 0.005) * 100) / 100;
        }
        else
        {
            reflevel = (qreal)(qint64)((reflevel - 0.005) * 100) / 100;
        }
        refStr = QString::number(reflevel,'f',2);
        refStr += QString(" dBm");
        break;
    case RTSA_DBV:
        if(reflevel >= 0)
        {
            reflevel = (qreal)(qint64)((reflevel + 0.005) * 100) / 100;
        }
        else
        {
            reflevel = (qreal)(qint64)((reflevel - 0.005) * 100) / 100;
        }
        refStr = QString::number(reflevel,'f',2);
        refStr += QString(" dBV");
        break;
    case RTSA_DBMV:
        if(reflevel >= 0)
        {
            reflevel = (qreal)(qint64)((reflevel + 0.005) * 100) / 100;
        }
        else
        {
            reflevel = (qreal)(qint64)((reflevel - 0.005) * 100) / 100;
        }
        refStr = QString::number(reflevel,'f',2);
        refStr += QString(" dBmV");
        break;
    case RTSA_DBUV:
        if(reflevel >= 0)
        {
            reflevel = (qreal)(qint64)((reflevel + 0.005) * 100) / 100;
        }
        else
        {
            reflevel = (qreal)(qint64)((reflevel - 0.005) * 100) / 100;
        }
        refStr = QString::number(reflevel,'f',2);
        refStr += QString(" dBuV");
        break;
    case RTSA_VOLT:
        refStr = getRefLevelVoltStr(reflevel);
        break;
    case RTSA_WATTS:
        refStr = getRefLevelWattStr(reflevel);
        break;
    default:
        break;
    }    return refStr;
}
/**
 * @brief get ref level string
 * @note
 * @author Albert
 * @since {2018-12-27}
*/
QString RtSa_Interface::getRefLevelAdjustStr()
{
    qreal reflevel = ChangedBmToOherUnit();

//    qint32 unit = getAmptUint();
    QString refStr = QString("");
    refStr = getRefLevelStr(reflevel);
    return refStr;
}
/**
 * @brief get ref level string
 * @note
 * @author Albert
 * @since {2018-12-27}
*/
QString RtSa_Interface::getRefLevelVoltStr(qreal reflevel)
{
    QString voltStr;
    QString UnitStr;
    qreal UNION_SIZE = 1.0;
    if(reflevel > UNION_SIZE)
    {
        UnitStr = QString(" V");
    }
    else if(reflevel >= (UNION_SIZE / 1000.0))
    {
        reflevel *= 1000.0;
        UnitStr = QString(" mV");
    }
    else if(reflevel >= (UNION_SIZE / 1000000.0))
    {
        reflevel *= 1000000.0;
        UnitStr = QString(" uV");
    }
    else if(reflevel >= (UNION_SIZE / 1000000000.0))
    {
        reflevel *= 1000000000.0;
        UnitStr = QString(" nV");
    }
    else if(reflevel >= (UNION_SIZE / 1000000000000.0))
    {
        reflevel *= 1000000000000.0;
        UnitStr = QString(" pV");
    }
    else if(reflevel >= (UNION_SIZE / 1000000000000000.0))
    {
        reflevel *= 1000000000000000.0;
        UnitStr = QString(" fV");
    }
    else if(reflevel >= (UNION_SIZE / 1000000000000000000.0))
    {
        reflevel *= 1000000000000000000.0;
        UnitStr = QString(" aV");
    }
    else if(reflevel >= (UNION_SIZE / 1000000000000000000000.0))
    {
        reflevel *= 1000000000000000000.0;
        UnitStr = QString(" zV");
    }
    else
    {
        reflevel *= 1000000000000000000000000.0;
        UnitStr = QString(" yV");
    }
    // Only 2 decimal places reserved
    reflevel = (qreal)(qint32)((reflevel + 0.005) * 100) /100;
    voltStr = QString::number(reflevel,'f',2);
//    voltStr.replace(rx,"");
    voltStr += UnitStr;
    return voltStr;
}
/**
 * @brief get ref level string
 * @note
 * @author Albert
 * @since {2018-12-27}
*/
QString RtSa_Interface::getRefLevelWattStr(qreal reflevel)
{
    QString wattStr;
    QString UnitStr;
    qreal UNION_SIZE = 1.0;
    if(reflevel >= UNION_SIZE)
    {
        UnitStr = QString(" W");
    }
    else if(reflevel >= (UNION_SIZE / 1000.0))
    {
        reflevel *= 1000.0;
        UnitStr = QString(" mW");
    }
    else if(reflevel >= (UNION_SIZE / 1000000.0))
    {
        reflevel *= 1000000.0;
        UnitStr = QString(" uW");
    }
    else if(reflevel >= (UNION_SIZE / 1000000000.0))
    {
        reflevel *= 1000000000.0;
        UnitStr = QString(" nW");
    }
    else if(reflevel >= (UNION_SIZE / 1000000000000.0))
    {
        reflevel *= 1000000000000.0;
        UnitStr = QString(" pW");
    }
    else if(reflevel >= (UNION_SIZE / 1000000000000000.0))
    {
        reflevel *= 1000000000000000.0;
        UnitStr = QString(" fW");
    }
    else /*if(reflevel >= (UNION_SIZE / 1000000000000000000.0))*/
    {
        reflevel *= 1000000000000000000.0;
        UnitStr = QString(" aW");
    }
//    else if(reflevel >= (UNION_SIZE / 1000000000000000000000.0))
//    {
//        reflevel *= 1000000000000000000000.0;
//        UnitStr = QString(" zW");
//    }
//    else
//    {
//        reflevel *= 1000000000000000000000000.0;
//        UnitStr = QString(" yW");
//    }
    // Only 2 decimal places reserved
    reflevel = (qreal)(qint32)((reflevel + 0.005) * 100) /100;
    wattStr = QString::number(reflevel,'f',2);
//    wattStr.replace(rx,"");
    wattStr += UnitStr;
    return wattStr;
}
/**
 * @brief set units
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setAmptUnit(qint32 unitIndex)
{
    if(unitIndex < RTSA_DBM)
        unitIndex = RTSA_DBM;
    else if(unitIndex > RTSA_WATTS)
        unitIndex = RTSA_WATTS;

    globalUserVariable->gAmptdUnit = unitIndex;
//    pSweepControl.setAmptUnit(unitIndex);
    mBitView[curwindowindex]->setAmptdUnit(globalUserVariable->gAmptdUnit);
    mBitView[curwindowindex]->showTopWordsMsg(BV_TOP_APMTINFO);
    mBitView[curwindowindex]->refleshdisplay();
    return;
}
/**
 * @brief get units
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 RtSa_Interface::getAmptUint()
{
    return mBitView[curwindowindex]->getAmptUnit();// pSweepControl.getAmptUint();
}
/**
 * @brief set atten auto on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setAttenAuto(bool isAttenAuto)
{
    if(globalUserVariable->gAtten == isAttenAuto)
        return;
    pSweepControl.setAttenAuto(isAttenAuto);
    resetAvgCnt();
    emit RedrawInfoShow(LABEL_ATTEN_STATUS);
    return;
}
/**
 * @brief get atten auto on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool RtSa_Interface::IsAttenAuto()
{
    return pSweepControl.IsAttenAuto();
}
/**
 * @brief set atten val
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setAttenVal(qreal attenVal)
{
    pSweepControl.setAttenVal(attenVal);
    resetAvgCnt();
    emit RedrawInfoShow(LABEL_ATTEN_VAL);
    return;
}
/**
 * @brief get atten val
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal RtSa_Interface::getAttenVal()
{
    return pSweepControl.getAttenVal();
}
/**
 * @brief set scale val
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setScaleDiv(qreal scaleDiv)
{
    // Only 2 decimal places reserved
    scaleDiv = (qreal)(qint64)((scaleDiv + 0.005) * 100) / 100;
    if(0.2 > scaleDiv)
    {
        scaleDiv = 0.2;
    }
    else if(20. < scaleDiv)
    {
        scaleDiv = 20.;
    }
    globalUserVariable->gScaleDiv = scaleDiv;

//    if(getCurBitviewType() == BIT_DENSITY)
    pSweepControl.setDpxAmptMin();
    pSweepControl.setDpxAmptZoom();
//    if(mDisplayMode == RTSA_DENSITY)
//    {
//        pSweepControl.setDpxAmptMin();
//        pSweepControl.setDpxAmptZoom();
////        mBitView[curwindowindex]->setAmptdAttribute(BIT_AMPTD_DIV,scaleDiv);
////        mBitView[curwindowindex]->showTopWordsMsg(BV_TOP_APMTINFO);
////        mBitView[curwindowindex]->refleshdisplay();

//    }

    for(int i=0;i<RTSA_BITVIEWNUM;i++)
    {

        mBitView[i]->setAmptdAttribute(BIT_AMPTD_DIV,scaleDiv);
        mBitView[i]->showTopWordsMsg(BV_TOP_APMTINFO);
        mBitView[i]->refleshdisplay();
    }
//    pSweepControl.setDpxAmptMin();
//    pSweepControl.setDpxAmptZoom();

//    mBitView[curwindowindex]->setAmptdAttribute(BIT_AMPTD_DIV,scaleDiv);
//    mBitView[curwindowindex]->showTopWordsMsg(BV_TOP_APMTINFO);
//    mBitView[curwindowindex]->refleshdisplay();
    return;
}
/**
 * @brief get scale val
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal RtSa_Interface::getScaleDiv()
{
    qreal scale = 0;
    scale = mBitView[curwindowindex]->getAmptdAttribute(BIT_AMPTD_DIV);
    return scale;
}
/**
 * @brief set ref offset
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setRefOffset(qreal refOffset)
{
    // Only 2 decimal places reserved
    if(refOffset < 0)
    {
        refOffset = (qreal)(qint64)((refOffset - 0.005) * 100) / 100;
    }
    else
    {
        refOffset = (qreal)(qint64)((refOffset + 0.005) * 100) / 100;
    }
    if(refOffset >= RTSA_SPEC_REF_OFFSET_MAX)
    {
        refOffset = RTSA_SPEC_REF_OFFSET_MAX;
    }
    else if(refOffset <= RTSA_SPEC_REF_OFFSET_MIN)
    {
        refOffset = RTSA_SPEC_REF_OFFSET_MIN;
    }
    globalUserVariable->gRefOffset = refOffset;

//    if(getCurBitviewType() == BIT_DENSITY)
//    {
//        pSweepControl.setDpxAmptMin();
//        pSweepControl.setDpxAmptZoom();
//    }
//    pSweepControl.setDpxAmptMin();
//    pSweepControl.setDpxAmptZoom();

    updateGeneralDataToBitview(RTSA_REF_OFFSET);
    return;
}
/**
 * @brief get ref offset
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal RtSa_Interface::getRefOffset()
{
    qreal refOffset = 0;
    refOffset = mBitView[curwindowindex]->getAmptdAttribute(BIT_AMPTD_OFFSET);
    return refOffset;
}
/**
 * @brief set pre-amp on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setPreAmpOn(bool IsOn)
{
    if(globalUserVariable->gPreamp == IsOn)
        return;
    pSweepControl.setPreAmpOn(IsOn);
    resetAvgCnt();
    emit RedrawInfoShow(LABEL_PREAMP);
    return;
}
/**
 * @brief get pre-amp on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool RtSa_Interface::IsPreAmpOn()
{
    return pSweepControl.IsPreAmpOn();
}
/**
 * @brief set auto scale
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setAutoScale()
{
    qreal AMax = pTrace.searchMaxAmplitude();
    qreal AMin = pTrace.searchMinAmplitude();
    globalUserVariable->gScaleDiv = (AMax - AMin)/8;
    if(globalUserVariable->gScaleDiv < 0.2)
    {
        globalUserVariable->gScaleDiv = 0.2;
        globalUserVariable->gRefLevel = AMax + 2 * globalUserVariable->gScaleDiv;
    }
    else
    {
        globalUserVariable->gRefLevel = AMax + globalUserVariable->gScaleDiv;
    }
    setRefLevel(globalUserVariable->gRefLevel);
    resetAvgCnt();
    setScaleDiv(globalUserVariable->gScaleDiv);
    return;
}

//BW
qreal RtSa_Interface::getBW()
{
    return globalUserVariable->gRbw;
}
/**
 * @brief set BW auto on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setBWAuto(bool isAuto)
{
//    if(globalUserVariable->gAutoRbw == isAuto)
//        return;
    globalUserVariable->gAutoRbw = isAuto;
    if(globalUserVariable->gAutoRbw == RTSA_ON)
    {
//        globalUserVariable->gRbw = RTSA_RbwManualList[globalUserVariable->gFTTWindows][globalUserVariable->gRbwGrade][1];
//        globalUserVariable->gRbwIndex = RTSA_RBW5;
        if(globalUserVariable->gFTTWindows == RTSA_RECTANGULAR)
        {
            globalUserVariable->gRbw = RTSA_RbwManualList[globalUserVariable->gFTTWindows][globalUserVariable->gRbwGrade][6];
            globalUserVariable->gRbwIndex = RTSA_RBW6;
        }
        else
        {
            globalUserVariable->gRbw = RTSA_RbwManualList[globalUserVariable->gFTTWindows][globalUserVariable->gRbwGrade][5];
            globalUserVariable->gRbwIndex = RTSA_RBW5;
        }
//        bwSweepSettingDisplayFunc();
    }
    else if(globalUserVariable->gAutoRbw == RTSA_OFF) // Tony 0907
    {
        if(globalUserVariable->gFTTWindows == RTSA_RECTANGULAR)
        {
            globalUserVariable->gRbw = RTSA_RbwManualList[globalUserVariable->gFTTWindows][globalUserVariable->gRbwGrade][0];
            globalUserVariable->gRbwIndex = RTSA_RBW6;
        }
        else
        {
            globalUserVariable->gRbw = RTSA_RbwManualList[globalUserVariable->gFTTWindows][globalUserVariable->gRbwGrade][globalUserVariable->gRbwIndex];
        }
//        bwSweepSettingDisplayFunc();
    }
    pSweepControl.setBWAuto(isAuto);
    resetAvgCnt();
    //Tony 1102
    updateGeneralDataToBitview(RTSA_RBW_INFO);
    emit RedrawInfoShow(LABEL_RBW_STATUS);
    emit RedrawInfoShow(LABEL_RBW);
    return;
}
/**
 * @brief get BW auto on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool RtSa_Interface::IsBWAuto()
{
    return globalUserVariable->gAutoRbw;
}
/**
 * @brief set BW index
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setBWIndex(qint32 bwIndex)
{
    qreal rbw = 0;
    if(globalUserVariable->gFTTWindows == RTSA_RECTANGULAR)
    {
        return;
    }
    if(globalUserVariable->gRbwIndex == bwIndex)
        return;
    if(bwIndex < RTSA_RBW0)
        bwIndex = RTSA_RBW0;
    else if(bwIndex > RTSA_RBW6)
        bwIndex = RTSA_RBW6;
    globalUserVariable->gAutoRbw = RTSA_MANUAL;//Tony 1024
    globalUserVariable->gRbwIndex = bwIndex;
    globalUserVariable->gRbw = RTSA_RbwManualList[globalUserVariable->gFTTWindows][globalUserVariable->gRbwGrade][globalUserVariable->gRbwIndex];
//    bwSweepSettingDisplayFunc();
    rbw = globalUserVariable->gRbw;
    pSweepControl.setBW(rbw);
    resetAvgCnt();
    //Tony 1102
    updateGeneralDataToBitview(RTSA_RBW_INFO);
    emit RedrawInfoShow(LABEL_RBW);
    emit RedrawInfoShow(LABEL_RBW_STATUS);
    emit RedrawInfoShow(LABEL_POI);
    return;
}
/**
 * @brief get BW index
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 RtSa_Interface::getBWIndex()
{
    return globalUserVariable->gRbwIndex;
}
/**
 * @brief set BW FFT window
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setFFTWindow(qint32 fftWindow)
{
//    if(globalUserVariable->gFTTWindows == fftWindow)
//        return;
    if(fftWindow < RTSA_RECTANGULAR)
        fftWindow = RTSA_RECTANGULAR;
    else if(fftWindow > RTSA_FLATTOP)
        fftWindow = RTSA_FLATTOP;
    globalUserVariable->gFTTWindows = fftWindow;

    if(fftWindow == RTSA_RECTANGULAR)
    {
        globalUserVariable->gFTTWindows = RTSA_RECTANGULAR;
        globalUserVariable->gRbwIndex = RTSA_RBW6;
        globalUserVariable->gRbw = RTSA_RbwManualList[fftWindow][globalUserVariable->gRbwGrade][globalUserVariable->gRbwIndex];
//        updateGeneralDataToBitview(RTSA_RBW_INFO);
    }
    else
    {
        if(globalUserVariable->gAutoRbw == RTSA_AUTO)
        {
            globalUserVariable->gRbwIndex = RTSA_RBW5;
            globalUserVariable->gRbw = RTSA_RbwManualList[fftWindow][globalUserVariable->gRbwGrade][5];
        }
         else
             globalUserVariable->gRbw = RTSA_RbwManualList[fftWindow][globalUserVariable->gRbwGrade][globalUserVariable->gRbwIndex];

    }
     updateGeneralDataToBitview(RTSA_RBW_INFO);

    pSweepControl.setBWFFTWindow(fftWindow);
    resetAvgCnt();
    emit RedrawInfoShow(LABEL_FFTWINDOW);
    emit RedrawInfoShow(LABEL_RBW);
    return;
}
/**
 * @brief get BW FFT window
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 RtSa_Interface::getFFTWindow()
{
    return globalUserVariable->gFTTWindows;
}
QString RtSa_Interface::getFFTWindowStr()
{
    QString str = QString("");
    switch (globalUserVariable->gFTTWindows) {
    case RTSA_HANNING:
        str = QString("Hanning");
        break;
    case RTSA_FLATTOP:
        str = QString("Flattop");
        break;
    case RTSA_GAUSIAN:
        str = QString("Gausian");
        break;
    case RTSA_RECTANGULAR:
        str = QString("Rectangular");
        break;
    case RTSA_KAISER:
        str = QString("Kaiser");
        break;
    case RTSA_BLACKMANHARRIS:
        str = QString("Black-Harris");
        break;
    default:
        break;
    }
    return str;
}
/**
* @brief getCurIndexBW
* @param get bw
* @Author Albert
* @date 2019-04-18
*/
qreal RtSa_Interface::getCurIndexBW(qint32 index)
{
    qreal bw;
    if(index < RTSA_RBW0)
        index = RTSA_RBW0;
    else if(index > RTSA_RBW6)
        index  = RTSA_RBW6;
    bw = RTSA_RbwManualList[globalUserVariable->gFTTWindows][globalUserVariable->gRbwGrade][index];
    return bw;
}
//Display
/**
 * @brief set measure type
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setDisplay(qint32 disPlayMode)
{
//    if(mDisplayMode == disPlayMode)
//        return;
    qint32 nWidth = mWidth;
    qint32 nHeight = mHeight;

//    mWidth = mOrginWidth;
//    mHeight = mOrginHeight;
    if(disPlayMode < RTSA_SPECTRUM_SPECTROGRAM)
        disPlayMode = RTSA_SPECTRUM_SPECTROGRAM;
    else if(disPlayMode > RTSA_DENSITY_SPECTROGRAM)
        disPlayMode = RTSA_DENSITY_SPECTROGRAM;
    mDisplayMode = disPlayMode;
    globalUserVariable->closeDpxDevice();
    for(int i=0;i<RTSA_BITVIEWNUM;i++)
    {
//        mBitView[i]->close();
#ifdef BITVIEW_TIME_MARKER
        closeAllSpectrogramTimeCursor(i);
#endif
        mBitView[i]->hide();
    }

    setBitViewParam(mDisplayMode);
    mIsCurBitViewSizeChange = false;
    if(mIsZoomIn)
    {
        setZoomIn();
    }
    else
    {
        setZoomOut();
    }
    setGeneralDataToShm();
    pSweepControl.setMeasType(disPlayMode);

    emit RedrawInfoShow(LABEL_MODE);
    return;
}
/**
 * @brief get measure type
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 RtSa_Interface::getDisplay()
{
    return mDisplayMode;
}
/**
 * @brief set single sweep on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setSingleSweep(bool isSingle)
{
    if(globalUserVariable->gSweepType == isSingle)
        return;

    mSingleFinished = true;
    pSweepControl.setSingleSweep(isSingle);
    resetAvgCnt();

    qreal refval = getRefLevel();
    qreal scale = getScaleDiv();
    for(int i=0;i<RTSA_BITVIEWNUM;i++)
    {
        mBitView[i]->setSystemAttribute(RUNNINGSTATE,globalUserVariable->gSweepType);
        mBitView[i]->refleshdisplay();
    }
    for(qint32 i = 0 ; i < RTSA_NUM_SWEEP_POINT; i++)
    {
        mLowData[i] = refval  - 10 * scale;
    }
    setBitViewFileLoadFlag(false);
    return;
}
/**
 * @brief get single sweep on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool RtSa_Interface::IsSingleSweep()
{
    return pSweepControl.IsSingleSweep();
}
/**
 * @brief set auto atten track on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setAutoAttenTrack(bool isOn)
{
    globalUserVariable->gAutoAttenTrack = isOn;
}
/**
 * @brief get auto atten track on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool RtSa_Interface::IsAutoAttenTrackOn()
{
    return globalUserVariable->gAutoAttenTrack;
}
/**
 * @brief set Persistence Time Infinite on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setPersistenceTimeInfinite(bool isInfinite)
{
//    if(mDisplayMode != RTSA_DENSITY && mDisplayMode != RTSA_DENSITY_SPECTROGRAM)
//        return;
    if(globalUserVariable->gAutoPersistenceTime == isInfinite)
        return;
    globalUserVariable->gAutoPersistenceTime = isInfinite;
    pSweepControl.setPersistenceInfinite(isInfinite);
    emit RedrawInfoShow(LABEL_PERSISTENCE);
    return;
}
/**
 * @brief get Persistence Time Infinite on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool RtSa_Interface::IsPersistenceTimeInfinite()
{
    return globalUserVariable->gAutoPersistenceTime;
}
/**
 * @brief set Persistence Time
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setPersistenceTime(qreal time)
{
    // only DENSITY and DENSITY_SPECTROGRAM can set this param
//    if(mDisplayMode != RTSA_DENSITY && mDisplayMode != RTSA_DENSITY_SPECTROGRAM)
//        return;
    if(time < 50000.0)
        time = 50000.0;
    else if(time >= 6.35 * RTSA_S)
        time = 6.35 * RTSA_S;
    if(globalUserVariable->gAutoPersistenceTime == RTSA_INFINITE)
    {
        globalUserVariable->gAutoPersistenceTime = RTSA_FINITE;
    }
    globalUserVariable->gPersistenceTime = (qreal)((qint32)(time / 50000.0) * 50000.0);
    pSweepControl.setPersistenceTime(time);
    emit RedrawInfoShow(LABEL_PERSISTENCE);
    return;
}
/**
 * @brief get Persistence Time
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal RtSa_Interface::getPersistenceTime()
{
    return globalUserVariable->gPersistenceTime;
}
/**
 * @brief RtSa_Interface::getAdjustPersistenceTime
 * @param time
 * @return
 */
QString RtSa_Interface::getAdjustTimeStr(qreal time)
{
    qreal value = time;
    QString strVal;
    QString strUnit;
    if(time >= RTSA_S)
    {
        time /= RTSA_S;
        strVal = QString::number(time,'f',3);
        strUnit = QString(" s");
    }
    else if(time >= RTSA_MS)
    {
        time /= RTSA_MS;
        strVal = QString::number(time,'f',3);
        strUnit = QString(" ms");
    }
    else if(time >= RTSA_US)
    {
        time /= RTSA_US;
        strVal = QString::number(time,'f',3);
        strUnit = QString(" us");
    }
    else
    {
        time *= RTSA_NS;
        strVal = QString::number(time,'f',3);
        strUnit = QString(" ns");
    }
    strVal += strUnit;
    return strVal;
}
/**
 * @brief set highest density
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setHighestDensity(qint32 high)
{
//    if(mDisplayMode != RTSA_DENSITY && mDisplayMode != RTSA_DENSITY_SPECTROGRAM)
//        return ;
    if(high > RTSA_DENTISY_HIGHEST)
        high = RTSA_DENTISY_HIGHEST;
    else if(high < RTSA_DENTISY_LOWEST)
        high = RTSA_DENTISY_LOWEST;
    if(globalUserVariable->gHighestDensity == high)
    {
        return;
    }
    if(high < (qint32)(globalUserVariable->gLowestDensity + 2))
    {
        if(globalUserVariable->gLowestDensity > 98)
        {
            globalUserVariable->gHighestDensity = 100;
            globalUserVariable->gLowestDensity = 98;
        }
        else
        {
            globalUserVariable->gHighestDensity = globalUserVariable->gLowestDensity + 2;
        }
    }
    else
    {
        globalUserVariable->gHighestDensity = high;
    }
    pSweepControl.setHighestDensity(globalUserVariable->gHighestDensity);
    return;
}
/**
 * @brief get highest density
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 RtSa_Interface::getHighestDensity()
{
    return globalUserVariable->gHighestDensity;
}
/**
 * @brief set lowest density
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setLowestDensity(qint32 low)
{
//    if(mDisplayMode != RTSA_DENSITY && mDisplayMode != RTSA_DENSITY_SPECTROGRAM)
//        return ;
    if(low > RTSA_DENTISY_HIGHEST)
        low = RTSA_DENTISY_HIGHEST;
    else if(low < RTSA_DENTISY_LOWEST)
        low = RTSA_DENTISY_LOWEST;
    if(globalUserVariable->gLowestDensity == low)
        return;
    if(low > (qint32)(globalUserVariable->gHighestDensity - 2))
    {
        if(globalUserVariable->gHighestDensity < 2)
        {
            globalUserVariable->gLowestDensity = 2;
            globalUserVariable->gHighestDensity = 4;

        }
        else
        {
            globalUserVariable->gLowestDensity = globalUserVariable->gHighestDensity - 2;
        }
    }else
    {
        globalUserVariable->gLowestDensity = low;
    }
    pSweepControl.setLowestDensity(globalUserVariable->gLowestDensity);
    return;
}
/**
 * @brief get lowest density
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 RtSa_Interface::getLowestDensity()
{
    return globalUserVariable->gLowestDensity;
}
/**
 * @brief set curve
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setCurve(float curve)
{
    if(curve < -100.0)
    {
        curve = -100.0;
    }else if(curve > 100.0)
    {
        curve = 100.0;
    }
    pSweepControl.setDpxCurve(curve);
    return;
}
/**
 * @brief get curve
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 RtSa_Interface::getCurve()
{
    return globalUserVariable->gCurve;
}
/**
 * @brief set Density Level adjust
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setDensityLevelAjust()
{
    pSweepControl.getDpxRealProbability();
    pSweepControl.setHighestDensity(globalUserVariable->gHighestDensity);
    return;
}
/**
 * @brief set acq time auto on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setAcqTimeAuto(bool isAuto)
{
    if(globalUserVariable->gAutoAcqTime == isAuto)
        return;
    globalUserVariable->gAutoAcqTime = isAuto;
    if(globalUserVariable->gAutoAcqTime == RTSA_AUTO)
    {
        globalUserVariable->gAcqTime = RTSA_ACQ_DEFAULT_TIME;
//        globalUserVariable->gSleepTime = globalUserVariable->gAcqTime;
    }
    pSweepControl.setAcqTime(globalUserVariable->gAcqTime);
    updateGeneralDataToBitview(RTSA_ACQ_INFO);
    emit RedrawInfoShow(LABEL_ACQTIME);
    return;
}
/**
 * @brief get acq time auto on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool RtSa_Interface::IsAcqTimeAuto()
{
    return globalUserVariable->gAutoAcqTime;
}
/**
 * @brief set acq time
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setAcqTime(qreal acqtime)
{
    // time default us
    if(acqtime < RTSA_ACQ_MIN_TIME)
        acqtime = RTSA_ACQ_MIN_TIME;
    else if(acqtime > RTSA_ACQ_MAX_TIME)
        acqtime = RTSA_ACQ_MAX_TIME;
    if(globalUserVariable->gAutoAcqTime == RTSA_AUTO)
        globalUserVariable->gAutoAcqTime = RTSA_MANUAL;
    pSweepControl.setAcqTime(acqtime);
//    setSleepTime(acqtime);
//    globalUserVariable->gSleepTime = globalUserVariable->gAcqTime;
    updateGeneralDataToBitview(RTSA_ACQ_INFO);
    emit RedrawInfoShow(LABEL_ACQTIME);
    return;
}
void RtSa_Interface::setSleepTime(qreal sleepTime)
{
    if(sleepTime < RTSA_ACQ_MIN_TIME)
        sleepTime = RTSA_ACQ_MIN_TIME;
    else if(sleepTime > RTSA_ACQ_MAX_TIME)
        sleepTime = RTSA_ACQ_MAX_TIME;
    if(sleepTime < globalUserVariable->gAcqTime)
        sleepTime = globalUserVariable->gAcqTime;
    globalUserVariable->gSleepTime = sleepTime;
    return;
}
/**
 * @brief get acq time
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal RtSa_Interface::getAcqTime()
{
    return globalUserVariable->gAcqTime;
}
/**
 * @brief set current limit id
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setCurLimit(qint32 curIndex)
{
    pLimit.setCurLimit(curIndex);
    return;
}
/**
 * @brief get current limit id
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 RtSa_Interface::getCurLimit()
{
    return pLimit.getCurLimit();
}
/**
 * @brief set current limit on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setCurLimitOn(qint32 LimitID, bool isOn)
{
    if(LimitID < 0)
    {
        LimitID = getCurLimit();
    }
    pLimit.setCurLimitOn(LimitID,isOn);
    emit RedrawInfoShow(LABEL_LIMIT);
    return;
}
/**
 * @brief get current limit on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool RtSa_Interface::IsCurLimitOn(qint32 LimitID)
{
    if(LimitID < 0)
    {
        LimitID = getCurLimit();
    }
    return pLimit.IsCurLimitOn(LimitID);
}
/**
 * @brief set current limit test on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setLimitTestOn(bool isOn)
{
    pLimit.setLimitTestOn(isOn);
    return;
}
/**
 * @brief get current limit test on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool RtSa_Interface::IsLimitTestOn()
{
    return pLimit.IsLimitTestOn();
}
/**
 * @brief set current limit margin on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setMarginOn(qint32 LimitID, bool isOn)
{
    if(LimitID < 0)
    {
        LimitID = getCurLimit();
    }
    pLimit.setMarginOn(LimitID,isOn);
    return;
}
/**
 * @brief get current limit margin on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool RtSa_Interface::IsMarginOn(qint32 LimitID)
{
    if(LimitID < 0)
    {
        LimitID = getCurLimit();
    }
    return pLimit.IsMarginOn(LimitID);
}
/**
 * @brief set current limit margin
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setMargin(qint32 LimitID, qreal margin)
{
    if(LimitID < 0)
    {
        LimitID = getCurLimit();
    }
    pLimit.setMargin(LimitID,margin);
    return;
}
/**
 * @brief get current limit margin
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal RtSa_Interface::getMargin(qint32 LimitID)
{
    if(LimitID < 0)
    {
        LimitID = getCurLimit();
    }
    return pLimit.getMargin(LimitID);
}
/**
 * @brief set current limit type
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setLimitType(qint32 LimitID, qint32 nType)
{
    if(LimitID < 0)
    {
        LimitID = getCurLimit();
    }
    pLimit.setLimitType(LimitID,nType);
    return;
}
/**
 * @brief get current limit type
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 RtSa_Interface::getLimitType(qint32 LimitID)
{
    if(LimitID < 0)
    {
        LimitID = getCurLimit();
    }
    return pLimit.getLimitType(LimitID);
}
/**
 * @brief set current limit data num
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setLimitNum(qint32 LimitID, qint32 num)
{
    if(LimitID < 0)
    {
        LimitID = getCurLimit();
    }
    pLimit.setLimitNum(LimitID,num);
    return;
}
/**
 * @brief get current limit data num
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 RtSa_Interface::getLimitDataNum(qint32 LimitID)
{
    if(LimitID < 0)
    {
        LimitID = getCurLimit();
    }
    return pLimit.getLimitDataNum(LimitID);
}
/**
 * @brief set current limit data freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setLimitFreqData(qreal *pData, qint32 DataNum, qint32 LimitID)
{
    pLimit.setLimitFreqData(pData,DataNum,LimitID);
    return;
}
/**
 * @brief get current limit data freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal* RtSa_Interface::getLimitFreqData(qint32 LimitID)
{
    return pLimit.getLimitFreqData(LimitID);
}
/**
 * @brief set current limit data ampt
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setLimitAmptData(qreal *pData, qint32 DataNum, qint32 LimitID)
{
    pLimit.setLimitAmptData(pData,DataNum,LimitID);
    return;
}
/**
 * @brief get current limit data ampt
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal* RtSa_Interface::getLimitAmptData(qint32 LimitID)
{
    return pLimit.getLimitAmptData(LimitID);
}
/**
 * @brief insert limit row
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::InsertLimitRow()
{
    pLimit.InsertLimitRow();
    return;
}
/**
 * @brief delete limit row
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::DeleteLimitRow(qint32 index)
{
    if(index < 0)
    {
        index = getCurLimit();
    }
    pLimit.DelLimitRow(index);
    return;
}
/**
 * @brief delete limit
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::DeleteLimit(qint32 index)
{
    if(index < 0)
    {
        index = getCurLimit();
    }
    pLimit.DeleteLimit(index);
    return;
}
void RtSa_Interface::setLimitTableShow(bool isShow)
{
    pLimit.setLimitTableShow(isShow);
    return;
}
/**
 * @brief set current trace id
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setCurTrace(qint32 traceID)
{
    pTrace.setCurTrace(traceID);
    repaintBitview();
    emit RedrawInfoShow(LABEL_TRACE_STATUS);
    return;
}
/**
 * @brief get current trace id
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 RtSa_Interface::getCurTrace()
{
    return pTrace.getCurTrace();
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-10-08
*/
void RtSa_Interface::setTraceViewStatus(bool status, qint32 traceID)
{
    if(traceID < 0)
    {
        traceID = getCurTrace();
    }
    setTraceOn(traceID,status);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-10-08
*/
bool RtSa_Interface::getTraceViewStatus(qint32 traceID)
{
    if(traceID < 0)
    {
        traceID = getCurTrace();
    }
    return IsTraceOn(traceID);
//    if(getTraceType(traceID) != RTSA_TRACE_OFF)
//    {
//        return true;
//    }
//    else
//    {
//        return false;
//    }
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-10-08
*/
void RtSa_Interface::setCurTraceType(qint32 traceType)
{
    qint32 curTrace = getCurTrace();
    setTraceType(curTrace,traceType);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-10-08
*/
qint32 RtSa_Interface::getCurTraceType()
{
    qint32 type = 0;
    qint32 curTrace = getCurTrace();
    type = getTraceType(curTrace);
    return type;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-10-08
*/
void RtSa_Interface::setCurTraceAvgNum(qint32 Num)
{
    qint32 curTrace = getCurTrace();
    setAvgNum(curTrace,Num);
    return;
}

qint32 RtSa_Interface::getCurTraceAvgNum()
{
    qint32 avgNum = 0;
    qint32 curTrace = getCurTrace();
    avgNum = getAvgNum(curTrace);
    return avgNum;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-11-01
*/
void RtSa_Interface::setTraceOn(qint32 traceID, bool isTraceOn)
{
    pTrace.setTraceOn(traceID,isTraceOn);
//    if(isTraceOn)
//    {
//        resetAvgCnt();
//    }
    emit RedrawInfoShow(LABEL_TRACE_STATUS);
    emit RedrawInfoShow(LABEL_AVERAGE);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-11-01
*/
bool RtSa_Interface::IsTraceOn(qint32 traceID)
{
    return pTrace.IsTraceOn(traceID);
}

/**
 * @brief set current trace type
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setTraceType(qint32 traceID, qint32 traceType)
{
    pTrace.setTraceType(traceID,traceType);
//    resetAvgCnt();
    emit RedrawInfoShow(LABEL_TRACE_STATUS);
    emit RedrawInfoShow(LABEL_AVERAGE);
    return;
}
/**
 * @brief get current trace type
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 RtSa_Interface::getTraceType(qint32 traceID)
{
    return pTrace.getTraceType(traceID);
}
/**
 * @brief set current dector type
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setDectorType(qint32 DectorType)
{
    pSweepControl.setDectorType(DectorType);
    resetAvgCnt();
    emit RedrawInfoShow(LABEL_DETECTOR);
    return;
}
/**
 * @brief get current dector type
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 RtSa_Interface::getDectorType()
{
    return pSweepControl.getDectorType();
}
/**
 * @brief set current trace average on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setAvgOn(qint32 traceID, bool isOn)
{
    pTrace.setAvgOn(traceID,isOn);
    return;
}
/**
 * @brief get current trace average on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool RtSa_Interface::IsAvgOn(qint32 traceID)
{
    return pTrace.IsAvgOn(traceID);
}
/**
 * @brief set current trace average num
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setAvgNum(qint32 traceID, qint32 Num)
{
    pTrace.setAvgNum(traceID,Num);
    resetAvgCnt();
    return;
}
/**
 * @brief get current trace average num
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 RtSa_Interface::getAvgNum(qint32 traceID)
{
    return pTrace.getAvgNum(traceID);
}
/**
 * @brief get current trace now average num
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 RtSa_Interface::getCurAvgNum(qint32 traceID)
{
    return pTrace.getCurAvgNum(traceID);
}
/**
 * @brief reset average count
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::resetAvgCnt()
{
    for(qint32 j = 0 ;j < RTSA_BITVIEWNUM; j++)
    {
//        if(!mSingleFinished)
//        {
//            mBitView[j]->refreshSepectrogramRect();
//        }
        for(qint32 i = 0; i < RTSA_NUM_TRACE; i++)
        {
            qint32 tracetype = mBitView[j]->getTraceAttribute(i,BIT_TRACE_TYPE_ATTR);
//            qint32 tracetype = mBitView[j]->getTraceAttribute(i,BIT_TRACE_TYPE_ATTR);
            //Albert 19/03/13 when sweep param changed, trace data should refresh.
//            mBitView[j]->setTraceAttribute(i,BIT_TRACE_TYPE_ATTR,getTraceType(i));
            if(tracetype == RTSA_AVERAGE)
            {
                mBitView[j]->setTraceAttribute(i,BIT_RE_AVAG_ATTR,BITON);
            }
            if(tracetype == RTSA_MAX_HOLD)
            {
                mBitView[j]->setTraceAttribute(i,BIT_TRACE_TYPE_ATTR,BIT_MAX_HOLD);
            }
            if(tracetype == RTSA_MIN_HOLD)
            {
                mBitView[j]->setTraceAttribute(i,BIT_TRACE_TYPE_ATTR,BIT_MIN_HOLD);
            }
        }
    }
    refreshMainDisplay();
    return;
}
/**
 * @brief set render trace data
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setTraceData(qreal *pData, qint32 dataNum, qint32 traceID)
{
    pTrace.setTraceData(pData,dataNum,traceID);
    return;
}
/**
 * @brief get render trace data
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal* RtSa_Interface::GetTraceData(qint32 dataNum, qint32 traceID)
{
    return pTrace.GetTraceData(dataNum,traceID);
}
/**
 * @brief set current marker id
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setCurMarkerID(qint32 MarkerID)
{
    if(mBitView[curwindowindex]->getBitviewType() == RTSA_SPECTROGRAM)
        return;

    pMarker.setCurMarkerID(MarkerID);
    emit MarkerSelectOnOff(MarkerID,true);
    return;
}
/**
 * @brief get current marker id
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 RtSa_Interface::getCurMarkerID()
{
    return pMarker.getCurMarkerID();
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-10-08
*/
void RtSa_Interface::setCurMarkerOn(bool isOn)
{
    qint32 markerID = getCurMarkerID();
    setMarkerOn(markerID,isOn);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-10-08
*/
bool RtSa_Interface::isCurMarkerOn()
{
    bool MarkerOn = false;
    qint32 markerID = getCurMarkerID();
    MarkerOn = isMarkerOn(markerID);
    return MarkerOn;
}
/**
 * @brief set current marker on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setMarkerOn(qint32 MarkerID, bool isOn)
{
    if(mBitView[curwindowindex]->getBitviewType() == RTSA_SPECTROGRAM)
        return;
    if(isMarkerOn(MarkerID) == isOn)
        return;
    if(!isOn)
    {
        mIsPeakTrackOn = false;
        setMarkerType(MarkerID,RTSA_REF);
        setMarkerNoiseOn(MarkerID,false);
    }

    for(qint32 i = 0;i < RTSA_BITVIEWNUM; i++)
    {
        mBitView[i]->setMarkerAttribute(BIT_MARKER_VISIABLE,isOn,MarkerID);
        mBitView[i]->setMarkerFreqAttribute(BIT_MARKER_NORMAL,getCenterFreq(),MarkerID);
        mBitView[i]->setMarkerFreqAttribute(BIT_MARKER_DELTA,getCenterFreq(),MarkerID);
        mBitView[i]->markerUpdateByFreq();
        mBitView[i]->refleshdisplay();
    }
//    pMarker.setMarkerOn(MarkerID,isOn);
//    if(!isOn)
//    {
//        setMarkerRefFreq(MarkerID,getCenterFreq());
//        setMarkerDeltaFreq(MarkerID,getCenterFreq());
//    }
    emit MarkerSelectOnOff(MarkerID,isOn);
    emit BitViewMakerDraw(MarkerID,isOn);
    if(mIsZoomIn)
    {
       setZoomIn();
    }
    else
    {
        setZoomOut();
    }
    return;
}
/**
 * @brief get current marker on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool RtSa_Interface::isMarkerOn(qint32 MarkerID)
{
    return pMarker.isMarkerOn(MarkerID);
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-10-08
*/
void RtSa_Interface::setCurMarkerType(qint32 MarkerType)
{
    qint32 curMarkerID = getCurMarkerID();
    setMarkerType(curMarkerID,MarkerType);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-10-08
*/
qint32 RtSa_Interface::getCurMarkerType()
{
    qint32 type = 0;
    qint32 curMarkerID = getCurMarkerID();
    type = getMarkerType(curMarkerID);
    return type;
}

/**
 * @brief set current marker type
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setMarkerType(qint32 MarkerID, qint32 MarkerType)
{
    if(mBitView[curwindowindex]->getBitviewType() == RTSA_SPECTROGRAM)
        return;

    pMarker.setMarkerType(MarkerID,MarkerType);

    return;
}
/**
 * @brief get current marker type
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 RtSa_Interface::getMarkerType(qint32 MarkerID)
{
    return pMarker.getMarkerType(MarkerID);
}
/**
 * @brief set current marker ref freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setMarkerRefFreq(qint32 MarkerID, qreal refFreq)
{
    if(mBitView[curwindowindex]->getBitviewType() == RTSA_SPECTROGRAM)
        return;
    if(MarkerID < 0)
    {
        MarkerID = getCurMarkerID();
    }
    pMarker.setMarkerRefFreq(MarkerID,refFreq);
    return;
}
/**
 * @brief get current marker ref freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal RtSa_Interface::getMarkerRefFreq(qint32 MarkerID)
{
    if(MarkerID < 0)
    {
        MarkerID = getCurMarkerID();
    }
    return pMarker.getMarkerRefFreq(MarkerID) + globalUserVariable->gfreqOffset;
}
/**
 * @brief set current marker delta freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setMarkerDeltaFreq(qint32 MarkerID, qreal DeltaFreq)
{
    if(mBitView[curwindowindex]->getBitviewType() == RTSA_SPECTROGRAM)
        return;
    if(MarkerID < 0)
    {
        MarkerID = getCurMarkerID();
    }
    pMarker.setMarkerDeltaFreq(MarkerID,DeltaFreq);
    return;
}
/**
 * @brief get current marker delta freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal RtSa_Interface::getMarkerDeltaFreq(qint32 MarkerID)
{
    if(MarkerID < 0)
    {
        MarkerID = getCurMarkerID();
    }
    return pMarker.getMarkerDeltaFreq(MarkerID) + globalUserVariable->gfreqOffset;
}
/**
 * @brief set current marker display
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setMarkerDisplay(qint32 display)
{
    if(mBitView[curwindowindex]->getBitviewType() == RTSA_SPECTROGRAM)
        return;

    pMarker.setMarkerDisplay(display);
    return;
}
/**
 * @brief get current marker display
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 RtSa_Interface::getMarkerDisplay()
{
    return pMarker.getMarkerDisplay();
}
/**
 * @brief set current marker noise on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setMarkerNoiseOn(qint32 MarkerID, bool isOn)
{
    if(mBitView[curwindowindex]->getBitviewType() == RTSA_SPECTROGRAM)
        return;
    if(MarkerID < 0)
    {
        MarkerID = getCurMarkerID();
    }
    setDectorType(RTSA_DEC_SAMPLE);
    pMarker.setMarkerNoiseOn(MarkerID,isOn);
    return;
}
/**
 * @brief get current marker noise on/off
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
bool RtSa_Interface::IsMarkerNoiseOn(qint32 MarkerID)
{
    if(MarkerID < 0)
    {
        MarkerID = getCurMarkerID();
    }
    return pMarker.IsMarkerNoiseOn(MarkerID);
}
/**
 * @brief set current marker to center freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setMarkerToCenter()
{
    if(mBitView[curwindowindex]->getBitviewType() == RTSA_SPECTROGRAM)
        return;

    qint32 markerID = pMarker.getCurMarkerID();
    qreal centerFreq = 0;
    if(pMarker.isMarkerOn(markerID))
    {
        centerFreq = pMarker.getMarkerCurFreq(BIT_MARKER_CURRENT_FREQ);
        setCenterFreq(centerFreq);
    }
    showBitViewBottomMsg(BV_BOTTOM_CENTERANDSPAN);
    return;
}
/**
 * @brief set current marker to step freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setMarkerToCFStep()
{
    if(mBitView[curwindowindex]->getBitviewType() == RTSA_SPECTROGRAM)
        return;

    qint32 markerID = pMarker.getCurMarkerID();
    qreal CFStepFreq = 0;
    if(pMarker.isMarkerOn(markerID))
    {
        CFStepFreq = pMarker.getMarkerCurFreq(BIT_MARKER_STEP_FREQ);
        setCFStep(CFStepFreq);
    }
    return;
}
/**
 * @brief set current marker to start freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setMarkerToStart()
{
    if(mBitView[curwindowindex]->getBitviewType() == RTSA_SPECTROGRAM)
        return;

    qint32 markerID = pMarker.getCurMarkerID();
    qreal startFreq = 0;
    if(pMarker.isMarkerOn(markerID))
    {
        startFreq = pMarker.getMarkerCurFreq(BIT_MARKER_CURRENT_FREQ);
        setStartFreq(startFreq);
    }
    showBitViewBottomMsg(BV_BOTTOM_CENTERANDSPAN);
    return;
}
/**
 * @brief set current marker to stop freq
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setMarkerToStop()
{
    if(mBitView[curwindowindex]->getBitviewType() == RTSA_SPECTROGRAM)
        return;

    qint32 markerID = pMarker.getCurMarkerID();
    qreal stopFreq = 0;
    if(pMarker.isMarkerOn(markerID))
    {
        stopFreq = pMarker.getMarkerCurFreq(BIT_MARKER_CURRENT_FREQ);
        setStopFreq(stopFreq);
    }
    showBitViewBottomMsg(BV_BOTTOM_CENTERANDSPAN);
    return;
}
/**
 * @brief set current marker to ref level
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setMarkerToRefLevel()
{
    if(mBitView[curwindowindex]->getBitviewType() == RTSA_SPECTROGRAM)
        return;

    qint32 markerID = pMarker.getCurMarkerID();
    qreal refLevel = 0;
    if(pMarker.isMarkerOn(markerID))
    {
        refLevel = pMarker.getMarkerAmptInfo(BIT_MARKER_REF);
        setRefLevel(refLevel);
    }
    return;
}
/**
 * @brief RtSa_Interface::getMarkerFreq
 * @param MarkerID
 * @return
 */
qreal RtSa_Interface::getMarkerFreq(qint32 MarkerID)
{
    if(getMarkerType(MarkerID) == RTSA_REF)
    {
        return getMarkerRefFreq(MarkerID);
    }
    else
    {
        return getMarkerDeltaFreq(MarkerID);
    }
}
/**
 * @brief RtSa_Interface::setMarkerFreq
 * @param MarkerID
 * @param Freq
 */
void RtSa_Interface::setMarkerFreq(qint32 MarkerID, qreal Freq)
{
    if(mBitView[curwindowindex]->getBitviewType() == RTSA_SPECTROGRAM)
        return;

    if(getMarkerType(MarkerID) == RTSA_REF)
    {
        setMarkerRefFreq(MarkerID,Freq);
    }
    else
    {
        setMarkerDeltaFreq(MarkerID,Freq);
    }
    emit BitViewMakerMoved(true);
    return;
}
/**
* @brief IsMarkerAlreadyOn
* @param none
* @Author Albert
* @date 2019-03-27
*/
bool RtSa_Interface::IsMarkerAlreadyOn()
{
    bool isOn = false;
    for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
    {
        if(isMarkerOn(i))
        {
            isOn = true;
        }
    }
    return isOn;
}
/**
 * @brief RtSa_Interface::setPeakTrackOn
 * @param PeakTrackOn
 */
void RtSa_Interface::setPeakTrackOn(bool PeakTrackOn)
{
    mIsPeakTrackOn = PeakTrackOn;
    return;
}
/**
* @brief IsPeakTrackOn
* @param none
* @Author Albert
* @date 2019-03-27
*/
bool RtSa_Interface::IsPeakTrackOn()
{
    return mIsPeakTrackOn;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-14
*/
void RtSa_Interface::showMarkerWidget(bool isShow)
{
//    if(isMarkerBtnPressed == isShow)
//        return;
    isMarkerBtnPressed = isShow;
    if(mIsZoomIn)
    {
       setZoomIn();
    }
    else
    {
        setZoomOut();
    }
    return;
}
/**
 * @brief get current marker ref ampt
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal RtSa_Interface::getMarkerRefAmpt(qint32 MarkerID)
{
    return pMarker.getMarkerRefAmpt(MarkerID);
}
/**
 * @brief get current marker delta ampt
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal RtSa_Interface::getMarkerDeltaAmpt(qint32 MarkerID)
{
    return pMarker.getMarkerDeltaAmpt(MarkerID);
}
/**
 * @brief get current marker noise ampt
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qreal RtSa_Interface::getMarkerNoiseAmpt(qint32 MarkerID)
{
    return pMarker.getMarkerNoiseAmpt(MarkerID);
}
QString RtSa_Interface::getMarkerInfoStr(qint32 MarkerID)
{
    return pMarker.getmarkerInfoStr(MarkerID);
}
/**
 * @brief set trigger type
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setTrigger(qint32 TriggerMode)
{
    if(TriggerMode >= RTSA_TRIGGER_FMTMASK)
        TriggerMode = RTSA_TRIGGER_FMTMASK;
    else if(TriggerMode < RTSA_TRIGGER_EXTERNAL)
          TriggerMode = RTSA_TRIGGER_FREE_RUN;
    if(globalUserVariable->gTriggerMode == TriggerMode)
        return;

    if(TriggerMode == RTSA_TRIGGER_FMTMASK)
    {
        setFmtDataNum(mFmtDataTotalNum);
        setFmtFreqData(fmtFreq,mFmtDataTotalNum);
        setFmtAmptData(fmtAmplitude,mFmtDataTotalNum);
    }
    pSweepControl.setTrigger(TriggerMode);
    QThread::msleep(200);
    pSweepControl.setTriggerParam();
    if(TriggerMode == RTSA_TRIGGER_FMTMASK)
    {
        QThread::msleep(200);
        pSweepControl.recalFmtAxisData();
    }
    for(qint32 i  = 0;i < RTSA_BITVIEWNUM; i++)
    {
        mBitView[i]->setTriggerrMode(TriggerMode);
        if(TriggerMode == RTSA_TRIGGER_FMTMASK)
        {
            mBitView[i]->setFmtShow(true);
        }
        else
        {
            mBitView[i]->setFmtShow(false);
        }
        mBitView[i]->refleshdisplay();
    }
    emit RedrawInfoShow(LABEL_TRIGGER);
//    mBitView[curwindowindex]->refleshdisplay();
    return;
}
/**
 * @brief get trigger type
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
qint32 RtSa_Interface::getTrigger()
{
    return pSweepControl.getTrigger();
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-03
*/
void RtSa_Interface::setTriggerSlope(qint32 TriggerMode, qint32 slope)
{
    if(TriggerMode < 0)
    {
        TriggerMode = globalUserVariable->gTriggerMode;
    }
    pSweepControl.setTriggerSlope(TriggerMode,slope);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-03
*/
qint32 RtSa_Interface::getTriggerSlope(qint32 TriggerMode)
{
    return pSweepControl.getTriggerSlope(TriggerMode);
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
void RtSa_Interface::setTriggerDelayStatus(qint32 TriggerMode, bool delayStatus)
{
    pSweepControl.setTriggerDelayStatus(TriggerMode,delayStatus);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
bool RtSa_Interface::getTriggerDelayStatus(qint32 TriggerMode)
{
    return pSweepControl.getTriggerDelayStatus(TriggerMode);
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
void RtSa_Interface::setTriggerDelay(qint32 TriggerMode, qreal Delay)
{
    pSweepControl.setTriggerDelay(TriggerMode,Delay);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
qreal RtSa_Interface::getTriggerDelay(qint32 TriggerMode)
{
    return pSweepControl.getTriggerDelay(TriggerMode);
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-03
*/
void RtSa_Interface::setTriggerLevel(qint32 TriggerMode, qreal level)
{
    if(level > (globalUserVariable->gRefLevel + globalUserVariable->gfreqOffset))
    {
        level = globalUserVariable->gRefLevel + globalUserVariable->gfreqOffset;
    }
    if(TriggerMode == RTSA_TRIGGER_VIDEO)
    {
        for(qint32 i  = 0;i < RTSA_BITVIEWNUM; i++)
        {
            mBitView[i]->setVideoTriggerLevel(level);
            mBitView[i]->refleshdisplay();
        }
    }
    pSweepControl.setTriggerLevel(TriggerMode,level);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-03
*/
qreal RtSa_Interface::getTriggerLevel(qint32 TriggerMode)
{
    return pSweepControl.getTriggerLevel(TriggerMode);
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
void RtSa_Interface::setTriggerPeriodTime(qreal time)
{
    pSweepControl.setTriggerPeriodTime(time);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-04
*/
qreal RtSa_Interface::getTriggerPeriodTime()
{
    return pSweepControl.getTriggerPeriodTime();
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-17
*/
void RtSa_Interface::settriggerHoldOffTime(qint32 TriggerMode, qreal holdOffTime)
{
    pSweepControl.settriggerHoldOffTime(TriggerMode,holdOffTime);
    return;
}
qreal RtSa_Interface::getriggerHoldOffTime(qint32 TriggerMode)
{
    return pSweepControl.getriggerHoldOffTime(TriggerMode);
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-07-03
*/
void RtSa_Interface::setFmtType(qint32 Upper)
{
    if(Upper < BIT_FMT_UPPER)
        Upper = BIT_FMT_UPPER;
    else if(Upper > BIT_FMT_LOWER)
        Upper = BIT_FMT_LOWER;
    globalUserVariable->gfmtType = Upper;

    //should reset fmt data when type changed
    setFmtDataNum(mFmtDataTotalNum);
    setFmtFreqData(fmtFreq,mFmtDataTotalNum);
    setFmtAmptData(fmtAmplitude,mFmtDataTotalNum);

    for(qint32 i = 0; i < RTSA_BITVIEWNUM; i++)
    {
        if(mBitView[i]->getBitviewType() != RTSA_SPECTROGRAM)
        {
            mBitView[i]->setFmtType(Upper);
            mBitView[i]->refleshdisplay();
        }
    }
    return;
}

qint32 RtSa_Interface::getFmtType()
{
    return globalUserVariable->gfmtType;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-24
*/
void RtSa_Interface::setCurFmtDataIndex(qint32 curIndex)
{
    if(curIndex >= mFmtDataTotalNum - 1)
        curIndex = mFmtDataTotalNum - 1;
    else if(curIndex < 0)
        curIndex = 0;
    mFmtCurDataIndex = curIndex;
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-24
*/
qint32 RtSa_Interface::getCurFmtDataIndex()
{
    return mFmtCurDataIndex;
}
/**
* @brief  setFmtDataNum
* @param dataNum
* @Author Albert
* @date 2019-05-24
*/
void RtSa_Interface::setFmtDataNum(qint32 dataNum)
{
    mFmtDataTotalNum = dataNum;
    return;
}

qint32 RtSa_Interface::getFmtDataNum()
{
    return mFmtDataTotalNum;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-24
*/
void RtSa_Interface::setFmtFreqData(qreal *data, qint32 dataNum)
{
    if(dataNum < 0)
    {
        return;
    }
//    memset(fmtFreq,0,RTSA_NUM_SWEEP_POINT * sizeof(qreal));
    qreal startFreq = getStartFreq()/RTSA_MHZ;
    for(qint32 i =0 ; i< dataNum; i++)
    {
        if(data[i] < startFreq)
        {
            fmtFreq[i] = data[i];
        }
        else
        {
            fmtFreq[i] = data[i];
        }
    }
//    memcpy(fmtFreq,data,dataNum * sizeof(qreal));
    for(qint32 i = 0; i < RTSA_BITVIEWNUM; i++)
    {
        if(mBitView[i]->getBitviewType() != RTSA_SPECTROGRAM)
        {
            mBitView[i]->setFMTData(fmtFreq,dataNum,BIT_FMT_FREQ);
            mBitView[i]->refleshdisplay();
        }
    }
     return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-24
*/
void RtSa_Interface::setFmtAmptData(qreal *data, qint32 dataNum)
{
    if(dataNum < 0)
    {
        return;
    }
    memcpy(fmtAmplitude,data,dataNum * sizeof(qreal));
    for(qint32 i = 0; i < RTSA_BITVIEWNUM; i++)
    {
        if(mBitView[i]->getBitviewType() != RTSA_SPECTROGRAM)
        {
            mBitView[i]->setFMTData(data,dataNum,BIT_FMT_AMPT);
            mBitView[i]->refleshdisplay();
        }
    }
    if(globalUserVariable->gfmtType == BIT_FMT_UPPER)
    {
        calUpperFmtPointsY(dataNum);
    }
    else
    {
        calLowerFmtPointsY(dataNum);
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-23
*/
qreal* RtSa_Interface::getFMTFreqData()
{
    return fmtFreq;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-23
*/
qreal* RtSa_Interface::getFMTAmplitudeData()
{
    return fmtAmplitude;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-10
*/
void RtSa_Interface::calUpperFmtPointsY(qint32 dataNum)
{
    if(dataNum < 0)
        return;
    qint32 highPointY = 200;
    qint32 lowPointY = 0;
    qint32 pointY = 0;
    qreal yDivs = 0;
    qint32 cnt = 0;
    qreal baseY = globalUserVariable->gRefLevel + globalUserVariable->gRefOffset;
    qreal BottomY = baseY - globalUserVariable->gScaleDiv * 10;
    qreal freqStep = globalUserVariable->gSpanFreq / (RTSA_NUM_SWEEP_POINT - 1);
    qint32 xDivs = 0;
    qreal Freq0 = fmtFreq[0];
    qreal Freq1 = 0.0;

    if(Freq0 * RTSA_MHZ < globalUserVariable->gStartFreq)
    {
        xDivs = 0;
    }
    else
    {
        xDivs = (qint32)((Freq0 * RTSA_MHZ - globalUserVariable->gStartFreq) / freqStep);
    }
    qint32 index = xDivs;

    //divide into 3 parts
    memset(&globalUserVariable->gFmtData,0,sizeof(qint32) * RTSA_NUM_SWEEP_POINT);
    if(dataNum == 1)
    {
        index = xDivs;
        if(xDivs == 0)
        {
            yDivs = 0;
        }
        else
        {
            yDivs = (fmtAmplitude[1] - fmtAmplitude[0])/xDivs;
        }
        lowPointY = (fmtAmplitude[0]/* + RTSA_COMP_TEMPDATA*/ + yDivs * index - BottomY)/(globalUserVariable->gScaleDiv * 10) * 200;
        pointY = (1 << 16) + (highPointY << 8) + lowPointY;
        globalUserVariable->gFmtData[index] = pointY;
//        while (xDivs) {
//            lowPointY = (fmtAmplitude[0]/* + RTSA_COMP_TEMPDATA*/ + yDivs * index - BottomY)/(globalUserVariable->gScaleDiv * 10) * 200;
//            pointY = (1 << 16) + (highPointY << 8) + lowPointY;
//            globalUserVariable->gFmtData[index] = pointY;
//            index ++;
//            xDivs --;
//        }
    }
    else
    {
        for(qint32 i = 1 ; i < dataNum; i++)
        {
            Freq0 = fmtFreq[i - 1];
            if(Freq0 < globalUserVariable->gStartFreq/RTSA_MHZ)
            {
                Freq0 = globalUserVariable->gStartFreq/RTSA_MHZ;
            }
            else if(Freq0 >= globalUserVariable->gStopFreq/RTSA_MHZ)
            {
                Freq0 = globalUserVariable->gStopFreq/RTSA_MHZ;
            }
            Freq1 = fmtFreq[i];
            if(Freq1 >= globalUserVariable->gStopFreq/RTSA_MHZ)
            {
                Freq1 = globalUserVariable->gStopFreq/RTSA_MHZ;
            }
            else if(Freq1 < globalUserVariable->gStartFreq/RTSA_MHZ)
            {
                Freq1 = globalUserVariable->gStartFreq/RTSA_MHZ;
            }
            xDivs = (Freq1 - Freq0) * RTSA_MHZ /freqStep ;
            if(xDivs == 0)
            {
                yDivs = fmtAmplitude[i];
            }
            else
            {
                yDivs = (fmtAmplitude[i] - fmtAmplitude[i - 1])/xDivs;
            }
            cnt = 0;
//            qreal a = 0;
            while (xDivs) {
                lowPointY = (fmtAmplitude[i - 1]/* + RTSA_COMP_TEMPDATA*/ + cnt * yDivs - BottomY)/(globalUserVariable->gScaleDiv * 10) * 200;
                pointY = (1 << 16) + (highPointY << 8) + lowPointY;
                globalUserVariable->gFmtData[index] = pointY;
                index ++;
                xDivs --;
                cnt ++;
            }
        }
    }
//    qreal a = (fmtAmplitude[dataNum - 1] - BottomY);
    lowPointY = (fmtAmplitude[dataNum - 1]/* + RTSA_COMP_TEMPDATA*/ - BottomY)/(globalUserVariable->gScaleDiv * 10) * 200;
    pointY = (1 << 16) + (highPointY << 8) + lowPointY;
    globalUserVariable->gFmtData[index] = pointY;

    pSweepControl.recalFmtAxisData();

    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-10
*/
void RtSa_Interface::calLowerFmtPointsY(qint32 dataNum)
{
    if(dataNum < 0)
        return;
    qint32 highPointY = 200;
    qint32 lowPointY = 0;
    qint32 pointY = 0;
    qreal yDivs = 0;
    qint32 cnt = 0;
    qreal baseY = globalUserVariable->gRefLevel + globalUserVariable->gRefOffset;
    qreal BottomY = baseY - globalUserVariable->gScaleDiv * 10;
    qreal freqStep = globalUserVariable->gSpanFreq / (RTSA_NUM_SWEEP_POINT - 1);
    qint32 xDivs = 0;
    qreal Freq0 = fmtFreq[0];
    qreal Freq1 = 0.0;

    if(Freq0 * RTSA_MHZ < globalUserVariable->gStartFreq)
    {
        xDivs = 0;
    }
    else
    {
        xDivs = (qint32)((Freq0 * RTSA_MHZ - globalUserVariable->gStartFreq) / freqStep);
    }
//    qint32 xDivs = (qint32)((fmtFreq[0] * RTSA_MHZ - globalUserVariable->gStartFreq) / freqStep);
    qint32 index = xDivs;

    //divide into 3 parts
    memset(&globalUserVariable->gFmtData,0,sizeof(qint32) * RTSA_NUM_SWEEP_POINT);
    if(dataNum == 1)
    {
        index = xDivs;
        yDivs = (fmtAmplitude[1] - fmtAmplitude[0])/xDivs;
        highPointY = (fmtAmplitude[0]/* + RTSA_COMP_TEMPDATA*/ + yDivs * index - BottomY)/(globalUserVariable->gScaleDiv * 10) * 200;
        pointY = (1 << 16) + (highPointY << 8) + lowPointY;
        globalUserVariable->gFmtData[index] = pointY;
//        while (xDivs) {
//            lowPointY = (fmtAmplitude[0]/* + RTSA_COMP_TEMPDATA*/ + yDivs * index - BottomY)/(globalUserVariable->gScaleDiv * 10) * 200;
//            pointY = (1 << 16) + (highPointY << 8) + lowPointY;
//            globalUserVariable->gFmtData[index] = pointY;
//            index ++;
//            xDivs --;
//        }
    }
    else
    {
        for(qint32 i = 1 ; i < dataNum; i++)
        {
            Freq0 = fmtFreq[i - 1];
            if(Freq0 < globalUserVariable->gStartFreq/RTSA_MHZ)
            {
                Freq0 = globalUserVariable->gStartFreq/RTSA_MHZ;
            }
            else if(Freq0 >= globalUserVariable->gStopFreq/RTSA_MHZ)
            {
                Freq0 = globalUserVariable->gStopFreq/RTSA_MHZ;
            }
            Freq1 = fmtFreq[i];
            if(Freq1 >= globalUserVariable->gStopFreq/RTSA_MHZ)
            {
                Freq1 = globalUserVariable->gStopFreq/RTSA_MHZ;
            }
            else if(Freq1 < globalUserVariable->gStartFreq/RTSA_MHZ)
            {
                Freq1 = globalUserVariable->gStartFreq/RTSA_MHZ;
            }
//            if(Freq0 < globalUserVariable->gStartFreq/RTSA_MHZ)
//            {
//                Freq0 = globalUserVariable->gStartFreq/RTSA_MHZ;
//            }
//            Freq1 = fmtFreq[i];
            xDivs = (Freq1 - Freq0) * RTSA_MHZ /freqStep ;
            if(xDivs == 0)
            {
                yDivs = fmtAmplitude[i];
            }
            else
            {
                yDivs = (fmtAmplitude[i] - fmtAmplitude[i - 1])/xDivs;
            }
            cnt = 0;
//            qreal a = 0;
            while (xDivs) {
                highPointY = (fmtAmplitude[i - 1]/* + RTSA_COMP_TEMPDATA*/ + cnt * yDivs - BottomY)/(globalUserVariable->gScaleDiv * 10) * 200;
                pointY = (1 << 16) + (highPointY << 8) + lowPointY;
                globalUserVariable->gFmtData[index] = pointY;
                index ++;
                xDivs --;
                cnt ++;
            }
        }
    }
    highPointY = (fmtAmplitude[dataNum - 1]/* + RTSA_COMP_TEMPDATA*/ - BottomY)/(globalUserVariable->gScaleDiv * 10) * 200;
    pointY = (1 << 16) + (highPointY << 8) + lowPointY;
    globalUserVariable->gFmtData[index] = pointY;

    pSweepControl.recalFmtAxisData();

    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-24
*/
void RtSa_Interface::setCurFmtFreqData(qreal data, qint32 index)
{
    if(data <= globalUserVariable->gStartFreq/RTSA_MHZ)
    {
        data  = globalUserVariable->gStartFreq / RTSA_MHZ;
    }
    else if(data >= globalUserVariable->gStopFreq/RTSA_MHZ)
    {
        data = globalUserVariable->gStopFreq / RTSA_MHZ;
    }
    if(isFreqInFmtArray(data))
    {
        return;
    }
    fmtFreq[index] = data;
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-24
*/
qreal RtSa_Interface::getCurFmtFreqData(qint32 index)
{
    return fmtFreq[index];
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-24
*/
void RtSa_Interface::setCurFmtAmptData(qreal data, qint32 index)
{
    qreal baseY = globalUserVariable->gRefLevel + globalUserVariable->gRefOffset;
    qreal BottomY = baseY - globalUserVariable->gScaleDiv * 10;
    if(data < BottomY)
    {
        data = BottomY;
    }
    fmtAmplitude[index] = data;
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-24
*/
qreal RtSa_Interface::getCurFmtAmptData(qint32 index)
{
    return fmtAmplitude[index];
}

void RtSa_Interface::ReSetAllFmtData()
{
    qreal tempFreqData[RTSA_NUM_SWEEP_POINT];
    qreal tempAmptData[RTSA_NUM_SWEEP_POINT];
    memset(tempFreqData,0,sizeof(tempFreqData));
    memset(tempAmptData,0,sizeof(tempAmptData));

    memcpy(tempFreqData,fmtFreq,RTSA_NUM_SWEEP_POINT*sizeof(qreal));
    memcpy(tempAmptData,fmtAmplitude,RTSA_NUM_SWEEP_POINT*sizeof(qreal));

    qsort(&tempFreqData, mFmtDataTotalNum, sizeof(tempFreqData[0]), compare);
    for(qint32 j = 0; j < mFmtDataTotalNum; j ++)
    {
//        fmtFreq[j] = tempFreqData[j];
        for(qint32 i = 0; i < RTSA_NUM_SWEEP_POINT; i++)
        {
            if((tempFreqData[j] - fmtFreq[i] <= RTSA_ESP_ZERO) && (tempFreqData[j] - fmtFreq[i] >= -RTSA_ESP_ZERO))
            {
                fmtAmplitude[j] = tempAmptData[i];
                break;
            }
        }
    }

    setFmtFreqData(tempFreqData,mFmtDataTotalNum);
    setFmtAmptData(fmtAmplitude,mFmtDataTotalNum);
}

bool RtSa_Interface::isFreqInFmtArray(qreal freq)
{
    bool isTrue = false;
    qint32 iBowIndex = 0,iHighIndex = 0;
    for(qint32 i = 0;i < RTSA_NUM_SWEEP_POINT; i++)
    {
        if(freq <= fmtFreq[i])
        {
            iBowIndex = i;
            break;
        }
    }

    for(qint32 j = 0;j < mFmtDataTotalNum; j++)
    {
        if(freq >= fmtFreq[j])
        {
            iHighIndex = j;
//            break;
        }
    }
    if(iHighIndex == iBowIndex)
    {
        if((freq - fmtFreq[iHighIndex] <= RTSA_ESP_ZERO) && (freq - fmtFreq[iHighIndex] >= -RTSA_ESP_ZERO))
        {
            isTrue = true;
        }
        else
        {
            isTrue = false;
        }
    }
    else
    {
        isTrue = false;
    }
    return isTrue;
}
/**
 * @brief update render trace data
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::updateTraceData(qreal *pTraceData, qint32 TraceNum)
{
    pTrace.updateTraceData(pTraceData,TraceNum);
    return;
}

void RtSa_Interface::updateDpxData(quint32 *pTraceData, qint32 TraceNum)
{
    pTrace.updateDpxData(pTraceData,TraceNum);
    return;
}
/**
 * @brief select current bieview
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setCurBitView(qint32 index)
{
    setcurrentview(index);
    return;
}
/**
 * @brief update data to bitview
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::updateGeneralDataToBitview(qint32 datatype)
{
    switch (datatype) {
    case RTSA_FREQ_INFO:
        for(qint32 i=0;i<RTSA_BITVIEWNUM;i++)
        {
            mBitView[i]->setFreqOffset(globalUserVariable->gfreqOffset);
            mBitView[i]->setFreqAttribute(BIT_START_FREQ,globalUserVariable->gStartFreq);
            mBitView[i]->setFreqAttribute(BIT_STOP_FREQ,globalUserVariable->gStopFreq);
            mBitView[i]->setFreqAttribute(BIT_CENTER_FREQ,globalUserVariable->gCenterFreq);
            mBitView[i]->setFreqAttribute(BIT_SPAN_FREQ,globalUserVariable->gSpanFreq);
            mBitView[i]->showBottomWordsMsg(bitviewbottomdisplay);
            mBitView[i]->markerUpdateByFreq();
            mBitView[i]->refleshdisplay();
        }
        break;
    case RTSA_RBW_INFO:
        for(qint32 i=0;i<RTSA_BITVIEWNUM;i++)
        {
            mBitView[i]->setFreqAttribute(BIT_RBW_FREQ,globalUserVariable->gRbw);
            mBitView[i]->showBottomWordsMsg(bitviewbottomdisplay);
            mBitView[i]->refleshdisplay();
        }
        break;
    case RTSA_REF_LVL:
        for(qint32 i=0;i<RTSA_BITVIEWNUM;i++)
        {
//            mBitView[i]->setAmptdUnit(globalUserVariable->gAmptdUnit);
            mBitView[i]->showTopWordsMsg(BV_TOP_APMTINFO);
            //Tony 1022 & 1024
            mBitView[i]->setAmptdAttribute(BIT_AMPTD_REF,globalUserVariable->gRefLevel /*+ globalUserVariable->gRefOffset*/);
//            globalUserVariable->gRefOffset = mBitView[i]->getAmptdAttribute(BIT_AMPTD_OFFSET);
            mBitView[i]->setAmptdAttribute(BIT_AMPTD_OFFSET,globalUserVariable->gRefOffset);
            mBitView[i]->showTopWordsMsg(bitviewtopdisplay);
            mBitView[i]->refleshdisplay();
        }
        break;
    case RTSA_SYS_INFO:
        for(qint32 i=0;i<RTSA_BITVIEWNUM;i++)
        {
            mBitView[i]->setSystemAttribute(RUNNINGSTATE,globalUserVariable->gSweepType);
            mBitView[i]->refleshdisplay();
        }
        break;
    case RTSA_ACQ_INFO:
        for(qint32 i=0;i<RTSA_BITVIEWNUM;i++)
        {
            mBitView[i]->setAcqTime(globalUserVariable->gAcqTime);
            mBitView[i]->showBottomWordsMsg(bitviewbottomdisplay);
            mBitView[i]->refleshdisplay();
        }
        break;
    case RTSA_FREQ_OFFSET:
        for(qint32 i=0;i<RTSA_BITVIEWNUM;i++)
        {
            mBitView[i]->setFreqOffset(globalUserVariable->gfreqOffset);
//            mBitView[i]->setFreqAttribute(BIT_START_FREQ,globalUserVariable->gStartFreq);
//            mBitView[i]->setFreqAttribute(BIT_STOP_FREQ,globalUserVariable->gStopFreq);
//            mBitView[i]->setFreqAttribute(BIT_CENTER_FREQ,globalUserVariable->gCenterFreq);
//            mBitView[i]->setFreqAttribute(BIT_SPAN_FREQ,globalUserVariable->gSpanFreq);
            mBitView[i]->showBottomWordsMsg(bitviewbottomdisplay);
            mBitView[i]->markerUpdateByFreq();
            mBitView[i]->refleshdisplay();
        }
        break;
    case RTSA_REF_OFFSET:
        for(qint32 i=0;i<RTSA_BITVIEWNUM;i++)
        {
//            mBitView[i]->setAmptdUnit(globalUserVariable->gAmptdUnit);
//            mBitView[i]->showTopWordsMsg(BV_TOP_APMTINFO);
            mBitView[i]->setAmptdAttribute(BIT_AMPTD_OFFSET,globalUserVariable->gRefOffset);
            mBitView[i]->showTopWordsMsg(bitviewtopdisplay);
            mBitView[i]->refleshdisplay();
        }
        break;
    default:
        break;
    }
}
/**
 * @brief update data from bitview
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::updateDateFromBitview()
{
    globalUserVariable->gAmptdUnit = mBitView[curwindowindex]->getAmptUnit();
    globalUserVariable->gRefOffset = mBitView[curwindowindex]->getAmptdAttribute(BIT_AMPTD_OFFSET);
    globalUserVariable->gScaleDiv  = mBitView[curwindowindex]->getAmptdAttribute(BIT_AMPTD_DIV);

//    pLimit.setCurLimit(mBitView[curwindowindex]->getLimitAttribute(BIT_LIMIT_INDEX));
//    pLimit.setLimitTestOn(mBitView[curwindowindex]->getLimitAttribute(BIT_LIMIT_TEST));
//    for(int i=0;i<BIT_LIMIT_TOTAL_CNT;i++)
//    {
//        pLimit.setCurLimitOn(i,mBitView[curwindowindex]->getLimitAttribute(BIT_LIMIT_VIEW,i));
//        pLimit.setMarginOn(i,mBitView[curwindowindex]->getLimitAttribute(BIT_LIMIT_MARGIN,i));
//        pLimit.setMargin(i,mBitView[curwindowindex]->getLimitAttributeEX(BIT_LIMIT_MARGIN_VALUE,i));
//        pLimit.setLimitType(i,mBitView[curwindowindex]->getLimitAttribute(BIT_LIMIT_TYPE,i));
//    }

    pTrace.setCurTrace(mBitView[curwindowindex]->getTraceAttribute(0,BIT_TRACE_INDEX));
//    for(int i=0;i<SUPPORTTRACENUM;i++)
//    {
//        pTrace.setTraceType(i,mBitView[curwindowindex]->getTraceAttribute(i,BIT_TRACE_TYPE_ATTR));
//        pTrace.setAvgOn(i,mBitView[curwindowindex]->getTraceAttribute(i,BIT_AVAG_ATTR));
//        pTrace.setAvgNum(i,mBitView[curwindowindex]->getTraceAttribute(i,BIT_AVAG_NUM_ATTR));
//    }
//    pMarker.setCurMarkerID(mBitView[curwindowindex]->getMarkerAttribute(BIT_MARKER_INDEX));
//    for(int i=0;i<BIT_LIMIT_TOTAL_CNT;i++)
//    {
//        pMarker.setMarkerType(i,mBitView[curwindowindex]->getMarkerAttribute(BIT_MARKER_DISPLAY,i));
//        pMarker.setMarkerOn(i,mBitView[curwindowindex]->getMarkerAttribute(BIT_MARKER_VISIABLE,i));
//        pMarker.setMarkerNoiseOn(i,mBitView[curwindowindex]->getMarkerAttribute(BIT_MARKER_NOISE,i));
//    }
//    pMarker.setMarkerDisplay(mBitView[curwindowindex]->getMarkerAttribute(BIT_MARKER_DISPLAY));
    return;
}
/**
 * @brief RtSa_Interface::setMarkerToPeak
 */
void RtSa_Interface::setMarkerToPeak()
{
//    qint32 markerID = getCurMarkerID();
//    setMarkerOn(markerID,true);
    pMarker.setMarkerToPeak();
    emit BitViewMakerMoved(true);
//    emit BitViewMakerDraw(markerID,true);
    return;
}
/**
 * @brief RtSa_Interface::setMarkerToNextPeak
 */
void RtSa_Interface::setMarkerToNextPeak()
{
    pMarker.setMarkerToNextPeak();
    return;
}
/**
 * @brief RtSa_Interface::setMarkerToLeftPeak
 */
void RtSa_Interface::setMarkerToLeftPeak()
{
    pMarker.setMarkerToLeftPeak();
    return;
}
/**
 * @brief RtSa_Interface::setMarkerToRightPeak
 */
void RtSa_Interface::setMarkerToRightPeak()
{
    pMarker.setMarkerToRightPeak();
    return;
}
void RtSa_Interface::setMarkerToMin()
{
    pMarker.setMarkerToMin();
    return;
}

/**
 * @brief refresh bitview bottom message
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::showBitViewBottomMsg(qint32 bottomDisplay)
{
    for(int i=0;i< RTSA_BITVIEWNUM;i++)
    {
        mBitView[i]->showBottomWordsMsg(bottomDisplay);
        mBitView[i]->refleshdisplay();
    }
    return;
}
/**
 * @brief select current bieview
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::setcurrentview(quint32 index)
{
    emit ParentFocus();
    if(globalUserVariable->gLocal == RTSA_REMOTE)
    {
        return;
    }
    if(curwindowindex == (qint32)index || wintotalnum < 1)
        return;

    for(qint32 i = 0; i < RTSA_BITVIEWNUM; i++)
    {
        mBitView[i]->getclickSource(index);
        mBitView[i]->HideBoardLine();
    }

    //Tony 1010 optimization
    mBitView[curwindowindex]->getclickSource(index);
    mBitView[curwindowindex]->showBoarderLine();
    curwindowindex=index;
    mBitView[curwindowindex]->getclickSource(index);
    mBitView[curwindowindex]->showBoarderLine();

    pLimit.setCurBitView(mBitView[curwindowindex]);
    pMarker.setCurBitView(mBitView[curwindowindex]);
    pTrace.setCurBitView(mBitView[curwindowindex]);


    updateDateFromBitview();

    //Albert 03/09 when single sweep, should refresh bitview display.
    for(int i=0;i< RTSA_BITVIEWNUM;i++)
    {
        mBitView[i]->refleshdisplay();
    }

    emit BitViewChanged(curwindowindex);
    emit RedrawInfoShow(LABEL_TRACE_STATUS);
    emit RedrawInfoShow(LABEL_AVERAGE);
    return;
}
/**
 * @brief marker change slot
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::markerchange(qint32 index)
{
//    if(pMarker.getCurMarkerID() == index)
//    {
//        return;
//    }
    setCurMarkerID(index);
    return;
}
/**
 * @brief marker move slot
 * @note
 * @author Albert
 * @since {2018-12-17}
*/
void RtSa_Interface::markerMove(bool index)
{
    if(index)
    {
        qint32 curMarkerID = getCurMarkerID();
        emit BitViewMakerMoved(true);
        emit MarkerPosChanged(true);
        emit BitViewMakerDraw(curMarkerID,true);
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-28
*/
void RtSa_Interface::changeBitViewSize(bool isDoubleClicked)
{
    qint32 bitViewIndex = curwindowindex;
    for(int i=0;i<RTSA_BITVIEWNUM;i++)
    {
        mBitView[i]->hide();
    }
    mIsCurBitViewSizeChange = isDoubleClicked;
    if(mIsCurBitViewSizeChange)
    {
    }
    else
    {
        switch (mDisplayMode) {
        case RTSA_SPECTRUM_SPECTROGRAM:
            mBitView[0]->show();
            mBitView[1]->show();
            break;
        case RTSA_SPECTROGRAM:
            mBitView[0]->show();
            break;
        case RTSA_DENSITY:
            mBitView[0]->show();
            mBitView[1]->show();
#ifdef BITVIEW_TIME_MARKER
            if(curwindowindex == 0)
            {
                mBitView[1]->refreshSepectrogramRect();
            }
#endif
            break;
        default:
            break;
        }
    }
    if(mIsZoomIn)
    {
        setZoomIn();
    }
    else
    {
        setZoomOut();
    }
    return;
}
/**
 * @brief RtSa_Interface::setZoomFlag
 * @param isZoomIn
 */
void RtSa_Interface::setZoomFlag(bool isZoomIn)
{
    mIsZoomIn = isZoomIn;
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-03-27
*/
void RtSa_Interface::setDragFlag(bool dragFlag)
{
    mDragFlag = dragFlag;
    if(mIsZoomIn)
    {
       setZoomIn();
    }
    else
    {
        setZoomOut();
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-07-29
*/
bool RtSa_Interface::getDragFlag()
{
    return mDragFlag;
}
/**
 * @brief RtSa_Interface::refreshMainDisplay
 */
void RtSa_Interface::refreshMainDisplay()
{
    //when change param in single swp, trace data should set to the down below
    if(IsSingleSweep() && !mSingleFinished)
    {
        pTrace.updateTraceData(mLowData,RTSA_NUM_SWEEP_POINT);
        pTrace.draw();
    }
    mSingleFinished = false;
    return;
}
/**
* @brief set shift key down flag
* @param[in] isEnable
* @Author Albert
* @date 2019-03-27
*/
void RtSa_Interface::setShiftKeyEnable(bool isEnable)
{
    mIsShiftKeyEnable = isEnable;
    return;
}
/**
* @brief if shift key down flag
* @param none
* @Author Albert
* @date 2019-03-27
*/
bool RtSa_Interface::isShiftKeyEnable()
{
    return mIsShiftKeyEnable;
}
/**
* @brief set channel std index
* @param[in] standard index
* @Author Albert
* @date 2019-03-27
*/
void RtSa_Interface::setCHStandard(qint32 index)
{
//    if(index == globalUserVariable->gTecIndex)
//        return;
    qreal newCerFreq;
    if(index < 0)
    {
        globalUserVariable->gTecIndex = -1;
        emit RedrawInfoShow(LABEL_CHANNEL);
        emit RedrawInfoShow(LABEL_SIGNAL_STANDARD);
        return;
    }
    globalUserVariable->gTecIndex = index;
    globalUserVariable->getBandInfo(index);
//    globalUserVariable->adjustCHStandarByCerFreq(globalUserVariable->gCenterFreq);
    newCerFreq = globalUserVariable->adjustFreqByCHStandar();
//    globalUserVariable->adjustCHStandarByCerFreq(newCerFreq);
    setCenterFreq(newCerFreq);
    emit RedrawInfoShow(LABEL_CHANNEL);
    emit RedrawInfoShow(LABEL_SIGNAL_STANDARD);
    return;
}
/**
* @brief get channel std index
* @param none
* @Author Albert
* @date 2019-03-27
*/
qint32 RtSa_Interface::getCHStandard()
{
    if(globalUserVariable->gTecIndex<0)
    {
        return -1;
    }
    qint32 index = mRTSA_ChStand[globalUserVariable->gTecIndex].index;
    return index;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-24
*/
void RtSa_Interface::setBandIndex(qint32 bandIndex)
{
    if(bandIndex < 0)
        bandIndex = 0;
    else if(bandIndex >= globalUserVariable->gCHName->size())
    {
        bandIndex = globalUserVariable->gCHName->size() - 1;
    }
    globalUserVariable->gCHIndex = bandIndex;

    globalUserVariable->getBandInfo(globalUserVariable->gTecIndex);
//    globalUserVariable->adjustCHStandarByCerFreq(globalUserVariable->gCenterFreq);
    qreal newCerFreq = globalUserVariable->adjustFreqByCHStandar();
//    globalUserVariable->adjustCHStandarByCerFreq(newCerFreq);
    setCenterFreq(newCerFreq);
    emit RedrawInfoShow(LABEL_CHANNEL);
    emit RedrawInfoShow(LABEL_SIGNAL_STANDARD);
    return;
}

qint32 RtSa_Interface::getBandIndex()
{
    return globalUserVariable->gCHIndex;
}
/**
* @brief set channel std communicate direction
* @param[in] direction type
* @Author Albert
* @date 2019-03-27
*/
void RtSa_Interface::setCommuDirection(qint32 direction)
{
    if(globalUserVariable->gCommuDirection == direction)
        return;
    qreal newCerFreq = 0.;
    globalUserVariable->gCommuDirection = direction;
    newCerFreq = globalUserVariable->adjustFreqByCHStandar();
//    globalUserVariable->adjustCHStandarByCerFreq(newCerFreq);
    setCenterFreq(newCerFreq);
    return;
}
/**
* @brief get channel std communicate direction
* @param none
* @Author Albert
* @date 2019-03-20
*/
qint32 RtSa_Interface::getCommuDirection()
{
    return globalUserVariable->gCommuDirection;
}
/**
* @brief set channel number
* @param[in] channel number
* @Author Albert
* @date 2019-03-27
*/
void RtSa_Interface::setChannelNumber(qint32 number)
{
    if(number == globalUserVariable->gChannelNum)
        return;
    qreal min = 0;
    qreal max = 0;
    qreal centerFreq;
    if(globalUserVariable->gCommuDirection == RTSA_UPLINK)
    {
        max = globalUserVariable->gCHStandard->at(globalUserVariable->gCHIndex).Up.Max;
        min = globalUserVariable->gCHStandard->at(globalUserVariable->gCHIndex).Up.Min;
    }
    else
    {
        max = globalUserVariable->gCHStandard->at(globalUserVariable->gCHIndex).Down.Max;
        min = globalUserVariable->gCHStandard->at(globalUserVariable->gCHIndex).Down.Min;
    }
    if(number < min)
        number = min;
    else if(number > max)
        number = max;
    globalUserVariable->gChannelNum = number;
    //Center Freq need modify
    centerFreq = globalUserVariable->adjustFreqByCHNum(number);
    setCenterFreq(centerFreq);
    return ;
}
/**
* @brief get channel number
* @param none
* @Author Albert
* @date 2019-03-25
*/
qint32 RtSa_Interface::getChannelNumber()
{
    return globalUserVariable->gChannelNum;
}
/**
* @brief delete all limit
* @param none
* @Author Albert
* @date 2019-03-25
*/
void RtSa_Interface::DeleteAllLimit()
{
    for(qint32 i = 0; i < RTSA_BITVIEWNUM;i++)
    {
        mBitView[i]->setTableEdit(BIT_LIMIT_DELETE_LIMIT,0);
        pLimit.setCurBitView(mBitView[i]);
        for(qint32 j = 0 ; j < RTSA_LIMIT_TOTAL_CNT; j++)
        {
            pLimit.setLimitNum(j,0);
        }
//        mBitView[i]->setTableEdit(BIT_LIMIT_EDIT_VISIABLE,BIT_LIMIT_TABLE_EDIT_SHOW);
        mBitView[i]->refleshdisplay();
    }
    pLimit.setCurBitView(mBitView[curwindowindex]);
    return;
}

bool RtSa_Interface::isHaveLimitOn()
{
    return  pLimit.IsHaveLimitOn();
}

/**
* @brief getGlobalUserVariable
* @param none
* @Author Albert
* @date 2019-04-15
*/
RtSa_User_Variable* RtSa_Interface::getGlobalUserVariable()
{
    return globalUserVariable;
}
/**
* @brief BuildLimitFromTrace
* @param none
* @Author Albert
* @date 2019-04-15
*/
void RtSa_Interface::BuildLimitFromTrace()
{
    qreal freq[101] = {0};
    qreal ampt[101] = {0};
    qint32 traceID = getCurTrace();
    qint32 limitID = getCurLimit();
    qint32 freqstep  = (qint32)((globalUserVariable->gStopFreq - globalUserVariable->gStartFreq)/100);
    quint32 amptstep  = (quint32)((RTSA_NUM_SWEEP_POINT - 1)/100);
    qreal *trace = pTrace.GetTraceData(RTSA_NUM_SWEEP_POINT,traceID);

    freq[0] = getStartFreq()/RTSA_MHZ;
    ampt[0] = trace[0] + 10.0;

    for(qint32 i = 0 ; i < 100; i++)
    {
        freq[i] = (getStartFreq() + freqstep * i)/RTSA_MHZ;
        ampt[i] = getMaxTraceData(trace,amptstep * i,amptstep) + 10.0;
    }
    freq[100] = getStopFreq()/RTSA_MHZ;
    ampt[100] = trace[RTSA_NUM_SWEEP_POINT - 1] + 10.0;

    setCurLimit(limitID);
    setCurLimitOn(limitID,true);
    setLimitFreqData(freq,101,limitID);
    setLimitAmptData(ampt,101,limitID);
    return;
}
/**
* @brief getMaxTraceData
* @param 【IN】 pData，startIndex，nNum
* @Author Albert
* @date 2019-04-15
*/
qreal RtSa_Interface::getMaxTraceData(qreal *pData, qint32 startIndex, qint32 nNum)
{
    qreal maxValue = 0.0;
    if(startIndex < 0)
        startIndex = 0;
    maxValue = pData[startIndex];
    for(qint32 i = startIndex; i < startIndex + nNum; i++)
    {
        if(maxValue <= pData[i])
        {
            maxValue = pData[i];
        }
    }
    return maxValue;
}

//qreal RtSa_Interface::getLimitMaxTraceData(qreal *pData, qreal pMaxData, qint32 Index)
//{
//    qreal maxValue = 0.0;
////    if(pData < 0)
////        pData = 0;
////    maxValue = pMaxData;
////    for(qint32 i = pData; i < stopIndex; i++)
////    {
////        if(i == Index)
////        {
////            continue;
////        }
////        if(maxValue <= pData[i])
////        {
////            maxValue = pData[i];
////        }
////    }
//    return maxValue;
//}
/**
* @brief setGeneralDataToShm
* @param none
* @Author Albert
* @date 2019-04-15
*/
void RtSa_Interface::setGeneralDataToShm()
{
//    pSweepControl.setGeneralDataToShm();
//    pSweepControl.setGeneralDataToShm();
//    setCenterFreq(globalUserVariable->gCenterFreq);
//    setSpan(globalUserVariable->gSpanFreq);
//    setBWAuto(globalUserVariable->gAutoRbw);
//    setAttenVal(globalUserVariable->gAttenValue);
//    setAttenAuto(globalUserVariable->gAtten);
//    setAcqTime(globalUserVariable->gAcqTime);
//    setPersistenceTime(globalUserVariable->gPersistenceTime);
//    setFFTWindow(globalUserVariable->gFTTWindows);
    return;
}
/**
* @brief saveDisplayParam
* @param [in] display
* @Author Albert
* @date 2019-04-15
*/
void RtSa_Interface::saveDisplayParam(qint32 display)
{
    switch(display)
    {
    case RTSA_SPECTRUM_SPECTROGRAM:

        break;
    case RTSA_SPECTROGRAM:
        break;
    case RTSA_DENSITY:
        break;
    case RTSA_DENSITY_SPECTROGRAM:
        break;
    default:
        break;
    }
    return;
}
/**
* @brief  loadDisplayParam
* @param [in] display
* @Author Albert
* @date 2019-04-15
*/
void RtSa_Interface::loadDisplayParam(qint32 display)
{
    switch(display)
    {
    case RTSA_SPECTRUM_SPECTROGRAM:
        break;
    case RTSA_SPECTROGRAM:
        break;
    case RTSA_DENSITY:
        break;
    case RTSA_DENSITY_SPECTROGRAM:
        break;
    default:
        break;
    }
    return;
}
/**
* @brief  getCurBitviewType
* @param
* @Author Albert
* @date 2019-04-26
*/
qint32 RtSa_Interface::getCurBitviewType()
{
    qint32 type = RTSA_SPECTRUM_SPECTROGRAM;
    type = mBitView[curwindowindex]->getBitviewType();
    return type;
}
/**
* @brief SetCurLimitDataIndex
* @param limit edit cur pos
* @Author Albert
* @date 2019-05-13
*/
void RtSa_Interface::SetCurLimitDataIndex(qint32 curPos)
{
    qint32 curLimitID = getCurLimit();
    qint32 maxLimitIndex = getLimitDataNum(curLimitID);
    if(curPos < 0)
        curPos = 0;
    if(curPos > maxLimitIndex)
        curPos = maxLimitIndex - 1;
    mCurLimitDataPos = curPos;
    return;
}
/**
* @brief GetCurLimitDataIndex
* @param return cur select limit data index
* @Author Albert
* @date 2019-05-13
*/
qint32 RtSa_Interface::GetCurLimitDataIndex()
{
    return mCurLimitDataPos;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-13
*/
void RtSa_Interface::setLimitCurPointFreq(qreal pData, qint32 curPos, qint32 limitID)
{
    qreal freqMin = getStartFreq()/RTSA_MHZ;
    qreal freqMax = getStopFreq()/RTSA_MHZ;
    if(pData < freqMin)
        pData = freqMin;
    else if(pData > freqMax)
        pData = freqMax;
    pLimit.setCurLimitFreq(pData,curPos,limitID);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-05-13
*/
void RtSa_Interface::setLimitCurPointAmpt(qreal pData, qint32 curPos, qint32 limitID)
{
    if(pData < -170.0)
        pData = -170.0;
    else if(pData > 30)
        pData = 20.0;
    pLimit.setCurLimitAmpt(pData,curPos,limitID);
    return;
}
/**
* @brief getLimitCurPointFreq
* @param [curPos] cur limit select index, [limitID] cur limit index
* @Author Albert
* @date 2019-05-13
*/
qreal RtSa_Interface::getLimitCurPointFreq(qint32 curPos, qint32 limitID)
{
    qreal freq = 0.0;
    freq = pLimit.getCurLimitFreq(curPos,limitID);
    return freq;
}
/**
* @brief getLimitCurPointAmpt
* @param [curPos] cur limit select index, [limitID] cur limit index
* @Author Albert
* @date 2019-05-13
*/
qreal RtSa_Interface::getLimitCurPointAmpt(qint32 curPos, qint32 limitID)
{
    qreal ampt = 0.0;
    ampt = pLimit.getCurLimitAmpt(curPos,limitID);
    return ampt;
}

void RtSa_Interface::setcurFreq(qreal freq)
{
    mCurFreq = freq;
    return;
}

void RtSa_Interface::setcurAmpt(qreal ampt)
{
    mCurAmpt = ampt;
    return;
}

qreal RtSa_Interface::getcurFreq()
{
    return mCurFreq;
}

qreal RtSa_Interface::getcurAmpt()
{
    return mCurAmpt;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-14
*/
void RtSa_Interface::PltCurAnaMode(qint32 imod)
{
    globalUserVariable->startMode = imod;
    return;
}
/**
* @brief PltSaveConditions
* @param itype file type 0 means default.cond 1 means last.cond 2 means user.cond
* @Author Albert
* @date 2019-05-21
*/
qint32 RtSa_Interface::PltSaveConditions(qint32 itype)
{
    qint32 ret = -1;
    switch (itype) {
    case STATE_DEFAULT_FILE:
        savePresState();
        initDefaultParam(mStateParam);
        ret = saveState(RTSA_DEFAULT_COND);
        break;
    case STATE_LAST_FILE:
        savePresState();
        initStateParam(mStateParam);
        ret = saveState(RTSA_LAST_COND);
        break;
    case STATE_USER_FILE:
        savePresState();
        initStateParam(mStateParam);
        ret = saveState(RTSA_USER_COND);
        break;
    default:
        break;
    }
    return ret;
}
/**
* @brief PltLoadConditions
* @param itype file type 0 means default.cond 1 means last.cond 2 means user.cond
* @Author Albert
* @date 2019-05-21
*/
qint32 RtSa_Interface::PltLoadConditions(qint32 itype)
{
    qint32 ret = -1;
    switch (itype) {
    case STATE_DEFAULT_FILE:
        loadPresState();
        ret = loadState(RTSA_DEFAULT_COND);
        if(ret < 0)
        {
            setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,RTSA_APP_FILE_DEFAULT);
            errorOutput();
        }
        break;
    case STATE_LAST_FILE:
        loadPresState();
        ret = loadState(RTSA_LAST_COND);
        if(ret < 0)
        {
            setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,RTSA_APP_FILE_LAST);
            errorOutput();
        }
        break;
    case STATE_USER_FILE:
        loadPresState();
        ret = loadState(RTSA_USER_COND);
        if(ret < 0)
        {
            setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,RTSA_APP_FILE_USER);
            errorOutput();
        }
        break;
    default:
        break;
    }
//    globalUserVariable->gfileType = itype;
    return ret;
}

qint32 RtSa_Interface::PltSavePres(qint32 itype)
{
    qint32 iback = -1;
    globalUserVariable->gfileType = itype;
    iback = savePresState();
    return iback;
}

void RtSa_Interface::initDefaultParam(_RTSA_FILE_SAVE_LOAD_VARIABLE_ &stateParam)
{
    stateParam.gConfig_Display.displayMode = RTSA_SPECTRUM_SPECTROGRAM;
    stateParam.gConfig_Display.bitviewStatus[0] = BIT_SPECTRUM;
    stateParam.gConfig_Display.bitviewStatus[1] = BIT_SPECTROGRAM;
    stateParam.gConfig_Display.bitviewStatus[2] = BIT_NONE;
    stateParam.gConfig_Display.bitviewStatus[3] = BIT_NONE;

    stateParam.gConfig_Display.curWindowIndex = 0;
    //Freq
    stateParam.gConfig_FreqSpan.gCenterFreq = 5050000000LL;
    stateParam.gConfig_FreqSpan.gStartFreq = 5000000000LL;
    stateParam.gConfig_FreqSpan.gStopFreq = 5100000000LL;
    stateParam.gConfig_FreqSpan.gSpanFreq = 100000000LL;
    stateParam.gConfig_FreqSpan.gStepFreq = 1000000LL;
    stateParam.gConfig_FreqSpan.gOffsetFreq = 0;
    stateParam.gConfig_FreqSpan.channelStd = RTSA_CDMA - 1;
    stateParam.gConfig_FreqSpan.channelSelID = 0;
    stateParam.gConfig_FreqSpan.channelNumber = 0;
    stateParam.gConfig_FreqSpan.channelStep = mRTSA_ChStand[RTSA_CDMA].ChStep;
    stateParam.gConfig_FreqSpan.channelType = RTSA_UPLINK;

    //amplitude
    stateParam.gConfig_Amplitude.refLevel = -10.0;
    stateParam.gConfig_Amplitude.attenAuto = RTSA_AUTO;
    stateParam.gConfig_Amplitude.attenVal = 0.0;
    for(qint32 i = 0 ; i < RTSA_BITVIEWNUM ; i++)
    {
        stateParam.gConfig_Amplitude.scaleDiv[i] = 10;
        stateParam.gConfig_Amplitude.refOffset[i] = 0;
        stateParam.gConfig_Amplitude.units[i] = RTSA_DBM;
    }
    stateParam.gConfig_Amplitude.preAmpStatus = RTSA_OFF;

    //sweep
    stateParam.gConfig_Sweep.sweepType = RTSA_CONT;
    stateParam.gConfig_Sweep.autoAcqtime = RTSA_AUTO;
    stateParam.gConfig_Sweep.acqTimeVal = RTSA_ACQ_DEFAULT_TIME;
    stateParam.gConfig_Sweep.autoPersistence = RTSA_FINITE;
    stateParam.gConfig_Sweep.persistenceVal = RTSA_PERSISTENCE_TIME;
    stateParam.gConfig_Sweep.highDensity = 100;
    stateParam.gConfig_Sweep.lowDensity = 0;
    stateParam.gConfig_Sweep.curveNum = 0;

    //BW
    stateParam.gConfig_BW.autoRbw = RTSA_ON;
    stateParam.gConfig_BW.rbw = RTSA_RbwManualList[0][0][6];
    stateParam.gConfig_BW.rbwIndex = RTSA_RBW5;
    stateParam.gConfig_BW.fftFilter = RTSA_KAISER;

    //Trigger
    stateParam.gConfig_Trigger.triggerType = RTSA_TRIGGER_FREE_RUN;
    //Video trigger
    stateParam.gConfig_Trigger.triggerVideoSlope = 0;
    stateParam.gConfig_Trigger.triggerVideoLevel = -20.0;
    stateParam.gConfig_Trigger.triggerVideoDelayStatus = 0;
    stateParam.gConfig_Trigger.triggerVideoDelay = 0;

    //extern trigger
    stateParam.gConfig_Trigger.triggerExternSlope = 0;
    stateParam.gConfig_Trigger.triggerExternLevel = -20.0;
    stateParam.gConfig_Trigger.triggerExternDelayStatus = 0;
    stateParam.gConfig_Trigger.triggerExternDelay = 0;

    //period
    stateParam.gConfig_Trigger.triggerPeriodDelay = 0;
    stateParam.gConfig_Trigger.triggerPeriodDelayStatus = 0;
    stateParam.gConfig_Trigger.triggerPeriodTime = RTSA_HOLDOFF_TIME_MIN;

    //RF Burst
    stateParam.gConfig_Trigger.triggerRFSlope = 0;
    stateParam.gConfig_Trigger.triggerRFLevel = -20.0;
    stateParam.gConfig_Trigger.triggerRFDelayStatus = 0;
    stateParam.gConfig_Trigger.triggerRFDelay = 0;


    stateParam.gConfig_Trigger.triggerVideoHoldOff = RTSA_HOLDOFF_TIME_MIN;
    stateParam.gConfig_Trigger.triggerRFBurstHoldOff = RTSA_HOLDOFF_TIME_MIN;
    stateParam.gConfig_Trigger.triggerExternHoldOff = RTSA_HOLDOFF_TIME_MIN;
    stateParam.gConfig_Trigger.triggerFMTHoldOff = RTSA_HOLDOFF_TIME_MIN;

//    stateParam.gConfig_Trigger.triggerSlope = 0;
//    stateParam.gConfig_Trigger.maskType = globalUserVariable->gMaskType;
//    stateParam.gConfig_Trigger.triggerCriteria = globalUserVariable->gMaskType;

    stateParam.gConfig_Trigger.fmtnumber = 0;
    for(qint32 i = 0; i < stateParam.gConfig_Trigger.fmtnumber; i++)
    {
        stateParam.gConfig_Trigger.fmtFreq[i] = 0;
        stateParam.gConfig_Trigger.fmtAmpt[i] = 0;
    }

    //Trace
    for(qint32 j = 0; j < RTSA_BITVIEWNUM; j++)
    {
        stateParam.gConfig_Trace.curTraceID[j] = RTSA_TR1;
        for(qint32 i = 0; i < RTSA_NUM_TRACE; i++)
        {
            stateParam.gConfig_Trace.Rtsa_Config_Trace[j][i].traceType = RTSA_TRACE_OFF;
            stateParam.gConfig_Trace.Rtsa_Config_Trace[j][i].averageOn = RTSA_OFF;
            stateParam.gConfig_Trace.Rtsa_Config_Trace[j][i].averageCount = 10;
        }
        stateParam.gConfig_Trace.Rtsa_Config_Trace[j][0].traceType = RTSA_CLEAR_WRITE;
    }
    stateParam.gConfig_Trace.detectorType = RTSA_DEC_SAMPLE;

    stateParam.gConfig_Trace.Rtsa_Config_Trace[0][RTSA_TR1].traceType = RTSA_CLEAR_WRITE;
    //Marker
    for(qint32 j = 0; j < RTSA_BITVIEWNUM; j++)
    {
        stateParam.gConfig_Marker[j].curmarkerID = RTSA_M1;
        stateParam.gConfig_Marker[j].markerPeakTraceOn = RTSA_OFF;
        for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
        {
            stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].markerView = RTSA_OFF;
            stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].markerType = RTSA_REF;
            stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].markerNoiseOn = RTSA_OFF;
            stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].gMarkerRefFreq = stateParam.gConfig_FreqSpan.gCenterFreq;
            stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].gMarkerRefAmpt = 0;
            stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].gMarkerNormalPosY = 0;
        }

    }

    //Limit
    for(qint32 j = 0; j < RTSA_BITVIEWNUM; j++)
    {
        stateParam.gConfig_Limit[j].limitID = RTSA_LIMIT1;
        stateParam.gConfig_Limit[j].limitTest = RTSA_OFF;
        for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
        {
            stateParam.gConfig_Limit[j].limitOn[i] = RTSA_LIMIT_OFF;
            stateParam.gConfig_Limit[j].limitEdgeOn[i] = RTSA_OFF;
            stateParam.gConfig_Limit[j].limitEdgeVal[i] = 0;
            stateParam.gConfig_Limit[j].limitType[i] = RTSA_UPPER;
            stateParam.gConfig_Limit[j].limitEditNum[i] = 0;
            stateParam.gConfig_Limit[j].limitCurEditIndex[i] = 0;
        }
    }
    return;
}
/**
* @brief initStateParam
* @param init state struct
* @Author Albert
* @date 2019-05-22
*/
void RtSa_Interface::initStateParam(_RTSA_FILE_SAVE_LOAD_VARIABLE_ &stateParam)
{
    //Albert 19/06/03  when save state, should consider every bitview

    stateParam.gConfig_Display.displayMode = getDisplay();
    for(qint32 i = 0;i < RTSA_BITVIEWNUM; i++)
    {
        stateParam.gConfig_Display.bitviewStatus[i] = mBitView[i]->getBitviewType();
    }
    stateParam.gConfig_Display.curWindowIndex = curwindowindex;
    //Freq
    stateParam.gConfig_FreqSpan.gCenterFreq = globalUserVariable->gCenterFreq;
    stateParam.gConfig_FreqSpan.gStartFreq = globalUserVariable->gStartFreq;
    stateParam.gConfig_FreqSpan.gStopFreq = globalUserVariable->gStopFreq;
    stateParam.gConfig_FreqSpan.gSpanFreq = globalUserVariable->gSpanFreq;
    stateParam.gConfig_FreqSpan.gStepFreq = globalUserVariable->gStepFreq;
    stateParam.gConfig_FreqSpan.gOffsetFreq = globalUserVariable->gfreqOffset;
    stateParam.gConfig_FreqSpan.channelStd = globalUserVariable->gTecIndex;
    stateParam.gConfig_FreqSpan.channelSelID = globalUserVariable->gCHIndex;
    stateParam.gConfig_FreqSpan.channelNumber = globalUserVariable->gChannelNum;
    stateParam.gConfig_FreqSpan.channelStep = globalUserVariable->gChannelStep;
    stateParam.gConfig_FreqSpan.channelType = globalUserVariable->gCommuDirection;

    //amplitude
    stateParam.gConfig_Amplitude.refLevel = globalUserVariable->gRefLevel;
    stateParam.gConfig_Amplitude.attenAuto = globalUserVariable->gAtten;
    stateParam.gConfig_Amplitude.attenVal = globalUserVariable->gAttenValue;
    for(qint32 i = 0 ;i < RTSA_BITVIEWNUM; i++)
    {
        stateParam.gConfig_Amplitude.scaleDiv[i] = mBitView[i]->getAmptdAttribute(BIT_AMPTD_DIV);//globalUserVariable->gScaleDiv;
        stateParam.gConfig_Amplitude.refOffset[i] = mBitView[i]->getAmptdAttribute(BIT_AMPTD_OFFSET);//globalUserVariable->gRefOffset;
        stateParam.gConfig_Amplitude.units[i] = mBitView[i]->getAmptUnit();//globalUserVariable->gAmptdUnit;
    }
    stateParam.gConfig_Amplitude.preAmpStatus = globalUserVariable->gPreamp;

    //sweep
    stateParam.gConfig_Sweep.sweepType = globalUserVariable->gSweepType;
    stateParam.gConfig_Sweep.autoAcqtime = globalUserVariable->gAutoAcqTime;
    stateParam.gConfig_Sweep.acqTimeVal = globalUserVariable->gAcqTime;
    stateParam.gConfig_Sweep.autoPersistence = globalUserVariable->gAutoPersistenceTime;
    stateParam.gConfig_Sweep.persistenceVal = globalUserVariable->gPersistenceTime;
    stateParam.gConfig_Sweep.highDensity = globalUserVariable->gHighestDensity;
    stateParam.gConfig_Sweep.lowDensity = globalUserVariable->gLowestDensity;
    stateParam.gConfig_Sweep.curveNum = globalUserVariable->gCurve;

    //BW
    stateParam.gConfig_BW.autoRbw = globalUserVariable->gAutoRbw;
    stateParam.gConfig_BW.rbw = globalUserVariable->gRbw;
    stateParam.gConfig_BW.rbwIndex = globalUserVariable->gRbwIndex;
    stateParam.gConfig_BW.fftFilter = globalUserVariable->gFTTWindows;

    //Trigger
    stateParam.gConfig_Trigger.triggerType = globalUserVariable->gTriggerMode;
    //Video trigger
    stateParam.gConfig_Trigger.triggerVideoSlope = globalUserVariable->gTriggerVideoSlope;
    stateParam.gConfig_Trigger.triggerVideoLevel = globalUserVariable->gVideoTrigLevel;
    stateParam.gConfig_Trigger.triggerVideoDelayStatus = globalUserVariable->gVideoTrigDelayStatus;
    stateParam.gConfig_Trigger.triggerVideoDelay = globalUserVariable->gVideoTrigDelay;

    //extern trigger
    stateParam.gConfig_Trigger.triggerExternSlope = globalUserVariable->gTriggerExternSlope;
    stateParam.gConfig_Trigger.triggerExternLevel = globalUserVariable->gExternTrigLevel;
    stateParam.gConfig_Trigger.triggerExternDelayStatus = globalUserVariable->gExternTrigDelayStatus;
    stateParam.gConfig_Trigger.triggerExternDelay = globalUserVariable->gExternTrigDelay;

    //period
    stateParam.gConfig_Trigger.triggerPeriodDelay =globalUserVariable->gPeriodTrigDelay;
    stateParam.gConfig_Trigger.triggerPeriodDelayStatus = globalUserVariable->gPeriodTrigDelayStatus;
    stateParam.gConfig_Trigger.triggerPeriodTime = globalUserVariable->gPeriodTrigTime;

    //RF Burst
    stateParam.gConfig_Trigger.triggerRFSlope = globalUserVariable->gTriggerRFBurstSlope;
    stateParam.gConfig_Trigger.triggerRFLevel = globalUserVariable->gRFBurstTrigLevel;
    stateParam.gConfig_Trigger.triggerRFDelayStatus = globalUserVariable->gRFBurstTrigDelayStatus;
    stateParam.gConfig_Trigger.triggerRFDelay = globalUserVariable->gRFBurstTrigDelay;

    stateParam.gConfig_Trigger.triggerVideoHoldOff = globalUserVariable->gVideoHoldOff;
    stateParam.gConfig_Trigger.triggerRFBurstHoldOff = globalUserVariable->gRFBurstHoldOff;
    stateParam.gConfig_Trigger.triggerExternHoldOff = globalUserVariable->gExternHoldOff;
    stateParam.gConfig_Trigger.triggerFMTHoldOff = globalUserVariable->gFMTHoldOff;

    stateParam.gConfig_Trigger.triggerSlope = globalUserVariable->gTriggerSlope;
    stateParam.gConfig_Trigger.maskType = globalUserVariable->gMaskType;
    stateParam.gConfig_Trigger.triggerCriteria = globalUserVariable->gMaskType;

    stateParam.gConfig_Trigger.fmtnumber = mFmtDataTotalNum;
    for(qint32 i = 0; i < stateParam.gConfig_Trigger.fmtnumber; i++)
    {
        stateParam.gConfig_Trigger.fmtFreq[i] = fmtFreq[i];
        stateParam.gConfig_Trigger.fmtAmpt[i] = fmtAmplitude[i];
    }

    //Trace
    for(qint32 j = 0; j < RTSA_BITVIEWNUM; j++)
    {
        stateParam.gConfig_Trace.curTraceID[j] = mBitView[j]->getTraceAttribute(0,BIT_TRACE_INDEX);// getCurTrace();
        for(qint32 i = 0; i < RTSA_NUM_TRACE; i++)
        {
            stateParam.gConfig_Trace.Rtsa_Config_Trace[j][i].traceType = mBitView[j]->getTraceAttribute(i,BIT_TRACE_TYPE_ATTR);// getTraceType(i);
            stateParam.gConfig_Trace.Rtsa_Config_Trace[j][i].averageOn = mBitView[j]->getTraceAttribute(i,BIT_AVAG_ATTR);//IsAvgOn(i);
            stateParam.gConfig_Trace.Rtsa_Config_Trace[j][i].averageCount = mBitView[j]->getTraceAttribute(i,BIT_AVAG_NUM_ATTR);//getAvgNum(i);
        }
    }

    stateParam.gConfig_Trace.detectorType = getDectorType();
    //Marker

    for(qint32 j = 0; j < RTSA_BITVIEWNUM; j++)
    {
        stateParam.gConfig_Marker[j].curmarkerID = mBitView[j]->getMarkerAttribute(BIT_MARKER_INDEX);
        stateParam.gConfig_Marker[j].markerPeakTraceOn = mIsPeakTrackOn;
        for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
        {
            stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].markerView = mBitView[j]->getMarkerAttribute(BIT_MARKER_VISIABLE,i);
            stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].gMarkerRefAmpt = mBitView[j]->getMarkerRefAmpt(i);
            stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].gMarkerNormalPosY = mBitView[j]->getMarkerNormalPosY(i);
            stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].markerType = mBitView[j]->getMarkerAttribute(BIT_MARKER_TYPE,i);
            stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].markerNoiseOn = mBitView[j]->getMarkerAttribute(BIT_MARKER_NOISE,i);
            stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].gMarkerRefFreq = mBitView[j]->getMarkerFreqAttribute(BIT_MARKER_NORMAL,i);
            stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].gMarkerDeltaFreq = mBitView[j]->getMarkerFreqAttribute(BIT_MARKER_DELTA,i);
        }

    }

    //Limit
    for(qint32 j = 0; j < RTSA_BITVIEWNUM; j++)
    {
        stateParam.gConfig_Limit[j].limitID = mBitView[j]->getLimitAttribute(BIT_LIMIT_INDEX);
        stateParam.gConfig_Limit[j].limitTest = mBitView[j]->getLimitAttribute(BIT_LIMIT_TEST);
        for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
        {
            stateParam.gConfig_Limit[j].limitOn[i] = mBitView[j]->getLimitAttribute(BIT_LIMIT_VIEW,i);
            stateParam.gConfig_Limit[j].limitEdgeOn[i] = mBitView[j]->getLimitAttribute(BIT_LIMIT_MARGIN,i);
            stateParam.gConfig_Limit[j].limitEdgeVal[i] = mBitView[j]->getLimitAttributeEX(BIT_LIMIT_MARGIN_VALUE,i);
            stateParam.gConfig_Limit[j].limitType[i] = mBitView[j]->getLimitAttribute(BIT_LIMIT_TYPE,i);
            stateParam.gConfig_Limit[j].limitEditNum[i] = mBitView[j]->getLimitAttribute(BIT_LIMIT_POINT_NUM,i);
            for(qint32 k = 0; k < stateParam.gConfig_Limit[j].limitEditNum[i]; k++)
            {
                stateParam.gConfig_Limit[j].limitFreq[k] = mBitView[j]->getLimitCurPointData(k,BIT_LIMIT_FREQ,i);
                stateParam.gConfig_Limit[j].limitAmpt[k] = mBitView[j]->getLimitCurPointData(k,BIT_LIMIT_AMPT,i);
            }
            stateParam.gConfig_Limit[j].limitCurEditIndex[i] = mCurLimitDataPos;
        }
    }

    //Display
//    stateParam.gConfig_Display.displayMode = RTSA_SPECTROGRAM;
    return;
}
/**
* @brief saveState
* @param fileName full path file name
* @Author Albert
* @date 2019-05-21
*/
qint32 RtSa_Interface::saveState(QString fileName)
{
    qint32 back = -1;
    mFileType = (qint64)RTSA_FILEHEADER_STATE;
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
    {
        return back;
    }
    else
    {
        file.write((char *)&mFileType, sizeof(mFileType));

        file.write((char *)&mStateParam, sizeof(mStateParam));
    }
    file.close();
    file.flush();
    back = 0;
    return back;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-14
*/
void RtSa_Interface::setStateParam(_RTSA_FILE_SAVE_LOAD_VARIABLE_ &stateParam)
{
    globalUserVariable->gRefreshAllParam = true;
    for(qint32 i = 0;i < RTSA_BITVIEWNUM; i++)
    {
        mBitView[i]->setBitviewType(stateParam.gConfig_Display.bitviewStatus[i]);
    }
    mIsCurBitViewSizeChange = false;
    setDisplay(stateParam.gConfig_Display.displayMode);
    setcurrentview(stateParam.gConfig_Display.curWindowIndex);
    //Freq
    setCHStandard(stateParam.gConfig_FreqSpan.channelStd);
    setChannelNumber(stateParam.gConfig_FreqSpan.channelNumber);
    setCommuDirection(stateParam.gConfig_FreqSpan.channelType);

    setCenterFreq(stateParam.gConfig_FreqSpan.gCenterFreq);
    setSpan(stateParam.gConfig_FreqSpan.gSpanFreq);
    setCFStep(stateParam.gConfig_FreqSpan.gStepFreq);
    setFreqOffset(stateParam.gConfig_FreqSpan.gOffsetFreq);

    //amplitude
//    setAmptUnit(stateParam.gConfig_Amplitude.units);
    setAmptUnit(stateParam.gConfig_Amplitude.units[stateParam.gConfig_Display.curWindowIndex]);
    setScaleDiv(stateParam.gConfig_Amplitude.scaleDiv[stateParam.gConfig_Display.curWindowIndex]);
    setRefOffset(stateParam.gConfig_Amplitude.refOffset[stateParam.gConfig_Display.curWindowIndex]);
    bitviewbottomdisplay = BV_TOP_APMTINFO;
    setAttenVal(stateParam.gConfig_Amplitude.attenVal);
    setAttenAuto(stateParam.gConfig_Amplitude.attenAuto);
    setPreAmpOn(stateParam.gConfig_Amplitude.preAmpStatus);
    globalUserVariable->gRefLevel = stateParam.gConfig_Amplitude.refLevel;
    stateParam.gConfig_Amplitude.refLevel = ChangedBmToOherUnit();
    if(getAmptUint() == RTSA_VOLT)
    {
        stateParam.gConfig_Amplitude.refLevel *= 1000000;
    }
    setRefLevel(stateParam.gConfig_Amplitude.refLevel);
    for(qint32 i = 0 ;i < RTSA_BITVIEWNUM; i++)
    {
//        mBitView[i]->setAmptdAttribute(BIT_AMPTD_DIV,stateParam.gConfig_Amplitude.scaleDiv[i]);
        mBitView[i]->setAmptdAttribute(BIT_AMPTD_OFFSET,stateParam.gConfig_Amplitude.refOffset[i]);
        mBitView[i]->setAmptdUnit(stateParam.gConfig_Amplitude.units[i]);
//        mBitView[i]->showTopWordsMsg(bitviewbottomdisplay);
    }
//    setAmptUnit(stateParam.gConfig_Amplitude.units);
    setAmptUnit(stateParam.gConfig_Amplitude.units[stateParam.gConfig_Display.curWindowIndex]);

    //Sweep
    setSingleSweep(stateParam.gConfig_Sweep.sweepType);
    setAcqTime(stateParam.gConfig_Sweep.acqTimeVal);
    setAcqTimeAuto(stateParam.gConfig_Sweep.autoAcqtime);
    setPersistenceTime(stateParam.gConfig_Sweep.persistenceVal);
    setPersistenceTimeInfinite(stateParam.gConfig_Sweep.autoPersistence);
    setHighestDensity(stateParam.gConfig_Sweep.highDensity);
    setLowestDensity(stateParam.gConfig_Sweep.lowDensity);
    setCurve(stateParam.gConfig_Sweep.curveNum);

    //BW
    setFFTWindow(stateParam.gConfig_BW.fftFilter);
    setBWIndex(stateParam.gConfig_BW.rbwIndex);
    setBWAuto(stateParam.gConfig_BW.autoRbw);

    //Trace
    for(qint32 j = 0; j < RTSA_BITVIEWNUM; j++)
    {
        mBitView[j]->setTraceAttribute(0,BIT_TRACE_INDEX,stateParam.gConfig_Trace.curTraceID[j]);
        for(qint32 i = 0;i < RTSA_NUM_TRACE; i++)
        {
            mBitView[j]->setTraceAttribute(i,BIT_TRACE_TYPE_ATTR,stateParam.gConfig_Trace.Rtsa_Config_Trace[j][i].traceType);
            mBitView[j]->setTraceAttribute(i,BIT_AVAG_NUM_ATTR,stateParam.gConfig_Trace.Rtsa_Config_Trace[j][i].averageCount);
            mBitView[j]->setTraceAttribute(i,BIT_AVAG_ATTR,stateParam.gConfig_Trace.Rtsa_Config_Trace[j][i].averageOn);
        }
    }
    setCurTrace(stateParam.gConfig_Trace.curTraceID[stateParam.gConfig_Display.curWindowIndex]);
    setDectorType(stateParam.gConfig_Trace.detectorType);

    //trigger
    //set all trigger params
    setTriggerLevel(RTSA_TRIGGER_VIDEO,stateParam.gConfig_Trigger.triggerVideoLevel);
    setTriggerSlope(RTSA_TRIGGER_VIDEO,stateParam.gConfig_Trigger.triggerVideoSlope);
    setTriggerDelayStatus(RTSA_TRIGGER_VIDEO,stateParam.gConfig_Trigger.triggerVideoDelayStatus);
    setTriggerDelay(RTSA_TRIGGER_VIDEO,stateParam.gConfig_Trigger.triggerVideoDelay);
    settriggerHoldOffTime(RTSA_TRIGGER_VIDEO,stateParam.gConfig_Trigger.triggerVideoHoldOff);

    setTriggerLevel(RTSA_TRIGGER_EXTERNAL,stateParam.gConfig_Trigger.triggerExternLevel);
    setTriggerSlope(RTSA_TRIGGER_EXTERNAL,stateParam.gConfig_Trigger.triggerExternSlope);
    setTriggerDelayStatus(RTSA_TRIGGER_EXTERNAL,stateParam.gConfig_Trigger.triggerExternDelayStatus);
    setTriggerDelay(RTSA_TRIGGER_EXTERNAL,stateParam.gConfig_Trigger.triggerExternDelay);
    settriggerHoldOffTime(RTSA_TRIGGER_EXTERNAL,stateParam.gConfig_Trigger.triggerExternHoldOff);

    setTriggerDelayStatus(RTSA_TRIGGER_PERIODIC_TIMER,stateParam.gConfig_Trigger.triggerPeriodDelayStatus);
    setTriggerDelay(RTSA_TRIGGER_PERIODIC_TIMER,stateParam.gConfig_Trigger.triggerPeriodDelay);

    setTriggerLevel(RTSA_TRIGGER_RF_BURST,stateParam.gConfig_Trigger.triggerRFLevel);
    setTriggerSlope(RTSA_TRIGGER_RF_BURST,stateParam.gConfig_Trigger.triggerRFSlope);
    setTriggerDelayStatus(RTSA_TRIGGER_RF_BURST,stateParam.gConfig_Trigger.triggerRFDelayStatus);
    setTriggerDelay(RTSA_TRIGGER_RF_BURST,stateParam.gConfig_Trigger.triggerRFDelay);
    settriggerHoldOffTime(RTSA_TRIGGER_RF_BURST,stateParam.gConfig_Trigger.triggerRFBurstHoldOff);

    settriggerHoldOffTime(RTSA_TRIGGER_FMTMASK,stateParam.gConfig_Trigger.triggerFMTHoldOff);
    setFmtDataNum(stateParam.gConfig_Trigger.fmtnumber);
    setFmtFreqData(stateParam.gConfig_Trigger.fmtFreq,stateParam.gConfig_Trigger.fmtnumber);
    setFmtAmptData(stateParam.gConfig_Trigger.fmtAmpt,stateParam.gConfig_Trigger.fmtnumber);


    setTrigger(stateParam.gConfig_Trigger.triggerType);
   //here should judge trigger mode to set params
    setTriggerPeriodTime(stateParam.gConfig_Trigger.triggerPeriodTime);
    switch(stateParam.gConfig_Trigger.triggerType)
    {
    //Video
    case RTSA_TRIGGER_VIDEO:
        setTriggerLevel(RTSA_TRIGGER_VIDEO,stateParam.gConfig_Trigger.triggerVideoLevel);
        setTriggerSlope(RTSA_TRIGGER_VIDEO,stateParam.gConfig_Trigger.triggerVideoSlope);
        setTriggerDelayStatus(RTSA_TRIGGER_VIDEO,stateParam.gConfig_Trigger.triggerVideoDelayStatus);
        setTriggerDelay(RTSA_TRIGGER_VIDEO,stateParam.gConfig_Trigger.triggerVideoDelay);
        settriggerHoldOffTime(RTSA_TRIGGER_VIDEO,stateParam.gConfig_Trigger.triggerVideoHoldOff);
        break;
    case RTSA_TRIGGER_EXTERNAL:
        setTriggerLevel(RTSA_TRIGGER_EXTERNAL,stateParam.gConfig_Trigger.triggerExternLevel);
        setTriggerSlope(RTSA_TRIGGER_EXTERNAL,stateParam.gConfig_Trigger.triggerExternSlope);
        setTriggerDelayStatus(RTSA_TRIGGER_EXTERNAL,stateParam.gConfig_Trigger.triggerExternDelayStatus);
        setTriggerDelay(RTSA_TRIGGER_EXTERNAL,stateParam.gConfig_Trigger.triggerExternDelay);
        settriggerHoldOffTime(RTSA_TRIGGER_EXTERNAL,stateParam.gConfig_Trigger.triggerExternHoldOff);
        break;
    case RTSA_TRIGGER_PERIODIC_TIMER:
        setTriggerDelayStatus(RTSA_TRIGGER_PERIODIC_TIMER,stateParam.gConfig_Trigger.triggerPeriodDelayStatus);
        setTriggerDelay(RTSA_TRIGGER_PERIODIC_TIMER,stateParam.gConfig_Trigger.triggerPeriodDelay);
        break;
    case RTSA_TRIGGER_RF_BURST:
        setTriggerLevel(RTSA_TRIGGER_RF_BURST,stateParam.gConfig_Trigger.triggerRFLevel);
        setTriggerSlope(RTSA_TRIGGER_RF_BURST,stateParam.gConfig_Trigger.triggerRFSlope);
        setTriggerDelayStatus(RTSA_TRIGGER_RF_BURST,stateParam.gConfig_Trigger.triggerRFDelayStatus);
        setTriggerDelay(RTSA_TRIGGER_RF_BURST,stateParam.gConfig_Trigger.triggerRFDelay);
        settriggerHoldOffTime(RTSA_TRIGGER_RF_BURST,stateParam.gConfig_Trigger.triggerRFBurstHoldOff);
        break;
    case RTSA_TRIGGER_FMTMASK:
        settriggerHoldOffTime(RTSA_TRIGGER_FMTMASK,stateParam.gConfig_Trigger.triggerFMTHoldOff);
        setFmtDataNum(stateParam.gConfig_Trigger.fmtnumber);
        setFmtFreqData(stateParam.gConfig_Trigger.fmtFreq,stateParam.gConfig_Trigger.fmtnumber);
        setFmtAmptData(stateParam.gConfig_Trigger.fmtAmpt,stateParam.gConfig_Trigger.fmtnumber);
//        stateParam.gConfig_Trigger.fmtnumber = mFmtDataTotalNum;
//        for(qint32 i = 0; i < stateParam.gConfig_Trigger.fmtnumber; i++)
//        {
//            stateParam.gConfig_Trigger.fmtFreq[i] = fmtFreq[i];
//            stateParam.gConfig_Trigger.fmtAmpt[i] = fmtAmplitude[i];
//        }
        break;
    }
//    setTriggerSlope(stateParam.gConfig_Trigger.triggerType,stateParam.gConfig_Trigger.triggerSlope);
//    setTriggerDelay(stateParam.gConfig_Trigger.triggerType,stateParam.gConfig_Trigger.triggerType);
    //Marker
    for(qint32 j = 0; j < RTSA_BITVIEWNUM; j++)
    {
        mBitView[j]->setMarkerAttribute(BIT_MARKER_INDEX,stateParam.gConfig_Marker[j].curmarkerID);
        setPeakTrackOn(stateParam.gConfig_Marker[j].markerPeakTraceOn);
        for(qint32 i = 0;i < RTSA_MARKER_TOTAL_CNT; i++)
       {
            mBitView[j]->setMarkerAttribute(BIT_MARKER_VISIABLE,stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].markerView,i);
            mBitView[j]->setMarkerAttribute(BIT_MARKER_TYPE,stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].markerType,i);
            mBitView[j]->setMarkerAttribute(BIT_MARKER_NOISE,stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].markerNoiseOn,i);
            mBitView[j]->setMarkerFreqAttribute(BIT_MARKER_NORMAL,stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].gMarkerRefFreq,i);
            mBitView[j]->setMarkerFreqAttribute(BIT_MARKER_DELTA,stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].gMarkerDeltaFreq,i);
            mBitView[j]->setMarkerRefAmpt(stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].gMarkerRefAmpt,i);
            mBitView[j]->setMarkerNormalPosY(stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].gMarkerNormalPosY,i);
            emit MarkerSelectOnOff(i,stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].markerView);
            emit BitViewMakerDraw(i,stateParam.gConfig_Marker[j].gRtsa_Config_marker[i].markerView);
       }
//        mBitView[j]->refleshdisplay();
//        mBitView[j]->refleshmarker();
    }

    //Limit
    for(qint32 j = 0; j < RTSA_BITVIEWNUM; j++)
    {
        mBitView[j]->setLimitAttribute(BIT_LIMIT_INDEX,stateParam.gConfig_Limit[j].limitID);
        mBitView[j]->setLimitAttribute(BIT_LIMIT_TEST,stateParam.gConfig_Limit[j].limitTest);

        for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
        {
            mBitView[j]->setLimitAttribute(BIT_LIMIT_VIEW,stateParam.gConfig_Limit[j].limitOn[i],i);
            mBitView[j]->setLimitAttribute(BIT_LIMIT_MARGIN,stateParam.gConfig_Limit[j].limitEdgeOn[i],i);
            mBitView[j]->setLimitAttributeEX(BIT_LIMIT_MARGIN_VALUE,stateParam.gConfig_Limit[j].limitEdgeVal[i],i);
            mBitView[j]->setLimitAttribute(BIT_LIMIT_TYPE,stateParam.gConfig_Limit[j].limitType[i],i);
            mBitView[j]->setLimitAttribute(BIT_LIMIT_POINT_NUM,stateParam.gConfig_Limit[j].limitEditNum[i],i);
            mBitView[j]->setLimitPointData(stateParam.gConfig_Limit[j].limitFreq,stateParam.gConfig_Limit[j].limitEditNum[i],BIT_LIMIT_FREQ,i);
            mBitView[j]->setLimitPointData(stateParam.gConfig_Limit[j].limitAmpt,stateParam.gConfig_Limit[j].limitEditNum[i],BIT_LIMIT_AMPT,i);
            SetCurLimitDataIndex(stateParam.gConfig_Limit[j].limitCurEditIndex[i]);
        }
    }
    globalUserVariable->gRefreshAllParam = false;

    //refresh all ctrl params. Albert add 19/07/16
//    pSweepControl.setMeasureParam();
//    if(globalUserVariable->startMode == RTSA_MODULE)
//    {
        pSweepControl.setConfigParam();
        QThread::msleep(200);
        pSweepControl.setMeasType(stateParam.gConfig_Display.displayMode);
        QThread::msleep(200);
        pSweepControl.setTriggerParam();
        QThread::msleep(200);

        for(qint32 i = 0;i < RTSA_BITVIEWNUM; i++)
        {
            mBitView[i]->refleshdisplay();
            mBitView[i]->refleshmarker();
        }
//    }
    return;
}
/**
* @brief loadState
* @param fileName full path file name
* @Author Albert
* @date 2019-05-21
*/
qint32 RtSa_Interface::loadState(QString fileName)
{
    qint32 back = -1;
//    back = loadPresState();

    memset(&mStateParam,0,sizeof(mStateParam));
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
       return back;
    }
    else
    {
       file.read((char *)&mFileType, sizeof(mFileType));

       file.read((char *)&mStateParam, sizeof(mStateParam));
    }
    file.close();
    back = 1;
    setStateParam(mStateParam);
    return back;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-14
*/
qint32 RtSa_Interface::savePresState()
{
    qint32 back = -1;
    _RTSA_CONFIG_PRESET_ presParam;
    presParam.startMode = globalUserVariable->startMode;
    presParam.startFileType = globalUserVariable->gfileType;

    QFile file(RTSA_PRE_STATE_FILE);
    if(!file.open(QIODevice::WriteOnly))
    {
        return back;
    }
    else
    {
        file.write((char *)&presParam, sizeof(presParam));
    }
    file.close();
    file.flush();
    back = 0;
    return back;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-14
*/
qint32 RtSa_Interface::loadPresState()
{
    qint32 back = -1;
    _RTSA_CONFIG_PRESET_ presParam;
    memset(&presParam,0,sizeof(presParam));
    QFile file(RTSA_PRE_STATE_FILE);
    if(!file.open(QIODevice::ReadOnly))
    {
       setNoticePara(NOTIC_MESSAGE,EXECUTE_ERR_EXCEPTION,RTSA_APP_FILE_PERS);
       errorOutput();
       return back;
    }
    else
    {
       file.read((char *)&presParam, sizeof(presParam));
    }
    file.close();
    back = 1;
//    pSweepControl.setStartedFlag(RTSA_START_FLAG);
    globalUserVariable->gfileType = presParam.startFileType;
    globalUserVariable->startMode = presParam.startMode;
//    if(presParam.startMode != RTSA_MODULE)
//    {
        pSweepControl.setStartedFlag(RTSA_START_FLAG);
//    }
    return back;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-14
*/
void RtSa_Interface::setBitViewParam(qint32 measType)
{
    switch(measType)
    {
    case RTSA_SPECTRUM_SPECTROGRAM:
        mBitView[0]->setBitviewType(RTSA_SPECTRUM_SPECTROGRAM);
        mBitView[1]->setBitviewType(RTSA_SPECTROGRAM);
        mBitView[1]->initSpectrogramCacheDataArray(gSpectrogramCacheData[0]);
        mBitView[0]->setSystemAttribute(WINDOWTYPE,BIT_MULTIWINDOW);
        mBitView[1]->setSystemAttribute(WINDOWTYPE,BIT_MULTIWINDOW);
        pTrace.setDisplay(RTSA_SPECTRUM_SPECTROGRAM);
        wintotalnum = 2;
        curwindowindex = 1;
        setcurrentview(0);
        mBitView[0]->show();
        mBitView[1]->show();
        mBitView[0]->refleshdisplay();
        mBitView[1]->refleshdisplay();
        break;
    case RTSA_SPECTROGRAM:
        globalUserVariable->openDpxDevice();
        mBitView[0]->setBitviewType(RTSA_DENSITY);
        pTrace.setDisplay(RTSA_SPECTROGRAM);
        mBitView[0]->setSystemAttribute(WINDOWTYPE,BIT_SINGLEWINDOW);
        wintotalnum = 1;
        curwindowindex = 1;
        setcurrentview(0);
        mBitView[0]->show();
        mBitView[0]->refleshdisplay();
        break;
    case RTSA_DENSITY:
        globalUserVariable->openDpxDevice();
        mBitView[0]->setBitviewType(RTSA_SPECTROGRAM);
        mBitView[1]->setBitviewType(RTSA_DENSITY);
        mBitView[0]->initSpectrogramCacheDataArray(gSpectrogramCacheData[0]);
#ifdef BITVIEW_TIME_MARKER
        mBitView[1]->initSpectrogramCacheDataArray(gSpectrogramCacheData[0]);
#endif
        pTrace.setDisplay(RTSA_DENSITY);
        mBitView[0]->setSystemAttribute(WINDOWTYPE,BIT_MULTIWINDOW);
        mBitView[1]->setSystemAttribute(WINDOWTYPE,BIT_MULTIWINDOW);
        wintotalnum = 2;
        curwindowindex = 1;
        setcurrentview(0);
        mBitView[0]->show();
        mBitView[1]->show();
        mBitView[0]->refleshdisplay();
        mBitView[1]->refleshdisplay();
        break;
//        break;
    case RTSA_DENSITY_SPECTROGRAM:
        mBitView[0]->setBitviewType(RTSA_SPECTRUM_SPECTROGRAM);
        mBitView[1]->setBitviewType(RTSA_SPECTROGRAM);
        mBitView[2]->setBitviewType(RTSA_SPECTRUM_SPECTROGRAM);
        mBitView[3]->setBitviewType(RTSA_SPECTRUM_SPECTROGRAM);
        mBitView[1]->initSpectrogramCacheDataArray(gSpectrogramCacheData[0]);
        pTrace.setDisplay(RTSA_DENSITY_SPECTROGRAM);
        mBitView[0]->setSystemAttribute(WINDOWTYPE,BIT_MULTIWINDOW);
        mBitView[1]->setSystemAttribute(WINDOWTYPE,BIT_MULTIWINDOW);
        mBitView[2]->setSystemAttribute(WINDOWTYPE,BIT_MULTIWINDOW);
        mBitView[3]->setSystemAttribute(WINDOWTYPE,BIT_MULTIWINDOW);
        curwindowindex = 3;
        wintotalnum = 4;
        setcurrentview(0);
        mBitView[0]->show();
        mBitView[1]->show();
        mBitView[2]->show();
        mBitView[3]->show();
        mBitView[0]->refleshdisplay();
        mBitView[1]->refleshdisplay();
        mBitView[2]->refleshdisplay();
        mBitView[3]->refleshdisplay();
//        globalUserVariable->openDpxDevice();
        break;
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-07-02
*/
void RtSa_Interface::SetDisplayMode(qint32 mDisMode)
{
    if(mDisMode < RTSA_INDOOR)
        mDisMode = RTSA_INDOOR;
    else if(mDisMode > RTSA_NIGHT)
        mDisMode = RTSA_NIGHT;
    globalUserVariable->gDisplayMode = mDisMode;
    setSystemDisplay(mDisMode);
    emit RedrawInfoShow(LABEL_DISPLAY);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-07-02
*/
qint32 RtSa_Interface::GetDisplayMode()
{
    return globalUserVariable->gDisplayMode;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-07-30
*  true---- suspend draw  false ---- start draw
*/
void RtSa_Interface::DrawFlag(bool isSuspend)
{
    globalUserVariable->gSuspendDrawFlag = isSuspend;
    return;
}

bool RtSa_Interface::getDrawFlag()
{
    return globalUserVariable->gSuspendDrawFlag;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-07-04
*/
void RtSa_Interface::BuildFmtFromTrace()
{
    qreal freq[101] = {0};
    qreal ampt[101] = {0};
    qint32 limitID = getCurTrace();
    qint32 freqstep  = (qint32)((globalUserVariable->gStopFreq - globalUserVariable->gStartFreq)/100);
    quint32 amptstep  = (quint32)((RTSA_NUM_SWEEP_POINT - 1)/100);
    qreal *trace = pTrace.GetTraceData(RTSA_NUM_SWEEP_POINT,limitID);
    for(qint32 i = 0 ; i < 100; i++)
    {
        freq[i] = (getStartFreq() + freqstep * i)/RTSA_MHZ;
        ampt[i] = getMaxTraceData(trace,amptstep * i,amptstep) + 10.0;
    }
    freq[100] = getStopFreq()/RTSA_MHZ;
    ampt[100] = trace[RTSA_NUM_SWEEP_POINT - 1];

    memcpy(fmtFreq,freq,sizeof(qreal) * 101);
    memcpy(fmtAmplitude,ampt,sizeof(qreal)* 101);
    mFmtDataTotalNum = 101;
    setFmtFreqData(freq,101);
    setFmtAmptData(ampt,101);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-07-04
*/
void RtSa_Interface::DeleteAllFmtMask()
{
    mFmtDataTotalNum = 0;
    memset(fmtFreq,0,sizeof(fmtFreq));
    memset(fmtAmplitude,0,sizeof(fmtFreq));
    setFmtFreqData(0,0);
    setFmtAmptData(0,0);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-09
*/
void RtSa_Interface::setFmtTriggerCriterion(qint32 criterion)
{
//    globalUserVariable->gFmtTriggerCriterion = criterion;
    pSweepControl.setFmtTriggerCriterion(criterion);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-09
*/
qint32 RtSa_Interface::getFmtTriggerCriterion()
{
    return globalUserVariable->gFmtTriggerCriterion;
}

void RtSa_Interface::InsertFmtDataRow()
{
    if(isFreqInFmtArray(getStartFreq()/RTSA_MHZ))
    {
        return;
    }
    mFmtDataTotalNum ++;
    for(qint32 i = 0; i < mFmtDataTotalNum - 1; i++)
    {
        fmtFreq[i + 1] = fmtFreq[i];
        fmtAmplitude[i + 1] = fmtAmplitude[i];
    }
    fmtFreq[0] = getStartFreq()/RTSA_MHZ;
    fmtAmplitude[0] = -10.0;
    setFmtFreqData(fmtFreq,mFmtDataTotalNum);
    setFmtAmptData(fmtAmplitude,mFmtDataTotalNum);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-16
*/
bool RtSa_Interface::hasMarkerOn()
{
    bool markerOn = false;
    for(qint32 j = 0; j < RTSA_BITVIEWNUM; j++)
    {
        for(qint32 i = 0; i < RTSA_MARKER_TOTAL_CNT; i++)
        {
//           if(mBitView[j]->isHidden())
//           {
//               continue;
//           }
           markerOn = mBitView[j]->getMarkerAttribute(BIT_MARKER_VISIABLE,i);
           if(markerOn)
           {
               return markerOn;
           }
        }
    }
    return markerOn;
}
/**
* @brief
* @param
* @Author Albert
* @date 2020-04-21
*/
qint32 RtSa_Interface::ParseFileType(QString fileName)
{
    qint32 back = -1;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
       return back;
    }
    else
    {
       file.read((char *)&mFileType, sizeof(mFileType));
    }
    file.close();
    back = 1;
    return back;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-22
*/
void RtSa_Interface::initFileType(qint32 fileType)
{
    switch (fileType) {
    case RTSA_FILE_STATE:
        mFileType = (qint64)RTSA_FILEHEADER_STATE;
        initStateParam(mStateParam);
        break;
    case RTSA_FILE_TRACE_STATE:
        mFileType = (qint64)RTSA_FILEHEADER_STATE_DATA;
        initStateParam(mStateParam);
        break;
    case RTSA_FILE_SCREENCONFIG_STATE:
        break;
    case RTSA_FILE_MEASUREDATA:
        break;
    case RTSA_FILE_LIMIT:
        break;
    default:
        break;
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-22
*/
void RtSa_Interface::parseFile(QString fileName)
{
//    QFile file(fileName);
//    if(!file.open(QIODevice::ReadOnly))
//    {
//       return ;
//    }
//    else
//    {
//       file.read((char *)&mFileType, sizeof(mFileType));
//    }
//    file.close();
    ParseFileType(fileName);
//    mFileType = RTSA_FILEHEADER_STATE_DATA;
    switch (mFileType) {
    case RTSA_FILEHEADER_STATE:
        loadState(fileName);
        break;
    case RTSA_FILEHEADER_STATE_DATA:
        loadTraceData(fileName);
        break;
    case RTSA_FILE_SCREENCONFIG_STATE:
        break;
    case RTSA_FILE_MEASUREDATA:
        break;
    case RTSA_FILE_LIMIT:
        break;
    default:
        break;
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-22
*/
qint32 RtSa_Interface::saveTraceData(QString fileName)
{
    qint32 ret = -1;
    qint32 validStartPos = 0;
    qint32 RealNumber = 0;
    // trace data divide into 3 parts. 1-detector trace data, 2-dpx data, 3-spectrogram data
    uchar* pDpxData = NULL;
    qreal *trace = pTrace.GetTraceData(RTSA_NUM_SWEEP_POINT,0);
    initStateParam(mStateParam);
    mFileType = (qint64)RTSA_FILEHEADER_STATE_DATA;
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
    {
        return ret;
    }
    else
    {
        // first save file type,
        file.write((char *)&mFileType, sizeof(mFileType));
        //// state params.
        file.write((char *)&mStateParam, sizeof(mStateParam));

        //detector trace data
        for(qint32 j = 0; j < RTSA_BITVIEWNUM; j++)
        {
            for(qint32 i = 0; i < RTSA_NUM_TRACE; i ++)
            {
                if(mBitView[j]->getBitviewType() == BIT_SPECTROGRAM)
                {
                    validStartPos = mBitView[j]->getSpectrogramValidStartPos(validStartPos,RealNumber);
                }
               mBitView[j]->getTraceRenderData(trace,RTSA_NUM_SWEEP_POINT,i);
               file.write((char *)trace, sizeof(qreal) * RTSA_NUM_SWEEP_POINT);
            }
        }
        // spectrogram data
        file.write((char *)&validStartPos, sizeof(qint32));
        file.write((char *)&RealNumber, sizeof(qint32));
        file.write((char *)gSpectrogramCacheData, sizeof(qreal) * RTSA_SPECTROGRAM_CACHE_DATA * RTSA_TRACE_DATA_NUM);
        // dpx data
        pDpxData = pTrace.GetDensityData(DPX_WIDTH_SIZE * DPX_HEIGHT_SIZE * 4);
        file.write((char *)pDpxData, sizeof(uchar) * DPX_WIDTH_SIZE * DPX_HEIGHT_SIZE * 4);
    }
    file.close();
    file.flush();
    ret = 0;
    return ret;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-08-29
*/
qint32 RtSa_Interface::loadTraceData(QString fileName)
{
    qint32 ret = -1;
    qint32 validStartPos = 0;
    qint32 RealNumber = 0;
    uchar* pDpxData;
    qreal *trace;
    trace = pTrace.GetTraceData(RTSA_NUM_SWEEP_POINT,0);
    pDpxData = pTrace.GetDensityData(DPX_WIDTH_SIZE * DPX_HEIGHT_SIZE * 4);
    memset(&mStateParam,0,sizeof(mStateParam));
    memset(&gSpectrogramCacheData,0,sizeof(gSpectrogramCacheData));
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
       return ret;
    }
    else
    {
       file.read((char *)&mFileType, sizeof(mFileType));
        // read state params
       file.read((char *)&mStateParam, sizeof(mStateParam));
       setStateParam(mStateParam);

       // read normal trace data
       for(qint32 j = 0; j  < RTSA_BITVIEWNUM; j++)
       {
           mBitView[j]->setFileLoadDoneFlag(true);
           for(qint32 i = 0; i < RTSA_NUM_TRACE; i ++)
           {
              file.read((char *)trace, sizeof(qreal) * RTSA_NUM_SWEEP_POINT);
              mBitView[j]->setTraceRenderData(trace,RTSA_NUM_SWEEP_POINT,i);
           }
       }
       // spectrogram data
       file.read((char *)&validStartPos,sizeof(qint32));
       file.read((char *)&RealNumber,sizeof(qint32));

       file.read((char *)gSpectrogramCacheData, sizeof(qreal) * RTSA_SPECTROGRAM_CACHE_DATA * RTSA_TRACE_DATA_NUM);
       // when cache data re-fill, load data should from last end to this start
       if(RealNumber == RTSA_SPECTROGRAM_CACHE_DATA)
       {
            if(validStartPos < SPECTROGRAM_SCREEN_MAX)
            {
                qint32 partStartPos = SPECTROGRAM_SCREEN_MAX - validStartPos;
                for(qint32 i = (RTSA_SPECTROGRAM_CACHE_DATA - partStartPos); i < RTSA_SPECTROGRAM_CACHE_DATA; i++)
                {
                    drawFileLoadSpectrogram(gSpectrogramCacheData[i]);
                }
            }
       }
       for(qint32 i = 0; i < validStartPos; i++)
       {
           drawFileLoadSpectrogram(gSpectrogramCacheData[i]);
       }
       // dpx data
       file.read((char *)pDpxData, sizeof(uchar) * DPX_WIDTH_SIZE * DPX_HEIGHT_SIZE * 4);
       pTrace.SetDensityData(gSpectrogramCacheData[validStartPos - 1],pDpxData);

    }
    file.close();
    refreshAllBitView();
//    setSingleSweep(true);
    ret = 1;
    return ret;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-03
*/
void RtSa_Interface::refreshAllBitView()
{
    for(qint32 i = 0; i < RTSA_BITVIEWNUM;i++)
    {
        mBitView[i]->refleshdisplay();
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-04
*/
void RtSa_Interface::setBitViewFileLoadFlag(bool isFileload)
{
    for(qint32 i = 0; i < RTSA_BITVIEWNUM; i++)
    {
        if(isFileload)
        {
            if(mBitView[i]->getBitviewType() == BIT_SPECTROGRAM)
                mBitView[i]->refreshSepectrogramRect();
        }
        mBitView[i]->setFileLoadDoneFlag(isFileload);
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-09-05
*/
void RtSa_Interface::drawFileLoadSpectrogram(qreal *pData)
{
    for(qint32 i = 0; i < RTSA_BITVIEWNUM; i++)
    {
        if(mBitView[i]->getBitviewType() == BIT_SPECTROGRAM)
        {
            mBitView[i]->renderFileSpectrogram(pData);
//            mBitView[i]->refleshdisplay();
        }
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-10-09
*/
void RtSa_Interface::GetRawData(char* dest)
{
    pTrace.getRawTraceData(dest);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-10-09
*/
void RtSa_Interface::GetDrawData(char* dest)
{
//    memcpy(dest,globalUserVariable->gTraceMeasureVal,sizeof(qreal)*NUM_SWEEP_POINT*TRACE_CNT_TOTAL);
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-10-09
*/
void RtSa_Interface::GetAllData(char *dest)
{
//    memcpy(dest,globalUserVariable->gOriginalMeasureVal,sizeof(qreal)*NUM_SWEEP_POINT);
//    memcpy((char*)dest + sizeof(qreal)*NUM_SWEEP_POINT,globalUserVariable->gTraceMeasureVal,sizeof(qreal)*NUM_SWEEP_POINT*TRACE_CNT_TOTAL);
    pTrace.GetAllTraceData(dest);
//    memcpy((char*)dest + sizeof(qreal)*RTSA_NUM_SWEEP_POINT,pData,sizeof(qreal)*RTSA_NUM_SWEEP_POINT);
    return;
}

void RtSa_Interface::GetDensityData(char *dest)
{
    dest = (char*)pTrace.GetDensityData(sizeof(uchar) * DPX_WIDTH_SIZE * DPX_HEIGHT_SIZE * 4);
    return;
}

void RtSa_Interface::refreshSpectrogramRect()
{
    for(qint32 i = 0; i < RTSA_BITVIEWNUM; i++)
    {
        mBitView[i]->refreshSepectrogramRect();
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-12-04
*/
void RtSa_Interface::setspectrogramCursorID(qint32 CursorId)
{
    for(qint32 i = 0; i < mDisplayMode + 1; i ++)
    {
        if(mBitView[i]->getBitviewType() != BIT_SPECTRUM)
        {
            mBitView[i]->setspectrogramCursorID(CursorId);
            mBitView[i]->refleshdisplay();
        }
    }
    return;
}

qint32 RtSa_Interface::getspectrogramCursorID()
{
//    if(mDisplayMode != RTSA_SPECTROGRAM)
//        return 0;
    for(qint32 i = 0; i < mDisplayMode + 1; i ++)
    {
        if(mBitView[i]->getBitviewType() != BIT_SPECTRUM)
        {
            return mBitView[i]->getspectrogramCursorID();
        }
    }
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-12-10
*/
void RtSa_Interface::closeAllSpectrogramTimeCursor(qint32 bitviewIndex)
{
    for(qint32 i = 0; i < RTSA_NUM_TRACE; i++)
    {
        mBitView[bitviewIndex]->setSepctrogramEnableDrawCursor(i,false);
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-12-03
*/
void RtSa_Interface::setSepctrogramEnableDrawCursor(qint32 CursorId, bool isEnable)
{
//    if(mDisplayMode != RTSA_SPECTROGRAM)
//        return;
    for(qint32 i = 0; i < mDisplayMode + 1; i ++)
    {
        if(mBitView[i]->getBitviewType() != BIT_SPECTRUM)
        {
//            globalUserVariable->gCursorState[CursorId] = isEnable;
            mBitView[i]->setSepctrogramEnableDrawCursor(CursorId,isEnable);
            if(!isEnable)
            {
                mBitView[i]->setspectrogramCursorIndex(CursorId,0);
            }
            mBitView[i]->refleshdisplay();
        }
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-12-03
*/
bool RtSa_Interface::isSepectrogramDrawCursorEnable(qint32 CursorId)
{
//    if(mDisplayMode != RTSA_SPECTROGRAM)
//        return false;
    for(qint32 i = 0; i < mDisplayMode + 1; i ++)
    {
        if(mBitView[i]->getBitviewType() != BIT_SPECTRUM)
        {
            return mBitView[i]->isSepectrogramDrawCursorEnable(CursorId);
        }
    }
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-12-03
*/
void RtSa_Interface::setspectrogramCursorIndex(qint32 CursorId, qint32 index)
{
//    if(mDisplayMode == RTSA_SPECTROGRAM)
//        return;
    for(qint32 i = 0; i < mDisplayMode + 1; i ++)
    {
        if(mBitView[i]->getBitviewType() != BIT_SPECTRUM)
        {
            mBitView[i]->setspectrogramCursorIndex(CursorId,index);
            mBitView[i]->refleshdisplay();
        }
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-12-03
*/
qint32 RtSa_Interface::getspectrogramCursorIndex(qint32 CursorId)
{
//    if(mDisplayMode != RTSA_SPECTROGRAM)
//        return 0;
    for(qint32 i = 0; i < mDisplayMode + 1; i ++)
    {
        if(mBitView[i]->getBitviewType() != BIT_SPECTRUM)
        {
            return mBitView[i]->getspectrogramCursorIndex(CursorId);
        }
    }
}

void RtSa_Interface::repaintBitview()
{
    if(globalUserVariable->gSweepType == RTSA_SINGLE)
    {
        for(qint32 i = 0; i < RTSA_BITVIEWNUM; i++)
        {
            mBitView[i]->refleshdisplay();
        }
    }
    return;
}

bool RtSa_Interface::IsSizeChangeEnable()
{
    return mIsCurBitViewSizeChange;
}

/**
* @brief
* @param
* @Author Albert
* @date 2019-10-30
*/
#ifdef BITVIEW_F239
void RtSa_Interface::scaleChange(qreal xsize, qreal ysize)
{
    emit BitScaleChange();
    globalUserVariable->gSuspendDrawFlag = true;
    qreal span = globalUserVariable->gSpanFreq/xsize;
    setSpan(span);
    globalUserVariable->gSuspendDrawFlag = false;
}

void RtSa_Interface::BitSuspendDrawSlot()
{
    globalUserVariable->gSuspendDrawFlag = true;
    return;
}

void RtSa_Interface::BitChangeCenterFreq(qreal freq)
{
    emit BitScaleChange();
    setCenterFreq(freq);
    globalUserVariable->gSuspendDrawFlag = false;
    return;
}
void RtSa_Interface::BitChangeRefLevel(qreal refLevel)
{
    emit BitScaleChange();
    globalUserVariable->gRefLevel = refLevel;
    qreal refval = ChangedBmToOherUnit();
    if(getAmptUint() == RTSA_VOLT)
    {
        refval *= 100000;
    }
    setRefLevel(refval);
    globalUserVariable->gSuspendDrawFlag = false;
    return;
}
#endif
//Begin By Roc
//End By Roc
