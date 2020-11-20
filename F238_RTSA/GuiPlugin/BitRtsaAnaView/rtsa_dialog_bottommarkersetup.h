#ifndef RTSA_DIALOG_BOTTOMMARKERSETUP_H
#define RTSA_DIALOG_BOTTOMMARKERSETUP_H

#include <QWidget>
#include <QButtonGroup>
#include "rtsa_interface.h"
#include "rtsa_dialog_digitinput.h"
#include <QKeyEvent>

namespace Ui {
class RtSa_Dialog_BottomMarkerSetup;
}

class RtSa_Dialog_BottomMarkerSetup : public QWidget
{
    Q_OBJECT

public:
    explicit RtSa_Dialog_BottomMarkerSetup(RtSa_Interface *interface = NULL,RtSa_Dialog_Digitinput *mInput = NULL,QWidget *parent = 0);
    ~RtSa_Dialog_BottomMarkerSetup();
    void InitGroup();
    void refreshDisplay();
protected:
    void keyPressEvent(QKeyEvent *event);
private slots:
    void on_pb_cancel_clicked();

    void MarkerToGroup_click(qint32 index);

    void on_pb_normal_clicked();

    void on_pb_delta_clicked();

    void on_pb_MinSearch_clicked();

    void on_pb_visible_toggled(bool checked);

    void refreshMarkerTable();

    void On_DisplayChange();

    void MarkerInfoChange(qint32 markerID,bool isOn);

    void on_pb_PeakTrackOn_toggled(bool checked);

    void on_edit_MkrFreq_clicked();

    void on_timeOut();

    void On_Update(bool isOn);
    void on_finishEntry(qint32 index);
    void on_pb_DeltaPair_clicked();

private:
    void editclicked();
    void showInputDialog(qint32 index);
    void refreshMarkerFreq();
private:
    Ui::RtSa_Dialog_BottomMarkerSetup *ui;
    RtSa_Interface *mControl;
    QButtonGroup *mMarkerToGroup;
    QWidget* pParent;
    RtSa_Dialog_Digitinput *mInputDialog;
    QTimer* timer;
    qint32 mSelectInputID;
    qint32 mUpDownFlag;

};

#endif // RTSA_DIALOG_BOTTOMMARKERSETUP_H
