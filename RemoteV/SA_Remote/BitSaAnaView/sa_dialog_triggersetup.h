#ifndef SA_DIALOG_TRIGGERSETUP_H
#define SA_DIALOG_TRIGGERSETUP_H

#include <sa_lineedit.h>
#include <QWidget>
#include <QDialog>
#include <QMap>
#include <QButtonGroup>
#include <QDebug>
#include <QKeyEvent>
#include "sa_combobox.h"
#include "sa_interface_dialog.h"

class SA_Dialog_DigitInput;
class controlInterface;
namespace Ui {
class SA_Dialog_TriggerSetup;
}

class SA_Dialog_TriggerSetup : public QWidget,public sa_interface_dialog
{
    Q_OBJECT
public:
    explicit SA_Dialog_TriggerSetup(controlInterface *interface, QWidget *parent = 0);
    ~SA_Dialog_TriggerSetup();
    void initDisplay(); //init display
    void initWidget();  // init control display and hide
    void showWidget();
    void hideWidget();
signals:
    void mDialogHide();
private slots:
    void btnclicked(qint32 mode);
    void on_pb_cancel_clicked();
    void on_finishEntry(qint32 index);
    void on_TriggerTypeBox_currentIndexChanged(int index);
    void on_getComboBoxFocus(SA_Combobox* mBox);
    void on_getFocus(SA_LineEdit* mEdit);
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

private:
    Ui::SA_Dialog_TriggerSetup *ui;
    controlInterface *mControl;
    qint32 mCurEdit;
    QMap <qint32,SA_Combobox*> mBoxList;
    QMap <quint32,SA_LineEdit*> mEditList;
    SA_Dialog_DigitInput* mInputDialog;
    enum{
        SA_VIDEO_LEVEL = 2,
        SA_VIDEO_DELAY_VALUE,
        SA_EXTERNAL_LEVEL,
        SA_EXTERNAL_DELAY_VALUE,
        SA_PERI_TIME,
        SA_PERI_TIME_DELAY_VALUE,
        SA_RFBURST_LEVEL,
        SA_RFBURST_DELAY_VALUE,
    };
    void initMap();
    void refreshSubmenuDisplay();
    void refreshComBoBox();
    void keyPressEvent(QKeyEvent *event);
    void showInputDialog(qint32 index);
    void digitInputClose();
    void getKnobValue(qint32 mode);
    qreal getTimeStep(qreal time);
};
#endif // SA_DIALOG_TRIGGERSETUP_H
