#ifndef PM_DIALOG_ALLSETUP_H
#define PM_DIALOG_ALLSETUP_H

#include <QWidget>
#include "pm_interface.h"
#include "pm_dialog_digitinput.h"
#include "pm_clickedwidget.h"
#include "pm_dialog_ch_std.h"
#include "pm_user_variable.h"
#include <QKeyEvent>
#include "pm_combbox.h"

namespace Ui {
class Pm_Dialog_AllSetup;
}

class Pm_Dialog_AllSetup : public QWidget
{
    Q_OBJECT

public:
    explicit Pm_Dialog_AllSetup(BitPm_Interface *BitPmInterface= NULL,Pm_Dialog_Digitinput* input = NULL, QWidget *parent = 0);
    ~Pm_Dialog_AllSetup();
protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_finishEntry(qint32 index);
    void on_pb_cancel_clicked();

private slots:
    void on_clicked();
    void on_Combclicked();
    void on_CHStdClose();

    void on_value_Span_Type_currentIndexChanged(int index);

    void on_Channel_UpLink_clicked();
    void on_Channel_DownLink_clicked();
    void on_btn_Freq_Offset_toggled(bool checked);

    void on_Auto_Scale_clicked();
    void on_btn_Ampt_Forward_clicked(bool checked);
    void on_Ampt_Set_Forward_clicked();
    void on_btn_Ampt_Reverse_clicked(bool checked);
    void on_Ampt_Set_Reverse_clicked();

    void on_value_Unit_currentIndexChanged(int index);
    void on_Sweep_Conti_clicked();
    void on_Sweep_Single_clicked();
    void on_value_Avg_Acq_currentIndexChanged(int index);
    void on_btn_Max_Hold_toggled(bool checked);
    void on_Zero_clicked();
    void on_btn_Limit_Show_toggled(bool checked);
    void on_value_Vido_BW_currentIndexChanged(int index);

    void on_value_Display_Forward_activated(int index);
    void on_value_Display_Reverse_activated(int index);
    void on_Display_Summay_clicked();

private:
    void refreshBtnInfo();
    void digitInputClose();
    void showCHStdDialog();

    void refreshFreq();
    void refreshAmpt();
    void refreshUnit();
    void refreshSweep();
    void refreshAvg();
    void refreshZero();
    void refreshLimit();
    void refreshDisplay();

public:
    void initDisplay();
private:
    void initMap();
    void showInputDialog(qint32 index);

private slots:
    void refreshEditDisplay(qint32 index);


    void on_btn_Average_Running_toggled(bool checked);


private:
    Ui::Pm_Dialog_AllSetup *ui;
     BitPm_Interface *PmInterfaceObj;
    Pm_Dialog_Digitinput *mInputDialog;
    QMap <qint32,Pm_ClickedWidget*> mWidgetList;
    QMap <qint32,Pm_CombBox*> mCombList;
    Pm_Dialog_Ch_Std *mChStdDialog;

    qint32 mLastWidgetID;
    qint32 mLastCombID;

};

#endif // PM_DIALOG_ALLSETUP_H
