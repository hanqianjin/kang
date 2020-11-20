#ifndef SA_DIALOG_LIMITTABLE_H
#define SA_DIALOG_LIMITTABLE_H

#include <QWidget>
#include <QKeyEvent>
#include <QScrollBar>
#include "sa_lineedit.h"
class controlInterface;
class SA_Dialog_DigitInput;
namespace Ui {
class SA_Dialog_LimitTable;
}

class SA_Dialog_LimitTable : public QWidget
{
    Q_OBJECT

public:
    explicit SA_Dialog_LimitTable(controlInterface *interface,QWidget *parent = 0);
    ~SA_Dialog_LimitTable();
    void initTable();
private slots:
    void keyPressEvent(QKeyEvent *event);
    void digitInputClose();
    void on_finishEntry(qint32 index);
    void on_pb_InsertRow_clicked();

    void on_pb_DeleteRow_clicked();

    void on_pb_DeleteLimit_clicked();

    void on_pb_cancel_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_getFocus(SA_LineEdit* mEdit);
    void on_tableWidget_clicked();

    void on_tableWidget_cellChanged(int row, int column);

    void on_LED_CurPtIndex_clicked();

private:
    Ui::SA_Dialog_LimitTable *ui;
    controlInterface *mControl;
    SA_Dialog_DigitInput *mInputDialog;
    QWidget *mParent;
    qint32 mCurEdit;
    qint32 curColum;
    void showInputDialog(qint32 index);
    void initDisplay();
    void initWidget();
    void tabelChange(qint32 step);
    void getKnobValue(qint32 mode);
    void getEditKnobValue(qint32 mode);
    void refreshLineEdit();
};

#endif // SA_DIALOG_LIMITTABLE_H
