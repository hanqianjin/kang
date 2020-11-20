#ifndef PM_DIALOG_CALTABLE_H
#define PM_DIALOG_CALTABLE_H

#include <QWidget>
#include "pm_interface.h"
#include "pm_dialog_digitinput.h"
#include <QKeyEvent>
#include "pm_tablewidget.h"
#include "pm_lineedit.h"

namespace Ui {
class Pm_Dialog_CalTable;
}

class Pm_Dialog_CalTable : public QWidget
{
    Q_OBJECT

public:
    explicit Pm_Dialog_CalTable(BitPm_Interface *BitPmInterface = NULL, Pm_Dialog_Digitinput *mInput = NULL, QWidget *parent = 0);
    ~Pm_Dialog_CalTable();

protected:
    void keyPressEvent(QKeyEvent *event);
private slots:
    void on_finishEntry(qint32 index);
    void on_pb_cancel_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void resetTableSort(qint32 rowIndex);
    void respondKeyEvent(QKeyEvent* event);

    void on_pb_arrayNo_clicked();
    void on_pb_arrayFreq_clicked();
    void on_leArrayIndex_clicked();
    void on_leFreq_clicked();

    void on_finishCal();


    void on_pb_setCalTo_clicked();

public:
    void changeTitleName(QString str);
    void initDisplay();
private:
    void initTable();


private:
    Ui::Pm_Dialog_CalTable *ui;
    BitPm_Interface *PmInterfaceObj;
    Pm_Dialog_Digitinput *mInputDialog;
    QMap <quint32,Pm_LineEdit*> mEditList;

    void showInputDialog(qint32 index);
    void refreshEditDisplay(quint32 index);

    qint32 mColumnIndex;
};

#endif // PM_DIALOG_CALTABLE_H
