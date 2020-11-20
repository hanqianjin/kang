#ifndef SA_DIALOG_MARKERSINGLE_H
#define SA_DIALOG_MARKERSINGLE_H

#include <QWidget>
#include <QKeyEvent>
#include "sa_interface_dialog.h"

class controlInterface;
class user_variable;
namespace Ui {
class SA_Dialog_MarkerSingle;
}

class SA_Dialog_MarkerSingle : public QWidget,public sa_interface_dialog
{
    Q_OBJECT

public:
    explicit SA_Dialog_MarkerSingle(controlInterface *interface, user_variable *puser_variable,QWidget *parent = 0);
    ~SA_Dialog_MarkerSingle();
    void initDisplay();
    void initWidget();
    void showWidget();
    void hideWidget();

    void refreshInfo();
    void refreshTitle();
signals:
    void mDialogHide();
private slots:
    void on_pb_close_clicked();
    void on_pb_Normal_clicked();

    void on_pb_Delta_clicked();

    void on_pb_Delta_Pair_clicked();

    void on_pb_Start_clicked();

    void on_pb_Center_clicked();

    void on_pb_Stop_clicked();

    void on_pb_PeakSearch_clicked();

    void on_pb_MinSearch_clicked();

    void on_pb_NextPeak_clicked();

    void on_pb_PeakLeft_clicked();

    void on_pb_PeakRight_clicked();

    void on_pb_Mkr_On_clicked();

    void on_pb_PeakTrack_toggled(bool checked);

    void on_pb_Mkr_On_toggled(bool checked);

    void on_pb_PeakTrack_clicked(bool checked);

private:
//    void refreshToggleBtn(qint32 status);
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::SA_Dialog_MarkerSingle *ui;
    controlInterface *mControl;
    user_variable *globalUserVariable;
    qint32 mIndex;
};

#endif // SA_DIALOG_MARKERSINGLE_H
