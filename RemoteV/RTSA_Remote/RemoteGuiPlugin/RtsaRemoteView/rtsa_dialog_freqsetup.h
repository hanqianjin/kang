#ifndef RTSA_DIALOG_FREQSETUP_H
#define RTSA_DIALOG_FREQSETUP_H

#include <QWidget>
#include "rtsa_dialog_freqsetup.h"
#include "rtsa_dialog_digitinput.h"
#include "rtsa_remote_interface.h"
#include <QMap>
#include "rtsa_lineedit.h"
#include <QKeyEvent>
#include "rtsa_dialog_ch_std.h"
#include "rtsa_user_variable.h"
#include <QTimer>
namespace Ui {
class RtSa_Dialog_FreqSetup;
}

class RtSa_Dialog_FreqSetup : public QWidget
{
    Q_OBJECT

public:
    explicit RtSa_Dialog_FreqSetup(Rtsa_Remote_Interface *RtsaRemoteInterface,RtSa_Dialog_Digitinput* InputDialog = 0,RtSa_User_Variable* userVariable = NULL,QWidget *parent = 0);
    ~RtSa_Dialog_FreqSetup();
    void setUserVariable(RtSa_User_Variable* userVariable);
//    void setUserVariable(RtSa_User_Variable* userVariable);
    void initDisplay();
    void HideChStdDialog();
protected:
    void keyPressEvent(QKeyEvent *event);
private slots:
    void finishEntry_freq(qint32 index);

    void on_pb_cancel_clicked();

    void on_LedCenterFreq_clicked();

    void on_pb_FullSpan_clicked();

    void on_LedStartFreq_clicked();

    void on_LedStopFreq_clicked();

    void on_LedSpan_clicked();

    void on_LedFreqStep_clicked();

    void DigitalKeyRespond(QKeyEvent *event);

    void on_LedOffsetFreq_clicked();

    void on_CHStdClose();

    void on_LedChStd_clicked();

    void on_LedChannel_clicked();

    void on_pb_Uplink_clicked();

    void on_pb_Downlink_clicked();

    void on_timeOut();

private:
    Ui::RtSa_Dialog_FreqSetup *ui;
    RtSa_Dialog_Digitinput *mInputDialog;
    Rtsa_Remote_Interface *RemoteInterfaceObj;
    RtSa_Dialog_Ch_Std *mChStdDialog;
    QMap <quint32,RtSa_LineEdit*> mEditList;
    RtSa_User_Variable *mUserVariable;

//    void AskEquipment(quint32 index);
    void initMap();
    void refreshEditDisplay(quint32 index);

    void refreshButtonDisplay();
    void showInputDialog(qint32 index);
    void showCHStdDialog();
    qint32 mSelectInputID;
    QTimer *timer;
    qint32 mUpDownFlag;
};

#endif // RTSA_DIALOG_FREQSETUP_H
