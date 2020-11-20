/**************Copyright (c)**************************************
 **
 **               INNO Instrument(China) Co.,Ltd.
 **
 **------------File Info------------------------------------------
 **Class name:              bitpm
 **Latest Version:          V1.0.0
 **Latest modified Date:
 **Created by:              ROC
 **Created date:            2019/10/18
 **Descriptions:            PM main plot class
 **
 *****************************************************************/
#ifndef BITPM_H
#define BITPM_H

#include <QLayout>
#include <QWidget>
#include <QString>
#include <QDebug>

#include "bitgaugedialview.h"
#include "pm_define.h"
#include "pm_user_variable.h"

#include "pm_threadgraph.h"
#include "pm_dialog_allsetup.h"
#include "pm_clickedwidget.h"
#include "pm_dialog_freqsetup.h"
#include "pm_dialog_digitinput.h"
#include "pm_dialog_amptsetup.h"
#include "pm_dialog_zerosetup.h"
#include "pm_dialog_averagesetup.h"
#include "pm_dialog_sweepsetup.h"
#include "pm_dialog_limitsetup.h"
#include "pm_dialog_displaysetup.h"
#include "pm_dialog_warning.h"
#include "pm_dialog_quicksave.h"
#include "safilemanager.h"
#include "bpltinterface.h"


namespace Ui {
class BitPm;
}

class BitPm : public QWidget  ,public BPltInterface
{
    Q_OBJECT

public:
    explicit BitPm(QWidget *parent = 0);
    ~BitPm();

//function define
public:
    void InitBitview();
//    void InitStyleSheet(qint32 index);
    void deleteWidget();
    void menuClose();
    void InitAllDialog();

//    qint32 GetLocalPmMode();

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

private:
    void initGlobalInterface();
    void initThread();
    void initWidget(void);

    void HideWidget();
    void ShowWidget();

    void InitLeftInfoWidget();
    void keyRespond(qint32 key);
    void InitFileManager();

signals:
    void ZoomIn(bool isOn);
    void KeyEventSig(qint32 keyval);
    void SysSetSig();

    void MesPlatTitleSig(qint32 iIndex);

    void TouchSig(quint32 iIndex);

    void PltAllPresetSig();

private slots:
    void thread_setContinous(qint32 nContinous);
    void anaylysisPower(QByteArray arrayData);

    void waringZeroClose();
    void waringZeroShow();
    void waringZeroSleep(qint32 nTime);

    void anaylysisRevc(_PM_SENSOR_DATA &sensorData);
    void graphRefreshFunc();

    void menuHide(qint32 menuID,bool visible);
    void menuShow(qint32 menuID);
    void setActive();
    void ClockKeyDown();
    void setDialogActive();
    void connectStatusChange(qint32 pStatus);

    void on_pb_Drag_clicked();

    void leftInfo_Update(qint32 infoID);
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

    //file manager slots
    void LoadFilePara(QString strPath);
    void saveFilePara(QString strPath, qint32 fileType);
    void quickSaveFilePara(QString strPath,qint32 fileType);
    void on_fastSaveDialogClosed();
    void on_fileManagerWidgetClosed();

public:
    BitPm_Interface *PmInterfaceObj;
private:
    Ui::BitPm *ui;
    Pm_ThreadGraph *m_thread;

    Pm_User_Variable *UserVariableObj;

    QButtonGroup *mBtnGroup;

    Pm_Dialog_Digitinput *mDigitInput;
    Pm_Dialog_FreqSetup *mFreqSetup;
    Pm_Dialog_AmptSetup *mAmptSetup;
    Pm_Dialog_SweepSetup *mSweepSetup;
    Pm_Dialog_AverageSetup *mAverageSetup;
    Pm_Dialog_ZeroSetup *mZeroSetup;
    Pm_Dialog_Limit *mLimitSetup;
    Pm_Dialog_DisplaySetup *mDisplaySetup;
    Pm_Dialog_QuickSave *mQuickSave;
    Pm_Dialog_AllSetup *mAllSetup;
    Pm_Dialog_Warning *mWarningSetUp;

    QWidget* mCurSetupDialog;
    qint32 mCurMenuID;
    bool mIsZoomIn;
    bool mShiftKeyPressed;
    bool mDragFlag;
    QMap<Pm_ClickedWidget*,qint32> *mPmInfoWidget;
    quint32 touchSignal;
    qint32 mStyleIndex;
    SAFileManager* mFileManager;


private:

    qreal m_fAveTotleForward;
    qreal m_fAveTotleReverse;
    qint32 m_nAverage ;
    qreal m_fZeroTotleForward;
    qreal  m_fZeroTotleReverse;
    quint32 m_nZeroNum;
};

#endif // BITPM_H
