#ifndef SA_DIALOG_DISPLAYSETUP_H
#define SA_DIALOG_DISPLAYSETUP_H

#include <sa_lineedit.h>
#include <QWidget>
#include <QDialog>
#include <QMap>
#include <QDebug>
#include <QListView>
#include <QKeyEvent>
#include "sa_interface_dialog.h"

class SA_Dialog_DigitInput;
class controlInterface;
class user_variable;
class SA_Combobox;
class sa_dialog_doorcontrol;
namespace Ui {
class SA_Dialog_DisplaySetup;
}

class SA_Dialog_DisplaySetup : public QWidget,public sa_interface_dialog
{
    Q_OBJECT

public:
    explicit SA_Dialog_DisplaySetup(controlInterface *interface,user_variable *puser_variable,QWidget *parent = 0);
    ~SA_Dialog_DisplaySetup();
    void initDisplay(); //init display
    void initWidget(); // init control display and hide
    void showWidget();
    void hideWidget();
private slots:
    void on_finishEntry(qint32 index);

    void on_pb_conti_clicked();

    void on_pb_single_clicked();

    void on_pb_cancel_clicked();

    void on_pb_SweepTime_Auto_clicked();

    void on_pb_SweepTime_Manual_clicked();

    void on_edit_SweepTime_clicked();

    void on_getFocus(SA_LineEdit* mEdit);
    void on_getComboBoxFocus(SA_Combobox*);
    void on_pb_Sweep_Once_clicked();
    void keyPressEvent(QKeyEvent *event);
    void on_edit_DotSweepTime_clicked();

    void on_pb_DotSweepTime_Auto_clicked();

    void on_pb_DotSweepTime_Manual_clicked();

    void on_pb_FixedDotSweepTime_clicked();

    void on_pb_FixedDotSweepTime_toggled(bool checked);

    void on_pb_DoorCtrlSweep_clicked();
    void subMenuDestroy();
    void gateSweepCancel();
private:
    Ui::SA_Dialog_DisplaySetup *ui;
    SA_Dialog_DigitInput *mInputDialog;
    controlInterface *mControl;
    user_variable *globalUserVariable;
    QMap <quint32,SA_LineEdit*> mEditList;
    QMap <quint32,SA_Combobox*> mBoxList;
    qint32 mCurEdit;

    void initMap();
    void refreshEditDisplay(quint32 index);
    void refreshButtonDisplay();
    void showInputDialog(qint32 index);
    void getKnobValue(qint32 mode);
    qreal getTimeStep(qreal time);

signals:
    void mDialogHide();
public:
    void gateSweepDisplay();
    sa_dialog_doorcontrol *mDoorControl;
};
#endif // SA_DIALOG_DISPLAYSETUP_H
