#ifndef PM_DIALOG_CH_STD_H
#define PM_DIALOG_CH_STD_H

#include <QWidget>
#include "pm_interface.h"
#include "pm_user_variable.h"
#include <QButtonGroup>
#include <QKeyEvent>

namespace Ui {
class Pm_Dialog_Ch_Std;
}

class Pm_Dialog_Ch_Std : public QWidget
{
    Q_OBJECT

public:
    explicit Pm_Dialog_Ch_Std(BitPm_Interface *BitPmInterface = NULL,QWidget *parent = 0);
    ~Pm_Dialog_Ch_Std();
protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_pb_cancel_clicked();
    void on_pb_up_clicked();
    void on_pb_down_clicked();
    void runBtnTypeFunction(qint32 index);
    void on_currentCellChanged(qint32 currentRow, qint32 currentColumn, qint32 previousRow, qint32 previousColumn);
    void on_pb_ok_clicked();
    void on_pb_close_clicked();
private:
    BitPm_Interface *PmInterfaceObj;
    qint32 tabPageIndex;
    qint32 curCHIndex;
    Ui::Pm_Dialog_Ch_Std *ui;
    QButtonGroup *mTypeGroup;
    qint32 ChType;
    void initWidget();
    void initDisplay();
    void initMap();
    void initTabContent(qint32 index);
    void analysisData(QString str);
    void getBandInfo(qint32 STDIndex);
    void initTabPage();
};

#endif // PM_DIALOG_CH_STD_H
