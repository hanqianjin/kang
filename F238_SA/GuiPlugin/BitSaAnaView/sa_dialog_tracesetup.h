#ifndef SA_DIALOG_TRACESETUP_H
#define SA_DIALOG_TRACESETUP_H

#include <sa_lineedit.h>
#include <QWidget>
#include <QDialog>
#include <QMap>
#include <QDebug>
#include <QButtonGroup>
#include <QComboBox>
#include <QListView>
#include <QKeyEvent>
#include "sa_interface_dialog.h"

class SA_Dialog_DigitInput;
class controlInterface;
class SA_Combobox;
namespace Ui {
class SA_Dialog_TraceSetup;
}

class SA_Dialog_TraceSetup : public QWidget,public sa_interface_dialog
{
    Q_OBJECT

public:
    explicit SA_Dialog_TraceSetup(controlInterface *interface, QWidget *parent = 0);
    ~SA_Dialog_TraceSetup();
    void initDisplay(); //init display
    void initWidget();  // init control display and hide
    void showWidget();
    void hideWidget();
signals:
    void mDialogHide();
private slots:
    void mTraceSelectGroup_click(qint32 index);
    void on_pb_cancel_clicked();

    void on_pb_toggle_clicked(bool checked);

    void on_TR_Detector_currentIndexChanged(qint32 index);

    void on_TR_Type_activated(qint32 index);
    void on_getComboBoxFocus(SA_Combobox* mBox);
    void on_getFocus(SA_LineEdit* mEdit);
    void on_pb_toggle_Ave_clicked(bool checked);
    void on_finishEntry(qint32 index);
    void on_averageEdit_clicked();
    void keyPressEvent(QKeyEvent *event);
    void on_pb_traceAllOn_clicked();

    void on_pb_clearall_clicked();

private:
    Ui::SA_Dialog_TraceSetup *ui;
    controlInterface *mControl;
    QButtonGroup *mTraceSelectGroup;
    qint32 mCurEdit;
    QMap <qint32,SA_Combobox*> mBoxList;
    QMap <quint32,SA_LineEdit*> mEditList;
    SA_Dialog_DigitInput* mInputDialog;
    qint32 mTrIndex;

    void initMap();
    void setTraceType(qint32 traceIndex,qint32 type);
    void setDetector(qint32 index);
    void refreshDetectorInfo();
    void refreshTypeInfo(qint32 traceIndex = -1);
    void traceSelect(qint32 index);
    void blockSignal(qint32 status);
    void refreshToggleBtn(qint32 index,qint32 status);
    void showInputDialog(qint32 index);
    void refreshEditDisplay(quint32 index,quint32 traceindex = 0);
    void getKnobValue(qint32 mode);
};
#endif // SA_DIALOG_TRACESETUP_H
