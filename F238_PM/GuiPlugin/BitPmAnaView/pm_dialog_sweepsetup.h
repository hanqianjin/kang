#ifndef PM_DIALOG_SWEEPSETUP_H
#define PM_DIALOG_SWEEPSETUP_H

#include <QWidget>
#include "pm_interface.h"
#include "pm_dialog_digitinput.h"
#include "pm_lineedit.h"
#include <QKeyEvent>
#include <QTimer>

namespace Ui {
class Pm_Dialog_SweepSetup;
}

class Pm_Dialog_SweepSetup : public QWidget
{
    Q_OBJECT

public:
    explicit Pm_Dialog_SweepSetup(BitPm_Interface *BitPmInterface = NULL,Pm_Dialog_Digitinput *input = NULL,QWidget *parent = 0);
    ~Pm_Dialog_SweepSetup();
protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void finishEntry_sweep(qint32 index);
    void on_pb_cancel_clicked();
    void DigitalKeyRespond(QKeyEvent *event);
    void on_timeOut();

    void on_LedTimeInterval_clicked();
    void on_ledDutyCycle_clicked();
    void on_LedMeasureOffset_clicked();
    void on_pb_conti_clicked();
    void on_pb_single_clicked();


public:
    void initDisplay();
private:
    void initMap();

    void refreshEditDisplay(quint32 index);
    void showInputDialog(qint32 index);
    void refreshButtonDisplay();
private:
    Ui::Pm_Dialog_SweepSetup *ui;
    BitPm_Interface *PmInterfaceObj;
    Pm_Dialog_Digitinput *mInputDialog;
    QMap <quint32,Pm_LineEdit*> mEditList;

    qint32 mSelectInputID;
    QTimer* timer;
    qint32 mUpDownFlag;
    qint32 m_UpFlg;    //向上加数据个数 从0 开始  超过10后进位加
    qint32 m_DownFlg;//向下加数据个数 从0 开始  超过10后进位减
};

#endif // PM_DIALOG_SWEEPSETUP_H
