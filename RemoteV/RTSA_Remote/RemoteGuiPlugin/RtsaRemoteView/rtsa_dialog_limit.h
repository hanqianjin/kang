#ifndef RTSA_DIALOG_OBSERVE_H
#define RTSA_DIALOG_OBSERVE_H

#include <QWidget>
#include "rtsa_remote_interface.h"
#include "rtsa_dialog_digitinput.h"
#include "rtsa_lineedit.h"
#include <QKeyEvent>
#include <QButtonGroup>
#include "rtsa_dialog_limittable.h"
#include <QTimer>
namespace Ui {
class RtSa_Dialog_Limit;
}

class RtSa_Dialog_Limit : public QWidget
{
    Q_OBJECT

public:
    explicit RtSa_Dialog_Limit(Rtsa_Remote_Interface *RtsaRemoteInterface= NULL,RtSa_Dialog_Digitinput* input = NULL, QWidget *parent = 0);
    ~RtSa_Dialog_Limit();

    void BuildLimitFromTrace();
    void initDisplay();
    void HideTableWidget();
protected:
    void keyPressEvent(QKeyEvent *event);
private slots:
    void on_finishEntry(qint32 index);

    void on_pb_cancel_clicked();

    void on_leMargin_clicked();

    void mLimitSelectGroup_click(int index);

//    void on_pbInsertRow_clicked();

    void DigitalKeyRespond(QKeyEvent *event);

    void on_pb_toggle_toggled(bool checked);

    void on_pb_EditMask_clicked();

    void on_limitDestroyed();

//    void on_lineEdit_clicked();

    void on_pb_Edge_toggled(bool checked);

    void on_pb_LimitTest_toggled(bool checked);

    void on_pb_Upper_clicked();

    void on_pb_Lower_clicked();

    void on_pb_DeleteAll_clicked();

    void on_Update();

    void on_timeOut();

private:
    Ui::RtSa_Dialog_Limit *ui;
    Rtsa_Remote_Interface *RemoteInterfaceObj;
    RtSa_Dialog_Digitinput *mInputDialog;
    QMap <quint32,RtSa_LineEdit*> mEditList;

    void initMap();
    void initButtonDisplay();
    void refreshEditDisplay(quint32 index);
    void refreshButtonDisplay();
    void showInputDialog(qint32 index);
    qint32 mSelectInputID;
    QButtonGroup *mLimitSelectGroup;
    RtSa_Dialog_LimitTable *mLimitTable;
    QTimer *timer;
    qint32 mUpDownFlag;
};

#endif // RTSA_DIALOG_OBSERVE_H
