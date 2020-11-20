#ifndef RTSA_DIALOG_MARKERSETUP_H
#define RTSA_DIALOG_MARKERSETUP_H

#include <QWidget>
#include <QPainter>
#include <QButtonGroup>
#include "rtsa_interface.h"
#include "rtsa_dialog_digitinput.h"
#include "rtsa_lineedit.h"
#include <QKeyEvent>
#include <QTimer>

namespace Ui {
class RtSa_Dialog_MarkerSetup;
}
class RtSa_Dialog_MarkerSetup : public QWidget
{
    Q_OBJECT
public:
    explicit RtSa_Dialog_MarkerSetup(RtSa_Interface *interface,RtSa_Dialog_Digitinput *mInput,QWidget *parent = 0 );
    ~RtSa_Dialog_MarkerSetup();
    void initDisplay();
    void setCtlAttribute();
    void showNotice(bool isShow);
protected:
    void keyPressEvent(QKeyEvent *event);
signals:
private slots:
    void on_finishEntry(qint32 index);
    void mMarkerSelectGroup_click(qint32 index);
//    void mMarkerViewGroup_click(qint32 index);
//    void mMarkerToGroup_click(qint32 index);
//    void on_pb_allon_clicked();

//    void on_pb_normal_clicked();

//    void on_pb_delta_clicked();

//    void on_pb_mkrnoise_clicked();

    void on_edit_MkrFreq_clicked();
    void on_pb_cancel_clicked();
    void On_Update(bool isOn);

    void On_DisplayChange();
    void on_pb_toggle_toggled(bool checked);

    void on_pb_mkrnoise_toggled(bool checked);

    void DigitalKeyRespond(QKeyEvent *event);

    void on_pb_peakTrack_toggled(bool checked);

    void on_pb_MkrAllOn_clicked();

    void on_pb_Normal_clicked();

    void on_pb_Delta_clicked();

    void on_pb_Start_clicked();

    void on_pb_Center_clicked();

    void on_pb_Stop_clicked();

    void on_timeOut();

    void on_pb_DeltaPair_clicked();

private:
    Ui::RtSa_Dialog_MarkerSetup *ui;
    RtSa_Dialog_Digitinput *mInputDialog;
    RtSa_Interface *mControl;
    QButtonGroup *mMarkerSelectGroup;
    QButtonGroup *mMarkerViewGroup;
    QButtonGroup *mMarkerToGroup;
    qint32 mCurrentMarker;
    void initMap();
//    void refreshMarker(qint32 index);
    void refreshMarkerEdit(qint32 index = -1);
    void showInputDialog(qint32 index);
    void editclicked();
    void refreshMarkerInfoBox();
    void refreshMarkerFreq();
    void refreshMarkerType();
    void refreshMarkerNoise();
    void markerSelect(qint32 index);
    void refreshMarkerState();
    void refreshMarkerPeakTrack();
//    void digitInputClose();
    bool mIsAllMarkerButtonPressed;
    qint32 mSelectInputID;
    QTimer* timer;
    qint32 mUpDownFlag;
};

#endif // RTSA_DIALOG_MARKERSETUP_H
