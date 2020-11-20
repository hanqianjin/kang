#ifndef RTSA_DIALOG_DISPLAYSETUP_H
#define RTSA_DIALOG_DISPLAYSETUP_H

#include <QWidget>
#include "rtsa_remote_interface.h"
#include "rtsa_dialog_digitinput.h"
#include "rtsa_lineedit.h"
#include <QKeyEvent>
#include <QTimer>

namespace Ui {
class RtSa_Dialog_SweepSetup;
}

class RtSa_Dialog_SweepSetup : public QWidget
{
    Q_OBJECT

public:
    explicit RtSa_Dialog_SweepSetup(Rtsa_Remote_Interface *RtsaRemoteInterface = NULL,RtSa_Dialog_Digitinput *input = NULL,QWidget *parent = 0);
    ~RtSa_Dialog_SweepSetup();
    void initDisplay();
private:
    void initMap();
    void refreshEditDisplay(quint32 index);
    void refreshButtonDisplay();
    void showInputDialog(qint32 index);
    void initButtonDisplay();
protected:
    void keyPressEvent(QKeyEvent *event);
private slots:
    void finishEntry_Display(qint32 index);

    void on_pb_conti_clicked();

    void on_pb_single_clicked();

//    void on_pb_Spectrum_clicked();

//    void on_pb_Spectrogram_clicked();

    void on_pb_Infinite_clicked();

    void on_pb_cancel_clicked();

    void on_pb_Auto_Density_clicked();

    void on_edit_time_clicked();

    void on_edit_highest_clicked();

    void on_edit_lowest_clicked();

    void on_edit_curve_clicked();

    void on_pb_Finite_clicked();

    void DigitalKeyRespond(QKeyEvent *event);

    void on_pb_Sweep_Once_clicked();

    void on_leAcqtime_clicked();

    void on_pbAcqAuto_clicked();

    void on_pbAcqMan_clicked();

    void on_timeOut();

private:
    Ui::RtSa_Dialog_SweepSetup *ui;
   Rtsa_Remote_Interface *RemoteInterfaceObj;
    RtSa_Dialog_Digitinput *mInputDialog;
    QMap <quint32,RtSa_LineEdit*> mEditList;
    qint32 mSelectInputID;
    QTimer* timer;
    qint32 mUpDownFlag;
};

#endif // RTSA_DIALOG_DISPLAYSETUP_H
