#ifndef PM_DIALOG_LIMITSTEUP_H
#define PM_DIALOG_LIMITSTEUP_H

#include <QWidget>
#include "pm_interface.h"
#include "pm_dialog_digitinput.h"
#include "pm_lineedit.h"
#include <QKeyEvent>
#include <QButtonGroup>
#include <QTimer>

namespace Ui {
class Pm_Dialog_Limit;
}

class Pm_Dialog_Limit : public QWidget
{
    Q_OBJECT

public:
    explicit Pm_Dialog_Limit(BitPm_Interface *BitPmInterface= NULL,Pm_Dialog_Digitinput* input = NULL, QWidget *parent = 0);
    ~Pm_Dialog_Limit();


protected:
    void keyPressEvent(QKeyEvent *event);
private slots:
    void finishEntry_Limit(qint32 index);
    void on_pb_cancel_clicked();
    void DigitalKeyRespond(QKeyEvent *event);
    void on_timeOut();

    void on_pb_Limt_toggled(bool checked);
    void on_ledForwardUp_clicked();
    void on_ledForwardLow_clicked();
    void on_ledReverseUp_clicked();
    void on_ledReverseLow_clicked();
    void on_pb_Full_clicked();
    void on_pb_4k_clicked();
    void on_pb_200k_clicked();


public:
    void initDisplay();
private:
    void initMap();
    void refreshEditDisplay(quint32 index);
    void refreshButtonDisplay();
    void showInputDialog(qint32 index);
private:
    Ui::Pm_Dialog_Limit *ui;
    BitPm_Interface *PmInterfaceObj;
    Pm_Dialog_Digitinput *mInputDialog;
    QMap <quint32,Pm_LineEdit*> mEditList;

    qint32 mSelectInputID;
    QTimer *timer;
    qint32 mUpDownFlag;
    qint32 m_UpFlg;    //向上加数据个数 从0 开始  超过10后进位加
    qint32 m_DownFlg;//向下加数据个数 从0 开始  超过10后进位减
};

#endif // PM_DIALOG_LIMITSTEUP_H
