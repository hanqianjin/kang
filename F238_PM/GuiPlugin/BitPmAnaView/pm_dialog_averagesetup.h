#ifndef PM_DIALOG_AVERAGESETUP_H
#define PM_DIALOG_AVERAGESETUP_H

#include <QWidget>
#include <QPainter>
#include <QButtonGroup>
#include "pm_interface.h"
#include "pm_dialog_digitinput.h"
#include "pm_lineedit.h"
#include <QKeyEvent>
#include <QTimer>

namespace Ui {
class Pm_Dialog_AverageSetup;
}
class Pm_Dialog_AverageSetup : public QWidget
{
    Q_OBJECT
public:
    explicit Pm_Dialog_AverageSetup(BitPm_Interface *BitPmInterface,Pm_Dialog_Digitinput *mInput,QWidget *parent = 0 );
    ~Pm_Dialog_AverageSetup();
protected:
    void keyPressEvent(QKeyEvent *event);
signals:
private slots:
    void finishEntry_average(qint32 index);
    void on_pb_cancel_clicked();
    void DigitalKeyRespond(QKeyEvent *event);
    void on_timeOut();

    void on_pb_Fast_clicked();
    void on_pb_Med_clicked();
    void on_pb_Slow_clicked();
    void on_pb_MaxHold_toggled(bool checked);
    void on_leAveragePoint_clicked();

    void on_pb_RunningAverage_toggled(bool checked);


public:
    void initDisplay();
private:
    void initMap();
    void showInputDialog(qint32 index);
    void refreshEditDisplay(quint32 index);
    void refreshButtonDisplay();
private:
    Ui::Pm_Dialog_AverageSetup *ui;
    BitPm_Interface *PmInterfaceObj;
    Pm_Dialog_Digitinput *mInputDialog;
    QMap <quint32,Pm_LineEdit*> mEditList;

    qint32 mSelectInputID;
    QTimer* timer;
    qint32 mUpDownFlag;
    qint32 m_UpFlg;    //向上加数据个数 从0 开始  超过10后进位加
    qint32 m_DownFlg;//向下加数据个数 从0 开始  超过10后进位减
};

#endif // PM_DIALOG_AVERAGESETUP_H
