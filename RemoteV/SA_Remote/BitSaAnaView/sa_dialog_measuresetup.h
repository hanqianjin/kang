#ifndef SA_DIALOG_MEASURESETUP_H
#define SA_DIALOG_MEASURESETUP_H

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

namespace Ui {
class SA_Dialog_MeasureSetup;
}

class SA_Dialog_MeasureSetup : public QWidget,public sa_interface_dialog
{
    Q_OBJECT

public:
    explicit SA_Dialog_MeasureSetup(controlInterface *interface, user_variable *puser_variable,QWidget *parent = 0);
    ~SA_Dialog_MeasureSetup();
    void initDisplay(); //init display
    void initWidget(); // init control display and hide
    void showWidget();
    void hideWidget();
private slots:
    void on_finishEntry(qint32 index);

    void on_pb_cancel_clicked();

    void runBtnFunction(qint32 menuID);

private:
    Ui::SA_Dialog_MeasureSetup *ui;
    SA_Dialog_DigitInput *mInputDialog;
    controlInterface *mControl;
    user_variable *globalUserVariable;
    QMap <quint32,SA_LineEdit*> mEditList;
    QButtonGroup *mBtnGroup;

    void keyPressEvent(QKeyEvent *event);
    void initMap();
    void refreshEditDisplay(quint32 index);
    void refreshButtonDisplay();
    void showInputDialog(qint32 index);
signals:
    void mDialogHide();
};
#endif // SA_DIALOG_MEASURESETUP_H
