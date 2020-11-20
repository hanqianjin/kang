#ifndef SA_DIALOG_ALLSETUP_H
#define SA_DIALOG_ALLSETUP_H

#include <QWidget>
#include <QDialog>
#include <QMap>
#include <QListView>
#include <QMouseEvent>
class SA_ClickedWidget;
class controlInterface;
class SA_Dialog_DigitInput;
class user_variable;
class SA_Dialog_CH_Std;
namespace Ui {
class SA_Dialog_AllSetup;
}

class SA_Dialog_AllSetup : public QWidget
{
    Q_OBJECT

public:
    explicit SA_Dialog_AllSetup(controlInterface *interface,user_variable *puser_variable,QWidget *parent = 0);
    ~SA_Dialog_AllSetup();
    void mShow();
    void mHide();
private:
    void initMap();
    void initWidget();
    void getKnobValue(qint32 mode);
    void focusControl(qint32 dir);
    void refreshFocus();
    void initDisplay();
    void refreshFreq();
    void refreshAmpt();
    void refreshSweepTime();
    void refreshBW();
    qint32 RatioCompare(qreal ratio);
    qint32 RbwVbwCompare(qint32 value);
    void showInputDialog(qint32 index);
    void dbmToVoltCalculatorAndDisplayFunc(char *label, double _level);
    void dbmToWattsCalculatorAndDisplayFunc(char *label, double _level);
    QString amptTransformToQstring(qint32 unit,qreal value);
    void refreshUnit();
    void refreshTrigger();
    void refreshTrace();
    void refreshMarker();
    void refreshLimit();
    void digitInputClose();
    void channelInputClose();
    void keyPressEvent(QKeyEvent *event);
    qreal getTimeStep(qreal time);
private slots:
    void on_CHfinishEntry();
    void on_widgetclicked();
    void on_widgetFocus();
    void on_finishEntry(qint32 index);
    void on_clicked();

    void on_btn_Preamp_clicked(bool checked);
    void on_Sweep_Conti_clicked(bool checked);
    void on_Sweep_Single_clicked(bool checked);
    void on_RBW_Auto_clicked(bool checked);
    void on_RBW_Manual_clicked(bool checked);
    void on_VBW_Auto_clicked(bool checked);
    void on_VBW_Manual_clicked(bool checked);
    void on_pb_cancel_clicked();
    void on_Marker_Select_clicked();
    void on_Scale_Unit_clicked();
    void on_RBW_Freq_clicked();
    void on_VBW_Freq_clicked();
    void on_VBW_RBW_clicked();
    void on_Trace_Select_clicked();
    void on_Trace_Type_clicked();
    void on_Limit_Select_clicked();
    void on_Detectors_clicked();

    void on_value_Unit_clicked();

    void on_Channel_Uplink_clicked(bool checked);

    void on_Channel_Downlink_clicked(bool checked);

    void on_btn_Preamp_toggled(bool checked);

    void on_value_RBW_currentIndexChanged(qint32 index);
    void on_value_VBW_currentIndexChanged(qint32 index);
    void on_value_VBW_RBW_currentIndexChanged(qint32 index);
    void on_value_Trace_currentIndexChanged(qint32 index);
    void on_value_TraceType_currentIndexChanged(qint32 index);
    void on_value_Detectors_currentIndexChanged(qint32 index);
    void on_value_MarkerSelect_currentIndexChanged(qint32 index);
    void on_value_Unit_currentIndexChanged(qint32 index);
    void on_value_LimitSelect_currentIndexChanged(qint32 index);
    void on_value_MarkerTo_currentIndexChanged(qint32 index);

    void on_value_Detectors_clicked();

    void on_value_RBW_clicked();

    void on_value_VBW_clicked();

    void on_value_VBW_RBW_clicked();

    void on_value_Trace_clicked();

    void on_value_TraceType_clicked();

    void on_value_MarkerSelect_clicked();

    void on_value_LimitSelect_clicked();



    void on_Value_Limit_Toggle_clicked(bool checked);

    void on_Value_Limit_Toggle_toggled(bool checked);

    void on_value_Limit_Edge_Toggle_clicked(bool checked);

    void on_value_Limit_Edge_Toggle_toggled(bool checked);

    void on_Value_Limit_Test_clicked(bool checked);

    void on_Value_Limit_Test_toggled(bool checked);

    void on_btn_Upper_clicked(bool checked);

    void on_btn_Lower_clicked(bool checked);

    void on_btn_MarkerView_clicked(bool checked);

    void on_btn_MarkerView_toggled(bool checked);

    void on_Marker_Normal_clicked(bool checked);

    void on_Marker_Delta_clicked(bool checked);

    void on_btn_FreqCount_clicked(bool checked);

    void on_btn_FreqCount_toggled(bool checked);

    void on_btn_NoiseMarker_clicked(bool checked);

    void on_btn_NoiseMarker_toggled(bool checked);

    void on_btn_TraceView_clicked(bool checked);

    void on_btn_TraceView_toggled(bool checked);

    void on_btn_Average_clicked(bool checked);

    void on_btn_Average_toggled(bool checked);

    void on_Atten_Auto_clicked(bool checked);

    void on_Atten_Manual_clicked(bool checked);

    void on_pb_nextPage_clicked();

    void on_pb_prePage_2_clicked();

    void on_SweepTime_Auto_clicked(bool checked);

    void on_SweepTime_Manual_clicked(bool checked);



    void on_value_MarkerTo_clicked();

    void on_value_TriggerSource_clicked();

    void on_value_TriggerSource_currentIndexChanged(qint32 index);

    void on_value_External_DelayOn_clicked(bool checked);

    void on_value_Peri_DelayOn_clicked(bool checked);

    void on_value_RFBurst_DelayOn_clicked(bool checked);

    void on_value_Video_DelayOn_clicked(bool checked);

    void on_pb_Video_Pos_clicked(bool checked);

    void on_pb_Video_Neg_clicked(bool checked);

    void on_pb_External_Pos_clicked(bool checked);

    void on_pb_External_Neg_clicked(bool checked);

    void on_pb_RFBurst_Pos_clicked(bool checked);

    void on_pb_RFBurst_Neg_clicked(bool checked);



private:
    Ui::SA_Dialog_AllSetup *ui;
    controlInterface *mControl;
    user_variable *globalUserVariable;
    QMap <qint32,SA_ClickedWidget*> mWidgetList;
    QVector <qint32> mInputWidget;
    SA_Dialog_DigitInput *mInputDialog;
    qint32 curWidget,lastWidget;
    qint32 initialPAction;
    SA_Dialog_CH_Std *mChannelInput;
    qint32 mTrIndex;
signals:
    void mDialogHide();
};

#endif // SA_DIALOG_ALLSETUP_H
