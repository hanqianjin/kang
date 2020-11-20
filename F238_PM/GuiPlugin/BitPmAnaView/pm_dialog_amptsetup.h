#ifndef PM_DIALOG_AMPTSETUP_H
#define PM_DIALOG_AMPTSETUP_H

#include <QWidget>
#include <QMap>
#include <QDialog>
#include <QButtonGroup>
#include "pm_lineedit.h"
#include "pm_dialog_digitinput.h"
#include <QKeyEvent>
#include <QTimer>
#include "pm_interface.h"

namespace Ui {
class Pm_Dialog_AmptSetup;
}

class Pm_Dialog_AmptSetup : public QWidget
{
    Q_OBJECT

public:
    explicit Pm_Dialog_AmptSetup(BitPm_Interface *BitPmInterface,Pm_Dialog_Digitinput* input= NULL, QWidget *parent = 0);
    ~Pm_Dialog_AmptSetup();
protected:
    void mousePressEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void finishEntry_ampt(qint32 index);
    void on_pb_cancel_clicked();
    void DigitalKeyRespond(QKeyEvent *event);
    void on_timeOut();


    void btn_clicked();

    void on_leMax_clicked();
    void on_leMin_clicked();
    void on_leEnterOffset_clicked();

    void unitSelect(qint32 index);
    void on_pb_Scale_Auto_clicked();


    void on_pb_unitSelect_highlighted(int index);

    void on_pb_SetForward_clicked();
    void on_pb_SetReverse_clicked();

    void on_pb_ForwardRelative_toggled(bool checked);
    void on_pb_ReverseRelative_toggled(bool checked);
    void on_leEnterForward_clicked();
    void on_leEnterReverse_clicked();


public:
    void initDisplay();
private:
    void initMap();
    void refreshEditDisplay(quint32 index);
    void refreshButtonDisplay();
    void showInputDialog(qint32 index);

private:
    Ui::Pm_Dialog_AmptSetup *ui;
    BitPm_Interface *PmInterfaceObj;
    Pm_Dialog_Digitinput *mInputDialog;
    QMap <quint32,Pm_LineEdit*> mEditList;

    qint32 mSelectInputID;
    QTimer *timer;
    qint32 mUpDownFlag;
    qint32 m_UpFlg;    //向上加数据个数 从0 开始  超过10后进位加
    qint32 m_DownFlg;//向下加数据个数 从0 开始  超过10后进位减

};

#endif // PM_DIALOG_AMPTSETUP_H
