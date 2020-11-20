#ifndef RTSA_DIALOG_TRIGGERSETUP_H
#define RTSA_DIALOG_TRIGGERSETUP_H

#include <QWidget>
#include <QButtonGroup>
#include "rtsa_remote_interface.h"
#include "rtsa_dialog_digitinput.h"
#include "rtsa_dialog_fmttable.h"
#include "rtsa_combbox.h"
#include "rtsa_lineedit.h"

enum{
    RTSA_VIDEO_LEVEL = 2,
    RTSA_VIDEO_DELAY_VALUE,
    RTSA_EXTERNAL_LEVEL,
    RTSA_EXTERNAL_DELAY_VALUE,
    RTSA_PERI_TIME,
    RTSA_PERI_TIME_DELAY_VALUE,
    RTSA_RFBURST_LEVEL,
    RTSA_RFBURST_DELAY_VALUE,
    RTSA_VIDEO_HOLDOFF,
    RTSA_EXTERN_HOLDOFF,
    RTSA_RFBURST_HOLDOFF,
    RTSA_FMT_HOLDOFF,
};

namespace Ui {
class RtSa_Dialog_TriggerSetup;
}

class RtSa_Dialog_TriggerSetup : public QWidget
{
    Q_OBJECT

public:
    explicit RtSa_Dialog_TriggerSetup( Rtsa_Remote_Interface *RtsaRemoteInterface = NULL,RtSa_Dialog_Digitinput *input = NULL, QWidget *parent = 0);
    ~RtSa_Dialog_TriggerSetup();
    void initDisplay();
    void HideTableWidget();
private slots:
    void btnclicked(qint32 mode);
//    void on_pb_cancel_clicked();
    void on_finishEntry(qint32 index);

    void on_limitDestroyed();

    void on_TriggerTypeBox_currentIndexChanged(int index);
    void on_getComboBoxFocus(RtSa_CombBox* mBox);
    void on_getFocus(RtSa_LineEdit* mEdit);
    void edit_clicked();
    void on_pb_External_DelayOn_clicked(bool checked);

    void on_pb_PeriTime_DelayOn_clicked(bool checked);

    void on_pb_RFBurst_DelayOn_clicked(bool checked);

    void on_pb_Video_DelayOn_clicked(bool checked);

    void on_pb_RFBurst_Pos_clicked(bool checked);

    void on_pb_RFBurst_Neg_clicked(bool checked);

    void on_pb_Video_Pos_clicked(bool checked);

    void on_pb_Video_Neg_clicked(bool checked);

    void on_pb_External_Pos_clicked(bool checked);

    void on_pb_External_Neg_clicked(bool checked);

    void on_pb_cancel_2_clicked();

    void on_pb_FMTNew_clicked();

    void on_pb_FMTUpper_clicked();

    void on_pb_FMTLower_clicked();

    void on_pb_FMTBuildFromTrace_clicked();

    void on_pb_FMTBuildFromTrace_2_clicked();

    void on_TriggerCriterion_currentIndexChanged(int index);

private:
    Ui::RtSa_Dialog_TriggerSetup *ui;
      Rtsa_Remote_Interface *RemoteInterfaceObj;
    qint32 mCurEdit;
    QMap <qint32,RtSa_CombBox*> mBoxList;
    QMap <quint32,RtSa_LineEdit*> mEditList;
    RtSa_Dialog_Digitinput* mInputDialog;

    void initMap();
    void refreshSubmenuDisplay();
    void refreshComBoBox();
    void keyPressEvent(QKeyEvent *event);
    void showInputDialog(qint32 index);
    void digitInputClose();
    RtSa_Dialog_FmtTable* mFmtTable;
};

#endif // RTSA_DIALOG_TRIGGERSETUP_H
