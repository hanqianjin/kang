#ifndef SA_DIALOG_BWSETUP_H
#define SA_DIALOG_BWSETUP_H

#include <sa_lineedit.h>
#include <QDialog>
#include <QMap>
#include <QPointer>
#include <QDebug>
#include <stdio.h>
#include <QKeyEvent>
#include "sa_interface_dialog.h"

class SA_Dialog_DigitInput;
class controlInterface;
class user_variable;
class SA_Combobox;
namespace Ui {
class SA_Dialog_BWSetup;
}

class SA_Dialog_BWSetup : public QWidget,public sa_interface_dialog
{
    Q_OBJECT
public:
    explicit SA_Dialog_BWSetup(controlInterface *interface, user_variable *puser_variable,QWidget *parent = 0);
    ~SA_Dialog_BWSetup();
    void initDisplay(); //init display
    void initWidget(); // init control display and hide
    void showWidget();
    void hideWidget();
signals:
    void mDialogHide();
private slots:
    void on_finishEntry(qint32 index);
    void edit_clicked();
    void on_RBWAutoPB_clicked();
    void on_RBWManualPB_clicked();
    void on_VBWAutoPB_clicked();
    void on_VBWManualPB_clicked();
    void on_pb_cancel_clicked();
    void on_RBWBox_currentIndexChanged(qint32 index);
    void on_VBWBox_currentIndexChanged(qint32 index);
    void on_ratioBox_currentIndexChanged(QString text);
    void on_getFocus(SA_LineEdit* mEdit);
    void on_getComboBoxFocus(SA_Combobox* mBox);
    void keyPressEvent(QKeyEvent *event);
    void on_IF_OutPut_Box_currentIndexChanged(qint32 index);
private:
    void RBWEdit_clicked();
    void VBWEdit_clicked();

    Ui::SA_Dialog_BWSetup *ui;
    SA_Dialog_DigitInput* mInputDialog;
    controlInterface *mControl;
    user_variable *globalUserVariable;
    qint32 mCurEdit;
    QMap <quint32,SA_LineEdit*> mEditList;
    QMap <quint32,SA_Combobox*> mBoxList;

    void initMap();
    void refreshEditDisplay(quint32 index);
    void refreshButtonDisplay();
    void showInputDialog(qint32 index);
    void digitInputClose();
    qint32 RbwVbwCompare(qint32 value);
    void refreshComboboxDisplay();
    void getKnobValue(qint32 mode);
    qint32 RatioCompare(qreal ratio);
};
#endif // SA_DIALOG_BWSETUP_H
