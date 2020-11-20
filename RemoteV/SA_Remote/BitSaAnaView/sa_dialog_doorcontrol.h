#ifndef SA_DIALOG_DOORCONTROL_H
#define SA_DIALOG_DOORCONTROL_H

#include <sa_lineedit.h>
#include <QWidget>
#include <QDialog>
#include <QMap>
#include <QButtonGroup>
#include <QDebug>
#include <QKeyEvent>
#include "sa_combobox.h"


class SA_Dialog_DigitInput;
class controlInterface;

namespace Ui {
class sa_dialog_doorcontrol;
}

class sa_dialog_doorcontrol : public QWidget
{
    Q_OBJECT

public:
    explicit sa_dialog_doorcontrol(controlInterface *interface, QWidget *parent = 0);
    ~sa_dialog_doorcontrol();
    void initDisplay();

private slots:
    void on_DoorControlSourceBox_currentIndexChanged(int index);

    void on_pb_External_Level_clicked();

    void on_pb_External_Edge_clicked();

    void on_pb_External_Low_clicked();

    void on_pb_External_High_clicked();

    void on_Extern_SweepModeBox_currentIndexChanged(int index);

    void on_pb_Extern_PreventStatus_clicked(bool checked);

    void on_pb_RFBurst_Level_clicked();

    void on_pb_RFBurst_Edge_clicked();

    void on_pb_RFBurst_Low_clicked();

    void on_pb_RFBurst_High_clicked();

    void on_RFBurst_SweepModeBox_currentIndexChanged(int index);

    void on_pb_RFBurst_Sweep_Switch_clicked(bool checked);

    void on_pb_RFBurst_PreventStatus_clicked(bool checked);

    void on_pb_Period_Low_clicked(bool checked);

    void on_pb_Period_High_clicked(bool checked);

    void on_Period_SweepModeBox_currentIndexChanged(int index);

    void on_Period_SynchSourceBox_currentIndexChanged(int index);

    void on_Period_Sweep_Switch_clicked(bool checked);

    void on_pb_Period_PreventStatus_clicked(bool checked);

    void on_pb_Period_SynSrcPreventStatus_clicked(bool checked);

    void on_pb_cancel_clicked();
    void on_finishEntry(qint32 index);

    void on_getComboBoxFocus(SA_Combobox* mBox);
    void on_getFocus(SA_LineEdit* mEdit);
    void edit_clicked();

    void on_pb_Extern_Sweep_Switch_clicked(bool checked);

    void on_pb_Extern_GateViewStatus_clicked(bool checked);

    void on_pb_RFBurst_GateViewStatus_clicked(bool checked);

    void on_pb_Period_GateViewStatus_clicked(bool checked);

private:
    Ui::sa_dialog_doorcontrol *ui;

    controlInterface *mControl;
    qint32 mCurEdit;
    QMap <qint32,SA_Combobox*> mBoxList;
    QMap <quint32,SA_LineEdit*> mEditList;
    SA_Dialog_DigitInput* mInputDialog;
    enum{
        SA_EXTERN_TRIGGER_DELAY = 2,
        SA_EXTERN_DOORWIDTH,
        SA_EXTERN_PREVENT_TIME,
        SA_RFBURST_TRIGGER_DELAY,
        SA_RFBURST_DOORWIDTH,
        SA_RFBURST_PREVENT_TIME,
        SA_RFBURST_TRIGGER_LEVEL,
        SA_PERI_TRIGGER_DELAY,
        SA_PERI_DOOR_WIDTH,
        SA_PERI_PREVENT_TIME,
        SA_PERI_PERIOD,
        SA_PERI_SYN_SOURCE_DELAY,
        SA_PERI_SYN_SOURCE_PREVENT_TIME,
        SA_EXTERN_GATEVIEW_STARTTIME,
        SA_RFBURST_GATEVIEW_STARTTIME,
        SA_PERI_GATEVIEW_STARTTIME
    };
    enum{
        SA_COMBOBOX_DOORCONTROL_SOURCE = -1,
        SA_COMBOBOX_EXTERN_SWEEP_MODE = -2,
        SA_COMBOBOX_REBURST_SWEEP_MODE = -3,
        SA_COMBOBOX_PERI_SWEEP_MODE = -4,
        SA_COMBOBOX_PERI_SYN_SOURCE = -5,
    };
    void initMap();
    void refreshSubmenuDisplay();
    void refreshComBoBox();
    void refreshButton();
    void keyPressEvent(QKeyEvent *event);
    void showInputDialog(qint32 index);
    void getKnobValue(qint32 mode);
    qreal getTimeStep(qreal time);
};

#endif // SA_DIALOG_DOORCONTROL_H
