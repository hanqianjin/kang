#ifndef RTSA_DIALOG_MEASURESETUP_H
#define RTSA_DIALOG_MEASURESETUP_H

#include <QWidget>
#include "rtsa_remote_interface.h"
#include "rtsa_dialog_digitinput.h"
#include "rtsa_lineedit.h"
#include <QKeyEvent>
namespace Ui {
class RtSa_Dialog_MeasureSetup;
}

class RtSa_Dialog_MeasureSetup : public QWidget
{
    Q_OBJECT

public:
    explicit RtSa_Dialog_MeasureSetup(Rtsa_Remote_Interface *RtsaRemoteInterface = NULL, QWidget *parent = 0);
    ~RtSa_Dialog_MeasureSetup();
    void initDisplay();
protected:
    void keyPressEvent(QKeyEvent *event);
private slots:

    void on_pb_cancel_clicked();

    void on_pb_Spectrum_clicked();

    void on_pb_Persisten_spec_clicked();

    void on_pb_Density_clicked();

    void on_pb_Density_Spectrogram_clicked();

private:
    Ui::RtSa_Dialog_MeasureSetup *ui;
     Rtsa_Remote_Interface *RemoteInterfaceObj;
    void initMap();
    void refreshButtonDisplay();
    void showInputDialog(qint32 index);
    QPushButton* buttonGroup[RTSA_BITVIEWNUM];
};

#endif // RTSA_DIALOG_MEASURESETUP_H
