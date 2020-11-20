#ifndef RTSA_DIALOG_TRACESETUP_H
#define RTSA_DIALOG_TRACESETUP_H

#include <QWidget>
#include <QButtonGroup>
#include <QPushButton>
#include "rtsa_remote_interface.h"
#include "rtsa_dialog_digitinput.h"
#include <QKeyEvent>
#include "rtsa_dialog_warning.h"
#include <QTimer>

namespace Ui {
class RtSa_Dialog_TraceSetup;
}

class RtSa_Dialog_TraceSetup : public QWidget
{
    Q_OBJECT

public:
    explicit RtSa_Dialog_TraceSetup(Rtsa_Remote_Interface *RtsaRemoteInterface = NULL, RtSa_Dialog_Digitinput *Input = NULL, QWidget *parent = 0);
    ~RtSa_Dialog_TraceSetup();
    void InitDisplay();
private:
    void InitTraceOnOff();
    void InitTraceType();
    void InitDector();
    void InitCurTrace();
    void refreshInfo();
    void showInputDialog(qint32 index);
protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_pb_cancel_clicked();

//    void on_pb_allon_clicked();

//    void on_pb_clearall_clicked();

    void on_Update();

//    void TraceType_Change(qint32 index);

    void TraceDec_Change(qint32 index);

    void TraceSelect_Change(qint32 index);

//    void TraceToggle(bool isOn);


//    void on_pb_allon_clicked();

    void on_pb_TraceType_currentIndexChanged(int index);

    void on_pb_toggle_toggled(bool checked);

    void finishEntry_trace(qint32 index);

    void DigitalKeyRespond(QKeyEvent* event);

    void on_averageEdit_clicked();

    void on_pb_traceAllOn_clicked();

    void on_pb_clearall_clicked();

    void on_timeOut();


private:
    Ui::RtSa_Dialog_TraceSetup *ui;
    Rtsa_Remote_Interface *RemoteInterfaceObj;
    QButtonGroup *mTraceTypeGroup;
    QButtonGroup *mTraceDectorGroup;
    QButtonGroup *mTraceSelectGroup;
//    QButtonGroup *mTraceOnOffGroup;
    QPushButton *mTraceOnOffGroup[RTSA_TRACE];
    RtSa_Dialog_Digitinput *mInputDialog;
    qint32 mCurSelTraceIndex;
    QTimer* timer;
    qint32 mUpDownFlag;
};

#endif // RTSA_DIALOG_TRACESETUP_H
