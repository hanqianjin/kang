#ifndef RTSA_DIALOG_LIMITTABLE_H
#define RTSA_DIALOG_LIMITTABLE_H

#include <QWidget>
#include "rtsa_interface.h"
#include "rtsa_dialog_digitinput.h"
#include <QKeyEvent>
#include "rtsa_tablewidget.h"
#include "rtsa_interface.h"
enum
{
   RTSA_TYPE_LIMIT = 0,
   RTSA_TYPE_FMT
};
namespace Ui {
class RtSa_Dialog_LimitTable;
}

class RtSa_Dialog_LimitTable : public QWidget
{
    Q_OBJECT

public:
    explicit RtSa_Dialog_LimitTable(RtSa_Interface *interface = NULL, RtSa_Dialog_Digitinput *mInput = NULL, QWidget *parent = 0);
    ~RtSa_Dialog_LimitTable();
    void initTable();

    void changeTitleName(QString str);
    void changeButtonName(QString str);

    // type 0 means show LIMIT, 1 means show FMT
    void setShowType(qint32 type);

protected:
    void keyPressEvent(QKeyEvent *event);
private slots:
//    void digitInputClose();
    void on_finishEntry(qint32 index);
    void on_pb_InsertRow_clicked();

    void on_pb_DeleteRow_clicked();

    void on_pb_DeleteLimit_clicked();

    void on_pb_cancel_clicked();

    void on_tableWidget_cellClicked(int row, int column);

//    void on_pb_close_clicked();

//    void on_pb_ok_clicked();

    void resetTableSort(qint32 rowIndex);

    void on_LED_CurPtIndex_clicked();

    void respondKeyEvent(QKeyEvent* event);

private:
    Ui::RtSa_Dialog_LimitTable *ui;
    RtSa_Interface *mControl;
    RtSa_Dialog_Digitinput *mInputDialog;

    void showInputDialog(qint32 index);
//    void tabelChange(qint32 step);
    void refreshEditDisplay(quint32 index);
    void refreshCurRowIndex();
    void refreshLimitData();
    qreal* mLimitFreq;
    qreal* mLimitAmpt;
    qint32 mColumnIndex;
    qint32 mShowType;
};

#endif // RTSA_DIALOG_LIMITTABLE_H
