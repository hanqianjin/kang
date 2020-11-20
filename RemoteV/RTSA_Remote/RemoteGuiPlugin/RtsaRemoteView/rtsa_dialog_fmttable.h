#ifndef RTSA_DIALOG_FMTTABLE_H
#define RTSA_DIALOG_FMTTABLE_H

#include <QWidget>
#include "rtsa_dialog_digitinput.h"
#include "rtsa_remote_interface.h"
#include <QKeyEvent>
#include "rtsa_tablewidget.h"
namespace Ui {
class RtSa_Dialog_FmtTable;
}

class RtSa_Dialog_FmtTable : public QWidget
{
    Q_OBJECT

public:
    explicit RtSa_Dialog_FmtTable(Rtsa_Remote_Interface *RtsaRemoteInterface = NULL, RtSa_Dialog_Digitinput *input = NULL, QWidget *parent = 0);
    ~RtSa_Dialog_FmtTable();
    void initTable();

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
    Ui::RtSa_Dialog_FmtTable *ui;
   Rtsa_Remote_Interface *RemoteInterfaceObj;
    RtSa_Dialog_Digitinput *mInput;

    void showInputDialog(qint32 index);
    void tabelChange(qint32 step);
    void refreshEditDisplay(quint32 index);
    void refreshCurRowIndex();
    void refreshFmtData();
    qreal* mLimitFreq;
    qreal* mLimitAmpt;
    qint32 mColumnIndex;
//    qint32 mShowType;
};

#endif // RTSA_DIALOG_FMTTABLE_H
