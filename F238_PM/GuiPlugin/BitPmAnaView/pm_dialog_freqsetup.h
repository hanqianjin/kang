#ifndef PM_DIALOG_FREQSETUP_H
#define PM_DIALOG_FREQSETUP_H

#include <QWidget>
#include "pm_dialog_freqsetup.h"
#include "pm_dialog_digitinput.h"
#include "pm_interface.h"
#include <QMap>
#include "pm_lineedit.h"
#include <QKeyEvent>
#include "pm_dialog_ch_std.h"
#include "pm_user_variable.h"
#include <QTimer>

namespace Ui {
class Pm_Dialog_FreqSetup;
}

class Pm_Dialog_FreqSetup : public QWidget
{
    Q_OBJECT

public:
    explicit Pm_Dialog_FreqSetup(BitPm_Interface *BitPmInterface,Pm_Dialog_Digitinput* InputDialog = 0,QWidget *parent = 0);
    ~Pm_Dialog_FreqSetup();
protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void finishEntry_freq(qint32 index);
    void on_pb_cancel_clicked();
    void DigitalKeyRespond(QKeyEvent *event);
    void on_timeOut();

    void on_LedCenterFreq_clicked();
    void on_LedStartFreq_clicked();
    void on_LedStopFreq_clicked();
    void on_LedFreqStep_clicked();
    void on_LedSpan_clicked();

//    void on_pb_SpanDown_currentIndexChanged(int index);
//    void on_pb_SpanUp_currentIndexChanged(int index);

    void on_pb_LastSpan_clicked();
    void on_pb_MinSpan_clicked();
    void on_pb_FullSpan_clicked();

    void on_LedChStd_clicked();

    void on_LedChannel_clicked();

    void on_pb_FreqOffset_toggled(bool checked);
    void on_LedOffsetFreq_clicked();
//    void on_LedOffsetFreqSize_clicked();

   void on_CHStdClose();

   void on_pb_Uplink_clicked();

   void on_pb_Downlink_clicked();

public:
    void initDisplay();

private:
    void initMap();
    void refreshEditDisplay(quint32 index);
    void refreshButtonDisplay();
    void showInputDialog(qint32 index);

    void showCHStdDialog();
public:
    void HideChStdDialog();

private:
    Ui::Pm_Dialog_FreqSetup *ui;
    Pm_Dialog_Digitinput *mInputDialog;
    BitPm_Interface *PmInterfaceObj;
    QMap <quint32,Pm_LineEdit*> mEditList;

    Pm_Dialog_Ch_Std *mChStdDialog;


    qint32 mSelectInputID;
    QTimer *timer;
    qint32 mUpDownFlag;
    qint32 m_UpFlg;    //向上加数据个数 从0 开始  超过10后进位加
    qint32 m_DownFlg;//向下加数据个数 从0 开始  超过10后进位减
};

#endif // PM_DIALOG_FREQSETUP_H

