#ifndef SA_DIALOG_CHNLPOWERSET_H
#define SA_DIALOG_CHNLPOWERSET_H

#include <sa_lineedit.h>
#include <QWidget>
#include <QKeyEvent>
#include "sa_interface_dialog.h"
class SA_Dialog_DigitInput;
class controlInterface;
class user_variable;

namespace Ui {
class sa_dialog_chnlpowerset;
}

class sa_dialog_chnlpowerset : public QWidget,public sa_interface_dialog
{
    Q_OBJECT

public:
    explicit sa_dialog_chnlpowerset(controlInterface *interface,user_variable *puser_variable,QWidget *parent = 0);
    ~sa_dialog_chnlpowerset();
    void initDisplay();
    void initWidget();
    void showWidget();
    void hideWidget();
    void refreshEditDisplay();
signals:
    void mDialogHide();
private slots:
    void on_lineEdit_clicked();
    void on_finishEntry(qint32 index);
    void on_pb_cancel_2_clicked();
    void on_getFocus(SA_LineEdit* mEdit);
protected slots:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::sa_dialog_chnlpowerset *ui;
    SA_Dialog_DigitInput *mInputDialog;
    controlInterface *mControl;
    user_variable *globalUserVariable;
    void digitInputClose();
    void showInputDialog();
    void getKnobValue(qint32 mode);
    qint32 mCurEdit;
};

#endif // SA_DIALOG_CHNLPOWERSET_H
