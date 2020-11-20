#ifndef RTSA_DIALOG_TOOLSETUP_H
#define RTSA_DIALOG_TOOLSETUP_H

#include <QWidget>
#include "rtsa_interface.h"
#include "rtsa_dialog_digitinput.h"
#include "rtsa_lineedit.h"
#include "rtsa_define.h"
#include <QKeyEvent>
#include <QTimer>

namespace Ui {
class RtSa_Dialog_ToolSetup;
}

class RtSa_Dialog_ToolSetup : public QWidget
{
    Q_OBJECT

public:
    explicit RtSa_Dialog_ToolSetup(RtSa_Interface *interface = NULL, RtSa_Dialog_Digitinput *input = NULL, QWidget *parent = 0);
    ~RtSa_Dialog_ToolSetup();
    void InitDisplay();
    void showNotice(bool isShow);
protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_edit_time_clicked();

    void finishEntry_Display(qint32 index);

    void DigitalKeyRespond(QKeyEvent *event);


    void on_edit_highest_clicked();

    void on_edit_lowest_clicked();

    void on_edit_curve_clicked();

    void on_pb_cancel_clicked();

    void on_pb_Auto_Density_clicked();

    void on_pb_Infinite_clicked();

    void on_pb_Finite_clicked();

    void on_timeOut();

private:
    Ui::RtSa_Dialog_ToolSetup *ui;
    RtSa_Interface *mControl;
    RtSa_Dialog_Digitinput *mInputDialog;
    QMap <quint32,RtSa_LineEdit*> mEditList;

    void initMap();
    void refreshEditDisplay(quint32 index);
    void refreshButtonDisplay();
    void showInputDialog(qint32 index);
    void initButtonDisplay();
    void refreshTitle();
    qint32 mSelectInputID;
    QTimer *timer;
    qint32 mUpDownFlag;
};

#endif // RTSA_DIALOG_TOOLSETUP_H
