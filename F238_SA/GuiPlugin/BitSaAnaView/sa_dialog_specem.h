#ifndef SA_DIALOG_SPECEM_H
#define SA_DIALOG_SPECEM_H

#include <QWidget>
#include <QKeyEvent>
#include "sa_interface_dialog.h"

#include "sa_lineedit.h"
#include "sa_combobox.h"
#include "sa_dialog_digitinput.h"
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

    void on_MaskBox_currentIndexChanged(qint32 index);

    void on_DisplayBox_currentIndexChanged(qint32 index);

    void on_RefBox_currentIndexChanged(qint32 index);

    void on_getComboBoxFocus(SA_Combobox* mBox);
    void on_ChBwEdit_clicked();

    void on_BSPowerEdit_clicked();
    void on_getFocus(SA_LineEdit* mEdit);
    void on_finishEntry(qint32 index);
private:
    void getKnobValue(qint32 mode);
    void showInputDialog(qint32 index);
    SA_Dialog_DigitInput *mInputDialog;
    qint32 mCurEdit;
    QMap <quint32,SA_LineEdit*> mEditList;
    QMap <quint32,SA_Combobox*> mBoxList;

    Ui::SA_Dialog_SpecEM *ui;
    controlInterface *mControl;
    void keyPressEvent(QKeyEvent *event);
    void initMap();
    void refreshEditDisplay();
};

#endif // SA_DIALOG_SPECEM_H
