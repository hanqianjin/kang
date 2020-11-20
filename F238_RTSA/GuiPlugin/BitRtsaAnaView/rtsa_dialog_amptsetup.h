#ifndef RTSA_DIALOG_AMPTSETUP_H
#define RTSA_DIALOG_AMPTSETUP_H

#include <QWidget>
#include <QMap>
#include <QDialog>
#include <QButtonGroup>
#include "rtsa_lineedit.h"
#include "rtsa_interface.h"
#include "rtsa_lineedit.h"
#include "rtsa_dialog_digitinput.h"
#include <QKeyEvent>
#include <QTimer>

namespace Ui {
class RtSa_Dialog_AmptSetup;
}

class RtSa_Dialog_AmptSetup : public QWidget
{
    Q_OBJECT

public:
    explicit RtSa_Dialog_AmptSetup(RtSa_Interface* interface, RtSa_Dialog_Digitinput* input= NULL, QWidget *parent = 0);
    ~RtSa_Dialog_AmptSetup();
    void initDisplay();
protected:
    void mousePressEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent *event);
//    bool eventFilter(QObject *watched, QEvent *event);
private slots:
    void finishEntry_ampt(qint32 index);
    void btn_clicked();
    void on_pb_cancel_clicked();

    void on_leRefLevel_clicked();

    void on_leAtten_clicked();

//    void on_pbAutoAttenOn_clicked();

    void on_leScaleDiv_clicked();

    void on_leRefOffset_clicked();

//    void on_pushButton_clicked();

//    void on_pb_unit_dBm_clicked();

//    void on_pb_unit_dBmV_clicked();

//    void on_pb_unit_dBuV_clicked();

//    void on_pb_unit_V_clicked();

//    void on_pb_unit_W_clicked();

    void on_Update();

    void on_pb_Scale_Auto_clicked();

    void unitSelect(qint32 unit);

    void setAttenType(qint32 atten);

    void on_pbPreAmptOn_toggled(bool checked);

    void DigitalKeyRespond(QKeyEvent *event);

    void on_pb_Auto_clicked();

    void on_pb_Manual_clicked();

    void on_timeOut();

private:
    Ui::RtSa_Dialog_AmptSetup *ui;
    RtSa_Dialog_Digitinput *mInputDialog;
    RtSa_Interface *mControl;
    QMap <quint32,RtSa_LineEdit*> mEditList;
//    QButtonGroup *mUnitGroup;
    void initMap();
    void refreshEditDisplay(quint32 index);
    void refreshButtonDisplay();
    void showInputDialog(qint32 index);
    void refreshAttenAutoButton();
    qint32 mSelectInputID;
    QTimer *timer;
    qint32 mUpDownFlag;
};

#endif // RTSA_DIALOG_AMPTSETUP_H
