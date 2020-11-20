#ifndef SA_DIALOG_LIMIT_H
#define SA_DIALOG_LIMIT_H

#include <QWidget>
#include <QKeyEvent>
#include <QButtonGroup>
#include "sa_interface_dialog.h"
namespace Ui {
class SA_Dialog_Limit;
}
class controlInterface;
class SA_Dialog_LimitTable;
class SA_Dialog_DigitInput;
class SA_Dialog_Limit : public QWidget,public sa_interface_dialog
{
    Q_OBJECT
public:
    explicit SA_Dialog_Limit(controlInterface *interface,QWidget *parent = 0);
    ~SA_Dialog_Limit();
    void refreshTable();

    void initDisplay(); //init display
    void initWidget(); // init control display and hide
    void showWidget();
    void hideWidget();
signals:
    void mDialogHide();
private slots:
    void on_limitDestroyed();
    void on_finishEntry(qint32 index);
    void on_pb_cancel_clicked();

    void on_pb_toggle_clicked(bool checked);
    void on_pb_toggle_toggled(bool checked);

    void on_pb_Edge_clicked(bool checked);
    void on_pb_Edge_toggled(bool checked);

    void on_pb_LimitTest_clicked(bool checked);
    void on_pb_LimitTest_toggled(bool checked);

    void mLimitSelectGroup_click(qint32 index);
    void on_pb_Upper_clicked(bool checked);
    void on_pb_Lower_clicked(bool checked);

    void on_pb_DeleteAll_clicked();

    void on_pb_EditMask_clicked();

    void on_lineEdit_clicked();

private:
    Ui::SA_Dialog_Limit *ui;
    controlInterface *mControl;
    QButtonGroup *mLimitSelectGroup;
    SA_Dialog_LimitTable *mLimitTable;
    SA_Dialog_DigitInput *mInputDialog;

    void initMap();
    void keyPressEvent(QKeyEvent *event);
    void showInputDialog(qint32 index);
    void digitInputClose();
    void getKnobValue(qint32 mode);
};

#endif // SA_DIALOG_LIMIT_H
