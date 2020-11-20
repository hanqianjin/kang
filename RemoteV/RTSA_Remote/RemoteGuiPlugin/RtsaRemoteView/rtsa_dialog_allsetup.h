#ifndef RTSA_DIALOG_ALLSETUP_H
#define RTSA_DIALOG_ALLSETUP_H

#include <QWidget>
#include "rtsa_remote_interface.h"
#include "rtsa_dialog_digitinput.h"
#include "rtsa_clickedwidget.h"
#include "rtsa_dialog_ch_std.h"
#include "rtsa_user_variable.h"
#include <QKeyEvent>
#include "rtsa_combbox.h"

namespace Ui {
class RtSa_Dialog_AllSetup;
}

class RtSa_Dialog_AllSetup : public QWidget
{
    Q_OBJECT

public:
    explicit RtSa_Dialog_AllSetup(Rtsa_Remote_Interface *RtsaRemoteInterface= NULL,RtSa_Dialog_Digitinput* input = NULL, QWidget *parent = 0);
    ~RtSa_Dialog_AllSetup();
    void initDisplay();
protected:
    void keyPressEvent(QKeyEvent *event);
private:
    void initMap();
    void showInputDialog(qint32 index);
    void refreshBtnInfo();
    void refreshDisplay(qint32 index);
    void dbmToVoltCalculatorAndDisplayFunc(char *label, double _level);
    void dbmToWattsCalculatorAndDisplayFunc(char *label, double _level);
    QString amptTransformToQstring(qint32 unit,qreal value);
    void refreshUnit();
    void digitInputClose();
    void showCHStdDialog();

    //Albert 19/04/19
    void refreshFreq();
    void refreshAmpt();
    void refreshSweep();
    void refreshBW();
    void refreshTrigger();
    void refreshTrace();
    void refreshMarker();
    void refreshLimit();
    void refreshDisplay();
private slots:
    void on_Span_Full_clicked();

    void on_pb_cancel_clicked();

//    void on_leCenterFreq_clicked();

    void on_clicked();
    void on_Combclicked();

    void refreshEditDisplay(qint32 index);

    void on_CHStdClose();

    void on_finishEntry(qint32 index);

    void on_pb_nextPage_clicked();

    void on_pb_prePage_2_clicked();

    void on_Auto_Scale_clicked();

    void on_value_Unit_currentIndexChanged(int index);

    void on_Atten_Auto_clicked();

    void on_Atten_Manual_clicked();

    void on_btn_Preamp_toggled(bool checked);

    void on_Sweep_Conti_clicked();

    void on_Sweep_Single_clicked();

    void on_value_RBW_currentIndexChanged(int index);

    void on_value_VBW_currentIndexChanged(int index);

    void on_RBW_Auto_clicked();

    void on_RBW_Manual_clicked();

    void on_value_Trace_currentIndexChanged(int index);

//    void on_btn_Average_toggled(bool checked);

    void on_btn_TraceView_toggled(bool checked);

    void on_value_MarkerSelect_currentIndexChanged(int index);

    void on_btn_MarkerView_toggled(bool checked);

    void on_btn_MarkerView_2_toggled(bool checked);

    void on_btn_NoiseMarker_toggled(bool checked);

    void on_value_TraceType_currentIndexChanged(int index);

    void on_value_Trigger_currentIndexChanged(int index);

private:
    Ui::RtSa_Dialog_AllSetup *ui;
     Rtsa_Remote_Interface *RemoteInterfaceObj;
    RtSa_Dialog_Digitinput *mInputDialog;
    QMap <qint32,RtSa_ClickedWidget*> mWidgetList;
    QMap <qint32,RtSa_CombBox*> mCombList;
    RtSa_Dialog_Ch_Std *mChStdDialog;
    RtSa_User_Variable* mUserVariable;
    qint32 mLastWidgetID;
    qint32 mLastCombID;

};

#endif // RTSA_DIALOG_ALLSETUP_H
