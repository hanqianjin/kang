#ifndef SA_DIALOG_SPECEM_H
#define SA_DIALOG_SPECEM_H

#include <QWidget>
#include <QKeyEvent>
#include "sa_interface_dialog.h"
class controlInterface;

namespace Ui {
class SA_Dialog_SpecEM;
}

class SA_Dialog_SpecEM : public QWidget,public sa_interface_dialog
{
    Q_OBJECT

public:
    explicit SA_Dialog_SpecEM(controlInterface *interface,QWidget *parent = 0);
    ~SA_Dialog_SpecEM();
    void initDisplay(); //init display
    void initWidget();  // init control display and hide
    void showWidget();
    void hideWidget();
signals:
    void mDialogHide();
private slots:
    void on_pb_Display_Abs_clicked();

    void on_pb_Display_Ref_clicked();

    void on_pb_Display_IntePwr_clicked();

    void on_pb_ref_TotalPwr_clicked();

    void on_pb_ref_PSD_clicked();

    void on_pb_ref_SpecPk_clicked();

    void on_pb_cancel_clicked();

private:
    Ui::SA_Dialog_SpecEM *ui;
    controlInterface *mControl;
    void keyPressEvent(QKeyEvent *event);
};

#endif // SA_DIALOG_SPECEM_H
