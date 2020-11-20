#ifndef SA_DIALOG_AMPTSETUP_H
#define SA_DIALOG_AMPTSETUP_H

#include <sa_lineedit.h>
#include <QWidget>
#include <QDialog>
#include <QMap>
#include <QDebug>
#include <QButtonGroup>
#include <QKeyEvent>
#include "sa_interface_dialog.h"

class SA_Dialog_DigitInput;
class controlInterface;
class user_variable;
class SA_Combobox;
namespace Ui {
class SA_Dialog_AmptSetup;
}

class SA_Dialog_AmptSetup : public QWidget,public sa_interface_dialog
{
    Q_OBJECT

public:
    explicit SA_Dialog_AmptSetup(controlInterface *interface,user_variable *puser_variable,QWidget *parent = 0);
    ~SA_Dialog_AmptSetup();
    void refreshEditDisplay(quint32 index);

    void initDisplay(); //init display
    void initWidget(); // init control display and hide
    void showWidget();
    void hideWidget();
private slots:
    void on_finishEntry(qint32 index);
    void edit_clicked();
    void on_pb_Scale_Auto_clicked();
    void unitSelect(qint32 unit);
    void on_pb_Preamp_clicked();

    void on_pb_cancel_clicked();

    void on_pb_Preamp_toggled(bool checked);
    void on_getFocus(SA_LineEdit* mEdit);
    void on_getComboBoxFocus(SA_Combobox* mBox);
    void keyPressEvent(QKeyEvent *event);
    void on_pb_Auto_clicked(bool checked);

    void on_pb_Manual_clicked(bool checked);
private:
    Ui::SA_Dialog_AmptSetup *ui;
    SA_Dialog_DigitInput *mInputDialog;
    controlInterface *mControl;
    user_variable *globalUserVariable;
    QMap <quint32,SA_LineEdit*> mEditList;
    QMap <qint32,SA_Combobox*> mBoxList;
    qint32 mCurEdit;

    void initMap();
    void refreshButtonDisplay();
    void showInputDialog(qint32 index);
    QString amptTransformToQstring(qint32 unit,qreal value);
    void digitInputClose();
    void getKnobValue(qint32 mode);
signals:
    void mDialogHide();
};
#endif // SA_DIALOG_AMPTSETUP_H
