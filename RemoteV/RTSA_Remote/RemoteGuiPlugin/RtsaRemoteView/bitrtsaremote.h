/**************Copyright (c)**************************************
 **
 **               INNO Instrument(China) Co.,Ltd.
 **
 **------------File Info------------------------------------------
 **Class name:              resaremote
 **Latest Version:          V1.0.0
 **Latest modified Date:
 **Created by:              ROC
 **Created date:            2019/10/18
 **Descriptions:            RTSA main plot class
 **
 *****************************************************************/
#ifndef BITRTSA_REMOTE_H
#define BITRTSA_REMOTE_H

#include <QWidget>
#include <QLayout>
#include "bitview.h"
#include "rtsa_define.h"
#include "rtsa_user_variable.h"

#include "rtsa_threadgraph.h"
#include "rtsa_dialog_freqsetup.h"
#include "rtsa_dialog_digitinput.h"
#include "rtsa_dialog_amptsetup.h"
#include "rtsa_dialog_bwsetup.h"
#include "rtsa_dialog_tracesetup.h"
#include "rtsa_dialog_triggersetup.h"
#include "rtsa_dialog_markersetup.h"
#include "rtsa_dialog_sweepsetup.h"
#include "rtsa_dialog_measuresetup.h"
#include "rtsa_dialog_allsetup.h"
#include "rtsa_dialog_bottommarkersetup.h"
#include "rtsa_clickedwidget.h"
#include "rtsa_dialog_limit.h"
#include "rtsa_dialog_toolsetup.h"
#include "rtsa_dialog_warning.h"
#include "rtsa_dialog_quicksave.h"
#include "safilemanager.h"
#include "bpltinterface.h"

namespace Ui {
class BitRtSaRemote;
}

class BitRtSaRemote : public QWidget,public BPltInterface
{
    Q_OBJECT

public:
    explicit BitRtSaRemote(QWidget *parent = 0);
    ~BitRtSaRemote();

//function define
public:
    void InitBitview();
    void InitStyleSheet(qint32 index);
    void deleteWidget();
    void InitBottomLayOut();
    void InitMarkerGroup();
    void menuClose();

    void InitAllDialog();


//    qint32 GetLocalRemoteMode();

    // virtual functions
    void ChangeLcdStateWithNoSig(qint32 ilock);
    void SetLocalRemoteMode(qint32 mode);
    void MenuClose();
    void SetMeasureItems(qint32 imea);
    void PltCurAnaMode(qint32 imode);
    qint32 PltSavePres(qint32 itype);
    qint32 PltSaveConditions(qint32 itype);
    qint32 PltLoadConditions(qint32 itype);
    void PresetDefaultStates();
    void SetDisplayMode(qint32 imode);
    void SetSysRefuiStates(qint32 itype);


    void PltCurLinkMode(qint32 imode);
    qint32 PltSaveLinkFlg(qint32 itype);
protected:
    void resizeEvent(QResizeEvent *event)override;
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
//    bool eventFilter(QObject *watched, QEvent *event);
private:
    void initGlobalInterface();
    void initUserVariable();
    void initThread();
    void initWidget(void);

//    void HideDialog(qint32 menuID);
//    void ShowDialog(qint32 menuID);

    void HideWidget();
    void ShowWidget();

    //ALbert 19/03/043
    void InitLeftInfoWidget();

    void refreshTraceStatus();

    void keyRespond(qint32 key);

    void refreshTraceType();

    void InitFileManager();

signals:
    void ZoomIn(bool isOn);
    void MarkerMoved(bool isOn);
    void KeyEventSig(qint32 keyval);
    void SysSetSig();

    void MesPlatTitleSig(qint32 iIndex);

    void TouchSig(quint32 iIndex);

    void PltAllPresetSig();
private slots:
    void graphRefreshFunc();

    void menuHide(qint32 menuID,bool visible);
    void menuShow(qint32 menuID);
    void setActive();
    void ClockKeyDown();
    void setDialogActive();
    void connectStatusChange(qint32 pStatus);


 //variable define
//    void on_pushButton_clicked();

//    void on_Home_clicked();

    void on_rightButton8_clicked();
    void on_rightButton9_clicked();

    void on_rightButton10_clicked();

    void MarkerWidgetHide(bool isOn);

    void MarkerInfoChange(qint32 markerID,bool isOn);

    void MarkerSelect(qint32 MarkerID, bool isOn);

    void on_pb_Drag_clicked();

    void BitViewMarkerRefresh(quint32 MarkerID);

//    void on_pb_marker_Off_2_clicked();

    void on_pb_marker_AllOff_2_clicked();

    void leftInfo_Update(qint32 infoID);

    void on_WidgetClicked();

    void on_rightButton1_clicked();

    void on_rightButton3_clicked();

    void marker_changed(bool isChanged);

    void on_rightButton4_clicked();

    void on_rightButton2_clicked();

    void on_rightButton7_clicked();

    void on_rightButton6_clicked();

    void on_rightButton5_clicked();

    //file manager slots
    void LoadFilePara(QString strPath);
    void saveFilePara(QString strPath, qint32 fileType);
    void quickSaveFilePara(QString strPath,qint32 fileType);
    void on_fastSaveDialogClosed();
    void on_fileManagerWidgetClosed();

public:
    Rtsa_Remote_Interface *RemoteInterfaceObj;
private:
    Ui::BitRtSaRemote *ui;
    //    BitView *mBitView[RTSA_BITVIEWNUM];
    RtSa_ThreadGraph *m_thread;
    RtSa_User_Variable *UserVariableObj;

    QButtonGroup *mBtnGroup;
    QButtonGroup *mBtnMarkerGroup;
    RtSa_Dialog_Digitinput *mDigitInput;
    RtSa_Dialog_FreqSetup *mFreqSetup;
    RtSa_Dialog_AmptSetup *mAmptSetup;
    RtSa_Dialog_BWSetup *mBwSetup;
    RtSa_Dialog_TraceSetup *mTraceSetup;
    RtSa_Dialog_TriggerSetup *mTriggerSetup;
    RtSa_Dialog_MarkerSetup *mMarkerSetup;
    RtSa_Dialog_SweepSetup *mDisplaySetup;
    RtSa_Dialog_MeasureSetup *mMeasureSetup;
    RtSa_Dialog_AllSetup *mAllSetup;
    RtSa_Dialog_Warning *mWarningSetUp;
    RtSa_Dialog_Limit *mLimit;
    RtSa_Dialog_BottomMarkerSetup *mBottomMarkerSetup;
    RtSa_Dialog_ToolSetup *mToolSetup;
    RtSa_Dialog_QuickSave *mQuickSave;
    QWidget* mCurSetupDialog;
//    QMap <qint32 , QWidget *> mWidgetList;
    bool mIsZoomIn;
    bool mShiftKeyPressed;
    qint32 mCurMenuID;
    QHBoxLayout *bomLayout;
    QPushButton* mMarkerButton[RTSA_MARKER_TOTAL_CNT];
//    QButtonGroup *mMarkerButtonGroup;
//    qreal mLastAcqTime;
    bool mDragFlag;
    QMap<RtSa_ClickedWidget*,qint32> *mRtSaInfoWidget;
    quint32 touchSignal;
    qint32 mStyleIndex;
    SAFileManager* mFileManager;
};

#endif // BITRTSA_REMOTE_H
