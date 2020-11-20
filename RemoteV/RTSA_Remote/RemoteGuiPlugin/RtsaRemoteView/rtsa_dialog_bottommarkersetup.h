#ifndef RTSA_DIALOG_BOTTOMMARKERSETUP_H
#define RTSA_DIALOG_BOTTOMMARKERSETUP_H

#include <QWidget>
#include <QButtonGroup>
#include "rtsa_remote_interface.h"

namespace Ui {
class RtSa_Dialog_BottomMarkerSetup;
}

class RtSa_Dialog_BottomMarkerSetup : public QWidget
{
    Q_OBJECT

public:
    explicit RtSa_Dialog_BottomMarkerSetup(Rtsa_Remote_Interface *RtsaRemoteInterface= NULL,QWidget *parent = 0);
    ~RtSa_Dialog_BottomMarkerSetup();
    void InitGroup();
    void refreshDisplay();

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

private:
    Ui::RtSa_Dialog_BottomMarkerSetup *ui;
    Rtsa_Remote_Interface *RemoteInterfaceObj;
    QButtonGroup *mMarkerToGroup;
    QWidget* pParent;

};

#endif // RTSA_DIALOG_BOTTOMMARKERSETUP_H
