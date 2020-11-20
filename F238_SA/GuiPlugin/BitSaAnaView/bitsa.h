#ifndef BITSA_H
#define BITSA_H

#include <QWidget>
#include <QStylePainter>
#include <QButtonGroup>
#include <QMap>
#include <QPointer>

#include "sa_shared_memory.h"
#include "extern.h"
#include "define.h"
//#include "file_user_variable.h"

#include "sa_threadgraph.h"
#include "sa_user_variable.h"
#include "sa_user_limit.h"
#include "sa_alothforsa.h"
#include "sa_applicationcontrol.h"
#include "sa_parasaveload.h"

#include "sa_uirefresh_control.h"
#include "sa_freqspan_control.h"
#include "sa_amplitude_control.h"
#include "sa_bw_control.h"
#include "sa_trigger_control.h"
#include "sa_trace_control.h"
#include "sa_marker_control.h"
#include "qvector.h"
#include "sa_widget_acptable.h"
#include "sa_widget_channelpowertable.h"
#include "sa_widget_markertable.h"
#include "sa_widget_occupiedxdbtable.h"
#include "sa_widget_multiacptable.h"
#include "sa_widget_spectrumemtable.h"
#include "sa_widget_spuriousemtable.h"

#include "sa_controlwidget_acptable.h"
#include "sa_controlwidget_chnltable.h"
#include "sa_controlwidget_markertable.h"
#include "sa_controlwidget_occupiedxdbtable.h"
#include "sa_controlwidget_multiacptable.h"
#include "sa_controlwidget_spectrumemtable.h"
#include "sa_controlwidget_spuriousemtable.h"
#include "globaldef.h"

#include <QKeyEvent>
#include <QCoreApplication>
#include <QTimer>

#include "bpltinterface.h"
#include "sa_interface_dialog.h"

#include "sa_dialog_freqsetup.h"
#include "sa_dialog_amptsetup.h"
#include "sa_dialog_displaysetup.h"
#include "sa_dialog_bwsetup.h"
#include "sa_dialog_triggersetup.h"
#include "sa_dialog_tracesetup.h"
#include "sa_dialog_markersetup.h"
#include "sa_dialog_measuresetup.h"
#include "sa_dialog_markersingle.h"
#include "sa_dialog_limit.h"

namespace Ui {
class BitSA;
}
class SA_Dialog_DigitInput;
class SA_Dialog_AllSetup;
class SA_Dialog_Setup;
class SA_ClickedWidget;
class SAFileManager;
class SA_Dialog_QuickSave;

class BitSA : public QWidget,public BPltInterface
{
    Q_OBJECT
public:
    BitSA(QWidget *parent = 0);
    ~BitSA();
public:
    controlInterface *pcontrolInterface;
public:
    void SetMeasureItems(qint32 item);
    void PltCurAnaMode(qint32 imode);
    qint32 PltSavePres(qint32 itype);
    qint32 PltSaveConditions(qint32 itype);
    qint32 PltLoadConditions(qint32 itype);
    void ChangeLcdStateWithNoSig(qint32 ilock);
    void MenuClose();
    void SetLocalRemoteMode(qint32 imode);
    void PresetDefaultStates();
    void SetDisplayMode(qint32 imode);
    void SetSysRefuiStates(qint32 itype);
    void showMenu(qint32 index);
    qint32 GetCurMenu();
    void   SetLeftInfobarDisplay(qint32 isShow);
    qint32 GetLeftInfobarDisplay();
    void   SetScreenFull(qint32 isFull);
    qint32 GetScreenFull();
    void   SetScreenLock(qint32 islock);
    qint32 GetScreenLock();
    void   SetAllMkrOff();
private:
    QTimer *mDelayTimer;
    qint32 modmenuCloseeChangeFlag;
    QEventLoop *mloop;
    Ui::BitSA *pBitSA;
    ThreadGraph *m_thread;   // Thread Define
    user_variable *m_user_variable;
    user_limit    *globalUserLimit;
    alothforsa *bitaloth;
    paraSaveLoad *pparaSaveLoad;
    sa_UIRefresh_Control *psa_UIRefresh_Control;
    sa_Amplitude_Control *psa_Amplitude_Control;

    void modeChange();
private:
    void initQssByDef();
    void initPointer();
    void initTableWidget();
    void initThread();
    void initDrive();
    void initVariable();
private://Johnson 190822
    void presetStatesProcess();
private slots:
    void getLimitDot();
    void judgeTableContent(/*QTableWidget *tableWidget,unsigned long long startFreq,unsigned long long stopFreq*/);
    void graphRefreshFunc();
    void menuShow(int menuID);
    void runBtnFunction(qint32 menuID);
    void runBtnMkrFunction(qint32 menuID);
    void on_infoRefresh(qint32 mType, qint32 mIndex);
    //Johnson 190530
    void measureModeParaRefresh();
private:
    void getTableWidgetValue(void);
    void initTableWidgetValue(void);
private:
    _FILE_SAVE_LOAD_VARIABLE_ gGlobalParam;
    qint32 singparamflag;//1 means single state,2 means single state but need hold curve and trig param setting events,default 0
#if SMALL_LARGE_PIXMAP_IMAGE
private:
    void setPixmap(bool bSmall = true);//bSmall == true is small pixmap;bSmall = false is large pixmap
    void setImage(bool bSmall = true);//bSmall == true is small image;bSmall = false is large image
#endif
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
#ifdef SA_MULTI_TOUCH
    bool event(QEvent *event);
#endif
private:
    qint32 m_ScaleMode;
    qint32 m_TranslationMode;
    qint32 m_MarkerMoveMode;
    qint32 mTraceAvgResetNumber;

    QMap<SA_ClickedWidget*,qint32> *mInfoWidget;
    qint32 lastMenuID;

    QWidget *mSetupDialog;
    sa_interface_dialog* mInteDialog;
    SA_Dialog_QuickSave *mScreenshots;
    QButtonGroup *mBtnGroup;
    QButtonGroup *mBtnMkrGroup;
    char winStatus[5];

    QRect CenterDrawRect;
    qint32 FullStatus;
    qint32 reflag;
    qint32 suspendFlag;

    /*
    QPixmap mPixmap;
    SA_Dialog_AllSetup *mAllSetDialog;
    */
private:
    qint32 DelayFunc(qint32 timeMs);
    void initInfo();
    void initWidget(void);
    void initMenuWidget();
    void setMenuProperty(const char *name, const QVariant &value);
    void loadstylesheet(int stylemode);
    void setZoomIn();
    void refreshSystem(qint32 mIndex);
    void refreshFreq(qint32 mIndex);
    void refreshAmpt(qint32 mIndex);
    void refreshSweep(qint32 mIndex);
    void refreshBw(qint32 mIndex);
    void refreshLimit(qint32 mIndex);
    void refreshTrigger(qint32 mIndex);
    void refreshTrace(qint32 mIndex);
    void refreshMeasure(qint32 mIndex);
    void refreshTraceStatus();
    void refreshTraceType();
    void showMarkerTableIcon(qint32 viewStatus);
    void traceAverageProcessFunction(qint32 traceNo);

    void showMkrMenu(qint32 index);
    qint32 setParaForSEM();
    qint32 setParaForSpurEM();
    void processRawData();
    void refreshSpecEMData();
    void setSpecEMBwValue(quint64 uRbwValue,quint64 uVbwValue);
public slots:
    void on_pb_marker_AllOff_clicked();

private slots:
    void refreshBtnFocus(qint32 mIndex);
    void refreshMarker(qint32 mIndex);
    void on_menuDestroyed();
    void on_refreshMarkerInfo();

    void on_pb_left_hide_clicked();
    void on_WidgetClicked();
    void on_rightButton1_clicked();
    void on_rightButton2_clicked();
    void on_rightButton3_clicked();
    void on_rightButton4_clicked();
    void on_rightButton5_clicked();
    void on_rightButton6_clicked();
    void on_rightButton7_clicked();
    void on_rightButton8_clicked();
    void on_rightButton9_clicked();
    void on_rightButton10_clicked();
    void on_lblAverage_clicked();
    void on_lblAverageValue_clicked();
signals:
    void SysSetSig();
    void ZoomIn(bool);
    void KeyEventSig(qint32 keyval);
    void AllSetSig();
    void MesPlatTitleSig(qint32 iIndex);
    void PltAllPresetSig();
//Johnson relative with table
private:
    QWidget *pBottomInfoWidget;
    QWidget *pBottomInfoControlWidget;
    QWidget *pBottomInfoMarker;
    QWidget *pBottomInfoMarkerControl;

    sa_widget_ACPTable *pACPTable;
    sa_widget_ChannelPowerTable *pChannelPowerTable;
    sa_widget_markerTable *pMarkerTable;
    sa_widget_OccupiedXdBTable *pOccupiedXdBTable;
    sa_widget_MultiACPTable *pMultiACPTable;
    sa_widget_SpectrumEMTable *pSpectrumEMTable;
    sa_widget_SpuriousEMTable *pSpuriousEMTable;

    sa_ControlWidget_ACPTable *pControlACPTable;
    sa_controlWidget_ChnlTable *pControlChannelPowerTable;
    sa_controlWidget_MarkerTable *pControlMarkerTable;
    sa_controlWidget_OccupiedXdBTable *pControlpOccupiedXdBTable;
    sa_ControlWidget_MultiACPTable *pControlMultiACPTable;
    sa_ControlWidget_SpectrumEMTable *pControlSpectrumEMTable;
    sa_ControlWidget_SpuriousEMTable *pControlSpuriousEMTable;
private slots:
    void slotOperateTable();
    void refreshMkrTable();
    void slotHideTable(quint32 tableID);

    void on_bottomInfoDestroyed();
    void on_bottomInfoMarkerDestroyed();
    void on_lblDetectors_clicked();

    void on_lblDetectorValue_clicked();

    void on_lblIFOutPut_clicked();

    void on_lblIFOutPutValue_clicked();
    void loopQuit();
private:
    void bottomInfoShow();
    void setTablePosition();
//public:
private:
    void bottomInfoMarker();
    void bottomInfoClose();
    void bottomInfoMarkerClose();
//public:
    void initTableInfoWidget();
//public:
    void setCenterRect(qint32 x,qint32 y,qint32 w,qint32 h);
    void setCenterRect_pbLeftHide_ChnlPowerMode();
    void setCenterRect_pbLeftHide_ACPMode();
    void setCenterRect_pbLeftHide_OccuXdBMode();
    void setCenterRect_pbLeftHide_MultiACPMode();
    void setCenterRect_pbLeftHide_SpectrumEMMode();
    void setCenterRect_pbLeftHide_SpuriousEMMode();
    void setCenterRect_pbLeftShow_ChnlPowerMode();
    void setCenterRect_pbLeftShow_ACPMode();
    void setCenterRect_pbLeftShow_OccuXdBMode();
    void setCenterRect_pbLeftShow_MultiACPMode();
    void setCenterRect_pbLeftShow_SpectrumEMMode();
    void setCenterRect_pbLeftShow_SpuriousEMMode();
    void adjustRect();
public://Johnson 190422 Zero Restrain celibrate
    bool bTableWidgetInitComplete;
private:
    SAFileManager* mFileManager;
    qint32 loadFlag;
    qint32 modeChangeFlag;


//    SA_Dialog_AllSetup *mAllSetDialog;
//    SA_Dialog_FreqSetup *wFreqSetup;
//    SA_Dialog_AmptSetup *wAmptSetup;
//    SA_Dialog_DisplaySetup *wSweepSetup;
//    SA_Dialog_BWSetup *wBwSetup;
//    SA_Dialog_TriggerSetup *wTriggerSetup;
//    SA_Dialog_TraceSetup  *wTraceSetup;
//    SA_Dialog_MarkerSetup *wMarkerSetup;
//    SA_Dialog_Limit *wLimitSetup;
//    SA_Dialog_MeasureSetup *wMeasureSetup;
//    SA_Dialog_MarkerSingle *wMarkerSingle;

    QString makeColorString(const QColor &color, const QString type = "RGB");
private slots:
    void LoadFilePara(QString mPath);
    void saveFilePara(QString mPath, int mFileType);
    void quickSaveFilePara(QString mPath, int mFileType);
    void on_fastSaveDialogClosed();

    void on_fileManagerWidgetClosed();
    void menuClose();
    void on_uiRefresh(qint32 index);
};

#endif
